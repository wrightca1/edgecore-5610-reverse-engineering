# cl-acltool — iptables → BCM Field Processor TCAM

How Cumulus translates Linux iptables rules into BCM FP (Field Processor)
TCAM entries. The mechanism uses a **FUSE filesystem** mounted by switchd.

## Architecture overview

```
USER (admin):
  edits /etc/cumulus/acl/policy.d/*.rules
  runs `cl-acltool -i`
    ↓
cl-acltool (Python, 1435 lines):
  1. Parse rules via cumulus.aclpolicy (3 sections: [iptables], [ip6tables], [ebtables])
  2. Apply to Linux kernel via iptables-restore
  3. Tell switchd to re-sync HW via FUSE control file
    ↓
switchd (statically links libfuse.so.2):
  - Reads kernel iptables rules (via iptables-save / netfilter intro)
  - For each rule with HW-applicable action (SETCLASS/POLICE/DROP/COPY_TO_CPU):
    - Translates to BCM FP qualifiers + actions
    - Calls bcm_field_entry_create + bcm_field_qualify_* + bcm_field_action_add + bcm_field_entry_install
    ↓
BCM Trident+ Field Processor TCAM
  - Hardware-accelerated rule matching
  - Per-port stats counters
```

## switchd is a FUSE filesystem!

`switchd` is linked against `libfuse.so.2`. It mounts a **virtual control
filesystem** at `/cumulus/switchd/`. Userspace tools poke entries here to
request actions.

ACL-related control paths (from `cl-acltool` source):
* `/cumulus/switchd/ctrl/acl/stop_stats_sync` — write "1" to pause stats sync
* `/cumulus/switchd/ctrl/acl/reset_stats_sync` — reset stats counters
* `/cumulus/switchd/ctrl/acl/resync` — re-program FP from current iptables (writes "1", reads result back)

The flow uses **write + immediate read** on `resync`:

```python
def hw_sync_commit():
    with open("/cumulus/switchd/ctrl/acl/resync", "r+") as f:
        f.write("1")           # request resync
        f.seek(0)
        ret = f.read().strip()  # read status
        if ret and len(ret) > 1:
            log_crit('hw sync failed (%s)' % ret)
            return -1
    return 0
```

switchd's FUSE write handler:
1. Sees the "1" write
2. Reads current iptables rules from kernel
3. Translates to BCM FP entries (calls bcm_field_*)
4. Returns success/error string on next read

## cl-acltool full lifecycle (the `-i` install path)

```
1. cl-acltool -i [-P policy.d/...]
2. read_config_file(policy.conf)        # global env vars
3. for each *.rules file in policy.d:
     aclPolicy.parse()                  # tokenize [iptables]/[ip6tables]/[ebtables] blocks
4. resolve $VAR substitutions           # e.g. $INGRESS_INTF=swp+
5. generate combined iptables-restore-format files
6. exec_command('iptables-restore < /tmp/...')   # Linux kernel side
7. exec_command('ip6tables-restore < /tmp/...')
8. exec_command('ebtables-restore < /tmp/...')
9. hw_init():
     open(/cumulus/switchd/ctrl/acl/stop_stats_sync, "w")  # connect to switchd
10. hw_sync_start():
     write "1" to stop_stats_sync
11. hw_sync_commit():
     write "1" + read result from /cumulus/switchd/ctrl/acl/resync
12. hw_sync_end():
     no-op
```

If hw_sync fails, `iptables_rollback()` is called to revert to the
saved pre-install rules. Atomic from the user's POV.

## The rule-file format

`/etc/cumulus/acl/policy.d/00control_plane.rules` (we captured earlier):

```
INGRESS_INTF = swp+
INGRESS_CHAIN = INPUT
INNFWD_CHAIN = INPUT,FORWARD
MARTIAN_SOURCES_4 = "240.0.0.0/5,127.0.0.0/8,224.0.0.0/8,255.255.255.255/32"

[iptables]
-A $INNFWD_CHAIN --in-interface $INGRESS_INTF -s $MARTIAN_SOURCES_4 -j DROP
-A $INGRESS_CHAIN --in-interface $INGRESS_INTF -p ospf -j SETCLASS --class 7
-A $INGRESS_CHAIN -p ospf -j POLICE --set-mode pkt --set-rate 2000 --set-burst 2000
...

[ip6tables]
-A $INNFWD_CHAIN --in-interface $INGRESS_INTF -s $MARTIAN_SOURCES_6 -j DROP
...

[ebtables]
-A INPUT -d BGA -i swp+ -j setclass --class 7
-A INPUT -d 1:80:c2:0:0:2 -i swp+ -j setclass --class 7
-A INPUT -p ARP -i swp+ -j setclass --class 2
...
```

Rule blocks delimited by `[iptables]` / `[ip6tables]` / `[ebtables]`.
`$VAR` substitution from `policy.conf` + per-file env-vars.

## aclpolicy.py — the parser

```python
class aclRuleType:
    iptables, ip6tables, ebtables, iptables_raw = range(4)

class aclRule(object):
    """One -A line"""
    def __init__(self, rule_line, rule_type):
        self.rule = rule_line
        self.type = rule_type

class aclPolicy(object):
    """One .rules file"""
    rule_block_parsers = {
        '[iptables]': {'type': iptables, 'parse_func': parse_iptables_rules},
        '[ip6tables]': {'type': ip6tables, 'parse_func': parse_ip6tables_rules},
        '[ebtables]': {'type': ebtables, 'parse_func': parse_ebtables_rules},
        '[iptables-raw]': {'type': iptables_raw, 'save_func': save_iptables_raw},
    }
```

Simple line-by-line tokenizer. `[iptables-raw]` is for advanced users
who want to bypass Cumulus's variable substitution.

## linuxpktfilter.py — the kernel-side applier

408 lines. Wraps `iptables-restore` / `ip6tables-restore` /
`ebtables-restore` invocations:

```python
class pktFilterBase():
    def restore(self, table, file, ...): ...
    def save(self, table, file, ...): ...

class iptables(pktFilterBase):
    kernel_tables = ['filter', 'nat', 'mangle', 'raw', 'security']
    restore_cmd = 'iptables-restore'
    save_cmd = 'iptables-save'

class ip6tables(pktFilterBase):
    kernel_tables = ['filter', 'nat', 'mangle', 'raw', 'security']
    restore_cmd = 'ip6tables-restore'

class ebtables(pktFilterBase):
    kernel_tables = ['filter', 'nat']
    restore_cmd = 'ebtables-restore'
```

So Cumulus uses **standard Linux netfilter** for kernel-side. No magic.
The HW side is what's different — that's the switchd FUSE call.

## EdgeNOS implications

For EdgeNOS to support similar ACL programming:

### Option A: Mirror the FUSE model
1. EdgeNOS's switchd-equivalent mounts a FUSE filesystem at `/edgenos/control/`
2. A `acl/resync` virtual file triggers re-read of iptables + program BCM FP
3. cl-acltool-equivalent is mostly portable as-is (just change ctrl_base path)

### Option B: Direct API call
1. EdgeNOS's `cl-acltool`-equivalent reads policy files
2. Translates rules to OpenMDK `bmd_field_*` calls directly (no FUSE)
3. Updates iptables in parallel (standard restore)
4. Less elegant but simpler than mounting a FUSE filesystem

### What stays the same regardless:
* Policy file format: `[iptables]`/`[ip6tables]`/`[ebtables]` sections + `$VAR` substitution
* Linux side: standard `iptables-restore` etc.
* Rule format: standard iptables syntax + `SETCLASS`/`POLICE` extensions
* `cumulus.aclpolicy` + `cumulus.linuxpktfilter` can be **reused as-is** in EdgeNOS

## switchd's FUSE — the broader picture

`/cumulus/switchd/` is the control surface. ACL is just one subtree.
Other expected paths (inferred from cl-* tool patterns):

* `/cumulus/switchd/ctrl/acl/` — ACL control
* `/cumulus/switchd/ctrl/route/` — L3 route control (config/route/...)
* `/cumulus/switchd/ctrl/port/` — per-port control
* `/cumulus/switchd/ctrl/stat/` — counter access
* `/cumulus/switchd/debug/` — debugging knobs
* `/cumulus/switchd/version` — switchd version (we saw this earlier)

Discoverable at runtime by `ls /cumulus/switchd/` (would need to be live to test).

## Files captured

* `cl-acltool` (35,727 bytes, 1435 lines Python)
* `aclpolicy.py` (rule parser)
* `linuxpktfilter.py` (iptables wrapper)
* `00control_plane.rules` + `99control_plane_catch_all.rules` (the rules themselves)

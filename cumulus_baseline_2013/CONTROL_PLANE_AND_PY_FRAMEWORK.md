# Control Plane ACLs + Cumulus Python Framework

Deep dive into two subsystems revealed by live chassis inspection:

1. The **default control-plane ACL rules** at `/usr/share/cumulus/acl/` —
   these define what packets get punted to CPU and at what rate (CoPP).
2. The **Cumulus Python framework** at `/usr/lib/python2.7/dist-packages/cumulus/` —
   the modules that all cl-* tools and Python daemons import.

Neither was visible in static binary analysis. Both are critical for
EdgeNOS feature parity.

---

## 1. Default CoPP — `/usr/share/cumulus/acl/`

Cumulus ships **two ACL policy files** that get loaded into the FP TCAM
at boot via `aclinit` → `cl-acltool --boot`:

| File | Purpose |
|---|---|
| `00control_plane.rules` (5782 B) | Per-protocol classification + rate-limit |
| `99control_plane_catch_all.rules` (912 B) | Catch-all for unmatched traffic |

The lexicographic ordering matters: `00...` first, `99...` last —
classifying traffic before the catch-all.

### `00control_plane.rules` — protocol-specific punt + police

Uses iptables syntax with two Cumulus-specific extensions:
- **`SETCLASS --class N`** — sets the internal priority class (0-7)
- **`POLICE --set-mode pkt --set-rate R --set-burst B`** — rate-limit

Classes have implicit priority: class 7 = highest, class 0 = lowest.

#### IPv4 rules (iptables)

| Protocol | Class | Rate (pps) | Burst | Notes |
|---|---|---|---|---|
| OSPF | 7 | 2000 | 2000 | Routing protocol — highest prio |
| BGP (tcp dport/sport 179) | 7 | 2000 | 2000 | Routing protocol |
| CLAG (tcp port 5342) | 7 | 2000 | 2000 | MLAG sync — high prio |
| ICMP | 2 | 100 | 40 | Ping etc. |
| BOOTP (udp + tcp 67/68) | 2 | 100 | 100 | DHCP |
| IGMP | 6 | 300 | 100 | Multicast |
| Martian sources | drop | — | — | 240.0.0.0/5, 127.0.0.0/8, 224.0.0.0/8, 255.255.255.255 |

#### IPv6 rules (ip6tables)

| Protocol | Class | Rate (pps) | Burst |
|---|---|---|---|
| OSPFv3 | 7 | 2000 | 2000 |
| BGP (tcp dport/sport 179) | 7 | 2000 | 2000 |
| Router Solicitation/Advertisement | 2 | 100 | 100 |
| Neighbour Solicitation/Advertisement | 2 | 100 | 100 |
| MLD Listener Query/Report/Done (icmp6 130/131/132) | 6 | 200 | 100 |
| MLD Listener Report v2 (icmp6 143) | 6 | 200 | 100 |
| ICMPv6 (other) | 2 | 64 | 40 |
| DHCPv6 (udp/tcp 546/547) | 2 | 100 | 100 |
| Martian IPv6 sources | drop | — | — | ff00::/8, ::/128, ::ffff:0.0.0.0/96, ::1/128 |

### `99control_plane_catch_all.rules` — last-resort

Anything not matched above falls through to:

| Destination | Class | Rate (pps) | Burst |
|---|---|---|---|
| LOCAL (to this box) | 0 | 1000 | 1000 |
| IPROUTER (routed by this box) | 0 | 400 | 100 |
| L2 broadcast (ebtables) | 0 | 100 | 100 |

These are the **last-resort rate limiters** that prevent CPU melt-down
from unexpected traffic. Any L3 packet destined for the chassis itself
is capped at 1000 pps; any L3 router-type punt is capped at 400 pps.

### How these rules end up in the chip

```
1. /etc/init.d/aclinit at boot
2. → cl-acltool --boot
3. → reads /usr/share/cumulus/acl/*.rules (in name order)
4. → expands variables ($INGRESS_INTF=swp+, $INGRESS_CHAIN=INPUT, etc.)
5. → translates iptables syntax → bcm_field_* SDK calls
   (via /usr/lib/python2.7/dist-packages/cumulus/linuxpktfilter.py)
6. → talks to switchd via /cumulus/switchd/ctrl/acl/ FUSE paths
7. → switchd → bcm_field_group_create + bcm_field_entry_create +
       bcm_field_qualify_* + bcm_field_action_add
8. → SCHAN writes to FP TCAM
```

### For EdgeNOS

The control-plane ACL rules need to be in EdgeNOS too. Without them:
- BGP/OSPF can be DoS'd by malicious packets (rate-limit missing)
- ARP storms can overwhelm the CPU
- Martian sources will be processed instead of dropped

**Action items:**
- [ ] Copy `00control_plane.rules` and `99control_plane_catch_all.rules`
      verbatim — they're vendor-agnostic iptables syntax
- [ ] Implement `cl-acltool`-equivalent that parses iptables → FP TCAM
      (see `linuxpktfilter.py` for reference)
- [ ] Load at boot before user-defined ACLs

---

## 2. Cumulus Python Framework

Living at `/usr/lib/python2.7/dist-packages/cumulus/`:

### Module structure (17 modules)

| Module | Purpose |
|---|---|
| `__init__.py` | Package marker |
| `__chip_config/` | Chip-default config templates (sdk.bcm for Trident, etc.) |
| `aclpolicy.py` | ACL policy file parser (reads `*.rules` files) |
| `cpld.py` | CPLD register access wrapper |
| `ledup.py` | LED uController bytecode upload / status |
| `linuxpktfilter.py` | iptables → BCM FP translation (the cl-acltool core) |
| `platform.py` | Platform base class + chip class hierarchy |
| `platformdb.py` | Per-platform module registry |
| `platforms/` | Per-platform Python modules (one per hardware) |
| `portconfig.py` | ports.conf parser |
| `porttab.py` | porttab (Linux↔BCM port name mapping) reader |
| `sensors.py` | Sensor reader (uses lm-sensors output) |
| `sff8472.py` | SFP+ DOM parser per SFF-8472 spec |
| `sfp.py` | SFP class — generic module access |
| `sfputilbase.py` | Base class for cl-sfputil |
| `sunit.py` | Unit conversion (bytes/sec etc.) |
| `sysledcontrol.py` | System LED control |
| `utilities.py` | Common helpers |

### `platform.py` — the chip-class hierarchy

```python
class Platform:
    revision = None
    cpld = None
    switch = None

class BCMChip:
    '''BCM chip common attributes'''
    hsp_bw          = None    # Hierarchical Service Pool bandwidth
    portmap_capable = None    # Whether portmap_N.0 config is supported
    base_pbmp       = None    # Always-on port bitmap
    file_list       = None    # Which chip-config files to use

    def get_config(self, file_name):
        '''Read chip-default config from __chip_config/'''
        for prefix in ['/bcm']:
            path = chip_config_path + prefix + '/' + file_name
            if os.path.exists(path):
                return open(path).read()
        return None

class TridentChip(BCMChip):
    '''Trident chip (BCM56846 etc.)'''
    portmap_capable = True
    base_pbmp = 0x20000000000000001   # LBPORT0 | CPU port
    file_list = ('datapath.conf', 'rc.forwarding', 'hw_desc', 'sdk.bcm')
```

There are similar classes for `TridentTwoChip`, `Apollo`, `Triumph`,
etc. — each chip family has its own bitmap and feature flags.

This is the framework that `datapath-update` uses to know "for this
chip family, do X; for that one, do Y." Critical pattern for any
multi-chip-family NOS.

### `__chip_config/` — chip-default config templates

```
__chip_config/
├── bcm/
│   ├── Apollo/sdk.bcm          # BCM56624 family
│   ├── Trident/sdk.bcm         # BCM568xx (ours)
│   ├── TridentTwo/sdk.bcm      # BCM56850 family
│   └── Triumph/sdk.bcm         # BCM56624 older
```

The `sdk.bcm` is the **chip defaults** that get merged with the platform's
`config.bcm` at switchd startup. We have the Trident/sdk.bcm captured
(37 lines, see `ASIC_INIT_COOKBOOK.md` § 4).

### `platformdb.py` — platform registry

A dict mapping platform-detect strings to Python platform classes:

```python
# Pseudocode
platform_db = {
    'accton_as5610_52x': AcctonAs5610_52xPlatform,
    'accton_as5712_54x': AcctonAs5712_54xPlatform,
    'dell_s4000_c2338':  DellS4000Platform,
    # ...
}
```

`cl-platform` detects the platform via `decode-syseeprom`, looks up the
class, instantiates it. The class has properties like `cpld`, `switch`
(BCMChip instance), `sfp_ports`, etc.

### `linuxpktfilter.py` — iptables → FP TCAM

The translation engine. Takes iptables match expressions and produces
BCM field-qualifier API calls:

```python
# Pseudocode
def translate_match(iptables_match):
    if iptables_match.proto == 'tcp':
        bcm_field_qualify_IpProtocol(entry, IPPROTO_TCP, 0xff)
    if iptables_match.dport:
        bcm_field_qualify_L4DstPort(entry, dport, 0xffff)
    if iptables_match.src:
        bcm_field_qualify_SrcIp(entry, src_ip, src_mask)
    # ...

def translate_action(iptables_action):
    if iptables_action == 'DROP':
        bcm_field_action_add(entry, bcmFieldActionDrop)
    elif iptables_action.startswith('POLICE'):
        meter = bcm_meter_create(rate, burst)
        bcm_field_action_add(entry, bcmFieldActionMeter, meter)
    elif iptables_action == 'COPY_TO_CPU':
        bcm_field_action_add(entry, bcmFieldActionCopyToCpu)
```

### `cpld.py` — CPLD access from Python

```python
class CPLD:
    def read(self, offset): ...
    def write(self, offset, value): ...
    def read_field(self, offset, field_name): ...

# Uses /dev/i2c-N to talk to the Accton CPLD at I²C address 0x32
```

Used by `sysledcontrol`, `smond`, `ledmgrd` for chassis LEDs and PSU/fan
state queries.

### `ledup.py` — LED uController interface

```python
def assemble(led_source_file):
    '''Assemble LED bytecode (calls ledasm)'''

def upload(uC_id, hex_file):
    '''Upload bytecode to LED uController via switchd'''

def status(uC_id):
    '''Read uController state (running/halted/error)'''
```

### `sff8472.py` — SFP+ DOM parser

Parses the 256-byte SFP+ EEPROM per SFF-8472 spec:
- Vendor name (bytes 20-35)
- Vendor part number (40-55)
- Vendor serial number (68-83)
- Date code (84-91)
- Diagnostic monitoring (page A2h):
  - Temperature, Vcc, TX bias, TX power, RX power
  - Alarm/warning thresholds

### `sensors.py` — sensor interface

Wraps `lm-sensors`' libsensors. Used by `smond` to:
- Read CPU temp, DIMM temp, BCM die temp
- Read fan tachs from CPLD via gpio_pca953x
- Read PSU status from CPLD

---

## 3. Per-platform Python modules

`platforms/` (subdir of cumulus framework) contains one module per
platform. For us:

```python
# platforms/accton_as5610_52x.py
class AcctonAs5610_52x(Platform):
    revision = 'as5610_52x'
    cpld = AcctonCPLD(i2c_bus=0, i2c_addr=0x32)
    switch = TridentChip()  # BCM56846
    # ... port definitions, sensor mappings, etc.
```

These per-platform modules tell the framework:
- Which CPLD class (each vendor has different CPLD register layouts)
- Which chip class (Trident / TridentTwo / Apollo)
- Port count and layout
- Sensor topology

The `cl-platform` shell wrapper runs `python -c 'import cumulus.platformdb;
print platformdb.platform_db["accton_as5610_52x"].__class__.__name__'`
to find the right class.

---

## 4. Where switchd reads chip-default config

Per `BCM_INIT_STATIC_CHAIN.md`, switchd's startup flow includes:

```c
soc_cm_device_create_id(unit);
sysconf_attach(unit);            // FUN_10109348
   ↑
   reads /etc/bcm.d/config.bcm + sdk.bcm template
```

The `sdk.bcm` template comes from
`/usr/lib/python2.7/dist-packages/cumulus/__chip_config/bcm/Trident/sdk.bcm`.

But switchd doesn't load it from Python — there's a SEPARATE mechanism:
- `datapath-update` (Python, at install time) writes the merged config to
  `/etc/bcm.d/config.bcm`
- switchd reads `/etc/bcm.d/config.bcm` at startup

So the Python framework is **install-time + boot-time configuration**;
switchd at runtime is independent of Python.

---

## 5. EdgeNOS implications

For EdgeNOS, we need to either:

### Option A: Adopt Cumulus's Python framework

Pros:
- Battle-tested
- Multi-platform-ready (23 platforms supported)
- Compatible with `cl-*` tools out of the box
- BSD/GPL Python code (mostly)

Cons:
- Tied to Cumulus's design choices
- Python 2.7 (need to port to 3.x)
- Large code base

### Option B: Reimplement minimally

Pros:
- Cleaner, modern Python 3
- Only need what AS5610-52X actually uses
- No legacy baggage

Cons:
- Reimplements many things (cpld, sff8472, platform detect)

### Recommended: Hybrid

- **Reuse:** sff8472.py (vendor-agnostic SFP DOM parser)
- **Adapt:** platform.py framework (rewrite for Python 3, simplify)
- **Custom:** cpld.py specifically for accton_as5610_52x (we already have
  our own CPLD driver in EdgeNOS)
- **Skip:** Multi-platform support (just AS5610 for now)

---

## 6. Files

- `/usr/share/cumulus/acl/00control_plane.rules` — default CoPP rules
- `/usr/share/cumulus/acl/99control_plane_catch_all.rules` — catch-all
- `/usr/lib/python2.7/dist-packages/cumulus/` — Python framework root
- `/etc/cumulus/init/accton_as5610_52x/platform.conf` — platform config
- `/etc/cumulus/init/accton_as5610_52x/platform.fdisk` — partition layout

For EdgeNOS reference:
- The default CoPP rules — copy verbatim
- `platform.py` + `__chip_config/bcm/Trident/sdk.bcm` — chip-config template
- `platform.fdisk` — partition recipe for the AS5610's USB flash

---

*Captured 2026-05-11 via live SSH inspection. These items were invisible
to static rootfs extraction because:
- ACL `.rules` files are user-visible but not bound to a specific binary
- Python modules are .pyc compiled at install time (we have the .py
  sources here)
- Per-platform configs were in subdirs our extraction script didn't
  recurse into.*

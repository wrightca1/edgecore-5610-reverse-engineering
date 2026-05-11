# FP TCAM + MMU + Remaining Subsystems

Coverage of the previously-unexplored areas: Field Processor (ACL TCAM),
MMU buffer management, VLAN translation, Mirror/SPAN, Storm control,
Linkscan, KNET stubs, and the `cl-acltool` glue.

This closes the remaining gaps in `WHATS_MISSING.md`.

---

## 1. Field Processor (FP TCAM) — 857 functions discovered

The FP TCAM is the chip's **ACL classifier**. Every packet entering
ingress (or leaving egress, depending on stage) gets matched against
the FP TCAM, and on hit takes an action: drop, copy-to-CPU, set class,
mirror, ratelimit, etc.

### FP geometry on Trident+ (BCM56846)

| Stage | Slices | Entries/slice | Total entries |
|---|---|---|---|
| IFP (Ingress) | 9 | 256 | 2,304 |
| VFP (VLAN, pre-bridging) | 4 | 128 | 512 |
| EFP (Egress) | 2 | 256 | 512 |

(From the chip's `run/acl_info` data we captured in the FUSE filesystem.)

### Function discovery by category (FP TCAM = 857 hits)

| Group | Sample functions |
|---|---|
| **Entry CRUD** | `bcm_field_entry_create` (FUN_1013c260, 928B), `bcm_field_entry_destroy` (FUN_1013cc7c, 788B), `bcm_field_entry_copy_id` (FUN_1013c600, 936B) |
| **Group CRUD** | `bcm_field_group_create` (FUN_1013df90, 4060B), `bcm_field_group_destroy`, `bcm_field_group_enable_set/get` |
| **Entry control** | `bcm_field_entry_enable_set/get` (FUN_10079718, 1488B), `bcm_field_entry_prio_set` (FUN_1013d8e0, 1152B), `bcm_field_entry_install`, `bcm_field_entry_reinstall` |
| **Qualifiers (matches)** | `bcm_field_qualify_SrcIp{,6}`, `bcm_field_qualify_DstIp{,6}`, `bcm_field_qualify_SrcPort`, `bcm_field_qualify_L4{Src,Dst}Port`, `bcm_field_qualify_IcmpTypeCode`, `bcm_field_qualify_TcpControl`, `bcm_field_qualify_Vlan`, `bcm_field_qualify_OutPort`, `bcm_field_qualify_DstClassL3`, etc. (50+ types) |
| **Actions (on match)** | `bcm_field_action_add` (FUN_10216970), `bcm_field_action_remove`, etc. |
| **Statistics** | `bcm_field_stat_create`, `bcm_field_entry_stat_attach`, `bcm_field_stat_get` |

### `bcm_field_group_create` flow

```c
int bcm_field_group_create(unit, priority, qset, *group_id_out) {
    /* 1. Parse command-line args (76 B qset struct) */
    bcm_field_qset_t local_qset;
    memcpy(&local_qset, user_qset, 0x4c);   // 76 bytes

    /* 2. Call internal impl (FUN_103ab670) */
    int rc = _bcm_field_group_create_internal(unit, &local_qset, priority,
                                              &group_id);
    if (rc < 0) {
        log("FP(unit %d) Error: bcm_field_group_create failed: %s",
            unit, err_str(rc));
        return rc;
    }

    log("FP(unit %d) verb: bcm_field_group_create success", unit);
    return 0;
}
```

The internal impl allocates an unused FP slice (out of 9 IFP slices for
Trident+), programs the slice's qualifier-selection register
(`FP_SLICE_CONFIG`, `FP_DOUBLE_WIDE_SELECT`, etc.), and returns a
handle.

### `bcm_field_entry_create` flow

```c
int bcm_field_entry_create(unit, group_id, *entry_id_out) {
    /* 1. Verify group exists and has free slots */
    /* 2. Allocate next free TCAM index in the group's slice */
    /* 3. Return entry_id as (group << 16) | index */
}
```

Entries are NOT installed until `bcm_field_entry_install()` is called.
This allows you to fully configure (qualifiers + actions) before
committing.

### Adding qualifiers (matches)

```c
int bcm_field_qualify_DstIp(unit, entry_id, data, mask) {
    /* Look up entry's slice config */
    /* Validate that DstIp is in the qset for this group */
    /* Write data + mask into TCAM word(s) at the right bit offset */
    /* Mark entry dirty (needs install) */
}
```

### Adding actions

```c
int bcm_field_action_add(unit, entry_id, action_type, param0, param1) {
    /* Encode action into TCAM data RAM word at entry's index */
    /* action_type values:
       bcmFieldActionDrop          = drop the packet
       bcmFieldActionCopyToCpu     = punt to CPU
       bcmFieldActionRedirectPort  = redirect to specified port
       bcmFieldActionPrioPktNew    = set internal priority
       bcmFieldActionMirrorIngress = mirror to mirror dest
       bcmFieldActionStatGroup     = bind to a counter
    */
}
```

### Installing the entry

```c
int bcm_field_entry_install(unit, entry_id) {
    /* SCHAN write key TCAM entry (slice, index) */
    /* SCHAN write data RAM entry (action bits) */
    /* SCHAN write mask TCAM entry */
    /* Update entry's installed flag */
}
```

After install, the entry actively matches packets.

### Statistics attachment

```c
bcm_field_stat_create(unit, group_id, num_stats, stat_types, *stat_id_out);
/* Allocates a counter from FP_STAT bank */

bcm_field_entry_stat_attach(unit, entry_id, stat_id);
/* Binds entry's stat-counter index */

bcm_field_stat_get(unit, stat_id, type, *value_out);
/* Reads via SCHAN counter-read opcode */
```

### How `cl-acltool` uses this (already covered in CL_ACLTOOL_FLOW.md)

`cl-acltool` parses iptables-style rules → builds an internal model →
writes to `/cumulus/switchd/ctrl/acl/*` FUSE paths → switchd reads
them and translates each rule:

```
iptables -A FORWARD -p tcp --dport 80 -j DROP
        ↓
bcm_field_group_create(qset={bcmFieldQualifyDstL4Port, bcmFieldQualifyIpProtocol})
bcm_field_entry_create(group)
bcm_field_qualify_DstL4Port(entry, 80, 0xffff)
bcm_field_qualify_IpProtocol(entry, IPPROTO_TCP, 0xff)
bcm_field_action_add(entry, bcmFieldActionDrop)
bcm_field_entry_install(entry)
```

---

## 2. MMU buffer management — 141 functions

The MMU (Memory Management Unit) inside the chip manages the **shared
packet buffer pool** (46K cells × 208 bytes = ~9.5 MB total) and the
**per-port/per-queue scheduling**.

### Function categories

| Group | Examples |
|---|---|
| **cosq config** | `bcm_cosq_config_set/get`, `bcm_cosq_control_set/get` |
| **gport (generic port) attach** | `bcm_cosq_gport_attach` (FUN_10126da4, **15 KB** — biggest function) |
| **Scheduling** | `bcm_cosq_sched_strict_set`, `bcm_cosq_sched_weight_set` |
| **Buffer pool** | `bcm_cosq_pfc_class_config_set`, `bcm_cosq_priority_group_*` |
| **Classification** | `bcm_cosq_classifier_create`, `bcm_cosq_classifier_mapping_set` |
| **BST (Buffer Stats Tracking)** | `bcm_cosq_bst_*` family — ~14 functions |

### Where the MMU registers actually live

From `BCM_INIT_REGISTER_MAP.md`, the `rc.datapath_0` writes touch:

**Ingress buffer pools** (THDI):
- `buffer_cell_limit_sp[0..3]` — per service-pool ingress cell limit
- `buffer_cell_limit_sp_shared` — global ingress shared
- `pg_min_cell` (per priority group, per port) — guaranteed buffer per PG
- `pg_shared_limit_cell` — shared limit per PG
- `global_hdrm_limit` — headroom buffer for in-flight after PAUSE

**Egress buffer pools** (THDO):
- `op_queue_config_cell[0..7].$allports` — per-queue per-port limit
- `op_queue_config1_cell[0..7].$allports` — per-queue config2
- `op_buffer_shared_limit_cell[0..3]` — per service-pool egress shared
- `thdo_config_0/1/sp_0/sp_1` — threshold-disable/queue setup arrays

**Scheduling** (egress):
- `s3_config.$allports` — top-level scheduler config
- `s2_config.$allports` — mid-level scheduler config
- `s2_s3_routing.$allports` — which S2 group → which S3 group
- `s2_cosweights/s3_cosweights` — WRR weights per queue
- `cosweights(0..2).$allports` — additional weights
- `esconfig.$allports` — egress scheduler config

**The MMU is the single largest "Hidden" subsystem.** 639 registers total
named (from the 36K register table). Most are configured by `rc.datapath_0`
and never touched again.

### For EdgeNOS

If you copy Cumulus's `rc.datapath_0` verbatim (which programs all the
buffer pools, queue thresholds, and scheduler weights), the MMU is
operational. You only need to call the `bcm_cosq_*` APIs if you want
to do runtime QoS tweaking (e.g., changing a queue's weight on a live
port).

---

## 3. VLAN translation (Ingress/Egress xlate) — 76 functions

The chip has ingress and egress VLAN translation tables that can rewrite
VLAN tags as packets traverse. Used for:
- VLAN translation (Q-in-Q)
- Service-provider VLAN mapping
- VLAN-to-VFI (Virtual Forwarding Instance) for MPLS L2VPN
- Stacked VLAN edge

### Key tables

| Table | Block | Size | Use |
|---|---|---|---|
| `ING_VLAN_XLATE` | IPIPE | 32,768 | (port,outer_VID) → translated VID |
| `EGR_VLAN_XLATE` | EPIPE | 16,384 | output translation |
| `ING_VFI_PROFILE` | IPIPE | 256 | per-VFI behavior |

### API surface

`bcm_vlan_translate_action_create/range_set/create/destroy/get/range_get`
- Mostly used for advanced features (Q-in-Q service VLANs)
- Not used in basic L2/L3 routing

For EdgeNOS basic forwarding, you don't need to program these — they
remain in their default (pass-through) state.

---

## 4. Mirror / SPAN — 35 functions

Port mirroring (copying traffic for IDS or troubleshooting).

### Function family
- `bcm_mirror_init`
- `bcm_mirror_destination_create` — define WHERE to copy traffic
- `bcm_mirror_destination_destroy`
- `bcm_mirror_port_set` — enable mirroring on a port (ingress, egress, or both)
- `bcm_mirror_port_get`

### How it works

1. Create a mirror destination (= a port or a remote-SPAN VLAN):
   ```c
   bcm_mirror_destination_t md;
   md.gport = swp1_gport;       // copies go to swp1
   bcm_mirror_destination_create(unit, &md);
   /* returns mirror_id */
   ```

2. Enable mirroring on a source port:
   ```c
   bcm_mirror_port_set(unit, src_port, mirror_id, BCM_MIRROR_PORT_INGRESS);
   ```

3. From this point: every packet entering `src_port` gets copied (cloned)
   to the mirror destination.

For EdgeNOS basic forwarding, this is **optional** — only needed if you
want IDS/IPS / SPAN port functionality.

---

## 5. Storm control — 3 functions only

Surprisingly small subsystem in switchd: `bcm_rate_set` and `bcm_rate_get`.

Rate-limits broadcast/multicast/unknown-unicast traffic per port (the
"storm control" feature).

From `WHATS_MISSING.md`, this is exposed via `/cumulus/switchd/config/
interface/swpN/storm_control/{broadcast,multicast,unknown_unicast}`.

The 3 functions just translate the FUSE write to a `bcm_rate_set` call.
The chip enforces the rate using **per-port meters** that are part of
the FP TCAM's metering subsystem.

For EdgeNOS, if you don't need storm control, you can skip this entirely.
If you do, the API is:
```c
bcm_rate_set(unit, port, BCM_RATE_BCAST, kbps);
bcm_rate_set(unit, port, BCM_RATE_MCAST, kbps);
bcm_rate_set(unit, port, BCM_RATE_DLF, kbps);   // unknown unicast = DLF
```

---

## 6. Linkscan — 17 functions, full subsystem

The linkscan thread is what gets PHY link state into Linux netdev state.

### Function family
- `bcm_linkscan_init` — start the polling thread (default 250 ms interval)
- `bcm_linkscan_enable_set/get` — enable per-port
- `bcm_linkscan_mode_set/get` — software or hardware linkscan
- `bcm_linkscan_register` — register callback (switchd does this)
- `bcm_linkscan_update` — force a poll cycle

### Hardware-assisted linkscan

Trident+ has a **hardware linkscan engine** that reads PHY status
registers via MIIM and posts events to an interrupt. switchd's mode
is typically `bcmLinkScanModeHard` (hardware), with software fallback
for ports that don't support it.

### Implementation hints

- `FUN_1053bcd0` (3624B) is `bcm_linkscan_errdelay` — error retry timer
- `FUN_100cfcdc` (7072B) is the main linkscan worker
- `FUN_1008f9cc` (1296B) — `bcm_linkscan_interval` setter

The chip's `LINKSCAN_FAILOVER_TIMER` register controls how long the
hardware retries an MIIM read before giving up.

---

## 7. Statistics — 5 functions only

Stats are collected via **counter DMA** (FIFO DMA in our deep-dive doc):
the chip pushes the entire counter bank to host memory periodically,
and switchd reads from the host copy.

### Function family
- `bcm_stat_get` — read a counter (per-port, per-type)
- `bcm_stat_clear` — zero a counter
- `bcm_stat_multi_get` — bulk read
- `bcm_stat_sync` — force a DMA refresh
- `bcm_stat_init`

Counter types include:
- RX bytes, RX packets, RX broadcast, RX multicast, RX dropped, RX CRC errors
- TX bytes, TX packets, TX collisions, TX deferred, TX excessive collisions
- Per-priority RX/TX (with PFC)
- Drop reasons (using the `rdbgc*_select` registers we documented)

For EdgeNOS, the bcm_stat_* API is what you'd call from `ethtool -S`
implementations.

---

## 8. KNET stubs — present but unused

10 functions found, all in the `FUN_103e6***` range (the bcm_* PLT
wrapper region):

```
bcm_knet_init, bcm_knet_cleanup
bcm_knet_netif_create / destroy / get / traverse
bcm_knet_filter_create / destroy / get / traverse
```

These are full implementations (each ~280-340 B wrapper around the
real impl). They CALL `linux-bcm-knet.ko` ioctls — but since Cumulus
doesn't load that module, none of these execute at runtime.

The compiled-in code suggests Cumulus 2.5 was *built with* KNET support
just-in-case. Operators who wanted KNET could `insmod linux-bcm-knet.ko`
and start using these APIs (though it's not the default architecture).

EdgeNOS could:
- Keep using TUN (Cumulus's choice)
- Pull in `linux-bcm-knet.ko` for higher pps
- Build something hybrid

---

## 9. PHY firmware loading — `phy-update` Python tool

The PHY firmware (`BCM84740-ver-D102.bin`, 32 KB 8051 binary) is **NOT**
loaded by `bcm_init`. It's loaded **later** by `/usr/lib/cumulus/phy-update`,
a Python tool that uses `bcmshell` (the bcmsh CLI client).

### The phy-update flow

```python
# Simplified pseudocode
sh = bcmshell.client()
for port_phyid in [9, 10, 11, ..., 8]:  # 32 ports per PHY group
    # Halt 8051
    sh.execute(f"phy raw {port_phyid} 0x1c.1c=0x0000")  # halt

    # Upload firmware byte-by-byte via MDIO ramcode interface
    for byte_idx in range(0, len(firmware)):
        sh.execute(f"phy raw {port_phyid} 0x1c.18=0x{firmware[byte_idx]:02x}")

    # Verify checksum
    sh.execute(f"phy raw {port_phyid} 0x1c.40")

    # Release reset → 8051 starts running
    sh.execute(f"phy raw {port_phyid} 0x1c.1c=0x0008")
```

The actual ramcode upload is via:
- Register `0x1c.0x18` = data byte
- Register `0x1c.0x1c` = control (halt/reset/run)
- Register `0x1c.0x40` = checksum readback

This happens **per PHY chip** (not per port). The BCM84740 is an
8-port PHY, so we have 8 chips on this 52-port switch (32 ports × 2
SFP cages each = wait, actually 48 × 1 = 48 ports + 4 QSFP).

Looking at the running chassis, `phy-update` runs from `/etc/rc.local`
or a systemd-equivalent right before switchd starts.

For EdgeNOS: implement this as part of `platform-init.sh`. We already
have the firmware file (`binaries/firmware/BCM84740-ver-D102.bin`).

---

## 10. Updated WHATS_MISSING.md status

Recompute coverage as of this commit:

### ✅ Fully covered (additions)
- SCHAN/CMICm/DMA protocol (`CMIC_SCHAN_DMA_DEEP_DIVE.md`)
- Access methods 5-layer model (`ACCESS_METHODS_DEFINITIVE_GUIDE.md`)
- DCB descriptor format
- bcm_init 42-block static call chain
- soc_init body + reset state machine
- 89 init-time registers identified
- End-to-end packet I/O flow (RX punt + TX inject)
- L3 route programming (this doc + L3_L2_PROGRAMMING_FLOW.md)
- L2 FDB programming
- L2 MAC learning via L2 MOD FIFO thread
- FP TCAM (entry/group/qualifier/action APIs)
- MMU buffer management (architecture + register categories)
- 62K field-name table at 0x11d332ec
- 36K register-name table at 0x11bc9344
- KNET stubs (confirmed unused, 10 stub functions)
- Linkscan thread (HW + SW modes)
- Mirror/SPAN API surface
- Storm control API
- Stats counter DMA architecture
- VLAN translation (architecture, mostly unused for basic forwarding)
- PHY firmware loader (phy-update Python flow)

### ⚠️ Partially covered
- **bcm_init's 42 block-inits**: top-level + biggest 3 (common/port/field)
  recursively traced 3 levels deep. The remaining 39 small block-inits
  not individually decompiled.
- **Per-port helpers**: FUN_105b98c4 (15K) + FUN_105b0980 (8.8K) etc.
  identified but not byte-for-byte decoded.

### ❌ Still not started (smaller items)
- `datapath-update` Python script (219 KB) — the rc.datapath_0 generator
- `clagd` binary (MLAG state machine, 92 KB)
- `mstpd` binary
- `ptmd` binary
- `cl-license` validation logic (the bytes that decide license valid)
- Individual PHY firmware functions (0xE301, 0xE2CD, 0xE3FD entry chain)
- `bcmsh` userspace CLI client internals
- Per-table entry bit layouts (DEFIP, L3_HOST, L2_TABLE — we have field
  names but not bit positions for every entry)

### What we cannot get without actual BCM SDK
Same as before:
- Per-register field bit positions (we have names via 0x11d332ec table
  but not per-field bit offset/width — those live in the per-reg `fields`
  array in the reg-info struct, which is heap-allocated at init time
  from data we don't have direct access to)
- The exact internal protocol between chip blocks (IPIPE→MMU→EPIPE
  metadata flow)

---

## 11. Files

- `ghidra-analysis/switchd_fp_mmu_decomp.c` — 15 functions decompiled (FP + MMU)
- `ghidra-analysis/switchd_l3l2_decomp.c` — 22 functions (L3 + L2)
- `ghidra-analysis/switchd_l3l2fp_hunt.txt` — 600-line function discovery
- `L3_L2_PROGRAMMING_FLOW.md` — L3 + L2 from netlink to tables

---

*Coverage of FP TCAM, MMU, VLAN xlate, Mirror, Storm, Linkscan, Stats,
KNET stubs, and PHY firmware loader. Closes the major remaining gaps
in WHATS_MISSING.md.*

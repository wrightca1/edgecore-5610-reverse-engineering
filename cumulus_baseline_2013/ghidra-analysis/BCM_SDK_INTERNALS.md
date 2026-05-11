# BCM SDK Internals — Worker Functions & Patterns

By following the call graph from 128 labeled BCM API functions, we found
348 reachable functions (depth ≤ 2). The most-called helpers reveal the
SDK's internal structure.

## The BCM API trampoline pattern

Every BCM API in switchd follows this structure:

```c
int bcm_xxx(unit, ...) {
    1. mutex_lock_timed(unit_mutex, timeout)   // FUN_11312da0
    2. port_validate(unit, port, &p)            // FUN_105a6a18 (port APIs only)
    3. result = do_actual_work(...)             // module-specific
    4. mutex_unlock(unit_mutex)                 // FUN_11312efc
    5. if (debug) api_trace_log(name, args, result)  // FUN_10461a0c
    return result;
}
```

## Top worker functions (most-called)

| Address | Callers | Size | Identified as | What it does |
|---|---|---|---|---|
| `FUN_10461a0c` | 78 | 748 | **API trace logger** | `"API: %s(...) -> %d %s\n"` — debug call trace |
| `FUN_112c5590` | 78 | 288 | API trace logger pair | helper for FUN_10461a0c |
| `FUN_10762108` | 79 | 152 | ⚠ mis-labeled as bcm_port_link_failed_clear | actually a generic init-state checker |
| `FUN_10761a94` | 52 | 220 | (unidentified, port-related) | probably bcm_port_init_get-equivalent |
| `FUN_105a6a18` | 43 | 284 | **BCM port-number validator** | decode encoded port → logical, validate |
| `FUN_11312da0` | 42 | 348 | **BCM mutex lock (timed)** | `sal/core/unix/sync.c:0x23c` |
| `FUN_11312efc` | 42 | 140 | **BCM mutex unlock** | paired with 11312da0 |
| `FUN_1038b364` | 34 | 80 | (small validator) | likely bcm_pbmp_valid or similar |
| `FUN_107a36e4` | 15 | 96 | (small helper) | |
| `FUN_1080290c` | 15 | 208 | (helper) | |
| `memset@113179b0` | 14 | 16 | libc memset | clear local stack buffers |

## Key code insight: BCM port-number encoding

`FUN_105a6a18` decompiles to:

```c
int bcm_port_translate(int unit, uint port, uint *out_port) {
    if (g_unit_initialized[unit] == 0) return -0x11;  // BCM_E_INIT
    
    // Bit pattern decode:
    if ((port >> 26) == 0 || (port >> 26) > 0x29) {
        // Standard logical port (0..0x81)
        if (port > 0x81 || g_port_table[unit][port + 0x1c84] == 0)
            return -0x12;  // BCM_E_PARAM
        *out_port = port;
    } else {
        // bits 26+ between 1 and 0x29: "encoded" port type
        // Translate via FUN_10619410 (hardware port-table)
        return FUN_10619410(unit, port, out_port);
    }
    return 0;
}
```

**Findings:**
* Port numbers are 32-bit but mostly use low 26 bits (logical port).
* Bits 26+ encode a "port type" (1..0x29 = 1..41) — front-panel,
  fabric, CMIC, mirror, etc.
* Logical ports go 0..0x81 (129 max — more than 52 because the chip
  supports more)
* Per-unit metadata array at `&DAT_1212d2dc` (indirected per unit),
  port table starts at offset `+ 0x1c84` from that base.

EdgeNOS should mirror this encoding for compatibility.

## SDK build environment confirmation

From `FUN_11312da0`'s assert path string:

```
/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/
  build/powerpc/bcm-sdk/src/sal/core/unix/sync.c
```

This proves Cumulus 2.5.0 switchd was built from Broadcom's source SDK
at `bcm-sdk/src/sal/core/unix/sync.c`. The full BCM SDK source tree is
NOT public, but OpenMDK contains the same SAL primitives.

## More BCM APIs discovered via call graph

The call graph also revealed BCM APIs we hadn't labeled (because their
error paths use a different log format than the standard CRIT log
pattern). Examples found:

```
bcm_eav_bandwidth_get / set
bcm_eav_pcp_mapping_get / set
bcm_eav_srp_mac_ethertype_get / set
bcm_l2_addr_delete
bcm_l2_conflict_get
bcm_l2_tunnel_add
bcm_mcast_addr_remove
bcm_mcast_bitmap_del / get / set / max_set
bcm_mim_init
bcm_mim_port_add / get_all
bcm_mirror_destination_destroy
bcm_mirror_egress_set
bcm_mirror_port_dest_add / delete
bcm_mirror_to_set / get
bcm_mirror_vlan_set
bcm_mpls_port_add / delete
bcm_mpls_port_get_all
bcm_mpls_tunnel_switch_add / delete
bcm_multicast_mim_encap_get
bcm_multicast_vpls_encap_get
bcm_port_ability_advert_get
bcm_port_ability_get
bcm_port_autoneg_get
bcm_port_discard_set / get
bcm_port_duplex_set
bcm_port_enable_set
bcm_port_encap_get
bcm_port_fault_get
bcm_port_info_get
bcm_port_loopback_set
bcm_port_pfm_set
bcm_port_phy_timesync_config_set
bcm_port_pfm_set
bcm_rate_bcast_port_set
bcm_rate_dlfbcast_port_set
bcm_rate_mcast_port_set
bcm_tr2_wlan_cli_client_print
bcm_wlan_client_add / get
```

So the **complete BCM SDK surface** switchd uses is ~150-200 APIs.

## False-positive warning

`bcm_port_link_failed_clear` at 0x10762108 is **wrongly labeled** — it's
called from `FUN_10461a0c` (the API trace logger) by 79 unrelated BCM
APIs. The actual function at that address is some internal check helper.
This is the limitation of the log-string-xref technique: when an API
uses the standard trace logger AND has a CRIT-log error, the heuristic
may pick the wrong `bl` target. ~10% of our 255 labels likely have this
issue.

The truly clean labels are the 127 with unique 1:1 mappings, where
exactly one BCM API name maps to exactly one address.

## Files

* `switchd_bcm_call_graph.txt` (15 KB) — full call graph stats
* `switchd_bcm_workers_decomp.c` (107 KB) — 60 most-called worker
  function decompilations

## Reproducing

```bash
$GHIDRA/support/analyzeHeadless \
    /home/smiley/analysis/build-server/switchd/ghidra-projects/ switchd \
    -process \
    -scriptPath ghidra-analysis/scripts \
    -postScript FollowBcmCallGraph.java
```

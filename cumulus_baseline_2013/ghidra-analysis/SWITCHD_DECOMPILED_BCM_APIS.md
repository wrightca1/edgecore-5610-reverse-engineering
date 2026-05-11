# Decompiled BCM SDK APIs from switchd

We used the CRIT log strings as a Rosetta Stone to identify and label BCM
SDK functions inside the stripped switchd binary, then decompiled them.

## Method

1. switchd's `.rodata` has ~365 CRIT log format strings of the pattern
   `"%s %s:%d CRIT bcm_<api_name> failed: %s\n"`.
2. For each string, find xrefs (where switchd loads its address into a
   register before calling log_crit).
3. Walk backward from the xref looking for the most recent `bl`
   (PowerPC branch-and-link = function call). That `bl`'s target is
   the BCM API.
4. Label the target with the API name.

## Results

* **365 BCM API strings examined**
* **255 labels applied** (some false-positives at common helpers like
  log_crit at 0x10047de0)
* **127 unique, high-confidence labels** (one API name → one address)
* **128 functions decompiled** (filtered for size 4 ≤ size ≤ 8192 bytes)

## Categories (decompiled output, by file)

| File | Size | Coverage |
|---|---|---|
| `switchd_bcm_decomp_port.c` | **161 KB** | All `bcm_port_*` APIs (the big one) |
| `switchd_bcm_decomp_encap.c` | 20 KB | wlan, mim (MAC-in-MAC), mpls |
| `switchd_bcm_decomp_other.c` | 12 KB | misc |
| `switchd_bcm_decomp_mirror.c` | 7 KB | mirror destination/port APIs |
| `switchd_bcm_decomp_l2_vlan.c` | 4 KB | vlan + l2 |
| `switchd_bcm_decomp_field_acl.c` | <1 KB | TCAM/FP entries |
| `switchd_bcm_decomp_l3.c` | <1 KB | route/host limited (mostly went to common helpers) |
| `switchd_bcm_decomp_rate_policer.c` | <1 KB | rate-limiting |
| `switchd_bcm_decomp_rxtx.c` | <1 KB | RX/TX init |
| `switchd_bcm_decomp_stats.c` | <1 KB | stat init / get |

## Example: `bcm_port_speed_get` decompiled

```c
int bcm_port_speed_get(int unit, uint port, int *speed_out) {
    int retval;
    int local_speed;

    if (g_unit_initialized[unit] == 0) {
        return -0x11;     // BCM_E_INIT
    }
    retval = FUN_105a6a18(unit, port, &local_speed);   // helper: read PHY
    if (retval >= 0) {
        ...
        *speed_out = ...;
    }
    return retval;
}
```

The Cumulus build of the BCM SDK uses standard error codes (`-0x11 = -17`
= `BCM_E_INIT`). Function bodies follow a consistent pattern:

1. Check init state
2. Call a worker function (still unnamed `FUN_xxxxxx`)
3. Translate result, populate output pointer

## High-confidence API → address map (selected)

From `switchd_bcm_api_resolved.txt`:

```
bcm_port_speed_get                      0x105c37e4
bcm_port_speed_max                      0x105c3dbc
bcm_port_autoneg_set                    0x105c3460
bcm_port_advert_set                     0x105cb05c
bcm_port_ability_advert_set             0x105cb5c8
bcm_port_duplex_get                     0x105c8de8
bcm_port_interface_get                  0x105c6e3c
bcm_port_stp_get                        0x105c186c
bcm_port_untagged_priority_set          0x105d053c
bcm_port_linkscan_set                   0x105c3048
bcm_port_pfm_get                        0x105d0298
bcm_port_medium_get                     0x105f0f6c
bcm_port_mdix_set                       0x105f023c
bcm_port_control_phy_timesync_get       0x10415890
bcm_port_phy_timesync_config_get        0x1041f484
bcm_esw_port_vlan_member_get            0x105ce0f0
bcm_mirror_mode_get                     0x10403b58
bcm_mirror_ingress_set                  0x10403910
bcm_mirror_port_dest_add                0x10403d88
bcm_mirror_egress_get                   0x10762a98
bcm_mim_vpn_get                         0x104025f0
bcm_mim_vpn_create                      0x1040229c
bcm_mim_vpn_destroy                     0x104023b4
bcm_mim_port_delete                     0x10401bd8
bcm_mim_detach                          0x104010b0
bcm_mpls_exp_map_destroy                0x10405bfc
bcm_mpls_exp_map_get                    0x10405d14
bcm_mpls_vpn_id_get                     0x10409d58
bcm_mpls_tunnel_initiator_clear         0x1040890c
bcm_multicast_mim_encap_get             0x1040ca24
bcm_wlan_init                           0x10459548
bcm_wlan_port_add                       0x10459658
bcm_wlan_port_delete                    0x10459870
bcm_wlan_port_delete_all                0x104599a0
bcm_wlan_client_traverse                0x10459318
bcm_wlan_detach                         0x10459438
bcm_field_entry_stat_attach             0x103abbf8
bcm_stat_attach                         0x103abd18
bcm_mcast_addr_remove                   0x103ffba0
bcm_policer_destroy_all                 0x104120f0
... (127 total)
```

The fact that port APIs cluster around `0x105cxxxx` and mirror/mim
around `0x1040xxxx` suggests the SDK is compiled per-module — each
file gets contiguous code. We can find more functions by exploring
those address ranges.

## Why this matters for EdgeNOS

EdgeNOS uses OpenMDK (a public subset of the BCM SDK). The full Cumulus
SDK above is a SUPERSET. From the decomp we can:

1. **Confirm exact function signatures** for OpenMDK-equivalent APIs.
2. **See what arguments are validated** (e.g., the `unit_initialized[unit]`
   check that returns `-0x11`).
3. **Trace down to the chip-register level** by following `FUN_xxxxxx`
   sub-calls deeper.
4. **Compare to EdgeNOS implementation** function-by-function.

## Reproducing

The scripts are in `scripts/`:
* `LabelBcmApiFunctions.java` — applies labels from log-string xrefs
* `DecompileBcmFuncs.java` — decompiles all labeled BCM functions

To run against the existing Ghidra project:
```bash
$GHIDRA/support/analyzeHeadless \
    /home/smiley/analysis/build-server/switchd/ghidra-projects/ switchd \
    -process \
    -scriptPath ghidra-analysis/scripts \
    -postScript LabelBcmApiFunctions.java \
    -postScript DecompileBcmFuncs.java
```

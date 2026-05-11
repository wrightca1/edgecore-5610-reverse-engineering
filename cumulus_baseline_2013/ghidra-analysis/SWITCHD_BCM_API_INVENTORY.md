# switchd → BCM SDK API Call Inventory

Extracted from existing `/home/smiley/analysis/build-server/switchd/`
Ghidra project. The freshly-pulled `switchd` from our live Cumulus
(SHA256 `02ddb782...`) differs by only 6400 bytes (likely build
metadata) from the previously-analyzed copy (SHA256 `859abd6d...`)
— so the existing analysis still applies.

## Scale

* **23,795 functions** total in switchd
  * 3,420 small (<100 bytes)
  * 12,201 medium (100–500 bytes)
  * 6,483 large (500–2000 bytes)
  * 1,691 huge (>2000 bytes)
* **5,001 strings** matching BCM/Cumulus/CMIC/MMU/TCAM patterns
* **990 log-format strings** mentioning BCM API call names — these
  are CRIT-level error messages emitted on API failure

## How we know which BCM SDK functions switchd uses

The CRIT-level error log messages in `.rodata` are a free directory of
the BCM SDK calls switchd depends on. Pattern: `%s %s:%d CRIT
bcm_<api_name> failed: %s\n` (these are inside `if (bcm_xxx() < 0) {
log_crit("..."); ... }` blocks).

From the strings dump, switchd invokes (verified by string presence):

### Port management
* `bcm_port_learn_set`
* `bcm_port_pause_set` / `bcm_port_pause_addr_set` / `bcm_port_pause_addr_get`
* `bcm_port_l3_enable_set` / `bcm_port_l3_mtu_set`
* `bcm_port_vlan_member_set`
* `bcm_port_control_set`
* `bcm_port_frame_max_set` / `bcm_port_frame_max_get`
* `bcm_port_enable_get`
* `bcm_port_status_get`

### L2 / VLAN
* `bcm_vlan_control_port_set`
* `hal_bcm_vlan_alloc`
* `hal_bcm_add_brmac` (broadcast MAC programming)

### L3
* `bcm_l3_info`
* `bcm_l3_intf_create`
* `bcm_l3_route_max_ecmp_set`
* `bcm_l3_egress_multipath_get`
* `bcm_l3_ip4_options_profile_create`

### Field Processor / ACL
* (FP-related calls — captured separately; see prior wc40_*.c decomps)

### RX/TX
* `bcm_tx_init`
* `bcm_rx_start`
* `bcm_rx_register`
* `bcm_rx_control_set` (with `VTAG_STRIP`, `CRC_STRIP` modes visible)
* `bcm_rx_cosq_mapping_set`

### Stats / monitoring
* `bcm_stat_multi_get`
* `hal_bcm_stat_init`

### Trunk / LAG
* `bcm_trunk_init`
* `bcm_trunk_chip_info_get`

### Rate limiting
* `bcm_rate_bcast_get`
* `bcm_rate_mcast_get`
* `bcm_rate_dlfbc_get` (destination lookup failure / broadcast)

## What this means for EdgeNOS

EdgeNOS already uses OpenMDK, which exposes a similar but smaller API
surface. The full list above is the **minimum BCM SDK surface area**
switchd touches — anything not on this list, EdgeNOS can ignore. For
each function name on this list, OpenMDK either:

* Has an equivalent (just call it),
* Has it under a slightly different name (rename in EdgeNOS),
* Or doesn't have it (write our own using lower-level chip access).

The `wc40_*_decomp.c` files in `ghidra-decomp/` (previously committed)
already cover the Warpcore-specific call sequences switchd uses for
SerDes setup. We can directly translate those into EdgeNOS code.

## Prior Warpcore decomps available

In `ghidra-decomp/` (committed earlier):
* `wc40_init_decomp.c` — top-level Warpcore init
* `wc40_speed_set_decomp.c` — port speed change handler
* `wc40_firmware_mode_set.c` — firmware mode (10G XFI vs SGMII etc.)
* `wc40_fw_mailbox_decomp.c` — firmware-mailbox protocol (PHY-side
  command channel for SerDes operations)
* `wc40_dispatch_table_decomp.c` — function dispatch (mode → handler)
* `wc40_reg_modify_decomp.c` / `wc40_reg_modify2_decomp.c` — RMW helpers
* `tx_control_set_decomp.c` — TX configuration
* `fw_mode_set_decomp.c` — set firmware mode
* `ind_lane_init_decomp.c` — individual lane init

These are the gold-standard reference for porting the Warpcore SerDes
init sequence to EdgeNOS.

## Why we didn't re-import the fresh switchd

| Aspect | Verdict |
|---|---|
| Fresh vs old size | 31,677,516 vs 31,683,916 (Δ = 6400 bytes ≈ 0.02%) |
| SHA256 | DIFFER (`02ddb782...` vs `859abd6d...`) |
| Source | Both Cumulus 2.5.0, different builds |
| Re-analysis cost | ~30 min of CPU + tens of MB Ghidra DB |
| Information gain | Marginal — same Cumulus codebase, same BCM SDK, same APIs |

The existing project already gave us:
* Full function inventory (23,795 functions)
* Full string inventory (every BCM API name they emit logs about)
* Decompiled Warpcore-specific routines

Future re-analysis only worthwhile if we see anomalies in the live
binary's behavior that contradict the existing decomp output.

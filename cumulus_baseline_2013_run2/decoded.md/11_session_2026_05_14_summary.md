# 2026-05-14 RE session summary — chip→CPU silent drop

Marathon investigation into why EdgeNOS's chip-side L3 forwarding to
CPU silently drops frames despite chip MAC accepting them.

## Setup

Hardware: AS5610-52X (BCM56846 / Trident+), connected to a Cisco
Nexus on:
 - `swp1` (chip phys 65) ↔ Nexus `eth1/33`, 10.101.101.0/29
 - `swp2` (chip phys 66) ↔ Nexus `eth1/34`, 10.101.101.8/29

Both for ECMP between EdgeNOS + Nexus.

## Real fixes that landed

| Symptom | Root cause | Fix |
|---|---|---|
| swp1 PCS `block_lock=0` | DS100DF410 retimer output muted | `pfd_prbs_dfe=0` + `adapt_eq_sm=64` + 20 ms CDR-reset settling per retimer.  Implemented in `config/rootfs/overlay/usr/sbin/platform-init.sh` sysfs pass. |
| BMD link state stuck DOWN despite PCS lock | Warpcore's MII_STATUS bit never asserts on SFP+ optical no-AN | `portmap_link_poll` reads `CL49_LSM.block_lock` and sets `BMD_PST_FORCE_LINK + LINK_UP`; bmd_link_update bypasses MII_STATUS. |
| chip-stats spam, swp2-only debug, XGS DMA flood | Dev-time `syslog`/`printf` calls left in production | Removed.  Per-packet hex dumps gone, chip-stat poll moved to 10 s + every port instead of swp2-only @ 200 ms. |
| Fan controller silently fighting itself (3 services, all broken) | Two services enabled (devmem + sysfs-broken), CPLD driver had two bugs | Consolidated to one `fan-controller.service` using sysfs.  CPLD driver: `.driver.groups → .driver.dev_groups` (was attaching attrs to driver kobj, segv'd on read), and `fan_pwm` accept range 0-31 (was 0-15). |

All pushed to `wrightca1/edgenos`.

## What DOESN'T work yet — the chip→CPU drop

After the above + ~80 individual rc.datapath_0 register writes
ported, end-to-end ping STILL fails:

 - chip MAC RX counter increments on swp1 (frames from Nexus arrive)
 - chip TX out swp1 works (Nexus has received 167K+ packets from us)
 - **CMICm DCB ring never fills** (interrupt count 0 forever,
   `handle_asic_rx` returns `CDK_E_TIMEOUT` on every poll)
 - **`swp1` Linux RX = 0**

I.e. frames hit the chip MAC but are silently dropped before the
CPU port enqueues them.  No `rx_drops` counter increments — it's a
forwarding-pipeline-stage drop with no easy-to-find counter.

## The systematic register-diff loop

To attack this I built `edged.c`'s one-shot regdump tool: if
`/tmp/regdump.in` exists, edged reads every register listed in
Cumulus's `dump_soc_diff.txt`, writes our chip's actual value to
`/tmp/regdump.out` in form

```
0x<addr> NAME.scope cum=0x<cum> ours=0x<our> [DIFF]
```

Snapshot after rounds 1-3 (`regdump_after_round3.out.gz` in
this directory): **3640 register diffs remaining** out of 4544
original.  Closed ~900 across:

 - OP_QUEUE_LIMIT_COLOR_CELL, OP_QUEUE_RESET_OFFSET_CELL (per-queue)
 - XLPORT_CONFIG (per-XLPORT)
 - OP_UC_PORT_LIMIT_COLOR_CELL, _RESUME_, _CONFIG1_CELL
 - XMAC_RX_CTRL, XMAC_CTRL, XMAC_RX_MAX_SIZE
 - MAC_0 / MAC_1 / XMAC_RX_MAC_SA / XMAC_TX_MAC_SA (chip per-port MAC)
 - STORM_CONTROL_METER_CONFIG
 - AUX_ARB_CONTROL_2, EGR_MTU, EGR_VLAN_CONTROL_1, COMMAND_CONFIG
 - PG_MIN_CELL, PG_SHARED_LIMIT_CELL, USE_SP_SHARED, OP_BUFFER_SHARED_LIMIT
 - ES_QUEUE_TO_PRIO, ESCONFIG, COSWEIGHTS, S3_CONFIG, S2_CONFIG
 - PORT_PG_SPID, COSMASK.COSMASKRXEN, ES_TDM_CONFIG, OVQ_FLOWCONTROL_THRESHOLD
 - PORT_MAX_PKT_SIZE, XMODID_DUAL_EN, OP_PORT_LIMIT_COLOR_CELL

## The wrapping discovery

Reading the 245 K-line `finish_*/a1_init_strace.log` revealed
Cumulus's switchd init recipe:

```
attach *
0:
init all                     ← THE MAGIC.  BCM SDK soc_init().
rcload /etc/bcm.d/rc.led
rcload /etc/bcm.d/rc.ports_0
setreg xmac_tx_ctrl 0xc802
s MAC_RSV_MASK MASK=0x18
m cmic_misc_control LINK40G_ENABLE=1
0: rcload /var/lib/cumulus/rc.datapath_0
setreg IFP_METER_PARITY_CONTROL 0
setreg rdbgc0_select 0x04000d11
... (the rest of rc.datapath_0)
```

**`init all` is the BCM SDK `soc_init` function** — proprietary C
code that programs hundreds of registers internally **before**
`rc.datapath_0` even runs.  Those `rcload` lines are *post-init
tuning*.  OpenMDK's `bmd_init` is a strict **subset** of `soc_init`.
**That's why our 80+ register writes haven't been enough — we've
been adding Cumulus's *post-init tuning* on top of an
*under-initialized* chip.**

The remaining 3640 register diffs are mostly what `init all`
programs and `bmd_init` skips.

## Other findings

### SDK configuration files we hadn't seen

`deep_mine_*/06_bcm_files/`:
 - `etc_bcm.d_config.d_02sdk.bcm` — `parity_enable=1`,
   `polled_irq_mode=0`, `bcm_stat_flags=0x1`, `l2xmsg_mode=1`,
   `miim_intr_enable=1`, `tdma_intr_enable=1`, `tslam_dma_enable=1`,
   `table_dma_enable=1`, `xgxs_lcpll_xtal_refclk=1`,
   `parity_enable=1` (← triggers init all's 103 `*_PARITY_CONTROL` writes).
 - `etc_bcm.d_config.d_11ports.bcm` — full portmap + per-port
   `port_init_speed_xeN=10000` + `port_init_autoneg_xeN=0`.

OpenMDK doesn't read these — uses hardcoded defaults.  May explain
some of the gap.

### Cumulus's `bmd_switching_init` is the canonical OpenMDK init

Tried disabling our service-VID-3301+ scheme and falling back to
OpenMDK's default (VLAN 1, CPU tagged, swpN untagged, STG-1
FORWARDING).  **Still no ping.**  So the bug is NOT in our
service-VID code; it's lower in the stack.

## Pickup options for next session

Memory's `project_init_all_insight_2026_05_14` has the writeup.
TL;DR:

1. Continue the regdump→port loop on the 3640 remaining diffs.
2. Port the 103 `*_PARITY_CONTROL` writes (likely triggered by
   `parity_enable=1` in 02sdk.bcm).
3. Diff our `bcm56840_a0_p2m` port map against Cumulus's
   `portmap_N.0` to verify alignment.
4. Static RE the 31 MB `switchd` binary with Ghidra to extract
   `soc_init`'s register-write sequence into our datapath code.
5. **Off the table**: running Cumulus's switchd binary on EdgeNOS
   (see `feedback_no_cumulus_switchd` memory).

## Artifacts

 - `regdump_after_round3.out.gz` — full register-by-register diff
   (3640 DIFF lines) between our chip and Cumulus, after all of
   tonight's writes
 - `cumulus_register_analysis.csv` — re-generated; "ported_by_us"
   column reflects all of tonight's commits
 - `scripts/regs_analysis.py` — re-run after edged changes to
   refresh "ported_by_us"
 - `scripts/mine_strace.py` — extract chip-config commands from
   Cumulus's bcmcmd-input strace

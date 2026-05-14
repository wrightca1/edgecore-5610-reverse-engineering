---
name: project_cumulus_chip_init_recipes
description: "Cumulus 2.5.0's actual chip-init recipes (rc.soc, config.bcm, rc.datapath) captured 2026-05-13 — the exact sequence/flags Cumulus uses to bring the BCM56846 up"
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# Files
All in `/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/deep_mine_20260513_191506/06_bcm_files/` (also `cumulus_baseline_2013/` partial copies):

| File | Lines | What |
|---|---|---|
| `etc_bcm.d_config.bcm` | 237 | **The chip-tuning config** — every chip flag Cumulus sets at startup |
| `etc_bcm.d_rc.soc` | 84 | **The init script** — bcmcmd commands to set up forwarding |
| `etc_bcm.d_datapath_rc.forwarding` | 107 | RTAG7 hashing + forwarding plane setup |
| `etc_bcm.d_config.d_01config.bcm`, `02sdk.bcm`, `10phy-ucode.bcm`, `11ports.bcm`, `12portwd.bcm` | various | Subsystem-specific config drop-ins |
| `etc_bcm.d_rc.led`, `rc.phy`, `rc.ports_0` | various | LED/PHY/port init recipes |

# Key chip-config flags (`config.bcm`)
```
polled_irq_mode=0                # Use real IRQs, not polling
miim_intr_enable=1               # MII via IRQ (we need this on AS5610)
tdma_intr_enable=1               # Table DMA via IRQ
tslam_intr_enable=1              # SLAM DMA via IRQ
tslam_dma_enable=1               # Enable SLAM DMA
table_dma_enable=1               # Enable Table DMA
l2xmsg_mode=1                    # L2 change notifs via FIFO (not poll)
parity_enable=1
xgxs_lcpll_xtal_refclk=1
phy_ext_rom_boot=0               # PHY ucode via MDIO (no ROM boot)
bcm_xlate_port_map.BCM56634=bcm56636_single_modid
bcm_xlate_sysport_enable.BCM56634=1
```

# Port map (physical port for each swpN)
```
portmap_1.0  = 65:10   # swp1 = chip port 65 @ 10G
portmap_2.0  = 66:10   # swp2 = chip port 66
portmap_3.0  = 67:10   # swp3 = chip port 67
portmap_4.0  = 68:10   ...
portmap_5.0  = 69:10
portmap_6.0  = 70:10
portmap_7.0  = 71:10
portmap_8.0  = 72:10
portmap_9.0  = 5:10    # swp9 onward = chip ports 5-...
...
```

**Confirms our EdgeNOS port assignment** — swp1→65, swp2→66 (which is what we already use).

# The init script (`rc.soc`) — what Cumulus's `bcmcmd rcload` runs at startup
```
init all                                # SDK init (everything)
rcload /etc/bcm.d/rc.ports_0            # Port enable
setreg xmac_tx_ctrl 0xc802              # XMAC TX control
s MAC_RSV_MASK MASK=0x18                # MAC reserved-bits mask
m cmic_misc_control LINK40G_ENABLE=1    # Enable 40G link mode for CMIC
0: rcload /var/lib/cumulus/rc.datapath_0  # Datapath init (auto-generated, big)
setreg IFP_METER_PARITY_CONTROL 0       # Workaround Trident FP_METER parity errata
# Drop-counter setup
setreg rdbgc0_select 0x04000d11
setreg rdbgc3_select 0x00000011
setreg rdbgc4_select 0x00000100
setreg rdbgc5_select 0x00002000
setreg rdbgc6_select 0x00008000
setreg tdbgc6_select 0x00040000
rcload /etc/bcm.d/rc.led                # LED init
```

# Implications for EdgeNOS
1. **We should mirror these config flags** in `edged/config.bcm` (or hardcode in `bmd_init`):
   - `parity_enable=1`
   - `tdma_intr_enable=1`, `table_dma_enable=1` (table DMA)
   - `miim_intr_enable=1` (MII interrupts)
2. **The init sequence** maps directly to BMD/CDK calls we already make (`bmd_init`, port-enable, datapath setup).
3. **One missing setting** worth investigating: `m cmic_misc_control LINK40G_ENABLE=1` — Cumulus enables this even though we're not doing 40G. Could affect CMICm DMA behavior.
4. **`l2xmsg_mode=1` (FIFO L2 changes)** — Cumulus uses the chip's L2 change FIFO instead of polling. We don't program this in EdgeNOS yet.

# DMA / interrupt finding
`config.bcm` clearly shows Cumulus runs in **interrupt-driven mode** (not polled). All the DMA flags say "use interrupts not poll". This matches what we found in [[project_cumulus_dma_decoded]] — switchd blocks on `LUBDE_WAIT_FOR_INTERRUPT (ioctl 9)`, not polling. EdgeNOS's `bmd_xgsd_dma_chan_poll` is the polling fallback — we should switch to interrupts.

# CMICm: ONLY CMC0 is used
The deep-mine register dump (`02_cmc_regs.txt`) confirmed: every `CMC1_*` and `CMC2_*` register reads as 0. **Only CMC0 is used.** This means EdgeNOS using `CMIC_CMC0_*` registers is correct.

Linked: [[project_cumulus_dma_decoded]] (DMA model), [[project_cumulus_route_storage_decoded]] (L3 table model), [[project_cumulus_full_capture_2026_05_13]] (capture inventory).

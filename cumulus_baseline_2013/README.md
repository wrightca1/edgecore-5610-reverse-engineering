# Cumulus Linux 2.5.0 Baseline Capture (clock-rolled to 2013)

> **For the documentation overview, see [`../DOCUMENTATION_INDEX.md`](../DOCUMENTATION_INDEX.md)**.
> This file documents the runtime capture itself; the analysis docs in
> this directory are listed below.

## 🔑 Key analysis docs in this directory (May 2026)

These build on the captures here to deliver a complete ASIC bring-up
understanding. Read in this order for EdgeNOS work:

| Doc | Topic |
|---|---|
| `ACCESS_METHODS_DEFINITIVE_GUIDE.md` | The 5-layer MMIO/SCHAN/PAXB stack |
| `CMIC_SCHAN_DMA_DEEP_DIVE.md` | SCHAN protocol + CMICm registers + DMA |
| `BCM_INIT_STATIC_CHAIN.md` | bcm_init 42-block dispatch order |
| `ASIC_INIT_COOKBOOK.md` | rc.soc / rc.datapath_0 / config.bcm decoded |
| `PACKET_FLOW_END_TO_END.md` | RX punt + TX inject end-to-end |
| `L3_L2_PROGRAMMING_FLOW.md` | netlink → switchd → BCM API → chip |
| `TABLE_ENTRY_HASH_OPS.md` | HASH_INSERT/LOOKUP/DELETE SCHAN opcodes |
| `FP_MMU_AND_REMAINING.md` | FP TCAM + MMU + VLAN + Mirror + others |
| `BCM_INIT_REGISTER_MAP.md` | 89 init-time registers identified |
| `WHATS_MISSING.md` | Gap analysis |
| `PROVEN_WORKING_CONFIG.md` | Known-good Cumulus 2.5.0 state |
| `fuse-explore/SWITCHD_SFS_INTERNALS.md` | switchd FUSE control plane |

## Why this exists

EdgeNOS, our custom NOS for the AS5610-52X, gets the BCM56846 partway up but
the front-panel SFP+ ports do not link. The retimer (DS100DF410) reports a
CDR not locked even though optical signal is present. To bisect "is this a
software bug or hardware bug," we re-installed the original Cumulus Linux
2.5.0 image (known to have worked on this hardware) and captured its
register/runtime state with the link UP. Future EdgeNOS regressions can be
diffed against these snapshots.

## Hardware under test

| Slot | Module | Linked? |
| --- | --- | --- |
| `swp1` (SFP+) | Finisar FTLX1475D3BTL-E7, 10G-LR, 1310nm SMF, S/N A0BAJGQ | ✅ 10G UP |
| `swp2` (SFP+) | Finisar FTLX1370W4BTL-E7, 10G-LR, 1310nm SMF, S/N PZG32P9 | ✅ 10G UP |
| `swp49` (QSFP+) | Cisco-Avago AFBR-79EBPZ-CS2, 40G QSFP-40G-SR-BD bidirectional | ❌ no carrier |
| `swp50` (QSFP+) | Cisco-Avago AFBR-79EBPZ-CS2, 40G QSFP-40G-SR-BD bidirectional | ❌ no carrier |
| `swp51` (QSFP+) | Cisco-Avago AFBR-79EBPZ-CS2, 40G QSFP-40G-SR-BD bidirectional | ❌ no carrier |
| `swp52` (QSFP+) | Cisco-Avago AFBR-79EBPZ-CS2, 40G QSFP-40G-SR-BD bidirectional | ❌ no carrier |

Per user, two of the QSFPs are loopbacked to each other; expected at least
one pair to link. They do not. Likely cause: Cumulus 2.5.0 leaves QSFPs in
LPMode (lower-page DOM is all `0x00`, suggesting modules are unpowered).
Vendor info IS readable from upper pages, so the I2C path works — only
LPMode/ModSel GPIO state needs flipping (probably via CPLD; out of scope
for this read-only capture).

* Edgecore AS5610-52X, accton_as5610_52x platform, S/N 561052X1916063
* BCM56846 Trident+ ASIC, Warpcore SerDes
* DS100DF410 4-channel retimer × **32 instances** (16 chips × Tx + Rx, or
  one full set per direction; each DS100DF410 has 4 lanes)
* P2020 PowerPC CPU, kernel 3.2.60-1+deb7u1+cl2.5
* Linux MAC for `eth0`: `80:a2:35:81:ca:ae`

## Reproducing the baseline

```bash
# 1) Install Cumulus 2.5.0 via ONIE - several busybox tools missing,
#    must symlink to /usr/bin: fdisk, mkfs.ext2, mkfs.vfat, blockdev,
#    sfdisk, fw_setenv (in /usr/sbin), reboot.

# 2) After first boot:
sudo service ntp stop
sudo service switchd stop

# 3) Install license + roll clock (license expires 2013-11-27):
sudo cp <license_file> /etc/cumulus/.license.txt
sudo date -s "2013-06-01 12:00:00"

# 4) Start switchd:
sudo service switchd start

# 5) Bring up the wanted ports:
sudo ip link set swp1 up
sudo ip link set swp2 up
```

## Files

| File | What it is |
| --- | --- |
| `cumulus_dump.sh` / `cumulus_dump2.sh` / `cumulus_retimer.sh` | The dump scripts — read-only. Reproduce the snapshot. |
| `00_*` / `01_*` / `02_*` / `03_*` | Initial probing of available diag tools |
| `10_phy_*.txt` | Per-port PHY identification (CL22 / CL45) |
| `20_phy_state.txt` | Initial PHY register sample |
| `30_full_dump.txt` | **Full comprehensive dump (1163 lines)** — primary baseline |
| `40_unlinked_port_baseline.txt` | xe2/xe4 (no SFP, admin down) reference values |
| `50_phase2_dump.txt` | **Phase-2 deep dump (1764 lines)** — adds QSFP, swp10, lspci, dmesg, etc. |
| `60_retimer_state.txt` | First retimer probe (i2cget direct — failed because driver-owned) |
| `70_retimer_full.txt` | **Per-retimer sysfs state for all 32 instances** |
| `80_link_recheck.txt` | Late link-state check |
| `81_qsfp_link_watch.txt` | QSFP bounce + 30s wait |
| `82_qsfp_dom_raw.txt` / `83_qsfp_eeprom_full.txt` | Raw QSFP EEPROM bytes |
| `85_sfp_dom_cumulus.txt` | `cl-sfputil -d` output for swp1/2/49–52 |

## Key findings

### 1. SerDes drive settings (10G XFI vs 40G KR4)

| Port type | BCM port | Preemphasis | DriverCurrent | PreDriverCurrent |
| --- | --- | --- | --- | --- |
| 10G XFI (SFP+) | xe0–xe47 | `0xa370` | `0x2` | `0x3` |
| 40G KR4 (QSFP+) | xe48–xe51 | `0xe270` | `0x4` | `0x4` |

Same values appear on linked AND unlinked ports of the same type, so these
are firmware defaults, not the missing config. The relevant difference for
EdgeNOS is the per-port-type selection.

### 2. Port → BCM → Warpcore mapping

* `swp1` → `xe0` → Warpcore B0/16/0 (PHY MDIO addr `0xd1`)
* `swp2` → `xe1` → Warpcore B0/16/1 (PHY MDIO addr `0xd1`)
* `swp48` → `xe47` → Warpcore B0/03/3
* QSFP `swp49` → `xe48` → Warpcore B0/12/4 (PHY addr `0xc1`)
* QSFP `swp50` → `xe49` → Warpcore B0/11/4 (PHY addr `0xb5`)
* QSFP `swp51` → `xe50` → Warpcore B0/15/4 (PHY addr `0xcd`)
* QSFP `swp52` → `xe51` → Warpcore B0/14/4

Each block of 4 SFP+ ports shares one PHY address; QSFP uses lane 4 in
selected blocks. Full mapping in `30_full_dump.txt` under "phy info".

### 3. DS100DF410 retimer state (linked, working)

There are **32 retimer chips** at I2C address `0x27` on logical buses
18–69 (sub-bus on the second-tier mux). Each chip is the standard
DS100DF410 4-lane retimer.

All retimers report nearly identical sysfs state when linked:

| Attribute | Value | Meaning |
| --- | --- | --- |
| `adapt_eq_sm` | 32 | adaptive-EQ state machine |
| `cdr_rst` | 16 | last CDR reset value |
| `channels` | 165 | per-chip channel mask |
| `drv_sel_vod` | 128 | driver/output VOD select |
| `pfd_prbs_dfe` | 233 | PFD/PRBS/DFE config |
| `tap_dem` | 16 OR 23 (see below) | DFE tap (de-emphasis?) |
| `veo_clk_cdr_cap` | 1 | VEO clock CDR capture flag |

`tap_dem` splits into two clusters:

* `tap_dem = 23`: buses **18, 19, 20, 21, 40, 66, 67, 68, 69** (9 chips)
* `tap_dem = 16`: all other 23 chips

Buses 18–21 form a contiguous group of 4 (one DS100DF410 per QSFP lane,
likely the QSFP-side retimers for ports 49–52). Buses 66–69 also contiguous
(probably another QSFP). The standalone bus-40 chip is unexplained; possibly
an EEPROM I2C arbitration anomaly.

### 4. Retimer kernel driver attributes — these are the hooks for control

The Cumulus kernel ships a `ds100df410` driver that exposes per-chip:

```
adapt_eq_sm  cdr_rst  channels  drv_sel_vod
pfd_prbs_dfe  tap_dem  veo_clk_cdr_cap  retimer_dev
```

Per memory `feedback_miim_safety.md` / `project_cdr_reset_breakthrough.md`,
**writing to `cdr_rst` is the breakthrough that made our EdgeNOS port pass
signal**. EdgeNOS should use the same driver attributes (or the equivalent
register sequence — TI's CDR reset is reg 0x0a bit 2) at the right point in
port-up.

### 5. PHY register sample, xe0 link UP (CL22)

```
xe0 reg 0x00 = 0x0000   (Control)
xe0 reg 0x01 = 0x0000   (Status)
xe0 reg 0x04 = 0x00a0   (ANEG advertisement)
xe0 reg 0x06 = 0x0004
xe0 reg 0x07 = 0x2001
```

(Full dumps in `30_full_dump.txt`.)

### 6. ports.conf / switchd.conf

Default factory config: 48 SFP+ as 10G + 4 QSFP as 40G. No 4×10G break-out
applied. `/etc/cumulus/switchd.conf` is largely defaulted.

### 7. SFP+ module DOM (linked ports)

* `swp1`: TX bias alarms ON (not concerning — power readings are gated
  alarms, not absolute values, in this output mode)
* `swp2`: same pattern, RXPower OK (on)

Both modules are 10G-LR class single-mode 1310nm, factory date 2018.

### 8. QSFP+ EEPROM upper page is readable, lower (DOM) is zeros

The Cisco AFBR-79EBPZ-CS2 modules respond on I2C, vendor/serial readable.
But bytes 0–127 (lower memory page 0, which holds DOM in QSFP / SFF-8436)
are all `0x00` except the identifier byte. Module is in LPMode — DOM
monitoring isn't being updated. Cumulus 2.5.0 leaves QSFPs in LPMode by
default; nothing is reading them or writing the LPMode pin.

### 9. Do we need anything special for 40G QSFP in Cumulus?

`/etc/cumulus/ports.conf`:

```
49=40G
50=40G
51=40G
52=40G
```

That syntax is correct (alternative would be `49=4x10G` to split into four
10G break-outs).

But on this platform, Cumulus 2.5.0 alone is **not** sufficient to bring up
40G QSFP+ optical modules:

* Switchd configures the BCM port (xe48–xe51 show `KR4` and `Forward`).
* The QSFP module identifier (byte 0 of the EEPROM = `0x0d`) is read.
* LPMode and ResetL GPIOs are driven by the platform CPLD on AS5610-52X.
* Cumulus 2.5.0's `accton_as5610_52x` platform package does **not** appear
  to flip those GPIOs when the port goes admin-up (DOM page stays at zero).
* Without deasserting LPMode, the laser/CDR inside the QSFP never powers
  up, so even loopbacked pairs cannot link.

What would actually bring the QSFPs up:

1. CPLD GPIO write to clear LPMode + assert ResetL deassert for each QSFP
   slot. The CPLD register layout is per `I2C_BUS_TOPOLOGY_AND_SFP_CONTROL.md`
   and `feedback_cpld_addr_wrap.md` (CPLD wraps at 32 bytes).
2. After ~100ms, re-read DOM to confirm the module is alive.
3. If still no link with both ends loopbacked, check ResetL polarity and
   ModSel handling.

For EdgeNOS this is the right place to add an explicit "QSFP power-up"
sequence in the per-port enable path. The breakthrough we already have for
SFP+ retimer CDR reset (`project_cdr_reset_breakthrough.md`) does not
substitute — that's a retimer-side action, while LPMode/ResetL is a
module-side power-control issue handled via CPLD.

## Next steps for EdgeNOS debugging

1. **Diff EdgeNOS retimer state vs this baseline.** Specifically check
   that all 32 retimer chips end up at `adapt_eq_sm=32`, `pfd_prbs_dfe=233`,
   `drv_sel_vod=128`, `veo_clk_cdr_cap=1`. If EdgeNOS leaves any of these at
   chip-reset values, the link won't come up.
2. **Use the kernel driver model in EdgeNOS.** Cumulus's `ds100df410.ko`
   is a much cleaner abstraction than poking the I2C registers directly;
   we should port that pattern.
3. **MIIM trace during port-up.** Capture Cumulus's MIIM transactions when
   `swp1` goes from disabled to up using GDB passive capture per
   `feedback_miim_safety.md`. Compare against `traces/cumulus_port_up_miim_capture.txt`
   to confirm the trace is still representative.
4. **For QSFP link bring-up later**: figure out the LPMode-deassertion path
   (probably a CPLD GPIO write, but read-only on Cumulus per
   `feedback_readonly_cumulus.md`).

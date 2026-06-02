# 40G QSFP Enablement Plan (SR4 fiber) — AS5610-52X

Status: **scoped, not yet implemented.** The four QSFP cages (swp49–52) all have
modules; **two are connected by fiber** (the loopback pair). They do **not** link
or pass traffic today. This is the spec to enable them.

Already correct (don't re-do):
- Lane map matches Cumulus: `swp49=49, swp50=45, swp51=61, swp52=57`.
- `CMIC_MISC_CONTROL.LINK40G_ENABLE=1` is set (`datapath.c`).
- Ports configured as `bmdPortMode40000fd` (40G); TUNs `swp49–52` exist.

## Three gaps to close

### 1. 40G-SR4 (optical) PHY firmware mode  ← most fundamental
`bcmi_warpcore_xgxs_drv.c` `speed_set()` 40G branch only handles
`PHY_IF_KR → KR4 (fw_mode=0x3333)`, `PHY_IF_CR → CR4`, else **defaults to KR4**.
There is **no SR4/optical case**, so a fiber QSFP gets KR4 (copper DAC) RX
adaptation → won't lock.
- The SDK *does* define the mode: OpenBCM `_SHR_PORT_PHY_FIRMWARE_SFP_OPT_SR4`
  ("optical short range") vs `_SHR_PORT_PHY_FIRMWARE_SFP_DAC`.
- **TODO:** add an SR4/optical path: set `PHY_CTRL_LINE_INTF`/a fiber flag for
  QSFP-with-fiber, and program the optical per-lane `fw_mode` nibble (the
  `SFP_OPT_SR4` ucode value — confirm from the full SDK wc40 firmware-mode-set;
  OpenMDK driver currently uses nibble 2=10G-DAC, 3=40G-KR4). Optical mode
  disables/changes the DFE that KR4 assumes for copper.

### 2. QSFP optic I2C path is broken
Reading bus 66–69 @ 0x50 (the `port_to_i2c_bus` mapping) returns `id=0x03`
(SFP, not QSFP `0x0C/0D/11`), vendor bytes `0x00`, **identical on all 4 buses** →
not reaching the real QSFP EEPROMs. `i2cdetect` shows nothing at 0x50.
- **TODO:** find the correct QSFP I2C topology (mux channel select / page select;
  QSFP SFF-8636 uses upper-page paging). Needed to (a) detect which 2 cages have
  fiber, (b) manage optic power (SFF-8636 byte 93) + `TX_DISABLE` (byte 86), and
  (c) deassert **LPMODE** so the optic runs full power for 40G.

### 3. CL82 multi-lane link detection
edged's `pcs_block_lock_get()` reads CL49 (single-lane, 0x8360 reg 0x17). 40G
uses **CL82** (MLD/BAM): per-lane block_lock **plus** alignment-marker lock across
4 lanes. The single-lane check never asserts for 40G → edged treats QSFPs as down
→ flood-TX → no egress. (Confirmed: forcing link-up + directed TX still didn't
pass traffic — so link detection alone isn't enough; #1/#2 must be fixed too.)
- **TODO:** add a 40G link read (CL82 AM-lock / `pcs_block_lock` aggregate across
  the 4 lanes) for QSFP ports in `portmap_link_poll`.

## Suggested order
1. Fix the QSFP I2C path (#2) → confirm the 2 fibered cages + read optic type/power.
2. Add the SR4 optical firmware mode (#1) → the link should establish at L1.
3. Add CL82 link detection (#3) → edged marks them up → directed TX/RX works.
4. Test the 2-fiber loopback (frame out one, punt to CPU on the other), like the
   working swp47↔swp48 SFP+ loopback.

## Note
The 10G datapath (Nexus ping, swp47↔swp48 loopback) is fully working and
committed. 40G QSFP is independent of it; this is a focused add-on effort.

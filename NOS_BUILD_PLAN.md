# AS4610-54T — NOS Build Plan & Gap Analysis

How to get our own NOS running on the 4610-54T, given what already exists.

---

## The strategic difference from the 5610

The 5610 required a from-scratch reverse-engineering of a proprietary `switchd`
and the PCIe→PAXB→CMICm→SCHAN access stack because no open NOS supported the
board cleanly. **The 4610 needs none of that:**

- ONL already supports the board end-to-end (DTS, kernel, ONLP platform layer).
- OpenMDK already has a native `bcm56340_a0` data-plane driver.
- The CPU-on-die (iProc) design eliminates the PAXB sub-window problem entirely.

So the question isn't "can we figure out the hardware" — it's "which NOS posture
do we want." Three options, in increasing order of effort:

### Option A — Build ONL and run it (fastest, recommended first step)
Build the in-tree `as4610-54` ONL image and install via ONIE. Gets us a booting
Linux with working sensors/optics/LEDs/fans and an ONLP CLI. Data-plane
forwarding then comes from whatever switch agent we layer on (OpenMDK demo,
ofdpa/indigo if present, or our own thin agent on OpenMDK). **Validates the
whole platform with near-zero new code.**

### Option B — Thin custom NOS on OpenMDK (the "EdgeNOS for 4610") — L2 switch
Mirror the 5610 EdgeNOS goal but on a vastly easier base: a small userspace
daemon that drives the OpenMDK `bcm56340_a0` BMD for init + port bring-up +
**L2/VLAN/STP/MAC + TX/RX**, on top of the ONL kernel + platform drivers. This
is the direct analogue of our 5610 `newnos/`, but we **start from a working chip
driver** instead of writing SCHAN by hand.
**Limit:** the BMD is L2-only — it gets you a working VLAN **switch**, not a
router (see "Switch vs router" below).

### Option C — L3 / routing (full SDK or hand-programmed tables)
Required to be a **router** (which is the box's intended role — datasheet says
L2 **or L3** forwarding). The BMD has no L3 API at all. Two routes:
- **OpenBCM 6.5.27 full SDK** — real L3 (route/ECMP/L3-intf programming of
  `L3_DEFIP`/`L3_ENTRY`/`EGR_L3_*`). **Helix4 is first-class here** (verified:
  `src/soc/esw/helix4.c` 5.6k lines, `BCM_56340_A0`→`BCM_HELIX4_SUPPORT`,
  `CONFIG_BCM56340` field defs). The chip-generic `bcm_l3_*` API dispatches
  through `helix4.c`. Likely-easiest path to a working router.
- **Hand-program Helix4 L3 memories via SCHAN** — the exact table technique the
  5610 project already proved (`L3_NEXTHOP_FORMAT`, HASH_INSERT). **Now easy:**
  OpenMDK's CDK already gives every Helix4 L3 table's exact field bit layout
  (`bcm56340_a0_defs.h`, e.g. `EGR_L3_INTFm_MAC_ADDRESSf` = bits 34..81) **and**
  the access engine (`cdk/PKG/arch/xgsm/xgsm_mem_write`). So this is table-fill
  code with provided macros, **not** reverse engineering — unlike the 5610 where
  we had to derive those layouts by hand. See `EXISTING_SOFTWARE_ASSETS.md` §
  "Layer 1 — CDK".

> Recommendation: **A → B → C.** Get ONL booting and the platform proven, stand
> up an L2 switch on the BMD, then add L3 last (the only genuinely hard piece).

---

## Switch vs router — capability of what we have

| Capability | Have it? | Source |
|---|---|---|
| Port bring-up incl. **10G SFP+ (XFI/SFI)** + **20/40G QSFP+** uplinks | **Yes** | BMD `port_mode_set`, `warpcore_phy_init`, `tdm_default` |
| L2 switching (VLAN, STP, MAC, flood/learn) | **Yes** | BMD `bmd_vlan_*`, `bmd_port_stp_*`, `bmd_*_mac_addr_*` |
| Packet TX/RX to CPU | **Yes** | BMD `bmd_tx`, `bmd_rx_*` (XGS-M DMA) |
| Stats / counters | **Yes** | BMD `bmd_stat_*` |
| **L3 routing (IPv4/IPv6, ECMP, L3 intf)** | Not in BMD; **yes in OpenBCM** | `helix4.c` / `bcm_l3_*` (Option C) |
| ACL / QoS / advanced | yes in OpenBCM | OpenBCM only |

**Bottom line:** with on-disk assets the 4610 becomes a fully working **L2
switch with live 10G uplinks**. Making it a **router** is the one real chunk of
remaining work, and it's table-programming (Option C), not hardware RE.

---

## Work breakdown

### Phase 0 — Inventory & bench bring-up
- [ ] Get the physical unit; serial console (`ttyS0`, 115200 8N1).
- [ ] Confirm ONIE boots; capture board EEPROM TLV + `onie machine.conf`.
- [ ] PCB inspection → component map (mirror `AS5610_52X_BOARD_COMPONENT_MAP.md`).
- [ ] Dump CPLD register map from live unit; cross-check `accton_as4610_cpld.c`.

### Phase 1 — ONL image (Option A)
- [ ] Build armhf ONL for `as4610-54-r0` from the in-tree platform package.
- [ ] ONIE-install to `/dev/sda`; verify boot, console, mgmt port (gmac0/SGMII).
- [ ] Verify ONLP: `onlpdump` — PSU, fans, thermals (LM77), SFP/QSFP presence.
- [ ] Confirm optics EEPROM reads (optoe1/optoe2) on ports 49–54.

### Phase 2 — Data plane up (Option A/B boundary)
- [ ] Bring up OpenMDK on the box; `bmd_attach` the BCM56340_a0.
- [ ] Run chip init (`bcm56340_a0_bmd_init` + `_switching_init`); confirm via
      register reads (no PAXB step — direct CMICd MMIO).
- [ ] Bring a 1G copper port to link; verify integrated-PHY autoneg.
- [ ] L2 learn + forward between two front ports (basic switching).
- [ ] RX-to-CPU / TX-from-CPU punt path via BMD `rx`/`tx` (validate XGS-M DCB).

### Phase 3 — Thin L2 NOS (Option B)
- [ ] Daemon skeleton: init → port config → L2/VLAN/STP/MAC.
- [ ] Wire ONLP platform events (link/SFP insert) to the agent.
- [ ] Bring up **10G SFP+ uplinks (ports 49–52)** and QSFP+ (53–54) — BMD
      `port_mode_set` XFI/SFI / 20–40G; confirm link + traffic.
- [ ] End state: working VLAN switch with live 1G access + 10G uplinks.

### Phase 4 — L3 routing (Option C) — the one hard part
- [ ] Decide path: OpenBCM full SDK vs hand-programmed Helix4 L3 memories.
- [ ] Re-derive Helix4 `L3_DEFIP` / `L3_ENTRY` / `EGR_L3_*` layouts from CDK
      `bcm56340_a0_defs.h` (do **not** reuse 5610 Trident+ values).
- [ ] Program an L3 interface + a static route; ping through the box (router).
- [ ] ECMP + IPv6 as follow-on.

---

## Gap analysis vs the 5610 project

| Problem that dominated the 5610 | Status on the 4610 |
|---|---|
| PCIe BAR0 + PAXB sub-window remap | **Gone** — CPU on-die, direct CMICd MMIO |
| Reverse-engineer SCHAN / proprietary switchd | **Not needed** — OpenMDK BMD exists |
| Chip table layouts unknown (mined via bcmcmd) | **Provided** — CDK `bcm56340_a0_defs.h` |
| Warpcore SerDes + DS100DF410 retimer unmute | **Gone** — integrated copper PHYs, no retimers |
| 6-layer I²C mux tree | **Trivial** — single PCA9548 |
| CPLD RE (memory-mapped, undocumented) | ONL driver exists (`accton_as4610_cpld.c`); just dump to confirm |
| RX DMA / CMICm completion bug | Re-verify XGS-M DCB on this stepping (partial carryover) |
| Cumulus baseline to diff against | Need an **ARM Cumulus 2.5.4+/3.x** image (not on disk) |

### Genuinely new/open items for the 4610
1. **Confirm OpenMDK builds + runs against the ONL iProc 4.14 kernel** (BDE/CMICd
   kernel module integration on this kernel).
2. **XGS-M DCB / RX-completion specifics** for the BCM56340 stepping.
3. **Integrated 1G copper PHY bring-up** (autoneg/EEE) — different from 5610's
   10G SFP path; check BMD `port_mode` + `download` (PHY fw) handling.
4. **Acquire an ARM Cumulus image** if we want a reference data plane to diff.

---

## Next concrete action

Get the unit on a bench with serial, then **Phase 1**: build and ONIE-install
the in-tree `as4610-54` ONL image. That single step validates ~80% of the
platform with code we already have.

# AS4610-54T — Existing Software Assets

What we already have on disk that targets this board. The headline: **almost
the entire stack already exists** — we are integrating, not reverse-engineering.

---

## 1. Open Network Linux — full platform support (armhf)

`OpenNetworkLinux/packages/platforms/accton/`

| Path | Contents |
|---|---|
| `armhf/as4610/as4610-54/` | ONLP package, platform-config (r0), modules build for the 54-port |
| `armhf/as4610/as4610-30/` | 24-port sibling |
| `armel/as4610/...` | armel variants |
| `armxx/arm-accton-as4610/` | **shared platform code** (DTS + kernel modules + ONLP drivers) |

Shared platform code (`armxx/arm-accton-as4610/`):

- **Device tree:** `arm-accton-as4610.dts` (+ `dts/bcm-helix4.dtsi` base)
- **Kernel modules:** `accton_as4610_cpld.c`, `accton_as4610_fan.c`,
  `accton_as4610_leds.c`, `accton_as4610_psu.c`
- **ONLP drivers** (`arm_accton_as4610/module/src/`): `sysi.c`, `sfpi.c`,
  `psui.c`, `fani.c`, `thermali.c`, `ledi.c`, `platform_lib.c`, `ucli.c`

ONLP platform string: **`arm-accton-as4610`**, IDs `..._AS4610_54_R0` /
`..._AS4610_30_R0`. Kernel: **armhf iProc 4.14**. Boots from `/dev/sda` (USB),
U-Boot env on `/dev/mtd2`.

> This means a buildable ONL image for the 4610-54 is essentially already in the
> tree. The platform layer (sensors, optics, LEDs, fans, EEPROM, ONIE TLV) is
> done.

## 2. OpenMDK — data-plane SDK with native BCM56340 support

> **Key insight:** OpenMDK is *layered*. The bottom layer (CDK) **is the
> silicon, as source** — the complete register/memory/field map for the
> BCM56340. The "minimal" in BMD refers only to the **driver API surface** (it
> happens to expose L2 ops), **not** to chip coverage. So the so-called "L3 gap"
> is *not* a silicon-knowledge gap: we have every L3 table's exact bit layout.
> This is precisely the data we reverse-engineered by hand on the 5610
> (`L2_ENTRY_FORMAT`, `L3_NEXTHOP_FORMAT`, `VLAN_TABLE_FORMAT`) — here it's
> simply given to us.

### Layer 1 — CDK: the chip definition (`cdk/PKG/chip/bcm56340/`)

**~25 MB, ~504K lines of source for this one chip:**

| File | Size | Contents |
|---|---|---|
| `bcm56340_a0_defs.h` | 248,528 lines | **2,301 registers** + field-level GET/SET macros with **exact bit positions** |
| `bcm56340_a0_sym.c` | 140,351 lines | **8,108 symbols** — runtime table of every reg/memory + fields |
| `bcm56340_a0_cmic.h` | 104,773 lines | CMIC management-interface register defs |
| `bcm56340_a0_enum.h` | 10,057 lines | **5,013 enumerated** registers/memories |
| `bcm56340_a0_chip.c` / `_sym.c` | — | chip descriptor + symbol wiring |

L3 tables are fully defined with bit encodings — e.g. straight from `defs.h`:

```c
EGR_L3_INTFm_MAC_ADDRESSf    → bits 34..81   (router source MAC)
EGR_L3_INTFm_TTL_THRESHOLDf  → bits 26..33
EGR_PORT_TO_NHI_MAPPINGr_NEXT_HOP_INDEXf → 14-bit, mask 0x3fff
```

Present (with layouts): `L3_DEFIP`, `L3_ENTRY*`, `EGR_L3_NEXT_HOP`,
`ING_L3_NEXT_HOP`, `EGR_L3_INTF`, `FP_POLICY_TABLE`, VLAN/EGR_VLAN, etc.
**Use these Helix4 values — not the 5610 Trident+ ones.**

### Layer 2 — xgsm access engine (`cdk/PKG/arch/xgsm/`)

The CMIC/SCHAN/DMA plumbing as source: `xgsm_mem_read/write/clear`,
`xgsm_block_*` addressing, `xgsm_chip.c`. This is the 5610's painstakingly
reverse-engineered "5-layer access stack" — handed to us. (Arch is **XGS-M**, the
same CMICm/DMA family our 5610 work migrated toward, so
`project_dcb_format_decoded` / `project_cmicm_rx_completion_decoded` partially
transfer — verify DCB specifics for this stepping.)

### Layer 3 — libbde (`libbde/`)

Bus/DMA enumeration (PCI/iProc probe + mmap) — the user/kernel BDE shim.

### Layer 4 — PHY + SerDes firmware (`phy/PKG/chip/`)

SerDes drivers **plus microcode as C source**: `bcmi_warpcore_xgxs_ucode*.c`
(~4,865 lines) for the 10G uplinks, internal SerDes (`combo`/`tsce`/etc.) for the
1G ports, and external-PHY ucode (`bcm84xxx_ucode.c`). The usual "binary blob"
problem is source-available here.

### Layer 5 — BMD: the driver (`bmd/PKG/chip/bcm56340_a0/`)

A **complete BMD chip package** for our exact ASIC (`SUPPORTED_CHIPS.md`: *Helix —
BCM56300–BCM56344 … BMD: BCM56340_A0*). `bmd_init.c` is a real 2,188-line init
sequence. The public API:

| Capability | File |
|---|---|
| Chip attach/detach/reset | `..._bmd_attach.c`, `..._bmd_detach.c`, `..._bmd_reset.c` |
| Init + switching init | `..._bmd_init.c`, `..._bmd_switching_init.c` |
| Port mode get/set/update (incl. 10G XFI/SFI) | `..._bmd_port_mode_*.c` |
| VLAN create/destroy/port | `..._bmd_vlan_*.c` |
| STP state | `..._bmd_port_stp_*.c` |
| L2 / CPU MAC add/remove | `..._bmd_*_mac_addr_*.c` |
| RX/TX + polling | `..._bmd_rx*.c`, `..._bmd_tx.c` |
| Stats | `..._bmd_stat_*.c` |
| PHY firmware download | `..._bmd_download.c` |

**L2-only API** — no `bmd_l3_route_add`. But given Layers 1+2 (full L3 defs +
access engine) and the SCHAN table technique already proven on the 5610, adding
L3 is **straightforward table-fill code** (`EGR_L3_INTFm_*_SET(...)` →
`xgsm_mem_write`), *not* reverse engineering.

## 3. OpenBCM (full SDK 6.5.27) — **first-class Helix4 + full L3**

`OpenBCM/sdk-6.5.27/` — the full Broadcom SDK, and it **does support our exact
chip as a first-class part** (verified, not a stub):

| Evidence | Detail |
|---|---|
| Chip SOC driver | `src/soc/esw/helix4.c` (**5,648 lines**) + `include/soc/helix4.h` |
| Chip variant | `BCM_56340_A0` in `include/soc/defs.h` → auto-enables `BCM_HELIX4_SUPPORT` (+ shared Trident/Triumph3 codepaths Helix4 reuses) |
| Register/field defs | `include/soc/mcm/allfields.h`, gated by `CONFIG_BCM56340` / `CONFIG_OTP_BCM56340` |
| L3 in chip driver | 122 L3/LPM/route/nexthop/ECMP refs in `helix4.c` |
| L3/LPM build gate | `BCM_HELIX4_SUPPORT` gates `lpm.h`, `mem.c`, `drv.c`, `ism.c`, … |

So OpenBCM gives the **full L3 control plane** for the 4610: `bcm_l3_route_add`,
host/next-hop/ECMP/L3-interface programming, ACL, QoS, cosq — the chip-generic
BCM API dispatches through `helix4.c`. This is the path to make the box the
**router** its datasheet advertises.

**Posture:** OpenMDK = fast L2 bring-up; **OpenBCM = the real L2+L3 data plane.**

## 4. Reference NOS images (Cumulus)

The `*.bin` Cumulus images in the repo root are **PowerPC/amd64** and predate
4610 support (added in Cumulus 2.5.4, ARM). If we want a known-good binary to
diff against (like the 5610 Cumulus 2.5 baseline), we'd need a **Cumulus 2.5.4+
or 3.x ARM** image — not currently on disk.

## 5. 5610 reverse-engineering corpus (conceptual reference only)

`edgecore-5610-reverse-engineering/` — SCHAN opcodes, StrataXGS table concepts,
SDK call structure, CMICm/DMA learnings. Useful as **background**; every
concrete address/layout must be re-derived from the Helix4 CDK defs.

---

## Asset summary

| Layer | 4610 status | Where |
|---|---|---|
| Platform (sensors/optics/LED/fan/ONIE) | **Done** | ONL `arm-accton-as4610` |
| Device tree / kernel | **Done** | ONL DTS + iProc 4.14 |
| Data-plane SDK (chip driver) | **Available** | OpenMDK `bcm56340_a0` BMD |
| Chip register/table defs | **Available** | OpenMDK CDK `bcm56340_a0_defs.h` |
| Full L2+L3 SDK (route/ECMP/ACL) | **Available, first-class** | OpenBCM 6.5.27 (`helix4.c`, `BCM_56340_A0`) |
| Reference binary NOS | Need ARM Cumulus 2.5.4+/3.x | not on disk |

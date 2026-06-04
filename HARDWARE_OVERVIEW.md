# AS4610-54T — Hardware Overview

Chip inventory and specifications. Sources are public datasheets plus the
device tree and ONLP drivers in our local `OpenNetworkLinux/` tree
(`packages/platforms/accton/armxx/arm-accton-as4610/`). Physical PCB inspection
still **TODO** — when we have the unit on the bench, mirror
`AS5610_52X_BOARD_COMPONENT_MAP.md` and fill markings/locations.

---

## System specifications (datasheet)

| Attribute | Value |
|---|---|
| Model | Accton/Edgecore **AS4610-54T** (ONIE platform `arm-accton-as4610-54-r0`) |
| Sibling models | AS4610-54P (PoE), AS4610-30 / 30T (24-port), AS4610-30P |
| Front ports | **48 × 10/100/1000BASE-T** (RJ-45), ports 1–48 |
| Uplinks | **4 × 10G SFP+**, ports 49–52 |
| Stacking | **2 × 20G QSFP+**, ports 53–54 |
| Switching capacity | 176 Gb/s (datasheet); Helix4 core line-rate ~120 Gb/s |
| Forwarding rate | ~131–190 Mpps |
| PSU | Dual hot-swappable AC, ~150 W (3Y-Power YM-1921, PMBus) |
| Cooling | Fan tray(s), thermal-managed by ONLP |
| Boot | ONIE installer → NOS on USB disk (`/dev/sda`) |

### Switching role: Layer 2 **and** Layer 3 (by design)

Edgecore markets and builds the AS4610-54T as a **Layer 3 switch / router**, not
a pure L2 box. The datasheet states *"full line-rate **Layer 2 or Layer 3**
forwarding and switching."* The Helix4 (BCM56340) silicon implements hardware
IPv4/IPv6 routing, L3 interfaces/SVIs, and ECMP in its forwarding pipeline.

- **Hardware L3 is present in the chip** (L3_DEFIP / L3_ENTRY / EGR_L3_* tables).
- **Routing *protocols* (static, OSPF, BGP, VRRP) come from the NOS**, not the
  chip — the box ships bare (ONIE only); you bring the control plane (e.g. FRR).
- The "L3 gap" noted elsewhere in these docs is a limitation of the **OpenMDK
  BMD driver** (L2-only by design), **not** of the hardware. See
  [`EXISTING_SOFTWARE_ASSETS.md`](EXISTING_SOFTWARE_ASSETS.md) — OpenBCM has full
  L3 SDK support for this chip.

---

## Core silicon

### Switch ASIC + CPU: Broadcom BCM56340 "Helix4" (SoC)

**This is the single most important fact about the board:** the CPU is *inside*
the switch chip. The BCM56340 is a StrataXGS Helix4 SoC that integrates:

- a 48-port GbE + 10GbE-uplink switching core,
- a **dual-core ARM Cortex-A9 @ 1 GHz ("iProc")** application processor,
- DDR3 memory controller, PCIe, USB, UART, I²C, GPIO, etc.

| Attribute | Value |
|---|---|
| Part | BCM56340 (Helix4 family; siblings BCM56341/2/3/4/6) |
| Family | StrataXGS Helix4 (BCM5634x) |
| CPU | Dual-core ARM Cortex-A9, ~1 GHz, on-die (iProc) |
| Switching | 48× 1GbE + up to 6× 10GbE SerDes |
| L3 | IPv4/IPv6 routing, ECMP, large enterprise tables |
| DT compatible | `brcm,helix4`; CMIC node `iproc_cmicd` |
| Status | Broadcom **EOL** — fine for our hobby/RE use; no new designs |

Because the CPU is on-die, **there is no PCIe enumeration of the switch and no
PAXB sub-window remap** — the entire `5610` "5-layer access stack" (PCIe BAR0 →
PAXB IMAP → CMICm → SCHAN) collapses. The CMIC is reached directly via
memory-mapped iProc registers (`iproc_cmicd` in the device tree). See
[`ASIC_AND_CPU_ARCHITECTURE.md`](ASIC_AND_CPU_ARCHITECTURE.md).

### Memory / boot media (from DTS + platform-config)

| Component | Detail | Source |
|---|---|---|
| DRAM | ~2 GB DDR3 (`memory reg = <0x61000000 0x7f000000>`, `mem=2000M`) | DTS |
| Kernel | armhf, **iProc 4.14** ONL kernel | platform-config yml |
| NOS storage | USB disk `/dev/sda` (loadaddr `0x70000000`) | platform-config yml |
| U-Boot env | `/dev/mtd2`, offset 0, size 0x2000, sector 0x10000 | platform-config yml |
| Flash | NOR for U-Boot + ONIE (exact part TBD on bench) | — |

---

## Board peripherals (decoded from device tree)

Full topology in [`BOARD_TOPOLOGY_AND_I2C.md`](BOARD_TOPOLOGY_AND_I2C.md). Summary:

| Function | Part / compatible | Bus / addr |
|---|---|---|
| **CPLD** | `accton,as4610_54_cpld` | i2c0 @ **0x30** (note: I²C, not memory-mapped like 5610) |
| Port I²C mux | TI **PCA9548** (8-ch) | i2c1 @ 0x70 |
| SFP+ 49–52 EEPROM | `optoe2` | mux ch0–3 @ 0x50 |
| QSFP+ 53–54 EEPROM | `optoe1` | mux ch4–5 @ 0x50 |
| PSU1/PSU2 EEPROM | `accton,as4610_psu1/2` | mux ch6 @ 0x50 / 0x51 |
| PSU1/PSU2 PMBus | 3Y-Power **YM-1921** | mux ch6 @ 0x58 / 0x59 |
| Temp sensor | NXP **LM77** | mux ch7 @ 0x48 |
| RTC | **M41T11** (driven as ds1307) | mux ch7 @ 0x68 |
| Board EEPROM | **AT24C04** | mux ch7 @ 0x50 |
| Mgmt PHY | via `gmac0`, SGMII | iProc GMAC0 |
| USB | iProc EHCI + USB PHY (host) | on-die |
| Misc on-die | HW RNG, watchdog (`iproc_wdt`), DMA (`dmac0`), GPIO (`gpio_cca`) | on-die |

---

## Front-port / CPLD port numbering (from `sfpi.c`)

ONLP numbers the optics ports **48–53** internally (0-based-ish) for the 54T,
mapping to physical SFP+/QSFP+ ports 49–54. CPLD port index = `front_port - 47`.
Front-port I²C bus index = `front_port - 46`. Use these maps when wiring up
present/LOS/tx-disable to CPLD registers.

---

## Still TODO (bench work)

- [ ] Physical PCB inspection → component map with markings/locations.
- [ ] Confirm NOR flash part + full flash partition layout.
- [ ] Confirm DDR3 size/part and exact iProc variant stepping.
- [ ] Dump CPLD register map from the running unit (cross-check `accton_as4610_cpld.c`).
- [ ] Capture ONIE machine.conf / board EEPROM TLV.

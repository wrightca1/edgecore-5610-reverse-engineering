# AS4610-54T — ASIC & CPU Architecture (and why it differs from the 5610)

This document exists to stop us from blindly reusing the 5610 mental model. The
5610 and 4610 are **fundamentally different system architectures**, even though
both are Broadcom StrataXGS parts programmed through a CMIC + SCHAN.

---

## The one-sentence difference

> On the **5610**, a separate PowerPC CPU reaches the switch chip **over PCIe**;
> on the **4610**, the CPU **is** the switch chip (ARM core on the same die),
> reached over the **on-chip iProc bus** — so there is no PCIe, no BAR0, and no
> PAXB sub-window remapping.

---

## Side-by-side

| Layer | AS5610-52X (Trident+) | AS4610-54T (Helix4 SoC) |
|---|---|---|
| CPU | Freescale P2020, **external chip** | ARM Cortex-A9 ×2, **on the switch die (iProc)** |
| CPU↔ASIC transport | **PCIe** (BAR0 @ 0xA0000000, 256 KB) | **On-die AXI / iProc** memory map |
| Address translation | **PAXB sub-windows** (8×4 KB, IMAP0_7 remap) — the big 5610 headache | **None** — CMIC regs are directly memory-mapped |
| CMIC | CMICm in a PCIe BAR sub-window | `iproc_cmicd` node, MMIO via platform driver |
| Endianness | PPC32 **big-endian** | ARM **little-endian** |
| Kernel BDE | `linux-kernel-bde` + `linux-user-bde`, PCI probe | iProc/CMICd BDE, platform probe (no PCI dev) |
| DMA | DV ring, DCB type 21, 32 B | Helix4 CMICd DMA (verify DCB format on this gen) |

### What still carries over from the 5610 work

The **chip-table programming layer is largely the same idea**: you still talk
to the switch core through a **CMIC** using **SCHAN** transactions, and the
StrataXGS memory/register model (L2_ENTRY, L3_DEFIP, VLAN, EGR_*, FP TCAM,
HASH_INSERT/LOOKUP opcodes) is the same SDK lineage. So our 5610 docs on:

- SCHAN opcodes (read/write/table/HASH_*),
- L2/L3/VLAN/ECMP entry **field layouts** (conceptually),
- the SDK `soc_*` / `bcm_*` call structure,

are useful **reference**, but every concrete value (chip addresses, table sizes,
field bit positions, block IDs) must be **re-derived for Helix4** — they differ
between Trident+ and Helix4. Do not copy 5610 addresses verbatim.

### What does NOT carry over

- The entire **PCIe BAR0 / PAXB IMAP sub-window** machinery
  (`PAXB_SUBWINDOW_MECHANISM.md`, the May-17 DMA root cause) — **N/A** on the
  4610. The CMIC is directly mapped.
- PowerPC-specific bits (e500 cache, eLBC/localbus CPLD at 0xEA000000, gianfar
  eTSEC). The 4610 CPLD is on **I²C @ 0x30**, and the mgmt MAC is an iProc GMAC.
- Warpcore SerDes + DS100DF410 retimers + BCM84740 PHY firmware: the 4610 uses
  **integrated copper PHYs** for the 48× 1G ports and Helix4 10G SerDes for
  uplinks — different (and simpler) SerDes story, **no external retimers**.

---

## iProc, in brief

"iProc" is Broadcom's on-chip ARM subsystem found in Helix4 / Trident2+ / XGS
SoCs. It provides the ARM A9 cores plus standard peripherals (UART, I²C, SPI,
GPIO, USB, PCIe-RC, DMA, watchdog, RNG) and a bridge to the switch core's
**CMIC** (here exposed as the `iproc_cmicd` device-tree node). From software:

- The switch chip appears as a **platform device**, not a PCI device.
- CMIC registers, SCHAN, and DMA are accessed through the CMICd BDE driver's
  MMIO mapping — **no PAXB translation step**.
- This is why the 4610 sidesteps the single hardest 5610 bug
  (`project_paxb_subwindow_algorithm_decoded`).

> **Open question to confirm on bench / in SDK source:** exact CMICd register
> base, DMA descriptor (DCB) format for this Helix4 stepping, and whether the
> in-tree OpenMDK/OpenNSL supports BCM56340 directly or needs config work. Track
> in [`NOS_BUILD_PLAN.md`](NOS_BUILD_PLAN.md).

---

## Device-tree evidence (from `arm-accton-as4610.dts`)

```
compatible = "accton,as4610_54","brcm,helix4";
#include "dts/bcm-helix4.dtsi"     // iProc Helix4 base SoC
&gmac0   { phy-mode = "sgmii"; }   // management ethernet (on-die GMAC)
&iproc_cmicd { status = "okay"; }  // <-- the switch CMIC, on-die
&iproc_wdt   { ... }  &dmac0 { ... }  &hwrng { ... }  // on-die peripherals
&i2c0 { cpld@30 { compatible = "accton,as4610_54_cpld"; } }
```

The presence of `iproc_cmicd` (vs a PCI switch device) is the definitive marker
that this is a CPU-on-die design.

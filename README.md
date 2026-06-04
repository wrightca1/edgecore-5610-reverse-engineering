# Edgecore AS4610-54T — Open NOS Project

Working folder for bringing up our own NOS (EdgeNOS-class) on the
**Edgecore / Accton AS4610-54T**, the same goal we pursued on the AS5610-52X
— but on **very different and much friendlier hardware**.

> **TL;DR for the impatient:** The 4610 is a Helix4 **SoC** (ARM Cortex-A9 CPU
> baked into the switch chip, no PCIe), running **armhf Linux**, and it is
> **already fully supported by Open Network Linux** in our local
> `OpenNetworkLinux/` tree (device tree + all ONLP platform drivers). We do not
> have to reverse-engineer the hardware the way we did for the 5610. The work
> here is mostly *assembling and configuring an existing open stack*, not
> static-analyzing a proprietary `switchd`.

---

## Start here

1. [`HARDWARE_OVERVIEW.md`](HARDWARE_OVERVIEW.md) — the chip inventory and specs.
2. [`ASIC_AND_CPU_ARCHITECTURE.md`](ASIC_AND_CPU_ARCHITECTURE.md) — **why the
   4610 is architecturally different from the 5610** (SoC vs PCIe). Read this
   before you reuse any 5610 access-stack assumptions.
3. [`BOARD_TOPOLOGY_AND_I2C.md`](BOARD_TOPOLOGY_AND_I2C.md) — board map / I²C
   tree decoded from the ONL device tree.
4. [`EXISTING_SOFTWARE_ASSETS.md`](EXISTING_SOFTWARE_ASSETS.md) — what already
   exists in our local trees (ONL, OpenMDK, etc.) that we can use directly.
5. [`NOS_BUILD_PLAN.md`](NOS_BUILD_PLAN.md) — gap analysis vs the 5610 work and
   the recommended path to a working NOS.
6. [`FULLY_OPENSOURCE_LINUX_PLAN.md`](FULLY_OPENSOURCE_LINUX_PLAN.md) — what it
   takes to run a vanilla-Linux + L3-routing stack (FRR) with no proprietary
   NOS, and exactly where the open-source line falls.
7. [`LICENSING.md`](LICENSING.md) — licenses on the OpenMDK / OpenBCM switch
   SDKs (source-available, redistributable, not OSI-libre) and the GPL boundary.

---

## Hardware at a glance

| Component | AS4610-54T | (compare: AS5610-52X) |
|---|---|---|
| **Switch ASIC** | Broadcom **BCM56340 "Helix4"** | BCM56846 "Trident+" |
| **CPU** | **Dual-core ARM Cortex-A9 @ 1 GHz, integrated in the ASIC (iProc)** | Separate Freescale P2020 PowerPC over PCIe |
| **CPU↔switch link** | **On-die (iProc CMICd, MMIO)** | **PCIe BAR0 + PAXB sub-windows** |
| **Architecture** | **armhf / armel** | PowerPC (PPC32 BE) |
| **Front ports** | 48× 10/100/1000BASE-T (RJ-45) | 48× 10G SFP+ |
| **Uplinks** | 4× 10G SFP+ (ports 49–52) | 4× 40G QSFP+ |
| **Stacking** | 2× 20G QSFP+ (ports 53–54) | — |
| **Throughput** | ~176–256 Gb/s (datasheet), 120 Gb/s line-rate switching core | 640 Gb/s |
| **PSU** | Dual hot-swap AC (3Y-Power YM-1921, PMBus) | Dual AC |
| **Storage / boot** | ONIE on flash → NOS on USB (`/dev/sda`) | ONIE on NOR → NOS on internal USB-NAND |
| **NOS support** | ONL (full), Cumulus 2.5.4+ / 3.x / 4.1+ | Cumulus 2.5, custom EdgeNOS |

---

## How this differs from the 5610 effort

The 5610 project was a deep, ~194-document reverse-engineering campaign against a
proprietary Broadcom `switchd` because **no open NOS supported that exact board
well** and the silicon access path (PCIe → PAXB → CMICm → SCHAN) had to be
rediscovered from binaries and live `bcmcmd` probing.

The 4610 is the opposite situation:

- **It's a reference design.** The BCM56340 Helix4 was Broadcom's "single-chip
  enterprise switch" — CPU + switch fabric + SerDes on one die. Many vendors
  shipped near-identical boards.
- **Open Network Linux already supports it.** Our local `OpenNetworkLinux/` tree
  contains the device tree, kernel patches, and the full ONLP platform driver
  set (CPLD, fan, PSU, LED, SFP, thermal, sys) for `as4610-54` and `as4610-30`.
- **Cumulus Linux supported it** from 2.5.4 onward (3.x throughout, 4.1+) — so a
  known-good binary NOS exists to diff against if we need a reference, exactly
  like the Cumulus 2.5 baseline we mined for the 5610.

So the deliverable here is realistically: *stand up ONL (or a custom thin NOS)
on the box, get the data plane forwarding via OpenMDK/OpenNSL or the in-tree
brcm SDK, and document the board* — not a from-scratch silicon RE.

See [`NOS_BUILD_PLAN.md`](NOS_BUILD_PLAN.md) for the concrete plan.

---

## Provenance / ethics

Same standard as the 5610 work: only hardware we own, public datasheets,
open-source trees (ONL, OpenMDK), and live inspection of devices we possess.
No Broadcom NDA material.

*Folder created 2026-06-03.*

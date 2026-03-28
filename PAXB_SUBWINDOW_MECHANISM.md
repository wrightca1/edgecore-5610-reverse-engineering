# iProc PAXB Sub-Window Mechanism (BCM56846)

## Overview

The BCM56846 (Trident+) uses an iProc PCI-AXI bridge (PAXB) to map AXI-bus
registers into the PCIe BAR0 address space.  BAR0 is 256KB but only the first
32KB (0x0000-0x7FFF) is divided into 8 sub-windows of 4KB each.  Each
sub-window maps to a configurable 4KB page in the AXI address space via an
IMAP register.

This document captures how Cumulus Linux (and the Broadcom SDK) use sub-window
remapping for register access, derived from:
- Live register dumps from Cumulus 2.5.1 on AS5610-52X (March 2026)
- Disassembly of Cumulus `linux-kernel-bde.ko` symbol table
- Broadcom SDK source `shbde_iproc.c` (from SONiC saibcm-modules)
- `iproc_map_default` data extracted from Cumulus BDE .ko

## Sub-Window Layout

```
BAR0 Offset     Sub-window    IMAP Register     Default AXI Mapping
─────────────   ──────────    ─────────────     ───────────────────
0x0000-0x0FFF   0             IMAP0_0 (0x2C00)  0x18000000 (CMIC base)
0x1000-0x1FFF   1             IMAP0_1 (0x2C04)  0x18030000 (CMICm SCHAN/DMA)
0x2000-0x2FFF   2             IMAP0_2 (0x2C08)  0x18012000 (XLPORT/MAC)
0x3000-0x3FFF   3             IMAP0_3 (0x2C0C)  (varies)
0x4000-0x4FFF   4             IMAP0_4 (0x2C10)  (varies)
0x5000-0x5FFF   5             IMAP0_5 (0x2C14)  (varies)
0x6000-0x6FFF   6             IMAP0_6 (0x2C18)  (varies)
0x7000-0x7FFF   7 (remap)     IMAP0_7 (0x2C1C)  (dynamically remapped)
```

The default mappings come from `iproc_map_default` in the Cumulus BDE:

```c
// Extracted from linux-kernel-bde.ko .data section at offset 0x124
iproc_map_default[] = {
    { 0x18000000, 0x18000FFF },  // entry 0: CMIC base
    { 0x18030000, 0x18030FFF },  // entry 1: CMICm (SCHAN, DMA)
    { 0x18012000, 0x18012FFF },  // entry 2: XLPORT/MAC
    { 0, 0 },                    // entries 3-7: unused
    ...
};
```

## IMAP Register Format

Each IMAP register is 32 bits:

```
Bits [31:12]  AXI base address (4K-aligned page)
Bit  [0]     Valid bit (must be set for the mapping to be active)
Bits [11:1]  Reserved
```

Example: To map sub-window 7 to AXI 0x18032000 (CMICm MIIM):
```c
iowrite32(0x18032001, bar0 + 0x2C1C);  // page 0x18032000 | valid=1
```

## How Cumulus BDE Accesses iProc Registers

From `shbde_iproc_pci_read()` / `shbde_iproc_pci_write()` in `shbde_iproc.c`:

1. **Cache** all 8 IMAP values at init time (`subwin_cache_init`)
2. For each access to AXI address `A`:
   a. Compute `page = A & ~0xFFF`
   b. Scan cached sub-windows 0-7 for a match
   c. If found at sub-window `i`: access `BAR0 + (i * 0x1000) + (A & 0xFFF)`
   d. If no match: **remap sub-window 7**:
      - Write `(page | 1)` to IMAP0_7 (`BAR0 + 0x2C1C`)
      - Readback IMAP0_7 to ensure write completes
      - Update cache entry 7
      - Access `BAR0 + 0x7000 + (A & 0xFFF)`

## Key AXI Address Ranges

| AXI Address   | Size  | Block              | Access Method              |
|---------------|-------|--------------------|----------------------------|
| 0x18000000    | 4KB   | CMIC base          | Sub-window 0 (always mapped) |
| 0x18012000    | 4KB   | XLPORT/MAC         | Sub-window 2 (default)     |
| 0x18030000    | 4KB   | CMICm SCHAN/DMA    | Sub-window 1 (default)     |
| 0x18032000    | 4KB   | CMICm MIIM         | Remap sub-window 7         |
| 0x18033000    | 4KB   | CMICm SCHAN (alt)  | Remap sub-window 7         |

## Legacy CMIC vs CMICm

The BCM56846 has **both** legacy CMIC and CMICm register blocks:

- **Legacy CMIC** at AXI 0x18000000 (sub-window 0, BAR0 offset 0x000):
  - SCHAN_CTRL: 0x050
  - MIIM_PARAM: 0x150, MIIM_READ_DATA: 0x154, MIIM_ADDRESS: 0x158
  - MIIM_CTRL: 0x49C, MIIM_STAT: 0x4A0
  - CMIC_DEV_REV_ID: 0x178

- **CMICm** at AXI 0x18030000-0x18033FFF (needs sub-window remap for MIIM):
  - CMICm SCHAN: 0x18033000
  - CMICm MIIM: 0x18032000

Cumulus switchd uses the **legacy CMIC MIIM** registers in sub-window 0
for PHY access.  The MIIM_ADDRESS (0x158) was observed with value 0x00009102
on the live system, confirming active MIIM operations through sub-window 0.

## Live Register Dump (Cumulus 2.5.1, March 27 2026)

From the running AS5610 at 10.1.1.242:

```
CMIC_DEV_REV_ID  (0x0178) = 0x46b80200   (BCM56846 rev 02)
SCHAN_CTRL       (0x0050) = 0x00000000   (idle)
MIIM_PARAM       (0x0150) = 0x00000000
MIIM_READ_DATA   (0x0154) = 0x00000000
MIIM_ADDRESS     (0x0158) = 0x00009102   (active MIIM address)
MIIM_STAT        (0x04a0) = 0x1f000000

PAXB_ENDIANESS   (0x2030) = 0xf3000000
IMAP0            (0x2c00) = 0x00000000
IMAP1            (0x2c04) = 0x00000000
IMAP2            (0x2c08) = 0xf8000000
IMAP3            (0x2c0c) = 0x80000000
IMAP4            (0x2c10) = 0xf8000000
IMAP5            (0x2c14) = 0x80000000
IMAP6            (0x2c18) = 0xf8000000
IMAP7            (0x2c1c) = 0x80000000
```

Note: The IMAP values read as garbage/defaults because Cumulus remaps them
dynamically via PCI config space writes from the kernel BDE module.  The
BAR0 read of IMAP registers may not reflect the actual programmed values
on all iProc revisions.

## Implications for Custom NOS (EdgeNOS)

Our BDE module (`newnos/asic/bde/linux-kernel-bde.c`) originally used only
direct BAR0 ioread32/iowrite32 without sub-window remapping.  This worked for
legacy CMIC registers in sub-window 0 but could not access CMICm registers
at AXI addresses above 0x18000FFF.

The fix adds:
- `iproc_axi_read()` / `iproc_axi_write()` functions with sub-window lookup
- Sub-window cache initialized at probe time
- Dynamic remapping of sub-window 7 for uncached AXI pages
- New ioctls `BDE_IOC_IPROC_READ` / `BDE_IOC_IPROC_WRITE` for userspace
- Spinlock protection for concurrent sub-window 7 remapping

## References

- Broadcom SDK: `systems/bde/shared/shbde_iproc.c` (shbde_iproc_pci_read/write)
- Broadcom SDK: `systems/bde/linux/kernel/linux-kernel-bde.c` (_iproc_read/write)
- Cumulus BDE: `extracted/2.5.0-powerpc/rootfs/lib/modules/.../linux-kernel-bde.ko`
- EdgeNOS BDE: `newnos/asic/bde/linux-kernel-bde.c`

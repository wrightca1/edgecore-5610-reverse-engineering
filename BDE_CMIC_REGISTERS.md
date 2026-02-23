# BDE CMIC Register Definitions

**Date**: 2026-02-15  
**Source**: OpenNSL SDK `systems/bde/linux/user/kernel/linux-user-bde.c`  
**Purpose**: Canonical CMIC/CMICm/CMICd register offsets used by BDE for interrupt and device access

---

## Summary

The **linux-user-bde** (and kernel BDE) module uses these offsets **relative to the device base** (PCI BAR0). They are the same values used by the SDK for CMICm/CMICd (Trident/Trident+).

## CMIC / CMICe (legacy)

| Offset   | Name             | Usage in BDE        |
|----------|------------------|---------------------|
| `0x00000144` | CMIC_IRQ_STAT   | Interrupt status    |
| `0x00000148` | CMIC_IRQ_MASK   | Interrupt mask      |
| `0x0000006C` | CMIC_IRQ_MASK_1 | Interrupt mask 1    |
| `0x00000070` | CMIC_IRQ_MASK_2 | Interrupt mask 2   |

## CMICm / CMICd CMC Registers

CMC base for CMCx: `0x31400 + (0x1000 * x)` (x = 0, 1, 2). BDE uses these for interrupt status and mask. S-Channel is at CMC base + 0x1800 (e.g. 0x32800 for CMC0). See SDK_REGISTER_MAP.md and SCHAN_AND_RING_BUFFERS.md.

## Reference

- File: `sdk-6.5.12-gpl-modules/systems/bde/linux/user/kernel/linux-user-bde.c`

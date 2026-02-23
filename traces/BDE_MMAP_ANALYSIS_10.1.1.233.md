# BDE mmap vs ioctl Analysis (10.1.1.233)

**Date**: 2026-02-19  
**Source**: `bde-mmap-trace-10.1.1.233.log`, `bde-mmap-maps-10.1.1.233.txt`

## /proc/PID/maps: /dev/mem mmap

switchd has **mmap'd /dev/mem** for direct ASIC register access:

| Virtual range    | Phys offset  | Size  | Flags | Device  |
|------------------|--------------|-------|-------|---------|
| 4802b000-4806b000| 0xa0000000   | 256KB | rw-s  | /dev/mem |
| 4806b000-4c06b000| 0x04000000   | 64MB  | rw-s  | /dev/mem |

**Conclusion**: switchd uses **mmap + direct read/write** for register access, not LUBDE_CPU_READ_REG/CPU_WRITE_REG ioctl per access. BDE (or init code) gets physical address from LUBDE_GET_DEVICE and mmaps /dev/mem at that offset.

## Trace: mmap during capture

The trace captured repeated `mmap(NULL, 659456, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)` — anonymous heap, not /dev/mem. The /dev/mem mmaps happened at **process startup** (before our attach).

## Checklist 1.5–1.6 update

- **1.5** PARTIAL → HAVE: BAR mapping via mmap /dev/mem at 0x04000000 (64MB) and 0xa0000000 (256KB).
- **1.6** PARTIAL → HAVE: Register access is **mmap + direct read/write**, not ioctl.

# Runtime Trace Analysis — <LIVE_SWITCH_IP>

**Date**: 2026-02-19  
**Switch**: Cumulus Linux @ <LIVE_SWITCH_IP>

---

## Summary

Consolidated analysis of route-ecmp, OSPF, and port-up straces. All traces show the same BDE ioctl set; no CPU_READ_REG/CPU_WRITE_REG — register access via mmap.

---

## BDE ioctl usage (all traces)

From `linux-user-bde.h`:
- `_IO('L', 8)`  = **LUBDE_USLEEP** (0x20004c08)
- `_IO('L', 9)`  = **LUBDE_WAIT_FOR_INTERRUPT** (0x20004c09)
- `_IO('L', 10)` = **LUBDE_SEM_OP** (0x20004c0a)
- `_IO('L', 11)` = **LUBDE_UDELAY** (0x20004c0b)

| ioctl   | LUBDE name               | Purpose                         |
|---------|--------------------------|---------------------------------|
| 0x20004c08 | LUBDE_USLEEP            | Sleep (timing)                  |
| 0x20004c09 | LUBDE_WAIT_FOR_INTERRUPT| Block until ASIC interrupt      |
| 0x20004c0a | LUBDE_SEM_OP            | Semaphore take/give (sync)      |
| 0x20004c0b | LUBDE_UDELAY            | Microsecond delay               |

---

## Trace comparison

| Trace         | Lines   | Trigger                  | Unique ioctls | Notes                          |
|---------------|---------|--------------------------|---------------|--------------------------------|
| route-ecmp    | ~7.2k   | ECMP route add/delete    | 08, 09, 0a    | L3/ECMP programming            |
| OSPF          | ~17k    | clear ip ospf neighbor   | 08, 09, 0a    | FIB refresh, more activity     |
| port-up       | ~12k    | ip link set swp2 down/up | 08, 09, 0a, 0b| Same set + UDELAY              |

**No LUBDE_CPU_READ_REG (24) or LUBDE_CPU_WRITE_REG (23)** — register access is via mmap (see BDE_MMAP_ANALYSIS).

---

## Table IDs from traces

Strace does not expose table IDs. For API→table mapping:
- Use GDB breakpoints at table dispatcher (requires `gdb` on switch)
- Or correlate Ghidra xrefs from L2/L3 table addresses

---

## Next steps

1. Install GDB on switch; run `run-api-to-table-id-trace-<LIVE_SWITCH_IP>.sh`.
2. Add mmap/read/write to trace filter if deeper register/tables analysis needed.
3. Use L3 table callers output: FUN_018d7ad4 calls FUN_018d62ec (table write wrapper).

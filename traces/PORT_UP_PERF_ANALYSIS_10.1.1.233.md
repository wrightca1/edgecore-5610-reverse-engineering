# Port-Up Perf Trace Analysis (<LIVE_SWITCH_IP>)

**Date**: 2026-02-20  
**Trace**: `perf-port-up-<LIVE_SWITCH_IP>.data`, `perf-port-up-<LIVE_SWITCH_IP>.txt`  
**Command**: `run-perf-port-up-<LIVE_SWITCH_IP>.sh swp1` (perf record on switchd during `ip link set swp1 down/up`)

---

## Summary

- **~23.5k samples** over ~12s; **159 samples** include `linux_user_bde` or switchd user-space frames.
- Port bringup path shows **BDE semaphore/ioctl** (`sal_sem_take` → `_ioctl` → `vfs_ioctl`) called from **Cumulus switchd** (not OpenNSL). Register access is via **mmap** (see [BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md)), so perf does not show CPU_READ_REG/CPU_WRITE_REG.
- Call stacks during port up show a consistent **switchd → BDE** chain: many switchd addresses (e.g. 100235ec, 100118d0, 10011fcc, 1000f084, 10008a4c) then libc `ioctl`, then `_ioctl` / `sal_sem_take` in `linux_user_bde`.

---

## Sample call stacks (BDE path)

Representative stacks where switchd is in the call chain with BDE:

```
switchd  1731 cycles:
        c048315c _raw_spin_unlock_irqrestore ([kernel.kallsyms])
        f107caf0  ([linux_user_bde])
        f107cbd0 sal_sem_take ([linux_user_bde])
        f107b81c _ioctl ([linux_user_bde])
        ...
         fca6bb8 ioctl (/lib/powerpc-linux-gnu/libc-2.13.so)
        10322e2c  (/usr/sbin/switchd)
        1032567c  (/usr/sbin/switchd)
        10830510  (/usr/sbin/switchd)
        1082f650  (/usr/sbin/switchd)
        111490a8  (/usr/sbin/switchd)
        ...
        100235ec _init (/usr/sbin/switchd)
        100118d0 _init (/usr/sbin/switchd)
        10011fcc _init (/usr/sbin/switchd)
        1000f084 _init (/usr/sbin/switchd)
        10008a4c _init (/usr/sbin/switchd)
```

Another stack shows different switchd frames (10024aa0, 1001d750, 1000f250) before the same BDE/ioctl path — consistent with multiple code paths (e.g. port state, link state, PHY) all using BDE sync.

---

## Interpretation for 5.2–5.3 (port bringup registers)

1. **BDE usage**: Port up/down triggers **LUBDE_SEM_OP** (and USLEEP/WAIT_FOR_INTERRUPT/UDELAY) as in the strace; perf confirms these happen from switchd via `sal_sem_take` / `_ioctl` in `linux_user_bde`.
2. **Register access**: No register read/write ioctls in strace; [BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md) shows switchd mmaps at 0x04000000 and 0xa0000000. So **port/SerDes register writes are via mmap**, not captured by perf call stacks unless we had a custom probe on those addresses.
3. **Next steps to close 5.2–5.3**:
   - **Option A**: Strace or eBPF on **mmap’d region**: trace `read`/`write` (or equivalent) to the BAR ranges during port up to log which offsets are touched (port/SerDes register list).
   - **Option B**: **Ghidra on Cumulus switchd** binary: locate port enable/speed/duplex code paths (e.g. by string refs or by correlating the perf addresses 100235ec, 100118d0, 1000f084, etc. if symbols are available) and extract register offsets.
   - **Option C**: **OpenNSL reference** (already documented): [PORT_BRINGUP_ANALYSIS.md](../PORT_BRINGUP_ANALYSIS.md), [PORT_BRINGUP_REGISTERS_ANALYSIS.md](../PORT_BRINGUP_REGISTERS_ANALYSIS.md) — handler tables at -0x5fe0/-0x68b0; GDB on ONL switch or mmap trace to get concrete SerDes regs.

---

## Artifacts

| File | Description |
|------|-------------|
| `perf-port-up-<LIVE_SWITCH_IP>.data` | Perf record data (can run `perf script -i …` again) |
| `perf-port-up-<LIVE_SWITCH_IP>.txt` | Perf script output (~23.5k lines, call stacks) |

Perf was installed from Debian Wheezy powerpc packages (linux-tools-3.2, libelf1, libdw1, libnewt0.52) and run with `LD_LIBRARY_PATH=/tmp/bundle:/tmp/bundle/elfutils` on the switch.

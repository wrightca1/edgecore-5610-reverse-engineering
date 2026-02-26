# Port-Up Trace Analysis (<LIVE_SWITCH_IP>)

**Date**: 2026-02-19  
**Trace**: `port-up-trace-<LIVE_SWITCH_IP>.log`, `port-up-summary-<LIVE_SWITCH_IP>.txt`  
**Command**: `run-port-up-trace-<LIVE_SWITCH_IP>.sh swp1`

## BDE ioctl decoding

From `linux-user-bde.h`:
- `_IO('L', 8)` = **LUBDE_USLEEP** (0x20004c08)
- `_IO('L', 9)` = **LUBDE_WAIT_FOR_INTERRUPT** (0x20004c09)
- `_IO('L', 10)` = **LUBDE_SEM_OP** (0x20004c0a)
- `_IO('L', 11)` = **LUBDE_UDELAY** (0x20004c0b)

## Observed during `ip link set swp1 down ; ip link set swp1 up`

| ioctl code  | LUBDE name              | Purpose                          |
|-------------|-------------------------|----------------------------------|
| 0x20004c08  | LUBDE_USLEEP            | Sleep (timing)                   |
| 0x20004c09  | LUBDE_WAIT_FOR_INTERRUPT| Block until ASIC interrupt       |
| 0x20004c0a  | LUBDE_SEM_OP            | Semaphore take/give (sync)       |
| 0x20004c0b  | LUBDE_UDELAY            | Microsecond delay                |

Both take `lubde_ioctl_t` with `p0` (3rd arg) = pointer to struct. LUBDE_SEM_OP uses `d0`/`dx` for op (CREATE/TAKE/GIVE) and sem ID.

## Interpretation

Port bringup uses the same BDE synchronization as packet I/O: **wait_for_interrupt** and **sem_op**. No LUBDE_CPU_READ_REG (24) or LUBDE_CPU_WRITE_REG (23) appear in this trace, which suggests:

1. Register access may go through **mmap** (direct /dev/mem or BDE-exposed BAR) rather than ioctl, or
2. Register access is in a different thread/timing not captured, or
3. Port bringup logic may be in kernel/PHY driver rather than switchd for this path.

## Next steps for port bringup (5.2–5.3)

1. **perf port-up trace**: `run-perf-port-up-<LIVE_SWITCH_IP>.sh swp1` — captures call stacks during port down/up (requires perf on switch).
2. Add **mmap** and **read**/write to trace filter to catch register access if via mmap.
3. Run trace with longer capture around link up.
4. Check for LUBDE_CPU_READ_REG (0x20004c18) / LUBDE_CPU_WRITE_REG (0x20004c17) in full trace.
5. Correlate with `/proc/PID/maps` for switchd to see mmap regions.

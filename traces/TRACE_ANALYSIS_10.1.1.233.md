# Packet I/O trace analysis — 10.1.1.233

**Switch**: cumulus@10.1.1.233  
**Run**: Via `run-packet-io-trace-10.1.1.233.sh` with `SSHPASS` and sudo password piped.

## Result (updated)

- **Trace file**: `packet-io-trace-10.1.1.233.log`
- **Summary**: `packet-io-summary-10.1.1.233.txt`

Earlier runs attached to the wrong PID / only one thread and produced almost no output. The on-switch tracer was updated to:

- Find the real daemon PID via `pgrep -xo switchd`
- Attach to **all threads** via `/proc/$PID/task/*` (multiple `-p` args)
- Trace `read,write,ioctl` plus wait syscalls (`select`/`poll`/`epoll_*`) so we can see wakeups

With that, we captured a full trace.

## Key findings from the syscall trace

- **BDE + MMIO fds**:
  - `/dev/linux-user-bde` is open (fd **14**)
  - `/dev/mem` is open (fd **15**)
- **TUN fds**: many `/dev/net/tun` fds are open (fd **20–71** observed)
- **Kernel→switchd** (TX to ASIC path start):
  - `select()` indicates ready on a TUN fd, then `read(fd=20, ..., 16384) = 42/82/122` (example sizes seen)
- **switchd→kernel** (RX from ASIC path end):
  - `write(fd=20, buf, len) = 60/82` observed
- **BDE ioctls**:
  - ioctl request `0x20004c09` / `0x20004c0a` map to **LUBDE_WAIT_FOR_INTERRUPT (9)** and **LUBDE_SEM_OP (10)** (from `linux-user-bde.h`)

This strongly suggests packets move via user-space DMA rings (accessed through `/dev/mem` and/or BDE-provided mappings) with interrupt/sem synchronization via BDE ioctls, rather than a simple “packet TX ioctl”.

**Full extraction** (thread roles, fd map, BDE ioctl decode, TX/RX sequences, raw samples): [PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md](PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md).

## Interpretation

1. **Why earlier traces were empty**  
   We were attaching to the wrong PID (because `pgrep -f switchd` can match the tracer’s own command line) and/or only one thread. Fixing PID selection + attaching to all threads made the trace usable.

2. **Why TX/RX “doesn’t show a BDE call” right after TUN read**  
   After `read(/dev/net/tun)`, the packet is likely copied into a DMA buffer and enqueued by **memory writes** to DMA descriptors / rings (no syscall boundary). The observable syscalls are mainly: TUN `read`/`write` and BDE interrupt/sem ioctls.

3. **Next steps**
   - Use the syscall trace to map: which TUN fd corresponds to which interface (requires tracing init-time TUN ioctls or inspecting switchd internals).
   - Use Ghidra (`FindPacketTxPath.java`) to connect the in-process code path between TUN read and the DMA enqueue / BDE interaction.

## How to capture read/write/ioctl

1. **Trace set**  
   The on-switch script now traces **read, write, ioctl, poll, ppoll, select, epoll_wait, pselect6, epoll_pwait**. If switchd sits in `epoll_wait()` and only occasionally does I/O, we’ll see the wakeups and the following syscalls.

2. **Run the trace** (from your machine, with SSH auth):
   ```bash
   SSHPASS='yourpassword' ./scripts/reverse-engineering/run-packet-io-trace-10.1.1.233.sh 10.1.1.1
   ```

3. **If the main trace still has only 2 lines**, run a **probe** to confirm strace can see any syscalls (5s of all syscalls):
   ```bash
   DO_PROBE=1 SSHPASS='yourpassword' ./scripts/reverse-engineering/run-packet-io-trace-10.1.1.233.sh 10.1.1.1
   ```
   Then check `traces/packet-io-probe-10.1.1.233.log`. If the probe has many lines, strace works and the main trace filter or timing is the issue. If the probe also has only 2 lines, check **ptrace_scope** (script prints it) and disk space.

4. **On the switch** the script prints `ptrace_scope` (0 = allow attach) and disk space; fix low space or ptrace before re-running.

## Commands when SSH is available

```bash
# Re-run packet I/O trace (from repo, with password)
SSHPASS='yourpassword' ./scripts/reverse-engineering/run-packet-io-trace-10.1.1.233.sh 10.1.1.1

# On the switch: check ptrace (0 = allow attach to any process)
ssh cumulus@10.1.1.233 'cat /proc/sys/kernel/yama/ptrace_scope'
```

## Artifacts

| File | Description |
|------|-------------|
| `packet-io-trace-10.1.1.233.log` | Raw strace output (read/write/ioctl only). |
| `packet-io-summary-10.1.1.233.txt` | Extracted reads, writes, ioctls + first 80 lines (empty in this run). |

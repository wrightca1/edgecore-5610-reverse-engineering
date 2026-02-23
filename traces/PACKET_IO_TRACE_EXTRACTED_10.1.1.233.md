# Packet I/O trace extraction — 10.1.1.233

**Source**: `packet-io-trace-10.1.1.233.log` (20,367 lines), switchd PID 19036, 25s strace of read/write/ioctl and select/poll/epoll.

**Capture note**: Strace reported "Process 19036 attached with 9 threads" and some later PTRACE_ATTACH "Operation not permitted"; the log still contains syscalls from 11 TIDs (19036, 19037, 19038, 19039, 19040, 19057, 19058, 19070, 19072, 19088, 19089), so the trace is complete for the threads that perform packet I/O and BDE ioctls.

---

## 1. File descriptor map (from live switch)

| fd   | device / role |
|------|----------------|
| 14   | `/dev/linux-user-bde` (BDE) |
| 15   | `/dev/mem` (MMIO) |
| 18   | (in TUN select set; likely `/dev/net/tun`) |
| 20–71| `/dev/net/tun` (52 TUN devices) |

**Select() read sets** (distinct patterns):

- **Main/control**: `select(73, [4 8 10 12 72], [], [8 10 12], …)` — fds 4,8,10,12,72 (pipes/sockets/control).
- **TUN I/O**: `select(72, [18 20 21 22 … 71], [], [20 21 … 71], …)` — fd 18 + 20–71 (all TUN + one other).

---

## 2. Thread roles (TID → syscalls)

| TID   | read(20) | write(20) | ioctl(14) | Role |
|-------|----------|-----------|-----------|------|
| 19089 | 28       | 0         | 0         | **TUN read thread** (kernel→switchd) |
| 19088 | 0        | 3         | 181       | **TUN write thread** (switchd→kernel) |
| 19039 | 0        | 0         | 7150      | BDE SEM_OP / WAIT_FOR_INTERRUPT (heavy) |
| 19036 | 0        | 0         | 2047      | BDE ioctls + main select([4 8 10 12 72]) |
| 19058 | 0        | 0         | 1396      | BDE ioctls |
| 19072 | 0        | 0         | 1243      | BDE ioctls |
| 19070 | 0        | 0         | 15        | BDE ioctls |
| 19057 | 0        | 0         | 13        | BDE ioctls |
| 19040 | 0        | 0         | 9         | BDE ioctls |

So: **one thread (19089) does all TUN reads**, **one thread (19088) does all TUN writes**. Others do BDE and control.

---

## 3. BDE ioctl usage

**Ioctl codes observed** (fd 14 = BDE):

| Code (hex)    | Name (linux-user-bde.h)   | Count (approx) |
|---------------|---------------------------|-----------------|
| 0x20004c08    | LUBDE_USLEEP              | 801             |
| 0x20004c09    | LUBDE_WAIT_FOR_INTERRUPT  | 3571            |
| 0x20004c0a    | LUBDE_SEM_OP              | 7682            |

**Third argument (pointer)** — per-thread or per-ring context; examples:

- `0x4c754608` / `0x4c754718` — thread 19039 (SEM_OP / WAIT_FOR_INTERRUPT).
- `0x4c778428` / `0x4c778498` / `0x4c778588` / `0x4c778598` — LUBDE_USLEEP / SEM_OP (e.g. 19058).
- `0x4c869748` / `0x4c7544a8` — thread 19088 (TUN write thread; SEM_OP around write).
- `0x4c8450d8` / `0x4c845138` / `0x4c845618` — thread 19072.
- `0x4c79c738` — thread 19070.
- `0xbfb58fd8` / `0xbfb590c8` etc. — stack addresses (main thread 19036).

So BDE is used for **interrupt wait** and **semaphore** sync around DMA/rings, not for raw packet read/write.

---

## 4. Canonical TX path (kernel → switchd → ASIC)

**Observed sequence** (one example, timestamps trimmed):

1. **19089** (TUN read thread): `select(72, [18 20 21 … 71], [], [20…71], NULL)` → **resumed** `) = 1 (in [20])`.
2. **19089**: `read(20, 0x48655018, 16384) = 82`.
3. **19089**: `read(20, 0x48659098, 16384) = -1 EAGAIN` (non-blocking drain).
4. **19089**: `select(72, [18 20 … 71], [], [20…71], {0,0}) = 0 (Timeout)` then `select(..., NULL)` again (block).

**Interpretation**: One thread blocks in `select()` on all TUN fds; when fd 20 is readable it **read()**s one packet (82 bytes). No further syscalls from this thread for that packet — TX to ASIC is in-process (DMA/ring enqueue, no ioctl for the packet itself).

**TX read sizes**: 42 (9×), 82 (1×), 122 (1×) — consistent with small frames (e.g. ARP 42, ICMP 82, or with header 122).

---

## 5. Canonical RX path (ASIC → switchd → kernel)

**Observed sequence** (one example):

1. **19088** (TUN write thread): `<... ioctl resumed> , 0x4c869748) = 0` (SEM_OP completes).
2. **19088**: `write(20, 0x4828f604, 60) = 60`.
3. **19088**: `ioctl(14, 0x20004c0a, ...)` (next SEM_OP).

**Another**:

1. **19089**: `read(20, …, 16384) = 42` (TX path).
2. **19088**: `write(20, 0x4828b584, 82) = 82` (RX path, ~0.5 ms later).
3. **19088**: `ioctl(14, 0x20004c0a, ...)`.

**Interpretation**: RX path: BDE interrupt/sem (ioctl 9/10) → thread 19088 gets RX buffer → **write(fd=20, buf, len)** to TUN. Same TUN fd 20 used for both TX read and RX write in these samples.

**RX write sizes**: 60 (1×), 82 (2×).

---

## 6. Raw sequence samples (copy-paste from trace)

### 6.1 TX: select → read (fd 20)

```
[pid 19089] 20:48:12.585100 <... select resumed> ) = 1 (in [20])
[pid 19089] 20:48:12.585182 read(20, 0x48655018, 16384) = 82
[pid 19089] 20:48:12.585296 read(20, 0x48659098, 16384) = -1 EAGAIN (Resource temporarily unavailable)
[pid 19089] 20:48:12.585491 select(72, [18 20 21 22 ... 71], [], [20 ... 71], {0, 0}) = 0 (Timeout)
[pid 19089] 20:48:12.585741 select(72, [18 20 21 ... 71], [], [20 ... 71], NULL <unfinished ...>
```

### 6.2 TX: another (42 bytes)

```
[pid 19089] 20:48:16.237661 <... select resumed> ) = 1 (in [20])
[pid 19089] 20:48:16.237783 read(20, 0x48669298, 16384) = 42
[pid 19089] 20:48:16.238013 read(20, 0x4866d318, 16384) = -1 EAGAIN (Resource temporarily unavailable)
```

### 6.3 RX: write (60 bytes) and surrounding BDE ioctls

```
[pid 19088] 20:48:16.239198 <... ioctl resumed> , 0x4c869748) = 0
[pid 19039] 20:48:16.239241 <... ioctl resumed> , 0x4c7544a8) = 0
[pid 19088] 20:48:16.239367 write(20, 0x4828f604, 60) = 60
[pid 19088] 20:48:16.239580 ioctl(14, 0x20004c0a <unfinished ...>
[pid 19039] 20:48:16.239652 ioctl(14, 0x20004c09, 0x4c754718) = 0
```

### 6.4 RX: write (82 bytes)

```
[pid 19088] 20:48:12.248382 <... ioctl resumed> , 0x4c869748) = 0
[pid 19088] 20:48:12.248523 write(20, 0x4828b584, 82 <unfinished ...>
[pid 19088] 20:48:12.248657 <... write resumed> ) = 82
[pid 19088] 20:48:12.248740 ioctl(14, 0x20004c0a <unfinished ...>
```

---

## 7. Summary statistics (from trace)

| Metric | Value |
|--------|--------|
| Total trace lines | 20,367 |
| read(20, …) with return ≥ 0 | 11 (9×42, 1×82, 1×122) |
| read(20, …) EAGAIN | 17 (drain after each packet) |
| write(20, …) | 3 (60, 82, 82 bytes) |
| ioctl(14, 0x20004c08) | 801 (LUBDE_USLEEP) |
| ioctl(14, 0x20004c09) | 3571 (LUBDE_WAIT_FOR_INTERRUPT) |
| ioctl(14, 0x20004c0a) | 7682 (LUBDE_SEM_OP) |

---

## 8. Implications for Path B

- **TX**: TUN read (fd 20 in this run) → in-process handling → DMA/ring enqueue (no packet ioctl; BDE used for interrupt/sem only).
- **RX**: BDE interrupt/sem (ioctl 9/10) → thread 19088 gets buffer → **write(fd=20, buf, len)** to TUN.
- **BDE**: LUBDE_WAIT_FOR_INTERRUPT and LUBDE_SEM_OP dominate; LUBDE_USLEEP present. No “send packet” / “receive packet” ioctl — packets go via shared memory (DMA rings) and ioctls are for synchronization.
- **TUN fd 20**: Used for both TX (read) and RX (write) in this trace; other TUN fds (21–71) are in the select set but only 20 showed activity in this 25s window.
- **Next**: Map TUN fd index to port/interface (e.g. via switchd init or TUNGETIFF); in Ghidra, tie TUN read return to opennsl_tx / DMA enqueue and RX DMA completion to TUN write.

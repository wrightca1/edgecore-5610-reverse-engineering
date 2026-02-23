# Tracing Packet I/O (TX/RX Path) on Live Switch

**Purpose**: Get exact TX and RX code path for Path B.  
**When**: Run on a Cumulus (or switchd) box with working swp interfaces.

---

## 1. Prerequisites

- Switch running Cumulus (or your switchd), at least one swp up.
- `strace`; optional `ltrace`.

---

## 2. Capture TX Path (CPU to Port)

### Find switchd and fds

```bash
PID=$(pgrep -xo switchd)
ls -la /proc/$PID/fd | grep -E "tun|bde|mem"
```

### Strace TX

```bash
# IMPORTANT: switchd is multi-threaded; attach to all threads or you may miss packet I/O.
PARGS=""
for tid in $(ls /proc/$PID/task); do PARGS="$PARGS -p $tid"; done
strace -f -e trace=read,write,ioctl,poll,ppoll,select,epoll_wait,pselect6,epoll_pwait $PARGS -s 200 2>&1 | tee /tmp/switchd_tx.log
```

In another terminal:

```bash
ping -c 1 -I swp1 10.0.0.2
```

Stop strace. Then:

```bash
grep "read.*= [0-9]" /tmp/switchd_tx.log
grep -A 5 "read(2[0-9]," /tmp/switchd_tx.log
```

**Record**: Fd used for the TUN read that returns packet length; the **next** syscalls (ioctl which fd/request, or write).

### Ltrace (if available)

```bash
ltrace -f -e 'opennsl_*' -p $PID 2>&1 | tee /tmp/switchd_ltrace_tx.log
# Then: ping -c 1 -I swp1 <target>
```

Look for `opennsl_tx` or `bcm_*` with buffer/length.

---

## 3. Capture RX Path (Port to CPU)

Run strace again; generate a packet that will be received (e.g. ping from another host to switch swp1 IP):

```bash
PARGS=""
for tid in $(ls /proc/$PID/task); do PARGS="$PARGS -p $tid"; done
strace -f -e trace=read,write,ioctl,poll,ppoll,select,epoll_wait,pselect6,epoll_pwait $PARGS -s 200 2>&1 | tee /tmp/switchd_rx.log
```

Look for **write(fd, buf, len)** to a TUN fd (switchd injecting to kernel). Then see what **read** or **ioctl** happened **before** that (on BDE or other fd).

**Record**: Which fd and syscall deliver the packet before the TUN write; ioctl request if any.

---

## 4. Interpret Results

| After TUN read (TX) | Likely meaning |
|--------------------|----------------|
| ioctl(BDE_fd, ...) | Packet sent via BDE ioctl; need request code and payload. |
| ioctl(KNET_fd, ...) | Packet sent via KNET ioctl (even if no KNET netdevs). |

| Before TUN write (RX) | Likely meaning |
|------------------------|----------------|
| read(BDE_fd, ...) | Packet from BDE read (ring or message). |
| ioctl(BDE_fd/KNET_fd, ...) | Packet from ioctl response. |

---

## 5. BDE vs KNET

- BDE: `/dev/linux-user-bde` (major 126). Register access.
- KNET: `/dev/linux-bcm-knet`. Cumulus typically does **not** load it. If you see no KNET fd, path is BDE-only.

---

## 6. Next Steps

1. Save the exact sequence (fds, ioctl codes) under `docs/reverse-engineering/traces/`.
2. In Ghidra, find that ioctl in switchd/libopennsl and follow buffer format.
3. Update PATH_B_INFORMATION_CHECKLIST.md §4 with findings.

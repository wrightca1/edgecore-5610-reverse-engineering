# Packet I/O Mechanism: Verified

**Date**: 2026-02-17  
**Method**: strace, lsof, live switch testing  
**Result**: Cumulus uses **TUN devices** for CPU ↔ port packet I/O (not KNET)

---

## Correction: swp Are TUN From the Start (Never Dummy)

Earlier analysis suggested swp might be "virtual netdevs" or created with `ip link add type dummy`. **That was wrong.**

**Verified on switch:**
- Every swp1–swp52 has **tun_flags** in sysfs (`/sys/class/net/swpN/tun_flags`) → they are **TUN** interfaces.
- eth0 has no tun_flags. Only swp* have tun_flags.
- The **dummy** kernel module is **not loaded** on Cumulus.
- switchd creates swp by opening `/dev/net/tun` and `ioctl(TUNSETIFF, "swp1")` etc. They are TUN from creation, not dummy.

---

## Summary

**swp interfaces are TUN devices.** switchd opens one `/dev/net/tun` fd per swp interface (52 total). Packets flow:

- **TX (CPU → port)**: Kernel writes to TUN → switchd reads from TUN fd → SDK/BDE → ASIC TX
- **RX (port → CPU)**: ASIC punt → BDE → switchd → switchd writes to TUN fd → kernel delivers to app

---

## Evidence

### 1. switchd File Descriptors

```
fd 14  -> /dev/linux-user-bde   (BDE device for ASIC access)
fd 15  -> /dev/mem
fd 20  -> /dev/net/tun          (swp1)
fd 21  -> /dev/net/tun          (swp2)
...
fd 71  -> /dev/net/tun          (swp52)
```

52 TUN fds = 52 swp interfaces.

### 2. Strace During ping -I swp1

**TX (ping sends ICMP request):**
```
[pid 8453] read(20, 0x48747598, 16384) = 98    ← switchd reads packet from TUN fd 20
```
Kernel routes packet to swp1 → writes to TUN → switchd reads it.

**RX (ping receives ICMP reply):**
```
[pid 8452] write(20, 0x4832c984, 94) = 94      ← switchd writes packet to TUN fd 20
[pid 8452] write(20, 0x48330a04, 98) = 98
```
ASIC punts reply → switchd receives via BDE → writes to TUN → kernel delivers to ping.

### 3. Flow Diagram

```
TX (CPU → Port):
  ping → sendmsg(socket) → kernel routes to swp1
       → kernel writes to TUN fd 20
       → switchd read(20) = packet
       → switchd calls SDK packet TX (bcm_* / BDE)
       → BDE DMA to ASIC
       → ASIC transmits on port 1

RX (Port → CPU):
  ASIC receives packet, L3 lookup = punt (host route)
       → BDE DMA to CPU
       → switchd gets packet (SDK RX / BDE read or poll)
       → switchd write(20, packet)
       → kernel delivers to swp1
       → ping receives
```

---

## How It's Commanded

### Table Programming (switchd → ASIC)

- Netlink: RTM_NEWROUTE, RTM_NEWNEIGH, RTM_NEWLINK
- switchd parses → bcm_l3_route_add, bcm_l3_host_add, bcm_l3_egress_create, bcm_port_enable_set
- BDE ioctl(fd 14, 0x20004c0a, ...) for register/table access

### Packet I/O (CPU ↔ ASIC)

- **TX**: read(fd 20..71) from TUN → SDK packet TX API → BDE
- **RX**: BDE delivers packet → switchd → write(fd 20..71) to TUN

---

## Implications

1. **No KNET** – Cumulus uses TUN, not linux-bcm-knet.ko
2. **One TUN per port** – fd 20 = swp1, fd 21 = swp2, etc.
3. **switchd owns packet path** – It bridges TUN (Linux) and BDE (ASIC)
4. **Implementable** – Create TUN devices, use SDK packet APIs with BDE for TX/RX

---

## SDK APIs Involved (Inferred)

- Packet TX: `bcm_rx_*` or `bcm_pkt_*` or equivalent (to send to ASIC)
- Packet RX: BDE interrupt/poll + SDK RX callback or similar
- TUN creation: `open("/dev/net/tun")` + `ioctl(TUNSETIFF)` with interface name "swp1", etc.

---

## Verification Commands

```bash
# Confirm TUN fds
sudo ls -la /proc/$(pgrep -f 'switchd -d')/fd | grep tun

# Trace packet flow
sudo strace -p $(pgrep -f 'switchd -d') -e trace=read,write -f &
ping -c 2 -I swp1 10.101.101.2
```

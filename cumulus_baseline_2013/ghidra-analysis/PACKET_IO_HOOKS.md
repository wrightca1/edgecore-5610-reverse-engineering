# Packet I/O Hooks — switchd ↔ Linux

How switchd catches packets punted by the ASIC and forwards them to
Linux swp* netdevs, and how it picks up packets from Linux for transmission.

## Architecture: TUN devices (not KNET)

Cumulus 2.5.0 uses the **TUN device** approach. switchd opens
`/dev/net/tun` 52 times, once per swp*. The BCM SDK has an alternative
**bcm_knet** mechanism (kernel netif via `bcm_knet.ko`) but Cumulus
doesn't load that module — only `linux-kernel-bde.ko` + `linux-user-bde.ko`.

The bcm_knet code IS statically compiled into switchd (we found
`bcm_knet_init`, `bcm_knet_filter_create`, `bcm_knet_netif_create`,
etc.) — it's just not active.

## RX path: ASIC → TUN

### The RX callback — `FUN_101b8f54` (332 bytes)

Registered with the BCM SDK via:
```c
bcm_rx_unregister(unit, FUN_101b8f54, 0xff);
// (bcm_rx_register has the same signature — same callback)
```

The callback is **producer-consumer with ring buffer**:

```c
int rx_callback(void *userdata, void *pkt /*bcm_pkt_t*/, int unit_ctx) {
    int max_packets = unit_ctx->ring_max;          // +0x909c
    
    if (unit_ctx->enqueue_enabled == 0)            // +0x90b0
        return BCM_RX_NOT_HANDLED /*= 1*/;
    
    // Copy BCM packet struct into next ring slot (0x1f8 = 504 bytes per slot)
    bcm_pkt_t *slot = &unit_ctx->ring_base[unit_ctx->head * 0x1f8];   // +0x90a4 / +0x90b4
    memcpy(slot, pkt, 0x1f8);
    slot[0] = (int)&slot[0x42];   // packet data pointer fixup
    
    int new_count = ++unit_ctx->head;
    
    // If ring is filling up and worker idle, wake the worker thread
    if (new_count >= max_packets && !unit_ctx->worker_busy) {
        unit_ctx->enqueue_enabled = 0;             // back-pressure
        unit_ctx->worker_busy = 1;                 // +0x908c
        sem_give(unit_ctx->worker_sem);            // +0x9094
    }
    
    return BCM_RX_HANDLED_OWNED /*= 3*/;  // we now own this packet
}
```

This is a **lock-free fast path** — the callback runs in interrupt/poll
context and just enqueues. The slow path (TUN write) runs in a separate
worker thread.

### Unit RX context struct layout (size 0x90c8 = 36,936 bytes)

Inferred from offsets used:

| Offset | Field | Type |
|---|---|---|
| `+0x908c` | `worker_busy` | int |
| `+0x9094` | `worker_sem` (37000 dec = 0x9094 hex) | sem handle |
| `+0x909c` | `ring_max` (max packets in ring) | int |
| `+0x90a4` | `ring_base` (pointer to ring buffer) | bcm_pkt_t * |
| `+0x90b0` | `enqueue_enabled` | int |
| `+0x90b4` | `head` (write index) | int |

The ring buffer is N slots × 0x1f8 (504 bytes) per slot. Each slot
stores the entire BCM packet metadata struct + a pointer to packet data
at slot offset `0x42 * 4 = 264 bytes` from slot start.

### Worker thread → TUN write — `FUN_1002b8cc` (744 bytes)

Source: `nic.c:0x17a, 0x199, 0x1a6`

```c
void rx_to_tun(int port_ctx_idx, packet_t *packet) {
    void *buf = packet->data;
    
    if (packet->flags & 1) {                     // needs copy to bounce buffer
        if (packet->length > PKT_BUF_SZ /*=0x4000=16K*/)
            assert("packet->length < PKT_BUF_SZ");
        memcpy(bounce_buf, packet->data, packet->length);
        buf = bounce_buf;
        packet->length = 0x4000;
    }
    
    if (packet->flags & (4|8)) {                 // preprocessing
        FUN_1002b48c(port_ctx_idx, packet);      // probably VLAN/QoS rewrite
    }
    
    if (packet->flags & 2) return;               // drop flag
    
    int tun_fd = tap_fds[port_ctx_idx * 0x200];  // port-ctx is 0x200 bytes each
    
    if (packet->tag == 0) {
        // Simple write — no VLAN tag insertion
        ssize_t n = write(tun_fd, buf, packet->length);
        if (n < 1) log_drop("nic.c:0x199 tapdev queue full");
    } else {
        // VLAN tag insertion via writev() scatter-gather
        struct iovec iov[3] = {
            { buf,                      12 },    // dst+src MAC headers
            { &packet->tag,             4 },    // 802.1Q tag (4 bytes)
            { buf + 12,  packet->length - 12 }  // rest of frame
        };
        ssize_t n = writev(tun_fd, iov, 3);
        if (n < 1) log_drop("nic.c:0x1a6 tapdev queue full");
    }
}
```

**This is how punted packets land in Linux:**
1. write the BCM packet's raw bytes to the right TUN fd
2. Linux's TUN driver delivers it as a netdev RX skb on swp{N}
3. Linux IP stack processes it normally

### Port context array layout (size 0x200 = 512 bytes)

`DAT_11e46f24` is the base of an array of port-context structs.
`tap_fds[port * 0x200]` reads the TUN fd as the first int of that struct.

Per-port stats and state visible:
| Offset | Field |
|---|---|
| `+0x000` | TUN fd (int) |
| `+0x198/0x19c` | read error counter (64-bit) |
| `+0x1a0/0x1a4` | TX drop counter (tapdev queue full, 64-bit) |
| (other offsets are stats/buffers) |

## TX path: Linux → ASIC

### The TUN-read driver — `FUN_1002b044` (1096 bytes)

Source: `nic.c:0xe5, 0xfc, 0x100, 0x104, 0x11b`

Called when `select()` shows a TUN fd readable:

```c
void tun_to_tx_read(int fd, uint poll_mask, int port_ctx) {
    if (poll_mask & 4) return;  // POLL_ERR
    if (!(poll_mask & 1)) assert("mask & POLL_MASK_READ");
    
    int pkt_count = 0;
    packet_t *chain_tail = NULL;
    int chain_head_idx;
    
    do {
        // Find next free slot in the global tx_ring
        int next_tail = (tx_ring_tail + 1) % RB_SZ /*=128*/;
        if (tx_ring_head == next_tail) {
            log("nic.c:0xfc Tx_Ring queue full");
            break;
        }
        
        // Get next packet buffer
        packet_t *pkt = tx_ring_slots[tx_ring_tail];
        pkt->length = PKT_BUF_SZ /*=0x4000*/;
        if (pkt == NULL) assert("packet");
        
        // Read from TUN
        ssize_t n = read(fd, pkt->data, pkt->length);
        if (n < 0) {
            if (errno == EAGAIN) break;
            log("nic.c:0x104 read error errno %d");
            port_ctx->read_errors++;
            if (errno == ENOTCONN /*0x4d*/)
                FUN_100461bc(fd);  // reset fd
            break;
        }
        if (n > 0) {
            pkt->length = n;
            // Link into per-call chain
            if (chain_tail == NULL) chain_head_idx = tx_ring_tail;
            else chain_tail->next = pkt;        // chain via slot+0x1c
            pkt_count++;
            tx_ring_tail = next_tail;
            chain_tail = pkt;
        }
    } while (n > 0);
    
    if (pkt_count > RB_SZ) assert("pkt_count <= RB_SZ");
    
    if (pkt_count > 0) {
        chain_tail->next = NULL;
        // Hand off to TX (calls bcm_tx with the chain — not shown here)
        ...
    }
}
```

### Constants

* `RB_SZ = 0x80 = 128` — TX ring slot count
* `PKT_BUF_SZ = 0x4000 = 16 KB` — max single-packet length
* Packet struct fields: `flags @ 0`, `length @ 4`, `data @ 8`, `tag @ 12`,
  ..., `next @ 0x1c` (chain pointer)
* `errno == EAGAIN (0xb)` — no more data, normal exit
* `errno == ENOTCONN (0x4d)` — fd corruption, trigger reset

## TUN device creation — `FUN_10008ae8` (988 bytes)

Source: `tuntap.c:0x22, 0x3e`

Already documented earlier. Called once per swp*:

```c
int create_tun(char *name, void *mac) {
    int fd = open64("/dev/net/tun", O_RDWR);
    struct ifreq ifr = { .ifr_flags = IFF_TUN | IFF_NO_PI };  // = 0x300e
    strncpy(ifr.ifr_name, name, IFNAMSIZ);
    ioctl(fd, TUNSETIFF /*=0x800454ca*/, &ifr);
    if (mac && memcmp(mac, &zero, 6) != 0) {
        ifr.ifr_hwaddr = *mac;
        ioctl(fd, SIOCSIFHWADDR /*=0x8927*/, &ifr);
    }
    return fd;
}
```

## TUN socket creator — `FUN_10008ec4` (516 bytes)

Source: `tuntap.c:0x...` — creates the AF_NETLINK ioctl socket used
for `ip link` operations on the swp* devices. The "Couldn't create
tuntap ioctl socket" log message comes from here.

## Complete data flow (end-to-end)

```
═══════════════════════════════════════════════════════════════════
RX (ASIC → kernel)
═══════════════════════════════════════════════════════════════════
Wire on swp1 → BCM Trident+ ASIC
  iPipe parser + L2/L3 lookup
  My_Station_TCAM hit → terminate at L3
  L3 → trap to CPU port
  MMU buffer → CMIC CoS-2 RX queue
  DMA into host RAM RX descriptor ring
  CMIC raises IRQ 16 (linux-kernel-bde)
    ↓
linux-kernel-bde.ko _ether_interrupt()
  mask IRQ in HW
  wake_up(&_ether_interrupt_wq)
    ↓
switchd's RX thread blocked in LUBDE_WAIT_FOR_INTERRUPT
  returns from ioctl
  BCM SDK RX poller reads RX descriptors
  for each packet:
    calls rx_callback FUN_101b8f54 ← our hook
      copies packet to ring at unit_ctx[+0x90a4]
      head++ at +0x90b4
      if full: sem_give(worker_sem at +0x9094)
      return BCM_RX_HANDLED_OWNED (3)
    ↓
Worker thread "rxmon" blocked on worker_sem
  wakes up → drains ring
  for each packet:
    determines source port (from packet meta)
    calls rx_to_tun FUN_1002b8cc ← our hook  [nic.c:0x17a]
      writes packet to tap_fds[port*0x200] via write() or writev()
    ↓
TUN driver in kernel
  injects skb as RX on swp{N}
  ↓
Linux IP stack: route lookup, app delivery

═══════════════════════════════════════════════════════════════════
TX (kernel → ASIC)
═══════════════════════════════════════════════════════════════════
Application sends packet
  Linux IP stack → route → swp{N} netdev
  TUN driver queues packet
    ↓
switchd's main select() loop
  TUN fd N becomes readable
  switchd calls tun_to_tx_read FUN_1002b044 ← our hook  [nic.c:0xe5]
    loops reading from fd into tx_ring[tail]
    chains packets via pkt->next at +0x1c
    when EAGAIN or chain has packets:
      hand chain to BCM SDK TX
      → bcm_tx(unit, chain_head)
        builds TX DCB for each packet
        DMA descriptor to CMIC TX queue
    ↓
CMIC DMA engine → ASIC ingress (from CPU port)
  L2/L3 lookup → egress port selection
  out the wire on swp{egress}
```

## Files

* `switchd_rx_callback_decomp.c` — the RX callback + related funcs
* `switchd_rxtx_decomp.c` — 16 functions (TUN setup, RX/TX hot path)
* `switchd_rxtx_callers.txt` — function listing
* `switchd_packet_io_decomp.c` — earlier PLT analysis
* `switchd_packet_io_clues.txt` — string xrefs for tuntap.c / bcm_knet
* `scripts/PacketIO.java`, `FindRxTxPath.java`, `DecompileRxCallback.java`

## Source files now confirmed (from leaked strings)

| Path | What |
|---|---|
| `nic.c` | switchd's NIC/packet I/O glue (the `rx_to_tun`/`tun_to_tx_read` we decoded) |
| `tuntap.c` | TUN device creation helpers |
| `bcm-sdk/src/...rx.c` | BCM SDK RX (statically linked in switchd) |

## EdgeNOS mapping

| Cumulus function | EdgeNOS equivalent |
|---|---|
| `FUN_101b8f54` (rx_callback) | `bmd_rx_callback()` in newnos/asic/openmdk/bmd |
| `FUN_1002b8cc` (rx_to_tun) | newnos packet-RX dispatcher to TUN |
| `FUN_1002b044` (tun_to_tx_read) | newnos TUN read → bmd_tx_pkt() |
| `FUN_10008ae8` (tun create) | EdgeNOS TUN-init in switchd-equivalent |
| `bcm_rx_register` | `bmd_rx_register()` in OpenMDK |

EdgeNOS already implements this pattern; we now have switchd's exact
constants and offsets to match.

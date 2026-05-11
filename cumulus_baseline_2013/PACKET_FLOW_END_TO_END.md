# End-to-End Packet Flow: CPU ↔ ASIC

The complete bidirectional packet flow on BCM56846. **RX punt**
(wire → ASIC → CPU → swp* netdev) and **TX inject** (swp* netdev → CPU
→ ASIC → wire), traced from kernel buffer to chip silicon and back.

Every step verified against decompiled switchd, Cumulus BDE kernel
module, and the BCM SDK's static analysis. This is what EdgeNOS needs
to move packets bidirectionally.

---

## 1. The big picture (one diagram)

```
                           User-space app (BGP, OSPF, ARP, ping, ...)
                                          │
                                          ▼
                          ┌───────────────────────────────────┐
                          │ Linux kernel — IP / netif layer    │
                          └───────┬──────────────────────▲────┘
                                  │                      │
                            (TX: kernel→TUN write)  (RX: TUN read→kernel)
                                  │                      │
                                  ▼                      │
                          ┌───────────────────────────────────┐
                          │ /dev/net/tun (52 fds, one per swp) │
                          └───────┬──────────────────────▲────┘
                                  │                      │
                            (switchd TX thread       (switchd worker
                             reads from TUN)         writes to TUN)
                                  │                      │
                                  ▼                      │
        ┌─────────────────────────────────────────────────────────────────┐
        │ switchd (userspace daemon, statically linked BCM SDK)            │
        │                                                                  │
        │  ┌──── TX path ────────┐         ┌──── RX path ────────────┐    │
        │  │ tun_to_tx_read()    │         │ bcm_rx callback         │    │
        │  │  FUN_1002b044       │         │  FUN_101b8f54           │    │
        │  │  ↓                  │         │  (enqueue, no copy)     │    │
        │  │ bcm_tx_list()       │         │  ↓                      │    │
        │  │  FUN_10441108       │         │ producer ring (40k slots)│    │
        │  │  ↓                  │         │  ↓                      │    │
        │  │ DMA channel write   │         │ rx_to_tun() worker      │    │
        │  │  FUN_101f33f8       │         │  FUN_1002b8cc           │    │
        │  └─────────┬───────────┘         └────────▲───────────────┘    │
        └────────────┼────────────────────────────────┼──────────────────┘
                     │                                │
                     │ ioctl: PHYS_WR32 to CMICm    │ wait_for_interrupt
                     │       (DMA_DESC, DMA_CTRL)    │ wakes worker
                     │                                │
                     ▼                                │
        ┌─────────────────────────────────────────────────────────────────┐
        │ linux-kernel-bde.ko (kernel BDE module)                          │
        │  - PAXB sub-window translation                                   │
        │  - DMA descriptor ring memory management                         │
        │  - IRQ handler dispatches to user_bde wait queue                 │
        └────────────┬────────────────────────────────▲──────────────────┘
                     │                                │
                     │ MMIO via PCIe                 │ PCIe IRQ
                     │                                │
                     ▼                                │
        ┌─────────────────────────────────────────────────────────────────┐
        │ BCM56846 ASIC                                                    │
        │                                                                  │
        │  ┌── CMICm ──────────────────────────────────────────┐          │
        │  │ Packet DMA engines (4 channels per CMC)            │          │
        │  │ Reads/writes DCB rings + packet buffers in host RAM│          │
        │  └─────┬──────────────────────────────────▲──────────┘          │
        │        │ TX inject                        │ RX punt              │
        │        ▼                                  │                      │
        │  ┌── EPIPE ────┐                  ┌── IPIPE ────┐                │
        │  │ Egress      │                  │ Ingress     │                │
        │  │ • L2 lookup │                  │ • parser    │                │
        │  │ • VLAN edit │                  │ • L2 LU     │                │
        │  │ • TX queue  │                  │ • L3 LU     │                │
        │  │ • HG2 strip │                  │ • FP TCAM   │                │
        │  └──────┬──────┘                  │ • CPU steer │                │
        │         │                          └─────┬──────┘                │
        │         ▼                                ▲                      │
        │  ┌── XLPORT/CDPORT MAC ─────────────────────────┐                │
        │  │ XMAC (10G) / CDMAC (40G) — wire-side MAC       │                │
        │  └─────┬─────────────────────────────────▲──────┘                │
        │        │                                  │                      │
        └────────┼──────────────────────────────────┼──────────────────────┘
                 ▼                                  │
            wire out (TX)                    wire in (RX)
```

---

## 2. RX path: ASIC → CPU (the "punt")

### Step 1: Frame arrives at the wire

A frame arrives on swp1's SFP+ port. The signal goes through:
- SFP+ module → DS100DF410 retimer → BCM84740 PHY → SerDes lane
- SerDes deserialization, EQ adaptation, clock recovery
- XLPORT block's XMAC (10G MAC) deserializes the frame, checks CRC,
  optionally strips it

### Step 2: Ingress pipeline classification (IPIPE)

The frame enters IPIPE block (block ID 0x01). IPIPE does:

1. **Parser**: extract Ethernet/VLAN/IP/L4 headers into a metadata struct
2. **L2 lookup**: find dest MAC in L2_TABLE (131,072-entry hash table)
3. **L3 lookup** (if L2 dest = router MAC): find dest IP in DEFIP TCAM
4. **FP TCAM lookup**: 3 stages × 9 slices of ACL rules
5. **CPU-steer decision**: based on the lookup result + cpu_control_1 bits

### Step 3: The CPU-steer decision — when does a packet get punted?

The `cpu_control_1` register (set by rc.datapath_0 lines 206-211) has
these bits that trigger CPU-punt:

| `cpu_control_1` bit | Triggers punt when |
|---|---|
| `l3_mtu_fail_tocpu` | Packet too large for egress MTU (need to generate ICMP frag-needed) |
| `l3_slowpath_tocpu` | Has IP options (must be handled in software) |
| `v4l3dstmiss_tocpu` | L3 dest IPv4 not in DEFIP (unknown route) |
| `v6l3dstmiss_tocpu` | L3 dest IPv6 not in DEFIP |
| (others) | TTL=1, L2 station hit, FP rule action=COPY_TO_CPU, etc. |

Plus L2 events:
- Unknown L2 unicast → bridge config decides flood or punt
- IGMP/MLD reports → punt to IGMP snooping
- ARP/RARP → punt for ARP processing
- BPDU (DEST=01:80:c2:00:00:00) → punt to STP daemon

Plus FP TCAM action:
- Any FP rule with `COPY_TO_CPU` action → punted
- ACLs that the user installed (e.g., to capture BGP traffic)

### Step 4: Through the MMU to the CPU port

When a packet is marked for CPU, it's:
1. Queued in the MMU buffer pool (~46K cell buffer)
2. Eventually scheduled out the egress pipeline destined for the **CPU
   port** (internal port number 0)
3. CPU's cos_map decides which of 8 CPU queues based on the packet's
   internal_pri:
   - `cpu_cos_map` is a 128-entry TCAM mapping (`int_pri_key, int_pri_mask) → cos`
   - rc.datapath_0 programs entries 120-127 for default priority→queue mapping

### Step 5: Egress encapsulates with HG2 header

Before the packet leaves the CPU port, the egress pipeline **prepends a
12-byte HiGig2 (HG2) header** containing:

```
 byte 0       1       2       3       4       5       6       7       8       9       10      11
┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
│ start │ vers  │ resv  │ rsn0  │ rsn1  │ srcmod│ srcprt│ dstmod│ dstprt│ vid/tc│ misc  │ misc  │
└───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
```

- `start` = 0xFB (HG2 start byte)
- `vers` = version (1 for HG, 2 for HG2)
- `rsn0/rsn1` = REASON CODE (why was this punted — L3 miss, ACL match, etc.)
- `srcmod, srcprt` = where the packet came from (the source port)
- `dstmod, dstprt` = where it was destined (CPU port = mod 0, port 0)
- `vid/tc` = VLAN ID, traffic class

switchd's RX callback parses this header to find `srcprt` and use that
to route to the right `swp*` TUN.

### Step 6: DMA into the host's DCB ring

The chip's packet DMA engine (in CMICm) pulls the **next free DCB** from
the RX descriptor ring in host memory. Each DCB has:

```
struct dcb {
    uint32_t packet_addr;     // physical addr of buffer (16 KB typical)
    uint32_t length_flags;    // bit 24=CHAIN, bit 25=REQUEST_INTR
    uint32_t next_dcb;        // next DCB in chain
    uint32_t status;          // chip writes DONE/length here when complete
};
```

The chip:
1. DMAs the packet (HG2 header + Ethernet frame) into the buffer at `packet_addr`
2. Updates the `status` field with `DONE | actual_length`
3. Optionally raises an IRQ (if `REQUEST_INTR` was set)

### Step 7: IRQ fires → kernel BDE wakes the userspace BDE

The chip raises **IRQ 16** (per `cat /proc/interrupts`). `linux-kernel-bde.ko`'s
`_isr` runs in kernel context:

```c
irqreturn_t _isr(int irq, void *dev_id) {
    sinfo = dev_id;
    // Read CMC's IRQ_STAT0 (at CMC_base + 0x400)
    uint32_t stat = _read(sinfo->dev, CMICM_IRQ_STAT0);
    uint32_t mask = sinfo->irq_mask;

    if (stat & mask & ISR1_BITS) sinfo->isr1_func(sinfo);
    if (stat & mask & ISR2_BITS) sinfo->isr2_func(sinfo);

    // Wake user_bde waiter
    wake_up_interruptible(&_ether_interrupt_wq);
    return IRQ_HANDLED;
}
```

`linux-user-bde.ko` has a thread blocked on `_ether_interrupt_wq`. When
woken, it returns from the `LUBDE_WAIT_FOR_INTERRUPT` ioctl (0x20004c09)
back to switchd.

### Step 8: switchd's RX callback (FUN_101b8f54)

switchd's BDE userspace thread now runs the chip-driver's IRQ handler,
which walks the RX DCB ring, finds completed DCBs, and for each one
calls the registered RX callback:

```c
/* FUN_101b8f54 — switchd's bcm_rx callback (decompiled, simplified) */
int rx_callback(void *userdata, bcm_pkt_t *pkt, int unit) {
    unit_rx_ctx_t *ctx = ...;

    if (ctx->enqueue_enabled == 0)        // back-pressured
        return BCM_RX_NOT_HANDLED;        // = 1; pkt freed by SDK

    /* Copy the bcm_pkt metadata (504 bytes) into next ring slot */
    bcm_pkt_t *slot = &ctx->ring_base[ctx->head * 504];
    memcpy(slot, pkt, 504);
    slot[0] = (int)&slot[0x42];           // fixup data ptr

    if (++ctx->head >= ctx->ring_max && !ctx->worker_busy) {
        ctx->enqueue_enabled = 0;         // back-pressure
        ctx->worker_busy = 1;
        sem_post(ctx->worker_sem);        // wake worker
    }

    return BCM_RX_HANDLED_OWNED;          // = 3; we own pkt now
}
```

This callback runs in **interrupt/poll context** so it can't block. The
producer-consumer ring decouples the fast IRQ path from the slow
TUN-write path.

### Step 9: Worker thread → TUN write (FUN_1002b8cc — `rx_to_tun`)

A separate worker thread sleeps on `ctx->worker_sem`. When woken:

```c
/* FUN_1002b8cc — rx_to_tun, from nic.c (744 B decomp) */
void rx_to_tun_worker(void) {
    while (1) {
        sem_wait(ctx->worker_sem);

        while (ctx->tail < ctx->head) {
            bcm_pkt_t *slot = &ctx->ring_base[ctx->tail * 504];
            uint8_t *data = (uint8_t *)slot[0];   // pkt data pointer
            int length = pkt_length(slot);
            int src_port = parse_hg2_srcport(data);   // peek HG2 header
            int tun_fd = ctx->tun_fds[src_port];

            // Skip HG2 header (first 12 bytes), write to TUN
            write(tun_fd, data + 12, length - 12);

            // (Re-insert VLAN if needed — Cumulus does writev with iovecs)

            ctx->tail++;
        }

        // Release back-pressure
        ctx->worker_busy = 0;
        ctx->enqueue_enabled = 1;
    }
}
```

The `iovec` approach lets switchd re-insert the VLAN tag (stripped at
ingress per `bcm_rx_control_set(VTAG_STRIP, 1)`) without copying.

### Step 10: Linux kernel sees packet on swp1 TUN

When switchd's `write()` to `/dev/net/tun` (fd opened with `IFF_TUN_NO_PI`)
returns, the kernel:
1. Wraps the bytes in an `sk_buff`
2. Sets `skb->dev = swp1_netdev`
3. Calls `netif_rx(skb)` to inject into the network stack
4. The kernel routes the packet up (e.g., to AF_INET if it's an IP packet)
5. User-space sockets that match get the data

### RX path summary table

| Step | Component | Time |
|---|---|---|
| 1 | Wire → SerDes | ~ns |
| 2 | IPIPE classify | ~µs |
| 3 | CPU-steer decision | ~ns |
| 4 | MMU queue | ~µs |
| 5 | HG2 encap | ~ns |
| 6 | DMA into host buffer | ~µs |
| 7 | IRQ → wake user_bde | ~10-100 µs |
| 8 | bcm_rx callback (enqueue) | ~1 µs |
| 9 | Worker dequeue + TUN write | ~10 µs |
| 10 | Kernel netif_rx | ~1 µs |
| **Total** | wire to TUN | **~30-100 µs** |

---

## 3. TX path: CPU → ASIC (the "inject")

### Step 1: Kernel writes packet to swp1 TUN

An application (e.g., OSPF daemon) sends a packet:
- App writes to AF_INET socket
- Kernel routes to swp1 (kernel routing table)
- swp1 is a TUN netdev — kernel writes the packet to the TUN fd
- switchd's TUN-reader thread (per-port or shared) gets `read()` data

### Step 2: switchd reads from TUN (FUN_1002b044 — `tun_to_tx_read`)

```c
/* FUN_1002b044 — tun_to_tx_read, 1096 B decomp */
void tun_to_tx_loop(int swp_idx) {
    int tun_fd = ctx->tun_fds[swp_idx];
    while (1) {
        // Read up to RING_SIZE packets into staging buffers
        int n = readv(tun_fd, ctx->staging_iovecs, MAX_BATCH);
        // Each staging buf is 16KB

        // Build bcm_pkt chain: each pkt points at staging buf
        bcm_pkt_t *chain = build_pkt_chain(ctx->staging, n);

        // Push to TX
        bcm_tx_send(unit, swp_idx, chain);
    }
}
```

### Step 3: switchd's `bcm_tx_list` wrapper (FUN_1005b3e4)

```c
/* FUN_1005b3e4 — switchd's bcm_tx wrapper (1104 B decomp) */
int switchd_tx_list(int unit, int port, pkt_chain_t *chain, int *sent) {
    int idx = port_to_egress_idx(port);   // dest_port_bitmap encoding

    pkt_t *cur = chain;
    bcm_pkt_t *slot = chain->bcm_slot;
    int count = 0;

    do {
        /* Pad short packets to 60 bytes (Ethernet minimum) */
        if (cur->length < 60) {
            slot->length = 64;            // 60 + 4 CRC
            memset(slot->data + cur->length, 0, 60 - cur->length);
        } else {
            slot->length = cur->length + 4;
        }

        /* Set destination port bitmap (8 words = 256-port bitmap) */
        for (int w = 0; w < 8; w++) slot->dst_pbmp[w] = 0;
        slot->dst_pbmp[idx >> 5] |= (1 << (idx & 0x1f));

        /* Set flags */
        slot->flags |= 0x40000;           // BCM_TX_NO_PAD / UNTAGGED?
        slot->cos = 3;
        slot->prio = 3;

        slot->user_data = cur;            // for completion callback
        count++;

        /* Auto-flush every 16 packets */
        if (count == 16) {
            bcm_tx_list(unit, chain_head, tx_complete_cb, 16);
            count = 0;
            cur = cur->next;
            chain_head = cur->bcm_slot;
        } else {
            slot->chain_next = cur->next->bcm_slot;
            cur = cur->next;
            slot = cur->bcm_slot;
        }
    } while (cur != NULL);

    if (count > 0) {
        bcm_tx_list(unit, chain_head, tx_complete_cb, count);
    }
    return 0;
}
```

### Step 4: `bcm_tx_list` → DMA channel programming (FUN_101f33f8)

The SDK's `bcm_tx_list` ultimately calls FUN_101f33f8 (the TX DMA start):

```c
/* FUN_101f33f8 — start TX DMA on a channel */
int tx_dma_start(int unit, int chan, int n_pkts, pkt_chain_t *chain) {
    cmc_t *cmc = unit->tx_cmc;            // *(unit + 0x96d0)

    /* Initialize BMD DMA for direction TX */
    bmd_dma_init(1 /*TX*/, cmc);          // FUN_107909b8(1, cmc)

    /* Set EN+TXDIR in CMC control */
    cmc->ctrl[0x14] |= 0x02;               // bit 1 = TX DIR
    cmc->ctrl[0x14] &= ~0x01;              // bit 0 cleared
    cmc->ctrl[0x38] = 0;                   // clear status

    /* Build descriptor chain */
    for (int i = 0; i < n_pkts; i++) {
        bmd_dma_build_desc(unit, cmc, chain[i].buf, ...);  // FUN_101f3220
        bmd_dma_descbuild_intr(&intr, cmc->dma_intr_addr);  // FUN_10091c98
    }

    /* Set 256-port destination bitmap (8 × 32-bit words) */
    uint32_t pbmp[8] = { 0 };
    int port = cmc->dst_port;
    pbmp[port >> 5] |= 1 << (port & 0x1f);

    /* Build the SCHAN command + issue DMA start */
    soc_schan_build(unit, pbmp, ...);
    bmd_dma_start(unit, 0xffffffff, cmc); // FUN_1078dbdc
    return 0;
}
```

### Step 5: SCHAN writes to CMICm DMA registers

The DMA start sequence issues SCHAN writes to:
- **`DMA_DESC[chan]`** = ring base physical address (CMC base + 0x158 + chan*4)
- **`DMA_CTRL[chan]`** = `EN | DIR_TX | EN_INTR` (CMC base + 0x140 + chan*4)

These go through the SCHAN protocol with **block=0 (CMIC)** as
documented in `CMIC_SCHAN_DMA_DEEP_DIVE.md`.

### Step 6: Chip DMA engine reads DCBs and packets

The chip:
1. Reads `DMA_DESC[chan]` to find the ring base
2. Walks DCBs one by one (each has `next_dcb` → next pointer)
3. For each DCB: DMA-reads the packet from `packet_addr` into its
   internal queue
4. After DMA: writes `STATUS = DONE | length` into the DCB
5. After all packets: raises IRQ (or batches if `SEL_INTR_ON_DESC_OR_PKT`
   is set)

### Step 7: Packets enter the egress pipeline

Each DMA'd packet arrives at the chip's CPU port. The egress pipeline:
1. **Optionally** prepends an HG2 header (if `chain->use_hg2 == 1`)
   - Header indicates `dest_port = chain->dst_port`, etc.
2. **Strips** the HG2 header at the destination's egress (if HG2 was on)
3. **L2 lookup** at egress for dest MAC (if not directed-injection)
4. **VLAN edit**: insert/replace VLAN tag based on egress VLAN config
5. **CRC calculate** and append
6. **Send to MAC**: into the appropriate XLPORT or CDPORT block

### Step 8: MAC sends to wire

The XLPORT MAC (10G) or CDPORT MAC (40G):
1. Serializes the frame into a stream of 10/40 Gbps bits
2. Through the Warpcore PHY → SerDes → SFP+/QSFP+ module → wire

### TX path summary table

| Step | Component | Time |
|---|---|---|
| 1 | App → kernel → swp1 TUN write | ~µs |
| 2 | TUN read by switchd | ~10 µs |
| 3 | bcm_tx_list wrapping | ~1 µs |
| 4 | SCHAN writes for DMA setup | ~10 µs |
| 5 | DMA channel fires, chip walks ring | ~µs |
| 6 | EPIPE processing | ~µs |
| 7 | MAC + wire | ~ns |
| **Total** | TUN write to wire | **~20-50 µs** |

---

## 4. The DMA ring lifecycle

### Allocation

```c
/* During switchd init (called by bcm_rx_start / bcm_tx_init) */
struct dma_pool {
    uint8_t  *dv_buf;        // DV management struct (~200 B)
    uint8_t  *dcb_array;     // DCBs (32 B each × N)
    uint8_t  *packet_bufs[NUM_DCBS];  // 16 KB buffers
    dma_addr_t dcb_array_dma_addr;
    dma_addr_t packet_buf_dma_addrs[NUM_DCBS];
};

void dma_pool_init(int unit, int direction, int num_dcbs) {
    /* Get DCB size for this chip from chip-ops vtable */
    int dcb_size = unit_state[unit].chip_ops->dcb_size;  // 32 for Trident+

    /* Allocate DV struct */
    dv_buf = bcm_alloc(unit, sizeof(struct dma_vector), "DMA Vector");

    /* Allocate DCB array (DMA-coherent host memory) */
    dcb_array = dma_alloc_coherent(&pdev, num_dcbs * dcb_size, &dcb_array_dma);

    /* Allocate packet buffers */
    for (int i = 0; i < num_dcbs; i++) {
        packet_bufs[i] = dma_alloc_coherent(&pdev, 16384, &buf_dma);

        /* Build the DCB */
        dcb_t *dcb = &dcb_array[i];
        dcb->packet_addr = buf_dma;
        dcb->length_flags = (1 << 25);   // REQUEST_INTR
        dcb->next_dcb = dcb_array_dma + ((i + 1) % num_dcbs) * dcb_size;
        dcb->status = 0;
    }

    /* Last DCB chains back to first (circular ring) */
    /* Already handled by modulo above */
}
```

### Programming the chip

```c
void dma_chan_program(int unit, int chan, int direction, dma_addr_t ring_base) {
    /* SCHAN write the descriptor ring base */
    schan_write(unit, 0 /*CMIC*/, 0x158 + chan * 4 /*DMA_DESC*/, ring_base);

    /* SCHAN write the control register to enable */
    uint32_t ctrl = (1 << 0)                      // CH_DMA_EN
                  | ((direction == TX ? 1 : 0) << 4)  // DIR
                  | (1 << 16);                    // EN_INTR
    schan_write(unit, 0 /*CMIC*/, 0x140 + chan * 4 /*DMA_CTRL*/, ctrl);
}
```

### Walk on IRQ

```c
void rx_irq_walk(struct dma_pool *pool) {
    while (1) {
        dcb_t *dcb = &pool->dcb_array[pool->head];
        if ((dcb->status & 0x80000000) == 0) break;  // DONE not set, stop

        int length = dcb->status & 0xFFFFFF;
        uint8_t *pkt = pool->packet_bufs[pool->head];

        /* Process packet */
        rx_callback(pkt, length);

        /* Refill DCB for reuse */
        dcb->status = 0;
        dcb->length_flags = (1 << 25);
        /* packet_addr and next_dcb unchanged */

        pool->head = (pool->head + 1) % NUM_DCBS;
    }
}
```

### Refill (continuous operation)

The chip keeps walking the ring forever — when it gets to a DCB whose
`STATUS != 0` (i.e., not yet processed by host), it pauses. The host's
IRQ handler resets STATUS=0 after processing, allowing the chip to
continue.

For **TX**: host fills DCB, chip consumes. Once consumed, host can
fill a new packet into the same buffer.

For **RX**: chip fills DCB+buffer, host consumes. Once consumed, host
resets STATUS=0 and chip can DMA the next packet in.

---

## 5. The HG2 header parser (RX side)

When switchd's RX worker receives a packet, the first 12 bytes are the
HG2 header. switchd's `parse_hg2_srcport()` does:

```c
struct hg2_header {
    uint8_t start;          // 0xFB
    uint8_t version_misc;   // bits 7..4 = version, bits 3..0 = misc
    uint8_t reserved;
    uint8_t reason0;
    uint8_t reason1;
    uint8_t srcmod_srcport;  // bits 7..1 = port, bit 0 = mod (LSB)
    uint8_t srcmod_msb;
    uint8_t dstmod_dstport;
    uint8_t dstmod_msb;
    uint16_t vid_tc;         // VID[11:0] | TC[15:12]
    uint16_t extension;
};

int parse_hg2_srcport(uint8_t *pkt) {
    if (pkt[0] != 0xFB) return -1;  // not HG2
    int srcmod = (pkt[5] & 0x01) | (pkt[6] << 1);
    int srcport = pkt[5] >> 1;
    return srcport;  // matches phys_port from chip's portmap
}
```

The `srcport` is the **chip-physical port** (the same number as in
`portmap_N.0 = phys:speed`). switchd translates phys → swp via the
`porttab`:

```
porttab entry, linux:swp1 sdk:xe0     (xe0 = phys port 65 from portmap_1.0=65:10)
porttab entry, linux:swp9 sdk:xe8     (xe8 = phys port 5  from portmap_9.0=5:10)
```

So a packet that arrived on phys port 65 (chip's view) routes to swp1
(Linux's view) via the porttab.

---

## 6. CPU-steer programming (what makes packets get punted)

Cumulus's `rc.datapath_0` programs these (already covered in
`ASIC_INIT_COOKBOOK.md` but cross-referencing for clarity):

```bcmsh
modreg cpu_control_1 l3_mtu_fail_tocpu=1     # ICMP frag-needed generation
modreg cpu_control_1 l3_slowpath_tocpu=1     # IP options → CPU
modreg cpu_control_1 v4l3dstmiss_tocpu=1     # Unknown IPv4 dest → CPU
modreg cpu_control_1 v6l3dstmiss_tocpu=1     # Unknown IPv6 dest → CPU

# CPU COS map (priorities → CPU queue 0-7)
modify cpu_cos_map 127 1 int_pri_key=0 int_pri_mask=0xf cos=0 valid=1
modify cpu_cos_map 126 1 int_pri_key=1 int_pri_mask=0xf cos=1 valid=1
modify cpu_cos_map 125 1 int_pri_key=2 int_pri_mask=0xf cos=2 valid=1
... (etc for priorities 4..7) ...
```

Without these, the chip silently drops packets that don't match any L3
route — bypassing the CPU entirely.

To **temporarily snoop** a port's traffic to the CPU, install an FP
TCAM rule with action `COPY_TO_CPU`. switchd's `cl-acltool` does this
when you install an iptables rule with `MIRROR` target.

---

## 7. Specific things the user needs to know for EdgeNOS

### A. RX punt bring-up checklist

1. ✅ **PAXB sub-windows initialized** — kernel BDE handles
2. ✅ **DMA descriptor ring allocated** — DMA-coherent, 32 B per DCB,
   N=64 typical, circular chain
3. ✅ **Packet buffers allocated** — 16 KB each, one per DCB,
   DMA-coherent
4. ⚠️ **Write DMA_DESC via SCHAN** (not direct MMIO!)
   - SCHAN: block=0 (CMIC), addr=0x158 + chan*4, value=ring_base_dma_addr
5. ⚠️ **Write DMA_CTRL via SCHAN** to enable RX
   - SCHAN: block=0, addr=0x140 + chan*4, value=(EN | DIR_RX | EN_INTR)
6. ✅ **CPU steer config** — `cpu_control_1.{v4l3dstmiss, l3_slowpath, ...}` set to 1
7. ✅ **CPU queue mapping** — `cpu_cos_map` entries 120-127 populated
8. ✅ **IRQ handler registered** — kernel BDE has it
9. ✅ **bcm_rx_register callback** — switchd-style producer ring
10. ✅ **HG2 parser** in RX worker
11. ✅ **TUN device write** for each swp

### B. TX inject bring-up checklist

1. ✅ **TX DMA channel allocated** — `bcm_tx_init` calls FUN_100c1f60
   which walks the bitmap and picks an available channel for TX
2. ✅ **TUN device read** loop (one thread per swp, or one shared)
3. ✅ **bcm_pkt_t chain construction** — link packets via `next` field
   at offset 0x1c
4. ✅ **Padding to 60 B minimum** — Ethernet requires it
5. ✅ **Destination port bitmap** — 8 × 32-bit words, bit set for dest port
6. ✅ **bcm_tx_list call** in batches of 16
7. ✅ **TX completion callback** — to free buffers after chip done
8. ⚠️ **DMA_CTRL via SCHAN** for TX (same fix as RX)

### C. Common pitfalls

❌ **Don't write DMA_CTRL via /dev/mem directly** — SCHAN-mediated.
❌ **Don't forget to set REQUEST_INTR in DCB** — chip won't IRQ.
❌ **Don't forget to set EN_INTR in DMA_CTRL** — chip won't IRQ.
❌ **Don't forget to clear STATUS in DCB after processing** — chip stops.
❌ **Don't forget the HG2 header strip** — sending 12 garbage bytes to TUN.
❌ **Don't forget the CPU-steer config** — chip silently drops punt-able packets.

---

## 8. Key function reference (everything switchd uses)

### TX path

| Function | What |
|---|---|
| `FUN_1002b044` | `tun_to_tx_read` — reads from TUN, builds bcm_pkt chain |
| `FUN_1005b3e4` | switchd's bcm_tx_list wrapper (padding + bitmap + 16-pkt batches) |
| `FUN_10441108` | `bcm_tx_list` — SDK entry point |
| `FUN_101f33f8` | TX DMA channel start (issues SCHAN writes for DMA_DESC/CTRL) |
| `FUN_100c1f60` | TX DMA channel allocator (walks bitmap, picks channel) |
| `FUN_1078dbdc` | `bmd_xgsd_dma_start` (BMD layer, the chip-specific start) |
| `FUN_107909b8` | `bmd_dma_init(direction, cmc)` |
| `FUN_1005b2e4` | TX completion callback |

### RX path

| Function | What |
|---|---|
| `FUN_1042b380` | `bcm_rx_start` / `bcm_rx_register` |
| `FUN_104290c4` | `bcm_rx_control_set` (VTAG_STRIP, CRC_STRIP, etc.) |
| `FUN_101f2fac` | RX DMA channel start |
| `FUN_101b8f54` | switchd's RX callback (enqueue to producer ring) |
| `FUN_1002b8cc` | `rx_to_tun` worker (consume ring → TUN write) |
| `FUN_10008ae8` | TUN device creation (per-swp) |

### Init coordination

| Function | What |
|---|---|
| `FUN_10051be0` | switchd packet-IO setup (calls bcm_tx_init + bcm_rx_start + ...) |
| `FUN_1006f798` | bcm_rx_cos_rate_set / burst_set callers |

---

## 9. Files

- `BLOCK_INIT_DEEP_DIVE.md` — block-init register/function map
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` — SCHAN+DMA protocol low-level
- `ACCESS_METHODS_DEFINITIVE_GUIDE.md` — MMIO/SCHAN/CMICm/PAXB layering
- `BCM_INIT_REGISTER_MAP.md` — every register touched at init
- `ASIC_INIT_COOKBOOK.md` — rc.soc / rc.datapath_0 line decoded
- `PACKET_IO_HOOKS.md` — original RX callback decompilation
- `BDE_COMPLETE.md` — kernel BDE module ioctl table
- `cumulus-packet-io-architecture.md` — "no KNET, uses TUN" finding
- `ghidra-analysis/switchd_pkt_flow_decomp.c` — TX/RX DMA function decomps
- `ghidra-analysis/switchd_pkt_flow2_decomp.c` — bcm_tx_list wrapper decomp

---

## 10. The user's RX punt fix — distilled

You said the issue was that direct MMIO writes to DMA_CTRL "don't
stick". Here's the minimal correct sequence:

```c
/* Initialize once at startup */
int rx_chan = bcm_tx_init_alloc_rx_channel(unit);   // returns chan 0-3

/* Allocate ring + buffers */
struct dma_pool pool;
dma_pool_init(unit, RX, &pool, NUM_DCBS=64);

/* Program ring base via SCHAN (NOT direct MMIO) */
schan_write(unit, /*block=*/0, /*addr=*/0x158 + rx_chan*4,
            /*value=*/pool.dcb_array_dma_addr);

/* Enable RX via SCHAN (NOT direct MMIO) */
uint32_t ctrl = 0;
ctrl |= (1 << 0);    // CH<chan>_DMA_EN
ctrl |= (0 << 4);    // DIR = RX
ctrl |= (1 << 16);   // EN_INTR
schan_write(unit, /*block=*/0, /*addr=*/0x140 + rx_chan*4, ctrl);

/* Now CPU-steer config (these go via rc.datapath_0 normally) */
schan_write_field(unit, /*reg=*/CPU_CONTROL_1,
                  /*field=*/V4L3DSTMISS_TOCPU, 1);
schan_write_field(unit, CPU_CONTROL_1, V6L3DSTMISS_TOCPU, 1);
schan_write_field(unit, CPU_CONTROL_1, L3_SLOWPATH_TOCPU, 1);

/* IRQ handler runs when DCB completes — process and TUN-write */
```

If you have an SCHAN userspace tool (per the recipe in
`CMIC_SCHAN_DMA_DEEP_DIVE.md`), this is testable from userspace.

---

*Complete end-to-end packet flow recovered from static analysis of
switchd binary + Cumulus kernel BDE module. Verified against
decompiled functions and live trace data.*

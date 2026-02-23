# DMA / DCB Layout (from bcm-knet.c)

**Source**: OpenNSL `systems/linux/kernel/modules/bcm-knet/bcm-knet.c`  
**Purpose**: Document the Descriptor Control Block (DCB) and ring layout used by the kernel for packet TX/RX. On Cumulus, KNET is not loaded; if user-space (libopennsl) uses the same ASIC DMA rings over BDE, the **hardware** layout may be the same.

---

## 1. Constants

| Symbol | Value | Meaning |
|--------|-------|---------|
| MAX_TX_DCBS | 64 | Max TX descriptors per ring |
| MAX_RX_DCBS | 64 | Max RX descriptors per ring |
| NUM_DMA_CHAN | 8 | Total DMA channels |
| NUM_RX_CHAN | 7 | (XGS) |
| NUM_CMICM_RX_CHAN | 3 | RX channels for CMICm (Trident/Trident+) |
| SOC_DCB_KNET_DONE | 0x8000 | Flag in DCB: kernel processing done |
| SOC_DCB_KNET_COUNT_MASK | 0x7fff | Packet length in last word |
| SOC_DCB_META_OFFSET | 2 | Metadata starts at word 2 |

---

## 2. DCB Layout (software view)

- **dcb_wsize**: DCB size in **32-bit words** (device-dependent; from KNET init message).
- **dcb_mem**: logical pointer to DCB; **dcb_dma**: physical address for hardware.
- Each descriptor is **dcb_wsize** words. Ring is contiguous: descriptor 0, 1, … at `dcb_mem + i * dcb_wsize`.

### 2.1 Last word (status)

- **dcb[dcb_wsize-1]**:
  - Bits 0–14 (SOC_DCB_KNET_COUNT_MASK): **packet length** (bytes).
  - Bit 31: **chain/descriptor valid** (1 = valid, 0 = stop).
  - SOC_DCB_KNET_DONE (0x8000): set when kernel has consumed (RX) or filled (TX) the descriptor.

### 2.2 First words (buffer / next)

- **Word 0**: For chained DCBs, can hold **next DCB physical address** (or first buffer address for TX).
- **CMICm (non-X)**: `dcb[1] & 0xffff` = packet length; buffer address in low words.
- **CMICx**: `dcb[2] & 0xffff` = packet length; different layout for buffer/hi address.
- **Metadata**: from word 2 (SOC_DCB_META_OFFSET) up to dcb_wsize-1; last word is status above.

### 2.3 Ring sizing (from code)

```c
dcb_size = sinfo->dcb_wsize * sizeof(uint32_t);
tx_ring_size = dcb_size * (MAX_TX_DCBS + 1);   // 65 DCBs
rx_ring_size = dcb_size * (MAX_RX_DCBS + 1);   // 65 DCBs
```

---

## 3. Per-descriptor info (bkn_desc_info_t)

```c
typedef struct bkn_desc_info_s {
    uint32_t *dcb_mem;   // logical DCB
    uint64_t dcb_dma;    // physical DCB
    struct sk_buff *skb; // kernel buffer (or NULL for user API)
    uint64_t skb_dma;    // physical buffer
    uint32_t dma_size;   // buffer size
} bkn_desc_info_t;
```

So each slot has: DCB (logical + physical), optional skb, and buffer DMA address/size.

---

## 4. DMA registers (CMICm)

From SCHAN_AND_RING_BUFFERS.md and bcm-knet:

| Register | Offset (BAR0) | Use |
|----------|----------------|-----|
| CMICM_DMA_DESC0r | 0x31158 (+ 4×chan) | Physical address of first DCB in ring |
| CMICM_DMA_HALT_ADDRr | 0x31120 (+ 4×chan) | Halt address (continuous DMA) |
| CMICM_DMA_CTRLr | 0x31140 (+ 4×chan) | Control |
| CMICM_DMA_STATr | 0x31150 | Status |
| CMICM_DMA_STAT_CLRr | 0x311a4 | Clear status |

Channels: TX typically 0, RX 1..N (e.g. 3 for CMICm).

---

## 5. KNET ioctl (user ↔ kernel)

From bcm-knet.h:

```c
typedef struct {
    int rc;
    int len;
    int bufsz;
    int reserved;
    uint64_t buf;    // pointer to buffer
} bkn_ioctl_t;
```

User-space can send/receive packet buffer (buf, len, bufsz) via ioctl on `/dev/linux-bcm-knet`. Cumulus does **not** load KNET, so switchd does **not** use this unless a different build is used. If your trace shows no KNET fd, the path is BDE-only (e.g. BDE exposes DMA memory or another ioctl).

---

## 6. Relevance for Path B

- **If** libopennsl (or switchd) uses the **same** DMA rings as KNET (via BDE-provided memory and register programming), then:
  - DCB layout (word count, last word = status/length, word 0/1/2 for addr/length) is as above.
  - Ring size and channel assignment (TX 0, RX 1..3 for CMICm) apply.
- **If** Cumulus uses a different path (e.g. BDE ioctl with a single buffer per packet), the trace (TRACING_PACKET_IO_GUIDE.md) will show the actual syscall and you can reverse the buffer format from there.
- Use this doc when implementing or reverse-engineering the BDE packet interface (§4.5–4.8 in PATH_B_INFORMATION_CHECKLIST.md).

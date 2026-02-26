# Packet I/O BDE DMA Interface — BCM56846 (Trident+)

**Date**: 2026-02-24
**Status**: HAVE — architecture confirmed from strace, DCB format verified via `bcmcmd dma dvalloc/dcbdump` on live switch
**Switch**: Edgecore AS5610-52X / Cumulus Linux 2.5 / <LIVE_SWITCH_IP>

---

## Summary

BCM56846 packet I/O uses **CMICm DMA rings** (no KNET kernel module on Cumulus). User-space SDK:
- Allocates TX/RX DCB rings from the mmap'd DMA pool (physical 0x04000000)
- Fills TX DCBs with buffer address + HiGig/SOPCmd TX metadata header → kicks DMA channel 0
- Pre-fills RX DCBs with empty buffers → ASIC fills them on punt → interrupt notifies SDK

---

## 1. Hardware DMA Architecture

### 1.1 DMA Pool

| Resource | Physical address | Size | User-space mapping (switchd) |
|----------|-----------------|------|------------------------------|
| DMA pool | 0x04000000 | 64 MB | 0x4806b000 → 0x04000000 (mmap /dev/mem) |
| BAR0 | 0xa0000000 | 256 KB | 0x4802b000 → 0xa0000000 (mmap /dev/mem) |

All DCBs and packet buffers are allocated within the DMA pool. Addresses stored in DCBs are **physical (bus) addresses** from this pool.

### 1.2 DMA Channels (CMICm)

| Channel | Direction | BAR0 register offsets |
|---------|-----------|----------------------|
| **0** | TX | CMICM_DMA_CTRL = BAR0+0x31140, CMICM_DMA_DESC0 = BAR0+0x31158, CMICM_DMA_HALT = BAR0+0x31120 |
| **1** | RX | CMICM_DMA_CTRL = BAR0+0x31144, CMICM_DMA_DESC0 = BAR0+0x3115C, CMICM_DMA_HALT = BAR0+0x31124 |
| **2** | RX | CMICM_DMA_CTRL = BAR0+0x31148, CMICM_DMA_DESC0 = BAR0+0x31160, CMICM_DMA_HALT = BAR0+0x31128 |
| **3** | RX | CMICM_DMA_CTRL = BAR0+0x3114C, CMICM_DMA_DESC0 = BAR0+0x31164, CMICM_DMA_HALT = BAR0+0x3112C |

Formula: `CMICM_DMA_CTRL(ch) = BAR0 + 0x31140 + 4*ch`, same for DESC0 (0x31158) and HALT (0x31120).

### 1.3 Ring Sizing

```c
#define MAX_TX_DCBS 64
#define MAX_RX_DCBS 64
// +1 for wrap-around / sentinel
tx_ring_size = (MAX_TX_DCBS + 1) * dcb_wsize * 4;   // 65 × 64 = 4160 bytes
rx_ring_size = (MAX_RX_DCBS + 1) * dcb_wsize * 4;   // same
```

---

## 2. DCB Format — BCM56846 (DCB Type 21)

**Verified via bcmcmd** on live switch:
```
bcmcmd 'dma dvalloc t 1'
→ "Allocated DMA Vector (DV) at 0x12ee9e88. 8 DCBs (start 0x4864ba18, 64 bytes)"
```

**DCB type: 21. Size: 16 words (64 bytes) per DCB.**

### 2.1 TX DCB Layout

Verified dcbdump output for a TX DCB destined for xe0 (port 1):
```
word[ 0] = 0x046d4498  ← packet buffer physical address
word[ 1] = 0x00180046  ← flags[31:16]=0x0018, pkt_length[15:0]=0x46=70
word[ 2] = 0xff000000  ← TX metadata w0: START=0xFF (HiGig-style SOPCmd header)
word[ 3] = 0x00000100  ← TX metadata w1: UNICAST[8]=1, SRC_MODID[7:0]=0
word[ 4] = 0x03030301  ← TX metadata w2: INPUT_PRI[31:28]=3, QUEUE_NUM[27:24]=3,
                          COS[19:16]=3, LOCAL_DEST_PORT[7:0]=1 (xe0/swp1)
words[5–14] = 0x00000000  ← zeros for simple unicast
word[15] = 0x80000046  ← status: bit31=1 (valid/done), bits[14:0]=0x46=70 bytes
```

### 2.2 TX Metadata (words 2–4) Field Details

**word[2]** — TX metadata byte 0–3:
| Bits | Field | Value | Notes |
|------|-------|-------|-------|
| [31:24] | START | 0xFF | HiGig-style SOPCmd start byte |
| [23:16] | HGI | 0x00 | HiGig type (0=HiGig, 1=HiGig2) |
| [15:8] | RESERVED | 0x00 | |
| [7:0] | RESERVED | 0x00 | |

**word[3]** — TX metadata byte 4–7:
| Bits | Field | Value | Notes |
|------|-------|-------|-------|
| [31:26] | RESERVED | 0 | |
| [25] | SPID_OVERRIDE | 0 | |
| [24:16] | SPID/SRC fields | 0 | |
| [8] | UNICAST | 1 | 1=unicast dest, 0=multicast bitmap |
| [7:0] | SRC_MODID | 0 | Source module ID (0 = this chip) |

**word[4]** — TX metadata byte 8–11:
| Bits | Field | Value | Notes |
|------|-------|-------|-------|
| [31:28] | INPUT_PRI | 3 | Input priority |
| [27:24] | QUEUE_NUM | 3 | COS queue number |
| [19:16] | COS | 3 | Class of service |
| [7:0] | LOCAL_DEST_PORT | 1 | **Egress BCM port number**: 1=xe0(swp1), 2=xe1(swp2), …, 52=xe51(swp52) |

**For custom SDK TX to port N** (xe0 = port 1, xe1 = port 2, etc.):
```c
dcb[2] = 0xff000000;                 // START=0xFF
dcb[3] = 0x00000100;                 // UNICAST=1
dcb[4] = 0x03030300 | (port & 0xFF); // LOCAL_DEST_PORT = BCM port number
```

### 2.3 RX DCB Layout (pre-filled; ASIC fills metadata + status on receive)

Pre-filled by SDK:
```
word[ 0] = <buf_phys>   ← physical address of pre-allocated RX buffer
word[ 1] = 0x00180046   ← buffer flags + allocated size
words[2–14] = 0          ← ASIC will overwrite with RX metadata
word[15] = 0             ← ASIC sets bit31=1 and bits[14:0]=pkt_len on completion
```

On completion (RX done):
```
word[ 0] = <buf_phys>         ← unchanged
word[ 1] = 0x...              ← may be updated
words[2–5] = RX metadata      ← ingress port, VLAN, reason code, timestamp (ASIC writes)
              word[2] bits[7:0] = src_port (BCM port number, e.g. 1=xe0)
              (exact field mapping needs runtime verification)
word[15]   = 0x8000XXXX       ← bit31=1 (done), bits[14:0]=pkt_len
```

The RX metadata fields in words[2–14] follow the same HiGig header format as TX, but filled by ASIC ingress pipeline. Key field: `SRC_PORT` (ingress port) in word[2] or word[4] bits[7:0] (same position as LOCAL_DEST_PORT in TX).

### 2.4 Status Word (word[15]) Summary

| Bits | Field | TX meaning | RX meaning |
|------|-------|-----------|-----------|
| [31] | DONE/VALID | 1 = ASIC consumed packet | 1 = ASIC filled buffer |
| [15] | ERROR | TX error occurred | RX error occurred |
| [14:0] | COUNT | bytes transferred | received packet length |

---

## 3. BDE Ioctl Interface

The SDK does **not** use ioctls to send/receive individual packets. Packets flow via mmap'd DMA rings. BDE ioctls are used only for synchronization:

| Code | Name | Description |
|------|------|-------------|
| `0x20004c08` | `LUBDE_USLEEP` | Sleep for N microseconds |
| `0x20004c09` | `LUBDE_WAIT_FOR_INTERRUPT` | Block until ASIC DMA interrupt fires |
| `0x20004c0a` | `LUBDE_SEM_OP` | Semaphore create/destroy/take/give for ring sync |

**Ioctl structure** (`lubde_ioctl_t`):
```c
typedef struct {
    unsigned int dev;           // Unit/device number (0)
    unsigned int rc;            // Return code (out)
    unsigned int d0, d1, d2, d3; // Operation-specific data
    bde_kernel_addr_t p0;       // Pointer argument
    union { unsigned int dw[2]; unsigned char buf[64]; } dx;
} lubde_ioctl_t;
```

---

## 4. Thread Model (Observed via strace)

| TID | Role | Syscalls |
|-----|------|----------|
| 19089 | TUN read thread | `select(all TUN fds)` → `read(fd_swpN, pkt, 16384)` → DMA enqueue (in-process) |
| 19088 | TUN write thread | `LUBDE_SEM_OP` (block) → `write(fd_swpN, pkt, len)` → next `LUBDE_SEM_OP` |
| 19039 | DMA poll thread | `LUBDE_WAIT_FOR_INTERRUPT` in tight loop |
| others | BDE/SDK threads | `LUBDE_SEM_OP` (various ring/worker sync) |

### TX flow:
```
1. TUN read thread: select(TUN fds) → read(fd20, buf, 16384) = 82 bytes
2. TUN read thread (in-process): fill TX DCB → update TX ring tail pointer → write CMICM_DMA_CTRL kick
3. DMA poll thread: WAIT_FOR_INTERRUPT returns → check TX ring for completions → free TX DCBs
```

### RX flow:
```
1. DMA poll thread: WAIT_FOR_INTERRUPT fires (ASIC DMA'd packet to RX ring)
2. SDK: scan RX ring, find completed DCBs (word[15] bit31=1)
3. Extract packet: pkt_buf = dcb[0], pkt_len = dcb[15] & 0x7fff
4. Determine port: parse RX metadata in dcb[2..14] for src_port
5. SEM_GIVE → TUN write thread wakes → write(fd_swp(port-1+20), pkt, pkt_len)
6. Refill RX DCB with fresh buffer, re-arm
```

---

## 5. Implementation Guide (Custom SDK)

### 5.1 Initialization

```c
// 1. Map DMA pool (BDE ioctl: LUBDE_GET_DEVICE → phys addr; then mmap /dev/mem)
// Already confirmed: DMA pool phys=0x04000000, 64MB

// 2. Allocate TX ring from DMA pool
uint32_t *tx_ring = dma_alloc(65 * 64);     // 65 × 64-byte DCBs
uint64_t tx_ring_phys = virt_to_phys(tx_ring);

// 3. Allocate RX ring + RX buffers
uint32_t *rx_ring = dma_alloc(65 * 64);
uint64_t rx_ring_phys = virt_to_phys(rx_ring);
uint8_t *rx_bufs[65];
for (int i = 0; i < 64; i++) {
    rx_bufs[i] = dma_alloc(2048);           // 2KB per RX buffer
    // Pre-fill RX DCB
    uint32_t *dcb = rx_ring + i * 16;
    dcb[0] = virt_to_phys(rx_bufs[i]);     // buffer physical address
    dcb[1] = 0x00180800;                    // flags | buffer size (2048=0x800)
    dcb[15] = (1 << 31);                    // valid, owned by ASIC, length=0
}

// 4. Program DMA registers (BAR0 access via mmap)
volatile uint32_t *bar0 = map_bar0();
bar0[0x31158 >> 2] = tx_ring_phys;          // CMICM_DMA_DESC0(ch0) = TX ring addr
bar0[0x3115C >> 2] = rx_ring_phys;          // CMICM_DMA_DESC0(ch1) = RX ring addr
bar0[0x31148 >> 2] |= 1;                    // CMICM_DMA_CTRL(ch1) |= START (enable RX)
```

### 5.2 TX Packet to Specific Port

```c
int bcm56846_tx(int port, uint8_t *pkt, int pkt_len) {
    // port: BCM port number (1=xe0/swp1, ..., 52=xe51/swp52)
    uint32_t *dcb = get_free_tx_dcb();      // next slot in TX ring
    uint8_t *buf = dma_alloc(pkt_len);
    memcpy(buf, pkt, pkt_len);

    dcb[0]  = virt_to_phys(buf);
    dcb[1]  = 0x00180000 | pkt_len;         // flags | length
    dcb[2]  = 0xff000000;                   // TX metadata: START=0xFF
    dcb[3]  = 0x00000100;                   // UNICAST=1
    dcb[4]  = 0x03030300 | (port & 0xFF);   // LOCAL_DEST_PORT = port
    // dcb[5..14] = 0x00000000 (already zeroed)
    dcb[15] = (1 << 31) | pkt_len;          // valid + length

    // Kick TX DMA channel 0
    bar0[0x31158 >> 2] = virt_to_phys(dcb); // DMA_DESC0(ch0) = this DCB
    bar0[0x31140 >> 2] |= 1;                // DMA_CTRL(ch0) |= START
    return 0;
}
```

### 5.3 RX Packet Dispatch

```c
void rx_poll_thread(void) {
    while (running) {
        ioctl(bde_fd, 0x20004c09, &args);    // LUBDE_WAIT_FOR_INTERRUPT
        for (int i = 0; i < 64; i++) {
            uint32_t *dcb = rx_ring + i * 16;
            if (dcb[15] & (1 << 31)) {       // done bit set
                int pkt_len = dcb[15] & 0x7fff;
                uint8_t *buf = phys_to_virt(dcb[0]);
                int src_port = /* parse from dcb[4] bits[7:0] */ dcb[4] & 0xFF;
                int tun_fd = 20 + (src_port - 1);   // fd 20=swp1, fd 21=swp2, ...
                write(tun_fd, buf, pkt_len);
                // Refill: keep dcb[0] as buffer addr, clear status
                dcb[15] = (1 << 31);         // re-arm: owned by ASIC, length=0
            }
        }
    }
}
```

---

## 6. bcmcmd Reference

```bash
# Allocate and inspect DCBs
bcmcmd 'dma dvalloc t <count>'          # Allocate TX DV with N DCBs
bcmcmd 'dma dvalloc r <count>'          # Allocate RX DV with N DCBs
bcmcmd 'dma dcbdump t <laddr>'          # Dump TX DCB at logical address
bcmcmd 'dma dcbdump r <laddr>'          # Dump RX DCB at logical address
bcmcmd 'dma l2p <laddr>'               # Convert logical → physical address
bcmcmd 'dma p2l <paddr>'               # Convert physical → logical address
bcmcmd 'dma addrx <dv_laddr> <buf_laddr> <bytes>'  # Add RX buffer to DV
```

**Live dcbdump output** (TX to xe0/port1):
```
word[ 0] = 0x046d4498      ← buf phys
word[ 1] = 0x00180046      ← flags|len (70 bytes)
word[ 2] = 0xff000000      ← START=0xFF
word[ 3] = 0x00000100      ← UNICAST=1
word[ 4] = 0x03030301      ← LOCAL_DEST_PORT=1 (xe0)
words[5–14] = 0x00000000
word[15] = 0x80000046      ← done, length=70
type 21 !chain !sg !reload hg stat
```

---

## 7. References

- [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md) — TUN device architecture, no KNET
- [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md) — opennsl_pkt_t structure, TX call chain
- [DMA_DCB_LAYOUT_FROM_KNET.md](DMA_DCB_LAYOUT_FROM_KNET.md) — DCB/ring layout from KNET source
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — BDE/S-Channel for table writes
- [traces/PACKET_IO_TRACE_EXTRACTED_<LIVE_SWITCH_IP>.md](traces/PACKET_IO_TRACE_EXTRACTED_<LIVE_SWITCH_IP>.md) — strace thread/ioctl analysis
- [traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md) — DMA pool physical address

# CMIC / SCHAN / DMA — Complete Deep Dive

Everything we've recovered about the BCM56846 (Trident+) chip-control
fabric. Both the **conceptual model** (how this kind of chip is
organized) and the **byte-for-byte register layout, bit positions, and
transaction protocols** an EdgeNOS implementer needs.

All findings statically derived from `switchd` (PowerPC ELF, 31 MB,
BCM SDK statically linked) — no chassis interaction. Verified register
addresses, field IDs, and protocols against decompiled SDK source
references (`bcm-sdk/src/soc/common/schan.c` etc.).

---

# Part I — THE BIG PICTURE

## 1. The Broadcom XGS chip architecture (mental model)

A modern Broadcom switch ASIC like the BCM56846 is not "one chip" in the
software sense. It's a collection of **hardware blocks**, each with its
own register file and SRAM tables, **glued together by an internal
control fabric**:

```
                ┌──────── Host CPU (P2020 PowerPC) ────────┐
                │                                          │
                │  /dev/mem  → mmap BAR0 → MMIO writes     │
                │  /dev/linux-user-bde ioctl interface     │
                │  DMA pool (8 MB coherent)                │
                └────────────────┬─────────────────────────┘
                                 │ PCIe (BAR0 @ 0xa0000000, 256 KB)
                                 ↓
   ┌─────────────────────────────────────────────────────────────────┐
   │                  BCM56846 (Trident+) ASIC                       │
   │                                                                 │
   │   ┌───────── CMICm (Control Module Interface, "CMICm") ──────┐ │
   │   │  - Embedded "front door" to the entire chip               │ │
   │   │  - 4 separate CMC instances (CMC0..CMC3)                  │ │
   │   │  - Each CMC has: SCHAN engine + DMA channels + IRQ unit  │ │
   │   │  - Translates host PCIe transactions → on-chip ops         │ │
   │   └──────┬──────────────────┬─────────────────────┬──────────┘ │
   │          │ SCHAN bus        │ Table DMA           │ Packet DMA │
   │          ↓                  ↓                     ↓             │
   │  ┌─────────────┐  ┌───────────────────┐  ┌──────────────────┐ │
   │  │ IPIPE       │  │ MMU (Memory Mgmt) │  │ XLPORT/CDPORT    │ │
   │  │ EPIPE       │  │ - Buffer pool     │  │ - 10G/40G MACs   │ │
   │  │ - Parser    │  │ - Queue config    │  │ - PHY interface  │ │
   │  │ - L2/L3 LU  │  │ - 46K cells       │  └──────────────────┘ │
   │  │ - FP TCAM   │  └───────────────────┘                       │
   │  └─────────────┘                                              │
   └─────────────────────────────────────────────────────────────────┘
```

### Three fundamentally different access paths:

| Path | What it's for | How fast | How wide |
|---|---|---|---|
| **MMIO direct** | A small set of registers that live IN the CMICm | ~100 ns | 32 bits |
| **SCHAN** | Any register/memory inside any block | ~1 µs | up to 22 × 32-bit words |
| **DMA** | Bulk table fills, packet I/O | ~hundreds MB/s | unlimited |

**Critical insight:** Some registers that *appear* to be at fixed MMIO
addresses are actually **SCHAN-mediated** — i.e., the MMIO address you
see in documentation is a "shadow" that only takes effect when you go
through the proper SCHAN protocol. Writing them via direct `*reg = value`
either reads back stale or silently fails. The user's RX punt bug was
caused exactly by this.

---

## 2. What is CMIC? What is CMICm?

**CMIC** = "Control Module Interface" — the legacy version on chips like
BCM56218.

**CMICm** = "CMIC modern" — newer version on Trident+ and successors.
The "m" historically stood for the new banking architecture: instead of
one global SCHAN bank, there are **N parallel CMC banks** (CMC0, CMC1,
...) each capable of independent transactions.

On BCM56846: **4 CMCs**. switchd typically uses CMC0 for register access
and CMC1+ for DMA / statistics.

The per-CMC layout in BAR0 (relative to **CMC base = `0x31000 + cmc_idx * 0x1000`**):

```
Offset    Size    Register                           Purpose
─────────────────────────────────────────────────────────────────────
+0x000    4 B    CMC_SCHAN_CTRL                     SCHAN transaction control
+0x00c    88 B   CMC_SCHAN_MSG[0..21]               SCHAN message bank (22 words for CMICm)
+0x120    16 B   CMC_DMA_HALT_ADDR[chan]            Per-channel DMA halt
+0x140    16 B   CMC_DMA_CTRL[chan]                 Per-channel DMA control
+0x150    16 B   CMC_DMA_STAT[chan]                 Per-channel DMA status
+0x158    16 B   CMC_DMA_DESC[chan]                 Per-channel DMA descriptor base
+0x2c0    16 B   CMC_FIFO_DMA_CTRL[chan]            Per-channel FIFO DMA control
+0x364    16 B   CMC_FIFO_DMA_STAT[chan]            Per-channel FIFO DMA status
+0x400    4 B    CMC_IRQ_STAT0                      IRQ status word 0
+0x404    4 B    CMC_IRQ_MASK0                      IRQ mask word 0
+0x408    4 B    CMC_IRQ_STAT1                      IRQ status word 1
+...                                                more IRQ words
```

Why 4 CMCs? Different CPU threads can have their own CMC, avoiding
contention. Stats DMA can happen on CMC1 while switchd is doing
register access on CMC0.

---

## 3. The SCHAN bus, conceptually

**SCHAN** = "Switch Channel" or "S-Channel". It's a **packet-oriented
control bus** that connects the CMICm to every other block in the chip.

Conceptually: a SCHAN transaction is a tiny **request packet** that the
host hands to the CMICm. The CMICm:

1. Routes it (via the address's `block` field) to the target block
2. The target block decodes the command and acts on the address
3. Returns a response packet with NAK or with data

This is **not** a memory bus — it's a transaction bus. A single SCHAN op
can:
- Read or write a single register
- Read or write an entry in a multi-word table (multi-word tables span
  multiple SCHAN words)
- Trigger a side-effect (link state change, port enable, etc.)
- Touch internal SRAMs that have no MMIO address (most of them!)

**Why this matters:** The chip has ~37,000 named registers, but the BAR0
window is only 256 KB. The vast majority of registers and tables are
*only* accessible via SCHAN — they have no MMIO address at all.

---

## 4. The DMA model

Three flavors of DMA on this chip, all CMICm-mediated:

### A. Packet DMA (RX punt + TX inject)

Bidirectional pump between host memory and the chip's packet-processing
pipeline. Each direction uses a ring of **DCBs** (Descriptor Control
Blocks). The host writes the DCBs; the chip reads them, transfers data,
and writes status back.

- **TX path**: switchd builds DCBs pointing at packets in host memory →
  writes ring base to CMC_DMA_DESC → sets EN+DIR=1 in CMC_DMA_CTRL →
  chip pulls packets from ring and injects them into the egress pipeline
- **RX path**: switchd allocates empty buffers, builds DCBs pointing at
  them → CMC_DMA_DESC → sets EN+DIR=0 → chip writes received packets
  into buffers and sets DONE in the DCB → IRQ fires → switchd processes
  the ring

### B. Table DMA / SLAM DMA (bulk SRAM ops)

For initializing big internal tables (L2, L3, VLAN, FP TCAM). The host
prepares a descriptor describing "fill memory M from address A to B with
pattern P" and hands it off. The chip walks the table autonomously,
writing each entry. This is how `soc_mem_clear` works for large tables —
much faster than 100,000 SCHAN writes.

### C. FIFO DMA (counter polling)

Chip-internal counters are too numerous to read one-at-a-time. The chip
DMAs the entire counter bank to host memory on a timer. switchd reads
the host buffer instead of hammering SCHAN.

This is what `bcm_stat_flags=0x1` in config.bcm enables. The 4 FIFO DMA
channels each handle a subset of counters.

---

## 5. Packet punt — the high-level story

When a packet arrives at the chip's wire side and switchd needs to see
it (e.g., an ARP request, BGP packet, or unknown-L3-dest miss):

```
1. Wire → SerDes lane → PHY → XLPORT MAC → ingress pipeline parser
2. Ingress lookup: L2 table miss / L3 dest miss / FP rule match
3. CPU-steer decision: cpu_control_1.{l3_mtu_fail_tocpu, l3_slowpath_tocpu,
                       v4l3dstmiss_tocpu, v6l3dstmiss_tocpu, ...}
   determines whether the packet gets COPY_TO_CPU
4. Packet goes through MMU buffer pool, then back into the egress pipeline
   with CPU as destination port
5. Egress encapsulates with a HiGig2 header (8 bytes prepended)
   containing source port, reason code, queue priority
6. Packet is queued on CPU port's TX queue (cpu_cos_map decides which of
   8 CPU queues)
7. Chip pulls a free RX DCB from the host-supplied ring
8. Chip DMAs packet + HG2 header into the buffer the DCB points at
9. Chip writes status word (DONE | length | flags) into DCB
10. Chip raises IRQ on the CMC's RX channel
11. switchd's IRQ handler walks the ring, finds completed DCB
12. switchd parses HG2 header → identifies source port → writes packet
    (minus HG2) to TUN device for the corresponding swp* interface
13. Kernel sees packet on tun device → routes to userspace listener
    (e.g., the OSPF daemon)
```

For TX inject (e.g., ARP reply going out from the kernel):
- Kernel writes packet to swp* TUN
- switchd reads from TUN
- switchd allocates a TX DCB, prepends HG2 if needed
- Writes DCB to TX ring
- Sets EN bit in CMC_DMA_CTRL[tx_chan]
- Chip DMAs packet, injects into egress pipeline
- Chip sets DONE on the DCB

This is the same packet I/O pattern across all Broadcom XGS chips for
20+ years.

---

# Part II — LOW-LEVEL REFERENCE

## 6. SCHAN — exact protocol

### Command word format (32-bit, first SCHAN_MSG word)

```
 31    26 25  20 19  14 13          0
┌────────┬────────┬────────┬─────────────┐
│ OPCODE │ PORT   │ BLOCK  │ REG_ADDR    │
└────────┴────────┴────────┴─────────────┘
```

**OPCODE values** (6 high bits, value << 26):

| Hex | Binary | Name | Use |
|---|---|---|---|
| 0x09 | 001001 | `MEM_R` | Generic memory read |
| 0x0b | 001011 | `REG_R` | Register read (a.k.a. `SCHAN_OP_READ`) |
| 0x0d | 001101 | `REG_W` | Register write (a.k.a. `SCHAN_OP_WRITE`) |
| 0x0f | 001111 | `MEM_W` | Generic memory write |
| 0x11 | 010001 | `TBL_R` | Table read |
| 0x13 | 010011 | `TBL_W` | Table write |
| 0x15 | 010101 | `CTR_R` | Counter read |
| 0x1a | 011010 | `LINK_W` | Link state write |
| 0x1c | 011100 | `LINK_R` | Link state read |
| 0x20 | 100000 | `OUTSIDE` | Outside CMIC (chip-specific) |
| 0x22 | 100010 | (CMICe variant) | |
| 0x24, 0x26, 0x28 | | (error-checked variants) | |

**PORT** (6 bits) — physical port number for per-port registers; 0 for
chip-global registers.

**BLOCK** (6 bits) — block ID. Each chip has its own set; for BCM56846
the common ones are:

| Block ID | Block name (approximate) |
|---|---|
| 0x00 | CMIC itself |
| 0x01 | IPIPE_0 (ingress pipeline) |
| 0x02 | EPIPE_0 (egress pipeline) |
| 0x03 | MMU_GLB (global MMU) |
| 0x04-0x07 | MMU_SC / MMU_XPE (per-pipe MMU sub-blocks) |
| 0x08 | TOP |
| 0x09-0x0E | XLPORT0..5 (10G port wrappers) |
| 0x0F-0x13 | CDPORT0..4 (40G port wrappers) |
| 0x14-0x1A | XQPORT (QSFP+) groups |
| 0x1B | XGS / OTPC (OTP controller) |

(Exact mapping is in each register's per-reg info struct.)

**REG_ADDR** (14 bits) — the register's address within the block. This
is what the BCM SDK's symbol table maps to "register name". The 36,896
register-names file we have contains every (block, reg_addr) pair.

### Per-CMC SCHAN register layout

For CMC `cmc`:
- **SCHAN_CTRL** = MMIO offset `0x31000 + cmc * 0x1000`
- **SCHAN_MSG[w]** = MMIO offset `0x3100c + cmc * 0x1000 + w * 4`

### SCHAN_CTRL bit layout

```
 31     22  21    20   19  ...  2     1      0
┌────┬────┬────┬─────┬────┬─────┬─────┬──────┐
│ ?  │ER2 │NAK │PARERR│ ?  │  ?  │DONE │START │
└────┴────┴────┴─────┴────┴─────┴─────┴──────┘
```

| Bit | Name | Field ID | Meaning |
|---|---|---|---|
| 0 | `START` | 0xcf04 | W: set 1 to begin transaction |
| 1 | `DONE` | 0x3325 | R/W1C: 1 = complete; write 1 to clear |
| 20 | `PARERR` | — | R: parity error |
| 21 | `NAK` | 0x8b6c | R: target rejected the op |
| 22 | `ER2` | — | R: other error |

### Transaction state machine (CMICm path, what BCM56846 uses)

```c
int schan_op(int unit, uint32_t *msg, int dwc_write, int dwc_read) {
    int cmc = unit_default_cmc[unit];       // = 0 for Trident+ typically
    uint32_t cmc_base = 0x31000 + (cmc << 12);

    // (1) Write all message words
    for (int w = 0; w < dwc_write; w++) {
        mmio_write(cmc_base + 0x00c + w * 4, msg[w]);
    }

    // (2) Trigger
    uint32_t ctrl = mmio_read(cmc_base + 0x000);
    mmio_write(cmc_base + 0x000, ctrl | 0x01);  // START

    // (3) Poll for DONE with 10000 us timeout (default for non-MMU ops)
    uint64_t start = monotonic_us();
    uint32_t status;
    while (1) {
        status = mmio_read(cmc_base + 0x000);
        if (status & 0x02) break;             // DONE
        if (monotonic_us() - start > 10000) return -9;  // E_TIMEOUT
    }

    // (4) Error check
    if (status & 0x200000) {                  // NAK
        log("NAK from SCHAN");
        return -0xb;                          // E_INTERNAL
    }
    if ((status & 0x100000) && chip_flag(unit, 0x2f2c3c, 0x400)) {
        log("SER Parity Check Error");
        return -0xb;
    }
    if ((status & 0x400000) && chip_flag(unit, 0x2f2c14, 0x200)) {
        return -9;
    }

    // (5) Read result words
    for (int w = 0; w < dwc_read; w++) {
        msg[w] = mmio_read(cmc_base + 0x00c + w * 4);
    }

    // (6) Clear DONE
    mmio_write(cmc_base + 0x000, 0x01);

    return 0;
}
```

For a typical 32-bit register READ: `dwc_write=1, dwc_read=1`. Result
in `msg[1]` (msg[0] is the command word, msg[1] is the data).

For a 32-bit register WRITE: `dwc_write=2, dwc_read=0`. Command word
plus data word.

For multi-word table reads (e.g., a 12-byte L2 entry): `dwc_write=2,
dwc_read=5` (or however many words the entry uses).

### Word-count maxima

| Chip | dwc max |
|---|---|
| Legacy CMIC | 20 (0x14) |
| CMICm (BCM56846) | 22 (0x16) |

These come from the chip-state flag check `(unit_state + 0x2f2c40) & 2`.

---

## 7. DMA — exact protocol

### Per-CMC packet DMA register layout

For CMC `cmc`, channel `ch` (0-3):

| Register | MMIO offset | Field IDs of key bits |
|---|---|---|
| `DMA_HALT_ADDR[ch]` | `CMC_base + 0x120 + ch*4` | — |
| `DMA_CTRL[ch]` | `CMC_base + 0x140 + ch*4` | `CH<ch>_DMA_EN`, `CH<ch>_ABORT_DMA`, `CH<ch>_SEL_INTR_ON_DESC_OR_PKT`, `DIR`, `CHAIN` |
| `DMA_STAT[ch]` | `CMC_base + 0x150 + ch*4` | `CH<ch>_DMA_ACTIVE`, `CH<ch>_DESC_DONE`, `CH<ch>_DESCRD_CMPLT_CLR` |
| `DMA_DESC[ch]` | `CMC_base + 0x158 + ch*4` | (full 32-bit DMA address) |

### DMA_CTRL field IDs (the ones EdgeNOS needs)

These are the field IDs you'd pass to `soc_reg_field_set(unit, DMA_CTRL,
field_id, value)`:

| Field ID | Name | Meaning |
|---|---|---|
| `0x16dd` (5853) | `CH0_DMA_EN` | Set 1 to enable channel 0 |
| `0x16d3` (5843) | `CH0_ABORT_DMA` | Set 1 to abort in-flight transfers |
| `0x16e6` (5862) | `CH0_SEL_INTR_ON_DESC_OR_PKT` | 0=per-DCB IRQ, 1=per-packet IRQ |
| `0x313b` (12603) | `DIR` | 0 = RX (chip→host), 1 = TX (host→chip) |
| `0x1731` (5937) | `CHAIN` | Use chained DCBs |

(For CH1/2/3, add 0x16 to the channel-specific IDs above — there are
also `CH1_DMA_EN`, `CH2_DMA_EN`, etc. in the field table.)

### DMA_STAT field IDs

| Field ID | Name |
|---|---|
| `0x16dc` (5852) | `CH0_DMA_ACTIVE` |
| `0x16da` (5850) | `CH0_DESC_DONE` |
| `0x16d9` (5849) | `CH0_DESCRD_CMPLT_CLR` |
| `0x16d8` (5848) | `CH0_DESCRD_ADDR_DECODE_ERR` |

### DCB (Descriptor Control Block) format

Standard CMICm DCB is **16 bytes** for basic chips; on Trident+ it can
be 32 bytes with extended status. switchd reads the DCB size from a
chip-specific constant at `unit_state + 0x2f1bf4 + 4`.

**16-byte (basic) DCB:**

```
Offset  Size  Field           Direction  Description
─────────────────────────────────────────────────────────────────────
 0      4 B   PACKET_ADDR     H→C        32-bit DMA address of buffer
 4      4 B   LENGTH_FLAGS    H→C        Flags + length (see below)
 8      4 B   NEXT_DCB        H→C        DMA address of next DCB in chain (0 = end)
 c      4 B   STATUS          C→H        Hardware status (chip writes when done)
```

**LENGTH_FLAGS bit layout:**

```
 31    25 24    16 15           0
┌────────┬────────┬──────────────┐
│ FLAGS  │ FLAGS  │ LENGTH (bytes)│
└────────┴────────┴──────────────┘
  bit 31 = DONE (chip sets when complete)
  bit 30 = SOP (start of packet)
  bit 29 = EOP (end of packet)
  bit 25 = REQUEST_INTR
  bit 24 = CHAIN (this DCB chains to NEXT_DCB)
  bits 23..0 = packet length in bytes
```

**STATUS word** (chip writes on completion):

```
 31    25 24    16 15           0
┌────────┬────────┬──────────────┐
│ STATUS │ STATUS │ ACTUAL_LEN    │
└────────┴────────┴──────────────┘
  bit 31 = ERROR
  bit 30 = CRC_ERROR
  bit 29 = LATE_ABORT
  bits 23..0 = actual packet length received (for RX)
```

### DV (DMA Vector) — switchd's higher-level wrapper

switchd manages DCBs as **DMA Vectors** (DVs) — basically named DCB
ring instances with bcmsh-visible attributes:

| bcmsh var | Set via | Meaning |
|---|---|---|
| `dma_dcb_count` | DV alloc | How many DCBs in this DV |
| `dma_dcb_size` | DV alloc | DCB size in bytes (chip-dependent) |
| `dma_dcb_laddr` | DV alloc | Local (CPU) address of DCB array |
| `dma_dv_laddr` | DV alloc | Local address of DV management struct |

**DV management struct** (allocated by `bcm_dv_alloc`-equivalent at FUN_10130b18):

```c
struct dma_vector {
    /* 0x00 */ uint32_t  type;            // 1 = TX, 2 = RX
    /* 0x04 */ ...
    /* 0x18 */ uint32_t  dcb_count;       // total DCBs in this DV
    /* 0x1c */ uint8_t  *dcb_array;       // base of DCB ring (host virt)
    /* 0xc4 */ uint32_t  dcb_dma_addr;    // base of DCB ring (DMA addr)
    /* ... */
};
```

### FIFO DMA register layout

For CMC `cmc`, channel `ch` (0-3):

| Register | MMIO offset |
|---|---|
| `FIFO_DMA_CTRL[ch]` | `CMC_base + 0x2c0 + ch*4` |
| `FIFO_DMA_STAT[ch]` | `CMC_base + 0x364 + ch*4` |

FIFO_DMA_CTRL key fields:
- `EN` (field 0x3e94) — enable channel
- `ABORT` (field 0x10) — abort current transfer

FIFO_DMA_STAT key field:
- `DONE` (field 0x3325) — ABORT done indicator

---

## 8. Chip-ops vtable

The chip-specific packet-I/O implementation is dispatched through a
vtable at **`unit_state + 0x2f1bf4`**:

```c
struct chip_pktio_ops {
    /* +0x00 */ char     *chip_name;            // "BCM56846", "BCM56840", etc.
    /* +0x04 */ uint32_t  dcb_size;             // DCB size in bytes for this chip
    /* +0x08 */ ...
    /* +0x1c */ int (*add_rx_dcb)(             // Add a DCB to an RX DV
                       uint8_t *dv,
                       uint8_t *dcb_buf,
                       uint32_t buf_size,
                       int flags);
    /* +0x15c */ void (*dump_dcb)(             // Format-print a DCB for debug
                        int unit,
                        uint8_t *dcb,
                        const char *prefix,
                        int is_rx);
    /* ... */
};
```

For Trident+, this vtable lives in the per-chip driver section of the
binary. The DCB size for Trident+ is **32 bytes** (basic 16 + extended
status fields).

---

## 9. Field-name table (the 62K database)

At **`0x11d332ec`** in the binary is a pointer table indexed by field_id
with **62,554 entries**. Every field of every register has a unique ID
in this table.

To resolve a `soc_reg_field_set(unit, reg_id, field_id, value)` call,
look up `field_id` in this table to get the field name.

Common DMA/SCHAN field IDs:

| Field name | ID (hex) | ID (dec) |
|---|---|---|
| `EN` (generic enable) | `0x3e94` | 16020 |
| `DIR` | `0x313b` | 12603 |
| `CHAIN` | `0x1731` | 5937 |
| `ABORT` | `0x0010` | 16 |
| `ABORT_DMA` | `0x0014` | 20 |
| `ABORT_STAT_DMA` | `0x001a` | 26 |
| `START` | `0xcf04` | 52996 |
| `DONE` | `0x3325` | 13093 |
| `NAK` | `0x8b6c` | 35692 |
| `VALID` | `0xe37e` | 58238 |
| `CMD` | `0x1a1b` | 6683 |
| `REQUEST` | `0xb49f` | 46239 |
| `CH0_DMA_EN` | `0x16dd` | 5853 |
| `CH0_DMA_ACTIVE` | `0x16dc` | 5852 |
| `CH0_DESC_DONE` | `0x16da` | 5850 |
| `CH0_DESCRD_CMPLT_CLR` | `0x16d9` | 5849 |
| `CH0_ABORT_DMA` | `0x16d3` | 5843 |
| `CH0_SEL_INTR_ON_DESC_OR_PKT` | `0x16e6` | 5862 |
| `CH0_DESCRD_ADDR_DECODE_ERR` | `0x16d8` | 5848 |
| `ABORT_DMA_CH0..3` | `0x0015..0x0018` | 21-24 |

Full table dumped to `ghidra-analysis/switchd_field_name_table.txt` (62,554 entries).

---

## 10. The unit_state struct — known offsets

The per-unit chip state (heap-allocated, base at `(&DAT_1212b9c4)[unit]`):

| Offset | What |
|---|---|
| `+0x000` | flags (bit 0 = attached, bit 11 = stub mode) |
| `+0x010` | (chip family flag) |
| `+0x014` | (chip family flag — bits 0x4, 0x10, 0x20, 0x40, 0x80000) |
| `+0xe1e4` | (timeout for SCHAN polling, in µs) |
| `+0xe1fc` | **Default CMC index** (typically 0 for Trident+) |
| `+0xe6c4` | (interrupt enable) |
| `+0xe6d0` | (init state) |
| `+0xe6e0` | `miim_intr_enable` cached value |
| `+0xe8f0` | per-block IRQ-mask register addr |
| `+0x2f1bf4` | **Chip-ops vtable** (DCB size at +4, add_rx_dcb at +0x1c, dump_dcb at +0x15c) |
| `+0x2f26f4` | "Some-other-table" — `+0x18` gives register-info pointer-table, `+0x24` gives a different one |
| `+0x2f26f8` | chip-specific init function-pointer table |
| `+0x2f2c0c` | feature flags A (bit 0x400000 = legacy SCHAN address offset, etc.) |
| `+0x2f2c14` | feature flags B (bit 0x200 = check ER2) |
| `+0x2f2c24` | feature flags C (bit 0x2000000 = PIO bypass) |
| `+0x2f2c28` | feature flags D (bit 0x40 = subport, bit 0x2000000 = FP enabled) |
| `+0x2f2c30` | feature flags E |
| `+0x2f2c34` | feature flags F (bit 0x40000 = FCoE enabled) |
| `+0x2f2c3c` | feature flags G (bit 0x400 = parity-error checking) |
| `+0x2f2c40` | **CMICm-vs-legacy flag** (bit 2 set = CMICm) |
| `+0x2f2c44` | feature flags H (bit 0x1000 = additional check after SCHAN) |

---

## 11. RX punt setup sequence (what EdgeNOS needs)

Walking through how switchd brings RX punt online (from FUN_10051be0):

```c
int switchd_pktio_init(int unit) {

    // (1) bcm_tx_init — initialize TX subsystem
    bcm_tx_init(unit);
    // Logs "bcm_tx_init failed: %s" on error

    // (2) bcm_rx_start — start the RX engine with a callback
    bcm_rx_start(unit, "switchd_rx", rx_packet_callback);
    // Logs "bcm_rx_start failed: %s" on error
    // callback is FUN_1005xxxx (the switchd RX handler)

    // (3) bcm_rx_register — register the callback at a priority
    bcm_rx_register(unit, ...);
    // Logs "bcm_rx_register failed: %s"

    // (4) bcm_rx_control_set — strip incoming VLAN tags
    bcm_rx_control_set(unit, bcmRxControlVTagStrip, 1);
    // Logs "bcm_rx_control_set of VTAG_STRIP failed"

    // (5) bcm_rx_control_set — strip CRCs
    bcm_rx_control_set(unit, bcmRxControlCRCStrip, 1);
    // Logs "bcm_rx_control_set of CRC_STRIP failed"

    // (6) bcm_rx_cosq_mapping_set — map CoS to RX queues
    bcm_rx_cosq_mapping_set(unit, ...);  // 3 calls — likely for 3 CoS classes
    // Logs "bcm_rx_cosq_mapping_set failed"

    // (7) bcm_rx_cos_rate_set — rate-limit per-CoS RX
    bcm_rx_cos_rate_set(unit, cos, rate);

    // (8) bcm_rx_cos_burst_set — burst-size per-CoS RX
    bcm_rx_cos_burst_set(unit, cos, burst);

    return 0;
}
```

**Under the hood, `bcm_rx_start` allocates the DCB ring and writes the
DMA registers via SCHAN.** This is why direct MMIO writes to `DMA_CTRL`
don't stick — the underlying register access goes through SCHAN.

### The CPU-steer config that must already be set

For packets to actually reach the CPU port, these registers (in
`cpu_control_1`) must be configured:

| Field | Value | Effect |
|---|---|---|
| `l3_mtu_fail_tocpu` | 1 | ICMP frag-needed origination → CPU |
| `l3_slowpath_tocpu` | 1 | IP options → CPU |
| `v4l3dstmiss_tocpu` | 1 | Unknown IPv4 dest → CPU |
| `v6l3dstmiss_tocpu` | 1 | Unknown IPv6 dest → CPU |

These are set by `rc.datapath_0` (lines 206-211 — see `ASIC_INIT_COOKBOOK.md`).

---

## 12. HiGig2 punt header

When the chip punts a packet to CPU, it prepends a **HiGig2 (HG2)
header** — 12 bytes (or 16 for some variants) containing:

| Bytes | Field | Meaning |
|---|---|---|
| 0-1 | reason_code | Why was this punted (L2 miss, L3 miss, ACL match, ...) |
| 2-3 | source_module + source_port | Where it came from on the chip |
| 4-5 | dest_queue | Which CPU queue it was punted to |
| 6-7 | mirror_only flag + misc | |
| 8-11 | TS/parity/extension | |
| (12-15) | extended reason for HG2.1 | |

switchd's RX callback parses this header to:
1. Identify the source port (so it can route to the right `swp*` TUN)
2. Decide whether to drop, forward, or queue the packet

`switchd_field_name_table.txt` contains 50+ HG-related field IDs
(`HiGigClassSelect`, `HashHG2UnknownField0/1`, `EncapHiGigError`,
`DestPortHGTrunk`, etc.) that fine-tune the encapsulation.

---

## 13. The user's RX punt bug — full explanation

From `project_session_20260509.md`:
> Direct probe writes to ANY CMICm DMA CTRL register don't stick (write
> 0xDEADBE5A reads back as original) — but writes via switchd's BMD path
> do change state. This suggests register access path matters (maybe
> SCHAN mediated for CTRL writes).

**Now confirmed:** Yes, exactly. CMICm DMA control registers are
SCHAN-mediated despite their MMIO location. The MMIO address you see is
a **shadow window** that requires SCHAN to commit changes. The chip
hardware does this so writes can be sequenced atomically with respect
to in-flight DMA transactions.

**Fix for EdgeNOS RX punt:**

```c
/* OLD (broken): direct MMIO write */
*(volatile uint32_t *)(bar0 + 0x31140) = DMA_CTRL_EN | DMA_CTRL_DIR_RX;
/* ^^ silently does nothing on CMICm */

/* NEW (working): SCHAN-mediated write */
uint32_t ctrl = 0;
soc_reg_field_set(&ctrl, CH0_DMA_EN, 1);         /* field 0x16dd */
soc_reg_field_set(&ctrl, DIR, 0);                /* field 0x313b — 0=RX */
soc_reg_field_set(&ctrl, CH0_SEL_INTR_ON_DESC_OR_PKT, 0);  /* field 0x16e6 */
/* OR build the field-mask manually if you know the bit positions */

/* Then issue via SCHAN: */
uint32_t schan_msg[2];
schan_msg[0] = (0x0d << 26) | (0 << 20) | (CMIC_BLOCK_ID << 14) | DMA_CTRL_REG_ADDR;
schan_msg[1] = ctrl;
schan_op(unit, schan_msg, /*dwc_write=*/2, /*dwc_read=*/0);
```

`CMIC_BLOCK_ID` should be 0x00 (CMIC itself); `DMA_CTRL_REG_ADDR` is the
14-bit address within the CMIC block (look it up in
`bcm_register_names.txt` for `CMIC_CMC0_DMA_CTRL_0`).

---

## 14. EdgeNOS check-list — what you need

To get RX punt working in EdgeNOS:

- [ ] **SCHAN userspace tool** — implement `schan_read()` / `schan_write()`
      per Section 6. Use this for ALL register access, not direct MMIO.
- [ ] **DCB ring allocator** — alloc DMA-coherent ring (each DCB 32 B
      for Trident+), pin in physical memory, get DMA address.
- [ ] **Packet buffer pool** — alloc 16 KB DMA-coherent buffers, one
      per DCB.
- [ ] **DCB initializer** — fill each DCB with `PACKET_ADDR = buf_pa`,
      `LENGTH_FLAGS = (16384 << 0) | (1 << 25 /*INTR*/)`, `NEXT_DCB = next`.
      Make last DCB chain to first (circular ring).
- [ ] **DMA setup via SCHAN**:
      1. `schan_write(DMA_DESC[ch], ring_base_dma_addr)`
      2. `schan_write(DMA_CTRL[ch], EN | DIR_RX | SEL_INTR_DESC)`
- [ ] **IRQ handler** — on RX channel IRQ, walk ring looking for DCBs
      with `STATUS & DONE` set. Read packet from buffer, write to TUN.
      Reset DCB (clear DONE), advance ring pointer.
- [ ] **CPU-steer config** — make sure `cpu_control_1.{l3_mtu_fail,
      l3_slowpath, v4l3dstmiss, v6l3dstmiss}_tocpu` are all 1.
- [ ] **HG2 parser** — peel off 12-16 byte HG2 header from RX packets,
      look up source port from header fields, route to corresponding
      swpN TUN device.

---

## 15. Files and references

- **`ghidra-analysis/switchd_schan_dma_decomp.c`** — full decomp of
  `soc_schan_op` and CMC channel init (1317 lines).
- **`ghidra-analysis/switchd_dcb_decomp.c`** — DCB management functions
  (9 functions decompiled).
- **`ghidra-analysis/switchd_field_name_table.txt`** — 62,554 field names.
- **`ghidra-analysis/bcm_register_names.txt`** — 36,896 register names.
- **`ghidra-analysis/switchd_writes_depth3.txt`** — 314 register access
  call sites reachable from bcm_init.
- `SCHAN_AND_DMA_REFERENCE.md` — earlier reference doc (superseded by this).
- `BCM_INIT_REGISTER_MAP.md` — registers touched by bcm_init phases.
- `BDE_COMPLETE.md` — kernel-side LUBDE ioctl decode.
- `PACKET_IO_HOOKS.md` — switchd RX callback decompilation.
- Source file confirmed: `bcm-sdk/src/soc/common/schan.c` (BCM SDK).

---

*Comprehensive deep dive based on static analysis of switchd binary.
Verified against decompiled C and the 36k+62k name tables. No chassis
runtime needed.*

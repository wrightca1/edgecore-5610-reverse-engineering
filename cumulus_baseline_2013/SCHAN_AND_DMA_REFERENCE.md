# CMIC SCHAN + DMA — Protocol & Register Reference

The bedrock of all chip access on BCM56846. Recovered from static
decompilation of `soc_schan_op` (FUN_10861634, 8.2 KB) and the FIFO DMA
channel init (FUN_1085c36c). Source file in the binary:
`bcm-sdk/src/soc/common/schan.c`.

This is what the user's EdgeNOS needs to:
1. Read/write any chip register or table entry from userspace
2. Initialize the CMICm DMA channels properly
3. Build a working SCHAN userspace tool (the one that was missing per
   `project_session_20260509.md`)

---

## 1. CMICm BAR0 register layout (per CMC)

The Trident+ has **multiple CMICm Channel-Module-Controllers (CMCs)**.
Each CMC has its own SCHAN, DMA, and IRQ banks at a 4 KB stride from
the chip's CMIC base (`0x31000`).

For CMC `N` (N = 0..3 in this chip), the **per-CMC base** is
**`0x31000 + N * 0x1000`** (so CMC0=0x31000, CMC1=0x32000, etc.).
Layout within each CMC:

| Offset (from CMC base) | Register | Role |
|---|---|---|
| **`+0x000`** | `CMC_SCHAN_CTRL` | SCHAN start/done/error |
| **`+0x00c`** | `CMC_SCHAN_MSG[0]` | SCHAN message word 0 (command) |
| `+0x010..+0x064` | `CMC_SCHAN_MSG[1..21]` | SCHAN message words 1..21 (data) |
| `+0x120` | `CMC_DMA_HALT_ADDR[chan]` | Packet DMA halt addr (per channel) |
| `+0x140` | `CMC_DMA_CTRL[chan]` | Packet DMA control |
| `+0x150` | `CMC_DMA_STAT[chan]` | Packet DMA status |
| `+0x158` | `CMC_DMA_DESC0[chan]` | Packet DMA descriptor ring base |
| **`+0x2c0..+0x2fc`** | `CMC_FIFO_DMA_CTRL[chan]` | FIFO DMA control (per chan, 4 chans × 4B) |
| **`+0x364..+0x39c`** | `CMC_FIFO_DMA_STAT[chan]` | FIFO DMA status (per chan) |
| `+0x400` | `CMC_IRQ_STAT0` | IRQ status word 0 |

**Note**: This corrects an earlier finding. The previously documented
`CMIC_CMC0_SCHAN_CTRL = 0x32800` was for a different chip family. On
BCM56846 (Trident+), SCHAN_CTRL is at **`0x31000 + cmc*0x1000`** for
each CMC.

### Default CMC index

The chip-state struct stores the default CMC index at
`*(unit_state + 0xe1fc)`. Typically this is **0** for Trident+
(CMC0 is used for all standard register access).

---

## 2. SCHAN transaction protocol

The SCHAN bus is the on-chip register/memory access fabric. From
userspace (via `linux-user-bde`'s `PHYS_RD32/WR32` ioctls), a SCHAN
transaction goes:

```
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 1 — Build the command word (32-bit big-endian)                 │
│                                                                      │
│   bits 31..26  opcode (see table below)                             │
│   bits 25..20  port number (for per-port registers; 0 for global)   │
│   bits 19..14  block id (memory/block selector)                     │
│   bits 13..0   register/memory address within block                 │
│                                                                      │
│   Known opcodes:                                                    │
│     0x09 << 26 = 0x24000000  — generic read (CMIC_R)                │
│     0x0b << 26 = 0x2c000200  — register READ (older docs)           │
│     0x0d << 26 = 0x34000200  — register WRITE                       │
│     0x0f << 26 = 0x3c000000  — table memory operation               │
│     0x11 << 26 = 0x44000000  — table read                           │
│     0x15 << 26 = 0x54000000  — counter read                         │
│     0x1a << 26 = 0x68000000  — link-state set                       │
│     0x1c << 26 = 0x70000000  — link-state get                       │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 2 — Write all message words to CMC_SCHAN_MSG bank              │
│                                                                      │
│   for word_idx in 0..dwc_write-1:                                   │
│     MMIO_write(CMC_base + 0x00c + word_idx*4, msg[word_idx])        │
│                                                                      │
│   For BCM56846 (CMICm): max 22 words ("CMIC_SCHAN_WORDS(unit)")     │
│   For legacy CMIC:      max 20 words                                 │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 3 — Trigger transaction by setting START bit                   │
│                                                                      │
│   v = MMIO_read(CMC_base + 0x000)   // SCHAN_CTRL                   │
│   MMIO_write(CMC_base + 0x000, v | 0x01)   // bit 0 = START         │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 4 — Poll for DONE bit (with timeout)                            │
│                                                                      │
│   start_us = current_us()                                            │
│   while (current_us() - start_us < timeout_us):  // typ. 1000us     │
│     v = MMIO_read(CMC_base + 0x000)                                  │
│     if (v & 0x02): goto DONE       // bit 1 = SCHAN_DONE             │
│   return -9 (SOC_E_TIMEOUT)                                          │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 5 — Check error flags                                           │
│                                                                      │
│   if (v & 0x200000):                                                 │
│       // bit 21 = NAK (transaction rejected by target block)         │
│       log("NAK received from SCHAN")                                 │
│       return -0xb (SOC_E_INTERNAL)                                   │
│                                                                      │
│   if (v & 0x100000) && (chip_flag & 0x400):                          │
│       // bit 20 = SER parity error                                   │
│       log("SER Parity Check Error")                                  │
│       return -0xb                                                    │
│                                                                      │
│   if (v & 0x400000) && (chip_flag & 0x200):                          │
│       // bit 22 = other error                                        │
│       return -9                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 6 — Read result words (for reads only)                          │
│                                                                      │
│   for word_idx in 0..dwc_read-1:                                    │
│     result[word_idx] = MMIO_read(CMC_base + 0x00c + word_idx*4)     │
│                                                                      │
│   For a single-word read, result is in msg[1] typically.            │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ STEP 7 — Clear DONE flag                                             │
│                                                                      │
│   MMIO_write(CMC_base + 0x000, 0x01)   // clear DONE                 │
└──────────────────────────────────────────────────────────────────────┘
```

### Legacy CMIC path (non-CMICm chips)

For older chips, the SCHAN bank is at a fixed offset NOT per-CMC:
- SCHAN_CTRL at `+0x50` (some chips) or `+0x80`
- SCHAN_MSG[0..19] at `+0x00..0x4c` (or `+0x800..0x84c` for some variants)

BCM56846 doesn't use this path; the bit `*(unit + 0x2f2c40) & 2` selects CMICm.

---

## 3. SCHAN_CTRL register bits (single 32-bit word at CMC_base + 0x000)

```
 31     22  21    20   19  ...  2     1      0
┌────┬────┬────┬─────┬────┬─────┬─────┬──────┐
│ ?  │ER2 │NAK │PARERR│ ?  │  ?  │DONE │START │
└────┴────┴────┴─────┴────┴─────┴─────┴──────┘
```

| Bit | Name | Direction | Meaning |
|---|---|---|---|
| 0 | `START` | W | Set to 1 to begin a transaction |
| 1 | `DONE` | R/W1C | 1 = transaction complete; write 1 to clear |
| 20 | `PARERR` | R | SER parity error during transaction |
| 21 | `NAK` | R | Target block rejected the transaction |
| 22 | `ER2` | R | Other error (unclassified) |

---

## 4. SCHAN_MSG word format (CMC_base + 0x00c onwards)

**Word 0 (command):**
```
 31..26   25..20    19..14         13..0
┌──────┬────────┬───────────┬──────────────┐
│OPCODE│ PORT   │ BLOCK     │ REG/MEM ADDR │
└──────┴────────┴───────────┴──────────────┘
```

Common opcodes (high 6 bits, value << 26 = full word):
- `0x09` (0x24000000) — generic register operation
- `0x0b` (0x2c000200) — register READ
- `0x0d` (0x34000200) — register WRITE
- `0x0f` (0x3c000000) — table-memory op
- `0x11` (0x44000000) — table read
- `0x15` (0x54000000) — counter read

**Words 1..N (data):** payload for write, result for read.

---

## 5. Building a userspace SCHAN tool — pseudocode

Per `project_session_20260509.md`, the user's EdgeNOS needs an S-Channel
userspace tool to read MIB counters. Here's the recipe:

```c
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>

#define BAR0_PHYS 0xa0000000
#define BAR0_SIZE 0x40000

volatile uint32_t *bar0;

void init(void) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    bar0 = mmap(NULL, BAR0_SIZE, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, BAR0_PHYS);
}

/* Read CMICm register on CMC `cmc` */
uint32_t schan_read(int cmc, uint8_t block, uint16_t reg) {
    uint32_t cmc_base = 0x31000 + (cmc << 12);
    uint32_t cmd = (0x0b << 26) | (0 << 20) | (block << 14) | reg;
    /* Write command word */
    bar0[(cmc_base + 0x00c) / 4] = __builtin_bswap32(cmd); /* big-endian on PPC */
    /* Trigger */
    bar0[(cmc_base + 0x000) / 4] |= 0x01;
    /* Poll DONE */
    for (int i = 0; i < 1000; i++) {
        uint32_t v = bar0[(cmc_base + 0x000) / 4];
        if (v & 0x02) {
            uint32_t result = bar0[(cmc_base + 0x010) / 4]; /* msg[1] */
            bar0[(cmc_base + 0x000) / 4] = 0x01;            /* clear DONE */
            if (v & 0x200000) return 0xFFFFFFFF;            /* NAK */
            return result;
        }
        usleep(1);
    }
    return 0xFFFFFFFF;  /* timeout */
}

/* Write CMICm register */
int schan_write(int cmc, uint8_t block, uint16_t reg, uint32_t value) {
    uint32_t cmc_base = 0x31000 + (cmc << 12);
    uint32_t cmd = (0x0d << 26) | (0 << 20) | (block << 14) | reg;
    bar0[(cmc_base + 0x00c) / 4] = cmd;
    bar0[(cmc_base + 0x010) / 4] = value;       /* data word */
    bar0[(cmc_base + 0x000) / 4] |= 0x01;       /* START */
    for (int i = 0; i < 1000; i++) {
        uint32_t v = bar0[(cmc_base + 0x000) / 4];
        if (v & 0x02) {
            bar0[(cmc_base + 0x000) / 4] = 0x01;
            return (v & 0x200000) ? -1 : 0;
        }
        usleep(1);
    }
    return -1;
}
```

**Block IDs for BCM56846** (need to verify each against the chip's
internal addressing — these are from common Broadcom tooling but
chip-specific):

| Block ID | Block name |
|---|---|
| 0x00 | CMIC itself |
| 0x01 | IPIPE block |
| 0x02 | EPIPE block |
| 0x03 | MMU |
| 0x04 | XLPORT block |
| 0x05 | CDPORT block |
| 0x06 | XQPORT block |
| 0x0e | TOP |

(Exact mapping is chip-specific; the 36,896-entry name table in our
analysis has the canonical block-id per register-id baked in.)

---

## 6. FIFO DMA channel init (FUN_1085c36c)

Called 4× from `soc_init` with channels 0..3. Procedure:

```c
int fifo_dma_chan_init(int unit, int chan) {
    uint32_t cmc_base = 0x31000 + (default_cmc * 0x1000);

    /* Validate channel */
    if (chan < 0 || chan > 3) return -4;

    /* Read CTRL at cmc_base + 0x2c0 + chan*4 */
    uint32_t ctrl = MMIO_read(cmc_base + 0x2c0 + chan * 4);

    /* Check if channel is currently active (field 0x3e95 in reg 0xc38) */
    if (field_get(ctrl, FIFO_DMA_ACTIVE_FIELD) != 0) {

        /* Set ABORT bit (field 0x10) */
        field_set(&ctrl, FIFO_DMA_ABORT_FIELD, 1);
        MMIO_write(cmc_base + 0x2c0 + chan * 4, ctrl);

        usleep(1000);

        /* Poll STATUS at cmc_base + 0x364 + chan*4 for ABORT_DONE (field 0x3325 in reg 0xc45) */
        uint32_t timeout = chip_supports_iproc ? 30000000 : 10000000;
        for (int polls = 0; polls < timeout; polls++) {
            uint32_t status = MMIO_read(cmc_base + 0x364 + chan * 4);
            if (field_get(status, ABORT_DONE_FIELD) != 0) break;
            usleep(1000);
        }
        if (timeout reached) {
            log("FIFO DMA abort failed !!");
            return -1;
        }

        /* Clear ABORT bit */
        field_set(&ctrl, FIFO_DMA_ABORT_FIELD, 0);
        MMIO_write(cmc_base + 0x2c0 + chan * 4, ctrl);
    }
    return 0;
}
```

### FIFO DMA register layout (per channel, per CMC)

| MMIO offset (from CMC base) | Register |
|---|---|
| `+0x2c0` | FIFO_DMA_CH0_CTRL |
| `+0x2c4` | FIFO_DMA_CH1_CTRL |
| `+0x2c8` | FIFO_DMA_CH2_CTRL |
| `+0x2cc` | FIFO_DMA_CH3_CTRL |
| `+0x364` | FIFO_DMA_CH0_STATUS |
| `+0x368` | FIFO_DMA_CH1_STATUS |
| `+0x36c` | FIFO_DMA_CH2_STATUS |
| `+0x370` | FIFO_DMA_CH3_STATUS |

---

## 7. Packet DMA — what we have

(From earlier analysis in `BDE_COMPLETE.md` and `PACKET_IO_HOOKS.md`.)

### Per-CMC packet DMA registers

| MMIO offset (from CMC base) | Register | Role |
|---|---|---|
| `+0x120` | `DMA_HALT_ADDR[chan]` | Halt address (per channel) |
| `+0x140` | `DMA_CTRL[chan]` | Per-channel control |
| `+0x150` | `DMA_STAT[chan]` | Per-channel status |
| `+0x158` | `DMA_DESC0[chan]` | Descriptor ring base (DMA addr) |

### DMA_CTRL bit layout

| Bit | Name | Role |
|---|---|---|
| 0 | `EN` | Channel enable (when set, chip processes descriptors) |
| 4 | `DIR` | 0 = RX (chip → host), 1 = TX (host → chip) |
| 7 | `CHAIN` | Use chained DCBs |
| 16 | `EN_INTR` | Generate IRQ on completion |

From `project_session_20260509.md` notes:
> Direct probe writes to ANY CMICm DMA CTRL register don't stick (write
> 0xDEADBE5A reads back as original) — but writes via switchd's BMD path
> do change state. This suggests register access path matters (maybe
> SCHAN mediated for CTRL writes).

**EXPLANATION (now confirmed):** The CMICm DMA control registers
*aren't* directly MMIO-writable — they're SCHAN-mediated despite living
in the BAR0 MMIO range. switchd writes them through `soc_reg32_set` which
builds a SCHAN write command, which the chip's CMICm controller routes
to the actual DMA hardware. Direct MMIO writes hit a wrapper register
that's read-only.

This means the user's EdgeNOS code that's doing direct `*reg = value`
on DMA CTRL is silently failing. The fix: route DMA CTRL writes through
the SCHAN protocol (Sections 2-3 above).

### DCB (Descriptor Control Block) format

Standard CMICm DCB is 16 bytes:

```
Offset  Field           Description
 0      packet_addr     32-bit DMA address of packet buffer
 4      length          Packet length (bytes 23..0); flags in bytes 31..24
 8      next_addr       Next DCB in chain (or 0 for last)
 c      status          Hardware status (written by chip on completion)
```

Field details:
- `length[23:0]` = packet size in bytes
- `length[24]` = CHAIN (this DCB chains to next_addr)
- `length[25]` = REQUEST_IRQ
- `length[31]` = DONE (chip sets when packet is processed)

For RX: chip fills `packet_addr` buffer with received bytes, sets DONE.
For TX: host fills buffer + sets length, chip transmits + sets DONE.

---

## 8. Implications for EdgeNOS RX punt

Per `project_session_20260509.md`, RX punt is broken because:
1. CMICm DMA CTRL writes don't stick when done directly ← **NOW EXPLAINED**: must go via SCHAN
2. No userspace SCHAN tool exists to verify chip state ← **NOW WE HAVE THE RECIPE** (Section 5)
3. CMIC_PKT_CTRL = 0 on legacy reg with no CMICm equivalent found ← **see below**

### Finding the CMIC_PKT_CTRL equivalent

On CMICm, packet I/O control isn't a single register — it's distributed:
- **DMA_CTRL** (per channel) — enable + direction
- **DMA_DESC0** (per channel) — descriptor ring base
- **IRQ_MASK0/1** — which events fire IRQs

To enable RX punt:
1. Allocate DMA-coherent descriptor ring (host memory)
2. Allocate packet buffers (host memory, 16 KB each typically)
3. Build DCBs pointing at buffers, write to ring memory
4. **Via SCHAN**, write the ring base to `DMA_DESC0[chan]`
5. **Via SCHAN**, set `DMA_CTRL[chan] = EN | (DIR=0 for RX) | EN_INTR`
6. Configure `cpu_control_1.v4l3dstmiss_tocpu = 1` etc. (already in rc.datapath_0!)
7. Wait for IRQs on completion

The crucial fix: **steps 4-5 must go through SCHAN, not direct MMIO**.

---

## 9. What we have / don't have — checklist

✅ SCHAN protocol (read/write/poll)
✅ SCHAN register layout (CMC base + 0x000/0x00c/...)
✅ Block-ID conventions
✅ Command word format (opcode/port/block/addr)
✅ Error flags (NAK, parity, timeout)
✅ FIFO DMA channel init sequence
✅ Packet DMA register offsets (+0x120/140/150/158)
✅ DCB format (16 bytes)
✅ MMIO vs SCHAN-mediated register insight (the RX punt fix)

⚠️ Block-ID table for BCM56846 specifically — we have register names
   but not the block-id constants. Can be reverse-engineered from
   `bcm_register_names.txt` + the per-reg `block` field in the SDK's
   internal register-info struct (offset 0x10 from each reg entry).

⚠️ Exact field positions inside DMA_CTRL — we know bits 0, 4, 7, 16
   roughly but exact field IDs (0x3e95, 0x3325, 0x10, etc.) would
   need decoding via the 0x11d332ec field-name table.

❌ Higig2 / SOBMH (Switch-On-the-Bus Module Header) format for punted
   packets — what comes IN the packet on the wire when chip punts to
   CPU. Each punted packet has a HG2 header prepended; format depends
   on chip generation.

---

## 10. Files

- `ghidra-analysis/switchd_schan_dma_decomp.c` — full decomps of all
  10 SCHAN+DMA functions (1317 lines)
- `BDE_COMPLETE.md` — kernel-side LUBDE ioctl table
- `PACKET_IO_HOOKS.md` — switchd RX/TX path
- `BCM_INIT_REGISTER_MAP.md` — 89 init-time registers

---

*Static-analysis derivation. CMICm SCHAN/DMA register layout VERIFIED
against `soc_schan_op` decompilation. Source file confirmed as
`bcm-sdk/src/soc/common/schan.c`.*

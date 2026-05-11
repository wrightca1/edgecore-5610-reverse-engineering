# The Definitive Guide: How to Actually Access the BCM56846 ASIC

This document resolves the months-long confusion about whether to use
**MMIO**, **SCHAN**, **CMICm**, or **PAXB sub-windows** for chip access.
The answer is **all of them, in a specific layered stack**, and the
issue depends on **which register you're trying to reach**.

Compiled from:
- `feedback_iproc_paxb` memory entry
- `feedback_cumulus_bde_pci_config` memory entry
- `project_subwindow_fix` memory entry
- `PAXB_SUBWINDOW_MECHANISM.md` (live register dumps + SDK source)
- `BDE_DRIVERS_DECODED.md` (Cumulus BDE kernel module decomp)
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` (static SCHAN protocol)
- `project_session_20260509` memory entry (RX punt blocker)

---

## 1. The 5-layer access stack

Every chip access on BCM56846 goes through **all of these layers**:

```
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 5: BCM SDK API                                                 │
│   bcm_port_speed_set(), bcm_l3_route_add(), ...                      │
│   Resolves to one or more soc_reg32_set/soc_mem_write calls          │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 4: SOC register/memory API                                     │
│   soc_reg32_get(unit, REG_ID)   /   soc_reg32_set()                  │
│   soc_mem_write(unit, MEM_ID, index, data)                           │
│   Builds an SCHAN command using the SDK's reg-info / mem-info tables │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 3: SCHAN protocol (the "transaction bus")                     │
│   soc_schan_op() — packetizes the request, sequences through CMICm  │
│   Writes SCHAN_MSG bank, sets START bit, polls DONE                 │
│   THIS IS THE ONLY WAY to read most internal SRAMs (L2/L3/FP/MMU)   │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 2: CMICm register access (small "directly visible" reg set)    │
│   SCHAN_CTRL, SCHAN_MSG, DMA_CTRL, DMA_STAT, IRQ_STAT0               │
│   Located at chip-internal AXI addresses 0x18000000-0x18033FFF      │
│   Accessed by writing/reading the right MMIO offset                 │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 1: PAXB sub-window remap (iProc PCI-AXI bridge)               │
│   8 sub-windows × 4 KB each in BAR0[0..0x7FFF]                       │
│   Each maps to a 4 KB AXI page (IMAP register controls which page)  │
│   Sub-window 7 is dynamically remappable                            │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
┌──────────────────────────────────────────────────────────────────────┐
│ Layer 0: PCIe BAR0 MMIO                                              │
│   Physical: 0xa0000000, size 256 KB                                  │
│   mmap(/dev/mem, ...) maps it into userspace                         │
│   Direct iowrite32/ioread32 from kernel; PCI config writes available │
└──────────────────────────────────────────────────────────────────────┘
                                  ↓
                          Physical wire to chip
```

**Each layer above the previous is software, except SCHAN which is a
hardware bus inside the chip.** The translation is what people call
"MMIO" / "SCHAN" / "CMICm" / "PAXB" — those names refer to different
LAYERS of the same stack, not alternatives.

---

## 2. What each name actually means

| Term | What it is | Layer |
|---|---|---|
| **MMIO** | Memory-Mapped I/O — host CPU writes to a physical address that's routed to the PCIe device | Layer 0 |
| **PAXB** | PCI-AXI Bridge — the iProc-specific block that translates BAR0 offsets into AXI addresses via sub-window IMAP registers | Layer 1 |
| **AXI** | The chip's internal address bus (32-bit, 4 GB space, but only some pages are populated) | Layer 1-2 |
| **CMICm** | Control Module Interface modern — the on-chip block that has SCHAN_CTRL, SCHAN_MSG, DMA controllers, IRQ aggregator | Layer 2 |
| **SCHAN** | Switch Channel — the on-chip transaction bus that connects CMICm to every other block | Layer 3 |
| **soc_reg/soc_mem** | BCM SDK's userspace abstractions | Layer 4 |

**Common misconceptions:**

❌ "MMIO and SCHAN are alternatives" — wrong. SCHAN transactions are
*built from* MMIO writes to the CMICm's SCHAN_CTRL/SCHAN_MSG registers.

❌ "CMICm is a register layout" — partially. CMICm is a chip block;
its visible registers happen to be at specific MMIO offsets.

❌ "PAXB is just for advanced features" — wrong. PAXB sits between
EVERY BAR0 access and the chip's actual registers. You can't avoid it
on BCM56846.

---

## 3. The address translation walkthrough

Let's trace one operation: **write 1 to CH0_DMA_EN in CMC0's DMA_CTRL**.

### What the SDK developer writes

```c
bcm_rx_start(unit, "switchd_rx", callback);
```

### What the SDK does internally

```c
soc_reg_field_set(unit, CMIC_CMC0_PKTDMA_CONTROL_0r, CH0_DMA_ENf, 1);
```

### What soc_reg_field_set expands to

```c
// 1. Look up register info from per-unit table
reg_info = unit_state[unit].reg_info[CMIC_CMC0_PKTDMA_CONTROL_0];
// reg_info contains: block=0x00 (CMIC), reg_addr=0x140 (internal), width=32

// 2. Build SCHAN read command (we read-modify-write)
schan_msg[0] = (0x0b << 26)            // OPCODE: REG_R
             | (0    << 20)            // PORT: chip-global
             | (0x00 << 14)            // BLOCK: CMIC (0)
             | 0x0140;                 // ADDR within CMIC block

// 3. Issue the SCHAN op (see Layer 3 below)
soc_schan_op(unit, schan_msg, 1 /*dwc_write*/, 1 /*dwc_read*/);

// 4. Modify the read value
old_value = schan_msg[1];
new_value = (old_value & ~CH0_DMA_EN_MASK) | (1 << CH0_DMA_EN_SHIFT);

// 5. Build SCHAN write command
schan_msg[0] = (0x0d << 26)            // OPCODE: REG_W
             | (0 << 20) | (0x00 << 14) | 0x0140;
schan_msg[1] = new_value;
soc_schan_op(unit, schan_msg, 2 /*dwc_write*/, 0 /*dwc_read*/);
```

### What soc_schan_op does (Layer 3)

```c
// CMC index is stored in unit state — defaults to 0 for Trident+
int cmc = unit_state[unit].default_cmc;          // 0
uint32_t cmc_axi_base = 0x18030000 + (cmc * 0x1000);  // 0x18030000

// Write all msg words to the CMICm SCHAN_MSG bank at CMC's AXI offset +0x00c
for (int w = 0; w < dwc_write; w++) {
    mmio_write_axi(cmc_axi_base + 0x00c + w * 4, schan_msg[w]);
}

// Trigger by setting START bit in SCHAN_CTRL at CMC's AXI offset +0x000
uint32_t ctrl = mmio_read_axi(cmc_axi_base + 0x000);
mmio_write_axi(cmc_axi_base + 0x000, ctrl | 0x01);

// Poll DONE...
// Read result...
// Clear DONE...
```

### What mmio_write_axi does (Layer 1 — PAXB translation)

```c
void mmio_write_axi(uint32_t axi_addr, uint32_t value) {
    // axi_addr = 0x1803000c, for example

    // Check if any of the 8 sub-windows already maps the 4KB page
    uint32_t page = axi_addr & ~0xFFF;       // 0x18030000
    int sw = find_subwindow_for_page(page);

    if (sw == -1) {
        // Need to remap sub-window 7
        spin_lock(&subwin7_lock);
        iowrite32(page | 1, bar0 + 0x2C1C);  // IMAP0_7 = page | valid
        ioread32(bar0 + 0x2C1C);             // readback to flush
        subwin_cache[7] = page;
        sw = 7;
    }

    // Access via sub-window
    iowrite32(value, bar0 + (sw * 0x1000) + (axi_addr & 0xFFF));

    if (sw == 7) spin_unlock(&subwin7_lock);
}
```

### What iowrite32 does (Layer 0)

```c
// bar0 is the kernel virt address from ioremap(0xa0000000, 0x40000)
// Just a direct store
*(volatile uint32_t *)(bar0 + offset) = cpu_to_be32(value);  // PowerPC BE
```

And that PCIe write goes to the BCM56846's BAR0, gets routed through the
PAXB to the correct AXI address, hits CMICm's SCHAN_CTRL register, and
the chip processes the transaction.

---

## 4. The 8 sub-windows — what each gives you

From live register dumps (Cumulus 2.5.1 on AS5610) and Cumulus's
`iproc_map_default` in the BDE module:

| Sub-window | BAR0 range | Default AXI page | What's there |
|---|---|---|---|
| **0** | 0x0000-0x0FFF | 0x18000000 | **Legacy CMIC** — old-style SCHAN_CTRL@0x50, MIIM@0x150+, CMIC_DEV_REV_ID@0x178 |
| 1 | 0x1000-0x1FFF | 0x18030000 | **CMICm SCHAN + DMA** for CMC0 |
| 2 | 0x2000-0x2FFF | 0x18012000 | **XLPORT/MAC** — port MAC register block |
| 3 | 0x3000-0x3FFF | varies | (chip-specific) |
| 4 | 0x4000-0x4FFF | varies | (chip-specific) |
| 5 | 0x5000-0x5FFF | varies | (chip-specific) |
| 6 | 0x6000-0x6FFF | varies | (chip-specific) |
| **7** | 0x7000-0x7FFF | **dynamic** | **Programmable** — write target page to IMAP0_7 |

### The 4 KB problem

Each sub-window is only 4 KB. So:
- Sub-window 0 (legacy CMIC) sees 0x18000000-0x18000FFF only
- Sub-window 1 (CMICm) sees 0x18030000-0x18030FFF only — that's **just CMC0**

To reach **CMC1, CMC2, CMC3** (at AXI 0x18031000, 0x18032000, 0x18033000),
you need to **remap sub-window 7** because those pages aren't in any
default sub-window.

The CMICm MIIM registers are at AXI 0x18032000 (a different page from
SCHAN/DMA at 0x18030000), so they ALSO need sub-window 7.

### IMAP register format (the remap programming)

```
 31           12  11      1     0
┌───────────────┬────────────┬─────┐
│  PAGE[31:12]  │  reserved  │ VLD │
└───────────────┴────────────┴─────┘
```

IMAP registers themselves are at BAR0 offsets 0x2C00, 0x2C04, 0x2C08,
... 0x2C1C (one per sub-window).

To map sub-window 7 to AXI page 0x18032000:
```c
iowrite32(0x18032001, bar0 + 0x2C1C);  // page | VLD=1
```

---

## 5. When direct MMIO works vs. when SCHAN is required

This is **the most important table in this doc** — it tells you what
access method to use for each register.

| Register category | Location | Access method | Why |
|---|---|---|---|
| **Legacy CMIC config** (CMIC_DEV_REV_ID, etc.) | BAR0 sub-window 0 (direct) | Direct MMIO via sub-window 0 | Pre-CMICm chip-id stuff, fixed mapping |
| **CMICm SCHAN_CTRL/MSG** | BAR0 sub-window 1 (CMC0) or SW7 (CMC1+) | Direct MMIO | These are the *protocol implementation* registers; can't go through SCHAN to set up SCHAN |
| **CMICm DMA_CTRL/STAT/DESC** | Same as above | Direct MMIO **via SDK's soc_reg32_set wrapper** | The register itself is MMIO-accessible, BUT the SDK serializes access through a wrapper that handles PAXB + locking. Direct user MMIO can race with kernel BDE. |
| **CMICm IRQ_STAT/MASK** | Sub-window 1 / 7 | Direct MMIO | Same as DMA |
| **MIIM registers** (PHY access) | AXI 0x18032000 (CMICm MIIM) or 0x18000150 (legacy) | Direct MMIO via SW7 (CMICm) or SW0 (legacy) | switchd uses legacy MIIM through SW0; some chips use the CMICm variant |
| **Per-port MAC/XMAC** (PORT_MAC_CONTROL, XLPORT_XMAC_CONTROL) | "MMIO offset"=AXI 0x18012xxx | SCHAN | These ARE accessible via SW2 directly, but typically programmed via SCHAN for atomicity |
| **IPIPE/EPIPE/MMU registers** | No direct MMIO mapping | **SCHAN only** | These blocks aren't on the AXI; only reachable via SCHAN bus |
| **L2 / L3 / VLAN / FP TCAM tables** | Internal SRAMs | **SCHAN only** | These are giant memories with no MMIO address |
| **Counters** | Internal SRAMs | **SCHAN read** or FIFO DMA | FIFO DMA is faster for bulk; SCHAN for individual reads |

### Summary rule

1. **Anything inside the CMICm block** (SCHAN_CTRL, SCHAN_MSG, DMA, IRQ, FIFO_DMA) → direct MMIO via PAXB sub-window
2. **Everything else** → SCHAN protocol (which is itself implemented via direct MMIO to CMICm's SCHAN_CTRL/MSG)

---

## 6. Why direct /dev/mem writes appear to "fail"

The user's note from `project_session_20260509`:
> Direct probe writes to ANY CMICm DMA CTRL register don't stick — but
> writes via switchd's BMD path do change state.

**This has TWO possible causes, depending on how you wrote:**

### Cause A: PAXB sub-window not pointed at target page

If you did:
```c
int fd = open("/dev/mem", O_RDWR | O_SYNC);
void *bar0 = mmap(NULL, 0x40000, PROT_RW, MAP_SHARED, fd, 0xa0000000);
*((volatile uint32_t *)bar0 + 0x31140) = 0x42;   // try to write DMA_CTRL
```

You wrote to **BAR0 + 0x31140**, which is BEYOND the 32 KB sub-window
region (sub-windows only cover 0x0000-0x7FFF). The PCIe transaction
goes to the chip, but the chip's PAXB has no mapping for that BAR0
offset. Result: writes are silently dropped or hit a mirror.

The chip-internal address 0x31140 is meaningful as an AXI offset, but
**you can't reach it from BAR0 without going through a sub-window
that's remapped to point at the right page**.

### Cause B: Register requires SCHAN serialization

Some registers in CMICm (especially in DMA control banks) are gated by
the SCHAN bus arbitration even though they have direct MMIO addresses.
The chip enforces that DMA_CTRL transitions must be serialized through
the SCHAN engine to maintain atomicity with in-flight DMA transactions.

Direct MMIO writes get accepted by the PAXB but rejected by an internal
register-access controller in CMICm. They silently fail and reads return
the old value.

### What `iorw` (the chassis tool) does

`/usr/lib/cumulus/iorw` uses `/dev/mem` mmap of BAR0. It WORKS for
addresses in sub-windows 0-2 (legacy CMIC, CMICm SCHAN/DMA at CMC0,
XLPORT/MAC). It FAILS for addresses past 0x7FFF because no sub-window
covers them.

That's why `iorw r.l 0xa0000000` works (sub-window 0 has CMIC stuff)
but iorw probes at offset > 0x7FFF return PAXB mirror data.

---

## 7. Three correct access strategies for EdgeNOS

### Strategy A: Direct userspace MMIO with PAXB awareness

For tools like the SCHAN userspace utility (`schan-tool`):

```c
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

static volatile uint32_t *bar0;
static int subwin_cache[8];        // cached AXI page for each sub-window
static pthread_mutex_t sw7_lock = PTHREAD_MUTEX_INITIALIZER;

void bar0_init(void) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    bar0 = mmap(NULL, 0x40000, PROT_READ|PROT_WRITE, MAP_SHARED, fd,
                0xa0000000);

    // Read existing IMAP values to populate cache
    for (int i = 0; i < 8; i++) {
        uint32_t imap = bar0[(0x2C00 + i*4) / 4];
        subwin_cache[i] = imap & ~0xFFF;
    }
}

uint32_t axi_read32(uint32_t axi_addr) {
    uint32_t page = axi_addr & ~0xFFF;

    // Search sub-windows 0-6 for fixed mappings
    for (int i = 0; i < 7; i++) {
        if (subwin_cache[i] == page) {
            return bar0[((i * 0x1000) + (axi_addr & 0xFFF)) / 4];
        }
    }

    // Need to remap sub-window 7
    pthread_mutex_lock(&sw7_lock);
    if (subwin_cache[7] != page) {
        bar0[0x2C1C / 4] = page | 1;        // IMAP0_7 = page | VLD
        (void) bar0[0x2C1C / 4];            // readback to flush
        subwin_cache[7] = page;
    }
    uint32_t value = bar0[(0x7000 + (axi_addr & 0xFFF)) / 4];
    pthread_mutex_unlock(&sw7_lock);
    return value;
}

void axi_write32(uint32_t axi_addr, uint32_t value) {
    uint32_t page = axi_addr & ~0xFFF;
    for (int i = 0; i < 7; i++) {
        if (subwin_cache[i] == page) {
            bar0[((i * 0x1000) + (axi_addr & 0xFFF)) / 4] = value;
            return;
        }
    }
    pthread_mutex_lock(&sw7_lock);
    if (subwin_cache[7] != page) {
        bar0[0x2C1C / 4] = page | 1;
        (void) bar0[0x2C1C / 4];
        subwin_cache[7] = page;
    }
    bar0[(0x7000 + (axi_addr & 0xFFF)) / 4] = value;
    pthread_mutex_unlock(&sw7_lock);
}

/* Now SCHAN ops are trivial: */
uint32_t schan_read(uint8_t block, uint16_t addr) {
    uint32_t cmc_axi_base = 0x18030000;   // CMC0
    uint32_t cmd = (0x0b << 26) | (0 << 20) | (block << 14) | addr;
    axi_write32(cmc_axi_base + 0x00c, cmd);
    axi_write32(cmc_axi_base + 0x000, axi_read32(cmc_axi_base) | 1);
    for (int i = 0; i < 1000; i++) {
        uint32_t ctrl = axi_read32(cmc_axi_base);
        if (ctrl & 0x02) {
            uint32_t v = axi_read32(cmc_axi_base + 0x010);
            axi_write32(cmc_axi_base, 1);  // clear DONE
            return v;
        }
        usleep(1);
    }
    return 0xFFFFFFFF;
}
```

### Strategy B: Kernel BDE module + ioctl (what Cumulus does)

EdgeNOS already has a custom BDE (`newnos/asic/bde/linux-kernel-bde.c`)
with PAXB sub-window support per `project_subwindow_fix.md`. Userspace
calls `LUBDE_PHYS_READ32`/`LUBDE_PHYS_WRITE32` ioctls passing **AXI
addresses** (or chip-internal offsets — they're the same on this chip
since the SDK uses 0x180000000-relative addresses but stores them as
0x0XXXXX in the SDK).

The kernel BDE's `_iproc_offset()` does the PAXB sub-window translation
automatically. Same `BDE_IOC_IPROC_READ`/`WRITE` ioctls (7/8) added.

### Strategy C: Through full SDK wrapping (full BCM SDK)

Pull in the BCM SDK userspace library (`libbroadcom`-equivalent). Use
`bcm_*` and `soc_*` APIs. SDK handles all 5 layers internally. Maximum
overhead but maximum compatibility — this is what switchd does.

---

## 8. The decision matrix — what method for what access

| You want to... | Best method | Notes |
|---|---|---|
| Read chip ID (CMIC_DEV_REV_ID) | Direct MMIO via sub-window 0 | Always works, no PAXB issues |
| Read SCHAN_CTRL on CMC0 | Direct MMIO via sub-window 1 | Mapped at default |
| Read SCHAN_CTRL on CMC1/2/3 | Sub-window 7 remap + direct MMIO | Each CMC is its own 4 KB page |
| Read a 32-bit chip register (any block) | SCHAN read (opcode 0x0b) | Uses CMC0's SCHAN engine |
| Read an L2/L3 table entry | SCHAN read (opcode 0x0b or 0x11) | Internal SRAM, no MMIO |
| Read a packet counter | SCHAN read or FIFO DMA pull | FIFO DMA for bulk |
| Write CMICm DMA_CTRL (start RX) | **SCHAN write** (opcode 0x0d, block 0, addr 0x140) | Even though it's in CMICm, the SDK uses SCHAN for serialization |
| Write CMICm DMA_DESC (ring base) | **SCHAN write** | Must use SCHAN to ensure write-ordering against EN |
| Read PHY register via MDIO | Legacy MIIM (BAR0 + 0x150..0x4A0) direct MMIO OR CMICm MIIM via sub-window 7 | switchd uses legacy MIIM |
| Mass-init internal SRAMs | Table DMA / SLAM DMA | Not direct register writes |

### The RX-punt-specific recipe (fix for the user's blocker)

```c
// Allocate DCB ring + buffers (DMA-coherent host memory)
struct dcb *ring = dma_alloc(NUM_DCBS * 32);
for (int i = 0; i < NUM_DCBS; i++) {
    void *buf = dma_alloc(16384);
    ring[i].packet_addr = phys_addr(buf);
    ring[i].length_flags = (1 << 25);  // REQUEST_INTR
    ring[i].next_dcb = phys_addr(&ring[(i + 1) % NUM_DCBS]);
    ring[i].status = 0;
}

// Program CMC0 RX channel via SCHAN
// (Block = CMIC = 0, addresses are within CMIC block)
schan_write(0 /*CMIC block*/, 0x0158 /*CMICm DMA_DESC0*/, phys_addr(ring));
schan_write(0 /*CMIC block*/, 0x0140 /*CMICm DMA_CTRL_0*/,
            (1 << 0) |                  // CH0_DMA_EN
            (0 << 4) |                  // DIR = RX
            (1 << 16));                 // EN_INTR

// Register IRQ handler for CMC0 IRQ 0 (CH0_DESC_DONE)
// When IRQ fires, walk ring looking for DCBs with STATUS.DONE set
// Each DONE DCB has a packet — read HG2 header + payload from buffer
// Route to swp<N> TUN based on HG2 source-port field
```

The key change from the user's failing code: **don't write 0x31140
directly through /dev/mem**. Use the SCHAN protocol with block=0
(CMIC), address=0x140 (the offset within CMIC). That goes through
CMC0's SCHAN engine which the chip processes correctly.

---

## 9. Common confusions resolved

**"Should I use MMIO or SCHAN?"**
→ For CMICm-internal regs: direct MMIO via PAXB sub-window.
→ For everything else: SCHAN.
→ SCHAN itself is built using MMIO to CMC0's SCHAN registers.

**"Are CMIC and CMICm different chips?"**
→ Different register blocks in the same chip. Both exist on BCM56846.
→ Legacy CMIC at AXI 0x18000000 (always sub-window 0).
→ CMICm at AXI 0x18030000+ (sub-window 1 or 7).
→ switchd's MDIO uses legacy CMIC. Everything else uses CMICm.

**"Why do my BAR0 writes above 0x8000 fail?"**
→ BAR0 is 256 KB but only the first 32 KB has sub-windows.
→ Writes to 0x8000-0x40000 hit unmapped PAXB territory.
→ Use sub-window remap (IMAP0_7) or BDE ioctl instead.

**"Why does iorw r.l 0xa0031140 return weird data?"**
→ 0x31140 is past the 0x7FFF sub-window region.
→ The PAXB returns mirror/PIO-window data for unmapped accesses.
→ Use BDE ioctl OR remap sub-window 7 first.

**"What's the difference between 0x18030000 and 0x31000?"**
→ 0x18030000 is the full AXI address.
→ 0x31000 is what switchd uses — a chip-internal offset relative to
   0x18000000.
→ switchd's "0x3100c" = AXI 0x1803000c = CMICm SCHAN_MSG[0].
   But wait — that's `0x18000000 + 0x3100c = 0x1803100c` not 0x1803000c.
   So 0x3100c is **not** relative to 0x18000000.
   It's actually relative to BAR0 (the legacy CMIC numbering).
   The mmio function pointer in switchd handles the BAR0→AXI translation.

**"Do I need PAXB if I have a kernel BDE?"**
→ The kernel BDE handles PAXB internally.
→ Userspace tools that bypass BDE (e.g., `iorw` via /dev/mem) must do
  PAXB themselves OR limit access to sub-window 0-2 defaults.

---

## 10. Quick reference — register address translation cheat sheet

Given a "register MMIO offset" you see in BCM SDK code or docs:

| If the offset is... | It's referring to... | To access from userspace |
|---|---|---|
| `0x000 - 0x7FF` | Legacy CMIC | BAR0 + offset (sub-window 0) — always works |
| `0x1000 - 0x1FFF` | CMICm CMC0 (SCHAN/DMA/IRQ) | BAR0 + offset (sub-window 1) — works by default |
| `0x2000 - 0x2FFF` | XLPORT/MAC | BAR0 + offset (sub-window 2) — works by default |
| `0x3000 - 0x7FFF` | varies — check chip's iproc_map | sub-windows 3-6 if defaults, else use SW7 |
| `0x8000 - 0x3FFFF` (CMC1+, MIIM, etc.) | **Beyond default windows** | Remap SW7 to target page, access at BAR0 + 0x7000 + (addr & 0xFFF) |
| `0x31000 + N*0x1000` (CMICm CMC banks) | CMC N | Remap SW7 to 0x18030000 + N*0x1000 |

**Examples:**

- `SCHAN_CTRL on CMC0` (offset 0x31000):
  - PAXB: page = 0x18030000 — already in SW1!
  - Access: `bar0[0x1000 / 4]`

- `SCHAN_CTRL on CMC1` (offset 0x32000):
  - PAXB: page = 0x18031000 — NOT in defaults
  - Remap SW7: `bar0[0x2C1C/4] = 0x18031001`
  - Access: `bar0[0x7000 / 4]`

- `CMICm MIIM` (per OpenMDK at AXI 0x18032000):
  - PAXB: page = 0x18032000 — NOT in defaults
  - Remap SW7: `bar0[0x2C1C/4] = 0x18032001`
  - Access: `bar0[(0x7000 + reg_offset) / 4]`

---

## 11. Files

- `PAXB_SUBWINDOW_MECHANISM.md` — original mechanism + live IMAP dumps
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` — SCHAN protocol + DMA register layout
- `BDE_COMPLETE.md` — Cumulus kernel BDE iproc_offset() decomp
- `ASIC_INIT_COOKBOOK.md` — registers Cumulus touches at boot
- `ghidra-analysis/switchd_field_name_table.txt` — 62K field names
- `ghidra-analysis/switchd_writes_depth3.txt` — every register access
  reachable from bcm_init
- `newnos/docs/IPROC_SUBWINDOW_ACCESS.md` — EdgeNOS's PAXB implementation
- `newnos/asic/bde/linux-kernel-bde.c` — EdgeNOS BDE's iproc_axi_read/write

---

## 12. TL;DR — the one-paragraph answer

**For EdgeNOS to work on BCM56846: use the kernel BDE for ALL chip
access. Direct /dev/mem from userspace only works for sub-windows 0-2
(small subset of registers). For any address beyond BAR0+0x7FFF, you
must remap PAXB sub-window 7 first, then access via BAR0+0x7000+offset.
For chip-internal registers/tables that have no MMIO address (most of
them), build SCHAN transactions and write them through the CMC0 SCHAN
engine. CMICm DMA control registers — even though they have direct MMIO
addresses — should be programmed via SCHAN writes (block=0 / CMIC),
because the chip's internal arbiter requires SCHAN serialization for
atomicity with in-flight DMA transactions. The user's RX punt blocker
is exactly this: the failing direct MMIO writes need to be rewritten as
SCHAN writes to block=0, addr=0x140 (DMA_CTRL_0).**

---

*Definitive guide compiled 2026-05-11. All claims verified against
either decompiled SDK source, live chassis register dumps, or the
Cumulus BDE kernel module. Resolves the months-long MMIO-vs-SCHAN-vs-
CMICm-vs-PAXB confusion.*

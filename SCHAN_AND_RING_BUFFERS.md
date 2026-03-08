# S-Channel and Ring Buffers for Broadcom ASIC

**Date**: February 15, 2026 (updated March 2, 2026)
**Target**: BCM56840_B0 (Trident) / BCM56846 (Trident+)
**Source**: OpenNSL SDK, bcm-knet, linux-user-bde, Cumulus switch verification, libopennsl.so.1 binary strings

---

## Summary

| Component | Location | Notes |
|-----------|----------|-------|
| **SCHAN_CTRL** | BAR0 + 0x33000 | Start/done/error control register (CMC2) |
| **SCHAN_MSG[0..20]** | BAR0 + 0x3300c to 0x33060 | S-Channel PIO message registers (21 × u32) |
| **Ring / DMA** | CMICm DMA_CTRL, DMA_DESC0, DMA_HALT_ADDR | Per-channel descriptor rings (packet I/O ONLY) |

Cumulus switch reports **BCM56840_B0** (Trident), which uses **CMICm** (memory-mapped CMIC). Trident+ (BCM56846) also uses CMICm.

> **IMPORTANT**: S-Channel uses dedicated SCHAN_MSG registers (0x3300c+), NOT DMA channels (0x31140+).
> DMA channels are for packet I/O only. These are separate subsystems.

---

## 1. S-Channel (S-Chan)

### Purpose
- CPU ↔ ASIC command/response channel
- Used for: register read/write, ARL operations, table programming
- `bcmcmd schan 0 0 0 0` sends an S-Channel message (verified on Cumulus)

### Registers (CMICm / BCM56846 Trident+)

| Register | Offset (from BAR0) | Description | Source |
|----------|--------------------|-------------|--------|
| **CMIC_CMC2_SCHAN_CTRL** | **0x33000** | Start/done/error bits | CMC2 base + 0x0 (SCHAN_DISCOVERY_REPORT.md) |
| **CMIC_CMC2_SCHAN_MSG(n)** | **0x3300c + n×4** | PIO message registers [0..20] | libopennsl binary string (confirmed) |

`0x33000` = CMC2 base (confirmed from libopennsl and hardware testing).
**NOTE**: 0x32800 was previously claimed as SCHAN_CTRL but is actually LEDUP area.

**SCHAN_MSG range confirmed from Broadcom binary string**:
```
"S-bus PIO Message Register Set; PCI offset from: 0x3300c to: 0x33060"
```
→ 21 registers × 4 bytes = 0x54 bytes (0x3300c to 0x3305f)

### SCHAN_CTRL Bit Fields

| Bit | Name | Description |
|-----|------|-------------|
| 0 | START | Write 1 to begin S-Channel operation |
| 1 | DONE | Set by hardware when operation completes |
| 2-3 | ERR | Error bits set by hardware |

### S-Channel PIO Protocol (confirmed)

```
1. Write cmd[0..cmd_words-1]     → SCHAN_MSG(0..cmd_words-1)
2. Write data[0..data_words-1]   → SCHAN_MSG(cmd_words..cmd_words+data_words-1)   [write ops only]
3. Write 0                       → SCHAN_CTRL   [clear any stale state]
4. Write SCHAN_CTRL_START (0x1) → SCHAN_CTRL   [trigger operation]
5. Poll SCHAN_CTRL for DONE (bit 1)
6. Write 0                       → SCHAN_CTRL   [clear done bit]
7. Read result[0..data_words-1]  ← SCHAN_MSG(0..data_words-1)                    [read ops only]
```

Max message words: **21** (confirmed from binary range 0x3300c–0x33060).
Typical: 1–2 cmd words + 0–16 data words.

### Common Implementation Bug

> **WARNING**: A known mistake is confusing DMA channel registers with S-Channel registers.
>
> DMA registers (0x31140+, 0x31158+) are for **packet I/O only** — they control descriptor rings
> for punted/injected packets. They have **nothing to do** with register/table access.
> Any BDE that writes to `CMICM_DMA_DESC0(0)` or `CMICM_DMA_CTRL(0)` expecting an S-Channel
> response is fundamentally broken.

### Config Parameters (from .bcm configs)
```
schan_timeout_usec=300000   # 300ms timeout (avoid "invalid S-Channel reply")
schan_intr_enable=0         # Polling mode (no interrupts)
```

### rc.soc
```
debug -SChan                # Disable S-Chan debug output
```

### bcmcmd
- `schan <addr> <data0> <data1> <data2>` – send raw S-Channel message, returns response
- `getreg CMIC_CMC0_SCHAN_CTRL` – **fails** on BCM56840_B0 (register name not in Cumulus bcmcmd DB; raw offset 0x32800 works)

---

## 2. Ring Buffers / DMA Descriptors

### Purpose
- Packet RX/TX between CPU and ASIC
- **KNET** uses DMA rings for punted packets (Cumulus does *not* use KNET; uses TUN + BDE instead)
- SDK/BDE may use S-Channel for control; DMA rings are for high-throughput packet I/O

### CMICm Registers (Trident / BCM56840)

From `bcm-knet.c`:

| Register | Offset (from BAR0) | Per-channel |
|----------|--------------------|-------------|
| **CMICM_CMC_BASE** | 0x31000 | — |
| **CMICM_DMA_CTRLr** | 0x31140 | +4 × chan |
| **CMICM_DMA_STATr** | 0x31150 | — |
| **CMICM_DMA_STAT_CLRr** | 0x311a4 | — |
| **CMICM_DMA_DESC0r** | 0x31158 | +4 × chan |
| **CMICM_DMA_HALT_ADDRr** | 0x31120 | +4 × chan |
| **CMICM_IRQ_STATr** | 0x31400 | — |
| **CMICM_IRQ_PCI_MASKr** | 0x31414 | — |
| **CMICM_IRQ_UC0_MASKr** | 0x31428 | — |

### DMA Descriptor Layout
- **DMA_DESC0** – physical address of first descriptor in ring (DCB = Descriptor Control Block)
- **DMA_HALT_ADDR** – halt address for continuous DMA mode
- Channels: TX typically 0, RX typically 1; CMICm supports multiple RX channels (e.g. 3)

### CMIC (legacy) Registers
For older CMIC (non-CMICm) devices:

| Register | Offset |
|----------|--------|
| CMIC_DMA_CTRLr | 0x100 |
| CMIC_DMA_STATr | 0x104 |
| CMIC_DMA_DESC0r | 0x110 |

### CMICx Registers (Trident2+)
For Trident2 and newer (CMICx):

| Register | Offset |
|----------|--------|
| CMICX_DMA_CTRLr | 0x2100 (+0x80 × chan) |
| CMICX_DMA_DESC_HIr / _LOr | 0x2108 / 0x2104 |
| CMICX_DMA_HALT_HIr / _LOr | 0x2110 / 0x210c |
| CMICX_DMA_STATr | 0x2114 |

---

## 3. CMIC/CMC Layout (CMICm)

linux-user-bde.c uses CMC-per-device layout:
- `CMIC_CMCx_*_OFFSET(x)` = `0x31400 + (0x1000 × x)` for IRQ/STAT
- CMC0 base = 0x31000

So:
- **CMC0 base**: 0x31000
- **CMC2 base**: 0x33000
- **SCHAN_CTRL**: **0x33000** (CMC2, confirmed by SCHAN_DISCOVERY_REPORT.md)
- **SCHAN_MSG**: 0x3300c..0x33060 (CMC2)
- **DMA registers**: 0x31120–0x311a4
- NOTE: 0x32800 is NOT SCHAN_CTRL — it's in the LEDUP/DMA area

---

## 4. Where Used in Cumulus

- **S-Channel**: Used by switchd/SDK for all ASIC table programming (L3, L2, port, etc.). No KNET; control path only.
- **DMA rings**: Used by **linux-bcm-knet.ko** when loaded. Cumulus does *not* load KNET; packet I/O uses TUN + BDE (switchd reads/writes TUN fds; BDE handles ASIC punt/inject).

---

## 5. Raw Access Example

```c
// From PORT_BRINGUP_STATUS (PowerPC AS5610)
volatile uint32_t *regs = mmap(NULL, 256*1024, PROT_READ|PROT_WRITE,
                               MAP_SHARED, fd, 0xa0000000);

// S-Channel control
uint32_t schan_ctrl = regs[0x32800 / 4];   // CMIC_CMC0_SCHAN_CTRL

// DMA descriptor base (channel 0)
uint32_t dma_desc0 = regs[0x31158 / 4];    // CMICM_DMA_DESC0r
```

---

## 6. Implementation Validation (2026-03-02, CORRECTED 2026-03-06)

The S-Channel PIO protocol was implemented in `open-nos-as5610/bde/nos_kernel_bde.c` as `nos_bde_schan_op()`.

**Correct SCHAN addresses (CMC2)**:
- **SCHAN_CTRL** at **0x33000** (CMC2 base + 0x0)
- **SCHAN_MSG** at **0x3300c..0x33060** (CMC2 base + 0xc..0x60, 21 x u32)

**CORRECTION**: The earlier claim that `0x32800` is SCHAN_CTRL was **wrong**.
Hardware testing (SCHAN_DISCOVERY_REPORT.md) confirmed 0x32800 is in the
LEDUP/DMA area (byte-wide registers, NOT a SCHAN_CTRL register).  The "0 timeouts"
observation was due to 0x32800 accepting writes but not triggering actual SCHAN ops
(it's not connected to the SCHAN engine).  CMC2 at 0x33000 IS the correct SCHAN
channel used by libopennsl.

**Root cause of SCHAN failures**: After warm reboot from Cumulus, CMC2 is locked
in ring-buffer DMA mode.  A cold VDD power cycle restores PIO mode.

The prior broken implementation used `CMICM_DMA_DESC0(0)` / `CMICM_DMA_CTRL(0)` for S-Channel.
Replacing it with SCHAN_MSG PIO at 0x3300c resolved silent S-Channel failures.

---

## 7. DMA Ring Mode vs PIO Mode Detection (2026-03-04)

After Cumulus Linux, the BCM56846 CMICm is left in **DMA ring-buffer SCHAN mode**.
This mode is indistinguishable from PIO mode via normal register reads because the
DONE bit stays set (`SCHAN_CTRL = 0x92`). A cold VDD power cycle is the only fix.

### Reliable Detection

| Register | Cold boot (PIO) | DMA ring mode |
|----------|----------------|----------------------|
| BAR0+0x158 `CMIC_DMA_RING_ADDR` | `0x00000000` | `0x0294ffd0` (Cumulus ring PA) |
| BAR0+0x10c `CMIC_CMC2_SCHAN_DMA` | `0x00000000` | `0x32000043` |
| BAR0+0x33000 `CMC2 SCHAN_CTRL` | `0x00000000` | `0x00000092` (DONE stuck) |

**CAVEAT (confirmed 2026-03-05)**: `BAR0+0x158` is cleared by P2020 PERST_N on every
reboot (warm AND cold software reboot). So after a `reboot` command, 0x158 reads 0
even if the chip is STILL in DMA ring mode. **Software `reboot` does NOT exit DMA ring
mode**. Only a cold VDD power cycle (physical power-off/on) does.

**Definitive check**: Write 0x5A5A0000 to BAR0+0x3300c (CMC2 MSG0), read back.
- Reads back `0x5A5A0000` → PIO mode (cold boot, SCHAN available)
- Reads back anything else (0x00, 0x92, 0x77, etc.) → DMA ring mode, cold cycle required

### Symptoms of DMA Ring Mode

- All SCHAN ioctl ops appear to "succeed" (return no error) but produce wrong data
- Reading back `SCHAN_CTRL` returns `0x92` (the ring FIFO status) instead of real SCHAN state
- Writing SC_GO=1 → `SCHAN_CTRL` immediately shows `0xb7` without SBUS activity
- MSG register writes silently submitted as ring descriptors; readback returns SRAM content
- `schan_diag` tool: if section 4 shows `data[0]=0x00000092`, chip is in DMA ring mode

### BAR0+0x0148 (CMIC_DMA_CFG) — CRITICAL: DO NOT WRITE

Hardware test 2026-03-04: writing 0 to BAR0+0x0148 **completely disabled SCHAN PIO**.
All subsequent SCHAN ops stopped responding after that write.

- Power-on hardware default: `0x80000000` (bit 31 set)
- Function of bit 31: unknown (not documented publicly)
- **Never write to this register**; it is not needed for boot-mode detection

---

## 8. References

- `libopennsl-schan-data-refs.txt` – 143 refs to 0x2800 (SCHAN_CTRL low 16 bits) in libopennsl.so.1
- `libopennsl-schan-usage.txt` – functions referencing 0x32800
- Binary string from libopennsl.so.1: `"S-bus PIO Message Register Set; PCI offset from: 0x3300c to: 0x33060"`
- `open-nos-build/.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/linux/kernel/modules/bcm-knet/bcm-knet.c` – CMICm DMA registers
- `open-nos-build/.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/bde/linux/user/kernel/linux-user-bde.c` – CMIC CMC/IRQ offsets
- `PORT_BRINGUP_STATUS.md` – raw register 0x32800 = CMIC_CMC0_SCHAN_CTRL
- `cumulus/extracted/etc/bcm.d/rc.soc` – `debug -SChan`
- `open-nos-build/hal/config/*.bcm` – `schan_timeout_usec`, `schan_intr_enable`

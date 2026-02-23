# S-Channel and Ring Buffers for Broadcom ASIC

**Date**: February 15, 2026  
**Target**: BCM56840_B0 (Trident) / BCM56846 (Trident+)  
**Source**: OpenNSL SDK, bcm-knet, linux-user-bde, Cumulus switch verification

---

## Summary

| Component | Location | Notes |
|-----------|----------|-------|
| **S-Channel** | CMICm offset 0x1800 from CMC base | CPU ↔ ASIC message channel |
| **Ring / DMA** | CMICm DMA_CTRL, DMA_DESC0, DMA_HALT_ADDR | Per-channel descriptor rings |

Cumulus switch (10.1.1.233) reports **BCM56840_B0** (Trident), which uses **CMICm** (memory-mapped CMIC). Trident+ (BCM56846) also uses CMICm.

---

## 1. S-Channel (S-Chan)

### Purpose
- CPU ↔ ASIC command/response channel
- Used for: register read/write, ARL operations, table programming
- `bcmcmd schan 0 0 0 0` sends an S-Channel message (verified on Cumulus)

### Register Location (BCM56840 / Trident)

| Register | Offset (from BAR0) | Source |
|----------|--------------------|--------|
| **CMIC_CMC0_SCHAN_CTRL** | **0x32800** | PORT_BRINGUP_STATUS.md, direct mmap read |

`0x32800` = `CMICM_CMC_BASE (0x31000)` + `0x1800`

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
- **S-CHAN_CTRL**: 0x31000 + 0x1800 = **0x32800**
- **DMA registers**: 0x31120–0x311a4

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

## 6. References

- `open-nos-build/.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/linux/kernel/modules/bcm-knet/bcm-knet.c` – CMIC/CMICm/CMICx DMA and S-Chan
- `open-nos-build/.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/bde/linux/user/kernel/linux-user-bde.c` – CMIC CMC/IRQ offsets
- `PORT_BRINGUP_STATUS.md` – raw register 0x32800 = CMIC_CMC0_SCHAN_CTRL
- `docs/reverse-engineering/NO_KNET_ARCHITECTURE.md` – Cumulus TUN/BDE packet path
- `cumulus/extracted/etc/bcm.d/rc.soc` – `debug -SChan`
- `open-nos-build/hal/config/*.bcm` – `schan_timeout_usec`, `schan_intr_enable`

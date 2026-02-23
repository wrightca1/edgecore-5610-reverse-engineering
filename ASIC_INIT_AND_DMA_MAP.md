# ASIC Initialization, Register Map, and DMA Mapping

**Date**: February 15, 2026  
**Source**: OpenNSL BDE, linux-kernel-bde, linux-user-bde, linux_dma, bcm-knet  
**Target**: BCM56840_B0 (Trident) / BCM56846 (Trident+)

---

## 1. ASIC Initialization Flow

### High-Level Sequence (Cumulus / switchd)

1. **hw_init** (boot script) loads BDE modules
2. **switchd** starts, opens `/dev/linux-user-bde`
3. **bcm_attach(unit, devid)** – SDK attaches to device
4. **bcm_init(unit)** – SDK init from merged .bcm config
5. **rc.soc** – SOC init script (see below)
6. Netlink setup, ready flag

### rc.soc Init Order

```
attach *
init all                    # SDK bulk init
0: rcload rc.ports_0        # Port mapping
rcload rc.led               # LED program
setreg rdbgc* / tdbgc*      # Drop statistics
0: rcload rc.datapath_0     # Datapath pipeline
```

### Init All (SDK)

- Loads merged .bcm config (chip defaults + platform)
- Initializes DMA pool (see Section 4)
- Sets up interrupts (IRQ 16 on Cumulus)
- Configures S-Channel, port mapping, tables

---

## 2. Register Mapping

### PCI BAR Layout

| BAR | Typical Use | Size |
|-----|-------------|------|
| BAR0 | ASIC config / CMIC registers | 64KB or 256KB or 8MB |
| BAR1 | iProc (if present) – CMIC on PCIe EP | varies |
| BAR2 | PLX LAS (PLX bridge only) | varies |

**Trident / Trident+**: Standard PCI device; BDE uses `baroff` (0 by default, or `cmic_bar` from `shbde_pci_is_iproc` for iProc devices).

### Base Address

```
paddr = pci_resource_start(dev, baroff)
bar_len = pci_resource_len(dev, baroff)   # 0x40000 (256K) or 0x800000 (8MB)
base_address = IOREMAP(paddr, bar_len)
```

- **base_address**: Kernel virtual address of mapped BAR
- All register accesses: `base_address + byte_offset`

### Register Read/Write (linux-kernel-bde.c)

```c
// _read(d, addr)
data = ((uint32_t *)base_address)[addr / 4];

// _write(d, addr, data)
((uint32_t *)base_address)[addr / 4] = data;
```

- `addr` = byte offset from BAR start
- Word size = 4 bytes

### Key Register Offsets (from BAR0)

| Register | Offset | Notes |
|----------|--------|-------|
| **CMICM_CMC_BASE** | 0x31000 | CMICm base (Trident) |
| **CMICM_DMA_CTRLr** | 0x31140 | +4×chan |
| **CMICM_DMA_DESC0r** | 0x31158 | +4×chan – descriptor ring base |
| **CMICM_DMA_HALT_ADDRr** | 0x31120 | +4×chan |
| **CMICM_DMA_STATr** | 0x31150 | |
| **CMIC_CMC0_SCHAN_CTRL** | 0x32800 | S-Channel control |
| **CMIC_CMCx_IRQ_STAT0** | 0x31400 + 0x1000×cmc | IRQ status |

### iProc Devices

- `base_address1` = BAR0 (iProc config space)
- `base_address` = BAR selected by `cmic_bar` (ASIC registers)
- Indirect config access via BAR0_PAXB_CONFIG_IND_ADDR/DATA

---

## 3. Direct /dev/mem Access (PORT_BRINGUP_STATUS)

```c
// On PowerPC AS5610 – phys addr from lspci
volatile uint32_t *regs = mmap(NULL, 256*1024, PROT_READ|PROT_WRITE,
                               MAP_SHARED, fd, 0xa0000000);

// S-Channel
uint32_t v = regs[0x32800 / 4];

// DMA descriptor
uint32_t d = regs[0x31158 / 4];
```

---

## 4. DMA Mapping

### BDE DMA Pool (linux_dma.c)

**Allocation methods:**
1. **Private pool** (default): Contiguous kernel memory via page allocator or `dma_alloc_coherent`
2. **High memory**: Reserved via `mem=xxx`, mapped into kernel
3. **On-demand**: `dmasize=0M` – no pool; alloc on demand (not recommended for non-coherent)

**Module params:**
- `dmasize` – pool size (e.g. 8M default, 4M for Robo)
- `dmaalloc` – 0=chunk, 1=API (single alloc)
- `himem` – use high memory

**Allocation:**
```c
_dma_vbase = dma_alloc_coherent(DMA_DEV(0), size, &dma_handle, GFP_KERNEL);
_cpu_pbase = dma_handle;   // CPU physical
_dma_pbase = pbase;        // Bus address (DMA visible, may differ with IOMMU)
mpool_create(_dma_vbase, size);   // Sub-allocator for SDK
```

### User-Space DMA Access

**ioctl LUBDE_GET_DMA_INFO** (linux-user-bde):
- Returns: `dma_pbase`, `size`, `cpu_pbase`
- `USE_LINUX_BDE_MMAP`: user can mmap via `/dev/linux-kernel-bde` using `vm_pgoff = cpu_pbase >> PAGE_SHIFT`

**mmap (USE_LINUX_BDE_MMAP):**
```c
// User mmaps phys_addr, size
mmap(addr, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, phys_addr >> PAGE_SHIFT);
// Range must be within _cpu_pbase .. _cpu_pbase + _dma_mem_size
```

### KNET Ring Buffers (bcm-knet.c)

When KNET is loaded:
```c
dcb_mem = DMA_ALLOC_COHERENT(dma_dev, dcb_mem_size, &dcb_dma);
// Program ASIC:
DEV_WRITE32(sinfo, CMICM_DMA_DESC0r + 4*chan, dcb_dma);
DEV_WRITE32(sinfo, CMICM_DMA_HALT_ADDRr + 4*chan, halt_addr);
// Start DMA via CMICM_DMA_CTRLr
```

**DCB layout**: Descriptor Control Block ring; each entry = packet buffer pointer + metadata.

**Cumulus**: Does not load KNET; packet I/O uses TUN + BDE (switchd read/write TUN fds).

---

## 5. Summary Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│ PCI Device (BCM56846)                                            │
│  BAR0 (256KB/8MB) → IOREMAP → base_address                      │
│    0x00000–0x31000   Device-specific regs                        │
│    0x31000          CMICm CMC base                               │
│      0x1140         DMA_CTRL (per chan)                          │
│      0x1158         DMA_DESC0 (ring base PA)                     │
│      0x1800         SCHAN_CTRL (0x32800 total)                   │
│      0x31400+       IRQ_STAT/MASK                                │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ DMA Pool (linux_dma.c)                                           │
│  dma_alloc_coherent / _pgalloc → _dma_vbase                      │
│  _cpu_pbase = phys, _dma_pbase = bus addr                        │
│  mpool_create → suballoc for SDK                                 │
│  LUBDE_GET_DMA_INFO → user gets pbase, size                      │
│  mmap(/dev/linux-kernel-bde, pgoff=phys>>12) → user access       │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│ KNET (if loaded)                                                 │
│  DMA_ALLOC_COHERENT for DCB ring                                 │
│  CMICM_DMA_DESC0r = dcb_dma                                      │
│  ASIC DMAs packets to/from ring                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 6. Source File References

| Component | File |
|-----------|------|
| PCI probe, BAR map | `linux-kernel-bde.c` _pci_probe, ~2469 |
| Read/Write | `linux-kernel-bde.c` _read, _write ~4070 |
| DMA init | `linux_dma.c` _dma_init, _alloc_mpool |
| DMA ioctl | `linux-user-bde.c` LUBDE_GET_DMA_INFO |
| KNET DCB | `bcm-knet.c` bkn_alloc_dcbs, CMICM_* |
| rc.soc | `cumulus/extracted/etc/bcm.d/rc.soc` |
| Init sequence | `docs/reverse-engineering/initialization-sequence.md` |
| S-Chan / DMA regs | `docs/reverse-engineering/SCHAN_AND_RING_BUFFERS.md` |

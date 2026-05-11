# BDE Complete — Full ioctl Table, DMA, IRQ

Final pass on the BDE drivers — covered the remaining items.

## Complete LUBDE ioctl table (all 20)

| ioctl | Name | Action |
|---|---|---|
| `0x20004c00` | `LUBDE_VERSION` | returns 0 (BDE version) |
| `0x20004c01` | `LUBDE_GET_NUM_DEVICES` | count switch chips |
| `0x20004c02` | `LUBDE_GET_DEVICE` | id, rev, BAR0 phys addr lo/hi |
| `0x20004c03` | `LUBDE_PCI_CONFIG_PUT` | PCI config-space write |
| `0x20004c04` | `LUBDE_PCI_CONFIG_GET` | PCI config-space read |
| `0x20004c05` | `LUBDE_GET_DMA_INFO` | DMA pool phys addr + size |
| `0x20004c06` | `LUBDE_ENABLE_INTERRUPTS` | connect ISR (Ethernet ISR or device-specific) |
| `0x20004c07` | `LUBDE_DISABLE_INTERRUPTS` | disconnect ISR |
| `0x20004c08` | `LUBDE_USLEEP` | `sal_usleep(us)` (millisecond-class sleep) |
| `0x20004c09` | `LUBDE_WAIT_FOR_INTERRUPT` | block on `_ether_interrupt_wq` wait queue |
| `0x20004c0a` | `LUBDE_SEM_OP` | sub-cmd 1 = create, 2 = destroy semaphore |
| `0x20004c0b` | `LUBDE_UDELAY` | `sal_udelay(us)` (busy-wait microsecond) |
| `0x20004c0c` | `LUBDE_GET_DEVICE_TYPE` | return `dev_type` flag word |
| `0x20004c0d` | `LUBDE_SPI_READ` | SPI bus read (for non-PCI chips) |
| `0x20004c0e` | `LUBDE_SPI_WRITE` | SPI bus write |
| `0x20004c13` | `LUBDE_READ_REG` | call `user_bde->read(dev, addr)` — BAR0 32-bit read |
| `0x20004c14` | `LUBDE_WRITE_REG` | call `user_bde->write(dev, addr, data)` — BAR0 32-bit write |
| `0x20004c15` | `LUBDE_GET_PCI_BUS_FEATURES` | bus capability bits |
| `0x20004c16` | `LUBDE_IRQ_MASK_SET` | `lkbde_irq_mask_set(dev, addr, mask, 0)` |
| `0x20004c1a` | `LUBDE_GET_DEVICE_RESOURCE` | full resource (BAR0/BAR1/IRQ) |

Cases `0x20004c0f..0x20004c12` and `0x20004c17..0x20004c19` aren't present in this build — likely reserved for future extensions or specific platforms.

## DMA management

### `_alloc_dma_blocks` — incremental block allocator

```c
int _alloc_dma_blocks(dma_segment_t *dseg, int blks) {
    if (dseg->blk_cnt + blks > dseg->blk_cnt_max) {
        gprintk("No more DMA blocks\n");
        return -1;
    }
    int start = dseg->blk_cnt;
    dseg->blk_cnt += blks;
    
    for (int i = start; i < dseg->blk_cnt; i++) {
        ulong addr = __get_free_pages(GFP_KERNEL|GFP_DMA /*=0x24*/,
                                       dseg->blk_order);
        if (!addr) { gprintk("DMA allocation failed\n"); return -1; }
        dseg->blk_ptr[i] = addr;
    }
    return 0;
}
```

`0x24 = GFP_DMA | GFP_KERNEL` — legacy DMA mask (suitable for 32-bit DMA).
EdgeNOS should use the same allocator flags for compatibility.

### `_dma_segment_alloc` — full segment allocator

```c
dma_segment_t * _dma_segment_alloc(size_t size, size_t blk_size) {
    // Allocate dma_segment_t struct (0x2c = 44 bytes) from kmem_cache
    dseg = kmem_cache_alloc(...);
    memset(dseg, 0, 0x2c);
    
    // Round blk_size up to 4 KB
    dseg->blk_size = (blk_size + 0xfff) & ~0xfff;
    
    if (dseg->blk_size <= 0x1000) {
        // <= 4 KB: each block is one page
        si_meminfo(&info);
        dseg->blk_cnt_max = (info.freeram * PAGE_SIZE) / dseg->blk_size;
    } else {
        // > 4 KB: compute blk_order (power-of-2 page count)
        int order = 1;
        while ((0x1000 << order) < dseg->blk_size) order++;
        dseg->blk_order = order;
        ...
    }
    
    // Allocate blk_ptr array (uint32 per block)
    dseg->blk_ptr = kmalloc(dseg->blk_cnt_max * 4, GFP_KERNEL);
    
    // Initial allocation: req_size / blk_size blocks
    _alloc_dma_blocks(dseg, dseg->req_size / dseg->blk_size);
    
    // If not enough contiguous, keep allocating in 8-block chunks
    do {
        _find_largest_segment(dseg);
        if (dseg->seg_size >= dseg->req_size) break;
    } while (_alloc_dma_blocks(dseg, 8) == 0);
    
    return dseg;
}
```

Allocates a `dma_segment_t` (44 bytes), then a `blk_ptr[]` array, then
fills it with `__get_free_pages` results. Calls `_find_largest_segment`
to identify the largest contiguous run — that's the actual DMA buffer
returned to switchd.

`dma_segment_t` structure (inferred):
```c
struct dma_segment_t {
    int req_size;        // user-requested size
    int blk_size;        // page-aligned block size
    int blk_order;       // get_free_pages order (0 = 1 page, 1 = 2 pages, ...)
    int blk_cnt;         // current block count
    int blk_cnt_max;     // max allowed blocks
    ulong *blk_ptr;      // array of physical block addresses
    int seg_size;        // largest contiguous segment size
    // ... possibly more fields, total = 0x2c bytes
};
```

## IRQ management

### `lkbde_irq_mask_set` — set IRQ enable mask

```c
int lkbde_irq_mask_set(int d, uint32_t addr, uint32_t mask, uint32_t fmask) {
    int dev = d & 0x7fff;     // strip bit 15 = isr2 flag
    if (dev < 0 || dev >= _ndevices) return -1;
    
    spin_lock_irqsave(&_devices[dev].lock);
    
    if (d & 0x8000) {
        // ISR2 mode — secondary handler with fmask
        _devices[dev].fmask = fmask;
        _devices[dev].imask2 = fmask & mask;
    } else {
        // Standard ISR — primary mask, exclude fmask bits
        _devices[dev].imask = mask & ~_devices[dev].fmask;
    }
    
    // Write combined mask to hardware register
    _write(dev, addr, _devices[dev].imask2 | _devices[dev].imask);
    
    spin_unlock_irqrestore(&_devices[dev].lock);
    return 0;
}
```

Bit 15 of `d` (`0x8000`) selects between:
* **Standard ISR**: maintains `imask`, excludes any bits set in `fmask`
* **ISR2**: maintains `fmask` (the secondary "fast" handler mask), `imask2` = `fmask & mask`

The hardware register is written with `imask | imask2` (combined enables).

This implements **dual-handler interrupts**: one for fast/slow paths with
different mask ownership. EdgeNOS's IRQ handling needs this same model
if it wants to support `bcm_rx_register` (the BCM API for packet I/O).

### `lkbde_irq_imask_get` — read stored IRQ mask

```c
int lkbde_irq_imask_get(int d, uint32_t *mask) {
    int dev = d & 0x7fff;
    if (dev < 0 || dev >= _ndevices || mask == NULL) return -1;
    
    *mask = 0;
    if (_devices[dev].fmask == 0) {
        return 0;  // no isr2 active
    }
    *mask = _devices[dev].imask;
    return 0;
}
```

Returns 0 if no ISR2 is active (no fast handler) or the stored `imask` if
one is active. The `fmask != 0` check is the "isr2 is in use" signal.

## kernel-bde `_init` (the chardev + driver registration)

```c
int _init(void) {
    // Disable MSI (not supported in 3.2 kernel)
    use_msi = 0;
    _device_driver.name = "linux-kernel-bde";
    
    // Register PCI driver - probes via _pci_probe()
    __pci_register_driver(&_device_driver, &__this_module, "linux_kernel_bde");
    
    // Setup PCIe-to-PCI bridges
    p2p_bridge();
    
    // Parse "eb_bus=BA=...,IRQ=...,RD16=...,WR16=..." for external bus devs
    if (eb_bus) {
        for each comma-separated entry:
            _parse_eb_args(...);
            _eb_device_create(...);
    }
    
    // Parse "dmasize=N" for DMA pool size
    if (dmasize) { ... }
    
    // Register chardev /dev/linux-kernel-bde (in __register_chrdev path)
}
```

Module parameters (all set via `insmod linux-kernel-bde.ko foo=bar`):
* `usemsi` — request MSI mode (forced to 0 — kernel 3.2 doesn't have MSI for BCM)
* `eb_bus` — comma-separated external-bus dev specs
* `dmasize` — DMA pool size (e.g., "8m" = 8 MB)
* `forceirq` — force a specific IRQ number on the device
* `forceirqubm` — bitmask: which devices get the forced IRQ
* `nodevices` — skip device probe (testing)
* `debug` — verbosity 0-9

## IRQ flow end-to-end

```
HARDWARE
  CMICm raises IRQ on PCI
    ↓
KERNEL (linux-kernel-bde.ko)
  _ether_interrupt(irq, dev_id)  // top-half ISR
    - read CMIC interrupt status (via _read)
    - mask offending IRQ bits in hardware (so they don't re-fire)
    - atomic_inc(&_ether_interrupt_has_taken_place)
    - wake_up(&_ether_interrupt_wq)
    ↓
USERSPACE (switchd, blocked in LUBDE_WAIT_FOR_INTERRUPT)
  user_bde->wait_for_interrupt() → ioctl(0x20004c09)
    - kernel: wait_event_interruptible(_ether_interrupt_wq, _has_taken_place != 0)
    - returns to user when ISR fires
    ↓
  switchd handles the interrupt:
    - reads CMIC RX descriptor ring
    - delivers packets to TUN fds for swp* interfaces
    - re-arms the IRQ via LUBDE_IRQ_MASK_SET (0x20004c16)
```

## Summary of what's complete

| Item | Status |
|---|---|
| Bedrock MMIO `_read`/`_write` | ✅ decoded |
| iProc/PAXB `_iproc_offset` translation | ✅ decoded |
| All 20 LUBDE ioctls | ✅ documented |
| DMA buffer allocator (`_alloc_dma_blocks`, `_dma_segment_alloc`) | ✅ decoded |
| `dma_segment_t` struct layout | ✅ inferred |
| IRQ mask set/get + dual-handler model | ✅ decoded |
| Module init + PCI driver register | ✅ decoded |
| Module parameters (eb_bus, dmasize, forceirq, etc.) | ✅ documented |
| PCI device-ID matching | ✅ list extracted |
| BCM4704 north-bridge quirk | ✅ found |
| Device-type flag bitmask | ✅ decoded |

## EdgeNOS equivalence (full BDE stack)

| Cumulus BDE component | EdgeNOS OpenMDK equivalent |
|---|---|
| `_read` / `_write` | `cdk_xgs_mmio_read32` / `cdk_xgs_mmio_write32` |
| `_iproc_offset` / `_iproc_read` / `_iproc_write` | `iproc_paxb_*` (our custom BDE fix) |
| `_alloc_dma_blocks` | `cdk_xgs_dma_alloc` |
| `lkbde_irq_mask_set` | `cdk_xgs_intr_mask_set` |
| LUBDE ioctl handler | `cdk_xgs_bde_ioctl` |
| `_pci_probe` | `cdk_xgs_pci_probe` |
| `_init` | `cdk_xgs_bde_init` |

All major pieces of OpenMDK have direct equivalents to the BCM SDK's
BDE primitives.

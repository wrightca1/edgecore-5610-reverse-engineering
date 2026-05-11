# BDE Kernel Drivers — Fully Decoded

Both `linux-kernel-bde.ko` and `linux-user-bde.ko` ship UNSTRIPPED with
debug_info. Decompilation is essentially as-good-as-source.

## Module identification

| Module | Size | Author | Description |
|---|---|---|---|
| `linux-kernel-bde.ko` | 504 KB | Broadcom Corporation | "Kernel BDE" |
| `linux-user-bde.ko`   | 428 KB | Broadcom Corporation | "User BDE Helper Module" (depends on kernel-bde) |
| `linux-bde-i2c.ko`    | 186 KB | Cumulus Networks, LLC | "I2C bus driver for Broadcom BCM56845" |
| `linux-bde-tmon.ko`   | 153 KB | JR Rivers @ Cumulus | "Thermal monitoring driver" |

Both BCM-provided modules are signed by Broadcom Corporation. The Cumulus
modules wrap upstream Linux drivers (i2c/thermal frameworks).

## kernel-bde: 168 functions, 128 decompiled

### MMIO read primitive — `_read`

```c
uint32_t _read(int d, uint32_t addr) {
    if (d < 0 || d >= _ndevices) return -1;
    if ((_devices[d].dev_type & 0x1008d) == 0) return -1;
    
    if ((_devices[d].dev_type & 0x1000) == 0) {
        // Normal 32-bit MMIO read at BAR0 + addr
        return *(uint32_t *)((addr & ~3) + _devices[d].bde_dev.base_address);
    } else {
        // 16-bit external-bus read (older chips, PIO with spinlock)
        spin_lock_irqsave(&bus_lock);
        uint16_t v = *(uint16_t *)(((addr & 0xffff) << 1 | addr & 0xffff0000) + base_address);
        spin_unlock_irqrestore(&bus_lock);
        return v | (v << 16);
    }
}
```

### MMIO write primitive — `_write`

```c
int _write(int d, uint32_t addr, uint32_t data) {
    if (d < 0 || d >= _ndevices) return -1;
    if ((_devices[d].dev_type & 0x1008d) == 0) return -1;
    
    if ((_devices[d].dev_type & 0x2000) != 0) {
        // 16-bit external-bus write
        uint sl_addr = (addr & 0xffff) << 1 | (addr & 0xffff0000);
        spin_lock_irqsave(&bus_lock);
        *(uint16_t *)(sl_addr + base_address) = data & 0xffff;
        *(uint16_t *)(sl_addr + base_address) = data >> 16;
        spin_unlock_irqrestore(&bus_lock);
        return 0;
    }
    // Normal Trident+ 32-bit MMIO write
    *(uint32_t *)((addr & ~3) + _devices[d].bde_dev.base_address) = data;
    return 0;
}
```

**This is the bottom of the chain.** Direct 4-byte MMIO write to
PCI BAR0. EdgeNOS's `cdk_xgs_mmio_write32()` is this exactly.

### iProc access — `_iproc_read` / `_iproc_write` / `_iproc_offset`

```c
uint32_t _iproc_offset(uint32_t map_no, uint32_t addr) {
    for (int i = 0; i < 8; i++) {
        if (iproc_map[0].subwin[i].addr_min <= map_no &&
            map_no <= iproc_map[0].subwin[i].addr_max) {
            return iproc_map[0].subwin[i].addr_min - (i * 0x1000);
        }
    }
    return 0;  // not in any window
}

uint32_t _iproc_read(int d, uint32_t addr) {
    uint32_t offset = _iproc_offset(addr, addr);
    if (offset == 0) return -1;
    return *(uint32_t *)((addr - offset & ~3) + _devices[d].bde_dev.base_address1);
}

int _iproc_write(int d, uint32_t addr, uint32_t data) {
    uint32_t offset = _iproc_offset(addr, addr);
    if (offset == 0) return -1;
    *(uint32_t *)((addr - offset & ~3) + _devices[d].bde_dev.base_address1) = data;
    return 0;
}
```

**This is the PAXB Sub-Window mechanism!** 
* 8 sub-windows (0-7) of 4 KB each in BAR1 (`base_address1`)
* Each sub-window has `addr_min` and `addr_max` (configurable)
* Address translation: `target_addr - subwin.addr_min` = offset in BAR1
* This is exactly what `project_subwindow_fix.md` covered

The data structure layout is:
```c
struct iproc_subwin {
    uint32_t addr_min;
    uint32_t addr_max;
    // ... possibly more fields
};
struct iproc_map {
    struct iproc_subwin subwin[8];
};
struct iproc_map *iproc_map[N_DEVICES];
```

### `_pci_probe` — chip detection (1944 bytes)

PCI device IDs the BDE recognizes:

| PCI dev_id | Action | Chip |
|---|---|---|
| `0x9056` | Skip | PLX 9056 bridge |
| `0x9656` | Skip | PLX 9656 bridge |
| `0xb102` | Add as switch | BCM5XXX |
| `0xb103` | Add as switch | (range check 0xb103) |
| `0xb112` | Add as switch | |
| `0xb304` | Add as switch | |
| `0xb314` | Add as switch | |
| `0xb504` | Add as switch | |
| `0x5300` | Add as CPU device | (P2020 PCIe?) |
| (other) | Reject | |

Special quirks:
* **BCM4704** north-bridge fix: ioremap 0x18008000 / write 0x80 to 
  offset +0x18 ("PriorInvTim register"). Applies once at probe time.
* **IRQ forcing** based on bridge chipset (PLX 0x3388:0x22, Intel 0x12d8:0x8150, 
  some specific dev 0x14e4:0x4704 etc.). Forces IRQ to 0x38 or 0x3a if needed.
* **DMA retry to infinite** for switch devices via PCI capability config.

Note: I didn't see `0xb846` (BCM56846 - our chip!) directly. Either:
1. It's matched by a wildcard in the PCI device-id table (not shown in the 
   probe function — that's just the per-device branching)
2. The exact match is later in the function we didn't capture
3. Our chip uses a different device_id

### Module init `_init` (920 bytes)

Module parameters (insmod args):
* `usemsi` — use MSI interrupts (always disabled in this version, "MSI not supported by kernel")
* `eb_bus=BA=%x IRQ=%d RD16=%d WR16=%d` — external bus devices (older PIO chips)
* `dmasize=N` — DMA buffer pool size
* `forceirq=N` — force a specific IRQ number
* `forceirqubm=N` — bitmask for which device gets forced IRQ
* `nodevices=0/1` — skip device probe (testing)
* `debug=N` — debug verbosity

Registers via `__pci_register_driver(&_device_driver, &__this_module, "linux_kernel_bde")`.

### PCI config space — `_pci_conf_read` / `_pci_conf_write`

Standard `pci_bus_read_config_dword` wrappers with device-index lookup.

### IRQ management — `lkbde_irq_imask_get` / `lkbde_irq_mask_set`

Exported symbols for the user-bde module to control interrupts.

## user-bde: 119 functions, 86 decompiled

### `_ioctl` (1660 bytes) — the LUBDE_* command handler

**Complete LUBDE ioctl table** decoded from the switch statement:

| ioctl | Name | Function |
|---|---|---|
| `0x20004c00` | `LUBDE_VERSION` | Return BDE version (= 0) |
| `0x20004c01` | `LUBDE_GET_NUM_DEVICES` | Count switch chips (via `user_bde->num_devices()`) |
| `0x20004c02` | `LUBDE_GET_DEVICE` | Get device info — id, rev, PCI BAR phys addr lo/hi |
| `0x20004c03` | `LUBDE_PCI_CONFIG_PUT` | Write PCI config space |
| `0x20004c04` | `LUBDE_PCI_CONFIG_GET` | Read PCI config space |
| `0x20004c05` | `LUBDE_GET_DMA_INFO` | Get DMA pool physical addr + size |
| `0x20004c06` | `LUBDE_ENABLE_INTERRUPTS` | Connect ISR to device |
| `0x20004c07` | `LUBDE_DISABLE_INTERRUPTS` | Disconnect ISR |
| `0x20004c08` | `LUBDE_USLEEP` | Sleep N microseconds |
| `0x20004c09` | `LUBDE_WAIT_FOR_INTERRUPT` | Block waiting for IRQ |
| `0x20004c0a` | `LUBDE_PHYS_READ32` | Read 32-bit value at phys addr (BAR0 read) |
| `0x20004c0b` | `LUBDE_PHYS_WRITE32` | Write 32-bit value at phys addr (BAR0 write) |
| `0x20004c0c` | (TBD) | one of the iproc_* variants |
| `0x20004c0d` | (TBD) | |
| `0x20004c0e` | (TBD) | |
| `0x20004c13` | (TBD) | |
| `0x20004c14` | (TBD) | |
| `0x20004c15` | (TBD) | |
| `0x20004c16` | (TBD) | |
| `0x20004c1a` | (TBD) | |

There are ~20 LUBDE ioctls total. Each one:
1. Copy `lubde_ioctl_t io` (0x5c bytes) from user
2. Dispatch on cmd
3. Copy `io` back to user

### Helper `_intr_mode_str` (92 bytes)

Returns string for interrupt mode constants:
* 0 = "INTERRUPT_MODE_NORMAL"
* 1 = "INTERRUPT_MODE_TASKLET"
* 2 = etc.

## Device-type bitmask decoded

`_devices[d].dev_type` is a flag word with these bits:

| Bit | Mask | Meaning |
|---|---|---|
| 0 | `0x0001` | PCI device |
| 7 | `0x0080` | (set in `0x1008d`) |
| 8 | `0x0100` | PCI switch device |
| 10 | `0x0400` | CPU device |
| 12 | `0x1000` | 16-bit external-bus read (older chips) |
| 13 | `0x2000` | 16-bit external-bus write |
| 16 | `0x10000` | Combined-set bit (for `0x1008d`) |

`0x1008d` = `0x10000 | 0x80 | 0x0d` = combined "real switch device" flag.

For BCM56846 (Trident+): bits set are 0x100 (PCI switch) and probably
0x80, 0x10000. Not 0x1000/0x2000 (uses 32-bit MMIO).

## DMA management

The kernel-bde manages a DMA buffer pool for packet I/O:
* `_alloc_dma_blocks` (212 bytes) — allocate DMA blocks
* `_dma_segment_alloc` (680 bytes) — allocate a DMA segment
* `_dma_segment_free` (272 bytes) — free
* `lkbde_get_dma_info` — exported to user-bde for the DMA info ioctl

DMA pool sized via `dmasize` insmod param.

## Source locations confirmed

From debug_info / strings:
* `bcm-sdk/systems/bde/linux/kernel/linux-kernel-bde.c`
* `bcm-sdk/systems/bde/linux/user/linux-user-bde.c`

## Complete CMICm-side stack now mapped

```
Userspace (switchd)
  bcm_xxx_set(...)
    → port_validate
    → soc_reg32_get
      → soc_schan_op
        → linux_user_bde_ioctl
          ↓ ioctl(0x20004c0b /*LUBDE_PHYS_WRITE32*/, &io)
            ↓
Kernel-bde syscall:
  _gmodule_unlocked_ioctl(file, cmd, arg)
    → user_bde->ioctl(cmd, arg)
      (in user-bde.ko)
      → switch on cmd
        case LUBDE_PHYS_WRITE32:
          → _write(devnum, addr, data)   ← THE BEDROCK
            *(uint32_t *)(BAR0 + addr) = data
```

EdgeNOS's OpenMDK has the equivalent stack:
```
cdk_xgs_reg_set
  → cdk_xgs_schan_op
    → cdk_xgs_bde_ioctl
      → linux_bde_dev_write
        → mmio_write32
```

We can now do **line-by-line comparison** between Cumulus's BDE and
EdgeNOS's OpenMDK BDE at every layer.

## Files

* `linux-kernel-bde.ko_decompile.c` (95 KB) — 128 decompiled functions
* `linux-kernel-bde.ko_functions.txt` — 168 functions named
* `linux-kernel-bde.ko_symbols.txt` — 972 symbols (debug info!)
* `linux-user-bde.ko_decompile.c` (50 KB) — 86 functions decompiled
* `linux-user-bde.ko_functions.txt` — 119 functions named
* `linux-user-bde.ko_symbols.txt` — 595 symbols

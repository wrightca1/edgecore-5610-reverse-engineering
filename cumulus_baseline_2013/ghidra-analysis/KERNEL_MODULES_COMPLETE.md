# Kernel Modules — Complete Picture

Final pass on the three Cumulus-relevant kernel modules:
`linux-kernel-bde.ko`, `linux-bde-i2c.ko`, `linux-bde-tmon.ko`.
All shipped UNSTRIPPED with debug_info → near-source-quality decomp.

## 1. The IRQ top-half: `_isr` in kernel-bde

96 bytes. Confirms the **dual-handler model**:

```c
irqreturn_t _isr(int irq, void *dev_id) {
    bde_ctrl_t *ctrl = dev_id;
    
    if (ctrl->isr1_func)                       // +0x38
        ctrl->isr1_func(ctrl->isr1_data);      // +0x3c (data arg)
    if (ctrl->isr2_func)                       // +0x40
        ctrl->isr2_func(ctrl->isr2_data);      // +0x44
    return IRQ_HANDLED;
}
```

**Both handlers run on every IRQ.** They each check their own status registers and decide if they have work to do.

Registered at `_pci_probe` time via `request_threaded_irq(IRQ, _isr, ...)`.

Handlers get connected via `LUBDE_ENABLE_INTERRUPTS` (ioctl `0x20004c06`),
which sets `ctrl->isr1_func` (and optionally isr2 if dev #15 bit set).

`bde_ctrl_t` struct (offsets confirmed):
| Offset | Field |
|---|---|
| `+0x38` | `isr1_func` (primary IRQ handler callback) |
| `+0x3c` | `isr1_data` (cookie passed to handler) |
| `+0x40` | `isr2_func` (secondary "fast" handler) |
| `+0x44` | `isr2_data` |

The user-bde side: `LUBDE_WAIT_FOR_INTERRUPT` (ioctl 0x20004c09) blocks on `_ether_interrupt_wq`. The actual `_ether_interrupt` function is probably one of these registered isr1/isr2 callbacks — it increments `_ether_interrupt_has_taken_place` and `wake_up()`s the wait queue.

## 2. `linux-bde-i2c.ko` — BCM ASIC internal I2C controller

92 functions, 53 decompiled. By Cumulus Networks. Description: "I2C bus driver for Broadcom BCM56845".

**This is the I2C controller _inside the BCM ASIC_**, NOT the CPU's I2C controllers. The chip has its own I2C master used for things like SFP+ EEPROM reads, PHY firmware uploads, etc.

### `bde_i2c_send_data` — the I2C byte-write primitive

```c
int bde_i2c_send_data(bde_i2c *d, uint8_t *buf, int len) {
    for (int i = 0; i < len; i++) {
        // Write data byte to TX register (with endian swap if needed)
        uint32_t endian_bit = MMIO(d->addr + 0x174) & 1;
        uint32_t val = buf[i];
        if (endian_bit == 0) val = (uint32_t)buf[i] << 24;  // BE byte-swap
        MMIO(d->addr + 0x124) = val;     // I2C_DATA
        
        // Set "go" bit (clear bit 3) in control register
        uint32_t ctrl = MMIO(d->addr + 0x128) & ~0x08;
        if (endian_bit == 0) ctrl = ctrl << 24 | endian_bit;
        MMIO(d->addr + 0x128) = ctrl;    // I2C_CONTROL
        
        // Wait for completion (via IRQ)
        if (bde_i2c_wait(d) != 0) {
            bde_i2c_reset(d);
            return error;
        }
        
        // Check status (offset 0x12c)
        if (MMIO(d->addr + 0x12c) & 0xff == 0x30)
            bde_i2c_send_stop(d);
    }
    return 0;
}
```

I2C controller register offsets within the BCM ASIC MMIO:

| Offset | Name | Purpose |
|---|---|---|
| `+0x124` | `I2C_TX_DATA` | Byte to transmit |
| `+0x128` | `I2C_CONTROL` | Control bits (bit 3 = "go") |
| `+0x12c` | `I2C_STATUS` | Status (0x30 = need STOP) |
| `+0x148` | `I2C_INTR_MASK` | IRQ mask (bit 0x40000 = I2C done) |
| `+0x174` | `I2C_ENDIAN` | Bit 0 = little-endian access mode |

### `bde_i2c_wait` — wait for I2C done IRQ

```c
int bde_i2c_wait(bde_i2c *d) {
    d->intr = 0;
    // Enable I2C IRQ via ISR2 (bit 15 = 0x8000 = "fast handler" mode)
    lkbde_irq_mask_set(d->n | 0x8000,    // dev | 0x8000 for ISR2
                       0x148,             // I2C_INTR_MASK register offset
                       0x40000,           // I2C done bit
                       0x40000);          // fmask
    
    // Wait on wait_queue with 10-second timeout
    int rc = wait_event_interruptible_timeout(d->wq,
                                               d->intr != 0,
                                               10000);
    return rc;
}
```

**This is the ISR2 "fast handler" use case.** When the I2C controller raises an IRQ:
1. `_isr` fires (kernel)
2. `isr2_func` callback (registered by i2c.ko) runs
3. It checks I2C_STATUS, sets `d->intr = 1`, wakes the wait queue
4. Caller in `bde_i2c_wait` returns

### Other I2C primitives

* `bde_i2c_send_stop` — sends I2C STOP condition (writes some control reg)
* `bde_i2c_reset` — resets the I2C controller (toggle bits in I2C_CONTROL)
* `bde_i2c_functionality` — returns Linux i2c_adapter capability bitmap (I2C, SMBUS_QUICK, etc.)

The module registers a standard Linux i2c_adapter so the chip's internal I2C bus shows up as `/dev/i2c-N` from userspace. EdgeNOS can call `ioctl(I2C_RDWR, ...)` to read SFP+ EEPROMs via this path.

## 3. `linux-bde-tmon.ko` — BCM ASIC die-temperature sensor

68 functions, 50 decompiled. By JR Rivers @ Cumulus. Description: "Thermal monitoring driver for Broadcom networks SOCs".

This exposes the BCM chip's INTERNAL die temperature sensor as a Linux `hwmon` device (`/sys/class/hwmon/hwmon0/temp1_input` — we read 42.5°C earlier).

### `trident_tmon_enable` — enable die temp sensor on Trident class

```c
void trident_tmon_enable(void *base) {
    // Check endian flag
    bool be = (MMIO(base + 0x174) & 0x1010101) != 0;
    
    // Read existing TMON control register at +0x88
    uint32_t val = MMIO(base + 0x88);
    if (be) val = bswap32(val);
    
    // Enable: clear bits in 0x20007 mask, set bit 0 and bit 16 (0x10001)
    val = (val & ~0x20007) | 0x10001;
    
    if (be) val = bswap32(val);
    MMIO(base + 0x88) = val;
}
```

So TMON control register is at MMIO `+0x88`:
* bit 0: enable bit
* bit 16: secondary enable bit
* bits 0-2: mask cleared (some configuration)
* bit 17: cleared
* bits 18+: status

The endian-swap pattern is because BCM chips can be configured for BE or
LE host access. The driver detects which via the bit 0 of reg `+0x174`.

### `tmon_get` / `tmon_show` — sysfs read of temperature

```c
ssize_t tmon_get(device *dev, device_attribute *dattr, char *buf) {
    int idx = get_tmon_idx(dev);
    if (strcmp(dattr->attr.name, "temp1_max") == 0)
        return sprintf(buf, "%lu\n", tmon_info[idx].max);
    if (strcmp(dattr->attr.name, "temp1_max_hyst") == 0)
        return sprintf(buf, "%lu\n", tmon_info[idx].hyst);
    return -EINVAL;
}
```

Returns the *thresholds*; the actual temperature reading is in
`tmon_show` (528 bytes, larger) — reads the temp register, converts the
raw value to milli-celsius, formats.

### `tmon_set` — programmable thresholds

User can write to `temp1_max` / `temp1_max_hyst` sysfs files. Driver
updates the chip's temp comparator (probably for over-temp interrupt).

## Module dependency chain

```
linux-kernel-bde.ko  (Broadcom — PCI/MMIO/DMA/IRQ infrastructure)
   ↑
   ├── linux-user-bde.ko  (Broadcom — userspace chardev /dev/linux-user-bde)
   ├── linux-bde-i2c.ko    (Cumulus — registers Linux i2c_adapter)
   └── linux-bde-tmon.ko   (Cumulus — registers Linux hwmon device)
```

All three depend on `linux-kernel-bde` for:
* Device enumeration (`lkbde_get_dev_*`)
* IRQ multiplexing (`lkbde_irq_mask_set`, both go through `_isr`)
* MMIO access (`_read`/`_write` exported)
* DMA management

## EdgeNOS mapping

| Cumulus kernel module | EdgeNOS equivalent / status |
|---|---|
| `linux-kernel-bde.ko` | Custom BDE in EdgeNOS (mostly done, per project memory) |
| `linux-user-bde.ko`   | Custom user-side BDE chardev |
| `linux-bde-i2c.ko`    | ⚠️ Needs port if we want SFP EEPROM via chip's I2C (otherwise use P2020 I2C) |
| `linux-bde-tmon.ko`   | ⚠️ Needs port for BCM die temp via hwmon |

For EdgeNOS:
* **The dual-handler IRQ model** (`isr1`/`isr2` in bde_ctrl_t at offsets 0x38-0x47) is what enables concurrent fast (I2C/linkscan) + slow (packet RX) handlers on the same IRQ line. EdgeNOS's IRQ glue must match this layout if it wants to load these stock kernel modules.
* **`bde_i2c_wait`** uses ISR2 mode (`dev | 0x8000`) — this is the canonical pattern for "fast handler" use cases.
* **TMON register offset `+0x88`** is the per-chip enable. EdgeNOS can read live BCM die temp directly via MMIO.

## Files

* `linux-bde-i2c.ko_decompile.c` (36 KB)
* `linux-bde-i2c.ko_functions.txt` (92 functions)
* `linux-bde-i2c.ko_strings.txt` (13 KB)
* `linux-bde-i2c.ko_symbols.txt` (9.6 KB)
* `linux-bde-tmon.ko_decompile.c` (29 KB)
* `linux-bde-tmon.ko_functions.txt` (68 functions)
* `linux-bde-tmon.ko_strings.txt` (12 KB)
* `linux-bde-tmon.ko_symbols.txt` (8 KB)

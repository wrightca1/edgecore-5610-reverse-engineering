# open-nos-as5610 Implementation Findings

**Date**: 2026-03-02
**Target**: BCM56846 Trident+ / Edgecore AS5610-52X
**Repo**: https://github.com/wrightca1/open-nos-as5610

This document captures bugs found and fixes applied while building a working open NOS
for the AS5610-52X, cross-validated against the RE data in this repository.

---

## 1. Critical Bug: S-Channel Register Confusion

### Problem

The initial `nos_kernel_bde.c` implementation incorrectly used **DMA channel registers**
for S-Channel (register/table) operations:

```c
// WRONG — these are packet DMA registers, not S-Channel
#define CMICM_DMA_CTRL(ch)   (0x31140 + 4*(ch))
#define CMICM_DMA_DESC0(ch)  (0x31158 + 4*(ch))

// The broken nos_bde_schan_op() wrote to CMICM_DMA_DESC0(0) and polled CMICM_DMA_CTRL(0)
// This caused all S-Channel operations (port enable, table writes) to silently fail.
```

**These are packet I/O DMA registers**, used exclusively for punted/injected packet descriptors.
They have nothing to do with S-Channel register/memory access.

### Fix

S-Channel PIO uses **dedicated SCHAN_MSG registers** at BAR0+0x3300c:

```c
// CORRECT — confirmed from libopennsl.so.1 binary string:
// "S-bus PIO Message Register Set; PCI offset from: 0x3300c to: 0x33060"
#define CMIC_CMC0_SCHAN_CTRL     0x32800u
#define CMIC_CMC0_SCHAN_MSG(n)  (0x3300cu + (n) * 4u)
#define SCHAN_MAX_MSG_WORDS      21

// SCHAN_CTRL bits
#define SCHAN_CTRL_START    (1u << 0)
#define SCHAN_CTRL_DONE     (1u << 1)
#define SCHAN_CTRL_ERR_MASK ((1u << 2) | (1u << 3))
```

### S-Channel PIO Protocol (implemented and validated)

```c
// 1. Write command words
for (i = 0; i < cmd_words; i++)
    iowrite32(cmd[i], bar0 + CMIC_CMC0_SCHAN_MSG(i));

// 2. Write data words (for write ops)
for (i = 0; i < data_words; i++)
    iowrite32(data[i], bar0 + CMIC_CMC0_SCHAN_MSG(cmd_words + i));

// 3. Clear stale state, then trigger
iowrite32(0, bar0 + CMIC_CMC0_SCHAN_CTRL);
iowrite32(SCHAN_CTRL_START, bar0 + CMIC_CMC0_SCHAN_CTRL);

// 4. Poll for DONE
while (time_before(jiffies, timeout)) {
    ctrl = ioread32(bar0 + CMIC_CMC0_SCHAN_CTRL);
    if (ctrl & SCHAN_CTRL_DONE) {
        iowrite32(0, bar0 + CMIC_CMC0_SCHAN_CTRL);
        // read result for read ops
        return 0;
    }
    usleep_range(10, 100);
}
```

### Validation

After implementing the correct protocol:
- `bcm56846_chip_init` runs to completion
- Journal: `[init] bcm56846_chip_init: done (SCHAN_CTRL=0x00000000)`
- 52 TAP interfaces (swp1-swp52) successfully created
- `nos_switchd` active and running on AS5610-52X

---

## 2. soc.c: Missing rc.soc Command Handlers

### Problem

The initial `sdk/src/soc.c` only handled `setreg 0xHEX val` and `getreg 0xHEX`.
Cumulus `rc.soc` uses several commands that were silently skipped:

| Command | Status in original code |
|---------|------------------------|
| `init all` | Silently ignored |
| `rcload /path/to/script` | Silently ignored |
| `setreg regname val` | Silently ignored (only hex addresses worked) |
| `attach *` | Silently ignored |
| `0:` (unit prefix) | Silently ignored |
| `m reg FIELD=val` | Silently ignored |

### Fix

`soc.c` was rewritten to handle:
- `init all` → calls `bcm56846_chip_init(0)`
- `rcload PATH` → recursive script execution (depth-limited)
- `setreg REGNAME val` → named register lookup table
- Unit prefix `0:` → stripped and line re-processed
- All other commands → warning logged but execution continues

Named register table for BCM56846 (addresses derived from Cumulus/Ghidra RE):

| Register Name | Address |
|---------------|---------|
| `rdbgc0_select` | 0x06500380 |
| `rdbgc3_select` | 0x065003a0 |
| `rdbgc4_select` | 0x065003a4 |
| `rdbgc5_select` | 0x065003a8 |
| `rdbgc6_select` | 0x065003ac |
| `tdbgc6_select` | 0x04b00200 |
| `ifp_meter_parity_control` | 0x0a400000 |
| `xmac_tx_ctrl` | 0x40a0082c |
| `rtag7_hash_seed_a` | 0x05e00180 |
| `rtag7_hash_ecmp` | 0x05e00200 |
| `cmic_misc_control` | 0x0000001c |

---

## 3. init.c: Chip Initialization Sequence

### bcm56846_chip_init()

Minimal chip init for BCM56846 after warm reboot (ONIE install + reboot):

```c
// Step 1: Set SBUS timeout
bde_write_reg(0x0000010cu, 0x000007d0u);  // CMIC_SBUS_TIMEOUT_REG = 2000 cycles

// Step 2: Clear stale SCHAN state
bde_write_reg(CMIC_CMC0_SCHAN_CTRL, 0u);
usleep(1000);

// Step 3: Verify CMICm accessible
bde_read_reg(CMIC_CMC0_SCHAN_CTRL, &ctrl);
// Log SCHAN_CTRL value for diagnostics
```

**Note**: After ONIE install + warm reboot, BCM56846 retains CMICm ring maps from the
previous Cumulus SDK run. Only DMA descriptors and CPU port need re-initialization.
SCHAN_CTRL=0x00000000 after init is correct (register cleared at end of sequence).

---

## 4. IFF_TUN → IFF_TAP Fix

Initial `switchd/src/main.c` created TUN interfaces instead of TAP.
BCM56846 ASIC punts Ethernet frames (Layer 2), which requires TAP interfaces.

```c
// WRONG
ifr.ifr_flags = IFF_TUN;

// CORRECT
ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
```

After fix: 52 TAP interfaces (swp1-swp52) with LOWER_UP confirmed on switch.

---

## 5. Platform Management (platform-mgrd)

Python daemon `platform/platform-mgrd/platform_mgrd.py` manages:
- CPLD sysfs at `/sys/devices/platform/ff705000.localbus/ea000000.cpld`
- Fan PWM via `pwm1` attribute (valid values: 40, 70, 100)
- Watchdog keepalive via `watch_dog_keep_alive`
- PSU status via `psu_pwr{1,2}_present` and `psu_pwr{1,2}_all_ok`
- Temperature via hwmon `temp*_input` (millidegrees Celsius)
- LED status via `led_diag`

Fan speed policy:
- `< 35°C` → 40%
- `35–55°C` → 70%
- `> 55°C` → 100% (warning logged)

---

## 6. Known Remaining Issues

| Issue | Status |
|-------|--------|
| ASIC RX = 0 packets (cold-boot ring maps) | Under investigation |
| I2C temp sensors (MAX6581, NE1617A) | Not accessible |
| System time stuck at 1970 | NTP not configured |
| S-Channel timeout on fresh cold boot | CMIC_SBUS_RING_MAP values needed |

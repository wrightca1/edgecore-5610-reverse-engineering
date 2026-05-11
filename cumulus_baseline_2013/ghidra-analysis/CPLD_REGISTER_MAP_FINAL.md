# CPLD Register Map — Final Extracted from Ghidra

Decoded from `accton_as5610_52x_cpld.ko` via decompilation + .data table
extraction. EdgeNOS can use this directly to write a CPLD driver.

## Memory map

| Phys addr | Linux mapping | Size |
|---|---|---|
| `0xea000000` | `of_iomap(np, 0)` | (small, ≤ 32 bytes per CPLD wrap rule) |

## Per-byte register map

| Offset | Register | Bits | Purpose | R/W |
|---|---|---|---|---|
| **0x01** | PSU2 power status | bit 0 = present, bit 1 = dc_ok | R |
| **0x02** | PSU1 power status | bit 0 = present, bit 1 = dc_ok | R |
| **0x03** | System status | bit 0 = fan_present, bit 1 = fan_ok, bit 2 = fan_present? (inverted), bit 4 = fan_air_flow (1=F→B), bit 5 = dc_power_ok | R |
| **0x0D** | PWM1 duty | 5 bits (val = user_pwm >> 3, range 0-31) | R/W |
| **0x0E** | Watchdog control | bit 0 = enable, bit 1 = keep_alive (write-only triggers) | R/W |
| **0x13** | **System LEDs** | bits 0-1: led_psu1, bits 2-3: led_psu2, bits 4-5: led_diag, bits 6-7: more | R/W |

(Other offsets exist but only the above are used by the driver's sysfs handlers.)

## LED encoding (CPLD register 0x13)

**The 4 system LEDs share a single byte at CPLD offset 0x13.** Each LED
gets 2 bits. From the `cpld_leds[]` table layout extracted:

| LED name | mask (in reg 0x13) | green value | yellow value | off value |
|---|---|---|---|---|
| `led_psu1` | `0x03` (bits 0-1) | `0x02` | `0x01` (inferred) | `0x03` |
| `led_psu2` | `0x0C` (bits 2-3) | `0x08` | `0x04` (inferred) | `0x0C` |
| `led_diag` | `0x30` (bits 4-5) | (TBD) | `0x20` | `0x10` |
| `led_fan` / `led_locator` | `0xC0` (bits 6-7) | (TBD) | (TBD) | (TBD) |

Note: "off" values match the mask pattern (e.g. led_psu1 off = 0x03 = mask).
This is a typical Cumulus pattern where both bits high = LED off, single bit
set = a specific color. EdgeNOS needs to verify with live read/writes.

## Live readings (matches our chassis state)

Captured earlier from sysfs read of these attrs:

| Attr | Value | Decoded byte at CPLD[0x13] |
|---|---|---|
| `led_psu1` | `green` | bits 0-1 = `0x02` |
| `led_psu2` | `yellow` | bits 2-3 = `0x04` |
| `led_diag` | `yellow` | bits 4-5 = `0x20` |
| `led_fan` | `green` | bits 6-7 = ? |

So CPLD[0x13] currently reads as approximately `0x26 + (fan_value)` =
`0x46` or `0x66` depending on the fan/locator encoding.

## Watchdog details

CPLD offset 0x0E:
* bit 0 = watch_dog_enable (R/W)
* bit 1 = watch_dog_keep_alive (write-triggered)

Timeout range = 8..520 seconds (from decomp: `if (val - 8 < 0x1F9)`).
There's a separate timeout-value register but the driver wraps it as a
single sysfs attribute — likely the timeout high/low bytes are at adjacent
CPLD offsets (0x10/0x11 perhaps; not directly visible in decomp).

## PWM stamping algorithm

```c
// User writes 0-255 to /sys/.../pwm1
sscanf(buf, "%d", &pwm);          // parse
if (pwm > 0xFF) pwm = 0xFF;        // clamp top
pwm = pwm & ((-pwm) >> 31);        // clamp bottom to 0
accton_as5610_52x_pwm1 = pwm;      // cache full user value
CPLD[0x0D] = (uint8_t)(pwm >> 3);  // write 5-bit value to CPLD
```

User value 0-7 → CPLD 0. Value 8-15 → CPLD 1. ... Value 248-255 → CPLD 31.
**This means PWM is granular only every 8 user units.** Practical effective
values: 0, 8, 16, 24, ..., 248.

## EdgeNOS port recipe

```c
#define CPLD_BASE     0xea000000
#define CPLD_SIZE     0x20         // wraps at 32 bytes

// Register offsets
#define CPLD_PSU2     0x01
#define CPLD_PSU1     0x02
#define CPLD_SYSTEM   0x03
#define CPLD_PWM1     0x0D
#define CPLD_WDT      0x0E
#define CPLD_LEDS     0x13

// System status bits (CPLD[0x03])
#define SYS_FAN_PRESENT  0x01
#define SYS_FAN_OK       0x02
#define SYS_AIRFLOW_FB   0x10   // 1 = front-to-back
#define SYS_DC_POWER_OK  0x20

// PSU status bits (CPLD[0x01] for PSU2, CPLD[0x02] for PSU1)
#define PSU_PRESENT      0x01
#define PSU_DC_OK        0x02
#define PSU_ALL_OK(b)    (((b) & (PSU_PRESENT|PSU_DC_OK)) == (PSU_PRESENT|PSU_DC_OK))

// LED mask and encoding
#define LED_PSU1_MASK  0x03
#define LED_PSU2_MASK  0x0C
#define LED_DIAG_MASK  0x30
#define LED_FAN_MASK   0xC0

static void cpld_pwm_set(uint8_t *cpld, uint8_t user_value) {
    cpld[CPLD_PWM1] = user_value >> 3;   // 5-bit
}

static void cpld_led_set(uint8_t *cpld, uint8_t mask, uint8_t color_value) {
    uint8_t v = cpld[CPLD_LEDS];
    cpld[CPLD_LEDS] = (v & ~mask) | color_value;
}

static void cpld_wdt_enable(uint8_t *cpld, bool enable) {
    uint8_t v = cpld[CPLD_WDT];
    cpld[CPLD_WDT] = enable ? (v | 0x01) : (v & ~0x01);
}

static void cpld_wdt_kick(uint8_t *cpld) {
    cpld[CPLD_WDT] |= 0x02;  // pulses bit 1
}
```

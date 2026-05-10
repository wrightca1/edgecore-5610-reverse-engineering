# CPLD register/attr layout — extracted from `accton_as5610_52x_cpld.ko` strings

```
filename:    /lib/modules/3.2.60-1+deb7u1+cl2.5/extra/accton_as5610_52x_cpld.ko (157KB)
version:     1.0
license:     GPL
author:      Puneet Shenoy <puneet@cumulusnetworks.com>
srcversion:  34773A0D6D6F29FE7C7CD18
```

## Sysfs attrs exposed (from strings)

| Attr name | Doc | Type |
|---|---|---|
| `board_revision` | Read-only `model.HW_rev:cpld_version` | R/O |
| `led_diag` | System diag LED color | R/W |
| `led_fan` | Fan tray status LED | R/W |
| `led_locator` | Identify LED | R/W |
| `led_psu1`, `led_psu2` | Per-PSU status LED | R/W |
| `psu_pwr[12]_present` | PSU slot presence | R/O |
| `psu_pwr[12]_dc_ok` | PSU DC output good | R/O |
| `psu_pwr[12]_all_ok` | Computed: `present && dc_ok` | R/O |
| `system_fan_present` | Fan tray present | R/O |
| `system_fan_ok` | Fan tray healthy | R/O |
| `system_fan_air_flow` | "front-to-back" / "back-to-front" | R/O |
| `system_dc_power_ok` | System power good | R/O |
| `system_all_ok` | Computed: `system_fan_present && system_fan_ok && system_dc_power_ok` | R/O |
| `pwm1` | **Fan PWM duty cycle, range 0-248** (note: NOT 0-255) | R/W |
| `pwm1_enable` | Read returns 1 always; write is no-op | R/W |
| `watch_dog_enable` | Enable hardware watchdog | R/W |
| `watch_dog_keep_alive` | Write to kick the dog | W/O |
| `watch_dog_timeout` | Seconds until NMI if not kicked | R/W |

## RE notes

* PWM max is **248**, not 255. (Important for EdgeNOS reimplementation —
  ratio is 64/248 ≈ 26% at idle.)
* `pwm1_enable` is always 1 — the CPLD has no way to "disable" PWM
  control once driven; the read-side is just a status hint.
* `psu_pwr[12]_all_ok` and `system_all_ok` are computed in the driver,
  not stored as separate CPLD registers. EdgeNOS just needs to read the
  base bits and compute the same logical AND.
* The CPLD is at physical address `0xea000000` on the PowerPC local-bus
  controller `ff705000.localbus`. CPLD register space wraps at 32 bytes
  (`feedback_cpld_addr_wrap.md`).

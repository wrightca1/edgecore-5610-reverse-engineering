# AS4610-54T — Board Topology & I²C Tree

Decoded from `OpenNetworkLinux/.../arm-accton-as4610/arm-accton-as4610.dts` and
the ONLP `sfpi.c` / `psui.c` / `thermali.c` / `fani.c` drivers. This is the
4610 equivalent of the 5610's `I2C_BUS_TOPOLOGY_AND_SFP_CONTROL.md` — but note
the 4610's I²C tree is **dramatically simpler** (one mux, one level) versus the
5610's 6-layer mux jungle.

---

## On-die iProc peripherals (no external chips)

| DT node | Function |
|---|---|
| `gmac0` (SGMII) | Management Ethernet MAC → mgmt RJ-45 |
| `uart1`, `uart2` | Serial consoles (`ttyS0` @ 115200 8N1) |
| `ehci0` + `usbphy0` (host) | USB → boot/NOS disk (`/dev/sda`) |
| `iproc_cmicd` | **Switch core CMIC** (data-plane control) |
| `iproc_wdt` | Watchdog |
| `dmac0` | iProc DMA controller |
| `hwrng` | Hardware RNG |
| `gpio_cca` | iProc GPIO (CCA block) |

## I²C bus 0 (`i2c0`, 400 kHz)

| Device | Compatible | Addr |
|---|---|---|
| **System CPLD** | `accton,as4610_54_cpld` | **0x30** |

The CPLD is the board's glue logic — fan control, PSU status, port present/LED,
reset lines. Version readable at `/sys/bus/i2c/devices/0-0030/version`. Register
map is implemented in `modules/accton_as4610_cpld.c` (mirror it into a
`CPLD_REGISTER_MAP.md` once dumped from the live unit).

## I²C bus 1 (`i2c1`) → PCA9548 8-channel mux @ 0x70

`deselect-on-exit` set. Channels:

| Ch | Device(s) | Addr | Maps to |
|---|---|---|---|
| 0 | `optoe2` (SFP EEPROM) | 0x50 | **port 49** (SFP+ 1) |
| 1 | `optoe2` | 0x50 | **port 50** (SFP+ 2) |
| 2 | `optoe2` | 0x50 | **port 51** (SFP+ 3) |
| 3 | `optoe2` | 0x50 | **port 52** (SFP+ 4) |
| 4 | `optoe1` (QSFP EEPROM) | 0x50 | **port 53** (QSFP+ STK1) |
| 5 | `optoe1` | 0x50 | **port 54** (QSFP+ STK2) |
| 6 | PSU1 EEPROM / PMBus | 0x50 / 0x58 | PSU1 (`accton,as4610_psu1`, YM-1921) |
| 6 | PSU2 EEPROM / PMBus | 0x51 / 0x59 | PSU2 (`accton,as4610_psu2`, YM-1921) |
| 7 | Temp sensor `lm77` | 0x48 | Board thermal |
| 7 | RTC (M41T11 as `ds1307`) | 0x68 | Real-time clock |
| 7 | Board EEPROM `at24c04` | 0x50 | ONIE TLV / board id |

> `optoe1` = QSFP-style paged EEPROM; `optoe2` = SFP-style. These are upstream
> Linux optical-module EEPROM drivers — present/managed via sysfs, no custom
> SFP access code needed beyond CPLD present/LOS bits.

---

## Port numbering & CPLD mapping (from `sfpi.c`)

For the **AS4610-54** (`PLATFORM_ID_..._AS4610_54_R0`):

| Quantity | Formula | Notes |
|---|---|---|
| Optics port range | ONLP ports **48–53** (`start=48, end=54` exclusive) | = physical 49–54 |
| Front-port → I²C bus index | `port - 46` | |
| Front-port → CPLD port index | `port - 47` | feeds `MODULE_PRESENT_FORMAT` etc. |
| SFP EEPROM sysfs | `/sys/bus/i2c/devices/%d-0050/eeprom` | per mux channel |

(The 48× 1G copper ports 1–48 are PHY/MAC ports inside Helix4; they are not
optical and have no per-port EEPROM — only the 6 SFP/QSFP cages do.)

---

## Power / thermal / fan

| Subsystem | Driver | Notes |
|---|---|---|
| PSU | `accton_as4610_psu.c` + `psui.c` | 2× hot-swap, EEPROM + YM-1921 PMBus telemetry |
| Fan | `accton_as4610_fan.c` + `fani.c` | duty-cycle via `/sys/devices/platform/as4610_fan/fan_duty_cycle_percentage`; ONLP `platform_manage_fans` ramps on thermal |
| Thermal | `thermali.c` (LM77) | drives the fan curve |
| LEDs | `accton_as4610_leds.c` + `ledi.c` | system + port LEDs |

---

## Comparison to 5610 board complexity

| | 5610 | 4610 |
|---|---|---|
| I²C mux levels | up to 6 (PCA9546 + PCA9548 cascades) | **1** (single PCA9548) |
| GPIO expanders | 6× PCA9506 + 4× PCA9538 | none (CPLD + iProc GPIO) |
| Retimers | 8× TI DS100DF410 (32 channels) | **none** |
| External PHYs | BCM84740 ×N + mgmt BCM54610 | integrated copper PHYs |
| CPLD access | memory-mapped (eLBC @ 0xEA000000) | **I²C @ 0x30** |
| Total ICs | ~44 | far fewer |

The takeaway: almost everything that made 5610 board bring-up painful (retimer
unmute, mux tree, PAXB) is **absent or trivial** here.

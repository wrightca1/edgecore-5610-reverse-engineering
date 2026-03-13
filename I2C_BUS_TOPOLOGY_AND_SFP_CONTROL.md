# AS5610-52X I2C Bus Topology and SFP Control

## I2C Controllers

The P2020 SoC has two MPC I2C controllers:
- **i2c-0** (`/sys/devices/soc.0/ff703000.i2c`): Management/platform bus
- **i2c-1** (`/sys/devices/soc.0/ff703100.i2c`): SFP/QSFP data and control buses

> For physical chip inventory, markings, and board locations see
> [AS5610_52X_BOARD_COMPONENT_MAP.md](AS5610_52X_BOARD_COMPONENT_MAP.md)

## Kernel Module Load Order

From Cumulus `/etc/modules` (loaded in this order at boot):

| Module | Function |
|--------|----------|
| `accton_as5610_52x_cpld` | CPLD at `0xEA000000` via eLBC CS1 |
| `at24` | SFP+ EEPROM driver (at24c04, depends on `eeprom_class`) |
| `sff_8436_eeprom` | QSFP+ EEPROM driver (depends on `eeprom_class`) |
| `gpio-pca953x` | PCA9538 GPIO expander driver (QSFP control) |
| `max6697` | MAX6697/MAX6581 temperature sensor driver |
| `adm1021` | NE1617A/MAX1617 temperature sensor driver |
| `ds100df410` | DS100DF410 retimer driver (depends on `retimer_class`) |

Implicit dependencies loaded automatically:
- `i2c-core` → `i2c-mux` → `pca954x` (PCA9546/PCA9548 mux driver)
- `eeprom_class` (base class for at24 and sff_8436_eeprom)
- `retimer_class` (base class for ds100df410, registered as `subsys_initcall`)

## Bus Number Mapping

Total: 70 I2C buses (i2c-0 through i2c-69).

### Management Bus (i2c-0)

```
i2c-0 (ff703000.i2c)
└── PCA9548 @ 0x70 (8-channel mux)
    ├── ch0 → i2c-2:  Epson RTC8564 @ 0x51 (real-time clock)
    ├── ch1 → i2c-3:  PSU1 devices
    │                  ├── EEPROM @ 0x3A (PSU1 FRU data)
    │                  ├── PMBus  @ 0x3E (PSU1 power monitoring)
    │                  └── PMBus  @ 0x78 (PSU1 page register)
    ├── ch2 → i2c-4:  PSU2 devices
    │                  ├── Unknown @ 0x0C
    │                  ├── EEPROM  @ 0x39 (PSU2 FRU data)
    │                  ├── PMBus   @ 0x3D (PSU2 power monitoring)
    │                  └── PMBus   @ 0x78 (PSU2 page register)
    ├── ch3 → i2c-5:  (empty)
    ├── ch4 → i2c-6:  SMSC USB2513i USB hub @ 0x2C
    ├── ch5 → i2c-7:  VT1165M voltage monitor @ 0x71
    ├── ch6 → i2c-8:  ICS83905I PCIe clock buffer @ 0x6E
    └── ch7 → i2c-9:  Thermal sensors
                       ├── MAX6697/MAX6581 @ 0x4D (7-ch remote temp sensor)
                       │   sysfs: /sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-004d
                       │   hwmon: temp1..temp7 (board temperature zones)
                       └── NE1617A/MAX1617 @ 0x18 (2-ch temp sensor)
                           sysfs: /sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0018
                           hwmon: temp1 (NE1617A local), temp2 (MAC board)
```

**Additional DTS-referenced devices on bus i2c-9** (from ONIE DTS):
- 0x1A and 0x4C — may be present on some board revisions

### SFP/QSFP Bus (i2c-1)

```
i2c-1 (ff703100.i2c)
├── PCA9546 @ 0x75 (4-channel, deselect-on-exit)
│   ├── ch0 → i2c-10 → PCA9548 @ 0x74 → i2c-22..29 (ports 1-8)
│   ├── ch1 → i2c-11 → PCA9548 @ 0x74 → i2c-30..37 (ports 9-16)
│   ├── ch2 → i2c-12 → PCA9548 @ 0x74 → i2c-38..45 (ports 17-24)
│   └── ch3 → i2c-13 → PCA9548 @ 0x74 → i2c-46..53 (ports 25-32)
│
├── PCA9546 @ 0x76 (4-channel, deselect-on-exit)
│   ├── ch0 → i2c-14 → PCA9548 @ 0x74 → i2c-54..61 (ports 33-40)
│   ├── ch1 → i2c-15 → PCA9548 @ 0x74 → i2c-62..69 (ports 41-48)
│   ├── ch2 → i2c-16: GPIO control bus 1 + QSFP GPIO
│   │                  ├── PCA9506 @ 0x20 (SFP rate select 0)
│   │                  ├── PCA9506 @ 0x21 (SFP rate select 1)
│   │                  ├── PCA9538 @ 0x70 (QSFP LPMODE[3:0] + RESET[3:0])
│   │                  │   GPIO chip base: 160 (rst_l), 168 (lpmode)
│   │                  ├── PCA9538 @ 0x71 (QSFP MODSEL[3:0] + INT)
│   │                  │   GPIO chip base: 164 (modsel_l)
│   │                  ├── PCA9538 @ 0x72 (SFP ports 40-47 rate select)
│   │                  └── PCA9538 @ 0x73 (misc GPIO)
│   └── ch3 → i2c-17: GPIO control bus 2 (SFP status + control)
│                      ├── PCA9506 @ 0x20 (MOD_ABS: SFP present, ports 0-39)
│                      ├── PCA9506 @ 0x21 (TX_FAULT: ports 0-39)
│                      ├── PCA9506 @ 0x22 (RX_LOS: ports 0-39)
│                      ├── PCA9506 @ 0x23 (mixed: ports 40-47 + QSFP 48-51 presence)
│                      └── PCA9506 @ 0x24 (TX_DISABLE: ports 0-39)
│
└── PCA9546 @ 0x77 (4-channel, deselect-on-exit)
    ├── ch0 → i2c-18: QSFP port 49 (sff8436 @ 0x50, ds100df410 @ 0x27)
    ├── ch1 → i2c-19: QSFP port 50 (sff8436 @ 0x50, ds100df410 @ 0x27)
    ├── ch2 → i2c-20: QSFP port 51 (sff8436 @ 0x50, ds100df410 @ 0x27)
    └── ch3 → i2c-21: QSFP port 52 (sff8436 @ 0x50, ds100df410 @ 0x27)
```

### Complete I2C Device Inventory

| Bus | Addr | Device | Driver | Function |
|-----|------|--------|--------|----------|
| 0 | 0x70 | PCA9548 | pca954x | 8-ch management mux |
| 1 | 0x75 | PCA9546 | pca954x | 4-ch SFP mux (ports 1-32) |
| 1 | 0x76 | PCA9546 | pca954x | 4-ch SFP mux (ports 33-48) + GPIO |
| 1 | 0x77 | PCA9546 | pca954x | 4-ch QSFP mux (ports 49-52) |
| 2 | 0x51 | RTC8564 | rtc8564 | Real-time clock |
| 3 | 0x3A | AT24 | at24 | PSU1 EEPROM/FRU |
| 3 | 0x3E | CPR-4011 | pmbus | PSU1 power monitoring |
| 3 | 0x78 | CPR-4011 | pmbus | PSU1 page register |
| 4 | 0x39 | AT24 | at24 | PSU2 EEPROM/FRU |
| 4 | 0x3D | CPR-4011 | pmbus | PSU2 power monitoring |
| 4 | 0x78 | CPR-4011 | pmbus | PSU2 page register |
| 4 | 0x0C | Unknown | — | PSU2 (purpose unclear) |
| 6 | 0x2C | USB2513i | — | USB hub configuration |
| 7 | 0x71 | VT1165M | — | Voltage margining monitor |
| 8 | 0x6E | ICS83905I | — | PCIe clock buffer |
| 9 | 0x4D | MAX6697 | max6697 | 7-ch temperature sensor |
| 9 | 0x18 | NE1617A | adm1021 | 2-ch temperature sensor |
| 10-15 | 0x74 | PCA9548 | pca954x | 8-ch port sub-muxes (×6) |
| 16 | 0x20 | PCA9506 | — | SFP rate select bank 0 |
| 16 | 0x21 | PCA9506 | — | SFP rate select bank 1 |
| 16 | 0x70 | PCA9538 | gpio-pca953x | QSFP LPMODE + RESET |
| 16 | 0x71 | PCA9538 | gpio-pca953x | QSFP MODSEL + INT |
| 16 | 0x72 | PCA9538 | gpio-pca953x | SFP 40-47 rate select |
| 16 | 0x73 | PCA9538 | gpio-pca953x | Misc GPIO |
| 17 | 0x20 | PCA9506 | — | SFP MOD_ABS (present) ports 0-39 |
| 17 | 0x21 | PCA9506 | — | SFP TX_FAULT ports 0-39 |
| 17 | 0x22 | PCA9506 | — | SFP RX_LOS ports 0-39 |
| 17 | 0x23 | PCA9506 | — | Mixed: SFP 40-47 + QSFP presence |
| 17 | 0x24 | PCA9506 | — | SFP TX_DISABLE ports 0-39 |
| 22-69 | 0x50 | AT24/SFF8436 | at24/sff_8436 | SFP+/QSFP+ EEPROM |
| 18-21 | 0x50 | SFF8436 | sff_8436 | QSFP+ EEPROM |
| 18-21 | 0x27 | DS100DF410 | ds100df410 | QSFP RX retimer |
| * | 0x27 | DS100DF410 | ds100df410 | SFP retimer (ports w/ retimer) |

### QSFP GPIO Initialization (S10gpio_init.sh)

At boot, the PCA9538 GPIO expanders on bus 16 are configured by `S10gpio_init.sh`:

```
GPIO Base 160 (PCA9538 @ 0x70):
  GPIO 160-163: QSFP1-4 RST_L     (output, set HIGH = out of reset)

GPIO Base 164 (PCA9538 @ 0x71):
  GPIO 164-167: QSFP1-4 MODSEL_L  (output, set LOW = module selected)

GPIO Base 168 (PCA9538 @ 0x70):
  GPIO 168-171: QSFP1-4 LPMODE    (output, set LOW = normal power mode)

GPIO 48-51:    QSFP1-4 PRESENCE   (input, active LOW via PCA9506 @ 0x23)
GPIO 24-64:    SFP TX_DISABLE     (output, set LOW = TX enabled)
GPIO 97-104:   SFP TX_DISABLE     (output, set LOW = TX enabled)
```

### Memory-Mapped Devices (Non-I2C)

See [AS5610_52X_BOARD_COMPONENT_MAP.md](AS5610_52X_BOARD_COMPONENT_MAP.md) for
full chip details, markings, and board locations.

| Base Address | Device | Interface | Sysfs Path |
|-------------|--------|-----------|------------|
| 0xEA000000 | Altera EPM570T144C5N (CPLD) | eLBC CS1 | `/sys/devices/ff705000.localbus/ea000000.cpld` |
| 0xEFC00000 | Spansion S29GL064N (8 MB NOR) | eLBC CS0 | — |
| 0xA0000000 | BCM56846 (Trident+) | PCIe BAR0 | `/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0` |

### Per-Port Bus Formula

**Port N = I2C bus (21 + N)**

| Port Range | Bus Range | Mux Path | Retimer Label |
|-----------|-----------|----------|---------------|
| 1-4 | 22-25 | 0x75/ch0 → 0x74/ch0-3 | sfp_rx_eq_0..3 |
| 5-8 | 26-29 | 0x75/ch0 → 0x74/ch4-7 | (none) |
| 9-12 | 30-33 | 0x75/ch1 → 0x74/ch0-3 | sfp_rx_eq_4..7 |
| 13-16 | 34-37 | 0x75/ch1 → 0x74/ch4-7 | (none) |
| 17-20 | 38-41 | 0x75/ch2 → 0x74/ch0-3 | sfp_rx_eq_8..11 |
| 21-24 | 42-45 | 0x75/ch2 → 0x74/ch4-7 | (none) |
| 25-28 | 46-49 | 0x75/ch3 → 0x74/ch0-3 | sfp_tx_eq_0..3 |
| 29-32 | 50-53 | 0x75/ch3 → 0x74/ch4-7 | (none) |
| 33-36 | 54-57 | 0x76/ch0 → 0x74/ch0-3 | sfp_tx_eq_4..7 |
| 37-40 | 58-61 | 0x76/ch0 → 0x74/ch4-7 | (none) |
| 41-44 | 62-65 | 0x76/ch1 → 0x74/ch0-3 | sfp_tx_eq_8..11 |
| 45-48 | 66-69 | 0x76/ch1 → 0x74/ch4-7 | qsfp_tx_eq_0..3 |
| 49-52 | 18-21 | 0x77/ch0-3 (direct) | qsfp_rx_eq_0..3 |

### Per-Port Devices

Each SFP+ port bus has:
- **EEPROM at 0x50**: at24c04 (SFP+) or sff8436 (QSFP+)
- **Retimer at 0x27**: DS100DF410 (only on ports with retimers, see table above)

### Port-to-SerDes Mapping (from Cumulus accton.py)

The BCM56846 SerDes lane assignment for each front-panel port. This mapping is
needed for SDK port configuration and links the I2C port bus to the ASIC lane.

| Port | I2C Bus | SerDes | Port | I2C Bus | SerDes |
|------|---------|--------|------|---------|--------|
| 1 | 22 | 64 | 25 | 46 | 21 |
| 2 | 23 | 65 | 26 | 47 | 20 |
| 3 | 24 | 66 | 27 | 48 | 23 |
| 4 | 25 | 67 | 28 | 49 | 22 |
| 5 | 26 | 68 | 29 | 50 | 24 |
| 6 | 27 | 69 | 30 | 51 | 25 |
| 7 | 28 | 70 | 31 | 52 | 26 |
| 8 | 29 | 71 | 32 | 53 | 27 |
| 9 | 30 | 4 | 33 | 54 | 28 |
| 10 | 31 | 5 | 34 | 55 | 29 |
| 11 | 32 | 6 | 35 | 56 | 30 |
| 12 | 33 | 7 | 36 | 57 | 31 |
| 13 | 34 | 8 | 37 | 58 | 32 |
| 14 | 35 | 9 | 38 | 59 | 33 |
| 15 | 36 | 10 | 39 | 60 | 34 |
| 16 | 37 | 11 | 40 | 61 | 35 |
| 17 | 38 | 12 | 41 | 62 | 36 |
| 18 | 39 | 13 | 42 | 63 | 37 |
| 19 | 40 | 14 | 43 | 64 | 38 |
| 20 | 41 | 15 | 44 | 65 | 39 |
| 21 | 42 | 17 | 45 | 66 | 40 |
| 22 | 43 | 16 | 46 | 67 | 41 |
| 23 | 44 | 19 | 47 | 68 | 42 |
| 24 | 45 | 18 | 48 | 69 | 43 |

**QSFP Ports (4 lanes each):**

| Port | I2C Bus | SerDes Lanes |
|------|---------|-------------|
| 49 | 18 | 48, 49, 50, 51 |
| 50 | 19 | 44, 45, 46, 47 |
| 51 | 20 | 60, 61, 62, 63 |
| 52 | 21 | 56, 57, 58, 59 |

**Source**: `AcctonAS5610_52XSwitch.ports` in
`extracted/2.5.0-amd64/rootfs/usr/lib/python2.7/dist-packages/cumulus/platforms/accton.py`
(lines 1056-1109)

## SFP GPIO Control

All SFP control signals use PCA9506 40-bit GPIO expanders on bus 17 (mux@0x76 ch3).

### GPIO Expander Assignments (from ONLP sfpi.c)

| Signal | PCA9506 Addr | Ports | Direction | Active Level |
|--------|-------------|-------|-----------|-------------|
| SFP_PRESENT | 0x20 | 0-39 | Input | LOW = present |
| TX_FAULT | 0x21 | 0-39 | Input | HIGH = fault |
| RX_LOS | 0x22 | 0-39 | Input | HIGH = loss |
| TX_DISABLE | 0x24 | 0-39 | Output | HIGH = TX enabled* |
| Mixed signals | 0x23 | 40-47 | Mixed | Various |

*TX_DISABLE polarity note: ONLP sets GPIO HIGH to enable TX, suggesting an inverter
between PCA9506 output and SFP+ TX_DISABLE pin (SFF-8431 spec: TX_DISABLE is active HIGH).

### PCA9506 Register Map

| Register | Offset | Description |
|----------|--------|-------------|
| IP0-IP4 | 0x00-0x04 | Input Port (read pin state) |
| OP0-OP4 | 0x08-0x0C | Output Port (write pin state) |
| PI0-PI4 | 0x10-0x14 | Polarity Inversion |
| IOC0-IOC4 | 0x18-0x1C | I/O Configuration (1=input, 0=output) |
| MSK0-MSK4 | 0x20-0x24 | Interrupt Mask |

### TX_DISABLE Pin Mapping (PCA9506 @ 0x24)

| Port | IOC Reg | OP Reg | Bit |
|------|---------|--------|-----|
| 1-8 | 0x18 | 0x08 | 0-7 |
| 9-16 | 0x19 | 0x09 | 0-7 |
| 17-24 | 0x1A | 0x0A | 0-7 |
| 25-32 | 0x1B | 0x0B | 0-7 |
| 33-40 | 0x1C | 0x0C | 0-7 |

To enable TX on port 1:
```python
# Configure pin as output (clear IOC bit)
ioc = i2c_read(17, 0x24, 0x18)
i2c_write(17, 0x24, 0x18, ioc & ~0x01)
# Set output HIGH (TX enabled)
op = i2c_read(17, 0x24, 0x08)
i2c_write(17, 0x24, 0x08, op | 0x01)
```

**CRITICAL**: After cold boot, IOC defaults to 0xFF (all inputs) and OP to 0x00.
TX_DISABLE is FLOATING until software configures the GPIO as output and drives it.

## DS100DF410 Retimer

TI quad-channel 10G retimer/equalizer at I2C address **0x27**. One retimer IC per
group of 4 SFP+ ports. The AS5610-52X is a PHY-less design — these retimers are the
only signal conditioning between the BCM56846 SerDes and the SFP+ cages. They handle
clock/data recovery (CDR), equalization (CTLE + optional DFE), and output drive
level (VOD) tuning.

### Physical Retimer IC Count

There are **8 physical DS100DF410 ICs** on the board:
- 3 RX equalizer retimers for SFP+ ports 1-12 (each serves 4 ports)
- 3 TX equalizer retimers for SFP+ ports 25-36 (questionable — see note)
- 1 retimer for QSFP TX (ports 45-48)
- 1 retimer for QSFP RX (ports 49-52)

Each IC appears at address 0x27 on its respective I2C bus segment. The retimer
class driver enumerates **32 sysfs retimer devices** (retimer0..retimer31), one per
port-bus that has a retimer instantiated in the device tree.

**Note**: Ports 5-8, 13-16, 21-24, 29-32, and 37-40 have **no retimer** — only
EEPROMs. These port groups connect to different PCB trace routing that doesn't
require retiming. Thermal sensors U49 and U57 are placed near retimer ICs for
monitoring.

### Linux Driver Architecture

The retimer subsystem has three components:

1. **retimer_class** (`drivers/misc/retimer_class.c`) — creates sysfs class
   `/sys/class/retimer_dev/` with auto-numbered devices (`retimer0`, `retimer1`,
   ...). Each device exports a `label` attribute read from the device tree `label`
   property. Registered as `subsys_initcall` (runs before normal module init).

2. **ds100df410** (`drivers/misc/ds100df410.c`) — I2C client driver matching
   `"ds100df410"` device ID. On probe, creates sysfs attributes for register
   access and registers with the retimer class. Uses SMBus byte read/write.

3. **Device tree entries** — each retimer is instantiated under its I2C mux
   channel with a label like `sfp_rx_eq_0`, `sfp_tx_eq_4`, `qsfp_rx_eq_0`, etc.

**Sysfs layout per retimer**:
```
/sys/class/retimer_dev/retimer0/
├── label              # e.g. "sfp_rx_eq_0" (from DTS, read-only)
└── device/
    ├── channels       # reg 0xFF — channel select
    ├── reset          # reg 0x00 — device reset
    ├── override       # reg 0x09 — override control
    ├── cdr_rst        # reg 0x0A — CDR reset/release
    ├── tap_dem        # reg 0x15 — DEM tap equalization
    ├── pfd_prbs_dfe   # reg 0x1E — output mux / DFE power
    ├── drv_sel_vod    # reg 0x2D — output VOD level
    ├── adapt_eq_sm    # reg 0x31 — adaptation EQ mode
    └── veo_clk_cdr_cap # reg 0x36 — VEO clock / CDR cap
```

All attributes are read/write (owner write, group/other read: `0644`). Values
are decimal integers. The driver performs no validation — raw register writes.

### Register Space Selection (0xFF — CHANNELS)

The DS100DF410 has per-channel register banks. Register 0xFF selects which
channel's registers are accessed for subsequent reads/writes:

| Value | Selection | Notes |
|-------|-----------|-------|
| 0x00 | Shared/control registers | Global device config |
| 0x04 | Channel 0 only | |
| 0x05 | Channel 1 only | |
| 0x06 | Channel 2 only | |
| 0x07 | Channel 3 only | |
| 0x08 | Channels 0+1 | Broadcast to pair |
| 0x0C | Broadcast all channels | **Used by AS5610 init** |
| 0xFF | All channels (alt) | Same as 0x0C in some docs |

The AS5610 init script writes `12` (decimal, = 0x0C) to select broadcast mode
before programming equalizer settings, so all 4 channels get identical config.

### Complete Register Map (Driver-Exposed)

| Addr | Sysfs Name | Default | Bit Fields |
|------|------------|---------|------------|
| 0x00 | `reset` | — | Device reset control |
| 0x09 | `override` | — | Override control for manual EQ |
| 0x0A | `cdr_rst` | 0x10 | CDR reset (write 0x1C=assert, 0x10=release) |
| 0x15 | `tap_dem` | 0x00 | DEM (Dynamic Equalization Mode) tap settings |
| 0x1E | `pfd_prbs_dfe` | 0xE9 | See bit-field breakdown below |
| 0x2D | `drv_sel_vod` | 0x80 | Output driver VOD (Voltage Output Differential) |
| 0x31 | `adapt_eq_sm` | 0x20 | See bit-field breakdown below |
| 0x36 | `veo_clk_cdr_cap` | 0x00 | VEO clock and CDR capacitor |

#### Additional Registers (Not in sysfs, used in full init sequence)

| Addr | Name | Notes |
|------|------|-------|
| 0x01 | SIG_STATUS | bit0: loss of signal (read-only) |
| 0x02 | CDR_STATUS | bit4: CDR locked, bit3: SBT met (read-only) |
| 0x18 | VCO_DIV | VCO divider (0x00 = div-by-1 for 10G) |
| 0x1F | LPF_DAC | Loop filter DAC (0x52 for 10G SFI) |
| 0x2F | LOCK_RATE | bits[7:4]: rate lock (0xC0 = 10.3125 Gbps) |

### Critical Register Bit-Field Breakdowns

#### Register 0x1E — PFD_PRBS_DFE

```
  7   6   5   4   3   2   1   0
┌───┬───┬───┬───┬───┬───┬───┬───┐
│    OUT_MUX    │   │DFE│   │   │
│   [7:5]       │   │_PD│   │   │
└───┴───┴───┴───┴───┴───┴───┴───┘
```

| Bits | Field | Values |
|------|-------|--------|
| [7:5] | OUT_MUX | 0=normal data, **7=MUTED** (default!) |
| [3] | DFE_PD | 0=DFE enabled, **1=DFE powered down** (default!) |

**Default 0xE9 = 0b11101001**: OUT_MUX=7 (muted) + DFE_PD=1 (powered down).
This means the retimer **outputs nothing by default** until software initializes it.

| Value | Meaning |
|-------|---------|
| 0xE9 | **Default** — output muted, DFE off (no signal passes!) |
| 0xE1 | Output muted, DFE enabled (AS6701 uses for ports > 19) |
| 0x00 | **Normal operation** — output unmuted, DFE enabled |

#### Register 0x31 — ADAPT_EQ_SM

```
  7   6   5   4   3   2   1   0
┌───┬───┬───┬───┬───┬───┬───┬───┐
│   │ MODE  │                   │
│   │ [6:5] │                   │
└───┴───┴───┴───┴───┴───┴───┴───┘
```

| Bits[6:5] | Mode | Description |
|-----------|------|-------------|
| 00 | Manual | No adaptation, use fixed EQ settings |
| 01 | CTLE only | Continuous Time Linear Equalization only |
| 10 | CTLE + DFE | Full adaptive equalization (**preferred for 10G**) |

| Value | Meaning |
|-------|---------|
| 0x20 | Default — mode 1 (CTLE only) |
| 0x40 | **Mode 2 (CTLE+DFE)** — used by AS5610 and AS6701 for ports > 19 |

#### Register 0x15 — TAP_DEM

Controls the output driver DEM (Dynamic Equalization Mode) taps for pre-emphasis
and de-emphasis. The value encodes both the tap coefficients and polarity.

| Value | Meaning (AS5610 context) |
|-------|--------------------------|
| 0x00 | No DEM (default, used for most SFP RX/TX) |
| 0x17 (23 decimal) | DEM enabled — used for QSFP and sfp_rx_eq_10 |

#### Register 0x2D — DRV_SEL_VOD

Controls the output driver Voltage Output Differential level. Higher values =
stronger output swing. Bit 7 selects the driver, bits [6:0] set the VOD level.

| Value | Approximate Output Level |
|-------|--------------------------|
| 0x80 | Default (~600 mVppd) |
| 0x81 | Slightly higher (~650 mVppd) |
| 0x83 | Medium (~750 mVppd) |
| 0x84 | Higher (~800 mVppd) |
| 0x87 | Maximum (~950 mVppd) |

#### Register 0x36 — VEO_CLK_CDR_CAP

| Value | Meaning |
|-------|---------|
| 0x00 | Default — uses 25 MHz reference clock |
| 0x01 | **No 25 MHz reference clock** (AS5610/AS6701 setting) |

### AS5610 Initialization (S20retimer_init.sh)

The init script runs at boot (`S20` priority in `hw_init.d`). It iterates all 32
retimer sysfs devices and applies one of two equalization profiles based on the
device tree label.

#### Equalization Profiles

**Profile `set_eq1`** — Default for most SFP ports:
```sh
echo 12 > channels        # 0x0C = broadcast all channels
echo 1  > veo_clk_cdr_cap # No 25MHz ref clock
echo 28 > cdr_rst         # 0x1C = CDR reset assert
echo 16 > cdr_rst         # 0x10 = CDR reset release
```

**Profile `set_eq2`** — For QSFP and sfp_rx_eq_10 (longer traces):
```sh
echo 12 > channels        # 0x0C = broadcast all channels
echo 1  > veo_clk_cdr_cap # No 25MHz ref clock
echo 28 > cdr_rst         # 0x1C = CDR reset assert
echo 16 > cdr_rst         # 0x10 = CDR reset release
echo 23 > tap_dem         # 0x17 = DEM tap enabled (pre-emphasis)
```

The only difference: `set_eq2` adds a TAP_DEM write of 23 (0x17), enabling
output pre-emphasis for traces that need it.

#### Profile Assignment by Label

| Label Pattern | Profile | Ports Affected |
|---------------|---------|----------------|
| `sfp_rx_eq_0..9` | set_eq1 | SFP RX ports 1-4, 9-12, 17-20 (most) |
| `sfp_rx_eq_10` | **set_eq2** | SFP RX ports (longer trace to this retimer) |
| `sfp_rx_eq_11` | set_eq1 | SFP RX ports |
| `sfp_tx_eq_*` | set_eq1 | SFP TX ports 25-28, 33-36, 41-44 |
| `qsfp_*` | **set_eq2** | All QSFP TX and RX (ports 45-52) |

#### What the AS5610 Init Does NOT Do

Notably, the AS5610 init script is minimal compared to a full DS100DF410 setup:
- Does **not** write `pfd_prbs_dfe` (reg 0x1E) — leaves default 0xE9 (output muted!)
- Does **not** write `adapt_eq_sm` (reg 0x31) — leaves default CTLE-only mode
- Does **not** write `drv_sel_vod` (reg 0x2D) — leaves default VOD
- Does **not** write `reset` (reg 0x00) or `lock_rate` (reg 0x2F)

This suggests Cumulus Linux's `switchd` (or the Memory-Mapped Broadcom SDK path)
handles the full retimer initialization including unmuting and rate-locking, and
this init script only pre-programs the analog EQ tuning that varies by board trace
length. Alternatively, the Cumulus DTS may set different defaults than the TI
datasheet values.

**Contrast with AS6701-32X**: The AS6701 init script is much more complete — it
writes `pfd_prbs_dfe` (0xE1 = unmute DFE), `adapt_eq_sm` (0x40 = CTLE+DFE mode),
per-port `tap_dem` and `drv_sel_vod` from lookup tables, showing the full init
sequence needed when the NOS doesn't handle retimer setup.

### Full 10G SFI Initialization Sequence

For custom NOS development, the complete retimer init (combining AS6701 script
knowledge + TI SNLA323 programming guide) is:

```python
# Step 1: Select all channels
i2c_write(bus, 0x27, 0xFF, 0x0C)  # Broadcast all channels

# Step 2: Reset
i2c_write(bus, 0x27, 0x00, 0x04)  # Channel reset

# Step 3: Rate lock to 10.3125 Gbps
i2c_write(bus, 0x27, 0x2F, 0xC0)  # LOCK_RATE = 10.3125G
i2c_write(bus, 0x27, 0x18, 0x00)  # VCO divider = 1
i2c_write(bus, 0x27, 0x1F, 0x52)  # LPF DAC for 10G

# Step 4: Enable adaptive equalization
i2c_write(bus, 0x27, 0x31, 0x40)  # CTLE + DFE mode

# Step 5: Clock reference
i2c_write(bus, 0x27, 0x36, 0x01)  # No 25MHz ref clock

# Step 6: Output pre-emphasis (board-dependent)
i2c_write(bus, 0x27, 0x15, 0x17)  # DEM tap (0x00 for short traces)

# Step 7: Output drive level (board-dependent)
i2c_write(bus, 0x27, 0x2D, 0x83)  # VOD level

# Step 8: UNMUTE OUTPUT (critical!)
i2c_write(bus, 0x27, 0x1E, 0x00)  # Unmute output, enable DFE

# Step 9: CDR reset cycle
i2c_write(bus, 0x27, 0x0A, 0x1C)  # CDR reset assert
time.sleep(0.02)                   # 20ms settling time
i2c_write(bus, 0x27, 0x0A, 0x10)  # CDR reset release
```

**Order matters**: The CDR reset must come last, after all analog parameters
are configured. The 20ms delay between reset assert and release allows the PLL
to settle.

### Retimer-to-Port Signal Flow

```
                    BCM56846 SerDes
                         │
           ┌─────────────┴─────────────┐
           │                           │
     TX SerDes lane              RX SerDes lane
           │                           │
    ┌──────▼──────┐             ┌──────▼──────┐
    │ DS100DF410  │             │ DS100DF410  │
    │ TX Retimer  │             │ RX Retimer  │
    │ (sfp_tx_eq) │             │ (sfp_rx_eq) │
    └──────┬──────┘             └──────┬──────┘
           │                           │
      SFP+ TX pin               SFP+ RX pin
           │                           │
           └───────── SFP+ Module ─────┘
```

For SFP+ ports 1-24: only RX retimers are present (sfp_rx_eq_0..11).
For SFP+ ports 25-48: both TX and RX retimers may be present, depending on port group.
For QSFP ports 49-52: both TX and RX retimers (qsfp_tx_eq_0..3, qsfp_rx_eq_0..3).

Ports without retimers (5-8, 13-16, 21-24, 29-32, 37-40) have direct SerDes-to-cage
connections with trace lengths short enough to not need signal conditioning.

## Source References

- **ONLP sfpi.c**: `/Users/smiley/Documents/Coding/edgecore/onl/packages/platforms/accton/powerpc/powerpc-accton-as5610-52x/onlp/builds/src/module/src/sfpi.c`
- **DTS**: `open-nos-as5610/boot/as5610_52x_full.dts`
- **TI DS100DF410 Programming Guide**: SNLA323
- **ONL ds100df410 driver patch**: `opennetworklinux/linux` 3.2.65 patches
- **Cumulus ds100df410.c driver**: `OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_ds100df410.c.patch`
- **Cumulus retimer_class.c**: `OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_retimer_class.c.patch`
- **AS5610 retimer init**: `extracted/2.5.1-powerpc/rootfs/usr/share/platform-config/accton/as5610_52x/hw_init.d/S20retimer_init.sh`
- **AS6701 retimer init (comparison)**: `extracted/2.5.1-powerpc/rootfs/usr/share/platform-config/accton/as6701_32x/hw_init.d/S20retimer_init.sh`

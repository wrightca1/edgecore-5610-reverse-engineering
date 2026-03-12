# ONLP Platform Reference: Edgecore AS5610-52X (powerpc-accton-as5610-52x)

> **Purpose**: Complete documentation of the ONL (Open Network Linux) ONLP platform
> driver for the Edgecore AS5610-52X switch, including all source files, hardware
> interfaces, CPLD registers, I2C device maps, SFP access, thermal management,
> fan control, PSU monitoring, and LED control.

**ONL Source**: `/Users/smiley/Documents/Coding/edgecore/onl/`
**Platform Path**: `packages/platforms/accton/powerpc/powerpc-accton-as5610-52x/`
**Architecture**: PowerPC (Freescale P2020)
**ASIC**: BCM56846_A1 (Trident+)
**Ports**: 48x 1G SFP + 4x 40G QSFP+

---

## Table of Contents

1. [Source File Inventory](#1-source-file-inventory)
2. [ONLP Framework Overview](#2-onlp-framework-overview)
3. [Platform Library (platform_lib)](#3-platform-library-platform_lib)
4. [CPLD Register Map](#4-cpld-register-map)
5. [I2C Device Map](#5-i2c-device-map)
6. [System Implementation (sysi.c)](#6-system-implementation-sysic)
7. [Thermal Sensors (thermali.c)](#7-thermal-sensors-thermalic)
8. [Fan Control (fani.c)](#8-fan-control-fanic)
9. [PSU Monitoring (psui.c)](#9-psu-monitoring-psuic)
10. [SFP/QSFP Management (sfpi.c)](#10-sfpqsfp-management-sfpic)
11. [LED Control (ledi.c)](#11-led-control-ledic)
12. [ONLP API Contracts](#12-onlp-api-contracts)
13. [OID Hierarchy](#13-oid-hierarchy)
14. [Build System](#14-build-system)

---

## 1. Source File Inventory

**Base path**: `packages/platforms/accton/powerpc/powerpc-accton-as5610-52x/onlp/builds/src/module/`

### Implementation Files (`src/`)

| File | Lines | Purpose |
|------|-------|---------|
| `platform_lib.c` | | Core platform library: CPLD, I2C, PMBus, mux control |
| `platform_lib.h` | | Platform library declarations and constants |
| `sysi.c` | | System ONLP: platform ID, ONIE data, OID table |
| `thermali.c` | | Thermal sensors: NE1617A, MAX6581, BCM56846, PSU |
| `fani.c` | | Fan control: chassis fan (CPLD), PSU fans (PMBus) |
| `psui.c` | | PSU monitoring: status, voltage, current, power |
| `sfpi.c` | ~4100 | SFP/QSFP: presence, EEPROM, TX control, retimer EQ |
| `ledi.c` | | LED control: DIAG, FAN, LOC, PSU1, PSU2 |
| `powerpc_accton_as5610_52x_module.c` | | Module initialization |
| `powerpc_accton_as5610_52x_config.c` | | Configuration management |
| `powerpc_accton_as5610_52x_enums.c` | | Enumeration definitions |
| `powerpc_accton_as5610_52x_log.c` | | Logging implementation |
| `powerpc_accton_as5610_52x_int.h` | | Internal header |
| `powerpc_accton_as5610_52x_log.h` | | Logging header |

### Public Headers (`inc/powerpc_accton_as5610_52x/`)

| File | Purpose |
|------|---------|
| `powerpc_accton_as5610_52x_config.h` | Configuration macros |
| `powerpc_accton_as5610_52x_porting.h` | Porting macros |
| `powerpc_accton_as5610_52x_dox.h` | Documentation header |

---

## 2. ONLP Framework Overview

### Architecture

ONLP uses a split architecture:

```
User Application
    ↓
Public API (onlp/*.h)          ← Validation, caching, error handling
    ↓
Platform Interface (onlp/platformi/*.h)  ← What platform drivers implement
    ↓
Platform Driver (sfpi.c, fani.c, etc.)   ← Hardware-specific code
    ↓
Hardware (I2C, CPLD, PMBus)
```

### OID System

All hardware components are identified by 32-bit Object IDs:

```c
typedef uint32_t onlp_oid_t;

// OID format: [type(8 bits) | id(24 bits)]
#define ONLP_OID_TYPE_GET(_id)           ((_id) >> 24)
#define ONLP_OID_ID_GET(_id)            (_id & 0xFFFFFF)
#define ONLP_OID_TYPE_CREATE(_type, _id) ((_type) << 24 | (_id))
```

OID types:
```
ONLP_OID_TYPE_CHASSIS  = 1    // System root
ONLP_OID_TYPE_MODULE   = 2    // Plug-in modules
ONLP_OID_TYPE_THERMAL  = 3    // Temperature sensors
ONLP_OID_TYPE_FAN      = 4    // Cooling fans
ONLP_OID_TYPE_PSU      = 5    // Power supplies
ONLP_OID_TYPE_LED      = 6    // Indicator lights
ONLP_OID_TYPE_SFP      = 7    // Pluggable transceivers
ONLP_OID_TYPE_GENERIC  = 8    // Custom objects
```

### OID Header (Common to All Objects)

```c
typedef struct onlp_oid_hdr_s {
    onlp_oid_t id;                    // Object ID
    char description[128];             // Human-readable name
    onlp_oid_t poid;                  // Parent OID
    onlp_oid_t coids[256];            // Children OID table
    onlp_oid_status_flags_t status;   // PRESENT, FAILED, OPERATIONAL, UNPLUGGED
} onlp_oid_hdr_t;
```

### Initialization Flow

```
onlp_sw_init()
  → onlp_platform_sw_init(platform)
  → onlp_fan_sw_init()       → onlp_fani_sw_init()
  → onlp_thermal_sw_init()   → onlp_thermali_sw_init()
  → onlp_psu_sw_init()       → onlp_psui_sw_init()
  → onlp_led_sw_init()       → onlp_ledi_sw_init()
  → onlp_sfp_sw_init()       → onlp_sfpi_sw_init()
```

---

## 3. Platform Library (platform_lib)

### CPLD Access

```c
#define CPLD_BASE_ADDRESS  0xEA000000

int cpld_read(unsigned int regOffset, unsigned char *val);
int cpld_write(unsigned int regOffset, unsigned char val);
```

Uses memory-mapped I/O via `/dev/mem` at base address **0xEA000000**.

### I2C Access Functions

```c
#define MAX_I2C_BUSSES     2
#define I2C_BUFFER_MAXSIZE 16

int i2c_read(unsigned int bus_id, unsigned char i2c_addr,
             unsigned char offset, unsigned char *buf);
int i2c_write(unsigned int bus_id, unsigned char i2c_addr,
              unsigned char offset, unsigned char *buf);
int i2c_nRead(unsigned int bus_id, unsigned char i2c_addr,
              unsigned char offset, unsigned int size, unsigned char *buf);
int i2c_nWrite(unsigned int bus_id, unsigned char i2c_addr,
               unsigned char offset, unsigned int size, unsigned char *buf);
int i2c_nWriteForce(unsigned int bus_id, unsigned char i2c_addr,
                    unsigned char offset, unsigned int size,
                    unsigned char *buf, int force);
```

### PCA9548 Mux Control

```c
int as5610_52x_i2c0_pca9548_channel_set(unsigned char channel);
```

Controls the PCA9548 multiplexer at address **0x70** on I2C bus 0. Used for
routing thermal sensor and PSU access.

### PMBus Helper Functions

```c
int pmbus_parse_literal_format(unsigned short val);
int pmbus_read_literal_data(unsigned char bus, unsigned char i2c_addr,
                            unsigned char reg, int *val);
int pmbus_parse_vout_format(unsigned char vout_mode, unsigned short val);
int pmbus_read_vout_data(unsigned char bus, unsigned char i2c_addr, int *val);
int int_to_pmbus_linear(int val);

#define PMBUS_LITERAL_DATA_MULTIPLIER  1000
```

PMBus linear format: 5-bit signed exponent (bits[15:11]) + 11-bit mantissa (bits[10:0]).
Result = mantissa * 2^exponent * 1000 (millivolts/milliamps/milliwatts).

### PSU Type Detection

```c
typedef enum as5610_52x_psu_type {
    PSU_TYPE_UNKNOWN,
    PSU_TYPE_AC_F2B,        // Front-to-Back AC (CPR-4011-4M11)
    PSU_TYPE_AC_B2F,        // Back-to-Front AC (CPR-4011-4M21)
    PSU_TYPE_DC_48V_F2B,    // Front-to-Back DC (um400d01-01G)
    PSU_TYPE_DC_48V_B2F     // Back-to-Front DC (um400d01G)
} as5610_52x_psu_type_t;

as5610_52x_psu_type_t as5610_52x_get_psu_type(int id, char* modelname,
                                               int modelname_len);
```

Detection algorithm:
1. Set PCA9548 channel (0x2 for PSU1, 0x4 for PSU2)
2. Try AC PSU: read model name from EEPROM @ 0x3A/0x39, register 0x26
3. Compare against "CPR-4011-4M11" (F2B) or "CPR-4011-4M21" (B2F)
4. Try DC PSU: read model name from EEPROM @ 0x56/0x55, register 0x50
5. Compare against "um400d01G" (B2F) or "um400d01-01G" (F2B)

---

## 4. CPLD Register Map

The CPLD is memory-mapped at **0xEA000000**.

| Offset | Name | R/W | Function |
|--------|------|-----|----------|
| 0x01 | PSU2_STATUS | R | PSU2 status bits |
| 0x02 | PSU1_STATUS | R | PSU1 status bits |
| 0x03 | SYS_STATUS | R | System/fan status bits |
| 0x0D | FAN_SPEED_CTL | R/W | Chassis fan speed (5-bit, 0x00-0x1F) |
| 0x13 | LED_CONTROL_1 | R/W | PSU/FAN/DIAG LED control |
| 0x15 | LED_CONTROL_2 | R/W | Locator LED control |

### PSU Status Registers (0x01, 0x02)

```
Bit 0: PSU_PRESENT     (0=present, 1=absent — inverted logic)
Bit 1: PSU_POWER_GOOD  (0=good, 1=bad — inverted logic)
Bit 2: PSU_FAN_FAILURE (0=OK, 1=failed — inverted logic for DC; direct for AC)
```

### System Status Register (0x03)

```
Bit 2: FAN_PRESENT    (0=present, inverted)
Bit 3: FAN_FAILURE    (1=failed)
Bit 4: FAN_DIRECTION  (1=F2B, 0=B2F)
```

### Fan Speed Control (0x0D)

5-bit value controlling chassis fan PWM duty cycle:

| Value | Duty Cycle |
|-------|-----------|
| 0x1F | 100% (MAX) |
| 0x15 | 70% (MID) |
| 0x0C | 40% (MIN) |
| Other | value * 3.25% |

### LED Control Register 1 (0x13)

```
Bits [1:0] = PSU1 LED:  0x03=OFF, 0x02=GREEN, 0x01=AMBER
Bits [3:2] = PSU2 LED:  0x0C=OFF, 0x08=GREEN, 0x04=AMBER
Bits [5:4] = DIAG LED:  0x00=OFF, 0x20=GREEN, 0x10=AMBER
Bits [7:6] = FAN LED:   0xC0=OFF, 0x40=GREEN, 0x80=AMBER
```

### LED Control Register 2 (0x15)

```
Bits [1:0] = LOC LED:   0x01=OFF, 0x03=ORANGE BLINKING
```

---

## 5. I2C Device Map

### Bus 0 — Management Bus

| Device | Address | PCA9548 Ch | Function |
|--------|---------|------------|----------|
| PCA9548 | 0x70 | — | Management bus mux |
| NE1617A | 0x18 | 0x80 | Thermal sensor (2 ch: local + remote) |
| MAX6581 | 0x4D | 0x80 | Thermal sensor (8 ch: local + 7 remote) |
| PSU1 PMBus | 0x3E | 0x02 | AC PSU1 config/monitoring |
| PSU1 EEPROM | 0x3A | 0x02 | AC PSU1 model/serial info |
| PSU2 PMBus | 0x3D | 0x04 | AC PSU2 config/monitoring |
| PSU2 EEPROM | 0x39 | 0x04 | AC PSU2 model/serial info |
| PSU1 DC EEPROM | 0x56 | 0x02 | DC PSU1 model info |
| PSU2 DC EEPROM | 0x55 | 0x04 | DC PSU2 model info |
| RTC | — | 0x01 | Reserved by kernel |

### Bus 1 — SFP/QSFP Bus

| Device | Address | Function |
|--------|---------|----------|
| PCA9546 | 0x75 | Primary mux for 1G SFP ports 0-31 |
| PCA9546 | 0x76 | Primary mux for 1G SFP ports 32-47 + GPIO |
| PCA9546 | 0x77 | QSFP mux for 40G ports 48-51 |
| PCA9548 | 0x74 | Secondary mux (per-port SFP access) |
| PCA9506 | 0x20 | GPIO: SFP PRESENT (input, active LOW) |
| PCA9506 | 0x21 | GPIO: SFP TX_FAULT (input, active HIGH) |
| PCA9506 | 0x22 | GPIO: SFP RX_LOS (input, active HIGH) |
| PCA9506 | 0x23 | GPIO: Additional SFP signals (ports 40-47) |
| PCA9506 | 0x24 | GPIO: SFP TX_DISABLE (output, HIGH=TX enabled) |
| IO Expander | 0x71 | QSFP MODSEL control |
| DS100DF410 | 0x27 | 10G retimer/equalizer |
| SFP EEPROM | 0x50 | Per-port SFP identification (via mux) |
| SFP DOM | 0x51 | Per-port SFP diagnostics (via mux) |

---

## 6. System Implementation (sysi.c)

### Platform Identification

```c
const char* onlp_sysi_platform_get(void)
{
    return "powerpc-accton-as5610-52x-rX";
}
```

### ONIE Data

```c
int onlp_sysi_onie_data_phys_addr_get(void** physaddr)
{
    *physaddr = (void*)(0xeff70000);
    return ONLP_STATUS_OK;
}
```

ONIE data stored at physical address **0xEFF70000** (in NOR flash).

### OID Table

The system exposes the following objects:

| Type | Count | IDs | Description |
|------|-------|-----|-------------|
| PSU | 2 | 1, 2 | Power supplies |
| Fan | 1 | 1 | Chassis fan |
| Thermal | 11 | 1-11 | NE1617A(2) + MAX6581(8) + BCM56846(1) |
| LED | 5 | 1-5 | DIAG, FAN, LOC, PSU1, PSU2 |

---

## 7. Thermal Sensors (thermali.c)

### Sensor Enumeration

```c
enum onlp_thermal_id {
    THERMAL_RESERVED = 0,
    NE1617A_LOCAL_SENSOR,           // 1 — NE1617A local
    NE1617A_REMOTE_SENSOR,          // 2 — NE1617A remote
    MAX6581_LOCAL_SENSOR,           // 3 — MAX6581 local
    MAX6581_REMOTE_SENSOR_1,        // 4 — MAX6581 remote ch1
    MAX6581_REMOTE_SENSOR_2,        // 5
    MAX6581_REMOTE_SENSOR_3,        // 6
    MAX6581_REMOTE_SENSOR_4,        // 7
    MAX6581_REMOTE_SENSOR_5,        // 8
    MAX6581_REMOTE_SENSOR_6,        // 9
    MAX6581_REMOTE_SENSOR_7,        // 10
    BCM56846_LOCAL_SENSOR,          // 11 — Switch ASIC temperature
    PSU1_THERMAL_SENSOR_1,          // 12 — PSU1 temperature
    PSU2_THERMAL_SENSOR_1,          // 13 — PSU2 temperature
};

#define NUM_OF_CHASSIS_THERMAL_SENSOR  11   // excludes PSU sensors
#define TEMPERATURE_MULTIPLIER         1000  // values in millidegrees C
```

### Initialization

```c
int onlp_thermali_init(void)
{
    // 1. Set PCA9548 channel 0x80 (bus 0)
    // 2. Read MAX6581 config register (0x41)
    // 3. If extended range bit (0x02) not set, set it and write back
    // 4. Sleep 1 second after configuration change
    // 5. Close channel (write 0x00)
}
```

### NE1617A Sensor

- I2C bus 0, address **0x18**, PCA9548 channel **0x80**
- 2 channels: Local (register 0x00), Remote (register 0x01)
- 1-byte integer temperature, multiply by 1000 for millidegrees

### MAX6581 Sensor

- I2C bus 0, address **0x4D**, PCA9548 channel **0x80**
- 8 channels: Local + 7 remote
- Temperature registers: 0x07 (local), 0x01-0x06, 0x08 (remote 1-7)
- Extended decimal registers: 0x51-0x58 (fractional part)
- Configuration register: 0x41 (bit 1 = extended range enable)
- Diode fault status: register 0x46
- Extended range offset: -64°C (when bit set)

### BCM56846 ASIC Sensor

- Reads from file: `/var/run/broadcom/temp0`
- Updated by switch management daemon (switchd)
- Not directly accessed via I2C

### PSU Thermal Sensors

- AC PSU (CPR-4011) only, via PMBus
- PSU1: address 0x3E, PCA9548 channel 0x02
- PSU2: address 0x3D, PCA9548 channel 0x04
- PMBus STATUS_TEMPERATURE register: 0x7D (failure bits: status & 0x90)
- PMBus temperature data register: 0x8D (linear format)

---

## 8. Fan Control (fani.c)

### Chassis Fan

Controlled via CPLD registers:

| Register | Offset | Purpose |
|----------|--------|---------|
| Status | 0x03 | Presence, failure, direction |
| Speed | 0x0D | PWM duty cycle (5-bit) |

**Status bits (CPLD 0x03)**:
```c
#define CPLD_FAN_PRESENT_MASK    0x04  // Bit 2 (inverted: 0=present)
#define CPLD_FAN_FAILURE_MASK    0x08  // Bit 3 (1=failed)
#define CPLD_FAN_DIRECTION_MASK  0x10  // Bit 4 (1=F2B, 0=B2F)
```

**Speed values**:
```c
#define CPLD_FAN_SPEED_VALUE_MAX  0x1F  // 100%
#define CPLD_FAN_SPEED_VALUE_MID  0x15  // 70%
#define CPLD_FAN_SPEED_VALUE_MIN  0x0C  // 40%

enum onlp_fan_duty_cycle_percentage {
    FAN_PERCENTAGE_MIN = 40,
    FAN_PERCENTAGE_MID = 70,
    FAN_PERCENTAGE_MAX = 100
};
```

**Conversion function**:
```c
static int chassis_fan_cpld_val_to_duty_cycle(unsigned char reg_val) {
    reg_val &= 0x1F;
    if (reg_val == 0x1F) return 100;
    if (reg_val == 0x15) return 70;
    if (reg_val == 0x0C) return 40;
    return (reg_val * 3.25);
}
```

### PSU Fans

**AC PSU (CPR-4011)**:
- Speed control register: 0x3B (PMBus)
- Status register: 0x81 (bit 7 = failure)
- PSU1: address 0x3E, PCA9548 channel 0x02
- PSU2: address 0x3D, PCA9548 channel 0x04

**DC PSU (um400d)**:
- Status only (no speed control)
- PSU1 status: CPLD offset 0x02, failure mask 0x04
- PSU2 status: CPLD offset 0x01, failure mask 0x04

---

## 9. PSU Monitoring (psui.c)

### PSU Status (CPLD)

```
PSU1: CPLD offset 0x02
PSU2: CPLD offset 0x01

Bit 0: PRESENT     (0=present, inverted)
Bit 1: POWER_GOOD  (0=good, inverted)
Bit 2: FAN_FAILURE (0=OK, inverted)
```

### AC PSU (CPR-4011) — PMBus Monitoring

**Capabilities**: `ONLP_PSU_CAPS_AC | GET_VIN | GET_VOUT | GET_IIN | GET_IOUT | GET_PIN | GET_POUT`

**PMBus Registers**:

| Register | Address | Function | Format |
|----------|---------|----------|--------|
| READ_VIN | 0x88 | Input voltage | Linear (mV) |
| READ_VOUT | 0x8B | Output voltage | VOUT mode |
| READ_IIN | 0x89 | Input current | Linear (mA) |
| READ_IOUT | 0x8C | Output current | Linear (mA) |
| READ_PIN | 0x97 | Input power | Linear (mW) |
| READ_POUT | 0x96 | Output power | Linear (mW) |
| VOUT_MODE | 0x20 | Output voltage format | Mode byte |

**I2C Addresses**:

| PSU | Config Addr | EEPROM Addr | PCA9548 Ch |
|-----|-------------|-------------|------------|
| PSU1 | 0x3E | 0x3A | 0x02 |
| PSU2 | 0x3D | 0x39 | 0x04 |

Model name at EEPROM register 0x26.

### DC PSU (um400d)

**Capabilities**: `ONLP_PSU_CAPS_DC48` (status only, no voltage/current monitoring)

**I2C Addresses**: PSU1=0x56, PSU2=0x55 (EEPROM at register 0x50)

---

## 10. SFP/QSFP Management (sfpi.c)

This is the largest file (~4100 lines) and handles all 52 transceiver ports.

### Port Layout

- **Ports 0-47**: 1G SFP modules (48 ports)
- **Ports 48-51**: 40G QSFP+ modules (4 ports)

### I2C Addresses

```c
#define SFP_IDPROM_ADDR  0x50   // SFP EEPROM (identification)
#define SFP_DOM_ADDR     0x51   // SFP DOM (diagnostics monitoring)
```

### 1G SFP I2C Mux Hierarchy (Ports 0-47)

Two-level mux chain on I2C bus 1:

```
Level 1: PCA9546 at 0x75 or 0x76 (channel select)
Level 2: PCA9548 at 0x74 (per-port select)

Port  0-7:  0x75 ch 0x01 → 0x74 ch {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}
Port  8-15: 0x75 ch 0x02 → 0x74 ch {0x01..0x80}
Port 16-23: 0x75 ch 0x04 → 0x74 ch {0x01..0x80}
Port 24-31: 0x75 ch 0x08 → 0x74 ch {0x01..0x80}
Port 32-39: 0x76 ch 0x01 → 0x74 ch {0x01..0x80}
Port 40-47: 0x76 ch 0x02 → 0x74 ch {0x01..0x80}
```

**Data structure**:
```c
typedef struct mux_info {
    unsigned char addr;    // Mux I2C address
    unsigned char ch;      // Channel select value
} mux_info_t;

typedef struct sfp_eeprom_hierarchy {
    int port;
    unsigned int bus;      // I2C bus (1)
    mux_info_t mux[2];    // [0]=primary, [1]=secondary
} sfp_eeprom_hierarchy_t;
```

### 40G QSFP I2C Access (Ports 48-51)

Single-level mux, direct to EEPROM:

```
Port 48: PCA9546 @ 0x77, channel 0x01 → EEPROM @ 0x50
Port 49: PCA9546 @ 0x77, channel 0x02 → EEPROM @ 0x50
Port 50: PCA9546 @ 0x77, channel 0x04 → EEPROM @ 0x50
Port 51: PCA9546 @ 0x77, channel 0x08 → EEPROM @ 0x50
```

### EEPROM Read Algorithm

```
1. Look up port in sfp_eeprom_data[] table
2. Write primary mux channel (PCA9546 @ 0x75/0x76/0x77)
3. Write secondary mux channel (PCA9548 @ 0x74) — 1G SFP only
4. Read 256 bytes from EEPROM at 0x50 (IDPROM) or 0x51 (DOM)
   — 16-byte chunks, 16 iterations
5. Clear secondary mux (write 0x00)
6. Clear primary mux (write 0x00)
```

### SFP GPIO Control (Ports 0-47)

GPIO expanders on bus 1, accessed through PCA9546 @ 0x76, channel 0x08:

| Signal | Address | Config Reg | Data Reg | Active |
|--------|---------|------------|----------|--------|
| PRESENT | 0x20 | 0x18-0x1C | 0x00-0x04 | LOW = present |
| TX_FAULT | 0x21 | 0x18-0x1A | 0x00-0x02 | HIGH = fault |
| RX_LOS | 0x22 | 0x18-0x1C | 0x00-0x04 | HIGH = loss |
| TX_DISABLE | 0x24 | 0x18-0x1C | 0x08-0x0C | Set IOC=output, OP=1 to enable |

**Port-to-register mapping**:
```
Ports  0-7:  config_reg = 0x18, bit mask 0x01-0x80
Ports  8-15: config_reg = 0x19, bit mask 0x01-0x80
Ports 16-23: config_reg = 0x1A, bit mask 0x01-0x80
Ports 24-31: config_reg = 0x1B, bit mask 0x01-0x80
Ports 32-39: config_reg = 0x1C, bit mask 0x01-0x80
Ports 40-47: special mapping (addr 0x23 for some signals)
```

### TX Enable/Disable

```c
int onlp_sfpi_enable_set(int port, int enable);
int onlp_sfpi_enable_get(int port, int* enable);
```

Uses IO expander at 0x24:
- Set IOC register bit to 0 (output mode)
- Set OP register bit to 1 (TX enabled) or 0 (TX disabled)

### QSFP MODSEL Control

```c
static int init_qsfp_modsel(void) {
    // Set PCA9546 @ 0x76 channel 0x04
    // Set IO expander @ 0x71 to output mode
    // Drive MODSEL pins low for 40G mode
}
```

### DS100DF410 Retimer/Equalizer Configuration

The SFP driver configures the retimer for QSFP ports:

```c
typedef struct equalizer_info {
    unsigned int bus_id;
    unsigned char i2c_addr;    // 0x27
    unsigned char offset;      // Register offset
    unsigned char data;        // Value to write
} equalizer_info_t;
```

- Channel select register: 0xFF (0x04=Ch0, 0x08=Ch1, 0x10=Ch2, 0x20=Ch3)
- RX/TX equalization programmed per QSFP port
- Accessed through PCA9546 @ 0x77 channel selection

### Key SFP API Functions

```c
int onlp_sfpi_sw_init(void);
int onlp_sfpi_bitmap_get(onlp_sfp_bitmap_t* bmap);       // Valid ports
int onlp_sfpi_is_present(onlp_oid_id_t id);              // Single port
int onlp_sfpi_presence_bitmap_get(onlp_sfp_bitmap_t* dst); // All ports
int onlp_sfpi_rx_los_bitmap_get(onlp_sfp_bitmap_t* dst);  // RX loss
int onlp_sfpi_eeprom_read(int port, uint8_t data[256]);    // IDPROM
int onlp_sfpi_dom_read(int port, uint8_t data[256]);       // DOM
int onlp_sfpi_enable_set(int port, int enable);            // TX control
int onlp_sfpi_enable_get(int port, int* enable);
int onlp_sfpi_dev_read(onlp_oid_id_t id, int devaddr,
                       int addr, uint8_t* dst, int len);
int onlp_sfpi_dev_write(onlp_oid_id_t id, int devaddr,
                        int addr, uint8_t* src, int len);
```

---

## 11. LED Control (ledi.c)

### LED IDs

```c
typedef enum onlp_led_id {
    LED_DIAG = 1,    // System diagnostics LED
    LED_FAN  = 2,    // Fan status LED
    LED_LOC  = 3,    // Locator/identify LED
    LED_PSU1 = 4,    // PSU 1 status LED
    LED_PSU2 = 5     // PSU 2 status LED
} onlp_led_id_t;
```

### LED Data Table

```c
typedef struct onlp_led_cpld {
    onlp_led_id_t   lid;
    unsigned char    cpld_offset;
    unsigned char    cpld_mask;
    unsigned char    cpld_val;
    onlp_led_mode_t mode;
} onlp_led_cpld_t;

const onlp_led_cpld_t led_data[] = {
    // PSU1 LED (CPLD 0x13, bits [1:0])
    { LED_PSU1, 0x13, 0x03, 0x03, ONLP_LED_MODE_OFF },
    { LED_PSU1, 0x13, 0x03, 0x02, ONLP_LED_MODE_GREEN },
    { LED_PSU1, 0x13, 0x03, 0x01, ONLP_LED_MODE_ORANGE },

    // PSU2 LED (CPLD 0x13, bits [3:2])
    { LED_PSU2, 0x13, 0x0C, 0x0C, ONLP_LED_MODE_OFF },
    { LED_PSU2, 0x13, 0x0C, 0x08, ONLP_LED_MODE_GREEN },
    { LED_PSU2, 0x13, 0x0C, 0x04, ONLP_LED_MODE_ORANGE },

    // DIAG LED (CPLD 0x13, bits [5:4])
    { LED_DIAG, 0x13, 0x30, 0x00, ONLP_LED_MODE_OFF },
    { LED_DIAG, 0x13, 0x30, 0x20, ONLP_LED_MODE_GREEN },
    { LED_DIAG, 0x13, 0x30, 0x10, ONLP_LED_MODE_ORANGE },

    // FAN LED (CPLD 0x13, bits [7:6])
    { LED_FAN,  0x13, 0xC0, 0xC0, ONLP_LED_MODE_OFF },
    { LED_FAN,  0x13, 0xC0, 0x40, ONLP_LED_MODE_GREEN },
    { LED_FAN,  0x13, 0xC0, 0x80, ONLP_LED_MODE_ORANGE },

    // LOC LED (CPLD 0x15, bits [1:0])
    { LED_LOC,  0x15, 0x03, 0x01, ONLP_LED_MODE_OFF },
    { LED_LOC,  0x15, 0x03, 0x03, ONLP_LED_MODE_ORANGE_BLINKING },
};
```

### LED Control Functions

```c
int onlp_ledi_init(void);
int onlp_ledi_info_get(onlp_oid_t id, onlp_led_info_t* info);
int onlp_ledi_set(onlp_oid_t id, int on_or_off);
int onlp_ledi_mode_set(onlp_oid_t id, onlp_led_mode_t mode);
```

Mode setting: read CPLD register, mask off LED bits, OR in new value, write back.

---

## 12. ONLP API Contracts

### Platform Interface Functions (what platform drivers implement)

Each subsystem has a matching `platformi` interface:

**System** (`onlp/platformi/sysi.h`):
```c
const char* onlp_sysi_platform_get(void);
int onlp_sysi_onie_data_phys_addr_get(void** pa);
int onlp_sysi_oids_get(onlp_oid_t* table, int max);
int onlp_sysi_platform_manage_fans(void);    // Optional thermal policy
int onlp_sysi_platform_manage_leds(void);    // Optional LED policy
```

**SFP** (`onlp/platformi/sfpi.h`):
```c
int onlp_sfpi_sw_init(void);
int onlp_sfpi_bitmap_get(onlp_sfp_bitmap_t* bmap);
int onlp_sfpi_is_present(onlp_oid_id_t id);
int onlp_sfpi_presence_bitmap_get(onlp_sfp_bitmap_t* dst);
int onlp_sfpi_rx_los_bitmap_get(onlp_sfp_bitmap_t* dst);
int onlp_sfpi_dev_read(onlp_oid_id_t id, int devaddr, int addr,
                       uint8_t* dst, int len);
int onlp_sfpi_dev_write(onlp_oid_id_t id, int devaddr, int addr,
                        uint8_t* src, int len);
int onlp_sfpi_control_set(onlp_oid_id_t id, onlp_sfp_control_t ctl, int val);
int onlp_sfpi_control_get(onlp_oid_id_t id, onlp_sfp_control_t ctl, int* val);
int onlp_sfpi_post_insert(onlp_oid_id_t id, sff_info_t* info);  // Optional
```

**Thermal** (`onlp/platformi/thermali.h`):
```c
int onlp_thermali_sw_init(void);
int onlp_thermali_info_get(onlp_oid_id_t id, onlp_thermal_info_t* rv);
```

**Fan** (`onlp/platformi/fani.h`):
```c
int onlp_fani_sw_init(void);
int onlp_fani_info_get(onlp_oid_id_t id, onlp_fan_info_t* rv);
int onlp_fani_rpm_set(onlp_oid_id_t id, int rpm);
int onlp_fani_percentage_set(onlp_oid_id_t id, int p);
int onlp_fani_dir_set(onlp_oid_id_t id, onlp_fan_dir_t dir);
```

**PSU** (`onlp/platformi/psui.h`):
```c
int onlp_psui_sw_init(void);
int onlp_psui_info_get(onlp_oid_id_t id, onlp_psu_info_t* rv);
```

**LED** (`onlp/platformi/ledi.h`):
```c
int onlp_ledi_sw_init(void);
int onlp_ledi_info_get(onlp_oid_id_t id, onlp_led_info_t* rv);
int onlp_ledi_mode_set(onlp_oid_id_t id, onlp_led_mode_t mode);
int onlp_ledi_char_set(onlp_oid_id_t id, char c);
```

### Public API Info Structures

```c
// Thermal
typedef struct onlp_thermal_info_s {
    onlp_oid_hdr_t hdr;
    uint32_t caps;         // GET_TEMPERATURE, GET_WARNING/ERROR/SHUTDOWN_THRESHOLD
    int mcelsius;          // Temperature in millidegrees Celsius
    struct { int warning, error, shutdown; } thresholds;
} onlp_thermal_info_t;

// Fan
typedef struct onlp_fan_info_s {
    onlp_oid_hdr_t hdr;
    onlp_fan_dir_t dir;    // F2B, B2F, UNKNOWN
    uint32_t caps;         // SET/GET_DIR, SET/GET_RPM, SET/GET_PERCENTAGE
    int rpm;
    int percentage;
    char model[64], serial[64];
} onlp_fan_info_t;

// PSU
typedef struct onlp_psu_info_s {
    onlp_oid_hdr_t hdr;
    char model[64], serial[64];
    uint32_t caps;         // AC/DC, GET_VIN/VOUT/IIN/IOUT/PIN/POUT
    onlp_psu_type_t type;
    int mvin, mvout;       // millivolts
    int miin, miout;       // milliamps
    int mpin, mpout;       // milliwatts
} onlp_psu_info_t;

// LED
typedef struct onlp_led_info_s {
    onlp_oid_hdr_t hdr;
    uint32_t caps;         // Supported modes
    onlp_led_mode_t mode;  // OFF, GREEN, ORANGE, BLINKING variants
    char character;
} onlp_led_info_t;

// SFP
typedef struct onlp_sfp_info_s {
    onlp_oid_hdr_t hdr;
    onlp_sfp_type_t type;  // SFP, QSFP, SFP28, QSFP28
    uint32_t controls;
    sff_info_t sff;        // Parsed EEPROM
    sff_dom_info_t dom;    // Digital Optics Monitoring
    struct {
        uint8_t a0[256];   // EEPROM page A0
        uint8_t a2[256];   // EEPROM page A2 (SFP+ DOM)
    } bytes;
} onlp_sfp_info_t;
```

### Status Codes

```c
typedef enum onlp_status {
    ONLP_STATUS_OK         =  0,
    ONLP_STATUS_E_GENERIC  = -1,
    ONLP_STATUS_E_UNSUPPORTED = -2,
    ONLP_STATUS_E_MISSING  = -3,
    ONLP_STATUS_E_INVALID  = -4,
    ONLP_STATUS_E_INTERNAL = -5,
    ONLP_STATUS_E_PARAM    = -6,
    ONLP_STATUS_E_I2C      = -7,
} onlp_status_t;
```

---

## 13. OID Hierarchy

```
CHASSIS (0x01000001)
├── THERMAL  1 (0x03000001)  NE1617A Local
├── THERMAL  2 (0x03000002)  NE1617A Remote
├── THERMAL  3 (0x03000003)  MAX6581 Local
├── THERMAL  4 (0x03000004)  MAX6581 Remote 1
├── THERMAL  5 (0x03000005)  MAX6581 Remote 2
├── THERMAL  6 (0x03000006)  MAX6581 Remote 3
├── THERMAL  7 (0x03000007)  MAX6581 Remote 4
├── THERMAL  8 (0x03000008)  MAX6581 Remote 5
├── THERMAL  9 (0x03000009)  MAX6581 Remote 6
├── THERMAL 10 (0x0300000A)  MAX6581 Remote 7
├── THERMAL 11 (0x0300000B)  BCM56846 ASIC
├── FAN 1      (0x04000001)  Chassis Fan
├── PSU 1      (0x05000001)  Power Supply 1
│   └── THERMAL 12 (0x0300000C)  PSU1 Temperature
├── PSU 2      (0x05000002)  Power Supply 2
│   └── THERMAL 13 (0x0300000D)  PSU2 Temperature
├── LED 1      (0x06000001)  DIAG LED
├── LED 2      (0x06000002)  FAN LED
├── LED 3      (0x06000003)  LOC LED
├── LED 4      (0x06000004)  PSU1 LED
└── LED 5      (0x06000005)  PSU2 LED
```

SFP ports (0x07000001 through 0x07000034) are enumerated separately via
`onlp_sfpi_bitmap_get()`.

---

## 14. Build System

**Makefile paths**:
```
onlp/builds/lib/Makefile        — ONLP shared library
onlp/builds/onlpdump/Makefile   — onlpdump diagnostic utility
onlp/builds/src/Makefile         — Source module compilation
platform-config/r0/builds/Makefile    — Platform config
platform-config/r0/builds/dtb/Makefile — Device tree blob
```

**ONLP common framework location**:
```
packages/base/any/onlp/src/onlp/module/       — Core ONLP framework
packages/base/any/onlp/src/onlplib/module/     — Utility library (I2C, file, mmap)
```

**Key framework headers**:
```
onlp/module/inc/onlp/onlp.h          — Core API, status codes
onlp/module/inc/onlp/oids.h          — OID system
onlp/module/inc/onlp/sfp.h           — SFP public API
onlp/module/inc/onlp/fan.h           — Fan public API
onlp/module/inc/onlp/thermal.h       — Thermal public API
onlp/module/inc/onlp/psu.h           — PSU public API
onlp/module/inc/onlp/led.h           — LED public API
onlp/module/inc/onlp/platformi/*.h   — Platform interface contracts
```

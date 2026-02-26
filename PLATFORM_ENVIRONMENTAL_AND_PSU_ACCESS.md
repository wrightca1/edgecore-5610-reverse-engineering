# Platform Environmental, PSU, and Low-Level Access

**Date**: February 15, 2026  
**Platform**: Accton AS5610-52X (Edgecore AS5610-52X)  
**Source**: Cumulus accton.py, rc.soc, PORT_BRINGUP_STATUS

---

## Summary: What We Have vs What’s Missing

| Component | Documented | Access Path | Notes |
|-----------|------------|-------------|-------|
| **ASIC** | ✅ | PCI BAR0, BDE | See ASIC_INIT_AND_DMA_MAP.md |
| **S-Channel / DMA** | ✅ | Registers 0x32800, 0x31158 | See SCHAN_AND_RING_BUFFERS.md |
| **CPLD** | ✅ | sysfs | LEDs, PSU, fan status, PWM |
| **Temperature** | ✅ | sysfs (hwmon, I2C) | Multiple sensors |
| **Fans** | ✅ | CPLD hwmon | Status + PWM via CPLD |
| **PSU** | ✅ | CPLD hwmon | psu_pwr1, psu_pwr2 |
| **GPIO** | ✅ | sysfs | mb_led_rst |
| **I2C** | ✅ | sysfs, rc.soc | SFP I2C topology verified; see SFP_TURNUP_AND_ACCESS.md |
| **SFP/QSFP** | ✅ | ethtool -m, sfptab, eeprom_dev | See SFP_TURNUP_AND_ACCESS.md |

---

## 1. CPLD (Complex Programmable Logic Device)

**Path**: `/sys/devices/ff705000.localbus/ea000000.cpld`

Used for:
- PSU presence/power status (`psu_pwr1`, `psu_pwr2`)
- Fan status (`system_fan`)
- Fan PWM control
- Status LEDs (`led_psu1`, `led_psu2`, `led_fan`, `led_diag`)

**Access**: Standard Linux hwmon/sysfs under that device.

---

## 2. Temperature Sensors (AS5610-52X)

From Cumulus `accton.py`:

| Sensor | Description | driver_path | driver_hwmon |
|--------|-------------|-------------|--------------|
| **Temp1** | MAC die (ASIC) | `/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0` | temp1 |
| **Temp2** | Board | `.../soc.0/ff703000.i2c/i2c-0/i2c-9/9-004d` | temp1 |
| **Temp3** | Board | same | temp2 |
| **Temp4** | Board | same | temp3 |
| **Temp5** | Board | same | temp4 |
| **Temp6** | Board | same | temp5 |
| **Temp7** | Board | same | temp6 |
| **Temp8** | Board | same | temp7 |
| **Temp9** | NE1617A | `.../i2c-9/9-0018` | temp1 |
| **Temp10** | MAC board | `.../i2c-9/9-0018` | temp2 |

**Read example**:
```bash
cat /sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0/hwmon/hwmon*/temp1_input   # ASIC temp (millideg C)
cat /sys/class/hwmon/hwmon*/temp*_input
```

---

## 3. Fans

**Status**: CPLD hwmon `system_fan`  
**PWM control**: `/sys/devices/ff705000.localbus/ea000000.cpld` (PWM sysfs under CPLD)

```bash
# Fan speed (RPM)
cat /sys/class/hwmon/hwmon*/fan*_input

# PWM (if exposed)
cat /sys/class/hwmon/hwmon*/pwm*
```

---

## 4. PSUs (Power Supply Units)

**Status**: CPLD hwmon `psu_pwr1`, `psu_pwr2`

```bash
# PSU status (OK/ABSENT/BAD - platform-specific)
cat /sys/class/hwmon/hwmon*/power*_input   # If exposed
# Or via platform-specific paths under CPLD
```

Cumulus `PSU_Unit` uses `cpld_hwmon` – actual sysfs layout depends on the CPLD driver.

---

## 5. GPIO

**rc.soc**:
```
/sys/class/gpio/mb_led_rst/value   # 0 then 1 to reset port LEDs
```

```bash
# Export (if not auto-exported)
echo <gpio_num> > /sys/class/gpio/export
# Read/write
cat /sys/class/gpio/gpio<N>/value
echo 1 > /sys/class/gpio/gpio<N>/value
```

---

## 6. I2C

### From rc.soc
- `/sys/devices/pci0000:00/0000:00:1f.3/i2c-0/0-003a/qsfp_led_mode` – QSFP LED mode (0x3a on i2c-0), write 255

### I2C Topology (AS5610-52X, PowerPC)

- **i2c-0**: PCI 00:1f.3 (SMBus) – base bus  
- **i2c-9**: Mux channel from i2c-0 (e.g. `ff703000.i2c`)  
  - 9-0018: NE1617A temp  
  - 9-004d: LM75-style temp (multi-channel)  
  - 9-003a: QSFP LED (rc.soc)

### SFP/QSFP I2C Buses (PORT_BRINGUP_STATUS)

Expected but not present when only base drivers load:
- **i2c-22 to i2c-69**: SFP ports 1–48 (one bus per port)
- **i2c-70 to i2c-73**: QSFP ports 49–52

**Cause**: Platform I2C mux drivers for SFP/QSFP not loaded. Need platform DTS/modules (e.g. ONLP or Cumulus platform modules).

**Manual check**:
```bash
ls /sys/bus/i2c/devices/
i2cdetect -y 0
i2cdetect -y 9
```

---

## 7. SFP/QSFP Module Access

**When I2C works**:
- SFP EEPROM: typically `i2c-N` with N = 22+port for SFP, 70+ for QSFP
- Address: 0x50 (data), 0x51 (optional)

**Via ethtool** (uses kernel SFP support, depends on port/netdev):
```bash
sudo ethtool -m swp1    # Module info, DDM, temp, power
```

**Direct I2C** (if bus exists):
```bash
i2cdump -y 22 0x50     # SFP port 1 EEPROM
```

---

## 8. LED Control

**rc.soc**:
1. GPIO `mb_led_rst`: 0 → sleep 1 → 1 (reset port LEDs)
2. `0-003a/qsfp_led_mode`: 255 (QSFP LED mode)

**Trident port LEDs**: Controlled by ASIC/switchd (rc.led), not direct sysfs.

**Status LEDs**: Via CPLD (`led_psu1`, `led_psu2`, `led_fan`, `led_diag`) – paths under CPLD sysfs.

---

## 9. Platform Init (rc.soc)

```bash
# LED reset
echo 0 > /sys/class/gpio/mb_led_rst/value
sleep 1
echo 1 > /sys/class/gpio/mb_led_rst/value

# QSFP LED mode
echo 255 > /sys/devices/pci0000:00/0000:00:1f.3/i2c-0/0-003a/qsfp_led_mode
```

---

## 10. Gaps and Next Steps

### Verified (Section 11)
- CPLD sysfs layout – all attributes documented
- Temperature paths – 10 sensors confirmed
- I2C buses – i2c-0..i2c-69 present on Cumulus

### Still Missing / Incomplete
1. **mb_led_rst GPIO** – rc.soc references it; not found under `/sys/class/gpio/` on live switch
2. **PSU PMBus/I2C** – PSUs may have direct I2C; not yet mapped for AS5610
3. **CPLD register map** – raw register offsets if bypassing sysfs
4. **Fan RPM** – CPLD exposes status and PWM, not RPM

### How to Probe on Live Switch
```bash
# Temperature
find /sys -name "temp*_input" 2>/dev/null

# Fans
find /sys -name "fan*_input" 2>/dev/null

# PSU
find /sys -name "*psu*" -o -name "*power*" 2>/dev/null

# I2C
ls -la /sys/bus/i2c/devices/
i2cdetect -l

# GPIO
ls /sys/class/gpio/
cat /sys/kernel/debug/gpio   # If debugfs mounted

# CPLD
find /sys -path "*cpld*" 2>/dev/null
```

---

## 11. Verified on Cumulus Switch (<LIVE_SWITCH_IP>)

Live probe on Cumulus AS5610-52X:

### CPLD Path
```
/sys/devices/ff705000.localbus/ea000000.cpld
```
Driver: `accton_as5610_52x_cpld`

### CPLD Attributes (verified)
| Attribute | Type | Sample Value |
|-----------|------|--------------|
| psu_pwr1_present | R | 1 |
| psu_pwr2_present | R | 1 |
| psu_pwr1_dc_ok, psu_pwr2_dc_ok | R | — |
| psu_pwr1_all_ok, psu_pwr2_all_ok | R | — |
| system_fan_ok | R | 1 |
| system_fan_present | R | — |
| system_fan_air_flow | R | front-to-back |
| system_dc_power_ok | R | 0 |
| pwm1 | R/W | 64 (0–248) |
| board_revision | R | 0.2:7-eng |
| led_psu1, led_psu2 | R/W | green, yellow, off |
| led_diag, led_fan, led_locator | R/W | — |
| watch_dog_enable, watch_dog_timeout, watch_dog_keep_alive | R/W | — |

### Temperature Paths (verified)
```
/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0/temp1_input  # ASIC (25722 = 25.7°C)
/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-004d/temp1..temp7_input
/sys/devices/soc.0/ff703000.i2c/i2c-0/i2c-9/9-0018/temp1_input, temp2_input
```

### Fans
- No `fan*_input` – CPLD does not expose RPM; status via `system_fan_ok`, PWM via `pwm1` (0–248).

### I2C Buses (verified)
- **i2c-0 through i2c-69** – all 70 buses present.
- **SFP ports**: i2c-22..i2c-69 (0x50, 0x51 EEPROM; 0x27 presence/control).
- **QSFP ports**: similar mapping.
- **Temp sensors**: i2c-9 (mux) – 9-0018 (NE1617A), 9-004d (LM75-style multi-channel).

### GPIO
- pca9506 (base 24, 64, 104, 176, 216), pca9538 (base 144, 152, 160, 168).
- `mb_led_rst` not found under `/sys/class/gpio/` – may be platform-init symlink or different Cumulus version.

---

## 12. References

- `cumulus/extracted/sysroot/usr/lib/python2.7/dist-packages/cumulus/platforms/accton.py` – AcctonAS5610_52X sensors, PSU, fan, temp, CPLD
- `cumulus/extracted/etc/bcm.d/rc.soc` – GPIO, I2C init
- `previous_findings/PORT_BRINGUP_STATUS.md` – I2C bus gap (22–73)
- `docs/reverse-engineering/ASIC_INIT_AND_DMA_MAP.md` – ASIC, DMA
- `docs/reverse-engineering/SCHAN_AND_RING_BUFFERS.md` – S-Channel, DMA registers
- `docs/reverse-engineering/VERSIONS_AND_BUILD_INFO.md` – OS, packages, libraries, build toolchain

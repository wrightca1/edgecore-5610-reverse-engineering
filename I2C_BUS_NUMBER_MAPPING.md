# I2C Bus Number Mapping: Cumulus vs EdgeNOS

## Why They're Different

Cumulus Linux (kernel 3.2) and EdgeNOS (kernel 5.10) enumerate I2C mux children
in different order:

- **Cumulus 3.2**: Breadth-first — all level-1 mux channels get bus numbers first,
  then level-2 sub-mux channels get the next block of numbers.
- **EdgeNOS 5.10**: Depth-first — when a mux channel is registered, its sub-mux
  children are immediately probed and assigned the next bus numbers before moving
  to the next sibling channel.

This means **every I2C bus number above 10 is different** between the two systems.
Any code or script that uses hardcoded bus numbers must be updated.

## Root Controllers (same on both)

| Bus | Controller | Purpose |
|-----|-----------|---------|
| 0   | MPC I2C @ 0xff703000 | System I2C (EEPROM, RTC, sensors) |
| 1   | MPC I2C @ 0xff703100 | Port I2C (SFP, QSFP, retimer, GPIO) |

## Level 1 Muxes off Bus 0 (same on both)

Bus 0 → PCA9548 @ 0x70, 8 channels → buses 2-9

| Chan | Bus | Purpose | Same? |
|------|-----|---------|-------|
| 0    | 2   | Board EEPROM (0x51) | Yes |
| 1    | 3   | RTC (0x3a) | Yes |
| 2    | 4   | Sensors (0x39) | Yes |
| 3-6  | 5-8 | (unused) | Yes |
| 7    | 9   | Temp sensors (MAX6697 0x18, MAX1617 0x4d) | Yes |

## Level 1 Muxes off Bus 1 (numbering diverges here)

Bus 1 has three PCA9546 muxes (4-channel each): 0x75, 0x76, 0x77

### Mux 0x75 (SFP groups 1-4, each with PCA9548 sub-mux @ 0x74)

| Chan | Cumulus Bus | EdgeNOS Bus | Sub-mux children |
|------|-----------|------------|-----------------|
| 0    | 10        | **10**     | Cumulus: 22-29, EdgeNOS: **11-18** |
| 1    | 11        | **19**     | Cumulus: 30-37, EdgeNOS: **20-27** |
| 2    | 12        | **28**     | Cumulus: 38-45, EdgeNOS: **29-36** |
| 3    | 13        | **37**     | Cumulus: 46-53, EdgeNOS: **38-45** |

### Mux 0x76 (SFP groups 5-6 + GPIO)

| Chan | Cumulus Bus | EdgeNOS Bus | Sub-mux children |
|------|-----------|------------|-----------------|
| 0    | 14        | **46**     | Cumulus: 54-61, EdgeNOS: **47-54** |
| 1    | 15        | **55**     | Cumulus: 62-69, EdgeNOS: **56-63** |
| 2    | 16        | **64**     | GPIO expanders (0x20, 0x21, 0x70-0x73) |
| 3    | 17        | **65**     | GPIO expanders (0x20, 0x23, 0x24) |

### Mux 0x77 (QSFP ports 49-52)

| Chan | Cumulus Bus | EdgeNOS Bus | Devices |
|------|-----------|------------|---------|
| 0    | 18        | **66**     | QSFP49: retimer 0x27, EEPROM 0x50 |
| 1    | 19        | **67**     | QSFP50: retimer 0x27, EEPROM 0x50 |
| 2    | 20        | **68**     | QSFP51: retimer 0x27, EEPROM 0x50 |
| 3    | 21        | **69**     | QSFP52: retimer 0x27, EEPROM 0x50 |

## Per-Port SFP Bus Mapping

### SFP Group 1 (swp1-8): sub-mux on Cumulus bus 10 / EdgeNOS bus 10

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp1 | 0    | 22        | **11**     | Yes (0x27) |
| swp2 | 1    | 23        | **12**     | Yes |
| swp3 | 2    | 24        | **13**     | Yes |
| swp4 | 3    | 25        | **14**     | Yes |
| swp5 | 4    | 26        | **15**     | No |
| swp6 | 5    | 27        | **16**     | No |
| swp7 | 6    | 28        | **17**     | No |
| swp8 | 7    | 29        | **18**     | No |

### SFP Group 2 (swp9-16): sub-mux on Cumulus bus 11 / EdgeNOS bus 19

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp9  | 0   | 30        | **20**     | Yes |
| swp10 | 1   | 31        | **21**     | Yes |
| swp11 | 2   | 32        | **22**     | Yes |
| swp12 | 3   | 33        | **23**     | Yes |
| swp13 | 4   | 34        | **24**     | No |
| swp14 | 5   | 35        | **25**     | No |
| swp15 | 6   | 36        | **26**     | No |
| swp16 | 7   | 37        | **27**     | No |

### SFP Group 3 (swp17-24): sub-mux on Cumulus bus 12 / EdgeNOS bus 28

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp17 | 0   | 38        | **29**     | Yes |
| swp18 | 1   | 39        | **30**     | Yes |
| swp19 | 2   | 40        | **31**     | Yes |
| swp20 | 3   | 41        | **32**     | Yes |
| swp21 | 4   | 42        | **33**     | No |
| swp22 | 5   | 43        | **34**     | No |
| swp23 | 6   | 44        | **35**     | No |
| swp24 | 7   | 45        | **36**     | No |

### SFP Group 4 (swp25-32): sub-mux on Cumulus bus 13 / EdgeNOS bus 37

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp25 | 0   | 46        | **38**     | Yes |
| swp26 | 1   | 47        | **39**     | Yes |
| swp27 | 2   | 48        | **40**     | Yes |
| swp28 | 3   | 49        | **41**     | Yes |
| swp29 | 4   | 50        | **42**     | No |
| swp30 | 5   | 51        | **43**     | No |
| swp31 | 6   | 52        | **44**     | No |
| swp32 | 7   | 53        | **45**     | No |

### SFP Group 5 (swp33-40): sub-mux on Cumulus bus 14 / EdgeNOS bus 46

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp33 | 0   | 54        | **47**     | Yes |
| swp34 | 1   | 55        | **48**     | Yes |
| swp35 | 2   | 56        | **49**     | Yes |
| swp36 | 3   | 57        | **50**     | Yes |
| swp37 | 4   | 58        | **51**     | No |
| swp38 | 5   | 59        | **52**     | No |
| swp39 | 6   | 60        | **53**     | No |
| swp40 | 7   | 61        | **54**     | No |

### SFP Group 6 (swp41-48): sub-mux on Cumulus bus 15 / EdgeNOS bus 55

| Port | Chan | Cumulus Bus | EdgeNOS Bus | Retimer? |
|------|------|-----------|------------|----------|
| swp41 | 0   | 62        | **56**     | Yes |
| swp42 | 1   | 63        | **57**     | Yes |
| swp43 | 2   | 64        | **58**     | Yes |
| swp44 | 3   | 65        | **59**     | Yes |
| swp45 | 4   | 66        | **60**     | Yes |
| swp46 | 5   | 67        | **61**     | Yes |
| swp47 | 6   | 68        | **62**     | Yes |
| swp48 | 7   | 69        | **63**     | Yes |

## GPIO Expanders

| Device | Cumulus Bus | EdgeNOS Bus | Address |
|--------|-----------|------------|---------|
| PCA9506 (SFP TX_DIS 1-40) | 16 | **64** | 0x20 |
| PCA9506 (SFP TX_DIS 41-48) | 16 | **64** | 0x21 |
| PCA9548 mux | 16 | **64** | 0x70-0x73 |
| PCA9506 GPIO | 17 | **65** | 0x20 |
| PCA9538 GPIO | 17 | **65** | 0x23, 0x24 |

## Code That Needs Updating

1. **`newnos/asic/switchd/portmap.c`** — `port_to_i2c_bus[]` array uses Cumulus numbers
2. **`newnos/config/rootfs/overlay/usr/sbin/platform-init.sh`** — retimer init bus list
3. **`newnos/config/rootfs/overlay/usr/sbin/sfp-enable.sh`** — SFP enable bus references

## How to Make This Stable

Instead of hardcoding bus numbers, use sysfs device paths which are stable:
```
/sys/bus/i2c/devices/1-0075/     → mux 0x75 on bus 1
/sys/bus/i2c/devices/10-0074/    → sub-mux 0x74 on bus 10
/sys/bus/i2c/devices/11-0050/    → SFP EEPROM on bus 11 (swp1)
```

Or discover bus numbers at runtime by walking the mux topology:
```bash
# Find bus number for a given mux path
find /sys/bus/i2c/devices -name "10-0074" -exec cat {}/channel-0/name \;
```

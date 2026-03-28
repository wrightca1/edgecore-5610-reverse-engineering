# AS5610-52X Complete I2C Hardware Inventory (from Cumulus 2.5.1)

Captured March 27, 2026 from live Cumulus system at 10.1.1.242.

## I2C Bus Topology

### Root Controllers
| Bus | Controller | MMIO Address |
|-----|-----------|-------------|
| 0   | MPC I2C   | 0xff703000  |
| 1   | MPC I2C   | 0xff703100  |

### Level 1 Muxes (off root buses)

**Bus 0 → PCA9548 @ 0x70** (8-channel mux):
| Chan | Bus | Purpose |
|------|-----|---------|
| 0    | 2   | Board EEPROM |
| 1    | 3   | Power / PSU |
| 2    | 4   | Sensors / CPLD |
| 3    | 5   | (unused?) |
| 4    | 6   | (unused?) |
| 5    | 7   | (unused?) |
| 6    | 8   | (unused?) |
| 7    | 9   | Temp sensors |

**Bus 1 → Three PCA9548 muxes @ 0x75, 0x76, 0x77**:

Mux @ 0x75 (4 channels used):
| Chan | Bus | Purpose |
|------|-----|---------|
| 0    | 10  | SFP group 1 sub-mux (ports 1-8) |
| 1    | 11  | SFP group 2 sub-mux (ports 9-16) |
| 2    | 12  | SFP group 3 sub-mux (ports 17-24) |
| 3    | 13  | SFP group 4 sub-mux (ports 25-32) |

Mux @ 0x76 (4 channels used):
| Chan | Bus | Purpose |
|------|-----|---------|
| 0    | 14  | SFP group 5 sub-mux (ports 33-40) |
| 1    | 15  | SFP group 6 sub-mux (ports 41-48) |
| 2    | 16  | GPIO expanders |
| 3    | 17  | GPIO expanders + PSU |

Mux @ 0x77 (4 channels used):
| Chan | Bus | Purpose |
|------|-----|---------|
| 0    | 18  | QSFP port 49 (retimer + EEPROM) |
| 1    | 19  | QSFP port 50 (retimer + EEPROM) |
| 2    | 20  | QSFP port 51 (retimer + EEPROM) |
| 3    | 21  | QSFP port 52 (retimer + EEPROM) |

### Level 2 Muxes (off level 1)

Each SFP group bus (10-15) has a **PCA9548 @ 0x74** (8-channel sub-mux):

**Bus 10 (SFP group 1) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 22  | swp1 | 0x27 (retimer), 0x50 (SFP EEPROM), 0x51 (SFP DOM) |
| 1    | 23  | swp2 | 0x27, 0x50, 0x51 |
| 2    | 24  | swp3 | 0x27, 0x50, 0x51 |
| 3    | 25  | swp4 | 0x27, 0x50, 0x51 |
| 4    | 26  | swp5 | 0x50, 0x51 (no retimer) |
| 5    | 27  | swp6 | 0x50, 0x51 (no retimer) |
| 6    | 28  | swp7 | 0x50, 0x51 (no retimer) |
| 7    | 29  | swp8 | 0x50, 0x51 (no retimer) |

**Bus 11 (SFP group 2) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 30  | swp9  | 0x27, 0x50, 0x51 |
| 1    | 31  | swp10 | 0x27, 0x50, 0x51 |
| 2    | 32  | swp11 | 0x27, 0x50, 0x51 |
| 3    | 33  | swp12 | 0x27, 0x50, 0x51 |
| 4    | 34  | swp13 | 0x50, 0x51 |
| 5    | 35  | swp14 | 0x50, 0x51 |
| 6    | 36  | swp15 | 0x50, 0x51 |
| 7    | 37  | swp16 | 0x50, 0x51 |

**Bus 12 (SFP group 3) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 38  | swp17 | 0x27, 0x50, 0x51 |
| 1    | 39  | swp18 | 0x27, 0x50, 0x51 |
| 2    | 40  | swp19 | 0x27, 0x50, 0x51 |
| 3    | 41  | swp20 | 0x27, 0x50, 0x51 |
| 4    | 42  | swp21 | 0x50, 0x51 |
| 5    | 43  | swp22 | 0x50, 0x51 |
| 6    | 44  | swp23 | 0x50, 0x51 |
| 7    | 45  | swp24 | 0x50, 0x51 |

**Bus 13 (SFP group 4) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 46  | swp25 | 0x27, 0x50, 0x51 |
| 1    | 47  | swp26 | 0x27, 0x50, 0x51 |
| 2    | 48  | swp27 | 0x27, 0x50, 0x51 |
| 3    | 49  | swp28 | 0x27, 0x50, 0x51 |
| 4    | 50  | swp29 | 0x50, 0x51 |
| 5    | 51  | swp30 | 0x50, 0x51 |
| 6    | 52  | swp31 | 0x50, 0x51 |
| 7    | 53  | swp32 | 0x50, 0x51 |

**Bus 14 (SFP group 5) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 54  | swp33 | 0x27, 0x50, 0x51 |
| 1    | 55  | swp34 | 0x27, 0x50, 0x51 |
| 2    | 56  | swp35 | 0x27, 0x50, 0x51 |
| 3    | 57  | swp36 | 0x27, 0x50, 0x51 |
| 4    | 58  | swp37 | 0x50, 0x51 |
| 5    | 59  | swp38 | 0x50, 0x51 |
| 6    | 60  | swp39 | 0x50, 0x51 |
| 7    | 61  | swp40 | 0x50, 0x51 |

**Bus 15 (SFP group 6) → sub-mux @ 0x74**:
| Chan | Bus | Port | Devices |
|------|-----|------|---------|
| 0    | 62  | swp41 | 0x27, 0x50, 0x51 |
| 1    | 63  | swp42 | 0x27, 0x50, 0x51 |
| 2    | 64  | swp43 | 0x27, 0x50, 0x51 |
| 3    | 65  | swp44 | 0x27, 0x50, 0x51 |
| 4    | 66  | swp45 | 0x27, 0x50, 0x51 |
| 5    | 67  | swp46 | 0x27, 0x50, 0x51 |
| 6    | 68  | swp47 | 0x27, 0x50, 0x51 |
| 7    | 69  | swp48 | 0x27, 0x50, 0x51 |

## Device Address Summary

| Address | Device | Count | Location |
|---------|--------|-------|----------|
| 0x0070  | PCA9548 mux | 1 | Bus 0 (root mux) |
| 0x0074  | PCA9548 mux | 6 | Buses 10-15 (SFP sub-muxes) |
| 0x0075  | PCA9548 mux | 1 | Bus 1 (level 1 mux) |
| 0x0076  | PCA9548 mux | 1 | Bus 1 (level 1 mux) |
| 0x0077  | PCA9548 mux | 1 | Bus 1 (level 1 mux) |
| 0x0070-73 | PCA9548 mux | 4 | Bus 16 (GPIO sub-muxes) |
| 0x0018  | MAX6697 temp | 1 | Bus 9 |
| 0x003a  | PCF8563 RTC | 1 | Bus 3 |
| 0x003e  | (unknown) | 1 | Bus 3 |
| 0x003d  | (unknown) | 1 | Bus 4 |
| 0x0039  | (unknown) | 1 | Bus 4 |
| 0x000c  | (unknown) | 1 | Bus 4 |
| 0x0020  | PCA9506 GPIO | 2 | Buses 16, 17 |
| 0x0021  | PCA9506 GPIO | 1 | Bus 16 |
| 0x0023  | PCA9538 GPIO | 1 | Bus 17 |
| 0x0024  | PCA9538 GPIO | 1 | Bus 17 |
| 0x0027  | DS100DF410 retimer | 32 | See below |
| 0x004d  | MAX1617 temp | 1 | Bus 9 |
| 0x0050  | SFP/QSFP EEPROM | 52 | Buses 18-69 (one per port) |
| 0x0051  | SFP/QSFP DOM | 48 | Buses 22-69 (SFP ports) |
| 0x0051  | Board EEPROM | 1 | Bus 2 |
| 0x0078  | (unknown, high addr) | 2 | Buses 3, 4 |

## Retimer (DS100DF410) Mapping

**Pattern**: First 4 ports in each SFP group of 8 have retimers. Last 4 don't.

| Port Group | Retimer Buses | No-Retimer Buses |
|-----------|--------------|-----------------|
| swp1-8    | 22,23,24,25  | 26,27,28,29     |
| swp9-16   | 30,31,32,33  | 34,35,36,37     |
| swp17-24  | 38,39,40,41  | 42,43,44,45     |
| swp25-32  | 46,47,48,49  | 50,51,52,53     |
| swp33-40  | 54,55,56,57  | 58,59,60,61     |
| swp41-48  | 62,63,64,65,66,67,68,69 | (all have retimers) |
| swp49-52  | 18,19,20,21  | (all have retimers, QSFP) |

Total retimers: 32 (24 SFP + 4 QSFP + 4 extra in group 6)

## Comparison with EdgeNOS portmap.c

EdgeNOS `port_to_i2c_bus[]` currently maps:
- swp1 → bus 22, swp2 → bus 23, ... swp8 → bus 29 (**matches Cumulus**)
- swp49 → bus 18, swp50 → bus 19, swp51 → bus 20, swp52 → bus 21 (**matches Cumulus**)

**Port-to-bus mapping is correct** in our code.

## Management MAC

eth0 MAC: `80:a2:35:81:ca:ae` (management port, base MAC for the switch)

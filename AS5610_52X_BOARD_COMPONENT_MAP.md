# AS5610-52X Board Component Map

> Physical chip inventory, markings, and board locations from visual PCB inspection.
> Cross-references software/driver mappings from Cumulus Linux and ONL.

---

## CPU Area

| Chip | Part Number | Package | Marking | Function |
|------|-------------|---------|---------|----------|
| P2020 SoC | Freescale P2020 | BGA | — | Dual-core PowerPC e500 CPU |
| Mgmt PHY | Broadcom BCM54610C1KFBG | BGA | — | GbE PHY, RGMII to eTSEC, near mgmt RJ-45 |
| CPLD | Altera EPM570T144C5N | TQFP-144 | — | MAX II CPLD, 570 LEs, speed grade C5 |
| NOR Flash | Spansion S29GL064N90TFI01 | TSOP-56 | — | 64 Mbit (8 MB), 90ns, boot storage (U-Boot + ONIE) |
| NAND Flash | Toshiba TC58NVG5H2HTA00 | TSOP-48 | — | 32 Gbit (4 GB), MLC, OS storage |
| Bus Buffer | SN74LVC244A (×2) | — | — | Octal buffer/line driver, 3-state outputs |
| Bus Mux | SN74LVC257A | — | CL257 / 88K G4 / AH05 | Quad 2:1 mux, 3-state outputs |

### CPLD (Altera EPM570T144C5N)

Memory-mapped at **0xEA000000** via P2020 eLBC chip-select 1 (256 bytes).
Kernel module: `accton_as5610_52x_cpld`
Sysfs: `/sys/devices/ff705000.localbus/ea000000.cpld`

Functions:
- PSU status monitoring (regs 0x01-0x02)
- System power/fan status (reg 0x03)
- SFP/QSFP interrupt status (reg 0x05)
- Fan PWM speed control (reg 0x0D, 5-bit)
- Watchdog timer (reg 0x0E)
- Over-temperature protection (reg 0x0F)
- BCM56846 + peripheral reset control (regs 0x10-0x11)
- System LEDs: FAN, DIAG, PSU1, PSU2 (reg 0x13)
- Voltage margining control (regs 0x0A-0x0B)
- Interrupt mask (reg 0x12)

### NOR Flash (Spansion S29GL064N90TFI01)

Memory-mapped at **0xEFC00000** via P2020 eLBC chip-select 0.

| Parameter | Value |
|-----------|-------|
| Capacity | 64 Mbit (8 MB) |
| Sector Size | 128 KB uniform |
| Access Time | 90 ns |
| Interface | CFI (Common Flash Interface) |
| Temp Range | Industrial (-40 to +85°C) |
| Boot Block | Top boot |

Note: Software/DTS maps only 4 MB (0xEFC00000-0xEFFFFFFF). The chip is 8 MB —
upper region may be used by ONIE/U-Boot for redundancy or may be unmapped.

Flash layout (from DTS, 4 MB mapped region):
```
0x000000 - 0x35FFFF  onie        (3.375 MB)
0x360000 - 0x36FFFF  uboot-env   (64 KB)
0x370000 - 0x37FFFF  board_eeprom (64 KB)
0x380000 - 0x3FFFFF  uboot       (512 KB)
```

### Internal USB Flash Drive (Toshiba NAND + Phison Controller)

The Toshiba NAND and Phison PS2251-67 are located together on the board and
form an **on-board USB flash drive**. This is the primary NOS storage — ONIE
installs Cumulus/ONL/etc. to this device.

| Parameter | Value |
|-----------|-------|
| NAND | Toshiba TC58NVG5H2HTA00 |
| Capacity | 32 Gbit (4 GB) |
| Type | MLC NAND |
| Controller | Phison PS2251-67-5 (USB 2.0) |
| Interface | NAND → Phison → USB2513i hub → P2020 USB |

**Boot flow:**
```
NOR Flash (Spansion, 8 MB)          Internal USB Drive (Toshiba+Phison, 4 GB)
┌─────────────────────┐             ┌─────────────────────┐
│ U-Boot (512 KB)     │ ──────────► │ NOS partition(s)    │
│ ONIE  (3.375 MB)    │  USB boot   │ Cumulus / ONL / etc │
│ Board EEPROM (64 KB)│             │ Config, logs        │
└─────────────────────┘             └─────────────────────┘
```

### eLBC Bus Glue Logic

**2× SN74LVC244A** (octal buffer/line driver) near the CPLD. Buffer the eLBC
bus signals between the P2020 CPU and the CPLD — likely the 8-bit data bus +
address/control lines (CS, OE, WE). Provides voltage level matching and drive
strength isolation for the memory-mapped CPLD interface.

**1× SN74LVC257A** (quad 2:1 mux) near the CPLD. Multiplexes shared eLBC
signals between the NOR flash (CS0 @ 0xEFC00000) and CPLD (CS1 @ 0xEA000000),
switched by chip-select lines.

### Management PHY (Broadcom BCM54610C1KFBG)

Located near the management RJ-45 port. Single-port 10/100/1000BASE-T PHY.

| Parameter | Value |
|-----------|-------|
| Interface | RGMII to P2020 eTSEC (@ 0x24000) |
| MDIO Address | 0x01 |
| MDIO Bus | gianfar (@ 0x24520) |

Note: Some documentation references BCM5482S (dual-port) as the management PHY,
but board inspection confirms BCM54610C (single-port).

---

## SFP/QSFP Port Area

### I2C Mux ICs

| Chip | Qty | Address | Location | Function |
|------|-----|---------|----------|----------|
| PCA9546 | 3 | 0x75, 0x76, 0x77 | Near SFP/QSFP cages | 4-ch I2C mux (top-level, deselect-on-exit) |
| PCA9548 | 6 | All 0x74 | Near SFP cages | 8-ch I2C mux (per port-group, behind PCA9546) |
| PCA9548 | 1 | 0x70 | Near CPU | 8-ch management bus mux |

### GPIO Expanders

| Chip | Qty | Marking | Location | Function |
|------|-----|---------|----------|----------|
| PCA9506D | 6 | — | Near SFP cages | 40-bit GPIO: SFP present/fault/LOS/TX_DISABLE/rate select |
| PCA9538 (TI) | 2 | PD538 / 88K 04 / C020 | Near QSFP cages | QSFP RST_L, LPMODE, MODSEL_L, INT |
| PCA9538 (TI) | 2 | PD538 / 88K 04 / C020 | Near SFP ports 40-48 | SFP 40-47 rate select + misc GPIO |

Note: Software enumerates 7 PCA9506 addresses (0x20-0x24 across buses 16-17).
6 confirmed near SFP cages; 7th may be elsewhere on the board.

### Retimer ICs

| Chip | Qty | Address | Location | Function |
|------|-----|---------|----------|----------|
| TI DS100DF410 | 8 | All 0x27 | Along SFP/QSFP trace paths | Quad-channel 10G retimer/equalizer |

See `I2C_BUS_TOPOLOGY_AND_SFP_CONTROL.md` for full retimer register map and
initialization details.

---

## Management Bus Area

| Chip | Address | Bus | Location | Function |
|------|---------|-----|----------|----------|
| Epson RTC8564 | 0x51 | i2c-2 | — | Real-time clock |
| SMSC USB2513i | 0x2C | i2c-6 | — | USB hub |
| VT1165M | 0x71 | i2c-7 | — | Voltage margining monitor |
| ICS83905I | 0x6E | i2c-8 | — | PCIe clock buffer |
| MAX6697/MAX6581 | 0x4D | i2c-9 | — | 7-ch remote temperature sensor |
| NE1617A/MAX1617 | 0x18 | i2c-9 | — | 2-ch temperature sensor |

---

## USB Storage

| Chip | Part Number | Function |
|------|-------------|----------|
| USB Flash Controller | Phison PS2251-67-5 | USB-to-NAND flash controller |

The Phison PS2251-67 is a USB 2.0 flash drive controller. Paired with the
Toshiba TC58NVG5H2HTA00 NAND (physically adjacent), it presents as an internal
USB mass storage device to the P2020 via the SMSC USB2513i hub on the management
bus. This is the primary NOS storage — ONIE installs the operating system here.

---

## Switch ASIC

| Chip | Part Number | Interface | Function |
|------|-------------|-----------|----------|
| BCM56846 | Broadcom BCM56846_A1 (Trident+) | PCIe BAR0 @ 0xA0000000 | 640 Gbps switching ASIC |

Sysfs: `/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0`
PCI Device ID: `0x14e4:0xb846`

---

## Complete Physical Chip Summary

| Category | Chip | Quantity |
|----------|------|----------|
| CPU | Freescale P2020 | 1 |
| Switch ASIC | Broadcom BCM56846 | 1 |
| CPLD | Altera EPM570T144C5N | 1 |
| NOR Flash | Spansion S29GL064N90TFI01 | 1 |
| NAND Flash | Toshiba TC58NVG5H2HTA00 | 1 |
| USB Flash Controller | Phison PS2251-67-5 | 1 |
| I2C Mux (4-ch) | PCA9546 | 3 |
| I2C Mux (8-ch) | PCA9548 | 7 |
| GPIO (40-bit) | PCA9506D | 6+ |
| GPIO (8-bit) | PCA9538 (TI) | 4 |
| Retimer | TI DS100DF410 | 8 |
| Bus Buffer | SN74LVC244A | 2 |
| Bus Mux | SN74LVC257A | 1 |
| Temp Sensor | MAX6697/MAX6581 | 1 |
| Temp Sensor | NE1617A/MAX1617 | 1 |
| RTC | Epson RTC8564 | 1 |
| USB Hub | SMSC USB2513i | 1 |
| Voltage Monitor | VT1165M | 1 |
| Clock Buffer | ICS83905I | 1 |
| Mgmt PHY | Broadcom BCM54610C | 1 |
| **Total ICs** | | **~44** |

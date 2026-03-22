# AS5610-52X Complete Chip Inventory

**Date**: 2026-03-22
**Source**: Live switch enumeration via sysfs, device tree, PCI, I2C, GPIO, MTD

Every chip that is loaded and active on the system, verified against Linux drivers.

---

## CPU / SoC

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Freescale P2020** | P2020E | SoC | n/a | 0xff700000 | Main CPU (e500v2 core, PPC32 BE) |
| - L2 Cache Controller | integrated | SoC | n/a | 0xff720000 | 512KB L2 cache |
| - Memory Controller | DDR | SoC | n/a | 0xff702000 | DDR2/DDR3 controller |
| - I2C Controller 0 | MPC I2C | SoC | mpc-i2c | 0xff703000 | I2C bus 0 |
| - I2C Controller 1 | MPC I2C | SoC | mpc-i2c | 0xff703100 | I2C bus 1 |
| - UART | 16550A | SoC | serial8250 | 0xff704500 | Console (ttyS0, 115200) |
| - USB EHCI | integrated | SoC | fsl-ehci | 0xff722000 | USB host (USB flash at 1-1.3) |
| - Ethernet | TSEC/eTSEC | SoC | fsl-gianfar | 0xff724000 | Management eth0 (1G) |
| - MDIO | integrated | SoC | fsl-gianfar | 0xff724520 | Management PHY MDIO |
| - PCIe Root Port | integrated | SoC | n/a | 0xff70a000 | PCIe x4 to BCM56846 |
| - PIC | MPIC | SoC | n/a | 0xff740000 | Interrupt controller |
| - Global Utilities | integrated | SoC | n/a | 0xff7e0000 | Clock, reset, PVR |

## Switch ASIC

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Broadcom BCM56846** | BCM56846_A1 | PCIe | linux-kernel-bde | PCI 01:00.0, BAR0=0xa0000000 | Trident+ switch ASIC (48x10G + 4x40G) |
| - Warpcore SerDes | WC-B0 (x14) | internal | firmware v0x0103 | MDIO buses 0,1,2 | 56-lane SerDes (14 x 4-lane blocks) |
| - CMIC LED Processor | x2 | internal | BCM SDK | CMIC LED regs | Front panel port LEDs |

## Flash / Storage

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **NOR Flash** | (SPI/LPB) | LocalBus | cfi_cmdset | 0xefc00000 | 4MB NOR flash (ONIE, U-Boot) |
| - mtd0 | onie | MTD | mtdblock | 3.4MB | ONIE partition |
| - mtd1 | uboot-env | MTD | mtdblock | 64KB | U-Boot environment |
| - mtd2 | board_eeprom | MTD | mtdblock | 64KB | Board EEPROM data |
| - mtd3 | uboot | MTD | mtdblock | 512KB | U-Boot bootloader |
| **USB Flash** | (unknown) | USB | usb-storage | /dev/sda (3.8GB) | Root filesystem |
| - sda1 | persist | ext4 | 128MB | /mnt/persist |
| - sda3 | root-rw | ext4 | 3.3GB | /mnt/root-rw (overlayfs upper) |
| - sda6 | root-ro | squashfs | 128MB | /mnt/root-ro (overlayfs lower) |

## CPLD

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Accton CPLD** | custom | LocalBus | accton_as5610_52x_cpld | 0xea000000 (LPB CS1) | System management (LEDs, PSU, fan, watchdog) |

## I2C Mux Chips

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **NXP PCA9548** | 8-ch mux | I2C-0 | pca954x | 0x70 | Root mux -> buses 2-9 |
| **NXP PCA9546** | 4-ch mux | I2C-1 | pca954x | 0x75 | SFP group A mux -> buses 10-13 |
| **NXP PCA9546** | 4-ch mux | I2C-1 | pca954x | 0x76 | SFP group B + GPIO mux -> buses 14-17 |
| **NXP PCA9546** | 4-ch mux | I2C-1 | pca954x | 0x77 | QSFP mux -> buses 18-21 |
| **NXP PCA9548** x6 | 8-ch mux | buses 10-15 | pca954x | 0x74 | SFP port muxes -> buses 22-69 |

**Total: 10 I2C mux chips** (1x PCA9548 root + 3x PCA9546 level-1 + 6x PCA9548 level-2)

## Temperature Sensors

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Maxim MAX6697** | 7-ch temp | I2C bus 9 | max6697 | 0x4d | Board temperature (7 zones) |
| **Maxim MAX1617** | 2-ch temp | I2C bus 9 | adm1021 | 0x18 | CPU/ambient temperature |

## GPIO Expanders

| Chip | Part | Bus | Driver | Base GPIO | Function |
|------|------|-----|--------|-----------|----------|
| **NXP PCA9506** | 40-bit GPIO | bus 16, 0x20 | pca953x | gpio24 | SFP TX disable (ports 1-40) |
| **NXP PCA9506** | 40-bit GPIO | bus 16, 0x21 | pca953x | gpio64 | SFP TX disable (ports 41-48) + misc |
| **NXP PCA9538** | 8-bit GPIO | bus 16, 0x70 | pca953x | gpio144 | QSFP1 control (reset, lpmode, modsel, presence) |
| **NXP PCA9538** | 8-bit GPIO | bus 16, 0x71 | pca953x | gpio152 | QSFP2 control |
| **NXP PCA9538** | 8-bit GPIO | bus 16, 0x72 | pca953x | gpio160 | QSFP3 control |
| **NXP PCA9538** | 8-bit GPIO | bus 16, 0x73 | pca953x | gpio168 | QSFP4 control |
| **NXP PCA9506** | 40-bit GPIO | bus 17, 0x20 | pca953x | gpio104 | SFP presence detect |
| **NXP PCA9506** | 40-bit GPIO | bus 17, 0x23 | pca953x | gpio176 | SFP RX LOS |
| **NXP PCA9506** | 40-bit GPIO | bus 17, 0x24 | pca953x | gpio216 | SFP TX fault |

**Total: 9 GPIO expander chips** (5x PCA9506 + 4x PCA9538)

## Retimers / Equalizers

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **TI DS100DF410** x32 | 4-ch retimer | buses 18-69 | ds100df410 | 0x27 | Signal conditioning (EQ + CDR) |

Retimer label mapping:
- retimer0-3: `qsfp_rx_eq_0` through `qsfp_rx_eq_3` (QSFP RX equalizer)
- retimer4-15: `sfp_rx_eq_0` through `sfp_rx_eq_11` (SFP+ RX equalizer)
- retimer16-27: `sfp_tx_eq_0` through `sfp_tx_eq_11` (SFP+ TX equalizer)
- retimer28-31: `qsfp_tx_eq_0` through `qsfp_tx_eq_3` (QSFP TX equalizer)

**Total: 32 retimer chips** on 32 I2C buses (4 QSFP RX + 12 SFP RX + 12 SFP TX + 4 QSFP TX)

Buses WITH retimers: 18-25, 30-33, 38-41, 46-49, 54-57, 62-69
Buses WITHOUT retimers: 26-29, 34-37, 42-45, 50-53, 58-61

## RTC

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Epson RTC8564** | RTC | I2C bus 2 | rtc-pcf8563 | 0x51 | Real-time clock (battery backed) |

## EEPROMs

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **24C02** x7 | 2Kbit EEPROM | buses 3-4 | at24 | 0x0c,0x39,0x3a,0x3d,0x3e,0x78 | Board/PSU/FRU EEPROMs |
| **24C04** x48 | 4Kbit EEPROM | buses 22-69 | at24 | 0x50 | SFP+ transceiver EEPROMs (SFF-8472 A0) |
| **SFF8436** x4 | QSFP EEPROM | buses 18-21 | sff8436 | 0x50 | QSFP transceiver EEPROMs (SFF-8436) |
| **dummy** x48 | placeholder | buses 22-69 | dummy | 0x51 | SFP diagnostic page (A2) placeholder |

**Total: 59 EEPROM devices** (7 board + 48 SFP + 4 QSFP)

## Management PHY

| Chip | Part | Bus | Driver | Address | Function |
|------|------|-----|--------|---------|----------|
| **Broadcom BCM5461** (or similar) | 1G PHY | MDIO (integrated) | fsl-gianfar | internal | Management port eth0 PHY |

---

## Summary Counts

| Category | Count | Chips |
|----------|-------|-------|
| CPU/SoC | 1 | P2020 |
| Switch ASIC | 1 | BCM56846 |
| CPLD | 1 | Accton custom |
| Flash | 2 | NOR (4MB) + USB (3.8GB) |
| I2C Mux | 10 | 1x PCA9548 + 3x PCA9546 + 6x PCA9548 |
| Temperature | 2 | MAX6697 + MAX1617 |
| GPIO Expander | 9 | 5x PCA9506 + 4x PCA9538 |
| Retimer/EQ | 32 | DS100DF410 |
| RTC | 1 | RTC8564 |
| EEPROM | 59 | 7x 24C02 + 48x 24C04 + 4x SFF8436 |
| Mgmt PHY | 1 | BCM5461 |
| SerDes (internal) | 14 | WC-B0 (inside BCM56846) |
| **TOTAL** | **133** | |

---

## Kernel Modules Required

| Module | Devices | Count |
|--------|---------|-------|
| linux-kernel-bde | BCM56846 | 1 |
| linux-user-bde | BCM56846 userspace | 1 |
| linux-bde-tmon | BCM56846 temp monitor | 1 |
| tun | TUN interfaces | 52 |
| accton_as5610_52x_cpld | CPLD | 1 |
| pca954x (i2c-mux-pca954x) | PCA9548/9546 | 10 |
| pca953x (gpio-pca953x) | PCA9506/9538 | 9 |
| at24 | 24C02/24C04 EEPROMs | 55 |
| sff_8436_eeprom | QSFP EEPROMs | 4 |
| ds100df410 | DS100DF410 retimers | 32 |
| max6697 | MAX6697 temp sensor | 1 |
| adm1021 | MAX1617 temp sensor | 1 |
| rtc-pcf8563 | RTC8564 | 1 |
| 8021q | VLAN | kernel |

# Edgecore AS5610-52X: Ecosystem, External References, and Cross-Platform Analysis

> Comprehensive compilation of all AS5610-52X platform references found across the Open
> Network Linux (ONL) tree, ONIE, Cumulus Linux, dentOS, Stratum, SONiC, OpenMDK, and
> other open-source projects. Includes full CPLD register maps, device tree analysis,
> kernel platform drivers, retimer equalizer tables, thermal sensor placement, and
> hardware specifications from Edge-Core official documentation.
>
> Date: 2026-03-12

---

## Table of Contents

1. [Hardware Specifications (Official)](#1-hardware-specifications-official)
2. [CPLD Register Map (Complete)](#2-cpld-register-map-complete)
3. [Cumulus Linux CPLD Driver](#3-cumulus-linux-cpld-driver)
4. [Device Tree Source Analysis](#4-device-tree-source-analysis)
5. [ONIE Machine Definition](#5-onie-machine-definition)
6. [ONIE Kernel Platform Patch](#6-onie-kernel-platform-patch)
7. [NOR Flash Layout](#7-nor-flash-layout)
8. [dentOS ONLP Platform Code](#8-dentos-onlp-platform-code)
9. [SFP I2C Mux Hierarchy (dentOS sfpi.c)](#9-sfp-i2c-mux-hierarchy-dentos-sfpic)
10. [DS100DF410 Retimer Equalizer Tables](#10-ds100df410-retimer-equalizer-tables)
11. [Thermal Sensor Placement Map](#11-thermal-sensor-placement-map)
12. [PSU Models and PMBus Registers](#12-psu-models-and-pmbus-registers)
13. [GPIO Expander Signal Mapping (dentOS)](#13-gpio-expander-signal-mapping-dentos)
14. [LED Control Details](#14-led-control-details)
15. [Fan Control and Thermal Policy](#15-fan-control-and-thermal-policy)
16. [BCM56846 in Stratum Project](#16-bcm56846-in-stratum-project)
17. [BCM56846 in SONiC](#17-bcm56846-in-sonic)
18. [OpenMDK BCM56846 SVK Board Config](#18-openmdk-bcm56846-svk-board-config)
19. [NXP-QorIQ ONL Fork](#19-nxp-qoriq-onl-fork)
20. [Open NOS Project Local Files](#20-open-nos-project-local-files)
21. [External Documentation Links](#21-external-documentation-links)
22. [Cross-Reference: Compatible Strings](#22-cross-reference-compatible-strings)
23. [Hardware Revision Notes](#23-hardware-revision-notes)

---

## 1. Hardware Specifications (Official)

From Edge-Core official datasheet (AS5610-52X_ONIE_DS_R03_20151029):

| Parameter | Value |
|-----------|-------|
| **Model** | AS5610-52X |
| **Ports** | 48 x 10GbE SFP+ (10GBASE-SR/LR or 1GbE) + 4 x 40GbE QSFP+ |
| **ASIC** | Broadcom BCM56846 (Trident+), 640 Gbps switching capacity |
| **CPU** | Freescale P2020 (dual-core PowerPC e500) |
| **Architecture** | PHY-less design with TI DS100DF410 retimer/equalizer |
| **Throughput** | 1.28 Tbps full line-rate L2/L3 |
| **PSU** | Dual hot-swappable: 110-230VAC 400W (CPR-4011) or -48VDC or 12VDC |
| **Typical Power** | 170W |
| **Fans** | N+1 redundant fan tray (3:1 configuration) |
| **Form Factor** | 1RU, 438.4 x 473 x 43.4 mm, 8.395 kg |
| **Airflow** | F2B (port-to-power) or B2F (power-to-port) SKUs |
| **Management** | Ethernet RJ-45, console RJ-45, USB storage |
| **ONIE** | Pre-loaded |
| **Compatible NOS** | Cumulus Linux, Big Switch BigTap, PicOS, Open Network Linux, dentOS |
| **PCI Device ID** | 0x14e4:0xb846 |
| **BAR0** | 0xa0000000 (256KB mapped) |
| **PCIe Range** | 0xa0000000 - 0xbfffffff (512MB) |
| **NOR Flash** | 4MB CFI at 0xefc00000 |
| **CPLD** | Memory-mapped at 0xea000000 via eLBC chip-select 1 |
| **Management PHY** | Broadcom BCM5482S (RGMII to eTSEC) |
| **USB** | SMSC USB2513i hub, ULPI host mode |
| **Warranty** | 3 years |

---

## 2. CPLD Register Map (Complete)

Compiled from Cumulus `accton_as5610_52x_cpld.h`, dentOS `ledi.c`/`fani.c`/`psui.c`, and
ONL ONLP platform sources. The CPLD is memory-mapped at **0xEA000000** (256 bytes) via
the P2020 eLBC chip-select 1.

### Register Table

| Offset | Name | R/W | Description |
|--------|------|-----|-------------|
| 0x00 | MODEL_TYPE | R | PCB model type (bits[2:0]) and PCB version (bits[5:3]) |
| 0x01 | PS2_STATUS | R | PSU 2 status |
| 0x02 | PS1_STATUS | R | PSU 1 status |
| 0x03 | SYSTEM_STATUS | R | System power/fan status |
| 0x04 | (reserved) | | |
| 0x05 | SFP_INTR_STATUS | R | SFP/QSFP interrupt status |
| 0x06 | (reserved) | | |
| 0x07 | (reserved) | | |
| 0x08 | MISC_INTR_STATUS | R | MAX6581/USB interrupt status |
| 0x09 | VERSION | R | CPLD version |
| 0x0A | VMARG_CTRL_1 | RW | CPU 1.05V voltage margin control |
| 0x0B | VMARG_CTRL_2 | RW | 3.3V and 3.3V SFP voltage margin |
| 0x0C | (reserved) | | |
| 0x0D | FAN_CTRL | RW | Fan PWM speed control (5-bit, 0x00-0x1F) |
| 0x0E | WATCH_DOG_CTRL | RW | Watchdog timer enable/kick/timeout |
| 0x0F | POWER_CTRL | RW | Over-temperature protection |
| 0x10 | RESET_CTRL_1 | RW | BCM56846 and MAX6581 resets (active LOW) |
| 0x11 | RESET_CTRL_2 | RW | Peripheral resets (active LOW) |
| 0x12 | INTERRUPT_MASK | RW | Interrupt mask register |
| 0x13 | SYSTEM_LED_CTRL_1 | RW | PSU1, PSU2, DIAG, FAN LEDs |
| 0x14 | MISC_CTRL | RW | QSFP LED shift register clear |
| 0x15 | SYSTEM_LED_CTRL_2 | RW | Locator LED |

### Register Bit Details

#### 0x00 - MODEL_TYPE
```
bits[2:0] = PCB model type (CPLD_PCB_MODEL_TYPE_MASK)
bits[5:3] = PCB version (CPLD_PCB_VER_MASK)
```

#### 0x01 - PS2_STATUS / 0x02 - PS1_STATUS
```
bit 0 = PSU absent (1=absent, 0=present)     — CPLD_PS_ABSENT
bit 1 = PSU DC OK (1=good, 0=not-OK)         — CPLD_PS_DC_OK
bit 2 = PSU fan OK (1=good, 0=not-OK)        — CPLD_PS_FAN_OK
bit 3 = PSU not over-temp (1=OK)              — CPLD_PS_NOT_OT
bit 4 = PSU fan direction                     — CPLD_PS_FAN_DIR
```

#### 0x03 - SYSTEM_STATUS
```
bit 0 = System power good                     — CPLD_SYS_PWR_GOOD
bit 2 = System fan absent (1=absent)          — CPLD_SYS_FAN_ABSENT
bit 3 = System fan bad (1=failure)            — CPLD_SYS_FAN_BAD
bit 4 = Fan airflow direction (1=F2B, 0=B2F)  — CPLD_SYS_FAN_AIR_FLOW
```

#### 0x05 - SFP_INTR_STATUS
```
bit 0 = SFP present interrupt                 — CPLD_SFP_PRESENT
bit 1 = SFP RX_LOS interrupt                  — CPLD_SFP_RX_LOS
bit 2 = QSFP port 0 interrupt                 — CPLD_QSFP_P0_INTR
bit 3 = QSFP port 1 interrupt                 — CPLD_QSFP_P1_INTR
bit 4 = QSFP port 2 interrupt                 — CPLD_QSFP_P2_INTR
bit 5 = QSFP port 3 interrupt                 — CPLD_QSFP_P3_INTR
```

#### 0x08 - MISC_INTR_STATUS
```
bit 0 = MAX6581 thermal interrupt             — CPLD_MAX6581_INTR
bit 1 = UPD720102GG USB controller interrupt  — CPLD_UPD720102GG_INTR
```

#### 0x09 - VERSION
```
bits[4:0] = CPLD version number               — CPLD_VERSION_MASK
bit 5     = Release version (0=engineering, 1=production) — CPLD_RELEASE_VERSION
```

#### 0x0A - VMARG_CTRL_1 (1.05V CPU Voltage Margin)
```
bits[1:0] = Voltage margin level
  3 = High (CPLD_VMARG_HIGH)
  2 = Normal (CPLD_VMARG_NORMAL)
  0 = Low (CPLD_VMARG_LOW)
```

#### 0x0B - VMARG_CTRL_2 (3.3V Voltage Margins)
```
bits[1:0] = 3.3V margin (same encoding as VMARG_CTRL_1)
bits[3:2] = 3.3V SFP margin
```

#### 0x0D - FAN_CTRL (Fan PWM Speed)
```
bits[4:0] = Fan speed raw value (0x00-0x1F)
  0x0C = 40% (MIN)    — duty cycle 96/248
  0x15 = 70% (MID)    — duty cycle 168/248
  0x1F = 100% (MAX)   — duty cycle 248/248

Sysfs scale: pwm_value = raw * 8 (range 0-248)
```

#### 0x0E - WATCH_DOG_CTRL
```
bit 0     = Kick (write 1 to keep alive)      — CPLD_WATCH_DOG_KICK
bit 1     = Enable watchdog                    — CPLD_WATCH_DOG_ENABLE
bits[5:2] = Timeout counter (4-bit index)     — CPLD_WATCH_DOG_COUNT_MASK

Timeout lookup table (16 entries, in seconds):
  Index:  0    1    2    3    4    5    6    7
  Secs:   8   16   32   48   64   72   88   96
  Index:  8    9   10   11   12   13   14   15
  Secs: 128  136  149  192  256  320  448  512
```

#### 0x0F - POWER_CTRL
```
bit 2 = Over-temperature protection enable    — CPLD_POWER_OT_PROTECT
```

#### 0x10 - RESET_CTRL_1 (All Active LOW: 0=reset, 1=normal)
```
bit 1 = BCM56846 reset                        — CPLD_RESET_BCM56846_L
bit 4 = MAX6581 thermal sensor reset          — CPLD_RESET_MAX6581_L
```

#### 0x11 - RESET_CTRL_2 (All Active LOW: 0=reset, 1=normal)
```
bit 0 = BCM5482S management PHY reset         — CPLD_RESET_BCM5482S_L
bit 1 = I2C switch (mux) reset                — CPLD_RESET_I2C_SWITCH_L
bit 2 = I2C GPIO expander reset               — CPLD_RESET_I2C_GPIO_L
bit 3 = USB PHY reset                         — CPLD_RESET_USB_PHY_L
bit 4 = USB HUB reset                         — CPLD_RESET_USB_HUB_L
```

#### 0x12 - INTERRUPT_MASK (1=masked, 0=enabled)
```
bit 0 = MAX6581 thermal interrupt             — CPLD_INTR_MASK_MAX6581
bit 1 = BCM56846 ASIC interrupt               — CPLD_INTR_MASK_BCM56846
bit 3 = I2C GPIO interrupt                    — CPLD_INTR_MASK_I2C_GPIO
bit 4 = USB interrupt                         — CPLD_INTR_MASK_USB
bit 5 = CF card interrupt                     — CPLD_INTR_MASK_CF_CARD
bit 6 = Watchdog interrupt                    — CPLD_INTR_MASK_WATCH_DOG
bit 7 = SFP RX_LOS interrupt                  — CPLD_INTR_MASK_RX_LOS
```

#### 0x13 - SYSTEM_LED_CTRL_1
```
bits[1:0] = PSU1 LED
  00 = Yellow, 10 = Green, 11 = Off

bits[3:2] = PSU2 LED
  00 = Yellow, 10 = Green, 11 = Off

bits[5:4] = DIAG LED
  00 = Off, 01 = Yellow, 10 = Green

bits[7:6] = FAN LED
  01 = Green, 10 = Yellow, 11 = Off
```

#### 0x14 - MISC_CTRL
```
bit 0 = QSFP LED shift register clear         — CPLD_MISC_QSFP_LED_SHIFT_REG_CLEAR
```

#### 0x15 - SYSTEM_LED_CTRL_2
```
bits[1:0] = Locator LED
  01 = Off (CPLD_SYS_LED_LOCATOR_OFF)
  11 = Yellow blink (CPLD_SYS_LED_LOCATOR_YELLOW_BLINK)
```

---

## 3. Cumulus Linux CPLD Driver

**Source**: `sonix-network/platform-modules-cumulus-4.19.y-stable4`
**Author**: Puneet Shenoy (Cumulus Networks), 2014

### Header File (accton_as5610_52x_cpld.h)

Complete C header defining all CPLD register offsets and bit masks:

```c
#ifndef ACCTON_AS5610_52X_H__
#define ACCTON_AS5610_52X_H__

#define CPLD_REG_MODEL_TYPE         (0x00)
#  define CPLD_PCB_VER_MASK           (0x38)
#  define CPLD_PCB_VER_SHIFT          (0x3)
#  define CPLD_PCB_MODEL_TYPE_MASK    (0x7)
#  define CPLD_PCB_MODEL_TYPE_SHIFT   (0x0)

#define CPLD_REG_PS2_STATUS         (0x01)
#define CPLD_REG_PS1_STATUS         (0x02)
#  define CPLD_PS_ABSENT              (1 << 0)
#  define CPLD_PS_DC_OK               (1 << 1)
#  define CPLD_PS_FAN_OK              (1 << 2)
#  define CPLD_PS_NOT_OT              (1 << 3)
#  define CPLD_PS_FAN_DIR             (1 << 4)

#define CPLD_REG_SYSTEM_STATUS      (0x03)
#  define CPLD_SYS_PWR_GOOD           (1 << 0)
#  define CPLD_SYS_FAN_ABSENT         (1 << 2)
#  define CPLD_SYS_FAN_BAD            (1 << 3)
#  define CPLD_SYS_FAN_AIR_FLOW       (1 << 4)

#define CPLD_REG_SFP_INTR_STATUS    (0x05)
#  define CPLD_SFP_PRESENT            (1 << 0)
#  define CPLD_SFP_RX_LOS             (1 << 1)
#  define CPLD_QSFP_P0_INTR           (1 << 2)
#  define CPLD_QSFP_P1_INTR           (1 << 3)
#  define CPLD_QSFP_P2_INTR           (1 << 4)
#  define CPLD_QSFP_P3_INTR           (1 << 5)

#define CPLD_REG_MISC_INTR_STATUS   (0x08)
#  define CPLD_MAX6581_INTR           (1 << 0)
#  define CPLD_UPD720102GG_INTR       (1 << 1)

#define CPLD_REG_VERSION            (0x09)
#  define CPLD_VERSION_MASK           (0x1F)
#  define CPLD_RELEASE_VERSION        (1 << 5)

#define CPLD_REG_VMARG_CTRL_1       (0x0A)
#  define CPLD_VMARG_1_05V_CPU_MASK   (0x3)
#  define CPLD_VMARG_1_05V_CPU_SHIFT  (0)
#  define CPLD_VMARG_HIGH             (3)
#  define CPLD_VMARG_NORMAL           (2)
#  define CPLD_VMARG_LOW              (0)

#define CPLD_REG_VMARG_CTRL_2       (0x0B)
#  define CPLD_VMARG_3_3V_MASK        (0x3)
#  define CPLD_VMARG_3_3V_SHIFT       (0)
#  define CPLD_VMARG_3_3V_SFP_MASK    (0xc)
#  define CPLD_VMARG_3_3V_SFP_SHIFT   (2)

#define CPLD_REG_FAN_CTRL           (0x0D)
#  define CPLD_FAN_CTRL_MASK          (0x1F)

#define CPLD_REG_WATCH_DOG_CTRL     (0x0E)
#  define CPLD_WATCH_DOG_KICK         (1 << 0)
#  define CPLD_WATCH_DOG_ENABLE       (1 << 1)
#  define CPLD_WATCH_DOG_COUNT_MASK   (0x3c)
#  define CPLD_WATCH_DOG_COUNT_SHIFT  (2)

#define CPLD_REG_POWER_CTRL         (0x0F)
#  define CPLD_POWER_OT_PROTECT       (1 << 2)

#define CPLD_REG_RESET_CTRL_1       (0x10)   // all resets active low
#  define CPLD_RESET_BCM56846_L       (1 << 1)
#  define CPLD_RESET_MAX6581_L        (1 << 4)

#define CPLD_REG_RESET_CTRL_2       (0x11)   // all resets active low
#  define CPLD_RESET_BCM5482S_L       (1 << 0)
#  define CPLD_RESET_I2C_SWITCH_L     (1 << 1)
#  define CPLD_RESET_I2C_GPIO_L       (1 << 2)
#  define CPLD_RESET_USB_PHY_L        (1 << 3)
#  define CPLD_RESET_USB_HUB_L        (1 << 4)

#define CPLD_REG_INTERRUPT_MASK     (0x12)
#  define CPLD_INTR_MASK_MAX6581      (1 << 0)
#  define CPLD_INTR_MASK_BCM56846     (1 << 1)
#  define CPLD_INTR_MASK_I2C_GPIO     (1 << 3)
#  define CPLD_INTR_MASK_USB          (1 << 4)
#  define CPLD_INTR_MASK_CF_CARD      (1 << 5)
#  define CPLD_INTR_MASK_WATCH_DOG    (1 << 6)
#  define CPLD_INTR_MASK_RX_LOS       (1 << 7)

#define CPLD_REG_SYSTEM_LED_CTRL_1  (0x13)
#  define CPLD_SYS_LED_PS1_MASK       (0x03)
#    define CPLD_SYS_LED_PS1_OFF        (3)
#    define CPLD_SYS_LED_PS1_GREEN      (2)
#    define CPLD_SYS_LED_PS1_YELLOW     (0)
#  define CPLD_SYS_LED_PS2_MASK       (0x0c)
#    define CPLD_SYS_LED_PS2_OFF        (3 << 2)
#    define CPLD_SYS_LED_PS2_GREEN      (2 << 2)
#    define CPLD_SYS_LED_PS2_YELLOW     (0 << 2)
#  define CPLD_SYS_LED_DIAG_MASK      (0x30)
#    define CPLD_SYS_LED_DIAG_GREEN     (2 << 4)
#    define CPLD_SYS_LED_DIAG_YELLOW    (1 << 4)
#    define CPLD_SYS_LED_DIAG_OFF       (0 << 4)
#  define CPLD_SYS_LED_FAN_MASK       (0xC0)
#    define CPLD_SYS_LED_FAN_OFF        (3 << 6)
#    define CPLD_SYS_LED_FAN_YELLOW     (2 << 6)
#    define CPLD_SYS_LED_FAN_GREEN      (1 << 6)

#define CPLD_REG_MISC_CTRL           (0x14)
#  define CPLD_MISC_QSFP_LED_SHIFT_REG_CLEAR (1 << 0)

#define CPLD_REG_SYSTEM_LED_CTRL_2    (0x15)
#  define CPLD_SYS_LED_LOCATOR_MASK     (0x03)
#    define CPLD_SYS_LED_LOCATOR_YELLOW_BLINK   (3)
#    define CPLD_SYS_LED_LOCATOR_OFF            (1)

#endif /* ACCTON_AS5610_52X_H__ */
```

### Driver Implementation Notes

The Cumulus driver (`accton_as5610_52x_cpld.c`) uses:
- `of_iomap()` for memory-mapped CPLD access (compatible: `"accton,accton_as5610_52x-cpld"`)
- `readb()`/`writeb()` for register I/O
- PWM: input range 0-255, shifted right 3 bits → 0-31 CPLD raw value
- Sysfs attributes: `board_revision`, `pwm1`, `pwm1_enable`, `psu_pwr{1,2}_*`, `system_*`, `led_*`, `watch_dog_*`

---

## 4. Device Tree Source Analysis

From our custom DTS (`open-nos-as5610/boot/as5610_52x_full.dts`) and the ONIE kernel patch DTS.

### SoC Architecture

```
P2020 SoC @ 0xff700000
├── Memory Controller @ 0x2000
├── I2C0 @ 0x3000 (Management bus)
│   └── PCA9548 @ 0x70 (8-channel mux)
│       ├── Ch0: Epson RTC8564 @ 0x51
│       ├── Ch1: PSU1 EEPROMs @ 0x3A/0x3E/0x78
│       ├── Ch2: PSU2 EEPROMs @ 0x0C/0x39/0x3D/0x78
│       ├── Ch3: (empty)
│       ├── Ch4: SMSC USB2513i hub @ 0x2C
│       ├── Ch5: VT1165M voltage monitor @ 0x71
│       ├── Ch6: ICS83905I PCIe clock buffer @ 0x6E
│       └── Ch7: Thermal sensors
│           ├── MAX6697/MAX6581 @ 0x4D (7/8-channel)
│           └── MAX1617/NE1617A @ 0x18
│               (ONIE DTS also shows: 0x1A, 0x4C)
├── I2C1 @ 0x3100 (SFP/QSFP bus)
│   ├── PCA9546 @ 0x75 (ports 1-32 via sub-muxes)
│   ├── PCA9546 @ 0x76 (ports 33-48, GPIO expanders)
│   └── PCA9546 @ 0x77 (QSFP ports 49-52)
├── Serial @ 0x4500 (ns16550, console)
├── L2 Cache Controller @ 0x20000 (512KB)
├── USB @ 0x22000 (ULPI host)
├── MDIO @ 0x24520 (gianfar, BCM5482S PHY @ addr 1)
├── Ethernet @ 0x24000 (eTSEC, RGMII)
├── OpenPIC @ 0x40000
└── Global Utilities @ 0xe0000

Local Bus (eLBC) @ 0xff705000
├── CS0: NOR Flash @ 0xefc00000 (4MB, CFI)
│   ├── onie: 0x000000 - 0x35FFFF (3.375MB)
│   ├── uboot-env: 0x360000 - 0x36FFFF (64KB)
│   ├── board_eeprom: 0x370000 - 0x37FFFF (64KB)
│   └── uboot: 0x380000 - 0x3FFFFF (512KB)
└── CS1: CPLD @ 0xea000000 (256 bytes)

PCIe @ 0xff70a000
└── BCM56846 @ BAR0 0xa0000000-0xbfffffff (512MB range)

BCM DMA Region: 64MB, 1MB aligned (for ASIC packet DMA)
```

### I2C1 Mux Tree (SFP/QSFP)

```
I2C1 @ 0x3100
├── PCA9546 @ 0x75 (deselect-on-exit)
│   ├── Ch0 → PCA9548 @ 0x74
│   │   ├── Ch0: Port 1  (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_0")
│   │   ├── Ch1: Port 2  (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_1")
│   │   ├── Ch2: Port 3  (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_2")
│   │   ├── Ch3: Port 4  (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_3")
│   │   ├── Ch4: Port 5  (EEPROM @0x50)
│   │   ├── Ch5: Port 6  (EEPROM @0x50)
│   │   ├── Ch6: Port 7  (EEPROM @0x50)
│   │   └── Ch7: Port 8  (EEPROM @0x50)
│   ├── Ch1 → PCA9548 @ 0x74
│   │   ├── Ch0: Port 9  (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_4")
│   │   ├── Ch1: Port 10 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_5")
│   │   ├── Ch2: Port 11 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_6")
│   │   ├── Ch3: Port 12 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_7")
│   │   ├── Ch4: Port 13 (EEPROM @0x50)
│   │   ├── Ch5: Port 14 (EEPROM @0x50)
│   │   ├── Ch6: Port 15 (EEPROM @0x50)
│   │   └── Ch7: Port 16 (EEPROM @0x50)
│   ├── Ch2 → PCA9548 @ 0x74
│   │   ├── Ch0: Port 17 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_8")
│   │   ├── Ch1: Port 18 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_9")
│   │   ├── Ch2: Port 19 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_10")
│   │   ├── Ch3: Port 20 (EEPROM @0x50, Retimer @0x27 "sfp_rx_eq_11")
│   │   ├── Ch4: Port 21 (EEPROM @0x50)
│   │   ├── Ch5: Port 22 (EEPROM @0x50)
│   │   ├── Ch6: Port 23 (EEPROM @0x50)
│   │   └── Ch7: Port 24 (EEPROM @0x50)
│   └── Ch3 → PCA9548 @ 0x74
│       ├── Ch0: Port 25 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_0")
│       ├── Ch1: Port 26 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_1")
│       ├── Ch2: Port 27 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_2")
│       ├── Ch3: Port 28 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_3")
│       ├── Ch4: Port 29 (EEPROM @0x50)
│       ├── Ch5: Port 30 (EEPROM @0x50)
│       ├── Ch6: Port 31 (EEPROM @0x50)
│       └── Ch7: Port 32 (EEPROM @0x50)
├── PCA9546 @ 0x76 (deselect-on-exit)
│   ├── Ch0 → PCA9548 @ 0x74
│   │   ├── Ch0: Port 33 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_4")
│   │   ├── Ch1: Port 34 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_5")
│   │   ├── Ch2: Port 35 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_6")
│   │   ├── Ch3: Port 36 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_7")
│   │   ├── Ch4: Port 37 (EEPROM @0x50)
│   │   ├── Ch5: Port 38 (EEPROM @0x50)
│   │   ├── Ch6: Port 39 (EEPROM @0x50)
│   │   └── Ch7: Port 40 (EEPROM @0x50)
│   ├── Ch1 → PCA9548 @ 0x74
│   │   ├── Ch0: Port 41 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_8")
│   │   ├── Ch1: Port 42 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_9")
│   │   ├── Ch2: Port 43 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_10")
│   │   ├── Ch3: Port 44 (EEPROM @0x50, Retimer @0x27 "sfp_tx_eq_11")
│   │   ├── Ch4: Port 45 (EEPROM @0x50, Retimer @0x27 "qsfp_tx_eq_0")
│   │   ├── Ch5: Port 46 (EEPROM @0x50, Retimer @0x27 "qsfp_tx_eq_1")
│   │   ├── Ch6: Port 47 (EEPROM @0x50, Retimer @0x27 "qsfp_tx_eq_2")
│   │   └── Ch7: Port 48 (EEPROM @0x50, Retimer @0x27 "qsfp_tx_eq_3")
│   ├── Ch2: GPIO expanders
│   │   ├── PCA9506 @ 0x20 (rate select 0)
│   │   ├── PCA9506 @ 0x21 (rate select 1)
│   │   ├── PCA9538 @ 0x70 (QSFP LPMODE/RESET 0)
│   │   ├── PCA9538 @ 0x71 (QSFP MODSEL/INT)
│   │   ├── PCA9538 @ 0x72 (SFP 40-47 rate select)
│   │   └── PCA9538 @ 0x73 (misc GPIO)
│   └── Ch3: GPIO expanders
│       ├── PCA9506 @ 0x20 (MOD_ABS ports 0-39)
│       ├── PCA9506 @ 0x23 (mixed: ports 40-47 + QSFP presence)
│       └── PCA9506 @ 0x24 (TX_DISABLE ports 0-39)
└── PCA9546 @ 0x77 (deselect-on-exit)
    ├── Ch0: Port 49/QSFP (EEPROM @0x50 "sff8436", Retimer @0x27 "qsfp_rx_eq_0")
    ├── Ch1: Port 50/QSFP (EEPROM @0x50 "sff8436", Retimer @0x27 "qsfp_rx_eq_1")
    ├── Ch2: Port 51/QSFP (EEPROM @0x50 "sff8436", Retimer @0x27 "qsfp_rx_eq_2")
    └── Ch3: Port 52/QSFP (EEPROM @0x50 "sff8436", Retimer @0x27 "qsfp_rx_eq_3")
```

**Key observations from DTS**:
- Ports 1-4, 9-12, 17-20, 25-28 have **RX equalizer** retimers (labeled `sfp_rx_eq_*`)
- Ports 25-28, 33-36, 41-44 have **TX equalizer** retimers (labeled `sfp_tx_eq_*`)
- Ports 45-48 have **QSFP TX equalizer** retimers (`qsfp_tx_eq_*`)
- Ports 49-52 have **QSFP RX equalizer** retimers (`qsfp_rx_eq_*`)
- All retimers are DS100DF410 at address 0x27
- SFP EEPROMs use `at,24c04` (4Kbit); QSFP EEPROMs use `sff8436`
- Ports 5-8, 13-16, 21-24, 29-32, 37-40 have **NO retimer** in the DTS (EEPROM only)

**Important note**: The retimer at 0x27 is physically on I2C-1 (not on per-port buses). It
appears on downstream buses due to I2C mux passthrough. The DTS labels indicate which
equalizer channel the retimer serves on each port's bus.

---

## 5. ONIE Machine Definition

**Source**: `opencomputeproject/onie`, path: `machine/accton/accton_as5610_52x/machine.make`

```makefile
ONIE_ARCH ?= powerpc-softfloat
SWITCH_ASIC_VENDOR = bcm

VENDOR_REV ?= r01a

# Hardware revision mapping
# r01a -> MACHINE_REV = 0
# r01d -> MACHINE_REV = 1 (new SDRAM and different oscillator)

UBOOT_MACHINE = AS5610_52X
KERNEL_DTB = as5610_52x.dtb

VENDOR_ID = 259   # Accton Technology Corporation IANA number

LINUX_VERSION = 3.2
LINUX_MINOR_VERSION = 69
GCC_VERSION = 4.9.2

EXT3_4_ENABLE = no
BTRFS_PROGS_ENABLE = no
MTDUTILS_ENABLE = no
STRACE_ENABLE = no
```

**Key facts**:
- **Vendor ID 259**: Accton Technology Corporation IANA enterprise number
- **Two hardware revisions**: r01a (rev 0) and r01d (rev 1, different SDRAM and oscillator)
- ONIE uses Linux 3.2.69 with GCC 4.9.2 (our NOS uses Linux 5.10)
- No ext3/4, btrfs, or MTD utilities in ONIE (not needed)

---

## 6. ONIE Kernel Platform Patch

**Source**: `opencomputeproject/onie`, path: `machine/accton/accton_as5610_52x/kernel/`

The ONIE kernel patch (`platform-accton-as5610_52x.patch`, 33,735 bytes) adds three components:

### 6.1 Kconfig Entry
```kconfig
config AS5610_52X
    bool "Accton AS5610_52X"
    select DEFAULT_UIMAGE
    help
      Accton AS5610_52X
```

### 6.2 Platform Init Code (`as5610_52x.c`)

```c
/* Machine definition */
static char *board[] __initdata = {
    "accton,5652",
    NULL,
};

static void __init as5610_52x_pic_init(void)
{
    struct mpic *mpic = mpic_alloc(NULL, 0, MPIC_BIG_ENDIAN |
        MPIC_SINGLE_DEST_CPU, 0, 256, " OpenPIC  ");
    BUG_ON(mpic == NULL);
    mpic_init(mpic);
}

define_machine(as5610_52x) {
    .name           = "Accton AS5610-52X",
    .probe          = as5610_52x_probe,
    .setup_arch     = as5610_52x_setup_arch,
    .init_IRQ       = as5610_52x_pic_init,
    .get_irq        = mpic_get_irq,
    .restart        = fsl_rstcr_restart,
    .calibrate_decr = generic_calibrate_decr,
    .progress       = udbg_progress,
};
```

### 6.3 Full DTS (1,238 lines)

The ONIE DTS has additional I2C devices compared to our custom DTS:

| I2C0/Ch | Device | Address | Description |
|---------|--------|---------|-------------|
| Ch0 | Epson RTC8564 | 0x51 | Real-time clock |
| Ch1 | at24c02 | 0x39, 0x3A, 0x3D, 0x3E | PSU EEPROMs (config + data) |
| Ch4 | USB2513i | 0x2C | USB hub (handled by U-Boot) |
| Ch5 | VT1165M | 0x71 | Voltage monitor |
| Ch6 | ICS83905I | 0x6E | PCIe clock buffer |
| Ch7 | W83782D | 0x29 | Winbond hardware monitor |
| Ch7 | MAX1617/NE1617A | 0x18 | Thermal sensor |
| Ch7 | NE1617A | 0x1A | Thermal sensor (not in our DTS) |
| Ch7 | MAX6581 | 0x4C | Thermal sensor (not in our DTS) |
| Ch7 | MAX6581 | 0x4D | Primary thermal sensor |

**Notable**: ONIE DTS has the Winbond W83782D hwmon at 0x29 and additional thermal sensors
at 0x1A and 0x4C that are not in our simplified DTS. The ONIE DTS also notes
`accton,broken_1000` property on the gianfar ethernet node (1Gb PHY broken on some
board revisions).

---

## 7. NOR Flash Layout

The AS5610-52X has a **4MB NOR flash** (CFI) at physical address 0xEFC00000.

### Flash Partition Map

```
Address Range          Size      Name
0xEFC00000-0xEFF5FFFF  3,538,944 (0x360000)  onie (kernel + initramfs uImage)
0xEFF60000-0xEFF6FFFF     65,536 (0x010000)  uboot-env
0xEFF70000-0xEFF7FFFF     65,536 (0x010000)  board_eeprom (ONIE TLV data)
0xEFF80000-0xEFFFFFFF    524,288 (0x080000)  uboot
```

**Constraint**: ONIE kernel image max size is **0x360000 (3.375MB)**. This is extremely
tight — calculated as: 4MB total - 512KB U-Boot - 64KB env - 64KB eeprom = 3.375MB.

### ONIE Board EEPROM

The ONIE TLV data block resides at physical address **0xEFF70000** (in the `board_eeprom`
NOR partition). This contains serial number, MAC addresses, platform name, and other
ONIE-standard fields.

### onie-rom.conf

```shell
description="Accton, AS5610_52X"
format=ubootenv_onie
uimage_max_size=$(( 0x400000 - 0x80000 - 0x20000 ))  # = 0x360000
uboot_machine=AS5610_52X
onie_uimage_size=0x00360000
```

---

## 8. dentOS ONLP Platform Code

**Source**: `dentproject/dentOS`, path:
`packages/platforms/accton/powerpc/as5610-52x/onlp/builds/powerpc_accton_as5610_52x/module/src/`

dentOS carries a complete copy of the ONLP platform driver, identical to the OCP ONL
version. Key implementation details not covered in the ONLP reference document:

### 8.1 System Info (sysi.c)

```c
/* ONIE data physical address (in NOR flash board_eeprom partition) */
#define ONIE_EEPROM_PHYS_ADDR  0xeff70000

/* Platform capabilities */
#define PSU_COUNT       2
#define FAN_COUNT       1
#define THERMAL_COUNT   11   /* NE1617A(2) + MAX6581(8) + BCM56846(1) */
#define LED_COUNT       5    /* PSU1, PSU2, DIAG, FAN, LOCATOR */
```

**Thermal policy** defines Front-to-Back (F2B) and Back-to-Front (B2F) threshold tables
with per-sensor temperature targets: tA, tB, tC, tD, tCritical for all 11 sensors.

Fan management operates in 3 speeds:
- **MIN** = 40% (CPLD raw 0x0C)
- **MID** = 70% (CPLD raw 0x15)
- **MAX** = 100% (CPLD raw 0x1F)

### 8.2 Platform Registration (__init__.py)

```python
class OnlPlatform_powerpc_accton_as5610_52x_r0(OnlPlatformAccton,
                                               OnlPlatformPortConfig_48x10_4x40):
    PLATFORM = 'powerpc-accton-as5610-52x-r0'
    MODEL = 'AS5610-52X'
    SYS_OBJECT_ID = '.5610.52'
```

---

## 9. SFP I2C Mux Hierarchy (dentOS sfpi.c)

The dentOS `sfpi.c` (~960 lines) contains the complete I2C mux selection logic for all 52
ports. This is the authoritative reference for the mux hierarchy.

### Port-to-Mux Mapping Table

| Ports | I2C Bus | L1 Mux | L1 Ch | L2 Mux | L2 Ch (mask) |
|-------|---------|--------|-------|--------|---------------|
| 0-7   | 1 | 0x75 | 0x01 | 0x74 | 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 |
| 8-15  | 1 | 0x75 | 0x02 | 0x74 | 0x01-0x80 |
| 16-23 | 1 | 0x75 | 0x04 | 0x74 | 0x01-0x80 |
| 24-31 | 1 | 0x75 | 0x08 | 0x74 | 0x01-0x80 |
| 32-39 | 1 | 0x76 | 0x01 | 0x74 | 0x01-0x80 |
| 40-47 | 1 | 0x76 | 0x02 | 0x74 | 0x01-0x80 |
| 48    | 1 | 0x77 | 0x01 | N/A  | N/A (direct) |
| 49    | 1 | 0x77 | 0x02 | N/A  | N/A (direct) |
| 50    | 1 | 0x77 | 0x04 | N/A  | N/A (direct) |
| 51    | 1 | 0x77 | 0x08 | N/A  | N/A (direct) |

**Note**: dentOS uses 0-indexed ports (0-51), while our NOS uses 1-indexed (1-52). The
QSFP ports 48-51 (dentOS) = ports 49-52 (NOS) connect directly to PCA9546 @ 0x77 channels
with no sub-mux.

### QSFP MODSEL Control

Before accessing QSFP EEPROM, the driver must assert MODSEL (active low) via I2C GPIO:
```c
/* Set QSFP MODSEL low via IO expander 0x71 on mux 0x76 ch 0x04 */
as5610_52x_i2c_mux_select(1, 0x76, 0x04);  /* Select GPIO bus */
i2c_smbus_write_byte_data(fd, 0x71, 0x03, ~(1 << qsfp_port));
```

### QSFP Port 48/49 Presence Swap Bug

The dentOS code documents a hardware quirk where QSFP port 48 and 49 presence bits are
swapped in the IO expander:
```c
static int port_qsfp_ioexpander_presence_map__[] = {1, 0, 2, 3};
```

---

## 10. DS100DF410 Retimer Equalizer Tables

The dentOS `sfpi.c` contains per-port retimer configuration for all 48 SFP+ ports. Each
entry specifies the TX and RX channel select values written to the DS100DF410 register
0xFF before programming equalizer settings.

### Retimer Channel Select Values (Register 0xFF)

| Channel | Value | Description |
|---------|-------|-------------|
| 0x04 | Channel 0 | First channel |
| 0x08 | Channel 1 | Second channel |
| 0x10 | Channel 2 | Third channel |
| 0x20 | Channel 3 | Fourth channel |

### Per-Port Retimer Mapping

The retimer configuration table from dentOS maps each SFP port to specific TX and RX
channels on the DS100DF410. The equalizer address (0x27) and I2C mux path select which
physical retimer IC is programmed.

**Pattern**: Ports are grouped by retimer IC. Each retimer serves 4 ports (4 channels).
The retimer labels in the DTS (`sfp_rx_eq_0` through `sfp_rx_eq_11`, `sfp_tx_eq_0`
through `sfp_tx_eq_11`, `qsfp_rx_eq_0` through `qsfp_rx_eq_3`, `qsfp_tx_eq_0` through
`qsfp_tx_eq_3`) indicate:

- **12 RX equalizer retimers** for SFP ports (ports 1-48, groups of 4)
- **12 TX equalizer retimers** for SFP ports (ports 25-48 only + some overlap)
- **4 RX equalizer retimers** for QSFP ports (ports 49-52, one per port)
- **4 TX equalizer retimers** for QSFP ports (mux76/ch1 sub-mux ch4-7)

Total: **32 equalizer retimer channel assignments** (but physically fewer ICs due to the
single retimer at 0x27 appearing on multiple buses).

---

## 11. Thermal Sensor Placement Map

From dentOS `thermali.c`, with physical board placement descriptions:

| ID | Sensor | I2C Bus | Addr | Register | Board Location |
|----|--------|---------|------|----------|----------------|
| 1 | NE1617A local | 0 (ch7) | 0x18 | 0x00 | On-chip (NE1617A die) |
| 2 | NE1617A remote | 0 (ch7) | 0x18 | 0x01 | External diode |
| 3 | MAX6581 local | 0 (ch7) | 0x4D | 0x07 | On-chip (MAX6581 die) |
| 4 | MAX6581 remote 1 | 0 (ch7) | 0x4D | 0x01 | Near right-upper side of CPU |
| 5 | MAX6581 remote 2 | 0 (ch7) | 0x4D | 0x02 | Near right side of MAX6581 |
| 6 | MAX6581 remote 3 | 0 (ch7) | 0x4D | 0x03 | Near right side of MAC (Trident+) |
| 7 | MAX6581 remote 4 | 0 (ch7) | 0x4D | 0x04 | Near left-down side of Equalizer_U57 |
| 8 | MAX6581 remote 5 | 0 (ch7) | 0x4D | 0x05 | Near right-down side of MAC |
| 9 | MAX6581 remote 6 | 0 (ch7) | 0x4D | 0x06 | Near upper side of Equalizer_U49 |
| 10 | MAX6581 remote 7 | 0 (ch7) | 0x4D | 0x08 | Near left-down side of PCB |
| 11 | BCM56846 on-die | N/A | N/A | N/A | Read from `/var/run/broadcom/temp0` |

### MAX6581 Configuration

- **Extended range mode**: Config reg 0x41 bit 1 (range -64 to +191 C)
- **Diode fault register**: 0x46 (bits indicate broken thermal diode connections)
- **Decimal place registers**: 0x51-0x58 (0.125 C resolution)

### Temperature Reading Formula (MAX6581 Extended Range)

```
temp_C = register_value - 64 + (decimal_reg >> 5) * 0.125
```

---

## 12. PSU Models and PMBus Registers

From dentOS `psui.c`:

### Supported PSU Models

| Type | Model | Airflow | I2C Config Addr | I2C EEPROM Addr |
|------|-------|---------|-----------------|-----------------|
| AC | CPR-4011-4M11 | F2B | PSU1: 0x3E, PSU2: 0x3D | PSU1: 0x3A, PSU2: 0x39 |
| AC | CPR-4011-4M21 | B2F | PSU1: 0x3E, PSU2: 0x3D | PSU1: 0x3A, PSU2: 0x39 |
| DC | um400d01G | B2F | N/A | PSU1: 0x56, PSU2: 0x55 |
| DC | um400d01-01G | F2B | N/A | PSU1: 0x56, PSU2: 0x55 |

### PMBus Register Map

| Register | Address | Description | Unit |
|----------|---------|-------------|------|
| VIN | 0x88 | Input voltage | mV (LINEAR11) |
| VOUT | 0x8B | Output voltage | mV (LINEAR16) |
| IIN | 0x89 | Input current | mA (LINEAR11) |
| IOUT | 0x8C | Output current | mA (LINEAR11) |
| PIN | 0x97 | Input power | mW (LINEAR11) |
| POUT | 0x96 | Output power | mW (LINEAR11) |
| FAN_SPEED | 0x3B | Fan speed RPM | RPM |
| STATUS_FAN | 0x81 | Fan status | bit 7 = failure |
| STATUS_TEMPERATURE | 0x7D | Temperature status | bit flags |
| READ_TEMPERATURE | 0x8D | PSU temperature | C (LINEAR11) |

### PSU Detection Logic

```c
/* AC PSU: read model name from EEPROM addr (0x3A/0x39) register 0x26 */
/* DC PSU: read model name from EEPROM addr (0x56/0x55) register 0x50 */
/* Model name string determines airflow direction */
```

---

## 13. GPIO Expander Signal Mapping (dentOS)

From dentOS `sfpi.c`, the complete GPIO expander mapping for SFP/QSFP control signals:

### SFP Ports 0-39 (PCA9506 expanders on mux76/ch3)

| Signal | Expander Addr | IOC Registers | Active Level |
|--------|--------------|---------------|--------------|
| PRESENT (MOD_ABS) | 0x20 | IOC 0x18-0x1C (5 banks, 8 bits each) | LOW = present |
| TX_FAULT | 0x21 | IOC 0x18-0x1C | HIGH = fault |
| RX_LOS | 0x22 | IOC 0x18-0x1C | HIGH = loss |
| TX_DISABLE | 0x24 | IOC 0x18-0x1C | HIGH = disabled |

Each PCA9506 has 5 banks of 8 bits = 40 ports per expander.

### SFP Ports 40-47 (PCA9506 @ 0x23 on mux76/ch3)

| Signal | Register | Bits |
|--------|----------|------|
| PRESENT | IOC 0x19 | bits[7:0] for ports 40-47 |
| TX_FAULT | IOC 0x19 | bits[7:0] |
| RX_LOS | IOC 0x19 | bits[7:0] |
| TX_DISABLE | IOC 0x19 | bits[7:0] |

### QSFP Ports 48-51 (PCA9506 @ 0x23 on mux76/ch3)

| Signal | Register | Bits | Notes |
|--------|----------|------|-------|
| PRESENT | IOC 0x1A | bits[3:0] | Ports 48/49 presence swapped! |
| MODSEL | PCA9538 @ 0x71 on mux76/ch2 | via write to reg 0x03 | Active LOW |
| LPMODE | PCA9538 @ 0x70 on mux76/ch2 | | |
| RESET | PCA9538 @ 0x70 on mux76/ch2 | | |

---

## 14. LED Control Details

From dentOS `ledi.c` and Cumulus `accton_as5610_52x_cpld.h`:

### System LED Register (CPLD 0x13)

```
Bit Map:
  7  6  5  4  3  2  1  0
  |FAN | |DIAG| |PSU2| |PSU1|

PSU1 [1:0]:  00=yellow  10=green  11=off
PSU2 [3:2]:  00=yellow  10=green  11=off
DIAG [5:4]:  00=off     01=yellow 10=green
FAN  [7:6]:  01=green   10=yellow 11=off
```

### Locator LED Register (CPLD 0x15)

```
bits[1:0]:
  01 = Off
  11 = Yellow blink
```

### LED State Mapping (dentOS ledi.c)

| LED | Green Condition | Yellow Condition | Off Condition |
|-----|----------------|------------------|---------------|
| PSU1 | PSU1 present + power OK | PSU1 absent or power fail | Manual off |
| PSU2 | PSU2 present + power OK | PSU2 absent or power fail | Manual off |
| DIAG | System healthy | Boot/diagnostic in progress | Not initialized |
| FAN | All fans OK | Fan failure detected | Manual off |
| LOCATOR | N/A | Blink (identification) | Not locating |

---

## 15. Fan Control and Thermal Policy

From dentOS `sysi.c` and `fani.c`:

### Fan Speed Settings

| Level | CPLD Raw | PWM (0-248) | Duty Cycle |
|-------|----------|-------------|------------|
| MIN | 0x0C | 96 | ~40% |
| MID | 0x15 | 168 | ~70% |
| MAX | 0x1F | 248 | 100% |

### Thermal Policy (F2B Airflow)

The thermal management daemon monitors all 11 sensors and adjusts fan speed based on
configurable thresholds. The dentOS `sysi.c` defines temperature targets per sensor:

```
tA = Warning threshold (increase fan)
tB = High threshold (max fan)
tC = Critical threshold (begin shutdown)
tD = Emergency shutdown
tCritical = Absolute maximum
```

### Fan Status Monitoring

```
CPLD reg 0x03:
  bit 2 = Fan tray present (active LOW)
  bit 3 = Fan failure (active HIGH)
  bit 4 = Airflow direction (1=F2B, 0=B2F)

PSU fan status:
  I2C addr 0x3E/0x3D, PMBus STATUS_FAN (0x81), bit 7 = failure
  Fan speed: PMBus FAN_SPEED (0x3B) in RPM
```

---

## 16. BCM56846 in Stratum Project

**Source**: `stratum/stratum`

Stratum (Google's reference P4Runtime implementation for OpenFlow switches) maps BCM56846
to the `TRIDENT_PLUS` chip type:

### bcm.proto
```protobuf
message BcmChip {
  enum BcmChipType {
    UNKNOWN = 0;
    TRIDENT_PLUS = 1;   // BCM56846
    TRIDENT2 = 2;       // BCM56850
    TOMAHAWK = 3;       // BCM56960
    TOMAHAWK_PLUS = 4;  // BCM56965
    TOMAHAWK2 = 5;      // BCM56970
    TOMAHAWK3 = 6;      // BCM56980
  }
}
```

### utils.cc
```cpp
std::string PrintBcmChipNumber(const BcmChip::BcmChipType& chip_type) {
  switch (chip_type) {
    case BcmChip::TRIDENT_PLUS:
      return "BCM56846";
    // ...
  }
}
```

This confirms BCM56846 is the **representative Trident+ chip** in the Stratum ecosystem.

---

## 17. BCM56846 in SONiC

**Source**: `sonic-net/sonic-buildimage`

SONiC includes BCM56846 in its BDE kernel module PCI device table:

```c
#define BCM56846_DEVICE_ID      0xb846
#define BCM56846_A0_REV_ID      1
#define BCM56846_A1_REV_ID      2
```

The SONiC BDE module recognizes BCM56846 as part of the Trident+ family and applies the
same initialization sequence as BCM56840.

---

## 18. OpenMDK BCM56846 SVK Board Config

**Source**: `Broadcom/OpenMDK`, path: `board/config/board_bcm56846_svk.c`

The SVK (System Verification Kit) board configuration defines the reference port mapping
for BCM56846:

### Port Configuration

- **56 ports**, all 10G
- System ports 1-56 map to application ports 9-68 (gap at 53-56)
- DCFG_LCPLL_156 reference clock

### PHY Address Mapping

```c
/* External MIIM bus assignment by port range */
Ports  9-24: EBUS(0), PHY addr = port - 8
Ports 25-40: EBUS(1), PHY addr = port - 24
Ports 41-60: EBUS(2), PHY addr = port - 40
Ports 61-68: EBUS(2), PHY addr = port - 41
```

### WARPcore RX Lane Remap

```c
/* Most ports use 0x1032 (lanes 0,1 swapped with 2,3) */
/* Port 45 is special: uses 0x3210 (no swap) */
if (port == 45)
    lane_swap = 0x3210;
else
    lane_swap = 0x1032;
```

This SVK board config is for the reference design and differs from the AS5610-52X
production board, which uses a different port-to-PHY mapping (confirmed by our SIGDET
probing: Port 49 → PHY 13, Port 50 → PHY 17, Port 51 → PHY 31).

---

## 19. NXP-QorIQ ONL Fork

**Source**: `nxp-qoriq/OpenNetworkLinux`

The NXP fork of ONL contains a near-identical copy of the ONLP platform driver at:
`packages/platforms/accton/powerpc/powerpc-accton-as5610-52x/onlp/builds/src/module/src/`

The files `platform_lib.c`, `platform_lib.h`, `sysi.c`, `sfpi.c` are byte-for-byte
identical to the dentOS/OCP ONL versions, with one minor difference:

- NXP fork uses `strncpy()` instead of `aim_strlcpy()` in `as5610_52x_get_psu_type()`

The NXP ONIE machine directory (`nxp-qoriq/onie/machine/as5610_52x/`) contains the same
DTS and machine.make as the OCP ONIE version.

---

## 20. Open NOS Project Local Files

Files in our `open-nos-as5610` project repo relevant to this reference:

### Platform Configuration

| File | Purpose |
|------|---------|
| `boot/as5610_52x_full.dts` | Full device tree (1314 lines) |
| `boot/as5610_52x_minimal.dts` | Minimal DTS for FIT build |
| `platform/drivers/accton_as5610_cpld.c` | CPLD kernel module (397 lines) |
| `sdk/include/bcm56846_regs.h` | ASIC register definitions (205 lines) |
| `sdk/include/bcm56846.h` | SDK API header |
| `sdk/include/bde_ioctl.h` | BDE ioctl interface |
| `hal/config/as5610.config.bcm` | BCM SDK config (portmap, limits) |

### Build & Boot

| File | Purpose |
|------|---------|
| `onie-installer/cumulus/init/accton_as5610_52x/platform.conf` | Partition layout |
| `onie-installer/cumulus/init/accton_as5610_52x/platform.fdisk` | MBR partition script |
| `onie-installer/uboot_env/as5610_52x.platform.inc` | U-Boot platform env |
| `onie-installer/uboot_env/common_env.inc` | Common U-Boot env |
| `boot/kernel-patches/arch/powerpc/platforms/85xx/accton_as5610_52x.c` | Kernel platform code |

### BDE Kernel Modules

| File | Purpose |
|------|---------|
| `bde/nos_kernel_bde.c` | PCI driver, BAR0, DMA, S-Channel (~400 lines) |
| `bde/nos_user_bde.c` | Userspace /dev/nos-bde character device (~100 lines) |

---

## 21. External Documentation Links

### Edge-Core Official

| Document | URL |
|----------|-----|
| Datasheet (ONIE) | https://www.edge-core.com/_upload/images/AS5610-52X_ONIE_DS_R03_20151029.pdf |
| Datasheet (Cumulus) | https://www.edge-core.com/_upload/images/1604211522050.pdf |
| Installation Guide | https://www.edge-core.com/_upload/images/AS5610-52X_IG-R01_1220.pdf |
| Quick Start Guide | https://www.edge-core.com/_upload/images/AS5610-52X_QSG-R02_150200000722A%20_0104.pdf |
| Product Page | https://www.edge-core.com/productsInfo.php?cls=1&cls2=8&cls3=45&id=28 |

### Open Source Repositories

| Repository | Description | URL |
|-----------|-------------|-----|
| OCP ONL | Official AS5610 ONLP platform | https://github.com/opencomputeproject/OpenNetworkLinux |
| OCP ONIE | ONIE machine definition + kernel patch | https://github.com/opencomputeproject/onie |
| dentOS | AS5610 ONLP platform (dentOS fork) | https://github.com/dentproject/dentOS |
| NXP ONL | NXP QorIQ fork with AS5610 | https://github.com/nxp-qoriq/OpenNetworkLinux |
| Broadcom OpenMDK | BCM56846 chip support | https://github.com/Broadcom/OpenMDK |
| Stratum | BCM56846 as TRIDENT_PLUS | https://github.com/stratum/stratum |
| SONiC | BCM56846 BDE device table | https://github.com/sonic-net/sonic-buildimage |
| Cumulus CPLD | AS5610 CPLD header/driver | https://github.com/sonix-network/platform-modules-cumulus-4.19.y-stable4 |

---

## 22. Cross-Reference: Compatible Strings

Different sources use different device tree compatible strings for the same hardware:

| Component | Compatible String | Source |
|-----------|------------------|--------|
| Machine | `accton,as5610_52x` | Our custom DTS |
| Machine | `accton,5652` | ONIE kernel patch |
| CPLD | `accton,accton_as5610_52x-cpld` | Our DTS, ONL |
| CPLD | `accton,5652-cpld` | ONIE DTS |
| I2C mux (PCA9548) | `ti,pca9548` | All sources |
| I2C mux (PCA9546) | `ti,pca9546` | All sources |
| Thermal (MAX6697) | `nxp,max6697` | Our DTS |
| Thermal (MAX6581) | `maxim,max6581` | ONIE DTS |
| Thermal (MAX1617) | `nxp,max1617` | Our DTS |
| Thermal (NE1617A) | `dallas,ne1617a` | ONIE DTS |
| SFP EEPROM | `at,24c04` | All SFP ports |
| QSFP EEPROM | `sff8436` | QSFP ports only |
| Retimer | `ti,ds100df410` | Our DTS |
| GPIO (PCA9506) | `ti,pca9506` | All sources |
| GPIO (PCA9538) | `ti,pca9538` | Our DTS |
| RTC | `epson,rtc8564` | Our DTS |
| Ethernet PHY | N/A (via MDIO) | BCM5482S at addr 1 |
| NOR Flash | `cfi-flash` | All sources |
| PCIe bridge | `fsl,mpc8548-pcie` | All sources |
| SoC | `fsl,p2020-immr` | All sources |

**Note**: The Cumulus thermal sensor is labeled MAX6581 (8-channel) in their sources, while
our DTS and kernel use MAX6697 (7-channel) driver. The MAX6697 driver is compatible with
MAX6581 and handles the extra channel.

---

## 23. Hardware Revision Notes

### Board Revisions

| Revision | ONIE MACHINE_REV | Changes |
|----------|-----------------|---------|
| r01a | 0 | Original production |
| r01d | 1 | New SDRAM, different oscillator |

### Known Hardware Quirks

1. **Management PHY broken at 1Gb**: ONIE DTS has `accton,broken_1000` property on the
   gianfar ethernet node, suggesting some board revisions have issues with 1Gbps link on
   the management port (BCM5482S).

2. **QSFP port 48/49 presence swap**: The IO expander bits for QSFP port 48 and 49
   presence detection are physically swapped on the PCB. Software must compensate with
   a mapping table.

3. **I2C bus stuck after kill**: Killing processes during I2C transactions can leave SDA
   held low, requiring a full reboot to recover. The CPLD can reset I2C switches via
   register 0x11 bit 1 (`CPLD_RESET_I2C_SWITCH_L`).

4. **BCM56846 warm boot**: After warm reboot from Cumulus, the BCM56846 S-Channel
   interface is locked in DMA ring mode. A cold VDD power cycle is required to restore
   PIO mode. The CPLD can hard-reset the BCM56846 via register 0x10 bit 1
   (`CPLD_RESET_BCM56846_L`).

5. **NOR flash extremely small**: Only 4MB total, with ONIE kernel image capped at
   3.375MB. This is the smallest NOR flash of any modern OCP switch.

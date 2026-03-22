# How the Edgecore AS5610-52X Works: A Complete Technical Reference

**Date**: 2026-03-22
**Source**: Reverse engineering of Cumulus Linux 2.5 + live switch captures + OpenMDK analysis

This document describes, in detail, how every subsystem in the AS5610-52X
functions — from power-on to forwarding the first packet.

---

## Table of Contents

1. [Hardware Overview](#1-hardware-overview)
2. [Power-On and Boot Sequence](#2-power-on-and-boot-sequence)
3. [Kernel Initialization](#3-kernel-initialization)
4. [I2C Bus Topology and Device Discovery](#4-i2c-bus-topology-and-device-discovery)
5. [CPLD and System Management](#5-cpld-and-system-management)
6. [BCM56846 ASIC Architecture](#6-bcm56846-asic-architecture)
7. [PCIe and BAR0 Register Access](#7-pcie-and-bar0-register-access)
8. [BDE: Bridging Kernel and Userspace](#8-bde-bridging-kernel-and-userspace)
9. [ASIC Initialization Sequence](#9-asic-initialization-sequence)
10. [Warpcore SerDes and Port Bringup](#10-warpcore-serdes-and-port-bringup)
11. [MDIO / MIIM Bus Architecture](#11-mdio--miim-bus-architecture)
12. [S-Channel: Programming ASIC Tables](#12-s-channel-programming-asic-tables)
13. [Packet I/O: DMA and TUN Interfaces](#13-packet-io-dma-and-tun-interfaces)
14. [L2 Forwarding](#14-l2-forwarding)
15. [L3 Routing](#15-l3-routing)
16. [DS100DF410 Retimers / Signal Conditioning](#16-ds100df410-retimers--signal-conditioning)
17. [SFP/QSFP Transceiver Management](#17-sfpqsfp-transceiver-management)
18. [LED System](#18-led-system)
19. [Thermal Management](#19-thermal-management)
20. [ONIE and Installation](#20-onie-and-installation)

---

## 1. Hardware Overview

The AS5610-52X is a 1U top-of-rack switch with:

```
┌─────────────────────────────────────────────────────────────────────┐
│ FRONT PANEL                                                         │
│                                                                     │
│ [SFP+] [SFP+] ... [SFP+]  [QSFP+] [QSFP+] [QSFP+] [QSFP+]      │
│  swp1   swp2       swp48    swp49   swp50    swp51    swp52        │
│  10GbE  10GbE      10GbE    40GbE   40GbE    40GbE    40GbE        │
│                                                                     │
│ [STATUS LEDs: PSU1 PSU2 FAN SYS]  [CONSOLE RJ45]  [MGMT ETH]     │
└─────────────────────────────────────────────────────────────────────┘
```

### Key Components

| Chip | Part Number | Function | Bus |
|------|-------------|----------|-----|
| CPU | Freescale P2020E | Dual-core PowerPC e500v2, 1.2GHz | - |
| Switch ASIC | Broadcom BCM56846_A1 | Trident+ 720Gbps switching | PCIe x4 |
| CPLD | Accton custom | System management (LEDs, PSU, fan, watchdog) | LocalBus |
| NOR Flash | 4MB | ONIE bootloader + U-Boot | LocalBus |
| USB Flash | 4GB | Root filesystem | USB 2.0 |
| DRAM | 2GB DDR3 | System memory | DDR bus |
| RTC | Epson RTC8564 (PCF8563) | Real-time clock | I2C bus 2 |
| Retimers | TI DS100DF410 x32 | 10G signal conditioning | I2C |
| Temp Sensors | Maxim MAX6697 + MAX1617 | Board temperature | I2C bus 9 |
| I2C Muxes | NXP PCA9548 x7, PCA9546 x3 | 70-bus I2C tree | I2C |
| GPIO Expanders | NXP PCA9506 x5, PCA9538 x4 | SFP/QSFP control | I2C |
| Mgmt PHY | Broadcom BCM5461 | 1GbE management port | MDIO |

### Internal Block Diagram

```
                    ┌──────────────────┐
                    │   P2020 CPU      │
                    │  (e500v2 x2)     │
                    │                  │
                    │  DDR3   NOR      │
                    │  2GB    4MB      │
                    └─┬──┬──┬──┬──┬───┘
                      │  │  │  │  │
              ┌───────┘  │  │  │  └──────────┐
              │          │  │  │              │
         PCIe x4     I2C x2 │ LocalBus    USB EHCI
              │          │   │    │           │
    ┌─────────┴──┐   ┌──┴───┴┐  ┌┴────┐   ┌──┴──┐
    │  BCM56846  │   │ 70-bus │  │CPLD │   │ USB │
    │ Trident+   │   │ I2C   │  │     │   │Flash│
    │            │   │ tree   │  │LEDs │   │ 4GB │
    │ 14 xlport  │   │       │  │PSU  │   └─────┘
    │ 56 lanes   │   │       │  │Fan  │
    │ 2 LED proc │   │       │  │WDog │
    └────────────┘   │       │  └─────┘
                     │       │
         ┌───────────┴───────┴──────────┐
         │                              │
    ┌────┴────┐  ┌───────┐  ┌──────────┐
    │ 48 SFP+ │  │ 4 QSFP│  │ 32 DS100 │
    │ EEPROMs │  │EEPROMs│  │ retimers │
    │ 24C04   │  │SFF8436│  │ DF410    │
    └─────────┘  └───────┘  └──────────┘
```

---

## 2. Power-On and Boot Sequence

### U-Boot (First Stage)

The P2020's BootROM loads U-Boot from NOR flash at physical address `0xefc00000`.
U-Boot version is 2013.01 (very old, specific to this platform).

```
Power on
  → P2020 BootROM executes from NOR flash reset vector
    → U-Boot 2013.01 starts
      → Initializes DDR3 (2GB)
      → Initializes UART (ttyS0 at 115200 baud)
      → Scans USB for boot media
      → Executes bootcmd:
          run check_boot_reason    ← if onie_boot_reason set, boot ONIE
          run nos_bootcmd          ← boot the NOS
          run onie_bootcmd         ← fallback to ONIE
```

### U-Boot Environment Variables (Critical)

The AS5610 U-Boot has a specific boot chain. Key variables from the live switch:

```
bootcmd=run check_boot_reason; run nos_bootcmd; run onie_bootcmd

check_boot_reason=if test -n $onie_boot_reason; then
    setenv onie_bootargs boot_reason=$onie_boot_reason;
    run onie_bootcmd;
fi

nos_bootcmd=if test -n $bootsource; then
    run lbootcmd;
else
    run bootorder1;
fi
```

The NOS boot chain ultimately runs:
```
usb start
usbiddev                    ← detect USB device number
usbboot $loadaddr ${usbdev}:5    ← load FIT image from partition 5
bootm $loadaddr#accton_as5610_52x ← boot with named FIT configuration
```

### Critical U-Boot Quirks

1. **`fdt_high=0xffffffff`**: Must be set. Without this, U-Boot tries to relocate
   the device tree above physical memory, causing a hang on P2020.

2. **`initrd_high=0xffffffff`**: Same issue for initramfs.

3. **`onie_boot_reason` must be EMPTY (deleted)**: If set to ANY value (even "nos"),
   U-Boot's `check_boot_reason` sees a non-empty string and boots ONIE instead.

4. **`usbboot` not `usb read`**: The proven command on this U-Boot build is
   `usbboot $loadaddr ${usbdev}:N` which reads partition N as raw data.
   `usb read` (raw sector access) may not be available.

### FIT Image Format

The kernel, device tree, and initramfs are packaged in a Flattened Image Tree:

```
FIT Image (uImage-powerpc.itb on sda5)
├── kernel: gzip-compressed vmlinux
│   load = <0x00000000>
│   compression = gzip
├── accton_as5610_52x_dtb: device tree blob
│   load = <0x00f00000>
├── initramfs: cpio.gz (optional, can be stub)
│   load = <0x01000000>
└── configuration "accton_as5610_52x":
    kernel + fdt + ramdisk
```

U-Boot loads the FIT from sda5, selects the `accton_as5610_52x` configuration,
and calls `bootm` which decompresses the kernel, places the DTB, and jumps
to the kernel entry point.

### Disk Partition Layout

```
/dev/sda (4GB USB flash)
├── sda1:  128 MB  ext2     Persistent config (/mnt/persist)
├── sda2:  (extended container)
│   ├── sda5:  16 MB   raw  FIT image (kernel + DTB + initramfs)
│   ├── sda6:  128 MB  raw  Root filesystem (squashfs)
│   ├── sda7:  16 MB   raw  FIT image slot 2 (Cumulus dual-boot)
│   └── sda8:  128 MB  raw  Rootfs slot 2 (Cumulus dual-boot)
└── sda3:  ~3.3 GB ext2     RW overlay (overlayfs upper layer)
```

---

## 3. Kernel Initialization

The kernel (`Linux 5.10.224` or Cumulus's `3.2.60`) boots on the P2020:

1. **CPU init**: e500v2 core, SMP with 2 cores, SPE (signal processing engine)
2. **Device tree parse**: discovers all peripherals from the DTB
3. **Early console**: `ttyS0` at `0xff704500` (16550A UART)
4. **Memory**: 2GB DDR3, HIGHMEM enabled
5. **PCIe**: enumerate bus, find BCM56846 at `0001:01:00.0`
6. **I2C**: two MPC I2C controllers at `0xff703000` and `0xff703100`
7. **USB**: EHCI at `0xff722000`, discover USB flash as `/dev/sda`
8. **Ethernet**: gianfar at `0xff724000`, management port `eth0`
9. **LocalBus**: NOR flash at `0xefc00000`, CPLD at `0xea000000`

### Module Loading Order

After the kernel boots, systemd (or init scripts) loads platform modules:

```
1.  linux-kernel-bde     ← BCM56846 PCI driver + DMA pool (MUST BE FIRST)
2.  linux-user-bde       ← Userspace BDE bridge
3.  tun                  ← TUN/TAP for 52 switch port interfaces
4.  accton_as5610_52x_cpld ← CPLD sysfs interface
5.  at24                 ← EEPROM driver (board + 48 SFP + 4 QSFP)
6.  sff_8436_eeprom      ← QSFP EEPROM pages
7.  gpio-pca953x         ← GPIO expanders (SFP TX disable, QSFP reset)
8.  max6697              ← 7-channel temperature sensor
9.  adm1021              ← 2-channel temperature sensor (MAX1617)
10. ds100df410           ← Retimer/equalizer (32 devices)
```

---

## 4. I2C Bus Topology and Device Discovery

The AS5610 has a 3-level I2C mux tree creating 70 buses:

### Level 0: Physical Controllers

| Controller | P2020 Address | Linux Bus |
|-----------|--------------|-----------|
| I2C0 | `0xff703000` | i2c-0 |
| I2C1 | `0xff703100` | i2c-1 |

### Level 1: Root Muxes

```
I2C-0
  └── PCA9548 @ 0x70 (8-channel) → buses 2-9
        ├── ch0 → bus 2: RTC (PCF8563 @ 0x51)
        ├── ch1 → bus 3: Board EEPROMs (24c02 @ 0x3a, 0x3e, 0x78)
        ├── ch2 → bus 4: PSU/FRU EEPROMs (24c02 @ 0x0c, 0x39, 0x3d, 0x78)
        └── ch7 → bus 9: Temp sensors (MAX6697 @ 0x4d, MAX1617 @ 0x18)

I2C-1
  ├── PCA9546 @ 0x75 (4-ch) → buses 10-13 (SFP group A)
  ├── PCA9546 @ 0x76 (4-ch) → buses 14-17 (SFP group B + GPIO)
  └── PCA9546 @ 0x77 (4-ch) → buses 18-21 (QSFP ports)
```

### Level 2: Per-Port Muxes

Each PCA9546 channel connects to a PCA9548 (8-channel), giving 8 buses per group.
Six PCA9548 muxes at address 0x74 create buses 22-69 for individual SFP+ ports.

### Per-Port Devices

Each SFP+ port bus (22-69) has:
- **0x50**: SFP EEPROM (24c04, SFF-8472 A0 page) — vendor, part, serial, wavelength
- **0x51**: SFP diagnostic page (A2) — temperature, TX power, RX power
- **0x27**: DS100DF410 retimer (on 32 of 48 buses)

Each QSFP port bus (18-21) has:
- **0x50**: QSFP EEPROM (SFF-8436) — multi-page, 4-lane diagnostics
- **0x27**: DS100DF410 retimer

### GPIO Expanders

Bus 16 and 17 have GPIO expanders for SFP/QSFP control:

| Bus | Chip | Address | GPIO Base | Function |
|-----|------|---------|-----------|----------|
| 16 | PCA9506 | 0x20 | gpio24 | SFP TX disable (ports 1-40) |
| 16 | PCA9506 | 0x21 | gpio64 | SFP TX disable (ports 41-48) |
| 16 | PCA9538 | 0x70 | gpio144 | QSFP1 reset/lpmode/modsel/presence |
| 16 | PCA9538 | 0x71 | gpio152 | QSFP2 control |
| 16 | PCA9538 | 0x72 | gpio160 | QSFP3 control |
| 16 | PCA9538 | 0x73 | gpio168 | QSFP4 control |
| 17 | PCA9506 | 0x20 | gpio104 | SFP presence detect |
| 17 | PCA9506 | 0x23 | gpio176 | SFP RX loss-of-signal |
| 17 | PCA9506 | 0x24 | gpio216 | SFP TX fault |

To enable an SFP+ port's laser, you:
1. Set TX_DISABLE low (gpio24 + port_index, output, value=0)
2. Check PRESENCE (gpio104 + port_index, input, value=0 means present)
3. Check RX_LOS (gpio176 + port_index, input, value=0 means signal OK)
4. Check TX_FAULT (gpio216 + port_index, input, value=0 means no fault)

---

## 5. CPLD and System Management

The Accton CPLD is memory-mapped via the P2020's LocalBus at physical address
`0xea000000`. The `accton_as5610_52x_cpld` kernel module creates sysfs files at
`/sys/devices/ff705000.localbus/ea000000.cpld/`.

### CPLD Register Map

| Register | Type | Values | Purpose |
|----------|------|--------|---------|
| `board_revision` | R | "0.2:7-eng" | Model.HWrev:CPLDver |
| `psu_pwr1_present` | R | 0/1 | PSU1 installed |
| `psu_pwr1_dc_ok` | R | 0/1 | PSU1 output OK |
| `psu_pwr1_all_ok` | R | 0/1 | PSU1 fully operational |
| `psu_pwr2_present` | R | 0/1 | PSU2 installed |
| `psu_pwr2_dc_ok` | R | 0/1 | PSU2 output OK |
| `system_fan_present` | R | 0/1 | Fan tray installed |
| `system_fan_ok` | R | 0/1 | Fan running normally |
| `system_fan_air_flow` | R | front-to-back / back-to-front | Airflow direction |
| `system_dc_power_ok` | R | 0/1 | System DC rail OK |
| `system_all_ok` | R | 0/1 | fan_present AND fan_ok AND dc_power_ok |
| `led_psu1` | RW | green/yellow/off | PSU1 status LED |
| `led_psu2` | RW | green/yellow/off | PSU2 status LED |
| `led_fan` | RW | green/yellow/off | Fan status LED |
| `led_diag` | RW | green/yellow/off | System diagnostic LED |
| `led_locator` | RW | amber_blinking/off | Locator LED |
| `pwm1` | RW | 0-248 | Fan speed (PWM duty cycle) |
| `pwm1_enable` | RW | 0/1 | PWM enable (always 1) |
| `watch_dog_enable` | RW | 0/1 | Hardware watchdog enable |
| `watch_dog_timeout` | RW | 8-512 sec | Watchdog NMI timeout |
| `watch_dog_keep_alive` | W | any int | Pet the watchdog |

### Watchdog Behavior

If `watch_dog_enable=1` and `watch_dog_keep_alive` is not written within
`watch_dog_timeout` seconds:
1. First timeout: Non-maskable interrupt (NMI) to CPU
2. Second timeout: Full board hardware reset

---

## 6. BCM56846 ASIC Architecture

The BCM56846 is a variant of Broadcom's Trident+ (TD+) switching ASIC family.
It shares the BCM56840 base design.

### Key Specs

| Feature | Value |
|---------|-------|
| Device ID | 0xb846, Revision 0x02 |
| Switching capacity | 720 Gbps |
| Port configuration | 48x10G + 4x40G (56 lanes total) |
| L2 table size | 32K entries (hash-based, 4-way associative) |
| L3 table size | 16K IPv4 routes (DEFIP/LPM) |
| ECMP groups | 1K groups, 64 members each |
| Buffer | 46,080 cells (208 bytes/cell = 9.6 MB) |
| Packet processing | Ingress pipeline → MMU → Egress pipeline |
| SerDes | 14 Warpcore WC-B0 blocks (4 lanes each) |
| CMIC | CMICm architecture (PIO indirect for some regs) |

### Internal Architecture

```
┌──────────────────────────────────────────────────────────┐
│                      BCM56846                             │
│                                                          │
│  ┌─────────┐  ┌────────────────────┐  ┌─────────┐       │
│  │  CMIC   │  │  Ingress Pipeline  │  │   MMU   │       │
│  │ (host   │  │                    │  │(memory  │       │
│  │ interface│  │  Parser → Lookup  │  │ mgmt    │       │
│  │ PCIe)   │  │  → FP → Modify    │  │ unit)   │       │
│  └────┬────┘  └────────┬───────────┘  └────┬────┘       │
│       │                │                    │            │
│       │         ┌──────┴──────┐      ┌─────┴─────┐      │
│       │         │   Tables    │      │  Buffers  │      │
│       │         │ L2, L3, FP  │      │ 46K cells │      │
│       │         │ VLAN, STG   │      │ 9.6 MB    │      │
│       │         └─────────────┘      └───────────┘      │
│       │                                                  │
│  ┌────┴────────────────────────────────────────────┐     │
│  │              Egress Pipeline                     │     │
│  │  Lookup → Modify → Queue → Schedule → MAC → PHY│     │
│  └──────────────────────────────────────────────────┘     │
│                                                          │
│  ┌──────────────────────────────────────────────────┐     │
│  │             14 x Warpcore SerDes                  │     │
│  │  xlport0..17 (4 lanes each = 56 lanes total)    │     │
│  │  Each WC: PLL, firmware uC, TX/RX per lane      │     │
│  └──────────────────────────────────────────────────┘     │
│                                                          │
│  ┌────────┐  ┌────────┐                                  │
│  │ LED    │  │ LED    │  2 LED processors (256B program) │
│  │ proc 0 │  │ proc 1 │  30Hz, serial shift to front LED│
│  └────────┘  └────────┘                                  │
└──────────────────────────────────────────────────────────┘
```

---

## 7. PCIe and BAR0 Register Access

The BCM56846 appears on PCIe bus `0001:01:00.0` with:
- BAR0: 256KB at physical `0xa0000000`
- IRQ: 16 (shared)
- Vendor: 0x14e4 (Broadcom)
- Device: 0xb846

### BAR0 Memory Map

The 256KB BAR0 space is split into two access windows:

```
Offset Range        Access Method           Contents
──────────────────────────────────────────────────────
0x00000 - 0x00FFF   Direct word access      CMIC core (MIIM, IRQ, config)
0x00100 - 0x004FF   Direct word access      MIIM registers (MDIO PHY access)
0x00000 - 0x03FFF   Direct word access      XLPORT block 0 (MAC/PHY regs)
0x04000 - 0x07FFF   Direct word access      XLPORT block 1
  ...                                        (repeat every 0x4000 for 14 xlports)
0x10000 - 0x103FF   Direct word access      CMIC_COMMON (mirror of 0x000)
0x10200 - 0x10214   Direct word access      SBUS ring map
0x31000 - 0x31FFF   CMICm PIO indirect      PKTDMA (packet DMA channels)
0x32000 - 0x32FFF   CMICm PIO indirect      SBUSDMA channels
0x32800 - 0x328FF   CMICm PIO indirect      S-Channel message registers
0x33000 - 0x33FFF   CMICm PIO indirect      CMC2 S-Channel
0x38000 - 0x3FFFF   CMICm PIO indirect      LED processor memory
```

### The CMICm PIO Problem

On the AS5610 (P2020 PPC host), CMIC registers above 0x10000 use the
**CMICm PIO indirect access** window. Direct 32-bit reads to these addresses
return a **repeating byte-level pattern** (e.g., `0xb3, 0x84, 0x4a, 0x84`)
instead of the actual register values.

This is because:
1. The P2020's PCIe outbound window maps BAR0 as a flat memory region
2. CMICm registers above 0x10000 require a multi-step PIO access protocol
3. Direct `lwz`/`stw` instructions don't trigger the PIO protocol correctly

**Solution**: Use `ioread32()`/`iowrite32()` from the kernel BDE module, which
includes proper PPC MMIO barriers (`eieio`/`sync`). The BDE provides ioctl-based
register access that handles this transparently.

### The XLPORT Direct Window

Registers below 0x10000 are in the "direct access window" and work correctly
via simple mmap. This includes:
- MIIM registers (0x150-0x4a0) — used for MDIO PHY access
- XLPORT MAC registers (repeating at 0x4000 intervals)
- Port configuration, statistics counters

The Cumulus switchd uses mmap for ALL register access (confirmed via strace —
no BDE register ioctls, only WAIT_FOR_INTERRUPT and SEM_OP). This works because
Cumulus's SDK has the PIO protocol implemented in its register access functions.

---

## 8. BDE: Bridging Kernel and Userspace

The BDE (Broadcom Device Enumerator) is a kernel module that provides:

1. **PCI enumeration**: Finds BCM56846 on the PCIe bus
2. **BAR0 mapping**: `pci_ioremap_bar()` with kernel MMIO accessors
3. **DMA pool**: `dma_alloc_coherent()` for packet buffer memory
4. **Interrupt handling**: `request_irq()` for DMA completion notification
5. **Userspace interface**: `/dev/linux-kernel-bde` char device

### Kernel BDE Architecture

```
Userspace (switchd)                     Kernel (linux-kernel-bde.ko)
─────────────────────                   ─────────────────────────────
open("/dev/linux-kernel-bde")    →     bde_open()
ioctl(BDE_IOC_DEV_INFO)         →     return PCI device info
ioctl(BDE_IOC_REG_READ, addr)   →     ioread32(bar0 + addr)
ioctl(BDE_IOC_REG_WRITE, addr)  →     iowrite32(val, bar0 + addr)
ioctl(BDE_IOC_DMA_ALLOC)        →     return DMA pool phys addr
mmap(fd, BAR0_PHYS)             →     io_remap_pfn_range() [BAR0]
mmap(fd, DMA_PHYS)              →     dma_mmap_coherent() [DMA pool]
ioctl(BDE_IOC_WAIT_INTR)        →     wait_event_interruptible()
```

### DMA Pool

The BDE allocates a 32MB DMA pool via `dma_alloc_coherent()`. This memory is:
- **Physically contiguous**: required for DMA engine
- **Cache-coherent**: CPU writes are immediately visible to ASIC DMA
- **Mapped to both kernel and userspace**: kernel handles allocation,
  userspace accesses via mmap

The DMA pool is used for:
- TX/RX packet buffers (2KB each, ~16 RX descriptors)
- DMA Control Blocks (DCBs) — 64 bytes each, describe packet buffers
- S-Channel DMA message buffers

---

## 9. ASIC Initialization Sequence

When switchd starts, it initializes the BCM56846 via OpenMDK's BMD API:

### Step 1: bmd_reset()

```
1. Read CMIC_DEV_REV_ID → verify 0xb846 rev 02
2. Soft reset: write CMIC_CONFIG reset bit
3. Wait for reset complete (poll CMIC_CONFIG)
4. Program SBUS ring map (CMIC_SBUS_RING_MAP_0..5):
     Block 0 = ring 0 (CMIC)
     Block 1 = ring 13 (TOP/misc)
     Block 2 = ring 7 (MMU)
     Blocks 10-11 = ring 1-2 (IPIPE)
     Block 12 = ring 5 (EPIPE)
     Blocks 14-36 = ring 3-4 (XLPORT groups A/B)
5. Wait for PLL lock (LCPLL at 156.25 MHz reference)
6. Initialize TCAM, memory BIST
```

### Step 2: bmd_init()

```
1. Port mapping: physical ↔ logical ↔ MMU port assignment
     ING_PHYS_TO_LOGIC_MAPm, EGR_LOGIC_TO_PHYS_MAPr, MMU_TO_PHYS_MAPr
2. TDM calendar programming (time-division for port scheduling)
3. For EACH xlport (14 blocks, 56 lanes):
     → _warpcore_init_stage_0:
        a. Stop PLL sequencer (XGXSCONTROLr START_SEQUENCER=0)
        b. Set TX FIR taps (CL72_DEBUG_4r TAP_V2_VAL=9)
        c. Configure VCO frequency (MISC1r FORCE_PLL_MODE_AFE)
        d. Download Warpcore firmware v0x0101 (30KB, 8051 microcode)
           via COMMANDr/WRDATAr/RAMWORDr sequence
        e. Start PLL sequencer (XGXSCONTROLr START_SEQUENCER=1)
     → _warpcore_init_stage_1:
        a. Check firmware CRC via VERSIONr
     → _warpcore_init_stage_2:
        a. Wait for PLL lock
        b. Configure clock compensation (RX66_CONTROLr)
        c. Configure 64/66 encoding (RX66_SCW registers)
        d. Disable PLL powerdown (CONTROL1000X1r)
        e. Set FIFO elasticity (CONTROL1000X3r)
        f. Configure CL73 BAM auto-negotiation
4. MMU buffer allocation:
     46,080 total cells across 4 service pools
5. Enable packet DMA channels
```

### Step 3: bmd_switching_init()

```
1. Create VLAN 1 with all ports as untagged members
2. Set PVID=1 on every port (PORT_TABm)
3. Enable hardware MAC learning
4. Configure L2 aging timer
5. Set MAC_RSV_MASK for reserved MAC handling
6. Add CPU port to EPC_LINK_BMAP
```

### Step 4: Per-port bmd_port_mode_set()

```
For each port:
  1. Set preferred line interface (SFI for 10G, KR for 40G)
  2. Drain TX pipeline (FLUSH_CONTROLr, wait for XLP_TXFIFO_CELL_CNTr=0)
  3. Update PHY speed via bmd_port_mode_to_phy():
     → bcmi_warpcore_xgxs_speed_set():
       a. Select speed mode (FV_fdr_10G_XFI or FV_fdr_40G_KR4)
       b. Set PLL divider (div66 for 10G)
       c. Configure firmware mode (SFP_DAC for SFI, default for XFI)
       d. Write MISC1r FORCE_SPEED, MISC3r FORCE_SPEED_B5
       e. Restart PLL sequencer
  4. Reset MAC (COMMAND_CONFIGr SW_RESET=1)
  5. Configure XMAC (speed, duplex, XMAC_MODEr)
  6. Update XLPORT mode (PHY_PORT_MODE for 1/2/4 lane)
  7. Enable MAC RX (XMAC_CTRLr RX_EN=1)
  8. Add port to EPC_LINK_BMAP
```

### Step 5: TX driver configuration

```
For each port:
  PHY_CONFIG_SET(pc, PhyConfig_TxIDrv, 2)    → idriver=2
  PHY_CONFIG_SET(pc, PhyConfig_TxPreIDrv, 3) → predriver=3

  This writes TXB_TX_DRIVERr via the OpenMDK Warpcore driver:
    bcmi_warpcore_xgxs_config_set()
      → READ TXB_TX_DRIVERr
      → SET IDRIVERf = 2
      → WRITE TXB_TX_DRIVERr

  Works because OpenMDK firmware v0x0101 does NOT intercept these writes.
  (Cumulus firmware v0x0103 uses a firmware mailbox protocol instead.)
```

---

## 10. Warpcore SerDes and Port Bringup

Each Warpcore (WC-B0) block contains:
- 4 SerDes lanes (each capable of 10.3125 Gbps)
- A shared PLL (configurable for different line rates)
- An embedded 8051 microcontroller (runs firmware)
- TX driver with configurable pre-emphasis, amplitude, and slew rate
- RX equalizer with adaptive DFE

### Warpcore Internal Structure

```
┌─────────────────────────────────────────┐
│           Warpcore WC-B0                 │
│                                          │
│  ┌──────────────────────────────┐        │
│  │      8051 Microcontroller    │        │
│  │  Firmware v0x0101 (OpenMDK)  │        │
│  │  Controls: TX driver, AN,    │        │
│  │  link training, adaptation   │        │
│  └──────────────────────────────┘        │
│                                          │
│  ┌─────────┐  ┌─────┐  ┌──────────┐     │
│  │   PLL   │  │ AER │  │ Digital  │     │
│  │156.25MHz│  │(lane│  │ control  │     │
│  │ → 10.3G │  │ sel)│  │ (64/66)  │     │
│  └─────────┘  └─────┘  └──────────┘     │
│                                          │
│  ┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐│
│  │Lane 0 │ │Lane 1 │ │Lane 2 │ │Lane 3 ││
│  │TX  RX │ │TX  RX │ │TX  RX │ │TX  RX ││
│  │driver │ │driver │ │driver │ │driver ││
│  │  EQ   │ │  EQ   │ │  EQ   │ │  EQ   ││
│  └───────┘ └───────┘ └───────┘ └───────┘│
└─────────────────────────────────────────┘
```

### MDIO PHY Address Map

The 14 Warpcore blocks are accessed via 3 internal MDIO buses using 6 PHY addresses:

| BUS | PHY Addresses | xlport Blocks | Ports |
|-----|--------------|---------------|-------|
| 0 | 1, 5, 9, 13 | xlport0-5 | swp9-28 (SFP+) |
| 1 | 1, 5, 9, 13, 21 | xlport6-11 | swp29-48 (SFP+), swp50,52 (QSFP) |
| 2 | 1, 9, 13, 17, 21 | xlport12-17 | swp1-8 (SFP+), swp49,51 (QSFP) |

PHY ID encoding for `soc_miim_read/write`:
```
phy_id = (internal << 7) | (bus << 5) | phy_addr
```
Examples: xe0 = 0xd1 (BUS2, INT, PHY17), xe4 = 0xb5 (BUS0, INT, PHY21)

### Port-Up Sequence (from MIIM Capture)

When a port is brought up (`ip link set swpN up`), switchd performs:

```
PHASE 1: TX Configuration (page 0x0000)
  reg[0x17] = 0x8010   TX misc control (drive strength)
  reg[0x18] = 0x8370   TX amplitude/pre-emphasis (3x for reliability)

PHASE 2: IEEE Block Enable (page 0x0008)
  reg[0x1e] = 0x8000   Enable IEEE extended features

PHASE 3: AN/Clock Recovery (page 0xE000/0x1000)
  reg[0x18] = 0x8010   Clock recovery config (3x)

PHASE 4: AER + SerDes Digital (page 0x0AEE)
  reg[0x10] = 0xFFE0   All SerDes digital features enabled (fiber, 10G)
  reg[0x14] = 0x81D0   Extended digital control

PHASE 5: RX Equalization (page 0x0000)
  reg[0x11] = 0x81D0   RX control
  reg[0x19] = 0x8320   RX EQ coefficient A
  reg[0x1a] = 0x8320   RX EQ coefficient B
  reg[0x1b] = 0x8320   RX EQ coefficient C
  reg[0x1d] = 0x8350   RX EQ coefficient D

PHASE 6: Core Sequencer Start (page 0x3800)
  reg[0x01] = 0x0010   Start PLL sequencer (bit 4)

PHASE 7: Steady-State Link Polling (every 30ms)
  page 0x1800 → read reg[0x01] (MII_STATUS) for link state
  page 0x0000 → maintenance writes (reg[0x15], reg[0x10], reg[0x1e])
```

---

## 11. MDIO / MIIM Bus Architecture

The BCM56846's CMIC provides an MDIO master for accessing the internal Warpcore
SerDes PHYs. This is NOT the same as the management port's MDIO.

### CMIC MIIM Registers

| Register | BAR0 Offset | Function |
|----------|-------------|----------|
| CMIC_MIIM_PARAM | 0x158 | Transaction parameters |
| CMIC_MIIM_ADDRESS | 0x4a0 | Clause-22 register address (triggers transaction) |
| CMIC_MIIM_READ_DATA | 0x160 | Read result (16-bit) |
| CMIC_MIIM_STAT | 0x15c | Status (bit 0 = DONE) |

### MIIM_PARAM Format

```
Bits [31:26]: reserved
Bit  [25]:    INTERNAL_SEL (1 = internal MDIO, always 1 for Warpcore)
Bits [24:22]: BUS_ID (0-2 for the 3 internal MDIO buses)
Bit  [21]:    C45_SEL (0 = clause-22, 1 = clause-45)
Bits [20:16]: PHY_ADDR (5 bits)
Bits [15:0]:  DATA (0 = READ, non-zero = WRITE data)
```

### Warpcore Register Access via Clause-22

Warpcore registers use a two-step access:
1. Write `PAGE_SELECT` (cl22 reg 0x1f) with the block address
2. Read/write the target register (cl22 reg 0x10-0x1e)

The WC register address maps to clause-22 as:
```
block = wc_addr & 0xFFF0    → write to PAGE_SELECT (reg 0x1f)
reg   = 0x10 | (wc_addr & 0x000F)  → access via cl22 register
```

### Safety Rule

**NEVER write to MIIM_PARAM or MIIM_ADDRESS directly from userspace.**

Our RE testing proved that direct writes to these registers from Python `/dev/mem`
or GDB cause soft lockups in `ledmgrd` (which also uses MDIO for LED data).
The MDIO bus has no hardware arbitration — concurrent access from multiple
sources corrupts in-flight transactions.

Safe approaches:
- **GDB `awatch`** on MIIM_ADDRESS (passive observation, no bus contention)
- **Call switchd's `soc_miim_read/write`** via GDB (uses SDK's bus locking)
- **BDE ioctl** from the kernel module (includes proper MMIO barriers)

---

## 12. S-Channel: Programming ASIC Tables

The S-Channel (SBUS channel) is the primary interface for reading/writing
ASIC internal tables (L2, L3, VLAN, FP, counters).

### S-Channel Message Format

```
Word 0 (Header):
  Bits [31:26]: Opcode (0x07=READ_MEM, 0x0a=WRITE_MEM, 0x0b=WRITE_REG, etc.)
  Bits [25:19]: Destination block ID
  Bits [18:16]: Access type
  Bits [15:7]:  Data length (in bytes)
  Bit  [4]:     DMA flag
  Bits [1:0]:   Bank select

Word 1: Address / register offset
Words 2+: Data payload (for writes)
```

### S-Channel Operation (via soc_schan_op at 0x108623e4)

```
Function signature: soc_schan_op(unit, schan_msg_ptr, dwc_write, dwc_read)

1. Write SCHAN_MSG words to CMIC_CMC0_SCHAN_MSG registers
2. Write SCHAN_CTRL = MSG_START
3. Poll SCHAN_CTRL for MSG_DONE
4. Read response from SCHAN_MSG registers
```

### S-Channel Operation Types (from live capture)

| Opcode | Name | Count | Purpose |
|--------|------|-------|---------|
| 0x07 | READ_MEMORY | 224 | Table entry reads |
| 0x0b | WRITE_REGISTER | 470 | Register writes to ASIC blocks |
| 0x0d | WRITE_REGISTER_ACK | 66 | ASIC acknowledgment responses |

### Key Tables

| Table | ID | Entry Size | Function |
|-------|----|-----------|----------|
| L2_USER_ENTRY | 0x1547 | 36 bytes | MAC forwarding table |
| L3_DEFIP | 0x22d3 | varies | IPv4 routing (LPM) |
| VLAN_TAB | direct reg | 4 bytes/VLAN | VLAN port membership |
| EGR_VLAN | direct reg | 4 bytes/VLAN | Egress VLAN (untag bitmap) |
| FP_TCAM | varies | 59 bytes | ACL/filter entries |
| STG_TAB | varies | 2 bits/port | STP state per port |

---

## 13. Packet I/O: DMA and TUN Interfaces

### Architecture

```
             KERNEL                              USERSPACE (switchd)
    ┌──────────────────────┐           ┌──────────────────────────┐
    │   Network Stack      │           │                          │
    │   (routing, ARP,     │           │   switchd                │
    │    bridging)         │           │                          │
    │         │            │           │   ┌────────────────┐     │
    │    ┌────┴────┐       │           │   │  packet_io.c   │     │
    │    │ TUN/TAP │←──────┼───────────┼──→│                │     │
    │    │ swp1..52│       │   read()  │   │ TX: TUN read   │     │
    │    └─────────┘       │   write() │   │  → bmd_tx()    │     │
    │         52 fds       │           │   │  → DMA → ASIC  │     │
    │         fd = 19+swp  │           │   │                │     │
    └──────────────────────┘           │   │ RX: bmd_rx_poll│     │
                                       │   │  → DMA ← ASIC │     │
                                       │   │  → TUN write   │     │
                                       │   └────────────────┘     │
                                       └──────────────────────────┘
```

### TUN Interface Mapping

switchd creates 52 TUN/TAP interfaces, one per switch port:
```
fd = 19 + swp_number
fd 20 = swp1  (MAC 80:a2:35:81:ca:af)
fd 69 = swp50 (MAC 80:a2:35:81:ca:e3)
fd 71 = swp52 (MAC 80:a2:35:81:ca:eb)
```

### TX Path (kernel → ASIC)

```
1. Kernel generates packet on swpN (e.g., ARP request)
2. switchd reads from TUN fd via select() + read()
3. Allocate DMA-coherent buffer from BDE pool
4. Copy packet data into DMA buffer
5. Build bmd_pkt_t:
     .port = logical port number
     .data = DMA buffer virtual address
     .baddr = DMA buffer physical address
     .size = packet length
6. Call bmd_tx(unit, &pkt):
     a. Allocate TX DCB (DMA Control Block) from DMA pool
     b. Build SOBMH (Stream-of-Bytes Module Header):
        - sob[0] = 0xff000000 (marker)
        - sob[1] = 0x00000100 (unicast)
        - sob[2] = logical_port (destination)
     c. Set DCB: address = DMA phys, byte_count, SG/chain bits
     d. Start DMA: write DCB address to CMICM_DMA_DESC(ch0)
     e. Poll DMA completion: read CMICM_DMA_STAT
7. Free DMA buffer
```

### RX Path (ASIC → kernel)

```
1. Pre-allocate 16 RX DMA buffers (2048 bytes each)
2. Submit to ASIC via bmd_rx_start() for each buffer:
     a. Build RX DCB with buffer physical address
     b. Chain DCBs into circular ring
     c. Write ring base to CMICM_DMA_DESC(ch1)
     d. Start RX DMA
3. Poll loop (called from main loop):
     a. bmd_rx_poll() checks for completed RX DCBs
     b. On completion: DCB contains ingress port, byte count, status
     c. Map ASIC port → swpN via portmap
     d. Write packet to TUN fd: write(swp_fd, data, len)
     e. Re-submit buffer to DMA ring
```

### DCB (DMA Control Block) Format — Type 21 (Trident+)

Each DCB is 64 bytes (16 x 32-bit words):

| Word | Field | Description |
|------|-------|-------------|
| 0 | ADDR | Physical address of packet buffer |
| 1 | CTRL | Byte count[15:0], chain[16], reload[17], SG[18], HG[20] |
| 2 | STATUS | Done[31], EOP[30], SOP[29], byte_count_rx[15:0] |
| 3-6 | MH | Module header (SOBMH: src_mod, dst_port, cos, opcode) |
| 7-11 | RX_STATUS | Ingress port, CoS, reason codes, match rule |
| 12 | MATCH | Outer/inner VLAN IDs |
| 13-14 | TIMESTAMP | RX timestamp (if enabled) |
| 15 | MISC | Decap info, tunnel type |

---

## 14. L2 Forwarding

### Hardware MAC Learning

The BCM56846 learns MAC addresses autonomously in hardware:
1. Packet arrives on port P with source MAC S in VLAN V
2. ASIC hash function computes index from (S, V)
3. If entry doesn't exist: create L2_USER_ENTRY with (S, V, P, STATIC=0)
4. If entry exists with different port: update port (MAC move)
5. Aging: hardware decrements hit counter; entries with hit=0 are deleted

### L2_USER_ENTRY Format (36 bytes)

```
Offset  Field
0x00    Flags (valid, static, hit, pending)
0x08    MAC address (6 bytes)
0x14    VLAN ID (12 bits)
0x2C    Destination port (output port number)
```

### Software MAC Programming

switchd can add/remove static MAC entries via BMD:
```c
bmd_port_mac_addr_add(unit, port, vlan, &mac_addr);
bmd_port_mac_addr_remove(unit, port, vlan, &mac_addr);
```

These internally write to the L2 table via S-Channel:
1. Build 36-byte L2_USER_ENTRY buffer
2. Set MAC, VLAN, port, STATIC=1, VALID=1
3. Compute hash index
4. Write via S-Channel WRITE_MEMORY to table 0x1547

---

## 15. L3 Routing

### Hardware L3 (requires OpenNSL SDK)

The BCM56846 supports hardware L3 routing via:
- **L3_DEFIP** (Longest Prefix Match table): 16K IPv4 routes
- **ING_L3_NEXT_HOP / EGR_L3_NEXT_HOP**: Next-hop MAC rewrite
- **EGR_L3_INTF**: Output interface (VLAN, MAC)
- **ECMP groups**: Equal-cost multipath (1K groups, 64 members)

Programming requires OpenNSL API (bcm_l3_route_add, bcm_l3_egress_create),
which is not available in OpenMDK. OpenMDK provides L2 switching only.

### Software L3 (current implementation)

Without hardware L3 offload, routing works via the kernel:
1. Kernel routes packets between swpN interfaces
2. Packets destined for remote subnets go through TUN → switchd → ASIC → wire
3. ARP resolution handled by kernel, ARP packets go through TUN
4. Performance: limited by CPU (P2020 ~500 Mbps routing vs 720 Gbps hardware)

---

## 16. DS100DF410 Retimers / Signal Conditioning

### Purpose

The DS100DF410 is a quad-channel 10Gbps retimer/equalizer from Texas Instruments.
It sits between the BCM56846 SerDes and the SFP+ cage, compensating for:
- PCB trace loss at 10 Gbps
- SFP+ module insertion loss
- Cable attenuation

### Device Distribution

32 DS100DF410 devices across the switch:
- 4 QSFP RX equalizers (retimer0-3, label `qsfp_rx_eq_0..3`)
- 12 SFP RX equalizers (retimer4-15, label `sfp_rx_eq_0..11`)
- 12 SFP TX equalizers (retimer16-27, label `sfp_tx_eq_0..11`)
- 4 QSFP TX equalizers (retimer28-31, label `qsfp_tx_eq_0..3`)

### I2C Access

Each retimer is at I2C address 0x27 on its port's bus. The `ds100df410` kernel
module creates sysfs attributes:
- `channels`: channel select (12 = all 4 channels)
- `veo_clk_cdr_cap`: VCO/CDR capacitor setting
- `cdr_rst`: CDR reset sequence (write 28, then 16)
- `tap_dem`: DEM (Decision-feedback Equalizer Mode) tap value

### Initialization Sequence (from Cumulus S20retimer_init.sh)

```bash
# For all retimers:
echo 12 > channels         # Select all 4 channels
echo 1  > veo_clk_cdr_cap  # VCO capacitor setting
echo 28 > cdr_rst          # CDR reset phase 1
echo 16 > cdr_rst          # CDR reset phase 2

# Additional for QSFP and SFP RX:
echo 23 > tap_dem           # DFE tap coefficient
```

### Which Ports Have Retimers

Not all SFP+ ports have retimers. The 48 SFP+ ports are split:
- **32 ports with retimers**: buses 22-25, 30-33, 38-41, 46-49, 54-57, 62-69
- **16 ports without retimers**: buses 26-29, 34-37, 42-45, 50-53

The ports without retimers are those with shorter PCB traces (closer to the ASIC).

---

## 17. SFP/QSFP Transceiver Management

### SFP+ (SFF-8472)

Each SFP+ transceiver has a 256-byte EEPROM at I2C address 0x50 on its port bus:

```
Bytes 0-19:   Transceiver type, connector, compliance codes
Bytes 20-35:  Vendor name (ASCII, 16 chars)
Bytes 36-39:  Vendor OUI
Bytes 40-55:  Vendor part number (ASCII, 16 chars)
Bytes 56-59:  Vendor revision
Bytes 60-61:  Wavelength (nm)
Bytes 68-83:  Vendor serial number (ASCII, 16 chars)
Bytes 84-91:  Date code (YYMMDD)
```

Diagnostic monitoring (A2 page at 0x51, if supported):
```
Bytes 96-97:  Temperature (signed, 1/256 degree C)
Bytes 98-99:  VCC supply voltage
Bytes 100-101: TX bias current (2 μA units)
Bytes 102-103: TX output power (0.1 μW units)
Bytes 104-105: RX input power (0.1 μW units)
```

### QSFP+ (SFF-8436)

QSFP transceivers use the `sff_8436_eeprom` driver with multi-page access:
- Page 0x00: Status, monitoring, control
- Page 0x01: AST (Vendor specific)
- Page 0x02: User writable EEPROM
- Page 0x03: Enhanced features

### Transceiver Detection Flow

```
1. Check PRESENCE GPIO (active low):
     gpio104 + port_idx → 0 = present, 1 = absent

2. If present, read EEPROM:
     I2C bus (21+port) address 0x50 → vendor, part, type

3. Determine speed capability:
     Byte 3 (10G compliance): bit 4 = 10GBASE-SR, bit 5 = 10GBASE-LR

4. Enable TX laser:
     Set TX_DISABLE GPIO low (gpio24 + port_idx → value=0)

5. Monitor link:
     Check RX_LOS GPIO (gpio176 + port_idx → 0 = signal OK)
     Check TX_FAULT GPIO (gpio216 + port_idx → 0 = no fault)
```

---

## 18. LED System

### CMIC LED Processor (Port LEDs)

The BCM56846 has two programmable LED processors that run 256-byte programs at 30Hz.
They control the front-panel port LEDs via a serial shift chain.

**Program flow:**
```
for each port (in PCB wiring order):
    1. Push amber bit = 0 (always off on AS5610)
    2. Read linkscan data (TX/RX activity)
    3. AND with blink state (10Hz toggle)
    4. INVERT (flash OFF during activity)
    5. AND with LINKEN (port admin enabled)
    6. Push green bit (result)
    7. Pack into shift register
send N bits to serial LED chain
update blink timer
```

**Effect:** Green LED solid ON when link up. Blinks OFF briefly during packet activity.

**Loading:**
```
led 0 stop
led 0 auto on        # Enable linkscan auto-update
led 0 load led0.hex  # Load 256-byte program
led 0 start
```

### System LEDs (CPLD)

Four system LEDs controlled via CPLD sysfs:

| LED | Location | Meaning |
|-----|----------|---------|
| PSU1 | `led_psu1` | Green = OK, Yellow = fault, Off = absent |
| PSU2 | `led_psu2` | Same |
| Fan | `led_fan` | Green = OK, Yellow = fault |
| System | `led_diag` | Green = running, Yellow = booting/error |

`ledmgrd` (Python daemon on Cumulus) or our `platform-init.sh` manages these
by reading sensor status and writing to CPLD sysfs.

---

## 19. Thermal Management

### Sensors

| Sensor | Chip | Bus | Addr | Channels |
|--------|------|-----|------|----------|
| Board temps | MAX6697 | 9 | 0x4d | 7 zones (local + 6 remote) |
| CPU/ambient | MAX1617 | 9 | 0x18 | 2 (local + remote) |

### Fan Control

Fan speed is controlled via CPLD PWM register:
```
/sys/devices/ff705000.localbus/ea000000.cpld/pwm1
Value range: 0 (off) to 248 (full speed)
```

### Thermal Policy

```
< 40°C:  Fan low (PWM=64, ~25%)
40-50°C: Fan medium (PWM=128, ~50%)
50-60°C: Fan high (PWM=200, ~80%)
60-75°C: Fan full (PWM=248, 100%)
> 75°C:  CRITICAL — full fan + 30s re-check → emergency shutdown
```

---

## 20. ONIE and Installation

### ONIE (Open Network Install Environment)

ONIE lives in the NOR flash (mtd0, 3.4MB) and provides:
- Network-based OS installation via `onie-nos-install`
- USB-based installation
- Serial console access
- fw_setenv for U-Boot environment

### NOR Flash Layout

```
mtd0: 3.4 MB  "onie"        ONIE kernel + rootfs
mtd1: 64 KB   "uboot-env"   U-Boot environment variables
mtd2: 64 KB   "board_eeprom" Board identification EEPROM
mtd3: 512 KB  "uboot"       U-Boot bootloader
```

### Installation Process

```
1. Boot into ONIE install mode (serial console or onie-nos-install)
2. ONIE downloads installer .bin file (self-extracting shell script)
3. Installer partitions USB flash:
     sda1: 128MB ext2 (persist)
     sda2: extended (sda5: 16MB FIT, sda6: rootfs)
     sda3: rest of disk ext2 (overlay)
4. Write FIT image to sda5 (raw dd)
5. Write squashfs rootfs to sda6 (raw dd)
6. Configure U-Boot:
     nos_bootcmd = "usb start; usbiddev; usbboot ... && bootm"
     DELETE onie_boot_reason (must be empty!)
7. Set root password, generate SSH keys
8. Reboot into NOS
```

### fw_env.config

For accessing U-Boot environment from Linux:
```
/dev/mtd1  0x00000000  0x00010000  0x00010000
```
This maps to the `uboot-env` MTD partition (64KB, sector size 64KB).

---

## References

- [edgecore-5610-reverse-engineering](https://github.com/wrightca1/edgecore-5610-reverse-engineering) — Full RE project with 90+ docs
- [edgenos](https://github.com/wrightca1/edgenos) — Custom NOS implementation
- [OpenMDK](https://github.com/Broadcom-Network-Switching-Software/OpenMDK) — Open-source BCM SDK
- CAPTURE_RESULTS_20260322.md — Live switch captures (MIIM, S-Channel, BAR, DMA)
- COMPLETE_CHIP_INVENTORY.md — All 133 hardware devices
- SYSTEM_BOOT_AND_I2C.md — Boot sequence and I2C topology
- LED_ARCHITECTURE.md — CMIC LED processor and ledmgrd

# To The Silicon — Complete Hardware-Layer Map

This is the final layer of the onion. Below this is bare metal: PCIe TLPs,
SCHAN messages, I²C wire transactions, and SerDes electrical signals.

Captured 2026-05-11 from the live AS5610-52X chassis. Treat this as the
**authoritative hardware map for writing an EdgeNOS BDE replacement**.

---

## 1. The hardware stack — top to bottom

```
┌──────────────────────────────────────────────────────────┐
│  User space                                                │
│  ┌──────────┐  ┌──────────┐  ┌─────────────────────────┐  │
│  │ switchd  │  │ bcmcmd   │  │ cl-* tools (Python)     │  │
│  └────┬─────┘  └────┬─────┘  └──────┬──────────────────┘  │
│       │             │               │                       │
│       ▼             ▼               ▼                       │
│  /dev/linux-user-bde   /var/run/switchd.socket             │
│  /dev/mem (BAR0 mmap)  /usr/share/cumulus/clcmd_uds         │
│  /dev/fuse             /dev/net/tun × 52                    │
│  /dev/i2c-{0..72}      /sys/class/eeprom_dev/*              │
│                                                             │
├──────────────────────────────────────────────────────────┤
│  Kernel space — loaded modules (in dep order)             │
│  ┌────────────────────────────────────────────────────┐   │
│  │ linux-kernel-bde.ko (34 KB resident, 504 KB on disk)│   │
│  │   - Device enumerator (PCI scan)                    │   │
│  │   - 64 MB DMA pool (dma_alloc_coherent)             │   │
│  │   - IRQ 16 ISR (wakes user-bde via wait queue)      │   │
│  │   - /dev/linux-kernel-bde (cdev)                    │   │
│  └────────────────────────────────────────────────────┘   │
│  ┌────────────────────────────────────────────────────┐   │
│  │ linux-user-bde.ko (14 KB resident, depends kbde)    │   │
│  │   - /dev/linux-user-bde (cdev)                      │   │
│  │   - mmap(PROT_READ|WRITE) for BAR0 + DMA pool       │   │
│  │   - IOCTL passthrough to kernel BDE                 │   │
│  └────────────────────────────────────────────────────┘   │
│  ┌────────────────────────────────────────────────────┐   │
│  │ linux-bde-tmon.ko (6.6 KB) — chip temperature hwmon │   │
│  └────────────────────────────────────────────────────┘   │
│  ┌────────────────────────────────────────────────────┐   │
│  │ accton_as5610_52x_cpld.ko (13.8 KB resident, GPL)   │   │
│  │   Author: Puneet Shenoy <puneet@cumulusnetworks.com> │   │
│  │   - CPLD register access via I²C                    │   │
│  │   - Exposes /sys/class/cpld/ entries                │   │
│  └────────────────────────────────────────────────────┘   │
│  ┌────────────────────────────────────────────────────┐   │
│  │ ds100df410.ko — TI DS100DF410 retimer driver        │   │
│  │   (in /kernel/drivers/misc/, GPL)                   │   │
│  │   32 chips on the chassis (one per pair of SFP+    │   │
│  │   ports or per QSFP+)                               │   │
│  └────────────────────────────────────────────────────┘   │
│  ┌────────────────────────────────────────────────────┐   │
│  │ Generic Linux modules:                              │   │
│  │   - tun.ko (52 instances of /dev/net/tun)           │   │
│  │   - at24.ko (SFP+ EEPROM A0/A2 pages)               │   │
│  │   - sff_8436_eeprom.ko (QSFP+ EEPROM)               │   │
│  │   - gpio_pca953x.ko (PCA9555 expanders, 61 inst)    │   │
│  │   - i2c_mpc (eTSEC I²C master)                      │   │
│  │   - i2c_mux_pca954x (PCA9548 muxes)                 │   │
│  │   - max6697, adm1021 (temperature sensors)          │   │
│  │   - 8021q (VLAN tagging)                            │   │
│  └────────────────────────────────────────────────────┘   │
│                                                             │
├──────────────────────────────────────────────────────────┤
│  Hardware                                                  │
│  ┌────────────────────────────────────────────────────┐   │
│  │ Freescale P2020 (PowerPC dual-core)                 │   │
│  │   - 2 GB DDR3 system RAM (0x00000000-0x7fffffff)    │   │
│  │   - eTSEC (eth0) management Ethernet                │   │
│  │   - I²C mpc (2 i2c controllers, IRQ 43)             │   │
│  │   - OpenPIC interrupt controller                    │   │
│  │   - EHCI USB (IRQ 28, internal flash)               │   │
│  │   - UART serial (ff704500)                          │   │
│  └────────────────────────────────────────────────────┘   │
│                  │ PCIe Gen1 x1 (2.5 GT/s)                 │
│                  ▼                                          │
│  ┌────────────────────────────────────────────────────┐   │
│  │ BCM56846 (Trident+) at PCI 0000:01:00.0             │   │
│  │   PCI vendor:device = 0x14e4:0xb846 rev 0x02        │   │
│  │   Subsystem = 0x14e4:0xb846                          │   │
│  │   BAR0 = 0xa0000000, size 256 KB, non-prefetchable  │   │
│  │   IRQ 16 (legacy INTx pin A, MSI available unused)  │   │
│  │   PCIe v2 endpoint, MaxPayload 256, MaxReadReq 256  │   │
│  │   Capabilities: PM, MSI, PCIe, DSN, AER, PB, VC     │   │
│  │   Integrated temperature sensor (hwmon temp1_input) │   │
│  │                                                       │   │
│  │   Internal blocks:                                   │   │
│  │   - iProc PAXB bridge (8x4KB sub-windows)           │   │
│  │   - CMICm controller (4 CMCs)                       │   │
│  │   - SCHAN bus                                        │   │
│  │   - L2/L3 tables, FP TCAM, MMU buffer pool           │   │
│  │   - 52 ports (48×10G SFP+ + 4×40G QSFP+)            │   │
│  │   - 2 LED uControllers                              │   │
│  └────────────────────────────────────────────────────┘   │
│                  │  10G/40G SerDes lanes                    │
│                  ▼                                          │
│  ┌────────────────────────────────────────────────────┐   │
│  │ 32× TI DS100DF410 retimers (4 channels each)        │   │
│  │   On per-port I²C buses at address 0x27             │   │
│  │   Buses: 18-25, 30-33, 38-41, 46-49, 54-57, 62-69  │   │
│  │   sysfs: cdr_rst, adapt_eq_sm, drv_sel_vod, ...     │   │
│  └────────────────────────────────────────────────────┘   │
│                  │  Equalized SerDes                        │
│                  ▼                                          │
│  ┌────────────────────────────────────────────────────┐   │
│  │ Front-panel SFP+ cages (48) + QSFP+ cages (4)       │   │
│  │   Per-port: SFP+ A0/A2 EEPROMs at I²C 0x50/0x51    │   │
│  │   Per-port: MODSEL/INTL/RESET via PCA9555 GPIO     │   │
│  │   Per-port: bicolor LED via LED uController         │   │
│  └────────────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────────┘
```

---

## 2. linux-kernel-bde.ko — module parameters

From `modinfo`:

```
filename:       /lib/modules/3.2.60-1+deb7u1+cl2.5/extra/linux-kernel-bde.ko
license:        GPL
description:    Kernel BDE
author:         Broadcom Corporation
depends:        (none)
vermagic:       3.2.60-1+deb7u1+cl2.5 SMP mod_unload modversions
```

### Module parameters (CRITICAL for our own driver)

| Parameter | Type | Default | Use |
|---|---|---|---|
| `dmasize` | charp | 4MB | DMA pool size — set to 64MB on this box |
| `himem` | charp | no | Use high memory for DMA buffers |
| `maxpayload` | int | auto | Limit PCIe MaxPayload/MaxReadReq |
| `usemsi` | int | 0 | Use MSI interrupts instead of INTx |
| `nodevices` | int | 0 | Ignore all recognized devices |
| `forceirq` | int | auto | Override IRQ line from bootloader |
| `forceirqubm` | uint | 0 | Per-unit IRQ override bitmap |
| `debug` | int | 0 | Debug level |
| `eb_bus` | charp | none | External Bus devices (non-PCI chips) |

The fact that BDE has GPL license and standard module params makes it
straightforward to write an open replacement.

### linux-user-bde.ko

```
description: User BDE Helper Module
depends:     linux-kernel-bde
```

No parameters — just an mmap helper. Provides `/dev/linux-user-bde` for
user-space mmap of BAR0 and the DMA pool.

---

## 3. PCI config space — complete

From hex dump of `/sys/bus/pci/devices/0000:01:00.0/config`:

```
Offset  Value                                       Meaning
0x00    e4 14 46 b8                                 Vendor 0x14e4, Device 0xb846
0x04    06 00 10 00                                 Cmd=Mem+BM+, Status=Cap+
0x08    02 00 00 02                                 Rev 0x02, Class 0x020000 (Ethernet ctrl)
0x0c    08 00 00 00                                 CacheLineSize=32 bytes, latency=0
0x10    04 00 00 a0                                 BAR0 = 0xa0000004 (Mem 64-bit)
0x14    00 00 00 00                                 BAR0 upper 32 = 0
0x18..  (zero — no other BARs)
0x2c    e4 14 46 b8                                 Subsystem = 0x14e4:0xb846
0x34    48 00 00 00                                 Capabilities ptr = 0x48
0x3c    00 01 00 00                                 IntLine=0x01, IntPin=A
0x48    01 50 ...                                   Power Management cap (next=0x50)
0x50    03 58 ...                                   (extension of PM, next=0x58)
0x58    05 ac 86 00                                 MSI cap (next=0xac, Count=8, 64-bit)
0xa0    11 00 ...                                   (Vital Product Data)
0xac    10 00 02 00                                 PCIe Express cap v2 endpoint
0xb0    02 80 3c 00 20 1c 10 00 22 6c 01 00         PCIe device control / link cap
0xd0    1f 00 ...                                   (PCIe device serial number ext)
0x100   03 00 01 11                                 Ext cap 0x0003: Device Serial Number
0x110   01 00 01 15                                 Ext cap 0x0001: AER
0x150   ...                                          Ext cap: Power Budgeting
0x160   ...                                          Ext cap: Virtual Channel
```

### Key PCI facts

- **PCIe link is Gen1 x1 (2.5 GT/s)** even though the chip supports Gen2 x2.
  This is a board/host limitation — the P2020 PCIe root complex on AS5610
  only routes one lane to the BCM chip.
- **Theoretical PCIe BW = 2 Gbps each way** (Gen1 x1, 8b/10b encoded).
  This is the upper bound for CPU↔chip DMA throughput. The chip's
  104 Tbps switching capacity is unaffected — only RX punt and TX inject
  go via this PCIe link.
- **MSI is available (8 vectors) but unused.** switchd uses legacy INTx
  on IRQ 16. Could switch to MSI for lower latency.
- **AER (Advanced Error Reporting) is enabled** — chip-level PCIe errors
  surface to the kernel via /sys/bus/pci/devices/.../aer_*.

---

## 4. The 32 retimers — DS100DF410

`/lib/modules/.../kernel/drivers/misc/ds100df410.ko` (Cumulus-patched in).

### Retimer chip locations (32 chips, 4 channels each = 128 channels)

| I²C bus range | Retimers | Likely port group |
|---|---|---|
| 18-25 | 8 chips | SFP+ ports 1-16 (2 ports per chip) |
| 30-33 | 4 chips | SFP+ ports 17-24 |
| 38-41 | 4 chips | SFP+ ports 25-32 |
| 46-49 | 4 chips | SFP+ ports 33-40 |
| 54-57 | 4 chips | SFP+ ports 41-48 |
| 62-69 | 8 chips | 4× QSFP+ ports 49-52 (each QSFP = 4 lanes = 2 chips) |

**Math check:** 48 SFP+ × 2 lanes (TX/RX) + 4 QSFP+ × 4 lanes × 2 = 128
channels = 32 chips × 4 channels. ✓

### Sysfs interface per retimer

```
/sys/bus/i2c/devices/{18,19,...,69}-0027/
├── adapt_eq_sm       ← Adaptive Equalization State Machine status
├── cdr_rst           ← CDR (Clock Data Recovery) RESET ⭐
├── channels          ← Number of channels (4)
├── drv_sel_vod       ← Driver Select Vod (output voltage swing)
├── pfd_prbs_dfe      ← PFD/PRBS/DFE control register
├── retimer_dev       ← Retimer device identifier
├── tap_dem           ← Equalizer tap demarcation
└── veo_clk_cdr_cap   ← VEO clock CDR capture status
```

### Why this matters

Per the earlier breakthrough (`project_cdr_reset_breakthrough.md`):
**writing 1 to `cdr_rst` is required for retimer signal pass-through.**
Without resetting CDR after a port re-init, the retimer doesn't lock
onto the new line rate and the SFP+ stays dark.

The kernel driver makes this a one-line shell command:

```sh
echo 1 > /sys/bus/i2c/devices/N-0027/cdr_rst
sleep 0.1
echo 0 > /sys/bus/i2c/devices/N-0027/cdr_rst
```

EdgeNOS should mirror this driver — or just keep using this very driver,
since it's already GPL and in the kernel tree under
`drivers/misc/ds100df410.c`.

---

## 5. The CPLD — accton_as5610_52x_cpld.ko

```
filename:    /lib/modules/.../extra/accton_as5610_52x_cpld.ko
license:     GPL
author:      Puneet Shenoy <puneet@cumulusnetworks.com>
description: CPLD driver for Accton Technology Corporation, AS5610_52X
```

**This is Cumulus-authored, GPL, and platform-specific.** Two CPLDs on
the chassis:
- I²C 3-003a: CPLD #1 (chassis controller — fans, PSUs, system LEDs)
- I²C 3-003e: CPLD #2 (port controller — SFP+ presence/LPMODE/RESET)

The driver exposes their registers as sysfs attrs. Wraps for the 32-byte
register address space (per `feedback_cpld_addr_wrap.md` — addresses wrap
above 0x1f, never write above that, never use devmem).

For EdgeNOS: this driver is GPL — can adopt directly, or port to a
modern kernel. The CPLD register layout is documented in our captured
copies.

---

## 6. Kernel BDE — interrupt + DMA flow

```
                BCM56846 chip raises INTx on pin A
                                │
                                ▼
                OpenPIC routes to IRQ 16 (CPU0)
                                │
                                ▼
                linux-kernel-bde ISR:
                  1. Read BCM PCIe interrupt status
                  2. Update wait queues (one per "interrupt type":
                     - DMA completion (TX/RX rings)
                     - SCHAN completion
                     - Link status change
                     - Error/parity
                  3. wake_up_interruptible on matched queue
                                │
                                ▼
                User-space switchd thread blocked in:
                  ioctl(/dev/linux-user-bde, BDE_WAIT_INTR, ...)
                  returns; thread services the event
                                │
                                ▼
                For DMA RX: switchd reads DMA buffer (via /dev/mem mmap),
                  parses CPU_HEADER, writes packet to TUN fd for that port
                                │
                                ▼
                Linux kernel receives packet on swpN interface
```

### DMA pool

- 64 MB allocated by linux-kernel-bde via `dma_alloc_coherent` at boot
  (set via `dmasize=64M` boot arg — default is 4 MB)
- 0 used by kernel BDE — switchd allocates DMA chunks via user-BDE ioctls
- mapped into switchd via `/dev/linux-user-bde` mmap

---

## 7. Complete I²C tree

From `/sys/bus/i2c/devices/`:

```
ROOT (i2c-mpc on Freescale P2020)
├── i2c-0 (master 0)
│   └── mux PCA9548 @ 0x70 → i2c-3..i2c-9
│       ├── i2c-3 → CPLD #1 (3-003a), CPLD #2 (3-003e), mux @ 0x78
│       │            (NOTE: 0x3a/0x3e bound to at24 c02 driver;
│       │             the actual CPLD logic is via accton_as5610_52x_cpld)
│       ├── i2c-4..9 → other muxes / sensors
│
├── i2c-1 (master 1)
│   ├── mux PCA9548 @ 0x75 → i2c-10..i2c-13
│   ├── mux PCA9548 @ 0x76 → i2c-14..i2c-17
│   │   ├── i2c-16 → 4x PCA9506 GPIO @ 0x20-0x23 (40-bit each)
│   │   │            and 4x PCA9548 muxes @ 0x70-0x73
│   │   └── i2c-17 → more GPIO expanders @ 0x23, 0x24
│   └── mux PCA9548 @ 0x77 → i2c-18..i2c-21
│
└── Per-port buses (cascaded through tier-2 muxes at @ 0x74):
    i2c-18..i2c-25  → ports 1-16  (each: DS100DF410 @ 0x27, SFP @ 0x50/51)
    i2c-30..i2c-33  → ports 17-24
    i2c-38..i2c-41  → ports 25-32
    i2c-46..i2c-49  → ports 33-40
    i2c-54..i2c-57  → ports 41-48
    i2c-62..i2c-69  → ports 49-52 QSFP+ (4 lanes each)
```

### Device → driver mapping

| Addr | Driver | Function |
|---|---|---|
| 0x20-0x23 (bus 16) | `pca9506` / gpio_pca953x | 40-bit GPIO expander (LED/presence) |
| 0x27 (per-port) | **`ds100df410`** | TI retimer (4 channels each) |
| 0x3a, 0x3e | `24c02` / at24 | Small EEPROM (board info / syseeprom) |
| 0x50 (per-port SFP+) | `at24` | SFP+ EEPROM page A0 (identification) |
| 0x51 (per-port SFP+) | `at24` | SFP+ EEPROM page A2 (DOM diagnostic) |
| 0x70, 0x74-0x78 | `i2c-mux-pca954x` | I²C 8-channel muxes |

---

## 8. The platform kernel module list (final list for EdgeNOS)

To boot the AS5610-52X with packet forwarding, EdgeNOS needs these
kernel modules (or equivalents):

### Must-have, platform-specific
1. **linux-kernel-bde** — Broadcom BDE core (or our replacement)
2. **linux-user-bde** — user-space mmap helper (or our replacement)
3. **accton_as5610_52x_cpld** — Cumulus's CPLD driver (GPL, reusable)
4. **ds100df410** — retimer driver (GPL, in mainline drivers/misc/)

### Must-have, generic Linux drivers
5. **tun** — TUN/TAP for swp* interfaces
6. **i2c_mpc** — Freescale P2020 I²C controller (mainline)
7. **i2c_mux_pca954x** — PCA9548 I²C mux (mainline)
8. **gpio_pca953x** — PCA9555 GPIO expander (mainline)
9. **at24** — SFP+ EEPROM driver (mainline)
10. **sff_8436_eeprom** — QSFP+ EEPROM driver (mainline-ish)
11. **8021q** — VLAN tagging

### Nice-to-have
12. **linux-bde-tmon** — chip temperature monitor (or use mainline hwmon)
13. **adm1021, max6697** — board temperature sensors

---

## 9. Below the silicon: what we still don't see

After all this digging, the layer we haven't touched is:
- **PCIe link training** — happens in P2020 boot, before Linux
- **The actual MMIO writes during `init all`** — switchd's chip-init
  sequence (the bcm_init dispatch chain). We have it statically but
  not live-traced.
- **SCHAN message wire format** — we have opcodes, but the bit-level
  TLP payload going into PAXB is not directly visible
- **PHY firmware execution** — loaded via MDIO at boot but we don't
  trace inside the PHY's microcontroller
- **LED uController execution** — the 187/210-line bytecode runs on a
  dedicated micro inside the chip
- **MMU buffer cell-level state** — only the configured limits are
  visible; actual cell counts are inside chip MMIO

To get any deeper we'd need:
- PCIe protocol analyzer (hardware bus tap) for TLP capture
- JTAG access to the chip for register/memory dump
- A Broadcom NDA agreement (which defeats the purpose)

For EdgeNOS, **we have enough**. The hardware map above is the
complete recipe; everything below it is the same for any NOS that
runs on this silicon.

---

## 10. EdgeNOS minimum viable bring-up — recipe

To bring up the AS5610-52X from cold boot to forwarding packets:

### Phase 1: BIOS/U-Boot (already in place)
- P2020 boots from NOR flash
- DDR3 init, PCIe root complex up
- Loads kernel from internal USB flash

### Phase 2: Linux boot
1. Standard kernel boot
2. Load `i2c_mpc`, `i2c_mux_pca954x`, `gpio_pca953x`
3. Probe I²C tree, create 70 `/dev/i2c-N` devices
4. Load `accton_as5610_52x_cpld` — chassis comes alive (fans spin up,
   PSU status visible)
5. Load `at24`, `sff_8436_eeprom` — SFP+ EEPROMs accessible
6. Load `ds100df410` — retimers programmable

### Phase 3: BDE bring-up
7. Load `linux-kernel-bde` with `dmasize=64M`
   - Module probes PCI 0000:01:00.0
   - Allocates 64 MB DMA pool
   - Registers IRQ 16 handler
8. Load `linux-user-bde`
   - Exposes `/dev/linux-user-bde`

### Phase 4: Chip bring-up
9. Run BDE init recipe (analogue of `rc.soc`):
   - `attach *` (PCI scan)
   - `init all` (bcm_init dispatch — sets up MMU, FP, L2/L3 tables)
   - Load port config (52 ports, see config.bcm)
   - Load datapath config (buffer pools, QoS map)
   - Set XMAC_TX_CTRL = 0xc802
   - Set MAC_RSV_MASK MASK=0x18
   - Set CMIC_MISC_CONTROL LINK40G_ENABLE=1
   - Reset all 32 retimers via cdr_rst
10. Load LED uController bytecode (`led0.hex`, `led1.hex`)
11. Load PHY firmware via MDIO (BCM84740/54)

### Phase 5: Linux interfaces
12. Create 52 TUN devices, name them `swp1`..`swp52`
13. Start switchd-equivalent: tie TUN fds to chip TX/RX DMA rings
14. Install default control-plane ACL (00control_plane.rules)
15. Set link-scan enable per port

### Phase 6: Forwarding active
- Links come up
- LACP / STP / LLDP daemons start (Linux-native)
- Routing daemons (FRR or quagga) take over L3
- Datapath active

---

## 11. Files (for future reference)

Configuration that drives the whole stack:
- `/etc/bcm.d/config.bcm` — SDK parameters
- `/etc/bcm.d/rc.soc` — SOC init recipe
- `/etc/bcm.d/rc.ports_0` — port environment
- `/etc/bcm.d/rc.led`, `/etc/bcm.d/led{0,1}.hex` — LED uController
- `/etc/bcm.d/rc.phy` — PHY init (4 lines)
- `/etc/bcm.d/backend_map` — internal port-block mapping
- `/var/lib/cumulus/rc.datapath_0` — MMU + QoS config (auto-generated)
- `/var/lib/cumulus/phytab`, `porttab`, `sfptab` — port tables
- `/usr/share/cumulus/phy_ucode/` — 3 PHY firmware files
- `/usr/share/cumulus/acl/00control_plane.rules` — CoPP rules
- `/etc/cumulus/init/accton_as5610_52x/platform.conf` — platform config

Kernel modules (all GPL, in `/lib/modules/.../extra/` or kernel/drivers/):
- `linux-kernel-bde.ko`, `linux-user-bde.ko`, `linux-bde-tmon.ko`
- `accton_as5610_52x_cpld.ko`
- `ds100df410.ko` (in drivers/misc/)
- Plus mainline: tun, at24, sff_8436_eeprom, gpio_pca953x, i2c-*, 8021q

---

*Captured 2026-05-11 from live Cumulus 2.5.0 chassis at 10.1.1.212.
This is the complete hardware map. Below this layer is bare silicon.*

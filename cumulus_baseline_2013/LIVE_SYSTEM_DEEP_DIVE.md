# Live System Deep Dive — Runtime Facts Not in Static Analysis

Captured 2026-05-11 from the live Cumulus 2.5.0 AS5610-52X at 10.1.1.212.

This doc records the runtime state that static rootfs analysis missed.
Treat this as **ground truth** for any chip-access code in EdgeNOS.

---

## 1. PCI device — BCM56846 location

From `/proc/iomem` and `/sys/bus/pci/devices/0000:01:00.0/`:

```
PCI vendor:  0x14e4  (Broadcom)
PCI device:  0xb846  (NOT 0x56846 — the PCI DID is shortened)
PCI rev:     2
BAR0:        0xa0000000 - 0xa003ffff  (256 KB, prefetchable, 64-bit)
IRQ:         16 (shared with linux-kernel-bde driver)
PCI BDF:     0000:01:00.0
```

The full `/proc/iomem` map:

```
00000000-7fffffff : System RAM           (2 GB DDR3)
a0000000-bfffffff : /pcie@ff70a000       (PCIe window 512 MB)
  a0000000-bfffffff : PCI Bus 0000:01
    a0000000-a003ffff : 0000:01:00.0     ← BCM56846 BAR0 (256 KB)
efc00000-efffffff : efc00000.flash       (4 MB U-Boot/NOR flash)
ff704500-ff704507 : serial               (PowerPC console UART)
ff722000-ff722fff : EHCI USB
```

**This confirms:**
- BAR0 is exactly 256 KB (0x40000), enough for CMICm at +0x31000-0x33xxx
- BAR1 is unused (single-BAR device, all chip regs in BAR0)
- Mapping `/dev/mem` at offset 0xa0000000 with 256 KB length gives full chip access
- Our EdgeNOS BDE replacement can request just this PCI BDF

---

## 2. Kernel BDE — the chip device enumerator

`/proc/linux-kernel-bde` reports:

```
Broadcom Device Enumerator (linux-kernel-bde)
DMA Memory (high): 67108864 bytes, 0 used, 67108864 free
Devices:
    0 (swi) : PCI device 0:0x14e4:0xb846:2:0xa0000000:16
```

What this tells us:

| Item | Value | Meaning |
|---|---|---|
| Driver | linux-kernel-bde | Broadcom kernel module name |
| DMA pool | 64 MB | Reserved at boot via `dma_alloc_coherent` |
| Pool usage | 0 used (!!!) | DMA pool is ENTIRELY UNUSED at runtime |
| Device 0 | swi (switch interface) | Single switch device |
| BDF/BAR/IRQ | 0:14e4:b846:2:a0000000:16 | Matches /proc/iomem |

**The "0 used" of DMA is significant.** It means switchd is NOT using
the kernel BDE's DMA pool. Either:
- (A) DMA isn't running — packets are punted via SCHAN CPU-port reads
- (B) DMA buffers come from `/dev/mem` or user-space mmap, not BDE pool

Looking at switchd's fd 14 (`/dev/linux-user-bde`) and fd 15 (`/dev/mem`)
— it's likely (B): the user-space BDE driver mmaps DMA buffers via
`/dev/mem` and the kernel BDE just tracks them.

This is critical for EdgeNOS: **don't reimplement DMA via kernel BDE
pool — switchd doesn't use it.** Mirror its mmap-via-/dev/mem strategy.

---

## 3. User BDE — interrupt mode

`/proc/linux-user-bde` reports:

```
Broadcom Device Enumerator (linux-user-bde)
    0: Interrupt mode CMIC/CMICe
```

Confirms the chip is operating in **interrupt-driven mode**, not polled.
The "CMIC/CMICe" string is BDE's way of saying "CMICm-class device"
(CMICe was the older name for what became CMICm in Trident).

---

## 4. IRQ 16 — chip interrupt

`/proc/interrupts`:

```
           CPU0       CPU1
 16:   44,111,281         0   OpenPIC   Level     linux-kernel-bde
 28:      230,542         0   OpenPIC   Level     ehci_hcd:usb1
 29:           0     25,887   OpenPIC   Level     eth0_g0_tx
 30:      852,756         0   OpenPIC   Level     eth0_g0_rx
 43:           0  2,026,896   OpenPIC   Level     i2c-mpc, i2c-mpc
```

**44 million chip interrupts** to date — that's link events, DMA completions,
SCHAN completions, and counter rollovers from running ~6 weeks of uptime.

- **IRQ 16**: chip — `linux-kernel-bde` is the ISR; it wakes user-space
  switchd via the user-BDE device
- **IRQ 43**: I²C (CPLD + SFP+ DOM polling — Cumulus uses interrupt-driven
  I²C, not bit-banging)
- **IRQ 29/30**: eth0 (Freescale eTSEC management Ethernet)

---

## 5. switchd's open fds (with sudo) — full picture

```
fd 0,1,2    /dev/null              standard streams
fd 3        /var/log/switchd.log   log
fd 4,5      pipe                   internal IPC (probably config reload)
fd 6-13     sockets                netlink + Unix sockets (mgmt)
fd 14       /dev/linux-user-bde    ← USER-SPACE BDE (chip control)
fd 15       /dev/mem               ← DIRECT MMIO (BAR0 + DMA buffers)
fd 16       socket /var/run/switchd.socket  cl-* dispatcher
fd 18,19    pipe                   thread IPC
fd 20-71    /dev/net/tun x 52      ← ONE TUN DEVICE PER SWITCH PORT
fd 72       /dev/fuse              ← FUSE filesystem at /cumulus/switchd
fd 73-75    sockets                ZTP/clcmd/stat
```

### Key insights from the fd table

1. **52 TUN devices = the punt/inject mechanism.** When the chip punts
   a packet, switchd:
   - Reads the DMA descriptor (via mmap)
   - Looks at the CPU_HEADER source port field
   - Writes the packet to TUN fd N → it appears on Linux `swpN`
   - kernel routes/bridges normally

   When Linux sends out a `swpN`:
   - TUN fd N becomes readable
   - switchd reads packet, builds CPU_HEADER with destination port = N
   - Writes to chip TX DMA ring → packet egresses

2. **fd 14 (`/dev/linux-user-bde`) is the SOC API entry point.** All
   `bcm_*` and `soc_*` calls eventually become ioctls on this fd.

3. **fd 15 (`/dev/mem`) is for direct mapping.** Mapped at offset
   0xa0000000 for BAR0 access, plus contiguous DMA regions
   (probably allocated by kernel-BDE then mmap'd here).

4. **fd 72 (`/dev/fuse`) is the chip-tables FUSE.** switchd is BOTH
   the FUSE producer (servicing reads/writes on `/cumulus/switchd/*`
   from cl-tools) AND the chip controller. Single process holds both
   roles.

---

## 6. I²C topology — 33 buses for 52 ports

`ls /sys/bus/i2c/devices/` reveals a complex multi-tier mux tree:

```
ROOT BUSES
i2c-0  ─→ mux PCA9548 at 0x70  ─→ i2c-3..i2c-9 (per-mux channels)
i2c-1  ─→ mux PCA9548 at 0x75  ─→ i2c-10..i2c-13
       ─→ mux PCA9548 at 0x76  ─→ i2c-14..i2c-17
       ─→ mux PCA9548 at 0x77  ─→ i2c-18..i2c-21
i2c-2  ─→ syseeprom at 0x51

PER-PORT MUX TREE (cascading)
i2c-10..32 each → mux PCA9548 at 0x74 → i2c-N+15..N+22 (port-specific)

PER-PORT DEVICES (terminal leaves)
i2c-{18-32}-0027  ← QSFP/SFP+ MODSEL / INTL / RESET GPIO (1 per port)
i2c-{18-32}-0050  ← SFP+ EEPROM page A0 (identification)
i2c-{22-32}-0051  ← SFP+ EEPROM page A2 (DOM diagnostic monitoring)

CONTROL DEVICES
i2c-3-003a   ← CPLD #1 (chassis controller)
i2c-3-003e   ← CPLD #2 (port controller)
i2c-3-0078   ← Another I²C mux
i2c-16-0020..0023  ← PCA9555 GPIO expanders (port LEDs, presence bits)
i2c-17-0023..0024  ← More GPIO expanders
```

### What's at each address

| 7-bit addr | Type | Linux driver | Use |
|---|---|---|---|
| 0x20-0x23 | PCA9555 | gpio_pca953x | 16-bit GPIO expanders |
| 0x27 | unknown | unknown | per-port QSFP control (modsel/intl/rst) |
| 0x3a, 0x3e | Accton CPLD | i2c-mpc / custom | chassis state |
| 0x50 | EEPROM | at24 | SFP+ ident (A0 page) |
| 0x51 | EEPROM | at24 | SFP+ DOM (A2 page) |
| 0x70, 0x74, 0x75-0x77 | PCA9548 | i2c-mux-pca954x | I²C muxes |
| 0x78 | PCA9548 | i2c-mux-pca954x | yet another mux |

The mux topology means each SFP+ port has **its own dedicated I²C bus**
exposed at `/dev/i2c-N`, making per-port access non-conflicting.

---

## 7. SFP+ EEPROM access — kernel-native, not switchd

`/sys/class/eeprom_dev/eepromN` lists 33 EEPROM devices:

```
eeprom0  → 3-003a   (CPLD #1)
eeprom1  → 3-003e   (CPLD #2)
eeprom2  → 3-0078   (mux)
eeprom10 → 25-0050  (SFP+ port @ i2c-25)
eeprom11 → 26-0050  (SFP+ port @ i2c-26)
...
eeprom34 → 57-0050  (last port?)
```

**Key insight:** Cumulus exposes SFP+ EEPROMs as **kernel `at24`
devices**, NOT through switchd. Tools like `cl-cabledetect` and
`cl-sfputil` read them via standard `/sys/class/i2c-dev/i2c-N/`
sysfs paths or `/dev/i2c-N` directly.

This is the **proper Linux-native pattern** — no proprietary IPC
needed for SFP+ EEPROM access. EdgeNOS should adopt the same model.

---

## 8. IPC sockets

`ss -xlpn` shows these Unix-domain listening sockets:

| Socket path | Owner | Use |
|---|---|---|
| `/var/run/audispd_events` | audispd | Audit subsystem (Linux native) |
| `/usr/share/cumulus/clcmd_uds` | python (PID 2271) | **cl-* dispatcher** |
| `/var/run/lldpd.socket` | lldpd | LLDP control (Linux native) |
| `/var/run/switchd.socket` | switchd | **switchd direct IPC** |

### `clcmd_uds` — the Cumulus command dispatcher

There's a long-running Python process (PID 2271) listening on
`/usr/share/cumulus/clcmd_uds`. All `cl-*` shell commands are thin
wrappers that:
1. Read user args from CLI
2. Open `/usr/share/cumulus/clcmd_uds` (Unix DGRAM or SEQPACKET socket)
3. Send a request like `{"cmd": "cl-ports", "args": [...], "env": {...}}`
4. The Python dispatcher routes to the correct Python module
5. Module performs work (reads FUSE, talks to switchd via switchd.socket,
   or accesses sysfs directly)
6. Returns result over the socket

This is the **clcmd RPC pattern** — all cl-tools share one Python
runtime. Reduces startup overhead (otherwise each `cl-*` call would
import all of cumulus.* which is slow).

### `switchd.socket` — direct switchd IPC

switchd's fd 16 listens on `/var/run/switchd.socket`. This is a
secondary control channel (separate from the FUSE filesystem). Used
for:
- Health/status queries
- Reload signals
- Maybe direct SDK calls for performance-sensitive ops

The clcmd_uds server (Python dispatcher) likely opens switchd.socket
when it needs to query chip state directly.

---

## 9. Hardware monitoring (hwmon)

`/sys/bus/pci/devices/0000:01:00.0/` exposes:
- `temp1_input` — current chip die temperature
- `temp1_max` — maximum chip die temperature
- `temp1_max_hyst` — hysteresis threshold

**This means the BCM56846 has an integrated temperature sensor**
exposed via the kernel hwmon framework, accessible from Linux WITHOUT
going through switchd or SCHAN.

Source: kernel-bde driver registers a hwmon device when it loads the
chip. EdgeNOS should preserve this — `lm-sensors` will pick it up
automatically.

---

## 10. Switchd's virtual memory map

`/proc/$(pidof switchd)/maps` shows:

```
0x10000000 - 0x11808000  switchd code (.text)            ~24 MB
0x11817000 - 0x11e46000  switchd r/w data + relocs       ~6 MB
0x11e46000 - 0x12f58000  HEAP #1 (probably libc malloc)  ~17 MB
0x124e3000 - 0x12f58000  HEAP #2 (allocated separately)
```

The 24 MB text section is the entire switchd binary statically linked
with libopennsl-style SDK. The big heap is the runtime state — chip
register cache, port state, FP TCAM cache, L2/L3 table cache.

Libraries loaded:
- libfuse.so.2.9.0 (the FUSE driver for /cumulus/switchd)
- libnl-3 / libnl-route-3 / libnl-genl-3 (netlink)
- libc-2.13.so (Debian wheezy)
- libpthread (switchd is multithreaded)

---

## 11. /etc/network/interfaces — minimal

Just:
```
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet dhcp
```

The `swp1`-`swp52` Linux interfaces are **NOT configured here**. They're
created dynamically by switchd at startup (as the kernel side of the
TUN devices). Their L3 config (IP addresses, MTU, etc.) is managed via:
- `/var/lib/cumulus/datapath.conf`
- FUSE writes to `/cumulus/switchd/config/port/swpN/*`
- ifupdown2 with `/etc/network/ifupdown2/policy.d/` for higher-level
  bridge/bond/vrr abstractions

---

## 12. Why static analysis missed all of this

Items 1-11 here came **only from live inspection** — they were either:

| Item | Why missed statically |
|---|---|
| /proc/iomem | Runtime kernel state, not in any binary |
| BDE DMA pool size | kernel boot params + runtime allocation |
| /proc/interrupts | Live IRQ counters |
| switchd fd list | Process must be running |
| 52 TUN devices | Created by switchd at startup |
| /dev/fuse fd | Same |
| I²C device tree | Built by kernel device tree probing |
| /sys/class/eeprom_dev | at24 driver creates entries on probe |
| clcmd_uds protocol | Live socket, no binary contains the protocol spec |
| hwmon temp sensor | Runtime hwmon class registration |
| /proc/iomem PCI BAR | PCI enumeration at boot |

For EdgeNOS, **always validate static findings against live state**. The
static rootfs gives you the *recipe*, but live state gives you the
*execution result*.

---

## 13. EdgeNOS action items from this analysis

### Must-haves
- [ ] Map `/dev/mem` at offset 0xa0000000 length 256KB (single mmap)
      for BAR0 access; or use a custom uio-style driver
- [ ] Implement chip-IRQ handler attached to PCI device, waking
      user-space via eventfd
- [ ] Use kernel `at24` driver for SFP+ EEPROM access — don't reinvent
- [ ] Use kernel `gpio_pca953x` for chassis GPIO — already in mainline
- [ ] Use kernel `i2c-mux-pca954x` for I²C mux topology — already mainline
- [ ] Create 52 TUN devices at startup, one per switch port, named
      `swp1`...`swp52` (or `Ethernet0`...`Ethernet51` SAI-style)
- [ ] Register a hwmon device for chip temperature reporting

### Nice-to-haves
- [ ] FUSE filesystem at `/edgenos/chip/` mirroring Cumulus's layout
      (eases migration)
- [ ] clcmd-style RPC dispatcher to avoid Python startup overhead per
      command (but in Go or Rust)

### Avoid
- Don't reimplement kernel-BDE's DMA pool — it's allocated but unused
- Don't use polling I²C — use interrupt-driven (IRQ 43 pattern)
- Don't put SFP+ EEPROM access through the chip daemon — kernel-native

---

## 14. The live SOC init recipe — `/etc/bcm.d/rc.soc`

This is the **actual sequence switchd runs to bring up the chip**. It is
the runtime equivalent of the bcm_init dispatch chain we reverse-engineered
statically.

```
debug -PCi -SChan -SOCMEM -SYMTAB -VERInet -L3 -INTr -ARL -ARLMon \
      -L2table -DMA -POrt -PAcket -TX -RCLOAD -TEsts -VERbose -MIIm \
      -PHY -END -LInk -CounTeR -IP -STP -VLAN -RX -I2C -REG -MEM -STK

attach *                                   # attach to all chip devices
0:                                         # select unit 0
init all                                   # run bcm_init dispatch chain
rcload /etc/bcm.d/rc.ports_0               # load port-map ($allports etc.)
setreg xmac_tx_ctrl 0xc802                 # set XMAC TX control
s MAC_RSV_MASK MASK=0x18                   # set MAC RSV mask
m cmic_misc_control LINK40G_ENABLE=1       # enable 40G link
0: rcload /var/lib/cumulus/rc.datapath_0   # apply per-port datapath
```

### rc.led — LED uController boot

```
led 0 stop                       # halt LED uC #0
led 0 auto on                    # enable autonomous mode
led 0 load /etc/bcm.d/led0.hex   # load 187-line bytecode
led 0 start                      # start uC #0
led 1 stop / auto on / load /etc/bcm.d/led1.hex / start  # uC #1
```

Two LED uControllers (one per stack of ports) — each runs ~200 lines
of asm reading `LINKSCAN_P` (a port-data array updated by switchd at
periodic intervals) and driving the front-panel LEDs autonomously.

### rc.ports_0 — port environment

```
setenv allports xe0-xe51         # all 52 ports
setenv 40Gports xe48-xe51        # last 4 ports support 40G
setenv 10Gports xe0-xe47         # first 48 are 10G only
```

### config.bcm — SDK parameters

Key parameters (verified live on 2026-05-11):

| Parameter | Value | Meaning |
|---|---|---|
| `polled_irq_mode` | 0 | Interrupt-driven, NOT polled |
| `bcm_stat_flags` | 0x1 | Counter DMA enabled |
| `l2xmsg_mode` | 1 | L2 FIFO mode (not poll) for table change |
| `miim_intr_enable` | 1 | MII operations use interrupts (~70µs each) |
| `tdma_intr_enable` | 1 | Table DMA uses interrupts |
| `tslam_intr_enable` | 1 | Table SLAM DMA uses interrupts |
| `tslam_dma_enable` | 1 | SLAM DMA enabled |
| `table_dma_enable` | 1 | Table DMA enabled |
| `parity_enable` | 1 | Memory parity checking |
| `xgxs_lcpll_xtal_refclk` | 1 | XGXS LCPLL uses crystal ref |
| `bcm_xlate_port_map.BCM56634` | bcm56636_single_modid | Port-to-modid translation |
| `pbmp_xport_xe.0` | 0x1ffffffffffffe | XE port bitmap (52 ports) |
| `pbmp_valid.0` | 0x2001fffffffffffff | Valid ports incl. CPU (bit 64) |
| `phy_ext_rom_boot` | 0 | PHY firmware via MDIO, not external ROM |
| `portmap_1.0..portmap_52.0` | `phy:speed` | 52-port mapping table |

### IMPORTANT: chip identity in SDK

The PCI device ID is **0xb846 (BCM56846)**, but the SDK code path uses
**BCM56634** as the family base. Config has:
```
bcm_xlate_port_map.BCM56634=bcm56636_single_modid
bcm_xlate_sysport_enable.BCM56634=1
```

And a comment: `CUMULUS 56845 requires a portmap in the config, otherwise bcm_init segfaults`.

So the chip identifies in multiple ways:
- Silicon ID:  BCM56846 (PCI device 0xb846)
- SDK family:  BCM56634 (Trident base)
- Cumulus tag: 56845

For EdgeNOS code paths that branch on chip ID, recognize **0xb846** as
the authoritative PCI device ID.

### rc.datapath_0 — buffer + QoS init

Generated by `/usr/lib/cumulus/update-ports` (a Python tool). It computes:
- Buffer cell allocation per service pool (4 pools, 46080 cells total)
- Per-port-group cell limits (PG0=18432, PG7=64, PG2=64)
- Per-queue minimum/shared limits (UC, MC, CPU)
- Priority → traffic class mapping (PCP → internal pri)
- Flow control (default: PFC off, pause-rx on)
- Color-aware mode (off by default)

This is the **MMU (Memory Management Unit) configuration** — what
buffer space each port/queue gets. Critical for forwarding without
head-of-line blocking and for correct behavior under congestion.

---

## 15. Files referenced

- `/proc/iomem` — physical memory map
- `/proc/interrupts` — IRQ counters
- `/proc/linux-kernel-bde` — kernel BDE state
- `/proc/linux-user-bde` — user BDE state
- `/proc/$(pidof switchd)/maps` — switchd address space
- `/proc/$(pidof switchd)/fd/*` — switchd file descriptors
- `/sys/bus/pci/devices/0000:01:00.0/` — BCM56846 PCI device
- `/sys/class/eeprom_dev/` — SFP+ EEPROM endpoints
- `/sys/bus/i2c/devices/` — full I²C topology

*Captured 2026-05-11 from live AS5610-52X chassis at 10.1.1.212
running Cumulus Linux 2.5.0 baseline.*

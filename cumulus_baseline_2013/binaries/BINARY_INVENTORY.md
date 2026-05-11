# Binary Inventory — what's now local for offline RE

Everything pulled from the running Cumulus 2.5.0 chassis (10.1.1.212) so
we can analyze offline. All in `extracted/` mirroring the on-switch paths.

## Big binaries (closed-source — Ghidra targets)

| File | Size | Type | What it does |
|---|---|---|---|
| `usr/sbin/switchd` | **31.7 MB** | PowerPC ELF, stripped, dynamically linked | The main Cumulus daemon. BCM SDK is **statically linked in** (~19 MB .text). Talks to /dev/linux-user-bde, owns 52 TUN fds, programs the chip. Linked against libnl, libnet, libfuse. |
| `usr/lib/cumulus/datapath-update` | 219 KB | **Python script** | Reads ports.conf, generates rc.datapath_0. NOT a binary — readable source. |
| `usr/lib/cumulus/ledasm` | 34 KB | PowerPC ELF, **NOT stripped** (has debug_info) | The LED uController **assembler**. Reads `.asm` source, emits `.hex` bytecode. Debug symbols make this trivial to RE. |
| `usr/lib/cumulus/iorw` | 9.9 KB | (binary) | Direct I/O register read/write tool |
| `usr/sbin/clagd` | 92 KB | binary | Cumulus MLAG daemon |
| `usr/sbin/lldpd` | 146 KB | binary | LLDP daemon (open-source upstream) |

## Kernel modules (binary .ko, useful for RE)

| File | Size | What |
|---|---|---|
| `linux-kernel-bde.ko` | (in /lib/modules) | BCM SDK kernel-side BDE — provides /dev/linux-user-bde, MIIM/SCHAN, DMA |
| `linux-user-bde.ko` | | User-side BDE — exposes the chardev interface |
| `linux-bde-i2c.ko` | | I2C-based device enumeration |
| `linux-bde-tmon.ko` | | BCM ASIC die temp sensor driver |
| `accton_as5610_52x_cpld.ko` | 157 KB | The CPLD platform driver (already extracted earlier) |
| `ds100df410.ko` | 141 KB | Retimer driver (already extracted) |
| `gpio-pca953x.ko` | 160 KB | GPIO expander (LPMode/ResetL control) |
| `max6697.ko` | 154 KB | 7-channel board temp sensor driver |
| `sff_8436_eeprom.ko` | 170 KB | QSFP EEPROM driver |

## PHY firmware (CRITICAL — needed for Warpcore)

| File | Size | Target |
|---|---|---|
| `usr/share/cumulus/phy_ucode/BCM84740-ver-D102.bin` | **32 KB** | **Warpcore B0** — this is what loads into our PHYs at PHY MDIO 0xd1, 0xd5, etc. EdgeNOS needs this exact blob. |
| `usr/share/cumulus/phy_ucode/BCM84754-ver-D102.bin` | 32 KB | Different Warpcore variant (not used on AS5610-52X) |
| `usr/share/cumulus/phy_ucode/BCM8754-ver-0411.bin` | 16 KB | Older PHY family (Apollo?) |

Loaded by `/etc/init.d/phy_ucode_update` → `/usr/lib/cumulus/phy-update`
(Python script, 22 KB) → MDIO download to the chip (`phy_ext_rom_boot=0`
in config.bcm forces MDIO method).

## BCM SDK chip config (`etc/bcm.d/`)

The complete BCM init recipe for this chassis:

| File | Size | Role |
|---|---|---|
| `rc.soc` | 1.5 KB | Master BCM SDK init script. `attach *`, `init all`, then loads sub-scripts. |
| `config.bcm` | 6 KB | BCM SDK boot config (polled_irq_mode, miim_intr_enable, parity_enable, port maps) |
| `config.d/01config.bcm` | | Drop-in config supplement |
| `config.d/02sdk.bcm` | | SDK-level config |
| `config.d/10phy-ucode.bcm` | | PHY ucode load instructions |
| `config.d/11ports.bcm` | | Per-port BCM config |
| `config.d/12portwd.bcm` | | Port watchdog config |
| `rc.phy` | 103 B | PHY init script (probably calls phy-update) |
| `rc.led` | 240 B | LED init — loads `led0.hex` and `led1.hex` into CMIC LED uController |
| `rc.ports_0` | 178 B | Port-mode init for unit 0 |
| `led0.asm` | **5.1 KB** | **Full LED uController assembly source for ports 1-32** |
| `led0.hex` | 784 B | Compiled bytecode (= what bcmcmd "led 0 dump" showed live) |
| `led1.asm` | 5.2 KB | LED uController source for ports 33-52 + QSFPs |
| `led1.hex` | 784 B | Compiled bytecode for unit 1 |
| `backend_map` | 29 B | Backend ASIC family identifier |
| `datapath/` | (dir) | Datapath config tree (traffic.conf etc.) |

## Cumulus tools (`usr/lib/cumulus/`)

| File | Type | Role |
|---|---|---|
| `bcmcmd` | shell wrapper (1.2 KB) | wraps `/usr/sbin/switchd -dshell` for `bcmcmd "..."` syntax |
| `update-ports` | Python (8 KB) | reads ports.conf, generates porttab/phytab/sfptab/led0/1.asm/rc.datapath_0 |
| `datapath-update` | Python (219 KB) | larger config generator — full datapath config |
| `phy-update` | Python (22 KB) | loads PHY ucode via MDIO at boot |
| `ledasm` | PowerPC ELF (34 KB, unstripped) | LED uController assembler — converts .asm → .hex |
| `iorw` | PowerPC ELF (9.9 KB) | Direct I/O register access tool |
| `cl-platform` | shell (1.9 KB) | Platform-detect helper |
| `datapath-config` | Python (5 KB) | Helper for datapath-update |
| `sysled-mgmt` | (4.8 KB) | System LED management daemon helper |
| `start-stop-monitor` | shell (2.4 KB) | Service supervision wrapper |
| `udev-module` | (940 B) | udev hook for module loading |
| `autoprovision` | shell (12 KB) | ZTP auto-provisioning |
| `ztp-usb` | Python (6 KB) | USB ZTP script |
| `brctl.cl` | shell (8 KB) | Cumulus-wrapped brctl |

## Notable strings from switchd

Build environment confirms it's the official Cumulus build:
```
/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/...
```

References to:
* `/etc/cumulus/.license.txt`
* `/etc/cumulus/switchd.conf`
* `/etc/cumulus/datapath/traffic.conf`
* `Switchd version`
* iptables/ip6tables/ebtables rule conversion
* Netlink listening (link family, neigh family, addr build)
* hashtable, sfs, log, poll, itimer lib calls

## High-value RE targets

1. **switchd binary** (31.7 MB):
   * Load into Ghidra (PowerPC big-endian 32-bit, GLIBC 2.0-2.4)
   * Find `bcm_port_init`, `bcm_l2_addr_add`, `bcm_l3_*` symbol patterns
   * Trace the TUN read → DCB build → BDE ioctl path
   * Compare port-up sequence to our OpenMDK in EdgeNOS

2. **ledasm** (with debug symbols):
   * Disassemble for the full LED uController opcode table
   * Confirms our hand-decoded bytecode is correct

3. **Warpcore PHY firmware** `BCM84740-ver-D102.bin`:
   * Binary blob loaded into the PHY's internal CPU
   * EdgeNOS needs this exact file
   * Possibly RE-able as a firmware blob

4. **`datapath-update` Python source** (219 KB):
   * Trivial to read — Python source!
   * Shows exactly how `ports.conf` becomes the per-port BCM config
   * EdgeNOS can fork this directly

5. **`led0.asm` + `led1.asm`**:
   * Full LED uController program — autoritative source
   * Confirms our existing `leddance/passthrough.asm` syntax
   * The `equ` constants define the chip's internal data layout
     (LINKSCAN_P=0x80, PORTSTATUS_P=0x00, BLINK_STATE_P=0xf1, etc.)

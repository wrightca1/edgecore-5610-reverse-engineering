# Cumulus Linux 2.5.0 Runtime Inventory

Complete catalog of every Cumulus-specific binary, script, and init
service on the running AS5610-52X chassis. Built from the extracted
rootfs at `/home/smiley/edgecore/extracted/2.5.0-powerpc/rootfs/`.

**Total files:** 988 executables (101 in /bin, 137 in /sbin, 497 in
/usr/bin, 148 in /usr/sbin, 17 in /usr/lib/cumulus, 19 in /usr/cumulus/bin,
69 init scripts). Most are standard Debian Wheezy tools. This document
covers the **~70 Cumulus-specific entries**.

---

## 1. The Cumulus daemon set (long-running services)

These are the daemons that run continuously to operate the switch.

### Critical (must run for the box to function as a switch)

| Daemon | Type | Size | Function | Doc reference |
|---|---|---|---|---|
| **`switchd`** | ELF PPC32 | 31.7 MB | THE main chip-controller daemon. BCM SDK statically linked. Hosts FUSE filesystem at `/cumulus/switchd/`. Translates netlink → BCM API → SCHAN → chip. | `BCM_INIT_STATIC_CHAIN.md`, `BLOCK_INIT_DEEP_DIVE.md`, `fuse-explore/SWITCHD_SFS_INTERNALS.md` |
| **`pwmd`** | Python | ~20 KB | Fan PWM controller (linear interpolation: thermal-zone temp → fan-speed PWM). Reads thermal sensors via lm-sensors → drives PWM via CPLD. | `PLATFORM_DAEMONS_REVERSE_ENGINEERED.md` |
| **`smond`** | Python | ~50 KB | Sensor monitor — polls voltages/temps/fan-tachs, dispatches to status LED on CPLD, logs to syslog. | `PLATFORM_DAEMONS_REVERSE_ENGINEERED.md` |
| **`ledmgrd`** | Python | ~30 KB | LED manager — loads LED uController bytecode (.hex), drives per-port LED patterns based on link state via CPLD register 0x13. | `LED_ARCHITECTURE.md`, `LED_CPU_INTERFACE.md` |
| **`portwd`** | Python | ~20 KB | Port flap watchdog — detects rapid link bounces, takes corrective action (e.g., disable port). | `PLATFORM_DAEMONS_REVERSE_ENGINEERED.md` |

### Optional / Topology

| Daemon | Type | Size | Function |
|---|---|---|---|
| **`lldpd`** | ELF PPC32 | 146 KB | LLDP daemon — standard open-source `lldpd` (vincentbernat/lldpd). Sends/receives LLDP frames, advertises chassis info, learns neighbor info. Provides data to `ptmd` via Unix socket. |
| **`ptmd`** | ELF PPC32 | 429 KB | **Prescriptive Topology Manager** (Cumulus) — reads a topology file (`/etc/cumulus/topology.dot`), validates against actual LLDP neighbors, runs BFD sessions to detect link failures. Reports topology drift. **Cumulus-proprietary**, not in our extracted rootfs of switchd-only — would need separate analysis if needed. |
| **`mstpd`** | init script only | n/a | MSTP daemon — open-source MSTP from `mstpd` package. Init script present but binary not in this rootfs extraction. Use upstream. |
| **`clagd`** | Python | 92 KB | **MLAG daemon** (Cumulus Link AGgregation). Syncs L2 FDB/MDB across two switches over peer-link. Uses `bcmshell` to talk to switchd. | `FP_MMU_AND_REMAINING.md` § clagd |
| **`clcmd_server`** | (init script) | n/a | "cl-command-server" — RPC backend for `cl-cfg` and other cl-* tools. Listens on a Unix socket. |
| **`ptpd`** | ELF | (standard) | IEEE 1588 PTP daemon — standard open-source. Time synchronization. |
| **`snmpd`** | ELF | (standard) | SNMP daemon — standard net-snmp. Exposes interface stats, chassis info via SNMP. |
| **`monit`** | (init script) | n/a | Daemon monitor — restarts crashed Cumulus daemons. Standard upstream. |

---

## 2. Cumulus user-facing tools (`/usr/cumulus/bin/cl-*`)

The `cl-*` tools — Cumulus's user-facing CLI utilities. All Python (or
bash wrappers). Available in `$PATH`.

| Tool | Type | Lines | Function |
|---|---|---|---|
| **`cl-acltool`** | Python | 1435 | Install/clear iptables rules → BCM Field Processor TCAM entries. Talks to switchd via FUSE `/cumulus/switchd/ctrl/acl/`. | `ghidra-analysis/CL_ACLTOOL_FLOW.md` |
| **`cl-brctl`** | symlink → `brctl.cl` | 322 | Wrapper around `brctl` (bridge utility). Translates bridge config to switchd-aware ops. |
| **`cl-cfg`** | Python | 483 | Configuration tool — reads/writes /etc/cumulus/switchd.conf and friends. |
| **`cl-ecmpcalc`** | symlink → `ecmpcalc` | 936 | Calculate which ECMP member gets a given flow's hash. Queries chip RTAG7 config + ECMP group state. |
| **`cl-encoder`** | Python | 1189 | Output formatter for cl-* tools (column layout, JSON, plain text). Library for the others. |
| **`cl-img-clear-overlay`** | shell | — | Reset image overlay (RW layer on read-only base). |
| **`cl-img-install`** | shell | — | Install Cumulus image to other slot. |
| **`cl-img-pkg`** | shell | — | Package an image. |
| **`cl-img-select`** | shell | — | Select which slot to boot. |
| **`cl-license`** | bash | — | License install. Reads PGP-signed `.license.txt`, validates, installs to `/etc/cumulus/.license.txt`. **License has clock dependency** (expires 2013-11-27 for our copy). |
| **`cl-netstat`** | Python | 262 | Like `netstat -i` but with delta calc (rates instead of totals). |
| **`cl-ns-mgmt`** | Python | 1015 | Linux network namespace management. Creates `mgmt` netns for eth0 (management plane separation). |
| **`cl-resource-query`** | Python | 150 | Query chip-resource occupancy: routes, hosts, ACL entries, FP slices. Reads from `/cumulus/switchd/run/`. |
| **`cl-route-check`** | Python | 578 | Compare kernel routes/neighbors vs chip routes/neighbors. Prints diffs. Exit 1 on mismatch. |
| **`cl-sfputil`** | Python | 750 | SFP+ / QSFP+ module utility. Reads DOM (digital optical monitoring) bytes via I²C. |
| **`cl-support`** | bash | 196 | Generate support bundle — tar.gz of /var/log + configs + chip state. |
| **`cl-vrr`** | bash | 447 | Virtual Router Redundancy (VRR / VRRPv3) config. |
| `decode-syseeprom` | Python | 295 | Decode the system TLV EEPROM (manufacturer info, MAC, board rev, S/N) per ONIE TLV format. |
| `ecmpcalc` | Python | 936 | Same as `cl-ecmpcalc` (the symlink target). |

---

## 3. Cumulus utility tools (`/usr/lib/cumulus/`)

Internal utilities used by daemons and init scripts.

| Tool | Type | Function | Doc reference |
|---|---|---|---|
| **`autoprovision`** | Python (422 lines) | ZTP (Zero-Touch Provisioning). Runs at first boot — checks DHCP for a provisioning URL, fetches + runs a config script. |
| **`bcmcmd`** | bash wrapper | The `bcmcmd` user CLI — wraps `bcmsh` (the bcmsh CLI client) for switchd FUSE socket. |
| **`brctl.cl`** | Python (322) | Bridge control wrapper (target of `cl-brctl` symlink). Translates `brctl` cmds to FUSE-aware ops. |
| **`cl-platform`** | shell | Platform detection. Returns chip-family (TridentChip etc.), board ID. Used by datapath-update. |
| **`datapath-config`** | Python (149) | Datapath config reader — parses `/etc/cumulus/datapath/traffic.conf`. |
| **`datapath-update`** | Python (4785) | Generates `rc.datapath_0` from ports.conf + traffic.conf. Big script with chip-family register managers. | `PHY_ENTRY_CHAIN_AND_REMAINING.md` § 2 |
| **`iorw`** | ELF PPC32 (9.9 KB) | Direct MMIO read/write tool. `iorw r.l <addr>` reads, `iorw w.l <addr> <val>` writes. Uses /dev/mem mmap. Limited to sub-windows 0-2 of BAR0. |
| **`ledasm`** | ELF PPC32 (30 KB) | LED uController bytecode assembler. Compiles .S sources to .hex files. | `LED_ARCHITECTURE.md` |
| **`phy-update`** | Python (697) | PHY firmware uploader. Halts PHY 8051 via MDIO 0x1c.1c, uploads 32 KB firmware byte-by-byte via 0x1c.18, verifies checksum at 0x1c.40, releases reset. | `PHY_ENTRY_CHAIN_AND_REMAINING.md` § 1 |
| **`portsamp`** | Python (51) | Configure packet sampling (sFlow-style) on physical interfaces. Calls `bcmcmd`. |
| **`start-stop-daemon.cl`** | shell | Cumulus's daemon start/stop wrapper (replaces /usr/bin/start-stop-daemon for some daemons). |
| **`start-stop-monitor`** | shell | Monit integration — registers daemons with monit for restart-on-crash. |
| **`sysled-mgmt`** | Python (169) | System LED (chassis-level status LEDs: power, fault, fan). Drives CPLD register. |
| **`tail.cl`** | shell | `tail` wrapper (the bbox `tail` had busybox quirks). |
| **`udev-module`** | shell | udev handler — runs when a kernel module is loaded/unloaded. Sets up device nodes for BDE etc. |
| **`update-ports`** | Python (~8 KB) | Generates `portmap_N.0=phys:speed` config from ports.conf. |
| **`ztp-usb`** | Python (188) | USB-based ZTP — when a USB stick is inserted at boot, runs autoprovision from it. |

---

## 4. /etc/init.d scripts

69 init scripts total. Below is the Cumulus-added subset (the rest are
Debian Wheezy standard: bootlogd, checkfs.sh, cron, etc.).

### Cumulus-specific init scripts

| Script | Type | Calls | Boot order | Purpose |
|---|---|---|---|---|
| **`hw_init`** | shell | `S10gpio_init.sh`, `S20retimer_init.sh` from platform-config | **Very early** | Hardware init: GPIO setup (LPMode, ResetL, ModSel for QSFPs), retimer init (CDR reset, EQ config). | 
| **`phy_ucode_update`** | shell | `phy-update` | After hw_init | Uploads PHY firmware to all BCM84740 PHYs. Runs once at boot before switchd. |
| **`clinit`** | shell | Cumulus boot prep | Early | Cumulus boot tasks — clear state, prepare /var, init logging. |
| **`cl-l2tune`** | shell | sysctl, ethtool | Early | Linux network-stack tuning — sysctls for TCP/UDP, neigh cache sizes. |
| **`aclinit`** | shell | `cl-acltool --boot` | After switchd ready | Apply iptables rules from `/etc/cumulus/acl/policy.conf` to FP TCAM. |
| **`acltool`** | shell | `cl-acltool` | (manual) | Wrapper for ACL operations. |
| **`switchd`** | bash | start-stop-daemon → switchd | After hw_init, phy_ucode_update | Start the BCM chip daemon. |
| **`autoprovision`** | bash | autoprovision Python | First boot only | Run ZTP if no config present. |
| **`ztp-usb`** | bash | ztp-usb Python | First boot only | USB-based ZTP. |
| **`pwmd`** | shell | start-stop-daemon → pwmd | After hw_init | Fan PWM control. |
| **`smond`** | shell | start-stop-daemon → smond | After hw_init | Sensor monitor. |
| **`ledmgrd`** | shell | start-stop-daemon → ledmgrd | After switchd ready | LED manager. |
| **`portwd`** | shell | start-stop-daemon → portwd | After switchd ready | Port flap watchdog. |
| **`clagd`** | shell | start-stop-daemon → clagd | After switchd, optional | MLAG daemon. |
| **`mstpd`** | shell | start-stop-daemon → mstpd | After switchd, optional | MSTP daemon. |
| **`lldpd`** | shell | start-stop-daemon → lldpd | After switchd | LLDP daemon. |
| **`ptmd`** | shell | start-stop-daemon → ptmd | After lldpd | Topology manager. |
| **`ptpd`** | shell | start-stop-daemon → ptpd | Optional | PTP daemon. |
| **`clcmd_server`** | bash | RPC server | After clinit | Backend for cl-* tools. |
| **`arp_refresh`** | shell | iproute2 commands | Periodic via cron | Refresh stale ARP entries. |
| **`monit`** | shell | start monit | Late | Daemon monitor (restart-on-crash). |

### Standard Debian Wheezy init scripts (kept for completeness)

`bootlogd`, `bootlogs`, `bootmisc.sh`, `checkfs.sh`, `checkroot-bootclean.sh`,
`checkroot.sh`, `cron`, `halt`, `hostname.sh`, `hwclock.sh`, `kmod`,
`killprocs`, `motd`, `mountall-bootclean.sh`, `mountall.sh`,
`mountdevsubfs.sh`, `mountkernfs.sh`, `mountnfs-bootclean.sh`,
`mountnfs.sh`, `mtab.sh`, `networking`, `ntp`, `procps`, `quagga` (BGP/OSPF
daemon), `rc`, `rc.local`, `rcS`, `reboot`, `rmnologin`, `rsyslog`,
`sendsigs`, `single`, `skeleton`, `ssh`, `stop-bootlogd`, `sudo`,
`umountfs`, `umountnfs.sh`, `umountroot`, `urandom`, `auditd`,
`isc-dhcp-relay`, `isc-dhcp-server`, `lm-sensors`, `openvswitch-vtep`.

---

## 5. Cron jobs

| Path | Trigger | What it does |
|---|---|---|
| `/etc/cron.daily/apt` | daily | Standard Debian apt update (clock-rolled may break this) |
| `/etc/cron.daily/debsums` | daily | Verify .deb file checksums |
| `/etc/cron.daily/dpkg` | daily | Maintain dpkg state |
| `/etc/cron.daily/logrotate` | daily | Rotate /var/log files |
| `/etc/cron.daily/man-db` | daily | Update man database (often disabled to save flash) |
| `/etc/cron.daily/ntp` | daily | NTP stats |
| `/etc/cron.daily/passwd` | daily | Validate /etc/passwd |
| **`/etc/cron.hourly/sfputil_dom_check`** | hourly | **Cumulus-specific**: poll SFP+ DOM values, log temperature/Vcc/Rx-power for monitoring. |
| `/etc/cron.weekly/debsums` | weekly | Weekly .deb checksum |
| `/etc/cron.weekly/man-db` | weekly | Weekly man-db |

The only Cumulus-specific cron is **sfputil_dom_check** (hourly SFP DOM polling).

---

## 6. /etc/network hooks

Cumulus is sparse here — only `ethtool` and standard hooks.

| Hook | Script | What it does |
|---|---|---|
| `if-pre-up.d/ethtool` | shell | Apply ethtool settings from /etc/network/interfaces |
| `if-up.d/ethtool` | shell | (same, post-up) |
| `if-up.d/mountnfs` | shell | Mount NFS if listed in fstab and interface is up |
| `if-up.d/openssh-server` | shell | Trigger sshd to listen on new interface |

**No `swp*` or chip-specific hooks** — switchd handles all chip
configuration; `ifup swp1` just sets the kernel netdev state, which
switchd reads via netlink.

---

## 7. /etc/bcm.d — chip init scripts

These are loaded by switchd's embedded `bcmsh` CLI during init:

| File | Purpose | Doc reference |
|---|---|---|
| `rc.soc` | Master chip init script (run after `init all`). Decoded line-by-line. | `ASIC_INIT_COOKBOOK.md` |
| `rc.ports_0` | Port-group env vars (`allports`, `40Gports`, `10Gports`) | `ASIC_INIT_COOKBOOK.md` § 6 |
| `rc.led` | LED uController bytecode load | `LED_ARCHITECTURE.md` |
| `config.bcm` | BCM SDK config (`portmap_N.0`, feature flags) | `ASIC_INIT_COOKBOOK.md` § 4 |
| `led0.hex` / `led1.hex` | LED uController compiled bytecode | `LED_ARCHITECTURE.md` |

---

## 8. /etc/cumulus/

Cumulus-specific config files:

| File / dir | Purpose |
|---|---|
| `/etc/cumulus/ports.conf` | Per-port type definitions (10G, 40G, 4x10G breakouts) |
| `/etc/cumulus/switchd.conf` | switchd daemon config (logging level, IRQ mode, etc.) |
| `/etc/cumulus/.license.txt` | PGP-signed license (clock-bound) |
| `/etc/cumulus/datapath/traffic.conf` | Packet priorities, color, COS-to-PG mapping |
| `/etc/cumulus/datapath/forwarding.conf` | Forwarding config (RTAG7, CPU steer) |
| `/etc/cumulus/clagd.conf` | MLAG config (peer-link, system MAC) |
| `/etc/cumulus/topology.dot` | ptmd topology file |
| `/etc/cumulus/acl/policy.conf` | iptables rules to install at boot |

---

## 9. ELF binaries we haven't analyzed yet

These are full binaries that we may or may not need:

| Binary | Size | Status | Importance for EdgeNOS |
|---|---|---|---|
| `ptmd` | 429 KB | Not analyzed | **Optional** — only if you want enforced topology. |
| `lldpd` | 146 KB | Standard OSS | **Optional** — use upstream `vincentbernat/lldpd`. |
| `snmpd` | (varies) | Standard OSS | **Optional** — use upstream net-snmp. |
| `ptpd` | (varies) | Standard OSS | **Optional** — use upstream `ptpd`. |
| `tcpdump` | 853 KB | Standard OSS | **Optional** — debugging. |
| `dhcpd` / `dhcrelay` | (varies) | Standard ISC | **Optional** — server-mode DHCP. |
| `ovs-vtepd` | 664 KB | OVS for VxLAN VTEP | **Optional** — VxLAN feature. |
| `ovsdb-server` | 327 KB | OVS database | **Optional** — OVS dep. |
| `rsyslogd` | 373 KB | Standard syslog | **Required** — but use upstream. |
| `ntpd` | 502 KB | Standard NTP | **Optional** — use chrony or upstream NTP. |
| `mz` | 452 KB | mausezahn packet gen | **Optional** — testing tool. |

---

## 10. Boot order (best reconstruction)

Based on init.d script symlinks in `/etc/rcS.d`, `/etc/rc2.d`, etc.:

```
1. Kernel boot → init
2. /etc/init.d/rcS runs:
   - mountkernfs, mountdevsubfs, checkroot, mountall, kmod
   - hostname.sh, hwclock.sh, urandom
3. /etc/init.d/rc 2 (multi-user):
   - clinit                  (Cumulus boot prep)
   - rsyslog                 (logging)
   - hw_init                 (GPIO + retimer init)
   - phy_ucode_update        (PHY firmware upload)
   - cl-l2tune               (network sysctls)
   - networking              (bring up eth0)
   - switchd                 (THE big one)
   - aclinit                 (iptables → FP TCAM)
   - pwmd, smond             (sensors / fans)
   - ledmgrd                 (LEDs)
   - portwd                  (port watchdog)
   - lldpd                   (LLDP)
   - ptmd                    (topology mgmt)
   - mstpd                   (STP, optional)
   - clagd                   (MLAG, optional)
   - clcmd_server            (cl-* RPC backend)
   - quagga                  (BGP/OSPF daemons)
   - ssh, cron, monit        (standard services)
```

---

## 11. For EdgeNOS — what to replicate

To bring an open-source NOS up to feature parity with Cumulus 2.5,
EdgeNOS needs equivalents for:

### Required (chip operation)
- ✅ `hw_init` equivalent — GPIO setup + retimer init (we have the scripts in `platform-config-accton-as5610_52x/hw_init.d/`)
- ✅ `phy_ucode_update` — done via custom code or borrow `phy-update`
- ✅ `switchd` equivalent — this is what EdgeNOS IS
- ⚠️ `datapath-update` equivalent — needed if you want to regenerate `rc.datapath_0` from ports.conf changes; otherwise reuse Cumulus's

### Recommended (for proper operation)
- ✅ Fan/sensor daemon equivalent (`pwmd` + `smond`) — small Python, can port
- ✅ LED manager equivalent — bytecode is in `led0.hex`/`led1.hex`, just upload it
- ⚠️ Port flap watchdog — small Python, can adopt

### Optional (control-plane features)
- LLDP — use upstream `lldpd`
- MSTP — use upstream `mstpd`
- BGP/OSPF — use upstream FRRouting (modern replacement for Cumulus's Quagga)
- ACL — implement the iptables → FP TCAM translation (we have CL_ACLTOOL_FLOW.md as reference)
- MLAG (clagd) — only if you need it
- ZTP — only if you want auto-provisioning

### NOT needed
- `cl-license` (you don't need a license)
- `cl-cfg` / `cl-encoder` etc. — these are CLI tools; EdgeNOS can have its own UX
- `monit` — use systemd's restart-on-failure
- Cumulus-specific cron jobs

---

## 12. File system layout summary

```
/
├── etc/
│   ├── init.d/                 # 69 init scripts (Cumulus + Debian)
│   ├── bcm.d/                  # rc.soc, rc.ports_0, config.bcm, rc.led, led{0,1}.hex
│   ├── cron.{hourly,daily,weekly}/
│   ├── cumulus/                # Cumulus config files
│   │   ├── ports.conf
│   │   ├── switchd.conf
│   │   ├── .license.txt
│   │   └── datapath/
│   ├── network/                # interfaces, if-*.d hooks
│   ├── ssh/
│   └── ...
├── usr/
│   ├── bin/                    # 497 standard Debian + a few Cumulus
│   ├── sbin/                   # 148 daemons (switchd here)
│   ├── cumulus/bin/            # cl-* tools
│   ├── lib/cumulus/            # internal utilities
│   ├── lib/python2.7/dist-packages/cumulus/  # Python modules
│   └── share/cumulus/          # data files (firmware, defaults)
├── cumulus/
│   └── switchd/                # FUSE mount point (mounted by switchd)
├── var/log/                    # log files
└── lib/modules/3.2.60-1+deb7u1+cl2.5/extra/  # Cumulus kernel modules
    ├── linux-kernel-bde.ko     (504 KB)
    ├── linux-user-bde.ko       (428 KB)
    ├── linux-bde-i2c.ko        (186 KB)
    ├── linux-bde-tmon.ko       (153 KB)
    └── accton_as5610_52x_cpld.ko (157 KB)
```

---

## 13. Summary — what each Cumulus daemon does and why

The minimum daemon set for a working switch:

1. **`switchd`** — controls the ASIC. Without this, no packets flow.
2. **`pwmd`** — keeps the chip cool. Without it, the chip throttles or burns.
3. **`smond`** — monitors environmental sensors. Without it, you can't
   detect overheat / fan failure / voltage anomaly.
4. **`ledmgrd`** — drives status LEDs. Cosmetic but operationally
   important for troubleshooting.
5. **`portwd`** — prevents flap storms. Optional but recommended.
6. **`lldpd`** — neighbor discovery. Optional but standard.

Everything else is optional / control-plane-specific. Total RAM
footprint for the daemon set is ~150 MB on the running chassis (mostly
switchd's BCM SDK).

---

## 14. Cross-references

- `BCM_INIT_STATIC_CHAIN.md` — switchd's chip-init internals
- `BLOCK_INIT_DEEP_DIVE.md` — switchd's per-block init details
- `PACKET_FLOW_END_TO_END.md` — switchd's packet I/O path
- `L3_L2_PROGRAMMING_FLOW.md` — switchd's netlink integration
- `fuse-explore/SWITCHD_SFS_INTERNALS.md` — switchd's FUSE control plane
- `PLATFORM_DAEMONS_REVERSE_ENGINEERED.md` — pwmd / smond / ledmgrd / portwd
- `LED_ARCHITECTURE.md` — LED uController + bytecode
- `PHY_ENTRY_CHAIN_AND_REMAINING.md` — phy-update + datapath-update + clagd
- `ghidra-analysis/CL_ACLTOOL_FLOW.md` — cl-acltool internals
- `ghidra-analysis/CPLD_REGISTER_MAP_FINAL.md` — CPLD register map

---

*Inventory compiled 2026-05-11 from extracted rootfs at
`/home/smiley/edgecore/extracted/2.5.0-powerpc/rootfs/`. All Cumulus-
specific binaries enumerated and classified. Most major daemons have
prior detailed analysis (see "Doc reference" column).*

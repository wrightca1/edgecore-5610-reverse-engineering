# Live Chassis Inventory — what static analysis missed

Companion to `CUMULUS_RUNTIME_INVENTORY.md` (which is from static rootfs
extraction). This document captures items that **only show up when
inspecting the running chassis** at `10.1.1.212` — like switchd's FUSE
mount, the runtime monit config, namespace setup, etc.

Captured 2026-05-11 via SSH to the live Cumulus 2.5.0 chassis.

---

## 1. Mounts (the FUSE mount that started this enquiry)

```
proc on /proc type proc                       (kernel state)
sysfs on /sys type sysfs                      (kernel state)
dev on /dev type tmpfs (10 MB)                (devnodes)

/dev/sysroot1 on /mnt/root-ro type squashfs (ro)
/dev/sda3 on /mnt/root-rw type ext2 (rw)
overlayfs:root on / type overlayfs            ← Cumulus is overlay-mounted!

tmpfs on /run                                 (10 MB)
tmpfs on /run/lock, /run/shm
tmpfs on /tmp (100 MB), /var/tmp (100 MB)
initramfs on /mnt/initramfs (ro)
/dev/persist on /mnt/persist type ext2        (persistent state across upgrades)
devpts on /dev/pts type devpts

/dev/fuse on /cumulus/switchd type fuse       ← switchd's FUSE control plane!
  options: rw,nosuid,nodev,allow_other,default_permissions
```

**Key findings:**
- **Cumulus is overlay-mounted**: read-only squashfs base + ext2 RW
  layer at `/mnt/root-rw/config1`. This is the "config1" slot — switching
  to slot 2 = `/mnt/root-rw/config2`. Explains how `cl-img-select` works.
- **`/dev/persist`** is a separate ext2 filesystem for state that
  survives image upgrades. (Probably licenses, certificates, ZTP state.)
- **`/cumulus/switchd`** is the FUSE mount — **invisible in static
  analysis**, only shows up when switchd is running. This is the SFS
  control plane we documented in `fuse-explore/SWITCHD_SFS_INTERNALS.md`.

---

## 2. Running processes (live `ps auxf` highlights)

What's ACTUALLY running on a healthy Cumulus 2.5.0:

| PID | RSS | Process | Notes |
|---|---|---|---|
| 22306 | 32 MB | `switchd -d` | THE chip daemon |
| 1606 | 12 MB | python pwmd | Fan control |
| 1551 | 12 MB | python ledmgrd | LED mgmt |
| 1646 | 12 MB | python smond | Sensor monitor |
| 1269 | 470 KB | `mstpd -v2` | MSTP daemon (**running, lives at `/sbin/mstpd`**) |
| 1454 | 1.6 MB | bash `/usr/bin/arp_refresh` (loop with `sleep 30`) | Periodic ARP refresh |
| 2271 | 5 MB | python `clcmd_server.py` | cl-* RPC backend at `/usr/lib/python2.7/dist-packages/clcmd_server.py` |
| 2362 | 5 MB | python ztp-usb | Auto-provisioning daemon (waiting for USB) |
| 2743 | 1.8 MB | monit | Daemon-restart watchdog |
| 31655 | 1.3 MB | lldpd -c | LLDP control process |
| 31680 | 1 MB | lldpd -c (_lldpd user) | LLDP worker (privsep) |
| 11740 | (zombie) | `script ... cl-license -i /tmp/license.txt` | **License install stuck on EULA prompt** since Jun 1 — never completed because nobody pressed Enter. Benign. |

### What's NOT running

- No `ptmd` (not installed on this chassis)
- No `clagd` (no MLAG configured)
- No `quagga` / `zebra` / `bgpd` / `ospfd` — routing daemons not started
- No `ntpd` — Cumulus uses `dhclient` for time? Or stopped due to clock-roll
- No `snmpd` — not enabled in this baseline

---

## 3. Listening sockets (TCP/UDP/Unix)

```
TCP:
  0.0.0.0:22       sshd
  127.0.0.1:2812   monit (web UI / HTTPCheck)
  :::22            sshd (IPv6)

UDP:
  *:67  + :::67    dhclient (DHCP reply)
  *:4510           dhclient (DHCP discover, IPv4)
  :::64406         dhclient (DHCPv6)
```

### Unix sockets (Cumulus IPC channels)

```
/var/run/switchd.socket      ← switchd's RPC port (separate from FUSE)
                               Listens here for `bcmsh` CLI clients
                               (`bcmcmd`, `phy-update`, `clagd`'s bcmshell module)

/var/run/lldpd.socket        ← LLDP API
                               clients: ptmd, `lldpctl`, `lldpcli`

/usr/share/cumulus/clcmd_uds ← clcmd_server's RPC port
                               clients: cl-cfg, cl-vrr, etc.

/var/run/audispd_events      ← audit subsystem
```

**Two distinct switchd interfaces!**
- `/cumulus/switchd/` (FUSE filesystem) — the structured config/run tree
- `/var/run/switchd.socket` (Unix socket) — the `bcmsh` CLI

Both serve different clients. FUSE for declarative ops (`cl-acltool` reads
/writes paths), socket for imperative CLI (`bcmcmd 'getreg CMIC_CONFIG'`).

---

## 4. Loaded kernel modules

```
Module                  Size  Used by
8021q                  20604  0           VLAN 802.1q
ds100df410              6086  0           TI retimer (Cumulus driver)
adm1021                 8639  0           ADM1021 temp sensor (hwmon)
max6697                 9564  0           Maxim 6697 multi-channel temp
gpio_pca953x           12937  61          ← PCA953x GPIO expander (CRITICAL for QSFP!)
sff_8436_eeprom        11381  0           QSFP+ SFF-8436 EEPROM driver
at24                    9322  0           AT24 family EEPROM (SFP+)
accton_as5610_52x_cpld 13854  0           Cumulus's CPLD driver
linux_bde_tmon          6674  0           BCM die-temp
tun                    18389  104         TUN/TAP (52 swp + management +
                                            test devices)
linux_user_bde         14431  0           BDE userspace
linux_kernel_bde       34398  2           BDE kernel
```

### What this reveals

1. **`gpio_pca953x` is loaded with 61 uses** — this is the critical GPIO
   expander driver for **QSFP LPMode/ResetL/ModSel**. The 61 uses suggest
   it's exposing GPIO lines for everything: 4 QSFPs × 3-4 control pins
   = ~16 pins for QSFP, plus more for PSUs, fans, status LEDs, etc.

2. **`max6697` + `adm1021`** are the temperature sensors that smond reads.

3. **`sff_8436_eeprom` + `at24`** — the I²C EEPROM drivers that expose
   SFP+/QSFP+ EEPROMs as sysfs files under `/sys/class/eeprom_dev/`.

4. **`accton_as5610_52x_cpld`** — Cumulus's CPLD driver (vs EdgeNOS's
   custom implementation). Worth comparing.

5. **`tun` has 104 uses** — that's 52 swp interfaces × 2 + ~0. Each TUN
   typically has 2 fd references (one from switchd userspace, one from
   the netdev), so 52 swp × 2 = 104. Matches.

6. **NO `linux-bcm-knet.ko`** — confirms Cumulus doesn't use KNET.

---

## 5. `/etc/cumulus/` — the actual live config

```
.license.txt              ← PGP-signed license (clock-bound)
acl/                      ← ACL config dir
datapath/                 ← Only README + traffic.conf (NO forwarding.conf!)
etc.replace/              ← OS-branding overlay (lsb-release, os-release)
init/                     ← Per-platform init configs (28 platforms)
nice.conf                 ← Process priority config
ns.conf                   ← Network namespace per-process config
ports.conf                ← Port speed config (10G/40G/4x10G)
ssmonitor.d/              ← Service monitor configs (3 daemons)
switchd.conf              ← switchd config
```

### `/etc/cumulus/init/` — Per-platform init (NEW!)

A massive directory with **23 platform-specific subdirs**:

```
accton_as4600_54t/
accton_as5610_52x/      ← OUR PLATFORM
accton_as5712_54x/
accton_as6700_32x/
accton_as6701_32x/
accton_es5652bt1/
cel_kennisis/
cel_redstone/
cel_redstone_xp/
cel_smallstone/
cel_smallstone_xp/
cumulus_cumulus_p2020/
dell_s4000_c2338/
dell_s6000_s1220/
dni_c7448n/
dni_et-6448r/
dni_et-7448bf/
mlx_sx1400_i73612/
quanta_lb9/
quanta_ly2/
quanta_ly2r/
quanta_ly6_p2020/
quanta_ly6_rangeley/
quanta_ly8_rangeley/
quanta_ly9_rangeley/
quanta_panther/

running -> accton_as5610_52x   (symlink — current platform)

amd64-init.conf
arch.conf
lsb-release
platform.conf
powerpc-init.conf
```

Plus three multi-arch config files:
- `amd64-init.conf` — x86_64-specific init
- `powerpc-init.conf` — PPC-specific init (what we care about)
- `arch.conf` — architecture selector
- `lsb-release` — Cumulus distro string
- `platform.conf` — per-platform settings

The **`running` symlink** is `clinit`'s way of finding "what platform
am I". `cl-platform` (the shell script) reads this.

For EdgeNOS, this is the **platform-detect mechanism** — set a symlink
at boot, and all subsequent scripts know what hardware they're on.

### `/etc/cumulus/ns.conf` — Network namespace config (NEW!)

```
# If a process must be restarted in a specific namespace, list it here.
switchd       default
zebra         default
bgpd          default
ripd          default
ripngd        default
ospfd         default
ospf6d        default
isisd         default
babeld        default
watchquagga   default
```

Tells `start-stop-daemon.cl` which netns to start each daemon in.
Currently all in `default`, but Cumulus supports mgmt-VRF where these
would go in `mgmt` namespace.

### `/etc/cumulus/nice.conf` — Process priority (NEW!)

```
# Higher priority processes (nice = -5)
switchd  -5
ospfd    -5
zebra    -5
ospf6d   -5
bgpd     -5
mstpd    -5

# Lower priority processes (nice = +5, ionice = best-effort:5)
cron     5  best-effort:5
monit    5  best-effort:5
inetd    5  best-effort:5
```

Critical: **switchd runs at nice -5** (high priority) to ensure chip
control isn't preempted by other tasks. Same for routing daemons.
Maintenance daemons (cron, monit) are deprioritized.

For EdgeNOS, the equivalent should be set via systemd `Nice=-5` for the
ASIC daemon.

### `/etc/cumulus/ssmonitor.d/` — Service status monitor configs (NEW!)

Three monit-style configs:
- `clagd-monit.rc` — monitor clagd
- `switchd-monit.rc` — monitor switchd
- `watchquagga-monit.rc` — monitor watchquagga (the wrapper that runs Quagga)

These aren't standard Debian monitrc snippets — they're Cumulus's own
service-status framework. Smaller scope than monit (just process
liveness checks).

### `/etc/cumulus/etc.replace/` — OS-branding overlay

Just two files:
- `lsb-release` — sets `DISTRIB_ID=Cumulus Linux`
- `os-release` — same for systemd-style `/etc/os-release`

At boot, `clinit` copies these over `/etc/lsb-release` and
`/etc/os-release` so userspace tools think the OS is "Cumulus Linux"
rather than "Debian wheezy". Clean OS-branding mechanism.

---

## 6. `/etc/monit/monitrc.d/` — Daemons under monit watch

```
cron               (standard Debian monit)
cumulus            (Cumulus's master config)
ledmgrd-monit.rc
lldpd-monit.rc
mstpd-monit.rc
openssh-server     (standard)
ptm-monit.rc
pwmd-monit.rc
smond-monit.rc
```

7 Cumulus daemons under monit (switchd is monitored via
`/etc/cumulus/ssmonitor.d/switchd-monit.rc`, not under standard monitrc.d).

monit restarts these if they crash. For EdgeNOS, **systemd's
`Restart=on-failure`** does the same thing.

---

## 7. Switchd's Unix RPC socket — separate from FUSE!

While documenting switchd's FUSE control plane, we didn't note that
switchd ALSO has a **second IPC channel**: `/var/run/switchd.socket`.

This is used by:
- `bcmcmd` — the user-facing bcmsh CLI wrapper
- `bcmshell.py` — Python module used by clagd, ecmpcalc, etc.
- Anything that does CLI-style `bcmsh 'cmd args...'` calls

The socket protocol is a simple line-oriented CLI: client writes
`bcmsh-command\n`, server runs it through the embedded bcmsh
interpreter, returns output.

This is **different** from the FUSE control plane:

| Mechanism | Path | Use case |
|---|---|---|
| FUSE | `/cumulus/switchd/` | Declarative (`cat /cumulus/switchd/config/route/max_routes`) |
| Unix socket | `/var/run/switchd.socket` | Imperative (`bcmcmd 'getreg CMIC_CONFIG'`) |

Both are present at runtime. Static analysis only revealed the FUSE
one because it's the `libfuse`-backed surface (lots of code to
implement); the socket is a smaller surface (one accept() loop).

---

## 8. Boot sequence (actual, from `ps` start times)

Process Jun01 start times let us reconstruct the actual boot order:

```
init (PID 1)         Jun01 boot
rsyslogd             Jun01  ← logging up first
mstpd                Jun01  ← MSTP (before switchd)
dhclient             Jun01  ← DHCP for eth0
arp_refresh          Jun01  ← arp daemon loop
ledmgrd              Jun01  ← LED manager
pwmd                 Jun01  ← fan PWM
smond                Jun01  ← sensors
auditd, audispd      Jun01  ← audit
cron                 Jun01  ← cron
clcmd_server         Jun01  ← cl-* RPC server
ztp-usb              Jun01  ← ZTP USB monitor
sshd                 Jun01  ← SSH
monit                Jun01  ← service watchdog
sshd: cumulus        12:03  ← my SSH session
cl-license (stuck)   Jun01  ← never completed EULA prompt
lldpd                Jun01  ← LLDP
switchd (restarted)  07:34  ← restarted earlier today (during our LD_PRELOAD experiment)
```

Interesting: **mstpd starts BEFORE switchd**. That's unusual — STP
normally needs switchd's bridge interfaces to exist. But on Cumulus 2.5,
mstpd discovers bridges via netlink and waits for them.

---

## 9. NEW items to add to the runtime inventory

Items that were missing or wrong in `CUMULUS_RUNTIME_INVENTORY.md`:

| Item | Where it lives | Doc status |
|---|---|---|
| **`/sbin/mstpd`** | `/sbin/mstpd` (195 KB ELF) | NEWLY ADDED to live findings |
| **`/usr/bin/arp_refresh`** | shell script in /usr/bin (not /usr/sbin) | Runs as continuous daemon (bash loop) |
| **`clcmd_server`** | `/usr/lib/python2.7/dist-packages/clcmd_server.py` | (not in any "bin" dir) |
| **`/etc/cumulus/init/`** | Per-platform configs | NEW — Cumulus's platform detection mechanism |
| **`/etc/cumulus/etc.replace/`** | OS branding overlay | NEW — explains how the OS reads as "Cumulus" |
| **`/etc/cumulus/ns.conf`** | netns config | NEW — daemon-to-namespace mapping |
| **`/etc/cumulus/nice.conf`** | priorities | NEW — switchd at nice=-5 |
| **`/etc/cumulus/ssmonitor.d/`** | service health configs | NEW — Cumulus's own monit-lite framework |
| **`gpio_pca953x` kernel module** | (loaded) | **Critical for QSFP LPMode/ResetL!** Not documented in our analysis |
| **`max6697`, `adm1021` modules** | (loaded) | Temperature sensors used by smond |
| **`sff_8436_eeprom`, `at24` modules** | (loaded) | SFP/QSFP EEPROM drivers |
| **`/var/run/switchd.socket`** | switchd's CLI port (Unix socket) | Distinct from FUSE plane |
| **`/dev/persist` mount** | ext2 partition for cross-upgrade state | NEW — explains where licenses live |
| **`overlayfs:root /`** | squashfs + ext2 overlay | Image-slot mechanism for `cl-img-select` |
| **`/var/run/lldpd.socket`** | LLDP API | Used by ptm + lldpctl |
| **`/usr/share/cumulus/clcmd_uds`** | cl-* RPC | Used by all cl-* tools |

---

## 10. The user was right — what static analysis missed

The user's observation that **switchd's FUSE filesystem only showed up
in runtime inspection** is part of a broader pattern. Things invisible
to pure static analysis:

1. **Mounts created at runtime** (FUSE, tmpfs, overlay slots)
2. **Unix sockets created on listen()** (switchd.socket, clcmd_uds)
3. **Kernel module dependencies that show up only when loaded** (gpio_pca953x usage count = 61)
4. **Process trees** (which daemons start which)
5. **Process state** (e.g., cl-license stuck at EULA)
6. **Overlay filesystem layering** (squashfs base + ext2 RW upper)
7. **Per-platform symlinks** (`/etc/cumulus/init/running`)

For complete coverage, we need BOTH static analysis (this is what
binaries DO when run) AND runtime inspection (what they actually have
running RIGHT NOW).

---

## 11. Updated EdgeNOS checklist

Items to add to EdgeNOS based on live findings:

### Must
- ☐ Use overlayfs with squashfs base + ext2 RW (for image-slot upgrades)
- ☐ Mount `/dev/persist` as ext2 (for state across upgrades)
- ☐ Implement equivalent of `/etc/cumulus/init/running` symlink for platform detect
- ☐ Set switchd-equivalent to `Nice=-5` in systemd unit
- ☐ Load `gpio_pca953x` kernel module (or equivalent) for QSFP LPMode control
- ☐ Load `max6697` + `adm1021` for temp sensors
- ☐ Load `sff_8436_eeprom` + `at24` for module EEPROMs
- ☐ Switchd FUSE mount at `/cumulus/switchd` (or similar)
- ☐ Switchd Unix socket for CLI (if you want bcmcmd compatibility)
- ☐ arp_refresh loop (or periodic via systemd timer)

### Should
- ☐ Implement `etc.replace`-style OS-branding (lsb-release / os-release)
- ☐ Add ns.conf-equivalent for mgmt-VRF support
- ☐ ssmonitor framework for daemon health checks
- ☐ ZTP via USB equivalent

### Optional
- ☐ MSTP via upstream mstpd
- ☐ LLDPD via upstream lldpd
- ☐ Monit equivalent (or just use systemd Restart=on-failure)
- ☐ Audit subsystem (auditd/audispd)
- ☐ ptmd / clagd (if MLAG needed)

---

## 12. Files

- `CUMULUS_RUNTIME_INVENTORY.md` — static rootfs inventory (what's on disk)
- `LIVE_CHASSIS_INVENTORY.md` (this doc) — what's actually running
- `PROVEN_WORKING_CONFIG.md` — known-good baseline at 10.1.1.212

---

*Captured 2026-05-11 via live SSH inspection of 10.1.1.212. Confirms
that static analysis alone misses runtime state — overlay mounts, FUSE
mount, Unix sockets, kernel module usage, process trees, per-platform
init configs.*

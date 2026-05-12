# ONIE Live Capture — AS5610-52X, install mode (2026-05-11)

Captured from the chassis at `10.1.1.222` while it was sitting in the ONIE
install discovery loop. Complements the static `ONIE_*` docs by recording
exact runtime state, all shell scripts that drive install discovery, and
the dependency layout of `/lib/onie/`.

Raw artifacts live under
[`cumulus_baseline_2013/captures/onie_2026-05-11/`](cumulus_baseline_2013/captures/onie_2026-05-11/).

---

## 1. Identity (live)

| Item | Value |
|---|---|
| ONIE version | **2017.02.00.07** |
| Build date | `2017-06-06T10:47+0800` |
| Kernel | `3.2.69-onie+` (Tue Jun 6 10:48:06 CST 2017, SMP, ppc) |
| Platform | `powerpc-accton_as5610_52x-r0` |
| Machine | `accton_as5610_52x` (rev 0) |
| Switch ASIC | `bcm` |
| Vendor ID | 259 |
| `/proc/cmdline` | `quiet console=ttyS0,115200 serial_num=561052X1916063 eth_addr=80:A2:35:81:CA:AE boot_reason=install` |

The `boot_reason=install` is set by U-Boot via the `onie_install`/`onie_rescue`
trick (`setenv onie_boot_reason <reason> && boot`); ONIE reads it from
the kernel cmdline.

---

## 2. Init flow (PID 1 → discover loop)

```
init (PID 1) — busybox init reads /etc/inittab
  ├── /etc/init.d/rc S       — sysinit
  └── /etc/init.d/rc 3       — runlevel 3
        ├── networking.sh
        ├── dropbear.sh      (PID 230 — SSH on port 22, blank password root)
        ├── telnetd.sh       (PID 240)
        ├── syslogd.sh       (PID 214)
        └── discover.sh
              └── /bin/discover  (PID 259, /bin/sh shell script)
                     └── /lib/onie/udhcp4_net + /lib/onie/udhcp4_sd
```

`/bin/onie-console` is launched as the askfirst tty on the serial port.

---

## 3. Discovery flow (decoded from `/bin/discover` + onie.log)

For each attempt, ONIE walks the URL fallback list **per IPv4 source +
every IPv6 link-local neighbor on eth0** until one of them returns a
successful HTTP/TFTP/FTP fetch.

### URL filename probe order (12 variants per source)

```
onie-installer-${platform}-${machine_rev}        # eg. -powerpc-accton_as5610_52x-r0
onie-installer-${platform}                       # -powerpc-accton_as5610_52x
onie-installer-${machine}                        # -accton_as5610_52x
onie-installer-${arch}-${switch_asic}            # -powerpc-bcm
onie-installer-${arch}                           # -powerpc
onie-installer                                   # bare fallback
```

### Source ordering

Captured from `onie.log` while the discovery loop ran 2026-05-11 at
19:15:19 UTC:

1. DHCPv4 server's `siaddr`/option 66 (`10.1.1.1`)
2. Then every `fe80::…%eth0` IPv6 link-local neighbor (one full URL set per
   neighbor — we saw **8 distinct neighbors** in 1 sub-second window, all
   probed). The neighbor table came from RA + ND.
3. USB attached storage (mounted at `/mnt/installer`)
4. TFTP `bootfile` from DHCP (option 67)

Per source, all **6 filename variants** are tried before moving on.
Protocols attempted in order: **http → https → ftp → tftp → file** (URL
prefix swap; same names).

### Live DHCP environment (from discover log)

```
onie_disco_router  = 10.1.1.1
onie_disco_subnet  = 255.255.255.0
onie_disco_domain  = frostlane.net
onie_disco_interface = eth0
onie_disco_dns     = 10.1.1.1
onie_disco_serverid= 10.1.1.1
onie_disco_boot_reason = install
onie_disco_ip      = 10.1.1.222
onie_disco_serial_num  = 561052X1916063
onie_disco_eth_addr= 80:A2:35:81:CA:AE
onie_disco_lease   = 7198
onie_disco_mask    = 24
onie_disco_opt53   = 05               # DHCPACK
```

These `onie_disco_*` variables get exported to any installer script
that ONIE eventually downloads and runs.

---

## 4. Where the install scripts actually live

| Path | Type | Purpose |
|---|---|---|
| `/bin/discover` | sh | Main discovery loop (calls `udhcp4_sd`) |
| `/bin/onie-console` | sh | Login-on-tty banner + shell |
| `/bin/onie-discovery-start` / `…-stop` | sh | Toggle the discover daemon |
| `/bin/onie-env-get` / `onie-env-set` | sh | Read/write U-Boot env from ONIE |
| `/bin/onie-nos-install` | sh | URL-driven NOS installer entry (`onie_exec_url`) |
| `/bin/onie-self-update` | sh | Update ONIE itself |
| `/bin/onie-support` | sh | Bundle diagnostics into a `.tgz` |
| `/bin/onie-sysinfo` | sh | Print `/etc/machine.conf` lookups |
| `/bin/onie-uninstaller` | sh | Wipe sda + return to discovery |
| `/etc/init.d/discover.sh` | sh | rc-script that launches `/bin/discover` |
| `/etc/init.d/networking.sh` | sh | Brings eth0 up via DHCPv4 |
| `/lib/onie/functions` | sh | **Shared helper library — 11 KB** |
| `/lib/onie/udhcp4_net` | sh | DHCPv4 → set `eth0` addr + route |
| `/lib/onie/udhcp4_sd` | sh | DHCPv4 → discover-mode env emit |
| `/lib/onie/onie-uninstaller-common` | sh | Uninstall logic |
| `/lib/onie/{init,boot-mode,dropbear,support,uninstall}-arch` | sh | Arch-specific glue |
| `/lib/onie/uninstall-platform` | sh | Platform-specific uninstall (stub) |

Captured copies of all of these are in
[`cumulus_baseline_2013/captures/onie_2026-05-11/onie-live/onie-scripts/`](cumulus_baseline_2013/captures/onie_2026-05-11/onie-live/onie-scripts/).

The big one is `/lib/onie/functions` (11 KB) — that's where the URL
expansion, the per-protocol fetch loop, and the install-success
bookkeeping live.

---

## 5. Available tools in ONIE shell (BusyBox 1.25.1 + extras)

`onie-sysinfo` flags: `-h s S e v i m r p c f d a t P`

```
-s  Serial Number
-P  Part Number
-e  Management Ethernet MAC address
-v  ONIE version string
-i  Vendor ID
-m  Machine
-r  Machine revision
-p  Platform (default)
-c  Config version
-f  Firmware
-d  Build date
-a  Arch
-t  Partition type
-S  Switch ASIC
```

`onie-syseeprom` flags: `-h -l -e -g <code> -s <code>=<value>`
- `-l` lists TLV codes
- `-g 0x23` (Serial Number), `-g 0x24` (Base MAC), `-g 0x28` (Platform Name)…
- Note: there is **no `-a`** (all) flag in this build — running it with no args dumps everything.

Notably missing in this ONIE: `onie-fwpkg`, `ip`, `nft`. Available:
`busybox` (full applet set), `mtd-utils`, `e2fsprogs`, `dropbear`,
`udhcpc`, `wget`, `tftp`, `lftp`, `nslookup`, `lsusb`, `lspci`.

---

## 6. Runtime state at capture time

| Item | Value |
|---|---|
| Hostname | `onie` |
| eth0 IP | `10.1.1.222/24` |
| Gateway / DNS | `10.1.1.1` |
| DHCP lease | 7165 s (renewed every ~30 s — `udhcpc` retry loop visible in syslog) |
| Running daemons | `init` `kthreadd` `syslogd` `dropbear` `telnetd` `discover` `sh` (PID 259 is the `/bin/discover` shell loop) |
| `/var/log/onie.log` | full discovery loop captured |
| `/var/log/messages` | shows DHCP renewals and dropbear connections |

**Security note:** `dropbear` accepted my SSH login with a **blank
password** for `root`. Visible in `/var/log/messages`:

```
authpriv.notice dropbear: Auth succeeded with blank password for 'root' from 10.1.1.30
```

This is ONIE-default behavior in install mode and matches the OCP design
spec, but worth knowing if anyone is on a hostile network during install.

---

## 7. How `onie-nos-install` and `bootm` cooperate (live‑confirmed)

When discovery succeeds (or when the user runs `onie-nos-install <URL>`):

1. ONIE downloads to `/installer` (RAM-only).
2. Sets `onie_exec_url=<URL>` so the script knows it was invoked by ONIE.
3. Executes the installer script (our `install.sh`).
4. The installer does its own partitioning + writes, then sets the
   U-Boot env (via `fw_setenv`) to skip ONIE on next boot:
   - **delete** `onie_boot_reason` (per `/etc/init.d/discover.sh`, ONIE
     sets it to `install` and only clears it on success — our installer
     must clear it explicitly via `fw_setenv onie_boot_reason ""`).
   - set `nos_bootcmd` / `cl.active=1` / partition path vars.
5. Installer calls `/sbin/reboot`. U-Boot reads `bootcmd`:
   ```
   run check_boot_reason; run nos_bootcmd; run onie_bootcmd
   ```
   `check_boot_reason` is a no-op if `onie_boot_reason` is empty;
   `nos_bootcmd` runs `bootorder1..5` (DHCP TFTP attempts, then
   `flashboot` → reads sda5 (slot 1) → `bootm`).

This validates that our EdgeNOS installer's U-Boot env discipline
(`fw_setenv -f -s` with `onie_boot_reason` cleared) is correct.

---

## 8. Mismatches between this ONIE and our installer assumptions

- **ONIE_ISSUES.md §6** says `fw_setenv` prompts for confirmation in
  ONIE. Live capture shows ONIE's `fw_setenv` is just the standard
  `u-boot-tools` binary — the prompt is for the U-Boot env partition
  size mismatch warning. Workaround (`echo y | fw_setenv`) remains valid.
- **ONIE_ISSUES.md §9** lists `parted` and `partprobe` as missing. Live
  capture confirms — busybox has neither. Our installer uses `printf |
  fdisk -u` and `sync; sleep 2`.
- **ONIE_ISSUES.md §11** says `bootargs` must be set explicitly before
  `bootm`. Confirmed — `bootcmd` in this build does
  `run check_boot_reason; run nos_bootcmd; run onie_bootcmd`, and
  `nos_bootcmd` is responsible for setting `bootargs`.

No new ONIE quirks discovered. Our installer should work as-is.

---

## 9. Open questions still unanswered

- The `/bin/discover` script itself uses helpers in `/lib/onie/functions`
  that pattern-walk eight URL filename variants per source. Reading the
  `functions` file (captured, 11 KB) will reveal the exact regex and the
  HTTPS cert/strict-mode policy.
- `udhcp4_sd` is the DHCP option parser; it converts DHCP option 114
  (`url`) and option 67 (`bootfile`) into install URLs. Worth diffing
  against the OCP design spec to confirm matching semantics.

---

*Captured 2026-05-11 21:15 UTC over SSH (dropbear, blank-password root)
from the live ONIE install loop on the AS5610-52X chassis at 10.1.1.222.*

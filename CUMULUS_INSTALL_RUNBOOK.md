# Runbook: Install Cumulus 2.5.0 over EdgeNOS on AS5610-52X (via ONIE)

**Last verified working: 2026-06-07.** This is the *exact* sequence that works on
this box. Read [§Why](#why-onie-nos-install-fails) first — it explains why the
"normal" `onie-nos-install` fails here and why these manual steps are required.

> TL;DR: ONIE's BusyBox on this box does **not** symlink `fdisk`/`mkfs.ext2` into
> PATH, so the Cumulus installer's partition step dies with "Partitioning failed
> / Unable to install image". Fix = partition + format the disk yourself with
> `busybox fdisk`/`busybox mke2fs`, then run the installer with
> `skip_disk_format=y` so it skips its own (broken) partition step and just
> writes the image + U-Boot env. Do **not** create `fdisk`/`mkfs` symlinks — that
> caused a downstream "Unable to determine platform" failure in the past
> (`feedback_onie_install_no_workarounds`).

---

## 0. Prerequisites

- Box sitting in **ONIE install mode**, reachable on the mgmt net. (From EdgeNOS:
  `onie-nos-mode -i` or reboot into ONIE → "ONIE: Install OS".)
- Cumulus image on the build host: `/home/smiley/edgecore/CumulusLinux-2.5.0-powerpc.bin`
  (md5 `b19fb27b4eea786d109dc4f40a5809b2`).
- Build host = `10.1.1.30`. ONIE box IP this run = `10.1.1.222` (it DHCPs; sweep
  `10.1.1.0/24` if different — ONIE SSH = dropbear, banner offers
  `kexguess2@matt.ucc.asn.au`).

### ONIE SSH (root, NO password, legacy crypto)
```bash
SSHO="-o KexAlgorithms=+diffie-hellman-group14-sha1,diffie-hellman-group1-sha1 \
 -o HostKeyAlgorithms=+ssh-rsa -o PubkeyAuthentication=no \
 -o PreferredAuthentications=password,keyboard-interactive \
 -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o ConnectTimeout=8"
ONIE=root@10.1.1.222
```

---

## 1. Confirm the box & mode
```bash
ssh $SSHO $ONIE "onie-sysinfo; . /lib/onie/functions; import_cmdline; echo boot_reason=\$onie_boot_reason"
# expect: powerpc-accton_as5610_52x-r0 ... boot_reason=install
```

## 2. Copy the image to the box
`scp` does NOT work (ONIE dropbear has no sftp subsystem). Stream over a plain
SSH channel instead:
```bash
cat /home/smiley/edgecore/CumulusLinux-2.5.0-powerpc.bin | \
  ssh $SSHO $ONIE "cat > /tmp/cl250.bin"
ssh $SSHO $ONIE "md5sum /tmp/cl250.bin"   # must be b19fb27b4eea786d109dc4f40a5809b2
```

## 3. Wipe any stale partition table, then REBOOT
If the disk has a leftover (EdgeNOS) table, the kernel caches it and partitioning
fails. There is **no** `partprobe`/`fdisk` symlink to re-read it live, so the
clean way is: zero the table, reboot, let the kernel re-read.
```bash
ssh $SSHO $ONIE "dd if=/dev/zero of=/dev/sda bs=1M count=2;        # MBR + primary GPT
                 dd if=/dev/zero of=/dev/sda bs=1M count=2 seek=3822; sync"  # backup GPT (disk≈3823 MiB)
ssh $SSHO $ONIE "(sleep 1; /sbin/reboot) &"     # 'reboot' isn't in PATH; use /sbin/reboot
# wait ~90s for ONIE to come back, then re-do step 2 (tmpfs /tmp is wiped on reboot)
```
After reboot, `cat /proc/partitions | grep sda` should show ONLY `sda` (no sda1..n).

## 4. Partition the disk manually (busybox fdisk + the platform layout)
The Cumulus image ships the exact layout in
`control.tar.xz → cumulus/init/accton_as5610_52x/platform.fdisk`. It is (feed
verbatim, blank lines = "accept default" and are REQUIRED):
```
o
n
p
1
8192
270273
n
e
2
270274
860097
n
p
3
860160

n
l
270336
303041
n
l
303104
565185
n
l
565248
597953
n
l
598016

w
```
Put that in `/tmp/platform.fdisk` on the box, then:
```bash
# (stream the layout above into /tmp/platform.fdisk first)
ssh $SSHO $ONIE "busybox fdisk -u /dev/sda < /tmp/platform.fdisk; cat /proc/partitions | grep sda"
```
Expect: `sda1`(persist ~128M) `sda2`(extended) `sda3`(rw-overlay, rest)
`sda5`/`sda6`(slot1 kernel/root) `sda7`/`sda8`(slot2 kernel/root).

## 5. Format persist + rw-overlay (ext2) — what format_disk would do
```bash
ssh $SSHO $ONIE "busybox mkfs.ext2 -F /dev/sda1;   # persist
                 busybox mkfs.ext2 -F /dev/sda3;   # rw-overlay
                 busybox blkid /dev/sda1 /dev/sda3"
```
(Kernel sda5/7 and rootfs sda6/8 are RAW `dd` targets — do NOT format them.)

## 6. Run the installer with skip_disk_format=y
Run the `.bin` directly (NOT `onie-nos-install` — it hides the real error on the
serial console and can't be told `skip_disk_format`). The env vars matter:
```bash
ssh $SSHO $ONIE '
  export HOME=/tmp
  . /lib/onie/functions ; import_cmdline
  export onie_exec_url="file:///tmp/cl250.bin"   # makes the installer pick cmd=provision
  export onie_boot_reason=install
  export skip_disk_format=y                        # <-- skips the broken fdisk/mkfs step
  export PATH=/usr/sbin:/usr/bin:/sbin:/bin:$PATH  # so fw_setenv (/usr/sbin) is found
  chmod +x /tmp/cl250.bin
  /tmp/cl250.bin
'
```
Success looks like:
```
Copying sysroot into /dev/sda6... done.  Verifying sysroot copy... OK.
Copying kernel uImage into /dev/sda5... done.
... (slot 2 -> sda8/sda7) ...
Updating u-boot environment variables... done.
Success: System provisioning complete.  Rebooting...
```
The installer sets U-Boot `bootsource=flashboot`, `cl.active=1` and reboots.

## 7. Boot Cumulus
The installer reboots itself. If it doesn't: `ssh $SSHO $ONIE "/sbin/reboot"`.
Cumulus 2.5.0 boots in ~2-3 min and DHCPs the mgmt port. Sweep `10.1.1.0/24`.
Cumulus uses real OpenSSH (still old — keep the legacy `KexAlgorithms`/`ssh-rsa`
options). Default login: `root` / `CumulusLinux!`.

## 8. License (Cumulus refuses to bring up `swp` ports without it)
See `reference_cumulus_license_install`: license at `/home/smiley/license.txt`
(expires 2013-11-27 → set switch clock to 2013-10-01 first). Fast path:
```bash
date -s 2013-10-01          # on the switch, BEFORE licensing
cp /path/license.txt /etc/cumulus/.license.txt   # skips the cl-license EULA paginator
```
Then `ifup swp1 swp49 ...` / restart switchd.

---

## Why `onie-nos-install` fails  {#why-onie-nos-install-fails}

1. `onie-nos-install file:///tmp/cl250.bin` → `/bin/exec_installer` → `run_installer`
   (`/bin/exec_installer:102`) runs the Cumulus `.bin`, tee-ing its output to
   `realpath(/proc/$$/fd/1)`. BusyBox `realpath` of an SSH pipe fails → output
   falls back to **/dev/console (serial)**, so over SSH you only ever see the
   generic `Failure: Unable to install image`. The real error is on the serial
   console or in `/var/log/onie.log` (`logger -t os-install`).
2. The real error: `Partitioning /dev/sda...Failure: Partitioning failed.`
   The installer's `format_disk` (`scripts/arch-installer-functions`) calls **bare
   `fdisk`** then **bare `mkfs.ext2`**. On this ONIE, BusyBox HAS those applets
   but they are **not symlinked into PATH** (`which fdisk` → empty; only `dd`,
   `tar`, and `fw_setenv` are linked). So bare `fdisk` is "not found" → fail.
3. We do NOT fix this by symlinking `fdisk`/`mkfs` (BusyBox `fdisk` behaves subtly
   differently and previously caused a downstream "Unable to determine platform
   from /proc/device-tree" on retry — `feedback_onie_install_no_workarounds`).
   Instead we run the *same* tools manually with `busybox <applet>` to build the
   exact documented layout, then `skip_disk_format=y` so the installer never
   touches `fdisk`/`mkfs` and just does the `dd`/`fw_setenv` steps (those tools
   ARE available).

### Tool availability on this ONIE (BusyBox v1.25.1)
| Tool | In PATH? | BusyBox applet? | Notes |
|------|----------|-----------------|-------|
| `dd`, `tar` | yes | yes | image copy works |
| `fw_setenv` | yes (`/usr/sbin`→busybox) | yes | U-Boot env works (needs `/usr/sbin` in PATH) |
| `fdisk` | **NO** | yes | call as `busybox fdisk` |
| `mkfs.ext2`/`mke2fs` | **NO** | yes | call as `busybox mkfs.ext2` |
| `sgdisk`/`parted`/`partprobe` | NO | no | not needed (layout is MBR/DOS) |

## Reflash back to EdgeNOS later
Same idea in reverse: boot ONIE (`onie-nos-mode -i` from Cumulus, or U-Boot), then
`onie-nos-install <EdgeNOS .bin>`. EdgeNOS install path: see
`feedback_onie_install_no_workarounds` / project notes. The box IP moves on each
reflash — sweep `10.1.1.0/24` (Dropbear banner = ONIE or EdgeNOS;
`project_switch_ip_reflash`).

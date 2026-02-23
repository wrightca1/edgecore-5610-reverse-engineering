# ONIE Boot Flow, A/B Partitions, and Custom NOS Requirements

**Date**: February 15, 2026  
**Platform**: Accton AS5610-52X (Edgecore AS5610-52X)  
**Source**: Cumulus installer (install.sh, platform.conf, platform.fdisk), ONIE, U-Boot env

---

## Summary

| Component | Description |
|-----------|-------------|
| **ONIE** | Open Network Install Environment – bootloader extension, runs in install/rescue mode |
| **onie-nos-install** | Downloads installer URL, execs it with `onie_exec_url` set |
| **Cumulus installer** | Shell script + `control.tar.xz` + `data.tar`; `provision` = full install |
| **A/B slots** | Slot 1 (primary) and Slot 2 (alternate); kernel + squashfs rootfs each |
| **U-Boot** | `cl.active` selects slot; `flashboot` / `flashboot_alt` boot primary/alternate |

---

## 1. Boot Flow (High Level)

```
U-Boot (PowerPC)
    ↓
ONIE (install / rescue / uninstall / normal)
    ↓ (if NOS installed, normal mode)
Cumulus Linux kernel (uImage from slot 1 or 2)
    ↓
Initramfs → mount squashfs + overlay → switch to root
    ↓
Systemd → switchd, etc.
```

---

## 2. ONIE Invocation

### 2.1 User Command

```bash
onie-nos-install http://server/CumulusLinux-2.5.1-powerpc.bin
# or
onie-nos-install /mnt/usb/CumulusLinux-2.5.1-powerpc.bin
```

### 2.2 ONIE Script Behavior

1. Checks `onie_boot_reason` is `install` or `rescue`.
2. Writes `onie_cli_static_url` and `onie_cli_static_parms` to `/tmp/.install_url_parms`.
3. Calls `exec_installer` (downloads URL, `exec`’s the script).

### 2.3 Installer Execution

- Installer is a **self-extracting shell script**.
- ONIE sets `onie_exec_url` in the environment.
- Cumulus `install.sh`:
  - If no args and `onie_exec_url` set → `cmd=provision`.
  - `provision` = full install (partition, format, install both slots, U-Boot env, reboot).

---

## 3. Cumulus Installer Format

### 3.1 Layout

```
#!/bin/sh
# ... script header ...
exit 0
__ARCHIVE__    ← binary boundary; payload follows
```

Payload (after `__ARCHIVE__`):

- **control.tar.xz** – metadata
- **control.tar.xz.sha1**
- **data.tar** – rootfs + kernel

### 3.2 control.tar.xz Contents

- **control** – text metadata, e.g.:
  - `Architecture: powerpc`
  - `Platforms: accton_as5610_52x ...`
  - `OS-Release: 2.5.1`
  - `Installer-Version: 1.2`
- **cumulus/init/** – platform configs (platform.conf, platform.fdisk)
- **scripts/** – installer-functions, arch-installer-functions, etc.
- **uboot_env/** – U-Boot env fragments

### 3.3 data.tar Contents

- **uImage-powerpc.itb** – kernel + initramfs FIT image
- **uImage-powerpc.itb.sha1**
- **sysroot.squash.xz** – SquashFS rootfs
- **sysroot.squash.xz.sha1**
- **uboot_env.tar.xz** – U-Boot env script

---

## 4. A/B Partition Layout (AS5610-52X)

### 4.1 Storage

- **Internal USB flash** at `/sys/bus/usb/devices/1-1.3:1.0`
- Block device: `sda` (or `sdb` etc., depending on host number)

### 4.2 platform.conf (accton_as5610_52x)

| Variable | Value | Partition | Purpose |
|----------|-------|-----------|---------|
| **persist_part** | ${blk_dev}1 | /dev/sda1 | Persistent config (ext2) |
| **rw_rootpart** | ${blk_dev}3 | /dev/sda3 | Read-write overlay (ext2) |
| **kernel_part1** | ${blk_dev}5 | /dev/sda5 | Kernel slot 1 (raw uImage) |
| **ro_part1** | ${blk_dev}6 | /dev/sda6 | Root FS slot 1 (squashfs) |
| **kernel_part2** | ${blk_dev}7 | /dev/sda7 | Kernel slot 2 (raw uImage) |
| **ro_part2** | ${blk_dev}8 | /dev/sda8 | Root FS slot 2 (squashfs) |

### 4.3 platform.fdisk (fdisk Script)

MBR layout:

```
Primary 1:   sectors 8192–270273    → sda1 (persist)
Extended 2:  sectors 270274–860097  → sda2 (container)
  Logical:   270336–303041          → sda5 (kernel slot 1)
  Logical:   303104–565185          → sda6 (ro slot 1)
  Logical:   565248–597953          → sda7 (kernel slot 2)
  Logical:   598016–end             → sda8 (ro slot 2)
Primary 3:   sectors 860160–end     → sda3 (rw overlay)
```

### 4.4 Slot Mapping

| Slot | Kernel | Root FS |
|------|--------|---------|
| **1 (A)** | /dev/sda5 | /dev/sda6 (squashfs) |
| **2 (B)** | /dev/sda7 | /dev/sda8 (squashfs) |

---

## 5. Provision Flow (image_provision_handler)

1. **Detect platform** – `onie-sysinfo -p` or `/proc/device-tree/model` → `accton_as5610_52x`
2. **Load platform.conf** – partition names, device paths
3. **format_disk** – `fdisk -u /dev/$blk_dev < platform.fdisk`, then `mkfs` on persist, rw_root
4. **image_install_handler 1 2** – install to both slots:
   - `install_sysroot_blk 1` – `tar -xOf data.tar sysroot.squash.xz \| dd of=/dev/sda6`
   - `install_kernel uImage-powerpc.itb 1` – `dd if=... of=/dev/sda5`
   - Same for slot 2
5. **image_env_handler** – write U-Boot env from uboot_env/*.inc
6. **arch_post_provision** – set `bootsource=flashboot`, `cl.active=1`
7. **save_info** – persist installer copy to rw partition
8. **reboot**

---

## 6. U-Boot Boot Flow

### 6.1 Key Variables

| Variable | Purpose |
|----------|---------|
| **cl.active** | 1 = slot 1, 2 = slot 2 |
| **bootsource** | `flashboot` = boot from flash |
| **lbootargs** | Extra kernel cmdline (e.g. ONIE install) |
| **onie_boot_reason** | install / rescue / uninstall / normal |

### 6.2 Boot Sequence (common_env.inc)

```
nos_bootcmd → bootorder1 (or lbootcmd if bootsource set)
bootorder1 → tftp ${ethaddr}.img, try boot
bootorder2 → DHCP bootfile
bootorder3 → ${cl.platform}.img
bootorder4 → flashboot (primary)
bootorder5 → flashboot_alt (alternate)
flashboot   → run initargs boot_active (boot from active slot)
flashboot_alt → run initargs boot_alt (swap active, boot)
```

### 6.3 Platform-Specific (as5610_52x.platform.inc)

```
cl.platform  accton_as5610_52x
```

U-Boot loads kernel from USB flash based on `cl.active` and slot layout (MTD or block); AS5610 uses block (sda5/sda6, sda7/sda8).

---

## 7. What You Need for Your Own NOS

### 7.1 Minimum Installer Layout

1. **Self-extracting script** – `#!/bin/sh` header, extract/run logic, `exit 0`, `__ARCHIVE__`, payload
2. **control.tar.xz** – `control` + platform configs + scripts
3. **data.tar** – `uImage-*.itb`, `sysroot.squash.xz` (or your rootfs format), `uboot_env.tar.xz`

### 7.2 Required Platform Files (AS5610)

- **platform.conf** – partition layout, USB path, blk_dev detection
- **platform.fdisk** – fdisk script for MBR
- **uboot_env/as5610_52x.platform.inc** – `cl.platform accton_as5610_52x`
- **uboot_env/common_env.inc** – nos_bootcmd, flashboot, flashboot_alt
- **uboot_env/clear_env.inc** – env wipe if needed

### 7.3 Installer Script Flow

- Reuse or adapt Cumulus `install.sh`:
  - Parse control, load platform, call `format_disk`, `image_install_handler`, `image_env_handler`, `arch_post_provision`
- Or implement a minimal variant that:
  - Partitions via `platform.fdisk`
  - Copies kernel to sda5/sda7, rootfs to sda6/sda8
  - Sets U-Boot env (`fw_setenv`) for `cl.active`, `bootsource`, etc.
  - Reboots

### 7.4 Kernel / Root FS

- **Kernel**: PowerPC uImage or FIT (`uImage-*.itb`) compatible with U-Boot `bootm`
- **Root FS**: SquashFS for ro slots; kernel cmdline must specify `root=/dev/sda6` or `root=/dev/sda8` (or by UUID/label)
- **Overlay**: `/dev/sda3` for rw overlay, `/dev/sda1` for persist (e.g. `/mnt/persist`)

### 7.5 ONIE Compatibility

- Installer must run when exec’d by ONIE (busybox, limited tools)
- Use `onie-sysinfo -p` to get platform string
- Map platform to your platform.conf / platform.fdisk (e.g. `powerpc-accton-as5610-52x-r0` → `accton_as5610_52x`)

### 7.6 File Locations (Cumulus Extracted)

| File | Path |
|------|------|
| install.sh | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/install.sh` |
| platform.conf | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/cumulus/init/accton_as5610_52x/platform.conf` |
| platform.fdisk | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/cumulus/init/accton_as5610_52x/platform.fdisk` |
| powerpc-installer-functions | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/arch/powerpc-installer-functions` |
| as5610_52x_install.sh | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/scripts/platform/as5610_52x_install.sh` |
| uboot_env | `cumulus/extracted/sysroot/usr/share/cumulus/.installer/uboot_env/` |

---

## 8. References

- ONIE: https://github.com/opencomputeproject/onie
- ONIE NOS interface: https://opencomputeproject.github.io/onie/design-spec/nos_interface.html
- VERSION_COMPARISON.md – AS5610 storage layout
- scripts/extract-cumulus-bin.sh – Cumulus extraction
- scripts/create-onie-installer.sh – ONIE installer assembly

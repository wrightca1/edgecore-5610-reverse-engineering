# ONIE and Installer Formats — Deep Dive

**Date**: 2026-02-26  
**Platform**: Edgecore/Accton AS5610-52X (internal USB flash, PowerPC U-Boot)  
**Sources**: Cumulus installer (extracted), open-nos-as5610 onie-installer, [ONIE design spec](https://opencomputeproject.github.io/onie/design-spec/nos_interface.html), [U-Boot NOS interface](https://opencomputeproject.github.io/onie/design-spec/uboot_nos_interface.html)

This document expands [ONIE_BOOT_AND_PARTITION_LAYOUT.md](ONIE_BOOT_AND_PARTITION_LAYOUT.md) with exact formats, sector math, and ONIE contract details.

---

## 1. ONIE NOS interface (what ONIE requires)

### 1.1 Contract

From the [ONIE NOS interface](https://opencomputeproject.github.io/onie/design-spec/nos_interface.html) and [U-Boot NOS interface](https://opencomputeproject.github.io/onie/design-spec/uboot_nos_interface.html):

| Requirement | Description |
|-------------|-------------|
| **Boot after install** | Installer must update U-Boot so the **NOS** boots on next reboot (not ONIE). On U-Boot platforms this means setting **`nos_bootcmd`** (or platform-equivalent) so U-Boot runs the NOS boot sequence. |
| **onie-nos-mode** | On success, installer should call **`onie-nos-mode -s`** so ONIE is “user friendly” on later boots. |
| **Installer flexibility** | Otherwise the installer can do anything: partition disk, write kernel/rootfs, use HTTP, kexec, etc. |

### 1.2 How ONIE runs the installer

- User (or discovery) runs: **`onie-nos-install <URL>`** (e.g. `onie-nos-install http://server/image.bin` or `onie-nos-install /mnt/usb/image.bin`).
- ONIE downloads the URL (or uses local path), then **exec()’s the downloaded file** as a shell script.
- ONIE sets **`onie_exec_url`** in the environment so the script knows it was invoked by ONIE.
- Installer runs in ONIE’s BusyBox environment (limited tools; no systemd, no full Debian).

### 1.3 U-Boot environment (PowerPC / AS5610)

- **`onie_boot_reason`**: `install` | `rescue` | `uninstall` | `update` | `normal`. Set by NOS or user to tell ONIE what to do next boot.
- **`nos_bootcmd`**: U-Boot command(s) to boot the NOS. **The installer must set this** (or the platform-specific equivalent) so that after reboot U-Boot runs the NOS instead of ONIE.
- **`onie_debugargs`**: Optional extra kernel args for ONIE; e.g. `install_url=http://10.0.1.249/nos_installer.bin` for auto-install.
- **Platform-specific**: On AS5610/Cumulus, **`bootsource=flashboot`**, **`cl.active=1`** (or 2), **`cl.platform=accton_as5610_52x`** are used so U-Boot’s `nos_bootcmd` (or `lbootcmd`) runs `flashboot` and loads kernel from the correct slot.

### 1.4 System info

- **`onie-sysinfo -p`**: Prints platform string (e.g. `accton_as5610_52x`, `edgecore_as5610_52x`). Installer uses this to select platform.conf / platform.fdisk.
- **`/etc/onielabel`**: Alternative source for platform on some ONIE builds.

---

## 2. Cumulus installer format (exact)

### 2.1 File layout

```
┌─────────────────────────────────────────────────────────────┐
│  #!/bin/sh                                                   │
│  ... install script (sources control, runs fdisk, dd,        │
│       image_install_handler, image_env_handler, reboot)      │
│  exit 0                                                      │
│  __ARCHIVE__        ← boundary: script ends here            │
├─────────────────────────────────────────────────────────────┤
│  control.tar.xz     (XZ-compressed tarball)                 │
│  control.tar.xz.sha1                                        │
│  data.tar            (uncompressed)                         │
└─────────────────────────────────────────────────────────────┘
```

- The **.bin** file is a single blob: **executable shell script** up to and including the line **`__ARCHIVE__`**, then **binary payload**.
- Cumulus payload = **control.tar.xz** + **control.tar.xz.sha1** + **data.tar**. The script locates `__ARCHIVE__`, then extracts or seeks past the script, then parses control and data (Cumulus uses `tar -xOf data.tar ...` for streaming).

### 2.2 control.tar.xz contents (Cumulus)

| Path | Purpose |
|------|---------|
| **control** | Debian-style metadata: `Architecture: powerpc`, `Platforms: accton_as5610_52x ...`, `OS-Release: 2.5.1`, `Installer-Version: 1.2` |
| **cumulus/init/** | Platform configs: **platform.conf**, **platform.fdisk** per platform |
| **scripts/** | installer-functions, arch-installer-functions, platform-specific (e.g. as5610_52x_install.sh) |
| **uboot_env/** | U-Boot env fragments (e.g. common_env.inc, as5610_52x.platform.inc) |

### 2.3 data.tar contents (Cumulus)

| Member | Purpose |
|--------|---------|
| **uImage-powerpc.itb** | FIT image: kernel (uImage) + initramfs + DTB |
| **uImage-powerpc.itb.sha1** | Checksum |
| **sysroot.squash.xz** | SquashFS root filesystem (XZ-compressed) |
| **sysroot.squash.xz.sha1** | Checksum |
| **uboot_env.tar.xz** | U-Boot env script tarball |

### 2.4 Cumulus provision flow (summary)

1. **Detect platform**: `onie-sysinfo -p` or device tree → e.g. `accton_as5610_52x`.
2. **Load platform.conf**: partition variables (`persist_part`, `kernel_part1`, `ro_part1`, …), USB syspath, `blk_dev` detection.
3. **format_disk**: `fdisk -u /dev/$blk_dev < platform.fdisk`, then `mkfs` on persist and rw_root.
4. **image_install_handler 1 2**: For each slot, extract from data.tar and write:  
   `tar -xOf data.tar sysroot.squash.xz | dd of=/dev/sda6`; kernel: `dd if=...itb of=/dev/sda5`.
5. **image_env_handler**: Write U-Boot env from uboot_env/*.inc (e.g. `fw_setenv` for each line).
6. **arch_post_provision**: Set `bootsource=flashboot`, `cl.active=1`.
7. **save_info** (optional): Persist installer copy to rw partition.
8. **reboot**.

---

## 3. AS5610 partition layout (exact sectors and sizes)

### 3.1 MBR layout (sector 0 = 512 bytes)

| Partition | Type | Start (sector) | End (sector) | Sectors | Size (approx) | Purpose |
|-----------|------|----------------|--------------|---------|---------------|---------|
| **sda1** | Primary | 8192 | 270273 | 262082 | ~128 MiB | **persist** — ext2 (config, licenses) |
| **sda2** | Extended | 270274 | 895839 | 625566 | ~305 MiB | Container for logicals |
| **sda5** | Logical | 270336 | 303041 | 32768 | 16 MiB | **Kernel** — raw FIT (uImage .itb) |
| **sda6** | Logical | 303104 | 895839 | 592736 | ~289 MiB | **Root FS** — squashfs |
| **sda3** | Primary | 895840 | end | rest | ~remaining | **rw-overlay** — ext2 (overlay upper/work) |

**Single-slot layout**: Only 2 logicals (sda5, sda6) so ONIE’s kernel always exposes both. Cumulus uses 4 logicals (sda5..sda8) but their installer runs in a full Linux initramfs; ONIE’s BusyBox on this device only exposes 3 logicals, so we use 2.

- **Total logical in extended**: 32768 + 592736 = 625504 (fits in 625566).

### 3.2 Block device detection (Cumulus platform.conf)

- **USB path**: `/sys/bus/usb/devices/1-1.3:1.0` (port 3 of root hub).
- **Detection**: Wait for `hostN` under that syspath; then `blk_dev=sdX` (e.g. `sda`) from the SCSI host number. Timeout ~100 s (slumber × 0.1 s).
- **open-nos**: Uses fixed `sda` or tries `sda`/`sdb` if `/dev/sda` not present.

### 3.3 Slot mapping (single-slot)

| Slot | Kernel partition | Root partition |
|------|------------------|----------------|
| **1** | /dev/sda5 | /dev/sda6 |

Kernel cmdline **`root=/dev/sda6`**. Initramfs mounts squashfs from that root and overlay from **/dev/sda3**, then `switch_root`.

---

## 4. open-nos-as5610 installer format (variant)

### 4.1 Differences from Cumulus

| Aspect | Cumulus | open-nos-as5610 |
|--------|---------|------------------|
| Payload after **__ARCHIVE__** | control.tar.xz + control.tar.xz.sha1 + data.tar | **data.tar only** (no separate control.tar.xz) |
| control metadata | Inside control.tar.xz | Inside data.tar as file **control** |
| Platform files | control.tar.xz → cumulus/init/... | data.tar → cumulus/init/accton_as5610_52x/platform.conf, platform.fdisk |
| Kernel/rootfs | data.tar → uImage-powerpc.itb, sysroot.squash.xz | data.tar → nos-powerpc.itb (or uImage-powerpc.itb), sysroot.squash.xz |
| U-Boot env | uboot_env.tar.xz + image_env_handler | Install script calls **fw_setenv** directly (bootsource, cl.active, cl.platform) |

### 4.2 open-nos .bin layout

```
┌─────────────────────────────────────────────────────────────┐
│  #!/bin/sh                                                   │
│  ... install.sh (find __ARCHIVE__, dd payload to /tmp,      │
│       tar -xf payload → control + cumulus/ + uboot_env/     │
│       + nos-powerpc.itb + sysroot.squash.xz; partition,     │
│       dd kernel/rootfs to sda5/6/7/8, fw_setenv, reboot)     │
│  exit 0                                                      │
│  __ARCHIVE__                                                 │
├─────────────────────────────────────────────────────────────┤
│  data.tar (uncompressed)                                     │
│    control                                                   │
│    cumulus/init/accton_as5610_52x/platform.conf              │
│    cumulus/init/accton_as5610_52x/platform.fdisk              │
│    uboot_env/*.inc                                           │
│    nos-powerpc.itb  (and/or uImage-powerpc.itb)              │
│    sysroot.squash.xz                                         │
└─────────────────────────────────────────────────────────────┘
```

- **build.sh** (open-nos): Builds **data.tar** with control, platform files, uboot_env, FIT, squashfs; then **`cat install.sh data.tar > open-nos-as5610-YYYYMMDD.bin`**. No control.tar.xz.
- **install.sh** (open-nos): Finds line number of `__ARCHIVE__`, computes byte offset, `dd`’s remainder of script to `/tmp/_nos_payload.bin`, then **`tar -xf /tmp/_nos_payload.bin`** into INSTALLER_DIR, sources platform.conf, runs fdisk, dd’s kernel/rootfs to both slots, runs fw_setenv, reboot.

### 4.3 control file (open-nos)

```
Architecture: powerpc
Platforms: accton_as5610_52x edgecore_as5610_52x
OS-Release: open-nos-as5610
Installer-Version: 1.0
```

### 4.4 U-Boot env (open-nos)

- **common_env.inc**: `bootsource flashboot`, `cl.active 1`
- **as5610_52x.platform.inc**: `cl.platform accton_as5610_52x`
- Install script sets these via **fw_setenv** (if available) so U-Boot boots from flash slot 1.

---

## 5. U-Boot boot flow (AS5610)

- **nos_bootcmd** (or platform default): Typically runs a **bootorder** that includes **flashboot** (primary) and **flashboot_alt** (alternate).
- **flashboot**: Runs **initargs** then **boot_active** — loads kernel from **sda5**, root **sda6**.
- **flashboot_alt**: Swaps active slot and boots (e.g. for A/B upgrade).
- **bootsource=flashboot**: Tells U-Boot to use flash boot path instead of ONIE/discovery.

---

## 6. ONIE boot reasons and reinstall

| onie_boot_reason | Effect on next boot |
|------------------|---------------------|
| **install** | ONIE enters discovery/install (e.g. run onie-nos-install) |
| **rescue** | ONIE rescue mode (no discovery; console/telnet, wget, etc.) |
| **uninstall** | ONIE wipes mass storage (except ONIE); back to discovery |
| **update** | ONIE self-update (U-Boot platforms: update only, non-destructive to NOS) |
| **normal** | Boot NOS (run nos_bootcmd / flashboot path) |

To **reinstall or install a different NOS** from the running NOS: set **`onie_boot_reason=install`** and reboot; then use **onie-nos-install** with the new image URL.

---

## 7. References

- [ONIE_BOOT_AND_PARTITION_LAYOUT.md](ONIE_BOOT_AND_PARTITION_LAYOUT.md) — Boot flow, provision summary, file locations
- [ONIE NOS interface](https://opencomputeproject.github.io/onie/design-spec/nos_interface.html)
- [U-Boot NOS interface](https://opencomputeproject.github.io/onie/design-spec/uboot_nos_interface.html)
- open-nos-as5610: `onie-installer/install.sh`, `onie-installer/build.sh`, `onie-installer/cumulus/init/accton_as5610_52x/platform.conf`, `platform.fdisk`, `docs/EDGECORE_AS5610_ONIE_PARTITIONS.md`
- Cumulus extracted: `cumulus/extracted/sysroot/usr/share/cumulus/.installer/` (install.sh, cumulus/init/accton_as5610_52x/, uboot_env/)

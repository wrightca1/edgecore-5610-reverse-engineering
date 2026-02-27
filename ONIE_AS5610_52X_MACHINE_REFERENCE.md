# ONIE machine/accton/accton_as5610_52x — Reference

This document summarizes the **official ONIE machine support** for the Accton AS5610-52X (Edgecore AS5610-52X). Source: [opencomputeproject/onie](https://github.com/opencomputeproject/onie), path **`machine/accton/accton_as5610_52x`**.

## Path in ONIE repo

- **Tree**: https://github.com/opencomputeproject/onie/tree/master/machine/accton/accton_as5610_52x  
- **Platform ID**: `accton_as5610_52x` (matches `onie-sysinfo -p` and our FIT config / U-Boot `cl.platform`).

## Directory layout (from ONIE master)

| Path | Purpose |
|------|--------|
| **INSTALL** | How to cross-compile and flash ONIE (TFTP, NOR layout). |
| **machine.make** | Make variables: `ONIE_ARCH=powerpc-softfloat`, `SWITCH_ASIC_VENDOR=bcm`, `UBOOT_MACHINE=AS5610_52X`, `KERNEL_DTB=as5610_52x.dtb`, kernel 3.2.69, GCC 4.9.2. |
| **onie-rom.conf** | NOR layout: u-boot 512KB, board info 64KB, u-boot env 64KB, onie-uimage remainder; `format=ubootenv_onie`, `onie_uimage_size=0x00360000`. |
| **installer/install-platform** | Platform check: `onie_build_machine` vs `image_build_machine` (allows `accton_$onie` = `image`), `onie_machine_rev`, `onie_arch`. |
| **demo/platform.conf** | Block device via USB bus `1-1.3` → `sdX`; `install_uimage`: `dd if=demo-${platform}.itb of=/dev/$blk_dev bs=4M`; `hw_load`: `usb start && usbiddev && usbboot $loadaddr ${usbdev}:0`. |
| **kernel/** | `config` (CONFIG_AS5610_52X=y), `series`, `platform-accton-as5610_52x.patch`. |
| **u-boot/** | `series`, `driver-swizzle-flash-sectors-error.patch`, `platform-accton-as5610_52x.patch`. |
| **rootconf/sysroot-lib-onie/uninstall-platform** | Uninstall: find mass storage on bus `1-1.3:1.0` (sdX), then `erase_mass_storage`. |
| **busybox/conf/** | Busybox config for ONIE rootfs. |

## Build (from ONIE INSTALL)

```bash
cd build-config
make -j4 MACHINEROOT=../machine/accton MACHINE=accton_as5610_52x all
```

Output in `build/images`:

- `onie-accton_as5610_52x-r0.bin` — ONIE kernel + empty U-Boot env (to NOR)
- `onie-accton_as5610_52x-r0.bin.uboot` — U-Boot binary (to NOR)

## NOR flash layout (onie-rom.conf + INSTALL)

- **Image 1** (ONIE kernel + env): `q1start=0xefc00000`, `q1sz.b=0x360000`
- **Image 2** (U-Boot): `q2start=0xeff80000`, `q2sz.b=0x00080000`

## Relevance to open-nos-as5610

1. **Platform ID**  
   Our installer and FIT use `accton_as5610_52x` (and alias `edgecore_as5610_52x`). This matches ONIE’s `MACHINE` and the NOS boot flow (`bootm ${loadaddr}#${cl.platform}`).

2. **Block device**  
   ONIE demo uses USB mass storage at `1-1.3` → `/dev/sda` (or sdb). Our installer uses `sda` (or first available); same hardware.

3. **Kernel DTB**  
   ONIE uses `KERNEL_DTB = as5610_52x.dtb`; we use `as5610_52x.dtb` in the FIT (and `accton_as5610_52x_dtb` image name to match Cumulus).

4. **U-Boot**  
   ONIE’s U-Boot is patched per `u-boot/platform-accton-as5610_52x.patch`; our NOS installer only sets env (e.g. `fw_setenv bootsource flashboot`, `cl.active`, `cl.platform`) and does not reflash U-Boot.

5. **Install flow**  
   Our `install.sh` writes kernel FIT + rootfs to partitions (e.g. sda5/sda6) and sets env; ONIE’s `install-platform` only validates machine/arch/rev. Our partition layout is documented in `ONIE_BOOT_AND_PARTITION_LAYOUT.md` and `ONIE_AND_INSTALLER_FORMATS_DEEP_DIVE.md`.

## How to make the installer image

### ONIE image (ONIE itself, for NOR)

From the ONIE repo, to build the ONIE kernel + env and U-Boot for this machine:

```bash
cd build-config
make -j4 MACHINEROOT=../machine/accton MACHINE=accton_as5610_52x all
```

Output in `build/images`: `onie-accton_as5610_52x-r0.bin` (ONIE kernel + env), `onie-accton_as5610_52x-r0.bin.uboot` (U-Boot). Flash per INSTALL (NOR layout in **NOR flash layout** above). This does **not** produce a NOS installer; it produces the ONIE runtime that runs on the switch.

### NOS installer image (open-nos-as5610)

Our installer is a **shell script + tar** payload (like Cumulus): script until `exit_marker`, then a tar containing `installer/install.sh`, `installer/control.tar.xz`, and `installer/data.tar`. The data tar contains:

- **uImage-powerpc.itb** (or `nos-powerpc.itb`) — FIT with kernel + initramfs + FDT
- **rootfs.squashfs** — root filesystem for the NOS

**Build steps:**

1. **Kernel**: Build Linux (e.g. 5.10) for powerpc; produce `uImage` (legacy wrapper). DTB: `as5610_52x.dtb` (from ONL tree or extract from Cumulus FIT).
2. **FIT**: Build FIT so it matches Cumulus format (required for U-Boot 2013.01 on this machine):
   - **Kernel**: raw gzip kernel (from `dumpimage -T kernel -p 0 -o kernel.gz uImage`), `load`/`entry` **0x00000000**, `compression = "gzip"`, `type = "kernel"`.
   - **Initramfs**: Include in the FIT and in **every** configuration as `ramdisk = "initramfs"`. Cumulus always has kernel + initramfs + fdt in each config; omitting ramdisk can cause `bootm` to fail with “can’t get kernel image!”.
   - **FDT**: `accton_as5610_52x_dtb` (description `accton_as5610_52x.dtb`), `type = "flat_dt"`, uncompressed.
   - Config nodes: `accton_as5610_52x` and optionally `edgecore_as5610_52x` (alias), each with `kernel`, `ramdisk`, `fdt`.
3. **Rootfs**: Build squashfs (e.g. from open-nos root).
4. **Pack**: Run `onie-installer/build.sh` to produce `data.tar` and then the single `.bin` file (script + tar). See `open-nos-as5610/scripts/build-onie-image.sh` for a full build.

**Cumulus reference FIT** (from `CumulusLinux-2.5.1-powerpc.bin` → `data.tar` → `uImage-powerpc.itb`):

- Kernel: PowerPC, gzip, load/entry 0x0, ~3 MiB.
- Initramfs: RAMDisk, uncompressed, ~809 KiB.
- Multiple DTBs; config `accton_as5610_52x` uses kernel + initramfs + `accton_as5610_52x_dtb`.

**ONIE demo** (machine tree `demo/platform.conf`): installs a single `demo-${platform}.itb` with `dd ... of=/dev/$blk_dev bs=4M` and loads with `usbboot $loadaddr ${usbdev}:0` (partition 0). Our installer uses a partitioned layout (e.g. sda5 = FIT, sda6 = rootfs) and `usbboot $loadaddr ${usbdev}:$active_part` with `active_part=5`.

## References

- ONIE repo: https://github.com/opencomputeproject/onie  
- ONIE docs: https://opencomputeproject.github.io/onie  
- This machine: https://github.com/opencomputeproject/onie/tree/master/machine/accton/accton_as5610_52x  

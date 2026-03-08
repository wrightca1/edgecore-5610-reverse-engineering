# Open Network Linux (ONL) — PowerPC / deb8 and AS5610-52X

Summary of how [Open Network Linux](https://github.com/opencomputeproject/OpenNetworkLinux) (ONL) handles PowerPC and the Accton AS5610-52X, for comparison with open-nos-as5610.

## Repo and layout

- **Repo**: https://github.com/opencomputeproject/OpenNetworkLinux  
- **Arch**: `make/config.powerpc.mk` — `ARCH_BOOT := uboot`, `TOOLCHAIN := powerpc-linux-gnu`, `ARCH := powerpc`.  
- **AS5610-52X**: `packages/platforms/accton/powerpc/as5610-52x/` (platform-config, onlp, modules).

## AS5610-52X platform config

From `packages/platforms/accton/powerpc/as5610-52x/platform-config/r0/src/lib/powerpc-accton-as5610-52x-r0.yml`:

- **flat_image_tree** (FIT): kernel + **dtb** (`powerpc-accton-as5610-52x-r0.dtb`), from package `onl-platform-build-powerpc-accton-as5610-52x-r0:powerpc`.
- **loader**: device `/dev/sda`, `nos_bootcmds: *usb_bootcmds`.
- **environment**: `/dev/mtd1` (NOR), offset 0x0, size 0x10000, sector 0x10000.
- **installer** partitions: ONL-BOOT 128MiB ext2, ONL-CONFIG 128MiB ext4, ONL-IMAGES 768MiB ext4, ONL-DATA remainder ext4.

So ONL uses a **platform-built DTB** from the ONL kernel/platform build, not a minimal hand-written DTS. The DTB is produced by the platform package and is expected to work with U-Boot and the kernel.

## PowerPC installer build

- **builds/powerpc/installer/installed/builds/Makefile** includes `config.powerpc.mk` and `builds/any/installer/uboot/builds/Makefile`.
- **builds/any/installer/uboot/builds/Makefile** builds the installer with:
  - `--fit onl-loader-fit:$(ARCH) onl-loader-fit.itb` — FIT image from package `onl-loader-fit`.
  - `--swi onl-swi:$(ARCH)` — switch image.
  - Pre/post install scripts and plugins.

The FIT (`onl-loader-fit.itb`) is built by the ONL build system (e.g. `flat-image-tree.py` or equivalent) and bundles kernel + initrd + **platform DTB** for the target.

## Installer flow (any arch)

- **builds/any/installer/installer.sh.in**: Unpacks initrd, chroots, runs `/usr/bin/onl-install --force`. Uses `onie_platform` / `onie_arch` from ONIE. For U-Boot: `has_uboot_env()` checks `fw_printenv` and `/etc/fw_env.config`.

ONL does **not** implement special FDT/chosen handling in the installer; it relies on:

1. A **correct platform DTB** (from kernel/platform build) that already has `/chosen`, console path, etc.  
2. U-Boot env on NOR for bootcmd and NOS boot.

## PPC/ARM deploy (opennetlinux.org)

- Doc: https://opennetlinux.org/doc-deploy-ppc-arm.html  
- Example (QuantaMesh LB9): U-Boot loads a **Legacy multi-file image** (kernel, ramdisk ~690 KiB, FDT ~9 KiB). “Loading Device Tree to 03ffa000, end 03fff425 … OK” then kernel boots. So ONL’s PPC images use a DTB that U-Boot loads without failing on chosen/stdout-path.

## Takeaways for open-nos-as5610

1. **Use a full platform DTB** — ONL uses a DTB from the platform/kernel build (`powerpc-accton-as5610-52x-r0.dtb`), not a minimal DTS. We use the **Cumulus DTB** (extracted from their FIT) for the same reason: it matches the board and U-Boot expectations (including `/chosen` and `linux,stdout-path`).
2. **Padding** — ONL’s build may produce DTBs with enough space for U-Boot fixups; we add **`dtc -p 0x3000`** when repacking the Cumulus DTB so U-Boot can add initrd/chosen properties.
3. **Partition layout** — ONL uses ONL-BOOT / ONL-CONFIG / ONL-IMAGES / ONL-DATA on `/dev/sda`. We use a single-slot layout (kernel partition, rootfs partition) on USB; same idea, different partitioning.
4. **Console** — We set **`consoledev`/`baudrate`** in U-Boot env so `initargs` builds `console=ttyS0,115200`; ONL’s platform config doesn’t show this explicitly in the YAML (may be in loader or initrd).

## open-nos-as5610 alignment (ONL-style)

We use the same platform-config pattern as ONL:

- **Platform YAML**: `open-nos-as5610/packages/platforms/accton/powerpc/as5610-52x/platform-config/r0/src/lib/powerpc-accton-as5610-52x-r0.yml` — single source of truth for loader, FIT, env, installer partitions.
- **Implementation**: `onie-installer/cumulus/init/accton_as5610_52x/platform.conf` and `platform.fdisk` implement the YAML; `uboot_env/` implements loader and console; `install.sh` uses platform.conf.
- **README**: `packages/platforms/accton/powerpc/as5610-52x/README.md` documents the mapping and differences from ONL.

## References

- ONL: https://github.com/opencomputeproject/OpenNetworkLinux  
- ONL building: https://opennetlinux.org/doc-building.html  
- ONL PPC/ARM deploy: https://opennetlinux.org/doc-deploy-ppc-arm.html  
- ONL AS5610 platform YAML: `packages/platforms/accton/powerpc/as5610-52x/platform-config/r0/src/lib/powerpc-accton-as5610-52x-r0.yml`

# Edgecore AS5610-52X Retimer Chip Information

## Retimer Chip: Texas Instruments DS100DF410
- Low Power 10GbE Quad Channel Retimer
- 32 retimers on the AS5610-52X platform
- Accessed via I2C (SMBus)

## Key Files

### Retimer Kernel Driver (patch)
- `/home/smiley/edgecore/OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_ds100df410.c.patch`
- I2C-based driver exposing sysfs attributes for CDR reset, equalization, VOD, DFE, channel selection, etc.

### Retimer Class Framework (patch)
- `/home/smiley/edgecore/OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_retimer_class.c.patch`
- Generic retimer device class for sysfs registration
- Author: Puneet Shenoy (Cumulus Networks, 2014)

### Retimer Init Script (extracted Cumulus)
- `/home/smiley/edgecore/extracted/2.5.0-powerpc/rootfs/usr/share/platform-config/accton/as5610_52x/hw_init.d/S20retimer_init.sh`
- Initializes all 32 retimers, configures EQ settings per port type (QSFP vs SFP)

### Kernel Build Config (patches)
- `/home/smiley/edgecore/OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_Kconfig.patch`
- `/home/smiley/edgecore/OpenNetworkLinux/packages/base/any/kernels/3.2-lts/configs/arm-iproc-all/patches/drivers_misc_Makefile.patch`
- Both CONFIG_RETIMER_CLASS and CONFIG_DS100DF410 are currently DISABLED in arm-iproc-all.config

### Platform Library Header
- `/home/smiley/edgecore/OpenNetworkLinux/packages/platforms/accton/powerpc/as5610-52x/onlp/builds/powerpc_accton_as5610_52x/module/src/platform_lib.h`

### AS5610 Platform Directory
- `/home/smiley/edgecore/OpenNetworkLinux/packages/platforms/accton/powerpc/as5610-52x/`

## DS100DF410 Register Map (from driver)

| Register | Function |
|----------|----------|
| 0x00 | Reset |
| 0x09 | Override |
| 0x0A | CDR Reset |
| 0x15 | TAP DEM |
| 0x1E | PFD / PRBS / DFE |
| 0x2D | Driver Select / VOD |
| 0x31 | Adaptive EQ State Machine |
| 0x36 | VEO Clock CDR Cap |
| 0xFF | Channel Select |

## DS100DF410 Sysfs Attributes
- `cdr_rst` - Clock Data Recovery reset
- `tap_dem` - Tap DEM register
- `pfd_prbs_dfe` - Phase Frequency Detector PRBS DFE
- `drv_sel_vod` - Driver selection VOD (Voltage Output Differential)
- `adapt_eq_sm` - Adaptive Equalization State Machine
- `veo_clk_cdr_cap` - VEO Clock CDR capacitance
- `channels` - Channel configuration
- `override` - Override register
- `reset` - Reset register

## Retimer Init Script EQ Settings
- QSFP ports: EQ2 (higher equalization)
- SFP RX ports: EQ2
- Other ports: EQ1 (default)

## Other Platforms with Retimer Code
- **AS9716-32d** (x86-64): Configures retimers at I2C addresses 0x18-0x1b on bus 22, sets 2x10G XFI mode, 800mV output, -3.5dB de-emphasis
  - File: `/home/smiley/edgecore/OpenNetworkLinux/packages/platforms/accton/x86-64/as9716_32d/platform-config/r0/src/python/x86_64_accton_as9716_32d_r0/__init__.py`

## Platform Hardware
- Switch chip: Broadcom BCM56846 (640 Gbps multilayer switch)
- Processor: Freescale P2020 (PowerPC e500v2)
- I2C mux: PCA9548 at address 0x70
- OpenMDK contains BCM56846 board config but NO retimer code

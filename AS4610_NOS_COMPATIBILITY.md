# Edgecore AS4610 NOS Compatibility

## Hardware Overview

| Attribute | Value |
|---|---|
| Models | AS4610-54T, AS4610-54P, AS4610-30 |
| Ports | 48x1G + 4x10G + 2x20G (54-port models) |
| CPU | ARM Cortex-A9 1GHz (Broadcom iProc) |
| Forwarding ASIC | BCM56340 (Helix4) |
| Architecture | ARM (armel / armhf) |

## Cumulus Linux Support

The AS4610 is **not** supported by all Cumulus Linux versions. Support was added
after the initial 2.5.x release and was temporarily dropped in 4.0.

| Cumulus Version | AS4610 Supported | Notes |
|---|---|---|
| 2.5.0 - 2.5.3 | No | Pre-dates AS4610 support |
| **2.5.4+** | **Yes** | First version with AS4610 support |
| 3.x (through 3.7.x) | Yes | Full support throughout 3.x lifecycle |
| 4.0 | **No** | Temporarily dropped; listed as unsupported |
| **4.1+** | **Yes** | Support restored for AS4610-54T and AS4610-54P |

### Local Image Inventory

The following extracted Cumulus images are available in `extracted/`:

| Image | Architecture | AS4610 Support |
|---|---|---|
| 2.5.0-amd64 | x86_64 | No |
| 2.5.0-powerpc | PowerPC | No |
| 2.5.1-amd64 | x86_64 | No |
| 2.5.1-powerpc | PowerPC | No |

None of these images include AS4610 platform configs. The AS4610 requires an
**ARM** image, and support was not added until Cumulus 2.5.4.

### Accton/Edgecore Platforms in Local Cumulus 2.5.0 Images

- AS4600-54T (PowerPC, BCM56540 Apollo2)
- AS5610-52X (PowerPC, BCM56846 Trident+)
- AS5712-54X (x86_64, BCM56854 Trident2)
- AS6700-32X (PowerPC, BCM56850 Trident2)
- AS6701-32X (PowerPC, BCM56850 Trident2)
- ES5652BT1

### Additional Platform in Cumulus 2.5.1

- AS6712-32X (x86_64, BCM56850 Trident2)

## Open Network Linux (ONL) Support

ONL has full platform support for the AS4610 in the local `OpenNetworkLinux/` tree:

- **AS4610-30**: `packages/platforms/accton/armhf/as4610/as4610-30/`
- **AS4610-54**: `packages/platforms/accton/armhf/as4610/as4610-54/`
- Shared platform code: `packages/platforms/accton/armxx/arm-accton-as4610/`

### ONL Driver Support

| Component | Driver Source |
|---|---|
| CPLD | `arm-accton-as4610/modules/accton_as4610_cpld.c` |
| Fan | `arm-accton-as4610/modules/accton_as4610_fan.c` |
| LEDs | `arm-accton-as4610/modules/accton_as4610_leds.c` |
| PSU | `arm-accton-as4610/modules/accton_as4610_psu.c` |
| SFP | `arm_accton_as4610/module/src/sfpi.c` |
| Thermal | `arm_accton_as4610/module/src/thermali.c` |
| Device Tree | `arm-accton-as4610/arm-accton-as4610.dts` |
| Kernel Patches | `kernels/3.2-lts/configs/arm-iproc-all/patches/platform-accton-as4610-device-drivers.patch` |

## Summary

To run a NOS on the AS4610:

1. **Cumulus Linux** - Requires version **2.5.4 or later** (ARM image). Avoid 4.0 (no support). Version 4.1+ restores support.
2. **Open Network Linux** - Fully supported with ONLP drivers, device tree, and kernel patches available in the local ONL tree.

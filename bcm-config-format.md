# BCM Config File Format Specification

**Source**: Reverse engineering of Cumulus Linux 2.5.1 `/etc/bcm.d/`
**Date**: 2026-02-15

## Overview

The BCM SDK uses configuration files in two formats:
1. **`.bcm` files** - Key=value SDK parameters
2. **`rc.soc` script** - SOC initialization commands (imperative script)

## 1. .bcm File Format

### Syntax

- **Key=Value** - One per line
- **Comments** - Lines starting with `#`
- **Unit suffix** - Some keys use `.0` for unit 0: `portmap_1.0=65:10`
- **No quotes** - Values are unquoted
- **Whitespace** - Trimmed; empty lines ignored

### Common Parameters

#### IRQ and DMA

| Parameter | Values | Purpose |
|-----------|--------|---------|
| polled_irq_mode | 0, 1 | 0=hardware IRQs, 1=polled |
| table_dma_enable | 0, 1 | Enable table DMA |
| tslam_dma_enable | 0, 1 | Enable SLAM DMA |
| tdma_intr_enable | 0, 1 | Table DMA interrupts |
| tslam_intr_enable | 0, 1 | SLAM DMA interrupts |
| miim_intr_enable | 0, 1 | MDIO/PHY interrupts |

#### Statistics

| Parameter | Values | Purpose |
|-----------|--------|---------|
| bcm_stat_flags | 0x0, 0x1 | 0x1=counter DMA |
| bcm_stat_interval | microseconds | Stats poll interval |

#### L2/L3

| Parameter | Values | Purpose |
|-----------|--------|---------|
| l2xmsg_mode | 0, 1 | L2 table notification (0=poll, 1=FIFO) |
| l2_mem_entries | int | L2 table size |
| l3_mem_entries | int | L3 table size |

#### Port Mapping

| Parameter | Format | Example | Purpose |
|-----------|--------|---------|---------|
| portmap_N | physical:speed | portmap_1=1:10 | Logical port N = physical lane at speed (10=10G, 40=40G) |
| portmap_N.0 | physical:speed | portmap_1.0=65:10 | Same, with unit 0 suffix (Cumulus) |
| pbmp_xport_xe | hex | pbmp_xport_xe=0x3ffffffffffff | Port bitmap for XE ports |
| pbmp_valid | hex | pbmp_valid.0=0x2001fffffffffffff | Valid port bitmap |

#### PHY/MDIO

| Parameter | Values | Purpose |
|-----------|--------|---------|
| mdio_output_delay | int | MDIO timing |
| mdio_io_voltage | 0, 1 | I/O voltage |
| miim_timeout_usec.N | microseconds | MDIO timeout per unit |
| serdes_firmware_mode | hex | SerDes firmware mode |
| xgxs_lcpll_xtal_refclk | 0, 1 | LCPLL crystal reference |

#### Other

| Parameter | Values | Purpose |
|-----------|--------|---------|
| parity_enable | 0, 1 | Parity checking |
| bcm_xlate_port_map.* | name | Port translation map |
| bcm_xlate_sysport_enable.* | 0, 1 | System port translation |
| parity_correction | 0, 1 | Parity correction |

### File Locations

- `/etc/bcm.d/config.d/01config.bcm` - Platform-specific overrides
- `/usr/share/cumulus/__chip_config/bcm/Trident/sdk.bcm` - Chip defaults (Trident/Trident+)
- Platform configs merge: chip defaults + 01config.bcm

### Parsing Rules

1. Read files in order: chip sdk.bcm first, then config.d/*.bcm
2. Later values override earlier
3. Unit suffix `.0` applies to unit 0; strip for single-unit systems
4. Portmap: `portmap_<logical>=<physical_lane>:<speed>`
   - speed 10 = 10G, 40 = 40G
   - physical_lane = SerDes lane index

## 2. rc.soc Script Format

### Command Types

| Command | Syntax | Purpose |
|---------|--------|---------|
| debug | debug +/-FLAG | Enable/disable debug categories |
| attach | attach * | Attach to all BCM units |
| unit | N: | Set current unit (N: on own line) |
| init | init all | Initialize ASIC |
| rcload | rcload /path | Load config file (rc.ports, rc.led, rc.datapath) |
| setreg | setreg REG VALUE | Write register |
| s | s REG FIELD=VALUE | Set register field |
| m | m REG FIELD=VALUE | Modify register field |
| save | save /sys/path value | Write to sysfs |
| sleep | sleep N | Sleep N seconds |

### Debug Flags (from rc.soc)

- PCi, SChan, SOCMEM, SYMTAB, VERInet, L3, INTr
- ARL, ARLMon, L2table, DMA, POrt, PAcket, TX
- RCLOAD, TEsts, VERbose, MIIm, PHY, END
- LInk, CounTeR, IP, STP, VLAN, RX, I2C, REG, MEM, STK

### Execution Order (from Cumulus rc.soc)

1. `debug -FLAG` (disable all debug)
2. `attach *`
3. `0:` (unit 0)
4. Optional: save sysfs (LED reset, QSFP mode)
5. `sleep 1` (if gpio used)
6. `init all`
7. `0: rcload /etc/bcm.d/rc.ports_0`
8. `rcload /etc/bcm.d/rc.led`
9. `setreg` (statistics, drop counters)
10. `0: rcload /var/lib/cumulus/rc.datapath_0`

### rc.ports_N Format

Loaded by `rcload /etc/bcm.d/rc.ports_0`. Contains port mapping in .bcm format:
- portmap_1.0=65:10 through portmap_52.0=...
- pbmp_xport_xe.0, pbmp_valid.0

### rc.led Format

LED program configuration. Binary/opcode format - loaded into ASIC LED controller.

### rc.datapath_N Format

Runtime-generated datapath config. Created by switchd during init.

## 3. Backend Map

`/etc/bcm.d/backend_map`:
```
backend index list:
backend 0
```
Maps backend index to unit. Single-line "backend N" per unit.

## 4. Implementation Notes

For open-source config parser:

1. **.bcm parser**: Simple key=value, strip comments, handle unit suffix
2. **rc.soc interpreter**: State machine - current unit, parse line by line
3. **rcload**: Recursive - rc.soc can load rc.ports which is .bcm format
4. **setreg/s/m**: Need register name table - map to SDK soc_reg interface

## References

- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md) Section 5
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found config paths (`/config/route/table`, `/config/coalesce/offset`, `/config/resv_vlan_range`) that may correspond to sysfs-style config nodes or internal config keys, complementing the `.bcm` file format documented here
- [CUMULUS_SYSTEM_DUMP.md](../../CUMULUS_SYSTEM_DUMP.md)
- [open-nos-build/docs/PORT_49_52_BREAKOUT.md](../../open-nos-build/docs/PORT_49_52_BREAKOUT.md)

# OpenMDK Reference for BCM56846 (Trident+) / Edgecore AS5610-52X

> **Purpose**: AI-searchable index of all OpenMDK code relevant to the BCM56846_A1
> ASIC in the Edgecore AS5610-52X switch. Covers chip-specific files, inherited
> BCM56840 code, XGS architecture layer, PHY drivers, and board config.

**OpenMDK Version**: 2.10.9
**Repo Path**: `OpenMDK/`
**ASIC**: BCM56846_A1 (Trident+), Device ID 0xb846, Vendor 0x14e4, Rev A1=0x02
**Architecture**: XGS (NOT xgsd or xgsm)
**Base Chip**: BCM56840_B0 (all register definitions inherited from here)
**Throughput**: 640 Gbps
**Integrated PHY**: Warpcore XGXS SerDes (10G/40G)

---

## Table of Contents

1. [Repository Layout](#1-repository-layout)
2. [BCM56846 Chip-Specific Files](#2-bcm56846-chip-specific-files)
3. [BCM56840 Base Chip (Inherited)](#3-bcm56840-base-chip-inherited)
4. [XGS Architecture Layer](#4-xgs-architecture-layer)
5. [CMIC Register Definitions](#5-cmic-register-definitions)
6. [SCHAN (S-Channel) Protocol](#6-schan-s-channel-protocol)
7. [Register and Memory Access](#7-register-and-memory-access)
8. [BMD Driver Layer](#8-bmd-driver-layer)
9. [PHY Drivers (Warpcore)](#9-phy-drivers-warpcore)
10. [Board Configuration](#10-board-configuration)
11. [BDE (Hardware Abstraction)](#11-bde-hardware-abstraction)
12. [Key Register Address Cross-Reference](#12-key-register-address-cross-reference)
13. [Build Configuration](#13-build-configuration)

---

## 1. Repository Layout

```
OpenMDK/
  cdk/          Chip Development Kit - register/memory access, symbols, SCHAN
  bmd/          Broadcom Mini Driver - port, VLAN, MAC, stats, DMA, packet I/O
  phy/          PHY drivers - SerDes, copper, MIIM bus
  board/        Board configs - port maps, LED firmware, PHY bus wiring
  libbde/       BDE library - PCI BAR mapping, MDIO, iProc
  examples/     Sample apps (cdksim, linux-user)
  doc/          HTML documentation (Quick Start Guide, User Guide)
  RELDOCS/      Release notes
```

**Layer stack** (bottom to top):
```
libbde  →  cdk (arch/xgs)  →  bmd (arch/xgs)  →  board
                             →  phy (Warpcore)
```

---

## 2. BCM56846 Chip-Specific Files

All in `cdk/PKG/chip/bcm56846/`:

| File | Purpose |
|------|---------|
| `PKGINFO` | Package metadata: `ARCH:xgs`, `DEPEND:bcm56840` |
| `bcm56846_a0_chip.c` | Chip info struct, port map, setup function |
| `cdk_devids.def` | Device/vendor IDs: `0xb846` / `0x14e4`, revisions A0=0x01 A1=0x02 |
| `cdk_devlist.def` | Maps A0/A1 to `bcm56840_b0` base, family "Trident+" |
| `cdk_config_chips.def` | Build dependency: requires `BCM56840_B0` |
| `cdk_config_phys.def` | PHY config: enables `BCMI_WARPCORE_XGXS` |

### Key Details from `bcm56846_a0_chip.c`

**Port map** (69 physical ports):
```
0-52, 57-72  (ports 53-56 do not exist)
```

**Valid port bitmap**: `CDK_PBMP_3(0xffffffff, 0xffffffff, 0x000003ff)`

**Chip flags**:
- `CDK_XGS_CHIP_FLAG_CLAUSE45` - Use MDIO clause 45 for PHY access
- `CDK_XGS_CHIP_FLAG_SCHAN_EXT` - SCHAN message buffer at 0x800 (not 0x000)
- `CDK_XGS_CHIP_FLAG_SCHAN_SB0` - Source block 0 in SCHAN header
- `BCM56840_B0_CHIP_FLAG_BW640G` - 640G bandwidth mode

**Setup function**: Calls `cdk_xgs_setup(dev)` after setting `chip_info`.

**Everything else** (registers, blocks, symbols, address calculation) is inherited
from `bcm56840_b0`.

---

## 3. BCM56840 Base Chip (Inherited)

All in `cdk/PKG/chip/bcm56840/`:

| File | Size | Purpose |
|------|------|---------|
| `bcm56840_b0_defs.h` | 269K lines | **ALL register/memory definitions** for the chip |
| `bcm56840_b0_sym.c` | Large | Symbol table (name→address lookup) |
| `bcm56840_b0_chip.c` | | Chip info, block definitions, port numbering |
| `bcm56840_a0_defs.h` | | A0 revision register definitions |
| `bcm56840_a0_sym.c` | | A0 symbol table |
| `cdk_devids.def` | | BCM56840/56841/56843 device IDs |
| `cdk_devlist.def` | | Family mappings |

### How to Read `bcm56840_b0_defs.h`

This 269K-line auto-generated header defines **every register and memory table**
in the BCM56846. Pattern for each register:

```c
// Register address
#define REGISTER_NAMEr 0x00000XXX
#define REGISTER_NAMEr_SIZE N  // bytes

// Type union
typedef union REGISTER_NAMEr_s { uint32_t v[N/4]; ... } REGISTER_NAMEr_t;

// Whole-register access
#define REGISTER_NAMEr_CLR(r)  // zero
#define REGISTER_NAMEr_SET(r,d)  // set raw value
#define REGISTER_NAMEr_GET(r)  // get raw value

// Field access
#define REGISTER_NAMEr_FIELD_NAMEf_GET(r)  // extract field
#define REGISTER_NAMEr_FIELD_NAMEf_SET(r,f)  // set field

// I/O macros
#define READ_REGISTER_NAMEr(u,r)  // read from hardware
#define WRITE_REGISTER_NAMEr(u,r)  // write to hardware
```

**Important**: The BCM56840 defs use chip-prefixed names internally
(`BCM56840_B0_CMIC_MISC_CONTROLr`) but the build system creates unprefixed
aliases when compiling for BCM56846 target.

---

## 4. XGS Architecture Layer

All in `cdk/PKG/arch/xgs/`:

### Core Files

| File | Purpose |
|------|---------|
| `xgs_chip.c` | Chip setup, block management |
| `xgs_chip.h` | `cdk_xgs_chip_info_t` struct, block types, flags |
| `xgs_cmic.h` | **CMIC register definitions** (1060 lines, auto-generated) |
| `xgs_schan.h` | SCHAN message types, header field macros, control bits |
| `xgs_schan.c` | `cdk_xgs_schan_op()` - execute SCHAN transaction |
| `xgs_setup.c` | Device setup entry point |

### Register Access

| File | Purpose |
|------|---------|
| `xgs_reg.h` | Register read/write function declarations |
| `xgs_reg.c` | Core register access via SCHAN |
| `xgs_reg32_read.c` | 32-bit register read |
| `xgs_reg32_write.c` | 32-bit register write |
| `xgs_reg32_port_read.c` | Port-indexed 32-bit read |
| `xgs_reg32_port_write.c` | Port-indexed 32-bit write |
| `xgs_reg32_block_read.c` | Block-indexed 32-bit read |
| `xgs_reg32_block_write.c` | Block-indexed 32-bit write |
| `xgs_reg32_blockport_read.c` | Block+port indexed read |
| `xgs_reg32_blockport_write.c` | Block+port indexed write |
| `xgs_reg32_blocks_read.c` | Read from all blocks of a type |
| `xgs_reg32_blocks_write.c` | Write to all blocks of a type |
| `xgs_reg32_writei.c` | Write with index |
| `xgs_reg32_port_writei.c` | Port-indexed write with index |
| `xgs_reg32_block_writei.c` | Block-indexed write with index |
| `xgs_reg32_blockport_writei.c` | Block+port write with index |
| `xgs_reg32_blocks_writei.c` | All-blocks write with index |
| `xgs_reg64_*.c` | Same patterns for 64-bit registers |
| `xgs_reg_block_read.c` | Variable-width block read |
| `xgs_reg_block_write.c` | Variable-width block write |
| `xgs_reg_blocks_read.c` | Variable-width all-blocks read |
| `xgs_reg_blocks_write.c` | Variable-width all-blocks write |
| `xgs_reg_port_read.c` | Variable-width port read |
| `xgs_reg_port_write.c` | Variable-width port write |
| `xgs_reg_index_valid.c` | Check if register index is valid |

### Memory Table Access

| File | Purpose |
|------|---------|
| `xgs_mem.h` | Memory read/write declarations |
| `xgs_mem.c` | Core memory access via SCHAN |
| `xgs_mem_block_read.c` | Read memory table entry from specific block |
| `xgs_mem_block_write.c` | Write memory table entry to specific block |
| `xgs_mem_block_clear.c` | Clear memory table in a block |
| `xgs_mem_blocks_read.c` | Read from all blocks |
| `xgs_mem_blocks_write.c` | Write to all blocks |
| `xgs_mem_clear.c` | Clear entire memory table |
| `xgs_mem_maxidx.c` | Get max index for a memory |
| `xgs_mem_op.c` | Table operations: INSERT, DELETE, LOOKUP, PUSH, POP |

### MIIM (PHY MDIO Access)

| File | Purpose |
|------|---------|
| `xgs_miim.h` | MIIM function declarations, bus macros |
| `xgs_miim.c` | `cdk_xgs_miim_read/write()` - clause 22/45 PHY access |
| `xgs_miim_iblk_read.c` | Internal block MIIM read (for SerDes PHYs) |
| `xgs_miim_iblk_write.c` | Internal block MIIM write |

### Block/Port Mapping

| File | Purpose |
|------|---------|
| `xgs_block.c` | Block type lookup |
| `xgs_block_addr.c` | Block address calculation |
| `xgs_block_number.c` | Block number lookup |
| `xgs_block_pbmp.c` | Block port bitmap |
| `xgs_block_type.c` | Block type enumeration |
| `xgs_blockport_addr.c` | Combined block+port address |
| `xgs_port_addr.c` | Port address calculation |
| `xgs_port_block.c` | Port-to-block mapping |
| `xgs_port_number.c` | Port numbering |

### Shell Commands

`xgs_shell/` contains CLI commands for interactive register/memory access:
`get`, `set`, `geti`, `seti`, `list`, `lookup`, `modify` etc.

---

## 5. CMIC Register Definitions

From `cdk/PKG/arch/xgs/xgs_cmic.h` (shared across all XGS chips):

| Register | Offset | Description |
|----------|--------|-------------|
| `CMIC_CONFIGr` | 0x010C | Main config: CPS reset, SCHAN abort, DMA enables |
| `CMIC_SCHAN_CTRLr` | 0x0050 | SCHAN control: start/done/abort/NAK/timeout bits |
| `CMIC_SCHAN_ERRr` | 0x005C | SCHAN error details |
| `CMIC_IRQ_STATr` | (in file) | Interrupt status including SCHAN_ERR |
| `CMIC_IRQ_MASKr` | (in file) | Interrupt mask |

From `cdk/PKG/chip/bcm56840/bcm56840_b0_defs.h` (chip-specific):

| Register | Offset | Description |
|----------|--------|-------------|
| `CMIC_MISC_CONTROLr` | 0x0860 | PLL power down, MDIO select, PLL load |

**IMPORTANT NOTE**: The CMIC_MISC_CONTROL at 0x0860 in OpenMDK is a different
register than the MISC_CONTROL at 0x01C we found via hardware probing. The 0x01C
register is not defined in OpenMDK but exists on the hardware.

### CMIC_CONFIG Fields (0x010C)

From `xgs_cmic.h`:
- bit 0: `RD_BRST_EN` - PIO read burst enable
- bit 1: `WR_BRST_EN` - PIO write burst enable
- bit 5: `RESET_CPS` - Drive CPS-Channel reset
- bit 6: `ACT_LOW_INT` - Active-low interrupt
- bit 7: `SCHAN_ABORT` - Abort pending SCHAN operation
- bit 11: `LE_DMA_EN` - Little-endian DMA
- bit 12: `I2C_EN` - I2C access enable
- bit 29: `OVER_RIDE_EXT_MDIO_MSTR_CNTRL` - CMIC as MDIO master

---

## 6. SCHAN (S-Channel) Protocol

### Files
- **Header/types**: `cdk/PKG/arch/xgs/xgs_schan.h`
- **Implementation**: `cdk/PKG/arch/xgs/xgs_schan.c`

### Message Buffer

22 x 32-bit words (`CMIC_SCHAN_WORDS_ALLOC = 22`).

For BCM56846 with `CDK_XGS_CHIP_FLAG_SCHAN_EXT`, the message buffer is at
**BAR0 + 0x0800** (extended address). Without this flag it would be at 0x0000.

**NOTE**: Our hardware testing confirmed 0x0800 is an alias of 0x0000 (CMIC
space repeats every 2KB). Both addresses work.

### SCHAN Header Format (32-bit word)

```
Bits [31:26] = opcode  (6 bits)
Bits [25:20] = dstblk  (6 bits)
Bits [19:14] = srcblk  (6 bits)
Bits [13:7]  = datalen (7 bits)
Bit  [6]     = ebit    (error indicator)
Bits [5:4]   = ecode   (error code)
Bits [3:1]   = cos     (class of service)
Bit  [0]     = cpu     (CPU bit)
```

Field access macros: `SCMH_OPCODE_GET/SET`, `SCMH_DSTBLK_GET/SET`, etc.

### SCHAN Opcodes

| Opcode | Value | Description |
|--------|-------|-------------|
| `READ_MEMORY_CMD_MSG` | 0x07 | Read memory table entry |
| `READ_MEMORY_ACK_MSG` | 0x08 | Read memory response |
| `WRITE_MEMORY_CMD_MSG` | 0x09 | Write memory table entry |
| `WRITE_MEMORY_ACK_MSG` | 0x0A | Write memory ack |
| `READ_REGISTER_CMD_MSG` | 0x0B | Read register |
| `READ_REGISTER_ACK_MSG` | 0x0C | Read register response |
| `WRITE_REGISTER_CMD_MSG` | 0x0D | Write register |
| `WRITE_REGISTER_ACK_MSG` | 0x0E | Write register ack |
| `ARL_INSERT_CMD_MSG` | 0x0F | ARL insert |
| `ARL_DELETE_CMD_MSG` | 0x11 | ARL delete |
| `ARL_LOOKUP_CMD_MSG` | 0x19 | ARL lookup |
| `TABLE_INSERT_CMD_MSG` | 0x24 | Generic table insert |
| `TABLE_DELETE_CMD_MSG` | 0x26 | Generic table delete |
| `TABLE_LOOKUP_CMD_MSG` | 0x28 | Generic table lookup |
| `FIFO_POP_CMD_MSG` | 0x2A | FIFO pop |
| `FIFO_PUSH_CMD_MSG` | 0x2C | FIFO push |

### SCHAN Control Bits (CMICe byte-write format at 0x0050)

```c
SC_MSG_START_SET  = 0x80  // Write to start SCHAN operation
SC_MSG_START_CLR  = 0x00  // Clear start bit
SC_MSG_DONE_TST   = 0x00000002  // Test done (read as 32-bit)
SC_MSG_NAK_TST    = 0x00200000  // Test NAK (bit 21)
SC_MSG_TIMEOUT_TST = 0x00400000  // Test timeout (bit 22)
SC_MSG_DONE_CLR   = 0x01  // Clear done bit (byte write)
```

### SCHAN Operation Flow (`cdk_xgs_schan_op`)

```
1. Determine msg_addr (0x800 for SCHAN_EXT, else 0x000)
2. Write message words to msg_addr + i*4
3. Write SC_MSG_START_SET (0x80) to CMIC_SCHAN_CTRLr (0x50)
4. Poll CMIC_SCHAN_CTRLr for SC_MSG_DONE_TST (bit 1)
5. Check for NAK, timeout, SCHAN_ERR
6. Write SC_MSG_DONE_CLR to CMIC_SCHAN_CTRLr
7. Read response words from msg_addr + i*4
8. On error: toggle SCHAN_ABORT in CMIC_CONFIG (0x10C bit 7)
```

### SCHAN Message Types (C structs)

| Type | Struct | Fields |
|------|--------|--------|
| Read command | `schan_msg_readcmd_t` | header + address |
| Read response | `schan_msg_readresp_t` | header + data[21] |
| Write command | `schan_msg_writecmd_t` | header + address + data[20] |
| Generic table cmd | `schan_msg_gencmd_t` | header + address + data[20] |
| Generic table resp | `schan_msg_genresp_t` | header + response + data[20] |
| ARL insert | `schan_msg_arlins_t` | header + data[3] |
| L2X2 cmd | `schan_msg_l2x2_t` | header + data[3] |
| L3X2 cmd | `schan_msg_l3x2_t` | header + data[13] |

### Generic Table Response Codes

```c
SCGR_TYPE_FOUND      = 0
SCGR_TYPE_NOT_FOUND   = 1
SCGR_TYPE_FULL        = 2
SCGR_TYPE_INSERTED    = 3
SCGR_TYPE_REPLACED    = 4
SCGR_TYPE_DELETED     = 5
SCGR_TYPE_ERROR       = 15
```

---

## 7. Register and Memory Access

### How Register Access Works

All register/memory reads and writes ultimately go through `cdk_xgs_schan_op()`.

**Register read flow**:
1. Build SCHAN header: opcode=0x0B (READ_REG), dstblk, srcblk
2. Set address word
3. Call `cdk_xgs_schan_op(unit, &msg, 2, dwc_read)`
4. Response opcode will be 0x0C (READ_REG_ACK), data in msg.readresp.data[]

**Register write flow**:
1. Build SCHAN header: opcode=0x0D (WRITE_REG), dstblk, srcblk
2. Set address word + data words
3. Call `cdk_xgs_schan_op(unit, &msg, 2+dwc_data, 1)`
4. Response opcode will be 0x0E (WRITE_REG_ACK)

### Access Pattern Functions

**Port-based** (most common for MAC/port registers):
```c
cdk_xgs_reg32_port_read(unit, port, addr, &val)
cdk_xgs_reg32_port_write(unit, port, addr, val)
```

**Block-based** (for specific hardware blocks):
```c
cdk_xgs_reg32_block_read(unit, blkidx, addr, &val)
cdk_xgs_reg32_block_write(unit, blkidx, addr, val)
```

**Memory table** (L2, VLAN, etc.):
```c
cdk_xgs_mem_block_read(unit, blkidx, addr, index, data, size)
cdk_xgs_mem_block_write(unit, blkidx, addr, index, data, size)
cdk_xgs_mem_op(unit, &msg, op_type)  // INSERT/DELETE/LOOKUP
```

---

## 8. BMD Driver Layer

### Chip-Specific BMD (all at `bmd/PKG/chip/`)

BCM56846 has NO chip-specific BMD directory. It inherits everything from
BCM56840, which has two revision directories:

**`bcm56840_a0/`** (actual implementations, 34 files):

| File | Purpose |
|------|---------|
| `bcm56840_a0_bmd_attach.c` (19KB) | Device init, PHY bus setup, port property assignment |
| `bcm56840_a0_bmd_reset.c` (25KB) | Chip reset: CPS, PLL, xport/Warpcore init |
| `bcm56840_a0_bmd_init.c` (74KB) | Full chip init: MMU, ports, VLANs, MAC, EPC |
| `bcm56840_a0_bmd_port_mode_set.c` (15KB) | Set port speed/duplex/loopback (1G/10G/HiGig) |
| `bcm56840_a0_bmd_port_mode_get.c` | Get current port mode |
| `bcm56840_a0_bmd_port_mode_update.c` | Update port after mode change |
| `bcm56840_a0_bmd_port_vlan_set.c` | Set port default VLAN (PVID) |
| `bcm56840_a0_bmd_port_vlan_get.c` | Get port default VLAN |
| `bcm56840_a0_bmd_port_stp_set.c` | Set STP state (disable/learn/forward/block) |
| `bcm56840_a0_bmd_port_stp_get.c` | Get STP state |
| `bcm56840_a0_bmd_vlan_create.c` | Create VLAN |
| `bcm56840_a0_bmd_vlan_destroy.c` | Destroy VLAN |
| `bcm56840_a0_bmd_vlan_port_add.c` | Add port to VLAN (tagged/untagged) |
| `bcm56840_a0_bmd_vlan_port_get.c` | Get ports in VLAN |
| `bcm56840_a0_bmd_vlan_port_remove.c` | Remove port from VLAN |
| `bcm56840_a0_bmd_cpu_mac_addr_add.c` | Add CPU MAC to L2 table |
| `bcm56840_a0_bmd_cpu_mac_addr_remove.c` | Remove CPU MAC from L2 table |
| `bcm56840_a0_bmd_port_mac_addr_add.c` | Add MAC address to port |
| `bcm56840_a0_bmd_port_mac_addr_remove.c` | Remove MAC address from port |
| `bcm56840_a0_bmd_stat_get.c` | Get port statistics (counters) |
| `bcm56840_a0_bmd_stat_clear.c` | Clear port statistics |
| `bcm56840_a0_bmd_rx.c` | Core RX packet implementation |
| `bcm56840_a0_bmd_rx_start.c` | Start RX DMA |
| `bcm56840_a0_bmd_rx_stop.c` | Stop RX DMA |
| `bcm56840_a0_bmd_rx_poll.c` | Poll for received packets |
| `bcm56840_a0_bmd_tx.c` | Transmit packet |
| `bcm56840_a0_bmd_switching_init.c` | Initialize switching fabric + EPC |
| `bcm56840_a0_bmd_download.c` | Download firmware/microcode |
| `bcm56840_a0_bmd_detach.c` | Detach device |
| `bcm56840_a0_bmd_test_interrupt_*.c` | Test interrupt assert/clear |
| `bcm56840_a0_internal.h` | Internal helpers, register shortcuts, constants |

**`bcm56840_b0/`** (thin wrappers, 30 files):
Each `bcm56840_b0_bmd_*.c` simply calls the corresponding `bcm56840_a0_bmd_*()`
function. B0 is a silicon revision compatible with A0.

### Key Reset Sequence (from `bcm56840_a0_bmd_reset.c`)

The Warpcore PHY init sequence (`bcm56840_a0_warpcore_phy_init`):
1. Enable multi-MMD mode via clause 22 reg 0x1f=0x8000, 0x1d
2. Stop Warpcore sequencer (CL45 PMA 0x8000 bit 13)
3. Set independent lane mode for speeds <= 20G
4. Enable broadcast (CL45 PMA 0xffde = 0x01ff)
5. Configure speed advertisements per port type
6. Set reference clock: 156.25 MHz or 161.25 MHz
7. Disable broadcast
8. Restart sequencer

The xport reset sequence (`bcm56840_a0_xport_reset`):
1. Configure MDIO device-in-package
2. Force into reset (IDDQ, PWRDWN, PWRDWN_PLL, RSTB_HW=0)
3. Power up (clear IDDQ, PWRDWN, PWRDWN_PLL)
4. Release HW reset (RSTB_HW=1)
5. Release MDIO reset (RSTB_MDIO=1)
6. Release PLL reset (RSTB_PLL=1)
7. Wait for TX PLL lock (XGXS_STATUS_GEN_REG bit 12)
8. Release TX FIFO resets

### PHY Address Mapping (from reset.c)

```c
ports 1-24:  phy_addr = port + MIIM_IBUS(0)
ports 25-48: phy_addr = (port-24) + MIIM_IBUS(1)
ports 49+:   phy_addr = (port-48) + MIIM_IBUS(2)
```

### XGS Architecture BMD

At `bmd/PKG/arch/xgs/`:

| File | Purpose |
|------|---------|
| `xgs_dma.h` / `xgs_dma.c` | DMA engine init, TX/RX control |
| `xgs_mac_util.h` / `.c` | MAC utilities (LAG, speed calc) |
| `xgs_stp_xlate.c` | STP state translation |
| `xgs_led_prog.c` | LED programming |
| `xgs_led_update.c` | LED state update |
| `xgs_dump_rx_dcb.c` | Debug: dump RX DMA Control Block |
| `shell/` | BMD shell commands |

### BMD API (at `bmd/include/bmd/`)

| Header | Purpose |
|--------|---------|
| `bmd.h` | Main BMD API declarations |
| `bmd_device.h` | Device management |
| `bmd_dma.h` | DMA operations |
| `bmd_phy.h` | PHY control interface |
| `bmd_phy_ctrl.h` | PHY control internals |

### BMD Shared Code (at `bmd/shared/`)

| File | Purpose |
|------|---------|
| `bmd_device.c` | Device attach/detach management |
| `bmd_phy_ctrl.c` | PHY speed/duplex/autoneg/loopback control |
| `bmd_phy_staged_init.c` | Staged PHY init (probe/init/reset callbacks) |
| `bmd_phy_probe_default.c` | Default PHY auto-detection |
| `bmd_link_update.c` | Link state change tracking |
| `bmd_dma.c` | Generic DMA handling |
| `bmd_port_mode_from_phy.c` | Convert PHY state to port mode |

---

## 9. PHY Drivers (Warpcore)

### Warpcore XGXS Driver

At `phy/PKG/chip/bcmi_warpcore_xgxs/`:

| File | Size | Purpose |
|------|------|---------|
| `bcmi_warpcore_xgxs_drv.c` | 73 KB | Main driver: init, speed, link, autoneg, loopback |
| `bcmi_warpcore_xgxs_defs.h` | 4.9 MB | Register/field definitions for Warpcore |
| `bcmi_warpcore_xgxs_firmware_set.c` | 5.5 KB | Firmware download support |
| `bcmi_warpcore_xgxs_ucode.c` | 164 KB | Microcode binary (A0 silicon) |
| `bcmi_warpcore_xgxs_ucode_b0.c` | 186 KB | Microcode binary (B0 silicon) |
| `bcmi_warpcore_xgxs_sym.c` | 726 KB | Symbol table |

**PHY ID**: BCM Serdes ID 0x09, PHY ID0=0x143, PHY ID1=0xbff0

**Supported Speeds**:
- 10M, 100M, 1G, 1G-KX, 2.5G, 5G
- 10G (CX4, KX4, KR, XFI, SFI, HiG, DXGXS variants)
- 12G, 13G, 15G, 16G, 20G, 21G, 25G, 31.5G
- 40G (KR4, CR4, generic)

**Lane Modes**:
- 1-lane: Single SerDes lane, up to 10G
- 2-lane: Dual DXGXS, 10G-20G range
- 4-lane: Full quad, up to 40G

**Driver API** (standard `phy_driver_t`):
```c
bcmi_warpcore_xgxs_probe()       // Identify PHY
bcmi_warpcore_xgxs_init()        // Initialize (staged)
bcmi_warpcore_xgxs_link_get()    // Get link status
bcmi_warpcore_xgxs_speed_set()   // Force speed
bcmi_warpcore_xgxs_speed_get()   // Read current speed
bcmi_warpcore_xgxs_ability_get() // Report capabilities
bcmi_warpcore_xgxs_autoneg_*()   // Auto-negotiation
bcmi_warpcore_xgxs_loopback_*()  // Loopback control
```

**MIIM Access**: Uses AER (Address Extension Register) IBLK access:
```c
phy_aer_iblk_read()   // Internal block read
phy_aer_iblk_write()  // Internal block write
```

### MIIM Bus Driver

At `phy/PKG/bus/bcm56840_miim_int/`:

Internal MIIM bus for BCM56840/56846. Uses `cdk_xgs_miim_read/write()`.

Also: `phy/PKG/bus/bcm956840k_miim_ext/` for external PHYs (not used on AS5610).

### Generic PHY Functions

At `phy/generic/`:

| File | Purpose |
|------|---------|
| `ge_phy_speed_get.c` | Generic 1G PHY speed read |
| `ge_phy_speed_set.c` | Generic 1G PHY speed set |
| `ge_phy_duplex_get.c` | Duplex mode read |
| `ge_phy_duplex_set.c` | Duplex mode set |
| `ge_phy_autoneg_get.c` | Auto-negotiation status |
| `ge_phy_autoneg_set.c` | Auto-negotiation control |
| `ge_phy_loopback_get.c` | Loopback status |
| `ge_phy_loopback_set.c` | Loopback control |
| `ge_phy_link_get.c` | Link status |
| `ge_phy_init.c` | Generic PHY init |
| `ge_phy_reset.c` | Generic PHY reset |
| `unknown_drv.c` | Fallback for unknown PHYs |

---

## 10. Board Configuration

### BCM56846 SVK Board

At `board/config/board_bcm56846_svk.c`:

- 48 x 10G ports + 4 x 25G/40G ports = 52 total
- PHY bus: `phy_bus_bcm56840_miim_int` (internal), external MIIM
- LED program: `sdk56840_ledprog_info` from `board/xgsled/sdk56840.c`
- Warpcore XGXS with lane remapping
- Dynamic config: `DCFG_LCPLL_156` (156.25 MHz reference clock)

### Related Boards

| File | Description |
|------|-------------|
| `board_bcm56845_svk.c` | BCM56845 SVK (comment says "also works with BCM56846") |
| `board_bcm56844_ext.c` | BCM56844 Trident+ variant |
| `board_bcm56845_ext.c` | BCM56845 with external PHY |
| `board_bcm56845_ext2.c` | BCM56845 alternate external PHY config |

### LED Firmware

At `board/xgsled/sdk56840.c` and `board/include/board/sdk56840.h`:
- `ledprog_sdk56840[]` - LED program binary
- `sdk56840_ledprog_info()` - returns LED program info struct
- Shared by all Trident/Trident+ boards

### Board Mapping

At `board/config/board_config_map_sjlab.c`:
- `rack40_08` maps to `board_bcm56846_svk`

---

## 11. BDE (Hardware Abstraction)

At `libbde/shared/`:

| File | Purpose |
|------|---------|
| `shbde_pci.c` | PCI BAR mapping for ASIC registers |
| `shbde_iproc.c` | iProc CPU access (not used on AS5610) |
| `shbde_mdio.c` | MDIO bus driver for PHY access |

---

## 12. Key Register Address Cross-Reference

Mapping between OpenMDK register names and hardware addresses relevant to our
BCM56846:

### CMIC Core Registers (from xgs_cmic.h)

| OpenMDK Name | Offset | Our Usage |
|--------------|--------|-----------|
| `CMIC_SCHAN_CTRLr` | 0x0050 | SCHAN control (start/done/abort) |
| `CMIC_SCHAN_ERRr` | 0x005C | SCHAN error details |
| `CMIC_CONFIGr` | 0x010C | CPS reset (bit 5), SCHAN abort (bit 7) |

### SCHAN Message Buffer

| OpenMDK Concept | Offset | Notes |
|-----------------|--------|-------|
| `msg_addr` (SCHAN_EXT) | 0x0800 | BCM56846 uses this due to SCHAN_EXT flag |
| `msg_addr` (standard) | 0x0000 | Alias of 0x0800 (2KB wrap) |
| SCHAN_D(0) through D(21) | msg_addr + 0..0x54 | 22 x 32-bit message words |

### Chip-Specific Registers (from bcm56840_b0_defs.h)

| OpenMDK Name | Offset | Description |
|--------------|--------|-------------|
| `CMIC_MISC_CONTROLr` | 0x0860 | PLL power down, MDIO select |
| Various XLPORT_* | varies | Per-port MAC/PHY control |
| Various MMU_* | varies | Memory management unit |

### Hardware-Discovered Registers (NOT in OpenMDK)

| Offset | Our Name | Notes |
|--------|----------|-------|
| 0x01C | MISC_CONTROL | bit 0 = LINK40G_ENABLE; not defined in OpenMDK |
| 0x178 | DEV_REV_ID | Reads 0x0002B846; not in xgs_cmic.h |
| 0x200 | CMIC_SBUS_TIMEOUT | Referenced in xgs_cmic.h docs but no define |
| 0x204 | CMIC_SBUS_RING_MAP_0 | Not defined; we found via probing |
| 0x208 | CMIC_SBUS_RING_MAP_1 | Not defined |
| 0x20C | CMIC_SBUS_RING_MAP_2 | Not defined |
| 0x210 | CMIC_SBUS_RING_MAP_3 | Not defined |
| 0x580 | CMIC_SOFT_RESET_REG | Not in OpenMDK; found via RE |
| 0x57C | CMIC_SOFT_RESET_REG_2 | Not in OpenMDK; found via RE |

---

## 13. Build Configuration

### Required Config Defines

From `cdk/PKG/chip/bcm56846/cdk_config_chips.def`:
```c
CDK_CONFIG_INCLUDE_BCM56846_A0 = 1  // or A1
CDK_CONFIG_INCLUDE_BCM56840_B0 = 1  // required dependency
```

From `cdk/PKG/chip/bcm56846/cdk_config_phys.def`:
```c
PHY_CONFIG_INCLUDE_BCMI_WARPCORE_XGXS = 1
```

### Architecture Conditional

All XGS-specific code compiles under:
```c
#ifdef CDK_CONFIG_ARCH_XGS_INSTALLED
```

### Chip Include Pattern

All BCM56846 code includes:
```c
#include <cdk/chip/bcm56840_b0_defs.h>  // register definitions
#include <cdk/arch/xgs_chip.h>           // architecture types
#include <cdk/arch/xgs_miim.h>           // MIIM access
#include <cdk/arch/xgs_schan.h>          // SCHAN protocol
```

---

## Quick Lookup: "Where is the code for X?"

| Want to... | Look at... |
|------------|------------|
| Read/write a register | `cdk/PKG/arch/xgs/xgs_reg32_*.c` via `xgs_schan.c` |
| Read/write a memory table | `cdk/PKG/arch/xgs/xgs_mem_*.c` |
| Find a register address | `cdk/PKG/chip/bcm56840/bcm56840_b0_defs.h` |
| Find a CMIC register | `cdk/PKG/arch/xgs/xgs_cmic.h` |
| Do SCHAN transaction | `cdk/PKG/arch/xgs/xgs_schan.c` (`cdk_xgs_schan_op`) |
| Init the chip | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_init.c` |
| Reset the chip | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_reset.c` |
| Set port speed | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_port_mode_set.c` |
| Configure Warpcore PHY | `phy/PKG/chip/bcmi_warpcore_xgxs/bcmi_warpcore_xgxs_drv.c` |
| Access PHY via MDIO | `cdk/PKG/arch/xgs/xgs_miim.c` |
| Set up VLAN | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_vlan_*.c` |
| Send/receive packets | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_tx.c` / `_rx*.c` |
| Board port mapping | `board/config/board_bcm56846_svk.c` |
| LED programming | `board/xgsled/sdk56840.c` |
| Get chip device ID | `cdk/PKG/chip/bcm56846/cdk_devids.def` |
| Understand SCHAN header | `cdk/PKG/arch/xgs/xgs_schan.h` |
| PCI/BAR access | `libbde/shared/shbde_pci.c` |

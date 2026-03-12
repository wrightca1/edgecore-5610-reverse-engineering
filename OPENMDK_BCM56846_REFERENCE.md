# OpenMDK Comprehensive Reference: BCM56846 (Trident+) / Edgecore AS5610-52X

> **Purpose**: Complete reference of all OpenMDK code relevant to the BCM56846_A1
> ASIC in the Edgecore AS5610-52X switch. Covers chip-specific files, the BCM56840
> family, XGS architecture, WARPcore PHY drivers, XLPORT/XMAC MAC layer, and board
> configuration.

**OpenMDK Version**: 2.10.9
**Repo Path**: `OpenMDK/`
**ASIC**: BCM56846_A1 (Trident+), Device ID 0xb846, Vendor 0x14e4, Rev A1=0x02
**Architecture**: XGS (NOT xgsd or xgsm)
**Base Chip**: BCM56840_B0 (all register definitions inherited from here)
**Throughput**: 640 Gbps
**Integrated PHY**: WARPcore XGXS SerDes (10G/40G)

---

## Table of Contents

1. [What Makes BCM56846 Unique](#1-what-makes-bcm56846-unique)
2. [BCM56840 Family Overview](#2-bcm56840-family-overview)
3. [Repository Layout](#3-repository-layout)
4. [BCM56846 Chip-Specific Files](#4-bcm56846-chip-specific-files)
5. [BCM56840 Base Chip (Inherited)](#5-bcm56840-base-chip-inherited)
6. [Block Architecture and Port Mapping](#6-block-architecture-and-port-mapping)
7. [XGS Architecture Layer](#7-xgs-architecture-layer)
8. [CMIC Register Definitions](#8-cmic-register-definitions)
9. [SCHAN (S-Channel) Protocol](#9-schan-s-channel-protocol)
10. [Register and Memory Access](#10-register-and-memory-access)
11. [XLPORT / XMAC MAC Layer](#11-xlport--xmac-mac-layer)
12. [WARPcore XGXS PHY Driver](#12-warpcore-xgxs-phy-driver)
13. [MIIM (MDIO) PHY Access](#13-miim-mdio-phy-access)
14. [BMD Driver Layer](#14-bmd-driver-layer)
15. [DMA Engine](#15-dma-engine)
16. [Board Configuration](#16-board-configuration)
17. [Build Configuration](#17-build-configuration)
18. [Key Register Address Cross-Reference](#18-key-register-address-cross-reference)
19. [Quick Lookup Table](#19-quick-lookup-table)

---

## 1. What Makes BCM56846 Unique

The BCM56846 is a **die variant** of the BCM56840, not a separate silicon design.
All differences are in software configuration, not hardware. Here is what
distinguishes it from every other chip in the BCM56840 family:

### 1.1 BCM56846 vs BCM56840_B0 (the base it inherits from)

| Aspect | BCM56840_B0 | BCM56846 |
|--------|-------------|----------|
| **Device ID** | 0xb840 | 0xb846 |
| **Bandwidth** | 480 Gbps (default) | **640 Gbps** (BW640G flag set) |
| **BW640G flag** | NOT set | **Set** (`BCM56840_B0_CHIP_FLAG_BW640G`) |
| **Port map** | 53 ports (0-4, 9-48, 57-68) | **69 ports** (0-52, 57-72) |
| **Valid port bitmap** | Same 3-word PBMP | Same 3-word PBMP |
| **XLPORT blocks excluded** | Blocks 1, 5, 12, 13, 17 (default 480G) | **Only blocks 0, 13** (more ports active) |
| **Family label** | "Trident" | **"Trident+"** |
| **Register defs** | bcm56840_b0_defs.h | Same (inherited) |
| **Silicon revisions** | A0-A4, B0-B1 | **A0-A1 only** |
| **Setup function** | `bcm56840_b0_setup()` | **`bcm56846_a0_setup()`** (sets BW640G) |

The key difference is a **single chip flag**: `BCM56840_B0_CHIP_FLAG_BW640G`.
This flag changes port exclusion logic in `_port_speed_max()`, enabling more
XLPORT blocks and thus more physical ports.

### 1.2 BCM56846 vs BCM56845 (640G Trident, not Trident+)

| Aspect | BCM56845 | BCM56846 |
|--------|----------|----------|
| **Register base** | bcm56840_**a0** | bcm56840_**b0** |
| **Family** | "Trident" (original) | "Trident+" (revised) |
| **Revisions** | A0-A4, B0-B1 | A0-A1 |
| **Bandwidth** | 640 Gbps | 640 Gbps |
| **Silicon revision** | A-series = older die | B0-based = newer die |

BCM56845 is the 640G variant of original Trident silicon (A0 regs).
BCM56846 is the 640G variant of Trident+ silicon (B0 regs, bug fixes).

### 1.3 BCM56846 vs All Other Variants

| Chip | Dev ID | Family | Base Regs | Bandwidth | Revisions |
|------|--------|--------|-----------|-----------|-----------|
| **BCM56840** | 0xb840 | Trident | a0 / b0 | 480G | A0-A4, B0-B1 |
| **BCM56841** | 0xb841 | Trident | a0 / b0 | 320G | A0-A4, B0-B1 |
| **BCM56842** | 0xb842 | Trident+ | b0 | 320G | A0-A1 |
| **BCM56843** | 0xb843 | Trident | a0 / b0 | 480G | A0-A4, B0-B1 |
| **BCM56844** | 0xb844 | Trident+ | b0 | 480G | A0-A1 |
| **BCM56845** | 0xb845 | Trident | a0 / b0 | 640G | A0-A4, B0-B1 |
| **BCM56846** | 0xb846 | **Trident+** | **b0** | **640G** | **A0-A1** |

**Pattern**: The "Trident+" variants (BCM56842, BCM56844, BCM56846) all:
- Use `bcm56840_b0` register definitions exclusively
- Have only A0-A1 revisions
- Are newer silicon (bug fixes over original Trident)

**Bandwidth tiers** (320G / 480G / 640G) determine which XLPORT blocks are
active and thus how many ports the chip exposes.

### 1.4 XLPORT Block Exclusion by Bandwidth

The function `_port_speed_max()` in `bcm56840_a0_bmd_attach.c` determines
which XLPORT blocks are disabled based on bandwidth configuration:

```
BW640G (BCM56846):     Exclude blocks {0, 13}       → 16 active XLPORT blocks
Default 480G:          Exclude blocks {1, 5, 12, 13, 17} → 13 active blocks
BW320G:                Exclude blocks {1, 2, 5, 6, 11, 12, 13, 16, 17} → 9 blocks
HGONLY (HiGig-only):   Exclude blocks {0, 13}       → 16 blocks (40G each)
```

### 1.5 What BCM56846 Does NOT Change

Everything else is identical to BCM56840_B0:
- All register addresses and field definitions
- Block types, block numbers, block structure
- Address calculation function (`bcm56840_b0_blockport_addr`)
- Symbol tables
- SCHAN protocol and flags
- CMIC registers
- XLPORT/XMAC register set
- WARPcore PHY driver
- MMU configuration
- Pipeline architecture (IPIPE/EPIPE)
- DMA engine

---

## 2. BCM56840 Family Overview

### 2.1 Complete Variant Table

All variants share vendor ID `0x14e4` and use the same physical die.

| Chip | Device ID | Rev Range | Base Regs | Family | Bandwidth | Description |
|------|-----------|-----------|-----------|--------|-----------|-------------|
| BCM56840 | 0xb840 | A0(0x01)-A4(0x05), B0(0x11)-B1(0x12) | a0/b0 | Trident | 480G | Base chip |
| BCM56841 | 0xb841 | A0(0x01)-A4(0x05), B0(0x11)-B1(0x12) | a0/b0 | Trident | 320G | Reduced BW |
| BCM56842 | 0xb842 | A0(0x01)-A1(0x02) | b0 only | Trident+ | 320G | T+ reduced BW |
| BCM56843 | 0xb843 | A0(0x01)-A4(0x05), B0(0x11)-B1(0x12) | a0/b0 | Trident | 480G | Alternate 480G |
| BCM56844 | 0xb844 | A0(0x01)-A1(0x02) | b0 only | Trident+ | 480G | T+ standard BW |
| BCM56845 | 0xb845 | A0(0x01)-A4(0x05), B0(0x11)-B1(0x12) | a0/b0 | Trident | 640G | Full BW original |
| BCM56846 | 0xb846 | A0(0x01)-A1(0x02) | b0 only | Trident+ | 640G | **Full BW T+** |

### 2.2 Register Definition Versions

Two register definition sets exist:

- **bcm56840_a0_defs.h**: Original Trident silicon (used by BCM56840 Ax, BCM56841 Ax, BCM56843 Ax, BCM56845 Ax)
- **bcm56840_b0_defs.h**: Trident+ silicon (used by BCM56840 Bx, BCM56841 Bx, BCM56842, BCM56843 Bx, BCM56844, BCM56845 Bx, **BCM56846**)

The B0 defs contain bug fixes and possibly additional registers vs A0.

### 2.3 CDK_DEVLIST_ENTRY Format

From `cdk_devlist.def`:
```c
CDK_DEVLIST_ENTRY(
    BCM56846,           // chip name
    BCM56846_VENDOR_ID, // 0x14e4
    BCM56846_DEVICE_ID, // 0xb846
    BCM56846_REV_A0,    // 0x01
    0, 0,               // model/rev override
    bcm56840_b0,        // register definitions base
    bcm56846_a0,        // chip setup function
    bcm56846_a0,        // chip init function
    CDK_DEV_ARCH_XGS,   // architecture
    "Trident+",         // family name
    "BCM56840",         // base chip name
    "640 Gbps Ethernet Multilayer Switch",  // description
    0, 0                // flags
)
```

---

## 3. Repository Layout

```
OpenMDK/
  cdk/          Chip Development Kit - register/memory access, symbols, SCHAN
    PKG/arch/xgs/     XGS architecture (SCHAN, MIIM, reg/mem access)
    PKG/arch/xgsd/    XGS-D architecture (SBUSv4, NOT used by BCM56846)
    PKG/arch/xgsm/    XGS-M architecture (NOT used by BCM56846)
    PKG/chip/bcm56840/ Base chip definitions (a0 + b0 register defs)
    PKG/chip/bcm56846/ BCM56846-specific setup (thin wrapper)
  bmd/          Broadcom Mini Driver - port, VLAN, MAC, stats, DMA, packet I/O
    PKG/arch/xgs/     XGS DMA, LED, MAC utilities
    PKG/chip/bcm56840_a0/  All functional code (reset, init, port, VLAN, etc.)
    PKG/chip/bcm56840_b0/  Thin wrappers calling a0 functions
  phy/          PHY drivers - SerDes, copper, MIIM bus
    PKG/chip/bcmi_warpcore_xgxs/  WARPcore driver (init, speed, link, firmware)
    PKG/bus/bcm56840_miim_int/    Internal MIIM bus driver
    PKG/bus/bcm956840k_miim_ext/  External MIIM bus (not used on AS5610)
    generic/    Generic GE PHY functions
  board/        Board configs - port maps, LED firmware, PHY bus wiring
    config/board_bcm56846_svk.c   BCM56846 SVK board configuration
    xgsled/sdk56840.c             LED firmware binary
  libbde/       BDE library - PCI BAR mapping, MDIO, iProc
  examples/     Sample apps
  doc/          HTML documentation
  RELDOCS/      Release notes
```

**Layer stack** (bottom to top):
```
libbde  →  cdk (arch/xgs)  →  bmd (arch/xgs)  →  board
                             →  phy (WARPcore)
```

---

## 4. BCM56846 Chip-Specific Files

All in `cdk/PKG/chip/bcm56846/`:

| File | Purpose |
|------|---------|
| `PKGINFO` | Package metadata: `ARCH:xgs`, `DEPEND:bcm56840` |
| `bcm56846_a0_chip.c` | Chip info struct, port map, setup function |
| `cdk_devids.def` | Device/vendor IDs: `0xb846` / `0x14e4`, revisions A0=0x01 A1=0x02 |
| `cdk_devlist.def` | Maps A0/A1 to `bcm56840_b0` base, family "Trident+" |
| `cdk_config_chips.def` | Build dependency: requires `BCM56840_B0` |
| `cdk_config_phys.def` | PHY config: enables `BCMI_WARPCORE_XGXS` |
| `cdk_allsyms.def` | Symbol definitions |

### 4.1 Key Details from `bcm56846_a0_chip.c`

```c
#include <cdk/chip/bcm56840_b0_defs.h>

// Reuses ALL BCM56840_B0 infrastructure:
extern const char *bcm56840_b0_blktype_names[];
extern cdk_xgs_block_t bcm56840_b0_blocks[];
extern cdk_symbols_t bcm56840_b0_symbols;
extern cdk_xgs_numel_info_t bcm56840_b0_numel_info;
extern uint32_t bcm56840_b0_blockport_addr(int block, int port, uint32_t offset);

// Port map (69 physical ports):
static cdk_port_map_port_t _ports[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
    47, 48, 49, 50, 51, 52,  // data ports
    57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
    // ports 53-56 do NOT exist
};

// Chip info structure - THE ONLY UNIQUE THING:
static cdk_xgs_chip_info_t bcm56846_a0_chip_info = {
    .cmic_block = BCM56840_B0_CMIC_BLOCK,    // = 5
    .nblktypes = 8,
    .blktype_names = bcm56840_b0_blktype_names,
    .blockport_addr = bcm56840_b0_blockport_addr,
    .nblocks = 28,                             // 28 non-CMIC blocks
    .blocks = bcm56840_b0_blocks,
    .valid_pbmps = CDK_PBMP_3(0xffffffff, 0xffffffff, 0x000003ff),
    .chip_flags =
        CDK_XGS_CHIP_FLAG_CLAUSE45 |
        CDK_XGS_CHIP_FLAG_SCHAN_EXT |
        CDK_XGS_CHIP_FLAG_SCHAN_SB0 |
        BCM56840_B0_CHIP_FLAG_BW640G |   // ← THIS IS THE BCM56846 DIFFERENCE
        0,
};
```

Compare with `bcm56840_b0_chip.c` which has:
```c
    .chip_flags =
        CDK_XGS_CHIP_FLAG_CLAUSE45 |
        CDK_XGS_CHIP_FLAG_SCHAN_EXT |
        CDK_XGS_CHIP_FLAG_SCHAN_SB0 |
        0,    // ← NO BW640G flag
```

---

## 5. BCM56840 Base Chip (Inherited)

All in `cdk/PKG/chip/bcm56840/`:

| File | Size | Purpose |
|------|------|---------|
| `bcm56840_b0_defs.h` | ~269K lines | **ALL register/memory definitions** |
| `bcm56840_b0_sym.c` | Large | Symbol table (name→address lookup) |
| `bcm56840_b0_chip.c` | 206 lines | Block definitions, port map, address function |
| `bcm56840_a0_defs.h` | ~269K lines | A0 revision register definitions |
| `bcm56840_a0_sym.c` | Large | A0 symbol table |
| `bcm56840_a0_chip.c` | | A0 chip info |
| `cdk_devids.def` | | Device IDs: 0xb840, Rev A0=0x01 through B1=0x12 |
| `cdk_devlist.def` | | Family mappings for A0-B1 |
| `cdk_config_chips.def` | | Build config |
| `cdk_config_phys.def` | | WARPcore PHY enabled |

### 5.1 How to Read `bcm56840_b0_defs.h`

This auto-generated header defines **every register and memory table**. Pattern:

```c
// Register address
#define REGISTER_NAMEr 0x00000XXX
#define REGISTER_NAMEr_SIZE N  // bytes

// Type union
typedef union REGISTER_NAMEr_s { uint32_t v[N/4]; ... } REGISTER_NAMEr_t;

// Whole-register access
#define REGISTER_NAMEr_CLR(r)      // zero
#define REGISTER_NAMEr_SET(r,d)    // set raw value
#define REGISTER_NAMEr_GET(r)      // get raw value

// Field access
#define REGISTER_NAMEr_FIELD_NAMEf_GET(r)      // extract field
#define REGISTER_NAMEr_FIELD_NAMEf_SET(r,f)    // set field

// I/O macros
#define READ_REGISTER_NAMEr(u,r)   // read from hardware
#define WRITE_REGISTER_NAMEr(u,r)  // write to hardware
```

### 5.2 Address Calculation

From `bcm56840_b0_chip.c`:
```c
uint32_t bcm56840_b0_blockport_addr(int block, int port, uint32_t offset) {
    if (block & 0x10) {      // block >= 16
        block &= 0xf;        // mask to low 4 bits
        block |= 0x400;      // set bit 10 for high blocks
    }
    return ((block * 0x100000) | (port * 0x1000) | (offset & ~0xf00000));
}
```

Address breakdown:
- **Block**: bits [23:20] (or [31:30]+[23:20] for blocks >= 16)
- **Port**: bits [15:12] (subport within block)
- **Register offset**: bits [11:0] (within port space)
- Each block: 1 MB address space
- Each port within block: 4 KB address space

---

## 6. Block Architecture and Port Mapping

### 6.1 Block Types

```c
const char *bcm56840_b0_blktype_names[] = {
    "cmic",         // type 0 - CPU Management Interface Controller
    "epipe",        // type 1 - Egress Pipeline
    "ipipe",        // type 2 - Ingress Pipeline
    "lbport",       // type 3 - Loopback Port
    "mmu",          // type 4 - Memory Management Unit
    "port_group4",  // type 5 - Port Group 4
    "port_group5",  // type 6 - Port Group 5
    "xlport"        // type 7 - XLPORT (10G/40G MAC blocks)
};
```

### 6.2 Physical Block Map (28 non-CMIC blocks)

From `bcm56840_b0_blocks[]`:

```
Block  Type         Blknum  Ports
-----  -----------  ------  -----------------------------------
0      LBPORT       28      Port 73 (loopback)
1      XLPORT       10      Ports 1-4   (XLPORT block 0)
2      XLPORT       11      Ports 5-8   (XLPORT block 1)
3      XLPORT       12      Ports 9-12  (XLPORT block 2)
4      XLPORT       13      Ports 13-16 (XLPORT block 3)
5      XLPORT       14      Ports 17-20 (XLPORT block 4)
6      XLPORT       15      Ports 21-24 (XLPORT block 5)
7      XLPORT       16      Ports 25-28 (XLPORT block 6)
8      XLPORT       17      Ports 29-32 (XLPORT block 7)
9      XLPORT       18      Ports 33-36 (XLPORT block 8)
10     XLPORT       19      Ports 37-40 (XLPORT block 9)
11     XLPORT       20      Ports 41-44 (XLPORT block 10)
12     XLPORT       21      Ports 45-48 (XLPORT block 11)
13     XLPORT       22      Ports 49-52 (XLPORT block 12) ← 40G/10G QSFP
14     XLPORT       23      Ports 57-60 (XLPORT block 13)
15     XLPORT       24      Ports 61-64 (XLPORT block 14)
16     XLPORT       25      Ports 65-68 (XLPORT block 15)
17     XLPORT       26      Ports 69-72 (XLPORT block 16) ← NOT ON AS5610
18     XLPORT       27      (empty - XLPORT block 17)
19     XLPORT       29      (empty)
20     XLPORT       30      (empty)
21     IPIPE        1       All data ports
22     EPIPE        2       All data ports
23     MMU          3       All data ports
24     PORT_GROUP4  6       Ports 21-36 + border
25     PORT_GROUP4  7       Ports 57-72 + border
26     PORT_GROUP5  8       Ports 1-20
27     PORT_GROUP5  9       Ports 37-56
```

### 6.3 Port Numbering

```c
#define NUM_PHYS_PORTS   74    // 0..73
#define NUM_LOGIC_PORTS  66
#define NUM_MMU_PORTS    66

#define CMIC_LPORT       0     // CPU port logical
#define CMIC_MPORT       0     // CPU port MMU
#define CMIC_HG_LPORT    66    // CPU HiGig logical port
#define LB_LPORT         65    // Loopback logical port
#define LB_MPORT         33    // Loopback MMU port
```

Port mapping macros:
```c
#define XLPORT_BLKIDX(port)  ((port - 1) >> 2)    // block index 0-17
#define XLPORT_SUBPORT(port) ((port - 1) & 0x3)    // lane 0-3 within block
#define P2L(unit, port)  bcm56840_a0_p2l(unit, port, 0)  // phys → logical
#define L2P(unit, port)  bcm56840_a0_p2l(unit, port, 1)  // logical → phys
#define P2M(unit, port)  bcm56840_a0_p2m(unit, port, 0)  // phys → MMU
#define M2P(unit, port)  bcm56840_a0_p2m(unit, port, 1)  // MMU → phys
```

### 6.4 AS5610-52X Port Layout

On the actual Edgecore AS5610-52X with BCM56846:
- **Ports 1-48**: 48x 1G SFP (copper/fiber) via XLPORT blocks in quad 1G mode
- **Ports 49-52**: 4x 40G/4x10G QSFP+ (XLPORT blocks 12-15, one port per block)
- **Port 0**: CPU port (CMIC)
- **Port 73**: Internal loopback
- **Ports 53-56**: Do not exist on this chip
- **Ports 57-72**: Additional XLPORT ports (available in hardware, not all wired on AS5610)

---

## 7. XGS Architecture Layer

All in `cdk/PKG/arch/xgs/`:

### 7.1 Core Files

| File | Purpose |
|------|---------|
| `xgs_chip.c` | Chip setup, CMIC init (endian, burst, interrupts) |
| `xgs_chip.h` | `cdk_xgs_chip_info_t` struct, block types, chip flags |
| `xgs_cmic.h` | **CMIC register definitions** (~1060 lines, auto-generated) |
| `xgs_schan.h` | SCHAN message types, header field macros, control bits |
| `xgs_schan.c` | `cdk_xgs_schan_op()` - execute SCHAN transaction |
| `xgs_setup.c` | Device setup entry point |

### 7.2 Chip Info Structure

```c
typedef struct cdk_xgs_chip_info_s {
    int cmic_block;                    // CMIC block number (5 for BCM56846)
    int nblktypes;                     // Number of block types (8)
    const char **blktype_names;        // Block type name strings
    cdk_xgs_blockport_addr_f blockport_addr;  // Address calc function
    int nblocks;                       // Non-CMIC blocks (28)
    cdk_xgs_block_t *blocks;           // Block definitions array
    cdk_pbmp_t valid_pbmps;            // Valid port bitmap
    uint32_t chip_flags;               // Feature flags
    // ... symbols, port map, numel info
} cdk_xgs_chip_info_t;
```

### 7.3 Chip Flags

```c
CDK_XGS_CHIP_FLAG_CLAUSE45   // Use Clause 45 MDIO for PHY access
CDK_XGS_CHIP_FLAG_SCHAN_EXT  // SCHAN message buffer at offset 0x800
CDK_XGS_CHIP_FLAG_SCHAN_SB0  // Source block = 0 in SCHAN header
CDK_XGS_CHIP_FLAG_SCHAN_MBI  // Modified block/index mode (NOT on BCM56846)

BCM56840_B0_CHIP_FLAG_BW640G // 640 Gbps bandwidth mode (BCM56846 unique)
BCM56840_A0_CHIP_FLAG_BW320G // 320 Gbps mode
BCM56840_A0_CHIP_FLAG_HGONLY // HiGig-only ports
```

### 7.4 Register Access Files

| File | Purpose |
|------|---------|
| `xgs_reg.h` / `xgs_reg.c` | Core register access via SCHAN |
| `xgs_reg32_read.c` | 32-bit register read |
| `xgs_reg32_write.c` | 32-bit register write |
| `xgs_reg32_port_read.c` / `_write.c` | Port-indexed 32-bit access |
| `xgs_reg32_block_read.c` / `_write.c` | Block-indexed 32-bit access |
| `xgs_reg32_blockport_read.c` / `_write.c` | Block+port indexed access |
| `xgs_reg32_blocks_read.c` / `_write.c` | All blocks of a type |
| `xgs_reg64_*.c` | Same patterns for 64-bit registers |
| `xgs_reg_port_read.c` / `_write.c` | Variable-width port access |
| `xgs_reg_block_read.c` / `_write.c` | Variable-width block access |

### 7.5 Memory Table Access Files

| File | Purpose |
|------|---------|
| `xgs_mem.h` / `xgs_mem.c` | Core memory access via SCHAN |
| `xgs_mem_block_read.c` / `_write.c` / `_clear.c` | Block-specific memory |
| `xgs_mem_blocks_read.c` / `_write.c` | Multi-block memory |
| `xgs_mem_clear.c` | Clear entire memory table |
| `xgs_mem_maxidx.c` | Get max index for a memory |
| `xgs_mem_op.c` | Table operations: INSERT, DELETE, LOOKUP, PUSH, POP |

### 7.6 Block/Port Mapping Files

| File | Purpose |
|------|---------|
| `xgs_block.c` | Block type lookup |
| `xgs_block_addr.c` | Block address calculation |
| `xgs_block_number.c` | Block number lookup |
| `xgs_block_pbmp.c` | Block port bitmap |
| `xgs_block_type.c` | Block type from number |
| `xgs_blockport_addr.c` | Combined block+port address |
| `xgs_port_addr.c` | Port address calculation |
| `xgs_port_block.c` | Port-to-block mapping |
| `xgs_port_number.c` | Port numbering |

### 7.7 XGSD and XGSM (Not Used by BCM56846)

For reference, OpenMDK contains two other XGS architecture variants:

- **XGSD** (`cdk/PKG/arch/xgsd/`): Uses SBUSv4 with address extension (`adext`).
  Block/access-type encoded separately. Used by newer chips (Memory, Memory+).
- **XGSM** (`cdk/PKG/arch/xgsm/`): Additional memory management features.

BCM56846 uses plain **XGS** (no D/M suffix).

---

## 8. CMIC Register Definitions

### 8.1 From `xgs_cmic.h` (Shared Across All XGS Chips)

| Register | Offset | Description |
|----------|--------|-------------|
| `CMIC_CONFIGr` | 0x010C | Main config: CPS reset, SCHAN abort, DMA enables |
| `CMIC_SCHAN_CTRLr` | 0x0050 | SCHAN control: start/done/abort/NAK/timeout bits |
| `CMIC_SCHAN_ERRr` | 0x005C | SCHAN error details |
| `CMIC_IRQ_STATr` | varies | Interrupt status including SCHAN_ERR |
| `CMIC_IRQ_MASKr` | varies | Interrupt mask |
| `CMIC_ENDIANESS_SELr` | varies | Endian configuration |
| `CMIC_DMA_CTRLr` | varies | DMA channel direction |
| `CMIC_DMA_STATr` | varies | DMA status |
| `CMIC_DMA_DESC0r` | varies | DMA descriptor base (+ 4*chan) |
| `CMIC_MIIM_PARAMr` | 0x0158 | MIIM parameters (PHY addr, register) |
| `CMIC_MIIM_ADDRESSr` | 0x04A0 | Clause 45 register address |
| `CMIC_MIIM_READ_DATAr` | 0x015C | MIIM read data return |

### 8.2 CMIC_CONFIG Fields (0x010C)

- bit 0: `RD_BRST_EN` - PIO read burst enable
- bit 1: `WR_BRST_EN` - PIO write burst enable
- bit 5: `RESET_CPS` - Drive CPS-Channel reset
- bit 6: `ACT_LOW_INT` - Active-low interrupt
- bit 7: `SCHAN_ABORT` - Abort pending SCHAN operation
- bit 11: `LE_DMA_EN` - Little-endian DMA
- bit 12: `I2C_EN` - I2C access enable
- bit 29: `OVER_RIDE_EXT_MDIO_MSTR_CNTRL` - CMIC as MDIO master

### 8.3 Chip-Specific (from `bcm56840_b0_defs.h`)

| Register | Offset | Description |
|----------|--------|-------------|
| `CMIC_MISC_CONTROLr` | 0x0860 | PLL power down, MDIO select, PLL load |

### 8.4 Hardware-Discovered Registers (NOT in OpenMDK)

| Offset | Our Name | Notes |
|--------|----------|-------|
| 0x01C | MISC_CONTROL | bit 0 = LINK40G_ENABLE |
| 0x178 | DEV_REV_ID | Reads 0x0002B846 |
| 0x204-0x210 | CMIC_SBUS_RING_MAP_0..3 | Found via probing |
| 0x580 | CMIC_SOFT_RESET_REG | Found via RE |
| 0x57C | CMIC_SOFT_RESET_REG_2 | Found via RE |

---

## 9. SCHAN (S-Channel) Protocol

### 9.1 Files

- **Types/header**: `cdk/PKG/arch/xgs/xgs_schan.h`
- **Implementation**: `cdk/PKG/arch/xgs/xgs_schan.c`

### 9.2 Message Buffer

22 x 32-bit words (`CMIC_SCHAN_WORDS_ALLOC = 22`).

For BCM56846 with `CDK_XGS_CHIP_FLAG_SCHAN_EXT`, the message buffer is at
**BAR0 + 0x0800**. Without this flag it would be at 0x0000.

**NOTE**: Hardware testing confirmed 0x0800 is an alias of 0x0000 (CMIC
space repeats every 2KB). Both addresses work.

### 9.3 SCHAN Header Format (32-bit word)

```
Bits [31:26] = opcode   (6 bits)  - SCMH_OPCODE_GET/SET
Bits [25:20] = dstblk   (6 bits)  - SCMH_DSTBLK_GET/SET
Bits [19:14] = srcblk   (6 bits)  - SCMH_SRCBLK_GET/SET
Bits [13:7]  = datalen  (7 bits)  - SCMH_DATALEN_GET/SET
Bit  [6]     = ebit     (1 bit)   - SCMH_EBIT_GET/SET (error indicator)
Bits [5:4]   = ecode    (2 bits)  - SCMH_ECODE_GET/SET (error code)
Bits [3:1]   = cos      (3 bits)  - SCMH_COS_GET/SET (class of service)
Bit  [0]     = cpu      (1 bit)   - SCMH_CPU_GET/SET
```

### 9.4 SCHAN Opcodes

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

### 9.5 SCHAN Control Bits (CMICe Byte-Write at 0x0050)

```c
SC_MSG_START_SET   = 0x80|0   // Write byte to start SCHAN operation
SC_MSG_START_CLR   = 0x00|0   // Clear start bit
SC_MSG_DONE_TST    = 0x00000002  // Test done (read as 32-bit)
SC_MSG_DONE_CLR    = 0x00|1     // Clear done (write byte)
SC_MSG_NAK_TST     = 0x00200000 // Test NAK (bit 21)
SC_MSG_TIMEOUT_TST = 0x00400000 // Test timeout (bit 22)

// MIIM control (also in SCHAN_CTRL)
SC_MIIM_RD_START_SET = 0x80|16  // Trigger MIIM read
SC_MIIM_WR_START_SET = 0x80|17  // Trigger MIIM write
SC_MIIM_OP_DONE_TST  = 0x00040000  // MIIM operation done (bit 18)
```

### 9.6 SCHAN Operation Flow (`cdk_xgs_schan_op`)

```
1. Determine msg_addr (0x800 for SCHAN_EXT, else 0x000)
2. Write message words to msg_addr + i*4
3. Write SC_MSG_START_SET (0x80) to CMIC_SCHAN_CTRLr (0x50)
4. Poll CMIC_SCHAN_CTRLr for SC_MSG_DONE_TST (bit 1)
5. Check for NAK (bit 21), timeout (bit 22), SCHAN_ERR
6. Write SC_MSG_DONE_CLR to CMIC_SCHAN_CTRLr
7. Read response words from msg_addr + i*4
8. On error: toggle SCHAN_ABORT in CMIC_CONFIG (0x10C bit 7)
```

### 9.7 SCHAN Message Types (C Structs)

| Type | Struct | Fields |
|------|--------|--------|
| Read command | `schan_msg_readcmd_t` | header + address |
| Read response | `schan_msg_readresp_t` | header + data[21] |
| Write command | `schan_msg_writecmd_t` | header + address + data[20] |
| Generic table cmd | `schan_msg_gencmd_t` | header + address + data[20] |
| Generic table resp | `schan_msg_genresp_t` | header + response + data[20] |
| L2X2 cmd | `schan_msg_l2x2_t` | header + data[3] |
| L3X2 cmd | `schan_msg_l3x2_t` | header + data[13] |
| Pop cmd | `schan_msg_popcmd_t` | header + address |
| Push cmd | `schan_msg_pushcmd_t` | header + address + data[20] |

### 9.8 Generic Table Response Codes

```c
SCGR_TYPE_FOUND      = 0
SCGR_TYPE_NOT_FOUND  = 1
SCGR_TYPE_FULL       = 2
SCGR_TYPE_INSERTED   = 3
SCGR_TYPE_REPLACED   = 4
SCGR_TYPE_DELETED    = 5
SCGR_TYPE_ENTRY_OLD  = 6
SCGR_TYPE_CLR_VALID  = 7
SCGR_TYPE_ERROR      = 15
```

---

## 10. Register and Memory Access

### 10.1 How Register Access Works

All register/memory reads and writes ultimately go through `cdk_xgs_schan_op()`.

**Register read flow**:
1. Build SCHAN header: opcode=0x0B (READ_REG), dstblk, srcblk (0 for BCM56846)
2. Set address word
3. Call `cdk_xgs_schan_op(unit, &msg, 2, dwc_read)`
4. Response opcode = 0x0C (READ_REG_ACK), data in `msg.readresp.data[]`

**Register write flow**:
1. Build SCHAN header: opcode=0x0D (WRITE_REG), dstblk, srcblk
2. Set address word + data words
3. Call `cdk_xgs_schan_op(unit, &msg, 2+dwc_data, 1)`
4. Response opcode = 0x0E (WRITE_REG_ACK)

### 10.2 Access Patterns

**Port-based** (most common for MAC/port registers):
```c
cdk_xgs_reg32_port_read(unit, port, addr, &val)
cdk_xgs_reg32_port_write(unit, port, addr, val)
```

**Block-based** (specific hardware block):
```c
cdk_xgs_reg32_block_read(unit, blkidx, addr, &val)
cdk_xgs_reg32_block_write(unit, blkidx, addr, val)
```

**Memory table** (L2, VLAN, etc.):
```c
cdk_xgs_mem_block_read(unit, blkidx, addr, index, data, size)
cdk_xgs_mem_block_write(unit, blkidx, addr, index, data, size)
cdk_xgs_mem_op(unit, &info)  // INSERT/DELETE/LOOKUP/PUSH/POP
```

### 10.3 Memory Operation Info Structure

```c
typedef struct cdk_xgs_mem_op_info_s {
    int mem_op;         // INSERT, DELETE, LOOKUP, PUSH, POP
    int size;           // Entry size in words
    uint32_t addr;      // Memory address
    uint32_t *data;     // Entry data
    uint32_t *key;      // Search key (for INSERT/DELETE/LOOKUP)
    uint32_t idx_min;   // Min index
    uint32_t idx_max;   // Max index
} cdk_xgs_mem_op_info_t;
```

---

## 11. XLPORT / XMAC MAC Layer

### 11.1 XLPORT Register Definitions

| Register | Address Pattern | Purpose |
|----------|----------------|---------|
| `XLPORT_MODE_REGr` | 0x00580229 | Port mode (core, PHY, MAC modes) |
| `XLPORT_PORT_ENABLEr` | 0x0058022a | Port enable (1 bit per subport 0-3) |
| `XLPORT_XMAC_CONTROLr` | 0x0058022b | XMAC reset control |
| `XLPORT_XGXS_CTRL_REGr` | 0x00580237 | SerDes/PHY control (power, PLL, reset) |
| `XLPORT_XGXS_STATUS_GEN_REGr` | 0x00580239 | SerDes status (PLL lock, sync) |
| `XLPORT_CONFIGr` | 0x00500200 | HiGig mode, flow control, PFC |
| `XLPORT_MIB_RESETr` | 0x00580240 | MIB counter reset |
| `XLPORT_WC_UCMEM_CTRLr` | 0x00580246 | WARPcore microcode memory control |
| `XLPORT_WC_UCMEM_DATAr` | 0x00580247 | WARPcore microcode memory data |

### 11.2 XLPORT_MODE_REG Fields

```
CORE_PORT_MODE [1:0]:
  0 = 40G mode (single port, 4 lanes)
  1 = 20G mode (dual port, 2 lanes each)
  2 = 10G/1G mode (quad port, 1 lane each)

PHY_PORT_MODE [3:2]:
  0 = 40G mode
  1 = 20G mode
  2 = 10G/1G mode (quad port)

PORT0_MAC_MODE [4]: 0=XMAC (10G+), 1=GigMAC (1G)
PORT1_MAC_MODE [5]: 0=XMAC, 1=GigMAC
PORT2_MAC_MODE [6]: 0=XMAC, 1=GigMAC
PORT3_MAC_MODE [7]: 0=XMAC, 1=GigMAC
```

### 11.3 XLPORT_XGXS_CTRL_REG Fields (SerDes Control)

```
PWRDWN_PLL [0]:       Power down PLL
PWRDWN [1]:           Power down SerDes
IDDQ [9]:             Deep power down (IDDQ mode)
PLLBYP [10]:          PLL bypass
LCREF_EN [11]:        Local clocking reference enable
RSTB_HW [12]:         Hardware reset (active low)
RSTB_PLL [13]:        PLL reset (active low)
RSTB_MDIOREGS [14]:   MDIO registers reset (active low)
TXD1G_FIFO_RSTB [15]: 1G Tx FIFO reset (active low)
TXD10G_FIFO_RSTB [16]: 10G Tx FIFO reset (active low)
```

### 11.4 XMAC Register Definitions

| Register | Purpose |
|----------|---------|
| `XMAC_CTRLr` | Soft reset, Tx/Rx enable, loopback, alignment |
| `XMAC_MODEr` | Header mode (IEEE/HiGig/HiGig2) |
| `XMAC_TX_CTRLr` | Tx IPG, CRC mode, padding |
| `XMAC_RX_CTRLr` | Strict preamble, CRC handling |
| `XMAC_RX_MAX_SIZEr` | Maximum receive frame size |
| `XMAC_TX_MAC_SAr` | Source MAC address |
| `XMAC_PAUSE_CTRLr` | Pause frame control |
| `XMAC_PFC_CTRLr` | Priority flow control |
| `XMAC_EEE_CTRLr` | Energy Efficient Ethernet |
| `XMAC_LLFC_CTRLr` | Link-level flow control |
| `XMAC_FIFO_STATUSr` | Tx/Rx FIFO status |

### 11.5 XMAC_CTRL Fields

```
SOFT_RESET [0]:         MAC software reset
TX_EN [1]:              Transmit enable
RX_EN [2]:              Receive enable
LINE_LOCAL_LPBK [3]:    MAC loopback
RX_LPBK [4]:            Receive loopback
XLGMII_ALIGN_ENB [5]:   XLGMII alignment enable (required for 40G)
RUNT_THRESHOLD [13:8]:  Runt frame threshold
STRIP_CRC [16]:         Strip CRC from Rx frames
TX_ADDR_INS_EN [17]:    Insert source MAC in Tx
```

### 11.6 GigMAC (UniMAC) for 1G Ports

For ports at 1G or below, the XLPORT block uses UniMAC instead of XMAC:

```c
COMMAND_CONFIG_SPEED_10   = 0x0
COMMAND_CONFIG_SPEED_100  = 0x1
COMMAND_CONFIG_SPEED_1000 = 0x2
COMMAND_CONFIG_SPEED_2500 = 0x3
```

Key register: `COMMAND_CONFIGr` - controls Rx/Tx enable, duplex, speed.

### 11.7 Port Speed to Mode Mapping

From `bcm56840_a0_bmd_port_mode_set.c`:

```
Speed > 20000:   CORE_PORT_MODE=0, PHY_PORT_MODE=0 (40G single-port)
Speed > 10000:   CORE_PORT_MODE=1, PHY_PORT_MODE=1 (20G dual-port)
Speed <= 10000:  CORE_PORT_MODE=2, PHY_PORT_MODE=2 (quad-port)

MAC mode:
  Speed > 2500:  mac_mode=0 (XMAC)
  Speed <= 2500: mac_mode=1 (GigMAC/UniMAC)
```

### 11.8 XLPORT Initialization Sequence

From `bcm56840_a0_bmd_init.c`:

```c
// 1. Get port bitmap
bcm56840_a0_xlport_pbmp_get(unit, &pbmp);

// 2. For each XLPORT block (at subport 0):
//    a. Read number of lanes per port
//    b. Set CORE_PORT_MODE and PHY_PORT_MODE
//    c. Set MAC_MODE per subport (XMAC vs GigMAC)
//    d. Write XLPORT_MODE_REGr
//    e. Enable ports in XLPORT_PORT_ENABLEr
//    f. Reset MIB counters via XLPORT_MIB_RESETr

// 3. For each port:
//    a. Initialize PORT_TABm and EGR_PORTm
//    b. If GigMAC: reset COMMAND_CONFIG, set speed/duplex
//    c. If XMAC: soft reset, configure Tx/Rx, set max frame size
```

### 11.9 XMAC Reset Sequence

```c
// Assert XMAC reset
XLPORT_XMAC_CONTROLr_XMAC_RESETf_SET(xlport_ctrl, 1);
WRITE_XLPORT_XMAC_CONTROLr(unit, xlport_ctrl, port);
BMD_SYS_USLEEP(1000);

// Deassert XMAC reset
XLPORT_XMAC_CONTROLr_XMAC_RESETf_SET(xlport_ctrl, 0);
WRITE_XLPORT_XMAC_CONTROLr(unit, xlport_ctrl, port);
BMD_SYS_USLEEP(1000);

// Configure XMAC
XMAC_CTRLr_SOFT_RESETf_SET(mac_ctrl, 1);
WRITE_XMAC_CTRLr(unit, port, mac_ctrl);
XMAC_CTRLr_SOFT_RESETf_SET(mac_ctrl, 0);
XMAC_CTRLr_TX_ENf_SET(mac_ctrl, 1);
if (speed == 40000) XMAC_CTRLr_XLGMII_ALIGN_ENBf_SET(mac_ctrl, 1);
WRITE_XMAC_CTRLr(unit, port, mac_ctrl);

// Set Tx parameters
XMAC_TX_CTRLr_PAD_THRESHOLDf_SET(txctrl, 0x40);
XMAC_TX_CTRLr_AVERAGE_IPGf_SET(txctrl, 0xc);
XMAC_TX_CTRLr_CRC_MODEf_SET(txctrl, 0x2);

// Set Rx parameters
XMAC_RX_CTRLr_STRICT_PREAMBLEf_SET(rxctrl, 1);
XMAC_RX_MAX_SIZEr_RX_MAX_SIZEf_SET(rxmaxsz, JUMBO_MAXSZ);
```

### 11.10 HiGig Mode Configuration

```c
// XMAC_MODE header mode: 0=IEEE, 1=HiGig, 2=HiGig2
XMAC_MODEr_HDR_MODEf_SET(xmac_mode, hg2 ? 2 : hg);

// XLPORT config
XLPORT_CONFIGr_HIGIG_MODEf_SET(xlport_cfg, hg);
XLPORT_CONFIGr_HIGIG2_MODEf_SET(xlport_cfg, hg2);

// Port table
PORT_TABm_PORT_TYPEf_SET(port_tab, hg);
PORT_TABm_HIGIG2f_SET(port_tab, hg2);
```

---

## 12. WARPcore XGXS PHY Driver

### 12.1 Files

At `phy/PKG/chip/bcmi_warpcore_xgxs/`:

| File | Size | Purpose |
|------|------|---------|
| `bcmi_warpcore_xgxs_drv.c` | 73 KB | Main driver: init, speed, link, autoneg, loopback |
| `bcmi_warpcore_xgxs_defs.h` | 4.9 MB | Register/field definitions for WARPcore |
| `bcmi_warpcore_xgxs_firmware_set.c` | 5.5 KB | Firmware download via MDIO serial |
| `bcmi_warpcore_xgxs_firmware_set.h` | 32 lines | FW function declarations |
| `bcmi_warpcore_xgxs_ucode.c` | 164 KB | Firmware binary (A0 silicon) |
| `bcmi_warpcore_xgxs_ucode_b0.c` | 186 KB | Firmware binary (B0 silicon, v0x0101) |
| `bcmi_warpcore_xgxs_sym.c` | 726 KB | Symbol table |

### 12.2 PHY Identification

- **Serdes ID**: 0x09 (`SERDES_ID0_XGXS_WARPCORE`)
- **PHY ID0**: 0x143
- **PHY ID1**: 0xbff0
- **Device ID**: 0x0707 (WC-B0)
- **Rev**: 0xbcbc

### 12.3 Supported Speeds

**Actual speed register values (FV_adr_\*)**:
```
10M, 100M, 1G, 2.5G, 5G, 10G (CX4, KX4, KR, XFI, SFI, HiG),
12G, 12.5G, 13G, 15G, 16G, 20G, 21G, 25G, 31.5G, 40G (KR4, CR4)
```

**Forced speed register values (FV_fdr_\*)**:
```
FV_fdr_10G_SFI = 0x29   (MISC1[4:0]=0x09 + MISC3.FORCE_SPEED_B5=1)
```

### 12.4 Lane Modes

- **1-lane**: Single SerDes lane, up to 10G (IS_1LANE_PORT)
- **2-lane**: Dual DXGXS, 10G-20G range (IS_2LANE_PORT)
- **4-lane**: Full quad, up to 40G (IS_4LANE_PORT)

### 12.5 Initialization Stages

**Stage 0 (`_warpcore_init_stage_0`)**:
1. Stop PLL sequencer (CL45 PMA 0x8000 bit 13)
2. Initialize Tx FIR (CL72_DEBUG_4)
3. Configure VCO frequency based on port mode
4. Handle errata (CL48 sync, MDIO override)
5. Disable 1000X and 10G parallel detect
6. Configure txck/rxck clocking
7. **Load firmware via MDIO serial** (`bcmi_warpcore_xgxs_firmware_set()`)
8. Restart PLL sequencer

**Stage 1 (`_warpcore_init_stage_1`)**:
- Check firmware CRC (optional)
- Verify FW_VERSION register

**Stage 2 (`_warpcore_init_stage_2`)**:
- Configure 64B/66B sync patterns (RX66_SCW0-3)
- Configure 1000X control
- Configure unicore mode
- Configure 40-bit interface mode

### 12.6 Firmware Download Flow

From `bcmi_warpcore_xgxs_firmware_set()`:

```
1. COMMAND.INIT_CMD = 1           // Initialize RAM
2. Wait for DOWNLOAD_STATUS.INIT_DONE (200ms timeout)
3. COMMAND2.TMR_EN = 1            // Enable uC timers
4. RAMWORD = fw_size - 1          // Transfer size (16-byte aligned)
5. ADDRESS = offset               // Starting RAM location
6. COMMAND = {WRITE=1, RUN=1}     // Start write operation
7. Write fw_data via WRDATA       // 16-bit words, ~15K MIIM writes
8. COMMAND.STOP = 1               // Complete write operation
9. Check DOWNLOAD_STATUS (ERR0/ERR1)
10. CRC = WARPCORE_CRC_DISABLE    // Disable CRC check
11. COMMAND.MDIO_UC_RESET_N = 1   // Release uC from reset
```

**Key registers**:
- `COMMAND` (0xFFC2): INIT_CMD, WRITE, READ, STOP, RUN, MDIO_UC_RESET_N
- `WRDATA` (0xFFC3): Firmware data write
- `DOWNLOAD_STATUS` (0xFFC4/0xFFC5): INIT_DONE, ERR0, ERR1
- `VERSION` (0x81F0): Firmware version readback
- `FW_ALIGN_BYTES` = 16

### 12.7 Key WARPcore Registers

From `bcmi_warpcore_xgxs_defs.h`:

| Register | Address | Purpose |
|----------|---------|---------|
| UC_CTRL | 0x820E | GP_UC_REQ, READY_FOR_CMD, SUPPLEMENT_INFO |
| MISC1 | 0x8308 | FORCE_SPEED[4:0], FORCE_PLL_MODE_AFE |
| MISC3 | 0x833C | FORCE_SPEED_B5, LANEDISABLE |
| MISC6 | 0x8345 | Lane release |
| XGXSSTATUS4 | 0x8104 | ACTUAL_SPEED per lane |
| COMBO_MII_CTRL | 0xFFE0 | IEEE reset (bit 15 - DESTRUCTIVE) |
| LANEPRBS | 0x8015 | PRBS config (must clear on init) |
| CL49_CONTROL1 | varies | HiGig2 bits (must clear for standard 10G) |
| ANARXCONTROL | varies | SIGDET override (bits 9:8) |

### 12.8 Driver API

```c
bcmi_warpcore_xgxs_probe()        // Identify PHY
bcmi_warpcore_xgxs_init()         // Initialize (staged)
bcmi_warpcore_xgxs_link_get()     // Link status
bcmi_warpcore_xgxs_speed_set()    // Force speed
bcmi_warpcore_xgxs_speed_get()    // Read current speed
bcmi_warpcore_xgxs_ability_get()  // Report capabilities
bcmi_warpcore_xgxs_autoneg_set()  // Auto-negotiation
bcmi_warpcore_xgxs_autoneg_get()
bcmi_warpcore_xgxs_loopback_set() // Loopback control
bcmi_warpcore_xgxs_loopback_get()
bcmi_warpcore_xgxs_duplex_set()
bcmi_warpcore_xgxs_duplex_get()
bcmi_warpcore_xgxs_firmware_set()  // FW download
bcmi_warpcore_xgxs_firmware_check() // FW verify
```

---

## 13. MIIM (MDIO) PHY Access

### 13.1 Files

| File | Purpose |
|------|---------|
| `cdk/PKG/arch/xgs/xgs_miim.h` | MIIM declarations, bus selection macros |
| `cdk/PKG/arch/xgs/xgs_miim.c` | Clause 22/45 PHY read/write |
| `cdk/PKG/arch/xgs/xgs_miim_iblk_read.c` | Internal block MIIM read (SerDes) |
| `cdk/PKG/arch/xgs/xgs_miim_iblk_write.c` | Internal block MIIM write |
| `phy/PKG/bus/bcm56840_miim_int/` | Internal MIIM bus driver for BCM56840 |

### 13.2 MIIM Bus Selection Macros

```c
CDK_XGS_MIIM_INTERNAL    // Select internal SerDes MII bus
CDK_XGS_MIIM_BUS_1       // External MIIM bus #1
CDK_XGS_MIIM_BUS_2       // External MIIM bus #2
CDK_XGS_MIIM_CLAUSE45    // Use Clause 45 access method
CDK_XGS_MIIM_EBUS(n)     // External bus shorthand
```

### 13.3 Core Functions

```c
cdk_xgs_miim_read(int unit, uint32_t phy_addr, uint32_t reg, uint32_t *val)
cdk_xgs_miim_write(int unit, uint32_t phy_addr, uint32_t reg, uint32_t val)
cdk_xgs_miim_iblk_read(int unit, uint32_t phy_addr, uint32_t reg, uint32_t *val)
cdk_xgs_miim_iblk_write(int unit, uint32_t phy_addr, uint32_t reg, uint32_t val)
```

### 13.4 MIIM CMIC Registers

| Register | Offset | Purpose |
|----------|--------|---------|
| `CMIC_MIIM_PARAMr` | 0x0158 | PHY address + register (CL22) |
| `CMIC_MIIM_ADDRESSr` | 0x04A0 | CL45 register address |
| `CMIC_MIIM_READ_DATAr` | 0x015C | Read data return |
| `CMIC_SCHAN_CTRLr` | 0x0050 | Trigger/poll MIIM (via SC_MIIM_xx bits) |

### 13.5 Access Method for WARPcore

WARPcore uses AER (Address Extension Register) IBLK access:
```c
// Register 0x1F selects the block for indirect access
// CL22 reg 13 = devad, reg 14 = addr (CL45 indirect)

phy_aer_iblk_read()   // Internal block read
phy_aer_iblk_write()  // Internal block write

// Lane-specific access:
READ_<REG>r(pc, &reg)           // Read current lane
READLN_<REG>r(pc, lane, &reg)   // Read specific lane
WRITEALL_<REG>r(pc, reg)        // Write all lanes
```

### 13.6 PHY Address Mapping (BCM56840 Reset Code)

```c
ports 1-24:  phy_addr = port + MIIM_IBUS(0)      // MDIO bus 0
ports 25-48: phy_addr = (port-24) + MIIM_IBUS(1)  // MDIO bus 1
ports 49+:   phy_addr = (port-48) + MIIM_IBUS(2)  // MDIO bus 2
```

---

## 14. BMD Driver Layer

### 14.1 Chip-Specific BMD

BCM56846 has **no** chip-specific BMD directory. It inherits everything from
BCM56840.

**`bmd/PKG/chip/bcm56840_a0/`** (34 files, all implementations):

| File | Size | Purpose |
|------|------|---------|
| `bcm56840_a0_bmd_attach.c` | 19KB | Device init, PHY bus, port properties |
| `bcm56840_a0_bmd_reset.c` | 25KB | Chip reset: CPS, PLL, xport/WARPcore init |
| `bcm56840_a0_bmd_init.c` | 74KB | Full chip init: MMU, ports, VLANs, MAC, EPC |
| `bcm56840_a0_bmd_port_mode_set.c` | 15KB | Set port speed/duplex/loopback |
| `bcm56840_a0_bmd_port_mode_get.c` | | Get current port mode |
| `bcm56840_a0_bmd_port_mode_update.c` | | Update after mode change |
| `bcm56840_a0_bmd_port_vlan_set.c` | | Set port default VLAN |
| `bcm56840_a0_bmd_port_vlan_get.c` | | Get port default VLAN |
| `bcm56840_a0_bmd_port_stp_set.c` | | Set STP state |
| `bcm56840_a0_bmd_port_stp_get.c` | | Get STP state |
| `bcm56840_a0_bmd_vlan_create.c` | | Create VLAN |
| `bcm56840_a0_bmd_vlan_destroy.c` | | Destroy VLAN |
| `bcm56840_a0_bmd_vlan_port_add.c` | | Add port to VLAN |
| `bcm56840_a0_bmd_vlan_port_get.c` | | Get ports in VLAN |
| `bcm56840_a0_bmd_vlan_port_remove.c` | | Remove port from VLAN |
| `bcm56840_a0_bmd_cpu_mac_addr_add.c` | | Add CPU MAC to L2 table |
| `bcm56840_a0_bmd_cpu_mac_addr_remove.c` | | Remove CPU MAC |
| `bcm56840_a0_bmd_port_mac_addr_add.c` | | Add MAC to port |
| `bcm56840_a0_bmd_port_mac_addr_remove.c` | | Remove MAC from port |
| `bcm56840_a0_bmd_stat_get.c` | | Get port statistics |
| `bcm56840_a0_bmd_stat_clear.c` | | Clear statistics |
| `bcm56840_a0_bmd_rx.c` | | Core RX implementation |
| `bcm56840_a0_bmd_rx_start.c` | | Start RX DMA |
| `bcm56840_a0_bmd_rx_stop.c` | | Stop RX DMA |
| `bcm56840_a0_bmd_rx_poll.c` | | Poll for received packets |
| `bcm56840_a0_bmd_tx.c` | | Transmit packet |
| `bcm56840_a0_bmd_switching_init.c` | | Initialize switching + EPC |
| `bcm56840_a0_bmd_download.c` | | Download firmware |
| `bcm56840_a0_bmd_detach.c` | | Detach device |
| `bcm56840_a0_internal.h` | | Internal macros, constants |

**`bmd/PKG/chip/bcm56840_b0/`** (thin wrappers, 30 files):
Each `bcm56840_b0_bmd_*.c` simply calls the corresponding `bcm56840_a0_bmd_*()`.

### 14.2 Key Reset Sequence (`bcm56840_a0_bmd_reset.c`)

**WARPcore PHY init** (`bcm56840_a0_warpcore_phy_init`):
1. Enable multi-MMD mode (CL22 reg 0x1f=0x8000, 0x1d)
2. Stop sequencer (CL45 PMA 0x8000 bit 13)
3. Set independent lane mode for speeds <= 20G
4. Enable broadcast (CL45 PMA 0xffde = 0x01ff)
5. Configure speed advertisements per port type
6. Set reference clock (156.25 MHz or 161.25 MHz)
7. Disable broadcast
8. Restart sequencer

**xport reset** (`bcm56840_a0_xport_reset`):
1. Configure MDIO device-in-package
2. Force into reset (IDDQ, PWRDWN, PWRDWN_PLL, RSTB_HW=0)
3. Power up (clear IDDQ, PWRDWN, PWRDWN_PLL)
4. Release HW reset (RSTB_HW=1)
5. Release MDIO reset (RSTB_MDIOREGS=1)
6. Release PLL reset (RSTB_PLL=1)
7. Wait for TX PLL lock (XGXS_STATUS_GEN_REG bit 12, 100ms timeout)
8. Release TX FIFO resets

### 14.3 Supported Port Modes

```c
bmdPortModeAuto       bmdPortModeDisabled
bmdPortMode10fd       bmdPortMode100fd
bmdPortMode1000fd     bmdPortMode2500fd
bmdPortMode10000fd    bmdPortMode10000XFI
bmdPortMode10000KR    bmdPortMode10000SFI
bmdPortMode20000fd    bmdPortMode40000fd
bmdPortMode40000KR    bmdPortMode40000CR
bmdPortMode12000fd    bmdPortMode13000fd  (HiGig)
bmdPortMode15000fd    bmdPortMode16000fd  (HiGig)
bmdPortMode30000fd                        (HiGig)
```

### 14.4 Port Speed Configuration

From `_port_speed_max()`:
```
config_speed    port configuration
-----------     -------------------
1000            1-lane, 1 Gbps max
2500            1-lane, 2.5 Gbps max
10000           1-lane, 10 Gbps max
10001           2-lane, 10 Gbps max
20000           2-lane, 20 Gbps max
20001           4-lane, 20 Gbps max
30000           4-lane, 30 Gbps max
40000           4-lane, 40 Gbps max
```

### 14.5 XGS Architecture BMD

At `bmd/PKG/arch/xgs/`:

| File | Purpose |
|------|---------|
| `xgs_dma.h` / `xgs_dma.c` | DMA engine init, TX/RX control |
| `xgs_mac_util.h` / `.c` | MAC utilities |
| `xgs_stp_xlate.c` | STP state translation |
| `xgs_led_prog.c` | LED programming |
| `xgs_led_update.c` | LED state update |

---

## 15. DMA Engine

### 15.1 Files

- `bmd/PKG/arch/xgs/xgs_dma.h`
- `bmd/PKG/arch/xgs/xgs_dma.c`

### 15.2 DMA Channels

- Channel 0: TX (Transmit)
- Channel 1: RX (Receive)
- Channels 2-3: Optional

### 15.3 Functions

```c
bmd_xgs_dma_init(int unit)
bmd_xgs_dma_tx_start(int unit, dma_addr_t dcb)
bmd_xgs_dma_tx_poll(int unit, int num_polls)
bmd_xgs_dma_rx_start(int unit, dma_addr_t dcb)
bmd_xgs_dma_rx_poll(int unit, int num_polls)
bmd_xgs_dma_chan_init(int unit, int chan, int dir)
bmd_xgs_dma_chan_start(int unit, int chan, dma_addr_t dcb)
bmd_xgs_dma_chan_poll(int unit, int chan, int num_polls)
bmd_xgs_dma_chan_abort(int unit, int chan, int num_polls)
```

### 15.4 DMA Control Bits

```c
DS_DMA_ACTIVE(ch)      = 0x00040000 << ch  // DMA active status
DS_DMA_EN_SET(ch)      = 0x80|(ch)         // Enable DMA
DS_DMA_EN_CLR(ch)      = 0x00|(ch)         // Disable DMA
DS_CHAIN_DONE_SET(ch)  = 0x80|(4+ch)       // Clear chain done
DS_DESC_DONE_SET(ch)   = 0x80|(8+ch)       // Clear descriptor done
DC_ABORT_DMA(ch)       = 0x04 << (8*ch)    // Abort DMA
```

### 15.5 DMA Registers

```
CMIC_DMA_DESC0r + 4*chan:  DCB (Descriptor Control Block) address
CMIC_DMA_STATr:            Status/enable/completion flags
CMIC_DMA_CTRLr:            Channel direction (TX/RX)
```

**NOTE**: BCM56846 uses CMICe at 0x100 (NOT CMICm at 0x31xxx).

---

## 16. Board Configuration

### 16.1 BCM56846 SVK Board

At `board/config/board_bcm56846_svk.c`:

**Port configuration**: 56 x 10G ports + additional HiGig ports
```c
static cdk_port_config_t _port_configs[] = {
    // 56 entries, all 10000 Mbps
    // sys_port 1-56 mapped to app_port 9-68
};
```

**PHY address mapping**:
```c
_phy_addr(int port):
    port > 60:  (port - 41) + MIIM_EBUS(2)
    port > 56:  (port - 44) + MIIM_EBUS(2)
    port > 40:  (port - 40) + MIIM_EBUS(2)
    port > 24:  (port - 24) + MIIM_EBUS(1)
    default:    (port - 8) + MIIM_EBUS(0)
```

**PHY instance**: `_phy_inst(port) = (port - 1) & 3` (lane within quad)

**WARPcore Rx lane remapping**:
```c
Port 45: rx_map = 0x3210  (no remap)
Others:  rx_map = 0x1032  (swap lane pairs)
```

**Dynamic config**: `DCFG_LCPLL_156` (156.25 MHz reference clock)

**PHY bus stack**: Internal MIIM (`bcm56840_miim_int`) + external MIIM

**LED firmware**: `sdk56840_ledprog_info` from `board/xgsled/sdk56840.c`

### 16.2 Related Board Files

| File | Description |
|------|-------------|
| `board_bcm56845_svk.c` | BCM56845 SVK ("also works with BCM56846") |
| `board_bcm56844_ext.c` | BCM56844 Trident+ variant |
| `board_bcm56845_ext.c` | BCM56845 with external PHY |
| `board_config_map_sjlab.c` | Maps `rack40_08` to `board_bcm56846_svk` |

---

## 17. Build Configuration

### 17.1 Required Config Defines

From `cdk/PKG/chip/bcm56846/cdk_config_chips.def`:
```c
CDK_CONFIG_INCLUDE_BCM56846_A0 = 1  // (or A1)
CDK_CONFIG_INCLUDE_BCM56840_B0 = 1  // required dependency (auto-set)
```

From `cdk/PKG/chip/bcm56846/cdk_config_phys.def`:
```c
PHY_CONFIG_INCLUDE_BCMI_WARPCORE_XGXS = 1
```

### 17.2 Architecture Conditional

```c
#ifdef CDK_CONFIG_ARCH_XGS_INSTALLED
// All XGS-specific code
#endif
```

### 17.3 Chip Include Pattern

```c
#include <cdk/chip/bcm56840_b0_defs.h>  // register definitions
#include <cdk/arch/xgs_chip.h>           // architecture types
#include <cdk/arch/xgs_miim.h>           // MIIM access
#include <cdk/arch/xgs_schan.h>          // SCHAN protocol
```

---

## 18. Key Register Address Cross-Reference

### CMIC Core (from xgs_cmic.h)

| OpenMDK Name | Offset | Our Usage |
|--------------|--------|-----------|
| `CMIC_SCHAN_CTRLr` | 0x0050 | SCHAN + MIIM control |
| `CMIC_SCHAN_ERRr` | 0x005C | SCHAN error details |
| `CMIC_CONFIGr` | 0x010C | CPS reset, SCHAN abort |
| `CMIC_MIIM_PARAMr` | 0x0158 | MIIM PHY/register params |
| `CMIC_MIIM_READ_DATAr` | 0x015C | MIIM read data |
| `CMIC_MIIM_ADDRESSr` | 0x04A0 | CL45 register address |

### SCHAN Message Buffer

| Concept | Offset | Notes |
|---------|--------|-------|
| msg_addr (SCHAN_EXT) | 0x0800 | BCM56846 uses this |
| msg_addr (standard) | 0x0000 | Alias of 0x0800 (2KB wrap) |
| SCHAN_D(0)..D(21) | msg_addr + 0..0x54 | 22 x 32-bit words |

### Chip-Specific (from bcm56840_b0_defs.h)

| OpenMDK Name | Offset | Description |
|--------------|--------|-------------|
| `CMIC_MISC_CONTROLr` | 0x0860 | PLL power down, MDIO select |
| `XLPORT_MODE_REGr` | 0x00580229 | Port mode config |
| `XLPORT_PORT_ENABLEr` | 0x0058022a | Port enable |
| `XLPORT_XMAC_CONTROLr` | 0x0058022b | XMAC reset |
| `XLPORT_XGXS_CTRL_REGr` | 0x00580237 | SerDes control |
| `CMIC_SOFT_RESET_REGr` | (from defs) | Chip soft reset |

### Hardware-Discovered (NOT in OpenMDK)

| Offset | Our Name | Notes |
|--------|----------|-------|
| 0x01C | MISC_CONTROL | bit 0 = LINK40G_ENABLE |
| 0x178 | DEV_REV_ID | Reads 0x0002B846 |
| 0x204-0x210 | CMIC_SBUS_RING_MAP_0..3 | Found via probing |
| 0x580 | CMIC_SOFT_RESET_REG | Found via RE |
| 0x57C | CMIC_SOFT_RESET_REG_2 | Found via RE |

---

## 19. Quick Lookup Table

| Want to... | Look at... |
|------------|------------|
| Read/write a register | `cdk/PKG/arch/xgs/xgs_reg32_*.c` → `xgs_schan.c` |
| Read/write a memory table | `cdk/PKG/arch/xgs/xgs_mem_*.c` |
| Find a register address | `cdk/PKG/chip/bcm56840/bcm56840_b0_defs.h` |
| Find a CMIC register | `cdk/PKG/arch/xgs/xgs_cmic.h` |
| Do SCHAN transaction | `cdk/PKG/arch/xgs/xgs_schan.c` |
| Init the chip | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_init.c` |
| Reset the chip | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_reset.c` |
| Set port speed/mode | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_port_mode_set.c` |
| Configure WARPcore PHY | `phy/PKG/chip/bcmi_warpcore_xgxs/bcmi_warpcore_xgxs_drv.c` |
| Download WARPcore FW | `phy/PKG/chip/bcmi_warpcore_xgxs/bcmi_warpcore_xgxs_firmware_set.c` |
| Access PHY via MDIO | `cdk/PKG/arch/xgs/xgs_miim.c` |
| Set up VLAN | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_vlan_*.c` |
| Send/receive packets | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_tx.c` / `_rx*.c` |
| Board port mapping | `board/config/board_bcm56846_svk.c` |
| LED programming | `board/xgsled/sdk56840.c` |
| Get chip device ID | `cdk/PKG/chip/bcm56846/cdk_devids.def` |
| Understand SCHAN header | `cdk/PKG/arch/xgs/xgs_schan.h` |
| XLPORT/XMAC config | `bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_init.c` (XLPORT init section) |
| WARPcore register defs | `phy/PKG/chip/bcmi_warpcore_xgxs/bcmi_warpcore_xgxs_defs.h` |
| PCI/BAR access | `libbde/shared/shbde_pci.c` |
| Port-to-block mapping | `XLPORT_BLKIDX(port) = (port-1) >> 2` in `bcm56840_a0_internal.h` |
| DMA operations | `bmd/PKG/arch/xgs/xgs_dma.c` |

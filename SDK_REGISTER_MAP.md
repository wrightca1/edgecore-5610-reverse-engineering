# SDK Register Map and API Reference

**Date**: 2026-02-15  
**Sources**: OpenNSL 3.5.0.1 source code, switchd binary (Cumulus Linux 2.5.1)  
**ASIC**: Broadcom BCM56846 (Trident+)

## Overview

This document consolidates register mappings, packet I/O APIs, and table structures extracted from:
1. **OpenNSL source code** - Register definitions from SDK headers
2. **switchd binary** - Register offsets found via Ghidra reverse engineering
3. **OpenNSL headers** - Packet TX/RX API signatures and table structures

## Register Map

### CMIC (Common Microcontroller Interface) Registers

CMIC registers provide CPU-ASIC communication via S-Channel and interrupt handling.

#### Base Addresses

- **CMIC Base**: `0x08000000` (BCM_ICS_CMIC_BASE)
- **CMIC Register Space**: `0x00000000` - `0x00040000` (256KB)

**BDE source**: CMIC/CMICm/CMICd offsets are defined in `linux-user-bde.c`. See [`BDE_CMIC_REGISTERS.md`](./BDE_CMIC_REGISTERS.md).

#### CMIC Register Offsets

| Offset | Name | Description | Access |
|--------|------|-------------|--------|
| `0x00000144` | `CMIC_IRQ_STAT` | Interrupt status register | RO |
| `0x00000148` | `CMIC_IRQ_MASK` | Interrupt mask register | R/W |
| `0x0000006C` | `CMIC_IRQ_MASK_1` | Interrupt mask register 1 | R/W |
| `0x00000070` | `CMIC_IRQ_MASK_2` | Interrupt mask register 2 | R/W |
| `0x00000178` | `CMIC_DEV_REV_ID` | Device revision ID | RO |

#### CMIC CMC (Common Microcontroller Core) Registers

For CMICm/CMICd variants, CMC registers are accessed via offset macros:

```c
// CMC0 (x=0) base offset: 0x31400
// CMC1 (x=1) base offset: 0x32400
// CMC2 (x=2) base offset: 0x33400
// Each CMC has 0x1000 byte space

#define CMIC_CMCx_IRQ_STAT0_OFFSET(x)    (0x31400 + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT1_OFFSET(x)    (0x31404 + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT2_OFFSET(x)    (0x31408 + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT3_OFFSET(x)    (0x3140c + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT4_OFFSET(x)    (0x31410 + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT5_OFFSET(x)    (0x314b0 + (0x1000 * x))
#define CMIC_CMCx_IRQ_STAT6_OFFSET(x)    (0x314b4 + (0x1000 * x))

#define CMIC_CMCx_PCIE_IRQ_MASK0_OFFSET(x)  (0x31414 + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK1_OFFSET(x)  (0x31418 + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK2_OFFSET(x)  (0x3141c + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK3_OFFSET(x)  (0x31420 + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK4_OFFSET(x)  (0x31424 + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK5_OFFSET(x)  (0x314b8 + (0x1000 * x))
#define CMIC_CMCx_PCIE_IRQ_MASK6_OFFSET(x)  (0x314bc + (0x1000 * x))

#define CMIC_CMCx_UC0_IRQ_MASK0_OFFSET(x)   (0x31428 + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK1_OFFSET(x)   (0x3142c + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK2_OFFSET(x)   (0x31430 + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK3_OFFSET(x)   (0x31434 + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK4_OFFSET(x)   (0x31438 + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK5_OFFSET(x)   (0x314c0 + (0x1000 * x))
#define CMIC_CMCx_UC0_IRQ_MASK6_OFFSET(x)   (0x314c4 + (0x1000 * x))
```

**Example**: For CMC0 (x=0):
- `CMIC_CMC0_IRQ_STAT0` = `0x31400`
- `CMIC_CMC0_PCIE_IRQ_MASK0` = `0x31414`
- `CMIC_CMC0_UC0_IRQ_MASK0` = `0x31428`

#### S-Channel Registers

S-Channel (Service Channel) provides register access and control operations.

**Known S-Channel Register**:
- `CMIC_CMC0_SCHAN_CTRL` = `0x32800` (found in switchd binary analysis)

**S-Channel Operation**:
1. Write command to S-Channel command register
2. Poll status register for completion
3. Read result from data register

### LED Registers

| Offset | Name | Description |
|--------|------|-------------|
| `0x20000` | `OPENNSL_CMIC_LEDUP0_CTRL_OFFSET` | LED UP0 control |
| `0x20004` | `OPENNSL_CMIC_LEDUP0_STATUS_OFFSET` | LED UP0 status |
| `0x20400` | `OPENNSL_CMIC_LEDUP0_DATA_RAM_OFFSET` | LED UP0 data RAM |
| `0x20800` | `OPENNSL_CMIC_LEDUP0_PROGRAM_RAM_OFFSET` | LED UP0 program RAM |
| `0x21000` | `OPENNSL_CMIC_LEDUP1_CTRL_OFFSET` | LED UP1 control |
| `0x21004` | `OPENNSL_CMIC_LEDUP1_STATUS_OFFSET` | LED UP1 status |
| `0x21400` | `OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET` | LED UP1 data RAM |
| `0x21800` | `OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET` | LED UP1 program RAM |

### Register Access Patterns from switchd and libopennsl.so

From Ghidra analysis of both switchd binary and libopennsl.so library:

#### LED Registers Found (Confirmed)

| Offset | OpenNSL Match | Description |
|--------|---------------|-------------|
| `0x21000` | ✅ `OPENNSL_CMIC_LEDUP1_CTRL_OFFSET` | LED UP1 control register |
| `0x21400` | ✅ `OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET` | LED UP1 data RAM |
| `0x21800` | ✅ `OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET` | LED UP1 program RAM |

**Note**: These match OpenNSL definitions exactly, confirming the extraction method works.

#### Other Constants Found

- `0x20001`: LED-related constant
- `0x2625a`, `0x275e2`, `0x2dc6c`: Unknown constants (appear multiple times)
- `0x27fff`: Possibly a mask or limit value
- `0x1000ccc`, `0x1005e00`, `0x1112233`, `0x1120066`, `0x1120200`, `0x180c200`: Table memory addresses

#### CMIC/S-Channel Registers

- **Not found in data sections**: CMIC registers (0x31000-0x35000) and S-Channel registers (0x32000-0x33000) were not found as constants in switchd data sections
- **Possible reasons**:
  - Registers accessed via SDK function calls (not direct offsets)
  - Registers computed at runtime
  - Registers accessed via S-Channel (indirect access)
  - Register offsets stored in libopennsl.so, not switchd

### Table Memory Addresses (Major Finding!)

From libopennsl.so analysis, **20,176 table memory addresses** were found in the `0x1000000+` range!

**Key constraint**: for this target, extracted table-style addresses were entirely within:

- `0x01000000–0x01ffff20` (20,176 unique addresses)

See [`TABLE_MEMORY_MAP_FROM_OPENNSL.md`](./TABLE_MEMORY_MAP_FROM_OPENNSL.md) for the 1MB histogram and range details.
See [`TABLE_MEMORY_ANALYSIS.md`](./TABLE_MEMORY_ANALYSIS.md) for anchor addresses + xref plan to recover table names.
See [`FUNCTION_STRINGS_ANALYSIS.md`](./FUNCTION_STRINGS_ANALYSIS.md) for identified table names from string extraction.

#### Identified Table Addresses (from String Analysis)

| Address | Table Name | Functions Using It | Source |
|---------|------------|-------------------|--------|
| `0x01000000` | **CMIC UC Base** | `FUN_01905af8` | Region base, CMIC UC initialization |
| `0x0180c200` | **L2_USER_ENTRY** | `FUN_00948700`, `FUN_01cc2f2c` | String: `skip_L2_USER_ENTRY` |
| `0x01f00898` | **FP/ACL Table** | `FUN_008fb92c` | String: `FP(unit %d) Error: action=...` |
| `0x01855abc` | **A9JTAG Registers** | `FUN_00faf85c` | Strings: `A9JTAG_M0_IDM_*` |
| `0x01312d00` | **Hardware Control** | `FUN_01452b3c` | PTP, PLL, temperature registers |

#### Table Name Patterns Found in Binary

Direct string search in `libopennsl.so.1` found thousands of table name occurrences:

| Table Name | Occurrences | Description |
|-----------|-------------|------------|
| **L2_ENTRY** | 223 | L2 MAC address table |
| **L2_USER_ENTRY** | 107 | L2 user entry table (confirmed: `0x0180c200`) |
| **L3_DEFIP** | 394 | L3 Default IP (FIB/routing table) |
| **L3_ECMP** | 117 | L3 ECMP next-hop groups |
| **ECMP** | 532 | ECMP-related (broader pattern) |
| **VLAN_XLATE** | 350 | VLAN translation table |
| **VLAN** | 1,977 | VLAN-related (broader pattern) |
| **FP** | 4,858 | Field Processor (ACL/filtering) |
| **ACL** | 228 | Access Control List |
| **L3_HOST** | 2 | L3 host table |
| **L3_EGRESS** | 1 | L3 egress interface table |

**See**: [`TABLE_NAME_MAPPING.md`](./TABLE_NAME_MAPPING.md) for detailed analysis.

#### Table Name → Address Cross-Reference (from Ghidra)

Functions that reference both a table name string and table memory (0x01xxxxxx) give direct name→address links. Output: `build-server/opennsl/sdk-deep-extract/opennsl-table-name-to-addr-xref.txt`.

| Table Name    | Example table addresses (0x01xxxxxx) |
|---------------|--------------------------------------|
| **L3_DEFIP**  | 0x018124a8, 0x018dc3a0, 0x018dc3b0, 0x018dc430, 0x01f19a50 |
| **L3_ECMP**   | 0x0103bdc0, 0x01a15728, 0x01b16eec, 0x01b39158, … |
| **L2_ENTRY**  | 0x0137cd30, 0x01842c04, 0x01842c14, … (448+ in functions using "L2_ENTRY") |
| **L2_USER_ENTRY** | 0x0137cd30, 0x01408284, … (177+ in functions using "L2_USER_ENTRY") |
| **VLAN_XLATE**| 0x0137e2f0, 0x013d3a8c, … (114+ in functions using "VLAN_XLATE") |
| **ECMP**      | 0x0103136c, 0x01031888, … (671+ in functions using "ECMP") |

#### Table Memory Region Mapping

Based on address distribution and identified tables:

| Region | Size | Density | Likely Contents |
|--------|------|---------|----------------|
| `0x01000000-0x010fffff` | 1MB | 1405 addresses | CMIC UC, base tables |
| `0x01100000-0x011fffff` | 1MB | 905 addresses | Low-density tables |
| `0x01200000-0x012fffff` | 1MB | 1573 addresses | Medium-density tables |
| `0x01300000-0x013fffff` | 1MB | 884 addresses | Hardware control (PTP, PLL) |
| `0x01400000-0x014fffff` | 1MB | 1269 addresses | Medium-density tables |
| `0x01500000-0x015fffff` | 1MB | 1322 addresses | Medium-density tables |
| `0x01600000-0x016fffff` | 1MB | 718 addresses | Low-density tables |
| `0x01700000-0x017fffff` | 1MB | 953 addresses | Medium-density tables |
| `0x01800000-0x018fffff` | 1MB | 1435 addresses | **L2 tables** (L2_USER_ENTRY confirmed) |
| `0x01900000-0x019fffff` | 1MB | 397 addresses | Low-density tables |
| `0x01a00000-0x01afffff` | 1MB | 302 addresses | Low-density tables |
| `0x01b00000-0x01bfffff` | 1MB | 2051 addresses | **High-density** (likely L3/ECMP) |
| `0x01c00000-0x01cfffff` | 1MB | 2595 addresses | **Highest density** (likely major tables) |
| `0x01d00000-0x01dfffff` | 1MB | 887 addresses | Medium-density tables |
| `0x01e00000-0x01efffff` | 1MB | 1475 addresses | Medium-density tables |
| `0x01f00000-0x01ffffff` | 1MB | 2005 addresses | **FP/ACL tables** (confirmed) |

**Likely Purpose** (unconfirmed addresses):
- L2 table base addresses
- L3 table base addresses (DEFIP, host, route, egress)
- ECMP table addresses
- VLAN table addresses
- Buffer management addresses
- Statistics counter addresses

**See**: 
- [`REGISTER_EXTRACTION_RESULTS.md`](./REGISTER_EXTRACTION_RESULTS.md) - switchd extraction results
- [`OPENNSL_LIBRARY_EXTRACTION_RESULTS.md`](./OPENNSL_LIBRARY_EXTRACTION_RESULTS.md) - libopennsl.so extraction results
- [`REGISTER_EXTRACTION_SUMMARY.md`](./REGISTER_EXTRACTION_SUMMARY.md) - Complete analysis summary
- [`FUNCTION_STRINGS_ANALYSIS.md`](./FUNCTION_STRINGS_ANALYSIS.md) - Table name identification

## Packet TX/RX APIs

### Packet Transmit API

```c
/**
 * Transmit one or more packets
 * 
 * @param unit Unit number (typically 0 for single ASIC)
 * @param tx_pkt Packet structure containing data and metadata
 * @param cookie Application data returned with callback
 * 
 * @return OPENNSL_E_NONE on success
 * @return OPENNSL_E_UNIT Invalid device ID
 * @return OPENNSL_E_MEMORY Unable to allocate necessary structures
 * @return OPENNSL_E_PARAM Invalid parameters
 */
extern int opennsl_tx(
    int unit, 
    opennsl_pkt_t *tx_pkt, 
    void *cookie);
```

### Packet Receive API

```c
/**
 * Register callback for received packets
 * 
 * @param unit Unit number
 * @param name String identifier for reporting
 * @param callback Function pointer to be called on packet receive
 * @param priority Relative priority (0 is lowest)
 * @param cookie Application data passed to callback
 * @param flags RX callback flags (OPENNSL_RX_F_*)
 * 
 * @return OPENNSL_E_NONE on success
 */
extern int opennsl_rx_register(
    int unit,
    const char *name,
    opennsl_rx_cb_f callback,
    int priority,
    void *cookie,
    uint32 flags);

/**
 * Start packet reception
 * 
 * @param unit Unit number
 * @param cfg RX configuration (may be NULL for defaults)
 * 
 * @return OPENNSL_E_NONE on success
 */
extern int opennsl_rx_start(
    int unit, 
    opennsl_rx_cfg_t *cfg);

/**
 * Stop packet reception
 * 
 * @param unit Unit number
 * @param cfg Saved configuration state (may be NULL)
 * 
 * @return OPENNSL_E_NONE on success
 */
extern int opennsl_rx_stop(
    int unit, 
    opennsl_rx_cfg_t *cfg);
```

### Packet Structure

```c
struct opennsl_pkt_s {
    opennsl_pkt_blk_t *pkt_data;    // Pointer to array of data blocks
    uint8 blk_count;                // Number of blocks in data array
    uint8 unit;                     // Unit number
    uint8 cos;                      // COS queue to use
    opennsl_vlan_t vlan;            // 802.1q VID or VSI or VPN
    int16 src_port;                 // Source port used in header/tag
    uint16 dest_port;               // Destination port used in header/tag
    uint16 pkt_len;                 // Packet length according to flags
    uint16 tot_len;                 // Packet length as transmitted/received
    opennsl_pbmp_t tx_pbmp;         // Target ports
    opennsl_pbmp_t tx_upbmp;         // Untagged target ports
    uint32 rx_reason;               // Opcode from packet
    opennsl_rx_reasons_t rx_reasons; // Set of packet "reasons"
    uint8 rx_port;                  // Local rx port
    uint8 rx_untagged;              // Packet was untagged on ingress
    uint32 rx_matched;              // Field processor matched rule
    opennsl_pkt_cb_f call_back;    // Callback function
    uint32 flags;                   // OPENNSL_PKT_F_xxx flags
    opennsl_pkt_blk_t _pkt_data;    // For single block packets (internal)
    // ... additional fields ...
};

typedef struct opennsl_pkt_blk_s {
    uint8 *data;    // Pointer to packet data
    int len;        // Length of data block
} opennsl_pkt_blk_t;
```

### Packet Flags

```c
#define OPENNSL_PKT_F_NO_VTAG     0x4        // Packet does not contain VLAN tag
#define OPENNSL_TX_CRC_ALLOC       0x10       // Allocate buffer for CRC
#define OPENNSL_TX_CRC_REGEN       0x20       // Regenerate CRC
#define OPENNSL_TX_CRC_APPEND      (OPENNSL_TX_CRC_ALLOC + OPENNSL_TX_CRC_REGEN)
#define OPENNSL_TX_ETHER           0x100000   // Fully mapped packet TX
#define OPENNSL_PKT_F_TRUNK        0x20000000 // Trunk port
```

## L2 Table Structures

### L2 Address Entry

```c
typedef struct opennsl_l2_addr_s {
    uint32 flags;                       // OPENNSL_L2_xxx flags
    opennsl_mac_t mac;                  // 802.3 MAC address
    opennsl_vlan_t vid;                 // VLAN identifier
    int port;                           // Zero-based port number
    int modid;                          // XGS: modid
    opennsl_trunk_t tgid;               // Trunk group ID
    opennsl_multicast_t l2mc_group;    // L2MC table index
    // ... additional fields ...
} opennsl_l2_addr_t;
```

### L2 Flags

```c
#define OPENNSL_L2_DISCARD_SRC    0x00000002
#define OPENNSL_L2_DISCARD_DST    0x00000004
#define OPENNSL_L2_COPY_TO_CPU     0x00000008
#define OPENNSL_L2_L3LOOKUP        0x00000010
#define OPENNSL_L2_STATIC          0x00000020
#define OPENNSL_L2_HIT             0x00000040
#define OPENNSL_L2_TRUNK_MEMBER    0x00000080
#define OPENNSL_L2_MCAST           0x00000100
#define OPENNSL_L2_LOCAL_CPU       0x00200000  // Entry is for local CPU
```

### L2 API Functions

```c
// Add L2 address entry
extern int opennsl_l2_addr_add(int unit, opennsl_l2_addr_t *l2addr);

// Delete L2 address entry
extern int opennsl_l2_addr_delete(int unit, opennsl_mac_t mac, opennsl_vlan_t vid);

// Find L2 address entry
extern int opennsl_l2_addr_get(int unit, opennsl_mac_t mac, opennsl_vlan_t vid, opennsl_l2_addr_t *l2addr);
```

## L3 Table Structures

### L3 Host Entry

```c
typedef struct opennsl_l3_host_s {
    uint32 l3a_flags;                   // OPENNSL_L3_xxx flags
    opennsl_vrf_t l3a_vrf;              // Virtual router instance
    opennsl_ip_t l3a_ip_addr;           // Destination host IP (IPv4)
    opennsl_ip6_t l3a_ip6_addr;         // Destination host IP (IPv6)
    opennsl_cos_t l3a_pri;              // New priority in packet
    opennsl_if_t l3a_intf;              // L3 intf associated with address
    opennsl_mac_t l3a_nexthop_mac;      // Next hop MAC address
    opennsl_port_t l3a_port_tgid;      // Port/TGID packet is switched to
    // ... additional fields ...
} opennsl_l3_host_t;
```

### L3 Route Entry

```c
typedef struct opennsl_l3_route_s {
    uint32 l3a_flags;                   // OPENNSL_L3_xxx flags
    opennsl_vrf_t l3a_vrf;              // Virtual router instance
    opennsl_ip_t l3a_subnet;             // IP subnet address (IPv4)
    opennsl_ip6_t l3a_ip6_net;          // IP subnet address (IPv6)
    opennsl_ip_t l3a_ip_mask;            // IP subnet mask (IPv4)
    opennsl_ip6_t l3a_ip6_mask;         // IP subnet mask (IPv6)
    opennsl_if_t l3a_intf;               // L3 interface associated with route
    opennsl_port_t l3a_port_tgid;       // Port or trunk group ID
    opennsl_cos_t l3a_pri;               // Priority (COS)
    // ... additional fields ...
} opennsl_l3_route_t;
```

### L3 Egress Entry

```c
typedef struct opennsl_l3_egress_s {
    uint32 flags;                       // Interface flags
    opennsl_if_t intf;                  // L3 interface (source MAC, tunnel)
    opennsl_mac_t mac_addr;             // Next hop forwarding destination MAC
    opennsl_vlan_t vlan;                // Next hop VLAN ID
    opennsl_module_t module;            
    opennsl_port_t port;                // Port packet switched to
    opennsl_trunk_t trunk;              // Trunk packet switched to
    int qos_map_id;                     // General QOS map id
    opennsl_if_t encap_id;              // Encapsulation index
    // ... additional fields ...
} opennsl_l3_egress_t;
```

### L3 Flags

```c
#define OPENNSL_L3_L2ONLY          (1 << 0)   // L2 switch only on interface
#define OPENNSL_L3_UNTAG           (1 << 1)   // Packet goes out untagged
#define OPENNSL_L3_S_HIT            (1 << 2)   // Source IP address match
#define OPENNSL_L3_D_HIT            (1 << 3)   // Destination IP address match
#define OPENNSL_L3_HIT              (OPENNSL_L3_S_HIT | OPENNSL_L3_D_HIT)
#define OPENNSL_L3_IP6              (1 << 17)  // IPv6
#define OPENNSL_L3_MULTIPATH        (1 << 14)  // Specify ECMP treatment
#define OPENNSL_L3_COPY_TO_CPU      (1 << 23)  // Send a copy to CPU
```

### L3 API Functions

```c
// Add L3 host entry
extern int opennsl_l3_host_add(int unit, opennsl_l3_host_t *info);

// Delete L3 host entry
extern int opennsl_l3_host_delete(int unit, opennsl_l3_host_t *info);

// Add L3 route entry
extern int opennsl_l3_route_add(int unit, opennsl_l3_route_t *info);

// Delete L3 route entry
extern int opennsl_l3_route_delete(int unit, opennsl_l3_route_t *info);

// Add L3 egress entry
extern int opennsl_l3_egress_create(int unit, opennsl_l3_egress_t *egr, opennsl_if_t *if_id);

// Delete L3 egress entry
extern int opennsl_l3_egress_destroy(int unit, opennsl_if_t intf);
```

## Table Sizes (from switchd analysis)

From Ghidra analysis of switchd binary strings:

- **Host Table**: Current count, maximum size tracked
- **Route Table**: Current count, maximum size tracked, IPv4/IPv6 split
- **L2 Table**: Current count, maximum size tracked
- **ECMP Table**: Next-hop table current count, maximum size, max next-hops per route

## Register Access Functions

### Direct Register Access (via BDE)

```c
// Read register
uint32 bde_read(int unit, uint32 offset);

// Write register
void bde_write(int unit, uint32 offset, uint32 value);

// Read 64-bit register
uint64 bde_read64(int unit, uint32 offset);

// Write 64-bit register
void bde_write64(int unit, uint32 offset, uint64 value);
```

### S-Channel Access

S-Channel provides indirect register access for registers not directly accessible via memory-mapped I/O.

**Operation Flow**:
1. Write command to S-Channel command register (`CMIC_CMC0_SCHAN_CTRL` = `0x32800`)
2. Poll status register for completion
3. Read/write data via S-Channel data registers

## Related Documents

- [`GHIDRA_REGISTER_TABLE_ANALYSIS.md`](./GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Detailed Ghidra analysis results
- [`GAPS_FOR_CUSTOM_SWITCHD_SDK.md`](./GAPS_FOR_CUSTOM_SWITCHD_SDK.md) - Missing SDK information
- [`REVERSE_ENGINEERING_STATUS_REPORT.md`](./REVERSE_ENGINEERING_STATUS_REPORT.md) - Overall status
- [`WHAT_MAKES_THE_SWITCH_WORK.md`](./WHAT_MAKES_THE_SWITCH_WORK.md) - System architecture

## Extraction Scripts

- `scripts/reverse-engineering/extract-opennsl-registers.sh` - Extracts register definitions from OpenNSL source
- `scripts/reverse-engineering/ExtractRegisterConstants.java` - Ghidra script to extract register offsets from switchd
- `scripts/reverse-engineering/ExtractRegisterAndTableInfo.java` - Ghidra script for general register/table analysis

## Next Steps

1. **Run enhanced Ghidra script** (`ExtractRegisterConstants.java`) on switchd to find more register offsets
2. **Cross-reference** register offsets found in switchd with OpenNSL definitions
3. **Document** port-specific registers (SerDes, PHY, MAC)
4. **Extract** DMA ring buffer register offsets
5. **Map** table memory addresses and access patterns

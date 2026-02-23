# Function String Analysis (Table Address Users)

**Date**: 2026-02-15  
**Source**: `build-server/opennsl/sdk-deep-extract/opennsl-function-strings.txt`  
**Method**: Extracted strings from functions that reference table memory addresses

## Overview

We analyzed 12 functions that reference table memory addresses (from `XrefTableAddressConstants.java`) and extracted strings they reference. This helps identify **table names** and **register names** used by the SDK.

## Key Findings

### Table-Related Strings

1. **`skip_L2_USER_ENTRY`**
   - Found in: `FUN_00948700`, `FUN_01cc2f2c`
   - **Significance**: Directly identifies **L2_USER_ENTRY** table
   - **Addresses used**: `0x0180c200` (both functions)
   - **Implication**: `0x0180c200` is likely the base address or offset for the L2 User Entry table

2. **FP (Field Processor) Related**
   - Found in: `FUN_008fb92c`
   - Strings: `"FP(unit %d) Error: action=%s conflicts with existing action in entry=%d"`
   - **Significance**: Identifies **FP (Field Processor)** table operations
   - **Address used**: `0x01f00898`
   - **Implication**: `0x01f00898` is related to FP/ACL table entries

### Register Names

1. **A9JTAG Registers**
   - Found in: `FUN_00faf85c`
   - Strings:
     - `"A9JTAG_M0_IDM_IDM_INTERRUPT_STATUS"`
     - `"A9JTAG_M0_IDM_IDM_RESET_STATUS"`
   - **Significance**: Identifies ARM Cortex-A9 JTAG-related registers
   - **Address used**: `0x01855abc`

### CMIC Microcontroller (UC) Related

- Found in: `FUN_01905af8`
- Strings:
  - `"soc_cmic_uc_appl_init"`
  - `"UC%d soc_cmic_uc_msg_receive failed"`
  - `"UC%d soc_cmic_uc_msg_send failed"`
- **Significance**: CMIC UC (microcontroller) message passing
- **Address used**: `0x01000000` (region base)
- **Implication**: Base address `0x01000000` is used for CMIC UC initialization

### Hardware Control Strings

- Found in: `FUN_01452b3c`
- Strings:
  - PTP (Precision Time Protocol) related: `"ptp_bs_fref"`, `"ptp_ts_pll_fref"`, etc.
  - Temperature monitoring: `"temp0_threshold"`, `"temp1_threshold"`
  - Clock/PLL control: `"BS_PLL0 not locked"`, `"LCPLL %d not locked"`
- **Address used**: `0x01312d00`
- **Implication**: Hardware initialization and control registers

## Function-to-Address Mapping

| Function | Address Used | Key Strings | Table/Register Type |
|----------|--------------|-------------|---------------------|
| `FUN_00948700` | `0x0180c200` | `skip_L2_USER_ENTRY` | **L2_USER_ENTRY** table |
| `FUN_01cc2f2c` | `0x0180c200` | `skip_L2_USER_ENTRY` | **L2_USER_ENTRY** table |
| `FUN_008fb92c` | `0x01f00898` | `FP(unit %d) Error: action=...` | **FP/ACL** table |
| `FUN_00faf85c` | `0x01855abc` | `A9JTAG_M0_IDM_*` | **A9JTAG** registers |
| `FUN_01905af8` | `0x01000000` | `soc_cmic_uc_*` | **CMIC UC** base |
| `FUN_01452b3c` | `0x01312d00` | `ptp_*`, `temp*`, `*PLL*` | Hardware control |

## Implications

### Table Memory Mapping

1. **L2_USER_ENTRY Table**: `0x0180c200` is confirmed as an L2 table address
   - This is within the `0x01800000` bucket (high density: 1435 addresses)
   - Suggests the `0x01800000-0x018fffff` region contains L2-related tables

2. **FP/ACL Tables**: `0x01f00898` is related to Field Processor tables
   - This is within the `0x01f00000` bucket (high density: 2005 addresses)
   - Suggests the `0x01f00000-0x01ffffff` region contains FP/ACL tables

3. **Base Address**: `0x01000000` is used for CMIC UC initialization
   - This is the region base address
   - Confirms `0x01000000` is the start of the table memory region

### Next Steps

1. **Expand string extraction** to more functions:
   - Find functions that reference addresses in `0x01b00000` and `0x01c00000` buckets
   - These high-density buckets likely contain L3, ECMP, or other major tables

2. **Cross-reference with OpenNSL headers**:
   - Match extracted strings to known table names from `opennsl/l2.h`, `opennsl/l3.h`
   - Identify which addresses correspond to which OpenNSL table structures

3. **Extract more anchor addresses**:
   - Use the identified table names to find more addresses
   - Search for strings like `"L3_DEFIP"`, `"ECMP"`, `"VLAN_XLATE"` in the binary

## Related Documents

- [`TABLE_ADDR_XREFS_OPENNSL.md`](./TABLE_ADDR_XREFS_OPENNSL.md) - Initial xref analysis
- [`TABLE_MEMORY_ANALYSIS.md`](./TABLE_MEMORY_ANALYSIS.md) - Address distribution analysis
- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Consolidated register/table map

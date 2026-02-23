# Table Name to Address Mapping

**Date**: 2026-02-15  
**Source**: `build-server/opennsl/sdk-deep-extract/opennsl-table-name-strings.txt`  
**Method**: Direct string search in `libopennsl.so.1` binary

## Overview

We searched the `libopennsl.so.1` binary for known table name patterns and found **thousands of occurrences** of table-related strings. This document maps these table names to their usage locations in the binary.

## Table Name Patterns Found

| Pattern | Occurrences | Description |
|---------|-------------|-------------|
| **L3_DEFIP** | 394 | L3 Default IP (FIB/routing table) |
| **L3_ECMP** | 117 | L3 ECMP (Equal-Cost Multi-Path) table |
| **ECMP** | 532 | ECMP-related strings (broader pattern) |
| **VLAN_XLATE** | 350 | VLAN translation table |
| **VLAN** | 1,977 | VLAN-related strings (broader pattern) |
| **FP** | 4,858 | Field Processor (ACL/filtering) |
| **ACL** | 228 | Access Control List |
| **L3_HOST** | 2 | L3 host table |
| **L3_EGRESS** | 1 | L3 egress table |

## Key Findings

### L3 Tables

1. **L3_DEFIP** (394 occurrences)
   - **Purpose**: L3 Default IP table (FIB - Forwarding Information Base)
   - **Usage**: Stores IP routes for longest-prefix-match lookups
   - **Addresses**: Found at many locations in binary (e.g., `0x01e13748`, `0x01f167e0`, `0x01f4ad30`)
   - **Implication**: This is a major table, likely spanning multiple memory regions

2. **L3_ECMP** (117 occurrences) + **ECMP** (532 occurrences)
   - **Purpose**: ECMP (Equal-Cost Multi-Path) next-hop groups
   - **Usage**: Stores multiple next-hops for load balancing
   - **Addresses**: Found at locations like `0x01e8edb8`, `0x01f5d258`, `0x01f71b34`
   - **Implication**: High-density bucket `0x01c00000` (2595 addresses) likely contains ECMP tables

3. **L3_HOST** (2 occurrences)
   - **Purpose**: L3 host table (host routes)
   - **Addresses**: `0x01e7181c`, `0x025041ac`

4. **L3_EGRESS** (1 occurrence)
   - **Purpose**: L3 egress interface table
   - **Address**: `0x024755b8`

### L2 Tables

From previous analysis, we confirmed:
- **L2_USER_ENTRY**: `0x0180c200` (confirmed via string `skip_L2_USER_ENTRY`)

### VLAN Tables

1. **VLAN_XLATE** (350 occurrences)
   - **Purpose**: VLAN translation/translation table
   - **Usage**: Maps VLAN IDs and port configurations
   - **Addresses**: Found at `0x01e94be8`, `0x01f42518`, `0x01f48520`, etc.
   - **Implication**: Likely in `0x01e00000` or `0x01f00000` buckets

2. **VLAN** (1,977 occurrences)
   - **Purpose**: General VLAN-related operations
   - **Note**: Very common pattern, includes many related strings

### Field Processor / ACL Tables

1. **FP** (4,858 occurrences)
   - **Purpose**: Field Processor (ACL/filtering engine)
   - **Usage**: Packet filtering, ACL rules, policy enforcement
   - **Addresses**: Found throughout binary, especially in `0x01f00000` bucket
   - **Confirmed**: `0x01f00898` is FP-related (from previous analysis)

2. **ACL** (228 occurrences)
   - **Purpose**: Access Control List operations
   - **Addresses**: Found at `0x01e5e9f4`, `0x01e5e9fc`, etc.

## Address-to-Table Mapping (Inferred)

Based on string locations and address distribution:

| Address Range | Likely Table Types | Evidence |
|---------------|-------------------|----------|
| `0x01000000-0x010fffff` | CMIC UC, base tables | `0x01000000` confirmed as CMIC UC base |
| `0x01800000-0x018fffff` | **L2 tables** | `0x0180c200` = L2_USER_ENTRY (confirmed) |
| `0x01b00000-0x01bfffff` | **L3/ECMP tables** | High density (2051 addresses), ECMP strings found |
| `0x01c00000-0x01cfffff` | **L3_DEFIP, ECMP** | Highest density (2595 addresses), L3_DEFIP strings |
| `0x01e00000-0x01efffff` | **VLAN_XLATE** | VLAN_XLATE strings found in this range |
| `0x01f00000-0x01ffffff` | **FP/ACL tables** | `0x01f00898` = FP (confirmed), FP strings abundant |

## Table Name → Address Cross-Reference (Ghidra)

We ran `XrefTableNamesToAddresses.java` to find functions that reference both a table name string and table memory (0x01xxxxxx). Results in `build-server/opennsl/sdk-deep-extract/opennsl-table-name-to-addr-xref.txt`.

### Summary

| Table Name    | String Locations | Functions | Table Addresses Found |
|---------------|------------------|-----------|------------------------|
| L2_ENTRY      | 153              | 8         | 448+ (e.g. 0x0137cd30, 0x01842c04) |
| L2_USER_ENTRY | 104              | 20        | 177+ (e.g. 0x0137cd30, 0x01408284) |
| L3_DEFIP      | 361              | 1         | 5 (0x018124a8, 0x018dc3a0, 0x018dc3b0, 0x018dc430, 0x01f19a50) |
| L3_ECMP       | 56               | 2         | 51+ (e.g. 0x0103bdc0, 0x01a15728, 0x01b16eec) |
| VLAN_XLATE    | 230              | 1         | 114+ (e.g. 0x0137e2f0, 0x013d3a8c) |
| ECMP          | 176              | 24        | 671+ (e.g. 0x0103136c, 0x01031888) |

L3_HOST and L3_EGRESS had no table memory refs in the same functions (or no matching string locations). Addresses are in the 0x01xxxxxx region (script output omits leading zero).

## Next Steps

1. **Extract more functions**:
   - Functions using addresses in `0x01b00000` and `0x01c00000` buckets
   - Extract strings from those functions to confirm L3_DEFIP and ECMP mappings

3. **Search for table base address definitions**:
   - Look for patterns like `L3_DEFIPm`, `L3_ECMPm` (memory table macros)
   - These might directly define base addresses

## Related Documents

- [`FUNCTION_STRINGS_ANALYSIS.md`](./FUNCTION_STRINGS_ANALYSIS.md) - Strings extracted from functions using table addresses
- [`TABLE_MEMORY_ANALYSIS.md`](./TABLE_MEMORY_ANALYSIS.md) - Address distribution analysis
- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Consolidated register/table map

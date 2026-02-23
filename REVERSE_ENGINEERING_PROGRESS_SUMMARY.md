# Reverse Engineering Progress Summary

**Date**: 2026-02-15  
**Target**: Broadcom BCM56846 (Trident+) ASIC  
**Goal**: Reverse engineer SDK information for custom `switchd` implementation

## Executive Summary

We have successfully extracted and analyzed **20,176 table memory addresses** from `libopennsl.so.1` and identified **major table names** through string analysis. This provides a solid foundation for understanding the ASIC's memory organization and table structures.

## Key Achievements

### 1. Register Extraction ✅

- **LED Registers**: 15 registers identified (matching OpenNSL definitions)
- **Port Registers**: 3 registers identified
- **CMIC Registers**: Definitions extracted from OpenNSL source code
- **Challenge**: CMIC/S-Channel registers not found as constants (likely computed at runtime)

### 2. Table Memory Address Extraction ✅

- **20,176 unique addresses** extracted from `libopennsl.so.1`
- **Address range**: `0x01000000–0x01ffff20` (16MB region)
- **Distribution**: Analyzed by 1MB buckets, identified high-density regions

### 3. Table Name Identification ✅

**Confirmed Table Names**:
- **L2_USER_ENTRY**: `0x0180c200` (confirmed via function string analysis)
- **FP/ACL Tables**: `0x01f00898` (confirmed via function string analysis)
- **CMIC UC Base**: `0x01000000` (confirmed via function string analysis)

**Table Name → Address Cross-Reference** (Ghidra script: functions using both table name string and table memory):
- **L3_DEFIP**: 5 addresses (e.g. 0x018124a8, 0x018dc3a0, 0x01f19a50)
- **L3_ECMP**: 51+ addresses (e.g. 0x0103bdc0, 0x01a15728, 0x01b16eec)
- **L2_ENTRY**: 448+ addresses; **L2_USER_ENTRY**: 177+; **VLAN_XLATE**: 114+; **ECMP**: 671+

**Table Name Patterns Found** (via direct string search):
- **L2_ENTRY**: 223 occurrences
- **L2_USER_ENTRY**: 107 occurrences
- **L3_DEFIP**: 394 occurrences
- **L3_ECMP**: 117 occurrences
- **ECMP**: 532 occurrences
- **VLAN_XLATE**: 350 occurrences
- **VLAN**: 1,977 occurrences
- **FP**: 4,858 occurrences
- **ACL**: 228 occurrences
- **L3_HOST**: 2 occurrences
- **L3_EGRESS**: 1 occurrence

### 4. Function-to-Address Mapping ✅

Identified 12+ functions that reference table memory addresses:
- `FUN_00948700`, `FUN_01cc2f2c`: Use `0x0180c200` (L2_USER_ENTRY)
- `FUN_008fb92c`: Uses `0x01f00898` (FP/ACL)
- `FUN_01905af8`: Uses `0x01000000` (CMIC UC base)
- `FUN_01452b3c`: Uses `0x01312d00` (Hardware control)
- And more...

## Memory Region Mapping (Inferred)

| Region | Density | Likely Contents | Evidence |
|--------|---------|-----------------|----------|
| `0x01000000-0x010fffff` | 1405 | CMIC UC, base tables | `0x01000000` = CMIC UC base |
| `0x01800000-0x018fffff` | 1435 | **L2 tables** | `0x0180c200` = L2_USER_ENTRY ✅ |
| `0x01b00000-0x01bfffff` | 2051 | **L3/ECMP tables** | High density, ECMP strings found |
| `0x01c00000-0x01cfffff` | 2595 | **L3_DEFIP, ECMP** | Highest density, L3_DEFIP strings |
| `0x01e00000-0x01efffff` | 1475 | **VLAN_XLATE** | VLAN_XLATE strings found |
| `0x01f00000-0x01ffffff` | 2005 | **FP/ACL tables** | `0x01f00898` = FP ✅ |

## Tools and Scripts Created

1. **ExtractRegisterConstants.java**: Ghidra script to extract register/table addresses
   - Handles PowerPC `lis`+`addi` instruction pairs
   - Scans both code and data sections
   - Filters by address ranges

2. **XrefTableAddressConstants.java**: Cross-reference anchor addresses to functions
   - Finds data locations holding target addresses
   - Lists all code references to those locations

3. **ExtractAllFunctionStrings.java**: Extract strings from functions using table addresses
   - Identifies table-like strings (L2, L3, VLAN, FP, etc.)
   - Links strings to specific functions

4. **SearchTableNameStrings.java**: Direct search for table name patterns
   - Searches entire binary for known table names
   - Finds thousands of occurrences

5. **Bash wrapper scripts**: Automated Ghidra headless execution on build server

## Documentation Created

1. **SDK_REGISTER_MAP.md**: Consolidated register and table map
2. **TABLE_MEMORY_ANALYSIS.md**: Address distribution analysis
3. **FUNCTION_STRINGS_ANALYSIS.md**: Strings extracted from functions
4. **TABLE_NAME_MAPPING.md**: Table name patterns found in binary
5. **TABLE_MEMORY_MAP_FROM_OPENNSL.md**: Histogram of addresses by 1MB buckets
6. **REGISTER_EXTRACTION_RESULTS.md**: Detailed extraction results
7. **OPENNSL_LIBRARY_EXTRACTION_RESULTS.md**: Library extraction analysis

## Remaining Gaps

### 1. CMIC/S-Channel Register Access
- **Status**: Not found as constants in binaries
- **Likely reason**: Computed at runtime or accessed via SDK functions
- **Next step**: Analyze BDE (Broadcom Device Enumeration) module for register access patterns

### 2. Direct Address-to-Table Mapping
- **Status**: Partial (3 addresses confirmed, thousands inferred)
- **Challenge**: Need to cross-reference string locations with actual table memory addresses
- **Next step**: Find functions that reference both table name strings AND table addresses

### 3. Table Structure Definitions
- **Status**: Have OpenNSL structure definitions (`opennsl_l2_addr_t`, `opennsl_l3_route_t`, etc.)
- **Gap**: Need to map these structures to actual memory layouts
- **Next step**: Analyze table access functions to understand entry formats

## Next Steps

1. ~~**Cross-reference table names with addresses**~~ **DONE**: `XrefTableNamesToAddresses.java` produced direct mappings (L3_DEFIP, L3_ECMP, L2_ENTRY, L2_USER_ENTRY, VLAN_XLATE, ECMP). See `opennsl-table-name-to-addr-xref.txt` and TABLE_NAME_MAPPING.md.

2. ~~**Analyze BDE module**~~ **DONE**: CMIC/CMICm/CMICd offsets documented from `linux-user-bde.c` in BDE_CMIC_REGISTERS.md.

3. **Table entry format analysis**:
   - Analyze functions that read/write table entries
   - Map OpenNSL structures to actual memory layouts

4. **Expand function analysis**:
   - Extract strings from more functions in high-density buckets
   - Identify additional table names and their addresses

## Files and Locations

### Extraction Results
- `build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt`: 20,197 register/table addresses
- `build-server/opennsl/sdk-deep-extract/opennsl-table-addr-xrefs.txt`: Cross-references for anchor addresses
- `build-server/opennsl/sdk-deep-extract/opennsl-function-strings.txt`: Strings from functions using table addresses
- `build-server/opennsl/sdk-deep-extract/opennsl-table-name-strings.txt`: Direct table name string search results

### Scripts
- `scripts/reverse-engineering/ExtractRegisterConstants.java`
- `scripts/reverse-engineering/XrefTableAddressConstants.java`
- `scripts/reverse-engineering/ExtractAllFunctionStrings.java`
- `scripts/reverse-engineering/SearchTableNameStrings.java`
- `scripts/reverse-engineering/ghidra-*.sh`: Wrapper scripts

### Documentation
- `docs/reverse-engineering/SDK_REGISTER_MAP.md`: Main reference
- `docs/reverse-engineering/TABLE_MEMORY_ANALYSIS.md`: Address analysis
- `docs/reverse-engineering/FUNCTION_STRINGS_ANALYSIS.md`: Function string analysis
- `docs/reverse-engineering/TABLE_NAME_MAPPING.md`: Table name patterns

## Conclusion

We have made significant progress in reverse engineering the Broadcom SDK:
- ✅ Extracted 20,176 table memory addresses
- ✅ Identified major table names (L2, L3, VLAN, FP, ECMP)
- ✅ Mapped 3 addresses to specific tables
- ✅ Created tools and documentation for continued analysis

The foundation is solid for continuing the reverse engineering effort and eventually building a custom `switchd` implementation.

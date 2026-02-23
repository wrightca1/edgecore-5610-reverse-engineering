# Table ID Mapping Analysis

**Date**: 2026-02-19  
**Status**: Comprehensive analysis of table ID usage across dispatcher functions

---

## Summary

Analysis of table IDs found in various dispatcher functions reveals patterns that help map numerical IDs to logical table names (L3_DEFIP, L3_ECMP, VLAN_XLATE).

---

## Table ID Findings

### L2 Table

**Confirmed**: `0x1547` (5447 decimal)
- **Location**: FUN_01408a48 @ `0x01408b10` (`li r4,0x1547`)
- **Call chain**: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10
- **Status**: ✅ Confirmed as L2_USER_ENTRY table

### L3_DEFIP (L3 Route Table)

**Hypothesized IDs**: `0x22c9`, `0x22ca`, `0x22d3`

**Evidence**:
1. **FUN_01876f10** checks `0x22ca` at `0x01876fc4`
   - Converts to `0x22c9` at `0x01877024`
   
2. **FUN_018751e0** checks `0x22c9` at `0x018752d4`
   - Calls FUN_01874a50 (dispatcher)
   - FUN_018751e0 is called by FUN_018758cc
   - This function appears to handle L3 route operations

3. **FUN_018d7ad4** validates `0x22d3` (8915 decimal)
   - Very close to `0x22ca` (8906) and `0x22c9` (8905)
   - Passes to FUN_018d62ec → FUN_01876f10

**Pattern**: `0x22c9` < `0x22ca` < `0x22d3` - likely different contexts or offsets for the same logical table

**Hypothesis**: These are all L3_DEFIP (L3 route table) IDs:
- `0x22c9` - Base or offset variant
- `0x22ca` - Standard ID
- `0x22d3` - Validated variant

### L3_ECMP (ECMP Group Table)

**Hypothesized IDs**: `0x2c32`, `0x2c33`, `0x6418`, `0x6419`, `0x8a8`, `0x1`

**Evidence**:
1. **FUN_01876f10** checks `0x2c33` at `0x01876fcc`

2. **FUN_018d7ad4** validates `0x2c32` (11314 decimal)
   - Very close to `0x2c33` (11315)
   - Passes to FUN_018d62ec → FUN_01876f10

3. **FUN_01a1572c** (references "L3_ECMP" string) uses:
   - `0x6418`
   - `0x6419`
   - `0x8a8`
   - `0x1`
   - Calls FUN_01876f10 with these IDs

**Pattern**: `0x2c32` < `0x2c33` - likely different contexts for ECMP operations

**Hypothesis**: 
- `0x2c32`/`0x2c33` - ECMP group table (validated by FUN_018d7ad4)
- `0x6418`/`0x6419`/`0x8a8`/`0x1` - ECMP-related operations (from table name reference)

### VLAN_XLATE (VLAN Translation Table)

**Hypothesized ID**: `0x835`

**Evidence**:
1. **FUN_01876f10** checks `0x835` at `0x01876fd4`
   - Converts to `0x6fa` at `0x0187702c`

2. **FUN_018d7ad4** validates range `0x1559-0x155e` (5465-5470)
   - Also validates `0x1599` (5529) and `0x15a5` (5541)
   - These are in a different range, possibly VLAN-related

**Hypothesis**: `0x835` (2101 decimal) is VLAN_XLATE table ID

### Other Table IDs

**FUN_018d7ad4** validates additional IDs:
- `0x1559-0x155e` (5465-5470) - Range check
- `0x1599` (5529)
- `0x2c24` (11300)
- `0x15a5` (5541)

**FUN_018d62ec** validates maximum table ID:
- Maximum: `0x2c67` (11367 decimal)

---

## Table ID Validation Flow

### Validation Chain

```
API Call
  ↓
FUN_018d7ad4 (table ID dispatcher/validator)
  ├─ Validates: 0x22d3, 0x2c32, 0x1559-0x155e, 0x1599, 0x2c24, 0x15a5
  ├─ Routes to: FUN_01874a50, FUN_01875b04, FUN_018d987c, FUN_01882c80, FUN_018815e4
  ↓
FUN_018d62ec (table ID validator)
  ├─ Validates: table ID <= 0x2c67
  ↓
FUN_01876f10 (generic table write dispatcher)
  ├─ Checks: 0x1547 (L2), 0x22ca, 0x2c33, 0x835
  ↓
Hardware Write (S-Channel or mmap)
```

### Direct Checks

Some functions check table IDs directly:
- **FUN_018751e0**: Checks `0x22c9` → calls FUN_01874a50
- **FUN_01876f10**: Checks `0x1547`, `0x22ca`, `0x2c33`, `0x835`

---

## Table ID Mapping Summary

| Table Name | Hypothesized IDs | Confidence | Evidence |
|------------|------------------|------------|----------|
| **L2_USER_ENTRY** | `0x1547` | ✅ Confirmed | Direct call chain identified |
| **L3_DEFIP** | `0x22c9`, `0x22ca`, `0x22d3` | 🟡 High | Multiple checks, close values, L3 route context |
| **L3_ECMP** | `0x2c32`, `0x2c33`, `0x6418`, `0x6419`, `0x8a8`, `0x1` | 🟡 High | Table name reference + close values |
| **VLAN_XLATE** | `0x835` | 🟡 Medium | Checked by FUN_01876f10, VLAN context |

---

## Next Steps

1. **Runtime verification**: Use live switch traces to confirm table ID mappings
2. **Function analysis**: Analyze FUN_018758cc (caller of FUN_018751e0) to understand L3 route flow
3. **Table name references**: Find more functions referencing "L3_DEFIP", "VLAN_XLATE" strings
4. **Structure analysis**: Analyze data structures passed to dispatchers to understand table formats

---

## References

- [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) - Complete call chain
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md) - L3/ECMP/VLAN analysis
- [DISPATCHER_CALL_CHAIN_SUMMARY.md](DISPATCHER_CALL_CHAIN_SUMMARY.md) - Dispatcher summary

# L3/ECMP/VLAN Analysis Progress Summary

**Date**: 2026-02-19  
**Status**: IN PROGRESS - Call chains identified, table IDs partially mapped

---

## Executive Summary

We have successfully identified the unified table write mechanism used by all table types (L2, L3, ECMP, VLAN) and traced the call chains from potential API entry points down to the hardware write layer. The analysis reveals a multi-level dispatch system with table ID validation at each level.

---

## Key Findings

### 1. Unified Table Write Mechanism ✅

**Central Dispatcher**: FUN_01876f10 (`0x01876f10`)
- **2,245 callers** across all table types
- Accepts table ID in r4 parameter
- Checks for specific table IDs: `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`
- Converts some IDs: `0x22ca` → `0x22c9`, `0x835` → `0x6fa`

### 2. Table ID Validation Layers ✅

**Layer 1 - Validator/Dispatcher**: FUN_018d7ad4 (`0x018d7ad4`)
- Validates table IDs before calling FUN_018d62ec
- Checks for: `0x1559-0x155e`, `0x1599`, `0x2c32`, `0x22d3`, `0x2c24`, `0x15a5`
- **5 callers** identified

**Layer 2 - Wrapper**: FUN_018d62ec (`0x018d62ec`)
- Validates table ID <= `0x2c67` (maximum valid table ID)
- Calls FUN_01876f10
- **2 callers** from FUN_018d7ad4

**Layer 3 - Dispatcher**: FUN_01876f10 (`0x01876f10`)
- Generic table write dispatcher
- Routes to appropriate write function based on table ID

### 3. Call Chain Structure ✅

```
API Entry Points (to be identified)
    ↓
FUN_01874a50 / FUN_01875b04 / FUN_018d987c / FUN_01882c80 / FUN_018815e4
    ↓ (pass table ID in r7)
FUN_018d7ad4 (validates table ID)
    ↓
FUN_018d62ec (validates <= 0x2c67)
    ↓
FUN_01876f10 (dispatches based on table ID)
    ↓
FUN_01876ee0 → FUN_01876c30 → Function pointer dispatch
    ↓
Hardware write (S-Channel or direct mmap)
```

### 4. Table ID Mapping (Partial) ✅

**Confirmed**:
- **L2**: `0x1547` (5447 decimal)
  - Passed by FUN_01408a48 @ `0x01408b10`
  - Call chain: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10

**Likely L3/ECMP/VLAN** (needs confirmation):
- **`0x22ca`** / **`0x22d3`** (8906 / 8915) - Possibly L3_DEFIP
- **`0x2c33`** / **`0x2c32`** (11315 / 11314) - Possibly L3_ECMP
- **`0x835`** (2101) - Possibly VLAN_XLATE

**Other IDs found**:
- `0x1559-0x155e` (5465-5470) - Range validated by FUN_018d7ad4
- `0x1599` (5529)
- `0x2c24` (11300)
- `0x15a5` (5541)

### 5. Dispatcher Function Callers ✅

| Function | Call Sites | Callers | Notes |
|----------|------------|---------|-------|
| **FUN_01874a50** | 1 | FUN_018751e0 | Single caller path |
| **FUN_01875b04** | 1 | 4 callers | Checks for 0x35/0x36/0x37/0x38/0x30 |
| **FUN_018d987c** | 1 | FUN_018da09c | Computes table ID from memory + 0x974 |
| **FUN_01882c80** | 1 | 30 callers | General-purpose, many call sites |
| **FUN_018815e4** | 1 | 30 callers | General-purpose, many call sites |

---

## Analysis Artifacts

### Scripts Created
1. `FindTableWriteCallers.java` - Finds all callers of FUN_01876f10
2. `FindTableIDConstants.java` - Attempts to find table ID constants
3. `FindSpecificTableIDs.java` - Searches for specific known table IDs
4. `FindL3TableCallers.java` - Finds functions referencing table name strings
5. `FindTableDispatcherCallers.java` - Finds callers of FUN_018d7ad4
6. `AnalyzeTableDispatcherCallSites.java` - Analyzes call sites for table IDs
7. `FindTableDispatcherCallerChain.java` - Traces caller chains

### Output Files
- `libopennsl-table-write-callers.txt` - 2,245 callers of FUN_01876f10
- `libopennsl-table-ids.txt` - Table ID constants (0 found - passed as parameters)
- `libopennsl-specific-table-ids.txt` - Specific table IDs (0 found - passed as parameters)
- `libopennsl-l3-table-callers.txt` - Functions referencing table names
- `libopennsl-table-dispatcher-callers.txt` - 5 callers of FUN_018d7ad4
- `libopennsl-table-dispatcher-analysis.txt` - Analysis of call sites
- `libopennsl-table-dispatcher-caller-chain.txt` - Caller chains

### Function Dumps
- `libopennsl-dump-01876f10.txt` - Generic table write dispatcher
- `libopennsl-dump-018d62ec.txt` - Table write wrapper
- `libopennsl-dump-018d7ad4.txt` - Table ID validator/dispatcher
- `libopennsl-dump-01408a48.txt` - L2-specific path (passes 0x1547)
- `libopennsl-dump-01874a50.txt` - Dispatcher caller
- `libopennsl-dump-01875b04.txt` - Dispatcher caller
- `libopennsl-dump-018d987c.txt` - Dispatcher caller

---

## Remaining Work

### High Priority
1. **Map table IDs to table names**:
   - Use live switch traces: add L3 route, ECMP group, VLAN translation
   - Correlate strace output with Ghidra findings
   - Map `0x22ca`/`0x22d3`, `0x2c33`/`0x2c32`, `0x835` to specific tables

2. **Find API entry points**:
   - Trace callers of FUN_01874a50, FUN_01875b04, FUN_018d987c
   - Check if any are exported symbols (`opennsl_l3_route_add`, etc.)
   - Identify which functions correspond to which API calls

3. **Map API structs to ASIC formats**:
   - Once table IDs mapped, trace data flow from API structs
   - Document byte order, field positions, valid bits
   - Map `opennsl_l3_route_t` → L3_DEFIP format
   - Map `opennsl_l3_egress_ecmp_t` → L3_ECMP format
   - Map `opennsl_vlan_translate_t` → VLAN_XLATE format

### Medium Priority
4. **Identify function pointer targets**:
   - FUN_01876c30 calls function pointer from `[r9-0x6b7c]`
   - Determine which functions are actually called at runtime
   - May require live switch traces or deeper static analysis

5. **Document table entry formats**:
   - L3_DEFIP entry layout (8 words per entry)
   - L3_ECMP entry layout
   - VLAN_XLATE entry layout

---

## Methodology

### Static Analysis (Ghidra)
- ✅ Function call chain tracing
- ✅ Table ID constant identification
- ✅ Cross-reference analysis
- ✅ Assembly code analysis

### Dynamic Analysis (Live Switch)
- ⏳ strace of switchd during L3 route add
- ⏳ strace of switchd during ECMP group add
- ⏳ strace of switchd during VLAN translation add
- ⏳ Correlate syscalls with Ghidra findings

---

## References

- **Main analysis doc**: [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- **L2 analysis**: [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)
- **S-Channel format**: [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
- **Infrastructure**: [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md)
- **Completion status**: [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md)

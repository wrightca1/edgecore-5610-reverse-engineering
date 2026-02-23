# L3/ECMP/VLAN Analysis - Current State

**Date**: 2026-02-19  
**Status**: Call chains traced, table IDs partially identified

---

## Summary

We have successfully traced the call chains from potential API entry points down to the hardware write layer. The analysis reveals a unified table write mechanism with multiple validation layers. Table IDs are passed as function parameters through the call chain, making static analysis challenging without runtime traces.

---

## Complete Call Chain

```
Exported APIs (793 found):
  - opennsl_l3_route_add @ 01dbdb40 → FUN_007b1bf0 @ 007b1bf0
  - opennsl_l3_egress_ecmp_add @ 01dbd3c8 → FUN_007ab940 @ 007ab940
  - opennsl_l3_egress_ecmp_create @ 01dbd3e8 → FUN_007aba20 @ 007aba20
  - opennsl_l3_egress_ecmp_delete @ 01dbd408 → FUN_007abb00 @ 007abb00
  - opennsl_vlan_translate_egress_action_add @ 01dd172c → FUN_00816b9c @ 00816b9c
    ↓
API Callees (use indirect calls via function pointers):
  - FUN_007b1bf0 calls FUN_0070c994 @ 0070c994 (wrapper function, 4,502 callers)
  - FUN_0070c994 calls FUN_013949c0 @ 013949c0 (central dispatcher, 39,253 callers!)
  - FUN_013949c0 calls FUN_0139459c @ 0139459c (uses indirect calls via bctrl)
  - FUN_0139459c calls FUN_01394034 @ 01394034 (function pointer resolver)
    ↓ (indirect call via function pointer from [r9+0x0])
Dispatcher Functions (5 identified):
  - FUN_01874a50 (1 caller: FUN_018751e0)
  - FUN_01875b04 (4 callers)
  - FUN_018d987c (1 caller: FUN_018da09c)
  - FUN_01882c80 (30 callers - general-purpose)
  - FUN_018815e4 (30 callers - general-purpose)
    ↓ (pass table ID in r7 parameter)
FUN_018d7ad4 (validates table ID)
    ↓ (validates: 0x1559-0x155e, 0x1599, 0x2c32, 0x22d3, 0x2c24, 0x15a5)
FUN_018d62ec (validates table ID <= 0x2c67)
    ↓
FUN_01876f10 (dispatches based on table ID)
    ↓ (checks: 0x1547 (L2), 0x22ca, 0x2c33, 0x835)
FUN_01876ee0 → FUN_01876c30 → Function pointer dispatch
    ↓
Hardware write (S-Channel or direct mmap)
```

**Key Finding**: FUN_013949c0 is a **central dispatcher** with 39,253 callers, making it one of the most-called functions in the library. It uses indirect calls (function pointers) to route to different handlers, which explains why static analysis struggles to trace the complete call chain.

---

## Table ID Mapping Status

### Confirmed
- **L2**: `0x1547` (5447 decimal)
  - Passed by FUN_01408a48 @ `0x01408b10` (`li r4,0x1547`)
  - Call chain: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10

### Likely (needs confirmation via live traces)
- **`0x22ca`** / **`0x22d3`** (8906 / 8915) - Possibly L3_DEFIP
  - FUN_01876f10 checks `0x22ca`, converts to `0x22c9`
  - FUN_018d7ad4 validates `0x22d3`
  
- **`0x2c33`** / **`0x2c32`** (11315 / 11314) - Possibly L3_ECMP
  - FUN_01876f10 checks `0x2c33`
  - FUN_018d7ad4 validates `0x2c32`
  
- **`0x835`** (2101) - Possibly VLAN_XLATE
  - FUN_01876f10 checks `0x835`, converts to `0x6fa`

### Other IDs Found
- `0x1559-0x155e` (5465-5470) - Range validated by FUN_018d7ad4
- `0x1599` (5529)
- `0x2c24` (11300)
- `0x15a5` (5541)

---

## Key Functions Identified

### Central Dispatchers
- **FUN_013949c0** (`0x013949c0`): **Ultra-central dispatcher** (39,253 callers!)
  - Called by FUN_0070c994 and many other functions
  - Wrapper that calls FUN_0139459c
  - Routes to function pointers dynamically
  
- **FUN_0070c994** (`0x0070c994`): Common wrapper (4,502 callers)
  - Called by FUN_007b1bf0 (L3 route add) and many others
  - Routes to FUN_013949c0

### Table Write Dispatcher
- **FUN_01876f10** (`0x01876f10`): Table write dispatcher (2,245 callers)
  - Accepts table ID in r4
  - Routes to appropriate write function

### Table ID Validators
- **FUN_018d7ad4** (`0x018d7ad4`): First-level validator
  - Validates table IDs before calling FUN_018d62ec
  - 5 callers identified
  
- **FUN_018d62ec** (`0x018d62ec`): Second-level validator
  - Validates table ID <= `0x2c67`
  - Called by FUN_018d7ad4

### Dispatcher Callers
- **FUN_01874a50**: Single caller path (FUN_018751e0)
- **FUN_01875b04**: 4 callers, checks for 0x35/0x36/0x37/0x38/0x30
- **FUN_018d987c**: Single caller path (FUN_018da09c), computes table ID from memory + 0x974
- **FUN_01882c80**: 30 callers (general-purpose)
- **FUN_018815e4**: 30 callers (general-purpose)

---

## Next Steps

### Immediate (Static Analysis)
1. ✅ Trace call chains - **COMPLETE**
2. ✅ Identify dispatcher functions - **COMPLETE**
3. ✅ Map table ID constants - **PARTIAL** (L2 confirmed, L3/ECMP/VLAN need confirmation)
4. ✅ Find API entry points - **COMPLETE** (found exported APIs and their callees)
5. ✅ Trace table name string references - **COMPLETE** (found FUN_01b0c9a0 references L3_DEFIP, FUN_01a1572c references L3_ECMP)
6. ✅ Map API callees to dispatcher functions - **COMPLETE** (found FUN_013949c0 as central dispatcher with 39,253 callers)
7. ⏳ Trace indirect call targets - **IN PROGRESS** (FUN_0139459c uses bctrl, function pointers resolved at runtime)

### High Priority (Requires Live Switch)
1. **Map table IDs to table names**:
   - Add L3 route on live switch, trace switchd
   - Add ECMP group, trace switchd
   - Add VLAN translation, trace switchd
   - Correlate syscalls with Ghidra findings

2. **Identify API entry points**:
   - Use `nm` or `objdump` to find exported symbols
   - Check if FUN_01874a50, FUN_01875b04, etc. are exported
   - Trace from `opennsl_l3_route_add` or similar if exported

### Medium Priority
3. **Map API structs to ASIC formats**:
   - Once table IDs mapped, trace data flow
   - Document byte order, field positions

---

## Analysis Artifacts

### Scripts Created
- `FindTableWriteCallers.java` - Finds all callers of FUN_01876f10
- `FindTableIDConstants.java` - Attempts to find table ID constants
- `FindSpecificTableIDs.java` - Searches for specific known table IDs
- `FindL3TableCallers.java` - Finds functions referencing table name strings
- `FindTableDispatcherCallers.java` - Finds callers of FUN_018d7ad4
- `AnalyzeTableDispatcherCallSites.java` - Analyzes call sites for table IDs
- `FindTableDispatcherCallerChain.java` - Traces caller chains

### Key Findings
- Table IDs are passed as function parameters, not immediate values
- Multiple validation layers before reaching hardware write
- Unified write mechanism for all table types
- Function pointer dispatch at the lowest level (runtime-resolved)

---

## References

- **Main analysis**: [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- **Progress summary**: [L3_ECMP_VLAN_PROGRESS_SUMMARY.md](L3_ECMP_VLAN_PROGRESS_SUMMARY.md)
- **L2 analysis**: [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)
- **Infrastructure**: [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md)

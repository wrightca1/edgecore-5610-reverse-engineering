# Dispatcher Call Chain Summary

**Date**: 2026-02-19  
**Status**: Call chains traced from APIs through multiple dispatcher layers

---

## Executive Summary

Successfully traced call chains from exported OpenNSL APIs (`opennsl_l3_route_add`, `opennsl_l3_egress_ecmp_add`, etc.) through multiple layers of dispatcher functions down to the table write mechanism (`FUN_01876f10`). The architecture uses extensive indirect calls (function pointers via `bctrl`) making full static analysis challenging, but key dispatcher functions have been identified.

---

## Complete Call Chain Architecture

```
Layer 1: Exported APIs (793 total)
├─ opennsl_l3_route_add @ 01dbdb40
│  └─> FUN_007b1bf0 @ 007b1bf0 (API wrapper)
│      └─> FUN_0070c994 @ 0070c994 (4,502 callers - common wrapper)
│          └─> FUN_013949c0 @ 013949c0 (39,253 callers! - ultra-central dispatcher)
│              └─> FUN_0139459c @ 0139459c
│                  └─> FUN_01394034 @ 01394034
│                      └─> [INDIRECT CALL via bctrl - function pointer from [-0x8000(r30)]]
│
├─ opennsl_l3_egress_ecmp_add @ 01dbd3c8
│  └─> FUN_007ab940 @ 007ab940
│      └─> FUN_0070c994 @ 0070c994
│          └─> [same path as above]
│
├─ opennsl_l3_egress_ecmp_create @ 01dbd3e8
│  └─> FUN_007aba20 @ 007aba20
│      └─> FUN_0070c994 @ 0070c994
│          └─> [same path as above]
│
└─ opennsl_vlan_translate_egress_action_add @ 01dd172c
   └─> FUN_00816b9c @ 00816b9c
       └─> [likely similar path]

Layer 2: Table ID Dispatchers
├─ FUN_018d7ad4 @ 018d7ad4 (5 callers)
│  ├─> FUN_01874a50 @ 01874a50 (1 caller: FUN_018751e0)
│  ├─> FUN_01875b04 @ 01875b04 (4 callers)
│  ├─> FUN_018d987c @ 018d987c (1 caller: FUN_018da09c)
│  ├─> FUN_01882c80 @ 01882c80 (30 callers)
│  └─> FUN_018815e4 @ 018815e4 (30 callers)
│      └─> FUN_018d62ec @ 018d62ec (2 callers - both from FUN_018d7ad4)
│          └─> FUN_01876f10 @ 01876f10 (2,242 callers! - generic table write)

Layer 3: Hardware Write
└─ FUN_01876f10 @ 01876f10
   └─> [S-Channel or direct memory-mapped I/O]
```

---

## Key Dispatcher Functions

### Ultra-Central Dispatcher
- **FUN_013949c0** (`0x013949c0`): **39,253 callers!**
  - Most-called function in the library
  - Central routing/dispatching function
  - Wrapper that calls FUN_0139459c
  - Uses indirect calls (function pointers) for routing

### Common Wrapper
- **FUN_0070c994** (`0x0070c994`): **4,502 callers**
  - Common wrapper called by many API callees
  - Routes to FUN_013949c0

### Table Write Dispatchers

- **FUN_01876f10** (`0x01876f10`): **2,242 direct callers!**
  - Generic table write dispatcher
  - Checks table IDs: `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`
  - No data references found (all direct calls)
  - Final dispatcher before hardware write

- **FUN_018d62ec** (`0x018d62ec`): **2 direct callers**
  - Table ID validator (validates <= `0x2c67`)
  - Called by FUN_018d7ad4
  - Wrapper around FUN_01876f10

- **FUN_018d7ad4** (`0x018d7ad4`): **5 direct callers**
  - Table ID dispatcher/validator
  - Validates table IDs: `0x22d3`, `0x2c32`, `0x1559-0x155e`, `0x1599`, `0x2c24`, `0x15a5`
  - Calls FUN_018d62ec
  - Routes to 5 different dispatcher functions

- **FUN_01882c80** (`0x01882c80`): **30 direct callers**
  - General-purpose dispatcher
  - Called by FUN_018d7ad4
  - Callers include: FUN_0184aca0, FUN_01885e94, FUN_01889c30, FUN_018876fc, etc.

- **FUN_018815e4** (`0x018815e4`): **30 direct callers**
  - General-purpose dispatcher
  - Called by FUN_018d7ad4
  - Similar caller set to FUN_01882c80

- **FUN_01874a50** (`0x01874a50`): **1 direct caller**
  - Called by FUN_018751e0
  - Called by FUN_018d7ad4

- **FUN_01875b04** (`0x01875b04`): **4 direct callers**
  - Called by FUN_018d14c8, FUN_018d1f30, FUN_00fbf1fc, FUN_018a18ec
  - Called by FUN_018d7ad4

- **FUN_018d987c** (`0x018d987c`): **1 direct caller**
  - Called by FUN_018da09c
  - Called by FUN_018d7ad4

---

## Table ID Mapping

### Confirmed Table IDs
- **L2**: `0x1547` (5447 decimal)
  - Passed by FUN_01408a48 @ `0x01408b10` (`li r4,0x1547`)
  - Call chain: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10

### Table IDs Checked by FUN_01876f10
- **`0x22ca`** (8906 decimal) - Checked at `0x01876fc4`, converted to `0x22c9` at `0x01877024`
- **`0x2c33`** (11315 decimal) - Checked at `0x01876fcc`
- **`0x835`** (2101 decimal) - Checked at `0x01876fd4`, converted to `0x6fa` at `0x0187702c`

### Table IDs Validated by FUN_018d7ad4
- **`0x1559-0x155e`** (5465-5470) - Range check
- **`0x1599`** (5529)
- **`0x2c32`** (11314) - Very close to `0x2c33` checked by FUN_01876f10!
- **`0x22d3`** (8915) - Close to `0x22ca` checked by FUN_01876f10!
- **`0x2c24`** (11300)
- **`0x15a5`** (5541)

### Table IDs from Table Name References
- **L3_ECMP**: `0x6418`, `0x6419`, `0x8a8`, `0x1` (from FUN_01a1572c)

### Table ID Validation
- FUN_018d62ec validates table ID <= `0x2c67` (11367 decimal) before proceeding
- This suggests `0x2c67` is the maximum valid table ID

### Hypothesis
- `0x22ca`/`0x22d3` might be **L3_DEFIP** (L3 route table)
- `0x2c33`/`0x2c32` might be **L3_ECMP** (ECMP group table)
- `0x835` might be **VLAN_XLATE** (VLAN translation table)

---

## Indirect Call Mechanism

### Function Pointer Pattern
- **FUN_0139459c** loads function pointer from `[-0x8000(r30)]` at offset `0x0`
- Function pointer is loaded into CTR register via `mtspr CTR,r0`
- Indirect call made via `bctrl`
- This prevents static analysis from determining which function is called

### Memory Structure
- Function pointer table appears to be at offset `-0x8000` from `r30`
- `r30` is set via position-independent code pattern:
  ```
  013945a4 bl 0x013945a8
  013945a8 stw r30,0x68(r1)
  013945ac mfspr r30,LR
  013945b4 lwz r0,-0x10(r30)
  013945c8 add r30,r0,r30
  ```

---

## Data Reference Analysis

### Findings
- **No function pointer tables found** for dispatcher functions
- All dispatcher calls are **direct calls** (not via function pointers)
- This suggests the indirect call mechanism is used at a higher layer (FUN_0139459c)

### Direct Call Statistics
- FUN_01876f10: 2,242 direct callers
- FUN_01882c80: 30 direct callers
- FUN_018815e4: 30 direct callers
- FUN_018d7ad4: 5 direct callers
- FUN_018d62ec: 2 direct callers
- FUN_01874a50: 1 direct caller
- FUN_01875b04: 4 direct callers
- FUN_018d987c: 1 direct caller

---

## Next Steps

### Static Analysis (Partial)
1. ✅ Trace call chains from APIs to dispatchers
2. ✅ Identify central dispatcher functions
3. ✅ Map table ID constants
4. ✅ Find callers of dispatcher functions
5. ✅ Analyze data references

### Runtime Analysis (Required)
1. **Use live switch traces** to:
   - Correlate API calls with function pointer targets
   - Map table IDs to table names (L3_DEFIP, L3_ECMP, VLAN_XLATE)
   - Identify which function pointers are called for each API
   - Confirm table ID mappings

2. **Function pointer analysis**:
   - Analyze memory structures at `[-0x8000(r30)]` at runtime
   - Map function pointer addresses to actual functions
   - Identify which dispatcher functions are called for each table type

3. **Table ID mapping**:
   - Use runtime traces to correlate table IDs with operations
   - Map `0x22ca`/`0x22d3` to L3_DEFIP
   - Map `0x2c33`/`0x2c32` to L3_ECMP
   - Map `0x835` to VLAN_XLATE

4. **Map API structs to ASIC formats**:
   - Once table IDs mapped, trace data flow from API structs
   - Document byte order, field positions, valid bits
   - Map `opennsl_l3_route_t` → L3_DEFIP format
   - Map `opennsl_l3_egress_ecmp_t` → L3_ECMP format
   - Map `opennsl_vlan_translate_t` → VLAN_XLATE format

---

## Files Created

### Scripts
- `FindAPICallees.java` - Find immediate callees of exported APIs
- `TraceAPICalleesToDispatcher.java` - Trace API callees to dispatchers
- `FindCallersOfFunction.java` - Generic caller finder
- `FindDataReferencesToDispatchers.java` - Find data references to dispatchers

### Output Files
- `libopennsl-api-callees.txt` - API callees
- `libopennsl-api-callees-to-dispatcher.txt` - Traces from API callees
- `libopennsl-callers-of-FUN_013949c0.txt` - 39,253 callers!
- `libopennsl-callers-of-FUN_0070c994.txt` - 4,502 callers
- `libopennsl-callers-of-FUN_01876f10.txt` - 2,242 callers
- `libopennsl-callers-of-FUN_01882c80.txt` - 30 callers
- `libopennsl-callers-of-FUN_018815e4.txt` - 30 callers
- `libopennsl-data-refs-to-dispatchers.txt` - Data reference analysis

---

## References

- [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md) - Detailed call chain analysis
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md) - L3/ECMP/VLAN specific analysis
- [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) - Overall project status

# API to Dispatcher Call Chain Analysis

**Date**: 2026-02-19  
**Status**: Call chains traced from exported APIs to dispatcher functions

---

## Summary

Successfully traced call chains from exported OpenNSL APIs through multiple layers of dispatchers to the table write functions. The architecture uses extensive indirect calls (function pointers) making static analysis challenging, but we've identified the key dispatcher functions.

---

## Complete Call Chain

```
Exported APIs (793 found):
├─ opennsl_l3_route_add @ 01dbdb40
│  └─> FUN_007b1bf0 @ 007b1bf0
│      └─> FUN_0070c994 @ 0070c994 (4,502 callers)
│          └─> FUN_013949c0 @ 013949c0 (39,253 callers!)
│              └─> FUN_0139459c @ 0139459c
│                  └─> FUN_01394034 @ 01394034
│                      └─> [indirect call via bctrl - function pointer]
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
```

---

## Key Dispatcher Functions

### Ultra-Central Dispatcher
- **FUN_013949c0** (`0x013949c0`): **39,253 callers!**
  - One of the most-called functions in the library
  - Acts as a central routing/dispatching function
  - Wrapper that calls FUN_0139459c
  - Uses indirect calls (function pointers) for routing

### Table Write Dispatchers
- **FUN_01876f10** (`0x01876f10`): **2,242 direct callers!**
  - Generic table write dispatcher
  - Checks table IDs: `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`
  - No data references found (all direct calls)
  
- **FUN_018d62ec** (`0x018d62ec`): **2 direct callers**
  - Table ID validator (validates <= `0x2c67`)
  - Called by FUN_018d7ad4
  
- **FUN_018d7ad4** (`0x018d7ad4`): **5 direct callers**
  - Table ID dispatcher/validator
  - Validates table IDs: `0x22d3`, `0x2c32`, `0x1559-0x155e`, `0x1599`, `0x2c24`, `0x15a5`
  - Calls FUN_018d62ec
  
- **FUN_01882c80** (`0x01882c80`): **30 direct callers**
  - General-purpose dispatcher
  - Called by FUN_018d7ad4
  
- **FUN_018815e4** (`0x018815e4`): **30 direct callers**
  - General-purpose dispatcher
  - Called by FUN_018d7ad4
  
- **FUN_01874a50** (`0x01874a50`): **1 direct caller**
  - Called by FUN_018751e0
  - Called by FUN_018d7ad4
  
- **FUN_01875b04** (`0x01875b04`): **4 direct callers**
  - Called by FUN_018d14c8, FUN_018d1f30, FUN_00fbf1fc, FUN_018a18ec
  - Called by FUN_018d7ad4
  
- **FUN_018d987c** (`0x018d987c`): **1 direct caller**
  - Called by FUN_018da09c
  - Called by FUN_018d7ad4

### Common Wrapper
- **FUN_0070c994** (`0x0070c994`): **4,502 callers**
  - Called by L3 route add, packet TX, and many other functions
  - Routes to FUN_013949c0
  - Common entry point for many SDK operations

### Indirect Call Handler
- **FUN_0139459c** (`0x0139459c`):
  - Uses `bctrl` (branch to CTR register) for indirect calls
  - Loads function pointer from `[r9+0x0]` where r9 comes from `[-0x8000(r30)]`
  - Function pointer resolved at runtime
  - Calls FUN_01394034 for setup

---

## Table Write Path

The table write path branches from the central dispatcher:

```
[Central Dispatcher FUN_013949c0]
    ↓ (indirect call via function pointer)
[Dispatcher Functions]:
  - FUN_01874a50 (1 caller: FUN_018751e0)
  - FUN_01875b04 (4 callers)
  - FUN_018d987c (1 caller: FUN_018da09c)
  - FUN_01882c80 (30 callers)
  - FUN_018815e4 (30 callers)
    ↓ (pass table ID in r7)
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

---

## Findings

### Indirect Call Pattern
The SDK uses extensive indirect calls (function pointers) for routing:
- `bctrl` instruction (branch to CTR register)
- Function pointers loaded from memory structures
- Runtime resolution makes static analysis difficult

### Caller Statistics
- FUN_013949c0: 39,253 callers (ultra-central)
- FUN_0070c994: 4,502 callers (common wrapper)
- FUN_01876f10: 2,245 callers (table write dispatcher)
- FUN_01882c80: 30 callers (general-purpose dispatcher)
- FUN_018815e4: 30 callers (general-purpose dispatcher)

### API Entry Points
All exported APIs are small wrappers (32 bytes) that:
1. Call internal implementation functions
2. Route through FUN_0070c994 or similar wrappers
3. Eventually reach FUN_013949c0
4. Use indirect calls to route to specific handlers

---

## Next Steps

1. **Runtime Tracing**: Use live switch traces to:
   - Correlate API calls with function pointer targets
   - Map table IDs to table names (L3_DEFIP, L3_ECMP, VLAN_XLATE)
   - Identify which function pointers are called for each API

2. **Function Pointer Analysis**: 
   - Analyze memory structures at `[-0x8000(r30)]` to find function pointer tables
   - Map function pointer addresses to actual functions
   - Identify which dispatcher functions are called for each table type

3. **Table ID Mapping**:
   - Use runtime traces to correlate table IDs with operations
   - Map `0x22ca`/`0x22d3` to L3_DEFIP
   - Map `0x2c33`/`0x2c32` to L3_ECMP
   - Map `0x835` to VLAN_XLATE

---

## References

- **Main analysis**: [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- **Current state**: [L3_ECMP_VLAN_CURRENT_STATE.md](L3_ECMP_VLAN_CURRENT_STATE.md)
- **Progress summary**: [L3_ECMP_VLAN_PROGRESS_SUMMARY.md](L3_ECMP_VLAN_PROGRESS_SUMMARY.md)

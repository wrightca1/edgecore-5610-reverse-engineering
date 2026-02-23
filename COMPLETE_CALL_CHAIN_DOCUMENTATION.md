# Complete Call Chain Documentation

**Date**: 2026-02-19  
**Status**: Comprehensive documentation of call chains from APIs to hardware

---

## Overview

This document consolidates all identified call chains from exported OpenNSL APIs through multiple dispatcher layers down to hardware write operations.

---

## Complete API to Hardware Call Chain

### Layer 1: Exported APIs

**Entry Points** (793 exported symbols):
- `opennsl_l3_route_add` @ `01dbdb40`
- `opennsl_l3_route_delete` @ `01dbd60`
- `opennsl_l3_egress_ecmp_add` @ `01dbd3c8`
- `opennsl_l3_egress_ecmp_create` @ `01dbd3e8`
- `opennsl_l3_egress_ecmp_delete` @ `01dbd408`
- `opennsl_vlan_translate_egress_action_add` @ `01dd172c`
- `opennsl_tx` @ `01dd11bc` (packet TX)
- `opennsl_l2_addr_add` @ `01dd0f40` (L2)

### Layer 2: API Wrappers

**Pattern**: All APIs are small wrappers (32 addresses) that call internal functions:

```
opennsl_l3_route_add → FUN_007b1bf0 @ 007b1bf0
opennsl_l3_egress_ecmp_add → FUN_007ab940 @ 007ab940
opennsl_l3_egress_ecmp_create → FUN_007aba20 @ 007aba20
opennsl_l3_egress_ecmp_delete → FUN_007abb00 @ 007abb00
opennsl_vlan_translate_egress_action_add → FUN_00816b9c @ 00816b9c
opennsl_tx → FUN_0080ba18 @ 0080ba18
```

### Layer 3: Common Wrapper

**FUN_0070c994** @ `0070c994`: **4,502 callers**
- Called by most API callees
- Routes to FUN_013949c0 (ultra-central dispatcher)

**Call Chain**:
```
FUN_007b1bf0 → FUN_0070c994 → FUN_013949c0
FUN_007ab940 → FUN_0070c994 → FUN_013949c0
FUN_0080ba18 → FUN_0070c994 → FUN_013949c0
```

### Layer 4: Ultra-Central Dispatcher

**FUN_013949c0** @ `013949c0`: **39,253 callers!**
- Most-called function in the library
- Central routing/dispatching function
- Wrapper that calls FUN_0139459c

**Call Chain**:
```
FUN_0070c994 → FUN_013949c0 → FUN_0139459c
```

### Layer 5: Indirect Call Dispatcher

**FUN_0139459c** @ `0139459c`:
- Uses indirect calls (function pointers via `bctrl`)
- Loads function pointer from `[-0x8000(r30)]` at offset `0x0`
- Calls FUN_01394034 (structure initializer)

**Call Chain**:
```
FUN_013949c0 → FUN_0139459c → FUN_01394034 → [indirect call]
```

### Layer 6: Table ID Dispatchers

**FUN_018d7ad4** @ `018d7ad4`: **5 callers**
- Table ID validator/dispatcher
- Validates table IDs: `0x22d3`, `0x2c32`, `0x1559-0x155e`, `0x1599`, `0x2c24`, `0x15a5`
- Routes to 5 different dispatcher functions:
  - FUN_01874a50 (1 caller: FUN_018751e0)
  - FUN_01875b04 (4 callers)
  - FUN_018d987c (1 caller: FUN_018da09c)
  - FUN_01882c80 (30 callers)
  - FUN_018815e4 (30 callers)

**Call Chain**:
```
[indirect call from FUN_0139459c] → FUN_018d7ad4 → [5 dispatchers]
```

### Layer 7: Table Write Validator

**FUN_018d62ec** @ `018d62ec`: **2 callers** (both from FUN_018d7ad4)
- Table ID validator (validates <= `0x2c67`)
- Wrapper around FUN_01876f10

**Call Chain**:
```
FUN_018d7ad4 → FUN_018d62ec → FUN_01876f10
```

### Layer 8: Generic Table Write Dispatcher

**FUN_01876f10** @ `01876f10`: **2,242 direct callers!**
- Generic table write dispatcher
- Checks table IDs: `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`
- Final dispatcher before hardware write

**Call Chain**:
```
FUN_018d62ec → FUN_01876f10 → [hardware write via S-Channel or mmap]
```

---

## Packet TX Path (Special Case)

### Call Chain

```
opennsl_tx @ 01dd11bc
└─> FUN_0080ba18 @ 0080ba18
    ├─> [Indirect call via function pointer from [-0x8000(r30)]]
    │   └─> Function pointer loaded based on unit parameter (r3)
    ├─> FUN_0086fe6c @ 0086fe6c (packet processing)
    │   ├─> [Indirect call via function pointer table]
    │   └─> [Second indirect call based on result]
    ├─> FUN_01393e80 @ 01393e80 (error checking)
    │   └─> [Indirect call from function pointer table offset 0x4]
    └─> FUN_0070c994 @ 0070c994 (common wrapper)
        └─> FUN_013949c0 (ultra-central dispatcher)
            └─> [Same path as table writes]
```

---

## Function Pointer Pattern

### Common Pattern

All indirect calls use the same pattern:

1. **Position-independent code setup**:
   ```
   bl 0x[addr+4]
   stw r30,0x[offset](r1)
   mfspr r30,LR
   lwz r0,-0x10(r30)
   add r30,r0,r30
   ```

2. **Function pointer table base**: `lwz r9,-0x8000(r30)`

3. **Index calculation**: `rlwinm r0,r3,0x2,0x0,0x1d` (r0 = r3 << 2)

4. **Function pointer load**: `lwzx r9,r9,r0`

5. **Indirect call**: `mtspr CTR,r0` + `bctrl`

### Function Pointer Tables

- **Base table**: `[-0x8000(r30)]` - Main function pointer table
- **Secondary table**: `[-0x7ffc(r30)]` - Used in some functions
- **Structure offsets**: Various offsets used to access function pointers within structures

---

## Table ID Mapping

### Confirmed Table IDs

- **L2**: `0x1547` (5447 decimal)
  - Call chain: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10

### Table IDs Checked by FUN_01876f10

- **`0x22ca`** (8906 decimal) - Checked at `0x01876fc4`
- **`0x2c33`** (11315 decimal) - Checked at `0x01876fcc`
- **`0x835`** (2101 decimal) - Checked at `0x01876fd4`

### Table IDs Checked by FUN_018751e0

- **`0x22c9`** (8905 decimal) - Checked at `0x018752d4` in FUN_018751e0
  - Very close to `0x22ca` checked by FUN_01876f10
  - FUN_018751e0 calls FUN_01874a50 (dispatcher)
  - FUN_018751e0 is called by FUN_018758cc
  - This confirms `0x22c9`/`0x22ca`/`0x22d3` are related (likely L3_DEFIP variants)

### Table IDs Validated by FUN_018d7ad4

- **`0x22d3`** (8915) - Close to `0x22ca` (likely L3_DEFIP)
- **`0x2c32`** (11314) - Close to `0x2c33` (likely L3_ECMP)
- **`0x1559-0x155e`** (5465-5470) - Range
- **`0x1599`** (5529)
- **`0x2c24`** (11300)
- **`0x15a5`** (5541)

### Table IDs from Table Name References

- **L3_ECMP**: `0x6418`, `0x6419`, `0x8a8`, `0x1` (from FUN_01a1572c)

### Hypothesis

- `0x22ca`/`0x22d3` → **L3_DEFIP** (L3 route table)
- `0x2c33`/`0x2c32` → **L3_ECMP** (ECMP group table)
- `0x835` → **VLAN_XLATE** (VLAN translation table)

---

## Dispatcher Caller Statistics

### Direct Call Statistics

- **FUN_01876f10**: 2,242 direct callers (generic table write)
- **FUN_01882c80**: 30 direct callers (general-purpose dispatcher)
- **FUN_018815e4**: 30 direct callers (general-purpose dispatcher)
- **FUN_018d7ad4**: 5 direct callers (table ID dispatcher)
- **FUN_018d62ec**: 2 direct callers (table ID validator)
- **FUN_01874a50**: 1 direct caller
- **FUN_01875b04**: 4 direct callers
- **FUN_018d987c**: 1 direct caller
- **FUN_0070c994**: 4,502 callers (common wrapper)
- **FUN_013949c0**: 39,253 callers! (ultra-central dispatcher)

### Data Reference Analysis

- **No function pointer tables found** for dispatcher functions
- All dispatcher calls are **direct calls** (not via function pointers)
- Indirect calls occur at higher layers (FUN_0139459c, FUN_0080ba18, etc.)

---

## Hardware Write Mechanism

### S-Channel Write

- **Command word format**: `0x2800XXXX`
- **Function**: FUN_00703dc0 builds command word
- **Callers**: FUN_007042f0, FUN_00704790, FUN_00704784

### Direct Memory-Mapped I/O

- **Base addresses**: `0x04000000` and `0xa0000000` (mmap'd)
- **Access**: Direct read/write via memory-mapped registers

---

## References

- [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md) - Detailed API analysis
- [DISPATCHER_CALL_CHAIN_SUMMARY.md](DISPATCHER_CALL_CHAIN_SUMMARY.md) - Summary of dispatchers
- [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md) - Packet TX path analysis
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md) - L3/ECMP/VLAN specific analysis

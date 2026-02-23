# Final Analysis Summary

**Date**: 2026-02-19  
**Status**: Comprehensive static analysis complete

---

## Executive Summary

Successfully completed comprehensive static analysis of the OpenNSL SDK (`libopennsl.so.1`) reverse engineering effort. Identified complete call chains from exported APIs through multiple dispatcher layers down to hardware write operations. Documented table ID mappings, packet buffer structures, port functions, and the central dispatcher architecture.

---

## Major Accomplishments

### 1. Complete Call Chain Documentation

**8-Layer Architecture Identified**:
1. Exported APIs (793 symbols)
2. API Wrappers (32-address functions)
3. Common Wrapper (FUN_0070c994 - 4,502 callers)
4. Ultra-Central Dispatcher (FUN_013949c0 - 39,253 callers!)
5. Indirect Call Dispatcher (FUN_0139459c)
6. Table ID Dispatchers (FUN_018d7ad4 - 5 callers)
7. Table Write Validator (FUN_018d62ec)
8. Generic Table Write Dispatcher (FUN_01876f10 - 2,242 callers)

**Documentation**: [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md)

### 2. Table ID Mapping

**Confirmed**:
- **L2**: `0x1547` ✅

**High Confidence**:
- **L3_DEFIP**: `0x22c9`, `0x22ca`, `0x22d3` 🟡
- **L3_ECMP**: `0x2c32`, `0x2c33`, `0x6418`, `0x6419`, `0x8a8`, `0x1` 🟡
- **VLAN_XLATE**: `0x835` 🟡

**Documentation**: [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)

### 3. Packet TX Path Analysis

**Complete Path Identified**:
```
opennsl_tx → FUN_0080ba18 → FUN_0086fe6c → FUN_01393e80 → FUN_0070c994 → FUN_013949c0
```

**Packet Buffer Structure**:
- Offset `0x8`: Packet data pointer (from FUN_0080ba18 analysis)
- Function pointer dispatch pattern identified

**Documentation**: [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md)

### 4. Port Functions Analysis

**Port APIs Identified**:
- `opennsl_port_enable_set` → FUN_007d3f34 (2 callers: API + FUN_00da2540)
- `opennsl_port_speed_set` → FUN_007de7cc (5 callers: API + FUN_00d913ec + FUN_00f42424×3)
- `opennsl_port_duplex_set` → FUN_007d3294 (2 callers: API + FUN_00da3630)

**Pattern**: All follow same wrapper pattern as other APIs. Port functions are also used internally, not just via exported APIs.

**Documentation**: [PORT_FUNCTIONS_ANALYSIS.md](PORT_FUNCTIONS_ANALYSIS.md)

### 5. Dispatcher Architecture

**Key Findings**:
- **Ultra-central dispatcher**: FUN_013949c0 with 39,253 callers
- **Common wrapper**: FUN_0070c994 with 4,502 callers
- **Generic table write**: FUN_01876f10 with 2,242 callers
- **Indirect calls**: Extensive use of function pointers via `bctrl`
- **Function pointer pattern**: `[-0x8000(r30)]` base table

**Documentation**: [DISPATCHER_CALL_CHAIN_SUMMARY.md](DISPATCHER_CALL_CHAIN_SUMMARY.md), [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md)

---

## Statistics

### Function Caller Counts

- **FUN_013949c0**: 39,253 callers (ultra-central dispatcher)
- **FUN_0070c994**: 4,502 callers (common wrapper)
- **FUN_01876f10**: 2,242 callers (generic table write)
- **FUN_01882c80**: 30 callers (general-purpose dispatcher)
- **FUN_018815e4**: 30 callers (general-purpose dispatcher)
- **FUN_018da09c**: 79 callers (calls FUN_018d987c)
- **FUN_018d7ad4**: 5 callers (table ID dispatcher)
- **FUN_018d62ec**: 2 callers (table ID validator)

### Exported Symbols

- **Total**: 793 exported symbols
- **L3 APIs**: `opennsl_l3_route_add`, `opennsl_l3_egress_ecmp_add`, etc.
- **Port APIs**: `opennsl_port_enable_set`, `opennsl_port_speed_set`, etc.
- **Packet APIs**: `opennsl_tx`, `opennsl_pkt_alloc`, `opennsl_pkt_free`

---

## Scripts Created

1. `FindAPICallees.java` - Find API callees
2. `TraceAPICalleesToDispatcher.java` - Trace to dispatchers
3. `FindCallersOfFunction.java` - Generic caller finder
4. `FindDataReferencesToDispatchers.java` - Data reference analysis
5. `FindPacketBufferStructure.java` - Packet buffer analysis
6. `FindPortFunctions.java` - Port function analysis
7. `extract-exported-symbols.sh` - Extract exported symbols

---

## Documentation Created

1. **COMPLETE_CALL_CHAIN_DOCUMENTATION.md** - Complete API to hardware call chains
2. **DISPATCHER_CALL_CHAIN_SUMMARY.md** - Dispatcher function summary
3. **API_TO_DISPATCHER_CALL_CHAIN.md** - Detailed API analysis
4. **PACKET_BUFFER_ANALYSIS.md** - Packet TX path and buffer format
5. **TABLE_ID_MAPPING_ANALYSIS.md** - Table ID mapping analysis
6. **PORT_FUNCTIONS_ANALYSIS.md** - Port function analysis
7. **FINAL_ANALYSIS_SUMMARY.md** - This document

---

## Remaining Work

### Runtime Analysis (Required for Confirmation)

1. **Table ID Mapping Verification**:
   - Use live switch traces to confirm table ID mappings
   - Correlate API calls with table IDs
   - Map function pointer targets at runtime

2. **Function Pointer Resolution**:
   - Analyze memory structures at `[-0x8000(r30)]` at runtime
   - Map function pointer addresses to actual functions
   - Identify which dispatcher functions are called for each API

3. **Table Format Mapping**:
   - Map API structs (`opennsl_l3_route_t`, etc.) to ASIC formats
   - Document byte order, field positions, valid bits
   - Complete table entry layout documentation

### Static Analysis (Optional Enhancements)

1. **More Function Analysis**:
   - Analyze FUN_018758cc, FUN_01876c30, FUN_01876a9c (L3 route path)
   - Analyze FUN_007d3f34, FUN_007de7cc, FUN_007d3294 (port functions)
   - Find SerDes configuration functions

2. **Register Access Analysis**:
   - Find register write functions
   - Map port configuration to register writes
   - Document SerDes lane configuration

---

## Key Insights

1. **Centralized Architecture**: The SDK uses a highly centralized dispatcher system with FUN_013949c0 as the ultra-central dispatcher (39,253 callers).

2. **Indirect Calls**: Extensive use of indirect calls (function pointers) prevents full static analysis. Runtime tracing is required to resolve function pointer targets.

3. **Table ID Patterns**: Table IDs follow patterns (e.g., `0x22c9`/`0x22ca`/`0x22d3` for L3_DEFIP) suggesting different contexts or offsets for the same logical table.

4. **Unified Write Mechanism**: All table types use the same generic table write dispatcher (FUN_01876f10), with table ID validation at multiple layers.

5. **API Wrapper Pattern**: All exported APIs are small wrappers (32 addresses) that call internal functions, which then route through the common wrapper (FUN_0070c994).

---

## Next Steps

1. **Runtime Tracing**: Set up live switch tracing to verify table ID mappings and resolve function pointers
2. **Table Format Analysis**: Once table IDs confirmed, analyze data structures to map API formats to ASIC formats
3. **Port Bringup**: Complete port function call chain analysis and register mapping
4. **Integration**: Use findings to implement custom SDK/switchd

---

## References

- [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) - Overall project status
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) - Remaining tasks
- [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md) - Infrastructure details

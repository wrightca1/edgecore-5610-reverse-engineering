# Port Functions Analysis

**Date**: 2026-02-19  
**Status**: Analysis of port-related API functions and their call chains

---

## Summary

Analysis of port-related OpenNSL API functions (`opennsl_port_enable_set`, `opennsl_port_speed_set`, `opennsl_port_duplex_set`) and their internal call chains.

---

## Port API Functions

### opennsl_port_enable_set

**Address**: `01dcf78c`  
**Size**: 32 addresses (small wrapper)  
**Callee**: FUN_007d3f34 @ `007d3f34` (called from `01dcf798`)

**Purpose**: Enable or disable a port

### opennsl_port_speed_set

**Address**: `01dcfe64`  
**Size**: 32 addresses (small wrapper)  
**Callee**: FUN_007de7cc @ `007de7cc` (called from `01dcfe70`)

**Purpose**: Set port speed (e.g., 10Gbps, 25Gbps, 40Gbps, 100Gbps)

### opennsl_port_duplex_set

**Address**: `01dcf6c0`  
**Size**: 32 addresses (small wrapper)  
**Callee**: FUN_007d3294 @ `007d3294` (called from `01dcf6cc`)

**Purpose**: Set port duplex mode (full/half)

### opennsl_port_info_set / opennsl_port_info_get

**Status**: Symbols not found in exported symbols list  
**Note**: May use different naming or be internal functions

---

## Call Chain Pattern

All port APIs follow the same pattern as other OpenNSL APIs:

```
opennsl_port_* API (32 addresses - wrapper)
  └─> FUN_007d* (internal function)
      └─> [Likely routes to FUN_0070c994 → FUN_013949c0]
```

---

## Port Function Callees

### FUN_007d3f34 (opennsl_port_enable_set callee)

**Callers**: 2
- `opennsl_port_enable_set` @ `01dcf78c` (exported API)
- FUN_00da2540 @ `00da2540` (internal function)

**Status**: Used by both exported API and internal code

### FUN_007de7cc (opennsl_port_speed_set callee)

**Callers**: 5
- `opennsl_port_speed_set` @ `01dcfe64` (exported API)
- FUN_00d913ec @ `00d913ec` (internal function)
- FUN_00f42424 @ `00f42424` (internal function, called 3 times)

**Status**: Used by exported API and multiple internal functions

### FUN_007d3294 (opennsl_port_duplex_set callee)

**Callers**: 2
- `opennsl_port_duplex_set` @ `01dcf6c0` (exported API)
- FUN_00da3630 @ `00da3630` (internal function)

**Status**: Used by both exported API and internal code

---

## Port Bringup Sequence

Based on OpenNSL documentation and typical switch initialization:

1. **Port Configuration**:
   - `opennsl_port_speed_set()` - Set speed
   - `opennsl_port_duplex_set()` - Set duplex
   - `opennsl_port_enable_set()` - Enable port

2. **SerDes Configuration**:
   - SerDes lane configuration (likely handled internally)
   - PHY initialization
   - Link training

3. **MAC Configuration**:
   - MAC enable
   - Flow control settings
   - VLAN configuration

---

## Connection to Dispatcher System

Port functions likely follow the same dispatcher pattern as table operations:

```
Port API → FUN_007d* → FUN_0070c994 → FUN_013949c0 → FUN_0139459c → [indirect call]
```

However, port operations may use different dispatcher paths than table writes, as they involve register configuration rather than table writes.

---

## Next Steps

1. **Trace port function callees**: Analyze FUN_007d3f34, FUN_007de7cc, FUN_007d3294
2. **Find port register access**: Identify register write functions for port configuration
3. **SerDes analysis**: Find SerDes configuration functions
4. **Runtime tracing**: Use port-up trace to correlate API calls with register writes

---

## References

- [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) - Complete call chain
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) - Port bringup requirements
- [PORT_BRINGUP_STATUS.md](../previous_findings/PORT_BRINGUP_STATUS.md) - Previous port bringup analysis

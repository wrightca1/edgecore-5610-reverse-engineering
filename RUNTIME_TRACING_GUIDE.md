# Runtime Tracing Guide

**Date**: 2026-02-19  
**Purpose**: Guide for runtime tracing on live switch to map API calls to table IDs

---

## Overview

Runtime tracing is required to:
1. **Verify static analysis findings** - Confirm table ID mappings
2. **Resolve indirect calls** - Map function pointer targets
3. **Correlate API calls with table IDs** - Link `opennsl_l3_route_add` → table ID `0x22ca`
4. **Capture actual data formats** - See table entry structures at runtime

---

## Prerequisites

### Live Switch Access
- **Switch**: 10.1.1.233 (Cumulus Linux)
- **User**: cumulus
- **Requirements**: sudo access for gdb/strace

### Tools Required
- `gdb` - For function breakpoints and parameter inspection
- `strace` - For system call tracing
- `perf` (optional) - For performance-based function tracing

---

## Tracing Methods

### Method 1: GDB Function Breakpoints (Recommended)

**Script**: `trace-api-to-table-id-on-switch.sh`

**How it works**:
1. Attaches gdb to running switchd process
2. Sets breakpoints on API functions (`opennsl_l3_route_add`, etc.)
3. Sets breakpoints on dispatcher functions (`FUN_01876f10`, `FUN_018d7ad4`, etc.)
4. Captures register values (table IDs in r4/r7)
5. Captures stack traces

**Usage**:
```bash
# On local machine
./scripts/reverse-engineering/run-api-to-table-id-trace-10.1.1.233.sh

# During trace, trigger API calls:
ssh cumulus@10.1.1.233
sudo ip route add 10.1.1.0/24 via 10.1.1.1 dev swp1
sudo ip route add 192.168.1.0/24 via 10.1.1.2 dev swp2
```

**Output**:
- `api-to-table-id-trace-10.1.1.233.log` - Full gdb trace
- `api-to-table-id-summary-10.1.1.233.txt` - Summary with table IDs

### Method 2: Table Write Dispatcher Tracing

**Script**: `trace-table-writes-on-switch.sh`

**How it works**:
1. Sets breakpoint on `FUN_01876f10` (generic table write dispatcher)
2. Captures table ID from r4 register
3. Captures function parameters
4. Captures stack trace to see which API called it

**Usage**:
```bash
./scripts/reverse-engineering/run-table-write-trace-10.1.1.233.sh
```

**Output**:
- `table-writes-trace-10.1.1.233.log` - Full trace
- `table-writes-summary-10.1.1.233.txt` - Summary

### Method 3: Strace System Call Tracing

**Script**: `trace-api-calls-strace-on-switch.sh`

**How it works**:
1. Uses strace to trace system calls (mmap, ioctl, write)
2. Captures memory mappings and I/O operations
3. Less precise but doesn't require gdb

**Usage**:
```bash
# Copy script to switch
scp trace-api-calls-strace-on-switch.sh cumulus@10.1.1.233:/home/cumulus/
ssh cumulus@10.1.1.233
sudo bash /home/cumulus/trace-api-calls-strace-on-switch.sh
```

---

## API Functions to Trace

### L3 Route APIs
- `opennsl_l3_route_add` @ `0x01dbdb40`
  - Expected table ID: `0x22ca` or `0x22d3` (L3_DEFIP)
  
- `opennsl_l3_route_delete` @ `0x01dbd60`
  - Expected table ID: `0x22ca` or `0x22d3`

### ECMP APIs
- `opennsl_l3_egress_ecmp_add` @ `0x01dbd3c8`
  - Expected table ID: `0x2c33` or `0x2c32` (L3_ECMP)
  
- `opennsl_l3_egress_ecmp_create` @ `0x01dbd3e8`
  - Expected table ID: `0x2c33` or `0x2c32`

- `opennsl_l3_egress_ecmp_delete` @ `0x01dbd408`
  - Expected table ID: `0x2c33` or `0x2c32`

### VLAN APIs
- `opennsl_vlan_translate_egress_action_add` @ `0x01dd172c`
  - Expected table ID: `0x835` (VLAN_XLATE)

---

## Dispatcher Functions to Trace

### Table Write Dispatcher
- **FUN_01876f10** @ `0x01876f10`
  - **Table ID location**: r4 register
  - **Purpose**: Generic table write dispatcher
  - **Checks**: `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`

### Table ID Validator
- **FUN_018d62ec** @ `0x018d62ec`
  - **Table ID location**: r7 register
  - **Purpose**: Validates table ID <= `0x2c67`
  - **Called by**: FUN_018d7ad4

### Table ID Dispatcher
- **FUN_018d7ad4** @ `0x018d7ad4`
  - **Table ID location**: r7 register
  - **Purpose**: Routes to specific dispatcher functions
  - **Validates**: `0x22d3`, `0x2c32`, `0x1559-0x155e`, `0x1599`, `0x2c24`, `0x15a5`

---

## Triggering API Calls

### L3 Route Addition
```bash
# Via Linux ip command
sudo ip route add 10.1.1.0/24 via 10.1.1.1 dev swp1
sudo ip route add 192.168.1.0/24 via 10.1.1.2 dev swp2

# Via Cumulus CLI
net add route 10.1.1.0/24 via 10.1.1.1
net commit
```

### ECMP Group Creation
```bash
# Via Cumulus CLI (if available)
net add route 10.1.1.0/24 nexthop via 10.1.1.1 nexthop via 10.1.1.2
net commit
```

### VLAN Translation
```bash
# Via Cumulus CLI
net add vlan 100
net add vlan 100 ip address 10.1.1.1/24
net commit
```

---

## Interpreting Results

### Table ID Format
- PowerPC uses registers r3-r10 for parameters
- Table ID typically in **r4** (4th parameter) or **r7** (7th parameter)
- Values are hexadecimal (e.g., `0x22ca`)

### Expected Mappings
Based on static analysis:

| API Call | Expected Table ID | Dispatcher |
|----------|-------------------|------------|
| `opennsl_l3_route_add` | `0x22ca` or `0x22d3` | FUN_01876f10 |
| `opennsl_l3_egress_ecmp_add` | `0x2c33` or `0x2c32` | FUN_01876f10 |
| `opennsl_vlan_translate_egress_action_add` | `0x835` | FUN_01876f10 |

### Stack Trace Analysis
Stack traces show the call chain:
```
opennsl_l3_route_add
  → FUN_007b1bf0
    → FUN_0070c994
      → FUN_013949c0
        → FUN_0139459c
          → [indirect call]
            → FUN_018d7ad4
              → FUN_018d62ec
                → FUN_01876f10
```

---

## Troubleshooting

### GDB Permission Denied
```bash
# Enable ptrace
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```

### Switchd Not Found
```bash
# Find switchd PID
pgrep -f switchd
# Or
ps aux | grep switchd
```

### Library Base Address Not Found
```bash
# Check process maps
cat /proc/$(pgrep switchd)/maps | grep libopennsl
```

### No Breakpoints Hit
- Verify addresses are correct (check libopennsl.so.1 base address)
- Ensure API calls are actually being made
- Check if switchd is using a different library version

---

## Next Steps After Tracing

1. **Correlate Results**: Match captured table IDs with API calls
2. **Verify Mappings**: Confirm static analysis hypotheses
3. **Document Findings**: Update TABLE_ID_MAPPING_ANALYSIS.md
4. **Function Pointer Resolution**: Use traces to resolve indirect calls
5. **Data Format Analysis**: Analyze register values to understand table entry formats

---

## References

- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md) - Table ID hypotheses
- [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) - Call chain documentation
- [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md) - Infrastructure details

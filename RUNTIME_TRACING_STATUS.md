# Runtime Tracing Status

**Date**: 2026-02-19  
**Status**: Infrastructure Complete, Ready for Execution

---

## Overview

Runtime tracing infrastructure has been created to map OpenNSL API calls to table IDs on the live Cumulus switch (10.1.1.233). The infrastructure is ready, but execution requires:

1. **Switch access** - SSH to cumulus@10.1.1.233
2. **Sudo permissions** - For gdb/strace attachment
3. **API trigger** - Commands to trigger route/ECMP/VLAN operations

---

## Created Scripts

### 1. Primary Tracing Scripts

#### `trace-api-to-table-id-on-switch.sh`
- **Purpose**: GDB-based trace with address breakpoints
- **Method**: Sets breakpoints on API functions and dispatchers using calculated addresses
- **Challenges**: Requires finding libopennsl.so.1 base address (statically linked into switchd)

#### `trace-with-gdb-symbols-on-switch.sh`
- **Purpose**: GDB-based trace using symbol names
- **Method**: Uses `break opennsl_l3_route_add` (symbol-based)
- **Advantage**: Works if symbols are available, no address calculation needed
- **Status**: Fixed temp file issue, ready to test

#### `trace-table-writes-on-switch.sh`
- **Purpose**: Trace table write dispatcher (`FUN_01876f10`)
- **Method**: Breaks on generic table write function to capture table IDs
- **Output**: Table IDs from r4 register

### 2. Wrapper Scripts

#### `run-api-to-table-id-trace-10.1.1.233.sh`
- Copies script to switch, runs trace, fetches results
- **Usage**: `./run-api-to-table-id-trace-10.1.1.233.sh`

#### `run-gdb-symbol-trace-10.1.1.233.sh`
- Runs symbol-based GDB trace
- **Usage**: `./run-gdb-symbol-trace-10.1.1.233.sh`

#### `run-table-write-trace-10.1.1.233.sh`
- Runs table write dispatcher trace
- **Usage**: `./run-table-write-trace-10.1.1.233.sh`

### 3. Helper Scripts

#### `trigger-api-calls-on-switch.sh`
- Automatically triggers API calls during trace
- Adds/deletes test routes
- **Usage**: Run in parallel with trace script

#### `run-complete-runtime-trace-10.1.1.233.sh`
- Runs trace and triggers API calls automatically
- **Usage**: `./run-complete-runtime-trace-10.1.1.233.sh`

#### `check-switchd-libraries.sh`
- Checks what libraries switchd loads
- **Finding**: OpenNSL is statically linked (not in ldd output)

---

## Key Findings

### OpenNSL Library Location
- **Status**: Statically linked into switchd binary
- **Implication**: Functions are in `/usr/sbin/switchd`, not separate `.so` file
- **Impact**: Need to use switchd binary base address instead of library base

### Process Maps Access
- **Issue**: `/proc/PID/maps` requires sudo access
- **Solution**: Scripts use `sudo` when accessing process maps

### Symbol Availability
- **Status**: Unknown (switchd binary is stripped)
- **Test**: GDB symbol breakpoints may not work
- **Fallback**: Address-based breakpoints using calculated offsets

---

## Execution Plan

### Step 1: Test Symbol-Based Tracing
```bash
./scripts/reverse-engineering/run-gdb-symbol-trace-10.1.1.233.sh
```
- In parallel terminal: `ssh cumulus@10.1.1.233 "sudo ip route add 10.1.1.0/24 via 10.1.1.1 dev swp1"`

### Step 2: If Symbols Don't Work, Use Address-Based
1. Extract switchd binary from switch
2. Load into Ghidra to find function addresses
3. Update `trace-api-to-table-id-on-switch.sh` with correct addresses
4. Run trace

### Step 3: Analyze Results
- Correlate API calls with captured table IDs
- Verify static analysis hypotheses
- Update `TABLE_ID_MAPPING_ANALYSIS.md`

---

## Expected Outputs

### Trace Files
- `docs/reverse-engineering/traces/api-to-table-id-trace-10.1.1.233.log`
- `docs/reverse-engineering/traces/gdb-symbol-trace-10.1.1.233.log`
- `docs/reverse-engineering/traces/table-writes-trace-10.1.1.233.log`

### Summary Files
- `docs/reverse-engineering/traces/api-to-table-id-summary-10.1.1.233.txt`
- `docs/reverse-engineering/traces/gdb-symbol-summary-10.1.1.233.txt`
- `docs/reverse-engineering/traces/table-writes-summary-10.1.1.233.txt`

---

## Troubleshooting

### "No space left on device"
- **Cause**: Temp file creation issue
- **Fix**: Updated script to use `printf` instead of here-doc

### "libopennsl.so.1 not found"
- **Cause**: Library is statically linked
- **Fix**: Script now uses switchd binary base address

### "Breakpoint not hit"
- **Possible causes**:
  - Symbols stripped (use address-based breakpoints)
  - Addresses incorrect (need to extract switchd and analyze in Ghidra)
  - API calls not being triggered (verify with `ip route` commands)

### Permission Denied
- **Solution**: Ensure sudo access on switch
- **Test**: `ssh cumulus@10.1.1.233 "sudo cat /proc/\$(pgrep switchd)/maps | head -5"`

---

## Next Steps

1. **Execute traces** - Run scripts on live switch
2. **Extract switchd binary** - If address-based tracing needed
3. **Analyze results** - Correlate API calls with table IDs
4. **Update documentation** - Verify/correct table ID mappings
5. **Function pointer resolution** - Use traces to resolve indirect calls

---

## References

- [RUNTIME_TRACING_GUIDE.md](RUNTIME_TRACING_GUIDE.md) - Detailed tracing guide
- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md) - Table ID hypotheses
- [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) - Call chain docs

# Runtime Tracing - Complete Infrastructure

**Date**: 2026-02-19  
**Status**: ✅ Infrastructure Complete - Ready for Execution

---

## Summary

Complete runtime tracing infrastructure has been created to map OpenNSL API calls to table IDs on the live Cumulus switch (10.1.1.233). All scripts are ready for execution.

---

## Created Infrastructure

### Tracing Scripts (On-Switch)

1. **`trace-api-to-table-id-on-switch.sh`**
   - GDB-based trace with address breakpoints
   - Calculates addresses from libopennsl.so.1 offsets
   - Handles statically linked OpenNSL SDK

2. **`trace-with-gdb-symbols-on-switch.sh`**
   - GDB-based trace using symbol names
   - Simpler approach if symbols available
   - Fixed temp file issues

3. **`trace-table-writes-on-switch.sh`**
   - Traces table write dispatcher (`FUN_01876f10`)
   - Captures table IDs from r4 register
   - Focused on generic table write function

4. **`trace-api-calls-strace-on-switch.sh`**
   - Alternative: strace-based system call tracing
   - Less precise but doesn't require gdb

### Wrapper Scripts (Local)

1. **`run-api-to-table-id-trace-10.1.1.233.sh`**
   - Copies script, runs trace, fetches results
   - Handles SSH/SCP automatically

2. **`run-gdb-symbol-trace-10.1.1.233.sh`**
   - Runs symbol-based GDB trace
   - Simplified execution

3. **`run-table-write-trace-10.1.1.233.sh`**
   - Runs table write dispatcher trace

4. **`run-complete-runtime-trace-10.1.1.233.sh`**
   - Automated: runs trace + triggers API calls

### Helper Scripts

1. **`trigger-api-calls-on-switch.sh`**
   - Automatically triggers API calls during trace
   - Adds/deletes test routes

2. **`check-switchd-libraries.sh`**
   - Checks what libraries switchd loads
   - Found: OpenNSL is statically linked

---

## Key Findings

### OpenNSL SDK Location
- **Status**: Statically linked into `/usr/sbin/switchd`
- **Evidence**: `ldd /usr/sbin/switchd` shows no libopennsl.so.1
- **Implication**: Functions are in switchd binary, not separate library
- **Solution**: Scripts use switchd binary base address

### Function Addresses
- **Source**: From static analysis of `libopennsl.so.1`
- **API Functions**:
  - `opennsl_l3_route_add` @ `0x01dbdb40`
  - `opennsl_l3_egress_ecmp_add` @ `0x01dbd3c8`
  - `opennsl_l3_egress_ecmp_create` @ `0x01dbd3e8`
  - `opennsl_vlan_translate_egress_action_add` @ `0x01dd172c`
- **Dispatcher Functions**:
  - `FUN_01876f10` @ `0x01876f10` (table write dispatcher)
  - `FUN_018d7ad4` @ `0x018d7ad4` (table ID dispatcher)
  - `FUN_018d62ec` @ `0x018d62ec` (table ID validator)
  - `FUN_0070c994` @ `0x0070c994` (common wrapper)
  - `FUN_013949c0` @ `0x013949c0` (ultra-central dispatcher)

### Expected Table IDs
Based on static analysis:
- **L3_DEFIP**: `0x22ca`, `0x22c9`, `0x22d3`
- **L3_ECMP**: `0x2c33`, `0x2c32`, `0x6418`, `0x6419`, `0x8a8`, `0x1`
- **VLAN_XLATE**: `0x835`
- **L2**: `0x1547` (confirmed)

---

## Execution Instructions

### Quick Start

```bash
# Option 1: Automated (trace + trigger API calls)
./scripts/reverse-engineering/run-complete-runtime-trace-10.1.1.233.sh

# Option 2: Manual (run trace, trigger API calls separately)
# Terminal 1:
./scripts/reverse-engineering/run-gdb-symbol-trace-10.1.1.233.sh

# Terminal 2:
ssh cumulus@10.1.1.233
sudo ip route add 10.1.1.0/24 via 10.1.1.1 dev swp1
sudo ip route add 192.168.1.0/24 via 10.1.1.2 dev swp2
```

### Expected Outputs

All outputs go to `docs/reverse-engineering/traces/`:

- `api-to-table-id-trace-10.1.1.233.log` - Full GDB trace
- `api-to-table-id-summary-10.1.1.233.txt` - Summary with table IDs
- `gdb-symbol-trace-10.1.1.233.log` - Symbol-based trace
- `table-writes-trace-10.1.1.233.log` - Table write dispatcher trace

---

## Troubleshooting

### Issue: "No space left on device"
- **Fix**: Updated scripts to use `printf` instead of here-doc
- **Status**: ✅ Fixed

### Issue: "libopennsl.so.1 not found"
- **Cause**: Library is statically linked
- **Fix**: Scripts now use switchd binary base address
- **Status**: ✅ Fixed

### Issue: Breakpoints not hit
- **Possible causes**:
  1. Symbols stripped (use address-based breakpoints)
  2. Addresses incorrect (need to extract switchd and analyze in Ghidra)
  3. API calls not being triggered
- **Solution**: Verify with `ip route` commands, check trace output

### Issue: Permission denied
- **Solution**: Ensure sudo access on switch
- **Test**: `ssh cumulus@10.1.1.233 "sudo cat /proc/\$(pgrep switchd)/maps | head -5"`

---

## Next Steps After Tracing

1. **Execute traces** - Run scripts on live switch
2. **Extract switchd binary** (if needed) - For address verification
3. **Analyze results** - Correlate API calls with table IDs
4. **Update documentation** - Verify/correct table ID mappings in `TABLE_ID_MAPPING_ANALYSIS.md`
5. **Function pointer resolution** - Use traces to resolve indirect calls
6. **Data format analysis** - Analyze register values to understand table entry formats

---

## Documentation

- **[RUNTIME_TRACING_GUIDE.md](RUNTIME_TRACING_GUIDE.md)** - Detailed tracing guide with methods and examples
- **[RUNTIME_TRACING_STATUS.md](RUNTIME_TRACING_STATUS.md)** - Status and troubleshooting
- **[TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)** - Table ID hypotheses to verify
- **[COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md)** - Call chain architecture

---

## Script Inventory

### On-Switch Scripts
- `trace-api-to-table-id-on-switch.sh`
- `trace-with-gdb-symbols-on-switch.sh`
- `trace-table-writes-on-switch.sh`
- `trace-api-calls-strace-on-switch.sh`
- `trace-api-symbols-on-switch.sh`
- `check-switchd-libraries.sh`

### Local Wrapper Scripts
- `run-api-to-table-id-trace-10.1.1.233.sh`
- `run-gdb-symbol-trace-10.1.1.233.sh`
- `run-table-write-trace-10.1.1.233.sh`
- `run-complete-runtime-trace-10.1.1.233.sh`
- `trigger-api-calls-on-switch.sh`

---

## Status: ✅ Ready for Execution

All infrastructure is complete. The next step is to execute the traces on the live switch and analyze the results to verify table ID mappings.

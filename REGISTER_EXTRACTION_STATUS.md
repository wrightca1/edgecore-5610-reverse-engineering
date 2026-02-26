# Register Extraction Status

**Date**: 2026-02-18  
**Status**: In Progress  
**Method**: Ghidra headless analysis on build server (<USER>@<GHIDRA_HOST_IP>)

## Current Status

### Extraction Running
- **Script**: `ExtractRegisterConstants.java`
- **Target**: switchd binary (Cumulus Linux 2.5.1)
- **Host**: <USER>@<GHIDRA_HOST_IP> (Fedora, 30GB RAM)
- **Output**: `/home/<USER>/analysis/build-server/switchd/sdk-deep-extract/ghidra-register-constants.txt`

### Search Ranges Expanded

The script searches for register offset constants in these ranges:

1. **CMIC Registers**: `0x31000 - 0x35000`
   - CMIC base registers
   - CMC registers (IRQ_STAT, IRQ_MASK, etc.)

2. **S-Channel Registers**: `0x32000 - 0x33000`
   - S-Channel control registers
   - CMIC_CMC0_SCHAN_CTRL = 0x32800

3. **Extended CMIC Range**: `0x30000 - 0x40000`
   - Additional CMIC-related registers

4. **LED Registers**: `0x20000 - 0x30000`
   - LED UP0/UP1 control and data registers

5. **Port Registers**: `0x60000 - 0x70000`
   - Per-port configuration registers
   - SerDes registers

6. **Table Memory**: `0x1000000 - 0x2000000`
   - L2/L3 table memory addresses
   - Buffer management

### Process Details

- **Functions Analyzed**: Up to 1000 functions
- **Instructions per Function**: Up to 200 instructions
- **Java Heap**: 8GB (`-Xmx8G`)
- **Expected Duration**: 5-15 minutes depending on binary size

## Scripts Created

1. **`ghidra-extract-register-constants.sh`**
   - Runs Ghidra headless with ExtractRegisterConstants.java
   - Handles existing projects (skips import, uses -process)

2. **`run-register-extraction-on-build-server.sh`**
   - Copies SDK + scripts to build server
   - Executes extraction remotely
   - Sets up environment (GHIDRA_INSTALL, JAVA_HOME)

3. **`ExtractRegisterConstants.java`**
   - Enhanced Ghidra script
   - Searches for register offset constants
   - Provides context (function name, instruction address)

## Next Steps

1. ✅ Wait for extraction to complete
2. ⏳ Copy results back to local machine
3. ⏳ Analyze extracted register offsets
4. ⏳ Cross-reference with OpenNSL register definitions
5. ⏳ Update SDK_REGISTER_MAP.md with findings
6. ⏳ Identify missing register definitions

## Expected Output Format

```
=== Register Offset Constants from switchd Binary ===
Program: switchd

--- Register Offset Constants (N unique) ---

0x31400:
  FUN_10005ecc@0x1000607c: li r3, 0x31400
  FUN_10010a80@0x10010ac4: addi r4, r3, 0x31400
  ...

0x32800:
  FUN_1000b638@0x1000b650: stw r5, 0x32800(r6)
  ...
```

## Related Documents

- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Current register map (will be updated)
- [`GHIDRA_REGISTER_TABLE_ANALYSIS.md`](./GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Previous Ghidra analysis
- [`GAPS_FOR_CUSTOM_SWITCHD_SDK.md`](./GAPS_FOR_CUSTOM_SWITCHD_SDK.md) - Missing SDK information

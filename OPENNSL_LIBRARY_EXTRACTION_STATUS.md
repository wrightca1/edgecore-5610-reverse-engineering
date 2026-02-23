# OpenNSL Library Register Extraction Status

**Date**: 2026-02-18  
**Status**: In Progress  
**Target**: libopennsl.so.1 (PowerPC, 47MB)  
**Method**: Ghidra headless analysis on build server (<USER>@10.1.1.30)

## Current Status

### Extraction Running
- **Script**: `ExtractRegisterConstants.java`
- **Target**: `/home/<USER>/analysis/build-server/opennsl/libopennsl.so.1`
- **Architecture**: PowerPC:BE:32:default
- **Size**: 47MB (stripped shared library)
- **Output**: `/home/<USER>/analysis/build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt`

### Why Analyze libopennsl.so?

From switchd analysis, we found:
- ✅ LED registers (0x21000, 0x21400, 0x21800) - matched OpenNSL definitions
- ❌ CMIC registers (0x31000-0x35000) - **NOT found** in switchd
- ❌ S-Channel registers (0x32000-0x33000) - **NOT found** in switchd

**Hypothesis**: CMIC/S-Channel register offsets are stored in libopennsl.so (the SDK library), not in switchd. This makes sense because:
1. switchd calls SDK functions (e.g., `bcm_reg_read`, `bcm_reg_write`)
2. The SDK library contains the actual register access code
3. Register offsets are likely defined as constants in the SDK library

### Expected Findings

We expect to find:
1. **CMIC Register Offsets** (0x31000-0x35000)
   - CMIC_IRQ_STAT, CMIC_IRQ_MASK
   - CMIC_CMCx_IRQ_STAT0_OFFSET, etc.
   - CMIC_CMC0_SCHAN_CTRL (0x32800)

2. **Port Register Offsets** (0x60000-0x70000)
   - Per-port configuration registers
   - SerDes registers

3. **Table Memory Addresses** (0x1000000+)
   - L2/L3 table base addresses
   - Buffer management addresses

4. **Other Register Offsets**
   - MMU registers
   - Statistics counter registers
   - Pipeline registers

### Process Details

- **Functions Analyzed**: Up to 1000 functions
- **Data Sections**: All data sections scanned for register offsets
- **Java Heap**: 8GB (`-Xmx8G`)
- **Expected Duration**: 10-30 minutes (47MB library)

## Scripts Created

1. **`ghidra-extract-opennsl-registers.sh`**
   - Runs Ghidra headless on libopennsl.so
   - Auto-detects PowerPC architecture
   - Handles existing projects

2. **`run-opennsl-extraction-on-build-server.sh`**
   - Copies libopennsl.so to build server
   - Executes extraction remotely
   - Sets up environment

## Next Steps

1. ⏳ Wait for extraction to complete
2. ⏳ Copy results back to local machine
3. ⏳ Analyze extracted register offsets
4. ⏳ Cross-reference with:
   - OpenNSL source code register definitions
   - switchd extraction results
   - Previous Ghidra analysis
5. ⏳ Update SDK_REGISTER_MAP.md with findings
6. ⏳ Identify missing register definitions

## Related Documents

- [`REGISTER_EXTRACTION_RESULTS.md`](./REGISTER_EXTRACTION_RESULTS.md) - switchd extraction results
- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Current register map (will be updated)
- [`GHIDRA_REGISTER_TABLE_ANALYSIS.md`](./GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Previous Ghidra analysis

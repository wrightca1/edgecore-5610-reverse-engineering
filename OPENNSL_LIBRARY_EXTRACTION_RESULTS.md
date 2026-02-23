# OpenNSL Library Register Extraction Results

**Date**: 2026-02-18  
**Source**: Ghidra headless analysis of libopennsl.so.1 (PowerPC, 47MB)  
**Method**: Data section scanning + instruction operand analysis  
**Total Found**: **20,197 unique register offset constants** (60,614 total lines)

## Summary Statistics

| Category | Count | Notes |
|----------|-------|-------|
| **Total unique offsets** | 20,197 | Massive extraction success! |
| **CMIC range (0x31000-0x35000)** | 0 | ❌ Not found as constants |
| **S-Channel range (0x32000-0x33000)** | 0 | ❌ Not found as constants |
| **LED range (0x20000-0x30000)** | 15 | ✅ Found (matches switchd findings) |
| **Port range (0x60000-0x70000)** | 3 | ✅ Found |
| **Table memory (0x1000000+)** | 20,176 | ✅ **Huge number!** |

## Key Findings

### ✅ LED Registers Confirmed

Found LED register offsets matching OpenNSL definitions:
- `0x20000`, `0x20004`, `0x20400`, `0x20800`, `0x21000`, `0x21400`, `0x21800`
- These match what we found in switchd and OpenNSL source code

### ✅ Table Memory Addresses (Major Finding!)

**20,176 table memory addresses** found in the `0x1000000+` range!

These are likely:
- L2 table base addresses
- L3 table base addresses  
- Buffer management addresses
- ECMP table addresses
- VLAN table addresses
- Statistics counter addresses

**Examples**:
- `0x1000000` - Base address
- `0x10001e4`, `0x1000458`, `0x10007b8` - Table offsets
- `0x1005e00` - Appears multiple times (important table?)
- `0x180c200` - Appears multiple times (important table?)

### ✅ Port Registers

Found 3 port register offsets in the `0x60000-0x70000` range:
- `0x60407`, `0x60408`, `0x60409` - Port configuration registers

### ❌ CMIC/S-Channel Registers Not Found

**Critical Finding**: CMIC registers (0x31000-0x35000) and S-Channel registers (0x32000-0x33000) were **NOT found** as constants in libopennsl.so data sections.

**Possible Reasons**:
1. **Computed at runtime**: Register offsets computed via macros/functions
   - Example: `CMIC_CMCx_IRQ_STAT0_OFFSET(x) = (0x31400 + (0x1000 * x))`
   - The base `0x31400` might be computed, not stored as constant

2. **Accessed via SDK functions**: Registers accessed through function calls
   - Functions like `bcm_reg_read()`, `soc_reg_read()` take register offsets as parameters
   - Offsets might be passed from switchd or computed dynamically

3. **Stored in different format**: Register offsets might be:
   - In lookup tables
   - Computed from base addresses
   - Stored as relative offsets

4. **Architecture-specific**: CMIC registers might be accessed differently on PowerPC vs x86

## Analysis

### What This Tells Us

1. **Table Memory Layout**: The huge number of table memory addresses (20,176) suggests:
   - Complex memory layout for L2/L3 tables
   - Multiple table instances or views
   - Buffer management structures
   - This is valuable information for understanding ASIC memory architecture

2. **Register Access Pattern**: CMIC registers not being constants suggests:
   - They're accessed via SDK API functions
   - Register offsets are computed from base addresses
   - The SDK abstracts register access (as expected)

3. **LED Registers**: Found as constants because they're likely accessed directly

### Comparison with switchd

| Source | LED Registers | CMIC Registers | Table Addresses |
|--------|---------------|----------------|-----------------|
| **switchd** | 3 found | 0 found | 6 found |
| **libopennsl.so** | 15 found | 0 found | 20,176 found |

**Conclusion**: libopennsl.so contains far more register/table information than switchd, but CMIC registers are still accessed indirectly.

## Next Steps

### 1. Analyze Table Memory Addresses
- Group addresses by ranges
- Identify patterns (L2 vs L3 vs buffers)
- Cross-reference with OpenNSL source code table definitions

### 2. Search for CMIC Register Access Patterns
- Look for function calls that compute register offsets
- Search for `0x31400` (CMIC CMC0 base) in code sections
- Find register access functions (`bcm_reg_read`, `soc_reg_read`)

### 3. Extract Register Access Functions
- Find SDK functions that access CMIC registers
- Extract function signatures
- Document register offset computation methods

### 4. Cross-Reference with OpenNSL Source
- Match found offsets with OpenNSL register definitions
- Identify which offsets correspond to which registers
- Document register-to-offset mappings

## Related Documents

- [`REGISTER_EXTRACTION_RESULTS.md`](./REGISTER_EXTRACTION_RESULTS.md) - switchd extraction results
- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Current register map (will be updated)
- [`OPENNSL_LIBRARY_EXTRACTION_STATUS.md`](./OPENNSL_LIBRARY_EXTRACTION_STATUS.md) - Extraction process

## Files

- **Raw output**: `build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt` (60,614 lines)
- **Remote location**: `/home/<USER>/analysis/build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt`

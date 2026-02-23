# Register Extraction Results from switchd Binary

**Date**: 2026-02-18  
**Source**: Ghidra headless analysis of switchd binary (Cumulus Linux 2.5.1)  
**Method**: Data section scanning + instruction operand analysis  
**Total Found**: 21 unique register offset constants

## Summary

The extraction found register offsets stored in data sections of the switchd binary. These are likely register addresses or offsets used by the SDK functions.

## Extracted Register Offsets

### LED Registers (0x20000-0x30000 range)

| Offset | Count | Data Addresses | Notes |
|--------|-------|----------------|-------|
| `0x20001` | 1 | `0x113183d8` | LED-related constant |
| `0x21000` | 1 | `0x1183c5f0` | **LED UP1 Control** (matches OpenNSL `OPENNSL_CMIC_LEDUP1_CTRL_OFFSET`) |
| `0x21400` | 1 | `0x1183c5fc` | **LED UP1 Data RAM** (matches OpenNSL `OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET`) |
| `0x21800` | 1 | `0x1183c5f8` | **LED UP1 Program RAM** (matches OpenNSL `OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET`) |

**Cross-reference**: These match OpenNSL LED register definitions:
- `OPENNSL_CMIC_LEDUP1_CTRL_OFFSET = 0x21000` ✅
- `OPENNSL_CMIC_LEDUP1_DATA_RAM_OFFSET = 0x21400` ✅
- `OPENNSL_CMIC_LEDUP1_PROGRAM_RAM_OFFSET = 0x21800` ✅

### Other Constants in 0x20000-0x40000 Range

| Offset | Count | Data Addresses | Possible Purpose |
|--------|-------|----------------|------------------|
| `0x2625a` | 3 | `0x114309b8`, `0x1144a1ac`, `0x11457ef4` | Unknown (appears multiple times) |
| `0x267ac` | 1 | `0x11e46e78` | Unknown |
| `0x26ce4` | 1 | `0x11e46e74` | Unknown |
| `0x275e2` | 3 | `0x114309c0`, `0x1144a1b4`, `0x11457efc` | Unknown (appears multiple times) |
| `0x27fff` | 1 | `0x11350100` | Possibly a mask or limit value |
| `0x29fcc` | 1 | `0x11e46e7c` | Unknown |
| `0x2cb6c` | 1 | `0x11e46e88` | Unknown |
| `0x2cccd` | 1 | `0x1143a508` | Unknown |
| `0x2dc6c` | 3 | `0x114309bc`, `0x1144a1b0`, `0x11457ef8` | Unknown (appears multiple times) |
| `0x3061c` | 1 | `0x11e46e84` | Unknown |
| `0x331d4` | 1 | `0x11e46e80` | Unknown |

**Note**: These offsets don't match known CMIC register ranges. They might be:
- Port-specific register offsets
- Table memory offsets
- Configuration values
- Other ASIC-specific constants

### Table Memory Addresses (0x1000000+ range)

| Offset | Count | Data Addresses | Possible Purpose |
|--------|-------|----------------|------------------|
| `0x1000ccc` | 1 | `0x11324cd2` | Table memory address |
| `0x1005e00` | 2 | `0x11328650`, `0x1132a75c` | Table memory address (used twice) |
| `0x1112233` | 1 | `0x11851eb4` | Table memory address |
| `0x1120066` | 1 | `0x11436434` | Table memory address |
| `0x1120200` | 1 | `0x11436428` | Table memory address |
| `0x180c200` | 3 | `0x11324cc6`, `0x1139be40`, `0x11e46da4` | Table memory address (used multiple times) |

**Note**: These are likely L2/L3 table memory addresses or buffer management addresses.

## Analysis

### What We Found

1. **LED Registers Confirmed**: Found 3 LED UP1 register offsets that match OpenNSL definitions exactly
2. **Data Section Storage**: Register offsets are stored in data sections, not as immediate values in code
3. **Multiple References**: Some offsets appear multiple times, suggesting they're used in different contexts

### What We Didn't Find

1. **CMIC Registers (0x31000-0x35000)**: No CMIC register offsets found in data sections
   - **Possible reasons**:
     - CMIC registers accessed via SDK function calls (not direct offsets)
     - Registers computed at runtime
     - Registers accessed via S-Channel (indirect access)
     - Offsets stored in libopennsl.so, not switchd

2. **S-Channel Registers (0x32000-0x33000)**: No S-Channel register offsets found
   - **Possible reasons**: Same as CMIC registers above

3. **Port Registers (0x60000-0x70000)**: No port register offsets found
   - **Possible reasons**: Port registers accessed via SDK APIs, not direct offsets

## Recommendations

### Next Steps

1. **Analyze libopennsl.so**: Extract register offsets from the SDK library itself
   - The SDK library likely contains register offset definitions
   - Use `strings` and Ghidra on libopennsl.so

2. **Search for Register Access Patterns**: Look for SDK function calls that take register offsets
   - Find calls to `bcm_reg_read`, `bcm_reg_write`, `soc_reg_read`, `soc_reg_write`
   - Extract register offsets passed as parameters

3. **Cross-reference with OpenNSL Source**: Compare found offsets with OpenNSL register definitions
   - We already have 76 CMIC register definitions from OpenNSL source
   - Match switchd offsets with OpenNSL definitions

4. **Runtime Analysis**: Use dynamic analysis to capture register accesses
   - Run switchd under strace/ltrace
   - Monitor register read/write operations
   - Capture register offsets at runtime

## Related Documents

- [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) - Current register map
- [`GHIDRA_REGISTER_TABLE_ANALYSIS.md`](./GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Previous Ghidra analysis
- [`REGISTER_EXTRACTION_STATUS.md`](./REGISTER_EXTRACTION_STATUS.md) - Extraction process details

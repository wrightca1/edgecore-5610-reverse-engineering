# Table Memory Map (from `libopennsl.so` extraction)

**Date**: 2026-02-18  
**Source**: `build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt` (Ghidra headless extraction)  
**Scope**: Offsets \(\ge 0x01000000\) (table / internal-memory style addresses)

## Summary

From `libopennsl.so.1`, we extracted **20,176 unique addresses** in the range:

- **min**: `0x01000000`
- **max**: `0x01ffff20`

All extracted table-style addresses fall within the **single 16MB region**:

- `0x01000000–0x01ffffff`

This strongly suggests OpenNSL/SDK encodes most “table memory” references for this target into a contiguous `0x01xxxxxx` window (likely an internal-memory address space or table-region selector).

## 1MB histogram (counts per `0x01?00000` bucket)

| 1MB base | Count |
|---:|---:|
| `0x01000000` | 1405 |
| `0x01100000` | 905 |
| `0x01200000` | 1573 |
| `0x01300000` | 884 |
| `0x01400000` | 1269 |
| `0x01500000` | 1322 |
| `0x01600000` | 718 |
| `0x01700000` | 953 |
| `0x01800000` | 1435 |
| `0x01900000` | 397 |
| `0x01a00000` | 302 |
| `0x01b00000` | 2051 |
| `0x01c00000` | 2595 |
| `0x01d00000` | 887 |
| `0x01e00000` | 1475 |
| `0x01f00000` | 2005 |

## Observations

- **Heavy concentration** in:
  - `0x01c00000` (2595)
  - `0x01b00000` (2051)
  - `0x01f00000` (2005)
  - `0x01e00000` (1475)
  - `0x01200000` (1573)
- **Lighter usage** in:
  - `0x01a00000` (302)
  - `0x01900000` (397)

## How to use this

- Treat `0x01xxxxxx` as the **primary “table memory” address space** observed from OpenNSL for this target.
- Use the **1MB histogram** as a guide for where tables/blocks likely live and which regions are used most heavily.
- Next step is to **map these regions to table names** by correlating:
  - callsites/functions in `libopennsl.so` that reference these offsets
  - known Broadcom/OpenNSL concepts (`L2_ENTRY`, `L3_DEFIP`, `VLAN_XLATE`, MMU, etc.)

## Related

- `docs/reverse-engineering/OPENNSL_LIBRARY_EXTRACTION_RESULTS.md`
- `docs/reverse-engineering/REGISTER_EXTRACTION_SUMMARY.md`
- `docs/reverse-engineering/SDK_REGISTER_MAP.md`


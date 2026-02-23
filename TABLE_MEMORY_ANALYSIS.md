# Table Memory Address Analysis (OpenNSL / Trident+ target)

**Date**: 2026-02-18  
**Primary input**: `build-server/opennsl/sdk-deep-extract/opennsl-register-constants.txt`  
**Addresses analyzed**: `0x01000000–0x01ffff20` (**20,176 unique**)

## What this is

`libopennsl.so` contains a huge set of “table memory style” addresses for this target, but they are not annotated with table names. This document summarizes structure and suggests the next RE step: **xref the hottest/anchor addresses back into code** to recover which tables/blocks they belong to.

## Range + region

- **min**: `0x01000000`
- **max**: `0x01ffff20`
- **Region**: everything is within a single 16MB window `0x01xxxxxx`

This suggests the SDK uses an internal addressing scheme where “table memory” references are encoded into the `0x01xxxxxx` region for this platform/ASIC generation.

## 1MB bucket histogram (counts)

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

## Coverage per bucket (min/max/span)

Each bucket generally spans almost the full 1MB, but some have large “gaps” (missing ranges), hinting at sub-block partitioning.

Examples:
- `0x01b00000`: `min=0x01b37998` `max=0x01bffff0` (span smaller than full 1MB)
- `0x01900000`: max gap `0x3cb5d` between `0x0196d9a8` and `0x019aa505`

## Candidate “anchor” addresses to xref first

These show up as obvious bases or repeated constants across artifacts:

- **`0x01000000`**: base of the region (likely table region base / first block)
- **`0x0180c200`**: shows up in both `switchd` extraction and `libopennsl.so` extraction
- **`0x01312d00`**, **`0x01560974`**, **`0x01855abc`**: observed with multiple occurrences in extracted output

## Next step (actionable)

Run an xref-focused Ghidra post-script against the existing `libopennsl` project:

- locate data items whose value equals each anchor address
- list **references to those data items** (functions + instruction addresses)
- dump nearby strings used in the same functions (often includes table names like `L2_ENTRY`, `L3_DEFIP`, etc.)

That’s the shortest path to turn “20k addresses” into a **named table map**.

## Current xref output

See [`TABLE_ADDR_XREFS_OPENNSL.md`](./TABLE_ADDR_XREFS_OPENNSL.md) for the first round of anchor xrefs.

## Related

- `docs/reverse-engineering/TABLE_MEMORY_MAP_FROM_OPENNSL.md` (histogram-only view)
- `docs/reverse-engineering/OPENNSL_LIBRARY_EXTRACTION_RESULTS.md`
- `docs/reverse-engineering/SDK_REGISTER_MAP.md`


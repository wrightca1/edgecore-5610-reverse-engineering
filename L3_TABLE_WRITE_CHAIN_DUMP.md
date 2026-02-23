# L3 Table Write Chain — Function Dumps

**Date**: 2026-02-19  
**Source**: DumpFunctionCode for FUN_018d7ad4, FUN_018d62ec

---

## Call chain

```
FUN_018d7ad4 (table ID validator)
    └─> FUN_018d62ec (table write wrapper, large frame 0x330)
            └─> FUN_018d43e4
            └─> [further dispatcher calls]
```

---

## FUN_018d7ad4 (validator)

- **Entry**: 0x018d7ad4
- **Args**: r3=unit, r4–r10 (passed through to FUN_018d62ec)
- **Flow**:
  1. Call `0x01393e80` with r3=0xa011e05 — validation
  2. Compare r31 (7th arg) with table IDs:
     - **0x1559–0x155e**: branch to call FUN_018d62ec @ 018d7b7c
     - **0x2c32**: same path
     - **0x1599, 0x22d3, 0x2c24**: branch to 018d7ce0 (different handler)
     - **0x15a5**: branch to 018d7e00
  3. On match (0x1559–0x155e or 0x2c32), call FUN_018d62ec with r3–r10

**Table ID mapping** (from TABLE_ID_MAPPING_ANALYSIS):
- `0x22d3` / `0x22ca` → L3_DEFIP
- `0x2c32` / `0x2c33` → L3_ECMP
- `0x1559–0x155e`, `0x1599`, `0x2c24`, `0x15a5` → L3-related or other tables

---

## FUN_018d62ec (table write wrapper)

- **Entry**: 0x018d62ec
- **Frame**: 0x330 (816 bytes)
- **Flow**:
  1. r21 = r3*4 (unit index)
  2. Call `0x01393e80` with r3=0xa011e05
  3. `cmplwi r24,0x2c67` — r24 (7th arg) ≤ 0x2c67
  4. Table lookup: r22 = [r30-0x7ff8]; r17 = [r22][r21]
  5. Follow chain: [r17+0xa36c30], [r28][r24*4], check bit 0x2
  6. Call `FUN_018d43e4` (r3=unit, r4=&stack)

### FUN_018d43e4 (struct initializer)

- **Entry**: 0x018d43e4
- **Flow**: Calls 0x02f52440 with r3=buffer (r4), r4=0, r5=0x224 (548 bytes) — likely memset. Then stores -1 to offsets 0x204, 0x208, 0x20c, 0x210–0x220. Initializes a 0x224-byte table-write struct before dispatch.
  7. Check [r9+0x10], [r9+0x14] & 0x100

**r24** (7th arg) is used as table/op index; max 0x2c67.

### FUN_018d62ec — buffer and table-ID dispatch (from 354-insn dump)

- **Buffer**: **r1+0x6c** (0x224 bytes), passed to 018d43e4 then to table-specific fill.
- **Fill call sites**: After 018d43e4, buffer (addi r6,r1,0x6c) is passed to:
  - **FUN_014a51e8** (bl 0x014a51e8) — when [r9+0xc] not 0x35/0x37/0x38 and other checks; table IDs 0x1559–0x155e, 0x154c, 0x1561, etc. referenced.
  - **FUN_0170b700** (bl 0x0170b700) — alternate path (e.g. 0x100 bit set).
- **Per-table layout**: Stores into the 0x224-byte buffer are in **014a51e8** and **0170b700**, not in 018d62ec. **Done**: See [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md) for store list and tentative offset→field table (0x0=op, 0x204–0x214=format constants, 0x84/0x9c/0xb4/0xcc=indices).

---

## References

- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)
- [libopennsl-l3-table-callers.txt](../build-server/opennsl/sdk-deep-extract/libopennsl-l3-table-callers.txt)

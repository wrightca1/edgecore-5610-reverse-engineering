# L3 0x224-byte buffer layout from dumps (Path B 3.4–3.7)

**Source**: Dumps of FUN_014a51e8 and FUN_0170b700 (L3 table-write buffer fillers called from 018d62ec with r6 = r1+0x6c). Buffer size **0x224** (548 bytes).

---

## Buffer base

- **018d62ec** passes buffer as **r6** (addi r6,r1,0x6c) to 014a51e8 and 0170b700.
- **014a51e8**: buffer in **r28** (or r28,r6,r6 at 014a5238).
- **0170b700**: buffer in **r31** (or r31,r6,r6 at 0170b73c); some paths use **r6** directly.

---

## Stores observed (offset → value / role)

### Common header (both functions)

| Offset (hex) | Size | Values / role |
|--------------|------|----------------|
| **0x0**  | 4 | Op/type: 4, 6, or 8 (li r0,0x4 / 0x6 / 0x8 then stw). |
| **0x204**| 4 | Constant 0xa9e2 or 0xee2b (table/format ID?). |
| **0x208**| 4 | Constant 0x95d6 or 0x95d9. |
| **0x20c**| 4 | Constant 0x4fcc or 0x4fcf (014a51e4 doesn’t set; 018d43e4 stores -1). |
| **0x210**| 4 | Constant 0x992c or 0xb160 (table-ID path). |
| **0x214**| 4 | Constant 0x5740. |

### FUN_014a51e8 (r28 = buffer)

- **0x0(r28)**: 8 or 6 (op).
- **0x84(r28)**: computed (loop / index).
- **0x9c(r28)**: computed (from 0x84 + offset).
- **0x204–0x214(r28)**: as in table above.
- **0x4(r28)** (via r29=r28+0x40, -0x3c(r29)): table ID–related (r31 = table ID 0x1559–0x155e).

Table IDs in 014a51e8: 0x1584, 0x1590, 0x15a5, 0x2c32, 0x1597, 0x1514, 0x1515, 0x1559–0x155e, 0x1588, 0x158c, 0x6fa, 0x124a.

### FUN_0170b700 (r31 = buffer, sometimes r6)

- **0x0(r6/r31)**: 4 (op).
- **0x84(r31)**: index/count (r29 or r0).
- **0x9c(r31)**: computed or r29.
- **0xb4(r31)**: r11.
- **0xcc(r31)**: r0.
- **0x204, 0x208, 0x20c(r6/r31)**: 0xa9e2/0xee2b, 0x95d6/0x95d9, 0x4fcc/0x4fcf.
- **0x4(r31)**, **0x44(r31)** (loop, r9 = r31): table ID 0x1555 and flag 1 — array of entries starting at 0x4.

Table IDs in 0170b700: 0x152d, 0x1599, 0x2c4b, 0x2c4d, 0x2c24, 0xa95, 0x1529, 0x152b, 0x1594, 0x1596, 0x1555, etc.

---

## Tentative layout summary

- **0x000–0x083**: op (0x0), then table/entry data; **0x4**, **0x44** used for repeated entries (e.g. 0x1555 + flag).
- **0x084, 0x09c, 0x0b4, 0x0cc**: index / indices or pointers (table-specific).
- **0x204–0x214**: format/table constants (0xa9e2, 0x95d6, 0x4fcc, 0x992c/0xb160, 0x5740).
- **0x218–0x220**: -1 sentinels from 018d43e4.

Field names (prefix, next_hop, egress_id, port, MAC) need mapping from OpenNSL types or more traces; the constants at 0x204–0x214 likely identify table/format.

---

## References

- [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md)
- [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md)
- Dumps: `libopennsl-dump-014a51e8.txt`, `libopennsl-dump-0170b700.txt`

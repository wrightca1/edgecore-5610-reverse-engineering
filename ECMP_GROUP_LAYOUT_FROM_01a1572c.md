# ECMP group layout from FUN_01a1572c dump (Path B 3.7)

**Source**: libopennsl-dump-01a1572c.txt (184 instructions). FUN_01a1572c references L3_ECMP (string ref in binary); this doc summarizes ECMP-related flow and layout from the dump.

---

## Role of FUN_01a1572c

- **Entry**: 0x01a1572c. **Args**: r3=unit, r4=ptr (saved at 0x5c(r1)), r5=flag (saved at 0x58(r1)); r5=0 vs non-zero branches.
- **Unit struct** (r26 = [r19][unit*4]): uses **0x138(r26)**, **0x13c(r26)** (group base/count), **0x134(r26)** (array base), **0x10c(r9)** (per-unit table) for member access.
- **Table descriptor chain**: loads from [r9+0x6c30], [r8+0x28], [r8+0x55bc], [r8+0x55c0] — used for size/limit (0xc(ptr)) and **lhz 0x28(r9)** (entry-size–related).
- **Stack struct** at r1+0x24: **0x28** bytes; memset 0x28, then **stw 0x200** at 0x28(r1), **stw -1** at 0x30(r1), **stw r29** at 0x24(r1) (ptr), and saved r0 from r30-0x7fe4, -0x7fe0, -0x7fdc at 0x1c, 0x20, 0x14(r1). Passed to later calls.
- **Call 017c7b34**: r3=unit, r4=(0x28(r9)+3)&~3, r5=from GOT; **mullw r4,r4,r0** — alloc or size calc using entry size and count.
- **Call 018788bc**: r3=unit, **r4=0x1570** (table ID), r5=-1, r6=r31, r7=r24, r8=r18 (buffer). So this path uses **table ID 0x1570** for the ECMP write, not 0x6418/0x6419/0x8a8 in this code path; those IDs may be used elsewhere or in data.
- **Member iteration**: r23 = count (from 0x68(r9), cntlzw); r21 = r23*8, r22 = r23*4; r29 = r31*8, r28 = r31*4; loop over **0x134(r26)[r29]** and **0x10c(r9)[r28]** (andi. 0x18 on word). So **stride 8** for one array and **stride 4** for the other (indices r31, r23).

---

## Tentative ECMP layout (from 01a1572c)

- **Unit struct**: 0x138 = group base or first index, 0x13c = group count or last index; 0x134 = pointer to member array (stride 8); 0x10c in per-unit block = second array (stride 4).
- **Table ID**: **0x1570** passed to 018788bc (generic table write).
- **Entry size**: derived from **lhz 0x28(r9)** in descriptor; size used in mullw for alloc.
- **0x6418, 0x6419, 0x8a8**: Not present as immediates in dumped 01a1572c; likely used in other branches or in data (e.g. table name → ID map). See TABLE_ID_MAPPING_ANALYSIS.md.

---

## References

- [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md) §3 (ECMP group layout)
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)
- Dump: `libopennsl-dump-01a1572c.txt`

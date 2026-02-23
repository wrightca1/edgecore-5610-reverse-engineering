# L2 Table Access Analysis (libopennsl)

**Source**: `opennsl-table-addr-xrefs.txt`, `opennsl-table-name-to-addr-xref.txt`

## L2_USER_ENTRY (0x0180c200)

From opennsl-table-addr-xrefs and TABLE_NAME_MAPPING:

| Address    | Function       | Access | Instruction        |
|------------|----------------|--------|--------------------|
| 0x180c200  | FUN_00881edc   | READ   | lwz r11,0x0(r9)    |
| 0x180c200  | FUN_00948700   | READ   | lwz r10,0x0(r9)    |
| 0x180c200  | FUN_01cc2f2c   | READ   | lwz r8,0x0(r11)    |

Functions referencing L2_USER_ENTRY name: 20 (from opennsl-table-name-to-addr-xref).

## L2_ENTRY

Table addresses in 0x13xxxxx–0x18xxxxx range. Many functions reference L2_ENTRY string and table addresses (418+ xrefs).

## Layout inference

- OpenNSL `opennsl_l2_addr_t` (API layer, from l2.h): `flags`, `reserved1`, `reserved2`, `mac` (6B), `vid` (2B), `port`, `modid`, `tgid`, `l2mc_group`, etc.
- Flags: OPENNSL_L2_STATIC (0x20), OPENNSL_L2_HIT (0x40), OPENNSL_L2_COPY_TO_CPU (0x08), OPENNSL_L2_L3LOOKUP (0x10), etc.
- Access pattern `lwz rX,0x0(rY)` indicates 32-bit word read; hardware L2_USER_ENTRY is multi-word (ASIC format differs from API struct).

## Call chain (from FindL2Callers)

- **FUN_00946a00** → FUN_00948700 → FUN_01cc2f2c. FUN_00946a00 is top-level L2 path.

## Callers of FUN_00946a00 (L2 top)

From libopennsl-callers-of-0x946a00.txt: 2 callers — FUN_0092c64c (from 0092c85c), FUN_009307a4 (from 00930a0c).

**FUN_0092c64c** (dumped): Validates unit (r3 ≤ 17), table lookup from r30-0x7ff4/0x7ff8/0x7fec; calls FUN_00973f6c, 0x01393e80 (r3=0x2003005), FUN_01d2f1f0; checks struct at 0x24, offsets 0x7184/0x7188. Part of L2 add path.

**FUN_009307a4** (dumped): L2 opcode dispatcher. Validates r4 ≤ 0x30; indirect jump via table at r30-0x7eb8 indexed by r4*4. Fallthrough calls FUN_0094e450, FUN_00a68ef0. Different r4 values → different handlers (0093082c→FUN_0089c230, 0093083c→FUN_00b2bbb4, 0093084c→FUN_009af1fc).

**FUN_01d2f1f0** (dumped): Large frame 0x640. Unit-based index r26 = r3*32 + r3*256; table at r23+0x48; checks [r29+0x1488], [r9+0x7194]. L2 state/alloc handling.

**FUN_00973f6c** (dumped): Unit validation, loads from [r30-0x8000][r3*4]; checks [r11+0x10], [r11+0x14] with masks 0x1921200, 0x8000, 0x40, 0x20, 0x800, 0x1000. Calls 0x01393e80 (r3=0x102004) on early path. L2 capability/init check.

**FUN_0094e450** (dumped): Calls FUN_018124a8; sets bit at [r9+0x78]; struct access at 0x78, 0x10. L2/table setup.

**FUN_00a68ef0** (dumped): Unit table lookup; checks [r9+0x71c4] & 0x80; loads from 0x6c30, 0x28, 0x6bdc, 0x4654. L2/ECMP path.

**FUN_0089c230**, **FUN_00b2bbb4**, **FUN_009af1fc** (dumped): L2 opcode handlers from FUN_009307a4 dispatch. FUN_009af1fc checks [r9+0x7190] & 0x10; calls FUN_01a56740, FUN_01a574e4.

## Next steps

1. Correlate opennsl_l2_addr_t fields with ASIC L2_USER_ENTRY format (Ghidra on write path; S-Chan memory-write opcodes).
2. See [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md) for S-Channel call chain.

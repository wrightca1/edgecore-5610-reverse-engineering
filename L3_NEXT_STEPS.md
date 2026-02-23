# L3 / ECMP / VLAN — next steps (Path B 3.4–3.8)

**Purpose**: Concise “what we have” and “what to do next” for L3 route, egress, ECMP, and VLAN table layouts and write path.

---

## Have

- **Call chain**: API → … → **FUN_018d7ad4** (table ID validator) → **FUN_018d62ec** (write wrapper) → **FUN_018d43e4** (init **0x224-byte** struct), then dispatch. [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md)
- **Table IDs** (from FUN_018d7ad4 / TABLE_ID_MAPPING_ANALYSIS):
  - **0x22d3 / 0x22ca** → L3_DEFIP
  - **0x2c32 / 0x2c33** → L3_ECMP
  - **0x1559–0x155e, 0x1599, 0x2c24, 0x15a5** → L3-related
  - **0x6418, 0x6419, 0x8a8** → L3_ECMP (from FUN_01a1572c)
- **Dispatcher call sites**: [libopennsl-table-dispatcher-analysis.txt](../build-server/opennsl/sdk-deep-extract/libopennsl-table-dispatcher-analysis.txt) — 5 call sites to FUN_018d7ad4; r7 (table ID) from param/memory, not immediate.
- **L3_DEFIP / L3_ECMP name refs**: FUN_01b0c9a0 (L3_DEFIP), FUN_01a1572c (L3_ECMP).

---

## Next steps (in order)

1. **Per–table layout**
   - For each table ID (0x22d3, 0x2c32, 0x1559–0x155e, …): in Ghidra, follow the path from FUN_018d62ec/FUN_018d43e4 for that ID and list **stores** into the 0x224-byte (or table-specific) buffer: offset → field (prefix, mask, next_hop, egress_id, port, MAC, etc.). Use OpenNSL types (e.g. opennsl_l3_route_t, opennsl_l3_egress_t) as hints.
   - **From 018d62ec (354-insn dump)**: Buffer at **r1+0x6c** (0x224 bytes). FUN_018d43e4 only **memset** and stores -1 at 0x204–0x220. The buffer is then passed as **r6** to **FUN_014a51e8** (after table checks 0x30/0x33/0x36/0x14 etc.) or **FUN_0170b700** (other path). Table ID **r24** is checked (0x1559–0x155e, 0x155c, 0x155d, 0x1567, 0x154c, 0x1561, 0x152b, 0x1529). So **per-table layout** lives in **014a51e8** and **0170b700** — dump those and list stores into the buffer (r6 = r1+0x6c).
   - **Done**: Dumped 014a51e8 and 0170b700 (220 insn each). Store list and tentative layout in **[L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md)**: 0x0 = op (4/6/8), 0x4/0x44 = entry array (e.g. table 0x1555), 0x84/0x9c/0xb4/0xcc = indices, 0x204–0x214 = format constants (0xa9e2, 0x95d6, 0x4fcc, etc.).

2. **Write mechanism**
   - Confirm whether this path uses **S-Chan memory write** (like L2) or **direct BAR** write. Trace FUN_018d62ec / FUN_018d43e4 callees to FUN_007042f0 or to stores into mmap’d table-memory range (0x01000000–0x01ffffff). [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md) notes FUN_01876f10 as generic table write; check if it calls S-Chan.
   - **Current state**: FUN_01876c30 loads a handler from per-unit table (`[r28][r31*4]` then offset -0x6b7c) and calls it via **bctrl** with buffer in r4. The handler is table-type–specific; confirming S-Chan requires either (a) running a Ghidra “callers of FUN_007042f0” and checking if any lie on the 01876f10→01876ee0→01876c30 path, or (b) GDB on switch: break at 0x007042f0 during an L2/L3 add and see if it hits.
   - **Checked**: FUN_01876f10 does **not** call FUN_007042f0; it branches to **01876ee0** → 01876c30 → bctrl to per-unit handler. No `bl 0x007042f0` in 01876f10 dump. S-Chan use (if any) is inside the **indirect handler**; static "callers of 007042f0" in repo only list 007045d0 (internal to 007042f0).

3. **ECMP group layout**
   - FUN_01a1572c references L3_ECMP and IDs 0x6418/0x6419/0x8a8. Dump that function and any callers; document how ECMP group members and next-hops are laid out (entry size, stride, link to egress table).
   - **Done**: Dumped 01a1572c (184 insn). **[ECMP_GROUP_LAYOUT_FROM_01a1572c.md](ECMP_GROUP_LAYOUT_FROM_01a1572c.md)** — table ID **0x1570** passed to 018788bc; unit struct 0x138/0x13c (group), 0x134 (array stride 8), 0x10c (stride 4); entry size from lhz 0x28(descriptor). IDs 0x6418/0x6419/0x8a8 not in this path (other branch or data).

4. **VLAN_XLATE (3.9)**
   - Resolve table address from [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md); find functions that read/write that address; same process: stores into buffer → field layout.
   - **From libopennsl-table-name-to-dispatcher-chain.txt**: **FUN_018d4770** references VLAN_XLATE (12 functions total); chain → FUN_01876f10. **Table IDs** 0x6418, 0x6419, 0x8a8, 0x645d, 0x8a4 (li r4 at 014affc4–014b0640, 01742d10–01742da8). Dumped 018d4770 — validator/alloc (017c7b34), unit table lookups, strides 0xec/0x3a4.
   - **Dumped FUN_014aec60** (VLAN_XLATE path): uses **table ID 0x8a6**, calls **0181f7dc** (same as L2!) with buffer at r1+0x8, then **01876f10**. So this path reuses the **0x24-byte L2-style buffer** (0181f7dc → 0181f080 → 0181e718). Layout is same as L2_USER_ENTRY (descriptor-driven); field mapping needs VLAN-specific descriptor for 0x8a6.

5. **Hash/index (3.10)**
   - For L3 (and L2 if hash-based): in Ghidra, find where **hash** or **index** is computed before table insert (e.g. calls to a hash function, or mask/shift of key). Document key format and index derivation.
   - **L2**: Index is passed as **r6** to FUN_01876f10 from FUN_01408a48 ([L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)). **Done**: [L2_INDEX_SOURCE_FROM_DUMPS.md](L2_INDEX_SOURCE_FROM_DUMPS.md) — 01cc2f2c uses retry 0..5 (linear probe); 00948700 passes -1 (auto). No hash in these paths; hash/key→index would be elsewhere.

---

## Scripts

- `run-analyze-table-dispatcher-call-sites-on-build-server.sh` — already run; output in libopennsl-table-dispatcher-analysis.txt.
- `run-dump-func-on-build-server.sh libopennsl.so.1 018d43e4` (and 018d62ec, 018d7ad4) — dump assembly for manual layout inference.
- `run-find-l3-table-callers-on-build-server.sh` — L3_DEFIP / L3_ECMP / VLAN_XLATE name refs.

---

## References

- [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md)
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md), [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) §4 (L3/ECMP/VLAN)

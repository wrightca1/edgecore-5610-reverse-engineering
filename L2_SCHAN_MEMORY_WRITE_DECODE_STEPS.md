# L2 S-Chan memory-write decode — Ghidra steps (Path B 3.3, 3.8)

**Goal**: Recover ASIC **L2_USER_ENTRY** format (field layout, size, byte order) by tracing how the L2 write path builds the S-Channel memory-write payload.

**Reference**: [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md) (command word `(val & 0x7fff) | 0x28000000`), [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md) (call chain, L2_USER_ENTRY @ 0x180c200).

---

## 1. Entry points

| Item | Address / name | Role |
|------|----------------|------|
| S-Chan command builder | **FUN_00703dc0** | Encodes word `(r4 & 0x7fff) \| 0x28000000`; callers pass payload in *r4 |
| S-Chan callers | **FUN_007042f0**, **FUN_00704790**, **FUN_00704784** | Build command and call 00703dc0 |
| L2 write chain | **FUN_00946a00** → **FUN_00948700** → **FUN_01cc2f2c** | L2_USER_ENTRY (0x180c200) read in FUN_01cc2f2c |

---

## 2. Ghidra steps (manual)

1. **Find where S-Chan is used for a memory write to table memory**
   - In **FUN_007042f0** / **FUN_00704790** / **FUN_00704784**: follow data flow into the pointer passed to FUN_00703dc0 (r4). Identify whether this path is used for table writes (vs other S-Chan ops).
   - Search for xrefs to **0x180c200** (L2_USER_ENTRY) and list functions that **write** (store) to that address or to a buffer that is later sent via S-Chan.

2. **Trace L2 write path into S-Chan**
   - From **FUN_01cc2f2c** (L2 path that reads L2_USER_ENTRY): find callers and see if any eventually call FUN_007042f0 / FUN_00704790 / FUN_00704784 or another S-Chan submit path.
   - Alternatively: from FUN_007042f0, trace backward — which callers pass a buffer that holds L2 entry data? Look for struct layout (MAC, VLAN, port, flags) consistent with opennsl_l2_addr_t.

3. **Decode the payload struct**
   - Once you have the function that fills the S-Chan memory-write payload for L2:
     - List all **stores** (stw, stb, etc.) to that buffer: offset and size.
     - Map offsets to logical fields: MAC (6 B), VLAN (2 B), port, flags/valid/static/hit, etc., using OpenNSL `opennsl_l2_addr_t` as a hint.
   - Note **byte order** (big-endian from PowerPC) and **entry size** (number of bytes written before S-Chan submit).

4. **S-Chan opcode/subop**
   - In the code that submits the command, check for constants that select “memory write” vs “memory read” and table ID or base address (e.g. 0x180c200 or a table ID that maps to L2_USER_ENTRY). Compare with [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md).

---

## 3. Scripts / automation (optional)

- **FindL2Callers** already gives FUN_00946a00 → FUN_00948700 → FUN_01cc2f2c.
- **DumpFunctionCode** for FUN_01cc2f2c, 007042f0, 00704790, 00704784 already in build-server/opennsl/sdk-deep-extract/.
- **From dumps**: [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md) — L2 write uses **table ID 0x1547**, **0x24-byte** payload. **0181f080** tail-calls **0181e718**; **0181e718** (r29=buffer) fills the payload using descriptor r26 (offsets 0x4,0x6,0x8) and buffer+offset (add r7,r29,r7). Annotate 0181e718 for all stw/stb/sth to r29 to get final ASIC layout.

---

## 4. Output to document

- **L2_USER_ENTRY ASIC layout**: table of byte offset → field name (MAC, VLAN, port, valid, static, hit, …) and size.
- **S-Chan memory-write**: opcode/subop (if any) and how table address 0x180c200 is specified (immediate, register, or table ID).
- **Mapping**: opennsl_l2_addr_t field → ASIC L2_USER_ENTRY offset (for code that converts API struct to hardware format).

# L2 payload layout from function dumps (Path B 3.3, 3.8)

**Source**: Existing Ghidra dumps (libopennsl-dump-01cc2f2c.txt, libopennsl-dump-01408a48.txt). Complements [L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md](L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md).

---

## FUN_01cc2f2c (L2 path) — stack struct at r1+0x30

From the assembly, the function builds a small struct on the stack and passes it along:

| Offset (r1+) | Instruction | Content (from context) |
|--------------|-------------|-------------------------|
| 0x30 | stw r7,0x30(r1) | r7 = 0x11 (constant) |
| 0x38 | stw r8,0x38(r1) | r8 = [r11] (loaded from L2 source) |
| 0x3c | sth r10,0x3c(r1) | r10 = half at 0x4(r11) |
| 0x3e | stw r11,0x3e(r1) | r11 = [r9] (note: 0x3e is unaligned; may be packed) |
| 0x42 | sth r9,0x42(r1) | r9 = half at 0x4(r9) |

Then: `bl 0x01cbd2e0` with r4 = r1+0xc, r5 = r1+0x30 (so 0xc is a different buffer/descriptor). Later: `bl 0x01408a48` with r4 = r1+0xc (in caller), r6 = result ptr.

**Interpretation**: The 0x30 struct looks like: 4B (0x11) + 4B + 2B + 4B + 2B = at least 16 bytes; likely MAC/VLAN/port-related. Full L2 payload is built elsewhere (01cbd2e0 or 01408a48).

---

## FUN_01408a48 — L2 write via FUN_01876f10

- **Table ID**: **0x1547** (li r4,0x1547) — L2 table.
- **Payload size**: **0x24** (36 bytes) — li r5,0x24; passed to 0x02f52328 (copy) and buffer at r1+0xc passed as r7 to FUN_01876f10.
- **Flow**: Copies 0x24 bytes into buffer at r1+0xc, then calls **FUN_01876f10** (r3=unit, r4=0x1547, r5=-1, r6=index, r7=buffer). So the **ASIC L2 table write** uses a **36-byte** payload and table ID **0x1547**.

---

## L2_USER_ENTRY size and layout (inferred)

- **Size**: **0x24** (36 bytes) for the buffer passed to the generic table write (FUN_01876f10).
- **Fields**: To be filled by mapping stores in 01cbd2e0 and the copy source into MAC (6B), VLAN (2B), port, flags, etc. OpenNSL `opennsl_l2_addr_t` and the 01cc2f2c stack struct (0x11, two 4B+2B pairs) are hints; exact ASIC bit layout still needs store-by-store decode in 01cbd2e0 and any function that fills the 0x24-byte buffer before the copy.

---

## FUN_01cbd2e0 (L2 entry builder) — input struct and 0x24-byte buffer

**Args**: r4 = output buffer (0x24 bytes), r5 = input struct (from 01cc2f2c stack struct at r1+0x30).

- **memset(r28, 0, 0x24)** at 01cbd3d0 (bl 0x02f52440) — clears the L2 payload buffer.
- **Input struct (r31) layout**:
  - **0x00**: word; bit 0x20 checked (OPENNSL_L2_STATIC).
  - **0x08**: passed as 7th arg to 0x01820598 (addi r7,r31,0x8) — likely **MAC (6 B)** start.
  - **0x14**: halfword (lhz); used for VLAN range check (rlwinm r9,r0,0x14,0xc,0x1f; compare with 0xfff).
  - **0x2c**: word; compared/used for port or modid (slw r3,r11,r3; cmpw with r9).
- **Callees that fill the 0x24-byte buffer**:
  - **0181f7dc** → **0181f080** (passes r7=1; thin wrapper).
  - **01820598** (r7 = input+8 = MAC): loads **6 bytes** at 0..5(r7), packs them into **two 32-bit words** (big-endian), stores at r1+8 and r1+0xc, then calls **0181f080**. So **MAC at input+8** is converted to two words and passed to 0181f080, which likely writes them into the 0x24-byte buffer at specific offsets. Dump **0181f080** for the exact store offsets into the L2 payload.

So the **API-side input** has flags at 0x0, **MAC (6 B) at 0x8**, VLAN at 0x14, port/modid at 0x2c. The **ASIC 0x24-byte payload** is built by 0181f080 (called from 0181f7dc and 01820598); 01820598 confirms MAC lives at input+8.

---

## Write path summary

- **01cc2f2c** builds stack struct (0x11, words/halfs from L2 source) → **01cbd2e0** (memset 0x24, then 0181f7dc + 01820598 to fill buffer from input) → **01408a48** (copy 0x24 bytes, call **01876f10** with table 0x1547) → **01876ee0** → **01876c30** (indirect call to per-table handler; handler does S-Chan or BAR write).

---

## FUN_0181f080 (shared by 0181f7dc and 01820598)

Validates table ID (r4 ≤ 0x2c67), loads per-unit table and descriptor; at **0181f1d8** it does **b 0x0181e718** (tail-call). So the buffer (r5) is passed to **FUN_0181e718**.

## FUN_0181e718 (writes into L2 buffer)

- **Args**: r3=unit, r4=table id, r5=**buffer** (0x24-byte), r6=r28, r7=r27. Buffer is in **r29** (r29=r5).
- Calls **0181c73c** (r3=r26, r4=r27); then loads from descriptor r26: **lhz 0x4(r26), 0x6(r26), 0x8(r26)** (likely size/type fields).
- **Buffer-relative addresses**: **add r7,r29,r7** and **add r11,r29,r9** (0181e924, 0181e928) — so it computes buffer+offset and writes via those pointers. Loop at 0181e940 uses r31 (input), r11/r28 (buffer+offset), r23/r24 (masks).
- So the **0x24-byte L2 payload** is filled in **0181e718** (and possibly 0181c73c). Exact byte offsets for each field need a full dump of 0181e718 with store instructions (stw/stb/sth) annotated; the descriptor at r26 drives layout (offsets 0x4, 0x6, 0x8 used).

---

## Stores to buffer in FUN_0181e718 (from 250-insn dump)

Buffer base is **r29** (r29 = r5 on entry). Offsets are computed from descriptor r26 (fields at 0x4, 0x6, 0x8) and from r31 (input): e.g. **r7 = (r10+1)*4**, **r9 = r9*4** (word indices), **add r7,r29,r7**, **add r11,r29,r9**. Then:

| Address   | Instruction      | Target        | Notes |
|-----------|------------------|---------------|--------|
| 0181e9d4  | **stwx r0,r29,r5** | buffer + r5   | r5 = word offset (from 0x28(r31)); direct buffer[r5] |
| 0181e998  | stw r25,0x0(r28) | r28 = buffer+offset | r28 from r11 or r5 (buffer+offset) |
| 0181ea20  | stw r4,0x0(r5)   | r5 = buffer+offset | in loop |
| 0181ea68  | stw r0,0x0(r5)   | r5 = buffer+offset | in loop |
| 0181eae4  | stw r8,0x0(r4)  | r4 = buffer+offset | r4 from add r5,r29,r5 |

So the **0x24-byte** buffer is written **word by word** (stw); offsets come from descriptor (0x4, 0x6, 0x8) and input (0x28(r31)). To get a **byte-offset → field** table: trace r5, r7, r9, r10 and the loop counter from descriptor values for one concrete L2 add, then map each store’s offset to MAC/VLAN/port/flags (e.g. first word = flags, next 2 words = MAC, etc.).

### Descriptor (r26) and offset formulas

- **0x4(r26)** → r8: treated as **bit width** (e.g. field size); used in `subi r5,r8,0x1` then `rlwinm r5,r5,0x1b,0x5,0x1f` and `addi r5,r5,0x1` → loop count = `((r8-1)>>5)+1` (number of 32-bit words).
- **0x6(r26)** → r9: **bit index / word index** source; `rlwinm r3,r9,0x0,0x1b,0x1f` = r3 = r9 & 0x1f (bit within word); `srawi r9,r9,0x5` = r9 = r9>>5 (word index); then `r7 = (r9+1)*4`, `r9 = r9*4` (byte offsets into buffer).
- **0x8(r26)** → r0: used in offset for **stwx** path: `lhz r5,0x28(r31)`, `(r5+3)/4 - 1 - r0` → word offset into buffer (so **0x28(r31)** is an “extended” or VLAN-related word index from the input struct).

So the loop writes a **bitfield** that can span multiple words; descriptor defines width (0x4) and start (0x6); input 0x28(r31) selects which word is updated for the **stwx** store. For a single 0x24-byte L2 entry, typical values would yield word offsets 0..8 (9 words). Mapping to MAC/VLAN/port still needs one concrete run (or table ID 0x1547 descriptor layout from OpenNSL/BCM docs).

---

## Next

- Trace one full L2 add path with concrete descriptor values to resolve **r5/r7/r9** per iteration → build L2_USER_ENTRY byte layout table.
- FUN_01876c30 dispatches via **bctrl** to a handler from per-unit table; that handler is where S-Chan or BAR write occurs (not in 01876c30 itself).

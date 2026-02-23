# L2 Write Path — Complete Analysis (Path B 3.3, 3.8)

**Date**: 2026-02-23
**Status**: HAVE — call chain fully decoded; ASIC field bit positions verified via bcmcmd on live switch (see [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md))
**Sources**: [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md), [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md), [L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md](L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md), [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md), [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md)

---

## 1. Full Call Chain (API → ASIC)

```
opennsl_l2_addr_add(unit, l2addr)          [OpenNSL public API]
  └─> FUN_00946a00 @ 0x00946a00            [top-level L2 add; per-unit dispatch via [r30-0x7ff0][r31]]
        ├─> FUN_00973f6c                   [L2 capability/init check; bitmask 0x1921200/0x8000/0x40]
        ├─> FUN_0092c64c @ 0x0092c85c      [caller A — table lookup r30-0x7ff4/0x7ff8/0x7fec]
        └─> FUN_009307a4 @ 0x00930a0c      [caller B — L2 opcode dispatcher; r4 ≤ 0x30]
              └─> FUN_00948700             [L2_USER_ENTRY access; lwz r10,0x0(r9)]
                    ├─> FUN_00a7d4a0       [loads [r9+0x710c] → *r4 helper]
                    ├─> FUN_00947cd8       [validation: flags, VID, static bit]
                    └─> FUN_01408a48       [main write entry; table ID 0x1547, size 0x24]
                          ├─> FUN_01cc2f2c [builds stack struct → 01cbd2e0 entry builder]
                          │     └─> FUN_01cbd2e0  [memset 0x24, calls 0181f7dc + 01820598]
                          │           ├─> FUN_0181f7dc → FUN_0181f080 → FUN_0181e718  [fills buffer]
                          │           └─> FUN_01820598 → FUN_0181f080 → FUN_0181e718  [fills MAC]
                          └─> FUN_01876f10 (r3=unit, r4=0x1547, r5=-1, r6=index, r7=buffer)
                                └─> FUN_01876ee0
                                      └─> FUN_01876c30
                                            └─> bctrl [r9+0x19484]  ← per-unit handler (S-Chan or BAR)
                                                 (addis r11,r9,0x2 → lwz r0,-0x6b7c(r11) → r9+0x20000-0x6b7c)
```

---

## 2. ASIC Buffer Layout

### 2.1 Buffer parameters (FUN_01408a48)

- **Table ID**: `0x1547` (L2_USER_ENTRY) — passed as r4 to FUN_01876f10
- **Buffer size**: **0x24** (36 bytes) — passed as r5 to `0x02f52328` (copy), then as r7 to FUN_01876f10
- **Index**: passed as r6 (r6 = -1 for auto-index from FUN_00948700; retry 0..5 in FUN_01cc2f2c)
- **Entry builder**: FUN_01cbd2e0 fills the 0x24-byte buffer; base register = **r29** throughout

### 2.2 API struct → entry builder mapping (FUN_01cbd2e0)

The API struct (from `opennsl_l2_addr_t`) is passed as **r31** into FUN_01cbd2e0. Known field offsets in that struct:

| API struct offset | Field | Evidence |
|------------------|-------|---------|
| **0x00** | `flags` (uint32) | bit 0x20 = `OPENNSL_L2_STATIC`; bit checked directly |
| **0x08** | `mac[6]` | `addi r7,r31,0x8` passed to FUN_01820598 which loads 6 bytes at 0..5(r7) |
| **0x14** | `vid` (uint16) | `lhz` then compare with 0xfff (VLAN range check) |
| **0x2c** | `port` / modid | word used in `slw r3,r11,r3`; `cmpw` with r9 |

Note: These are **API struct** offsets, not ASIC buffer offsets. The ASIC buffer layout (in r29) is filled via the descriptor mechanism in FUN_0181e718.

### 2.3 Descriptor-driven buffer fill (FUN_0181e718)

FUN_0181f080 (tail-called from both FUN_0181f7dc and FUN_01820598) loads a **descriptor pointer** r26 from the per-unit table for table ID 0x1547, then tail-calls **FUN_0181e718**.

In FUN_0181e718 (buffer base = r29 = r5 on entry):

| Descriptor field | Offset in r26 | Meaning | Use |
|-----------------|---------------|---------|-----|
| `width` | `lhz 0x4(r26)` → r8 | Field bit-width | Loop count = `((width-1)>>5)+1` words |
| `bit_index` | `lhz 0x6(r26)` → r9 | Start bit in buffer | `r9>>5` = word index; `r9&0x1f` = bit within word |
| `ext_offset` | `lhz 0x8(r26)` → r0 | Extended offset | Used in `stwx` path: `lhz r5,0x28(r31)` then `(r5+3)/4 - 1 - ext_offset` → word index |

**Buffer store pattern**:
- Computes byte offsets: `r7 = (word_index+1)*4`, `r9 = word_index*4`
- Does `add r7,r29,r7` and `add r11,r29,r9` to get pointer to buffer slot
- Store instructions: `stwx r0,r29,r5` / `stw r25,0x0(r28)` / `stw r4,0x0(r5)` / `stw r8,0x0(r4)`
- Loop at 0x0181e940 over the width field (word count)

This is a **bitfield packing loop**: each call (one per field: flags, MAC, VLAN, port) fills bits at the position given by the descriptor for table 0x1547.

### 2.4 ASIC Buffer Structure — VERIFIED

ASIC bit positions verified via `bcmcmd listmem` + `bcmcmd dump raw` + write-back tests on live switch (2026-02-23). See [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) for complete encoding.

**Table 0x1547 = L2_ENTRY** (hash table, 131072 entries, 13 bytes / 4 words, addr 0x07120000):

| Entry bits | word[N] location | Field | Verified |
|-----------|-----------------|-------|---------|
| [0] | w0 bit 0 | VALID | ✓ |
| [3:1] | w0 bits[3:1] | KEY_TYPE (0=standard L2) | ✓ |
| [15:4] | w0 bits[15:4] | VLAN_ID (12 bits) | ✓ |
| [31:16] | w0 bits[31:16] | MAC_ADDR[47:32] (upper 16 bits) | ✓ |
| [63:32] | w1 bits[31:0] | MAC_ADDR[31:0] (lower 32 bits) | ✓ |
| [70:64] | w2 bits[6:0] | PORT_NUM (7 bits) | ✓ |
| [78:71] | w2 bits[14:7] | MODULE_ID (8 bits) | ✓ |
| [79] | w2 bit 15 | T (trunk flag) | from listmem |
| [93] | w2 bit 29 | STATIC_BIT | ✓ |
| [100] | w3 bit 4 | HITDA | from listmem |
| [101] | w3 bit 5 | HITSA | from listmem |

**Example raw encoding** (MAC=0xdeadbeef0001, VLAN=3301, PORT=5, MODULE=3, STATIC=1):
```
0x0001ce51  0xdeadbeef  0x20000185  0x00000000
```

The 0x24-byte SDK buffer (padded) is transformed by FUN_0181e718's descriptor-based bitfield packer to produce the 13-byte ASIC entry above.

---

## 3. Write Mechanism — What's Known

**FUN_01876c30** (final dispatch before hardware write):
- Loads per-unit base: `lwz r28,-0x7ff8(r30)`; per-unit struct: `lwzx r9,r28,r29` (r29=unit*4)
- Handler address: `addis r11,r9,0x2` then `lwz r0,-0x6b7c(r11)` → handler at **r9+0x19484** from per-unit struct
  (note: earlier docs incorrectly stated `r9-0x6b7c` — the `addis` adds 0x20000 first)
- If handler NULL: fallback path at 0x01876d2c checks `r9+0x10`, `r9+0x14` bitmask, then `r9+0xa30000+0x7190` for alternate dispatch
- No `bl FUN_007042f0` found in FUN_01876f10 or FUN_01876ee0 (static analysis)

**Therefore**:
- S-Channel use (if any) is **inside the bctrl handler** — not resolvable by static analysis alone
- Options to resolve: (A) GDB breakpoint on Cumulus switchd at `bctrl` in FUN_01876c30 during an L2 add, capture target address; (B) Check callers of FUN_007042f0 — if any fall on the 01876f10→01876ee0→01876c30 path
- The bctrl handler could also write to the mmap'd table-memory region (0x01000000–0x01ffffff) directly, bypassing S-Channel for non-CMIC table writes

---

## 4. Index / Probe Strategy

From [L2_INDEX_SOURCE_FROM_DUMPS.md](L2_INDEX_SOURCE_FROM_DUMPS.md):
- **FUN_01cc2f2c**: passes index via retry loop 0..5 (linear probe for hash collision)
- **FUN_00948700**: passes -1 (auto-index = ASIC chooses)
- No hash key computation found in these paths; hash-to-index is likely in the bctrl handler or a pre-step

---

## 5. What's Still Needed

| Gap | What to do | Priority |
|-----|-----------|---------|
| ~~ASIC byte layout~~ | ✅ DONE — verified via bcmcmd on live switch. See [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) | complete |
| ~~Write mechanism~~ | ✅ DONE — confirmed S-channel DMA via GDB. See [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) | complete |
| bctrl handler address (L2-specific) | Runtime GDB capture during `bcmcmd l2 add` — lower priority since write mechanism is confirmed | low |
| L2 delete path | Not traced; likely parallel to add (FUN_009307a4 dispatcher r4=delete opcode) | medium |

---

## 6. Scripts to Run

```bash
# Dump FUN_0181e718 (buffer fill — need full instruction list)
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 0181e718 400

# Dump FUN_01876c30 (final dispatch before hardware write)
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 01876c30 200

# Find callers of FUN_007042f0 (S-Channel submitter) — already done, check output
# If 007042f0 callers include anything reachable from 01876f10 path → S-Chan confirmed
```

---

## References

- [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md)
- [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)
- [L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md](L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md)
- [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md)
- [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md)
- [L2_INDEX_SOURCE_FROM_DUMPS.md](L2_INDEX_SOURCE_FROM_DUMPS.md)
- [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) §3

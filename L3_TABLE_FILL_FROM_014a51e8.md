# L3 Table Buffer Fill — FUN_014a51e8 Analysis

**Date**: 2026-02-21
**Status**: PARTIAL — table ID dispatch and buffer stores decoded; index computation partially traced
**Sources**: [build-server/opennsl/sdk-deep-extract/libopennsl-dump-014a51e8.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-dump-014a51e8.txt)
**Context**: FUN_014a51e8 fills the 0x224-byte L3 write buffer; called from FUN_018d62ec

---

## 1. Function Signature

```
FUN_014a51e8(r3=unit, r4=table_id, r5=arg5, r6=buffer_ptr, ...)
```

After prologue:
- **r26** = unit (r3)
- **r31** = table_id (r4)
- **r24** = input index / key value (r5 — used as L3 prefix index, nexthop, or ECMP member)
- **r28** = buffer_ptr (r6 — the 0x224-byte buffer at r1+0x6c in FUN_018d62ec)

---

## 2. Table ID Dispatch Table

The function opens with a binary tree of `cmpwi` comparisons on r31 (table_id):

| Table ID | Target | Notes |
|----------|--------|-------|
| `0x1514` | 014a5868 | Sub-table |
| `0x1515` | 014a576c | Sub-table |
| `0x1559–0x155e` | (range, falls through) | Main L3 sub-tables: 6 entries |
| `0x1584` | 014a540c | L3_DEFIP sub-table |
| `0x1588` | 014a540c | L3_DEFIP sub-table |
| `0x158c` | 014a540c | L3_DEFIP sub-table |
| `0x1590` | 014a540c | L3_DEFIP sub-table |
| `0x1597` | 014a540c | L3_DEFIP sub-table |
| `0x15a5` | 014a5834 | L3 variant |
| `0x2c32` | 014a5828 | L3_ECMP primary |
| `0x6fa` | 014a57d0 | Auxiliary |
| `0x124a` | (adjacent to 0x6fa path) | Auxiliary |
| other | → li r3,-0x4; return | Error (table not found) |

---

## 3. Format Constants Written to Buffer (common to many table IDs)

These constants are stored at fixed offsets in the 0x224-byte buffer. Two variants exist
depending on the table path:

### Variant A — used for tables 0x1559–0x155e (range check: `subi r31,r31,0x1559; cmplwi r31,0x5`)

```asm
014a5330: ori r0,r0,0xa9e2; stw r0,0x204(r28)   ; buf+0x204 = 0xa9e2
014a5340: ori r0,r0,0x95d6; stw r0,0x208(r28)   ; buf+0x208 = 0x95d6
014a531c: ori r0,r0,0x992c; stw r0,0x210(r28)   ; buf+0x210 = 0x992c
014a5328: li r0,0x5740;    stw r0,0x214(r28)    ; buf+0x214 = 0x5740
014a534c: li r0,0x8;       stw r0,0x0(r28)      ; buf+0x000 = 0x8  (op code 8 = write)
```

### Variant B — used for tables 0x1584, 0x1590, 0x1597, 0x1588, 0x158c

```asm
014a5464: ori r0,r0,0xb160; stw r0,0x210(r28)   ; buf+0x210 = 0xb160  (different from A)
014a5470: li r0,0x5740;     stw r0,0x214(r28)   ; buf+0x214 = 0x5740  (same)
014a5478: ori r0,r0,0xa9e2; stw r0,0x204(r28)   ; buf+0x204 = 0xa9e2  (same)
014a5484: ori r0,r0,0x95d6; stw r0,0x208(r28)   ; buf+0x208 = 0x95d6  (same)
014a548c: li r0,0x8;        stw r0,0x0(r28)     ; buf+0x000 = 0x8     (same)
```

### Op code values

| buf+0x000 | Meaning |
|-----------|---------|
| `0x8` | Write (confirmed for tables 0x1559–0x155e and 0x1584–0x158c) |
| `0x6` | Write variant (seen for tables 0x6fa, 0x124a) |

---

## 4. Index Computation — Table 0x1584 Path (representative)

For the `0x1584` path and related tables (L3_DEFIP physical sub-entries):

```asm
014a54ac: li r9, 0x1000      ; page_size = 4096
014a54b0: ori r10, r10, 0x8000  ; 0x8000
014a54b4: li r8, 0x2000      ; base_offset = 0x2000
014a54b8: divw r0, r24, r9   ; quotient = r24 / 4096
014a54bc: li r7, 0x3
014a54c0: add r11, r8, r10   ; 0x2000 + 0x8000 = 0xa000 (boundary_0)
014a54c4: mtspr CTR, r7      ; loop 3 times

; Per-iteration:
014a54c8: mullw r0, r0, r9   ; r0 = floor(r24/4096) * 4096
014a54cc: subf r0, r0, r24   ; r0 = r24 mod 4096 (remainder)
014a54d0: add r0, r8, r0     ; r0 = 0x2000 + (r24 mod 4096)
014a54d4: subf r8, r8, r0    ; (update r8)
014a54d8: cmpw cr7, r24, r11 ; if r24 < boundary (0xa000, 0x12000, 0x1a000)
014a54dc: blt cr7, 0x014a54e4
014a54e0: add r0, r8, r11    ; wrapped index
014a54e4: add r11, r11, r10  ; boundary += 0x8000
014a54e8: bdnz 0x014a54d8

014a54f0: stw r0, 0x84(r28)  ; buffer+0x84 = computed_index_0
014a54f8: mtspr CTR, r11     ; r11=0x8 → loop 7 more times
014a5500: lwz r0, 0x84(r28)
014a5504: add r0, r9, r0     ; index += page_size (0x1000)
014a5508: stw r0, 0x9c(r28)  ; buffer+0x9c = computed_index_1
014a550c: addi r28, r28, 0x18 ; buffer ptr += 0x18 per iteration
014a5510: bdnz 0x014a5500
```

**Interpretation**: L3_DEFIP table has multiple "banks" of 4096 entries each. The input value
r24 is an ASIC-level LPM index. The computation distributes it across banks:
- Bank 0: indices 0x2000–0x9fff (8K entries)
- Bank 1: 0x2000–0x11fff (next 8K)
- Bank 2: 0x2000–0x19fff (next 8K)

Stored results:
- `buf + 0x84`: physical table row index (bank-adjusted)
- `buf + 0x9c`: adjacent/paired row (index + 0x1000)

---

## 5. Entry Array Build — Tables 0x1559–0x155e

```asm
014a5550: rlwinm r0,r24,0x2,0x0,0x1d  ; r0 = r24 * 4 (word-align nexthop index)
014a5554: oris r10, r19, 0x2           ; r10 = (unit_hi << 16 | 0x2) | r0
014a5558: oris r9,  r19, 0x1           ; r9  = (unit_hi << 16 | 0x1) | r0
014a555c: or r11, r0, r19              ; r11 = r0 | r19
014a5560: or r9,  r9,  r0             ; r9  |= r0
014a5564: or r0,  r10, r0             ; r0  |= r10

014a556c: stw r10, 0x4(r29)           ; buf+0x44+4 = type-2 entry word (oris 0x2)
014a5570: stw r11, 0x84(r27)          ; entry_array[0]+0x84 = raw nexthop word
014a5574: stw r9,  0x88(r27)          ; entry_array[0]+0x88 = type-1 nexthop
014a5578: stw r0,  0x8c(r27)          ; entry_array[0]+0x8c = type-2 nexthop
```

Where:
- `r19 = rlwinm(r24,0x0,0x1e,0x1f)` = bits[30:31] of the input r24 (the low 2 bits of nexthop)
- `r29 = buf + 0x40` (second entry in array)
- `r27 = buf` (first entry base)

**Entry array format**: Each entry spans 0x40 bytes within the 0x224 buffer (entries at 0x4, 0x44,
0x84, 0xc4, ...). The `oris 0x1` / `oris 0x2` flags are type codes indicating nexthop entry type.

---

## 6. Iterator Structure (lines 014a55a4–014a5640)

For table IDs 0x1559–0x155e, there is an **outer loop** over all member entries:

```asm
; Outer loop state:
r25 = iteration counter (starts 0, increments to 7)
r24 += 0x800 per iteration  (index += 2048)
r23 += 0x2000 per iteration (something += 8192)
r27 += 0x18 per iteration   (entry base advances 24 bytes)
```

Then for each iteration, an **inner loop** calls the central dispatcher (013949c0) for each
valid member:
```asm
014a55f4: or r10, r0, r0     ; member_word → r10
014a5604: bl 0x013949c0      ; dispatch sub-write for this member
```

This is the multi-entry write for L3 tables: iterates up to 8 members, writing each via the
central dispatcher.

---

## 7. Confirmed Format Constants vs Earlier Docs

| Offset | Value (Variant A) | Value (Variant B) | Field |
|--------|------------------|------------------|-------|
| `buf+0x000` | `0x8` (op=write) | `0x8` | Operation code |
| `buf+0x204` | `0xa9e2` | `0xa9e2` | Format ID word 0 |
| `buf+0x208` | `0x95d6` | `0x95d6` | Format ID word 1 |
| `buf+0x20c` | `-1` (init) | `-1` | Sentinel (from 018d43e4 init) |
| `buf+0x210` | `0x992c` | **`0xb160`** | Format ID word 3 (differs by table!) |
| `buf+0x214` | `0x5740` | `0x5740` | Format ID word 4 |

**Key finding**: The 0x210 word distinguishes Variant A (0x992c, for 0x1559–0x155e range) from
Variant B (0xb160, for 0x1584/0x1590/0x1597/0x1588/0x158c). These are likely table format
version IDs used by the bctrl handler to know the buffer layout.

---

## 8. Remaining Gaps

| Gap | Action | Priority |
|-----|--------|----------|
| L3_DEFIP field layout (prefix, mask, nexthop) | Trace stores at buf+0x4..0x3c for table 0x22d3 specifically (not 0x1559 range) | HIGH |
| Exact nexthop encoding (bits[30:31] meaning) | Cross-reference OpenNSL `bcm_l3_egress_t` field offsets | MEDIUM |
| FUN_0170b700 (alternate L3 fill path) | Dump already collected — see below | MEDIUM |

```bash
# FUN_0170b700 dump already available:
# build-server/opennsl/sdk-deep-extract/libopennsl-dump-0170b700.txt
# Still needs analysis
```

---

## References

- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) — caller chain and buffer layout overview
- [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md) — earlier buffer analysis
- [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md) — FUN_018d62ec and FUN_018d43e4
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — what happens after buffer is filled

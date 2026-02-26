# L3 / ECMP / VLAN Write Path — Complete Analysis (Path B 3.4–3.9)

**Date**: 2026-02-23
**Status**: MOSTLY HAVE — L3_DEFIP call chain + format fully decoded; ECMP table format decoded via bcmcmd; nexthop chain (ING/EGR_L3_NEXT_HOP + EGR_L3_INTF) fully verified with raw bit positions. VLAN_XLATE not used on this switch. See [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) for table layouts.
**Sources**: [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md), [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md), [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md), [ECMP_GROUP_LAYOUT_FROM_01a1572c.md](ECMP_GROUP_LAYOUT_FROM_01a1572c.md), [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)

---

## 1. Full L3 Write Call Chain

### 1.1 L3_DEFIP route write (table 0x22c9 / 0x22d3)

```
opennsl_l3_route_add
  └─> [chain] → FUN_01876c30 @ 01876c30    [generic table-write dispatcher]
        ├─ checks bctrl at unit_struct+0x19484 (hardware handler)
        ├─ if bctrl != NULL: call bctrl(unit, table_id, ..., data_ptr)  [HARDWARE path]
        └─ if bctrl == NULL: FUN_018758cc @ 018758cc  [SOFTWARE fallback path]
              ├─ FUN_01873404               [mutex/lock acquire]
              ├─ FUN_0187334c               [conditional ECMP flag check; returns data_ptr or
              │                              FUN_01869d7c result if unit_struct[0xa37190]&0x4000000]
              └─> FUN_018751e0 @ 018751e0   [L3_DEFIP write; 1 caller]
                    ├─ lhz 0x28(descriptor) [entry size from table descriptor]
                    ├─ cmpwi r27,0x22c9     [detect primary L3_DEFIP table]
                    ├─ if table==0x22c9: REMAP to physical table 0x22cf
                    │    r10 = entry_array_ptr + 0x8b3c  (= entry_array_ptr[0x22cf*4])
                    │    r16 = 0x8b3c (index offset)
                    │    r21 = 0x22cf (physical table ID)
                    ├─ bl 0x02f52328        [memcpy: pre-formatted ASIC data → local buf]
                    ├─ bl FUN_018736a4      [port validation; calls FUN_013949c0 if valid]
                    ├─ subtable dispatch: 0x154c, 0x1562–0x156c (11 physical LPM banks)
                    ├─ bl FUN_018232b8      [subtable write 1]
                    ├─ bl FUN_0186d870      [subtable write 2]
                    └─> bl FUN_018ca818     [subtable write 3 (li r5,0x9 → 9-field)]
```

#### FUN_018758cc internals (fully decoded)

| Step | Address | Operation |
|------|---------|-----------|
| mutex | 01875964 | `bl FUN_01873404` — lock before table ops |
| shadow stride | 01875994 | `mulli r21,r29,0x3a4` — 932 bytes/entry in unit_struct shadow table |
| shadow base | 018759b0 | `lwz r3,-0x5198(r9)` → unit_struct[0x1ae68 + index*0x3a4] |
| ECMP hook | 01875998 | `bl FUN_0187334c` — checks unit_struct[0xa37190]&0x4000000 flag |
| call 018751e0 | 018759f0 | r8 = data_ptr (from FUN_0187334c return), r10 = stack buf r1+0x18 |
| post-write | 01875a04 | `bl FUN_01875144` (post-write callback); then `bl FUN_0186b2f4` (unlock) |

#### L3_DEFIP physical table remapping (inside FUN_018751e0 at 018758b0)

When table_id == 0x22c9, the code at **018758b0** substitutes:
- `r10 = entry_array_ptr + 0x8b3c` (= `entry_array_ptr + 0x22cf × 4`, selecting table 0x22cf)
- `r16 = 0x8b3c` (index offset corresponding to physical table)
- `r21 = 0x22cf` (replaces table_id 0x22c9 for all downstream writes)

**L3_DEFIP logical table 0x22c9 → physical hardware table 0x22cf.**

#### FUN_0187334c — ECMP preprocessing check (fully decoded, 49 instructions)

```
FUN_0187334c(unit, index, data_ptr, buf1, buf2)
  → reads unit_struct[0xa37190] flag
  → if bit 0x4000000 NOT set: return data_ptr unchanged
  → if bit 0x4000000 set AND entry[0] & 0x40080000 == 0x80000:
      bl FUN_01869d7c(unit, index, 1, buf2, buf1) → return result
  → otherwise: return data_ptr unchanged
```

**Key finding**: L3_DEFIP does NOT use the descriptor-driven bitfield path (FUN_0181e718) that L2 uses.
Instead it does a **raw ASIC memcpy** of pre-formatted multi-subtable entry data. The entry spans
multiple physical subtables (0x154c, 0x1562–0x156c) — one entry per LPM bank/width. The raw ASIC
format (prefix/mask/nexthop bit positions) cannot be determined statically; requires GDB or HW docs.

### 1.2 L3 sub-table / multi-entry write (tables 0x1559–0x155e, 0x2c32, etc.)

```
opennsl_l3_route_add / opennsl_l3_host_add / opennsl_l3_egress_create
  └─> FUN_018d7ad4 @ 0x018d7ad4       [table ID validator; r7 (7th arg) = table ID]
        └─> FUN_018d62ec @ 0x018d62ec  [write wrapper; frame 0x330 = 816 bytes]
              ├─> FUN_018d43e4          [memset 0x224 bytes + stores -1 at 0x204–0x220]
              ├─> FUN_014a51e8          [fills buffer; table IDs 0x1559–0x155e, 0x2c32, etc.]
              └─> FUN_0170b700          [fills buffer; alternate path; table IDs 0x152d, 0x1555, etc.]
                    └─> FUN_01876f10 (unit, table_id, -1, index, buffer)
                          └─> FUN_01876ee0
                                └─> FUN_01876c30
                                      └─> bctrl [r9+0x19484]  ← per-unit ASIC write handler
                                           (addis r11,r9,0x2 → lwz r0,-0x6b7c(r11))
```

**Note**: FUN_018d7ad4 handles table 0x22d3 via a sub-type gate at 018d7ce0. For sub-type 0x35/0x37/0x38
→ FUN_018d62ec → FUN_0170b700 (which doesn't handle 0x22d3 → returns -0x4). The 0x22d3 path in
FUN_018d7ad4 is for sub-table metadata writes, not the primary route data write.

**Shared write mechanism**: L3 sub-table writes and L2 converge at **FUN_01876f10** — the same
generic table-write function. The bctrl handler at FUN_01876c30 is the same dynamic dispatch used
for all table writes. Handler is at `unit_struct + 0x19484` (NOT `r9-0x6b7c` as previously stated —
see [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) §2).

---

## 2. Table ID Mapping

### 2.1 L3_DEFIP (route table)

| Table ID | Variant | Notes |
|----------|---------|-------|
| `0x22c9` | L3_DEFIP (logical) | Used in FUN_018751e0 for primary L3_DEFIP writes |
| `0x22cf` | L3_DEFIP (physical) | Actual hardware table; 0x22c9 remaps here (0x22cf×4=0x8b3c offset) |
| `0x22d3` | L3_DEFIP (alt logical) | FUN_018d7ad4 check at 018d7ce0; FUN_01b0c9a0 L3_DEFIP string ref |
| `0x22ca` | L3_DEFIP (alt) | Paired with 0x22d3 |

### 2.2 L3_ECMP (equal-cost multi-path)

| Table ID | Variant | Notes |
|----------|---------|-------|
| `0x2c32` | L3_ECMP (primary) | FUN_018d7ad4 routes to FUN_018d62ec |
| `0x2c33` | L3_ECMP (alt) | Paired with 0x2c32 |
| `0x1570` | ECMP write path | Used in FUN_01a1572c → FUN_018788bc for group write |
| `0x6418` | ECMP (data) | Not in 01a1572c dump; in table-name→ID map |
| `0x6419` | ECMP (data) | Paired with 0x6418 |
| `0x8a8` | ECMP-related | From table-name→ID map |

### 2.3 L3-related tables (014a51e8 / 0170b700)

| Table ID | Range | Role |
|----------|-------|------|
| `0x1559–0x155e` | — | L3 sub-tables (routed via 018d7ad4) |
| `0x1599`, `0x2c24`, `0x15a5` | — | L3 variant tables |
| `0x1584`, `0x1590`, `0x15a5`, `0x1597` | — | In 014a51e8 path |
| `0x1514`, `0x1515` | — | In 014a51e8 |
| `0x1588`, `0x158c` | — | In 014a51e8 |
| `0x6fa`, `0x124a` | — | In 014a51e8 (auxiliary) |
| `0x152d`, `0x1555`, `0x2c4b`, `0x2c4d`, `0x2c24` | — | In 0170b700 path |
| `0x152b`, `0x1529`, `0x1594`, `0x1596` | — | In 0170b700 path |
| `0xa95` | — | In 0170b700 |

### 2.4 VLAN_XLATE

| Table ID | Notes |
|----------|-------|
| `0x8a6` | VLAN_XLATE write via FUN_014aec60; reuses **0x24-byte L2 buffer path** (0181f7dc → 0181e718) |
| `0x6418`, `0x6419` | Also referenced by VLAN_XLATE functions |
| `0x645d`, `0x8a4` | From FUN_018d4770 (VLAN_XLATE validator) |

---

## 3. L3 Buffer Layout (0x224 bytes at r1+0x6c)

### 3.1 Buffer lifecycle

1. **FUN_018d43e4** initializes: `memset(buf, 0, 0x224)` then stores -1 at offsets `0x204, 0x208, 0x20c, 0x210, 0x214, 0x218–0x220`
2. **FUN_014a51e8** or **FUN_0170b700** fills fields based on table ID
3. Filled buffer passed to **FUN_01876f10** (same as L2)

### 3.2 Known buffer fields

| Offset (hex) | Size | Value(s) / Field |
|--------------|------|------------------|
| `0x000` | 4 | Op/type: `4` (FUN_0170b700 path) or `8` (FUN_014a51e8 path); `6` seen for tables 0x6fa/0x124a |
| `0x004` | 4 | Table entry start (loop populates 0x4, 0x44, …; e.g. table 0x1555 + flag `1`) |
| `0x044` | 4 | Second entry in array (loop, same as 0x4 pattern) |
| `0x084` | 4 | Index / count (computed per table; loop variable) |
| `0x09c` | 4 | Index / count (from 0x84 + offset; table-specific) |
| `0x0b4` | 4 | Index or pointer (r11; in FUN_0170b700) |
| `0x0cc` | 4 | Index or pointer (r0; in FUN_0170b700) |
| `0x204` | 4 | Format constant: `0xa9e2` (014a51e8 / 0170b700 table 0x1555) or `0xee2b` (0170b700 table 0x124a) |
| `0x208` | 4 | Format constant: `0x95d6` (most tables) or `0x95d9` (0170b700 table 0x124a) |
| `0x20c` | 4 | Format constant: `0x4fcc` (0170b700 table 0x1555); `0x4fcf` (0170b700 table 0x124a); `-1` sentinel from 018d43e4 init (set for tables via 014a51e8) |
| `0x210` | 4 | Format constant: `0x992c` (014a51e8 tables 0x1559–0x155e) or `0xb160` (014a51e8 tables 0x1584/0x1590/0x1597); **not set** in 0170b700 path |
| `0x214` | 4 | Format constant: `0x5740` (014a51e8 path only) |
| `0x218–0x220` | varies | `-1` sentinels from 018d43e4 init |

### 3.3 Op Code by Fill Path

| Fill function | Op code (buf+0x000) | Tables |
|--------------|---------------------|--------|
| FUN_014a51e8 | **0x8** | 0x1559–0x155e, 0x1584, 0x1590, 0x1597, 0x1588, 0x158c |
| FUN_014a51e8 | **0x6** | 0x6fa, 0x124a (auxiliary) |
| FUN_0170b700 | **0x4** | 0x1555, 0x124a, 0x152d, 0x2c4b, 0x2c4d, 0x2c24, etc. |

### 3.4 Interpretation

- **0x000**: Op code 4 = standard write (FUN_0170b700 path); 8 = L3_DEFIP/sub-table write (FUN_014a51e8); 6 = auxiliary/MPLS table write.
- **0x004–0x044**: Entry array — for multi-entry writes (ECMP groups, nexthop arrays), entries are packed starting at 0x4, stride 0x40.
- **0x084–0x0cc**: Table indices or entry counts; used to locate the specific row in the ASIC table.
- **0x204–0x214**: Format descriptor words identifying the table format to the bctrl handler. The `0xee2b`/`0x95d9`/`0x4fcf` triple (table 0x124a via 0170b700) vs `0xa9e2`/`0x95d6`/`0x4fcc` (table 0x1555 via 0170b700) are distinct table format versions.

**Field names** (prefix, mask, nexthop, egress_id, MAC, port) still need to be mapped from concrete L3 write traces or OpenNSL type inspection.

---

## 4. ECMP Group Layout (FUN_01a1572c)

### 4.1 Unit struct offsets for ECMP

| Offset in unit struct | Field |
|----------------------|-------|
| `0x134` | Pointer to ECMP member array (stride 8 bytes per member) |
| `0x138` | Group base or first group index |
| `0x13c` | Group count or last group index |
| `0x10c` | Per-unit block for second array (stride 4 bytes) |

### 4.2 ECMP table write

- **Table ID for write**: `0x1570` — passed to **FUN_018788bc** (trampoline: `li r9,-1; b 0x018786d0`)
- **Real write function**: **FUN_018786d0** — actual ECMP member write implementation
- **Entry size**: computed from `lhz 0x28(descriptor)` in per-unit table; then `mullw` with count for alloc
- **Group member loop**: iterate `count` times over `0x134(unit)[member_idx*8]` and `0x10c(unit)[member_idx*4]`; `andi. 0x18` checks on the 4-byte entry word

### 4.3 FUN_018786d0 — ECMP Member Stride (NEW from dump analysis)

From `libopennsl-dump-018786d0.txt`:

| Unit struct field | Offset | Meaning |
|------------------|--------|---------|
| ECMP member array 1 | `unit_struct + 0x6b98 + group_id*0xe9 + member_idx` | Member data pointer (word) |
| ECMP member array 2 | `unit_struct + 0x6bd0 + group_id*0xe9 + member_idx` | Member flags/ptr |
| Member data word | `[member_ptr1 + 0xc]` | Member data |
| Member enable byte | `[member_ptr2 + 0x14][0]` & 0x1 | Valid flag |
| ASIC table info | `unit_struct + 0xa30000 + 0x6c30` → `[0x28]` → `[table_id*4]` → `lhz 0x28` | Entry size (bytes) |

**Key new finding**: ECMP member stride in unit struct = **0xe9 (233) bytes per group entry**, not 8 as previously estimated. Each group occupies 233 bytes across two parallel arrays starting at offsets 0x6b98 and 0x6bd0.

**Excluded table IDs** (FUN_018786d0 skips these for ECMP write):
- `0x1515`, `0x1521`, `0x1522` — these are handled differently

**Write operation**: `bl 0x02f52328` (memcpy) copies `count * entry_size` bytes into the ASIC table buffer, then dispatches via `b 0x01877f68` (another table write path).

### 4.3 ECMP stack struct (r1+0x24, 0x28 bytes)

From FUN_01a1572c:

| Stack offset | Value |
|-------------|-------|
| `0x14` | Saved from `[r30-0x7fdc]` |
| `0x1c` | Saved from `[r30-0x7fe4]` |
| `0x20` | Saved from `[r30-0x7fe0]` |
| `0x24` | Group pointer (r29 = r4 input) |
| `0x28` | `0x200` (constant) |
| `0x30` | `-1` (sentinel) |

---

## 5. VLAN_XLATE Write Path

**Key finding**: VLAN_XLATE uses the **same 0x24-byte buffer path as L2**, not the 0x224-byte L3 path.

```
FUN_014aec60 (VLAN_XLATE entry)
  └─> FUN_0181f7dc  [same as L2 buffer fill; r7=1]
        └─> FUN_0181f080
              └─> FUN_0181e718  [descriptor-driven bitfield write into 0x24-byte buffer]
  └─> FUN_01876f10  [table ID 0x8a6, buffer 0x24 bytes]
        └─> FUN_01876ee0 → FUN_01876c30 → bctrl
```

**Table ID**: `0x8a6` (VLAN_XLATE)
**Buffer**: 0x24 bytes (same size and fill mechanism as L2_USER_ENTRY table 0x1547)
**Descriptor**: Different descriptor for table 0x8a6 (VLAN fields instead of L2 MAC/port fields); same descriptor-driven bitfield packing logic in FUN_0181e718

**VLAN_XLATE fields** (inferred from OpenNSL `bcm_vlan_translate_*`): ingress VLAN, egress VLAN, port, action (replace/add/strip), valid bit. Exact offsets need the 0x8a6 descriptor values.

The function **FUN_018d4770** (VLAN_XLATE validator, referencing 12 functions) also uses table IDs `0x645d`, `0x8a4`; likely handles VLAN translation rules outside the per-port XLATE table.

---

## 6. Write Mechanism Status

Same situation as L2 (they share FUN_01876c30):

| Method | Evidence |
|--------|---------|
| S-Channel via FUN_007042f0 | **NOT found** in FUN_01876f10/ee0/c30 static dumps |
| Direct BAR write to 0x01xxxxxx table memory | **Possible** — table addresses (L3_DEFIP at ~0x018124a8, etc.) are in this range |
| bctrl to per-unit handler | **CONFIRMED** — FUN_01876c30 at 01876cbc: `addis r11,r9,0x2; lwz r0,-0x6b7c(r11)` = unit_struct+0x19484 |

**FUN_01876c30 = generic table-write dispatcher (now fully decoded)**:
- Frame: 0xd0 bytes; calls `bl 0x02f52440` (memset 0x80 bytes local buf) at 01876ca8
- Checks `unit_struct[0x19484]` (= `addis r11,r9,0x2; lwz r0,-0x6b7c(r11)`) for bctrl handler
- If non-NULL: `mtspr CTR,r0; bctrl` with args (unit, table_id, index, buf1, buf2, data_ptr)
- If NULL: falls through to FUN_018758cc
- After L3_DEFIP write: checks ECMP condition (table_id - 0x1660 ≤ 1) → calls FUN_01876a9c
- 2 callers of FUN_018758cc (FUN_01876c30 at 01876db0; FUN_01876a9c via trampoline 01875ad4)

**Working theory**: The bctrl handler at unit_struct+0x19484 performs the actual ASIC write (S-Channel or direct BAR). The software path (FUN_018758cc→FUN_018751e0) is the fallback/test path used when no hardware handler is registered. For BCM56846 production use, the hardware handler is expected to be non-NULL.

---

## 7. What's Still Needed

| Gap | Action | Priority |
|-----|--------|---------|
| ~~L3_DEFIP field bit layout~~ | ✅ DONE — verified via bcmcmd listmem + runtime dump. See [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) | complete |
| ~~L3_ECMP field layout~~ | ✅ DONE — L3_ECMP: NEXT_HOP_INDEX[13:0]; L3_ECMP_GROUP: BASE_PTR[21:10] + COUNT[9:0]. See [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) | complete |
| ~~Nexthop chain (ING/EGR_L3_NEXT_HOP, EGR_L3_INTF)~~ | ✅ DONE — all field bit positions verified via bcmcmd on live switch. See [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) | complete |
| ~~VLAN_XLATE field layout~~ | ✅ NOT NEEDED — no active VLAN_XLATE entries on this pure L3 switch; per-port VLANs set at init, not via VLAN_XLATE | complete |
| bctrl handler identity at unit_struct+0x19484 | GDB: `p/x *(void**)(unit_struct+0x19484)` during switchd startup; then dump that function | LOW (write mechanism confirmed via S-channel DMA) |
| FUN_01875144 (post-write callback) | Dump to understand what happens after FUN_018751e0 succeeds | LOW |
| FUN_01869d7c (ECMP preprocessing) | Dump to understand what it returns when unit_struct[0xa37190]&0x4000000 is set | LOW |

---

## 8. Scripts to Run

```bash
# Dump FUN_018d62ec for full dispatch logic (already have 354-insn; get more if needed)
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 018d62ec 500

# Dump FUN_014a51e8 — full store list into 0x224 buffer for L3 tables
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 014a51e8 500

# Dump FUN_0170b700 — alternate L3 buffer fill
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 0170b700 500

# Dump FUN_018788bc — ECMP table write (parallel to 01876f10)
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 018788bc 300

# Dump FUN_01876c30 — final dispatch; check what bctrl does
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 01876c30 200

# On switch: strace during L3 route add (OSPF will trigger this automatically)
# OSPF is already running on swp1 — the strace captures all ioctl/mmap access
# Look for write() calls to mmap'd regions during route-add netlink events
./scripts/reverse-engineering/run-packet-io-trace-<LIVE_SWITCH_IP>.sh
```

---

## References

- [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) — **L3 nexthop table chain: L3_ECMP, ING/EGR_L3_NEXT_HOP, EGR_L3_INTF (verified)**
- [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) — L3_DEFIP write mechanism (S-channel DMA confirmed)
- [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md)
- [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md)
- [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md)
- [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md)
- [L3_ECMP_VLAN_CURRENT_STATE.md](L3_ECMP_VLAN_CURRENT_STATE.md)
- [ECMP_GROUP_LAYOUT_FROM_01a1572c.md](ECMP_GROUP_LAYOUT_FROM_01a1572c.md)
- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md)
- [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md)
- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) — same bctrl dispatch (FUN_01876c30)
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) §4

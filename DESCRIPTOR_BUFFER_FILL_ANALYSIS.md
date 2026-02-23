# Descriptor-Driven Buffer Fill — FUN_0181e718 Analysis

**Date**: 2026-02-21
**Status**: COMPLETE — function fully decoded from 394-instruction dump
**Sources**: [build-server/opennsl/sdk-deep-extract/libopennsl-dump-0181e718.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-dump-0181e718.txt)
**Used by**: L2_USER_ENTRY (0x1547) via FUN_0181f7dc→FUN_0181f080→FUN_0181e718; VLAN_XLATE (0x8a6) same path

---

## 1. Function Signature

```
FUN_0181e718(r3, r4=table_handle, r5=dest_buffer, r6=field_key, r7=src_value_word0, ...)
```

- **r4** (`r31` after save): table handle pointer — points to per-table descriptor metadata
- **r5** (`r29`): destination buffer (the 0x24-byte ASIC buffer to fill)
- **r6** (`r28`): field key — used as search key in descriptor array (identifies which field to pack)
- **r7** (`r27`): source value (word(s) to pack into buffer)

---

## 2. Phase 1: Binary Search for Field Descriptor (0181e718–0181e8a8)

### 2.1 Table handle structure (at r31 = r4 input)

| Offset in table handle | Field | Use |
|------------------------|-------|-----|
| `0x0` (lwz) | table flags word | bit 0x08000000 = reverse word-order mode |
| `0x28` (lhz) | total buffer size in bytes | used when reverse-order flag set |
| `0x2a` (lhz) | descriptor count | number of fields in this table |
| `0x2c` (lwz) | descriptor array pointer | sorted array of field descriptors |

### 2.2 Binary search algorithm

```
r9  = table_handle + 0x2c → descriptor_array_ptr
r10 = descriptor_count       (lhz 0x2a(r4))

# Binary search bounds: [r9, r9 + stride*(count-1)]
# Stride = 0xc bytes per descriptor (12 bytes)
# Key comparison: descriptor[0] vs field_key (r28)

while bounds not collapsed:
    mid = (lo + hi) / 2  (using rlwinm/mullw/srawi/addze arithmetic)
    if descriptor[mid][0] == field_key → found at r26 = mid
    elif descriptor[mid][0] < field_key → lo = mid + 1
    else → hi = mid - 1

# On found: r26 = pointer to matching field descriptor
# On not found: call error handler (bl 0x01393e80 / 0x0137e2f0)
```

**Descriptor stride**: `rlwinm r8,r11,0x2,0x0,0x1d; rlwinm r0,r11,0x4,0x0,0x1b; subf r0,r8,r0`
= `r11*4 - r11*16` ... wait, that's `r11*(16-4) = r11*12`. Stride = **12 bytes per descriptor**.

### 2.3 Field descriptor structure (at r26, 12 bytes)

| Offset | Size | Field | Meaning |
|--------|------|-------|---------|
| `+0x0` | 4 | field_key | Opaque key used for binary search (field type identifier) |
| `+0x4` | 2 (lhz) | bit_width | Number of bits this field occupies in the ASIC buffer |
| `+0x6` | 2 (lhz) | bit_start | Starting bit position in the 0x24-byte buffer |
| `+0x8` | 2 (lhz) | flags | Bit 0 = 1 means "normal bitfield pack"; other bits control mode |

---

## 3. Phase 2: Bitfield Packing (0181e8d4–0181ec7c)

### 3.1 Entry into packing

After finding descriptor at r26, calls `bl 0x0181c73c` (FUN_0181c73c — lock/prepare buffer?),
then reads descriptor fields:

```asm
0181e8dc: lhz r0, 0x8(r26)    ; r0 = flags
0181e8e0: lhz r9, 0x6(r26)    ; r9 = bit_start
0181e8e4: andi. r4, r0, 0x1   ; test bit 0
0181e8e8: beq 0x0181eb70       ; bit 0 == 0 → "single-bit mode" at 0181eb70
; bit 0 == 1 → "multi-bit pack mode":
0181e8ec: lhz r8, 0x4(r26)    ; r8 = bit_width
0181e8f4: cmpwi cr7, r8, 0x0
0181e8f8: beq cr7, 0x0181eb38  ; zero width → early exit
```

### 3.2 Multi-bit pack mode (bit 0 of flags == 1)

```
word_index = bit_start >> 5               (srawi r9,r9,0x5)
bit_pos    = bit_start & 0x1f             (r3 = rlwinm ...,0x0,0x1b,0x1f)
word_count = ((bit_width - 1) >> 5) + 1  (r5 = rlwinm r5,r5,0x1b,0x5,0x1f then +1)
mask       = (1 << bit_pos) - 1           (slw r24,r24,r3; subi r24,r24,0x1)
```

**Reverse-word-order mode** (when `[r31+0x0] & 0x08000000`):
```
# Instead of word_index, compute:
total_words = (buffer_size + 3) / 4      (lhz r5,0x28(r31); addi,srawi)
word_index  = total_words - 1 - word_index  (subf)
```
This stores fields in big-endian reversed order (MSW first in buffer).

**Main pack loop** (0181e940, iterates `word_count` times via CTR):
```
for each word W in [0 .. word_count-1]:
    dst = buffer + word_index*4   (or reversed: buffer + (total_words-1-word_index)*4)
    src = src_value[W]            (from r27 + W*4)
    # Clear field bits in destination:
    *dst = (*dst & ~(field_mask << bit_pos))
    # Set new bits:
    *dst = *dst | (src_word << bit_pos)
    # Handle carry to next word (bit_pos != 0):
    *(dst+4) = (*(dst+4) & ~(src >> (32-bit_pos))) | (src >> (32-bit_pos))
```

### 3.3 Single-bit mode (bit 0 of flags == 0, at 0181eb70)

Used for boolean flags (e.g. STATIC bit, VALID bit):
```
width = descriptor[0x4]  (lhz r11, 0x4(r26))
for each bit B in [0..width-1]:
    word_idx = (bit_start + B) >> 5
    bit_pos  = (bit_start + B) & 0x1f
    src_bit  = (src_value >> B) & 1
    *buffer_word = (*buffer_word & ~(1 << bit_pos)) | (src_bit << bit_pos)
```

---

## 4. Callers and Field Types

### 4.1 L2_USER_ENTRY (table 0x1547) — called via FUN_0181f7dc and FUN_01820598

From FUN_01cbd2e0 and related analysis:

| Caller | field_key (r6) | Source (r7) | Field packed |
|--------|---------------|-------------|-------------|
| FUN_0181f7dc path | flags/static | `opennsl_l2_addr_t + 0x00` | STATIC, HIT bits |
| FUN_01820598 path | MAC field | `opennsl_l2_addr_t + 0x08` | MAC[0..5] (6 bytes) |
| — | VID field | `opennsl_l2_addr_t + 0x14` | VLAN ID (12 bits) |
| — | PORT field | `opennsl_l2_addr_t + 0x2c` | Destination port/modid |

### 4.2 VLAN_XLATE (table 0x8a6) — same path with different descriptor

Table 0x8a6 uses the same FUN_0181e718 with its own descriptor array. Fields packed:
- ingress VLAN (outer key)
- egress VLAN (inner key)
- port, action (translate/add/strip)
- valid bit

The **descriptor for table 0x8a6** vs **table 0x1547** has different `bit_start` and `bit_width`
values but the same binary-search lookup mechanism.

---

## 5. Known Descriptor Array Layout (Table 0x1547 — L2_USER_ENTRY)

The exact descriptor values (field_key, bit_start, bit_width) for table 0x1547 require either:
1. A GDB trace printing r26 values during an actual L2 add (gives concrete values per field)
2. Locating the descriptor array in Ghidra (search for `lhz 0x4(r26)` pattern near table init)

**Expected layout** (from OpenNSL/SDK L2_USER_ENTRY field definitions, BCM56846):
Typical 9-word (0x24 byte) L2_USER_ENTRY in Trident+ format:

| Bit range | Field | Notes |
|-----------|-------|-------|
| 0 | VALID | Entry valid |
| 1 | STATIC_BIT | Static/permanent |
| 2–7 | Priority | CoS |
| 8–55 | MAC_ADDR | 48 bits |
| 56–67 | VLAN_ID | 12 bits |
| 68–74 | DEST_PORT | 7 bits (physical port) |
| 75–76 | RPE | Route priority eligible |
| 77+ | Remaining flags | HIT_SA, HIT_DA, CPU, TRUNK, etc. |

**Note**: This is the approximate field order. Exact bit positions require tracing the descriptor
values for table 0x1547 from the libopennsl per-unit table initialization.

---

## 6. Scripts to Get Exact Descriptor Values

```bash
# Method 1: GDB trace on Cumulus switch during L2 add
# Break at FUN_0181e718 equivalent in switchd; print r26[0..2] (field_key, bit_start, bit_width)

# Method 2: Find descriptor array in Ghidra
# Search for constants near l2_user_entry table init (look for 0x1547 store followed by
# pointer stores that match descriptor array pattern)
./scripts/reverse-engineering/run-dump-func-on-build-server.sh libopennsl 0181f080 100
# FUN_0181f080 loads descriptor from per-unit table → find the data pointer

# Method 3: Search libopennsl data for the known field sizes (48-bit MAC = 0x30 bit_width)
# grep for 0x30 halfword in .data section near table 0x1547 references
```

---

## References

- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) — caller chain to this function
- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) — VLAN_XLATE uses same path
- [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md) — L3 uses different (larger) buffer

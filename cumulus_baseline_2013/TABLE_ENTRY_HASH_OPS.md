# Table Entry Operations — Hash Insert/Lookup/Delete via SCHAN

The chip has **dedicated SCHAN opcodes** for hash table operations on
L3_ENTRY (L3 host), L2_ENTRY (MAC FDB), and similar hash-indexed tables.
This is critical for direct table programming without using the BCM SDK.

Recovered from static decompilation of:
- `FUN_10ebbb38` (1768 B) — `soc_l3_entry_insert`
- `FUN_10ebc220` (1744 B) — `soc_l3_entry_delete`
- `FUN_10ebb2fc` (2108 B) — `soc_l3_entry_lookup`

These three functions reveal the **chip-level hash-table interface**
that bcm_l3_host_add and bcm_l2_addr_add eventually use.

---

## 1. The hash-operation SCHAN opcodes

In addition to the basic READ/WRITE opcodes documented earlier
(`CMIC_SCHAN_DMA_DEEP_DIVE.md`), the SCHAN bus has dedicated hash
opcodes:

| Operation | Request opcode | Response opcode | Function |
|---|---|---|---|
| `HASH_INSERT` | `0x1A` (`0x68000000`) | `0x1B` (`0x6c000000`) | `FUN_10ebbb38` |
| `HASH_DELETE` | `0x1C` (`0x70000000`) | `0x1D` (`0x74000000`) | `FUN_10ebc220` |
| `HASH_LOOKUP` | `0x22` (`0x88000000`) | `0x23` (`0x8c000000`) | `FUN_10ebb2fc` |
| `MEM_READ` | `0x09` (`0x24000000`) | — | (covered earlier) |
| `MEM_WRITE` | `0x0F` (`0x3c000000`) | — | (covered earlier) |
| `REG_READ` | `0x0B` (`0x2c000000`) | — | (covered earlier) |
| `REG_WRITE` | `0x0D` (`0x34000000`) | — | (covered earlier) |
| `TBL_READ` | `0x11` (`0x44000000`) | — | (covered earlier) |
| `TBL_WRITE` | `0x13` (`0x4c000000`) | — | (covered earlier) |
| `CTR_READ` | `0x15` (`0x54000000`) | — | counter read |
| `LINK_W` | `0x1A` (overlap?) | — | link state write |
| `LINK_R` | `0x1C` (overlap?) | — | link state read |

Note: the LINK_W/R opcodes documented earlier as 0x1A/0x1C may have
been mis-identified — those values match the HASH_INSERT/DELETE codes.
Either there's context-specific decoding (per target block) or our
earlier source was incomplete. The decompiled code unambiguously shows
0x1A/0x1B for hash insert and 0x1C/0x1D for hash delete on L3_ENTRYm.

---

## 2. Hash command word format

For hash ops, the SCHAN command word (word 0 of the message) has a
richer layout than READ/WRITE:

```
 31    26 25    20 19    14 13   9 8   3 2 1 0
┌────────┬────────┬────────┬─────┬────┬───┬─┐
│OPCODE  │BLOCK_A │BLOCK_B │ WC  │RSV │OP│E│
└────────┴────────┴────────┴─────┴────┴───┴─┘
```

| Bits | Field | Meaning |
|---|---|---|
| 26-31 | OPCODE | 0x1A=INSERT / 0x1C=DELETE / 0x22=LOOKUP |
| 20-25 | BLOCK_A | "search block" — usually IPIPE for L3 hash |
| 14-19 | BLOCK_B | "result block" — usually IPIPE for L3 hash |
| 9-13 | WC | word count of entry data (max 31 words) |
| 1-2 | OP | sub-opcode (which hash table within the block) |
| 0 | E | error/conflict flag (in response only) |

The two block IDs come from the chip-state struct:
- BLOCK_A from `unit_state + 0x5bb4`
- BLOCK_B from `unit_state + 0x5ba4`

These are set at attach time based on the chip's natural search/result
block assignment for the most common L3 lookups.

---

## 3. Word count and entry layout

The `WC` field (bits 9-13) is the **number of 32-bit words** in the
entry data, computed from the table's per-entry width:

```c
WC = (entry_width_bits + 31) / 32;
```

For BCM56846 (Trident+):

| Table | Width | WC |
|---|---|---|
| L2_ENTRY_1 / L2_ENTRY_2 | 105 bits | 4 |
| L3_ENTRY_IPV4_UNICAST (host) | 105 bits | 4 |
| L3_ENTRY_IPV6_UNICAST (host) | 200+ bits | 7-8 |
| L3_ENTRY_IPV4_MULTICAST | 154 bits | 5 |
| L3_ENTRY_IPV6_MULTICAST | 280 bits | 9 |

These widths come from the chip's per-table metadata. Reading
`*(unit_state + 0x2f26f4 + 0x24)[table_id * 4]`'s field at offset 0x28
gives the entry width in bits.

---

## 4. The HASH_INSERT protocol — step-by-step

```c
int soc_l3_entry_insert(int unit, byte op_type, uint32_t *entry) {
    /* 1. Look up metadata for memory ID 0x82f (L3_ENTRYm) */
    int mem_id = lookup_mem_table(unit, 0x82f, entry, &local_20, ...);
    if (mem_id < 0) return -1;

    /* 2. Compute word count from entry width */
    int wc = ((entry_width(unit, mem_id) + 31) / 32);

    /* 3. Build SCHAN command word */
    uint32_t cmd = 0;
    cmd |= ((wc & 0x1f) << 9);                 // word count
    cmd |= ((op_type & 3) << 1);               // sub-opcode (which hash bank)
    cmd |= ((block_a(unit) & 0x3f) << 20);     // search block
    cmd |= ((block_b(unit) & 0x3f) << 14);     // result block
    cmd |= 0x68000000;                          // HASH_INSERT opcode

    /* 4. Stage message: cmd word + entry data */
    uint32_t msg[wc + 2];
    msg[0] = cmd;
    memcpy(&msg[1], entry, wc * 4);

    /* 5. SCHAN op (dwc_write = wc+1, dwc_read = wc+2 to get index back) */
    int rc = soc_schan_op(unit, msg, wc + 1, wc + 2);

    /* 6. Check response */
    if ((msg[0] & 0xfc000000) == 0x6c000000) {   // got INSERT_DONE
        if ((msg[0] & 1) != 0 || rc == -0xb) {    // parity error or NAK
            log("Insert table[L3_ENTRY_XXX]: Parity Error Index %d ...");
            return -PARITY;
        }
        /* msg[wc] now contains the (encoded) index where entry was placed */
        int index = msg[wc] & ((1 << bucket_bits) - 1);
        return index;
    }
    return -1;
}
```

---

## 5. The HASH_LOOKUP protocol

```c
int soc_l3_entry_lookup(int unit, byte op_type, uint32_t *key,
                        uint32_t *entry_out, uint32_t *index_out) {
    int mem_id = lookup_mem_table(unit, 0x82f, key, &local_3c, ...);
    if (mem_id < 0) return -1;

    int wc = ((entry_width(unit, mem_id) + 31) / 32);

    uint32_t cmd = 0;
    cmd |= ((wc & 0x1f) << 9);
    cmd |= ((op_type & 3) << 1);
    cmd |= ((block_a(unit) & 0x3f) << 20);
    cmd |= ((block_b(unit) & 0x3f) << 14);
    cmd |= 0x88000000;                          // HASH_LOOKUP opcode

    uint32_t msg[wc + 2];
    msg[0] = cmd;
    memcpy(&msg[1], key, wc * 4);

    int rc = soc_schan_op(unit, msg, wc + 1, wc + 2);

    if ((msg[0] & 0xfc000000) == 0x8c000000) {   // got LOOKUP_DONE
        if ((msg[0] & 1) == 0 && rc != -0xb) {    // found
            /* Copy entry data back to caller */
            for (int i = 0; i < wc - 1; i++)
                entry_out[i] = msg[1 + i];
            /* Last word: high bits hold index, low bits hold last data */
            uint32_t bucket_bits = ...;
            entry_out[wc - 1] = msg[wc] & ((1 << bucket_bits) - 1);
            *index_out = (msg[wc] >> bucket_bits) |
                         (msg[wc + 1] << (32 - bucket_bits)) &
                         entry_width_mask;
            return 0;
        }
        *index_out = 0xffffffff;
        return -NOT_FOUND;
    }
    return -ERR;
}
```

The chip's response packs the entry data into words 1..wc-1, and the
last word contains a mix of:
- Low `bucket_bits` of the last data word
- High bits = the **bucket/slot index** where the entry was found

---

## 6. The HASH_DELETE protocol

Same structure as INSERT but with opcode `0x70000000`:

```c
int soc_l3_entry_delete(int unit, byte op_type, uint32_t *key) {
    /* ... same prep as INSERT ... */
    cmd = ... | 0x70000000;        // HASH_DELETE opcode
    /* SCHAN op */
    rc = soc_schan_op(unit, msg, wc + 1, wc + 2);
    if ((msg[0] & 0xfc000000) == 0x74000000) {  // DELETE_DONE
        if ((msg[0] & 1) != 0) {
            /* Parity error during delete */
            log("Delete table[L3_ENTRYm]: Parity Error Index %d ...");
            return -PARITY;
        }
        /* Successful delete */
        return 0;
    }
    if (rc == -0xb) {   // NAK from SCHAN
        log("Delete table[L3_ENTRYm]: Not found");
        return -NOT_FOUND;
    }
    return -ERR;
}
```

---

## 7. The L3 entry structures — what goes in the data words

### L3_ENTRY_IPV4_UNICAST (host route, 4 words)

```
Word 0:  bits 0..1     VALID flags (V/V4, V/V6 for both-family hash)
         bits 2..14    VRF (13-bit VRF identifier)
         bits 15..31   <unused>
Word 1:  IP address (4 bytes)
Word 2:  bits 0..14    nexthop / egress object ID (15-bit)
         bits 15..28   class_id (14-bit, for FP qualifier)
         bits 29..31   priority
Word 3:  bits 0..15    flags (HIT, STATIC, etc.)
         bits 16..31   parity / checksum (chip-computed on insert)
```

### L3_ENTRY_IPV6_UNICAST (host /128, 8 words)

```
Word 0:  bits 0..1     VALID flags
         bits 2..14    VRF
Word 1-4: IPv6 address (16 bytes)
Word 5:  bits 0..14    nexthop / egress object ID
         bits 15..28   class_id
Word 6:  flags
Word 7:  parity
```

### L2_ENTRY_1 / L2_ENTRY_2 (MAC FDB, 4 words)

The 4-word L2 entry has subfields for:
- VALID
- MAC address (6 bytes, packed across 2 words)
- VLAN (12 bits)
- DEST_PORT or TRUNK_ID
- STATIC / HIT / L2_STATIC flags
- class_id
- parity

The two banks (L2_ENTRY_1 and L2_ENTRY_2) are typically used in
parallel for collision resolution — a hash conflict in bank 1 can
land in bank 2.

For EdgeNOS direct programming, use the **bcm_l2_addr_add()** wrapper
unless you need bypass-the-SDK performance.

---

## 8. The `lookup_mem_table` helper (FUN_10ebae30)

This is the function that translates a generic memory ID (like `0x82f`
for L3_ENTRYm) into the specific table instance for the chip's
current state. It also returns the chip-internal `mem_id` (which is
not the same as the BCM SDK's memory ID — it's a per-chip-instance
index used as the dispatch key).

```c
int lookup_mem_table(int unit, int generic_mem_id, void *entry,
                     int *mem_id_out, void *aux_out) {
    /* Look at chip's table-instance assignment table */
    /* Resolve generic ID → concrete table instance for this chip */
    /* For L3_ENTRYm (0x82f), it might map to L3_ENTRY_IPV4 or
       L3_ENTRY_IPV6 depending on entry's V/V4/V6 flag bits */
    ...
    *mem_id_out = concrete_table_id;
    return 0;
}
```

---

## 9. ALPM (Algorithmic LPM) — alternative for big v6 prefix tables

Trident+ supports a **second** DEFIP TCAM mode called **ALPM**
(Algorithmic Longest-Prefix-Match) that scales better for IPv6
routes. From the function names we found:

| Table | What |
|---|---|
| `L3_DEFIP_ALPM_IPV6_64` | IPv6 prefixes /1-64 (split by prefix length) |
| `L3_DEFIP_ALPM_IPV6_128` | IPv6 prefixes /65-128 |
| `td2_l3_defip_pair128` | Paired entries for v6 /128 in regular TCAM |

ALPM uses a multi-stage trie hardware:
1. First lookup checks IP[31:16] (v4) or IP[127:112] (v6) → bucket
2. Bucket gives a pointer to a per-bucket sub-TCAM
3. Sub-TCAM does the actual LPM match

This is opaque (no public docs) and the SDK handles it for you. For
basic forwarding, ALPM vs traditional DEFIP doesn't affect the API
surface — `bcm_l3_route_add` works the same way.

Detection: bit `*(unit_state + 0x2f2c14) & 0x800000` indicates ALPM
support, and `unit_state + 0x2f2c44 & 0x10000` (from soc_init) enables
ALPM mode.

---

## 10. Putting it together — direct L3 host install without SDK

If you want to bypass `bcm_l3_host_add` and program the L3_HOST table
directly (e.g., for an offload from a kernel module):

```c
/* SCHAN-mediated direct L3 host install for IPv4 */
int direct_l3_host_add_v4(int unit, uint32_t ip, uint16_t vrf,
                          uint16_t egress_id) {
    /* Build L3_ENTRY_IPV4_UNICAST entry (4 words) */
    uint32_t entry[4] = {0};
    entry[0] = 0x1 | ((vrf & 0x1fff) << 2);  // V_V4=1, VRF
    entry[1] = ip;
    entry[2] = (egress_id & 0x7fff);          // nexthop
    entry[3] = 0;

    /* Build SCHAN command */
    uint32_t cmd = 0x68000000                  // HASH_INSERT
                 | ((4 & 0x1f) << 9)            // 4 words
                 | ((unit_block_a(unit) & 0x3f) << 20)
                 | ((unit_block_b(unit) & 0x3f) << 14);

    uint32_t msg[6] = {cmd, entry[0], entry[1], entry[2], entry[3], 0};
    int rc = schan_op(unit, msg, 5 /*write*/, 6 /*read*/);

    if ((msg[0] & 0xfc000000) != 0x6c000000) return -SCHAN_ERR;
    if (msg[0] & 1) return -PARITY_ERR;
    return msg[4] & 0x7fff;   // bucket/index where entry was placed
}
```

---

## 11. Implications

This finding tells us the chip supports **three operation classes** via SCHAN:

1. **Direct memory ops** (REG_W, REG_R, MEM_W, MEM_R, TBL_W, TBL_R) —
   you specify the index explicitly.
2. **Hash ops** (HASH_INSERT, LOOKUP, DELETE) — the chip computes the
   hash itself, finds/uses the right bucket. You don't need to compute
   the hash function.
3. **Counter ops** (CTR_R) — counter reads with auto-clear.

The hash ops are **crucial for L2/L3 host programming** because:
- The chip's hash function is undocumented (CRC variant + some folding)
- Even if we knew the hash, bucket conflict resolution is hardware-
  specific
- Using HASH_INSERT, we hand the chip the entry and let it figure out
  where to put it

For EdgeNOS, this means we **don't need to reimplement the hash function**.
We just need to call SCHAN with opcode 0x68 and the chip handles it.

---

## 12. Cross-reference

- `ghidra-analysis/switchd_table_entry_impl.c` — 10 functions decompiled
- `ghidra-analysis/switchd_table_entry_search.txt` — table-entry function discovery
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` — base SCHAN protocol
- `L3_L2_PROGRAMMING_FLOW.md` — L3/L2 from netlink to chip-tables (high-level)

---

*Recovered from static decompilation 2026-05-11. The HASH_INSERT/LOOKUP/
DELETE opcodes are NOT documented in any public Broadcom material —
this is one of the most useful findings for direct chip programming.*

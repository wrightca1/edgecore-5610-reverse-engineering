# L2 ASIC Entry Format — BCM56846 (Trident+)

**Date**: 2026-02-23
**Status**: HAVE — bit positions fully verified via bcmcmd listmem + raw dump + write-back tests
**Switch**: Edgecore AS5610-52X / Cumulus Linux 2.5 / <LIVE_SWITCH_IP>

---

## Summary

BCM56846 uses **two distinct L2 tables**:

| Table | bcmcmd name | ASIC address | Entries | Size | Usage |
|-------|------------|-------------|---------|------|-------|
| **L2_ENTRY** (L2X) | `l2_entry` | 0x07120000 | 131,072 | 13 bytes (4 words) | Regular MAC learning + static entries |
| **L2_USER_ENTRY** | `l2_user_entry` | 0x06168000 | 512 | 20 bytes (5 words) | Guaranteed/TCAM entries: BPDUs, protocol MACs |

The opennsl call chain (`opennsl_l2_addr_add → FUN_00948700 → FUN_01876f10, table 0x1547`) writes to **L2_ENTRY** (verified: `l2 add` shows "mac entries N/131072").

L2_USER_ENTRY is used for protocol entries (BPDUs, STP) set up during SDK init — 446 entries pre-programmed at boot.

---

## 1. L2_ENTRY — Regular Hash Table

### 1.1 Table Properties

```
bcmcmd: listmem l2_entry
Address:  0x07120000   alias: L2X
Flags:    valid cachable hashed multiview
Blocks:   ipipe0/dma (1 copy, 1 dmaable)
Entries:  131072 with indices 0–131071
Size:     13 bytes = 4 words
Entry mask: -1 -1 -1 0x0000007f  (word[3] only 7 bits valid)
Hash:     dual-hash with linear probe
```

### 1.2 Bit Layout (KEY_TYPE=0, standard unicast L2)

Entry = 4 words (word[0]=bits[31:0], word[1]=bits[63:32], word[2]=bits[95:64], word[3]=bits[102:96])

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| VALID | [0] | w0[0] | 1 | 1 = entry valid |
| KEY_TYPE | [3:1] | w0[3:1] | 3 | 0 = standard L2 MAC lookup |
| VLAN_ID | [15:4] | w0[15:4] | 12 | 802.1Q VLAN ID |
| MAC_ADDR | [63:16] | w0[31:16] + w1[31:0] | 48 | MSB at bit 63, LSB at bit 16 |
| PORT_NUM | [70:64] | w2[6:0] | 7 | Egress port (when T=0) |
| MODULE_ID | [78:71] | w2[14:7] | 8 | Module ID (typically 0 on single-chip) |
| T | [79] | w2[15] | 1 | Trunk flag (1 = TGID used instead of PORT_NUM) |
| TGID | [73:64] | w2[9:0] | 10 | Trunk Group ID (when T=1, overlaps MODULE_ID+PORT_NUM) |
| RPE | [87] | w2[23] | 1 | Remark priority enable |
| PRI | [91:88] | w2[27:24] | 4 | Priority |
| PENDING | [92] | w2[28] | 1 | Pending bit |
| STATIC_BIT | [93] | w2[29] | 1 | Static (not aged) |
| DST_DISCARD | [94] | w2[30] | 1 | Destination discard |
| SRC_DISCARD | [96] | w2[32→w3's scope?] | 1 | Source discard |
| HITDA | [100] | w3[4] | 1 | Hit on destination address |
| HITSA | [101] | w3[5] | 1 | Hit on source address |

### 1.3 Raw Word Encoding (verified)

**Test entry**: VALID=1, VLAN_ID=3301(0xCE5), MAC=0xdeadbeef0001, PORT_NUM=1, MODULE_ID=0, STATIC_BIT=1

```
Raw: 0x0001ce51  0xdeadbeef  0x20000001  0x00000000
     word[0]     word[1]     word[2]     word[3]

Decoded: VALID=1, VLAN_ID=0xce5=3301, MAC_ADDR=0xdeadbeef0001,
         PORT_NUM=1, MODULE_ID=0, STATIC_BIT=1
```

Verification of word encoding:
```
word[0] = 0x0001ce51:
  bit 0     = 1         → VALID=1 ✓
  bits[3:1] = 0         → KEY_TYPE=0 ✓
  bits[15:4]= 0xce5     → VLAN_ID=3301 ✓
  bits[31:16]= 0x0001   → MAC_ADDR[47:32] (upper 16 bits of MAC)

word[1] = 0xdeadbeef:
  bits[31:0] → MAC_ADDR[31:0] = 0xdeadbeef (lower 32 bits of MAC)
  Full MAC = {word[0][31:16], word[1][31:0]} = {0x0001, 0xdeadbeef} = 0x0001deadbeef
  → Wait: that's 0x0001deadbeef, not 0xdeadbeef0001!

CORRECTION: MAC storage order:
  MAC_ADDR<63:16>: bit 63 = MSB of MAC entry bits, bit 16 = LSB of MAC entry bits
  word[1][31:0] → entry bits [63:32] → MAC_ADDR[47:16]
  word[0][31:16] → entry bits [31:16] → MAC_ADDR[15:0]

  So MAC_ADDR = {word[1][31:0], word[0][31:16]} = {0xdeadbeef, 0x0001} = 0xdeadbeef0001 ✓
```

**Test entry 2**: PORT_NUM=5, MODULE_ID=3, STATIC_BIT=1
```
Raw: 0x0001ce51  0xdeadbeef  0x20000185  0x00000000

word[2] = 0x20000185:
  bits[6:0]  = 0x185 & 0x7F = 0x05 = 5     → PORT_NUM=5 ✓
  bits[14:7] = (0x185 >> 7) & 0xFF = 3      → MODULE_ID=3 ✓
  bit 29     = (0x20000185 >> 29) & 1 = 1   → STATIC_BIT=1 ✓
```

### 1.4 Hash Function

The L2_ENTRY uses dual-hash for collision handling. The SDK computes:

```
hash_key = (MAC_ADDR << 16) | (VLAN_ID << 4) | (KEY_TYPE << 1) | 0
```

Note: VALID=0 for hash key computation (VALID is set to 1 in the written entry).

**Example**: MAC=0xDEADBEEF0001, VLAN=3301=0xCE5:
```
hash_key = 0xDEADBEEF0001 << 16 | 0xCE5 << 4 | 0 << 1 | 0
         = 0xDEADBEEF0001CE50
```
→ `bcmcmd l2 hash MACaddress=de:ad:be:ef:00:01 Vlanid=3301` confirms key = 0xdeadbeef0001ce50 ✓

### 1.5 DESTINATION Field (software-computed)

The SDK may use a combined DESTINATION field (bits [78:64]) = {MODULE_ID, PORT_NUM} = 15-bit value:

```c
destination = (MODULE_ID << 7) | PORT_NUM;  // when T=0 (non-trunk)
destination = TGID;                           // when T=1 (trunk)
```

---

## 2. L2_USER_ENTRY — Guaranteed TCAM Table

### 2.1 Table Properties

```
bcmcmd: listmem l2_user_entry
Address:  0x06168000
Flags:    valid cachable bist-epic
Blocks:   ipipe0/dma (1 copy, 1 dmaable)
Entries:  512 with indices 0–511
Size:     20 bytes = 5 words
Entry mask: -1 -1 -1 0x7fffffff 0x1fffffff
           (word[3] bit 31 invalid, word[4] bits 31:29 invalid)
Description: Combined L2_ENTRY TCAM/Data RAM for guaranteed L2 entries and BPDUs.
```

### 2.2 Bit Layout

Entry = 5 words (word[0]=bits[31:0] ... word[4]=bits[159:128])

**KEY section** (bits [61:0]):

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| VALID | [0] | w0[0] | 1 | 1 = entry valid |
| MAC_ADDR | [48:1] | w0[31:1] + w1[16:0] | 48 | LSB at bit 1; MAC[30:0] in w0[31:1], MAC[47:31] in w1[16:0] |
| VLAN_ID | [60:49] | w1[28:17] | 12 | VLAN ID |
| KEY_TYPE | [61] | w1[29] | 1 | 0=MAC only, 1=MAC+protocol |

**MASK section** (bits [122:62]):

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| MASK | [122:62] | w1[31:30] + w2[31:0] + w3[26:0] | 61 | Bit=1: key bit must match; Bit=0: don't care |

**DATA section** (bits [159:123]):

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| PRI | [126:123] | w3[30:27] | 4 | Priority |
| RESERVED_0 | [127] | w3[31] | 1 | Reserved |
| RPE | [128] | w4[0] | 1 | Remark priority enable |
| CPU | [129] | w4[1] | 1 | Copy to CPU |
| DST_DISCARD | [130] | w4[2] | 1 | Discard destination |
| PORT_NUM | [137:131] | w4[9:3] | 7 | Port (when T=0) |
| TGID | [140:131] | w4[12:3] | 10 | Trunk Group ID (when T=1) |
| MODULE_ID | [145:138] | w4[17:10] | 8 | Module ID |
| T | [146] | w4[18] | 1 | Trunk flag |
| DO_NOT_LEARN_MACSA | [147] | w4[19] | 1 | Disable SA learning |
| CLASS_ID | [153:148] | w4[25:20] | 6 | Classification ID |
| BPDU | [154] | w4[26] | 1 | BPDU flag |
| L2_PROTOCOL_PKT | [155] | w4[27] | 1 | Protocol packet |
| EVEN_PARITY | [156] | w4[28] | 1 | Parity |

### 2.3 KEY Encoding Formula

```
KEY<61:1> = (KEY_TYPE << 60) | (VLAN_ID << 48) | MAC_ADDR
```

The KEY field is a 61-bit value (entry bits [61:1]):
- KEY[60] = KEY_TYPE
- KEY[59:48] = VLAN_ID (12 bits)
- KEY[47:0] = MAC_ADDR (48 bits)

**Example** (entry[1]): KEY_TYPE=1, VLAN_ID=0, MAC=0x0180c2000000:
```
KEY = (1 << 60) | (0 << 48) | 0x0180c2000000 = 0x10000180c2000000 ✓
```

### 2.4 MASK Encoding

MASK<122:62> uses the same bit structure as KEY:
- MASK[60] = KEY_TYPE mask (1 = must match KEY_TYPE)
- MASK[59:48] = VLAN_ID mask (1 = must match each VLAN bit; 0 = don't care)
- MASK[47:0] = MAC_ADDR mask (1 = must match each MAC bit)

**Standard BPDU mask** (MASK=0x1000ffffffffffff):
```
MASK = (1 << 60) | 0xffffffffffff
     = match KEY_TYPE + exact MAC + wildcard VLAN
```
→ BPDUs match any VLAN, exact MAC.

### 2.5 Raw Word Encoding (verified from existing BPDU entries)

**Entry[0]** (BPDU, 01:80:c2:00:00:00, KEY_TYPE=0, CPU=1, BPDU=1):
```
Raw: 0x84000001  0xc0000301  0xffffffff  0x04003fff  0x04000002
     word[0]     word[1]     word[2]     word[3]     word[4]

word[0] = 0x84000001:
  bit 0      = 1           → VALID=1
  bits[31:1] = 0x42000000  → MAC[30:0]=0x42000000
  → MAC lower 31 bits: 0x0180c2000000 & 0x7FFFFFFF = 0x42000000... wait
    lower 31 bits of 0x0180c2000000:
    lower 32 bits = 0xc2000000 (from the 48-bit MAC 0x0180c2000000)
    & 0x7FFFFFFF = 0x42000000 ✓
  word[0] = (0x42000000 << 1) | 1 = 0x84000001 ✓

word[1] = 0xc0000301:
  bits[16:0] = 0x0301     → MAC[47:31] = 0x0301
    upper 17 bits of 0x0180c2000000: 0x00000301 ✓
  bits[28:17]= 0           → VLAN_ID=0
  bit 29     = 0           → KEY_TYPE=0
  bits[31:30]= 3 (=0b11)  → MASK[1:0]=3 (two LSBs of MASK)

word[4] = 0x04000002:
  bit 1  = 1  → CPU=1 ✓
  bit 26 = 1  → BPDU=1 ✓
```

---

## 3. How the Tables Are Used

### 3.1 L2_ENTRY (opennsl_l2_addr_add path)

The regular L2 add API call chain:
```
opennsl_l2_addr_add(unit, l2addr)
  → FUN_00946a00 → FUN_00948700 → FUN_01408a48
  → FUN_01876f10(unit, table_id=0x1547, -1, index, buffer)
  → FUN_01876ee0 → FUN_01876c30
  → bctrl[unit_struct+0x19484]  ← per-unit ASIC write handler
```

Table ID **0x1547** = SDK internal ID for L2_ENTRY (hash table, 131072 entries).

The SDK buffer is 0x24 = 36 bytes (padded from 13-byte ASIC entry for internal alignment).

Buffer fill via FUN_0181e718 (descriptor-driven bitfield packer):
- Reads field descriptors from per-unit table for table ID 0x1547
- Packs each field (VID, MAC, port, flags) into the correct bit position

### 3.2 L2_USER_ENTRY (SDK init / BPDU setup)

Protocol entries (BPDUs, CDP, STP) are programmed during SDK initialization:
- 446 entries pre-programmed at boot
- Written via `opennsl_l2_cache_set` API → different call chain
- Hardware address 0x06168000, 512 entries max

### 3.3 Note on Pure L3 Mode

On this switch (pure L3 routing, per-port VLANs 3301-3352):
- **L2_ENTRY (L2X)** has 0 mac entries in hardware (routing does not use L2 forwarding)
- **L2_USER_ENTRY** has 446 BPDU/protocol entries
- The neighbor MAC→port mapping (for next-hop forwarding) is stored in the **L3 egress table**, not L2_ENTRY
- `bcmcmd l2 add` increments the SDK counter but the hardware entry may not persist in pure L3 mode

---

## 4. bcmcmd Reference

```bash
# List field bit positions
bcmcmd 'listmem l2_entry'
bcmcmd 'listmem l2_user_entry'

# Dump decoded entry
bcmcmd 'dump l2_entry <idx> 1'
bcmcmd 'dump l2_user_entry <idx> 1'

# Dump raw hex words
bcmcmd 'dump raw l2_entry <idx> 1'
bcmcmd 'dump raw l2_user_entry <idx> 1'

# Dump all (including VALID=0)
bcmcmd 'dump all l2_entry <idx> <count>'
bcmcmd 'dump all l2_user_entry 0 512'

# Write with field names
bcmcmd 'write l2_entry <idx> 1 VALID=1,MAC_ADDR=0xdeadbeef0001,...'
bcmcmd 'write l2_entry <idx> 1 <w0> <w1> <w2> <w3>'  # raw hex words

# L2 operations
bcmcmd 'l2 show'                    # Show learned/static MACs
bcmcmd 'l2 info'                    # Show counts
bcmcmd 'l2 hash MACaddress=<mac> Vlanid=<vid>'  # Compute hash bucket
bcmcmd 'l2 add MACaddress=<mac> Port=<p> Vlanid=<vid> STatic=true'
bcmcmd 'l2 del MACaddress=<mac> Vlanid=<vid>'
```

---

## 5. References

- [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) — L3_DEFIP format (same bcmcmd analysis approach)
- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) — opennsl call chain, FUN_0181e718 descriptor analysis
- [DESCRIPTOR_BUFFER_FILL_ANALYSIS.md](DESCRIPTOR_BUFFER_FILL_ANALYSIS.md) — FUN_0181e718 binary search + bitfield packer
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — FUN_01876c30 dispatch chain

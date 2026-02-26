# VLAN Table Format — BCM56846 (Trident+)

**Date**: 2026-02-23
**Status**: HAVE — bit positions fully verified via bcmcmd listmem + raw dump on live switch
**Switch**: Edgecore AS5610-52X / Cumulus Linux 2.5 / <LIVE_SWITCH_IP>

---

## Summary

BCM56846 uses **two VLAN tables**, one on each pipeline side:

| Table | bcmcmd name | ASIC address | Entries | Size | Pipeline |
|-------|------------|-------------|---------|------|----------|
| **VLAN** (ingress) | `vlan` alias `QVLAN` | 0x12168000 | 4096 | 40 bytes (10 words) | ipipe0 |
| **EGR_VLAN** (egress) | `egr_vlan` | 0x0d260000 | 4096 | 29 bytes (8 words) | epipe0 |

Both tables are **directly indexed by VLAN ID** (0–4095). No hash, no TCAM — just write to `table[vlan_id]`.

---

## 1. VLAN (Ingress) Table

### 1.1 Table Properties

```
bcmcmd: listmem vlan
Memory: VLAN.ipipe0   alias QVLAN
Address: 0x12168000
Flags:   valid cachable
Blocks:  ipipe0/dma (1 copy, 1 dmaable)
Entries: 4096 with indices 0–4095
Size:    40 bytes = 10 words
Entry mask: last word 0x1fffffff (bits[319:285] valid only to bit 284)
```

### 1.2 Key Fields

Entry = 10 words (word[0]=bits[31:0] ... word[9]=bits[319:288])

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| PORT_BITMAP | [65:0] | w0[31:0]+w1[31:0]+w2[1:0] | 66 | Ingress member ports: bit0=CPU, bit1=xe0(swp1), ..., bit52=xe51(swp52) |
| ING_PORT_BITMAP | [131:66] | w2[31:2]+w3[31:0]+w4[1:0] | 66 | Same port encoding, used for ingress port membership checks |
| STG | [140:132] | w4[12:4] | 9 | Spanning Tree Group index |
| VALID | [205] | w6[13] | 1 | Entry valid bit |
| VLAN_PROFILE_PTR | [238:232] | w7[14:8] | 7 | VLAN profile index (controls IGMP/MLD snooping, PV, etc.) |
| ENABLE_IGMP_MLD_SNOOPING | [314] | w9[26] | 1 | 1 = enable IGMP/MLD snooping for this VLAN |

### 1.3 Port Bitmap Encoding

```
bit  0  = CPU port
bit  1  = xe0  (swp1)
bit  2  = xe1  (swp2)
...
bit 52  = xe51 (swp52)
```

Both PORT_BITMAP and ING_PORT_BITMAP use this same encoding. Total 53 bits used (bit 0 = CPU, bits 1–52 = xe0–xe51). The 66-bit field has bits 53–65 unused (must be 0).

### 1.4 Raw Word Encoding (verified)

**VLAN 3301** (CPU + xe0 member, both tagged as ingress):
- PORT_BITMAP = 0x3 (CPU=bit0 + xe0=bit1)
- ING_PORT_BITMAP = 0x3 (same)
- STG = 2
- VALID = 1
- VLAN_PROFILE_PTR = 2

```
Raw: 0x00000003 0x00000000 0x0000000c 0x00000000 0x00000020
     word[0]    word[1]    word[2]    word[3]    word[4]

     0x00000000 0x00002000 0x00000200 0x00000000 0x04000400
     word[5]    word[6]    word[7]    word[8]    word[9]
```

Bit-level verification:

```
PORT_BITMAP@[65:0]:
  word[0] = 0x00000003  → PORT_BITMAP[31:0] = 3 → bit0(CPU)+bit1(xe0) ✓
  word[1] = 0x00000000  → PORT_BITMAP[63:32] = 0 ✓
  word[2][1:0] = 0      → PORT_BITMAP[65:64] = 0 ✓

ING_PORT_BITMAP@[131:66]:
  word[2][31:2] = 0xc >> 2 = 3  → ING_PORT_BITMAP[29:0] = 3 → bit0(CPU)+bit1(xe0) ✓
  word[3] = 0            → ING_PORT_BITMAP[61:30] = 0 ✓
  word[4][1:0] = 0       → ING_PORT_BITMAP[65:62] = 0 ✓

STG@[140:132]:
  word[4][12:4] = (0x00000020 >> 4) & 0x1FF = 2  → STG=2 ✓

VALID@[205]:
  word[6] bit(205 mod 32) = word[6] bit 13 = (0x00002000 >> 13) & 1 = 1 ✓

VLAN_PROFILE_PTR@[238:232]:
  word[7][14:8] = (0x00000200 >> 8) & 0x7F = 2  → VLAN_PROFILE_PTR=2 ✓
```

---

## 2. EGR_VLAN (Egress) Table

### 2.1 Table Properties

```
bcmcmd: listmem egr_vlan
Memory: EGR_VLAN.epipe0
Address: 0x0d260000
Flags:   valid cachable
Blocks:  epipe0/dma (1 copy, 1 dmaable)
Entries: 4096 with indices 0–4095
Size:    29 bytes = 8 words (last word partially valid)
```

### 2.2 Key Fields

Entry = 8 words (word[0]=bits[31:0] ... word[7]=bits[255:224])

| Field | Bits | word[N] bits | Width | Notes |
|-------|------|-------------|-------|-------|
| VALID | [0] | w0[0] | 1 | Entry valid bit |
| STG | [9:1] | w0[9:1] | 9 | Spanning Tree Group index |
| OUTER_TPID_INDEX | [11:10] | w0[11:10] | 2 | Outer TPID selector (0=0x8100) |
| UT_PORT_BITMAP | [161:96] | w3[31:0]+w4[31:0]+w5[1:0] | 66 | Untagged egress ports (strip tag on TX) |
| PORT_BITMAP | [227:162] | w5[31:2]+w6[31:0]+w7[3:0] | 66 | Egress member ports (all members, tagged or untagged) |

**Note**: UT_PORT_BITMAP and PORT_BITMAP use the same port encoding (bit0=CPU, bit1=xe0, ..., bit52=xe51). A port in UT_PORT_BITMAP has its VLAN tag stripped on egress; a port in PORT_BITMAP but NOT in UT_PORT_BITMAP leaves the tag in place.

### 2.3 Raw Word Encoding (verified)

**EGR_VLAN 3301** (CPU + xe0 member; xe0 untagged, CPU tagged):
- VALID = 1
- STG = 2
- OUTER_TPID_INDEX = 0
- UT_PORT_BITMAP = 0x2 (xe0 only — xe0 is untagged)
- PORT_BITMAP = 0x3 (CPU + xe0)

```
Raw: 0x00000005 0x00000000 0x00000000 0x00000002
     word[0]    word[1]    word[2]    word[3]

     0x00000000 0x0000000c 0x00000000 0x00000000
     word[4]    word[5]    word[6]    word[7]
```

Bit-level verification:

```
VALID@[0]:
  word[0] bit 0 = 0x5 & 1 = 1 ✓

STG@[9:1]:
  word[0][9:1] = (0x5 >> 1) & 0x1FF = 2  → STG=2 ✓

OUTER_TPID_INDEX@[11:10]:
  word[0][11:10] = (0x5 >> 10) & 0x3 = 0 ✓

UT_PORT_BITMAP@[161:96]:
  bit 96 → word[3] bit 0; bit 127 → word[3] bit 31
  bit 128 → word[4] bit 0; bit 159 → word[4] bit 31
  bit 160 → word[5] bit 0; bit 161 → word[5] bit 1
  word[3] = 0x00000002  → UT_PORT_BITMAP[31:0] = 2 → bit1=xe0 ✓
  word[4] = 0x00000000  → UT_PORT_BITMAP[63:32] = 0 ✓
  word[5][1:0] = 0      → UT_PORT_BITMAP[65:64] = 0 ✓
  → UT_PORT_BITMAP = 0x2 (xe0 untagged) ✓

PORT_BITMAP@[227:162]:
  bit 162 → word[5] bit 2; bit 191 → word[5] bit 31  (30 bits)
  bit 192 → word[6] bit 0; bit 223 → word[6] bit 31  (32 bits)
  bit 224 → word[7] bit 0; bit 227 → word[7] bit 3   (4 bits)
  word[5][31:2] = (0x0000000c >> 2) = 3  → PORT_BITMAP[29:0] = 3 → bit0(CPU)+bit1(xe0) ✓
  word[6] = 0x00000000 ✓
  word[7][3:0] = 0 ✓
  → PORT_BITMAP = 0x3 (CPU + xe0) ✓
```

---

## 3. How the Tables Are Used

### 3.1 vlan_create() — write both tables atomically

For `bcm56846_vlan_create(vlan_id)`:

1. **Write VLAN[vlan_id]** (ingress) with `VALID=1`, `STG=default_stg`, `PORT_BITMAP=0` (no members yet), `VLAN_PROFILE_PTR=0`
2. **Write EGR_VLAN[vlan_id]** (egress) with `VALID=1`, `STG=default_stg`, `PORT_BITMAP=0`, `UT_PORT_BITMAP=0`

### 3.2 vlan_port_add() — update bitmaps

For `bcm56846_vlan_port_add(vlan_id, port, untagged)`:

1. Read current VLAN[vlan_id] → set bit `(port+1)` in PORT_BITMAP and ING_PORT_BITMAP → write back
2. Read current EGR_VLAN[vlan_id] → set bit `(port+1)` in PORT_BITMAP → if untagged, also set in UT_PORT_BITMAP → write back

Port-to-bit mapping:
```c
int vlan_bit(int xcport) {
    return xcport + 1;   // xe0=1, xe1=2, ..., xe51=52
}
int cpu_bit = 0;
```

### 3.3 VLAN ID Assignment (pure L3 mode)

On this switch running in pure L3 mode (no bridging), each physical port has its own VLAN:
- xe0 (swp1) → VLAN 3301
- xe1 (swp2) → VLAN 3302
- ...
- xe51 (swp52) → VLAN 3352

Each per-port VLAN has exactly two members: CPU (bit0) and the port itself (bit N). The port is untagged in EGR_VLAN (xe0 strips the tag on egress to the wire) and CPU is tagged (internal VLAN tagging for the CPU port).

### 3.4 S-Channel Write Path

Both VLAN and EGR_VLAN are written via S-Channel DMA, same path as L2/L3 tables:
```
bcm56846_vlan_create()
  → pack entry into byte buffer (40-byte VLAN or 29-byte EGR_VLAN)
  → FUN_01876f10(unit, table_id, -1, vlan_id, buffer)
  → S-Channel DMA → ASIC write
```

Table IDs (SDK internal):
- VLAN → table ID for ipipe0 VLAN table (to confirm via bcmcmd if needed)
- EGR_VLAN → table ID for epipe0 EGR_VLAN table

---

## 4. bcmcmd Reference

```bash
# Table metadata
bcmcmd 'listmem vlan'
bcmcmd 'listmem egr_vlan'

# Dump decoded entry
bcmcmd 'dump vlan <vlan_id> 1'
bcmcmd 'dump egr_vlan <vlan_id> 1'

# Dump raw hex words
bcmcmd 'dump raw vlan <vlan_id> 1'
bcmcmd 'dump raw egr_vlan <vlan_id> 1'

# Write raw words
bcmcmd 'write vlan <vlan_id> <w0> <w1> ... <w9>'
bcmcmd 'write egr_vlan <vlan_id> <w0> <w1> ... <w7>'

# Show VLAN membership (SDK level)
bcmcmd 'vlan show'
bcmcmd 'vlan show <vlan_id>'
```

---

## 5. References

- [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) — L2_ENTRY + L2_USER_ENTRY format (same bcmcmd analysis)
- [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) — L3 egress tables format
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — S-Channel DMA write path
- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) — Port address map (xe0 = BCM port 1)

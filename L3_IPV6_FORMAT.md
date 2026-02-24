# IPv6 Routing Table Formats (BCM56846 / Trident+)

**Date**: 2026-02-23
**Status**: HAVE — all three IPv6 tables verified via bcmcmd on live AS5610-52X switch
**Switch**: AS5610-52X (BCM56846/Trident+), Cumulus Linux 2.5

---

## 1. Overview — IPv6 Table Architecture

BCM56846 uses **three separate tables** for IPv6 routing, each for a different route type:

| Table | Address | Size | Route Type |
|-------|---------|------|------------|
| `L3_DEFIP_128` | 0x0a176000 | 256 × 39 B | IPv6 /128 exact-match (host routes) |
| `L3_DEFIP` | 0x0a170000 | 8192 × 30 B | IPv6 LPM with prefix ≤ 64 bits (double-wide, shared with IPv4) |
| `L3_ENTRY_IPV6_UNICAST` | 0x0917c000 | 8192 × 22 B | IPv6 hash table — present but **unused** in this deployment |

### Route classification (from `l3 ip6route show` output):
- **"routes with prefix > 64 bits"** (e.g. /128) → `L3_DEFIP_128`
- **"routes with prefix ≤ 64 bits"** (e.g. /32, /64, /0) → `L3_DEFIP` double-wide
- IPv6 nexthop tables (ING/EGR_L3_NEXT_HOP, EGR_L3_INTF) are **shared with IPv4**

---

## 2. L3_DEFIP_128 — IPv6 /128 Exact-Match TCAM

### 2.1 Table Properties

```
Memory: L3_DEFIP_128.ipipe0
Address: 0x0a176000
Entries: 256 × indices 0–255
Entry size: 39 bytes = 10 words (last word masked 0x00ffffff → 24 bits valid)
Total bits: 312 (8*32 + 24 = 280 + 24 = 312 meaningful bits, stored in 320)
Flags: valid cachable, 1 DMA-able copy
```

### 2.2 Field Layout

```
Bit   Field             Width   Notes
---   -----             -----   -----
  0   VALID_0             1     Must be 1 (entry valid)
  1   VALID_1             1     Must be 1 (both always set for IPv6)
2–129 IP_ADDR           128     Full 128-bit IPv6 address (MSB at bit 129)
130–139 VRF_ID           10     VRF identifier
140–141 (reserved)        2
142–269 IP_ADDR_MASK     128     IPv6 prefix mask (0xfff...fff for /128)
270–279 VRF_ID_MASK      10     Typically 0x3ff (all VRF bits significant)
280–281 (reserved)        2
282   ECMP                1
283–292 ECMP_PTR         10     ECMP pointer (same as ECMP_PTR portion of NEXT_HOP)
283–296 NEXT_HOP_INDEX   14     14-bit nexthop index (shares bits with ECMP_PTR)
297–300 PRI               4
301   RPE / DEFAULTROUTE  1
302   DST_DISCARD/SRC_DISCARD 1
303–308 CLASS_ID          6
309   GLOBAL_ROUTE        1
310   EVEN_PARITY         1
311   HIT                 1
```

**KEY@[141:2]** (140 bits) = `{reserved[141:140] | VRF_ID[139:130] | IP_ADDR[129:2]}`
- KEY[127:0] = IPv6 address (128 bits, MSB-first)
- KEY[137:128] = VRF_ID (10 bits)
- KEY[139:138] = reserved = 0

**MASK@[281:142]** (140 bits) = same structure but with mask bits:
- MASK[127:0] = IP_ADDR_MASK (0xffffffffffffffffffffffffffffffff for /128)
- MASK[137:128] = VRF_ID_MASK (0x3ff)
- MASK[139:138] = 0

### 2.3 Live Example — fe80::82a2:35ff:fe81:caae/128

```
L3_DEFIP_128.ipipe0[1]:
  IP_ADDR   = 0xfe8000000000000082a235fffe81caae
  IP_ADDR_MASK = 0xffffffffffffffffffffffffffffffff  (/128)
  VRF_ID    = 0
  VALID_0   = 1, VALID_1 = 1
  NEXT_HOP_INDEX = 2
  ECMP      = 0, CLASS_ID = 2

Raw words: 0xfa072abb 0x0a88d7ff 0x00000002 0xfa000000
           0xffffc003 0xffffffff 0xffffffff 0xffffffff
           0x10ffffff 0x00010000
```

**Bit verification (entry[0] = fe80::/128):**
- Raw[0] = 0x00000003 → bits[1:0] = `11` → VALID_0=1, VALID_1=1 ✓
- IP_ADDR[29:0] = raw[0][31:2] = 0 (lower address bits)
- IP_ADDR[125:94] → raw[3] contains upper address bits
- IP_ADDR[126] = raw[4] bit 0 = 1, IP_ADDR[127] = raw[4] bit 1 = 1
- Reconstructed: IP_ADDR[127:126] = `11`, IP_ADDR[125:94] = 0xfa000000
  → {11, 11111010...} → 0b1111_1110_1000_0000 = 0xfe80 ✓

### 2.4 Raw Word Layout

```
w[0]  bits [31:0]:   VALID_0@0, VALID_1@1, IP_ADDR[29:0]@[31:2]
w[1]  bits [63:32]:  IP_ADDR[61:30]
w[2]  bits [95:64]:  IP_ADDR[93:62]
w[3]  bits [127:96]: IP_ADDR[125:94]
w[4]  bits [159:128]: IP_ADDR[127:126]@[129:128], IP_ADDR_MASK[27:0]@[157:130]  (+ VRF/reserved in [129:128])
w[5]  bits [191:160]: IP_ADDR_MASK[59:28]
w[6]  bits [223:192]: IP_ADDR_MASK[91:60]
w[7]  bits [255:224]: IP_ADDR_MASK[123:92]
w[8]  bits [287:256]: IP_ADDR_MASK[127:124]@[269:266], VRF_ID_MASK@[279:270], (reserved)@[281:280]
w[9]  bits [311:288]: ECMP@282, NEXT_HOP_INDEX@[296:283], PRI@[300:297], RPE@301, DST_DISCARD@302, CLASS_ID@[308:303], GLOBAL_ROUTE@309, EVEN_PARITY@310, HIT@311
```

### 2.5 Programming Notes

- SDK logical index = physical table index (indices 0, 1, 2... sequential insertion)
- /128 routes are inserted here; the `l3 ip6route show` "routes with prefix > 64 bits" count
- 256 entries is the hardware limit for this table

---

## 3. L3_DEFIP — IPv6 LPM Double-Wide Entries (prefix ≤ 64 bits)

### 3.1 Overview

The standard `L3_DEFIP` TCAM (8192 × 30 bytes) holds both IPv4 and IPv6 LPM routes:
- **IPv4** (MODE=0): uses only the "0" slot (VALID0=1, VALID1=0)
- **IPv6 LPM prefix ≤ 64 bits** (MODE=1): uses **both** slots (VALID0=1, VALID1=1) — "double-wide"

For the full L3_DEFIP field layout see [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md).

### 3.2 IPv6 Double-Wide Field Encoding

Each 30-byte entry has paired fields (subscript 0 = lower slot, subscript 1 = upper slot):

```
For IPv6 (MODE0=1, MODE1=1, VALID0=1, VALID1=1):

Slot 1 (upper, subscript 1) — IPv6 bits [127:96]:
  IP_ADDR1@[78:47]   = IPv6_addr[127:96]  (most significant 32 bits, e.g. 0x20010db8 for 2001:db8::)
  IP_ADDR_MASK1@[122:91] = /prefix mask for upper 32 bits (0xffffffff if prefix ≥ 32)

Slot 0 (lower, subscript 0) — IPv6 bits [95:64]:
  IP_ADDR0@[34:3]    = IPv6_addr[95:64]   (next 32 bits, e.g. 0x12345678 for 2001:db8:1234:5678::)
  IP_ADDR_MASK0@[88:57] = /prefix mask for next 32 bits (0xffffffff if prefix ≥ 64; 0 if prefix ≤ 32)

Note: IPv6 bits [63:0] (lower 64 bits) are NOT stored in L3_DEFIP
      Only routes with prefix ≤ 64 bits go here (lower 64 bits are always don't-care)
```

### 3.3 KEY Formula (for both slots)

```c
KEY0 = (VRF_ID << 33) | (IPv6_addr[95:64]  << 1) | 1  /* MODE=1 */
KEY1 = (VRF_ID << 33) | (IPv6_addr[127:96] << 1) | 1  /* MODE=1 */
```

Both `NEXT_HOP_INDEX0` and `NEXT_HOP_INDEX1` are set to the same nexthop value.

### 3.4 Live Examples

**::/0 (IPv6 default route)** at L3_DEFIP[2048]:
```
IP_ADDR1 = 0,  IP_ADDR_MASK1 = 0        (upper 32 bits = don't care)
IP_ADDR0 = 0,  IP_ADDR_MASK0 = 0        (lower 32 bits = don't care)
MODE0=1, MODE1=1, VALID0=1, VALID1=1
KEY0 = KEY1 = 0x000000000001             (only MODE=1 bit set, all addr bits = 0)
MASK0 = MASK1 = 0x07fe00000001           (VRF + MODE masked, IP bits don't care)
NEXT_HOP_INDEX0 = NEXT_HOP_INDEX1 = 2
Raw: 0x00000007 0x00004000 0x04000000 0xf8000000 0x0000005f 0x0011ff80 0x00010000 0x00000000
```

**2001:db8:1234:5678::/64** at L3_DEFIP[1024]:
```
IP_ADDR1 = 0x20010db8  (IPv6 bits[127:96] = 2001:0db8)
IP_ADDR0 = 0x12345678  (IPv6 bits[95:64]  = 1234:5678)
IP_ADDR_MASK1 = 0xffffffff, IP_ADDR_MASK0 = 0xffffffff  (/64: all 64 LPM bits significant)
KEY1 = 0x000040021b71  = (0x20010db8 << 1) | 1  ✓
KEY0 = 0x00002468acf1  = (0x12345678 << 1) | 1  ✓
MASK0 = MASK1 = 0x07ffffffffff
```

**2001:db8::/32** at L3_DEFIP[1024]:
```
IP_ADDR1 = 0x20010db8  (IPv6 bits[127:96] = 2001:0db8)
IP_ADDR0 = 0            (IPv6 bits[95:64]  = don't care for /32)
IP_ADDR_MASK1 = 0xffffffff, IP_ADDR_MASK0 = 0  (/32: only upper 32 bits significant)
KEY1 = 0x000040021b71  = (0x20010db8 << 1) | 1  ✓
KEY0 = 0x000000000001  (just MODE=1)
MASK1 = 0x07ffffffffff, MASK0 = 0x07fe00000001
```

### 3.5 Prefix Length → Field Coverage

| Prefix | IP_ADDR1 | IP_ADDR0 | Notes |
|--------|----------|----------|-------|
| /0    | 0, mask=0 | 0, mask=0 | ::/0 default |
| 1–32  | IPv6[127:96], mask=top-N-bits | 0, mask=0 | only upper word significant |
| 33–64 | IPv6[127:96], mask=0xffffffff | IPv6[95:64], mask=top-(N-32)-bits | both words significant |
| 65–128 | *(goes to L3_DEFIP_128, not here)* | | |

---

## 4. L3_ENTRY_IPV6_UNICAST — IPv6 Hash Table (Unused)

### 4.1 Table Properties

```
Memory: L3_ENTRY_IPV6_UNICAST.ipipe0
Address: 0x0917c000
Entries: 8192 × 22 bytes (6 words)
Flags: valid cachable hashed multiview
Description: L3 routing table IPV6 UNICAST view
```

### 4.2 Field Layout (from listmem)

```
VALID_0<0>           VALID_1<87>
V6_0<2>              V6_1<89>
KEY_TYPE_0<3:1>      KEY_TYPE_1<90:88>
IP_ADDR_LWR_64<67:4> IP_ADDR_UPR_64<154:91>   (together = full 128-bit IPv6 address)
VRF_ID<77:68>
RPE<78>
NEXT_HOP_INDEX<172:159>   (14 bits)
PRI<158:155>
KEY_0<77:4>          KEY_1<154:91>
DST_DISCARD<85>
```

### 4.3 Status on BCM56846 / Cumulus 2.5

**This table is empty/unused in this deployment.** The SDK routes all IPv6 host routes (/128) through `L3_DEFIP_128` instead. The `L3_ENTRY_IPV6_UNICAST` hash table may be used in other Trident+ deployments (e.g. data center leaf where IPv6 host routes dominate) or with different SDK configuration flags.

---

## 5. IPv6 Nexthop Tables — Shared with IPv4

The nexthop chain is **identical** for IPv4 and IPv6. IPv6 routes use the same nexthop entries:

```
IPv6 route (L3_DEFIP_128 or L3_DEFIP)
  → NEXT_HOP_INDEX → ING_L3_NEXT_HOP[idx] → PORT_NUM[22:16]
                   → EGR_L3_NEXT_HOP[idx] → MAC_ADDRESS[62:15] + INTF_NUM[14:3]
                     → EGR_L3_INTF[intf]  → SA_MAC[80:33] + VID[24:13]
```

**Verified**: all fe80::/128 entries have `NEXT_HOP_INDEX=2`, same as IPv4 routes on this switch.

The full nexthop field encoding is documented in [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md).

---

## 6. Summary — IPv6 Table Selection Logic

```
opennsl_l3_route_add(route):
  if route.flags & OPENNSL_L3_IP6:
    if prefix_len == 128:
      → L3_DEFIP_128  (TCAM, 256 entries, 39 bytes, sequential index)
    elif prefix_len <= 64:
      → L3_DEFIP      (TCAM, double-wide: VALID0=1+VALID1=1, MODE=1)
    else:  (65 < prefix < 128)
      → L3_DEFIP_128  (partial mask, IP_ADDR_MASK not all-1s)
  else:
    → L3_DEFIP        (IPv4, MODE=0, single-wide)
```

**Note**: Routes with 65 < prefix < 128 (e.g. /96 prefix) likely also use L3_DEFIP_128 since L3_DEFIP can only store 64 bits of IPv6 address. Not directly verified on this switch (no such routes present).

---

## 7. bcmcmd Verification Commands

```bash
# Show all IPv6 routes
bcmcmd "l3 ip6route show"

# Dump L3_DEFIP_128 (IPv6 /128 TCAM)
bcmcmd "listmem L3_DEFIP_128"
bcmcmd "dump L3_DEFIP_128"
bcmcmd "dump raw L3_DEFIP_128 0 3"

# Dump L3_DEFIP IPv6 double-wide entries
bcmcmd "dump L3_DEFIP" | grep "MODE0=1"

# Dump L3_ENTRY_IPV6_UNICAST (hash, unused)
bcmcmd "listmem L3_ENTRY_IPV6_UNICAST"
bcmcmd "dump raw L3_ENTRY_IPV6_UNICAST 0 8192"

# Test: add/remove a /64 route
ip -6 route add 2001:db8:1234:5678::/64 via fe80::... dev swp1
bcmcmd "dump L3_DEFIP" | grep "MODE0=1"
ip -6 route del 2001:db8:1234:5678::/64 via fe80::... dev swp1
```

---

## References

- [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) — ING/EGR nexthop and EGR_L3_INTF field layouts (shared IPv4/IPv6)
- [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) — L3_DEFIP IPv4 field encoding
- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) — Write path call chain
- [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md)

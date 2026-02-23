# L3 Nexthop Table Chain — Field Layout (Path B 3.4–3.9)

**Date**: 2026-02-23
**Status**: HAVE — bit positions verified via `bcmcmd listmem` + `dump raw` + cross-table chain tracing on live switch
**Switch**: AS5610-52X (BCM56846/Trident+), Cumulus Linux 2.5

---

## 1. Complete L3 Forwarding Chain

```
L3_DEFIP[prefix]
  → NEXT_HOP_INDEX (14-bit, from ECMP_PTR or NHOP field)
        ↓
ING_L3_NEXT_HOP[NEXT_HOP_INDEX]          ← ingress pipeline uses this for routing decision
  → PORT_NUM (7-bit physical port)
  → MODULE_ID (8-bit module, 0 for single-unit)
  → T (trunk flag)
        ↓
EGR_L3_NEXT_HOP[NEXT_HOP_INDEX]          ← egress pipeline uses this for header rewrite
  → L3:MAC_ADDRESS (48-bit destination MAC)
  → L3:INTF_NUM (12-bit egress interface index)
        ↓
EGR_L3_INTF[INTF_NUM]                    ← egress pipeline: source MAC + VLAN
  → MAC_ADDRESS (48-bit source/router MAC for this interface)
  → VID (12-bit egress VLAN)
```

For ECMP routes, there is an additional level of indirection:

```
L3_DEFIP → ECMP_PTR (ECMP group index)
  → L3_ECMP_GROUP[ECMP_PTR]
      → BASE_PTR + COUNT
  → L3_ECMP[BASE_PTR + (hash % COUNT)]
      → NEXT_HOP_INDEX
  → ING/EGR_L3_NEXT_HOP[NEXT_HOP_INDEX] (as above)
```

---

## 2. Table Addresses and Sizes

| Table | ASIC address | Entries | Entry size | Words |
|-------|-------------|---------|------------|-------|
| L3_DEFIP | 0x07120000 (via TCAM DMA) | 8192 pairs | 30 bytes | 8 |
| L3_ECMP | 0x0e176000 | 4096 | 2 bytes | 1 |
| L3_ECMP_GROUP | 0x0e174000 | 1024 | 25 bytes | 7 |
| ING_L3_NEXT_HOP | 0x0e17c000 | 16384 | 5 bytes | 2 |
| EGR_L3_NEXT_HOP | 0x0c260000 | 16384 | 15 bytes | 4 |
| EGR_L3_INTF | 0x01264000 | 4096 | 15 bytes | 4 |

---

## 3. L3_ECMP — ECMP Member Table

```
Memory: L3_ECMP.ipipe0 address 0x0e176000
Entries: 4096 × 2 bytes (1 word, mask 0x00007fff)
```

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `NEXT_HOP_INDEX` | [13:0] | 14 | Index into ING/EGR_L3_NEXT_HOP tables |
| `NEXT_HOP` | [13:0] | 14 | Alias for NEXT_HOP_INDEX |
| `EVEN_PARITY` | [14] | 1 | Parity bit |

**Encoding**: Each entry in L3_ECMP is a 15-bit word = `EVEN_PARITY[14] | NEXT_HOP_INDEX[13:0]`.

For an ECMP group with N members, entries are placed at consecutive indices `BASE_PTR, BASE_PTR+1, ..., BASE_PTR+N-1`.

---

## 4. L3_ECMP_GROUP — ECMP Group Descriptor Table

```
Memory: L3_ECMP_GROUP.ipipe0 address 0x0e174000
Entries: 1024 × 25 bytes (7 words, mask: -1 -1 -1 -1 -1 -1 0x0000003f)
```

### 4.1 Group Size Fields

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `BASE_PTR` | [21:10] | 12 | Base index in L3_ECMP table (alias: `BASE_PTR_0`) |
| `COUNT` | [9:0] | 10 | Number of members in group (alias: `COUNT_0`) |
| `ECMP_GT8` | [196] | 1 | Set when group has > 8 members |
| `EVEN_PARITY_0` | [80] | 1 | Parity for words 0–2 |
| `EVEN_PARITY_1` | [197] | 1 | Parity for words 3–6 |

For groups with ≤ 4 sub-groups (BCM56846 multi-LPM design), four parallel (BASE_PTR, COUNT) pairs exist:
- `BASE_PTR_0<19:8>`, `COUNT_0<7:0>` — primary
- `BASE_PTR_1<39:28>`, `COUNT_1<27:20>` — for paired sub-tables
- `BASE_PTR_2<59:48>`, `COUNT_2<47:40>`
- `BASE_PTR_3<79:68>`, `COUNT_3<67:60>`

### 4.2 Precomputed Fast-Path OIFs (for ≤ 8 members)

When `ECMP_GT8=0`, up to 8 nexthops are precomputed per group:

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `L3_OIF_0` | [94:82] | 13 | Precomputed nexthop 0 |
| `L3_OIF_0_TYPE` | [81] | 1 | OIF 0 type flag |
| `L3_OIF_1` | [108:96] | 13 | Precomputed nexthop 1 |
| `L3_OIF_1_TYPE` | [95] | 1 | OIF 1 type flag |
| `L3_OIF_2` | [122:110] | 13 | Precomputed nexthop 2 |
| `L3_OIF_2_TYPE` | [109] | 1 | OIF 2 type flag |
| `L3_OIF_3` | [136:124] | 13 | ... |
| `L3_OIF_4` | [150:138] | 13 | |
| `L3_OIF_5` | [164:152] | 13 | |
| `L3_OIF_6` | [178:166] | 13 | |
| `L3_OIF_7` | [192:180] | 13 | |
| `URPF_COUNT` | [195:193] | 3 | URPF member count |

### 4.3 Usage Formula

```
group_index → BASE_PTR, COUNT
hash = per-packet hash (based on 5-tuple or other)
slot = BASE_PTR + (hash % COUNT)
NEXT_HOP_INDEX = L3_ECMP[slot].NEXT_HOP_INDEX
```

---

## 5. ING_L3_NEXT_HOP — Ingress Nexthop (Port Routing)

```
Memory: ING_L3_NEXT_HOP.ipipe0 address 0x0e17c000
Entries: 16384 × 5 bytes (2 words, mask: -1 0x00000007)
```

This is a multiview table; fields depend on `ENTRY_TYPE`.

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `ENTRY_TYPE` | [1:0] | 2 | 0=L3 unicast, 1=trunk, 2=virtual port |
| `PORT_NUM` | [22:16] | 7 | Physical port (when T=0, ENTRY_TYPE=0) |
| `TGID` | [25:16] | 10 | Trunk group ID (when T=1) |
| `T` | [31] | 1 | Trunk flag (1 = use TGID instead of PORT_NUM) |
| `MODULE_ID` | [30:23] | 8 | Module ID (0 for single non-stacking unit) |
| `DROP` | [32] | 1 | Drop this nexthop |
| `COPY_TO_CPU` | [33] | 1 | Copy to CPU |
| `EVEN_PARITY` | [34] | 1 | Parity bit |

**Alternative view fields** (depend on ENTRY_TYPE):
- `VLAN_ID<13:2>` — overlaps PORT_NUM area; used for some entry types
- `MTU_SIZE<15:2>` — MTU check index
- `L3_OIF<14:2>` — outgoing interface for MPLS/VPN

**Verified example** (nexthop index 3 → swp1/xe0):
```
ING_L3_NEXT_HOP[3]: raw = 0x00010004 0x00000000
  ENTRY_TYPE = bits[1:0] = 0 (L3 unicast)
  PORT_NUM   = bits[22:16] = (0x00010004 >> 16) & 0x7f = 1  ← swp1 = xe0 = port 1
  MODULE_ID  = bits[30:23] = 0
  T          = bit[31] = 0 (not trunk)
```

---

## 6. EGR_L3_NEXT_HOP — Egress Nexthop (Header Rewrite)

```
Memory: EGR_L3_NEXT_HOP.epipe0 address 0x0c260000
Entries: 16384 × 15 bytes (4 words, mask: -1 -1 -1 0x001fffff)
```

Multiview table; for L3 unicast (`ENTRY_TYPE=0`), the L3 view fields are:

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `L3:MAC_ADDRESS` | [62:15] | 48 | Destination (neighbor) MAC address |
| `L3:INTF_NUM` | [14:3] | 12 | Index into EGR_L3_INTF (source interface) |
| `L3:IVID` | [26:15] | 12 | Inner VLAN ID (QinQ inner tag) |
| `L3:OVID` | [14:3] | 12 | Outer VLAN (overlaps INTF_NUM; used in VLAN context) |
| `L3:L3_UC_VLAN_DISABLE` | [66] | 1 | Disable VLAN rewrite for this nexthop |
| `L3:L3_UC_TTL_DISABLE` | [65] | 1 | Disable TTL decrement |
| `L3:L3_UC_SA_DISABLE` | [63] | 1 | Disable source MAC rewrite |
| `L3:L3_UC_DA_DISABLE` | [64] | 1 | Disable destination MAC rewrite |
| `ENTRY_TYPE` | [1:0] | 2 | 0=L3 unicast; other=SD_TAG/MPLS/etc. |
| `EVEN_PARITY` | [67] | 1 | (not shown in listmem but present in raw) |

**Verified example** (nexthop index 3 → neighbor 6c:b2:ae:cd:13:33 on swp1):
```
EGR_L3_NEXT_HOP[3]: raw = 0x89998008 0x36595766 0x00000000 0x00000000
  L3:MAC_ADDRESS = 0x6cb2aecd1333  (bits[62:15] → neighbor's DA MAC)
  L3:INTF_NUM    = 1               (bits[14:3] → EGR_L3_INTF[1] = swp1 interface)
  ENTRY_TYPE     = 0               (L3 unicast)
```

---

## 7. EGR_L3_INTF — Egress L3 Interface (Source MAC + VLAN)

```
Memory: EGR_L3_INTF.epipe0 address 0x01264000
Entries: 4096 × 15 bytes (4 words, mask: -1 -1 -1 0x0007ffff)
```

| Field | Bits | Width | Description |
|-------|------|-------|-------------|
| `MAC_ADDRESS` | [80:33] | 48 | Source (router) MAC for this L3 interface |
| `VID` | [24:13] | 12 | Egress VLAN ID (per-port VLAN for AS5610-52X) |
| `OVID` | [24:13] | 12 | Outer VLAN (same bits as VID) |
| `IVID` | [93:82] | 12 | Inner VLAN (for QinQ; unused in L3 router mode) |
| `IVID_VALID` | [81] | 1 | IVID is valid |
| `EVEN_PARITY` | [114] | 1 | Parity |
| `TTL_THRESHOLD` | [32:25] | 8 | TTL threshold for ICMP unreachable |
| `DSCP_SEL` | [12:11] | 2 | DSCP remarking selector |
| `L2_SWITCH` | [113] | 1 | Act as L2 switch (not L3 router) |

**Verified example** (interface 1 = swp1/xe0):
```
EGR_L3_INTF[1]: raw = 0x019ca000 0x6b03955e 0x00010144 0x00000000
  VID         = (0x019ca000 >> 13) & 0xfff = 0xce5 = 3301  ← swp1's per-port VLAN ✓
  MAC_ADDRESS = bits[80:33] = 0x80a23581caaf                ← switch's own MAC on swp1 ✓
```

**On the AS5610-52X** (52-port pure L3 router with per-port VLANs):
- EGR_L3_INTF[N] maps N=1..52 to ports swp1..swp52
- VID = 0xce4 + N (i.e., 3301 + N−1 for N ≥ 1)
- MAC_ADDRESS = sequential: 0x80a23581caae + N (the switch's per-port MAC address)

---

## 8. Raw Encoding Verification Summary

| Table | Entry | Raw words | Key field | Decoded |
|-------|-------|-----------|-----------|---------|
| EGR_L3_INTF | [1] | `0x019ca000 0x6b03955e 0x00010144 0x00000000` | VID[24:13] | (raw>>13)&0xfff = **0xce5 = 3301** ✓ |
| EGR_L3_INTF | [1] | — | MAC_ADDRESS[80:33] | **0x80a23581caaf** ✓ |
| ING_L3_NEXT_HOP | [3] | `0x00010004 0x00000000` | PORT_NUM[22:16] | (raw>>16)&0x7f = **1** (swp1) ✓ |
| EGR_L3_NEXT_HOP | [3] | `0x89998008 0x36595766 0x00000000 0x00000000` | L3:MAC_ADDRESS[62:15] | **0x6cb2aecd1333** ✓ |
| EGR_L3_NEXT_HOP | [3] | — | L3:INTF_NUM[14:3] | **1** (→ EGR_L3_INTF[1] = swp1) ✓ |

---

## 9. VLAN_XLATE

```
Memory: VLAN_XLATE.ipipe0 address 0x04170000
Entries: 8192 × 15 bytes (4 words), hashed BCAM
```

The AS5610-52X in pure L3 router mode has **no active VLAN_XLATE entries** — `dump vlan_xlate` returns zero results. VLAN translation is not used in this configuration; the per-port VLANs are set at init time via VLAN_PORT or XLPORT registers, not via VLAN_XLATE.

The table supports `XLATE` view (tagged VLAN translation) and `VIF` view (virtual interface). Key fields from `listmem`:
- `XLATE:KEY<44:1>` — lookup key (port + VLAN + tag type)
- `XLATE:NEW_VLAN_ID<58:47>` — translated egress VLAN ID
- `XLATE:NEW_OVID<58:47>` — translated outer VLAN
- `XLATE:TAG_ACTION_PROFILE_PTR<89:84>` — action profile (replace/add/strip)
- `XLATE:SOURCE_VP<83:71>` — source virtual port
- `VIF:SRC_VIF<32:21>` — source VIF index

For the AS5610-52X pure L3 use case, VLAN_XLATE is not needed.

---

## References

- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) — write path call chain for ECMP/VLAN tables
- [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) — L3_DEFIP write mechanism confirmed (S-channel DMA)
- [L3_ENTRY_FORMAT.md](L3_ENTRY_FORMAT.md) — L3_DEFIP TCAM bit layout (verified)
- [L2_NEXTHOP_FORMAT.md](L2_NEXTHOP_FORMAT.md) — (see L2_ENTRY_FORMAT.md for L2 path)
- [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md)

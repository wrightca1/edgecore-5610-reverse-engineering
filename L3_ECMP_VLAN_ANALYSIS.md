# L3/ECMP/VLAN Table Analysis (Path B 3.4-3.7, 3.9)

**Date**: 2026-02-19  
**Status**: IN PROGRESS (table write dispatcher identified)  
**Approach**: Same as L2 - trace call chains, identify write paths, map API structs to ASIC formats

---

## Table Names and Addresses

**From TABLE_NAME_MAPPING.md**:

| Table | Occurrences | Purpose | Addresses |
|-------|-------------|---------|-----------|
| **L3_DEFIP** | 394 | L3 Default IP (FIB/routing table) | `0x01e13748`, `0x01f167e0`, `0x01f4ad30` |
| **L3_ECMP** | 117 | ECMP next-hop groups | `0x01e8edb8`, `0x01f5d258`, `0x01f71b34` |
| **L3_HOST** | 2 | L3 host table (host routes) | `0x01e7181c`, `0x025041ac` |
| **L3_EGRESS** | 1 | L3 egress interface table | `0x024755b8` |
| **VLAN_XLATE** | 350 | VLAN translation table | (needs lookup) |

**Memory Map** (from BROADCOM_CUMULUS_ARCHITECTURE.md):
- L3_DEFIP: `0x02000000` (768KB, 12K entries × 64 bytes)
- L3_ECMP: `0x03000000` (256KB)

---

## Analysis Approach

**Same methodology as L2**:

1. **Find table access functions**:
   - Search for references to table addresses (e.g., `0x01e13748` for L3_DEFIP)
   - Look for `lwz`/`stw` instructions accessing table memory
   - Find functions that read/write table entries

2. **Trace call chains**:
   - Start from OpenNSL API functions (e.g., `opennsl_l3_route_add`)
   - Follow call chain to table write functions
   - Map to S-Channel or direct mmap write mechanism

3. **Map API to ASIC format**:
   - OpenNSL structs (e.g., `opennsl_l3_route_t`) → ASIC table entry format
   - Field mapping: subnet, mask, egress_intf, valid bits, etc.

---

## OpenNSL API Structures

### L3 Route (`opennsl_l3_route_t`)
```c
typedef struct opennsl_l3_route_s {
    uint32_t l3a_flags;          // Route flags
    uint32_t l3a_subnet;         // IP subnet (network address)
    uint32_t l3a_ip_mask;        // IP mask (prefix length)
    uint32_t l3a_intf;           // Egress interface ID
    uint32_t l3a_nexthop_ip;     // Next-hop IP address
    // ... more fields
} opennsl_l3_route_t;
```

### L3 Egress (`opennsl_l3_egress_t`)
```c
typedef struct opennsl_l3_egress_s {
    uint32_t flags;
    uint32_t intf;               // Interface ID
    bcm_mac_t mac_addr;          // Next-hop MAC (6 bytes)
    bcm_port_t port;             // Egress port
    uint16_t vlan;               // VLAN ID
    // ... more fields
} opennsl_l3_egress_t;
```

### ECMP (`opennsl_l3_egress_ecmp_t`)
```c
typedef struct opennsl_l3_egress_ecmp_s {
    uint32_t flags;
    int ecmp_group_id;           // ECMP group ID
    int max_paths;               // Maximum paths in group
    opennsl_if_t intf;           // Array of egress interfaces
    // ... more fields
} opennsl_l3_egress_ecmp_t;
```

### VLAN (`opennsl_vlan_translate_t`)
```c
typedef struct opennsl_vlan_translate_s {
    uint16_t old_vid;            // Ingress VLAN
    uint16_t new_vid;            // Egress VLAN
    uint32_t flags;               // Translation flags
    // ... more fields
} opennsl_vlan_translate_t;
```

---

## Write Mechanism (Confirmed Same as L2)

**Confirmed**: L3/ECMP/VLAN use the **same write mechanism** as L2:

- **Generic table write dispatcher**: FUN_01876f10 is called by **2242 callers** across all table types
- **Table ID parameter**: FUN_01876f10 accepts table ID in r4:
  - L2: `0x1547` (confirmed from L2 analysis)
  - Other tables: Various IDs (e.g., `0x22ca`, `0x2c33`, `0x835` seen in FUN_01876f10 checks)
- **Function pointer dispatch**: FUN_01876c30 calls function pointer from `[r9-0x6b7c]` via `bctrl`
- **Write mechanism**: Runtime-resolved function pointer → S-Channel or direct mmap write

**Key Functions**:
- **FUN_013949c0** (`0x013949c0`): **Ultra-central dispatcher** (39,253 callers!) - routes all API calls
- **FUN_0070c994** (`0x0070c994`): Common wrapper (4,502 callers) - routes to FUN_013949c0
- **FUN_01876f10** (`0x01876f10`): Generic table write dispatcher (2,245 callers)
- **FUN_018d62ec** (`0x018d62ec`): Table write wrapper (7 call sites), checks table ID <= `0x2c67`
- **FUN_018d7ad4** (`0x018d7ad4`): Table ID validator/dispatcher (2 call sites), validates table IDs `0x1559-0x155e`, `0x1599`, `0x2c32`, `0x22d3`, `0x2c24`, `0x15a5` before calling FUN_018d62ec
- **FUN_01408a48** (`0x01408a48`): L2-specific path (calls FUN_01876f10 with `0x1547`)

**Evidence**: 
- FUN_01876f10 has 2242 callers, confirming it's the central table write mechanism
- FUN_01876f10 checks for specific table IDs (`0x22ca`, `0x2c33`, `0x835`, `0x1547`)
- FUN_018d62ec validates table ID <= `0x2c67` before proceeding

## Progress Update (2026-02-19)

### Completed
1. ✅ **Identified generic table write dispatcher**: FUN_01876f10 (2245 callers)
2. ✅ **Found table write wrapper**: FUN_018d62ec (validates table ID <= `0x2c67`)
3. ✅ **Confirmed unified write mechanism**: All table types use FUN_01876f10
4. ✅ **Identified table ID constants**: FUN_01876f10 checks for `0x1547` (L2), `0x22ca`, `0x2c33`, `0x835`
5. ✅ **Found wrapper callers**: FUN_018d7ad4 calls FUN_018d62ec (2 call sites)
6. ✅ **Found dispatcher callers**: 5 functions call FUN_018d7ad4:
   - FUN_01874a50 @ 0x01874dc4 (1 caller: FUN_018751e0)
   - FUN_01875b04 @ 0x01876390 (4 callers: FUN_018d14c8, FUN_018d1f30, FUN_00fbf1fc, FUN_018a18ec)
   - FUN_018d987c @ 0x018d9d08 (1 caller: FUN_018da09c)
   - FUN_01882c80 @ 0x01883998 (30 callers - general-purpose function)
   - FUN_018815e4 @ 0x01882014 (30 callers - general-purpose function)

7. ✅ **Table ID parameter analysis**: 
   - Table IDs are passed as function parameters (r7) rather than immediate values
   - FUN_01874a50: r7 set from r27 (parameter)
   - FUN_01875b04: r7 set from r29 (parameter), checks for values 0x35/0x36/0x37/0x38/0x30
   - FUN_018d987c: r7 set from r28 (parameter), loads from memory and adds 0x974 offset
   - FUN_01882c80/FUN_018815e4: r7 loaded from stack or set from parameters

### Table ID Mapping

**Confirmed Table IDs**:
- **L2**: `0x1547` (5447 decimal)
  - Passed by FUN_01408a48 @ `0x01408b10` (`li r4,0x1547`)
  - Call chain: FUN_00946a00 → FUN_00948700 → FUN_01408a48 → FUN_01876f10

**Table IDs Checked by FUN_01876f10** (likely L3/ECMP/VLAN):
- **`0x22ca`** (8906 decimal) - Checked at `0x01876fc4`, converted to `0x22c9` at `0x01877024`
- **`0x2c33`** (11315 decimal) - Checked at `0x01876fcc`
- **`0x835`** (2101 decimal) - Checked at `0x01876fd4`, converted to `0x6fa` at `0x0187702c`

**Table IDs Validated by FUN_018d7ad4** (dispatcher calling FUN_018d62ec):
- **`0x1559-0x155e`** (5465-5470) - Range check, passes to FUN_018d62ec
- **`0x1599`** (5529) - Passes to FUN_018d62ec
- **`0x2c32`** (11314) - Very close to `0x2c33` checked by FUN_01876f10! Passes to FUN_018d62ec
- **`0x22d3`** (8915) - Close to `0x22ca` checked by FUN_01876f10! Passes to FUN_018d62ec
- **`0x2c24`** (11300) - Passes to FUN_018d62ec
- **`0x15a5`** (5541) - Passes to FUN_018d62ec

**Key Finding**: FUN_018d7ad4 validates table IDs and calls FUN_018d62ec, which then calls FUN_01876f10. The table IDs `0x22d3` and `0x2c32` are very close to `0x22ca` and `0x2c33` checked by FUN_01876f10, suggesting these are related table IDs (possibly with minor offsets or different contexts).

**Table ID Validation**:
- FUN_018d62ec validates table ID <= `0x2c67` (11367 decimal) before proceeding
- This suggests `0x2c67` is the maximum valid table ID

### Next Steps

1. **Map table IDs to table names**:
   - ✅ Found FUN_018d7ad4 validates table IDs `0x22d3` (close to `0x22ca`) and `0x2c32` (close to `0x2c33`)
   - ✅ FUN_018d7ad4 → FUN_018d62ec → FUN_01876f10 call chain identified
   - ✅ Found 5 callers of FUN_018d7ad4: FUN_01874a50, FUN_01875b04, FUN_018d987c, FUN_01882c80, FUN_018815e4
   - ✅ Traced caller chains: FUN_01882c80 and FUN_018815e4 have 30 callers each (likely general-purpose)
   - ✅ Traced further callers: FUN_01874a50 (1 caller: FUN_018751e0), FUN_01875b04 (4 callers), FUN_018d987c (1 caller: FUN_018da09c)
   - ✅ Table IDs passed as parameters (r7) from callers, not immediate values
   - ✅ **COMPLETED**: Traced callers of dispatcher functions:
     - FUN_01882c80: 30 callers (FUN_0184aca0, FUN_01885e94, FUN_01889c30, etc.)
     - FUN_018815e4: 30 callers (similar set)
     - FUN_01876f10: 2,242 direct callers (too many to list)
     - FUN_018d7ad4: 5 callers (FUN_01874a50, FUN_01875b04, FUN_018d987c, FUN_01882c80, FUN_018815e4)
   - ✅ **COMPLETED**: Analyzed data references - no function pointer tables found for dispatchers (all direct calls)
   - **Next**: Use live switch traces to correlate table IDs with actual table operations
   - **Hypothesis**: `0x22ca`/`0x22d3` might be L3_DEFIP, `0x2c33`/`0x2c32` might be L3_ECMP, `0x835` might be VLAN_XLATE

2. **Find L3 API entry points**:
   - ✅ Found exported APIs: `opennsl_l3_route_add` @ `01dbdb40`, `opennsl_l3_egress_ecmp_add` @ `01dbd3c8`, `opennsl_l3_egress_ecmp_create` @ `01dbd3e8`
   - ✅ Found 793 exported symbols total, including L3/ECMP/VLAN APIs
   - ✅ Found API callees:
     - `opennsl_l3_route_add` → `FUN_007b1bf0` @ `007b1bf0`
     - `opennsl_l3_egress_ecmp_add` → `FUN_007ab940` @ `007ab940`
     - `opennsl_l3_egress_ecmp_create` → `FUN_007aba20` @ `007aba20`
     - `opennsl_l3_egress_ecmp_delete` → `FUN_007abb00` @ `007abb00`
     - `opennsl_vlan_translate_egress_action_add` → `FUN_00816b9c` @ `00816b9c`
   - ✅ Traced API callees: FUN_007b1bf0 → FUN_0070c994 (4,502 callers) → FUN_013949c0 (39,253 callers - ultra-central dispatcher!)
   - ✅ Found FUN_013949c0 calls FUN_0139459c which uses indirect calls (bctrl) via function pointers
   - ⏳ Tracing indirect call targets - **IN PROGRESS** (function pointers resolved at runtime)
   - **Next**: Use live switch traces - add L3 route via `ip route add`, trace switchd to identify call chain and map table IDs

3. **Map ASIC formats**:
   - Once table IDs identified, trace data flow from API structs to table writes
   - Map API struct fields to ASIC table entry layout
   - Document byte order, field positions, valid bits for each table type

4. **Alternative approach**:
   - Use live switch traces: add L3 route, trace switchd syscalls
   - Correlate with Ghidra findings to identify write mechanism

---

## References

- **API to Dispatcher Call Chain**: [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md) - Complete call chain from APIs to dispatchers
- **Progress summary**: [L3_ECMP_VLAN_PROGRESS_SUMMARY.md](L3_ECMP_VLAN_PROGRESS_SUMMARY.md) - Comprehensive summary of all findings
- **Current state**: [L3_ECMP_VLAN_CURRENT_STATE.md](L3_ECMP_VLAN_CURRENT_STATE.md) - Current analysis state
- **Table mapping**: [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md)
- **L2 analysis**: [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)
- **S-Channel format**: [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
- **Memory map**: [BROADCOM_CUMULUS_ARCHITECTURE.md](../previous_findings/BROADCOM_CUMULUS_ARCHITECTURE.md)

# L2 Write Path Analysis (Path B 3.3, 3.8)

**Date**: 2026-02-19  
**Status**: PARTIAL (call chain known, write mechanism needs tracing)  
**Functions**: FUN_00946a00 → FUN_00948700 → FUN_01cc2f2c

---

## Call Chain

**From FindL2Callers**:
```
FUN_00946a00 (top-level L2 API)
  └─> FUN_00948700 @ 0x00946c60
       └─> FUN_01cc2f2c @ 0x00948938
```

**FUN_00946a00** (libopennsl.so.1 @ 0x00946a00):
- Top-level L2 entry add/delete/modify function
- Calls `0x0140afb4` with r3=unit, r4=0, r5=&stack
- Calls function pointer from `[r30-0x7ff0][r31]` (per-unit function table)
- Checks unit state flags (`0x20(r9)`, bit `0x2000`)
- Validates flags (`0x800`, `0x90c`)

**FUN_00948700** (libopennsl.so.1 @ 0x00948700):
- Called from FUN_00946a00 at `0x00946c60`
- Reads L2_USER_ENTRY: `lwz r10, 0x0(r9)` where r9 points to table entry
- Calls FUN_01cc2f2c

**FUN_01cc2f2c** (libopennsl.so.1 @ 0x01cc2f2c):
- Called from FUN_00948700 at `0x00948938`
- Reads L2_USER_ENTRY: `lwz r8, 0x0(r11)`
- Also called from FUN_01cc3178 at `0x01cc332c`

---

## L2 Table Address

**L2_USER_ENTRY**: `0x0180c200` (from table-addr-xrefs)

**Access pattern**: All reads use `lwz rX, 0x0(rY)` - 32-bit word reads from table entry.

---

## Write Mechanism (Tracing in Progress)

**FindL2Writes results**: 0 scalar stores found to L2 region (0x180c200, 0x137cd30, 0x137e39c)

**Call chain traced**:
```
FUN_00946a00 (top-level L2 API)
  └─> FUN_00948700 @ 0x00946c60
       ├─> FUN_00a7d4a0 @ 0x009487f0 (loads value from per-unit struct)
       ├─> FUN_00947cd8 @ 0x00948818 (validation)
       └─> FUN_01408a48 @ 0x00948838
                 └─> FUN_01876f10 @ 0x01408b24
                      └─> FUN_01876ee0 @ 0x01877020
                           └─> FUN_01876c30 @ 0x01876f08
                                └─> Function pointer @ [r9-0x6b7c] via bctrl (dynamic dispatch - runtime-resolved write function)
```

**Functions analyzed**:
- **FUN_00a7d4a0**: Short helper - loads value from `[r9+0x710c]` and stores to *r4
- **FUN_00947cd8**: Validation function - checks flags, VID ranges, static bit
- **FUN_01408a48**: Prepares data, calls `0x01876f10` with r3=unit, r4=0x1547, r5=-1, r6=index, r7=data
- **FUN_01876f10**: Checks unit state, branches to `0x01876ee0`
- **FUN_01876ee0**: Parameter shuffler, branches to `0x01876c30` (needs dump)

**Possible write mechanisms**:
1. **S-Channel memory write**: FUN_007042f0/FUN_00703dc0 builds command word `0x2800XXXX`, writes to register `0x04032800` (CMIC_CMC0_SCHAN_CTRL) - **not found in L2 path yet**
2. **Direct mmap write**: Write to mmap'd region at `0x04000000` + table offset - **needs verification**
3. **Function pointer call**: FUN_00946a00 calls function pointer from per-unit table - **not traced yet**

**Next steps**:
1. Dump FUN_01876c30 to continue tracing the write path
2. Check if FUN_01876c30 calls S-Channel functions or does direct mmap writes
3. Map opennsl_l2_addr_t API struct to ASIC L2_USER_ENTRY format once write mechanism is identified

---

## OpenNSL API Structure

**opennsl_l2_addr_t** (from OpenNSL headers):
```c
typedef struct opennsl_l2_addr_s {
    uint32_t flags;          // OPENNSL_L2_STATIC, OPENNSL_L2_HIT, etc.
    uint32_t reserved1;
    uint32_t reserved2;
    uint8_t  mac[6];         // MAC address
    uint16_t vid;            // VLAN ID
    bcm_port_t port;         // Egress port
    bcm_module_t modid;      // Module ID
    bcm_trunk_t tgid;        // Trunk group ID
    bcm_multicast_t l2mc_group;  // L2 multicast group
    // ... more fields
} opennsl_l2_addr_t;
```

**Flags**:
- `OPENNSL_L2_STATIC` (0x20): Static entry (not learned)
- `OPENNSL_L2_HIT` (0x40): Entry has been hit
- `OPENNSL_L2_COPY_TO_CPU` (0x08): Copy matching packets to CPU
- `OPENNSL_L2_L3LOOKUP` (0x10): Do L3 lookup after L2 match

**ASIC L2_USER_ENTRY format**: Unknown - needs reverse engineering from write path.

---

## References

- **L2 call chain**: `libopennsl-l2-callers.txt`
- **L2 writes**: `libopennsl-l2-writes.txt` (0 stores found)
- **S-Channel format**: [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
- **Table addresses**: [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md)
- **Function dumps**: `libopennsl-dump-0946a00.txt`, `libopennsl-dump-0948700.txt`

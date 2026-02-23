# Packet Buffer Format Analysis

**Date**: 2026-02-19  
**Status**: Analyzing packet buffer structure and TX path

---

## Summary

Analyzing packet buffer structure (`opennsl_pkt_t`) and the packet TX path (`opennsl_tx` → `FUN_0080ba18`) to understand how packets are formatted and transmitted.

---

## Packet TX Path

### Call Chain
```
opennsl_tx @ 01dd11bc
└─> FUN_0080ba18 @ 0080ba18 (opennsl_tx callee)
    ├─> [Indirect call via function pointer from [-0x8000(r30)]]
    ├─> FUN_0086fe6c @ 0086fe6c (called at 0080ba94)
    ├─> FUN_01393e80 @ 01393e80 (called at 0080baa0)
    └─> FUN_0070c994 @ 0070c994 (called at 0080bad0)
        └─> [Routes to FUN_013949c0 - ultra-central dispatcher]
```

### FUN_0080ba18 Analysis

**Key Instructions**:
- `0080ba54`: `lwz r9,-0x8000(r30)` - Loads function pointer table base
- `0080ba5c`: `lwzx r9,r9,r0` - Loads function pointer (r0 = r3 << 2, r3 is unit parameter)
- `0080ba7c`: `lwz r0,-0x3c34(r9)` - Loads function pointer from structure
- `0080ba80`: `mtspr CTR,r0` - Sets CTR register
- `0080ba84`: `bctrl` - Indirect call
- `0080ba94`: `bl 0x0086fe6c` - Calls FUN_0086fe6c
- `0080baa0`: `bl 0x01393e80` - Calls FUN_01393e80
- `0080bad0`: `bl 0x0070c994` - Calls FUN_0070c994 (common wrapper)

**Structure Access**:
- `0080ba68`: `lwz r28,0x8(r9)` - Loads offset 0x8 from structure (likely packet data pointer or length)
- Function uses r3 (unit parameter) to index into function pointer table
- After indirect call, calls FUN_0086fe6c with r4=r28 (packet data?)

### FUN_0086fe6c

**Purpose**: Called after indirect call in FUN_0080ba18, receives r4=r28 (packet data pointer).

**Key Instructions**:
- `0086feac`: `lwz r28,-0x8000(r30)` - Loads function pointer table base
- `0086feb0`: `rlwinm r29,r3,0x2,0x0,0x1d` - r29 = r3 << 2 (unit parameter * 4)
- `0086feb4`: `lwzx r0,r28,r29` - Loads function pointer from table
- `0086fec0`: `lwz r9,-0x7ffc(r30)` - Loads another function pointer table
- `0086fec4`: `rlwinm r0,r4,0x2,0x0,0x1d` - r0 = r4 << 2 (packet data parameter * 4)
- `0086fec8`: `addi r5,r1,0x8` - Sets r5 to stack address
- `0086fecc`: `li r4,0xf4` - Sets r4 = 0xf4 (244 decimal)
- `0086fed0`: `lwzx r11,r9,r0` - Loads function pointer from second table
- `0086fed8`: `mtspr CTR,r11` - Sets CTR register
- `0086fedc`: `bctrl` - Indirect call
- `0086fee8`: `lwz r0,0x8(r1)` - Loads result from stack
- `0086fef4`: `lwzx r11,r28,r29` - Reloads function pointer
- `0086fef8`: `addis r11,r11,0xa3` - Adds offset 0xa30000
- `0086fefc`: `lwz r0,0x7114(r11)` - Loads from structure at offset 0x7114
- `0086ff30`: `lwz r0,0xc(r27)` - Loads function pointer from offset 0xc
- `0086ff40`: `mtspr CTR,r0` + `bctrl` - Second indirect call

**Analysis**: FUN_0086fe6c uses two function pointer tables and performs two indirect calls. It appears to process packet data and then call another function based on the result.

### FUN_01393e80

**Purpose**: Called before FUN_0070c994, likely error handling or validation.

**Key Instructions**:
- `01393ea4`: `lwz r9,-0x8000(r30)` - Loads function pointer table base
- `01393ea8`: `lwz r9,0x4(r9)` - Loads function pointer from offset 0x4
- `01393eb4`: `mtspr CTR,r9` + `bctrl` - Indirect call if pointer is non-zero
- Returns r3 = result from indirect call (or 0 if pointer was null)

**Analysis**: FUN_01393e80 is a simple wrapper that calls a function pointer from offset 0x4 of the function pointer table. It's used for error checking/validation before calling FUN_0070c994.

---

## Packet Buffer Structure (opennsl_pkt_t)

### Structure Layout (from OpenNSL `hal/include/opennsl/pkt.h`)

```c
struct opennsl_pkt_blk_s {
    uint8 *data;    // Pointer to packet data
    int len;        // Length of block
};

struct opennsl_pkt_s {
    opennsl_pkt_blk_t *pkt_data;  // Offset 0:  Pointer to array of data blocks
    uint8 blk_count;              // 4:         Number of blocks
    uint8 unit;                   // 5:         Unit number
    uint8 cos;                    // 6:         COS queue
    uint8 reserved1;
    opennsl_vlan_t vlan;          // 8:         VID/VSI/VPN
    // ... reserved fields ...
    int16 src_port;               // Source port in header
    uint16 dest_port;             // Destination port in header
    uint16 pkt_len;               // Packet length (flags)
    uint16 tot_len;               // Length as transmitted/received
    opennsl_pbmp_t tx_pbmp;       // Target ports
    opennsl_pbmp_t tx_upbmp;      // Untagged target ports
    uint32 rx_reason;             // Opcode from packet
    uint8 rx_port;                // Local rx port
    // ... more ...
    opennsl_pkt_cb_f call_back;   // Callback function
    uint32 flags;                 // OPENNSL_PKT_F_xxx
    opennsl_pkt_blk_t _pkt_data;  // For single-block packets (internal)
    // ... reserved48, _vtag, etc.
};
```

**Packet layout** (from pkt.h comments): DMAC+SMAC (12) + VLAN tag (4) + payload (N) + CRC (4) + pad (M) + SL tag (4) + HiGig (12). `alloc_len = 12+4+N+4+M+4+12`.

**Single-block macro**: `OPENNSL_PKT_BLOCK_SET(pkt, buf, len)` sets `_pkt_data.data`, `_pkt_data.len`, and `pkt_data = &_pkt_data`.

### Access Patterns

From FUN_0080ba18:
- **Offset 0x8**: Loaded into r28, passed to FUN_0086fe6c — likely `pkt_data` or related handle.

### Trace Data

From previous traces:
- Packet lengths observed: 42, 60, 82, 122 bytes
- These match Ethernet frame sizes (ARP, min IP, ICMP+payload, larger)

---

## Function Pointer Dispatch

### Pattern in FUN_0080ba18

1. **Function pointer table base**: Loaded from `[-0x8000(r30)]`
2. **Index calculation**: `r0 = r3 << 2` (unit parameter * 4)
3. **Function pointer load**: `lwzx r9,r9,r0` (loads pointer from table)
4. **Structure access**: `lwz r28,0x8(r9)` (loads packet data from structure)
5. **Function pointer from structure**: `lwz r0,-0x3c34(r9)` (loads function pointer)
6. **Indirect call**: `mtspr CTR,r0` + `bctrl`

This pattern suggests:
- Unit parameter selects a function pointer table entry
- Each entry points to a structure containing:
  - Function pointer at offset `-0x3c34` (or `0x3c34` before base)
  - Packet data pointer at offset `0x8`

---

## Connection to Central Dispatcher

### FUN_0070c994 Call

FUN_0080ba18 calls FUN_0070c994 at `0080bad0`:
- **Parameters**: r3=0x3014805 (error code?), r5=0x3, r6=0x1, r7=r29 (unit), r10=r31 (return value)
- FUN_0070c994 is the common wrapper (4,502 callers)
- Routes to FUN_013949c0 (ultra-central dispatcher, 39,253 callers)

This connects the packet TX path to the central dispatcher system.

---

## Next Steps

1. **Analyze FUN_0086fe6c**: Understand packet data processing
2. **Analyze FUN_01393e80**: Understand error handling/validation
3. **Dump more packet-related functions**: Find packet allocation/free functions
4. **Runtime analysis**: Trace actual packet buffer contents
5. **Structure definition**: Map complete `opennsl_pkt_t` structure

---

## References

- [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md) - Previous function analysis
- [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md) - Central dispatcher analysis
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) - Overall project status

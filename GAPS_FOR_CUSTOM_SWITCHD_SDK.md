# Gaps for Writing Custom switchd/SDK

**Date**: 2026-02-18  
**Purpose**: Identify what's missing to implement a custom switchd and SDK interface for BCM56846 ASIC  
**Status**: Based on current reverse engineering work

---

## Executive Summary

You have **excellent coverage** of:
- ✅ High-level architecture (netlink → SDK mapping)
- ✅ API patterns (2,864 `bcm_*` APIs identified)
- ✅ Configuration formats (.bcm, rc.soc)
- ✅ Initialization sequences
- ✅ Register access patterns (from Ghidra)
- ✅ Packet I/O mechanism (TUN + BDE)

**Critical gaps** remain in:
- ❌ **Low-level register map** (complete register definitions)
- ❌ **Table structures** (exact field layouts for L2/L3/FIB/TCAM)
- ❌ **Packet TX/RX APIs** (exact SDK functions for TUN → ASIC)
- ❌ **DMA/ring buffer details** (packet buffer management)
- ❌ **Error handling** (error codes, recovery procedures)
- ❌ **Performance optimization** (buffer sizing, interrupt tuning)

---

## 1. Register Map (Critical)

### What You Have
- ✅ Register access patterns (`setreg`, `getreg`, `soc_reg`)
- ✅ CMIC register definitions from OpenNSL source (76 registers extracted)
- ✅ Register offset patterns (0x31xxx-0x35xxx ranges)
- ✅ S-Channel register offsets (CMIC_CMC0_SCHAN_CTRL = 0x32800)
- ✅ LED register definitions
- ✅ CMIC CMC register macros (IRQ_STAT, IRQ_MASK, PCIE_IRQ_MASK, UC0_IRQ_MASK)
- ✅ Ghidra found register-like constants from switchd binary
- ✅ **See [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) for complete register map**

### What's Missing
- ❌ **Complete register map** for BCM56846
  - All CMIC registers (0x31000-0x35000 range)
  - Port registers (per-port configuration)
  - L2 table registers (ARL, VLAN)
  - L3 table registers (FIB, host entries)
  - Ingress/egress pipeline registers
  - Buffer management registers
  - Statistics counter registers

- ❌ **Register field definitions**
  - Bit fields within each register
  - Field names and purposes
  - Read/write permissions
  - Reset values

- ❌ **Register access patterns**
  - Which registers require S-Channel vs direct access
  - Register locking requirements
  - Atomicity requirements

### Impact
**HIGH** - Without a complete register map, you cannot:
- Program tables directly (must rely on SDK APIs)
- Debug hardware issues
- Optimize performance
- Implement custom features

### Possible Sources
- Broadcom SDK documentation (proprietary)
- OpenNSL source code (partial, may have register definitions)
- Hardware register dumps (capture all registers during init)
- Ghidra analysis (extract more register constants, find register access functions)

---

## 2. Table Structures (Critical)

### What You Have
- ✅ Table management strings (L2, L3, ARL, MMU, VLAN tables)
- ✅ Table size tracking (current/maximum counts)
- ✅ API patterns (`bcm_l2_addr_add`, `bcm_l3_route_add`)
- ✅ Hash table operations (`hash_table_add`, `hash_table_find`)

### What's Missing
- ❌ **L2 table entry layout**
  - MAC address field (48 bits)
  - VLAN ID field (12 bits)
  - Port/trunk field
  - Hit bit location
  - Age/static flags
  - Entry size and alignment

- ❌ **L3 route table layout**
  - Destination IP + mask fields
  - Egress interface ID
  - Next-hop MAC (or pointer)
  - ECMP group ID (if multipath)
  - Entry size and alignment

- ❌ **L3 host table layout**
  - Host IP address
  - Egress interface
  - Next-hop MAC
  - Entry size

- ❌ **TCAM/ACL table layout**
  - Field processor (FP) entry format
  - Match/mask fields
  - Action fields
  - Priority encoding

- ❌ **VLAN table layout**
  - VLAN ID
  - Port membership bitmap
  - Untagged port bitmap
  - STP state per port

- ❌ **Table base addresses**
  - Where tables are located in ASIC memory
  - Table size limits
  - Table indexing scheme

### Impact
**HIGH** - Without table structures, you cannot:
- Program tables directly (must use SDK APIs)
- Debug table programming issues
- Understand table capacity limits
- Implement custom table management

### Possible Sources
- SDK header files (if available)
- OpenNSL source (may have structure definitions)
- Ghidra analysis (find table access functions, extract structures)
- Runtime dumps (capture table entries, reverse-engineer layout)

---

## 3. Packet TX/RX APIs (Critical)

### What You Have
- ✅ Packet I/O mechanism (TUN devices)
- ✅ Flow understanding (TUN → SDK → BDE → ASIC)
- ✅ Some SDK RX APIs (`bcm_rx_*` functions identified)

### What's Missing
- ❌ **Exact packet TX API**
  - Function name (`bcm_pkt_tx`, `bcm_tx`, or other?)
  - Parameters (port, buffer, length, flags)
  - Return codes
  - Buffer ownership (who frees?)

- ❌ **Exact packet RX API**
  - How to register RX callback
  - How to receive packets (poll vs interrupt)
  - Packet buffer format
  - Metadata (port, VLAN, etc.)

- ❌ **Packet buffer management**
  - Buffer allocation (DMA pool?)
  - Buffer size requirements
  - Buffer alignment requirements
  - Buffer lifetime management

- ❌ **Port-to-TUN mapping**
  - How SDK knows which TUN fd for which port
  - Port index vs BCM port number mapping
  - Breakout port handling (swp49s0-3)

### Impact
**HIGH** - Without packet APIs, you cannot:
- Send packets from CPU to ports
- Receive packets from ports to CPU
- Implement control plane packet handling

### Possible Sources
- SDK documentation (if available)
- OpenNSL source (`opennsl_pkt_*` functions)
- Ghidra analysis (find packet TX/RX functions in switchd)
- Dynamic tracing (strace switchd during packet I/O)

---

## 4. DMA and Ring Buffer Details (High Priority)

### What You Have
- ✅ DMA pool understanding (BDE allocates DMA memory)
- ✅ Ring buffer registers (DMA_DESC0, DMA_HALT_ADDR)
- ✅ S-Channel understanding (control path)

### What's Missing
- ❌ **DMA descriptor format**
  - Descriptor Control Block (DCB) layout
  - Packet buffer pointer format
  - Metadata fields
  - Descriptor ring size

- ❌ **DMA channel assignment**
  - Which channels for TX vs RX
  - How many channels available
  - Channel priority/interrupt assignment

- ❌ **Packet buffer format**
  - Buffer header (if any)
  - Packet data layout
  - Metadata location
  - Buffer alignment requirements

- ❌ **DMA interrupt handling**
  - Interrupt vectors
  - Interrupt status registers
  - Interrupt clearing procedure

### Impact
**MEDIUM-HIGH** - Needed for:
- High-performance packet I/O
- Understanding packet flow
- Debugging packet drops

### Possible Sources
- OpenNSL KNET source (has DCB definitions)
- BDE source code (if available)
- Ghidra analysis (find DMA setup functions)

---

## 5. Error Handling and Diagnostics (Medium Priority)

### What You Have
- ✅ Some error strings from Ghidra ("Adding arp dst to hash table failed", etc.)
- ✅ Basic understanding of initialization failures

### What's Missing
- ❌ **SDK error codes**
  - Complete list of return codes
  - Error code meanings
  - Error recovery procedures

- ❌ **Hardware error detection**
  - Parity errors
  - Table overflow conditions
  - Port link failures
  - DMA errors

- ❌ **Diagnostic APIs**
  - Register dump functions
  - Table dump functions
  - Statistics collection
  - Health monitoring

### Impact
**MEDIUM** - Needed for:
- Robust error handling
- Debugging production issues
- Monitoring system health

### Possible Sources
- SDK documentation
- OpenNSL error codes
- Ghidra analysis (find error handling code)

---

## 6. Performance Optimization (Medium Priority)

### What You Have
- ✅ Buffer pool configuration (datapath.conf)
- ✅ Priority groups (control, service, lossless, bulk)
- ✅ Coalescing configuration

### What's Missing
- ❌ **Optimal buffer sizing**
  - How to size DMA pools
  - Buffer cell size calculations
  - Memory pressure handling

- ❌ **Interrupt tuning**
  - IRQ coalescing settings
  - Poll vs interrupt thresholds
  - CPU affinity for interrupts

- ❌ **Table sizing**
  - Optimal L2 table size
  - Optimal L3 table size
  - Table memory allocation

- ❌ **Pipeline optimization**
  - Ingress/egress buffer allocation
  - Queue depth tuning
  - Flow control settings

### Impact
**MEDIUM** - Needed for:
- Production performance
- Handling high traffic loads
- Avoiding packet drops

---

## 7. SerDes and PHY Configuration (Medium Priority)

### What You Have
- ✅ Port mapping (SerDes lane → BCM port)
- ✅ Port speed configuration (10G/40G)
- ✅ Some PHY parameters (mdio_*, serdes_*)

### What's Missing
- ❌ **SerDes lane configuration**
  - Lane enable/disable
  - Lane speed configuration
  - Lane training parameters

- ❌ **PHY initialization**
  - PHY firmware loading
  - PHY register programming
  - Autoneg configuration (disabled in Cumulus)

- ❌ **Link state detection**
  - How link status is read
  - Link state change interrupts
  - Link state polling

- ❌ **QSFP/breakout configuration**
  - How 40G → 4×10G breakout works
  - Lane remapping for breakout
  - Port numbering for breakout ports

### Impact
**MEDIUM** - Needed for:
- Port bringup
- Link state monitoring
- Breakout port support

---

## 8. Statistics and Counters (Low-Medium Priority)

### What You Have
- ✅ Some counter register names (`rdbgc*_select`, `tdbgc*_select`)
- ✅ Counter DMA configuration (`bcm_stat_flags`)

### What's Missing
- ❌ **Complete counter list**
  - All available counters
  - Counter register addresses
  - Counter formats (32-bit vs 64-bit)

- ❌ **Counter collection**
  - How to read counters
  - Counter DMA format
  - Counter overflow handling

- ❌ **Performance counters**
  - Per-port counters
  - Per-VLAN counters
  - Per-queue counters

### Impact
**LOW-MEDIUM** - Needed for:
- Network monitoring
- Performance analysis
- Troubleshooting

---

## 9. Advanced Features (Low Priority)

### What's Missing
- ❌ **ACL/TCAM programming**
  - Field processor entry format
  - Match/mask programming
  - Action programming

- ❌ **QoS/CoS configuration**
  - Priority mapping
  - Queue scheduling
  - Rate limiting

- ❌ **Trunk/LAG configuration**
  - Trunk group creation
  - Member port assignment
  - Load balancing

- ❌ **Mirroring**
  - Port mirroring configuration
  - Mirror destination setup

- ❌ **Tunneling**
  - VXLAN support
  - GRE support

### Impact
**LOW** - Needed only for advanced features

---

## 10. Practical Implementation Path

### Option A: Use OpenNSL (Recommended)
**Pros:**
- Open-source SDK with APIs
- Well-documented
- Active community

**Cons:**
- Uses KNET by default (you need TUN)
- API names differ (`opennsl_*` vs `bcm_*`)
- May need modifications for TUN support

**What You Need:**
- Adapt OpenNSL for TUN instead of KNET
- Map OpenNSL APIs to your netlink handlers
- Test on hardware

### Option B: Build Minimal SDK Wrapper
**Pros:**
- Full control
- Matches Cumulus behavior exactly

**Cons:**
- Requires complete register map
- Requires table structure knowledge
- Much more work

**What You Need:**
- Complete register map (from SDK docs or reverse engineering)
- Table structure definitions
- Packet TX/RX implementation
- Extensive testing

### Option C: Hybrid Approach
**Pros:**
- Use OpenNSL for most operations
- Custom code for TUN packet I/O
- Best of both worlds

**Cons:**
- Integration complexity
- Need to bridge OpenNSL and TUN

**What You Need:**
- OpenNSL integration
- Custom TUN packet handler
- BDE access for packet I/O

---

## Recommendations

### Immediate Priorities

1. **Packet TX/RX APIs** (Critical)
   - Use Ghidra to find packet TX/RX functions in switchd
   - Trace switchd during packet I/O to see exact API calls
   - Document function signatures and usage

2. **Table Structures** (Critical)
   - Use Ghidra to find table access functions
   - Extract structure definitions from switchd binary
   - Dump tables at runtime to reverse-engineer layout

3. **Register Map** (High Priority)
   - Extract more register constants from Ghidra analysis
   - Use OpenNSL source as reference (may have register definitions)
   - Capture register dumps during initialization

4. **OpenNSL Evaluation** (High Priority)
   - Test OpenNSL on hardware
   - Evaluate TUN support options
   - Determine if OpenNSL can be adapted

### Next Steps

1. **Enhance Ghidra Analysis**
   - Extract packet TX/RX function signatures
   - Find table structure definitions
   - Extract more register constants

2. **Dynamic Analysis**
   - Trace packet I/O to identify exact APIs
   - Dump tables to reverse-engineer structures
   - Capture register accesses during operations

3. **OpenNSL Integration**
   - Test OpenNSL on AS5610-52X
   - Evaluate TUN packet I/O options
   - Document integration approach

---

## Related Documents

- [REVERSE_ENGINEERING_STATUS_REPORT.md](REVERSE_ENGINEERING_STATUS_REPORT.md) - Comprehensive status report of all documents and coverage
- [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md) - Complete checklist
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Register/table patterns found
- [sdk-api-list.md](sdk-api-list.md) - 2,864 API symbols
- [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md) - TUN mechanism
- [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md) - Register/DMA basics
- [netlink-handlers.md](netlink-handlers.md) - Netlink → SDK mapping

---

## Conclusion

You have **excellent high-level understanding** but need **low-level implementation details**:

**Critical Gaps:**
1. Complete register map
2. Table structure definitions  
3. Packet TX/RX API details

**Recommended Path:**
- **Short term**: Use OpenNSL with TUN adaptation
- **Long term**: Build custom SDK as you reverse-engineer more details

The foundation is solid - you understand the architecture, APIs, and flow. The remaining work is filling in the low-level details needed for implementation.

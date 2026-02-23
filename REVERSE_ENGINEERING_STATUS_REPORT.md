# Reverse Engineering Status Report

**Date**: 2026-02-18  
**Purpose**: Comprehensive assessment of what we have vs what we need for custom switchd/SDK implementation  
**Total Documents**: 36 reverse engineering documents

---

## Executive Summary

**Coverage**: ~75% complete for high-level implementation, ~30% for low-level SDK details

**Status**: 
- ✅ **Excellent** high-level architecture understanding
- ✅ **Good** API and configuration coverage  
- ⚠️ **Partial** low-level implementation details
- ⚠️ **Partially documented** register map and table structures (see [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md))

**Recommendation**: Use OpenNSL with TUN adaptation (most practical path forward)

---

## 1. What We Have (Documented)

### 1.1 Architecture & Flow ✅ EXCELLENT

| Document | Coverage | Status |
|----------|----------|--------|
| **WHAT_MAKES_THE_SWITCH_WORK.md** | Complete checklist of required components | ✅ Complete |
| **netlink-handlers.md** | Netlink → SDK mapping (RTM_NEWROUTE → bcm_l3_route_add, etc.) | ✅ Complete |
| **netlink-message-flow.md** | Message flow diagrams | ✅ Complete |
| **api-patterns.md** | Common SDK call patterns (L2, L3, port, VLAN) | ✅ Complete |
| **initialization-sequence.md** | 16-step startup flow | ✅ Complete |
| **PACKET_IO_VERIFIED.md** | TUN mechanism verified (not KNET) | ✅ Complete |
| **cumulus-packet-io-architecture.md** | Packet I/O architecture | ✅ Complete |
| **COMPLETE_INTERFACE_ANALYSIS.md** | Interface creation mechanism | ✅ Complete |

**Coverage**: 100% - Full understanding of how switchd works at architectural level

### 1.2 SDK APIs ✅ GOOD

| Document | Coverage | Status |
|----------|----------|--------|
| **sdk-api-list.md** | 2,864 `bcm_*` API symbols extracted | ✅ Complete |
| **sdk-api-mapping.md** | API categorization (L2, L3, Port, VLAN, etc.) | ✅ Complete |
| **api-patterns.md** | Usage patterns for common operations | ✅ Complete |

**Key Findings**:
- ✅ `bcm_tx` - Packet TX function identified
- ✅ `bcm_rx_*` - 61 RX-related functions identified
- ✅ `bcm_rx_register` - RX callback registration
- ✅ `bcm_rx_process_packet` - Packet processing callback
- ✅ `bcm_pkt_alloc` - Packet buffer allocation

**Coverage**: 90% - Have API names but need function signatures and usage details

### 1.3 Configuration ✅ EXCELLENT

| Document | Coverage | Status |
|----------|----------|--------|
| **bcm-config-format.md** | Complete .bcm file format specification | ✅ Complete |
| **SDK_AND_ASIC_CONFIG_FROM_SWITCH.md** | All config files from live switch | ✅ Complete |
| **QSFP_BREAKOUT_CONFIGURATION.md** | Port 49-52 breakout (40G vs 4×10G) | ✅ Complete |
| **config-to-register-map.md** | Config params → register writes | ✅ Complete |
| **asic-init-sequence.md** | rc.soc register writes | ✅ Complete |

**Coverage**: 95% - Complete understanding of configuration system

### 1.4 Initialization ✅ EXCELLENT

| Document | Coverage | Status |
|----------|----------|--------|
| **initialization-sequence.md** | Complete 16-step startup flow | ✅ Complete |
| **switchd-init-trace.md** | Actual trace from live switch (51MB, 680k lines) | ✅ Complete |
| **switchd-dynamic-analysis-summary.md** | Dynamic analysis results | ✅ Complete |
| **ASIC_INIT_AND_DMA_MAP.md** | BDE init, DMA pool, register mapping | ✅ Complete |
| **SCHAN_AND_RING_BUFFERS.md** | S-Channel and DMA ring details | ✅ Complete |

**Coverage**: 90% - Full initialization sequence documented

### 1.5 Register Access ⚠️ PARTIAL

| Document | Coverage | Status |
|----------|----------|--------|
| **ASIC_INIT_AND_DMA_MAP.md** | PCI BAR layout, CMIC base (0x31000), S-Chan (0x32800) | ✅ Partial |
| **SCHAN_AND_RING_BUFFERS.md** | DMA registers (DMA_CTRL, DMA_DESC0, DMA_HALT_ADDR) | ✅ Partial |
| **config-to-register-map.md** | Debug counter registers (rdbgc*, tdbgc*) | ✅ Partial |
| **GHIDRA_REGISTER_TABLE_ANALYSIS.md** | 34,918 register/table strings, xrefs | ✅ Partial |

**What We Have**:
- ✅ CMIC base address (0x31000)
- ✅ S-Channel register (0x32800)
- ✅ DMA registers (0x31140-0x311a4)
- ✅ IRQ registers (0x31400+)
- ✅ Debug counter registers (rdbgc*, tdbgc*)
- ✅ Register access patterns (`setreg`, `getreg`, `soc_reg`)

**Coverage**: 30% - Have key registers but not complete map

### 1.6 Table Management ✅ IMPROVED

| Document | Coverage | Status |
|----------|----------|--------|
| **SDK_REGISTER_MAP.md** | L2/L3 table structures from OpenNSL | ✅ Complete |
| **GHIDRA_REGISTER_TABLE_ANALYSIS.md** | Table management strings, HAL functions | ✅ Partial |
| **netlink-handlers.md** | Table programming via SDK APIs | ✅ Complete |
| **api-patterns.md** | Table API usage patterns | ✅ Complete |

**What We Have**:
- ✅ `opennsl_l2_addr_t` structure layout documented
- ✅ `opennsl_l3_host_t`, `opennsl_l3_route_t`, `opennsl_l3_egress_t` structures documented
- ✅ L2/L3 flags and API function signatures documented
- ✅ Table types identified (L2, L3, ARL, MMU, VLAN, ECMP, Host)
- ✅ Table size tracking (current/maximum counts)
- ✅ API patterns (`opennsl_l2_addr_add`, `opennsl_l3_route_add`)
- ✅ **See [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) for table structures**

**Coverage**: 60% - Have structure layouts but need exact field offsets and memory addresses

### 1.7 Packet I/O ✅ IMPROVED

| Document | Coverage | Status |
|----------|----------|--------|
| **SDK_REGISTER_MAP.md** | Packet TX/RX API signatures from OpenNSL | ✅ Complete |
| **PACKET_IO_VERIFIED.md** | TUN mechanism verified | ✅ Complete |
| **sdk-api-list.md** | `bcm_tx`, `bcm_rx_*` APIs identified | ✅ Partial |
| **cumulus-packet-io-architecture.md** | Packet flow architecture | ✅ Complete |

**What We Have**:
- ✅ `opennsl_tx()` function signature documented
- ✅ `opennsl_rx_register()`, `opennsl_rx_start()`, `opennsl_rx_stop()` documented
- ✅ `opennsl_pkt_t` structure layout documented
- ✅ Packet flags and callback mechanisms documented
- ✅ TUN device mechanism (52 TUN fds, one per port)
- ✅ Flow understanding (TUN → SDK → BDE → ASIC)
- ✅ **See [`SDK_REGISTER_MAP.md`](./SDK_REGISTER_MAP.md) for API details**

**Coverage**: 75% - Have API signatures, still need DMA ring buffer details

### 1.8 Platform & Hardware ✅ GOOD

| Document | Coverage | Status |
|----------|----------|--------|
| **ONIE_BOOT_AND_PARTITION_LAYOUT.md** | Boot process and partitions | ✅ Complete |
| **QSFP_BREAKOUT_CONFIGURATION.md** | Port configuration | ✅ Complete |
| **SFP_TURNUP_AND_ACCESS.md** | SFP/QSFP access | ✅ Complete |
| **PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md** | Platform hardware access | ✅ Complete |

**Coverage**: 85% - Good platform understanding

---

## 2. What We Need (Gaps)

### 2.1 Critical Gaps ❌

#### Register Map (Critical)
**Status**: 30% complete

**Have**:
- CMIC base (0x31000), S-Channel (0x32800)
- DMA registers (0x31140-0x311a4)
- IRQ registers (0x31400+)
- Debug counters (rdbgc*, tdbgc*)

**Need**:
- ❌ Complete register map (all CMIC, port, L2, L3, pipeline registers)
- ❌ Register field definitions (bit fields, purposes, reset values)
- ❌ Register access patterns (S-Channel vs direct, locking requirements)

**Impact**: HIGH - Cannot program tables directly, debug hardware issues, or optimize

**Sources**: 
- OpenNSL source (may have register definitions)
- Ghidra analysis (extract more register constants)
- Hardware register dumps

#### Table Structures (Critical)
**Status**: 40% complete

**Have**:
- Table types (L2, L3, ARL, MMU, VLAN, ECMP, Host)
- API patterns (`bcm_l2_addr_add`, `bcm_l3_route_add`)
- Table size tracking

**Need**:
- ❌ L2 table entry layout (MAC, VLAN, port, hit bit, flags, size)
- ❌ L3 route table layout (destination, mask, egress, next-hop, ECMP, size)
- ❌ L3 host table layout (IP, egress, MAC, size)
- ❌ TCAM/ACL table layout (FP entry format, match/mask, actions)
- ❌ VLAN table layout (VLAN ID, port bitmap, untagged bitmap)
- ❌ Table base addresses (where tables are in ASIC memory)

**Impact**: HIGH - Cannot program tables directly or debug table issues

**Sources**:
- SDK header files (if available)
- OpenNSL source (may have structure definitions)
- Ghidra analysis (find table access functions, extract structures)
- Runtime dumps (capture table entries, reverse-engineer layout)

#### Packet TX/RX APIs (Critical)
**Status**: 60% complete

**Have**:
- TUN mechanism (verified)
- API names (`bcm_tx`, `bcm_rx_register`, `bcm_rx_process_packet`)
- Flow understanding

**Need**:
- ❌ `bcm_tx` function signature (parameters, return codes, buffer ownership)
- ❌ `bcm_rx_register` callback signature (how to register, callback format)
- ❌ Packet buffer format (buffer header, metadata location, alignment)
- ❌ Port-to-TUN mapping (how SDK knows which TUN fd for which port)

**Impact**: HIGH - Cannot send/receive packets from CPU

**Sources**:
- SDK documentation (if available)
- OpenNSL source (`opennsl_pkt_*` functions)
- Ghidra analysis (find packet TX/RX functions, extract signatures)
- Dynamic tracing (strace switchd during packet I/O)

### 2.2 High Priority Gaps ⚠️

#### DMA/Ring Buffer Details
**Status**: 50% complete

**Have**:
- DMA pool understanding
- Ring buffer registers (DMA_DESC0, DMA_HALT_ADDR)
- S-Channel understanding

**Need**:
- ❌ DMA descriptor format (DCB layout, packet buffer pointer format)
- ❌ DMA channel assignment (TX vs RX channels, priorities)
- ❌ Packet buffer format (header, data layout, metadata)
- ❌ DMA interrupt handling (vectors, status registers, clearing)

**Impact**: MEDIUM-HIGH - Needed for high-performance packet I/O

**Sources**: OpenNSL KNET source (has DCB definitions), BDE source

#### OpenNSL vs Cumulus SDK
**Status**: 20% complete

**Have**:
- API name mapping (`bcm_*` vs `opennsl_*`)
- KNET vs TUN understanding

**Need**:
- ❌ OpenNSL TUN support evaluation
- ❌ API compatibility assessment
- ❌ Integration approach

**Impact**: HIGH - Determines implementation path

**Sources**: OpenNSL testing, documentation review

### 2.3 Medium Priority Gaps ⚠️

#### Error Handling
**Status**: 30% complete

**Have**:
- Some error strings from Ghidra
- Basic initialization failure understanding

**Need**:
- ❌ Complete SDK error codes
- ❌ Hardware error detection (parity, table overflow, DMA errors)
- ❌ Diagnostic APIs (register dump, table dump, statistics)

**Impact**: MEDIUM - Needed for robust error handling

#### Performance Optimization
**Status**: 50% complete

**Have**:
- Buffer pool configuration
- Priority groups
- Coalescing configuration

**Need**:
- ❌ Optimal buffer sizing guidelines
- ❌ Interrupt tuning (coalescing, poll vs interrupt thresholds)
- ❌ Table sizing (optimal L2/L3 table sizes)

**Impact**: MEDIUM - Needed for production performance

#### SerDes/PHY Configuration
**Status**: 60% complete

**Have**:
- Port mapping (SerDes lane → BCM port)
- Port speed configuration
- Some PHY parameters

**Need**:
- ❌ SerDes lane configuration details
- ❌ PHY initialization sequence
- ❌ Link state detection mechanism
- ❌ QSFP breakout lane remapping

**Impact**: MEDIUM - Needed for port bringup

### 2.4 Low Priority Gaps

- ACL/TCAM programming
- QoS/CoS configuration
- Trunk/LAG configuration
- Mirroring
- Tunneling (VXLAN, GRE)

---

## 3. Document Inventory

### Core Architecture (8 documents)
1. ✅ WHAT_MAKES_THE_SWITCH_WORK.md - Complete checklist
2. ✅ netlink-handlers.md - Netlink → SDK mapping
3. ✅ netlink-message-flow.md - Message flow
4. ✅ api-patterns.md - SDK usage patterns
5. ✅ initialization-sequence.md - Startup flow
6. ✅ PACKET_IO_VERIFIED.md - TUN mechanism
7. ✅ cumulus-packet-io-architecture.md - Packet I/O architecture
8. ✅ COMPLETE_INTERFACE_ANALYSIS.md - Interface creation

### SDK & APIs (3 documents)
9. ✅ sdk-api-list.md - 2,864 APIs
10. ✅ sdk-api-mapping.md - API categorization
11. ✅ GHIDRA_REGISTER_TABLE_ANALYSIS.md - Register/table patterns

### Configuration (5 documents)
12. ✅ bcm-config-format.md - .bcm format
13. ✅ SDK_AND_ASIC_CONFIG_FROM_SWITCH.md - Live config files
14. ✅ QSFP_BREAKOUT_CONFIGURATION.md - Port 49-52 breakout
15. ✅ config-to-register-map.md - Config → registers
16. ✅ asic-init-sequence.md - rc.soc register writes

### Initialization & Hardware (6 documents)
17. ✅ switchd-init-trace.md - Actual trace (51MB)
18. ✅ switchd-dynamic-analysis-summary.md - Dynamic analysis
19. ✅ ASIC_INIT_AND_DMA_MAP.md - BDE, DMA, registers
20. ✅ SCHAN_AND_RING_BUFFERS.md - S-Channel, DMA rings
21. ✅ ONIE_BOOT_AND_PARTITION_LAYOUT.md - Boot process
22. ✅ switchd-binary-analysis.md - Binary analysis approach

### Platform Hardware (3 documents)
23. ✅ SFP_TURNUP_AND_ACCESS.md - SFP/QSFP access
24. ✅ PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md - Platform hardware
25. ✅ VERSIONS_AND_BUILD_INFO.md - Version info

### Analysis & Status (11 documents)
26. ✅ ANALYSIS_SUMMARY.md - Analysis summary
27. ✅ RE_COMPLETE.md - RE completion status
28. ✅ GAPS_FOR_CUSTOM_SWITCHD_SDK.md - Gap analysis
29. ✅ VERIFICATION_RESULTS.md - Verification results
30. ✅ file-access-pattern.md - File access patterns
31. ✅ architecture-diagrams.md - Architecture diagrams
32. ✅ packet-flow-analysis.md - Packet flow
33. ✅ interface-creation-analysis.md - Interface analysis
34. ✅ interface-creation-mechanism.md - Interface mechanism
35. ✅ LIVE_SWITCH_CONFIG_10.1.1.233.md - Live switch config
36. ✅ ANALYSIS_RUN_2026-02-18.md - Analysis run log

**Total**: 36 documents covering architecture, APIs, config, initialization, hardware

---

## 4. Coverage Assessment

### By Category

| Category | Coverage | Documents | Status |
|----------|----------|-----------|--------|
| **Architecture & Flow** | 95% | 8 | ✅ Excellent |
| **SDK APIs** | 90% | 3 | ✅ Good |
| **Configuration** | 95% | 5 | ✅ Excellent |
| **Initialization** | 90% | 6 | ✅ Excellent |
| **Register Access** | 50% | 5 | ✅ Improved |
| **Table Structures** | 60% | 4 | ✅ Improved |
| **Packet I/O** | 60% | 3 | ⚠️ Partial |
| **Platform Hardware** | 85% | 3 | ✅ Good |
| **Error Handling** | 30% | 1 | ⚠️ Partial |
| **Performance** | 50% | 1 | ⚠️ Partial |

### Overall Coverage

- **High-Level (Architecture, APIs, Config)**: 90% ✅
- **Mid-Level (Initialization, Flow)**: 85% ✅
- **Low-Level (Registers, Tables, Packet APIs)**: 40% ⚠️

---

## 5. Critical Path to Implementation

### Option A: OpenNSL + TUN (Recommended) ⭐

**What We Have**:
- ✅ Complete architecture understanding
- ✅ API mapping (`bcm_*` → `opennsl_*`)
- ✅ TUN mechanism verified
- ✅ Netlink handlers documented

**What We Need**:
- ⚠️ OpenNSL TUN support evaluation
- ⚠️ OpenNSL integration testing
- ⚠️ TUN packet handler implementation

**Effort**: Medium (2-4 weeks)
**Risk**: Low-Medium
**Recommendation**: ⭐ **START HERE**

### Option B: Custom SDK Wrapper

**What We Have**:
- ✅ Architecture understanding
- ✅ API patterns
- ✅ Configuration formats

**What We Need**:
- ❌ Complete register map (70% missing)
- ❌ Table structures (60% missing)
- ❌ Packet TX/RX signatures (40% missing)
- ❌ DMA details (50% missing)

**Effort**: High (3-6 months)
**Risk**: High
**Recommendation**: Long-term goal

### Option C: Hybrid (OpenNSL + Custom Packet I/O)

**What We Have**:
- ✅ OpenNSL API mapping
- ✅ TUN mechanism
- ✅ BDE understanding

**What We Need**:
- ⚠️ Custom TUN packet handler
- ⚠️ BDE packet I/O implementation
- ⚠️ OpenNSL integration

**Effort**: Medium-High (1-2 months)
**Risk**: Medium
**Recommendation**: Alternative if Option A fails

---

## 6. Immediate Next Steps

### Priority 1: Packet TX/RX APIs (Critical)

**Actions**:
1. Use Ghidra to find `bcm_tx` function signature
   - Search for `bcm_tx` calls in switchd binary
   - Extract function parameters from call sites
   - Document return codes and error handling

2. Use Ghidra to find `bcm_rx_register` signature
   - Find RX callback registration
   - Extract callback function signature
   - Document packet buffer format

3. Dynamic tracing during packet I/O
   - Trace switchd during `ping -I swp1`
   - Capture exact API calls and parameters
   - Document buffer allocation/deallocation

**Expected Outcome**: Complete packet TX/RX API documentation

### Priority 2: Table Structures (Critical)

**Actions**:
1. Use Ghidra to find table access functions
   - Search for `bcm_l2_addr_add`, `bcm_l3_route_add` implementations
   - Extract structure definitions from function parameters
   - Document field offsets and sizes

2. Runtime table dumps
   - Use bcmsh to dump L2 table entries
   - Use bcmsh to dump L3 route entries
   - Reverse-engineer table layout from dumps

**Expected Outcome**: Table structure definitions

### Priority 3: Register Map Enhancement (High Priority)

**Actions**:
1. Extract more register constants from Ghidra
   - Search for 0x31xxx-0x35xxx constants
   - Find register access functions
   - Document register purposes

2. Use OpenNSL source as reference
   - Check OpenNSL for register definitions
   - Map OpenNSL registers to Cumulus offsets
   - Document register fields

**Expected Outcome**: Expanded register map (50-60% coverage)

### Priority 4: OpenNSL Evaluation (High Priority)

**Actions**:
1. Test OpenNSL on AS5610-52X
   - Compile OpenNSL for PowerPC
   - Test basic initialization
   - Evaluate TUN support options

2. Document integration approach
   - Map OpenNSL APIs to netlink handlers
   - Design TUN packet handler
   - Create integration plan

**Expected Outcome**: Viable implementation path

---

## 7. Summary Matrix

| Component | Have | Need | Coverage | Priority |
|-----------|------|------|----------|----------|
| **Architecture** | ✅ Complete | — | 95% | ✅ Done |
| **SDK APIs** | ✅ Names | Signatures | 90% | ⚠️ Medium |
| **Configuration** | ✅ Complete | — | 95% | ✅ Done |
| **Initialization** | ✅ Complete | — | 90% | ✅ Done |
| **Register Map** | ⚠️ Partial | Complete map | 30% | ❌ Critical |
| **Table Structures** | ⚠️ Partial | Complete layouts | 40% | ❌ Critical |
| **Packet TX/RX** | ⚠️ Partial | Signatures | 60% | ❌ Critical |
| **DMA Details** | ⚠️ Partial | Descriptor format | 50% | ⚠️ High |
| **Error Handling** | ⚠️ Partial | Error codes | 30% | ⚠️ Medium |
| **Performance** | ⚠️ Partial | Optimization guides | 50% | ⚠️ Medium |

---

## 8. Recommendations

### For Immediate Implementation

1. **Start with OpenNSL** (Option A)
   - Test OpenNSL on hardware
   - Evaluate TUN support
   - Implement netlink handlers using OpenNSL APIs

2. **Fill Critical Gaps in Parallel**
   - Use Ghidra to extract packet TX/RX signatures
   - Use Ghidra to find table structures
   - Document findings as you go

3. **Iterative Approach**
   - Get basic functionality working with OpenNSL
   - Replace OpenNSL components with custom code as you reverse-engineer details
   - Build custom SDK wrapper incrementally

### For Long-Term Custom SDK

1. **Complete Register Map**
   - Extract from OpenNSL source
   - Use Ghidra to find more registers
   - Capture hardware register dumps

2. **Reverse-Engineer Table Structures**
   - Use Ghidra to find structure definitions
   - Dump tables at runtime
   - Document field layouts

3. **Document Packet APIs**
   - Extract function signatures from Ghidra
   - Trace packet I/O dynamically
   - Document buffer management

---

## 9. Conclusion

**Current State**: Excellent foundation with ~75% coverage overall

**Strengths**:
- Complete architectural understanding
- Full configuration system documented
- Comprehensive API list (2,864 APIs)
- Verified packet I/O mechanism

**Weaknesses**:
- Incomplete register map (30% coverage)
- Missing table structures (40% coverage)
- Incomplete packet API signatures (60% coverage)

**Path Forward**:
- **Short term**: Use OpenNSL with TUN adaptation (most practical)
- **Long term**: Build custom SDK as you reverse-engineer more details

**Bottom Line**: You have enough to **implement a working switchd** using OpenNSL. For a **complete custom SDK**, you need 3-6 months more reverse engineering work to fill the register map and table structure gaps.

---

## Related Documents

- [GAPS_FOR_CUSTOM_SWITCHD_SDK.md](GAPS_FOR_CUSTOM_SWITCHD_SDK.md) - Detailed gap analysis
- [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md) - Complete checklist
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra findings

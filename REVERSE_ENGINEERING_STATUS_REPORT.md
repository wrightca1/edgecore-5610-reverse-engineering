# Reverse Engineering Status Report

**Date**: 2026-02-26  
**Purpose**: Comprehensive assessment of what we have vs what we need for custom switchd/SDK implementation  
**Total Documents**: 80+ markdown documents in `docs/reverse-engineering/` (including `traces/` subdir); see [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) for completion summary.

---

## Executive Summary

**Coverage**: ~85% complete for high-level implementation, ~65% for low-level SDK details

**Status**: 
- ✅ **Excellent** high-level architecture understanding
- ✅ **Good** API and configuration coverage  
- ✅ **Improved** low-level implementation details (FP, STG, SerDes Verified)
- ⚠️ **Partially documented** remaining register map and pipeline details

**Recommendation**: Proceed with OpenNSL + custom TUN adaptation with high confidence.

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

### 1.5 Register Access ✅ IMPROVED

| Document | Coverage | Status |
|----------|----------|--------|
| **ASIC_INIT_AND_DMA_MAP.md** | PCI BAR layout, CMIC base (0x31000), S-Chan (0x32800) | ✅ Complete |
| **SERDES_WC_INIT.md** | Warpcore MDIO sequence and equalization taps | ✅ Verified |
| **GEMINI_RE_SOLUTIONS.md** | Verified SerDes, Interrupt, and Buffer parameters | ✅ Verified |
| **GHIDRA_REGISTER_TABLE_ANALYSIS.md** | 34,918 register/table strings, xrefs | ✅ Partial |

**What We Have**:
- ✅ CMIC base address (0x31000)
- ✅ S-Channel register (0x32800)
- ✅ SerDes/Warpcore Tuning Sequence (MAIN=55, POSTC=8) (Verified)
- ✅ Interrupt ioctl mechanism (0x20004c09/0x20004c0a) (Verified)
- ✅ DMA registers (0x31140-0x311a4)
- ✅ IRQ registers (0x31400+)

**Coverage**: 75% - Key registers and tuning sequences verified.

### 1.6 Table Management ✅ IMPROVED

| Document | Coverage | Status |
|----------|----------|--------|
| **GEMINI_RE_SOLUTIONS.md** | Verified FP_TCAM and STG Table Layouts | ✅ Verified |
| **L2_PAYLOAD_FROM_DUMPS.md** | L2 entry layout and store offsets | ✅ Verified |
| **SDK_REGISTER_MAP.md** | L2/L3 table structures from OpenNSL | ✅ Complete |
| **netlink-handlers.md** | Table programming via SDK APIs | ✅ Complete |

**What We Have**:
- ✅ **FP_TCAM Layout**: 2048 entries, 234-bit key/mask (Verified)
- ✅ **STG Layout**: 2-bit state per port, Ingress/Egress tables (Verified)
- ✅ **L2 Layout**: 36-byte payload, MAC at offset 0x8 (Verified)
- ✅ `opennsl_l2_addr_t` structure layout documented
- ✅ `opennsl_l3_host_t`, `opennsl_l3_route_t`, `opennsl_l3_egress_t` structures documented

**Coverage**: 85% - Major ASIC table layouts verified on live hardware.

### 1.7 Packet I/O ✅ IMPROVED

| Document | Coverage | Status |
|----------|----------|--------|
| **PKTIO_BDE_DMA_INTERFACE.md** | DCB type 21, 16 words, TX/RX layout, BDE ioctls, DMA channels | ✅ Verified on live switch |
| **GEMINI_RE_SOLUTIONS.md** | Verified Interrupt/Semaphore Handshake | ✅ Verified |
| **PACKET_IO_VERIFIED.md** | TUN mechanism verified | ✅ Complete |
| **SDK_REGISTER_MAP.md** | Packet TX/RX API signatures from OpenNSL | ✅ Complete |

**What We Have**:
- ✅ DCB format (type 21, 64 bytes), LOCAL_DEST_PORT encoding, RX metadata (verified via bcmcmd dma dcbdump)
- ✅ `opennsl_tx()` function signature documented
- ✅ TUN device mechanism (52 TUN fds, one per port)
- ✅ Verified userspace interrupt state machine (WAIT_FOR_INTERRUPT/SEM_OP)

**Coverage**: 85% - Packet flow and synchronization mechanism verified.

### 1.8 Platform & Hardware ✅ GOOD

| Document | Coverage | Status |
|----------|----------|--------|
| **ONIE_BOOT_AND_PARTITION_LAYOUT.md** | Boot process and partitions | ✅ Complete |
| **QSFP_BREAKOUT_CONFIGURATION.md** | Port configuration | ✅ Complete |
| **SFP_TURNUP_AND_ACCESS.md** | SFP/QSFP access | ✅ Complete |
| **PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md** | Platform hardware access | ✅ Complete |

**Coverage**: 85% - Good platform understanding

---

## 4. Coverage Assessment

### By Category

| Category | Coverage | Documents | Status |
|----------|----------|-----------|--------|
| **Architecture & Flow** | 95% | 8 | ✅ Excellent |
| **SDK APIs** | 90% | 3 | ✅ Good |
| **Configuration** | 95% | 5 | ✅ Excellent |
| **Initialization** | 90% | 6 | ✅ Excellent |
| **Register Access** | 75% | 7 | ✅ Improved |
| **Table Structures** | 85% | 6 | ✅ Improved |
| **Packet I/O** | 85% | 4 | ✅ Improved |
| **Platform Hardware** | 85% | 3 | ✅ Good |

### Overall Coverage

- **High-Level (Architecture, APIs, Config)**: 95% ✅
- **Mid-Level (Initialization, Flow)**: 90% ✅
- **Low-Level (Registers, Tables, Packet APIs)**: 70% ✅

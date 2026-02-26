# Gaps for Writing Custom switchd/SDK

**Date**: 2026-02-25  
**Purpose**: Identify what's missing to implement a custom switchd and SDK interface for BCM56846 ASIC  
**Status**: Based on verified solutions from live switch (<LIVE_SWITCH_IP>)

---

## Executive Summary

You have **near-complete coverage** of:
- ✅ High-level architecture (netlink → SDK mapping)
- ✅ API patterns (2,864 `bcm_*` APIs identified)
- ✅ Configuration formats (.bcm, rc.soc)
- ✅ Initialization sequences
- ✅ Packet I/O mechanism (TUN + BDE + Verified ioctls)
- ✅ **FP/ACL Table Layout** (Verified 234-bit key/mask)
- ✅ **STG Table Layout** (Verified 2-bit state per port)
- ✅ **SerDes/Warpcore Tuning** (Verified MDIO sequences and tap values)

**Remaining gaps** are in:
- ❌ **Pipeline registers** (detailed ingress/egress staging)
- ❌ **L3 Route/ECMP Hash logic** (exact hardware hash polynomial selection)
- ❌ **Error handling** (exact parity recovery procedures)
- ❌ **Performance optimization** (exact interrupt coalescing thresholds)

---

## 1. Pipeline & Hash Logic (Current Priority)

### What You Have
- ✅ Register access patterns (`setreg`, `getreg`, `soc_reg`)
- ✅ S-Channel register offsets (CMIC_CMC0_SCHAN_CTRL = 0x32800)
- ✅ ECMP RTAG7 hash bin configuration from `rc.forwarding`
- ✅ **See [`GEMINI_RE_SOLUTIONS.md`](./GEMINI_RE_SOLUTIONS.md) for verified SerDes and Table data**

### What's Missing
- ❌ **Hash Polynomial logic**: While we have the bins, the exact hardware logic for the `hash_a0_function_select=9` (CRC16-CCITT) implementation in the pipeline is not fully documented.
- ❌ **Pipeline staging**: Exact register offsets for the IPIPE/EPIPE stage controls beyond the basic enable/disable bits.

---

## 2. Table Structures (Mostly Solved)

### What You Have
- ✅ **FP_TCAM**: 2048 entries, 59 bytes each, 234-bit Key/Mask (Verified)
- ✅ **STG_TAB**: 512 entries, 2 bits per port (Verified)
- ✅ **L2_USER_ENTRY**: 36-byte payload, MAC at offset 0x8 (Verified)

### What's Missing
- ❌ **L3 DEFIP Bit-Layout**: While we have the buffer size (0x224 bytes), the exact bit-level alignment for IPv6 prefixes within the 15-word entries is still inferred from OpenNSL headers rather than direct hardware dump.

---

## 3. Packet TX/RX APIs (Solved)

### What You Have
- ✅ Packet I/O mechanism (TUN devices)
- ✅ Flow understanding (TUN → SDK → BDE → ASIC)
- ✅ **Verified Synchronization**: `LUBDE_WAIT_FOR_INTERRUPT` (ioctl 9) and `LUBDE_SEM_OP` (ioctl 10).

### What's Missing
- ❌ **DMA Descriptor (DCB) bit-fields**: Exact layout of the physical descriptors in the DMA ring (e.g., SOF, EOF, Error bits).

---

## Conclusion

The project has moved from **"Researching"** to **"Implementation Phase"**. The core hardware obstacles (SerDes, Table Layouts, Interrupts) have been cleared via live switch verification.

**Recommended Path**:
- **Immediate**: Implement the TUN-to-DMA bridge using the verified ioctl state machine.
- **Next**: Implement L2/VLAN/STG programming using the verified 0x24-byte payload layouts.

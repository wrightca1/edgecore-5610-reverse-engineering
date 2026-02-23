# What You Need for a Fully Functional Software Stack (Edgecore AS5610-52X)

**Date**: 2026-02-15  
**Target**: Edgecore AS5610-52X (BCM56846 Trident+)  
**Goal**: Identify every gap between “what we know” and “fully functional L2/L3 switch”

---

## 1. What “Fully Functional” Means

- **Boot** → ONIE/kernel → BDE loaded → switchd (or equivalent) runs.
- **Ports** → All 52 ports (or 48+4 breakout) come up; link state correct; speed/duplex correct.
- **L2** → VLANs, MAC learning, forwarding; host/control traffic on swp via TUN.
- **L3** → Kernel routes and neighbors synced to ASIC FIB; ECMP; punt to CPU for slow path.
- **Packet I/O** → CPU→port (TX) and port→CPU (RX) through TUN ↔ SDK/BDE ↔ ASIC.

---

## 2. What You Already Have (Summary)

| Area | Status | Where It’s Documented |
|------|--------|------------------------|
| **Architecture** | ✅ Cumulus-style: TUN + BDE, no KNET | WHAT_MAKES_THE_SWITCH_WORK.md, PACKET_IO_VERIFIED.md |
| **Init sequence** | ✅ BDE open, attach, rc.soc, rc.ports, rc.datapath, rc.forwarding | initialization-sequence.md, SDK_AND_ASIC_CONFIG_FROM_SWITCH.md |
| **Config formats** | ✅ .bcm, rc.soc, porttab, datapath.conf, 11ports.bcm | Various config docs |
| **Port mapping** | ✅ swpN ↔ xeM (BCM port), porttab, SerDes/breakout concept | COMPLETE_INTERFACE_ANALYSIS.md, QSFP_BREAKOUT_CONFIGURATION.md |
| **Netlink → SDK** | ✅ Link, route, neighbor handlers; API patterns (bcm_*) | netlink-handlers.md, api-patterns.md |
| **CMIC/BDE registers** | ✅ Offsets from OpenNSL + linux-user-bde.c | SDK_REGISTER_MAP.md, BDE_CMIC_REGISTERS.md, SCHAN_AND_RING_BUFFERS.md |
| **S-Channel** | ✅ CMC0_SCHAN_CTRL = 0x32800, usage (control path) | SCHAN_AND_RING_BUFFERS.md |
| **LED registers** | ✅ Offsets (OpenNSL match) | SDK_REGISTER_MAP.md |
| **Table memory region** | ✅ 0x01000000–0x01ffffff; 20k+ addresses from libopennsl | TABLE_MEMORY_ANALYSIS.md, OPENNSL_LIBRARY_EXTRACTION_RESULTS.md |
| **Table names → addresses** | ✅ L2_ENTRY, L2_USER_ENTRY, L3_DEFIP, L3_ECMP, VLAN_XLATE, ECMP | TABLE_NAME_MAPPING.md, opennsl-table-name-to-addr-xref.txt |
| **Packet I/O flow** | ✅ TUN fd ↔ switchd ↔ SDK/BDE ↔ ASIC; strace evidence | PACKET_IO_VERIFIED.md |
| **OpenNSL packet API** | ✅ opennsl_tx, opennsl_rx_register/start/stop, opennsl_pkt_t | SDK_REGISTER_MAP.md (from OpenNSL headers) |
| **OpenNSL L2/L3 structures** | ✅ opennsl_l2_addr_t, opennsl_l3_route_t, opennsl_l3_egress_t, etc. | OpenNSL headers, SDK_REGISTER_MAP.md |

So you have: **architecture, init, config, port mapping, netlink handling, register map (partial), table regions and names, and packet API signatures.**

---

## 3. What You Still Need (By Priority)

### 3.1 Critical (Without These, Stack Won’t Work End-to-End)

| Gap | What’s Missing | Why It Matters | Possible Way to Get It |
|-----|----------------|----------------|-------------------------|
| **Packet TX/RX implementation** | Exact code path: TUN fd → which SDK/BDE call → ASIC. Buffer format, ownership, error handling. | You know it’s TUN+BDE and have OpenNSL API names; you need the **actual implementation** (e.g. how switchd calls into libopennsl/BDE for one packet). | Trace switchd (strace/ltrace) on TX and RX; or Ghidra: find callers of opennsl_tx / RX callback registration and follow buffer flow. |
| **BDE device usage for packets** | How switchd uses `/dev/linux-user-bde` (and optionally `/dev/mem`) for packet DMA: ioctl sequence, buffer registration, ring layout. | Packets don’t move without this. | Trace ioctl on BDE fd during ping; inspect BDE kernel or user-side source (if available); compare with OpenNSL KNET path (same BDE underneath). |
| **Port/SerDes bringup** | Exact sequence and registers to get link up per port (SerDes, MAC, PHY). Port enable, speed, duplex. | Ports stay down without it. | Capture register writes during “port up” on working Cumulus; or reuse OpenNSL port init if you use OpenNSL. |
| **Table entry layouts (enough to program L2/L3)** | Bit-level layout of L2 entry, L3 route/host/egress, and how they’re written (direct memory vs S-Channel vs SDK API). | Needed to sync kernel state to ASIC (or to debug SDK). | OpenNSL structs give logical fields; Ghidra on table-access functions in libopennsl can map to memory; or dump table contents on live switch and reverse. |

### 3.2 High (Needed for Robust, Deployable Stack)

| Gap | What’s Missing | Why It Matters | Possible Way to Get It |
|-----|----------------|----------------|-------------------------|
| **Complete register map** | All CMIC, port, pipeline, buffer, and stats registers; which are S-Channel vs direct. | Debugging, tuning, and any direct register programming. | Extend Ghidra extraction; register dumps during init; OpenNSL/soc code. |
| **DMA/ring layout** | Descriptor format, ring size, channel assignment (TX/RX), interrupt/coalescing. | Correct and efficient packet I/O. | BDE/KNET source or docs; trace descriptor setup; compare with SCHAN_AND_RING_BUFFERS.md. |
| **Error and return codes** | SDK and BDE error codes and when they occur. | Reliable error handling and logging. | OpenNSL headers; Ghidra on error paths; runtime testing. |
| **Platform/AS5610 specifics** | I2C for SFP/QSFP, thermal, LED mapping, any platform EEPROM or GPIO. | Full platform support and diagnostics. | ONLP or vendor docs; compare with port bringup and existing ONL/platform code. |

### 3.3 Medium (Important for Production Quality)

| Gap | What’s Missing | Why It Matters | Possible Way to Get It |
|-----|----------------|----------------|-------------------------|
| **VLAN/ACL/FP table layouts** | How VLAN_XLATE and FP/ACL entries are encoded and written. | Advanced L2 and ACL features. | Same as L2/L3: OpenNSL + Ghidra + live dumps. |
| **Stats and counters** | Counter list, register or DMA format, overflow behavior. | Monitoring and troubleshooting. | OpenNSL/soc stats APIs; register map. |
| **Buffer/datapath tuning** | Pool sizes, priority groups, coalescing from datapath.conf → actual registers. | Avoid drops under load. | Reverse rc.datapath_0 and register writes; or rely on OpenNSL defaults. |

### 3.4 Lower (Nice to Have)

| Gap | What’s Missing | Why It Matters |
|-----|----------------|----------------|
| **QoS/CoS, mirroring, tunnels** | Detailed register/table usage. | Advanced features. |
| **Trunk/LAG** | Trunk group and member programming. | LAG. |

---

## 4. Two Practical Paths

### Path A: OpenNSL-Based Stack (Fastest to “Working”)

- **Use OpenNSL** for: init, port config, L2/L3/ECMP/VLAN APIs, and (if available) packet TX/RX.
- **Use BDE** as shipped with OpenNSL (or your built BDE for PowerPC/ONL).
- **Implement TUN-based I/O** by either:
  - Using OpenNSL’s RX/TX if they work with your BDE (no KNET), or
  - Implementing a small shim: TUN read → your buffer → OpenNSL/BDE TX; and BDE RX → your buffer → TUN write.
- **Gaps you still need**: (1) Exact OpenNSL+BDE packet path (so your TUN shim matches), (2) port/SerDes bringup (OpenNSL may cover most of it), (3) platform/AS5610 (I2C, thermal, LED) if you care.

**Information still needed**: Packet path (TUN ↔ OpenNSL/BDE), BDE packet interface, and AS5610-specific port/platform details.

### Path B: Minimal Custom SDK (Maximum Control)

- **BDE**: Keep using it for PCI, BAR, DMA, S-Channel (you have enough to open device and do register access).
- **Register access**: Use your register map + S-Channel where needed; add missing registers as you reverse or dump.
- **Tables**: Use table names and addresses you have; reverse entry layouts from libopennsl table-access functions or runtime dumps; write table programming (or thin wrappers) yourself.
- **Packet I/O**: Reverse the exact BDE packet interface (ioctl, rings, buffers) and implement TX/RX yourself.

**Information still needed**: Everything in §3.1 plus full register map and table layouts; §3.2–3.3 as you need robustness and features.

---

## 5. Minimal “Must Resolve” List for Any Path

To get a **fully functional** software stack for the Edgecore 5610, you must close at least:

1. **Packet path** – From TUN fd to ASIC TX and from ASIC RX to TUN fd (exact APIs and buffer flow).
2. **BDE packet interface** – How buffers and rings are set up and used for that path.
3. **Port bringup** – Enough SerDes/port init that link comes up on the ports you use.
4. **L2/L3 programming** – Either via OpenNSL (Path A) or your own code (Path B); in both cases you need either working APIs or table layouts + write path.

Everything else (full register map, stats, ACL, QoS, platform I2C/thermal, etc.) supports robustness and features but is not the minimum to “get the stack working.”

---

## 6. Where It’s Documented

- **Gaps in detail**: [GAPS_FOR_CUSTOM_SWITCHD_SDK.md](GAPS_FOR_CUSTOM_SWITCHD_SDK.md)  
- **What makes the switch work (checklist)**: [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md)  
- **Register and table map**: [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md), [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md)  
- **Table names and addresses**: [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md), `opennsl-table-name-to-addr-xref.txt`  
- **Packet I/O (TUN)**: [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md)  
- **Init and config**: [initialization-sequence.md](initialization-sequence.md), [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md)

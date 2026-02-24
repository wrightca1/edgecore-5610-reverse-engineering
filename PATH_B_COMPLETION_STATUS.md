# Path B Completion Status

**Date**: 2026-02-23
**Purpose**: Summary of completed work and remaining gaps for a minimal custom SDK/switchd on Edgecore AS5610-52X (BCM56846).

---

## Completed

| Area | Status | Artifacts / Notes |
|------|--------|-------------------|
| **BDE/device (1.x)** | HAVE | ioctl list, mmap at 0x04000000 + 0xa0000000; reg access via mmap |
| **S-Channel (2.3)** | HAVE | Command word format `0x2800XXXX` decoded. FUN_00703dc0 builds command word. [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) |
| **BDE/device arch** | HAVE | Cumulus uses switchd with Broadcom `bcm_*` SDK (statically linked) — NOT libopennsl. OpenNSL `opennsl_*` is functionally identical. [CUMULUS_VS_OPENNSL_ARCHITECTURE.md](CUMULUS_VS_OPENNSL_ARCHITECTURE.md) |
| **L2 (3.3, 3.8)** | **HAVE** | Full call chain decoded. **ASIC bit positions verified** via bcmcmd listmem + raw dump + write-back tests on live switch. Two tables: L2_ENTRY (hash, 131072 entries, 13 bytes, addr 0x07120000) for regular MACs; L2_USER_ENTRY (TCAM, 512 entries, 20 bytes, addr 0x06168000) for guaranteed/BPDU entries. **L2_ENTRY**: VALID@bit0, KEY_TYPE@3:1, VLAN_ID@15:4, MAC_ADDR@63:16, PORT_NUM@70:64, MODULE_ID@78:71, T@79, STATIC_BIT@93. **L2_USER_ENTRY**: VALID@0, MAC@48:1, VLAN@60:49, KEY_TYPE@61, MASK@122:62, CPU@129, PORT_NUM@137:131, BPDU@154. KEY formula: `KEY = (KEY_TYPE<<60)|(VLAN_ID<<48)|MAC_ADDR`. Hash key for L2_ENTRY: `(MAC<<16)|(VLAN<<4)|(KEY_TYPE<<1)`. [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md), [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) |
| **Write mechanism** | **HAVE** (L3_DEFIP confirmed) | Runtime GDB on Cumulus switchd confirmed S-channel DMA path (NOT direct BAR writes). Main thread → `FUN_10324084` → `FUN_103257B8` (queue S-chan cmd + SEM_GIVE) → DMA thread → `.BCM` BDE ioctl → kernel DMA → ASIC. CPU never writes SCHAN_CTRL (0x32800) directly; DMA engine does it internally. libopennsl's `FUN_01876c30` bctrl handler question: for Cumulus switchd, the statically-linked SDK uses S-channel DMA. [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md), [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) |
| **L3/ECMP/VLAN (3.4-3.9)** | **HAVE** | **Full chain verified via bcmcmd on live switch (2026-02-23)**. L3_DEFIP: TCAM, 30 bytes, KEY=(VRF<<33)\|(IP<<1)\|MODE. L3_ECMP: 4096×2B, NEXT_HOP_INDEX[13:0]. L3_ECMP_GROUP: 1024×25B, BASE_PTR[21:10]+COUNT[9:0]. ING_L3_NEXT_HOP: PORT_NUM[22:16]+MODULE_ID[30:23] (raw verified: 0x00010004→port=1). EGR_L3_NEXT_HOP: L3:MAC_ADDRESS[62:15]+L3:INTF_NUM[14:3] (raw verified: nexthop[3]→MAC=6c:b2:ae:cd:13:33,INTF=1). EGR_L3_INTF: VID[24:13]+MAC[80:33] (raw verified: intf[1]→VLAN=3301,MAC=80:a2:35:81:ca:af). VLAN_XLATE: not used on pure L3 switch. [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md), [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md), [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) |
| **IPv6 routing** | **HAVE** | **All three IPv6 tables verified via bcmcmd on live switch (2026-02-23)**. BCM56846 uses: (1) **L3_DEFIP_128** (0x0a176000, 256×39B TCAM): IPv6 /128 exact-match; KEY@[141:2]={VRF[139:130]\|IPv6_addr[129:2]}, NEXT_HOP_INDEX@[296:283]; raw-verified fe80::/128 entries. (2) **L3_DEFIP double-wide** (same TCAM, MODE0=MODE1=1, VALID0=VALID1=1): IPv6 LPM prefix ≤ 64 bits; IP_ADDR1@[78:47]=IPv6[127:96], IP_ADDR0@[34:3]=IPv6[95:64]; KEY=(VRF<<33)\|(IP_ADDR_half<<1)\|1; verified with ::/0 default, /32, and /64 routes. (3) **L3_ENTRY_IPV6_UNICAST** (0x0917c000, 8192×22B hash): present but unused in this deployment. Nexthop tables ING/EGR_L3_NEXT_HOP + EGR_L3_INTF shared with IPv4. [L3_IPV6_FORMAT.md](L3_IPV6_FORMAT.md) |
| **Packet I/O (4.x)** | HAVE (4.3, 4.6); PARTIAL (4.4, 4.5, 4.7–4.8) | TX path, buffer format documented. [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md), [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md) |
| **Port bringup (5.2-5.3)** | **HAVE** | Port API dispatch: enable→FUN_007d3f34, speed→FUN_007de7cc (-0x5fe0), duplex→FUN_007d3294 (-0x68b0). **XLPORT/MAC registers verified via bcmcmd**: XLPORT_PORT_ENABLE (block_base+0x80000+0x22a), XLPORT_CONFIG (lane*0x1000+0x200), MAC_MODE (lane*0x1000+0x511), MAC_0/MAC_1 (0x503/0x504). Full 16-block address map (xe0–xe51). **Warpcore SerDes init captured via GDB watchpoint (2026-02-23)**: CMIC_MIIM_PARAM=0x0291xxxx (INTERNAL_SEL+BUS_ID+PHY_ADDR+DATA), MIIM_ADDRESS=reg#. Full 10G init sequence: TX config (reg[0x17]=0x8010, reg[0x18]=0x8370), IEEE block (page 0x0008), AN/clock (page 0x1000), SerDes digital (page 0xa00, reg[0x10]=0xffe0), RX EQ (regs 0x19-0x1d=0x8320/0x8350), WC_CORE sequencer (page 0x3800, reg[0x01]=0x0010). [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md), [SERDES_WC_INIT.md](SERDES_WC_INIT.md) |
| **Init (6.x)** | HAVE | rc.soc, rc.ports, rc.datapath, rc.forwarding sequence known |

---

## Remaining (must-have to ship)

1. **S-Channel (2.3)**: ✅ HAVE - [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md), [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md)
2. **Packet TX path (4.3)**: ✅ HAVE - opennsl_tx → FUN_0080ba18 → … → FUN_013949c0. [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md), [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md)
3. **Packet buffer (4.6)**: ✅ HAVE - opennsl_pkt_t, offset 0x8 packet data. [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md)
4. **L2 layout (3.3, 3.8)**: ✅ HAVE — bit positions fully verified via bcmcmd on live switch. L2_ENTRY + L2_USER_ENTRY formats documented with raw word encoding. [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md)
5. **L3/ECMP/VLAN (3.4–3.9)**: ✅ HAVE — Full nexthop chain decoded via bcmcmd. L3_DEFIP write path (call chain + ASIC format). L3_ECMP: NEXT_HOP_INDEX[13:0]. L3_ECMP_GROUP: BASE_PTR+COUNT. ING/EGR_L3_NEXT_HOP + EGR_L3_INTF: all field bit positions verified with raw encoding. VLAN_XLATE not used. [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md), [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md)
6. **Write mechanism (3.8)**: PARTIAL — FUN_01876c30 dispatch structure CONFIRMED (checks unit_struct+0x19484 for bctrl, calls it or falls through to FUN_018758cc); runtime handler address still needs GDB. [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md)
7. **Port bringup regs (5.2–5.3)**: ✅ HAVE — XLPORT/MAC registers + full Warpcore SerDes init sequence captured via GDB watchpoint. [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md), [SERDES_WC_INIT.md](SERDES_WC_INIT.md)

---

## Scripts and commands

| Script | Purpose |
|--------|---------|
| `run-dump-func-on-build-server.sh <binary> <addr>` | Dump function assembly |
| `run-schan-data-refs-on-build-server.sh` | Find 0x32800/0x2800 refs |
| `run-l2-callers-on-build-server.sh` | L2 call chain |
| `run-port-up-trace-10.1.1.233.sh [iface]` | Port up/down trace on switch |
| `run-find-packet-tx-path-on-build-server.sh [binary]` | Packet TX path (opennsl_tx, read) |
| `run-find-table-write-callers-on-build-server.sh` | Find callers of FUN_01876f10 (generic table write dispatcher) |
| `run-find-specific-table-ids-on-build-server.sh` | Find callers passing specific table IDs (0x1547, 0x22ca, 0x2c33, 0x835) |
| `run-find-l3-table-callers-on-build-server.sh` | Find functions referencing L3_DEFIP, L3_ECMP, VLAN_XLATE table names |
| `run-find-table-dispatcher-callers-on-build-server.sh` | Find callers of FUN_018d7ad4 (table ID validator/dispatcher) |
| `run-analyze-table-dispatcher-call-sites-on-build-server.sh` | Analyze call sites to find table IDs passed in r7 |
| `run-find-table-dispatcher-caller-chain-on-build-server.sh` | Trace caller chains of dispatcher functions |
| `run-find-table-name-to-dispatcher-chain-on-build-server.sh` | Trace functions referencing table name strings to dispatcher functions |
| `extract-exported-symbols.sh` | Extract exported symbols from libopennsl.so to identify API entry points |
| `run-trace-api-to-dispatcher-on-build-server.sh` | Trace exported API functions to dispatcher functions |
| `run-find-api-callees-on-build-server.sh` | Find callees of exported API functions |
| `run-trace-api-callees-to-dispatcher-on-build-server.sh` | Trace API callees to dispatcher functions |
| `run-find-callers-on-build-server.sh <func>` | Find all callers of a specific function |

---

## References

- **Infrastructure (hosts, paths, workflows)**: [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md)
- [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md)
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md)
- [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) - Complete API to hardware call chains
- [DISPATCHER_CALL_CHAIN_SUMMARY.md](DISPATCHER_CALL_CHAIN_SUMMARY.md) - Dispatcher function summary
- [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md) - Packet TX path and buffer format
- [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md) - Table ID mapping analysis
- [PORT_FUNCTIONS_ANALYSIS.md](PORT_FUNCTIONS_ANALYSIS.md) - Port function analysis
- [FINAL_ANALYSIS_SUMMARY.md](FINAL_ANALYSIS_SUMMARY.md) - Comprehensive analysis summary
- [CUMULUS_VS_OPENNSL_ARCHITECTURE.md](CUMULUS_VS_OPENNSL_ARCHITECTURE.md) - switchd (bcm_*) vs libopennsl (opennsl_*) architectural distinction
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) - FUN_01876c30 dispatch chain, bctrl handler analysis, S-Chan vs BAR
- [DESCRIPTOR_BUFFER_FILL_ANALYSIS.md](DESCRIPTOR_BUFFER_FILL_ANALYSIS.md) - FUN_0181e718 binary search + bitfield packing (L2/VLAN buffer fill)
- [L3_TABLE_FILL_FROM_014a51e8.md](L3_TABLE_FILL_FROM_014a51e8.md) - FUN_014a51e8 table ID dispatch and buffer stores
- [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) - **L2_ENTRY + L2_USER_ENTRY ASIC bit layout (verified)**
- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) - Full L2 call chain synthesis
- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) - Full L3/ECMP/VLAN call chain synthesis
- [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) - **L3_ECMP + ING/EGR_L3_NEXT_HOP + EGR_L3_INTF field layouts (verified)**
- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) - Port BAR diff classification + API dispatch + XLPORT/MAC register map
- [SERDES_WC_INIT.md](SERDES_WC_INIT.md) - **Warpcore WC-B0 SerDes MDIO init sequence (verified via GDB watchpoint)**
- [L3_IPV6_FORMAT.md](L3_IPV6_FORMAT.md) - **IPv6 routing tables: L3_DEFIP_128 (/128 TCAM), L3_DEFIP double-wide (LPM ≤/64), L3_ENTRY_IPV6_UNICAST (unused) — all field layouts verified**

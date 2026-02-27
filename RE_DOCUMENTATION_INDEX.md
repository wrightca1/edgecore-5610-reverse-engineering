# Reverse Engineering Documentation — Full Index

**Last updated**: 2026-02-26  
**Total**: 80+ markdown docs + traces + sdk-register-map. Use this to “check” all RE docs.

---

## 1. Status and roadmap (start here)

| Document | Purpose |
|----------|---------|
| [RE_COMPLETE.md](RE_COMPLETE.md) | Phase 1–5 summary; “all phases complete”; verification on switch |
| [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md) | Path B checklist: BDE, registers, tables, packet I/O, port, init (HAVE/NEED) |
| [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) | What’s done (L2/L3/ECMP/VLAN/port/DCB verified); scripts list |
| [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) | Concise “what’s left”; Cumulus vs OpenNSL; next steps in order |
| [REVERSE_ENGINEERING_STATUS_REPORT.md](REVERSE_ENGINEERING_STATUS_REPORT.md) | Coverage (~85% high-level); what we have vs need |
| [STACK_READINESS_AS5610.md](STACK_READINESS_AS5610.md) | What you need for a fully functional stack; Path A vs Path B |
| [GAPS_FOR_CUSTOM_SWITCHD_SDK.md](GAPS_FOR_CUSTOM_SWITCHD_SDK.md) | Gaps for custom switchd/SDK |
| [GEMINI_RE_GAPS.md](GEMINI_RE_GAPS.md) | RE gaps (Gemini) |
| [GEMINI_RE_SOLUTIONS.md](GEMINI_RE_SOLUTIONS.md) | RE solutions |

---

## 2. BDE, device, registers

| Document | Purpose |
|----------|---------|
| [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md) | BDE init, DMA pool, /dev/mem mappings |
| [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md) | CMIC/CMICm register offsets |
| [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md) | Register map (CMIC, S-Chan, DMA, LED, etc.) |
| [SCHAN_AND_RING_BUFFERS.md](SCHAN_AND_RING_BUFFERS.md) | S-Channel + DMA ring registers (0x31140, 0x31158, 0x32800) |
| [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) | Command word `0x2800XXXX`; FUN_00703dc0 |
| [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md) | S-Chan 0x2800 refs; command builder |
| [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) | Table write dispatch (FUN_01876f10 → bctrl); S-Chan vs BAR |
| [REGISTER_EXTRACTION_RESULTS.md](REGISTER_EXTRACTION_RESULTS.md) | Register extraction |
| [REGISTER_EXTRACTION_STATUS.md](REGISTER_EXTRACTION_STATUS.md) | Status |
| [REGISTER_EXTRACTION_SUMMARY.md](REGISTER_EXTRACTION_SUMMARY.md) | Summary |
| [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) | Ghidra register/table strings, xrefs |

---

## 3. Tables: L2, L3, ECMP, VLAN

| Document | Purpose |
|----------|---------|
| [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) | **L2_ENTRY** (0x07120000) + **L2_USER_ENTRY** bit layout; hash key formula; verified |
| [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) | L2 call chain; table 0x1547; 0x24-byte buffer; ASIC encoding |
| [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md) | L2 write path; S-Chan not found in L2 path yet |
| [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md) | 0x24-byte buffer; FUN_01876f10(0x1547); 01cbd2e0 |
| [L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md](L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md) | Steps to decode S-Chan memory write for L2 |
| [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md) | L2 table access; call chain |
| [L2_INDEX_SOURCE_FROM_DUMPS.md](L2_INDEX_SOURCE_FROM_DUMPS.md) | Hash/index; retry 0..5; -1 from 00948700 |
| [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) | **L3_DEFIP**, ING/EGR_L3_NEXT_HOP, EGR_L3_INTF; verified |
| [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) | L3/ECMP/VLAN write chain; op 4/6/8; 0x224 buffer; VLAN 0x24 path |
| [L3_ECMP_VLAN_ANALYSIS.md](L3_ECMP_VLAN_ANALYSIS.md) | ECMP/VLAN analysis |
| [L3_ECMP_VLAN_CURRENT_STATE.md](L3_ECMP_VLAN_CURRENT_STATE.md) | Current state |
| [L3_ECMP_VLAN_PROGRESS_SUMMARY.md](L3_ECMP_VLAN_PROGRESS_SUMMARY.md) | Progress summary |
| [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md) | L3 next steps; per-table layout |
| [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md) | L3 table write chain dump |
| [L3_TABLE_FILL_FROM_014a51e8.md](L3_TABLE_FILL_FROM_014a51e8.md) | FUN_014a51e8 table fill |
| [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md) | 0x224 buffer layout; 014a51e8/0170b700 stores |
| [L3_IPV6_FORMAT.md](L3_IPV6_FORMAT.md) | IPv6 tables (L3_DEFIP_128, double-wide, etc.); verified |
| [SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md](SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md) | L3 route programming; S-Chan WRITE_MEMORY (0x28, Word 1 = address); DMA path |
| [VLAN_TABLE_FORMAT.md](VLAN_TABLE_FORMAT.md) | VLAN + EGR_VLAN; verified |
| [ECMP_GROUP_LAYOUT_FROM_01a1572c.md](ECMP_GROUP_LAYOUT_FROM_01a1572c.md) | ECMP group layout; table 0x1570 |
| [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md) | Table names → addresses |
| [TABLE_ID_MAPPING_ANALYSIS.md](TABLE_ID_MAPPING_ANALYSIS.md) | Table ID mapping |
| [TABLE_MEMORY_ANALYSIS.md](TABLE_MEMORY_ANALYSIS.md) | Table memory region 0x01xxxxxx |
| [TABLE_MEMORY_MAP_FROM_OPENNSL.md](TABLE_MEMORY_MAP_FROM_OPENNSL.md) | Table memory map from OpenNSL |
| [TABLE_ADDR_XREFS_OPENNSL.md](TABLE_ADDR_XREFS_OPENNSL.md) | Table address xrefs |
| [DESCRIPTOR_BUFFER_FILL_ANALYSIS.md](DESCRIPTOR_BUFFER_FILL_ANALYSIS.md) | FUN_0181e718 descriptor-driven buffer fill (L2/VLAN) |

---

## 4. Packet I/O, DMA, TX/RX

| Document | Purpose |
|----------|---------|
| [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md) | TUN + BDE; no KNET; flow verified |
| [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md) | opennsl_pkt_t; offset 0x8; TX path (opennsl_tx → … → 013949c0) |
| [PKTIO_BDE_DMA_INTERFACE.md](PKTIO_BDE_DMA_INTERFACE.md) | **DCB type 21**, 16 words; TX/RX word layout; LOCAL_DEST_PORT; BDE ioctls; verified |
| [DMA_DCB_LAYOUT_FROM_KNET.md](DMA_DCB_LAYOUT_FROM_KNET.md) | DCB layout from bcm-knet.c |
| [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md) | opennsl_tx callees; packet TX path |
| [TRACING_PACKET_IO_GUIDE.md](TRACING_PACKET_IO_GUIDE.md) | How to trace packet I/O |
| [cumulus-packet-io-architecture.md](cumulus-packet-io-architecture.md) | Packet I/O architecture |
| [packet-flow-analysis.md](packet-flow-analysis.md) | Packet flow |

---

## 5. Port bringup, SerDes

| Document | Purpose |
|----------|---------|
| [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) | BAR diff; XLPORT/MAC; 0x4xxx range; port API dispatch; next steps |
| [PORT_BRINGUP_REGISTERS_ANALYSIS.md](PORT_BRINGUP_REGISTERS_ANALYSIS.md) | Port bringup registers analysis |
| [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md) | Port API call chain; enable/speed/duplex |
| [PORT_FUNCTIONS_ANALYSIS.md](PORT_FUNCTIONS_ANALYSIS.md) | Port functions analysis |
| [SERDES_WC_INIT.md](SERDES_WC_INIT.md) | **Warpcore WC-B0** SerDes MDIO init; 10G sequence; verified via GDB |

---

## 6. Config, init, SDK/ASIC config

| Document | Purpose |
|----------|---------|
| [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md) | Live switch config (config.bcm, portmap, rc.*) |
| [initialization-sequence.md](initialization-sequence.md) | 16-step init |
| [asic-init-sequence.md](asic-init-sequence.md) | rc.soc register writes |
| [bcm-config-format.md](bcm-config-format.md) | .bcm format |
| [config-to-register-map.md](config-to-register-map.md) | Config → register map |
| [COMPLETE_INTERFACE_ANALYSIS.md](COMPLETE_INTERFACE_ANALYSIS.md) | Interface creation; swpN ↔ xeM |
| [QSFP_BREAKOUT_CONFIGURATION.md](QSFP_BREAKOUT_CONFIGURATION.md) | Port 49–52 breakout |
| [LIVE_SWITCH_CONFIG_<LIVE_SWITCH_IP>.md](LIVE_SWITCH_CONFIG_<LIVE_SWITCH_IP>.md) | Live switch <LIVE_SWITCH_IP> config |

---

## 7. Netlink, API, call chains

| Document | Purpose |
|----------|---------|
| [netlink-handlers.md](netlink-handlers.md) | RTM_* → SDK (link, route, neigh, addr) |
| [netlink-message-flow.md](netlink-message-flow.md) | Netlink message flow |
| [api-patterns.md](api-patterns.md) | Common SDK call patterns |
| [API_TO_DISPATCHER_CALL_CHAIN.md](API_TO_DISPATCHER_CALL_CHAIN.md) | API → dispatcher → table write |
| [COMPLETE_CALL_CHAIN_DOCUMENTATION.md](COMPLETE_CALL_CHAIN_DOCUMENTATION.md) | Full API → hardware chains |
| [DISPATCHER_CALL_CHAIN_SUMMARY.md](DISPATCHER_CALL_CHAIN_SUMMARY.md) | Dispatcher summary; FUN_01876f10 |
| [FINAL_ANALYSIS_SUMMARY.md](FINAL_ANALYSIS_SUMMARY.md) | Analysis summary |
| [ANALYSIS_SUMMARY.md](ANALYSIS_SUMMARY.md) | Analysis summary |
| [ANALYSIS_RUN_2026-02-18.md](ANALYSIS_RUN_2026-02-18.md) | Analysis run |
| [CUMULUS_VS_OPENNSL_ARCHITECTURE.md](CUMULUS_VS_OPENNSL_ARCHITECTURE.md) | Cumulus (bcm_*) vs OpenNSL (opennsl_*) |
| [OPENNSL_LIBRARY_EXTRACTION_RESULTS.md](OPENNSL_LIBRARY_EXTRACTION_RESULTS.md) | OpenNSL extraction |
| [OPENNSL_LIBRARY_EXTRACTION_STATUS.md](OPENNSL_LIBRARY_EXTRACTION_STATUS.md) | Status |
| [sdk-api-list.md](sdk-api-list.md) | bcm_* API list |
| [sdk-api-mapping.md](sdk-api-mapping.md) | API mapping |
| [interface-creation-mechanism.md](interface-creation-mechanism.md) | Interface creation |
| [interface-creation-analysis.md](interface-creation-analysis.md) | Interface creation analysis |

---

## 8. Platform, stats, misc

| Document | Purpose |
|----------|---------|
| [PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md](PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md) | Thermal, PSU, platform |
| [SFP_TURNUP_AND_ACCESS.md](SFP_TURNUP_AND_ACCESS.md) | SFP/QSFP access |
| [STATS_COUNTER_FORMAT.md](STATS_COUNTER_FORMAT.md) | Stats counter register map; verified |
| [ONIE_BOOT_AND_PARTITION_LAYOUT.md](ONIE_BOOT_AND_PARTITION_LAYOUT.md) | ONIE boot; partitions |
| [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md) | Checklist of required components |
| [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md) | Hosts, paths, workflows |
| [ENVIRONMENT_REFERENCE.md](ENVIRONMENT_REFERENCE.md) | Environment |
| [MANUAL_SSH_KEY_TO_SWITCH.md](MANUAL_SSH_KEY_TO_SWITCH.md) | SSH key to switch |
| [SSH_KEY_AUTH_SWITCH.md](SSH_KEY_AUTH_SWITCH.md) | SSH auth |
| [VERSIONS_AND_BUILD_INFO.md](VERSIONS_AND_BUILD_INFO.md) | Versions and build |
| [VERIFICATION_RESULTS.md](VERIFICATION_RESULTS.md) | Verification results |
| [SESSION_SUMMARY_2026-02-19.md](SESSION_SUMMARY_2026-02-19.md) | Session summary |
| [PUBLISH_AND_REDACTION.md](PUBLISH_AND_REDACTION.md) | Publish and redaction |
| [file-access-pattern.md](file-access-pattern.md) | File access pattern |
| [architecture-diagrams.md](architecture-diagrams.md) | Architecture diagrams |
| [HOW_TO_RUN_FINDPACKETTXPATH.md](HOW_TO_RUN_FINDPACKETTXPATH.md) | How to run FindPacketTxPath |
| [FUNCTION_STRINGS_ANALYSIS.md](FUNCTION_STRINGS_ANALYSIS.md) | Function strings |
| [REVERSE_ENGINEERING_PROGRESS_SUMMARY.md](REVERSE_ENGINEERING_PROGRESS_SUMMARY.md) | Progress summary |

---

## 9. Runtime tracing, switchd analysis

| Document | Purpose |
|----------|---------|
| [RUNTIME_TRACING_COMPLETE.md](RUNTIME_TRACING_COMPLETE.md) | Runtime tracing complete |
| [RUNTIME_TRACING_GUIDE.md](RUNTIME_TRACING_GUIDE.md) | How to run traces |
| [RUNTIME_TRACING_STATUS.md](RUNTIME_TRACING_STATUS.md) | Status |
| [switchd-dynamic-analysis-summary.md](switchd-dynamic-analysis-summary.md) | switchd dynamic analysis |
| [switchd-init-trace.md](switchd-init-trace.md) | switchd init trace |
| [switchd-binary-analysis.md](switchd-binary-analysis.md) | switchd binary analysis |

---

## 10. Traces (subdir `traces/`)

| File | Purpose |
|------|---------|
| [traces/RUNTIME_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/RUNTIME_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md) | Runtime trace analysis |
| [traces/PORT_UP_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/PORT_UP_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md) | Port up trace |
| [traces/TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md) | Trace analysis |
| [traces/PORT_UP_PERF_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/PORT_UP_PERF_ANALYSIS_<LIVE_SWITCH_IP>.md) | Port up perf |
| [traces/BAR_DIFF_PORT_UP_<LIVE_SWITCH_IP>.md](traces/BAR_DIFF_PORT_UP_<LIVE_SWITCH_IP>.md) | BAR diff on port up |
| [traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md) | BDE mmap (0x04000000, 0xa0000000) |
| [traces/PACKET_IO_TRACE_EXTRACTED_<LIVE_SWITCH_IP>.md](traces/PACKET_IO_TRACE_EXTRACTED_<LIVE_SWITCH_IP>.md) | Packet I/O extracted |
| [traces/RUN_SUMMARY_<LIVE_SWITCH_IP>.md](traces/RUN_SUMMARY_<LIVE_SWITCH_IP>.md) | Run summary |
| traces/*.log, *.txt | Raw trace logs and summaries (port-up, packet-io, bde-mmap, schan, etc.) |

---

## 11. Other files

| Item | Purpose |
|------|---------|
| `sdk-register-map/` | opennsl-dma-registers.txt, opennsl-register-defines.txt, opennsl-cmic-registers.txt |
| `sdk-api-list.txt` | Plain list of APIs |
| `switchd-summary.txt` | switchd summary |
| `netlink-events.log` | Netlink events log |

---

## Quick reference: key docs for open-nos-as5610

| Need | Doc |
|------|-----|
| L2 entry layout + hash | L2_ENTRY_FORMAT.md, L2_WRITE_PATH_COMPLETE.md |
| L2 S-Chan write | SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md (§ S-Channel WRITE_MEMORY), SCHAN_FORMAT_ANALYSIS.md |
| L3 nexthop, egress, intf | L3_NEXTHOP_FORMAT.md, L3_ECMP_VLAN_WRITE_PATH.md |
| Port/SerDes | PORT_BRINGUP_REGISTER_MAP.md, SERDES_WC_INIT.md |
| Packet I/O, DCB | PKTIO_BDE_DMA_INTERFACE.md, PACKET_BUFFER_ANALYSIS.md |
| Config, init | SDK_AND_ASIC_CONFIG_FROM_SWITCH.md, initialization-sequence.md |
| Netlink → SDK | netlink-handlers.md, api-patterns.md |
| What’s done / what’s left | PATH_B_COMPLETION_STATUS.md, PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md |

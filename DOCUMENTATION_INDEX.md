# Master Documentation Index — AS5610-52X / BCM56846 RE

**Last updated**: 2026-05-11 (post-static-analysis session)
**Total docs**: 194 .md files across `./` and `cumulus_baseline_2013/`

This is the **canonical entry point** for all reverse-engineering
documentation. Use this index to find the **current authoritative
source** for any topic — older docs in the parent directory may be
**superseded by newer cumulus_baseline_2013/** docs.

---

## 🎯 Quick lookup — what to read for what

| Goal | Read this |
|---|---|
| **Bring the chip out of reset** | `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` + `BCM_INIT_REGISTER_MAP.md` |
| **Understand the access stack** (MMIO/SCHAN/PAXB) | `cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md` |
| **Issue SCHAN transactions** | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| **Move packets bidirectionally** | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| **Program L3 routes** | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| **Program L2 entries (chip-side bits)** | `L2_ENTRY_FORMAT.md` (Feb 2026, verified via bcmcmd) |
| **Program L3 entries (chip-side bits)** | `L3_NEXTHOP_FORMAT.md` (Feb 2026, verified) |
| **Program VLAN entries (chip-side bits)** | `VLAN_TABLE_FORMAT.md` (Feb 2026, verified) |
| **Hash table SCHAN opcodes** | `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` |
| **Init Cumulus's way** (scripts decoded) | `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` |
| **Configure MMU/buffer pools** | `cumulus_baseline_2013/FP_MMU_AND_REMAINING.md` |
| **Configure FP TCAM (ACLs)** | `cumulus_baseline_2013/FP_MMU_AND_REMAINING.md` |
| **PHY bring-up + firmware** | `PHY_FIRMWARE_FUNCTIONS.md` + `cumulus_baseline_2013/PHY_ENTRY_CHAIN_AND_REMAINING.md` |
| **SerDes (Warpcore) init** | `SERDES_WC_INIT.md` (verified via GDB watchpoint) |
| **Port bring-up (XLPORT)** | `PORT_BRINGUP_REGISTER_MAP.md` |
| **PAXB sub-windows** | `PAXB_SUBWINDOW_MECHANISM.md` (in parent dir, verified) |
| **LED programming** | `LED_ARCHITECTURE.md` + `LED_CPU_INTERFACE.md` (May 2026) |
| **CPLD register map** | `cumulus_baseline_2013/ghidra-analysis/CPLD_REGISTER_MAP_FINAL.md` |
| **I²C / SFP access** | `CUMULUS_I2C_HARDWARE_INVENTORY.md` + `I2C_BUS_TOPOLOGY_AND_SFP_CONTROL.md` |
| **switchd FUSE control plane** | `cumulus_baseline_2013/fuse-explore/SWITCHD_SFS_INTERNALS.md` |
| **Current gap analysis** | `cumulus_baseline_2013/WHATS_MISSING.md` |

---

## 📁 Documentation hierarchy

### 🆕 Tier 1: Current canonical docs (cumulus_baseline_2013/, May 2026)

These are the most recent, comprehensive, statically-verified docs.
**Start here for any topic.**

| Doc | Coverage |
|---|---|
| `ACCESS_METHODS_DEFINITIVE_GUIDE.md` | **The 5-layer model**: MMIO/PAXB/CMICm/SCHAN/SDK |
| `CMIC_SCHAN_DMA_DEEP_DIVE.md` | SCHAN protocol, DMA channels, DCB format, opcodes |
| `BCM_INIT_STATIC_CHAIN.md` | bcm_init's 42-block dispatch order |
| `BCM_INIT_REGISTER_MAP.md` | 89 registers touched at init |
| `BLOCK_INIT_DEEP_DIVE.md` | common/port/field block-init internals |
| `ASIC_INIT_COOKBOOK.md` | rc.soc / rc.datapath_0 / config.bcm decoded |
| `ASIC_INIT_TRACE_DECODED.md` | strace timing per phase |
| `PACKET_FLOW_END_TO_END.md` | RX punt + TX inject, DCB lifecycle |
| `L3_L2_PROGRAMMING_FLOW.md` | netlink → switchd → BCM API → chip tables |
| `TABLE_ENTRY_HASH_OPS.md` | HASH_INSERT/LOOKUP/DELETE SCHAN opcodes (NEW finding!) |
| `FP_MMU_AND_REMAINING.md` | FP TCAM, MMU, VLAN, Mirror, Storm, Linkscan, KNET, PHY loader |
| `PHY_ENTRY_CHAIN_AND_REMAINING.md` | PHY entry chain + datapath-update + clagd + closeout |
| `WHATS_MISSING.md` | **Current gap status** (was: GAPS_FOR_CUSTOM_SWITCHD_SDK.md, etc.) |
| `GAP_ANALYSIS.md` | Higher-level gap analysis |
| `PROVEN_WORKING_CONFIG.md` | Known-good Cumulus 2.5.0 baseline at 10.1.1.212 |
| `PLATFORM_DAEMONS_REVERSE_ENGINEERED.md` | pwmd/smond/ledmgrd/portwd Python daemons |
| `SCHAN_AND_DMA_REFERENCE.md` | Earlier SCHAN doc — **see CMIC_SCHAN_DMA_DEEP_DIVE.md instead** |
| `fuse-explore/SWITCHD_SFS_INTERNALS.md` | switchd FUSE filesystem (SFS) |
| `fuse-explore/SWITCHD_FUSE_API.md` | Earlier FUSE doc — see SWITCHD_SFS_INTERNALS instead |

### Tier 2: Static-analysis artifacts (cumulus_baseline_2013/ghidra-analysis/)

Per-binary Ghidra decompilation + analysis. Reference these when you
need byte-level details:

| Doc | Coverage |
|---|---|
| `BDE_COMPLETE.md` | linux-kernel-bde + linux-user-bde — full ioctl table |
| `BDE_DRIVERS_DECODED.md` | BDE driver decomps (MMIO/DMA primitives) |
| `KERNEL_MODULES_COMPLETE.md` | linux-bde-i2c, linux-bde-tmon |
| `CPLD_REGISTER_MAP_FINAL.md` | Accton AS5610 CPLD register map |
| `BCM_SDK_INTERNALS.md` | BCM API trampoline pattern, lock helpers |
| `FULL_CHIP_ACCESS_STACK.md` | API→port_validate→soc_reg32_get→SCHAN→MMIO |
| `CHIP_PRIMITIVES_AND_REG_TABLE.md` | 36,896 register names extracted |
| `PACKET_IO_HOOKS.md` | switchd RX callback decompile |
| `PHY_FIRMWARE_FUNCTIONS.md` | 43 PHY firmware functions mapped |
| `PHY_MMIO_MAP.md` | PHY MMIO register access patterns |
| `SWITCHD_BCM_API_INVENTORY.md` | 128 BCM API addresses labeled |
| `SWITCHD_DECOMPILED_BCM_APIS.md` | 128 API decompiled into categories |
| `L3_ROUTE_PROGRAMMING.md` | L3 route programming details (earlier) |
| `CL_ACLTOOL_FLOW.md` | cl-acltool → FUSE → BCM FP |
| `GHIDRA_FINDINGS.md` | Initial Ghidra exploration findings |

### Tier 3: Chip-side bit layouts (parent dir, Feb 2026, verified via bcmcmd)

**Critically valuable** — these were verified on a live chassis with
`bcmcmd listmem` + `dump raw` + write-back tests. They tell you the
exact bit positions inside each table entry.

| Doc | Coverage |
|---|---|
| `L2_ENTRY_FORMAT.md` | L2_ENTRY (0x07120000) + L2_USER_ENTRY (0x06168000) bit layout |
| `L3_NEXTHOP_FORMAT.md` | L3_DEFIP/L3_ECMP/ING_L3_NEXT_HOP/EGR_L3_NEXT_HOP/EGR_L3_INTF |
| `L3_IPV6_FORMAT.md` | L3_DEFIP_128 + L3_DEFIP double-wide (IPv6 LPM) |
| `VLAN_TABLE_FORMAT.md` | VLAN (ingress) + EGR_VLAN (egress) bit layouts |
| `ECMP_GROUP_LAYOUT_FROM_01a1572c.md` | L3_ECMP_GROUP table layout |
| `STATS_COUNTER_FORMAT.md` | XLMAC stat-counter offsets, port→block/lane map |
| `SCHAN_FORMAT_ANALYSIS.md` | S-channel command word format (older view, see CMIC_SCHAN_DMA_DEEP_DIVE) |

### Tier 4: Hardware / platform reference (parent dir, still valid)

| Doc | Coverage |
|---|---|
| `PAXB_SUBWINDOW_MECHANISM.md` | iProc PAXB IMAP mechanism (Mar 27) |
| `PORT_BRINGUP_REGISTER_MAP.md` | XLPORT block addresses, MAC registers |
| `SERDES_WC_INIT.md` | Warpcore SerDes MDIO init (GDB-watchpoint captured) |
| `WARPCORE_TX_CONFIG_CAPTURED.md` | Warpcore TX driver configs from live chassis |
| `WARPCORE_SPEED_ENCODING_ANALYSIS.md` | Warpcore lane speed encoding |
| `10G-LINK-BRINGUP-CHECKLIST.md` | 10G link bring-up checklist (May 9) |
| `802.3-10G-MDIO-reference.md` | IEEE 802.3 10G MDIO reference |
| `CHIP_RESET_RE_FINDINGS.md` | BCM56846 soft reset (SCHAN_CTRL=0x92) findings |
| `LED_ARCHITECTURE.md` | LED uController architecture (May 9) |
| `LED_CPU_INTERFACE.md` | LED CPU interface (May 9) |
| `WC40-TX-DRIVER-ANALYSIS.md` | Warpcore 40G TX driver analysis |
| `AS5610_52X_BOARD_COMPONENT_MAP.md` | Board-level component map |
| `CUMULUS_I2C_HARDWARE_INVENTORY.md` | I2C device inventory |
| `I2C_BUS_NUMBER_MAPPING.md` | I2C bus number assignments |
| `I2C_BUS_TOPOLOGY_AND_SFP_CONTROL.md` | I2C topology + SFP control |
| `SFP_TURNUP_AND_ACCESS.md` | SFP+ port turnup procedure |
| `QSFP_BREAKOUT_CONFIGURATION.md` | QSFP+ breakout configs |
| `SYSTEM_BOOT_AND_I2C.md` | System boot + I2C order |
| `PLATFORM_ENVIRONMENTAL_AND_PSU_ACCESS.md` | Fans, PSUs, temp sensors |
| `as5610_retimer.md` | DS100DF410 retimer details |

### Tier 5: ONIE / NOS reference (parent dir, still valid)

| Doc | Coverage |
|---|---|
| `ONIE_AND_INSTALLER_FORMATS_DEEP_DIVE.md` | ONIE installer formats |
| `ONIE_AS5610_52X_MACHINE_REFERENCE.md` | Machine ID for ONIE |
| `ONIE_BOOT_AND_PARTITION_LAYOUT.md` | ONIE boot + partition layout |
| `ONL_DEB8_PPC_AS5610_REFERENCE.md` | OpenNetworkLinux Debian 8 PPC reference |
| `ONLP_AS5610_52X_PLATFORM_REFERENCE.md` | ONLP platform reference |
| `OPENMDK_BCM56846_REFERENCE.md` | OpenMDK reference for BCM56846 |
| `OPEN_NOS_IMPLEMENTATION_FINDINGS.md` | Open NOS implementation findings |
| `OPENNSL_LIBRARY_EXTRACTION_RESULTS.md` | OpenNSL library extraction |
| `OPENNSL_LIBRARY_EXTRACTION_STATUS.md` | OpenNSL extraction status |
| `SUPPORTED_CHIPS.md` | List of supported BCM chips |
| `AS5610_52X_ECOSYSTEM_AND_EXTERNAL_REFERENCES.md` | External references |
| `CUMULUS_VS_OPENNSL_ARCHITECTURE.md` | Cumulus vs OpenNSL comparison |
| `INFRASTRUCTURE.md` / `INFRASTRUCTURE_REFERENCE.md` | Lab infrastructure |

### Tier 6: Procedure / runbook (parent dir, still useful)

| Doc | Coverage |
|---|---|
| `MANUAL_SSH_KEY_TO_SWITCH.md` | SSH key install procedure |
| `SSH_KEY_AUTH_SWITCH.md` | SSH key auth setup |
| `LIVE_SWITCH_CONFIG_10.1.1.233.md` | Live config from previous chassis |
| `CAPTURE_RESULTS_20260322.md` | Capture run results |
| `DEBUGGING_LOG_20260323.md` | Debugging session log |
| `PUBLISH_AND_REDACTION.md` | Doc redaction guide for publication |

### Tier 7: SUPERSEDED — older docs replaced by Tier 1

**Don't read these for current information.** They contain valid
historical analysis but newer docs have better coverage. Listed for
completeness:

| Old doc | Superseded by |
|---|---|
| `ASIC_INIT_AND_DMA_MAP.md` | `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` |
| `asic-init-sequence.md` | `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` |
| `initialization-sequence.md` | `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` |
| `BDE_CMIC_REGISTERS.md` | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| `SCHAN_AND_RING_BUFFERS.md` | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| `SCHAN_AND_L2_ANALYSIS.md` | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` + `TABLE_ENTRY_HASH_OPS.md` |
| `WRITE_MECHANISM_ANALYSIS.md` | `cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md` |
| `L2_WRITE_PATH_*.md` (3 files) | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `L2_TABLE_ACCESS_ANALYSIS.md` | `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` |
| `L2_PAYLOAD_FROM_DUMPS.md` | `L2_ENTRY_FORMAT.md` (Tier 3, kept) |
| `L2_INDEX_SOURCE_FROM_DUMPS.md` | `L2_ENTRY_FORMAT.md` |
| `L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md` | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| `L3_ECMP_VLAN_*.md` (4 files) | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `L3_TABLE_WRITE_CHAIN_DUMP.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `L3_TABLE_FILL_FROM_014a51e8.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `L3_BUFFER_LAYOUT_FROM_DUMPS.md` | `L3_NEXTHOP_FORMAT.md` (Tier 3, kept) |
| `L3_NEXT_STEPS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `RC_DATAPATH_GENERATION.md` | `cumulus_baseline_2013/PHY_ENTRY_CHAIN_AND_REMAINING.md` section 2 |
| `PACKET_IO_VERIFIED.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `cumulus-packet-io-architecture.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `PKTIO_BDE_DMA_INTERFACE.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `packet-flow-analysis.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `DMA_DCB_LAYOUT_FROM_KNET.md` | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| `DESCRIPTOR_BUFFER_FILL_ANALYSIS.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `TABLE_*.md` (6 files: TABLE_NAME_MAPPING, TABLE_ID_MAPPING_ANALYSIS, etc.) | `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` + Tier 3 bit-layout docs |
| `netlink-handlers.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `netlink-message-flow.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `RE_COMPLETE.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `REVERSE_ENGINEERING_STATUS_REPORT.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `REVERSE_ENGINEERING_PROGRESS_SUMMARY.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `STACK_READINESS_AS5610.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `PATH_B_COMPLETION_STATUS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `PATH_B_INFORMATION_CHECKLIST.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `GAPS_FOR_CUSTOM_SWITCHD_SDK.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `CUSTOM_NOS_GAP_ANALYSIS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `GEMINI_RE_GAPS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `GEMINI_RE_SOLUTIONS.md` | `cumulus_baseline_2013/WHATS_MISSING.md` |
| `FINAL_ANALYSIS_SUMMARY.md` | This index doc |
| `ANALYSIS_SUMMARY.md` | This index doc |
| `ANALYSIS_RUN_2026-02-18.md` | `cumulus_baseline_2013/ASIC_INIT_TRACE_DECODED.md` |
| `SESSION_SUMMARY_2026-02-19.md` | This index doc |
| `RUNTIME_TRACING_*.md` (3 files) | `cumulus_baseline_2013/tools/lubde-trace/README.md` |
| `TRACING_PACKET_IO_GUIDE.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `HOW_TO_RUN_FINDPACKETTXPATH.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| `REGISTER_EXTRACTION_*.md` (3 files) | `cumulus_baseline_2013/ghidra-analysis/CHIP_PRIMITIVES_AND_REG_TABLE.md` |
| `GHIDRA_REGISTER_TABLE_ANALYSIS.md` | `cumulus_baseline_2013/ghidra-analysis/CHIP_PRIMITIVES_AND_REG_TABLE.md` |
| `FUNCTION_DUMP_ANALYSIS.md` | `cumulus_baseline_2013/ghidra-analysis/SWITCHD_BCM_API_INVENTORY.md` |
| `FUNCTION_STRINGS_ANALYSIS.md` | `cumulus_baseline_2013/ghidra-analysis/SWITCHD_BCM_API_INVENTORY.md` |
| `API_TO_DISPATCHER_CALL_CHAIN.md` | `cumulus_baseline_2013/FULL_CHIP_ACCESS_STACK.md` |
| `DISPATCHER_CALL_CHAIN_SUMMARY.md` | `cumulus_baseline_2013/FULL_CHIP_ACCESS_STACK.md` |
| `COMPLETE_CALL_CHAIN_DOCUMENTATION.md` | `cumulus_baseline_2013/FULL_CHIP_ACCESS_STACK.md` |
| `switchd-binary-analysis.md` | `cumulus_baseline_2013/ghidra-analysis/SWITCHD_BCM_API_INVENTORY.md` |
| `switchd-dynamic-analysis-summary.md` | `cumulus_baseline_2013/ASIC_INIT_TRACE_DECODED.md` |
| `switchd-init-trace.md` | `cumulus_baseline_2013/ASIC_INIT_TRACE_DECODED.md` |
| `sdk-api-list.md`, `sdk-api-mapping.md` | `cumulus_baseline_2013/ghidra-analysis/SWITCHD_DECOMPILED_BCM_APIS.md` |
| `bcm-config-format.md` | `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` |
| `config-to-register-map.md` | `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` |
| `interface-creation-analysis.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `interface-creation-mechanism.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `COMPLETE_INTERFACE_ANALYSIS.md` | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| `architecture-diagrams.md` | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` (has diagrams) |
| `api-patterns.md` | `cumulus_baseline_2013/ghidra-analysis/BCM_SDK_INTERNALS.md` |
| `file-access-pattern.md` | `cumulus_baseline_2013/ASIC_INIT_TRACE_DECODED.md` |
| `index.md` | This document |
| `README.md` (parent dir) | Still valid as project overview; this is the deeper index |

---

## 📊 Coverage by area

### ✅ Fully covered (multiple authoritative docs)

| Area | Canonical doc |
|---|---|
| Chip init flow | `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` |
| SCHAN protocol | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| PAXB sub-windows | `PAXB_SUBWINDOW_MECHANISM.md` |
| DMA / DCB | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` + `PACKET_FLOW_END_TO_END.md` |
| Packet RX/TX | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| L2 entry layout | `L2_ENTRY_FORMAT.md` (chip-side) + `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` (host-side) |
| L3 entry layout | `L3_NEXTHOP_FORMAT.md` + `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` |
| VLAN tables | `VLAN_TABLE_FORMAT.md` |
| ECMP | `ECMP_GROUP_LAYOUT_FROM_01a1572c.md` + `L3_NEXTHOP_FORMAT.md` |
| FP TCAM | `cumulus_baseline_2013/FP_MMU_AND_REMAINING.md` section 1 |
| MMU buffer pool | `cumulus_baseline_2013/FP_MMU_AND_REMAINING.md` section 2 + `ASIC_INIT_COOKBOOK.md` |
| BDE kernel module | `cumulus_baseline_2013/ghidra-analysis/BDE_COMPLETE.md` |
| switchd FUSE | `cumulus_baseline_2013/fuse-explore/SWITCHD_SFS_INTERNALS.md` |
| PHY firmware | `PHY_FIRMWARE_FUNCTIONS.md` |
| SerDes init | `SERDES_WC_INIT.md` |
| LED uC | `LED_ARCHITECTURE.md` |
| Port bring-up | `PORT_BRINGUP_REGISTER_MAP.md` |
| CPLD | `cumulus_baseline_2013/ghidra-analysis/CPLD_REGISTER_MAP_FINAL.md` |

### ⚠️ Partial coverage (sufficient for EdgeNOS)

- 39 small block-init helpers — addresses + sizes known, not individually decompiled
- PHY entry-chain functions (0xE301, 0xE2CD, 0xE3FD) — addresses known, not disassembled
- Per-register field bit positions — names known via 62K table, exact bit offsets not extracted

### ❌ Not in any of our docs (use external)

- mstpd, ptmd — not in captured rootfs, use upstream packages
- cl-license validation bytes — clock-rolled workaround works
- Full BCM SDK private headers — never public

---

## 🚀 For an EdgeNOS implementer starting fresh

Read in this order:

1. `README.md` (parent dir) — project overview
2. `cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md` — the foundation
3. `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` — register access
4. `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` — init sequence
5. `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` — what to set
6. `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` — packet I/O
7. `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` — forwarding tables
8. `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` — direct table programming
9. Tier 3 chip-side docs (bit layouts) as you implement each table

For each implementation step, look at:
- **Tier 1** doc for the high-level "what + why"
- **Tier 2** decomp for the byte-level "how Cumulus does it"
- **Tier 3** for the chip-side "what bits to put in the entry"

---

## 🔄 Update process

This index was generated 2026-05-11 after a comprehensive
static-analysis session. If you add a new doc:

1. Add it to the relevant **Tier 1** or **Tier 2** section
2. If it supersedes an older doc, add it to **Tier 7** with the new
   canonical pointer
3. Update **Quick lookup** if the topic changes destination

---

*If this index ever gets out of date, regenerate by listing all .md
files and re-categorizing.*

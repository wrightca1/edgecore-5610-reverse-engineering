# Path B — What’s left and next steps

**Source**: Derived from [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md). Use this for a concise “what to do next” list.

---

## Cumulus vs OpenNSL

**Cumulus does not use OpenNSL.** The live switch (10.1.1.233) runs Cumulus Linux with its own SDK/API. Implications:

- **GDB breakpoints at OpenNSL API addresses** on Cumulus switchd will never hit — N/A for API→table-ID tracing.
- **libopennsl** remains the **ASIC reference** — Ghidra on libopennsl extracts S-Channel format, table layouts, L2/L3 entry formats. This is BCM56846-level; applies regardless of Cumulus vs ONL.
- **Strace on Cumulus** remains valid — port-up, packet I/O, BDE mmap capture low-level syscalls; same hardware/BDE.
- **Runtime API tracing** for OpenNSL would require the **ONL switch (10.1.1.222)** if it uses OpenNSL, or skip and rely on Ghidra static analysis.

---

## Status at a glance

| Section | Have | Partial | Need | Blocker for… |
|--------|------|---------|------|----------------|
| **1** BDE/device | 1.1–1.6 | — | — | — |
| **2** Registers | 2.1–2.5, **2.3** S-Chan | — | **2.6** port/SerDes, **2.7** pipeline regs | Port up |
| **3** Tables | 3.1–3.2 | **3.3–3.8** L2/L3/ECMP layout + write path | **3.10** hash/index | L2/L3 programming |
| **4** Packet I/O | 4.1–4.2, **4.3** TX path, **4.6** buffer | 4.4–4.5, 4.7–4.8 | — | Full packet path |
| **5** Port bringup | 5.1 | 5.4 (breakout) | **5.2–5.3** port/SerDes regs | Link up |
| **6** Init | 6.1–6.3 | 6.4–6.5 | — | Optional tuning |
| **7** Platform | — | 7.2 (LED) | 7.1 (I2C) | Full AS5610 |
| **8** Errors | 8.1 | 8.2–8.3 | — | Production hardening |

**Must-have to ship**: §2.3 (S-Chan), §3.3–3.8 (tables), §4.6 (buffer), §5.2–5.3 (port up). §2.3, §4.3, §4.6 **DONE**. §3.3–3.8 PARTIAL. §5.2–5.3 NEED.

**Primary path**: Ghidra on libopennsl (ASIC reference) + strace on Cumulus (low-level behavior). No OpenNSL runtime tracing on Cumulus.

---

## Recommended next steps (actionable)

| Priority | What | How |
|----------|------|-----|
| **L2** | Finish ASIC L2_USER_ENTRY layout (3.3, 3.8) | In Ghidra/dumps: annotate **0181e718** (and **0181c73c**) for every **stw/stb/sth** to r29 (buffer) or r29+offset → table: byte offset → field (MAC, VLAN, port, flags). See [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md). **Done**: store table + **descriptor formulas** (0x4=width, 0x6=word/bit index, 0x8=offset; input 0x28=word index); layout is descriptor-driven bitfield. |
| **Port** | Name BAR diff registers (5.2–5.3) | Search SDK/OpenNSL headers for **0x46f8, 0x4818, 0x4830, 0x4870, 0x4928, 0x49b8, 0x4a38, 0x4b38**; or run BAR diff on swp3 and compare. [traces/BAR_DIFF_PORT_UP_10.1.1.233.md](traces/BAR_DIFF_PORT_UP_10.1.1.233.md). **Done**: swp3 diff run (6 words: 0x46f8, 0x4820, 0x4870, 0x4880, 0x4928, 0x49b8). |
| **L3** | Per-table layout (3.4–3.7) | For table IDs 0x22d3, 0x2c32, 0x1559–0x155e: trace from FUN_018d62ec/018d43e4, list **stores** into 0x224-byte buffer → field layout. [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md). **Done**: [L3_BUFFER_LAYOUT_FROM_DUMPS.md](L3_BUFFER_LAYOUT_FROM_DUMPS.md) — 014a51e8/0170b700 stores; 0x0=op, 0x4/0x44=entry array, 0x84/0x9c/0xb4/0xcc=indices, 0x204–0x214=format constants. |
| **L3** | Write mechanism | Confirm FUN_01876f10 (or 01876c30’s handler) uses S-Chan (FUN_007042f0) or direct BAR; trace one L3 write to completion. **Checked**: 01876f10 does not call 007042f0 (→01876ee0→01876c30→bctrl); S-Chan would be in indirect handler. |
| **Optional** | Hash/index (3.10) | In Ghidra, find hash/index computation before L2/L3 table insert; document key and index derivation. **L2 done**: [L2_INDEX_SOURCE_FROM_DUMPS.md](L2_INDEX_SOURCE_FROM_DUMPS.md) — 01cc2f2c retry 0..5, 00948700 passes -1; no hash in these paths. |

**Scripts**: `run-dump-func-on-build-server.sh libopennsl <addr> [insn_limit]`, `run-bar-diff-port-up-10.1.1.233.sh [swpN]`, `run-find-l3-table-callers-on-build-server.sh`.

---

## Next steps (in order)

### 1. Packet TX path (4.3) — **done**

- **libopennsl**: opennsl_tx → FUN_0080ba18 → FUN_0086fe6c → FUN_01393e80 → FUN_0070c994 → FUN_013949c0. [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md), [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md).
- Custom switchd implements TUN read → opennsl_tx; Cumulus does not use OpenNSL.

---

### 2. S-Channel format (closes 2.3; required for tables) — **done**

- **Ghidra**: FUN_00703dc0 encodes S-Chan command word: `(val & 0x7fff) | 0x28000000`. See [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md) §S-Channel command word format.

---

### 3. L2 entry layout + write path (closes 3.3, 3.8) — **partial**

- **API layout** (opennsl_l2_addr_t) and **call chain** FUN_00946a00→FUN_00948700→FUN_01cc2f2c in [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md). **What**: L2 entry layout (MAC, VLAN, port, valid/static/hit, size, byte order) and how it’s written (S-Chan vs direct BAR).
- **Remaining**: ASIC L2_USER_ENTRY format — step-by-step in [L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md](L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md). From dumps: [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md) — L2 write uses **table ID 0x1547**, **0x24-byte** payload via FUN_01876f10; FUN_01cc2f2c builds a stack struct; decode 01cbd2e0 for full field layout.

---

### 4. L3 / ECMP / VLAN (3.4–3.7, 3.9)

- **What**: L3 route, egress, host, ECMP group layouts and write path; VLAN_XLATE layout.
- **Have**: [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md), [libopennsl-table-dispatcher-analysis.txt](../build-server/opennsl/sdk-deep-extract/libopennsl-table-dispatcher-analysis.txt). Table IDs 0x22d3/0x22ca (L3_DEFIP), 0x2c32/0x2c33 (L3_ECMP), 0x1559–0x155e, etc.
- **Next**: [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md) — per-table layout (stores into 0x224-byte struct), write mechanism (S-Chan vs BAR), ECMP/VLAN_XLATE, hash/index. **ECMP**: [ECMP_GROUP_LAYOUT_FROM_01a1572c.md](ECMP_GROUP_LAYOUT_FROM_01a1572c.md). **VLAN_XLATE**: FUN_018d4770, **FUN_014aec60** — table ID **0x8a6**, uses **0181f7dc** (same 0x24-byte L2 buffer path) then 01876f10.

---

### 5. Port bringup registers (closes 5.2–5.3)

- **What**: Minimal register sequence to bring one port up (enable, speed, duplex) and SerDes lane config.
- **Done**: Strace + perf port-up trace; **BAR diff** during port up. See [traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md), [traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md](traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md), [traces/BAR_DIFF_PORT_UP_10.1.1.233.md](traces/BAR_DIFF_PORT_UP_10.1.1.233.md) — 14 BAR0 offsets changed (0x46f8–0x4b38); candidates for port/SerDes.
- **How to close further**: (B) Ghidra on Cumulus switchd for port paths; (C) OpenNSL handlers at -0x5fe0/-0x68b0; correlate BAR offsets with SDK register names.
- **Scripts**: `run-port-up-trace-10.1.1.233.sh`, `run-perf-port-up-10.1.1.233.sh`, **`run-bar-diff-port-up-10.1.1.233.sh [interface]`** (dump /dev/mem before/after port up, diff).

---

### 6. Runtime Tracing — **strace valid; OpenNSL GDB N/A on Cumulus**

- **Strace** (port-up, packet I/O, BDE mmap): Done; analysis in [traces/RUNTIME_TRACE_ANALYSIS_10.1.1.233.md](traces/RUNTIME_TRACE_ANALYSIS_10.1.1.233.md). Valid on Cumulus (low-level syscalls).
- **GDB breakpoints at OpenNSL APIs**: **N/A on Cumulus** — Cumulus does not use OpenNSL; breakpoints never hit. Scripts exist but are for ONL switch (10.1.1.222) if it uses OpenNSL.
- **Path forward**: Rely on Ghidra static analysis of libopennsl for table layouts; strace for low-level behavior.

### 7. Packet buffer format (4.6) — **done**

- **opennsl_pkt_t**: Layout from OpenNSL `hal/include/opennsl/pkt.h`; offset 0x8 = packet data. [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md).
- Trace lengths: 42, 60, 82, 122 bytes (Ethernet frames).

---

### 7. BDE mmap vs ioctl (1.5–1.6) — optional early

- **What**: Whether switchd uses ioctl only or mmap + direct read/write for registers; how it gets BAR base.
- **How**: Strace switchd at startup (open, mmap, ioctl) and inspect BDE kernel or user code for LUBDE_CPU_READ_REG/WRITE and GET_DEVICE.

---

### 8. Platform (7.1–7.2) — when needed for full AS5610

- I2C bus/mux for SFP/QSFP; LED front-panel mapping. ONLP or vendor docs; existing ONL/platform code.

---

## Done (no action needed)

- **Packet I/O trace (10.1.1.233)**: Full strace captured; extraction in [traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md](traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md). BDE ioctls (WAIT_FOR_INTERRUPT, SEM_OP, USLEEP), TUN read/write on fd 20, thread roles, and canonical TX/RX sequences are documented.
- **Function dumps**: [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md) — FUN_0080ba18 (opennsl_tx callee), FUN_1000b638 (switchd S-Channel anchor). DumpFunctionCode runs on build server; FindL2Writes found 0 scalar L2 stores (PowerPC uses register+offset).
- **Port-up trace**: [PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md) — BDE ioctls 0x20004c08–0x20004c0b decoded. Strace re-run 2026-02-19 (10982 lines); perf port-up 2026-02-20 (~23.5k samples).
- **Port-up perf trace**: [PORT_UP_PERF_ANALYSIS_10.1.1.233.md](traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md). **BAR diff**: [BAR_DIFF_PORT_UP_10.1.1.233.md](traces/BAR_DIFF_PORT_UP_10.1.1.233.md) — swp1: 14 offsets; swp2: 5 offsets (overlap 0x49e8, 0x4a38, 0x4a40, 0x4a50, 0x4b38).
- **BDE mmap (1.5–1.6)**: [BDE_MMAP_ANALYSIS_10.1.1.233.md](traces/BDE_MMAP_ANALYSIS_10.1.1.233.md) — switchd mmaps /dev/mem at 0x04000000 and 0xa0000000; register access via mmap, not ioctl.
- **L2 table access**: [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md) — L2_USER_ENTRY (0x180c200) xrefs. [L2_PAYLOAD_FROM_DUMPS.md](L2_PAYLOAD_FROM_DUMPS.md) — table ID 0x1547, 0x24-byte payload; 01cbd2e0 input (flags 0x0, MAC 0x8, VLAN 0x14, port 0x2c); 0181f080 → 0181e718 fills buffer (r29); descriptor-driven layout.
- **S-Channel call chain**: FUN_007042f0 / FUN_00704790 / FUN_00704784 → FUN_00703dc0 (oris 0x2800). [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md).
- **L2 call chain**: FUN_00946a00 → FUN_00948700 → FUN_01cc2f2c. Dumped FUN_00946a00, FUN_0092c64c, FUN_009307a4, FUN_01d2f1f0, FUN_00973f6c, FUN_0094e450, FUN_00a68ef0, FUN_0089c230, FUN_00b2bbb4, FUN_009af1fc. S-Chan callers: FUN_007042f0, FUN_00704790, FUN_00704784.
- **Runtime trace analysis**: [traces/RUNTIME_TRACE_ANALYSIS_10.1.1.233.md](traces/RUNTIME_TRACE_ANALYSIS_10.1.1.233.md) — consolidated BDE ioctl summary.
- **L3 table callers**: [libopennsl-l3-table-callers.txt](../build-server/opennsl/sdk-deep-extract/libopennsl-l3-table-callers.txt) — FUN_018d7ad4→FUN_018d62ec chain.
- **Port bringup**: [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md) — port API callees and dispatch pattern.
- **L2 callers**: FUN_00946a00→FUN_0092c64c, FUN_009307a4. Dumped L2 handlers: 0094e450, 00a68ef0, 0089c230, 00b2bbb4, 009af1fc. S-Chan callers: FUN_007042f0, FUN_00704790, FUN_00704784. See [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md), [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md).
- **Completion summary**: [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md)

---

## References

- **Infrastructure (hosts, paths, workflows)**: [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md)
- **Checklist**: [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md)
- **Suggested order**: §11 of checklist (Packet I/O → BDE/DMA → S-Chan → L2 → L3 → Port bringup → Registers).
- **Ghidra TX path**: [HOW_TO_RUN_FINDPACKETTXPATH.md](HOW_TO_RUN_FINDPACKETTXPATH.md), `scripts/reverse-engineering/ghidra-find-packet-tx-path.sh`
- **Trace extraction**: [traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md](traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md)
- **S-Channel / DMA**: [SCHAN_AND_RING_BUFFERS.md](SCHAN_AND_RING_BUFFERS.md), [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md)
- **Tables**: [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md), [TABLE_MEMORY_ANALYSIS.md](TABLE_MEMORY_ANALYSIS.md)

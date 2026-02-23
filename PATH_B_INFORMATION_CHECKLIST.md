# Path B: Minimal Custom SDK — Information Checklist

**Purpose**: Ensure you have (or know how to get) every piece of information needed to build a minimal custom SDK and switchd for the Edgecore AS5610-52X (BCM56846), without relying on OpenNSL for data path or table programming.

**How to use**: Work through each section. Mark items **HAVE** / **NEED** / **PARTIAL**. Use "How to get" to close NEEDs.

### Next actions (to close remaining NEEDs)

See **[PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md)** for a concise list and order.

**Note**: Cumulus does not use OpenNSL. Use libopennsl as ASIC reference (Ghidra); use Cumulus for strace only.

1. ~~**Live switch trace**~~ **Done.** [traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md](traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md)
2. ~~**Packet TX path (4.3)**~~ **Done.** [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md), [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md)
3. ~~**S-Channel (2.3)**~~ **Done.** [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md), [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
4. ~~**Packet buffer (4.6)**~~ **Done.** [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md)
5. **L2/L3 layouts + write path (3.3–3.8)**: PARTIAL. [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md), [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md)
6. **Port bringup**: Strace + perf port-up done. See [traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md), [traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md](traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md). To close 5.2–5.3: mmap trace or Ghidra on switchd. [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md)

### At a glance (Path B must-haves)

| Area | Have | Partial | Need | Notes |
|------|------|---------|------|--------|
| BDE/device | 1.1–1.6 | — | — | §1 |
| Registers | 2.1–2.5, **2.3** S-Chan format | — | 2.6 port/SerDes, 2.7 pipeline | §2 |
| Tables | 3.1–3.2 | **3.3–3.8** layouts + write path | 3.10 hash/index | §3 |
| Packet I/O | 4.1–4.2, **4.3** TX path, **4.6** buffer | 4.4 RX, 4.5 BDE, 4.7–4.8 DCB/ring | — | §4 |
| Port bringup | 5.1 | 5.4 breakout | 5.2–5.3 reg sequence | §5 |
| Init/config | 6.1–6.3 | 6.4–6.5 | — | §6 |
| Platform | — | 7.2 LED | 7.1 I2C | §7 |

---

## 1. BDE and device access

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 1.1 | Device node: `/dev/linux-user-bde` (major 126) | HAVE | linux-bde.h, WHAT_MAKES_THE_SWITCH_WORK.md |
| 1.2 | Open device, basic ioctl list (LUBDE_* in linux-user-bde.h) | HAVE | `systems/bde/linux/user/kernel/linux-user-bde.h` |
| 1.3 | Register read/write ioctls: LUBDE_CPU_READ_REG (24), LUBDE_CPU_WRITE_REG (23) | HAVE | linux-user-bde.h; args in lubde_ioctl_t (dev, d0/d1 = addr/data, etc.) |
| 1.4 | LUBDE_GET_DMA_INFO (5), LUBDE_GET_DEVICE (2), LUBDE_GET_NUM_DEVICES (1) | HAVE | linux-user-bde.h |
| 1.5 | PCI BAR mapping: BAR0 = ASIC registers (e.g. 256KB); how userland gets base address | HAVE | BDE_MMAP_ANALYSIS_10.1.1.233.md: switchd mmaps /dev/mem at 0x04000000 (64MB) and 0xa0000000 (256KB). |
| 1.6 | How register read/write is used: ioctl with (dev, addr, value) or mmap + direct read/write | HAVE | BDE_MMAP_ANALYSIS_10.1.1.233.md: mmap + direct read/write (not per-access ioctl). |

**How to get 1.5–1.6**: Strace switchd at startup (open, ioctl, mmap). Inspect BDE kernel module for how it implements LUBDE_CPU_READ_REG/WRITE and whether it exposes a base address for mmap.

---

## 2. Register map (for direct and S-Channel access)

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 2.1 | CMIC/CMICm/CMICd offsets (IRQ_STAT, IRQ_MASK, CMCx_*) | HAVE | SDK_REGISTER_MAP.md, BDE_CMIC_REGISTERS.md, linux-user-bde.c |
| 2.2 | S-Channel: CMIC_CMC0_SCHAN_CTRL = 0x32800; CMC0 base 0x31000 | HAVE | SCHAN_AND_RING_BUFFERS.md, SDK_REGISTER_MAP.md |
| 2.3 | S-Channel command/response format (opcodes, data words, poll/completion) | HAVE | [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md), [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md). FUN_00703dc0 encodes command word `0x2800XXXX` (val masked and ORed with 0x28000000). |
| 2.4 | LED register offsets | HAVE | SDK_REGISTER_MAP.md |
| 2.5 | DMA ring registers: DMA_CTRL, DMA_DESC0, DMA_HALT_ADDR (0x31140, 0x31158, 0x31120) | HAVE | SCHAN_AND_RING_BUFFERS.md |
| 2.6 | Port/SerDes register blocks (per-port base or block layout) | NEED | Register dump during port up; or OpenNSL/soc port code |
| 2.7 | Pipeline / buffer / stats register set (full list) | NEED | Ghidra extraction; register dump; OpenNSL/soc |

**How to get 2.3**: Ghidra: find code that writes to 0x32800 (or S-Chan symbol); decode opcode and data layout. Or capture schan traffic (bcmcmd schan) and correlate with SDK.

**How to get 2.6–2.7**: Run Cumulus, script getreg/setreg (or /dev/mem read) before/after “port up” and during init; diff. Or analyze OpenNSL port/pipeline code.

---

## 3. Table memory and programming

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 3.1 | Table memory region 0x01000000–0x01ffffff (16MB) | HAVE | TABLE_MEMORY_ANALYSIS.md, SDK_REGISTER_MAP.md |
| 3.2 | Table names → addresses (L2_ENTRY, L2_USER_ENTRY, L3_DEFIP, L3_ECMP, VLAN_XLATE, ECMP) | HAVE | TABLE_NAME_MAPPING.md, opennsl-table-name-to-addr-xref.txt |
| 3.3 | L2 entry layout: MAC, VLAN, port, valid/static/hit, entry size, byte order | PARTIAL | [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md). opennsl_l2_addr_t + call chain FUN_00946a00→FUN_00948700→FUN_01cc2f2c. ASIC L2_USER_ENTRY format needs S-Chan decode. |
| 3.4 | L3 route (DEFIP) layout: prefix, mask, egress id, next-hop, entry size | PARTIAL | [L3_TABLE_WRITE_CHAIN_DUMP.md](L3_TABLE_WRITE_CHAIN_DUMP.md). FUN_018d7ad4→FUN_018d62ec→FUN_018d43e4; table IDs 0x22d3/0x22ca. OpenNSL types + Ghidra. |
| 3.5 | L3 egress layout: port, MAC, entry size | PARTIAL | Same chain as 3.4; table IDs 0x2c32/0x2c33 (L3_ECMP). |
| 3.6 | L3 host layout | PARTIAL | Same chain; table IDs 0x1559–0x155e, 0x1599, 0x2c24, 0x15a5. |
| 3.7 | ECMP group layout and how it links to egress/next-hop | PARTIAL | FUN_01a1572c references L3_ECMP; table IDs 0x6418/0x6419/0x8a8. |
| 3.8 | How tables are written: S-Channel memory write vs direct BAR access vs other | PARTIAL | [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md). S-Chan via FUN_00703dc0; table write via FUN_01876f10, FUN_018d62ec. |
| 3.9 | VLAN table (VLAN_XLATE) layout and write path | PARTIAL | Addresses have; layout and write path NEED |
| 3.10 | Hash/index computation for L2 (and L3 if hash-based) | NEED | Ghidra on L2/L3 add; or SDK/soc docs |

**How to get 3.3–3.10**: (1) OpenNSL headers give logical fields. (2) Ghidra: find functions that reference both table name string and table address; decode how they build the entry and which memory/register they write. (3) Optional: dump table on live switch and reverse from known entries.

---

## 4. Packet I/O (TX and RX)

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 4.1 | Flow: TUN fd ↔ switchd ↔ BDE/SDK ↔ ASIC | HAVE | PACKET_IO_VERIFIED.md |
| 4.2 | No KNET; TUN only; switchd has 52 TUN fds + BDE fd | HAVE | PACKET_IO_VERIFIED.md, NO_KNET_ARCHITECTURE |
| 4.3 | Exact TX path: TUN read → which BDE/SDK call(s) → ASIC (buffer, length, port) | HAVE | [FUNCTION_DUMP_ANALYSIS.md](FUNCTION_DUMP_ANALYSIS.md), [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md). opennsl_tx → FUN_0080ba18 → FUN_0086fe6c → FUN_01393e80 → FUN_0070c994 → FUN_013949c0. Strace: read(fd=20)=42/82/122. Custom switchd implements TUN read → opennsl_tx. |
| 4.4 | Exact RX path: ASIC punt → BDE → switchd → which call → TUN write | PARTIAL | **Observed** `write(fd=20, buf, len)=60/82` to `/dev/net/tun`; BDE ioctls (interrupt/sem). Still need: DMA ring/queue and buffer metadata mapping. |
| 4.5 | BDE packet interface: ioctl for TX/RX? Or mmap DMA rings + interrupt/poll? | PARTIAL | **Observed** LUBDE_WAIT_FOR_INTERRUPT (9), LUBDE_SEM_OP (10); `/dev/mem` mmap. User-space DMA ring + interrupt/sem. |
| 4.6 | Packet buffer format: contiguous packet only, or header + metadata (port, reason)? | HAVE | [PACKET_BUFFER_ANALYSIS.md](PACKET_BUFFER_ANALYSIS.md). opennsl_pkt_t from hal/include/opennsl/pkt.h; offset 0x8 = packet data; trace lengths 42/60/82/122 bytes. |
| 4.7 | DMA descriptor (DCB) layout: buffer pointer, length, control bits | PARTIAL | [DMA_DCB_LAYOUT_FROM_KNET.md](DMA_DCB_LAYOUT_FROM_KNET.md) (from bcm-knet.c); confirm for BDE-only path |
| 4.8 | Ring size, number of RX/TX channels, interrupt vs poll | PARTIAL | **Observed** BDE interrupt + sem ioctls (9/10) in the packet I/O trace; still need: which DMA channels/rings + how they map to ports/queues. |

**How to get 4.3–4.8**: (1) **Live switch**: Follow [TRACING_PACKET_IO_GUIDE.md](TRACING_PACKET_IO_GUIDE.md) (strace/ltrace during ping). (2) **Ghidra**: Run `FindPacketTxPath.java` on switchd (callers of `read`, refs to opennsl_tx/bcm_tx) and on libopennsl (opennsl_tx callees). (3) **DCB/ring layout**: See [DMA_DCB_LAYOUT_FROM_KNET.md](DMA_DCB_LAYOUT_FROM_KNET.md) (from bcm-knet.c).

**Trace run (10.1.1.233)**: Full syscall trace; see [traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md](traces/PACKET_IO_TRACE_EXTRACTED_10.1.1.233.md) for full extraction (thread roles, fd map, BDE ioctl decode, canonical TX/RX sequences, raw samples). Artifacts: `traces/packet-io-trace-10.1.1.233.log`, `packet-io-summary-10.1.1.233.txt`, optional `packet-io-probe-10.1.1.233.log`.

---

## 5. Port and SerDes bringup

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 5.1 | Port mapping swpN ↔ xeM (BCM port), porttab format | HAVE | WHAT_MAKES_THE_SWITCH_WORK.md, COMPLETE_INTERFACE_ANALYSIS.md |
| 5.2 | List of registers (or script) to bring one port up (enable, speed, duplex) | NEED | Capture setreg/getreg (or rc.ports_0) on working Cumulus during “port up”; or OpenNSL port init code |
| 5.3 | SerDes lane configuration (per port / per lane) | NEED | Same as 5.2; often in soc/port or phy code |
| 5.4 | 40G vs 4×10G breakout (ports 49–52): lane remap, port numbering | PARTIAL | QSFP_BREAKOUT_CONFIGURATION.md concept; exact regs NEED |

**How to get 5.2–5.4**: On Cumulus, run a script that does “ip link set swp1 up” (and down) while logging all register reads/writes (e.g. via wrapper or /dev/mem trace). Diff to get minimal set. Alternatively analyze OpenNSL/soc port and SerDes code.

---

## 6. Initialization and config

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 6.1 | Order: open BDE → attach/init → rc.soc (init all, rcload rc.ports_0, rc.led, rc.datapath_0, rc.forwarding) | HAVE | initialization-sequence.md, WHAT_MAKES_THE_SWITCH_WORK.md |
| 6.2 | .bcm config (key=value) and how it’s merged/used | HAVE | Config docs, extract from switch |
| 6.3 | rc.soc script syntax (init, setreg, rcload, etc.) | HAVE | soc_script parser, SDK_AND_ASIC_CONFIG_FROM_SWITCH.md |
| 6.4 | rc.datapath_0 / datapath.conf → buffer pools, priority groups → registers | PARTIAL | We know config format; exact register mapping NEED (or skip and use defaults) |
| 6.5 | rc.forwarding (ECMP hash, punt rules) → registers | PARTIAL | Same |

**How to get 6.4–6.5**: Reverse rc.datapath_0 execution (which setregs run) or OpenNSL datapath init.

---

## 7. Platform (AS5610-52X)

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 7.1 | I2C for SFP/QSFP (module detect, DDM): bus/mux mapping | NEED | ONLP or vendor docs; existing ONL/platform code |
| 7.2 | LED mapping (front-panel ↔ LED registers) | PARTIAL | LED regs HAVE; platform mapping NEED for correct behavior |
| 7.3 | Thermal sensors (if needed) | OPTIONAL | Platform docs / ONLP |

---

## 8. Error handling and robustness

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 8.1 | BDE return codes (e.g. LUBDE_SUCCESS / LUBDE_FAIL) | HAVE | linux-user-bde.h |
| 8.2 | SDK/opennsl-style error codes (e.g. OPENNSL_E_*) | PARTIAL | OpenNSL headers list many; full list and meaning NEED for production |
| 8.3 | S-Channel timeout and error behavior | PARTIAL | schan_timeout_usec in config; behavior on timeout NEED |

---

## 9. Optional but useful later

| # | Information | Status | Where / How to get |
|---|-------------|--------|--------------------|
| 9.1 | Stats/counter list and how to read (registers or DMA) | NEED for monitoring | OpenNSL stats APIs; register map |
| 9.2 | VLAN_XLATE and FP/ACL entry layout | NEED for ACL/VLAN features | Same approach as L2/L3 tables |
| 9.3 | Buffer/datapath tuning (pool sizes, coalescing) | NEED for high load | rc.datapath + register map |

---

## 10. Summary: Must-have before you can ship Path B

- **1.x** BDE: HAVE ioctls, mmap, register read/write (BDE_MMAP_ANALYSIS).
- **2.x** Registers: HAVE CMIC, S-Chan format (2.3), DMA regs; **need** port/SerDes regs (2.6), pipeline (2.7).
- **3.x** Tables: HAVE region, names; **PARTIAL** L2/L3 layouts and write path (L2_TABLE_ACCESS_ANALYSIS, L3_TABLE_WRITE_CHAIN_DUMP); **need** 3.10 hash/index.
- **4.x** Packet I/O: HAVE TX path (4.3), buffer format (4.6); **PARTIAL** RX (4.4), BDE interface (4.5), DCB/ring (4.7–4.8).
- **5.x** Port bringup: HAVE mapping; **need** minimal reg sequence (5.2–5.4); **PARTIAL** breakout (5.4).
- **6.x** Init: Mostly HAVE; 6.4–6.5 optional for first bringup.
- **7.x** Platform: Optional for “one port works”; needed for full AS5610 support.
- **8.x** Errors: Partial; can be filled as you test.

---

## 11. Suggested order of work

1. **Packet I/O (4.x)** — Without this, control plane and host traffic don’t work. Strace + Ghidra on switchd and libopennsl.
2. **BDE packet interface (4.5–4.8)** — DMA/DCB and how buffers are handed to BDE/ASIC.
3. **S-Channel format (2.3)** — Required for table and possibly other register access.
4. **L2 entry layout + write path (3.3, 3.8)** — First table you need for L2 forwarding.
5. **L3 route/egress/host layouts + write path (3.4–3.8)** — For L3 and ECMP.
6. **Port bringup (5.2–5.4)** — So at least one port gets link.
7. **Register map gaps (2.6–2.7)** — As needed for debugging and tuning.

---

## 12. References

- **Tracing packet I/O (live switch)**: [TRACING_PACKET_IO_GUIDE.md](TRACING_PACKET_IO_GUIDE.md)
- **DCB/ring layout (from KNET source)**: [DMA_DCB_LAYOUT_FROM_KNET.md](DMA_DCB_LAYOUT_FROM_KNET.md)
- **What’s left / next steps**: [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md)
- **Ghidra script (TX path)**: `scripts/reverse-engineering/FindPacketTxPath.java`; run guide: [HOW_TO_RUN_FINDPACKETTXPATH.md](HOW_TO_RUN_FINDPACKETTXPATH.md); wrapper: `ghidra-find-packet-tx-path.sh`
- **Port-up trace (5.2–5.3)**: `run-port-up-trace-10.1.1.233.sh`, `trace-port-up-on-switch.sh`
- **Gaps (general)**: [GAPS_FOR_CUSTOM_SWITCHD_SDK.md](GAPS_FOR_CUSTOM_SWITCHD_SDK.md)
- **Stack readiness**: [STACK_READINESS_AS5610.md](STACK_READINESS_AS5610.md)
- **Register map**: [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md), [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md)
- **S-Channel / DMA**: [SCHAN_AND_RING_BUFFERS.md](SCHAN_AND_RING_BUFFERS.md)
- **Table names/addresses**: [TABLE_NAME_MAPPING.md](TABLE_NAME_MAPPING.md), `build-server/opennsl/sdk-deep-extract/opennsl-table-name-to-addr-xref.txt`
- **Packet I/O (TUN)**: [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md)
- **Init**: [initialization-sequence.md](initialization-sequence.md), [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md)
- **BDE headers** (in repo): `open-nos-build/.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/bde/linux/user/kernel/linux-user-bde.h`, `.../systems/bde/linux/include/linux-bde.h`

# Edgecore AS5610-52X Reverse Engineering

Comprehensive reverse engineering of the **Edgecore AS5610-52X** 52-port
10GbE switch running **Cumulus Linux 2.5** on a **Broadcom BCM56846
(Trident+)** ASIC. Goal: understand the hardware deeply enough to build
a fully functional open-source NOS (EdgeNOS) without access to Broadcom
NDA documentation.

---

## 📖 Start here

**Read [`DOCUMENTATION_INDEX.md`](DOCUMENTATION_INDEX.md) first** —
the canonical entry point that catalogues all 194 documentation files
in this repo across 7 tiers, with per-topic guidance.

Then read [`VERIFICATION_LOG.md`](VERIFICATION_LOG.md) for the audit
of old docs vs new findings — important for knowing which old data is
still authoritative.

For an EdgeNOS implementer starting fresh, the recommended reading
order is in `DOCUMENTATION_INDEX.md` § "For an EdgeNOS implementer
starting fresh".

---

## Quick-lookup table

| Goal | Doc |
|---|---|
| Bring the chip out of reset | `cumulus_baseline_2013/BCM_INIT_STATIC_CHAIN.md` |
| Understand access methods (MMIO/SCHAN/PAXB) | `cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md` |
| Issue SCHAN transactions | `cumulus_baseline_2013/CMIC_SCHAN_DMA_DEEP_DIVE.md` |
| Move packets RX/TX | `cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md` |
| Program L3 routes | `cumulus_baseline_2013/L3_L2_PROGRAMMING_FLOW.md` |
| What hardware Cumulus supports (decoded from the install images) | [`CUMULUS_SUPPORTED_HARDWARE.md`](CUMULUS_SUPPORTED_HARDWARE.md) |
| L2 entry bit layout (verified via bcmcmd) | [`L2_ENTRY_FORMAT.md`](L2_ENTRY_FORMAT.md) |
| L3 entry bit layout (verified) | [`L3_NEXTHOP_FORMAT.md`](L3_NEXTHOP_FORMAT.md) |
| VLAN entry bit layout (verified) | [`VLAN_TABLE_FORMAT.md`](VLAN_TABLE_FORMAT.md) |
| Hash table SCHAN opcodes (NEW) | `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` |
| MMU buffer pool / FP TCAM | `cumulus_baseline_2013/FP_MMU_AND_REMAINING.md` |
| Init scripts (rc.soc) decoded | `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md` |
| PHY firmware + Warpcore SerDes | [`cumulus_baseline_2013/ghidra-analysis/PHY_FIRMWARE_FUNCTIONS.md`](cumulus_baseline_2013/ghidra-analysis/PHY_FIRMWARE_FUNCTIONS.md) + [`SERDES_WC_INIT.md`](SERDES_WC_INIT.md) |
| PAXB sub-windows | [`PAXB_SUBWINDOW_MECHANISM.md`](PAXB_SUBWINDOW_MECHANISM.md) |
| switchd FUSE control plane | `cumulus_baseline_2013/fuse-explore/SWITCHD_SFS_INTERNALS.md` |
| Current gap analysis | `cumulus_baseline_2013/WHATS_MISSING.md` |
| Known-good Cumulus baseline | `cumulus_baseline_2013/PROVEN_WORKING_CONFIG.md` |
| Hardware-layer map (BAR0/CMICm/I²C/retimers/CPLD) | [`cumulus_baseline_2013/TO_THE_SILICON.md`](cumulus_baseline_2013/TO_THE_SILICON.md) |
| Live runtime state (PCI BAR, /proc/iomem, IRQs, fds, I²C tree, bcm.d/rc.soc) | [`cumulus_baseline_2013/LIVE_SYSTEM_DEEP_DIVE.md`](cumulus_baseline_2013/LIVE_SYSTEM_DEEP_DIVE.md) |
| Default CoPP ACL + Python framework + clcmd_uds pickle protocol | [`cumulus_baseline_2013/CONTROL_PLANE_AND_PY_FRAMEWORK.md`](cumulus_baseline_2013/CONTROL_PLANE_AND_PY_FRAMEWORK.md) |

---

## Hardware

| Component | Detail |
|---|---|
| **Switch** | Edgecore AS5610-52X (also sold as Accton AS5610-52X) |
| **ASIC** | Broadcom BCM56846 (Trident+, iProc PAXB), 560 Gbps, 52× 10GbE + 4× 40GbE |
| **CPU** | PowerPC e500v2 (Freescale P2020) |
| **NOS analyzed** | Cumulus Linux 2.5 (Debian 7 / Wheezy base, PPC32 big-endian) |
| **SerDes** | Broadcom Warpcore WC-B0 (internal MDIO, clause-22) |
| **PHY** | Broadcom BCM84740 (8-port, embedded 8051) |
| **Retimer** | TI DS100DF410 × 32 instances (4-channel each) |
| **CPLD** | Accton AS5610_52X CPLD (LED + GPIO + PSU/fan) |

---

## Methods used

- **Ghidra** — static analysis of `switchd` (31 MB PPC32 BE binary, BCM
  SDK statically linked), kernel BDE modules, PHY firmware (8051)
- **bcmcmd** (`listmem`, `dump raw`, `setreg`) — live ASIC table inspection
- **GDB hardware watchpoints** — captured CMIC MIIM writes at runtime
- **GDB on live switchd** — confirmed S-channel write paths
- **strace** — full 455K-line trace of switchd cold-boot
- **Live BAR0 dump** — 256 KB MMIO snapshot from running chassis
- **FUSE filesystem capture** — full mirror of `/cumulus/switchd/`
  (298 files / 1.3 MB)

---

## What's been recovered

### Hardware-level
- BCM56846 access stack (MMIO ↔ PAXB ↔ CMICm ↔ SCHAN)
- Per-CMC register layout (SCHAN_CTRL, SCHAN_MSG, DMA_CTRL, DMA_DESC, FIFO_DMA)
- DCB format (32 B for Trident+, with chained/IRQ flags)
- **36,896 BCM register names** extracted (pointer table at `0x11bc9344`)
- **62,554 field names** extracted (pointer table at `0x11d332ec`)
- PAXB IMAP sub-window mechanism (8 × 4 KB windows; IMAP0_7 dynamic)
- Warpcore SerDes MDIO init sequence
- DS100DF410 retimer init recipe
- CPLD register map (LED packing, GPIO, PSU/fan)
- LED uController ISA (39 opcodes) + bytecode interpretation
- I²C topology (6-layer mux tree)
- BCM84740 PHY firmware (43 functions mapped + entry chain)

### Chip-internal table programming
- **L2_TABLE** (131K entries, 13 B) bit layout — verified via bcmcmd
- **L3_DEFIP** TCAM + ALPM variants — verified
- **L3_HOST** hash table — bit layout + HASH_INSERT/LOOKUP/DELETE SCHAN opcodes
- **L3_ECMP** + ECMP_GROUP — verified
- **ING_L3_NEXT_HOP** + EGR_L3_NEXT_HOP + EGR_L3_INTF — full L3 chain
- **VLAN** + EGR_VLAN — verified
- **FP TCAM** (Field Processor / ACL) — 27 slices × 256 entries
- **MMU buffer pool** — service pools + priority groups + per-port limits

### switchd internals
- `bcm_init` 42-block dispatch order statically traced
- `soc_init` body + chip reset state machine decompiled
- SCHAN protocol (7-step transaction state machine)
- Block IDs for IPIPE/EPIPE/MMU/XLPORT
- BCM SDK API trampoline pattern (universal in switchd)
- Linkscan / Mirror / Storm / Stats / cosq APIs
- KNET stubs (statically linked but **unused** in Cumulus 2.5)
- `cl-acltool` → FP TCAM translation flow
- `phy-update` PHY firmware uploader

### Kernel modules
- `linux-kernel-bde.ko` (504 KB) — fully decoded
- `linux-user-bde.ko` (428 KB) — all 20 LUBDE ioctls
- `linux-bde-i2c.ko` (186 KB) — BCM ASIC internal I²C controller
- `linux-bde-tmon.ko` (153 KB) — BCM die-temperature sensor (hwmon)
- `accton_as5610_52x_cpld.ko` — CPLD driver

### Control plane
- switchd's **SFS** ("Switch File System") FUSE control plane — full
  295-entry schema captured + decoded
- 19 `fuse_operations` callbacks identified
- `cl-acltool` IPC protocol decoded
- netlink → switchd HAL → BCM API → chip-table flow traced end-to-end

### Init / boot
- Complete cold-boot register-write sequence statically recovered
- `rc.soc` / `rc.datapath_0` / `rc.led` / `config.bcm` decoded line-by-line
- 89 init-time registers identified with names + roles
- 24-second `bcm_init` window profiled (110K reads, 557 writes via PIO,
  thousands more via Table DMA)

---

## The 5-layer access stack

Every chip access traverses all layers:

```
Layer 5: BCM SDK API           (bcm_*)
Layer 4: SOC reg/mem API       (soc_reg32_set, soc_mem_write)
Layer 3: SCHAN protocol        (the on-chip transaction bus)
Layer 2: CMICm registers       (SCHAN_CTRL, DMA, IRQ — in BAR0 sub-window)
Layer 1: PAXB sub-window remap (8 × 4 KB windows via IMAP0_0..7)
Layer 0: PCIe BAR0 MMIO        (256 KB at physical 0xa0000000)
```

The historical confusion of "MMIO vs SCHAN vs CMICm vs PAXB" is fully
resolved in [`cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md`](cumulus_baseline_2013/ACCESS_METHODS_DEFINITIVE_GUIDE.md).

---

## SCHAN opcode reference (the chip's transaction bus)

The chip has dedicated SCHAN opcodes for hash table operations beyond
basic read/write:

| Opcode | Cmd word | Operation |
|---|---|---|
| `0x09` | `0x24000000` | Memory read |
| `0x0B` | `0x2c000200` | Register read |
| `0x0D` | `0x34000200` | Register write |
| `0x0F` | `0x3c000000` | Memory write |
| `0x11` | `0x44000000` | Table read |
| `0x13` | `0x4c000000` | Table write |
| `0x15` | `0x54000000` | Counter read |
| **`0x1A`** | **`0x68000000`** | **HASH_INSERT** (L3/L2 hash table insert) |
| `0x1B` | `0x6c000000` | HASH_INSERT_DONE (chip response) |
| **`0x1C`** | **`0x70000000`** | **HASH_DELETE** |
| `0x1D` | `0x74000000` | HASH_DELETE_DONE |
| **`0x22`** | **`0x88000000`** | **HASH_LOOKUP** |
| `0x23` | `0x8c000000` | HASH_LOOKUP_DONE |

The HASH_* opcodes let EdgeNOS bypass the BCM SDK for L2/L3 programming
— hand the chip an entry, the chip hashes + inserts. Full protocol in
[`cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md`](cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md).

---

## Selected chip-internal table layouts (verified via bcmcmd)

### L2 Table — [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md)
- Hash table, 131,072 entries × 13 bytes, chip address `0x07120000`
- Key fields: `VALID@0`, `VLAN_ID@[15:4]`, `MAC_ADDR@[63:16]`, `PORT_NUM@[70:64]`

### L3 Forwarding Chain — [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md)
```
IPv4: L3_DEFIP[prefix, MODE=0]  ─┐
IPv6 LPM (≤/64): L3_DEFIP[prefix, MODE=1, double-wide]  ─┤─→ NEXT_HOP_INDEX
IPv6 /128: L3_DEFIP_128[exact]  ─┘
  ING_L3_NEXT_HOP[idx] → PORT_NUM[22:16]
  EGR_L3_NEXT_HOP[idx] → DA_MAC[62:15] + INTF_NUM[14:3]
    EGR_L3_INTF[intf]  → SA_MAC[80:33] + VLAN[24:13]
```

### IPv6 Tables — [L3_IPV6_FORMAT.md](L3_IPV6_FORMAT.md)
- `L3_DEFIP_128` (0x0a176000, 256 entries × 39 B): exact /128 TCAM
- `L3_DEFIP` double-wide (MODE=1): LPM ≤/64

### VLAN Tables — [VLAN_TABLE_FORMAT.md](VLAN_TABLE_FORMAT.md)
- **VLAN** (ingress, alias QVLAN): `0x12168000`, 4096 × 40 B
- **EGR_VLAN** (egress): `0x0d260000`, 4096 × 29 B

### Stats Counters (XLMAC) — [STATS_COUNTER_FORMAT.md](STATS_COUNTER_FORMAT.md)
- Register address formula: `(block_id << 20) | (lane << 12) | reg_offset`
- Key offsets: `RPKT=0x0b, RBYT=0x34, TPKT=0x45, TBYT=0x64, R64=0x00, T64=0x39`

### SerDes Init (Warpcore WC-B0) — [SERDES_WC_INIT.md](SERDES_WC_INIT.md)
Key MDIO writes on port bring-up (captured via GDB watchpoint):
- `page=0x0008, reg[0x1e]=0x8000` — IEEE block enable
- `page=0x0a00, reg[0x10]=0xffe0` — SerDes digital: fiber/SFI mode
- `page=0x1000, reg[0x18]=0x8010` — clock recovery
- `page=0x3800, reg[0x01]=0x0010` — WC_CORE sequencer start

---

## Critical findings for EdgeNOS implementation

### The RX punt fix
See [`cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md`](cumulus_baseline_2013/PACKET_FLOW_END_TO_END.md).

Direct MMIO writes to CMICm `DMA_CTRL` silently fail. Reason: the chip's
internal arbiter requires SCHAN-mediated writes for atomicity with
in-flight DMA transactions.

**Fix:** route DMA_CTRL/DESC writes through SCHAN with `block=CMIC=0`:
```c
schan_write(unit, /*block*/ 0, /*addr*/ 0x158 + chan*4, ring_dma_addr);
schan_write(unit, /*block*/ 0, /*addr*/ 0x140 + chan*4,
            EN | DIR_RX | EN_INTR);
```

### CPU-steer config
For packets to be punted to CPU, set in `cpu_control_1`:
```
l3_mtu_fail_tocpu = 1
l3_slowpath_tocpu = 1
v4l3dstmiss_tocpu = 1
v6l3dstmiss_tocpu = 1
```

### L2 MOD FIFO overflow prevention
```
aux_arb_control.l2_mod_fifo_enable_l2_delete = 0
```
Without this, bulk MAC deletes overflow the FIFO and learn events get lost.

---

## Repository layout

```
.
├── DOCUMENTATION_INDEX.md       ← Master doc index (START HERE)
├── VERIFICATION_LOG.md          ← Verification of old vs new docs
├── README.md                    ← (this file)
│
├── cumulus_baseline_2013/       ← Recent canonical analysis (May 2026)
│   ├── ACCESS_METHODS_DEFINITIVE_GUIDE.md
│   ├── CMIC_SCHAN_DMA_DEEP_DIVE.md
│   ├── BCM_INIT_STATIC_CHAIN.md
│   ├── ASIC_INIT_COOKBOOK.md
│   ├── PACKET_FLOW_END_TO_END.md
│   ├── L3_L2_PROGRAMMING_FLOW.md
│   ├── TABLE_ENTRY_HASH_OPS.md
│   ├── FP_MMU_AND_REMAINING.md
│   ├── WHATS_MISSING.md
│   ├── TO_THE_SILICON.md                  ← Hardware-layer map (May 11)
│   ├── LIVE_SYSTEM_DEEP_DIVE.md           ← Live runtime state (May 11)
│   ├── CONTROL_PLANE_AND_PY_FRAMEWORK.md  ← CoPP + Python (May 11)
│   ├── ghidra-analysis/         ← Per-binary decomps
│   ├── fuse-explore/            ← switchd FUSE filesystem (298 files)
│   ├── captures/                ← BAR0 dump + state
│   ├── binaries/                ← Extracted switch rootfs
│   ├── tools/lubde-trace/       ← PPC32 LD_PRELOAD shim source
│   └── platform-config-accton-as5610_52x/
│
├── L2_ENTRY_FORMAT.md           ← Chip-side bit layouts (Feb 2026,
├── L3_NEXTHOP_FORMAT.md         ↰   verified via live bcmcmd —
├── L3_IPV6_FORMAT.md            ↰     still authoritative)
├── VLAN_TABLE_FORMAT.md
├── SERDES_WC_INIT.md
├── PORT_BRINGUP_REGISTER_MAP.md
├── STATS_COUNTER_FORMAT.md
├── PAXB_SUBWINDOW_MECHANISM.md
├── (PHY_FIRMWARE_FUNCTIONS.md lives under cumulus_baseline_2013/ghidra-analysis/)
├── LED_ARCHITECTURE.md
├── ECMP_GROUP_LAYOUT_FROM_01a1572c.md
├── (~70 more docs, see DOCUMENTATION_INDEX.md for full catalog)
│
├── traces/                      ← strace + register dumps from live chassis
├── scripts/                     ← Analysis scripts
└── ghidra-decomp/               ← Earlier Ghidra outputs
```

---

## Status

Major reverse engineering goals are **complete**. See
[`cumulus_baseline_2013/WHATS_MISSING.md`](cumulus_baseline_2013/WHATS_MISSING.md)
for the detailed gap status.

What's left is mostly **implementation work in EdgeNOS** (using these
findings), not more reverse engineering. Specific remaining unknowns
are listed in `WHATS_MISSING.md` § "Not started" — mostly low-priority
items (mstpd / ptmd come from upstream packages; cl-license validation
is bypassed by the clock-roll trick).

---

## Ethics

All findings obtained via:
- Hardware we own
- Static analysis of binaries shipped on the device
- Live `bcmcmd` queries on the running chassis
- No proprietary Broadcom NDA documentation was used

The goal is to enable a fully open-source switch NOS on this class of
hardware — without depending on Broadcom-licensed binaries.

---

*Last major update: 2026-05-11 — live-chassis dig from documentation
down to the silicon: BAR0 layout, kernel-BDE module parameters,
I²C tree, 32 DS100DF410 retimers via sysfs, CPLD driver origin,
chip die-temperature path via hwmon. See `TO_THE_SILICON.md`,
`LIVE_SYSTEM_DEEP_DIVE.md`, `CONTROL_PLANE_AND_PY_FRAMEWORK.md`.*

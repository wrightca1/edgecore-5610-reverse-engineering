# BCM Init — Register-Level Map (depth-3 static recursion)

Recursive static analysis of `bcm_init` and `soc_init` call graphs to a
depth of 3, extracting every reachable `soc_reg32_set`/`get`/`mem_*`/
`schan_op` call site and resolving the register-name argument from the
SDK's name-pointer table at **`0x11bc9344`**.

This is the **register-level "how Cumulus turns the chip on"** — pulled
entirely from the binary, no chassis required.

---

## 1. Coverage achieved

| Root function | Total primitive calls reachable | Unique registers identified |
|---|---:|---:|
| `soc_init`     (`FUN_10794970`) | 113 | 22 |
| `port` block   (`FUN_105b4b88`) | 117 |  29 |
| `field` block  (`FUN_104b8f94`) |  78 | 39 |
| `common` block (`FUN_10b84db0`) |   6 |  1 |
| `soc_mmu_init` (`FUN_10e412f4`) |   0 |  — (helpers exceed size cap) |
| **TOTAL distinct registers** | **314 primitive calls** | **89 unique** |

The `?` entries (regs whose IDs aren't constant-foldable from depth-3
decompile context) account for the difference between primitive-call
count and identified-register count. To resolve them requires either
deeper recursion or constant-propagation analysis.

---

## 2. The bring-up registers (`soc_init` — runs BEFORE bcm_init)

`soc_init` is the BCM SDK's chip-level initialization (the function
called by switchd's `FUN_100a3680` wrapper, BEFORE `bcm_init`). Its
register-touch profile reveals the actual chip bring-up sequence:

### A. CMIC reset / config (the chip's brain)

| Register | Count | Role |
|---|---:|---|
| **`CMIC_SOFT_RESET_REG`** (6054) | **8** | Multi-stage CMIC reset toggling — the chip's master reset |
| `CMIC_CMC0_SBUSDMA_CH0_CONTROL` (3230) | 3 | SBUS DMA channel 0 setup (internal block access bus) |
| `CMIC_CMC0_PCIE_MISCEL` (3215) | 3 | PCIe-related misc |
| `CMIC_PCIE_USERIF_PURGE_CONTROL` (5345) | 3 | PCIe user interface purge |
| `CMIC_PCIE_USERIF_STATUS_CLR` | 2 | Clear PCIe userif status |
| `CMIC_CMC0_FIFO_CH0_RD_DMA_CFG` (3128) | 2 | FIFO read DMA configuration |
| `CMIC_CMC0_STAT_DMA_CFG` (3330) | 2 | Statistics DMA config |
| `CMIC_STAT_DMA_SETUP` (6138) | 2 | Statistics DMA setup |
| `CMIC_CMC0_SBUSDMA_CH0_REQUEST` (3244) | 2 | SBUS DMA channel 0 request |

### B. PHY interface (MDIO)

| Register | Count | Role |
|---|---:|---|
| **`CHIPCOMMONB_MII_MANAGEMENT_COMMAND_DATA`** (2254) | **24** | MDIO command/data (the actual PHY register I/O!) |
| `CHIPCOMMONB_MII_MANAGEMENT_CONTROL` (2255) | 2 | MIIM control |

The 24 MDIO operations during soc_init are **probably the PHY discovery
phase** — querying each PHY's ID register to identify what's connected.
The actual firmware upload happens later (in `phy-update`).

### C. PCI / PAXB

| Register | Count | Role |
|---|---:|---|
| `PAXB_0_CONFIG_IND_ADDR` (27135) | 2 | PCI adapter 0 indirect address |
| `PAXB_1_CONFIG_IND_ADDR` (27283) | 2 | PCI adapter 1 indirect address |

### D. XGXS SerDes (lane control)

| Register | Count | Role |
|---|---:|---|
| `XPORT_XGXS_NEWCTL_REG` (36841) | 6 | XGXS SerDes control for X ports (10G XFI) |
| `XQPORT_XGXS_NEWCTL_REG` (36876) | 2 | XGXS SerDes control for XQ ports (QSFP+) |

### E. Per-port MAC

| Register | Count | Role |
|---|---:|---|
| **`PORT_MAC_CONTROL`** (28196) | **30** | The big MAC control register — touched 30× in soc_init alone |
| `XLPORT_XMAC_CONTROL` (36696) | 5 | XLPORT 10G XMAC control |
| `PORT_MLD_CTRL_REG` (28215) | 4 | Multicast Listener Discovery control |

### F. Top-level features

| Register | Count | Role |
|---|---:|---|
| `TOP_SWITCH_FEATURE_ENABLE` (34582) | 1 | Master feature-enable register |
| `L3_DEFIP_RPF_CONTROL` (23319) | 1 | L3 DEFIP reverse-path-filter control |

---

## 3. The per-port init (`port` block)

Runs over all 52 ports + CPU port. Per-port register-touch profile:

| Register | Count | Role |
|---|---:|---|
| **`PORT_MAC_CONTROL`** (28196) | **30** | Per-port MAC reset/config (overlap with soc_init — different phases touching same reg) |
| `EGR_VLAN_CONTROL_3` (12175) | 14 | Egress VLAN control register 3 |
| `EGR_VLAN_CONTROL_2` (12174) | 12 | Egress VLAN control 2 |
| `EGR_VLAN_CONTROL_1` (12173) | 7 | Egress VLAN control 1 |
| **`E2ECC_PORT_MAPPING_CONFIG`** (10086) | 6 | End-to-End Congestion Control port mapping |
| `E2ECC_TX_ENABLE_BMP` (10087) | 5 | E2ECC TX enable bitmap |
| `XLPORT_XMAC_CONTROL` (36696) | 5 | 10G XMAC control |
| `XPORT_XMAC_CONTROL` (36847) | 5 | (XPORT variant) |
| `IPG_HD_BKP_CNTL` (21115) | 3 | Inter-Packet-Gap headroom backup control |
| `GE_PORT_CONFIG` (15515) | 3 | Gigabit Ethernet port config (legacy 1G) |
| `E2ECC_PORT_MAPPING` (10085) | 3 | E2ECC port mapping (separate from CONFIG) |
| `GPORT_UMAC_CONTROL` (15927) | 2 | Universal MAC control |
| `E2ECC_MAX_TX_TIMER` (10083) | 2 | E2ECC max TX timer |
| `ING_OUTER_TPID` (20884) | 1 | Ingress outer TPID for VLAN-tagged frames |
| `SRC_MODID_EGRESS_SEL` (32846) | 1 | Source module-ID egress selection |
| `XLPORT_MODE_REG` (37081-ish) | 1 | XLPORT mode (10G/40G mux) |
| `E2E_HOL_EN` (10173) | 1 | End-to-end Head-of-Line enable |
| `E2ECC_HOL_EN` (10081) | 1 | E2ECC HOL enable |
| `XPORT_CONFIG` (variable) | 1 | XPORT config |

**Total: 29 unique registers × ~4 ops/register average × 52 ports = ~6,000+ register
operations** during the port-init phase. This matches the order of magnitude of
the 10,000+ PHYS_READ32 we saw in our trace bucket for sub-phase C.

---

## 4. The Field Processor (`field` block)

Runs only if chip flag `0x2f2c28 bit 0x2000000` is set (set on BCM56846).
Programs the FP TCAM for ACL classification.

### FP slice / key configuration

| Register | Count | Role |
|---|---:|---|
| `SBS_CONTROL` | 5 | Slice Bus Selector control |
| `VFP_SLICE_CONTROL` (36125) | 3 | VLAN FP slice control |
| `VFP_KEY_CONTROL_2` (36117) | 3 | VLAN FP key control 2 |
| `VFP_KEY_CONTROL` (36115) | 1 | VLAN FP key control |
| `EFP_SLICE_CONTROL` (11257) | 1 | Egress FP slice control |
| `EFP_KEY4_DVP_SELECTOR` (11241) | 1 | Egress FP key 4 DVP selector |
| `EFP_KEY4_MDL_SELECTOR` (11242) | 1 | Egress FP key 4 MDL selector |
| `EFP_SLICE_MAP` (11258) | 1 | Egress FP slice map |
| `FP_SLICE_ENABLE` (15085) | 2 | Ingress FP slice enable |
| `FP_LOOKUP_ENABLE` (15038) | 1 | Ingress FP lookup enable |
| `FP_DOUBLE_WIDE_SELECT` (15022) | 2 | FP double-wide mode select |
| `FP_DOUBLE_WIDE_F4_SELECT` (15021) | 2 | FP double-wide F4 key select |
| `FP_SLICE_CONFIG` (15084) | 1 | FP slice config |
| `FP_F4_SELECT` (15024) | 1 | FP F4 select |
| `IFP_KEY_CLASSID_SELECT` (17095) | 1 | Ingress FP key class-ID select |

### Warpcore (BCM84740) PHY data via FMAC

| Register | Count | Role |
|---|---:|---|
| `BRDC_FMAC_FPS_CONFIGURATION_RX_SYNC` (1219) | 3 | FPS RX sync config |
| `BRDC_FMAC_EDS_STATUS` (1204) | 3 | EDS (Error Detection System) status |
| `BRDC_FMAC_ECC_1B_ERR_CNT` (1198) | 3 | ECC 1-bit error count |
| `BRDC_FMAC_ECC_2B_ERR_CNT` (1201) | 3 | ECC 2-bit error count |
| `BRDC_FMAC_ECC_2B_ERR_MONITOR_MEM_MASK` (1202) | 3 | ECC 2-bit error mask |
| `BRDC_FMAC_FBIST_STATUS` (1211) | 3 | F-BIST status |
| `BRDC_FMACL_TEST_CONFIGURATION` (1187) | 2 | FMAC L test config |
| `BRDC_FMACL_TEST_STATUS` (1188) | 2 | FMAC L test status |
| `BRDC_FMACL_SPARE_REGISTER_3` (1186) | 2 | spare reg |
| `BRDC_FMAC_FBIST_CONFIGURATION_B` (1210) | 2 | F-BIST config B |
| `BRDC_FMAC_FMAL_STATISTICS_GTIMER` (1215) | 2 | FMAC stats timer |

### Other (LED uC, AXI interconnect)

- `CMIC_LEDUP0_DATA_RAM141/142` (LED uController internal RAM)
- `AXIIC_DS_0/1_IDM_*` (AXI interconnect down-stream IDM error logs)

---

## 5. The minimum cold-boot register sequence (synthesized)

Putting this together, the **chip cold-boot sequence Cumulus performs**:

```
1. POWER-UP / KERNEL BOOT
   - linux-kernel-bde.ko PCI probe maps BAR0 at 0xa0000000 (256 KB)
   - DMA pool allocated (8 MB coherent)
   - IRQ 16 connected to BDE handler

2. SWITCHD STARTUP — `bcm_attach`
   - Parse config.bcm (portmap, pbmp_valid, etc.)
   - Allocate per-chip state structs

3. SWITCHD STARTUP — `soc_init` (FUN_10794970, 22.7 KB)
   Phase 3A: CMIC reset
     - Toggle CMIC_SOFT_RESET_REG (8 writes) — full chip soft reset
     - Initialize CMIC DMA controllers:
         · CMIC_CMC0_SBUSDMA_CH0_CONTROL  (×3)
         · CMIC_CMC0_SBUSDMA_CH0_REQUEST  (×2)
         · CMIC_CMC0_FIFO_CH0_RD_DMA_CFG  (×2)
         · CMIC_CMC0_STAT_DMA_CFG, CMIC_STAT_DMA_SETUP
     - Configure PCIe interface:
         · CMIC_CMC0_PCIE_MISCEL  (×3)
         · CMIC_PCIE_USERIF_PURGE_CONTROL  (×3)
         · CMIC_PCIE_USERIF_STATUS_CLR  (×2)
     - Set up PAXB indirect addressing:
         · PAXB_0_CONFIG_IND_ADDR  (×2)
         · PAXB_1_CONFIG_IND_ADDR  (×2)

   Phase 3B: PHY discovery via MDIO
     - 24 MDIO operations via CHIPCOMMONB_MII_MANAGEMENT_COMMAND_DATA
       (read PHY IDs, capability registers)

   Phase 3C: SerDes setup
     - Toggle XPORT_XGXS_NEWCTL_REG (6 ops — for 10G XFI lanes)
     - Toggle XQPORT_XGXS_NEWCTL_REG (2 ops — for 40G QSFP lanes)

   Phase 3D: Per-port MAC init
     - For each of 52 ports:
         · PORT_MAC_CONTROL (the main per-port MAC reset/config — 30 ops total)
         · XLPORT_XMAC_CONTROL (5 ops total — 10G XMAC blocks)
         · PORT_MLD_CTRL_REG (4 ops — multicast listener)

   Phase 3E: Top-level features
     - TOP_SWITCH_FEATURE_ENABLE (1 op — bit-mask of enabled features)
     - L3_DEFIP_RPF_CONTROL (1 op — RPF filter)

4. SWITCHD STARTUP — `bcm_init` per-block dispatch (FUN_104f0b7c)
   - `common`: defensive teardown (44 calls) + profile-mem alloc (11 calls)
   - `port`: per-port pipeline init (117 register ops)
     - PORT_MAC_CONTROL writes (30x more — different fields than soc_init)
     - EGR_VLAN_CONTROL_1/2/3 (7+12+14 writes — egress VLAN setup)
     - E2ECC_* (congestion control config)
     - IPG_HD_BKP_CNTL (IPG headroom)
   - `l2`, `stg`, `vlan`, `trunk`, ... (40 more blocks)
   - `field`: FP TCAM slice config (78 register ops on FP_*, VFP_*, EFP_*)

5. POST-BCM_INIT — rc.soc setregs
   - setreg xmac_tx_ctrl 0xc802
   - setreg MAC_RSV_MASK MASK=0x18
   - modreg cmic_misc_control LINK40G_ENABLE=1
   - run rc.datapath_0 (~140 register writes for MMU/scheduler config)
   - setreg IFP_METER_PARITY_CONTROL 0 (Trident errata)
   - drop counter setup (rdbgc*_select, tdbgc6_select)
   - LED uController bytecode load (rc.led)

6. READY
   - touch /var/run/switchd.ready
   - linkscan thread polls every 250 ms
```

---

## 6. Key takeaways for EdgeNOS

### The "must-touch" registers

For a barebones bring-up, the **minimum critical register set** is:

```
# Phase 1: Wake the CMIC
CMIC_SOFT_RESET_REG                  ─ pulse reset
CMIC_CMC0_SBUSDMA_CH0_CONTROL        ─ enable internal bus DMA
CMIC_CMC0_PCIE_MISCEL                ─ PCI bridge config
CMIC_CONFIG                          ─ main CMIC mode

# Phase 2: MDIO / PHY init
CHIPCOMMONB_MII_MANAGEMENT_CONTROL   ─ MDIO controller
CHIPCOMMONB_MII_MANAGEMENT_COMMAND_DATA  ─ MDIO transactions

# Phase 3: SerDes
XPORT_XGXS_NEWCTL_REG                ─ 10G XGXS for swp1-48
XQPORT_XGXS_NEWCTL_REG               ─ 40G XGXS for swp49-52

# Phase 4: Per-port MAC
PORT_MAC_CONTROL                     ─ TOUCH 60+ TIMES (soc_init + bcm_init)
XLPORT_XMAC_CONTROL                  ─ 10G XMAC
XPORT_XMAC_CONTROL                   ─ XPORT variant
XLPORT_MODE_REG                      ─ 10G/40G mode mux

# Phase 5: VLAN egress
EGR_VLAN_CONTROL_1, _2, _3           ─ outer VLAN config

# Phase 6: E2ECC (congestion control — required even if unused)
E2ECC_PORT_MAPPING_CONFIG
E2ECC_TX_ENABLE_BMP
E2ECC_PORT_MAPPING
E2ECC_MAX_TX_TIMER
E2ECC_HOL_EN

# Phase 7: Top-level
TOP_SWITCH_FEATURE_ENABLE            ─ master feature bits
L3_DEFIP_RPF_CONTROL
```

### What we DON'T have

- **Exact values** written to each register (most arg3 still `?`)
- **Bit positions** for field-level writes (the `reg_field_lk` calls
  resolve a field name to bit-offset/width inside the register, but we
  haven't extracted those constants yet)
- **Per-port iteration unrolling** (we know PORT_MAC_CONTROL is touched
  30 times in soc_init alone — likely once per port — but haven't
  confirmed the port-indexing pattern)

### Path to complete coverage

To get a fully ground-truth register-write sequence (with values), the
next step is to:

1. **Decompile FUN_10e7153c** — this is the giant function in soc_init's
   call chain where most port-reset register writes happen. From the
   depth-3 dump, it's the dominant contributor (~40 PORT_MAC_CONTROL
   ops in this function alone). Reading its decompiled C will reveal
   the per-port reset state machine.

2. **Constant-propagate** through the `setreg_field` calls — Ghidra's
   decompiler can fold many constants if we use better p-code analysis.

3. **Walk further into table-clear sub-graph** — there are 52 mem_clear
   calls in the depth-3 output but only a few have resolved memory IDs.
   Need to extract these to know which tables Cumulus zeros at init.

This is mechanical work; we have all the addresses and tools.

---

## 7. Files

- `ghidra-analysis/switchd_writes_depth3.txt` — raw 342-line call-site dump
- `ghidra-analysis/switchd_writes_per_helper.txt` — per-helper breakdown
- `ghidra-analysis/switchd_recurse_profile.txt` — depth-2 callee enumeration
- `BCM_INIT_STATIC_CHAIN.md` — bcm_init's 42-block dispatch order
- `BLOCK_INIT_DEEP_DIVE.md` — common/port/field decomposition
- `ASIC_INIT_COOKBOOK.md` — rc.soc/rc.datapath_0/config.bcm decoded

---

*Static analysis from `switchd` binary; no chassis interaction. 89
distinct chip registers identified across the init phases, providing
the register-level blueprint Cumulus uses to bring the BCM56846 from
cold boot to forwarding state.*

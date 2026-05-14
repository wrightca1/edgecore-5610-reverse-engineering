# Cross-Correlation: SOC Registers × Chip Memories × Raw Dumps × Our Code

This document ties together, for each chip subsystem:
- the **registers** Cumulus changed (`dump_soc_diff.txt`)
- the **memories** Cumulus populated (`dump_socmem_diff.txt`)
- the **raw chip-table dumps** captured separately (FP_TCAM, L3_DEFIP, etc.)
- **what `asic/edged/*.c` writes** (our static side)

Registers are config-knobs (typically global or per-port);
memories are tables with multiple entries (e.g. routes, MAC table, FP rules).
A subsystem only works if both are programmed.  Until now we've been
looking at register diffs in isolation — this doc tracks the *pair*.

**Header symbols:** 2263 regs + 638 mems
**Cumulus reg diff:** 417 regs
**Cumulus mem diff:** 132 mems
**Edged-source refs:** 80

## Smoking guns for the chip→CPU drop

Cross-correlating the soc-register diff with the soc-memory diff
makes the missing surfaces obvious.  All four below are populated in
Cumulus, zero in our edged, and any one of them is plausibly the
silent-drop cause:

| # | Chip table | Cumulus rows | What's in it | Why it matters |
|---|---|--:|---|---|
| 1 | `L2_USER_ENTRY` | **63** | `MAC_ADDR=0x0180c2000000` etc. with `CPU=1, BPDU=1` | Per-MAC CPU-trap table — protocol addresses (LLDP / STP / BFD / OSPF-multicast) that the chip should copy to CPU.  Without it, control-plane frames are forwarded but never punted. |
| 2 | `FP_TCAM` + `FP_POLICY_TABLE` | **100 / 100** | Policy rows show `Y_COPY_TO_CPU=3, Y_DROP=1, R_COPY_TO_CPU=3, R_DROP=1` | The Field-Processor's CPU-trap rules.  Cumulus's `00control_plane.rules` compiles into this.  Our chip has the slices *enabled* (`FP_SLICE_ENABLE=0xe33ff` ported) but zero entries. |
| 3 | `EPC_LINK_BMAP` | **1** | `PORT_BITMAP=0x020000…` | The egress port-bitmap the EPC stage uses.  If our register read is zero, the egress pipeline doesn't know any port is up — frames get dropped after the MMU. |
| 4 | `EGR_VLAN` + `EGR_VLAN_X/Y` + `EGR_VLAN_STG` | **53 / 53 / 53 / 1** | `VALID=1, STG=1`, plus per-port STG state `SP_TREE_PORT*=3` (forwarding) | Egress VLAN/STP state — the chip won't egress (including egressing-to-CPU on the CPU port) without this. |

Also from the L3 memories section: Cumulus has 30 distinct L3
memories populated (routes, next-hops, ECMP), with the actual route
content captured in `trace_hash_redo/11a_L3_DEFIP_raw_before.txt`
and friends — that file is where the bytes to load live.  Our edged
touches 4 of those memories via OpenMDK BMD APIs.

## Per-subsystem cross-correlation

### L3 forwarding

**Registers (17):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `ING_L3_NEXT_HOP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `INITIAL_L3_ECMP_GROUP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `INITIAL_L3_ECMP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_AUX_HASH_CONTROL` | 1 | `0x00000015` | — |
| `L3_DEFIP_128_CAM_ENABLE` | 1 | `0x00000003` | — |
| `L3_DEFIP_128_DATA_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_DEFIP_DATA_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_ECMP_GROUP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_ECMP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_ENTRY_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_IIF_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_IPMC_1_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_IPMC_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L3_IPMC_REMAP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| _...2 more_ | | | |

**Memories (30):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `L3_MTU_VALUES` | 12288 | `MTU_SIZE=0x3fff,` | `—` | — |
| `L3_IIF` | 8192 | `URPF_DEFAULTROUTECHECK=1,ALLOW_GLOBAL_ROUTE=1` | `—` | — |
| `L3_IPMC_REMAP` | 4095 | `L3MC_INDEX=1,` | `—` | — |
| `MY_STATION_TCAM` | 52 | `VALID=1,MASK=0x000000ffffffffffff,MAC_ADDR_MASK=0xffffffffff` | `—` | l3.c |
| `MY_STATION_TCAM_DATA_ONLY` | 52 | `IPV6_TERMINATION_ALLOWED=1,IPV4_TERMINATION_ALLOWED=1,DATA=0` | `—` | — |
| `MY_STATION_TCAM_ENTRY_ONLY` | 52 | `VALID=1,MASK=0x000000ffffffffffff,MAC_ADDR_MASK=0xffffffffff` | `—` | — |
| `L3_DEFIP_DATA_ONLY` | 28 | `NEXT_HOP_INDEX1=2,NEXT_HOP_INDEX0=2,ECMP_PTR1=2,ECMP_PTR0=2,` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `L3_DEFIP` | 25 | `VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,NEXT` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `L3_DEFIP_ONLY` | 25 | `VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,MODE` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `L3_DEFIP_X` | 25 | `VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,NEXT` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `L3_DEFIP_Y` | 25 | `VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,NEXT` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `EGR_L3_NEXT_HOP` | 5 | `SD_TAG_VID=0xfff,OVID=0xfff,L3:OVID=0xfff,L3:INTF_NUM=0xfff,` | `trace_hash_redo/11a_EGR_L3_NEXT_HOP_befo` | l3.c |
| `ING_L3_NEXT_HOP` | 4 | `TGID=0x1f,PORT_NUM=0x1f,DROP=1,` | `trace_hash_redo/11a_ING_L3_NEXT_HOP_befo` | l3.c |
| `L3_DEFIP_128` | 4 | `VRF_ID_MASK=0x3ff,VALID_1=1,VALID_0=1,NEXT_HOP_INDEX=2,MASK=` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| `L3_DEFIP_128_DATA_ONLY` | 4 | `NEXT_HOP_INDEX=2,ECMP_PTR=2,CLASS_ID=2` | `trace_hash_redo/11a_L3_DEFIP_raw_before.` | — |
| _...15 more_ | | | | |


### L2 / MAC table

**Registers (10):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `L2_AGE_TIMER` | 1 | `0x00000000` | — |
| `L2_AUX_HASH_CONTROL` | 1 | `0x00000013` | — |
| `L2_BULK_CONTROL` | 1 | `0x0000001b` | — |
| `L2_ENTRY_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L2_LEARN_CONTROL` | 1 | `0x00000001` | — |
| `L2_MOD_FIFO_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `L2_MOD_FIFO_RD_PTR` | 1 | `0x00000004` | — |
| `L2_MOD_FIFO_WR_PTR` | 1 | `0x00000004` | — |
| `L2_USER_ENTRY_CAM_DBGCTRL` | 1 | `0x0003c000` | — |
| `L2_USER_ENTRY_DATA_PARITY_CONTROL` | 1 | `0x00000001` | — |

**Memories (6):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `L2_USER_ENTRY` | 63 | `VALID=1,MASK=0x1000ffffffffffff,MAC_ADDR=0x0180c2000000,KEY=` | `—` | — |
| `L2_USER_ENTRY_DATA_ONLY` | 63 | `CPU=1,BPDU=1` | `—` | — |
| `L2_USER_ENTRY_ONLY` | 63 | `VALID=1,MASK=0x1000ffffffffffff,MAC_ADDR=0x0180c2000000,KEY=` | `—` | — |
| `L2_MOD_FIFO` | 4 | `L2_ENTRY_DATA=0x082000000a0000000000110011,BUCKET_INDEX=0x14` | `—` | — |
| `L2_BULK_MATCH_DATA` | 1 | `VPG_1=0x200,VALID=1,TGID_1=0x200,MODULE_ID_1=4,MAC_ADDR=0x01` | `—` | — |
| `L2_BULK_MATCH_MASK` | 1 | `VALID=1,TRILL_NONUC_NETWORK_SHORT:RESERVED_0=0x001000000000,` | `—` | — |


### VLAN / STP / port-tab

**Registers (3):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `EGR_VLAN_CONTROL_1` | 52 | `0x00002001` | datapath.c |
| `EGR_VLAN_PARITY_CONTROL` | 1 | `0x00000fff` | — |
| `PORT_TABLE_ECC_CONTROL` | 1 | `0x00000001` | — |

**Memories (4):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `EGR_VLAN` | 53 | `VALID=1,STG=1,` | `—` | — |
| `EGR_VLAN_X` | 53 | `VALID=1,STG=1,` | `—` | — |
| `EGR_VLAN_Y` | 53 | `VALID=1,STG=1,` | `—` | — |
| `EGR_VLAN_STG` | 1 | `SP_TREE_PORT2=3,SP_TREE_PORT1=3,` | `—` | — |


### FP / ACL

**Registers (21):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `EFP_METER_CONTROL` | 1 | `0x00000003` | — |
| `EFP_METER_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `EFP_POLICY_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `EFP_SLICE_CONTROL` | 1 | `0x000900cf` | — |
| `EFP_SLICE_MAP` | 1 | `0x00004ee4` | — |
| `EFP_TCAM_BLKSEL` | 1 | `0x000000ff` | — |
| `FP_FIELD_SEL_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `FP_GM_TCAM_BLK_SEL` | 1 | `0x00000fff` | — |
| `FP_SLICE_ENABLE` | 1 | `0x000e33ff` | — |
| `FP_TCAM_BLK_SEL` | 1 | `0x00000fff` | — |
| `FP_UDF_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `IFP_COUNTER_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `IFP_ING_DVP_2_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `IFP_METER_MUX_DATA_STAGING_PARITY_CONTROL` | 1 | `0x00000001` | — |
| _...6 more_ | | | |

**Memories (23):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `FP_GLOBAL_MASK_TCAM` | 100 | `VALID=1,MASK=0x02001fffffffffffff,KEY=0x00001fffffffffffff,I` | `deep_mine_20260513_191506/09_FP_GLOBAL_M` | — |
| `FP_GLOBAL_MASK_TCAM_X` | 100 | `VALID=1,MASK=0x00000001fffffffe01,KEY=0x00000001fffffffe01,I` | `deep_mine_20260513_191506/09_FP_GLOBAL_M` | — |
| `FP_GLOBAL_MASK_TCAM_Y` | 100 | `VALID=1,MASK=0x02001ffe00000001fe,KEY=0x00001ffe00000001fe,I` | `deep_mine_20260513_191506/09_FP_GLOBAL_M` | — |
| `FP_GM_FIELDS` | 100 | `VALID=1,MASK_X=0x1fffffffff,MASK=0x1fffffffff,KEY_X=0x1fffff` | `—` | — |
| `FP_GM_FIELDS_X` | 100 | `VALID=1,MASK_X=0x1fffffffff,MASK=0x1fffffffff,KEY_X=0x1fffff` | `—` | — |
| `FP_GM_FIELDS_Y` | 100 | `VALID=1,MASK_X=0x1fffffffff,MASK=0x1fffffffff,KEY_X=0x0ff110` | `—` | — |
| `FP_POLICY_TABLE` | 100 | `Y_DROP=1,Y_COPY_TO_CPU=3,R_DROP=1,R_COPY_TO_CPU=3,METER_PAIR` | `deep_mine_20260513_191506/09_FP_POLICY_T` | — |
| `FP_TCAM` | 100 | `VALID=3,PAIRING_FIXED_MASK=0x600,PAIRING_FIXED=0x200,PAIRING` | `deep_mine_20260513_191506/09_FP_TCAM_raw` | — |
| `FP_PORT_FIELD_SEL` | 54 | `SLICE9_F3=0xa,SLICE9_F2=5,SLICE9_F1=0xc,SLICE9_8_PAIRING=1,S` | `—` | — |
| `EFP_POLICY_TABLE` | 36 | `R_DROP=1,PID_COUNTER_MODE=4,METER_UPDATE_EVEN=1,METER_TEST_E` | `deep_mine_20260513_191506/09_FP_POLICY_T` | — |
| `EFP_TCAM` | 36 | `VALID=3,MASK=0x383f800000000000000000000000000000003fc000000` | `deep_mine_20260513_191506/09_FP_TCAM_raw` | — |
| `EFP_METER_TABLE` | 18 | `REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf` | `deep_mine_20260513_191506/09_FP_METER_TA` | — |
| `EFP_METER_TABLE_X` | 18 | `REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf` | `deep_mine_20260513_191506/09_FP_METER_TA` | — |
| `EFP_METER_TABLE_Y` | 18 | `REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf` | `deep_mine_20260513_191506/09_FP_METER_TA` | — |
| `FP_METER_TABLE` | 18 | `REFRESHCOUNT=0x7d0,PKTS_BYTES=1,BUCKETSIZE=0xf43,BUCKETCOUNT` | `deep_mine_20260513_191506/09_FP_METER_TA` | — |
| _...8 more_ | | | | |


### EPC / egress port

**Memories (1):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `EPC_LINK_BMAP` | 1 | `PORT_BITMAP_W2=2,PORT_BITMAP_W0=7,PORT_BITMAP=0x020000000000` | `—` | — |


### MMU

**Registers (85):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `S3_COSWEIGHTS` | 928 | `0x00000090` | — |
| `S2_COSWEIGHTS` | 468 | `0x00000090` | — |
| `OP_QUEUE_LIMIT_COLOR_CELL` | 313 | `0x00000007` | datapath.c |
| `OP_QUEUE_RESET_OFFSET_CELL` | 313 | `0x00000003` | datapath.c |
| `OVQ_MCQ_CREDITS` | 265 | `0x000000c0` | — |
| `MCQ_FIFO_BASE_REG` | 212 | `0x000000c0` | — |
| `OP_QUEUE_CONFIG1_CELL` | 164 | `0x00000008` | datapath.c |
| `PG_SHARED_LIMIT_CELL` | 162 | `0x000211c4` | datapath.c |
| `PG_MIN_CELL` | 159 | `0x0000002d` | datapath.c |
| `S2_S3_ROUTING` | 159 | `0x00001ff814941ca4` | — |
| `COSWEIGHTS` | 104 | `0x00000010` | datapath.c |
| `OP_QUEUE_CONFIG_CELL` | 61 | `0x01330819` | datapath.c |
| `OP_PORT_LIMIT_COLOR_CELL` | 54 | `0x0000130b` | datapath.c |
| `OP_PORT_LIMIT_RESUME_COLOR_CELL` | 54 | `0x0000130a` | datapath.c |
| `PG_RESET_OFFSET_CELL` | 54 | `0x00010010` | — |
| _...70 more_ | | | |


### XLPORT MAC

**Registers (57):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `COMMAND_CONFIG` | 52 | `0x11800158` | datapath.c |
| `IPG_HD_BKP_CNTL` | 52 | `0x00000014` | — |
| `LAG_FAILOVER_CONFIG` | 52 | `0x00000008` | — |
| `MAC_0` | 52 | `0x80a23581` | datapath.c |
| `MAC_1` | 52 | `0x0000caaf` | datapath.c |
| `MAC_MODE` | 52 | `0x00000022` | — |
| `MAC_PFC_REFRESH_CTRL` | 52 | `0xc0000001` | — |
| `MAC_RSV_MASK` | 52 | `0x00000018` | datapath.c |
| `PAUSE_CONTROL` | 52 | `0x0003ffff` | — |
| `TX_IPG_LENGTH` | 52 | `0x0000000c` | — |
| `XLPORT_CONFIG` | 52 | `0x00010040` | datapath.c |
| `XLP_TXFIFO_CELL_REQ_CNT` | 52 | `0x00000004` | — |
| `XMAC_CTRL` | 52 | `0x0000000000000003` | datapath.c |
| `XMAC_PFC_CTRL` | 52 | `0x00000001ffffc000` | — |
| `XMAC_RX_CTRL` | 52 | `0x0000000000000408` | datapath.c |
| _...42 more_ | | | |


### Hash / RTAG7

**Registers (11):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `RTAG7_HASH_TRILL_ECMP` | 2 | `0x00004000` | — |
| `HASH_CONTROL` | 1 | `0x0dd14000` | datapath.c |
| `MPLS_ENTRY_HASH_CONTROL` | 1 | `0x0000004a` | — |
| `RTAG7_HASH_CONTROL_3` | 1 | `0x00000009` | datapath.c |
| `RTAG7_HASH_FIELD_BMAP_1` | 1 | `0x00000f1c` | datapath.c |
| `RTAG7_HASH_FIELD_BMAP_2` | 1 | `0x00000f1c` | datapath.c |
| `RTAG7_HASH_SEED_A` | 1 | `0x0000002a` | datapath.c |
| `RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1` | 1 | `0x00000f3c` | datapath.c |
| `RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2` | 1 | `0x00000f7c` | datapath.c |
| `RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1` | 1 | `0x00000f3c` | datapath.c |
| `RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2` | 1 | `0x00000f7c` | datapath.c |

**Memories (1):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `RTAG7_FLOW_BASED_HASH` | 252 | `OFFSET_ECMP=1,` | `—` | — |


### CPU punt control

**Registers (1):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `CPU_CONTROL_1` | 1 | `0x18500600` | datapath.c, l3.c |


### Port mapping

**Registers (1):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `STORM_CONTROL_METER_MAPPING` | 1 | `0x00000e64` | — |

**Memories (9):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `ING_PHYSICAL_TO_LOGICAL_PORT_NUMBER_MAPPING_TABLE` | 73 | `LOGICAL_PORT_NUMBER=0x7f` | `—` | — |
| `EGR_MPLS_EXP_MAPPING_1` | 63 | `CFI=1` | `—` | — |
| `EGR_MPLS_EXP_MAPPING_2` | 63 | `CFI=1` | `—` | — |
| `EGR_MPLS_PRI_MAPPING` | 63 | `NEW_CFI=1,` | `—` | — |
| `DLB_HGT_PORT_QUALITY_MAPPING` | 56 | `ASSIGNED_QUALITY=1` | `—` | — |
| `ING_OUTER_DOT1P_MAPPING_TABLE` | 15 | `NEW_CFI=1` | `—` | — |
| `ING_ROUTED_INT_PRI_MAPPING` | 15 | `NEW_INT_PRI=1` | `—` | — |
| `ESBS_PORT_TO_PIPE_MAPPING` | 1 | `BITMAP=0x02001ffe00000001fe` | `—` | — |
| `ISBS_PORT_TO_PIPE_MAPPING` | 1 | `BITMAP=0x02001ffe00000001fe` | `—` | — |


### Parity init

**Registers (83):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `ALTERNATE_EMIRROR_BITMAP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `BCAST_BLOCK_MASK_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `CPB_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `CPU_TS_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `DLB_HGT_FLOWSET_PORT_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `DLB_HGT_FLOWSET_TIMESTAMP_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `DSCP_TABLE_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `E2E_HOL_STATUS_1_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `E2E_HOL_STATUS_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `EGR_EDATABUF_PARITY_CONTROL` | 1 | `0x0001ffff` | — |
| `EGR_EHCPM_ECC_PARITY_CONTROL` | 1 | `0x00000003` | — |
| `EGR_EL3_ECC_PARITY_CONTROL` | 1 | `0x00000fff` | — |
| `EGR_MASK_MODBASE_PARITY_CONTROL` | 1 | `0x00000001` | — |
| `EGR_MASK_PARITY_CONTROL` | 1 | `0x00000001` | — |
| _...68 more_ | | | |


### (misc)

**Registers (120):**

| Register | Cumulus scopes | Sample value | Our code refs |
|---|--:|---|---|
| `EGR_MTU` | 52 | `0x000045f2` | datapath.c |
| `STORM_CONTROL_METER_CONFIG` | 52 | `0x00000fa0` | datapath.c |
| `CBL_ATTRIBUTE` | 4 | `0x00000001` | — |
| `EGR_OUTER_TPID` | 3 | `0x00008100` | — |
| `ING_MPLS_TPID` | 3 | `0x00008100` | — |
| `ING_OUTER_TPID` | 3 | `0x00008100` | — |
| `PG4_INTR_ENABLE` | 2 | `0x0000001f` | — |
| `PG5_INTR_ENABLE` | 2 | `0x0000003f` | — |
| `PORT_GROUP4_BOD_FIFO_ECC_ENABLE` | 2 | `0x00000001` | — |
| `PORT_GROUP4_TDM_CONTROL` | 2 | `0x0000003e` | — |
| `PORT_GROUP4_TDM_REG_0` | 2 | `0x211d1915` | — |
| `PORT_GROUP4_TDM_REG_1` | 2 | `0x221e1a16` | — |
| `PORT_GROUP4_TDM_REG_2` | 2 | `0x231f1b17` | — |
| `PORT_GROUP4_TDM_REG_3` | 2 | `0x24201c18` | — |
| `PORT_GROUP4_TDM_REG_4` | 2 | `0x211d1915` | — |
| _...105 more_ | | | |

**Memories (58):**

| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |
|---|--:|---|---|---|
| `EGR_PRI_CNG_MAP` | 1188 | `CFI=1` | `—` | — |
| `EGR_MAP_MH` | 989 | `HG_TC=1,` | `—` | — |
| `VLAN_PROTOCOL_DATA` | 832 | `VLAN_ID=0xce5,OVID=0xce5,` | `—` | — |
| `TOS_FN` | 255 | `FN1=1,FN0=1,` | `—` | — |
| `TTL_FN` | 255 | `FN1=1,FN0=1,` | `—` | — |
| `SYSTEM_CONFIG_TABLE` | 128 | `OUTER_TPID_ENABLE=1,` | `—` | — |
| `EGR_PERQ_XMT_COUNTERS_BASE_ADDR` | 112 | `BASE=0xa` | `—` | — |
| `EGR_MMU_REQUESTS` | 66 | `OUTSTANDING_MMU_REQUESTS=4` | `—` | — |
| `EGR_MMU_REQUESTS_X` | 66 | `OUTSTANDING_MMU_REQUESTS=4` | `—` | — |
| `EGR_PORT_REQUESTS` | 66 | `OUTSTANDING_PORT_REQUESTS=1` | `—` | — |
| `EGR_PORT_REQUESTS_X` | 66 | `OUTSTANDING_PORT_REQUESTS=1` | `—` | — |
| `TCP_FN` | 63 | `FN1=1,FN0=1` | `—` | — |
| `EGR_MMU_REQUESTS_Y` | 57 | `OUTSTANDING_MMU_REQUESTS=6` | `—` | — |
| `EGR_PORT_REQUESTS_Y` | 57 | `OUTSTANDING_PORT_REQUESTS=4` | `—` | — |
| `EGR_PORT` | 55 | `EN_EFILTER=1,EM_SRCMOD_CHANGE=1,EFP_FILTER_ENABLE=1,DUAL_MOD` | `—` | — |
| _...43 more_ | | | | |


## Summary by subsystem

| Subsystem | Cumulus regs / mems | Our edged regs / mems | Match status |
|---|---|---|---|
| **L3 forwarding** | 17 / 30 | 0 / 4 | ⚠ 0/17 regs, 4/30 mems |
| **L2 / MAC table** | 10 / 6 | 0 / 0 | ❌ no memory writes |
| **VLAN / STP / port-tab** | 3 / 4 | 1 / 0 | ❌ no memory writes |
| **FP / ACL** | 21 / 23 | 0 / 0 | ❌ no memory writes |
| **EPC / egress port** | 0 / 1 | 0 / 0 | ❌ no memory writes |
| **MMU** | 85 / 0 | 30 / 0 | ⚠ 30/85 regs, 0/0 mems |
| **XLPORT MAC** | 57 / 0 | 11 / 0 | ⚠ 11/57 regs, 0/0 mems |
| **Hash / RTAG7** | 11 / 1 | 9 / 0 | ❌ no memory writes |
| **CPU punt control** | 1 / 0 | 1 / 0 | ✅ all writes covered |
| **Port mapping** | 1 / 9 | 0 / 0 | ❌ no memory writes |
| **Parity init** | 83 / 0 | 0 / 0 | ❌ untouched |
| **(misc)** | 120 / 58 | 10 / 1 | ⚠ 10/120 regs, 1/58 mems |

## What this surfaces

Reading the per-subsystem tables above, the categories where Cumulus has
**memory entries** (not just register values) that we haven't touched stand out.
These are tables with *content* — chip rows that contain forwarding rules,
not just configuration flags.  In particular:

- **L3 forwarding memories**: Cumulus has populated L3_DEFIPm, L3_ENTRY_IPV4_UNICASTm,
  EGR_L3_NEXT_HOPm, ING_L3_NEXT_HOPm, L3_ECMPm, MY_STATION_TCAMm with actual *routes*.
  Our edged programs L3_HOST + MY_STATION_TCAM via OpenMDK BMD APIs.
  Cross-reference with the raw dumps in `deep_mine_*/12d_*` and `trace_hash_redo/11*-12*` —
  those have the ACTUAL chip rows Cumulus had at capture time.

- **FP / ACL memories**: Cumulus has FP_TCAMm + FP_POLICY_TABLEm + FP_METER_TABLEm with
  the OSPF/BGP/ICMP/BFD CPU-trap rules.  Our edged writes ZERO FP entries.
  Raw dumps: `deep_mine_*/09_FP_*_raw.txt`.

- **VLAN / STP memories**: VLAN_TABm content per VID (we partially write via BMD),
  EGR_VLANm (we partially write), LPORT_TABm (we write V4/V6_L3_ENABLE + VT_ENABLE=0),
  STG_TABm (we set FORWARDING via the patched bmd_port_stp_set).

- **MMU memories**: VAST.  OP_QUEUE_CONFIG_CELLm, PG_*_CELLm, BUFFER_*m all live as
  per-port-per-queue entries.  We write some via direct CDK macros in datapath_rc_full.

- **EPC / egress-port memories**: EGR_PORTm per port — egress-side port config.
  This is where Cumulus stores per-port egress rules.  We don't write to it.

## How to use this for the chip→CPU drop

1. Pick the subsystem that's most likely the silent-drop cause (e.g. EPC / FP / L2).
2. Open the per-subsystem table above; identify a specific memory or register that's
   non-zero in Cumulus but zero in our edged.
3. Open the raw dump file referenced (e.g. `deep_mine_*/09_FP_TCAM_raw.txt`).
4. Use OpenMDK's `WRITE_<MEMNAME>m` (or `bmd_*` API) to populate the equivalent
   row in `asic/edged/datapath.c` or a new module.
5. Re-run regdump + ping test.

This doc is the index; the per-row work is straight implementation.

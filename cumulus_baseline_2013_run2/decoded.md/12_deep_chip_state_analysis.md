# BCM56846 Deep Chip-State Analysis — Cumulus vs EdgeNOS

This document analyses every register Cumulus 2.5.0 changes from chip
reset defaults on a working AS5610-52X (data: `dump_soc_diff.txt`,
6,415 register/scope entries) and groups them by chip-pipeline stage,
with cross-reference to what EdgeNOS currently programs.

**Goal:** identify which subset of Cumulus's chip writes is the gate that
currently keeps frames from being enqueued to the CPU port (CMICm DCB).

**Snapshot date:** 2026-05-14, after 3 rounds of regdump-diff porting.
**Total registers Cumulus changes:** 417
**Total still-DIFF in our chip:** 403

## By pipeline stage

Rough flow on BCM56846 / Trident+ chip:

```
        Port MAC → IPIPE (ingress) → MMU → EPIPE (egress) → Port MAC
                  │
                  └─ L2 bridging │ L3 lookup │ FP/ACL │ Hash │ CPU punt

        MMU = central buffer manager + multi-level scheduler (S2/S3)
              Output queues (per port per CoS) + colour cells + service pools
```

Below: for each stage, the registers Cumulus changed, with:
- name + brief description
- number of scopes (per-port / per-queue) Cumulus changed it on
- sample Cumulus value vs ours
- whether we still differ

### MMU + scheduler

**84 unique registers, 4208 scope-writes; ~2852 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `S3_COSWEIGHTS` ⚠ | 928 | `0x00000090` | `0x00000000` | Egress Scheduler Weight for each queue in WRR & WERR modes |
| `S2_COSWEIGHTS` ⚠ | 468 | `0x00000090` | `0x00000000` | Egress Scheduler Weight for each queue in WRR & WERR modes |
| `OP_QUEUE_LIMIT_COLOR_CELL` ⚠ | 313 | `0x00000007` | `0x00000007` | OP_QUEUE_LIMIT_COLOR_CELL |
| `OP_QUEUE_RESET_OFFSET_CELL` ⚠ | 313 | `0x00000003` | `0x00000003` | OP_QUEUE_RESET_OFFSET_CELL |
| `OVQ_MCQ_CREDITS` ⚠ | 265 | `0x000000c0` | `0x0000000c` | OVQ_MCQ_FIFO_CREDITS |
| `MCQ_FIFO_BASE_REG` ⚠ | 212 | `0x000000c0` | `0x000000c0` | MCQ_FIFO_BASE_REG |
| `OP_QUEUE_CONFIG1_CELL` ⚠ | 164 | `0x00000008` | `0x00000040` | OP_QUEUE_CONFIG1_CELL |
| `PG_SHARED_LIMIT_CELL` ⚠ | 162 | `0x000211c4` | `0x000011c4` | For packets with inner/outer VLAN tag, the first 256-entries |
| `PG_MIN_CELL` ⚠ | 159 | `0x0000002d` | `0x0000002d` | PG_MIN_CELL |
| `S2_S3_ROUTING` ⚠ | 159 | `0x00001ff814941ca4` | `0x928398a4` | The S3 group number routed to this S2 ETS group input, 0x1F  |
| `MMU_TO_LOGIC_PORT_MAPPING` ⚠ | 65 | `0x00000009` | `0x00000001` | ? |
| `MMU_TO_PHY_PORT_MAPPING` ⚠ | 65 | `0x00000005` | `0x00000005` | ? |
| `OP_QUEUE_CONFIG_CELL` ⚠ | 61 | `0x01330819` | `0x03990819` | OP_QUEUE_CONFIG_CELL |
| `OP_PORT_LIMIT_COLOR_CELL` ⚠ | 54 | `0x0000130b` | `0x0000130b` | OP_PORT_LIMIT_COLOR_CELL |
| `OP_PORT_LIMIT_RESUME_COLOR_CELL` ⚠ | 54 | `0x0000130a` | `0x00000000` | OP_PORT_LIMIT_RESUME_COLOR_CELL |
| `PG_RESET_OFFSET_CELL` ⚠ | 54 | `0x00010010` | `0x00000010` | PG_RESET_OFFSET_CELL |
| `PORT_MAX_PKT_SIZE` ⚠ | 54 | `0x0000002d` | `0x0000002d` | PORT_MAX_PKT_SIZE |
| `PORT_PG_SPID` ⚠ | 54 | `0x00004020` | `0x00004020` | PORT_PG_SPID |
| `PORT_PRI_GRP0` ⚠ | 54 | `0x00e00080` | `0x00ffffff` | PORT_PRI_GRP0 |
| `PORT_RESUME_LIMIT_CELL` ⚠ | 54 | `0x0000b3f0` | `0x0000b3f0` | PORT_RESUME_LIMIT |
| `TOQ_EP_CREDIT` ⚠ | 54 | `0x00000004` | `0x00000004` | Egress cell request counter |
| `S2_CONFIG` ⚠ | 53 | `0x0000003f` | `0x0000003f` | Egress Scheduler Configuration Register for stage 2 schedule |
| `S3_CONFIG` ⚠ | 53 | `0x000001ff` | `0x000001ff` | Egress Scheduler Configuration Register for stage 3 schedule |
| `ESCONFIG` ⚠ | 52 | `0x00000003` | `0x00000003` | Egress Scheduler Configuration Register for stage 1 schedule |
| `OP_UC_PORT_CONFIG1_CELL` ⚠ | 52 | `0x00008040` | `0x00000000` | OP_UC_PORT_CONFIG1_CELL |
| _...59 more registers in this stage..._ | | | | |


### IPIPE — L2 bridging

**23 unique registers, 74 scope-writes; ~73 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `MAC_1` ⚠ | 52 | `0x0000caaf` | `0x00000000` | MAC Block Mask Table. |
| `EMIRROR_CONTROL2_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for EMIRROR_CONTROL2 table, FeatureSpecific-E |
| `L2_AGE_TIMER` ⚠ | 1 | `0x00000000` | `0x0000012c` | Age Timer Register |
| `L2_AUX_HASH_CONTROL` ⚠ | 1 | `0x00000013` | `0x00000000` | L2_AUX_HASH_CONTROL. |
| `L2_BULK_CONTROL` ⚠ | 1 | `0x0000001b` | `0x00000000` | L2 Bulk match enable. |
| `L2_ENTRY_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L2_ENTRY_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L2_LEARN_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | FIFO for operations that MODify the L2_ENTRY table. FeatureS |
| `L2_MOD_FIFO_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L2_MOD_FIFO_PARITY_CONTROL |
| `L2_MOD_FIFO_RD_PTR` ⚠ | 1 | `0x00000004` | `0x00000000` | L2_MOD_FIFO_RD_PTR, FeatureSpecific-Ethernet |
| `L2_MOD_FIFO_WR_PTR` ⚠ | 1 | `0x00000004` | `0x00000000` | Combined L2_ENTRY TCAM/Data RAM for guaranteed L2 entries an |
| `L2_USER_ENTRY_CAM_DBGCTRL` ✓ | 1 | `0x0003c000` | `0x0003c000` | L2_USER_ENTRY_CAM_CONTROL, FeatureSpecific-Ethernet |
| `L2_USER_ENTRY_DATA_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L2_USER_ENTRY_DATA_PARITY_CONTROL |
| `MAC_BLOCK_TABLE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for MAC_BLOCK_TABLE table, FeatureSpecific-Et |
| `NIV_VLAN_TAGGED_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for NIV_VLAN_TAGGED table, FeatureSpecific-Et |
| `VLAN_COS_MAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for VLAN_COS_MAP table, FeatureSpecific-Ether |
| `VLAN_MPLS_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_MPLS_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `VLAN_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_PARITY_CONTROL |
| `VLAN_PROFILE_2_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for VLAN_PROFILE_2 table, FeatureSpecific-Eth |
| `VLAN_PROT_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_PROT_PARITY_CONTROL |
| `VLAN_RANGE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_RANGE_PARITY_CONTROL |
| `VLAN_STG_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_STG_PARITY_CONTROL |
| `VLAN_SUBNET_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_SUBNET_PARITY_CONTROL |
| `VLAN_XLATE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VLAN_XLATE_PARITY_CONTROL |


### IPIPE — L3 lookup

**19 unique registers, 20 scope-writes; ~19 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `RTAG7_HASH_TRILL_ECMP` ⚠ | 2 | `0x00004000` | `0x00000000` | RTAG7 hash control register for TRILL ECMP. |
| `EMIRROR_CONTROL3_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for EMIRROR_CONTROL3 table, FeatureSpecific-E |
| `ING_L3_NEXT_HOP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | ING_L3_NEXT_HOP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROL |
| `INITIAL_L3_ECMP_GROUP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | INITIAL_L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethern |
| `INITIAL_L3_ECMP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | INITIAL_L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_AUX_HASH_CONTROL` ⚠ | 1 | `0x00000015` | `0x00000000` | L3 Default IP Route (LPM) TCAM view with data and hit bits.  |
| `L3_DEFIP_128_CAM_ENABLE` ✓ | 1 | `0x00000003` | `0x00000003` | L3_DEFIP_128_CAM_ENABLE, FeatureSpecific-Ethernet |
| `L3_DEFIP_128_DATA_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_DEFIP_128_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_DEFIP_DATA_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_DEFIP_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_ECMP_GROUP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_ECMP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_ENTRY_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_ENTRY_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_IIF_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_IIF_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_IPMC_1_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_IPMC_1_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_IPMC_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_IPMC_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_IPMC_REMAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_IPMC_REMAP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `L3_MTU_VALUES_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Controls for L3_MTU_VALUES, FeatureSpecific-Ethernet |
| `L3_TUNNEL_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | L3_TUNNEL_PARITY_CONTROL |


### IPIPE — FP/ACL filter

**17 unique registers, 70 scope-writes; ~65 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `IFP_GM_LOGICAL_TO_PHYSICAL_MAPPING` ⚠ | 54 | `0x00000000` | `0x00000000` | ? |
| `FP_FIELD_SEL_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | FP_FIELD_SEL_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `FP_GM_TCAM_BLK_SEL` ✓ | 1 | `0x00000fff` | `0x00000fff` | FP_GM_TCAM_BLK_SEL, FeatureSpecific-FP |
| `FP_SLICE_ENABLE` ⚠ | 1 | `0x000e33ff` | `0x000fffff` | Slice enable control for ingress fp. |
| `FP_TCAM_BLK_SEL` ✓ | 1 | `0x00000fff` | `0x00000fff` | FP UDF offset table, FeatureSpecific-FP. |
| `FP_UDF_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | FP_UDF_PARITY_CONTROL |
| `IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROL |
| `IFP_COUNTER_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_COUNTER_PARITY_CONTROL |
| `IFP_ING_DVP_2_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_ING_DVP_2_PARITY_CONTROL |
| `IFP_METER_MUX_DATA_STAGING_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_METER_MUX_DATA_STAGING_PARITY_CONTROL |
| `IFP_POLICY_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_POLICY_PARITY_CONTROL |
| `IFP_PWR_WATCH_DOG_STATUS` ✓ | 1 | `0x80000000` | `0x80000000` | Contains the number of members in each ECMP group.  Used wit |
| `IFP_REDIRECTION_PROFILE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_REDIRECTION_PROFILE_PARITY_CONTROL, FeatureSpecific-Ethe |
| `IFP_STORM_CONTROL_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IFP_STORM_CONTROL_PARITY_CONTROL |
| `SW2_FP_DST_ACTION_CONTROL` ⚠ | 1 | `0x0000000c` | `0x00000000` | Enable functions when IFP generates a REDIRECT, REPLACE_PBM  |
| `VFP_KEY_CONTROL` ⚠ | 1 | `0x00000003` | `0x00000000` | VFP slice key control register. |
| `VFP_POLICY_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | VFP_POLICY_PARITY_CONTROL |


### IPIPE — hash

**10 unique registers, 10 scope-writes; ~7 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `HASH_CONTROL` ✓ | 1 | `0x0dd14000` | `0x0dd14000` | HG-Trunk DLB Control. |
| `MPLS_ENTRY_HASH_CONTROL` ⚠ | 1 | `0x0000004a` | `0x0000000a` | MPLS_ENTRY_HASH_CONTROL, FeatureSpecific-MPLS. |
| `RTAG7_HASH_CONTROL_3` ✓ | 1 | `0x00000009` | `0x00000009` | Hash control register 2 for Rtag7 hashing. |
| `RTAG7_HASH_FIELD_BMAP_1` ⚠ | 1 | `0x00000f1c` | `0x00001e1c` | Rtag7 hashing field selection bitmap register1. |
| `RTAG7_HASH_FIELD_BMAP_2` ⚠ | 1 | `0x00000f1c` | `0x00001e1c` | Rtag7 hashing field selection bitmap register2. |
| `RTAG7_HASH_SEED_A` ✓ | 1 | `0x0000002a` | `0x0000002a` | Hash Seed for Rtag7 hashing. |
| `RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1` ⚠ | 1 | `0x00000f3c` | `0x00001e7c` | Rtag7 IPV4 TCP/UDP Source-equals-Dest Field Bitmap control r |
| `RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2` ⚠ | 1 | `0x00000f7c` | `0x00001efc` | Rtag7 IPV4 TCP/UDP Field Bitmap control register. |
| `RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1` ⚠ | 1 | `0x00000f3c` | `0x00001e7c` | Rtag7 IPV6 TCP/UDP Source=Dest Field Bitmap control register |
| `RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2` ⚠ | 1 | `0x00000f7c` | `0x00001efc` | Rtag7 IPV6 TCP/UDP Field Bitmap control register. |


### IPIPE — CPU punt control

**1 unique registers, 1 scope-writes; ~1 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `CPU_CONTROL_1` ⚠ | 1 | `0x18500600` | `0x00500600` | Control Register for Packets sent to the CPU. |


### IPIPE (other)

**86 unique registers, 251 scope-writes; ~99 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `COSWEIGHTS` ⚠ | 104 | `0x00000010` | `0x00000010` | Select one of four sections of COS_MAP table. |
| `STORM_CONTROL_METER_CONFIG` ⚠ | 52 | `0x00000fa0` | `0x00001100` | Per-port configuration and enables for storm control meters. |
| `CBL_ATTRIBUTE` ⚠ | 4 | `0x00000001` | `0x00000000` | Class based station movement attribute register, index from  |
| `ING_MPLS_TPID` ✓ | 3 | `0x00008100` | `0x00008100` | Ingress Outer TPID register. |
| `ING_OUTER_TPID` ✓ | 3 | `0x00008100` | `0x00008100` | Ingress Outer TPID register. |
| `RDBGC1` ⚠ | 2 | `0x0000046b` | `0x00000000` | Receive debug counter #1. |
| `RIPC4` ⚠ | 2 | `0x00000132` | `0x00000000` | Receive IPv4 L3 Unicast Frame Counter. |
| `RUC` ⚠ | 2 | `0x00000152` | `0x00000000` | Receive Unicast Counter. |
| `TBYT` ⚠ | 2 | `0x0000000000026720` | `0x00000000` | TCP function table to map TCP Flags to any value for an IFP  |
| `ARB_EOP_DEBUG` ⚠ | 1 | `0x00020000` | `0x00000000` | Forces accesses to stages to be eop resource |
| `AUX_ARB_CONTROL` ⚠ | 1 | `0x00000012` | `0x00000000` | IP auxilary arbiter control register for L2 table |
| `AUX_ARB_CONTROL_2` ✓ | 1 | `0x0327f863` | `0x0327f863` | Broadcast Block Mask, FeatureSpecific-Ethernet. |
| `DLB_HGT_CURRENT_TIME` ⚠ | 1 | `0x000879e5` | `0x00004378` | DLB_HGT Current Time. |
| `DLB_HGT_QUALITY_MEASURE_CONTROL` ⚠ | 1 | `0x00000003` | `0x00000000` | DLB_HGT Quality Measure Update Control Register. |
| `GLOBAL_MPLS_RANGE_1_UPPER` ⚠ | 1 | `0x000fffff` | `0x00000000` | MPLS label first global range upper bound. (Inclusive). |
| `GLOBAL_MPLS_RANGE_2_UPPER` ⚠ | 1 | `0x000fffff` | `0x00000000` | MPLS label second global range upper bound. (Inclusive). |
| `IARB_HDR_ECC_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IARB_HDR_ECC_CONTROL, FeatureSpecific-Ethernet |
| `IARB_LEARN_FIFO_ECC_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | TDM TABLE configuration, Set to 0, select port_group5. Set t |
| `IARB_PKT_ECC_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | IARB_PKT_ECC_CONTROL, FeatureSpecific-Ethernet |
| `IARB_TDM_CONTROL` ✓ | 1 | `0x00000080` | `0x00000080` | TDM TABLE configuration |
| `IGMP_MLD_PKT_CONTROL` ⚠ | 1 | `0x01249000` | `0x00000051` | IGMP/MLD Control Register. |
| `IL2LU_PWR_WATCH_DOG_STATUS` ✓ | 1 | `0x80000000` | `0x80000000` | IL2LU_PWR_WATCH_DOG_STATUS, FeatureSpecific-Ethernet |
| `ING_CONFIG_64` ⚠ | 1 | `0x000401802080300e` | `0x0000000e` | Switch configuration register. |
| `ING_EVENT_DEBUG_Y` ⚠ | 1 | `0x00000002` | `0x00000000` | Ingress Events Debug Register. |
| `ING_MISC_CONFIG2` ⚠ | 1 | `0x00000080` | `0x00000000` | Ingress misc config register #2. |
| _...61 more registers in this stage..._ | | | | |


### EPIPE (egress)

**29 unique registers, 133 scope-writes; ~31 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `EGR_MTU` ⚠ | 52 | `0x000045f2` | `0x00003fff` | Egress MTU Register. |
| `EGR_VLAN_CONTROL_1` ⚠ | 52 | `0x00002001` | `0x00000800` | Controls Vlan Translate and VLAN membership related function |
| `EGR_OUTER_TPID` ✓ | 3 | `0x00008100` | `0x00008100` | Egress Outer TPID register. |
| `EFP_METER_CONTROL` ⚠ | 1 | `0x00000003` | `0x00000000` | EFP_METER_CONTROL. |
| `EFP_METER_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | EFP_METER_PARITY_CONTROL |
| `EFP_POLICY_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | EFP_POLICY_PARITY_CONTROL |
| `EFP_SLICE_CONTROL` ⚠ | 1 | `0x000900cf` | `0x000000ff` | EFP_SLICE_CONTROL. |
| `EFP_SLICE_MAP` ⚠ | 1 | `0x00004ee4` | `0x0000e4e4` | TCAM FOR EFP. |
| `EFP_TCAM_BLKSEL` ✓ | 1 | `0x000000ff` | `0x000000ff` | EFP_TCAM_BLKSEL |
| `EGR_CONFIG_1` ⚠ | 1 | `0x00006001` | `0x00004000` | Configuration Register Extension for the entire chip. |
| `EGR_EDATABUF_PARITY_CONTROL` ⚠ | 1 | `0x0001ffff` | `0x00000000` | Continuation of ram controls |
| `EGR_EHCPM_ECC_PARITY_CONTROL` ⚠ | 1 | `0x00000003` | `0x00000000` | Control ecc/parity functions of EHCPM RAMS |
| `EGR_EL3_ECC_PARITY_CONTROL` ⚠ | 1 | `0x00000fff` | `0x00000000` | EGR_L3_INTF_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `EGR_HW_RESET_CONTROL_1` ✓ | 1 | `0x00000000` | `0x00000000` | Mirror to Port Table to be used for IM tagged packets. |
| `EGR_INTR0_ENABLE` ⚠ | 1 | `0x03ffffff` | `0x00000000` | Bitwise interrupt enable for EGR_INTR0_STATUS |
| `EGR_INTR1_ENABLE` ⚠ | 1 | `0x000fffff` | `0x00000000` | Bitwise interrupt enable for EGR_INTR1_STATUS |
| `EGR_MC_CONTROL_1` ⚠ | 1 | `0x10000000` | `0x00000000` | TBfilled |
| `EGR_MC_CONTROL_2` ⚠ | 1 | `0x00002000` | `0x00000000` | TBfilled |
| `EGR_PW_INIT_COUNTERS_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | EGR_PW_INIT_COUNTERS_PARITY_CONTROL, FeatureSpecific-Etherne |
| `EGR_Q_BEGIN` ⚠ | 1 | `0x00100000` | `0x00000000` | Register starts an EQ Bus which is provided for later ECO re |
| `EGR_Q_END` ⚠ | 1 | `0x00100000` | `0x00000000` | Register starts an EQ Bus which is provided for later ECO re |
| `EGR_VLAN_PARITY_CONTROL` ⚠ | 1 | `0x00000fff` | `0x00000000` | EGR_VLAN_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `TDBGC0_SELECT` ⚠ | 1 | `0x00000050` | `0x00000000` | Transmit debug counter #0 Trigger Select Register. |
| `TDBGC1_SELECT` ⚠ | 1 | `0x000000a0` | `0x00000000` | Transmit debug counter #1 Trigger Select Register. |
| `TDBGC2_SELECT` ⚠ | 1 | `0x00000040` | `0x00000000` | Transmit debug counter #2 Trigger Select Register. |
| _...4 more registers in this stage..._ | | | | |


### XLPORT (MAC/SERDES)

**55 unique registers, 1184 scope-writes; ~533 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `COMMAND_CONFIG` ✓ | 52 | `0x11800158` | `0x11800158` | Command register. Used by the host processor to control and  |
| `IPG_HD_BKP_CNTL` ✓ | 52 | `0x00000014` | `0x00000014` | The control register for HD-BackPressure. |
| `LAG_FAILOVER_CONFIG` ✓ | 52 | `0x00000008` | `0x00000008` | XLPORT LAG Failover Loopback Config |
| `MAC_0` ⚠ | 52 | `0x80a23581` | `0x00000000` | MAC Address 32-Bit Word 0. Core MAC address bit 47 to 16. |
| `MAC_MODE` ✓ | 52 | `0x00000022` | `0x00000022` | MAC Mode. MAC Speed and Duplex Mode configuration from regis |
| `MAC_PFC_REFRESH_CTRL` ⚠ | 52 | `0xc0000001` | `0x7fff0000` | PPP refresh control register |
| `MAC_RSV_MASK` ✓ | 52 | `0x00000018` | `0x00000018` | MAC RSV MASK Register |
| `PAUSE_CONTROL` ⚠ | 52 | `0x0003ffff` | `0x0002ffff` | PAUSE frame timer control register |
| `TX_IPG_LENGTH` ✓ | 52 | `0x0000000c` | `0x0000000c` | Programmable Inter-Packet-Gap (IPG). |
| `XLPORT_CONFIG` ✓ | 52 | `0x00010040` | `0x00010040` | XLPORT Configuration Register, per Port 0,1,2,3 |
| `XLP_TXFIFO_CELL_REQ_CNT` ⚠ | 52 | `0x00000004` | `0x00000004` | XLPORT TX FIFO Cell Request Count Register |
| `XMAC_CTRL` ⚠ | 52 | `0x0000000000000003` | `0x00000003` | MAC control. |
| `XMAC_PFC_CTRL` ⚠ | 52 | `0x00000001ffffc000` | `0xffffc000` | Transmit Per-Priority FLOW Control |
| `XMAC_RX_CTRL` ⚠ | 52 | `0x0000000000000408` | `0x00000008` | Receive control. |
| `XMAC_RX_MAC_SA` ⚠ | 52 | `0x000080a23581caaf` | `0x00000000` | Receive source address. |
| `XMAC_RX_MAX_SIZE` ✓ | 52 | `0x00000000000005f2` | `0x000005f2` | Receive maximum packet size. |
| `XMAC_TX_MAC_SA` ⚠ | 52 | `0x000080a23581caaf` | `0x00000000` | Transmit Source Address. |
| `XMODID_DUAL_EN` ✓ | 52 | `0x00000001` | `0x00000001` | Dual-modid enable |
| `XLPORT_ECC_CONTROL` ⚠ | 16 | `0x00000007` | `0x00000000` | XLPORT memories ECC control register |
| `XLPORT_INTR_ENABLE` ⚠ | 16 | `0x000003ff` | `0x00000000` | XLPORT interrupt enable register |
| `XLPORT_PORT_ENABLE` ⚠ | 16 | `0x0000000f` | `0x0000000f` | XLPORT Port Enable Register |
| `XLPORT_XGXS0_STATUS0_REG` ⚠ | 16 | `0x00000002` | `0x00080042` | Status signals from Warpcore Lane0: first set |
| `XLPORT_XGXS1_STATUS0_REG` ⚠ | 16 | `0x00000002` | `0x00000002` | Status signals from Warpcore Lane1: first set |
| `XLPORT_XGXS2_STATUS0_REG` ⚠ | 16 | `0x00000002` | `0x00000002` | Status signals from Warpcore Lane2: first set |
| `XLPORT_XGXS3_STATUS0_REG` ⚠ | 16 | `0x00000002` | `0x00000002` | Status signals from Warpcore Lane3: first set |
| _...30 more registers in this stage..._ | | | | |


### port mapping (read-only)

**2 unique registers, 108 scope-writes; ~104 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `EGR_LOGICAL_TO_PHYSICAL_PORT_NUMBER_MAPPING` ⚠ | 54 | `0x00000000` | `0x00000000` | ? |
| `EGR_VLAN_LOGICAL_TO_PHYSICAL_MAPPING` ⚠ | 54 | `0x00000000` | `0x00000000` | ? |


### parity / ECC init

**67 unique registers, 67 scope-writes; ~67 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `ALTERNATE_EMIRROR_BITMAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ALTERNATE_EMIRROR_BITMAP table, FeatureSp |
| `BCAST_BLOCK_MASK_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for BCAST_BLOCK_MASK table, FeatureSpecific-E |
| `CPB_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for CPB table, FeatureSpecific-Ethernet |
| `CPU_TS_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | CPU_TS_PARITY_CONTROL |
| `DLB_HGT_FLOWSET_PORT_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Controls for DLB_HGT_FLOWSET_PORT, FeatureSpecific-Et |
| `DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP_PAGE, FeatureS |
| `DLB_HGT_FLOWSET_TIMESTAMP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP, FeatureSpecif |
| `DSCP_TABLE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | DSCP_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `E2E_HOL_STATUS_1_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for E2E_HOL_STATUS_1 table, FeatureSpecific-E |
| `E2E_HOL_STATUS_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for E2E_HOL_STATUS table, FeatureSpecific-Eth |
| `EGR_MASK_MODBASE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | EGR_MASK_MODBASE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `EGR_MASK_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for EGR_MAS_KPORTVIEW table, FeatureSpecific- |
| `EMIRROR_CONTROL1_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for EMIRROR_CONTROL1 table, FeatureSpecific-E |
| `EMIRROR_CONTROL_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for EMIRROR_CONTROL table, FeatureSpecific-Et |
| `HG_COUNTERS_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for Higig stats counters, FeatureSpecific-Eth |
| `ICONTROL_OPCODE_BITMAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | ICONTROL_OPCODE_BITMAP_PARITY_CONTROL, FeatureSpecific-Ether |
| `IMIRROR_BITMAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for IMIRROR_BITMAP table, FeatureSpecific-Eth |
| `ING_DVP_TABLE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | ING_DVP_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `ING_EGRMSKBMAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ING_EGRMSKBMAP table, FeatureSpecific-Eth |
| `ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ING_HIGIG_TRUNK_OVERRIDE_PROFILE table, F |
| `ING_PRI_CNG_MAP_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | ING_PRI_CNG_MAP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `ING_PW_TERM_SEQ_NUM_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ING_PW_TERM_SEQ_NUM table, FeatureSpecifi |
| `ING_SERVICE_COUNTER_TABLE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ING_SERVICE_COUNTER_TABLE table, FeatureS |
| `ING_UNTAGGED_PHB_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | ING_UNTAGGED_PHB_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `ING_VINTF_COUNTER_TABLE_PARITY_CONTROL` ⚠ | 1 | `0x00000001` | `0x00000000` | Parity Control for ING_VINTF_COUNTER_TABLE table, FeatureSpe |
| _...42 more registers in this stage..._ | | | | |


### (misc)

**24 unique registers, 46 scope-writes; ~22 of those still DIFF in our chip.**

| Register | Scopes | Cumulus | Ours | Description |
|---|--:|---|---|---|
| `PG4_INTR_ENABLE` ⚠ | 2 | `0x0000001f` | `0x00000000` | PORT_GROUP4_INTR_ENABLE |
| `PG5_INTR_ENABLE` ⚠ | 2 | `0x0000003f` | `0x00000000` | PORT_GROUP5_INTR_ENABLE |
| `PORT_GROUP4_BOD_FIFO_ECC_ENABLE` ⚠ | 2 | `0x00000001` | `0x00000000` | PORT_GROUP4_BOD_FIFO_ECC_ENABLE |
| `PORT_GROUP4_TDM_CONTROL` ✓ | 2 | `0x0000003e` | `0x0000003e` | TDM TABLE Control |
| `PORT_GROUP4_TDM_REG_0` ✓ | 2 | `0x211d1915` | `0x211d1915` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_1` ⚠ | 2 | `0x221e1a16` | `0x221e1a16` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_2` ⚠ | 2 | `0x231f1b17` | `0x231f1b17` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_3` ⚠ | 2 | `0x24201c18` | `0x24201c18` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_4` ✓ | 2 | `0x211d1915` | `0x211d1915` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_5` ⚠ | 2 | `0x221e1a16` | `0x221e1a16` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_6` ⚠ | 2 | `0x231f1b17` | `0x231f1b17` | TDM TABLE configuration |
| `PORT_GROUP4_TDM_REG_7` ⚠ | 2 | `0x24201c18` | `0x24201c18` | TDM TABLE configuration |
| `PORT_GROUP5_BOD_FIFO_ECC_ENABLE` ⚠ | 2 | `0x00000001` | `0x00000000` | PORT_GROUP5_BOD_FIFO_ECC_ENABLE |
| `PORT_GROUP5_TDM_CONTROL` ✓ | 2 | `0x0000003e` | `0x0000003e` | TDM TABLE Control |
| `PORT_GROUP5_TDM_REG_0` ✓ | 2 | `0x110d0905` | `0x110d0905` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_1` ⚠ | 2 | `0x120e0a06` | `0x120e0a06` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_2` ⚠ | 2 | `0x130f0b07` | `0x130f0b07` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_3` ⚠ | 2 | `0x14100c08` | `0x14100c08` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_4` ✓ | 2 | `0x110d0905` | `0x110d0905` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_5` ⚠ | 2 | `0x120e0a06` | `0x120e0a06` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_6` ⚠ | 2 | `0x130f0b07` | `0x130f0b07` | TDM TABLE configuration |
| `PORT_GROUP5_TDM_REG_7` ⚠ | 2 | `0x14100c08` | `0x14100c08` | TDM TABLE configuration |
| `EGR_CONFIG_2` ⚠ | 1 | `0x0000001f` | `0x00000000` | ? |
| `ING_CONFIG_2` ⚠ | 1 | `0x000001ff` | `0x00000000` | ? |


## Critical gates for chip→CPU forwarding

For a broadcast/unknown-unicast frame to reach the CPU CMICm DCB ring,
every one of these gates must be open at the right time:

1. **MAC RX accepts frame** — `XMAC_CTRL.RX_EN`, `XLPORT_CONFIG`, MAC SA filtering
2. **IPIPE STP allows ingress** — `STG_TABm.SP_TREE_PORTn` for ingress port
3. **VLAN_TAB has CPU as member** — `VLAN_TABm.PORT_BITMAP`
4. **L2 lookup decides flood-to-VLAN-members** (broadcast)
    OR `MY_STATION_TCAM` hit → `L3_HOST` → next-hop = CPU port
5. **MMU has buffer for CPU queue** — `PG_MIN_CELL`, `OP_QUEUE_CONFIG`, `OP_BUFFER_SHARED_LIMIT`
6. **EPIPE STP allows egress to CPU port** — `EGR_VLAN_STGm.SP_TREE_PORT0`
7. **EPC_LINK_BMAPm has CPU bit set** — chip considers CPU 'link up'
8. **Egress scheduler dequeues CPU port** — `S2_CONFIG`, `S3_CONFIG`, `ESCONFIG`, `COSWEIGHTS`
9. **CMICm DMA armed** — DCB ring set up with `RELOAD=1`, `DESC_HALT_ADDR`

We've verified 1, 2, 3, 6, 7 directly.  We've ported parts of 5 and 8 but
none are fully matching Cumulus.  9 is done.  4 might fail for L3-routed traffic
if `MY_STATION_TCAM` doesn't match (we program it but the chip-side may have
its own match requirements).

The most likely current blockers, ranked:

1. **`*_PARITY_CONTROL` (~103 not ported)** — Cumulus's `parity_enable=1` SDK
   flag triggers init-time writes to enable parity checking on every chip
   memory.  If these aren't init'd, the chip may refuse to enqueue to certain
   memories.  (Speculation; would need to test.)
2. **Per-port `S3_COSWEIGHTS` (928 scopes)** — egress scheduler weights.  Without
   them all set, the scheduler may never select CPU port's queue for dequeue.
3. **`MMU_TO_LOGIC_PORT_MAPPING` (64 scopes)** — MMU's view of port mapping.
   Could differ from OpenMDK's hardcoded mapping → MMU writes go to wrong port.
4. **Memory-table contents** (we haven't touched `dump_socmem_diff.txt`).
   L2 MAC table entries, FP_TCAM rules, VLAN_TAB content.

## Memory tables not yet analysed

Cumulus also writes 1.47 MB worth of chip-memory data (`dump_socmem_diff.txt`)
that our regdump tool doesn't read — it's content of internal SRAMs, not
registers.  These tables back L2 forwarding, FP rules, VLAN membership, etc.

Important memories to mine:

- `L2_USER_ENTRY` — static MAC table entries.  Cumulus pre-populates own MAC.
- `VLAN_TABm` — VLAN port bitmaps + STG mapping (we set up VID 1 / 3301+).
- `EGR_VLAN_STGm` — egress STG per VLAN per port (we patched bmd_port_stp_set).
- `STG_TABm` — ingress STG per port.
- `FP_TCAMm` + `FP_POLICY_TABLEm` + `FP_METER_TABLEm` + `FP_GLOBAL_MASK_TCAMm`
  — Cumulus has ~100 FP entries for OSPF/BGP/ICMP/BFD trap rules.
- `EGR_PORTm` + `EGR_VLAN_CONTROLm` — egress port-level config tables.
- `L3_HOSTm` + `L3_DEFIPm` — L3 forwarding tables (we partially program).
- `MY_STATION_TCAM` — chip-side 'my MAC' match table.

Mining strategy (TODO next-session):
1. Parse `dump_socmem_diff.txt` (1.47 MB; format is similar to register diff).
2. Group by memory name.
3. For each memory, count non-default entries; sample the most-populated.
4. Use OpenMDK's `WRITE_<MEM>m_<FIELD>f_SET` macros to replicate in `edged`.

## Recommended next-day actions, in order

1. **Port `*_PARITY_CONTROL` writes** (~103 of them, all value 0x1).  Simple
   to add — single bit set per register, no per-port scope.  Cheap test:
   does any chip-level behaviour change?
2. **Compare `bcm56840_a0_p2m` (OpenMDK port map) byte-by-byte with Cumulus's
   `portmap_N.0` from `11ports.bcm`**.  If they differ for swp1/swp2, our
   per-port writes are landing on the wrong chip ports.
3. **Mine `dump_socmem_diff.txt`** for memory-table content; port the L2_USER,
   VLAN_TAB content, and any FP_TCAM trap rules.
4. **Static-RE switchd binary**: find `bcm_init_check` / `bcm_init_selective`
   (visible as strings) and read disassembly.  These are the SDK's top-level
   init entry points called by `bcmcmd init all`.

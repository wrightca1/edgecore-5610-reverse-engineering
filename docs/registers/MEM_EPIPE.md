# BCM56846 Memories (tables) — EPIPE block

_Egress pipeline — egress VLAN, modification, mirroring, egress policy_

75 memories.

---

## EGR_MAC_DA_PROFILEm

- **Base address:** `0x01262000`  ·  **Entries:** 512  ·  **Entry width:** 7 bytes
- **Function:** MAC-DA values for use when doing MPLS packet mods, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[48]` | EVEN_PARITY |

---

## EGR_L3_INTFm

- **Base address:** `0x01264000`  ·  **Entries:** 4096  ·  **Entry width:** 15 bytes
- **Function:** L3 Interface Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[10:0]` | MPLS_TUNNEL_INDEX |
    | `[10:2]` | TUNNEL_INDEX |
    | `[12:11]` | DSCP_SEL |
    | `[24:13]` | OVID |
    | `[24:13]` | VID |
    | `[81]` | IVID_VALID |
    | `[93:82]` | IVID |
    | `[100]` | DSCP_UNUSED |
    | `[102:101]` | OPRI_OCFI_SEL |
    | `[106:103]` | OPRI_OCFI_MAPPING_PROFILE |
    | `[105:103]` | OPRI |
    | `[106]` | OCFI |
    | `[108:107]` | IPRI_ICFI_SEL |
    | `[112:109]` | IPRI_ICFI_MAPPING_PROFILE |
    | `[111:109]` | IPRI |
    | `[112]` | ICFI |
    | `[113]` | L2_SWITCH |
    | `[114]` | EVEN_PARITY |

**Live capture (Cumulus):** 53 entries populated. Sample:

    epipe0[1]: <VID=0xce5,OVID=0xce5,MAC_ADDRESS=0x80a23581caaf,>

---

## EGR_MPLS_VC_AND_SWAP_LABEL_TABLEm

- **Base address:** `0x01268000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** MPLS VC and SWAP Label Table, FeatureSpecific-MPLS

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | MPLS_LABEL |
    | `[22:20]` | MPLS_EXP |
    | `[30:23]` | MPLS_TTL |
    | `[34:33]` | CW_INSERT_FLAG |
    | `[36:35]` | MPLS_EXP_SELECT |
    | `[40:37]` | MPLS_EXP_MAPPING_PTR |
    | `[37]` | NEW_CFI |
    | `[40:38]` | NEW_PRI |
    | `[41]` | UPDATE_PW_INIT_COUNTERS |
    | `[44:42]` | SD_TAG_ACTION_IF_PRESENT |
    | `[46:45]` | SD_TAG_ACTION_IF_NOT_PRESENT |
    | `[48:47]` | SD_TAG_TPID_INDEX |
    | `[60:49]` | SD_TAG_VID |
    | `[61]` | SD_TAG_DOT1P_PRI_SELECT |
    | `[62]` | SD_TAG_NEW_CFI |
    | `[66]` | SD_TAG_REMARK_CFI |
    | `[67]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <MPLS_LABEL_ACTION=3,>

---

## EGR_IPMCm

- **Base address:** `0x0126c000`  ·  **Entries:** 4096  ·  **Entry width:** 1 bytes
- **Function:** Per IPMC group attributes needed in EP, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DONT_PRUNE_VLAN |
    | `[1]` | L3_PAYLOAD |
    | `[5:2]` | TRILL_TREE_PROFILE_PTR |
    | `[6]` | IPMC_GROUP_TYPE |
    | `[7]` | EVEN_PARITY |

---

## EGR_ING_PORTm

- **Base address:** `0x01270000`  ·  **Entries:** 67  ·  **Entry width:** 1 bytes
- **Function:** Configuration Register for Ingress Port. This is different for each GE, 10GE port. FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PORT_TYPE |
    | `[2]` | HIGIG2 |

**Live capture (Cumulus):** 2 entries populated. Sample:

    epipe0[65]: <PORT_TYPE=2,>

---

## EGR_QCN_CNM_CONTROL_TABLEm

- **Base address:** `0x01272000`  ·  **Entries:** 1  ·  **Entry width:** 15 bytes
- **Function:** QCN CNM Control table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[119:96]` | QCN_CPID_PREFIX |

---

## EGR_TRILL_TREE_PROFILEm

- **Base address:** `0x01274000`  ·  **Entries:** 16  ·  **Entry width:** 3 bytes
- **Function:** Trill Tree profile table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | HOPCOUNT |
    | `[21:6]` | ROOT_RBRIDGE_NICKNAME |

---

## EGR_MAP_MHm

- **Base address:** `0x01278000`  ·  **Entries:** 1056  ·  **Entry width:** 1 bytes
- **Function:** Used for mapping incoming PBE MH_PRIORITY into a new MH_PRIORITY/TC For Higig+/Higig2 header, on a per-egress-port basis.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | HG_TC |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 989 entries populated. Sample:

    epipe0[1]: <HG_TC=1,>

---

## EGR_FRAGMENT_ID_TABLE_Xm

- **Base address:** `0x02231000`  ·  **Entries:** 512  ·  **Entry width:** 3 bytes
- **Function:** IPv4 Tunnel Fragment ID Table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | FRAGMENT_ID |
    | `[16]` | EVEN_PARITY |

---

## EGR_FRAGMENT_ID_TABLE_Ym

- **Base address:** `0x02251000`  ·  **Entries:** 512  ·  **Entry width:** 3 bytes
- **Function:** IPv4 Tunnel Fragment ID Table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | FRAGMENT_ID |
    | `[16]` | EVEN_PARITY |

---

## EGR_VLAN_STGm

- **Base address:** `0x02261000`  ·  **Entries:** 512  ·  **Entry width:** 18 bytes
- **Function:** Egress Spanning Tree Stage Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SP_TREE_PORT0 |
    | `[3:2]` | SP_TREE_PORT1 |
    | `[5:4]` | SP_TREE_PORT2 |
    | `[7:6]` | SP_TREE_PORT3 |
    | `[9:8]` | SP_TREE_PORT4 |
    | `[11:10]` | SP_TREE_PORT5 |
    | `[13:12]` | SP_TREE_PORT6 |
    | `[15:14]` | SP_TREE_PORT7 |
    | `[17:16]` | SP_TREE_PORT8 |
    | `[19:18]` | SP_TREE_PORT9 |
    | `[21:20]` | SP_TREE_PORT10 |
    | `[23:22]` | SP_TREE_PORT11 |
    | `[25:24]` | SP_TREE_PORT12 |
    | `[27:26]` | SP_TREE_PORT13 |
    | `[29:28]` | SP_TREE_PORT14 |
    | `[31:30]` | SP_TREE_PORT15 |
    | `[33:32]` | SP_TREE_PORT16 |
    | `[35:34]` | SP_TREE_PORT17 |
    | `[37:36]` | SP_TREE_PORT18 |
    | `[39:38]` | SP_TREE_PORT19 |
    | `[41:40]` | SP_TREE_PORT20 |
    | `[43:42]` | SP_TREE_PORT21 |
    | `[45:44]` | SP_TREE_PORT22 |
    | `[47:46]` | SP_TREE_PORT23 |
    | `[49:48]` | SP_TREE_PORT24 |
    | `[51:50]` | SP_TREE_PORT25 |
    | `[53:52]` | SP_TREE_PORT26 |
    | `[55:54]` | SP_TREE_PORT27 |
    | `[57:56]` | SP_TREE_PORT28 |
    | `[59:58]` | SP_TREE_PORT29 |
    | `[61:60]` | SP_TREE_PORT30 |
    | `[63:62]` | SP_TREE_PORT31 |
    | `[65:64]` | SP_TREE_PORT32 |
    | `[67:66]` | SP_TREE_PORT33 |
    | `[69:68]` | SP_TREE_PORT34 |
    | `[71:70]` | SP_TREE_PORT35 |
    | `[73:72]` | SP_TREE_PORT36 |
    | `[75:74]` | SP_TREE_PORT37 |
    | `[77:76]` | SP_TREE_PORT38 |
    | `[79:78]` | SP_TREE_PORT39 |
    | `[81:80]` | SP_TREE_PORT40 |
    | `[83:82]` | SP_TREE_PORT41 |
    | `[85:84]` | SP_TREE_PORT42 |
    | `[87:86]` | SP_TREE_PORT43 |
    | `[89:88]` | SP_TREE_PORT44 |
    | `[91:90]` | SP_TREE_PORT45 |
    | `[93:92]` | SP_TREE_PORT46 |
    | `[95:94]` | SP_TREE_PORT47 |
    | `[97:96]` | SP_TREE_PORT48 |
    | `[99:98]` | SP_TREE_PORT49 |
    | `[101:100]` | SP_TREE_PORT50 |
    | `[103:102]` | SP_TREE_PORT51 |
    | `[105:104]` | SP_TREE_PORT52 |
    | `[107:106]` | SP_TREE_PORT53 |
    | `[109:108]` | SP_TREE_PORT54 |
    | `[111:110]` | SP_TREE_PORT55 |
    | `[113:112]` | SP_TREE_PORT56 |
    | `[115:114]` | SP_TREE_PORT57 |
    | `[117:116]` | SP_TREE_PORT58 |
    | `[119:118]` | SP_TREE_PORT59 |
    | `[121:120]` | SP_TREE_PORT60 |
    | `[123:122]` | SP_TREE_PORT61 |
    | `[125:124]` | SP_TREE_PORT62 |
    | `[127:126]` | SP_TREE_PORT63 |
    | `[129:128]` | SP_TREE_PORT64 |
    | `[131:130]` | SP_TREE_PORT65 |
    | `[139:132]` | RESERVED_0 |
    | `[140]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[1]: <SP_TREE_PORT2=3,SP_TREE_PORT1=3,>

---

## EGR_PRI_CNG_MAPm

- **Base address:** `0x02264000`  ·  **Entries:** 4224  ·  **Entry width:** 1 bytes
- **Function:** Per port egress priority/CFI mapping table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CFI |
    | `[3:1]` | PRI |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 1188 entries populated. Sample:

    epipe0[1]: <CFI=1>

---

## EGR_IP_TUNNELm

- **Base address:** `0x02266000`  ·  **Entries:** 512  ·  **Entry width:** 29 bytes
- **Function:** Egress IP Tunnel Table. Used to Make new Tunnel Header.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | ENTRY_TYPE |
    | `[5:2]` | TUNNEL_TYPE |
    | `[103:102]` | TUNNEL_TPID_INDEX |
    | `[104]` | VLAN_ASSIGN_POLICY |
    | `[105]` | DOT1P_PRI_SELECT |
    | `[109:106]` | DOT1P_MAPPING_PTR |
    | `[106]` | NEW_CFI |
    | `[109:107]` | NEW_PRI |
    | `[117:110]` | TTL |
    | `[119:118]` | IPV4_DF_SEL |
    | `[120]` | IPV6_DF_SEL |
    | `[127:121]` | DSCP_MAPPING_PTR |
    | `[126:121]` | DSCP |
    | `[127]` | DSCP_UNUSED |
    | `[129:128]` | DSCP_SEL |
    | `[209:194]` | L4_SRC_PORT |
    | `[227:226]` | RESERVED_0 |
    | `[229:228]` | IPV4_UNUSED_0 |
    | `[230]` | EVEN_PARITY |

---

## EGR_IP_TUNNEL_IPV6m

- **Base address:** `0x02267000`  ·  **Entries:** 256  ·  **Entry width:** 58 bytes
- **Function:** IPV6 view of the Egress IP Tunnel Table. Used to make new IPV6 Tunnel Header. FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | ENTRY_TYPE |
    | `[5:2]` | TUNNEL_TYPE |
    | `[230]` | EVEN_PARITY_LOWER |
    | `[232:231]` | ENTRY_TYPE_COPY |
    | `[234:233]` | TUNNEL_TPID_INDEX |
    | `[235]` | VLAN_ASSIGN_POLICY |
    | `[236]` | DOT1P_PRI_SELECT |
    | `[240:237]` | DOT1P_MAPPING_PTR |
    | `[237]` | NEW_CFI |
    | `[240:238]` | NEW_PRI |
    | `[267:261]` | DSCP_MAPPING_PTR |
    | `[266:261]` | DSCP |
    | `[267]` | DSCP_UNUSED |
    | `[269:268]` | DSCP_SEL |
    | `[277:270]` | TTL |
    | `[437:422]` | L4_DEST_PORT |
    | `[439:438]` | RESERVED_0 |
    | `[461]` | EVEN_PARITY_UPPER |

---

## EGR_IP_TUNNEL_MPLSm

- **Base address:** `0x02268000`  ·  **Entries:** 512  ·  **Entry width:** 29 bytes
- **Function:** MPLS view of the Egress IP Tunnel Table. Used to make new MPLS Tunnel Header. Note there are 4 entries per location. FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | ENTRY_TYPE |
    | `[3:2]` | MPLS_UNUSED_0 |
    | `[23:4]` | MPLS_LABEL_0 |
    | `[25:24]` | MPLS_PUSH_ACTION_0 |
    | `[27:26]` | MPLS_EXP_SELECT_0 |
    | `[31:28]` | MPLS_EXP_MAPPING_PTR_0 |
    | `[28]` | NEW_CFI_0 |
    | `[31:29]` | NEW_PRI_0 |
    | `[34:32]` | MPLS_EXP_0 |
    | `[43:36]` | MPLS_TTL_0 |
    | `[63:44]` | MPLS_LABEL_1 |
    | `[65:64]` | MPLS_PUSH_ACTION_1 |
    | `[67:66]` | MPLS_EXP_SELECT_1 |
    | `[71:68]` | MPLS_EXP_MAPPING_PTR_1 |
    | `[68]` | NEW_CFI_1 |
    | `[71:69]` | NEW_PRI_1 |
    | `[74:72]` | MPLS_EXP_1 |
    | `[83:76]` | MPLS_TTL_1 |
    | `[95:84]` | MPLS_UNUSED_1 |
    | `[115:96]` | MPLS_LABEL_2 |
    | `[117:116]` | MPLS_PUSH_ACTION_2 |
    | `[119:118]` | MPLS_EXP_SELECT_2 |
    | `[123:120]` | MPLS_EXP_MAPPING_PTR_2 |
    | `[120]` | NEW_CFI_2 |
    | `[123:121]` | NEW_PRI_2 |
    | `[126:124]` | MPLS_EXP_2 |
    | `[135:128]` | MPLS_TTL_2 |
    | `[155:136]` | MPLS_LABEL_3 |
    | `[157:156]` | MPLS_PUSH_ACTION_3 |
    | `[159:158]` | MPLS_EXP_SELECT_3 |
    | `[163:160]` | MPLS_EXP_MAPPING_PTR_3 |
    | `[160]` | NEW_CFI_3 |
    | `[163:161]` | NEW_PRI_3 |
    | `[166:164]` | MPLS_EXP_3 |
    | `[175:168]` | MPLS_TTL_3 |
    | `[230]` | EVEN_PARITY |

---

## EGR_MPLS_EXP_MAPPING_1m

- **Base address:** `0x02269000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Mapping table for Internal Priority and CNG to MPLS labels EXP. Address = {VC_AND_SWAP_LABEL.MPLS_EXP_MAPPING_PTR, int_PRI, CNG}. FeatureSpecific-MPLS

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | MPLS_EXP |
    | `[2:0]` | PRI |
    | `[3]` | CFI |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 63 entries populated. Sample:

    epipe0[1]: <CFI=1>

---

## EGR_MPLS_EXP_MAPPING_2m

- **Base address:** `0x0226a000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Mapping table for Internal Priority and CNG to MPLS labels EXP. Address = {EGR_IP_TUNNEL_MPLS.MPLS_EXP_MAPPING_PTR, int_PRI, CNG} FeatureSpecific-MPLS

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | MPLS_EXP |
    | `[2:0]` | PRI |
    | `[3]` | CFI |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 63 entries populated. Sample:

    epipe0[1]: <CFI=1>

---

## EGR_MPLS_PRI_MAPPINGm

- **Base address:** `0x0226b000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Mapping table for Internal Priority and CNG to MPLS labels EXP. Address = {MPLS_EXP_MAPPING_PTR, int_PRI, CNG} FeatureSpecific-MPLS

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | NEW_PRI |
    | `[3]` | NEW_CFI |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 63 entries populated. Sample:

    epipe0[1]: <NEW_CFI=1,>

---

## EGR_IM_MTP_INDEXm

- **Base address:** `0x0226c000`  ·  **Entries:** 32  ·  **Entry width:** 4 bytes
- **Function:** Mirror to Port Table to be used for IM tagged packets.\nIndex is constructed using pbe.mtp_index[6:0] field.\nWe use {pbe.mtp_index[4:3],pbe.mtp_index[2:0]} as index into this table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MTP_DST_MODID |
    | `[14:8]` | MTP_DST_PORT |
    | `[15]` | INSERT_CLASS_TAG |
    | `[16]` | CHANGE_INT_PRI |
    | `[20:17]` | NEW_INT_PRI |
    | `[21]` | MIRROR_ENCAP_ENABLE |
    | `[24:22]` | MIRROR_ENCAP_INDEX |

---

## EGR_EM_MTP_INDEXm

- **Base address:** `0x0226d000`  ·  **Entries:** 32  ·  **Entry width:** 4 bytes
- **Function:** Mirror to Port Table.\nIndex is constructed using pbe.mtp_index[6:0] field.\nWe use {pbe.mtp_index[5:4],pbe.mtp_index[2:0]} as index into this table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MTP_DST_MODID |
    | `[14:8]` | MTP_DST_PORT |
    | `[15]` | INSERT_CLASS_TAG |
    | `[16]` | CHANGE_INT_PRI |
    | `[20:17]` | NEW_INT_PRI |
    | `[21]` | MIRROR_ENCAP_ENABLE |
    | `[24:22]` | MIRROR_ENCAP_INDEX |

---

## EGR_DSCP_ECN_MAPm

- **Base address:** `0x0226e000`  ·  **Entries:** 64  ·  **Entry width:** 1 bytes
- **Function:** Egress DSCP Table to select the new dscp for outer tunnel header packets.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECN_MODE |

---

## EGR_VLAN_TAG_ACTION_PROFILEm

- **Base address:** `0x0226f000`  ·  **Entries:** 64  ·  **Entry width:** 8 bytes
- **Function:** Egress VLAN Tag Action Profile Table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | UT_ITAG_ACTION |
    | `[3:2]` | UT_OTAG_ACTION |
    | `[5:4]` | SIT_PITAG_ACTION |
    | `[7:6]` | SIT_ITAG_ACTION |
    | `[10:8]` | SIT_OTAG_ACTION |
    | `[13:11]` | SOT_ITAG_ACTION |
    | `[15:14]` | SOT_POTAG_ACTION |
    | `[17:16]` | SOT_OTAG_ACTION |
    | `[20:18]` | DT_PITAG_ACTION |
    | `[23:21]` | DT_ITAG_ACTION |
    | `[26:24]` | DT_POTAG_ACTION |
    | `[29:27]` | DT_OTAG_ACTION |
    | `[31:30]` | RESERVED_0 |
    | `[33:32]` | UT_OPRI_ACTION |
    | `[35:34]` | UT_OCFI_ACTION |
    | `[37:36]` | UT_IPRI_ACTION |
    | `[39:38]` | UT_ICFI_ACTION |
    | `[41:40]` | SIT_OPRI_ACTION |
    | `[43:42]` | SIT_OCFI_ACTION |
    | `[45:44]` | SIT_IPRI_ACTION |
    | `[47:46]` | SIT_ICFI_ACTION |
    | `[49:48]` | SOT_OPRI_ACTION |
    | `[51:50]` | SOT_OCFI_ACTION |
    | `[53:52]` | SOT_IPRI_ACTION |
    | `[55:54]` | SOT_ICFI_ACTION |
    | `[57:56]` | DT_OPRI_ACTION |
    | `[59:58]` | DT_OCFI_ACTION |
    | `[61:60]` | DT_IPRI_ACTION |
    | `[63:62]` | DT_ICFI_ACTION |

---

## EGR_MIRROR_ENCAP_CONTROLm

- **Base address:** `0x02270000`  ·  **Entries:** 8  ·  **Entry width:** 1 bytes
- **Function:** Contains the Mirror Encap controls for each of the 8 Mirror Encap Indices.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENTRY_TYPE |
    | `[2:1]` | RSPAN_ADD_OPTIONAL_HEADER |
    | `[3]` | RSPAN_ADD_TRILL_OUTER_VLAN |
    | `[2:1]` | ERSPAN_ADD_OPTIONAL_HEADER |
    | `[3]` | ERSPAN_ADD_TRILL_OUTER_VLAN |
    | `[4]` | ERSPAN_ADD_ERSPAN_OUTER_VLAN |
    | `[5]` | ERSPAN_UNTAG_PAYLOAD |

---

## EGR_DSCP_TABLEm

- **Base address:** `0x02272000`  ·  **Entries:** 8192  ·  **Entry width:** 1 bytes
- **Function:** Egress DSCP Table to select the new dscp for outer tunnel header packets.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | DSCP |
    | `[6]` | EVEN_PARITY |

---

## EGR_GPP_ATTRIBUTES_MODBASEm

- **Base address:** `0x02274000`  ·  **Entries:** 256  ·  **Entry width:** 2 bytes
- **Function:** Per-GPP attributes MODBASE table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | BASE |
    | `[12]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <BASE=0x80>

---

## EGR_GPP_ATTRIBUTESm

- **Base address:** `0x02275000`  ·  **Entries:** 4096  ·  **Entry width:** 4 bytes
- **Function:** Per-GPP attributes table, PORT view.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | SRC_NIV_VIF_ID |
    | `[12]` | SRC_IS_NIV_UPLINK_PORT |
    | `[22:13]` | TGID |
    | `[23]` | ISTRUNK |
    | `[24]` | EVEN_PARITY |

---

## EGR_FRAGMENT_ID_TABLEm

- **Base address:** `0x022d1000`  ·  **Entries:** 512  ·  **Entry width:** 3 bytes
- **Function:** IPv4 / CAPWAP Tunnel Fragment ID Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | FRAGMENT_ID |
    | `[16]` | EVEN_PARITY |

---

## EGR_MPLS_EXP_PRI_MAPPINGm

- **Base address:** `0x04260000`  ·  **Entries:** 128  ·  **Entry width:** 1 bytes
- **Function:** Mapping table for EXP to .1p/cfi. Address = {MPLS_EXP_MAPPING_PTR, new_exp} FeatureSpecific-MPLS

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | NEW_PRI |
    | `[3]` | NEW_CFI |

---

## EGR_TRILL_RBRIDGE_NICKNAMESm

- **Base address:** `0x04262000`  ·  **Entries:** 4  ·  **Entry width:** 2 bytes
- **Function:** Table that defines the TRILL RBridge nickname to use when sending out a packet. The index is derived from the ingress VLAN table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | RBRIDGE_NICKNAME |

---

## EGR_MOD_MAP_TABLEm

- **Base address:** `0x05260000`  ·  **Entries:** 512  ·  **Entry width:** 2 bytes
- **Function:** Egress Module Remapping Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA_FIELDS |
    | `[6:0]` | PORT_OFFSET |
    | `[13:7]` | MODID |
    | `[14]` | EVEN_PARITY |

---

## EGR_MIRROR_ENCAP_DATA_1m

- **Base address:** `0x06260000`  ·  **Entries:** 8  ·  **Entry width:** 43 bytes
- **Function:** Contains the Base Header portion of Mirror Encap Data for each of the 8 Mirror Encap Indices.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[207:192]` | ERSPAN_HEADER_ETYPE |
    | `[336]` | EVEN_PARITY |

---

## EGR_MIRROR_ENCAP_DATA_2m

- **Base address:** `0x06262000`  ·  **Entries:** 8  ·  **Entry width:** 25 bytes
- **Function:** Contains the Optional Header portion of Mirror Encap Data for each of the 8 Mirror Encap Indices.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[192]` | EVEN_PARITY |

---

## EGR_TRILL_PARSE_CONTROL_2m

- **Base address:** `0x06266000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Trill parse control (second copy).

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[48]` | TRILL_ALL_IS_IS_RBRIDGES_MAC_ADDRESS_ENABLE |
    | `[49]` | TRILL_L2_IS_IS_ETHERTYPE_ENABLE |

---

## EFP_METER_TABLE_Xm

- **Base address:** `0x08224000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** METER TABLE STRUCTURES FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[60:42]` | REFRESHCOUNT |
    | `[61]` | REFRESH_MODE |
    | `[65]` | PKTS_BYTES |
    | `[66]` | EFP_METER_SPARE |
    | `[67]` | EVEN_PARITY |

**Live capture (Cumulus):** 18 entries populated. Sample:

    epipe0[512]: <REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf43,BUCKETCOUNT=0xf430000>

---

## EGR_PW_INIT_COUNTERS_Xm

- **Base address:** `0x08226000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** L2 MPLS Pseudo-wire Initiation SEQNUM Table -- indexed by PW number.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## EFP_METER_TABLE_Ym

- **Base address:** `0x08244000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** METER TABLE STRUCTURES FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[60:42]` | REFRESHCOUNT |
    | `[61]` | REFRESH_MODE |
    | `[65]` | PKTS_BYTES |
    | `[66]` | EFP_METER_SPARE |
    | `[67]` | EVEN_PARITY |

**Live capture (Cumulus):** 18 entries populated. Sample:

    epipe0[512]: <REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf43,BUCKETCOUNT=0xf430000>

---

## EGR_PW_INIT_COUNTERS_Ym

- **Base address:** `0x08246000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** L2 MPLS Pseudo-wire Initiation SEQNUM Table -- indexed by PW number.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## EFP_TCAMm

- **Base address:** `0x08260000`  ·  **Entries:** 1024  ·  **Entry width:** 54 bytes
- **Function:** TCAM FOR EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | VALID |

**Live capture (Cumulus):** 36 entries populated. Sample:

    epipe0[512]: <VALID=3,MASK=0x383f800000000000000000000000000000003fc000000000000000,KEY_MASK=0x383f800000000000000000000000000000003fc000000000000000,KEY=0x200000000000000000000000000000000000164000000000000000>

---

## EFP_POLICY_TABLEm

- **Base address:** `0x08262000`  ·  **Entries:** 1024  ·  **Entry width:** 16 bytes
- **Function:** POLICY TABLE FOR DETERMINING ACTIONS IN THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | G_NEW_OUTER_CFI |
    | `[1]` | G_CHANGE_OUTER_CFI |
    | `[2]` | Y_NEW_OUTER_CFI |
    | `[3]` | Y_CHANGE_OUTER_CFI |
    | `[4]` | R_NEW_OUTER_CFI |
    | `[5]` | R_CHANGE_OUTER_CFI |
    | `[6]` | G_NEW_INNER_CFI |
    | `[7]` | G_CHANGE_INNER_CFI |
    | `[8]` | Y_NEW_INNER_CFI |
    | `[9]` | Y_CHANGE_INNER_CFI |
    | `[10]` | R_NEW_INNER_CFI |
    | `[11]` | R_CHANGE_INNER_CFI |
    | `[14:12]` | G_NEW_DOT1P |
    | `[15]` | G_CHANGE_DOT1P |
    | `[18:16]` | Y_NEW_DOT1P |
    | `[19]` | Y_CHANGE_DOT1P |
    | `[22:20]` | R_NEW_DOT1P |
    | `[23]` | R_CHANGE_DOT1P |
    | `[26:24]` | G_NEW_INNER_PRI |
    | `[27]` | G_REPLACE_INNER_PRI |
    | `[30:28]` | Y_NEW_INNER_PRI |
    | `[31]` | Y_REPLACE_INNER_PRI |
    | `[34:32]` | R_NEW_INNER_PRI |
    | `[35]` | R_REPLACE_INNER_PRI |
    | `[41:36]` | G_NEW_DSCP |
    | `[42]` | G_CHANGE_DSCP |
    | `[48:43]` | Y_NEW_DSCP |
    | `[49]` | Y_CHANGE_DSCP |
    | `[55:50]` | R_NEW_DSCP |
    | `[56]` | R_CHANGE_DSCP |
    | `[58:57]` | G_DROP |
    | `[60:59]` | Y_DROP |
    | `[62:61]` | R_DROP |
    | `[65]` | PID_REPLACE_OUTER_TPID |
    | `[77:66]` | PID_NEW_OUTER_VID |
    | `[78]` | PID_REPLACE_OUTER_VID |
    | `[90:79]` | PID_NEW_INNER_VID |
    | `[91]` | PID_REPLACE_INNER_VID |
    | `[93:92]` | RESERVED_1 |
    | `[105:97]` | PID_COUNTER_INDEX |
    | `[108:106]` | METER_PAIR_MODE |
    | `[109]` | METER_TEST_EVEN |
    | `[110]` | METER_TEST_ODD |
    | `[111]` | METER_UPDATE_EVEN |
    | `[112]` | METER_UPDATE_ODD |
    | `[119:113]` | METER_INDEX_EVEN |
    | `[126:120]` | METER_INDEX_ODD |
    | `[127]` | EVEN_PARITY |

**Live capture (Cumulus):** 36 entries populated. Sample:

    epipe0[512]: <R_DROP=1,PID_COUNTER_MODE=4,METER_UPDATE_EVEN=1,METER_TEST_EVEN=1,METER_PAIR_MODE=1,>

---

## EFP_METER_TABLEm

- **Base address:** `0x082c4000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** METER TABLE STRUCTURES FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[60:42]` | REFRESHCOUNT |
    | `[61]` | REFRESH_MODE |
    | `[65]` | PKTS_BYTES |
    | `[66]` | EFP_METER_SPARE |
    | `[67]` | EVEN_PARITY |

**Live capture (Cumulus):** 18 entries populated. Sample:

    epipe0[512]: <REFRESHCOUNT=0x7d0,PKTS_BYTES=1,EVEN_PARITY=1,BUCKETSIZE=0xf43,BUCKETCOUNT=0xf430000>

---

## EGR_PW_INIT_COUNTERSm

- **Base address:** `0x082c6000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** L2 MPLS Pseudo-wire Initiation Pkt/byte counters with SEQNUM overlay-- indexed by PW number

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## EFP_COUNTER_TABLE_Xm

- **Base address:** `0x0a220000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    epipe0[1]: <PACKET_COUNTER=0x8e8,EVEN_PARITY=1,BYTE_COUNTER=0x00000352a8>

---

## EGR_PERQ_XMT_COUNTERS_Xm

- **Base address:** `0x0a224000`  ·  **Entries:** 784  ·  **Entry width:** 8 bytes
- **Function:** Per-port Per-queue transmit counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | PACKET_COUNTER |
    | `[59]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x8ce,EVEN_PARITY=1,BYTE_COUNTER=0x0000033668>

---

## EGR_VINTF_COUNTER_TABLE_Xm

- **Base address:** `0x0a226000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x1d3f,EVEN_PARITY=1,BYTE_COUNTER=0x00000c16e4>

---

## EGR_SERVICE_COUNTER_TABLE_Xm

- **Base address:** `0x0a228000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x1d3f,EVEN_PARITY=1,BYTE_COUNTER=0x00000c16e4>

---

## EGR_PORT_REQUESTS_Xm

- **Base address:** `0x0a22c000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This table contains the cell requests asserted by individual port blocks (XLPORT's and CMIC).\nMeaning of cell request is different for different ports, but this register has no\nunderstanding of those meanings. All it shows is the number of times cell_request signal\nwas asserted by each port to TP.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_PORT_REQUESTS |

**Live capture (Cumulus):** 66 entries populated. Sample:

    epipe0[0]: <OUTSTANDING_PORT_REQUESTS=1>

---

## EGR_MMU_REQUESTS_Xm

- **Base address:** `0x0a22e000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1664 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_MMU_REQUESTS |

**Live capture (Cumulus):** 66 entries populated. Sample:

    epipe0[0]: <OUTSTANDING_MMU_REQUESTS=4>

---

## EGR_MAX_USED_ENTRIES_Xm

- **Base address:** `0x0a230000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1664 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | LEVEL |

**Live capture (Cumulus):** 31 entries populated. Sample:

    epipe0[0]: <LEVEL=0x1a>

---

## EFP_COUNTER_TABLE_Ym

- **Base address:** `0x0a240000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## EGR_PERQ_XMT_COUNTERS_Ym

- **Base address:** `0x0a244000`  ·  **Entries:** 784  ·  **Entry width:** 8 bytes
- **Function:** Per-port Per-queue transmit counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | PACKET_COUNTER |
    | `[59]` | EVEN_PARITY |

**Live capture (Cumulus):** 2 entries populated. Sample:

    epipe0[3]: <PACKET_COUNTER=0x657,BYTE_COUNTER=0x00000268b0>

---

## EGR_VINTF_COUNTER_TABLE_Ym

- **Base address:** `0x0a246000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## EGR_SERVICE_COUNTER_TABLE_Ym

- **Base address:** `0x0a248000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## EGR_PORT_REQUESTS_Ym

- **Base address:** `0x0a24c000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This table contains the cell requests asserted by individual port blocks (XLPORT's and CMIC).\nMeaning of cell request is different for different ports, but this register has no\nunderstanding of those meanings. All it shows is the number of times cell_request signal\nwas asserted by each port to TP.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_PORT_REQUESTS |

**Live capture (Cumulus):** 57 entries populated. Sample:

    epipe0[1]: <OUTSTANDING_PORT_REQUESTS=4>

---

## EGR_MMU_REQUESTS_Ym

- **Base address:** `0x0a24e000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1664 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_MMU_REQUESTS |

**Live capture (Cumulus):** 57 entries populated. Sample:

    epipe0[1]: <OUTSTANDING_MMU_REQUESTS=6>

---

## EGR_MAX_USED_ENTRIES_Ym

- **Base address:** `0x0a250000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1664 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | LEVEL |

**Live capture (Cumulus):** 4 entries populated. Sample:

    epipe0[1]: <LEVEL=5>

---

## EGR_PERQ_XMT_COUNTERS_BASE_ADDRm

- **Base address:** `0x0a262000`  ·  **Entries:** 264  ·  **Entry width:** 2 bytes
- **Function:** Per-port Per-queue transmit counters Base Address.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | BASE |
    | `[10]` | EVEN_PARITY |

**Live capture (Cumulus):** 112 entries populated. Sample:

    epipe0[5]: <BASE=0xa>

---

## EGR_ENABLEm

- **Base address:** `0x0a26a000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** Enables the Egress Port for transmission.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PRT_ENABLE |

**Live capture (Cumulus):** 54 entries populated. Sample:

    epipe0[0]: <PRT_ENABLE=1>

---

## EGR_PFC_CONTROLm

- **Base address:** `0x0a272000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** control the PFC (Priority Flow Control) feature of the egress. It should be only used for the XLPORT.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[6:1]` | WATERMARK |

---

## EFP_COUNTER_TABLEm

- **Base address:** `0x0a2c0000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE EFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    epipe0[1]: <PACKET_COUNTER=0x8e8,EVEN_PARITY=1,BYTE_COUNTER=0x00000352a8>

---

## EGR_PERQ_XMT_COUNTERSm

- **Base address:** `0x0a2c4000`  ·  **Entries:** 784  ·  **Entry width:** 8 bytes
- **Function:** Per-port Per-queue transmit counters

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | PACKET_COUNTER |
    | `[59]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x8ce,EVEN_PARITY=1,BYTE_COUNTER=0x0000033668>

---

## EGR_VINTF_COUNTER_TABLEm

- **Base address:** `0x0a2c6000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x1d3f,EVEN_PARITY=1,BYTE_COUNTER=0x00000c16e4>

---

## EGR_SERVICE_COUNTER_TABLEm

- **Base address:** `0x0a2c8000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Egress Virtual Port / Interface Counters

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <PACKET_COUNTER=0x1d3f,EVEN_PARITY=1,BYTE_COUNTER=0x00000c16e4>

---

## EGR_PORT_REQUESTSm

- **Base address:** `0x0a2cc000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by individual ports from GPORT, XPORT, CMIC\nblocks. Meaning of cell request is different for different ports, but this register has no\nunderstanding of those meanings. All it shows is the number of times cell_request signal\nwas asserted by each port to TP.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_PORT_REQUESTS |

**Live capture (Cumulus):** 66 entries populated. Sample:

    epipe0[0]: <OUTSTANDING_PORT_REQUESTS=1>

---

## EGR_MMU_REQUESTSm

- **Base address:** `0x0a2ce000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1024 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | OUTSTANDING_MMU_REQUESTS |

**Live capture (Cumulus):** 66 entries populated. Sample:

    epipe0[0]: <OUTSTANDING_MMU_REQUESTS=4>

---

## EGR_MAX_USED_ENTRIESm

- **Base address:** `0x0a2d0000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes
- **Function:** This register contains the cell requests asserted by TP for individual ports to MMU.\nMeaning of cell request is 1664 bits data. All it shows is the number of times cell_request signal\nwas asserted by TP to MMU for each port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | LEVEL |

**Live capture (Cumulus):** 31 entries populated. Sample:

    epipe0[0]: <LEVEL=0x1a>

---

## ESBS_PORT_TO_PIPE_MAPPINGm

- **Base address:** `0x0b270000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** ESBS Port to Pipe Mapping table.

**Entry fields:**

    _(no field breakdown — treated as a single value)_

**Live capture (Cumulus):** 1 entries populated. Sample:

    epipe0[0]: <BITMAP=0x02001ffe00000001fe>

---

## EGR_L3_NEXT_HOPm

- **Base address:** `0x0c260000`  ·  **Entries:** 16384  ·  **Entry width:** 15 bytes
- **Function:** Next Hop Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | ENTRY_TYPE |
    | `[14:3]` | LEGACY_INTF_NUM |
    | `[14:3]` | LEGACY_OVID |
    | `[14:3]` | LEGACY_SD_TAG_VID |
    | `[27:15]` | LEGACY_DVP |
    | `[26:15]` | LEGACY_IVID |
    | `[28]` | LEGACY_DVP_IS_NETWORK_PORT |
    | `[30]` | LEGACY_HG_MODIFY_ENABLE |
    | `[31]` | LEGACY_HG_HDR_SEL |
    | `[39:32]` | LEGACY_HG_MC_DST_MODID |
    | `[46:40]` | LEGACY_HG_MC_DST_PORT_NUM |
    | `[47]` | LEGACY_HG_ADD_SYS_RSVD_VID |
    | `[48]` | LEGACY_HG_LEARN_OVERRIDE |
    | `[49]` | LEGACY_HG_L3_OVERRIDE |
    | `[62:50]` | LEGACY_PW_INIT_NUM |
    | `[62:50]` | LEGACY_VC_AND_SWAP_INDEX |
    | `[61:59]` | LEGACY_SD_TAG_ACTION_IF_PRESENT |
    | `[63:62]` | LEGACY_SD_TAG_ACTION_IF_NOT_PRESENT |
    | `[65:64]` | LEGACY_SD_TAG_TPID_INDEX |
    | `[99]` | LEGACY_USE_VINTF_CTR_IDX |
    | `[115:100]` | LEGACY_RESERVED_2 |
    | `[14:3]` | L3_INTF_NUM |
    | `[14:3]` | L3_OVID |
    | `[26:15]` | L3_IVID |
    | `[63]` | L3_L3_UC_SA_DISABLE |
    | `[64]` | L3_L3_UC_DA_DISABLE |
    | `[65]` | L3_L3_UC_TTL_DISABLE |
    | `[66]` | L3_L3_UC_VLAN_DISABLE |
    | `[68:67]` | L3_EH_TAG_TYPE |
    | `[69]` | L3_EH_TM |
    | `[85:70]` | L3_EH_QUEUE_TAG |
    | `[99]` | L3_USE_VINTF_CTR_IDX |
    | `[100]` | L3_HG_LEARN_OVERRIDE |
    | `[115:101]` | L3_RESERVED_0 |
    | `[14:3]` | MPLS_INTF_NUM |
    | `[27:15]` | MPLS_DVP |
    | `[28]` | MPLS_UMC_DROP |
    | `[29]` | MPLS_DVP_IS_NETWORK_PORT |
    | `[30]` | MPLS_HG_MODIFY_ENABLE |
    | `[31]` | MPLS_HG_HDR_SEL |
    | `[39:32]` | MPLS_HG_MC_DST_MODID |
    | `[46:40]` | MPLS_HG_MC_DST_PORT_NUM |
    | `[47]` | MPLS_HG_ADD_SYS_RSVD_VID |
    | `[48]` | MPLS_HG_LEARN_OVERRIDE |
    | `[49]` | MPLS_HG_L3_OVERRIDE |
    | `[62:50]` | MPLS_PW_INIT_NUM |
    | `[62:50]` | MPLS_VC_AND_SWAP_INDEX |
    | `[72]` | MPLS_UUC_DROP |
    | `[73]` | MPLS_BC_DROP |
    | `[86:74]` | MPLS_VINTF_CTR_IDX |
    | `[87]` | MPLS_DELETE_VNTAG |
    | `[89:88]` | MPLS_EH_TAG_TYPE |
    | `[90]` | MPLS_EH_TM |
    | `[107]` | MPLS_USE_VINTF_CTR_IDX |
    | `[115:108]` | MPLS_RESERVED_0 |
    | `[14:3]` | SD_TAG_SD_TAG_VID |
    | `[27:15]` | SD_TAG_DVP |
    | `[28]` | SD_TAG_HG_L3_OVERRIDE |
    | `[29]` | SD_TAG_DVP_IS_NETWORK_PORT |
    | `[30]` | SD_TAG_HG_MODIFY_ENABLE |
    | `[31]` | SD_TAG_HG_HDR_SEL |
    | `[39:32]` | SD_TAG_HG_MC_DST_MODID |
    | `[46:40]` | SD_TAG_HG_MC_DST_PORT_NUM |
    | `[47]` | SD_TAG_HG_ADD_SYS_RSVD_VID |
    | `[48]` | SD_TAG_HG_LEARN_OVERRIDE |
    | `[51:49]` | SD_TAG_SD_TAG_ACTION_IF_PRESENT |
    | `[53:52]` | SD_TAG_SD_TAG_ACTION_IF_NOT_PRESENT |
    | `[55:54]` | SD_TAG_SD_TAG_TPID_INDEX |
    | `[70]` | SD_TAG_VNTAG_FORCE_L |
    | `[71]` | SD_TAG_VNTAG_P |
    | `[73:72]` | SD_TAG_VNTAG_ACTIONS |
    | `[74]` | SD_TAG_BC_DROP |
    | `[75]` | SD_TAG_UUC_DROP |
    | `[76]` | SD_TAG_SD_TAG_DOT1P_PRI_SELECT |
    | `[80:77]` | SD_TAG_SD_TAG_DOT1P_MAPPING_PTR |
    | `[77]` | SD_TAG_NEW_CFI |
    | `[80:78]` | SD_TAG_NEW_PRI |
    | `[81]` | SD_TAG_UMC_DROP |
    | `[94:82]` | SD_TAG_VINTF_CTR_IDX |
    | `[95]` | SD_TAG_SD_TAG_REMARK_CFI |
    | `[97:96]` | SD_TAG_EH_TAG_TYPE |
    | `[98]` | SD_TAG_EH_TM |
    | `[114:99]` | SD_TAG_EH_QUEUE_TAG |
    | `[115]` | SD_TAG_USE_VINTF_CTR_IDX |
    | `[14:3]` | MIM_INTF_NUM |
    | `[27:15]` | MIM_DVP |
    | `[28]` | MIM_ADD_ISID_TO_MACDA |
    | `[29]` | MIM_DVP_IS_NETWORK_PORT |
    | `[30]` | MIM_HG_MODIFY_ENABLE |
    | `[31]` | MIM_HG_HDR_SEL |
    | `[39:32]` | MIM_HG_MC_DST_MODID |
    | `[46:40]` | MIM_HG_MC_DST_PORT_NUM |
    | `[47]` | MIM_HG_ADD_SYS_RSVD_VID |
    | `[48]` | MIM_HG_LEARN_OVERRIDE |
    | `[49]` | MIM_HG_L3_OVERRIDE |
    | `[61:50]` | MIM_BVID |
    | `[62]` | MIM_BVID_VALID |
    | `[72]` | MIM_UMC_DROP |
    | `[73]` | MIM_UUC_DROP |
    | `[74]` | MIM_BC_DROP |
    | `[75]` | MIM_ISID_LOOKUP_TYPE |
    | `[76]` | MIM_DOT1P_PRI_SELECT |
    | `[80:77]` | MIM_DOT1P_MAPPING_PTR |
    | `[77]` | MIM_NEW_CFI |
    | `[80:78]` | MIM_NEW_PRI |
    | `[93:81]` | MIM_VINTF_CTR_IDX |
    | `[94]` | MIM_DELETE_VNTAG |
    | `[97]` | MIM_EH_TM |
    | `[113:98]` | MIM_EH_QUEUE_TAG |
    | `[114]` | MIM_USE_VINTF_CTR_IDX |
    | `[115]` | MIM_RESERVED_0 |
    | `[14:3]` | PROXY_INTF_NUM |
    | `[27:15]` | PROXY_VINTF_CTR_IDX |
    | `[28]` | PROXY_HG_LEARN_OVERRIDE |
    | `[29]` | PROXY_HG_L3_OVERRIDE |
    | `[30]` | PROXY_HG_MODIFY_ENABLE |
    | `[31]` | PROXY_HG_HDR_SEL |
    | `[39:32]` | PROXY_HG_MC_DST_MODID |
    | `[46:40]` | PROXY_HG_MC_DST_PORT_NUM |
    | `[47]` | PROXY_HG_ADD_SYS_RSVD_VID |
    | `[56:48]` | PROXY_MAC_DA_PROFILE_INDEX |
    | `[58:57]` | PROXY_EH_TAG_TYPE |
    | `[59]` | PROXY_EH_TM |
    | `[76]` | PROXY_USE_VINTF_CTR_IDX |
    | `[14:3]` | IFP_ACTIONS_INTF_NUM |
    | `[63]` | IFP_ACTIONS_L3_UC_SA_DISABLE |
    | `[64]` | IFP_ACTIONS_L3_UC_DA_DISABLE |
    | `[65]` | IFP_ACTIONS_L3_UC_TTL_DISABLE |
    | `[66]` | IFP_ACTIONS_L3_UC_VLAN_DISABLE |
    | `[100:99]` | IFP_ACTIONS_VNTAG_ACTION |
    | `[101]` | IFP_ACTIONS_HG_LEARN_OVERRIDE |
    | `[115:102]` | IFP_ACTIONS_RESERVED_0 |
    | `[116]` | EVEN_PARITY |

**Live capture (Cumulus):** 5 entries populated. Sample:

    epipe0[0]: <SD_TAG_VID=0xfff,OVID=0xfff,L3:OVID=0xfff,L3:INTF_NUM=0xfff,INTF_NUM=0xfff,>

---

## EGR_DVP_ATTRIBUTEm

- **Base address:** `0x0c264000`  ·  **Entries:** 8192  ·  **Entry width:** 8 bytes
- **Function:** Egress DVP Attribute Table, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | MTU_VALUE |
    | `[14]` | MTU_ENABLE |
    | `[22:15]` | CNTAG_DELETE_PRI_BITMAP |
    | `[23]` | DELETE_VNTAG |
    | `[29:24]` | HOPCOUNT |
    | `[47:46]` | VP_TYPE |
    | `[53:48]` | VLAN_MEMBERSHIP_PROFILE |
    | `[54]` | DISABLE_VP_PRUNING |
    | `[55]` | EN_EFILTER |
    | `[56]` | EVEN_PARITY |

---

## EGR_VFIm

- **Base address:** `0x0c268000`  ·  **Entries:** 1024  ·  **Entry width:** 2 bytes
- **Function:** Egress WLAN Destination Virtual Port Table, FeatureSpecific-Wireless

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | SERVICE_CTR_IDX |
    | `[13]` | USE_SERVICE_CTR_IDX |
    | `[14]` | EVEN_PARITY |

---

## EGR_PORTm

- **Base address:** `0x0c26a000`  ·  **Entries:** 67  ·  **Entry width:** 14 bytes
- **Function:** Configuration Register for a Port. This is different for each GE, 10GE port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PORT_TYPE |
    | `[2]` | HIGIG2 |
    | `[3]` | EN_EFILTER |
    | `[4]` | PRESERVE_CPU_TAG |
    | `[7:5]` | RESERVED_0 |
    | `[8]` | EM_SRCMOD_CHANGE |
    | `[16:9]` | MY_MODID |
    | `[24:17]` | EGR_PORT_GROUP_ID |
    | `[31:25]` | VT_PORT_GROUP_ID |
    | `[32]` | DUAL_MODID_ENABLE |
    | `[33]` | EFP_FILTER_ENABLE |
    | `[46:34]` | VINTF_CTR_IDX |
    | `[54:47]` | CNTAG_DELETE_PRI_BITMAP |
    | `[58:55]` | RESERVED_1 |
    | `[59]` | EH_EXT_HDR_ENABLE |
    | `[60]` | EH_EXT_HDR_LEARN_OVERRIDE |
    | `[62:61]` | VNTAG_ACTIONS_IF_PRESENT |
    | `[63]` | NIV_PRUNE_ENABLE |
    | `[75:64]` | NIV_VIF_ID |
    | `[76]` | NIV_UPLINK_PORT |
    | `[82:77]` | QCN_CNM_RESERVED |
    | `[99]` | TRILL_ENABLE |
    | `[100]` | ALLOW_TRILL_FRAMES |
    | `[101]` | ALLOW_NON_TRILL_FRAMES |
    | `[102]` | MIRROR_ENCAP_ENABLE |
    | `[105:103]` | MIRROR_ENCAP_INDEX |
    | `[106]` | EVEN_PARITY |

**Live capture (Cumulus):** 55 entries populated. Sample:

    epipe0[0]: <EN_EFILTER=1,EM_SRCMOD_CHANGE=1,EFP_FILTER_ENABLE=1,DUAL_MODID_ENABLE=1,>

---

## EGR_TRILL_PARSE_CONTROLm

- **Base address:** `0x0c26c000`  ·  **Entries:** 1  ·  **Entry width:** 17 bytes
- **Function:** Trill parse control.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TRILL_ETHERTYPE |
    | `[112]` | TRILL_ETHERTYPE_ENABLE |
    | `[113]` | TRILL_ALL_IS_IS_RBRIDGES_MAC_ADDRESS_ENABLE |
    | `[114]` | TRILL_L2_IS_IS_ETHERTYPE_ENABLE |

---

## EGR_VLAN_Xm

- **Base address:** `0x0d220000`  ·  **Entries:** 4096  ·  **Entry width:** 29 bytes
- **Function:** Vlan Membership Table for Egress.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[9:1]` | STG |
    | `[11:10]` | OUTER_TPID_INDEX |
    | `[24:12]` | SERVICE_CTR_IDX |
    | `[25]` | REMARK_DOT1P |
    | `[29:26]` | DOT1P_MAPPING_PTR |
    | `[30]` | REMARK_CFI |
    | `[95]` | RESERVED_0 |
    | `[161:160]` | UT_BITMAP_W2 |
    | `[161:160]` | UT_PORT_BITMAP_W2 |
    | `[227:226]` | PORT_BITMAP_W2 |
    | `[228]` | EVEN_PARITY |

**Live capture (Cumulus):** 53 entries populated. Sample:

    epipe0[1]: <VALID=1,STG=1,>

---

## EGR_VLAN_Ym

- **Base address:** `0x0d240000`  ·  **Entries:** 4096  ·  **Entry width:** 29 bytes
- **Function:** Vlan Membership Table for Egress.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[9:1]` | STG |
    | `[11:10]` | OUTER_TPID_INDEX |
    | `[24:12]` | SERVICE_CTR_IDX |
    | `[25]` | REMARK_DOT1P |
    | `[29:26]` | DOT1P_MAPPING_PTR |
    | `[30]` | REMARK_CFI |
    | `[95]` | RESERVED_0 |
    | `[161:160]` | UT_BITMAP_W2 |
    | `[161:160]` | UT_PORT_BITMAP_W2 |
    | `[227:226]` | PORT_BITMAP_W2 |
    | `[228]` | EVEN_PARITY |

**Live capture (Cumulus):** 53 entries populated. Sample:

    epipe0[1]: <VALID=1,STG=1,>

---

## EGR_VLANm

- **Base address:** `0x0d260000`  ·  **Entries:** 4096  ·  **Entry width:** 29 bytes
- **Function:** Vlan Membership Table for Egress

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[9:1]` | STG |
    | `[11:10]` | OUTER_TPID_INDEX |
    | `[24:12]` | SERVICE_CTR_IDX |
    | `[25]` | REMARK_DOT1P |
    | `[29:26]` | DOT1P_MAPPING_PTR |
    | `[30]` | REMARK_CFI |
    | `[95]` | RESERVED_0 |
    | `[161:160]` | UT_BITMAP_W2 |
    | `[161:160]` | UT_PORT_BITMAP_W2 |
    | `[227:226]` | PORT_BITMAP_W2 |
    | `[228]` | EVEN_PARITY |

**Live capture (Cumulus):** 53 entries populated. Sample:

    epipe0[1]: <VALID=1,STG=1,>

---

## EGR_VLAN_XLATEm

- **Base address:** `0x0d262000`  ·  **Entries:** 8192  ·  **Entry width:** 13 bytes
- **Function:** Egress Vlan Translate CAM-RAM Combined View.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | ENTRY_TYPE |
    | `[15:4]` | XLATE_OLD_VLAN_ID |
    | `[15:4]` | XLATE_OVID |
    | `[15:4]` | XLATE_VID |
    | `[28:16]` | XLATE_DVP |
    | `[23:16]` | XLATE_DST_MODID |
    | `[22:16]` | XLATE_PORT_GROUP_ID |
    | `[30:23]` | XLATE_DUMMY_BITS |
    | `[30:24]` | XLATE_DST_PORT |
    | `[58:43]` | XLATE_NEW_OTAG_VPTAG |
    | `[58:43]` | XLATE_NEW_VPTAG |
    | `[54:43]` | XLATE_NEW_OVID |
    | `[54:43]` | XLATE_NEW_VID |
    | `[54:43]` | XLATE_NEW_VLAN_ID |
    | `[58:55]` | XLATE_OPRI_MAPPING_PTR |
    | `[57:55]` | XLATE_NEW_OPRI |
    | `[57:55]` | XLATE_PRI |
    | `[58]` | XLATE_NEW_OCFI |
    | `[59]` | XLATE_NEW_OTAG_VPTAG_SEL |
    | `[60]` | XLATE_OPRI_CFI_SEL |
    | `[76:73]` | XLATE_IPRI_MAPPING_PTR |
    | `[75:73]` | XLATE_NEW_IPRI |
    | `[76]` | XLATE_NEW_ICFI |
    | `[77]` | XLATE_IPRI_CFI_SEL |
    | `[83:78]` | XLATE_TAG_ACTION_PROFILE_PTR |
    | `[97]` | XLATE_USE_VINTF_CTR_IDX |
    | `[26:1]` | MIM_ISID_KEY |
    | `[13:4]` | MIM_ISID_VFI |
    | `[26:14]` | MIM_ISID_DVP |
    | `[28:27]` | MIM_ISID_RESERVED_0 |
    | `[53]` | MIM_ISID_ISID_DOT1P_PRI_SELECT |
    | `[54]` | MIM_ISID_SD_TAG_DOT1P_PRI_SELECT |
    | `[58:55]` | MIM_ISID_DOT1P_MAPPING_PTR |
    | `[55]` | MIM_ISID_NEW_CFI |
    | `[58:56]` | MIM_ISID_NEW_PRI |
    | `[61:59]` | MIM_ISID_SD_TAG_ACTION_IF_PRESENT |
    | `[63:62]` | MIM_ISID_SD_TAG_ACTION_IF_NOT_PRESENT |
    | `[65:64]` | MIM_ISID_SD_TAG_TPID_INDEX |
    | `[77:66]` | MIM_ISID_SD_TAG_VID |
    | `[78]` | MIM_ISID_SD_TAG_REMARK_CFI |
    | `[98]` | EVEN_PARITY |

---

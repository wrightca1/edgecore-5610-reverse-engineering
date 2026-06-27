# BCM56846 Memories (tables) — IPIPE block

_Ingress pipeline — parsing, L2/L3 lookup, VLAN, FP/TCAM, ingress policy_

218 memories.

---

## ING_PHYS_TO_LOGIC_MAPm

- **Base address:** `0x00162000`  ·  **Entries:** 74  ·  **Entry width:** 1 bytes

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | LOGICAL_PORT_NUMBER |
    | `[6:0]` | LOGIC_PORT |

---

## IARB_MAIN_TDMm

- **Base address:** `0x00170000`  ·  **Entries:** 65  ·  **Entry width:** 1 bytes
- **Function:** TDM TABLE configuration, Set to 0, select port_group5. Set to 1, select port_group4. Set to 2, select extra slot.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | TDM_SLOT |

**Live capture (Cumulus):** 33 entries populated. Sample:

    ipipe0[1]: <TDM_SLOT=1>

---

## PORT_TABm

- **Base address:** `0x01162000`  ·  **Entries:** 67  ·  **Entry width:** 39 bytes
- **Function:** Port Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | FILTER_ENABLE |
    | `[1]` | VT_MISS_DROP |
    | `[2]` | VT_ENABLE |
    | `[3]` | TRUST_DSCP_V4 |
    | `[4]` | TRUST_DSCP_V6 |
    | `[5]` | EN_IFILTER |
    | `[9:6]` | MIRROR |
    | `[12:10]` | OPRI |
    | `[12:10]` | PORT_PRI |
    | `[13]` | IPMC_DO_VLAN |
    | `[14]` | V6IPMC_ENABLE |
    | `[15]` | V4IPMC_ENABLE |
    | `[16]` | V6IPMC_L2_ENABLE |
    | `[17]` | V4IPMC_L2_ENABLE |
    | `[18]` | V6L3_ENABLE |
    | `[19]` | V4L3_ENABLE |
    | `[20]` | DROP_BPDU |
    | `[21]` | PORT_DIS_TAG |
    | `[22]` | PORT_DIS_UNTAG |
    | `[23]` | PASS_CONTROL_FRAMES |
    | `[24]` | SUBNET_BASED_VID_ENABLE |
    | `[25]` | MAC_BASED_VID_ENABLE |
    | `[39:38]` | PORT_TYPE |
    | `[40]` | DUAL_MODID_ENABLE |
    | `[46:41]` | DOT1P_REMAP_POINTER |
    | `[47]` | PVLAN_ENABLE |
    | `[55:48]` | MY_MODID |
    | `[56]` | VLAN_PRECEDENCE |
    | `[57]` | PORT_BRIDGE |
    | `[58]` | MIM_ENABLE_DEFAULT_NETWORK_SVP |
    | `[59]` | HIGIG_TRUNK |
    | `[65]` | HIGIG2 |
    | `[66]` | ALLOW_SRC_MOD |
    | `[70:67]` | RTAG7_PORT_LBN |
    | `[71]` | RTAG7_HASH_CFG_SEL_TRUNK |
    | `[72]` | RTAG7_HASH_CFG_SEL_HIGIG_TRUNK |
    | `[73]` | RTAG7_HASH_CFG_SEL_ECMP |
    | `[74]` | RTAG7_HASH_CFG_SEL_LBID |
    | `[75]` | REMOVE_HG_HDR_SRC_PORT |
    | `[76]` | VFP_ENABLE |
    | `[84:77]` | VFP_PORT_GROUP_ID |
    | `[86:85]` | URPF_MODE |
    | `[87]` | URPF_DEFAULTROUTECHECK |
    | `[91:88]` | CFI_AS_CNG |
    | `[95:92]` | OUTER_TPID_ENABLE |
    | `[103:96]` | ECCP_0 |
    | `[102:96]` | ECC_0 |
    | `[103]` | PARITY_0 |
    | `[104]` | TRUST_INCOMING_VID |
    | `[116:105]` | IVID |
    | `[120:117]` | VT_KEY_TYPE |
    | `[121]` | VT_KEY_TYPE_USE_GLP |
    | `[125:122]` | VT_KEY_TYPE_2 |
    | `[126]` | VT_KEY_TYPE_2_USE_GLP |
    | `[127]` | MH_INGRESS_TAGGED_SEL |
    | `[128]` | CLASS_BASED_SM_ENABLE |
    | `[132:129]` | CML_FLAGS_NEW |
    | `[136:133]` | CML_FLAGS_MOVE |
    | `[161]` | CFI_0_MAPPING |
    | `[162]` | CFI_1_MAPPING |
    | `[163]` | MPLS_ENABLE |
    | `[166:164]` | PORT_OPERATION |
    | `[167]` | DISABLE_VLAN_CHECKS |
    | `[168]` | REMOTE_CPU_EN |
    | `[169]` | DISABLE_STATIC_MOVE_DROP |
    | `[170]` | MIM_TERM_ENABLE |
    | `[172:171]` | CML_BMAC_NEW |
    | `[174:173]` | CML_BMAC_MOVE |
    | `[180:175]` | PROTOCOL_PKT_INDEX |
    | `[186:181]` | TRUST_DOT1P_PTR |
    | `[207:200]` | ECCP_1 |
    | `[206:200]` | ECC_1 |
    | `[207]` | PARITY_1 |
    | `[210:208]` | IPRI |
    | `[211]` | IEEE_802_1AS_ENABLE |
    | `[212]` | USE_PORT_TABLE_GROUP_ID |
    | `[219:213]` | FP_PORT_FIELD_SEL_INDEX |
    | `[227]` | OCFI |
    | `[228]` | ICFI |
    | `[229]` | NIV_UPLINK_PORT |
    | `[241:230]` | NIV_VIF_ID |
    | `[253:242]` | NIV_NAMESPACE |
    | `[262]` | NIV_RPF_CHECK_ENABLE |
    | `[263]` | NIV_VIF_LOOKUP_ENABLE |
    | `[279:264]` | TX_DEST_PORT |
    | `[280]` | TX_DEST_PORT_ENABLE |
    | `[282:281]` | VNTAG_ACTIONS_IF_NOT_PRESENT |
    | `[284:283]` | VNTAG_ACTIONS_IF_PRESENT |
    | `[285]` | DISCARD_IF_VNTAG_PRESENT |
    | `[286]` | DISCARD_IF_VNTAG_NOT_PRESENT |
    | `[288]` | MIM_MC_TERM_ENABLE |
    | `[289]` | USE_IVID_AS_OVID |
    | `[290]` | USE_INNER_PRI |
    | `[291]` | OUTER_TPID_VERIFY |
    | `[297:292]` | TAG_ACTION_PROFILE_PTR |
    | `[298]` | ALLOW_NON_TRILL_FRAMES |
    | `[299]` | ALLOW_TRILL_FRAMES |
    | `[300]` | TRILL_ENABLE |
    | `[301]` | COPY_CORE_IS_IS_TO_CPU |
    | `[302]` | RTAG7_HASH_CFG_SEL_TRILL_ECMP |
    | `[303]` | RESERVED_0 |
    | `[311:304]` | ECCP_2 |
    | `[310:304]` | ECC_2 |
    | `[311]` | PARITY_2 |

---

## SYSTEM_CONFIG_TABLE_MODBASEm

- **Base address:** `0x01164000`  ·  **Entries:** 256  ·  **Entry width:** 2 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | BASE |
    | `[12]` | EVEN_PARITY |

---

## SYSTEM_CONFIG_TABLEm

- **Base address:** `0x01166000`  ·  **Entries:** 4096  ·  **Entry width:** 1 bytes
- **Function:** System Port Table. Holds fields necessary to futher parse a higig packet, address = {src_modid[6:0], src_port[5:0]} FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | OUTER_TPID_ENABLE |
    | `[4]` | EVEN_PARITY |

**Live capture (Cumulus):** 128 entries populated. Sample:

    ipipe0[0]: <OUTER_TPID_ENABLE=1,>

---

## SOURCE_TRUNK_MAP_MODBASEm

- **Base address:** `0x01168000`  ·  **Entries:** 256  ·  **Entry width:** 2 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | BASE |
    | `[12]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BASE=0x80>

---

## SOURCE_TRUNK_MAP_TABLEm

- **Base address:** `0x02162000`  ·  **Entries:** 4096  ·  **Entry width:** 9 bytes
- **Function:** Source Trunk Map Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PORT_TYPE |
    | `[11:2]` | TGID |
    | `[18:12]` | LPORT_PROFILE_IDX |
    | `[26:19]` | CLASS_ID |
    | `[46:34]` | L3_IIF |
    | `[46:34]` | SOURCE_VP |
    | `[45:34]` | OVID |
    | `[43:34]` | VRF_ID |
    | `[47]` | DISABLE_VLAN_CHECKS |
    | `[55:48]` | VFP_PORT_GROUP_ID |
    | `[57:56]` | TRILL_RBRIDGE_NICKNAME_INDEX |
    | `[65]` | PARITY |

---

## L3_TUNNELm

- **Base address:** `0x02164000`  ·  **Entries:** 512  ·  **Entry width:** 41 bytes
- **Function:** L3 Tunnel Table TCAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[1]` | MODE |
    | `[73:66]` | PROTOCOL |
    | `[89:74]` | L4_DEST_PORT |
    | `[106]` | MODE_MASK |
    | `[178:171]` | PROTOCOL_MASK |
    | `[210:195]` | L4_SRC_PORT_MASK |
    | `[211]` | GRE_PAYLOAD_IPV6 |
    | `[212]` | GRE_PAYLOAD_IPV4 |
    | `[215:213]` | SUB_TUNNEL_TYPE |
    | `[213]` | PAYLOAD_IPV6 |
    | `[214]` | PAYLOAD_IPV4 |
    | `[216]` | TUNNEL_TYPE |
    | `[218:217]` | UDP_TUNNEL_TYPE |
    | `[219]` | USE_OUTER_HDR_DSCP |
    | `[220]` | USE_OUTER_HDR_TTL |
    | `[221]` | DONOT_CHANGE_INNER_HDR_DSCP |
    | `[287:286]` | ALLOWED_PORT_BITMAP_W2 |
    | `[300:288]` | IINTF |
    | `[300:288]` | L3_IIF |
    | `[308:301]` | TUNNEL_CLASS_ID |
    | `[323]` | IGNORE_UDP_CHECKSUM |
    | `[324]` | CTRL_PKTS_TO_CPU |
    | `[325]` | EVEN_PARITY |

---

## FP_UDF_TCAMm

- **Base address:** `0x02166000`  ·  **Entries:** 512  ·  **Entry width:** 18 bytes
- **Function:** FP UDF tcam table, FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | INNER_IP_TYPE |
    | `[6:4]` | OUTER_IP_TYPE |
    | `[30:7]` | L3_FIELDS |
    | `[48:47]` | L2_TAG_STATUS |
    | `[49]` | HIGIG |
    | `[51:50]` | L2_TYPE |
    | `[54:52]` | LOOPBACK_PKT_TYPE |
    | `[61:55]` | SOURCE_PORT_NUMBER |
    | `[62]` | VNTAG_PRESENT |
    | `[63]` | CNTAG_PRESENT |
    | `[66:64]` | FC_HDR_ENCODE_2 |
    | `[69:67]` | FC_HDR_ENCODE_1 |
    | `[72:70]` | INNER_IP_TYPE_MASK |
    | `[75:73]` | OUTER_IP_TYPE_MASK |
    | `[115:100]` | L2_ETHER_TYPE_MASK |
    | `[117:116]` | L2_TAG_STATUS_MASK |
    | `[118]` | HIGIG_MASK |
    | `[120:119]` | L2_TYPE_MASK |
    | `[123:121]` | LOOPBACK_PKT_TYPE_MASK |
    | `[131]` | VNTAG_PRESENT_MASK |
    | `[132]` | CNTAG_PRESENT_MASK |
    | `[135:133]` | FC_HDR_ENCODE_2_MASK |
    | `[138:136]` | FC_HDR_ENCODE_1_MASK |

---

## FP_UDF_OFFSETm

- **Base address:** `0x02168000`  ·  **Entries:** 512  ·  **Entry width:** 19 bytes
- **Function:** FP UDF offset table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | UDF1_OFFSET0 |
    | `[11:6]` | UDF1_OFFSET1 |
    | `[17:12]` | UDF1_OFFSET2 |
    | `[23:18]` | UDF1_OFFSET3 |
    | `[29:24]` | UDF1_OFFSET4 |
    | `[41:36]` | UDF1_OFFSET6 |
    | `[47:42]` | UDF1_OFFSET7 |
    | `[50:48]` | UDF1_BASE_OFFSET_0 |
    | `[53:51]` | UDF1_BASE_OFFSET_1 |
    | `[56:54]` | UDF1_BASE_OFFSET_2 |
    | `[59:57]` | UDF1_BASE_OFFSET_3 |
    | `[62:60]` | UDF1_BASE_OFFSET_4 |
    | `[68:66]` | UDF1_BASE_OFFSET_6 |
    | `[71:69]` | UDF1_BASE_OFFSET_7 |
    | `[77:72]` | UDF2_OFFSET0 |
    | `[83:78]` | UDF2_OFFSET1 |
    | `[89:84]` | UDF2_OFFSET2 |
    | `[95:90]` | UDF2_OFFSET3 |
    | `[101:96]` | UDF2_OFFSET4 |
    | `[107:102]` | UDF2_OFFSET5 |
    | `[113:108]` | UDF2_OFFSET6 |
    | `[119:114]` | UDF2_OFFSET7 |
    | `[122:120]` | UDF2_BASE_OFFSET_0 |
    | `[125:123]` | UDF2_BASE_OFFSET_1 |
    | `[131:129]` | UDF2_BASE_OFFSET_3 |
    | `[134:132]` | UDF2_BASE_OFFSET_4 |
    | `[137:135]` | UDF2_BASE_OFFSET_5 |
    | `[140:138]` | UDF2_BASE_OFFSET_6 |
    | `[143:141]` | UDF2_BASE_OFFSET_7 |
    | `[150:144]` | PORT_FIELD_SEL_INDEX |
    | `[151]` | EVEN_PARITY |

---

## ING_MOD_MAP_TABLEm

- **Base address:** `0x0216a000`  ·  **Entries:** 256  ·  **Entry width:** 11 bytes
- **Function:** Ingress Module Remapping Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | THRESH_C |
    | `[13:7]` | THRESH_B |
    | `[20:14]` | THRESH_A |
    | `[27:21]` | PORTOFF_D |
    | `[41:35]` | PORTOFF_B |
    | `[48:42]` | PORTOFF_A |
    | `[56:49]` | MOD_D |
    | `[72:65]` | MOD_B |
    | `[80:73]` | MOD_A |
    | `[81]` | EVEN_PARITY |

---

## SOURCE_MOD_PROXY_TABLEm

- **Base address:** `0x0216c000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** Source MODID table for Higig Lookup

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | V6_ENABLE |
    | `[1]` | USE_MH_PRIORITY |
    | `[2]` | MIM_MC_PROXY_ENABLE |

---

## IPV4_IN_IPV6_PREFIX_MATCH_TABLEm

- **Base address:** `0x02170000`  ·  **Entries:** 4  ·  **Entry width:** 13 bytes
- **Function:** IPv6 in IPv6 Address Prefix Matching Memory

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[96]` | ENABLE |

---

## LPORT_TABm

- **Base address:** `0x02172000`  ·  **Entries:** 128  ·  **Entry width:** 39 bytes
- **Function:** LPort Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | FILTER_ENABLE |
    | `[1]` | VT_MISS_DROP |
    | `[2]` | VT_ENABLE |
    | `[3]` | TRUST_DSCP_V4 |
    | `[4]` | TRUST_DSCP_V6 |
    | `[5]` | EN_IFILTER |
    | `[9:6]` | MIRROR |
    | `[12:10]` | OPRI |
    | `[12:10]` | PORT_PRI |
    | `[13]` | IPMC_DO_VLAN |
    | `[14]` | V6IPMC_ENABLE |
    | `[15]` | V4IPMC_ENABLE |
    | `[16]` | V6IPMC_L2_ENABLE |
    | `[17]` | V4IPMC_L2_ENABLE |
    | `[18]` | V6L3_ENABLE |
    | `[19]` | V4L3_ENABLE |
    | `[20]` | DROP_BPDU |
    | `[21]` | PORT_DIS_TAG |
    | `[22]` | PORT_DIS_UNTAG |
    | `[23]` | PASS_CONTROL_FRAMES |
    | `[24]` | SUBNET_BASED_VID_ENABLE |
    | `[25]` | MAC_BASED_VID_ENABLE |
    | `[39:38]` | PORT_TYPE |
    | `[40]` | DUAL_MODID_ENABLE |
    | `[46:41]` | DOT1P_REMAP_POINTER |
    | `[47]` | PVLAN_ENABLE |
    | `[55:48]` | MY_MODID |
    | `[56]` | VLAN_PRECEDENCE |
    | `[57]` | PORT_BRIDGE |
    | `[58]` | MIM_ENABLE_DEFAULT_NETWORK_SVP |
    | `[59]` | HIGIG_TRUNK |
    | `[65]` | HIGIG2 |
    | `[66]` | ALLOW_SRC_MOD |
    | `[70:67]` | RTAG7_PORT_LBN |
    | `[71]` | RTAG7_HASH_CFG_SEL_TRUNK |
    | `[72]` | RTAG7_HASH_CFG_SEL_HIGIG_TRUNK |
    | `[73]` | RTAG7_HASH_CFG_SEL_ECMP |
    | `[74]` | RTAG7_HASH_CFG_SEL_LBID |
    | `[75]` | REMOVE_HG_HDR_SRC_PORT |
    | `[76]` | VFP_ENABLE |
    | `[84:77]` | VFP_PORT_GROUP_ID |
    | `[86:85]` | URPF_MODE |
    | `[87]` | URPF_DEFAULTROUTECHECK |
    | `[91:88]` | CFI_AS_CNG |
    | `[95:92]` | OUTER_TPID_ENABLE |
    | `[103:96]` | ECCP_0 |
    | `[102:96]` | ECC_0 |
    | `[103]` | PARITY_0 |
    | `[104]` | TRUST_INCOMING_VID |
    | `[116:105]` | IVID |
    | `[120:117]` | VT_KEY_TYPE |
    | `[121]` | VT_KEY_TYPE_USE_GLP |
    | `[125:122]` | VT_KEY_TYPE_2 |
    | `[126]` | VT_KEY_TYPE_2_USE_GLP |
    | `[127]` | MH_INGRESS_TAGGED_SEL |
    | `[128]` | CLASS_BASED_SM_ENABLE |
    | `[132:129]` | CML_FLAGS_NEW |
    | `[136:133]` | CML_FLAGS_MOVE |
    | `[161]` | CFI_0_MAPPING |
    | `[162]` | CFI_1_MAPPING |
    | `[163]` | MPLS_ENABLE |
    | `[166:164]` | PORT_OPERATION |
    | `[167]` | DISABLE_VLAN_CHECKS |
    | `[168]` | REMOTE_CPU_EN |
    | `[169]` | DISABLE_STATIC_MOVE_DROP |
    | `[170]` | MIM_TERM_ENABLE |
    | `[172:171]` | CML_BMAC_NEW |
    | `[174:173]` | CML_BMAC_MOVE |
    | `[180:175]` | PROTOCOL_PKT_INDEX |
    | `[186:181]` | TRUST_DOT1P_PTR |
    | `[207:200]` | ECCP_1 |
    | `[206:200]` | ECC_1 |
    | `[207]` | PARITY_1 |
    | `[210:208]` | IPRI |
    | `[211]` | IEEE_802_1AS_ENABLE |
    | `[212]` | USE_PORT_TABLE_GROUP_ID |
    | `[219:213]` | FP_PORT_FIELD_SEL_INDEX |
    | `[227]` | OCFI |
    | `[228]` | ICFI |
    | `[229]` | NIV_UPLINK_PORT |
    | `[241:230]` | NIV_VIF_ID |
    | `[253:242]` | NIV_NAMESPACE |
    | `[262]` | NIV_RPF_CHECK_ENABLE |
    | `[263]` | NIV_VIF_LOOKUP_ENABLE |
    | `[279:264]` | TX_DEST_PORT |
    | `[280]` | TX_DEST_PORT_ENABLE |
    | `[282:281]` | VNTAG_ACTIONS_IF_NOT_PRESENT |
    | `[284:283]` | VNTAG_ACTIONS_IF_PRESENT |
    | `[285]` | DISCARD_IF_VNTAG_PRESENT |
    | `[286]` | DISCARD_IF_VNTAG_NOT_PRESENT |
    | `[288]` | MIM_MC_TERM_ENABLE |
    | `[289]` | USE_IVID_AS_OVID |
    | `[290]` | USE_INNER_PRI |
    | `[291]` | OUTER_TPID_VERIFY |
    | `[297:292]` | TAG_ACTION_PROFILE_PTR |
    | `[298]` | ALLOW_NON_TRILL_FRAMES |
    | `[299]` | ALLOW_TRILL_FRAMES |
    | `[300]` | TRILL_ENABLE |
    | `[301]` | COPY_CORE_IS_IS_TO_CPU |
    | `[302]` | RTAG7_HASH_CFG_SEL_TRILL_ECMP |
    | `[303]` | RESERVED_0 |
    | `[311:304]` | ECCP_2 |
    | `[310:304]` | ECC_2 |
    | `[311]` | PARITY_2 |

---

## ING_VLAN_RANGEm

- **Base address:** `0x02174000`  ·  **Entries:** 128  ·  **Entry width:** 25 bytes
- **Function:** vlan range match table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | VLAN_MIN_0 |
    | `[23:12]` | VLAN_MAX_0 |
    | `[47:36]` | VLAN_MAX_1 |
    | `[59:48]` | VLAN_MIN_2 |
    | `[83:72]` | VLAN_MIN_3 |
    | `[95:84]` | VLAN_MAX_3 |
    | `[107:96]` | VLAN_MIN_4 |
    | `[119:108]` | VLAN_MAX_4 |
    | `[143:132]` | VLAN_MAX_5 |
    | `[155:144]` | VLAN_MIN_6 |
    | `[179:168]` | VLAN_MIN_7 |
    | `[191:180]` | VLAN_MAX_7 |
    | `[192]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <VLAN_MIN_7=1,VLAN_MIN_6=1,VLAN_MIN_5=1,VLAN_MIN_4=1,VLAN_MIN_3=1,VLAN_MIN_2=1,VLAN_MIN_1=1,VLAN_MIN_0=1,>

---

## CPU_TS_MAPm

- **Base address:** `0x02176000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** vlan range match table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | CPU_QUEUE_ID |
    | `[6]` | EVEN_PARITY |

---

## FC_HEADER_TYPEm

- **Base address:** `0x0217a000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** FCoE Header Type.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | FC_HDR_ENCODE |

**Live capture (Cumulus):** 41 entries populated. Sample:

    ipipe0[0]: <FC_HDR_ENCODE=1>

---

## ING_TRILL_PARSE_CONTROLm

- **Base address:** `0x0217c000`  ·  **Entries:** 1  ·  **Entry width:** 18 bytes
- **Function:** Trill parse control.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TRILL_ETHERTYPE |
    | `[112]` | TRILL_ETHERTYPE_ENABLE |
    | `[113]` | TRILL_ALL_RBRIDGES_MAC_ADDRESS_ENABLE |
    | `[114]` | TRILL_ALL_IS_IS_RBRIDGES_MAC_ADDRESS_ENABLE |
    | `[115]` | L2_IS_IS_ETHERTYPE_ENABLE |
    | `[137:132]` | MIN_INCOMING_HOPCOUNT |
    | `[138]` | EGRESS_RBRIDGE_CHECK_HOPCOUNT |

---

## VLAN_PROTOCOLm

- **Base address:** `0x04160000`  ·  **Entries:** 16  ·  **Entry width:** 3 bytes
- **Function:** Holds data for Protocol-based VLAN substitution.  Just the VLAN_PROTOCOL RAM.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | LLC |
    | `[17]` | SNAP |
    | `[18]` | ETHERII |
    | `[19]` | MATCHLOWER |
    | `[20]` | MATCHUPPER |

---

## VLAN_PROTOCOL_DATAm

- **Base address:** `0x04162000`  ·  **Entries:** 2048  ·  **Entry width:** 5 bytes
- **Function:** Holds data for Protocol-based VLAN substitution

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | OPRI |
    | `[2:0]` | PRI |
    | `[14:3]` | OVID |
    | `[14:3]` | VLAN_ID |
    | `[26:15]` | IVID |
    | `[33]` | OCFI |
    | `[34]` | ICFI |
    | `[37:35]` | IPRI |
    | `[38]` | EVEN_PARITY |

**Live capture (Cumulus):** 832 entries populated. Sample:

    ipipe0[16]: <VLAN_ID=0xce5,OVID=0xce5,>

---

## VLAN_SUBNETm

- **Base address:** `0x04164000`  ·  **Entries:** 512  ·  **Entry width:** 21 bytes
- **Function:** TCAM for IP subnet based VLAN substitution

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[131:129]` | OPRI |
    | `[131:129]` | PRI |
    | `[143:132]` | OVID |
    | `[143:132]` | VLAN_ID |
    | `[155:144]` | IVID |
    | `[162]` | OCFI |
    | `[163]` | ICFI |
    | `[166:164]` | IPRI |
    | `[167]` | EVEN_PARITY |

---

## VLAN_SUBNET_ONLYm

- **Base address:** `0x04166000`  ·  **Entries:** 512  ·  **Entry width:** 17 bytes
- **Function:** TCAM for IP subnet based VLAN substitution

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |

---

## VLAN_SUBNET_DATA_ONLYm

- **Base address:** `0x04168000`  ·  **Entries:** 512  ·  **Entry width:** 5 bytes
- **Function:** Holds data for IP Subnet-based VLAN substitution

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | OPRI |
    | `[2:0]` | PRI |
    | `[14:3]` | OVID |
    | `[14:3]` | VLAN_ID |
    | `[26:15]` | IVID |
    | `[33]` | OCFI |
    | `[34]` | ICFI |
    | `[37:35]` | IPRI |
    | `[38]` | EVEN_PARITY |

---

## VLAN_MACm

- **Base address:** `0x0416e000`  ·  **Entries:** 8192  ·  **Entry width:** 15 bytes
- **Function:** Holds key & data for MAC-based VLAN substitution

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[4:1]` | KEY_TYPE |
    | `[76:65]` | MAC_IVID |
    | `[77]` | MAC_RESERVED_IVID |
    | `[83:78]` | MAC_TAG_ACTION_PROFILE_PTR |
    | `[86:84]` | MAC_OPRI |
    | `[86:84]` | MAC_PRI |
    | `[87]` | MAC_OCFI |
    | `[88]` | MAC_ICFI |
    | `[91:89]` | MAC_IPRI |
    | `[43:37]` | MAC_IP_BIND_SRC_PORT |
    | `[51:44]` | MAC_IP_BIND_SRC_MODID |
    | `[100]` | MAC_IP_BIND_SRC_T |
    | `[113:101]` | MAC_IP_BIND_RESERVED_0 |
    | `[114]` | EVEN_PARITY |

---

## VLAN_XLATEm

- **Base address:** `0x04170000`  ·  **Entries:** 8192  ·  **Entry width:** 15 bytes
- **Function:** BCAM for VLAN trans of tagged pkts.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[4:1]` | KEY_TYPE |
    | `[20:5]` | XLATE_GLP |
    | `[14:5]` | XLATE_TGID |
    | `[11:5]` | XLATE_PORT_NUM |
    | `[19:12]` | XLATE_MODULE_ID |
    | `[20]` | XLATE_T |
    | `[44:33]` | XLATE_IVID |
    | `[44:37]` | XLATE_KEY_ZERO_1 |
    | `[46:45]` | XLATE_MPLS_ACTION |
    | `[58:47]` | XLATE_NEW_OVID |
    | `[58:47]` | XLATE_NEW_VLAN_ID |
    | `[83:71]` | XLATE_DUMMY |
    | `[83:71]` | XLATE_L3_IIF |
    | `[83:71]` | XLATE_SOURCE_VP |
    | `[89:84]` | XLATE_TAG_ACTION_PROFILE_PTR |
    | `[92:90]` | XLATE_NEW_OPRI |
    | `[92:90]` | XLATE_OPRI |
    | `[106]` | XLATE_RESERVED_0 |
    | `[107]` | XLATE_DISABLE_VLAN_CHECKS |
    | `[108]` | XLATE_NEW_OCFI |
    | `[109]` | XLATE_NEW_ICFI |
    | `[112:110]` | XLATE_NEW_IPRI |
    | `[113]` | XLATE_USE_VINTF_CTR_IDX |
    | `[20:5]` | VIF_GLP |
    | `[14:5]` | VIF_TGID |
    | `[11:5]` | VIF_PORT_NUM |
    | `[19:12]` | VIF_MODULE_ID |
    | `[20]` | VIF_T |
    | `[44:33]` | VIF_VLAN |
    | `[46:45]` | VIF_MPLS_ACTION |
    | `[58:47]` | VIF_NEW_OVID |
    | `[58:47]` | VIF_NEW_VLAN_ID |
    | `[83:71]` | VIF_DUMMY |
    | `[83:71]` | VIF_L3_IIF |
    | `[83:71]` | VIF_SOURCE_VP |
    | `[89:84]` | VIF_TAG_ACTION_PROFILE_PTR |
    | `[92:90]` | VIF_NEW_OPRI |
    | `[92:90]` | VIF_OPRI |
    | `[106]` | VIF_USE_AS_DEFAULT_VLAN |
    | `[107]` | VIF_DISABLE_VLAN_CHECKS |
    | `[108]` | VIF_NEW_OCFI |
    | `[109]` | VIF_NEW_ICFI |
    | `[112:110]` | VIF_NEW_IPRI |
    | `[113]` | VIF_USE_VINTF_CTR_IDX |
    | `[114]` | EVEN_PARITY |

---

## VFP_TCAMm

- **Base address:** `0x04172000`  ·  **Entries:** 1024  ·  **Entry width:** 59 bytes
- **Function:** TCAM FOR VFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | VALID |

**Live capture (Cumulus):** 3 entries populated. Sample:

    ipipe0[0]: <VALID=3,MASK=0x00000000000000000000ffffffffff000000000000000000000000000000,KEY=0x0000000000000000000001005e0000000000000000000000000000000000,F2_MASK=0xffffffffff0000000000000000000000,F2=0x01005e00000000000000000000000000,>

---

## ING_VLAN_TAG_ACTION_PROFILEm

- **Base address:** `0x04176000`  ·  **Entries:** 64  ·  **Entry width:** 8 bytes
- **Function:** ACTIONS for the VXLT stage

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

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <UT_OTAG_ACTION=1,UT_OPRI_ACTION=1,UT_OCFI_ACTION=1,SOT_POTAG_ACTION=2,SIT_OTAG_ACTION=1,SIT_OPRI_ACTION=1,SIT_OCFI_ACTION=1,DT_POTAG_ACTION=2,>

---

## VFP_POLICY_TABLEm

- **Base address:** `0x0417a000`  ·  **Entries:** 1024  ·  **Entry width:** 17 bytes
- **Function:** POLICY TABLE FOR DETERMINING ACTIONS IN THE VFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | FIELDS_ACTION |
    | `[2]` | DISABLE_VLAN_CHECKS |
    | `[15:3]` | L3_IIF |
    | `[15:3]` | SVP |
    | `[12:3]` | VFP_VRF_ID |
    | `[15:13]` | VFP_VRF_ID_UNSED |
    | `[16]` | USE_VFP_CLASS_ID_H |
    | `[22:17]` | VFP_CLASS_ID_H |
    | `[23]` | USE_VFP_CLASS_ID_L |
    | `[29:24]` | VFP_CLASS_ID_L |
    | `[44:33]` | NEW_OUTER_VLAN |
    | `[47:45]` | INNER_VLAN_ACTIONS |
    | `[59:48]` | NEW_INNER_VLAN |
    | `[60]` | CHANGE_CNG |
    | `[62:61]` | NEW_CNG |
    | `[66:65]` | COPY_TO_CPU |
    | `[67]` | CHANGE_INT_PRIORITY |
    | `[71:68]` | NEW_INT_PRIORITY |
    | `[73:72]` | RESERVED_0 |
    | `[74]` | DO_NOT_LEARN |
    | `[82:75]` | VFP_MATCHED_RULE |
    | `[88:83]` | CPU_COS |
    | `[89]` | IPV6_TO_IPV4_MAP_DIP_VALID |
    | `[90]` | IPV6_TO_IPV4_MAP_SIP_VALID |
    | `[109:97]` | VINTF_CTR_IDX |
    | `[110]` | USE_VINTF_CTR_IDX |
    | `[112:111]` | CHANGE_OUTER_DOT1P |
    | `[115:113]` | NEW_OUTER_DOT1P |
    | `[117:116]` | CHANGE_OUTER_CFI |
    | `[118]` | NEW_OUTER_CFI |
    | `[120:119]` | CHANGE_INNER_DOT1P |
    | `[123:121]` | NEW_INNER_DOT1P |
    | `[125:124]` | CHANGE_INNER_CFI |
    | `[126]` | NEW_INNER_CFI |
    | `[134]` | EVEN_PARITY |

**Live capture (Cumulus):** 3 entries populated. Sample:

    ipipe0[0]: <COPY_TO_CPU=1,>

---

## MPLS_ENTRYm

- **Base address:** `0x0417c000`  ·  **Entries:** 8192  ·  **Entry width:** 12 bytes
- **Function:** MPLS Label Lookup. Dual-Hash table with Keys and Data

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[13:4]` | MPLS_TGID |
    | `[10:4]` | MPLS_PORT_NUM |
    | `[18:11]` | MPLS_MODULE_ID |
    | `[19]` | MPLS_T |
    | `[42:40]` | MPLS_MPLS_ACTION_IF_BOS |
    | `[44:43]` | MPLS_CW_CHECK_CTRL |
    | `[45]` | MPLS_DECAP_USE_TTL |
    | `[47:46]` | MPLS_DECAP_USE_EXP_FOR_PRI |
    | `[52:48]` | MPLS_EXP_MAPPING_PTR |
    | `[56:53]` | MPLS_NEW_PRI |
    | `[71]` | MPLS_DECAP_USE_EXP_FOR_INNER |
    | `[72]` | MPLS_V4_ENABLE |
    | `[73]` | MPLS_V6_ENABLE |
    | `[86:74]` | MPLS_PW_TERM_NUM |
    | `[86:74]` | MPLS_VINTF_CTR_IDX |
    | `[87]` | MPLS_PW_TERM_NUM_VALID |
    | `[88]` | MPLS_USE_VINTF_CTR_IDX |
    | `[90:89]` | MPLS_MPLS_ACTION_IF_NOT_BOS |
    | `[93:91]` | MPLS_RESERVED_0 |
    | `[15:4]` | MIM_NVP_BVID |
    | `[93:64]` | MIM_NVP_DATA |
    | `[73:64]` | MIM_NVP_TGID |
    | `[70:64]` | MIM_NVP_PORT_NUM |
    | `[78:71]` | MIM_NVP_MODULE_ID |
    | `[79]` | MIM_NVP_T |
    | `[92:80]` | MIM_NVP_SVP |
    | `[93]` | MIM_NVP_ISID_LOOKUP_TYPE |
    | `[27:4]` | MIM_ISID_ISID |
    | `[50:41]` | MIM_ISID_VFI |
    | `[19:1]` | TRILL_KEY |
    | `[19:4]` | TRILL_RBRIDGE_NICKNAME |
    | `[25:20]` | TRILL_CLASS_ID |
    | `[41:38]` | TRILL_TREE_ID |
    | `[42]` | TRILL_DST_COPY_TO_CPU |
    | `[43]` | TRILL_MCAST_DST_DISCARD |
    | `[44]` | TRILL_UCAST_DST_DISCARD |
    | `[58:45]` | TRILL_NEXT_HOP_INDEX |
    | `[54:45]` | TRILL_ECMP_PTR |
    | `[59]` | TRILL_ECMP |
    | `[60]` | TRILL_DECAP_TRILL_TUNNEL |
    | `[61]` | TRILL_SRC_COPY_TO_CPU |
    | `[62]` | TRILL_SRC_DISCARD |
    | `[63]` | TRILL_PHB_FROM_OUTER_L2_HEADER |
    | `[76:64]` | TRILL_VIRTUAL_PORT |
    | `[93:77]` | TRILL_RESERVED_0 |
    | `[94]` | EVEN_PARITY |

---

## VLAN_MPLSm

- **Base address:** `0x05160000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** Contains MPLS cntrls assoc with the 4K VLANs.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MPLS_ENABLE |
    | `[1]` | MIM_TERM_ENABLE |
    | `[14:2]` | L3_IIF |
    | `[15]` | EVEN_PARITY |

**Live capture (Cumulus):** 53 entries populated. Sample:

    ipipe0[1]: <MPLS_ENABLE=1,MIM_TERM_ENABLE=1,L3_IIF=1,>

---

## MY_STATION_TCAMm

- **Base address:** `0x05162000`  ·  **Entries:** 512  ·  **Entry width:** 19 bytes
- **Function:** TCAM for MPLS My Station lookups - no associated data.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[60:49]` | VLAN_ID |
    | `[127:116]` | VLAN_ID_MASK |
    | `[134:128]` | ING_PORT_NUM_MASK |
    | `[144:135]` | DATA |
    | `[135]` | MIM_TERMINATION_ALLOWED |
    | `[136]` | MPLS_TERMINATION_ALLOWED |
    | `[137]` | TRILL_TERMINATION_ALLOWED |
    | `[138]` | IPV4_TERMINATION_ALLOWED |
    | `[139]` | IPV6_TERMINATION_ALLOWED |
    | `[140]` | ARP_RARP_TERMINATION_ALLOWED |
    | `[142]` | FCOE_TERMINATION_ALLOWED |
    | `[143]` | DISCARD |
    | `[144]` | COPY_TO_CPU |
    | `[145]` | EVEN_PARITY |

**Live capture (Cumulus):** 52 entries populated. Sample:

    ipipe0[7]: <VALID=1,MASK=0x000000ffffffffffff,MAC_ADDR_MASK=0xffffffffffff,MAC_ADDR=0x80a23581caaf,KEY=0x00000080a23581caaf,IPV6_TERMINATION_ALLOWED=1,IPV4_TERMINATION_ALLOWED=1,DATA=0x38,ARP_RARP_TERMINATION_ALLOWED=1>

---

## MY_STATION_TCAM_ENTRY_ONLYm

- **Base address:** `0x05164000`  ·  **Entries:** 512  ·  **Entry width:** 17 bytes
- **Function:** TCAM for MPLS My Station lookups - no associated data.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[60:49]` | VLAN_ID |
    | `[127:116]` | VLAN_ID_MASK |
    | `[134:128]` | ING_PORT_NUM_MASK |

**Live capture (Cumulus):** 52 entries populated. Sample:

    ipipe0[7]: <VALID=1,MASK=0x000000ffffffffffff,MAC_ADDR_MASK=0xffffffffffff,MAC_ADDR=0x80a23581caaf,KEY=0x00000080a23581caaf,>

---

## MY_STATION_TCAM_DATA_ONLYm

- **Base address:** `0x05166000`  ·  **Entries:** 512  ·  **Entry width:** 2 bytes
- **Function:** TCAM for MPLS My Station lookups - no associated data.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | DATA |
    | `[0]` | MIM_TERMINATION_ALLOWED |
    | `[1]` | MPLS_TERMINATION_ALLOWED |
    | `[2]` | TRILL_TERMINATION_ALLOWED |
    | `[3]` | IPV4_TERMINATION_ALLOWED |
    | `[4]` | IPV6_TERMINATION_ALLOWED |
    | `[5]` | ARP_RARP_TERMINATION_ALLOWED |
    | `[7]` | FCOE_TERMINATION_ALLOWED |
    | `[8]` | DISCARD |
    | `[9]` | COPY_TO_CPU |
    | `[10]` | EVEN_PARITY |

**Live capture (Cumulus):** 52 entries populated. Sample:

    ipipe0[7]: <IPV6_TERMINATION_ALLOWED=1,IPV4_TERMINATION_ALLOWED=1,DATA=0x38,ARP_RARP_TERMINATION_ALLOWED=1>

---

## VFI_1m

- **Base address:** `0x0516e000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** VFI-1 Table (used for MAC-in-MAC and HG ports) - address is VFI value.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | TPID_ENABLE |
    | `[4]` | SD_TAG_MODE |
    | `[5]` | EVEN_PARITY |

---

## ING_MPLS_EXP_MAPPINGm

- **Base address:** `0x05170000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** EXP to Internal Priority and Color Maping table. Address = {EXP_MAPPING_PTR, EXP}

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | CNG |
    | `[5:2]` | PRI |

---

## STG_TABm

- **Base address:** `0x05176000`  ·  **Entries:** 512  ·  **Entry width:** 18 bytes
- **Function:** Spanning Tree Group state table

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

---

## VLAN_PROFILE_TABm

- **Base address:** `0x05178000`  ·  **Entries:** 128  ·  **Entry width:** 6 bytes
- **Function:** Programmable L2_MISS_TOCPU Value.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | L2_PFM |
    | `[3:2]` | L3_IPV4_PFM |
    | `[5:4]` | L3_IPV6_PFM |
    | `[6]` | UNKNOWN_IPV4_MC_TOCPU |
    | `[7]` | UNKNOWN_IPV6_MC_TOCPU |
    | `[8]` | LEARN_DISABLE |
    | `[10:9]` | OUTER_TPID_INDEX |
    | `[11]` | ICMP_REDIRECT_TOCPU |
    | `[12]` | IPMCV6_ENABLE |
    | `[13]` | IPMCV4_ENABLE |
    | `[14]` | IPMCV6_L2_ENABLE |
    | `[15]` | IPMCV4_L2_ENABLE |
    | `[16]` | IPV6L3_ENABLE |
    | `[17]` | IPV4L3_ENABLE |
    | `[18]` | L2_MISS_TOCPU |
    | `[19]` | L2_MISS_DROP |
    | `[20]` | L2_NON_UCAST_TOCPU |
    | `[21]` | L2_NON_UCAST_DROP |
    | `[25:22]` | PHB2_DOT1P_MAPPING_PTR |
    | `[26]` | PHB2_USE_INNER_DOT1P |
    | `[27]` | PHB2_ENABLE |
    | `[34]` | TRUST_DOT1P |
    | `[40:35]` | PROTOCOL_PKT_INDEX |

---

## ING_OUTER_DOT1P_MAPPING_TABLEm

- **Base address:** `0x0517a000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Outer Dot1p mapping table, used to mark traffic from non-QCN-aware sources with a dot1p value that does not map to QCN-aware queues. The PORT_TABLE/SVP/VFI tables select the profile, and the {cfi,got1p[2:0]} value selects one of 16 entries.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | NEW_DOT1P |
    | `[3]` | NEW_CFI |

**Live capture (Cumulus):** 15 entries populated. Sample:

    ipipe0[1]: <NEW_CFI=1>

---

## L2_HITDA_ONLYm

- **Base address:** `0x06120000`  ·  **Entries:** 16384  ·  **Entry width:** 1 bytes
- **Function:** HW managed L2_HITDA_ONLY table.  Just the DA hit bits.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HITDA_0 |
    | `[1]` | HITDA_1 |
    | `[2]` | HITDA_2 |
    | `[3]` | HITDA_3 |
    | `[4]` | HITDA_4 |
    | `[5]` | HITDA_5 |
    | `[6]` | HITDA_6 |
    | `[7]` | HITDA_7 |

---

## L2_HITSA_ONLYm

- **Base address:** `0x06124000`  ·  **Entries:** 16384  ·  **Entry width:** 2 bytes
- **Function:** HW managed L2_HITSA_ONLY table.  Just the SA hit bits.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HITSA_0 |
    | `[1]` | HITSA_1 |
    | `[2]` | HITSA_2 |
    | `[3]` | HITSA_3 |
    | `[4]` | HITSA_4 |
    | `[5]` | HITSA_5 |
    | `[6]` | HITSA_6 |
    | `[7]` | HITSA_7 |
    | `[8]` | LOCAL_SA_0 |
    | `[9]` | LOCAL_SA_1 |
    | `[10]` | LOCAL_SA_2 |
    | `[11]` | LOCAL_SA_3 |
    | `[12]` | LOCAL_SA_4 |
    | `[13]` | LOCAL_SA_5 |
    | `[14]` | LOCAL_SA_6 |
    | `[15]` | LOCAL_SA_7 |

---

## L2_MOD_FIFOm

- **Base address:** `0x0612e000`  ·  **Entries:** 128  ·  **Entry width:** 21 bytes
- **Function:** FIFO for operations that MODify the L2_ENTRY table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | OPERATION |
    | `[4]` | RESERVED_0 |
    | `[7:5]` | ENTRY_INDEX |
    | `[21:8]` | BUCKET_INDEX |
    | `[164]` | STATION_MOVE |
    | `[165]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[0]: <L2_ENTRY_DATA=0x082000000a0000000000110011,BUCKET_INDEX=0x1406>

---

## L2_BULK_MATCH_MASKm

- **Base address:** `0x06132000`  ·  **Entries:** 1  ·  **Entry width:** 13 bytes
- **Function:** L2 Bulk match enable.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |
    | `[100]` | HITDA |
    | `[101]` | HITSA |
    | `[102]` | LOCAL_SA |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <VALID=1,TRILL_NONUC_NETWORK_SHORT:RESERVED_0=0x001000000000,TRILL_NONUC_NETWORK_SHORT:KEY=7,TRILL_NONUC_NETWORK_SHORT:DATA=0x00000000001000000000,TRILL_NONUC_NETWORK_SHORT:ASSOCIATED_DATA=0x00000000001000000000,KEY_TYPE=7,>

---

## L2_BULK_MATCH_DATAm

- **Base address:** `0x06134000`  ·  **Entries:** 1  ·  **Entry width:** 13 bytes
- **Function:** L2 Bulk match enable.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |
    | `[100]` | HITDA |
    | `[101]` | HITSA |
    | `[102]` | LOCAL_SA |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <VPG_1=0x200,VALID=1,TGID_1=0x200,MODULE_ID_1=4,MAC_ADDR=0x010000000000,L2:MAC_ADDR=0x010000000000,L2:KEY=0x0080000000000000,KEY=0x0080000000000000,DESTINATION_1=0x200,>

---

## L2_BULK_REPLACE_MASKm

- **Base address:** `0x06136000`  ·  **Entries:** 1  ·  **Entry width:** 13 bytes
- **Function:** L2 Bulk match enable.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |
    | `[100]` | HITDA |
    | `[101]` | HITSA |
    | `[102]` | LOCAL_SA |

---

## L2_BULK_REPLACE_DATAm

- **Base address:** `0x06138000`  ·  **Entries:** 1  ·  **Entry width:** 13 bytes
- **Function:** L2 Bulk match enable.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |
    | `[100]` | HITDA |
    | `[101]` | HITSA |
    | `[102]` | LOCAL_SA |

---

## L2_USER_ENTRYm

- **Base address:** `0x06168000`  ·  **Entries:** 512  ·  **Entry width:** 20 bytes
- **Function:** Combined L2_ENTRY TCAM/Data RAM for guaranteed L2 entries and BPDUs.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[60:49]` | VLAN_ID |
    | `[61]` | KEY_TYPE |
    | `[126:123]` | PRI |
    | `[127]` | RESERVED_0 |
    | `[128]` | RPE |
    | `[129]` | CPU |
    | `[130]` | DST_DISCARD |
    | `[140:131]` | TGID |
    | `[137:131]` | PORT_NUM |
    | `[145:138]` | MODULE_ID |
    | `[146]` | T |
    | `[147]` | DO_NOT_LEARN_MACSA |
    | `[153:148]` | CLASS_ID |
    | `[154]` | BPDU |
    | `[155]` | L2_PROTOCOL_PKT |
    | `[156]` | EVEN_PARITY |

**Live capture (Cumulus):** 63 entries populated. Sample:

    ipipe0[0]: <VALID=1,MASK=0x1000ffffffffffff,MAC_ADDR=0x0180c2000000,KEY=0x00000180c2000000,CPU=1,BPDU=1>

---

## L2_USER_ENTRY_ONLYm

- **Base address:** `0x0616a000`  ·  **Entries:** 512  ·  **Entry width:** 16 bytes
- **Function:** TCAM for guaranteed L2 entries and BPDUs.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[60:49]` | VLAN_ID |
    | `[61]` | KEY_TYPE |

**Live capture (Cumulus):** 63 entries populated. Sample:

    ipipe0[0]: <VALID=1,MASK=0x1000ffffffffffff,MAC_ADDR=0x0180c2000000,KEY=0x00000180c2000000>

---

## L2_USER_ENTRY_DATA_ONLYm

- **Base address:** `0x0616c000`  ·  **Entries:** 512  ·  **Entry width:** 5 bytes
- **Function:** Data SRAM for L2_USER_ENTRY TCAM.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PRI |
    | `[4]` | RESERVED_0 |
    | `[5]` | RPE |
    | `[6]` | CPU |
    | `[7]` | DST_DISCARD |
    | `[17:8]` | TGID |
    | `[14:8]` | PORT_NUM |
    | `[22:15]` | MODULE_ID |
    | `[23]` | T |
    | `[24]` | DO_NOT_LEARN_MACSA |
    | `[30:25]` | CLASS_ID |
    | `[31]` | BPDU |
    | `[32]` | L2_PROTOCOL_PKT |
    | `[33]` | EVEN_PARITY |

**Live capture (Cumulus):** 63 entries populated. Sample:

    ipipe0[0]: <CPU=1,BPDU=1>

---

## L2Xm

- **Base address:** `0x07120000`  ·  **Entries:** 131072  ·  **Entry width:** 13 bytes
- **Function:** Combined HW managed L2 entry table.  Includes L2_ENTRY, L2_HITDA, and L2_HITSA

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |
    | `[100]` | HITDA |
    | `[101]` | HITSA |
    | `[102]` | LOCAL_SA |

---

## L2_ENTRY_ONLYm

- **Base address:** `0x08120000`  ·  **Entries:** 131072  ·  **Entry width:** 13 bytes
- **Function:** HW managed L2_ENTRY table only.  Does not include L2_HITSA or L2_HITDA

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[15:4]` | LEGACY_OVID |
    | `[15:4]` | LEGACY_VLAN_ID |
    | `[13:4]` | LEGACY_VFI |
    | `[27:16]` | LEGACY_IVID |
    | `[61:47]` | LEGACY_DESTINATION_1 |
    | `[59:47]` | LEGACY_VPG_1 |
    | `[56:47]` | LEGACY_TGID_1 |
    | `[53:47]` | LEGACY_PORT_NUM_1 |
    | `[61:54]` | LEGACY_MODULE_ID_1 |
    | `[61]` | LEGACY_REMOTE_TRUNK_1 |
    | `[63:62]` | LEGACY_DEST_TYPE_1 |
    | `[62]` | LEGACY_T_1 |
    | `[63]` | LEGACY_VPG_TYPE_1 |
    | `[78:64]` | LEGACY_DESTINATION |
    | `[76:64]` | LEGACY_L2MC_PTR |
    | `[76:64]` | LEGACY_VPG |
    | `[73:64]` | LEGACY_TGID |
    | `[70:64]` | LEGACY_PORT_NUM |
    | `[78:71]` | LEGACY_MODULE_ID |
    | `[77]` | LEGACY_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | LEGACY_REMOTE_TRUNK |
    | `[80:79]` | LEGACY_DEST_TYPE |
    | `[79]` | LEGACY_T |
    | `[80]` | LEGACY_VPG_TYPE |
    | `[86:81]` | LEGACY_CLASS_ID |
    | `[85:81]` | LEGACY_MAC_BLOCK_INDEX |
    | `[86]` | LEGACY_DUMMY_INDEX |
    | `[87]` | LEGACY_RPE |
    | `[91:88]` | LEGACY_PRI |
    | `[92]` | LEGACY_PENDING |
    | `[93]` | LEGACY_STATIC_BIT |
    | `[94]` | LEGACY_DST_DISCARD |
    | `[95]` | LEGACY_CPU |
    | `[96]` | LEGACY_SRC_DISCARD |
    | `[97]` | LEGACY_SCP |
    | `[15:4]` | L2_VLAN_ID |
    | `[13:4]` | L2_VFI |
    | `[78:64]` | L2_DESTINATION |
    | `[76:64]` | L2_L2MC_PTR |
    | `[76:64]` | L2_VPG |
    | `[73:64]` | L2_TGID |
    | `[70:64]` | L2_PORT_NUM |
    | `[78:71]` | L2_MODULE_ID |
    | `[77]` | L2_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[78]` | L2_REMOTE_TRUNK |
    | `[80:79]` | L2_DEST_TYPE |
    | `[79]` | L2_T |
    | `[80]` | L2_VPG_TYPE |
    | `[86:81]` | L2_CLASS_ID |
    | `[85:81]` | L2_MAC_BLOCK_INDEX |
    | `[86]` | L2_DUMMY_INDEX |
    | `[87]` | L2_RPE |
    | `[91:88]` | L2_PRI |
    | `[92]` | L2_PENDING |
    | `[93]` | L2_STATIC_BIT |
    | `[94]` | L2_DST_DISCARD |
    | `[95]` | L2_CPU |
    | `[96]` | L2_SRC_DISCARD |
    | `[97]` | L2_SCP |
    | `[27:1]` | VLAN_KEY |
    | `[15:4]` | VLAN_OVID |
    | `[27:16]` | VLAN_IVID |
    | `[61:47]` | VLAN_DESTINATION_1 |
    | `[59:47]` | VLAN_VPG_1 |
    | `[56:47]` | VLAN_TGID_1 |
    | `[53:47]` | VLAN_PORT_NUM_1 |
    | `[61:54]` | VLAN_MODULE_ID_1 |
    | `[61]` | VLAN_REMOTE_TRUNK_1 |
    | `[63:62]` | VLAN_DEST_TYPE_1 |
    | `[62]` | VLAN_T_1 |
    | `[63]` | VLAN_VPG_TYPE_1 |
    | `[78:64]` | VLAN_DESTINATION |
    | `[76:64]` | VLAN_VPG |
    | `[73:64]` | VLAN_TGID |
    | `[70:64]` | VLAN_PORT_NUM |
    | `[78:71]` | VLAN_MODULE_ID |
    | `[78]` | VLAN_REMOTE_TRUNK |
    | `[80:79]` | VLAN_DEST_TYPE |
    | `[79]` | VLAN_T |
    | `[80]` | VLAN_VPG_TYPE |
    | `[86:81]` | VLAN_CLASS_ID |
    | `[85:81]` | VLAN_MAC_BLOCK_INDEX |
    | `[86]` | VLAN_DUMMY_INDEX |
    | `[87]` | VLAN_RPE |
    | `[91:88]` | VLAN_PRI |
    | `[92]` | VLAN_PENDING |
    | `[93]` | VLAN_STATIC_BIT |
    | `[94]` | VLAN_DST_DISCARD |
    | `[95]` | VLAN_CPU |
    | `[96]` | VLAN_SRC_DISCARD |
    | `[97]` | VLAN_SCP |
    | `[30:1]` | VIF_KEY |
    | `[15:4]` | VIF_NAMESPACE |
    | `[29:16]` | VIF_DST_VIF |
    | `[30]` | VIF_P |
    | `[78:64]` | VIF_DESTINATION |
    | `[76:64]` | VIF_L2MC_PTR |
    | `[76:64]` | VIF_VPG |
    | `[73:64]` | VIF_TGID |
    | `[70:64]` | VIF_PORT_NUM |
    | `[78:71]` | VIF_MODULE_ID |
    | `[78]` | VIF_REMOTE_TRUNK |
    | `[80:79]` | VIF_DEST_TYPE |
    | `[79]` | VIF_T |
    | `[80]` | VIF_VPG_TYPE |
    | `[86:81]` | VIF_CLASS_ID |
    | `[85:81]` | VIF_MAC_BLOCK_INDEX |
    | `[86]` | VIF_DUMMY_INDEX |
    | `[87]` | VIF_RPE |
    | `[91:88]` | VIF_PRI |
    | `[92]` | VIF_PENDING |
    | `[93]` | VIF_STATIC_BIT |
    | `[94]` | VIF_DST_DISCARD |
    | `[95]` | VIF_CPU |
    | `[96]` | VIF_SRC_DISCARD |
    | `[97]` | VIF_SCP |
    | `[15:4]` | TRILL_NONUC_ACCESS_VLAN_ID |
    | `[75:64]` | TRILL_NONUC_ACCESS_L3MC_PTR |
    | `[80:79]` | TRILL_NONUC_ACCESS_DEST_TYPE |
    | `[86:81]` | TRILL_NONUC_ACCESS_CLASS_ID |
    | `[85:81]` | TRILL_NONUC_ACCESS_MAC_BLOCK_INDEX |
    | `[87]` | TRILL_NONUC_ACCESS_RPE |
    | `[91:88]` | TRILL_NONUC_ACCESS_PRI |
    | `[92]` | TRILL_NONUC_ACCESS_PENDING |
    | `[93]` | TRILL_NONUC_ACCESS_STATIC_BIT |
    | `[94]` | TRILL_NONUC_ACCESS_DST_DISCARD |
    | `[95]` | TRILL_NONUC_ACCESS_CPU |
    | `[96]` | TRILL_NONUC_ACCESS_SRC_DISCARD |
    | `[97]` | TRILL_NONUC_ACCESS_SCP |
    | `[15:4]` | TRILL_NONUC_NETWORK_LONG_VLAN_ID |
    | `[67:64]` | TRILL_NONUC_NETWORK_LONG_TREE_ID |
    | `[79:68]` | TRILL_NONUC_NETWORK_LONG_L3MC_INDEX |
    | `[80]` | TRILL_NONUC_NETWORK_LONG_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[82:81]` | TRILL_NONUC_NETWORK_LONG_DEST_TYPE |
    | `[19:1]` | TRILL_NONUC_NETWORK_SHORT_KEY |
    | `[15:4]` | TRILL_NONUC_NETWORK_SHORT_VLAN_ID |
    | `[19:16]` | TRILL_NONUC_NETWORK_SHORT_TREE_ID |
    | `[75:64]` | TRILL_NONUC_NETWORK_SHORT_L3MC_INDEX |
    | `[76]` | TRILL_NONUC_NETWORK_SHORT_TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[78:77]` | TRILL_NONUC_NETWORK_SHORT_DEST_TYPE |
    | `[99]` | EVEN_PARITY |

---

## L3_ENTRY_IPV4_MULTICASTm

- **Base address:** `0x09168000`  ·  **Entries:** 8192  ·  **Entry width:** 22 bytes
- **Function:** L3 routing table IPV4 MULTICAST view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID_0 |
    | `[3:1]` | KEY_TYPE_0 |
    | `[1]` | IPMC_0 |
    | `[2]` | V6_0 |
    | `[3]` | DUMMY_0 |
    | `[77:68]` | IPV4MC_VRF_ID |
    | `[78]` | IPV4MC_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[84:79]` | IPV4MC_CLASS_ID |
    | `[85]` | IPV4MC_DST_DISCARD |
    | `[86]` | EVEN_PARITY_0 |
    | `[87]` | VALID_1 |
    | `[90:88]` | KEY_TYPE_1 |
    | `[88]` | IPMC_1 |
    | `[89]` | V6_1 |
    | `[90]` | DUMMY_1 |
    | `[91]` | IPV4MC_RPE |
    | `[95:92]` | IPV4MC_PRI |
    | `[99:96]` | IPV4MC_RESERVED_1 |
    | `[111:100]` | IPV4MC_L3MC_INDEX |
    | `[172:160]` | IPV4MC_L3_IIF |
    | `[171:160]` | IPV4MC_VLAN_ID |
    | `[172]` | IPV4MC_VLAN_ID_BIT12 |
    | `[173]` | EVEN_PARITY_1 |
    | `[174]` | HIT_0 |
    | `[175]` | HIT_1 |

---

## L3_ENTRY_IPV6_MULTICASTm

- **Base address:** `0x09170000`  ·  **Entries:** 4096  ·  **Entry width:** 44 bytes
- **Function:** L3 routing table IPV6 MULTICAST view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID_0 |
    | `[3:1]` | KEY_TYPE_0 |
    | `[1]` | IPMC_0 |
    | `[2]` | V6_0 |
    | `[3]` | DUMMY_0 |
    | `[77:68]` | IPV6MC_VRF_ID |
    | `[78]` | IPV6MC_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[84:79]` | IPV6MC_CLASS_ID |
    | `[85]` | IPV6MC_DST_DISCARD |
    | `[86]` | EVEN_PARITY_0 |
    | `[87]` | VALID_1 |
    | `[90:88]` | KEY_TYPE_1 |
    | `[88]` | IPMC_1 |
    | `[89]` | V6_1 |
    | `[90]` | DUMMY_1 |
    | `[154:147]` | IPV6MC_RESERVED_3 |
    | `[155]` | IPV6MC_RPE |
    | `[159:156]` | IPV6MC_PRI |
    | `[160]` | IPV6MC_RESERVED_2 |
    | `[172:161]` | IPV6MC_L3MC_INDEX |
    | `[173]` | EVEN_PARITY_1 |
    | `[174]` | VALID_2 |
    | `[177:175]` | KEY_TYPE_2 |
    | `[175]` | IPMC_2 |
    | `[176]` | V6_2 |
    | `[177]` | DUMMY_2 |
    | `[254:242]` | IPV6MC_L3_IIF |
    | `[253:242]` | IPV6MC_VLAN_ID |
    | `[254]` | IPV6MC_VLAN_ID_BIT12 |
    | `[255]` | IPV6MC_IPV6_SIP_LINK_LOCAL_DROP |
    | `[259:256]` | IPV6MC_RESERVED_1 |
    | `[260]` | EVEN_PARITY_2 |
    | `[261]` | VALID_3 |
    | `[264:262]` | KEY_TYPE_3 |
    | `[262]` | IPMC_3 |
    | `[263]` | V6_3 |
    | `[264]` | DUMMY_3 |
    | `[346:329]` | IPV6MC_RESERVED_0 |
    | `[347]` | EVEN_PARITY_3 |
    | `[348]` | HIT_0 |
    | `[349]` | HIT_1 |
    | `[350]` | HIT_2 |
    | `[351]` | HIT_3 |

---

## L3_ENTRY_ONLYm

- **Base address:** `0x09174000`  ·  **Entries:** 16384  ·  **Entry width:** 11 bytes
- **Function:** L3 routing table with fb_regs arch view.  No hit bits

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[1]` | IPMC |
    | `[2]` | V6 |
    | `[3]` | DUMMY |
    | `[45:36]` | IPV4UC_VRF_ID |
    | `[46]` | IPV4UC_RESERVED_2 |
    | `[47]` | IPV4UC_DST_DISCARD |
    | `[53:48]` | IPV4UC_CLASS_ID |
    | `[67]` | IPV4UC_RPE |
    | `[71:68]` | IPV4UC_PRI |
    | `[85:72]` | IPV4UC_NEXT_HOP_INDEX |
    | `[23:1]` | TRILL_KEY |
    | `[19:4]` | TRILL_INGRESS_RBRIDGE_NICKNAME |
    | `[23:20]` | TRILL_TREE_ID |
    | `[30:24]` | TRILL_EXPECTED_PORT_NUM |
    | `[39]` | TRILL_EXPECTED_T |
    | `[86]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[2224]: <VALID=1,NEXT_HOP_INDEX=2,KEY=0x000050080808,IP_ADDR=0xa010101,IPV4UC:NEXT_HOP_INDEX=2,IPV4UC:KEY=0x000050080808,IPV4UC:IP_ADDR=0xa010101,IPV4UC:DATA=0x0008000000,EVEN_PARITY=1,DATA=0x0008000000,>

---

## L3_ENTRY_IPV4_UNICASTm

- **Base address:** `0x09178000`  ·  **Entries:** 16384  ·  **Entry width:** 11 bytes
- **Function:** L3 routing table IPV4 UNICAST view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[3:1]` | KEY_TYPE |
    | `[2]` | V6 |
    | `[3]` | DUMMY |
    | `[45:36]` | IPV4UC_VRF_ID |
    | `[46]` | IPV4UC_RESERVED_2 |
    | `[53:48]` | IPV4UC_CLASS_ID |
    | `[67]` | IPV4UC_RPE |
    | `[71:68]` | IPV4UC_PRI |
    | `[85:72]` | IPV4UC_NEXT_HOP_INDEX |
    | `[23:1]` | TRILL_KEY |
    | `[1]` | IPMC |
    | `[47]` | IPV4UC_DST_DISCARD |
    | `[19:4]` | TRILL_INGRESS_RBRIDGE_NICKNAME |
    | `[23:20]` | TRILL_TREE_ID |
    | `[30:24]` | TRILL_EXPECTED_PORT_NUM |
    | `[39]` | TRILL_EXPECTED_T |
    | `[86]` | EVEN_PARITY |
    | `[87]` | HIT |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[2224]: <VALID=1,NEXT_HOP_INDEX=2,KEY=0x000050080808,IP_ADDR=0xa010101,IPV4UC:NEXT_HOP_INDEX=2,IPV4UC:KEY=0x000050080808,IPV4UC:IP_ADDR=0xa010101,IPV4UC:DATA=0x0008000000,EVEN_PARITY=1,DATA=0x0008000000,>

---

## L3_ENTRY_IPV6_UNICASTm

- **Base address:** `0x0917c000`  ·  **Entries:** 8192  ·  **Entry width:** 22 bytes
- **Function:** L3 routing table IPV6 UNICAST view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID_0 |
    | `[3:1]` | KEY_TYPE_0 |
    | `[1]` | IPMC_0 |
    | `[2]` | V6_0 |
    | `[3]` | DUMMY_0 |
    | `[77:68]` | IPV6UC_VRF_ID |
    | `[85:78]` | IPV6UC_DATA_0 |
    | `[78]` | IPV6UC_RPE |
    | `[84:79]` | IPV6UC_CLASS_ID |
    | `[85]` | IPV6UC_DST_DISCARD |
    | `[86]` | EVEN_PARITY_0 |
    | `[87]` | VALID_1 |
    | `[90:88]` | KEY_TYPE_1 |
    | `[88]` | IPMC_1 |
    | `[89]` | V6_1 |
    | `[90]` | DUMMY_1 |
    | `[158:155]` | IPV6UC_PRI |
    | `[173]` | EVEN_PARITY_1 |
    | `[174]` | HIT_0 |
    | `[175]` | HIT_1 |

---

## L3_DEFIP_ONLYm

- **Base address:** `0x0a162000`  ·  **Entries:** 8192  ·  **Entry width:** 23 bytes
- **Function:** L3 Default IP Route (LPM) TCAM only view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID0 |
    | `[1]` | VALID1 |
    | `[2]` | MODE0 |
    | `[44:35]` | VRF_ID_0 |
    | `[45]` | RESERVED_3 |
    | `[46]` | MODE1 |
    | `[88:79]` | VRF_ID_1 |
    | `[89]` | RESERVED_2 |
    | `[90]` | MODE_MASK0 |
    | `[133]` | RESERVED_1 |
    | `[134]` | MODE_MASK1 |
    | `[176:167]` | VRF_ID_MASK1 |
    | `[177]` | RESERVED_0 |

**Live capture (Cumulus):** 25 entries populated. Sample:

    ipipe0[512]: <VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,MODE_MASK1=1,MODE_MASK0=1,MODE1=1,MODE0=1,MASK1=0x07ffffffffff,MASK0=0x07ffffffffff,KEY1=0x0001fd000001,KEY0=0x000000000001,IP_ADDR_MASK1=0xffffffff,IP_ADDR_MASK0=0xffffffff,IP_ADDR1=0xfe800000,>

---

## L3_DEFIP_128_ONLYm

- **Base address:** `0x0a168000`  ·  **Entries:** 256  ·  **Entry width:** 36 bytes
- **Function:** L3 Default IP Route (LPM) TCAM only view. FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID_0 |
    | `[1]` | VALID_1 |
    | `[139:130]` | VRF_ID |
    | `[141:140]` | RESERVED_0 |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[0]: <VALID_1=1,VALID_0=1,MASK=0x03ffffffffffffffffffffffffffffffffff,KEY=0x0000fe800000000000000000000000000000,IP_ADDR=0xfe800000000000000000000000000000>

---

## RTAG7_FLOW_BASED_HASHm

- **Base address:** `0x0a16c000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** RTAG7 Flow-based Hash table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL_ECMP |
    | `[6:3]` | OFFSET_ECMP |
    | `[7]` | EVEN_PARITY |

**Live capture (Cumulus):** 252 entries populated. Sample:

    ipipe0[1]: <OFFSET_ECMP=1,>

---

## L3_DEFIPm

- **Base address:** `0x0a170000`  ·  **Entries:** 8192  ·  **Entry width:** 30 bytes
- **Function:** L3 Default IP Route (LPM) TCAM view with data and hit bits

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID0 |
    | `[1]` | VALID1 |
    | `[2]` | MODE0 |
    | `[44:35]` | VRF_ID_0 |
    | `[45]` | RESERVED_5 |
    | `[46]` | MODE1 |
    | `[88:79]` | VRF_ID_1 |
    | `[89]` | RESERVED_4 |
    | `[90]` | MODE_MASK0 |
    | `[133]` | RESERVED_3 |
    | `[134]` | MODE_MASK1 |
    | `[176:167]` | VRF_ID_MASK1 |
    | `[177]` | RESERVED_2 |
    | `[178]` | ECMP1 |
    | `[188:179]` | ECMP_PTR1 |
    | `[196:193]` | PRI1 |
    | `[197]` | DEFAULTROUTE1 |
    | `[197]` | RPE1 |
    | `[198]` | DST_DISCARD1 |
    | `[198]` | SRC_DISCARD1 |
    | `[204:199]` | CLASS_ID1 |
    | `[205]` | GLOBAL_ROUTE1 |
    | `[206]` | ECMP0 |
    | `[220:207]` | NEXT_HOP_INDEX0 |
    | `[216:207]` | ECMP_PTR0 |
    | `[220:217]` | RESERVED_ECMP_PTR0 |
    | `[225]` | DEFAULTROUTE0 |
    | `[225]` | RPE0 |
    | `[226]` | DST_DISCARD0 |
    | `[226]` | SRC_DISCARD0 |
    | `[232:227]` | CLASS_ID0 |
    | `[233]` | GLOBAL_ROUTE0 |
    | `[234]` | EVEN_PARITY |
    | `[235]` | HIT0 |
    | `[236]` | HIT1 |

**Live capture (Cumulus):** 25 entries populated. Sample:

    ipipe0[512]: <VRF_ID_MASK1=0x3ff,VRF_ID_MASK0=0x3ff,VALID1=1,VALID0=1,NEXT_HOP_INDEX1=2,NEXT_HOP_INDEX0=2,MODE_MASK1=1,MODE_MASK0=1,MODE1=1,MODE0=1,MASK1=0x07ffffffffff,MASK0=0x07ffffffffff,KEY1=0x0001fd000001,KEY0=0x000000000001,IP_ADDR_MASK1=0xffffffff,IP_ADDR_MASK0=0xffffffff,IP_ADDR1=0xfe800000,ECMP_PTR1=2,ECMP_PTR0=2,>

---

## L3_DEFIP_DATA_ONLYm

- **Base address:** `0x0a174000`  ·  **Entries:** 8192  ·  **Entry width:** 8 bytes
- **Function:** L3 Default IP Route (LPM) Data SRAM for the L3_DEFIP TCAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECMP1 |
    | `[14:1]` | NEXT_HOP_INDEX1 |
    | `[10:1]` | ECMP_PTR1 |
    | `[14:11]` | RESERVED_ECMP_PTR1 |
    | `[18:15]` | PRI1 |
    | `[19]` | DEFAULTROUTE1 |
    | `[19]` | RPE1 |
    | `[20]` | DST_DISCARD1 |
    | `[20]` | SRC_DISCARD1 |
    | `[26:21]` | CLASS_ID1 |
    | `[27]` | GLOBAL_ROUTE1 |
    | `[28]` | ECMP0 |
    | `[42:39]` | RESERVED_ECMP_PTR0 |
    | `[46:43]` | PRI0 |
    | `[47]` | DEFAULTROUTE0 |
    | `[47]` | RPE0 |
    | `[48]` | DST_DISCARD0 |
    | `[48]` | SRC_DISCARD0 |
    | `[54:49]` | CLASS_ID0 |
    | `[55]` | GLOBAL_ROUTE0 |
    | `[56]` | EVEN_PARITY |

**Live capture (Cumulus):** 28 entries populated. Sample:

    ipipe0[512]: <NEXT_HOP_INDEX1=2,NEXT_HOP_INDEX0=2,ECMP_PTR1=2,ECMP_PTR0=2,>

---

## L3_DEFIP_128m

- **Base address:** `0x0a176000`  ·  **Entries:** 256  ·  **Entry width:** 39 bytes
- **Function:** L3 Default IP Route (LPM) TCAM view with data and hit bits. FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID_0 |
    | `[1]` | VALID_1 |
    | `[139:130]` | VRF_ID |
    | `[141:140]` | RESERVED_2 |
    | `[279:270]` | VRF_ID_MASK |
    | `[281:280]` | RESERVED_1 |
    | `[282]` | ECMP |
    | `[296:293]` | RESERVED_ECMP_PTR |
    | `[300:297]` | PRI |
    | `[301]` | DEFAULTROUTE |
    | `[301]` | RPE |
    | `[302]` | DST_DISCARD |
    | `[302]` | SRC_DISCARD |
    | `[308:303]` | CLASS_ID |
    | `[309]` | GLOBAL_ROUTE |
    | `[310]` | EVEN_PARITY |
    | `[311]` | HIT |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[0]: <VRF_ID_MASK=0x3ff,VALID_1=1,VALID_0=1,NEXT_HOP_INDEX=2,MASK=0x03ffffffffffffffffffffffffffffffffff,KEY=0x0000fe800000000000000000000000000000,IP_ADDR_MASK=0xffffffffffffffffffffffffffffffff,IP_ADDR=0xfe800000000000000000000000000000,ECMP_PTR=2,CLASS_ID=2>

---

## L3_DEFIP_128_DATA_ONLYm

- **Base address:** `0x0a17a000`  ·  **Entries:** 256  ·  **Entry width:** 4 bytes
- **Function:** L3 Default IP Route (LPM) Data SRAM for the L3_DEFIP_128 TCAM. FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECMP |
    | `[14:1]` | NEXT_HOP_INDEX |
    | `[10:1]` | ECMP_PTR |
    | `[14:11]` | RESERVED_ECMP_PTR |
    | `[18:15]` | PRI |
    | `[19]` | DEFAULTROUTE |
    | `[19]` | RPE |
    | `[20]` | DST_DISCARD |
    | `[20]` | SRC_DISCARD |
    | `[26:21]` | CLASS_ID |
    | `[27]` | GLOBAL_ROUTE |
    | `[28]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[0]: <NEXT_HOP_INDEX=2,ECMP_PTR=2,CLASS_ID=2>

---

## INITIAL_PROT_GROUP_TABLEm

- **Base address:** `0x0b168000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Protection Switching (backup path) Next Hop Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | STATUS |

---

## TRUNK_CBL_TABLEm

- **Base address:** `0x0b16e000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Trunk (LAG) Class Based Learning Attribute Table for class based station movement. Direct index table, address = TGID[6:0]

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PORT_LEARNING_CLASS |

---

## L3_IPMC_1m

- **Base address:** `0x0b170000`  ·  **Entries:** 4096  ·  **Entry width:** 3 bytes
- **Function:** L3 IPMC Table (for source properties)

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TGID |
    | `[6:0]` | PORT_NUM |
    | `[14:7]` | MODULE_ID |
    | `[15]` | T |
    | `[16]` | EVEN_PARITY |

---

## PORT_CBL_TABLE_MODBASEm

- **Base address:** `0x0b17a000`  ·  **Entries:** 256  ·  **Entry width:** 2 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | BASE |
    | `[12]` | EVEN_PARITY |

---

## PORT_CBL_TABLEm

- **Base address:** `0x0b17c000`  ·  **Entries:** 8192  ·  **Entry width:** 1 bytes
- **Function:** Port Class Based Learning Attribute Table for class based station movement. Direct index table, address = {mod[6:0], port[5:0]} or address = virtual_port_num

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PORT_LEARNING_CLASS |
    | `[3:2]` | VIRTUAL_PORT_LEARNING_CLASS |
    | `[4]` | EVEN_PARITY |

---

## L3_ENTRY_HIT_ONLY_Xm

- **Base address:** `0x0c122000`  ·  **Entries:** 1024  ·  **Entry width:** 2 bytes
- **Function:** L3 Hit bit table, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT_0 |
    | `[1]` | HIT_1 |
    | `[2]` | HIT_2 |
    | `[3]` | HIT_3 |
    | `[4]` | HIT_4 |
    | `[5]` | HIT_5 |
    | `[6]` | HIT_6 |
    | `[7]` | HIT_7 |
    | `[8]` | HIT_8 |
    | `[9]` | HIT_9 |
    | `[10]` | HIT_10 |
    | `[11]` | HIT_11 |
    | `[12]` | HIT_12 |
    | `[13]` | HIT_13 |
    | `[14]` | HIT_14 |
    | `[15]` | HIT_15 |

---

## L3_DEFIP_HIT_ONLY_Xm

- **Base address:** `0x0c124000`  ·  **Entries:** 8192  ·  **Entry width:** 1 bytes
- **Function:** L3_DEFIP Hit bit table, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT0 |
    | `[1]` | HIT1 |

---

## L3_ENTRY_HIT_ONLY_Ym

- **Base address:** `0x0c142000`  ·  **Entries:** 1024  ·  **Entry width:** 2 bytes
- **Function:** L3 Hit bit table, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT_0 |
    | `[1]` | HIT_1 |
    | `[2]` | HIT_2 |
    | `[3]` | HIT_3 |
    | `[4]` | HIT_4 |
    | `[5]` | HIT_5 |
    | `[6]` | HIT_6 |
    | `[7]` | HIT_7 |
    | `[8]` | HIT_8 |
    | `[9]` | HIT_9 |
    | `[10]` | HIT_10 |
    | `[11]` | HIT_11 |
    | `[12]` | HIT_12 |
    | `[13]` | HIT_13 |
    | `[14]` | HIT_14 |
    | `[15]` | HIT_15 |

---

## L3_DEFIP_HIT_ONLY_Ym

- **Base address:** `0x0c144000`  ·  **Entries:** 8192  ·  **Entry width:** 1 bytes
- **Function:** L3_DEFIP Hit bit table, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT0 |
    | `[1]` | HIT1 |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[2562]: <HIT1=1,>

---

## FP_PORT_FIELD_SELm

- **Base address:** `0x0c160000`  ·  **Entries:** 128  ·  **Entry width:** 22 bytes
- **Function:** FIELD SELECT VALUE FOR EACH SLICE IN THE FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | SLICE0_F1 |
    | `[7:4]` | SLICE0_F2 |
    | `[11:8]` | SLICE0_F3 |
    | `[15:12]` | SLICE1_F1 |
    | `[19:16]` | SLICE1_F2 |
    | `[23:20]` | SLICE1_F3 |
    | `[27:24]` | SLICE2_F1 |
    | `[31:28]` | SLICE2_F2 |
    | `[35:32]` | SLICE2_F3 |
    | `[39:36]` | SLICE3_F1 |
    | `[43:40]` | SLICE3_F2 |
    | `[47:44]` | SLICE3_F3 |
    | `[51:48]` | SLICE4_F1 |
    | `[55:52]` | SLICE4_F2 |
    | `[59:56]` | SLICE4_F3 |
    | `[63:60]` | SLICE5_F1 |
    | `[67:64]` | SLICE5_F2 |
    | `[71:68]` | SLICE5_F3 |
    | `[75:72]` | SLICE6_F1 |
    | `[79:76]` | SLICE6_F2 |
    | `[83:80]` | SLICE6_F3 |
    | `[87:84]` | SLICE7_F1 |
    | `[91:88]` | SLICE7_F2 |
    | `[95:92]` | SLICE7_F3 |
    | `[99:96]` | SLICE8_F1 |
    | `[103:100]` | SLICE8_F2 |
    | `[107:104]` | SLICE8_F3 |
    | `[111:108]` | SLICE9_F1 |
    | `[115:112]` | SLICE9_F2 |
    | `[119:116]` | SLICE9_F3 |
    | `[122:120]` | SLICE0_D_TYPE_SEL |
    | `[125:123]` | SLICE1_D_TYPE_SEL |
    | `[131:129]` | SLICE3_D_TYPE_SEL |
    | `[134:132]` | SLICE4_D_TYPE_SEL |
    | `[137:135]` | SLICE5_D_TYPE_SEL |
    | `[140:138]` | SLICE6_D_TYPE_SEL |
    | `[143:141]` | SLICE7_D_TYPE_SEL |
    | `[146:144]` | SLICE8_D_TYPE_SEL |
    | `[149:147]` | SLICE9_D_TYPE_SEL |
    | `[151:150]` | SLICE0_S_TYPE_SEL |
    | `[153:152]` | SLICE1_S_TYPE_SEL |
    | `[155:154]` | SLICE2_S_TYPE_SEL |
    | `[157:156]` | SLICE3_S_TYPE_SEL |
    | `[159:158]` | SLICE4_S_TYPE_SEL |
    | `[161:160]` | SLICE5_S_TYPE_SEL |
    | `[163:162]` | SLICE6_S_TYPE_SEL |
    | `[165:164]` | SLICE7_S_TYPE_SEL |
    | `[167:166]` | SLICE8_S_TYPE_SEL |
    | `[169:168]` | SLICE9_S_TYPE_SEL |
    | `[170]` | SLICE1_0_PAIRING |
    | `[171]` | SLICE3_2_PAIRING |
    | `[172]` | SLICE5_4_PAIRING |
    | `[173]` | SLICE7_6_PAIRING |
    | `[174]` | SLICE9_8_PAIRING |
    | `[175]` | EVEN_PARITY |

**Live capture (Cumulus):** 54 entries populated. Sample:

    ipipe0[0]: <SLICE9_F3=0xa,SLICE9_F2=5,SLICE9_F1=0xc,SLICE9_8_PAIRING=1,SLICE8_F3=7,SLICE8_F2=1,SLICE8_F1=5,SLICE3_F3=6,SLICE3_F2=3,SLICE3_F1=0xa,SLICE3_2_PAIRING=1,SLICE2_F3=7,SLICE2_F2=2,SLICE2_F1=0xc,>

---

## TCP_FNm

- **Base address:** `0x0c166000`  ·  **Entries:** 64  ·  **Entry width:** 2 bytes
- **Function:** TCP function table to map TCP Flags to any value for an IFP key, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | FN0 |
    | `[11:6]` | FN1 |

**Live capture (Cumulus):** 63 entries populated. Sample:

    ipipe0[1]: <FN1=1,FN0=1>

---

## TTL_FNm

- **Base address:** `0x0c168000`  ·  **Entries:** 256  ·  **Entry width:** 3 bytes
- **Function:** TTL FUNCTION TABLE FOR IFP, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | FN0 |
    | `[15:8]` | FN1 |
    | `[16]` | EVEN_PARITY |

**Live capture (Cumulus):** 255 entries populated. Sample:

    ipipe0[1]: <FN1=1,FN0=1,>

---

## TOS_FNm

- **Base address:** `0x0c16a000`  ·  **Entries:** 256  ·  **Entry width:** 3 bytes
- **Function:** TOS FUNCTION TABLE FOR IFP, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | FN0 |
    | `[15:8]` | FN1 |
    | `[16]` | EVEN_PARITY |

**Live capture (Cumulus):** 255 entries populated. Sample:

    ipipe0[1]: <FN1=1,FN0=1,>

---

## L3_DEFIP_128_HIT_ONLYm

- **Base address:** `0x0c16c000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** L3_DEFIP Hit bit table, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT |

---

## DSCP_TABLEm

- **Base address:** `0x0c16e000`  ·  **Entries:** 8192  ·  **Entry width:** 2 bytes
- **Function:** Diff Serv Code Point Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | DSCP |
    | `[9:6]` | PRI |
    | `[11:10]` | CNG |
    | `[12]` | EVEN_PARITY |

---

## ING_PRI_CNG_MAPm

- **Base address:** `0x0c170000`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** Per port ingress priority/CFI mapping table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | CNG |
    | `[5:2]` | PRI |
    | `[6]` | EVEN_PARITY |

**Live capture (Cumulus):** 14 entries populated. Sample:

    ipipe0[2]: <PRI=1,>

---

## ING_UNTAGGED_PHBm

- **Base address:** `0x0c172000`  ·  **Entries:** 64  ·  **Entry width:** 1 bytes
- **Function:** Table used to derive untagged packet's PHB.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | CNG |
    | `[5:2]` | PRI |
    | `[6]` | EVEN_PARITY |

---

## L3_ENTRY_HIT_ONLYm

- **Base address:** `0x0c1c2000`  ·  **Entries:** 1024  ·  **Entry width:** 2 bytes
- **Function:** L3 Hit bit table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT_0 |
    | `[1]` | HIT_1 |
    | `[2]` | HIT_2 |
    | `[3]` | HIT_3 |
    | `[4]` | HIT_4 |
    | `[5]` | HIT_5 |
    | `[6]` | HIT_6 |
    | `[7]` | HIT_7 |
    | `[8]` | HIT_8 |
    | `[9]` | HIT_9 |
    | `[10]` | HIT_10 |
    | `[11]` | HIT_11 |
    | `[12]` | HIT_12 |
    | `[13]` | HIT_13 |
    | `[14]` | HIT_14 |
    | `[15]` | HIT_15 |

---

## L3_DEFIP_HIT_ONLYm

- **Base address:** `0x0c1c4000`  ·  **Entries:** 8192  ·  **Entry width:** 1 bytes
- **Function:** L3_DEFIP Hit bit table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIT0 |
    | `[1]` | HIT1 |

---

## FP_METER_TABLEm

- **Base address:** `0x0d128000`  ·  **Entries:** 2048  ·  **Entry width:** 9 bytes
- **Function:** METER TABLE STRUCTURES FOR THE FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[60:42]` | REFRESHCOUNT |
    | `[62:61]` | REFRESH_MODE |
    | `[66]` | PKTS_BYTES |
    | `[67]` | EVEN_PARITY |

**Live capture (Cumulus):** 18 entries populated. Sample:

    ipipe0[0]: <REFRESHCOUNT=0x7d0,PKTS_BYTES=1,BUCKETSIZE=0xf43,BUCKETCOUNT=0xf430000>

---

## FP_COUNTER_TABLE_Xm

- **Base address:** `0x0d12a000`  ·  **Entries:** 2048  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE FP in IPX. FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## FP_GLOBAL_MASK_TCAM_Xm

- **Base address:** `0x0d12e000`  ·  **Entries:** 2048  ·  **Entry width:** 17 bytes
- **Function:** IPB view of the IFP_TCAM.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <VALID=1,MASK=0x00000001fffffffe01,KEY=0x00000001fffffffe01,IPBM_MASK=0x00000001fffffffe01,IPBM=0x00000001fffffffe01>

---

## FP_STORM_CONTROL_METERS_Xm

- **Base address:** `0x0d130000`  ·  **Entries:** 264  ·  **Entry width:** 7 bytes
- **Function:** STORM CONTROL METER TABLE STRUCTURES FOR THE FP, FeatureSpecific-FP.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[51:33]` | REFRESHCOUNT |
    | `[52]` | METER_SPARE |
    | `[53]` | EVEN_PARITY |

---

## FP_COUNTER_TABLE_Ym

- **Base address:** `0x0d14a000`  ·  **Entries:** 2048  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE FP in IPY. FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[1540]: <PACKET_COUNTER=0x8eb,EVEN_PARITY=1,BYTE_COUNTER=0x000003300a>

---

## FP_GLOBAL_MASK_TCAM_Ym

- **Base address:** `0x0d14e000`  ·  **Entries:** 2048  ·  **Entry width:** 17 bytes
- **Function:** IPB view of the IFP_TCAM.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <VALID=1,MASK=0x02001ffe00000001fe,KEY=0x00001ffe00000001fe,IPBM_MASK=0x02001ffe00000001fe,IPBM=0x00001ffe00000001fe>

---

## FP_STORM_CONTROL_METERS_Ym

- **Base address:** `0x0d150000`  ·  **Entries:** 264  ·  **Entry width:** 7 bytes
- **Function:** STORM CONTROL METER TABLE STRUCTURES FOR THE FP, FeatureSpecific-FP.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[51:33]` | REFRESHCOUNT |
    | `[52]` | METER_SPARE |
    | `[53]` | EVEN_PARITY |

---

## FP_RANGE_CHECKm

- **Base address:** `0x0d160000`  ·  **Entries:** 32  ·  **Entry width:** 5 bytes
- **Function:** RANGE CHECK VALUES FOR FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | LOWER_BOUNDS |
    | `[31:16]` | UPPER_BOUNDS |
    | `[33:32]` | FIELD_SELECT |
    | `[34]` | ENABLE |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[0]: <UPPER_BOUNDS=0x223,LOWER_BOUNDS=0x222,FIELD_SELECT=1,ENABLE=1>

---

## FP_TCAMm

- **Base address:** `0x0d162000`  ·  **Entries:** 2048  ·  **Entry width:** 59 bytes
- **Function:** TCAM FOR FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | VALID |
    | `[8:2]` | F4 |
    | `[8:2]` | PAIRING_F4 |
    | `[217:215]` | RESERVED_SINGLE_WIDE |
    | `[216:215]` | PAIRING_RESERVED |
    | `[242:236]` | F4_MASK |
    | `[242:236]` | PAIRING_F4_MASK |
    | `[451:449]` | RESERVED_SINGLE_WIDE_MASK |
    | `[450:449]` | PAIRING_RESERVED_MASK |
    | `[469:451]` | PAIRING_FIXED_MASK |
    | `[469:452]` | FIXED_MASK |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <VALID=3,PAIRING_FIXED_MASK=0x600,PAIRING_FIXED=0x200,PAIRING_F2_MASK=0xff000000000000000000000000000000,PAIRING_F2=0xff000000000000000000000000000000,MASK=0x00030000000000003fc00000000000000000000000000000000000000000,KEY=0x00010000000000003fc00000000000000000000000000000000000000000,FIXED_MASK=0x300,FIXED=0x100,F2_MASK=0xff000000000000000000000000000000,F2=0xff000000000000000000000000000000,>

---

## FP_SLICE_MAPm

- **Base address:** `0x0d164000`  ·  **Entries:** 1  ·  **Entry width:** 10 bytes
- **Function:** SLICE MAPPING CONTROLS FOR IFP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | VIRTUAL_SLICE_0_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[7:4]` | VIRTUAL_SLICE_1_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[11:8]` | VIRTUAL_SLICE_2_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[15:12]` | VIRTUAL_SLICE_3_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[19:16]` | VIRTUAL_SLICE_4_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[23:20]` | VIRTUAL_SLICE_5_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[27:24]` | VIRTUAL_SLICE_6_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[31:28]` | VIRTUAL_SLICE_7_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[35:32]` | VIRTUAL_SLICE_8_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[39:36]` | VIRTUAL_SLICE_9_PHYSICAL_SLICE_NUMBER_ENTRY_0 |
    | `[43:40]` | VIRTUAL_SLICE_0_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[47:44]` | VIRTUAL_SLICE_1_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[51:48]` | VIRTUAL_SLICE_2_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[55:52]` | VIRTUAL_SLICE_3_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[59:56]` | VIRTUAL_SLICE_4_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[63:60]` | VIRTUAL_SLICE_5_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[67:64]` | VIRTUAL_SLICE_6_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[71:68]` | VIRTUAL_SLICE_7_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[75:72]` | VIRTUAL_SLICE_8_VIRTUAL_SLICE_GROUP_ENTRY_0 |
    | `[79:76]` | VIRTUAL_SLICE_9_VIRTUAL_SLICE_GROUP_ENTRY_0 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <VIRTUAL_SLICE_9_VIRTUAL_SLICE_GROUP_ENTRY_0=9,VIRTUAL_SLICE_9_PHYSICAL_SLICE_NUMBER_ENTRY_0=7,VIRTUAL_SLICE_8_VIRTUAL_SLICE_GROUP_ENTRY_0=8,VIRTUAL_SLICE_8_PHYSICAL_SLICE_NUMBER_ENTRY_0=6,VIRTUAL_SLICE_7_VIRTUAL_SLICE_GROUP_ENTRY_0=7,VIRTUAL_SLICE_7_PHYSICAL_SLICE_NUMBER_ENTRY_0=5,VIRTUAL_SLICE_6_VIRTUAL_SLICE_GROUP_ENTRY_0=6,VIRTUAL_SLICE_6_PHYSICAL_SLICE_NUMBER_ENTRY_0=4,VIRTUAL_SLICE_5_VIRTUAL_SLICE_GROUP_ENTRY_0=5,VIRTUAL_SLICE_5_PHYSICAL_SLICE_NUMBER_ENTRY_0=1,VIRTUAL_SLICE_4_VIRTUAL_SLICE_GROUP_ENTRY_0=4,VIRTUAL_SLICE_3_VIRTUAL_SLICE_GROUP_ENTRY_0=3,VIRTUAL_SLICE_3_PHYSICAL_SLICE_NUMBER_ENTRY_0=9,VIRTUAL_SLICE_2_VIRTUAL_SLICE_GROUP_ENTRY_0=2,VIRTUAL_SLICE_2_PHYSICAL_SLICE_NUMBER_ENTRY_0=8,VIRTUAL_SLICE_1_VIRTUAL_SLICE_GROUP_ENTRY_0=1,VIRTUAL_SLICE_1_PHYSICAL_SLICE_NUMBER_ENTRY_0=3,VIRTUAL_SLICE_0_PHYSICAL_SLICE_NUMBER_ENTRY_0=2>

---

## FP_GLOBAL_MASK_TCAMm

- **Base address:** `0x0d16e000`  ·  **Entries:** 2048  ·  **Entry width:** 17 bytes
- **Function:** PORT BITMAP TCAM ENTRY FOR EACH IFP_TCAM ENTRY.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <VALID=1,MASK=0x02001fffffffffffff,KEY=0x00001fffffffffffff,IPBM_MASK=0x02001fffffffffffff,IPBM=0x00001fffffffffffff>

---

## FP_SLICE_KEY_CONTROLm

- **Base address:** `0x0d172000`  ·  **Entries:** 1  ·  **Entry width:** 18 bytes
- **Function:** SLICE KEY GENERATION CONTROLS FOR IFP, FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SLICE_0_SRC_CLASS_ID_SEL |
    | `[3:2]` | SLICE_0_DST_CLASS_ID_SEL |
    | `[5:4]` | SLICE_0_INTERFACE_CLASS_ID_SEL |
    | `[6]` | SLICE_0_TOS_FN_SEL |
    | `[7]` | SLICE_0_TCP_FN_SEL |
    | `[8]` | SLICE_0_TTL_FN_SEL |
    | `[10:9]` | SLICE_1_SRC_CLASS_ID_SEL |
    | `[12:11]` | SLICE_1_DST_CLASS_ID_SEL |
    | `[14:13]` | SLICE_1_INTERFACE_CLASS_ID_SEL |
    | `[15]` | SLICE_1_TOS_FN_SEL |
    | `[16]` | SLICE_1_TCP_FN_SEL |
    | `[17]` | SLICE_1_TTL_FN_SEL |
    | `[19:18]` | SLICE_2_SRC_CLASS_ID_SEL |
    | `[21:20]` | SLICE_2_DST_CLASS_ID_SEL |
    | `[23:22]` | SLICE_2_INTERFACE_CLASS_ID_SEL |
    | `[24]` | SLICE_2_TOS_FN_SEL |
    | `[25]` | SLICE_2_TCP_FN_SEL |
    | `[26]` | SLICE_2_TTL_FN_SEL |
    | `[28:27]` | SLICE_3_SRC_CLASS_ID_SEL |
    | `[30:29]` | SLICE_3_DST_CLASS_ID_SEL |
    | `[33]` | SLICE_3_TOS_FN_SEL |
    | `[34]` | SLICE_3_TCP_FN_SEL |
    | `[35]` | SLICE_3_TTL_FN_SEL |
    | `[37:36]` | SLICE_4_SRC_CLASS_ID_SEL |
    | `[39:38]` | SLICE_4_DST_CLASS_ID_SEL |
    | `[41:40]` | SLICE_4_INTERFACE_CLASS_ID_SEL |
    | `[42]` | SLICE_4_TOS_FN_SEL |
    | `[43]` | SLICE_4_TCP_FN_SEL |
    | `[44]` | SLICE_4_TTL_FN_SEL |
    | `[46:45]` | SLICE_5_SRC_CLASS_ID_SEL |
    | `[48:47]` | SLICE_5_DST_CLASS_ID_SEL |
    | `[50:49]` | SLICE_5_INTERFACE_CLASS_ID_SEL |
    | `[51]` | SLICE_5_TOS_FN_SEL |
    | `[52]` | SLICE_5_TCP_FN_SEL |
    | `[53]` | SLICE_5_TTL_FN_SEL |
    | `[55:54]` | SLICE_6_SRC_CLASS_ID_SEL |
    | `[57:56]` | SLICE_6_DST_CLASS_ID_SEL |
    | `[59:58]` | SLICE_6_INTERFACE_CLASS_ID_SEL |
    | `[60]` | SLICE_6_TOS_FN_SEL |
    | `[61]` | SLICE_6_TCP_FN_SEL |
    | `[62]` | SLICE_6_TTL_FN_SEL |
    | `[66:65]` | SLICE_7_DST_CLASS_ID_SEL |
    | `[68:67]` | SLICE_7_INTERFACE_CLASS_ID_SEL |
    | `[69]` | SLICE_7_TOS_FN_SEL |
    | `[70]` | SLICE_7_TCP_FN_SEL |
    | `[71]` | SLICE_7_TTL_FN_SEL |
    | `[73:72]` | SLICE_8_SRC_CLASS_ID_SEL |
    | `[75:74]` | SLICE_8_DST_CLASS_ID_SEL |
    | `[77:76]` | SLICE_8_INTERFACE_CLASS_ID_SEL |
    | `[78]` | SLICE_8_TOS_FN_SEL |
    | `[79]` | SLICE_8_TCP_FN_SEL |
    | `[80]` | SLICE_8_TTL_FN_SEL |
    | `[82:81]` | SLICE_9_SRC_CLASS_ID_SEL |
    | `[84:83]` | SLICE_9_DST_CLASS_ID_SEL |
    | `[86:85]` | SLICE_9_INTERFACE_CLASS_ID_SEL |
    | `[87]` | SLICE_9_TOS_FN_SEL |
    | `[88]` | SLICE_9_TCP_FN_SEL |
    | `[89]` | SLICE_9_TTL_FN_SEL |
    | `[90]` | SLICE0_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[91]` | SLICE1_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[92]` | SLICE2_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[93]` | SLICE3_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[94]` | SLICE4_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[95]` | SLICE5_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[96]` | SLICE6_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[97]` | SLICE7_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[98]` | SLICE8_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[99]` | SLICE9_RANGE_CHECKER_OR_UDF_CHUNK_VALID_SEL |
    | `[101:100]` | SLICE0_AUX_TAG_1_SEL |
    | `[103:102]` | SLICE1_AUX_TAG_1_SEL |
    | `[105:104]` | SLICE2_AUX_TAG_1_SEL |
    | `[107:106]` | SLICE3_AUX_TAG_1_SEL |
    | `[109:108]` | SLICE4_AUX_TAG_1_SEL |
    | `[111:110]` | SLICE5_AUX_TAG_1_SEL |
    | `[113:112]` | SLICE6_AUX_TAG_1_SEL |
    | `[115:114]` | SLICE7_AUX_TAG_1_SEL |
    | `[117:116]` | SLICE8_AUX_TAG_1_SEL |
    | `[119:118]` | SLICE9_AUX_TAG_1_SEL |
    | `[121:120]` | SLICE0_AUX_TAG_2_SEL |
    | `[123:122]` | SLICE1_AUX_TAG_2_SEL |
    | `[125:124]` | SLICE2_AUX_TAG_2_SEL |
    | `[127:126]` | SLICE3_AUX_TAG_2_SEL |
    | `[129:128]` | SLICE4_AUX_TAG_2_SEL |
    | `[131:130]` | SLICE5_AUX_TAG_2_SEL |
    | `[133:132]` | SLICE6_AUX_TAG_2_SEL |
    | `[135:134]` | SLICE7_AUX_TAG_2_SEL |
    | `[137:136]` | SLICE8_AUX_TAG_2_SEL |
    | `[139:138]` | SLICE9_AUX_TAG_2_SEL |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <SLICE_9_DST_CLASS_ID_SEL=1,SLICE_2_DST_CLASS_ID_SEL=1,>

---

## FP_PORT_METER_MAPm

- **Base address:** `0x0d174000`  ·  **Entries:** 66  ·  **Entry width:** 3 bytes
- **Function:** FP_PORT_METER_MAP TABLE STRUCTURES FOR THE FP, FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | VALUE |
    | `[15:8]` | MASK |
    | `[22:16]` | NH_OFFSET |

---

## FP_GM_FIELDSm

- **Base address:** `0x0d176000`  ·  **Entries:** 2048  ·  **Entry width:** 10 bytes
- **Function:** Fields view of IFP_GM TCAM.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <VALID=1,MASK_X=0x1fffffffff,MASK=0x1fffffffff,KEY_X=0x1fffffffe1,KEY=0x1fffffffe1>

---

## ING_DVP_2_TABLEm

- **Base address:** `0x0d17a000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** Used to generate an ECMP_Group/NHI from the DVP value and other DVP properties.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[9:0]` | ECMP_PTR |
    | `[14]` | ECMP |
    | `[16:15]` | VP_TYPE |
    | `[17]` | NETWORK_PORT |
    | `[18]` | EVEN_PARITY |

---

## FP_POLICY_TABLEm

- **Base address:** `0x0d17c000`  ·  **Entries:** 2048  ·  **Entry width:** 30 bytes
- **Function:** POLICY TABLE FOR DETERMINING ACTIONS IN THE FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | MTP_INDEX0 |
    | `[3:2]` | MTP_INDEX1 |
    | `[5:4]` | MTP_INDEX2 |
    | `[7:6]` | MTP_INDEX3 |
    | `[11:8]` | MIRROR |
    | `[12]` | MIRROR_OVERRIDE |
    | `[14:13]` | R_DROP_PRECEDENCE |
    | `[16:15]` | Y_DROP_PRECEDENCE |
    | `[18:17]` | G_DROP_PRECEDENCE |
    | `[20:19]` | R_DROP |
    | `[22:21]` | Y_DROP |
    | `[24:23]` | G_DROP |
    | `[27:25]` | R_COPY_TO_CPU |
    | `[30:28]` | Y_COPY_TO_CPU |
    | `[35:34]` | R_CHANGE_ECN |
    | `[37:36]` | Y_CHANGE_ECN |
    | `[39:38]` | G_CHANGE_ECN |
    | `[42:40]` | R_NEW_PKT_PRI |
    | `[45:43]` | Y_NEW_PKT_PRI |
    | `[48:46]` | G_NEW_PKT_PRI |
    | `[51:49]` | R_CHANGE_PKT_PRI |
    | `[54:52]` | Y_CHANGE_PKT_PRI |
    | `[57:55]` | G_CHANGE_PKT_PRI |
    | `[63:58]` | Y_NEW_DSCP |
    | `[69:64]` | R_NEW_DSCP |
    | `[75:70]` | G_NEW_DSCP_TOS |
    | `[77:76]` | R_CHANGE_DSCP |
    | `[79:78]` | Y_CHANGE_DSCP |
    | `[82:80]` | G_CHANGE_DSCP_TOS |
    | `[90:83]` | MATCHED_RULE |
    | `[104:98]` | Y_COS_INT_PRI |
    | `[111:105]` | G_COS_INT_PRI |
    | `[115:112]` | R_CHANGE_COS_OR_INT_PRI |
    | `[119:116]` | Y_CHANGE_COS_OR_INT_PRI |
    | `[123:120]` | G_CHANGE_COS_OR_INT_PRI |
    | `[124]` | GREEN_TO_PID |
    | `[127:125]` | G_L3SW_CHANGE_L2_FIELDS |
    | `[130:128]` | G_PACKET_REDIRECTION |
    | `[131]` | METER_PAIR_MODE_MODIFIER |
    | `[134:132]` | METER_PAIR_MODE |
    | `[144:135]` | METER_PAIR_INDEX_EVEN |
    | `[145]` | METER_UPDATE_EVEN |
    | `[146]` | METER_TEST_EVEN |
    | `[156:147]` | METER_PAIR_INDEX_ODD |
    | `[157]` | METER_UPDATE_ODD |
    | `[158]` | METER_TEST_ODD |
    | `[171:165]` | COUNTER_INDEX |
    | `[172]` | RESERVED_0 |
    | `[178:173]` | CPU_COS |
    | `[180:179]` | CHANGE_CPU_COS |
    | `[187:181]` | PORT_NUM |
    | `[196]` | T |
    | `[199:197]` | REDIRECT_TO_NHI |
    | `[218:200]` | ECMP_NH_INFO |
    | `[215:200]` | PPD3_CLASS_TAG |
    | `[213:200]` | NEXT_HOP_INDEX |
    | `[209:200]` | ECMP_PTR |
    | `[201:200]` | EH_TAG_TYPE |
    | `[202]` | EH_TM |
    | `[218:203]` | EH_QUEUE_TAG |
    | `[212:210]` | ECMP_HASH_SEL |
    | `[214]` | ECMP |
    | `[219]` | DO_NOT_GENERATE_CNM |
    | `[220]` | DISABLE_DYNAMIC_LOAD_BALANCING |
    | `[221]` | DO_NOT_CHANGE_TTL |
    | `[222]` | DO_NOT_URPF |
    | `[237]` | EVEN_PARITY |

**Live capture (Cumulus):** 100 entries populated. Sample:

    ipipe0[256]: <Y_DROP=1,Y_COPY_TO_CPU=3,R_DROP=1,R_COPY_TO_CPU=3,METER_PAIR_MODE_MODIFIER=1,G_DROP=1,G_COPY_TO_CPU=3,COUNTER_MODE=7,>

---

## FP_COUNTER_TABLEm

- **Base address:** `0x0d1ca000`  ·  **Entries:** 2048  ·  **Entry width:** 9 bytes
- **Function:** COUNTER TABLE FOR THE FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## FP_STORM_CONTROL_METERSm

- **Base address:** `0x0d1d0000`  ·  **Entries:** 264  ·  **Entry width:** 7 bytes
- **Function:** STORM CONTROL METER TABLE STRUCTURES FOR THE FP, FeatureSpecific-FP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | BUCKETCOUNT |
    | `[51:33]` | REFRESHCOUNT |
    | `[52]` | METER_SPARE |
    | `[53]` | EVEN_PARITY |

---

## L2MCm

- **Base address:** `0x0e128000`  ·  **Entries:** 8192  ·  **Entry width:** 10 bytes
- **Function:** L2 Multicast table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |
    | `[73:66]` | HIGIG_TRUNK_OVERRIDE_PROFILE_PTR |
    | `[74]` | VALID |
    | `[75]` | EVEN_PARITY |

---

## L3_IPMCm

- **Base address:** `0x0e12c000`  ·  **Entries:** 4096  ·  **Entry width:** 19 bytes
- **Function:** L3 IPMC Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | L2_BITMAP_W2 |
    | `[131:130]` | L3_BITMAP_W2 |
    | `[143:132]` | HIGIG_TRUNK_OVERRIDE_PROFILE_PTR |
    | `[144]` | REMOVE_SGLP_FROM_L3_BITMAP |
    | `[145]` | VALID |
    | `[146]` | EVEN_PARITY |

---

## IFP_REDIRECTION_PROFILEm

- **Base address:** `0x0e166000`  ·  **Entries:** 1024  ·  **Entry width:** 10 bytes
- **Function:** Contains the number of members in each ECMP group.  Used with ECMP_POINTER to calulate index to L3_ECMP table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[73:66]` | HIGIG_TRUNK_OVERRIDE_PROFILE_PTR |
    | `[74]` | EVEN_PARITY |

---

## L3_IPMC_REMAPm

- **Base address:** `0x0e16a000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** L3 IPMC Remap Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | L3MC_INDEX |
    | `[12]` | EVEN_PARITY |

**Live capture (Cumulus):** 4095 entries populated. Sample:

    ipipe0[1]: <L3MC_INDEX=1,>

---

## ICONTROL_OPCODE_BITMAPm

- **Base address:** `0x0e16e000`  ·  **Entries:** 66  ·  **Entry width:** 9 bytes
- **Function:** Higig control packet's switching bitmap register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## CPU_PBMm

- **Base address:** `0x0e170000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W0=1,BITMAP=0x000000000000000001>

---

## EGR_MASK_MODBASEm

- **Base address:** `0x0e172000`  ·  **Entries:** 256  ·  **Entry width:** 2 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | BASE |
    | `[12]` | EVEN_PARITY |

---

## L3_ECMP_COUNTm

- **Base address:** `0x0e174000`  ·  **Entries:** 1024  ·  **Entry width:** 25 bytes
- **Function:** Contains the number of members in each ECMP group.  Used with ECMP_POINTER to calulate index to L3_ECMP table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | COUNT |
    | `[7:0]` | COUNT_0 |
    | `[19:8]` | BASE_PTR_0 |
    | `[21:10]` | BASE_PTR |
    | `[27:20]` | COUNT_1 |
    | `[47:40]` | COUNT_2 |
    | `[59:48]` | BASE_PTR_2 |
    | `[79:68]` | BASE_PTR_3 |
    | `[80]` | EVEN_PARITY_0 |
    | `[81]` | L3_OIF_0_TYPE |
    | `[94:82]` | L3_OIF_0 |
    | `[95]` | L3_OIF_1_TYPE |
    | `[108:96]` | L3_OIF_1 |
    | `[109]` | L3_OIF_2_TYPE |
    | `[122:110]` | L3_OIF_2 |
    | `[123]` | L3_OIF_3_TYPE |
    | `[137]` | L3_OIF_4_TYPE |
    | `[150:138]` | L3_OIF_4 |
    | `[151]` | L3_OIF_5_TYPE |
    | `[165]` | L3_OIF_6_TYPE |
    | `[178:166]` | L3_OIF_6 |
    | `[179]` | L3_OIF_7_TYPE |
    | `[195:193]` | URPF_COUNT |
    | `[196]` | ECMP_GT8 |
    | `[197]` | EVEN_PARITY_1 |

---

## L3_ECMPm

- **Base address:** `0x0e176000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** L3 Equal Cost Multipath table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP |
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[14]` | EVEN_PARITY |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[0]: <NEXT_HOP_INDEX=3,NEXT_HOP=3,>

---

## TRUNK_GROUPm

- **Base address:** `0x0e17a000`  ·  **Entries:** 1024  ·  **Entry width:** 3 bytes
- **Function:** Egress Mask Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RTAG |
    | `[10:3]` | TG_SIZE |
    | `[21:11]` | BASE_PTR |
    | `[22]` | EVEN_PARITY |

---

## ING_L3_NEXT_HOPm

- **Base address:** `0x0e17c000`  ·  **Entries:** 16384  ·  **Entry width:** 5 bytes
- **Function:** Reduced version of L3_NEXT_HOP table.  Used to provide just mod and port/TGID

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | ENTRY_TYPE |
    | `[15:2]` | MTU_SIZE |
    | `[14:2]` | L3_OIF |
    | `[13:2]` | VLAN_ID |
    | `[8:2]` | DVP_RES_INFO |
    | `[15:14]` | ENTRY_INFO_UPPER |
    | `[25:16]` | TGID |
    | `[22:16]` | PORT_NUM |
    | `[30:23]` | MODULE_ID |
    | `[31]` | T |
    | `[32]` | DROP |
    | `[33]` | COPY_TO_CPU |
    | `[34]` | EVEN_PARITY |

**Live capture (Cumulus):** 4 entries populated. Sample:

    ipipe0[0]: <TGID=0x1f,PORT_NUM=0x1f,DROP=1,>

---

## EGR_MASKm

- **Base address:** `0x0f12b000`  ·  **Entries:** 4096  ·  **Entry width:** 9 bytes
- **Function:** Egress Mask Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | EGRESS_MASK_W2 |
    | `[66]` | EVEN_PARITY |

---

## E2E_HOL_STATUSm

- **Base address:** `0x0f131400`  ·  **Entries:** 256  ·  **Entry width:** 33 bytes
- **Function:** Remote Module End-to-End HOL Status Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[256]` | EVEN_PARITY |

---

## E2E_HOL_STATUS_1m

- **Base address:** `0x0f131800`  ·  **Entries:** 256  ·  **Entry width:** 33 bytes
- **Function:** Remote Module End-to-End HOL Status Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[256]` | EVEN_PARITY |

---

## TRILL_DROP_STATS_Xm

- **Base address:** `0x0f13c000`  ·  **Entries:** 1  ·  **Entry width:** 16 bytes
- **Function:** TRILL_DROP_STATS table.

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## TRILL_DROP_STATS_Ym

- **Base address:** `0x0f15c000`  ·  **Entries:** 1  ·  **Entry width:** 16 bytes
- **Function:** TRILL_DROP_STATS table.

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## L3_MTU_VALUESm

- **Base address:** `0x0f160000`  ·  **Entries:** 12288  ·  **Entry width:** 2 bytes
- **Function:** index by ING_L3_NEXT_HOP.L3_OIF or ipmc_index or VID

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | MTU_SIZE |
    | `[14]` | EVEN_PARITY |

**Live capture (Cumulus):** 12288 entries populated. Sample:

    ipipe0[0]: <MTU_SIZE=0x3fff,>

---

## MODPORT_MAP_M2m

- **Base address:** `0x0f164000`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** First physical copy of Module Port Mapping Table - used for mapping the M2 copy of a packet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST |
    | `[7]` | ISTRUNK |
    | `[8]` | ENABLE |
    | `[9]` | EVEN_PARITY |

---

## MODPORT_MAP_M3m

- **Base address:** `0x0f165000`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** First physical copy of Module Port Mapping Table - used for mapping the M3 copy of a packet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST |
    | `[7]` | ISTRUNK |
    | `[8]` | ENABLE |
    | `[9]` | EVEN_PARITY |

---

## VLAN_COS_MAPm

- **Base address:** `0x0f167000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** index by vid

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | VLAN_COS |
    | `[7]` | VALID |
    | `[8]` | EVEN_PARITY |

---

## SRC_MODID_EGRESSm

- **Base address:** `0x0f16a000`  ·  **Entries:** 2048  ·  **Entry width:** 9 bytes
- **Function:** Source Modid based blocking mask table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BLOCK_MASK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## TRUNK_MEMBERm

- **Base address:** `0x0f16a800`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** Contains the members in each LAG group.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[14:7]` | MODULE_ID |
    | `[15]` | EVEN_PARITY |

---

## MODPORT_MAP_SWm

- **Base address:** `0x0f16c000`  ·  **Entries:** 2048  ·  **Entry width:** 3 bytes
- **Function:** First physical copy of Module Port Mapping Table - used for mapping the switched copy of a packet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST0 |
    | `[7]` | ISTRUNK0 |
    | `[8]` | ENABLE0 |
    | `[15:9]` | DEST1 |
    | `[16]` | ISTRUNK1 |
    | `[17]` | ENABLE1 |
    | `[21:18]` | VOQ_GRP_ID |
    | `[22]` | VOQ_COS_VALID |
    | `[23]` | EVEN_PARITY |

---

## MODPORT_MAP_MIRRORm

- **Base address:** `0x0f16d000`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** Second physical copy of Module Port Mapping Table - used for mapping the ingress mirrored copy of a packet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST |
    | `[7]` | ISTRUNK |
    | `[8]` | ENABLE |
    | `[9]` | EVEN_PARITY |

---

## MODPORT_MAP_M0m

- **Base address:** `0x0f16e000`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** First physical copy of Module Port Mapping Table - used for mapping the M0 copy of a packet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST |
    | `[7]` | ISTRUNK |
    | `[8]` | ENABLE |
    | `[9]` | EVEN_PARITY |

---

## MODPORT_MAP_M1m

- **Base address:** `0x0f16f000`  ·  **Entries:** 2048  ·  **Entry width:** 2 bytes
- **Function:** First physical copy of Module Port Mapping Table - used for mapping the M1 copy of a packet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DEST |
    | `[7]` | ISTRUNK |
    | `[8]` | ENABLE |
    | `[9]` | EVEN_PARITY |

---

## HG_TRUNK_GROUPm

- **Base address:** `0x0f170000`  ·  **Entries:** 32  ·  **Entry width:** 2 bytes
- **Function:** HiGig Trunk [0-7] membership by port number and RTAG

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RTAG |
    | `[7:3]` | TG_SIZE |
    | `[15:8]` | BASE_PTR |

---

## HG_TRUNK_MEMBERm

- **Base address:** `0x0f170400`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** Contains the list of all HG Trunk members.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |

---

## TRUNK_BITMAPm

- **Base address:** `0x0f170800`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** Source Trunk Bitmap Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | TRUNK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## MAC_BLOCKm

- **Base address:** `0x0f170c00`  ·  **Entries:** 32  ·  **Entry width:** 9 bytes
- **Function:** Source Trunk Bitmap Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | MAC_BLOCK_MASK_W2 |
    | `[66]` | EVEN_PARITY |

---

## NONUCAST_TRUNK_BLOCK_MASKm

- **Base address:** `0x0f171000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** Multicast and Broadcast Trunk Block Mask Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLOCK_MASK_W2 |
    | `[66]` | EVEN_PARITY |

---

## IM_MTP_INDEXm

- **Base address:** `0x0f171c00`  ·  **Entries:** 4  ·  **Entry width:** 16 bytes
- **Function:** Ingress Mirror to Port Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[6:0]` | PORT_NUM_0 |
    | `[14:7]` | MODULE_ID |
    | `[14:7]` | MODULE_ID_0 |
    | `[21:15]` | PORT_NUM_1 |
    | `[29:22]` | MODULE_ID_1 |
    | `[44:37]` | MODULE_ID_2 |
    | `[51:45]` | PORT_NUM_3 |
    | `[59:52]` | MODULE_ID_3 |
    | `[74:67]` | MODULE_ID_4 |
    | `[81:75]` | PORT_NUM_5 |
    | `[89:82]` | MODULE_ID_5 |
    | `[104:97]` | MODULE_ID_6 |
    | `[111:105]` | PORT_NUM_7 |
    | `[119:112]` | MODULE_ID_7 |
    | `[120]` | T |
    | `[123:121]` | COUNT |
    | `[126:124]` | RTAG |

---

## EM_MTP_INDEXm

- **Base address:** `0x0f172000`  ·  **Entries:** 4  ·  **Entry width:** 16 bytes
- **Function:** Egress Mirror to Port Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[6:0]` | PORT_NUM_0 |
    | `[14:7]` | MODULE_ID |
    | `[14:7]` | MODULE_ID_0 |
    | `[21:15]` | PORT_NUM_1 |
    | `[29:22]` | MODULE_ID_1 |
    | `[44:37]` | MODULE_ID_2 |
    | `[51:45]` | PORT_NUM_3 |
    | `[59:52]` | MODULE_ID_3 |
    | `[74:67]` | MODULE_ID_4 |
    | `[81:75]` | PORT_NUM_5 |
    | `[89:82]` | MODULE_ID_5 |
    | `[104:97]` | MODULE_ID_6 |
    | `[111:105]` | PORT_NUM_7 |
    | `[119:112]` | MODULE_ID_7 |
    | `[120]` | T |
    | `[123:121]` | COUNT |
    | `[126:124]` | RTAG |

---

## SRC_MODID_INGRESS_BLOCKm

- **Base address:** `0x0f172400`  ·  **Entries:** 256  ·  **Entry width:** 9 bytes
- **Function:** Source Modid based blocking mask table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## ALTERNATE_EMIRROR_BITMAPm

- **Base address:** `0x0f172800`  ·  **Entries:** 256  ·  **Entry width:** 9 bytes
- **Function:** Source Modid based blocking mask table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## PORT_LAG_FAILOVER_SETm

- **Base address:** `0x0f172c00`  ·  **Entries:** 66  ·  **Entry width:** 16 bytes
- **Function:** Port LAG Failover Set Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT0 |
    | `[14:7]` | MODULE0 |
    | `[21:15]` | PORT1 |
    | `[29:22]` | MODULE1 |
    | `[44:37]` | MODULE2 |
    | `[51:45]` | PORT3 |
    | `[59:52]` | MODULE3 |
    | `[74:67]` | MODULE4 |
    | `[81:75]` | PORT5 |
    | `[89:82]` | MODULE5 |
    | `[104:97]` | MODULE6 |
    | `[111:105]` | PORT7 |
    | `[119:112]` | MODULE7 |
    | `[122:120]` | RTAG |
    | `[125:123]` | FAILOVER_SET_SIZE |
    | `[126]` | EVEN_PARITY |

---

## HG_TRUNK_FAILOVER_SETm

- **Base address:** `0x0f173000`  ·  **Entries:** 66  ·  **Entry width:** 8 bytes
- **Function:** Higig Trunk Failover Set Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT0 |
    | `[13:7]` | PORT1 |
    | `[20:14]` | PORT2 |
    | `[27:21]` | PORT3 |
    | `[41:35]` | PORT5 |
    | `[48:42]` | PORT6 |
    | `[55:49]` | PORT7 |
    | `[58:56]` | RTAG |
    | `[61:59]` | FAILOVER_SET_SIZE |

---

## VLAN_PROFILE_2m

- **Base address:** `0x0f173400`  ·  **Entries:** 128  ·  **Entry width:** 18 bytes
- **Function:** Vlan Profile Table 2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLOCK_MASK_A_W2 |
    | `[131:130]` | BLOCK_MASK_B_W2 |
    | `[133:132]` | BCAST_MASK_SEL |
    | `[135:134]` | UNKNOWN_UCAST_MASK_SEL |
    | `[137:136]` | UNKNOWN_MCAST_MASK_SEL |
    | `[139:138]` | KNOWN_MCAST_MASK_SEL |
    | `[140]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[2]: <UNKNOWN_UCAST_MASK_SEL=1,UNKNOWN_MCAST_MASK_SEL=1,BLOCK_MASK_A_W0=1,BLOCK_MASK_A=0x000000000000000001,>

---

## PORT_COS_MAPm

- **Base address:** `0x0f173800`  ·  **Entries:** 64  ·  **Entry width:** 2 bytes
- **Function:** index by COS_MAP_SEL.SELECT(2-bit), ingress port internal priority(4-bit)

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | COS |
    | `[3:0]` | UC_COS1 |
    | `[10:4]` | HG_COS |
    | `[13:11]` | MC_COS1 |

---

## CPU_COS_MAPm

- **Base address:** `0x0f174000`  ·  **Entries:** 128  ·  **Entry width:** 18 bytes
- **Function:** index by COPYTO_CPU reasons code and internal priorities

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[4:1]` | INT_PRI_KEY |
    | `[5]` | MIRR_PKT_KEY |
    | `[7:6]` | SW_PKT_TYPE_KEY |
    | `[71:68]` | INT_PRI_MASK |
    | `[72]` | MIRR_PKT_MASK |
    | `[74:73]` | SW_PKT_TYPE_MASK |
    | `[140:135]` | COS |

**Live capture (Cumulus):** 11 entries populated. Sample:

    ipipe0[117]: <VALID=1,REASONS_MASK_HIGH=0x30,REASONS_KEY_HIGH=0x30,MASK=0x000000180000000000,KEY=0x000000180000000000,COS=0x22>

---

## CPU_COS_MAP_ONLYm

- **Base address:** `0x0f174400`  ·  **Entries:** 128  ·  **Entry width:** 17 bytes
- **Function:** CPU_COS_MAP TCAM only view

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALID |
    | `[4:1]` | INT_PRI_KEY |
    | `[5]` | MIRR_PKT_KEY |
    | `[7:6]` | SW_PKT_TYPE_KEY |
    | `[71:68]` | INT_PRI_MASK |
    | `[72]` | MIRR_PKT_MASK |
    | `[74:73]` | SW_PKT_TYPE_MASK |

**Live capture (Cumulus):** 11 entries populated. Sample:

    ipipe0[117]: <VALID=1,REASONS_MASK_HIGH=0x30,REASONS_KEY_HIGH=0x30,MASK=0x000000180000000000,KEY=0x000000180000000000,>

---

## CPU_COS_MAP_DATA_ONLYm

- **Base address:** `0x0f174800`  ·  **Entries:** 128  ·  **Entry width:** 1 bytes
- **Function:** CPU_COS_MAP Data SRAM for CPU_COS_MAP TCAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | COS |

**Live capture (Cumulus):** 10 entries populated. Sample:

    ipipe0[117]: <COS=0x22>

---

## UNKNOWN_UCAST_BLOCK_MASKm

- **Base address:** `0x0f174c00`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Unknown Unicast Block Mask

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## UNKNOWN_MCAST_BLOCK_MASKm

- **Base address:** `0x0f175000`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Unknown Multicast Block Mask

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## BCAST_BLOCK_MASKm

- **Base address:** `0x0f175400`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Broadcast Block Mask

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## EMIRROR_CONTROLm

- **Base address:** `0x0f175800`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Egress mirror bitmap register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## ING_EGRMSKBMAPm

- **Base address:** `0x0f175c00`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Ingress Block Mask, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## LOCAL_SW_DISABLE_DEFAULT_PBMm

- **Base address:** `0x0f176000`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Local switching disable default port bitmap, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## KNOWN_MCAST_BLOCK_MASKm

- **Base address:** `0x0f176400`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Known Multicast Block Mask, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BLK_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## EMIRROR_CONTROL1m

- **Base address:** `0x0f176800`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Egress mirror 1bitmap register, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## EMIRROR_CONTROL2m

- **Base address:** `0x0f176c00`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Egress mirror bitmap register, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## EMIRROR_CONTROL3m

- **Base address:** `0x0f177000`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Egress mirror bitmap register, FeatureSpecific-Ethernet.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_MIRRm

- **Base address:** `0x0f177400`  ·  **Entries:** 67  ·  **Entry width:** 9 bytes
- **Function:** Local switching disable default port bitmap for ingress mirror or egress mirror packets, FeatureSpecific-Ethernet

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## IMIRROR_BITMAPm

- **Base address:** `0x0f177800`  ·  **Entries:** 66  ·  **Entry width:** 9 bytes
- **Function:** Alternate Bitmap/path to MTP for Mirroring

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## UNKNOWN_HGI_BITMAPm

- **Base address:** `0x0f177c00`  ·  **Entries:** 66  ·  **Entry width:** 9 bytes
- **Function:** Forwarding bitmap for unknown HGI

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |
    | `[66]` | EVEN_PARITY |

---

## ING_EN_EFILTER_BITMAPm

- **Base address:** `0x0f178000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Ingress Enable EFilter Bitmap Register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W1=0x1fffff,BITMAP_W0=0xffffffff,BITMAP=0x00001fffffffffffff>

---

## HIGIG_TRUNK_CONTROLm

- **Base address:** `0x0f178400`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** HiGig Trunk Control Register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | ACTIVE_PORT_BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <ACTIVE_PORT_BITMAP_W2=2,ACTIVE_PORT_BITMAP_W1=0x1fffff,ACTIVE_PORT_BITMAP_W0=0xffffffff,ACTIVE_PORT_BITMAP=0x02001fffffffffffff>

---

## EPC_LINK_BMAPm

- **Base address:** `0x0f178800`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Link status register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <PORT_BITMAP_W2=2,PORT_BITMAP_W0=7,PORT_BITMAP=0x020000000000000007>

---

## HG_TRUNK_BITMAPm

- **Base address:** `0x0f179000`  ·  **Entries:** 32  ·  **Entry width:** 9 bytes
- **Function:** HiGig Trunk [0-7] Membership Bitmap

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | HIGIG_TRUNK_BITMAP_W2 |

---

## HG_TRUNK_FAILOVER_ENABLEm

- **Base address:** `0x0f179400`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** HiGig Trunk Failover Enable Register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

---

## LINK_STATUSm

- **Base address:** `0x0f179800`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Link Status Indication Register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W2=2,BITMAP_W0=7,BITMAP=0x020000000000000007>

---

## PORT_BRIDGE_BMAPm

- **Base address:** `0x0f179c00`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Bitmap of ports with port_bridge enabled

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

---

## PORT_BRIDGE_MIRROR_BMAPm

- **Base address:** `0x0f17a000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Bitmap of ports with port bridge enables for mirror packets.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

---

## MULTIPASS_LOOPBACK_BITMAPm

- **Base address:** `0x0f17a800`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Multipass Loopback Bitmap Register.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W2=2,BITMAP=0x020000000000000000>

---

## MIRROR_CONTROLm

- **Base address:** `0x0f17ac00`  ·  **Entries:** 67  ·  **Entry width:** 3 bytes
- **Function:** Mirror control register

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | M_ENABLE |
    | `[2:1]` | MTP_INDEX0 |
    | `[4:3]` | MTP_INDEX1 |
    | `[6:5]` | MTP_INDEX2 |
    | `[8:7]` | MTP_INDEX3 |
    | `[10:9]` | NON_UC_EM_MTP_INDEX |
    | `[10:9]` | NON_UC_EM_MTP_INDEX0 |
    | `[12:11]` | NON_UC_EM_MTP_INDEX1 |
    | `[14:13]` | NON_UC_EM_MTP_INDEX2 |
    | `[16:15]` | NON_UC_EM_MTP_INDEX3 |

**Live capture (Cumulus):** 55 entries populated. Sample:

    ipipe0[0]: <NON_UC_EM_MTP_INDEX3=3,NON_UC_EM_MTP_INDEX2=2,NON_UC_EM_MTP_INDEX1=1,M_ENABLE=1,MTP_INDEX3=3,MTP_INDEX2=2,MTP_INDEX1=1,>

---

## COS_MAP_SELm

- **Base address:** `0x0f17b000`  ·  **Entries:** 67  ·  **Entry width:** 1 bytes
- **Function:** Select one of four sections of COS_MAP table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SELECT |

---

## ING_ROUTED_INT_PRI_MAPPINGm

- **Base address:** `0x0f17b400`  ·  **Entries:** 16  ·  **Entry width:** 1 bytes
- **Function:** Internal priority mapping table, used to steer traffic from non-QCN-aware sources away from QCN queues.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | NEW_INT_PRI |

**Live capture (Cumulus):** 15 entries populated. Sample:

    ipipe0[1]: <NEW_INT_PRI=1>

---

## ING_HIGIG_TRUNK_OVERRIDE_PROFILEm

- **Base address:** `0x0f17b800`  ·  **Entries:** 256  ·  **Entry width:** 5 bytes
- **Function:** Higig Trunk Override Profile Pointer.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[32]` | EVEN_PARITY |

---

## VOQ_COS_MAPm

- **Base address:** `0x0f17bc00`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** VOQ Mapping table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | VOQ_COS |
    | `[7]` | EVEN_PARITY |

---

## HGT_DLB_CONTROLm

- **Base address:** `0x0f17c400`  ·  **Entries:** 32  ·  **Entry width:** 1 bytes
- **Function:** HG-Trunk DLB Control.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | GROUP_ENABLE |
    | `[3:1]` | DLB_ID |

---

## PHB2_COS_MAPm

- **Base address:** `0x0f17c800`  ·  **Entries:** 272  ·  **Entry width:** 1 bytes
- **Function:** index by PHB2_DOT1P_MAPPING_PTR(4-bit), 802.1 priority(3-bit), CFI/DE

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | COS |
    | `[3:0]` | UC_COS2 |
    | `[6:4]` | MC_COS2 |

---

## CPU_PBM_2m

- **Base address:** `0x0f17cc00`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** Specifies the port(s) that is (are) CPU.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W0=1,BITMAP=0x000000000000000001>

---

## TRILL_DROP_STATSm

- **Base address:** `0x0f1dc000`  ·  **Entries:** 1  ·  **Entry width:** 16 bytes
- **Function:** TRILL_DROP_STATS table.

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## ISBS_PORT_TO_PIPE_MAPPINGm

- **Base address:** `0x10170000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** SBS Port to Pipe Mapping table.

**Entry fields:**

    _(no field breakdown — treated as a single value)_

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP=0x02001ffe00000001fe>

---

## DLB_HGT_GROUP_CONTROL_Xm

- **Base address:** `0x11120000`  ·  **Entries:** 8  ·  **Entry width:** 5 bytes
- **Function:** DLB_HGT Group Parameters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[14:0]` | INACTIVITY_DURATION |
    | `[16:15]` | PORT_ASSIGNMENT_MODE |
    | `[19:17]` | FLOW_SET_SIZE |
    | `[35]` | ENABLE_OPTIMAL_CANDIDATE_UPDATE |

---

## DLB_HGT_PORT_QUALITY_MAPPINGm

- **Base address:** `0x11121000`  ·  **Entries:** 512  ·  **Entry width:** 1 bytes
- **Function:** DLB_HGT Quality Mapping.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | ASSIGNED_QUALITY |

**Live capture (Cumulus):** 56 entries populated. Sample:

    ipipe0[8]: <ASSIGNED_QUALITY=1>

---

## DLB_HGT_GROUP_STATS_Xm

- **Base address:** `0x11125000`  ·  **Entries:** 8  ·  **Entry width:** 8 bytes
- **Function:** DLB_HGT Group Member Bitmap.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | REASSIGNMENTS |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGE_Xm

- **Base address:** `0x11126000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** DLB_HGT Flow Set Page-Number table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[64]` | EVEN_PARITY |

---

## DLB_HGT_GLB_QUANTIZE_THRESHOLDSm

- **Base address:** `0x11127000`  ·  **Entries:** 1  ·  **Entry width:** 28 bytes
- **Function:** DLB_HGT Quantization Thresholds table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | PORT_QSIZE_THRESHOLD_1 |
    | `[31:16]` | PORT_QSIZE_THRESHOLD_2 |
    | `[47:32]` | PORT_QSIZE_THRESHOLD_3 |
    | `[63:48]` | PORT_QSIZE_THRESHOLD_4 |
    | `[79:64]` | PORT_QSIZE_THRESHOLD_5 |
    | `[95:80]` | PORT_QSIZE_THRESHOLD_6 |
    | `[111:96]` | PORT_QSIZE_THRESHOLD_7 |
    | `[127:112]` | PORT_LOADING_THRESHOLD_1 |
    | `[143:128]` | PORT_LOADING_THRESHOLD_2 |
    | `[159:144]` | PORT_LOADING_THRESHOLD_3 |
    | `[175:160]` | PORT_LOADING_THRESHOLD_4 |
    | `[191:176]` | PORT_LOADING_THRESHOLD_5 |
    | `[207:192]` | PORT_LOADING_THRESHOLD_6 |
    | `[223:208]` | PORT_LOADING_THRESHOLD_7 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <PORT_LOADING_THRESHOLD_7=0x348,PORT_LOADING_THRESHOLD_6=0x2d0,PORT_LOADING_THRESHOLD_5=0x258,PORT_LOADING_THRESHOLD_4=0x1e0,PORT_LOADING_THRESHOLD_3=0x168,PORT_LOADING_THRESHOLD_2=0xf0,PORT_LOADING_THRESHOLD_1=0x78>

---

## DLB_HGT_OPTIMAL_CANDIDATE_Xm

- **Base address:** `0x11128000`  ·  **Entries:** 8  ·  **Entry width:** 1 bytes
- **Function:** DLB_HGT Optimal Candidate table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | OPTIMAL_CANDIDATE |
    | `[7]` | OPTIMAL_CANDIDATE_VALID |

---

## DLB_HGT_FLOWSET_PORT_Xm

- **Base address:** `0x11130000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Assigned Member.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[7]` | VALID |
    | `[8]` | EVEN_PARITY |

---

## DLB_HGT_FLOWSET_TIMESTAMP_Xm

- **Base address:** `0x11138000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Observation Timestamp.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | OBSERVATION_TIMESTAMP |
    | `[8]` | EVEN_PARITY |

---

## DLB_HGT_GROUP_CONTROL_Ym

- **Base address:** `0x11140000`  ·  **Entries:** 8  ·  **Entry width:** 5 bytes
- **Function:** DLB_HGT Group Parameters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[14:0]` | INACTIVITY_DURATION |
    | `[16:15]` | PORT_ASSIGNMENT_MODE |
    | `[19:17]` | FLOW_SET_SIZE |
    | `[35]` | ENABLE_OPTIMAL_CANDIDATE_UPDATE |

---

## DLB_HGT_GROUP_STATS_Ym

- **Base address:** `0x11145000`  ·  **Entries:** 8  ·  **Entry width:** 8 bytes
- **Function:** DLB_HGT Group Member Bitmap.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | REASSIGNMENTS |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGE_Ym

- **Base address:** `0x11146000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** DLB_HGT Flow Set Page-Number table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[64]` | EVEN_PARITY |

---

## DLB_HGT_OPTIMAL_CANDIDATE_Ym

- **Base address:** `0x11148000`  ·  **Entries:** 8  ·  **Entry width:** 1 bytes
- **Function:** DLB_HGT Optimal Candidate table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | OPTIMAL_CANDIDATE |
    | `[7]` | OPTIMAL_CANDIDATE_VALID |

---

## DLB_HGT_FLOWSET_PORT_Ym

- **Base address:** `0x11150000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Assigned Member.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[7]` | VALID |
    | `[8]` | EVEN_PARITY |

---

## DLB_HGT_FLOWSET_TIMESTAMP_Ym

- **Base address:** `0x11158000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Observation Timestamp.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | OBSERVATION_TIMESTAMP |
    | `[8]` | EVEN_PARITY |

---

## DLB_HGT_GROUP_MEMBERSHIPm

- **Base address:** `0x11162000`  ·  **Entries:** 8  ·  **Entry width:** 9 bytes
- **Function:** DLB_HGT Group Member Bitmap.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_MAP_W2 |

---

## DLB_HGT_PORT_STATEm

- **Base address:** `0x11163000`  ·  **Entries:** 1  ·  **Entry width:** 9 bytes
- **Function:** DLB_HGT Hardware Link State.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | BITMAP_W2 |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <BITMAP_W2=2,BITMAP_W0=7,BITMAP=0x020000000000000007>

---

## DLB_HGT_LINK_CONTROLm

- **Base address:** `0x11164000`  ·  **Entries:** 1  ·  **Entry width:** 17 bytes
- **Function:** DLB_HGT Software Link Status Control.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | SW_PORT_STATE_W2 |
    | `[131:130]` | SW_OVERRIDE_PORT_MAP_W2 |

---

## DLB_HGT_GROUP_CONTROLm

- **Base address:** `0x111c0000`  ·  **Entries:** 8  ·  **Entry width:** 5 bytes
- **Function:** DLB_HGT Group Parameters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[14:0]` | INACTIVITY_DURATION |
    | `[16:15]` | PORT_ASSIGNMENT_MODE |
    | `[19:17]` | FLOW_SET_SIZE |
    | `[35]` | ENABLE_OPTIMAL_CANDIDATE_UPDATE |

---

## DLB_HGT_GROUP_STATSm

- **Base address:** `0x111c5000`  ·  **Entries:** 8  ·  **Entry width:** 8 bytes
- **Function:** DLB_HGT Group Member Bitmap.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | REASSIGNMENTS |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGEm

- **Base address:** `0x111c6000`  ·  **Entries:** 1024  ·  **Entry width:** 9 bytes
- **Function:** DLB_HGT Flow Set Page-Number table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[64]` | EVEN_PARITY |

---

## DLB_HGT_OPTIMAL_CANDIDATEm

- **Base address:** `0x111c8000`  ·  **Entries:** 8  ·  **Entry width:** 1 bytes
- **Function:** DLB_HGT Optimal Candidate table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | OPTIMAL_CANDIDATE |
    | `[7]` | OPTIMAL_CANDIDATE_VALID |

---

## DLB_HGT_FLOWSET_PORTm

- **Base address:** `0x111d0000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Assigned Member.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PORT_NUM |
    | `[7]` | VALID |
    | `[8]` | EVEN_PARITY |

---

## DLB_HGT_FLOWSET_TIMESTAMPm

- **Base address:** `0x111d8000`  ·  **Entries:** 32768  ·  **Entry width:** 2 bytes
- **Function:** DLB_HGT Flow Set Observation Timestamp.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | OBSERVATION_TIMESTAMP |
    | `[8]` | EVEN_PARITY |

---

## SOURCE_VPm

- **Base address:** `0x12160000`  ·  **Entries:** 8192  ·  **Entry width:** 14 bytes
- **Function:** Source Virtual Port Properties

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | ENTRY_TYPE |
    | `[10:3]` | CLASS_ID |
    | `[26:11]` | DEFAULT_VLAN_TAG |
    | `[23:11]` | DVP |
    | `[22:11]` | DEFAULT_VID |
    | `[22:11]` | EXP_PVLAN_VID |
    | `[20:11]` | VFI |
    | `[22:21]` | RESERVED_VFI |
    | `[25:23]` | DEFAULT_PRI |
    | `[26]` | DEFAULT_CFI |
    | `[28:27]` | PVLAN_OR_DEFAULT_VID_CONTROL |
    | `[27]` | DEFAULT_VLAN_TAG_VALID |
    | `[28]` | PVLAN_ENABLE |
    | `[28]` | SD_TAG_VFI_ENABLE |
    | `[30:29]` | TPID_SOURCE |
    | `[35]` | SD_TAG_MODE |
    | `[36]` | NETWORK_PORT |
    | `[42:37]` | TRUST_DOT1P_PTR |
    | `[43]` | USE_INNER_PRI |
    | `[50:44]` | SRC_PORT |
    | `[58:51]` | SRC_MODID |
    | `[72]` | DISABLE_VLAN_CHECKS |
    | `[79:73]` | TRUST_DSCP_PTR |
    | `[80]` | TRUST_DSCP_V4 |
    | `[81]` | TRUST_DSCP_V6 |
    | `[85:82]` | ING_MIRROR_ENABLE |
    | `[91:86]` | DOT1P_REMAP_POINTER |
    | `[92]` | USE_VINTF_CTR_IDX |
    | `[100:97]` | CML_FLAGS_MOVE |
    | `[106:101]` | VLAN_MEMBERSHIP_PROFILE |
    | `[107]` | ENABLE_IFILTER |
    | `[108]` | DISABLE_VP_PRUNING |
    | `[110:109]` | TRILL_RBRIDGE_NICKNAME_INDEX |
    | `[111]` | EVEN_PARITY |

---

## L3_IIFm

- **Base address:** `0x12162000`  ·  **Entries:** 8192  ·  **Entry width:** 8 bytes
- **Function:** Layer 3 Input Interface Properties

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | VRF |
    | `[10]` | ALLOW_GLOBAL_ROUTE |
    | `[18:11]` | CLASS_ID |
    | `[25:19]` | TRUST_DSCP_PTR |
    | `[27:26]` | URPF_MODE |
    | `[28]` | URPF_DEFAULTROUTECHECK |
    | `[54:42]` | IPMC_L3_IIF |
    | `[55]` | USE_VINTF_CTR_IDX |
    | `[56]` | EVEN_PARITY |

**Live capture (Cumulus):** 8192 entries populated. Sample:

    ipipe0[0]: <URPF_DEFAULTROUTECHECK=1,ALLOW_GLOBAL_ROUTE=1>

---

## VFIm

- **Base address:** `0x12164000`  ·  **Entries:** 1024  ·  **Entry width:** 12 bytes
- **Function:** VFI Properties - address is VFI value.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | VP_0 |
    | `[11:0]` | BC_INDEX |
    | `[12]` | RESERVED_BC_INDEX |
    | `[25:13]` | VP_1 |
    | `[24:13]` | UUC_INDEX |
    | `[25]` | RESERVED_UUC_INDEX |
    | `[49:38]` | BVID |
    | `[55:50]` | TRUST_DOT1P_PTR |
    | `[56]` | PT2PT_EN |
    | `[73:70]` | PHB2_DOT1P_MAPPING_PTR |
    | `[74]` | PHB2_USE_INNER_DOT1P |
    | `[75]` | PHB2_ENABLE |
    | `[76]` | L2_PROTOCOL_PKT_DROP |
    | `[77]` | L2_PROTOCOL_TO_CPU |
    | `[83:78]` | DOT1P_REMAP_POINTER |
    | `[84]` | USE_SERVICE_CTR_IDX |
    | `[90:85]` | PROTOCOL_PKT_INDEX |
    | `[91]` | EVEN_PARITY |

---

## VRFm

- **Base address:** `0x12166000`  ·  **Entries:** 1024  ·  **Entry width:** 2 bytes
- **Function:** VRF Properties - address is VRF value.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | SERVICE_CTR_IDX |
    | `[13]` | USE_SERVICE_CTR_IDX |
    | `[14]` | EVEN_PARITY |

---

## VLAN_TABm

- **Base address:** `0x12168000`  ·  **Entries:** 4096  ·  **Entry width:** 40 bytes
- **Function:** Contains cntrls assoc with the 4K VLANs.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[65:64]` | PORT_BITMAP_W2 |
    | `[131:130]` | ING_PORT_BITMAP_W2 |
    | `[140:132]` | STG |
    | `[205]` | VALID |
    | `[207:206]` | L2_ENTRY_KEY_TYPE |
    | `[209:208]` | SRC_PVLAN_PORT_TYPE |
    | `[217:210]` | HIGIG_TRUNK_OVERRIDE_PROFILE_PTR |
    | `[218]` | VIRTUAL_PORT_EN |
    | `[238:232]` | VLAN_PROFILE_PTR |
    | `[250:239]` | FID_ID |
    | `[270:259]` | BC_IDX |
    | `[282:271]` | UUC_IDX |
    | `[295]` | BC_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[296]` | UUC_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[297]` | UMC_TRILL_NETWORK_RECEIVERS_PRESENT |
    | `[298]` | TRILL_TRANSIT_IGMP_MLD_PAYLOAD_TO_CPU |
    | `[310:299]` | TRILL_DOMAIN_NONUC_REPL_INDEX |
    | `[311]` | TRILL_ACCESS_RECEIVERS_PRESENT |
    | `[313:312]` | TRILL_RBRIDGE_NICKNAME_INDEX |
    | `[314]` | ENABLE_IGMP_MLD_SNOOPING |
    | `[315]` | EVEN_PARITY_0 |
    | `[316]` | EVEN_PARITY_1 |

---

## ING_TRILL_PAYLOAD_PARSE_CONTROLm

- **Base address:** `0x1216a000`  ·  **Entries:** 1  ·  **Entry width:** 7 bytes
- **Function:** Trill parse control.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[51:48]` | TPID_ENABLE |
    | `[52]` | TRILL_ALL_ESADI_RBRIDGES_MAC_ADDRESS_ENABLE |

---

## INITIAL_L3_ECMP_Xm

- **Base address:** `0x13122000`  ·  **Entries:** 4096  ·  **Entry width:** 5 bytes
- **Function:** Initial L3 Equal Cost Multipath table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP |
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[27:14]` | PROT_NEXT_HOP_INDEX |
    | `[38]` | EVEN_PARITY |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[0]: <NEXT_HOP_INDEX=3,NEXT_HOP=3,>

---

## INITIAL_L3_ECMP_Ym

- **Base address:** `0x13142000`  ·  **Entries:** 4096  ·  **Entry width:** 5 bytes
- **Function:** Initial L3 Equal Cost Multipath table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP |
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[27:14]` | PROT_NEXT_HOP_INDEX |
    | `[38]` | EVEN_PARITY |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[0]: <NEXT_HOP_INDEX=3,NEXT_HOP=3,>

---

## INITIAL_L3_ECMP_GROUPm

- **Base address:** `0x13160000`  ·  **Entries:** 1024  ·  **Entry width:** 11 bytes
- **Function:** Contains the number of members in each ECMP group and the ECMP base pointer.  It is indexed by ECMP group number from LPM table.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | COUNT |
    | `[7:0]` | COUNT_0 |
    | `[19:8]` | BASE_PTR_0 |
    | `[21:10]` | BASE_PTR |
    | `[27:20]` | COUNT_1 |
    | `[47:40]` | COUNT_2 |
    | `[59:48]` | BASE_PTR_2 |
    | `[79:68]` | BASE_PTR_3 |
    | `[80]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <COUNT_0=1,COUNT=1,>

---

## INITIAL_L3_ECMPm

- **Base address:** `0x13162000`  ·  **Entries:** 4096  ·  **Entry width:** 5 bytes
- **Function:** Initial L3 Equal Cost Multipath table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP |
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[27:14]` | PROT_NEXT_HOP_INDEX |
    | `[38]` | EVEN_PARITY |

**Live capture (Cumulus):** 2 entries populated. Sample:

    ipipe0[0]: <NEXT_HOP_INDEX=3,NEXT_HOP=3,>

---

## ING_DVP_TABLEm

- **Base address:** `0x13164000`  ·  **Entries:** 8192  ·  **Entry width:** 5 bytes
- **Function:** Used to generte a NHI from the DVP value and other DVP properties.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP_INDEX |
    | `[9:0]` | ECMP_PTR |
    | `[14]` | ECMP |
    | `[16:15]` | VP_TYPE |
    | `[20:17]` | EGR_MIRROR_ENABLE |
    | `[22:21]` | DST_PVLAN_PORT_TYPE |
    | `[35]` | NETWORK_PORT |
    | `[36]` | EVEN_PARITY |

---

## INITIAL_PROT_NHI_TABLEm

- **Base address:** `0x13168000`  ·  **Entries:** 16384  ·  **Entry width:** 4 bytes
- **Function:** Protection Switching (backup path) Next Hop Table

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | PROT_NEXT_HOP_INDEX |
    | `[23:14]` | PROT_GROUP |
    | `[24]` | EVEN_PARITY |

---

## INITIAL_ING_L3_NEXT_HOPm

- **Base address:** `0x1316c000`  ·  **Entries:** 16384  ·  **Entry width:** 3 bytes
- **Function:** Reduced version of L3_NEXT_HOP table.  Used to provide just mod and port/TGID

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TGID |
    | `[6:0]` | PORT_NUM |
    | `[14:7]` | MODULE_ID |
    | `[15]` | T |
    | `[16]` | EVEN_PARITY |

**Live capture (Cumulus):** 3 entries populated. Sample:

    ipipe0[0]: <TGID=0x1f,PORT_NUM=0x1f,>

---

## ING_PW_TERM_SEQ_NUM_Xm

- **Base address:** `0x14126000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** Pseudo-wire Termination Sequence Number - index by PW number.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## ING_VINTF_COUNTER_TABLE_Xm

- **Base address:** `0x14128000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## ING_SERVICE_COUNTER_TABLE_Xm

- **Base address:** `0x1412a000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Service Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## ING_PW_TERM_SEQ_NUM_Ym

- **Base address:** `0x14146000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** Pseudo-wire Termination Sequence Number - index by PW number.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## ING_VINTF_COUNTER_TABLE_Ym

- **Base address:** `0x14148000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Virtual Port / Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <PACKET_COUNTER=0x275c,BYTE_COUNTER=0x0000100c08>

---

## ING_SERVICE_COUNTER_TABLE_Ym

- **Base address:** `0x1414a000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Service Interface Counters.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

**Live capture (Cumulus):** 1 entries populated. Sample:

    ipipe0[0]: <PACKET_COUNTER=0x2759,BYTE_COUNTER=0x0000100ae6>

---

## ING_PW_TERM_SEQ_NUMm

- **Base address:** `0x141c6000`  ·  **Entries:** 8192  ·  **Entry width:** 3 bytes
- **Function:** Pseudo-wire Termination Sequence Number - index by PW number

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEQ_NUM |
    | `[16]` | EVEN_PARITY |

---

## ING_VINTF_COUNTER_TABLEm

- **Base address:** `0x141c8000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Virtual Port / Interface Counters

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

## ING_SERVICE_COUNTER_TABLEm

- **Base address:** `0x141ca000`  ·  **Entries:** 8192  ·  **Entry width:** 9 bytes
- **Function:** Ingress Service Interface Counters

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[28:0]` | PACKET_COUNTER |
    | `[65]` | EVEN_PARITY |

---

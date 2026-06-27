# BCM56846 Registers — EPIPE block

_Egress pipeline — egress VLAN, modification, mirroring, egress policy_

214 registers. Source: OpenMDK CDK defs/sym + OpenBCM descriptions + live Cumulus dump.

---

## EGR_HW_RESET_CONTROL_0r

- **Address:** `0x00280700`  ·  **Size:** 4 bytes
- **Function:** This register is for controlling the HW Table Initialization Feature of the Egress Pipeline.\nThis register should be programmed before programming EGR_HW_RESET_CONTROL_1 register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | STAGE_NUMBER |
    | `[25:6]` | START_ADDRESS |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x00280700` | `0x00000000` |

---

## EGR_HW_RESET_CONTROL_1r

- **Address:** `0x00280701`  ·  **Size:** 4 bytes
- **Function:** This register is for controlling the HW Table Initialization Feature of the Egress Pipeline.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | COUNT |
    | `[16]` | RESET_ALL |
    | `[17]` | VALID |
    | `[18]` | DONE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x00280701` | `0x00000000` |

---

## EGR_Q_BEGINr

- **Address:** `0x00280702`  ·  **Size:** 4 bytes
- **Function:** Register starts an EQ Bus which is provided for later ECO reasons, if any.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:7]` | QBUS |
    | `[31:20]` | HW_CTRL_QBUS |
    | `[20]` | SW_ENC_DEC_TCAM_KEY_MASK |
    | `[31:21]` | RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x00280702` | `0x00100000` |

---

## EGR_ARB_TIMEOUT_CONTROLr

- **Address:** `0x00280703`  ·  **Size:** 4 bytes
- **Function:** Egress arbiter s-bus / IPFIX arbitration timeout control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SBUS_TIMEOUT_EN |
    | `[15:1]` | SBUS_TIMEOUT_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x00280703` | `0x0000012d` |

---

## EGR_VLAN_CONTROL_1r

- **Address:** `0x01200606`  ·  **Size:** 4 bytes
- **Function:** Controls Vlan Translate and VLAN membership related functions.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VT_ENABLE |
    | `[1]` | VT_MISS_DROP |
    | `[2]` | VT_MISS_UT_DROP |
    | `[3]` | VT_MISS_UNTAG |
    | `[4]` | OUTER_TPID_SEL |
    | `[6:5]` | OUTER_TPID_INDEX |
    | `[10:7]` | CFI_AS_CNG |
    | `[11]` | REMARK_OUTER_DOT1P |
    | `[12]` | REMARK_OUTER_DSCP |
    | `[13]` | PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x01200606` | `0x00000000` |
    | xe0 | `0x01201606` | `0x00002001` |
    | xe1 | `0x01202606` | `0x00002001` |
    | xe2 | `0x01203606` | `0x00002001` |
    | xe3 | `0x01204606` | `0x00002001` |
    | xe4 | `0x01205606` | `0x00002001` |
    | xe5 | `0x01206606` | `0x00002001` |
    | xe6 | `0x01207606` | `0x00002001` |
    | xe7 | `0x01208606` | `0x00002001` |
    | xe8 | `0x01209606` | `0x00002001` |
    | xe9 | `0x0120a606` | `0x00002001` |
    | xe10 | `0x0120b606` | `0x00002001` |
    | xe11 | `0x0120c606` | `0x00002001` |
    | xe12 | `0x0120d606` | `0x00002001` |
    | xe13 | `0x0120e606` | `0x00002001` |
    | xe14 | `0x0120f606` | `0x00002001` |
    | xe15 | `0x01210606` | `0x00002001` |
    | xe16 | `0x01211606` | `0x00002001` |
    | xe17 | `0x01212606` | `0x00002001` |
    | xe18 | `0x01213606` | `0x00002001` |
    | xe19 | `0x01214606` | `0x00002001` |
    | xe20 | `0x01215606` | `0x00002001` |
    | xe21 | `0x01216606` | `0x00002001` |
    | xe22 | `0x01217606` | `0x00002001` |
    | xe23 | `0x01218606` | `0x00002001` |
    | xe24 | `0x01219606` | `0x00002001` |
    | xe25 | `0x0121a606` | `0x00002001` |
    | xe26 | `0x0121b606` | `0x00002001` |
    | xe27 | `0x0121c606` | `0x00002001` |
    | xe28 | `0x0121d606` | `0x00002001` |
    | xe29 | `0x0121e606` | `0x00002001` |
    | xe30 | `0x0121f606` | `0x00002001` |
    | xe31 | `0x01220606` | `0x00002001` |
    | xe32 | `0x01221606` | `0x00002001` |
    | xe33 | `0x01222606` | `0x00002001` |
    | xe34 | `0x01223606` | `0x00002001` |
    | xe35 | `0x01224606` | `0x00002001` |
    | xe36 | `0x01225606` | `0x00002001` |
    | xe37 | `0x01226606` | `0x00002001` |
    | xe38 | `0x01227606` | `0x00002001` |
    | xe39 | `0x01228606` | `0x00002001` |
    | xe40 | `0x01229606` | `0x00002001` |
    | xe41 | `0x0122a606` | `0x00002001` |
    | xe42 | `0x0122b606` | `0x00002001` |
    | xe43 | `0x0122c606` | `0x00002001` |
    | xe44 | `0x0122d606` | `0x00002001` |
    | xe45 | `0x0122e606` | `0x00002001` |
    | xe46 | `0x0122f606` | `0x00002001` |
    | xe47 | `0x01230606` | `0x00002001` |
    | xe48 | `0x01231606` | `0x00002001` |
    | xe49 | `0x01232606` | `0x00002001` |
    | xe50 | `0x01233606` | `0x00002001` |
    | xe51 | `0x01234606` | `0x00002001` |
    | lb0 | `0x01241606` | `0x00000000` |

---

## EGR_IPMC_CFG2r

- **Address:** `0x01200610`  ·  **Size:** 4 bytes
- **Function:** Configuration Register for IPMC related modifications.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DISABLE_TTL_DECREMENT |
    | `[1]` | DISABLE_SA_REPLACE |
    | `[2]` | UNTAG |
    | `[14:3]` | OVID |
    | `[14:3]` | VID |
    | `[15]` | IVID_VALID |
    | `[27:16]` | IVID |
    | `[28]` | DISABLE_TTL_CHECK |
    | `[29]` | PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x01200610` | `0x00000000` |
    | xe0 | `0x01201610` | `0x00000000` |
    | xe1 | `0x01202610` | `0x00000000` |
    | xe2 | `0x01203610` | `0x00000000` |
    | xe3 | `0x01204610` | `0x00000000` |
    | xe4 | `0x01205610` | `0x00000000` |
    | xe5 | `0x01206610` | `0x00000000` |
    | xe6 | `0x01207610` | `0x00000000` |
    | xe7 | `0x01208610` | `0x00000000` |
    | xe8 | `0x01209610` | `0x00000000` |
    | xe9 | `0x0120a610` | `0x00000000` |
    | xe10 | `0x0120b610` | `0x00000000` |
    | xe11 | `0x0120c610` | `0x00000000` |
    | xe12 | `0x0120d610` | `0x00000000` |
    | xe13 | `0x0120e610` | `0x00000000` |
    | xe14 | `0x0120f610` | `0x00000000` |
    | xe15 | `0x01210610` | `0x00000000` |
    | xe16 | `0x01211610` | `0x00000000` |
    | xe17 | `0x01212610` | `0x00000000` |
    | xe18 | `0x01213610` | `0x00000000` |
    | xe19 | `0x01214610` | `0x00000000` |
    | xe20 | `0x01215610` | `0x00000000` |
    | xe21 | `0x01216610` | `0x00000000` |
    | xe22 | `0x01217610` | `0x00000000` |
    | xe23 | `0x01218610` | `0x00000000` |
    | xe24 | `0x01219610` | `0x00000000` |
    | xe25 | `0x0121a610` | `0x00000000` |
    | xe26 | `0x0121b610` | `0x00000000` |
    | xe27 | `0x0121c610` | `0x00000000` |
    | xe28 | `0x0121d610` | `0x00000000` |
    | xe29 | `0x0121e610` | `0x00000000` |
    | xe30 | `0x0121f610` | `0x00000000` |
    | xe31 | `0x01220610` | `0x00000000` |
    | xe32 | `0x01221610` | `0x00000000` |
    | xe33 | `0x01222610` | `0x00000000` |
    | xe34 | `0x01223610` | `0x00000000` |
    | xe35 | `0x01224610` | `0x00000000` |
    | xe36 | `0x01225610` | `0x00000000` |
    | xe37 | `0x01226610` | `0x00000000` |
    | xe38 | `0x01227610` | `0x00000000` |
    | xe39 | `0x01228610` | `0x00000000` |
    | xe40 | `0x01229610` | `0x00000000` |
    | xe41 | `0x0122a610` | `0x00000000` |
    | xe42 | `0x0122b610` | `0x00000000` |
    | xe43 | `0x0122c610` | `0x00000000` |
    | xe44 | `0x0122d610` | `0x00000000` |
    | xe45 | `0x0122e610` | `0x00000000` |
    | xe46 | `0x0122f610` | `0x00000000` |
    | xe47 | `0x01230610` | `0x00000000` |
    | xe48 | `0x01231610` | `0x00000000` |
    | xe49 | `0x01232610` | `0x00000000` |
    | xe50 | `0x01233610` | `0x00000000` |
    | xe51 | `0x01234610` | `0x00000000` |
    | lb0 | `0x01241610` | `0x00000000` |

---

## EGR_PORT_TO_NHI_MAPPINGr

- **Address:** `0x01200634`  ·  **Size:** 4 bytes
- **Function:** Maps Egress Port to a Next Hop Index.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | NEXT_HOP_INDEX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x01200634` | `0x00000000` |
    | xe0 | `0x01201634` | `0x00000000` |
    | xe1 | `0x01202634` | `0x00000000` |
    | xe2 | `0x01203634` | `0x00000000` |
    | xe3 | `0x01204634` | `0x00000000` |
    | xe4 | `0x01205634` | `0x00000000` |
    | xe5 | `0x01206634` | `0x00000000` |
    | xe6 | `0x01207634` | `0x00000000` |
    | xe7 | `0x01208634` | `0x00000000` |
    | xe8 | `0x01209634` | `0x00000000` |
    | xe9 | `0x0120a634` | `0x00000000` |
    | xe10 | `0x0120b634` | `0x00000000` |
    | xe11 | `0x0120c634` | `0x00000000` |
    | xe12 | `0x0120d634` | `0x00000000` |
    | xe13 | `0x0120e634` | `0x00000000` |
    | xe14 | `0x0120f634` | `0x00000000` |
    | xe15 | `0x01210634` | `0x00000000` |
    | xe16 | `0x01211634` | `0x00000000` |
    | xe17 | `0x01212634` | `0x00000000` |
    | xe18 | `0x01213634` | `0x00000000` |
    | xe19 | `0x01214634` | `0x00000000` |
    | xe20 | `0x01215634` | `0x00000000` |
    | xe21 | `0x01216634` | `0x00000000` |
    | xe22 | `0x01217634` | `0x00000000` |
    | xe23 | `0x01218634` | `0x00000000` |
    | xe24 | `0x01219634` | `0x00000000` |
    | xe25 | `0x0121a634` | `0x00000000` |
    | xe26 | `0x0121b634` | `0x00000000` |
    | xe27 | `0x0121c634` | `0x00000000` |
    | xe28 | `0x0121d634` | `0x00000000` |
    | xe29 | `0x0121e634` | `0x00000000` |
    | xe30 | `0x0121f634` | `0x00000000` |
    | xe31 | `0x01220634` | `0x00000000` |
    | xe32 | `0x01221634` | `0x00000000` |
    | xe33 | `0x01222634` | `0x00000000` |
    | xe34 | `0x01223634` | `0x00000000` |
    | xe35 | `0x01224634` | `0x00000000` |
    | xe36 | `0x01225634` | `0x00000000` |
    | xe37 | `0x01226634` | `0x00000000` |
    | xe38 | `0x01227634` | `0x00000000` |
    | xe39 | `0x01228634` | `0x00000000` |
    | xe40 | `0x01229634` | `0x00000000` |
    | xe41 | `0x0122a634` | `0x00000000` |
    | xe42 | `0x0122b634` | `0x00000000` |
    | xe43 | `0x0122c634` | `0x00000000` |
    | xe44 | `0x0122d634` | `0x00000000` |
    | xe45 | `0x0122e634` | `0x00000000` |
    | xe46 | `0x0122f634` | `0x00000000` |
    | xe47 | `0x01230634` | `0x00000000` |
    | xe48 | `0x01231634` | `0x00000000` |
    | xe49 | `0x01232634` | `0x00000000` |
    | xe50 | `0x01233634` | `0x00000000` |
    | xe51 | `0x01234634` | `0x00000000` |
    | lb0 | `0x01241634` | `0x00000000` |

---

## EGR_CONFIGr

- **Address:** `0x01280600`  ·  **Size:** 4 bytes
- **Function:** Configuration Register for the entire chip.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | INNER_TPID |
    | `[27:16]` | LEARN_VID |
    | `[28]` | USE_LEARN_VID |
    | `[29]` | SNAP_OTHER_DECODE_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280600` | `0x00008100` |

---

## EGR_CONFIG_1r

- **Address:** `0x01280601`  ·  **Size:** 4 bytes
- **Function:** Configuration Register Extension for the entire chip.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RING_MODE |
    | `[1]` | IPMC_ROUTE_SAME_VLAN |
    | `[2]` | FORCE_STATIC_MH_PFM |
    | `[4:3]` | MH_PFM |
    | `[5]` | DISABLE_PPD0_PRESERVE_QOS |
    | `[6]` | VT_SYS_PORT_OVERRIDE |
    | `[7]` | STRIP_PAD_EN |
    | `[8]` | IGNORE_HG_LAG_FAILOVER |
    | `[9]` | IGNORE_HG_HDR_DONOT_LEARN |
    | `[10]` | MIRROR_INVALID_VLAN_DROP |
    | `[11]` | BPDU_INVALID_VLAN_DROP |
    | `[12]` | DISABLE_VT_IF_IFP_CHANGE_VLAN |
    | `[13]` | DISABLE_MIRROR_CHECKS |
    | `[14]` | SET_PPD2_OPCODE |
    | `[15]` | UPDATE_HG_FABRIC_SRC_FOR_L2 |
    | `[16]` | UPDATE_HG_FABRIC_SRC_FOR_L3 |
    | `[17]` | PPD0_ADD_SYSTEM_SRC_PORT |
    | `[18]` | PPD2_ADD_SYSTEM_SRC_PORT |
    | `[19]` | DISABLE_PPD3_PRESERVE_QOS |
    | `[20]` | DISABLE_PPD2_PRESERVE_QOS |
    | `[27:21]` | CPU_PORTNUM |
    | `[28]` | QCN_SEND_NULL_CNTAG_IF_NO_CNTAG |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280601` | `0x00006001` |

---

## EGR_CONFIG_2r

- **Address:** `0x01280602`  ·  **Size:** 4 bytes
- **Function:** Egress Pipeline stage config register 2.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DO_NOT_MOD_TPID |
    | `[1]` | QCN_CNM_MESSAGE_DRAFT_24 |
    | `[2]` | USE_RBRIDGES_NICKNAMES_TABLE |
    | `[3]` | WESP_DRAFT_11 |
    | `[4]` | TRILL_L2_IS_IS_PARSE_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280602` | `0x0000001f` |

---

## EGR_BYPASS_CTRLr

- **Address:** `0x01280603`  ·  **Size:** 4 bytes
- **Function:** Egress Pipeline stage bypass control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EFP_BYPASS |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280603` | `0x00000000` |

---

## EGR_MIRROR_SELECTr

- **Address:** `0x01280609`  ·  **Size:** 4 bytes
- **Function:** Egress Mirror select register, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | MTP_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280609` | `0x0000000c` |

---

## EGR_L3_TUNNEL_PFM_VIDr

- **Address:** `0x0128060a`  ·  **Size:** 4 bytes
- **Function:** L3 Tunnel Terminated VLAN Override Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | VID |
    | `[12]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0128060a` | `0x00000000` |

---

## EGR_NIV_ETHERTYPEr

- **Address:** `0x0128060b`  ·  **Size:** 4 bytes
- **Function:** Egress NIV Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0128060b` | `0x00000000` |

---

## EGR_SD_TAG_CONTROLr

- **Address:** `0x01280611`  ·  **Size:** 4 bytes
- **Function:** Egress Mirror select register, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DO_NOT_MOD_TPID_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280611` | `0x00000000` |

---

## EGR_QCN_CNTAG_ETHERTYPEr

- **Address:** `0x01280620`  ·  **Size:** 4 bytes
- **Function:** QCN CNTAG Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280620` | `0x00000000` |

---

## EGR_QCN_CNM_ETHERTYPEr

- **Address:** `0x01280621`  ·  **Size:** 4 bytes
- **Function:** QCN CNM Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280621` | `0x00000000` |

---

## EGR_HBFC_CNTAG_ETHERTYPEr

- **Address:** `0x01280622`  ·  **Size:** 4 bytes
- **Function:** HBFC CNTAG Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280622` | `0x00000000` |

---

## EGR_HBFC_CNM_ETHERTYPEr

- **Address:** `0x01280623`  ·  **Size:** 4 bytes
- **Function:** HBFC CNM Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280623` | `0x00000000` |

---

## EGR_QCN_CNM_CONTROL_1r

- **Address:** `0x01280631`  ·  **Size:** 4 bytes
- **Function:** Egress CNM Control Register 1.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | QCN_CNM_DEFAULT_OUTER_VLAN_ID |
    | `[12]` | QCN_CNM_USE_DEFAULT_OUTER_VLAN_ID |
    | `[15:13]` | QCN_CNM_OUTER_DOT1P |
    | `[16]` | QCN_CNM_CHANGE_OUTER_DOT1P |
    | `[17]` | QCN_CNM_OUTER_CFI |
    | `[18]` | QCN_CNM_CHANGE_OUTER_CFI |
    | `[21:19]` | QCN_CNM_INNER_DOT1P |
    | `[22]` | QCN_CNM_CHANGE_INNER_DOT1P |
    | `[23]` | QCN_CNM_INNER_CFI |
    | `[24]` | QCN_CNM_CHANGE_INNER_CFI |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280631` | `0x00000000` |

---

## EGR_QCN_CNM_CONTROL_2r

- **Address:** `0x01280632`  ·  **Size:** 4 bytes
- **Function:** Egress CNM Control Register 2.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | QCN_CNM_DEFAULT_OUTER_TPID |
    | `[16]` | QCN_CNM_USE_DEFAULT_OUTER_TPID |
    | `[20:17]` | QCN_CNM_VERSION |
    | `[21]` | QCN_CNM_CPID_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280632` | `0x00000000` |

---

## EGR_LOOPBACK_PORT_TPIDr

- **Address:** `0x01280633`  ·  **Size:** 4 bytes
- **Function:** Loopback Port's TPID Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280633` | `0x00000000` |

---

## EGR_EL3_ECC_PARITY_CONTROLr

- **Address:** `0x01280700`  ·  **Size:** 4 bytes
- **Function:** EGR_L3_INTF_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_L3_NEXT_HOP_PARITY_EN |
    | `[1]` | EGR_L3_INTF_PARITY_EN |
    | `[2]` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_EN |
    | `[3]` | EGR_MAC_DA_PROFILE_PARITY_EN |
    | `[4]` | EGR_DVP_ATTRIBUTE_PARITY_EN |
    | `[5]` | EGR_VFI_PARITY_EN |
    | `[6]` | EGR_IPMC_PARITY_EN |
    | `[7]` | EGR_PORT_PARITY_EN |
    | `[8]` | EGR_MPB_ECC_EN |
    | `[9]` | EGR_MAP_MH_PARITY_EN |
    | `[10]` | EGR_VLAN_CONTROL_1_PARITY_EN |
    | `[11]` | EGR_IPMC_CFG2_PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280700` | `0x00000fff` |

---

## EGR_EL3_STBY_CONTROLr

- **Address:** `0x01280718`  ·  **Size:** 4 bytes
- **Function:** Control register for standby bits of El3 and Einitbuf stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_INITBUF_STBY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280718` | `0x00000000` |

---

## EGR_EL3_PM_CONTROLr

- **Address:** `0x01280719`  ·  **Size:** 4 bytes
- **Function:** Control register for pm bits of El3 stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_L3_NEXT_HOP_PM |
    | `[1]` | EGR_L3_INTF_PM |
    | `[2]` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PM |
    | `[3]` | EGR_MAC_DA_PROFILE_PM |
    | `[4]` | EGR_DVP_ATTRIBUTE_PM |
    | `[5]` | EGR_VFI_PM |
    | `[6]` | EGR_MAP_MH_PM |
    | `[7]` | EGR_IPMC_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280719` | `0x00000000` |

---

## EGR_EL3_RAM_CONTROLr

- **Address:** `0x0128071a`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of El3 stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | EGR_L3_NEXT_HOP_TM |
    | `[9:5]` | EGR_L3_INTF_TM |
    | `[14:10]` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_TM |
    | `[19:15]` | EGR_MAC_DA_PROFILE_TM |
    | `[24:20]` | EGR_DVP_ATTRIBUTE_TM |
    | `[29:25]` | EGR_VFI_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0128071a` | `0x00000000` |

---

## EGR_EL3_RAM_CONTROL_2r

- **Address:** `0x0128071b`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of El3 stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | EGR_MAP_MH_TM |
    | `[9:5]` | EGR_IPMC_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0128071b` | `0x00000000` |

---

## EGR_MPB_ECC_STATUS_INTRr

- **Address:** `0x01280d01`  ·  **Size:** 4 bytes
- **Function:** ECC interrupt status register for MPB memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[18:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d01` | `0x00000000` |

---

## EGR_L3_NEXT_HOP_PARITY_STATUS_INTRr

- **Address:** `0x01280d02`  ·  **Size:** 4 bytes
- **Function:** EGR_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d02` | `0x00000000` |

---

## EGR_L3_NEXT_HOP_PARITY_STATUS_NACKr

- **Address:** `0x01280d03`  ·  **Size:** 4 bytes
- **Function:** EGR_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d03` | `0x00000000` |

---

## EGR_L3_INTF_PARITY_STATUS_INTRr

- **Address:** `0x01280d04`  ·  **Size:** 4 bytes
- **Function:** EGR_L3_INTF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d04` | `0x00000000` |

---

## EGR_L3_INTF_PARITY_STATUS_NACKr

- **Address:** `0x01280d05`  ·  **Size:** 4 bytes
- **Function:** EGR_L3_INTF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d05` | `0x00000000` |

---

## EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x01280d06`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d06` | `0x00000000` |

---

## EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x01280d07`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d07` | `0x00000000` |

---

## EGR_MAC_DA_PROFILE_PARITY_STATUS_INTRr

- **Address:** `0x01280d08`  ·  **Size:** 4 bytes
- **Function:** EGR_MAC_DA_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d08` | `0x00000000` |

---

## EGR_MAC_DA_PROFILE_PARITY_STATUS_NACKr

- **Address:** `0x01280d09`  ·  **Size:** 4 bytes
- **Function:** EGR_MAC_DA_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d09` | `0x00000000` |

---

## EGR_DVP_ATTRIBUTE_PARITY_STATUS_INTRr

- **Address:** `0x01280d0a`  ·  **Size:** 4 bytes
- **Function:** EGR_DVP_ATTRIBUTE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0a` | `0x00000000` |

---

## EGR_DVP_ATTRIBUTE_PARITY_STATUS_NACKr

- **Address:** `0x01280d0b`  ·  **Size:** 4 bytes
- **Function:** EGR_DVP_ATTRIBUTE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0b` | `0x00000000` |

---

## EGR_VFI_PARITY_STATUS_INTRr

- **Address:** `0x01280d0c`  ·  **Size:** 4 bytes
- **Function:** EGR_VFI_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0c` | `0x00000000` |

---

## EGR_VFI_PARITY_STATUS_NACKr

- **Address:** `0x01280d0d`  ·  **Size:** 4 bytes
- **Function:** EGR_VFI_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0d` | `0x00000000` |

---

## EGR_PORT_PARITY_STATUS_INTRr

- **Address:** `0x01280d0e`  ·  **Size:** 4 bytes
- **Function:** EGR_PORT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0e` | `0x00000000` |

---

## EGR_PORT_PARITY_STATUS_NACKr

- **Address:** `0x01280d0f`  ·  **Size:** 4 bytes
- **Function:** EGR_PORT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d0f` | `0x00000000` |

---

## EGR_IPMC_PARITY_STATUS_INTRr

- **Address:** `0x01280d10`  ·  **Size:** 4 bytes
- **Function:** EGR_IPMC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d10` | `0x00000000` |

---

## EGR_IPMC_PARITY_STATUS_NACKr

- **Address:** `0x01280d11`  ·  **Size:** 4 bytes
- **Function:** EGR_IPMC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d11` | `0x00000000` |

---

## EGR_MAP_MH_PARITY_STATUS_INTRr

- **Address:** `0x01280d12`  ·  **Size:** 4 bytes
- **Function:** EGR_MAP_MH_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d12` | `0x00000000` |

---

## EGR_MAP_MH_PARITY_STATUS_NACKr

- **Address:** `0x01280d13`  ·  **Size:** 4 bytes
- **Function:** EGR_MAP_MH_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d13` | `0x00000000` |

---

## EGR_VLAN_CONTROL_1_PARITY_STATUS_INTRr

- **Address:** `0x01280d14`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_CONTROL_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d14` | `0x00000000` |

---

## EGR_VLAN_CONTROL_1_PARITY_STATUS_NACKr

- **Address:** `0x01280d15`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_CONTROL_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d15` | `0x00000000` |

---

## EGR_IPMC_CFG2_PARITY_STATUS_INTRr

- **Address:** `0x01280d16`  ·  **Size:** 4 bytes
- **Function:** EGR_IPMC_CFG2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d16` | `0x00000000` |

---

## EGR_IPMC_CFG2_PARITY_STATUS_NACKr

- **Address:** `0x01280d17`  ·  **Size:** 4 bytes
- **Function:** EGR_IPMC_CFG2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x01280d17` | `0x00000000` |

---

## EGR_VLAN_CONTROL_2r

- **Address:** `0x02200611`  ·  **Size:** 4 bytes
- **Function:** Controls Vlan Translate and VLAN membership related functions.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | OTAG_VPTAG |
    | `[15:0]` | VPTAG |
    | `[11:0]` | OVID |
    | `[15:12]` | OPRI_MAPPING_PTR |
    | `[14:12]` | OPRI |
    | `[15]` | OCFI |
    | `[16]` | OTAG_VPTAG_SEL |
    | `[17]` | OPRI_CFI_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02200611` | `0x00000000` |
    | xe0 | `0x02201611` | `0x00000000` |
    | xe1 | `0x02202611` | `0x00000000` |
    | xe2 | `0x02203611` | `0x00000000` |
    | xe3 | `0x02204611` | `0x00000000` |
    | xe4 | `0x02205611` | `0x00000000` |
    | xe5 | `0x02206611` | `0x00000000` |
    | xe6 | `0x02207611` | `0x00000000` |
    | xe7 | `0x02208611` | `0x00000000` |
    | xe8 | `0x02209611` | `0x00000000` |
    | xe9 | `0x0220a611` | `0x00000000` |
    | xe10 | `0x0220b611` | `0x00000000` |
    | xe11 | `0x0220c611` | `0x00000000` |
    | xe12 | `0x0220d611` | `0x00000000` |
    | xe13 | `0x0220e611` | `0x00000000` |
    | xe14 | `0x0220f611` | `0x00000000` |
    | xe15 | `0x02210611` | `0x00000000` |
    | xe16 | `0x02211611` | `0x00000000` |
    | xe17 | `0x02212611` | `0x00000000` |
    | xe18 | `0x02213611` | `0x00000000` |
    | xe19 | `0x02214611` | `0x00000000` |
    | xe20 | `0x02215611` | `0x00000000` |
    | xe21 | `0x02216611` | `0x00000000` |
    | xe22 | `0x02217611` | `0x00000000` |
    | xe23 | `0x02218611` | `0x00000000` |
    | xe24 | `0x02219611` | `0x00000000` |
    | xe25 | `0x0221a611` | `0x00000000` |
    | xe26 | `0x0221b611` | `0x00000000` |
    | xe27 | `0x0221c611` | `0x00000000` |
    | xe28 | `0x0221d611` | `0x00000000` |
    | xe29 | `0x0221e611` | `0x00000000` |
    | xe30 | `0x0221f611` | `0x00000000` |
    | xe31 | `0x02220611` | `0x00000000` |
    | xe32 | `0x02221611` | `0x00000000` |
    | xe33 | `0x02222611` | `0x00000000` |
    | xe34 | `0x02223611` | `0x00000000` |
    | xe35 | `0x02224611` | `0x00000000` |
    | xe36 | `0x02225611` | `0x00000000` |
    | xe37 | `0x02226611` | `0x00000000` |
    | xe38 | `0x02227611` | `0x00000000` |
    | xe39 | `0x02228611` | `0x00000000` |
    | xe40 | `0x02229611` | `0x00000000` |
    | xe41 | `0x0222a611` | `0x00000000` |
    | xe42 | `0x0222b611` | `0x00000000` |
    | xe43 | `0x0222c611` | `0x00000000` |
    | xe44 | `0x0222d611` | `0x00000000` |
    | xe45 | `0x0222e611` | `0x00000000` |
    | xe46 | `0x0222f611` | `0x00000000` |
    | xe47 | `0x02230611` | `0x00000000` |
    | xe48 | `0x02231611` | `0x00000000` |
    | xe49 | `0x02232611` | `0x00000000` |
    | xe50 | `0x02233611` | `0x00000000` |
    | xe51 | `0x02234611` | `0x00000000` |
    | lb0 | `0x02241611` | `0x00000000` |

---

## EGR_VLAN_CONTROL_3r

- **Address:** `0x02200612`  ·  **Size:** 4 bytes
- **Function:** Controls Vlan Translate and VLAN membership related functions.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | IVID |
    | `[15:12]` | IPRI_MAPPING_PTR |
    | `[14:12]` | IPRI |
    | `[15]` | ICFI |
    | `[21:16]` | TAG_ACTION_PROFILE_PTR |
    | `[22]` | MH_INGRESS_TAGGED_SEL |
    | `[23]` | IPRI_CFI_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02200612` | `0x00000000` |
    | xe0 | `0x02201612` | `0x00000000` |
    | xe1 | `0x02202612` | `0x00000000` |
    | xe2 | `0x02203612` | `0x00000000` |
    | xe3 | `0x02204612` | `0x00000000` |
    | xe4 | `0x02205612` | `0x00000000` |
    | xe5 | `0x02206612` | `0x00000000` |
    | xe6 | `0x02207612` | `0x00000000` |
    | xe7 | `0x02208612` | `0x00000000` |
    | xe8 | `0x02209612` | `0x00000000` |
    | xe9 | `0x0220a612` | `0x00000000` |
    | xe10 | `0x0220b612` | `0x00000000` |
    | xe11 | `0x0220c612` | `0x00000000` |
    | xe12 | `0x0220d612` | `0x00000000` |
    | xe13 | `0x0220e612` | `0x00000000` |
    | xe14 | `0x0220f612` | `0x00000000` |
    | xe15 | `0x02210612` | `0x00000000` |
    | xe16 | `0x02211612` | `0x00000000` |
    | xe17 | `0x02212612` | `0x00000000` |
    | xe18 | `0x02213612` | `0x00000000` |
    | xe19 | `0x02214612` | `0x00000000` |
    | xe20 | `0x02215612` | `0x00000000` |
    | xe21 | `0x02216612` | `0x00000000` |
    | xe22 | `0x02217612` | `0x00000000` |
    | xe23 | `0x02218612` | `0x00000000` |
    | xe24 | `0x02219612` | `0x00000000` |
    | xe25 | `0x0221a612` | `0x00000000` |
    | xe26 | `0x0221b612` | `0x00000000` |
    | xe27 | `0x0221c612` | `0x00000000` |
    | xe28 | `0x0221d612` | `0x00000000` |
    | xe29 | `0x0221e612` | `0x00000000` |
    | xe30 | `0x0221f612` | `0x00000000` |
    | xe31 | `0x02220612` | `0x00000000` |
    | xe32 | `0x02221612` | `0x00000000` |
    | xe33 | `0x02222612` | `0x00000000` |
    | xe34 | `0x02223612` | `0x00000000` |
    | xe35 | `0x02224612` | `0x00000000` |
    | xe36 | `0x02225612` | `0x00000000` |
    | xe37 | `0x02226612` | `0x00000000` |
    | xe38 | `0x02227612` | `0x00000000` |
    | xe39 | `0x02228612` | `0x00000000` |
    | xe40 | `0x02229612` | `0x00000000` |
    | xe41 | `0x0222a612` | `0x00000000` |
    | xe42 | `0x0222b612` | `0x00000000` |
    | xe43 | `0x0222c612` | `0x00000000` |
    | xe44 | `0x0222d612` | `0x00000000` |
    | xe45 | `0x0222e612` | `0x00000000` |
    | xe46 | `0x0222f612` | `0x00000000` |
    | xe47 | `0x02230612` | `0x00000000` |
    | xe48 | `0x02231612` | `0x00000000` |
    | xe49 | `0x02232612` | `0x00000000` |
    | xe50 | `0x02233612` | `0x00000000` |
    | xe51 | `0x02234612` | `0x00000000` |
    | lb0 | `0x02241612` | `0x00000000` |

---

## EGR_PVLAN_EPORT_CONTROLr

- **Address:** `0x02200613`  ·  **Size:** 4 bytes
- **Function:** Private VLAN Egress-port Control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PVLAN_PVID |
    | `[12]` | PVLAN_ENABLE |
    | `[15:13]` | PVLAN_PRI |
    | `[16]` | PVLAN_UNTAG |
    | `[17]` | PVLAN_RPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02200613` | `0x00000000` |
    | xe0 | `0x02201613` | `0x00000000` |
    | xe1 | `0x02202613` | `0x00000000` |
    | xe2 | `0x02203613` | `0x00000000` |
    | xe3 | `0x02204613` | `0x00000000` |
    | xe4 | `0x02205613` | `0x00000000` |
    | xe5 | `0x02206613` | `0x00000000` |
    | xe6 | `0x02207613` | `0x00000000` |
    | xe7 | `0x02208613` | `0x00000000` |
    | xe8 | `0x02209613` | `0x00000000` |
    | xe9 | `0x0220a613` | `0x00000000` |
    | xe10 | `0x0220b613` | `0x00000000` |
    | xe11 | `0x0220c613` | `0x00000000` |
    | xe12 | `0x0220d613` | `0x00000000` |
    | xe13 | `0x0220e613` | `0x00000000` |
    | xe14 | `0x0220f613` | `0x00000000` |
    | xe15 | `0x02210613` | `0x00000000` |
    | xe16 | `0x02211613` | `0x00000000` |
    | xe17 | `0x02212613` | `0x00000000` |
    | xe18 | `0x02213613` | `0x00000000` |
    | xe19 | `0x02214613` | `0x00000000` |
    | xe20 | `0x02215613` | `0x00000000` |
    | xe21 | `0x02216613` | `0x00000000` |
    | xe22 | `0x02217613` | `0x00000000` |
    | xe23 | `0x02218613` | `0x00000000` |
    | xe24 | `0x02219613` | `0x00000000` |
    | xe25 | `0x0221a613` | `0x00000000` |
    | xe26 | `0x0221b613` | `0x00000000` |
    | xe27 | `0x0221c613` | `0x00000000` |
    | xe28 | `0x0221d613` | `0x00000000` |
    | xe29 | `0x0221e613` | `0x00000000` |
    | xe30 | `0x0221f613` | `0x00000000` |
    | xe31 | `0x02220613` | `0x00000000` |
    | xe32 | `0x02221613` | `0x00000000` |
    | xe33 | `0x02222613` | `0x00000000` |
    | xe34 | `0x02223613` | `0x00000000` |
    | xe35 | `0x02224613` | `0x00000000` |
    | xe36 | `0x02225613` | `0x00000000` |
    | xe37 | `0x02226613` | `0x00000000` |
    | xe38 | `0x02227613` | `0x00000000` |
    | xe39 | `0x02228613` | `0x00000000` |
    | xe40 | `0x02229613` | `0x00000000` |
    | xe41 | `0x0222a613` | `0x00000000` |
    | xe42 | `0x0222b613` | `0x00000000` |
    | xe43 | `0x0222c613` | `0x00000000` |
    | xe44 | `0x0222d613` | `0x00000000` |
    | xe45 | `0x0222e613` | `0x00000000` |
    | xe46 | `0x0222f613` | `0x00000000` |
    | xe47 | `0x02230613` | `0x00000000` |
    | xe48 | `0x02231613` | `0x00000000` |
    | xe49 | `0x02232613` | `0x00000000` |
    | xe50 | `0x02233613` | `0x00000000` |
    | xe51 | `0x02234613` | `0x00000000` |
    | lb0 | `0x02241613` | `0x00000000` |

---

## EGR_INGRESS_PORT_TPID_SELECTr

- **Address:** `0x02200614`  ·  **Size:** 4 bytes
- **Function:** Controls per ingress port outgoing tpid selection.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | TPID_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02200614` | `0x00000000` |
    | xe0 | `0x02201614` | `0x00000000` |
    | xe1 | `0x02202614` | `0x00000000` |
    | xe2 | `0x02203614` | `0x00000000` |
    | xe3 | `0x02204614` | `0x00000000` |
    | xe4 | `0x02205614` | `0x00000000` |
    | xe5 | `0x02206614` | `0x00000000` |
    | xe6 | `0x02207614` | `0x00000000` |
    | xe7 | `0x02208614` | `0x00000000` |
    | xe8 | `0x02209614` | `0x00000000` |
    | xe9 | `0x0220a614` | `0x00000000` |
    | xe10 | `0x0220b614` | `0x00000000` |
    | xe11 | `0x0220c614` | `0x00000000` |
    | xe12 | `0x0220d614` | `0x00000000` |
    | xe13 | `0x0220e614` | `0x00000000` |
    | xe14 | `0x0220f614` | `0x00000000` |
    | xe15 | `0x02210614` | `0x00000000` |
    | xe16 | `0x02211614` | `0x00000000` |
    | xe17 | `0x02212614` | `0x00000000` |
    | xe18 | `0x02213614` | `0x00000000` |
    | xe19 | `0x02214614` | `0x00000000` |
    | xe20 | `0x02215614` | `0x00000000` |
    | xe21 | `0x02216614` | `0x00000000` |
    | xe22 | `0x02217614` | `0x00000000` |
    | xe23 | `0x02218614` | `0x00000000` |
    | xe24 | `0x02219614` | `0x00000000` |
    | xe25 | `0x0221a614` | `0x00000000` |
    | xe26 | `0x0221b614` | `0x00000000` |
    | xe27 | `0x0221c614` | `0x00000000` |
    | xe28 | `0x0221d614` | `0x00000000` |
    | xe29 | `0x0221e614` | `0x00000000` |
    | xe30 | `0x0221f614` | `0x00000000` |
    | xe31 | `0x02220614` | `0x00000000` |
    | xe32 | `0x02221614` | `0x00000000` |
    | xe33 | `0x02222614` | `0x00000000` |
    | xe34 | `0x02223614` | `0x00000000` |
    | xe35 | `0x02224614` | `0x00000000` |
    | xe36 | `0x02225614` | `0x00000000` |
    | xe37 | `0x02226614` | `0x00000000` |
    | xe38 | `0x02227614` | `0x00000000` |
    | xe39 | `0x02228614` | `0x00000000` |
    | xe40 | `0x02229614` | `0x00000000` |
    | xe41 | `0x0222a614` | `0x00000000` |
    | xe42 | `0x0222b614` | `0x00000000` |
    | xe43 | `0x0222c614` | `0x00000000` |
    | xe44 | `0x0222d614` | `0x00000000` |
    | xe45 | `0x0222e614` | `0x00000000` |
    | xe46 | `0x0222f614` | `0x00000000` |
    | xe47 | `0x02230614` | `0x00000000` |
    | xe48 | `0x02231614` | `0x00000000` |
    | xe49 | `0x02232614` | `0x00000000` |
    | xe50 | `0x02233614` | `0x00000000` |
    | xe51 | `0x02234614` | `0x00000000` |
    | lb0 | `0x02241614` | `0x00000000` |

---

## EGR_VLAN_LOGIC_TO_PHYS_MAPr

- **Address:** `0x02200620`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PHYSICAL_PORT_NUM |
    | `[6:0]` | PHYS_PORT |

---

## EGR_OUTER_TPIDr

- **Address:** `0x02280600`  ·  **Size:** 4 bytes
- **Function:** Egress Outer TPID register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

---

## EGR_OUTER_TPID_0r

- **Address:** `0x02280600`  ·  **Size:** 4 bytes
- **Function:** Egress outer TPID register #0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280600` | `0x00008100` |

---

## EGR_OUTER_TPID_1r

- **Address:** `0x02280601`  ·  **Size:** 4 bytes
- **Function:** Egress outer TPID register #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280601` | `0x00009100` |

---

## EGR_OUTER_TPID_2r

- **Address:** `0x02280602`  ·  **Size:** 4 bytes
- **Function:** Egress outer TPID register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280602` | `0x000088a8` |

---

## EGR_OUTER_TPID_3r

- **Address:** `0x02280603`  ·  **Size:** 4 bytes
- **Function:** Egress outer TPID register #3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280603` | `0x00000000` |

---

## EGR_VLAN_XLATE_HASH_CONTROLr

- **Address:** `0x02280610`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_XLATE_HASH_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | HASH_SELECT_A |
    | `[5:3]` | HASH_SELECT_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280610` | `0x0000000a` |

---

## EGR_TUNNEL_ID_MASKr

- **Address:** `0x02280615`  ·  **Size:** 4 bytes
- **Function:** Global ID mask value for Tunnel Pkts.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | FRAG_ID_MASK |
    | `[16]` | SHARED_FRAG_ID_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280615` | `0x00000000` |

---

## EGR_VLAN_PARITY_CONTROLr

- **Address:** `0x02280700`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_VLAN_PARITY_EN |
    | `[1]` | EGR_VLAN_STG_PARITY_EN |
    | `[2]` | EGR_VLAN_XLATE_PARITY_EN |
    | `[3]` | EGR_IP_TUNNEL_PARITY_EN |
    | `[4]` | EGR_MPLS_EXP_MAPPING_2_PARITY_EN |
    | `[5]` | EGR_MPLS_PRI_MAPPING_PARITY_EN |
    | `[6]` | EGR_PRI_CNG_MAP_PARITY_EN |
    | `[7]` | EGR_DSCP_TABLE_PARITY_EN |
    | `[8]` | EGR_FRAGMENT_ID_TABLE_PARITY_EN |
    | `[9]` | EGR_GPP_ATTRIBUTES_MODBASE_PARITY_EN |
    | `[10]` | EGR_GPP_ATTRIBUTES_PARITY_EN |
    | `[11]` | EGR_MPLS_EXP_MAPPING_1_PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280700` | `0x00000fff` |

---

## EGR_VLAN_RAM_CONTROL_1r

- **Address:** `0x0228071b`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_GPP_ATTRIBUTES_MODBASE_TM |
    | `[19:10]` | EGR_GPP_ATTRIBUTES_TM |
    | `[29:20]` | EGR_FRAGMENT_ID_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0228071b` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_2r

- **Address:** `0x0228071c`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Evxlt stage memories (also used for Ehcpm and Einitbuf stage memories)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | EGR_VLAN_TM |
    | `[9:5]` | EGR_VLAN_STG_TM |
    | `[14:10]` | EGR_DSCP_TM |
    | `[19:15]` | EGR_PRI_CNG_MAP_TM |
    | `[27:20]` | INITBUF_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0228071c` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_3r

- **Address:** `0x0228071d`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_VLAN_XLATE_TM |
    | `[14:10]` | EGR_IP_TUNNEL_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0228071d` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_4r

- **Address:** `0x0228071e`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_MPLS_EXP_MAPPING_2_TM |
    | `[19:10]` | EGR_MPLS_EXP_MAPPING_1_TM |
    | `[29:20]` | EGR_MPLS_PRI_MAPPING_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0228071e` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_DCMr

- **Address:** `0x0228071f`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_VLAN_XLATE |
    | `[1]` | EGR_GPP_ATTRIBUTES |
    | `[2]` | EGR_GPP_ATTRIBUTES_MODBASE |
    | `[3]` | EGR_MPLS_EXP_MAPPING_2 |
    | `[4]` | EGR_MPLS_EXP_MAPPING_1 |
    | `[5]` | EGR_MPLS_PRI_MAPPING |
    | `[6]` | EGR_FRAGMENT_ID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0228071f` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_PDAHr

- **Address:** `0x02280720`  ·  **Size:** 4 bytes
- **Function:** Control register for PDAH bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | EGR_VLAN_XLATE |
    | `[9:2]` | EGR_GPP_ATTRIBUTES |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280720` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_STBYr

- **Address:** `0x02280721`  ·  **Size:** 4 bytes
- **Function:** Control register for STBY bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | INITBUF |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280721` | `0x00000000` |

---

## EGR_VLAN_RAM_CONTROL_PMr

- **Address:** `0x02280722`  ·  **Size:** 4 bytes
- **Function:** Control register for pm bits of Evxlt stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_VLAN_XLATE |
    | `[1]` | EGR_VLAN |
    | `[2]` | EGR_VLAN_STG |
    | `[3]` | EGR_PRI_CNG_MAP |
    | `[4]` | EGR_IP_TUNNEL |
    | `[5]` | EGR_GPP_ATTRIBUTES |
    | `[6]` | EGR_GPP_ATTRIBUTES_MODBASE |
    | `[7]` | EGR_FRAGMENT_ID |
    | `[8]` | EGR_DSCP |
    | `[9]` | EGR_MPLS_EXP_MAPPING_2 |
    | `[10]` | EGR_MPLS_EXP_MAPPING_1 |
    | `[11]` | EGR_MPLS_PRI_MAPPING |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280722` | `0x00000000` |

---

## EGR_INTR0_ENABLEr

- **Address:** `0x02280724`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for EGR_INTR0_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_NHOP_PAR_ERR |
    | `[1]` | EGR_L3_INTF_PAR_ERR |
    | `[2]` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PAR_ERR |
    | `[3]` | EGR_VLAN_PAR_ERR |
    | `[4]` | EGR_VLAN_STG_PAR_ERR |
    | `[5]` | EGR_IP_TUNNEL_PAR_ERR |
    | `[6]` | EGR_VLAN_XLATE_PAR_ERR |
    | `[7]` | EGR_FRAGMENT_ID_TABLE_PAR_ERR |
    | `[8]` | EGR_INITBUF_ECC_ERR |
    | `[9]` | EGR_PORT_PAR_ERR |
    | `[10]` | EGR_GPP_ATTRIBUTES_PAR_ERR |
    | `[11]` | EGR_MOD_MAP_TABLE_PAR_ERR |
    | `[12]` | EGR_MAC_DA_PROFILE_PAR_ERR |
    | `[13]` | EGR_DVP_ATTRIBUTE_PAR_ERR |
    | `[14]` | EGR_VFI_PAR_ERR |
    | `[15]` | EGR_IPMC_PAR_ERR |
    | `[16]` | EGR_MPLS_EXP_MAPPING_2_PAR_ERR |
    | `[17]` | EGR_MPLS_PRI_MAPPING_PAR_ERR |
    | `[18]` | EGR_PRI_CNG_MAP_PAR_ERR |
    | `[19]` | EGR_DSCP_TABLE_PAR_ERR |
    | `[20]` | EGR_MPB_ECC_ERR |
    | `[21]` | EGR_MAP_MH_PAR_ERR |
    | `[22]` | EGR_VLAN_CONTROL_1_PAR_ERR |
    | `[23]` | EGR_IPMC_CFG2_PAR_ERR |
    | `[24]` | EGR_GPP_ATTRIBUTES_MODBASE_PAR_ERR |
    | `[25]` | EGR_MPLS_EXP_MAPPING_1_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280724` | `0x03ffffff` |

---

## EGR_VLAN_PARITY_STATUS_INTRr

- **Address:** `0x02280d01`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d01` | `0x00000000` |

---

## EGR_VLAN_PARITY_STATUS_NACKr

- **Address:** `0x02280d02`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d02` | `0x00000000` |

---

## EGR_VLAN_STG_PARITY_STATUS_INTRr

- **Address:** `0x02280d03`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_STG_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d03` | `0x00000000` |

---

## EGR_VLAN_STG_PARITY_STATUS_NACKr

- **Address:** `0x02280d04`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_STG_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d04` | `0x00000000` |

---

## EGR_VLAN_XLATE_PARITY_STATUS_INTR_0r

- **Address:** `0x02280d05`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_XLATE_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d05` | `0x00000000` |

---

## EGR_VLAN_XLATE_PARITY_STATUS_INTR_1r

- **Address:** `0x02280d06`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_XLATE_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d06` | `0x00000000` |

---

## EGR_VLAN_XLATE_PARITY_STATUS_NACK_0r

- **Address:** `0x02280d07`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_XLATE_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d07` | `0x00000000` |

---

## EGR_VLAN_XLATE_PARITY_STATUS_NACK_1r

- **Address:** `0x02280d08`  ·  **Size:** 4 bytes
- **Function:** EGR_VLAN_XLATE_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d08` | `0x00000000` |

---

## EGR_IP_TUNNEL_PARITY_STATUS_INTRr

- **Address:** `0x02280d09`  ·  **Size:** 4 bytes
- **Function:** EGR_IP_TUNNEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d09` | `0x00000000` |

---

## EGR_IP_TUNNEL_PARITY_STATUS_NACKr

- **Address:** `0x02280d0a`  ·  **Size:** 4 bytes
- **Function:** EGR_IP_TUNNEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0a` | `0x00000000` |

---

## EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_INTRr

- **Address:** `0x02280d0b`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0b` | `0x00000000` |

---

## EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_NACKr

- **Address:** `0x02280d0c`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0c` | `0x00000000` |

---

## EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_INTRr

- **Address:** `0x02280d0d`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0d` | `0x00000000` |

---

## EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_NACKr

- **Address:** `0x02280d0e`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0e` | `0x00000000` |

---

## EGR_MPLS_PRI_MAPPING_PARITY_STATUS_INTRr

- **Address:** `0x02280d0f`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_PRI_MAPPING_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d0f` | `0x00000000` |

---

## EGR_MPLS_PRI_MAPPING_PARITY_STATUS_NACKr

- **Address:** `0x02280d10`  ·  **Size:** 4 bytes
- **Function:** EGR_MPLS_PRI_MAPPING_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d10` | `0x00000000` |

---

## EGR_PRI_CNG_MAP_PARITY_STATUS_INTRr

- **Address:** `0x02280d11`  ·  **Size:** 4 bytes
- **Function:** EGR_PRI_CNG_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d11` | `0x00000000` |

---

## EGR_PRI_CNG_MAP_PARITY_STATUS_NACKr

- **Address:** `0x02280d12`  ·  **Size:** 4 bytes
- **Function:** EGR_PRI_CNG_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d12` | `0x00000000` |

---

## EGR_DSCP_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x02280d13`  ·  **Size:** 4 bytes
- **Function:** EGR_DSCP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d13` | `0x00000000` |

---

## EGR_DSCP_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x02280d14`  ·  **Size:** 4 bytes
- **Function:** EGR_DSCP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d14` | `0x00000000` |

---

## EGR_FRAGMENT_ID_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x02280d15`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for FRAGMENT_ID memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d15` | `0x00000000` |

---

## EGR_FRAGMENT_ID_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x02280d16`  ·  **Size:** 4 bytes
- **Function:** PARITY nack status register for FRAGMENT_ID memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d16` | `0x00000000` |

---

## EGR_GPP_ATTRIBUTES_MODBASE_PARITY_STATUS_INTRr

- **Address:** `0x02280d17`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for GPP_ATTRIBUTES_MODBASE memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d17` | `0x00000000` |

---

## EGR_GPP_ATTRIBUTES_MODBASE_PARITY_STATUS_NACKr

- **Address:** `0x02280d18`  ·  **Size:** 4 bytes
- **Function:** PARITY nack status register for GPP_ATTRIBUTES_MODBASE memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d18` | `0x00000000` |

---

## EGR_GPP_ATTRIBUTES_PARITY_STATUS_INTRr

- **Address:** `0x02280d19`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for GPP_ATTRIBUTES memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d19` | `0x00000000` |

---

## EGR_GPP_ATTRIBUTES_PARITY_STATUS_NACKr

- **Address:** `0x02280d1a`  ·  **Size:** 4 bytes
- **Function:** PARITY nack status register for GPP_ATTRIBUTES memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d1a` | `0x00000000` |

---

## EGR_INTR0_STATUSr

- **Address:** `0x02280d23`  ·  **Size:** 4 bytes
- **Function:** EP Interrupt 0  Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_NHOP_PAR_ERR |
    | `[1]` | EGR_L3_INTF_PAR_ERR |
    | `[2]` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PAR_ERR |
    | `[3]` | EGR_VLAN_PAR_ERR |
    | `[4]` | EGR_VLAN_STG_PAR_ERR |
    | `[5]` | EGR_IP_TUNNEL_PAR_ERR |
    | `[6]` | EGR_VLAN_XLATE_PAR_ERR |
    | `[7]` | EGR_FRAGMENT_ID_TABLE_PAR_ERR |
    | `[8]` | EGR_INITBUF_ECC_ERR |
    | `[9]` | EGR_PORT_PAR_ERR |
    | `[10]` | EGR_GPP_ATTRIBUTES_PAR_ERR |
    | `[11]` | EGR_MOD_MAP_TABLE_PAR_ERR |
    | `[12]` | EGR_MAC_DA_PROFILE_PAR_ERR |
    | `[13]` | EGR_DVP_ATTRIBUTE_PAR_ERR |
    | `[14]` | EGR_VFI_PAR_ERR |
    | `[15]` | EGR_IPMC_PAR_ERR |
    | `[16]` | EGR_MPLS_EXP_MAPPING_2_PAR_ERR |
    | `[17]` | EGR_MPLS_PRI_MAPPING_PAR_ERR |
    | `[18]` | EGR_PRI_CNG_MAP_PAR_ERR |
    | `[19]` | EGR_DSCP_TABLE_PAR_ERR |
    | `[20]` | EGR_MPB_ECC_ERR |
    | `[21]` | EGR_MAP_MH_PAR_ERR |
    | `[22]` | EGR_VLAN_CONTROL_1_PAR_ERR |
    | `[23]` | EGR_IPMC_CFG2_PAR_ERR |
    | `[24]` | EGR_GPP_ATTRIBUTES_MODBASE_PAR_ERR |
    | `[25]` | EGR_MPLS_EXP_MAPPING_1_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x02280d23` | `0x00000000` |

---

## EGR_DBGr

- **Address:** `0x03200600`  ·  **Size:** 4 bytes
- **Function:** Configuration Register for a Port. This is same for GE, 10GE, Higig Ports.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RESURRECT |
    | `[1]` | DISABLE_CRC_REGEN |
    | `[2]` | ALWAYS_CRC_REGEN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x03200600` | `0x00000000` |
    | xe0 | `0x03201600` | `0x00000000` |
    | xe1 | `0x03202600` | `0x00000000` |
    | xe2 | `0x03203600` | `0x00000000` |
    | xe3 | `0x03204600` | `0x00000000` |
    | xe4 | `0x03205600` | `0x00000000` |
    | xe5 | `0x03206600` | `0x00000000` |
    | xe6 | `0x03207600` | `0x00000000` |
    | xe7 | `0x03208600` | `0x00000000` |
    | xe8 | `0x03209600` | `0x00000000` |
    | xe9 | `0x0320a600` | `0x00000000` |
    | xe10 | `0x0320b600` | `0x00000000` |
    | xe11 | `0x0320c600` | `0x00000000` |
    | xe12 | `0x0320d600` | `0x00000000` |
    | xe13 | `0x0320e600` | `0x00000000` |
    | xe14 | `0x0320f600` | `0x00000000` |
    | xe15 | `0x03210600` | `0x00000000` |
    | xe16 | `0x03211600` | `0x00000000` |
    | xe17 | `0x03212600` | `0x00000000` |
    | xe18 | `0x03213600` | `0x00000000` |
    | xe19 | `0x03214600` | `0x00000000` |
    | xe20 | `0x03215600` | `0x00000000` |
    | xe21 | `0x03216600` | `0x00000000` |
    | xe22 | `0x03217600` | `0x00000000` |
    | xe23 | `0x03218600` | `0x00000000` |
    | xe24 | `0x03219600` | `0x00000000` |
    | xe25 | `0x0321a600` | `0x00000000` |
    | xe26 | `0x0321b600` | `0x00000000` |
    | xe27 | `0x0321c600` | `0x00000000` |
    | xe28 | `0x0321d600` | `0x00000000` |
    | xe29 | `0x0321e600` | `0x00000000` |
    | xe30 | `0x0321f600` | `0x00000000` |
    | xe31 | `0x03220600` | `0x00000000` |
    | xe32 | `0x03221600` | `0x00000000` |
    | xe33 | `0x03222600` | `0x00000000` |
    | xe34 | `0x03223600` | `0x00000000` |
    | xe35 | `0x03224600` | `0x00000000` |
    | xe36 | `0x03225600` | `0x00000000` |
    | xe37 | `0x03226600` | `0x00000000` |
    | xe38 | `0x03227600` | `0x00000000` |
    | xe39 | `0x03228600` | `0x00000000` |
    | xe40 | `0x03229600` | `0x00000000` |
    | xe41 | `0x0322a600` | `0x00000000` |
    | xe42 | `0x0322b600` | `0x00000000` |
    | xe43 | `0x0322c600` | `0x00000000` |
    | xe44 | `0x0322d600` | `0x00000000` |
    | xe45 | `0x0322e600` | `0x00000000` |
    | xe46 | `0x0322f600` | `0x00000000` |
    | xe47 | `0x03230600` | `0x00000000` |
    | xe48 | `0x03231600` | `0x00000000` |
    | xe49 | `0x03232600` | `0x00000000` |
    | xe50 | `0x03233600` | `0x00000000` |
    | xe51 | `0x03234600` | `0x00000000` |
    | lb0 | `0x03241600` | `0x00000000` |

---

## EGR_NIV_CONFIGr

- **Address:** `0x03280601`  ·  **Size:** 4 bytes
- **Function:** Egress NIV Config Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | VNTAG_DST_VIF |
    | `[14]` | VNTAG_L |
    | `[15]` | VNTAG_P |
    | `[16]` | VNTAG_R |
    | `[18:17]` | VNTAG_V |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x03280601` | `0x00000000` |

---

## EGR_SYS_RSVD_VIDr

- **Address:** `0x03280602`  ·  **Size:** 4 bytes
- **Function:** VID to populate HG header when leaving real VID in the packet.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | VID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x03280602` | `0x00000000` |

---

## EGR_TRILL_HEADER_ATTRIBUTESr

- **Address:** `0x04280600`  ·  **Size:** 4 bytes
- **Function:** Egress Trill Heaader Attributes Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | RBRIDGE_NICKNAME |
    | `[17:16]` | VERSION |
    | `[19:18]` | RESERVED_FIELD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x04280600` | `0x00000000` |

---

## EGR_MODMAP_CTRLr

- **Address:** `0x05200604`  ·  **Size:** 4 bytes
- **Function:** Module Mapping Control

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MODULEID_OFFSET |
    | `[8]` | EGR_MAP_EN |
    | `[9]` | EGR_MOD_MAP_ID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x05200604` | `0x00000000` |
    | xe0 | `0x05201604` | `0x00000000` |
    | xe1 | `0x05202604` | `0x00000000` |
    | xe2 | `0x05203604` | `0x00000000` |
    | xe3 | `0x05204604` | `0x00000000` |
    | xe4 | `0x05205604` | `0x00000000` |
    | xe5 | `0x05206604` | `0x00000000` |
    | xe6 | `0x05207604` | `0x00000000` |
    | xe7 | `0x05208604` | `0x00000000` |
    | xe8 | `0x05209604` | `0x00000000` |
    | xe9 | `0x0520a604` | `0x00000000` |
    | xe10 | `0x0520b604` | `0x00000000` |
    | xe11 | `0x0520c604` | `0x00000000` |
    | xe12 | `0x0520d604` | `0x00000000` |
    | xe13 | `0x0520e604` | `0x00000000` |
    | xe14 | `0x0520f604` | `0x00000000` |
    | xe15 | `0x05210604` | `0x00000000` |
    | xe16 | `0x05211604` | `0x00000000` |
    | xe17 | `0x05212604` | `0x00000000` |
    | xe18 | `0x05213604` | `0x00000000` |
    | xe19 | `0x05214604` | `0x00000000` |
    | xe20 | `0x05215604` | `0x00000000` |
    | xe21 | `0x05216604` | `0x00000000` |
    | xe22 | `0x05217604` | `0x00000000` |
    | xe23 | `0x05218604` | `0x00000000` |
    | xe24 | `0x05219604` | `0x00000000` |
    | xe25 | `0x0521a604` | `0x00000000` |
    | xe26 | `0x0521b604` | `0x00000000` |
    | xe27 | `0x0521c604` | `0x00000000` |
    | xe28 | `0x0521d604` | `0x00000000` |
    | xe29 | `0x0521e604` | `0x00000000` |
    | xe30 | `0x0521f604` | `0x00000000` |
    | xe31 | `0x05220604` | `0x00000000` |
    | xe32 | `0x05221604` | `0x00000000` |
    | xe33 | `0x05222604` | `0x00000000` |
    | xe34 | `0x05223604` | `0x00000000` |
    | xe35 | `0x05224604` | `0x00000000` |
    | xe36 | `0x05225604` | `0x00000000` |
    | xe37 | `0x05226604` | `0x00000000` |
    | xe38 | `0x05227604` | `0x00000000` |
    | xe39 | `0x05228604` | `0x00000000` |
    | xe40 | `0x05229604` | `0x00000000` |
    | xe41 | `0x0522a604` | `0x00000000` |
    | xe42 | `0x0522b604` | `0x00000000` |
    | xe43 | `0x0522c604` | `0x00000000` |
    | xe44 | `0x0522d604` | `0x00000000` |
    | xe45 | `0x0522e604` | `0x00000000` |
    | xe46 | `0x0522f604` | `0x00000000` |
    | xe47 | `0x05230604` | `0x00000000` |
    | xe48 | `0x05231604` | `0x00000000` |
    | xe49 | `0x05232604` | `0x00000000` |
    | xe50 | `0x05233604` | `0x00000000` |
    | xe51 | `0x05234604` | `0x00000000` |
    | lb0 | `0x05241604` | `0x00000000` |

---

## EGR_SF_SRC_MODID_CHECKr

- **Address:** `0x05200605`  ·  **Size:** 8 bytes
- **Function:** Module Mapping Control

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | MODID0 |
    | `[14:7]` | SF_MODID0 |
    | `[15]` | SF_MODID0_VALID |
    | `[22:16]` | MODID1 |
    | `[30:23]` | SF_MODID1 |
    | `[31]` | SF_MODID1_VALID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x05200605` | `0x0000000000000000` |
    | xe0 | `0x05201605` | `0x0000000000000000` |
    | xe1 | `0x05202605` | `0x0000000000000000` |
    | xe2 | `0x05203605` | `0x0000000000000000` |
    | xe3 | `0x05204605` | `0x0000000000000000` |
    | xe4 | `0x05205605` | `0x0000000000000000` |
    | xe5 | `0x05206605` | `0x0000000000000000` |
    | xe6 | `0x05207605` | `0x0000000000000000` |
    | xe7 | `0x05208605` | `0x0000000000000000` |
    | xe8 | `0x05209605` | `0x0000000000000000` |
    | xe9 | `0x0520a605` | `0x0000000000000000` |
    | xe10 | `0x0520b605` | `0x0000000000000000` |
    | xe11 | `0x0520c605` | `0x0000000000000000` |
    | xe12 | `0x0520d605` | `0x0000000000000000` |
    | xe13 | `0x0520e605` | `0x0000000000000000` |
    | xe14 | `0x0520f605` | `0x0000000000000000` |
    | xe15 | `0x05210605` | `0x0000000000000000` |
    | xe16 | `0x05211605` | `0x0000000000000000` |
    | xe17 | `0x05212605` | `0x0000000000000000` |
    | xe18 | `0x05213605` | `0x0000000000000000` |
    | xe19 | `0x05214605` | `0x0000000000000000` |
    | xe20 | `0x05215605` | `0x0000000000000000` |
    | xe21 | `0x05216605` | `0x0000000000000000` |
    | xe22 | `0x05217605` | `0x0000000000000000` |
    | xe23 | `0x05218605` | `0x0000000000000000` |
    | xe24 | `0x05219605` | `0x0000000000000000` |
    | xe25 | `0x0521a605` | `0x0000000000000000` |
    | xe26 | `0x0521b605` | `0x0000000000000000` |
    | xe27 | `0x0521c605` | `0x0000000000000000` |
    | xe28 | `0x0521d605` | `0x0000000000000000` |
    | xe29 | `0x0521e605` | `0x0000000000000000` |
    | xe30 | `0x0521f605` | `0x0000000000000000` |
    | xe31 | `0x05220605` | `0x0000000000000000` |
    | xe32 | `0x05221605` | `0x0000000000000000` |
    | xe33 | `0x05222605` | `0x0000000000000000` |
    | xe34 | `0x05223605` | `0x0000000000000000` |
    | xe35 | `0x05224605` | `0x0000000000000000` |
    | xe36 | `0x05225605` | `0x0000000000000000` |
    | xe37 | `0x05226605` | `0x0000000000000000` |
    | xe38 | `0x05227605` | `0x0000000000000000` |
    | xe39 | `0x05228605` | `0x0000000000000000` |
    | xe40 | `0x05229605` | `0x0000000000000000` |
    | xe41 | `0x0522a605` | `0x0000000000000000` |
    | xe42 | `0x0522b605` | `0x0000000000000000` |
    | xe43 | `0x0522c605` | `0x0000000000000000` |
    | xe44 | `0x0522d605` | `0x0000000000000000` |
    | xe45 | `0x0522e605` | `0x0000000000000000` |
    | xe46 | `0x0522f605` | `0x0000000000000000` |
    | xe47 | `0x05230605` | `0x0000000000000000` |
    | xe48 | `0x05231605` | `0x0000000000000000` |
    | xe49 | `0x05232605` | `0x0000000000000000` |
    | xe50 | `0x05233605` | `0x0000000000000000` |
    | xe51 | `0x05234605` | `0x0000000000000000` |
    | lb0 | `0x05241605` | `0x0000000000000000` |

---

## EGR_TUNNEL_PIMDR1_CFG0r

- **Address:** `0x05280600`  ·  **Size:** 4 bytes
- **Function:** For PIMSM-DR1 type of tunnel pkts, MS 4 bytes are specified here, so that they\ncan be inserted in the packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280600` | `0x00000000` |

---

## EGR_TUNNEL_PIMDR1_CFG1r

- **Address:** `0x05280601`  ·  **Size:** 4 bytes
- **Function:** For PIMSM-DR1 type of tunnel pkts, LS 4 bytes are specified here, so that they\ncan be inserted in the packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280601` | `0x00000000` |

---

## EGR_TUNNEL_PIMDR2_CFG0r

- **Address:** `0x05280602`  ·  **Size:** 4 bytes
- **Function:** For PIMSM-DR2 type of tunnel pkts, MS 4 bytes are specified here, so that they\ncan be inserted in the packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280602` | `0x00000000` |

---

## EGR_TUNNEL_PIMDR2_CFG1r

- **Address:** `0x05280603`  ·  **Size:** 4 bytes
- **Function:** For PIMSM-DR2 type of tunnel pkts, LS 4 bytes are specified here, so that they\ncan be inserted in the packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280603` | `0x00000000` |

---

## EGR_MIM_ETHERTYPEr

- **Address:** `0x05280606`  ·  **Size:** 4 bytes
- **Function:** MAC-in-MAC Ethertype Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280606` | `0x000088e7` |

---

## EGR_EHCPM_ECC_PARITY_CONTROLr

- **Address:** `0x05280700`  ·  **Size:** 4 bytes
- **Function:** Control ecc/parity functions of EHCPM RAMS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MOD_MAP_PARITY_EN |
    | `[1]` | INITBUF_ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280700` | `0x00000003` |

---

## EGR_EHCPM_RAM_CONTROL_STBYr

- **Address:** `0x05280704`  ·  **Size:** 4 bytes
- **Function:** Control ecc functions of EHCPM RAMS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MOD_MAP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280704` | `0x00000000` |

---

## EGR_MOD_MAP_PARITY_STATUS_INTRr

- **Address:** `0x05280d01`  ·  **Size:** 4 bytes
- **Function:** ECC interrupt status register for EGR_MOD_MAP memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280d01` | `0x00000000` |

---

## EGR_MOD_MAP_PARITY_STATUS_NACKr

- **Address:** `0x05280d02`  ·  **Size:** 4 bytes
- **Function:** ECC nack status register for EGR_MOD_MAP memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280d02` | `0x00000000` |

---

## EGR_INITBUF_ECC_STATUS_INTRr

- **Address:** `0x05280d03`  ·  **Size:** 4 bytes
- **Function:** ECC interrupt status register for INITBUF memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[6:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x05280d03` | `0x00000000` |

---

## EGR_SHAPING_CONTROLr

- **Address:** `0x06200606`  ·  **Size:** 4 bytes
- **Function:** Specifies control fields Egress for the Shaping Counters.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PACKET_IFG_BYTES |
    | `[13:7]` | PACKET_IFG_BYTES_2 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x06200606` | `0x00000000` |
    | xe0 | `0x06201606` | `0x00000000` |
    | xe1 | `0x06202606` | `0x00000000` |
    | xe2 | `0x06203606` | `0x00000000` |
    | xe3 | `0x06204606` | `0x00000000` |
    | xe4 | `0x06205606` | `0x00000000` |
    | xe5 | `0x06206606` | `0x00000000` |
    | xe6 | `0x06207606` | `0x00000000` |
    | xe7 | `0x06208606` | `0x00000000` |
    | xe8 | `0x06209606` | `0x00000000` |
    | xe9 | `0x0620a606` | `0x00000000` |
    | xe10 | `0x0620b606` | `0x00000000` |
    | xe11 | `0x0620c606` | `0x00000000` |
    | xe12 | `0x0620d606` | `0x00000000` |
    | xe13 | `0x0620e606` | `0x00000000` |
    | xe14 | `0x0620f606` | `0x00000000` |
    | xe15 | `0x06210606` | `0x00000000` |
    | xe16 | `0x06211606` | `0x00000000` |
    | xe17 | `0x06212606` | `0x00000000` |
    | xe18 | `0x06213606` | `0x00000000` |
    | xe19 | `0x06214606` | `0x00000000` |
    | xe20 | `0x06215606` | `0x00000000` |
    | xe21 | `0x06216606` | `0x00000000` |
    | xe22 | `0x06217606` | `0x00000000` |
    | xe23 | `0x06218606` | `0x00000000` |
    | xe24 | `0x06219606` | `0x00000000` |
    | xe25 | `0x0621a606` | `0x00000000` |
    | xe26 | `0x0621b606` | `0x00000000` |
    | xe27 | `0x0621c606` | `0x00000000` |
    | xe28 | `0x0621d606` | `0x00000000` |
    | xe29 | `0x0621e606` | `0x00000000` |
    | xe30 | `0x0621f606` | `0x00000000` |
    | xe31 | `0x06220606` | `0x00000000` |
    | xe32 | `0x06221606` | `0x00000000` |
    | xe33 | `0x06222606` | `0x00000000` |
    | xe34 | `0x06223606` | `0x00000000` |
    | xe35 | `0x06224606` | `0x00000000` |
    | xe36 | `0x06225606` | `0x00000000` |
    | xe37 | `0x06226606` | `0x00000000` |
    | xe38 | `0x06227606` | `0x00000000` |
    | xe39 | `0x06228606` | `0x00000000` |
    | xe40 | `0x06229606` | `0x00000000` |
    | xe41 | `0x0622a606` | `0x00000000` |
    | xe42 | `0x0622b606` | `0x00000000` |
    | xe43 | `0x0622c606` | `0x00000000` |
    | xe44 | `0x0622d606` | `0x00000000` |
    | xe45 | `0x0622e606` | `0x00000000` |
    | xe46 | `0x0622f606` | `0x00000000` |
    | xe47 | `0x06230606` | `0x00000000` |
    | xe48 | `0x06231606` | `0x00000000` |
    | xe49 | `0x06232606` | `0x00000000` |
    | xe50 | `0x06233606` | `0x00000000` |
    | xe51 | `0x06234606` | `0x00000000` |
    | lb0 | `0x06241606` | `0x00000000` |

---

## EGR_COUNTER_CONTROLr

- **Address:** `0x06200607`  ·  **Size:** 4 bytes
- **Function:** Specifies control fields Egress for the MMU Counters and Meters.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PACKET_IFG_BYTES |
    | `[13:7]` | PACKET_IFG_BYTES_2 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x06200607` | `0x00000000` |
    | xe0 | `0x06201607` | `0x00000000` |
    | xe1 | `0x06202607` | `0x00000000` |
    | xe2 | `0x06203607` | `0x00000000` |
    | xe3 | `0x06204607` | `0x00000000` |
    | xe4 | `0x06205607` | `0x00000000` |
    | xe5 | `0x06206607` | `0x00000000` |
    | xe6 | `0x06207607` | `0x00000000` |
    | xe7 | `0x06208607` | `0x00000000` |
    | xe8 | `0x06209607` | `0x00000000` |
    | xe9 | `0x0620a607` | `0x00000000` |
    | xe10 | `0x0620b607` | `0x00000000` |
    | xe11 | `0x0620c607` | `0x00000000` |
    | xe12 | `0x0620d607` | `0x00000000` |
    | xe13 | `0x0620e607` | `0x00000000` |
    | xe14 | `0x0620f607` | `0x00000000` |
    | xe15 | `0x06210607` | `0x00000000` |
    | xe16 | `0x06211607` | `0x00000000` |
    | xe17 | `0x06212607` | `0x00000000` |
    | xe18 | `0x06213607` | `0x00000000` |
    | xe19 | `0x06214607` | `0x00000000` |
    | xe20 | `0x06215607` | `0x00000000` |
    | xe21 | `0x06216607` | `0x00000000` |
    | xe22 | `0x06217607` | `0x00000000` |
    | xe23 | `0x06218607` | `0x00000000` |
    | xe24 | `0x06219607` | `0x00000000` |
    | xe25 | `0x0621a607` | `0x00000000` |
    | xe26 | `0x0621b607` | `0x00000000` |
    | xe27 | `0x0621c607` | `0x00000000` |
    | xe28 | `0x0621d607` | `0x00000000` |
    | xe29 | `0x0621e607` | `0x00000000` |
    | xe30 | `0x0621f607` | `0x00000000` |
    | xe31 | `0x06220607` | `0x00000000` |
    | xe32 | `0x06221607` | `0x00000000` |
    | xe33 | `0x06222607` | `0x00000000` |
    | xe34 | `0x06223607` | `0x00000000` |
    | xe35 | `0x06224607` | `0x00000000` |
    | xe36 | `0x06225607` | `0x00000000` |
    | xe37 | `0x06226607` | `0x00000000` |
    | xe38 | `0x06227607` | `0x00000000` |
    | xe39 | `0x06228607` | `0x00000000` |
    | xe40 | `0x06229607` | `0x00000000` |
    | xe41 | `0x0622a607` | `0x00000000` |
    | xe42 | `0x0622b607` | `0x00000000` |
    | xe43 | `0x0622c607` | `0x00000000` |
    | xe44 | `0x0622d607` | `0x00000000` |
    | xe45 | `0x0622e607` | `0x00000000` |
    | xe46 | `0x0622f607` | `0x00000000` |
    | xe47 | `0x06230607` | `0x00000000` |
    | xe48 | `0x06231607` | `0x00000000` |
    | xe49 | `0x06232607` | `0x00000000` |
    | xe50 | `0x06233607` | `0x00000000` |
    | xe51 | `0x06234607` | `0x00000000` |
    | lb0 | `0x06241607` | `0x00000000` |

---

## EGR_MTUr

- **Address:** `0x06200609`  ·  **Size:** 4 bytes
- **Function:** Egress MTU Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | MTU_SIZE |
    | `[14]` | MTU_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x06200609` | `0x00003fff` |
    | xe0 | `0x06201609` | `0x000045f2` |
    | xe1 | `0x06202609` | `0x000045f2` |
    | xe2 | `0x06203609` | `0x000045f2` |
    | xe3 | `0x06204609` | `0x000045f2` |
    | xe4 | `0x06205609` | `0x000045f2` |
    | xe5 | `0x06206609` | `0x000045f2` |
    | xe6 | `0x06207609` | `0x000045f2` |
    | xe7 | `0x06208609` | `0x000045f2` |
    | xe8 | `0x06209609` | `0x000045f2` |
    | xe9 | `0x0620a609` | `0x000045f2` |
    | xe10 | `0x0620b609` | `0x000045f2` |
    | xe11 | `0x0620c609` | `0x000045f2` |
    | xe12 | `0x0620d609` | `0x000045f2` |
    | xe13 | `0x0620e609` | `0x000045f2` |
    | xe14 | `0x0620f609` | `0x000045f2` |
    | xe15 | `0x06210609` | `0x000045f2` |
    | xe16 | `0x06211609` | `0x000045f2` |
    | xe17 | `0x06212609` | `0x000045f2` |
    | xe18 | `0x06213609` | `0x000045f2` |
    | xe19 | `0x06214609` | `0x000045f2` |
    | xe20 | `0x06215609` | `0x000045f2` |
    | xe21 | `0x06216609` | `0x000045f2` |
    | xe22 | `0x06217609` | `0x000045f2` |
    | xe23 | `0x06218609` | `0x000045f2` |
    | xe24 | `0x06219609` | `0x000045f2` |
    | xe25 | `0x0621a609` | `0x000045f2` |
    | xe26 | `0x0621b609` | `0x000045f2` |
    | xe27 | `0x0621c609` | `0x000045f2` |
    | xe28 | `0x0621d609` | `0x000045f2` |
    | xe29 | `0x0621e609` | `0x000045f2` |
    | xe30 | `0x0621f609` | `0x000045f2` |
    | xe31 | `0x06220609` | `0x000045f2` |
    | xe32 | `0x06221609` | `0x000045f2` |
    | xe33 | `0x06222609` | `0x000045f2` |
    | xe34 | `0x06223609` | `0x000045f2` |
    | xe35 | `0x06224609` | `0x000045f2` |
    | xe36 | `0x06225609` | `0x000045f2` |
    | xe37 | `0x06226609` | `0x000045f2` |
    | xe38 | `0x06227609` | `0x000045f2` |
    | xe39 | `0x06228609` | `0x000045f2` |
    | xe40 | `0x06229609` | `0x000045f2` |
    | xe41 | `0x0622a609` | `0x000045f2` |
    | xe42 | `0x0622b609` | `0x000045f2` |
    | xe43 | `0x0622c609` | `0x000045f2` |
    | xe44 | `0x0622d609` | `0x000045f2` |
    | xe45 | `0x0622e609` | `0x000045f2` |
    | xe46 | `0x0622f609` | `0x000045f2` |
    | xe47 | `0x06230609` | `0x000045f2` |
    | xe48 | `0x06231609` | `0x000045f2` |
    | xe49 | `0x06232609` | `0x000045f2` |
    | xe50 | `0x06233609` | `0x000045f2` |
    | xe51 | `0x06234609` | `0x000045f2` |
    | lb0 | `0x06241609` | `0x00003fff` |

---

## EGR_PORT_1r

- **Address:** `0x0620060b`  ·  **Size:** 4 bytes
- **Function:** Configuration Register for Egress port.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | OUTER_TPID_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0620060b` | `0x00000001` |
    | xe0 | `0x0620160b` | `0x00000001` |
    | xe1 | `0x0620260b` | `0x00000001` |
    | xe2 | `0x0620360b` | `0x00000001` |
    | xe3 | `0x0620460b` | `0x00000001` |
    | xe4 | `0x0620560b` | `0x00000001` |
    | xe5 | `0x0620660b` | `0x00000001` |
    | xe6 | `0x0620760b` | `0x00000001` |
    | xe7 | `0x0620860b` | `0x00000001` |
    | xe8 | `0x0620960b` | `0x00000001` |
    | xe9 | `0x0620a60b` | `0x00000001` |
    | xe10 | `0x0620b60b` | `0x00000001` |
    | xe11 | `0x0620c60b` | `0x00000001` |
    | xe12 | `0x0620d60b` | `0x00000001` |
    | xe13 | `0x0620e60b` | `0x00000001` |
    | xe14 | `0x0620f60b` | `0x00000001` |
    | xe15 | `0x0621060b` | `0x00000001` |
    | xe16 | `0x0621160b` | `0x00000001` |
    | xe17 | `0x0621260b` | `0x00000001` |
    | xe18 | `0x0621360b` | `0x00000001` |
    | xe19 | `0x0621460b` | `0x00000001` |
    | xe20 | `0x0621560b` | `0x00000001` |
    | xe21 | `0x0621660b` | `0x00000001` |
    | xe22 | `0x0621760b` | `0x00000001` |
    | xe23 | `0x0621860b` | `0x00000001` |
    | xe24 | `0x0621960b` | `0x00000001` |
    | xe25 | `0x0621a60b` | `0x00000001` |
    | xe26 | `0x0621b60b` | `0x00000001` |
    | xe27 | `0x0621c60b` | `0x00000001` |
    | xe28 | `0x0621d60b` | `0x00000001` |
    | xe29 | `0x0621e60b` | `0x00000001` |
    | xe30 | `0x0621f60b` | `0x00000001` |
    | xe31 | `0x0622060b` | `0x00000001` |
    | xe32 | `0x0622160b` | `0x00000001` |
    | xe33 | `0x0622260b` | `0x00000001` |
    | xe34 | `0x0622360b` | `0x00000001` |
    | xe35 | `0x0622460b` | `0x00000001` |
    | xe36 | `0x0622560b` | `0x00000001` |
    | xe37 | `0x0622660b` | `0x00000001` |
    | xe38 | `0x0622760b` | `0x00000001` |
    | xe39 | `0x0622860b` | `0x00000001` |
    | xe40 | `0x0622960b` | `0x00000001` |
    | xe41 | `0x0622a60b` | `0x00000001` |
    | xe42 | `0x0622b60b` | `0x00000001` |
    | xe43 | `0x0622c60b` | `0x00000001` |
    | xe44 | `0x0622d60b` | `0x00000001` |
    | xe45 | `0x0622e60b` | `0x00000001` |
    | xe46 | `0x0622f60b` | `0x00000001` |
    | xe47 | `0x0623060b` | `0x00000001` |
    | xe48 | `0x0623160b` | `0x00000001` |
    | xe49 | `0x0623260b` | `0x00000001` |
    | xe50 | `0x0623360b` | `0x00000001` |
    | xe51 | `0x0623460b` | `0x00000001` |
    | lb0 | `0x0624160b` | `0x00000001` |

---

## EGR_MC_CONTROL_1r

- **Address:** `0x06280601`  ·  **Size:** 4 bytes
- **Function:** TBfilled

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | HIGIG2_BC_BASE_OFFSET |
    | `[31:16]` | HIGIG2_L2MC_BASE_OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280601` | `0x10000000` |

---

## EGR_MC_CONTROL_2r

- **Address:** `0x06280602`  ·  **Size:** 4 bytes
- **Function:** TBfilled

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | HIGIG2_IPMC_BASE_OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280602` | `0x00002000` |

---

## EGR_FLEXIBLE_IPV6_EXT_HDRr

- **Address:** `0x06280605`  ·  **Size:** 4 bytes
- **Function:** Egress Programmable IPv6 extension header value.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PROTOCOL_ID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280605` | `0x00000000` |

---

## EGR_PKT_MODS_CONTROLr

- **Address:** `0x06280608`  ·  **Size:** 4 bytes
- **Function:** Controls and limits for packet modifications

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MAX_ADDITION_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280608` | `0x00000070` |

---

## EGR_QCN_CNM_LBMH_CONTROLr

- **Address:** `0x06280630`  ·  **Size:** 4 bytes
- **Function:** Egress CNM Loopback Module Header Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | QCN_CNM_SRC_PORT |
    | `[15:8]` | QCN_CNM_SRC_MODID |
    | `[19:16]` | QCN_CNM_INTERNAL_PRIORITY |
    | `[21:20]` | QCN_CNM_CNG |
    | `[22]` | QCN_CNM_SRC_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280630` | `0x00000000` |

---

## EGR_NIV_ETHERTYPE_2r

- **Address:** `0x06280640`  ·  **Size:** 4 bytes
- **Function:** Egress NIV Ethertype Control Register (second copy).

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x06280640` | `0x00000000` |

---

## EGR_WESP_PROTO_CONTROLr

- **Address:** `0x07280603`  ·  **Size:** 4 bytes
- **Function:** Egress WESP Protocol Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | WESP_PROTO_NUMBER |
    | `[8]` | WESP_PROTO_NUMBER_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x07280603` | `0x00000000` |

---

## EGR_QCN_CNTAG_ETHERTYPE_2r

- **Address:** `0x07280610`  ·  **Size:** 4 bytes
- **Function:** QCN CNTAG Ethertype Control Register (second copy).

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x07280610` | `0x00000000` |

---

## EGR_HBFC_CNTAG_ETHERTYPE_2r

- **Address:** `0x07280611`  ·  **Size:** 4 bytes
- **Function:** HBFC CNTAG Ethertype Control Register (second copy).

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x07280611` | `0x00000000` |

---

## EFP_SLICE_CONTROLr

- **Address:** `0x0828060b`  ·  **Size:** 4 bytes
- **Function:** EFP_SLICE_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SLICE_ENABLE_SLICE_0 |
    | `[1]` | SLICE_ENABLE_SLICE_1 |
    | `[2]` | SLICE_ENABLE_SLICE_2 |
    | `[3]` | SLICE_ENABLE_SLICE_3 |
    | `[4]` | LOOKUP_ENABLE_SLICE_0 |
    | `[5]` | LOOKUP_ENABLE_SLICE_1 |
    | `[6]` | LOOKUP_ENABLE_SLICE_2 |
    | `[7]` | LOOKUP_ENABLE_SLICE_3 |
    | `[10:8]` | SLICE_0_MODE |
    | `[13:11]` | SLICE_1_MODE |
    | `[16:14]` | SLICE_2_MODE |
    | `[19:17]` | SLICE_3_MODE |
    | `[21:20]` | SLICE_0_IPV6_KEY_MODE |
    | `[23:22]` | SLICE_1_IPV6_KEY_MODE |
    | `[25:24]` | SLICE_2_IPV6_KEY_MODE |
    | `[27:26]` | SLICE_3_IPV6_KEY_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0828060b` | `0x000900cf` |

---

## EFP_METER_CONTROLr

- **Address:** `0x08280615`  ·  **Size:** 4 bytes
- **Function:** EFP_METER_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EFP_REFRESH_ENABLE |
    | `[4:1]` | MAX_TICK_COUNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280615` | `0x00000003` |

---

## EFP_SLICE_MAPr

- **Address:** `0x08280616`  ·  **Size:** 4 bytes
- **Function:** EFP_SLICE_MAP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | VIRTUAL_SLICE_0_VIRTUAL_SLICE_GROUP |
    | `[3:2]` | VIRTUAL_SLICE_1_VIRTUAL_SLICE_GROUP |
    | `[5:4]` | VIRTUAL_SLICE_2_VIRTUAL_SLICE_GROUP |
    | `[7:6]` | VIRTUAL_SLICE_3_VIRTUAL_SLICE_GROUP |
    | `[9:8]` | VIRTUAL_SLICE_0_PHYSICAL_SLICE_NUMBER |
    | `[11:10]` | VIRTUAL_SLICE_1_PHYSICAL_SLICE_NUMBER |
    | `[13:12]` | VIRTUAL_SLICE_2_PHYSICAL_SLICE_NUMBER |
    | `[15:14]` | VIRTUAL_SLICE_3_PHYSICAL_SLICE_NUMBER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280616` | `0x00004ee4` |

---

## EGR_PW_INIT_COUNTERS_PARITY_CONTROLr

- **Address:** `0x08280700`  ·  **Size:** 4 bytes
- **Function:** EGR_PW_INIT_COUNTERS_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280700` | `0x00000001` |

---

## EFP_POLICY_PARITY_CONTROLr

- **Address:** `0x08280703`  ·  **Size:** 4 bytes
- **Function:** EFP_POLICY_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280703` | `0x00000001` |

---

## EFP_METER_PARITY_CONTROLr

- **Address:** `0x08280706`  ·  **Size:** 4 bytes
- **Function:** EFP_METER_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280706` | `0x00000001` |

---

## EFP_CAM_BIST_CONTROLr

- **Address:** `0x0828070a`  ·  **Size:** 4 bytes
- **Function:** EFP_CAM_BIST_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CAM_BIST_ENABLE_SLICE_0 |
    | `[1]` | CAM_BIST_ENABLE_SLICE_1 |
    | `[2]` | CAM_BIST_ENABLE_SLICE_2 |
    | `[3]` | CAM_BIST_ENABLE_SLICE_3 |
    | `[4]` | CAM_DEBUG_ENABLE_SLICE_0 |
    | `[5]` | CAM_DEBUG_ENABLE_SLICE_1 |
    | `[6]` | CAM_DEBUG_ENABLE_SLICE_2 |
    | `[7]` | CAM_DEBUG_ENABLE_SLICE_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0828070a` | `0x00000000` |

---

## EFP_RAM_CONTROLr

- **Address:** `0x0828070b`  ·  **Size:** 4 bytes
- **Function:** EFP_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | EFP_CAM_TM |
    | `[14]` | PW_INIT_COUNTER_DCM |
    | `[15]` | PW_INIT_COUNTER_PM |
    | `[16]` | EFP_CAM_SLICE_0_PM |
    | `[17]` | EFP_CAM_SLICE_1_PM |
    | `[18]` | EFP_CAM_SLICE_2_PM |
    | `[19]` | EFP_CAM_SLICE_3_PM |
    | `[29:20]` | PW_INIT_COUNTER_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0828070b` | `0x00000000` |

---

## EFP_RAM_CONTROL_1r

- **Address:** `0x0828070c`  ·  **Size:** 4 bytes
- **Function:** EFP_RAM_CONTROL1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | EFP_POLICY_SLICE_0_TM |
    | `[9:5]` | EFP_POLICY_SLICE_1_TM |
    | `[14:10]` | EFP_POLICY_SLICE_2_TM |
    | `[19:15]` | EFP_POLICY_SLICE_3_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0828070c` | `0x00000000` |

---

## EFP_TCAM_BLKSELr

- **Address:** `0x0828070d`  ·  **Size:** 4 bytes
- **Function:** EFP_TCAM_BLKSEL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SLICE_0 |
    | `[3:2]` | SLICE_1 |
    | `[5:4]` | SLICE_2 |
    | `[7:6]` | SLICE_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0828070d` | `0x000000ff` |

---

## EGR_PW_INIT_COUNTERS_PARITY_STATUS_INTRr

- **Address:** `0x08280d01`  ·  **Size:** 4 bytes
- **Function:** EGR_PW_INIT_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d01` | `0x00000000` |

---

## EGR_PW_INIT_COUNTERS_PARITY_STATUS_NACKr

- **Address:** `0x08280d02`  ·  **Size:** 4 bytes
- **Function:** EGR_PW_INIT_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d02` | `0x00000000` |

---

## EFP_POLICY_PARITY_STATUS_INTRr

- **Address:** `0x08280d04`  ·  **Size:** 4 bytes
- **Function:** EFP_POLICY_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d04` | `0x00000000` |

---

## EFP_POLICY_PARITY_STATUS_NACKr

- **Address:** `0x08280d05`  ·  **Size:** 4 bytes
- **Function:** EFP_POLICY_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d05` | `0x00000000` |

---

## EFP_METER_PARITY_STATUS_INTRr

- **Address:** `0x08280d07`  ·  **Size:** 4 bytes
- **Function:** EFP_METER_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d07` | `0x00000000` |

---

## EFP_METER_PARITY_STATUS_NACKr

- **Address:** `0x08280d08`  ·  **Size:** 4 bytes
- **Function:** EFP_METER_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d08` | `0x00000000` |

---

## EFP_CAM_BIST_STATUSr

- **Address:** `0x08280d09`  ·  **Size:** 4 bytes
- **Function:** EFP_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x08280d09` | `0x00000000` |

---

## EFP_CAM_BIST_DBG_DATAr

- **Address:** `0x08280d0e`  ·  **Size:** 4 bytes
- **Function:** EFP_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## EFP_CAM_BIST_CONFIGr

- **Address:** `0x08280d0f`  ·  **Size:** 4 bytes
- **Function:** EFP_CAM_BIST_CONFIG

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

---

## EGR_DROP_VECTOR_Xr

- **Address:** `0x09280203`  ·  **Size:** 4 bytes
- **Function:** Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a block, then this register is updated with the reason.This is a sticky register, so once a bit is set, it'll stay set till the software clears it.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x09280203` | `0x00000000` |

---

## EGR_DROP_VECTOR_Yr

- **Address:** `0x09280403`  ·  **Size:** 4 bytes
- **Function:** Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a block, then this register is updated with the reason.This is a sticky register, so once a bit is set, it'll stay set till the software clears it.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x09280403` | `0x00000000` |

---

## EGR_DROP_VECTORr

- **Address:** `0x09280c03`  ·  **Size:** 4 bytes
- **Function:** Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a block, then this register is updated with the reason.This is a sticky register, so once a bit is set, it'll stay set till the software clears it.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x09280c03` | `0x00000000` |

---

## TDBGC0r

- **Address:** `0x0a200000`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #0

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200000` | `0x00000000` |
    | xe0 | `0x0a201000` | `0x00000000` |
    | xe1 | `0x0a202000` | `0x00000000` |
    | xe2 | `0x0a203000` | `0x00000000` |
    | xe3 | `0x0a204000` | `0x00000000` |
    | xe4 | `0x0a205000` | `0x00000000` |
    | xe5 | `0x0a206000` | `0x00000000` |
    | xe6 | `0x0a207000` | `0x00000000` |
    | xe7 | `0x0a208000` | `0x00000000` |
    | xe8 | `0x0a209000` | `0x00000000` |
    | xe9 | `0x0a20a000` | `0x00000000` |
    | xe10 | `0x0a20b000` | `0x00000000` |
    | xe11 | `0x0a20c000` | `0x00000000` |
    | xe12 | `0x0a20d000` | `0x00000000` |
    | xe13 | `0x0a20e000` | `0x00000000` |
    | xe14 | `0x0a20f000` | `0x00000000` |
    | xe15 | `0x0a210000` | `0x00000000` |
    | xe16 | `0x0a211000` | `0x00000000` |
    | xe17 | `0x0a212000` | `0x00000000` |
    | xe18 | `0x0a213000` | `0x00000000` |
    | xe19 | `0x0a214000` | `0x00000000` |
    | xe20 | `0x0a215000` | `0x00000000` |
    | xe21 | `0x0a216000` | `0x00000000` |
    | xe22 | `0x0a217000` | `0x00000000` |
    | xe23 | `0x0a218000` | `0x00000000` |
    | xe24 | `0x0a219000` | `0x00000000` |
    | xe25 | `0x0a21a000` | `0x00000000` |
    | xe26 | `0x0a21b000` | `0x00000000` |
    | xe27 | `0x0a21c000` | `0x00000000` |
    | xe28 | `0x0a21d000` | `0x00000000` |
    | xe29 | `0x0a21e000` | `0x00000000` |
    | xe30 | `0x0a21f000` | `0x00000000` |
    | xe31 | `0x0a220000` | `0x00000000` |
    | xe32 | `0x0a221000` | `0x00000000` |
    | xe33 | `0x0a222000` | `0x00000000` |
    | xe34 | `0x0a223000` | `0x00000000` |
    | xe35 | `0x0a224000` | `0x00000000` |
    | xe36 | `0x0a225000` | `0x00000000` |
    | xe37 | `0x0a226000` | `0x00000000` |
    | xe38 | `0x0a227000` | `0x00000000` |
    | xe39 | `0x0a228000` | `0x00000000` |
    | xe40 | `0x0a229000` | `0x00000000` |
    | xe41 | `0x0a22a000` | `0x00000000` |
    | xe42 | `0x0a22b000` | `0x00000000` |
    | xe43 | `0x0a22c000` | `0x00000000` |
    | xe44 | `0x0a22d000` | `0x00000000` |
    | xe45 | `0x0a22e000` | `0x00000000` |
    | xe46 | `0x0a22f000` | `0x00000000` |
    | xe47 | `0x0a230000` | `0x00000000` |
    | xe48 | `0x0a231000` | `0x00000000` |
    | xe49 | `0x0a232000` | `0x00000000` |
    | xe50 | `0x0a233000` | `0x00000000` |
    | xe51 | `0x0a234000` | `0x00000000` |
    | lb0 | `0x0a241000` | `0x00000000` |

---

## TDBGC1r

- **Address:** `0x0a200001`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #1

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200001` | `0x00000000` |
    | xe0 | `0x0a201001` | `0x00000000` |
    | xe1 | `0x0a202001` | `0x00000000` |
    | xe2 | `0x0a203001` | `0x00000000` |
    | xe3 | `0x0a204001` | `0x00000000` |
    | xe4 | `0x0a205001` | `0x00000000` |
    | xe5 | `0x0a206001` | `0x00000000` |
    | xe6 | `0x0a207001` | `0x00000000` |
    | xe7 | `0x0a208001` | `0x00000000` |
    | xe8 | `0x0a209001` | `0x00000000` |
    | xe9 | `0x0a20a001` | `0x00000000` |
    | xe10 | `0x0a20b001` | `0x00000000` |
    | xe11 | `0x0a20c001` | `0x00000000` |
    | xe12 | `0x0a20d001` | `0x00000000` |
    | xe13 | `0x0a20e001` | `0x00000000` |
    | xe14 | `0x0a20f001` | `0x00000000` |
    | xe15 | `0x0a210001` | `0x00000000` |
    | xe16 | `0x0a211001` | `0x00000000` |
    | xe17 | `0x0a212001` | `0x00000000` |
    | xe18 | `0x0a213001` | `0x00000000` |
    | xe19 | `0x0a214001` | `0x00000000` |
    | xe20 | `0x0a215001` | `0x00000000` |
    | xe21 | `0x0a216001` | `0x00000000` |
    | xe22 | `0x0a217001` | `0x00000000` |
    | xe23 | `0x0a218001` | `0x00000000` |
    | xe24 | `0x0a219001` | `0x00000000` |
    | xe25 | `0x0a21a001` | `0x00000000` |
    | xe26 | `0x0a21b001` | `0x00000000` |
    | xe27 | `0x0a21c001` | `0x00000000` |
    | xe28 | `0x0a21d001` | `0x00000000` |
    | xe29 | `0x0a21e001` | `0x00000000` |
    | xe30 | `0x0a21f001` | `0x00000000` |
    | xe31 | `0x0a220001` | `0x00000000` |
    | xe32 | `0x0a221001` | `0x00000000` |
    | xe33 | `0x0a222001` | `0x00000000` |
    | xe34 | `0x0a223001` | `0x00000000` |
    | xe35 | `0x0a224001` | `0x00000000` |
    | xe36 | `0x0a225001` | `0x00000000` |
    | xe37 | `0x0a226001` | `0x00000000` |
    | xe38 | `0x0a227001` | `0x00000000` |
    | xe39 | `0x0a228001` | `0x00000000` |
    | xe40 | `0x0a229001` | `0x00000000` |
    | xe41 | `0x0a22a001` | `0x00000000` |
    | xe42 | `0x0a22b001` | `0x00000000` |
    | xe43 | `0x0a22c001` | `0x00000000` |
    | xe44 | `0x0a22d001` | `0x00000000` |
    | xe45 | `0x0a22e001` | `0x00000000` |
    | xe46 | `0x0a22f001` | `0x00000000` |
    | xe47 | `0x0a230001` | `0x00000000` |
    | xe48 | `0x0a231001` | `0x00000000` |
    | xe49 | `0x0a232001` | `0x00000000` |
    | xe50 | `0x0a233001` | `0x00000000` |
    | xe51 | `0x0a234001` | `0x00000000` |
    | lb0 | `0x0a241001` | `0x00000000` |

---

## TDBGC2r

- **Address:** `0x0a200002`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #2

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200002` | `0x00000000` |
    | xe0 | `0x0a201002` | `0x00000000` |
    | xe1 | `0x0a202002` | `0x00000000` |
    | xe2 | `0x0a203002` | `0x00000000` |
    | xe3 | `0x0a204002` | `0x00000000` |
    | xe4 | `0x0a205002` | `0x00000000` |
    | xe5 | `0x0a206002` | `0x00000000` |
    | xe6 | `0x0a207002` | `0x00000000` |
    | xe7 | `0x0a208002` | `0x00000000` |
    | xe8 | `0x0a209002` | `0x00000000` |
    | xe9 | `0x0a20a002` | `0x00000000` |
    | xe10 | `0x0a20b002` | `0x00000000` |
    | xe11 | `0x0a20c002` | `0x00000000` |
    | xe12 | `0x0a20d002` | `0x00000000` |
    | xe13 | `0x0a20e002` | `0x00000000` |
    | xe14 | `0x0a20f002` | `0x00000000` |
    | xe15 | `0x0a210002` | `0x00000000` |
    | xe16 | `0x0a211002` | `0x00000000` |
    | xe17 | `0x0a212002` | `0x00000000` |
    | xe18 | `0x0a213002` | `0x00000000` |
    | xe19 | `0x0a214002` | `0x00000000` |
    | xe20 | `0x0a215002` | `0x00000000` |
    | xe21 | `0x0a216002` | `0x00000000` |
    | xe22 | `0x0a217002` | `0x00000000` |
    | xe23 | `0x0a218002` | `0x00000000` |
    | xe24 | `0x0a219002` | `0x00000000` |
    | xe25 | `0x0a21a002` | `0x00000000` |
    | xe26 | `0x0a21b002` | `0x00000000` |
    | xe27 | `0x0a21c002` | `0x00000000` |
    | xe28 | `0x0a21d002` | `0x00000000` |
    | xe29 | `0x0a21e002` | `0x00000000` |
    | xe30 | `0x0a21f002` | `0x00000000` |
    | xe31 | `0x0a220002` | `0x00000000` |
    | xe32 | `0x0a221002` | `0x00000000` |
    | xe33 | `0x0a222002` | `0x00000000` |
    | xe34 | `0x0a223002` | `0x00000000` |
    | xe35 | `0x0a224002` | `0x00000000` |
    | xe36 | `0x0a225002` | `0x00000000` |
    | xe37 | `0x0a226002` | `0x00000000` |
    | xe38 | `0x0a227002` | `0x00000000` |
    | xe39 | `0x0a228002` | `0x00000000` |
    | xe40 | `0x0a229002` | `0x00000000` |
    | xe41 | `0x0a22a002` | `0x00000000` |
    | xe42 | `0x0a22b002` | `0x00000000` |
    | xe43 | `0x0a22c002` | `0x00000000` |
    | xe44 | `0x0a22d002` | `0x00000000` |
    | xe45 | `0x0a22e002` | `0x00000000` |
    | xe46 | `0x0a22f002` | `0x00000000` |
    | xe47 | `0x0a230002` | `0x00000000` |
    | xe48 | `0x0a231002` | `0x00000000` |
    | xe49 | `0x0a232002` | `0x00000000` |
    | xe50 | `0x0a233002` | `0x00000000` |
    | xe51 | `0x0a234002` | `0x00000000` |
    | lb0 | `0x0a241002` | `0x00000000` |

---

## TDBGC3r

- **Address:** `0x0a200003`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #3

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200003` | `0x00000000` |
    | xe0 | `0x0a201003` | `0x00000000` |
    | xe1 | `0x0a202003` | `0x00000000` |
    | xe2 | `0x0a203003` | `0x00000000` |
    | xe3 | `0x0a204003` | `0x00000000` |
    | xe4 | `0x0a205003` | `0x00000000` |
    | xe5 | `0x0a206003` | `0x00000000` |
    | xe6 | `0x0a207003` | `0x00000000` |
    | xe7 | `0x0a208003` | `0x00000000` |
    | xe8 | `0x0a209003` | `0x00000000` |
    | xe9 | `0x0a20a003` | `0x00000000` |
    | xe10 | `0x0a20b003` | `0x00000000` |
    | xe11 | `0x0a20c003` | `0x00000000` |
    | xe12 | `0x0a20d003` | `0x00000000` |
    | xe13 | `0x0a20e003` | `0x00000000` |
    | xe14 | `0x0a20f003` | `0x00000000` |
    | xe15 | `0x0a210003` | `0x00000000` |
    | xe16 | `0x0a211003` | `0x00000000` |
    | xe17 | `0x0a212003` | `0x00000000` |
    | xe18 | `0x0a213003` | `0x00000000` |
    | xe19 | `0x0a214003` | `0x00000000` |
    | xe20 | `0x0a215003` | `0x00000000` |
    | xe21 | `0x0a216003` | `0x00000000` |
    | xe22 | `0x0a217003` | `0x00000000` |
    | xe23 | `0x0a218003` | `0x00000000` |
    | xe24 | `0x0a219003` | `0x00000000` |
    | xe25 | `0x0a21a003` | `0x00000000` |
    | xe26 | `0x0a21b003` | `0x00000000` |
    | xe27 | `0x0a21c003` | `0x00000000` |
    | xe28 | `0x0a21d003` | `0x00000000` |
    | xe29 | `0x0a21e003` | `0x00000000` |
    | xe30 | `0x0a21f003` | `0x00000000` |
    | xe31 | `0x0a220003` | `0x00000000` |
    | xe32 | `0x0a221003` | `0x00000000` |
    | xe33 | `0x0a222003` | `0x00000000` |
    | xe34 | `0x0a223003` | `0x00000000` |
    | xe35 | `0x0a224003` | `0x00000000` |
    | xe36 | `0x0a225003` | `0x00000000` |
    | xe37 | `0x0a226003` | `0x00000000` |
    | xe38 | `0x0a227003` | `0x00000000` |
    | xe39 | `0x0a228003` | `0x00000000` |
    | xe40 | `0x0a229003` | `0x00000000` |
    | xe41 | `0x0a22a003` | `0x00000000` |
    | xe42 | `0x0a22b003` | `0x00000000` |
    | xe43 | `0x0a22c003` | `0x00000000` |
    | xe44 | `0x0a22d003` | `0x00000000` |
    | xe45 | `0x0a22e003` | `0x00000000` |
    | xe46 | `0x0a22f003` | `0x00000000` |
    | xe47 | `0x0a230003` | `0x00000000` |
    | xe48 | `0x0a231003` | `0x00000000` |
    | xe49 | `0x0a232003` | `0x00000000` |
    | xe50 | `0x0a233003` | `0x00000000` |
    | xe51 | `0x0a234003` | `0x00000000` |
    | lb0 | `0x0a241003` | `0x00000000` |

---

## TDBGC4r

- **Address:** `0x0a200004`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #4

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200004` | `0x00000000` |
    | xe0 | `0x0a201004` | `0x00000000` |
    | xe1 | `0x0a202004` | `0x00000000` |
    | xe2 | `0x0a203004` | `0x00000000` |
    | xe3 | `0x0a204004` | `0x00000000` |
    | xe4 | `0x0a205004` | `0x00000000` |
    | xe5 | `0x0a206004` | `0x00000000` |
    | xe6 | `0x0a207004` | `0x00000000` |
    | xe7 | `0x0a208004` | `0x00000000` |
    | xe8 | `0x0a209004` | `0x00000000` |
    | xe9 | `0x0a20a004` | `0x00000000` |
    | xe10 | `0x0a20b004` | `0x00000000` |
    | xe11 | `0x0a20c004` | `0x00000000` |
    | xe12 | `0x0a20d004` | `0x00000000` |
    | xe13 | `0x0a20e004` | `0x00000000` |
    | xe14 | `0x0a20f004` | `0x00000000` |
    | xe15 | `0x0a210004` | `0x00000000` |
    | xe16 | `0x0a211004` | `0x00000000` |
    | xe17 | `0x0a212004` | `0x00000000` |
    | xe18 | `0x0a213004` | `0x00000000` |
    | xe19 | `0x0a214004` | `0x00000000` |
    | xe20 | `0x0a215004` | `0x00000000` |
    | xe21 | `0x0a216004` | `0x00000000` |
    | xe22 | `0x0a217004` | `0x00000000` |
    | xe23 | `0x0a218004` | `0x00000000` |
    | xe24 | `0x0a219004` | `0x00000000` |
    | xe25 | `0x0a21a004` | `0x00000000` |
    | xe26 | `0x0a21b004` | `0x00000000` |
    | xe27 | `0x0a21c004` | `0x00000000` |
    | xe28 | `0x0a21d004` | `0x00000000` |
    | xe29 | `0x0a21e004` | `0x00000000` |
    | xe30 | `0x0a21f004` | `0x00000000` |
    | xe31 | `0x0a220004` | `0x00000000` |
    | xe32 | `0x0a221004` | `0x00000000` |
    | xe33 | `0x0a222004` | `0x00000000` |
    | xe34 | `0x0a223004` | `0x00000000` |
    | xe35 | `0x0a224004` | `0x00000000` |
    | xe36 | `0x0a225004` | `0x00000000` |
    | xe37 | `0x0a226004` | `0x00000000` |
    | xe38 | `0x0a227004` | `0x00000000` |
    | xe39 | `0x0a228004` | `0x00000000` |
    | xe40 | `0x0a229004` | `0x00000000` |
    | xe41 | `0x0a22a004` | `0x00000000` |
    | xe42 | `0x0a22b004` | `0x00000000` |
    | xe43 | `0x0a22c004` | `0x00000000` |
    | xe44 | `0x0a22d004` | `0x00000000` |
    | xe45 | `0x0a22e004` | `0x00000000` |
    | xe46 | `0x0a22f004` | `0x00000000` |
    | xe47 | `0x0a230004` | `0x00000000` |
    | xe48 | `0x0a231004` | `0x00000000` |
    | xe49 | `0x0a232004` | `0x00000000` |
    | xe50 | `0x0a233004` | `0x00000000` |
    | xe51 | `0x0a234004` | `0x00000000` |
    | lb0 | `0x0a241004` | `0x00000000` |

---

## TDBGC5r

- **Address:** `0x0a200005`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #5

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200005` | `0x00000000` |
    | xe0 | `0x0a201005` | `0x00000000` |
    | xe1 | `0x0a202005` | `0x00000000` |
    | xe2 | `0x0a203005` | `0x00000000` |
    | xe3 | `0x0a204005` | `0x00000000` |
    | xe4 | `0x0a205005` | `0x00000000` |
    | xe5 | `0x0a206005` | `0x00000000` |
    | xe6 | `0x0a207005` | `0x00000000` |
    | xe7 | `0x0a208005` | `0x00000000` |
    | xe8 | `0x0a209005` | `0x00000000` |
    | xe9 | `0x0a20a005` | `0x00000000` |
    | xe10 | `0x0a20b005` | `0x00000000` |
    | xe11 | `0x0a20c005` | `0x00000000` |
    | xe12 | `0x0a20d005` | `0x00000000` |
    | xe13 | `0x0a20e005` | `0x00000000` |
    | xe14 | `0x0a20f005` | `0x00000000` |
    | xe15 | `0x0a210005` | `0x00000000` |
    | xe16 | `0x0a211005` | `0x00000000` |
    | xe17 | `0x0a212005` | `0x00000000` |
    | xe18 | `0x0a213005` | `0x00000000` |
    | xe19 | `0x0a214005` | `0x00000000` |
    | xe20 | `0x0a215005` | `0x00000000` |
    | xe21 | `0x0a216005` | `0x00000000` |
    | xe22 | `0x0a217005` | `0x00000000` |
    | xe23 | `0x0a218005` | `0x00000000` |
    | xe24 | `0x0a219005` | `0x00000000` |
    | xe25 | `0x0a21a005` | `0x00000000` |
    | xe26 | `0x0a21b005` | `0x00000000` |
    | xe27 | `0x0a21c005` | `0x00000000` |
    | xe28 | `0x0a21d005` | `0x00000000` |
    | xe29 | `0x0a21e005` | `0x00000000` |
    | xe30 | `0x0a21f005` | `0x00000000` |
    | xe31 | `0x0a220005` | `0x00000000` |
    | xe32 | `0x0a221005` | `0x00000000` |
    | xe33 | `0x0a222005` | `0x00000000` |
    | xe34 | `0x0a223005` | `0x00000000` |
    | xe35 | `0x0a224005` | `0x00000000` |
    | xe36 | `0x0a225005` | `0x00000000` |
    | xe37 | `0x0a226005` | `0x00000000` |
    | xe38 | `0x0a227005` | `0x00000000` |
    | xe39 | `0x0a228005` | `0x00000000` |
    | xe40 | `0x0a229005` | `0x00000000` |
    | xe41 | `0x0a22a005` | `0x00000000` |
    | xe42 | `0x0a22b005` | `0x00000000` |
    | xe43 | `0x0a22c005` | `0x00000000` |
    | xe44 | `0x0a22d005` | `0x00000000` |
    | xe45 | `0x0a22e005` | `0x00000000` |
    | xe46 | `0x0a22f005` | `0x00000000` |
    | xe47 | `0x0a230005` | `0x00000000` |
    | xe48 | `0x0a231005` | `0x00000000` |
    | xe49 | `0x0a232005` | `0x00000000` |
    | xe50 | `0x0a233005` | `0x00000000` |
    | xe51 | `0x0a234005` | `0x00000000` |
    | lb0 | `0x0a241005` | `0x00000000` |

---

## TDBGC6r

- **Address:** `0x0a200006`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #6

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200006` | `0x00000000` |
    | xe0 | `0x0a201006` | `0x00000000` |
    | xe1 | `0x0a202006` | `0x00000000` |
    | xe2 | `0x0a203006` | `0x00000000` |
    | xe3 | `0x0a204006` | `0x00000000` |
    | xe4 | `0x0a205006` | `0x00000000` |
    | xe5 | `0x0a206006` | `0x00000000` |
    | xe6 | `0x0a207006` | `0x00000000` |
    | xe7 | `0x0a208006` | `0x00000000` |
    | xe8 | `0x0a209006` | `0x00000000` |
    | xe9 | `0x0a20a006` | `0x00000000` |
    | xe10 | `0x0a20b006` | `0x00000000` |
    | xe11 | `0x0a20c006` | `0x00000000` |
    | xe12 | `0x0a20d006` | `0x00000000` |
    | xe13 | `0x0a20e006` | `0x00000000` |
    | xe14 | `0x0a20f006` | `0x00000000` |
    | xe15 | `0x0a210006` | `0x00000000` |
    | xe16 | `0x0a211006` | `0x00000000` |
    | xe17 | `0x0a212006` | `0x00000000` |
    | xe18 | `0x0a213006` | `0x00000000` |
    | xe19 | `0x0a214006` | `0x00000000` |
    | xe20 | `0x0a215006` | `0x00000000` |
    | xe21 | `0x0a216006` | `0x00000000` |
    | xe22 | `0x0a217006` | `0x00000000` |
    | xe23 | `0x0a218006` | `0x00000000` |
    | xe24 | `0x0a219006` | `0x00000000` |
    | xe25 | `0x0a21a006` | `0x00000000` |
    | xe26 | `0x0a21b006` | `0x00000000` |
    | xe27 | `0x0a21c006` | `0x00000000` |
    | xe28 | `0x0a21d006` | `0x00000000` |
    | xe29 | `0x0a21e006` | `0x00000000` |
    | xe30 | `0x0a21f006` | `0x00000000` |
    | xe31 | `0x0a220006` | `0x00000000` |
    | xe32 | `0x0a221006` | `0x00000000` |
    | xe33 | `0x0a222006` | `0x00000000` |
    | xe34 | `0x0a223006` | `0x00000000` |
    | xe35 | `0x0a224006` | `0x00000000` |
    | xe36 | `0x0a225006` | `0x00000000` |
    | xe37 | `0x0a226006` | `0x00000000` |
    | xe38 | `0x0a227006` | `0x00000000` |
    | xe39 | `0x0a228006` | `0x00000000` |
    | xe40 | `0x0a229006` | `0x00000000` |
    | xe41 | `0x0a22a006` | `0x00000000` |
    | xe42 | `0x0a22b006` | `0x00000000` |
    | xe43 | `0x0a22c006` | `0x00000000` |
    | xe44 | `0x0a22d006` | `0x00000000` |
    | xe45 | `0x0a22e006` | `0x00000000` |
    | xe46 | `0x0a22f006` | `0x00000000` |
    | xe47 | `0x0a230006` | `0x00000000` |
    | xe48 | `0x0a231006` | `0x00000000` |
    | xe49 | `0x0a232006` | `0x00000000` |
    | xe50 | `0x0a233006` | `0x00000000` |
    | xe51 | `0x0a234006` | `0x00000000` |
    | lb0 | `0x0a241006` | `0x00000000` |

---

## TDBGC7r

- **Address:** `0x0a200007`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #7

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200007` | `0x00000000` |
    | xe0 | `0x0a201007` | `0x00000000` |
    | xe1 | `0x0a202007` | `0x00000000` |
    | xe2 | `0x0a203007` | `0x00000000` |
    | xe3 | `0x0a204007` | `0x00000000` |
    | xe4 | `0x0a205007` | `0x00000000` |
    | xe5 | `0x0a206007` | `0x00000000` |
    | xe6 | `0x0a207007` | `0x00000000` |
    | xe7 | `0x0a208007` | `0x00000000` |
    | xe8 | `0x0a209007` | `0x00000000` |
    | xe9 | `0x0a20a007` | `0x00000000` |
    | xe10 | `0x0a20b007` | `0x00000000` |
    | xe11 | `0x0a20c007` | `0x00000000` |
    | xe12 | `0x0a20d007` | `0x00000000` |
    | xe13 | `0x0a20e007` | `0x00000000` |
    | xe14 | `0x0a20f007` | `0x00000000` |
    | xe15 | `0x0a210007` | `0x00000000` |
    | xe16 | `0x0a211007` | `0x00000000` |
    | xe17 | `0x0a212007` | `0x00000000` |
    | xe18 | `0x0a213007` | `0x00000000` |
    | xe19 | `0x0a214007` | `0x00000000` |
    | xe20 | `0x0a215007` | `0x00000000` |
    | xe21 | `0x0a216007` | `0x00000000` |
    | xe22 | `0x0a217007` | `0x00000000` |
    | xe23 | `0x0a218007` | `0x00000000` |
    | xe24 | `0x0a219007` | `0x00000000` |
    | xe25 | `0x0a21a007` | `0x00000000` |
    | xe26 | `0x0a21b007` | `0x00000000` |
    | xe27 | `0x0a21c007` | `0x00000000` |
    | xe28 | `0x0a21d007` | `0x00000000` |
    | xe29 | `0x0a21e007` | `0x00000000` |
    | xe30 | `0x0a21f007` | `0x00000000` |
    | xe31 | `0x0a220007` | `0x00000000` |
    | xe32 | `0x0a221007` | `0x00000000` |
    | xe33 | `0x0a222007` | `0x00000000` |
    | xe34 | `0x0a223007` | `0x00000000` |
    | xe35 | `0x0a224007` | `0x00000000` |
    | xe36 | `0x0a225007` | `0x00000000` |
    | xe37 | `0x0a226007` | `0x00000000` |
    | xe38 | `0x0a227007` | `0x00000000` |
    | xe39 | `0x0a228007` | `0x00000000` |
    | xe40 | `0x0a229007` | `0x00000000` |
    | xe41 | `0x0a22a007` | `0x00000000` |
    | xe42 | `0x0a22b007` | `0x00000000` |
    | xe43 | `0x0a22c007` | `0x00000000` |
    | xe44 | `0x0a22d007` | `0x00000000` |
    | xe45 | `0x0a22e007` | `0x00000000` |
    | xe46 | `0x0a22f007` | `0x00000000` |
    | xe47 | `0x0a230007` | `0x00000000` |
    | xe48 | `0x0a231007` | `0x00000000` |
    | xe49 | `0x0a232007` | `0x00000000` |
    | xe50 | `0x0a233007` | `0x00000000` |
    | xe51 | `0x0a234007` | `0x00000000` |
    | lb0 | `0x0a241007` | `0x00000000` |

---

## TDBGC8r

- **Address:** `0x0a200008`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #8

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200008` | `0x00000000` |
    | xe0 | `0x0a201008` | `0x00000000` |
    | xe1 | `0x0a202008` | `0x00000000` |
    | xe2 | `0x0a203008` | `0x00000000` |
    | xe3 | `0x0a204008` | `0x00000000` |
    | xe4 | `0x0a205008` | `0x00000000` |
    | xe5 | `0x0a206008` | `0x00000000` |
    | xe6 | `0x0a207008` | `0x00000000` |
    | xe7 | `0x0a208008` | `0x00000000` |
    | xe8 | `0x0a209008` | `0x00000000` |
    | xe9 | `0x0a20a008` | `0x00000000` |
    | xe10 | `0x0a20b008` | `0x00000000` |
    | xe11 | `0x0a20c008` | `0x00000000` |
    | xe12 | `0x0a20d008` | `0x00000000` |
    | xe13 | `0x0a20e008` | `0x00000000` |
    | xe14 | `0x0a20f008` | `0x00000000` |
    | xe15 | `0x0a210008` | `0x00000000` |
    | xe16 | `0x0a211008` | `0x00000000` |
    | xe17 | `0x0a212008` | `0x00000000` |
    | xe18 | `0x0a213008` | `0x00000000` |
    | xe19 | `0x0a214008` | `0x00000000` |
    | xe20 | `0x0a215008` | `0x00000000` |
    | xe21 | `0x0a216008` | `0x00000000` |
    | xe22 | `0x0a217008` | `0x00000000` |
    | xe23 | `0x0a218008` | `0x00000000` |
    | xe24 | `0x0a219008` | `0x00000000` |
    | xe25 | `0x0a21a008` | `0x00000000` |
    | xe26 | `0x0a21b008` | `0x00000000` |
    | xe27 | `0x0a21c008` | `0x00000000` |
    | xe28 | `0x0a21d008` | `0x00000000` |
    | xe29 | `0x0a21e008` | `0x00000000` |
    | xe30 | `0x0a21f008` | `0x00000000` |
    | xe31 | `0x0a220008` | `0x00000000` |
    | xe32 | `0x0a221008` | `0x00000000` |
    | xe33 | `0x0a222008` | `0x00000000` |
    | xe34 | `0x0a223008` | `0x00000000` |
    | xe35 | `0x0a224008` | `0x00000000` |
    | xe36 | `0x0a225008` | `0x00000000` |
    | xe37 | `0x0a226008` | `0x00000000` |
    | xe38 | `0x0a227008` | `0x00000000` |
    | xe39 | `0x0a228008` | `0x00000000` |
    | xe40 | `0x0a229008` | `0x00000000` |
    | xe41 | `0x0a22a008` | `0x00000000` |
    | xe42 | `0x0a22b008` | `0x00000000` |
    | xe43 | `0x0a22c008` | `0x00000000` |
    | xe44 | `0x0a22d008` | `0x00000000` |
    | xe45 | `0x0a22e008` | `0x00000000` |
    | xe46 | `0x0a22f008` | `0x00000000` |
    | xe47 | `0x0a230008` | `0x00000000` |
    | xe48 | `0x0a231008` | `0x00000000` |
    | xe49 | `0x0a232008` | `0x00000000` |
    | xe50 | `0x0a233008` | `0x00000000` |
    | xe51 | `0x0a234008` | `0x00000000` |
    | lb0 | `0x0a241008` | `0x00000000` |

---

## TDBGC9r

- **Address:** `0x0a200009`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #9

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a200009` | `0x00000000` |
    | xe0 | `0x0a201009` | `0x00000000` |
    | xe1 | `0x0a202009` | `0x00000000` |
    | xe2 | `0x0a203009` | `0x00000000` |
    | xe3 | `0x0a204009` | `0x00000000` |
    | xe4 | `0x0a205009` | `0x00000000` |
    | xe5 | `0x0a206009` | `0x00000000` |
    | xe6 | `0x0a207009` | `0x00000000` |
    | xe7 | `0x0a208009` | `0x00000000` |
    | xe8 | `0x0a209009` | `0x00000000` |
    | xe9 | `0x0a20a009` | `0x00000000` |
    | xe10 | `0x0a20b009` | `0x00000000` |
    | xe11 | `0x0a20c009` | `0x00000000` |
    | xe12 | `0x0a20d009` | `0x00000000` |
    | xe13 | `0x0a20e009` | `0x00000000` |
    | xe14 | `0x0a20f009` | `0x00000000` |
    | xe15 | `0x0a210009` | `0x00000000` |
    | xe16 | `0x0a211009` | `0x00000000` |
    | xe17 | `0x0a212009` | `0x00000000` |
    | xe18 | `0x0a213009` | `0x00000000` |
    | xe19 | `0x0a214009` | `0x00000000` |
    | xe20 | `0x0a215009` | `0x00000000` |
    | xe21 | `0x0a216009` | `0x00000000` |
    | xe22 | `0x0a217009` | `0x00000000` |
    | xe23 | `0x0a218009` | `0x00000000` |
    | xe24 | `0x0a219009` | `0x00000000` |
    | xe25 | `0x0a21a009` | `0x00000000` |
    | xe26 | `0x0a21b009` | `0x00000000` |
    | xe27 | `0x0a21c009` | `0x00000000` |
    | xe28 | `0x0a21d009` | `0x00000000` |
    | xe29 | `0x0a21e009` | `0x00000000` |
    | xe30 | `0x0a21f009` | `0x00000000` |
    | xe31 | `0x0a220009` | `0x00000000` |
    | xe32 | `0x0a221009` | `0x00000000` |
    | xe33 | `0x0a222009` | `0x00000000` |
    | xe34 | `0x0a223009` | `0x00000000` |
    | xe35 | `0x0a224009` | `0x00000000` |
    | xe36 | `0x0a225009` | `0x00000000` |
    | xe37 | `0x0a226009` | `0x00000000` |
    | xe38 | `0x0a227009` | `0x00000000` |
    | xe39 | `0x0a228009` | `0x00000000` |
    | xe40 | `0x0a229009` | `0x00000000` |
    | xe41 | `0x0a22a009` | `0x00000000` |
    | xe42 | `0x0a22b009` | `0x00000000` |
    | xe43 | `0x0a22c009` | `0x00000000` |
    | xe44 | `0x0a22d009` | `0x00000000` |
    | xe45 | `0x0a22e009` | `0x00000000` |
    | xe46 | `0x0a22f009` | `0x00000000` |
    | xe47 | `0x0a230009` | `0x00000000` |
    | xe48 | `0x0a231009` | `0x00000000` |
    | xe49 | `0x0a232009` | `0x00000000` |
    | xe50 | `0x0a233009` | `0x00000000` |
    | xe51 | `0x0a234009` | `0x00000000` |
    | lb0 | `0x0a241009` | `0x00000000` |

---

## TDBGC10r

- **Address:** `0x0a20000a`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #10

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000a` | `0x00000000` |
    | xe0 | `0x0a20100a` | `0x00000000` |
    | xe1 | `0x0a20200a` | `0x00000000` |
    | xe2 | `0x0a20300a` | `0x00000000` |
    | xe3 | `0x0a20400a` | `0x00000000` |
    | xe4 | `0x0a20500a` | `0x00000000` |
    | xe5 | `0x0a20600a` | `0x00000000` |
    | xe6 | `0x0a20700a` | `0x00000000` |
    | xe7 | `0x0a20800a` | `0x00000000` |
    | xe8 | `0x0a20900a` | `0x00000000` |
    | xe9 | `0x0a20a00a` | `0x00000000` |
    | xe10 | `0x0a20b00a` | `0x00000000` |
    | xe11 | `0x0a20c00a` | `0x00000000` |
    | xe12 | `0x0a20d00a` | `0x00000000` |
    | xe13 | `0x0a20e00a` | `0x00000000` |
    | xe14 | `0x0a20f00a` | `0x00000000` |
    | xe15 | `0x0a21000a` | `0x00000000` |
    | xe16 | `0x0a21100a` | `0x00000000` |
    | xe17 | `0x0a21200a` | `0x00000000` |
    | xe18 | `0x0a21300a` | `0x00000000` |
    | xe19 | `0x0a21400a` | `0x00000000` |
    | xe20 | `0x0a21500a` | `0x00000000` |
    | xe21 | `0x0a21600a` | `0x00000000` |
    | xe22 | `0x0a21700a` | `0x00000000` |
    | xe23 | `0x0a21800a` | `0x00000000` |
    | xe24 | `0x0a21900a` | `0x00000000` |
    | xe25 | `0x0a21a00a` | `0x00000000` |
    | xe26 | `0x0a21b00a` | `0x00000000` |
    | xe27 | `0x0a21c00a` | `0x00000000` |
    | xe28 | `0x0a21d00a` | `0x00000000` |
    | xe29 | `0x0a21e00a` | `0x00000000` |
    | xe30 | `0x0a21f00a` | `0x00000000` |
    | xe31 | `0x0a22000a` | `0x00000000` |
    | xe32 | `0x0a22100a` | `0x00000000` |
    | xe33 | `0x0a22200a` | `0x00000000` |
    | xe34 | `0x0a22300a` | `0x00000000` |
    | xe35 | `0x0a22400a` | `0x00000000` |
    | xe36 | `0x0a22500a` | `0x00000000` |
    | xe37 | `0x0a22600a` | `0x00000000` |
    | xe38 | `0x0a22700a` | `0x00000000` |
    | xe39 | `0x0a22800a` | `0x00000000` |
    | xe40 | `0x0a22900a` | `0x00000000` |
    | xe41 | `0x0a22a00a` | `0x00000000` |
    | xe42 | `0x0a22b00a` | `0x00000000` |
    | xe43 | `0x0a22c00a` | `0x00000000` |
    | xe44 | `0x0a22d00a` | `0x00000000` |
    | xe45 | `0x0a22e00a` | `0x00000000` |
    | xe46 | `0x0a22f00a` | `0x00000000` |
    | xe47 | `0x0a23000a` | `0x00000000` |
    | xe48 | `0x0a23100a` | `0x00000000` |
    | xe49 | `0x0a23200a` | `0x00000000` |
    | xe50 | `0x0a23300a` | `0x00000000` |
    | xe51 | `0x0a23400a` | `0x00000000` |
    | lb0 | `0x0a24100a` | `0x00000000` |

---

## TDBGC11r

- **Address:** `0x0a20000b`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #11

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000b` | `0x00000000` |
    | xe0 | `0x0a20100b` | `0x00000000` |
    | xe1 | `0x0a20200b` | `0x00000000` |
    | xe2 | `0x0a20300b` | `0x00000000` |
    | xe3 | `0x0a20400b` | `0x00000000` |
    | xe4 | `0x0a20500b` | `0x00000000` |
    | xe5 | `0x0a20600b` | `0x00000000` |
    | xe6 | `0x0a20700b` | `0x00000000` |
    | xe7 | `0x0a20800b` | `0x00000000` |
    | xe8 | `0x0a20900b` | `0x00000000` |
    | xe9 | `0x0a20a00b` | `0x00000000` |
    | xe10 | `0x0a20b00b` | `0x00000000` |
    | xe11 | `0x0a20c00b` | `0x00000000` |
    | xe12 | `0x0a20d00b` | `0x00000000` |
    | xe13 | `0x0a20e00b` | `0x00000000` |
    | xe14 | `0x0a20f00b` | `0x00000000` |
    | xe15 | `0x0a21000b` | `0x00000000` |
    | xe16 | `0x0a21100b` | `0x00000000` |
    | xe17 | `0x0a21200b` | `0x00000000` |
    | xe18 | `0x0a21300b` | `0x00000000` |
    | xe19 | `0x0a21400b` | `0x00000000` |
    | xe20 | `0x0a21500b` | `0x00000000` |
    | xe21 | `0x0a21600b` | `0x00000000` |
    | xe22 | `0x0a21700b` | `0x00000000` |
    | xe23 | `0x0a21800b` | `0x00000000` |
    | xe24 | `0x0a21900b` | `0x00000000` |
    | xe25 | `0x0a21a00b` | `0x00000000` |
    | xe26 | `0x0a21b00b` | `0x00000000` |
    | xe27 | `0x0a21c00b` | `0x00000000` |
    | xe28 | `0x0a21d00b` | `0x00000000` |
    | xe29 | `0x0a21e00b` | `0x00000000` |
    | xe30 | `0x0a21f00b` | `0x00000000` |
    | xe31 | `0x0a22000b` | `0x00000000` |
    | xe32 | `0x0a22100b` | `0x00000000` |
    | xe33 | `0x0a22200b` | `0x00000000` |
    | xe34 | `0x0a22300b` | `0x00000000` |
    | xe35 | `0x0a22400b` | `0x00000000` |
    | xe36 | `0x0a22500b` | `0x00000000` |
    | xe37 | `0x0a22600b` | `0x00000000` |
    | xe38 | `0x0a22700b` | `0x00000000` |
    | xe39 | `0x0a22800b` | `0x00000000` |
    | xe40 | `0x0a22900b` | `0x00000000` |
    | xe41 | `0x0a22a00b` | `0x00000000` |
    | xe42 | `0x0a22b00b` | `0x00000000` |
    | xe43 | `0x0a22c00b` | `0x00000000` |
    | xe44 | `0x0a22d00b` | `0x00000000` |
    | xe45 | `0x0a22e00b` | `0x00000000` |
    | xe46 | `0x0a22f00b` | `0x00000000` |
    | xe47 | `0x0a23000b` | `0x00000000` |
    | xe48 | `0x0a23100b` | `0x00000000` |
    | xe49 | `0x0a23200b` | `0x00000000` |
    | xe50 | `0x0a23300b` | `0x00000000` |
    | xe51 | `0x0a23400b` | `0x00000000` |
    | lb0 | `0x0a24100b` | `0x00000000` |

---

## EGR_TRILL_TX_PKTSr

- **Address:** `0x0a20000c`  ·  **Size:** 4 bytes
- **Function:** Number of packets transmitted from this port with TRILL ethertype.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000c` | `0x00000000` |
    | xe0 | `0x0a20100c` | `0x00000000` |
    | xe1 | `0x0a20200c` | `0x00000000` |
    | xe2 | `0x0a20300c` | `0x00000000` |
    | xe3 | `0x0a20400c` | `0x00000000` |
    | xe4 | `0x0a20500c` | `0x00000000` |
    | xe5 | `0x0a20600c` | `0x00000000` |
    | xe6 | `0x0a20700c` | `0x00000000` |
    | xe7 | `0x0a20800c` | `0x00000000` |
    | xe8 | `0x0a20900c` | `0x00000000` |
    | xe9 | `0x0a20a00c` | `0x00000000` |
    | xe10 | `0x0a20b00c` | `0x00000000` |
    | xe11 | `0x0a20c00c` | `0x00000000` |
    | xe12 | `0x0a20d00c` | `0x00000000` |
    | xe13 | `0x0a20e00c` | `0x00000000` |
    | xe14 | `0x0a20f00c` | `0x00000000` |
    | xe15 | `0x0a21000c` | `0x00000000` |
    | xe16 | `0x0a21100c` | `0x00000000` |
    | xe17 | `0x0a21200c` | `0x00000000` |
    | xe18 | `0x0a21300c` | `0x00000000` |
    | xe19 | `0x0a21400c` | `0x00000000` |
    | xe20 | `0x0a21500c` | `0x00000000` |
    | xe21 | `0x0a21600c` | `0x00000000` |
    | xe22 | `0x0a21700c` | `0x00000000` |
    | xe23 | `0x0a21800c` | `0x00000000` |
    | xe24 | `0x0a21900c` | `0x00000000` |
    | xe25 | `0x0a21a00c` | `0x00000000` |
    | xe26 | `0x0a21b00c` | `0x00000000` |
    | xe27 | `0x0a21c00c` | `0x00000000` |
    | xe28 | `0x0a21d00c` | `0x00000000` |
    | xe29 | `0x0a21e00c` | `0x00000000` |
    | xe30 | `0x0a21f00c` | `0x00000000` |
    | xe31 | `0x0a22000c` | `0x00000000` |
    | xe32 | `0x0a22100c` | `0x00000000` |
    | xe33 | `0x0a22200c` | `0x00000000` |
    | xe34 | `0x0a22300c` | `0x00000000` |
    | xe35 | `0x0a22400c` | `0x00000000` |
    | xe36 | `0x0a22500c` | `0x00000000` |
    | xe37 | `0x0a22600c` | `0x00000000` |
    | xe38 | `0x0a22700c` | `0x00000000` |
    | xe39 | `0x0a22800c` | `0x00000000` |
    | xe40 | `0x0a22900c` | `0x00000000` |
    | xe41 | `0x0a22a00c` | `0x00000000` |
    | xe42 | `0x0a22b00c` | `0x00000000` |
    | xe43 | `0x0a22c00c` | `0x00000000` |
    | xe44 | `0x0a22d00c` | `0x00000000` |
    | xe45 | `0x0a22e00c` | `0x00000000` |
    | xe46 | `0x0a22f00c` | `0x00000000` |
    | xe47 | `0x0a23000c` | `0x00000000` |
    | xe48 | `0x0a23100c` | `0x00000000` |
    | xe49 | `0x0a23200c` | `0x00000000` |
    | xe50 | `0x0a23300c` | `0x00000000` |
    | xe51 | `0x0a23400c` | `0x00000000` |
    | lb0 | `0x0a24100c` | `0x00000000` |

---

## EGR_TRILL_TX_ACCESS_PORT_TRILL_PKTS_DISCARDEDr

- **Address:** `0x0a20000d`  ·  **Size:** 4 bytes
- **Function:** Number of TRILL frames dropped on an outgoing TRILL access port.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000d` | `0x00000000` |
    | xe0 | `0x0a20100d` | `0x00000000` |
    | xe1 | `0x0a20200d` | `0x00000000` |
    | xe2 | `0x0a20300d` | `0x00000000` |
    | xe3 | `0x0a20400d` | `0x00000000` |
    | xe4 | `0x0a20500d` | `0x00000000` |
    | xe5 | `0x0a20600d` | `0x00000000` |
    | xe6 | `0x0a20700d` | `0x00000000` |
    | xe7 | `0x0a20800d` | `0x00000000` |
    | xe8 | `0x0a20900d` | `0x00000000` |
    | xe9 | `0x0a20a00d` | `0x00000000` |
    | xe10 | `0x0a20b00d` | `0x00000000` |
    | xe11 | `0x0a20c00d` | `0x00000000` |
    | xe12 | `0x0a20d00d` | `0x00000000` |
    | xe13 | `0x0a20e00d` | `0x00000000` |
    | xe14 | `0x0a20f00d` | `0x00000000` |
    | xe15 | `0x0a21000d` | `0x00000000` |
    | xe16 | `0x0a21100d` | `0x00000000` |
    | xe17 | `0x0a21200d` | `0x00000000` |
    | xe18 | `0x0a21300d` | `0x00000000` |
    | xe19 | `0x0a21400d` | `0x00000000` |
    | xe20 | `0x0a21500d` | `0x00000000` |
    | xe21 | `0x0a21600d` | `0x00000000` |
    | xe22 | `0x0a21700d` | `0x00000000` |
    | xe23 | `0x0a21800d` | `0x00000000` |
    | xe24 | `0x0a21900d` | `0x00000000` |
    | xe25 | `0x0a21a00d` | `0x00000000` |
    | xe26 | `0x0a21b00d` | `0x00000000` |
    | xe27 | `0x0a21c00d` | `0x00000000` |
    | xe28 | `0x0a21d00d` | `0x00000000` |
    | xe29 | `0x0a21e00d` | `0x00000000` |
    | xe30 | `0x0a21f00d` | `0x00000000` |
    | xe31 | `0x0a22000d` | `0x00000000` |
    | xe32 | `0x0a22100d` | `0x00000000` |
    | xe33 | `0x0a22200d` | `0x00000000` |
    | xe34 | `0x0a22300d` | `0x00000000` |
    | xe35 | `0x0a22400d` | `0x00000000` |
    | xe36 | `0x0a22500d` | `0x00000000` |
    | xe37 | `0x0a22600d` | `0x00000000` |
    | xe38 | `0x0a22700d` | `0x00000000` |
    | xe39 | `0x0a22800d` | `0x00000000` |
    | xe40 | `0x0a22900d` | `0x00000000` |
    | xe41 | `0x0a22a00d` | `0x00000000` |
    | xe42 | `0x0a22b00d` | `0x00000000` |
    | xe43 | `0x0a22c00d` | `0x00000000` |
    | xe44 | `0x0a22d00d` | `0x00000000` |
    | xe45 | `0x0a22e00d` | `0x00000000` |
    | xe46 | `0x0a22f00d` | `0x00000000` |
    | xe47 | `0x0a23000d` | `0x00000000` |
    | xe48 | `0x0a23100d` | `0x00000000` |
    | xe49 | `0x0a23200d` | `0x00000000` |
    | xe50 | `0x0a23300d` | `0x00000000` |
    | xe51 | `0x0a23400d` | `0x00000000` |
    | lb0 | `0x0a24100d` | `0x00000000` |

---

## EGR_TRILL_TX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDEDr

- **Address:** `0x0a20000e`  ·  **Size:** 4 bytes
- **Function:** Number of non-TRILL frames dropped on an outgoing TRILL network port.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000e` | `0x00000000` |
    | xe0 | `0x0a20100e` | `0x00000000` |
    | xe1 | `0x0a20200e` | `0x00000000` |
    | xe2 | `0x0a20300e` | `0x00000000` |
    | xe3 | `0x0a20400e` | `0x00000000` |
    | xe4 | `0x0a20500e` | `0x00000000` |
    | xe5 | `0x0a20600e` | `0x00000000` |
    | xe6 | `0x0a20700e` | `0x00000000` |
    | xe7 | `0x0a20800e` | `0x00000000` |
    | xe8 | `0x0a20900e` | `0x00000000` |
    | xe9 | `0x0a20a00e` | `0x00000000` |
    | xe10 | `0x0a20b00e` | `0x00000000` |
    | xe11 | `0x0a20c00e` | `0x00000000` |
    | xe12 | `0x0a20d00e` | `0x00000000` |
    | xe13 | `0x0a20e00e` | `0x00000000` |
    | xe14 | `0x0a20f00e` | `0x00000000` |
    | xe15 | `0x0a21000e` | `0x00000000` |
    | xe16 | `0x0a21100e` | `0x00000000` |
    | xe17 | `0x0a21200e` | `0x00000000` |
    | xe18 | `0x0a21300e` | `0x00000000` |
    | xe19 | `0x0a21400e` | `0x00000000` |
    | xe20 | `0x0a21500e` | `0x00000000` |
    | xe21 | `0x0a21600e` | `0x00000000` |
    | xe22 | `0x0a21700e` | `0x00000000` |
    | xe23 | `0x0a21800e` | `0x00000000` |
    | xe24 | `0x0a21900e` | `0x00000000` |
    | xe25 | `0x0a21a00e` | `0x00000000` |
    | xe26 | `0x0a21b00e` | `0x00000000` |
    | xe27 | `0x0a21c00e` | `0x00000000` |
    | xe28 | `0x0a21d00e` | `0x00000000` |
    | xe29 | `0x0a21e00e` | `0x00000000` |
    | xe30 | `0x0a21f00e` | `0x00000000` |
    | xe31 | `0x0a22000e` | `0x00000000` |
    | xe32 | `0x0a22100e` | `0x00000000` |
    | xe33 | `0x0a22200e` | `0x00000000` |
    | xe34 | `0x0a22300e` | `0x00000000` |
    | xe35 | `0x0a22400e` | `0x00000000` |
    | xe36 | `0x0a22500e` | `0x00000000` |
    | xe37 | `0x0a22600e` | `0x00000000` |
    | xe38 | `0x0a22700e` | `0x00000000` |
    | xe39 | `0x0a22800e` | `0x00000000` |
    | xe40 | `0x0a22900e` | `0x00000000` |
    | xe41 | `0x0a22a00e` | `0x00000000` |
    | xe42 | `0x0a22b00e` | `0x00000000` |
    | xe43 | `0x0a22c00e` | `0x00000000` |
    | xe44 | `0x0a22d00e` | `0x00000000` |
    | xe45 | `0x0a22e00e` | `0x00000000` |
    | xe46 | `0x0a22f00e` | `0x00000000` |
    | xe47 | `0x0a23000e` | `0x00000000` |
    | xe48 | `0x0a23100e` | `0x00000000` |
    | xe49 | `0x0a23200e` | `0x00000000` |
    | xe50 | `0x0a23300e` | `0x00000000` |
    | xe51 | `0x0a23400e` | `0x00000000` |
    | lb0 | `0x0a24100e` | `0x00000000` |

---

## TPCEr

- **Address:** `0x0a20000f`  ·  **Size:** 4 bytes
- **Function:** Egress Purge and Cell Error Drop Counter

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0a20000f` | `0x00000000` |
    | xe0 | `0x0a20100f` | `0x00000000` |
    | xe1 | `0x0a20200f` | `0x00000000` |
    | xe2 | `0x0a20300f` | `0x00000000` |
    | xe3 | `0x0a20400f` | `0x00000000` |
    | xe4 | `0x0a20500f` | `0x00000000` |
    | xe5 | `0x0a20600f` | `0x00000000` |
    | xe6 | `0x0a20700f` | `0x00000000` |
    | xe7 | `0x0a20800f` | `0x00000000` |
    | xe8 | `0x0a20900f` | `0x00000000` |
    | xe9 | `0x0a20a00f` | `0x00000000` |
    | xe10 | `0x0a20b00f` | `0x00000000` |
    | xe11 | `0x0a20c00f` | `0x00000000` |
    | xe12 | `0x0a20d00f` | `0x00000000` |
    | xe13 | `0x0a20e00f` | `0x00000000` |
    | xe14 | `0x0a20f00f` | `0x00000000` |
    | xe15 | `0x0a21000f` | `0x00000000` |
    | xe16 | `0x0a21100f` | `0x00000000` |
    | xe17 | `0x0a21200f` | `0x00000000` |
    | xe18 | `0x0a21300f` | `0x00000000` |
    | xe19 | `0x0a21400f` | `0x00000000` |
    | xe20 | `0x0a21500f` | `0x00000000` |
    | xe21 | `0x0a21600f` | `0x00000000` |
    | xe22 | `0x0a21700f` | `0x00000000` |
    | xe23 | `0x0a21800f` | `0x00000000` |
    | xe24 | `0x0a21900f` | `0x00000000` |
    | xe25 | `0x0a21a00f` | `0x00000000` |
    | xe26 | `0x0a21b00f` | `0x00000000` |
    | xe27 | `0x0a21c00f` | `0x00000000` |
    | xe28 | `0x0a21d00f` | `0x00000000` |
    | xe29 | `0x0a21e00f` | `0x00000000` |
    | xe30 | `0x0a21f00f` | `0x00000000` |
    | xe31 | `0x0a22000f` | `0x00000000` |
    | xe32 | `0x0a22100f` | `0x00000000` |
    | xe33 | `0x0a22200f` | `0x00000000` |
    | xe34 | `0x0a22300f` | `0x00000000` |
    | xe35 | `0x0a22400f` | `0x00000000` |
    | xe36 | `0x0a22500f` | `0x00000000` |
    | xe37 | `0x0a22600f` | `0x00000000` |
    | xe38 | `0x0a22700f` | `0x00000000` |
    | xe39 | `0x0a22800f` | `0x00000000` |
    | xe40 | `0x0a22900f` | `0x00000000` |
    | xe41 | `0x0a22a00f` | `0x00000000` |
    | xe42 | `0x0a22b00f` | `0x00000000` |
    | xe43 | `0x0a22c00f` | `0x00000000` |
    | xe44 | `0x0a22d00f` | `0x00000000` |
    | xe45 | `0x0a22e00f` | `0x00000000` |
    | xe46 | `0x0a22f00f` | `0x00000000` |
    | xe47 | `0x0a23000f` | `0x00000000` |
    | xe48 | `0x0a23100f` | `0x00000000` |
    | xe49 | `0x0a23200f` | `0x00000000` |
    | xe50 | `0x0a23300f` | `0x00000000` |
    | xe51 | `0x0a23400f` | `0x00000000` |
    | lb0 | `0x0a24100f` | `0x00000000` |

---

## EGR_LOGIC_TO_PHYS_MAPr

- **Address:** `0x0a2006c1`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PHYSICAL_PORT_NUMBER |
    | `[6:0]` | PHYS_PORT |

---

## TDBGC0_SELECTr

- **Address:** `0x0a280620`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #0 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280620` | `0x00000050` |

---

## TDBGC1_SELECTr

- **Address:** `0x0a280621`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #1 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280621` | `0x000000a0` |

---

## TDBGC2_SELECTr

- **Address:** `0x0a280622`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #2 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280622` | `0x00000040` |

---

## TDBGC3_SELECTr

- **Address:** `0x0a280623`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #3 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280623` | `0x00040000` |

---

## TDBGC4_SELECTr

- **Address:** `0x0a280624`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #4 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280624` | `0x00000011` |

---

## TDBGC5_SELECTr

- **Address:** `0x0a280625`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #5 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280625` | `0x00000088` |

---

## TDBGC6_SELECTr

- **Address:** `0x0a280626`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #6 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280626` | `0x00040000` |

---

## TDBGC7_SELECTr

- **Address:** `0x0a280627`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #7 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280627` | `0x00000000` |

---

## TDBGC8_SELECTr

- **Address:** `0x0a280628`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #8 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280628` | `0x00000000` |

---

## TDBGC9_SELECTr

- **Address:** `0x0a280629`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #9 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280629` | `0x00000000` |

---

## TDBGC10_SELECTr

- **Address:** `0x0a28062a`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #10 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a28062a` | `0x00000000` |

---

## TDBGC11_SELECTr

- **Address:** `0x0a28062b`  ·  **Size:** 4 bytes
- **Function:** Transmit debug counter #11 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a28062b` | `0x00000000` |

---

## EGR_Q_ENDr

- **Address:** `0x0a2806c0`  ·  **Size:** 4 bytes
- **Function:** Register starts an EQ Bus which is provided for later ECO reasons, if any.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a2806c0` | `0x00100000` |

---

## EGR_L1_CLK_RECOVERY_CTRLr

- **Address:** `0x0a280700`  ·  **Size:** 4 bytes
- **Function:** Select and Backup Select for top-level clock recovery

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PRI_PORT_SEL |
    | `[13:7]` | BKUP_PORT_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280700` | `0x00000000` |

---

## EGR_INTR1_ENABLEr

- **Address:** `0x0a280702`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for EGR_INTR1_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CM_PAR_ERR |
    | `[1]` | XLP0_PAR_ERR |
    | `[2]` | XLP1_PAR_ERR |
    | `[3]` | XLP2_PAR_ERR |
    | `[4]` | XLP3_PAR_ERR |
    | `[5]` | XLP4_PAR_ERR |
    | `[6]` | XLP5_PAR_ERR |
    | `[7]` | XLP6_PAR_ERR |
    | `[8]` | XLP7_PAR_ERR |
    | `[9]` | XLP8_PAR_ERR |
    | `[10]` | LBP_PAR_ERR |
    | `[11]` | EGR_STATS_COUNTER_TABLE_PAR_ERR |
    | `[12]` | EGR_EFP_COUNTER_TABLE_PAR_ERR |
    | `[13]` | EGR_PERQ_XMT_COUNTERS_PAR_ERR |
    | `[14]` | EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PAR_ERR |
    | `[15]` | EGR_VINTF_COUNTER_TABLE_PAR_ERR |
    | `[16]` | EGR_SERVICE_COUNTER_TABLE_PAR_ERR |
    | `[17]` | EGR_EFP_METER_TABLE_PAR_ERR |
    | `[18]` | EGR_EFP_POLICY_TABLE_PAR_ERR |
    | `[19]` | EGR_EFP_PW_INIT_COUNTERS_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280702` | `0x000fffff` |

---

## EGR_EDATABUF_PARITY_CONTROLr

- **Address:** `0x0a280703`  ·  **Size:** 4 bytes
- **Function:** Continuation of ram controls

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CM_ECC_EN |
    | `[1]` | XLP0_ECC_EN |
    | `[2]` | XLP1_ECC_EN |
    | `[3]` | XLP2_ECC_EN |
    | `[4]` | XLP3_ECC_EN |
    | `[5]` | XLP4_ECC_EN |
    | `[6]` | XLP5_ECC_EN |
    | `[7]` | XLP6_ECC_EN |
    | `[8]` | XLP7_ECC_EN |
    | `[9]` | XLP8_ECC_EN |
    | `[10]` | LBP_ECC_EN |
    | `[11]` | STATS_PAR_EN |
    | `[12]` | EFPCTR_PAR_EN |
    | `[13]` | PERQ_PAR_EN |
    | `[14]` | PERQ_BASE_ADDR_PAR_EN |
    | `[15]` | VINTFCTR_PAR_EN |
    | `[16]` | SVCCTR_PAR_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280703` | `0x0001ffff` |

---

## EGR_DATABUF_RAM_CONTROL_STBYr

- **Address:** `0x0a280704`  ·  **Size:** 4 bytes
- **Function:** Control register for stby bits of Edatabuf stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_PERQ_XMT_COUNTERS_BASE_ADDR |
    | `[1]` | EGR_EGESS_STATS_COUNTER |
    | `[2]` | XLP_BUFFER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280704` | `0x00000000` |

---

## EGR_DATABUF_RAM_CONTROL_PMr

- **Address:** `0x0a280705`  ·  **Size:** 4 bytes
- **Function:** Control register for PM bits of Edatabuf stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_VINTF_COUNTER_TABLE |
    | `[1]` | EGR_SERVICE_COUNTER_TABLE |
    | `[2]` | EGR_PERQ_XMT_COUNTERS |
    | `[3]` | EGR_EFP_COUNTER_TABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280705` | `0x00000000` |

---

## EGR_DATABUF_RAM_CONTROL_DCMr

- **Address:** `0x0a280706`  ·  **Size:** 4 bytes
- **Function:** Control register for dcm bits of Edatabuf stage memories

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_VINTF_COUNTER_TABLE |
    | `[1]` | EGR_SERVICE_COUNTER_TABLE |
    | `[2]` | EGR_PERQ_XMT_COUNTERS |
    | `[3]` | EGR_EFP_COUNTER_TABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280706` | `0x00000000` |

---

## EGR_DATABUF_RAM_CONTROL_1r

- **Address:** `0x0a280707`  ·  **Size:** 4 bytes
- **Function:** Control register for tm bits of Edatabuf stage memories (also used for pw_init memory in Efp stage)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_VINTF_COUNTER_TABLE_TM |
    | `[19:10]` | EGR_SERVICE_COUNTER_TABLE_TM |
    | `[29:20]` | EGR_PERQ_XMT_COUNTERS_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280707` | `0x00000000` |

---

## EGR_DATABUF_RAM_CONTROL_2r

- **Address:** `0x0a280708`  ·  **Size:** 4 bytes
- **Function:** Continuation of ram controls

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_EFP_COUNTER_TABLE_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280708` | `0x00000000` |

---

## EGR_START_XMIT_AFTER_MOP_ARRIVALr

- **Address:** `0x0a280721`  ·  **Size:** 4 bytes
- **Function:** For a new packet, always wait for MOP reach Edatabuf before transmitting

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VALUE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280721` | `0x00000000` |

---

## EGR_INTR1_STATUSr

- **Address:** `0x0a280d01`  ·  **Size:** 4 bytes
- **Function:** EP Interrupt 1  Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CM_PAR_ERR |
    | `[1]` | XLP0_PAR_ERR |
    | `[2]` | XLP1_PAR_ERR |
    | `[3]` | XLP2_PAR_ERR |
    | `[4]` | XLP3_PAR_ERR |
    | `[5]` | XLP4_PAR_ERR |
    | `[6]` | XLP5_PAR_ERR |
    | `[7]` | XLP6_PAR_ERR |
    | `[8]` | XLP7_PAR_ERR |
    | `[9]` | XLP8_PAR_ERR |
    | `[10]` | LBP_PAR_ERR |
    | `[11]` | EGR_STATS_COUNTER_TABLE_PAR_ERR |
    | `[12]` | EGR_EFP_COUNTER_TABLE_PAR_ERR |
    | `[13]` | EGR_PERQ_XMT_COUNTERS_PAR_ERR |
    | `[14]` | EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PAR_ERR |
    | `[15]` | EGR_VINTF_COUNTER_TABLE_PAR_ERR |
    | `[16]` | EGR_SERVICE_COUNTER_TABLE_PAR_ERR |
    | `[17]` | EGR_EFP_METER_TABLE_PAR_ERR |
    | `[18]` | EGR_EFP_POLICY_TABLE_PAR_ERR |
    | `[19]` | EGR_EFP_PW_INIT_COUNTERS_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d01` | `0x00000000` |

---

## EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PARITY_STATUS_INTRr

- **Address:** `0x0a280d09`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for  memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d09` | `0x00000000` |

---

## EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PARITY_STATUS_NACKr

- **Address:** `0x0a280d0a`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for EGR_PERQ_XMT_COUNTERS_BASE_ADDR memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d0a` | `0x00000000` |

---

## EGR_PERQ_XMT_COUNTERS_PARITY_STATUS_INTRr

- **Address:** `0x0a280d0b`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for EGR_PERQ_COUNTER_TABLE memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d0b` | `0x00000000` |

---

## EGR_PERQ_XMT_COUNTERS_PARITY_STATUS_NACKr

- **Address:** `0x0a280d0c`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for EGR_PERQ_COUNTER_TABLE memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d0c` | `0x00000000` |

---

## EGR_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0a280d0e`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for  memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d0e` | `0x00000000` |

---

## EGR_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0a280d0f`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for  memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d0f` | `0x00000000` |

---

## EGR_VINTF_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0a280d10`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d10` | `0x00000000` |

---

## EGR_VINTF_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0a280d11`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d11` | `0x00000000` |

---

## EGR_EFP_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0a280d12`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d12` | `0x00000000` |

---

## EGR_EFP_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0a280d13`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d13` | `0x00000000` |

---

## EGR_STATS_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0a280d14`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[20:2]` | ENTRY_IDX |
    | `[13:2]` | COUNTER_IDX |
    | `[20:14]` | PORT_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d14` | `0x00000000` |

---

## EGR_STATS_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0a280d15`  ·  **Size:** 4 bytes
- **Function:** Parity nack status register for EGR_STATS_COUNTER_TABLE memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[20:2]` | ENTRY_IDX |
    | `[13:2]` | COUNTER_IDX |
    | `[20:14]` | PORT_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d15` | `0x00000000` |

---

## EGR_XLP0_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d16`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d16` | `0x00000000` |

---

## EGR_XLP1_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d17`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d17` | `0x00000000` |

---

## EGR_XLP2_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d18`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d18` | `0x00000000` |

---

## EGR_XLP3_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d19`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d19` | `0x00000000` |

---

## EGR_XLP4_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1a`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1a` | `0x00000000` |

---

## EGR_XLP5_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1b`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1b` | `0x00000000` |

---

## EGR_XLP6_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1c`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1c` | `0x00000000` |

---

## EGR_XLP7_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1d`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1d` | `0x00000000` |

---

## EGR_XLP8_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1e`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1e` | `0x00000000` |

---

## EGR_LBP_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d1f`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d1f` | `0x00000000` |

---

## EGR_CM_BUFFER_STATUS_INTRr

- **Address:** `0x0a280d20`  ·  **Size:** 4 bytes
- **Function:** PARITY interrupt status register for memory

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR_MGRP |
    | `[1]` | ECC_ERR_2B_MGRP |
    | `[2]` | ECC_MULTI_MGRP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0a280d20` | `0x00000000` |

---

## EGR_SBS_CONTROLr

- **Address:** `0x0b280700`  ·  **Size:** 4 bytes
- **Function:** EP sbs control reg to select the pipe for acc_type 6 regs and mems

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PIPE_SELECT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | epipe0 | `0x0b280700` | `0x00000000` |

---


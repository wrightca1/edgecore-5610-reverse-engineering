# BCM56846 Registers — IPIPE block

_Ingress pipeline — parsing, L2/L3 lookup, VLAN, FP/TCAM, ingress policy_

809 registers.

---

## L2_AGE_TIMERr

- **Address:** `0x00180304`  ·  **Size:** 4 bytes
- **Function:** Age Timer Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | AGE_VAL |
    | `[20]` | AGE_ENA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180304` | `0x00000000` |

---

## L2_BULK_CONTROLr

- **Address:** `0x00180305`  ·  **Size:** 4 bytes
- **Function:** l2 Bluk Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2_MOD_FIFO_RECORD |
    | `[2:1]` | ACTION |
    | `[3]` | START |
    | `[4]` | COMPLETE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180305` | `0x0000001b` |

---

## L2_AGE_DEBUGr

- **Address:** `0x00180306`  ·  **Size:** 4 bytes
- **Function:** Age Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[16:0]` | AGE_COUNT |
    | `[17]` | RESERVED_1 |
    | `[18]` | START |
    | `[19]` | COMPLETE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180306` | `0x0001ffff` |

---

## IARB_LEARN_CONTROLr

- **Address:** `0x0018030a`  ·  **Size:** 4 bytes
- **Function:** Determines how the hit bits are set on a packet learn

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HITSA |
    | `[1]` | HITDA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018030a` | `0x00000001` |

---

## MOD_FIFO_CNTr

- **Address:** `0x0018030b`  ·  **Size:** 4 bytes
- **Function:** Mod Fifo entry counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | COUNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018030b` | `0x00000000` |

---

## LMEP_COMMON_1r

- **Address:** `0x0018030d`  ·  **Size:** 4 bytes
- **Function:** DA_47_16: The common MAC DA upper 32 bits for all LMEP packets.  These represent bits 47:16 of the DA.

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018030d` | `0x00000000` |

---

## LMEP_COMMON_2r

- **Address:** `0x0018030e`  ·  **Size:** 4 bytes
- **Function:** DA_15_3: The common MAC DA lower 13 bits for all LMEP packets.  These represent bits 15:3 of the DA.\nMY_MODID: MY_MODID

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | PFM |
    | `[2]` | L3 |
    | `[15:3]` | DA_15_3 |
    | `[23:16]` | MY_MODID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018030e` | `0x00000000` |

---

## OAM_TX_CONTROLr

- **Address:** `0x0018030f`  ·  **Size:** 4 bytes
- **Function:** TX_ENABLE: Enable oam lmep transmission\nCMIC_BUF_ENABLE: Enable cmic buffer\nDEBUG_ENABLE: accelerated time tick debug mode

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | TX_ENABLE |
    | `[1]` | CMIC_BUF_ENABLE |
    | `[2]` | DEBUG_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018030f` | `0x00000000` |

---

## OAM_CCM_COUNT_64r

- **Address:** `0x00180310`  ·  **Size:** 8 bytes
- **Function:** Lmep transmit ccm counts

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | CCM_2 |
    | `[7:2]` | CCM_3 |
    | `[16:8]` | CCM_4 |
    | `[28:17]` | CCM_5 |
    | `[61:44]` | CCM_7 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180310` | `0x0000000000000000` |

---

## OAM_TIMER_CONTROLr

- **Address:** `0x00180311`  ·  **Size:** 4 bytes
- **Function:** oam timer control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CLK_GRAN |
    | `[1]` | TIMER_ENABLE |
    | `[2]` | DBG_TRIGGER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180311` | `0x00000001` |

---

## ARB_RAM_DBGCTRLr

- **Address:** `0x00180312`  ·  **Size:** 4 bytes
- **Function:** ARB_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | LMEP_TM |
    | `[5]` | LMEP_PM |
    | `[15:6]` | PKT_TM |
    | `[16]` | PKT_PM |
    | `[17]` | PKT_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180312` | `0x00000000` |

---

## LMEP_PARITY_CONTROLr

- **Address:** `0x00180313`  ·  **Size:** 4 bytes
- **Function:** LMEP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180313` | `0x00000000` |

---

## LMEP_PARITY_STATUS_INTRr

- **Address:** `0x00180314`  ·  **Size:** 4 bytes
- **Function:** LMEP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180314` | `0x00000000` |

---

## LMEP_PARITY_STATUS_NACKr

- **Address:** `0x00180315`  ·  **Size:** 4 bytes
- **Function:** LMEP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180315` | `0x00000000` |

---

## IARB_PKT_ECC_CONTROLr

- **Address:** `0x00180316`  ·  **Size:** 4 bytes
- **Function:** IARB_PKT_ECC_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180316` | `0x00000001` |

---

## IARB_PKT_ECC_STATUS_INTRr

- **Address:** `0x00180317`  ·  **Size:** 4 bytes
- **Function:** IARB_PKT_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[12:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180317` | `0x00000000` |

---

## IARB_HDR_ECC_CONTROLr

- **Address:** `0x00180318`  ·  **Size:** 4 bytes
- **Function:** IARB_HDR_ECC_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180318` | `0x00000001` |

---

## IARB_HDR_ECC_STATUS_INTRr

- **Address:** `0x00180319`  ·  **Size:** 4 bytes
- **Function:** IARB_HDR_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180319` | `0x00000000` |

---

## IARB_LEARN_FIFO_ECC_CONTROLr

- **Address:** `0x0018031b`  ·  **Size:** 4 bytes
- **Function:** IARB_LERAN_FIFO_ECC_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |
    | `[1]` | FORCE_ECC_1B_ERR |
    | `[2]` | FORCE_ECC_2B_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018031b` | `0x00000001` |

---

## IARB_PIPE_X_LERAN_FIFO_ECC_STATUS_INTRr

- **Address:** `0x0018031c`  ·  **Size:** 4 bytes
- **Function:** IARB_PIPE_X_LERAN_FIFO_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018031c` | `0x00000000` |

---

## IARB_PIPE_Y_LERAN_FIFO_ECC_STATUS_INTRr

- **Address:** `0x0018031d`  ·  **Size:** 4 bytes
- **Function:** IARB_PIPE_Y_LERAN_FIFO_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018031d` | `0x00000000` |

---

## AUX_ARB_CONTROLr

- **Address:** `0x00180700`  ·  **Size:** 4 bytes
- **Function:** IP auxilary arbiter control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2_MOD_FIFO_ENABLE_MEMWR |
    | `[1]` | L2_MOD_FIFO_ENABLE_LEARN |
    | `[2]` | RESERVED_0 |
    | `[3]` | L2_MOD_FIFO_ENABLE_L2_INSERT |
    | `[4]` | L2_MOD_FIFO_ENABLE_AGE |
    | `[5]` | RESERVED_1 |
    | `[6]` | L2_MOD_FIFO_ENABLE_L2_DELETE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180700` | `0x00000012` |

---

## AUX_ARB_CONTROL_2r

- **Address:** `0x00180701`  ·  **Size:** 4 bytes
- **Function:** IP auxilary arbiter control register for FP functions. FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | CLK_GRAN |
    | `[2]` | RESERVED_AUX_ARB_CONTROL_2 |
    | `[10:3]` | SBUS_SPACING |
    | `[20:11]` | SBUS_ARB_BLOCK_CNT |
    | `[21]` | FP_REFRESH_ENABLE |
    | `[23:22]` | FP_REFRESH_MODE |
    | `[24]` | DLB_HGT_REFRESH_ENABLE |
    | `[25]` | DLB_HGT_256NS_REFRESH_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180701` | `0x0327f863` |

---

## ING_HW_RESET_CONTROL_1r

- **Address:** `0x00180702`  ·  **Size:** 4 bytes
- **Function:** Ingress Pipeline memory hardware initialization register #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | STAGE_NUMBER |
    | `[25:6]` | OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180702` | `0x00000000` |

---

## ING_HW_RESET_CONTROL_2r

- **Address:** `0x00180703`  ·  **Size:** 4 bytes
- **Function:** Ingress Pipeline memory hardware initialization register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[17:0]` | COUNT |
    | `[18]` | RESET_ALL |
    | `[19]` | VALID |
    | `[20]` | DONE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180703` | `0x00000000` |

---

## L2_AGE_DEBUG_2r

- **Address:** `0x00180707`  ·  **Size:** 4 bytes
- **Function:** Age Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[16:0]` | AGE_START_ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180707` | `0x00000000` |

---

## ING_Q_BEGINr

- **Address:** `0x00180708`  ·  **Size:** 4 bytes
- **Function:** Register starts the IQ Bus which is provided for later ECO reasons, if any.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SW_ENC_DEC_TCAM_KEY_MASK |
    | `[1]` | SUPPORT_8K_VP |
    | `[2]` | DISABLE_CELL_COMPRESSION |
    | `[15:3]` | RESERVED_0 |
    | `[31:17]` | RESERVED_1 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180708` | `0x00000007` |

---

## IARB_TDM_CONTROLr

- **Address:** `0x00180709`  ·  **Size:** 4 bytes
- **Function:** determines mapping of gxports onto tdm slots, slots[0-3] 16G, slots[4-7] 12G

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DISABLE |
    | `[7:1]` | TDM_WRAP_PTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180709` | `0x00000080` |

---

## ARB_EOP_DEBUGr

- **Address:** `0x0018070c`  ·  **Size:** 4 bytes
- **Function:** Forces accesses to stages to be eop resource

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ICFG |
    | `[1]` | IPARS |
    | `[2]` | IDISC |
    | `[3]` | IVXLT |
    | `[4]` | IMPLS |
    | `[5]` | IL2LU_1 |
    | `[6]` | IL2LU_2 |
    | `[7]` | IL2LU_3 |
    | `[8]` | IL3LU |
    | `[9]` | ILPM |
    | `[10]` | IRSEL1 |
    | `[11]` | ISW1 |
    | `[12]` | IFP |
    | `[13]` | IRSEL2 |
    | `[14]` | IDLB |
    | `[15]` | ISW2 |
    | `[16]` | IMPLS_TD_B0 |
    | `[17]` | IRSEL1_TD_B0 |
    | `[17]` | ISW2_TD_B0 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018070c` | `0x00020000` |

---

## IARB_SBUS_TIMERr

- **Address:** `0x0018071a`  ·  **Size:** 4 bytes
- **Function:** IARB_SBUS_TIMER

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[6:1]` | VALUE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0018071a` | `0x0000007e` |

---

## IP0_INTR_STATUSr

- **Address:** `0x00180d1e`  ·  **Size:** 4 bytes
- **Function:** IP0 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PPA_CMD_COMPLETE |
    | `[1]` | MEM_RESET_COMPLETE |
    | `[2]` | AGE_CMD_COMPLETE |
    | `[3]` | LMEP_PAR_ERR |
    | `[4]` | IARB_PKT_ERR |
    | `[5]` | IARB_HDR_ERR |
    | `[6]` | IARB_PIPE_X_LERAN_FIFO_ECC_ERR |
    | `[7]` | IARB_PIPE_Y_LERAN_FIFO_ECC_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180d1e` | `0x00000001` |

---

## IP0_INTR_ENABLEr

- **Address:** `0x00180d1f`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP0_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PPA_CMD_COMPLETE |
    | `[1]` | MEM_RESET_COMPLETE |
    | `[2]` | AGE_CMD_COMPLETE |
    | `[3]` | LMEP_PAR_ERR |
    | `[4]` | IARB_PKT_ERR |
    | `[5]` | IARB_HDR_ERR |
    | `[6]` | IARB_PIPE_X_LERAN_FIFO_ECC_ERR |
    | `[7]` | IARB_PIPE_Y_LERAN_FIFO_ECC_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x00180d1f` | `0x000000f0` |

---

## IE2E_CONTROLr

- **Address:** `0x0110060b`  ·  **Size:** 4 bytes
- **Function:** End-to-End Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HOL_TOCPU |
    | `[1]` | IBP_TOCPU |
    | `[2]` | HOL_ENABLE |
    | `[3]` | IBP_ENABLE |
    | `[4]` | VOQFC_ENABLE |
    | `[5]` | VOQFC_TO_CPU |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0110060b` | `0x00000000` |
    | xe0 | `0x0110160b` | `0x00000000` |
    | xe1 | `0x0110260b` | `0x00000000` |
    | xe2 | `0x0110360b` | `0x00000000` |
    | xe3 | `0x0110460b` | `0x00000000` |
    | xe4 | `0x0110560b` | `0x00000000` |
    | xe5 | `0x0110660b` | `0x00000000` |
    | xe6 | `0x0110760b` | `0x00000000` |
    | xe7 | `0x0110860b` | `0x00000000` |
    | xe8 | `0x0110960b` | `0x00000000` |
    | xe9 | `0x0110a60b` | `0x00000000` |
    | xe10 | `0x0110b60b` | `0x00000000` |
    | xe11 | `0x0110c60b` | `0x00000000` |
    | xe12 | `0x0110d60b` | `0x00000000` |
    | xe13 | `0x0110e60b` | `0x00000000` |
    | xe14 | `0x0110f60b` | `0x00000000` |
    | xe15 | `0x0111060b` | `0x00000000` |
    | xe16 | `0x0111160b` | `0x00000000` |
    | xe17 | `0x0111260b` | `0x00000000` |
    | xe18 | `0x0111360b` | `0x00000000` |
    | xe19 | `0x0111460b` | `0x00000000` |
    | xe20 | `0x0111560b` | `0x00000000` |
    | xe21 | `0x0111660b` | `0x00000000` |
    | xe22 | `0x0111760b` | `0x00000000` |
    | xe23 | `0x0111860b` | `0x00000000` |
    | xe24 | `0x0111960b` | `0x00000000` |
    | xe25 | `0x0111a60b` | `0x00000000` |
    | xe26 | `0x0111b60b` | `0x00000000` |
    | xe27 | `0x0111c60b` | `0x00000000` |
    | xe28 | `0x0111d60b` | `0x00000000` |
    | xe29 | `0x0111e60b` | `0x00000000` |
    | xe30 | `0x0111f60b` | `0x00000000` |
    | xe31 | `0x0112060b` | `0x00000000` |
    | xe32 | `0x0112160b` | `0x00000000` |
    | xe33 | `0x0112260b` | `0x00000000` |
    | xe34 | `0x0112360b` | `0x00000000` |
    | xe35 | `0x0112460b` | `0x00000000` |
    | xe36 | `0x0112560b` | `0x00000000` |
    | xe37 | `0x0112660b` | `0x00000000` |
    | xe38 | `0x0112760b` | `0x00000000` |
    | xe39 | `0x0112860b` | `0x00000000` |
    | xe40 | `0x0112960b` | `0x00000000` |
    | xe41 | `0x0112a60b` | `0x00000000` |
    | xe42 | `0x0112b60b` | `0x00000000` |
    | xe43 | `0x0112c60b` | `0x00000000` |
    | xe44 | `0x0112d60b` | `0x00000000` |
    | xe45 | `0x0112e60b` | `0x00000000` |
    | xe46 | `0x0112f60b` | `0x00000000` |
    | xe47 | `0x0113060b` | `0x00000000` |
    | xe48 | `0x0113160b` | `0x00000000` |
    | xe49 | `0x0113260b` | `0x00000000` |
    | xe50 | `0x0113360b` | `0x00000000` |
    | xe51 | `0x0113460b` | `0x00000000` |
    | lb0 | `0x0114160b` | `0x00000000` |

---

## ING_CONFIG_64r

- **Address:** `0x01180600`  ·  **Size:** 8 bytes
- **Function:** Switch configuration register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RESERVED_0 |
    | `[1]` | TRUNKS128 |
    | `[2]` | L2DH_EN |
    | `[2]` | L2DST_HIT_ENABLE |
    | `[3]` | L3SH_EN |
    | `[3]` | L3SRC_HIT_ENABLE |
    | `[4]` | RESERVED_1 |
    | `[5]` | CFI_AS_CNG |
    | `[6]` | SNAP_OTHER_DECODE_ENABLE |
    | `[7]` | STNMOVE_ON_L2SRC_DISC |
    | `[8]` | FB_A0_COMPATIBLE |
    | `[10:9]` | STACK_MODE |
    | `[11]` | CVLAN_CFI_AS_CNG |
    | `[12]` | APPLY_EGR_MASK_ON_L2 |
    | `[13]` | APPLY_EGR_MASK_ON_L3 |
    | `[14]` | SVL_ENABLE |
    | `[15]` | LOOKUP_L2MC_WITH_FID_ID |
    | `[17:16]` | RESERVED_2 |
    | `[18]` | DISABLE_E2E_HOL_CHECK |
    | `[21:19]` | LBID_RTAG |
    | `[22]` | APPLY_MTU_CHECK_ON_HIGIG_IPMC |
    | `[23]` | IGNORE_HG_HDR_LAG_FAILOVER |
    | `[24]` | IGNORE_HG_HDR_DONOT_LEARN |
    | `[25]` | IGNORE_HG_HDR_HDR_EXT_LEN |
    | `[26]` | IGNORE_MY_MODID |
    | `[27]` | IGMP_PKTS_UNICAST_IGNORE |
    | `[28]` | MLD_PKTS_UNICAST_IGNORE |
    | `[29]` | ARP_VALIDATION_EN |
    | `[30]` | MLD_CHECKS_ENABLE |
    | `[31]` | IPV4_RESERVED_MC_ADDR_IGMP_ENABLE |
    | `[32]` | IPV6_RESERVED_MC_ADDR_MLD_ENABLE |
    | `[33]` | IPV4_MC_MACDA_CHECK_ENABLE |
    | `[34]` | IPV6_MC_MACDA_CHECK_ENABLE |
    | `[36:35]` | TUNNEL_URPF_MODE |
    | `[37]` | TUNNEL_URPF_DEFAULTROUTECHECK |
    | `[38]` | L3IIF_URPF_SELECT |
    | `[40:39]` | ARP_RARP_TO_FP |
    | `[41]` | RESERVED_3 |
    | `[42]` | VFP_PRI_ACTION_FB2_MODE |
    | `[43]` | USE_PPD_SOURCE |
    | `[44]` | USE_PPD3_PKT_PRI_ENABLE |
    | `[45]` | USE_PPD3_DSCP_ENABLE |
    | `[46]` | USE_PPD3_DROP_ENABLE |
    | `[47]` | IGNORE_PPD0_PRESERVE_QOS |
    | `[48]` | IGNORE_PPD2_PRESERVE_QOS |
    | `[49]` | IGNORE_PPD3_PRESERVE_QOS |
    | `[50]` | IPHDR_ERROR_L3_LOOKUP_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180600` | `0x000401802080300e` |

---

## DOS_CONTROL_3r

- **Address:** `0x01180601`  ·  **Size:** 8 bytes
- **Function:** DOS (Denial of Service) Attack Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | BIG_ICMPV6_PKT_SIZE |
    | `[31:16]` | BIG_ICMP_PKT_SIZE |
    | `[39:32]` | MIN_TCPHDR_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180601` | `0x0000001402000200` |

---

## ING_CONFIG_2r

- **Address:** `0x01180602`  ·  **Size:** 4 bytes
- **Function:** Ingress Config Register 2.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | USE_VLAN_ING_PORT_BITMAP |
    | `[1]` | FCOE_IFP_KEY_MODE |
    | `[2]` | PROTOCOL_PKT_INDEX_PRECEDENCE_MODE |
    | `[3]` | WESP_DRAFT_11 |
    | `[4]` | ECMP_HASH_16BITS |
    | `[5]` | TRILL_TRANSIT_MTU_CHECK_ENHANCED |
    | `[6]` | L2_IS_IS_PARSE_MODE |
    | `[7]` | DISABLE_INVALID_RBRIDGE_NICKNAMES |
    | `[8]` | TRILL_ALL_ESADI_PARSE_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180602` | `0x000001ff` |

---

## VLAN_CTRLr

- **Address:** `0x01180603`  ·  **Size:** 4 bytes
- **Function:** VLAN Control Register #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | LEARN_VID |
    | `[12]` | USE_LEARN_VID |
    | `[28:13]` | INNER_TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180603` | `0x10200000` |

---

## FLEXIBLE_IPV6_EXT_HDRr

- **Address:** `0x0118060c`  ·  **Size:** 4 bytes
- **Function:** Programmable IPv6 extension header value.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PROTOCOL_ID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0118060c` | `0x00000000` |

---

## MC_CONTROL_1r

- **Address:** `0x01180610`  ·  **Size:** 4 bytes
- **Function:** Multicast Control Register1 for HiGig2 pkts

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | HIGIG2_BC_BASE_OFFSET |
    | `[31:16]` | HIGIG2_BC_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180610` | `0x10000000` |

---

## CFG_RAM_DBGCTRLr

- **Address:** `0x01180d00`  ·  **Size:** 4 bytes
- **Function:** CFG_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SYSCFG_TM |
    | `[5]` | SYSCFG_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d00` | `0x00000000` |

---

## PORT_TABLE_ECC_CONTROLr

- **Address:** `0x01180d01`  ·  **Size:** 4 bytes
- **Function:** PORT_TABLE_ECC_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d01` | `0x00000001` |

---

## PORT_TABLE_ECC_STATUS_INTRr

- **Address:** `0x01180d02`  ·  **Size:** 4 bytes
- **Function:** PORT_TABLE_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d02` | `0x00000000` |

---

## PORT_TABLE_ECC_STATUS_NACKr

- **Address:** `0x01180d03`  ·  **Size:** 4 bytes
- **Function:** PORT_TABLE_ECC_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d03` | `0x00000000` |

---

## SYSTEM_CONFIG_PARITY_CONTROLr

- **Address:** `0x01180d04`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d04` | `0x00000001` |

---

## SYSTEM_CONFIG_PARITY_STATUS_INTRr

- **Address:** `0x01180d05`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d05` | `0x00000000` |

---

## SYSTEM_CONFIG_PARITY_STATUS_NACKr

- **Address:** `0x01180d06`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d06` | `0x00000000` |

---

## SYSTEM_CONFIG_MODVIEW_PARITY_CONTROLr

- **Address:** `0x01180d07`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_MODVIEW_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d07` | `0x00000001` |

---

## SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_INTRr

- **Address:** `0x01180d08`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d08` | `0x00000000` |

---

## SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_NACKr

- **Address:** `0x01180d09`  ·  **Size:** 4 bytes
- **Function:** SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d09` | `0x00000000` |

---

## SOURCE_TRUNK_MAP_MODVIEW_PARITY_CONTROLr

- **Address:** `0x01180d0a`  ·  **Size:** 4 bytes
- **Function:** SOURCE_TRUNK_MAP_MODVIEW_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d0a` | `0x00000001` |

---

## SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_INTRr

- **Address:** `0x01180d0b`  ·  **Size:** 4 bytes
- **Function:** SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d0b` | `0x00000000` |

---

## SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_NACKr

- **Address:** `0x01180d0c`  ·  **Size:** 4 bytes
- **Function:** SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x01180d0c` | `0x00000000` |

---

## ING_MODMAP_CTRLr

- **Address:** `0x02100600`  ·  **Size:** 4 bytes
- **Function:** Ingress Module Remapping Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MODULEID_OFFSET |
    | `[8]` | ING_MAP_EN |
    | `[9]` | ING_MOD_MAP_ID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02100600` | `0x00000000` |
    | xe0 | `0x02101600` | `0x00000000` |
    | xe1 | `0x02102600` | `0x00000000` |
    | xe2 | `0x02103600` | `0x00000000` |
    | xe3 | `0x02104600` | `0x00000000` |
    | xe4 | `0x02105600` | `0x00000000` |
    | xe5 | `0x02106600` | `0x00000000` |
    | xe6 | `0x02107600` | `0x00000000` |
    | xe7 | `0x02108600` | `0x00000000` |
    | xe8 | `0x02109600` | `0x00000000` |
    | xe9 | `0x0210a600` | `0x00000000` |
    | xe10 | `0x0210b600` | `0x00000000` |
    | xe11 | `0x0210c600` | `0x00000000` |
    | xe12 | `0x0210d600` | `0x00000000` |
    | xe13 | `0x0210e600` | `0x00000000` |
    | xe14 | `0x0210f600` | `0x00000000` |
    | xe15 | `0x02110600` | `0x00000000` |
    | xe16 | `0x02111600` | `0x00000000` |
    | xe17 | `0x02112600` | `0x00000000` |
    | xe18 | `0x02113600` | `0x00000000` |
    | xe19 | `0x02114600` | `0x00000000` |
    | xe20 | `0x02115600` | `0x00000000` |
    | xe21 | `0x02116600` | `0x00000000` |
    | xe22 | `0x02117600` | `0x00000000` |
    | xe23 | `0x02118600` | `0x00000000` |
    | xe24 | `0x02119600` | `0x00000000` |
    | xe25 | `0x0211a600` | `0x00000000` |
    | xe26 | `0x0211b600` | `0x00000000` |
    | xe27 | `0x0211c600` | `0x00000000` |
    | xe28 | `0x0211d600` | `0x00000000` |
    | xe29 | `0x0211e600` | `0x00000000` |
    | xe30 | `0x0211f600` | `0x00000000` |
    | xe31 | `0x02120600` | `0x00000000` |
    | xe32 | `0x02121600` | `0x00000000` |
    | xe33 | `0x02122600` | `0x00000000` |
    | xe34 | `0x02123600` | `0x00000000` |
    | xe35 | `0x02124600` | `0x00000000` |
    | xe36 | `0x02125600` | `0x00000000` |
    | xe37 | `0x02126600` | `0x00000000` |
    | xe38 | `0x02127600` | `0x00000000` |
    | xe39 | `0x02128600` | `0x00000000` |
    | xe40 | `0x02129600` | `0x00000000` |
    | xe41 | `0x0212a600` | `0x00000000` |
    | xe42 | `0x0212b600` | `0x00000000` |
    | xe43 | `0x0212c600` | `0x00000000` |
    | xe44 | `0x0212d600` | `0x00000000` |
    | xe45 | `0x0212e600` | `0x00000000` |
    | xe46 | `0x0212f600` | `0x00000000` |
    | xe47 | `0x02130600` | `0x00000000` |
    | xe48 | `0x02131600` | `0x00000000` |
    | xe49 | `0x02132600` | `0x00000000` |
    | xe50 | `0x02133600` | `0x00000000` |
    | xe51 | `0x02134600` | `0x00000000` |
    | lb0 | `0x02141600` | `0x00000000` |

---

## IHG_LOOKUPr

- **Address:** `0x02100601`  ·  **Size:** 4 bytes
- **Function:** Higig Lookup Register to hold virtual port parameters

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | REMOVE_MH_SRC_PORT |
    | `[1]` | HG_LOOKUP_ENABLE |
    | `[2]` | USE_MH_VID |
    | `[3]` | USE_MH_PKT_PRI |
    | `[4]` | HYBRID_MODE_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02100601` | `0x00000000` |
    | xe0 | `0x02101601` | `0x00000000` |
    | xe1 | `0x02102601` | `0x00000000` |
    | xe2 | `0x02103601` | `0x00000000` |
    | xe3 | `0x02104601` | `0x00000000` |
    | xe4 | `0x02105601` | `0x00000000` |
    | xe5 | `0x02106601` | `0x00000000` |
    | xe6 | `0x02107601` | `0x00000000` |
    | xe7 | `0x02108601` | `0x00000000` |
    | xe8 | `0x02109601` | `0x00000000` |
    | xe9 | `0x0210a601` | `0x00000000` |
    | xe10 | `0x0210b601` | `0x00000000` |
    | xe11 | `0x0210c601` | `0x00000000` |
    | xe12 | `0x0210d601` | `0x00000000` |
    | xe13 | `0x0210e601` | `0x00000000` |
    | xe14 | `0x0210f601` | `0x00000000` |
    | xe15 | `0x02110601` | `0x00000000` |
    | xe16 | `0x02111601` | `0x00000000` |
    | xe17 | `0x02112601` | `0x00000000` |
    | xe18 | `0x02113601` | `0x00000000` |
    | xe19 | `0x02114601` | `0x00000000` |
    | xe20 | `0x02115601` | `0x00000000` |
    | xe21 | `0x02116601` | `0x00000000` |
    | xe22 | `0x02117601` | `0x00000000` |
    | xe23 | `0x02118601` | `0x00000000` |
    | xe24 | `0x02119601` | `0x00000000` |
    | xe25 | `0x0211a601` | `0x00000000` |
    | xe26 | `0x0211b601` | `0x00000000` |
    | xe27 | `0x0211c601` | `0x00000000` |
    | xe28 | `0x0211d601` | `0x00000000` |
    | xe29 | `0x0211e601` | `0x00000000` |
    | xe30 | `0x0211f601` | `0x00000000` |
    | xe31 | `0x02120601` | `0x00000000` |
    | xe32 | `0x02121601` | `0x00000000` |
    | xe33 | `0x02122601` | `0x00000000` |
    | xe34 | `0x02123601` | `0x00000000` |
    | xe35 | `0x02124601` | `0x00000000` |
    | xe36 | `0x02125601` | `0x00000000` |
    | xe37 | `0x02126601` | `0x00000000` |
    | xe38 | `0x02127601` | `0x00000000` |
    | xe39 | `0x02128601` | `0x00000000` |
    | xe40 | `0x02129601` | `0x00000000` |
    | xe41 | `0x0212a601` | `0x00000000` |
    | xe42 | `0x0212b601` | `0x00000000` |
    | xe43 | `0x0212c601` | `0x00000000` |
    | xe44 | `0x0212d601` | `0x00000000` |
    | xe45 | `0x0212e601` | `0x00000000` |
    | xe46 | `0x0212f601` | `0x00000000` |
    | xe47 | `0x02130601` | `0x00000000` |
    | xe48 | `0x02131601` | `0x00000000` |
    | xe49 | `0x02132601` | `0x00000000` |
    | xe50 | `0x02133601` | `0x00000000` |
    | xe51 | `0x02134601` | `0x00000000` |
    | lb0 | `0x02141601` | `0x00000000` |

---

## HG_LOOKUP_DESTINATIONr

- **Address:** `0x02100608`  ·  **Size:** 4 bytes
- **Function:** Destination to match to enable Proxy HG Lookup

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | DST_PORT |
    | `[14:7]` | DST_MODID |
    | `[15]` | DST_PORT_MASK |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x02100608` | `0x00000000` |
    | xe0 | `0x02101608` | `0x00000000` |
    | xe1 | `0x02102608` | `0x00000000` |
    | xe2 | `0x02103608` | `0x00000000` |
    | xe3 | `0x02104608` | `0x00000000` |
    | xe4 | `0x02105608` | `0x00000000` |
    | xe5 | `0x02106608` | `0x00000000` |
    | xe6 | `0x02107608` | `0x00000000` |
    | xe7 | `0x02108608` | `0x00000000` |
    | xe8 | `0x02109608` | `0x00000000` |
    | xe9 | `0x0210a608` | `0x00000000` |
    | xe10 | `0x0210b608` | `0x00000000` |
    | xe11 | `0x0210c608` | `0x00000000` |
    | xe12 | `0x0210d608` | `0x00000000` |
    | xe13 | `0x0210e608` | `0x00000000` |
    | xe14 | `0x0210f608` | `0x00000000` |
    | xe15 | `0x02110608` | `0x00000000` |
    | xe16 | `0x02111608` | `0x00000000` |
    | xe17 | `0x02112608` | `0x00000000` |
    | xe18 | `0x02113608` | `0x00000000` |
    | xe19 | `0x02114608` | `0x00000000` |
    | xe20 | `0x02115608` | `0x00000000` |
    | xe21 | `0x02116608` | `0x00000000` |
    | xe22 | `0x02117608` | `0x00000000` |
    | xe23 | `0x02118608` | `0x00000000` |
    | xe24 | `0x02119608` | `0x00000000` |
    | xe25 | `0x0211a608` | `0x00000000` |
    | xe26 | `0x0211b608` | `0x00000000` |
    | xe27 | `0x0211c608` | `0x00000000` |
    | xe28 | `0x0211d608` | `0x00000000` |
    | xe29 | `0x0211e608` | `0x00000000` |
    | xe30 | `0x0211f608` | `0x00000000` |
    | xe31 | `0x02120608` | `0x00000000` |
    | xe32 | `0x02121608` | `0x00000000` |
    | xe33 | `0x02122608` | `0x00000000` |
    | xe34 | `0x02123608` | `0x00000000` |
    | xe35 | `0x02124608` | `0x00000000` |
    | xe36 | `0x02125608` | `0x00000000` |
    | xe37 | `0x02126608` | `0x00000000` |
    | xe38 | `0x02127608` | `0x00000000` |
    | xe39 | `0x02128608` | `0x00000000` |
    | xe40 | `0x02129608` | `0x00000000` |
    | xe41 | `0x0212a608` | `0x00000000` |
    | xe42 | `0x0212b608` | `0x00000000` |
    | xe43 | `0x0212c608` | `0x00000000` |
    | xe44 | `0x0212d608` | `0x00000000` |
    | xe45 | `0x0212e608` | `0x00000000` |
    | xe46 | `0x0212f608` | `0x00000000` |
    | xe47 | `0x02130608` | `0x00000000` |
    | xe48 | `0x02131608` | `0x00000000` |
    | xe49 | `0x02132608` | `0x00000000` |
    | xe50 | `0x02133608` | `0x00000000` |
    | xe51 | `0x02134608` | `0x00000000` |
    | lb0 | `0x02141608` | `0x00000000` |

---

## E2E_HOL_RX_DA_MSr

- **Address:** `0x02180600`  ·  **Size:** 4 bytes
- **Function:** End-to-End HOL MSB DA Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180600` | `0x00000000` |

---

## E2E_HOL_RX_DA_LSr

- **Address:** `0x02180601`  ·  **Size:** 4 bytes
- **Function:** End-to-End HOL LSB DA Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180601` | `0x00000000` |

---

## E2E_HOL_RX_LENGTH_TYPEr

- **Address:** `0x02180602`  ·  **Size:** 4 bytes
- **Function:** End-to-End HOL Length/Type Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | LENGTH_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180602` | `0x00000000` |

---

## E2E_HOL_RX_OPCODEr

- **Address:** `0x02180603`  ·  **Size:** 4 bytes
- **Function:** End-to-End HOL Opcode Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | OPCODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180603` | `0x00000000` |

---

## E2E_IBP_RX_DA_MSr

- **Address:** `0x02180604`  ·  **Size:** 4 bytes
- **Function:** End-to-End IBP MSB DA Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180604` | `0x00000000` |

---

## E2E_IBP_RX_DA_LSr

- **Address:** `0x02180605`  ·  **Size:** 4 bytes
- **Function:** End-to-End IBP LSB DA Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180605` | `0x00000000` |

---

## E2E_IBP_RX_LENGTH_TYPEr

- **Address:** `0x02180606`  ·  **Size:** 4 bytes
- **Function:** End-to-End IBP Length/Type Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | LENGTH_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180606` | `0x00000000` |

---

## E2E_IBP_RX_OPCODEr

- **Address:** `0x02180607`  ·  **Size:** 4 bytes
- **Function:** End-to-End IBP Opcode Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | OPCODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180607` | `0x00000000` |

---

## ING_SYS_RSVD_VIDr

- **Address:** `0x02180609`  ·  **Size:** 4 bytes
- **Function:** VID in HG header to indicate real VID is inside packet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | VID |
    | `[12]` | VALID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180609` | `0x00000000` |

---

## RTAG7_HASH_CONTROLr

- **Address:** `0x0218062c`  ·  **Size:** 8 bytes
- **Function:** Rtag7 hashing control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | RESERVED_0_A |
    | `[2]` | DISABLE_FCOE_HASH_A |
    | `[3]` | DISABLE_HASH_IPV4_A |
    | `[4]` | DISABLE_HASH_IPV6_A |
    | `[5]` | DISABLE_HASH_MPLS_A |
    | `[6]` | DISABLE_HASH_MIM_A |
    | `[7]` | DISABLE_HASH_INNER_IPV4_OVER_IPV4_A |
    | `[8]` | DISABLE_HASH_INNER_IPV6_OVER_IPV4_A |
    | `[9]` | DISABLE_HASH_INNER_IPV4_OVER_GRE_IPV4_A |
    | `[10]` | DISABLE_HASH_INNER_IPV6_OVER_GRE_IPV4_A |
    | `[11]` | DISABLE_HASH_INNER_IPV4_OVER_GRE_IPV6_A |
    | `[12]` | DISABLE_HASH_INNER_IPV6_OVER_GRE_IPV6_A |
    | `[13]` | DISABLE_HASH_INNER_IPV6_OVER_IPV6_A |
    | `[14]` | DISABLE_HASH_INNER_IPV4_OVER_IPV6_A |
    | `[15]` | IPV6_COLLAPSED_ADDR_SELECT_A |
    | `[17:16]` | RESERVED_0_B |
    | `[18]` | DISABLE_FCOE_HASH_B |
    | `[19]` | DISABLE_HASH_IPV4_B |
    | `[20]` | DISABLE_HASH_IPV6_B |
    | `[21]` | DISABLE_HASH_MPLS_B |
    | `[22]` | DISABLE_HASH_MIM_B |
    | `[23]` | DISABLE_HASH_INNER_IPV4_OVER_IPV4_B |
    | `[24]` | DISABLE_HASH_INNER_IPV6_OVER_IPV4_B |
    | `[25]` | DISABLE_HASH_INNER_IPV4_OVER_GRE_IPV4_B |
    | `[26]` | DISABLE_HASH_INNER_IPV6_OVER_GRE_IPV4_B |
    | `[27]` | DISABLE_HASH_INNER_IPV4_OVER_GRE_IPV6_B |
    | `[28]` | DISABLE_HASH_INNER_IPV6_OVER_GRE_IPV6_B |
    | `[29]` | DISABLE_HASH_INNER_IPV6_OVER_IPV6_B |
    | `[30]` | DISABLE_HASH_INNER_IPV4_OVER_IPV6_B |
    | `[31]` | IPV6_COLLAPSED_ADDR_SELECT_B |
    | `[33:32]` | TRILL_TUNNEL_HASH_SELECT_A |
    | `[34]` | TRILL_PAYLOAD_HASH_SELECT_A |
    | `[36:35]` | TRILL_TUNNEL_HASH_SELECT_B |
    | `[37]` | TRILL_PAYLOAD_HASH_SELECT_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218062c` | `0x0000000000000000` |

---

## GLOBAL_MPLS_RANGE_1_LOWERr

- **Address:** `0x02180632`  ·  **Size:** 4 bytes
- **Function:** MPLS label first global range lower bound. (Inclusive)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | LABEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180632` | `0x00000000` |

---

## GLOBAL_MPLS_RANGE_1_UPPERr

- **Address:** `0x02180633`  ·  **Size:** 4 bytes
- **Function:** MPLS label first global range upper bound. (Inclusive)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | LABEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180633` | `0x000fffff` |

---

## GLOBAL_MPLS_RANGE_2_LOWERr

- **Address:** `0x02180634`  ·  **Size:** 4 bytes
- **Function:** MPLS label second global range lower bound. (Inclusive)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | LABEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180634` | `0x00000000` |

---

## GLOBAL_MPLS_RANGE_2_UPPERr

- **Address:** `0x02180635`  ·  **Size:** 4 bytes
- **Function:** MPLS label second global range upper bound. (Inclusive)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | LABEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180635` | `0x000fffff` |

---

## REMOTE_CPU_DA_MSr

- **Address:** `0x02180638`  ·  **Size:** 4 bytes
- **Function:** Remote CPU pkt LSB DA Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180638` | `0x00000000` |

---

## REMOTE_CPU_DA_LSr

- **Address:** `0x02180639`  ·  **Size:** 4 bytes
- **Function:** Remote CPU pkt LSB DA Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180639` | `0x00000000` |

---

## REMOTE_CPU_LENGTH_TYPEr

- **Address:** `0x0218063a`  ·  **Size:** 4 bytes
- **Function:** Remote cpu pkt  Length/Type Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | LENGTH_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063a` | `0x00000000` |

---

## MIM_ETHERTYPEr

- **Address:** `0x0218063b`  ·  **Size:** 4 bytes
- **Function:** MAC-in-MAC Ethertype Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063b` | `0x000088e7` |

---

## ING_OUTER_TPIDr

- **Address:** `0x0218063c`  ·  **Size:** 4 bytes
- **Function:** Ingress Outer TPID register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

---

## ING_OUTER_TPID_0r

- **Address:** `0x0218063c`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063c` | `0x00008100` |

---

## ING_OUTER_TPID_1r

- **Address:** `0x0218063d`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063d` | `0x00009100` |

---

## ING_OUTER_TPID_2r

- **Address:** `0x0218063e`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063e` | `0x000088a8` |

---

## ING_OUTER_TPID_3r

- **Address:** `0x0218063f`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0218063f` | `0x00000000` |

---

## TS_CONTROLr

- **Address:** `0x02180640`  ·  **Size:** 4 bytes
- **Function:** Holds TS control info

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[31:16]` | TS_MSG_BITMAP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180640` | `0x000d88f7` |

---

## TS_CONTROL_1r

- **Address:** `0x02180641`  ·  **Size:** 4 bytes
- **Function:** Vlaues for TS frame detection

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180641` | `0xc200000e` |

---

## TS_CONTROL_2r

- **Address:** `0x02180642`  ·  **Size:** 4 bytes
- **Function:** Vlaues for TS frame detection

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MAC_DA_UPPER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180642` | `0x00000180` |

---

## MMRP_CONTROL_1r

- **Address:** `0x02180643`  ·  **Size:** 4 bytes
- **Function:** Values for MMRP frame detection

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180643` | `0xc2000020` |

---

## MMRP_CONTROL_2r

- **Address:** `0x02180644`  ·  **Size:** 4 bytes
- **Function:** Values for MMRP frame detection

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[31:16]` | MAC_DA_UPPER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180644` | `0x018088f6` |

---

## SRP_CONTROL_1r

- **Address:** `0x02180645`  ·  **Size:** 4 bytes
- **Function:** Values for SRP frame detection

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180645` | `0x00000000` |

---

## SRP_CONTROL_2r

- **Address:** `0x02180646`  ·  **Size:** 4 bytes
- **Function:** Values for SRP frame detection

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[31:16]` | MAC_DA_UPPER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180646` | `0x00000001` |

---

## ING_BYPASS_CTRLr

- **Address:** `0x02180647`  ·  **Size:** 4 bytes
- **Function:** bypass enable to each ip stage

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | IFP_BYPASS_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180647` | `0x00000000` |

---

## NIV_ETHERTYPEr

- **Address:** `0x02180650`  ·  **Size:** 4 bytes
- **Function:** NIV Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |
    | `[18:17]` | VER_CHECK_CTRL |
    | `[20:19]` | VNTAG_VERSION |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180650` | `0x00000000` |

---

## ING_FCOE_ETHERTYPEr

- **Address:** `0x02180652`  ·  **Size:** 4 bytes
- **Function:** FCoE Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180652` | `0x00000000` |

---

## ING_WESP_PROTO_CONTROLr

- **Address:** `0x02180653`  ·  **Size:** 4 bytes
- **Function:** Ingress WESP Protocol Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | WESP_PROTO_NUMBER |
    | `[8]` | WESP_PROTO_NUMBER_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180653` | `0x00000000` |

---

## ING_QCN_CNTAG_ETHERTYPEr

- **Address:** `0x02180660`  ·  **Size:** 4 bytes
- **Function:** QCN CNTAG Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180660` | `0x00000000` |

---

## ING_QCN_CNM_ETHERTYPEr

- **Address:** `0x02180661`  ·  **Size:** 4 bytes
- **Function:** QCN CNM Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180661` | `0x00000000` |

---

## ING_HBFC_CNTAG_ETHERTYPEr

- **Address:** `0x02180662`  ·  **Size:** 4 bytes
- **Function:** HBFC CNTAG Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180662` | `0x00000000` |

---

## ING_HBFC_CNM_ETHERTYPEr

- **Address:** `0x02180663`  ·  **Size:** 4 bytes
- **Function:** HBFC CNM Ethertype Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | ETHERTYPE |
    | `[16]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180663` | `0x00000000` |

---

## ING_VOQFC_MACDA_MSr

- **Address:** `0x02180670`  ·  **Size:** 4 bytes
- **Function:** End-to-End VOQFC MSB MACDA Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DA |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180670` | `0x00000000` |

---

## ING_VOQFC_MACDA_LSr

- **Address:** `0x02180671`  ·  **Size:** 4 bytes
- **Function:** End-to-End VOQFC LSB MACDA Register.

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180671` | `0x00000000` |

---

## ING_VOQFC_IDr

- **Address:** `0x02180672`  ·  **Size:** 4 bytes
- **Function:** End-to-End VOQFC id Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | OPCODE |
    | `[31:16]` | LENGTH_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180672` | `0x00000000` |

---

## MC_CONTROL_2r

- **Address:** `0x02180681`  ·  **Size:** 4 bytes
- **Function:** Multicast Control Register2 for HiGig2 pkts

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | HIGIG2_L2MC_BASE_OFFSET |
    | `[31:16]` | HIGIG2_L2MC_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180681` | `0x10001000` |

---

## MC_CONTROL_3r

- **Address:** `0x02180682`  ·  **Size:** 4 bytes
- **Function:** Multicast Control Register3 for HiGig2 pkts

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | HIGIG2_IPMC_BASE_OFFSET |
    | `[31:16]` | HIGIG2_IPMC_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180682` | `0x10002000` |

---

## L3_TUNNEL_CAM_DBGCTRLr

- **Address:** `0x02180d00`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | BIST_EN |
    | `[7:4]` | DEBUG_EN |
    | `[21:8]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d00` | `0x00000000` |

---

## L3_TUNNEL_CAM_BIST_STATUSr

- **Address:** `0x02180d01`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d01` | `0x00000000` |

---

## L3_TUNNEL_CAM_BIST_CONFIGr

- **Address:** `0x02180d02`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d02` | `0x00000000` |

---

## L3_TUNNEL_CAM_BIST_DBG_DATAr

- **Address:** `0x02180d03`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## UDF_CAM_DBGCTRLr

- **Address:** `0x02180d04`  ·  **Size:** 4 bytes
- **Function:** UDF_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN |
    | `[1]` | DEBUG_EN |
    | `[12:2]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d04` | `0x00000000` |

---

## UDF_CAM_BIST_STATUSr

- **Address:** `0x02180d05`  ·  **Size:** 4 bytes
- **Function:** UDF_CAM_BIST_STATUS, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d05` | `0x00000000` |

---

## UDF_CAM_BIST_CONFIGr

- **Address:** `0x02180d06`  ·  **Size:** 4 bytes
- **Function:** UDF_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d06` | `0x00000000` |

---

## UDF_CAM_BIST_DBG_DATAr

- **Address:** `0x02180d07`  ·  **Size:** 4 bytes
- **Function:** UDF_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## PARS_RAM_DBGCTRLr

- **Address:** `0x02180d08`  ·  **Size:** 8 bytes
- **Function:** PARS_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SRCTRUNKMAP_TM |
    | `[9:5]` | L3TUNNEL_TM |
    | `[14:10]` | VLAN_RANGE_TM |
    | `[16:15]` | PKT_BUF_TM |
    | `[18:17]` | LPORT_TM |
    | `[22:19]` | RESERVED_PARS_RAM_CONTROL |
    | `[27:23]` | FP_UDF_RAM_TM |
    | `[46:42]` | ING_MOD_MAP_RAM_TM |
    | `[47]` | FP_UDF_RAM_PM |
    | `[48]` | ING_MOD_MAP_RAM_PM |
    | `[49]` | L3TUNNEL_PM |
    | `[50]` | SRCTRUNKMAP_PM |
    | `[51]` | VLAN_RANGE_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d08` | `0x0000000000000000` |

---

## CPU_TS_PARITY_CONTROLr

- **Address:** `0x02180d09`  ·  **Size:** 4 bytes
- **Function:** CPU_TS_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d09` | `0x00000001` |

---

## CPU_TS_PARITY_STATUS_INTRr

- **Address:** `0x02180d0a`  ·  **Size:** 4 bytes
- **Function:** CPU_TS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0a` | `0x00000000` |

---

## CPU_TS_PARITY_STATUS_NACKr

- **Address:** `0x02180d0b`  ·  **Size:** 4 bytes
- **Function:** CPU_TS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0b` | `0x00000000` |

---

## VLAN_RANGE_PARITY_CONTROLr

- **Address:** `0x02180d0c`  ·  **Size:** 4 bytes
- **Function:** VLAN_RANGE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0c` | `0x00000001` |

---

## VLAN_RANGE_PARITY_STATUS_INTRr

- **Address:** `0x02180d0d`  ·  **Size:** 4 bytes
- **Function:** VLAN_RANGE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0d` | `0x00000000` |

---

## VLAN_RANGE_PARITY_STATUS_NACKr

- **Address:** `0x02180d0e`  ·  **Size:** 4 bytes
- **Function:** VLAN_RANGE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0e` | `0x00000000` |

---

## MOD_MAP_PARITY_CONTROLr

- **Address:** `0x02180d0f`  ·  **Size:** 4 bytes
- **Function:** MOD_MAP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d0f` | `0x00000001` |

---

## MOD_MAP_PARITY_STATUS_INTRr

- **Address:** `0x02180d10`  ·  **Size:** 4 bytes
- **Function:** MOD_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d10` | `0x00000000` |

---

## MOD_MAP_PARITY_STATUS_NACKr

- **Address:** `0x02180d11`  ·  **Size:** 4 bytes
- **Function:** MOD_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d11` | `0x00000000` |

---

## FP_UDF_PARITY_CONTROLr

- **Address:** `0x02180d12`  ·  **Size:** 4 bytes
- **Function:** FP_UDF_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d12` | `0x00000001` |

---

## FP_UDF_PARITY_STATUS_INTRr

- **Address:** `0x02180d13`  ·  **Size:** 4 bytes
- **Function:** FP_UDF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d13` | `0x00000000` |

---

## FP_UDF_PARITY_STATUS_NACKr

- **Address:** `0x02180d14`  ·  **Size:** 4 bytes
- **Function:** FP_UDF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d14` | `0x00000000` |

---

## L3_TUNNEL_PARITY_CONTROLr

- **Address:** `0x02180d15`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d15` | `0x00000001` |

---

## L3_TUNNEL_PARITY_STATUS_INTRr

- **Address:** `0x02180d16`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d16` | `0x00000000` |

---

## L3_TUNNEL_PARITY_STATUS_NACKr

- **Address:** `0x02180d17`  ·  **Size:** 4 bytes
- **Function:** L3_TUNNEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d17` | `0x00000000` |

---

## SRC_TRUNK_ECC_CONTROLr

- **Address:** `0x02180d18`  ·  **Size:** 4 bytes
- **Function:** SRC_TRUNK_ECC_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d18` | `0x00000001` |

---

## SRC_TRUNK_ECC_STATUS_INTRr

- **Address:** `0x02180d19`  ·  **Size:** 4 bytes
- **Function:** SRC_TRUNK_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[15:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d19` | `0x00000000` |

---

## SRC_TRUNK_ECC_STATUS_NACKr

- **Address:** `0x02180d1a`  ·  **Size:** 4 bytes
- **Function:** SRC_TRUNK_ECC_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[15:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d1a` | `0x00000000` |

---

## LPORT_ECC_CONTROLr

- **Address:** `0x02180d1b`  ·  **Size:** 4 bytes
- **Function:** LPORT_ECC_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d1b` | `0x00000001` |

---

## LPORT_ECC_STATUS_INTRr

- **Address:** `0x02180d1c`  ·  **Size:** 4 bytes
- **Function:** LPORT_ECC_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d1c` | `0x00000000` |

---

## LPORT_ECC_STATUS_NACKr

- **Address:** `0x02180d1d`  ·  **Size:** 4 bytes
- **Function:** LPORT_ECC_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[9:3]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x02180d1d` | `0x00000000` |

---

## IPV6_MIN_FRAG_SIZEr

- **Address:** `0x03180600`  ·  **Size:** 4 bytes
- **Function:** Programmable Minimum IPv6 Fragment Size for DOS Attack Check.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | PKT_LENGTH |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x03180600` | `0x00000500` |

---

## DOS_CONTROLr

- **Address:** `0x03180601`  ·  **Size:** 4 bytes
- **Function:** DOS (Denial of Service) Attack Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DROP_IF_SIP_EQUALS_DIP |
    | `[1]` | MACSA_EQUALS_MACDA_DROP |
    | `[2]` | TCP_FLAGS_SYN_FRAG_ENABLE |
    | `[3]` | TCP_FLAGS_CTRL0_SEQ0_ENABLE |
    | `[4]` | IPV4_FIRST_FRAG_CHECK_ENABLE |
    | `[4]` | IP_FIRST_FRAG_CHECK_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x03180601` | `0x00000000` |

---

## DOS_CONTROL_2r

- **Address:** `0x03180602`  ·  **Size:** 4 bytes
- **Function:** DOS (Denial of Service) Attack Control Register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | TCP_FLAGS_FIN_URG_PSH_SEQ0_ENABLE |
    | `[1]` | TCP_FLAGS_SYN_FIN_ENABLE |
    | `[2]` | TCP_SPORT_EQ_DPORT_ENABLE |
    | `[3]` | UDP_SPORT_EQ_DPORT_ENABLE |
    | `[4]` | TCP_HDR_PARTIAL_ENABLE |
    | `[5]` | TCP_HDR_OFFSET_EQ1_ENABLE |
    | `[6]` | ICMP_V6_PING_SIZE_ENABLE |
    | `[7]` | ICMP_V4_PING_SIZE_ENABLE |
    | `[8]` | ICMP_FRAG_PKTS_ENABLE |
    | `[9]` | IPV6_MIN_FRAG_SIZE_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x03180602` | `0x00000000` |

---

## ING_NIV_CONFIGr

- **Address:** `0x04180600`  ·  **Size:** 4 bytes
- **Function:** Inress NIV Config Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | VNTAG_DST_VIF |
    | `[14]` | VNTAG_L |
    | `[15]` | VNTAG_P |
    | `[16]` | VNTAG_R |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180600` | `0x00000000` |

---

## VLAN_XLATE_HASH_CONTROLr

- **Address:** `0x04180608`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_HASH_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | HASH_SELECT_A |
    | `[5:3]` | HASH_SELECT_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180608` | `0x0000000a` |

---

## VFP_SLICE_CONTROLr

- **Address:** `0x04180620`  ·  **Size:** 4 bytes
- **Function:** VFP_SLICE_CONTROL

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

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180620` | `0x000000ff` |

---

## VFP_KEY_CONTROLr

- **Address:** `0x04180621`  ·  **Size:** 4 bytes
- **Function:** VFP_KEY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SLICE_0_F2 |
    | `[4:3]` | SLICE_0_F3 |
    | `[7:5]` | SLICE_1_F2 |
    | `[9:8]` | SLICE_1_F3 |
    | `[12:10]` | SLICE_2_F2 |
    | `[14:13]` | SLICE_2_F3 |
    | `[17:15]` | SLICE_3_F2 |
    | `[19:18]` | SLICE_3_F3 |
    | `[20]` | SLICE_0_DOUBLE_WIDE_MODE |
    | `[21]` | SLICE_1_DOUBLE_WIDE_MODE |
    | `[22]` | SLICE_2_DOUBLE_WIDE_MODE |
    | `[23]` | SLICE_3_DOUBLE_WIDE_MODE |
    | `[24]` | SLICE1_0_PAIRING |
    | `[25]` | SLICE3_2_PAIRING |
    | `[26]` | SLICE_0_DOUBLE_WIDE_KEY_SELECT |
    | `[27]` | SLICE_1_DOUBLE_WIDE_KEY_SELECT |
    | `[28]` | SLICE_2_DOUBLE_WIDE_KEY_SELECT |
    | `[29]` | SLICE_3_DOUBLE_WIDE_KEY_SELECT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180621` | `0x00000003` |

---

## VFP_KEY_CONTROL_2r

- **Address:** `0x04180622`  ·  **Size:** 4 bytes
- **Function:** VFP_KEY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SLICE_0_IP_FIELD_SELECT |
    | `[1]` | SLICE_1_IP_FIELD_SELECT |
    | `[2]` | SLICE_2_IP_FIELD_SELECT |
    | `[3]` | SLICE_3_IP_FIELD_SELECT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180622` | `0x00000000` |

---

## VFP_SLICE_MAPr

- **Address:** `0x04180636`  ·  **Size:** 4 bytes
- **Function:** VFP_SLICE_MAP

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
    | ipipe0 | `0x04180636` | `0x0000e4e4` |

---

## MPLS_ENTRY_HASH_CONTROLr

- **Address:** `0x04180640`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_HASH_CONTROL, FeatureSpecific-MPLS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | HASH_SELECT_A |
    | `[5:3]` | HASH_SELECT_B |
    | `[6]` | INSERT_LEAST_FULL_HALF |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180640` | `0x0000004a` |

---

## IP1_INTR_STATUSr

- **Address:** `0x04180d00`  ·  **Size:** 4 bytes
- **Function:** IP1 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VXLT_PAR_ERR |
    | `[1]` | VFP_POLICY_PAR_ERR |
    | `[2]` | VLAN_PROT_PAR_ERR |
    | `[3]` | VLAN_SUBNET_PAR_ERR |
    | `[4]` | CPU_TS_POLICY_PAR_ERR |
    | `[5]` | VLAN_RANGE_PAR_ERR |
    | `[6]` | MOD_MAP_PAR_ERR |
    | `[7]` | FP_UDF_PAR_ERR |
    | `[8]` | L3_TUNNEL_PAR_ERR |
    | `[9]` | WLAN_SVP_PAR_ERR |
    | `[10]` | SRC_TRUNK_PAR_ERR |
    | `[11]` | LPORT_PAR_ERR |
    | `[12]` | MPLS_ENTRY_PAR_ERR |
    | `[13]` | PORT_TABLE_PAR_ERR |
    | `[14]` | SYS_CONFIG_PAR_ERR |
    | `[15]` | SYSTEM_CONFIG_MODVIEW_PAR_ERR |
    | `[16]` | SOURCE_TRUNK_MAP_MODVIEW_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d00` | `0x00000000` |

---

## IP1_INTR_ENABLEr

- **Address:** `0x04180d01`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP1_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VXLT_PAR_ERR |
    | `[1]` | VFP_POLICY_PAR_ERR |
    | `[2]` | VLAN_PROT_PAR_ERR |
    | `[3]` | VLAN_SUBNET_PAR_ERR |
    | `[4]` | CPU_TS_POLICY_PAR_ERR |
    | `[5]` | VLAN_RANGE_PAR_ERR |
    | `[6]` | MOD_MAP_PAR_ERR |
    | `[7]` | FP_UDF_PAR_ERR |
    | `[8]` | L3_TUNNEL_PAR_ERR |
    | `[9]` | WLAN_SVP_PAR_ERR |
    | `[10]` | SRC_TRUNK_PAR_ERR |
    | `[11]` | LPORT_PAR_ERR |
    | `[12]` | MPLS_ENTRY_PAR_ERR |
    | `[13]` | PORT_TABLE_PAR_ERR |
    | `[14]` | SYS_CONFIG_PAR_ERR |
    | `[15]` | SYSTEM_CONFIG_MODVIEW_PAR_ERR |
    | `[16]` | SOURCE_TRUNK_MAP_MODVIEW_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d01` | `0x0001fdff` |

---

## VLAN_SUBNET_CAM_DBGCTRLr

- **Address:** `0x04180d02`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN |
    | `[1]` | DEBUG_EN |
    | `[15:2]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d02` | `0x00000000` |

---

## VLAN_SUBNET_CAM_BIST_STATUSr

- **Address:** `0x04180d03`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d03` | `0x00000000` |

---

## VLAN_SUBNET_CAM_BIST_CONFIGr

- **Address:** `0x04180d04`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d04` | `0x00000000` |

---

## VLAN_SUBNET_CAM_BIST_DBG_DATAr

- **Address:** `0x04180d05`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## VLAN_SUBNET_DATA_DBGCTRLr

- **Address:** `0x04180d06`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_DATA_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | TM |
    | `[5]` | PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d06` | `0x00000000` |

---

## VLAN_PROTOCOL_DATA_DBGCTRLr

- **Address:** `0x04180d07`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROTOCOL_DATA_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | TM |
    | `[5]` | PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d07` | `0x00000000` |

---

## VLAN_XLATE_DATA_DBGCTRL_0r

- **Address:** `0x04180d08`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_DATA_CONTROL_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TM_0 |
    | `[19:10]` | TM_1 |
    | `[29:20]` | TM_2 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d08` | `0x00000000` |

---

## VLAN_XLATE_DATA_DBGCTRL_1r

- **Address:** `0x04180d09`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_DATA_CONTROL_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TM_3 |
    | `[19:10]` | TM_4 |
    | `[29:20]` | TM_5 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d09` | `0x00000000` |

---

## VLAN_XLATE_DATA_DBGCTRL_2r

- **Address:** `0x04180d0a`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_DATA_CONTROL_2, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TM_6 |
    | `[19:10]` | TM_7 |
    | `[24:20]` | ING_VLAN_TAG_ACTION_PROFILE_TM |
    | `[25]` | ING_VLAN_TAG_ACTION_PROFILE_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0a` | `0x00000000` |

---

## VLAN_XLATE_DATA_DBGCTRL_3r

- **Address:** `0x04180d0b`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_DATA_CONTROL_3, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PM_0 |
    | `[1]` | PM_1 |
    | `[2]` | PM_2 |
    | `[3]` | PM_3 |
    | `[4]` | PM_4 |
    | `[5]` | PM_5 |
    | `[6]` | PM_6 |
    | `[7]` | PM_7 |
    | `[8]` | DCM_0 |
    | `[9]` | DCM_1 |
    | `[10]` | DCM_2 |
    | `[11]` | DCM_3 |
    | `[12]` | DCM_4 |
    | `[13]` | DCM_5 |
    | `[14]` | DCM_6 |
    | `[15]` | DCM_7 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0b` | `0x00000000` |

---

## VLAN_XLATE_PARITY_CONTROLr

- **Address:** `0x04180d0c`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0c` | `0x00000001` |

---

## VLAN_XLATE_PARITY_STATUS_INTR_0r

- **Address:** `0x04180d0d`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_PARITY_STATUS_INTR_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0d` | `0x00000000` |

---

## VLAN_XLATE_PARITY_STATUS_INTR_1r

- **Address:** `0x04180d0e`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_PARITY_STATUS_INTR_1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0e` | `0x00000000` |

---

## VLAN_XLATE_PARITY_STATUS_NACK_0r

- **Address:** `0x04180d0f`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_PARITY_STATUS_NACK_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d0f` | `0x00000000` |

---

## VLAN_XLATE_PARITY_STATUS_NACK_1r

- **Address:** `0x04180d10`  ·  **Size:** 4 bytes
- **Function:** VLAN_XLATE_PARITY_STATUS_NACK_1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d10` | `0x00000000` |

---

## VFP_POLICY_PARITY_CONTROLr

- **Address:** `0x04180d11`  ·  **Size:** 4 bytes
- **Function:** VFP_POLICY_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d11` | `0x00000001` |

---

## VFP_POLICY_PARITY_STATUS_INTRr

- **Address:** `0x04180d12`  ·  **Size:** 4 bytes
- **Function:** VFP_POLICY_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d12` | `0x00000000` |

---

## VFP_POLICY_PARITY_STATUS_NACKr

- **Address:** `0x04180d13`  ·  **Size:** 4 bytes
- **Function:** VFP_POLICY_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d13` | `0x00000000` |

---

## VFP_CAM_BIST_STATUSr

- **Address:** `0x04180d14`  ·  **Size:** 4 bytes
- **Function:** VFP_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d14` | `0x00000000` |

---

## VFP_CAM_BIST_CONTROLr

- **Address:** `0x04180d15`  ·  **Size:** 4 bytes
- **Function:** VFP_CAM_BIST_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CAM_BIST_ENABLE_SLICE_0_UPPER |
    | `[1]` | CAM_BIST_ENABLE_SLICE_0_LOWER |
    | `[2]` | CAM_BIST_ENABLE_SLICE_1_UPPER |
    | `[3]` | CAM_BIST_ENABLE_SLICE_1_LOWER |
    | `[4]` | CAM_BIST_ENABLE_SLICE_2_UPPER |
    | `[5]` | CAM_BIST_ENABLE_SLICE_2_LOWER |
    | `[6]` | CAM_BIST_ENABLE_SLICE_3_UPPER |
    | `[7]` | CAM_BIST_ENABLE_SLICE_3_LOWER |
    | `[8]` | CAM_DEBUG_ENABLE_SLICE_0_UPPER |
    | `[9]` | CAM_DEBUG_ENABLE_SLICE_0_LOWER |
    | `[10]` | CAM_DEBUG_ENABLE_SLICE_1_UPPER |
    | `[11]` | CAM_DEBUG_ENABLE_SLICE_1_LOWER |
    | `[12]` | CAM_DEBUG_ENABLE_SLICE_2_UPPER |
    | `[13]` | CAM_DEBUG_ENABLE_SLICE_2_LOWER |
    | `[14]` | CAM_DEBUG_ENABLE_SLICE_3_UPPER |
    | `[15]` | CAM_DEBUG_ENABLE_SLICE_3_LOWER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d15` | `0x00000000` |

---

## VFP_CAM_CONTROL_SLICE_3_0r

- **Address:** `0x04180d16`  ·  **Size:** 4 bytes
- **Function:** VFP_CAM_CONTROL_SLICE_3_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d16` | `0x00000000` |

---

## VFP_CAM_BIST_DBG_DATAr

- **Address:** `0x04180d17`  ·  **Size:** 4 bytes
- **Function:** VFP_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## VFP_CAM_BIST_CONFIGr

- **Address:** `0x04180d18`  ·  **Size:** 4 bytes
- **Function:** VFP_CAM_DEBUG_SEND

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d18` | `0x00000000` |

---

## VFP_POLICY_TABLE_RAM_CONTROLr

- **Address:** `0x04180d19`  ·  **Size:** 4 bytes
- **Function:** VFP_POLICY_TABLE_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SLICE_0_TM |
    | `[9:5]` | SLICE_1_TM |
    | `[14:10]` | SLICE_2_TM |
    | `[19:15]` | SLICE_3_TM |
    | `[20]` | SLICE_0_PM |
    | `[21]` | SLICE_1_PM |
    | `[22]` | SLICE_2_PM |
    | `[23]` | SLICE_3_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d19` | `0x00000000` |

---

## VLAN_PROT_PARITY_CONTROLr

- **Address:** `0x04180d1a`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROT_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1a` | `0x00000001` |

---

## VLAN_PROT_PARITY_STATUS_INTRr

- **Address:** `0x04180d1b`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1b` | `0x00000000` |

---

## VLAN_PROT_PARITY_STATUS_NACKr

- **Address:** `0x04180d1c`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1c` | `0x00000000` |

---

## VLAN_SUBNET_PARITY_CONTROLr

- **Address:** `0x04180d1d`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1d` | `0x00000001` |

---

## VLAN_SUBNET_PARITY_STATUS_INTRr

- **Address:** `0x04180d1e`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1e` | `0x00000000` |

---

## VLAN_SUBNET_PARITY_STATUS_NACKr

- **Address:** `0x04180d1f`  ·  **Size:** 4 bytes
- **Function:** VLAN_SUBNET_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d1f` | `0x00000000` |

---

## MPLS_ENTRY_DBGCTRL_0r

- **Address:** `0x04180d20`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM0_TM |
    | `[19:10]` | RAM1_TM |
    | `[29:20]` | RAM2_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d20` | `0x00000000` |

---

## MPLS_ENTRY_DBGCTRL_1r

- **Address:** `0x04180d21`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM3_TM |
    | `[19:10]` | RAM4_TM |
    | `[29:20]` | RAM5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d21` | `0x00000000` |

---

## MPLS_ENTRY_DBGCTRL_2r

- **Address:** `0x04180d22`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM6_TM |
    | `[19:10]` | RAM7_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d22` | `0x00000000` |

---

## MPLS_ENTRY_DBGCTRL_3r

- **Address:** `0x04180d23`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RAM0_PM |
    | `[1]` | RAM1_PM |
    | `[2]` | RAM2_PM |
    | `[3]` | RAM3_PM |
    | `[4]` | RAM4_PM |
    | `[5]` | RAM5_PM |
    | `[6]` | RAM6_PM |
    | `[7]` | RAM7_PM |
    | `[8]` | RAM0_DCM |
    | `[9]` | RAM1_DCM |
    | `[10]` | RAM2_DCM |
    | `[11]` | RAM3_DCM |
    | `[12]` | RAM4_DCM |
    | `[13]` | RAM5_DCM |
    | `[14]` | RAM6_DCM |
    | `[15]` | RAM7_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d23` | `0x00000000` |

---

## MPLS_ENTRY_PARITY_CONTROLr

- **Address:** `0x04180d24`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d24` | `0x00000001` |

---

## MPLS_ENTRY_PARITY_STATUS_INTR_0r

- **Address:** `0x04180d25`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d25` | `0x00000000` |

---

## MPLS_ENTRY_PARITY_STATUS_INTR_1r

- **Address:** `0x04180d26`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d26` | `0x00000000` |

---

## MPLS_ENTRY_PARITY_STATUS_NACK_0r

- **Address:** `0x04180d27`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d27` | `0x00000000` |

---

## MPLS_ENTRY_PARITY_STATUS_NACK_1r

- **Address:** `0x04180d28`  ·  **Size:** 4 bytes
- **Function:** MPLS_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[14:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x04180d28` | `0x00000000` |

---

## ING_TRILL_ADJACENCYr

- **Address:** `0x05100631`  ·  **Size:** 8 bytes
- **Function:** Ingress TRILL Adjacency Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[59:48]` | VLAN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x05100631` | `0x0000000000000000` |
    | xe0 | `0x05101631` | `0x0000000000000000` |
    | xe1 | `0x05102631` | `0x0000000000000000` |
    | xe2 | `0x05103631` | `0x0000000000000000` |
    | xe3 | `0x05104631` | `0x0000000000000000` |
    | xe4 | `0x05105631` | `0x0000000000000000` |
    | xe5 | `0x05106631` | `0x0000000000000000` |
    | xe6 | `0x05107631` | `0x0000000000000000` |
    | xe7 | `0x05108631` | `0x0000000000000000` |
    | xe8 | `0x05109631` | `0x0000000000000000` |
    | xe9 | `0x0510a631` | `0x0000000000000000` |
    | xe10 | `0x0510b631` | `0x0000000000000000` |
    | xe11 | `0x0510c631` | `0x0000000000000000` |
    | xe12 | `0x0510d631` | `0x0000000000000000` |
    | xe13 | `0x0510e631` | `0x0000000000000000` |
    | xe14 | `0x0510f631` | `0x0000000000000000` |
    | xe15 | `0x05110631` | `0x0000000000000000` |
    | xe16 | `0x05111631` | `0x0000000000000000` |
    | xe17 | `0x05112631` | `0x0000000000000000` |
    | xe18 | `0x05113631` | `0x0000000000000000` |
    | xe19 | `0x05114631` | `0x0000000000000000` |
    | xe20 | `0x05115631` | `0x0000000000000000` |
    | xe21 | `0x05116631` | `0x0000000000000000` |
    | xe22 | `0x05117631` | `0x0000000000000000` |
    | xe23 | `0x05118631` | `0x0000000000000000` |
    | xe24 | `0x05119631` | `0x0000000000000000` |
    | xe25 | `0x0511a631` | `0x0000000000000000` |
    | xe26 | `0x0511b631` | `0x0000000000000000` |
    | xe27 | `0x0511c631` | `0x0000000000000000` |
    | xe28 | `0x0511d631` | `0x0000000000000000` |
    | xe29 | `0x0511e631` | `0x0000000000000000` |
    | xe30 | `0x0511f631` | `0x0000000000000000` |
    | xe31 | `0x05120631` | `0x0000000000000000` |
    | xe32 | `0x05121631` | `0x0000000000000000` |
    | xe33 | `0x05122631` | `0x0000000000000000` |
    | xe34 | `0x05123631` | `0x0000000000000000` |
    | xe35 | `0x05124631` | `0x0000000000000000` |
    | xe36 | `0x05125631` | `0x0000000000000000` |
    | xe37 | `0x05126631` | `0x0000000000000000` |
    | xe38 | `0x05127631` | `0x0000000000000000` |
    | xe39 | `0x05128631` | `0x0000000000000000` |
    | xe40 | `0x05129631` | `0x0000000000000000` |
    | xe41 | `0x0512a631` | `0x0000000000000000` |
    | xe42 | `0x0512b631` | `0x0000000000000000` |
    | xe43 | `0x0512c631` | `0x0000000000000000` |
    | xe44 | `0x0512d631` | `0x0000000000000000` |
    | xe45 | `0x0512e631` | `0x0000000000000000` |
    | xe46 | `0x0512f631` | `0x0000000000000000` |
    | xe47 | `0x05130631` | `0x0000000000000000` |
    | xe48 | `0x05131631` | `0x0000000000000000` |
    | xe49 | `0x05132631` | `0x0000000000000000` |
    | xe50 | `0x05133631` | `0x0000000000000000` |
    | xe51 | `0x05134631` | `0x0000000000000000` |
    | lb0 | `0x05141631` | `0x0000000000000000` |

---

## ING_MPLS_TPIDr

- **Address:** `0x05180600`  ·  **Size:** 4 bytes
- **Function:** Ingress Outer TPID register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

---

## ING_MPLS_TPID_0r

- **Address:** `0x05180600`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180600` | `0x00008100` |

---

## ING_MPLS_TPID_1r

- **Address:** `0x05180601`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180601` | `0x00009100` |

---

## ING_MPLS_TPID_2r

- **Address:** `0x05180602`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180602` | `0x000088a8` |

---

## ING_MPLS_TPID_3r

- **Address:** `0x05180603`  ·  **Size:** 4 bytes
- **Function:** Ingress outer TPID matching register #3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180603` | `0x00000000` |

---

## ING_MPLS_INNER_TPIDr

- **Address:** `0x05180604`  ·  **Size:** 4 bytes
- **Function:** Ingress inner TPID matching register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | TPID |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180604` | `0x00008100` |

---

## VRF_MASKr

- **Address:** `0x0518060b`  ·  **Size:** 4 bytes
- **Function:** VRF_MASK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | MASK |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518060b` | `0x00000000` |

---

## RTAG7_HASH_FIELD_BMAP_1r

- **Address:** `0x0518060c`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV4_FIELD_BITMAP_A |
    | `[25:13]` | IPV4_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518060c` | `0x00000f1c` |

---

## RTAG7_HASH_FIELD_BMAP_2r

- **Address:** `0x0518060d`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV6_FIELD_BITMAP_A |
    | `[25:13]` | IPV6_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518060d` | `0x00000f1c` |

---

## RTAG7_HASH_FIELD_BMAP_3r

- **Address:** `0x0518060e`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | L2_FIELD_BITMAP_A |
    | `[25:13]` | L2_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518060e` | `0x00000000` |

---

## RTAG7_HASH_FIELD_BMAP_5r

- **Address:** `0x0518060f`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | UNKNOWN_PPD_FIELD_BITMAP_A |
    | `[25:13]` | UNKNOWN_PPD_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518060f` | `0x00000000` |

---

## RTAG7_MPLS_L2_PAYLOAD_HASH_FIELD_BMAPr

- **Address:** `0x05180610`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for MPLS terminated tunnels with L2 payloads

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | MPLS_L2_PAYLOAD_BITMAP_A |
    | `[25:13]` | MPLS_L2_PAYLOAD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180610` | `0x00000000` |

---

## RTAG7_MPLS_L3_PAYLOAD_HASH_FIELD_BMAPr

- **Address:** `0x05180611`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for MPLS terminated tunnels with L3 payloads

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | MPLS_L3_PAYLOAD_BITMAP_A |
    | `[25:13]` | MPLS_L3_PAYLOAD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180611` | `0x00000000` |

---

## RTAG7_MPLS_OUTER_HASH_FIELD_BMAPr

- **Address:** `0x05180612`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for MPLS non-terminated packets

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | MPLS_OUTER_BITMAP_A |
    | `[25:13]` | MPLS_OUTER_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180612` | `0x00000000` |

---

## RTAG7_MIM_PAYLOAD_HASH_FIELD_BMAPr

- **Address:** `0x05180613`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap for MAC-in-MAC terminated tunnels

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | MIM_PAYLOAD_BITMAP_A |
    | `[25:13]` | MIM_PAYLOAD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180613` | `0x00000000` |

---

## RTAG7_MIM_OUTER_HASH_FIELD_BMAPr

- **Address:** `0x05180614`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap for MAC-in-MAC non-terminated tunnels

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | MIM_OUTER_BITMAP_A |
    | `[25:13]` | MIM_OUTER_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180614` | `0x00000000` |

---

## RTAG7_HASH_SEED_Ar

- **Address:** `0x05180615`  ·  **Size:** 4 bytes
- **Function:** Hash Seed for Rtag7 hashing

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180615` | `0x0000002a` |

---

## RTAG7_HASH_SEED_Br

- **Address:** `0x05180616`  ·  **Size:** 4 bytes
- **Function:** Hash Seed for Rtag7 hashing

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180616` | `0x00000000` |

---

## DROP_CONTROL_0r

- **Address:** `0x05180617`  ·  **Size:** 4 bytes
- **Function:** Register for drop controls in the mpls stage

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DISABLE_DOS_CHECKS_ON_HIGIG |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180617` | `0x00000000` |

---

## ING_L2_TUNNEL_PARSE_CONTROLr

- **Address:** `0x05180618`  ·  **Size:** 4 bytes
- **Function:** Register for parser controls in L2 Tunnel Payload (Impls) parser.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MLD_ENABLE |
    | `[0]` | PARSE_IPV6_PAYLOAD |
    | `[1]` | IGMP_ENABLE |
    | `[1]` | PARSE_IPV4_PAYLOAD |
    | `[2]` | IFP_L2_TUNNEL_PAYLOAD_FIELD_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180618` | `0x00000000` |

---

## RTAG7_HASH_CONTROL_2r

- **Address:** `0x05180619`  ·  **Size:** 4 bytes
- **Function:** Hash control register 2 for Rtag7 hashing.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RTAG7_HASH_BIN_0_SELECT_A |
    | `[1]` | RTAG7_HASH_BIN_1_SELECT_A |
    | `[2]` | DISABLE_HASH_MIM_INNER_L2_A |
    | `[3]` | ENABLE_BIN_12_OVERLAY_A |
    | `[4]` | RTAG7_HASH_BIN_0_SELECT_B |
    | `[5]` | RTAG7_HASH_BIN_1_SELECT_B |
    | `[6]` | DISABLE_HASH_MIM_INNER_L2_B |
    | `[7]` | ENABLE_BIN_12_OVERLAY_B |
    | `[8]` | TREAT_PPD2_AS_KNOWN_PPD |
    | `[12:9]` | MIM_PAYLOAD_TPID_ENABLE |
    | `[13]` | MACRO_FLOW_HASH_BYTE_SEL |
    | `[17:14]` | MACRO_FLOW_HASH_FUNC_SEL |
    | `[18]` | ENABLE_FLOW_LABEL_IPV6_A |
    | `[19]` | ENABLE_FLOW_LABEL_IPV6_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180619` | `0x00000000` |

---

## RTAG7_HASH_CONTROL_3r

- **Address:** `0x0518061a`  ·  **Size:** 4 bytes
- **Function:** Hash control register 2 for Rtag7 hashing.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | HASH_A0_FUNCTION_SELECT |
    | `[7:4]` | HASH_A1_FUNCTION_SELECT |
    | `[8]` | HASH_PRE_PROCESSING_ENABLE_A |
    | `[12:9]` | HASH_B0_FUNCTION_SELECT |
    | `[16:13]` | HASH_B1_FUNCTION_SELECT |
    | `[17]` | HASH_PRE_PROCESSING_ENABLE_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061a` | `0x00000009` |

---

## RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1r

- **Address:** `0x0518061b`  ·  **Size:** 4 bytes
- **Function:** Rtag7 IPV4 TCP/UDP Source-equals-Dest Field Bitmap control register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV4_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_A |
    | `[25:13]` | IPV4_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061b` | `0x00000f3c` |

---

## RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2r

- **Address:** `0x0518061c`  ·  **Size:** 4 bytes
- **Function:** Rtag7 IPV4 TCP/UDP Field Bitmap control register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV4_TCP_UDP_FIELD_BITMAP_A |
    | `[25:13]` | IPV4_TCP_UDP_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061c` | `0x00000f7c` |

---

## RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1r

- **Address:** `0x0518061d`  ·  **Size:** 4 bytes
- **Function:** Rtag7 IPV6 TCP/UDP Source=Dest Field Bitmap control register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV6_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_A |
    | `[25:13]` | IPV6_TCP_UDP_SRC_EQ_DST_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061d` | `0x00000f3c` |

---

## RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2r

- **Address:** `0x0518061e`  ·  **Size:** 4 bytes
- **Function:** Rtag7 IPV6 TCP/UDP Field Bitmap control register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | IPV6_TCP_UDP_FIELD_BITMAP_A |
    | `[25:13]` | IPV6_TCP_UDP_FIELD_BITMAP_B |
    | `[26]` | IPV6_SRCDST_FIELD_SEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061e` | `0x00000f7c` |

---

## RTAG7_FCOE_HASH_FIELD_BMAPr

- **Address:** `0x0518061f`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for FCoE packets.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | FCOE_FIELD_BITMAP_A |
    | `[25:13]` | FCOE_FIELD_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0518061f` | `0x00000000` |

---

## RTAG7_TRILL_TUNNEL_HASH_FIELD_BMAPr

- **Address:** `0x05180620`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for TRILL tunnel packets.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | TRILL_TUNNEL_BITMAP_A |
    | `[25:13]` | TRILL_TUNNEL_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180620` | `0x00000000` |

---

## RTAG7_TRILL_PAYLOAD_L2_HASH_FIELD_BMAPr

- **Address:** `0x05180621`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for TRILL tunnel packets.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | TRILL_PAYLOAD_L2_BITMAP_A |
    | `[25:13]` | TRILL_PAYLOAD_L2_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180621` | `0x00000000` |

---

## RTAG7_TRILL_PAYLOAD_L3_HASH_FIELD_BMAPr

- **Address:** `0x05180622`  ·  **Size:** 4 bytes
- **Function:** Rtag7 hashing field selection bitmap register for TRILL tunnel packets.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | TRILL_PAYLOAD_L3_BITMAP_A |
    | `[25:13]` | TRILL_PAYLOAD_L3_BITMAP_B |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180622` | `0x00000000` |

---

## HASH_CONTROLr

- **Address:** `0x05180640`  ·  **Size:** 4 bytes
- **Function:** Hash Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | NON_UC_TRUNK_HASH_MOD_PORT_ENABLE |
    | `[1]` | NON_UC_TRUNK_HASH_SRC_ENABLE |
    | `[2]` | NON_UC_TRUNK_HASH_DST_ENABLE |
    | `[3]` | UC_TRUNK_HASH_USE_SRC_PORT |
    | `[11:4]` | ECMP_HASH_UDF |
    | `[12]` | ECMP_HASH_USE_DIP |
    | `[14:13]` | ECMP_HASH_SEL |
    | `[17:15]` | L2_AND_VLAN_MAC_HASH_SELECT |
    | `[20:18]` | L3_HASH_SELECT |
    | `[21]` | ENABLE_DRACO1_5_HASH |
    | `[22]` | USE_TCP_UDP_PORTS |
    | `[23]` | ECMP_HASH_USE_RTAG7 |
    | `[24]` | NON_UC_TRUNK_HASH_USE_RTAG7 |
    | `[27:25]` | ECMP_HASH_FIELD_UPPER_BITS_COUNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180640` | `0x0dd14000` |

---

## MIM_DEFAULT_NETWORK_SVPr

- **Address:** `0x05180641`  ·  **Size:** 4 bytes
- **Function:** Register for MIM Default Network SVP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | SVP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180641` | `0x00000000` |

---

## TRILL_RBRIDGE_NICKNAME_SELECTr

- **Address:** `0x05180642`  ·  **Size:** 4 bytes
- **Function:** Register to select source of TRILL RBridge nickname index

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | USE_SVP |
    | `[1]` | USE_VLAN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180642` | `0x00000000` |

---

## VLAN_MEMORY_DBGCTRLr

- **Address:** `0x05180d00`  ·  **Size:** 4 bytes
- **Function:** VLAN_MEMORY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | VLAN_STG_TM |
    | `[9:5]` | VLAN_TM |
    | `[14:10]` | VLAN_PROFILE_TM |
    | `[15]` | VLAN_STG_PM |
    | `[16]` | VLAN_PM |
    | `[17]` | VLAN_PROFILE_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d00` | `0x00000000` |

---

## VLAN_PARITY_CONTROLr

- **Address:** `0x05180d01`  ·  **Size:** 4 bytes
- **Function:** VLAN_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d01` | `0x00000001` |

---

## VLAN_PARITY_STATUS_INTRr

- **Address:** `0x05180d02`  ·  **Size:** 4 bytes
- **Function:** VLAN_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d02` | `0x00000000` |

---

## VLAN_PARITY_STATUS_NACKr

- **Address:** `0x05180d03`  ·  **Size:** 4 bytes
- **Function:** VLAN_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d03` | `0x00000000` |

---

## VLAN_STG_PARITY_CONTROLr

- **Address:** `0x05180d04`  ·  **Size:** 4 bytes
- **Function:** VLAN_STG_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d04` | `0x00000001` |

---

## VLAN_STG_PARITY_STATUS_INTRr

- **Address:** `0x05180d05`  ·  **Size:** 4 bytes
- **Function:** VLAN_STG_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d05` | `0x00000000` |

---

## VLAN_STG_PARITY_STATUS_NACKr

- **Address:** `0x05180d06`  ·  **Size:** 4 bytes
- **Function:** VLAN_STG_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d06` | `0x00000000` |

---

## MY_STATION_CAM_DBGCTRLr

- **Address:** `0x05180d07`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM0_TM |
    | `[18:14]` | RAM0_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d07` | `0x00000000` |

---

## MY_STATION_CAM_BIST_CONTROLr

- **Address:** `0x05180d08`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_CAM_BIST_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN0 |
    | `[1]` | DEBUG_EN0 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d08` | `0x00000000` |

---

## MY_STATION_CAM_BIST_STATUSr

- **Address:** `0x05180d09`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_CAM_BIST_STATUS, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d09` | `0x00000000` |

---

## MY_STATION_CAM_BIST_CONFIGr

- **Address:** `0x05180d0a`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0a` | `0x00000000` |

---

## MY_STATION_CAM_BIST_DBG_DATAr

- **Address:** `0x05180d0b`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0b` | `0x00000000` |

---

## SOURCE_VP_PARITY_CONTROLr

- **Address:** `0x05180d0c`  ·  **Size:** 4 bytes
- **Function:** SOURCE_VP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0c` | `0x00000001` |

---

## SOURCE_VP_PARITY_STATUS_INTRr

- **Address:** `0x05180d0d`  ·  **Size:** 4 bytes
- **Function:** SOURCE_VP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0d` | `0x00000000` |

---

## SOURCE_VP_PARITY_STATUS_NACKr

- **Address:** `0x05180d0e`  ·  **Size:** 4 bytes
- **Function:** SOURCE_VP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0e` | `0x00000000` |

---

## L3_IIF_PARITY_CONTROLr

- **Address:** `0x05180d0f`  ·  **Size:** 4 bytes
- **Function:** L3_IIF_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d0f` | `0x00000001` |

---

## L3_IIF_PARITY_STATUS_INTRr

- **Address:** `0x05180d10`  ·  **Size:** 4 bytes
- **Function:** L3_IIF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d10` | `0x00000000` |

---

## L3_IIF_PARITY_STATUS_NACKr

- **Address:** `0x05180d11`  ·  **Size:** 4 bytes
- **Function:** L3_IIF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d11` | `0x00000000` |

---

## VLAN_MPLS_PARITY_CONTROLr

- **Address:** `0x05180d12`  ·  **Size:** 4 bytes
- **Function:** VLAN_MPLS_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d12` | `0x00000001` |

---

## VLAN_MPLS_PARITY_STATUS_INTRr

- **Address:** `0x05180d13`  ·  **Size:** 4 bytes
- **Function:** VLAN_MPLS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d13` | `0x00000000` |

---

## VLAN_MPLS_PARITY_STATUS_NACKr

- **Address:** `0x05180d14`  ·  **Size:** 4 bytes
- **Function:** VLAN_MPLS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d14` | `0x00000000` |

---

## VFI_PARITY_CONTROLr

- **Address:** `0x05180d15`  ·  **Size:** 4 bytes
- **Function:** VFI_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d15` | `0x00000001` |

---

## VFI_PARITY_STATUS_INTRr

- **Address:** `0x05180d16`  ·  **Size:** 4 bytes
- **Function:** VFI_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d16` | `0x00000000` |

---

## VFI_PARITY_STATUS_NACKr

- **Address:** `0x05180d17`  ·  **Size:** 4 bytes
- **Function:** VFI_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d17` | `0x00000000` |

---

## VFI_1_PARITY_CONTROLr

- **Address:** `0x05180d18`  ·  **Size:** 4 bytes
- **Function:** VFI_1_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d18` | `0x00000001` |

---

## VFI_1_PARITY_STATUS_INTRr

- **Address:** `0x05180d19`  ·  **Size:** 4 bytes
- **Function:** VFI_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d19` | `0x00000000` |

---

## VFI_1_PARITY_STATUS_NACKr

- **Address:** `0x05180d1a`  ·  **Size:** 4 bytes
- **Function:** VFI_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1a` | `0x00000000` |

---

## VRF_PARITY_CONTROLr

- **Address:** `0x05180d1b`  ·  **Size:** 4 bytes
- **Function:** VRF_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1b` | `0x00000001` |

---

## VRF_PARITY_STATUS_INTRr

- **Address:** `0x05180d1c`  ·  **Size:** 4 bytes
- **Function:** VRF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1c` | `0x00000000` |

---

## VRF_PARITY_STATUS_NACKr

- **Address:** `0x05180d1d`  ·  **Size:** 4 bytes
- **Function:** VRF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1d` | `0x00000000` |

---

## MPLS_MEMORY_DBGCTRL_0r

- **Address:** `0x05180d1e`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SOURCE_VP_TM |
    | `[9:5]` | L3_IIF_TM |
    | `[14:10]` | VFI_TM |
    | `[19:15]` | VFI_1_TM |
    | `[24:20]` | VRF_TM |
    | `[29:25]` | VLAN_MPLS_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1e` | `0x00000000` |

---

## MPLS_MEMORY_DBGCTRL_1r

- **Address:** `0x05180d1f`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SOURCE_VP_PM |
    | `[1]` | L3_IIF_PM |
    | `[2]` | VFI_PM |
    | `[3]` | VFI_1_PM |
    | `[4]` | VRF_PM |
    | `[5]` | VLAN_MPLS_PM |
    | `[6]` | MY_STATION_DATA_PM |
    | `[11:7]` | MY_STATION_DATA_TM |
    | `[12]` | ING_MPLS_EXP_MAPPING_PM |
    | `[17:13]` | ING_MPLS_EXP_MAPPING_TM |
    | `[18]` | ING_OUTER_DOT1P_MAPPING_TABLE_PM |
    | `[23:19]` | ING_OUTER_DOT1P_MAPPING_TABLE_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d1f` | `0x00000000` |

---

## MY_STATION_DATA_PARITY_CONTROLr

- **Address:** `0x05180d20`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d20` | `0x00000000` |

---

## MY_STATION_DATA_PARITY_STATUS_INTRr

- **Address:** `0x05180d21`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d21` | `0x00000000` |

---

## MY_STATION_DATA_PARITY_STATUS_NACKr

- **Address:** `0x05180d22`  ·  **Size:** 4 bytes
- **Function:** MY_STATION_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x05180d22` | `0x00000000` |

---

## PP_C0_PORT_A_ADDRr

- **Address:** `0x06180330`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180330` | `0x00000000` |

---

## PP_C0_PORT_A_CMDr

- **Address:** `0x06180331`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180331` | `0x00000000` |

---

## PP_C0_PORT_A_DATA_0r

- **Address:** `0x06180332`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180332` | `0xffffffff` |

---

## PP_C0_PORT_A_DATA_1r

- **Address:** `0x06180333`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180333` | `0xffffefff` |

---

## PP_C0_PORT_A_DATA_2r

- **Address:** `0x06180334`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180334` | `0xffffbfff` |

---

## PP_C0_PORT_A_DATA_3r

- **Address:** `0x06180335`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_A_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180335` | `0x0000000f` |

---

## PP_C0_PORT_B_ADDRr

- **Address:** `0x06180336`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180336` | `0x00000000` |

---

## PP_C0_PORT_B_CMDr

- **Address:** `0x06180337`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180337` | `0x00000000` |

---

## PP_C0_PORT_B_DATA_0r

- **Address:** `0x06180338`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180338` | `0xffffffff` |

---

## PP_C0_PORT_B_DATA_1r

- **Address:** `0x06180339`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180339` | `0xffffefff` |

---

## PP_C0_PORT_B_DATA_2r

- **Address:** `0x0618033a`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033a` | `0xffffbfff` |

---

## PP_C0_PORT_B_DATA_3r

- **Address:** `0x0618033b`  ·  **Size:** 4 bytes
- **Function:** PP_C0_PORT_B_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033b` | `0x0000000f` |

---

## PP_C1_PORT_A_ADDRr

- **Address:** `0x0618033c`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033c` | `0x00000000` |

---

## PP_C1_PORT_A_CMDr

- **Address:** `0x0618033d`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033d` | `0x00000000` |

---

## PP_C1_PORT_A_DATA_0r

- **Address:** `0x0618033e`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033e` | `0xffffffff` |

---

## PP_C1_PORT_A_DATA_1r

- **Address:** `0x0618033f`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618033f` | `0xffffefff` |

---

## PP_C1_PORT_A_DATA_2r

- **Address:** `0x06180340`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180340` | `0xffffbfff` |

---

## PP_C1_PORT_A_DATA_3r

- **Address:** `0x06180341`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_A_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180341` | `0x0000000f` |

---

## PP_C1_PORT_B_ADDRr

- **Address:** `0x06180342`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180342` | `0x00000000` |

---

## PP_C1_PORT_B_CMDr

- **Address:** `0x06180343`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180343` | `0x00000000` |

---

## PP_C1_PORT_B_DATA_0r

- **Address:** `0x06180344`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180344` | `0xffffffff` |

---

## PP_C1_PORT_B_DATA_1r

- **Address:** `0x06180345`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180345` | `0xffffefff` |

---

## PP_C1_PORT_B_DATA_2r

- **Address:** `0x06180346`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180346` | `0xffffbfff` |

---

## PP_C1_PORT_B_DATA_3r

- **Address:** `0x06180347`  ·  **Size:** 4 bytes
- **Function:** PP_C1_PORT_B_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180347` | `0x0000000f` |

---

## PP_C2_PORT_A_ADDRr

- **Address:** `0x06180348`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180348` | `0x00000000` |

---

## PP_C2_PORT_A_CMDr

- **Address:** `0x06180349`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180349` | `0x00000000` |

---

## PP_C2_PORT_A_DATA_0r

- **Address:** `0x0618034a`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034a` | `0xffffffff` |

---

## PP_C2_PORT_A_DATA_1r

- **Address:** `0x0618034b`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034b` | `0xffffefff` |

---

## PP_C2_PORT_A_DATA_2r

- **Address:** `0x0618034c`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034c` | `0xffffbfff` |

---

## PP_C2_PORT_A_DATA_3r

- **Address:** `0x0618034d`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_A_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034d` | `0x0000000f` |

---

## PP_C2_PORT_B_ADDRr

- **Address:** `0x0618034e`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034e` | `0x00000000` |

---

## PP_C2_PORT_B_CMDr

- **Address:** `0x0618034f`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618034f` | `0x00000000` |

---

## PP_C2_PORT_B_DATA_0r

- **Address:** `0x06180350`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180350` | `0xffffffff` |

---

## PP_C2_PORT_B_DATA_1r

- **Address:** `0x06180351`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180351` | `0xffffefff` |

---

## PP_C2_PORT_B_DATA_2r

- **Address:** `0x06180352`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180352` | `0xffffbfff` |

---

## PP_C2_PORT_B_DATA_3r

- **Address:** `0x06180353`  ·  **Size:** 4 bytes
- **Function:** PP_C2_PORT_B_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180353` | `0x0000000f` |

---

## PP_C3_PORT_A_ADDRr

- **Address:** `0x06180354`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180354` | `0x00000000` |

---

## PP_C3_PORT_A_CMDr

- **Address:** `0x06180355`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180355` | `0x00000000` |

---

## PP_C3_PORT_A_DATA_0r

- **Address:** `0x06180356`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180356` | `0xffffffff` |

---

## PP_C3_PORT_A_DATA_1r

- **Address:** `0x06180357`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180357` | `0xffffefff` |

---

## PP_C3_PORT_A_DATA_2r

- **Address:** `0x06180358`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180358` | `0xffffbfff` |

---

## PP_C3_PORT_A_DATA_3r

- **Address:** `0x06180359`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_A_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180359` | `0x0000000f` |

---

## PP_C3_PORT_B_ADDRr

- **Address:** `0x0618035a`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_ADDR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | ADDR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035a` | `0x00000000` |

---

## PP_C3_PORT_B_CMDr

- **Address:** `0x0618035b`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_CMD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CS |
    | `[1]` | WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035b` | `0x00000000` |

---

## PP_C3_PORT_B_DATA_0r

- **Address:** `0x0618035c`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_DATA_0

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035c` | `0xffffffff` |

---

## PP_C3_PORT_B_DATA_1r

- **Address:** `0x0618035d`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_DATA_1

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035d` | `0xffffefff` |

---

## PP_C3_PORT_B_DATA_2r

- **Address:** `0x0618035e`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_DATA_2

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035e` | `0xffffbfff` |

---

## PP_C3_PORT_B_DATA_3r

- **Address:** `0x0618035f`  ·  **Size:** 4 bytes
- **Function:** PP_C3_PORT_B_DATA_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | DATA_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0618035f` | `0x0000000f` |

---

## PP_MODULE_CONTROLr

- **Address:** `0x06180360`  ·  **Size:** 4 bytes
- **Function:** PP_MODULE_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | READ_LATENCY |
    | `[4]` | CLEAR_ADDR |
    | `[5]` | CLEAR_DATA |
    | `[6]` | CLEAR_CS |
    | `[7]` | CLEAR_WE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180360` | `0x00000000` |

---

## PP_PROGRAM_GOr

- **Address:** `0x06180361`  ·  **Size:** 4 bytes
- **Function:** PP_PROGRAM_GO

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | GO |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180361` | `0x00000000` |

---

## L2_AUX_HASH_CONTROLr

- **Address:** `0x06180600`  ·  **Size:** 4 bytes
- **Function:** L2_AUX_HASH_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | INSERT_LEAST_FULL_HALF |
    | `[3:1]` | HASH_SELECT |
    | `[4]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180600` | `0x00000013` |

---

## L2_LEARN_CONTROLr

- **Address:** `0x06180617`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_RD_PTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2_RECORD_OVERFLOW_ENABLE |
    | `[1]` | NOCOPY_ON_OVERFLOW |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180617` | `0x00000001` |

---

## IP3_INTR_STATUSr

- **Address:** `0x06180d00`  ·  **Size:** 4 bytes
- **Function:** IP3 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2_ENTRY_PAR_ERR |
    | `[1]` | L2_MOD_FIFO_INTR |
    | `[2]` | L2_USER_ENTRY_DATA_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d00` | `0x00000000` |

---

## IP3_INTR_ENABLEr

- **Address:** `0x06180d01`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP2_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2_ENTRY_PAR_ERR |
    | `[1]` | L2_MOD_FIFO_INTR |
    | `[2]` | L2_USER_ENTRY_DATA_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d01` | `0x00000007` |

---

## L2_USER_ENTRY_CAM_DBGCTRLr

- **Address:** `0x06180d02`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |
    | `[17:14]` | BLKSEL |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d02` | `0x0003c000` |

---

## L2_USER_ENTRY_CAM_BIST_DBGCTRLr

- **Address:** `0x06180d03`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_CAM_BIST_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN |
    | `[1]` | DEBUG_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d03` | `0x00000000` |

---

## L2_USER_ENTRY_CAM_BIST_STATUSr

- **Address:** `0x06180d04`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d04` | `0x00000000` |

---

## L2_USER_ENTRY_CAM_BIST_CONFIGr

- **Address:** `0x06180d05`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d05` | `0x00000000` |

---

## L2_USER_ENTRY_CAM_BIST_DBG_DATAr

- **Address:** `0x06180d06`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d06` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_0r

- **Address:** `0x06180d07`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM0_TM |
    | `[19:10]` | RAM1_TM |
    | `[29:20]` | RAM2_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d07` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_1r

- **Address:** `0x06180d08`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM3_TM |
    | `[19:10]` | RAM4_TM |
    | `[29:20]` | RAM5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d08` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_2r

- **Address:** `0x06180d09`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM6_TM |
    | `[19:10]` | RAM7_TM |
    | `[29:20]` | RAM8_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d09` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_3r

- **Address:** `0x06180d0a`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM9_TM |
    | `[19:10]` | RAM10_TM |
    | `[29:20]` | RAM11_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0a` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_4r

- **Address:** `0x06180d0b`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM12_TM |
    | `[19:10]` | RAM13_TM |
    | `[29:20]` | RAM14_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0b` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_5r

- **Address:** `0x06180d0c`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM15_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0c` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_6r

- **Address:** `0x06180d0d`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RAM0_DCM |
    | `[1]` | RAM1_DCM |
    | `[2]` | RAM2_DCM |
    | `[3]` | RAM3_DCM |
    | `[4]` | RAM4_DCM |
    | `[5]` | RAM5_DCM |
    | `[6]` | RAM6_DCM |
    | `[7]` | RAM7_DCM |
    | `[8]` | RAM8_DCM |
    | `[9]` | RAM9_DCM |
    | `[10]` | RAM10_DCM |
    | `[11]` | RAM11_DCM |
    | `[12]` | RAM12_DCM |
    | `[13]` | RAM13_DCM |
    | `[14]` | RAM14_DCM |
    | `[15]` | RAM15_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0d` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_7r

- **Address:** `0x06180d0e`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | RAM0_PSM_VDD |
    | `[3:2]` | RAM1_PSM_VDD |
    | `[5:4]` | RAM2_PSM_VDD |
    | `[7:6]` | RAM3_PSM_VDD |
    | `[9:8]` | RAM4_PSM_VDD |
    | `[11:10]` | RAM5_PSM_VDD |
    | `[13:12]` | RAM6_PSM_VDD |
    | `[15:14]` | RAM7_PSM_VDD |
    | `[17:16]` | RAM8_PSM_VDD |
    | `[19:18]` | RAM9_PSM_VDD |
    | `[21:20]` | RAM10_PSM_VDD |
    | `[23:22]` | RAM11_PSM_VDD |
    | `[25:24]` | RAM12_PSM_VDD |
    | `[27:26]` | RAM13_PSM_VDD |
    | `[29:28]` | RAM14_PSM_VDD |
    | `[31:30]` | RAM15_PSM_VDD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0e` | `0x00000000` |

---

## L2_ENTRY_DA_DBGCTRL_8r

- **Address:** `0x06180d0f`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | RAM_TOP_PDAH |
    | `[31:16]` | RAM_BOTTOM_PDAH |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d0f` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_0r

- **Address:** `0x06180d10`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM0_TM |
    | `[19:10]` | RAM1_TM |
    | `[29:20]` | RAM2_TM |
    | `[30]` | USE_SA_TABLE_FOR_SBUS_MEMRD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d10` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_1r

- **Address:** `0x06180d11`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM3_TM |
    | `[19:10]` | RAM4_TM |
    | `[29:20]` | RAM5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d11` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_2r

- **Address:** `0x06180d12`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM6_TM |
    | `[19:10]` | RAM7_TM |
    | `[29:20]` | RAM8_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d12` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_3r

- **Address:** `0x06180d13`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM9_TM |
    | `[19:10]` | RAM10_TM |
    | `[29:20]` | RAM11_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d13` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_4r

- **Address:** `0x06180d14`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM12_TM |
    | `[19:10]` | RAM13_TM |
    | `[29:20]` | RAM14_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d14` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_5r

- **Address:** `0x06180d15`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM15_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d15` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_6r

- **Address:** `0x06180d16`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RAM0_DCM |
    | `[1]` | RAM1_DCM |
    | `[2]` | RAM2_DCM |
    | `[3]` | RAM3_DCM |
    | `[4]` | RAM4_DCM |
    | `[5]` | RAM5_DCM |
    | `[6]` | RAM6_DCM |
    | `[7]` | RAM7_DCM |
    | `[8]` | RAM8_DCM |
    | `[9]` | RAM9_DCM |
    | `[10]` | RAM10_DCM |
    | `[11]` | RAM11_DCM |
    | `[12]` | RAM12_DCM |
    | `[13]` | RAM13_DCM |
    | `[14]` | RAM14_DCM |
    | `[15]` | RAM15_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d16` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_7r

- **Address:** `0x06180d17`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | RAM0_PSM_VDD |
    | `[3:2]` | RAM1_PSM_VDD |
    | `[5:4]` | RAM2_PSM_VDD |
    | `[7:6]` | RAM3_PSM_VDD |
    | `[9:8]` | RAM4_PSM_VDD |
    | `[11:10]` | RAM5_PSM_VDD |
    | `[13:12]` | RAM6_PSM_VDD |
    | `[15:14]` | RAM7_PSM_VDD |
    | `[17:16]` | RAM8_PSM_VDD |
    | `[19:18]` | RAM9_PSM_VDD |
    | `[21:20]` | RAM10_PSM_VDD |
    | `[23:22]` | RAM11_PSM_VDD |
    | `[25:24]` | RAM12_PSM_VDD |
    | `[27:26]` | RAM13_PSM_VDD |
    | `[29:28]` | RAM14_PSM_VDD |
    | `[31:30]` | RAM15_PSM_VDD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d17` | `0x00000000` |

---

## L2_ENTRY_SA_DBGCTRL_8r

- **Address:** `0x06180d18`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | RAM_TOP_PDAH |
    | `[31:16]` | RAM_BOTTOM_PDAH |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d18` | `0x00000000` |

---

## L2_HIT_DBGCTRL_0r

- **Address:** `0x06180d19`  ·  **Size:** 4 bytes
- **Function:** L2_HIT_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | HITDA_0_TM |
    | `[19:10]` | HITDA_1_TM |
    | `[29:20]` | HITDA_2_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d19` | `0x00000000` |

---

## L2_HIT_DBGCTRL_1r

- **Address:** `0x06180d1a`  ·  **Size:** 4 bytes
- **Function:** L2_HIT_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | HITDA_3_TM |
    | `[19:10]` | HITSA_0_TM |
    | `[29:20]` | HITSA_1_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1a` | `0x00000000` |

---

## L2_HIT_DBGCTRL_2r

- **Address:** `0x06180d1b`  ·  **Size:** 4 bytes
- **Function:** L2_HIT_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | HITSA_2_TM |
    | `[19:10]` | HITSA_3_TM |
    | `[29:20]` | HITSA_4_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1b` | `0x00000000` |

---

## L2_HIT_DBGCTRL_3r

- **Address:** `0x06180d1c`  ·  **Size:** 4 bytes
- **Function:** L2_HIT_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | HITSA_5_TM |
    | `[19:10]` | HITSA_6_TM |
    | `[29:20]` | HITSA_7_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1c` | `0x00000000` |

---

## L2_HIT_DBGCTRL_4r

- **Address:** `0x06180d1d`  ·  **Size:** 4 bytes
- **Function:** L2_HIT_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HITDA_0_PM |
    | `[1]` | HITDA_1_PM |
    | `[2]` | HITDA_2_PM |
    | `[3]` | HITDA_3_PM |
    | `[4]` | HITSA_0_PM |
    | `[5]` | HITSA_1_PM |
    | `[6]` | HITSA_2_PM |
    | `[7]` | HITSA_3_PM |
    | `[8]` | HITSA_4_PM |
    | `[9]` | HITSA_5_PM |
    | `[10]` | HITSA_6_PM |
    | `[11]` | HITSA_7_PM |
    | `[12]` | HITDA_0_DCM |
    | `[13]` | HITDA_1_DCM |
    | `[14]` | HITDA_2_DCM |
    | `[15]` | HITDA_3_DCM |
    | `[16]` | HITSA_0_DCM |
    | `[17]` | HITSA_1_DCM |
    | `[18]` | HITSA_2_DCM |
    | `[19]` | HITSA_3_DCM |
    | `[20]` | HITSA_4_DCM |
    | `[21]` | HITSA_5_DCM |
    | `[22]` | HITSA_6_DCM |
    | `[23]` | HITSA_7_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1d` | `0x00000000` |

---

## L2_ENTRY_PARITY_CONTROLr

- **Address:** `0x06180d1e`  ·  **Size:** 4 bytes
- **Function:** L2_ENTRY_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1e` | `0x00000001` |

---

## L2_ENTRY_PARITY_STATUS_INTR_0r

- **Address:** `0x06180d1f`  ·  **Size:** 4 bytes
- **Function:** L2_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[18:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d1f` | `0x00000000` |

---

## L2_ENTRY_PARITY_STATUS_INTR_1r

- **Address:** `0x06180d20`  ·  **Size:** 4 bytes
- **Function:** L2_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[18:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d20` | `0x00000000` |

---

## L2_ENTRY_PARITY_STATUS_NACK_0r

- **Address:** `0x06180d21`  ·  **Size:** 4 bytes
- **Function:** L2_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[18:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d21` | `0x00000000` |

---

## L2_ENTRY_PARITY_STATUS_NACK_1r

- **Address:** `0x06180d22`  ·  **Size:** 4 bytes
- **Function:** L2_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PARITY_ERR_BM |
    | `[4]` | MULTIPLE_ERR |
    | `[18:5]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d22` | `0x00000000` |

---

## L2_USER_ENTRY_DATA_PARITY_CONTROLr

- **Address:** `0x06180d23`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_DATA_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d23` | `0x00000001` |

---

## L2_USER_ENTRY_DATA_PARITY_STATUS_INTRr

- **Address:** `0x06180d24`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_DATA_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d24` | `0x00000000` |

---

## L2_USER_ENTRY_DATA_PARITY_STATUS_NACKr

- **Address:** `0x06180d25`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_DATA_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d25` | `0x00000000` |

---

## L2_MOD_FIFO_PARITY_CONTROLr

- **Address:** `0x06180d26`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d26` | `0x00000001` |

---

## L2_MOD_FIFO_PARITY_STATUS_INTRr

- **Address:** `0x06180d27`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d27` | `0x00000000` |

---

## L2_MOD_FIFO_PARITY_STATUS_NACKr

- **Address:** `0x06180d28`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d28` | `0x00000000` |

---

## L2_USER_ENTRY_DATA_DBGCTRLr

- **Address:** `0x06180d29`  ·  **Size:** 4 bytes
- **Function:** L2_USER_ENTRY_DATA_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | TM |
    | `[5]` | PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d29` | `0x00000000` |

---

## L2_MOD_FIFO_DBGCTRLr

- **Address:** `0x06180d2a`  ·  **Size:** 4 bytes
- **Function:** FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | L2_MOD_FIFO_TM |
    | `[5]` | L2_MOD_FIFO_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2a` | `0x00000000` |

---

## L2_MOD_FIFO_RD_PTRr

- **Address:** `0x06180d2b`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_RD_PTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2b` | `0x00000004` |

---

## L2_MOD_FIFO_WR_PTRr

- **Address:** `0x06180d2c`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_WR_PTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2c` | `0x00000004` |

---

## L2_MOD_FIFO_CNTr

- **Address:** `0x06180d2d`  ·  **Size:** 4 bytes
- **Function:** L2_MOD_FIFO_CNT

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | NUM_OF_ENTRIES |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2d` | `0x00000000` |

---

## IL2LU_PWR_WATCH_DOG_CONTROLr

- **Address:** `0x06180d2e`  ·  **Size:** 4 bytes
- **Function:** IL2LU_PWR_WATCH_DOG_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[8:1]` | CGFC |
    | `[11:9]` | RSEL |
    | `[14:12]` | CLEARCFG |
    | `[20:15]` | START |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2e` | `0x00000000` |

---

## IL2LU_PWR_WATCH_DOG_STATUSr

- **Address:** `0x06180d2f`  ·  **Size:** 4 bytes
- **Function:** IL2LU_PWR_WATCH_DOG_STATUS, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | GOOD_COUNT |
    | `[31]` | GOOD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x06180d2f` | `0x80000000` |

---

## L3_AUX_HASH_CONTROLr

- **Address:** `0x09180600`  ·  **Size:** 4 bytes
- **Function:** L3_AUX_HASH_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | INSERT_LEAST_FULL_HALF |
    | `[3:1]` | HASH_SELECT |
    | `[4]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180600` | `0x00000015` |

---

## L3_ENTRY_DBGCTRL0r

- **Address:** `0x09180d00`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM0_TM |
    | `[19:10]` | RAM1_TM |
    | `[29:20]` | RAM2_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d00` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL1r

- **Address:** `0x09180d01`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM3_TM |
    | `[19:10]` | RAM4_TM |
    | `[29:20]` | RAM5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d01` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL2r

- **Address:** `0x09180d02`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL_2, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM6_TM |
    | `[19:10]` | RAM7_TM |
    | `[29:20]` | RAM8_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d02` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL3r

- **Address:** `0x09180d03`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL_3, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM9_TM |
    | `[19:10]` | RAM10_TM |
    | `[29:20]` | RAM11_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d03` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL4r

- **Address:** `0x09180d04`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL_4, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM12_TM |
    | `[19:10]` | RAM13_TM |
    | `[29:20]` | RAM14_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d04` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL5r

- **Address:** `0x09180d05`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL_5, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM15_TM |
    | `[10]` | RAM0_PM |
    | `[11]` | RAM1_PM |
    | `[12]` | RAM2_PM |
    | `[13]` | RAM3_PM |
    | `[14]` | RAM4_PM |
    | `[15]` | RAM5_PM |
    | `[16]` | RAM6_PM |
    | `[17]` | RAM7_PM |
    | `[18]` | RAM8_PM |
    | `[19]` | RAM9_PM |
    | `[20]` | RAM10_PM |
    | `[21]` | RAM11_PM |
    | `[22]` | RAM12_PM |
    | `[23]` | RAM13_PM |
    | `[24]` | RAM14_PM |
    | `[25]` | RAM15_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d05` | `0x00000000` |

---

## L3_ENTRY_DBGCTRL6r

- **Address:** `0x09180d06`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_CONTROL_6, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RAM0_DCM |
    | `[1]` | RAM1_DCM |
    | `[2]` | RAM2_DCM |
    | `[3]` | RAM3_DCM |
    | `[4]` | RAM4_DCM |
    | `[5]` | RAM5_DCM |
    | `[6]` | RAM6_DCM |
    | `[7]` | RAM7_DCM |
    | `[8]` | RAM8_DCM |
    | `[9]` | RAM9_DCM |
    | `[10]` | RAM10_DCM |
    | `[11]` | RAM11_DCM |
    | `[12]` | RAM12_DCM |
    | `[13]` | RAM13_DCM |
    | `[14]` | RAM14_DCM |
    | `[15]` | RAM15_DCM |
    | `[17:16]` | RAM_PDAH |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d06` | `0x00000000` |

---

## L3_ENTRY_PARITY_CONTROLr

- **Address:** `0x09180d07`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d07` | `0x00000001` |

---

## L3_ENTRY_PARITY_STATUS_INTR_0r

- **Address:** `0x09180d08`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PARITY_ERR_BM |
    | `[8]` | MULTIPLE_ERR |
    | `[18:9]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d08` | `0x00000000` |

---

## L3_ENTRY_PARITY_STATUS_INTR_1r

- **Address:** `0x09180d09`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PARITY_ERR_BM |
    | `[8]` | MULTIPLE_ERR |
    | `[18:9]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d09` | `0x00000000` |

---

## L3_ENTRY_PARITY_STATUS_NACK_0r

- **Address:** `0x09180d0a`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PARITY_ERR_BM |
    | `[8]` | MULTIPLE_ERR |
    | `[18:9]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d0a` | `0x00000000` |

---

## L3_ENTRY_PARITY_STATUS_NACK_1r

- **Address:** `0x09180d0b`  ·  **Size:** 4 bytes
- **Function:** L3_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PARITY_ERR_BM |
    | `[8]` | MULTIPLE_ERR |
    | `[18:9]` | BUCKET_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x09180d0b` | `0x00000000` |

---

## L3_DEFIP_RPF_CONTROLr

- **Address:** `0x0a180601`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_RPF_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DEFIP_RPF_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180601` | `0x00000000` |

---

## L3_DEFIP_CAM_DBGCTRL0r

- **Address:** `0x0a180d00`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_CONTROL0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM0_TM |
    | `[27:14]` | CAM1_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d00` | `0x00000000` |

---

## L3_DEFIP_CAM_DBGCTRL1r

- **Address:** `0x0a180d01`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_CONTROL1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM2_TM |
    | `[27:14]` | CAM3_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d01` | `0x00000000` |

---

## L3_DEFIP_CAM_DBGCTRL2r

- **Address:** `0x0a180d02`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_CONTROL2, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM4_TM |
    | `[27:14]` | CAM5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d02` | `0x00000000` |

---

## L3_DEFIP_CAM_DBGCTRL3r

- **Address:** `0x0a180d03`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_CONTROL3, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM6_TM |
    | `[27:14]` | CAM7_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d03` | `0x00000000` |

---

## L3_DEFIP_CAM_BIST_DBGCTRLr

- **Address:** `0x0a180d04`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_BIST_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN0 |
    | `[1]` | BIST_EN1 |
    | `[2]` | BIST_EN2 |
    | `[3]` | BIST_EN3 |
    | `[4]` | BIST_EN4 |
    | `[5]` | BIST_EN5 |
    | `[6]` | BIST_EN6 |
    | `[7]` | BIST_EN7 |
    | `[8]` | DEBUG_EN0 |
    | `[9]` | DEBUG_EN1 |
    | `[10]` | DEBUG_EN2 |
    | `[11]` | DEBUG_EN3 |
    | `[12]` | DEBUG_EN4 |
    | `[13]` | DEBUG_EN5 |
    | `[14]` | DEBUG_EN6 |
    | `[15]` | DEBUG_EN7 |
    | `[16]` | MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d04` | `0x00000000` |

---

## L3_DEFIP_CAM_BIST_STATUSr

- **Address:** `0x0a180d05`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d05` | `0x00000000` |

---

## L3_DEFIP_CAM_BIST_CONFIGr

- **Address:** `0x0a180d06`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d06` | `0x00000000` |

---

## L3_DEFIP_CAM_BIST_DBG_DATAr

- **Address:** `0x0a180d07`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d07` | `0x00000000` |

---

## L3_DEFIP_CAM_ENABLEr

- **Address:** `0x0a180d08`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_CAM_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CAM_0_ENABLE |
    | `[1]` | CAM_1_ENABLE |
    | `[2]` | CAM_2_ENABLE |
    | `[3]` | CAM_3_ENABLE |
    | `[4]` | CAM_4_ENABLE |
    | `[5]` | CAM_5_ENABLE |
    | `[6]` | CAM_6_ENABLE |
    | `[7]` | CAM_7_ENABLE |
    | `[9:8]` | DIP_CAMS |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d08` | `0x000003ff` |

---

## L3_DEFIP_DATA_DBGCTRL_0r

- **Address:** `0x0a180d09`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_DATA_CONTROL_0, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM_0_TM |
    | `[19:10]` | RAM_1_TM |
    | `[29:20]` | RAM_2_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d09` | `0x00000000` |

---

## L3_DEFIP_DATA_DBGCTRL_1r

- **Address:** `0x0a180d0a`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_DATA_CONTROL_1, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | RAM_3_TM |
    | `[10]` | RAM_0_PM |
    | `[11]` | RAM_1_PM |
    | `[12]` | RAM_2_PM |
    | `[13]` | RAM_3_PM |
    | `[14]` | RAM_0_DCM |
    | `[15]` | RAM_1_DCM |
    | `[16]` | RAM_2_DCM |
    | `[17]` | RAM_3_DCM |
    | `[18]` | RTAG7_FLOW_BASED_HASH_PM |
    | `[23:19]` | RTAG7_FLOW_BASED_HASH_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0a` | `0x00000000` |

---

## L3_DEFIP_128_DATA_DBGCTRLr

- **Address:** `0x0a180d0b`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_DATA_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TM |
    | `[10]` | PM |
    | `[11]` | DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0b` | `0x00000000` |

---

## L3_DEFIP_128_CAM_DBGCTRLr

- **Address:** `0x0a180d0c`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | CAM0_TM |
    | `[27:14]` | CAM1_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0c` | `0x00000000` |

---

## L3_DEFIP_128_CAM_ENABLEr

- **Address:** `0x0a180d0d`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_ENABLE, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CAM_0_ENABLE |
    | `[1]` | CAM_1_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0d` | `0x00000003` |

---

## L3_DEFIP_128_CAM_BIST_CONTROLr

- **Address:** `0x0a180d0e`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_BIST_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN0 |
    | `[1]` | BIST_EN1 |
    | `[2]` | DEBUG_EN0 |
    | `[3]` | DEBUG_EN1 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0e` | `0x00000000` |

---

## L3_DEFIP_128_CAM_BIST_STATUSr

- **Address:** `0x0a180d0f`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_BIST_STATUS, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d0f` | `0x00000000` |

---

## L3_DEFIP_128_CAM_BIST_CONFIGr

- **Address:** `0x0a180d10`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d10` | `0x00000000` |

---

## L3_DEFIP_128_CAM_BIST_DBG_DATAr

- **Address:** `0x0a180d11`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d11` | `0x00000000` |

---

## L3_DEFIP_DATA_PARITY_CONTROLr

- **Address:** `0x0a180d12`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d12` | `0x00000001` |

---

## L3_DEFIP_DATA_PARITY_STATUS_INTRr

- **Address:** `0x0a180d13`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d13` | `0x00000000` |

---

## L3_DEFIP_DATA_PARITY_STATUS_NACKr

- **Address:** `0x0a180d14`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d14` | `0x00000000` |

---

## L3_DEFIP_128_DATA_PARITY_CONTROLr

- **Address:** `0x0a180d15`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d15` | `0x00000001` |

---

## L3_DEFIP_128_DATA_PARITY_STATUS_INTRr

- **Address:** `0x0a180d16`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d16` | `0x00000000` |

---

## L3_DEFIP_128_DATA_PARITY_STATUS_NACKr

- **Address:** `0x0a180d17`  ·  **Size:** 4 bytes
- **Function:** L3_DEFIP_128_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d17` | `0x00000000` |

---

## RTAG7_FLOW_BASED_HASH_PARITY_CONTROLr

- **Address:** `0x0a180d23`  ·  **Size:** 4 bytes
- **Function:** RTAG7_FLOW_BASED_HASH_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d23` | `0x00000000` |

---

## RTAG7_FLOW_BASED_HASH_PARITY_STATUS_INTRr

- **Address:** `0x0a180d24`  ·  **Size:** 4 bytes
- **Function:** RTAG7_FLOW_BASED_HASH_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d24` | `0x00000000` |

---

## RTAG7_FLOW_BASED_HASH_PARITY_STATUS_NACKr

- **Address:** `0x0a180d25`  ·  **Size:** 4 bytes
- **Function:** RTAG7_FLOW_BASED_HASH_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0a180d25` | `0x00000000` |

---

## RTAG7_HASH_ECMPr

- **Address:** `0x0b180600`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for ECMP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL |
    | `[6:3]` | OFFSET |
    | `[9:7]` | SUB_SEL_PAGE |
    | `[13:10]` | OFFSET_PAGE |
    | `[14]` | USE_FLOW_HASH |

---

## CBL_ATTRIBUTEr

- **Address:** `0x0b180602`  ·  **Size:** 4 bytes
- **Function:** Class based station movement attribute register, index from PORT_CBL_TABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ALLOW_MOVE_IN_CLASS |
    | `[2:1]` | PORT_LEARNING_PRIORITY |

---

## RTAG7_HASH_LBIDr

- **Address:** `0x0b180606`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for LBID selection

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL_UC |
    | `[6:3]` | OFFSET_UC |
    | `[9:7]` | SUB_SEL_NONUC |
    | `[13:10]` | OFFSET_NONUC |

---

## RTAG7_HASH_TRILL_ECMPr

- **Address:** `0x0b180623`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for TRILL ECMP.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL |
    | `[6:3]` | OFFSET |
    | `[9:7]` | SUB_SEL_PAGE |
    | `[13:10]` | OFFSET_PAGE |
    | `[14]` | USE_FLOW_HASH |

---

## IP2_INTR_STATUSr

- **Address:** `0x0b180d00`  ·  **Size:** 4 bytes
- **Function:** IP2 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | NHOP_PAR_ERR |
    | `[1]` | ECMP_GRP_PAR_ERR |
    | `[2]` | L3_ECMP_PAR_ERR |
    | `[3]` | ING_DVP_PAR_ERR |
    | `[4]` | PROT_NHI_PAR_ERR |
    | `[5]` | PORT_CBL_PAR_ERR |
    | `[6]` | PORT_CBL_MODBASE_PAR_ERR |
    | `[7]` | L3_IPMC_1_PAR_ERR |
    | `[8]` | MA_INDEX_PAR_ERR |
    | `[9]` | RMEP_PAR_ERR |
    | `[10]` | MAID_REDUCTION_PAR_ERR |
    | `[11]` | MA_STATE_PAR_ERR |
    | `[12]` | VLAN_PAR_ERR |
    | `[13]` | SVP_PAR_ERR |
    | `[14]` | L3_IIF_PAR_ERR |
    | `[15]` | VFI_INTR |
    | `[16]` | VLAN_MPLS_INTR |
    | `[17]` | VLAN_STG_INTR |
    | `[18]` | VRF_INTR |
    | `[19]` | VFI_1_INTR |
    | `[20]` | L3_ENTRY_PAR_ERR |
    | `[21]` | L3_DEFIP_DATA_PAR_ERR |
    | `[22]` | L3_DEFIP_128_DATA_PAR_ERR |
    | `[23]` | TTL_FN_PAR_ERR |
    | `[24]` | TOS_FN_PAR_ERR |
    | `[25]` | ING_PRI_CNG_MAP_PAR_ERR |
    | `[26]` | ING_UNTAGGED_PHB_PAR_ERR |
    | `[27]` | DSCP_TABLE_PAR_ERR |
    | `[28]` | FP_FIELD_SEL_PAR_ERR |
    | `[29]` | MY_STATION_DATA_PAR_INTR |
    | `[30]` | RTAG7_FLOW_BASED_HASH_PAR_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d00` | `0x00000000` |

---

## IP2_INTR_STATUS_2r

- **Address:** `0x0b180d01`  ·  **Size:** 4 bytes
- **Function:** IP2 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SOME_RDI_DEFECT_INTR |
    | `[1]` | SOME_RMEP_CCM_DEFECT_INTR |
    | `[2]` | ERROR_CCM_DEFECT_INTR |
    | `[3]` | ANY_RMEP_TLV_PORT_DOWN_INTR |
    | `[4]` | ANY_RMEP_TLV_PORT_UP_INTR |
    | `[5]` | ANY_RMEP_TLV_INTERFACE_DOWN_INTR |
    | `[6]` | ANY_RMEP_TLV_INTERFACE_UP_INTR |
    | `[7]` | XCON_CCM_DEFECT_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d01` | `0x00000000` |

---

## IP2_INTR_ENABLEr

- **Address:** `0x0b180d02`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP2_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | NHOP_PAR_ERR |
    | `[1]` | ECMP_GRP_PAR_ERR |
    | `[2]` | L3_ECMP_PAR_ERR |
    | `[3]` | ING_DVP_PAR_ERR |
    | `[4]` | PROT_NHI_PAR_ERR |
    | `[5]` | PORT_CBL_PAR_ERR |
    | `[6]` | PORT_CBL_MODBASE_PAR_ERR |
    | `[7]` | L3_IPMC_1_PAR_ERR |
    | `[8]` | MA_INDEX_PAR_ERR |
    | `[9]` | RMEP_PAR_ERR |
    | `[10]` | MAID_REDUCTION_PAR_ERR |
    | `[11]` | MA_STATE_PAR_ERR |
    | `[12]` | VLAN_PAR_ERR |
    | `[13]` | SVP_PAR_ERR |
    | `[14]` | L3_IIF_PAR_ERR |
    | `[15]` | VFI_INTR |
    | `[16]` | VLAN_MPLS_INTR |
    | `[17]` | VLAN_STG_INTR |
    | `[18]` | VRF_INTR |
    | `[19]` | VFI_1_INTR |
    | `[20]` | L3_ENTRY_PAR_ERR |
    | `[21]` | L3_DEFIP_DATA_PAR_ERR |
    | `[22]` | L3_DEFIP_128_DATA_PAR_ERR |
    | `[23]` | TTL_FN_PAR_ERR |
    | `[24]` | TOS_FN_PAR_ERR |
    | `[25]` | ING_PRI_CNG_MAP_PAR_ERR |
    | `[26]` | ING_UNTAGGED_PHB_PAR_ERR |
    | `[27]` | DSCP_TABLE_PAR_ERR |
    | `[28]` | FP_FIELD_SEL_PAR_ERR |
    | `[29]` | MY_STATION_DATA_PAR_INTR |
    | `[30]` | RTAG7_FLOW_BASED_HASH_PAR_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d02` | `0x1ffff0df` |

---

## IP2_INTR_ENABLE_2r

- **Address:** `0x0b180d03`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP2_INTR_STATUS_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SOME_RDI_DEFECT_INTR |
    | `[1]` | SOME_RMEP_CCM_DEFECT_INTR |
    | `[2]` | ERROR_CCM_DEFECT_INTR |
    | `[3]` | ANY_RMEP_TLV_PORT_DOWN_INTR |
    | `[4]` | ANY_RMEP_TLV_PORT_UP_INTR |
    | `[5]` | ANY_RMEP_TLV_INTERFACE_DOWN_INTR |
    | `[6]` | ANY_RMEP_TLV_INTERFACE_UP_INTR |
    | `[7]` | XCON_CCM_DEFECT_INTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d03` | `0x00000000` |

---

## RSEL1_RAM_DBGCTRLr

- **Address:** `0x0b180d04`  ·  **Size:** 4 bytes
- **Function:** RSEL1_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | ECMP_COUNT_TM |
    | `[9:5]` | ECMP_TM |
    | `[19:10]` | CBL_TM |
    | `[20]` | CBL_DCM |
    | `[30:21]` | CBL_MODBASE_TM |
    | `[31]` | CBL_MODBASE_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d04` | `0x00000000` |

---

## RSEL1_RAM_DBGCTRL_2r

- **Address:** `0x0b180d05`  ·  **Size:** 4 bytes
- **Function:** RSEL1_RAM_CONTROL_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | NHI_TM |
    | `[9:5]` | PROT_NHI_TM |
    | `[19:10]` | MA_STATE_TM |
    | `[20]` | MA_STATE_DCM |
    | `[30:21]` | RMEP_TM |
    | `[31]` | RMEP_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d05` | `0x00000000` |

---

## RSEL1_RAM_DBGCTRL_3r

- **Address:** `0x0b180d06`  ·  **Size:** 4 bytes
- **Function:** RSEL1_RAM_CONTROL_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | MA_INDEX_TM |
    | `[9:5]` | L3_IPMC_1_TM |
    | `[14:10]` | ING_DVP_TABLE_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d06` | `0x00000000` |

---

## RSEL1_RAM_DBGCTRL_4r

- **Address:** `0x0b180d07`  ·  **Size:** 4 bytes
- **Function:** RSEL1_RAM_CONTROL_4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CBL_MODBASE_PM |
    | `[1]` | CBL_PM |
    | `[2]` | MA_INDEX_PM |
    | `[3]` | MA_STATE_PM |
    | `[4]` | RMEP_PM |
    | `[5]` | L3_IPMC_1_PM |
    | `[6]` | INITIAL_L3_ECMP_GROUP_PM |
    | `[7]` | ING_DVP_TABLE_PM |
    | `[8]` | INITIAL_PROT_NHI_TABLE_PM |
    | `[9]` | INITIAL_L3_ECMP_PM |
    | `[10]` | INITIAL_ING_L3_NEXT_HOP_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d07` | `0x00000000` |

---

## ING_DVP_TABLE_PARITY_CONTROLr

- **Address:** `0x0b180d08`  ·  **Size:** 4 bytes
- **Function:** ING_DVP_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d08` | `0x00000001` |

---

## ING_DVP_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0b180d09`  ·  **Size:** 4 bytes
- **Function:** ING_DVP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d09` | `0x00000000` |

---

## ING_DVP_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0b180d0a`  ·  **Size:** 4 bytes
- **Function:** ING_DVP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0a` | `0x00000000` |

---

## INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROLr

- **Address:** `0x0b180d0b`  ·  **Size:** 4 bytes
- **Function:** INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0b` | `0x00000001` |

---

## INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_INTRr

- **Address:** `0x0b180d0c`  ·  **Size:** 4 bytes
- **Function:** INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0c` | `0x00000000` |

---

## INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_NACKr

- **Address:** `0x0b180d0d`  ·  **Size:** 4 bytes
- **Function:** INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0d` | `0x00000000` |

---

## INITIAL_L3_ECMP_GROUP_PARITY_CONTROLr

- **Address:** `0x0b180d0e`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0e` | `0x00000001` |

---

## INITIAL_L3_ECMP_GROUP_PARITY_STATUS_INTRr

- **Address:** `0x0b180d0f`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d0f` | `0x00000000` |

---

## INITIAL_L3_ECMP_GROUP_PARITY_STATUS_NACKr

- **Address:** `0x0b180d10`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d10` | `0x00000000` |

---

## INITIAL_L3_ECMP_PARITY_CONTROLr

- **Address:** `0x0b180d11`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d11` | `0x00000001` |

---

## INITIAL_L3_ECMP_PARITY_STATUS_INTRr

- **Address:** `0x0b180d12`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d12` | `0x00000000` |

---

## INITIAL_L3_ECMP_PARITY_STATUS_NACKr

- **Address:** `0x0b180d13`  ·  **Size:** 4 bytes
- **Function:** INITIAL_L3_ECMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d13` | `0x00000000` |

---

## INITIAL_PROT_NHI_TABLE_PARITY_CONTROLr

- **Address:** `0x0b180d14`  ·  **Size:** 4 bytes
- **Function:** INITIAL_PROT_NHI_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d14` | `0x00000001` |

---

## INITIAL_PROT_NHI_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0b180d15`  ·  **Size:** 4 bytes
- **Function:** INITIAL_PROT_NHI_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d15` | `0x00000000` |

---

## INITIAL_PROT_NHI_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0b180d16`  ·  **Size:** 4 bytes
- **Function:** INITIAL_PROT_NHI_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d16` | `0x00000000` |

---

## PORT_CBL_TABLE_PARITY_CONTROLr

- **Address:** `0x0b180d17`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d17` | `0x00000000` |

---

## PORT_CBL_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0b180d18`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d18` | `0x00000000` |

---

## PORT_CBL_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0b180d19`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d19` | `0x00000000` |

---

## PORT_CBL_TABLE_MODBASE_PARITY_CONTROLr

- **Address:** `0x0b180d1a`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_MODBASE_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1a` | `0x00000001` |

---

## PORT_CBL_TABLE_MODBASE_PARITY_STATUS_INTRr

- **Address:** `0x0b180d1b`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_MODBASE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1b` | `0x00000000` |

---

## PORT_CBL_TABLE_MODBASE_PARITY_STATUS_NACKr

- **Address:** `0x0b180d1c`  ·  **Size:** 4 bytes
- **Function:** PORT_CBL_TABLE_MODBASE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1c` | `0x00000000` |

---

## L3_IPMC_1_PARITY_CONTROLr

- **Address:** `0x0b180d1d`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_1_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1d` | `0x00000001` |

---

## L3_IPMC_1_PARITY_STATUS_INTRr

- **Address:** `0x0b180d1e`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1e` | `0x00000000` |

---

## L3_IPMC_1_PARITY_STATUS_NACKr

- **Address:** `0x0b180d1f`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d1f` | `0x00000000` |

---

## MA_INDEX_PARITY_CONTROLr

- **Address:** `0x0b180d20`  ·  **Size:** 4 bytes
- **Function:** MA_INDEX_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d20` | `0x00000000` |

---

## MA_INDEX_PARITY_STATUS_INTRr

- **Address:** `0x0b180d21`  ·  **Size:** 4 bytes
- **Function:** MA_INDEX_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d21` | `0x00000000` |

---

## MA_INDEX_PARITY_STATUS_NACKr

- **Address:** `0x0b180d22`  ·  **Size:** 4 bytes
- **Function:** MA_INDEX_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d22` | `0x00000000` |

---

## RMEP_PARITY_CONTROLr

- **Address:** `0x0b180d23`  ·  **Size:** 4 bytes
- **Function:** RMEP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d23` | `0x00000000` |

---

## RMEP_PARITY_STATUS_INTRr

- **Address:** `0x0b180d24`  ·  **Size:** 4 bytes
- **Function:** RMEP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d24` | `0x00000000` |

---

## RMEP_PARITY_STATUS_NACKr

- **Address:** `0x0b180d25`  ·  **Size:** 4 bytes
- **Function:** RMEP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d25` | `0x00000000` |

---

## MAID_REDUCTION_PARITY_CONTROLr

- **Address:** `0x0b180d26`  ·  **Size:** 4 bytes
- **Function:** MAID_REDUCTION_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d26` | `0x00000000` |

---

## MAID_REDUCTION_PARITY_STATUS_INTRr

- **Address:** `0x0b180d27`  ·  **Size:** 4 bytes
- **Function:** MAID_REDUCTION_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d27` | `0x00000000` |

---

## MAID_REDUCTION_PARITY_STATUS_NACKr

- **Address:** `0x0b180d28`  ·  **Size:** 4 bytes
- **Function:** MAID_REDUCTION_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d28` | `0x00000000` |

---

## MA_STATE_PARITY_CONTROLr

- **Address:** `0x0b180d29`  ·  **Size:** 4 bytes
- **Function:** MA_STATE_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d29` | `0x00000000` |

---

## MA_STATE_PARITY_STATUS_INTRr

- **Address:** `0x0b180d2a`  ·  **Size:** 4 bytes
- **Function:** MA_STATE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d2a` | `0x00000000` |

---

## MA_STATE_PARITY_STATUS_NACKr

- **Address:** `0x0b180d2b`  ·  **Size:** 4 bytes
- **Function:** MA_STATE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d2b` | `0x00000000` |

---

## CCM_READ_CONTROLr

- **Address:** `0x0b180d2c`  ·  **Size:** 4 bytes
- **Function:** No information

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | BITS_TO_CLEAR |
    | `[18:8]` | INDEX |
    | `[19]` | MEMORY |
    | `[20]` | ENABLE_CLEAR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d2c` | `0x00000000` |

---

## CCM_INTERRUPT_CONTROLr

- **Address:** `0x0b180d2d`  ·  **Size:** 4 bytes
- **Function:** No information

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SOME_RMEP_CCM_DEFECT_INT_ENABLE |
    | `[1]` | SOME_RDI_DEFECT_INT_ENABLE |
    | `[2]` | ERROR_CCM_DEFECT_INT_ENABLE |
    | `[3]` | XCON_CCM_DEFECT_INT_ENABLE |
    | `[4]` | ANY_RMEP_TLV_INTERFACE_UP_INT_ENABLE |
    | `[5]` | ANY_RMEP_TLV_INTERFACE_DOWN_INT_ENABLE |
    | `[6]` | ANY_RMEP_TLV_PORT_UP_INT_ENABLE |
    | `[7]` | ANY_RMEP_TLV_PORT_DOWN_INT_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0b180d2d` | `0x00000000` |

---

## STORM_CONTROL_METER_CONFIGr

- **Address:** `0x0c100602`  ·  **Size:** 4 bytes
- **Function:** Per-port configuration and enables for storm control meters

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PACKET_QUANTUM |
    | `[12]` | BYTE_MODE |
    | `[13]` | BCAST_ENABLE |
    | `[14]` | KNOWN_L2MC_ENABLE |
    | `[15]` | UNKNOWN_L2MC_ENABLE |
    | `[16]` | KNOWN_IPMC_ENABLE |
    | `[17]` | UNKNOWN_IPMC_ENABLE |
    | `[18]` | DLFBC_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0c100602` | `0x00001100` |
    | xe0 | `0x0c101602` | `0x00000fa0` |
    | xe1 | `0x0c102602` | `0x00000fa0` |
    | xe2 | `0x0c103602` | `0x00000fa0` |
    | xe3 | `0x0c104602` | `0x00000fa0` |
    | xe4 | `0x0c105602` | `0x00000fa0` |
    | xe5 | `0x0c106602` | `0x00000fa0` |
    | xe6 | `0x0c107602` | `0x00000fa0` |
    | xe7 | `0x0c108602` | `0x00000fa0` |
    | xe8 | `0x0c109602` | `0x00000fa0` |
    | xe9 | `0x0c10a602` | `0x00000fa0` |
    | xe10 | `0x0c10b602` | `0x00000fa0` |
    | xe11 | `0x0c10c602` | `0x00000fa0` |
    | xe12 | `0x0c10d602` | `0x00000fa0` |
    | xe13 | `0x0c10e602` | `0x00000fa0` |
    | xe14 | `0x0c10f602` | `0x00000fa0` |
    | xe15 | `0x0c110602` | `0x00000fa0` |
    | xe16 | `0x0c111602` | `0x00000fa0` |
    | xe17 | `0x0c112602` | `0x00000fa0` |
    | xe18 | `0x0c113602` | `0x00000fa0` |
    | xe19 | `0x0c114602` | `0x00000fa0` |
    | xe20 | `0x0c115602` | `0x00000fa0` |
    | xe21 | `0x0c116602` | `0x00000fa0` |
    | xe22 | `0x0c117602` | `0x00000fa0` |
    | xe23 | `0x0c118602` | `0x00000fa0` |
    | xe24 | `0x0c119602` | `0x00000fa0` |
    | xe25 | `0x0c11a602` | `0x00000fa0` |
    | xe26 | `0x0c11b602` | `0x00000fa0` |
    | xe27 | `0x0c11c602` | `0x00000fa0` |
    | xe28 | `0x0c11d602` | `0x00000fa0` |
    | xe29 | `0x0c11e602` | `0x00000fa0` |
    | xe30 | `0x0c11f602` | `0x00000fa0` |
    | xe31 | `0x0c120602` | `0x00000fa0` |
    | xe32 | `0x0c121602` | `0x00000fa0` |
    | xe33 | `0x0c122602` | `0x00000fa0` |
    | xe34 | `0x0c123602` | `0x00000fa0` |
    | xe35 | `0x0c124602` | `0x00000fa0` |
    | xe36 | `0x0c125602` | `0x00000fa0` |
    | xe37 | `0x0c126602` | `0x00000fa0` |
    | xe38 | `0x0c127602` | `0x00000fa0` |
    | xe39 | `0x0c128602` | `0x00000fa0` |
    | xe40 | `0x0c129602` | `0x00000fa0` |
    | xe41 | `0x0c12a602` | `0x00000fa0` |
    | xe42 | `0x0c12b602` | `0x00000fa0` |
    | xe43 | `0x0c12c602` | `0x00000fa0` |
    | xe44 | `0x0c12d602` | `0x00000fa0` |
    | xe45 | `0x0c12e602` | `0x00000fa0` |
    | xe46 | `0x0c12f602` | `0x00000fa0` |
    | xe47 | `0x0c130602` | `0x00000fa0` |
    | xe48 | `0x0c131602` | `0x00000fa0` |
    | xe49 | `0x0c132602` | `0x00000fa0` |
    | xe50 | `0x0c133602` | `0x00000fa0` |
    | xe51 | `0x0c134602` | `0x00000fa0` |
    | lb0 | `0x0c141602` | `0x00001100` |

---

## FP_METER_CONTROLr

- **Address:** `0x0c10060a`  ·  **Size:** 4 bytes
- **Function:** FP_METER_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PACKET_IFG_BYTES |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0c10060a` | `0x00000000` |
    | xe0 | `0x0c10160a` | `0x00000000` |
    | xe1 | `0x0c10260a` | `0x00000000` |
    | xe2 | `0x0c10360a` | `0x00000000` |
    | xe3 | `0x0c10460a` | `0x00000000` |
    | xe4 | `0x0c10560a` | `0x00000000` |
    | xe5 | `0x0c10660a` | `0x00000000` |
    | xe6 | `0x0c10760a` | `0x00000000` |
    | xe7 | `0x0c10860a` | `0x00000000` |
    | xe8 | `0x0c10960a` | `0x00000000` |
    | xe9 | `0x0c10a60a` | `0x00000000` |
    | xe10 | `0x0c10b60a` | `0x00000000` |
    | xe11 | `0x0c10c60a` | `0x00000000` |
    | xe12 | `0x0c10d60a` | `0x00000000` |
    | xe13 | `0x0c10e60a` | `0x00000000` |
    | xe14 | `0x0c10f60a` | `0x00000000` |
    | xe15 | `0x0c11060a` | `0x00000000` |
    | xe16 | `0x0c11160a` | `0x00000000` |
    | xe17 | `0x0c11260a` | `0x00000000` |
    | xe18 | `0x0c11360a` | `0x00000000` |
    | xe19 | `0x0c11460a` | `0x00000000` |
    | xe20 | `0x0c11560a` | `0x00000000` |
    | xe21 | `0x0c11660a` | `0x00000000` |
    | xe22 | `0x0c11760a` | `0x00000000` |
    | xe23 | `0x0c11860a` | `0x00000000` |
    | xe24 | `0x0c11960a` | `0x00000000` |
    | xe25 | `0x0c11a60a` | `0x00000000` |
    | xe26 | `0x0c11b60a` | `0x00000000` |
    | xe27 | `0x0c11c60a` | `0x00000000` |
    | xe28 | `0x0c11d60a` | `0x00000000` |
    | xe29 | `0x0c11e60a` | `0x00000000` |
    | xe30 | `0x0c11f60a` | `0x00000000` |
    | xe31 | `0x0c12060a` | `0x00000000` |
    | xe32 | `0x0c12160a` | `0x00000000` |
    | xe33 | `0x0c12260a` | `0x00000000` |
    | xe34 | `0x0c12360a` | `0x00000000` |
    | xe35 | `0x0c12460a` | `0x00000000` |
    | xe36 | `0x0c12560a` | `0x00000000` |
    | xe37 | `0x0c12660a` | `0x00000000` |
    | xe38 | `0x0c12760a` | `0x00000000` |
    | xe39 | `0x0c12860a` | `0x00000000` |
    | xe40 | `0x0c12960a` | `0x00000000` |
    | xe41 | `0x0c12a60a` | `0x00000000` |
    | xe42 | `0x0c12b60a` | `0x00000000` |
    | xe43 | `0x0c12c60a` | `0x00000000` |
    | xe44 | `0x0c12d60a` | `0x00000000` |
    | xe45 | `0x0c12e60a` | `0x00000000` |
    | xe46 | `0x0c12f60a` | `0x00000000` |
    | xe47 | `0x0c13060a` | `0x00000000` |
    | xe48 | `0x0c13160a` | `0x00000000` |
    | xe49 | `0x0c13260a` | `0x00000000` |
    | xe50 | `0x0c13360a` | `0x00000000` |
    | xe51 | `0x0c13460a` | `0x00000000` |
    | lb0 | `0x0c14160a` | `0x00000000` |

---

## STORM_CONTROL_METER_MAPPINGr

- **Address:** `0x0c180601`  ·  **Size:** 4 bytes
- **Function:** Storm Meter Controls - each field select one of four storm meters to use for the given packet type.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | BCAST_METER_INDEX |
    | `[3:2]` | KNOWN_L2MC_METER_INDEX |
    | `[5:4]` | UNKNOWN_L2MC_METER_INDEX |
    | `[7:6]` | KNOWN_IPMC_METER_INDEX |
    | `[9:8]` | UNKNOWN_IPMC_METER_INDEX |
    | `[11:10]` | DLFBC_METER_INDEX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180601` | `0x00000e64` |

---

## CPU_CONTROL_1r

- **Address:** `0x0c180603`  ·  **Size:** 4 bytes
- **Function:** Control Register for Packets sent to the CPU

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | STATICMOVE_TOCPU |
    | `[1]` | NONSTATICMOVE_TOCPU |
    | `[2]` | URPF_MISS_TOCPU |
    | `[3]` | UMC_TOCPU |
    | `[4]` | UUCAST_TOCPU |
    | `[5]` | V4L3ERR_TOCPU |
    | `[6]` | IPMCERR_TOCPU |
    | `[7]` | RESERVED_7 |
    | `[8]` | UNRESOLVEDL3SRC_TOCPU |
    | `[9]` | V6L3DSTMISS_TOCPU |
    | `[10]` | V4L3DSTMISS_TOCPU |
    | `[11]` | IPMCPORTMISS_TOCPU |
    | `[12]` | SRCROUTE_TOCPU |
    | `[13]` | V6L3ERR_TOCPU |
    | `[14]` | MARTIAN_ADDR_TOCPU |
    | `[15]` | TUNNEL_ERR_TOCPU |
    | `[16]` | RESERVED_16 |
    | `[17]` | L3UC_TTL_ERR_TOCPU |
    | `[18]` | IPMC_TTL_ERR_TOCPU |
    | `[19]` | RESERVED_19 |
    | `[20]` | L3_SLOWPATH_TOCPU |
    | `[21]` | RESERVED_21 |
    | `[22]` | L3_MTU_FAIL_TOCPU |
    | `[23]` | NIP_L3ERR_TOCPU |
    | `[24]` | MC_INDEX_ERROR_TOCPU |
    | `[25]` | HG_HDR_ERROR_TOCPU |
    | `[26]` | HG_HDR_TYPE1_TOCPU |
    | `[27]` | L3UC_TTL1_ERR_TOCPU |
    | `[28]` | IPMC_TTL1_ERR_TOCPU |
    | `[29]` | CLASS_BASED_SM_PREVENTED_TOCPU |
    | `[30]` | VXLT_MISS_TOCPU |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180603` | `0x18500600` |

---

## CPU_CONTROL_Mr

- **Address:** `0x0c180604`  ·  **Size:** 4 bytes
- **Function:** Control Register for Packets sent to the CPU due to MPLS errors

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MPLS_INVALID_PAYLOAD |
    | `[1]` | MPLS_INVALID_ACTION |
    | `[2]` | MPLS_LABEL_MISS |
    | `[3]` | MPLS_TTL_CHECK_FAIL |
    | `[5:4]` | RESERVED_0 |
    | `[6]` | MAC_BIND_FAIL |
    | `[8:7]` | RESERVED_1 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180604` | `0x00000000` |

---

## ING_MISC_CONFIG2r

- **Address:** `0x0c180606`  ·  **Size:** 4 bytes
- **Function:** Ingress misc config register #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | FP_FIXED_KEY_EXPANSION |
    | `[4]` | FP_KEY_FORCE_VID |
    | `[5]` | DO_NOT_LEARN_DHCP |
    | `[6]` | UNKNOWN_TUNNEL_IPMC_DROP |
    | `[7]` | IPMC_MISS_AS_L2MC |
    | `[8]` | BLOCKED_PORTS_FP_DISABLE |
    | `[9]` | CLASS_BASED_SM_PREVENTED_DROP |
    | `[10]` | IPV6_TO_IPV4_ADDRESS_MAP_ENABLE |
    | `[16:11]` | IPV6_TO_IPV4_MAP_OFFSET_DEFAULT |
    | `[17]` | IPV6_SIP_LINK_LOCAL_DROP |
    | `[18]` | IPV6_SIP_AND_DIP_LINK_LOCAL_DO_NOT_DROP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180606` | `0x00000080` |

---

## FP_SLICE_INDEX_CONTROLr

- **Address:** `0x0c180607`  ·  **Size:** 4 bytes
- **Function:** Selects Index for FP Port Field Select Table, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | SLICE_SELECT_BITMAP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180607` | `0x00000000` |

---

## MC_CONTROL_4r

- **Address:** `0x0c180608`  ·  **Size:** 4 bytes
- **Function:** Multicast Control Register4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | L2MC_MASK_LEN |
    | `[9:5]` | IPMC_MASK_LEN |
    | `[10]` | ALLOW_L2MC_INDEX_WRAP_AROUND |
    | `[11]` | ALLOW_IPMC_INDEX_WRAP_AROUND |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180608` | `0x00000000` |

---

## MC_CONTROL_5r

- **Address:** `0x0c180609`  ·  **Size:** 4 bytes
- **Function:** Multicast Control Register5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | SHARED_TABLE_L2MC_SIZE |
    | `[25:13]` | SHARED_TABLE_IPMC_SIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180609` | `0x02001000` |

---

## CPU_CONTROL_0r

- **Address:** `0x0c18060b`  ·  **Size:** 4 bytes
- **Function:** Control Register for Packets sent to the CPU

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PVLAN_VID_MISMATCH_TOCPU |
    | `[1]` | PARITY_ERR_TOCPU |
    | `[2]` | DOSATTACK_TOCPU |
    | `[3]` | UVLAN_TOCPU |
    | `[4]` | MACSA_ALL_ZERO_DROP |
    | `[5]` | RESERVED_0 |
    | `[6]` | NIV_FORWARDING_DROP_TOCPU |
    | `[7]` | NIV_RPF_CHECK_FAIL_TOCPU |
    | `[8]` | DOT1P_ADMITTANCE_DROP_TOCPU |
    | `[9]` | DISCARD_VNTAG_NOT_PRESENT_TOCPU |
    | `[10]` | DISCARD_VNTAG_PRESENT_TOCPU |
    | `[11]` | VNTAG_FORMAT_DROP_TOCPU |
    | `[12]` | TRILL_OPTIONS_TOCPU |
    | `[13]` | TRILL_RPF_CHECK_FAIL_TOCPU |
    | `[14]` | TRILL_RBRIDGE_LOOKUP_MISS_TOCPU |
    | `[15]` | TRILL_UNEXPECTED_FRAMES_TOCPU |
    | `[16]` | TRILL_ERROR_FRAMES_TOCPU |
    | `[17]` | TRILL_HOPCOUNT_CHECK_FAIL_TOCPU |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c18060b` | `0x00000000` |

---

## PRIORITY_CONTROLr

- **Address:** `0x0c18060c`  ·  **Size:** 4 bytes
- **Function:** Register that controls the generation of various priorities

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | USE_QM_FOR_MH_PRI |
    | `[1]` | USE_SC_FOR_MH_PRI |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c18060c` | `0x00000000` |

---

## PROTOCOL_PKT_CONTROLr

- **Address:** `0x0c180620`  ·  **Size:** 4 bytes
- **Function:** Protocol Packet Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DHCP_PKT_TO_CPU |
    | `[1]` | DHCP_PKT_DROP |
    | `[2]` | ND_PKT_TO_CPU |
    | `[3]` | ND_PKT_DROP |
    | `[4]` | ARP_REQUEST_TO_CPU |
    | `[5]` | ARP_REQUEST_DROP |
    | `[6]` | ARP_REPLY_TO_CPU |
    | `[7]` | ARP_REPLY_DROP |
    | `[8]` | SRP_PKT_TO_CPU |
    | `[10:9]` | SRP_FWD_ACTION |
    | `[11]` | MMRP_PKT_TO_CPU |
    | `[13:12]` | MMRP_FWD_ACTION |

---

## IGMP_MLD_PKT_CONTROLr

- **Address:** `0x0c180660`  ·  **Size:** 4 bytes
- **Function:** IGMP/MLD Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | IPV6_MC_ROUTER_ADV_PKT_TO_CPU |
    | `[2:1]` | IPV6_MC_ROUTER_ADV_PKT_FWD_ACTION |
    | `[3]` | IPV4_MC_ROUTER_ADV_PKT_TO_CPU |
    | `[5:4]` | IPV4_MC_ROUTER_ADV_PKT_FWD_ACTION |
    | `[6]` | IPV6_RESVD_MC_PKT_TO_CPU |
    | `[8:7]` | IPV6_RESVD_MC_PKT_FWD_ACTION |
    | `[9]` | IPV4_RESVD_MC_PKT_TO_CPU |
    | `[11:10]` | IPV4_RESVD_MC_PKT_FWD_ACTION |
    | `[12]` | MLD_QUERY_TO_CPU |
    | `[14:13]` | MLD_QUERY_FWD_ACTION |
    | `[15]` | MLD_REP_DONE_TO_CPU |
    | `[17:16]` | MLD_REP_DONE_FWD_ACTION |
    | `[18]` | IGMP_UNKNOWN_MSG_TO_CPU |
    | `[20:19]` | IGMP_UNKNOWN_MSG_FWD_ACTION |
    | `[21]` | IGMP_QUERY_TO_CPU |
    | `[23:22]` | IGMP_QUERY_FWD_ACTION |
    | `[24]` | IGMP_REP_LEAVE_TO_CPU |
    | `[26:25]` | IGMP_REP_LEAVE_FWD_ACTION |
    | `[27]` | PFM_RULE_APPLY |

---

## TRILL_DROP_CONTROLr

- **Address:** `0x0c1806a0`  ·  **Size:** 4 bytes
- **Function:** .

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | UC_TRILL_HDR_MC_MACDA_DROP |
    | `[1]` | UNKNOWN_INGRESS_RBRIDGE_DROP |
    | `[2]` | TRILL_ADJACENCY_FAIL_DROP |
    | `[3]` | TRILL_HDR_VERSION_NON_ZERO_DROP |
    | `[4]` | RPF_CHECK_FAIL_DROP |
    | `[5]` | INGRESS_RBRIDGE_EQ_EGRESS_RBRIDGE_DROP |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c1806a0` | `0x0000003f` |

---

## SW1_RAM_DBGCTRLr

- **Address:** `0x0c180d00`  ·  **Size:** 4 bytes
- **Function:** SW1_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | DEFIP_TM |
    | `[10]` | DEFIP_DCM |
    | `[20:11]` | L3_HIT_TM |
    | `[21]` | L3_HIT_DCM |
    | `[26:22]` | DSCP_TM |
    | `[31:27]` | ING_PRI_CNG_MAP_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d00` | `0x00000000` |

---

## SW1_RAM_DBGCTRL_2r

- **Address:** `0x0c180d01`  ·  **Size:** 4 bytes
- **Function:** SW1_RAM_CONTROL_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | FP_FIELDSEL_TM |
    | `[10]` | FP_FIELDSEL_DCM |
    | `[11]` | DEFIP_PM |
    | `[12]` | L3_HIT_PM |
    | `[13]` | DSCP_PM |
    | `[14]` | ING_PRI_CNG_MAP_PM |
    | `[15]` | FP_FIELDSEL_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d01` | `0x00000000` |

---

## FP_FIELD_SEL_PARITY_CONTROLr

- **Address:** `0x0c180d02`  ·  **Size:** 4 bytes
- **Function:** FP_FIELD_SEL_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d02` | `0x00000001` |

---

## FP_FIELD_SEL_PARITY_STATUS_INTRr

- **Address:** `0x0c180d03`  ·  **Size:** 4 bytes
- **Function:** FP_FIELD_SEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d03` | `0x00000000` |

---

## FP_FIELD_SEL_PARITY_STATUS_NACKr

- **Address:** `0x0c180d04`  ·  **Size:** 4 bytes
- **Function:** FP_FIELD_SEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d04` | `0x00000000` |

---

## TTL_FN_PARITY_CONTROLr

- **Address:** `0x0c180d05`  ·  **Size:** 4 bytes
- **Function:** TTL_FN_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d05` | `0x00000001` |

---

## TTL_FN_PARITY_STATUS_INTRr

- **Address:** `0x0c180d06`  ·  **Size:** 4 bytes
- **Function:** TTL_FN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d06` | `0x00000000` |

---

## TTL_FN_PARITY_STATUS_NACKr

- **Address:** `0x0c180d07`  ·  **Size:** 4 bytes
- **Function:** TTL_FN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d07` | `0x00000000` |

---

## TOS_FN_PARITY_CONTROLr

- **Address:** `0x0c180d08`  ·  **Size:** 4 bytes
- **Function:** TOS_FN_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d08` | `0x00000001` |

---

## TOS_FN_PARITY_STATUS_INTRr

- **Address:** `0x0c180d09`  ·  **Size:** 4 bytes
- **Function:** TOS_FN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d09` | `0x00000000` |

---

## TOS_FN_PARITY_STATUS_NACKr

- **Address:** `0x0c180d0a`  ·  **Size:** 4 bytes
- **Function:** TOS_FN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0a` | `0x00000000` |

---

## ING_PRI_CNG_MAP_PARITY_CONTROLr

- **Address:** `0x0c180d0b`  ·  **Size:** 4 bytes
- **Function:** ING_PRI_CNG_MAP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0b` | `0x00000001` |

---

## ING_PRI_CNG_MAP_PARITY_STATUS_INTRr

- **Address:** `0x0c180d0c`  ·  **Size:** 4 bytes
- **Function:** ING_PRI_CNG_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0c` | `0x00000000` |

---

## ING_PRI_CNG_MAP_PARITY_STATUS_NACKr

- **Address:** `0x0c180d0d`  ·  **Size:** 4 bytes
- **Function:** ING_PRI_CNG_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0d` | `0x00000000` |

---

## ING_UNTAGGED_PHB_PARITY_CONTROLr

- **Address:** `0x0c180d0e`  ·  **Size:** 4 bytes
- **Function:** ING_UNTAGGED_PHB_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0e` | `0x00000001` |

---

## ING_UNTAGGED_PHB_PARITY_STATUS_INTRr

- **Address:** `0x0c180d0f`  ·  **Size:** 4 bytes
- **Function:** ING_UNTAGGED_PHB_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[7:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d0f` | `0x00000000` |

---

## ING_UNTAGGED_PHB_PARITY_STATUS_NACKr

- **Address:** `0x0c180d10`  ·  **Size:** 4 bytes
- **Function:** ING_UNTAGGED_PHB_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[7:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d10` | `0x00000000` |

---

## DSCP_TABLE_PARITY_CONTROLr

- **Address:** `0x0c180d11`  ·  **Size:** 4 bytes
- **Function:** DSCP_TABLE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d11` | `0x00000001` |

---

## DSCP_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0c180d12`  ·  **Size:** 4 bytes
- **Function:** DSCP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d12` | `0x00000000` |

---

## DSCP_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0c180d13`  ·  **Size:** 4 bytes
- **Function:** DSCP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0c180d13` | `0x00000000` |

---

## IFP_GM_LOGIC_TO_PHYS_MAPr

- **Address:** `0x0d100605`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PHYSICAL_PORT_NUM |
    | `[6:0]` | PHYS_PORT |

---

## FP_SLICE_ENABLEr

- **Address:** `0x0d180601`  ·  **Size:** 4 bytes
- **Function:** FP_SLICE_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | FP_SLICE_ENABLE_SLICE_0 |
    | `[1]` | FP_SLICE_ENABLE_SLICE_1 |
    | `[2]` | FP_SLICE_ENABLE_SLICE_2 |
    | `[3]` | FP_SLICE_ENABLE_SLICE_3 |
    | `[4]` | FP_SLICE_ENABLE_SLICE_4 |
    | `[5]` | FP_SLICE_ENABLE_SLICE_5 |
    | `[6]` | FP_SLICE_ENABLE_SLICE_6 |
    | `[7]` | FP_SLICE_ENABLE_SLICE_7 |
    | `[8]` | FP_SLICE_ENABLE_SLICE_8 |
    | `[9]` | FP_SLICE_ENABLE_SLICE_9 |
    | `[10]` | FP_LOOKUP_ENABLE_SLICE_0 |
    | `[11]` | FP_LOOKUP_ENABLE_SLICE_1 |
    | `[12]` | FP_LOOKUP_ENABLE_SLICE_2 |
    | `[13]` | FP_LOOKUP_ENABLE_SLICE_3 |
    | `[14]` | FP_LOOKUP_ENABLE_SLICE_4 |
    | `[15]` | FP_LOOKUP_ENABLE_SLICE_5 |
    | `[16]` | FP_LOOKUP_ENABLE_SLICE_6 |
    | `[17]` | FP_LOOKUP_ENABLE_SLICE_7 |
    | `[18]` | FP_LOOKUP_ENABLE_SLICE_8 |
    | `[19]` | FP_LOOKUP_ENABLE_SLICE_9 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180601` | `0x000e33ff` |

---

## FP_SLICE_METER_MAP_ENABLEr

- **Address:** `0x0d180603`  ·  **Size:** 4 bytes
- **Function:** FP_SLICE_METER_MAP_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SLICE_0_ENABLE |
    | `[1]` | SLICE_1_ENABLE |
    | `[2]` | SLICE_2_ENABLE |
    | `[3]` | SLICE_3_ENABLE |
    | `[4]` | SLICE_4_ENABLE |
    | `[5]` | SLICE_5_ENABLE |
    | `[6]` | SLICE_6_ENABLE |
    | `[7]` | SLICE_7_ENABLE |
    | `[8]` | SLICE_8_ENABLE |
    | `[9]` | SLICE_9_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180603` | `0x00000000` |

---

## FP_FORCE_FORWARDING_FIELDr

- **Address:** `0x0d180604`  ·  **Size:** 4 bytes
- **Function:** FP_FORCE_FORWARDING_FIELD

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SLICE_0_ENABLE |
    | `[1]` | SLICE_1_ENABLE |
    | `[2]` | SLICE_2_ENABLE |
    | `[3]` | SLICE_3_ENABLE |
    | `[4]` | SLICE_4_ENABLE |
    | `[5]` | SLICE_5_ENABLE |
    | `[6]` | SLICE_6_ENABLE |
    | `[7]` | SLICE_7_ENABLE |
    | `[8]` | SLICE_8_ENABLE |
    | `[9]` | SLICE_9_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180604` | `0x00000000` |

---

## FP_CAM_BIST_STATUSr

- **Address:** `0x0d180d00`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d00` | `0x00000000` |

---

## FP_CAM_DEBUG_CONTROLr

- **Address:** `0x0d180d01`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_DEBUG_CONTROL, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CAM_BIST_STATUS_DATA_SEL_ |
    | `[15:8]` | FP_CAM_BIST_SKIP_COUNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d01` | `0x00000000` |

---

## FP_CAM_CONTROL_SLICE_3_0r

- **Address:** `0x0d180d02`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_CONTROL_SLICE_3_0, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d02` | `0x00000000` |

---

## FP_CAM_CONTROL_SLICE_9_4r

- **Address:** `0x0d180d03`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_CONTROL_SLICE_9_4, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d03` | `0x00000000` |

---

## FP_CAM_DEBUG_DATAr

- **Address:** `0x0d180d04`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_DEBUG_DATA, FeatureSpecific-FP

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## FP_GLOBAL_MASK_CAM_CONTROL_SLICE_3_0r

- **Address:** `0x0d180d05`  ·  **Size:** 4 bytes
- **Function:** FP_GLOBAL_MASK_CAM_CONTROL_SLICE_3_0, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d05` | `0x00000000` |

---

## FP_GLOBAL_MASK_CAM_CONTROL_SLICE_9_4r

- **Address:** `0x0d180d06`  ·  **Size:** 4 bytes
- **Function:** FP_GLOBAL_MASK_CAM_CONTROL_SLICE_9_4, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d06` | `0x00000000` |

---

## FP_CAM_DEBUG_SENDr

- **Address:** `0x0d180d07`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_DEBUG_SEND

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LOAD_DATA |

---

## FP_CAM_BIST_ENABLE_LOWERr

- **Address:** `0x0d180d08`  ·  **Size:** 4 bytes
- **Function:** FP_CAM_BIST_ENABLE_LOWER

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | FP_CAM_BIST_ENABLE_SLICE_0_LOWER |
    | `[1]` | FP_CAM_BIST_ENABLE_SLICE_1_LOWER |
    | `[2]` | FP_CAM_BIST_ENABLE_SLICE_2_LOWER |
    | `[3]` | FP_CAM_BIST_ENABLE_SLICE_3_LOWER |
    | `[4]` | FP_CAM_BIST_ENABLE_SLICE_4_LOWER |
    | `[5]` | FP_CAM_BIST_ENABLE_SLICE_5_LOWER |
    | `[6]` | FP_CAM_BIST_ENABLE_SLICE_6_LOWER |
    | `[7]` | FP_CAM_BIST_ENABLE_SLICE_7_LOWER |
    | `[8]` | FP_CAM_BIST_ENABLE_SLICE_8_LOWER |
    | `[9]` | FP_CAM_BIST_ENABLE_SLICE_9_LOWER |
    | `[10]` | FP_CAM_DEBUG_ENABLE_SLICE_0_LOWER |
    | `[11]` | FP_CAM_DEBUG_ENABLE_SLICE_1_LOWER |
    | `[12]` | FP_CAM_DEBUG_ENABLE_SLICE_2_LOWER |
    | `[13]` | FP_CAM_DEBUG_ENABLE_SLICE_3_LOWER |
    | `[14]` | FP_CAM_DEBUG_ENABLE_SLICE_4_LOWER |
    | `[15]` | FP_CAM_DEBUG_ENABLE_SLICE_5_LOWER |
    | `[16]` | FP_CAM_DEBUG_ENABLE_SLICE_6_LOWER |
    | `[17]` | FP_CAM_DEBUG_ENABLE_SLICE_7_LOWER |
    | `[18]` | FP_CAM_DEBUG_ENABLE_SLICE_8_LOWER |
    | `[19]` | FP_CAM_DEBUG_ENABLE_SLICE_9_LOWER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d08` | `0x00000000` |

---

## FP_POLICY_TM_UPPERr

- **Address:** `0x0d180d09`  ·  **Size:** 4 bytes
- **Function:** FP_POLICY_TM_UPPER

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SLICE_6_TM |
    | `[9:5]` | SLICE_7_TM |
    | `[14:10]` | SLICE_8_TM |
    | `[19:15]` | SLICE_9_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d09` | `0x00000000` |

---

## FP_POLICY_TM_LOWERr

- **Address:** `0x0d180d0a`  ·  **Size:** 4 bytes
- **Function:** FP_POLICY_TM_LOWER

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SLICE_0_TM |
    | `[9:5]` | SLICE_1_TM |
    | `[14:10]` | SLICE_2_TM |
    | `[19:15]` | SLICE_3_TM |
    | `[24:20]` | SLICE_4_TM |
    | `[29:25]` | SLICE_5_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0a` | `0x00000000` |

---

## FP_POLICY_PMr

- **Address:** `0x0d180d0b`  ·  **Size:** 4 bytes
- **Function:** FP_POLICY_PM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SLICE_0_PM |
    | `[1]` | SLICE_1_PM |
    | `[2]` | SLICE_2_PM |
    | `[3]` | SLICE_3_PM |
    | `[4]` | SLICE_4_PM |
    | `[5]` | SLICE_5_PM |
    | `[6]` | SLICE_6_PM |
    | `[7]` | SLICE_7_PM |
    | `[8]` | SLICE_8_PM |
    | `[9]` | SLICE_9_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0b` | `0x00000000` |

---

## IFP_POLICY_PARITY_CONTROLr

- **Address:** `0x0d180d0c`  ·  **Size:** 4 bytes
- **Function:** IFP_POLICY_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0c` | `0x00000001` |

---

## IFP_POLICY_PARITY_STATUS_INTRr

- **Address:** `0x0d180d0d`  ·  **Size:** 4 bytes
- **Function:** IFP_POLICY_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0d` | `0x00000000` |

---

## IFP_POLICY_PARITY_STATUS_NACKr

- **Address:** `0x0d180d0e`  ·  **Size:** 4 bytes
- **Function:** IFP_POLICY_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0e` | `0x00000000` |

---

## IFP_METER_PARITY_CONTROLr

- **Address:** `0x0d180d0f`  ·  **Size:** 4 bytes
- **Function:** IFP_METER_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d0f` | `0x00000000` |

---

## IFP_METER_PARITY_STATUS_INTRr

- **Address:** `0x0d180d10`  ·  **Size:** 4 bytes
- **Function:** IFP_METER_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d10` | `0x00000000` |

---

## IFP_METER_PARITY_STATUS_NACKr

- **Address:** `0x0d180d11`  ·  **Size:** 4 bytes
- **Function:** IFP_METER_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d11` | `0x00000000` |

---

## IFP_COUNTER_PARITY_CONTROLr

- **Address:** `0x0d180d12`  ·  **Size:** 4 bytes
- **Function:** IFP_COUNTER_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d12` | `0x00000001` |

---

## IFP_COUNTER_PARITY_STATUS_INTRr

- **Address:** `0x0d180d13`  ·  **Size:** 4 bytes
- **Function:** IFP_COUNTER_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d13` | `0x00000000` |

---

## IFP_COUNTER_PARITY_STATUS_NACKr

- **Address:** `0x0d180d14`  ·  **Size:** 4 bytes
- **Function:** IFP_COUNTER_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d14` | `0x00000000` |

---

## IFP_STORM_CONTROL_PARITY_CONTROLr

- **Address:** `0x0d180d15`  ·  **Size:** 4 bytes
- **Function:** IFP_STORM_CONTROL_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d15` | `0x00000001` |

---

## IFP_STORM_CONTROL_PARITY_STATUS_INTRr

- **Address:** `0x0d180d16`  ·  **Size:** 4 bytes
- **Function:** IFP_STORM_CONTROL_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d16` | `0x00000000` |

---

## IFP_STORM_CONTROL_PARITY_STATUS_NACKr

- **Address:** `0x0d180d17`  ·  **Size:** 4 bytes
- **Function:** IFP_STORM_CONTROL_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[10:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d17` | `0x00000000` |

---

## IFP_ING_DVP_2_CONTROLr

- **Address:** `0x0d180d18`  ·  **Size:** 4 bytes
- **Function:** IFP_ING_DVP_2_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | TM |
    | `[5]` | PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d18` | `0x00000000` |

---

## IFP_ING_DVP_2_PARITY_CONTROLr

- **Address:** `0x0d180d19`  ·  **Size:** 4 bytes
- **Function:** IFP_ING_DVP_2_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d19` | `0x00000001` |

---

## IFP_ING_DVP_2_PARITY_STATUS_INTRr

- **Address:** `0x0d180d1a`  ·  **Size:** 4 bytes
- **Function:** IFP_ING_DVP_2_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1a` | `0x00000000` |

---

## IFP_ING_DVP_2_PARITY_STATUS_NACKr

- **Address:** `0x0d180d1b`  ·  **Size:** 4 bytes
- **Function:** IFP_ING_DVP_2_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1b` | `0x00000000` |

---

## IFP_METER_MUX_DATA_STAGING_PARITY_CONTROLr

- **Address:** `0x0d180d1c`  ·  **Size:** 4 bytes
- **Function:** IFP_METER_MUX_DATA_STAGING_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1c` | `0x00000001` |

---

## IFP_METER_MUX_DATA_STAGING_PARITY_STATUS_INTRr

- **Address:** `0x0d180d1d`  ·  **Size:** 4 bytes
- **Function:** IFP_METER_MUX_DATA_STAGING_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1d` | `0x00000000` |

---

## IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROLr

- **Address:** `0x0d180d1e`  ·  **Size:** 4 bytes
- **Function:** IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1e` | `0x00000001` |

---

## IFP_COUNTER_MUX_DATA_STAGING_PARITY_STATUS_INTRr

- **Address:** `0x0d180d1f`  ·  **Size:** 4 bytes
- **Function:** IFP_COUNTER_MUX_DATA_STAGING_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[7:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d1f` | `0x00000000` |

---

## FP_TCAM_BLK_SELr

- **Address:** `0x0d180d20`  ·  **Size:** 4 bytes
- **Function:** FP_TCAM_BLK_SEL, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SLICE_4 |
    | `[3:2]` | SLICE_5 |
    | `[5:4]` | SLICE_6 |
    | `[7:6]` | SLICE_7 |
    | `[9:8]` | SLICE_8 |
    | `[11:10]` | SLICE_9 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d20` | `0x00000fff` |

---

## FP_GM_TCAM_BLK_SELr

- **Address:** `0x0d180d21`  ·  **Size:** 4 bytes
- **Function:** FP_GM_TCAM_BLK_SEL, FeatureSpecific-FP

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SLICE_4 |
    | `[3:2]` | SLICE_5 |
    | `[5:4]` | SLICE_6 |
    | `[7:6]` | SLICE_7 |
    | `[9:8]` | SLICE_8 |
    | `[11:10]` | SLICE_9 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d21` | `0x00000fff` |

---

## IP4_INTR_STATUSr

- **Address:** `0x0d180d22`  ·  **Size:** 4 bytes
- **Function:** IP4 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | IFP_POLICY_PAR_ERR |
    | `[1]` | IFP_STORM_CONTROL_PAR_ERR |
    | `[2]` | IFP_COUNTER_PAR_ERR |
    | `[3]` | IFP_METER_PAR_ERR |
    | `[4]` | IFP_ING_DVP_2_PAR_ERR |
    | `[5]` | IFP_METER_MUX_DATA_STAGING_PAR_ERR |
    | `[6]` | IFP_COUNTER_MUX_DATA_STAGING_PAR_ERR |
    | `[7]` | IRSEL2_EGR_MASK_MODBASE_PAR_ERR |
    | `[8]` | IRSEL2_ICONTROL_OPCODE_BITMAP_PAR_ERR |
    | `[9]` | IRSEL2_IFP_REDIRECTION_PROFILE_PAR_ERR |
    | `[10]` | IRSEL2_ING_L3_NEXT_HOP_PAR_ERR |
    | `[11]` | IRSEL2_L2MC_PAR_ERR |
    | `[12]` | IRSEL2_L3_ECMP_GROUP_PAR_ERR |
    | `[13]` | IRSEL2_L3_ECMP_PAR_ERR |
    | `[14]` | IRSEL2_L3_IPMC_PAR_ERR |
    | `[15]` | IRSEL2_L3_IPMC_REMAP_PAR_ERR |
    | `[16]` | IRSEL2_TRUNK_GROUP_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d22` | `0x00000000` |

---

## IP4_INTR_ENABLEr

- **Address:** `0x0d180d23`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP4_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | IFP_POLICY_PAR_ERR |
    | `[1]` | IFP_STORM_CONTROL_PAR_ERR |
    | `[2]` | IFP_COUNTER_PAR_ERR |
    | `[3]` | IFP_METER_PAR_ERR |
    | `[4]` | IFP_ING_DVP_2_PAR_ERR |
    | `[5]` | IFP_METER_MUX_DATA_STAGING_PAR_ERR |
    | `[6]` | IFP_COUNTER_MUX_DATA_STAGING_PAR_ERR |
    | `[7]` | IRSEL2_EGR_MASK_MODBASE_PAR_ERR |
    | `[8]` | IRSEL2_ICONTROL_OPCODE_BITMAP_PAR_ERR |
    | `[9]` | IRSEL2_IFP_REDIRECTION_PROFILE_PAR_ERR |
    | `[10]` | IRSEL2_ING_L3_NEXT_HOP_PAR_ERR |
    | `[11]` | IRSEL2_L2MC_PAR_ERR |
    | `[12]` | IRSEL2_L3_ECMP_GROUP_PAR_ERR |
    | `[13]` | IRSEL2_L3_ECMP_PAR_ERR |
    | `[14]` | IRSEL2_L3_IPMC_PAR_ERR |
    | `[15]` | IRSEL2_L3_IPMC_REMAP_PAR_ERR |
    | `[16]` | IRSEL2_TRUNK_GROUP_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d23` | `0x0001ff97` |

---

## IFP_PWR_WATCH_DOG_CONTROLr

- **Address:** `0x0d180d24`  ·  **Size:** 4 bytes
- **Function:** Power watch dog control register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[8:1]` | CGFC |
    | `[11:9]` | RSEL |
    | `[14:12]` | CLEARCFG |
    | `[20:15]` | START |
    | `[31:21]` | RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d24` | `0x00000000` |

---

## IFP_PWR_WATCH_DOG_STATUSr

- **Address:** `0x0d180d25`  ·  **Size:** 4 bytes
- **Function:** Power watch dog status register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | GOOD_COUNT |
    | `[31]` | GOOD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d25` | `0x80000000` |

---

## FP_METER_TABLE_TMr

- **Address:** `0x0d180d26`  ·  **Size:** 4 bytes
- **Function:** FP_METER_TABLE_TM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | POOL_0 |
    | `[3:2]` | POOL_1 |
    | `[5:4]` | POOL_2 |
    | `[7:6]` | POOL_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0d180d26` | `0x00000000` |

---

## FP_ECMP_HASH_CONTROLr

- **Address:** `0x0e180600`  ·  **Size:** 4 bytes
- **Function:** Hash Key controls for when FP iniates and ECMP Route

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | ECMP_HASH_SALT |
    | `[8]` | USE_CRC |
    | `[9]` | USE_UPPER |
    | `[10]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180600` | `0x00000000` |

---

## RTAG7_HASH_TRUNKr

- **Address:** `0x0e180610`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for trunking

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL_UC |
    | `[6:3]` | OFFSET_UC |
    | `[9:7]` | SUB_SEL_NONUC |
    | `[13:10]` | OFFSET_NONUC |

---

## RSEL2_RAM_DBGCTRLr

- **Address:** `0x0e180d00`  ·  **Size:** 4 bytes
- **Function:** RSEL2_RAM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | L3_ECMP_TM |
    | `[9:5]` | L3_ECMP_GROUP_DST_TM |
    | `[14:10]` | L3_ECMP_GROUP_SRC_TM |
    | `[24:15]` | IFP_REDIRECTION_PROFILE_TM |
    | `[26:25]` | ICONTROL_OPCODE_BITMAP_TM |
    | `[31:27]` | L3_IPMC_REMAP_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d00` | `0x00000000` |

---

## RSEL2_RAM_CONTROL_2r

- **Address:** `0x0e180d01`  ·  **Size:** 4 bytes
- **Function:** RSEL2_RAM_CONTROL_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | L2MC_TM |
    | `[19:10]` | L3_IPMC_TM |
    | `[20]` | L2MC_PM |
    | `[21]` | L3_IPMC_PM |
    | `[22]` | L2MC_DCM |
    | `[23]` | L3_IPMC_DCM |
    | `[24]` | L3_IPMC_REMAP_PM |
    | `[25]` | L3_ECMP_PM |
    | `[26]` | L3_ECMP_GROUP_DST_PM |
    | `[27]` | L3_ECMP_GROUP_SRC_PM |
    | `[31:28]` | RESERVED_RSEL2_RAM_CONTROL_2 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d01` | `0x00000000` |

---

## RSEL2_RAM_CONTROL_3r

- **Address:** `0x0e180d02`  ·  **Size:** 4 bytes
- **Function:** RSEL2_RAM_CONTROL_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | EGR_MASK_MODBASE_TM |
    | `[12:8]` | TRUNK_GROUP_TM |
    | `[22:13]` | ING_L3_NEXT_HOP_TM |
    | `[23]` | IFP_REDIRECTION_PROFILE_DCM |
    | `[24]` | IFP_REDIRECTION_PROFILE_PM |
    | `[25]` | ING_L3_NEXT_HOP_DCM |
    | `[26]` | ING_L3_NEXT_HOP_PM |
    | `[27]` | TRUNK_GROUP_PM |
    | `[31:28]` | RESERVED_RSEL2_RAM_CONTROL_3 |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d02` | `0x00000000` |

---

## ING_L3_NEXT_HOP_PARITY_CONTROLr

- **Address:** `0x0e180d03`  ·  **Size:** 4 bytes
- **Function:** ING_L3_NEXT_HOP_PARITY_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d03` | `0x00000001` |

---

## ING_L3_NEXT_HOP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d04`  ·  **Size:** 4 bytes
- **Function:** ING_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d04` | `0x00000000` |

---

## ING_L3_NEXT_HOP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d05`  ·  **Size:** 4 bytes
- **Function:** ING_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d05` | `0x00000000` |

---

## L2MC_PARITY_CONTROLr

- **Address:** `0x0e180d06`  ·  **Size:** 4 bytes
- **Function:** L2MC_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d06` | `0x00000001` |

---

## L2MC_PARITY_STATUS_INTRr

- **Address:** `0x0e180d07`  ·  **Size:** 4 bytes
- **Function:** L2MC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d07` | `0x00000000` |

---

## L2MC_PARITY_STATUS_NACKr

- **Address:** `0x0e180d08`  ·  **Size:** 4 bytes
- **Function:** L2MC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d08` | `0x00000000` |

---

## L3_IPMC_PARITY_CONTROLr

- **Address:** `0x0e180d09`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: L3MC_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d09` | `0x00000001` |

---

## L3_IPMC_PARITY_STATUS_INTRr

- **Address:** `0x0e180d0a`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: L3_IPMC_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0a` | `0x00000000` |

---

## L3_IPMC_PARITY_STATUS_NACKr

- **Address:** `0x0e180d0b`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: L3_IPMC_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0b` | `0x00000000` |

---

## L3_IPMC_REMAP_PARITY_CONTROLr

- **Address:** `0x0e180d0c`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_REMAP_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: L3_IPMC_REMAP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0c` | `0x00000001` |

---

## L3_IPMC_REMAP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d0d`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_REMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: L3_IPMC_REMAP_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0d` | `0x00000000` |

---

## L3_IPMC_REMAP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d0e`  ·  **Size:** 4 bytes
- **Function:** L3_IPMC_REMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: L3_IPMC_REMAP_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0e` | `0x00000000` |

---

## L3_ECMP_GROUP_PARITY_CONTROLr

- **Address:** `0x0e180d0f`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: L3_ECMP_GROUP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d0f` | `0x00000001` |

---

## L3_ECMP_GROUP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d10`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: L3_ECMP_GROUP_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d10` | `0x00000000` |

---

## L3_ECMP_GROUP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d11`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: L3_ECMP_GROUP_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d11` | `0x00000000` |

---

## L3_ECMP_PARITY_CONTROLr

- **Address:** `0x0e180d12`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: L3_ECMP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d12` | `0x00000001` |

---

## L3_ECMP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d13`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: L3_ECMP_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d13` | `0x00000000` |

---

## L3_ECMP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d14`  ·  **Size:** 4 bytes
- **Function:** L3_ECMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: L3_ECMP_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d14` | `0x00000000` |

---

## IFP_REDIRECTION_PROFILE_PARITY_CONTROLr

- **Address:** `0x0e180d15`  ·  **Size:** 4 bytes
- **Function:** IFP_REDIRECTION_PROFILE_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: IFP_REDIRECTION_PROFILE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d15` | `0x00000001` |

---

## IFP_REDIRECTION_PROFILE_PARITY_STATUS_INTRr

- **Address:** `0x0e180d16`  ·  **Size:** 4 bytes
- **Function:** IFP_REDIRECTION_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: IFP_REDIRECTION_PROFILE_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d16` | `0x00000000` |

---

## IFP_REDIRECTION_PROFILE_PARITY_STATUS_NACKr

- **Address:** `0x0e180d17`  ·  **Size:** 4 bytes
- **Function:** IFP_REDIRECTION_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: IFP_REDIRECTION_PROFILE_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d17` | `0x00000000` |

---

## ICONTROL_OPCODE_BITMAP_PARITY_CONTROLr

- **Address:** `0x0e180d18`  ·  **Size:** 4 bytes
- **Function:** ICONTROL_OPCODE_BITMAP_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: ICONTROL_OPCODE_BITMAP_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d18` | `0x00000001` |

---

## ICONTROL_OPCODE_BITMAP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d19`  ·  **Size:** 4 bytes
- **Function:** ICONTROL_OPCODE_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: ICONTROL_OPCODE_BITMAP_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d19` | `0x00000000` |

---

## ICONTROL_OPCODE_BITMAP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d1a`  ·  **Size:** 4 bytes
- **Function:** ICONTROL_OPCODE_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: ICONTROL_OPCODE_BITMAP_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1a` | `0x00000000` |

---

## EGR_MASK_MODBASE_PARITY_CONTROLr

- **Address:** `0x0e180d1b`  ·  **Size:** 4 bytes
- **Function:** EGR_MASK_MODBASE_PARITY_CONTROL, FeatureSpecific-Ethernet\nHW: EGR_MASK_MODBASE_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1b` | `0x00000001` |

---

## EGR_MASK_MODBASE_PARITY_STATUS_INTRr

- **Address:** `0x0e180d1c`  ·  **Size:** 4 bytes
- **Function:** EGR_MASK_MODBASE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet\nHW: EGR_MASK_MODBASE_PARITY_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1c` | `0x00000000` |

---

## EGR_MASK_MODBASE_PARITY_STATUS_NACKr

- **Address:** `0x0e180d1d`  ·  **Size:** 4 bytes
- **Function:** EGR_MASK_MODBASE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet\nHW: EGR_MASK_MODBASE_PARITY_STATUS_NACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1d` | `0x00000000` |

---

## TRUNK_GROUP_PARITY_CONTROLr

- **Address:** `0x0e180d1e`  ·  **Size:** 4 bytes
- **Function:** Parity Control for TRUNK_GROUP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1e` | `0x00000001` |

---

## TRUNK_GROUP_PARITY_STATUS_INTRr

- **Address:** `0x0e180d1f`  ·  **Size:** 4 bytes
- **Function:** TRUNK_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d1f` | `0x00000000` |

---

## TRUNK_GROUP_PARITY_STATUS_NACKr

- **Address:** `0x0e180d20`  ·  **Size:** 4 bytes
- **Function:** TRUNK_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0e180d20` | `0x00000000` |

---

## RIPD4r

- **Address:** `0x0f100000`  ·  **Size:** 4 bytes
- **Function:** Receive IPv4 L3 Discard Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100000` | `0x00000000` |
    | xe0 | `0x0f101000` | `0x00000000` |
    | xe1 | `0x0f102000` | `0x00000000` |
    | xe2 | `0x0f103000` | `0x00000000` |
    | xe3 | `0x0f104000` | `0x00000000` |
    | xe4 | `0x0f105000` | `0x00000000` |
    | xe5 | `0x0f106000` | `0x00000000` |
    | xe6 | `0x0f107000` | `0x00000000` |
    | xe7 | `0x0f108000` | `0x00000000` |
    | xe8 | `0x0f109000` | `0x00000000` |
    | xe9 | `0x0f10a000` | `0x00000000` |
    | xe10 | `0x0f10b000` | `0x00000000` |
    | xe11 | `0x0f10c000` | `0x00000000` |
    | xe12 | `0x0f10d000` | `0x00000000` |
    | xe13 | `0x0f10e000` | `0x00000000` |
    | xe14 | `0x0f10f000` | `0x00000000` |
    | xe15 | `0x0f110000` | `0x00000000` |
    | xe16 | `0x0f111000` | `0x00000000` |
    | xe17 | `0x0f112000` | `0x00000000` |
    | xe18 | `0x0f113000` | `0x00000000` |
    | xe19 | `0x0f114000` | `0x00000000` |
    | xe20 | `0x0f115000` | `0x00000000` |
    | xe21 | `0x0f116000` | `0x00000000` |
    | xe22 | `0x0f117000` | `0x00000000` |
    | xe23 | `0x0f118000` | `0x00000000` |
    | xe24 | `0x0f119000` | `0x00000000` |
    | xe25 | `0x0f11a000` | `0x00000000` |
    | xe26 | `0x0f11b000` | `0x00000000` |
    | xe27 | `0x0f11c000` | `0x00000000` |
    | xe28 | `0x0f11d000` | `0x00000000` |
    | xe29 | `0x0f11e000` | `0x00000000` |
    | xe30 | `0x0f11f000` | `0x00000000` |
    | xe31 | `0x0f120000` | `0x00000000` |
    | xe32 | `0x0f121000` | `0x00000000` |
    | xe33 | `0x0f122000` | `0x00000000` |
    | xe34 | `0x0f123000` | `0x00000000` |
    | xe35 | `0x0f124000` | `0x00000000` |
    | xe36 | `0x0f125000` | `0x00000000` |
    | xe37 | `0x0f126000` | `0x00000000` |
    | xe38 | `0x0f127000` | `0x00000000` |
    | xe39 | `0x0f128000` | `0x00000000` |
    | xe40 | `0x0f129000` | `0x00000000` |
    | xe41 | `0x0f12a000` | `0x00000000` |
    | xe42 | `0x0f12b000` | `0x00000000` |
    | xe43 | `0x0f12c000` | `0x00000000` |
    | xe44 | `0x0f12d000` | `0x00000000` |
    | xe45 | `0x0f12e000` | `0x00000000` |
    | xe46 | `0x0f12f000` | `0x00000000` |
    | xe47 | `0x0f130000` | `0x00000000` |
    | xe48 | `0x0f131000` | `0x00000000` |
    | xe49 | `0x0f132000` | `0x00000000` |
    | xe50 | `0x0f133000` | `0x00000000` |
    | xe51 | `0x0f134000` | `0x00000000` |
    | lb0 | `0x0f141000` | `0x00000000` |

---

## RIPC4r

- **Address:** `0x0f100001`  ·  **Size:** 4 bytes
- **Function:** Receive IPv4 L3 Unicast Frame Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100001` | `0x00000000` |
    | xe0 | `0x0f101001` | `0x04000121` |
    | xe1 | `0x0f102001` | `0x00001bd7` |
    | xe2 | `0x0f103001` | `0x00000000` |
    | xe3 | `0x0f104001` | `0x00000000` |
    | xe4 | `0x0f105001` | `0x00000000` |
    | xe5 | `0x0f106001` | `0x00000000` |
    | xe6 | `0x0f107001` | `0x00000000` |
    | xe7 | `0x0f108001` | `0x00000000` |
    | xe8 | `0x0f109001` | `0x00000000` |
    | xe9 | `0x0f10a001` | `0x00000000` |
    | xe10 | `0x0f10b001` | `0x00000000` |
    | xe11 | `0x0f10c001` | `0x00000000` |
    | xe12 | `0x0f10d001` | `0x00000000` |
    | xe13 | `0x0f10e001` | `0x00000000` |
    | xe14 | `0x0f10f001` | `0x00000000` |
    | xe15 | `0x0f110001` | `0x00000000` |
    | xe16 | `0x0f111001` | `0x00000000` |
    | xe17 | `0x0f112001` | `0x00000000` |
    | xe18 | `0x0f113001` | `0x00000000` |
    | xe19 | `0x0f114001` | `0x00000000` |
    | xe20 | `0x0f115001` | `0x00000000` |
    | xe21 | `0x0f116001` | `0x00000000` |
    | xe22 | `0x0f117001` | `0x00000000` |
    | xe23 | `0x0f118001` | `0x00000000` |
    | xe24 | `0x0f119001` | `0x00000000` |
    | xe25 | `0x0f11a001` | `0x00000000` |
    | xe26 | `0x0f11b001` | `0x00000000` |
    | xe27 | `0x0f11c001` | `0x00000000` |
    | xe28 | `0x0f11d001` | `0x00000000` |
    | xe29 | `0x0f11e001` | `0x00000000` |
    | xe30 | `0x0f11f001` | `0x00000000` |
    | xe31 | `0x0f120001` | `0x00000000` |
    | xe32 | `0x0f121001` | `0x00000000` |
    | xe33 | `0x0f122001` | `0x00000000` |
    | xe34 | `0x0f123001` | `0x00000000` |
    | xe35 | `0x0f124001` | `0x00000000` |
    | xe36 | `0x0f125001` | `0x00000000` |
    | xe37 | `0x0f126001` | `0x00000000` |
    | xe38 | `0x0f127001` | `0x00000000` |
    | xe39 | `0x0f128001` | `0x00000000` |
    | xe40 | `0x0f129001` | `0x00000000` |
    | xe41 | `0x0f12a001` | `0x00000000` |
    | xe42 | `0x0f12b001` | `0x00000000` |
    | xe43 | `0x0f12c001` | `0x00000000` |
    | xe44 | `0x0f12d001` | `0x00000000` |
    | xe45 | `0x0f12e001` | `0x00000000` |
    | xe46 | `0x0f12f001` | `0x00000000` |
    | xe47 | `0x0f130001` | `0x00000000` |
    | xe48 | `0x0f131001` | `0x00000000` |
    | xe49 | `0x0f132001` | `0x00000000` |
    | xe50 | `0x0f133001` | `0x00000000` |
    | xe51 | `0x0f134001` | `0x00000000` |
    | lb0 | `0x0f141001` | `0x00000000` |

---

## RIPHE4r

- **Address:** `0x0f100002`  ·  **Size:** 4 bytes
- **Function:** Receive IPv4 L3 IP Header Error Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100002` | `0x00000000` |
    | xe0 | `0x0f101002` | `0x00000000` |
    | xe1 | `0x0f102002` | `0x00000000` |
    | xe2 | `0x0f103002` | `0x00000000` |
    | xe3 | `0x0f104002` | `0x00000000` |
    | xe4 | `0x0f105002` | `0x00000000` |
    | xe5 | `0x0f106002` | `0x00000000` |
    | xe6 | `0x0f107002` | `0x00000000` |
    | xe7 | `0x0f108002` | `0x00000000` |
    | xe8 | `0x0f109002` | `0x00000000` |
    | xe9 | `0x0f10a002` | `0x00000000` |
    | xe10 | `0x0f10b002` | `0x00000000` |
    | xe11 | `0x0f10c002` | `0x00000000` |
    | xe12 | `0x0f10d002` | `0x00000000` |
    | xe13 | `0x0f10e002` | `0x00000000` |
    | xe14 | `0x0f10f002` | `0x00000000` |
    | xe15 | `0x0f110002` | `0x00000000` |
    | xe16 | `0x0f111002` | `0x00000000` |
    | xe17 | `0x0f112002` | `0x00000000` |
    | xe18 | `0x0f113002` | `0x00000000` |
    | xe19 | `0x0f114002` | `0x00000000` |
    | xe20 | `0x0f115002` | `0x00000000` |
    | xe21 | `0x0f116002` | `0x00000000` |
    | xe22 | `0x0f117002` | `0x00000000` |
    | xe23 | `0x0f118002` | `0x00000000` |
    | xe24 | `0x0f119002` | `0x00000000` |
    | xe25 | `0x0f11a002` | `0x00000000` |
    | xe26 | `0x0f11b002` | `0x00000000` |
    | xe27 | `0x0f11c002` | `0x00000000` |
    | xe28 | `0x0f11d002` | `0x00000000` |
    | xe29 | `0x0f11e002` | `0x00000000` |
    | xe30 | `0x0f11f002` | `0x00000000` |
    | xe31 | `0x0f120002` | `0x00000000` |
    | xe32 | `0x0f121002` | `0x00000000` |
    | xe33 | `0x0f122002` | `0x00000000` |
    | xe34 | `0x0f123002` | `0x00000000` |
    | xe35 | `0x0f124002` | `0x00000000` |
    | xe36 | `0x0f125002` | `0x00000000` |
    | xe37 | `0x0f126002` | `0x00000000` |
    | xe38 | `0x0f127002` | `0x00000000` |
    | xe39 | `0x0f128002` | `0x00000000` |
    | xe40 | `0x0f129002` | `0x00000000` |
    | xe41 | `0x0f12a002` | `0x00000000` |
    | xe42 | `0x0f12b002` | `0x00000000` |
    | xe43 | `0x0f12c002` | `0x00000000` |
    | xe44 | `0x0f12d002` | `0x00000000` |
    | xe45 | `0x0f12e002` | `0x00000000` |
    | xe46 | `0x0f12f002` | `0x00000000` |
    | xe47 | `0x0f130002` | `0x00000000` |
    | xe48 | `0x0f131002` | `0x00000000` |
    | xe49 | `0x0f132002` | `0x00000000` |
    | xe50 | `0x0f133002` | `0x00000000` |
    | xe51 | `0x0f134002` | `0x00000000` |
    | lb0 | `0x0f141002` | `0x00000000` |

---

## IMRP4r

- **Address:** `0x0f100003`  ·  **Size:** 4 bytes
- **Function:** Receive IPv4 L3 routed multicast packets

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100003` | `0x00000000` |
    | xe0 | `0x0f101003` | `0x00000000` |
    | xe1 | `0x0f102003` | `0x00000000` |
    | xe2 | `0x0f103003` | `0x00000000` |
    | xe3 | `0x0f104003` | `0x00000000` |
    | xe4 | `0x0f105003` | `0x00000000` |
    | xe5 | `0x0f106003` | `0x00000000` |
    | xe6 | `0x0f107003` | `0x00000000` |
    | xe7 | `0x0f108003` | `0x00000000` |
    | xe8 | `0x0f109003` | `0x00000000` |
    | xe9 | `0x0f10a003` | `0x00000000` |
    | xe10 | `0x0f10b003` | `0x00000000` |
    | xe11 | `0x0f10c003` | `0x00000000` |
    | xe12 | `0x0f10d003` | `0x00000000` |
    | xe13 | `0x0f10e003` | `0x00000000` |
    | xe14 | `0x0f10f003` | `0x00000000` |
    | xe15 | `0x0f110003` | `0x00000000` |
    | xe16 | `0x0f111003` | `0x00000000` |
    | xe17 | `0x0f112003` | `0x00000000` |
    | xe18 | `0x0f113003` | `0x00000000` |
    | xe19 | `0x0f114003` | `0x00000000` |
    | xe20 | `0x0f115003` | `0x00000000` |
    | xe21 | `0x0f116003` | `0x00000000` |
    | xe22 | `0x0f117003` | `0x00000000` |
    | xe23 | `0x0f118003` | `0x00000000` |
    | xe24 | `0x0f119003` | `0x00000000` |
    | xe25 | `0x0f11a003` | `0x00000000` |
    | xe26 | `0x0f11b003` | `0x00000000` |
    | xe27 | `0x0f11c003` | `0x00000000` |
    | xe28 | `0x0f11d003` | `0x00000000` |
    | xe29 | `0x0f11e003` | `0x00000000` |
    | xe30 | `0x0f11f003` | `0x00000000` |
    | xe31 | `0x0f120003` | `0x00000000` |
    | xe32 | `0x0f121003` | `0x00000000` |
    | xe33 | `0x0f122003` | `0x00000000` |
    | xe34 | `0x0f123003` | `0x00000000` |
    | xe35 | `0x0f124003` | `0x00000000` |
    | xe36 | `0x0f125003` | `0x00000000` |
    | xe37 | `0x0f126003` | `0x00000000` |
    | xe38 | `0x0f127003` | `0x00000000` |
    | xe39 | `0x0f128003` | `0x00000000` |
    | xe40 | `0x0f129003` | `0x00000000` |
    | xe41 | `0x0f12a003` | `0x00000000` |
    | xe42 | `0x0f12b003` | `0x00000000` |
    | xe43 | `0x0f12c003` | `0x00000000` |
    | xe44 | `0x0f12d003` | `0x00000000` |
    | xe45 | `0x0f12e003` | `0x00000000` |
    | xe46 | `0x0f12f003` | `0x00000000` |
    | xe47 | `0x0f130003` | `0x00000000` |
    | xe48 | `0x0f131003` | `0x00000000` |
    | xe49 | `0x0f132003` | `0x00000000` |
    | xe50 | `0x0f133003` | `0x00000000` |
    | xe51 | `0x0f134003` | `0x00000000` |
    | lb0 | `0x0f141003` | `0x00000000` |

---

## RIPD6r

- **Address:** `0x0f100004`  ·  **Size:** 4 bytes
- **Function:** Receive IPv6 L3 Discard Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100004` | `0x00000000` |
    | xe0 | `0x0f101004` | `0x00000000` |
    | xe1 | `0x0f102004` | `0x00000000` |
    | xe2 | `0x0f103004` | `0x00000000` |
    | xe3 | `0x0f104004` | `0x00000000` |
    | xe4 | `0x0f105004` | `0x00000000` |
    | xe5 | `0x0f106004` | `0x00000000` |
    | xe6 | `0x0f107004` | `0x00000000` |
    | xe7 | `0x0f108004` | `0x00000000` |
    | xe8 | `0x0f109004` | `0x00000000` |
    | xe9 | `0x0f10a004` | `0x00000000` |
    | xe10 | `0x0f10b004` | `0x00000000` |
    | xe11 | `0x0f10c004` | `0x00000000` |
    | xe12 | `0x0f10d004` | `0x00000000` |
    | xe13 | `0x0f10e004` | `0x00000000` |
    | xe14 | `0x0f10f004` | `0x00000000` |
    | xe15 | `0x0f110004` | `0x00000000` |
    | xe16 | `0x0f111004` | `0x00000000` |
    | xe17 | `0x0f112004` | `0x00000000` |
    | xe18 | `0x0f113004` | `0x00000000` |
    | xe19 | `0x0f114004` | `0x00000000` |
    | xe20 | `0x0f115004` | `0x00000000` |
    | xe21 | `0x0f116004` | `0x00000000` |
    | xe22 | `0x0f117004` | `0x00000000` |
    | xe23 | `0x0f118004` | `0x00000000` |
    | xe24 | `0x0f119004` | `0x00000000` |
    | xe25 | `0x0f11a004` | `0x00000000` |
    | xe26 | `0x0f11b004` | `0x00000000` |
    | xe27 | `0x0f11c004` | `0x00000000` |
    | xe28 | `0x0f11d004` | `0x00000000` |
    | xe29 | `0x0f11e004` | `0x00000000` |
    | xe30 | `0x0f11f004` | `0x00000000` |
    | xe31 | `0x0f120004` | `0x00000000` |
    | xe32 | `0x0f121004` | `0x00000000` |
    | xe33 | `0x0f122004` | `0x00000000` |
    | xe34 | `0x0f123004` | `0x00000000` |
    | xe35 | `0x0f124004` | `0x00000000` |
    | xe36 | `0x0f125004` | `0x00000000` |
    | xe37 | `0x0f126004` | `0x00000000` |
    | xe38 | `0x0f127004` | `0x00000000` |
    | xe39 | `0x0f128004` | `0x00000000` |
    | xe40 | `0x0f129004` | `0x00000000` |
    | xe41 | `0x0f12a004` | `0x00000000` |
    | xe42 | `0x0f12b004` | `0x00000000` |
    | xe43 | `0x0f12c004` | `0x00000000` |
    | xe44 | `0x0f12d004` | `0x00000000` |
    | xe45 | `0x0f12e004` | `0x00000000` |
    | xe46 | `0x0f12f004` | `0x00000000` |
    | xe47 | `0x0f130004` | `0x00000000` |
    | xe48 | `0x0f131004` | `0x00000000` |
    | xe49 | `0x0f132004` | `0x00000000` |
    | xe50 | `0x0f133004` | `0x00000000` |
    | xe51 | `0x0f134004` | `0x00000000` |
    | lb0 | `0x0f141004` | `0x00000000` |

---

## RIPC6r

- **Address:** `0x0f100005`  ·  **Size:** 4 bytes
- **Function:** Receive IPv6 L3 Unicast Frame Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100005` | `0x00000000` |
    | xe0 | `0x0f101005` | `0x00000000` |
    | xe1 | `0x0f102005` | `0x00000000` |
    | xe2 | `0x0f103005` | `0x00000000` |
    | xe3 | `0x0f104005` | `0x00000000` |
    | xe4 | `0x0f105005` | `0x00000000` |
    | xe5 | `0x0f106005` | `0x00000000` |
    | xe6 | `0x0f107005` | `0x00000000` |
    | xe7 | `0x0f108005` | `0x00000000` |
    | xe8 | `0x0f109005` | `0x00000000` |
    | xe9 | `0x0f10a005` | `0x00000000` |
    | xe10 | `0x0f10b005` | `0x00000000` |
    | xe11 | `0x0f10c005` | `0x00000000` |
    | xe12 | `0x0f10d005` | `0x00000000` |
    | xe13 | `0x0f10e005` | `0x00000000` |
    | xe14 | `0x0f10f005` | `0x00000000` |
    | xe15 | `0x0f110005` | `0x00000000` |
    | xe16 | `0x0f111005` | `0x00000000` |
    | xe17 | `0x0f112005` | `0x00000000` |
    | xe18 | `0x0f113005` | `0x00000000` |
    | xe19 | `0x0f114005` | `0x00000000` |
    | xe20 | `0x0f115005` | `0x00000000` |
    | xe21 | `0x0f116005` | `0x00000000` |
    | xe22 | `0x0f117005` | `0x00000000` |
    | xe23 | `0x0f118005` | `0x00000000` |
    | xe24 | `0x0f119005` | `0x00000000` |
    | xe25 | `0x0f11a005` | `0x00000000` |
    | xe26 | `0x0f11b005` | `0x00000000` |
    | xe27 | `0x0f11c005` | `0x00000000` |
    | xe28 | `0x0f11d005` | `0x00000000` |
    | xe29 | `0x0f11e005` | `0x00000000` |
    | xe30 | `0x0f11f005` | `0x00000000` |
    | xe31 | `0x0f120005` | `0x00000000` |
    | xe32 | `0x0f121005` | `0x00000000` |
    | xe33 | `0x0f122005` | `0x00000000` |
    | xe34 | `0x0f123005` | `0x00000000` |
    | xe35 | `0x0f124005` | `0x00000000` |
    | xe36 | `0x0f125005` | `0x00000000` |
    | xe37 | `0x0f126005` | `0x00000000` |
    | xe38 | `0x0f127005` | `0x00000000` |
    | xe39 | `0x0f128005` | `0x00000000` |
    | xe40 | `0x0f129005` | `0x00000000` |
    | xe41 | `0x0f12a005` | `0x00000000` |
    | xe42 | `0x0f12b005` | `0x00000000` |
    | xe43 | `0x0f12c005` | `0x00000000` |
    | xe44 | `0x0f12d005` | `0x00000000` |
    | xe45 | `0x0f12e005` | `0x00000000` |
    | xe46 | `0x0f12f005` | `0x00000000` |
    | xe47 | `0x0f130005` | `0x00000000` |
    | xe48 | `0x0f131005` | `0x00000000` |
    | xe49 | `0x0f132005` | `0x00000000` |
    | xe50 | `0x0f133005` | `0x00000000` |
    | xe51 | `0x0f134005` | `0x00000000` |
    | lb0 | `0x0f141005` | `0x00000000` |

---

## RIPHE6r

- **Address:** `0x0f100006`  ·  **Size:** 4 bytes
- **Function:** Receive IPv6 L3 IP Header Error Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100006` | `0x00000000` |
    | xe0 | `0x0f101006` | `0x00000000` |
    | xe1 | `0x0f102006` | `0x00000000` |
    | xe2 | `0x0f103006` | `0x00000000` |
    | xe3 | `0x0f104006` | `0x00000000` |
    | xe4 | `0x0f105006` | `0x00000000` |
    | xe5 | `0x0f106006` | `0x00000000` |
    | xe6 | `0x0f107006` | `0x00000000` |
    | xe7 | `0x0f108006` | `0x00000000` |
    | xe8 | `0x0f109006` | `0x00000000` |
    | xe9 | `0x0f10a006` | `0x00000000` |
    | xe10 | `0x0f10b006` | `0x00000000` |
    | xe11 | `0x0f10c006` | `0x00000000` |
    | xe12 | `0x0f10d006` | `0x00000000` |
    | xe13 | `0x0f10e006` | `0x00000000` |
    | xe14 | `0x0f10f006` | `0x00000000` |
    | xe15 | `0x0f110006` | `0x00000000` |
    | xe16 | `0x0f111006` | `0x00000000` |
    | xe17 | `0x0f112006` | `0x00000000` |
    | xe18 | `0x0f113006` | `0x00000000` |
    | xe19 | `0x0f114006` | `0x00000000` |
    | xe20 | `0x0f115006` | `0x00000000` |
    | xe21 | `0x0f116006` | `0x00000000` |
    | xe22 | `0x0f117006` | `0x00000000` |
    | xe23 | `0x0f118006` | `0x00000000` |
    | xe24 | `0x0f119006` | `0x00000000` |
    | xe25 | `0x0f11a006` | `0x00000000` |
    | xe26 | `0x0f11b006` | `0x00000000` |
    | xe27 | `0x0f11c006` | `0x00000000` |
    | xe28 | `0x0f11d006` | `0x00000000` |
    | xe29 | `0x0f11e006` | `0x00000000` |
    | xe30 | `0x0f11f006` | `0x00000000` |
    | xe31 | `0x0f120006` | `0x00000000` |
    | xe32 | `0x0f121006` | `0x00000000` |
    | xe33 | `0x0f122006` | `0x00000000` |
    | xe34 | `0x0f123006` | `0x00000000` |
    | xe35 | `0x0f124006` | `0x00000000` |
    | xe36 | `0x0f125006` | `0x00000000` |
    | xe37 | `0x0f126006` | `0x00000000` |
    | xe38 | `0x0f127006` | `0x00000000` |
    | xe39 | `0x0f128006` | `0x00000000` |
    | xe40 | `0x0f129006` | `0x00000000` |
    | xe41 | `0x0f12a006` | `0x00000000` |
    | xe42 | `0x0f12b006` | `0x00000000` |
    | xe43 | `0x0f12c006` | `0x00000000` |
    | xe44 | `0x0f12d006` | `0x00000000` |
    | xe45 | `0x0f12e006` | `0x00000000` |
    | xe46 | `0x0f12f006` | `0x00000000` |
    | xe47 | `0x0f130006` | `0x00000000` |
    | xe48 | `0x0f131006` | `0x00000000` |
    | xe49 | `0x0f132006` | `0x00000000` |
    | xe50 | `0x0f133006` | `0x00000000` |
    | xe51 | `0x0f134006` | `0x00000000` |
    | lb0 | `0x0f141006` | `0x00000000` |

---

## IMRP6r

- **Address:** `0x0f100007`  ·  **Size:** 4 bytes
- **Function:** Receive IPv6 L3 routed multicast packets

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100007` | `0x00000000` |
    | xe0 | `0x0f101007` | `0x00000000` |
    | xe1 | `0x0f102007` | `0x00000000` |
    | xe2 | `0x0f103007` | `0x00000000` |
    | xe3 | `0x0f104007` | `0x00000000` |
    | xe4 | `0x0f105007` | `0x00000000` |
    | xe5 | `0x0f106007` | `0x00000000` |
    | xe6 | `0x0f107007` | `0x00000000` |
    | xe7 | `0x0f108007` | `0x00000000` |
    | xe8 | `0x0f109007` | `0x00000000` |
    | xe9 | `0x0f10a007` | `0x00000000` |
    | xe10 | `0x0f10b007` | `0x00000000` |
    | xe11 | `0x0f10c007` | `0x00000000` |
    | xe12 | `0x0f10d007` | `0x00000000` |
    | xe13 | `0x0f10e007` | `0x00000000` |
    | xe14 | `0x0f10f007` | `0x00000000` |
    | xe15 | `0x0f110007` | `0x00000000` |
    | xe16 | `0x0f111007` | `0x00000000` |
    | xe17 | `0x0f112007` | `0x00000000` |
    | xe18 | `0x0f113007` | `0x00000000` |
    | xe19 | `0x0f114007` | `0x00000000` |
    | xe20 | `0x0f115007` | `0x00000000` |
    | xe21 | `0x0f116007` | `0x00000000` |
    | xe22 | `0x0f117007` | `0x00000000` |
    | xe23 | `0x0f118007` | `0x00000000` |
    | xe24 | `0x0f119007` | `0x00000000` |
    | xe25 | `0x0f11a007` | `0x00000000` |
    | xe26 | `0x0f11b007` | `0x00000000` |
    | xe27 | `0x0f11c007` | `0x00000000` |
    | xe28 | `0x0f11d007` | `0x00000000` |
    | xe29 | `0x0f11e007` | `0x00000000` |
    | xe30 | `0x0f11f007` | `0x00000000` |
    | xe31 | `0x0f120007` | `0x00000000` |
    | xe32 | `0x0f121007` | `0x00000000` |
    | xe33 | `0x0f122007` | `0x00000000` |
    | xe34 | `0x0f123007` | `0x00000000` |
    | xe35 | `0x0f124007` | `0x00000000` |
    | xe36 | `0x0f125007` | `0x00000000` |
    | xe37 | `0x0f126007` | `0x00000000` |
    | xe38 | `0x0f127007` | `0x00000000` |
    | xe39 | `0x0f128007` | `0x00000000` |
    | xe40 | `0x0f129007` | `0x00000000` |
    | xe41 | `0x0f12a007` | `0x00000000` |
    | xe42 | `0x0f12b007` | `0x00000000` |
    | xe43 | `0x0f12c007` | `0x00000000` |
    | xe44 | `0x0f12d007` | `0x00000000` |
    | xe45 | `0x0f12e007` | `0x00000000` |
    | xe46 | `0x0f12f007` | `0x00000000` |
    | xe47 | `0x0f130007` | `0x00000000` |
    | xe48 | `0x0f131007` | `0x00000000` |
    | xe49 | `0x0f132007` | `0x00000000` |
    | xe50 | `0x0f133007` | `0x00000000` |
    | xe51 | `0x0f134007` | `0x00000000` |
    | lb0 | `0x0f141007` | `0x00000000` |

---

## RDISCr

- **Address:** `0x0f100008`  ·  **Size:** 4 bytes
- **Function:** Receive Discard Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100008` | `0x00000000` |
    | xe0 | `0x0f101008` | `0x00000000` |
    | xe1 | `0x0f102008` | `0x00000000` |
    | xe2 | `0x0f103008` | `0x00000000` |
    | xe3 | `0x0f104008` | `0x00000000` |
    | xe4 | `0x0f105008` | `0x00000000` |
    | xe5 | `0x0f106008` | `0x00000000` |
    | xe6 | `0x0f107008` | `0x00000000` |
    | xe7 | `0x0f108008` | `0x00000000` |
    | xe8 | `0x0f109008` | `0x00000000` |
    | xe9 | `0x0f10a008` | `0x00000000` |
    | xe10 | `0x0f10b008` | `0x00000000` |
    | xe11 | `0x0f10c008` | `0x00000000` |
    | xe12 | `0x0f10d008` | `0x00000000` |
    | xe13 | `0x0f10e008` | `0x00000000` |
    | xe14 | `0x0f10f008` | `0x00000000` |
    | xe15 | `0x0f110008` | `0x00000000` |
    | xe16 | `0x0f111008` | `0x00000000` |
    | xe17 | `0x0f112008` | `0x00000000` |
    | xe18 | `0x0f113008` | `0x00000000` |
    | xe19 | `0x0f114008` | `0x00000000` |
    | xe20 | `0x0f115008` | `0x00000000` |
    | xe21 | `0x0f116008` | `0x00000000` |
    | xe22 | `0x0f117008` | `0x00000000` |
    | xe23 | `0x0f118008` | `0x00000000` |
    | xe24 | `0x0f119008` | `0x00000000` |
    | xe25 | `0x0f11a008` | `0x00000000` |
    | xe26 | `0x0f11b008` | `0x00000000` |
    | xe27 | `0x0f11c008` | `0x00000000` |
    | xe28 | `0x0f11d008` | `0x00000000` |
    | xe29 | `0x0f11e008` | `0x00000000` |
    | xe30 | `0x0f11f008` | `0x00000000` |
    | xe31 | `0x0f120008` | `0x00000000` |
    | xe32 | `0x0f121008` | `0x00000000` |
    | xe33 | `0x0f122008` | `0x00000000` |
    | xe34 | `0x0f123008` | `0x00000000` |
    | xe35 | `0x0f124008` | `0x00000000` |
    | xe36 | `0x0f125008` | `0x00000000` |
    | xe37 | `0x0f126008` | `0x00000000` |
    | xe38 | `0x0f127008` | `0x00000000` |
    | xe39 | `0x0f128008` | `0x00000000` |
    | xe40 | `0x0f129008` | `0x00000000` |
    | xe41 | `0x0f12a008` | `0x00000000` |
    | xe42 | `0x0f12b008` | `0x00000000` |
    | xe43 | `0x0f12c008` | `0x00000000` |
    | xe44 | `0x0f12d008` | `0x00000000` |
    | xe45 | `0x0f12e008` | `0x00000000` |
    | xe46 | `0x0f12f008` | `0x00000000` |
    | xe47 | `0x0f130008` | `0x00000000` |
    | xe48 | `0x0f131008` | `0x00000000` |
    | xe49 | `0x0f132008` | `0x00000000` |
    | xe50 | `0x0f133008` | `0x00000000` |
    | xe51 | `0x0f134008` | `0x00000000` |
    | lb0 | `0x0f141008` | `0x00000000` |

---

## RUCr

- **Address:** `0x0f100009`  ·  **Size:** 4 bytes
- **Function:** Receive Unicast Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100009` | `0x00000000` |
    | xe0 | `0x0f101009` | `0x04000141` |
    | xe1 | `0x0f102009` | `0x04001bef` |
    | xe2 | `0x0f103009` | `0x00000000` |
    | xe3 | `0x0f104009` | `0x00000000` |
    | xe4 | `0x0f105009` | `0x00000000` |
    | xe5 | `0x0f106009` | `0x00000000` |
    | xe6 | `0x0f107009` | `0x00000000` |
    | xe7 | `0x0f108009` | `0x00000000` |
    | xe8 | `0x0f109009` | `0x00000000` |
    | xe9 | `0x0f10a009` | `0x00000000` |
    | xe10 | `0x0f10b009` | `0x00000000` |
    | xe11 | `0x0f10c009` | `0x00000000` |
    | xe12 | `0x0f10d009` | `0x00000000` |
    | xe13 | `0x0f10e009` | `0x00000000` |
    | xe14 | `0x0f10f009` | `0x00000000` |
    | xe15 | `0x0f110009` | `0x00000000` |
    | xe16 | `0x0f111009` | `0x00000000` |
    | xe17 | `0x0f112009` | `0x00000000` |
    | xe18 | `0x0f113009` | `0x00000000` |
    | xe19 | `0x0f114009` | `0x00000000` |
    | xe20 | `0x0f115009` | `0x00000000` |
    | xe21 | `0x0f116009` | `0x00000000` |
    | xe22 | `0x0f117009` | `0x00000000` |
    | xe23 | `0x0f118009` | `0x00000000` |
    | xe24 | `0x0f119009` | `0x00000000` |
    | xe25 | `0x0f11a009` | `0x00000000` |
    | xe26 | `0x0f11b009` | `0x00000000` |
    | xe27 | `0x0f11c009` | `0x00000000` |
    | xe28 | `0x0f11d009` | `0x00000000` |
    | xe29 | `0x0f11e009` | `0x00000000` |
    | xe30 | `0x0f11f009` | `0x00000000` |
    | xe31 | `0x0f120009` | `0x00000000` |
    | xe32 | `0x0f121009` | `0x00000000` |
    | xe33 | `0x0f122009` | `0x00000000` |
    | xe34 | `0x0f123009` | `0x00000000` |
    | xe35 | `0x0f124009` | `0x00000000` |
    | xe36 | `0x0f125009` | `0x00000000` |
    | xe37 | `0x0f126009` | `0x00000000` |
    | xe38 | `0x0f127009` | `0x00000000` |
    | xe39 | `0x0f128009` | `0x00000000` |
    | xe40 | `0x0f129009` | `0x00000000` |
    | xe41 | `0x0f12a009` | `0x00000000` |
    | xe42 | `0x0f12b009` | `0x00000000` |
    | xe43 | `0x0f12c009` | `0x00000000` |
    | xe44 | `0x0f12d009` | `0x00000000` |
    | xe45 | `0x0f12e009` | `0x00000000` |
    | xe46 | `0x0f12f009` | `0x00000000` |
    | xe47 | `0x0f130009` | `0x00000000` |
    | xe48 | `0x0f131009` | `0x00000000` |
    | xe49 | `0x0f132009` | `0x00000000` |
    | xe50 | `0x0f133009` | `0x00000000` |
    | xe51 | `0x0f134009` | `0x00000000` |
    | lb0 | `0x0f141009` | `0x00000000` |

---

## RPORTDr

- **Address:** `0x0f10000a`  ·  **Size:** 4 bytes
- **Function:** PortInDiscard Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000a` | `0x00000000` |
    | xe0 | `0x0f10100a` | `0x00000000` |
    | xe1 | `0x0f10200a` | `0x00000000` |
    | xe2 | `0x0f10300a` | `0x00000000` |
    | xe3 | `0x0f10400a` | `0x00000000` |
    | xe4 | `0x0f10500a` | `0x00000000` |
    | xe5 | `0x0f10600a` | `0x00000000` |
    | xe6 | `0x0f10700a` | `0x00000000` |
    | xe7 | `0x0f10800a` | `0x00000000` |
    | xe8 | `0x0f10900a` | `0x00000000` |
    | xe9 | `0x0f10a00a` | `0x00000000` |
    | xe10 | `0x0f10b00a` | `0x00000000` |
    | xe11 | `0x0f10c00a` | `0x00000000` |
    | xe12 | `0x0f10d00a` | `0x00000000` |
    | xe13 | `0x0f10e00a` | `0x00000000` |
    | xe14 | `0x0f10f00a` | `0x00000000` |
    | xe15 | `0x0f11000a` | `0x00000000` |
    | xe16 | `0x0f11100a` | `0x00000000` |
    | xe17 | `0x0f11200a` | `0x00000000` |
    | xe18 | `0x0f11300a` | `0x00000000` |
    | xe19 | `0x0f11400a` | `0x00000000` |
    | xe20 | `0x0f11500a` | `0x00000000` |
    | xe21 | `0x0f11600a` | `0x00000000` |
    | xe22 | `0x0f11700a` | `0x00000000` |
    | xe23 | `0x0f11800a` | `0x00000000` |
    | xe24 | `0x0f11900a` | `0x00000000` |
    | xe25 | `0x0f11a00a` | `0x00000000` |
    | xe26 | `0x0f11b00a` | `0x00000000` |
    | xe27 | `0x0f11c00a` | `0x00000000` |
    | xe28 | `0x0f11d00a` | `0x00000000` |
    | xe29 | `0x0f11e00a` | `0x00000000` |
    | xe30 | `0x0f11f00a` | `0x00000000` |
    | xe31 | `0x0f12000a` | `0x00000000` |
    | xe32 | `0x0f12100a` | `0x00000000` |
    | xe33 | `0x0f12200a` | `0x00000000` |
    | xe34 | `0x0f12300a` | `0x00000000` |
    | xe35 | `0x0f12400a` | `0x00000000` |
    | xe36 | `0x0f12500a` | `0x00000000` |
    | xe37 | `0x0f12600a` | `0x00000000` |
    | xe38 | `0x0f12700a` | `0x00000000` |
    | xe39 | `0x0f12800a` | `0x00000000` |
    | xe40 | `0x0f12900a` | `0x00000000` |
    | xe41 | `0x0f12a00a` | `0x00000000` |
    | xe42 | `0x0f12b00a` | `0x00000000` |
    | xe43 | `0x0f12c00a` | `0x00000000` |
    | xe44 | `0x0f12d00a` | `0x00000000` |
    | xe45 | `0x0f12e00a` | `0x00000000` |
    | xe46 | `0x0f12f00a` | `0x00000000` |
    | xe47 | `0x0f13000a` | `0x00000000` |
    | xe48 | `0x0f13100a` | `0x00000000` |
    | xe49 | `0x0f13200a` | `0x00000000` |
    | xe50 | `0x0f13300a` | `0x00000000` |
    | xe51 | `0x0f13400a` | `0x00000000` |
    | lb0 | `0x0f14100a` | `0x00000000` |

---

## RDBGC0r

- **Address:** `0x0f10000b`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000b` | `0x00000000` |
    | xe0 | `0x0f10100b` | `0x00000000` |
    | xe1 | `0x0f10200b` | `0x00000000` |
    | xe2 | `0x0f10300b` | `0x00000000` |
    | xe3 | `0x0f10400b` | `0x00000000` |
    | xe4 | `0x0f10500b` | `0x00000000` |
    | xe5 | `0x0f10600b` | `0x00000000` |
    | xe6 | `0x0f10700b` | `0x00000000` |
    | xe7 | `0x0f10800b` | `0x00000000` |
    | xe8 | `0x0f10900b` | `0x00000000` |
    | xe9 | `0x0f10a00b` | `0x00000000` |
    | xe10 | `0x0f10b00b` | `0x00000000` |
    | xe11 | `0x0f10c00b` | `0x00000000` |
    | xe12 | `0x0f10d00b` | `0x00000000` |
    | xe13 | `0x0f10e00b` | `0x00000000` |
    | xe14 | `0x0f10f00b` | `0x00000000` |
    | xe15 | `0x0f11000b` | `0x00000000` |
    | xe16 | `0x0f11100b` | `0x00000000` |
    | xe17 | `0x0f11200b` | `0x00000000` |
    | xe18 | `0x0f11300b` | `0x00000000` |
    | xe19 | `0x0f11400b` | `0x00000000` |
    | xe20 | `0x0f11500b` | `0x00000000` |
    | xe21 | `0x0f11600b` | `0x00000000` |
    | xe22 | `0x0f11700b` | `0x00000000` |
    | xe23 | `0x0f11800b` | `0x00000000` |
    | xe24 | `0x0f11900b` | `0x00000000` |
    | xe25 | `0x0f11a00b` | `0x00000000` |
    | xe26 | `0x0f11b00b` | `0x00000000` |
    | xe27 | `0x0f11c00b` | `0x00000000` |
    | xe28 | `0x0f11d00b` | `0x00000000` |
    | xe29 | `0x0f11e00b` | `0x00000000` |
    | xe30 | `0x0f11f00b` | `0x00000000` |
    | xe31 | `0x0f12000b` | `0x00000000` |
    | xe32 | `0x0f12100b` | `0x00000000` |
    | xe33 | `0x0f12200b` | `0x00000000` |
    | xe34 | `0x0f12300b` | `0x00000000` |
    | xe35 | `0x0f12400b` | `0x00000000` |
    | xe36 | `0x0f12500b` | `0x00000000` |
    | xe37 | `0x0f12600b` | `0x00000000` |
    | xe38 | `0x0f12700b` | `0x00000000` |
    | xe39 | `0x0f12800b` | `0x00000000` |
    | xe40 | `0x0f12900b` | `0x00000000` |
    | xe41 | `0x0f12a00b` | `0x00000000` |
    | xe42 | `0x0f12b00b` | `0x00000000` |
    | xe43 | `0x0f12c00b` | `0x00000000` |
    | xe44 | `0x0f12d00b` | `0x00000000` |
    | xe45 | `0x0f12e00b` | `0x00000000` |
    | xe46 | `0x0f12f00b` | `0x00000000` |
    | xe47 | `0x0f13000b` | `0x00000000` |
    | xe48 | `0x0f13100b` | `0x00000000` |
    | xe49 | `0x0f13200b` | `0x00000000` |
    | xe50 | `0x0f13300b` | `0x00000000` |
    | xe51 | `0x0f13400b` | `0x00000000` |
    | lb0 | `0x0f14100b` | `0x00000000` |

---

## RDBGC1r

- **Address:** `0x0f10000c`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000c` | `0x00000000` |
    | xe0 | `0x0f10100c` | `0x00000429` |
    | xe1 | `0x0f10200c` | `0x0400041e` |
    | xe2 | `0x0f10300c` | `0x00000000` |
    | xe3 | `0x0f10400c` | `0x00000000` |
    | xe4 | `0x0f10500c` | `0x00000000` |
    | xe5 | `0x0f10600c` | `0x00000000` |
    | xe6 | `0x0f10700c` | `0x00000000` |
    | xe7 | `0x0f10800c` | `0x00000000` |
    | xe8 | `0x0f10900c` | `0x00000000` |
    | xe9 | `0x0f10a00c` | `0x00000000` |
    | xe10 | `0x0f10b00c` | `0x00000000` |
    | xe11 | `0x0f10c00c` | `0x00000000` |
    | xe12 | `0x0f10d00c` | `0x00000000` |
    | xe13 | `0x0f10e00c` | `0x00000000` |
    | xe14 | `0x0f10f00c` | `0x00000000` |
    | xe15 | `0x0f11000c` | `0x00000000` |
    | xe16 | `0x0f11100c` | `0x00000000` |
    | xe17 | `0x0f11200c` | `0x00000000` |
    | xe18 | `0x0f11300c` | `0x00000000` |
    | xe19 | `0x0f11400c` | `0x00000000` |
    | xe20 | `0x0f11500c` | `0x00000000` |
    | xe21 | `0x0f11600c` | `0x00000000` |
    | xe22 | `0x0f11700c` | `0x00000000` |
    | xe23 | `0x0f11800c` | `0x00000000` |
    | xe24 | `0x0f11900c` | `0x00000000` |
    | xe25 | `0x0f11a00c` | `0x00000000` |
    | xe26 | `0x0f11b00c` | `0x00000000` |
    | xe27 | `0x0f11c00c` | `0x00000000` |
    | xe28 | `0x0f11d00c` | `0x00000000` |
    | xe29 | `0x0f11e00c` | `0x00000000` |
    | xe30 | `0x0f11f00c` | `0x00000000` |
    | xe31 | `0x0f12000c` | `0x00000000` |
    | xe32 | `0x0f12100c` | `0x00000000` |
    | xe33 | `0x0f12200c` | `0x00000000` |
    | xe34 | `0x0f12300c` | `0x00000000` |
    | xe35 | `0x0f12400c` | `0x00000000` |
    | xe36 | `0x0f12500c` | `0x00000000` |
    | xe37 | `0x0f12600c` | `0x00000000` |
    | xe38 | `0x0f12700c` | `0x00000000` |
    | xe39 | `0x0f12800c` | `0x00000000` |
    | xe40 | `0x0f12900c` | `0x00000000` |
    | xe41 | `0x0f12a00c` | `0x00000000` |
    | xe42 | `0x0f12b00c` | `0x00000000` |
    | xe43 | `0x0f12c00c` | `0x00000000` |
    | xe44 | `0x0f12d00c` | `0x00000000` |
    | xe45 | `0x0f12e00c` | `0x00000000` |
    | xe46 | `0x0f12f00c` | `0x00000000` |
    | xe47 | `0x0f13000c` | `0x00000000` |
    | xe48 | `0x0f13100c` | `0x00000000` |
    | xe49 | `0x0f13200c` | `0x00000000` |
    | xe50 | `0x0f13300c` | `0x00000000` |
    | xe51 | `0x0f13400c` | `0x00000000` |
    | lb0 | `0x0f14100c` | `0x00000000` |

---

## RDBGC2r

- **Address:** `0x0f10000d`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000d` | `0x00000000` |
    | xe0 | `0x0f10100d` | `0x00000000` |
    | xe1 | `0x0f10200d` | `0x00000000` |
    | xe2 | `0x0f10300d` | `0x00000000` |
    | xe3 | `0x0f10400d` | `0x00000000` |
    | xe4 | `0x0f10500d` | `0x00000000` |
    | xe5 | `0x0f10600d` | `0x00000000` |
    | xe6 | `0x0f10700d` | `0x00000000` |
    | xe7 | `0x0f10800d` | `0x00000000` |
    | xe8 | `0x0f10900d` | `0x00000000` |
    | xe9 | `0x0f10a00d` | `0x00000000` |
    | xe10 | `0x0f10b00d` | `0x00000000` |
    | xe11 | `0x0f10c00d` | `0x00000000` |
    | xe12 | `0x0f10d00d` | `0x00000000` |
    | xe13 | `0x0f10e00d` | `0x00000000` |
    | xe14 | `0x0f10f00d` | `0x00000000` |
    | xe15 | `0x0f11000d` | `0x00000000` |
    | xe16 | `0x0f11100d` | `0x00000000` |
    | xe17 | `0x0f11200d` | `0x00000000` |
    | xe18 | `0x0f11300d` | `0x00000000` |
    | xe19 | `0x0f11400d` | `0x00000000` |
    | xe20 | `0x0f11500d` | `0x00000000` |
    | xe21 | `0x0f11600d` | `0x00000000` |
    | xe22 | `0x0f11700d` | `0x00000000` |
    | xe23 | `0x0f11800d` | `0x00000000` |
    | xe24 | `0x0f11900d` | `0x00000000` |
    | xe25 | `0x0f11a00d` | `0x00000000` |
    | xe26 | `0x0f11b00d` | `0x00000000` |
    | xe27 | `0x0f11c00d` | `0x00000000` |
    | xe28 | `0x0f11d00d` | `0x00000000` |
    | xe29 | `0x0f11e00d` | `0x00000000` |
    | xe30 | `0x0f11f00d` | `0x00000000` |
    | xe31 | `0x0f12000d` | `0x00000000` |
    | xe32 | `0x0f12100d` | `0x00000000` |
    | xe33 | `0x0f12200d` | `0x00000000` |
    | xe34 | `0x0f12300d` | `0x00000000` |
    | xe35 | `0x0f12400d` | `0x00000000` |
    | xe36 | `0x0f12500d` | `0x00000000` |
    | xe37 | `0x0f12600d` | `0x00000000` |
    | xe38 | `0x0f12700d` | `0x00000000` |
    | xe39 | `0x0f12800d` | `0x00000000` |
    | xe40 | `0x0f12900d` | `0x00000000` |
    | xe41 | `0x0f12a00d` | `0x00000000` |
    | xe42 | `0x0f12b00d` | `0x00000000` |
    | xe43 | `0x0f12c00d` | `0x00000000` |
    | xe44 | `0x0f12d00d` | `0x00000000` |
    | xe45 | `0x0f12e00d` | `0x00000000` |
    | xe46 | `0x0f12f00d` | `0x00000000` |
    | xe47 | `0x0f13000d` | `0x00000000` |
    | xe48 | `0x0f13100d` | `0x00000000` |
    | xe49 | `0x0f13200d` | `0x00000000` |
    | xe50 | `0x0f13300d` | `0x00000000` |
    | xe51 | `0x0f13400d` | `0x00000000` |
    | lb0 | `0x0f14100d` | `0x00000000` |

---

## RDBGC3r

- **Address:** `0x0f10000e`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000e` | `0x00000000` |
    | xe0 | `0x0f10100e` | `0x00000000` |
    | xe1 | `0x0f10200e` | `0x00000000` |
    | xe2 | `0x0f10300e` | `0x00000000` |
    | xe3 | `0x0f10400e` | `0x00000000` |
    | xe4 | `0x0f10500e` | `0x00000000` |
    | xe5 | `0x0f10600e` | `0x00000000` |
    | xe6 | `0x0f10700e` | `0x00000000` |
    | xe7 | `0x0f10800e` | `0x00000000` |
    | xe8 | `0x0f10900e` | `0x00000000` |
    | xe9 | `0x0f10a00e` | `0x00000000` |
    | xe10 | `0x0f10b00e` | `0x00000000` |
    | xe11 | `0x0f10c00e` | `0x00000000` |
    | xe12 | `0x0f10d00e` | `0x00000000` |
    | xe13 | `0x0f10e00e` | `0x00000000` |
    | xe14 | `0x0f10f00e` | `0x00000000` |
    | xe15 | `0x0f11000e` | `0x00000000` |
    | xe16 | `0x0f11100e` | `0x00000000` |
    | xe17 | `0x0f11200e` | `0x00000000` |
    | xe18 | `0x0f11300e` | `0x00000000` |
    | xe19 | `0x0f11400e` | `0x00000000` |
    | xe20 | `0x0f11500e` | `0x00000000` |
    | xe21 | `0x0f11600e` | `0x00000000` |
    | xe22 | `0x0f11700e` | `0x00000000` |
    | xe23 | `0x0f11800e` | `0x00000000` |
    | xe24 | `0x0f11900e` | `0x00000000` |
    | xe25 | `0x0f11a00e` | `0x00000000` |
    | xe26 | `0x0f11b00e` | `0x00000000` |
    | xe27 | `0x0f11c00e` | `0x00000000` |
    | xe28 | `0x0f11d00e` | `0x00000000` |
    | xe29 | `0x0f11e00e` | `0x00000000` |
    | xe30 | `0x0f11f00e` | `0x00000000` |
    | xe31 | `0x0f12000e` | `0x00000000` |
    | xe32 | `0x0f12100e` | `0x00000000` |
    | xe33 | `0x0f12200e` | `0x00000000` |
    | xe34 | `0x0f12300e` | `0x00000000` |
    | xe35 | `0x0f12400e` | `0x00000000` |
    | xe36 | `0x0f12500e` | `0x00000000` |
    | xe37 | `0x0f12600e` | `0x00000000` |
    | xe38 | `0x0f12700e` | `0x00000000` |
    | xe39 | `0x0f12800e` | `0x00000000` |
    | xe40 | `0x0f12900e` | `0x00000000` |
    | xe41 | `0x0f12a00e` | `0x00000000` |
    | xe42 | `0x0f12b00e` | `0x00000000` |
    | xe43 | `0x0f12c00e` | `0x00000000` |
    | xe44 | `0x0f12d00e` | `0x00000000` |
    | xe45 | `0x0f12e00e` | `0x00000000` |
    | xe46 | `0x0f12f00e` | `0x00000000` |
    | xe47 | `0x0f13000e` | `0x00000000` |
    | xe48 | `0x0f13100e` | `0x00000000` |
    | xe49 | `0x0f13200e` | `0x00000000` |
    | xe50 | `0x0f13300e` | `0x00000000` |
    | xe51 | `0x0f13400e` | `0x00000000` |
    | lb0 | `0x0f14100e` | `0x00000000` |

---

## RDBGC4r

- **Address:** `0x0f10000f`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10000f` | `0x00000000` |
    | xe0 | `0x0f10100f` | `0x00000000` |
    | xe1 | `0x0f10200f` | `0x00000000` |
    | xe2 | `0x0f10300f` | `0x00000000` |
    | xe3 | `0x0f10400f` | `0x00000000` |
    | xe4 | `0x0f10500f` | `0x00000000` |
    | xe5 | `0x0f10600f` | `0x00000000` |
    | xe6 | `0x0f10700f` | `0x00000000` |
    | xe7 | `0x0f10800f` | `0x00000000` |
    | xe8 | `0x0f10900f` | `0x00000000` |
    | xe9 | `0x0f10a00f` | `0x00000000` |
    | xe10 | `0x0f10b00f` | `0x00000000` |
    | xe11 | `0x0f10c00f` | `0x00000000` |
    | xe12 | `0x0f10d00f` | `0x00000000` |
    | xe13 | `0x0f10e00f` | `0x00000000` |
    | xe14 | `0x0f10f00f` | `0x00000000` |
    | xe15 | `0x0f11000f` | `0x00000000` |
    | xe16 | `0x0f11100f` | `0x00000000` |
    | xe17 | `0x0f11200f` | `0x00000000` |
    | xe18 | `0x0f11300f` | `0x00000000` |
    | xe19 | `0x0f11400f` | `0x00000000` |
    | xe20 | `0x0f11500f` | `0x00000000` |
    | xe21 | `0x0f11600f` | `0x00000000` |
    | xe22 | `0x0f11700f` | `0x00000000` |
    | xe23 | `0x0f11800f` | `0x00000000` |
    | xe24 | `0x0f11900f` | `0x00000000` |
    | xe25 | `0x0f11a00f` | `0x00000000` |
    | xe26 | `0x0f11b00f` | `0x00000000` |
    | xe27 | `0x0f11c00f` | `0x00000000` |
    | xe28 | `0x0f11d00f` | `0x00000000` |
    | xe29 | `0x0f11e00f` | `0x00000000` |
    | xe30 | `0x0f11f00f` | `0x00000000` |
    | xe31 | `0x0f12000f` | `0x00000000` |
    | xe32 | `0x0f12100f` | `0x00000000` |
    | xe33 | `0x0f12200f` | `0x00000000` |
    | xe34 | `0x0f12300f` | `0x00000000` |
    | xe35 | `0x0f12400f` | `0x00000000` |
    | xe36 | `0x0f12500f` | `0x00000000` |
    | xe37 | `0x0f12600f` | `0x00000000` |
    | xe38 | `0x0f12700f` | `0x00000000` |
    | xe39 | `0x0f12800f` | `0x00000000` |
    | xe40 | `0x0f12900f` | `0x00000000` |
    | xe41 | `0x0f12a00f` | `0x00000000` |
    | xe42 | `0x0f12b00f` | `0x00000000` |
    | xe43 | `0x0f12c00f` | `0x00000000` |
    | xe44 | `0x0f12d00f` | `0x00000000` |
    | xe45 | `0x0f12e00f` | `0x00000000` |
    | xe46 | `0x0f12f00f` | `0x00000000` |
    | xe47 | `0x0f13000f` | `0x00000000` |
    | xe48 | `0x0f13100f` | `0x00000000` |
    | xe49 | `0x0f13200f` | `0x00000000` |
    | xe50 | `0x0f13300f` | `0x00000000` |
    | xe51 | `0x0f13400f` | `0x00000000` |
    | lb0 | `0x0f14100f` | `0x00000000` |

---

## RDBGC5r

- **Address:** `0x0f100010`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100010` | `0x00000000` |
    | xe0 | `0x0f101010` | `0x00000000` |
    | xe1 | `0x0f102010` | `0x00000000` |
    | xe2 | `0x0f103010` | `0x00000000` |
    | xe3 | `0x0f104010` | `0x00000000` |
    | xe4 | `0x0f105010` | `0x00000000` |
    | xe5 | `0x0f106010` | `0x00000000` |
    | xe6 | `0x0f107010` | `0x00000000` |
    | xe7 | `0x0f108010` | `0x00000000` |
    | xe8 | `0x0f109010` | `0x00000000` |
    | xe9 | `0x0f10a010` | `0x00000000` |
    | xe10 | `0x0f10b010` | `0x00000000` |
    | xe11 | `0x0f10c010` | `0x00000000` |
    | xe12 | `0x0f10d010` | `0x00000000` |
    | xe13 | `0x0f10e010` | `0x00000000` |
    | xe14 | `0x0f10f010` | `0x00000000` |
    | xe15 | `0x0f110010` | `0x00000000` |
    | xe16 | `0x0f111010` | `0x00000000` |
    | xe17 | `0x0f112010` | `0x00000000` |
    | xe18 | `0x0f113010` | `0x00000000` |
    | xe19 | `0x0f114010` | `0x00000000` |
    | xe20 | `0x0f115010` | `0x00000000` |
    | xe21 | `0x0f116010` | `0x00000000` |
    | xe22 | `0x0f117010` | `0x00000000` |
    | xe23 | `0x0f118010` | `0x00000000` |
    | xe24 | `0x0f119010` | `0x00000000` |
    | xe25 | `0x0f11a010` | `0x00000000` |
    | xe26 | `0x0f11b010` | `0x00000000` |
    | xe27 | `0x0f11c010` | `0x00000000` |
    | xe28 | `0x0f11d010` | `0x00000000` |
    | xe29 | `0x0f11e010` | `0x00000000` |
    | xe30 | `0x0f11f010` | `0x00000000` |
    | xe31 | `0x0f120010` | `0x00000000` |
    | xe32 | `0x0f121010` | `0x00000000` |
    | xe33 | `0x0f122010` | `0x00000000` |
    | xe34 | `0x0f123010` | `0x00000000` |
    | xe35 | `0x0f124010` | `0x00000000` |
    | xe36 | `0x0f125010` | `0x00000000` |
    | xe37 | `0x0f126010` | `0x00000000` |
    | xe38 | `0x0f127010` | `0x00000000` |
    | xe39 | `0x0f128010` | `0x00000000` |
    | xe40 | `0x0f129010` | `0x00000000` |
    | xe41 | `0x0f12a010` | `0x00000000` |
    | xe42 | `0x0f12b010` | `0x00000000` |
    | xe43 | `0x0f12c010` | `0x00000000` |
    | xe44 | `0x0f12d010` | `0x00000000` |
    | xe45 | `0x0f12e010` | `0x00000000` |
    | xe46 | `0x0f12f010` | `0x00000000` |
    | xe47 | `0x0f130010` | `0x00000000` |
    | xe48 | `0x0f131010` | `0x00000000` |
    | xe49 | `0x0f132010` | `0x00000000` |
    | xe50 | `0x0f133010` | `0x00000000` |
    | xe51 | `0x0f134010` | `0x00000000` |
    | lb0 | `0x0f141010` | `0x00000000` |

---

## IUNHGIr

- **Address:** `0x0f100011`  ·  **Size:** 4 bytes
- **Function:** Receive Unknown HGI Packet Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100011` | `0x00000000` |
    | xe0 | `0x0f101011` | `0x00000000` |
    | xe1 | `0x0f102011` | `0x00000000` |
    | xe2 | `0x0f103011` | `0x00000000` |
    | xe3 | `0x0f104011` | `0x00000000` |
    | xe4 | `0x0f105011` | `0x00000000` |
    | xe5 | `0x0f106011` | `0x00000000` |
    | xe6 | `0x0f107011` | `0x00000000` |
    | xe7 | `0x0f108011` | `0x00000000` |
    | xe8 | `0x0f109011` | `0x00000000` |
    | xe9 | `0x0f10a011` | `0x00000000` |
    | xe10 | `0x0f10b011` | `0x00000000` |
    | xe11 | `0x0f10c011` | `0x00000000` |
    | xe12 | `0x0f10d011` | `0x00000000` |
    | xe13 | `0x0f10e011` | `0x00000000` |
    | xe14 | `0x0f10f011` | `0x00000000` |
    | xe15 | `0x0f110011` | `0x00000000` |
    | xe16 | `0x0f111011` | `0x00000000` |
    | xe17 | `0x0f112011` | `0x00000000` |
    | xe18 | `0x0f113011` | `0x00000000` |
    | xe19 | `0x0f114011` | `0x00000000` |
    | xe20 | `0x0f115011` | `0x00000000` |
    | xe21 | `0x0f116011` | `0x00000000` |
    | xe22 | `0x0f117011` | `0x00000000` |
    | xe23 | `0x0f118011` | `0x00000000` |
    | xe24 | `0x0f119011` | `0x00000000` |
    | xe25 | `0x0f11a011` | `0x00000000` |
    | xe26 | `0x0f11b011` | `0x00000000` |
    | xe27 | `0x0f11c011` | `0x00000000` |
    | xe28 | `0x0f11d011` | `0x00000000` |
    | xe29 | `0x0f11e011` | `0x00000000` |
    | xe30 | `0x0f11f011` | `0x00000000` |
    | xe31 | `0x0f120011` | `0x00000000` |
    | xe32 | `0x0f121011` | `0x00000000` |
    | xe33 | `0x0f122011` | `0x00000000` |
    | xe34 | `0x0f123011` | `0x00000000` |
    | xe35 | `0x0f124011` | `0x00000000` |
    | xe36 | `0x0f125011` | `0x00000000` |
    | xe37 | `0x0f126011` | `0x00000000` |
    | xe38 | `0x0f127011` | `0x00000000` |
    | xe39 | `0x0f128011` | `0x00000000` |
    | xe40 | `0x0f129011` | `0x00000000` |
    | xe41 | `0x0f12a011` | `0x00000000` |
    | xe42 | `0x0f12b011` | `0x00000000` |
    | xe43 | `0x0f12c011` | `0x00000000` |
    | xe44 | `0x0f12d011` | `0x00000000` |
    | xe45 | `0x0f12e011` | `0x00000000` |
    | xe46 | `0x0f12f011` | `0x00000000` |
    | xe47 | `0x0f130011` | `0x00000000` |
    | xe48 | `0x0f131011` | `0x00000000` |
    | xe49 | `0x0f132011` | `0x00000000` |
    | xe50 | `0x0f133011` | `0x00000000` |
    | xe51 | `0x0f134011` | `0x00000000` |
    | lb0 | `0x0f141011` | `0x00000000` |

---

## ICTRLr

- **Address:** `0x0f100012`  ·  **Size:** 4 bytes
- **Function:** Receive HiGig Packet with Control Opcode Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100012` | `0x00000000` |
    | xe0 | `0x0f101012` | `0x00000000` |
    | xe1 | `0x0f102012` | `0x00000000` |
    | xe2 | `0x0f103012` | `0x00000000` |
    | xe3 | `0x0f104012` | `0x00000000` |
    | xe4 | `0x0f105012` | `0x00000000` |
    | xe5 | `0x0f106012` | `0x00000000` |
    | xe6 | `0x0f107012` | `0x00000000` |
    | xe7 | `0x0f108012` | `0x00000000` |
    | xe8 | `0x0f109012` | `0x00000000` |
    | xe9 | `0x0f10a012` | `0x00000000` |
    | xe10 | `0x0f10b012` | `0x00000000` |
    | xe11 | `0x0f10c012` | `0x00000000` |
    | xe12 | `0x0f10d012` | `0x00000000` |
    | xe13 | `0x0f10e012` | `0x00000000` |
    | xe14 | `0x0f10f012` | `0x00000000` |
    | xe15 | `0x0f110012` | `0x00000000` |
    | xe16 | `0x0f111012` | `0x00000000` |
    | xe17 | `0x0f112012` | `0x00000000` |
    | xe18 | `0x0f113012` | `0x00000000` |
    | xe19 | `0x0f114012` | `0x00000000` |
    | xe20 | `0x0f115012` | `0x00000000` |
    | xe21 | `0x0f116012` | `0x00000000` |
    | xe22 | `0x0f117012` | `0x00000000` |
    | xe23 | `0x0f118012` | `0x00000000` |
    | xe24 | `0x0f119012` | `0x00000000` |
    | xe25 | `0x0f11a012` | `0x00000000` |
    | xe26 | `0x0f11b012` | `0x00000000` |
    | xe27 | `0x0f11c012` | `0x00000000` |
    | xe28 | `0x0f11d012` | `0x00000000` |
    | xe29 | `0x0f11e012` | `0x00000000` |
    | xe30 | `0x0f11f012` | `0x00000000` |
    | xe31 | `0x0f120012` | `0x00000000` |
    | xe32 | `0x0f121012` | `0x00000000` |
    | xe33 | `0x0f122012` | `0x00000000` |
    | xe34 | `0x0f123012` | `0x00000000` |
    | xe35 | `0x0f124012` | `0x00000000` |
    | xe36 | `0x0f125012` | `0x00000000` |
    | xe37 | `0x0f126012` | `0x00000000` |
    | xe38 | `0x0f127012` | `0x00000000` |
    | xe39 | `0x0f128012` | `0x00000000` |
    | xe40 | `0x0f129012` | `0x00000000` |
    | xe41 | `0x0f12a012` | `0x00000000` |
    | xe42 | `0x0f12b012` | `0x00000000` |
    | xe43 | `0x0f12c012` | `0x00000000` |
    | xe44 | `0x0f12d012` | `0x00000000` |
    | xe45 | `0x0f12e012` | `0x00000000` |
    | xe46 | `0x0f12f012` | `0x00000000` |
    | xe47 | `0x0f130012` | `0x00000000` |
    | xe48 | `0x0f131012` | `0x00000000` |
    | xe49 | `0x0f132012` | `0x00000000` |
    | xe50 | `0x0f133012` | `0x00000000` |
    | xe51 | `0x0f134012` | `0x00000000` |
    | lb0 | `0x0f141012` | `0x00000000` |

---

## IBCASTr

- **Address:** `0x0f100013`  ·  **Size:** 4 bytes
- **Function:** Receive HiGig Packet with Broadcast Opcode Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100013` | `0x00000000` |
    | xe0 | `0x0f101013` | `0x00000000` |
    | xe1 | `0x0f102013` | `0x00000000` |
    | xe2 | `0x0f103013` | `0x00000000` |
    | xe3 | `0x0f104013` | `0x00000000` |
    | xe4 | `0x0f105013` | `0x00000000` |
    | xe5 | `0x0f106013` | `0x00000000` |
    | xe6 | `0x0f107013` | `0x00000000` |
    | xe7 | `0x0f108013` | `0x00000000` |
    | xe8 | `0x0f109013` | `0x00000000` |
    | xe9 | `0x0f10a013` | `0x00000000` |
    | xe10 | `0x0f10b013` | `0x00000000` |
    | xe11 | `0x0f10c013` | `0x00000000` |
    | xe12 | `0x0f10d013` | `0x00000000` |
    | xe13 | `0x0f10e013` | `0x00000000` |
    | xe14 | `0x0f10f013` | `0x00000000` |
    | xe15 | `0x0f110013` | `0x00000000` |
    | xe16 | `0x0f111013` | `0x00000000` |
    | xe17 | `0x0f112013` | `0x00000000` |
    | xe18 | `0x0f113013` | `0x00000000` |
    | xe19 | `0x0f114013` | `0x00000000` |
    | xe20 | `0x0f115013` | `0x00000000` |
    | xe21 | `0x0f116013` | `0x00000000` |
    | xe22 | `0x0f117013` | `0x00000000` |
    | xe23 | `0x0f118013` | `0x00000000` |
    | xe24 | `0x0f119013` | `0x00000000` |
    | xe25 | `0x0f11a013` | `0x00000000` |
    | xe26 | `0x0f11b013` | `0x00000000` |
    | xe27 | `0x0f11c013` | `0x00000000` |
    | xe28 | `0x0f11d013` | `0x00000000` |
    | xe29 | `0x0f11e013` | `0x00000000` |
    | xe30 | `0x0f11f013` | `0x00000000` |
    | xe31 | `0x0f120013` | `0x00000000` |
    | xe32 | `0x0f121013` | `0x00000000` |
    | xe33 | `0x0f122013` | `0x00000000` |
    | xe34 | `0x0f123013` | `0x00000000` |
    | xe35 | `0x0f124013` | `0x00000000` |
    | xe36 | `0x0f125013` | `0x00000000` |
    | xe37 | `0x0f126013` | `0x00000000` |
    | xe38 | `0x0f127013` | `0x00000000` |
    | xe39 | `0x0f128013` | `0x00000000` |
    | xe40 | `0x0f129013` | `0x00000000` |
    | xe41 | `0x0f12a013` | `0x00000000` |
    | xe42 | `0x0f12b013` | `0x00000000` |
    | xe43 | `0x0f12c013` | `0x00000000` |
    | xe44 | `0x0f12d013` | `0x00000000` |
    | xe45 | `0x0f12e013` | `0x00000000` |
    | xe46 | `0x0f12f013` | `0x00000000` |
    | xe47 | `0x0f130013` | `0x00000000` |
    | xe48 | `0x0f131013` | `0x00000000` |
    | xe49 | `0x0f132013` | `0x00000000` |
    | xe50 | `0x0f133013` | `0x00000000` |
    | xe51 | `0x0f134013` | `0x00000000` |
    | lb0 | `0x0f141013` | `0x00000000` |

---

## ILTOMCr

- **Address:** `0x0f100014`  ·  **Size:** 4 bytes
- **Function:** Receive HiGig Packet with L2MC Opcode Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100014` | `0x00000000` |
    | xe0 | `0x0f101014` | `0x00000000` |
    | xe1 | `0x0f102014` | `0x00000000` |
    | xe2 | `0x0f103014` | `0x00000000` |
    | xe3 | `0x0f104014` | `0x00000000` |
    | xe4 | `0x0f105014` | `0x00000000` |
    | xe5 | `0x0f106014` | `0x00000000` |
    | xe6 | `0x0f107014` | `0x00000000` |
    | xe7 | `0x0f108014` | `0x00000000` |
    | xe8 | `0x0f109014` | `0x00000000` |
    | xe9 | `0x0f10a014` | `0x00000000` |
    | xe10 | `0x0f10b014` | `0x00000000` |
    | xe11 | `0x0f10c014` | `0x00000000` |
    | xe12 | `0x0f10d014` | `0x00000000` |
    | xe13 | `0x0f10e014` | `0x00000000` |
    | xe14 | `0x0f10f014` | `0x00000000` |
    | xe15 | `0x0f110014` | `0x00000000` |
    | xe16 | `0x0f111014` | `0x00000000` |
    | xe17 | `0x0f112014` | `0x00000000` |
    | xe18 | `0x0f113014` | `0x00000000` |
    | xe19 | `0x0f114014` | `0x00000000` |
    | xe20 | `0x0f115014` | `0x00000000` |
    | xe21 | `0x0f116014` | `0x00000000` |
    | xe22 | `0x0f117014` | `0x00000000` |
    | xe23 | `0x0f118014` | `0x00000000` |
    | xe24 | `0x0f119014` | `0x00000000` |
    | xe25 | `0x0f11a014` | `0x00000000` |
    | xe26 | `0x0f11b014` | `0x00000000` |
    | xe27 | `0x0f11c014` | `0x00000000` |
    | xe28 | `0x0f11d014` | `0x00000000` |
    | xe29 | `0x0f11e014` | `0x00000000` |
    | xe30 | `0x0f11f014` | `0x00000000` |
    | xe31 | `0x0f120014` | `0x00000000` |
    | xe32 | `0x0f121014` | `0x00000000` |
    | xe33 | `0x0f122014` | `0x00000000` |
    | xe34 | `0x0f123014` | `0x00000000` |
    | xe35 | `0x0f124014` | `0x00000000` |
    | xe36 | `0x0f125014` | `0x00000000` |
    | xe37 | `0x0f126014` | `0x00000000` |
    | xe38 | `0x0f127014` | `0x00000000` |
    | xe39 | `0x0f128014` | `0x00000000` |
    | xe40 | `0x0f129014` | `0x00000000` |
    | xe41 | `0x0f12a014` | `0x00000000` |
    | xe42 | `0x0f12b014` | `0x00000000` |
    | xe43 | `0x0f12c014` | `0x00000000` |
    | xe44 | `0x0f12d014` | `0x00000000` |
    | xe45 | `0x0f12e014` | `0x00000000` |
    | xe46 | `0x0f12f014` | `0x00000000` |
    | xe47 | `0x0f130014` | `0x00000000` |
    | xe48 | `0x0f131014` | `0x00000000` |
    | xe49 | `0x0f132014` | `0x00000000` |
    | xe50 | `0x0f133014` | `0x00000000` |
    | xe51 | `0x0f134014` | `0x00000000` |
    | lb0 | `0x0f141014` | `0x00000000` |

---

## IIPMCr

- **Address:** `0x0f100015`  ·  **Size:** 4 bytes
- **Function:** Receive HiGig Packet with IPMC Opcode Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100015` | `0x00000000` |
    | xe0 | `0x0f101015` | `0x00000000` |
    | xe1 | `0x0f102015` | `0x00000000` |
    | xe2 | `0x0f103015` | `0x00000000` |
    | xe3 | `0x0f104015` | `0x00000000` |
    | xe4 | `0x0f105015` | `0x00000000` |
    | xe5 | `0x0f106015` | `0x00000000` |
    | xe6 | `0x0f107015` | `0x00000000` |
    | xe7 | `0x0f108015` | `0x00000000` |
    | xe8 | `0x0f109015` | `0x00000000` |
    | xe9 | `0x0f10a015` | `0x00000000` |
    | xe10 | `0x0f10b015` | `0x00000000` |
    | xe11 | `0x0f10c015` | `0x00000000` |
    | xe12 | `0x0f10d015` | `0x00000000` |
    | xe13 | `0x0f10e015` | `0x00000000` |
    | xe14 | `0x0f10f015` | `0x00000000` |
    | xe15 | `0x0f110015` | `0x00000000` |
    | xe16 | `0x0f111015` | `0x00000000` |
    | xe17 | `0x0f112015` | `0x00000000` |
    | xe18 | `0x0f113015` | `0x00000000` |
    | xe19 | `0x0f114015` | `0x00000000` |
    | xe20 | `0x0f115015` | `0x00000000` |
    | xe21 | `0x0f116015` | `0x00000000` |
    | xe22 | `0x0f117015` | `0x00000000` |
    | xe23 | `0x0f118015` | `0x00000000` |
    | xe24 | `0x0f119015` | `0x00000000` |
    | xe25 | `0x0f11a015` | `0x00000000` |
    | xe26 | `0x0f11b015` | `0x00000000` |
    | xe27 | `0x0f11c015` | `0x00000000` |
    | xe28 | `0x0f11d015` | `0x00000000` |
    | xe29 | `0x0f11e015` | `0x00000000` |
    | xe30 | `0x0f11f015` | `0x00000000` |
    | xe31 | `0x0f120015` | `0x00000000` |
    | xe32 | `0x0f121015` | `0x00000000` |
    | xe33 | `0x0f122015` | `0x00000000` |
    | xe34 | `0x0f123015` | `0x00000000` |
    | xe35 | `0x0f124015` | `0x00000000` |
    | xe36 | `0x0f125015` | `0x00000000` |
    | xe37 | `0x0f126015` | `0x00000000` |
    | xe38 | `0x0f127015` | `0x00000000` |
    | xe39 | `0x0f128015` | `0x00000000` |
    | xe40 | `0x0f129015` | `0x00000000` |
    | xe41 | `0x0f12a015` | `0x00000000` |
    | xe42 | `0x0f12b015` | `0x00000000` |
    | xe43 | `0x0f12c015` | `0x00000000` |
    | xe44 | `0x0f12d015` | `0x00000000` |
    | xe45 | `0x0f12e015` | `0x00000000` |
    | xe46 | `0x0f12f015` | `0x00000000` |
    | xe47 | `0x0f130015` | `0x00000000` |
    | xe48 | `0x0f131015` | `0x00000000` |
    | xe49 | `0x0f132015` | `0x00000000` |
    | xe50 | `0x0f133015` | `0x00000000` |
    | xe51 | `0x0f134015` | `0x00000000` |
    | lb0 | `0x0f141015` | `0x00000000` |

---

## IUNKOPCr

- **Address:** `0x0f100016`  ·  **Size:** 4 bytes
- **Function:** Receive HiGig Packet with Unknown Opcode Counter

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100016` | `0x00000000` |
    | xe0 | `0x0f101016` | `0x00000000` |
    | xe1 | `0x0f102016` | `0x00000000` |
    | xe2 | `0x0f103016` | `0x00000000` |
    | xe3 | `0x0f104016` | `0x00000000` |
    | xe4 | `0x0f105016` | `0x00000000` |
    | xe5 | `0x0f106016` | `0x00000000` |
    | xe6 | `0x0f107016` | `0x00000000` |
    | xe7 | `0x0f108016` | `0x00000000` |
    | xe8 | `0x0f109016` | `0x00000000` |
    | xe9 | `0x0f10a016` | `0x00000000` |
    | xe10 | `0x0f10b016` | `0x00000000` |
    | xe11 | `0x0f10c016` | `0x00000000` |
    | xe12 | `0x0f10d016` | `0x00000000` |
    | xe13 | `0x0f10e016` | `0x00000000` |
    | xe14 | `0x0f10f016` | `0x00000000` |
    | xe15 | `0x0f110016` | `0x00000000` |
    | xe16 | `0x0f111016` | `0x00000000` |
    | xe17 | `0x0f112016` | `0x00000000` |
    | xe18 | `0x0f113016` | `0x00000000` |
    | xe19 | `0x0f114016` | `0x00000000` |
    | xe20 | `0x0f115016` | `0x00000000` |
    | xe21 | `0x0f116016` | `0x00000000` |
    | xe22 | `0x0f117016` | `0x00000000` |
    | xe23 | `0x0f118016` | `0x00000000` |
    | xe24 | `0x0f119016` | `0x00000000` |
    | xe25 | `0x0f11a016` | `0x00000000` |
    | xe26 | `0x0f11b016` | `0x00000000` |
    | xe27 | `0x0f11c016` | `0x00000000` |
    | xe28 | `0x0f11d016` | `0x00000000` |
    | xe29 | `0x0f11e016` | `0x00000000` |
    | xe30 | `0x0f11f016` | `0x00000000` |
    | xe31 | `0x0f120016` | `0x00000000` |
    | xe32 | `0x0f121016` | `0x00000000` |
    | xe33 | `0x0f122016` | `0x00000000` |
    | xe34 | `0x0f123016` | `0x00000000` |
    | xe35 | `0x0f124016` | `0x00000000` |
    | xe36 | `0x0f125016` | `0x00000000` |
    | xe37 | `0x0f126016` | `0x00000000` |
    | xe38 | `0x0f127016` | `0x00000000` |
    | xe39 | `0x0f128016` | `0x00000000` |
    | xe40 | `0x0f129016` | `0x00000000` |
    | xe41 | `0x0f12a016` | `0x00000000` |
    | xe42 | `0x0f12b016` | `0x00000000` |
    | xe43 | `0x0f12c016` | `0x00000000` |
    | xe44 | `0x0f12d016` | `0x00000000` |
    | xe45 | `0x0f12e016` | `0x00000000` |
    | xe46 | `0x0f12f016` | `0x00000000` |
    | xe47 | `0x0f130016` | `0x00000000` |
    | xe48 | `0x0f131016` | `0x00000000` |
    | xe49 | `0x0f132016` | `0x00000000` |
    | xe50 | `0x0f133016` | `0x00000000` |
    | xe51 | `0x0f134016` | `0x00000000` |
    | lb0 | `0x0f141016` | `0x00000000` |

---

## RDBGC6r

- **Address:** `0x0f100017`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #6

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100017` | `0x00000000` |
    | xe0 | `0x0f101017` | `0x00000000` |
    | xe1 | `0x0f102017` | `0x00000000` |
    | xe2 | `0x0f103017` | `0x00000000` |
    | xe3 | `0x0f104017` | `0x00000000` |
    | xe4 | `0x0f105017` | `0x00000000` |
    | xe5 | `0x0f106017` | `0x00000000` |
    | xe6 | `0x0f107017` | `0x00000000` |
    | xe7 | `0x0f108017` | `0x00000000` |
    | xe8 | `0x0f109017` | `0x00000000` |
    | xe9 | `0x0f10a017` | `0x00000000` |
    | xe10 | `0x0f10b017` | `0x00000000` |
    | xe11 | `0x0f10c017` | `0x00000000` |
    | xe12 | `0x0f10d017` | `0x00000000` |
    | xe13 | `0x0f10e017` | `0x00000000` |
    | xe14 | `0x0f10f017` | `0x00000000` |
    | xe15 | `0x0f110017` | `0x00000000` |
    | xe16 | `0x0f111017` | `0x00000000` |
    | xe17 | `0x0f112017` | `0x00000000` |
    | xe18 | `0x0f113017` | `0x00000000` |
    | xe19 | `0x0f114017` | `0x00000000` |
    | xe20 | `0x0f115017` | `0x00000000` |
    | xe21 | `0x0f116017` | `0x00000000` |
    | xe22 | `0x0f117017` | `0x00000000` |
    | xe23 | `0x0f118017` | `0x00000000` |
    | xe24 | `0x0f119017` | `0x00000000` |
    | xe25 | `0x0f11a017` | `0x00000000` |
    | xe26 | `0x0f11b017` | `0x00000000` |
    | xe27 | `0x0f11c017` | `0x00000000` |
    | xe28 | `0x0f11d017` | `0x00000000` |
    | xe29 | `0x0f11e017` | `0x00000000` |
    | xe30 | `0x0f11f017` | `0x00000000` |
    | xe31 | `0x0f120017` | `0x00000000` |
    | xe32 | `0x0f121017` | `0x00000000` |
    | xe33 | `0x0f122017` | `0x00000000` |
    | xe34 | `0x0f123017` | `0x00000000` |
    | xe35 | `0x0f124017` | `0x00000000` |
    | xe36 | `0x0f125017` | `0x00000000` |
    | xe37 | `0x0f126017` | `0x00000000` |
    | xe38 | `0x0f127017` | `0x00000000` |
    | xe39 | `0x0f128017` | `0x00000000` |
    | xe40 | `0x0f129017` | `0x00000000` |
    | xe41 | `0x0f12a017` | `0x00000000` |
    | xe42 | `0x0f12b017` | `0x00000000` |
    | xe43 | `0x0f12c017` | `0x00000000` |
    | xe44 | `0x0f12d017` | `0x00000000` |
    | xe45 | `0x0f12e017` | `0x00000000` |
    | xe46 | `0x0f12f017` | `0x00000000` |
    | xe47 | `0x0f130017` | `0x00000000` |
    | xe48 | `0x0f131017` | `0x00000000` |
    | xe49 | `0x0f132017` | `0x00000000` |
    | xe50 | `0x0f133017` | `0x00000000` |
    | xe51 | `0x0f134017` | `0x00000000` |
    | lb0 | `0x0f141017` | `0x00000000` |

---

## RDBGC7r

- **Address:** `0x0f100018`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #7

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100018` | `0x00000000` |
    | xe0 | `0x0f101018` | `0x00000000` |
    | xe1 | `0x0f102018` | `0x00000000` |
    | xe2 | `0x0f103018` | `0x00000000` |
    | xe3 | `0x0f104018` | `0x00000000` |
    | xe4 | `0x0f105018` | `0x00000000` |
    | xe5 | `0x0f106018` | `0x00000000` |
    | xe6 | `0x0f107018` | `0x00000000` |
    | xe7 | `0x0f108018` | `0x00000000` |
    | xe8 | `0x0f109018` | `0x00000000` |
    | xe9 | `0x0f10a018` | `0x00000000` |
    | xe10 | `0x0f10b018` | `0x00000000` |
    | xe11 | `0x0f10c018` | `0x00000000` |
    | xe12 | `0x0f10d018` | `0x00000000` |
    | xe13 | `0x0f10e018` | `0x00000000` |
    | xe14 | `0x0f10f018` | `0x00000000` |
    | xe15 | `0x0f110018` | `0x00000000` |
    | xe16 | `0x0f111018` | `0x00000000` |
    | xe17 | `0x0f112018` | `0x00000000` |
    | xe18 | `0x0f113018` | `0x00000000` |
    | xe19 | `0x0f114018` | `0x00000000` |
    | xe20 | `0x0f115018` | `0x00000000` |
    | xe21 | `0x0f116018` | `0x00000000` |
    | xe22 | `0x0f117018` | `0x00000000` |
    | xe23 | `0x0f118018` | `0x00000000` |
    | xe24 | `0x0f119018` | `0x00000000` |
    | xe25 | `0x0f11a018` | `0x00000000` |
    | xe26 | `0x0f11b018` | `0x00000000` |
    | xe27 | `0x0f11c018` | `0x00000000` |
    | xe28 | `0x0f11d018` | `0x00000000` |
    | xe29 | `0x0f11e018` | `0x00000000` |
    | xe30 | `0x0f11f018` | `0x00000000` |
    | xe31 | `0x0f120018` | `0x00000000` |
    | xe32 | `0x0f121018` | `0x00000000` |
    | xe33 | `0x0f122018` | `0x00000000` |
    | xe34 | `0x0f123018` | `0x00000000` |
    | xe35 | `0x0f124018` | `0x00000000` |
    | xe36 | `0x0f125018` | `0x00000000` |
    | xe37 | `0x0f126018` | `0x00000000` |
    | xe38 | `0x0f127018` | `0x00000000` |
    | xe39 | `0x0f128018` | `0x00000000` |
    | xe40 | `0x0f129018` | `0x00000000` |
    | xe41 | `0x0f12a018` | `0x00000000` |
    | xe42 | `0x0f12b018` | `0x00000000` |
    | xe43 | `0x0f12c018` | `0x00000000` |
    | xe44 | `0x0f12d018` | `0x00000000` |
    | xe45 | `0x0f12e018` | `0x00000000` |
    | xe46 | `0x0f12f018` | `0x00000000` |
    | xe47 | `0x0f130018` | `0x00000000` |
    | xe48 | `0x0f131018` | `0x00000000` |
    | xe49 | `0x0f132018` | `0x00000000` |
    | xe50 | `0x0f133018` | `0x00000000` |
    | xe51 | `0x0f134018` | `0x00000000` |
    | lb0 | `0x0f141018` | `0x00000000` |

---

## RDBGC8r

- **Address:** `0x0f100019`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #8

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100019` | `0x00000000` |
    | xe0 | `0x0f101019` | `0x00000000` |
    | xe1 | `0x0f102019` | `0x00000000` |
    | xe2 | `0x0f103019` | `0x00000000` |
    | xe3 | `0x0f104019` | `0x00000000` |
    | xe4 | `0x0f105019` | `0x00000000` |
    | xe5 | `0x0f106019` | `0x00000000` |
    | xe6 | `0x0f107019` | `0x00000000` |
    | xe7 | `0x0f108019` | `0x00000000` |
    | xe8 | `0x0f109019` | `0x00000000` |
    | xe9 | `0x0f10a019` | `0x00000000` |
    | xe10 | `0x0f10b019` | `0x00000000` |
    | xe11 | `0x0f10c019` | `0x00000000` |
    | xe12 | `0x0f10d019` | `0x00000000` |
    | xe13 | `0x0f10e019` | `0x00000000` |
    | xe14 | `0x0f10f019` | `0x00000000` |
    | xe15 | `0x0f110019` | `0x00000000` |
    | xe16 | `0x0f111019` | `0x00000000` |
    | xe17 | `0x0f112019` | `0x00000000` |
    | xe18 | `0x0f113019` | `0x00000000` |
    | xe19 | `0x0f114019` | `0x00000000` |
    | xe20 | `0x0f115019` | `0x00000000` |
    | xe21 | `0x0f116019` | `0x00000000` |
    | xe22 | `0x0f117019` | `0x00000000` |
    | xe23 | `0x0f118019` | `0x00000000` |
    | xe24 | `0x0f119019` | `0x00000000` |
    | xe25 | `0x0f11a019` | `0x00000000` |
    | xe26 | `0x0f11b019` | `0x00000000` |
    | xe27 | `0x0f11c019` | `0x00000000` |
    | xe28 | `0x0f11d019` | `0x00000000` |
    | xe29 | `0x0f11e019` | `0x00000000` |
    | xe30 | `0x0f11f019` | `0x00000000` |
    | xe31 | `0x0f120019` | `0x00000000` |
    | xe32 | `0x0f121019` | `0x00000000` |
    | xe33 | `0x0f122019` | `0x00000000` |
    | xe34 | `0x0f123019` | `0x00000000` |
    | xe35 | `0x0f124019` | `0x00000000` |
    | xe36 | `0x0f125019` | `0x00000000` |
    | xe37 | `0x0f126019` | `0x00000000` |
    | xe38 | `0x0f127019` | `0x00000000` |
    | xe39 | `0x0f128019` | `0x00000000` |
    | xe40 | `0x0f129019` | `0x00000000` |
    | xe41 | `0x0f12a019` | `0x00000000` |
    | xe42 | `0x0f12b019` | `0x00000000` |
    | xe43 | `0x0f12c019` | `0x00000000` |
    | xe44 | `0x0f12d019` | `0x00000000` |
    | xe45 | `0x0f12e019` | `0x00000000` |
    | xe46 | `0x0f12f019` | `0x00000000` |
    | xe47 | `0x0f130019` | `0x00000000` |
    | xe48 | `0x0f131019` | `0x00000000` |
    | xe49 | `0x0f132019` | `0x00000000` |
    | xe50 | `0x0f133019` | `0x00000000` |
    | xe51 | `0x0f134019` | `0x00000000` |
    | lb0 | `0x0f141019` | `0x00000000` |

---

## ING_TRILL_RX_PKTSr

- **Address:** `0x0f10001a`  ·  **Size:** 4 bytes
- **Function:** Number of packets received on this port with TRILL ethertype.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001a` | `0x00000000` |
    | xe0 | `0x0f10101a` | `0x00000000` |
    | xe1 | `0x0f10201a` | `0x00000000` |
    | xe2 | `0x0f10301a` | `0x00000000` |
    | xe3 | `0x0f10401a` | `0x00000000` |
    | xe4 | `0x0f10501a` | `0x00000000` |
    | xe5 | `0x0f10601a` | `0x00000000` |
    | xe6 | `0x0f10701a` | `0x00000000` |
    | xe7 | `0x0f10801a` | `0x00000000` |
    | xe8 | `0x0f10901a` | `0x00000000` |
    | xe9 | `0x0f10a01a` | `0x00000000` |
    | xe10 | `0x0f10b01a` | `0x00000000` |
    | xe11 | `0x0f10c01a` | `0x00000000` |
    | xe12 | `0x0f10d01a` | `0x00000000` |
    | xe13 | `0x0f10e01a` | `0x00000000` |
    | xe14 | `0x0f10f01a` | `0x00000000` |
    | xe15 | `0x0f11001a` | `0x00000000` |
    | xe16 | `0x0f11101a` | `0x00000000` |
    | xe17 | `0x0f11201a` | `0x00000000` |
    | xe18 | `0x0f11301a` | `0x00000000` |
    | xe19 | `0x0f11401a` | `0x00000000` |
    | xe20 | `0x0f11501a` | `0x00000000` |
    | xe21 | `0x0f11601a` | `0x00000000` |
    | xe22 | `0x0f11701a` | `0x00000000` |
    | xe23 | `0x0f11801a` | `0x00000000` |
    | xe24 | `0x0f11901a` | `0x00000000` |
    | xe25 | `0x0f11a01a` | `0x00000000` |
    | xe26 | `0x0f11b01a` | `0x00000000` |
    | xe27 | `0x0f11c01a` | `0x00000000` |
    | xe28 | `0x0f11d01a` | `0x00000000` |
    | xe29 | `0x0f11e01a` | `0x00000000` |
    | xe30 | `0x0f11f01a` | `0x00000000` |
    | xe31 | `0x0f12001a` | `0x00000000` |
    | xe32 | `0x0f12101a` | `0x00000000` |
    | xe33 | `0x0f12201a` | `0x00000000` |
    | xe34 | `0x0f12301a` | `0x00000000` |
    | xe35 | `0x0f12401a` | `0x00000000` |
    | xe36 | `0x0f12501a` | `0x00000000` |
    | xe37 | `0x0f12601a` | `0x00000000` |
    | xe38 | `0x0f12701a` | `0x00000000` |
    | xe39 | `0x0f12801a` | `0x00000000` |
    | xe40 | `0x0f12901a` | `0x00000000` |
    | xe41 | `0x0f12a01a` | `0x00000000` |
    | xe42 | `0x0f12b01a` | `0x00000000` |
    | xe43 | `0x0f12c01a` | `0x00000000` |
    | xe44 | `0x0f12d01a` | `0x00000000` |
    | xe45 | `0x0f12e01a` | `0x00000000` |
    | xe46 | `0x0f12f01a` | `0x00000000` |
    | xe47 | `0x0f13001a` | `0x00000000` |
    | xe48 | `0x0f13101a` | `0x00000000` |
    | xe49 | `0x0f13201a` | `0x00000000` |
    | xe50 | `0x0f13301a` | `0x00000000` |
    | xe51 | `0x0f13401a` | `0x00000000` |
    | lb0 | `0x0f14101a` | `0x00000000` |

---

## ING_TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDEDr

- **Address:** `0x0f10001b`  ·  **Size:** 4 bytes
- **Function:** Number of TRILL frames dropped on an incoming TRILL access port.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001b` | `0x00000000` |
    | xe0 | `0x0f10101b` | `0x00000000` |
    | xe1 | `0x0f10201b` | `0x00000000` |
    | xe2 | `0x0f10301b` | `0x00000000` |
    | xe3 | `0x0f10401b` | `0x00000000` |
    | xe4 | `0x0f10501b` | `0x00000000` |
    | xe5 | `0x0f10601b` | `0x00000000` |
    | xe6 | `0x0f10701b` | `0x00000000` |
    | xe7 | `0x0f10801b` | `0x00000000` |
    | xe8 | `0x0f10901b` | `0x00000000` |
    | xe9 | `0x0f10a01b` | `0x00000000` |
    | xe10 | `0x0f10b01b` | `0x00000000` |
    | xe11 | `0x0f10c01b` | `0x00000000` |
    | xe12 | `0x0f10d01b` | `0x00000000` |
    | xe13 | `0x0f10e01b` | `0x00000000` |
    | xe14 | `0x0f10f01b` | `0x00000000` |
    | xe15 | `0x0f11001b` | `0x00000000` |
    | xe16 | `0x0f11101b` | `0x00000000` |
    | xe17 | `0x0f11201b` | `0x00000000` |
    | xe18 | `0x0f11301b` | `0x00000000` |
    | xe19 | `0x0f11401b` | `0x00000000` |
    | xe20 | `0x0f11501b` | `0x00000000` |
    | xe21 | `0x0f11601b` | `0x00000000` |
    | xe22 | `0x0f11701b` | `0x00000000` |
    | xe23 | `0x0f11801b` | `0x00000000` |
    | xe24 | `0x0f11901b` | `0x00000000` |
    | xe25 | `0x0f11a01b` | `0x00000000` |
    | xe26 | `0x0f11b01b` | `0x00000000` |
    | xe27 | `0x0f11c01b` | `0x00000000` |
    | xe28 | `0x0f11d01b` | `0x00000000` |
    | xe29 | `0x0f11e01b` | `0x00000000` |
    | xe30 | `0x0f11f01b` | `0x00000000` |
    | xe31 | `0x0f12001b` | `0x00000000` |
    | xe32 | `0x0f12101b` | `0x00000000` |
    | xe33 | `0x0f12201b` | `0x00000000` |
    | xe34 | `0x0f12301b` | `0x00000000` |
    | xe35 | `0x0f12401b` | `0x00000000` |
    | xe36 | `0x0f12501b` | `0x00000000` |
    | xe37 | `0x0f12601b` | `0x00000000` |
    | xe38 | `0x0f12701b` | `0x00000000` |
    | xe39 | `0x0f12801b` | `0x00000000` |
    | xe40 | `0x0f12901b` | `0x00000000` |
    | xe41 | `0x0f12a01b` | `0x00000000` |
    | xe42 | `0x0f12b01b` | `0x00000000` |
    | xe43 | `0x0f12c01b` | `0x00000000` |
    | xe44 | `0x0f12d01b` | `0x00000000` |
    | xe45 | `0x0f12e01b` | `0x00000000` |
    | xe46 | `0x0f12f01b` | `0x00000000` |
    | xe47 | `0x0f13001b` | `0x00000000` |
    | xe48 | `0x0f13101b` | `0x00000000` |
    | xe49 | `0x0f13201b` | `0x00000000` |
    | xe50 | `0x0f13301b` | `0x00000000` |
    | xe51 | `0x0f13401b` | `0x00000000` |
    | lb0 | `0x0f14101b` | `0x00000000` |

---

## ING_TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDEDr

- **Address:** `0x0f10001c`  ·  **Size:** 4 bytes
- **Function:** Number of non-TRILL frames dropped on an incoming TRILL network port.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001c` | `0x00000000` |
    | xe0 | `0x0f10101c` | `0x00000000` |
    | xe1 | `0x0f10201c` | `0x00000000` |
    | xe2 | `0x0f10301c` | `0x00000000` |
    | xe3 | `0x0f10401c` | `0x00000000` |
    | xe4 | `0x0f10501c` | `0x00000000` |
    | xe5 | `0x0f10601c` | `0x00000000` |
    | xe6 | `0x0f10701c` | `0x00000000` |
    | xe7 | `0x0f10801c` | `0x00000000` |
    | xe8 | `0x0f10901c` | `0x00000000` |
    | xe9 | `0x0f10a01c` | `0x00000000` |
    | xe10 | `0x0f10b01c` | `0x00000000` |
    | xe11 | `0x0f10c01c` | `0x00000000` |
    | xe12 | `0x0f10d01c` | `0x00000000` |
    | xe13 | `0x0f10e01c` | `0x00000000` |
    | xe14 | `0x0f10f01c` | `0x00000000` |
    | xe15 | `0x0f11001c` | `0x00000000` |
    | xe16 | `0x0f11101c` | `0x00000000` |
    | xe17 | `0x0f11201c` | `0x00000000` |
    | xe18 | `0x0f11301c` | `0x00000000` |
    | xe19 | `0x0f11401c` | `0x00000000` |
    | xe20 | `0x0f11501c` | `0x00000000` |
    | xe21 | `0x0f11601c` | `0x00000000` |
    | xe22 | `0x0f11701c` | `0x00000000` |
    | xe23 | `0x0f11801c` | `0x00000000` |
    | xe24 | `0x0f11901c` | `0x00000000` |
    | xe25 | `0x0f11a01c` | `0x00000000` |
    | xe26 | `0x0f11b01c` | `0x00000000` |
    | xe27 | `0x0f11c01c` | `0x00000000` |
    | xe28 | `0x0f11d01c` | `0x00000000` |
    | xe29 | `0x0f11e01c` | `0x00000000` |
    | xe30 | `0x0f11f01c` | `0x00000000` |
    | xe31 | `0x0f12001c` | `0x00000000` |
    | xe32 | `0x0f12101c` | `0x00000000` |
    | xe33 | `0x0f12201c` | `0x00000000` |
    | xe34 | `0x0f12301c` | `0x00000000` |
    | xe35 | `0x0f12401c` | `0x00000000` |
    | xe36 | `0x0f12501c` | `0x00000000` |
    | xe37 | `0x0f12601c` | `0x00000000` |
    | xe38 | `0x0f12701c` | `0x00000000` |
    | xe39 | `0x0f12801c` | `0x00000000` |
    | xe40 | `0x0f12901c` | `0x00000000` |
    | xe41 | `0x0f12a01c` | `0x00000000` |
    | xe42 | `0x0f12b01c` | `0x00000000` |
    | xe43 | `0x0f12c01c` | `0x00000000` |
    | xe44 | `0x0f12d01c` | `0x00000000` |
    | xe45 | `0x0f12e01c` | `0x00000000` |
    | xe46 | `0x0f12f01c` | `0x00000000` |
    | xe47 | `0x0f13001c` | `0x00000000` |
    | xe48 | `0x0f13101c` | `0x00000000` |
    | xe49 | `0x0f13201c` | `0x00000000` |
    | xe50 | `0x0f13301c` | `0x00000000` |
    | xe51 | `0x0f13401c` | `0x00000000` |
    | lb0 | `0x0f14101c` | `0x00000000` |

---

## ING_NIV_RX_FRAMES_ERROR_DROPr

- **Address:** `0x0f10001d`  ·  **Size:** 4 bytes
- **Function:** Number of frames dropped due to VNTAG format errors.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001d` | `0x00000000` |
    | xe0 | `0x0f10101d` | `0x00000000` |
    | xe1 | `0x0f10201d` | `0x00000000` |
    | xe2 | `0x0f10301d` | `0x00000000` |
    | xe3 | `0x0f10401d` | `0x00000000` |
    | xe4 | `0x0f10501d` | `0x00000000` |
    | xe5 | `0x0f10601d` | `0x00000000` |
    | xe6 | `0x0f10701d` | `0x00000000` |
    | xe7 | `0x0f10801d` | `0x00000000` |
    | xe8 | `0x0f10901d` | `0x00000000` |
    | xe9 | `0x0f10a01d` | `0x00000000` |
    | xe10 | `0x0f10b01d` | `0x00000000` |
    | xe11 | `0x0f10c01d` | `0x00000000` |
    | xe12 | `0x0f10d01d` | `0x00000000` |
    | xe13 | `0x0f10e01d` | `0x00000000` |
    | xe14 | `0x0f10f01d` | `0x00000000` |
    | xe15 | `0x0f11001d` | `0x00000000` |
    | xe16 | `0x0f11101d` | `0x00000000` |
    | xe17 | `0x0f11201d` | `0x00000000` |
    | xe18 | `0x0f11301d` | `0x00000000` |
    | xe19 | `0x0f11401d` | `0x00000000` |
    | xe20 | `0x0f11501d` | `0x00000000` |
    | xe21 | `0x0f11601d` | `0x00000000` |
    | xe22 | `0x0f11701d` | `0x00000000` |
    | xe23 | `0x0f11801d` | `0x00000000` |
    | xe24 | `0x0f11901d` | `0x00000000` |
    | xe25 | `0x0f11a01d` | `0x00000000` |
    | xe26 | `0x0f11b01d` | `0x00000000` |
    | xe27 | `0x0f11c01d` | `0x00000000` |
    | xe28 | `0x0f11d01d` | `0x00000000` |
    | xe29 | `0x0f11e01d` | `0x00000000` |
    | xe30 | `0x0f11f01d` | `0x00000000` |
    | xe31 | `0x0f12001d` | `0x00000000` |
    | xe32 | `0x0f12101d` | `0x00000000` |
    | xe33 | `0x0f12201d` | `0x00000000` |
    | xe34 | `0x0f12301d` | `0x00000000` |
    | xe35 | `0x0f12401d` | `0x00000000` |
    | xe36 | `0x0f12501d` | `0x00000000` |
    | xe37 | `0x0f12601d` | `0x00000000` |
    | xe38 | `0x0f12701d` | `0x00000000` |
    | xe39 | `0x0f12801d` | `0x00000000` |
    | xe40 | `0x0f12901d` | `0x00000000` |
    | xe41 | `0x0f12a01d` | `0x00000000` |
    | xe42 | `0x0f12b01d` | `0x00000000` |
    | xe43 | `0x0f12c01d` | `0x00000000` |
    | xe44 | `0x0f12d01d` | `0x00000000` |
    | xe45 | `0x0f12e01d` | `0x00000000` |
    | xe46 | `0x0f12f01d` | `0x00000000` |
    | xe47 | `0x0f13001d` | `0x00000000` |
    | xe48 | `0x0f13101d` | `0x00000000` |
    | xe49 | `0x0f13201d` | `0x00000000` |
    | xe50 | `0x0f13301d` | `0x00000000` |
    | xe51 | `0x0f13401d` | `0x00000000` |
    | lb0 | `0x0f14101d` | `0x00000000` |

---

## ING_NIV_RX_FRAMES_FORWARDING_DROPr

- **Address:** `0x0f10001e`  ·  **Size:** 4 bytes
- **Function:** Number of frames dropped due to an NIV forwarding errors.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001e` | `0x00000000` |
    | xe0 | `0x0f10101e` | `0x00000000` |
    | xe1 | `0x0f10201e` | `0x00000000` |
    | xe2 | `0x0f10301e` | `0x00000000` |
    | xe3 | `0x0f10401e` | `0x00000000` |
    | xe4 | `0x0f10501e` | `0x00000000` |
    | xe5 | `0x0f10601e` | `0x00000000` |
    | xe6 | `0x0f10701e` | `0x00000000` |
    | xe7 | `0x0f10801e` | `0x00000000` |
    | xe8 | `0x0f10901e` | `0x00000000` |
    | xe9 | `0x0f10a01e` | `0x00000000` |
    | xe10 | `0x0f10b01e` | `0x00000000` |
    | xe11 | `0x0f10c01e` | `0x00000000` |
    | xe12 | `0x0f10d01e` | `0x00000000` |
    | xe13 | `0x0f10e01e` | `0x00000000` |
    | xe14 | `0x0f10f01e` | `0x00000000` |
    | xe15 | `0x0f11001e` | `0x00000000` |
    | xe16 | `0x0f11101e` | `0x00000000` |
    | xe17 | `0x0f11201e` | `0x00000000` |
    | xe18 | `0x0f11301e` | `0x00000000` |
    | xe19 | `0x0f11401e` | `0x00000000` |
    | xe20 | `0x0f11501e` | `0x00000000` |
    | xe21 | `0x0f11601e` | `0x00000000` |
    | xe22 | `0x0f11701e` | `0x00000000` |
    | xe23 | `0x0f11801e` | `0x00000000` |
    | xe24 | `0x0f11901e` | `0x00000000` |
    | xe25 | `0x0f11a01e` | `0x00000000` |
    | xe26 | `0x0f11b01e` | `0x00000000` |
    | xe27 | `0x0f11c01e` | `0x00000000` |
    | xe28 | `0x0f11d01e` | `0x00000000` |
    | xe29 | `0x0f11e01e` | `0x00000000` |
    | xe30 | `0x0f11f01e` | `0x00000000` |
    | xe31 | `0x0f12001e` | `0x00000000` |
    | xe32 | `0x0f12101e` | `0x00000000` |
    | xe33 | `0x0f12201e` | `0x00000000` |
    | xe34 | `0x0f12301e` | `0x00000000` |
    | xe35 | `0x0f12401e` | `0x00000000` |
    | xe36 | `0x0f12501e` | `0x00000000` |
    | xe37 | `0x0f12601e` | `0x00000000` |
    | xe38 | `0x0f12701e` | `0x00000000` |
    | xe39 | `0x0f12801e` | `0x00000000` |
    | xe40 | `0x0f12901e` | `0x00000000` |
    | xe41 | `0x0f12a01e` | `0x00000000` |
    | xe42 | `0x0f12b01e` | `0x00000000` |
    | xe43 | `0x0f12c01e` | `0x00000000` |
    | xe44 | `0x0f12d01e` | `0x00000000` |
    | xe45 | `0x0f12e01e` | `0x00000000` |
    | xe46 | `0x0f12f01e` | `0x00000000` |
    | xe47 | `0x0f13001e` | `0x00000000` |
    | xe48 | `0x0f13101e` | `0x00000000` |
    | xe49 | `0x0f13201e` | `0x00000000` |
    | xe50 | `0x0f13301e` | `0x00000000` |
    | xe51 | `0x0f13401e` | `0x00000000` |
    | lb0 | `0x0f14101e` | `0x00000000` |

---

## ING_NIV_RX_FRAMES_VLAN_TAGGEDr

- **Address:** `0x0f10001f`  ·  **Size:** 4 bytes
- **Function:** Number of VLAN tagged packets received from this port.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | COUNT |
    | `[26]` | EVEN_PARITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f10001f` | `0x00000000` |
    | xe0 | `0x0f10101f` | `0x00000000` |
    | xe1 | `0x0f10201f` | `0x00000000` |
    | xe2 | `0x0f10301f` | `0x00000000` |
    | xe3 | `0x0f10401f` | `0x00000000` |
    | xe4 | `0x0f10501f` | `0x00000000` |
    | xe5 | `0x0f10601f` | `0x00000000` |
    | xe6 | `0x0f10701f` | `0x00000000` |
    | xe7 | `0x0f10801f` | `0x00000000` |
    | xe8 | `0x0f10901f` | `0x00000000` |
    | xe9 | `0x0f10a01f` | `0x00000000` |
    | xe10 | `0x0f10b01f` | `0x00000000` |
    | xe11 | `0x0f10c01f` | `0x00000000` |
    | xe12 | `0x0f10d01f` | `0x00000000` |
    | xe13 | `0x0f10e01f` | `0x00000000` |
    | xe14 | `0x0f10f01f` | `0x00000000` |
    | xe15 | `0x0f11001f` | `0x00000000` |
    | xe16 | `0x0f11101f` | `0x00000000` |
    | xe17 | `0x0f11201f` | `0x00000000` |
    | xe18 | `0x0f11301f` | `0x00000000` |
    | xe19 | `0x0f11401f` | `0x00000000` |
    | xe20 | `0x0f11501f` | `0x00000000` |
    | xe21 | `0x0f11601f` | `0x00000000` |
    | xe22 | `0x0f11701f` | `0x00000000` |
    | xe23 | `0x0f11801f` | `0x00000000` |
    | xe24 | `0x0f11901f` | `0x00000000` |
    | xe25 | `0x0f11a01f` | `0x00000000` |
    | xe26 | `0x0f11b01f` | `0x00000000` |
    | xe27 | `0x0f11c01f` | `0x00000000` |
    | xe28 | `0x0f11d01f` | `0x00000000` |
    | xe29 | `0x0f11e01f` | `0x00000000` |
    | xe30 | `0x0f11f01f` | `0x00000000` |
    | xe31 | `0x0f12001f` | `0x00000000` |
    | xe32 | `0x0f12101f` | `0x00000000` |
    | xe33 | `0x0f12201f` | `0x00000000` |
    | xe34 | `0x0f12301f` | `0x00000000` |
    | xe35 | `0x0f12401f` | `0x00000000` |
    | xe36 | `0x0f12501f` | `0x00000000` |
    | xe37 | `0x0f12601f` | `0x00000000` |
    | xe38 | `0x0f12701f` | `0x00000000` |
    | xe39 | `0x0f12801f` | `0x00000000` |
    | xe40 | `0x0f12901f` | `0x00000000` |
    | xe41 | `0x0f12a01f` | `0x00000000` |
    | xe42 | `0x0f12b01f` | `0x00000000` |
    | xe43 | `0x0f12c01f` | `0x00000000` |
    | xe44 | `0x0f12d01f` | `0x00000000` |
    | xe45 | `0x0f12e01f` | `0x00000000` |
    | xe46 | `0x0f12f01f` | `0x00000000` |
    | xe47 | `0x0f13001f` | `0x00000000` |
    | xe48 | `0x0f13101f` | `0x00000000` |
    | xe49 | `0x0f13201f` | `0x00000000` |
    | xe50 | `0x0f13301f` | `0x00000000` |
    | xe51 | `0x0f13401f` | `0x00000000` |
    | lb0 | `0x0f14101f` | `0x00000000` |

---

## SFLOW_ING_THRESHOLDr

- **Address:** `0x0f100660`  ·  **Size:** 4 bytes
- **Function:** sFlow Ingress Threshold Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[23:0]` | THRESHOLD |
    | `[24]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100660` | `0x00000000` |
    | xe0 | `0x0f101660` | `0x00000000` |
    | xe1 | `0x0f102660` | `0x00000000` |
    | xe2 | `0x0f103660` | `0x00000000` |
    | xe3 | `0x0f104660` | `0x00000000` |
    | xe4 | `0x0f105660` | `0x00000000` |
    | xe5 | `0x0f106660` | `0x00000000` |
    | xe6 | `0x0f107660` | `0x00000000` |
    | xe7 | `0x0f108660` | `0x00000000` |
    | xe8 | `0x0f109660` | `0x00000000` |
    | xe9 | `0x0f10a660` | `0x00000000` |
    | xe10 | `0x0f10b660` | `0x00000000` |
    | xe11 | `0x0f10c660` | `0x00000000` |
    | xe12 | `0x0f10d660` | `0x00000000` |
    | xe13 | `0x0f10e660` | `0x00000000` |
    | xe14 | `0x0f10f660` | `0x00000000` |
    | xe15 | `0x0f110660` | `0x00000000` |
    | xe16 | `0x0f111660` | `0x00000000` |
    | xe17 | `0x0f112660` | `0x00000000` |
    | xe18 | `0x0f113660` | `0x00000000` |
    | xe19 | `0x0f114660` | `0x00000000` |
    | xe20 | `0x0f115660` | `0x00000000` |
    | xe21 | `0x0f116660` | `0x00000000` |
    | xe22 | `0x0f117660` | `0x00000000` |
    | xe23 | `0x0f118660` | `0x00000000` |
    | xe24 | `0x0f119660` | `0x00000000` |
    | xe25 | `0x0f11a660` | `0x00000000` |
    | xe26 | `0x0f11b660` | `0x00000000` |
    | xe27 | `0x0f11c660` | `0x00000000` |
    | xe28 | `0x0f11d660` | `0x00000000` |
    | xe29 | `0x0f11e660` | `0x00000000` |
    | xe30 | `0x0f11f660` | `0x00000000` |
    | xe31 | `0x0f120660` | `0x00000000` |
    | xe32 | `0x0f121660` | `0x00000000` |
    | xe33 | `0x0f122660` | `0x00000000` |
    | xe34 | `0x0f123660` | `0x00000000` |
    | xe35 | `0x0f124660` | `0x00000000` |
    | xe36 | `0x0f125660` | `0x00000000` |
    | xe37 | `0x0f126660` | `0x00000000` |
    | xe38 | `0x0f127660` | `0x00000000` |
    | xe39 | `0x0f128660` | `0x00000000` |
    | xe40 | `0x0f129660` | `0x00000000` |
    | xe41 | `0x0f12a660` | `0x00000000` |
    | xe42 | `0x0f12b660` | `0x00000000` |
    | xe43 | `0x0f12c660` | `0x00000000` |
    | xe44 | `0x0f12d660` | `0x00000000` |
    | xe45 | `0x0f12e660` | `0x00000000` |
    | xe46 | `0x0f12f660` | `0x00000000` |
    | xe47 | `0x0f130660` | `0x00000000` |
    | xe48 | `0x0f131660` | `0x00000000` |
    | xe49 | `0x0f132660` | `0x00000000` |
    | xe50 | `0x0f133660` | `0x00000000` |
    | xe51 | `0x0f134660` | `0x00000000` |
    | lb0 | `0x0f141660` | `0x00000000` |

---

## SFLOW_EGR_THRESHOLDr

- **Address:** `0x0f100661`  ·  **Size:** 4 bytes
- **Function:** sFlow Egress Threshold Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[23:0]` | THRESHOLD |
    | `[24]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100661` | `0x00000000` |
    | xe0 | `0x0f101661` | `0x00000000` |
    | xe1 | `0x0f102661` | `0x00000000` |
    | xe2 | `0x0f103661` | `0x00000000` |
    | xe3 | `0x0f104661` | `0x00000000` |
    | xe4 | `0x0f105661` | `0x00000000` |
    | xe5 | `0x0f106661` | `0x00000000` |
    | xe6 | `0x0f107661` | `0x00000000` |
    | xe7 | `0x0f108661` | `0x00000000` |
    | xe8 | `0x0f109661` | `0x00000000` |
    | xe9 | `0x0f10a661` | `0x00000000` |
    | xe10 | `0x0f10b661` | `0x00000000` |
    | xe11 | `0x0f10c661` | `0x00000000` |
    | xe12 | `0x0f10d661` | `0x00000000` |
    | xe13 | `0x0f10e661` | `0x00000000` |
    | xe14 | `0x0f10f661` | `0x00000000` |
    | xe15 | `0x0f110661` | `0x00000000` |
    | xe16 | `0x0f111661` | `0x00000000` |
    | xe17 | `0x0f112661` | `0x00000000` |
    | xe18 | `0x0f113661` | `0x00000000` |
    | xe19 | `0x0f114661` | `0x00000000` |
    | xe20 | `0x0f115661` | `0x00000000` |
    | xe21 | `0x0f116661` | `0x00000000` |
    | xe22 | `0x0f117661` | `0x00000000` |
    | xe23 | `0x0f118661` | `0x00000000` |
    | xe24 | `0x0f119661` | `0x00000000` |
    | xe25 | `0x0f11a661` | `0x00000000` |
    | xe26 | `0x0f11b661` | `0x00000000` |
    | xe27 | `0x0f11c661` | `0x00000000` |
    | xe28 | `0x0f11d661` | `0x00000000` |
    | xe29 | `0x0f11e661` | `0x00000000` |
    | xe30 | `0x0f11f661` | `0x00000000` |
    | xe31 | `0x0f120661` | `0x00000000` |
    | xe32 | `0x0f121661` | `0x00000000` |
    | xe33 | `0x0f122661` | `0x00000000` |
    | xe34 | `0x0f123661` | `0x00000000` |
    | xe35 | `0x0f124661` | `0x00000000` |
    | xe36 | `0x0f125661` | `0x00000000` |
    | xe37 | `0x0f126661` | `0x00000000` |
    | xe38 | `0x0f127661` | `0x00000000` |
    | xe39 | `0x0f128661` | `0x00000000` |
    | xe40 | `0x0f129661` | `0x00000000` |
    | xe41 | `0x0f12a661` | `0x00000000` |
    | xe42 | `0x0f12b661` | `0x00000000` |
    | xe43 | `0x0f12c661` | `0x00000000` |
    | xe44 | `0x0f12d661` | `0x00000000` |
    | xe45 | `0x0f12e661` | `0x00000000` |
    | xe46 | `0x0f12f661` | `0x00000000` |
    | xe47 | `0x0f130661` | `0x00000000` |
    | xe48 | `0x0f131661` | `0x00000000` |
    | xe49 | `0x0f132661` | `0x00000000` |
    | xe50 | `0x0f133661` | `0x00000000` |
    | xe51 | `0x0f134661` | `0x00000000` |
    | lb0 | `0x0f141661` | `0x00000000` |

---

## MODPORT_MAP_SELr

- **Address:** `0x0f100665`  ·  **Size:** 4 bytes
- **Function:** Selects one of 16 MODPORT_MAP Tables

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | MODPORT_MAP_INDEX_UPPER |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100665` | `0x00000000` |
    | xe0 | `0x0f101665` | `0x00000000` |
    | xe1 | `0x0f102665` | `0x00000000` |
    | xe2 | `0x0f103665` | `0x00000000` |
    | xe3 | `0x0f104665` | `0x00000000` |
    | xe4 | `0x0f105665` | `0x00000000` |
    | xe5 | `0x0f106665` | `0x00000000` |
    | xe6 | `0x0f107665` | `0x00000000` |
    | xe7 | `0x0f108665` | `0x00000000` |
    | xe8 | `0x0f109665` | `0x00000000` |
    | xe9 | `0x0f10a665` | `0x00000000` |
    | xe10 | `0x0f10b665` | `0x00000000` |
    | xe11 | `0x0f10c665` | `0x00000000` |
    | xe12 | `0x0f10d665` | `0x00000000` |
    | xe13 | `0x0f10e665` | `0x00000000` |
    | xe14 | `0x0f10f665` | `0x00000000` |
    | xe15 | `0x0f110665` | `0x00000000` |
    | xe16 | `0x0f111665` | `0x00000000` |
    | xe17 | `0x0f112665` | `0x00000000` |
    | xe18 | `0x0f113665` | `0x00000000` |
    | xe19 | `0x0f114665` | `0x00000000` |
    | xe20 | `0x0f115665` | `0x00000000` |
    | xe21 | `0x0f116665` | `0x00000000` |
    | xe22 | `0x0f117665` | `0x00000000` |
    | xe23 | `0x0f118665` | `0x00000000` |
    | xe24 | `0x0f119665` | `0x00000000` |
    | xe25 | `0x0f11a665` | `0x00000000` |
    | xe26 | `0x0f11b665` | `0x00000000` |
    | xe27 | `0x0f11c665` | `0x00000000` |
    | xe28 | `0x0f11d665` | `0x00000000` |
    | xe29 | `0x0f11e665` | `0x00000000` |
    | xe30 | `0x0f11f665` | `0x00000000` |
    | xe31 | `0x0f120665` | `0x00000000` |
    | xe32 | `0x0f121665` | `0x00000000` |
    | xe33 | `0x0f122665` | `0x00000000` |
    | xe34 | `0x0f123665` | `0x00000000` |
    | xe35 | `0x0f124665` | `0x00000000` |
    | xe36 | `0x0f125665` | `0x00000000` |
    | xe37 | `0x0f126665` | `0x00000000` |
    | xe38 | `0x0f127665` | `0x00000000` |
    | xe39 | `0x0f128665` | `0x00000000` |
    | xe40 | `0x0f129665` | `0x00000000` |
    | xe41 | `0x0f12a665` | `0x00000000` |
    | xe42 | `0x0f12b665` | `0x00000000` |
    | xe43 | `0x0f12c665` | `0x00000000` |
    | xe44 | `0x0f12d665` | `0x00000000` |
    | xe45 | `0x0f12e665` | `0x00000000` |
    | xe46 | `0x0f12f665` | `0x00000000` |
    | xe47 | `0x0f130665` | `0x00000000` |
    | xe48 | `0x0f131665` | `0x00000000` |
    | xe49 | `0x0f132665` | `0x00000000` |
    | xe50 | `0x0f133665` | `0x00000000` |
    | xe51 | `0x0f134665` | `0x00000000` |
    | lb0 | `0x0f141665` | `0x00000000` |

---

## LOCAL_SW_DISABLE_CTRLr

- **Address:** `0x0f100666`  ·  **Size:** 4 bytes
- **Function:** Selects one of 16 MODPORT_MAP Tables

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | SW_MODE |
    | `[2]` | IM_MODE |
    | `[3]` | EM_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100666` | `0x00000000` |
    | xe0 | `0x0f101666` | `0x00000000` |
    | xe1 | `0x0f102666` | `0x00000000` |
    | xe2 | `0x0f103666` | `0x00000000` |
    | xe3 | `0x0f104666` | `0x00000000` |
    | xe4 | `0x0f105666` | `0x00000000` |
    | xe5 | `0x0f106666` | `0x00000000` |
    | xe6 | `0x0f107666` | `0x00000000` |
    | xe7 | `0x0f108666` | `0x00000000` |
    | xe8 | `0x0f109666` | `0x00000000` |
    | xe9 | `0x0f10a666` | `0x00000000` |
    | xe10 | `0x0f10b666` | `0x00000000` |
    | xe11 | `0x0f10c666` | `0x00000000` |
    | xe12 | `0x0f10d666` | `0x00000000` |
    | xe13 | `0x0f10e666` | `0x00000000` |
    | xe14 | `0x0f10f666` | `0x00000000` |
    | xe15 | `0x0f110666` | `0x00000000` |
    | xe16 | `0x0f111666` | `0x00000000` |
    | xe17 | `0x0f112666` | `0x00000000` |
    | xe18 | `0x0f113666` | `0x00000000` |
    | xe19 | `0x0f114666` | `0x00000000` |
    | xe20 | `0x0f115666` | `0x00000000` |
    | xe21 | `0x0f116666` | `0x00000000` |
    | xe22 | `0x0f117666` | `0x00000000` |
    | xe23 | `0x0f118666` | `0x00000000` |
    | xe24 | `0x0f119666` | `0x00000000` |
    | xe25 | `0x0f11a666` | `0x00000000` |
    | xe26 | `0x0f11b666` | `0x00000000` |
    | xe27 | `0x0f11c666` | `0x00000000` |
    | xe28 | `0x0f11d666` | `0x00000000` |
    | xe29 | `0x0f11e666` | `0x00000000` |
    | xe30 | `0x0f11f666` | `0x00000000` |
    | xe31 | `0x0f120666` | `0x00000000` |
    | xe32 | `0x0f121666` | `0x00000000` |
    | xe33 | `0x0f122666` | `0x00000000` |
    | xe34 | `0x0f123666` | `0x00000000` |
    | xe35 | `0x0f124666` | `0x00000000` |
    | xe36 | `0x0f125666` | `0x00000000` |
    | xe37 | `0x0f126666` | `0x00000000` |
    | xe38 | `0x0f127666` | `0x00000000` |
    | xe39 | `0x0f128666` | `0x00000000` |
    | xe40 | `0x0f129666` | `0x00000000` |
    | xe41 | `0x0f12a666` | `0x00000000` |
    | xe42 | `0x0f12b666` | `0x00000000` |
    | xe43 | `0x0f12c666` | `0x00000000` |
    | xe44 | `0x0f12d666` | `0x00000000` |
    | xe45 | `0x0f12e666` | `0x00000000` |
    | xe46 | `0x0f12f666` | `0x00000000` |
    | xe47 | `0x0f130666` | `0x00000000` |
    | xe48 | `0x0f131666` | `0x00000000` |
    | xe49 | `0x0f132666` | `0x00000000` |
    | xe50 | `0x0f133666` | `0x00000000` |
    | xe51 | `0x0f134666` | `0x00000000` |
    | lb0 | `0x0f141666` | `0x00000000` |

---

## SRC_MODID_EGRESS_SELr

- **Address:** `0x0f100668`  ·  **Size:** 4 bytes
- **Function:** Selects one of 8 SRC_MODID_EGRESS Tables

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SRCMOD_INDEX |
    | `[3]` | ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100668` | `0x00000000` |
    | xe0 | `0x0f101668` | `0x00000000` |
    | xe1 | `0x0f102668` | `0x00000000` |
    | xe2 | `0x0f103668` | `0x00000000` |
    | xe3 | `0x0f104668` | `0x00000000` |
    | xe4 | `0x0f105668` | `0x00000000` |
    | xe5 | `0x0f106668` | `0x00000000` |
    | xe6 | `0x0f107668` | `0x00000000` |
    | xe7 | `0x0f108668` | `0x00000000` |
    | xe8 | `0x0f109668` | `0x00000000` |
    | xe9 | `0x0f10a668` | `0x00000000` |
    | xe10 | `0x0f10b668` | `0x00000000` |
    | xe11 | `0x0f10c668` | `0x00000000` |
    | xe12 | `0x0f10d668` | `0x00000000` |
    | xe13 | `0x0f10e668` | `0x00000000` |
    | xe14 | `0x0f10f668` | `0x00000000` |
    | xe15 | `0x0f110668` | `0x00000000` |
    | xe16 | `0x0f111668` | `0x00000000` |
    | xe17 | `0x0f112668` | `0x00000000` |
    | xe18 | `0x0f113668` | `0x00000000` |
    | xe19 | `0x0f114668` | `0x00000000` |
    | xe20 | `0x0f115668` | `0x00000000` |
    | xe21 | `0x0f116668` | `0x00000000` |
    | xe22 | `0x0f117668` | `0x00000000` |
    | xe23 | `0x0f118668` | `0x00000000` |
    | xe24 | `0x0f119668` | `0x00000000` |
    | xe25 | `0x0f11a668` | `0x00000000` |
    | xe26 | `0x0f11b668` | `0x00000000` |
    | xe27 | `0x0f11c668` | `0x00000000` |
    | xe28 | `0x0f11d668` | `0x00000000` |
    | xe29 | `0x0f11e668` | `0x00000000` |
    | xe30 | `0x0f11f668` | `0x00000000` |
    | xe31 | `0x0f120668` | `0x00000000` |
    | xe32 | `0x0f121668` | `0x00000000` |
    | xe33 | `0x0f122668` | `0x00000000` |
    | xe34 | `0x0f123668` | `0x00000000` |
    | xe35 | `0x0f124668` | `0x00000000` |
    | xe36 | `0x0f125668` | `0x00000000` |
    | xe37 | `0x0f126668` | `0x00000000` |
    | xe38 | `0x0f127668` | `0x00000000` |
    | xe39 | `0x0f128668` | `0x00000000` |
    | xe40 | `0x0f129668` | `0x00000000` |
    | xe41 | `0x0f12a668` | `0x00000000` |
    | xe42 | `0x0f12b668` | `0x00000000` |
    | xe43 | `0x0f12c668` | `0x00000000` |
    | xe44 | `0x0f12d668` | `0x00000000` |
    | xe45 | `0x0f12e668` | `0x00000000` |
    | xe46 | `0x0f12f668` | `0x00000000` |
    | xe47 | `0x0f130668` | `0x00000000` |
    | xe48 | `0x0f131668` | `0x00000000` |
    | xe49 | `0x0f132668` | `0x00000000` |
    | xe50 | `0x0f133668` | `0x00000000` |
    | xe51 | `0x0f134668` | `0x00000000` |
    | lb0 | `0x0f141668` | `0x00000000` |

---

## ING_COS_MODEr

- **Address:** `0x0f100677`  ·  **Size:** 4 bytes
- **Function:** Index by egress port, COS mode select - must be programmed the same way as MMUs COS_MODE register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | COS_MODE |
    | `[2:1]` | QUEUE_MODE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f100677` | `0x00000000` |
    | xe0 | `0x0f101677` | `0x00000000` |
    | xe1 | `0x0f102677` | `0x00000000` |
    | xe2 | `0x0f103677` | `0x00000000` |
    | xe3 | `0x0f104677` | `0x00000000` |
    | xe4 | `0x0f105677` | `0x00000000` |
    | xe5 | `0x0f106677` | `0x00000000` |
    | xe6 | `0x0f107677` | `0x00000000` |
    | xe7 | `0x0f108677` | `0x00000000` |
    | xe8 | `0x0f109677` | `0x00000000` |
    | xe9 | `0x0f10a677` | `0x00000000` |
    | xe10 | `0x0f10b677` | `0x00000000` |
    | xe11 | `0x0f10c677` | `0x00000000` |
    | xe12 | `0x0f10d677` | `0x00000000` |
    | xe13 | `0x0f10e677` | `0x00000000` |
    | xe14 | `0x0f10f677` | `0x00000000` |
    | xe15 | `0x0f110677` | `0x00000000` |
    | xe16 | `0x0f111677` | `0x00000000` |
    | xe17 | `0x0f112677` | `0x00000000` |
    | xe18 | `0x0f113677` | `0x00000000` |
    | xe19 | `0x0f114677` | `0x00000000` |
    | xe20 | `0x0f115677` | `0x00000000` |
    | xe21 | `0x0f116677` | `0x00000000` |
    | xe22 | `0x0f117677` | `0x00000000` |
    | xe23 | `0x0f118677` | `0x00000000` |
    | xe24 | `0x0f119677` | `0x00000000` |
    | xe25 | `0x0f11a677` | `0x00000000` |
    | xe26 | `0x0f11b677` | `0x00000000` |
    | xe27 | `0x0f11c677` | `0x00000000` |
    | xe28 | `0x0f11d677` | `0x00000000` |
    | xe29 | `0x0f11e677` | `0x00000000` |
    | xe30 | `0x0f11f677` | `0x00000000` |
    | xe31 | `0x0f120677` | `0x00000000` |
    | xe32 | `0x0f121677` | `0x00000000` |
    | xe33 | `0x0f122677` | `0x00000000` |
    | xe34 | `0x0f123677` | `0x00000000` |
    | xe35 | `0x0f124677` | `0x00000000` |
    | xe36 | `0x0f125677` | `0x00000000` |
    | xe37 | `0x0f126677` | `0x00000000` |
    | xe38 | `0x0f127677` | `0x00000000` |
    | xe39 | `0x0f128677` | `0x00000000` |
    | xe40 | `0x0f129677` | `0x00000000` |
    | xe41 | `0x0f12a677` | `0x00000000` |
    | xe42 | `0x0f12b677` | `0x00000000` |
    | xe43 | `0x0f12c677` | `0x00000000` |
    | xe44 | `0x0f12d677` | `0x00000000` |
    | xe45 | `0x0f12e677` | `0x00000000` |
    | xe46 | `0x0f12f677` | `0x00000000` |
    | xe47 | `0x0f130677` | `0x00000000` |
    | xe48 | `0x0f131677` | `0x00000000` |
    | xe49 | `0x0f132677` | `0x00000000` |
    | xe50 | `0x0f133677` | `0x00000000` |
    | xe51 | `0x0f134677` | `0x00000000` |
    | lb0 | `0x0f141677` | `0x00000000` |

---

## ING_MISC_PORT_CONFIGr

- **Address:** `0x0f1006a2`  ·  **Size:** 4 bytes
- **Function:** index by ingress port

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[31:1]` | RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x0f1006a2` | `0x00000000` |
    | xe0 | `0x0f1016a2` | `0x00000000` |
    | xe1 | `0x0f1026a2` | `0x00000000` |
    | xe2 | `0x0f1036a2` | `0x00000000` |
    | xe3 | `0x0f1046a2` | `0x00000000` |
    | xe4 | `0x0f1056a2` | `0x00000000` |
    | xe5 | `0x0f1066a2` | `0x00000000` |
    | xe6 | `0x0f1076a2` | `0x00000000` |
    | xe7 | `0x0f1086a2` | `0x00000000` |
    | xe8 | `0x0f1096a2` | `0x00000000` |
    | xe9 | `0x0f10a6a2` | `0x00000000` |
    | xe10 | `0x0f10b6a2` | `0x00000000` |
    | xe11 | `0x0f10c6a2` | `0x00000000` |
    | xe12 | `0x0f10d6a2` | `0x00000000` |
    | xe13 | `0x0f10e6a2` | `0x00000000` |
    | xe14 | `0x0f10f6a2` | `0x00000000` |
    | xe15 | `0x0f1106a2` | `0x00000000` |
    | xe16 | `0x0f1116a2` | `0x00000000` |
    | xe17 | `0x0f1126a2` | `0x00000000` |
    | xe18 | `0x0f1136a2` | `0x00000000` |
    | xe19 | `0x0f1146a2` | `0x00000000` |
    | xe20 | `0x0f1156a2` | `0x00000000` |
    | xe21 | `0x0f1166a2` | `0x00000000` |
    | xe22 | `0x0f1176a2` | `0x00000000` |
    | xe23 | `0x0f1186a2` | `0x00000000` |
    | xe24 | `0x0f1196a2` | `0x00000000` |
    | xe25 | `0x0f11a6a2` | `0x00000000` |
    | xe26 | `0x0f11b6a2` | `0x00000000` |
    | xe27 | `0x0f11c6a2` | `0x00000000` |
    | xe28 | `0x0f11d6a2` | `0x00000000` |
    | xe29 | `0x0f11e6a2` | `0x00000000` |
    | xe30 | `0x0f11f6a2` | `0x00000000` |
    | xe31 | `0x0f1206a2` | `0x00000000` |
    | xe32 | `0x0f1216a2` | `0x00000000` |
    | xe33 | `0x0f1226a2` | `0x00000000` |
    | xe34 | `0x0f1236a2` | `0x00000000` |
    | xe35 | `0x0f1246a2` | `0x00000000` |
    | xe36 | `0x0f1256a2` | `0x00000000` |
    | xe37 | `0x0f1266a2` | `0x00000000` |
    | xe38 | `0x0f1276a2` | `0x00000000` |
    | xe39 | `0x0f1286a2` | `0x00000000` |
    | xe40 | `0x0f1296a2` | `0x00000000` |
    | xe41 | `0x0f12a6a2` | `0x00000000` |
    | xe42 | `0x0f12b6a2` | `0x00000000` |
    | xe43 | `0x0f12c6a2` | `0x00000000` |
    | xe44 | `0x0f12d6a2` | `0x00000000` |
    | xe45 | `0x0f12e6a2` | `0x00000000` |
    | xe46 | `0x0f12f6a2` | `0x00000000` |
    | xe47 | `0x0f1306a2` | `0x00000000` |
    | xe48 | `0x0f1316a2` | `0x00000000` |
    | xe49 | `0x0f1326a2` | `0x00000000` |
    | xe50 | `0x0f1336a2` | `0x00000000` |
    | xe51 | `0x0f1346a2` | `0x00000000` |
    | lb0 | `0x0f1416a2` | `0x00000000` |

---

## E2E_DROP_COUNT_Xr

- **Address:** `0x0f180201`  ·  **Size:** 4 bytes
- **Function:** Counter for packets dropped due to E2EHOL drop status.

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180201` | `0x00000000` |

---

## ING_EVENT_DEBUG_Xr

- **Address:** `0x0f180263`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VXLT_MISS |
    | `[1]` | BPDU |
    | `[2]` | PROTOCOL_PKT |
    | `[3]` | CML |
    | `[4]` | SRC_ROUTE |
    | `[5]` | L2SRC_DISCARD |
    | `[6]` | L2SRC_STATIC_MOVE |
    | `[7]` | L2DST_DISCARD |
    | `[8]` | CFI_OR_L3DISABLE |
    | `[9]` | HIGIG_MH_TYPE1 |
    | `[10]` | DISC_STAGE |
    | `[11]` | SW1_INVALID_VLAN |
    | `[12]` | PDISC |
    | `[13]` | RFILDR |
    | `[14]` | RIMDR |
    | `[15]` | RDROP |
    | `[16]` | VFP |
    | `[17]` | RESERVED_1 |
    | `[18]` | DSL2HE |
    | `[19]` | DSL3HE |
    | `[20]` | DSL4HE |
    | `[21]` | DSICMP |
    | `[22]` | DSFRAG |
    | `[23]` | MTUERR |
    | `[24]` | RESERVED_0 |
    | `[25]` | RTUNE |
    | `[26]` | HG_FAILOVER_PORT_DOWN |
    | `[27]` | HGHDRE |
    | `[28]` | MCIDXE |
    | `[29]` | LAGLUP |
    | `[30]` | LAGLUPD |
    | `[31]` | PARITYD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180263` | `0x00000000` |

---

## ING_EVENT_DEBUG_2_Xr

- **Address:** `0x0f180268`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIGIG_HDR_ERROR |
    | `[1]` | LAG_FAILOVER |
    | `[2]` | MACSA0 |
    | `[3]` | VLAN_CC_OR_PBT |
    | `[4]` | CLASS_BASED_SM |
    | `[5]` | MAC_RATE_LIMIT |
    | `[6]` | MPLS_STAGE |
    | `[15:7]` | DROP_RESERVED |
    | `[16]` | VLANDR |
    | `[17]` | URPF |
    | `[18]` | DSTDISC |
    | `[19]` | RESERVED_0 |
    | `[21]` | TIME_SYNC_PACKET_DROP |
    | `[31:22]` | RDBGC_TRIGGER_RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180268` | `0x00000000` |

---

## E2E_DROP_COUNT_Yr

- **Address:** `0x0f180401`  ·  **Size:** 4 bytes
- **Function:** Counter for packets dropped due to E2EHOL drop status.

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180401` | `0x00000000` |

---

## ING_EVENT_DEBUG_Yr

- **Address:** `0x0f180463`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VXLT_MISS |
    | `[1]` | BPDU |
    | `[2]` | PROTOCOL_PKT |
    | `[3]` | CML |
    | `[4]` | SRC_ROUTE |
    | `[5]` | L2SRC_DISCARD |
    | `[6]` | L2SRC_STATIC_MOVE |
    | `[7]` | L2DST_DISCARD |
    | `[8]` | CFI_OR_L3DISABLE |
    | `[9]` | HIGIG_MH_TYPE1 |
    | `[10]` | DISC_STAGE |
    | `[11]` | SW1_INVALID_VLAN |
    | `[12]` | PDISC |
    | `[13]` | RFILDR |
    | `[14]` | RIMDR |
    | `[15]` | RDROP |
    | `[16]` | VFP |
    | `[17]` | RESERVED_1 |
    | `[18]` | DSL2HE |
    | `[19]` | DSL3HE |
    | `[20]` | DSL4HE |
    | `[21]` | DSICMP |
    | `[22]` | DSFRAG |
    | `[23]` | MTUERR |
    | `[24]` | RESERVED_0 |
    | `[25]` | RTUNE |
    | `[26]` | HG_FAILOVER_PORT_DOWN |
    | `[27]` | HGHDRE |
    | `[28]` | MCIDXE |
    | `[29]` | LAGLUP |
    | `[30]` | LAGLUPD |
    | `[31]` | PARITYD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180463` | `0x00000002` |

---

## ING_EVENT_DEBUG_2_Yr

- **Address:** `0x0f180468`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIGIG_HDR_ERROR |
    | `[1]` | LAG_FAILOVER |
    | `[2]` | MACSA0 |
    | `[3]` | VLAN_CC_OR_PBT |
    | `[4]` | CLASS_BASED_SM |
    | `[5]` | MAC_RATE_LIMIT |
    | `[6]` | MPLS_STAGE |
    | `[15:7]` | DROP_RESERVED |
    | `[16]` | VLANDR |
    | `[17]` | URPF |
    | `[18]` | DSTDISC |
    | `[19]` | RESERVED_0 |
    | `[21]` | TIME_SYNC_PACKET_DROP |
    | `[31:22]` | RDBGC_TRIGGER_RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180468` | `0x00000000` |

---

## RDBGC0_SELECTr

- **Address:** `0x0f180614`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #0 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180614` | `0x04000d11` |

---

## RDBGC1_SELECTr

- **Address:** `0x0f180615`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #1 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180615` | `0x00001000` |

---

## RDBGC2_SELECTr

- **Address:** `0x0f180616`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #2 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180616` | `0x00004000` |

---

## RDBGC3_SELECTr

- **Address:** `0x0f180617`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #3 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180617` | `0x00000011` |

---

## RDBGC4_SELECTr

- **Address:** `0x0f180618`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #4 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180618` | `0x00000100` |

---

## RDBGC5_SELECTr

- **Address:** `0x0f180619`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #5 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180619` | `0x00002000` |

---

## RDBGC6_SELECTr

- **Address:** `0x0f18061a`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #6 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f18061a` | `0x00008000` |

---

## RDBGC7_SELECTr

- **Address:** `0x0f18061b`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #7 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f18061b` | `0x00000000` |

---

## RDBGC8_SELECTr

- **Address:** `0x0f18061c`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter #8 Trigger Select Register

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f18061c` | `0x00000000` |

---

## RDBGC_SELECT_2r

- **Address:** `0x0f18061d`  ·  **Size:** 4 bytes
- **Function:** Receive debug counter Trigger Select Registers for conditions in counter vector past the first 32 bits, ie for bits [63:32]

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## SFLOW_ING_RAND_SEEDr

- **Address:** `0x0f180626`  ·  **Size:** 4 bytes
- **Function:** sFlow Ingress Random Number Generator Seed Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[24:0]` | SEED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180626` | `0x00000001` |

---

## SFLOW_EGR_RAND_SEEDr

- **Address:** `0x0f180627`  ·  **Size:** 4 bytes
- **Function:** sFlow Egress Random Number Generator Seed Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[24:0]` | SEED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180627` | `0x00000002` |

---

## RTAG7_HASH_HG_TRUNKr

- **Address:** `0x0f18064c`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for Higig trunking

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL_UC |
    | `[6:3]` | OFFSET_UC |
    | `[9:7]` | SUB_SEL_NONUC |
    | `[13:10]` | OFFSET_NONUC |

---

## RTAG7_HASH_PLFSr

- **Address:** `0x0f18064e`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for LAG failover

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL |
    | `[6:3]` | OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f18064e` | `0x00000000` |

---

## RTAG7_HASH_HG_TRUNK_FAILOVERr

- **Address:** `0x0f18064f`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for Higig trunk failover

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL |
    | `[6:3]` | OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f18064f` | `0x00000000` |

---

## ING_MISC_CONFIGr

- **Address:** `0x0f180658`  ·  **Size:** 4 bytes
- **Function:** Configuration bits that are needed in Isw2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | APPLY_EGR_MASK_ON_UC_ONLY |
    | `[1]` | APPLY_SRCMOD_BLOCK_ON_UC_ONLY |
    | `[2]` | DO_NOT_APPLY_SRCMOD_BLOCK_ON_SC |
    | `[3]` | DO_NOT_COPY_FROM_CPU_TO_CPU |
    | `[4]` | LOCAL_SW_DISABLE_HGTRUNK_RES_EN |
    | `[5]` | MPLS_SEQ_NUM_FAIL_TOCPU |
    | `[6]` | PWACH_TOCPU |
    | `[7]` | OTHER_CW_TYPE_TOCPU |
    | `[8]` | STG_CHECK_ENABLE |
    | `[9]` | QCN_DO_NOT_GENERATE_CNM_IF_NO_CNTAG |
    | `[10]` | NONUC_VLAN_SHAPING_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180658` | `0x00000000` |

---

## MIRROR_SELECTr

- **Address:** `0x0f180659`  ·  **Size:** 4 bytes
- **Function:** Mirror select register, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | MTP_TYPE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180659` | `0x00000000` |

---

## SW2_HW_CONTROLr

- **Address:** `0x0f180662`  ·  **Size:** 4 bytes
- **Function:** Sw2 Control for Hardware functions

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LINK_STATUS_UPDATE_ENABLE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180662` | `0x00000000` |

---

## SW2_FP_DST_ACTION_CONTROLr

- **Address:** `0x0f180665`  ·  **Size:** 4 bytes
- **Function:** Enable functions when IFP generates a REDIRECT, REPLACE_PBM or OR_PBM action

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SRC_REMOVAL_EN |
    | `[1]` | HG_SRC_REMOVAL_EN |
    | `[2]` | LAG_RES_EN |
    | `[3]` | HGTRUNK_RES_EN |
    | `[4]` | VLAN_CHECK_EN |
    | `[5]` | PORT_BLOCK_EN |
    | `[6]` | VLAN_BLOCK_EN |
    | `[7]` | SRC_REMOVAL_EN_FOR_REDIRECT_TO_NHI |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180665` | `0x0000000c` |

---

## ING_MIRROR_COS_CONTROLr

- **Address:** `0x0f180678`  ·  **Size:** 4 bytes
- **Function:** Controls usage of MIR_COS for Unicast packets.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[3:1]` | MIRR_COS |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180678` | `0x00000000` |

---

## RTAG7_HASH_DLB_HGTr

- **Address:** `0x0f180679`  ·  **Size:** 4 bytes
- **Function:** RTAG7 hash control register for DLB_HGT Flow Set Index generation.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | SUB_SEL |
    | `[6:3]` | OFFSET |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180679` | `0x00000000` |

---

## E2E_DROP_COUNTr

- **Address:** `0x0f180c01`  ·  **Size:** 4 bytes
- **Function:** Counter for packets dropped due to E2EHOL drop status.

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180c01` | `0x00000000` |

---

## ING_EVENT_DEBUGr

- **Address:** `0x0f180c63`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VXLT_MISS |
    | `[1]` | BPDU |
    | `[2]` | PROTOCOL_PKT |
    | `[3]` | CML |
    | `[4]` | SRC_ROUTE |
    | `[5]` | L2SRC_DISCARD |
    | `[6]` | L2SRC_STATIC_MOVE |
    | `[7]` | L2DST_DISCARD |
    | `[8]` | CFI_OR_L3DISABLE |
    | `[9]` | HIGIG_MH_TYPE1 |
    | `[10]` | DISC_STAGE |
    | `[11]` | SW1_INVALID_VLAN |
    | `[12]` | PDISC |
    | `[13]` | RFILDR |
    | `[14]` | RIMDR |
    | `[15]` | RDROP |
    | `[16]` | VFP |
    | `[17]` | RESERVED_1 |
    | `[18]` | DSL2HE |
    | `[19]` | DSL3HE |
    | `[20]` | DSL4HE |
    | `[21]` | DSICMP |
    | `[22]` | DSFRAG |
    | `[23]` | MTUERR |
    | `[24]` | RESERVED_0 |
    | `[25]` | RTUNE |
    | `[26]` | HG_FAILOVER_PORT_DOWN |
    | `[27]` | HGHDRE |
    | `[28]` | MCIDXE |
    | `[29]` | LAGLUP |
    | `[30]` | LAGLUPD |
    | `[31]` | PARITYD |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180c63` | `0x00000000` |

---

## ING_EVENT_DEBUG_2r

- **Address:** `0x0f180c68`  ·  **Size:** 4 bytes
- **Function:** Ingress Events Debug Register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | HIGIG_HDR_ERROR |
    | `[1]` | LAG_FAILOVER |
    | `[2]` | MACSA0 |
    | `[3]` | VLAN_CC_OR_PBT |
    | `[4]` | CLASS_BASED_SM |
    | `[5]` | MAC_RATE_LIMIT |
    | `[6]` | MPLS_STAGE |
    | `[15:7]` | DROP_RESERVED |
    | `[16]` | VLANDR |
    | `[17]` | URPF |
    | `[18]` | DSTDISC |
    | `[19]` | RESERVED_0 |
    | `[21]` | TIME_SYNC_PACKET_DROP |
    | `[31:22]` | RDBGC_TRIGGER_RESERVED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180c68` | `0x00000000` |

---

## IP5_INTR_STATUSr

- **Address:** `0x0f180d00`  ·  **Size:** 4 bytes
- **Function:** IP5 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VOQ_COS_MAP_PAR_ERR |
    | `[1]` | DLB_HGT_FLOWSET_PORT_PAR_ERR |
    | `[2]` | DLB_HGT_FLOWSET_TIMESTAMP_PAR_ERR |
    | `[3]` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d00` | `0x00000000` |

---

## IP5_INTR_ENABLEr

- **Address:** `0x0f180d01`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP5_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | VOQ_COS_MAP_PAR_ERR |
    | `[1]` | DLB_HGT_FLOWSET_PORT_PAR_ERR |
    | `[2]` | DLB_HGT_FLOWSET_TIMESTAMP_PAR_ERR |
    | `[3]` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d01` | `0x0000000f` |

---

## IP5_INTR_STATUS_1r

- **Address:** `0x0f180d02`  ·  **Size:** 4 bytes
- **Function:** IP5 Interrupt Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_MASK_PAR_ERR |
    | `[1]` | TRUNK_BITMAP_PAR_ERR |
    | `[2]` | NONUCAST_TRUNK_BLOCK_MASK_PAR_ERR |
    | `[3]` | MAC_BLOCK_TABLE_PAR_ERR |
    | `[4]` | MODPORT_MAP_SW_PAR_ERR |
    | `[5]` | MODPORT_MAP_M0_PAR_ERR |
    | `[6]` | MODPORT_MAP_M1_PAR_ERR |
    | `[7]` | MODPORT_MAP_M2_PAR_ERR |
    | `[8]` | MODPORT_MAP_M3_PAR_ERR |
    | `[9]` | SRC_MODID_INGRESS_BLOCK_PAR_ERR |
    | `[10]` | SRC_MODID_EGRESS_PAR_ERR |
    | `[11]` | ALTERNATE_EMIRROR_BITMAP_PAR_ERR |
    | `[12]` | PORT_LAG_FAILOVER_SET_PAR_ERR |
    | `[13]` | VLAN_PROFILE_2_PAR_ERR |
    | `[14]` | L3_MTU_VALUES_PAR_ERR |
    | `[15]` | ING_PW_TERM_SEQ_NUM_PAR_ERR |
    | `[16]` | ING_SERVICE_COUNTER_TABLE_PAR_ERR |
    | `[17]` | ING_VINTF_COUNTER_TABLE_PAR_ERR |
    | `[18]` | VLAN_COS_MAP_PAR_ERR |
    | `[19]` | E2E_HOL_STATUS_PAR_ERR |
    | `[20]` | E2E_HOL_STATUS_1_PAR_ERR |
    | `[21]` | UNKNOWN_UCAST_BLOCK_MASK_PAR_ERR |
    | `[22]` | UNKNOWN_MCAST_BLOCK_MASK_PAR_ERR |
    | `[23]` | BCAST_BLOCK_MASK_PAR_ERR |
    | `[24]` | KNOWN_MCAST_BLOCK_MASK_PAR_ERR |
    | `[25]` | ING_EGRMSKBMAP_PAR_ERR |
    | `[26]` | LOCAL_SW_DISABLE_DEFAULT_PBM_PAR_ERR |
    | `[27]` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PAR_ERR |
    | `[28]` | IMIRROR_BITMAP_PAR_ERR |
    | `[29]` | UNKNOWN_HGI_BITMAP_PAR_ERR |
    | `[30]` | TRUNK_MEMBER_PAR_ERR |
    | `[31]` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d02` | `0x00000000` |

---

## IP5_INTR_ENABLE_1r

- **Address:** `0x0f180d03`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP5_INTR_STATUS_1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EGR_MASK_PAR_ERR |
    | `[1]` | TRUNK_BITMAP_PAR_ERR |
    | `[2]` | NONUCAST_TRUNK_BLOCK_MASK_PAR_ERR |
    | `[3]` | MAC_BLOCK_TABLE_PAR_ERR |
    | `[4]` | MODPORT_MAP_SW_PAR_ERR |
    | `[5]` | MODPORT_MAP_M0_PAR_ERR |
    | `[6]` | MODPORT_MAP_M1_PAR_ERR |
    | `[7]` | MODPORT_MAP_M2_PAR_ERR |
    | `[8]` | MODPORT_MAP_M3_PAR_ERR |
    | `[9]` | SRC_MODID_INGRESS_BLOCK_PAR_ERR |
    | `[10]` | SRC_MODID_EGRESS_PAR_ERR |
    | `[11]` | ALTERNATE_EMIRROR_BITMAP_PAR_ERR |
    | `[12]` | PORT_LAG_FAILOVER_SET_PAR_ERR |
    | `[13]` | VLAN_PROFILE_2_PAR_ERR |
    | `[14]` | L3_MTU_VALUES_PAR_ERR |
    | `[15]` | ING_PW_TERM_SEQ_NUM_PAR_ERR |
    | `[16]` | ING_SERVICE_COUNTER_TABLE_PAR_ERR |
    | `[17]` | ING_VINTF_COUNTER_TABLE_PAR_ERR |
    | `[18]` | VLAN_COS_MAP_PAR_ERR |
    | `[19]` | E2E_HOL_STATUS_PAR_ERR |
    | `[20]` | E2E_HOL_STATUS_1_PAR_ERR |
    | `[21]` | UNKNOWN_UCAST_BLOCK_MASK_PAR_ERR |
    | `[22]` | UNKNOWN_MCAST_BLOCK_MASK_PAR_ERR |
    | `[23]` | BCAST_BLOCK_MASK_PAR_ERR |
    | `[24]` | KNOWN_MCAST_BLOCK_MASK_PAR_ERR |
    | `[25]` | ING_EGRMSKBMAP_PAR_ERR |
    | `[26]` | LOCAL_SW_DISABLE_DEFAULT_PBM_PAR_ERR |
    | `[27]` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PAR_ERR |
    | `[28]` | IMIRROR_BITMAP_PAR_ERR |
    | `[29]` | UNKNOWN_HGI_BITMAP_PAR_ERR |
    | `[30]` | TRUNK_MEMBER_PAR_ERR |
    | `[31]` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d03` | `0xffffffff` |

---

## IP5_INTR_STATUS_2r

- **Address:** `0x0f180d04`  ·  **Size:** 4 bytes
- **Function:** IP5 Interrupt Status 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EMIRROR_CONTROL_PAR_ERR |
    | `[1]` | EMIRROR_CONTROL1_PAR_ERR |
    | `[2]` | EMIRROR_CONTROL2_PAR_ERR |
    | `[3]` | EMIRROR_CONTROL3_PAR_ERR |
    | `[4]` | SW2_EOP_BUFFER_A_PAR_ERR |
    | `[5]` | SW2_EOP_BUFFER_B_PAR_ERR |
    | `[6]` | SW2_EOP_BUFFER_C_PAR_ERR |
    | `[7]` | IP_COUNTERS_PAR_ERR |
    | `[8]` | RDBGC_MEM_INST0_PAR_ERR |
    | `[9]` | RDBGC_MEM_INST1_PAR_ERR |
    | `[10]` | RDBGC_MEM_INST2_PAR_ERR |
    | `[11]` | HG_COUNTERS_PAR_ERR |
    | `[12]` | NIV_ERROR_DROP_PAR_ERR |
    | `[13]` | NIV_FORWARDING_DROP_PAR_ERR |
    | `[14]` | NIV_VLAN_TAGGED_PAR_ERR |
    | `[15]` | TRILL_RX_PKTS_PAR_ERR |
    | `[16]` | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PAR_ERR |
    | `[17]` | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PAR_ERR |
    | `[18]` | CPB_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d04` | `0x00000000` |

---

## IP5_INTR_ENABLE_2r

- **Address:** `0x0f180d05`  ·  **Size:** 4 bytes
- **Function:** Bitwise interrupt enable for IP5_INTR_STATUS_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EMIRROR_CONTROL_PAR_ERR |
    | `[1]` | EMIRROR_CONTROL1_PAR_ERR |
    | `[2]` | EMIRROR_CONTROL2_PAR_ERR |
    | `[3]` | EMIRROR_CONTROL3_PAR_ERR |
    | `[4]` | SW2_EOP_BUFFER_A_PAR_ERR |
    | `[5]` | SW2_EOP_BUFFER_B_PAR_ERR |
    | `[6]` | SW2_EOP_BUFFER_C_PAR_ERR |
    | `[7]` | IP_COUNTERS_PAR_ERR |
    | `[8]` | RDBGC_MEM_INST0_PAR_ERR |
    | `[9]` | RDBGC_MEM_INST1_PAR_ERR |
    | `[10]` | RDBGC_MEM_INST2_PAR_ERR |
    | `[11]` | HG_COUNTERS_PAR_ERR |
    | `[12]` | NIV_ERROR_DROP_PAR_ERR |
    | `[13]` | NIV_FORWARDING_DROP_PAR_ERR |
    | `[14]` | NIV_VLAN_TAGGED_PAR_ERR |
    | `[15]` | TRILL_RX_PKTS_PAR_ERR |
    | `[16]` | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PAR_ERR |
    | `[17]` | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PAR_ERR |
    | `[18]` | CPB_PAR_ERR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d05` | `0x0007ffff` |

---

## L3_MTU_VALUES_PARITY_CONTROLr

- **Address:** `0x0f180d06`  ·  **Size:** 4 bytes
- **Function:** Parity Controls for L3_MTU_VALUES, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d06` | `0x00000001` |

---

## L3_MTU_VALUES_PARITY_STATUS_INTRr

- **Address:** `0x0f180d07`  ·  **Size:** 4 bytes
- **Function:** L3_MTU_VALUES_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d07` | `0x00000000` |

---

## L3_MTU_VALUES_PARITY_STATUS_NACKr

- **Address:** `0x0f180d08`  ·  **Size:** 4 bytes
- **Function:** L3_MTU_VALUES_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[15:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d08` | `0x00000000` |

---

## SW2_RAM_CONTROL_0r

- **Address:** `0x0f180d09`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | EGR_MASK_TM |
    | `[14:10]` | TRUNK_BITMAP_TM |
    | `[19:15]` | ALTERNATE_EMIRROR_BITMAP_TM |
    | `[24:20]` | TRUNK_MEMBER_TM |
    | `[29:25]` | VOQ_COS_MAP_TM |
    | `[30]` | EGR_MASK_PM |
    | `[31]` | EGR_MASK_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d09` | `0x00000000` |

---

## SW2_RAM_CONTROL_1r

- **Address:** `0x0f180d0a`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | SRC_MODID_EGRESS_BLOCK_TM |
    | `[9:5]` | SRC_MODID_INGRESS_BLOCK_TM |
    | `[14:10]` | MODPORT_MAP_SW_TM |
    | `[28:15]` | CPU_COS_MAP_TCAM_TM |
    | `[29]` | SRC_MODID_EGRESS_BLOCK_PM |
    | `[30]` | SRC_MODID_INGRESS_BLOCK_PM |
    | `[31]` | MODPORT_MAP_SW_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0a` | `0x00000000` |

---

## SW2_RAM_CONTROL_2r

- **Address:** `0x0f180d0b`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_TM |
    | `[14:5]` | E2E_HOL_STATUS_1_TM |
    | `[24:15]` | E2E_HOL_STATUS_TM |
    | `[25]` | E2E_HOL_STATUS_PM |
    | `[26]` | E2E_HOL_STATUS_DCM |
    | `[27]` | E2E_HOL_STATUS_1_PM |
    | `[28]` | E2E_HOL_STATUS_1_DCM |
    | `[29]` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0b` | `0x00000000` |

---

## SW2_RAM_CONTROL_3r

- **Address:** `0x0f180d0c`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | MODPORT_MAP_M0_TM |
    | `[9:5]` | MODPORT_MAP_M1_TM |
    | `[14:10]` | MODPORT_MAP_M2_TM |
    | `[19:15]` | MODPORT_MAP_M3_TM |
    | `[24:20]` | L3_MTU_VALUES_TM |
    | `[29:25]` | VLAN_COS_MAP_TM |
    | `[31:30]` | IMIRROR_BITMAP_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0c` | `0x00000000` |

---

## SW2_RAM_CONTROL_4r

- **Address:** `0x0f180d0d`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | MODPORT_MAP_M0_PM |
    | `[1]` | MODPORT_MAP_M1_PM |
    | `[2]` | MODPORT_MAP_M2_PM |
    | `[3]` | MODPORT_MAP_M3_PM |
    | `[4]` | TRUNK_BITMAP_PM |
    | `[5]` | ALTERNATE_EMIRROR_BITMAP_PM |
    | `[6]` | TRUNK_MEMBER_PM |
    | `[7]` | VLAN_COS_MAP_PM |
    | `[8]` | L3_MTU_VALUES_PM |
    | `[9]` | VLAN_PROFILE_2_PM |
    | `[10]` | NONUCAST_TRUNK_BLOCK_MASK_PM |
    | `[11]` | VOQ_COS_MAP_PM |
    | `[13:12]` | EOP_BUF_A_TM |
    | `[15:14]` | EOP_BUF_B_TM |
    | `[17:16]` | EOP_BUF_C_TM |
    | `[19:18]` | PLFS_TM |
    | `[21:20]` | UNKNOWN_UCAST_BLOCK_MASK_TM |
    | `[23:22]` | UNKNOWN_MCAST_BLOCK_MASK_TM |
    | `[25:24]` | KNOWN_MCAST_BLOCK_MASK_TM |
    | `[27:26]` | BCAST_BLOCK_MASK_TM |
    | `[29:28]` | ING_EGRMSKBMAP_TM |
    | `[31:30]` | LOCAL_SW_DISABLE_DEFAULT_PBM_TM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0d` | `0x00000000` |

---

## SW2_RAM_CONTROL_5r

- **Address:** `0x0f180d0e`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | UNKNOWN_HGI_BITMAP_TM |
    | `[11:2]` | ING_SERVICE_COUNTER_TABLE_TM |
    | `[21:12]` | ING_VINTF_COUNTER_TABLE_TM |
    | `[23:22]` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_TM |
    | `[27:24]` | E2E_HOL_STATUS_1_HI_TM |
    | `[28]` | ING_SERVICE_COUNTER_TABLE_PM |
    | `[29]` | ING_SERVICE_COUNTER_TABLE_DCM |
    | `[30]` | ING_VINTF_COUNTER_TABLE_PM |
    | `[31]` | ING_VINTF_COUNTER_TABLE_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0e` | `0x00000000` |

---

## SW2_RAM_CONTROL_6r

- **Address:** `0x0f180d0f`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MAC_BLOCK_TABLE_TM |
    | `[12:8]` | NONUCAST_TRUNK_BLOCK_MASK_TM |
    | `[17:13]` | VLAN_PROFILE_2_TM |
    | `[27:18]` | ING_PWE_TERM_SEQNUM_TM |
    | `[28]` | ING_PWE_TERM_SEQNUM_PM |
    | `[29]` | ING_PWE_TERM_SEQNUM_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d0f` | `0x00000000` |

---

## SW2_RAM_CONTROL_7r

- **Address:** `0x0f180d10`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | CPB_TM |
    | `[19:10]` | DLB_HGT_FLOWSET_PORT_TM |
    | `[29:20]` | DLB_HGT_FLOWSET_TIMESTAMP_TM |
    | `[30]` | CPB_PM |
    | `[31]` | CPB_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d10` | `0x00000000` |

---

## SW2_RAM_CONTROL_8r

- **Address:** `0x0f180d11`  ·  **Size:** 4 bytes
- **Function:** Debug Register to drive the TM inputs of internal rams

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_TM |
    | `[10]` | DLB_HGT_FLOWSET_PORT_PM |
    | `[11]` | DLB_HGT_FLOWSET_PORT_DCM |
    | `[12]` | DLB_HGT_FLOWSET_TIMESTAMP_PM |
    | `[13]` | DLB_HGT_FLOWSET_TIMESTAMP_DCM |
    | `[14]` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PM |
    | `[15]` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_DCM |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d11` | `0x00000000` |

---

## CPU_COS_CAM_DBGCTRLr

- **Address:** `0x0f180d12`  ·  **Size:** 4 bytes
- **Function:** CPU_COS_CAM_CONTROL, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_EN |
    | `[1]` | DEBUG_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d12` | `0x00000000` |

---

## CPU_COS_CAM_BIST_STATUSr

- **Address:** `0x0f180d13`  ·  **Size:** 4 bytes
- **Function:** CPU_COS_CAM_BIST_STATUS

**Fields:**

    _(no field breakdown — treated as a single value)_

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d13` | `0x00000000` |

---

## CPU_COS_CAM_BIST_CONFIGr

- **Address:** `0x0f180d14`  ·  **Size:** 4 bytes
- **Function:** CPU_COS_CAM_BIST_CONFIG, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BIST_DBG_COMPARE_EN |
    | `[1]` | BIST_DBG_DATA_VALID |
    | `[9:2]` | BIST_DBG_DATA_SLICE_OR_STATUS_SEL |
    | `[17:10]` | BIST_SKIP_ERROR_CNT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d14` | `0x00000000` |

---

## CPU_COS_CAM_BIST_DBG_DATAr

- **Address:** `0x0f180d15`  ·  **Size:** 4 bytes
- **Function:** CPU_COS_CAM_BIST_DBG_DATA

**Fields:**

    _(no field breakdown — treated as a single value)_

---

## EGR_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d16`  ·  **Size:** 4 bytes
- **Function:** Parity Control for EGR_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d16` | `0x00000001` |

---

## EGR_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d17`  ·  **Size:** 4 bytes
- **Function:** EGR_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d17` | `0x00000000` |

---

## EGR_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d18`  ·  **Size:** 4 bytes
- **Function:** EGR_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d18` | `0x00000000` |

---

## TRUNK_MEMBER_PARITY_CONTROLr

- **Address:** `0x0f180d19`  ·  **Size:** 4 bytes
- **Function:** Parity Controls for TRUNK_MEMBER, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d19` | `0x00000001` |

---

## TRUNK_MEMBER_PARITY_STATUS_INTRr

- **Address:** `0x0f180d1a`  ·  **Size:** 4 bytes
- **Function:** TRUNK_MEMBER_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1a` | `0x00000000` |

---

## TRUNK_MEMBER_PARITY_STATUS_NACKr

- **Address:** `0x0f180d1b`  ·  **Size:** 4 bytes
- **Function:** TRUNK_MEMBER_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1b` | `0x00000000` |

---

## TRUNK_BITMAP_TABLE_PARITY_CONTROLr

- **Address:** `0x0f180d1c`  ·  **Size:** 4 bytes
- **Function:** Parity Control for TRUNK_BITMAP_TABLE table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1c` | `0x00000001` |

---

## TRUNK_BITMAP_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0f180d1d`  ·  **Size:** 4 bytes
- **Function:** TRUNK_BITMAP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1d` | `0x00000000` |

---

## TRUNK_BITMAP_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0f180d1e`  ·  **Size:** 4 bytes
- **Function:** TRUNK_BITMAP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1e` | `0x00000000` |

---

## NONUCAST_TRUNK_BLOCK_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d1f`  ·  **Size:** 4 bytes
- **Function:** Parity Control for NONUCAST_TRUNK_BLOCK_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d1f` | `0x00000001` |

---

## NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d20`  ·  **Size:** 4 bytes
- **Function:** NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d20` | `0x00000000` |

---

## NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d21`  ·  **Size:** 4 bytes
- **Function:** NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d21` | `0x00000000` |

---

## MODPORT_MAP_SW_PARITY_CONTROLr

- **Address:** `0x0f180d22`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_SW_PARITY_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d22` | `0x00000001` |

---

## MODPORT_MAP_SW_PARITY_STATUS_INTRr

- **Address:** `0x0f180d23`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_SW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d23` | `0x00000000` |

---

## MODPORT_MAP_SW_PARITY_STATUS_NACKr

- **Address:** `0x0f180d24`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_SW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d24` | `0x00000000` |

---

## ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_CONTROLr

- **Address:** `0x0f180d25`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ING_HIGIG_TRUNK_OVERRIDE_PROFILE table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d25` | `0x00000001` |

---

## ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_INTRr

- **Address:** `0x0f180d26`  ·  **Size:** 4 bytes
- **Function:** ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d26` | `0x00000000` |

---

## ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_NACKr

- **Address:** `0x0f180d27`  ·  **Size:** 4 bytes
- **Function:** ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d27` | `0x00000000` |

---

## PORT_LAG_FAILOVER_SET_PARITY_CONTROLr

- **Address:** `0x0f180d28`  ·  **Size:** 4 bytes
- **Function:** Parity Control for PORT_LAG_FAILOVER_SET table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d28` | `0x00000001` |

---

## PORT_LAG_FAILOVER_SET_PARITY_STATUS_INTRr

- **Address:** `0x0f180d29`  ·  **Size:** 4 bytes
- **Function:** PORT_LAG_FAILOVER_SET_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d29` | `0x00000000` |

---

## PORT_LAG_FAILOVER_SET_PARITY_STATUS_NACKr

- **Address:** `0x0f180d2a`  ·  **Size:** 4 bytes
- **Function:** PORT_LAG_FAILOVER_SET_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2a` | `0x00000000` |

---

## MODPORT_MAP_MIRROR_PARITY_CONTROLr

- **Address:** `0x0f180d2b`  ·  **Size:** 4 bytes
- **Function:** Parity Control for MODPORT_MAP_MIRROR table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2b` | `0x00000001` |

---

## MODPORT_MAP_M0_PARITY_STATUS_INTRr

- **Address:** `0x0f180d2c`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M0_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2c` | `0x00000000` |

---

## MODPORT_MAP_M0_PARITY_STATUS_NACKr

- **Address:** `0x0f180d2d`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M0_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2d` | `0x00000000` |

---

## MODPORT_MAP_M1_PARITY_STATUS_INTRr

- **Address:** `0x0f180d2e`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2e` | `0x00000000` |

---

## MODPORT_MAP_M1_PARITY_STATUS_NACKr

- **Address:** `0x0f180d2f`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d2f` | `0x00000000` |

---

## MODPORT_MAP_M2_PARITY_STATUS_INTRr

- **Address:** `0x0f180d30`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d30` | `0x00000000` |

---

## MODPORT_MAP_M2_PARITY_STATUS_NACKr

- **Address:** `0x0f180d31`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d31` | `0x00000000` |

---

## MODPORT_MAP_M3_PARITY_STATUS_INTRr

- **Address:** `0x0f180d32`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M3_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d32` | `0x00000000` |

---

## MODPORT_MAP_M3_PARITY_STATUS_NACKr

- **Address:** `0x0f180d33`  ·  **Size:** 4 bytes
- **Function:** MODPORT_MAP_M3_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d33` | `0x00000000` |

---

## ALTERNATE_EMIRROR_BITMAP_PARITY_CONTROLr

- **Address:** `0x0f180d34`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ALTERNATE_EMIRROR_BITMAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d34` | `0x00000001` |

---

## ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d35`  ·  **Size:** 4 bytes
- **Function:** ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d35` | `0x00000000` |

---

## ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d36`  ·  **Size:** 4 bytes
- **Function:** ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d36` | `0x00000000` |

---

## ING_PW_TERM_SEQ_NUM_PARITY_CONTROLr

- **Address:** `0x0f180d37`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ING_PW_TERM_SEQ_NUM table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d37` | `0x00000001` |

---

## ING_PW_TERM_SEQ_NUM_PARITY_STATUS_INTRr

- **Address:** `0x0f180d38`  ·  **Size:** 4 bytes
- **Function:** ING_PW_TERM_SEQ_NUM_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d38` | `0x00000000` |

---

## ING_PW_TERM_SEQ_NUM_PARITY_STATUS_NACKr

- **Address:** `0x0f180d39`  ·  **Size:** 4 bytes
- **Function:** ING_PW_TERM_SEQ_NUM_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d39` | `0x00000000` |

---

## MAC_BLOCK_TABLE_PARITY_CONTROLr

- **Address:** `0x0f180d3a`  ·  **Size:** 4 bytes
- **Function:** Parity Control for MAC_BLOCK_TABLE table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3a` | `0x00000001` |

---

## MAC_BLOCK_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0f180d3b`  ·  **Size:** 4 bytes
- **Function:** MAC_BLOCK_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[6:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3b` | `0x00000000` |

---

## MAC_BLOCK_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0f180d3c`  ·  **Size:** 4 bytes
- **Function:** MAC_BLOCK_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[6:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3c` | `0x00000000` |

---

## VLAN_PROFILE_2_PARITY_CONTROLr

- **Address:** `0x0f180d3d`  ·  **Size:** 4 bytes
- **Function:** Parity Control for VLAN_PROFILE_2 table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3d` | `0x00000001` |

---

## VLAN_PROFILE_2_PARITY_STATUS_INTRr

- **Address:** `0x0f180d3e`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROFILE_2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3e` | `0x00000000` |

---

## VLAN_PROFILE_2_PARITY_STATUS_NACKr

- **Address:** `0x0f180d3f`  ·  **Size:** 4 bytes
- **Function:** VLAN_PROFILE_2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d3f` | `0x00000000` |

---

## E2E_HOL_STATUS_PARITY_CONTROLr

- **Address:** `0x0f180d40`  ·  **Size:** 4 bytes
- **Function:** Parity Control for E2E_HOL_STATUS table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d40` | `0x00000001` |

---

## E2E_HOL_STATUS_PARITY_STATUS_INTRr

- **Address:** `0x0f180d41`  ·  **Size:** 4 bytes
- **Function:** E2E_HOL_STATUS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d41` | `0x00000000` |

---

## E2E_HOL_STATUS_PARITY_STATUS_NACKr

- **Address:** `0x0f180d42`  ·  **Size:** 4 bytes
- **Function:** E2E_HOL_STATUS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d42` | `0x00000000` |

---

## E2E_HOL_STATUS_1_PARITY_CONTROLr

- **Address:** `0x0f180d43`  ·  **Size:** 4 bytes
- **Function:** Parity Control for E2E_HOL_STATUS_1 table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d43` | `0x00000001` |

---

## E2E_HOL_STATUS_1_PARITY_STATUS_INTRr

- **Address:** `0x0f180d44`  ·  **Size:** 4 bytes
- **Function:** E2E_HOL_STATUS_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d44` | `0x00000000` |

---

## E2E_HOL_STATUS_1_PARITY_STATUS_NACKr

- **Address:** `0x0f180d45`  ·  **Size:** 4 bytes
- **Function:** E2E_HOL_STATUS_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d45` | `0x00000000` |

---

## VLAN_COS_MAP_PARITY_CONTROLr

- **Address:** `0x0f180d46`  ·  **Size:** 4 bytes
- **Function:** Parity Control for VLAN_COS_MAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d46` | `0x00000001` |

---

## VLAN_COS_MAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d47`  ·  **Size:** 4 bytes
- **Function:** VLAN_COS_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d47` | `0x00000000` |

---

## VLAN_COS_MAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d48`  ·  **Size:** 4 bytes
- **Function:** VLAN_COS_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[13:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d48` | `0x00000000` |

---

## SRC_MODID_INGRESS_BLOCK_PARITY_CONTROLr

- **Address:** `0x0f180d49`  ·  **Size:** 4 bytes
- **Function:** Parity Control for SRC_MODID_INGRESS_BLOCK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d49` | `0x00000001` |

---

## SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d4a`  ·  **Size:** 4 bytes
- **Function:** SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4a` | `0x00000000` |

---

## SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d4b`  ·  **Size:** 4 bytes
- **Function:** SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4b` | `0x00000000` |

---

## SRC_MODID_EGRESS_PARITY_CONTROLr

- **Address:** `0x0f180d4c`  ·  **Size:** 4 bytes
- **Function:** Parity Control for SRC_MODID_EGRESS table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4c` | `0x00000001` |

---

## SRC_MODID_EGRESS_PARITY_STATUS_INTRr

- **Address:** `0x0f180d4d`  ·  **Size:** 4 bytes
- **Function:** SRC_MODID_EGRESS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4d` | `0x00000000` |

---

## SRC_MODID_EGRESS_PARITY_STATUS_NACKr

- **Address:** `0x0f180d4e`  ·  **Size:** 4 bytes
- **Function:** SRC_MODID_EGRESS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4e` | `0x00000000` |

---

## VOQ_COS_MAP_PARITY_CONTROLr

- **Address:** `0x0f180d4f`  ·  **Size:** 4 bytes
- **Function:** Parity Control for VOQ_COS_MAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d4f` | `0x00000001` |

---

## VOQ_COS_MAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d50`  ·  **Size:** 4 bytes
- **Function:** VOQ_COS_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d50` | `0x00000000` |

---

## VOQ_COS_MAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d51`  ·  **Size:** 4 bytes
- **Function:** VOQ_COS_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[9:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d51` | `0x00000000` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_CONTROLr

- **Address:** `0x0f180d52`  ·  **Size:** 4 bytes
- **Function:** Parity Control for LOCAL_SW_DISABLE_DEFAULT_PBM table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d52` | `0x00000001` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_INTRr

- **Address:** `0x0f180d53`  ·  **Size:** 4 bytes
- **Function:** LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d53` | `0x00000000` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_NACKr

- **Address:** `0x0f180d54`  ·  **Size:** 4 bytes
- **Function:** LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d54` | `0x00000000` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_CONTROLr

- **Address:** `0x0f180d55`  ·  **Size:** 4 bytes
- **Function:** Parity Control for LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d55` | `0x00000001` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_INTRr

- **Address:** `0x0f180d56`  ·  **Size:** 4 bytes
- **Function:** LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d56` | `0x00000000` |

---

## LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_NACKr

- **Address:** `0x0f180d57`  ·  **Size:** 4 bytes
- **Function:** LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d57` | `0x00000000` |

---

## UNKNOWN_UCAST_BLOCK_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d58`  ·  **Size:** 4 bytes
- **Function:** Parity Control for UNKNOWN_UCAST_BLOCK_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d58` | `0x00000001` |

---

## UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d59`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d59` | `0x00000000` |

---

## UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d5a`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5a` | `0x00000000` |

---

## UNKNOWN_MCAST_BLOCK_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d5b`  ·  **Size:** 4 bytes
- **Function:** Parity Control for UNKNOWN_MCAST_BLOCK_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5b` | `0x00000001` |

---

## UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d5c`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5c` | `0x00000000` |

---

## UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d5d`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5d` | `0x00000000` |

---

## BCAST_BLOCK_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d5e`  ·  **Size:** 4 bytes
- **Function:** Parity Control for BCAST_BLOCK_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5e` | `0x00000001` |

---

## BCAST_BLOCK_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d5f`  ·  **Size:** 4 bytes
- **Function:** BCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d5f` | `0x00000000` |

---

## BCAST_BLOCK_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d60`  ·  **Size:** 4 bytes
- **Function:** BCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d60` | `0x00000000` |

---

## EMIRROR_CONTROL_PARITY_CONTROLr

- **Address:** `0x0f180d61`  ·  **Size:** 4 bytes
- **Function:** Parity Control for EMIRROR_CONTROL table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d61` | `0x00000001` |

---

## EMIRROR_CONTROL_PARITY_STATUS_INTRr

- **Address:** `0x0f180d62`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d62` | `0x00000000` |

---

## EMIRROR_CONTROL_PARITY_STATUS_NACKr

- **Address:** `0x0f180d63`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d63` | `0x00000000` |

---

## ING_EGRMSKBMAP_PARITY_CONTROLr

- **Address:** `0x0f180d64`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ING_EGRMSKBMAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d64` | `0x00000001` |

---

## ING_EGRMSKBMAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d65`  ·  **Size:** 4 bytes
- **Function:** ING_EGRMSKBMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d65` | `0x00000000` |

---

## ING_EGRMSKBMAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d66`  ·  **Size:** 4 bytes
- **Function:** ING_EGRMSKBMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d66` | `0x00000000` |

---

## KNOWN_MCAST_BLOCK_MASK_PARITY_CONTROLr

- **Address:** `0x0f180d67`  ·  **Size:** 4 bytes
- **Function:** Parity Control for KNOWN_MCAST_BLOCK_MASK table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d67` | `0x00000001` |

---

## KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTRr

- **Address:** `0x0f180d68`  ·  **Size:** 4 bytes
- **Function:** KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d68` | `0x00000000` |

---

## KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACKr

- **Address:** `0x0f180d69`  ·  **Size:** 4 bytes
- **Function:** KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d69` | `0x00000000` |

---

## EMIRROR_CONTROL1_PARITY_CONTROLr

- **Address:** `0x0f180d6a`  ·  **Size:** 4 bytes
- **Function:** Parity Control for EMIRROR_CONTROL1 table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6a` | `0x00000001` |

---

## EMIRROR_CONTROL1_PARITY_STATUS_INTRr

- **Address:** `0x0f180d6b`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6b` | `0x00000000` |

---

## EMIRROR_CONTROL1_PARITY_STATUS_NACKr

- **Address:** `0x0f180d6c`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6c` | `0x00000000` |

---

## EMIRROR_CONTROL2_PARITY_CONTROLr

- **Address:** `0x0f180d6d`  ·  **Size:** 4 bytes
- **Function:** Parity Control for EMIRROR_CONTROL2 table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6d` | `0x00000001` |

---

## EMIRROR_CONTROL2_PARITY_STATUS_INTRr

- **Address:** `0x0f180d6e`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6e` | `0x00000000` |

---

## EMIRROR_CONTROL2_PARITY_STATUS_NACKr

- **Address:** `0x0f180d6f`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d6f` | `0x00000000` |

---

## EMIRROR_CONTROL3_PARITY_CONTROLr

- **Address:** `0x0f180d70`  ·  **Size:** 4 bytes
- **Function:** Parity Control for EMIRROR_CONTROL3 table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d70` | `0x00000001` |

---

## EMIRROR_CONTROL3_PARITY_STATUS_INTRr

- **Address:** `0x0f180d71`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL3_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d71` | `0x00000000` |

---

## EMIRROR_CONTROL3_PARITY_STATUS_NACKr

- **Address:** `0x0f180d72`  ·  **Size:** 4 bytes
- **Function:** EMIRROR_CONTROL3_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d72` | `0x00000000` |

---

## IMIRROR_BITMAP_PARITY_CONTROLr

- **Address:** `0x0f180d73`  ·  **Size:** 4 bytes
- **Function:** Parity Control for IMIRROR_BITMAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d73` | `0x00000001` |

---

## IMIRROR_BITMAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d74`  ·  **Size:** 4 bytes
- **Function:** IMIRROR_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d74` | `0x00000000` |

---

## IMIRROR_BITMAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d75`  ·  **Size:** 4 bytes
- **Function:** IMIRROR_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d75` | `0x00000000` |

---

## UNKNOWN_HGI_BITMAP_PARITY_CONTROLr

- **Address:** `0x0f180d76`  ·  **Size:** 4 bytes
- **Function:** Parity Control for UNKNOWN_HGI_BITMAP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d76` | `0x00000001` |

---

## UNKNOWN_HGI_BITMAP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d77`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_HGI_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d77` | `0x00000000` |

---

## UNKNOWN_HGI_BITMAP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d78`  ·  **Size:** 4 bytes
- **Function:** UNKNOWN_HGI_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d78` | `0x00000000` |

---

## SW2_EOP_BUFFER_A_PARITY_CONTROLr

- **Address:** `0x0f180d79`  ·  **Size:** 4 bytes
- **Function:** Parity Control for SW2_EOP_BUFFER_A table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d79` | `0x00000001` |

---

## SW2_EOP_BUFFER_A_PARITY_STATUS_INTRr

- **Address:** `0x0f180d7a`  ·  **Size:** 4 bytes
- **Function:** SW2_EOP_BUFFER_A_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7a` | `0x00000000` |

---

## SW2_EOP_BUFFER_B_PARITY_CONTROLr

- **Address:** `0x0f180d7b`  ·  **Size:** 4 bytes
- **Function:** Parity Control for SW2_EOP_BUFFER_B table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7b` | `0x00000001` |

---

## SW2_EOP_BUFFER_B_PARITY_STATUS_INTRr

- **Address:** `0x0f180d7c`  ·  **Size:** 4 bytes
- **Function:** SW2_EOP_BUFFER_B_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7c` | `0x00000000` |

---

## SW2_EOP_BUFFER_C_PARITY_CONTROLr

- **Address:** `0x0f180d7d`  ·  **Size:** 4 bytes
- **Function:** Parity Control for SW2_EOP_BUFFER_C table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7d` | `0x00000001` |

---

## SW2_EOP_BUFFER_C_PARITY_STATUS_INTRr

- **Address:** `0x0f180d7e`  ·  **Size:** 4 bytes
- **Function:** SW2_EOP_BUFFER_C_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7e` | `0x00000000` |

---

## CPB_PARITY_CONTROLr

- **Address:** `0x0f180d7f`  ·  **Size:** 4 bytes
- **Function:** Parity Control for CPB table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d7f` | `0x00000001` |

---

## CPB_PARITY_STATUS_INTRr

- **Address:** `0x0f180d80`  ·  **Size:** 4 bytes
- **Function:** CPB_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[12:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d80` | `0x00000000` |

---

## IP_COUNTERS_PARITY_CONTROLr

- **Address:** `0x0f180d81`  ·  **Size:** 4 bytes
- **Function:** Parity Control for IP stats counters, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d81` | `0x00000001` |

---

## IP_COUNTERS_PARITY_STATUS_INTRr

- **Address:** `0x0f180d82`  ·  **Size:** 4 bytes
- **Function:** IP_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d82` | `0x00000000` |

---

## IP_COUNTERS_PARITY_STATUS_NACKr

- **Address:** `0x0f180d83`  ·  **Size:** 4 bytes
- **Function:** IP_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d83` | `0x00000000` |

---

## RDBGC_MEM_INST0_PARITY_CONTROLr

- **Address:** `0x0f180d84`  ·  **Size:** 4 bytes
- **Function:** Parity Control for fixed and flexible debug counters, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d84` | `0x00000001` |

---

## RDBGC_MEM_INST0_PARITY_STATUS_INTRr

- **Address:** `0x0f180d85`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST0_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d85` | `0x00000000` |

---

## RDBGC_MEM_INST0_PARITY_STATUS_NACKr

- **Address:** `0x0f180d86`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST0_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d86` | `0x00000000` |

---

## RDBGC_MEM_INST1_PARITY_CONTROLr

- **Address:** `0x0f180d87`  ·  **Size:** 4 bytes
- **Function:** Parity Control for flexible debug counters, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d87` | `0x00000001` |

---

## RDBGC_MEM_INST1_PARITY_STATUS_INTRr

- **Address:** `0x0f180d88`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d88` | `0x00000000` |

---

## RDBGC_MEM_INST1_PARITY_STATUS_NACKr

- **Address:** `0x0f180d89`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d89` | `0x00000000` |

---

## RDBGC_MEM_INST2_PARITY_CONTROLr

- **Address:** `0x0f180d8a`  ·  **Size:** 4 bytes
- **Function:** Parity Control for flexible debug counters, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d8a` | `0x00000001` |

---

## RDBGC_MEM_INST2_PARITY_STATUS_INTRr

- **Address:** `0x0f180d8b`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d8b` | `0x00000000` |

---

## RDBGC_MEM_INST2_PARITY_STATUS_NACKr

- **Address:** `0x0f180d8c`  ·  **Size:** 4 bytes
- **Function:** RDBGC_MEM_INST2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d8c` | `0x00000000` |

---

## HG_COUNTERS_PARITY_CONTROLr

- **Address:** `0x0f180d8d`  ·  **Size:** 4 bytes
- **Function:** Parity Control for Higig stats counters, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d8d` | `0x00000001` |

---

## HG_COUNTERS_PARITY_STATUS_INTRr

- **Address:** `0x0f180d8e`  ·  **Size:** 4 bytes
- **Function:** HG_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d8e` | `0x00000000` |

---

## HG_COUNTERS_PARITY_STATUS_NACKr

- **Address:** `0x0f180d8f`  ·  **Size:** 4 bytes
- **Function:** HG_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

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
    | ipipe0 | `0x0f180d8f` | `0x00000000` |

---

## ING_SERVICE_COUNTER_TABLE_PARITY_CONTROLr

- **Address:** `0x0f180d90`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ING_SERVICE_COUNTER_TABLE table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d90` | `0x00000001` |

---

## ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0f180d91`  ·  **Size:** 4 bytes
- **Function:** ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d91` | `0x00000000` |

---

## ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0f180d92`  ·  **Size:** 4 bytes
- **Function:** ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d92` | `0x00000000` |

---

## ING_VINTF_COUNTER_TABLE_PARITY_CONTROLr

- **Address:** `0x0f180d93`  ·  **Size:** 4 bytes
- **Function:** Parity Control for ING_VINTF_COUNTER_TABLE table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d93` | `0x00000001` |

---

## ING_VINTF_COUNTER_TABLE_PARITY_STATUS_INTRr

- **Address:** `0x0f180d94`  ·  **Size:** 4 bytes
- **Function:** ING_VINTF_COUNTER_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d94` | `0x00000000` |

---

## ING_VINTF_COUNTER_TABLE_PARITY_STATUS_NACKr

- **Address:** `0x0f180d95`  ·  **Size:** 4 bytes
- **Function:** ING_VINTF_COUNTER_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[14:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d95` | `0x00000000` |

---

## NIV_ERROR_DROP_PARITY_CONTROLr

- **Address:** `0x0f180d96`  ·  **Size:** 4 bytes
- **Function:** Parity Control for NIV_ERROR_DROP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d96` | `0x00000001` |

---

## NIV_ERROR_DROP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d97`  ·  **Size:** 4 bytes
- **Function:** NIV_ERROR_DROP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d97` | `0x00000000` |

---

## NIV_ERROR_DROP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d98`  ·  **Size:** 4 bytes
- **Function:** NIV_ERROR_DROP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d98` | `0x00000000` |

---

## NIV_FORWARDING_DROP_PARITY_CONTROLr

- **Address:** `0x0f180d99`  ·  **Size:** 4 bytes
- **Function:** Parity Control for NIV_FORWARDING_DROP table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d99` | `0x00000001` |

---

## NIV_FORWARDING_DROP_PARITY_STATUS_INTRr

- **Address:** `0x0f180d9a`  ·  **Size:** 4 bytes
- **Function:** NIV_FORWARDING_DROP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9a` | `0x00000000` |

---

## NIV_FORWARDING_DROP_PARITY_STATUS_NACKr

- **Address:** `0x0f180d9b`  ·  **Size:** 4 bytes
- **Function:** NIV_FORWARDING_DROP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9b` | `0x00000000` |

---

## NIV_VLAN_TAGGED_PARITY_CONTROLr

- **Address:** `0x0f180d9c`  ·  **Size:** 4 bytes
- **Function:** Parity Control for NIV_VLAN_TAGGED table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9c` | `0x00000001` |

---

## NIV_VLAN_TAGGED_PARITY_STATUS_INTRr

- **Address:** `0x0f180d9d`  ·  **Size:** 4 bytes
- **Function:** NIV_VLAN_TAGGED_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9d` | `0x00000000` |

---

## NIV_VLAN_TAGGED_PARITY_STATUS_NACKr

- **Address:** `0x0f180d9e`  ·  **Size:** 4 bytes
- **Function:** NIV_VLAN_TAGGED_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9e` | `0x00000000` |

---

## TRILL_RX_PKTS_PARITY_CONTROLr

- **Address:** `0x0f180d9f`  ·  **Size:** 4 bytes
- **Function:** Parity Control for TRILL_RX_PKTS table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180d9f` | `0x00000001` |

---

## TRILL_RX_PKTS_PARITY_STATUS_INTRr

- **Address:** `0x0f180da0`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_PKTS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da0` | `0x00000000` |

---

## TRILL_RX_PKTS_PARITY_STATUS_NACKr

- **Address:** `0x0f180da1`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_PKTS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da1` | `0x00000000` |

---

## TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_CONTROLr

- **Address:** `0x0f180da2`  ·  **Size:** 4 bytes
- **Function:** Parity Control for TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da2` | `0x00000001` |

---

## TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTRr

- **Address:** `0x0f180da3`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da3` | `0x00000000` |

---

## TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACKr

- **Address:** `0x0f180da4`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da4` | `0x00000000` |

---

## TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_CONTROLr

- **Address:** `0x0f180da5`  ·  **Size:** 4 bytes
- **Function:** Parity Control for TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED table, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da5` | `0x00000001` |

---

## TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTRr

- **Address:** `0x0f180da6`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da6` | `0x00000000` |

---

## TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACKr

- **Address:** `0x0f180da7`  ·  **Size:** 4 bytes
- **Function:** TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[8:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x0f180da7` | `0x00000000` |

---

## SBS_CONTROLr

- **Address:** `0x10180720`  ·  **Size:** 4 bytes
- **Function:** IP main arbiter control register for number of ports

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PIPE_SELECT |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x10180720` | `0x00000000` |

---

## DLB_HGT_PORT_QUALITY_MEASURE_UPDATE_CONTROLr

- **Address:** `0x11100201`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Quality Update Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE_MEASURE_COLLECTION |
    | `[1]` | ENABLE_MEASURE_AVERAGE_CALCULATION |
    | `[2]` | ENABLE_PORT_QUALITY_UPDATE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100201` | `0x00000000` |
    | xe0 | `0x11101201` | `0x00000000` |
    | xe1 | `0x11102201` | `0x00000000` |
    | xe2 | `0x11103201` | `0x00000000` |
    | xe3 | `0x11104201` | `0x00000000` |
    | xe4 | `0x11105201` | `0x00000000` |
    | xe5 | `0x11106201` | `0x00000000` |
    | xe6 | `0x11107201` | `0x00000000` |
    | xe7 | `0x11108201` | `0x00000000` |
    | xe8 | `0x11109201` | `0x00000000` |
    | xe9 | `0x1110a201` | `0x00000000` |
    | xe10 | `0x1110b201` | `0x00000000` |
    | xe11 | `0x1110c201` | `0x00000000` |
    | xe12 | `0x1110d201` | `0x00000000` |
    | xe13 | `0x1110e201` | `0x00000000` |
    | xe14 | `0x1110f201` | `0x00000000` |
    | xe15 | `0x11110201` | `0x00000000` |
    | xe16 | `0x11111201` | `0x00000000` |
    | xe17 | `0x11112201` | `0x00000000` |
    | xe18 | `0x11113201` | `0x00000000` |
    | xe19 | `0x11114201` | `0x00000000` |
    | xe20 | `0x11115201` | `0x00000000` |
    | xe21 | `0x11116201` | `0x00000000` |
    | xe22 | `0x11117201` | `0x00000000` |
    | xe23 | `0x11118201` | `0x00000000` |
    | xe24 | `0x11119201` | `0x00000000` |
    | xe25 | `0x1111a201` | `0x00000000` |
    | xe26 | `0x1111b201` | `0x00000000` |
    | xe27 | `0x1111c201` | `0x00000000` |
    | xe28 | `0x1111d201` | `0x00000000` |
    | xe29 | `0x1111e201` | `0x00000000` |
    | xe30 | `0x1111f201` | `0x00000000` |
    | xe31 | `0x11120201` | `0x00000000` |
    | xe32 | `0x11121201` | `0x00000000` |
    | xe33 | `0x11122201` | `0x00000000` |
    | xe34 | `0x11123201` | `0x00000000` |
    | xe35 | `0x11124201` | `0x00000000` |
    | xe36 | `0x11125201` | `0x00000000` |
    | xe37 | `0x11126201` | `0x00000000` |
    | xe38 | `0x11127201` | `0x00000000` |
    | xe39 | `0x11128201` | `0x00000000` |
    | xe40 | `0x11129201` | `0x00000000` |
    | xe41 | `0x1112a201` | `0x00000000` |
    | xe42 | `0x1112b201` | `0x00000000` |
    | xe43 | `0x1112c201` | `0x00000000` |
    | xe44 | `0x1112d201` | `0x00000000` |
    | xe45 | `0x1112e201` | `0x00000000` |
    | xe46 | `0x1112f201` | `0x00000000` |
    | xe47 | `0x11130201` | `0x00000000` |
    | xe48 | `0x11131201` | `0x00000000` |
    | xe49 | `0x11132201` | `0x00000000` |
    | xe50 | `0x11133201` | `0x00000000` |
    | xe51 | `0x11134201` | `0x00000000` |
    | lb0 | `0x11141201` | `0x00000000` |

---

## DLB_HGT_QUANTIZE_CONTROLr

- **Address:** `0x11100202`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Quantization Parameters.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | PORT_QSIZE_THRESHOLD_SCALING_FACTOR |
    | `[11:6]` | PORT_LOADING_THRESHOLD_SCALING_FACTOR |
    | `[14:12]` | PORT_QUALITY_MAPPING_PROFILE_PTR |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100202` | `0x00000000` |
    | xe0 | `0x11101202` | `0x00000000` |
    | xe1 | `0x11102202` | `0x00000000` |
    | xe2 | `0x11103202` | `0x00000000` |
    | xe3 | `0x11104202` | `0x00000000` |
    | xe4 | `0x11105202` | `0x00000000` |
    | xe5 | `0x11106202` | `0x00000000` |
    | xe6 | `0x11107202` | `0x00000000` |
    | xe7 | `0x11108202` | `0x00000000` |
    | xe8 | `0x11109202` | `0x00000000` |
    | xe9 | `0x1110a202` | `0x00000000` |
    | xe10 | `0x1110b202` | `0x00000000` |
    | xe11 | `0x1110c202` | `0x00000000` |
    | xe12 | `0x1110d202` | `0x00000000` |
    | xe13 | `0x1110e202` | `0x00000000` |
    | xe14 | `0x1110f202` | `0x00000000` |
    | xe15 | `0x11110202` | `0x00000000` |
    | xe16 | `0x11111202` | `0x00000000` |
    | xe17 | `0x11112202` | `0x00000000` |
    | xe18 | `0x11113202` | `0x00000000` |
    | xe19 | `0x11114202` | `0x00000000` |
    | xe20 | `0x11115202` | `0x00000000` |
    | xe21 | `0x11116202` | `0x00000000` |
    | xe22 | `0x11117202` | `0x00000000` |
    | xe23 | `0x11118202` | `0x00000000` |
    | xe24 | `0x11119202` | `0x00000000` |
    | xe25 | `0x1111a202` | `0x00000000` |
    | xe26 | `0x1111b202` | `0x00000000` |
    | xe27 | `0x1111c202` | `0x00000000` |
    | xe28 | `0x1111d202` | `0x00000000` |
    | xe29 | `0x1111e202` | `0x00000000` |
    | xe30 | `0x1111f202` | `0x00000000` |
    | xe31 | `0x11120202` | `0x00000000` |
    | xe32 | `0x11121202` | `0x00000000` |
    | xe33 | `0x11122202` | `0x00000000` |
    | xe34 | `0x11123202` | `0x00000000` |
    | xe35 | `0x11124202` | `0x00000000` |
    | xe36 | `0x11125202` | `0x00000000` |
    | xe37 | `0x11126202` | `0x00000000` |
    | xe38 | `0x11127202` | `0x00000000` |
    | xe39 | `0x11128202` | `0x00000000` |
    | xe40 | `0x11129202` | `0x00000000` |
    | xe41 | `0x1112a202` | `0x00000000` |
    | xe42 | `0x1112b202` | `0x00000000` |
    | xe43 | `0x1112c202` | `0x00000000` |
    | xe44 | `0x1112d202` | `0x00000000` |
    | xe45 | `0x1112e202` | `0x00000000` |
    | xe46 | `0x1112f202` | `0x00000000` |
    | xe47 | `0x11130202` | `0x00000000` |
    | xe48 | `0x11131202` | `0x00000000` |
    | xe49 | `0x11132202` | `0x00000000` |
    | xe50 | `0x11133202` | `0x00000000` |
    | xe51 | `0x11134202` | `0x00000000` |
    | lb0 | `0x11141202` | `0x00000000` |

---

## DLB_HGT_PORT_INST_QUALITY_MEASUREr

- **Address:** `0x11100203`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Port Instantaneous Quality Metrics.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | INST_PORT_LOADING |
    | `[31:16]` | INST_PORT_QSIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100203` | `0x00000000` |
    | xe0 | `0x11101203` | `0x00000000` |
    | xe1 | `0x11102203` | `0x00000000` |
    | xe2 | `0x11103203` | `0x00000000` |
    | xe3 | `0x11104203` | `0x00000000` |
    | xe4 | `0x11105203` | `0x00000000` |
    | xe5 | `0x11106203` | `0x00000000` |
    | xe6 | `0x11107203` | `0x00000000` |
    | xe7 | `0x11108203` | `0x00000000` |
    | xe8 | `0x11109203` | `0x00000000` |
    | xe9 | `0x1110a203` | `0x00000000` |
    | xe10 | `0x1110b203` | `0x00000000` |
    | xe11 | `0x1110c203` | `0x00000000` |
    | xe12 | `0x1110d203` | `0x00000000` |
    | xe13 | `0x1110e203` | `0x00000000` |
    | xe14 | `0x1110f203` | `0x00000000` |
    | xe15 | `0x11110203` | `0x00000000` |
    | xe16 | `0x11111203` | `0x00000000` |
    | xe17 | `0x11112203` | `0x00000000` |
    | xe18 | `0x11113203` | `0x00000000` |
    | xe19 | `0x11114203` | `0x00000000` |
    | xe20 | `0x11115203` | `0x00000000` |
    | xe21 | `0x11116203` | `0x00000000` |
    | xe22 | `0x11117203` | `0x00000000` |
    | xe23 | `0x11118203` | `0x00000000` |
    | xe24 | `0x11119203` | `0x00000000` |
    | xe25 | `0x1111a203` | `0x00000000` |
    | xe26 | `0x1111b203` | `0x00000000` |
    | xe27 | `0x1111c203` | `0x00000000` |
    | xe28 | `0x1111d203` | `0x00000000` |
    | xe29 | `0x1111e203` | `0x00000000` |
    | xe30 | `0x1111f203` | `0x00000000` |
    | xe31 | `0x11120203` | `0x00000000` |
    | xe32 | `0x11121203` | `0x00000000` |
    | xe33 | `0x11122203` | `0x00000000` |
    | xe34 | `0x11123203` | `0x00000000` |
    | xe35 | `0x11124203` | `0x00000000` |
    | xe36 | `0x11125203` | `0x00000000` |
    | xe37 | `0x11126203` | `0x00000000` |
    | xe38 | `0x11127203` | `0x00000000` |
    | xe39 | `0x11128203` | `0x00000000` |
    | xe40 | `0x11129203` | `0x00000000` |
    | xe41 | `0x1112a203` | `0x00000000` |
    | xe42 | `0x1112b203` | `0x00000000` |
    | xe43 | `0x1112c203` | `0x00000000` |
    | xe44 | `0x1112d203` | `0x00000000` |
    | xe45 | `0x1112e203` | `0x00000000` |
    | xe46 | `0x1112f203` | `0x00000000` |
    | xe47 | `0x11130203` | `0x00000000` |
    | xe48 | `0x11131203` | `0x00000000` |
    | xe49 | `0x11132203` | `0x00000000` |
    | xe50 | `0x11133203` | `0x00000000` |
    | xe51 | `0x11134203` | `0x00000000` |
    | lb0 | `0x11141203` | `0x00000000` |

---

## DLB_HGT_PORT_AVG_QUALITY_MEASUREr

- **Address:** `0x11100204`  ·  **Size:** 8 bytes
- **Function:** DLB_HGT Port Average Quality Metrics.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | AVG_PORT_LOADING_FRACTION |
    | `[19:4]` | AVG_PORT_LOADING_REALNUM |
    | `[23:20]` | AVG_PORT_QSIZE_FRACTION |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100204` | `0x0000000000000000` |
    | xe0 | `0x11101204` | `0x0000000000000000` |
    | xe1 | `0x11102204` | `0x0000000000000000` |
    | xe2 | `0x11103204` | `0x0000000000000000` |
    | xe3 | `0x11104204` | `0x0000000000000000` |
    | xe4 | `0x11105204` | `0x0000000000000000` |
    | xe5 | `0x11106204` | `0x0000000000000000` |
    | xe6 | `0x11107204` | `0x0000000000000000` |
    | xe7 | `0x11108204` | `0x0000000000000000` |
    | xe8 | `0x11109204` | `0x0000000000000000` |
    | xe9 | `0x1110a204` | `0x0000000000000000` |
    | xe10 | `0x1110b204` | `0x0000000000000000` |
    | xe11 | `0x1110c204` | `0x0000000000000000` |
    | xe12 | `0x1110d204` | `0x0000000000000000` |
    | xe13 | `0x1110e204` | `0x0000000000000000` |
    | xe14 | `0x1110f204` | `0x0000000000000000` |
    | xe15 | `0x11110204` | `0x0000000000000000` |
    | xe16 | `0x11111204` | `0x0000000000000000` |
    | xe17 | `0x11112204` | `0x0000000000000000` |
    | xe18 | `0x11113204` | `0x0000000000000000` |
    | xe19 | `0x11114204` | `0x0000000000000000` |
    | xe20 | `0x11115204` | `0x0000000000000000` |
    | xe21 | `0x11116204` | `0x0000000000000000` |
    | xe22 | `0x11117204` | `0x0000000000000000` |
    | xe23 | `0x11118204` | `0x0000000000000000` |
    | xe24 | `0x11119204` | `0x0000000000000000` |
    | xe25 | `0x1111a204` | `0x0000000000000000` |
    | xe26 | `0x1111b204` | `0x0000000000000000` |
    | xe27 | `0x1111c204` | `0x0000000000000000` |
    | xe28 | `0x1111d204` | `0x0000000000000000` |
    | xe29 | `0x1111e204` | `0x0000000000000000` |
    | xe30 | `0x1111f204` | `0x0000000000000000` |
    | xe31 | `0x11120204` | `0x0000000000000000` |
    | xe32 | `0x11121204` | `0x0000000000000000` |
    | xe33 | `0x11122204` | `0x0000000000000000` |
    | xe34 | `0x11123204` | `0x0000000000000000` |
    | xe35 | `0x11124204` | `0x0000000000000000` |
    | xe36 | `0x11125204` | `0x0000000000000000` |
    | xe37 | `0x11126204` | `0x0000000000000000` |
    | xe38 | `0x11127204` | `0x0000000000000000` |
    | xe39 | `0x11128204` | `0x0000000000000000` |
    | xe40 | `0x11129204` | `0x0000000000000000` |
    | xe41 | `0x1112a204` | `0x0000000000000000` |
    | xe42 | `0x1112b204` | `0x0000000000000000` |
    | xe43 | `0x1112c204` | `0x0000000000000000` |
    | xe44 | `0x1112d204` | `0x0000000000000000` |
    | xe45 | `0x1112e204` | `0x0000000000000000` |
    | xe46 | `0x1112f204` | `0x0000000000000000` |
    | xe47 | `0x11130204` | `0x0000000000000000` |
    | xe48 | `0x11131204` | `0x0000000000000000` |
    | xe49 | `0x11132204` | `0x0000000000000000` |
    | xe50 | `0x11133204` | `0x0000000000000000` |
    | xe51 | `0x11134204` | `0x0000000000000000` |
    | lb0 | `0x11141204` | `0x0000000000000000` |

---

## DLB_HGT_QUANTIZED_AVG_QUALITY_MEASUREr

- **Address:** `0x11100205`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Quantized Average Port Quality Measure.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | QUANTIZED_PORT_LOADING |
    | `[5:3]` | QUANTIZED_PORT_QSIZE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100205` | `0x00000000` |
    | xe0 | `0x11101205` | `0x00000000` |
    | xe1 | `0x11102205` | `0x00000000` |
    | xe2 | `0x11103205` | `0x00000000` |
    | xe3 | `0x11104205` | `0x00000000` |
    | xe4 | `0x11105205` | `0x00000000` |
    | xe5 | `0x11106205` | `0x00000000` |
    | xe6 | `0x11107205` | `0x00000000` |
    | xe7 | `0x11108205` | `0x00000000` |
    | xe8 | `0x11109205` | `0x00000000` |
    | xe9 | `0x1110a205` | `0x00000000` |
    | xe10 | `0x1110b205` | `0x00000000` |
    | xe11 | `0x1110c205` | `0x00000000` |
    | xe12 | `0x1110d205` | `0x00000000` |
    | xe13 | `0x1110e205` | `0x00000000` |
    | xe14 | `0x1110f205` | `0x00000000` |
    | xe15 | `0x11110205` | `0x00000000` |
    | xe16 | `0x11111205` | `0x00000000` |
    | xe17 | `0x11112205` | `0x00000000` |
    | xe18 | `0x11113205` | `0x00000000` |
    | xe19 | `0x11114205` | `0x00000000` |
    | xe20 | `0x11115205` | `0x00000000` |
    | xe21 | `0x11116205` | `0x00000000` |
    | xe22 | `0x11117205` | `0x00000000` |
    | xe23 | `0x11118205` | `0x00000000` |
    | xe24 | `0x11119205` | `0x00000000` |
    | xe25 | `0x1111a205` | `0x00000000` |
    | xe26 | `0x1111b205` | `0x00000000` |
    | xe27 | `0x1111c205` | `0x00000000` |
    | xe28 | `0x1111d205` | `0x00000000` |
    | xe29 | `0x1111e205` | `0x00000000` |
    | xe30 | `0x1111f205` | `0x00000000` |
    | xe31 | `0x11120205` | `0x00000000` |
    | xe32 | `0x11121205` | `0x00000000` |
    | xe33 | `0x11122205` | `0x00000000` |
    | xe34 | `0x11123205` | `0x00000000` |
    | xe35 | `0x11124205` | `0x00000000` |
    | xe36 | `0x11125205` | `0x00000000` |
    | xe37 | `0x11126205` | `0x00000000` |
    | xe38 | `0x11127205` | `0x00000000` |
    | xe39 | `0x11128205` | `0x00000000` |
    | xe40 | `0x11129205` | `0x00000000` |
    | xe41 | `0x1112a205` | `0x00000000` |
    | xe42 | `0x1112b205` | `0x00000000` |
    | xe43 | `0x1112c205` | `0x00000000` |
    | xe44 | `0x1112d205` | `0x00000000` |
    | xe45 | `0x1112e205` | `0x00000000` |
    | xe46 | `0x1112f205` | `0x00000000` |
    | xe47 | `0x11130205` | `0x00000000` |
    | xe48 | `0x11131205` | `0x00000000` |
    | xe49 | `0x11132205` | `0x00000000` |
    | xe50 | `0x11133205` | `0x00000000` |
    | xe51 | `0x11134205` | `0x00000000` |
    | lb0 | `0x11141205` | `0x00000000` |

---

## DLB_HGT_FINAL_PORT_QUALITY_MEASUREr

- **Address:** `0x11100206`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Port Quality.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | QUALITY |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | cpu0 | `0x11100206` | `0x00000000` |
    | xe0 | `0x11101206` | `0x00000000` |
    | xe1 | `0x11102206` | `0x00000000` |
    | xe2 | `0x11103206` | `0x00000000` |
    | xe3 | `0x11104206` | `0x00000000` |
    | xe4 | `0x11105206` | `0x00000000` |
    | xe5 | `0x11106206` | `0x00000000` |
    | xe6 | `0x11107206` | `0x00000000` |
    | xe7 | `0x11108206` | `0x00000000` |
    | xe8 | `0x11109206` | `0x00000000` |
    | xe9 | `0x1110a206` | `0x00000000` |
    | xe10 | `0x1110b206` | `0x00000000` |
    | xe11 | `0x1110c206` | `0x00000000` |
    | xe12 | `0x1110d206` | `0x00000000` |
    | xe13 | `0x1110e206` | `0x00000000` |
    | xe14 | `0x1110f206` | `0x00000000` |
    | xe15 | `0x11110206` | `0x00000000` |
    | xe16 | `0x11111206` | `0x00000000` |
    | xe17 | `0x11112206` | `0x00000000` |
    | xe18 | `0x11113206` | `0x00000000` |
    | xe19 | `0x11114206` | `0x00000000` |
    | xe20 | `0x11115206` | `0x00000000` |
    | xe21 | `0x11116206` | `0x00000000` |
    | xe22 | `0x11117206` | `0x00000000` |
    | xe23 | `0x11118206` | `0x00000000` |
    | xe24 | `0x11119206` | `0x00000000` |
    | xe25 | `0x1111a206` | `0x00000000` |
    | xe26 | `0x1111b206` | `0x00000000` |
    | xe27 | `0x1111c206` | `0x00000000` |
    | xe28 | `0x1111d206` | `0x00000000` |
    | xe29 | `0x1111e206` | `0x00000000` |
    | xe30 | `0x1111f206` | `0x00000000` |
    | xe31 | `0x11120206` | `0x00000000` |
    | xe32 | `0x11121206` | `0x00000000` |
    | xe33 | `0x11122206` | `0x00000000` |
    | xe34 | `0x11123206` | `0x00000000` |
    | xe35 | `0x11124206` | `0x00000000` |
    | xe36 | `0x11125206` | `0x00000000` |
    | xe37 | `0x11126206` | `0x00000000` |
    | xe38 | `0x11127206` | `0x00000000` |
    | xe39 | `0x11128206` | `0x00000000` |
    | xe40 | `0x11129206` | `0x00000000` |
    | xe41 | `0x1112a206` | `0x00000000` |
    | xe42 | `0x1112b206` | `0x00000000` |
    | xe43 | `0x1112c206` | `0x00000000` |
    | xe44 | `0x1112d206` | `0x00000000` |
    | xe45 | `0x1112e206` | `0x00000000` |
    | xe46 | `0x1112f206` | `0x00000000` |
    | xe47 | `0x11130206` | `0x00000000` |
    | xe48 | `0x11131206` | `0x00000000` |
    | xe49 | `0x11132206` | `0x00000000` |
    | xe50 | `0x11133206` | `0x00000000` |
    | xe51 | `0x11134206` | `0x00000000` |
    | lb0 | `0x11141206` | `0x00000000` |

---

## DLB_HGT_QUALITY_MEASURE_CONTROLr

- **Address:** `0x11180200`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Quality Measure Update Control Register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | SAMPLING_PERIOD |
    | `[11:8]` | PORT_LOADING_WEIGHT |
    | `[15:12]` | PORT_QSIZE_WEIGHT |
    | `[16]` | CAP_LOADING_AVERAGE |
    | `[17]` | CAP_QSIZE_AVERAGE |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180200` | `0x00000003` |

---

## DLB_HGT_RANDOM_SELECTION_CONTROL_Xr

- **Address:** `0x11180208`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Random Selection Seed.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180208` | `0x00000000` |

---

## DLB_HGT_RANDOM_SELECTION_CONTROL_Yr

- **Address:** `0x11180408`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Random Selection Seed.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180408` | `0x00000000` |

---

## DLB_HGT_CURRENT_TIMEr

- **Address:** `0x11180607`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Current Time.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | CURRENT_TIME |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180607` | `0x000f733d` |

---

## DLB_HGT_RANDOM_SELECTION_CONTROLr

- **Address:** `0x11180c08`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT Random Selection Seed.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SEED |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180c08` | `0x00000000` |

---

## DLB_HGT_FLOWSET_PORT_PARITY_CONTROLr

- **Address:** `0x11180d00`  ·  **Size:** 4 bytes
- **Function:** Parity Controls for DLB_HGT_FLOWSET_PORT, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d00` | `0x00000001` |

---

## DLB_HGT_FLOWSET_PORT_PARITY_STATUS_INTRr

- **Address:** `0x11180d01`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_PORT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[16:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d01` | `0x00000000` |

---

## DLB_HGT_FLOWSET_PORT_PARITY_STATUS_NACKr

- **Address:** `0x11180d02`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_PORT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[16:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d02` | `0x00000000` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PARITY_CONTROLr

- **Address:** `0x11180d03`  ·  **Size:** 4 bytes
- **Function:** Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d03` | `0x00000001` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_INTRr

- **Address:** `0x11180d04`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[16:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d04` | `0x00000000` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_NACKr

- **Address:** `0x11180d05`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[16:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d05` | `0x00000000` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_CONTROLr

- **Address:** `0x11180d06`  ·  **Size:** 4 bytes
- **Function:** Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP_PAGE, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_EN |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d06` | `0x00000001` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_INTRr

- **Address:** `0x11180d07`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d07` | `0x00000000` |

---

## DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_NACKr

- **Address:** `0x11180d08`  ·  **Size:** 4 bytes
- **Function:** DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[11:2]` | ENTRY_IDX |

**Observed live values (Cumulus, working chip):**

    | Instance | Address | Value |
    |----------|---------|-------|
    | ipipe0 | `0x11180d08` | `0x00000000` |

---

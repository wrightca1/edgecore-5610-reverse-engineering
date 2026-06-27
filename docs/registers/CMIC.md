# BCM56846 Registers — CMIC block

_CMIC / CMICm — CPU Management Interface (DMA, S-channel, interrupts, MIIM)_

451 registers. Source: OpenMDK CDK defs/sym + OpenBCM descriptions + live Cumulus dump.

---

## CMIC_SCHAN_MESSAGEr

- **Address:** `0x00000000`  ·  **Size:** 4 bytes
- **Function:** S-bus PIO Message Register Set

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SCHAN_CTRLr

- **Address:** `0x00000050`  ·  **Size:** 4 bytes
- **Function:** Status and Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | BIT_POS |
    | `[0]` | MSG_START |
    | `[1]` | MSG_DONE |
    | `[7:2]` | RESERVED_1 |
    | `[7]` | BIT_VAL |
    | `[8]` | LINK_STATUS_CHANGE |
    | `[9]` | PCI_FATAL_ERR |
    | `[10]` | PCI_PARITY_ERR |
    | `[13:11]` | RESERVED_3 |
    | `[14]` | MIIM_SCAN_BUSY |
    | `[15]` | RPIO_PRIORITY_ABOVE_SWPIO |
    | `[16]` | MIIM_RD_START |
    | `[17]` | MIIM_WR_START |
    | `[18]` | MIIM_OP_DONE |
    | `[19]` | MIIM_LINK_SCAN_EN |
    | `[20]` | SER_CHECK_FAIL |
    | `[21]` | NACK |
    | `[22]` | TIMEOUT |
    | `[31:23]` | RESERVED_6 |

---

## CMIC_SCHAN_ERRr

- **Address:** `0x0000005c`  ·  **Size:** 4 bytes
- **Function:** Error Status Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | NACK |
    | `[3:1]` | RESERVED_1 |
    | `[5:4]` | ERR_CODE |
    | `[6]` | ERRBIT |
    | `[13:7]` | DATA_LEN |
    | `[19:14]` | SRC_PORT |
    | `[25:20]` | DST_PORT |
    | `[31:26]` | OP_CODE |

---

## CMIC_PCIE_ERROR_STATUSr

- **Address:** `0x00000060`  ·  **Size:** 4 bytes
- **Function:** PCIE Error Status Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LINK_CRC_ERROR |
    | `[1]` | END_CRC_ERROR |
    | `[2]` | OVERFLOW_UNDERFLOW_ERROR |
    | `[3]` | ERROR_ATTENTION_SET |
    | `[31:4]` | RESERVED |

---

## CMIC_IRQ_STAT_1r

- **Address:** `0x00000064`  ·  **Size:** 4 bytes
- **Function:** Interrupts coming from SBUS Block 0 to 31.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_IRQ_STAT_2r

- **Address:** `0x00000068`  ·  **Size:** 4 bytes
- **Function:** Interrupts coming from SBUS Block 32 to 63.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_IRQ_MASK_1r

- **Address:** `0x0000006c`  ·  **Size:** 4 bytes
- **Function:** Mask for Interrupts coming from SBUS Block 0 to 31.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_IRQ_MASK_2r

- **Address:** `0x00000070`  ·  **Size:** 4 bytes
- **Function:** Mask for Interrupts coming from SBUS Block 32 to 63.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SRAM_TM_CONTROLr

- **Address:** `0x00000084`  ·  **Size:** 4 bytes
- **Function:** This is to configure SRAM macro time margin value.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PCIE_XMT_FIFO_TM |
    | `[8]` | PCIE_XMT_FIFO_STBY |
    | `[16:9]` | PCIE_RCV_FIFO_TM |
    | `[17]` | PCIE_RCV_FIFO_STBY |
    | `[22:18]` | SER_MEM_TM |
    | `[23]` | PCIE_DLP2TLP_BUF_STBY |
    | `[24]` | PCIE_REPLAY_MEM_STBY |
    | `[31:25]` | RESERVED_0 |

---

## CMIC_THERMAL_MON_CTRLr

- **Address:** `0x00000088`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[18:0]` | I_TEMPMON_CTRL |
    | `[2:0]` | BG_ADJ |
    | `[15:3]` | RSVD2 |
    | `[16]` | VTMON_RSTB |
    | `[17]` | POWER_DOWN |
    | `[18]` | RSVD |
    | `[31:19]` | RESERVED |

---

## CMIC_THERMAL_MON_CALIBRATIONr

- **Address:** `0x0000008c`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Calibration Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA_25 |
    | `[31:10]` | RESERVED |

---

## CMIC_THERMAL_MON_RESULT_0r

- **Address:** `0x00000090`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_THERMAL_MON_RESULT_1r

- **Address:** `0x00000094`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_SRAM_TM_CONTROL_2r

- **Address:** `0x00000098`  ·  **Size:** 4 bytes
- **Function:** This is to configure SRAM memory time margin value.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MMU_CPU_COS_MEM_TM |
    | `[8]` | MMU_CPU_COS_MEM_STBY |
    | `[31:9]` | RESERVED |

---

## CMIC_DMA_CTRLr

- **Address:** `0x00000100`  ·  **Size:** 4 bytes
- **Function:** DMA Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CH0_DIRECTION |
    | `[1]` | RESERVED_1_CH0 |
    | `[2]` | CH0_ABORT_DMA |
    | `[3]` | CH0_SEL_INTR_ON_DESC_OR_PKT |
    | `[4]` | RESERVED_2_CH0 |
    | `[6:5]` | RESERVED_3_CH0 |
    | `[7]` | CH0_DROP_RX_PKT_ON_CHAIN_END |
    | `[8]` | CH1_DIRECTION |
    | `[9]` | RESERVED_1_CH1 |
    | `[10]` | CH1_ABORT_DMA |
    | `[11]` | CH1_SEL_INTR_ON_DESC_OR_PKT |
    | `[12]` | RESERVED_2_CH1 |
    | `[14:13]` | RESERVED_3_CH1 |
    | `[15]` | CH1_DROP_RX_PKT_ON_CHAIN_END |
    | `[16]` | CH2_DIRECTION |
    | `[17]` | RESERVED_1_CH2 |
    | `[18]` | CH2_ABORT_DMA |
    | `[19]` | CH2_SEL_INTR_ON_DESC_OR_PKT |
    | `[20]` | RESERVED_2_CH2 |
    | `[22:21]` | RESERVED_3_CH2 |
    | `[23]` | CH2_DROP_RX_PKT_ON_CHAIN_END |
    | `[24]` | CH3_DIRECTION |
    | `[25]` | RESERVED_1_CH3 |
    | `[26]` | CH3_ABORT_DMA |
    | `[27]` | CH3_SEL_INTR_ON_DESC_OR_PKT |
    | `[28]` | RESERVED_2_CH3 |
    | `[30:29]` | RESERVED_3_CH3 |
    | `[31]` | CH3_DROP_RX_PKT_ON_CHAIN_END |

---

## CMIC_DMA_STATr

- **Address:** `0x00000104`  ·  **Size:** 4 bytes
- **Function:** DMA Status and Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | BIT_POS |
    | `[0]` | CH0_DMA_EN |
    | `[1]` | CH1_DMA_EN |
    | `[2]` | CH2_DMA_EN |
    | `[3]` | CH3_DMA_EN |
    | `[4]` | CH0_CHAIN_DONE |
    | `[5]` | CH1_CHAIN_DONE |
    | `[6]` | CH2_CHAIN_DONE |
    | `[7]` | BIT_VAL |
    | `[7]` | CH3_CHAIN_DONE |
    | `[8]` | CH0_DESC_DONE |
    | `[9]` | CH1_DESC_DONE |
    | `[10]` | CH2_DESC_DONE |
    | `[11]` | CH3_DESC_DONE |
    | `[12]` | DMA_RESET |
    | `[13]` | STATS_DMA_OPN_COMPLETE |
    | `[14]` | STATS_DMA_ITER_DONE |
    | `[15]` | TX_DMA_ABORT_NEEDS_CLEANUP |
    | `[16]` | STATS_DMA_ERROR |
    | `[17]` | STATS_DMA_ACTIVE |
    | `[18]` | CH0_DMA_ACTIVE |
    | `[19]` | CH1_DMA_ACTIVE |
    | `[20]` | CH2_DMA_ACTIVE |
    | `[21]` | CH3_DMA_ACTIVE |
    | `[26:22]` | PCI_PARITY_ERR |
    | `[31:27]` | PCI_FATAL_ERR |

---

## CMIC_BS_INITIAL_CRCr

- **Address:** `0x00000108`  ·  **Size:** 4 bytes
- **Function:** Broadsync CRC8 Initial value

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | RESET |
    | `[31:8]` | RESERVED_1 |

---

## CMIC_CONFIGr

- **Address:** `0x0000010c`  ·  **Size:** 4 bytes
- **Function:** Configuration Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | RD_BRST_EN |
    | `[1]` | WR_BRST_EN |
    | `[2]` | BE_CHECK_EN |
    | `[3]` | MSTR_Q_MAX_EN |
    | `[4]` | IGNORE_MMU_BKP_TXDMA_PKT |
    | `[5]` | RESET_CPS |
    | `[6]` | ACT_LOW_INT |
    | `[7]` | SCHAN_ABORT |
    | `[8]` | UNTAG_ALL_RCV_EN |
    | `[9]` | UNTAG_EN |
    | `[10]` | LE_DMA_EN |
    | `[11]` | I2C_EN |
    | `[12]` | IGNORE_MMU_BKP_REMOTE_PKT |
    | `[13]` | IGNORE_ADR_ALIGN_EN |
    | `[14]` | RESERVED |
    | `[15]` | DMA_GARBAGE_COLLECT_EN |
    | `[16]` | RESET_PCI_EN |
    | `[17]` | TIME_STAMP_UPD_DIS |
    | `[18]` | SG_ENABLE |
    | `[19]` | SG_RELOAD_ENABLE |
    | `[20]` | RLD_STS_UPD_DIS |
    | `[21]` | STOP_LS_ON_CHANGE |
    | `[22]` | ABORT_STAT_DMA |
    | `[23]` | RESERVED_4 |
    | `[24]` | COS_RX_EN |
    | `[25]` | EN_SER_INTERLEAVE_PARITY |
    | `[26]` | OVER_RIDE_EXT_MDIO_MSTR_CNTRL |
    | `[27]` | MIIM_ADDR_MAP_ENABLE |
    | `[30:28]` | MDIO_OUT_DELAY |
    | `[31]` | STOP_LS_ON_FIRST_CHANGE |

---

## CMIC_DMA_DESC0r

- **Address:** `0x00000110`  ·  **Size:** 4 bytes
- **Function:** DMA Channel 0 Descriptor Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_DMA_DESC1r

- **Address:** `0x00000114`  ·  **Size:** 4 bytes
- **Function:** DMA Channel 1 Descriptor Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_DMA_DESC2r

- **Address:** `0x00000118`  ·  **Size:** 4 bytes
- **Function:** DMA Channel 2 Descriptor Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_DMA_DESC3r

- **Address:** `0x0000011c`  ·  **Size:** 4 bytes
- **Function:** DMA Channel 3 Descriptor Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_I2C_SLAVE_ADDRr

- **Address:** `0x00000120`  ·  **Size:** 4 bytes
- **Function:** I2C Slave Address Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | GEN_CALL_EN |
    | `[7:1]` | ADDR |
    | `[31:8]` | RESERVED_1 |

---

## CMIC_I2C_DATAr

- **Address:** `0x00000124`  ·  **Size:** 4 bytes
- **Function:** I2C Data Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | DATA |
    | `[31:8]` | RESERVED_1 |

---

## CMIC_I2C_CTRLr

- **Address:** `0x00000128`  ·  **Size:** 4 bytes
- **Function:** I2C Status and Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | RESERVED_1 |
    | `[2]` | AAAK |
    | `[3]` | INT_FLAG |
    | `[4]` | MM_STP |
    | `[5]` | MM_STRT |
    | `[6]` | BUS_EN |
    | `[7]` | INT_EN |
    | `[31:8]` | RESERVED_2 |

---

## CMIC_I2C_STATr

- **Address:** `0x0000012c`  ·  **Size:** 4 bytes
- **Function:** I2C Condition Status Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RESERVED_1 |
    | `[7:3]` | COND |
    | `[31:8]` | RESERVED_2 |

---

## CMIC_I2C_SLAVE_XADDRr

- **Address:** `0x00000130`  ·  **Size:** 4 bytes
- **Function:** I2C Slave Extended Address Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | ADDR |
    | `[31:8]` | RESERVED_1 |

---

## CMIC_I2C_RESETr

- **Address:** `0x0000013c`  ·  **Size:** 4 bytes
- **Function:** I2C Soft Reset Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | RESET |
    | `[31:8]` | RESERVED_1 |

---

## CMIC_LINK_STATr

- **Address:** `0x00000140`  ·  **Size:** 4 bytes
- **Function:** Link Status Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_IRQ_STATr

- **Address:** `0x00000144`  ·  **Size:** 4 bytes
- **Function:** Interrupt Status Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCH_MSG_DONE |
    | `[1]` | CHIP_FUNC_INTR_0 |
    | `[2]` | CHIP_FUNC_INTR_1 |
    | `[3]` | CHIP_FUNC_INTR_2 |
    | `[4]` | LINK_STAT_MOD |
    | `[5]` | CHIP_FUNC_INTR_3 |
    | `[6]` | CHIP_FUNC_INTR_4 |
    | `[7]` | CH0_DESC_DONE |
    | `[8]` | CH0_CHAIN_DONE |
    | `[9]` | CH1_DESC_DONE |
    | `[10]` | CH1_CHAIN_DONE |
    | `[11]` | CH2_DESC_DONE |
    | `[12]` | CH2_CHAIN_DONE |
    | `[13]` | CH3_DESC_DONE |
    | `[14]` | CH3_CHAIN_DONE |
    | `[15]` | PCI_PARITY_ERR |
    | `[16]` | PCI_FATAL_ERR |
    | `[17]` | SCHAN_ERR |
    | `[18]` | I2C_INTR |
    | `[19]` | MIIM_OP_DONE |
    | `[20]` | STAT_DMA_DONE |
    | `[21]` | FIFO_CH0_DMA_INTR |
    | `[22]` | FIFO_CH1_DMA_INTR |
    | `[23]` | FIFO_CH2_DMA_INTR |
    | `[24]` | FIFO_CH3_DMA_INTR |
    | `[25]` | CHIP_FUNC_INTR_5 |
    | `[26]` | CHIP_FUNC_INTR_6 |
    | `[27]` | CHIP_FUNC_INTR_7 |
    | `[28]` | MEM_FAIL |
    | `[29]` | TABLE_DMA_COMPLETE |
    | `[30]` | SLAM_DMA_COMPLETE |
    | `[31]` | BROADSYNC_INTERRUPT |

---

## CMIC_IRQ_MASKr

- **Address:** `0x00000148`  ·  **Size:** 4 bytes
- **Function:** Interrupt Mask Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCH_MSG_DONE |
    | `[1]` | CHIP_FUNC_INTR_0 |
    | `[2]` | CHIP_FUNC_INTR_1 |
    | `[3]` | CHIP_FUNC_INTR_2 |
    | `[4]` | LINK_STAT_MOD |
    | `[5]` | CHIP_FUNC_INTR_3 |
    | `[6]` | CHIP_FUNC_INTR_4 |
    | `[7]` | CH0_DESC_DONE |
    | `[8]` | CH0_CHAIN_DONE |
    | `[9]` | CH1_DESC_DONE |
    | `[10]` | CH1_CHAIN_DONE |
    | `[11]` | CH2_DESC_DONE |
    | `[12]` | CH2_CHAIN_DONE |
    | `[13]` | CH3_DESC_DONE |
    | `[14]` | CH3_CHAIN_DONE |
    | `[15]` | PCI_PARITY_ERR |
    | `[16]` | PCI_FATAL_ERR |
    | `[17]` | SCHAN_ERR |
    | `[18]` | I2C_INTR |
    | `[19]` | MIIM_OP_DONE |
    | `[20]` | STAT_DMA_DONE |
    | `[21]` | FIFO_CH0_DMA_INTR |
    | `[22]` | FIFO_CH1_DMA_INTR |
    | `[23]` | FIFO_CH2_DMA_INTR |
    | `[24]` | FIFO_CH3_DMA_INTR |
    | `[25]` | CHIP_FUNC_INTR_5 |
    | `[26]` | CHIP_FUNC_INTR_6 |
    | `[27]` | CHIP_FUNC_INTR_7 |
    | `[28]` | MEM_FAIL |
    | `[29]` | TABLE_DMA_COMPLETE |
    | `[30]` | SLAM_DMA_COMPLETE |
    | `[31]` | BROADSYNC_INTERRUPT |

---

## CMIC_IRQ_STAT_3r

- **Address:** `0x0000014c`  ·  **Size:** 4 bytes
- **Function:** Interrupt Status Register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EB3_PARITY_INTR |
    | `[1]` | VLI_PARITY_INTR |
    | `[31:2]` | RESERVED |

---

## CMIC_IRQ_MASK_3r

- **Address:** `0x00000150`  ·  **Size:** 4 bytes
- **Function:** Interrupt Mask Register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EB3_PARITY_INTR_MASK |
    | `[1]` | VLI_PARITY_INTR_MASK |
    | `[31:2]` | RESERVED |

---

## CMIC_IRQ_CLR_3r

- **Address:** `0x00000154`  ·  **Size:** 4 bytes
- **Function:** Interrupt Clear Register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EB3_PARITY_INTR_CLEAR |
    | `[1]` | VLI_PARITY_INTR_CLEAR |
    | `[31:2]` | RESERVED |

---

## CMIC_MIIM_PARAMr

- **Address:** `0x00000158`  ·  **Size:** 4 bytes
- **Function:** MIIM Parameter Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | PHY_DATA |
    | `[20:16]` | PHY_ID |
    | `[21]` | C45_SEL |
    | `[24:22]` | BUS_ID |
    | `[25]` | INTERNAL_SEL |
    | `[28:26]` | RESERVED_2 |
    | `[31:29]` | MIIM_CYCLE |

---

## CMIC_MIIM_READ_DATAr

- **Address:** `0x0000015c`  ·  **Size:** 4 bytes
- **Function:** MIIM Read Data Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DATA |

---

## CMIC_SCAN_PORTSr

- **Address:** `0x00000160`  ·  **Size:** 4 bytes
- **Function:** Scan Ports Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_ADDRr

- **Address:** `0x00000164`  ·  **Size:** 4 bytes
- **Function:** Stats memory start address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_SETUPr

- **Address:** `0x00000168`  ·  **Size:** 4 bytes
- **Function:** Stat Counter DMA Access Setup Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | RESERVED_1 |
    | `[29:16]` | TIME_VAL |
    | `[30]` | E_T |
    | `[31]` | EN |

---

## CMIC_STAT_DMA_PORTSr

- **Address:** `0x0000016c`  ·  **Size:** 4 bytes
- **Function:** Stat Counter Port Bit Map Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_CURRENTr

- **Address:** `0x00000170`  ·  **Size:** 4 bytes
- **Function:** Current Stat Counter Value Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_ENDIANESS_SELr

- **Address:** `0x00000174`  ·  **Size:** 4 bytes
- **Function:** Endianness selection register (for various CMIC operations)

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | BYTELANE0 |
    | `[15:8]` | BYTELANE1 |
    | `[23:16]` | BYTELANE2 |
    | `[31:24]` | BYTELANE3 |

---

## CMIC_DEV_REV_IDr

- **Address:** `0x00000178`  ·  **Size:** 4 bytes
- **Function:** Device/revision ID

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DEV_ID |
    | `[23:16]` | REV_ID |
    | `[26:24]` | CHIP_ID |
    | `[31:27]` | RESERVED_1 |

---

## CMIC_SWITCH_FEATURE_ENABLEr

- **Address:** `0x0000017c`  ·  **Size:** 4 bytes
- **Function:** Bond feature enable

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | BOND_FEATURE_EN |
    | `[31:16]` | RESERVED |

---

## CMIC_PCIE_MISCELr

- **Address:** `0x00000188`  ·  **Size:** 4 bytes
- **Function:** Miscellaneous registers for CMIC PCIE interface

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | MSI_PACING_DELAY |
    | `[31:4]` | RESERVED_1 |

---

## CMIC_TAP_CONTROLr

- **Address:** `0x00000194`  ·  **Size:** 4 bytes
- **Function:** Must follow TAP protocol to initiate BIST and read BIST results

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | TDI |
    | `[1]` | TMS |
    | `[2]` | TCK |
    | `[3]` | TRST |
    | `[4]` | TDO |
    | `[31:5]` | RESERVED_1 |

---

## CMIC_RATE_ADJUST_STDMAr

- **Address:** `0x000001b0`  ·  **Size:** 4 bytes
- **Function:** The clock divider configuration register for Stats DMA.\nVarious parts of the chip involved in rate control\nrequire a constant, known frequency. This reference\nfrequency is based off of the chip 's core clock.\nHowever, the core clock can be different in different\ndesigns, thus the need for this register.\nThe core clock frequency is multiplied by the rational\nquantity (DIVIDEND/DIVISOR), and the further divided\ndown by 2 to produce the actual MDIO operation freqeuncy.\nTo avoid skew, it is recommen ...

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DIVISOR |
    | `[31:16]` | DIVIDEND |

---

## CMIC_RATE_ADJUST_I2Cr

- **Address:** `0x000001b4`  ·  **Size:** 4 bytes
- **Function:** The clock divider configuration register for I2C.\nVarious parts of the chip involved in rate control\nrequire a constant, known frequency. This reference\nfrequency is based off of the chip 's core clock.\nHowever, the core clock can be different in different\ndesigns, thus the need for this register.\nThe core clock frequency is multiplied by the rational\nquantity (DIVIDEND/DIVISOR), and the further divided\ndown by 2 to produce the actual MDIO operation freqeuncy.\nTo avoid skew, it is recommended th ...

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DIVISOR |
    | `[31:16]` | DIVIDEND |

---

## CMIC_RATE_ADJUSTr

- **Address:** `0x000001b8`  ·  **Size:** 4 bytes
- **Function:** Various parts of the chip involved in rate control\nrequire a constant, known frequency. This reference\nfrequency is based off of the chip 's core clock.\nHowever, the core clock can be different in different\ndesigns, thus the need for this register.\nThe core clock frequency is multiplied by the rational\nquantity (DIVIDEND/DIVISOR), and the further divided\ndown by 2 to produce the actual MDIO operation freqeuncy.\nTo avoid skew, it is recommended that the DIVIDEND value\nusually be set to 1.\nThe def ...

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DIVISOR |
    | `[31:16]` | DIVIDEND |

---

## CMIC_RATE_ADJUST_INT_MDIOr

- **Address:** `0x000001bc`  ·  **Size:** 4 bytes
- **Function:** The clock divider configuration register for Internal MDIO.\nVarious parts of the chip involved in rate control\nrequire a constant, known frequency. This reference\nfrequency is based off of the chip 's core clock.\nHowever, the core clock can be different in different\ndesigns, thus the need for this register.\nThe core clock frequency is multiplied by the rational\nquantity (DIVIDEND/DIVISOR), and the further divided\ndown by 2 to produce the actual MDIO operation freqeuncy.\nTo avoid skew, it is reco ...

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DIVISOR |
    | `[31:16]` | DIVIDEND |

---

## CMIC_PKT_COUNT_SCHANr

- **Address:** `0x000001c0`  ·  **Size:** 4 bytes
- **Function:** Counter: number of SCHAN_REQUEST packets received

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_SCHAN_REPr

- **Address:** `0x000001c4`  ·  **Size:** 4 bytes
- **Function:** Counter: number of SCHAN_REPLY packets sent

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_FROMCPU_MHr

- **Address:** `0x000001c8`  ·  **Size:** 4 bytes
- **Function:** Counter: number of FROMCPU_PACKET packets received\n        (with module header)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_FROMCPUr

- **Address:** `0x000001cc`  ·  **Size:** 4 bytes
- **Function:** Counter: number of FROMCPU_PACKET packets received\n        (without module header)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_TOCPUDMr

- **Address:** `0x000001d0`  ·  **Size:** 4 bytes
- **Function:** Counter: number of packets sent by means of\n        CMIC_PKT_REASON_DIRECT matching (mini length)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_TOCPUDr

- **Address:** `0x000001d4`  ·  **Size:** 4 bytes
- **Function:** Counter: number of packets sent by means of\n        CMIC_PKT_REASON_DIRECT matching (full length)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_TOCPUEMr

- **Address:** `0x000001d8`  ·  **Size:** 4 bytes
- **Function:** Counter: number of packets sent by means of\n        CMIC_PKT_REASON matching (mini length)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_TOCPUEr

- **Address:** `0x000001dc`  ·  **Size:** 4 bytes
- **Function:** Counter: number of packets sent by means of\n        CMIC_PKT_REASON matching (full length)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_COUNT_TOCPUNr

- **Address:** `0x000001e0`  ·  **Size:** 4 bytes
- **Function:** Counter: number of packets dropped because they did not match\n        CMIC_PKT_REASON* and there was no PCI bus or internal bus\n        available.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_DMA_SB_ARB_CTRLr

- **Address:** `0x000001e4`  ·  **Size:** 4 bytes
- **Function:** For SBus arbitration, 8 round-robin slots are available to any requester.\nLowstr 4-bits are for slot 0 and highest 4-bits are for slot 7.\nEach bit in a slot determines whether the corresponding FIFO DMA channel (0-3)\ncan make a request in that slot (allow req if set). Table, Slam and Stat\nDMA have lower priorities than amy of the FIFO DMA channels.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SBUS_TIMEOUTr

- **Address:** `0x00000200`  ·  **Size:** 4 bytes
- **Function:** Secret register that allows software to program the\nS-bus operation completion time limit (in terms of\nnumber of core clocks).\nIf this limit is exceeded, the CMIC will set the SW PIO\n\"DONE\" bit and the \"ERROR\" bit to indicate the timeout.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SBUS_RING_MAP_0r

- **Address:** `0x00000204`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (0 to 7) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_0 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_1 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_2 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_3 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_4 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_5 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_6 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_7 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_1r

- **Address:** `0x00000208`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (8 to 15) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_8 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_9 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_10 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_11 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_12 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_13 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_14 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_15 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_2r

- **Address:** `0x0000020c`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (16 to 23) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_16 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_17 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_18 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_19 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_20 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_21 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_22 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_23 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_3r

- **Address:** `0x00000210`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (24 to 31) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_24 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_25 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_26 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_27 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_28 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_29 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_30 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_31 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_4r

- **Address:** `0x00000214`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (32 to 39) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_32 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_33 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_34 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_35 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_36 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_37 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_38 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_39 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_5r

- **Address:** `0x00000218`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (40 to 47) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_40 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_41 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_42 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_43 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_44 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_45 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_46 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_47 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_6r

- **Address:** `0x0000021c`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (48 to 55) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_48 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_49 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_50 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_51 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_52 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_53 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_54 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_55 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SBUS_RING_MAP_7r

- **Address:** `0x00000220`  ·  **Size:** 4 bytes
- **Function:** Map of S-bus agents (56 to 63) on all S-bus rings in the chip

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | RING_NUM_SBUS_ID_56 |
    | `[3]` | RESERVED_0 |
    | `[6:4]` | RING_NUM_SBUS_ID_57 |
    | `[7]` | RESERVED_1 |
    | `[10:8]` | RING_NUM_SBUS_ID_58 |
    | `[11]` | RESERVED_2 |
    | `[14:12]` | RING_NUM_SBUS_ID_59 |
    | `[15]` | RESERVED_3 |
    | `[18:16]` | RING_NUM_SBUS_ID_60 |
    | `[19]` | RESERVED_4 |
    | `[22:20]` | RING_NUM_SBUS_ID_61 |
    | `[23]` | RESERVED_5 |
    | `[26:24]` | RING_NUM_SBUS_ID_62 |
    | `[27]` | RESERVED_6 |
    | `[30:28]` | RING_NUM_SBUS_ID_63 |
    | `[31]` | RESERVED_7 |

---

## CMIC_SER_START_ADDR_0r

- **Address:** `0x00000224`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_1r

- **Address:** `0x00000228`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_2r

- **Address:** `0x0000022c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_3r

- **Address:** `0x00000230`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_4r

- **Address:** `0x00000234`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_5r

- **Address:** `0x00000238`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_6r

- **Address:** `0x0000023c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_7r

- **Address:** `0x00000240`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_8r

- **Address:** `0x00000244`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_9r

- **Address:** `0x00000248`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_10r

- **Address:** `0x0000024c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_11r

- **Address:** `0x00000250`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_12r

- **Address:** `0x00000254`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_13r

- **Address:** `0x00000258`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_14r

- **Address:** `0x0000025c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_START_ADDR_15r

- **Address:** `0x00000260`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_0r

- **Address:** `0x00000264`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_1r

- **Address:** `0x00000268`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_2r

- **Address:** `0x0000026c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_3r

- **Address:** `0x00000270`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_4r

- **Address:** `0x00000274`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_5r

- **Address:** `0x00000278`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_6r

- **Address:** `0x0000027c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_7r

- **Address:** `0x00000280`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_8r

- **Address:** `0x00000284`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_9r

- **Address:** `0x00000288`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_10r

- **Address:** `0x0000028c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_11r

- **Address:** `0x00000290`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_12r

- **Address:** `0x00000294`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_13r

- **Address:** `0x00000298`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_14r

- **Address:** `0x0000029c`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_END_ADDR_15r

- **Address:** `0x000002a0`  ·  **Size:** 4 bytes
- **Function:** This register holds the entry SBUS address starting from which protection is enabled.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_MEM_ADDR_0r

- **Address:** `0x000002a4`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_1r

- **Address:** `0x000002a8`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_2r

- **Address:** `0x000002ac`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_3r

- **Address:** `0x000002b0`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_4r

- **Address:** `0x000002b4`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_5r

- **Address:** `0x000002b8`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_6r

- **Address:** `0x000002bc`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_7r

- **Address:** `0x000002c0`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_8r

- **Address:** `0x000002c4`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_9r

- **Address:** `0x000002c8`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_10r

- **Address:** `0x000002cc`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_11r

- **Address:** `0x000002d0`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_12r

- **Address:** `0x000002d4`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_13r

- **Address:** `0x000002d8`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_14r

- **Address:** `0x000002dc`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_MEM_ADDR_15r

- **Address:** `0x000002e0`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_START_ADDR |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_FAIL_CNTr

- **Address:** `0x000002e4`  ·  **Size:** 4 bytes
- **Function:** This register holds the parity storage memory address and parity for this range will be stored starting from this location.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | PARITY_CHECK_FAIL_CNT |
    | `[31]` | RESERVED |

---

## CMIC_SER_FAIL_ENTRYr

- **Address:** `0x000002e8`  ·  **Size:** 4 bytes
- **Function:** This is the sbus addrss of the entry for which parity check fail.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[31:8]` | RESERVED |

---

## CMIC_SER_MEM_ADDRr

- **Address:** `0x000002f0`  ·  **Size:** 4 bytes
- **Function:** Parity storage address.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MEM_ADDRESS |
    | `[31:16]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_4_0r

- **Address:** `0x000002f4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 4 to 0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_0 |
    | `[11:6]` | SBUS_BLKNUM_1 |
    | `[17:12]` | SBUS_BLKNUM_2 |
    | `[23:18]` | SBUS_BLKNUM_3 |
    | `[29:24]` | SBUS_BLKNUM_4 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_9_5r

- **Address:** `0x000002f8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 9 to 5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_5 |
    | `[11:6]` | SBUS_BLKNUM_6 |
    | `[17:12]` | SBUS_BLKNUM_7 |
    | `[23:18]` | SBUS_BLKNUM_8 |
    | `[29:24]` | SBUS_BLKNUM_9 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_14_10r

- **Address:** `0x000002fc`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 14 to 10

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_10 |
    | `[11:6]` | SBUS_BLKNUM_11 |
    | `[17:12]` | SBUS_BLKNUM_12 |
    | `[23:18]` | SBUS_BLKNUM_13 |
    | `[29:24]` | SBUS_BLKNUM_14 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_19_15r

- **Address:** `0x00000300`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 19 to 15

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_15 |
    | `[11:6]` | SBUS_BLKNUM_16 |
    | `[17:12]` | SBUS_BLKNUM_17 |
    | `[23:18]` | SBUS_BLKNUM_18 |
    | `[29:24]` | SBUS_BLKNUM_19 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_24_20r

- **Address:** `0x00000304`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 19 to 15

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_20 |
    | `[11:6]` | SBUS_BLKNUM_21 |
    | `[17:12]` | SBUS_BLKNUM_22 |
    | `[23:18]` | SBUS_BLKNUM_23 |
    | `[29:24]` | SBUS_BLKNUM_24 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_29_25r

- **Address:** `0x00000308`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 29 to 25

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_25 |
    | `[11:6]` | SBUS_BLKNUM_26 |
    | `[17:12]` | SBUS_BLKNUM_27 |
    | `[23:18]` | SBUS_BLKNUM_28 |
    | `[29:24]` | SBUS_BLKNUM_29 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_34_30r

- **Address:** `0x0000030c`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 34 to 30

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_30 |
    | `[11:6]` | SBUS_BLKNUM_31 |
    | `[17:12]` | SBUS_BLKNUM_32 |
    | `[23:18]` | SBUS_BLKNUM_33 |
    | `[29:24]` | SBUS_BLKNUM_34 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_39_35r

- **Address:** `0x00000310`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 39 to 35

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_35 |
    | `[11:6]` | SBUS_BLKNUM_36 |
    | `[17:12]` | SBUS_BLKNUM_37 |
    | `[23:18]` | SBUS_BLKNUM_38 |
    | `[29:24]` | SBUS_BLKNUM_39 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_44_40r

- **Address:** `0x00000314`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 44 to 40

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_40 |
    | `[11:6]` | SBUS_BLKNUM_41 |
    | `[17:12]` | SBUS_BLKNUM_42 |
    | `[23:18]` | SBUS_BLKNUM_43 |
    | `[29:24]` | SBUS_BLKNUM_44 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_49_45r

- **Address:** `0x00000318`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 49 to 45

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_45 |
    | `[11:6]` | SBUS_BLKNUM_46 |
    | `[17:12]` | SBUS_BLKNUM_47 |
    | `[23:18]` | SBUS_BLKNUM_48 |
    | `[29:24]` | SBUS_BLKNUM_49 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_54_50r

- **Address:** `0x0000031c`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 54 to 50

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_50 |
    | `[11:6]` | SBUS_BLKNUM_51 |
    | `[17:12]` | SBUS_BLKNUM_52 |
    | `[23:18]` | SBUS_BLKNUM_53 |
    | `[29:24]` | SBUS_BLKNUM_54 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_59_55r

- **Address:** `0x00000320`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 59 to 55

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_55 |
    | `[11:6]` | SBUS_BLKNUM_56 |
    | `[17:12]` | SBUS_BLKNUM_57 |
    | `[23:18]` | SBUS_BLKNUM_58 |
    | `[29:24]` | SBUS_BLKNUM_59 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_64_60r

- **Address:** `0x00000324`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 64 to 60

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_60 |
    | `[11:6]` | SBUS_BLKNUM_61 |
    | `[17:12]` | SBUS_BLKNUM_62 |
    | `[23:18]` | SBUS_BLKNUM_63 |
    | `[29:24]` | SBUS_BLKNUM_64 |
    | `[31:30]` | RESERVED |

---

## CMIC_SER_PROTECT_ADDR_RANGE_VALIDr

- **Address:** `0x00000328`  ·  **Size:** 4 bytes
- **Function:** Bitmap of Valid SER address ranges

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | VALID_RANGE_BITMAP |
    | `[31:16]` | RESERVED |

---

## CMIC_SER_PARITY_MODE_SELr

- **Address:** `0x0000032c`  ·  **Size:** 4 bytes
- **Function:** Select number of parity bits for a given range. 0- 1 bit, 1- 2 bit, 2- 4 bit, 3- 8 bits

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | RANGE_0_PARITY_BITS |
    | `[3:2]` | RANGE_1_PARITY_BITS |
    | `[5:4]` | RANGE_2_PARITY_BITS |
    | `[7:6]` | RANGE_3_PARITY_BITS |
    | `[9:8]` | RANGE_4_PARITY_BITS |
    | `[11:10]` | RANGE_5_PARITY_BITS |
    | `[13:12]` | RANGE_6_PARITY_BITS |
    | `[15:14]` | RANGE_7_PARITY_BITS |
    | `[17:16]` | RANGE_8_PARITY_BITS |
    | `[19:18]` | RANGE_9_PARITY_BITS |
    | `[21:20]` | RANGE_10_PARITY_BITS |
    | `[23:22]` | RANGE_11_PARITY_BITS |
    | `[25:24]` | RANGE_12_PARITY_BITS |
    | `[27:26]` | RANGE_13_PARITY_BITS |
    | `[29:28]` | RANGE_14_PARITY_BITS |
    | `[31:30]` | RANGE_15_PARITY_BITS |

---

## CMIC_MMU_COSLC_COUNT_DATAr

- **Address:** `0x00000330`  ·  **Size:** 4 bytes
- **Function:** Every time S/W does a read of this register, CMIC requests MMU for coslc_count of CMIC_MMU_COSLC_COUNT_ADDR.PORT_NUM and  CMIC_MMU_COSLC_COUNT_ADDR.COS over a dedicated interface\nand will hold PCI bus until MMU responds with COSLC_COUNT[12:5].\nOnce MMU response is received, CMIC will release PCI bus and return the received COSLC_COUNT value.\nRead to this register will take 4 extra core clocks than regular cmic register reads.\nThis feature is supported for PCI and EB2 modes.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[14:0]` | COSLC_COUNT |
    | `[31:8]` | RESERVED_0 |

---

## CMIC_MMU_COSLC_COUNT_ADDRr

- **Address:** `0x00000334`  ·  **Size:** 4 bytes
- **Function:** When S/W does a read of CMIC_MMU_COSLC_COUNT_DATA register, CMIC returns COSLC_COUNTER value for the port and cos mentioned in this register.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | COS |
    | `[15:8]` | PORT_NUM |
    | `[16]` | EN_RECURSIVE_COSLC_REQ_TO_MMU |
    | `[31:17]` | RESERVED_0 |

---

## CMIC_BS_DRIFT_RATEr

- **Address:** `0x00000338`  ·  **Size:** 4 bytes
- **Function:** Register for Drift adjustment.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | FRAC_NS |
    | `[30]` | SIGN |
    | `[31]` | RESERVED_0 |

---

## CMIC_BS_OFFSET_ADJUST_0r

- **Address:** `0x0000033c`  ·  **Size:** 4 bytes
- **Function:** OFFSET ADJUSTMENT.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_OFFSET_ADJUST_1r

- **Address:** `0x00000340`  ·  **Size:** 4 bytes
- **Function:** OFFSET ADJUSTMENT.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[30]` | SIGN_BIT |
    | `[31]` | RESERVED_0 |

---

## CMIC_BS_CONFIGr

- **Address:** `0x00000344`  ·  **Size:** 4 bytes
- **Function:** Broadsync interface configuration.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[1]` | MODE |
    | `[2]` | TIME_CODE_ENABLE |
    | `[3]` | LOCK |
    | `[11:4]` | ACCURACY |
    | `[27:12]` | EPOCH |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_BS_CLK_CTRL_0r

- **Address:** `0x00000348`  ·  **Size:** 4 bytes
- **Function:** Broadsync clock synthesis control.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[30]` | ENABLE |
    | `[31]` | RESERVED_0 |

---

## CMIC_BS_CLK_CTRL_1r

- **Address:** `0x0000034c`  ·  **Size:** 4 bytes
- **Function:** Broadsync clock synthesis control.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | FRAC_NS |
    | `[31:30]` | RESERVED_0 |

---

## CMIC_BS_CLK_TOGGLE_TIME_0r

- **Address:** `0x00000350`  ·  **Size:** 4 bytes
- **Function:** This registers hold the next time value when Broadsync output clock should toggle.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_CLK_TOGGLE_TIME_1r

- **Address:** `0x00000354`  ·  **Size:** 4 bytes
- **Function:** This registers hold the next time value when Broadsync output clock should toggle.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[31:30]` | RESERVED_0 |

---

## CMIC_BS_CLK_TOGGLE_TIME_2r

- **Address:** `0x00000358`  ·  **Size:** 4 bytes
- **Function:** This registers hold the next time value when Broadsync output clock should toggle.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | FRAC_NS |
    | `[31:30]` | RESERVED_0 |

---

## CMIC_BS_HEARTBEAT_CTRLr

- **Address:** `0x0000035c`  ·  **Size:** 4 bytes
- **Function:** Heartbeat generation control.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[24:0]` | THRESHOLD |
    | `[25]` | ENABLE |
    | `[31:26]` | RESERVED_0 |

---

## CMIC_BS_INPUT_TIME_0r

- **Address:** `0x00000360`  ·  **Size:** 4 bytes
- **Function:** data received on Broadsync interface.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_INPUT_TIME_1r

- **Address:** `0x00000364`  ·  **Size:** 4 bytes
- **Function:** data received on Broadsync interface.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_INPUT_TIME_2r

- **Address:** `0x00000368`  ·  **Size:** 4 bytes
- **Function:** data received on Broadsync interface.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[24:0]` | DATA |
    | `[25]` | CHECKSUM_ERROR |
    | `[31:26]` | RESERVED |

---

## CMIC_BS_CAPTURE_CTRLr

- **Address:** `0x0000036c`  ·  **Size:** 4 bytes
- **Function:** Time capture logic control.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | INT_EN |
    | `[2:1]` | TIME_CAPTURE_MODE |
    | `[31:3]` | RESERVED |

---

## CMIC_BS_CAPTURE_STATUSr

- **Address:** `0x00000370`  ·  **Size:** 4 bytes
- **Function:** Time capture logic status.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | INTERRUPT |
    | `[1]` | TIME_CAPTURE_COMPLETE |
    | `[31:2]` | RESERVED |

---

## CMIC_BS_CAPTURE_FREE_RUN_TIME_0r

- **Address:** `0x00000374`  ·  **Size:** 4 bytes
- **Function:** Captured Free running timer.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_CAPTURE_FREE_RUN_TIME_1r

- **Address:** `0x00000378`  ·  **Size:** 4 bytes
- **Function:** Captured Free running timer.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[31:30]` | RESERVED |

---

## CMIC_BS_CAPTURE_SYNT_TIME_0r

- **Address:** `0x0000037c`  ·  **Size:** 4 bytes
- **Function:** Captured Syntonized timer.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_CAPTURE_SYNT_TIME_1r

- **Address:** `0x00000380`  ·  **Size:** 4 bytes
- **Function:** Captured syntonized timer.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[31:30]` | RESERVED |

---

## CMIC_BS_CAPTURE_SYNC_TIME_0r

- **Address:** `0x00000384`  ·  **Size:** 4 bytes
- **Function:** Captured Synchronized timer.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_BS_CAPTURE_SYNC_TIME_1r

- **Address:** `0x00000388`  ·  **Size:** 4 bytes
- **Function:** Captured synchronized timer.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[29:0]` | NS |
    | `[31:30]` | RESERVED |

---

## CMIC_SER_MEM_DATAr

- **Address:** `0x00000390`  ·  **Size:** 4 bytes
- **Function:** Parity storage data.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SER_RANGE0_DATAENTRY_LENr

- **Address:** `0x00000394`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE1_DATAENTRY_LENr

- **Address:** `0x00000398`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE2_DATAENTRY_LENr

- **Address:** `0x0000039c`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE3_DATAENTRY_LENr

- **Address:** `0x000003a0`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE4_DATAENTRY_LENr

- **Address:** `0x000003a4`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE5_DATAENTRY_LENr

- **Address:** `0x000003a8`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE6_DATAENTRY_LENr

- **Address:** `0x000003ac`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE7_DATAENTRY_LENr

- **Address:** `0x000003b0`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE8_DATAENTRY_LENr

- **Address:** `0x000003b4`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE9_DATAENTRY_LENr

- **Address:** `0x000003b8`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE10_DATAENTRY_LENr

- **Address:** `0x000003bc`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE11_DATAENTRY_LENr

- **Address:** `0x000003c0`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE12_DATAENTRY_LENr

- **Address:** `0x000003c4`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE13_DATAENTRY_LENr

- **Address:** `0x000003c8`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE14_DATAENTRY_LENr

- **Address:** `0x000003cc`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_SER_RANGE15_DATAENTRY_LENr

- **Address:** `0x000003d0`  ·  **Size:** 4 bytes
- **Function:** DATA ENTRY LENGTH.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | ENTRY_LEN |
    | `[31:10]` | RESERVED |

---

## CMIC_LEDCLK_PARAMSr

- **Address:** `0x00000400`  ·  **Size:** 4 bytes
- **Function:** This is the register to configure led clock speed.\nThe value mentioned in this register is time should take for half cycle.\nThe formula is:\nrequired time

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[25:0]` | REFRESH_CYCLE_PERIOD |
    | `[30:26]` | LEDCLK_HALF_PERIOD |

---

## CMIC_SW_PIO_ACK_DATA_BEAT_COUNTr

- **Address:** `0x00000410`  ·  **Size:** 4 bytes
- **Function:** Debug register that provides the number of data\nbeats in the last SW PIO S-bus ACK

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | BEAT_COUNT |
    | `[31:5]` | RESERVED_0 |

---

## CMIC_TABLE_DMA_PCIMEM_START_ADDRr

- **Address:** `0x00000420`  ·  **Size:** 4 bytes
- **Function:** Table DMA PCI Memory Start Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_TABLE_DMA_SBUS_START_ADDRr

- **Address:** `0x00000424`  ·  **Size:** 4 bytes
- **Function:** Table DMA S-bus Start Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_TABLE_DMA_ENTRY_COUNTr

- **Address:** `0x00000428`  ·  **Size:** 4 bytes
- **Function:** Table DMA Entry Count Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[23:0]` | COUNT |
    | `[28:24]` | SBUS_ADDR_INCREMENT_STEP |
    | `[31:29]` | RESERVED_1 |

---

## CMIC_TABLE_DMA_CFGr

- **Address:** `0x0000042c`  ·  **Size:** 4 bytes
- **Function:** Table DMA Config Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EN |
    | `[1]` | ABORT |
    | `[2]` | DONE |
    | `[3]` | ERROR |
    | `[4]` | ENABLE_MULTIPLE_SBUS_CMDS |
    | `[12:5]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[13]` | SER_CHECK_FAIL |
    | `[15:14]` | RESERVED_1 |
    | `[20:16]` | BEATS |
    | `[31:21]` | RESERVED_2 |

---

## CMIC_TABLE_DMA_CUR_ENTRY_SBUS_ADDRr

- **Address:** `0x00000434`  ·  **Size:** 4 bytes
- **Function:** Table DMA Current Entry S-bus Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SLAM_DMA_PCIMEM_START_ADDRr

- **Address:** `0x00000440`  ·  **Size:** 4 bytes
- **Function:** Slam DMA PCI Memory Start Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SLAM_DMA_SBUS_START_ADDRr

- **Address:** `0x00000444`  ·  **Size:** 4 bytes
- **Function:** Slam DMA S-bus Start Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SLAM_DMA_ENTRY_COUNTr

- **Address:** `0x00000448`  ·  **Size:** 4 bytes
- **Function:** Slam DMA Entry Count Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[23:0]` | COUNT |
    | `[28:24]` | SBUS_ADDR_INCREMENT_STEP |
    | `[31:29]` | RESERVED_1 |

---

## CMIC_SLAM_DMA_CFGr

- **Address:** `0x0000044c`  ·  **Size:** 4 bytes
- **Function:** Slam DMA Config Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EN |
    | `[1]` | ABORT |
    | `[2]` | DONE |
    | `[3]` | ERROR |
    | `[4]` | ENABLE_MULTIPLE_SBUS_CMDS |
    | `[12:5]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | BEATS |
    | `[21]` | ORDER |
    | `[27:22]` | REV_MODULO_COUNT |
    | `[31:28]` | RESERVED_2 |

---

## CMIC_SLAM_DMA_CUR_ENTRY_SBUS_ADDRr

- **Address:** `0x00000454`  ·  **Size:** 4 bytes
- **Function:** Slam DMA Current Entry S-bus Address Register

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_ING_STATS_CFGr

- **Address:** `0x00000460`  ·  **Size:** 4 bytes
- **Function:** Stats DMA Ingress stats config register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | ING_ETH_BLK_NUM |
    | `[7:6]` | RESERVED_1 |
    | `[14:8]` | ING_STAT_COUNTERS_NUM |
    | `[15]` | RESERVED_2 |
    | `[21:16]` | ING_STATS_PIPELINE_STAGE_NUM |
    | `[31:22]` | RESERVED_3 |

---

## CMIC_STAT_DMA_EGR_STATS_CFGr

- **Address:** `0x00000464`  ·  **Size:** 4 bytes
- **Function:** Stats DMA Egress stats config register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | EGR_ETH_BLK_NUM |
    | `[7:6]` | RESERVED_1 |
    | `[14:8]` | EGR_STAT_COUNTERS_NUM |
    | `[15]` | RESERVED_2 |
    | `[21:16]` | EGR_STATS_PIPELINE_STAGE_NUM |
    | `[31:22]` | RESERVED_3 |

---

## CMIC_STAT_DMA_MAC_STATS_CFGr

- **Address:** `0x00000468`  ·  **Size:** 4 bytes
- **Function:** Stats DMA MAC stats config register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | MAC_G_STAT_COUNTERS_NUM |
    | `[15:8]` | MAC_X_STAT_COUNTERS_NUM |
    | `[21:16]` | MAC_STATS_PIPELINE_STAGE_NUM |
    | `[23:22]` | RESERVED_0 |
    | `[30:24]` | CPU_STATS_PORT_NUM |
    | `[31]` | RESERVED_1 |

---

## CMIC_STAT_DMA_PORT_TYPE_MAPr

- **Address:** `0x0000046c`  ·  **Size:** 4 bytes
- **Function:** Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port\nNote: The bitmap is index by port number.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_SBUS_START_ADDRESSr

- **Address:** `0x00000470`  ·  **Size:** 4 bytes
- **Function:** SBus Start Address for BigMAC and UniMAC counters.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | SBUS_START_ADDRESS_GPORT |
    | `[23:12]` | SBUS_START_ADDRESS_XPORT |
    | `[31:24]` | RESERVED_0 |

---

## CMIC_MIIM_BUS_MAP_9_0r

- **Address:** `0x00000474`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 0 to Port 9

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_0_BUS_NUM |
    | `[5:3]` | PORT_1_BUS_NUM |
    | `[8:6]` | PORT_2_BUS_NUM |
    | `[11:9]` | PORT_3_BUS_NUM |
    | `[14:12]` | PORT_4_BUS_NUM |
    | `[17:15]` | PORT_5_BUS_NUM |
    | `[20:18]` | PORT_6_BUS_NUM |
    | `[23:21]` | PORT_7_BUS_NUM |
    | `[26:24]` | PORT_8_BUS_NUM |
    | `[29:27]` | PORT_9_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_19_10r

- **Address:** `0x00000478`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 10 to Port 19

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_10_BUS_NUM |
    | `[5:3]` | PORT_11_BUS_NUM |
    | `[8:6]` | PORT_12_BUS_NUM |
    | `[11:9]` | PORT_13_BUS_NUM |
    | `[14:12]` | PORT_14_BUS_NUM |
    | `[17:15]` | PORT_15_BUS_NUM |
    | `[20:18]` | PORT_16_BUS_NUM |
    | `[23:21]` | PORT_17_BUS_NUM |
    | `[26:24]` | PORT_18_BUS_NUM |
    | `[29:27]` | PORT_19_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_29_20r

- **Address:** `0x0000047c`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 10 to Port 19

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_20_BUS_NUM |
    | `[5:3]` | PORT_21_BUS_NUM |
    | `[8:6]` | PORT_22_BUS_NUM |
    | `[11:9]` | PORT_23_BUS_NUM |
    | `[14:12]` | PORT_24_BUS_NUM |
    | `[17:15]` | PORT_25_BUS_NUM |
    | `[20:18]` | PORT_26_BUS_NUM |
    | `[23:21]` | PORT_27_BUS_NUM |
    | `[26:24]` | PORT_28_BUS_NUM |
    | `[29:27]` | PORT_29_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_39_30r

- **Address:** `0x00000480`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 30 to Port 39

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_30_BUS_NUM |
    | `[5:3]` | PORT_31_BUS_NUM |
    | `[8:6]` | PORT_32_BUS_NUM |
    | `[11:9]` | PORT_33_BUS_NUM |
    | `[14:12]` | PORT_34_BUS_NUM |
    | `[17:15]` | PORT_35_BUS_NUM |
    | `[20:18]` | PORT_36_BUS_NUM |
    | `[23:21]` | PORT_37_BUS_NUM |
    | `[26:24]` | PORT_38_BUS_NUM |
    | `[29:27]` | PORT_39_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_49_40r

- **Address:** `0x00000484`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 40 to Port 49

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_40_BUS_NUM |
    | `[5:3]` | PORT_41_BUS_NUM |
    | `[8:6]` | PORT_42_BUS_NUM |
    | `[11:9]` | PORT_43_BUS_NUM |
    | `[14:12]` | PORT_44_BUS_NUM |
    | `[17:15]` | PORT_45_BUS_NUM |
    | `[20:18]` | PORT_46_BUS_NUM |
    | `[23:21]` | PORT_47_BUS_NUM |
    | `[26:24]` | PORT_48_BUS_NUM |
    | `[29:27]` | PORT_49_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_59_50r

- **Address:** `0x00000488`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 50 to Port 59

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_50_BUS_NUM |
    | `[5:3]` | PORT_51_BUS_NUM |
    | `[8:6]` | PORT_52_BUS_NUM |
    | `[11:9]` | PORT_53_BUS_NUM |
    | `[14:12]` | PORT_54_BUS_NUM |
    | `[17:15]` | PORT_55_BUS_NUM |
    | `[20:18]` | PORT_56_BUS_NUM |
    | `[23:21]` | PORT_57_BUS_NUM |
    | `[26:24]` | PORT_58_BUS_NUM |
    | `[29:27]` | PORT_59_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_69_60r

- **Address:** `0x0000048c`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 50 to Port 59

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_60_BUS_NUM |
    | `[5:3]` | PORT_61_BUS_NUM |
    | `[8:6]` | PORT_62_BUS_NUM |
    | `[11:9]` | PORT_63_BUS_NUM |
    | `[14:12]` | PORT_64_BUS_NUM |
    | `[17:15]` | PORT_65_BUS_NUM |
    | `[20:18]` | PORT_66_BUS_NUM |
    | `[23:21]` | PORT_67_BUS_NUM |
    | `[26:24]` | PORT_68_BUS_NUM |
    | `[29:27]` | PORT_69_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_BUS_MAP_79_70r

- **Address:** `0x00000490`  ·  **Size:** 4 bytes
- **Function:** MIIM BUS MAP FOR Port 50 to Port 59

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | PORT_70_BUS_NUM |
    | `[5:3]` | PORT_71_BUS_NUM |
    | `[8:6]` | PORT_72_BUS_NUM |
    | `[11:9]` | PORT_73_BUS_NUM |
    | `[14:12]` | PORT_74_BUS_NUM |
    | `[17:15]` | PORT_75_BUS_NUM |
    | `[20:18]` | PORT_76_BUS_NUM |
    | `[23:21]` | PORT_77_BUS_NUM |
    | `[26:24]` | PORT_78_BUS_NUM |
    | `[29:27]` | PORT_79_BUS_NUM |
    | `[31:30]` | RESERVED |

---

## CMIC_MIIM_ADDRESSr

- **Address:** `0x000004a0`  ·  **Size:** 4 bytes
- **Function:** Supplies the register address of MIIM reads and writes.\nFor clause 22 devices, bits [4:0] supply the REGAD.\nFor clause 45 devices, bits [20:16] supply the DTYPE,\n                   and bits [15: 0] supply the reg address

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | CLAUSE_45_REGADR |
    | `[4:0]` | CLAUSE_22_REGADR |
    | `[20:16]` | CLAUSE_45_DTYPE |
    | `[31:21]` | RESERVED_1 |

---

## CMIC_MIIM_PROTOCOL_MAPr

- **Address:** `0x000004a4`  ·  **Size:** 4 bytes
- **Function:** Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45\nNote: The bitmap is index by port number.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_INT_SEL_MAPr

- **Address:** `0x000004ac`  ·  **Size:** 4 bytes
- **Function:** Port bitmap specifying whether scan should be done\nfrom internal or external phy.\n0=external phy, 1=internal phy\nNote: The bitmap is index by port number.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_3_0r

- **Address:** `0x000004c0`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 3:0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_0 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_1 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_2 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_3 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_7_4r

- **Address:** `0x000004c4`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 7:4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_4 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_5 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_6 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_7 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_11_8r

- **Address:** `0x000004c8`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 11:8

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_8 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_9 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_10 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_11 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_15_12r

- **Address:** `0x000004cc`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 15:12

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_12 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_13 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_14 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_15 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_19_16r

- **Address:** `0x000004d0`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 19:16

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_16 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_17 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_18 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_19 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_23_20r

- **Address:** `0x000004d4`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 23:20

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_20 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_21 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_22 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_23 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_27_24r

- **Address:** `0x000004d8`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 27:24

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_24 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_25 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_26 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_27 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_31_28r

- **Address:** `0x000004dc`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 31:28

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_28 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_29 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_30 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_31 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_35_32r

- **Address:** `0x000004e0`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 35:32

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_32 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_33 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_34 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_35 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_39_36r

- **Address:** `0x000004e4`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 39:26

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_36 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_37 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_38 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_39 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_43_40r

- **Address:** `0x000004e8`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 43:40

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_40 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_41 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_42 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_43 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_47_44r

- **Address:** `0x000004ec`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 47:44

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_44 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_45 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_46 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_47 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_51_48r

- **Address:** `0x000004f0`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 51:48

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_48 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_49 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_50 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_51 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_55_52r

- **Address:** `0x000004f4`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 55:52

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_52 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_53 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_54 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_55 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_59_56r

- **Address:** `0x000004f8`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 59:56

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_56 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_57 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_58 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_59 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_63_60r

- **Address:** `0x000004fc`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 63:60

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_60 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_61 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_62 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_63 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_XGXS_MDIO_CONFIGr

- **Address:** `0x00000500`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_0r

- **Address:** `0x00000500`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 0 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_1r

- **Address:** `0x00000504`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 1 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_2r

- **Address:** `0x00000508`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 2 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_3r

- **Address:** `0x0000050c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 3 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_4r

- **Address:** `0x00000510`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 4 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_5r

- **Address:** `0x00000514`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 5 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_6r

- **Address:** `0x00000518`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 6 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_7r

- **Address:** `0x0000051c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 7 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_8r

- **Address:** `0x00000520`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 8 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_9r

- **Address:** `0x00000524`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 9 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_10r

- **Address:** `0x00000528`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 10 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_11r

- **Address:** `0x0000052c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 11 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_12r

- **Address:** `0x00000530`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 12 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_13r

- **Address:** `0x00000534`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 13 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_14r

- **Address:** `0x00000538`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 14 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_15r

- **Address:** `0x0000053c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 3 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_16r

- **Address:** `0x00000540`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 16 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_17r

- **Address:** `0x00000544`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 1 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_18r

- **Address:** `0x00000548`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 18 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_19r

- **Address:** `0x0000054c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 3 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_20r

- **Address:** `0x00000550`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 20 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_21r

- **Address:** `0x00000554`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 21 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_22r

- **Address:** `0x00000558`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 22 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_23r

- **Address:** `0x0000055c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 23 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_XGXS_MDIO_CONFIG_24r

- **Address:** `0x00000560`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS MDIO Config 24 register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | IEEE_DEVICES_IN_PKG |
    | `[12:8]` | MD_DEVAD |
    | `[13]` | MD_ST |
    | `[31:14]` | RESERVED_0 |

---

## CMIC_SOFT_RESET_REG_2r

- **Address:** `0x0000057c`  ·  **Size:** 4 bytes
- **Function:** CMIC Soft Reset register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | XQ0_HOTSWAP_RST_L |
    | `[1]` | XQ1_HOTSWAP_RST_L |
    | `[2]` | XQ2_HOTSWAP_RST_L |
    | `[3]` | XQ3_HOTSWAP_RST_L |
    | `[4]` | XQ4_HOTSWAP_RST_L |
    | `[5]` | XQ5_HOTSWAP_RST_L |
    | `[6]` | NS_RST_L |

---

## CMIC_SOFT_RESET_REGr

- **Address:** `0x00000580`  ·  **Size:** 4 bytes
- **Function:** CMIC Soft Reset register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | CMIC_PG0_RST_L |
    | `[1]` | CMIC_PG1_RST_L |
    | `[2]` | CMIC_PG2_RST_L |
    | `[3]` | CMIC_PG3_RST_L |
    | `[4]` | CMIC_MMU_RST_L |
    | `[5]` | CMIC_IP_RST_L |
    | `[6]` | CMIC_EP_RST_L |
    | `[7]` | CMIC_XG_PLL0_RST_L |
    | `[8]` | CMIC_XG_PLL1_RST_L |
    | `[9]` | CMIC_XG_PLL2_RST_L |
    | `[10]` | CMIC_XG_PLL3_RST_L |
    | `[11]` | CMIC_TEMP_MON_PEAK_RST_L |
    | `[12]` | CMIC_XG_PLL0_POST_RST_L |
    | `[13]` | CMIC_XG_PLL1_POST_RST_L |
    | `[14]` | CMIC_XG_PLL2_POST_RST_L |
    | `[15]` | CMIC_XG_PLL3_POST_RST_L |

---

## CMIC_XGXS0_PLL_CONTROL_1r

- **Address:** `0x00000584`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 0 Control register 1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_MDIV |
    | `[15:8]` | CH3_MDIV |
    | `[23:16]` | CH4_MDIV |
    | `[31:24]` | CH5_MDIV |

---

## CMIC_XGXS0_PLL_CONTROL_2r

- **Address:** `0x00000588`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 0 PLL Control register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | HOLD_CH |
    | `[11:6]` | LOAD_EN_CH |
    | `[14:12]` | KA |
    | `[17:15]` | KI |
    | `[21:18]` | KP |
    | `[24:22]` | PDIV |

---

## CMIC_XGXS0_PLL_CONTROL_3r

- **Address:** `0x0000058c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 0 Control register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | NDIV_INT |
    | `[10:8]` | CH0_MDEL |
    | `[13:11]` | CH3_MDEL |
    | `[16:14]` | CH4_MDEL |
    | `[19:17]` | CH5_MDEL |

---

## CMIC_XGXS0_PLL_CONTROL_4r

- **Address:** `0x00000590`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 0 PLL Control register 4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | DCO_CTRL_BYPASS |
    | `[12]` | DCO_CTRL_BYPASS_ENABLE |
    | `[13]` | STAT_RESET |
    | `[16:14]` | STAT_SELECT |
    | `[17]` | STAT_UPDATE |
    | `[18]` | REFCLKOUT |
    | `[19]` | AUX_CTRL |
    | `[20]` | VCODIV2 |
    | `[21]` | CML_BYP_EN |
    | `[22]` | CML_OUTPUT_EN |
    | `[23]` | TESTOUT_EN |
    | `[25:24]` | ANA_LDO_CTRL |
    | `[27:26]` | DIG_LDO_CTRL |
    | `[28]` | CML_2ED_OUT_EN |
    | `[29]` | TESTOUT2_EN |

---

## CMIC_XGXS0_PLL_STATUSr

- **Address:** `0x00000594`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 0 PLL Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | XGPLL_STATUS |
    | `[31]` | CMIC_XGPLL_LOCK |

---

## CMIC_XGXS1_PLL_CONTROL_1r

- **Address:** `0x00000598`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_MDIV |
    | `[15:8]` | CH3_MDIV |
    | `[23:16]` | CH4_MDIV |
    | `[31:24]` | CH5_MDIV |

---

## CMIC_XGXS1_PLL_CONTROL_2r

- **Address:** `0x0000059c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | HOLD_CH |
    | `[11:6]` | LOAD_EN_CH |
    | `[14:12]` | KA |
    | `[17:15]` | KI |
    | `[21:18]` | KP |
    | `[24:22]` | PDIV |

---

## CMIC_XGXS1_PLL_CONTROL_3r

- **Address:** `0x000005a0`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | NDIV_INT |
    | `[10:8]` | CH0_MDEL |
    | `[13:11]` | CH3_MDEL |
    | `[16:14]` | CH4_MDEL |
    | `[19:17]` | CH5_MDEL |

---

## CMIC_XGXS1_PLL_CONTROL_4r

- **Address:** `0x000005a4`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | DCO_CTRL_BYPASS |
    | `[12]` | DCO_CTRL_BYPASS_ENABLE |
    | `[13]` | STAT_RESET |
    | `[16:14]` | STAT_SELECT |
    | `[17]` | STAT_UPDATE |
    | `[18]` | REFCLKOUT |
    | `[19]` | AUX_CTRL |
    | `[20]` | VCODIV2 |
    | `[21]` | CML_BYP_EN |
    | `[22]` | CML_OUTPUT_EN |
    | `[23]` | TESTOUT_EN |
    | `[25:24]` | ANA_LDO_CTRL |
    | `[27:26]` | DIG_LDO_CTRL |
    | `[28]` | CML_2ED_OUT_EN |
    | `[29]` | TESTOUT2_EN |

---

## CMIC_XGXS1_PLL_STATUSr

- **Address:** `0x000005a8`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 1 PLL Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | XGPLL_STATUS |
    | `[31]` | CMIC_XGPLL_LOCK |

---

## CMIC_XGXS2_PLL_CONTROL_1r

- **Address:** `0x000005ac`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_MDIV |
    | `[15:8]` | CH3_MDIV |
    | `[23:16]` | CH4_MDIV |
    | `[31:24]` | CH5_MDIV |

---

## CMIC_XGXS2_PLL_CONTROL_2r

- **Address:** `0x000005b0`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 1 Control register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | HOLD_CH |
    | `[11:6]` | LOAD_EN_CH |
    | `[14:12]` | KA |
    | `[17:15]` | KI |
    | `[21:18]` | KP |
    | `[24:22]` | PDIV |

---

## CMIC_XGXS2_PLL_CONTROL_3r

- **Address:** `0x000005b4`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 2 Control register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | NDIV_INT |
    | `[10:8]` | CH0_MDEL |
    | `[13:11]` | CH3_MDEL |
    | `[16:14]` | CH4_MDEL |
    | `[19:17]` | CH5_MDEL |

---

## CMIC_XGXS2_PLL_CONTROL_4r

- **Address:** `0x000005b8`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 2 Control register 4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | DCO_CTRL_BYPASS |
    | `[12]` | DCO_CTRL_BYPASS_ENABLE |
    | `[13]` | STAT_RESET |
    | `[16:14]` | STAT_SELECT |
    | `[17]` | STAT_UPDATE |
    | `[18]` | REFCLKOUT |
    | `[19]` | AUX_CTRL |
    | `[20]` | VCODIV2 |
    | `[21]` | CML_BYP_EN |
    | `[22]` | CML_OUTPUT_EN |
    | `[23]` | TESTOUT_EN |
    | `[25:24]` | ANA_LDO_CTRL |
    | `[27:26]` | DIG_LDO_CTRL |
    | `[28]` | CML_2ED_OUT_EN |
    | `[29]` | TESTOUT2_EN |

---

## CMIC_XGXS2_PLL_STATUSr

- **Address:** `0x000005bc`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 2 PLL Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | XGPLL_STATUS |
    | `[31]` | CMIC_XGPLL_LOCK |

---

## CMIC_STAT_DMA_PORTNUM_MAP_3_0r

- **Address:** `0x000005c0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 3_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_0 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_1 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_2 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_3 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_7_4r

- **Address:** `0x000005c4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 7_4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_4 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_5 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_6 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_7 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_11_8r

- **Address:** `0x000005c8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 11_8

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_8 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_9 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_10 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_11 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_15_12r

- **Address:** `0x000005cc`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 15_12

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_12 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_13 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_14 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_15 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_19_16r

- **Address:** `0x000005d0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 19_16

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_16 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_17 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_18 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_19 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_23_20r

- **Address:** `0x000005d4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 23_20

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_20 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_21 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_22 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_23 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_27_24r

- **Address:** `0x000005d8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 27_24

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_24 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_25 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_26 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_27 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_31_28r

- **Address:** `0x000005dc`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 31_28

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_28 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_29 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_30 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_31 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_35_32r

- **Address:** `0x000005e0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 35_32

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_32 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_33 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_34 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_35 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_39_36r

- **Address:** `0x000005e4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 39_36

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_36 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_37 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_38 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_39 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_43_40r

- **Address:** `0x000005e8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 43_40

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_40 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_41 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_42 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_43 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_47_44r

- **Address:** `0x000005ec`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 47_44

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_44 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_45 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_46 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_47 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_51_48r

- **Address:** `0x000005f0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 51_48

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_48 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_49 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_50 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_51 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_55_52r

- **Address:** `0x000005f4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 55_52

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_52 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_53 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_54 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_55 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_59_56r

- **Address:** `0x000005f8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 59_56

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_56 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_57 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_58 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_59 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_63_60r

- **Address:** `0x000005fc`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 63_60

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_60 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_61 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_62 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_63 |
    | `[31]` | RESERVED_3 |

---

## CMIC_PKT_PRI_MAP_TABLEr

- **Address:** `0x00000600`  ·  **Size:** 4 bytes
- **Function:** 802.1p PRI, Traffic Class and CPU Queue ID Map Table (addresses 0x0600 - 0x06fc

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | IEEE_802_1_P |
    | `[6:3]` | MH_TC |
    | `[14:7]` | CPU_TC |

---

## CMIC_LINK_STAT_HIr

- **Address:** `0x00000700`  ·  **Size:** 4 bytes
- **Function:** Link Status Register, upper 32-bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SCAN_PORTS_HIr

- **Address:** `0x00000704`  ·  **Size:** 4 bytes
- **Function:** Scan Ports Register, upper 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_PROTOCOL_MAP_HIr

- **Address:** `0x00000708`  ·  **Size:** 4 bytes
- **Function:** Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45\nNote: The bitmap is index by port number. (upper 32 bits)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_INT_SEL_MAP_HIr

- **Address:** `0x00000710`  ·  **Size:** 4 bytes
- **Function:** Port bitmap specifying whether scan should be done\nfrom internal or external phy.\n0=external phy, 1=internal phy\nNote: The bitmap is index by port number. (upper 32-bits)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_CTRLr

- **Address:** `0x00000714`  ·  **Size:** 4 bytes
- **Function:** CMIC Remote packet Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE_SCHAN_REQUEST |
    | `[1]` | ENABLE_FROMCPU_PACKET |
    | `[2]` | ENABLE_TOCPU_PACKET |
    | `[3]` | VLAN_MATCH |
    | `[4]` | LMAC0_MATCH |
    | `[5]` | LMAC1_MATCH |
    | `[13:6]` | TOCPU_TRUNCATION_SIZE |
    | `[14]` | MH_SRC_PID_ENABLE |
    | `[15]` | CPU_TC_ENABLE |
    | `[16]` | MH_TC_MAP_ENABLE |
    | `[17]` | IEEE_802_1_PRI_MAP_ENABLE |
    | `[31:18]` | RESERVED_1 |

---

## CMIC_PKT_LMAC0_HIr

- **Address:** `0x00000718`  ·  **Size:** 4 bytes
- **Function:** CMIC Local MAC 0 Register Hi

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MAC0_HI |
    | `[31:16]` | RESERVED_1 |

---

## CMIC_PKT_LMAC0_LOr

- **Address:** `0x0000071c`  ·  **Size:** 4 bytes
- **Function:** CMIC Local MAC 0 Register Lo

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_LMAC1_HIr

- **Address:** `0x00000720`  ·  **Size:** 4 bytes
- **Function:** CMIC Local MAC 0 Register Hi

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MAC1_HI |
    | `[31:16]` | RESERVED_1 |

---

## CMIC_PKT_LMAC1_LOr

- **Address:** `0x00000724`  ·  **Size:** 4 bytes
- **Function:** CMIC Local MAC 0 Register Lo

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_VLANr

- **Address:** `0x00000728`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet TPID and VLAN Tag

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | VLAN_ID |
    | `[31:16]` | TPID |

---

## CMIC_PKT_ETHER_SIGr

- **Address:** `0x0000072c`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet Ethertype and Signature

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SIGNATURE |
    | `[31:16]` | ETHERTYPE |

---

## CMIC_PKT_COSr

- **Address:** `0x00000730`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet COS Bitmap

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_PORTSr

- **Address:** `0x00000734`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet Port Bitmap Low 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_PORTS_HIr

- **Address:** `0x00000738`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet Port Bitmap High 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_RMACr

- **Address:** `0x0000073c`  ·  **Size:** 4 bytes
- **Function:** Lower 32 bits of the destination MAC address for all packets that the CMIC generates except for Remote\nPIO replies.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_RMAC_HIr

- **Address:** `0x00000740`  ·  **Size:** 4 bytes
- **Function:** Higher 16 bits of the destination MAC address for all packets that the CMIC generates except for Remote\nPIO replies.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MAC_HI |
    | `[31:16]` | RESERVED |

---

## CMIC_PKT_RMH0r

- **Address:** `0x00000744`  ·  **Size:** 4 bytes
- **Function:** First DWord of the Module Header on an outpoing CMIC packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_RMH1r

- **Address:** `0x00000748`  ·  **Size:** 4 bytes
- **Function:** Second DWord of the Module Header on an outpoing CMIC packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_RMH2r

- **Address:** `0x0000074c`  ·  **Size:** 4 bytes
- **Function:** Third DWord of the Module Header on an outpoing CMIC packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASONr

- **Address:** `0x00000750`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to reinject packets.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASON_HIr

- **Address:** `0x00000754`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to reinject packets. (HI)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASON_DIRECTr

- **Address:** `0x00000758`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to reinject Higig packets.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASON_DIRECT_HIr

- **Address:** `0x0000075c`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to reinject Higig packets. (HI)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASON_MINIr

- **Address:** `0x00000760`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to truncate reinjected packets to a size of 128-bytes.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_REASON_MINI_HIr

- **Address:** `0x00000764`  ·  **Size:** 4 bytes
- **Function:** A bitmap of reason codes (sometimes called CPU opcodes) that cause\nCMIC to truncate reinjected packets to a size of 128-bytes. (HI)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_PORTS_HI_2r

- **Address:** `0x00000768`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet Port Bitmap MSB 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_PORTS_HIr

- **Address:** `0x00000780`  ·  **Size:** 4 bytes
- **Function:** Stat Counter Port Bit Map Register, upper 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_PORT_TYPE_MAP_HIr

- **Address:** `0x00000784`  ·  **Size:** 4 bytes
- **Function:** Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port\nNote: The bitmap is index by port number. (upper 32-bits)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_PKT_RMH3r

- **Address:** `0x00000788`  ·  **Size:** 4 bytes
- **Function:** Fourth DWord of the Module Header on an outpoing CMIC packet.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SCHAN_MESSAGE_EXTr

- **Address:** `0x00000800`  ·  **Size:** 4 bytes
- **Function:** S-bus PIO Message Register Set (extended)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MISC_CONTROLr

- **Address:** `0x00000860`  ·  **Size:** 4 bytes
- **Function:** CMIC Miscel Control Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | XGXS0_PLL_PWRDWN |
    | `[1]` | XGXS1_PLL_PWRDWN |
    | `[2]` | XGXS2_PLL_PWRDWN |
    | `[3]` | XGXS3_PLL_PWRDWN |
    | `[4]` | MISC_PCIE_PARITY_MODE |
    | `[5]` | MDIO_SEL |
    | `[6]` | COSC_TEST_ENABLE |
    | `[7]` | CMIC_TO_CORE_PLL_LOAD |
    | `[8]` | CMIC_TO_XG_PLL0_SW_OVWR |
    | `[9]` | CMIC_TO_XG_PLL1_SW_OVWR |
    | `[10]` | CMIC_TO_XG_PLL2_SW_OVWR |
    | `[11]` | CMIC_TO_XG_PLL3_SW_OVWR |
    | `[12]` | L1_RCVD_SW_OVWR_EN |
    | `[13]` | L1_RCVD_SW_OVWR_VALID |
    | `[14]` | L1_RCVD_SW_OVWR_BKUP_VALID |
    | `[17:15]` | THERMAL_MON_SEL |
    | `[18]` | LINK40G_ENABLE |
    | `[21:19]` | PLL_STATUS_SEL |
    | `[22]` | OOBFC_RX_ENABLE |
    | `[23]` | EXTERNAL_MDIO_MASTER_ENABLE |
    | `[31:24]` | RESERVED_MISC |

---

## CMIC_MIIM_AUTO_SCAN_ADDRESSr

- **Address:** `0x00000864`  ·  **Size:** 4 bytes
- **Function:** CMIC_MIIM_AUTO_SCAN_ADDRESS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[20:0]` | MIIM_DEVICE_ADDRESS |
    | `[21]` | MIIM_DEVICE_ADDRESS_ENABLE |
    | `[26:22]` | MIIM_LINK_STATUS_BIT_POSITION |
    | `[27]` | MIIM_FLIP_STATUS_BIT |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_MISC_STATUSr

- **Address:** `0x00000868`  ·  **Size:** 4 bytes
- **Function:** Miscel Status  Register

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ALL_CORE_PLL_TO_CMIC_LOCK |
    | `[3:1]` | RSRV_1 |
    | `[4]` | PCIE_PHYLINKUP |
    | `[5]` | PCIE_LINK_IN_L23 |
    | `[6]` | CORE_PLL_MSTR_TO_CMIC_LOCK |
    | `[7]` | CORE_PLL0_TO_CMIC_LOCK |
    | `[8]` | CORE_PLL1_TO_CMIC_LOCK |
    | `[9]` | CORE_PLL2_TO_CMIC_LOCK |
    | `[10]` | CORE_PLL3_TO_CMIC_LOCK |
    | `[11]` | CORE_PLL4_TO_CMIC_LOCK |
    | `[12]` | CORE_PLL5_TO_CMIC_LOCK |
    | `[15:13]` | AVS_STATUS |
    | `[27:16]` | PLL_STAT_OUT |
    | `[31:28]` | RSRV_0 |

---

## CMIC_CHIP_PARITY_INTR_STATUSr

- **Address:** `0x00000874`  ·  **Size:** 4 bytes
- **Function:** CMIC_PARITY_INTR_STATUS

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CHIP_PARITY_INTR_ENABLEr

- **Address:** `0x00000878`  ·  **Size:** 4 bytes
- **Function:** CMIC_CHIP_PARITY_INTR_ENABLE

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SCHAN_RCPU_RPIO_MESSAGEr

- **Address:** `0x00000900`  ·  **Size:** 4 bytes
- **Function:** S-bus Remote PIO Message Register Set

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_60_63r

- **Address:** `0x00000958`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 60-63

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_60 |
    | `[13:7]` | REMAP_PORT_61 |
    | `[20:14]` | REMAP_PORT_62 |
    | `[27:21]` | REMAP_PORT_63 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_THERMAL_MON_RESULT_2r

- **Address:** `0x0000095c`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_THERMAL_MON_RESULT_3r

- **Address:** `0x00000960`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_THERMAL_MON_RESULT_4r

- **Address:** `0x00000964`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_THERMAL_MON_RESULT_5r

- **Address:** `0x00000968`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_STAT_DMA_BLKNUM_MAP_69_65r

- **Address:** `0x0000096c`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 69 to 65

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_65 |
    | `[11:6]` | SBUS_BLKNUM_66 |
    | `[17:12]` | SBUS_BLKNUM_67 |
    | `[23:18]` | SBUS_BLKNUM_68 |
    | `[29:24]` | SBUS_BLKNUM_69 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_74_70r

- **Address:** `0x00000970`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 74 to 70

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_70 |
    | `[11:6]` | SBUS_BLKNUM_71 |
    | `[17:12]` | SBUS_BLKNUM_72 |
    | `[23:18]` | SBUS_BLKNUM_73 |
    | `[29:24]` | SBUS_BLKNUM_74 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_79_75r

- **Address:** `0x00000974`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 79 to 75

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_75 |
    | `[11:6]` | SBUS_BLKNUM_76 |
    | `[17:12]` | SBUS_BLKNUM_77 |
    | `[23:18]` | SBUS_BLKNUM_78 |
    | `[29:24]` | SBUS_BLKNUM_79 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_84_80r

- **Address:** `0x00000978`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 84 to 80

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_80 |
    | `[11:6]` | SBUS_BLKNUM_81 |
    | `[17:12]` | SBUS_BLKNUM_82 |
    | `[23:18]` | SBUS_BLKNUM_83 |
    | `[29:24]` | SBUS_BLKNUM_84 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_89_85r

- **Address:** `0x0000097c`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 89 to 85

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_85 |
    | `[11:6]` | SBUS_BLKNUM_86 |
    | `[17:12]` | SBUS_BLKNUM_87 |
    | `[23:18]` | SBUS_BLKNUM_88 |
    | `[29:24]` | SBUS_BLKNUM_89 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_94_90r

- **Address:** `0x00000980`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports 94 to 90

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_90 |
    | `[11:6]` | SBUS_BLKNUM_91 |
    | `[17:12]` | SBUS_BLKNUM_92 |
    | `[23:18]` | SBUS_BLKNUM_93 |
    | `[29:24]` | SBUS_BLKNUM_94 |
    | `[31:30]` | RESERVED |

---

## CMIC_STAT_DMA_BLKNUM_MAP_95r

- **Address:** `0x00000984`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> block-number map, ports  95

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | SBUS_BLKNUM_95 |
    | `[31:6]` | RESERVED |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_67_64r

- **Address:** `0x00000988`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 67:64

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_64 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_65 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_66 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_67 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_71_68r

- **Address:** `0x0000098c`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 71:68

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_68 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_69 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_70 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_71 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_75_72r

- **Address:** `0x00000990`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 75:72

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_72 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_73 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_74 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_75 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_79_76r

- **Address:** `0x00000994`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 79:76

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_76 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_77 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_78 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_79 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTS_HI_2r

- **Address:** `0x00000998`  ·  **Size:** 4 bytes
- **Function:** Stat Counter Port Bit Map Register, upper 32 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_LINK_STAT_HI_2r

- **Address:** `0x0000099c`  ·  **Size:** 4 bytes
- **Function:** Link Status Register, upper 95:64 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_SCAN_PORTS_HI_2r

- **Address:** `0x000009a0`  ·  **Size:** 4 bytes
- **Function:** Scan Ports Register, upper 95:64 bits

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_PROTOCOL_MAP_HI_2r

- **Address:** `0x000009a4`  ·  **Size:** 4 bytes
- **Function:** Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45\nNote: The bitmap is index by port number. (upper 32 bits)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_STAT_DMA_PORTNUM_MAP_67_64r

- **Address:** `0x000009a8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 67_64

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_64 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_65 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_66 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_67 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_71_68r

- **Address:** `0x000009ac`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 71_68

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_68 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_69 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_70 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_71 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_75_72r

- **Address:** `0x000009b0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 75_72

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_72 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_73 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_74 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_75 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_79_76r

- **Address:** `0x000009b4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 79_76

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_76 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_77 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_78 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_79 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_83_80r

- **Address:** `0x000009b8`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 83_80

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_80 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_81 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_82 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_83 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_87_84r

- **Address:** `0x000009bc`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 87_84

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_84 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_85 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_86 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_87 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_91_88r

- **Address:** `0x000009c0`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 91_88

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_88 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_89 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_90 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_91 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORTNUM_MAP_95_92r

- **Address:** `0x000009c4`  ·  **Size:** 4 bytes
- **Function:** Stats DMA port <-> port-number map, ports 95_92

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SBUS_PORTNUM_92 |
    | `[7]` | RESERVED_0 |
    | `[14:8]` | SBUS_PORTNUM_93 |
    | `[15]` | RESERVED_1 |
    | `[22:16]` | SBUS_PORTNUM_94 |
    | `[23]` | RESERVED_2 |
    | `[30:24]` | SBUS_PORTNUM_95 |
    | `[31]` | RESERVED_3 |

---

## CMIC_STAT_DMA_PORT_TYPE_MAP_HI_2r

- **Address:** `0x000009c8`  ·  **Size:** 4 bytes
- **Function:** Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port\nNote: The bitmap is index by port number.

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_INT_SEL_MAP_HI_2r

- **Address:** `0x000009cc`  ·  **Size:** 4 bytes
- **Function:** Port bitmap specifying whether scan should be done\nfrom internal or external phy.\n0=external phy, 1=internal phy\nNote: The bitmap is index by port number. (95:32 bits)

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_83_80r

- **Address:** `0x000009d0`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 83:80

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_80 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_81 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_82 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_83 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_87_84r

- **Address:** `0x000009d4`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 87:84

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_84 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_85 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_86 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_87 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_91_88r

- **Address:** `0x000009d8`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 91:88

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_88 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_89 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_90 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_91 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_44_47r

- **Address:** `0x000009dc`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 44-47

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_44 |
    | `[13:7]` | REMAP_PORT_45 |
    | `[20:14]` | REMAP_PORT_46 |
    | `[27:21]` | REMAP_PORT_47 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_48_51r

- **Address:** `0x000009e0`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 51-48

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_48 |
    | `[13:7]` | REMAP_PORT_49 |
    | `[20:14]` | REMAP_PORT_50 |
    | `[27:21]` | REMAP_PORT_51 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_52_55r

- **Address:** `0x000009e4`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 52-55

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_52 |
    | `[13:7]` | REMAP_PORT_53 |
    | `[20:14]` | REMAP_PORT_54 |
    | `[27:21]` | REMAP_PORT_55 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_56_59r

- **Address:** `0x000009e8`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 56-59

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_56 |
    | `[13:7]` | REMAP_PORT_57 |
    | `[20:14]` | REMAP_PORT_58 |
    | `[27:21]` | REMAP_PORT_59 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_MIIM_EXT_PHY_ADDR_MAP_95_92r

- **Address:** `0x000009ec`  ·  **Size:** 4 bytes
- **Function:** MIIM Phy Address map, Port 95:92

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | PHY_ID_92 |
    | `[7:5]` | RESERVED_0 |
    | `[12:8]` | PHY_ID_93 |
    | `[15:13]` | RESERVED_1 |
    | `[20:16]` | PHY_ID_94 |
    | `[23:21]` | RESERVED_2 |
    | `[28:24]` | PHY_ID_95 |
    | `[31:29]` | RESERVED_3 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAPr

- **Address:** `0x00000d00`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_0 |
    | `[13:7]` | REMAP_PORT_1 |
    | `[20:14]` | REMAP_PORT_2 |
    | `[27:21]` | REMAP_PORT_3 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_0_3r

- **Address:** `0x00000d00`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 0-3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_0 |
    | `[13:7]` | REMAP_PORT_1 |
    | `[20:14]` | REMAP_PORT_2 |
    | `[27:21]` | REMAP_PORT_3 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_4_7r

- **Address:** `0x00000d04`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 4-7

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_4 |
    | `[13:7]` | REMAP_PORT_5 |
    | `[20:14]` | REMAP_PORT_6 |
    | `[27:21]` | REMAP_PORT_7 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_8_11r

- **Address:** `0x00000d08`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 8-11

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_8 |
    | `[13:7]` | REMAP_PORT_9 |
    | `[20:14]` | REMAP_PORT_10 |
    | `[27:21]` | REMAP_PORT_11 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_12_15r

- **Address:** `0x00000d0c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 12_15

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_12 |
    | `[13:7]` | REMAP_PORT_13 |
    | `[20:14]` | REMAP_PORT_14 |
    | `[27:21]` | REMAP_PORT_15 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_16_19r

- **Address:** `0x00000d10`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 16_19

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_16 |
    | `[13:7]` | REMAP_PORT_17 |
    | `[20:14]` | REMAP_PORT_18 |
    | `[27:21]` | REMAP_PORT_19 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_20_23r

- **Address:** `0x00000d14`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 20-23

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_20 |
    | `[13:7]` | REMAP_PORT_21 |
    | `[20:14]` | REMAP_PORT_22 |
    | `[27:21]` | REMAP_PORT_23 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_24_27r

- **Address:** `0x00000d18`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 24_27

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_24 |
    | `[13:7]` | REMAP_PORT_25 |
    | `[20:14]` | REMAP_PORT_26 |
    | `[27:21]` | REMAP_PORT_27 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_28_31r

- **Address:** `0x00000d1c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 28-31

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_28 |
    | `[13:7]` | REMAP_PORT_29 |
    | `[20:14]` | REMAP_PORT_30 |
    | `[27:21]` | REMAP_PORT_31 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_32_35r

- **Address:** `0x00000d20`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 32-35

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_32 |
    | `[13:7]` | REMAP_PORT_33 |
    | `[20:14]` | REMAP_PORT_34 |
    | `[27:21]` | REMAP_PORT_35 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_36_39r

- **Address:** `0x00000d24`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 36-39

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_36 |
    | `[13:7]` | REMAP_PORT_37 |
    | `[20:14]` | REMAP_PORT_38 |
    | `[27:21]` | REMAP_PORT_39 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP0_PORT_ORDER_REMAP_40_43r

- **Address:** `0x00000d28`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 40-43

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_40 |
    | `[13:7]` | REMAP_PORT_41 |
    | `[20:14]` | REMAP_PORT_42 |
    | `[27:21]` | REMAP_PORT_43 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_FIFO_CH0_RD_DMA_CFGr

- **Address:** `0x00000d2c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 Config

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[1]` | ACTIVE |
    | `[1]` | ENABLE_VAL |
    | `[6:2]` | BEAT_COUNT |
    | `[10:7]` | HOST_NUM_ENTRIES_SEL |
    | `[11]` | ERROR |
    | `[25:12]` | TIMEOUT_COUNT |
    | `[30:26]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[31]` | ENABLE_MULTIPLE_SBUS_CMDS |

---

## CMIC_FIFO_CH1_RD_DMA_CFGr

- **Address:** `0x00000d30`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 Config

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[1]` | ACTIVE |
    | `[1]` | ENABLE_VAL |
    | `[6:2]` | BEAT_COUNT |
    | `[10:7]` | HOST_NUM_ENTRIES_SEL |
    | `[11]` | ERROR |
    | `[25:12]` | TIMEOUT_COUNT |
    | `[30:26]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[31]` | ENABLE_MULTIPLE_SBUS_CMDS |

---

## CMIC_FIFO_CH2_RD_DMA_CFGr

- **Address:** `0x00000d34`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 Config

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[1]` | ACTIVE |
    | `[1]` | ENABLE_VAL |
    | `[6:2]` | BEAT_COUNT |
    | `[10:7]` | HOST_NUM_ENTRIES_SEL |
    | `[11]` | ERROR |
    | `[25:12]` | TIMEOUT_COUNT |
    | `[30:26]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[31]` | ENABLE_MULTIPLE_SBUS_CMDS |

---

## CMIC_FIFO_CH3_RD_DMA_CFGr

- **Address:** `0x00000d38`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 Config

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ENABLE |
    | `[1]` | ACTIVE |
    | `[1]` | ENABLE_VAL |
    | `[6:2]` | BEAT_COUNT |
    | `[10:7]` | HOST_NUM_ENTRIES_SEL |
    | `[11]` | ERROR |
    | `[25:12]` | TIMEOUT_COUNT |
    | `[30:26]` | MULTIPLE_SBUS_CMD_SPACING |
    | `[31]` | ENABLE_MULTIPLE_SBUS_CMDS |

---

## CMIC_FIFO_CH0_RD_DMA_SBUS_START_ADDRESSr

- **Address:** `0x00000d3c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH1_RD_DMA_SBUS_START_ADDRESSr

- **Address:** `0x00000d40`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH2_RD_DMA_SBUS_START_ADDRESSr

- **Address:** `0x00000d44`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH3_RD_DMA_SBUS_START_ADDRESSr

- **Address:** `0x00000d48`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH0_RD_DMA_HOSTMEM_START_ADDRESSr

- **Address:** `0x00000d4c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH1_RD_DMA_HOSTMEM_START_ADDRESSr

- **Address:** `0x00000d50`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH2_RD_DMA_HOSTMEM_START_ADDRESSr

- **Address:** `0x00000d54`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH3_RD_DMA_HOSTMEM_START_ADDRESSr

- **Address:** `0x00000d58`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 SBus Address

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH0_RD_DMA_HOSTMEM_READ_PTRr

- **Address:** `0x00000d5c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 Host Memory Read Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH0_RD_DMA_HOSTMEM_WRITE_PTRr

- **Address:** `0x00000d60`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 Host Memory Write Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH1_RD_DMA_HOSTMEM_READ_PTRr

- **Address:** `0x00000d64`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 Host Memory Read Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH1_RD_DMA_HOSTMEM_WRITE_PTRr

- **Address:** `0x00000d68`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 Host Memory Write Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH2_RD_DMA_HOSTMEM_READ_PTRr

- **Address:** `0x00000d6c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 Host Memory Read Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH2_RD_DMA_HOSTMEM_WRITE_PTRr

- **Address:** `0x00000d70`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 Host Memory Write Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH3_RD_DMA_HOSTMEM_READ_PTRr

- **Address:** `0x00000d74`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 Host Memory Read Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH3_RD_DMA_HOSTMEM_WRITE_PTRr

- **Address:** `0x00000d78`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 Host Memory Write Pointer

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_RD_DMA_DEBUGr

- **Address:** `0x00000d7c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Debug

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[4:0]` | BIT_POS |
    | `[0]` | FIFO_CH0_DMA_HOSTMEM_OVERFLOW |
    | `[1]` | FIFO_CH0_DMA_HOSTMEM_TIMEOUT |
    | `[2]` | FIFO_CH1_DMA_HOSTMEM_OVERFLOW |
    | `[3]` | FIFO_CH1_DMA_HOSTMEM_TIMEOUT |
    | `[4]` | FIFO_CH2_DMA_HOSTMEM_OVERFLOW |
    | `[5]` | FIFO_CH2_DMA_HOSTMEM_TIMEOUT |
    | `[6]` | FIFO_CH3_DMA_HOSTMEM_OVERFLOW |
    | `[7]` | BIT_VAL |
    | `[7]` | FIFO_CH3_DMA_HOSTMEM_TIMEOUT |
    | `[8]` | FIFO_RD_DMA_NACK_FATAL |
    | `[31:9]` | RESERVED_0 |

---

## CMIC_FIFO_CH0_RD_DMA_HOSTMEM_THRESHOLDr

- **Address:** `0x00000d80`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 0 Threshold

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH1_RD_DMA_HOSTMEM_THRESHOLDr

- **Address:** `0x00000d84`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 1 Threshold

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH2_RD_DMA_HOSTMEM_THRESHOLDr

- **Address:** `0x00000d88`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 2 Threshold

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_FIFO_CH3_RD_DMA_HOSTMEM_THRESHOLDr

- **Address:** `0x00000d8c`  ·  **Size:** 4 bytes
- **Function:** FIFO Read DMA Channel 3 Threshold

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_COS_CTRL_RX_0r

- **Address:** `0x00000d90`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only the LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_1r

- **Address:** `0x00000d94`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only second LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_2r

- **Address:** `0x00000d98`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only the third LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_3r

- **Address:** `0x00000d9c`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only fourth LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_4r

- **Address:** `0x00000da0`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only the fifth LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_5r

- **Address:** `0x00000da4`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only sixth LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_6r

- **Address:** `0x00000da8`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only the seventh LS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_COS_CTRL_RX_7r

- **Address:** `0x00000dac`  ·  **Size:** 4 bytes
- **Function:** When COS_RX_EN of CMIC_CONFIG is set, this register\nindicates which cos are admitted by channel. This register\ngives only MS byte.

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_COS_BMP |
    | `[15:8]` | CH1_COS_BMP |
    | `[23:16]` | CH2_COS_BMP |
    | `[31:24]` | CH3_COS_BMP |

---

## CMIC_PKT_COS_HIr

- **Address:** `0x00000db8`  ·  **Size:** 4 bytes
- **Function:** CMIC Packet COS values of aceptable CMIC packets(upper 32 CoS values).

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL0_CTRL_STAT_0r

- **Address:** `0x00000dbc`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | DCO_CTRL_BYPASS |
    | `[12]` | DCO_CTRL_BYPASS_ENABLE |
    | `[13]` | STAT_RESET |
    | `[16:14]` | STAT_SELECT |
    | `[17]` | STAT_UPDATE |
    | `[18]` | REFCLKOUT |
    | `[19]` | AUX_CTRL |
    | `[21:20]` | STAT_MODE |
    | `[22]` | TEST_SELECT |
    | `[23]` | TEST_ENABLE |
    | `[25:24]` | PWN_RATE |
    | `[26]` | VCODIV2 |
    | `[27]` | POR_BYPASS |
    | `[28]` | SSC_MODE |
    | `[31:29]` | RESERVED |

---

## CMIC_CORE_PLL0_CTRL_STAT_1r

- **Address:** `0x00000dc0`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[21:0]` | SSC_LIMIT |
    | `[24:22]` | SLV3_CH0_MDEL |
    | `[27:25]` | SLV_KI |
    | `[30:28]` | SLV_KA |
    | `[31]` | RSRV |

---

## CMIC_CORE_PLL0_CTRL_STAT_2r

- **Address:** `0x00000dc4`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SSC_STEP |
    | `[16]` | FB_PHASE_EN |
    | `[20:17]` | MSTR_KP |
    | `[23:21]` | MSTR_KI |
    | `[26:24]` | MSTR_KA |
    | `[30:27]` | SLV_KP |
    | `[31]` | RSRV |

---

## CMIC_CORE_PLL0_CTRL_STAT_3r

- **Address:** `0x00000dc8`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | I_NDIV_INT |
    | `[15:8]` | CH0_MDIV |
    | `[18:16]` | CH0_MDEL |
    | `[21:19]` | I_PDIV |
    | `[24:22]` | SLV0_CH0_MDEL |
    | `[27:25]` | SLV1_CH0_MDEL |
    | `[30:28]` | SLV2_CH0_MDEL |
    | `[31]` | RSVED |

---

## CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_0r

- **Address:** `0x00000dcc`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_0

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_1r

- **Address:** `0x00000dd0`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_1

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_2r

- **Address:** `0x00000dd4`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_2

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_3r

- **Address:** `0x00000dd8`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_3

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_0r

- **Address:** `0x00000ddc`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | SLV0_FB_OFFSET |
    | `[23:12]` | SLV1_FB_OFFSET |
    | `[31:24]` | RSVD |

---

## CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_1r

- **Address:** `0x00000de0`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | SLV2_FB_OFFSET |
    | `[23:12]` | SLV3_FB_OFFSET |
    | `[31:24]` | RSVD |

---

## CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_2r

- **Address:** `0x00000de4`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | SLV4_FB_OFFSET |
    | `[23:12]` | SLV5_FB_OFFSET |
    | `[31:24]` | RSVD |

---

## CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_3r

- **Address:** `0x00000de8`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_3

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_0r

- **Address:** `0x00000dec`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_0

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_1r

- **Address:** `0x00000df0`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_1

**Fields:**

    _(no field breakdown — treated as a single 32-bit value)_

---

## CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_2r

- **Address:** `0x00000df4`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | OSC_ENABLE |
    | `[2:1]` | OSC_0_SEL |
    | `[4:3]` | OSC_1_SEL |
    | `[5]` | OSC_PW_EN |
    | `[6]` | IROSC_EN |
    | `[7]` | IROSC_SEL |
    | `[8]` | OSC_CNT_RSTB |
    | `[9]` | OSC_CNT_START |
    | `[13:10]` | OSC_SEL |
    | `[31:14]` | PLL_CTRL_RSV |

---

## CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_3r

- **Address:** `0x00000df8`  ·  **Size:** 4 bytes
- **Function:** CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | BG_ADJ |
    | `[6:3]` | OUTPUT_CODE |
    | `[15:7]` | RSVD2 |
    | `[18:16]` | MEASUREMENT_CALLIBRATION |
    | `[22:19]` | PROG_RESISTOR |
    | `[25:23]` | RESERVED |
    | `[26]` | PVTMON_RESET_N |
    | `[29:27]` | PVTMON_SELECT |
    | `[30]` | PVTMON_POWREDOWN |
    | `[31]` | VTMON_7_OR_PVTMON_SEL |

---

## CMIC_EB3_VLI_CONFIG_REGISTERr

- **Address:** `0x00000dfc`  ·  **Size:** 4 bytes
- **Function:** CMIC_EB3_CONFIG_REGISTER

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | EB3_PARITY_DEBUG_CTRL_BIT |
    | `[1]` | EB3_PARITY_POLARITY_CFG |
    | `[2]` | EB3_ADDR_PARITY_ENABLE |
    | `[3]` | EB3_DATA_PARITY_ENABLE |
    | `[4]` | VLI_PARITY_DEBUG_CTRL_BIT |
    | `[5]` | VLI_PARITY_POLARITY_CFG |
    | `[6]` | VLI_PARITY_ENABLE |
    | `[31:7]` | RESERVED |

---

## CMIC_LEDUP1_PORT_ORDER_REMAPr

- **Address:** `0x00000e00`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_0 |
    | `[13:7]` | REMAP_PORT_1 |
    | `[20:14]` | REMAP_PORT_2 |
    | `[27:21]` | REMAP_PORT_3 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_0_3r

- **Address:** `0x00000e00`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 0-3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_0 |
    | `[13:7]` | REMAP_PORT_1 |
    | `[20:14]` | REMAP_PORT_2 |
    | `[27:21]` | REMAP_PORT_3 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_4_7r

- **Address:** `0x00000e04`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 4-7

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_4 |
    | `[13:7]` | REMAP_PORT_5 |
    | `[20:14]` | REMAP_PORT_6 |
    | `[27:21]` | REMAP_PORT_7 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_8_11r

- **Address:** `0x00000e08`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 8-11

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_8 |
    | `[13:7]` | REMAP_PORT_9 |
    | `[20:14]` | REMAP_PORT_10 |
    | `[27:21]` | REMAP_PORT_11 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_12_15r

- **Address:** `0x00000e0c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 12_15

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_12 |
    | `[13:7]` | REMAP_PORT_13 |
    | `[20:14]` | REMAP_PORT_14 |
    | `[27:21]` | REMAP_PORT_15 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_16_19r

- **Address:** `0x00000e10`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 16_19

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_16 |
    | `[13:7]` | REMAP_PORT_17 |
    | `[20:14]` | REMAP_PORT_18 |
    | `[27:21]` | REMAP_PORT_19 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_20_23r

- **Address:** `0x00000e14`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 20-23

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_20 |
    | `[13:7]` | REMAP_PORT_21 |
    | `[20:14]` | REMAP_PORT_22 |
    | `[27:21]` | REMAP_PORT_23 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_24_27r

- **Address:** `0x00000e18`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 24_27

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_24 |
    | `[13:7]` | REMAP_PORT_25 |
    | `[20:14]` | REMAP_PORT_26 |
    | `[27:21]` | REMAP_PORT_27 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_28_31r

- **Address:** `0x00000e1c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 28-31

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_28 |
    | `[13:7]` | REMAP_PORT_29 |
    | `[20:14]` | REMAP_PORT_30 |
    | `[27:21]` | REMAP_PORT_31 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_32_35r

- **Address:** `0x00000e20`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 32-35

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_32 |
    | `[13:7]` | REMAP_PORT_33 |
    | `[20:14]` | REMAP_PORT_34 |
    | `[27:21]` | REMAP_PORT_35 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_36_39r

- **Address:** `0x00000e24`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 36-39

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_36 |
    | `[13:7]` | REMAP_PORT_37 |
    | `[20:14]` | REMAP_PORT_38 |
    | `[27:21]` | REMAP_PORT_39 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_40_43r

- **Address:** `0x00000e28`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 40-43

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_40 |
    | `[13:7]` | REMAP_PORT_41 |
    | `[20:14]` | REMAP_PORT_42 |
    | `[27:21]` | REMAP_PORT_43 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_44_47r

- **Address:** `0x00000e2c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 44-47

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_44 |
    | `[13:7]` | REMAP_PORT_45 |
    | `[20:14]` | REMAP_PORT_46 |
    | `[27:21]` | REMAP_PORT_47 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_48_51r

- **Address:** `0x00000e30`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 51-48

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_48 |
    | `[13:7]` | REMAP_PORT_49 |
    | `[20:14]` | REMAP_PORT_50 |
    | `[27:21]` | REMAP_PORT_51 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_52_55r

- **Address:** `0x00000e34`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 52-55

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_52 |
    | `[13:7]` | REMAP_PORT_53 |
    | `[20:14]` | REMAP_PORT_54 |
    | `[27:21]` | REMAP_PORT_55 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_56_59r

- **Address:** `0x00000e38`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 56-59

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_56 |
    | `[13:7]` | REMAP_PORT_57 |
    | `[20:14]` | REMAP_PORT_58 |
    | `[27:21]` | REMAP_PORT_59 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_LEDUP1_PORT_ORDER_REMAP_60_63r

- **Address:** `0x00000e3c`  ·  **Size:** 4 bytes
- **Function:** LEDUP SCan Data Remap register for ports 60-63

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | REMAP_PORT_60 |
    | `[13:7]` | REMAP_PORT_61 |
    | `[20:14]` | REMAP_PORT_62 |
    | `[27:21]` | REMAP_PORT_63 |
    | `[31:28]` | RESERVED_0 |

---

## CMIC_THERMAL_MON_RESULT_6r

- **Address:** `0x00000e40`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 6

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_THERMAL_MON_RESULT_7r

- **Address:** `0x00000e44`  ·  **Size:** 4 bytes
- **Function:** Temperature Monitor Result Register 7

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | TEMP_DATA |
    | `[21:10]` | RESERVED |
    | `[31:22]` | PEAK_TEMP_DATA |

---

## CMIC_XGXS3_PLL_CONTROL_1r

- **Address:** `0x00000e50`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 3 Control register 1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CH0_MDIV |
    | `[15:8]` | CH3_MDIV |
    | `[23:16]` | CH4_MDIV |
    | `[31:24]` | CH5_MDIV |

---

## CMIC_XGXS3_PLL_CONTROL_2r

- **Address:** `0x00000e54`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 3 Control register 2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | HOLD_CH |
    | `[11:6]` | LOAD_EN_CH |
    | `[14:12]` | KA |
    | `[17:15]` | KI |
    | `[21:18]` | KP |
    | `[24:22]` | PDIV |

---

## CMIC_XGXS3_PLL_CONTROL_3r

- **Address:** `0x00000e58`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 3 Control register 3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | NDIV_INT |
    | `[10:8]` | CH0_MDEL |
    | `[13:11]` | CH3_MDEL |
    | `[16:14]` | CH4_MDEL |
    | `[19:17]` | CH5_MDEL |

---

## CMIC_XGXS3_PLL_CONTROL_4r

- **Address:** `0x00000e5c`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS PLL 3 Control register 4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | DCO_CTRL_BYPASS |
    | `[12]` | DCO_CTRL_BYPASS_ENABLE |
    | `[13]` | STAT_RESET |
    | `[16:14]` | STAT_SELECT |
    | `[17]` | STAT_UPDATE |
    | `[18]` | REFCLKOUT |
    | `[19]` | AUX_CTRL |
    | `[20]` | VCODIV2 |
    | `[21]` | CML_BYP_EN |
    | `[22]` | CML_OUTPUT_EN |
    | `[23]` | TESTOUT_EN |
    | `[25:24]` | ANA_LDO_CTRL |
    | `[27:26]` | DIG_LDO_CTRL |
    | `[28]` | CML_2ED_OUT_EN |
    | `[29]` | TESTOUT2_EN |

---

## CMIC_XGXS3_PLL_STATUSr

- **Address:** `0x00000e60`  ·  **Size:** 4 bytes
- **Function:** CMIC XGXS 3 PLL Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | XGPLL_STATUS |
    | `[31]` | CMIC_XGPLL_LOCK |

---

## CMIC_CORE_PLL0_CTRL_STAT_4r

- **Address:** `0x00000e64`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | I_LOAD_EN |
    | `[11:6]` | I_HOLD |
    | `[19:12]` | SLV_I_NDIV_INT |
    | `[27:20]` | SLV_CH0_MDIV |
    | `[30:28]` | SLV_I_PDIV |
    | `[31]` | RSVED |

---

## CMIC_LEDUP0_CTRLr

- **Address:** `0x00001000`  ·  **Size:** 4 bytes
- **Function:** LEDUP0 Control

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LEDUP_EN |
    | `[3:1]` | LEDUP_SCAN_INTRA_PORT_DELAY |
    | `[7:4]` | LEDUP_SCAN_START_DELAY |

---

## CMIC_LEDUP0_STATUSr

- **Address:** `0x00001004`  ·  **Size:** 4 bytes
- **Function:** LEDUP0 Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PROGRAM_COUNTER |
    | `[8]` | LEDUP_RUNNING |
    | `[9]` | LEDUP_INITIALISING |
    | `[31:10]` | RESERVED |

---

## CMIC_LEDUP0_SCANCHAIN_ASSEMBLY_ST_ADDRr

- **Address:** `0x00001008`  ·  **Size:** 4 bytes
- **Function:** LEDUP0 scanchain assembly start address

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | SCANCHAIN_ASSEMBLY_ST_ADDR |

---

## CMIC_LEDUP0_DATA_RAMr

- **Address:** `0x00001400`  ·  **Size:** 4 bytes
- **Function:** LEDUP0 Data RAM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | DATA |

---

## CMIC_LEDUP0_PROGRAM_RAMr

- **Address:** `0x00001800`  ·  **Size:** 4 bytes
- **Function:** LEDUP0 Program RAM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | DATA |

---

## CMIC_LEDUP1_CTRLr

- **Address:** `0x00002000`  ·  **Size:** 4 bytes
- **Function:** LEDUP1 Control

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LEDUP_EN |
    | `[3:1]` | LEDUP_SCAN_INTRA_PORT_DELAY |
    | `[7:4]` | LEDUP_SCAN_START_DELAY |

---

## CMIC_LEDUP1_STATUSr

- **Address:** `0x00002004`  ·  **Size:** 4 bytes
- **Function:** LEDUP1 Status

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PROGRAM_COUNTER |
    | `[8]` | LEDUP_RUNNING |
    | `[9]` | LEDUP_INITIALISING |
    | `[31:10]` | RESERVED |

---

## CMIC_LEDUP1_SCANCHAIN_ASSEMBLY_ST_ADDRr

- **Address:** `0x00002008`  ·  **Size:** 4 bytes
- **Function:** LEDUP1 scanchain assembly start address

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | SCANCHAIN_ASSEMBLY_ST_ADDR |

---

## CMIC_LEDUP1_DATA_RAMr

- **Address:** `0x00002400`  ·  **Size:** 4 bytes
- **Function:** LEDUP1 Data RAM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | DATA |

---

## CMIC_LEDUP1_PROGRAM_RAMr

- **Address:** `0x00002800`  ·  **Size:** 4 bytes
- **Function:** LEDUP1 Program RAM

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | DATA |

---


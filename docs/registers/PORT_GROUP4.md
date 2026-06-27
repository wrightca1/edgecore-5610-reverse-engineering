# BCM56846 Registers — PORT_GROUP4 block

_Port group 4 — per-port MAC/PCS block_

25 registers. Source: OpenMDK CDK defs/sym + OpenBCM descriptions + live Cumulus dump.

---

## PORT_GROUP4_TDM_REGr

- **Address:** `0x00580000`  ·  **Size:** 4 bytes

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY0_PORT_ID |
    | `[14:8]` | TDM_ENTRY1_PORT_ID |
    | `[22:16]` | TDM_ENTRY2_PORT_ID |
    | `[30:24]` | TDM_ENTRY3_PORT_ID |

---

## PORT_GROUP4_TDM_REG_0r

- **Address:** `0x00580000`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_0

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY0_PORT_ID |
    | `[14:8]` | TDM_ENTRY1_PORT_ID |
    | `[22:16]` | TDM_ENTRY2_PORT_ID |
    | `[30:24]` | TDM_ENTRY3_PORT_ID |

---

## PORT_GROUP4_TDM_REG_1r

- **Address:** `0x00580001`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_1

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY4_PORT_ID |
    | `[14:8]` | TDM_ENTRY5_PORT_ID |
    | `[22:16]` | TDM_ENTRY6_PORT_ID |
    | `[30:24]` | TDM_ENTRY7_PORT_ID |

---

## PORT_GROUP4_TDM_REG_2r

- **Address:** `0x00580002`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_2

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY8_PORT_ID |
    | `[14:8]` | TDM_ENTRY9_PORT_ID |
    | `[22:16]` | TDM_ENTRY10_PORT_ID |
    | `[30:24]` | TDM_ENTRY11_PORT_ID |

---

## PORT_GROUP4_TDM_REG_3r

- **Address:** `0x00580003`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_3

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY12_PORT_ID |
    | `[14:8]` | TDM_ENTRY13_PORT_ID |
    | `[22:16]` | TDM_ENTRY14_PORT_ID |
    | `[30:24]` | TDM_ENTRY15_PORT_ID |

---

## PORT_GROUP4_TDM_REG_4r

- **Address:** `0x00580004`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_4

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY16_PORT_ID |
    | `[14:8]` | TDM_ENTRY17_PORT_ID |
    | `[22:16]` | TDM_ENTRY18_PORT_ID |
    | `[30:24]` | TDM_ENTRY19_PORT_ID |

---

## PORT_GROUP4_TDM_REG_5r

- **Address:** `0x00580005`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_5

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY20_PORT_ID |
    | `[14:8]` | TDM_ENTRY21_PORT_ID |
    | `[22:16]` | TDM_ENTRY22_PORT_ID |
    | `[30:24]` | TDM_ENTRY23_PORT_ID |

---

## PORT_GROUP4_TDM_REG_6r

- **Address:** `0x00580006`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_6

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY24_PORT_ID |
    | `[14:8]` | TDM_ENTRY25_PORT_ID |
    | `[22:16]` | TDM_ENTRY26_PORT_ID |
    | `[30:24]` | TDM_ENTRY27_PORT_ID |

---

## PORT_GROUP4_TDM_REG_7r

- **Address:** `0x00580007`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE configuration\nHW: PORT_GROUP4_TDM_REG_7

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | TDM_ENTRY28_PORT_ID |
    | `[14:8]` | TDM_ENTRY29_PORT_ID |
    | `[22:16]` | TDM_ENTRY30_PORT_ID |
    | `[30:24]` | TDM_ENTRY31_PORT_ID |

---

## PORT_GROUP4_TDM_CONTROLr

- **Address:** `0x00580008`  ·  **Size:** 4 bytes
- **Function:** TDM TABLE Control\nHW: PORT_GROUP4_TDM_CONTROL

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | DISABLE |
    | `[5:1]` | TDM_WRAP_PTR |
    | `[6]` | PORT_MULTICELL_STR_TDM_EN |

---

## PORT_GROUP4_BOD_FIFO_ECC_ENABLEr

- **Address:** `0x00580009`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_BOD_FIFO_ECC_ENABLE\nHW: PORT_GROUP4_BOD_FIFO_ECC_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | BOD_FIFO_ECC_ENABLE |

---

## PORT_GROUP4_XLPORT_POWER_DOWN_ENABLEr

- **Address:** `0x0058000a`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_XLPORT_POWER_DOWN_ENABLE\nHW: PORT_GROUP4_XLPORT_POWER_DOWN_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PORT_GROUP4_XLPORT0_POWER_DOWN_ENABLE |
    | `[1]` | PORT_GROUP4_XLPORT1_POWER_DOWN_ENABLE |
    | `[2]` | PORT_GROUP4_XLPORT2_POWER_DOWN_ENABLE |
    | `[3]` | PORT_GROUP4_XLPORT3_POWER_DOWN_ENABLE |

---

## PG4_INTR_STATUSr

- **Address:** `0x0058000b`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_INTR_STATUS\nHW: PORT_GROUP4_INTR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | XLP0_PERR_INTR |
    | `[1]` | XLP1_PERR_INTR |
    | `[2]` | XLP2_PERR_INTR |
    | `[3]` | XLP3_PERR_INTR |
    | `[4]` | PG4_PERR_INTR |

---

## PG4_INTR_ENABLEr

- **Address:** `0x0058000c`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_INTR_ENABLE\nHW: PORT_GROUP4_INTR_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | XLP0_PERR_INTR |
    | `[1]` | XLP1_PERR_INTR |
    | `[2]` | XLP2_PERR_INTR |
    | `[3]` | XLP3_PERR_INTR |
    | `[4]` | PG4_PERR_INTR |

---

## PORT_GROUP4_BOD_FIFO_FULL_ERR_STATUSr

- **Address:** `0x0058000d`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_BOD_FIFO_FULL_ERR_STATUS\nHW: PORT_GROUP4_BOD_FIFO_FULL_ERR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PORT_GROUP4_XLPORT0_BOD_FIFO_FULL_ERR_STATUS |
    | `[1]` | PORT_GROUP4_XLPORT1_BOD_FIFO_FULL_ERR_STATUS |
    | `[2]` | PORT_GROUP4_XLPORT2_BOD_FIFO_FULL_ERR_STATUS |
    | `[3]` | PORT_GROUP4_XLPORT3_BOD_FIFO_FULL_ERR_STATUS |

---

## PORT_GROUP4_CTRL_FIFO_FULL_ERR_STATUSr

- **Address:** `0x0058000e`  ·  **Size:** 4 bytes
- **Function:** PORT_GROUP4_CTRL_FIFO_FULL_ERR_STATUS\nHW: PORT_GROUP4_CTRL_FIFO_FULL_ERR_STATUS

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PORT_GROUP4_XLPORT0_CTRL_FIFO_FULL_ERR_STATUS |
    | `[1]` | PORT_GROUP4_XLPORT1_CTRL_FIFO_FULL_ERR_STATUS |
    | `[2]` | PORT_GROUP4_XLPORT2_CTRL_FIFO_FULL_ERR_STATUS |
    | `[3]` | PORT_GROUP4_XLPORT3_CTRL_FIFO_FULL_ERR_STATUS |

---

## PORT_GROUP4_XLP0_BOD_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580010`  ·  **Size:** 4 bytes
- **Function:** XLP0_BOD_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP0_BOD_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP0_CTRL_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580011`  ·  **Size:** 4 bytes
- **Function:** XLP0_CTRL_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP0_CTRL_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP1_BOD_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580012`  ·  **Size:** 4 bytes
- **Function:** XLP1_BOD_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP1_BOD_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP1_CTRL_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580013`  ·  **Size:** 4 bytes
- **Function:** XLP1_CTRL_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP1_CTRL_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP2_BOD_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580014`  ·  **Size:** 4 bytes
- **Function:** XLP2_BOD_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP2_BOD_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP2_CTRL_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580015`  ·  **Size:** 4 bytes
- **Function:** XLP2_CTRL_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP2_CTRL_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP3_BOD_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580016`  ·  **Size:** 4 bytes
- **Function:** XLP3_BOD_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP3_BOD_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_XLP3_CTRL_FIFO_ECC_STATUS_INTRr

- **Address:** `0x00580017`  ·  **Size:** 4 bytes
- **Function:** XLP3_CTRL_FIFO_ECC_STATUS_INTR\nHW: PORT_GROUP4_XLP3_CTRL_FIFO_ECC_STATUS_INTR

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | ECC_ERR |
    | `[1]` | MULTIPLE_ERR |
    | `[2]` | DOUBLE_BIT_ERR |
    | `[7:3]` | ENTRY_IDX |

---

## PORT_GROUP4_ISO_ENABLEr

- **Address:** `0x00580018`  ·  **Size:** 4 bytes
- **Function:** PG4_ISO_ENABLE\nHW: PORT_GROUP4_ISO_ENABLE

**Fields:**

    | Bits | Field |
    |------|-------|
    | `[3:0]` | PG4_ISO_ENABLE |

---


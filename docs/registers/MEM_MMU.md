# BCM56846 Memories (tables) — MMU block

_Memory Management Unit — buffering, queueing, scheduling, flow control_

360 memories.

---

## MMU_THDO_CONFIG_0m

- **Base address:** `0x03300000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC queues in normal (non-VOQ) ports, MMU ports 5 - 32.  Address index = ( port_num - 5 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_0Am

- **Base address:** `0x03300800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_CONFIG_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_0Bm

- **Base address:** `0x03301000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_CONFIG_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## MMU_THDO_CONFIG_1m

- **Base address:** `0x03301800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC queues in normal (non-VOQ) ports, MMU ports 38 - 65.  Address index = ( port_num - 38 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_1Am

- **Base address:** `0x03302000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_CONFIG_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_1Bm

- **Base address:** `0x03302800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_CONFIG_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## MMU_THDO_OFFSET_0m

- **Base address:** `0x03303000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC queues in normal (non-VOQ) ports, MMU ports 5 - 32.  Address index = ( port_num - 5 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_0Am

- **Base address:** `0x03303800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_OFFSET_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_0Bm

- **Base address:** `0x03304000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_OFFSET_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## MMU_THDO_OFFSET_1m

- **Base address:** `0x03304800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC queues in normal (non-VOQ) ports, MMU ports 38 - 65.  Address index = ( port_num - 38 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_1Am

- **Base address:** `0x03305000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_OFFSET_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_1Bm

- **Base address:** `0x03305800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_OFFSET_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## MMU_THDO_CONFIG_EX_0m

- **Base address:** `0x03306000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC extended queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_EX_0Am

- **Base address:** `0x03306800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_CONFIG_EX_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_EX_0Bm

- **Base address:** `0x03307000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_CONFIG_EX_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## MMU_THDO_CONFIG_EX_1m

- **Base address:** `0x03307800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC extended queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_EX_1Am

- **Base address:** `0x03308000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_CONFIG_EX_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## THDO_CONFIG_EX_1Bm

- **Base address:** `0x03308800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_CONFIG_EX_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |
    | `[51:50]` | RESERVED |
    | `[52]` | PARITY |

---

## MMU_THDO_OFFSET_EX_0m

- **Base address:** `0x03309000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC extended queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_EX_0Am

- **Base address:** `0x03309800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_OFFSET_EX_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_EX_0Bm

- **Base address:** `0x0330a000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_OFFSET_EX_0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## MMU_THDO_OFFSET_EX_1m

- **Base address:** `0x0330a800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC extended queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_EX_1Am

- **Base address:** `0x0330b000`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** First physical copy of MMU_THDO_OFFSET_EX_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## THDO_OFFSET_EX_1Bm

- **Base address:** `0x0330b800`  ·  **Entries:** 296  ·  **Entry width:** 7 bytes
- **Function:** Second physical copy of MMU_THDO_OFFSET_EX_1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |
    | `[52]` | PARITY |

---

## MMU_THDO_CONFIG_SP_0m

- **Base address:** `0x0330c000`  ·  **Entries:** 40  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC COS queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |

---

## MMU_THDO_CONFIG_SP_1m

- **Base address:** `0x0330c800`  ·  **Entries:** 40  ·  **Entry width:** 7 bytes
- **Function:** THDO configuration for UC COS queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | Q_SHARED_LIMIT_CELL |
    | `[3:0]` | Q_SHARED_ALPHA_CELL |
    | `[31:16]` | Q_MIN_CELL |
    | `[32]` | Q_LIMIT_ENABLE_CELL |
    | `[33]` | Q_LIMIT_DYNAMIC_CELL |
    | `[34]` | Q_E2E_DS_EN_CELL |
    | `[35]` | Q_COLOR_ENABLE_CELL |
    | `[36]` | Q_COLOR_LIMIT_DYNAMIC_CELL |
    | `[49:37]` | LIMIT_YELLOW_CELL |

---

## MMU_THDO_OFFSET_SP_0m

- **Base address:** `0x0330d000`  ·  **Entries:** 40  ·  **Entry width:** 7 bytes
- **Function:** THDO offset configuration for UC COS queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |

---

## MMU_THDO_OFFSET_SP_1m

- **Base address:** `0x0330d800`  ·  **Entries:** 40  ·  **Entry width:** 7 bytes
- **Function:** THDO offset configuration for UC COS queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | RESET_OFFSET_CELL |
    | `[25:13]` | RESET_OFFSET_YELLOW_CELL |
    | `[51:39]` | LIMIT_RED_CELL |

---

## MMU_THDO_QDRPRST_0m

- **Base address:** `0x03319000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 5 - 32.  Address index = ( port_num - 5 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QDRPRST_1m

- **Base address:** `0x03319800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 38 - 65.  Address index = ( port_num - 38 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QDRPRST_EX_0m

- **Base address:** `0x0331a000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC extended queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QDRPRST_EX_1m

- **Base address:** `0x0331a800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC extended queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QDRPRST_SP_0m

- **Base address:** `0x0331b000`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC COS queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |

---

## MMU_THDO_QDRPRST_SP_1m

- **Base address:** `0x0331b800`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_queue_drop_state_cell reset value for UC COS queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QDRP_RESET |

---

## MMU_THDO_QYELRST_0m

- **Base address:** `0x0331c000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 5 - 32.  Address index = ( port_num - 5 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QYELRST_1m

- **Base address:** `0x0331c800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 38 - 65.  Address index = ( port_num - 38 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QYELRST_EX_0m

- **Base address:** `0x0331d000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC extended queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QYELRST_EX_1m

- **Base address:** `0x0331d800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC extended queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QYELRST_SP_0m

- **Base address:** `0x0331e000`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC COS queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |

---

## MMU_THDO_QYELRST_SP_1m

- **Base address:** `0x0331e800`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_yellow_ds_cell reset value for UC COS queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QYEL_RESET |

---

## MMU_THDO_QREDRST_0m

- **Base address:** `0x0331f000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 5 - 32.  Address index = ( port_num - 5 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QREDRST_1m

- **Base address:** `0x0331f800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC queues in normal (non-VOQ) ports, MMU ports 38 - 65.  Address index = ( port_num - 38 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QREDRST_EX_0m

- **Base address:** `0x03320000`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC extended queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QREDRST_EX_1m

- **Base address:** `0x03320800`  ·  **Entries:** 296  ·  **Entry width:** 3 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC extended queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 74 + ext_queue_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |
    | `[15:13]` | RESERVED |
    | `[16]` | PARITY |

---

## MMU_THDO_QREDRST_SP_0m

- **Base address:** `0x03321000`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC COS queues in VOQ ports, MMU ports 1 - 4.  Address index = ( port_num - 1 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |

---

## MMU_THDO_QREDRST_SP_1m

- **Base address:** `0x03321800`  ·  **Entries:** 40  ·  **Entry width:** 2 bytes
- **Function:** THDO cos_red_ds_cell reset value for UC COS queues in VOQ ports, MMU ports 34 - 37.  Address index = ( port_num - 34 ) * 10 + cos_num.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[12:0]` | QRED_RESET |

---

## MMU_PKTLINKm

- **Base address:** `0x04380000`  ·  **Entries:** 49152  ·  **Entry width:** 3 bytes
- **Function:** PKTLINK

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[16:0]` | DATA |
    | `[15:0]` | NEXT_PTR |
    | `[16]` | NEXT_SCP |
    | `[22:17]` | ECCP |
    | `[21:17]` | ECC |
    | `[22]` | PARITY |

---

## MMU_CPQLINKm

- **Base address:** `0x04390000`  ·  **Entries:** 49152  ·  **Entry width:** 3 bytes
- **Function:** CPQLINK

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | NEXT_PTR |
    | `[16]` | NEXT_SCP |
    | `[22:17]` | ECCP |
    | `[21:17]` | ECC |
    | `[22]` | PARITY |

---

## MMU_UCQ_WPm

- **Base address:** `0x043a0000`  ·  **Entries:** 1152  ·  **Entry width:** 3 bytes
- **Function:** UCQ_WP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | DATA |
    | `[15:0]` | PKT_WR_PTR |
    | `[21:16]` | ECCP |
    | `[20:16]` | ECC |
    | `[21]` | PARITY |

---

## MMU_UCQ_RPm

- **Base address:** `0x043a0800`  ·  **Entries:** 1152  ·  **Entry width:** 3 bytes
- **Function:** UCQ_RP

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[16:0]` | DATA |
    | `[15:0]` | PKT_RD_PTR |
    | `[16]` | PKT_SCP |
    | `[22:17]` | ECCP |
    | `[21:17]` | ECC |
    | `[22]` | PARITY |

---

## ARB_TDM_TABLE_0m

- **Base address:** `0x06300000`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** MMU to EPIPE Arbiter TDM Table, PIPE 0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | PORT_NUM |
    | `[6]` | WRAP_EN |

---

## ARB_TDM_TABLE_1m

- **Base address:** `0x06300100`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** MMU to EPIPE Arbiter TDM Table, PIPE 1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | PORT_NUM |
    | `[6]` | WRAP_EN |

---

## MMU_CFAP_BANK0m

- **Base address:** `0x07300000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK1m

- **Base address:** `0x07300800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK2m

- **Base address:** `0x07301000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK3m

- **Base address:** `0x07301800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK4m

- **Base address:** `0x07302000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK5m

- **Base address:** `0x07302800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK6m

- **Base address:** `0x07303000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK7m

- **Base address:** `0x07303800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK8m

- **Base address:** `0x07304000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK9m

- **Base address:** `0x07304800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK10m

- **Base address:** `0x07305000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK11m

- **Base address:** `0x07305800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK12m

- **Base address:** `0x07306000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK13m

- **Base address:** `0x07306800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK14m

- **Base address:** `0x07307000`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CFAP_BANK15m

- **Base address:** `0x07307800`  ·  **Entries:** 1536  ·  **Entry width:** 4 bytes
- **Function:** CBP Free Address Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[11:0]` | PTR_0 |
    | `[23:12]` | PTR_1 |
    | `[28:24]` | ECC |
    | `[29]` | PARITY |

---

## MMU_CCP_MEMm

- **Base address:** `0x08300000`  ·  **Entries:** 24576  ·  **Entry width:** 3 bytes
- **Function:** Copy Count Pool RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | PTR_0 |
    | `[13:7]` | PTR_1 |
    | `[18:14]` | ECC |
    | `[19]` | PARITY |

---

## MMU_AGING_CTRm

- **Base address:** `0x0d300000`  ·  **Entries:** 8192  ·  **Entry width:** 4 bytes
- **Function:** Aging Counter RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[23:0]` | AGING_CTR |
    | `[24]` | PARITY |

---

## MMU_AGING_EXPm

- **Base address:** `0x0d308000`  ·  **Entries:** 8192  ·  **Entry width:** 2 bytes
- **Function:** Aging Expiration Status RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | AGING_EXP |
    | `[8]` | PARITY |

---

## MMU_CELLCHK0m

- **Base address:** `0x0e300000`  ·  **Entries:** 12288  ·  **Entry width:** 2 bytes
- **Function:** Cell CRC Check

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[10:0]` | ECC |
    | `[11]` | PARITY |

---

## MMU_CELLCHK1m

- **Base address:** `0x0e304000`  ·  **Entries:** 12288  ·  **Entry width:** 2 bytes
- **Function:** Cell CRC Check

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[10:0]` | ECC |
    | `[11]` | PARITY |

---

## MMU_CELLCHK2m

- **Base address:** `0x0e308000`  ·  **Entries:** 12288  ·  **Entry width:** 2 bytes
- **Function:** Cell CRC Check

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[10:0]` | ECC |
    | `[11]` | PARITY |

---

## MMU_CELLCHK3m

- **Base address:** `0x0e30c000`  ·  **Entries:** 12288  ·  **Entry width:** 2 bytes
- **Function:** Cell CRC Check

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[10:0]` | ECC |
    | `[11]` | PARITY |

---

## MMU_CELLLINKm

- **Base address:** `0x0e310000`  ·  **Entries:** 49152  ·  **Entry width:** 3 bytes
- **Function:** CELLLINK

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[17:0]` | DATA |
    | `[15:0]` | NEXT_CELL_PTR |
    | `[16]` | NEXT_CELL_SHARED |
    | `[17]` | NEXT_CELL_END |
    | `[23:18]` | ECCP |
    | `[22:18]` | ECC |
    | `[23]` | PARITY |

---

## MMU_PKTHDRm

- **Base address:** `0x0e330000`  ·  **Entries:** 49152  ·  **Entry width:** 5 bytes
- **Function:** CBP Packet Header RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[27:0]` | DATA |
    | `[13:0]` | PKT_LENGTH |
    | `[20:14]` | PORT_COUNT |
    | `[24:21]` | SPID_BMP |
    | `[25]` | QCN_MSG |
    | `[26]` | FC_SHARED |
    | `[27]` | NO_SW_COPY |
    | `[34]` | PARITY |

---

## MMU_CBPDATA0m

- **Base address:** `0x10300000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 0

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA1m

- **Base address:** `0x10304000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 1

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA2m

- **Base address:** `0x10308000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 2

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA3m

- **Base address:** `0x1030c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 3

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA4m

- **Base address:** `0x10310000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 4

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA5m

- **Base address:** `0x10314000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 5

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA6m

- **Base address:** `0x10318000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 6

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA7m

- **Base address:** `0x1031c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 7

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA8m

- **Base address:** `0x10320000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 8

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA9m

- **Base address:** `0x10324000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 9

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA10m

- **Base address:** `0x10328000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 10

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA11m

- **Base address:** `0x1032c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 11

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA12m

- **Base address:** `0x10330000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 12

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA13m

- **Base address:** `0x10334000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 13

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA14m

- **Base address:** `0x10338000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 14

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA15m

- **Base address:** `0x1033c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 15

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA16m

- **Base address:** `0x10340000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 16

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA17m

- **Base address:** `0x10344000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 17

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA18m

- **Base address:** `0x10348000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 18

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA19m

- **Base address:** `0x1034c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 19

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA20m

- **Base address:** `0x10350000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 20

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA21m

- **Base address:** `0x10354000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 21

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA22m

- **Base address:** `0x10358000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 22

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA23m

- **Base address:** `0x1035c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 23

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA24m

- **Base address:** `0x10360000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 24

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA25m

- **Base address:** `0x10364000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 25

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA26m

- **Base address:** `0x10368000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 26

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA27m

- **Base address:** `0x1036c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 27

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA28m

- **Base address:** `0x10370000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 28

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA29m

- **Base address:** `0x10374000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 29

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA30m

- **Base address:** `0x10378000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 30

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA31m

- **Base address:** `0x1037c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 31

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA32m

- **Base address:** `0x10380000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 32

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA33m

- **Base address:** `0x10384000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 33

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA34m

- **Base address:** `0x10388000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 34

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA35m

- **Base address:** `0x1038c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 35

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA36m

- **Base address:** `0x10390000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 36

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA37m

- **Base address:** `0x10394000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 37

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA38m

- **Base address:** `0x10398000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 38

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA39m

- **Base address:** `0x1039c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 39

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA40m

- **Base address:** `0x103a0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 40

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA41m

- **Base address:** `0x103a4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 41

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA42m

- **Base address:** `0x103a8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 42

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA43m

- **Base address:** `0x103ac000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 43

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA44m

- **Base address:** `0x103b0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 44

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA45m

- **Base address:** `0x103b4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 45

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA46m

- **Base address:** `0x103b8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 46

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA47m

- **Base address:** `0x103bc000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 47

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA48m

- **Base address:** `0x103c0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 48

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA49m

- **Base address:** `0x103c4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 49

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA50m

- **Base address:** `0x103c8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 50

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA51m

- **Base address:** `0x103cc000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 51

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA52m

- **Base address:** `0x11300000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 52

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA53m

- **Base address:** `0x11304000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 53

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA54m

- **Base address:** `0x11308000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 54

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA55m

- **Base address:** `0x1130c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 55

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA56m

- **Base address:** `0x11310000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 56

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA57m

- **Base address:** `0x11314000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 57

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA58m

- **Base address:** `0x11318000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 58

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA59m

- **Base address:** `0x1131c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 59

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA60m

- **Base address:** `0x11320000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 60

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA61m

- **Base address:** `0x11324000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 61

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA62m

- **Base address:** `0x11328000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 62

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA63m

- **Base address:** `0x1132c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 63

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA64m

- **Base address:** `0x11330000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 64

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA65m

- **Base address:** `0x11334000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 65

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA66m

- **Base address:** `0x11338000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 66

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA67m

- **Base address:** `0x1133c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 67

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA68m

- **Base address:** `0x11340000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 68

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA69m

- **Base address:** `0x11344000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 69

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA70m

- **Base address:** `0x11348000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 70

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA71m

- **Base address:** `0x1134c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 71

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA72m

- **Base address:** `0x11350000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 72

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA73m

- **Base address:** `0x11354000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 73

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA74m

- **Base address:** `0x11358000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 74

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA75m

- **Base address:** `0x1135c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 75

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA76m

- **Base address:** `0x11360000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 76

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA77m

- **Base address:** `0x11364000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 77

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA78m

- **Base address:** `0x11368000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 78

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA79m

- **Base address:** `0x1136c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 79

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA80m

- **Base address:** `0x11370000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 80

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA81m

- **Base address:** `0x11374000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 81

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA82m

- **Base address:** `0x11378000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 82

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA83m

- **Base address:** `0x1137c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 83

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA84m

- **Base address:** `0x11380000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 84

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA85m

- **Base address:** `0x11384000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 85

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA86m

- **Base address:** `0x11388000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 86

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA87m

- **Base address:** `0x1138c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 87

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA88m

- **Base address:** `0x11390000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 88

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA89m

- **Base address:** `0x11394000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 89

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA90m

- **Base address:** `0x11398000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 90

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA91m

- **Base address:** `0x1139c000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 91

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA92m

- **Base address:** `0x113a0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 92

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA93m

- **Base address:** `0x113a4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 93

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA94m

- **Base address:** `0x113a8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 94

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA95m

- **Base address:** `0x113ac000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 95

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA96m

- **Base address:** `0x113b0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 96

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA97m

- **Base address:** `0x113b4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 97

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA98m

- **Base address:** `0x113b8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 98

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA99m

- **Base address:** `0x113bc000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 99

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA100m

- **Base address:** `0x113c0000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 100

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA101m

- **Base address:** `0x113c4000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 101

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA102m

- **Base address:** `0x113c8000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 102

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_CBPDATA103m

- **Base address:** `0x113cc000`  ·  **Entries:** 12288  ·  **Entry width:** 8 bytes
- **Function:** CBP Data RAM 103

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_WRED_DROP_CURVE_PROFILE_0m

- **Base address:** `0x173c0000`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile for TCP Green Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_CURVE_PROFILE_1m

- **Base address:** `0x173c0080`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile for TCP Yellow Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_CURVE_PROFILE_2m

- **Base address:** `0x173c0100`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile For TCP Red Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_CURVE_PROFILE_3m

- **Base address:** `0x173c0180`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile For Non-TCP Green Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_CURVE_PROFILE_4m

- **Base address:** `0x173c0200`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile For Non-TCP Yellow Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_CURVE_PROFILE_5m

- **Base address:** `0x173c0280`  ·  **Entries:** 128  ·  **Entry width:** 5 bytes
- **Function:** WRED Drop Curve Profile For Non-TCP Red Traffic

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | MIN_THD |
    | `[31:16]` | MAX_THD |
    | `[35:32]` | MAX_DROP_RATE |
    | `[36]` | RESERVED |
    | `[37]` | PARITY_0 |

---

## MMU_WRED_DROP_THD_UC_ENQ0m

- **Base address:** `0x173c1000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** WRED Unicast Drop Threshold Memory for Enq pipe 0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_0 |
    | `[7:1]` | TCP_GREEN_DROP_THD |
    | `[14:8]` | TCP_YELLOW_DROP_THD |
    | `[21:15]` | TCP_RED_DROP_THD |
    | `[28:22]` | NONTCP_DROP_THD |
    | `[42:36]` | NONTCP_RED_DROP_THD |
    | `[43]` | ECN_MARKING |
    | `[44]` | PARITY_1 |

---

## MMU_WRED_DROP_THD_UC_ENQ1m

- **Base address:** `0x173c1800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** WRED Unicast Drop Threshold Memory for Enq pipe 1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_0 |
    | `[7:1]` | TCP_GREEN_DROP_THD |
    | `[14:8]` | TCP_YELLOW_DROP_THD |
    | `[21:15]` | TCP_RED_DROP_THD |
    | `[28:22]` | NONTCP_DROP_THD |
    | `[42:36]` | NONTCP_RED_DROP_THD |
    | `[43]` | ECN_MARKING |
    | `[44]` | PARITY_1 |

---

## MMU_WRED_DROP_THD_UC_DEQ0m

- **Base address:** `0x173c2000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** WRED Unicast Drop Threshold Memory for Deq pipe 0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_0 |
    | `[7:1]` | TCP_GREEN_DROP_THD |
    | `[14:8]` | TCP_YELLOW_DROP_THD |
    | `[21:15]` | TCP_RED_DROP_THD |
    | `[28:22]` | NONTCP_DROP_THD |
    | `[42:36]` | NONTCP_RED_DROP_THD |
    | `[43]` | ECN_MARKING |
    | `[44]` | PARITY_1 |

---

## MMU_WRED_DROP_THD_UC_DEQ1m

- **Base address:** `0x173c2800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** WRED Unicast Drop Threshold Memory for Deq pipe 1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | PARITY_0 |
    | `[7:1]` | TCP_GREEN_DROP_THD |
    | `[14:8]` | TCP_YELLOW_DROP_THD |
    | `[21:15]` | TCP_RED_DROP_THD |
    | `[28:22]` | NONTCP_DROP_THD |
    | `[42:36]` | NONTCP_RED_DROP_THD |
    | `[43]` | ECN_MARKING |
    | `[44]` | PARITY_1 |

---

## MMU_IPMC_GROUP_TBL1m

- **Base address:** `0x1b300000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL5m

- **Base address:** `0x1b301000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 5

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL9m

- **Base address:** `0x1b302000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 9

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL13m

- **Base address:** `0x1b303000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 13

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL2m

- **Base address:** `0x1b304000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL6m

- **Base address:** `0x1b305000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 6

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL10m

- **Base address:** `0x1b306000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 10

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL14m

- **Base address:** `0x1b307000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 14

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL3m

- **Base address:** `0x1b308000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL7m

- **Base address:** `0x1b309000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 7

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL11m

- **Base address:** `0x1b30a000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 11

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL15m

- **Base address:** `0x1b30b000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 15

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL4m

- **Base address:** `0x1b30c000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 4

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL8m

- **Base address:** `0x1b30d000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 8

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL12m

- **Base address:** `0x1b30e000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 12

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL16m

- **Base address:** `0x1b30f000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 16

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL17m

- **Base address:** `0x1b310000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 17

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL21m

- **Base address:** `0x1b311000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 21

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL25m

- **Base address:** `0x1b312000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 25

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL29m

- **Base address:** `0x1b313000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 29

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL18m

- **Base address:** `0x1b314000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 18

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL22m

- **Base address:** `0x1b315000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 22

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL26m

- **Base address:** `0x1b316000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 26

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL30m

- **Base address:** `0x1b317000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 30

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL19m

- **Base address:** `0x1b318000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 19

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL23m

- **Base address:** `0x1b319000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 23

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL27m

- **Base address:** `0x1b31a000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 27

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL31m

- **Base address:** `0x1b31b000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 31

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL20m

- **Base address:** `0x1b31c000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 20

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL24m

- **Base address:** `0x1b31d000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 24

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL28m

- **Base address:** `0x1b31e000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 28

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL32m

- **Base address:** `0x1b31f000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 32

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL34m

- **Base address:** `0x1b320000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 34

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL38m

- **Base address:** `0x1b321000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 38

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL42m

- **Base address:** `0x1b322000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 42

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL46m

- **Base address:** `0x1b323000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 46

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL35m

- **Base address:** `0x1b324000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 35

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL39m

- **Base address:** `0x1b325000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 39

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL43m

- **Base address:** `0x1b326000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 43

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL47m

- **Base address:** `0x1b327000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 47

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL36m

- **Base address:** `0x1b328000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 36

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL40m

- **Base address:** `0x1b329000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 40

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL44m

- **Base address:** `0x1b32a000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 44

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL48m

- **Base address:** `0x1b32b000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 48

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL37m

- **Base address:** `0x1b32c000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 37

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL41m

- **Base address:** `0x1b32d000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 41

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL45m

- **Base address:** `0x1b32e000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 45

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL49m

- **Base address:** `0x1b32f000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 49

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL50m

- **Base address:** `0x1b330000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 50

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL54m

- **Base address:** `0x1b331000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 54

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL58m

- **Base address:** `0x1b332000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 58

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL62m

- **Base address:** `0x1b333000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 62

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL51m

- **Base address:** `0x1b334000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 51

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL55m

- **Base address:** `0x1b335000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 55

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL59m

- **Base address:** `0x1b336000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 59

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL63m

- **Base address:** `0x1b337000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 63

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL52m

- **Base address:** `0x1b338000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 52

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL56m

- **Base address:** `0x1b339000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 56

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL60m

- **Base address:** `0x1b33a000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 60

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL64m

- **Base address:** `0x1b33b000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 64

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL53m

- **Base address:** `0x1b33c000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 53

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL57m

- **Base address:** `0x1b33d000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 57

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL61m

- **Base address:** `0x1b33e000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 61

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL65m

- **Base address:** `0x1b33f000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 65

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_GROUP_TBL33m

- **Base address:** `0x1b340000`  ·  **Entries:** 4096  ·  **Entry width:** 2 bytes
- **Function:** IPMC VLAN Group Table 33

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[13:0]` | DATA |
    | `[12:0]` | PORT_1STPTR |
    | `[13]` | PORT_LAST |
    | `[14]` | PARITY |

---

## MMU_IPMC_VLAN_TBLm

- **Base address:** `0x1b380000`  ·  **Entries:** 8192  ·  **Entry width:** 12 bytes
- **Function:** IPMC VLAN LSB Bitmap Table RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LAST |
    | `[13:1]` | NEXTPTR |
    | `[17:14]` | MODE_1_BITMAP |
    | `[47:33]` | INTF_NUM_1 |
    | `[62:48]` | INTF_NUM_2 |
    | `[86:78]` | MSB_VLAN |
    | `[87]` | MODE |
    | `[88]` | PARITY |

---

## IPMC_VLAN_TBL0m

- **Base address:** `0x1b384000`  ·  **Entries:** 8192  ·  **Entry width:** 12 bytes
- **Function:** First physical copy of MMU_IPMC_VLAN_TBL

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LAST |
    | `[13:1]` | NEXTPTR |
    | `[17:14]` | MODE_1_BITMAP |
    | `[47:33]` | INTF_NUM_1 |
    | `[62:48]` | INTF_NUM_2 |
    | `[86:78]` | MSB_VLAN |
    | `[87]` | MODE |
    | `[88]` | PARITY |

---

## IPMC_VLAN_TBL1m

- **Base address:** `0x1b388000`  ·  **Entries:** 8192  ·  **Entry width:** 12 bytes
- **Function:** Second physical copy of MMU_IPMC_VLAN_TBL

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | LAST |
    | `[13:1]` | NEXTPTR |
    | `[17:14]` | MODE_1_BITMAP |
    | `[47:33]` | INTF_NUM_1 |
    | `[62:48]` | INTF_NUM_2 |
    | `[86:78]` | MSB_VLAN |
    | `[87]` | MODE |
    | `[88]` | PARITY |

---

## MMU_MC_FIFO1m

- **Base address:** `0x1b3a0000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO5m

- **Base address:** `0x1b3a0400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO9m

- **Base address:** `0x1b3a0800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO13m

- **Base address:** `0x1b3a0c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO2m

- **Base address:** `0x1b3a1000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO6m

- **Base address:** `0x1b3a1400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO10m

- **Base address:** `0x1b3a1800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO14m

- **Base address:** `0x1b3a1c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO3m

- **Base address:** `0x1b3a2000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO7m

- **Base address:** `0x1b3a2400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO11m

- **Base address:** `0x1b3a2800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO15m

- **Base address:** `0x1b3a2c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO4m

- **Base address:** `0x1b3a3000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO8m

- **Base address:** `0x1b3a3400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO12m

- **Base address:** `0x1b3a3800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO16m

- **Base address:** `0x1b3a3c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO17m

- **Base address:** `0x1b3a4000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO21m

- **Base address:** `0x1b3a4400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO25m

- **Base address:** `0x1b3a4800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO29m

- **Base address:** `0x1b3a4c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO18m

- **Base address:** `0x1b3a5000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO22m

- **Base address:** `0x1b3a5400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO26m

- **Base address:** `0x1b3a5800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO30m

- **Base address:** `0x1b3a5c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO19m

- **Base address:** `0x1b3a6000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO23m

- **Base address:** `0x1b3a6400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO27m

- **Base address:** `0x1b3a6800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO31m

- **Base address:** `0x1b3a6c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO20m

- **Base address:** `0x1b3a7000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO24m

- **Base address:** `0x1b3a7400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO28m

- **Base address:** `0x1b3a7800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO32m

- **Base address:** `0x1b3a7c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO34m

- **Base address:** `0x1b3a8000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO38m

- **Base address:** `0x1b3a8400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO42m

- **Base address:** `0x1b3a8800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO46m

- **Base address:** `0x1b3a8c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO35m

- **Base address:** `0x1b3a9000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO39m

- **Base address:** `0x1b3a9400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO43m

- **Base address:** `0x1b3a9800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO47m

- **Base address:** `0x1b3a9c00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO36m

- **Base address:** `0x1b3aa000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO40m

- **Base address:** `0x1b3aa400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO44m

- **Base address:** `0x1b3aa800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO48m

- **Base address:** `0x1b3aac00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO37m

- **Base address:** `0x1b3ab000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO41m

- **Base address:** `0x1b3ab400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO45m

- **Base address:** `0x1b3ab800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO49m

- **Base address:** `0x1b3abc00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO50m

- **Base address:** `0x1b3ac000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO54m

- **Base address:** `0x1b3ac400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO58m

- **Base address:** `0x1b3ac800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO62m

- **Base address:** `0x1b3acc00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO51m

- **Base address:** `0x1b3ad000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO55m

- **Base address:** `0x1b3ad400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO59m

- **Base address:** `0x1b3ad800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO63m

- **Base address:** `0x1b3adc00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO52m

- **Base address:** `0x1b3ae000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO56m

- **Base address:** `0x1b3ae400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO60m

- **Base address:** `0x1b3ae800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO64m

- **Base address:** `0x1b3aec00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO53m

- **Base address:** `0x1b3af000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO57m

- **Base address:** `0x1b3af400`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO61m

- **Base address:** `0x1b3af800`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO65m

- **Base address:** `0x1b3afc00`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_MC_FIFO33m

- **Base address:** `0x1b3b0000`  ·  **Entries:** 1024  ·  **Entry width:** 6 bytes
- **Function:** MC_FIFO1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | L2 |
    | `[1]` | L3 |
    | `[2]` | MR0 |
    | `[3]` | MR1 |
    | `[4]` | MR2 |
    | `[5]` | MR3 |
    | `[17:6]` | MC_INDEX |
    | `[34]` | SCP |
    | `[41:35]` | ECCP |
    | `[40:35]` | ECC |
    | `[41]` | PARITY |

---

## MMU_PQE_MEM0m

- **Base address:** `0x1d300000`  ·  **Entries:** 3168  ·  **Entry width:** 6 bytes
- **Function:** Central Purge Queue RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | CELL_PTR |
    | `[7]` | ECCPBITS |
    | `[18:16]` | SPID |
    | `[19]` | SPID_OVERRIDE |
    | `[23:20]` | PRIORITY |
    | `[30:24]` | SRC_PORT |
    | `[31]` | CELL_EOP |
    | `[39:34]` | ECC |
    | `[34]` | DATAWIDTH |
    | `[40]` | PARITY |

---

## MMU_PQE_MEM1m

- **Base address:** `0x1d301000`  ·  **Entries:** 3168  ·  **Entry width:** 6 bytes
- **Function:** Central Purge Queue RAM

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | CELL_PTR |
    | `[7]` | ECCPBITS |
    | `[18:16]` | SPID |
    | `[19]` | SPID_OVERRIDE |
    | `[23:20]` | PRIORITY |
    | `[30:24]` | SRC_PORT |
    | `[31]` | CELL_EOP |
    | `[39:34]` | ECC |
    | `[34]` | DATAWIDTH |
    | `[40]` | PARITY |

---

## MMU_QCN_ENABLEm

- **Base address:** `0x1e300000`  ·  **Entries:** 66  ·  **Entry width:** 3 bytes
- **Function:** Memory address = dest_port_num\nto enable or disable QCN on per cos queue basis,\nand assign CPQ_index to each QCN enalbed queue (0 or 1).\nOnly up to two CPQs enalbed per egress port.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | COS0_ENABLE |
    | `[0]` | CPQ_EN0 |
    | `[1]` | CPQ_PROFILE_INDEX0 |
    | `[3:2]` | COS1_ENABLE |
    | `[2]` | CPQ_EN1 |
    | `[3]` | CPQ_PROFILE_INDEX1 |
    | `[5:4]` | COS2_ENABLE |
    | `[4]` | CPQ_EN2 |
    | `[5]` | CPQ_PROFILE_INDEX2 |
    | `[7:6]` | COS3_ENABLE |
    | `[6]` | CPQ_EN3 |
    | `[7]` | CPQ_PROFILE_INDEX3 |
    | `[9:8]` | COS4_ENABLE |
    | `[8]` | CPQ_EN4 |
    | `[9]` | CPQ_PROFILE_INDEX4 |
    | `[11:10]` | COS5_ENABLE |
    | `[10]` | CPQ_EN5 |
    | `[11]` | CPQ_PROFILE_INDEX5 |
    | `[13:12]` | COS6_ENABLE |
    | `[12]` | CPQ_EN6 |
    | `[13]` | CPQ_PROFILE_INDEX6 |
    | `[15:14]` | COS7_ENABLE |
    | `[14]` | CPQ_EN7 |
    | `[15]` | CPQ_PROFILE_INDEX7 |
    | `[17:16]` | COS8_ENABLE |
    | `[16]` | CPQ_EN8 |
    | `[17]` | CPQ_PROFILE_INDEX8 |
    | `[19:18]` | COS9_ENABLE |
    | `[18]` | CPQ_EN9 |
    | `[19]` | CPQ_PROFILE_INDEX9 |

---

## MMU_QCN_CPQCFGm

- **Base address:** `0x1e300100`  ·  **Entries:** 66  ·  **Entry width:** 3 bytes
- **Function:** Memory address = dest_port_num\nCPQ configuration

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[9:0]` | CQQCFG0_RANGE |
    | `[4:0]` | QNTZ_ACT_OFFSET0 |
    | `[7:5]` | EQTB_INDEX0 |
    | `[8]` | SITB_SEL0 |
    | `[9]` | OP_MODE0 |
    | `[19:10]` | CQQCFG1_RANGE |
    | `[14:10]` | QNTZ_ACT_OFFSET1 |
    | `[17:15]` | EQTB_INDEX1 |
    | `[18]` | SITB_SEL1 |
    | `[19]` | OP_MODE1 |

---

## MMU_QCN_SITBm

- **Base address:** `0x1e300200`  ·  **Entries:** 128  ·  **Entry width:** 1 bytes
- **Function:** Sample Interval Table.\nTwo Tables, each has 64 entries.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | CPQ_SI |

---

## MMU_QCN_QFBTBm

- **Base address:** `0x1e300400`  ·  **Entries:** 1024  ·  **Entry width:** 1 bytes
- **Function:** The Table to map QuantizedFb[5:0] from PreQntzFb[6:0].\nThere are eight different choices per PreQntzFb.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[5:0]` | CPQ_QNTZFB |

---

## MMU_QCN_CPQST_TSSLSm

- **Base address:** `0x1e300800`  ·  **Entries:** 132  ·  **Entry width:** 3 bytes
- **Function:** Per CPQ state memory for TSSLS.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | CPQ_TSSLS |

---

## MMU_QCN_CPQST_QLENm

- **Base address:** `0x1e301000`  ·  **Entries:** 132  ·  **Entry width:** 3 bytes
- **Function:** Per CPQ state memory for Q length and jitter.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[2:0]` | CPQ_JITTER |
    | `[18:3]` | CPQ_LENOLD |

---

## MMU_QCN_CNM_QUEUE0m

- **Base address:** `0x1e301200`  ·  **Entries:** 150  ·  **Entry width:** 10 bytes
- **Function:** QCN CNM queue.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SP_SOP_CELL_PTR |
    | `[8]` | ECCPBITS |
    | `[16]` | HBFC |
    | `[48:33]` | QOFFSET |
    | `[54:49]` | QNTZFB |
    | `[61:55]` | CP_PORT |
    | `[70]` | CP_Q_PROFILE_INDEX |
    | `[71]` | PURGE |
    | `[78:72]` | ECC |
    | `[72]` | DATAWIDTH |
    | `[79]` | PARITY |

---

## MMU_QCN_CNM_QUEUE1m

- **Base address:** `0x1e301400`  ·  **Entries:** 150  ·  **Entry width:** 10 bytes
- **Function:** QCN CNM queue.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[15:0]` | SP_SOP_CELL_PTR |
    | `[8]` | ECCPBITS |
    | `[16]` | HBFC |
    | `[48:33]` | QOFFSET |
    | `[54:49]` | QNTZFB |
    | `[61:55]` | CP_PORT |
    | `[70]` | CP_Q_PROFILE_INDEX |
    | `[71]` | PURGE |
    | `[78:72]` | ECC |
    | `[72]` | DATAWIDTH |
    | `[79]` | PARITY |

---

## MMU_QCN_CNM_COUNTERm

- **Base address:** `0x1e301600`  ·  **Entries:** 132  ·  **Entry width:** 3 bytes
- **Function:** QCN CNM Counter per CP Queue.

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | CNM_CNT |

---

## MMU_OVQ_BANK0_MEM0m

- **Base address:** `0x1f380000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCP |
    | `[12:1]` | IPMC_INDEX |
    | `[28:13]` | FRAME_PTR |
    | `[31:29]` | COS1 |
    | `[34:32]` | COS2 |
    | `[41:35]` | MTP_3 |
    | `[48:42]` | MTP_2 |
    | `[53:49]` | MTP_1 |

---

## MMU_OVQ_BANK0_MEM1m

- **Base address:** `0x1f384000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | MTP_1 |
    | `[8:2]` | MTP_0 |

---

## MMU_OVQ_BANK0_MEM2m

- **Base address:** `0x1f388000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | L3_BITMAP |

---

## MMU_OVQ_BANK0_MEM3m

- **Base address:** `0x1f38c000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | L2_BITMAP |
    | `[42:35]` | ECC |
    | `[43]` | PARITY |
    | `[53:44]` | UNUSED |

---

## MMU_OVQ_BANK1_MEM0m

- **Base address:** `0x1f390000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK1 MEM0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCP |
    | `[12:1]` | IPMC_INDEX |
    | `[28:13]` | FRAME_PTR |
    | `[31:29]` | COS1 |
    | `[34:32]` | COS2 |
    | `[41:35]` | MTP_3 |
    | `[48:42]` | MTP_2 |
    | `[53:49]` | MTP_1 |

---

## MMU_OVQ_BANK1_MEM1m

- **Base address:** `0x1f394000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK1 MEM1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | MTP_1 |
    | `[8:2]` | MTP_0 |

---

## MMU_OVQ_BANK1_MEM2m

- **Base address:** `0x1f398000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK1 MEM2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | L3_BITMAP |

---

## MMU_OVQ_BANK1_MEM3m

- **Base address:** `0x1f39c000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | L2_BITMAP |
    | `[42:35]` | ECC |
    | `[43]` | PARITY |
    | `[53:44]` | UNUSED |

---

## MMU_OVQ_BANK2_MEM0m

- **Base address:** `0x1f3a0000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK2 MEM0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCP |
    | `[12:1]` | IPMC_INDEX |
    | `[28:13]` | FRAME_PTR |
    | `[31:29]` | COS1 |
    | `[34:32]` | COS2 |
    | `[41:35]` | MTP_3 |
    | `[48:42]` | MTP_2 |
    | `[53:49]` | MTP_1 |

---

## MMU_OVQ_BANK2_MEM1m

- **Base address:** `0x1f3a4000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK2 MEM1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | MTP_1 |
    | `[8:2]` | MTP_0 |

---

## MMU_OVQ_BANK2_MEM2m

- **Base address:** `0x1f3a8000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK2 MEM2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | L3_BITMAP |

---

## MMU_OVQ_BANK2_MEM3m

- **Base address:** `0x1f3ac000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK2 MEM3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | L2_BITMAP |
    | `[42:35]` | ECC |
    | `[43]` | PARITY |
    | `[53:44]` | UNUSED |

---

## MMU_OVQ_BANK3_MEM0m

- **Base address:** `0x1f3b0000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK3 MEM0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCP |
    | `[12:1]` | IPMC_INDEX |
    | `[28:13]` | FRAME_PTR |
    | `[31:29]` | COS1 |
    | `[34:32]` | COS2 |
    | `[41:35]` | MTP_3 |
    | `[48:42]` | MTP_2 |
    | `[53:49]` | MTP_1 |

---

## MMU_OVQ_BANK3_MEM1m

- **Base address:** `0x1f3b4000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK3 MEM1

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | MTP_1 |
    | `[8:2]` | MTP_0 |

---

## MMU_OVQ_BANK3_MEM2m

- **Base address:** `0x1f3b8000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK0 MEM2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[19:0]` | L3_BITMAP |

---

## MMU_OVQ_BANK3_MEM3m

- **Base address:** `0x1f3bc000`  ·  **Entries:** 12288  ·  **Entry width:** 7 bytes
- **Function:** OVQ BANK3 MEM3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | L2_BITMAP |
    | `[42:35]` | ECC |
    | `[43]` | PARITY |
    | `[53:44]` | UNUSED |

---

## MMU_OVQ_DISTRIBUTOR_MEM0m

- **Base address:** `0x1f3c0000`  ·  **Entries:** 128  ·  **Entry width:** 8 bytes
- **Function:** OVQ_DISTRIBUTOR_MEM0

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[0]` | SCP |
    | `[12:1]` | IPMC_INDEX |
    | `[28:13]` | FRAME_PTR |
    | `[39:33]` | MTP_3 |
    | `[46:40]` | MTP_2 |
    | `[53:47]` | MTP_1 |
    | `[60:54]` | MTP_0 |
    | `[63:61]` | L3_BITMAP0 |

---

## MMU_OVQ_DISTRIBUTOR_MEM1m

- **Base address:** `0x1f3c0080`  ·  **Entries:** 128  ·  **Entry width:** 8 bytes
- **Function:** OVQ_DISTRIBUTOR_MEM1

**Entry fields:**

    _(no field breakdown — treated as a single value)_

---

## MMU_OVQ_DISTRIBUTOR_MEM2m

- **Base address:** `0x1f3c0100`  ·  **Entries:** 128  ·  **Entry width:** 8 bytes
- **Function:** OVQ Distributor MEM2

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[1:0]` | L3_BITMAP2 |

---

## MMU_OVQ_DISTRIBUTOR_MEM3m

- **Base address:** `0x1f3c0180`  ·  **Entries:** 128  ·  **Entry width:** 8 bytes
- **Function:** OVQ DISTRIBUTOR MEM3

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | L2_BITMAP1 |
    | `[7]` | MTP_MODE |
    | `[15:8]` | ECC |
    | `[16]` | PARITY |

---

## MMU_CTR_UC_DROP_MEMm

- **Base address:** `0x20300000`  ·  **Entries:** 1152  ·  **Entry width:** 9 bytes
- **Function:** Unicast drop counter mmeory.\nDrop Counters for MMU PORT1 - PORT32,PORT34 - PORT65.\nDrop Counters for CPU & LBP port are in \"MMU_CTR_MC_DROP_MEM\"\nPORT1  - PORT4 have  74 entries per port: 64-73 map to COS0-COS9, 0-63 map to VOQ 64-127\nPORT34 - PORT37 have 74 entries per port: 64-73 map to COS0-COS9, 0-63 map to VOQ 64-127\nPORT5  - PORT32 have 10 entries per port: 0-9 map to COS0-COS9.\nPORT38 - PORT65 have 10 entries per port: 0-9 map to COS0-COS9.\nPort1:  0x0   <= addr <= 0x49    74 entries\nPort2 ...

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | PKT_CNT |
    | `[67]` | PARITY |

---

## MMU_CTR_MC_DROP_MEMm

- **Base address:** `0x20301000`  ·  **Entries:** 373  ·  **Entry width:** 9 bytes
- **Function:** Unicast drop counter mmeory.\nPORT0 - has 48 entries, map to CPU_COS0 - CPU_COS47\nPORT1 - PORT65 have 5 entries per port: 0-4 map to COS0-COS4;\nPort0:  0x0   <= addr <= 0x2F    48 entries\nPort1:  0x30  <= addr <= 0x34    10 entries\nPort2:  0x35  <= addr <= 0x39    10 entries\n...                              10 entries\nport65: 0x170 <= addr <= 0x174   10 entries

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[30:0]` | PKT_CNT |
    | `[67]` | PARITY |

---

## MMU_CTR_COLOR_DROP_MEMm

- **Base address:** `0x20302000`  ·  **Entries:** 330  ·  **Entry width:** 5 bytes
- **Function:** Unicast WRED Color drop counter ,and\nUnicast/Multicast Color drop counter.\n0x0   -  0x41 :  Port0 - Port65 Unicast WRED Red Color drop count\n0x42  -  0x83 :  Port0 - Port65 Unicast WRED Yellow Color drop count\n0x84  -  0xC5 :  Port0 - Port65 Unicast WRED Greeen Color drop count\n0xC6  -  0x107:  Port0 - Port65 Red Color drop count\n0x108 -  0x149:  Port0 - Port65 Yellow Color drop count\n--\n|0x0\n|   Unicast WRED Red Drop CNT\n|\n--\n|0x42\n|   Unicast WRED Yellow Drop CNT\n|\n-\n|0x84\n|   Unicast WRED Gre ...

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[32]` | PARITY |

---

## MMU_CHFC_SYSPORT_MAPPINGm

- **Base address:** `0x22300100`  ·  **Entries:** 32  ·  **Entry width:** 1 bytes
- **Function:** Mapping from channel Flow Control Byte number to System port number

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[6:0]` | SYS_PORT |

---

## MMU_INTFO_TC2PRI_MAPPINGm

- **Base address:** `0x22300200`  ·  **Entries:** 256  ·  **Entry width:** 1 bytes
- **Function:** Channel TC state to Priority mapping

**Entry fields:**

    | Bits | Field |
    |------|-------|
    | `[7:0]` | PRI_BMP |

---

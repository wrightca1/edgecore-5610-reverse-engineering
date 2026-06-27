# AS5610 / BCM56846 Register Index

All 2301 registers implemented on the BCM56840_B0 die (the BCM56846's base chip).
One line each. Full detail in the per-block files under this directory.

| Address | Register | Block | Description |
|---------|----------|-------|-------------|
| `0x00000000` | CMIC_SCHAN_MESSAGEr | CMIC | S-bus PIO Message Register Set |
| `0x00000050` | CMIC_SCHAN_CTRLr | CMIC | Status and Control Register |
| `0x0000005c` | CMIC_SCHAN_ERRr | CMIC | Error Status Register |
| `0x00000060` | CMIC_PCIE_ERROR_STATUSr | CMIC | PCIE Error Status Register |
| `0x00000064` | CMIC_IRQ_STAT_1r | CMIC | Interrupts coming from SBUS Block 0 to 31. |
| `0x00000068` | CMIC_IRQ_STAT_2r | CMIC | Interrupts coming from SBUS Block 32 to 63. |
| `0x0000006c` | CMIC_IRQ_MASK_1r | CMIC | Mask for Interrupts coming from SBUS Block 0 to 31. |
| `0x00000070` | CMIC_IRQ_MASK_2r | CMIC | Mask for Interrupts coming from SBUS Block 32 to 63. |
| `0x00000084` | CMIC_SRAM_TM_CONTROLr | CMIC | This is to configure SRAM macro time margin value. |
| `0x00000088` | CMIC_THERMAL_MON_CTRLr | CMIC | Temperature Monitor Control Register |
| `0x0000008c` | CMIC_THERMAL_MON_CALIBRATIONr | CMIC | Temperature Monitor Calibration Register |
| `0x00000090` | CMIC_THERMAL_MON_RESULT_0r | CMIC | Temperature Monitor Result Register 0 |
| `0x00000094` | CMIC_THERMAL_MON_RESULT_1r | CMIC | Temperature Monitor Result Register 1 |
| `0x00000098` | CMIC_SRAM_TM_CONTROL_2r | CMIC | This is to configure SRAM memory time margin value. |
| `0x00000100` | CMIC_DMA_CTRLr | CMIC | DMA Control Register |
| `0x00000104` | CMIC_DMA_STATr | CMIC | DMA Status and Control Register |
| `0x00000108` | CMIC_BS_INITIAL_CRCr | CMIC | Broadsync CRC8 Initial value |
| `0x0000010c` | CMIC_CONFIGr | CMIC | Configuration Register |
| `0x00000110` | CMIC_DMA_DESC0r | CMIC | DMA Channel 0 Descriptor Address |
| `0x00000114` | CMIC_DMA_DESC1r | CMIC | DMA Channel 1 Descriptor Address |
| `0x00000118` | CMIC_DMA_DESC2r | CMIC | DMA Channel 2 Descriptor Address |
| `0x0000011c` | CMIC_DMA_DESC3r | CMIC | DMA Channel 3 Descriptor Address |
| `0x00000120` | CMIC_I2C_SLAVE_ADDRr | CMIC | I2C Slave Address Register |
| `0x00000124` | CMIC_I2C_DATAr | CMIC | I2C Data Register |
| `0x00000128` | CMIC_I2C_CTRLr | CMIC | I2C Status and Control Register |
| `0x0000012c` | CMIC_I2C_STATr | CMIC | I2C Condition Status Register |
| `0x00000130` | CMIC_I2C_SLAVE_XADDRr | CMIC | I2C Slave Extended Address Register |
| `0x0000013c` | CMIC_I2C_RESETr | CMIC | I2C Soft Reset Register |
| `0x00000140` | CMIC_LINK_STATr | CMIC | Link Status Register |
| `0x00000144` | CMIC_IRQ_STATr | CMIC | Interrupt Status Register |
| `0x00000148` | CMIC_IRQ_MASKr | CMIC | Interrupt Mask Register |
| `0x0000014c` | CMIC_IRQ_STAT_3r | CMIC | Interrupt Status Register 3 |
| `0x00000150` | CMIC_IRQ_MASK_3r | CMIC | Interrupt Mask Register 3 |
| `0x00000154` | CMIC_IRQ_CLR_3r | CMIC | Interrupt Clear Register 3 |
| `0x00000158` | CMIC_MIIM_PARAMr | CMIC | MIIM Parameter Register |
| `0x0000015c` | CMIC_MIIM_READ_DATAr | CMIC | MIIM Read Data Register |
| `0x00000160` | CMIC_SCAN_PORTSr | CMIC | Scan Ports Register |
| `0x00000164` | CMIC_STAT_DMA_ADDRr | CMIC | Stats memory start address |
| `0x00000168` | CMIC_STAT_DMA_SETUPr | CMIC | Stat Counter DMA Access Setup Register |
| `0x0000016c` | CMIC_STAT_DMA_PORTSr | CMIC | Stat Counter Port Bit Map Register |
| `0x00000170` | CMIC_STAT_DMA_CURRENTr | CMIC | Current Stat Counter Value Register |
| `0x00000174` | CMIC_ENDIANESS_SELr | CMIC | Endianness selection register (for various CMIC operations) |
| `0x00000178` | CMIC_DEV_REV_IDr | CMIC | Device/revision ID |
| `0x0000017c` | CMIC_SWITCH_FEATURE_ENABLEr | CMIC | Bond feature enable |
| `0x00000188` | CMIC_PCIE_MISCELr | CMIC | Miscellaneous registers for CMIC PCIE interface |
| `0x00000194` | CMIC_TAP_CONTROLr | CMIC | Must follow TAP protocol to initiate BIST and read BIST results |
| `0x000001b0` | CMIC_RATE_ADJUST_STDMAr | CMIC | The clock divider configuration register for Stats DMA. |
| `0x000001b4` | CMIC_RATE_ADJUST_I2Cr | CMIC | The clock divider configuration register for I2C. |
| `0x000001b8` | CMIC_RATE_ADJUSTr | CMIC | Various parts of the chip involved in rate control |
| `0x000001bc` | CMIC_RATE_ADJUST_INT_MDIOr | CMIC | The clock divider configuration register for Internal MDIO. |
| `0x000001c0` | CMIC_PKT_COUNT_SCHANr | CMIC | Counter: number of SCHAN_REQUEST packets received |
| `0x000001c4` | CMIC_PKT_COUNT_SCHAN_REPr | CMIC | Counter: number of SCHAN_REPLY packets sent |
| `0x000001c8` | CMIC_PKT_COUNT_FROMCPU_MHr | CMIC | Counter: number of FROMCPU_PACKET packets received |
| `0x000001cc` | CMIC_PKT_COUNT_FROMCPUr | CMIC | Counter: number of FROMCPU_PACKET packets received |
| `0x000001d0` | CMIC_PKT_COUNT_TOCPUDMr | CMIC | Counter: number of packets sent by means of |
| `0x000001d4` | CMIC_PKT_COUNT_TOCPUDr | CMIC | Counter: number of packets sent by means of |
| `0x000001d8` | CMIC_PKT_COUNT_TOCPUEMr | CMIC | Counter: number of packets sent by means of |
| `0x000001dc` | CMIC_PKT_COUNT_TOCPUEr | CMIC | Counter: number of packets sent by means of |
| `0x000001e0` | CMIC_PKT_COUNT_TOCPUNr | CMIC | Counter: number of packets dropped because they did not match |
| `0x000001e4` | CMIC_FIFO_DMA_SB_ARB_CTRLr | CMIC | For SBus arbitration, 8 round-robin slots are available to any requester. |
| `0x00000200` | CMIC_SBUS_TIMEOUTr | CMIC | Secret register that allows software to program the |
| `0x00000204` | CMIC_SBUS_RING_MAP_0r | CMIC | Map of S-bus agents (0 to 7) on all S-bus rings in the chip |
| `0x00000208` | CMIC_SBUS_RING_MAP_1r | CMIC | Map of S-bus agents (8 to 15) on all S-bus rings in the chip |
| `0x0000020c` | CMIC_SBUS_RING_MAP_2r | CMIC | Map of S-bus agents (16 to 23) on all S-bus rings in the chip |
| `0x00000210` | CMIC_SBUS_RING_MAP_3r | CMIC | Map of S-bus agents (24 to 31) on all S-bus rings in the chip |
| `0x00000214` | CMIC_SBUS_RING_MAP_4r | CMIC | Map of S-bus agents (32 to 39) on all S-bus rings in the chip |
| `0x00000218` | CMIC_SBUS_RING_MAP_5r | CMIC | Map of S-bus agents (40 to 47) on all S-bus rings in the chip |
| `0x0000021c` | CMIC_SBUS_RING_MAP_6r | CMIC | Map of S-bus agents (48 to 55) on all S-bus rings in the chip |
| `0x00000220` | CMIC_SBUS_RING_MAP_7r | CMIC | Map of S-bus agents (56 to 63) on all S-bus rings in the chip |
| `0x00000224` | CMIC_SER_START_ADDR_0r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000228` | CMIC_SER_START_ADDR_1r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000022c` | CMIC_SER_START_ADDR_2r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000230` | CMIC_SER_START_ADDR_3r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000234` | CMIC_SER_START_ADDR_4r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000238` | CMIC_SER_START_ADDR_5r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000023c` | CMIC_SER_START_ADDR_6r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000240` | CMIC_SER_START_ADDR_7r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000244` | CMIC_SER_START_ADDR_8r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000248` | CMIC_SER_START_ADDR_9r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000024c` | CMIC_SER_START_ADDR_10r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000250` | CMIC_SER_START_ADDR_11r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000254` | CMIC_SER_START_ADDR_12r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000258` | CMIC_SER_START_ADDR_13r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000025c` | CMIC_SER_START_ADDR_14r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000260` | CMIC_SER_START_ADDR_15r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000264` | CMIC_SER_END_ADDR_0r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000268` | CMIC_SER_END_ADDR_1r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000026c` | CMIC_SER_END_ADDR_2r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000270` | CMIC_SER_END_ADDR_3r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000274` | CMIC_SER_END_ADDR_4r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000278` | CMIC_SER_END_ADDR_5r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000027c` | CMIC_SER_END_ADDR_6r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000280` | CMIC_SER_END_ADDR_7r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000284` | CMIC_SER_END_ADDR_8r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000288` | CMIC_SER_END_ADDR_9r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000028c` | CMIC_SER_END_ADDR_10r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000290` | CMIC_SER_END_ADDR_11r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000294` | CMIC_SER_END_ADDR_12r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x00000298` | CMIC_SER_END_ADDR_13r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x0000029c` | CMIC_SER_END_ADDR_14r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x000002a0` | CMIC_SER_END_ADDR_15r | CMIC | This register holds the entry SBUS address starting from which protection is enabled. |
| `0x000002a4` | CMIC_SER_MEM_ADDR_0r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002a8` | CMIC_SER_MEM_ADDR_1r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002ac` | CMIC_SER_MEM_ADDR_2r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002b0` | CMIC_SER_MEM_ADDR_3r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002b4` | CMIC_SER_MEM_ADDR_4r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002b8` | CMIC_SER_MEM_ADDR_5r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002bc` | CMIC_SER_MEM_ADDR_6r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002c0` | CMIC_SER_MEM_ADDR_7r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002c4` | CMIC_SER_MEM_ADDR_8r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002c8` | CMIC_SER_MEM_ADDR_9r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002cc` | CMIC_SER_MEM_ADDR_10r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002d0` | CMIC_SER_MEM_ADDR_11r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002d4` | CMIC_SER_MEM_ADDR_12r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002d8` | CMIC_SER_MEM_ADDR_13r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002dc` | CMIC_SER_MEM_ADDR_14r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002e0` | CMIC_SER_MEM_ADDR_15r | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002e4` | CMIC_SER_FAIL_CNTr | CMIC | This register holds the parity storage memory address and parity for this range will be st |
| `0x000002e8` | CMIC_SER_FAIL_ENTRYr | CMIC | This is the sbus addrss of the entry for which parity check fail. |
| `0x000002f0` | CMIC_SER_MEM_ADDRr | CMIC | Parity storage address. |
| `0x000002f4` | CMIC_STAT_DMA_BLKNUM_MAP_4_0r | CMIC | Stats DMA port <-> block-number map, ports 4 to 0 |
| `0x000002f8` | CMIC_STAT_DMA_BLKNUM_MAP_9_5r | CMIC | Stats DMA port <-> block-number map, ports 9 to 5 |
| `0x000002fc` | CMIC_STAT_DMA_BLKNUM_MAP_14_10r | CMIC | Stats DMA port <-> block-number map, ports 14 to 10 |
| `0x00000300` | CMIC_STAT_DMA_BLKNUM_MAP_19_15r | CMIC | Stats DMA port <-> block-number map, ports 19 to 15 |
| `0x00000304` | CMIC_STAT_DMA_BLKNUM_MAP_24_20r | CMIC | Stats DMA port <-> block-number map, ports 19 to 15 |
| `0x00000308` | CMIC_STAT_DMA_BLKNUM_MAP_29_25r | CMIC | Stats DMA port <-> block-number map, ports 29 to 25 |
| `0x0000030c` | CMIC_STAT_DMA_BLKNUM_MAP_34_30r | CMIC | Stats DMA port <-> block-number map, ports 34 to 30 |
| `0x00000310` | CMIC_STAT_DMA_BLKNUM_MAP_39_35r | CMIC | Stats DMA port <-> block-number map, ports 39 to 35 |
| `0x00000314` | CMIC_STAT_DMA_BLKNUM_MAP_44_40r | CMIC | Stats DMA port <-> block-number map, ports 44 to 40 |
| `0x00000318` | CMIC_STAT_DMA_BLKNUM_MAP_49_45r | CMIC | Stats DMA port <-> block-number map, ports 49 to 45 |
| `0x0000031c` | CMIC_STAT_DMA_BLKNUM_MAP_54_50r | CMIC | Stats DMA port <-> block-number map, ports 54 to 50 |
| `0x00000320` | CMIC_STAT_DMA_BLKNUM_MAP_59_55r | CMIC | Stats DMA port <-> block-number map, ports 59 to 55 |
| `0x00000324` | CMIC_STAT_DMA_BLKNUM_MAP_64_60r | CMIC | Stats DMA port <-> block-number map, ports 64 to 60 |
| `0x00000328` | CMIC_SER_PROTECT_ADDR_RANGE_VALIDr | CMIC | Bitmap of Valid SER address ranges |
| `0x0000032c` | CMIC_SER_PARITY_MODE_SELr | CMIC | Select number of parity bits for a given range. 0- 1 bit, 1- 2 bit, 2- 4 bit, 3- 8 bits |
| `0x00000330` | CMIC_MMU_COSLC_COUNT_DATAr | CMIC | Every time S/W does a read of this register, CMIC requests MMU for coslc_count of CMIC_MMU |
| `0x00000334` | CMIC_MMU_COSLC_COUNT_ADDRr | CMIC | When S/W does a read of CMIC_MMU_COSLC_COUNT_DATA register, CMIC returns COSLC_COUNTER val |
| `0x00000338` | CMIC_BS_DRIFT_RATEr | CMIC | Register for Drift adjustment. |
| `0x0000033c` | CMIC_BS_OFFSET_ADJUST_0r | CMIC | OFFSET ADJUSTMENT. |
| `0x00000340` | CMIC_BS_OFFSET_ADJUST_1r | CMIC | OFFSET ADJUSTMENT. |
| `0x00000344` | CMIC_BS_CONFIGr | CMIC | Broadsync interface configuration. |
| `0x00000348` | CMIC_BS_CLK_CTRL_0r | CMIC | Broadsync clock synthesis control. |
| `0x0000034c` | CMIC_BS_CLK_CTRL_1r | CMIC | Broadsync clock synthesis control. |
| `0x00000350` | CMIC_BS_CLK_TOGGLE_TIME_0r | CMIC | This registers hold the next time value when Broadsync output clock should toggle. |
| `0x00000354` | CMIC_BS_CLK_TOGGLE_TIME_1r | CMIC | This registers hold the next time value when Broadsync output clock should toggle. |
| `0x00000358` | CMIC_BS_CLK_TOGGLE_TIME_2r | CMIC | This registers hold the next time value when Broadsync output clock should toggle. |
| `0x0000035c` | CMIC_BS_HEARTBEAT_CTRLr | CMIC | Heartbeat generation control. |
| `0x00000360` | CMIC_BS_INPUT_TIME_0r | CMIC | data received on Broadsync interface. |
| `0x00000364` | CMIC_BS_INPUT_TIME_1r | CMIC | data received on Broadsync interface. |
| `0x00000368` | CMIC_BS_INPUT_TIME_2r | CMIC | data received on Broadsync interface. |
| `0x0000036c` | CMIC_BS_CAPTURE_CTRLr | CMIC | Time capture logic control. |
| `0x00000370` | CMIC_BS_CAPTURE_STATUSr | CMIC | Time capture logic status. |
| `0x00000374` | CMIC_BS_CAPTURE_FREE_RUN_TIME_0r | CMIC | Captured Free running timer. |
| `0x00000378` | CMIC_BS_CAPTURE_FREE_RUN_TIME_1r | CMIC | Captured Free running timer. |
| `0x0000037c` | CMIC_BS_CAPTURE_SYNT_TIME_0r | CMIC | Captured Syntonized timer. |
| `0x00000380` | CMIC_BS_CAPTURE_SYNT_TIME_1r | CMIC | Captured syntonized timer. |
| `0x00000384` | CMIC_BS_CAPTURE_SYNC_TIME_0r | CMIC | Captured Synchronized timer. |
| `0x00000388` | CMIC_BS_CAPTURE_SYNC_TIME_1r | CMIC | Captured synchronized timer. |
| `0x00000390` | CMIC_SER_MEM_DATAr | CMIC | Parity storage data. |
| `0x00000394` | CMIC_SER_RANGE0_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x00000398` | CMIC_SER_RANGE1_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x0000039c` | CMIC_SER_RANGE2_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003a0` | CMIC_SER_RANGE3_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003a4` | CMIC_SER_RANGE4_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003a8` | CMIC_SER_RANGE5_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003ac` | CMIC_SER_RANGE6_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003b0` | CMIC_SER_RANGE7_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003b4` | CMIC_SER_RANGE8_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003b8` | CMIC_SER_RANGE9_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003bc` | CMIC_SER_RANGE10_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003c0` | CMIC_SER_RANGE11_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003c4` | CMIC_SER_RANGE12_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003c8` | CMIC_SER_RANGE13_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003cc` | CMIC_SER_RANGE14_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x000003d0` | CMIC_SER_RANGE15_DATAENTRY_LENr | CMIC | DATA ENTRY LENGTH. |
| `0x00000400` | CMIC_LEDCLK_PARAMSr | CMIC | This is the register to configure led clock speed. |
| `0x00000410` | CMIC_SW_PIO_ACK_DATA_BEAT_COUNTr | CMIC | Debug register that provides the number of data |
| `0x00000420` | CMIC_TABLE_DMA_PCIMEM_START_ADDRr | CMIC | Table DMA PCI Memory Start Address Register |
| `0x00000424` | CMIC_TABLE_DMA_SBUS_START_ADDRr | CMIC | Table DMA S-bus Start Address Register |
| `0x00000428` | CMIC_TABLE_DMA_ENTRY_COUNTr | CMIC | Table DMA Entry Count Register |
| `0x0000042c` | CMIC_TABLE_DMA_CFGr | CMIC | Table DMA Config Register |
| `0x00000434` | CMIC_TABLE_DMA_CUR_ENTRY_SBUS_ADDRr | CMIC | Table DMA Current Entry S-bus Address Register |
| `0x00000440` | CMIC_SLAM_DMA_PCIMEM_START_ADDRr | CMIC | Slam DMA PCI Memory Start Address Register |
| `0x00000444` | CMIC_SLAM_DMA_SBUS_START_ADDRr | CMIC | Slam DMA S-bus Start Address Register |
| `0x00000448` | CMIC_SLAM_DMA_ENTRY_COUNTr | CMIC | Slam DMA Entry Count Register |
| `0x0000044c` | CMIC_SLAM_DMA_CFGr | CMIC | Slam DMA Config Register |
| `0x00000454` | CMIC_SLAM_DMA_CUR_ENTRY_SBUS_ADDRr | CMIC | Slam DMA Current Entry S-bus Address Register |
| `0x00000460` | CMIC_STAT_DMA_ING_STATS_CFGr | CMIC | Stats DMA Ingress stats config register |
| `0x00000464` | CMIC_STAT_DMA_EGR_STATS_CFGr | CMIC | Stats DMA Egress stats config register |
| `0x00000468` | CMIC_STAT_DMA_MAC_STATS_CFGr | CMIC | Stats DMA MAC stats config register |
| `0x0000046c` | CMIC_STAT_DMA_PORT_TYPE_MAPr | CMIC | Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port |
| `0x00000470` | CMIC_STAT_DMA_SBUS_START_ADDRESSr | CMIC | SBus Start Address for BigMAC and UniMAC counters. |
| `0x00000474` | CMIC_MIIM_BUS_MAP_9_0r | CMIC | MIIM BUS MAP FOR Port 0 to Port 9 |
| `0x00000478` | CMIC_MIIM_BUS_MAP_19_10r | CMIC | MIIM BUS MAP FOR Port 10 to Port 19 |
| `0x0000047c` | CMIC_MIIM_BUS_MAP_29_20r | CMIC | MIIM BUS MAP FOR Port 10 to Port 19 |
| `0x00000480` | CMIC_MIIM_BUS_MAP_39_30r | CMIC | MIIM BUS MAP FOR Port 30 to Port 39 |
| `0x00000484` | CMIC_MIIM_BUS_MAP_49_40r | CMIC | MIIM BUS MAP FOR Port 40 to Port 49 |
| `0x00000488` | CMIC_MIIM_BUS_MAP_59_50r | CMIC | MIIM BUS MAP FOR Port 50 to Port 59 |
| `0x0000048c` | CMIC_MIIM_BUS_MAP_69_60r | CMIC | MIIM BUS MAP FOR Port 50 to Port 59 |
| `0x00000490` | CMIC_MIIM_BUS_MAP_79_70r | CMIC | MIIM BUS MAP FOR Port 50 to Port 59 |
| `0x000004a0` | CMIC_MIIM_ADDRESSr | CMIC | Supplies the register address of MIIM reads and writes. |
| `0x000004a4` | CMIC_MIIM_PROTOCOL_MAPr | CMIC | Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45 |
| `0x000004ac` | CMIC_MIIM_INT_SEL_MAPr | CMIC | Port bitmap specifying whether scan should be done |
| `0x000004c0` | CMIC_MIIM_EXT_PHY_ADDR_MAP_3_0r | CMIC | MIIM Phy Address map, Port 3:0 |
| `0x000004c4` | CMIC_MIIM_EXT_PHY_ADDR_MAP_7_4r | CMIC | MIIM Phy Address map, Port 7:4 |
| `0x000004c8` | CMIC_MIIM_EXT_PHY_ADDR_MAP_11_8r | CMIC | MIIM Phy Address map, Port 11:8 |
| `0x000004cc` | CMIC_MIIM_EXT_PHY_ADDR_MAP_15_12r | CMIC | MIIM Phy Address map, Port 15:12 |
| `0x000004d0` | CMIC_MIIM_EXT_PHY_ADDR_MAP_19_16r | CMIC | MIIM Phy Address map, Port 19:16 |
| `0x000004d4` | CMIC_MIIM_EXT_PHY_ADDR_MAP_23_20r | CMIC | MIIM Phy Address map, Port 23:20 |
| `0x000004d8` | CMIC_MIIM_EXT_PHY_ADDR_MAP_27_24r | CMIC | MIIM Phy Address map, Port 27:24 |
| `0x000004dc` | CMIC_MIIM_EXT_PHY_ADDR_MAP_31_28r | CMIC | MIIM Phy Address map, Port 31:28 |
| `0x000004e0` | CMIC_MIIM_EXT_PHY_ADDR_MAP_35_32r | CMIC | MIIM Phy Address map, Port 35:32 |
| `0x000004e4` | CMIC_MIIM_EXT_PHY_ADDR_MAP_39_36r | CMIC | MIIM Phy Address map, Port 39:26 |
| `0x000004e8` | CMIC_MIIM_EXT_PHY_ADDR_MAP_43_40r | CMIC | MIIM Phy Address map, Port 43:40 |
| `0x000004ec` | CMIC_MIIM_EXT_PHY_ADDR_MAP_47_44r | CMIC | MIIM Phy Address map, Port 47:44 |
| `0x000004f0` | CMIC_MIIM_EXT_PHY_ADDR_MAP_51_48r | CMIC | MIIM Phy Address map, Port 51:48 |
| `0x000004f4` | CMIC_MIIM_EXT_PHY_ADDR_MAP_55_52r | CMIC | MIIM Phy Address map, Port 55:52 |
| `0x000004f8` | CMIC_MIIM_EXT_PHY_ADDR_MAP_59_56r | CMIC | MIIM Phy Address map, Port 59:56 |
| `0x000004fc` | CMIC_MIIM_EXT_PHY_ADDR_MAP_63_60r | CMIC | MIIM Phy Address map, Port 63:60 |
| `0x00000500` | CMIC_XGXS_MDIO_CONFIGr | CMIC |  |
| `0x00000500` | CMIC_XGXS_MDIO_CONFIG_0r | CMIC | CMIC XGXS MDIO Config 0 register |
| `0x00000504` | CMIC_XGXS_MDIO_CONFIG_1r | CMIC | CMIC XGXS MDIO Config 1 register |
| `0x00000508` | CMIC_XGXS_MDIO_CONFIG_2r | CMIC | CMIC XGXS MDIO Config 2 register |
| `0x0000050c` | CMIC_XGXS_MDIO_CONFIG_3r | CMIC | CMIC XGXS MDIO Config 3 register |
| `0x00000510` | CMIC_XGXS_MDIO_CONFIG_4r | CMIC | CMIC XGXS MDIO Config 4 register |
| `0x00000514` | CMIC_XGXS_MDIO_CONFIG_5r | CMIC | CMIC XGXS MDIO Config 5 register |
| `0x00000518` | CMIC_XGXS_MDIO_CONFIG_6r | CMIC | CMIC XGXS MDIO Config 6 register |
| `0x0000051c` | CMIC_XGXS_MDIO_CONFIG_7r | CMIC | CMIC XGXS MDIO Config 7 register |
| `0x00000520` | CMIC_XGXS_MDIO_CONFIG_8r | CMIC | CMIC XGXS MDIO Config 8 register |
| `0x00000524` | CMIC_XGXS_MDIO_CONFIG_9r | CMIC | CMIC XGXS MDIO Config 9 register |
| `0x00000528` | CMIC_XGXS_MDIO_CONFIG_10r | CMIC | CMIC XGXS MDIO Config 10 register |
| `0x0000052c` | CMIC_XGXS_MDIO_CONFIG_11r | CMIC | CMIC XGXS MDIO Config 11 register |
| `0x00000530` | CMIC_XGXS_MDIO_CONFIG_12r | CMIC | CMIC XGXS MDIO Config 12 register |
| `0x00000534` | CMIC_XGXS_MDIO_CONFIG_13r | CMIC | CMIC XGXS MDIO Config 13 register |
| `0x00000538` | CMIC_XGXS_MDIO_CONFIG_14r | CMIC | CMIC XGXS MDIO Config 14 register |
| `0x0000053c` | CMIC_XGXS_MDIO_CONFIG_15r | CMIC | CMIC XGXS MDIO Config 3 register |
| `0x00000540` | CMIC_XGXS_MDIO_CONFIG_16r | CMIC | CMIC XGXS MDIO Config 16 register |
| `0x00000544` | CMIC_XGXS_MDIO_CONFIG_17r | CMIC | CMIC XGXS MDIO Config 1 register |
| `0x00000548` | CMIC_XGXS_MDIO_CONFIG_18r | CMIC | CMIC XGXS MDIO Config 18 register |
| `0x0000054c` | CMIC_XGXS_MDIO_CONFIG_19r | CMIC | CMIC XGXS MDIO Config 3 register |
| `0x00000550` | CMIC_XGXS_MDIO_CONFIG_20r | CMIC | CMIC XGXS MDIO Config 20 register |
| `0x00000554` | CMIC_XGXS_MDIO_CONFIG_21r | CMIC | CMIC XGXS MDIO Config 21 register |
| `0x00000558` | CMIC_XGXS_MDIO_CONFIG_22r | CMIC | CMIC XGXS MDIO Config 22 register |
| `0x0000055c` | CMIC_XGXS_MDIO_CONFIG_23r | CMIC | CMIC XGXS MDIO Config 23 register |
| `0x00000560` | CMIC_XGXS_MDIO_CONFIG_24r | CMIC | CMIC XGXS MDIO Config 24 register |
| `0x0000057c` | CMIC_SOFT_RESET_REG_2r | CMIC | CMIC Soft Reset register 2 |
| `0x00000580` | CMIC_SOFT_RESET_REGr | CMIC | CMIC Soft Reset register |
| `0x00000584` | CMIC_XGXS0_PLL_CONTROL_1r | CMIC | CMIC XGXS PLL 0 Control register 1 |
| `0x00000588` | CMIC_XGXS0_PLL_CONTROL_2r | CMIC | CMIC XGXS 0 PLL Control register 2 |
| `0x0000058c` | CMIC_XGXS0_PLL_CONTROL_3r | CMIC | CMIC XGXS PLL 0 Control register 3 |
| `0x00000590` | CMIC_XGXS0_PLL_CONTROL_4r | CMIC | CMIC XGXS 0 PLL Control register 4 |
| `0x00000594` | CMIC_XGXS0_PLL_STATUSr | CMIC | CMIC XGXS 0 PLL Status |
| `0x00000598` | CMIC_XGXS1_PLL_CONTROL_1r | CMIC | CMIC XGXS PLL 1 Control register 1 |
| `0x0000059c` | CMIC_XGXS1_PLL_CONTROL_2r | CMIC | CMIC XGXS PLL 1 Control register 2 |
| `0x000005a0` | CMIC_XGXS1_PLL_CONTROL_3r | CMIC | CMIC XGXS PLL 1 Control register 3 |
| `0x000005a4` | CMIC_XGXS1_PLL_CONTROL_4r | CMIC | CMIC XGXS PLL 1 Control register 4 |
| `0x000005a8` | CMIC_XGXS1_PLL_STATUSr | CMIC | CMIC XGXS 1 PLL Status |
| `0x000005ac` | CMIC_XGXS2_PLL_CONTROL_1r | CMIC | CMIC XGXS PLL 1 Control register 1 |
| `0x000005b0` | CMIC_XGXS2_PLL_CONTROL_2r | CMIC | CMIC XGXS PLL 1 Control register 2 |
| `0x000005b4` | CMIC_XGXS2_PLL_CONTROL_3r | CMIC | CMIC XGXS PLL 2 Control register 3 |
| `0x000005b8` | CMIC_XGXS2_PLL_CONTROL_4r | CMIC | CMIC XGXS PLL 2 Control register 4 |
| `0x000005bc` | CMIC_XGXS2_PLL_STATUSr | CMIC | CMIC XGXS 2 PLL Status |
| `0x000005c0` | CMIC_STAT_DMA_PORTNUM_MAP_3_0r | CMIC | Stats DMA port <-> port-number map, ports 3_0 |
| `0x000005c4` | CMIC_STAT_DMA_PORTNUM_MAP_7_4r | CMIC | Stats DMA port <-> port-number map, ports 7_4 |
| `0x000005c8` | CMIC_STAT_DMA_PORTNUM_MAP_11_8r | CMIC | Stats DMA port <-> port-number map, ports 11_8 |
| `0x000005cc` | CMIC_STAT_DMA_PORTNUM_MAP_15_12r | CMIC | Stats DMA port <-> port-number map, ports 15_12 |
| `0x000005d0` | CMIC_STAT_DMA_PORTNUM_MAP_19_16r | CMIC | Stats DMA port <-> port-number map, ports 19_16 |
| `0x000005d4` | CMIC_STAT_DMA_PORTNUM_MAP_23_20r | CMIC | Stats DMA port <-> port-number map, ports 23_20 |
| `0x000005d8` | CMIC_STAT_DMA_PORTNUM_MAP_27_24r | CMIC | Stats DMA port <-> port-number map, ports 27_24 |
| `0x000005dc` | CMIC_STAT_DMA_PORTNUM_MAP_31_28r | CMIC | Stats DMA port <-> port-number map, ports 31_28 |
| `0x000005e0` | CMIC_STAT_DMA_PORTNUM_MAP_35_32r | CMIC | Stats DMA port <-> port-number map, ports 35_32 |
| `0x000005e4` | CMIC_STAT_DMA_PORTNUM_MAP_39_36r | CMIC | Stats DMA port <-> port-number map, ports 39_36 |
| `0x000005e8` | CMIC_STAT_DMA_PORTNUM_MAP_43_40r | CMIC | Stats DMA port <-> port-number map, ports 43_40 |
| `0x000005ec` | CMIC_STAT_DMA_PORTNUM_MAP_47_44r | CMIC | Stats DMA port <-> port-number map, ports 47_44 |
| `0x000005f0` | CMIC_STAT_DMA_PORTNUM_MAP_51_48r | CMIC | Stats DMA port <-> port-number map, ports 51_48 |
| `0x000005f4` | CMIC_STAT_DMA_PORTNUM_MAP_55_52r | CMIC | Stats DMA port <-> port-number map, ports 55_52 |
| `0x000005f8` | CMIC_STAT_DMA_PORTNUM_MAP_59_56r | CMIC | Stats DMA port <-> port-number map, ports 59_56 |
| `0x000005fc` | CMIC_STAT_DMA_PORTNUM_MAP_63_60r | CMIC | Stats DMA port <-> port-number map, ports 63_60 |
| `0x00000600` | CMIC_PKT_PRI_MAP_TABLEr | CMIC | 802.1p PRI, Traffic Class and CPU Queue ID Map Table (addresses 0x0600 - 0x06fc |
| `0x00000700` | CMIC_LINK_STAT_HIr | CMIC | Link Status Register, upper 32-bits |
| `0x00000704` | CMIC_SCAN_PORTS_HIr | CMIC | Scan Ports Register, upper 32 bits |
| `0x00000708` | CMIC_MIIM_PROTOCOL_MAP_HIr | CMIC | Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45 |
| `0x00000710` | CMIC_MIIM_INT_SEL_MAP_HIr | CMIC | Port bitmap specifying whether scan should be done |
| `0x00000714` | CMIC_PKT_CTRLr | CMIC | CMIC Remote packet Control Register |
| `0x00000718` | CMIC_PKT_LMAC0_HIr | CMIC | CMIC Local MAC 0 Register Hi |
| `0x0000071c` | CMIC_PKT_LMAC0_LOr | CMIC | CMIC Local MAC 0 Register Lo |
| `0x00000720` | CMIC_PKT_LMAC1_HIr | CMIC | CMIC Local MAC 0 Register Hi |
| `0x00000724` | CMIC_PKT_LMAC1_LOr | CMIC | CMIC Local MAC 0 Register Lo |
| `0x00000728` | CMIC_PKT_VLANr | CMIC | CMIC Packet TPID and VLAN Tag |
| `0x0000072c` | CMIC_PKT_ETHER_SIGr | CMIC | CMIC Packet Ethertype and Signature |
| `0x00000730` | CMIC_PKT_COSr | CMIC | CMIC Packet COS Bitmap |
| `0x00000734` | CMIC_PKT_PORTSr | CMIC | CMIC Packet Port Bitmap Low 32 bits |
| `0x00000738` | CMIC_PKT_PORTS_HIr | CMIC | CMIC Packet Port Bitmap High 32 bits |
| `0x0000073c` | CMIC_PKT_RMACr | CMIC | Lower 32 bits of the destination MAC address for all packets that the CMIC generates excep |
| `0x00000740` | CMIC_PKT_RMAC_HIr | CMIC | Higher 16 bits of the destination MAC address for all packets that the CMIC generates exce |
| `0x00000744` | CMIC_PKT_RMH0r | CMIC | First DWord of the Module Header on an outpoing CMIC packet. |
| `0x00000748` | CMIC_PKT_RMH1r | CMIC | Second DWord of the Module Header on an outpoing CMIC packet. |
| `0x0000074c` | CMIC_PKT_RMH2r | CMIC | Third DWord of the Module Header on an outpoing CMIC packet. |
| `0x00000750` | CMIC_PKT_REASONr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x00000754` | CMIC_PKT_REASON_HIr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x00000758` | CMIC_PKT_REASON_DIRECTr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x0000075c` | CMIC_PKT_REASON_DIRECT_HIr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x00000760` | CMIC_PKT_REASON_MINIr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x00000764` | CMIC_PKT_REASON_MINI_HIr | CMIC | A bitmap of reason codes (sometimes called CPU opcodes) that cause |
| `0x00000768` | CMIC_PKT_PORTS_HI_2r | CMIC | CMIC Packet Port Bitmap MSB 32 bits |
| `0x00000780` | CMIC_STAT_DMA_PORTS_HIr | CMIC | Stat Counter Port Bit Map Register, upper 32 bits |
| `0x00000784` | CMIC_STAT_DMA_PORT_TYPE_MAP_HIr | CMIC | Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port |
| `0x00000788` | CMIC_PKT_RMH3r | CMIC | Fourth DWord of the Module Header on an outpoing CMIC packet. |
| `0x00000800` | CMIC_SCHAN_MESSAGE_EXTr | CMIC | S-bus PIO Message Register Set (extended) |
| `0x00000860` | CMIC_MISC_CONTROLr | CMIC | CMIC Miscel Control Register |
| `0x00000864` | CMIC_MIIM_AUTO_SCAN_ADDRESSr | CMIC | CMIC_MIIM_AUTO_SCAN_ADDRESS |
| `0x00000868` | CMIC_MISC_STATUSr | CMIC | Miscel Status  Register |
| `0x00000874` | CMIC_CHIP_PARITY_INTR_STATUSr | CMIC | CMIC_PARITY_INTR_STATUS |
| `0x00000878` | CMIC_CHIP_PARITY_INTR_ENABLEr | CMIC | CMIC_CHIP_PARITY_INTR_ENABLE |
| `0x00000900` | CMIC_SCHAN_RCPU_RPIO_MESSAGEr | CMIC | S-bus Remote PIO Message Register Set |
| `0x00000958` | CMIC_LEDUP0_PORT_ORDER_REMAP_60_63r | CMIC | LEDUP SCan Data Remap register for ports 60-63 |
| `0x0000095c` | CMIC_THERMAL_MON_RESULT_2r | CMIC | Temperature Monitor Result Register 2 |
| `0x00000960` | CMIC_THERMAL_MON_RESULT_3r | CMIC | Temperature Monitor Result Register 3 |
| `0x00000964` | CMIC_THERMAL_MON_RESULT_4r | CMIC | Temperature Monitor Result Register 4 |
| `0x00000968` | CMIC_THERMAL_MON_RESULT_5r | CMIC | Temperature Monitor Result Register 5 |
| `0x0000096c` | CMIC_STAT_DMA_BLKNUM_MAP_69_65r | CMIC | Stats DMA port <-> block-number map, ports 69 to 65 |
| `0x00000970` | CMIC_STAT_DMA_BLKNUM_MAP_74_70r | CMIC | Stats DMA port <-> block-number map, ports 74 to 70 |
| `0x00000974` | CMIC_STAT_DMA_BLKNUM_MAP_79_75r | CMIC | Stats DMA port <-> block-number map, ports 79 to 75 |
| `0x00000978` | CMIC_STAT_DMA_BLKNUM_MAP_84_80r | CMIC | Stats DMA port <-> block-number map, ports 84 to 80 |
| `0x0000097c` | CMIC_STAT_DMA_BLKNUM_MAP_89_85r | CMIC | Stats DMA port <-> block-number map, ports 89 to 85 |
| `0x00000980` | CMIC_STAT_DMA_BLKNUM_MAP_94_90r | CMIC | Stats DMA port <-> block-number map, ports 94 to 90 |
| `0x00000984` | CMIC_STAT_DMA_BLKNUM_MAP_95r | CMIC | Stats DMA port <-> block-number map, ports  95 |
| `0x00000988` | CMIC_MIIM_EXT_PHY_ADDR_MAP_67_64r | CMIC | MIIM Phy Address map, Port 67:64 |
| `0x0000098c` | CMIC_MIIM_EXT_PHY_ADDR_MAP_71_68r | CMIC | MIIM Phy Address map, Port 71:68 |
| `0x00000990` | CMIC_MIIM_EXT_PHY_ADDR_MAP_75_72r | CMIC | MIIM Phy Address map, Port 75:72 |
| `0x00000994` | CMIC_MIIM_EXT_PHY_ADDR_MAP_79_76r | CMIC | MIIM Phy Address map, Port 79:76 |
| `0x00000998` | CMIC_STAT_DMA_PORTS_HI_2r | CMIC | Stat Counter Port Bit Map Register, upper 32 bits |
| `0x0000099c` | CMIC_LINK_STAT_HI_2r | CMIC | Link Status Register, upper 95:64 bits |
| `0x000009a0` | CMIC_SCAN_PORTS_HI_2r | CMIC | Scan Ports Register, upper 95:64 bits |
| `0x000009a4` | CMIC_MIIM_PROTOCOL_MAP_HI_2r | CMIC | Port bitmap of MIIM protocol: 0=clause 22, 1=clause 45 |
| `0x000009a8` | CMIC_STAT_DMA_PORTNUM_MAP_67_64r | CMIC | Stats DMA port <-> port-number map, ports 67_64 |
| `0x000009ac` | CMIC_STAT_DMA_PORTNUM_MAP_71_68r | CMIC | Stats DMA port <-> port-number map, ports 71_68 |
| `0x000009b0` | CMIC_STAT_DMA_PORTNUM_MAP_75_72r | CMIC | Stats DMA port <-> port-number map, ports 75_72 |
| `0x000009b4` | CMIC_STAT_DMA_PORTNUM_MAP_79_76r | CMIC | Stats DMA port <-> port-number map, ports 79_76 |
| `0x000009b8` | CMIC_STAT_DMA_PORTNUM_MAP_83_80r | CMIC | Stats DMA port <-> port-number map, ports 83_80 |
| `0x000009bc` | CMIC_STAT_DMA_PORTNUM_MAP_87_84r | CMIC | Stats DMA port <-> port-number map, ports 87_84 |
| `0x000009c0` | CMIC_STAT_DMA_PORTNUM_MAP_91_88r | CMIC | Stats DMA port <-> port-number map, ports 91_88 |
| `0x000009c4` | CMIC_STAT_DMA_PORTNUM_MAP_95_92r | CMIC | Stats DMA port <-> port-number map, ports 95_92 |
| `0x000009c8` | CMIC_STAT_DMA_PORT_TYPE_MAP_HI_2r | CMIC | Port type bitmap for Stat DMA: 0=Gig port, 1=Higig port |
| `0x000009cc` | CMIC_MIIM_INT_SEL_MAP_HI_2r | CMIC | Port bitmap specifying whether scan should be done |
| `0x000009d0` | CMIC_MIIM_EXT_PHY_ADDR_MAP_83_80r | CMIC | MIIM Phy Address map, Port 83:80 |
| `0x000009d4` | CMIC_MIIM_EXT_PHY_ADDR_MAP_87_84r | CMIC | MIIM Phy Address map, Port 87:84 |
| `0x000009d8` | CMIC_MIIM_EXT_PHY_ADDR_MAP_91_88r | CMIC | MIIM Phy Address map, Port 91:88 |
| `0x000009dc` | CMIC_LEDUP0_PORT_ORDER_REMAP_44_47r | CMIC | LEDUP SCan Data Remap register for ports 44-47 |
| `0x000009e0` | CMIC_LEDUP0_PORT_ORDER_REMAP_48_51r | CMIC | LEDUP SCan Data Remap register for ports 51-48 |
| `0x000009e4` | CMIC_LEDUP0_PORT_ORDER_REMAP_52_55r | CMIC | LEDUP SCan Data Remap register for ports 52-55 |
| `0x000009e8` | CMIC_LEDUP0_PORT_ORDER_REMAP_56_59r | CMIC | LEDUP SCan Data Remap register for ports 56-59 |
| `0x000009ec` | CMIC_MIIM_EXT_PHY_ADDR_MAP_95_92r | CMIC | MIIM Phy Address map, Port 95:92 |
| `0x00000d00` | CMIC_LEDUP0_PORT_ORDER_REMAPr | CMIC |  |
| `0x00000d00` | CMIC_LEDUP0_PORT_ORDER_REMAP_0_3r | CMIC | LEDUP SCan Data Remap register for ports 0-3 |
| `0x00000d04` | CMIC_LEDUP0_PORT_ORDER_REMAP_4_7r | CMIC | LEDUP SCan Data Remap register for ports 4-7 |
| `0x00000d08` | CMIC_LEDUP0_PORT_ORDER_REMAP_8_11r | CMIC | LEDUP SCan Data Remap register for ports 8-11 |
| `0x00000d0c` | CMIC_LEDUP0_PORT_ORDER_REMAP_12_15r | CMIC | LEDUP SCan Data Remap register for ports 12_15 |
| `0x00000d10` | CMIC_LEDUP0_PORT_ORDER_REMAP_16_19r | CMIC | LEDUP SCan Data Remap register for ports 16_19 |
| `0x00000d14` | CMIC_LEDUP0_PORT_ORDER_REMAP_20_23r | CMIC | LEDUP SCan Data Remap register for ports 20-23 |
| `0x00000d18` | CMIC_LEDUP0_PORT_ORDER_REMAP_24_27r | CMIC | LEDUP SCan Data Remap register for ports 24_27 |
| `0x00000d1c` | CMIC_LEDUP0_PORT_ORDER_REMAP_28_31r | CMIC | LEDUP SCan Data Remap register for ports 28-31 |
| `0x00000d20` | CMIC_LEDUP0_PORT_ORDER_REMAP_32_35r | CMIC | LEDUP SCan Data Remap register for ports 32-35 |
| `0x00000d24` | CMIC_LEDUP0_PORT_ORDER_REMAP_36_39r | CMIC | LEDUP SCan Data Remap register for ports 36-39 |
| `0x00000d28` | CMIC_LEDUP0_PORT_ORDER_REMAP_40_43r | CMIC | LEDUP SCan Data Remap register for ports 40-43 |
| `0x00000d2c` | CMIC_FIFO_CH0_RD_DMA_CFGr | CMIC | FIFO Read DMA Channel 0 Config |
| `0x00000d30` | CMIC_FIFO_CH1_RD_DMA_CFGr | CMIC | FIFO Read DMA Channel 1 Config |
| `0x00000d34` | CMIC_FIFO_CH2_RD_DMA_CFGr | CMIC | FIFO Read DMA Channel 2 Config |
| `0x00000d38` | CMIC_FIFO_CH3_RD_DMA_CFGr | CMIC | FIFO Read DMA Channel 3 Config |
| `0x00000d3c` | CMIC_FIFO_CH0_RD_DMA_SBUS_START_ADDRESSr | CMIC | FIFO Read DMA Channel 0 SBus Address |
| `0x00000d40` | CMIC_FIFO_CH1_RD_DMA_SBUS_START_ADDRESSr | CMIC | FIFO Read DMA Channel 1 SBus Address |
| `0x00000d44` | CMIC_FIFO_CH2_RD_DMA_SBUS_START_ADDRESSr | CMIC | FIFO Read DMA Channel 2 SBus Address |
| `0x00000d48` | CMIC_FIFO_CH3_RD_DMA_SBUS_START_ADDRESSr | CMIC | FIFO Read DMA Channel 3 SBus Address |
| `0x00000d4c` | CMIC_FIFO_CH0_RD_DMA_HOSTMEM_START_ADDRESSr | CMIC | FIFO Read DMA Channel 0 SBus Address |
| `0x00000d50` | CMIC_FIFO_CH1_RD_DMA_HOSTMEM_START_ADDRESSr | CMIC | FIFO Read DMA Channel 1 SBus Address |
| `0x00000d54` | CMIC_FIFO_CH2_RD_DMA_HOSTMEM_START_ADDRESSr | CMIC | FIFO Read DMA Channel 2 SBus Address |
| `0x00000d58` | CMIC_FIFO_CH3_RD_DMA_HOSTMEM_START_ADDRESSr | CMIC | FIFO Read DMA Channel 3 SBus Address |
| `0x00000d5c` | CMIC_FIFO_CH0_RD_DMA_HOSTMEM_READ_PTRr | CMIC | FIFO Read DMA Channel 0 Host Memory Read Pointer |
| `0x00000d60` | CMIC_FIFO_CH0_RD_DMA_HOSTMEM_WRITE_PTRr | CMIC | FIFO Read DMA Channel 0 Host Memory Write Pointer |
| `0x00000d64` | CMIC_FIFO_CH1_RD_DMA_HOSTMEM_READ_PTRr | CMIC | FIFO Read DMA Channel 1 Host Memory Read Pointer |
| `0x00000d68` | CMIC_FIFO_CH1_RD_DMA_HOSTMEM_WRITE_PTRr | CMIC | FIFO Read DMA Channel 1 Host Memory Write Pointer |
| `0x00000d6c` | CMIC_FIFO_CH2_RD_DMA_HOSTMEM_READ_PTRr | CMIC | FIFO Read DMA Channel 2 Host Memory Read Pointer |
| `0x00000d70` | CMIC_FIFO_CH2_RD_DMA_HOSTMEM_WRITE_PTRr | CMIC | FIFO Read DMA Channel 2 Host Memory Write Pointer |
| `0x00000d74` | CMIC_FIFO_CH3_RD_DMA_HOSTMEM_READ_PTRr | CMIC | FIFO Read DMA Channel 3 Host Memory Read Pointer |
| `0x00000d78` | CMIC_FIFO_CH3_RD_DMA_HOSTMEM_WRITE_PTRr | CMIC | FIFO Read DMA Channel 3 Host Memory Write Pointer |
| `0x00000d7c` | CMIC_FIFO_RD_DMA_DEBUGr | CMIC | FIFO Read DMA Debug |
| `0x00000d80` | CMIC_FIFO_CH0_RD_DMA_HOSTMEM_THRESHOLDr | CMIC | FIFO Read DMA Channel 0 Threshold |
| `0x00000d84` | CMIC_FIFO_CH1_RD_DMA_HOSTMEM_THRESHOLDr | CMIC | FIFO Read DMA Channel 1 Threshold |
| `0x00000d88` | CMIC_FIFO_CH2_RD_DMA_HOSTMEM_THRESHOLDr | CMIC | FIFO Read DMA Channel 2 Threshold |
| `0x00000d8c` | CMIC_FIFO_CH3_RD_DMA_HOSTMEM_THRESHOLDr | CMIC | FIFO Read DMA Channel 3 Threshold |
| `0x00000d90` | CMIC_COS_CTRL_RX_0r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000d94` | CMIC_COS_CTRL_RX_1r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000d98` | CMIC_COS_CTRL_RX_2r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000d9c` | CMIC_COS_CTRL_RX_3r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000da0` | CMIC_COS_CTRL_RX_4r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000da4` | CMIC_COS_CTRL_RX_5r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000da8` | CMIC_COS_CTRL_RX_6r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000dac` | CMIC_COS_CTRL_RX_7r | CMIC | When COS_RX_EN of CMIC_CONFIG is set, this register |
| `0x00000db8` | CMIC_PKT_COS_HIr | CMIC | CMIC Packet COS values of aceptable CMIC packets(upper 32 CoS values). |
| `0x00000dbc` | CMIC_CORE_PLL0_CTRL_STAT_0r | CMIC |  |
| `0x00000dc0` | CMIC_CORE_PLL0_CTRL_STAT_1r | CMIC |  |
| `0x00000dc4` | CMIC_CORE_PLL0_CTRL_STAT_2r | CMIC |  |
| `0x00000dc8` | CMIC_CORE_PLL0_CTRL_STAT_3r | CMIC |  |
| `0x00000dcc` | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_0r | CMIC | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_0 |
| `0x00000dd0` | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_1r | CMIC | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_1 |
| `0x00000dd4` | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_2r | CMIC | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_2 |
| `0x00000dd8` | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_3r | CMIC | CMIC_CORE_PLL2_CTRL_STATUS_REGISTER_3 |
| `0x00000ddc` | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_0r | CMIC | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_0 |
| `0x00000de0` | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_1r | CMIC | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_1 |
| `0x00000de4` | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_2r | CMIC | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_2 |
| `0x00000de8` | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_3r | CMIC | CMIC_CORE_PLL1_CTRL_STATUS_REGISTER_3 |
| `0x00000dec` | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_0r | CMIC | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_0 |
| `0x00000df0` | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_1r | CMIC | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_1 |
| `0x00000df4` | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_2r | CMIC | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_2 |
| `0x00000df8` | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_3r | CMIC | CMIC_CORE_PLL3_CTRL_STATUS_REGISTER_3 |
| `0x00000dfc` | CMIC_EB3_VLI_CONFIG_REGISTERr | CMIC | CMIC_EB3_CONFIG_REGISTER |
| `0x00000e00` | CMIC_LEDUP1_PORT_ORDER_REMAPr | CMIC |  |
| `0x00000e00` | CMIC_LEDUP1_PORT_ORDER_REMAP_0_3r | CMIC | LEDUP SCan Data Remap register for ports 0-3 |
| `0x00000e04` | CMIC_LEDUP1_PORT_ORDER_REMAP_4_7r | CMIC | LEDUP SCan Data Remap register for ports 4-7 |
| `0x00000e08` | CMIC_LEDUP1_PORT_ORDER_REMAP_8_11r | CMIC | LEDUP SCan Data Remap register for ports 8-11 |
| `0x00000e0c` | CMIC_LEDUP1_PORT_ORDER_REMAP_12_15r | CMIC | LEDUP SCan Data Remap register for ports 12_15 |
| `0x00000e10` | CMIC_LEDUP1_PORT_ORDER_REMAP_16_19r | CMIC | LEDUP SCan Data Remap register for ports 16_19 |
| `0x00000e14` | CMIC_LEDUP1_PORT_ORDER_REMAP_20_23r | CMIC | LEDUP SCan Data Remap register for ports 20-23 |
| `0x00000e18` | CMIC_LEDUP1_PORT_ORDER_REMAP_24_27r | CMIC | LEDUP SCan Data Remap register for ports 24_27 |
| `0x00000e1c` | CMIC_LEDUP1_PORT_ORDER_REMAP_28_31r | CMIC | LEDUP SCan Data Remap register for ports 28-31 |
| `0x00000e20` | CMIC_LEDUP1_PORT_ORDER_REMAP_32_35r | CMIC | LEDUP SCan Data Remap register for ports 32-35 |
| `0x00000e24` | CMIC_LEDUP1_PORT_ORDER_REMAP_36_39r | CMIC | LEDUP SCan Data Remap register for ports 36-39 |
| `0x00000e28` | CMIC_LEDUP1_PORT_ORDER_REMAP_40_43r | CMIC | LEDUP SCan Data Remap register for ports 40-43 |
| `0x00000e2c` | CMIC_LEDUP1_PORT_ORDER_REMAP_44_47r | CMIC | LEDUP SCan Data Remap register for ports 44-47 |
| `0x00000e30` | CMIC_LEDUP1_PORT_ORDER_REMAP_48_51r | CMIC | LEDUP SCan Data Remap register for ports 51-48 |
| `0x00000e34` | CMIC_LEDUP1_PORT_ORDER_REMAP_52_55r | CMIC | LEDUP SCan Data Remap register for ports 52-55 |
| `0x00000e38` | CMIC_LEDUP1_PORT_ORDER_REMAP_56_59r | CMIC | LEDUP SCan Data Remap register for ports 56-59 |
| `0x00000e3c` | CMIC_LEDUP1_PORT_ORDER_REMAP_60_63r | CMIC | LEDUP SCan Data Remap register for ports 60-63 |
| `0x00000e40` | CMIC_THERMAL_MON_RESULT_6r | CMIC | Temperature Monitor Result Register 6 |
| `0x00000e44` | CMIC_THERMAL_MON_RESULT_7r | CMIC | Temperature Monitor Result Register 7 |
| `0x00000e50` | CMIC_XGXS3_PLL_CONTROL_1r | CMIC | CMIC XGXS PLL 3 Control register 1 |
| `0x00000e54` | CMIC_XGXS3_PLL_CONTROL_2r | CMIC | CMIC XGXS PLL 3 Control register 2 |
| `0x00000e58` | CMIC_XGXS3_PLL_CONTROL_3r | CMIC | CMIC XGXS PLL 3 Control register 3 |
| `0x00000e5c` | CMIC_XGXS3_PLL_CONTROL_4r | CMIC | CMIC XGXS PLL 3 Control register 4 |
| `0x00000e60` | CMIC_XGXS3_PLL_STATUSr | CMIC | CMIC XGXS 3 PLL Status |
| `0x00000e64` | CMIC_CORE_PLL0_CTRL_STAT_4r | CMIC |  |
| `0x00001000` | CMIC_LEDUP0_CTRLr | CMIC | LEDUP0 Control |
| `0x00001004` | CMIC_LEDUP0_STATUSr | CMIC | LEDUP0 Status |
| `0x00001008` | CMIC_LEDUP0_SCANCHAIN_ASSEMBLY_ST_ADDRr | CMIC | LEDUP0 scanchain assembly start address |
| `0x00001400` | CMIC_LEDUP0_DATA_RAMr | CMIC | LEDUP0 Data RAM |
| `0x00001800` | CMIC_LEDUP0_PROGRAM_RAMr | CMIC | LEDUP0 Program RAM |
| `0x00002000` | CMIC_LEDUP1_CTRLr | CMIC | LEDUP1 Control |
| `0x00002004` | CMIC_LEDUP1_STATUSr | CMIC | LEDUP1 Status |
| `0x00002008` | CMIC_LEDUP1_SCANCHAIN_ASSEMBLY_ST_ADDRr | CMIC | LEDUP1 scanchain assembly start address |
| `0x00002400` | CMIC_LEDUP1_DATA_RAMr | CMIC | LEDUP1 Data RAM |
| `0x00002800` | CMIC_LEDUP1_PROGRAM_RAMr | CMIC | LEDUP1 Program RAM |
| `0x00180304` | L2_AGE_TIMERr | IPIPE | Age Timer Register |
| `0x00180305` | L2_BULK_CONTROLr | IPIPE | l2 Bluk Control Register |
| `0x00180306` | L2_AGE_DEBUGr | IPIPE | Age Debug Register |
| `0x0018030a` | IARB_LEARN_CONTROLr | IPIPE | Determines how the hit bits are set on a packet learn |
| `0x0018030b` | MOD_FIFO_CNTr | IPIPE | Mod Fifo entry counter |
| `0x0018030d` | LMEP_COMMON_1r | IPIPE | DA_47_16: The common MAC DA upper 32 bits for all LMEP packets.  These represent bits 47:1 |
| `0x0018030e` | LMEP_COMMON_2r | IPIPE | DA_15_3: The common MAC DA lower 13 bits for all LMEP packets.  These represent bits 15:3  |
| `0x0018030f` | OAM_TX_CONTROLr | IPIPE | TX_ENABLE: Enable oam lmep transmission |
| `0x00180310` | OAM_CCM_COUNT_64r | IPIPE | Lmep transmit ccm counts |
| `0x00180311` | OAM_TIMER_CONTROLr | IPIPE | oam timer control register |
| `0x00180312` | ARB_RAM_DBGCTRLr | IPIPE | ARB_RAM_CONTROL |
| `0x00180313` | LMEP_PARITY_CONTROLr | IPIPE | LMEP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x00180314` | LMEP_PARITY_STATUS_INTRr | IPIPE | LMEP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x00180315` | LMEP_PARITY_STATUS_NACKr | IPIPE | LMEP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x00180316` | IARB_PKT_ECC_CONTROLr | IPIPE | IARB_PKT_ECC_CONTROL, FeatureSpecific-Ethernet |
| `0x00180317` | IARB_PKT_ECC_STATUS_INTRr | IPIPE | IARB_PKT_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x00180318` | IARB_HDR_ECC_CONTROLr | IPIPE | IARB_HDR_ECC_CONTROL, FeatureSpecific-Ethernet |
| `0x00180319` | IARB_HDR_ECC_STATUS_INTRr | IPIPE | IARB_HDR_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0018031b` | IARB_LEARN_FIFO_ECC_CONTROLr | IPIPE | IARB_LERAN_FIFO_ECC_CONTROL, FeatureSpecific-Ethernet |
| `0x0018031c` | IARB_PIPE_X_LERAN_FIFO_ECC_STATUS_INTRr | IPIPE | IARB_PIPE_X_LERAN_FIFO_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0018031d` | IARB_PIPE_Y_LERAN_FIFO_ECC_STATUS_INTRr | IPIPE | IARB_PIPE_Y_LERAN_FIFO_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x00180700` | AUX_ARB_CONTROLr | IPIPE | IP auxilary arbiter control register |
| `0x00180701` | AUX_ARB_CONTROL_2r | IPIPE | IP auxilary arbiter control register for FP functions. FeatureSpecific-FP |
| `0x00180702` | ING_HW_RESET_CONTROL_1r | IPIPE | Ingress Pipeline memory hardware initialization register #1 |
| `0x00180703` | ING_HW_RESET_CONTROL_2r | IPIPE | Ingress Pipeline memory hardware initialization register #2 |
| `0x00180707` | L2_AGE_DEBUG_2r | IPIPE | Age Debug Register |
| `0x00180708` | ING_Q_BEGINr | IPIPE | Register starts the IQ Bus which is provided for later ECO reasons, if any. |
| `0x00180709` | IARB_TDM_CONTROLr | IPIPE | determines mapping of gxports onto tdm slots, slots[0-3] 16G, slots[4-7] 12G |
| `0x0018070c` | ARB_EOP_DEBUGr | IPIPE | Forces accesses to stages to be eop resource |
| `0x0018071a` | IARB_SBUS_TIMERr | IPIPE | IARB_SBUS_TIMER |
| `0x00180d1e` | IP0_INTR_STATUSr | IPIPE | IP0 Interrupt Status |
| `0x00180d1f` | IP0_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP0_INTR_STATUS |
| `0x00280700` | EGR_HW_RESET_CONTROL_0r | EPIPE | This register is for controlling the HW Table Initialization Feature of the Egress Pipelin |
| `0x00280701` | EGR_HW_RESET_CONTROL_1r | EPIPE | This register is for controlling the HW Table Initialization Feature of the Egress Pipelin |
| `0x00280702` | EGR_Q_BEGINr | EPIPE | Register starts an EQ Bus which is provided for later ECO reasons, if any. |
| `0x00280703` | EGR_ARB_TIMEOUT_CONTROLr | EPIPE | Egress arbiter s-bus / IPFIX arbitration timeout control register |
| `0x00500000` | R64r | XLPORT | Receive 64 Byte Frame Counter |
| `0x00500001` | R127r | XLPORT | Receive 65 to 127 Byte Frame Counter |
| `0x00500002` | R255r | XLPORT | Receive 128 to 255 Byte Frame Counter |
| `0x00500003` | R511r | XLPORT | Receive 256 to 511 Byte Frame Counter |
| `0x00500004` | R1023r | XLPORT | Receive 512 to 1023 Byte Frame Counter |
| `0x00500005` | R1518r | XLPORT | Receive 1024 to 1518 Byte Frame Counter |
| `0x00500006` | RMGVr | XLPORT | Receive 1519 to 1522 Byte Good VLAN Frame Counter |
| `0x00500007` | R2047r | XLPORT | Receive 1519 to 2047 Byte Frame Counter |
| `0x00500008` | R4095r | XLPORT | Receive 2048 to 4095 Byte Frame Counter |
| `0x00500009` | R9216r | XLPORT | Receive 4096 to 9216 Byte Frame Counter |
| `0x0050000a` | R16383r | XLPORT | Receive 9217 to 16838 Byte Frame Counter |
| `0x0050000b` | RPKTr | XLPORT | Receive frame/packet Counter |
| `0x0050000c` | RUCAr | XLPORT | Receive Unicast Frame Counter |
| `0x0050000d` | RMCAr | XLPORT | Receive Multicast Frame Counter |
| `0x0050000e` | RBCAr | XLPORT | Receive Broadcast Frame Counter |
| `0x0050000f` | RFCSr | XLPORT | Receive FCS Error Frame Counter |
| `0x00500010` | RXCFr | XLPORT | Receive Control Frame Counter |
| `0x00500011` | RXPFr | XLPORT | Receive PAUSE Frame Counter |
| `0x00500012` | RXPPr | XLPORT | Receive PFC (Per-Priority Pause) Frame Counter |
| `0x00500013` | RXUOr | XLPORT | Receive Unsupported Opcode Frame Counter |
| `0x00500014` | RXUDAr | XLPORT | Receive Unsupported DA for PAUSE/PFC Frame Counter |
| `0x00500015` | RXWSAr | XLPORT | Receive Wrong SA Frame Counter |
| `0x00500016` | RALNr | XLPORT | Receive Alignment Error Frame Counter |
| `0x00500017` | RFLRr | XLPORT | Receive Length Out of Range Frame Counter |
| `0x00500018` | RERPKTr | XLPORT | Receive Code Error Frame Counter |
| `0x00500019` | RFCRr | XLPORT | Receive False Carrier Counter |
| `0x0050001a` | ROVRr | XLPORT | Receive Oversized Frame Counter |
| `0x0050001b` | RJBRr | XLPORT | Receive Jabber Frame Counter |
| `0x0050001c` | RMTUEr | XLPORT | Receive MTU Check Error Frame Counter |
| `0x0050001d` | RMCRCr | XLPORT | Matched CRC Frame Counter |
| `0x0050001e` | RPRMr | XLPORT | Receive Promiscuous Frame Counter |
| `0x0050001f` | RVLNr | XLPORT | Receive VLAN Tag Frame Counter |
| `0x00500020` | RDVLNr | XLPORT | Receive Double VLAN Tag Frame Counter |
| `0x00500021` | RTRFUr | XLPORT | Receive Truncated Frame Counter (due to RX FIFO full) |
| `0x00500022` | RPOKr | XLPORT | Receive Good Packet Counter |
| `0x00500023` | RPFCOFF0r | XLPORT | Receive PFC Frame Priority 0 XON to XOFF |
| `0x00500024` | RPFCOFF1r | XLPORT | Receive PFC Frame Priority 1 |
| `0x00500025` | RPFCOFF2r | XLPORT | Receive PFC Frame Priority 2 |
| `0x00500026` | RPFCOFF3r | XLPORT | Receive PFC Frame Priority 3 |
| `0x00500027` | RPFCOFF4r | XLPORT | Receive PFC Frame Priority 4 |
| `0x00500028` | RPFCOFF5r | XLPORT | Receive PFC Frame Priority 5 |
| `0x00500029` | RPFCOFF6r | XLPORT | Receive PFC Frame Priority 6 |
| `0x0050002a` | RPFCOFF7r | XLPORT | Receive PFC Frame Priority 7 |
| `0x0050002b` | RPFC0r | XLPORT | Receive PFC Frame Priority 0 |
| `0x0050002c` | RPFC1r | XLPORT | Receive PFC Frame Priority 1 |
| `0x0050002d` | RPFC2r | XLPORT | Receive PFC Frame Priority 2 |
| `0x0050002e` | RPFC3r | XLPORT | Receive PFC Frame Priority 3 |
| `0x0050002f` | RPFC4r | XLPORT | Receive PFC Frame Priority 4 |
| `0x00500030` | RPFC5r | XLPORT | Receive PFC Frame Priority 5 |
| `0x00500031` | RPFC6r | XLPORT | Receive PFC Frame Priority 6 |
| `0x00500032` | RPFC7r | XLPORT | Receive PFC Frame Priority 7 |
| `0x00500033` | RSCHCRCr | XLPORT | Receive SCH CRC Error |
| `0x00500034` | RBYTr | XLPORT | Receive Byte Counter |
| `0x00500035` | RRPKTr | XLPORT | Receive RUNT Frame Counter |
| `0x00500036` | RUNDr | XLPORT | Receive Undersize Frame Counter |
| `0x00500037` | RFRGr | XLPORT | Receive Fragment Counter |
| `0x00500038` | RRBYTr | XLPORT | Receive Runt Byte Counter |
| `0x00500039` | T64r | XLPORT | Transmit 64 Byte Frame Counter |
| `0x0050003a` | T127r | XLPORT | Transmit 65 to 127 Byte Frame Counter |
| `0x0050003b` | T255r | XLPORT | Transmit 128 to 255 Byte Frame Counter |
| `0x0050003c` | T511r | XLPORT | Transmit 256 to 511 Byte Frame Counter |
| `0x0050003d` | T1023r | XLPORT | Transmit 512 to 1023 Byte Frame Counter |
| `0x0050003e` | T1518r | XLPORT | Transmit 1024 to 1518 Byte Frame Counter |
| `0x0050003f` | TMGVr | XLPORT | Transmit 1519 to 1522 Byte Good VLAN Frame Counter |
| `0x00500040` | T2047r | XLPORT | Transmit 1519 to 2047 Byte Frame Counter |
| `0x00500041` | T4095r | XLPORT | Transmit 2048 to 4095 Byte Frame Counter |
| `0x00500042` | T9216r | XLPORT | Transmit 4096 to 9216 Byte Frame Counter |
| `0x00500043` | T16383r | XLPORT | Transmit 9217 to 16383 Byte Frame Counter |
| `0x00500044` | TPOKr | XLPORT | Transmit Good Packet Counter |
| `0x00500045` | TPKTr | XLPORT | Transmit Packet/Frame Counter |
| `0x00500046` | TUCAr | XLPORT | Transmit Unicast Frame Counter |
| `0x00500047` | TMCAr | XLPORT | Transmit Multicast Frame Counter |
| `0x00500048` | TBCAr | XLPORT | Transmit Broadcast Frame Counter |
| `0x00500049` | TXPFr | XLPORT | Transmit Pause Control Frame Counter |
| `0x0050004a` | TXPPr | XLPORT | Transmit PFC/Per-Priority Pause Control Frame Counter |
| `0x0050004b` | TJBRr | XLPORT | Transmit Jabber Counter |
| `0x0050004c` | TFCSr | XLPORT | Transmit FCS Error Counter |
| `0x0050004d` | TXCFr | XLPORT | Transmit Control Frame Counter |
| `0x0050004e` | TOVRr | XLPORT | Transmit Oversize Packet Counter |
| `0x0050004f` | TDFRr | XLPORT | Transmit Single Deferral Frame Counter |
| `0x00500050` | TEDFr | XLPORT | Transmit Multiple Deferral Frame Counter |
| `0x00500051` | TSCLr | XLPORT | Transmit Single Collision Frame Counter |
| `0x00500052` | TMCLr | XLPORT | Transmit Multiple Collision Frame Counter |
| `0x00500053` | TLCLr | XLPORT | Transmit Late Collision Frame Counter |
| `0x00500054` | TXCLr | XLPORT | Transmit Excessive Collision Frame Counter |
| `0x00500055` | TFRGr | XLPORT | Transmit Fragment Counter |
| `0x00500056` | TERRr | XLPORT | Transmit Error (set by system) Counter |
| `0x00500057` | TVLNr | XLPORT | Transmit VLAN Tag Frame Counter |
| `0x00500058` | TDVLNr | XLPORT | Transmit Double VLAN Tag Frame Counter |
| `0x00500059` | TRPKTr | XLPORT | Transmit RUNT Frame Counter |
| `0x0050005a` | TUFLr | XLPORT | Transmit FIFO Underrun Counter. |
| `0x0050005b` | TPFC0r | XLPORT | Transmit PFC Frame Priority 0 |
| `0x0050005c` | TPFC1r | XLPORT | Transmit PFC Frame Priority 1 |
| `0x0050005d` | TPFC2r | XLPORT | Transmit PFC Frame Priority 2 |
| `0x0050005e` | TPFC3r | XLPORT | Transmit PFC Frame Priority 3 |
| `0x0050005f` | TPFC4r | XLPORT | Transmit PFC Frame Priority 4 |
| `0x00500060` | TPFC5r | XLPORT | Transmit PFC Frame Priority 5 |
| `0x00500061` | TPFC6r | XLPORT | Transmit PFC Frame Priority 6 |
| `0x00500062` | TPFC7r | XLPORT | Transmit PFC Frame Priority 7 |
| `0x00500063` | TNCLr | XLPORT | Transmit Total Collision Counter |
| `0x00500064` | TBYTr | XLPORT | Transmit Byte Counter |
| `0x00500065` | RX_EEE_LPI_EVENT_COUNTERr | XLPORT | RX EEE LPI Event Counter. |
| `0x00500066` | RX_EEE_LPI_DURATION_COUNTERr | XLPORT | RX EEE LPI Duration Counter. |
| `0x00500067` | TX_EEE_LPI_EVENT_COUNTERr | XLPORT | TX EEE LPI Event Counter. |
| `0x00500068` | TX_EEE_LPI_DURATION_COUNTERr | XLPORT | TX EEE LPI Duration Counter. |
| `0x00500069` | RX_LLFC_PHY_COUNTERr | XLPORT | Receive Physical Type LLFC message counter |
| `0x0050006a` | RX_LLFC_LOG_COUNTERr | XLPORT | Receive Logical Type LLFC message Counter |
| `0x0050006b` | RX_LLFC_CRC_COUNTERr | XLPORT | Receive Type LLFC message with CRC error Counter |
| `0x0050006c` | TX_LLFC_LOG_COUNTERr | XLPORT | Transmit Logical Type LLFC message counter |
| `0x00500200` | XLPORT_CONFIGr | XLPORT | XLPORT Configuration Register, per Port 0,1,2,3 |
| `0x00500201` | XPAUSE_TX_PKT_XOFF_VALr | XLPORT | XPORT PAUSE XOFF timer value |
| `0x00500202` | XPAUSE_WATCHDOG_INIT_VALr | XLPORT | XPORT PAUSE Watchdog initial timer loading value |
| `0x00500203` | XPAUSE_WATCHDOG_THRESHr | XLPORT | XPORT PAUSE Watchdog XOFF retransmit timer threshold. |
| `0x00500204` | XPAUSE_MH0r | XLPORT | XPORT PAUSE MH 1st 4 bytes |
| `0x00500205` | XPAUSE_MH1r | XLPORT | XPORT PAUSE MH 2nd 4 bytes |
| `0x00500206` | XPAUSE_MH2r | XLPORT | XPORT PAUSE MH 3rd 4 bytes |
| `0x00500207` | XPAUSE_MH3r | XLPORT | XPORT PAUSE MH 4th 4 bytes |
| `0x00500208` | XPAUSE_D0r | XLPORT | XPORT PAUSE Data 1st 4 bytes |
| `0x00500209` | XPAUSE_D1r | XLPORT | XPORT PAUSE Data 2nd 4 bytes |
| `0x0050020a` | XPAUSE_D2r | XLPORT | XPORT PAUSE Data 3rd 4 bytes |
| `0x0050020b` | XPAUSE_D3r | XLPORT | XPORT PAUSE Data 4th 4 bytes |
| `0x0050020c` | XIBP_MH0r | XLPORT | XPORT E2E IBP pkt MH 1st 4 bytes |
| `0x0050020d` | XIBP_MH1r | XLPORT | XPORT E2E IBP pkt MH 2nd 4 bytes |
| `0x0050020e` | XIBP_MH2r | XLPORT | XPORT E2E IBP pkt MH 3rd 4 bytes |
| `0x0050020f` | XIBP_MH3r | XLPORT | XPORT E2E IBP pkt MH 4th 4 bytes |
| `0x00500210` | XIBP_D0r | XLPORT | XPORT E2E IBP Data 1st 4 bytes |
| `0x00500211` | XIBP_D1r | XLPORT | XPORT E2E IBP Data 2nd 4 bytes |
| `0x00500212` | XIBP_D2r | XLPORT | XPORT E2E IBP Data 3rd 4 bytes |
| `0x00500213` | XIBP_D3r | XLPORT | XPORT E2E IBP Data 4th 4 bytes |
| `0x00500214` | XPAUSE_RX_DA_MSr | XLPORT | XPORT PAUSE RX pkt DA - upper 16 bits |
| `0x00500215` | XPAUSE_RX_DA_LSr | XLPORT | XPORT PAUSE RX pkt DA - lower 32 bits |
| `0x00500216` | XPAUSE_RX_LENGTH_TYPEr | XLPORT | XPORT PAUSE Rx pkt expected Length/Type field |
| `0x00500217` | XPAUSE_RX_OPCODEr | XLPORT | XPORT PAUSE Rx pkt expected Opcode field |
| `0x00500218` | XLP_TXFIFO_PKT_DROP_CTLr | XLPORT | XLPORT TX FIFO Packet Drop Enable Control |
| `0x00500219` | XLP_TXFIFO_CELL_CNTr | XLPORT | XLPORT TX FIFO Cell Count register |
| `0x0050021a` | XLP_TXFIFO_CELL_REQ_CNTr | XLPORT | XLPORT TX FIFO Cell Request Count Register |
| `0x0050021b` | XLP_TXFIFO_OVRFLWr | XLPORT | XLPORT TX FIFO Overflow Status Register |
| `0x0050021c` | XTPSEr | XLPORT | Transmit PAUSE Control Frame Counter under XPORT pausing mode |
| `0x0050021d` | XTHOLr | XLPORT | Transmit End-to-End HOL packet counter |
| `0x0050021e` | XMODIDr | XLPORT | Module-IDs for 4 remote module |
| `0x0050021f` | XMODID_ENr | XLPORT | Module-ID enables for 4 remote module, Also Dual-modid-enable |
| `0x00500220` | XMODID_DUAL_ENr | XLPORT | Dual-modid enable |
| `0x00500221` | MAC_RSV_MASKr | XLPORT | MAC RSV MASK Register |
| `0x00500222` | MAC_STAT_UPDATE_MASKr | XLPORT | MAC RSV Statistical Counter Update MASK Register |
| `0x00500223` | XLP_EEE_COUNTER_MODEr | XLPORT | EEE Counter Mode Register |
| `0x00500224` | LAG_FAILOVER_CONFIGr | XLPORT | XLPORT LAG Failover Loopback Config |
| `0x00500225` | LAG_FAILOVER_STATUSr | XLPORT | XLPORT LAG Failover Loopback Status |
| `0x00500226` | GPORT_CONFIGr | XLPORT | GPORT configuration Register |
| `0x00500227` | GPORT_CNTMAXSIZEr | XLPORT | GPORT CNTMAXSIZE register |
| `0x00500228` | GPORT_SGNDET_EARLYCRSr | XLPORT | GPORT config bits for signal-detect and early-crs |
| `0x00500501` | IPG_HD_BKP_CNTLr | XLPORT | The control register for HD-BackPressure. |
| `0x00500502` | COMMAND_CONFIGr | XLPORT | Command register. Used by the host processor to control and configure the core |
| `0x00500503` | MAC_0r | XLPORT | MAC Address 32-Bit Word 0. Core MAC address bit 0 to 31. |
| `0x00500504` | MAC_1r | XLPORT | MAC Address 32-Bit Word 1. Core MAC address bit 32 to 47. |
| `0x00500505` | FRM_LENGTHr | XLPORT | Maximum Frame Length. |
| `0x00500506` | PAUSE_QUANTr | XLPORT | Receive Pause Quanta. |
| `0x00500510` | SFD_OFFSETr | XLPORT | EFM Preamble Length. |
| `0x00500511` | MAC_MODEr | XLPORT | MAC Mode. MAC Speed and Duplex Mode configuration from register COMMAND_CONFIG, when ENA_E |
| `0x00500512` | TAG_0r | XLPORT | Programmable vlan outer tag |
| `0x00500513` | TAG_1r | XLPORT | Programmable vlan inner tag |
| `0x00500514` | RX_PAUSE_QUANTA_SCALEr | XLPORT | programmable Rx pause quanta scaler. Static register. Affects Xoff values only |
| `0x00500515` | TX_PREAMBLEr | XLPORT | Programmable Preamble at Tx. |
| `0x00500517` | TX_IPG_LENGTHr | XLPORT | Programmable Inter-Packet-Gap (IPG). |
| `0x00500518` | PFC_XOFF_TIMERr | XLPORT | XOFF Timer value for PFC Tx packet |
| `0x00500519` | UMAC_EEE_CTRLr | XLPORT | control configs for EEE feature |
| `0x0050051a` | EEE_DELAY_ENTRY_TIMERr | XLPORT | EEE LPI timer |
| `0x0050051b` | EEE_WAKE_TIMERr | XLPORT | EEE Wake timer |
| `0x0050051c` | UMAC_EEE_REF_COUNTr | XLPORT | clock divider for 1 us quanta count in EEE |
| `0x005005c0` | MAC_PFC_TYPEr | XLPORT | Programmable ethertype (GNAT 13440) |
| `0x005005c1` | MAC_PFC_OPCODEr | XLPORT | Programmable opcode (GNAT 13440) |
| `0x005005c2` | MAC_PFC_DA_0r | XLPORT | lower 32 bits of programmable DA for PPP (GNAT 13897) |
| `0x005005c3` | MAC_PFC_DA_1r | XLPORT | upper 16 bits of programmable DA for PPP (GNAT 13897) |
| `0x005005c4` | MACSEC_PROG_TX_CRCr | XLPORT | Programmable CRC value to corrupt the Tx CRC to be used in MACSEC (GNAT 12078) |
| `0x005005c5` | MACSEC_CNTRLr | XLPORT | Miscellaneous control for MACSEC (GNAT 11599,11600,12078,12198) |
| `0x005005c6` | TS_STATUS_CNTRLr | XLPORT | Timestamp contrl/status |
| `0x005005c7` | TX_TS_DATAr | XLPORT | Transmit Timestamp data |
| `0x005005cc` | PAUSE_CONTROLr | XLPORT | PAUSE frame timer control register |
| `0x005005cd` | FLUSH_CONTROLr | XLPORT | Flush enable control register |
| `0x005005ce` | RXFIFO_STATr | XLPORT | RXFIFO status register |
| `0x005005cf` | TXFIFO_STATr | XLPORT | TXFIFO status register |
| `0x005005d0` | UNIMAC_PFC_CTRLr | XLPORT | PPP control register |
| `0x005005d1` | MAC_PFC_REFRESH_CTRLr | XLPORT | PPP refresh control register |
| `0x00500600` | XMAC_CTRLr | XLPORT | MAC control. |
| `0x00500601` | XMAC_MODEr | XLPORT | XMAC Mode register |
| `0x00500602` | XMAC_SPARE0r | XLPORT | Spare reg for ECO on Core, RX & TX clock domains |
| `0x00500603` | XMAC_SPARE1r | XLPORT | Additional Spare reg for ECO on core clock domain |
| `0x00500604` | XMAC_TX_CTRLr | XLPORT | Transmit control. |
| `0x00500605` | XMAC_TX_MAC_SAr | XLPORT | Transmit Source Address. |
| `0x00500606` | XMAC_RX_CTRLr | XLPORT | Receive control. |
| `0x00500607` | XMAC_RX_MAC_SAr | XLPORT | Receive source address. |
| `0x00500608` | XMAC_RX_MAX_SIZEr | XLPORT | Receive maximum packet size. |
| `0x00500609` | XMAC_RX_VLAN_TAGr | XLPORT | Inner and Outer VLAN tag fields |
| `0x0050060a` | XMAC_RX_LSS_CTRLr | XLPORT | Control for LSS (ordered set) messages |
| `0x0050060b` | XMAC_RX_LSS_STATUSr | XLPORT | Status for LSS (ordered set) messages. These bits are sticky by nature, and can be cleared |
| `0x0050060c` | XMAC_CLEAR_RX_LSS_STATUSr | XLPORT | Clear the RX LSS Status register, used for resetting the sticky status bits |
| `0x0050060d` | XMAC_PAUSE_CTRLr | XLPORT | Transmit PAUSE threshold. |
| `0x0050060e` | XMAC_PFC_CTRLr | XLPORT | Transmit Per-Priority FLOW Control |
| `0x0050060f` | XMAC_PFC_TYPEr | XLPORT | Transmit PFC Ethertype |
| `0x00500610` | XMAC_PFC_OPCODEr | XLPORT | Transmit PFC Opcode |
| `0x00500611` | XMAC_PFC_DAr | XLPORT | PFC Destination Address. |
| `0x00500612` | XMAC_LLFC_CTRLr | XLPORT | LLFC Control Register |
| `0x00500613` | XMAC_TX_LLFC_MSG_FIELDSr | XLPORT | Programmable TX LLFC Message fields. |
| `0x00500614` | XMAC_RX_LLFC_MSG_FIELDSr | XLPORT | Programmable RX LLFC Message fields |
| `0x00500615` | XMAC_HCFC_CTRLr | XLPORT | HCFC Control Register |
| `0x00500616` | XMAC_TX_TIMESTAMP_FIFO_DATAr | XLPORT | The TimeStamp value of the Tx packets. |
| `0x00500617` | XMAC_TX_TIMESTAMP_FIFO_STATUSr | XLPORT | Tx TimeStamp FIFO Status. |
| `0x00500618` | XMAC_FIFO_STATUSr | XLPORT | FIFO status register. These bits are sticky by nature, and can be cleared by writing to th |
| `0x00500619` | XMAC_CLEAR_FIFO_STATUSr | XLPORT | Clear FIFO status register, used for restting the sticky status bits |
| `0x0050061a` | XMAC_TX_FIFO_CREDITSr | XLPORT | Register for programming the TX FIFO credits for each port |
| `0x0050061b` | XMAC_EEE_CTRLr | XLPORT | Register for EEE Control |
| `0x0050061c` | XMAC_EEE_TIMERSr | XLPORT | EEE Timers |
| `0x00580000` | PORT_GROUP4_TDM_REGr | PORT_GROUP4 |  |
| `0x00580000` | PORT_GROUP4_TDM_REG_0r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580000` | PORT_GROUP5_TDM_REGr | PORT_GROUP5 |  |
| `0x00580000` | PORT_GROUP5_TDM_REG_0r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580001` | PORT_GROUP4_TDM_REG_1r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580001` | PORT_GROUP5_TDM_REG_1r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580002` | PORT_GROUP4_TDM_REG_2r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580002` | PORT_GROUP5_TDM_REG_2r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580003` | PORT_GROUP4_TDM_REG_3r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580003` | PORT_GROUP5_TDM_REG_3r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580004` | PORT_GROUP4_TDM_REG_4r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580004` | PORT_GROUP5_TDM_REG_4r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580005` | PORT_GROUP4_TDM_REG_5r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580005` | PORT_GROUP5_TDM_REG_5r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580006` | PORT_GROUP4_TDM_REG_6r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580006` | PORT_GROUP5_TDM_REG_6r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580007` | PORT_GROUP4_TDM_REG_7r | PORT_GROUP4 | TDM TABLE configuration |
| `0x00580007` | PORT_GROUP5_TDM_REG_7r | PORT_GROUP5 | TDM TABLE configuration |
| `0x00580008` | PORT_GROUP4_TDM_CONTROLr | PORT_GROUP4 | TDM TABLE Control |
| `0x00580008` | PORT_GROUP5_TDM_CONTROLr | PORT_GROUP5 | TDM TABLE Control |
| `0x00580009` | PORT_GROUP4_BOD_FIFO_ECC_ENABLEr | PORT_GROUP4 | PORT_GROUP4_BOD_FIFO_ECC_ENABLE |
| `0x00580009` | PORT_GROUP5_BOD_FIFO_ECC_ENABLEr | PORT_GROUP5 | PORT_GROUP5_BOD_FIFO_ECC_ENABLE |
| `0x0058000a` | PORT_GROUP4_XLPORT_POWER_DOWN_ENABLEr | PORT_GROUP4 | PORT_GROUP4_XLPORT_POWER_DOWN_ENABLE |
| `0x0058000a` | PORT_GROUP5_XLPORT_POWER_DOWN_ENABLEr | PORT_GROUP5 | PORT_GROUP5_XLPORT_POWER_DOWN_ENABLE |
| `0x0058000b` | PG4_INTR_STATUSr | PORT_GROUP4 | PORT_GROUP4_INTR_STATUS |
| `0x0058000b` | PG5_INTR_STATUSr | PORT_GROUP5 | PORT_GROUP5_INTR_STATUS |
| `0x0058000c` | PG4_INTR_ENABLEr | PORT_GROUP4 | PORT_GROUP4_INTR_ENABLE |
| `0x0058000c` | PG5_INTR_ENABLEr | PORT_GROUP5 | PORT_GROUP5_INTR_ENABLE |
| `0x0058000d` | PORT_GROUP4_BOD_FIFO_FULL_ERR_STATUSr | PORT_GROUP4 | PORT_GROUP4_BOD_FIFO_FULL_ERR_STATUS |
| `0x0058000d` | PORT_GROUP5_QGPORT_ENABLEr | PORT_GROUP5 | QGPORT_ENABLE |
| `0x0058000e` | PORT_GROUP4_CTRL_FIFO_FULL_ERR_STATUSr | PORT_GROUP4 | PORT_GROUP4_CTRL_FIFO_FULL_ERR_STATUS |
| `0x00580010` | PORT_GROUP4_XLP0_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP0_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580010` | PORT_GROUP5_XLP0_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP0_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580011` | PORT_GROUP4_XLP0_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP0_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580011` | PORT_GROUP5_XLP0_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP0_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580012` | PORT_GROUP4_XLP1_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP1_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580012` | PORT_GROUP5_XLP1_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP1_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580013` | PORT_GROUP4_XLP1_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP1_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580013` | PORT_GROUP5_XLP1_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP1_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580014` | PORT_GROUP4_XLP2_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP2_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580014` | PORT_GROUP5_XLP2_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP2_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580015` | PORT_GROUP4_XLP2_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP2_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580015` | PORT_GROUP5_XLP2_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP2_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580016` | PORT_GROUP4_XLP3_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP3_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580016` | PORT_GROUP5_XLP3_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP3_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580017` | PORT_GROUP4_XLP3_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP4 | XLP3_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580017` | PORT_GROUP5_XLP3_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP3_CTRL_FIFO_ECC_STATUS_INTR |
| `0x00580018` | PORT_GROUP4_ISO_ENABLEr | PORT_GROUP4 | PG4_ISO_ENABLE |
| `0x00580018` | PORT_GROUP5_XLP4_BOD_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP4_BOD_FIFO_ECC_STATUS_INTR |
| `0x00580019` | PORT_GROUP5_XLP4_CTRL_FIFO_ECC_STATUS_INTRr | PORT_GROUP5 | XLP4_CTRL_FIFO_ECC_STATUS_INTR |
| `0x0058001a` | PORT_GROUP5_BOD_FIFO_FULL_ERR_STATUSr | PORT_GROUP5 | PORT_GROUP5_BOD_FIFO_FULL_ERR_STATUS |
| `0x0058001b` | PORT_GROUP5_CTRL_FIFO_FULL_ERR_STATUSr | PORT_GROUP5 | PORT_GROUP5_CTRL_FIFO_FULL_ERR_STATUS |
| `0x0058001c` | PORT_GROUP5_ISO_ENABLEr | PORT_GROUP5 | PG5_ISO_ENABLE |
| `0x00580229` | XLPORT_MODE_REGr | XLPORT | XLPORT Mode Register |
| `0x0058022a` | XLPORT_PORT_ENABLEr | XLPORT | XLPORT Port Enable Register |
| `0x0058022b` | XLPORT_XMAC_CONTROLr | XLPORT | XLPORT XMAC Control Register |
| `0x0058022c` | XLPORT_MIB_RESETr | XLPORT | XLPORT MIB Counters Reset |
| `0x0058022d` | XLPORT_XGXS_COUNTER_MODEr | XLPORT | XLPORT XGXS Counter Compatiblity Mode |
| `0x0058022e` | XLPORT_EEE_DURATION_TIMER_PULSEr | XLPORT | XLPORT EEE Duration Timer Pulse Threshold |
| `0x0058022f` | XHOL_MH0r | XLPORT | XPORT E2E HOL pkt MH 1st 4 bytes |
| `0x00580230` | XHOL_MH1r | XLPORT | XPORT E2E HOL pkt MH 2nd 4 bytes |
| `0x00580231` | XHOL_MH2r | XLPORT | XPORT E2E HOL pkt MH 3rd 4 bytes |
| `0x00580232` | XHOL_MH3r | XLPORT | XPORT E2E HOL pkt MH 4th 4 bytes |
| `0x00580233` | XHOL_D0r | XLPORT | XPORT E2E HOL Data 1st 4 bytes |
| `0x00580234` | XHOL_D1r | XLPORT | XPORT E2E HOL Data 2nd 4 bytes |
| `0x00580235` | XHOL_D2r | XLPORT | XPORT E2E HOL Data 3rd 4 bytes |
| `0x00580236` | XHOL_D3r | XLPORT | XPORT E2E HOL Data 4th 4 bytes |
| `0x00580237` | XLPORT_XGXS_CTRL_REGr | XLPORT | Controls for Warpcore |
| `0x00580238` | XLPORT_XGXS_STATUS_GEN_REGr | XLPORT | Status signals from Warpcore for signals common to all four lanes. |
| `0x00580239` | XLPORT_XGXS0_STATUS0_REGr | XLPORT | Status signals from Warpcore Lane0: first set |
| `0x00580239` | XLPORT_XGXS_STATUS0_REGr | XLPORT |  |
| `0x0058023a` | XLPORT_XGXS0_STATUS1_REGr | XLPORT | Status signals from Warpcore Lane0 : second set |
| `0x0058023a` | XLPORT_XGXS_STATUS1_REGr | XLPORT |  |
| `0x0058023b` | XLPORT_XGXS1_STATUS0_REGr | XLPORT | Status signals from Warpcore Lane1: first set |
| `0x0058023c` | XLPORT_XGXS1_STATUS1_REGr | XLPORT | Status signals from Warpcore Lane1 : second set |
| `0x0058023d` | XLPORT_XGXS2_STATUS0_REGr | XLPORT | Status signals from Warpcore Lane2: first set |
| `0x0058023e` | XLPORT_XGXS2_STATUS1_REGr | XLPORT | Status signals from Warpcore Lane2 : second set |
| `0x0058023f` | XLPORT_XGXS3_STATUS0_REGr | XLPORT | Status signals from Warpcore Lane3: first set |
| `0x00580240` | XLPORT_XGXS3_STATUS1_REGr | XLPORT | Status signals from Warpcore Lane3 : second set |
| `0x00580241` | XLPORT_WC_UCMEM_CTRLr | XLPORT | XLPORT Warpcore micro-controller Memory Parallel Bus Control Register |
| `0x00580242` | XLPORT_ECC_CONTROLr | XLPORT | XLPORT memories ECC control register |
| `0x00580243` | XLPORT_FORCE_DOUBLE_BIT_ERRORr | XLPORT | XLPORT memories double bit error control register |
| `0x00580244` | XLPORT_FORCE_SINGLE_BIT_ERRORr | XLPORT | XLPORT memories single bit error control register |
| `0x00580245` | XLPORT_MIB_RSC_MEM4_ECC_STATUSr | XLPORT | XLPORT MIB RX Statistic Counter memory instance 4 ECC status register |
| `0x00580246` | XLPORT_MIB_RSC_MEM3_ECC_STATUSr | XLPORT | XLPORT MIB RX Statistic Counter memory instance 3 ECC status register |
| `0x00580247` | XLPORT_MIB_RSC_MEM2_ECC_STATUSr | XLPORT | XLPORT MIB RX Statistic Counter memory instance 2 ECC status register |
| `0x00580248` | XLPORT_MIB_RSC_MEM1_ECC_STATUSr | XLPORT | XLPORT MIB RX Statistic Counter memory instance 1 ECC status register |
| `0x00580249` | XLPORT_MIB_RSC_MEM0_ECC_STATUSr | XLPORT | XLPORT MIB RX Statistic Counter memory instance 0 ECC status register |
| `0x0058024a` | XLPORT_MIB_TSC_MEM3_ECC_STATUSr | XLPORT | XLPORT Port 3 MIB TX Statistic Counter memory ECC status register |
| `0x0058024b` | XLPORT_MIB_TSC_MEM2_ECC_STATUSr | XLPORT | XLPORT MIB TX Statistic Counter memory instance 2 ECC status register |
| `0x0058024c` | XLPORT_MIB_TSC_MEM1_ECC_STATUSr | XLPORT | XLPORT MIB TX Statistic Counter memory instance 1 ECC status register |
| `0x0058024d` | XLPORT_MIB_TSC_MEM0_ECC_STATUSr | XLPORT | XLPORT MIB TX Statistic Counter memory instance 0 ECC status register |
| `0x0058024e` | XLPORT_TXFIFO_MEM_ECC_STATUSr | XLPORT | XLPORT TX FIFO memory ECC status register |
| `0x0058024f` | XLPORT_MEMORY_CONTROL0r | XLPORT | Memory control fields |
| `0x00580250` | XLPORT_MEMORY_CONTROL1r | XLPORT | Memory control fields |
| `0x00580251` | XLPORT_MEMORY_CONTROL2r | XLPORT | Memory control fields |
| `0x00580252` | XLPORT_INTR_STATUSr | XLPORT | XLPORT interrupt status register |
| `0x00580253` | XLPORT_INTR_ENABLEr | XLPORT | XLPORT interrupt enable register |
| `0x00580254` | XLPORT_LINKSTATUS_DOWNr | XLPORT | Link status down sticky register |
| `0x00580255` | XLPORT_LINKSTATUS_DOWN_CLEARr | XLPORT | Link status down sticky bit clear register |
| `0x0110060b` | IE2E_CONTROLr | IPIPE | End-to-End Control Register |
| `0x01180600` | ING_CONFIG_64r | IPIPE | Switch configuration register |
| `0x01180601` | DOS_CONTROL_3r | IPIPE | DOS (Denial of Service) Attack Control Register. |
| `0x01180602` | ING_CONFIG_2r | IPIPE | Ingress Config Register 2. |
| `0x01180603` | VLAN_CTRLr | IPIPE | VLAN Control Register #1 |
| `0x0118060c` | FLEXIBLE_IPV6_EXT_HDRr | IPIPE | Programmable IPv6 extension header value. |
| `0x01180610` | MC_CONTROL_1r | IPIPE | Multicast Control Register1 for HiGig2 pkts |
| `0x01180d00` | CFG_RAM_DBGCTRLr | IPIPE | CFG_RAM_CONTROL |
| `0x01180d01` | PORT_TABLE_ECC_CONTROLr | IPIPE | PORT_TABLE_ECC_CONTROL, FeatureSpecific-Ethernet |
| `0x01180d02` | PORT_TABLE_ECC_STATUS_INTRr | IPIPE | PORT_TABLE_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01180d03` | PORT_TABLE_ECC_STATUS_NACKr | IPIPE | PORT_TABLE_ECC_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01180d04` | SYSTEM_CONFIG_PARITY_CONTROLr | IPIPE | SYSTEM_CONFIG_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x01180d05` | SYSTEM_CONFIG_PARITY_STATUS_INTRr | IPIPE | SYSTEM_CONFIG_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01180d06` | SYSTEM_CONFIG_PARITY_STATUS_NACKr | IPIPE | SYSTEM_CONFIG_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01180d07` | SYSTEM_CONFIG_MODVIEW_PARITY_CONTROLr | IPIPE | SYSTEM_CONFIG_MODVIEW_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x01180d08` | SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_INTRr | IPIPE | SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01180d09` | SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_NACKr | IPIPE | SYSTEM_CONFIG_MODVIEW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01180d0a` | SOURCE_TRUNK_MAP_MODVIEW_PARITY_CONTROLr | IPIPE | SOURCE_TRUNK_MAP_MODVIEW_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x01180d0b` | SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_INTRr | IPIPE | SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01180d0c` | SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_NACKr | IPIPE | SOURCE_TRUNK_MAP_MODVIEW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01200606` | EGR_VLAN_CONTROL_1r | EPIPE | Controls Vlan Translate and VLAN membership related functions. |
| `0x01200610` | EGR_IPMC_CFG2r | EPIPE | Configuration Register for IPMC related modifications. |
| `0x01200634` | EGR_PORT_TO_NHI_MAPPINGr | EPIPE | Maps Egress Port to a Next Hop Index. |
| `0x01280600` | EGR_CONFIGr | EPIPE | Configuration Register for the entire chip. |
| `0x01280601` | EGR_CONFIG_1r | EPIPE | Configuration Register Extension for the entire chip. |
| `0x01280602` | EGR_CONFIG_2r | EPIPE | Egress Pipeline stage config register 2. |
| `0x01280603` | EGR_BYPASS_CTRLr | EPIPE | Egress Pipeline stage bypass control register |
| `0x01280609` | EGR_MIRROR_SELECTr | EPIPE | Egress Mirror select register, FeatureSpecific-Ethernet |
| `0x0128060a` | EGR_L3_TUNNEL_PFM_VIDr | EPIPE | L3 Tunnel Terminated VLAN Override Register |
| `0x0128060b` | EGR_NIV_ETHERTYPEr | EPIPE | Egress NIV Ethertype Control Register. |
| `0x01280611` | EGR_SD_TAG_CONTROLr | EPIPE | Egress Mirror select register, FeatureSpecific-Ethernet |
| `0x01280620` | EGR_QCN_CNTAG_ETHERTYPEr | EPIPE | QCN CNTAG Ethertype Control Register. |
| `0x01280621` | EGR_QCN_CNM_ETHERTYPEr | EPIPE | QCN CNM Ethertype Control Register. |
| `0x01280622` | EGR_HBFC_CNTAG_ETHERTYPEr | EPIPE | HBFC CNTAG Ethertype Control Register. |
| `0x01280623` | EGR_HBFC_CNM_ETHERTYPEr | EPIPE | HBFC CNM Ethertype Control Register. |
| `0x01280631` | EGR_QCN_CNM_CONTROL_1r | EPIPE | Egress CNM Control Register 1. |
| `0x01280632` | EGR_QCN_CNM_CONTROL_2r | EPIPE | Egress CNM Control Register 2. |
| `0x01280633` | EGR_LOOPBACK_PORT_TPIDr | EPIPE | Loopback Port's TPID Register. |
| `0x01280700` | EGR_EL3_ECC_PARITY_CONTROLr | EPIPE | EGR_L3_INTF_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x01280718` | EGR_EL3_STBY_CONTROLr | EPIPE | Control register for standby bits of El3 and Einitbuf stage memories |
| `0x01280719` | EGR_EL3_PM_CONTROLr | EPIPE | Control register for pm bits of El3 stage memories |
| `0x0128071a` | EGR_EL3_RAM_CONTROLr | EPIPE | Control register for tm bits of El3 stage memories |
| `0x0128071b` | EGR_EL3_RAM_CONTROL_2r | EPIPE | Control register for tm bits of El3 stage memories |
| `0x01280d01` | EGR_MPB_ECC_STATUS_INTRr | EPIPE | ECC interrupt status register for MPB memory |
| `0x01280d02` | EGR_L3_NEXT_HOP_PARITY_STATUS_INTRr | EPIPE | EGR_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d03` | EGR_L3_NEXT_HOP_PARITY_STATUS_NACKr | EPIPE | EGR_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d04` | EGR_L3_INTF_PARITY_STATUS_INTRr | EPIPE | EGR_L3_INTF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d05` | EGR_L3_INTF_PARITY_STATUS_NACKr | EPIPE | EGR_L3_INTF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d06` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_INTRr | EPIPE | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d07` | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_NACKr | EPIPE | EGR_MPLS_VC_AND_SWAP_LABEL_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d08` | EGR_MAC_DA_PROFILE_PARITY_STATUS_INTRr | EPIPE | EGR_MAC_DA_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d09` | EGR_MAC_DA_PROFILE_PARITY_STATUS_NACKr | EPIPE | EGR_MAC_DA_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d0a` | EGR_DVP_ATTRIBUTE_PARITY_STATUS_INTRr | EPIPE | EGR_DVP_ATTRIBUTE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d0b` | EGR_DVP_ATTRIBUTE_PARITY_STATUS_NACKr | EPIPE | EGR_DVP_ATTRIBUTE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d0c` | EGR_VFI_PARITY_STATUS_INTRr | EPIPE | EGR_VFI_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d0d` | EGR_VFI_PARITY_STATUS_NACKr | EPIPE | EGR_VFI_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d0e` | EGR_PORT_PARITY_STATUS_INTRr | EPIPE | EGR_PORT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d0f` | EGR_PORT_PARITY_STATUS_NACKr | EPIPE | EGR_PORT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d10` | EGR_IPMC_PARITY_STATUS_INTRr | EPIPE | EGR_IPMC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d11` | EGR_IPMC_PARITY_STATUS_NACKr | EPIPE | EGR_IPMC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d12` | EGR_MAP_MH_PARITY_STATUS_INTRr | EPIPE | EGR_MAP_MH_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d13` | EGR_MAP_MH_PARITY_STATUS_NACKr | EPIPE | EGR_MAP_MH_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d14` | EGR_VLAN_CONTROL_1_PARITY_STATUS_INTRr | EPIPE | EGR_VLAN_CONTROL_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d15` | EGR_VLAN_CONTROL_1_PARITY_STATUS_NACKr | EPIPE | EGR_VLAN_CONTROL_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x01280d16` | EGR_IPMC_CFG2_PARITY_STATUS_INTRr | EPIPE | EGR_IPMC_CFG2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x01280d17` | EGR_IPMC_CFG2_PARITY_STATUS_NACKr | EPIPE | EGR_IPMC_CFG2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02100600` | ING_MODMAP_CTRLr | IPIPE | Ingress Module Remapping Control Register |
| `0x02100601` | IHG_LOOKUPr | IPIPE | Higig Lookup Register to hold virtual port parameters |
| `0x02100608` | HG_LOOKUP_DESTINATIONr | IPIPE | Destination to match to enable Proxy HG Lookup |
| `0x02180600` | E2E_HOL_RX_DA_MSr | IPIPE | End-to-End HOL MSB DA Register |
| `0x02180601` | E2E_HOL_RX_DA_LSr | IPIPE | End-to-End HOL LSB DA Register |
| `0x02180602` | E2E_HOL_RX_LENGTH_TYPEr | IPIPE | End-to-End HOL Length/Type Register |
| `0x02180603` | E2E_HOL_RX_OPCODEr | IPIPE | End-to-End HOL Opcode Register |
| `0x02180604` | E2E_IBP_RX_DA_MSr | IPIPE | End-to-End IBP MSB DA Register |
| `0x02180605` | E2E_IBP_RX_DA_LSr | IPIPE | End-to-End IBP LSB DA Register |
| `0x02180606` | E2E_IBP_RX_LENGTH_TYPEr | IPIPE | End-to-End IBP Length/Type Register |
| `0x02180607` | E2E_IBP_RX_OPCODEr | IPIPE | End-to-End IBP Opcode Register |
| `0x02180609` | ING_SYS_RSVD_VIDr | IPIPE | VID in HG header to indicate real VID is inside packet |
| `0x0218062c` | RTAG7_HASH_CONTROLr | IPIPE | Rtag7 hashing control register |
| `0x02180632` | GLOBAL_MPLS_RANGE_1_LOWERr | IPIPE | MPLS label first global range lower bound. (Inclusive) |
| `0x02180633` | GLOBAL_MPLS_RANGE_1_UPPERr | IPIPE | MPLS label first global range upper bound. (Inclusive) |
| `0x02180634` | GLOBAL_MPLS_RANGE_2_LOWERr | IPIPE | MPLS label second global range lower bound. (Inclusive) |
| `0x02180635` | GLOBAL_MPLS_RANGE_2_UPPERr | IPIPE | MPLS label second global range upper bound. (Inclusive) |
| `0x02180638` | REMOTE_CPU_DA_MSr | IPIPE | Remote CPU pkt LSB DA Register |
| `0x02180639` | REMOTE_CPU_DA_LSr | IPIPE | Remote CPU pkt LSB DA Register |
| `0x0218063a` | REMOTE_CPU_LENGTH_TYPEr | IPIPE | Remote cpu pkt  Length/Type Register |
| `0x0218063b` | MIM_ETHERTYPEr | IPIPE | MAC-in-MAC Ethertype Control Register |
| `0x0218063c` | ING_OUTER_TPIDr | IPIPE | Ingress Outer TPID register |
| `0x0218063c` | ING_OUTER_TPID_0r | IPIPE | Ingress outer TPID matching register #0 |
| `0x0218063d` | ING_OUTER_TPID_1r | IPIPE | Ingress outer TPID matching register #1 |
| `0x0218063e` | ING_OUTER_TPID_2r | IPIPE | Ingress outer TPID matching register #2 |
| `0x0218063f` | ING_OUTER_TPID_3r | IPIPE | Ingress outer TPID matching register #3 |
| `0x02180640` | TS_CONTROLr | IPIPE | Holds TS control info |
| `0x02180641` | TS_CONTROL_1r | IPIPE | Vlaues for TS frame detection |
| `0x02180642` | TS_CONTROL_2r | IPIPE | Vlaues for TS frame detection |
| `0x02180643` | MMRP_CONTROL_1r | IPIPE | Values for MMRP frame detection |
| `0x02180644` | MMRP_CONTROL_2r | IPIPE | Values for MMRP frame detection |
| `0x02180645` | SRP_CONTROL_1r | IPIPE | Values for SRP frame detection |
| `0x02180646` | SRP_CONTROL_2r | IPIPE | Values for SRP frame detection |
| `0x02180647` | ING_BYPASS_CTRLr | IPIPE | bypass enable to each ip stage |
| `0x02180650` | NIV_ETHERTYPEr | IPIPE | NIV Ethertype Control Register. |
| `0x02180652` | ING_FCOE_ETHERTYPEr | IPIPE | FCoE Ethertype Control Register. |
| `0x02180653` | ING_WESP_PROTO_CONTROLr | IPIPE | Ingress WESP Protocol Control Register. |
| `0x02180660` | ING_QCN_CNTAG_ETHERTYPEr | IPIPE | QCN CNTAG Ethertype Control Register. |
| `0x02180661` | ING_QCN_CNM_ETHERTYPEr | IPIPE | QCN CNM Ethertype Control Register. |
| `0x02180662` | ING_HBFC_CNTAG_ETHERTYPEr | IPIPE | HBFC CNTAG Ethertype Control Register. |
| `0x02180663` | ING_HBFC_CNM_ETHERTYPEr | IPIPE | HBFC CNM Ethertype Control Register. |
| `0x02180670` | ING_VOQFC_MACDA_MSr | IPIPE | End-to-End VOQFC MSB MACDA Register. |
| `0x02180671` | ING_VOQFC_MACDA_LSr | IPIPE | End-to-End VOQFC LSB MACDA Register. |
| `0x02180672` | ING_VOQFC_IDr | IPIPE | End-to-End VOQFC id Register. |
| `0x02180681` | MC_CONTROL_2r | IPIPE | Multicast Control Register2 for HiGig2 pkts |
| `0x02180682` | MC_CONTROL_3r | IPIPE | Multicast Control Register3 for HiGig2 pkts |
| `0x02180d00` | L3_TUNNEL_CAM_DBGCTRLr | IPIPE | L3_TUNNEL_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x02180d01` | L3_TUNNEL_CAM_BIST_STATUSr | IPIPE | L3_TUNNEL_CAM_BIST_STATUS |
| `0x02180d02` | L3_TUNNEL_CAM_BIST_CONFIGr | IPIPE | L3_TUNNEL_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x02180d03` | L3_TUNNEL_CAM_BIST_DBG_DATAr | IPIPE | L3_TUNNEL_CAM_BIST_DBG_DATA |
| `0x02180d04` | UDF_CAM_DBGCTRLr | IPIPE | UDF_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x02180d05` | UDF_CAM_BIST_STATUSr | IPIPE | UDF_CAM_BIST_STATUS, FeatureSpecific-Ethernet |
| `0x02180d06` | UDF_CAM_BIST_CONFIGr | IPIPE | UDF_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x02180d07` | UDF_CAM_BIST_DBG_DATAr | IPIPE | UDF_CAM_BIST_DBG_DATA |
| `0x02180d08` | PARS_RAM_DBGCTRLr | IPIPE | PARS_RAM_CONTROL |
| `0x02180d09` | CPU_TS_PARITY_CONTROLr | IPIPE | CPU_TS_PARITY_CONTROL |
| `0x02180d0a` | CPU_TS_PARITY_STATUS_INTRr | IPIPE | CPU_TS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d0b` | CPU_TS_PARITY_STATUS_NACKr | IPIPE | CPU_TS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d0c` | VLAN_RANGE_PARITY_CONTROLr | IPIPE | VLAN_RANGE_PARITY_CONTROL |
| `0x02180d0d` | VLAN_RANGE_PARITY_STATUS_INTRr | IPIPE | VLAN_RANGE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d0e` | VLAN_RANGE_PARITY_STATUS_NACKr | IPIPE | VLAN_RANGE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d0f` | MOD_MAP_PARITY_CONTROLr | IPIPE | MOD_MAP_PARITY_CONTROL |
| `0x02180d10` | MOD_MAP_PARITY_STATUS_INTRr | IPIPE | MOD_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d11` | MOD_MAP_PARITY_STATUS_NACKr | IPIPE | MOD_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d12` | FP_UDF_PARITY_CONTROLr | IPIPE | FP_UDF_PARITY_CONTROL |
| `0x02180d13` | FP_UDF_PARITY_STATUS_INTRr | IPIPE | FP_UDF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d14` | FP_UDF_PARITY_STATUS_NACKr | IPIPE | FP_UDF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d15` | L3_TUNNEL_PARITY_CONTROLr | IPIPE | L3_TUNNEL_PARITY_CONTROL |
| `0x02180d16` | L3_TUNNEL_PARITY_STATUS_INTRr | IPIPE | L3_TUNNEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d17` | L3_TUNNEL_PARITY_STATUS_NACKr | IPIPE | L3_TUNNEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d18` | SRC_TRUNK_ECC_CONTROLr | IPIPE | SRC_TRUNK_ECC_CONTROL |
| `0x02180d19` | SRC_TRUNK_ECC_STATUS_INTRr | IPIPE | SRC_TRUNK_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d1a` | SRC_TRUNK_ECC_STATUS_NACKr | IPIPE | SRC_TRUNK_ECC_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02180d1b` | LPORT_ECC_CONTROLr | IPIPE | LPORT_ECC_CONTROL |
| `0x02180d1c` | LPORT_ECC_STATUS_INTRr | IPIPE | LPORT_ECC_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02180d1d` | LPORT_ECC_STATUS_NACKr | IPIPE | LPORT_ECC_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02200611` | EGR_VLAN_CONTROL_2r | EPIPE | Controls Vlan Translate and VLAN membership related functions. |
| `0x02200612` | EGR_VLAN_CONTROL_3r | EPIPE | Controls Vlan Translate and VLAN membership related functions. |
| `0x02200613` | EGR_PVLAN_EPORT_CONTROLr | EPIPE | Private VLAN Egress-port Control register |
| `0x02200614` | EGR_INGRESS_PORT_TPID_SELECTr | EPIPE | Controls per ingress port outgoing tpid selection. |
| `0x02200620` | EGR_VLAN_LOGIC_TO_PHYS_MAPr | EPIPE |  |
| `0x02280600` | EGR_OUTER_TPIDr | EPIPE | Egress Outer TPID register |
| `0x02280600` | EGR_OUTER_TPID_0r | EPIPE | Egress outer TPID register #0 |
| `0x02280601` | EGR_OUTER_TPID_1r | EPIPE | Egress outer TPID register #1 |
| `0x02280602` | EGR_OUTER_TPID_2r | EPIPE | Egress outer TPID register #2 |
| `0x02280603` | EGR_OUTER_TPID_3r | EPIPE | Egress outer TPID register #3 |
| `0x02280610` | EGR_VLAN_XLATE_HASH_CONTROLr | EPIPE | EGR_VLAN_XLATE_HASH_CONTROL, FeatureSpecific-Ethernet |
| `0x02280615` | EGR_TUNNEL_ID_MASKr | EPIPE | Global ID mask value for Tunnel Pkts. |
| `0x02280700` | EGR_VLAN_PARITY_CONTROLr | EPIPE | EGR_VLAN_PARITY_CONTROL |
| `0x0228071b` | EGR_VLAN_RAM_CONTROL_1r | EPIPE | Control register for tm bits of Evxlt stage memories |
| `0x0228071c` | EGR_VLAN_RAM_CONTROL_2r | EPIPE | Control register for tm bits of Evxlt stage memories (also used for Ehcpm and Einitbuf sta |
| `0x0228071d` | EGR_VLAN_RAM_CONTROL_3r | EPIPE | Control register for tm bits of Evxlt stage memories |
| `0x0228071e` | EGR_VLAN_RAM_CONTROL_4r | EPIPE | Control register for tm bits of Evxlt stage memories |
| `0x0228071f` | EGR_VLAN_RAM_CONTROL_DCMr | EPIPE | Control register for tm bits of Evxlt stage memories |
| `0x02280720` | EGR_VLAN_RAM_CONTROL_PDAHr | EPIPE | Control register for PDAH bits of Evxlt stage memories |
| `0x02280721` | EGR_VLAN_RAM_CONTROL_STBYr | EPIPE | Control register for STBY bits of Evxlt stage memories |
| `0x02280722` | EGR_VLAN_RAM_CONTROL_PMr | EPIPE | Control register for pm bits of Evxlt stage memories |
| `0x02280724` | EGR_INTR0_ENABLEr | EPIPE | Bitwise interrupt enable for EGR_INTR0_STATUS |
| `0x02280d01` | EGR_VLAN_PARITY_STATUS_INTRr | EPIPE | EGR_VLAN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d02` | EGR_VLAN_PARITY_STATUS_NACKr | EPIPE | EGR_VLAN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d03` | EGR_VLAN_STG_PARITY_STATUS_INTRr | EPIPE | EGR_VLAN_STG_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d04` | EGR_VLAN_STG_PARITY_STATUS_NACKr | EPIPE | EGR_VLAN_STG_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d05` | EGR_VLAN_XLATE_PARITY_STATUS_INTR_0r | EPIPE | EGR_VLAN_XLATE_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet |
| `0x02280d06` | EGR_VLAN_XLATE_PARITY_STATUS_INTR_1r | EPIPE | EGR_VLAN_XLATE_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet |
| `0x02280d07` | EGR_VLAN_XLATE_PARITY_STATUS_NACK_0r | EPIPE | EGR_VLAN_XLATE_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet |
| `0x02280d08` | EGR_VLAN_XLATE_PARITY_STATUS_NACK_1r | EPIPE | EGR_VLAN_XLATE_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet |
| `0x02280d09` | EGR_IP_TUNNEL_PARITY_STATUS_INTRr | EPIPE | EGR_IP_TUNNEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d0a` | EGR_IP_TUNNEL_PARITY_STATUS_NACKr | EPIPE | EGR_IP_TUNNEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d0b` | EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_INTRr | EPIPE | EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d0c` | EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_NACKr | EPIPE | EGR_MPLS_EXP_MAPPING_2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d0d` | EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_INTRr | EPIPE | EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d0e` | EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_NACKr | EPIPE | EGR_MPLS_EXP_MAPPING_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d0f` | EGR_MPLS_PRI_MAPPING_PARITY_STATUS_INTRr | EPIPE | EGR_MPLS_PRI_MAPPING_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d10` | EGR_MPLS_PRI_MAPPING_PARITY_STATUS_NACKr | EPIPE | EGR_MPLS_PRI_MAPPING_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d11` | EGR_PRI_CNG_MAP_PARITY_STATUS_INTRr | EPIPE | EGR_PRI_CNG_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d12` | EGR_PRI_CNG_MAP_PARITY_STATUS_NACKr | EPIPE | EGR_PRI_CNG_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d13` | EGR_DSCP_TABLE_PARITY_STATUS_INTRr | EPIPE | EGR_DSCP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x02280d14` | EGR_DSCP_TABLE_PARITY_STATUS_NACKr | EPIPE | EGR_DSCP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x02280d15` | EGR_FRAGMENT_ID_TABLE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for FRAGMENT_ID memory |
| `0x02280d16` | EGR_FRAGMENT_ID_TABLE_PARITY_STATUS_NACKr | EPIPE | PARITY nack status register for FRAGMENT_ID memory |
| `0x02280d17` | EGR_GPP_ATTRIBUTES_MODBASE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for GPP_ATTRIBUTES_MODBASE memory |
| `0x02280d18` | EGR_GPP_ATTRIBUTES_MODBASE_PARITY_STATUS_NACKr | EPIPE | PARITY nack status register for GPP_ATTRIBUTES_MODBASE memory |
| `0x02280d19` | EGR_GPP_ATTRIBUTES_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for GPP_ATTRIBUTES memory |
| `0x02280d1a` | EGR_GPP_ATTRIBUTES_PARITY_STATUS_NACKr | EPIPE | PARITY nack status register for GPP_ATTRIBUTES memory |
| `0x02280d23` | EGR_INTR0_STATUSr | EPIPE | EP Interrupt 0  Status |
| `0x02300020` | PORT_MIN_CELLr | MMU | PORT_MIN_CELL |
| `0x02300021` | PORT_MAX_SHARED_CELLr | MMU | PORT_MAX_SHARED_CELL |
| `0x02300022` | PORT_MAX_PKT_SIZEr | MMU | PORT_MAX_PKT_SIZE |
| `0x02300023` | PG_SHARED_LIMIT_CELLr | MMU | PG_SHARED_LIMIT_CELL |
| `0x0230002c` | PORT_RESUME_LIMIT_CELLr | MMU | PORT_RESUME_LIMIT |
| `0x02300030` | PG_RESET_OFFSET_CELLr | MMU | PG_RESET_OFFSET_CELL |
| `0x02300040` | PG_RESET_FLOOR_CELLr | MMU | PG_RESET_FLOOR_CELL |
| `0x02300050` | PG_MIN_CELLr | MMU | PG_MIN_CELL |
| `0x02300060` | PG_HDRM_LIMIT_CELLr | MMU | PG_HDRM_LIMIT_CELL |
| `0x02300070` | PORT_PRI_GRP0r | MMU | PORT_PRI_GRP0 |
| `0x02300071` | PORT_PRI_GRP1r | MMU | PORT_PRI_GRP1 |
| `0x02300072` | PORT_PRI_XON_ENABLEr | MMU | PORT_PRI_XON_ENABLE |
| `0x02300073` | PORT_PG_SPIDr | MMU | PORT_PG_SPID |
| `0x02300080` | PORT_COUNT_CELLr | MMU | PORT_COUNT_CELL |
| `0x02300082` | PORT_MIN_COUNT_CELLr | MMU | PORT_MIN_COUNT_CELL |
| `0x02300084` | PORT_SHARED_COUNT_CELLr | MMU | PORT_SHARED_COUNT_CELL |
| `0x023000a0` | PG_MIN_COUNT_CELLr | MMU | PG_MIN_COUNT_CELL |
| `0x023000b0` | PG_PORT_MIN_COUNT_CELLr | MMU | PG_PORT_MIN_COUNT_CELL |
| `0x023000c0` | PG_SHARED_COUNT_CELLr | MMU | PG_SHARED_COUNT_CELL |
| `0x023000d0` | PG_HDRM_COUNT_CELLr | MMU | PG_HDRM_COUNT_CELL |
| `0x023000e0` | PG_GBL_HDRM_COUNTr | MMU | PG_GBL_HDRM_COUNT |
| `0x023000e8` | PORT_FC_STATUSr | MMU | PORT_FC_STATUS |
| `0x023000f0` | PG_RESET_VALUE_CELLr | MMU | PG_RESET_VALUE_CELL |
| `0x02300136` | PORT_SHARED_MAX_PG_ENABLEr | MMU | limit port shared max to these pgs |
| `0x02300137` | PORT_MIN_PG_ENABLEr | MMU | limit port min to these pgs |
| `0x02300138` | FLOW_CONTROL_XOFF_STATEr | MMU | this port.pg is in flow control xoff state, based on pg_limit_state, port_limit_state and  |
| `0x02380002` | GLOBAL_HDRM_LIMITr | MMU | GLOBAL_HDRM_LIMIT |
| `0x02380003` | THDI_BYPASSr | MMU | THDI_BYPASS |
| `0x02380004` | INPUT_PORT_RX_ENABLE0_64r | MMU | INPUT_PORT_RX_ENABLE0 |
| `0x02380005` | INPUT_PORT_RX_ENABLE1_64r | MMU | INPUT_PORT_RX_ENABLE1 |
| `0x02380006` | PORT_PAUSE_ENABLE0_64r | MMU | PORT_PAUSE_ENABLE0 |
| `0x02380007` | PORT_PAUSE_ENABLE1_64r | MMU | PORT_PAUSE_ENABLE1 |
| `0x02380008` | PORT_OVQ_PAUSE_ENABLE0r | MMU | enable OVQ pause for MMU port 0-32 |
| `0x02380009` | PORT_OVQ_PAUSE_ENABLE1r | MMU | enable OVQ pause for MMU port 33-65 |
| `0x02380077` | TOTAL_BUFFER_COUNT_CELLr | MMU | TOTAL_BUFFER_COUNT_CELL |
| `0x0238007b` | GLOBAL_HDRM_COUNTr | MMU | GLOBAL_HDRM_COUNT |
| `0x02380100` | TOTAL_BUFFER_COUNT_CELL_SPr | MMU | TOTAL_BUFFER_COUNT_CELL per Service Pool |
| `0x02380104` | TOTAL_BUFFER_COUNT_CELL_SP_SHAREDr | MMU | TOTAL_BUFFER_COUNT_CELL shared among Service Pools 0-3 |
| `0x0238010a` | BUFFER_CELL_LIMIT_SPr | MMU | BUFFER_CELL_LIMIT per Service Pool |
| `0x0238010e` | BUFFER_CELL_LIMIT_SP_SHAREDr | MMU | BUFFER_CELL_LIMIT for shared Service Pool |
| `0x02380114` | CELL_RESET_LIMIT_OFFSET_SPr | MMU | CELL_RESET_LIMIT_OFFSET per Service Pool |
| `0x0238011c` | CELL_SPAP_YELLOW_OFFSET_SPr | MMU | CELL_SPAP_YELLOW_OFFSET per Service Pool |
| `0x02380120` | CELL_SPAP_RED_OFFSET_SPr | MMU | CELL_SPAP_RED_OFFSET per Service Pool |
| `0x02380131` | COLOR_AWAREr | MMU | color awareness per service pool |
| `0x02380132` | USE_SP_SHAREDr | MMU | allow a service pool to use sp_shared resources |
| `0x02380134` | PORT_LIMIT_STATE_0r | MMU | port limit state for pipe 0 |
| `0x02380135` | PORT_LIMIT_STATE_1r | MMU | port limit state for pipe 1 |
| `0x02380139` | POOL_DROP_STATEr | MMU | service pool drop state per pool.color, the 3 bits [2:0] organized as {green, yellow, red} |
| `0x0238013a` | PARITY_ERROR_STATUS_0r | MMU | parity errors detected from memories pipe 0, clear with system wide PARITY_STAT_CLEAR |
| `0x0238013b` | PARITY_ERROR_STATUS_1r | MMU | parity errors detected from memories pipe 1, clear with system wide PARITY_STAT_CLEAR |
| `0x0238013c` | MEMORY_TM_0r | MMU | controlling TM and DCM for the 3 memories in pipe 0 |
| `0x0238013d` | MEMORY_TM_1r | MMU | controlling TM and DCM for the 3 memories in pipe 1 |
| `0x03180600` | IPV6_MIN_FRAG_SIZEr | IPIPE | Programmable Minimum IPv6 Fragment Size for DOS Attack Check. |
| `0x03180601` | DOS_CONTROLr | IPIPE | DOS (Denial of Service) Attack Control Register |
| `0x03180602` | DOS_CONTROL_2r | IPIPE | DOS (Denial of Service) Attack Control Register #2 |
| `0x03200600` | EGR_DBGr | EPIPE | Configuration Register for a Port. This is same for GE, 10GE, Higig Ports. |
| `0x03280601` | EGR_NIV_CONFIGr | EPIPE | Egress NIV Config Register. |
| `0x03280602` | EGR_SYS_RSVD_VIDr | EPIPE | VID to populate HG header when leaving real VID in the packet. |
| `0x03300000` | ASF_PORT_SPEEDr | MMU | ASF_PORT_SPEED |
| `0x03300020` | OP_PORT_CONFIG_CELLr | MMU | OP_PORT_CONFIG_CELL |
| `0x03300024` | OP_UC_PORT_CONFIG_CELLr | MMU | OP_UC_PORT_CONFIG_CELL |
| `0x03300028` | OP_PORT_CONFIG1_CELLr | MMU | OP_PORT_CONFIG1_CELL |
| `0x03300029` | OP_UC_PORT_CONFIG1_CELLr | MMU | OP_UC_PORT_CONFIG1_CELL |
| `0x0330002c` | OP_EX_PORT_CONFIG_SPID_0r | MMU | OP_EX_PORT_CONFIG_SPID_0 |
| `0x0330002d` | OP_EX_PORT_CONFIG_SPID_1r | MMU | OP_EX_PORT_CONFIG_SPID_1 |
| `0x03300030` | OP_EX_PORT_CONFIG_SPID_2r | MMU | OP_EX_PORT_CONFIG_SPID_2 |
| `0x03300032` | OP_EX_PORT_CONFIG_SPID_3r | MMU | OP_EX_PORT_CONFIG_SPID_3 |
| `0x03300034` | OP_EX_PORT_CONFIG_SPID_4r | MMU | OP_EX_PORT_CONFIG_SPID_4 |
| `0x03300035` | OP_EX_PORT_CONFIG_COS_MIN_0r | MMU | OP_EX_PORT_CONFIG_COS_MIN_0 |
| `0x03300036` | OP_EX_PORT_CONFIG_COS_MIN_1r | MMU | OP_EX_PORT_CONFIG_COS_MIN_1 |
| `0x03300037` | OP_EX_PORT_CONFIG_COS_MIN_2r | MMU | OP_EX_PORT_CONFIG_COS_MIN_2 |
| `0x03300038` | OP_PORT_LIMIT_COLOR_CELLr | MMU | OP_PORT_LIMIT_COLOR_CELL |
| `0x0330003c` | OP_UC_PORT_LIMIT_COLOR_CELLr | MMU | OP_UC_PORT_LIMIT_COLOR_CELL |
| `0x03300050` | OP_PORT_SHARED_COUNT_CELLr | MMU | OP_PORT_SHARED_COUNT_CELL |
| `0x03300054` | OP_UC_PORT_SHARED_COUNT_CELLr | MMU | OP_UC_PORT_SHARED_COUNT_CELL |
| `0x03300090` | OP_PORT_LIMIT_RESUME_COLOR_CELLr | MMU | OP_PORT_LIMIT_RESUME_COLOR_CELL |
| `0x03300094` | OP_UC_PORT_LIMIT_RESUME_COLOR_CELLr | MMU | OP_UC_PORT_LIMIT_RESUME_COLOR_CELL |
| `0x03300100` | OP_QUEUE_CONFIG_CELLr | MMU | OP_QUEUE_CONFIG_CELL |
| `0x03300140` | OP_QUEUE_CONFIG1_CELLr | MMU | OP_QUEUE_CONFIG1_CELL |
| `0x03300180` | OP_QUEUE_LIMIT_COLOR_CELLr | MMU | OP_QUEUE_LIMIT_COLOR_CELL |
| `0x03300200` | OP_QUEUE_RESET_OFFSET_CELLr | MMU | OP_QUEUE_RESET_OFFSET_CELL |
| `0x03300240` | OP_QUEUE_MIN_COUNT_CELLr | MMU | OP_QUEUE_MIN_COUNT_CELL |
| `0x03300280` | OP_UC_QUEUE_MIN_COUNT_CELLr | MMU | OP_UC_QUEUE_MIN_COUNT_CELL |
| `0x033002c0` | OP_QUEUE_SHARED_COUNT_CELLr | MMU | OP_QUEUE_SHARED_COUNT_CELL |
| `0x03300300` | OP_UC_QUEUE_SHARED_COUNT_CELLr | MMU | OP_UC_QUEUE_SHARED_COUNT_CELL |
| `0x03300340` | OP_QUEUE_TOTAL_COUNT_CELLr | MMU | OP_QUEUE_TOTAL_COUNT_CELL |
| `0x03300380` | OP_UC_QUEUE_TOTAL_COUNT_CELLr | MMU | OP_UC_QUEUE_TOTAL_COUNT_CELL |
| `0x033003c0` | OP_QUEUE_RESET_VALUE_CELLr | MMU | OP_QUEUE_RESET_VALUE_CELL |
| `0x03300400` | OP_UC_QUEUE_RESET_VALUE_CELLr | MMU | OP_UC_QUEUE_RESET_VALUE_CELL |
| `0x03300440` | OP_QUEUE_LIMIT_RESUME_COLOR_CELLr | MMU | OP_QUEUE_LIMIT_RESUME_COLOR_CELL |
| `0x03300800` | OP_EX_QUEUE_MIN_COUNT_CELLr | MMU | OP_EX_QUEUE_MIN_COUNT_CELL |
| `0x03300900` | OP_EX_QUEUE_SHARED_COUNT_CELLr | MMU | OP_EX_QUEUE_SHARED_COUNT_CELL |
| `0x03300a00` | OP_EX_QUEUE_TOTAL_COUNT_CELLr | MMU | OP_EX_QUEUE_TOTAL_COUNT_CELL |
| `0x03300b00` | OP_EX_QUEUE_RESET_VALUE_CELLr | MMU | OP_EX_QUEUE_RESET_VALUE_CELL |
| `0x03380004` | OP_BUFFER_SHARED_LIMIT_CELLr | MMU | OP_BUFFER_SHARED_LIMIT_CELL |
| `0x03380008` | OP_BUFFER_LIMIT_YELLOW_CELLr | MMU | OP_BUFFER_LIMIT_YELLOW_CELL |
| `0x0338000c` | OP_BUFFER_LIMIT_RED_CELLr | MMU | OP_BUFFER_LIMIT_RED_CELL |
| `0x03380010` | THDO_BYPASSr | MMU | THDO_BYPASS |
| `0x03380012` | OP_THR_CONFIGr | MMU | OP_THR_CONFIG |
| `0x03380013` | OP_THR_CONFIG_PLUSr | MMU | OP_THR_CONFIG_PLUS |
| `0x03380014` | OP_VOQ_PORT_CONFIGr | MMU | OP_VOQ_PORT_CONFIG |
| `0x03380015` | OP_VOQ_MOP1B_CONFIGr | MMU | OP_VOQ_MOP1B_CONFIG |
| `0x03380016` | THDO_UNICAST_DROP_EMIRROR_CNTr | MMU | THDO_UNICAST_DROP_EMIRROR_CNT |
| `0x03380018` | THDO_PARITY_ERROR_ADDRESSr | MMU | THDO_PARITY_ERROR_ADDRESS |
| `0x03380019` | THDO_PARITY_ERROR_STATUS_64r | MMU | THDO_PARITY_ERROR_STATUS |
| `0x0338001a` | THDO_DEBUG_TM_UC0r | MMU | THDO DEBUG_TM_UC0 |
| `0x0338001b` | THDO_DEBUG_TM_UC1r | MMU | THDO DEBUG_TM_UC1 |
| `0x0338001c` | THDO_DEBUG_TM_UCSP0r | MMU | THDO DEBUG_TM_UCSP0 |
| `0x0338001d` | THDO_DEBUG_TM_UCSP1r | MMU | THDO DEBUG_TM_UCSP1 |
| `0x0338001e` | THDO_DEBUG_DCM_PMr | MMU | THDO DCM and PCM REGISTER |
| `0x0338001f` | THDO_DEBUGr | MMU | THDO DEBUG REGISTER |
| `0x03380040` | OP_BUFFER_SHARED_COUNT_CELLr | MMU | OP_BUFFER_SHARED_COUNT_CELL |
| `0x03380044` | OP_BUFFER_TOTAL_COUNT_CELLr | MMU | OP_BUFFER_TOTAL_COUNT_CELL |
| `0x03380048` | OP_BUFFER_MAX_TOTAL_COUNT_CELLr | MMU | OP_BUFFER_MAX_TOTAL_COUNT_CELL |
| `0x03380060` | OP_PORT_DROP_STATE_CELL_BMP0_64r | MMU | OP_PORT_DROP_STATE_CELL_BMP0 |
| `0x03380064` | OP_PORT_DROP_STATE_CELL_BMP1_64r | MMU | OP_PORT_DROP_STATE_CELL_BMP1 |
| `0x03380068` | OP_UC_PORT_DROP_STATE_CELL_BMP0_64r | MMU | OP_UC_PORT_DROP_STATE_CELL_BMP0 |
| `0x0338006c` | OP_UC_PORT_DROP_STATE_CELL_BMP1_64r | MMU | OP_UC_PORT_DROP_STATE_CELL_BMP1 |
| `0x03380070` | THDO_INTEROP_CONFIGr | MMU | THDO_INTEROP_CONFIG |
| `0x03380071` | THDO_INTEROP_CONFIG_PLUSr | MMU | THDO_INTEROP_CONFIG_PLUS |
| `0x03380074` | OUTPUT_PORT_RX_ENABLE0_64r | MMU | OUTPUT_PORT_RX_ENABLE0 |
| `0x03380075` | OUTPUT_PORT_RX_ENABLE1_64r | MMU | OUTPUT_PORT_RX_ENABLE1 |
| `0x03380080` | OP_BUFFER_SHARED_LIMIT_RESUME_CELLr | MMU | OP_BUFFER_SHARED_LIMIT_RESUME_CELL |
| `0x03380084` | OP_BUFFER_LIMIT_RESUME_YELLOW_CELLr | MMU | OP_BUFFER_LIMIT_RESUME_YELLOW_CELL |
| `0x03380088` | OP_BUFFER_LIMIT_RESUME_RED_CELLr | MMU | OP_BUFFER_LIMIT_RESUME_RED_CELL |
| `0x033800a0` | OP_RESUME_OFFSET_COLOR_CELL_PROFILEr | MMU | OP_RESUME_OFFSET_COLOR_CELL_PROFILE |
| `0x04180600` | ING_NIV_CONFIGr | IPIPE | Inress NIV Config Register. |
| `0x04180608` | VLAN_XLATE_HASH_CONTROLr | IPIPE | VLAN_XLATE_HASH_CONTROL, FeatureSpecific-Ethernet |
| `0x04180620` | VFP_SLICE_CONTROLr | IPIPE | VFP_SLICE_CONTROL |
| `0x04180621` | VFP_KEY_CONTROLr | IPIPE | VFP_KEY_CONTROL |
| `0x04180622` | VFP_KEY_CONTROL_2r | IPIPE | VFP_KEY_CONTROL |
| `0x04180636` | VFP_SLICE_MAPr | IPIPE | VFP_SLICE_MAP |
| `0x04180640` | MPLS_ENTRY_HASH_CONTROLr | IPIPE | MPLS_ENTRY_HASH_CONTROL, FeatureSpecific-MPLS |
| `0x04180d00` | IP1_INTR_STATUSr | IPIPE | IP1 Interrupt Status |
| `0x04180d01` | IP1_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP1_INTR_STATUS |
| `0x04180d02` | VLAN_SUBNET_CAM_DBGCTRLr | IPIPE | VLAN_SUBNET_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x04180d03` | VLAN_SUBNET_CAM_BIST_STATUSr | IPIPE | VLAN_SUBNET_CAM_BIST_STATUS |
| `0x04180d04` | VLAN_SUBNET_CAM_BIST_CONFIGr | IPIPE | VLAN_SUBNET_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x04180d05` | VLAN_SUBNET_CAM_BIST_DBG_DATAr | IPIPE | VLAN_SUBNET_CAM_BIST_DBG_DATA |
| `0x04180d06` | VLAN_SUBNET_DATA_DBGCTRLr | IPIPE | VLAN_SUBNET_DATA_CONTROL, FeatureSpecific-Ethernet |
| `0x04180d07` | VLAN_PROTOCOL_DATA_DBGCTRLr | IPIPE | VLAN_PROTOCOL_DATA_CONTROL, FeatureSpecific-Ethernet |
| `0x04180d08` | VLAN_XLATE_DATA_DBGCTRL_0r | IPIPE | VLAN_XLATE_DATA_CONTROL_0, FeatureSpecific-Ethernet |
| `0x04180d09` | VLAN_XLATE_DATA_DBGCTRL_1r | IPIPE | VLAN_XLATE_DATA_CONTROL_1, FeatureSpecific-Ethernet |
| `0x04180d0a` | VLAN_XLATE_DATA_DBGCTRL_2r | IPIPE | VLAN_XLATE_DATA_CONTROL_2, FeatureSpecific-Ethernet |
| `0x04180d0b` | VLAN_XLATE_DATA_DBGCTRL_3r | IPIPE | VLAN_XLATE_DATA_CONTROL_3, FeatureSpecific-Ethernet |
| `0x04180d0c` | VLAN_XLATE_PARITY_CONTROLr | IPIPE | VLAN_XLATE_PARITY_CONTROL |
| `0x04180d0d` | VLAN_XLATE_PARITY_STATUS_INTR_0r | IPIPE | VLAN_XLATE_PARITY_STATUS_INTR_0 |
| `0x04180d0e` | VLAN_XLATE_PARITY_STATUS_INTR_1r | IPIPE | VLAN_XLATE_PARITY_STATUS_INTR_1 |
| `0x04180d0f` | VLAN_XLATE_PARITY_STATUS_NACK_0r | IPIPE | VLAN_XLATE_PARITY_STATUS_NACK_0 |
| `0x04180d10` | VLAN_XLATE_PARITY_STATUS_NACK_1r | IPIPE | VLAN_XLATE_PARITY_STATUS_NACK_1 |
| `0x04180d11` | VFP_POLICY_PARITY_CONTROLr | IPIPE | VFP_POLICY_PARITY_CONTROL |
| `0x04180d12` | VFP_POLICY_PARITY_STATUS_INTRr | IPIPE | VFP_POLICY_PARITY_STATUS_INTR |
| `0x04180d13` | VFP_POLICY_PARITY_STATUS_NACKr | IPIPE | VFP_POLICY_PARITY_STATUS_NACK |
| `0x04180d14` | VFP_CAM_BIST_STATUSr | IPIPE | VFP_CAM_BIST_STATUS |
| `0x04180d15` | VFP_CAM_BIST_CONTROLr | IPIPE | VFP_CAM_BIST_CONTROL |
| `0x04180d16` | VFP_CAM_CONTROL_SLICE_3_0r | IPIPE | VFP_CAM_CONTROL_SLICE_3_0 |
| `0x04180d17` | VFP_CAM_BIST_DBG_DATAr | IPIPE | VFP_CAM_BIST_DBG_DATA |
| `0x04180d18` | VFP_CAM_BIST_CONFIGr | IPIPE | VFP_CAM_DEBUG_SEND |
| `0x04180d19` | VFP_POLICY_TABLE_RAM_CONTROLr | IPIPE | VFP_POLICY_TABLE_RAM_CONTROL |
| `0x04180d1a` | VLAN_PROT_PARITY_CONTROLr | IPIPE | VLAN_PROT_PARITY_CONTROL |
| `0x04180d1b` | VLAN_PROT_PARITY_STATUS_INTRr | IPIPE | VLAN_PROT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x04180d1c` | VLAN_PROT_PARITY_STATUS_NACKr | IPIPE | VLAN_PROT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x04180d1d` | VLAN_SUBNET_PARITY_CONTROLr | IPIPE | VLAN_SUBNET_PARITY_CONTROL |
| `0x04180d1e` | VLAN_SUBNET_PARITY_STATUS_INTRr | IPIPE | VLAN_SUBNET_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x04180d1f` | VLAN_SUBNET_PARITY_STATUS_NACKr | IPIPE | VLAN_SUBNET_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x04180d20` | MPLS_ENTRY_DBGCTRL_0r | IPIPE | FeatureSpecific-Ethernet |
| `0x04180d21` | MPLS_ENTRY_DBGCTRL_1r | IPIPE | FeatureSpecific-Ethernet |
| `0x04180d22` | MPLS_ENTRY_DBGCTRL_2r | IPIPE | FeatureSpecific-Ethernet |
| `0x04180d23` | MPLS_ENTRY_DBGCTRL_3r | IPIPE | FeatureSpecific-Ethernet |
| `0x04180d24` | MPLS_ENTRY_PARITY_CONTROLr | IPIPE | MPLS_ENTRY_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x04180d25` | MPLS_ENTRY_PARITY_STATUS_INTR_0r | IPIPE | MPLS_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet |
| `0x04180d26` | MPLS_ENTRY_PARITY_STATUS_INTR_1r | IPIPE | MPLS_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet |
| `0x04180d27` | MPLS_ENTRY_PARITY_STATUS_NACK_0r | IPIPE | MPLS_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet |
| `0x04180d28` | MPLS_ENTRY_PARITY_STATUS_NACK_1r | IPIPE | MPLS_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet |
| `0x04280600` | EGR_TRILL_HEADER_ATTRIBUTESr | EPIPE | Egress Trill Heaader Attributes Register. |
| `0x04300010` | TOQ_EP_CREDITr | MMU | Egress cell request counter |
| `0x04300110` | UCQ_COS_EMPTY_REGr | MMU | UCQ_COS_EMPTY_REG |
| `0x04300120` | UCQ_EXTCOS1_EMPTY_REGr | MMU | UCQ_EXTCOS1_EMPTY_REG |
| `0x04380011` | TOQ_ERRINTRr | MMU | TOQ memory soft error interrupt |
| `0x04380012` | TOQ_CELLLINKERRPTRr | MMU | Captutred CELL LINK pointer address |
| `0x04380013` | TOQ_PKTLINKERRPTRr | MMU | Captutred PKT LINK pointer address |
| `0x04380014` | TOQ_CPQLINKERRPTRr | MMU | Captutred CPU Queue LINK pointer address |
| `0x04380015` | TOQ_UCQWPERRPTRr | MMU | Captutred UCQ Write Pointer address |
| `0x04380016` | TOQ_UCQRPERRPTRr | MMU | Captutred UCQ Read Pointer address |
| `0x04380021` | PKTLINKMEMDEBUGr | MMU | TM: tm registers. |
| `0x04380022` | CPQLINKMEMDEBUGr | MMU | CPQ Link Memory debug register |
| `0x04380023` | UCQWPMEMDEBUGr | MMU | UCQ WP Memory debug register |
| `0x04380024` | UCQRPMEMDEBUGr | MMU | UCQ RP Memory debug register |
| `0x04380140` | CPQ_COS_EMPTY_REGr | MMU | CPQ_COS_EMPTY_REG |
| `0x04380141` | TOQ_PORT_NOTEMPTY_PIPE0r | MMU | TOQ_PORT_NOTEMPTY_PIPE0 |
| `0x04380142` | TOQ_PORT_NOTEMPTY_PIPE1r | MMU | TOQ_PORT_NOTEMPTY_PIPE0 |
| `0x04380143` | TOQ_PORT_STATUS_PIPE0r | MMU | TOQ_PORT_STATUS_PIPE0 |
| `0x04380144` | TOQ_PORT_STATUS_PIPE1r | MMU | TOQ_PORT_STATUS_PIPE0 |
| `0x04380145` | TOQ_PORT_ACTIVATE_PIPE0r | MMU | TOQ_PORT_ACTIVATE_PIPE0 |
| `0x04380146` | TOQ_PORT_ACTIVATE_PIPE1r | MMU | TOQ_PORT_ACTIVATE_PIPE0 |
| `0x05100631` | ING_TRILL_ADJACENCYr | IPIPE | Ingress TRILL Adjacency Register. |
| `0x05180600` | ING_MPLS_TPIDr | IPIPE | Ingress Outer TPID register |
| `0x05180600` | ING_MPLS_TPID_0r | IPIPE | Ingress outer TPID matching register #0 |
| `0x05180601` | ING_MPLS_TPID_1r | IPIPE | Ingress outer TPID matching register #1 |
| `0x05180602` | ING_MPLS_TPID_2r | IPIPE | Ingress outer TPID matching register #2 |
| `0x05180603` | ING_MPLS_TPID_3r | IPIPE | Ingress outer TPID matching register #3 |
| `0x05180604` | ING_MPLS_INNER_TPIDr | IPIPE | Ingress inner TPID matching register |
| `0x0518060b` | VRF_MASKr | IPIPE | VRF_MASK |
| `0x0518060c` | RTAG7_HASH_FIELD_BMAP_1r | IPIPE | Rtag7 hashing field selection bitmap register1 |
| `0x0518060d` | RTAG7_HASH_FIELD_BMAP_2r | IPIPE | Rtag7 hashing field selection bitmap register2 |
| `0x0518060e` | RTAG7_HASH_FIELD_BMAP_3r | IPIPE | Rtag7 hashing field selection bitmap register3 |
| `0x0518060f` | RTAG7_HASH_FIELD_BMAP_5r | IPIPE | Rtag7 hashing field selection bitmap register5 |
| `0x05180610` | RTAG7_MPLS_L2_PAYLOAD_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for MPLS terminated tunnels with L2 payloads |
| `0x05180611` | RTAG7_MPLS_L3_PAYLOAD_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for MPLS terminated tunnels with L3 payloads |
| `0x05180612` | RTAG7_MPLS_OUTER_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for MPLS non-terminated packets |
| `0x05180613` | RTAG7_MIM_PAYLOAD_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap for MAC-in-MAC terminated tunnels |
| `0x05180614` | RTAG7_MIM_OUTER_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap for MAC-in-MAC non-terminated tunnels |
| `0x05180615` | RTAG7_HASH_SEED_Ar | IPIPE | Hash Seed for Rtag7 hashing |
| `0x05180616` | RTAG7_HASH_SEED_Br | IPIPE | Hash Seed for Rtag7 hashing |
| `0x05180617` | DROP_CONTROL_0r | IPIPE | Register for drop controls in the mpls stage |
| `0x05180618` | ING_L2_TUNNEL_PARSE_CONTROLr | IPIPE | Register for parser controls in L2 Tunnel Payload (Impls) parser. |
| `0x05180619` | RTAG7_HASH_CONTROL_2r | IPIPE | Hash control register 2 for Rtag7 hashing. |
| `0x0518061a` | RTAG7_HASH_CONTROL_3r | IPIPE | Hash control register 2 for Rtag7 hashing. |
| `0x0518061b` | RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_1r | IPIPE | Rtag7 IPV4 TCP/UDP Source-equals-Dest Field Bitmap control register. |
| `0x0518061c` | RTAG7_IPV4_TCP_UDP_HASH_FIELD_BMAP_2r | IPIPE | Rtag7 IPV4 TCP/UDP Field Bitmap control register. |
| `0x0518061d` | RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_1r | IPIPE | Rtag7 IPV6 TCP/UDP Source=Dest Field Bitmap control register. |
| `0x0518061e` | RTAG7_IPV6_TCP_UDP_HASH_FIELD_BMAP_2r | IPIPE | Rtag7 IPV6 TCP/UDP Field Bitmap control register. |
| `0x0518061f` | RTAG7_FCOE_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for FCoE packets. |
| `0x05180620` | RTAG7_TRILL_TUNNEL_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for TRILL tunnel packets. |
| `0x05180621` | RTAG7_TRILL_PAYLOAD_L2_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for TRILL tunnel packets. |
| `0x05180622` | RTAG7_TRILL_PAYLOAD_L3_HASH_FIELD_BMAPr | IPIPE | Rtag7 hashing field selection bitmap register for TRILL tunnel packets. |
| `0x05180640` | HASH_CONTROLr | IPIPE | Hash Control Register |
| `0x05180641` | MIM_DEFAULT_NETWORK_SVPr | IPIPE | Register for MIM Default Network SVP |
| `0x05180642` | TRILL_RBRIDGE_NICKNAME_SELECTr | IPIPE | Register to select source of TRILL RBridge nickname index |
| `0x05180d00` | VLAN_MEMORY_DBGCTRLr | IPIPE | VLAN_MEMORY_CONTROL |
| `0x05180d01` | VLAN_PARITY_CONTROLr | IPIPE | VLAN_PARITY_CONTROL |
| `0x05180d02` | VLAN_PARITY_STATUS_INTRr | IPIPE | VLAN_PARITY_STATUS_INTR |
| `0x05180d03` | VLAN_PARITY_STATUS_NACKr | IPIPE | VLAN_PARITY_STATUS_NACK |
| `0x05180d04` | VLAN_STG_PARITY_CONTROLr | IPIPE | VLAN_STG_PARITY_CONTROL |
| `0x05180d05` | VLAN_STG_PARITY_STATUS_INTRr | IPIPE | VLAN_STG_PARITY_STATUS_INTR |
| `0x05180d06` | VLAN_STG_PARITY_STATUS_NACKr | IPIPE | VLAN_STG_PARITY_STATUS_NACK |
| `0x05180d07` | MY_STATION_CAM_DBGCTRLr | IPIPE | MY_STATION_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d08` | MY_STATION_CAM_BIST_CONTROLr | IPIPE | MY_STATION_CAM_BIST_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d09` | MY_STATION_CAM_BIST_STATUSr | IPIPE | MY_STATION_CAM_BIST_STATUS, FeatureSpecific-Ethernet |
| `0x05180d0a` | MY_STATION_CAM_BIST_CONFIGr | IPIPE | MY_STATION_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x05180d0b` | MY_STATION_CAM_BIST_DBG_DATAr | IPIPE | MY_STATION_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet |
| `0x05180d0c` | SOURCE_VP_PARITY_CONTROLr | IPIPE | SOURCE_VP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d0d` | SOURCE_VP_PARITY_STATUS_INTRr | IPIPE | SOURCE_VP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d0e` | SOURCE_VP_PARITY_STATUS_NACKr | IPIPE | SOURCE_VP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d0f` | L3_IIF_PARITY_CONTROLr | IPIPE | L3_IIF_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d10` | L3_IIF_PARITY_STATUS_INTRr | IPIPE | L3_IIF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d11` | L3_IIF_PARITY_STATUS_NACKr | IPIPE | L3_IIF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d12` | VLAN_MPLS_PARITY_CONTROLr | IPIPE | VLAN_MPLS_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d13` | VLAN_MPLS_PARITY_STATUS_INTRr | IPIPE | VLAN_MPLS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d14` | VLAN_MPLS_PARITY_STATUS_NACKr | IPIPE | VLAN_MPLS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d15` | VFI_PARITY_CONTROLr | IPIPE | VFI_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d16` | VFI_PARITY_STATUS_INTRr | IPIPE | VFI_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d17` | VFI_PARITY_STATUS_NACKr | IPIPE | VFI_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d18` | VFI_1_PARITY_CONTROLr | IPIPE | VFI_1_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d19` | VFI_1_PARITY_STATUS_INTRr | IPIPE | VFI_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d1a` | VFI_1_PARITY_STATUS_NACKr | IPIPE | VFI_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d1b` | VRF_PARITY_CONTROLr | IPIPE | VRF_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d1c` | VRF_PARITY_STATUS_INTRr | IPIPE | VRF_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d1d` | VRF_PARITY_STATUS_NACKr | IPIPE | VRF_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05180d1e` | MPLS_MEMORY_DBGCTRL_0r | IPIPE | FeatureSpecific-Ethernet |
| `0x05180d1f` | MPLS_MEMORY_DBGCTRL_1r | IPIPE | FeatureSpecific-Ethernet |
| `0x05180d20` | MY_STATION_DATA_PARITY_CONTROLr | IPIPE | MY_STATION_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x05180d21` | MY_STATION_DATA_PARITY_STATUS_INTRr | IPIPE | MY_STATION_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x05180d22` | MY_STATION_DATA_PARITY_STATUS_NACKr | IPIPE | MY_STATION_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x05200604` | EGR_MODMAP_CTRLr | EPIPE | Module Mapping Control |
| `0x05200605` | EGR_SF_SRC_MODID_CHECKr | EPIPE | Module Mapping Control |
| `0x05280600` | EGR_TUNNEL_PIMDR1_CFG0r | EPIPE | For PIMSM-DR1 type of tunnel pkts, MS 4 bytes are specified here, so that they |
| `0x05280601` | EGR_TUNNEL_PIMDR1_CFG1r | EPIPE | For PIMSM-DR1 type of tunnel pkts, LS 4 bytes are specified here, so that they |
| `0x05280602` | EGR_TUNNEL_PIMDR2_CFG0r | EPIPE | For PIMSM-DR2 type of tunnel pkts, MS 4 bytes are specified here, so that they |
| `0x05280603` | EGR_TUNNEL_PIMDR2_CFG1r | EPIPE | For PIMSM-DR2 type of tunnel pkts, LS 4 bytes are specified here, so that they |
| `0x05280606` | EGR_MIM_ETHERTYPEr | EPIPE | MAC-in-MAC Ethertype Control Register |
| `0x05280700` | EGR_EHCPM_ECC_PARITY_CONTROLr | EPIPE | Control ecc/parity functions of EHCPM RAMS |
| `0x05280704` | EGR_EHCPM_RAM_CONTROL_STBYr | EPIPE | Control ecc functions of EHCPM RAMS |
| `0x05280d01` | EGR_MOD_MAP_PARITY_STATUS_INTRr | EPIPE | ECC interrupt status register for EGR_MOD_MAP memory |
| `0x05280d02` | EGR_MOD_MAP_PARITY_STATUS_NACKr | EPIPE | ECC nack status register for EGR_MOD_MAP memory |
| `0x05280d03` | EGR_INITBUF_ECC_STATUS_INTRr | EPIPE | ECC interrupt status register for INITBUF memory |
| `0x05300005` | DEQ_AGINGMASKr | MMU | Aging mask bitmap |
| `0x05380001` | DEQ_PKTHDRERRPTRr | MMU | Captutred PKT HDR pointer address |
| `0x05380002` | DEQ_MPBERRPTRr | MMU | Captutred CBP Header pointer address |
| `0x05380003` | DEQ_AGINGMASK_CPU_PORT_0r | MMU | CPU Port Aging mask bitmapim |
| `0x05380004` | DEQ_AGINGMASK_CPU_PORT_1r | MMU | CPU Port Aging mask bitmapim |
| `0x05380006` | DEQ_MEMDEBUG0r | MMU | Debug 0 |
| `0x05380007` | DEQ_MEMDEBUG1r | MMU | Debug 1 |
| `0x05380008` | PWR_WATCH_DOG_CONTROL_MBXr | MMU | Power watch dog control register |
| `0x05380009` | PWR_WATCH_DOG_STATUS_MBXr | MMU | Power watch dog status register |
| `0x0538000a` | PWR_WATCH_DOG_CONTROL_MBYr | MMU | Power watch dog control register |
| `0x0538000b` | PWR_WATCH_DOG_STATUS_MBYr | MMU | Power watch dog status register |
| `0x06180330` | PP_C0_PORT_A_ADDRr | IPIPE | PP_C0_PORT_A_ADDR |
| `0x06180331` | PP_C0_PORT_A_CMDr | IPIPE | PP_C0_PORT_A_CMD |
| `0x06180332` | PP_C0_PORT_A_DATA_0r | IPIPE | PP_C0_PORT_A_DATA_0 |
| `0x06180333` | PP_C0_PORT_A_DATA_1r | IPIPE | PP_C0_PORT_A_DATA_1 |
| `0x06180334` | PP_C0_PORT_A_DATA_2r | IPIPE | PP_C0_PORT_A_DATA_2 |
| `0x06180335` | PP_C0_PORT_A_DATA_3r | IPIPE | PP_C0_PORT_A_DATA_3 |
| `0x06180336` | PP_C0_PORT_B_ADDRr | IPIPE | PP_C0_PORT_B_ADDR |
| `0x06180337` | PP_C0_PORT_B_CMDr | IPIPE | PP_C0_PORT_B_CMD |
| `0x06180338` | PP_C0_PORT_B_DATA_0r | IPIPE | PP_C0_PORT_B_DATA_0 |
| `0x06180339` | PP_C0_PORT_B_DATA_1r | IPIPE | PP_C0_PORT_B_DATA_1 |
| `0x0618033a` | PP_C0_PORT_B_DATA_2r | IPIPE | PP_C0_PORT_B_DATA_2 |
| `0x0618033b` | PP_C0_PORT_B_DATA_3r | IPIPE | PP_C0_PORT_B_DATA_3 |
| `0x0618033c` | PP_C1_PORT_A_ADDRr | IPIPE | PP_C1_PORT_A_ADDR |
| `0x0618033d` | PP_C1_PORT_A_CMDr | IPIPE | PP_C1_PORT_A_CMD |
| `0x0618033e` | PP_C1_PORT_A_DATA_0r | IPIPE | PP_C1_PORT_A_DATA_0 |
| `0x0618033f` | PP_C1_PORT_A_DATA_1r | IPIPE | PP_C1_PORT_A_DATA_1 |
| `0x06180340` | PP_C1_PORT_A_DATA_2r | IPIPE | PP_C1_PORT_A_DATA_2 |
| `0x06180341` | PP_C1_PORT_A_DATA_3r | IPIPE | PP_C1_PORT_A_DATA_3 |
| `0x06180342` | PP_C1_PORT_B_ADDRr | IPIPE | PP_C1_PORT_B_ADDR |
| `0x06180343` | PP_C1_PORT_B_CMDr | IPIPE | PP_C1_PORT_B_CMD |
| `0x06180344` | PP_C1_PORT_B_DATA_0r | IPIPE | PP_C1_PORT_B_DATA_0 |
| `0x06180345` | PP_C1_PORT_B_DATA_1r | IPIPE | PP_C1_PORT_B_DATA_1 |
| `0x06180346` | PP_C1_PORT_B_DATA_2r | IPIPE | PP_C1_PORT_B_DATA_2 |
| `0x06180347` | PP_C1_PORT_B_DATA_3r | IPIPE | PP_C1_PORT_B_DATA_3 |
| `0x06180348` | PP_C2_PORT_A_ADDRr | IPIPE | PP_C2_PORT_A_ADDR |
| `0x06180349` | PP_C2_PORT_A_CMDr | IPIPE | PP_C2_PORT_A_CMD |
| `0x0618034a` | PP_C2_PORT_A_DATA_0r | IPIPE | PP_C2_PORT_A_DATA_0 |
| `0x0618034b` | PP_C2_PORT_A_DATA_1r | IPIPE | PP_C2_PORT_A_DATA_1 |
| `0x0618034c` | PP_C2_PORT_A_DATA_2r | IPIPE | PP_C2_PORT_A_DATA_2 |
| `0x0618034d` | PP_C2_PORT_A_DATA_3r | IPIPE | PP_C2_PORT_A_DATA_3 |
| `0x0618034e` | PP_C2_PORT_B_ADDRr | IPIPE | PP_C2_PORT_B_ADDR |
| `0x0618034f` | PP_C2_PORT_B_CMDr | IPIPE | PP_C2_PORT_B_CMD |
| `0x06180350` | PP_C2_PORT_B_DATA_0r | IPIPE | PP_C2_PORT_B_DATA_0 |
| `0x06180351` | PP_C2_PORT_B_DATA_1r | IPIPE | PP_C2_PORT_B_DATA_1 |
| `0x06180352` | PP_C2_PORT_B_DATA_2r | IPIPE | PP_C2_PORT_B_DATA_2 |
| `0x06180353` | PP_C2_PORT_B_DATA_3r | IPIPE | PP_C2_PORT_B_DATA_3 |
| `0x06180354` | PP_C3_PORT_A_ADDRr | IPIPE | PP_C3_PORT_A_ADDR |
| `0x06180355` | PP_C3_PORT_A_CMDr | IPIPE | PP_C3_PORT_A_CMD |
| `0x06180356` | PP_C3_PORT_A_DATA_0r | IPIPE | PP_C3_PORT_A_DATA_0 |
| `0x06180357` | PP_C3_PORT_A_DATA_1r | IPIPE | PP_C3_PORT_A_DATA_1 |
| `0x06180358` | PP_C3_PORT_A_DATA_2r | IPIPE | PP_C3_PORT_A_DATA_2 |
| `0x06180359` | PP_C3_PORT_A_DATA_3r | IPIPE | PP_C3_PORT_A_DATA_3 |
| `0x0618035a` | PP_C3_PORT_B_ADDRr | IPIPE | PP_C3_PORT_B_ADDR |
| `0x0618035b` | PP_C3_PORT_B_CMDr | IPIPE | PP_C3_PORT_B_CMD |
| `0x0618035c` | PP_C3_PORT_B_DATA_0r | IPIPE | PP_C3_PORT_B_DATA_0 |
| `0x0618035d` | PP_C3_PORT_B_DATA_1r | IPIPE | PP_C3_PORT_B_DATA_1 |
| `0x0618035e` | PP_C3_PORT_B_DATA_2r | IPIPE | PP_C3_PORT_B_DATA_2 |
| `0x0618035f` | PP_C3_PORT_B_DATA_3r | IPIPE | PP_C3_PORT_B_DATA_3 |
| `0x06180360` | PP_MODULE_CONTROLr | IPIPE | PP_MODULE_CONTROL |
| `0x06180361` | PP_PROGRAM_GOr | IPIPE | PP_PROGRAM_GO |
| `0x06180600` | L2_AUX_HASH_CONTROLr | IPIPE | L2_AUX_HASH_CONTROL |
| `0x06180617` | L2_LEARN_CONTROLr | IPIPE | L2_MOD_FIFO_RD_PTR, FeatureSpecific-Ethernet |
| `0x06180d00` | IP3_INTR_STATUSr | IPIPE | IP3 Interrupt Status |
| `0x06180d01` | IP3_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP2_INTR_STATUS |
| `0x06180d02` | L2_USER_ENTRY_CAM_DBGCTRLr | IPIPE | L2_USER_ENTRY_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d03` | L2_USER_ENTRY_CAM_BIST_DBGCTRLr | IPIPE | L2_USER_ENTRY_CAM_BIST_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d04` | L2_USER_ENTRY_CAM_BIST_STATUSr | IPIPE | L2_USER_ENTRY_CAM_BIST_STATUS |
| `0x06180d05` | L2_USER_ENTRY_CAM_BIST_CONFIGr | IPIPE | L2_USER_ENTRY_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x06180d06` | L2_USER_ENTRY_CAM_BIST_DBG_DATAr | IPIPE | L2_USER_ENTRY_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet |
| `0x06180d07` | L2_ENTRY_DA_DBGCTRL_0r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d08` | L2_ENTRY_DA_DBGCTRL_1r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d09` | L2_ENTRY_DA_DBGCTRL_2r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0a` | L2_ENTRY_DA_DBGCTRL_3r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0b` | L2_ENTRY_DA_DBGCTRL_4r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0c` | L2_ENTRY_DA_DBGCTRL_5r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0d` | L2_ENTRY_DA_DBGCTRL_6r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0e` | L2_ENTRY_DA_DBGCTRL_7r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d0f` | L2_ENTRY_DA_DBGCTRL_8r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d10` | L2_ENTRY_SA_DBGCTRL_0r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d11` | L2_ENTRY_SA_DBGCTRL_1r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d12` | L2_ENTRY_SA_DBGCTRL_2r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d13` | L2_ENTRY_SA_DBGCTRL_3r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d14` | L2_ENTRY_SA_DBGCTRL_4r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d15` | L2_ENTRY_SA_DBGCTRL_5r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d16` | L2_ENTRY_SA_DBGCTRL_6r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d17` | L2_ENTRY_SA_DBGCTRL_7r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d18` | L2_ENTRY_SA_DBGCTRL_8r | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d19` | L2_HIT_DBGCTRL_0r | IPIPE | L2_HIT_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d1a` | L2_HIT_DBGCTRL_1r | IPIPE | L2_HIT_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d1b` | L2_HIT_DBGCTRL_2r | IPIPE | L2_HIT_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d1c` | L2_HIT_DBGCTRL_3r | IPIPE | L2_HIT_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d1d` | L2_HIT_DBGCTRL_4r | IPIPE | L2_HIT_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d1e` | L2_ENTRY_PARITY_CONTROLr | IPIPE | L2_ENTRY_PARITY_CONTROL |
| `0x06180d1f` | L2_ENTRY_PARITY_STATUS_INTR_0r | IPIPE | L2_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet |
| `0x06180d20` | L2_ENTRY_PARITY_STATUS_INTR_1r | IPIPE | L2_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet |
| `0x06180d21` | L2_ENTRY_PARITY_STATUS_NACK_0r | IPIPE | L2_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet |
| `0x06180d22` | L2_ENTRY_PARITY_STATUS_NACK_1r | IPIPE | L2_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet |
| `0x06180d23` | L2_USER_ENTRY_DATA_PARITY_CONTROLr | IPIPE | L2_USER_ENTRY_DATA_PARITY_CONTROL |
| `0x06180d24` | L2_USER_ENTRY_DATA_PARITY_STATUS_INTRr | IPIPE | L2_USER_ENTRY_DATA_PARITY_STATUS_INTR |
| `0x06180d25` | L2_USER_ENTRY_DATA_PARITY_STATUS_NACKr | IPIPE | L2_USER_ENTRY_DATA_PARITY_STATUS_NACK |
| `0x06180d26` | L2_MOD_FIFO_PARITY_CONTROLr | IPIPE | L2_MOD_FIFO_PARITY_CONTROL |
| `0x06180d27` | L2_MOD_FIFO_PARITY_STATUS_INTRr | IPIPE | L2_MOD_FIFO_PARITY_STATUS_INTR |
| `0x06180d28` | L2_MOD_FIFO_PARITY_STATUS_NACKr | IPIPE | L2_MOD_FIFO_PARITY_STATUS_NACK |
| `0x06180d29` | L2_USER_ENTRY_DATA_DBGCTRLr | IPIPE | L2_USER_ENTRY_DATA_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d2a` | L2_MOD_FIFO_DBGCTRLr | IPIPE | FeatureSpecific-Ethernet |
| `0x06180d2b` | L2_MOD_FIFO_RD_PTRr | IPIPE | L2_MOD_FIFO_RD_PTR, FeatureSpecific-Ethernet |
| `0x06180d2c` | L2_MOD_FIFO_WR_PTRr | IPIPE | L2_MOD_FIFO_WR_PTR, FeatureSpecific-Ethernet |
| `0x06180d2d` | L2_MOD_FIFO_CNTr | IPIPE | L2_MOD_FIFO_CNT |
| `0x06180d2e` | IL2LU_PWR_WATCH_DOG_CONTROLr | IPIPE | IL2LU_PWR_WATCH_DOG_CONTROL, FeatureSpecific-Ethernet |
| `0x06180d2f` | IL2LU_PWR_WATCH_DOG_STATUSr | IPIPE | IL2LU_PWR_WATCH_DOG_STATUS, FeatureSpecific-Ethernet |
| `0x06200606` | EGR_SHAPING_CONTROLr | EPIPE | Specifies control fields Egress for the Shaping Counters. |
| `0x06200607` | EGR_COUNTER_CONTROLr | EPIPE | Specifies control fields Egress for the MMU Counters and Meters. |
| `0x06200609` | EGR_MTUr | EPIPE | Egress MTU Register. |
| `0x0620060b` | EGR_PORT_1r | EPIPE | Configuration Register for Egress port. |
| `0x06280601` | EGR_MC_CONTROL_1r | EPIPE | TBfilled |
| `0x06280602` | EGR_MC_CONTROL_2r | EPIPE | TBfilled |
| `0x06280605` | EGR_FLEXIBLE_IPV6_EXT_HDRr | EPIPE | Egress Programmable IPv6 extension header value. |
| `0x06280608` | EGR_PKT_MODS_CONTROLr | EPIPE | Controls and limits for packet modifications |
| `0x06280630` | EGR_QCN_CNM_LBMH_CONTROLr | EPIPE | Egress CNM Loopback Module Header Control Register. |
| `0x06280640` | EGR_NIV_ETHERTYPE_2r | EPIPE | Egress NIV Ethertype Control Register (second copy). |
| `0x06300000` | ESCONFIGr | MMU | Egress Scheduler Configuration Register |
| `0x06300020` | COSMASKr | MMU | Egress Scheduler Configuration Register |
| `0x06300050` | MINSPCONFIGr | MMU | Select a COS Queue as Strict Priority when schedule in MinBW modes |
| `0x06300100` | COSWEIGHTSr | MMU | Egress Scheduler Weight for each COS in WRR & WDRR modes |
| `0x06300140` | WERRCOUNTr | MMU | The count in the bucket controlling WERR/WRR |
| `0x06380021` | COSMASK_CPUr | MMU | Egress Scheduler Configuration Register |
| `0x06380022` | ES_TDM_CONFIGr | MMU | Egress TDM Configuration Register, defining Gb ports that share cpu slot |
| `0x06380051` | MINSPCONFIG_CPUr | MMU | Select a COS Queue as Strict Priority when schedule in MinBW modes |
| `0x06380080` | ES_QUEUE_TO_PRIOr | MMU | mapping of queues to priorities, note: stage 1 virtual queues numberered as queue 8 and 9 |
| `0x07280603` | EGR_WESP_PROTO_CONTROLr | EPIPE | Egress WESP Protocol Control Register. |
| `0x07280610` | EGR_QCN_CNTAG_ETHERTYPE_2r | EPIPE | QCN CNTAG Ethertype Control Register (second copy). |
| `0x07280611` | EGR_HBFC_CNTAG_ETHERTYPE_2r | EPIPE | HBFC CNTAG Ethertype Control Register (second copy). |
| `0x07380000` | CFAPCONFIGr | MMU | Controls the CFAP behavior |
| `0x07380001` | CFAPINITr | MMU | Controls CFAP Bank Init |
| `0x07380002` | CFAPFULLTHRESHOLDr | MMU | CFAPFULLSETPOINT: CFAP FULL Set Point define the threshold |
| `0x07380003` | CFAPREADPOINTERr | MMU | CFAPREADPOINTER: The current number of cells that are outstanding in the CBP memory. |
| `0x07380004` | CFAPOTPCONFIGr | MMU | Indicates the maximum CFAP Full threshold |
| `0x07380010` | CFAPBANKFULLr | MMU | CFAP Bank Full limit |
| `0x07380020` | CFAPBANK0STATUSr | MMU | Specifies the CFAP Bank 0 status |
| `0x07380021` | CFAPBANK1STATUSr | MMU | Specifies the CFAP Bank 1 status |
| `0x07380022` | CFAPBANK2STATUSr | MMU | Specifies the CFAP Bank 2 status |
| `0x07380023` | CFAPBANK3STATUSr | MMU | Specifies the CFAP Bank 3 status |
| `0x07380024` | CFAPBANK4STATUSr | MMU | Specifies the CFAP Bank 4 status |
| `0x07380025` | CFAPBANK5STATUSr | MMU | Specifies the CFAP Bank 5 status |
| `0x07380026` | CFAPBANK6STATUSr | MMU | Specifies the CFAP Bank 6 status |
| `0x07380027` | CFAPBANK7STATUSr | MMU | Specifies the CFAP Bank 7 status |
| `0x07380028` | CFAPBANK8STATUSr | MMU | Specifies the CFAP Bank 8 status |
| `0x07380029` | CFAPBANK9STATUSr | MMU | Specifies the CFAP Bank 9 status |
| `0x0738002a` | CFAPBANK10STATUSr | MMU | Specifies the CFAP Bank 10 status |
| `0x0738002b` | CFAPBANK11STATUSr | MMU | Specifies the CFAP Bank 11 status |
| `0x0738002c` | CFAPBANK12STATUSr | MMU | Specifies the CFAP Bank 12 status |
| `0x0738002d` | CFAPBANK13STATUSr | MMU | Specifies the CFAP Bank 13 status |
| `0x0738002e` | CFAPBANK14STATUSr | MMU | Specifies the CFAP Bank 14 status |
| `0x0738002f` | CFAPBANK15STATUSr | MMU | Specifies the CFAP Bank 15 status |
| `0x07380030` | CFAPBANKPARITYERRORr | MMU | CFAP Bank Parity Error Pointer |
| `0x07380040` | CFAPMEMDEBUGr | MMU | CCM: ccm registers. |
| `0x07380041` | CFAPDEBUGSCR0r | MMU | PTR: Scratch pad 0 pointer. |
| `0x07380042` | CFAPDEBUGSCR1r | MMU | PTR: Scratch pad 1 pointer. |
| `0x07380043` | CFAPDEBUGSCR2r | MMU | PTR: Scratch pad 2 pointer. |
| `0x07380044` | GMMEMWARMUPr | MMU | Controls Cell Data Buffer memory warm up timer |
| `0x07380045` | GMLOWBANKr | MMU | CFAP Bank 0 to 7 almost full flag set and reset limit in green mode |
| `0x07380046` | GMHIGHBANKr | MMU | CFAP Bank 8 to 15 almost full flag set and reset limit in green mode |
| `0x0828060b` | EFP_SLICE_CONTROLr | EPIPE | EFP_SLICE_CONTROL |
| `0x08280615` | EFP_METER_CONTROLr | EPIPE | EFP_METER_CONTROL |
| `0x08280616` | EFP_SLICE_MAPr | EPIPE | EFP_SLICE_MAP |
| `0x08280700` | EGR_PW_INIT_COUNTERS_PARITY_CONTROLr | EPIPE | EGR_PW_INIT_COUNTERS_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x08280703` | EFP_POLICY_PARITY_CONTROLr | EPIPE | EFP_POLICY_PARITY_CONTROL |
| `0x08280706` | EFP_METER_PARITY_CONTROLr | EPIPE | EFP_METER_PARITY_CONTROL |
| `0x0828070a` | EFP_CAM_BIST_CONTROLr | EPIPE | EFP_CAM_BIST_CONTROL |
| `0x0828070b` | EFP_RAM_CONTROLr | EPIPE | EFP_RAM_CONTROL |
| `0x0828070c` | EFP_RAM_CONTROL_1r | EPIPE | EFP_RAM_CONTROL1 |
| `0x0828070d` | EFP_TCAM_BLKSELr | EPIPE | EFP_TCAM_BLKSEL |
| `0x08280d01` | EGR_PW_INIT_COUNTERS_PARITY_STATUS_INTRr | EPIPE | EGR_PW_INIT_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x08280d02` | EGR_PW_INIT_COUNTERS_PARITY_STATUS_NACKr | EPIPE | EGR_PW_INIT_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x08280d04` | EFP_POLICY_PARITY_STATUS_INTRr | EPIPE | EFP_POLICY_PARITY_STATUS_INTR |
| `0x08280d05` | EFP_POLICY_PARITY_STATUS_NACKr | EPIPE | EFP_POLICY_PARITY_STATUS_NACK |
| `0x08280d07` | EFP_METER_PARITY_STATUS_INTRr | EPIPE | EFP_METER_PARITY_STATUS_INTR |
| `0x08280d08` | EFP_METER_PARITY_STATUS_NACKr | EPIPE | EFP_METER_PARITY_STATUS_NACK |
| `0x08280d09` | EFP_CAM_BIST_STATUSr | EPIPE | EFP_CAM_BIST_STATUS |
| `0x08280d0e` | EFP_CAM_BIST_DBG_DATAr | EPIPE | EFP_CAM_BIST_DBG_DATA |
| `0x08280d0f` | EFP_CAM_BIST_CONFIGr | EPIPE | EFP_CAM_BIST_CONFIG |
| `0x08380011` | CCPPARITYERRORPTRr | MMU | CCPPARITYERRORPTR: MMU CCP memory parity error pointer indicats. |
| `0x08380012` | CCPMEMDEBUGr | MMU | CCM: ccm registers. |
| `0x09180600` | L3_AUX_HASH_CONTROLr | IPIPE | L3_AUX_HASH_CONTROL |
| `0x09180d00` | L3_ENTRY_DBGCTRL0r | IPIPE | L3_ENTRY_CONTROL0, FeatureSpecific-Ethernet |
| `0x09180d01` | L3_ENTRY_DBGCTRL1r | IPIPE | L3_ENTRY_CONTROL1, FeatureSpecific-Ethernet |
| `0x09180d02` | L3_ENTRY_DBGCTRL2r | IPIPE | L3_ENTRY_CONTROL_2, FeatureSpecific-Ethernet |
| `0x09180d03` | L3_ENTRY_DBGCTRL3r | IPIPE | L3_ENTRY_CONTROL_3, FeatureSpecific-Ethernet |
| `0x09180d04` | L3_ENTRY_DBGCTRL4r | IPIPE | L3_ENTRY_CONTROL_4, FeatureSpecific-Ethernet |
| `0x09180d05` | L3_ENTRY_DBGCTRL5r | IPIPE | L3_ENTRY_CONTROL_5, FeatureSpecific-Ethernet |
| `0x09180d06` | L3_ENTRY_DBGCTRL6r | IPIPE | L3_ENTRY_CONTROL_6, FeatureSpecific-Ethernet |
| `0x09180d07` | L3_ENTRY_PARITY_CONTROLr | IPIPE | L3_ENTRY_PARITY_CONTROL |
| `0x09180d08` | L3_ENTRY_PARITY_STATUS_INTR_0r | IPIPE | L3_ENTRY_PARITY_STATUS_INTR_0, FeatureSpecific-Ethernet |
| `0x09180d09` | L3_ENTRY_PARITY_STATUS_INTR_1r | IPIPE | L3_ENTRY_PARITY_STATUS_INTR_1, FeatureSpecific-Ethernet |
| `0x09180d0a` | L3_ENTRY_PARITY_STATUS_NACK_0r | IPIPE | L3_ENTRY_PARITY_STATUS_NACK_0, FeatureSpecific-Ethernet |
| `0x09180d0b` | L3_ENTRY_PARITY_STATUS_NACK_1r | IPIPE | L3_ENTRY_PARITY_STATUS_NACK_1, FeatureSpecific-Ethernet |
| `0x09280203` | EGR_DROP_VECTOR_Xr | EPIPE | Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a bl |
| `0x09280403` | EGR_DROP_VECTOR_Yr | EPIPE | Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a bl |
| `0x09280c03` | EGR_DROP_VECTORr | EPIPE | Sticky drop vector register. On a per block (X or Y) basis. If a packet is dropped on a bl |
| `0x09300000` | BKPMETERINGCONFIG_64r | MMU | Back-pressure Metering Config |
| `0x09300001` | BKPMETERINGBUCKETr | MMU | BUCKET_COUNT: Pause Metering\'s Bucket Count for each ingress port |
| `0x09300003` | MTRI_IFGr | MMU | Specifies control fields for MTRI bucket |
| `0x09380010` | BKPMETERINGWARNSTATUS0_64r | MMU | PORT_BITMAP: Current Back Pressure Metering warning status, ports 0 - 32 (bits 0 - 32).  B |
| `0x09380012` | BKPMETERINGWARNSTATUS1_64r | MMU | PORT_BITMAP: Current Back Pressure Metering warning status, ports 33 - 65. |
| `0x09380014` | BKPMETERINGDISCSTATUS0_64r | MMU | PORT_BITMAP: Current Back Pressure Metering discard status, ports 0 - 32. |
| `0x09380016` | BKPMETERINGDISCSTATUS1_64r | MMU | PORT_BITMAP: Current Back Pressure Metering discard status, ports 33 - 65. |
| `0x0a180601` | L3_DEFIP_RPF_CONTROLr | IPIPE | L3_DEFIP_RPF_CONTROL |
| `0x0a180d00` | L3_DEFIP_CAM_DBGCTRL0r | IPIPE | L3_DEFIP_CAM_CONTROL0, FeatureSpecific-Ethernet |
| `0x0a180d01` | L3_DEFIP_CAM_DBGCTRL1r | IPIPE | L3_DEFIP_CAM_CONTROL1, FeatureSpecific-Ethernet |
| `0x0a180d02` | L3_DEFIP_CAM_DBGCTRL2r | IPIPE | L3_DEFIP_CAM_CONTROL2, FeatureSpecific-Ethernet |
| `0x0a180d03` | L3_DEFIP_CAM_DBGCTRL3r | IPIPE | L3_DEFIP_CAM_CONTROL3, FeatureSpecific-Ethernet |
| `0x0a180d04` | L3_DEFIP_CAM_BIST_DBGCTRLr | IPIPE | L3_DEFIP_CAM_BIST_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d05` | L3_DEFIP_CAM_BIST_STATUSr | IPIPE | L3_DEFIP_CAM_BIST_STATUS |
| `0x0a180d06` | L3_DEFIP_CAM_BIST_CONFIGr | IPIPE | L3_DEFIP_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x0a180d07` | L3_DEFIP_CAM_BIST_DBG_DATAr | IPIPE | L3_DEFIP_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet |
| `0x0a180d08` | L3_DEFIP_CAM_ENABLEr | IPIPE | L3_DEFIP_CAM_ENABLE |
| `0x0a180d09` | L3_DEFIP_DATA_DBGCTRL_0r | IPIPE | L3_DEFIP_DATA_CONTROL_0, FeatureSpecific-Ethernet |
| `0x0a180d0a` | L3_DEFIP_DATA_DBGCTRL_1r | IPIPE | L3_DEFIP_DATA_CONTROL_1, FeatureSpecific-Ethernet |
| `0x0a180d0b` | L3_DEFIP_128_DATA_DBGCTRLr | IPIPE | L3_DEFIP_128_DATA_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d0c` | L3_DEFIP_128_CAM_DBGCTRLr | IPIPE | L3_DEFIP_128_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d0d` | L3_DEFIP_128_CAM_ENABLEr | IPIPE | L3_DEFIP_128_CAM_ENABLE, FeatureSpecific-Ethernet |
| `0x0a180d0e` | L3_DEFIP_128_CAM_BIST_CONTROLr | IPIPE | L3_DEFIP_128_CAM_BIST_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d0f` | L3_DEFIP_128_CAM_BIST_STATUSr | IPIPE | L3_DEFIP_128_CAM_BIST_STATUS, FeatureSpecific-Ethernet |
| `0x0a180d10` | L3_DEFIP_128_CAM_BIST_CONFIGr | IPIPE | L3_DEFIP_128_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x0a180d11` | L3_DEFIP_128_CAM_BIST_DBG_DATAr | IPIPE | L3_DEFIP_128_CAM_BIST_DBG_DATA, FeatureSpecific-Ethernet |
| `0x0a180d12` | L3_DEFIP_DATA_PARITY_CONTROLr | IPIPE | L3_DEFIP_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d13` | L3_DEFIP_DATA_PARITY_STATUS_INTRr | IPIPE | L3_DEFIP_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0a180d14` | L3_DEFIP_DATA_PARITY_STATUS_NACKr | IPIPE | L3_DEFIP_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0a180d15` | L3_DEFIP_128_DATA_PARITY_CONTROLr | IPIPE | L3_DEFIP_128_DATA_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d16` | L3_DEFIP_128_DATA_PARITY_STATUS_INTRr | IPIPE | L3_DEFIP_128_DATA_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0a180d17` | L3_DEFIP_128_DATA_PARITY_STATUS_NACKr | IPIPE | L3_DEFIP_128_DATA_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0a180d23` | RTAG7_FLOW_BASED_HASH_PARITY_CONTROLr | IPIPE | RTAG7_FLOW_BASED_HASH_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0a180d24` | RTAG7_FLOW_BASED_HASH_PARITY_STATUS_INTRr | IPIPE | RTAG7_FLOW_BASED_HASH_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0a180d25` | RTAG7_FLOW_BASED_HASH_PARITY_STATUS_NACKr | IPIPE | RTAG7_FLOW_BASED_HASH_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0a200000` | TDBGC0r | EPIPE | Transmit debug counter #0 |
| `0x0a200001` | TDBGC1r | EPIPE | Transmit debug counter #1 |
| `0x0a200002` | TDBGC2r | EPIPE | Transmit debug counter #2 |
| `0x0a200003` | TDBGC3r | EPIPE | Transmit debug counter #3 |
| `0x0a200004` | TDBGC4r | EPIPE | Transmit debug counter #4 |
| `0x0a200005` | TDBGC5r | EPIPE | Transmit debug counter #5 |
| `0x0a200006` | TDBGC6r | EPIPE | Transmit debug counter #6 |
| `0x0a200007` | TDBGC7r | EPIPE | Transmit debug counter #7 |
| `0x0a200008` | TDBGC8r | EPIPE | Transmit debug counter #8 |
| `0x0a200009` | TDBGC9r | EPIPE | Transmit debug counter #9 |
| `0x0a20000a` | TDBGC10r | EPIPE | Transmit debug counter #10 |
| `0x0a20000b` | TDBGC11r | EPIPE | Transmit debug counter #11 |
| `0x0a20000c` | EGR_TRILL_TX_PKTSr | EPIPE | Number of packets transmitted from this port with TRILL ethertype. |
| `0x0a20000d` | EGR_TRILL_TX_ACCESS_PORT_TRILL_PKTS_DISCARDEDr | EPIPE | Number of TRILL frames dropped on an outgoing TRILL access port. |
| `0x0a20000e` | EGR_TRILL_TX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDEDr | EPIPE | Number of non-TRILL frames dropped on an outgoing TRILL network port. |
| `0x0a20000f` | TPCEr | EPIPE | Egress Purge and Cell Error Drop Counter |
| `0x0a2006c1` | EGR_LOGIC_TO_PHYS_MAPr | EPIPE |  |
| `0x0a280620` | TDBGC0_SELECTr | EPIPE | Transmit debug counter #0 Trigger Select Register |
| `0x0a280621` | TDBGC1_SELECTr | EPIPE | Transmit debug counter #1 Trigger Select Register |
| `0x0a280622` | TDBGC2_SELECTr | EPIPE | Transmit debug counter #2 Trigger Select Register |
| `0x0a280623` | TDBGC3_SELECTr | EPIPE | Transmit debug counter #3 Trigger Select Register |
| `0x0a280624` | TDBGC4_SELECTr | EPIPE | Transmit debug counter #4 Trigger Select Register |
| `0x0a280625` | TDBGC5_SELECTr | EPIPE | Transmit debug counter #5 Trigger Select Register |
| `0x0a280626` | TDBGC6_SELECTr | EPIPE | Transmit debug counter #6 Trigger Select Register |
| `0x0a280627` | TDBGC7_SELECTr | EPIPE | Transmit debug counter #7 Trigger Select Register |
| `0x0a280628` | TDBGC8_SELECTr | EPIPE | Transmit debug counter #8 Trigger Select Register |
| `0x0a280629` | TDBGC9_SELECTr | EPIPE | Transmit debug counter #9 Trigger Select Register |
| `0x0a28062a` | TDBGC10_SELECTr | EPIPE | Transmit debug counter #10 Trigger Select Register |
| `0x0a28062b` | TDBGC11_SELECTr | EPIPE | Transmit debug counter #11 Trigger Select Register |
| `0x0a2806c0` | EGR_Q_ENDr | EPIPE | Register starts an EQ Bus which is provided for later ECO reasons, if any. |
| `0x0a280700` | EGR_L1_CLK_RECOVERY_CTRLr | EPIPE | Select and Backup Select for top-level clock recovery |
| `0x0a280702` | EGR_INTR1_ENABLEr | EPIPE | Bitwise interrupt enable for EGR_INTR1_STATUS |
| `0x0a280703` | EGR_EDATABUF_PARITY_CONTROLr | EPIPE | Continuation of ram controls |
| `0x0a280704` | EGR_DATABUF_RAM_CONTROL_STBYr | EPIPE | Control register for stby bits of Edatabuf stage memories |
| `0x0a280705` | EGR_DATABUF_RAM_CONTROL_PMr | EPIPE | Control register for PM bits of Edatabuf stage memories |
| `0x0a280706` | EGR_DATABUF_RAM_CONTROL_DCMr | EPIPE | Control register for dcm bits of Edatabuf stage memories |
| `0x0a280707` | EGR_DATABUF_RAM_CONTROL_1r | EPIPE | Control register for tm bits of Edatabuf stage memories (also used for pw_init memory in E |
| `0x0a280708` | EGR_DATABUF_RAM_CONTROL_2r | EPIPE | Continuation of ram controls |
| `0x0a280721` | EGR_START_XMIT_AFTER_MOP_ARRIVALr | EPIPE | For a new packet, always wait for MOP reach Edatabuf before transmitting |
| `0x0a280d01` | EGR_INTR1_STATUSr | EPIPE | EP Interrupt 1  Status |
| `0x0a280d09` | EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for  memory |
| `0x0a280d0a` | EGR_PERQ_XMT_COUNTERS_BASE_ADDR_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for EGR_PERQ_XMT_COUNTERS_BASE_ADDR memory |
| `0x0a280d0b` | EGR_PERQ_XMT_COUNTERS_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for EGR_PERQ_COUNTER_TABLE memory |
| `0x0a280d0c` | EGR_PERQ_XMT_COUNTERS_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for EGR_PERQ_COUNTER_TABLE memory |
| `0x0a280d0e` | EGR_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for  memory |
| `0x0a280d0f` | EGR_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for  memory |
| `0x0a280d10` | EGR_VINTF_COUNTER_TABLE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d11` | EGR_VINTF_COUNTER_TABLE_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for memory |
| `0x0a280d12` | EGR_EFP_COUNTER_TABLE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d13` | EGR_EFP_COUNTER_TABLE_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for memory |
| `0x0a280d14` | EGR_STATS_COUNTER_TABLE_PARITY_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d15` | EGR_STATS_COUNTER_TABLE_PARITY_STATUS_NACKr | EPIPE | Parity nack status register for EGR_STATS_COUNTER_TABLE memory |
| `0x0a280d16` | EGR_XLP0_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d17` | EGR_XLP1_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d18` | EGR_XLP2_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d19` | EGR_XLP3_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1a` | EGR_XLP4_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1b` | EGR_XLP5_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1c` | EGR_XLP6_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1d` | EGR_XLP7_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1e` | EGR_XLP8_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d1f` | EGR_LBP_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a280d20` | EGR_CM_BUFFER_STATUS_INTRr | EPIPE | PARITY interrupt status register for memory |
| `0x0a300000` | MINBUCKETCONFIG_64r | MMU | MIN_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300100` | MINBUCKETr | MMU | MIN_BUCKET: Minimum rate bucket. Each unit represents 64k bits. |
| `0x0a300200` | MAXBUCKETCONFIG_64r | MMU | MAX_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300300` | MAXBUCKETr | MMU | MAX_BUCKET: Maximum rate bucket. Each unit represents 64k bits. |
| `0x0a300400` | S3_MINBUCKETCONFIG_64r | MMU | MIN_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300410` | S3_MINBUCKETr | MMU | MIN_BUCKET: Minimum rate bucket. |
| `0x0a300420` | S3_MAXBUCKETCONFIG_64r | MMU | MAX_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300430` | S3_MAXBUCKETr | MMU | MAX_BUCKET: Maximum rate bucket. |
| `0x0a300440` | S2_MINBUCKETCONFIG_64r | MMU | MIN_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300450` | S2_MINBUCKETr | MMU | MIN_BUCKET: Minimum rate bucket. |
| `0x0a300460` | S2_MAXBUCKETCONFIG_64r | MMU | MAX_THD: Threshold determines the size of Minimum Bucket. |
| `0x0a300470` | S2_MAXBUCKETr | MMU | MAX_BUCKET: Maximum rate bucket. |
| `0x0a3005c0` | SHAPING_CONTROLr | MMU | Shaping mode selection |
| `0x0a3005f0` | RESET_ON_EMPTY_MAX_64r | MMU | Enable Ethernet AV for MAX_BUCKET |
| `0x0a300750` | EGRMETERINGCONFIG_64r | MMU | THD_SEL: Threshold determines the size of Shaping Bucket. |
| `0x0a300790` | EGRMETERINGBUCKETr | MMU | BUCKET: Maximum rate bucket. Each unit represents 64k bits. |
| `0x0a3805d0` | EXT1_SHAPING_CONTROL_PORT1r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805d4` | EXT1_SHAPING_CONTROL_PORT2r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805d8` | EXT1_SHAPING_CONTROL_PORT3r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805dc` | EXT1_SHAPING_CONTROL_PORT4r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805e0` | EXT1_SHAPING_CONTROL_PORT34r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805e4` | EXT1_SHAPING_CONTROL_PORT35r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805e8` | EXT1_SHAPING_CONTROL_PORT36r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805ec` | EXT1_SHAPING_CONTROL_PORT37r | MMU | Selecting between byte mode and packet mode for shaping.  0 - byte mode, 1 - packet mode |
| `0x0a3805f2` | EXT1_RESET_ON_EMPTY_MAX_PORT1r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a3805f6` | EXT1_RESET_ON_EMPTY_MAX_PORT2r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a3805fa` | EXT1_RESET_ON_EMPTY_MAX_PORT3r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a3805fe` | EXT1_RESET_ON_EMPTY_MAX_PORT4r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a380600` | EXT1_RESET_ON_EMPTY_MAX_PORT34r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a380604` | EXT1_RESET_ON_EMPTY_MAX_PORT35r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a380608` | EXT1_RESET_ON_EMPTY_MAX_PORT36r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a38060c` | EXT1_RESET_ON_EMPTY_MAX_PORT37r | MMU | enable reset on empty ( reload the bucket to threshold |
| `0x0a380740` | TICK_MODEr | MMU | tick mode select |
| `0x0a3807e0` | MTRO_CONFIGr | MMU | AGGRESSIVE: Use aggressive setting for MTRO slot mechanism. |
| `0x0a3807f0` | EGRSHAPEPARITYERRORPTRr | MMU | MTRO Parity Error Pointer |
| `0x0b180600` | RTAG7_HASH_ECMPr | IPIPE | RTAG7 hash control register for ECMP |
| `0x0b180602` | CBL_ATTRIBUTEr | IPIPE | Class based station movement attribute register, index from PORT_CBL_TABLE |
| `0x0b180606` | RTAG7_HASH_LBIDr | IPIPE | RTAG7 hash control register for LBID selection |
| `0x0b180623` | RTAG7_HASH_TRILL_ECMPr | IPIPE | RTAG7 hash control register for TRILL ECMP. |
| `0x0b180d00` | IP2_INTR_STATUSr | IPIPE | IP2 Interrupt Status |
| `0x0b180d01` | IP2_INTR_STATUS_2r | IPIPE | IP2 Interrupt Status |
| `0x0b180d02` | IP2_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP2_INTR_STATUS |
| `0x0b180d03` | IP2_INTR_ENABLE_2r | IPIPE | Bitwise interrupt enable for IP2_INTR_STATUS_2 |
| `0x0b180d04` | RSEL1_RAM_DBGCTRLr | IPIPE | RSEL1_RAM_CONTROL |
| `0x0b180d05` | RSEL1_RAM_DBGCTRL_2r | IPIPE | RSEL1_RAM_CONTROL_2 |
| `0x0b180d06` | RSEL1_RAM_DBGCTRL_3r | IPIPE | RSEL1_RAM_CONTROL_3 |
| `0x0b180d07` | RSEL1_RAM_DBGCTRL_4r | IPIPE | RSEL1_RAM_CONTROL_4 |
| `0x0b180d08` | ING_DVP_TABLE_PARITY_CONTROLr | IPIPE | ING_DVP_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d09` | ING_DVP_TABLE_PARITY_STATUS_INTRr | IPIPE | ING_DVP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d0a` | ING_DVP_TABLE_PARITY_STATUS_NACKr | IPIPE | ING_DVP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d0b` | INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROLr | IPIPE | INITIAL_ING_L3_NEXT_HOP_PARITY_CONTROL |
| `0x0b180d0c` | INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_INTRr | IPIPE | INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d0d` | INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_NACKr | IPIPE | INITIAL_ING_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d0e` | INITIAL_L3_ECMP_GROUP_PARITY_CONTROLr | IPIPE | INITIAL_L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d0f` | INITIAL_L3_ECMP_GROUP_PARITY_STATUS_INTRr | IPIPE | INITIAL_L3_ECMP_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d10` | INITIAL_L3_ECMP_GROUP_PARITY_STATUS_NACKr | IPIPE | INITIAL_L3_ECMP_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d11` | INITIAL_L3_ECMP_PARITY_CONTROLr | IPIPE | INITIAL_L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d12` | INITIAL_L3_ECMP_PARITY_STATUS_INTRr | IPIPE | INITIAL_L3_ECMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d13` | INITIAL_L3_ECMP_PARITY_STATUS_NACKr | IPIPE | INITIAL_L3_ECMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d14` | INITIAL_PROT_NHI_TABLE_PARITY_CONTROLr | IPIPE | INITIAL_PROT_NHI_TABLE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d15` | INITIAL_PROT_NHI_TABLE_PARITY_STATUS_INTRr | IPIPE | INITIAL_PROT_NHI_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d16` | INITIAL_PROT_NHI_TABLE_PARITY_STATUS_NACKr | IPIPE | INITIAL_PROT_NHI_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d17` | PORT_CBL_TABLE_PARITY_CONTROLr | IPIPE | PORT_CBL_TABLE_PARITY_CONTROL |
| `0x0b180d18` | PORT_CBL_TABLE_PARITY_STATUS_INTRr | IPIPE | PORT_CBL_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d19` | PORT_CBL_TABLE_PARITY_STATUS_NACKr | IPIPE | PORT_CBL_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d1a` | PORT_CBL_TABLE_MODBASE_PARITY_CONTROLr | IPIPE | PORT_CBL_TABLE_MODBASE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d1b` | PORT_CBL_TABLE_MODBASE_PARITY_STATUS_INTRr | IPIPE | PORT_CBL_TABLE_MODBASE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d1c` | PORT_CBL_TABLE_MODBASE_PARITY_STATUS_NACKr | IPIPE | PORT_CBL_TABLE_MODBASE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d1d` | L3_IPMC_1_PARITY_CONTROLr | IPIPE | L3_IPMC_1_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d1e` | L3_IPMC_1_PARITY_STATUS_INTRr | IPIPE | L3_IPMC_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d1f` | L3_IPMC_1_PARITY_STATUS_NACKr | IPIPE | L3_IPMC_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d20` | MA_INDEX_PARITY_CONTROLr | IPIPE | MA_INDEX_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d21` | MA_INDEX_PARITY_STATUS_INTRr | IPIPE | MA_INDEX_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d22` | MA_INDEX_PARITY_STATUS_NACKr | IPIPE | MA_INDEX_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d23` | RMEP_PARITY_CONTROLr | IPIPE | RMEP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d24` | RMEP_PARITY_STATUS_INTRr | IPIPE | RMEP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d25` | RMEP_PARITY_STATUS_NACKr | IPIPE | RMEP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d26` | MAID_REDUCTION_PARITY_CONTROLr | IPIPE | MAID_REDUCTION_PARITY_CONTROL |
| `0x0b180d27` | MAID_REDUCTION_PARITY_STATUS_INTRr | IPIPE | MAID_REDUCTION_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d28` | MAID_REDUCTION_PARITY_STATUS_NACKr | IPIPE | MAID_REDUCTION_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d29` | MA_STATE_PARITY_CONTROLr | IPIPE | MA_STATE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0b180d2a` | MA_STATE_PARITY_STATUS_INTRr | IPIPE | MA_STATE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0b180d2b` | MA_STATE_PARITY_STATUS_NACKr | IPIPE | MA_STATE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0b180d2c` | CCM_READ_CONTROLr | IPIPE | No information |
| `0x0b180d2d` | CCM_INTERRUPT_CONTROLr | IPIPE | No information |
| `0x0b280700` | EGR_SBS_CONTROLr | EPIPE | EP sbs control reg to select the pipe for acc_type 6 regs and mems |
| `0x0c100602` | STORM_CONTROL_METER_CONFIGr | IPIPE | Per-port configuration and enables for storm control meters |
| `0x0c10060a` | FP_METER_CONTROLr | IPIPE | FP_METER_CONTROL |
| `0x0c180601` | STORM_CONTROL_METER_MAPPINGr | IPIPE | Storm Meter Controls - each field select one of four storm meters to use for the given pac |
| `0x0c180603` | CPU_CONTROL_1r | IPIPE | Control Register for Packets sent to the CPU |
| `0x0c180604` | CPU_CONTROL_Mr | IPIPE | Control Register for Packets sent to the CPU due to MPLS errors |
| `0x0c180606` | ING_MISC_CONFIG2r | IPIPE | Ingress misc config register #2 |
| `0x0c180607` | FP_SLICE_INDEX_CONTROLr | IPIPE | Selects Index for FP Port Field Select Table, FeatureSpecific-FP |
| `0x0c180608` | MC_CONTROL_4r | IPIPE | Multicast Control Register4 |
| `0x0c180609` | MC_CONTROL_5r | IPIPE | Multicast Control Register5 |
| `0x0c18060b` | CPU_CONTROL_0r | IPIPE | Control Register for Packets sent to the CPU |
| `0x0c18060c` | PRIORITY_CONTROLr | IPIPE | Register that controls the generation of various priorities |
| `0x0c180620` | PROTOCOL_PKT_CONTROLr | IPIPE | Protocol Packet Control Register |
| `0x0c180660` | IGMP_MLD_PKT_CONTROLr | IPIPE | IGMP/MLD Control Register |
| `0x0c1806a0` | TRILL_DROP_CONTROLr | IPIPE | . |
| `0x0c180d00` | SW1_RAM_DBGCTRLr | IPIPE | SW1_RAM_CONTROL |
| `0x0c180d01` | SW1_RAM_DBGCTRL_2r | IPIPE | SW1_RAM_CONTROL_2 |
| `0x0c180d02` | FP_FIELD_SEL_PARITY_CONTROLr | IPIPE | FP_FIELD_SEL_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0c180d03` | FP_FIELD_SEL_PARITY_STATUS_INTRr | IPIPE | FP_FIELD_SEL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d04` | FP_FIELD_SEL_PARITY_STATUS_NACKr | IPIPE | FP_FIELD_SEL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c180d05` | TTL_FN_PARITY_CONTROLr | IPIPE | TTL_FN_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0c180d06` | TTL_FN_PARITY_STATUS_INTRr | IPIPE | TTL_FN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d07` | TTL_FN_PARITY_STATUS_NACKr | IPIPE | TTL_FN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c180d08` | TOS_FN_PARITY_CONTROLr | IPIPE | TOS_FN_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0c180d09` | TOS_FN_PARITY_STATUS_INTRr | IPIPE | TOS_FN_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d0a` | TOS_FN_PARITY_STATUS_NACKr | IPIPE | TOS_FN_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c180d0b` | ING_PRI_CNG_MAP_PARITY_CONTROLr | IPIPE | ING_PRI_CNG_MAP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0c180d0c` | ING_PRI_CNG_MAP_PARITY_STATUS_INTRr | IPIPE | ING_PRI_CNG_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d0d` | ING_PRI_CNG_MAP_PARITY_STATUS_NACKr | IPIPE | ING_PRI_CNG_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c180d0e` | ING_UNTAGGED_PHB_PARITY_CONTROLr | IPIPE | ING_UNTAGGED_PHB_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0c180d0f` | ING_UNTAGGED_PHB_PARITY_STATUS_INTRr | IPIPE | ING_UNTAGGED_PHB_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d10` | ING_UNTAGGED_PHB_PARITY_STATUS_NACKr | IPIPE | ING_UNTAGGED_PHB_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c180d11` | DSCP_TABLE_PARITY_CONTROLr | IPIPE | DSCP_TABLE_PARITY_CONTROL |
| `0x0c180d12` | DSCP_TABLE_PARITY_STATUS_INTRr | IPIPE | DSCP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0c180d13` | DSCP_TABLE_PARITY_STATUS_NACKr | IPIPE | DSCP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0c380000` | MISCCONFIGr | MMU | Controls various functions in the MMU |
| `0x0c380001` | MEM_FAIL_INT_ENr | MMU | Memory Fail Interrupt Enable |
| `0x0c380002` | MEM_FAIL_INT_STATr | MMU | Memory Fail Interrupt Status |
| `0x0c380003` | MEM_FAIL_INT_CTRr | MMU | Memory Fail Interrupt Counter |
| `0x0c380004` | ECC_SINGLE_BIT_ERRORSr | MMU | Single bit (correctable) errors observed in ECC protected memories |
| `0x0c380005` | START_BY_START_ERROR0_64r | MMU | Start by start error detected by admission control |
| `0x0c380006` | START_BY_START_ERROR1_64r | MMU | Start by start error detected by admission control |
| `0x0c380100` | MMU_TO_LOGIC_MAPr | MMU |  |
| `0x0c380200` | MMU_TO_PHYS_MAPr | MMU |  |
| `0x0d100605` | IFP_GM_LOGIC_TO_PHYS_MAPr | IPIPE |  |
| `0x0d180601` | FP_SLICE_ENABLEr | IPIPE | FP_SLICE_ENABLE |
| `0x0d180603` | FP_SLICE_METER_MAP_ENABLEr | IPIPE | FP_SLICE_METER_MAP_ENABLE |
| `0x0d180604` | FP_FORCE_FORWARDING_FIELDr | IPIPE | FP_FORCE_FORWARDING_FIELD |
| `0x0d180d00` | FP_CAM_BIST_STATUSr | IPIPE | FP_CAM_BIST_STATUS |
| `0x0d180d01` | FP_CAM_DEBUG_CONTROLr | IPIPE | FP_CAM_DEBUG_CONTROL, FeatureSpecific-FP |
| `0x0d180d02` | FP_CAM_CONTROL_SLICE_3_0r | IPIPE | FP_CAM_CONTROL_SLICE_3_0, FeatureSpecific-FP |
| `0x0d180d03` | FP_CAM_CONTROL_SLICE_9_4r | IPIPE | FP_CAM_CONTROL_SLICE_9_4, FeatureSpecific-FP |
| `0x0d180d04` | FP_CAM_DEBUG_DATAr | IPIPE | FP_CAM_DEBUG_DATA, FeatureSpecific-FP |
| `0x0d180d05` | FP_GLOBAL_MASK_CAM_CONTROL_SLICE_3_0r | IPIPE | FP_GLOBAL_MASK_CAM_CONTROL_SLICE_3_0, FeatureSpecific-FP |
| `0x0d180d06` | FP_GLOBAL_MASK_CAM_CONTROL_SLICE_9_4r | IPIPE | FP_GLOBAL_MASK_CAM_CONTROL_SLICE_9_4, FeatureSpecific-FP |
| `0x0d180d07` | FP_CAM_DEBUG_SENDr | IPIPE | FP_CAM_DEBUG_SEND |
| `0x0d180d08` | FP_CAM_BIST_ENABLE_LOWERr | IPIPE | FP_CAM_BIST_ENABLE_LOWER |
| `0x0d180d09` | FP_POLICY_TM_UPPERr | IPIPE | FP_POLICY_TM_UPPER |
| `0x0d180d0a` | FP_POLICY_TM_LOWERr | IPIPE | FP_POLICY_TM_LOWER |
| `0x0d180d0b` | FP_POLICY_PMr | IPIPE | FP_POLICY_PM |
| `0x0d180d0c` | IFP_POLICY_PARITY_CONTROLr | IPIPE | IFP_POLICY_PARITY_CONTROL |
| `0x0d180d0d` | IFP_POLICY_PARITY_STATUS_INTRr | IPIPE | IFP_POLICY_PARITY_STATUS_INTR |
| `0x0d180d0e` | IFP_POLICY_PARITY_STATUS_NACKr | IPIPE | IFP_POLICY_PARITY_STATUS_NACK |
| `0x0d180d0f` | IFP_METER_PARITY_CONTROLr | IPIPE | IFP_METER_PARITY_CONTROL |
| `0x0d180d10` | IFP_METER_PARITY_STATUS_INTRr | IPIPE | IFP_METER_PARITY_STATUS_INTR |
| `0x0d180d11` | IFP_METER_PARITY_STATUS_NACKr | IPIPE | IFP_METER_PARITY_STATUS_NACK |
| `0x0d180d12` | IFP_COUNTER_PARITY_CONTROLr | IPIPE | IFP_COUNTER_PARITY_CONTROL |
| `0x0d180d13` | IFP_COUNTER_PARITY_STATUS_INTRr | IPIPE | IFP_COUNTER_PARITY_STATUS_INTR |
| `0x0d180d14` | IFP_COUNTER_PARITY_STATUS_NACKr | IPIPE | IFP_COUNTER_PARITY_STATUS_NACK |
| `0x0d180d15` | IFP_STORM_CONTROL_PARITY_CONTROLr | IPIPE | IFP_STORM_CONTROL_PARITY_CONTROL |
| `0x0d180d16` | IFP_STORM_CONTROL_PARITY_STATUS_INTRr | IPIPE | IFP_STORM_CONTROL_PARITY_STATUS_INTR |
| `0x0d180d17` | IFP_STORM_CONTROL_PARITY_STATUS_NACKr | IPIPE | IFP_STORM_CONTROL_PARITY_STATUS_NACK |
| `0x0d180d18` | IFP_ING_DVP_2_CONTROLr | IPIPE | IFP_ING_DVP_2_CONTROL |
| `0x0d180d19` | IFP_ING_DVP_2_PARITY_CONTROLr | IPIPE | IFP_ING_DVP_2_PARITY_CONTROL |
| `0x0d180d1a` | IFP_ING_DVP_2_PARITY_STATUS_INTRr | IPIPE | IFP_ING_DVP_2_PARITY_STATUS_INTR |
| `0x0d180d1b` | IFP_ING_DVP_2_PARITY_STATUS_NACKr | IPIPE | IFP_ING_DVP_2_PARITY_STATUS_NACK |
| `0x0d180d1c` | IFP_METER_MUX_DATA_STAGING_PARITY_CONTROLr | IPIPE | IFP_METER_MUX_DATA_STAGING_PARITY_CONTROL |
| `0x0d180d1d` | IFP_METER_MUX_DATA_STAGING_PARITY_STATUS_INTRr | IPIPE | IFP_METER_MUX_DATA_STAGING_PARITY_STATUS_INTR |
| `0x0d180d1e` | IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROLr | IPIPE | IFP_COUNTER_MUX_DATA_STAGING_PARITY_CONTROL |
| `0x0d180d1f` | IFP_COUNTER_MUX_DATA_STAGING_PARITY_STATUS_INTRr | IPIPE | IFP_COUNTER_MUX_DATA_STAGING_PARITY_STATUS_INTR |
| `0x0d180d20` | FP_TCAM_BLK_SELr | IPIPE | FP_TCAM_BLK_SEL, FeatureSpecific-FP |
| `0x0d180d21` | FP_GM_TCAM_BLK_SELr | IPIPE | FP_GM_TCAM_BLK_SEL, FeatureSpecific-FP |
| `0x0d180d22` | IP4_INTR_STATUSr | IPIPE | IP4 Interrupt Status |
| `0x0d180d23` | IP4_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP4_INTR_STATUS |
| `0x0d180d24` | IFP_PWR_WATCH_DOG_CONTROLr | IPIPE | Power watch dog control register |
| `0x0d180d25` | IFP_PWR_WATCH_DOG_STATUSr | IPIPE | Power watch dog status register |
| `0x0d180d26` | FP_METER_TABLE_TMr | IPIPE | FP_METER_TABLE_TM |
| `0x0d380000` | PKTAGINGTIMERr | MMU | DURATIONSELECT: 13 bits aging interval duration select registers. |
| `0x0d380001` | PKTAGINGLIMIT0r | MMU | Initial PRI limit aging values, reg 0 |
| `0x0d380002` | PKTAGINGLIMIT1r | MMU | Initial PRI limit aging values, reg 1 |
| `0x0d380003` | DEBUG0r | MMU | Debug 0 |
| `0x0d380004` | DEBUG1r | MMU | Debug 1 |
| `0x0d380005` | PERR_STATr | MMU | Parity error status |
| `0x0d380006` | PERR_PTR_CTRr | MMU | CTR parity error pointer |
| `0x0d380007` | PERR_PTR_EXPr | MMU | EXP parity error pointer |
| `0x0e180600` | FP_ECMP_HASH_CONTROLr | IPIPE | Hash Key controls for when FP iniates and ECMP Route |
| `0x0e180610` | RTAG7_HASH_TRUNKr | IPIPE | RTAG7 hash control register for trunking |
| `0x0e180d00` | RSEL2_RAM_DBGCTRLr | IPIPE | RSEL2_RAM_CONTROL |
| `0x0e180d01` | RSEL2_RAM_CONTROL_2r | IPIPE | RSEL2_RAM_CONTROL_2 |
| `0x0e180d02` | RSEL2_RAM_CONTROL_3r | IPIPE | RSEL2_RAM_CONTROL_3 |
| `0x0e180d03` | ING_L3_NEXT_HOP_PARITY_CONTROLr | IPIPE | ING_L3_NEXT_HOP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d04` | ING_L3_NEXT_HOP_PARITY_STATUS_INTRr | IPIPE | ING_L3_NEXT_HOP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d05` | ING_L3_NEXT_HOP_PARITY_STATUS_NACKr | IPIPE | ING_L3_NEXT_HOP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d06` | L2MC_PARITY_CONTROLr | IPIPE | L2MC_PARITY_CONTROL |
| `0x0e180d07` | L2MC_PARITY_STATUS_INTRr | IPIPE | L2MC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d08` | L2MC_PARITY_STATUS_NACKr | IPIPE | L2MC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d09` | L3_IPMC_PARITY_CONTROLr | IPIPE | L3_IPMC_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d0a` | L3_IPMC_PARITY_STATUS_INTRr | IPIPE | L3_IPMC_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d0b` | L3_IPMC_PARITY_STATUS_NACKr | IPIPE | L3_IPMC_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d0c` | L3_IPMC_REMAP_PARITY_CONTROLr | IPIPE | L3_IPMC_REMAP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d0d` | L3_IPMC_REMAP_PARITY_STATUS_INTRr | IPIPE | L3_IPMC_REMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d0e` | L3_IPMC_REMAP_PARITY_STATUS_NACKr | IPIPE | L3_IPMC_REMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d0f` | L3_ECMP_GROUP_PARITY_CONTROLr | IPIPE | L3_ECMP_GROUP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d10` | L3_ECMP_GROUP_PARITY_STATUS_INTRr | IPIPE | L3_ECMP_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d11` | L3_ECMP_GROUP_PARITY_STATUS_NACKr | IPIPE | L3_ECMP_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d12` | L3_ECMP_PARITY_CONTROLr | IPIPE | L3_ECMP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d13` | L3_ECMP_PARITY_STATUS_INTRr | IPIPE | L3_ECMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d14` | L3_ECMP_PARITY_STATUS_NACKr | IPIPE | L3_ECMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d15` | IFP_REDIRECTION_PROFILE_PARITY_CONTROLr | IPIPE | IFP_REDIRECTION_PROFILE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d16` | IFP_REDIRECTION_PROFILE_PARITY_STATUS_INTRr | IPIPE | IFP_REDIRECTION_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d17` | IFP_REDIRECTION_PROFILE_PARITY_STATUS_NACKr | IPIPE | IFP_REDIRECTION_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d18` | ICONTROL_OPCODE_BITMAP_PARITY_CONTROLr | IPIPE | ICONTROL_OPCODE_BITMAP_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d19` | ICONTROL_OPCODE_BITMAP_PARITY_STATUS_INTRr | IPIPE | ICONTROL_OPCODE_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d1a` | ICONTROL_OPCODE_BITMAP_PARITY_STATUS_NACKr | IPIPE | ICONTROL_OPCODE_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d1b` | EGR_MASK_MODBASE_PARITY_CONTROLr | IPIPE | EGR_MASK_MODBASE_PARITY_CONTROL, FeatureSpecific-Ethernet |
| `0x0e180d1c` | EGR_MASK_MODBASE_PARITY_STATUS_INTRr | IPIPE | EGR_MASK_MODBASE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d1d` | EGR_MASK_MODBASE_PARITY_STATUS_NACKr | IPIPE | EGR_MASK_MODBASE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e180d1e` | TRUNK_GROUP_PARITY_CONTROLr | IPIPE | Parity Control for TRUNK_GROUP table, FeatureSpecific-Ethernet |
| `0x0e180d1f` | TRUNK_GROUP_PARITY_STATUS_INTRr | IPIPE | TRUNK_GROUP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0e180d20` | TRUNK_GROUP_PARITY_STATUS_NACKr | IPIPE | TRUNK_GROUP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0e380029` | CELLCHKMEMDEBUGr | MMU | TM: tm registers. |
| `0x0e38002b` | PKTHDRMEMDEBUGr | MMU | TM_B: tm registers. |
| `0x0e380100` | DDP_C0_PORT_A_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380101` | DDP_C0_PORT_C_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380102` | DDP_C0_PORT_AC_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e380103` | DDP_C0_PORT_AC_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380104` | DDP_C0_PORT_B_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380105` | DDP_C0_PORT_D_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380106` | DDP_C0_PORT_BD_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e380107` | DDP_C0_PORT_BD_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380108` | DDP_C1_PORT_A_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380109` | DDP_C1_PORT_C_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38010a` | DDP_C1_PORT_AC_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e38010b` | DDP_C1_PORT_AC_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e38010c` | DDP_C1_PORT_B_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38010d` | DDP_C1_PORT_D_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38010e` | DDP_C1_PORT_BD_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e38010f` | DDP_C1_PORT_BD_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380110` | DDP_C2_PORT_A_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380111` | DDP_C2_PORT_C_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380112` | DDP_C2_PORT_AC_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e380113` | DDP_C2_PORT_AC_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380114` | DDP_C2_PORT_B_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380115` | DDP_C2_PORT_D_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380116` | DDP_C2_PORT_BD_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e380117` | DDP_C2_PORT_BD_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380118` | DDP_C3_PORT_A_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e380119` | DDP_C3_PORT_C_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38011a` | DDP_C3_PORT_AC_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e38011b` | DDP_C3_PORT_AC_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e38011c` | DDP_C3_PORT_B_RADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38011d` | DDP_C3_PORT_D_WADDRr | MMU | DDP Debug Logic Reg |
| `0x0e38011e` | DDP_C3_PORT_BD_CMDr | MMU | DDP Debug Logic Reg |
| `0x0e38011f` | DDP_C3_PORT_BD_DATAr | MMU | DDP Debug Logic Reg |
| `0x0e380120` | DDP_MODULE_CONTROLr | MMU | DDP Debug Logic Reg |
| `0x0e380121` | DDP_PROGRAM_GOr | MMU | DDP Debug Logic Reg |
| `0x0f100000` | RIPD4r | IPIPE | Receive IPv4 L3 Discard Packet Counter |
| `0x0f100001` | RIPC4r | IPIPE | Receive IPv4 L3 Unicast Frame Counter |
| `0x0f100002` | RIPHE4r | IPIPE | Receive IPv4 L3 IP Header Error Packet Counter |
| `0x0f100003` | IMRP4r | IPIPE | Receive IPv4 L3 routed multicast packets |
| `0x0f100004` | RIPD6r | IPIPE | Receive IPv6 L3 Discard Packet Counter |
| `0x0f100005` | RIPC6r | IPIPE | Receive IPv6 L3 Unicast Frame Counter |
| `0x0f100006` | RIPHE6r | IPIPE | Receive IPv6 L3 IP Header Error Packet Counter |
| `0x0f100007` | IMRP6r | IPIPE | Receive IPv6 L3 routed multicast packets |
| `0x0f100008` | RDISCr | IPIPE | Receive Discard Packet Counter |
| `0x0f100009` | RUCr | IPIPE | Receive Unicast Counter |
| `0x0f10000a` | RPORTDr | IPIPE | PortInDiscard Counter |
| `0x0f10000b` | RDBGC0r | IPIPE | Receive debug counter #0 |
| `0x0f10000c` | RDBGC1r | IPIPE | Receive debug counter #1 |
| `0x0f10000d` | RDBGC2r | IPIPE | Receive debug counter #2 |
| `0x0f10000e` | RDBGC3r | IPIPE | Receive debug counter #3 |
| `0x0f10000f` | RDBGC4r | IPIPE | Receive debug counter #4 |
| `0x0f100010` | RDBGC5r | IPIPE | Receive debug counter #5 |
| `0x0f100011` | IUNHGIr | IPIPE | Receive Unknown HGI Packet Counter |
| `0x0f100012` | ICTRLr | IPIPE | Receive HiGig Packet with Control Opcode Counter |
| `0x0f100013` | IBCASTr | IPIPE | Receive HiGig Packet with Broadcast Opcode Counter |
| `0x0f100014` | ILTOMCr | IPIPE | Receive HiGig Packet with L2MC Opcode Counter |
| `0x0f100015` | IIPMCr | IPIPE | Receive HiGig Packet with IPMC Opcode Counter |
| `0x0f100016` | IUNKOPCr | IPIPE | Receive HiGig Packet with Unknown Opcode Counter |
| `0x0f100017` | RDBGC6r | IPIPE | Receive debug counter #6 |
| `0x0f100018` | RDBGC7r | IPIPE | Receive debug counter #7 |
| `0x0f100019` | RDBGC8r | IPIPE | Receive debug counter #8 |
| `0x0f10001a` | ING_TRILL_RX_PKTSr | IPIPE | Number of packets received on this port with TRILL ethertype. |
| `0x0f10001b` | ING_TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDEDr | IPIPE | Number of TRILL frames dropped on an incoming TRILL access port. |
| `0x0f10001c` | ING_TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDEDr | IPIPE | Number of non-TRILL frames dropped on an incoming TRILL network port. |
| `0x0f10001d` | ING_NIV_RX_FRAMES_ERROR_DROPr | IPIPE | Number of frames dropped due to VNTAG format errors. |
| `0x0f10001e` | ING_NIV_RX_FRAMES_FORWARDING_DROPr | IPIPE | Number of frames dropped due to an NIV forwarding errors. |
| `0x0f10001f` | ING_NIV_RX_FRAMES_VLAN_TAGGEDr | IPIPE | Number of VLAN tagged packets received from this port. |
| `0x0f100660` | SFLOW_ING_THRESHOLDr | IPIPE | sFlow Ingress Threshold Register |
| `0x0f100661` | SFLOW_EGR_THRESHOLDr | IPIPE | sFlow Egress Threshold Register |
| `0x0f100665` | MODPORT_MAP_SELr | IPIPE | Selects one of 16 MODPORT_MAP Tables |
| `0x0f100666` | LOCAL_SW_DISABLE_CTRLr | IPIPE | Selects one of 16 MODPORT_MAP Tables |
| `0x0f100668` | SRC_MODID_EGRESS_SELr | IPIPE | Selects one of 8 SRC_MODID_EGRESS Tables |
| `0x0f100677` | ING_COS_MODEr | IPIPE | Index by egress port, COS mode select - must be programmed the same way as MMUs COS_MODE r |
| `0x0f1006a2` | ING_MISC_PORT_CONFIGr | IPIPE | index by ingress port |
| `0x0f180201` | E2E_DROP_COUNT_Xr | IPIPE | Counter for packets dropped due to E2EHOL drop status. |
| `0x0f180263` | ING_EVENT_DEBUG_Xr | IPIPE | Ingress Events Debug Register |
| `0x0f180268` | ING_EVENT_DEBUG_2_Xr | IPIPE | Ingress Events Debug Register |
| `0x0f180401` | E2E_DROP_COUNT_Yr | IPIPE | Counter for packets dropped due to E2EHOL drop status. |
| `0x0f180463` | ING_EVENT_DEBUG_Yr | IPIPE | Ingress Events Debug Register |
| `0x0f180468` | ING_EVENT_DEBUG_2_Yr | IPIPE | Ingress Events Debug Register |
| `0x0f180614` | RDBGC0_SELECTr | IPIPE | Receive debug counter #0 Trigger Select Register |
| `0x0f180615` | RDBGC1_SELECTr | IPIPE | Receive debug counter #1 Trigger Select Register |
| `0x0f180616` | RDBGC2_SELECTr | IPIPE | Receive debug counter #2 Trigger Select Register |
| `0x0f180617` | RDBGC3_SELECTr | IPIPE | Receive debug counter #3 Trigger Select Register |
| `0x0f180618` | RDBGC4_SELECTr | IPIPE | Receive debug counter #4 Trigger Select Register |
| `0x0f180619` | RDBGC5_SELECTr | IPIPE | Receive debug counter #5 Trigger Select Register |
| `0x0f18061a` | RDBGC6_SELECTr | IPIPE | Receive debug counter #6 Trigger Select Register |
| `0x0f18061b` | RDBGC7_SELECTr | IPIPE | Receive debug counter #7 Trigger Select Register |
| `0x0f18061c` | RDBGC8_SELECTr | IPIPE | Receive debug counter #8 Trigger Select Register |
| `0x0f18061d` | RDBGC_SELECT_2r | IPIPE | Receive debug counter Trigger Select Registers for conditions in counter vector past the f |
| `0x0f180626` | SFLOW_ING_RAND_SEEDr | IPIPE | sFlow Ingress Random Number Generator Seed Register |
| `0x0f180627` | SFLOW_EGR_RAND_SEEDr | IPIPE | sFlow Egress Random Number Generator Seed Register |
| `0x0f18064c` | RTAG7_HASH_HG_TRUNKr | IPIPE | RTAG7 hash control register for Higig trunking |
| `0x0f18064e` | RTAG7_HASH_PLFSr | IPIPE | RTAG7 hash control register for LAG failover |
| `0x0f18064f` | RTAG7_HASH_HG_TRUNK_FAILOVERr | IPIPE | RTAG7 hash control register for Higig trunk failover |
| `0x0f180658` | ING_MISC_CONFIGr | IPIPE | Configuration bits that are needed in Isw2 |
| `0x0f180659` | MIRROR_SELECTr | IPIPE | Mirror select register, FeatureSpecific-Ethernet |
| `0x0f180662` | SW2_HW_CONTROLr | IPIPE | Sw2 Control for Hardware functions |
| `0x0f180665` | SW2_FP_DST_ACTION_CONTROLr | IPIPE | Enable functions when IFP generates a REDIRECT, REPLACE_PBM or OR_PBM action |
| `0x0f180678` | ING_MIRROR_COS_CONTROLr | IPIPE | Controls usage of MIR_COS for Unicast packets. |
| `0x0f180679` | RTAG7_HASH_DLB_HGTr | IPIPE | RTAG7 hash control register for DLB_HGT Flow Set Index generation. |
| `0x0f180c01` | E2E_DROP_COUNTr | IPIPE | Counter for packets dropped due to E2EHOL drop status. |
| `0x0f180c63` | ING_EVENT_DEBUGr | IPIPE | Ingress Events Debug Register |
| `0x0f180c68` | ING_EVENT_DEBUG_2r | IPIPE | Ingress Events Debug Register 2 |
| `0x0f180d00` | IP5_INTR_STATUSr | IPIPE | IP5 Interrupt Status |
| `0x0f180d01` | IP5_INTR_ENABLEr | IPIPE | Bitwise interrupt enable for IP5_INTR_STATUS |
| `0x0f180d02` | IP5_INTR_STATUS_1r | IPIPE | IP5 Interrupt Status |
| `0x0f180d03` | IP5_INTR_ENABLE_1r | IPIPE | Bitwise interrupt enable for IP5_INTR_STATUS_1 |
| `0x0f180d04` | IP5_INTR_STATUS_2r | IPIPE | IP5 Interrupt Status 2 |
| `0x0f180d05` | IP5_INTR_ENABLE_2r | IPIPE | Bitwise interrupt enable for IP5_INTR_STATUS_2 |
| `0x0f180d06` | L3_MTU_VALUES_PARITY_CONTROLr | IPIPE | Parity Controls for L3_MTU_VALUES, FeatureSpecific-Ethernet |
| `0x0f180d07` | L3_MTU_VALUES_PARITY_STATUS_INTRr | IPIPE | L3_MTU_VALUES_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d08` | L3_MTU_VALUES_PARITY_STATUS_NACKr | IPIPE | L3_MTU_VALUES_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d09` | SW2_RAM_CONTROL_0r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0a` | SW2_RAM_CONTROL_1r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0b` | SW2_RAM_CONTROL_2r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0c` | SW2_RAM_CONTROL_3r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0d` | SW2_RAM_CONTROL_4r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0e` | SW2_RAM_CONTROL_5r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d0f` | SW2_RAM_CONTROL_6r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d10` | SW2_RAM_CONTROL_7r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d11` | SW2_RAM_CONTROL_8r | IPIPE | Debug Register to drive the TM inputs of internal rams |
| `0x0f180d12` | CPU_COS_CAM_DBGCTRLr | IPIPE | CPU_COS_CAM_CONTROL, FeatureSpecific-Ethernet |
| `0x0f180d13` | CPU_COS_CAM_BIST_STATUSr | IPIPE | CPU_COS_CAM_BIST_STATUS |
| `0x0f180d14` | CPU_COS_CAM_BIST_CONFIGr | IPIPE | CPU_COS_CAM_BIST_CONFIG, FeatureSpecific-Ethernet |
| `0x0f180d15` | CPU_COS_CAM_BIST_DBG_DATAr | IPIPE | CPU_COS_CAM_BIST_DBG_DATA |
| `0x0f180d16` | EGR_MASK_PARITY_CONTROLr | IPIPE | Parity Control for EGR_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d17` | EGR_MASK_PARITY_STATUS_INTRr | IPIPE | EGR_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d18` | EGR_MASK_PARITY_STATUS_NACKr | IPIPE | EGR_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d19` | TRUNK_MEMBER_PARITY_CONTROLr | IPIPE | Parity Controls for TRUNK_MEMBER, FeatureSpecific-Ethernet |
| `0x0f180d1a` | TRUNK_MEMBER_PARITY_STATUS_INTRr | IPIPE | TRUNK_MEMBER_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d1b` | TRUNK_MEMBER_PARITY_STATUS_NACKr | IPIPE | TRUNK_MEMBER_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d1c` | TRUNK_BITMAP_TABLE_PARITY_CONTROLr | IPIPE | Parity Control for TRUNK_BITMAP_TABLE table, FeatureSpecific-Ethernet |
| `0x0f180d1d` | TRUNK_BITMAP_TABLE_PARITY_STATUS_INTRr | IPIPE | TRUNK_BITMAP_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d1e` | TRUNK_BITMAP_TABLE_PARITY_STATUS_NACKr | IPIPE | TRUNK_BITMAP_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d1f` | NONUCAST_TRUNK_BLOCK_MASK_PARITY_CONTROLr | IPIPE | Parity Control for NONUCAST_TRUNK_BLOCK_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d20` | NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_INTRr | IPIPE | NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d21` | NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_NACKr | IPIPE | NONUCAST_TRUNK_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d22` | MODPORT_MAP_SW_PARITY_CONTROLr | IPIPE | MODPORT_MAP_SW_PARITY_CONTROL |
| `0x0f180d23` | MODPORT_MAP_SW_PARITY_STATUS_INTRr | IPIPE | MODPORT_MAP_SW_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d24` | MODPORT_MAP_SW_PARITY_STATUS_NACKr | IPIPE | MODPORT_MAP_SW_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d25` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_CONTROLr | IPIPE | Parity Control for ING_HIGIG_TRUNK_OVERRIDE_PROFILE table, FeatureSpecific-Ethernet |
| `0x0f180d26` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_INTRr | IPIPE | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d27` | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_NACKr | IPIPE | ING_HIGIG_TRUNK_OVERRIDE_PROFILE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d28` | PORT_LAG_FAILOVER_SET_PARITY_CONTROLr | IPIPE | Parity Control for PORT_LAG_FAILOVER_SET table, FeatureSpecific-Ethernet |
| `0x0f180d29` | PORT_LAG_FAILOVER_SET_PARITY_STATUS_INTRr | IPIPE | PORT_LAG_FAILOVER_SET_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d2a` | PORT_LAG_FAILOVER_SET_PARITY_STATUS_NACKr | IPIPE | PORT_LAG_FAILOVER_SET_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d2b` | MODPORT_MAP_MIRROR_PARITY_CONTROLr | IPIPE | Parity Control for MODPORT_MAP_MIRROR table, FeatureSpecific-Ethernet |
| `0x0f180d2c` | MODPORT_MAP_M0_PARITY_STATUS_INTRr | IPIPE | MODPORT_MAP_M0_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d2d` | MODPORT_MAP_M0_PARITY_STATUS_NACKr | IPIPE | MODPORT_MAP_M0_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d2e` | MODPORT_MAP_M1_PARITY_STATUS_INTRr | IPIPE | MODPORT_MAP_M1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d2f` | MODPORT_MAP_M1_PARITY_STATUS_NACKr | IPIPE | MODPORT_MAP_M1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d30` | MODPORT_MAP_M2_PARITY_STATUS_INTRr | IPIPE | MODPORT_MAP_M2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d31` | MODPORT_MAP_M2_PARITY_STATUS_NACKr | IPIPE | MODPORT_MAP_M2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d32` | MODPORT_MAP_M3_PARITY_STATUS_INTRr | IPIPE | MODPORT_MAP_M3_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d33` | MODPORT_MAP_M3_PARITY_STATUS_NACKr | IPIPE | MODPORT_MAP_M3_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d34` | ALTERNATE_EMIRROR_BITMAP_PARITY_CONTROLr | IPIPE | Parity Control for ALTERNATE_EMIRROR_BITMAP table, FeatureSpecific-Ethernet |
| `0x0f180d35` | ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_INTRr | IPIPE | ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d36` | ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_NACKr | IPIPE | ALTERNATE_EMIRROR_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d37` | ING_PW_TERM_SEQ_NUM_PARITY_CONTROLr | IPIPE | Parity Control for ING_PW_TERM_SEQ_NUM table, FeatureSpecific-Ethernet |
| `0x0f180d38` | ING_PW_TERM_SEQ_NUM_PARITY_STATUS_INTRr | IPIPE | ING_PW_TERM_SEQ_NUM_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d39` | ING_PW_TERM_SEQ_NUM_PARITY_STATUS_NACKr | IPIPE | ING_PW_TERM_SEQ_NUM_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d3a` | MAC_BLOCK_TABLE_PARITY_CONTROLr | IPIPE | Parity Control for MAC_BLOCK_TABLE table, FeatureSpecific-Ethernet |
| `0x0f180d3b` | MAC_BLOCK_TABLE_PARITY_STATUS_INTRr | IPIPE | MAC_BLOCK_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d3c` | MAC_BLOCK_TABLE_PARITY_STATUS_NACKr | IPIPE | MAC_BLOCK_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d3d` | VLAN_PROFILE_2_PARITY_CONTROLr | IPIPE | Parity Control for VLAN_PROFILE_2 table, FeatureSpecific-Ethernet |
| `0x0f180d3e` | VLAN_PROFILE_2_PARITY_STATUS_INTRr | IPIPE | VLAN_PROFILE_2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d3f` | VLAN_PROFILE_2_PARITY_STATUS_NACKr | IPIPE | VLAN_PROFILE_2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d40` | E2E_HOL_STATUS_PARITY_CONTROLr | IPIPE | Parity Control for E2E_HOL_STATUS table, FeatureSpecific-Ethernet |
| `0x0f180d41` | E2E_HOL_STATUS_PARITY_STATUS_INTRr | IPIPE | E2E_HOL_STATUS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d42` | E2E_HOL_STATUS_PARITY_STATUS_NACKr | IPIPE | E2E_HOL_STATUS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d43` | E2E_HOL_STATUS_1_PARITY_CONTROLr | IPIPE | Parity Control for E2E_HOL_STATUS_1 table, FeatureSpecific-Ethernet |
| `0x0f180d44` | E2E_HOL_STATUS_1_PARITY_STATUS_INTRr | IPIPE | E2E_HOL_STATUS_1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d45` | E2E_HOL_STATUS_1_PARITY_STATUS_NACKr | IPIPE | E2E_HOL_STATUS_1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d46` | VLAN_COS_MAP_PARITY_CONTROLr | IPIPE | Parity Control for VLAN_COS_MAP table, FeatureSpecific-Ethernet |
| `0x0f180d47` | VLAN_COS_MAP_PARITY_STATUS_INTRr | IPIPE | VLAN_COS_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d48` | VLAN_COS_MAP_PARITY_STATUS_NACKr | IPIPE | VLAN_COS_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d49` | SRC_MODID_INGRESS_BLOCK_PARITY_CONTROLr | IPIPE | Parity Control for SRC_MODID_INGRESS_BLOCK table, FeatureSpecific-Ethernet |
| `0x0f180d4a` | SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_INTRr | IPIPE | SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d4b` | SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_NACKr | IPIPE | SRC_MODID_INGRESS_BLOCK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d4c` | SRC_MODID_EGRESS_PARITY_CONTROLr | IPIPE | Parity Control for SRC_MODID_EGRESS table, FeatureSpecific-Ethernet |
| `0x0f180d4d` | SRC_MODID_EGRESS_PARITY_STATUS_INTRr | IPIPE | SRC_MODID_EGRESS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d4e` | SRC_MODID_EGRESS_PARITY_STATUS_NACKr | IPIPE | SRC_MODID_EGRESS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d4f` | VOQ_COS_MAP_PARITY_CONTROLr | IPIPE | Parity Control for VOQ_COS_MAP table, FeatureSpecific-Ethernet |
| `0x0f180d50` | VOQ_COS_MAP_PARITY_STATUS_INTRr | IPIPE | VOQ_COS_MAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d51` | VOQ_COS_MAP_PARITY_STATUS_NACKr | IPIPE | VOQ_COS_MAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d52` | LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_CONTROLr | IPIPE | Parity Control for LOCAL_SW_DISABLE_DEFAULT_PBM table, FeatureSpecific-Ethernet |
| `0x0f180d53` | LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_INTRr | IPIPE | LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d54` | LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_NACKr | IPIPE | LOCAL_SW_DISABLE_DEFAULT_PBM_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d55` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_CONTROLr | IPIPE | Parity Control for LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR table, FeatureSpecific-Ethernet |
| `0x0f180d56` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_INTRr | IPIPE | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d57` | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_NACKr | IPIPE | LOCAL_SW_DISABLE_DEFAULT_PBM_MIRR_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d58` | UNKNOWN_UCAST_BLOCK_MASK_PARITY_CONTROLr | IPIPE | Parity Control for UNKNOWN_UCAST_BLOCK_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d59` | UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_INTRr | IPIPE | UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d5a` | UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_NACKr | IPIPE | UNKNOWN_UCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d5b` | UNKNOWN_MCAST_BLOCK_MASK_PARITY_CONTROLr | IPIPE | Parity Control for UNKNOWN_MCAST_BLOCK_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d5c` | UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTRr | IPIPE | UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d5d` | UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACKr | IPIPE | UNKNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d5e` | BCAST_BLOCK_MASK_PARITY_CONTROLr | IPIPE | Parity Control for BCAST_BLOCK_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d5f` | BCAST_BLOCK_MASK_PARITY_STATUS_INTRr | IPIPE | BCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d60` | BCAST_BLOCK_MASK_PARITY_STATUS_NACKr | IPIPE | BCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d61` | EMIRROR_CONTROL_PARITY_CONTROLr | IPIPE | Parity Control for EMIRROR_CONTROL table, FeatureSpecific-Ethernet |
| `0x0f180d62` | EMIRROR_CONTROL_PARITY_STATUS_INTRr | IPIPE | EMIRROR_CONTROL_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d63` | EMIRROR_CONTROL_PARITY_STATUS_NACKr | IPIPE | EMIRROR_CONTROL_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d64` | ING_EGRMSKBMAP_PARITY_CONTROLr | IPIPE | Parity Control for ING_EGRMSKBMAP table, FeatureSpecific-Ethernet |
| `0x0f180d65` | ING_EGRMSKBMAP_PARITY_STATUS_INTRr | IPIPE | ING_EGRMSKBMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d66` | ING_EGRMSKBMAP_PARITY_STATUS_NACKr | IPIPE | ING_EGRMSKBMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d67` | KNOWN_MCAST_BLOCK_MASK_PARITY_CONTROLr | IPIPE | Parity Control for KNOWN_MCAST_BLOCK_MASK table, FeatureSpecific-Ethernet |
| `0x0f180d68` | KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTRr | IPIPE | KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d69` | KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACKr | IPIPE | KNOWN_MCAST_BLOCK_MASK_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d6a` | EMIRROR_CONTROL1_PARITY_CONTROLr | IPIPE | Parity Control for EMIRROR_CONTROL1 table, FeatureSpecific-Ethernet |
| `0x0f180d6b` | EMIRROR_CONTROL1_PARITY_STATUS_INTRr | IPIPE | EMIRROR_CONTROL1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d6c` | EMIRROR_CONTROL1_PARITY_STATUS_NACKr | IPIPE | EMIRROR_CONTROL1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d6d` | EMIRROR_CONTROL2_PARITY_CONTROLr | IPIPE | Parity Control for EMIRROR_CONTROL2 table, FeatureSpecific-Ethernet |
| `0x0f180d6e` | EMIRROR_CONTROL2_PARITY_STATUS_INTRr | IPIPE | EMIRROR_CONTROL2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d6f` | EMIRROR_CONTROL2_PARITY_STATUS_NACKr | IPIPE | EMIRROR_CONTROL2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d70` | EMIRROR_CONTROL3_PARITY_CONTROLr | IPIPE | Parity Control for EMIRROR_CONTROL3 table, FeatureSpecific-Ethernet |
| `0x0f180d71` | EMIRROR_CONTROL3_PARITY_STATUS_INTRr | IPIPE | EMIRROR_CONTROL3_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d72` | EMIRROR_CONTROL3_PARITY_STATUS_NACKr | IPIPE | EMIRROR_CONTROL3_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d73` | IMIRROR_BITMAP_PARITY_CONTROLr | IPIPE | Parity Control for IMIRROR_BITMAP table, FeatureSpecific-Ethernet |
| `0x0f180d74` | IMIRROR_BITMAP_PARITY_STATUS_INTRr | IPIPE | IMIRROR_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d75` | IMIRROR_BITMAP_PARITY_STATUS_NACKr | IPIPE | IMIRROR_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d76` | UNKNOWN_HGI_BITMAP_PARITY_CONTROLr | IPIPE | Parity Control for UNKNOWN_HGI_BITMAP table, FeatureSpecific-Ethernet |
| `0x0f180d77` | UNKNOWN_HGI_BITMAP_PARITY_STATUS_INTRr | IPIPE | UNKNOWN_HGI_BITMAP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d78` | UNKNOWN_HGI_BITMAP_PARITY_STATUS_NACKr | IPIPE | UNKNOWN_HGI_BITMAP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d79` | SW2_EOP_BUFFER_A_PARITY_CONTROLr | IPIPE | Parity Control for SW2_EOP_BUFFER_A table, FeatureSpecific-Ethernet |
| `0x0f180d7a` | SW2_EOP_BUFFER_A_PARITY_STATUS_INTRr | IPIPE | SW2_EOP_BUFFER_A_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d7b` | SW2_EOP_BUFFER_B_PARITY_CONTROLr | IPIPE | Parity Control for SW2_EOP_BUFFER_B table, FeatureSpecific-Ethernet |
| `0x0f180d7c` | SW2_EOP_BUFFER_B_PARITY_STATUS_INTRr | IPIPE | SW2_EOP_BUFFER_B_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d7d` | SW2_EOP_BUFFER_C_PARITY_CONTROLr | IPIPE | Parity Control for SW2_EOP_BUFFER_C table, FeatureSpecific-Ethernet |
| `0x0f180d7e` | SW2_EOP_BUFFER_C_PARITY_STATUS_INTRr | IPIPE | SW2_EOP_BUFFER_C_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d7f` | CPB_PARITY_CONTROLr | IPIPE | Parity Control for CPB table, FeatureSpecific-Ethernet |
| `0x0f180d80` | CPB_PARITY_STATUS_INTRr | IPIPE | CPB_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d81` | IP_COUNTERS_PARITY_CONTROLr | IPIPE | Parity Control for IP stats counters, FeatureSpecific-Ethernet |
| `0x0f180d82` | IP_COUNTERS_PARITY_STATUS_INTRr | IPIPE | IP_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d83` | IP_COUNTERS_PARITY_STATUS_NACKr | IPIPE | IP_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d84` | RDBGC_MEM_INST0_PARITY_CONTROLr | IPIPE | Parity Control for fixed and flexible debug counters, FeatureSpecific-Ethernet |
| `0x0f180d85` | RDBGC_MEM_INST0_PARITY_STATUS_INTRr | IPIPE | RDBGC_MEM_INST0_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d86` | RDBGC_MEM_INST0_PARITY_STATUS_NACKr | IPIPE | RDBGC_MEM_INST0_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d87` | RDBGC_MEM_INST1_PARITY_CONTROLr | IPIPE | Parity Control for flexible debug counters, FeatureSpecific-Ethernet |
| `0x0f180d88` | RDBGC_MEM_INST1_PARITY_STATUS_INTRr | IPIPE | RDBGC_MEM_INST1_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d89` | RDBGC_MEM_INST1_PARITY_STATUS_NACKr | IPIPE | RDBGC_MEM_INST1_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d8a` | RDBGC_MEM_INST2_PARITY_CONTROLr | IPIPE | Parity Control for flexible debug counters, FeatureSpecific-Ethernet |
| `0x0f180d8b` | RDBGC_MEM_INST2_PARITY_STATUS_INTRr | IPIPE | RDBGC_MEM_INST2_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d8c` | RDBGC_MEM_INST2_PARITY_STATUS_NACKr | IPIPE | RDBGC_MEM_INST2_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d8d` | HG_COUNTERS_PARITY_CONTROLr | IPIPE | Parity Control for Higig stats counters, FeatureSpecific-Ethernet |
| `0x0f180d8e` | HG_COUNTERS_PARITY_STATUS_INTRr | IPIPE | HG_COUNTERS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d8f` | HG_COUNTERS_PARITY_STATUS_NACKr | IPIPE | HG_COUNTERS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d90` | ING_SERVICE_COUNTER_TABLE_PARITY_CONTROLr | IPIPE | Parity Control for ING_SERVICE_COUNTER_TABLE table, FeatureSpecific-Ethernet |
| `0x0f180d91` | ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTRr | IPIPE | ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d92` | ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACKr | IPIPE | ING_SERVICE_COUNTER_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d93` | ING_VINTF_COUNTER_TABLE_PARITY_CONTROLr | IPIPE | Parity Control for ING_VINTF_COUNTER_TABLE table, FeatureSpecific-Ethernet |
| `0x0f180d94` | ING_VINTF_COUNTER_TABLE_PARITY_STATUS_INTRr | IPIPE | ING_VINTF_COUNTER_TABLE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d95` | ING_VINTF_COUNTER_TABLE_PARITY_STATUS_NACKr | IPIPE | ING_VINTF_COUNTER_TABLE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d96` | NIV_ERROR_DROP_PARITY_CONTROLr | IPIPE | Parity Control for NIV_ERROR_DROP table, FeatureSpecific-Ethernet |
| `0x0f180d97` | NIV_ERROR_DROP_PARITY_STATUS_INTRr | IPIPE | NIV_ERROR_DROP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d98` | NIV_ERROR_DROP_PARITY_STATUS_NACKr | IPIPE | NIV_ERROR_DROP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d99` | NIV_FORWARDING_DROP_PARITY_CONTROLr | IPIPE | Parity Control for NIV_FORWARDING_DROP table, FeatureSpecific-Ethernet |
| `0x0f180d9a` | NIV_FORWARDING_DROP_PARITY_STATUS_INTRr | IPIPE | NIV_FORWARDING_DROP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d9b` | NIV_FORWARDING_DROP_PARITY_STATUS_NACKr | IPIPE | NIV_FORWARDING_DROP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d9c` | NIV_VLAN_TAGGED_PARITY_CONTROLr | IPIPE | Parity Control for NIV_VLAN_TAGGED table, FeatureSpecific-Ethernet |
| `0x0f180d9d` | NIV_VLAN_TAGGED_PARITY_STATUS_INTRr | IPIPE | NIV_VLAN_TAGGED_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180d9e` | NIV_VLAN_TAGGED_PARITY_STATUS_NACKr | IPIPE | NIV_VLAN_TAGGED_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180d9f` | TRILL_RX_PKTS_PARITY_CONTROLr | IPIPE | Parity Control for TRILL_RX_PKTS table, FeatureSpecific-Ethernet |
| `0x0f180da0` | TRILL_RX_PKTS_PARITY_STATUS_INTRr | IPIPE | TRILL_RX_PKTS_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180da1` | TRILL_RX_PKTS_PARITY_STATUS_NACKr | IPIPE | TRILL_RX_PKTS_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180da2` | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_CONTROLr | IPIPE | Parity Control for TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED table, FeatureSpecific-Ethern |
| `0x0f180da3` | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTRr | IPIPE | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x0f180da4` | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACKr | IPIPE | TRILL_RX_ACCESS_PORT_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x0f180da5` | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_CONTROLr | IPIPE | Parity Control for TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED table, FeatureSpecific-E |
| `0x0f180da6` | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTRr | IPIPE | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_INTR, FeatureSpecific-Etherne |
| `0x0f180da7` | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACKr | IPIPE | TRILL_RX_NETWORK_PORT_NON_TRILL_PKTS_DISCARDED_PARITY_STATUS_NACK, FeatureSpecific-Etherne |
| `0x0f38002a` | CELLLINKMEMDEBUGr | MMU | TM: tm registers. |
| `0x10180720` | SBS_CONTROLr | IPIPE | IP main arbiter control register for number of ports |
| `0x11100201` | DLB_HGT_PORT_QUALITY_MEASURE_UPDATE_CONTROLr | IPIPE | DLB_HGT Quality Update Control Register. |
| `0x11100202` | DLB_HGT_QUANTIZE_CONTROLr | IPIPE | DLB_HGT Quantization Parameters. |
| `0x11100203` | DLB_HGT_PORT_INST_QUALITY_MEASUREr | IPIPE | DLB_HGT Port Instantaneous Quality Metrics. |
| `0x11100204` | DLB_HGT_PORT_AVG_QUALITY_MEASUREr | IPIPE | DLB_HGT Port Average Quality Metrics. |
| `0x11100205` | DLB_HGT_QUANTIZED_AVG_QUALITY_MEASUREr | IPIPE | DLB_HGT Quantized Average Port Quality Measure. |
| `0x11100206` | DLB_HGT_FINAL_PORT_QUALITY_MEASUREr | IPIPE | DLB_HGT Port Quality. |
| `0x11180200` | DLB_HGT_QUALITY_MEASURE_CONTROLr | IPIPE | DLB_HGT Quality Measure Update Control Register. |
| `0x11180208` | DLB_HGT_RANDOM_SELECTION_CONTROL_Xr | IPIPE | DLB_HGT Random Selection Seed. |
| `0x11180408` | DLB_HGT_RANDOM_SELECTION_CONTROL_Yr | IPIPE | DLB_HGT Random Selection Seed. |
| `0x11180607` | DLB_HGT_CURRENT_TIMEr | IPIPE | DLB_HGT Current Time. |
| `0x11180c08` | DLB_HGT_RANDOM_SELECTION_CONTROLr | IPIPE | DLB_HGT Random Selection Seed. |
| `0x11180d00` | DLB_HGT_FLOWSET_PORT_PARITY_CONTROLr | IPIPE | Parity Controls for DLB_HGT_FLOWSET_PORT, FeatureSpecific-Ethernet |
| `0x11180d01` | DLB_HGT_FLOWSET_PORT_PARITY_STATUS_INTRr | IPIPE | DLB_HGT_FLOWSET_PORT_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x11180d02` | DLB_HGT_FLOWSET_PORT_PARITY_STATUS_NACKr | IPIPE | DLB_HGT_FLOWSET_PORT_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x11180d03` | DLB_HGT_FLOWSET_TIMESTAMP_PARITY_CONTROLr | IPIPE | Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP, FeatureSpecific-Ethernet |
| `0x11180d04` | DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_INTRr | IPIPE | DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x11180d05` | DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_NACKr | IPIPE | DLB_HGT_FLOWSET_TIMESTAMP_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x11180d06` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_CONTROLr | IPIPE | Parity Controls for DLB_HGT_FLOWSET_TIMESTAMP_PAGE, FeatureSpecific-Ethernet |
| `0x11180d07` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_INTRr | IPIPE | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_INTR, FeatureSpecific-Ethernet |
| `0x11180d08` | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_NACKr | IPIPE | DLB_HGT_FLOWSET_TIMESTAMP_PAGE_PARITY_STATUS_NACK, FeatureSpecific-Ethernet |
| `0x15300060` | XPORT_TO_MMU_BKPr | MMU | XPORT to MMU BKP status |
| `0x15300070` | PORT_LLFC_CFGr | MMU | LLFC Configuation for each MMU Port, start from P1 to P65 |
| `0x15380000` | PRIO2COS_LLFCr | MMU | Bitmap identifying COSes affected by a given LLFC priority |
| `0x15380000` | PRIO2COS_LLFC0r | MMU | Profile 0, Bitmap identifying COSes affected by a given LLFC priority |
| `0x15380010` | PRIO2COS_LLFC1r | MMU | Profile 1, Bitmap identifying COSes affected by a given LLFC priority |
| `0x15380020` | PRIO2COS_LLFC2r | MMU | Profile 2, Bitmap identifying COSes affected by a given LLFC priority |
| `0x15380030` | PRIO2COS_LLFC3r | MMU | Profile 3, Bitmap identifying COSes affected by a given LLFC priority |
| `0x15380040` | PRIO2EXTQ_LLFCr | MMU | define Extended Qs affected by a given LLFC priority. |
| `0x15380040` | PRIO2EXTQ_LLFC0r | MMU | Profile 0,  define Extended Qs affected by a given LLFC priority. |
| `0x15380050` | PRIO2EXTQ_LLFC1r | MMU | Profile 1,  define Extended Qs affected by a given LLFC priority. |
| `0x15380080` | VOQFC_MSG_PORT_SEL0r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x15380090` | VOQFC_MSG_PORT_SEL1r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800a0` | VOQFC_MSG_PORT_SEL2r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800b0` | VOQFC_MSG_PORT_SEL3r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800c0` | VOQFC_MSG_PORT_SEL4r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800d0` | VOQFC_MSG_PORT_SEL5r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800e0` | VOQFC_MSG_PORT_SEL6r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x153800f0` | VOQFC_MSG_PORT_SEL7r | MMU | define system ports on remote Fabric chip who are involving in NVOQ-FC |
| `0x15380100` | VOQFC_STATE_MERGE_GRP0r | MMU | define NVOQ-FC (received on MMU port 1) message merge due to Trunking on Fabric |
| `0x15380110` | VOQFC_STATE_MERGE_GRP1r | MMU | define NVOQ-FC message(received on MMU port 2) merge due to Trunking on Fabric |
| `0x15380120` | VOQFC_STATE_MERGE_GRP2r | MMU | define NVOQ-FC message (received on MMU port 3)merge due to Trunking on Fabric |
| `0x15380130` | VOQFC_STATE_MERGE_GRP3r | MMU | define NVOQ-FC message (received on MMU port 4)merge due to Trunking on Fabric |
| `0x15380140` | VOQFC_STATE_MERGE_GRP4r | MMU | define NVOQ-FC message (received on MMU port 34)merge due to Trunking on Fabric |
| `0x15380150` | VOQFC_STATE_MERGE_GRP5r | MMU | define NVOQ-FC message (received on MMU port 35)merge due to Trunking on Fabric |
| `0x15380160` | VOQFC_STATE_MERGE_GRP6r | MMU | define NVOQ-FC message (received on MMU port 36)merge due to Trunking on Fabric |
| `0x15380170` | VOQFC_STATE_MERGE_GRP7r | MMU | define NVOQ-FC message (received on MMU port 37)merge due to Trunking on Fabric |
| `0x15380180` | VOQFC_STATE_PORT0_64r | MMU | NVOQ Port0 Virtual output queue status |
| `0x15380181` | VOQFC_STATE_PORT1_64r | MMU | NVOQ PORT1 Virtual output queue status |
| `0x15380182` | VOQFC_STATE_PORT2_64r | MMU | NVOQ PORT2 Virtual output queue status |
| `0x15380183` | VOQFC_STATE_PORT3_64r | MMU | NVOQ PORT3 Virtual output queue status |
| `0x15380184` | VOQFC_STATE_PORT4_64r | MMU | NVOQ PORT4 Virtual output queue status |
| `0x15380185` | VOQFC_STATE_PORT5_64r | MMU | NVOQ PORT5 Virtual output queue status |
| `0x15380186` | VOQFC_STATE_PORT6_64r | MMU | NVOQ PORT6 Virtual output queue status |
| `0x15380187` | VOQFC_STATE_PORT7_64r | MMU | NVOQ PORT7 Virtual output queue status |
| `0x15380200` | VOQFC_CNTr | MMU | Received VOQ-FC message counter |
| `0x16300100` | MMU_TO_XPORT_BKPr | MMU | MMU to XPORT BKP status |
| `0x16380010` | E2ECC_HOL_ENr | MMU | E2ECC HOL report enable |
| `0x16380020` | E2ECC_MIN_TX_TIMERr | MMU | E2ECC TX HG Minimum Repeat Timer Register |
| `0x16380021` | E2ECC_MAX_TX_TIMERr | MMU | E2ECC TX HG Maximum Repeat Timer Register |
| `0x16380050` | MMU_LLFC_TX_CONFIG_1r | MMU | LLC Configuration register 1 |
| `0x16380051` | MMU_LLFC_TX_CONFIG_2r | MMU | LLC Configuration register 2 |
| `0x16380400` | E2ECC_PORT_MAPPING_CONFIGr | MMU | E2ECC Port Mapping configuartion Register |
| `0x16380420` | E2ECC_TX_ENABLE_BMPr | MMU | e2ecc tx enable for each port of each XLPORT |
| `0x16380460` | E2ECC_TX_PORTS_NUMr | MMU | number of ports state carried in E2ECC message |
| `0x16380470` | E2ECC_TX_MODEr | MMU | E2ECC Tx UC queue or (UC \| MC) Queue states |
| `0x16380540` | OOBFC_CHANNEL_BASE_64r | MMU | OOBFC Channel Base |
| `0x16380550` | OOBFC_ING_PORT_EN_0_64r | MMU | per ingress port based status report enable,start from logic port0 |
| `0x16380560` | OOBFC_ING_PORT_EN_1_64r | MMU | per ingress port based status report enable,start from logic port35 |
| `0x16380570` | OOBFC_ENG_PORT_EN_0_64r | MMU | per egress port based status report enable,start from logic port0 |
| `0x16380580` | OOBFC_ENG_PORT_EN_1_64r | MMU | per egress port based status report enable,start from logic port35 |
| `0x16380590` | OOBFC_GCSr | MMU | GCS_EN: 0 - Don't report GCS field, set to 0 |
| `0x163805a0` | OOBFC_STSr | MMU | FIFO_XFR_EMPTY: 1 - Async FIFO during OOBFC transmitting |
| `0x163805b0` | OOBFC_TX_IDLEr | MMU | IDLE_GAP: Define IDLE period between each OOBFC TX message in 125Mhz clock cycles. |
| `0x17300010` | PORT_SP_WRED_CONFIGr | MMU | Port Service Pool WRED Config Register |
| `0x17300014` | PORT_SP_WRED_AVG_QSIZEr | MMU | Port Service Pool WRED Average Queue Size Register |
| `0x17300020` | WRED_CONFIGr | MMU | WRED Config Register |
| `0x17300028` | WRED_AVG_QSIZEr | MMU | WRED Average Queue Size Register |
| `0x17300100` | DMVOQ_WRED_CONFIGr | MMU | DMVOQ WRED Config Register |
| `0x17300200` | VOQ_WRED_AVG_QSIZEr | MMU | DMVOQ_WRED Average Queue Size Register |
| `0x17380000` | TIME_DOMAINr | MMU | ECN Marking configuartion Registers |
| `0x17380004` | WRED_PARITY_ERROR_INFOr | MMU | Parity error pointer info Registers |
| `0x17380005` | WRED_PARITY_ERROR_BITMAPr | MMU | Parity error pointer bitmap Registers |
| `0x17380008` | GLOBAL_SP_WRED_CONFIGr | MMU | Global Service Pool WRED Config Register |
| `0x1738000c` | GLOBAL_SP_WRED_AVG_QSIZEr | MMU | GLOBAL Service Pool WRED Average Queue Size Register |
| `0x17380c00` | WREDMEMDEBUG_CONFIGr | MMU | TM: tm registers. |
| `0x17380c01` | WREDMEMDEBUG_AVG_QSIZEr | MMU | TM: tm registers. |
| `0x17380c02` | WREDMEMDEBUG_PROFILEr | MMU | STBY_0: stby 0 register. |
| `0x17380c0c` | WREDMEMDEBUG_DROP_THD_UC_ENQ0r | MMU | TM: tm registers. |
| `0x17380c0d` | WREDMEMDEBUG_DROP_THD_UC_ENQ1r | MMU | TM: tm registers. |
| `0x17380c0e` | WREDMEMDEBUG_DROP_THD_UC_DEQ0r | MMU | TM: tm registers. |
| `0x17380c0f` | WREDMEMDEBUG_DROP_THD_UC_DEQ1r | MMU | TM: tm registers. |
| `0x19300000` | S3_CONFIGr | MMU | Egress Scheduler Configuration Register for stage 3 scheduler S3 |
| `0x19300001` | S3_CONFIG_MCr | MMU | Egress Scheduler Configuration Register for stage 3 scheduler MC group |
| `0x19300010` | S3_COSWEIGHTSr | MMU | Egress Scheduler Weight for each queue in WRR & WERR modes |
| `0x193000b0` | S3_COSMASKr | MMU | Cosmask for the 4 S3 groups |
| `0x193000bf` | S3_COSMASK_MCr | MMU | Cosmask for the special MC group |
| `0x193000c0` | S3_MINSPCONFIGr | MMU | Select a queue as Strict Priority when scheduling minimum bandwidth, only active for WRR/W |
| `0x193000cf` | S3_MINSPCONFIG_MCr | MMU | Select a queue as Strict Priority when scheduling minimum bandwidth in MC group, only acti |
| `0x193000d0` | S3_WERRCOUNTr | MMU | The count in the bucket controlling WERR/WRR. |
| `0x19380120` | ES_S3_MEMORY_PARITY_STATUS_0r | MMU | parity error status for pipe 0 |
| `0x19380121` | ES_S3_MEMORY_PARITY_STATUS_1r | MMU | parity error status for pipe 1 |
| `0x19380122` | ES_S3_MEMORY_TM_0r | MMU | TM: TM for weight memory in pipe 0 |
| `0x19380123` | ES_S3_MEMORY_TM_1r | MMU | TM: TM for weight memory in pipe 1 |
| `0x19380124` | ES_S3_MEMORY_CREDIT_TM_0r | MMU | TM: TM for credit ctr memory in pipe 0 |
| `0x19380125` | ES_S3_MEMORY_CREDIT_TM_1r | MMU | TM: TM for credit ctr memory in pipe 1 |
| `0x1a300000` | S2_CONFIGr | MMU | Egress Scheduler Configuration Register for stage 2 scheduler |
| `0x1a300010` | S2_COSWEIGHTSr | MMU | Egress Scheduler Weight for each queue in WRR & WERR modes |
| `0x1a3000b0` | S2_COSMASKr | MMU | Cosmask |
| `0x1a3000c0` | S2_MINSPCONFIGr | MMU | Select an S3 group as Strict Priority when scheduling minimum bandwidth, only active for W |
| `0x1a3000d0` | S2_WERRCOUNTr | MMU | The count in the bucket controlling WERR/WRR. |
| `0x1a3000e0` | S2_S3_ROUTINGr | MMU | The S3 group number routed to this S2 ETS group input, 0x1F means no connection |
| `0x1a3800f0` | ES_S2_MEMORY_PARITY_STATUS_0r | MMU | parity error status for pipe 0 |
| `0x1a3800f1` | ES_S2_MEMORY_PARITY_STATUS_1r | MMU | parity error status for pipe 1 |
| `0x1a3800f2` | ES_S2_MEMORY_TM_0r | MMU | TM: TM for weight memory in pipe 0 |
| `0x1a3800f3` | ES_S2_MEMORY_TM_1r | MMU | TM: TM for weight memory in pipe 1 |
| `0x1a3800f4` | ES_S2_MEMORY_CREDIT_TM_0r | MMU | TM: TM for credit ctr memory in pipe 0 |
| `0x1a3800f5` | ES_S2_MEMORY_CREDIT_TM_1r | MMU | TM: TM for credit ctr memory in pipe 1 |
| `0x1b300100` | MCQ_FIFO_BASE_REGr | MMU | MCQ_FIFO_BASE_REG |
| `0x1b300110` | MCQ_FIFO_EMPTY_REGr | MMU | MCQ_FIFO_EMPTY_REG |
| `0x1b380000` | MCQ_CONFIGr | MMU | MCQ_CONFIG |
| `0x1b380011` | MCQ_MCFIFOERRPTRr | MMU | Captutred MCFIFO Pointer address |
| `0x1b380012` | MCQ_GRPTBLERRPTRr | MMU | Captutred GRPTBL Pointer address |
| `0x1b380013` | MCQ_VLANTBLERRPTRr | MMU | Captutred VLANTBL Pointer address |
| `0x1b380020` | MCQ_ERRINTRr | MMU | MCQ memory soft error interrupt 1 |
| `0x1b380021` | MCFIFOMEMDEBUGr | MMU | MC FIFO Memory debug register |
| `0x1b380022` | IPMCGRPMEMDEBUGr | MMU | IPMC Group Table Memory debug register |
| `0x1b380023` | IPMCVLANMEMDEBUGr | MMU | TM: sam registers. |
| `0x1b380030` | MCQ_IPMCREP_SRCHFAIL0r | MMU | IPMC VLAN Table search fail register, pipe0 |
| `0x1b380032` | MCQ_IPMCREP_SRCHFAIL1r | MMU | IPMC VLAN Table search fail register, pipe0 |
| `0x1b380033` | MCQ_DIS_IPMC_REPLICATION0r | MMU | Stop IPMC packet replication in the MCQ, Pipe0 |
| `0x1b380034` | MCQ_DIS_IPMC_REPLICATION1r | MMU | Stop IPMC packet replication in the MCQ, Pipe1 |
| `0x1b380035` | MCQ_IPMC_FAST_FLUSH0r | MMU | Enable IPMC packet fast flush functions in the MCQ, Pipe0 |
| `0x1b380036` | MCQ_IPMC_FAST_FLUSH1r | MMU | Enable IPMC packet fast flush functions in the MCQ, Pipe1 |
| `0x1b380037` | MCQ_IPMC_REPLICATION_STAT0r | MMU | Port IPMC packet replication status, pipe0 |
| `0x1b380038` | MCQ_IPMC_REPLICATION_STAT1r | MMU | Port IPMC packet replication status, pipe1 |
| `0x1d380008` | PQEFIFOEMPTY0_64r | MMU | PQE fifo empty status |
| `0x1d380009` | PQEFIFOEMPTY1_64r | MMU | PQE fifo empty status |
| `0x1d380010` | PQEFIFOOVERFLOW0_64r | MMU | PQE fifo overflow Error |
| `0x1d380011` | PQEFIFOOVERFLOW1_64r | MMU | PQE fifo overflow Error |
| `0x1d380012` | PQEPARITYERRORADRr | MMU | PQE Parity Error Address |
| `0x1d380013` | PQEMEMDEBUGr | MMU | PQE Memory debug register |
| `0x1d380014` | PQEFIFOPTREQUAL0_64r | MMU | PQE fifo wr-rd ptr status |
| `0x1d380015` | PQEFIFOPTREQUAL1_64r | MMU | PQE fifo wr-rd ptr status |
| `0x1d380016` | PQEMEMCFGr | MMU | PQE MEM module config |
| `0x1e380000` | MMU_QCN_CNM_CTRL_64r | MMU | MMU QCN CNM Control register (debug-only) |
| `0x1e380010` | MMU_QCN_CPQ_SEQr | MMU | MMU QCN CPQ Expect Q setting |
| `0x1e380030` | MMU_QCN_PARITY_ERRr | MMU | Parity error memory and error address |
| `0x1e380040` | MMU_QCN_MEM_DEBUGr | MMU | memory stby config |
| `0x1f300040` | OVQ_MCQ_CREDITSr | MMU | OVQ_MCQ_FIFO_CREDITS |
| `0x1f300050` | OVQ_MCQ_STATEr | MMU | state machine |
| `0x1f380002` | OVQ_LINKED_LIST_SELECTr | MMU | enable linked list ovq logic |
| `0x1f380004` | OVQ_DROP_THRESHOLD0r | MMU | OVQ_DROP_THRESHOLD0 |
| `0x1f380006` | OVQ_LINKED_REGr | MMU | LINKED_FLOP MUX NUMBER |
| `0x1f380008` | OVQ_FLOWCONTROL_THRESHOLDr | MMU | OVQ_FLOWCONTROL_THRESHOLD |
| `0x1f380009` | OVQ_DROP_THRESHOLD_REGr | MMU | OVQ_DROP_THRESHOLD |
| `0x1f38000c` | OVQ_DROP_THRESHOLD_RESET_LIMITr | MMU | OVQ_DROP_THRESHOLD_RESET_LIMIT |
| `0x1f38000d` | OVQ_LINKED_NEXTPTRr | MMU | OVQ NEXT POINTER indicated by OVQ_LINKED_REG |
| `0x1f38000e` | OVQ_FLOWCONTROL_COUNTERr | MMU | OVQ_flow control counter |
| `0x1f38000f` | OVQ_BLOCK_COUNTERr | MMU | OVQ_block counter |
| `0x1f380010` | OVQ_BUBBLE_THRESHOLDr | MMU | OVQ_BUBBLE Threshold and offset_limit |
| `0x1f380011` | OVQ_BUBBLE_SIZE_REGr | MMU | OVQ_BUBBLE SIZE |
| `0x1f380014` | OVQ_ADDRESS_RANGE_0r | MMU | OVQ_ADDRESS_RANGE_0 |
| `0x1f380018` | OVQ_ADDRESS_RANGE_1r | MMU | OVQ_ADDRESS_RANGE_1, this can only be used when RANGE0 is active and range1 should be larg |
| `0x1f38001c` | OVQ_ADDRESS_RANGE_2r | MMU | OVQ_ADDRESS_RANGE_2, this can only be used when 0 and 1 are used, and range2 should be lar |
| `0x1f380020` | OVQ_ADDRESS_RANGE_3r | MMU | OVQ_ADDRESS_RANGE_3, this is used when 0 and 1 and 2 are used, and this range should be bi |
| `0x1f380024` | OVQ_DFTr | MMU | OVQ_DFT |
| `0x1f380025` | OVQ_DISTRIBUTOR_DFTr | MMU | OVQ_DISTRIBUTOR_DFT |
| `0x1f380029` | OVQ_SCANNER_POINTERr | MMU | SCNNER pointers |
| `0x1f380030` | OVQ_SCANNER_MAX_POINTERr | MMU | MAX SCNNER write pointer |
| `0x1f380031` | OVQ_LINKED_LIST_REGr | MMU | free head/tail and ovq head/tail |
| `0x1f380032` | COS_MODE_Xr | MMU | cos mode per port for x pipe |
| `0x1f380034` | COS_MODE_Yr | MMU | cos mode per port for y pipe |
| `0x1f380036` | MTP_COSr | MMU | mirror port cos |
| `0x1f380038` | OVQ_ECC_BITMAPr | MMU | ECC error bitmap, address |
| `0x20300100` | DROP_PKT_CNT_INGr | MMU | Drop packet counter |
| `0x20300101` | DROP_BYTE_CNT_ING_64r | MMU | Drop byte counter |
| `0x20300110` | DROP_PKT_CNT_OVQr | MMU | Drop packets due to Multicast OVQ |
| `0x20380000` | SYS_CONTROLr | MMU | CTR control |
| `0x20380002` | CTR_MEM_TMr | MMU | CTR  memory debug |
| `0x20380003` | CTR_MEM_CFGr | MMU | CTR  memory pin cfg |
| `0x20380004` | MMU_CTR_PARITY_ERRr | MMU | Parity error memory and error address |
| `0x20380010` | TX_CNT_CONFIGr | MMU | TX packet counter configuration |
| `0x20380020` | TX_PKT_CNTr | MMU | TX packet counter |
| `0x20380120` | DROP_CBP_64r | MMU | Drop packets due to CBP full |
| `0x21380100` | PQ_C0_PORT_A_RADDRr | MMU | PQ Debug Logic Reg |
| `0x21380101` | PQ_C0_PORT_A_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380102` | PQ_C0_PORT_A_CMDr | MMU | PQ Debug Logic Reg |
| `0x21380103` | PQ_C0_PORT_A_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380104` | PQ_C0_PORT_A_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x21380105` | PQ_C0_PORT_A_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380106` | PQ_C0_PORT_A_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x21380107` | PQ_C0_PORT_B_RADDRr | MMU | PQ Debug Logic Reg |
| `0x21380108` | PQ_C0_PORT_B_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380109` | PQ_C0_PORT_B_CMDr | MMU | PQ Debug Logic Reg |
| `0x2138010a` | PQ_C0_PORT_B_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x2138010b` | PQ_C0_PORT_B_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x2138010c` | PQ_C0_PORT_B_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x2138010d` | PQ_C0_PORT_B_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x2138010e` | PQ_C1_PORT_A_RADDRr | MMU | PQ Debug Logic Reg |
| `0x2138010f` | PQ_C1_PORT_A_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380110` | PQ_C1_PORT_A_CMDr | MMU | PQ Debug Logic Reg |
| `0x21380111` | PQ_C1_PORT_A_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380112` | PQ_C1_PORT_A_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x21380113` | PQ_C1_PORT_A_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380114` | PQ_C1_PORT_A_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x21380115` | PQ_C1_PORT_B_RADDRr | MMU | PQ Debug Logic Reg |
| `0x21380116` | PQ_C1_PORT_B_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380117` | PQ_C1_PORT_B_CMDr | MMU | PQ Debug Logic Reg |
| `0x21380118` | PQ_C1_PORT_B_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380119` | PQ_C1_PORT_B_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x2138011a` | PQ_C1_PORT_B_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x2138011b` | PQ_C1_PORT_B_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x2138011c` | PQ_C2_PORT_A_RADDRr | MMU | PQ Debug Logic Reg |
| `0x2138011d` | PQ_C2_PORT_A_WADDRr | MMU | PQ Debug Logic Reg |
| `0x2138011e` | PQ_C2_PORT_A_CMDr | MMU | PQ Debug Logic Reg |
| `0x2138011f` | PQ_C2_PORT_A_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380120` | PQ_C2_PORT_A_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x21380121` | PQ_C2_PORT_A_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380122` | PQ_C2_PORT_A_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x21380123` | PQ_C2_PORT_B_RADDRr | MMU | PQ Debug Logic Reg |
| `0x21380124` | PQ_C2_PORT_B_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380125` | PQ_C2_PORT_B_CMDr | MMU | PQ Debug Logic Reg |
| `0x21380126` | PQ_C2_PORT_B_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380127` | PQ_C2_PORT_B_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x21380128` | PQ_C2_PORT_B_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380129` | PQ_C2_PORT_B_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x2138012a` | PQ_C3_PORT_A_RADDRr | MMU | PQ Debug Logic Reg |
| `0x2138012b` | PQ_C3_PORT_A_WADDRr | MMU | PQ Debug Logic Reg |
| `0x2138012c` | PQ_C3_PORT_A_CMDr | MMU | PQ Debug Logic Reg |
| `0x2138012d` | PQ_C3_PORT_A_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x2138012e` | PQ_C3_PORT_A_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x2138012f` | PQ_C3_PORT_A_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380130` | PQ_C3_PORT_A_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x21380131` | PQ_C3_PORT_B_RADDRr | MMU | PQ Debug Logic Reg |
| `0x21380132` | PQ_C3_PORT_B_WADDRr | MMU | PQ Debug Logic Reg |
| `0x21380133` | PQ_C3_PORT_B_CMDr | MMU | PQ Debug Logic Reg |
| `0x21380134` | PQ_C3_PORT_B_DATA_0r | MMU | PQ Debug Logic Reg |
| `0x21380135` | PQ_C3_PORT_B_DATA_1r | MMU | PQ Debug Logic Reg |
| `0x21380136` | PQ_C3_PORT_B_DATA_2r | MMU | PQ Debug Logic Reg |
| `0x21380137` | PQ_C3_PORT_B_DATA_3r | MMU | PQ Debug Logic Reg |
| `0x21380138` | PQ_MODULE_CONTROLr | MMU | PQ Debug Logic Reg |
| `0x21380139` | PQ_PROGRAM_GOr | MMU | PQ Debug Logic Reg |
| `0x22300000` | CHFC2PFC_STATEr | MMU | Channel Flow Control (InBand/OutBand) states mapped to PFC priority states |
| `0x22380050` | OOBFC_CHIF_CFGr | MMU | OOBFC Channel Flow Control Interface config |
| `0x22380080` | OOBFC_MSG_CRC_CNTr | MMU | OOBFC message crc error count |
| `0x22380090` | OOBFC_MSG_REG0r | MMU | Debug Register, store OOBFC message Byte0-Byte7 |
| `0x223800a0` | OOBFC_MSG_REG1r | MMU | Debug Register, store OOBFC message Byte8-Byte14 |
| `0x223800b0` | OOBIF_DEBUGr | MMU | Debug Register |

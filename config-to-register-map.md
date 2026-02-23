# Config to Register Map

**Purpose**: Map BCM config parameters to ASIC register writes
**Source**: rc.soc analysis, CUMULUS_REVERSE_ENGINEERING_FINDINGS

## Config -> Register

| Config param | Effect | Register(s) |
|--------------|--------|-------------|
| polled_irq_mode | IRQ vs poll | SDK internal |
| table_dma_enable | Table DMA | DMA control regs |
| tslam_dma_enable | SLAM DMA | DMA control regs |
| portmap_* | Port mapping | Port table init |
| pbmp_* | Port bitmap | Port enable bitmap |

## rc.soc setreg commands

| setreg | Value | Purpose |
|--------|-------|---------|
| rdbgc0_select | 0x04000d11 | RX drop stats |
| rdbgc3_select | 0x00000011 | |
| rdbgc4_select | 0x00000100 | |
| rdbgc5_select | 0x00002000 | |
| rdbgc6_select | 0x00008000 | |
| tdbgc6_select | 0x00040000 | TX drop stats |

## References

- [asic-init-sequence.md](asic-init-sequence.md)
- [bcm-config-format.md](bcm-config-format.md)
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found register access patterns (`setreg`, `getreg`, `soc_reg`, `rcload`) and debug counter register strings (`rdbgc`, `tdbgc`) matching the rc.soc `setreg` commands documented here

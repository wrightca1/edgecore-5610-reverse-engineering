# ASIC Init Sequence

**Source**: rc.soc analysis, CUMULUS_REVERSE_ENGINEERING_FINDINGS
**Date**: 2026-02-15

## Register Writes (from rc.soc)

### Statistics / Drop Counters

| Register | Value | Purpose |
|----------|-------|---------|
| rdbgc0_select | 0x04000d11 | RIPD4, RIPD6, RDISC, RPORTD, PDISC, VLANDR |
| rdbgc3_select | 0x00000011 | RIPD4, RIPD6 |
| rdbgc4_select | 0x00000100 | RDISC |
| rdbgc5_select | 0x00002000 | RFILDR |
| rdbgc6_select | 0x00008000 | RDROP |
| tdbgc6_select | 0x00040000 | TPKTD |

### Optional (commented in rc.soc)

- xmac_tx_ctrl 0xc802
- MAC_RSV_MASK MASK=0x18
- cmic_misc_control LINK40G_ENABLE=1
- IFP_METER_PARITY_CONTROL 0 (Trident errata)

## Init Order

1. attach *
2. init all (SDK bulk init)
3. rcload rc.ports_0 (port mapping)
4. rcload rc.led (LED program)
5. setreg (statistics)
6. rcload rc.datapath_0 (datapath pipeline)

## Before/After Comparison

To capture full register state:
- Use bcmsh on Cumulus: `getreg <regname>`
- Dump before switchd start, after ready
- Compare to document init sequence

## References

- [bcm-config-format.md](bcm-config-format.md)
- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md) Section 5.4
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found `rdbgc*_select` and `tdbgc*_select` strings (e.g., `rdbgc0_select`, `rdbgc3_select`, `tdbgc6_select`) matching the drop counter register configuration documented here

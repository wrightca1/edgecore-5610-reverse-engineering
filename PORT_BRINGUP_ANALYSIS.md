# Port Bringup Analysis (5.2–5.3)

**Date**: 2026-02-19  
**Source**: FindPortFunctions, DumpFunctionCode for port API callees

---

## Port API → Internal callees

| OpenNSL API              | Address    | Callee        | Address   |
|--------------------------|------------|---------------|-----------|
| opennsl_port_enable_set  | 01dcf78c   | FUN_007d3f34  | 007d3f34  |
| opennsl_port_speed_set   | 01dcfe64   | FUN_007de7cc  | 007de7cc  |
| opennsl_port_duplex_set  | 01dcf6c0   | FUN_007d3294  | 007d3294  |
| opennsl_port_info_set    | —          | (not found)   | —         |
| opennsl_port_info_get    | —          | (not found)   | —         |

---

## Callee flow (speed, duplex)

FUN_007de7cc (speed) and FUN_007d3294 (duplex) follow the same pattern:

1. Validate unit: `cmplwi r3, 0x7f` (r3 ≤ 127)
2. Table lookup: base = [r30-0x8000], index = r3*4
3. r26 = [r9+8] (sub-index from unit struct)
4. Load handler from [base-0x7ffc][r26*4] + offset:
   - Speed: offset -0x5fe0
   - Duplex: offset -0x68b0
5. Indirect call (bctrl) to unit-specific handler
6. Call FUN_0086fe6c (callback dispatcher, same as packet TX)

No direct register addresses in first 80 lines; hardware access is in the indirect handler. The handler is loaded from per-unit data tables at [r9-0x5fe0] (speed) or [r9-0x68b0] (duplex) — cannot resolve static address. To find SerDes/port registers: (1) GDB breakpoint at bctrl in FUN_007de7cc/FUN_007d3294 to capture handler address, (2) trace mmap/write during port up.

---

## References

- [PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md) — BDE ioctls during link up
- libopennsl-port-functions.txt
- libopennsl-dump-07d3f34.txt, 07de7cc.txt, 07d3294.txt

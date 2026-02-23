# BAR diff during port up (10.1.1.233)

**Date**: 2026-02-20  
**Purpose**: Find register offsets that change when bringing swp1 up (Path B 5.2–5.3).  
**Method**: Dump first 64KB of BAR0 (phys 0x04000000) and 256KB of BAR1 (0xa0000000) before and after `ip link set swp1 down; ip link set swp1 up`, then diff.

## Result

- **BAR0 @ 0x04000000** (64KB): **14** 4-byte words changed.
- **BAR1 @ 0xa0000000** (256KB): No changes in this run (or dumps not differing).

### Changed offsets (BAR0, from 0x04000000)

| Offset (hex) | Before   | After    |
|--------------|----------|----------|
| 0x46f8       | 0x000015d9 | 0x000015da |
| 0x4818       | 0x00000004 | 0x00000005 |
| 0x4820       | 0x000015d9 | 0x000015da |
| 0x4830       | 0x00000336 | 0x00000338 |
| 0x4870       | 0x00001913 | 0x00001917 |
| 0x4880       | 0x0000190f | 0x00001912 |
| 0x4888       | 0x00000004 | 0x00000005 |
| 0x4928       | 0x00001913 | 0x00001917 |
| 0x49b8       | 0x000a5368 | 0x000a560c |
| 0x49e8       | 0x00000663 | 0x00000664 |
| 0x4a38       | 0x00000666 | 0x00000667 |
| 0x4a40       | 0x00000666 | 0x00000667 |
| 0x4a50       | 0x00000666 | 0x00000667 |
| 0x4b38       | 0x000325d2 | 0x00032644 |

Offsets are relative to BAR0 base **0x04000000** (full address = 0x04000000 + offset).

## Interpretation

- These locations are **candidates** for port/SerDes or link-state related registers (counters, status, or control). Small deltas (e.g. +1, +2) suggest counters or sequence numbers; larger deltas may be config or state.
- To map to port/SerDes: correlate with OpenNSL/SDK register names (e.g. from [SDK_REGISTER_MAP.md](../SDK_REGISTER_MAP.md), [PORT_BRINGUP_REGISTERS_ANALYSIS.md](../PORT_BRINGUP_REGISTERS_ANALYSIS.md)) or repeat with different ports to see per-port offsets.

## Register correlation (BAR0 base 0x04000000)

- Offsets above are **relative to BAR0** (full address = 0x04000000 + offset). In [SDK_REGISTER_MAP.md](../SDK_REGISTER_MAP.md) and [BDE_CMIC_REGISTERS.md](../BDE_CMIC_REGISTERS.md), CMIC/CMC bases are given (e.g. CMC0 0x31400, S-Chan 0x32800); those sit in a different range. The 0x4xxx range (0x46f8–0x4b38) may be **port block**, **stats**, or **SerDes**; no exact symbol match in current docs.
- **Next**: Search SDK/OpenNSL headers for hex constants **0x46f8**, **0x4818**, **0x4830**, **0x4870**, **0x4928**, **0x49b8**, **0x4a38**, **0x4b38**, or run BAR diff with another port (e.g. swp2) and diff the two diffs to see per-port stride.

## Scripts

- **On-switch**: `scripts/reverse-engineering/bar-diff-port-up-on-switch.sh [interface]` (run with sudo).
- **From host**: `scripts/reverse-engineering/run-bar-diff-port-up-10.1.1.233.sh [interface]` — runs on switch, fetches dumps, prints diff.

## swp2 vs swp1 (per-port)

Run with `run-bar-diff-port-up-10.1.1.233.sh swp2`:

- **swp2**: 5 words changed — 0x49e8, 0x4a38, 0x4a40, 0x4a50, 0x4b38 (values differ from swp1; e.g. 0x4a38 0x69d→0x69e).
- **swp1**: 14 words changed (see table above); includes 0x46f8, 0x4818, 0x4820, 0x4830, 0x4870, 0x4880, 0x4888, 0x4928, 0x49b8 in addition to the five above.

So **0x49e8, 0x4a38, 0x4a40, 0x4a50, 0x4b38** change for both ports (likely shared counters or global state); **0x46f8–0x4928** and **0x49b8** may be port-1-specific or only touched when swp1 is brought up first.

### swp3

Run with `run-bar-diff-port-up-10.1.1.233.sh swp3`:

- **swp3**: 6 words changed — **0x46f8, 0x4820, 0x4870, 0x4880, 0x4928, 0x49b8** (values differ per port; e.g. 0x46f8 0x17e7→0x17e8).
- Overlap with swp1: 0x46f8, 0x4820, 0x4870, 0x4880, 0x4928, 0x49b8 (swp3 does not show 0x4818, 0x4830, 0x4888, 0x49e8, 0x4a38, 0x4a40, 0x4a50, 0x4b38 in this run). So **0x46f8, 0x4820, 0x4870, 0x4880, 0x4928, 0x49b8** are strong per-port candidates; the rest may be shared or timing-dependent.

**Naming**: Searched repo (opennsl-register-constants.txt, docs, C headers) and OpenBCM GitHub — no symbol names for BAR0 offsets 0x46f8, 0x4820, etc. BCM56846/Trident2 register maps are typically under NDA. **Next**: Broadcom SDK headers, datasheet, or vendor docs for port/SerDes/stats block at 0x04xxxx.

## Artifacts

- `traces/bar-diff-before_bar0_40.bin`, `bar-diff-after_bar0_40.bin` (64KB each)
- `traces/bar-diff-before_bar1_a0.bin`, `bar-diff-after_bar1_a0.bin` (256KB each)

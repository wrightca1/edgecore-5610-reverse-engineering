# Cumulus → EdgeNOS register-gap analysis

Cross-references Cumulus's `dump_soc_diff.txt` (every chip register
Cumulus changed from reset defaults) with what we currently write in
`asic/edged/`.  Output is `cumulus_register_analysis.csv` alongside
this file.

## Method

The `scripts/regs_analysis.py` tool:

1. **Parses `bcm56840_a0_defs.h`** (the OpenMDK chip-symbols header)
   for register descriptions, blocks, and field lists.  Captured
   2,263 register definitions.
2. **Parses `dump_soc_diff.txt`** (Cumulus baseline capture) — 417
   unique registers that Cumulus changed from chip-reset defaults,
   across many port/pipe scopes (some have 50+ scopes — one per
   port/queue).
3. **Greps `asic/edged/*.c`** for `WRITE_<NAME>r` and `WRITE_<NAME>m`
   to see which registers we ourselves write — currently 55.
4. **Tags each register** with a crude importance heuristic based on
   name + block.

## Summary (2026-05-14)

| Category | Total | Ported | Gap |
|---|--:|--:|--:|
| HIGH (data path) | 26 | 17 | **9** |
| medium (MMU) | 57 | 3 | 54 |
| medium (ACL / filter) | 23 | 0 | 23 |
| medium (QoS / hash) | 20 | 10 | 10 |
| medium (diag/counter) | 19 | 7 | 12 |
| low (statistics) | 17 | 0 | 17 |
| low (parity init) | 103 | 0 | 103 |
| unknown | 152 | 0 | 152 |
| **TOTAL** | **417** | **37** | **380** |

## Top gaps to fix

### High-leverage, never-ported

| Register | Block | Scopes | Value | Why we suspect it matters |
|---|---|--:|---|---|
| `COMMAND_CONFIG` | XLPORT × 52 | 52 | `0x11800158` | XLMAC TX/RX enable + mode.  We never touch it. |
| `EGR_MTU` | EPIPE × 52 | 52 | `0x000045f2` | Egress per-port MTU.  Default may be 0 → every egress frame dropped at MTU check. |
| `EGR_VLAN_CONTROL_1` | EPIPE × 52 | 52 | `0x00002001` | Egress VLAN-membership controls. |
| `AUX_ARB_CONTROL_2` | IPIPE | 1 | `0x0327f863` | Companion to `AUX_ARB_CONTROL` (we ported _but not _2). |
| `OP_BUFFER_LIMIT_{RED,YELLOW}_CELL` | MMU | 1 each | `0x130b` | Color-aware MMU thresholds. |
| `OP_BUFFER_MAX_TOTAL_COUNT_CELL` | MMU | 3 | `0x4` | MMU total cell cap. |
| `OP_PORT_LIMIT_COLOR_CELL` | MMU × 54 | 54 | `0x130b` | Per-port color limits. |
| `OP_QUEUE_LIMIT_COLOR_CELL` | MMU × 313 | 313 | `0x7` | Per-queue color limits. |
| `INPUT_PORT_RX_ENABLE0_64` | MMU | 1 | `0x1ffffffff` | RX ingress enable bitmap for ports 0–32 — includes CPU (bit 0).  Our BMD writes it but value may differ. |

### Lower priority but missing

- All 23 IFP/EFP/VFP/FP_*_PARITY_CONTROL writes — Cumulus initializes parity-check tables.  Without these the chip may either log errors or drop frames hitting un-init'd memory.
- 103 `*_PARITY_CONTROL` writes total (mostly low-impact "enable parity checks on table X").
- 17 statistics-counter init writes (low impact).
- 152 "unknown" — uncategorized; some of these have descriptive names (`COMMAND_CONFIG`, `EGR_MTU`, `IGMP_MLD_PKT_CONTROL`) and are actually high-impact; the heuristic just didn't have a keyword for them.  Re-classifying after first pass would be useful.

## How to use this analysis

```sh
# Re-run after changing edged sources (to refresh "ported_by_us")
python3 scripts/regs_analysis.py

# Filter the CSV — show gap registers in a category:
python3 -c '
import csv
for r in csv.DictReader(open("decoded.md/cumulus_register_analysis.csv")):
    if r["ported_by_us"]=="no" and "HIGH" in r["importance_guess"]:
        print(r["register"], r["sample_value"], r["description"][:80])
'
```

## Next actions (in order of likely impact)

1. Port `EGR_MTU` to a sensible value (`0x45f2` = ~17.9 KB) per port.  Single highest suspicion for "frames silently dropped at egress."
2. Port `COMMAND_CONFIG` per port — make sure XLMAC RX/TX is enabled with the right bits Cumulus uses.
3. Port `OP_BUFFER_LIMIT_*_CELL` color thresholds (MMU per-port).
4. Port `OP_PORT_LIMIT_COLOR_CELL` per port.
5. Look at the 152 "unknown"-category registers; re-classify and triage.

Updated 2026-05-14 after the chip-to-CPU forwarding investigation.

# Warpcore PHY Firmware — Function Map

Deep analysis of `BCM84740-ver-D102.bin` (32 KB 8051 code, loaded at
0x8000 in PHY program memory). Identified 43 functions; for each
function, tracked MMIO accesses (via `MOVX @DPTR, A` after `MOV DPTR, #imm`).

8051 decompilation quality in Ghidra is moderate — assembly-level
analysis is often clearer.

## Function map (44 functions, sorted by entry address)

### Major BRANCH/init functions (touch many MMIO addresses)

| Addr | Size | MMIO writes | MMIO reads | Likely role |
|---|---|---|---|---|
| **0xACCE** | **1453** | 37 | 38 | **The MAIN SerDes init function** — touches 0x100-0x11C config block, 0x172-0x175 init regs, 0x1EB-0x1F6 (full SerDes adaptation cluster), 0x225 |
| **0xCEAD** | 314 | 9 | 10 | **EQ adaptation tight-loop arithmetic** — tight read+write to 0x01F4-0x01FD only |
| **0xC4CC** | 648 | 55 | 3 | **Configuration loader** (write-heavy) — 0x94xx range: 0x9430-0x945B, 0x9510-0x9519, 0x9544-0x9545, 0x9648-0x965A |
| **0xC978** | 526 | 77 | 2 | **Bigger config loader** (77 writes) — overlapping but expanded set in 0x94xx |
| **0xC1D7** | 838 | 27 | 15 | **Mode-change function** — touches both low bank (0x116, 0x199-0x1A3) and high bank (0xE001, 0x9542, 0x9641, 0x965C-D, 0x9472, 0x94E4-6) |
| **0xBC17** | 466 | 9 | 1 | Smaller helper — 0x1F0-0x1F7, 0x21C-0x21E + write 0x9643 |
| **0xD355** | 270 | 12 | 13 | EQ tracker — 0x1EB-0x1F7 (similar to 0xCEAD but with reads of all) |
| **0xD463** | 256 | 2 | 1 | **Chip-ID handshake** — writes 0x9434 (the "ready" register) with chip ID byte |

### Leaf utility functions (small, no MMIO)

A cluster at 0xD11C, 0xD135, 0xD162, 0xD174, 0xD196, 0xD1D7, 0xD1E0, 0xD1E9, 0xD20F — all 9-45 bytes — these are MDIO/MMIO helper primitives used by the bigger functions. Their names (from xrefs):

* `FUN_CODE_d11c` — small MMIO read (status?)
* `FUN_CODE_d1d7` — MMIO write
* `FUN_CODE_d1e0` — MMIO read
* `FUN_CODE_d135` — generic getter
* `FUN_CODE_d162` — write low byte
* `FUN_CODE_d174` — write with mask
* `FUN_CODE_d196` — 3-arg MMIO update (addr, mask, value)

### Entry-point chain (firmware @ 0x8000)

```
0x8000: LCALL 0xE301   ← main init helper (top of init chain)
0x8003: LCALL 0xBE00   ← only 5 bytes! likely a stub jump
0x800C: LCALL 0xE2CD   ← another init step
0x8021: LCALL 0xE3FD   ← chip-ID setter (also called by D463)
0x803C: LCALL 0xE334   ← yet another init step
```

## What we learned about the SerDes init

### Initialization order (inferred from 0xACCE function map)

The MAIN init function (0xACCE) touches registers in this MMIO space:

1. **Config block** (0x100-0x11C, 28 regs) — port-mode configuration, lane assignments
2. **Init regs** (0x172-0x175) — basic PHY ID and version
3. **0x197, 0x198** — clock dividers maybe
4. **SerDes adaptation cluster** (0x1EB-0x1F6, ~12 regs) — EQ tap state, RX/TX equalization
5. **0x225** — MDIO command channel or interrupt status

### EQ adaptation algorithm (function 0xCEAD)

Decompilation shows it's doing:

```c
void eq_update(char input) {
    int8_t v_old_a = read(0x1F1);
    int8_t v_old_b = ...;
    
    write(0x1F4, input);
    // ... shift-and-accumulate loop:
    // build a sliding window over R5+1 samples (where R5 is in 8051 bank 0)
    
    // Compute: new_tap_a = (v_a & mask_d) + (v_c & mask_b)
    //          new_tap_b = (v_b & mask_c) + (v_b & mask_a) - carry_correction
    
    write(0x1F1, new_tap_a);
    write(0x1F1, new_tap_b);
}
```

This is **DFE (Decision Feedback Equalizer) tap update arithmetic.**
The 8051 register R5 in bank 0 holds the tap count (number of samples
to integrate over). Each new sample shifts the window and recomputes
the EQ tap weights. The new tap values are written back via the
adjacent `0x1F8/0x1F9/0x1FA/0x1FB` regs which are the actual SerDes
DFE tap registers, then committed to `0x1F1`.

### High-bank configuration writes (0x94xx)

Functions 0xC4CC and 0xC978 together write 132+ values to the 0x94xx
register region. This is the **PMA (Physical Medium Attachment)
configuration block** — values stored in static tables in the firmware
that get loaded into the SerDes PMA at startup.

The most-written regs:
* `0x940F` (read+write) — likely a "PMA ready" status reg
* `0x9430-0x9437` (8 regs) — TX driver config
* `0x9452-0x945B` (10 regs) — RX adaptation initial state
* `0x9510-0x9519` (10 regs) — TX FFE tap initial values
* `0x9544-0x9545` — encoder config

### The 0x965C/0x965D pair — DFE adaptation telemetry

These two adjacent regs appear in BOTH 0xACCE and 0xC1D7. The high
read+write counts (11 reads, 11 writes from prior `phy_mmio_map.txt`)
suggest these hold the **DFE convergence status** — the firmware polls
them tightly during adaptation.

### Chip-ID handshake (function 0xD463)

Writes byte `0x44` to register `0x9434` (different from the chip ID
`0x8474` we initially expected — but it makes sense: the host doesn't
need the full chip ID echoed; this is a "firmware running, version
0x44" signal).

The host can poll `0x9434` after MDIO-loading the firmware:
* before load: garbage / 0
* after load + reset deassert: reads `0x44` (or similar version-stamp byte)

This is the **"firmware booted" signal** EdgeNOS can use.

## What's still unknown

1. **`0xE301`, `0xE2CD`, `0xE3FD`** — these are the first-call functions
   from entry point. They contain the early init logic but Ghidra
   couldn't reach them via standard disassembly. Need a manual disasm
   pass starting at each of these addresses.

2. **The MDIO command handler** — somewhere in the firmware there must
   be a poll loop that reads incoming MDIO commands (probably from a
   register around 0x0223 — the very first reg written at entry). This
   would be a "while (poll status) { decode command; dispatch }" loop.

3. **The SerDes BER threshold** — when the EQ adaptation declares
   "converged", which register/threshold drives that decision.

4. **Lane assignment** — the 84740 is 4-lane (one per QSFP), the
   firmware must support per-lane configuration. The config block at
   0x100-0x11C likely has 4 sub-blocks for the 4 lanes.

## EdgeNOS implications

For EdgeNOS to properly initialize Warpcore SerDes:

1. **Load this exact 32KB firmware** to PHY program RAM at 0x8000 via MDIO.
2. **Deassert PHY CPU reset** (separate MDIO write somewhere in CMICm).
3. **Wait for 0x9434 to read 0x44** — confirms firmware boot.
4. **Don't try to write SerDes registers (0x1Ex/0x1Fx)** while EQ adaptation
   is running — the firmware owns those. Just write the high-bank
   config (0x94xx) BEFORE telling it to start, then let it do its job.

The fact that the firmware does **all** the EQ math autonomously means
EdgeNOS doesn't need to implement DFE — just load the blob and trust it.

## Files

* `BCM84740-ver-D102.bin_function_map.txt` (43 functions w/ MMIO maps)
* `BCM84740-ver-D102.bin_key_funcs.c` (12 decompiled key functions)
* `BCM84740-ver-D102.bin_hot_functions.txt` (call frequency rank)
* `scripts/PhyFwDeep.java`, `PhyKeyFuncs.java`

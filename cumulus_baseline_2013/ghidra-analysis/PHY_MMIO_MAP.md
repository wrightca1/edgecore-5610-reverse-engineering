# PHY (Warpcore) MMIO Address Map — from 8051 firmware analysis

Extracted by walking every `MOVX @DPTR, A` and `MOVX A, @DPTR` instruction
in the disassembled PHY firmware. Tracked DPTR via the preceding
`MOV DPTR, #imm16` and `INC DPTR`.

* **Total accesses captured:** 910 MMIO operations
* **Unique addresses touched:** 181

The 8051's external-memory bus inside the Warpcore PHY IS the
register fabric — writing to a DPTR-addressed byte is a write to that
PHY register. Multi-byte reg accesses (16-bit, 32-bit) are done by
sequencing `MOVX` + `INC DPTR`.

## Most-accessed registers (high heat = state-machine / status polling)

| PHY addr | Reads | Writes | Likely role |
|---|---|---|---|
| `0x01EC` | 22 | 14 | SerDes status reg (hot R/W loop) |
| `0x01EB` | 21 | 18 | SerDes status reg (paired with 0x1EC) |
| `0x01F8` | 16 | 14 | Control reg |
| `0x01F7` | 11 | **23** | **MOST-written reg** — main control/cmd |
| `0x01FA` | 15 | 13 | Control |
| `0x01F9` | 15 | 13 | Control |
| `0x01EF` | 15 | 12 | Control |
| `0x01FB` | 12 | 10 | Control |
| `0x01EE` | 12 | 9 | Control |
| `0x01F5` | 9 | 18 | Heavy-write control |
| `0x01F1` | 7 | 18 | Heavy-write control |
| `0x01F0` | 8 | 18 | Heavy-write control |
| `0x01F6` | 6 | 17 | Heavy-write control |
| `0x965D` | 11 | 11 | Higher-bank register (DSC?) |
| `0x965C` | 8 | 8 | Paired with 0x965D |

The cluster at **0x1EB–0x1FB** is the SerDes adaptation state machine —
heavy read/write loops suggest the EQ/CDR convergence code.

## Init-time registers (lower-frequency, larger range)

| PHY addr | Pattern | What |
|---|---|---|
| `0x0223` / `0x0224` | First writes after entry | 16-bit value (R6:R7) stored at startup |
| `0x9434` / `0x9435` | Early writes | **Chip-ID handshake — stores 0x8474 here** |
| `0x9438` and following | Various | Init/version reporting block |
| `0x0100`–`0x011C` | Cluster of writes | **Initial configuration block** (28 regs) |
| `0x0172`–`0x01A7` | Cluster of writes | **Secondary init block** (~50 regs) |

## Higher-bank registers (above 0x8000)

The Warpcore PHY appears to have a paged register address space. Direct
DPTR loads above 0x8000 are observed:

| Addr | R | W | Notes |
|---|---|---|---|
| `0x9434/5` | early init | chip ID write |
| `0x9438`–`0x944A` | init | various init regs |
| `0x965C/D` | hot loop | DSC-related (digital signal conditioning?) |
| `0x9494` | init | |
| `0xFFFC/D` | reads only | program-memory ROM with chip ID `0x84 0x74` |

Address `0xFFFC`–`0xFFFD` is read with `MOVC A, @A+DPTR` — that's the
8051's program-memory read, not data memory. It reads from the firmware
image itself (last bytes contain chip ID `08 47 40 D1 02`).

## What this tells EdgeNOS

The firmware does the SerDes init "the right way" — touching ~30
registers in the 0x100s for setup, then running a tight EQ loop in
0x1EB–0x1FB during link bring-up. EdgeNOS doesn't have to replicate
this — the firmware does it autonomously once loaded.

But EdgeNOS DOES need to:
1. **Load the 32 KB firmware blob into PHY program RAM at 0x8000 via MDIO.**
   This is the `phy_ext_rom_boot=0` path in `config.bcm`.
2. **Trigger PHY CPU release-from-reset** (separate MDIO register write,
   probably to one of the 0x1Fx control regs).
3. **Wait for chip-ID echo** — the firmware writes its chip ID (0x8474)
   to register 0x9434 as a "ready" signal. EdgeNOS can poll 0x9434 to
   confirm the firmware booted successfully.

## Per-register access counts (sorted)

Top 30 by total access count:

```
0x01ec:    36 accesses (22R / 14W)
0x01eb:    39 accesses (21R / 18W)
0x01f8:    30 accesses
0x01f7:    34 accesses
0x01fa:    28 accesses
0x01f9:    28 accesses
0x01ef:    27 accesses
0x01fb:    22 accesses
0x01ee:    21 accesses
0x01f5:    27 accesses
0x01f1:    25 accesses
0x01f0:    26 accesses
0x01f6:    23 accesses
0x965d:    22 accesses
0x01f4:    17 accesses
0x965c:    16 accesses
0x01ed:    17 accesses
0x01f2:    13 accesses
0x01f3:    12 accesses
0x0225:    10 accesses
0x019a:     6 accesses
0x01a1:     6 accesses
0x01a2:     6 accesses
...
```

Full list in `phy_mmio_map.txt`.

## Open follow-ups

1. **Find the "PHY ready" handshake write.** Looking at addresses
   0x1EB–0x1F8 as candidates — the one written exactly once at startup
   then never again is the ready bit.
2. **Identify MDIO command handler.** There must be a loop that polls
   a register (probably `0x223` since it's the very first write at
   firmware entry) for incoming MDIO requests from the host BCM SDK.
3. **Trace the EQ adaptation loop.** Functions called from the
   0x1EB–0x1FB hot block — those are the SerDes EQ tuners.
4. **Map the upper bank (0x8xxx, 0x9xxx).** Probably switchbank
   registers selected via a page register at one of 0x1Fx.

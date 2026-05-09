# AS5610-52X — CPU → LED Data Path

**Date**: 2026-05-09
**Status**: Verified live on EdgeNOS at boot. All 52 LEDs driven from userspace.

---

This document describes how the host CPU (Freescale P2020 PowerPC) reaches the
front-panel LEDs of an AS5610-52X. Companion docs:
[LED_ARCHITECTURE.md](LED_ARCHITECTURE.md) (high-level overview),
[PAXB_SUBWINDOW_MECHANISM.md](PAXB_SUBWINDOW_MECHANISM.md) (the iProc bridge).

## 1. Physical chain

The 52 front-panel LEDs (48 SFP+ + 4 QSFP+) are bicolor (green + amber dies in
one package). They sit on a serial shift register chain wired into the BCM56846
ASIC. The ASIC clocks two bits per LED out of one of two pins — **amber first,
green second**. There are two independent chains driven by two independent
on-chip "LED processors":

- **LEDUP0 chain** — 32 SFP+ LEDs (drives swp9–swp40 in the panel mapping, each
  in some non-sequential PCB-wired order).
- **LEDUP1 chain** — 20 LEDs (4 QSFP + 16 SFP+ for swp1–swp8 and swp41–swp52).
  The chain output is 64 bits wide; the first 24 bits go to "phantom" slots
  that aren't physically wired (the original Cumulus program forces those to
  `1` with `pad_n_one`).

The CPU never bit-bangs LEDs. It writes a bytecode program once, then updates
a small RAM that the program reads.

## 2. CPU → BAR0 → PAXB → CMICm

The CPU is a Freescale P2020 (PowerPC e500v2). The BCM56846 hangs off PCIe and
exposes its registers via BAR0 (256 KB). Internally the BCM56846 sits behind
an iProc PCIe-AXI Bridge (PAXB). The AXI side hosts the CMICm peripherals (DMA,
MIIM, S-channel, **and the LED processors** at AXI 0x18001000–0x18002BFC).

PAXB divides BAR0 into eight 4 KB **sub-windows**, each with an AXI base
programmed via IMAP0_0..IMAP0_7 (BAR0+0x2C00..0x2C1C). Sub-windows 0–6 hold
fixed mappings. **Sub-window 7 is the dynamic one** — kernel code rewrites
IMAP0_7 to retarget it at the AXI page it currently needs to access. All LED
registers live above BAR0 + 0x1000, so they go through the sub-window remap
path.

A subtle quirk that took months to discover: **IMAP0_7 must be written via
PCI config-space accesses, not via BAR0 MMIO**. MMIO writes to that register
don't persist on this iProc revision.

In our custom BDE kernel module (`newnos/asic/bde/linux-kernel-bde.c`):

- `iproc_axi_read/write` checks an in-kernel sub-window cache. If the target
  page isn't already mapped, it writes IMAP0_7 via `pci_write_config_dword`,
  then issues `ioread32`/`iowrite32` at `BAR0 + 0x7000 + (axi_addr & 0xFFF)`.
- The `BDE_IOC_REG_READ/WRITE` ioctls take a BAR0 offset, auto-prepend
  `PAXB_AXI_BASE = 0x18000000`, and route through `iproc_axi_read/write` for
  any offset ≥ 0x1000.

That gives userspace a clean "write byte to 0x1400 + N*4 to set LED data RAM
byte N" abstraction — no PCI knowledge required.

## 3. CMIC LED processor block

Each LED processor is a tiny stack-machine microcontroller running a 256-byte
program at 30 Hz. Per processor:

| Region | BAR0 offset (LEDUP0 / LEDUP1) | Size | Purpose |
|---|---|---|---|
| `CTRL` | 0x1000 / 0x2000 | 4 B | bit 0 = enable; bits [3:1] inter-port scan delay; bits [7:4] start delay |
| `SCANCHAIN_ASSEMBLY_ST_ADDR` | 0x1008 / 0x2008 | 4 B | starting offset for scan assembly state |
| `PORT_ORDER_REMAP` | 0x0D00 / 0x0E00 | 9×4 B | port-number remap table (used by `port a` opcode) |
| `DATA_RAM` | 0x1400 / 0x2400 | 256×4 B | scratch RAM. 0x80–0x9F is conventionally the *linkscan area* the CPU updates with per-port link/activity bits; 0xA0–0xFF is free for the program |
| `PROGRAM_RAM` | 0x1800 / 0x2800 | 256×4 B | 256 bytes of bytecode |

Each register is 32-bit aligned but stores a single byte payload — high 24
bits ignored on write.

## 4. Execution model

Once enabled (CTRL bit 0 = 1), the processor runs its 256-byte program from
offset 0 to a `send N` instruction every ~33 ms. The instruction set is small
(≈30 opcodes) and stack-oriented:

- Two 8-bit data registers `a`, `b`.
- An output register that bits get **`pack`**ed into one at a time.
- `send N` shifts the assembled N-bit word out the serial chain.
- `pushst BIT` reads a per-port status bit (link up, activity, speed) — the
  hardware *implicitly* uses port number from register `a`. There's also a
  separate linkscan area in data RAM that the CPU updates.

Per-LED logic in Cumulus's stock program:

```
amber = 0   ; explicitly forced; could be driven
green = LINKEN AND NOT(activity AND blink_state)
```

where `blink_state` is a counter the program itself maintains in data RAM
(0xF0–0xF1). That single bit toggles every 3 ticks (10 Hz), so green flickers
off briefly during traffic.

## 5. The CPU's two roles

The CPU's interaction with the LED block is split:

1. **One-shot setup at boot.**
   `bmd_dev_download(unit, bmdDownloadPortLedController, hex, size)` stops both
   processors, writes 256 bytes into each `PROGRAM_RAM`, clears
   `DATA_RAM[0x80..0xFF]`, sets scan_assembly_st_addr to `0x4A`, sets enable.
   Cumulus loads two *different* programs into the two processors (different
   port-load tables).

2. **Continuous runtime updates.**
   The switchd linkscan task polls per-port status from the switch chip and
   writes one byte per port into `DATA_RAM[0x80 + port_num]`. Bits in that
   byte: bit 0 = link, bit 4 = TX-seen, bit 5 = RX-seen. The LED program reads
   it via `port a; ld b,LINKSCAN_P; add b,a; ld b,(b)` and `tst b,N`.

After that, the entire visual rendering — link-on, activity-blink, color
choice — happens autonomously on the LED processor at 30 Hz. The CPU is
uninvolved per frame.

## 6. The `leddance` userspace path (what we built)

Our tool exploits this: rather than have switchd push status, we replaced the
program with a 51-byte "passthrough" that does *no* port-status logic — it
just shifts the 64 bits in `DATA_RAM[0xA0..0xA7]` straight to the chain.
Userspace then writes patterns at whatever cadence we like through
`BDE_IOC_REG_WRITE`. Because each ioctl is one PCI MMIO write per byte,
refreshing all 16 chain bytes (8 per processor) is ~16 ioctls = sub-millisecond
— comfortably within the 30 Hz hardware tick.

Color encoding is the same as Cumulus's: bit `2N` = port-N amber, bit `2N+1`
= port-N green. Both lit ≈ yellow. The panel-port → (processor, chain-bit) map
is in `cumulus/platforms/accton.py` and is now embedded in `leddance.py`.

The passthrough program (51 bytes; see `newnos/utils/leddance/passthrough.asm`):

```asm
NUM_LEDS  equ  64
DATA_BASE equ  0xA0
DATA_END  equ  0xA8
PTR_P     equ  0xFE

main:
    ld   a,DATA_BASE
    ld   (PTR_P),a
loop:
    ld   a,(PTR_P)
    ld   b,a
    ld   b,(b)
    tst  b,0  push cy  pack
    tst  b,1  push cy  pack
    tst  b,2  push cy  pack
    tst  b,3  push cy  pack
    tst  b,4  push cy  pack
    tst  b,5  push cy  pack
    tst  b,6  push cy  pack
    tst  b,7  push cy  pack
    ld   a,(PTR_P)
    inc  a
    ld   (PTR_P),a
    cmp  a,DATA_END
    jnz  loop
    send NUM_LEDS
```

Compile with Cumulus's PPC `ledasm` (extracted at
`extracted/2.5.0-powerpc/rootfs/usr/lib/cumulus/ledasm`). Runs natively on the
switch.

## 7. End-to-end summary

```
userspace tool
  └─ ioctl(BDE_IOC_REG_WRITE, addr=0x1400+N*4, val=byte)
       └─ kernel BDE module
            └─ iproc_axi_write(0x18001400 + N*4)
                 ├─ pci_write_config_dword(IMAP0_7, page|VALID)   [if cache miss]
                 └─ iowrite32(BAR0 + 0x7000 + offset, val)
                      └─ PCIe TLP → BCM56846 PAXB → CMICm bus → LEDUP0 DATA_RAM[N]
                           └─ at next 30Hz tick, LED processor runs program,
                              shifts 64 bits to serial chain → 52 front-panel LEDs
```

## 8. Verified panel-port map (front-panel label → LED chain location)

Source: `cumulus/platforms/accton.py` `AcctonAS5610_52XSwitch.ports`. Each entry
gives `(LED processor, chain-bit-offset)` where the chain-bit-offset is the
*amber* bit (green is +1).

| swp | proc | bit | swp | proc | bit | swp | proc | bit | swp | proc | bit |
|-----|------|-----|-----|------|-----|-----|------|-----|-----|------|-----|
| 1   | 1 | 34 | 14  | 0 | 48 | 27  | 0 | 34 | 40  | 0 | 16 |
| 2   | 1 | 32 | 15  | 0 | 54 | 28  | 0 | 32 | 41  | 1 | 44 |
| 3   | 1 | 38 | 16  | 0 | 52 | 29  | 0 | 30 | 42  | 1 | 42 |
| 4   | 1 | 36 | 17  | 0 | 46 | 30  | 0 | 28 | 43  | 1 | 40 |
| 5   | 1 | 62 | 18  | 0 | 44 | 31  | 0 | 26 | 44  | 1 | 46 |
| 6   | 1 | 60 | 19  | 0 | 42 | 32  | 0 | 24 | 45  | 1 | 52 |
| 7   | 1 | 58 | 20  | 0 | 40 | 33  | 0 | 14 | 46  | 1 | 50 |
| 8   | 1 | 56 | 21  | 0 | 62 | 34  | 0 | 8  | 47  | 1 | 48 |
| 9   | 0 | 2  | 22  | 0 | 60 | 35  | 0 | 10 | 48  | 1 | 54 |
| 10  | 0 | 0  | 23  | 0 | 58 | 36  | 0 | 12 | 49  | 1 | 26 |
| 11  | 0 | 6  | 24  | 0 | 56 | 37  | 0 | 22 | 50  | 1 | 24 |
| 12  | 0 | 4  | 25  | 0 | 38 | 38  | 0 | 20 | 51  | 1 | 30 |
| 13  | 0 | 50 | 26  | 0 | 36 | 39  | 0 | 18 | 52  | 1 | 28 |

This was verified empirically: writing bit 0 of `LEDUP0_DATA_RAM[0xA0]` lit
swp10 amber; bit 1 lit swp10 green.

## References

- `newnos/utils/leddance/leddance.py` — the userspace tool
- `newnos/utils/leddance/passthrough.asm` — the bytecode
- `newnos/asic/bde/linux-kernel-bde.c` — sub-window translation, ioctls
- `newnos/asic/openmdk/cdk/include/cdk/chip/bcm56840_a0_defs.h` — register offsets
- `extracted/2.5.0-powerpc/rootfs/usr/lib/cumulus/ledasm` — LED bytecode assembler (PPC)
- `extracted/2.5.1-powerpc/.../cumulus/ledup.py` — Cumulus LED program generator (high-level)
- `extracted/2.5.1-powerpc/.../cumulus/platforms/accton.py` — panel-port-to-chain table
- `traces/led0.asm`, `traces/led1.asm` — disassembled Cumulus LED programs

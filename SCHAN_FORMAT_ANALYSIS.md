# S-Channel Format Analysis (Path B 2.3)

**Date**: 2026-02-19  
**Status**: PARTIAL → HAVE (command word format decoded)  
**Functions**: FUN_00703dc0, FUN_007042f0, FUN_00704790, FUN_00704784

---

## S-Channel Command Word Format

### Key Function: FUN_00703dc0

**Location**: `libopennsl.so.1` at `0x00703dc0`  
**Purpose**: Builds S-Channel command word by ORing `0x2800` into high bits

**Assembly (key path)**:
```asm
00703ed4 lwz r9,0x0(r4)          ; Load value from *r4
00703ed8 rlwinm r9,r9,0x0,0x15,0x1f  ; Mask bits 0-20 (keep lower 21 bits)
00703edc oris r9,r9,0x2800        ; OR 0x2800 into bits 16-29
00703ee0 stw r9,0x0(r4)           ; Store command word back to *r4
```

**Command Word Bit Layout**:
```
Bits 0-15:   Lower data/address (from input, masked)
Bits 16-29:  0x2800 pattern (10100000000000 binary) - S-Channel identifier
Bits 30-31:  Upper bits from input
```

**PowerPC `oris` instruction**: `oris r9,r9,0x2800` = `r9 = r9 | (0x2800 << 16)` = `r9 = r9 | 0x28000000`

**Example command word**: `0x2800XXXX` where `XXXX` is the lower 16 bits from input.

---

## Call Chain

### Callers of FUN_00703dc0

| Function | Address | Parameters | Purpose |
|----------|---------|------------|---------|
| **FUN_007042f0** | 0x007042f0 | r3=unit, r4=output ptr, r5=1, r6=4 | Main S-Chan builder (complex path) |
| **FUN_00704790** | 0x00704790 | r5=0, r6=4 → calls FUN_00703dc0 | Simple wrapper (r5=0) |
| **FUN_00704784** | 0x00704784 | r5=1, r6=4 → calls FUN_00703dc0 | Simple wrapper (r5=1) |

**FUN_00704790** (simple wrapper):
```asm
00704790 li r5,0x0      ; Set r5=0
00704794 li r6,0x4       ; Set r6=4
00704798 b 0x00703dc0    ; Branch to FUN_00703dc0
```

**FUN_00704784** (simple wrapper):
```asm
00704784 li r5,0x1      ; Set r5=1
00704788 li r6,0x4      ; Set r6=4
0070478c b 0x00703dc0   ; Branch to FUN_00703dc0
```

**FUN_007042f0** (main path):
- More complex: loads r27 from `[r30-0x7ff8]` and from `0x018120a0`
- Calls `0x018124a8`, `0x018120a0`, `FUN_0070479c`
- r4 for FUN_00703dc0 likely comes from per-unit struct (r27 or similar)

---

## FUN_00703dc0 Full Logic

**Parameters**:
- `r3`: Unit number
- `r4`: Pointer to output command word (in/out)
- `r5`: Flag (0 or 1) - affects behavior
- `r6`: Constant (always 4)

**Key paths**:
1. **Path at 0x703ed4-0x703ee0**: Loads from *r4, masks bits 0-20, ORs 0x2800, stores back
2. **Path at 0x703ec8-0x703ecc**: Masks bits 0-20, stores to *r4 (no 0x2800 OR)
3. **Path at 0x703ee8-0x703ef0**: Masks bits 0-20, sets r9=0xa, stores to *r4

**Conditional logic**:
- Checks unit state flags (`[r30-0x7ffc]`, `0x20(r9)`, bit 0x2000)
- Validates input value in *r4 (must be >= 0, <= 0xff)
- Uses r5 flag to select lookup path (0x703ef8 vs 0x703e80)

---

## S-Channel Register

**Register**: `CMIC_CMC0_SCHAN_CTRL` at offset `0x32800` (from CMIC base `0x04000000`)  
**Full address**: `0x04032800`

**Operation** (from SDK_REGISTER_MAP.md):
1. Write command word to S-Channel command register
2. Poll status register for completion
3. Read result from data register

**Command word format**: `0x2800XXXX` where:
- `0x2800` = S-Channel identifier (bits 16-29)
- `XXXX` = Command-specific data (bits 0-15)

---

## Usage Context

**From SCHAN_AND_L2_ANALYSIS.md**:
- FUN_00703dc0 is called during table writes (L2, L3, etc.)
- The command word is written to S-Channel register to trigger ASIC memory writes
- This is the mechanism for writing table entries (L2_USER_ENTRY, L3_DEFIP, etc.)

**Next steps**:
1. Find where FUN_007042f0/FUN_00704790/FUN_00704784 are called from
2. Trace how the command word is written to register 0x32800
3. Map command word data bits to table entry fields (L2 MAC/VLAN/port, L3 route, etc.)

---

## References

- **S-Channel analysis**: [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md)
- **Register map**: [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md)
- **Function dumps**: `libopennsl-dump-0703dc0.txt`, `libopennsl-dump-07042f0.txt`, `libopennsl-dump-0704790.txt`, `libopennsl-dump-0704784.txt`

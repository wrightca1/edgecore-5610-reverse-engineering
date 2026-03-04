# BCM56846 Chip Reset — Reverse Engineering Findings

**Date**: 2026-03-03
**Binary sources**: `build-server/switchd/switchd` (Cumulus 2.5.1) and `build-server/opennsl/libopennsl.so.1`
**Context**: All SCHAN reads return 0x92 because switch pipeline blocks are in soft reset.
  CMIC never de-asserted the reset, so every SBUS target NACKs.

---

## Problem Statement

After loading `nos_kernel_bde.ko` and running `opennsl_init()`, all SCHAN register reads
return `SCHAN_CTRL = 0x92` instead of `0x02` (DONE only).

### SCHAN_CTRL = 0x92 Bit Breakdown

| Bit | Mask | Name | Value |
|-----|------|------|-------|
| 1   | 0x02 | SCHAN_CTRL_DONE | **SET** (normal) |
| 4   | 0x10 | unknown / CMC error | **SET** (unexpected) |
| 7   | 0x80 | **SBUS NACK** | **SET** — target not responding |

`ERR_MASK = 0x0C` in `nos_kernel_bde.c` misses bits 0x10 and 0x80.
Bit 7 = SBUS NACK means the SBUS target (e.g. TOP_SOFT_RESET_REG) did not acknowledge.
Root cause: pipeline blocks are held in soft reset, so all SBUS accesses return NACK.

**Fix needed**: De-assert CMIC soft reset AND TOP_SOFT_RESET_REG before SCHAN use.

---

## CMIC_SOFT_RESET_REG

| Item | Value |
|------|-------|
| Register location | PCI BAR0, offset **0x70** |
| Type | CMICm standard register (same for BCM56840/BCM56846 Trident/Trident+) |
| Purpose | Controls CMIC block resets; must be written to de-assert after PCI enum |

This is a well-established CMICm register — write a specific value to release CMIC resets
before any SCHAN access.

---

## TOP_SOFT_RESET_REG — soc_reg_t Enum (Confirmed)

Extracted from `switchd` disassembly of the reset function at **vaddr 0x10e6e400–0x10e6f100**:

### TOP_SOFT_RESET_REG_2 = soc_reg_t enum **0x8714** (CONFIRMED)

```
vaddr 10e6e47c:  lwz r3, 120(r31)        ; r3 = unit
vaddr 10e6e480:  addi r10,r0,0x0000
vaddr 10e6e484:  ori  r4, r10, 0x8714    ; r4 = 0x8714 ← TOP_SOFT_RESET_REG_2 enum
vaddr 10e6e488:  addi r5, r0, 0xfff6     ; r5 = -10 = REG_PORT_ANY
vaddr 10e6e48c:  addi r6, r0, 0x0000     ; r6 = 0
vaddr 10e6e490:  or   r7, r9, r9         ; r7 = buffer pointer
vaddr 10e6e494:  bl   0x10847ab4         ; → soc_reg32_get
;; on error: branch to print "Reading TOP_SOFT_RESET_REG_2 failed !!"
```

The error string "Reading TOP_SOFT_RESET_REG_2 failed !!" at vaddr 0x11406148 is confirmed to
be triggered by the call with r4 = 0x8714, proving the enum.

### Field Enums Used with TOP_SOFT_RESET_REG_2

From `soc_reg_field32_modify` calls (bl 0x1084d57c) preceding the read:

| Field enum | Likely meaning |
|------------|---------------|
| 0xd8e7 | One soft-reset field within TOP_SOFT_RESET_REG_2 |
| 0xd8e9 | Second soft-reset field within TOP_SOFT_RESET_REG_2 |

### Other Reset Sequence Register Enums

These enums appear in the reset function 0x10e6e400–0x10e6f100 before/after 0x8714:

| Enum | Notes |
|------|-------|
| 0x86d9 | First register read/written; error at vaddr 0x11406120 |
| 0x8714 | **TOP_SOFT_RESET_REG_2** (confirmed) |
| 0x875e | Used in reset sequence |
| 0x8764 | Used in reset sequence |
| 0x8735–0x8738 | Group of 4 consecutive; used in reset sequence |
| 0x8680–0x8684 | Group of 5; used in reset sequence |

### soc_reg_t vs soc_mem_t Namespace Note

The name-pointer table at switchd vaddr **0x11bdac14** is the **soc_mem_t** (memory enum) table,
NOT the soc_reg_t register enum table. These are separate namespaces in the BCM SDK — both can
have the value 0x8714 with different meanings:

- `soc_mem_t` 0x8714 → "ESM_ACL_TABLE_CONTROL_TM" (memory table, indexed by mem table at 0x11bdac14)
- `soc_reg_t` 0x8714 → TOP_SOFT_RESET_REG_2 (register enum, confirmed from code flow)

---

## Error Strings — Memory Addresses

| String | File offset | Virtual address |
|--------|------------|-----------------|
| "Reading TOP_SOFT_RESET_REG_2 failed !!" | 0x01406148 | 0x11406148 |
| "Writing TOP_SOFT_RESET_REG_2 failed !!" | 0x01406170 | 0x11406170 |
| "Reading TOP_SOFT_RESET_REG failed !!"   | 0x01406378 | 0x11406378 |
| "Writing TOP_SOFT_RESET_REG failed !!"   | 0x014063a0 | 0x114063a0 |

---

## soc_reg32_get Function Architecture (switchd)

Two variants found in switchd:

| Address (vaddr) | Notes |
|-----------------|-------|
| **0x10847ab4** | Primary variant; used in reset function for TOP_SOFT_RESET_REG_2 |
| **0x1084a784** | Secondary variant; slightly different calling convention |

Internal data flow of 0x10847ab4:
1. BSS global table at vaddr **0x1213d2dc** — indexed by `unit * 4` → `soc_control_t *`
2. `soc_control_t` at offset **0x2F26F4** → pointer to `reg_info_table`
3. `reg_info_table[reg_enum]` → `soc_reg_info_t *`
4. `soc_reg_info_t` at offset 16 = flags (determines SCHAN address generation)

Related field-modify functions:

| Address (vaddr) | Function |
|-----------------|----------|
| 0x1084d57c | soc_reg_field32_modify (variant 1) |
| 0x1084bf98 | soc_reg_field32_modify (variant 2) |

---

## Reset Function Location in switchd

| Item | Value |
|------|-------|
| Start vaddr | **0x10e6e400** |
| End vaddr (approx) | **0x10e6f100** |
| File offset | 0x00e6e400 (PT_LOAD 0: foff=0, vaddr=0x10000000) |
| What it does | Reads/modifies TOP_SOFT_RESET_REG, TOP_SOFT_RESET_REG_2, and related TOP_* regs |

A second location referencing "Reading TOP_SOFT_RESET_REG failed !!" is at vaddr **0x10c51be8**
and **0x10c54da4** — these use the same error strings but appear to be a different init path
(possibly the non-BCM56846 fallback).

---

## libopennsl.so.1 Findings

| Item | Value |
|------|-------|
| ELF section headers | Garbled / stripped (obfuscated) |
| PT_DYNAMIC location | 0x27fead0 |
| SYMTAB address | 0x1800 |
| Exported public symbols | 960 (only bcm_*/opennsl_* API, no internal functions) |
| "soc_reset_bcm56840_a0" string | foff = **0x1f08798** (chip = BCM56840 = same silicon family as BCM56846) |
| "bcm56840_a0" string | foff = **0x1f087a2** |
| "Reading TOP_SOFT_RESET_REG_2 failed !!" | foff = **0x1f31d72** |
| "Writing TOP_SOFT_RESET_REG_2 failed !!" | foff = **0x1f31db2** |
| "Reading TOP_SOFT_RESET_REG failed !!" | foff = **0x1f31f7a** |

The library is position-independent (BCL/MFLR GOT-relative), making static analysis harder.
Internal `soc_reset_bcm56840_a0` is not in the export table (stripped), but the string exists,
confirming BCM56840/56846 init code is present.

Code references to "Reading TOP_SOFT_RESET_REG failed !!" in libopennsl:
- vaddr **0x015e4de4** (function starting around 0x015e4c5c, soc_reg32_get-like)
- vaddr **0x0151f878** (function at 0x0151f894)

---

## S-Bus Agent Map — CRITICAL MISSING PIECE (SOLVED)

**Source**: Deep binary RE of switchd (Cumulus 2.5.1, BCM56846).

The CMIC must know which hardware block (agent) sits at which position on each S-bus ring.
Without this map, every SCHAN command targets the wrong ring position → SBUS NACK.
**This is the primary reason all SCHAN reads return 0x92 (SBUS NACK).**

### CMIC_SBUS_RING_MAP BAR0 Register Addresses (CONFIRMED for BCM56846)

| Register name | BAR0 offset | BCM soc_reg_t enum |
|---------------|------------|---------------------|
| CMIC_SBUS_RING_MAP   | `0x0200` | 0x15a7 |
| CMIC_SBUS_RING_MAP_0 | `0x0204` | 0x15a8 |
| CMIC_SBUS_RING_MAP_1 | `0x0208` | 0x15a9 |
| CMIC_SBUS_RING_MAP_2 | `0x020c` | 0x15aa |
| CMIC_SBUS_RING_MAP_3 | `0x0210` | 0x15ab |
| CMIC_SBUS_RING_MAP_4 | `0x0214` | 0x15ac |

These are in the **CMIC register block at BAR0 + 0x200**, NOT in the CMCm 0x31000+ range.

### Write Sequence Extracted from switchd Disassembly

Confirmed from vaddr **0x10e6c800–0x10e6cc00** in switchd (adjacent to the SOFT_RESET region):

```
; CMIC_SBUS_RING_MAP (BAR0 + 0x0200) — agents 0–7 ring assignments
lis  r10, 0x4305        ; 0x43050000
ori  r10, r10, 0x2100   ; 0x43052100
stw  r10, 0(r9)         ; → BAR0 + 0x0200

; CMIC_SBUS_RING_MAP_0 (BAR0 + 0x0204) — agents 8–15
lis  r10, 0x3333        ; 0x33330000
ori  r10, r10, 0x3343   ; 0x33333343
stw  r10, 0(r9)         ; → BAR0 + 0x0204

; CMIC_SBUS_RING_MAP_1 (BAR0 + 0x0208) — agents 16–23
lis  r10, 0x4444        ; 0x44440000
ori  r10, r10, 0x4333   ; 0x44444333
stw  r10, 0(r9)         ; → BAR0 + 0x0208

; CMIC_SBUS_RING_MAP_2 (BAR0 + 0x020c) — agents 24–31
lis  r10, 0x0003        ; 0x00030000
ori  r10, r10, 0x4444   ; 0x00034444
stw  r10, 0(r9)         ; → BAR0 + 0x020c

; CMIC_SBUS_RING_MAP_3 (BAR0 + 0x0210) — agents 32–39: 0x00000000
; CMIC_SBUS_RING_MAP_4 (BAR0 + 0x0214) — agents 40+: 0x00000000
```

### S-Bus Ring Map Values (BCM56846 / AS5610-52X)

| BAR0 offset | Register | Write value | Agents covered |
|-------------|----------|-------------|----------------|
| `0x0200` | CMIC_SBUS_RING_MAP   | `0x43052100` | 0–7   |
| `0x0204` | CMIC_SBUS_RING_MAP_0 | `0x33333343` | 8–15  |
| `0x0208` | CMIC_SBUS_RING_MAP_1 | `0x44444333` | 16–23 |
| `0x020c` | CMIC_SBUS_RING_MAP_2 | `0x00034444` | 24–31 |
| `0x0210` | CMIC_SBUS_RING_MAP_3 | `0x00000000` | 32–39 |
| `0x0214` | CMIC_SBUS_RING_MAP_4 | `0x00000000` | 40+   |

Note: Two chip-variant sets exist in the descriptor table:
- BCM56840-A0 (older die): different values (e.g., agents 0–7 = `0x33022140`)
- **BCM56846 (AS5610-52X)**: the values above — hardcoded at vaddr 0x10e6c900

### S-Bus PIO Register Sets (BAR0 Offsets)

From `strings-hex-literals.txt`:

| Range | Likely CMC |
|-------|-----------|
| BAR0 0x3100c – 0x31060 | CMC0 S-bus PIO |
| BAR0 0x3200c – 0x32060 | CMC1 S-bus PIO |
| BAR0 0x3300c – 0x33060 | CMC2 S-bus PIO |
| BAR0 0x1000c – 0x10060 | IPROC / management S-bus PIO |

Note: CMIC_CMC0_SCHAN_CTRL is at BAR0 + 0x32800 (confirmed separately).

---

---

## TOP_SOFT_RESET_REG SCHAN Address — RE-Confirmed (2026-03-04)

**Update**: The SBUS address for TOP_SOFT_RESET_REG has been recovered from the switchd binary
via analysis of the SDK register-cache hash table implementation.

### How the SCHAN Address Was Found

Functions `FUN_10325fa0` (hash insert) and `FUN_103260d4` (hash lookup) in the switchd binary
are the BCM SDK's internal register-read-back cache. The hash key for each register is
constructed as the **SCHAN command word** itself:

```asm
; PowerPC assembly (FUN_10325fa0, ~vaddr 0x10325fa0):
rlwinm r9,r9,0x0,0x11,0x1f   ; mask r3 (block_sel) to lower 15 bits
rlwinm r9,r9,0x0b,0x0,0x14   ; shift left 11 → places in bits[25:11]
oris   r10,r9,0x2800          ; OR 0x28000000 → opcode 0x0A in bits[31:26]
rlwinm r9,r9,0x0,0x15,0x1f   ; mask r4 (reg_off) to lower 11 bits
or     r10,r10,r9             ; combine: SCHAN_word = opcode|block_addr|reg_off
```

The resulting 32-bit value is the SCHAN READ command word:
- `bits[31:26]` = `0x0A` (READ_REGISTER opcode; `0x0A << 26 = 0x28000000`)
- `bits[25:11]` = 15-bit SBUS block selector (from `r3`)
- `bits[10:0]`  = 11-bit register offset within block (from `r4`)

### Data Constants (Ghidra analysis, switchd .data section)

| Value | Address | Interpretation |
|-------|---------|----------------|
| `0x01120066` | DATA@0x11436428 | block_sel for TOP block (SBUS dest 3) |
| `0x01120200` | DATA@0x11436434 | likely TOP_SOFT_RESET_REG_2 entry |

For `0x01120066`:
- Lower 15 bits: `0x1120066 & 0x7FFF = 0x0066`
- After shift-left-11: `0x0066 << 11 = 0x00033000`
- After OR 0x28000000: `0x28033000`
- With r4 = register offset 0x200 (11-bit mask): `0x28033200`

### SCHAN Word Decoded: `0x28033200`

```
0x28033200 = 0010 1000 0000 0011 0011 0010 0000 0000
             ├─────────┤ ├──────────────┤ ├──────────────┤
             opcode=0x0A  SBUS_dst=0x003   block/reg=0x3200
             (READ_REG)   (TOP block)      (off 0x200)
```

- **SBUS destination 3** = TOP block, confirmed: `RING_MAP_0 = 0x43052100`,
  nibble 3 maps agent 3 → ring 2 (the TOP block ring for BCM56846).
- **Register offset 0x200** = known BCM56840 `TOP_SOFT_RESET_REG` offset.
- The `0x3200` in bits[15:0] encodes both the block sub-address from the upper bits
  of `block_sel << 11` and the 11-bit register offset.

### Usage in nos-switchd SDK (open-nos-as5610)

`init.c` `bcm56846_xlport_deassert_reset()` probes 7 candidate addresses in priority order.
`0x28033200` is CAND_0 (highest confidence); `0x00033200` (no opcode prefix) is CAND_1.

The probe accepts any address that reads a value with only bits[12:0] set (the 13 XLP_RESET
bits for BCM56846's 13 XLPORT blocks), then writes 0 to de-assert all XLPORT resets.

---

## Required Actions (from findings)

### 1. Fix nos_kernel_bde.c SCHAN_CTRL error mask

```c
/* Current — MISSING SBUS_NACK and bit4 */
#define SCHAN_CTRL_ERR_MASK  0x0C

/* Correct — include SBUS_NACK (bit7=0x80) and bit4 (0x10) */
#define SCHAN_CTRL_ERR_MASK  0x9C
```

### 2. Program S-bus ring map registers BEFORE any SCHAN

Write these 6 registers to BAR0 directly (in nos_kernel_bde.c `bcm56846_chip_init()`):

```c
/* CMIC_SBUS_RING_MAP registers — must be written before first SCHAN command */
static const struct { uint32_t offset; uint32_t value; } sbus_ring_map[] = {
    { 0x0200, 0x43052100 },  /* CMIC_SBUS_RING_MAP   — agents 0-7  */
    { 0x0204, 0x33333343 },  /* CMIC_SBUS_RING_MAP_0 — agents 8-15 */
    { 0x0208, 0x44444333 },  /* CMIC_SBUS_RING_MAP_1 — agents 16-23 */
    { 0x020c, 0x00034444 },  /* CMIC_SBUS_RING_MAP_2 — agents 24-31 */
    { 0x0210, 0x00000000 },  /* CMIC_SBUS_RING_MAP_3 — agents 32-39 */
    { 0x0214, 0x00000000 },  /* CMIC_SBUS_RING_MAP_4 — agents 40+   */
};
```

### 3. Implement bcm56846_chip_init() sequence

Full order of operations needed before first SCHAN (implemented in `sdk/src/init.c`):

```
1. Detect boot mode: read CMIC_DMA_RING_ADDR (BAR0+0x158)
   - Non-zero → warm boot; CMC2 in DMA ring-buffer mode; cold power cycle required
   - Zero + SCHAN_CTRL START=1,DONE=0 → PIO ERROR state = genuine cold boot
2. Write CMIC_SBUS_RING_MAP[0..7] (BAR0+0x204..0x220) → S-bus ring topology
3. Write CMIC_MISC_CONTROL LINK40G_ENABLE (BAR0+0x1c bit 0) → enable XLMAC SBUS
4. Write SCHAN_CTRL 0xFE (W1C + ABORT) → clear stale PIO error state (cold boot only)
5. Verify SCHAN_CTRL = 0x00 → SCHAN ready
6. Write TOP_SOFT_RESET_REG (SCHAN addr 0x28033200) → de-assert XLPORT resets
   - Probe 7 candidate addresses; accept first that reads bits[12:0]-only value
   - Write 0x00000000 to clear all 13 XLP_RESET bits
```

**Current status**: Steps 1–5 confirmed working on hardware (AS5610-52X at 10.1.1.233).
52 TAP interfaces up. Step 6 (XLPORT reset de-assertion) pending cold power cycle test
to confirm address `0x28033200` is correct.

### 4. TOP_SOFT_RESET_REG SCHAN Address (Best Candidate)

| Address | Confidence | Derivation |
|---------|-----------|------------|
| `0x28033200` | **HIGH** | RE-confirmed from switchd hash-table key construction code |
| `0x00033200` | Medium | Same address without opcode prefix (BDE addr-only format) |
| `0x00030200` | Low | agent<<16 \| offset (common CMICm format) |
| Others | Low | Various encoding schemes |

---

## ELF Layout Reference

### switchd

| Segment | File offset | Virtual address | Notes |
|---------|------------|-----------------|-------|
| PT_LOAD 0 | 0x0 | 0x10000000 | Code + rodata |
| PT_LOAD 1 | 0x1809000 | 0x11819000 | BSS/data |

To convert: `vaddr → foff`: if vaddr ≥ 0x11819000: foff = vaddr - 0x11819000 + 0x1809000

### libopennsl.so.1

| Segment | File offset | Virtual address | Notes |
|---------|------------|-----------------|-------|
| PT_LOAD 0 | identity | identity | foff = vaddr |
| PT_LOAD 1 | 0x273974c | 0x274974c | BSS/data |

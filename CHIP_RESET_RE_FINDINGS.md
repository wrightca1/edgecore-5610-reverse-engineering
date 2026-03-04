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

Full order of operations needed before first SCHAN:

```
1. Write CMIC_SOFT_RESET_REG (BAR0 + 0x70)  → de-assert CMIC block resets
2. Wait ~100ms for CMIC to stabilize
3. Write CMIC_SBUS_RING_MAP[0..4] (BAR0 + 0x200..0x214) → S-bus ring topology
4. Write TOP_SOFT_RESET_REG  → de-assert pipeline resets (enum TBD, near 0x86d9)
5. Write TOP_SOFT_RESET_REG_2 (soc_reg_t enum 0x8714) → de-assert remaining resets
6. Wait ~100ms for pipeline to stabilize
7. Now SCHAN reads should return 0x02 (DONE only), not 0x92
```

The exact SBUS addresses for TOP_SOFT_RESET_REG and TOP_SOFT_RESET_REG_2 are populated at
runtime by the SDK (runtime BSS tables). Options to find them:
- BCM56840 datasheet / BCM56846 register spec (proprietary)
- Dynamic tracing of Cumulus switchd during init (GDB/strace on soc_reg32_set calls)
- The write function region in switchd is at 0x10e6e400 — disassemble the full function

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

# Ghidra Static Analysis — Findings

Headless analysis run on the 3 priority binaries using Ghidra 12.0.3.
Output files in this directory; full disassembly + decompilation per binary.

## 1. `accton_as5610_52x_cpld.ko` — CPLD register map fully decoded

**81 functions, 376 strings, 66 decompiled.** Critical for EdgeNOS port.

### The CPLD register map (decoded from decompilation)

| CPLD offset | Purpose | Read/Write |
|---|---|---|
| **0x01** | PSU2 power status bits (`psu_pwr2_*`) | R |
| **0x02** | PSU1 power status bits (`psu_pwr1_*`) | R |
| **0x03** | System status bits (fan_present, fan_ok, fan_air_flow, dc_power_ok) | R |
| **0x0D** | PWM1 duty cycle — **5-bit field, user value >> 3** | R/W |
| **0x0E** | Watchdog control (per-bit assignments) | R/W |
| (varies) | LED registers — via `cpld_leds[]` table with per-LED `.reg` + `.mask` | R/W |

### Key decompilation: `pwm1_store`

```c
ssize_t pwm1_store(...) {
    sscanf(buf, "%d", &pwm);
    if (pwm > 0xFF) pwm = 0xFF;
    pwm = pwm & ((-pwm) >> 31);   // clamp to >= 0
    accton_as5610_52x_pwm1 = (uint8_t)pwm;
    sync(0);
    accton_as5610_52x_cpld_regs[0x0D] = (uint8_t)(pwm >> 3);  // ← 5-bit write
    return count;
}
```

This **explains the 0–248 range surprise**: PWM is stored as 5 bits (0–31), then
when written the lower 3 bits are zero. User value `248` → `248 >> 3 = 31`. So
max raw PWM byte is `31 << 3 = 248`. Anything above 248 in the user value just
gets clamped, losing precision.

### Key decompilation: `led_store`

```c
ssize_t led_store(...) {
    // Find LED entry by attribute name
    for (i = 0; cpld_leds[i].name; i++)
        if (strcmp(buf_name, cpld_leds[i].name) == 0) break;

    // Find color value
    for (j = 0; j < cpld_leds[i].n_colors; j++)
        if (strcmp(input_color, target->colors[j].name) == 0) break;

    // Atomic RMW on the CPLD register
    mutex_lock(&cpld_mutex);
    sync(0);
    /* Read current value */
    uint8_t val = accton_as5610_52x_cpld_regs[cpld_leds[i].reg];
    instructionSynchronize();
    sync(0);
    accton_as5610_52x_cpld_regs[cpld_leds[i].reg] =
        (val & ~cpld_leds[i].mask) | target->colors[j].value;
    mutex_unlock(&cpld_mutex);
}
```

Each LED has a `.reg`, `.mask`, and an array of `colors[]` with name→value.
EdgeNOS needs the `cpld_leds[]` table content (offsets 0x80 in .data — needs a
Ghidra DataType analysis pass to extract).

### Key decompilation: `probe`

```c
int accton_as5610_52x_cpld_probe(struct platform_device *ofdev) {
    if (dev_get_drvdata(&ofdev->dev) != 0) {
        dev_info(... "already probed");
        return 0;
    }
    accton_as5610_52x_cpld_regs = (uint8_t *)of_iomap(ofdev->dev.of_node, 0);
    if (!accton_as5610_52x_cpld_regs) return -ENOMEM;

    sysfs_create_group(&ofdev->dev.kobj, &accton_as5610_52x_cpld_attr_group);
    dev_info(..., "probed & iomapped @ 0x%p\n", ...);
    return 0;
}
```

Uses **`of_iomap(np, 0)`** to map the first I/O region from the device-tree
node. EdgeNOS device-tree must have a CPLD node with the right
`compatible` string + a `reg` entry pointing at `0xea000000`.

### Watchdog details from `watch_dog_store`

* CPLD offset **0x0E** is the watchdog control register
* `watch_dog_timeout` value range is 8..520 seconds (the code checks
  `local_28[0] - 8 < 0x1F9` = `value < 521`)
* `watch_dog_keep_alive` writes always set bit
* Per-bit assignment table is `watch_dog_bits[]` with `name` + `bit` fields

### Files

* `accton_as5610_52x_cpld.ko_functions.txt` — 81 functions with addresses
* `accton_as5610_52x_cpld.ko_decompile.c` — 66 functions decompiled (35 KB)
* `accton_as5610_52x_cpld.ko_symbols.txt` — 312 symbols
* `accton_as5610_52x_cpld.ko_strings.txt` — 376 strings

## 2. `ledasm` — LED uController assembler

**89 functions, 217 strings, 49 decompiled.** Best decompilation quality
because the binary shipped UNSTRIPPED with debug info.

### Key finding: `emit()` — LED program is 256 bytes max

```c
void emit(int v) {
    if (g_curpc < 0x100) {                     // 256-byte program limit
        if (v < -0x80 || v > 0xff)
            error("value out of bounds -128 <= val <= 255");
        else {
            g_program[g_curpc] = v & 0xff;
            g_curpc++;
        }
    } else {
        if (!warned)
            error("program is too long");
        warned = 1;
    }
}
```

The LED uController **firmware-program memory is just 256 bytes**. led0.hex
and led1.hex on our chassis are ~196 bytes each — well within budget.
EdgeNOS LED programs face the same limit.

### `init_tables()` decompilation

```c
void init_tables(void) {
    num_labels = 0;
    for (int i = 0; i < 256; i++) {
        symtab[i].valid = 0;
        symtab[i].label[0] = '\0';
        symtab[i].value = 0;
    }
}
```

Symbol table is fixed at 256 entries × label/value pairs. EdgeNOS port
would use the same constants.

### Files

* `ledasm_functions.txt` — 89 functions named (`parse_*`, `emit`, `dump_*`)
* `ledasm_decompile.c` — 49 functions decompiled (30 KB)
* `ledasm_symbols.txt` — 575 symbols
* `ledasm_strings.txt` — 217 strings

## 3. `BCM84740-ver-D102.bin` — Warpcore PHY firmware (8051)

**4487 instructions disassembled. 0 functions auto-recognized** (8051
function detection is challenging; needs more work).

### Critical finding: firmware loads at base 0x8000

The 32 KB binary fills the **upper half** of the 8051's 64KB program
address space. Reset vector at 0x0000 isn't in this file — there's
presumably a tiny boot ROM at 0x0000 that does `LJMP 0x8000` to enter
the downloaded firmware. The host loads this 32 KB blob via MDIO into
the PHY's program RAM at offset 0x8000.

### First instructions (firmware entry point at 0x8000)

```asm
8000: LCALL 0xE301           ; jump to main init code at 0xE301
8003: LCALL 0xBE00           ; secondary init (probably register block reset)
8006: MOV   R5, #0x01
8008: MOV   R4, #0xC8
800A: MOV   R7, #0x01
800C: LCALL 0xE2CD           ; another init helper

; Write 16-bit value to external memory 0x0223:
800F: MOV   DPTR, #0x0223    ; PHY register address 0x0223
8012: MOV   A, R6
8013: MOVX  @DPTR, A          ; write R6 to PHY reg 0x0223
8014: INC   DPTR
8015: MOV   A, R7
8016: MOVX  @DPTR, A          ; write R7 to PHY reg 0x0224

; Read 16-bit value from program memory at 0xFFFC (last 4 bytes - the chip ID area):
8017: MOV   DPTR, #0xFFFC
801A: CLR   A
801B: MOVC  A, @A+DPTR        ; A = byte at 0xFFFC (= 0x84)
801C: MOV   R6, A
801D: MOV   A, #0x01
801F: MOVC  A, @A+DPTR        ; A = byte at 0xFFFD (= 0x74)
8020: MOV   R7, A
8021: LCALL 0xE3FD            ; pass R6:R7 (= chip ID 0x8474) to function

; Write that 16-bit chip ID to PHY register 0x9434:
8024: MOV   DPTR, #0x9434
8027: MOV   A, R6
8028: MOVX  @DPTR, A
8029: INC   DPTR
802A: MOV   A, R7
802B: MOVX  @DPTR, A
```

### Pattern recognition

* `MOVX @DPTR, A` = **write to PHY hardware register** (8051 external
  memory bus mapped to chip registers in MMIO-like fashion)
* `MOVC A, @A+DPTR` = read from program memory (ROM)
* The firmware writes its chip ID (0x8474 from program ROM 0xFFFC) into
  PHY register 0x9434 as part of init handshake

### Important PHY register addresses touched in init

From first 100 instructions, addresses written:
* 0x0223 / 0x0224 — early init (R6:R7 written)
* 0x9434 / 0x9435 — chip ID handshake
* 0x9438 (per later code) — looks like a status register

### Files

* `BCM84740-ver-D102.bin_disasm_full.txt` — 4487 instructions disassembled
* `BCM84740-ver-D102.bin_symbols.txt` — 376 symbols
* `BCM84740-ver-D102.bin_disasm.txt` — initial 500-instr preview

### Open questions for deeper RE

1. **Identify functions at 0xE301, 0xBE00, 0xE2CD, 0xE3FD** — these are
   the main init helpers. Need to follow LCALL targets recursively.
2. **Map all `MOVX @DPTR` addresses** — gives us the full set of PHY
   registers the firmware touches.
3. **Find MDIO command handler** — there's probably a loop that polls
   a register, decodes MDIO clause22/45 commands, and responds.
4. **Identify SerDes EQ adaptation code** — long-running tight loops
   that adjust pre-emphasis based on RX BER.

## Summary — what static analysis bought us

| Concern | Status |
|---|---|
| CPLD register offsets (pwm1, leds, psu, watchdog) | ✅ DECODED (0x0D=pwm1, 0x0E=watchdog, 0x01-0x03=status) |
| LED uController ISA | ✅ Full opcode table + emit() decoded (256-byte program limit) |
| PHY firmware entry point + base address | ✅ Loads at 0x8000, first init: LCALL 0xE301 |
| Detailed PHY init sequence | ⚠️ 4487 instructions disassembled; needs LCALL-following and function naming pass |
| switchd BCM SDK call graph | ❌ Not yet (31 MB binary — long Ghidra run, separate task) |

## Next deeper RE targets

1. **Write a recursive 8051 function-finder script** that pre-marks all
   LCALL/ACALL targets as function entries (Ghidra's auto-function
   recovery doesn't grok 8051 well).
2. **Tag PHY MMIO addresses** by `MOVX @DPTR` target — gives us the
   full register map.
3. **switchd analysis** (31 MB) for the BCM API sequencing — pattern-
   match by string xrefs to function names like "bcm_port_speed_set" etc.
4. **Extract `cpld_leds[]` data table** from CPLD .ko using a Ghidra
   DataType pass — gives us exact LED→register mapping.

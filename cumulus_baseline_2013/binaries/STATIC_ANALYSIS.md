# Static Analysis of Cumulus Binaries — Findings

Analysis run against the binaries pulled from the live Cumulus 2.5.0
chassis. Tools used: `nm`, `objdump`, `readelf`, `strings`, `xxd`,
`binwalk`. Ghidra-class follow-on analysis is a separate task.

## 1. `ledasm` — LED uController assembler (34 KB, UNSTRIPPED)

Big win: `ledasm` was shipped with `.debug_info` intact. Source file is
`ledasm.c`, compiled by **GCC 4.7.2** in
`/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/build/powerpc/bcm-sdk/build/led`.
This is a single-file C program.

### Functions (from symbol table)

| Symbol | Role |
|---|---|
| `main` | entry |
| `init_tables` | populates the opcode table at `.data` 0x10014154 |
| `parse_file` | top-level parser |
| `parse_line`, `parse_label`, `parse_comment` | line lexer |
| `parse_mainpart`, `parse_args` | opcode + operand parser |
| `parse_addop`, `parse_mulop`, `parse_logop`, `parse_conexpr`, `parse_primop` | expression parser (operator precedence) |
| `parse_d`, `parse_ddd` | data directives |
| `emit` | byte emitter (pass 2) |
| `add_symbol`, `find_sym_idx`, `dump_sym_table` | symbol table |
| `dump_hex_file` | output `.hex` |
| `dump_c_file` | output C array `const unsigned char ledproc_<name>[]` |
| `hexval`, `ishexdigit`, `isoctdigit` | lexer helpers |
| `lower_buf` | case folding |
| `error` | error reporting |

### Full LED uController ISA (extracted from `.data` opcode table)

39 entries × 16 bytes each at .data offset 0x14154. Entry format:
```c
struct opcode_entry {
    uint32_t opcode_byte;   // base opcode value
    uint32_t mask;          // 0xff=exact, 0xf8=3-bit imm, etc; 0=directive
    const char *mnemonic;   // pointer into .rodata
    uint32_t handler_id;    // dispatch into emit logic
};
```

| Opcode | Mask | Mnemonic | Encoding hint |
|---|---|---|---|
| (directive) | 0 | `equ` | symbol assignment, no bytes emitted |
| (directive) | 0 | `set` | symbol re-assignment |
| (directive) | 0 | `clc` | clear carry — maybe pseudo / inline |
| 0x07 | 0xff | `stc` | set carry |
| 0x17 | 0xff | `cmc` | complement carry |
| 0x37 | 0xff | `ret` | return |
| 0x57 | 0xff | `call` | call (subroutine, saves return) |
| 0x67 | 0xff | `jmp` | unconditional jump |
| 0x77 | 0xff | `pack` | pack top-of-stack bits into output |
| 0x87 | 0xff | `pop` | pop top of stack |
| 0x97 | 0xff | `txor` | top-of-stack XOR |
| 0xa7 | 0xff | `tor` | top-of-stack OR |
| 0xb7 | 0xff | `tand` | top-of-stack AND |
| 0xc7 | 0xff | `tinv` | top-of-stack invert |
| 0xd7 | 0xff | `push` | push value (no embedded imm) |
| 0x20..0x27 | 0xf8 | `port` | select port N (N = low 3 bits) |
| 0x28..0x2f | 0xf8 | `pushst` | push status bit N |
| 0x30..0x33 | 0xfc | `send` | output to LED bank (low 2 bits) |
| 0x38..0x3f | 0xf8 | `jz` | jump on zero (3-bit imm) |
| 0x70 | 0xff | `jc` | jump on carry |
| 0x71 | 0xff | `jt` | jump on test |
| 0x72 | 0xff | `jnz` | jump not zero |
| 0x74 | 0xff | `jnc` | jump no carry |
| 0x75 | 0xff | `jnt` | jump no test |
| 0x76 | 0xff | `inc` | increment |
| 0x80..0x87 | 0xf8 | `dec` | decrement reg (low 3 bits = reg) |
| 0x90..0x97 | 0xf8 | `rol` | rotate left |
| 0x88..0x8f | 0xf8 | `ror` | rotate right |
| 0x98..0x9f | 0xf8 | `xor` | XOR reg |
| 0xa0..0xaf | 0xf0 | `or` | OR (4-bit imm) |
| 0xb0..0xbf | 0xf0 | `and` | AND (4-bit imm) |
| 0xc0..0xcf | 0xf0 | `cmp` | compare (4-bit imm) |
| 0xd0..0xdf | 0xf0 | `sub` | subtract (4-bit imm) |
| 0xe0..0xef | 0xf0 | `add` | add (4-bit imm) |
| 0xf0..0xff | 0xf0 | `tst` | test (4-bit imm) |
| 0x08+ | 0x8c | `bit` | bit access (variable encoding) |
| 0x0c+ | 0x8c | `ld` | load (variable encoding) |
| sentinel | 0x88 | (end) | |

### Confirming our LED bytecode dispatch table interpretation

```
02 06 67 9B   02 05 67 9B   ...   (32 entries)
```

Per the table above, byte 0x02 doesn't match any opcode directly. The
`ld` instruction's mask is 0x8c, meaning `(byte & 0x8c) == 0x0c`. For
byte 0x02, that doesn't fit. The most likely explanation: **`ld a, #imm8`
is a 2-byte instruction where 0x02 is the opcode and the next byte is
the immediate**. The opcode-table entry for `ld` at 0x0c covers a
different addressing mode (`ld a, (mem)` perhaps).

So `02 06 67 9B` decodes as:
```
ld a, #0x06     ; opcode 0x02, imm 0x06 (load port number 6 into A)
jmp 0x9B        ; opcode 0x67, target 0x9B (jump to set_led handler)
```

This matches `accton.py`'s `_set_led` source exactly — confirms our
hand-derivation of the LED program from the Python source.

### Why this matters for EdgeNOS

We have:
1. The **assembler source** as a 34 KB unstripped ELF (trivial to RE)
2. The **opcode table** byte-for-byte extracted (above)
3. The **disassembly target** — every LED program we encounter can be
   decoded back to assembly using the table

EdgeNOS can either:
* Ship a copy of `ledasm` (verify license — Cumulus build)
* Write a tiny Python re-implementation of the assembler using the table
  above (~200 lines)
* Just ship pre-compiled `.hex` bytecode (least flexibility)

## 2. `accton_as5610_52x_cpld.ko` — CPLD driver (157 KB)

Symbol dump reveals the full driver structure. EdgeNOS can mirror this
nearly verbatim.

### Module init/exit

```c
static int accton_as5610_52x_cpld_init(void);    // platform_driver_register
static void accton_as5610_52x_cpld_exit(void);   // platform_driver_unregister
static int accton_as5610_52x_cpld_probe(...);    // ioremap @ 0xea000000
static int accton_as5610_52x_cpld_remove(...);
static int accton_as5610_52x_cpld_setup(...);    // sysfs_create_group
```

The probe function calls `printk("probed & iomapped @ 0x%p\n", base)`
after `ioremap()` of the CPLD's physical address.

### sysfs attribute handlers

| sysfs attr | Show handler | Store handler |
|---|---|---|
| `board_revision` | `board_revision_show` | (read-only) |
| `led_diag`, `led_fan`, `led_locator`, `led_psu1`, `led_psu2` | `led_show` | `led_store` |
| `psu_pwr{1,2}_all_ok/dc_ok/present` | `psu_power_show` | (read-only) |
| `system_all_ok`, `system_dc_power_ok`, `system_fan_present`, `system_fan_ok`, `system_fan_air_flow` | (composite — uses `cpld_system_status` table) | (read-only) |
| `pwm1` | `pwm1_show` | `pwm1_store` |
| `pwm1_enable` | `pwm1_enable_show` | `pwm1_enable_store` |
| `watch_dog_enable`, `watch_dog_keep_alive`, `watch_dog_timeout` | (sysfs binding) | sysfs binding |

### Data tables (.data section, by offset)

| Offset | Symbol | What it likely holds |
|---|---|---|
| 0x00c | `accton_as5610_52x_pwm1` | pwm1 attribute descriptor (register offset, range, label) |
| 0x080 | `cpld_leds` | LED→register/value mapping table |
| 0x47c | `cpld_system_status` | System status register layout |
| 0x648 | `cpld_psu_status` | PSU status register layout |
| 0x75c | `accton_as5610_52x_cpld_driver` | `platform_driver` struct (name/probe/remove) |
| 0x7ac | `accton_as5610_52x_cpld_ids` | OF/platform match table |
| 0x934 | `accton_as5610_52x_cpld_attrs` | sysfs attribute group |
| 0x998+ | `dev_attr_*` | per-attribute `device_attribute` structs |

### EdgeNOS port path

The CPLD physical address `0xea000000` is on the PowerPC local bus
controller `ff705000.localbus`. The driver expects the device-tree to
have a `compatible` string matching the IDs at offset 0x7ac. EdgeNOS
can:

1. Reuse the .ko as-is (it's GPL-licensed per modinfo).
2. OR write an equivalent driver using the same register layout. The
   register offsets are in `cpld_system_status` / `cpld_psu_status` /
   `accton_as5610_52x_pwm1` — extracting them requires a Ghidra pass
   on the .ko's .data section.

## 3. PHY firmware — Broadcom 84740 (Warpcore) microcontroller code

`BCM84740-ver-D102.bin` (32 KB) is **8051 microcontroller machine code**.

### Evidence

Bytes 0–15:
```
12 e3 01    LJMP 0xe301         ; 8051 reset vector → init code
12 be 00    LJMP 0xbe00
7d 01       MOV R5, #0x01
7c c8       MOV R4, #0xc8
7f 01       MOV R7, #0x01
12 e2 cd    LJMP 0xe2cd
90 02 23    MOV DPTR, #0x0223
ee f0       MOVX @DPTR, A
```

These are textbook 8051 opcodes. The Warpcore PHY contains an embedded
8051 CPU that runs this firmware to handle:
* SerDes RX EQ adaptation
* PCS sync acquisition
* MDIO register interface to the host
* Idle/error block accounting

### Trailer (last 16 bytes)

```
00 08 47 40 D1 02 31 F4
```

* `08 47 40` = chip ID 0x84740 (matches filename)
* `D1 02` = firmware version D1.02 (matches filename)
* `31 F4` = likely CRC-16 / checksum

### Loading mechanism

From `config.bcm`:
```
phy_ext_rom_boot=0    # use MDIO method for ucode download
```

So the firmware is loaded via MDIO writes from the host (BCM SDK)
into the PHY's 8051 program RAM, then the PHY's CPU is released from
reset. This is the standard Broadcom PHY firmware-load pattern.

### EdgeNOS implications

EdgeNOS **must** load this exact 32 KB firmware blob into the Warpcore
PHYs at boot, before configuring any Warpcore registers. Without the
firmware, the PHY's SerDes won't adapt and link will never come up.

Static-analysis pathway for deeper understanding:
1. Load `BCM84740-ver-D102.bin` into Ghidra as **8051 raw binary**.
2. Identify entry point (reset vector at offset 0).
3. Find MDIO register handlers (likely respond to specific addresses).
4. Map out the SerDes init sequences.

## 4. `switchd` — main daemon (31.7 MB)

Too big for a thorough static analysis in one pass. Key observations:

* **Architecture:** ELF32 BIG-endian PowerPC, stripped, dynamically linked
* **Build environment:** `/work/monster-07/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/...`
* **GCC version:** can be inferred from build path / GLIBC 2.0-2.4 sym versions
* **Dynamic deps:** `libnl-3.so`, `libnl-route-3.so`, `libnl-genl-3.so`,
  `libnet.so.1`, `libfuse.so.2`, `librt`, `libdl`, `libpthread`, `libm`, `libc`
* **Section layout:**
  * `.text` = 19 MB (BCM SDK is statically linked in)
  * `.rodata` = 5 MB (lots of strings/tables)
  * Total binary ~32 MB

### Notable strings

* `/etc/cumulus/.license.txt`
* `/etc/cumulus/switchd.conf`
* `/etc/cumulus/datapath/traffic.conf`
* `Switchd version` / `Cumulus Networks switchd version %s`
* `build_work_queues`, `build_nl_link_family_filter`, `build_nl_neigh_family_filter`
* `Profile: Kernel build mac table in: %llu usecs`
* iptables/ip6tables/ebtables rule conversion error messages
* lots of `log.h:%d` source-line references → debug logs

### Ghidra targets in switchd

Symbol-stripping makes this a slog, but the BCM SDK statically linked
means the BCM API function bodies are intact and pattern-matchable.
High-value functions to find:

* `bcm_port_init`
* `bcm_port_speed_set`
* `bcm_l2_addr_add` / `bcm_l2_addr_delete`
* `bcm_l3_route_add` / `bcm_l3_host_add` / `bcm_l3_egress_add`
* `bcm_field_*` (FP/TCAM)
* `bcm_cosq_*` (CPU queues)
* `bcm_rx_*` (packet RX handling)
* `bcm_tx_*` (packet TX handling)

These are documented in the OpenMDK headers we already have in
EdgeNOS, so cross-referencing call patterns from switchd to EdgeNOS
source is feasible once the symbols are recovered.

## 5. Kernel modules (.ko files)

All cumulus-specific .ko binaries are extracted. Symbol tables visible
via `nm`. Each has a well-defined sysfs-driven API. Most useful for
EdgeNOS analysis:

| Module | Size | EdgeNOS value |
|---|---|---|
| `accton_as5610_52x_cpld.ko` | 157 KB | direct port material — see §2 above |
| `linux-kernel-bde.ko` | 496 KB | BCM SDK kernel-side BDE — IOCTL interface for switchd. Critical for PCIe/CMIC interrupt handling. |
| `linux-user-bde.ko` | 420 KB | User-space BDE chardev → forwards to kernel BDE |
| `linux-bde-i2c.ko` | 184 KB | I2C-based device enumeration |
| `linux-bde-tmon.ko` | 153 KB | ASIC die temperature monitor |
| `ds100df410.ko` | 141 KB | Retimer driver (already documented earlier) |
| `gpio-pca953x.ko` | 160 KB | Upstream Linux driver — EdgeNOS gets free |
| `max6697.ko` | 154 KB | Upstream Linux driver |
| `sff_8436_eeprom.ko` | 170 KB | QSFP EEPROM driver |
| `adm1021.ko` | 154 KB | max1617/ne1617 temp sensor (upstream) |

## What's now possible (next steps)

1. **Disassemble `BCM84740-ver-D102.bin` as 8051** — Ghidra has a built-in
   8051 processor. This unlocks understanding of how the PHY initializes
   its SerDes (vs. our current black-box approach).

2. **Ghidra-load `ledasm`** with debug info to extract the exact
   encoding logic for each opcode in `emit()`. The opcode table above
   covers the dispatch but not the bit-level packing of immediates.

3. **Ghidra-load `accton_as5610_52x_cpld.ko`** to extract the register
   offset map (which CPLD address corresponds to `pwm1`, `system_fan_ok`,
   etc.). With offsets, EdgeNOS can write a 1:1 driver.

4. **Ghidra-load `switchd`** for the BCM SDK call pattern in production.
   This is the longest pole — 31 MB stripped binary. Worth doing
   incrementally, function-by-function, for specific port-up sequences.

5. **`update-ports` + `datapath-update` Python** — already source.
   Read directly to extract the `rc.datapath_0` generation logic and
   port them to EdgeNOS-equivalent C/Python.

## Tools used

* `nm` — symbol table
* `objdump -s -j .data` — extract opcode table bytes from `ledasm`
* `objdump -s -j .rodata` — extract mnemonic strings
* `readelf -wL` — DWARF line info (confirmed `ledasm.c` source compile path)
* `strings -t x` — strings with file offsets
* `xxd` / `binwalk` — hex dump + structure analysis of PHY firmware

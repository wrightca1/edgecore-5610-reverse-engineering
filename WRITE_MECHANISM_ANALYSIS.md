# Table Write Mechanism — FUN_01876c30 Dispatch Analysis

**Date**: 2026-02-21
**Status**: PARTIAL — dispatch chain fully decoded; bctrl handler address requires runtime capture
**Sources**: [build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876c30.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876c30.txt), [build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876ee0.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876ee0.txt), [build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876f10.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-dump-01876f10.txt), [build-server/opennsl/sdk-deep-extract/libopennsl-schan-usage.txt](../../build-server/opennsl/sdk-deep-extract/libopennsl-schan-usage.txt)

---

## 1. Full Write Dispatch Chain

```
FUN_01876f10(unit, table_id, -1, index, buffer)
  ├─ table_id alias check: 0x22ca→0x22c9, 0x2c33→same, 0x835→0x6fa
  └─> FUN_01876ee0(unit, table_id, 0, index, size, buffer)
        └─> FUN_01876c30(unit, table_id, 0, index, size, buffer, ...)
              ├─ [primary path: handler found]
              │    load r9 = unit_struct[unit]
              │    r11 = r9 + 0x20000  (addis r11,r9,0x2)
              │    r0 = [r11 - 0x6b7c]  → handler at r9 + 0x19484
              │    → bctrl r0  (per-unit ASIC write handler)
              │
              └─ [fallback path: handler NULL at r9+0x19484]
                   check [r9+0x10]: sub-type selector
                   check [r9+0x14] & 0x08000001: mode bits
                   addis r9,r9,0xa3  → r9 += 0xa30000
                   load [r9+0xa30000+0x7190]: alternate handler selector
                   andis. [r0] & 0x400: conditional alt path
```

---

## 2. Corrected Handler Address

**Previous documentation error**: The handler was incorrectly stated as `[r9-0x6b7c]`.

**Actual assembly** (01876c30, lines 018cc6cb8–018cc6ce4):
```
01876cb8: addis r11, r9, 0x2        ; r11 = r9 + (2 << 16) = r9 + 0x20000
01876cbc: lwz   r0, -0x6b7c(r11)   ; r0  = mem[r11 - 0x6b7c] = mem[r9 + 0x19484]
01876cc0: cmpwi cr7, r0, 0x0        ; if handler NULL → fallback
01876cc4: beq   cr7, 0x01876d2c
...
01876ce0: mtspr CTR, r0             ; load handler into CTR
01876ce4: bctrl                     ; call handler
```

**Correct handler offset**: **r9 + 0x19484** (not r9 − 0x6b7c)

r9 is loaded as `lwzx r9,r28,r29` where r28 = global unit-array ptr, r29 = unit*4.
So r9 is the per-unit struct pointer for the given unit number.

The handler at **unit_struct + 0x19484** is populated at initialization time by the chip-specific
driver (SDRV) based on the detected ASIC type (BCM56846).

---

## 3. FUN_01876ee0 — Argument Reshuffling Trampoline

FUN_01876ee0 is a pure argument-reshuffling trampoline:

```
01876ee0 or  r12,r4,r4    ; save table_id
01876ee4 or  r10,r5,r5    ; save arg5
01876ee8 or  r11,r6,r6    ; save arg6
01876eec or  r0,r7,r7     ; save arg7
01876ef0 or  r9,r8,r8     ; save arg8
01876ef4 li  r4,0x0       ; r4 := 0 (clears "op" slot; sets "r4_new" = 0)
01876ef8 or  r5,r12,r12   ; r5 := old r4 (table_id)
01876efc or  r6,r10,r10   ; r6 := old r5
01876f00 or  r7,r11,r11   ; r7 := old r6
01876f04 or  r8,r0,r0     ; r8 := old r7
01876f08 b   0x01876c30   ; tail-call FUN_01876c30
```

**Effect**: Shifts table_id from r4 to r5, inserts r4=0. This sets up the argument order that
FUN_01876c30 expects: (unit, 0, table_id, index, size, buffer, ...).

---

## 4. FUN_01876f10 — Table-ID Alias Normalization

```
01876fc4: cmpwi cr7, r31, 0x22ca  ; if table_id == L3_DEFIP_alt → remap to 0x22c9
01876fc8: beq   cr7, 0x01877024
01876fcc: cmpwi cr7, r31, 0x2c33  ; if table_id == L3_ECMP_alt → keep (no remap shown)
01876fd0: beq   cr7, 0x01877078
01876fd4: cmpwi cr7, r31, 0x835   ; if table_id == 0x835 → remap to 0x6fa
01876fd8: beq   cr7, 0x0187702c
...
01877024: li  r31, 0x22c9          ; alias 0x22ca → 0x22c9
01877028: b   0x01876fdc
0187702c: li  r31, 0x6fa           ; alias 0x835 → 0x6fa
01877030: b   0x01876fdc
```

**Table-ID aliases** (normalized before dispatch):

| Input ID | Normalized ID | Table |
|----------|--------------|-------|
| `0x22ca` | `0x22c9` | L3_DEFIP alt |
| `0x2c33` | (special handling) | L3_ECMP alt |
| `0x835` | `0x6fa` | Unknown (likely MPLS or QoS table) |

---

## 5. S-Channel vs Direct BAR — Current Evidence

### 5.1 libopennsl has no direct 0x32800 references

`libopennsl-schan-usage.txt`:
```
Functions referencing S-Channel (0x32800 region): 0
```

This means libopennsl does **not** directly access BAR0+0x32800 (the CMIC S-Channel FIFO).

### 5.2 FUN_007042f0 (S-Channel submitter) is NOT in the 01876c30 call chain

S-Channel callers (`libopennsl-schan-callers.txt`):
```
FUN_007042f0 @ 007045d0   (calls FUN_00703dc0 which builds S-Chan command word)
FUN_00704790 @ 00704798
FUN_00704784 @ 0070478c
```

None of these are called from FUN_01876f10 → FUN_01876ee0 → FUN_01876c30.

### 5.3 switchd accesses S-Channel directly

`switchd-schan-data-refs.txt` shows 49+ instructions using `oris r10,r9,0x2800` across
17 functions (FUN_10325fa0, FUN_103260d4, etc.). switchd has the full SDRV statically linked
and accesses BAR0+0x32800 directly via mmap'd /dev/mem.

### 5.4 Working theory

The bctrl handler at `unit_struct + 0x19484` is installed by the chip-specific SDRV at boot
and likely performs one of:

| Write path | Evidence for | Evidence against |
|-----------|--------------|-----------------|
| **Direct BAR write to table memory (0x01xxxxxx)** | Table addresses (0x1005e00, 0x180c200) seen in switchd data; no S-Chan in libopennsl call chain | Not confirmed at runtime |
| **S-Channel via BDE kernel module (ioctl)** | Possible for TCAM/special tables | FUN_007042f0 not in call chain; no ioctl observed for table writes in strace |
| **S-Channel directly in bctrl handler** | switchd SDRV does use S-Chan; bctrl is opaque | libopennsl schan-usage=0 |

**Most likely**: Regular tables (L2_USER_ENTRY 0x1547, L3_DEFIP 0x22d3, L3_ECMP 0x2c32)
use **direct BAR writes** to on-chip SRAM (the 0x01xxxxxx region mmap'd from /dev/mem).
TCAM tables may use S-Channel. The bctrl handler at +0x19484 selects the path based on table type.

---

## 6. Fallback Path in FUN_01876c30

When primary handler at `r9 + 0x19484` is NULL:

```asm
01876d2c: lwz  r0,  0x10(r9)          ; load sub-type
01876d30: cmpwi cr7, r0, 0x0
01876d34: bne  cr7, 0x01876d4c        ; if sub-type != 0 → alt handler path
01876d38: lwz  r0,  0x14(r9)          ; load config word
01876d3c: lis  r11, 0x800
01876d40: ori  r11, r11, 0x1          ; r11 = 0x08000001
01876d44: and. r10, r11, r0           ; test bits 0x08000001
01876d48: bne  0x01876e58             ; if any of those bits set → yet another path
01876d4c: cmpwi cr7, r9, 0x0
01876d50: beq  cr7, 0x01876d94        ; NULL unit struct → error
01876d54: addis r9, r9, 0xa3          ; r9 += 0xa30000
01876d58: lwz  r0, 0x7190(r9)         ; load capability flags
01876d5c: andis. r11, r0, 0x400       ; test bit 26 (0x04000000)
01876d60: beq  0x01876d94             ; if not set → error/no-op
01876d64: lbz  r0, 0x5908(r9)         ; load enable byte
01876d68: cmpwi cr7, r0, 0x0
01876d6c: beq  cr7, 0x01876d94        ; if 0 → no-op
```

**Fallback fields** (relative to unit_struct r9 before addis):
- `r9 + 0x10`: sub-type (0 = primary handler path)
- `r9 + 0x14`: mode bits (0x08000001)
- After `addis r9,r9,0xa3` (r9 → r9+0xa30000):
  - `r9 + 0xa30000 + 0x7190` = capability flags (bit 0x04000000 = "use alternate path")
  - `r9 + 0xa30000 + 0x5908` = enable byte

---

## 7. What's Still Needed to Confirm Write Mechanism

| Action | How | Priority |
|--------|-----|----------|
| Capture bctrl handler address at runtime | GDB on switchd: `break *0x01876ce4` during `bcm_l2_addr_add`; print $ctr | **HIGH** |
| Dump the handler function (once addr known) | `run-dump-func-on-build-server.sh libopennsl <handler_addr> 200` | HIGH |
| Check if handler calls mmap write or kernel ioctl | Handler disasm will show: BAR write = `stwx` to mmap ptr; ioctl = `sc 0` or `bl kernel_ioctl` | HIGH |
| Cross-check with switchd for same handler | Find `unit_struct + 0x19484` equivalent in switchd (same SDK, different base addr) | MEDIUM |

### GDB commands (Cumulus switch 10.1.1.233)

```bash
gdb --pid $(pgrep -f 'switchd -d')
# In switchd, equivalent of 01876c30 is at a different address (statically linked)
# Find by searching for the pattern: addis r11,r9,0x2; lwz r0,-0x6b7c(r11)
(gdb) find /b 0x10000000, 0x11400000, 0x39, 0x62, 0x00, 0x02  # addis r11,r9,0x2
# OR: break at bcm_l2_addr_add entry, single-step to bctrl
(gdb) break bcm_l2_addr_add
(gdb) commands
(gdb)   continue
(gdb) end
```

---

## 8. FUN_018788bc — ECMP Write Trampoline

```
018788bc: li  r9, -0x1     ; set r9 = -1 (index = auto)
018788c0: b   0x018786d0   ; jump to FUN_018786d0 (real ECMP write)
```

FUN_018788bc is a 2-instruction trampoline: sets r9=-1 (use auto-index) then jumps to
FUN_018786d0, which is the actual ECMP member write function.

**FUN_018786d0 key behavior**:
- Loads `r11` from `[r30-0x7f5c][unit*4]` — checks if unit is "BCM56846 type 1"
- If r11 == 1 (BCM56846): checks per-unit struct + 0xa30000 + 0x5913 (enabled flag)
- For r5 == -1 (auto-index): `addi r9, r4, 0x3864` → loads group count from unit struct at `r8 + (table_id + 0x3864)*4 + 0x10`
- For specific index r4: computes ECMP stride `mulli r6,r4,0xe9` — **ECMP member stride = 0xe9 (233) bytes** in unit struct at offsets 0x6b98 and 0x6bd0 from base
- Member read: `lwz r9,0xc(member_ptr)` (data word), `lwz r8,0x14(member_ptr)` (ptr), `lbz r8,0x0(r8); andi. r6,r8,0x1` (valid bit)
- Member entry size: `lwz r10,0x6c30(unit+0xa30000)` → `0x28(table_info)` → `[table_id*4]` → `lhz r10,0x28(member)` (entry size in bytes)
- Write: `mullw r5,count,entry_size; bl 0x02f52328` (memcpy count entries into ASIC buffer)
- Falls through to `b 0x01877f68` for actual table submission

---

## References

- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md)
- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md)
- [CUMULUS_VS_OPENNSL_ARCHITECTURE.md](CUMULUS_VS_OPENNSL_ARCHITECTURE.md)
- [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md)
- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md)

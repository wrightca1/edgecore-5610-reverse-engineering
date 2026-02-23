# Function dump analysis (FUN_0080ba18, FUN_1000b638)

**Purpose**: Analyze Ghidra dumps of opennsl_tx callee (libopennsl) and S-Channel-related function (switchd).

**Artifacts**:
- `build-server/opennsl/sdk-deep-extract/libopennsl-dump-080ba18.txt` — opennsl_tx callee at 0x80ba18
- `build-server/switchd/sdk-deep-extract/switchd-dump-01000b638.txt` — switchd S-Channel anchor at 0x1000b638
- `build-server/opennsl/sdk-deep-extract/libopennsl-l2-writes.txt` — FindL2Writes output

---

## 1. FUN_0080ba18 (libopennsl — opennsl_tx callee)

**Address**: 0x0080ba18  
**Binary**: libopennsl.so.1 (PowerPC)

### Flow

1. **Input validation**: `cmplwi cr7, r3, 0x7f` — r3 (first arg) must be ≤ 127 (unit/device index).
2. **Lookup table**: Load pointer from `r30-0x8000` (GOT/PIC base), index by `r3*4`, get `r9`. If null, skip to error path.
3. **Sub-table**: From `r9`, load `r28 = [r9+8]`. Use `r28*4` and `r30-0x7ffc` + `addis r9,r9,0x1` to index another table, load `r0 = [r9-0x3c34]`, call via `mtspr CTR,r0; bctrl`.
4. **Callback/API**: The call at 0x80ba80 is the unit-specific TX handler. r3 (unit), r4 (r28) passed to `bl 0x0086fe6c` (0x86fe6c) — likely a wrapper or post-TX callback.
5. **Fallback / BDE path**: If validation fails or lookup returns null, call `bl 0x01393e80` with `r3=0x3014805` (error/status code). On failure, call `bl 0x0070c994` with:
   - r3=0x3014800
   - r4 from `[r30-0x3eb4]`
   - r5=3, r6=1, r7=r29 (unit), r8=0, r9=0, r10=r31 (return from callback)
   This is likely BDE/SDK TX or error handling.
6. **Return**: r31 (from callback or -3) is returned.

### Notes for packet buffer (4.6)

- Unit index in r3; lookup yields unit-specific TX handler.
- TX handler at `[r9-0x3c34]` receives control; r4 (r28) may be a handle/context.
- **Trace lengths** (PACKET_IO_TRACE_EXTRACTED): TX read 42/82/122, RX write 60/82. These match Ethernet frame sizes (42=ARP, 60=min IP, 82=ICMP+payload, 122=larger).
- **Buffer layout (inferred)**: Contiguous Ethernet frame (no obvious separate metadata in lengths). OpenNSL `opennsl_pkt_t` likely wraps `pkt_data` + `pkt_len`; header/metadata may be in a separate control structure or same buffer with offset. Dump 0x86fe6c, 0x70c994 in Ghidra for full layout.

---

## 2. FUN_1000b638 (switchd — S-Channel anchor)

**Address**: 0x1000b638  
**Binary**: switchd (PowerPC, statically linked)

### Flow

1. **Input**: r3 points to struct at 0x18(r31); byte at offset 0x10 is read: `lbz r9,0x10(r9)` → compared to `0xa` (10). If not 0xa, jump to 0x1000b71c (return 0).
2. **Config check**: Load `[0x11e46fb0]`; if 1, branch to 0x1000b688; if 2, to 0x1000b6b8; else to 0x1000b6c4.
3. **Path 1** (value 1): Load byte at offset 0x11, compare with `[0x11f1df2c]` (0x11f2-0x20d4+0xc). If ≤, fall through; else set result 1 and branch to 0x1000b718.
4. **Path 2** (value 2): Set result 1, branch to 0x1000b71c.
5. **Path 3** (other): Load `[0x11e46cd4]`; if ≤1, branch to 0x1000b71c. Else call `0x10047de0` (likely `malloc` or alloc), then `0x10047ec4` (likely `snprintf`/`fprintf` — string addrs 0x1132a6c4, 0x1132a69c, 0x1132a05c) for logging/error. Then branch to 0x1000b71c.
6. **Return**: Value at 0x8(r31) — 0 or 1.

### Notes for S-Channel (2.3)

- This function is a **validation/guard**: it checks a type field (0x10 == 0xa) and config globals, then returns 0 or 1. It does **not** perform the actual S-Channel write (0x32800).
- The S-Channel `stw r5, 0x32800(r6)` would appear in a **different** function — a caller of this one, or in a code path that does register-based store. FindSChannelUsage looks for scalar 0x32800; PowerPC `stw r5, 0x32800(r6)` uses offset 0x32800 in the address operand, which may be encoded differently (e.g. split immediate).
- **Next**: Search for functions that call FUN_1000b638 and that contain stores with base+offset; or search for 0x32800 in data/rodata and follow xrefs.

---

## 3. L2 writes (FindL2Writes)

**Output**: `libopennsl-l2-writes.txt`

- **Result**: 0 functions with direct scalar stores to L2 region (0x1300000–0x1900000).
- **Reason**: PowerPC table access uses `(base_reg + offset)`. The L2 base (0x180c200) is loaded into a register from data/GOT; stores are `stw Rx, off(Ry)` where Ry holds the base. FindL2Writes only checks `Scalar` operands, so it misses register-based addressing.
- **Next**: Use xrefs from L2_USER_ENTRY (0x180c200) in `opennsl-table-addr-xrefs.txt` / L2_TABLE_ACCESS_ANALYSIS.md; or write a script that follows data refs to 0x180c200 and finds stores through that base.

---

## 4. Scripts and commands

| Script | Purpose |
|--------|---------|
| `DumpFunctionCode.java` | Dump assembly for a function (decompile skipped in headless) |
| `run-dump-func-on-build-server.sh <binary> <addr>` | Run DumpFunctionCode on build server |
| `FindL2Writes.java` | Find store instructions with scalar L2 addresses (PowerPC: limited) |
| `run-l2-writes-on-build-server.sh` | Run FindL2Writes on libopennsl |

---

## 5. Additional dumps (packet path, S-Chan, L2)

| Function     | Binary    | Role |
|-------------|-----------|------|
| FUN_0086fe6c | libopennsl | Callback dispatcher (r4=0xf4), TX completion path |
| FUN_0070c994 | libopennsl | BDE/S-Channel TX; r3=unit|5, r6=mode 0/1/2; calls 0x1393e80, 0x13949c0 |

### 5a. FUN_0086fe6c — TX completion callback dispatcher

**Address**: 0x0086fe6c  
**Caller**: FUN_0080ba18 (opennsl_tx callee)

- **Input**: r3 = unit index (≤17), r4 = context/handle
- **Flow**:
  1. Validate unit: `cmplwi cr7,r3,0x11` → bgt → error (return -3)
  2. Table lookup: base at r30-0x8000, index r3*4; if null → error
  3. Sub-table: r9 = [base-0x7ffc][r4*4]; r27 = base
  4. Call `(*r11)(r3, r4, r5)` with r4=0xf4, r5=&out — likely packet/TX completion callback
  5. On success and out≠0: load r11 from [r28][r29]; check [r11+0xa37114]; if ≠0, call `(*[r27+0xc])(r3, 0xf3, 1)` — secondary callback
- **Interpretation**: 0xf4 = primary TX completion; 0xf3 = secondary (e.g. buffer release). No explicit packet buffer layout; callback receives unit + handle.

### 5b. FUN_0070c994 — BDE/S-Channel TX handler

**Address**: 0x0070c994  
**Caller**: FUN_0080ba18 (on error path)

- **Input**: r3 = unit, r4–r10 = args; r10 (r31) = result/handle; r6 = mode (0, 1, or 2)
- **Flow**:
  1. Early exit if r10 &lt; 0
  2. r6==0: `ori r28,r3,5` → call 0x01393e80 (validate); on success call 0x013949c0 with r6=0x2b (43) — S-Channel submit
  3. r6==1: branch 0x70cb40
  4. r6==2: branch 0x70cbc0
  5. r6 other: `ori r23,r3,5` → call 0x01393e80; call 0x013949c0 with r6=0x40 (64)
- **Interpretation**: 0x01393e80 = BDE/S-Chan validation; 0x013949c0 = S-Channel write. Constants 0x2b (43) and 0x40 (64) likely command length or type. r3|5 may be unit+flags. No packet buffer layout visible in this function.

| FUN_007ebb58 | libopennsl | Unit-dispatched; ori r3,0x2800 (error code) |
| FUN_00881edc | libopennsl | L2_USER_ENTRY reader |
| FUN_00948700 | libopennsl | L2 table reader |

See [SCHAN_AND_L2_ANALYSIS.md](SCHAN_AND_L2_ANALYSIS.md) for S-Channel 0x32800/0x2800 refs.

---

## 6. References

- [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md) — §2.3 (S-Chan), §3.3/3.8 (L2), §4.6 (buffer)
- [L2_TABLE_ACCESS_ANALYSIS.md](L2_TABLE_ACCESS_ANALYSIS.md) — L2_USER_ENTRY xrefs
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md)

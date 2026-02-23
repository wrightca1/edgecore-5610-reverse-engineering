# S-Channel and L2 analysis (Path B)

**Artifacts**: `libopennsl-schan-data-refs.txt`, `switchd-schan-data-refs.txt`, `libopennsl-dump-07ebb58.txt`, `libopennsl-dump-0881edc.txt`, `libopennsl-dump-0948700.txt`

---

## 1. S-Channel (0x32800) in libopennsl

### FindSChannelDataRefs results

- **3 memory locations** contain 0x32800 (data/rodata).
- **143 instructions** use 0x2800 (or lis/ori building 0x2800) — many are false positives (error codes 0x3012800, 0x3014800).

### Key S-Channel functions (0x2800 = lower 16 bits of 0x32800)

Pattern: `ori r3, r3, 0x2800` after loading a base — builds address for S-Chan or related register.

| Function     | Role |
|-------------|------|
| FUN_007ebb58 | Unit-dispatched; calls handler at [r9-0x556c]; error path uses 0x3012800/0x3012805; calls 0x70c994. Similar to FUN_0080ba18. |
| FUN_00703dc0 | `oris r9, r9, 0x2800` — different pattern; may form S-Chan base. |
| FUN_00b62c4c | `lwz r3, 0x2800(r9)` — load from base+0x2800. |
| FUN_00c9a2d0 | `lwz r9, 0x2800(r9)` — same. |
| FUN_0107699c, 01076e6c, 01077600, 01077a6c | `lis r11, 0x2800` — load high 16 bits. |
| FUN_0148e8b8 | Multiple `lis r26/r27/r28/r31, 0x2800` — table/register block. |
| FUN_0151b8a0, 0151c330 | `lis r5, 0x2800` + `oris r5, r5, 0x2800` — builds full 0x32800. |

### Dumped S-Channel candidates

| Function     | Key instructions | Role |
|-------------|------------------|------|
| FUN_00703dc0 | 0x703ee0: `oris r9,r9,0x2800`; `stw r9,0x0(r4)` | Builds value with 0x2800 in high bits, stores to *r4. May encode S-Chan command word. |
| FUN_0151b8a0 | Uses 0x8310, 0x8017; calls 0x0156c414, 0x0156c43c | Unit/block config; 0x2800 refs in later instructions (first 80 lines don't show). |

**FUN_00703dc0**: r4 points to output; r9 = (r9 & 0x7fff) | 0x2800 stored. Callers: FUN_007042f0, FUN_00704790, FUN_00704784. FUN_007042f0: uses r27 from [r30-0x7ff8] and from 0x018120a0; calls 0x018124a8, 0x018120a0, FUN_0070479c. r4 for 00703dc0 likely from per-unit struct (r27 or similar).

### S-Channel callers (FUN_00703dc0)

Callers (from libopennsl-callers-of-0x703dc0.txt): FUN_007042f0 (007045d0), FUN_00704790 (00704798), FUN_00704784 (0070478c). These build the S-Chan command word and pass to FUN_00703dc0.

### S-Channel command word format (FUN_00703dc0)

**Address**: 0x00703dc0  
**Role**: Encodes S-Channel command word before write.

**Flow** (from `libopennsl-dump-0703dc0.txt`):

1. **Input**: r3 = unit, r4 = pointer to value (read/write), r5 = mode flag, r6 = mask
2. **Validation**: r4 non-null; `[r4] >= 0`; per-unit struct at `unit*0x22c`; bit checks at 0x208(r3)
3. **Encoding path** (when r11>>26 == 0xa at 0x703e50):  
   - `lwz r9,0x0(r4)` — load current value  
   - `rlwinm r9,r9,0x0,0x15,0x1f` — mask to lower 15 bits (value & 0x7fff)  
   - `oris r9,r9,0x2800` — set high 16 bits to 0x2800  
   - `stw r9,0x0(r4)` — store result

**S-Channel command word**:
```
output = (input & 0x7fff) | 0x28000000
```
- Bits 0–14: payload (preserved from input)
- Bits 16–31: 0x2800 (S-Channel command type)

The 0x2800 is the S-Channel register/command prefix. Callers FUN_007042f0, FUN_00704790, FUN_00704784 pass the value in *r4; this function encodes it for S-Channel submission.

---

## 2. Packet TX path (FUN_0086fe6c, FUN_0070c994)

| Function     | Role |
|-------------|------|
| FUN_0086fe6c | Callback dispatcher: r3=unit (≤17), r4=sub-index. Calls handler with r4=0xf4, r5=&stack. Checks [r11+0x7114]. Event IDs 0xf4, 0xf3. |
| FUN_0070c994 | BDE/error TX path: receives r3=0x3012800/0x3014800, r4–r10 (unit, handle, etc.). Called from FUN_0080ba18, FUN_007ebb58 on error. |

---

## 3. L2 table readers and callers

| Function     | Access | Notes |
|-------------|--------|-------|
| FUN_00881edc | READ  | `lwz r11, 0x0(r9)` — L2_USER_ENTRY |
| FUN_00948700 | READ  | `lwz r10, 0x0(r9)` |
| FUN_01cc2f2c | READ  | `lwz r8, 0x0(r11)` |

**FindL2Callers** (libopennsl-l2-callers.txt): Call chain — FUN_00946a00 → FUN_00948700 → FUN_01cc2f2c. FUN_00946a00 is top-level L2 path; dump it for add/delete flow.

**L2 write path**: FindL2Writes found 0 scalar stores (PowerPC uses register+offset). Trace callers from FindL2Callers; also DATA xrefs at 027f3e80, 027f4d00, 0281d904 load 0x180c200.

---

## 4. Scripts

| Script | Purpose |
|--------|---------|
| `FindSChannelDataRefs.java` | Find 0x32800 in data + 0x2800 in code |
| `run-schan-data-refs-on-build-server.sh [libopennsl\|switchd\|both]` | Run on build server |
| `FindL2Callers.java` | List callers of L2 reader functions |
| `run-l2-callers-on-build-server.sh` | Run FindL2Callers on libopennsl |
| `FindSChanCallers.java` | List callers of FUN_00703dc0 |

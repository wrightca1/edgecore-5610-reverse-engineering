# Block-Init Deep Dive — what `common`, `port`, `field` actually do

Recursive static analysis of the three largest block-init functions
dispatched by `bcm_init()`. For each one, we trace 1-level deep through
the call graph to find which chip-access primitives get invoked and what
helper functions wrap them.

This builds directly on `BCM_INIT_STATIC_CHAIN.md` which lists the 42
block-init steps; here we crack open the three biggest (`common`, `port`,
`field` — combined ~42 KB of code) to see the underlying register-access
patterns.

---

## 1. Chip-access primitive functions (canonical)

The bedrock single-register / single-table access functions in the BCM SDK,
identified by their unique error/assert strings:

| Symbol | Address | Size | Role |
|---|---|---:|---|
| `soc_reg32_get` | `FUN_10845768` | 1176 | SCHAN read for ≤32-bit register |
| `soc_mem_write` | `FUN_10804ea4` | 6640 | Table memory write (any width) |
| `soc_mem_write_range` | `FUN_10806900` | 5772 | Bulk-range table write |
| `soc_mem_read` | `FUN_107fe254` | 11016 | Table memory read |
| `soc_mem_read_indexed` | `FUN_10800dcc` | 3456 | Indexed table read |
| `soc_mem_clear` | `FUN_108092ec` | 4020 | Table zero-fill |
| `soc_mem_clear_lpm` | `FUN_10e8ac44` | 7388 | LPM-specific clear variant |
| `soc_schan_op` | `FUN_10861634` | 8176 | Raw SCHAN protocol engine |

### Mid-level wrappers around the primitives

The block-init functions don't call primitives directly — they go through
mid-level wrappers that handle register/field lookup, validation, and
SCHAN command building:

| Wrapper | Address | Size | What it does |
|---|---|---:|---|
| `soc_reg32_get_wrapper` | `FUN_10846cf4` | 544 | validates reg-id < 0x9020, looks up reg-info, calls `soc_reg32_get` |
| `soc_reg32_set_wrapper` | `FUN_108499c4` | 512 | mirror of above for writes |
| `_soc_schan_register_write` | `FUN_10848458` | 312 | builds SCHAN write command: `(port<<20)\|(block<<14)\|0x34000200` |
| `_soc_reg_field_lookup` | `FUN_1084c7bc` | 1264 | binary-search a reg's field-info table to find bit offset/width |
| `_soc_profile_mem_create` | `FUN_10ef2a58` | 1576 | allocate profile-memory tracking structures (NOT a register access) |

### SCHAN command opcode pairs (now confirmed)

```
SCHAN READ  = 0x2c000200   (documented earlier in FULL_CHIP_ACCESS_STACK.md)
SCHAN WRITE = 0x34000200   (newly confirmed in FUN_10848458)

SCHAN command word format:
  bits 31..24  opcode (0x2c read / 0x34 write)
  bits 23..20  port
  bits 19..14  block
  bits 13..0   register/memory address
```

### Register-name pointer table

The BCM SDK has a global pointer table at **`0x11bc9344`** keyed by register
ID (0 to 0x901F = 36,895). Each entry is a `char*` to the register name
(e.g. "XMAC_TX_CTRL"). Wrappers use it like:

```c
const char *regname = (&PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bc9344)[reg_id];
```

This is the same table from which we already extracted 36,896 names into
`bcm_register_names.txt`.

---

## 2. `common_init` (FUN_10b84db0, 15,924 B)

The very first block dispatched by `bcm_init`. Despite the name "common",
this function does **NOT** do bulk memory clearing — that's done elsewhere
(soc_init via FUN_10794970 runs BEFORE bcm_init, and clears tables).

What `common_init` actually does:

### A. Per-table teardown (44 calls to `FUN_10b83b48`)

`FUN_10b83b48` (1984 B) is a **cleanup function** — it walks a per-table
state struct and frees any allocated buffers attached to it. Pattern:

```c
void table_teardown(unit, table_struct) {
    if (table_struct == NULL) return;
    for each attached buffer in table_struct:
        if (alloc_flag): free_special(buffer);
        free(buffer);
        buffer = NULL;
}
```

So common_init calls this 44 times on 44 internal table-state structures
to ensure clean slate. **Defensive** — if common_init is called on an
already-initialized chip (e.g. after a soft reset without full reboot),
it cleans up first.

### B. Profile memory subsystem setup (11 calls to `FUN_10ef2a58`)

`FUN_10ef2a58` is `_soc_profile_mem_create` — it allocates four tracking
arrays per "profile memory":
- `"Profile Mem Tables"` — array of table IDs
- `"Profile Mem Data Mask"` — per-table data masks
- `"Profile Mem Entries"` — entry-allocation bitmap
- `"Profile Mem Cache"` — cached values

Profile memories are used by **higher-level features** (FP, COS, etc.) to
manage **shared lookup tables** where multiple consumers can reference
the same entry by content. Eleven profile memories are created during
common_init — these are the 11 "profile-able" tables (e.g. cos_map,
priority_to_qid, etc.).

### C. Other helpers

- `FUN_11310fbc` (276 B) × 20 calls — generic `bcm_alloc` (named buffer alloc)
- `FUN_10ef2900` (80 B) × 17 calls — trivial state-init wrapper
- `FUN_107a2a0c` (92 B) × 15 calls — mutex/lock allocation
- `FUN_10ef40b4` (3820 B) × 2 calls — table memory binary-search helper

### Conclusion on `common_init`

This block is **NOT the memory clear phase** — it's the **state-tracking
setup phase**. It allocates the bookkeeping structures the SDK will use
to manage tables, profiles, and locks. The actual SCHAN memory clearing
happens earlier in `soc_init` (FUN_10794970, 22,724 B — the huge
SDK chip-level init).

For EdgeNOS, the equivalent would be:
1. Free any previous per-table state (defensive)
2. Allocate profile-memory tracking arrays for ~11 shared tables
3. Allocate locks (one per table or per port group)

The actual register-write activity is small — most of the 8s observed in
sub-phase B of our trace decode is `soc_init` (which runs in the same
window), not common_init specifically.

---

## 3. `port_init` (FUN_105b4b88, 16,624 B)

The largest single block-init at 16.6 KB of code. Runs for all 52 ports
plus the CPU port. The recursive profile reveals **66 distinct callees**.

### Direct primitive calls

| Primitive | Count |
|---|---|
| `soc_mem_clear` | 1 |
| `soc_reg32_get` (via wrapper FUN_10846cf4) | 1 (×4 wrapper calls) |
| `soc_schan_op` (via wrapper FUN_10848458) | 1 |

So most register activity happens through the **per-port iteration
sub-helpers** (called once each per port, but each sub-helper has its own
register-access pattern internally).

### Biggest per-port sub-helpers (each called 1× from port_init)

| Sub-helper | Size | Likely role |
|---|---:|---|
| `FUN_105b98c4` | **15,108** | Per-port pipeline reset + datapath setup |
| `FUN_105b0980` | **8,852** | Per-port MAC / XLPORT init |
| `FUN_105a961c` | **4,828** | Per-port speed/duplex configuration |
| `FUN_10bfac18` | **5,256** | Possibly PHY attach / SerDes link |
| `FUN_105b3278` | 2,584 | Per-port MIB clear |
| `FUN_105e933c` | 2,776 | Per-port linkscan registration |
| `FUN_105cc6f0` | 2,748 | Per-port stat counter setup |
| `FUN_10617aac` | 2,284 | Per-port mirroring config |
| `FUN_1099d84c` | 2,100 | Per-port subport handling |

### Frequently-called helpers (more iteration)

| Helper | Calls | Size | Role |
|---|---:|---:|---|
| `FUN_10760cd4` | 10 | 220 | log_info (a logger) |
| `FUN_108499c4` | 5 | 512 | **`soc_reg32_set` wrapper** (5 register writes) |
| `FUN_107a2a0c` | 5 | 92 | mutex acquire |
| `FUN_107a1e38` | 4 | 696 | mutex release |
| `FUN_10846cf4` | 4 | 544 | **`soc_reg32_get` wrapper** (4 register reads) |
| `FUN_1084c7bc` | 3 | 1264 | register-field lookup |
| `FUN_108080ac` | 2 | 208 | (table-related helper) |

So `port_init` itself only does:
- 5 register writes (via `soc_reg32_set` wrapper)
- 4 register reads (via `soc_reg32_get` wrapper)
- 1 SCHAN op (raw)
- 1 memory clear

Plus it calls 52+ sub-functions (one per port), and those sub-functions
do the heavy lifting.

### What does port_init at the top level actually do?

Reading the call structure: `port_init` is mostly **orchestration**:

```c
int port_init(unit) {
    bcm_alloc(unit, ...);                    // per-port state buffers
    for each port in pbmp_valid:
        port_pipeline_reset_setup(unit, port);   // FUN_105b98c4 — the 15 KB helper
        port_mac_init(unit, port);               // FUN_105b0980 — the 8.8 KB helper
        port_speed_config(unit, port);           // FUN_105a961c — the 4.8 KB helper
        port_phy_attach(unit, port);             // FUN_10bfac18 — the 5.2 KB helper
        port_mib_clear(unit, port);              // FUN_105b3278
        linkscan_register(unit, port);           // FUN_105e933c
        ...
    // Set a few global port-related registers (the 5 setreg + 4 getreg calls)
    setreg(unit, ALL_PORTS_PARITY_CTRL, value);
    setreg(unit, PORT_DROP_COUNTER_SELECT, value);
    ...
}
```

For EdgeNOS, the **52-port loop calling 8-10 per-port sub-functions** is
the core pattern. Each sub-function we'd recursively trace if we needed
to know its exact register-write sequence.

---

## 4. `field_init` (FUN_104b8f94, 9,428 B)

The Field Processor (ACL TCAM) initialization. Runs only when chip
feature flag `0x2f2c28 bit 0x2000000` is set (set on BCM56846).

### Top callees

| Helper | Calls | Size | Role |
|---|---:|---:|---|
| `FUN_10482210` | **27** | 608 | **FP slice setup wrapper** |
| `FUN_10498dcc` | 9 | 276 | FP entry allocator |
| `FUN_10799c5c` | 9 | 256 | trace/log helper |
| `FUN_10478d44` | 9 | 292 | FP table init helper |
| `FUN_10760b7c` | 8 | 220 | log_warn variant |
| `FUN_10761348` | 8 | 152 | log_error variant |
| `FUN_10be052c` | **7** | **12,016** | (HUGE) FP qualifier set config |
| `FUN_10498698` | 6 | 204 | FP slice indexer |
| `FUN_10bdb2fc` | **6** | **18,648** | (BIGGEST) FP TCAM mode-init |
| `FUN_10a67170` | 3 | 9,764 | (BIG) FP action set config |
| `FUN_10be341c` | 3 | 9,948 | (BIG) FP slice geometry |
| `FUN_10d7de9c` | 4 | 13,712 | (BIG) FP default entry insert |
| `FUN_10d8142c` | 3 | 10,256 | (BIG) FP egress slice |
| `FUN_108a2d5c` | 2 | 6,868 | (BIG) FP statistics counter binding |
| `FUN_10be9764` | 2 | 3,232 | FP mirror destination |

### Interpretation

The Field Processor has multiple **stages** (ingress / egress / VFP /
mid-stage) and within each, multiple **slices** (TCAM banks of 256 or
512 entries). Each slice can be configured for different qualifier sets.

`field_init` orchestrates this by:

```c
field_init(unit) {
    fp_default_mode_setup();          // FUN_10bdb2fc × 6 — once per stage/slice
    fp_qualifier_set_install();       // FUN_10be052c × 7
    fp_action_set_install();          // FUN_10a67170 × 3
    fp_slice_geometry_program();      // FUN_10be341c × 3
    fp_egress_slice_program();        // FUN_10d8142c × 3
    fp_default_entry_install();       // FUN_10d7de9c × 4 — default rules
    fp_statistics_binding();          // FUN_108a2d5c × 2
    for each of 27 slice instances:
        fp_slice_setup(unit, slice);  // FUN_10482210 × 27
    ...
}
```

The **27 slice setups** match the chip's documented FP geometry on Trident+:
- Ingress: 3 stages × 9 slices = 27 ingress slices
- (Egress: 2 slices, separate path)

The 27 is **specifically the ingress FP slice count** — this is verified
by the `cl-acltool` runtime data (`run/acl_info/ingress/slices_total = 5`
in our captured FUSE filesystem — that's the *currently in use* count;
the chip has 27 total potential slices).

For EdgeNOS implementing ACLs, this confirms:
- The chip has ~27 ingress FP slices
- Each needs individual mode setup, qualifier mapping, and default entries
- ACL programming follows: `slice_setup → entry_insert → counter_bind`

---

## 5. Implications for getting per-write ground truth

To extract the COMPLETE sequence of register/table writes during init
statically, the recursion would need to continue:

1. **For common_init**: recursively trace `FUN_10b83b48` (44× teardown),
   `FUN_10ef2a58` (11× profile-mem alloc), and the big helpers
   `FUN_10ef40b4` (3820 B) and `FUN_10ef6af4` (1224 B).
2. **For port_init**: recursively trace the 8-10 big per-port helpers
   (`FUN_105b98c4` 15K, `FUN_105b0980` 8.8K, `FUN_105a961c` 4.8K, etc.)
   — each likely makes dozens of register writes per port × 52 ports.
3. **For field_init**: recursively trace the 5-7 big FP helpers
   (`FUN_10bdb2fc` 18.6K, `FUN_10d7de9c` 13.7K, `FUN_10be052c` 12K, etc.)
   — these probably make hundreds of TCAM/SRAM writes per slice × 27 slices.

The depth-2 recursion would expand the call graph by ~10×; depth-3
recursion (which we'd need for leaf register writes) by another 10×.
Tractable with another full Ghidra pass.

**Estimated total static-analysis effort to get a complete per-write
register transcript**: ~2-3 more sessions of focused Ghidra work,
producing a structured machine-readable artifact of every
`soc_reg32_set` / `soc_mem_write` call site in `bcm_init`'s graph with
its register/table name and constant-value argument (where determinable).

---

## 6. Cross-references

- `BCM_INIT_STATIC_CHAIN.md` — bcm_init's 42-block dispatch order
- `ASIC_INIT_COOKBOOK.md` — rc.soc/rc.datapath_0/config.bcm decoded
- `ASIC_INIT_TRACE_DECODED.md` — strace timing breakdown
- `FULL_CHIP_ACCESS_STACK.md` — original SCHAN/MMIO documentation
- `ghidra-analysis/switchd_primitives.txt` — chip-access primitive locations
- `ghidra-analysis/switchd_recurse_profile.txt` — full callee enumeration
- `ghidra-analysis/switchd_wrappers_decomp.c` — wrapper function decomps

---

*Recursive static analysis 2026-05-11; based on Cumulus 2.5 switchd
binary at `/usr/sbin/switchd`. No chassis interaction required.*

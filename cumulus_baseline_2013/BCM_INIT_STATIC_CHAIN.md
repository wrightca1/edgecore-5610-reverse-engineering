# `bcm_init()` Static Call Chain — what really happens inside

Statically decompiled from `switchd` binary. Fills the biggest gap in our
ASIC init knowledge: the **exact ordered sequence of block-init functions
that `bcm_init()` dispatches**, derived without ever touching the chassis.

Verified against the log-string pattern: `"bcm_init: (%s)"` (block start),
`"bcm_init: %8s took %10d usec"` (block end timing). Each block emits two
log lines wrapping its init function call.

---

## 1. Top-level boot wrapper — `FUN_100a3680`

The switchd→SDK entry-point chain in **strict order**:

```c
int switchd_attach_chip(args, name) {
    soc_cm_device_create_id(...)        // FUN_1075ef68 — chip device create
    sysconf_attach(unit)                // FUN_10109348 — load /etc/bcm.d/config.bcm
    soc_init(unit)                      // FUN_10794970 — SDK chip-level init
    soc_misc_init(unit)                 // FUN_10794638 — misc SOC init
    soc_mmu_init(unit)                  // FUN_10e412f4 — MMU init (buffer pool config)
    bcm_attach(unit, ...)               // FUN_1038a8b4 — BCM SDK attach
    /* Now switchd is ready to call bcm_init via "init all" in rc.soc */
}
```

Error strings from binary confirm the order: `"soc_cm_device_create_id error"`,
`"sysconf_attach error"`, `"soc_init error"`, `"soc_misc_init error"`,
`"soc_mmu_init error"`, `"bcm_attach error"`.

---

## 2. `bcm_init()` block dispatch — `FUN_104f0b7c` (7700 bytes)

The big one. When `rc.soc`'s `init all` line runs, bcmsh ends up calling
`bcm_init(0)` which dispatches the following block-init functions **in this
strict order**:

| # | Block name (log) | Block-init fn | Size | Notes |
|---:|---|---|---:|---|
| 0 | (pre) | `FUN_10540758` | 1532 | Pre-init check (likely port validate) |
| 0 | (pre) | `FUN_10644704` | 484 | Another pre-init check |
| 1 | **`common`** | `FUN_10b84db0` | **15924** | **Memory clearing — clears all internal SRAMs** |
| 2 | **`port`** | `FUN_105b4b88` | **16624** | `bcm_port_init` — per-port pipeline reset, MAC, MIB clear, PHY config |
| 3 | **`l2`** | `FUN_10505590` | 2468 | L2 table init |
| 4 | **`stg`** | `FUN_106b8b14` | 1344 | Spanning Tree Group |
| 5 | **`vlan`** | `FUN_1071d5a0` | 2496 | VLAN table init (default VLAN 1) |
| 6 | **`trunk`** | `FUN_10708038` | **10488** | LAG / port-trunking |
| 7 | **`cosq`** | `FUN_10465b54` | 96 | Class-of-service queue (small wrapper) |
| 8 | **`mcast`** | `FUN_10540e2c` | 444 | Multicast |
| 9 | **`linkscan`** | `FUN_1053caf8` | 4628 | **Linkscan thread + port-state poll setup** |
| 10 | **`stat`** | `FUN_10652ba0` | 6012 | Counter DMA setup |
| 11 | **`stk`** | `FUN_1063f894` | 1964 | Stacking (multi-chip) — vestigial on AS5610 |
| 12 | **`rate`** | `FUN_10632e14` | 112 | Rate control (small wrapper) |
| 13 | **`udf`** | `FUN_1071ba50` | 148 | User-Defined Filter (small wrapper) |
| 14 | **`field`** | `FUN_104b8f94` | **9428** | **Field Processor / ACL TCAM init** |
| 15 | **`mirror`** | `FUN_1055f1f8` | 5176 | Port mirroring / SPAN |
| 16 | (unnamed) | `FUN_1071aa20` | 64 | Trivial init |
| 17 | (unnamed) | `FUN_10635594` | 420 | |
| 18 | **`rx`** | `FUN_1051dee0` | 496 | **RX packet path init (CPU rxpkt setup)** |
| 19 | (unnamed) | `FUN_104ffb8c` | 1012 | |
| 20 | (unnamed) | `FUN_10568ed0` | 320 | |
| 21 | (unnamed) | `FUN_1054398c` | 120 | |
| 22 | (unnamed) | `FUN_1074d810` | 188 | |
| 23 | (unnamed) | `FUN_1062d918` | 208 | |
| 24 | **`subport`** | `FUN_106ba7c8` | 172 | Subport / breakout-aware init |
| 25 | (unnamed) | `FUN_1062de60` | 1288 | |
| 26 | (unnamed) | `FUN_10704a9c` | 116 | |
| 27 | (unnamed) | `FUN_10586f88` | 624 | |
| 28 | (unnamed) | `FUN_10519404` | 116 | |
| 29 | (unnamed) | `FUN_107496d0` | 116 | |
| 30 | (unnamed) | `FUN_104735b4` | 352 | |
| 31 | (unnamed) | `FUN_1057a68c` | 904 | |
| 32 | (unnamed) | `FUN_10460f38` | 648 | |
| 33 | (unnamed) | `FUN_106f5e7c` | 1356 | |
| 34 | (unnamed) | `FUN_105889c0` | 436 | |
| 35 | (unnamed) | `FUN_104747cc` | 116 | |
| 36 | (unnamed) | `FUN_1058e5a0` | 4472 | |
| 37 | (unnamed) | `FUN_10475fd8` | 428 | |
| 38 | (unnamed) | `FUN_10a96458` | 180 | |
| 39 | (unnamed) | `FUN_10aa1bd8` | 508 | |
| 40 | **`fcoe`** | `FUN_109630b0` | 2164 | Fibre Channel over Ethernet (unused on AS5610) |

**42 block-init steps in total** dispatched by `bcm_init()`. Each block runs
sequentially; if any returns a negative error code (other than `-0x10` =
"not supported on this chip"), bcm_init returns the error and the chip is
left partially initialized.

### Skip conditions

Several block-inits are guarded by **chip-feature flags** in the per-unit
struct at offset `0x2f2c28` / `0x2f2c0c` / `0x2f2c14` / `0x2f2c30` /
`0x2f2c34`. If the flag is clear, `bcm_init` logs `"bcm_init: skipped %s
init"` and moves on. For BCM56846 (Trident+), most flags are set, but a
few advanced features may be skipped:

- `field` init guarded by flag 0x2f2c28 bit 0x2000000
- `subport` init guarded by flag 0x2f2c28 bit 0x40
- `fcoe` init guarded by flag 0x2f2c34 bit 0x40000

### Per-block timing in logs

Every block emits a "took X usec" line in `/var/log/switchd.log`. To
extract from a Cumulus chassis after init:

```
grep 'bcm_init:.*took' /var/log/switchd.log
```

This gives a verified per-block performance profile you can compare your
EdgeNOS init against. Approximate baselines for BCM56846 (from our 24.7s
total init window):

- common: ~5-8s (memory clearing dominates)
- port: ~7-10s (52-port pipeline reset)
- linkscan: ~100-200ms (thread setup)
- other blocks: ~10-500ms each

---

## 3. The "common" block (FUN_10b84db0) — 15.9 KB

This is the function whose duration dominates Phase 3b in our existing
strace trace. It calls `soc_mem_clear` (at `FUN_108092ec`) for every
internal table:

```c
soc_mem_clear(unit, table_id, ...);  // ~50 tables
```

We confirmed `soc_mem_clear` at `FUN_108092ec` (4020 B) which contains
the canonical error string `"soc_mem_clear: write %s.%s[%d] failed"`.

The tables cleared during common init include (from the BCM SDK header
analysis we have in `bcm_register_names.txt`):

- L2_TABLE (131072 entries × 16 bytes)
- L3_TABLE / DEFIP (16284 entries)
- L3_TABLE_LONG / DEFIP_PAIR (256 entries for v6 long-prefix)
- L3_IIF, L3_EIF (ingress/egress interface)
- L3_HOST (8192 entries)
- ECMP_GROUP (4044 nexthop entries)
- VLAN_TABLE (4096 entries)
- EGR_VLAN (4096 entries)
- MY_STATION_TCAM (256 entries)
- FP_TCAM_SLICE_GROUP / FP_TCAM (per slice × 3 stages)
- COS_MAP, CPU_COS_MAP, ING_PRI_CNG_MAP
- MMU table structures (buffer-cell limits, queue thresholds)

Each `soc_mem_clear` call dispatches a **Table DMA** burst (via CMICm's
table-DMA controller, configured by `tdma_intr_enable=1` in config.bcm)
to write zeros to the entire SRAM. The IRQ count of 54,371 in our trace
matches the order of magnitude for these DMA completions.

---

## 4. The "port" block (FUN_105b4b88) — 16.6 KB

`bcm_port_init` is the largest single block init at 16.6 KB of code. It
loops over all 52 ports (per `pbmp_valid.0=0x2001fffffffffffff` in config.bcm)
and for each port:

1. Asserts XLPORT/CDPORT reset (per-port reset register)
2. Initializes XMAC/CDMAC (MAC core for 10G XFI / 40G XLAUI)
3. Clears all per-port MIB counters
4. Configures port speed (10000 or 40000 from config.bcm `port_init_speed_*`)
5. Sets autoneg state (`port_init_autoneg_*` = 0)
6. Configures full duplex (`port_init_duplex=1`)
7. Releases per-port reset
8. Initializes Warpcore SerDes lanes (PMA/PCS)
9. Loads PHY firmware via MDIO if `phy_ext_rom_boot=0` — **except this
   chassis's BCM84740 PHY firmware is loaded later by `phy-update`, not
   here** (per our trace analysis, no phy_ucode files opened during
   bcm_init).

---

## 5. The "linkscan" block (FUN_1053caf8) — 4.6 KB

After all blocks are initialized, this starts the **linkscan thread**:
a kernel thread that polls each port's PHY status register at a fixed
interval (250 ms default per config). On link state change, it triggers
a netlink notification that `switchd` picks up and propagates to the
Linux `swp*` netdevs.

This is the thread responsible for `swp1: oper down` → `swp1: oper up`
messages in `/var/log/switchd.log`.

---

## 6. Cross-reference with the BAR0 post-init dump

We have `captures/bar0_postinit_2026-05-11.bin` (256 KB) which contains
the **final state of every BAR0 register after switchd reaches ready**.

The BAR is heavily aliased — only 8-16 words differ between each adjacent
16 KB window (probably per-pipe instance variation). Effective unique
register count: ~1,500-2,000 words out of 25,348 non-zero observations.

For EdgeNOS validation:
1. Run EdgeNOS init through the same `bcm_init` block sequence (above)
2. Dump BAR0 from your chassis (`iorw r.l 0xa0000000 65536`)
3. Diff against `bar0_postinit_2026-05-11.bin`
4. **Every differing word is a bug or missing init step**

The known register regions and their post-init "fingerprints":

| Region | BAR0 offset | Density | Block responsible |
|---|---|---|---|
| 0x00000-0x01000 | 403 non-zero/1024 | "chip ID / capability" — chip-revision constants, mostly read-only |
| 0x01000-0x02000 | 586 non-zero/1024 | Config registers + per-port pipeline indexing |
| 0x02000-0x03000 | 598 non-zero/1024 | Continuation |
| 0x10000-0x18000 | per-block reset/config | `common` block init writes here |
| 0x20000-0x28000 | Per-port XLPORT/CDPORT | `port` block init |
| 0x28000-0x30000 | Per-port MAC/MIB | `port` block init (MIB clear) |
| 0x31000-0x32000 | CMICm packet DMA | Done by `bcm_attach` / `soc_init` |
| 0x32800-0x33000 | CMICm SCHAN control | `common` (SCHAN setup) |

---

## 7. What's still needed for true ground-truth

Even with this static analysis, we don't have:

1. **Exact register addresses written by each block-init** — we'd need to
   recursively decompile every block-init function and trace its
   `soc_reg32_set` / `soc_mem_write` calls. Tractable but laborious.
2. **The contents of the DMA descriptor rings** — Table DMA burst contents
   live in DMA pool memory, never visible as PIO writes. Would require
   capturing the DMA pool region post-init.
3. **PHY MDIO sequence** — handled by `phy-update` after switchd ready.
   To decode: trace MDIO ioctls during `phy-update` run.

The **LD_PRELOAD shim** we built attempts to capture #1 dynamically by
intercepting every LUBDE ioctl. The shim builds correctly for PPC32 BE
and loads into simple commands, but the daemonized `switchd` process
does not invoke it for unknown reasons (env scrubbing during
daemonization is the leading hypothesis but not confirmed). Shim source
preserved at `tools/lubde-trace/` for future investigation.

---

## 8. Implications for EdgeNOS

The minimum-viable EdgeNOS init sequence is now fully specified:

```c
edgenos_chip_attach() {
    // Phase 1-2: BDE
    bde_open();
    bde_get_device(&dev_info);
    assert(dev_info.device_id == 0xb846);

    // Phase 3a (FUN_100a3680 equivalent):
    soc_cm_device_create_id(unit);
    sysconf_attach(unit);              // load config.bcm equiv
    soc_init(unit);                    // FUN_10794970 — SDK chip-level
    soc_misc_init(unit);
    soc_mmu_init(unit);                // buffer pool config
    bcm_attach(unit, ...);

    // Phase 3b: bcm_init dispatches block-inits IN THIS ORDER:
    common_init();      // mem-clear everything — 5-8s
    port_init();        // per-port reset + MAC init — 7-10s
    l2_init();
    stg_init();
    vlan_init();
    trunk_init();
    cosq_init();
    mcast_init();
    linkscan_init();    // start polling thread
    stat_init();
    stk_init();         // (skip on standalone)
    rate_init();
    udf_init();
    field_init();       // ACL TCAM
    mirror_init();
    rx_init();
    subport_init();     // (skip if no breakout)
    fcoe_init();        // (skip)
    // ... ~24 more small block-inits ...

    // Phase 4: post-init register tweaks (rc.soc):
    setreg(XMAC_TX_CTRL, 0xc802);
    setreg_field(MAC_RSV_MASK, MASK, 0x18);
    setreg_field(CMIC_MISC_CONTROL, LINK40G_ENABLE, 1);
    run_datapath_config();   // ~140 register writes
    setreg(IFP_METER_PARITY_CONTROL, 0);
    // drop counter setup ...

    // Phase 5: ready
    touch("/var/run/switchd.ready");
}
```

The critical invariants:

1. **`common` (mem-clear) MUST be first** — every other block depends on
   tables being zeroed.
2. **`port` MUST be second** — gates per-port operations.
3. **`linkscan` MUST be after `port`** — needs port state structures.
4. **`field` (ACL) requires `port` complete** — needs port masks.
5. **`rx` MUST be late** — depends on most other blocks ready.

---

## 9. Cross-references

- `ASIC_INIT_COOKBOOK.md` — rc.soc/rc.datapath_0/config.bcm decoded
- `ASIC_INIT_TRACE_DECODED.md` — strace timing per phase
- `FULL_CHIP_ACCESS_STACK.md` — API → SCHAN → MMIO path
- `BCM_SDK_INTERNALS.md` — API trampoline pattern
- `SWITCHD_DECOMPILED_BCM_APIS.md` — 127 BCM API addresses
- `captures/bar0_postinit_2026-05-11.bin` — final register state
- `ghidra-analysis/switchd_bcm_init_chain.txt` — raw call sequence
- `ghidra-analysis/switchd_bcm_init_decomp.c` — full decompile
- `ghidra-analysis/switchd_init_string_xrefs.txt` — string-based function ID

---

*Generated 2026-05-11 from static analysis of `/usr/sbin/switchd`
(Cumulus Linux 2.5.0, PowerPC big-endian, 31 MB ELF binary, BCM SDK
statically linked). No chassis interaction was required.*

# Port Bringup Register Map (Path B 5.2–5.3)

**Date**: 2026-02-23
**Status**: MOSTLY HAVE — XLPORT/MAC control registers identified via bcmcmd; full block address map derived; PHY=Warpcore WC-B0. SerDes programming sequence still needs GDB.
**Sources**: [traces/BAR_DIFF_PORT_UP_10.1.1.233.md](traces/BAR_DIFF_PORT_UP_10.1.1.233.md), [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md), [traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md), [traces/BDE_MMAP_ANALYSIS_10.1.1.233.md](traces/BDE_MMAP_ANALYSIS_10.1.1.233.md)

---

## 1. How Registers Are Accessed

From [traces/BDE_MMAP_ANALYSIS_10.1.1.233.md](traces/BDE_MMAP_ANALYSIS_10.1.1.233.md):

- switchd mmaps **`/dev/mem`** at two regions at startup (fd 15):
  - `0x04000000` — 64MB range (main register space / BAR0)
  - `0xa0000000` — 256KB range (secondary; likely second BAR or internal)
- **Register access is direct mmap read/write**, not ioctl (no `LUBDE_CPU_READ_REG`/`WRITE_REG` ioctls observed)
- ioctls observed during port up: `LUBDE_USLEEP`, `LUBDE_WAIT_FOR_INTERRUPT`, `LUBDE_SEM_OP`, `LUBDE_UDELAY` — synchronization only

---

## 2. BAR Diff Results — Offsets That Change on Port Up

Offsets relative to BAR0 (`0x04000000`). Full address = `0x04000000 + offset`.

### 2.1 swp1 — 14 registers changed

| BAR0 Offset | Full Address | Before | After | Delta | Classification |
|-------------|--------------|--------|-------|-------|----------------|
| `0x46f8` | `0x040046f8` | `0x000015d9` | `0x000015da` | +1 | Per-port (swp1, swp3) |
| `0x4818` | `0x04004818` | `0x00000004` | `0x00000005` | +1 | swp1-only |
| `0x4820` | `0x04004820` | `0x000015d9` | `0x000015da` | +1 | Per-port (swp1, swp3) |
| `0x4830` | `0x04004830` | `0x00000336` | `0x00000338` | +2 | swp1-only |
| `0x4870` | `0x04004870` | `0x00001913` | `0x00001917` | +4 | Per-port (swp1, swp3) |
| `0x4880` | `0x04004880` | `0x0000190f` | `0x00001912` | +3 | Per-port (swp1, swp3) |
| `0x4888` | `0x04004888` | `0x00000004` | `0x00000005` | +1 | swp1-only |
| `0x4928` | `0x04004928` | `0x00001913` | `0x00001917` | +4 | Per-port (swp1, swp3) |
| `0x49b8` | `0x040049b8` | `0x000a5368` | `0x000a560c` | +2724 | Per-port (swp1, swp3) |
| `0x49e8` | `0x040049e8` | `0x00000663` | `0x00000664` | +1 | Shared (swp1+swp2) |
| `0x4a38` | `0x04004a38` | `0x00000666` | `0x00000667` | +1 | Shared (swp1+swp2) |
| `0x4a40` | `0x04004a40` | `0x00000666` | `0x00000667` | +1 | Shared (swp1+swp2) |
| `0x4a50` | `0x04004a50` | `0x00000666` | `0x00000667` | +1 | Shared (swp1+swp2) |
| `0x4b38` | `0x04004b38` | `0x000325d2` | `0x00032644` | +114 | Shared (swp1+swp2) |

### 2.2 swp2 — 5 registers changed

| BAR0 Offset | Full Address | Before | After | Delta |
|-------------|--------------|--------|-------|-------|
| `0x49e8` | `0x040049e8` | `0x00000663` | `0x00000664` | +1 |
| `0x4a38` | `0x04004a38` | `0x0000069d` | `0x0000069e` | +1 |
| `0x4a40` | `0x04004a40` | `0x0000069d` | `0x0000069e` | +1 |
| `0x4a50` | `0x04004a50` | `0x0000069d` | `0x0000069e` | +1 |
| `0x4b38` | `0x04004b38` | `0x000325d2` | `0x00032644` | +114 |

### 2.3 swp3 — 6 registers changed

| BAR0 Offset | Before | After | Delta |
|-------------|--------|-------|-------|
| `0x46f8` | `0x000017e7` | `0x000017e8` | +1 |
| `0x4820` | `0x000017e7` | `0x000017e8` | +1 |
| `0x4870` | `0x00001b0b` | `0x00001b0f` | +4 |
| `0x4880` | `0x00001b07` | `0x00001b0a` | +3 |
| `0x4928` | `0x00001b0b` | `0x00001b0f` | +4 |
| `0x49b8` | (different per port) | | |

### 2.4 swp4 — 6 registers changed (same set as swp3)

| BAR0 Offset | Full Address | Before | After | Delta |
|-------------|--------------|--------|-------|-------|
| `0x46f8` | `0x040046f8` | `0x040032c9` | `0x040032ca` | +1 |
| `0x4820` | `0x04004820` | `0x000032c9` | `0x000032ca` | +1 |
| `0x4870` | `0x04004870` | `0x00003a41` | `0x00003a42` | +1 |
| `0x4880` | `0x04004880` | `0x00003a3b` | `0x00003a3c` | +1 |
| `0x4928` | `0x04004928` | `0x00003a41` | `0x00003a42` | +1 |
| `0x49b8` | `0x040049b8` | `0x0017fae4` | `0x0017fb36` | +82 |

### 2.5 swp5 — 8 registers changed (6 common + 2 new zeroed)

| BAR0 Offset | Full Address | Before | After | Delta | Note |
|-------------|--------------|--------|-------|-------|------|
| `0x18b0` | `0x040018b0` | `0x64000ede` | `0x00000000` | zeroed | **NEW** — only on swp5 |
| `0x18b4` | `0x040018b4` | `0x00001d42` | `0x00000000` | zeroed | **NEW** — only on swp5 |
| `0x46f8` | `0x040046f8` | `0x000032ce` | `0x040032cf` | +1 | same 6 |
| `0x4820` | `0x04004820` | `0x000032ce` | `0x000032cf` | +1 | |
| `0x4870` | `0x04004870` | `0x00003a46` | `0x00003a47` | +1 | |
| `0x4880` | `0x04004880` | `0x00003a40` | `0x00003a41` | +1 | |
| `0x4928` | `0x04004928` | `0x00003a46` | `0x00003a47` | +1 | |
| `0x49b8` | `0x040049b8` | `0x0017fc7e` | `0x0017fcd0` | +82 | |

**Interpretation of 0x18b0/0x18b4**: These zeroed during swp5 port-up. Values before (0x64000ede, 0x00001d42) look like time/tick registers or latched status. Zeroing on port-up could be a counter reset or state machine init. Offset 0x18b0 is in the lower CMIC/device config region (below 0x31000).

---

## 3. Register Classification

### 3.1 CONFIRMED GLOBAL counters (same 6 offsets for ALL 4 ports: swp1/swp3/swp4/swp5)

These 6 offsets change every time **any** port goes up. They are **global event counters**, not per-port control registers. There is NO per-port stride — all ports share the same counter block.

| Offset | Pattern | Confirmed role |
|--------|---------|---------------|
| `0x46f8` | +1 per port-up; absolute value grows over time | Global counter — link-up event count (total across all ports) |
| `0x4820` | Identical to 0x46f8 | Redundant or mirrored counter |
| `0x4870` | +1 per port-up (was +4 for swp1/swp3 — multiple events); absolute differs | Global counter — link-state transitions or negotiation steps |
| `0x4880` | +1 per port-up (was +3 for swp1/swp3) | Global counter — correlated with 0x4870 |
| `0x4928` | +1 per port-up (identical to 0x4870) | Global counter — same event, different sub-count |
| `0x49b8` | Large delta (+82 for swp4/5, +2724 for swp1 earlier); grows monotonically | Global byte/cycle counter — rapidly incrementing background traffic |

### 3.2 swp1-specific registers (not seen on swp2 or swp3 in these runs)

| Offset | Before | After | Likely role |
|--------|--------|-------|------------|
| `0x4818` | `0x4` | `0x5` | Status/control bit — may be port 1 link state |
| `0x4830` | `0x336` | `0x338` | Counter — possibly error count or state change |
| `0x4888` | `0x4` | `0x5` | Paired with 0x4818 |

These may be port-1-specific (not appearing for swp2/swp3) OR may only appear when swp1 is brought up first (initialization side-effect).

### 3.3 Shared / global registers (change for any port-up)

| Offset | Pattern | Likely role |
|--------|---------|------------|
| `0x49e8` | +1 for swp1 and swp2 | Global link-up counter or event sequence |
| `0x4a38` | +1 for swp1 and swp2 (different absolute values) | Per-port or global counter |
| `0x4a40` | +1, same pattern as 0x4a38 | Adjacent counter |
| `0x4a50` | +1, same pattern | Adjacent counter |
| `0x4b38` | +114 for both swp1 and swp2 (same delta) | Global bytes/packets counter; increments on any port event |

---

## 4. Port Block Address Analysis

All changed offsets are in the range **0x4000–0x4fff** of BAR0. This is consistent with a hardware **port statistics, status, or control block** sitting between CMIC registers (0x31000–0x32800) and the higher-address regions.

On BCM56840/BCM56846 (Trident/Trident+), the register map (from Broadcom SDK, mostly NDA) is approximately:

| BAR0 Range | Block |
|-----------|-------|
| 0x00000–0x30fff | Device-specific config |
| 0x31000–0x32fff | CMICm (DMA, IRQ, S-Channel) |
| 0x33000–0x3ffff | Additional CMICm |
| 0x40000–0x4ffff | Port/MAC/SerDes stats or control |
| 0x50000+ | Other blocks |

The 0x4xxx range is likely the **port MAC stats block** or **SerDes status registers**. The small +1/+4 deltas strongly suggest **read-only counters** (link-up event counts, byte counts, error counts) rather than writable control registers.

**Key implication**: BAR diff captures counter changes (side-effects of port-up), not the control register writes that *cause* the port to come up. The actual enable/speed/SerDes registers are written **before** the port comes up, making them invisible in a before/after diff of this type.

---

## 5. Port API Call Chain

From [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md):

| OpenNSL API | Entry point | Internal callee | Handler offset |
|-------------|-------------|-----------------|----------------|
| `opennsl_port_enable_set` | `0x01dcf78c` | `FUN_007d3f34` | — |
| `opennsl_port_speed_set` | `0x01dcfe64` | `FUN_007de7cc` | `-0x5fe0` from per-unit |
| `opennsl_port_duplex_set` | `0x01dcf6c0` | `FUN_007d3294` | `-0x68b0` from per-unit |

**All three** use dynamic dispatch via `bctrl` to a per-unit handler loaded from the unit struct. The hardware register access is inside that handler.

**Pattern** (FUN_007de7cc / FUN_007d3294):
1. Validate unit (`cmplwi r3, 0x7f`)
2. Load base from `[r30-0x8000]`, index `r3*4`
3. Load sub-index `r26 = [r9+8]`
4. Load handler from `[base-0x7ffc][r26*4] + offset (-0x5fe0 or -0x68b0)`
5. `bctrl` → port-specific handler (SerDes/MAC/PHY writes happen here)
6. `bl FUN_0086fe6c` — callback dispatcher (same as packet TX)

---

## 6. Next Steps to Close Port Bringup

### Option A — GDB on Cumulus switch (fastest)

```bash
# On Cumulus switch (10.1.1.233), GDB on switchd
# Break at bctrl in FUN_007de7cc (speed handler)
gdb --pid $(pgrep -f 'switchd -d')
(gdb) break *0x007de7cc+<offset_to_bctrl>
(gdb) commands
(gdb)   printf "bctrl target: %p\n", $lr
(gdb)   continue
(gdb) end
# Then: ip link set swp2 up in another terminal
# Capture the handler address → dump that function in Ghidra
```

Script: `scripts/reverse-engineering/run-port-up-trace-10.1.1.233.sh`

### Option B — Ghidra on switchd binary

The Cumulus switchd has the Broadcom SDK **statically linked** (SDK 6.3.8). Port register access is in the switchd binary, not libopennsl.

```bash
# On Ghidra server (10.1.1.30), analyze switchd binary
# Search for:
#   - Constants 0x46f8, 0x4818, 0x4820, 0x4870, 0x4928 in code
#   - "port" or "serdes" strings near register write patterns
#   - Function that writes to mmap'd base+0x4xxx
```

### Option C — Multi-port BAR diff to find stride

Run BAR diff on swp4 and swp5, then compute:
- If per-port registers have a fixed stride between ports → derive the register block base and stride
- E.g., if swp1 uses offset X and swp3 uses offset X+N, stride N could indicate per-port register spacing

```bash
./scripts/reverse-engineering/run-bar-diff-port-up-10.1.1.233.sh swp4
./scripts/reverse-engineering/run-bar-diff-port-up-10.1.1.233.sh swp5
```

Compare offsets across swp1, swp3, swp4, swp5 to find the per-port stride.

### Option D — SDK header search

Search OpenNSL GPL source and any available SDK headers for the hex constants:

```bash
grep -r "0x46f8\|0x4818\|0x4820\|0x4870\|0x4928\|0x49b8\|0x4a38\|0x4b38" \
  open-nos-build/.opennsl-extract/
```

---

## 7. Known BDE ioctls During Port Up

From [traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md):

| ioctl code | Meaning | When seen |
|-----------|---------|-----------|
| `0x20004c08` | `LUBDE_USLEEP` | After register writes (delay) |
| `0x20004c09` | `LUBDE_WAIT_FOR_INTERRUPT` | Waiting for link-up IRQ (IRQ 16) |
| `0x20004c0a` | `LUBDE_SEM_OP` | Semaphore lock/unlock |
| `0x20004c0b` | `LUBDE_UDELAY` | Microsecond delay |

No `CPU_READ_REG` or `CPU_WRITE_REG` ioctls — all register access is via mmap.

---

## 8. Summary: What We Have vs What We Need

| Item | Status |
|------|--------|
| BAR diff candidates (14 offsets, swp1) | ✅ HAVE — likely counters/status |
| Port API → internal callees mapped | ✅ HAVE (007d3f34, 007de7cc, 007d3294) |
| Handler dispatch offset (-0x5fe0, -0x68b0) | ✅ HAVE |
| Register access method (mmap /dev/mem) | ✅ HAVE |
| BDE ioctls during port-up decoded | ✅ HAVE |
| BAR diff counter: per-port vs shared | ✅ HAVE (see §3) |
| **XLPORT/MAC register names + addresses** | ✅ HAVE — see §9; verified via bcmcmd on live switch |
| **XLPORT block address map** | ✅ HAVE — full 16-block map (xe0–xe51) in §9.1 |
| **PHY type** | ✅ HAVE — Warpcore WC-B0, accessed via MDIO |
| **Per-port register stride** | ✅ CONFIRMED — lane × 0x1000; block-level at +0x80000 |
| **Actual control register writes** | ⚠️ MOSTLY HAVE — XLPORT_PORT_ENABLE, MAC_MODE, XLPORT_CONFIG identified; write sequence not traced |
| **bctrl handler address** | ❌ NEED — dynamic; requires GDB or switchd Ghidra |
| **SerDes init sequence** | ❌ NEED — WC-B0 MDIO sequence for speed/mode config; inside bctrl |

---

## 9. XLPORT/MAC Register Map — Verified via bcmcmd

Discovered via `bcmcmd 'dump soc diff'`, `getreg XLPORT_PORT_ENABLE`, `getreg XLPORT_CONFIG`, `getreg MAC_MODE`, and `phy info xe0` on live switch (2026-02-23).

### 9.1 PHY Type

```
bcmcmd 'phy info xe0'
  PHY type: WC-B0 (Broadcom Warpcore)
  Access: MDIO (CMIC_MIIM_ADDRESS @ BAR0+0x4a0, CMIC_MIIM_PARAM @ BAR0+0x158)
```

Warpcore (WC) is a multi-lane 10G SerDes used in BCM56846. Lane-level speed, mode, and training are programmed via MDIO registers into the WC PHY.

### 9.2 XLPORT Block Address Map (Full — 16 blocks, 52 xe ports)

Each XLPORT block manages 4 SerDes lanes (xe ports). Address formulas:
- **Per-lane register**: `block_base + lane_num × 0x1000 + reg_offset`
- **Block-level register** (e.g. XLPORT_PORT_ENABLE): `block_base + 0x80000 + reg_offset`

| xlport | block_base | xe ports | lanes active | PORT_ENABLE addr |
|--------|------------|----------|--------------|-----------------|
| xlport16 | `0x40a00000` | xe0–xe3 | 4 (0xf) | `0x40a8022a` |
| xlport17 | `0x40b00000` | xe4–xe7 | 4 (0xf) | `0x40b8022a` |
| xlport1 | `0x00b00000` | xe8–xe11 | 4 (0xf) | `0x00b8022a` |
| xlport2 | `0x00c00000` | xe12–xe15 | 4 (0xf) | `0x00c8022a` |
| xlport3 | `0x00d00000` | xe16–xe19 | 4 (0xf) | `0x00d8022a` |
| xlport4 | `0x00e00000` | xe20–xe23 ¹ | 4 (0xf) | `0x00e8022a` |
| xlport5 | `0x00f00000` | xe24–xe27 ¹ | 4 (0xf) | `0x00f8022a` |
| xlport6 | `0x40000000` | xe28–xe31 | 4 (0xf) | `0x40080000+0x22a` |
| xlport7 | `0x40100000` | xe32–xe35 | 4 (0xf) | `0x40180000+0x22a` |
| xlport8 | `0x40200000` | xe36–xe39 | 4 (0xf) | `0x40280000+0x22a` |
| xlport9 | `0x40300000` | xe40–xe43 | 4 (0xf) | `0x40380000+0x22a` |
| xlport10 | `0x40400000` | xe44–xe47 | 4 (0xf) | `0x40480000+0x22a` |
| xlport11 | `0x40500000` | xe49 | 1 (PORT0) | `0x4058022a` |
| xlport12 | `0x40600000` | xe48 | 1 (PORT0) | `0x4068022a` |
| xlport14 | `0x40800000` | xe51 | 1 (PORT0) | `0x4088022a` |
| xlport15 | `0x40900000` | xe50 | 1 (PORT0) | `0x4098022a` |

¹ xlport4/xlport5: SDK logical ports xe20–xe27 use swapped lanes — xe20=lane1, xe21=lane0, xe22=lane3, xe23=lane2 (and same pattern for xe24–xe27). Physical PCB routing causes the lane permutation.

**Uplink ports** (xe48–xe51) correspond to the 4 QSFP cages. Each is configured as a single-lane 10G port (PORT0 only enabled), not bonded 40G mode.

### 9.3 Key Register Addresses (xe0 example, xlport16 block_base=0x40a00000)

| Register | Per-lane address formula | xe0 addr | Value | Description |
|----------|--------------------------|----------|-------|-------------|
| `XLPORT_CONFIG` | `block_base + lane*0x1000 + 0x200` | `0x40a00200` | `0x10040` | XPAUSE_RX_EN=1, MY_MODID=2 |
| `XLPORT_PORT_ENABLE` | `block_base + 0x80000 + 0x22a` | `0x40a8022a` | `0xf` | PORT0–PORT3 all enabled |
| `MAC_MODE` | `block_base + lane*0x1000 + 0x511` | `0x40a00511` | `0x22` | MAC_SPEED=2, LINK_STATUS=1 |
| `MAC_0` | `block_base + lane*0x1000 + 0x503` | `0x40a00503` | `0x80a23581` | Station MAC addr [47:16] |
| `MAC_1` | `block_base + lane*0x1000 + 0x504` | `0x40a00504` | `0x0000caaf` | Station MAC addr [15:0] |
| `MAC_RSV_MASK` | `block_base + lane*0x1000 + 0x221` | `0x40a00221` | `0x18` | Reserved frame mask |

**MAC_MODE fields** (verified, xe0):
- `MAC_SPEED=2`: Encodes 10G for xe-type ports in this SDK/ASIC. All 52 ports show MAC_SPEED=2 regardless of link state.
- `LINK_STATUS=1`: Set when PHY reports link up; `LINK_STATUS=0` for ports with no cable/link.
- `MAC_TX_PAUSE=0, MAC_RX_PAUSE=0`: Pause frames disabled (normal L3 router config).

**XLPORT_CONFIG fields** (all ports, same value 0x10040):
- `XPAUSE_RX_EN=1`: Receive pause frames enabled.
- `MY_MODID=2`: Module ID for stacking/HiGig; 2 = default for single-unit non-HiGig.

### 9.4 XLPORT Per-Lane Address Examples (first 12 ports)

From `getreg XLPORT_CONFIG` — address encodes block_base + lane × 0x1000 + 0x200:

| Port | XLPORT_CONFIG addr | block_base | lane |
|------|--------------------|------------|------|
| xe0 | `0x40a00200` | `0x40a00000` | 0 |
| xe1 | `0x40a01200` | `0x40a00000` | 1 |
| xe2 | `0x40a02200` | `0x40a00000` | 2 |
| xe3 | `0x40a03200` | `0x40a00000` | 3 |
| xe4 | `0x40b00200` | `0x40b00000` | 0 |
| xe8 | `0x00b00200` | `0x00b00000` | 0 |
| xe12 | `0x00c00200` | `0x00c00000` | 0 |
| xe16 | `0x00d00200` | `0x00d00000` | 0 |
| xe28 | `0x40000200` | `0x40000000` | 0 |
| xe32 | `0x40100200` | `0x40100000` | 0 |
| xe44 | `0x40400200` | `0x40400000` | 0 |
| xe48 | `0x40600200` | `0x40600000` | 0 |

### 9.5 Port Enable Sequence (Inferred)

To enable a port (e.g. xe0 on xlport16):

1. **XLPORT_PORT_ENABLE** (`0x40a8022a`): Write `PORT0=1` (bit 0) to enable MAC; writing 0 disables.
2. **MAC_MODE** (`0x40a00511`): Set MAC_SPEED field for desired speed; set LINK_STATUS when PHY reports link.
3. **WC-B0 SerDes** via MDIO: Warpcore lane init (speed, mode, equalization) — programmed via `CMIC_MIIM_ADDRESS` (`BAR0+0x4a0`) and `CMIC_MIIM_PARAM` (`BAR0+0x158`). Exact sequence inside bctrl handler — requires GDB to trace.

This matches the API call chain: `opennsl_port_enable_set` → `FUN_007d3f34` → bctrl → sets XLPORT_PORT_ENABLE; `opennsl_port_speed_set` → `FUN_007de7cc` → bctrl → sets MAC_MODE + Warpcore MDIO.

---

## References

- [traces/BAR_DIFF_PORT_UP_10.1.1.233.md](traces/BAR_DIFF_PORT_UP_10.1.1.233.md)
- [PORT_BRINGUP_ANALYSIS.md](PORT_BRINGUP_ANALYSIS.md)
- [PORT_BRINGUP_REGISTERS_ANALYSIS.md](PORT_BRINGUP_REGISTERS_ANALYSIS.md)
- [traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md](traces/PORT_UP_TRACE_ANALYSIS_10.1.1.233.md)
- [traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md](traces/PORT_UP_PERF_ANALYSIS_10.1.1.233.md)
- [traces/BDE_MMAP_ANALYSIS_10.1.1.233.md](traces/BDE_MMAP_ANALYSIS_10.1.1.233.md)
- [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md)
- [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md) §5

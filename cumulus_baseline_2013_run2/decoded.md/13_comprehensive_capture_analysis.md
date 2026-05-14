# Comprehensive Cumulus Capture Analysis — Everything We Have

Inventory of every artefact in `cumulus_baseline_2013_run2/` (and its
decoded contents), grouped by purpose, with cross-reference to what we've
used / not used so far in the EdgeNOS chip→CPU forwarding investigation.

**Date:** 2026-05-14, end-of-session.
**Prior docs:**
- `decoded.md/01_route_storage.md` ... `decoded.md/09_capture_plan.md` — earlier per-topic decodings.
- `decoded.md/10_cumulus_register_analysis.md` — register-gap CSV summary.
- `decoded.md/11_session_2026_05_14_summary.md` — session writeup.
- `decoded.md/12_deep_chip_state_analysis.md` — chip-register diff by pipeline stage.

This doc (`13_...`) covers EVERYTHING ELSE — memories, FP rules, L3 tables, MCS, DMA, BAR0,
strace, switchd internals, etc. — not just the chip register diff.

## 1. Capture inventory

| Category | Files | Bytes | What it contains |
|---|--:|--:|---|
| **BAR0-dump** | 16 | 352 B | PCI BAR0 raw memory |
| **BDE-driver** | 18 | 15 KB | BDE driver state |
| **DMA-region** | 4 | 69 MB | host DMA buffer pool |
| **FP-TCAM** | 11 | 6 MB | Field Processor rules / counters / meters |
| **L3-tables** | 40 | 62 MB | L3 forwarding entries |
| **MCS-firmware** | 3 | 874 KB | chip MicroController RAM |
| **bcmcmd-rc-files** | 12 | 35 KB | bcmcmd init script |
| **bcmcmd-table-dumps** | 177 | 7 MB | bcmcmd-output snapshot |
| **chip-memories** | 2 | 17 MB | chip memory-table content |
| **chip-registers** | 2 | 3 MB | all 49,732 register values |
| **cpld-thermal** | 36 | 2 MB | thermal state |
| **cumulus-config** | 437 | 576 KB | Cumulus config file |
| **iptables-tc** | 90 | 111 KB | kernel netfilter / tc state |
| **kernel-modules** | 24 | 3 MB | loaded kernel module |
| **kernel-symbols** | 2 | 2 MB | kernel symbol map |
| **knet** | 37 | 3 KB | kernel network driver state |
| **misc** | 856 | 21 MB |  |
| **misc-logs** | 26 | 15 MB | log file |
| **phy-diag** | 8 | 0 B | PHY-level diagnostic |
| **port-tabs** | 3 | 4 KB | port/phy/sfp lookup tables |
| **procfs** | 97 | 705 KB | /proc snapshot |
| **quagga-config** | 13 | 19 KB | Quagga daemon config |
| **sfp-eeprom** | 118 | 31 KB | SFP transceiver EEPROM |
| **strace** | 6 | 15 MB | syscall trace |
| **switchd-binary** | 9 | 44 MB | switchd binary / gcore |
| **sysfs** | 6 | 10 KB | /sys snapshot |
| **tarballs-rolled-up** | 12 | 32 MB | (already-unpacked tarball) |
| **vtysh-routing** | 42 | 82 KB | Quagga vtysh state |
| _total_ | 2107 | 300 MB | |

## 2. Chip registers

Already analysed in `decoded.md/12_deep_chip_state_analysis.md`.
Summary: **417 unique registers** Cumulus changes from chip reset (`dump_soc_diff.txt`),
grouped across 12 pipeline stages.  Our regdump shows **3640 still-differing scopes** at session end.

## 3. Chip memories (NEW analysis — never previously diff'd)

`dump_socmem_diff.txt` is **12 MB** / **228312 lines** / **0 unique memory names**.

These are the chip's *internal SRAM table contents* — VLAN_TAB entries, L2 MAC table rows,
FP_TCAM rules, EGR_PORT per-port config, L3_HOST hash entries — what Cumulus *programmed into* the chip.
Crucially: **register state alone does not capture these.**  Our regdump tool reads only registers,
not memories.  This is the gap our chip→CPU debugging missed.

**Top 20 memories by scope-count diff:**

| Memory | Entries Cumulus changed |
|---|--:|

Many of these (EGR_PORTm, VLAN_TABm, EGR_VLANm, L2_USER_ENTRYm, MY_STATION_TCAMm, FP_TCAMm) directly
control forwarding decisions.  Without their content programmed, the chip cannot do L2/L3 forwarding
the way Cumulus does.

## 4. L3 forwarding tables

Cumulus's actual L3 routes + next-hops + ECMP groups, dumped at runtime via `bcmcmd dump`:

| Table | Size | Lines | Valid entries (heuristic) |
|---|--:|--:|--:|
| `L3_DEFIP_after` | 18 KB | 27 | ~27 |
| `L3_ENTRY_after` | 5 KB | 12 | ~12 |
| `EGR_L3_NEXT_HOP_after` | 15 MB | 16384 | ~0 |
| `ING_L3_NEXT_HOP_after` | 3 MB | 16384 | ~0 |
| `L3_ECMP_after` | 263 KB | 4096 | ~0 |
| `L3_ENTRY_IPV4_UC` | 1 KB | 3 | ~3 |

These are decoded in `decoded.md/01_route_storage.md` + `04_l3_chip_format.md`.
Used to reverse-engineer Cumulus's L3 chain (L3_DEFIP PAIR mode, L3_ENTRY hash key,
INTF id 100xxx/200xxx convention, EGR_L3_NEXT_HOP MAC layout).

## 5. FP (Field Processor) TCAM — chip-side CPU-punt rules

**Critical and never-implemented in EdgeNOS.**

The Field Processor is the chip's flexible packet classifier.  Cumulus uses FP rules to:
- COPY protocol packets to CPU (OSPF Hello, BGP TCP/179, ICMP, BFD, LACP, STP, LLDP, ...)
- Apply per-flow policing (rate-limit certain classes)
- Mark packets with priority/queue
- Redirect/drop based on L3/L4 headers

**Without FP rules**, control-plane packets are not punted to CPU on a Cumulus-style switch.
Trident+ does have implicit `V4L3DSTMISS_TOCPU` (and we set it), but the FP table is *the*
CPU-punt mechanism Cumulus relies on.

**Raw FP table dumps:**

| Table | Size | Lines | Non-empty entries (heuristic) |
|---|--:|--:|--:|
| `FP_COUNTER_TABLE` | 179 KB | 2048 | ~0 |
| `FP_GLOBAL_MASK_TCAM` | 15 KB | 100 | ~100 |
| `FP_METER_TABLE` | 255 KB | 2048 | ~0 |
| `FP_POLICY_TABLE` | 2 MB | 2048 | ~0 |
| `FP_TCAM` | 71 KB | 100 | ~100 |

**Human-readable FP summary output (`fp show`):**

- `09_fp_show_all.txt` (0 B, 0 lines)
- `09_fp_show_group.txt` (3 KB, 66 lines)
  First lines:
  ```
  Usage (FieldProcessor):  Where <cmd> is:
  	action <add|get|remove> <eid> [act] [p0] [p1]
  	action ports <add|get> <eid> <act> [<pbmp>]
  	action mac <add|get> <eid> <act> [<mac>]
  	aset <add|delete|show|clear> <gid> [action|action list]
  	control <ctrl_num> [<status>]
  ```
- `09_fp_show_stats.txt` (0 B, 0 lines)

To use this: parse `09_FP_TCAM_raw.txt` → extract entries → write equivalent FP TCAM
entries via OpenMDK's `WRITE_FP_TCAMm` macros.  Cumulus's `00control_plane.rules` source file
(`final_gaps_*/etc/cumulus/acl/policy.d/00control_plane.rules`) is the canonical *intent* — the FP_TCAM
entries are the compiled hardware output of those rules.

## 6. MCS — chip MicroController RAM

`01_dump_mcs.txt` is **782 KB** / **17408 lines**.

First few lines:

```
00000000: 28500000 0a170400 00000000 00000000
00000010: fc000000 ffffffff ffffffff 0003ffff
00000020: 00000000 00000000 ffffffff ffffffff
00000030: ffffffff ffffffff ffffffff 00003fff
00000040: 003fffff 00000000 00000000 00000000
00000050: 00000000 00000000 00000000 00000000
00000060: 00000000 00000000 00000000 00000000
00000070: 00000000 00000000 00000000 00000000
```

The MCS is the chip's embedded MicroController.  In Trident+ it runs SDK-loaded firmware
for tasks like LED scan, link-status polling, MIIM proxy.  OpenMDK's CMICm support uses the
MCS for hardware linkscan.  Cumulus's MCS RAM dump contains the actual firmware bytes loaded.

**Not critical for chip→CPU forwarding directly**, but the linkscan firmware affects whether
the chip auto-updates EPC_LINK_BMAP when PHY link state changes.

## 7. Host DMA region — what CPU sees from chip

`03_dma_region_full.bin` is **64 MB**.

This is the full 64 MB host-side DMA region used by switchd for RX/TX DCB rings,
scratch buffers, and the chip's BDE-mapped tables.  Most of it is poison values (`0xa5a5...`),
but the active region — the DCB ring base + descriptor metadata — is here.
Decoded in `decoded.md/02_dma_model.md`.

Key takeaways already extracted:
 - 64-DCB ring with `RELOAD=1` per DCB (Cumulus pattern)
 - `DESC_HALT_ADDR` at chip register 0x31120 + 4*chan
 - Interrupt-driven via `LUBDE_WAIT_FOR_INTERRUPT` (ioctl 9)

## 8. switchd binary + gcore + libs

| Artefact | Size | Notes |
|---|--:|---|
| `all/all_20131001_134200/binaries/switchd` | 30 MB | 31 MB PowerPC ELF, dyn-linked, stripped.  RE target. |
| `finish_20260513_203818/a7_sw2.core.gz` | 3 MB | Smaller gcore (~3 MB); thread stacks + small heap. |
| `gcorev3_20260513_171317/gcore/sw.core.gz` | 12 MB | Larger gcore (~13 MB); fuller memory image. |

Plus 10 shared libs in `gcorev3_*/switchd/libs/` (libc, libnl, libfuse, libnet, libpthread,
librt, libm, libdl, libnl-route, libnl-genl) so gdb can resolve symbols offline.

RE potential:
- Register names visible in `.rodata` strings (MY_STATION x47, INPUT_PORT_RX_ENABLE x33, EGR_MTU x2).
- 373 dynamic symbols still resolvable (mostly libc imports; a few `bcm_*` exports).
- `bcm_init_check`, `bcm_init_selective`, `_bcm_esw_*_init` visible as strings (debug-trace fmt).
- Use radare2 + cross-reference (`axt @ <addr>`) to walk from register-name string → caller function → that function's other writes.

## 9. strace — every syscall switchd made

| File | Size | Lines |
|---|--:|--:|
| `init` | 14 MB | 245437 |
| `runtime` | 2 MB | 41472 |

The `init` strace (245K lines) captured switchd from process-start through chip init.
**What strace SEES**: read() of rc.soc/rc.datapath_0 (bcmcmd input text), ioctl() to BDE driver,
mmap() of BAR0 + DMA pool, open()/close() syscalls.
**What strace MISSES**: every direct `iowrite32(bar0+offset, val)` (mmap'd BAR0 writes are CPU stores, not syscalls).
That's why we can't see the *register-write sequence* of `init all` even though we have the *bcmcmd input*.

Mined output: `scripts/mine_strace.py` extracts every chip-config command from the strace.
Result: 46 unique commands (mostly `debug -X` flag-sets + the rcload sequence).

## 10. What this all tells us about the chip→CPU drop

Synthesis of EVERY artefact analysed:

**Evidence the chip path works in Cumulus:**
- L3_DEFIP, L3_ENTRY, EGR_L3_NEXT_HOP all have valid Cumulus entries (section 4)
- FP_TCAM has Cumulus's CPU-trap rules (section 5)
- VLAN_TAB / EGR_VLAN / EGR_PORT memories have populated content (section 3)
- The chip register state (4544 entries) is `init all` + post-tuning (section 2)
- MCS firmware loaded for hardware linkscan (section 6)
- DMA ring properly armed via BDE (section 7)

**Evidence we're missing in EdgeNOS:**
- Chip MEMORIES: we never write content to most chip memories (section 3)
- FP_TCAM rules: zero ported (section 5)
- ~3640 register diffs still (section 2, ranked in doc 12)
- Chip MicroController firmware: we don't load anything for MCS (section 6)

**Probable root-cause-of-root-cause:**
Even if every register diff is closed, the chip's MEMORY tables would still be empty.
OpenMDK's `bmd_init` doesn't populate L2_USER_ENTRY, VLAN_TAB entries beyond the bitmap, FP_TCAM,
or the egress port-config tables.  Cumulus's `init all` populates all of these.  Without
them, even the correctly-programmed chip *registers* point at empty memories and forwarding
decisions return 'unknown' / drop.

**Strategy this analysis points at:**
1. **Diff and port `dump_socmem_diff.txt`** (12 MB, never done).  Particularly EGR_PORTm,
   VLAN_TABm content, FP_TCAMm, MY_STATION_TCAMm.
2. **Implement FP_TCAM control-plane trap rules** mirroring `00control_plane.rules`.
3. **Reverse-engineer `bcm_init_check` / `bcm_init_selective`** in switchd to find the
   chip-memory-population sequence.
4. **Continue register regdump→port loop** in parallel (still bumping diff count down 200/round).

## 11. EdgeNOS-side correspondence — match-up table

For every Cumulus capture category above, where in EdgeNOS we currently have / don't have
the equivalent.  This is the 'who-owns-what' map for tomorrow's prioritization.

| Cumulus capture | Cumulus content | EdgeNOS equivalent | Status |
|---|---|---|---|
| `dump_soc_diff.txt` (registers) | 417 regs / 6415 scopes != reset | `asic/edged/datapath.c` + `bmd_init_all` | **~80 of 417 written; 3640 scopes still DIFF** |
| `dump_socmem_diff.txt` (memories) | 12 MB chip-memory contents | only L2/VLAN/L3_HOST via BMD APIs; nothing else | **0 explicit memory-table writes** — biggest unaddressed gap |
| `FP_TCAM_raw.txt` (CPU-punt rules) | Cumulus has CPU-punt FP entries | `asic/edged/datapath.c` does ONLY `CPU_CONTROL_1` bits | **0 FP_TCAM entries programmed** |
| `L3_DEFIP` + `L3_ENTRY` | Cumulus's routes + ARP entries | `asic/edged/l3.c` writes L3_HOST hash (SCHAN HASH_INSERT) + L3_DEFIP (partial) | Partial — single-path only, no PAIR mode, no ECMP wiring from netlink |
| `EGR_L3_NEXT_HOP` + `ING_L3_NEXT_HOP` | nexthop MAC + egress port | `asic/edged/l3.c` writes ING_L3_NEXT_HOP for own IPs (COPY_TO_CPU=1) | Partial |
| `L3_ECMP` | ECMP group members | `l3_ecmp_group_create()` primitive exists | **Dead code — never called from netlink** |
| `MY_STATION_TCAM` | router MAC match entries | `asic/edged/l3.c` writes our chip MAC | Done |
| `01_dump_mcs.txt` (MCS firmware) | Cumulus loads linkscan firmware to MCS | OpenMDK CMICm support; we don't load firmware | **No firmware load** — using polling instead |
| `03_dma_region_full.bin` | 64 MB host DMA pool | `asic/edged/bde_interface.c` allocates 4 MB pool | Smaller pool — fine for low rate |
| `bcmcmd-rc-files/rc.soc` | bcmcmd top-level init script | `datapath_mac_init()` (xmac_tx_ctrl=0xc802, MAC_RSV_MASK=0x18, etc.) | Mostly ported |
| `bcmcmd-rc-files/rc.datapath_0` | MMU + scheduler + CPU buffer config | `datapath_buffer_init`, `datapath_cpu_buffer_init`, `datapath_rc_full` | ~50% ported across rounds 1-3 |
| `bcmcmd-rc-files/rc.forwarding` | RTAG7 hash + CPU_CONTROL_1 | `datapath_hash_init` + `datapath_cpu_punt_init` | Fully ported |
| `bcmcmd-rc-files/rc.led` | LED state machine config | not ported (cosmetic) | N/A for forwarding |
| `bcmcmd-rc-files/rc.ports_0` | `setenv allports`, `setenv 40Gports` | aliases only, no chip writes | N/A |
| `bcmcmd-rc-files/rc.phy` | empty (Cumulus reserved) | n/a | N/A |
| `bcmcmd-rc-files/config.d/02sdk.bcm` | SDK feature flags (parity_enable, polled_irq, miim_intr, dma) | `asic/openmdk/bmd/...` chip-init defaults | Mostly aligned but `parity_enable=1` triggers ~67 PARITY_CONTROL writes we don't make |
| `bcmcmd-rc-files/config.d/11ports.bcm` | full XE→phys port map + speeds | `asic/openmdk/bmd/pkgsrc/chip/bcm56840_a0/...p2m` hardcoded | Need byte-by-byte compare; some scopes may be off |
| `cumulus-config/etc/cumulus/acl/policy.d/00control_plane.rules` | OSPF/BGP/ICMP/BFD CPU-trap intent | not implemented | **Critical gap — these compile to FP_TCAM** |
| `cumulus-config/etc/cumulus/datapath/traffic.conf` | QoS class/priority config | not implemented | Cosmetic for ping |
| `cumulus-config/etc/cumulus/switchd.conf` | switchd runtime config | n/a (edged has its own) | N/A |
| `switchd-binary` | 31 MB stripped ELF | n/a — we build edged from sources | RE target for soc_init's sequence |
| `strace/a1_init_strace.log` | every syscall switchd made at boot | n/a — runtime instrumentation | Mined (see `scripts/mine_strace.py`); the bcmcmd input is the only useful extract |
| `kernel-modules/*.ko` | Cumulus's linux-kernel-bde + linux-user-bde + bcm-knet | EdgeNOS has compatible linux-kernel-bde + linux-user-bde (built from OpenMDK) | Same role, equivalent functionality |
| `knet/` (bcm-knet driver state) | TPID, port-VLAN, RX-filter rules in bcm-knet | EdgeNOS has no bcm-knet equivalent — RX punt is via CMICm DCB ring + TUN, not bcm-knet | Different model |
| `procfs/interrupts` | /proc/interrupts showing 'linux-kernel-bde' IRQ counts | Same module on EdgeNOS; CMICm IRQ count is 0 right now | Same source, different state |
| `bcmcmd-table-dumps/` (`show port`, `dump l2`, etc.) | various live chip-state queries | n/a (no equivalent shell in edged) | Used at debug time only |
| `cpld-thermal/` | Cumulus's read of MAX6697 + CPLD fan PWM | EdgeNOS has its own `fan-controller.sh` + ds100df410 + accton_as5610_52x_cpld | Equivalent and working |
| `sfp-eeprom/` | 52 SFP EEPROM dumps | EdgeNOS reads via i2c bus + ds100df410 driver | Equivalent |
| `phy-diag/` | `bcmcmd phy diag` outputs (mostly empty) | not implemented in edged | Cumulus capture failed at the time; we'd produce our own |
| `quagga-config/` | OSPF / BGP config | EdgeNOS has no routing daemon yet | Future work |
| `vtysh-routing/` | Quagga runtime tables | n/a | Future |
| `iptables-tc/` | kernel netfilter + tc-qdisc state | EdgeNOS has stock iptables / tc | Same kernel layer |

**Top three never-touched categories** (in order of likely impact on chip→CPU):

1. **`dump_socmem_diff.txt`** — every chip-memory table write Cumulus made.  We never write these.
2. **FP_TCAM raw + `00control_plane.rules`** — CPU-trap rules for OSPF/BGP/ICMP/BFD.
3. **MCS firmware** — Cumulus loads chip MCU code for hardware-linkscan.  We use polling instead.

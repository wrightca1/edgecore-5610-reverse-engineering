# Cumulus 2.5.0 Live Baseline — run2 (2026-05-13)

Second comprehensive capture from a live AS5610-52X running Cumulus 2.5.0 with
OSPF up against a Nexus neighbor. ~1 GB of raw data captured, distilled into
the tarballs below plus a set of decoded-findings markdown docs.

## What's in each tarball

| Tarball | Size | Contents |
|---|---|---|
| `streamed_20260513_162341.tgz` | 7 MB | **The gold mine.** `DUMP SOC` (49,732 named chip registers w/ values), `DUMP SOCMEM` (1.47M chip memory cells w/ names), DIFF variants (only-deltas-from-reset = the live config). Plus 60-sec strace under load, FUSE walk of `/cumulus/switchd`, kernel modules (.ko), switchd binary, BAR1 host-DMA region, Cumulus config dirs (`/etc/cumulus/*`), vtysh state, PHY diag, lspci, /proc/* state. |
| `gcorev3_20260513_171317_no_core.tgz` | 14 MB | Tarball *without* the giant `sw.core` ELF (which is checked in compressed separately as `gcore/sw.core.gz` inside the unpacked tree). Plus SFP eeprom dumps (52), CPLD register state (max6697 thermal + pca9538 GPIO), all 10 switchd shared libs (libnl, libfuse, libc, libpthread, ...) for offline `gdb`. |
| `deep_mine_20260513_191506.tgz` (n/a — full dir) | 69 MB | `DUMP MCS` (chip MicroController internal RAM dump), CMC0/1/2 register dumps (CMC1+CMC2 confirmed all-zero — only CMC0 in use), full DMA region 64 MB host RAM (mostly poison), FP_TCAM/POLICY/COUNTER/METER raw dumps, all bcmcmd subcommand help, kernel debug, all `.bcm` init scripts (`config.bcm`, `rc.soc`, etc.). |
| `routes_20131001_121841.tgz` | 311 KB | First L3 route trace — chip tables before/after adding a test route. Identifies L3_DEFIP/L3_ECMP/EGR_L3_NEXT_HOP layout. |
| `single_20131001_123018.tgz` | 148 KB | ECMP→single-path collapse capture — `ip link set swp2 down` makes Cumulus rewrite L3_DEFIP entries that used `INTF 200000` (ECMP) to `INTF 100004` (single). |
| `dma_20131001_123802.tgz` | 137 KB | DMA-focused strace + register snapshots under ping load. Confirms switchd uses interrupt-driven via `ioctl(/dev/linux-user-bde, 0x20004c09=LUBDE_WAIT_FOR_INTERRUPT)`. |
| `final_gaps_20260513_202013/` (in tree, ~1 MB) | 1 MB | The final missing pieces: `/var/lib/cumulus/rc.datapath_0` (auto-generated chip init, 371 lines, 223 ops), `update-ports` Python source, `switchd.conf`, `00control_plane.rules` (OSPF/BGP/ICMP trap rules), `traffic.conf`, platform.conf. |
| `finish_20260513_203818/` (~143 MB) | 143 MB | Last round of mining: 245K-line switchd init strace, 70-point hash function probe, ECMP collapse+reform trace, kallsyms + System.map (kernel symbols for offline kernel-side disasm), iptables/tc/ss state, swp1/swp2 pcaps. Includes `a7_sw2.core.gz` — second 120 MB switchd gcore (compressed to 3 MB). |
| `cap_20131001_121651.tgz` | 196 KB | First bulk capture attempt (early in the session). Superseded by `streamed_*.tgz`. |
| `extra_20131001_121652.tgz` | 7.5 KB | Initial OSPF + thermal snapshot. |
| `all_20131001_134200.tgz` | 8.6 MB | Earlier all-in-one capture before streamed approach. Superseded. |
| `everything_20131001_132056.tgz`, `tac_20131001_132947.tgz`, `gcore_and_misc_20260513_171139.tgz` | various | Intermediate captures during exploration of capture strategy. |

## Compressed big files (>100 MB raw, gzip'd in-place to fit GitHub's 100MB-per-file limit)

| Path | Original | Compressed |
|---|---|---|
| `gcorev3_20260513_171317/gcore/sw.core.gz` | 123 MB ELF coredump | 13 MB |
| `finish_20260513_203818/a7_sw2.core.gz` | 120 MB ELF coredump | 3 MB |
| `streamed_20260513_162341/soc/dump_socmem.txt.gz` | 80 MB text | 5 MB |

Decompress to use:
```
gunzip path/to/sw.core.gz
gdb -ex 'set sysroot path/to/streamed_*/binaries' \
    -ex 'set solib-search-path path/to/gcorev3_*/switchd/libs' \
    path/to/streamed_*/binaries/switchd  path/to/sw.core
```

## Decoded findings (decoded.md/)

Markdown analysis of what we found, ready to read without unpacking anything:

- [`decoded.md/01_route_storage.md`](decoded.md/01_route_storage.md) — Cumulus's L3 chain: `L3_ENTRY` hash for ARP, `L3_DEFIP` for everything else, INTF `100xxx` single / `200xxx` ECMP, MAC in `EGR_L3_NEXT_HOP` not in DEFIP.
- [`decoded.md/02_dma_model.md`](decoded.md/02_dma_model.md) — Cumulus DMA: user-mode BDE (no KNET), BAR0 via `/dev/mem`, interrupt-driven (`LUBDE_WAIT_FOR_INTERRUPT` ioctl 9), 64-DCB ring, `DESC_HALT_ADDR` at 0x31120+4*chan.
- [`decoded.md/03a_chip_init_recipes.md`](decoded.md/03a_chip_init_recipes.md) + [`decoded.md/03b_chip_init_complete.md`](decoded.md/03b_chip_init_complete.md) — `rc.soc` + `config.bcm` + `rc.datapath_0`: every chip-tuning flag and the exact bcmcmd ops Cumulus runs at boot.
- [`decoded.md/04_l3_chip_format.md`](decoded.md/04_l3_chip_format.md) — L3_DEFIP PAIR mode (2 routes/TCAM slot), L3_ENTRY hash table is 16K (not 8K), KEY = IP<<3 encoding, 8 + 70 IP→slot hash data points captured.
- [`decoded.md/05_capture_inventory.md`](decoded.md/05_capture_inventory.md) — Index of every file in every tarball + what it answers.
- [`decoded.md/06_final_mine.md`](decoded.md/06_final_mine.md) — Last-mile finds: 245K-line init strace, 70-point hash probe, ECMP collapse/reform trace, kallsyms.
- [`decoded.md/07_schan_hash_insert_findings.md`](decoded.md/07_schan_hash_insert_findings.md) — How Cumulus inserts L3_ENTRY: SCHAN HASH_INSERT opcode 0x68000000 / TABLE_INSERT_CMD_MSG=0x24 (chip-side hash, not MEM_WRITE).
- [`decoded.md/08_bulk_capture_strategy.md`](decoded.md/08_bulk_capture_strategy.md) + [`decoded.md/09_capture_plan.md`](decoded.md/09_capture_plan.md) — Capture methodology and plan.

## How to use this baseline for EdgeNOS development

1. **For chip-table format questions**: grep the `streamed_*/soc/dump_soc_diff.txt` (only-non-default-regs, 6,415 entries) or `dump_socmem_diff.txt.gz`.
2. **For "how does Cumulus do X?"** questions: grep the strace logs (steady-state in `streamed_*/strace/`, init in `finish_*/a1_init_strace.log`).
3. **For chip-init code**: read `deep_mine_*/06_bcm_files/etc_bcm.d_rc.soc` + `final_gaps_*/var/lib/cumulus/rc.datapath_0`.
4. **For runtime switchd state** (DCB ring addresses, software shadow tables): `gdb` the gcore files.
5. **For decoding L3 routing**: `routes/*.txt` and `trace_hash_redo/*.txt` have before/after diffs.

## Reproducing the captures

The capture scripts are at:
- `../cumulus_baseline_2013/cumulus_bulk_capture.sh` — first bulk script
- `cumulus_dma_capture.sh`, `cumulus_deep_mine.sh`, `cumulus_finish_mine.sh`, `redo_trace_hash.sh`, `stream_cumulus_capture.sh`, `stream_fixup.sh`, `gcore_v3.sh` — focused captures

To re-run on a freshly-installed Cumulus 2.5.0:
```
# On workstation
sshpass -p CumulusLinux! scp <opts> stream_cumulus_capture.sh cumulus@SWITCH:/tmp/
./stream_cumulus_capture.sh  # runs the SSH orchestration locally; streams output back
```

## Switch state at capture time

Cumulus 2.5.0 (powerpc), AS5610-52X, OSPF up with Nexus neighbor on both swp1 (10.101.101.1/29) and swp2 (10.101.101.10/29).  43 routes in L3_DEFIP, 12 INTFs allocated (one per swpN), 2-member ECMP group at L3_ECMP[0..1].

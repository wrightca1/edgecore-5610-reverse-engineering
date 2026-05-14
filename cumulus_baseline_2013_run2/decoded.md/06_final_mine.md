---
name: project_cumulus_final_mine_2026_05_13
description: "Final round of capture from live Cumulus 2.5.0 — switchd init strace, 70-point hash probe, ECMP collapse trace, kernel symbols, iptables, 2nd gcore. 143MB at cumulus_baseline_2013_run2/finish_*"
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# Captures (all in `cumulus_baseline_2013_run2/finish_20260513_203818/`)

## A1: switchd init strace — **245,437 lines**
File: `a1_init_strace.log`

Race-attached strace ~10 sec after switchd spawn (488 attempts at 20ms = ~10 sec). Caught the latter half of init + steady-state. Sample shows:
```
ioctl(14, 0x20004c0a, ...)   # SEM_OP
read(17, "", 4096) = 0       # close of init config file
mmap(NULL, 1179648, ...)     # 1.1 MB DMA pool allocation
mmap(NULL, 1052672, ...)     # 1.0 MB more
```

The 1.1MB + 1.0MB anonymous private mmaps are likely the DCB ring + packet buffer allocations. Cross-ref with `/proc/PID/maps` to find their physical addrs.

## A2: hash function probe — **70 (IP, slot) data points** ← was 8
File: `a2_l3table_diff.txt`, `a2_L3_ENTRY_diff.txt`

Added a `10.99.99.0/24` secondary to swp1, then `ip neigh add` for IPs `.2 .. .250`. 70 ARPs propagated to L3_ENTRY. Each entry shows (IP → INTF id, sequential entry #). Raw diff shows physical chip slots.

With 70 points across the same /24 prefix, the chip's CRC polynomial is now derivable offline.

## A3: ECMP collapse + reform trace
Files: `a3_switchd_strace.log` (41,472 lines), `a3_defip_{before,after}.txt`, `a3_ecmp_*`

Scenario: `ip link set swp2 down` → wait 8s → `ip link set swp2 up` → wait 12s

Defip diff shows:
- **Before**: 20+ routes via `INTF 200000` (ECMP via swp1+swp2)
- **During swp2-down**: all ECMP routes rewritten to `INTF 100004` (single-NH via swp1 only)
- **After swp2-up**: ECMP routes restored

The strace captures the exact SCHAN ops switchd issues to do this rewrite — invaluable for understanding L3_DEFIP update operations.

## A4: iptables / tc / cl-acltool
Files: `a4_iptables*.txt`, `a4_tc_*.txt`, `a4_cl_acltool*.txt`
- iptables mangle: 14 rules (control-plane class/police)
- iptables nat: 11 rules
- iptables raw: 5 rules
- iptables filter: 38 rules total
- tc qdisc/class/filter for traffic shaping

These are the host-side rules Cumulus's `cl-acltool` compiles into chip FP TCAM. We have the SOURCE rules in `final_gaps_*/etc/cumulus/acl/` and now the COMPILED state too.

## A5: Kernel symbols
Files: `a5_kallsyms.txt` (23,568 symbols), `a5_System.map` (1.6 MB)

Now we can offline-disassemble `linux_user_bde.ko` / `linux_kernel_bde.ko` (in `streamed_*/modules/`) and map kernel-side function calls. Critical for understanding the BDE ioctl handlers (0x20004c08/9/A).

## A6: DMA region 4MB hex dump
File: `a6_dma_first_4mb.bin` (4 MB)

Read phys 0x02400000 + 4MB. **All `dead beef`** — this region of switchd's mmap is poison/preallocated. The live DCB ring must be at a different phys address. Next step: extract DCB ring address from gcore.

## A7: second switchd gcore — **120 MB**
File: `a7_sw2.core`

Second snapshot for delta vs the first (123MB) gcore. Delta between them shows what switchd's in-memory state changes between two points (~20 min apart, both under live OSPF).

## A8-A11: small but valuable
- **A8** `cl-acltool` variant outputs
- **A9** `bcmcmd "show X"` for 22 X values
- **A10** `netstat`, `ss` — every open socket + Unix sockets (we see zebra's `/var/run/quagga/zserv.api`)
- **A11** `tcpdump -i swp1/2 -c 100` (4 KB each — caught ARP + OSPF Hello frames)

# What's now ACTUALLY exhaustively captured

| Layer | Source | Coverage |
|---|---|---|
| Chip register state | DUMP SOC + DUMP SOC DIFF | 49,732 / 6,415 entries |
| Chip memory state | DUMP SOCMEM + DUMP SOCMEM DIFF | 1.47M / 228K entries |
| switchd init sequence | A1 (245K lines) | from ~10s post-spawn through ~30s |
| switchd steady-state | streamed/strace 60sec + fixup 60sec + finish A3 41K lines | ~3 minutes of syscalls |
| switchd binary | streamed_*/binaries/switchd | 31MB, unstripped likely |
| switchd memory | 2x gcore (123MB + 120MB) | delta-able |
| switchd dependencies | gcorev3_*/switchd/libs/ | all 10 shared libs |
| Kernel symbols | A5 (kallsyms + System.map) | for offline kernel disasm |
| L3 chain format | trace_hash_redo + ECMP from finish A3 | DEFIP PAIR, ECMP group, EGR_L3_NEXT_HOP all decoded |
| Hash function data | A2 70 data points | derivable offline |
| Init scripts | rc.soc, rc.datapath_0, config.bcm, update-ports | every line |
| Cumulus config | switchd.conf, traffic.conf, control_plane.rules | every file |
| Kernel modules | linux_user_bde.ko, linux_kernel_bde.ko, accton_cpld.ko, ds100df410.ko, etc. | binary .ko files |
| Live host state | iptables, tc, netstat, /proc/* | full |
| Wire capture | 100 frames on swp1+swp2 | pcap files |

# What's STILL not in our possession (and not getatable)

- **Broadcom BCM56846 register reference manual** (NDA, doesn't exist publicly)
- **Cumulus switchd source code** (closed, but we have 31MB binary + 2x 123MB core + libs — Ghidra path is open)
- **The lower 10 sec of switchd init** (race-attach was at attempt 489, missing the very first ioctls)
- **Live DCB ring contents** (the 4MB poison region didn't have them; need gcore-derived address)

# Status
We have everything practically extractable. Continuing to mine yields diminishing returns. Reflash-back-to-EdgeNOS is safe whenever you want.

Linked: [[project_cumulus_chip_init_recipes]], [[project_cumulus_chip_init_complete]], [[project_cumulus_dma_decoded]], [[project_cumulus_route_storage_decoded]], [[project_l3_chip_format_decoded]], [[project_cumulus_full_capture_2026_05_13]].

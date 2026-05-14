# First end-to-end EdgeNOS ↔ Nexus ping — 2026-05-14

After ~8 weeks of RE work mapping how Cumulus 2.5.0 programs the Broadcom
BCM56846 / Trident+ on an Edgecore AS5610-52X, applying the findings
distilled in this repo to EdgeNOS produced the first successful end-to-end
IPv4 ping to a Nexus neighbor.

```
EdgeNOS  10.101.101.1/29  ── swp1 ──>  Nexus  10.101.101.9
PING 10.101.101.9 (10.101.101.9): 56 data bytes
64 bytes from 10.101.101.9: seq=1 ttl=254 time=0.601 ms
64 bytes from 10.101.101.9: seq=2 ttl=254 time=1.416 ms

--- 10.101.101.9 ping statistics ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max = 0.601/0.929/1.416 ms
```

## Which findings from this repo made it pass

The changes are split between `asic/openmdk/bmd/` (BMD layer of the
chip SDK) and `asic/edged/` (the EdgeNOS switch daemon) in the
[`wrightca1/edgenos`](https://github.com/wrightca1/edgenos) repo.

| Change | Source finding in this repo | edgenos commit |
|---|---|---|
| **64-DCB contiguous RX DMA ring** with `RELOAD=1`, `DESC_HALT_ADDR` programmed past last DCB. Was the root cause of "ICMP echo replies never reach CPU". | [`cumulus_baseline_2013_run2/decoded.md/02_dma_model.md`](cumulus_baseline_2013_run2/decoded.md/02_dma_model.md) — Cumulus's strace shows the chip walks a continuous DCB ring; single-DCB polling never saw `DCB.DONE` flip. | [`b1af93c`](https://github.com/wrightca1/edgenos/commit/b1af93c) + [`c272a37`](https://github.com/wrightca1/edgenos/commit/c272a37) |
| **`CONTINUOUS_DMA=1` + `DROP_RX_PKT_ON_CHAIN_END=0`** in RX channel init. | Same — Cumulus's interrupt-driven user-mode BDE model decoded from live `ioctl(/dev/linux-user-bde, 0x20004c09=LUBDE_WAIT_FOR_INTERRUPT)` strace. | `c272a37` |
| **`rc.soc` chip-config flags** mirrored: `IFP_METER_PARITY=0` (Trident errata), `RDBGC0/3/4/5/6_SELECT`, `TDBGC6_SELECT`. | [`cumulus_baseline_2013_run2/decoded.md/03a_chip_init_recipes.md`](cumulus_baseline_2013_run2/decoded.md/03a_chip_init_recipes.md) + the raw `deep_mine_*/06_bcm_files/etc_bcm.d_rc.soc` capture. | `b1af93c` |
| **Expanded `CPU_CONTROL_1.TOCPU` traps**: UMC (OSPF Hello 224.0.0.5), IPMCPORTMISS, L3_SLOWPATH, L3_MTU_FAIL, L3UC_TTL_ERR, IPMC_TTL_ERR, V4L3ERR, V6L3ERR, MARTIAN_ADDR, UNRESOLVEDL3SRC. | [`cumulus_baseline_2013_run2/decoded.md/01_route_storage.md`](cumulus_baseline_2013_run2/decoded.md/01_route_storage.md) + the live `DUMP SOC` diffs in `streamed_*/soc/dump_soc_diff.txt`. | `b1af93c` |
| **`SCHAN HASH_INSERT` opcode `0x68000000`** (`TABLE_INSERT_CMD_MSG=0x24`) for L3_ENTRY — the chip-side hash insert, not raw `MEM_WRITE`. | [`cumulus_baseline_2013_run2/decoded.md/07_schan_hash_insert_findings.md`](cumulus_baseline_2013_run2/decoded.md/07_schan_hash_insert_findings.md) | (already deployed earlier session) |

`edged` sha256: `49ca6da40590391a0d8fd3c4236f1ed145b93c4d974a5a94ecaeeb44f63109e7`

## What's still NOT implemented but didn't matter for first ping

From `wrightca1/edgenos` `b1af93c` commit message:

- **netlink `RTA_MULTIPATH` → `l3_ecmp_group_create` glue** —
  primitive exists in `asic/edged/l3.c:720` but is currently dead
  code. ECMP routes from zebra/OSPF silently collapse to
  single-nexthop. Will need wiring; see
  [`cumulus_baseline_2013_run2/decoded.md/04_l3_chip_format.md`](cumulus_baseline_2013_run2/decoded.md/04_l3_chip_format.md)
  for the chip-side ECMP format we'll write into.
- **`rc.datapath_0` MMU buffer-pool mirror** (223 chip writes) —
  OpenMDK stock buffer defaults are enough for unicast ping but won't
  match Cumulus's tuned thresholds under load. Captured at
  `cumulus_baseline_2013_run2/final_gaps_*/var/lib/cumulus/rc.datapath_0`.
- **FP/ACL TCAM control-plane rules** — Cumulus's
  `00control_plane.rules` is ~100 FP entries for OSPF/BGP/ICMP/BFD
  trap + policing. `CPU_CONTROL_1.TOCPU` bits cover trap-to-CPU
  without per-protocol policing or class marking.
- **L3_DEFIP PAIR mode** (`MODE_MASK0/1=1`) — 2× TCAM density
  optimization. Single-route-per-slot still functions correctly.

## Install gotchas this session uncovered

- ONIE installer ran to completion (download → partition writes →
  partition table) but its final auto-`reboot` failed with
  `/bin/exec_installer: line 469: reboot: not found` on this ONIE
  build's busybox. The image install **did succeed** — manual
  power-cycle and the new EdgeNOS came up clean. Ignore the
  "Failure" message at the end of `onie-nos-install`.
- `./build.sh image` (the Dockerized build path) silently exits
  mid-stream and never updates the `.bin` — the container's
  `docker-build.sh` is stale (still references `asic/switchd/` from
  before the switchd → edged rename). Working fast path: run
  `bash scripts/build-rootfs.sh assemble` on the host, copy the
  platform `.ko`s into `staging/lib/modules/extra/`, `mksquashfs`,
  then concatenate `installer/install.sh` + `tar(uImage-powerpc.itb,
  rootfs.sqsh)` manually. Total `.bin` ~30 MB.

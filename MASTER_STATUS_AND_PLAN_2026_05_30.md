# Master Status & Action Plan — 2026-05-30

> ## ✅ 2026-06-02 — WORKING DATAPATH: ping to the Nexus, both directions.
> See [`TX_DATAPATH_PORTMAP_AND_INJECTION_2026_06_02.md`](TX_DATAPATH_PORTMAP_AND_INJECTION_2026_06_02.md)
> and [`DATAPATH_DEBUG_INSTRUMENTATION_2026_06_02.md`](DATAPATH_DEBUG_INSTRUMENTATION_2026_06_02.md).
> `ping 10.101.101.2 from swp1: 5/5, 0% loss, ttl=254`. The full chain that landed:
> 1. **Port-map** — `p2l()` → captured Cumulus map (swp2 was logical 58, now 2).
> 2. **ING_CONFIG_64** — dropped `ARP_RARP_TO_FP`/`APPLY_EGR_MASK` (need FP/masks we lack).
> 3. **TX egress** — **directed injection** (`pkt.port=physical_lane`, SOBMH) — confirmed
>    working: the Nexus's `Eth1/33 InUcastPkts` rose with our echo requests. (The earlier
>    "egress not confirmed" was swp47-with-no-traffic; real traffic egresses fine.)
> 4. **Per-port MAC→CPU** L2 punt entries (ARP-reply punt).
> 5. **RX→CPU DMA** — the big one: RX was on the CMICm/xgsd channel regs (`0x31xxx`,
>    writes never took); moved to the **XGS packed `CMIC_DMA` @0x100** the working TX uses.
> 6. **L3 local-host** — startup `RTM_GETADDR` dump so edged programs swpN IPs present at
>    boot → ICMP-reply punt.
>
> The headline blocker below ("frames never reach the CPU queue") is **resolved** — it was
> the RX DMA on the wrong register set, not the IFP/`soc_init` foundation. (The IFP/FP
> trap path is still un-init'd, so broadcast/multicast-to-CPU control traps remain TODO;
> unicast control traffic works via L2/L3 punt today.) Original analysis kept below for history.

Comprehensive reconciliation of the **actual code on disk** against the RE
findings and the (now-stale) session memory. Covers both the reverse-engineering
project (`edgecore-5610-reverse-engineering/`) and EdgeNOS (`newnos/asic/`).

> **Headline:** EdgeNOS is *much* further along than the 13-day-old memory
> implied. The DMA RX ring, L3 IPv4 forwarding, Cumulus chip-memory replication,
> STP state, and the PAXB sub-window mechanism are **all implemented and, against
> the decoded Broadcom reference, correct**. The remaining blocker is **upstream of
> the CMICm DMA engine**: the chip ingress pipeline is not enqueueing trapped
> frames to the CPU port queue, so DMA never has work to do. See §3.
>
> **CORRECTION (the key one): "comprehensively implemented" applies only to the
> TUNING layer, not the FOUNDATION layer.** Cumulus's chip gets two layers:
> (1) `bcmcmd init all` → `soc_init` — hundreds of foundational writes (IFP/field-
> processor init, full IPIPE/EPIPE pipeline staging, MMU internals) done *silently*
> by the full SDK, present in NO script; (2) `rc.soc` + `rc.datapath_0` post-init
> tuning deltas on top. **We captured and replicated only (2).** All that replicated
> tuning sits on **OpenMDK's `bmd_init` foundation, not `soc_init`.** See
> `project_init_all_insight_2026_05_14`.
>
> **Smoking gun:** the **IFP (field processor) is never initialized** on EdgeNOS —
> the only IFP write is `IFP_METER_PARITY_CONTROL=0` (errata). Yet
> `cumulus_replicate.c` writes ~100 FP_TCAM/FP_POLICY copy-to-CPU rules into that
> uninitialized processor. They can't fire → a dead CPU-punt path, very likely part
> of why frames never reach the CPU queue.
>
> **The foundation is already in the tree:** `OpenBCM/sdk-6.5.27/src/soc/esw/
> trident.c` is the full-SDK bcm56840 `soc_init` (IFP init, pipeline staging). The
> real next step is to **port that foundation, then keep `rc.*` tuning on top** —
> not more tuning, and not (only) per-stage drop-counter chasing.
>
> **Caveats / corrections (verified during this review):**
> 1. ~~The local tree lags edgenos.~~ **FALSE — `newnos/` IS a git repo; HEAD =
>    `67fbbed` = `origin/master` (May 18).** The tree is fully current; the May-17
>    file mtimes just mean those files weren't touched by the May-18 diagnostic
>    commit. This code review reflects the true current state.
> 2. The register-path hypothesis (CDK direct-write bypasses sub-window) was
>    **already tested on hardware May 18 and refuted** — see §3.
> 3. ~~MMU CPU-port buffers not ported.~~ **FALSE — they ARE implemented**
>    (`datapath.c:349 datapath_cpu_buffer_init`, plus `datapath_disable_vt` and
>    `datapath_rc_full`). The CPU-path `rc.datapath_0` recipe is ported.

---

## 1. What is DONE and verified-correct in code

| Subsystem | File | State |
|---|---|---|
| **PAXB sub-window AXI→BAR0 translation** | `asic/bde/linux-kernel-bde.c:166-259` | ✅ Full algorithm: 8×4KB windows, IMAP0_7 dynamic remap **via PCI config space** + read-back. Matches decoded Broadcom `shbde_iproc.c`. |
| **64-DCB RX ring** | `patches/openmdk/bcm56840_a0_bmd_rx.c` | ✅ Contiguous ring, `RELOAD=1` per DCB, `DESC_HALT_ADDR=base+64·sizeof` at `0x31120+4·chan`, `CONTINUOUS_DMA=1`. Completion via **per-DCB DONE bit** (correct — STAT.CHAIN_DONE is sticky on this chip). |
| **L3 IPv4 unicast forwarding** | `asic/edged/l3.c` | ✅ MY_STATION_TCAM, L3_ENTRY via **SCHAN TABLE_INSERT** (chip-side hash), ING/EGR_L3_NEXT_HOP, EGR_L3_INTF, COPY_TO_CPU for local host, CPU_CONTROL_1 trap bits. |
| **Cumulus chip-memory replication** | `asic/edged/cumulus_replicate.c` | ✅ EPC_LINK_BMAP, L2_USER_ENTRY (63 rows), EGR_VLAN/STG, FP_TCAM/POLICY (100 rows). Wired into `datapath_init()`. |
| **STP forwarding state** | `asic/edged/vlan.c`, `cumulus_replicate.c` | ✅ All ports FORWARDING in STG 1 (both ingress STG and EGR_VLAN_STG). |
| **TX path** | `patches/openmdk/xgsd_dma.c`, `packet_io.c` | ✅ Single-DCB TX, polls CHAIN_DONE. |

## 2. Known feature gaps (do NOT block basic ping)

- **L3_DEFIP subnet routes** — stubbed (`l3.c:314-321,334`). Only host routes work.
- **IPv6 host routes** — early-return (`l3.c:548`).
- **L3 host/route deletion** — stubbed (`l3.c:683`).
- **ECMP netlink glue** — `l3_ecmp_group_create()` exists but is dead code; RTA_MULTIPATH not wired.
- **L3_IPMC multicast** — absent.
- **MMU buffer-pool tuning** (`rc.datapath_0`, 223 writes) — stock OpenMDK defaults; fine for unicast, not tuned under load.
- **FP/ACL policing** — trap-to-CPU works via CPU_CONTROL_1; no per-protocol policing/marking.

## 3. The remaining blocker — ingress→CPU trap gating (NOT the DMA engine)

**A register-path hypothesis was investigated and REFUTED on hardware (May 18).**
For the record, because it's tempting to re-litigate: the CDK bulk path
(`dv.write32 = bde_write32` → `BDE_IOC_REG_WRITE` → `iproc_write` = direct BAR0,
no sub-window xlate) *is* architecturally split from the sub-window path
(`bde_iproc_write32` → `BDE_IOC_IPROC_WRITE` → `iproc_axi_write`). It looks
suspicious because `cumulus_replicate.c:330` writes the IRQ mask `0x31414` via the
sub-window path. **But** edgenos commit `67fbbed` set `CMIC_CMC0_PCIE_IRQ_MASK0`
via *both* paths and read back via both: **identical results (both 0), and
Cumulus's own post-init BAR0 dump shows the CMC0 region reads all-zeros at idle
too.** So `0` is the normal idle state; the direct path is not dropping CMICm
writes. **Do not chase this again** unless a both-paths readback *disagrees*.

**The actual blocker is upstream of CMICm.** Evidence (edgenos, May 18 chassis):
- `handle_asic_rx: enters=17M ok=0 last_rv_neg=9 (CDK_E_TIMEOUT)` — RX poll never
  sees a DONE DCB.
- **`linux-kernel-bde` IRQ count = 0** — the chip *never* raises an RX-complete
  interrupt. The DMA engine is idle because **nothing is ever punted to the CPU
  port queue**, not because the engine is broken.
- All replicate writes (EPC_LINK_BMAP, L2_USER_ENTRY, EGR_VLAN/STG, FP_TCAM/POLICY)
  AND L3 traps (CPU_CONTROL_1, COPY_TO_CPU nexthop) are verified by **chip-side
  readback** — yet frames still don't enqueue to CPU.

So the trap *configuration* lands correctly but the ingress pipeline still doesn't
deliver frames to the CPU COS queue that the armed RX channel drains.

### Candidate gates still to rule out (the real frontier)
- **CPU COS-queue → RX-channel mapping.** `xgsd_dma.c:243-247` enables 48 CPU COS
  queues on `XGSD_DMA_RX_CHAN` via `COS_CTRL_RX_0/1`. Verify the *trapped* frames
  land in a COS queue actually mapped to the armed channel (wrong channel = silent
  no-op). This is the highest-suspicion item.
- **CPU/CMIC port ingress + MMU enable** beyond EPC_LINK_BMAP (egress-only). Is the
  CPU port enabled on the *ingress*/MMU side, and are its input-buffer thresholds
  non-zero (else the MMU drops every CPU-bound frame)? Ties to the un-ported
  `rc.datapath_0` MMU buffer-pool config (§2).
- **Where the trap actually fires.** Confirm on-chip that an inbound frame for a
  swpN MAC/IP hits MY_STATION→L3→COPY_TO_CPU (or an FP/L2_USER trap) and gets a
  CPU-port destination — vs. being dropped at L2 bridging or MMU admission. A
  `bcmcmd`-style per-stage counter walk (or the Cumulus `streamed_*/soc` diff
  under load) is the way to localize the drop stage.

### Decisive next diagnostic — the `RIPC4` splitter
The single most informative counter is **`RIPC4` (SOC reg `0x0f100001`) = "RX IPv4
L3 unicast frames punted to CPU"** (verified in `STATS_COUNTER_FORMAT.md`). Ping
swp1's IP and read it:
- **RIPC4 increments** → the L3 pipeline IS punting to CPU; the drop is
  **downstream** (MMU admission / CPU cosq / DMA). Next: read CPU-port cosq used
  cells + the `RDBGC4=RDISC` counter.
- **RIPC4 stays 0** → the L3 pipeline never classifies the frame as punt-to-CPU;
  the drop is **upstream** (MY_STATION_TCAM miss / L3_ENTRY hash miss / wrong VID).
  Next: read `RDBGC3` (RIPD4/6 IP-header drop) and verify MY_STATION/L3_ENTRY hit.

Companion reason-counters (EdgeNOS already sets their SELECTs, `datapath.c:230`):
`RDBGC3`=RIPD4/6, `RDBGC4`=RDISC (discard: STP/VLAN-membership/MMU), `RDBGC5`=RFILDR
(FP filter), `RDBGC6`=RDROP (generic). `RDBGC1`=`0x0f10000c` is confirmed; the
others are sequential in the `0x0f1000xx` ipipe block — confirm exact offsets on
first read.

**Build caveat:** these ipipe counters are SOC registers read via **S-Channel**,
NOT direct BAR0 — the standalone `tools/diag/bde_dump_via_ioctl.c` (which reads
CMIC `0x31xxx` directly) cannot read them. OpenMDK's CDK has no `RIPC4r`/`RDBGCr`
macros either. So the diagnostic must be a **small SCHAN-register-read addition
inside `edged`** (it has the CDK/SCHAN path), logged at startup or on a signal —
~30 lines using `cdk_xgs_reg_read`/the SCHAN helper. This is the recommended next
code change: a read-only probe, not a fix.

## 4. The real gate: reconcile the tree, then verify on hardware

1. **Reconcile `newnos/` against `wrightca1/edgenos` `master`.** The local tree is
   dated May 17 and is not a git checkout; edgenos has ≥ `67fbbed` (May 18). Some
   of the May-18 diagnostics may not be in this snapshot at all.
2. Last verified "ping" (May 14) was a **false positive** (mgmt `end0`, not swp1).
3. **The single most important action: build the *current edgenos* tree, flash the
   chassis, send a frame at swp1, and walk the per-stage drop counters (§3).**
   Everything else is contingent on finding the drop stage.

## 5. Documentation updates needed (RE project)

These docs predate the decode and are now stale/incomplete:
- `SCHAN_AND_RING_BUFFERS.md` — CONTINUOUS_DMA "mentioned but not explained"; now fully decoded (see DCB reload + per-DCB DONE completion).
- `DMA_DCB_LAYOUT_FROM_KNET.md` — reload-bit semantics unclear; now: type-21 control word `count[15:0]/chain[16]/sg[17]/reload[18]`.
- `BDE_CMIC_REGISTERS.md` — add the register-path split (REG_WRITE direct vs IPROC_WRITE sub-window) and the CMC0-block direct-write caveat.
- `PAXB_SUBWINDOW_MECHANISM.md` — accurate; cross-reference that the kernel BDE uses **PCI config space** (not BAR0 MMIO) to write IMAP0_7 (`linux-kernel-bde.c:212`), an important detail.

## 5b. Strategy decision (2026-05-30): COMBO (B) — feasibility CONFIRMED

Decision: foundation from the full SDK (OpenBCM), control plane stays in edged.

**Feasibility verdict — B is viable as a *guided port*, not a full SDK compile:**
- ✅ `bcm56840_a0` is a **build-enabled device** in OpenBCM 6.5.27
  (`include/soc/defs.h:287` → `BCM_TRIDENT_SUPPORT`). Source is current, not
  bit-rotted.
- ✅ The foundation init is `_soc_trident_misc_init` (`src/soc/esw/trident.c:7046`)
  + sub-functions (`_port_mapping_init`, `num_cosq_init`, `pg_tdm_init`,
  `mmu_tdm_init`, `ser_init`, `clear_all_memory`) — one readable file, portable to
  edged's CDK writes function-by-function.
- ✅ The SDK uses the **same `linux_shbde.c` sub-window BDE** EdgeNOS reimplemented
  → register ops map directly.
- ⚠️ Full compile+link of the SDK soc layer (SAL/drv/schan/soc_cm, no obvious PPC
  user target) is heavy — **NOT the chosen realization.**

**The gap is narrower than feared.** OpenMDK `bmd_init` already does: `_port_map_init`,
MMU TDM + port-pri-groups, `CPU_PBMm`/`CPU_PBM_2m` (CPU=bit0), `EPC_LINK_BMAP` clear,
SerDes, DMA channel enable. So the port = **fill specific holes**, not reimplement
soc_init.

**#1 confirmed hole: IFP / field-processor init.** OpenMDK has *zero* field init
(only `IFP_METER_PARITY_CONTROL=0`). `cumulus_replicate.c`'s ~100 FP copy-to-CPU
rules write into an uninitialized processor. This is the highest-probability
CPU-punt blocker and the first port target.

**Method:** enumerate `_soc_trident_misc_init` sub-inits + the SDK's trident
field/L3 module init; diff each against OpenMDK `bmd_init`; port the missing ones
into edged (IFP first). OpenBCM `trident.c` is the authoritative source — no
guessing.

## 6. Prioritized action plan

1. **Reconcile `newnos/` ↔ edgenos `master`** (§4.1). Know which snapshot you're on
   before changing anything.
2. **Build + flash current edgenos tree**, send a frame at swp1.
3. **Walk per-stage chip drop counters** (§3 "decisive next diagnostic") to find the
   stage where CPU-bound frames stop. May-18 data points at *before* the CPU COS
   queue.
4. **Attack the located gate** — most-likely order: CPU COS-queue↔RX-channel mapping
   → CPU/CMIC port ingress+MMU enable → MMU buffer-pool thresholds (`rc.datapath_0`).
5. **Real swp1 ping** (not mgmt) — the true functional milestone.
6. If ping works → feature gaps (§2): ECMP glue → L3_DEFIP subnet routes → MMU
   tuning → FP policing → IPv6.
7. **Refresh stale RE docs** (§5) and the `xgsd_dma.c` "single-DCB" comment (the RX
   path is a 64-DCB ring in `bcm56840_a0_bmd_rx.c`; that comment is misleading).

**Do NOT** re-investigate the register-path/sub-window hypothesis (§3) — settled May 18.

---
*Generated from a full read of the on-disk code on 2026-05-30. Supersedes DMA-blocker
claims in session memory dated 2026-05-17 and earlier.*

# Datapath Debug Instrumentation — What / Why / How (2026-06-01..02)

This is a catalog of every diagnostic dump/probe added to `edged` while bringing
the BCM56846/Trident+ datapath up end-to-end (links → TX egress → RX→CPU punt →
ping). The instrumentation has since been **removed from the production build**;
this document preserves *what* each probe read, *why* it was added (the hypothesis
it tested), and *how* it was used / what it revealed — so the same questions can
be re-instrumented quickly next time.

All probes printed via `syslog(LOG_INFO,...)` (edged) or `CDK_PRINTF` (OpenMDK
SDK, routed to stdout→journald). Read paths used were the normal driver paths
(`READ_*` table macros over S-Channel, `CDK_XGSD_CMC_READ` for CMC registers,
`PHY_BUS_READ/WRITE` for MIIM) — **no raw `/dev/mem` register pokes** (see
`feedback_miim_safety`).

---

## How to read this
Each entry: **WHERE** (file/function) · **WHAT** (registers/tables read) ·
**WHY** (hypothesis) · **REVEALED** (the finding that moved the investigation).

---

### 1. Drop-localization probe (the workhorse)
- **WHERE:** `edged.c`, stat-poll loop (every ~30k iters). Helper reads in
  `bcm56840_a0_bmd_stat_get.c` (added `bmdStatRxIpDrop/Discard/FilterDrop/
  GenDrop/PuntToCpu` → `RDBGC3/4/5/6` + `RIPC4`).
- **WHAT:** per chip port {0(CPU),43,44,65,66}: `rx_pkts/rx_drops/rx_err/
  tx_pkts/tx_err`, and the RDBGC drop disaggregation
  `punt2cpu | discard ip filter gen (agg)`. Plus a `TX summary`
  (`g_tx_calls/ok/fail/lastrv`).
- **WHY:** localize *where* in the ingress pipeline frames die — STP/VLAN
  (`discard`), IP-header (`ip`), field-processor (`filter`), or generic
  "no forwarding destination" (`gen`/RDROP) — and whether anything punts.
- **REVEALED:** CPU-injected TX and RX both hit **`gen` (RDROP) only** = no
  valid forwarding destination, *not* a classified filter/STP drop. swp47
  `tx_pkts` stuck at 2; **CPU `rx_pkts`=0 across the whole run** (nothing ever
  punted). This single probe drove the entire TX and RX investigation.
- **NOTE:** RDBGCn are global counters re-`SELECT`ed per port; STP drops on
  Trident+ surface as **generic RDBGC6**, *not* a filter counter — so "gen" did
  not by itself rule STP out.

### 2. PVID classification dump
- **WHERE:** `edged.c` (`bmd_port_vlan_get`).
- **WHAT:** `PVID: chip port N -> VID M` for 65/66/67/43/44.
- **WHY:** confirm untagged Nexus frames on swpN classify into their service VID
  (3300+logical) whose member set includes the CPU.
- **REVEALED:** PVID correct (66→3302, 43→3347 …) — classification ruled out.

### 3. Raw `VLAN_TABm[vid]` bitmap dump
- **WHERE:** `edged.c` (`READ_VLAN_TABm` + `PORT_BITMAP_W0/W1/W2`, `BC_IDX`,
  `UMC_IDX`, `UUC_IDX`, `STG`, `VALID`, `VLAN_PROFILE_PTR`).
- **WHAT:** the live VLAN membership/flood bitmap for VID 3302 and 3347.
- **WHY:** port-numbering check — which *logical* bit is set for swpN.
- **REVEALED:** swp2 bit was at **logical 58** (`PB_W1=0x4000000`) vs Cumulus's
  **logical 2** (`PB_W0=0x5`). This is what exposed the **P2L port-map bug**;
  after the fix the bitmap matched Cumulus byte-for-byte. Also confirmed
  `BC_IDX=0` and `L2MC` empty (broadcast floods via PORT_BITMAP) == Cumulus.

### 4. Egress-eligibility dump (`EPC_LINK_BMAP` + `EGR_ENABLE`)
- **WHERE:** `edged.c` (`READ_EPC_LINK_BMAPm`, `READ_EGR_ENABLEm`).
- **WHAT:** `EPC_LINK_BMAP W0/W1/W2`; `EGR_ENABLE` for cpu(0)/swp47(43)/
  swp48(44)/swp1(65).
- **WHY:** is the CPU/target port egress-eligible (the flood masks by these).
- **REVEALED:** runtime `EPC_LINK = W0=0x7 W1=0x8000` (CPU+swp1/2+swp47 eligible),
  `EGR_ENABLE`=1. *Gotcha:* an early dump in `asic_init` showed `EPC=0` — a **red
  herring** because it ran *before* `datapath_init`/`cumulus_replicate`. *Gotcha:*
  `EGR_ENABLEm` is indexed by **physical** port (bmd_init uses `port`, not
  `lport`) — an early read at index 47 hit an unused port.

### 5. Raw ingress STP dump (`STG_TABm[1]`)
- **WHERE:** `edged.c` (`READ_STG_TABm` + `SP_TREE_PORTn`).
- **WHAT:** ingress spanning-tree state (3=forwarding) for CPU/swp1/swp2/swp47.
- **WHY:** a non-forwarding *source* port drops ingress frames, and that shows as
  generic RDROP — so STP was a prime suspect.
- **REVEALED:** all = **3 (forwarding)**. `bmd_port_stp_get` returns -1 for the
  CPU port (a GET bug), so the raw `STG_TAB` read was needed to clear STP.

### 6. L1 PCS LSM dump
- **WHERE:** `portmap.c` (`portmap_pcs_lsm_raw`, reads Warpcore CL49 LSM
  block 0x8360 reg 0x17 via AER lane-select + `PHY_BUS_READ`).
- **WHAT:** full CL49 Link-Status-Monitor word for swp47/swp48/swp1.
- **WHY:** localize why swp48 wouldn't link (signal vs block-lock vs hi-BER).
- **REVEALED:** swp47/swp1 = `0xc262` (block_lock=1, hi_ber=0). swp48 = `0x4462`
  (AM/signal bits set, **no block_lock**, bit10 block-sync-not-acquired) = RX-EQ
  not converging — per-Warpcore-lane, not the shared retimer.

### 7. CMICm RX-DMA channel-1 state dump  ← led to the RX root cause
- **WHERE:** `edged.c` (`CDK_XGSD_CMC_READ` at literal CMC offsets) +
  `bde_iproc_read32` for a direct-vs-sub-window comparison.
- **WHAT:** ch1 `DMA_CTRL`(0x31140), `DMA_STAT`(0x31150), `CURR_DESC`(0x311a8),
  `PKT_COUNT_CH1_RX`(0x31488), `DMA_DESC`(0x31158), `DESC_HALT`(0x31120).
- **WHY:** is the RX DMA channel actually armed and advancing, or erroring?
- **REVEALED:** `pktcnt` stuck at a **stale 224** (no per-frame increment);
  `ctrl/desc/halt/curr_desc`=0 even right after `rx_start` wrote them
  (`XGSD DMA start: desc_rb=0 ctrl=0`). The channel never armed. Combined with
  "SCHAN at 0x31000 works via direct" (same 4KB page), this **refuted the PAXB
  sub-window theory** and pinpointed the real cause: RX used the CMICm
  per-channel regs (0x31xxx, writes don't take) while working TX uses the **XGS
  packed `CMIC_DMA` @0x100**. Fix = move RX to the XGS DMA path.

### 8. RX-poll / DCB dump
- **WHERE:** `bcm56840_a0_bmd_rx.c` (`bmd_rx_poll`) + `packet_io.c`
  (`handle_asic_rx` counters).
- **WHAT:** `RX poll: cnt/ok/rd_idx`, raw DCB status word `dcb[N].v[15]`
  (DONE@bit31, BYTES[15:0]), and `handle_asic_rx: enters/ok/last_rv_neg`.
- **WHY:** is `bmd_rx_poll` ever seeing a completed DCB? is the chip writing our
  ring? endianness/address mismatch?
- **REVEALED:** `ok=0` across 600k+ polls, `last_rv_neg=9` (E_TIMEOUT), all
  `dcb[*].v[15]=0` (DONE never set) — confirmed nothing was delivered to our ring
  (because the channel was never armed — see #7). After the XGS-path fix:
  `RX poll(XGS): ok` climbed, ports 65/66 delivered → RX alive.

### 9. Netlink receive-type log
- **WHERE:** `netlink.c` (`netlink_poll`).
- **WHAT:** `NL: recv nlmsg_type=N len=L` per message.
- **WHY:** is edged processing kernel events at all? specifically `RTM_NEWADDR`?
- **REVEALED:** type **28 (RTM_NEWNEIGH)** seen, but **no type 20 (RTM_NEWADDR)** —
  the kernel only emits NEWADDR on a *change*, so swpN IPs present before edged
  starts were never programmed for L3 local-host CPU-punt. Fix = startup
  `RTM_GETADDR` dump in `netlink_init`.

### 10. OpenMDK XGS/XGSD DMA arm-time readback (pre-existing, kept minimal)
- **WHERE:** `patches/openmdk/xgsd_dma.c` (`bmd_xgsd_dma_chan_start` debug block).
- **WHAT:** `XGSD DMA start: chan dcb desc_rb ctrl stat`.
- **WHY/REVEALED:** showed `desc_rb=0 ctrl=0` right after arming → the smoking gun
  that CMICm channel-register writes weren't taking (see #7).

---

## The methodology that worked
1. **Disaggregate the drop** (probe #1) — never guess "it's dropped"; read *which*
   stage/counter increments.
2. **Read the live table, compare to the Cumulus capture** (probes #2–#5) — every
   forwarding table was verified == Cumulus before concluding "not the tables."
3. **Follow the counter that doesn't move** (probe #7: `pktcnt` stale; probe #8:
   `ok=0`) — a stuck counter localized the dead DMA channel.
4. **Refute your own theory cheaply** (SCHAN@0x31000 works ⇒ not a sub-window
   problem) before doing expensive work.
5. **Instrument the boundary you can't see** (probe #9: netlink types) — the
   missing `RTM_NEWADDR` was invisible until the type log was added.

See `TX_DATAPATH_PORTMAP_AND_INJECTION_2026_06_02.md` for the fixes these probes
led to, and `MASTER_STATUS_AND_PLAN_2026_05_30.md` for the running status.

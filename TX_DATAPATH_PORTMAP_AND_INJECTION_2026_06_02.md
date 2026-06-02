# EdgeNOS TX Datapath: Port-Map Bug + CPU-Injection RDROP — Findings (2026-06-01..02)

Chassis: AS5610-52X (BCM56846/Trident+), EdgeNOS dev unit at 10.1.1.212.
Goal: get CPU-injected frames to actually leave the chip and reach the wire.
This document records the full diagnostic chain and the two confirmed fixes
plus the breakthrough on the egress path. Companion memory:
`project_tx_datapath_isolated_2026_06_01`, `project_l1_blocker_swp1_*`.

---

## TL;DR

1. **Port-map bug (FIXED + VERIFIED).** OpenMDK's `bcm56840_a0_p2l()` fell back
   to a contiguous-by-physical-iteration logical map (swp2/phys66 → logical 58)
   instead of Cumulus's explicit map (phys66 → logical 2). Every per-port chip
   table was built on the wrong numbering and disagreed with `cumulus_replicate.c`.
2. **ING_CONFIG_64 over-set (FIXED).** We had set `ARP_RARP_TO_FP=3`,
   `ARP_VALIDATION_EN`, and `APPLY_EGR_MASK_ON_L2/L3` — all of which depend on
   the FP and egress masks being initialised (Cumulus has them, we don't).
   They diverted ARP to a dead FP and masked floods to empty.
3. **CPU-injection RDROP (root-caused to mechanism, not tables).** With every
   L2 table verified == Cumulus, switched-flood injection (`pkt.port=-1`, no
   module header) still RDROPs at CPU-port ingress.
4. **Egress still UNCONFIRMED (see §4 — corrected).** Directed injection
   (`pkt.port=physical_lane`, SOBMH) delivers to the chip cleanly (DMA ok, no
   timeout) but does **not** show confirmed per-frame egress (`swp47 tx_pkts`
   stuck at 2 through 40 injected frames), and the loopback RX half can't be
   validated because **swp48 is link-down**. So neither path reliably puts
   traffic on the wire yet.

---

## 1. The port-map bug

### Symptom
`VLAN_TAB[3302]` (swp2's service VID) had its swp2 member bit in the wrong
position: `PB_W0=0x1, PB_W1=0x4000000` = {CPU(logical 0), logical 58}, where
Cumulus has `PB_W0=0x5` = {CPU(0), logical 2}.

### Root cause
`bcm56840_a0_p2l()` (in `bcm56840_a0_bmd_attach.c`) only uses an explicit map
if `CDK_NUM_PORT_CONFIGS(unit) != 0`. EdgeNOS never populates `CDK_PORT_CONFIG`,
so P2L fell through to the default: iterate `xlport_pbmp` ascending, assign
logical 1,2,3… by physical order. That yields swp2(phys66) → logical 58.

Cumulus's authoritative `ING_PHYSICAL_TO_LOGICAL_PORT_NUMBER_MAPPING_TABLE`
(from `cumulus_baseline_2013_run2/streamed_*/soc/dump_socmem.txt.gz`):

```
phys 0      -> logical 0      (CPU)
phys 1-4    -> 0x7f           (unmapped)
phys 5-44   -> logical 9-48   (swp9-48)   [note lane swizzle phys17-24 below]
phys 45     -> logical 50     (swp50)
phys 49     -> logical 49     (swp49)
phys 57     -> logical 52     (swp52)
phys 61     -> logical 51     (swp51)
phys 65-72  -> logical 1-8    (swp1-8)
phys 73     -> logical 65     (LB_LPORT)
all other   -> 0x7f
Lane swizzle: phys17->22 phys18->21 phys19->24 phys20->23
              phys21->26 phys22->25 phys23->28 phys24->27
```
A contiguous fallback can never reproduce that swizzle.

### Fix
- `bcm56840_a0_bmd_attach.c`: replaced `bcm56840_a0_p2l()` body with a hardcoded
  74-entry table `bcm56840_a0_cumulus_p2l[]` (forward + inverse search).
- `bcm56840_a0_bmd_switching_init.c`: added `if (P2L(unit,port) < 0) continue;`
  in the `CDK_PBMP_ITER` loop. Without it, `_config_port()` →
  `bmd_vlan_port_add()` aborts on the now-`0x7f` unused lanes → `ASIC init
  failed` exit(1) **crash-loop** (hit 123 restarts before we caught it).
- `scripts/quick-rebuild-edged.sh`: `SRCS += bmd_attach bmd_switching_init`,
  added `-I .../phy/include`.

### Verification (on chassis)
`VLAN_TAB[3302]` flipped to `PB_W0=0x5` — byte-for-byte Cumulus. Init clean,
NRestarts=0. EdgeNOS's own `edged.ports[].logical_port` was already correct
(`i+1`); only BMD's P2L disagreed, so the fix also re-aligns `cumulus_replicate.c`.

---

## 2. ING_CONFIG_64 over-set

Cumulus value (from reg dump): `0x000401802080300e`. EdgeNOS reset default:
`0x0000000e`. We had been *adding* `ARP_RARP_TO_FP=3`, `ARP_VALIDATION_EN`,
`APPLY_EGR_MASK_ON_L2/L3`. Those bits are safe **only if** the FP (field
processor) and per-port `EGR_MASK` are initialised:

- `ARP_RARP_TO_FP`/`ARP_VALIDATION_EN` route ARP/RARP into the VFP for
  validation. Our IFP/VFP is **uninitialised** → ARP shunted to a dead FP and
  dropped instead of L2-flooded (this is why an swp47→swp48 **ARP** loopback
  RDROP'd specifically).
- `APPLY_EGR_MASK_ON_L2/L3` ANDs the flood with the source port's `EGR_MASK`,
  which edged never populates → flood masked to empty → generic RDROP.

Fix (`datapath.c`): keep only `L3SRC_HIT_ENABLE` + `L2DST_HIT_ENABLE`; leave the
FP/mask bits OFF until those subsystems are programmed.

---

## 3. CPU-injection RDROP — exhaustive diagnosis

CPU-injected frames (tagged with the service VID, `pkt.port=-1`) RDROP at
CPU-port ingress: `RDBGC6` "gen" counter rises ~1 per injected frame
(per-port, attributed to CPU port 0), and target ports show `tx_pkts=0`.

**Everything in the L2 flood path verified correct AND == Cumulus** (live reads
for VID 3347 / swp47):

| Check | Result |
|---|---|
| VLAN_TAB[3347] valid / STG / members | valid=1, STG=1, {CPU(0),swp47(47)}, BC_IDX=UMC=UUC=0 |
| EPC_LINK_BMAP (runtime, post link-poll) | W0=0x7 W1=0x8000 W2=0x2 → swp47 egress-eligible |
| EGR_ENABLE (physical-indexed!) | cpu=1, swp47[43]=1, swp48[44]=1, swp1[65]=1 |
| STG_TAB[1] ingress STP (raw) | CPU=3, swp1=3, swp2=3, swp47=3 — **all forwarding** |
| VLAN tag insertion | correct: offset 12, `8100`+VID, well-formed |
| L2MC table | **empty in BOTH** Cumulus & EdgeNOS → broadcast floods via PORT_BITMAP, identical |

Gotchas found along the way:
- The first flood dump showed `EPC_LINK_BMAP=0` — a **red herring**: it ran in
  `asic_init` *before* `datapath_init`/`cumulus_replicate`. Runtime value is fine.
- `EGR_ENABLEm` is indexed by **physical** port (bmd_init uses `port`, not
  `lport`) — an earlier read at index 47 hit an unused port.
- `bmd_port_stp_get` returns -1 for the CPU port (GET bug); the raw STG_TAB read
  shows CPU STP is actually 3 (forwarding).
- STP drops on Trident+ surface as the **generic RDBGC6** counter (not a filter
  counter) — so "generic RDROP" did *not* rule STP out by itself; the raw read did.

**Conclusion:** the RDROP is not in any forwarding table. It is in the
**CPU-injection mechanism** — how a headerless CPU frame is switched.

---

## 4. Directed injection — delivers to chip, egress NOT confirmed (corrected)

`bmd_tx` has two paths:
- `pkt.port < 0`: single DCB, **no module header**; relies on the chip to
  ingress-switch a headerless CPU frame → **RDROPs**.
- `pkt.port >= 0`: `HGf=1` + SOBMH module header (`sob[0]=0xff000000`,
  `sob[1]=0x00000100` unicast, `sob[2]=P2L(port)`), 2-DCB chained SG →
  intended directed egress.

Changed `handle_tun_tx`: `pkt.port = port->link_up ? port->physical_lane : -1`
(directed for link-up ports, raw/untagged; flood+tag fallback for down ports).

**First read looked positive** (`swp47 tx_pkts=2`, `bmd_tx_ok` climbing,
`lastrv=0` — no timeout, unlike the old broken-P2L hang). **But it does not
hold up:**

```
inject 40 frames out swp47  ->  swp47 tx_pkts STAYS at 2   (not per-frame egress)
swp48 rx_pkts = 0           ->  but swp48 (port 44) is LINK-DOWN this run
```

So `tx_pkts=2` was a one-time value, not proof of working egress, and the
loopback RX half is unobservable because **only swp47 (43) is up; swp48 (44)
never linked** (0 "link UP" events). Also many *empty* ports false-flap UP
(L1 SerDes noise — ports 9/13/27/35/39 flapping 30–58×), so they momentarily
get `link_up=1` and pull frames onto the directed path into the void.

**Honest state:** neither switched-flood (RDROP at ingress) nor directed (no
confirmed egress) reliably puts traffic on the wire. The OpenMDK SOBMH format
above is **unvalidated for Trident** and is a prime suspect; a deeper cause may
be that the egress pipeline (EDB/MMU) isn't fully initialised — the same
`soc_init` foundation gap tracked elsewhere.

What the directed path *did* establish: bmd_tx's `port>=0` SG path no longer
times out (the old hang was the broken P2L writing logical 58 into the SOBMH;
with the port-map fix it carries logical 47 and the DMA completes cleanly).

---

## 5. Next steps

1. Make directed injection the primary TX path for the Cumulus service-VID
   scheme (each swpN frame directed to its physical lane). Resolve egress
   tag/VID handling (swp47 currently egresses tagged VID3347; the loopback RX
   half on swp48 drops it because swp48's PVID is 3348 and it isn't a 3347
   member — need untagged egress or matching VID for the RX side).
2. Verify swp48 RX + CPU punt to close the loopback (CPU→chip→wire→chip→CPU).
3. Separately, understand *why* switched-flood injection is dropped (likely a
   Trident requirement that CPU-switched frames carry an inject directive) — or
   simply adopt directed injection and move on.
4. L1 SerDes blocker for swp1/swp2 (Nexus) remains independent (see
   `project_l1_blocker_swp1_*`).

## Files touched (newnos)
- `asic/openmdk/bmd/{PKG,pkgsrc}/chip/bcm56840_a0/bcm56840_a0_bmd_attach.c` — P2L Cumulus map
- `asic/openmdk/bmd/{PKG,pkgsrc}/chip/bcm56840_a0/bcm56840_a0_bmd_switching_init.c` — skip unmapped lanes
- `asic/edged/datapath.c` — ING_CONFIG_64 (drop FP/mask bits)
- `asic/edged/packet_io.c` — directed injection for link-up ports
- `asic/edged/edged.c` — diagnostic dumps (VLAN_TAB, EPC_LINK_BMAP, EGR_ENABLE, STG_TAB)
- `scripts/quick-rebuild-edged.sh` — SRCS + phy include path
Working binary `/usr/sbin/edged`; pre-port-map backup `/usr/sbin/edged.bak-preP2L`.

---

## 6. RX FIXED — bidirectional datapath working (2026-06-02, later)

Root cause of the dead RX→CPU path: **RX was on the wrong DMA register set.**
- TX uses `bmd_xgs_dma_*` → XGS *packed* `CMIC_DMA_CTRLr` @ **0x100** (low/mapped) — works.
- RX used `bmd_xgsd_dma_*` → CMICm *per-channel* `CMIC_CMC_DMA_CTRLr` @ **0x31xxx** — channel-1
  arm writes (DESC/CTRL) read back 0; the channel never armed (`pktcnt` stale at 224).
  (The PAXB-sub-window theory was refuted: SCHAN at 0x31000 works via direct, same page.)

**Fix:** rewrote `bcm56840_a0_bmd_rx.c` to the XGS single-DCB model (`bmd_xgs_dma_init` +
`bmd_xgs_dma_rx_start/rx_poll`, packed `CMIC_DMA` @0x100, self-re-arm deferred to the next
poll so the chip can't overwrite the buffer mid-read).

**Result on chassis:** `RX poll(XGS): port=65/66 ... (ok=8,9,10…16 climbing)` — Nexus frames
now punt to the CPU. `ping 10.101.101.2` from swp1: our ARP request egresses **and the Nexus
ARP reply is punted back**, `ip neigh: 10.101.101.2 REACHABLE`. **Bidirectional L2/ARP datapath
with the live Nexus works.**

Remaining: ICMP echo to the Nexus SVI still 0% (requests egress, ARP round-trips, but no echo
reply observed) — most likely Nexus control-plane policing of ICMP-to-SVI, since the reply would
use the same (working) unicast-to-swp1-MAC punt path. Next validation: L2 forwarding *through*
the switch, or check Nexus CoPP.

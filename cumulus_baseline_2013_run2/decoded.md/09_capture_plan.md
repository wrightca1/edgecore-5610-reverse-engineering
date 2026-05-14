---
name: project_cumulus_reflash_capture_plan
description: "Master plan for what to extract from Cumulus the NEXT time the AS5610-52X gets reflashed back to Cumulus. Goal: full coverage to make EdgeNOS forward packets end-to-end."
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

The switch is reflashed between EdgeNOS and Cumulus; a Cumulus session is a heavy commitment. This is the comprehensive list — capture **everything below** in one Cumulus boot so we don't have to reload again.

# Tier 0 — immediate blocker (CMICm RX DMA)

Our chip-side L3 forwarding works (HASH_INSERT verified, rx_drops=0), TX wire-side works, but the CMICm RX path never writes DCB.DONE → kernel never sees inbound packets. We need Cumulus's live register state for the RX DMA path while a ping is *actually working*.

**Live capture during sustained ping (run `ping <neighbor>` in another tty first):**

```bash
BC=/usr/lib/cumulus/bcmcmd

# CMICm RX channel control + status — for ALL 4 channels
for chan in 0 1 2 3; do
  $BC "getreg CMIC_CMC0_PKTDMA_DMA_CTRL.${chan}"          # ENABLE, DIRECTION, CONT_DMA, DROP_RX_PKT_ON_CHAIN_END, RELOAD policy
  $BC "getreg CMIC_CMC0_PKTDMA_DMA_DESC.${chan}"           # current DCB pointer (advances as ring is consumed)
  $BC "getreg CMIC_CMC0_PKTDMA_DMA_DESC_HALT.${chan}"      # ring halt address — *this is what we don't set*
done

# Status, common, COS queues
$BC "getreg CMIC_CMC0_PKTDMA_DMA_STAT"                     # CHAIN_DONE / DESC_DONE / DMA_ACTIVE per chan
$BC "getreg CMIC_CMC0_PKTDMA_DMA_STAT_CLR"                 # which clear bits Cumulus is using
$BC "getreg CMIC_CMC0_PKTDMA_COS_CTRL_RX_0"                # per-chan, queues 0-31 mask
$BC "getreg CMIC_CMC0_PKTDMA_COS_CTRL_RX_1"                # per-chan, queues 32-47
$BC "getreg CMIC_CMC0_PKTDMA_INTR_ENABLE"                  # which DMA events generate IRQs
$BC "getreg CMIC_CMC0_PKTDMA_INTR_STAT"
$BC "getreg CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.0"          # coalescing? per-chan
$BC "getreg CMIC_CMC0_PKTDMA_DESC_DONE_INTR_THRES.0"

# RX buffer / EP credit control
$BC "getreg CMIC_RXBUF_THRESHOLD"
$BC "getreg CMIC_RXBUF_EP_RLS_CRED"
$BC "getreg CMIC_RXBUF_CTRL"                               # if it exists
$BC "getreg CMIC_RXBUF_PKT_CRED_*"                         # any per-channel credit regs

# CPU port enable / forwarding
$BC "getreg EPC_LINK_BMAP"                                 # CPU port bit set?
$BC "getreg CMIC_CONFIG"                                   # SG_ENABLE, etc.
$BC "getreg CMIC_CMC0_CONFIG"                              # CMICm-specific config

# Dump a live DCB by reading memory at the DESC pointer (do AFTER above getregs)
# Capture LIVE_DESC=$(getreg CMIC_CMC0_PKTDMA_DMA_DESC.1 | parse)
# $BC "dump pcimem $LIVE_DESC 64"
```

**Trace one packet from wire to TUN with strace:**

```bash
# capture switchd's RX path syscalls
strace -e read,write,ioctl,mmap,pread64,pwrite64 -p $(pgrep -x switchd) -o /tmp/sw_rx.log -f -tt -s 2048 &
ping -c 5 -W 2 <neighbor>
sleep 2
kill %1
# After: look for the ioctl that surfaces a packet to userspace, and the read() from /dev/bcm-knet or BDE
```

**Pull the bcm-knet source** (open-source from Broadcom — not on the switch unless you build it). We need:
- `bcm-knet.c` and `bcm-knet.h` from OpenNSL/OpenSDK — describes the EXACT CMICm RX init sequence with DMA_HALT_ADDR usage, channel count, ring layout
- Already referenced in `edgecore-5610-reverse-engineering/DMA_DCB_LAYOUT_FROM_KNET.md` but only partial — pull the full source for the init function (probably `bkn_dma_init`)

---

# Tier 1 — route programming (zebra → ASIC)

We solved local-host L3 (HASH_INSERT into L3_ENTRY_IPV4_UNICAST). For real routing we need LPM/DEFIP and the path from zebra → switchd → ASIC. Per `SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md`, the path is **zebra → zserv.api unix socket → switchd → BCM SDK**, NOT netlink.

**Already in the RE corpus** (don't re-capture, just re-read):
- `SWITCHD_L3_ROUTE_PROGRAMMING_ANALYSIS.md` — L3_DEFIP write path, table ID 0x22d3
- `L3_TABLE_FILL_FROM_014a51e8.md`, `L3_NEXTHOP_FORMAT.md`, `L3_BUFFER_LAYOUT_FROM_DUMPS.md`
- `ECMP_GROUP_LAYOUT_FROM_01a1572c.md`
- `TABLE_MEMORY_MAP_FROM_OPENNSL.md`, `TABLE_NAME_MAPPING.md`
- `TABLE_ID_MAPPING_ANALYSIS.md`

**To capture on the live Cumulus** (set up OSPF or static routes first — config in the analysis doc above):

```bash
# Add a static route + dump chip state before/after
ip route add 10.99.99.0/24 via 10.101.101.9 dev swp2
$BC "l3 defip show" > /tmp/defip_after.txt
$BC "l3 l3table show" > /tmp/host_after.txt
$BC "l3 egress show" > /tmp/egress_after.txt
$BC "l3 ecmp show" > /tmp/ecmp_after.txt

# Diff to see what changed
$BC "dump table L3_DEFIP" | head -200          # raw chip dump
$BC "dump table L3_ENTRY_ONLY"                  # IPv6 + chained v4 hosts
$BC "dump table ING_L3_NEXT_HOP"
$BC "dump table EGR_L3_NEXT_HOP"
$BC "dump table EGR_L3_INTF"
$BC "dump table MY_STATION_TCAM"
$BC "dump table L2_USER_ENTRY"
$BC "dump table VLAN_PROFILE_TAB"
$BC "dump table LPORT_TAB"

# Trace one route add through switchd
strace -e write,ioctl -p $(pgrep -x switchd) -o /tmp/sw_route.log -f -tt -s 1024 &
ip route add 10.88.88.0/24 via 10.101.101.9
sleep 1
kill %1
# Look in the log for the BDE_DEV ioctl that programs L3_DEFIP
```

---

# Tier 2 — init / port-up completeness

We have most of port bringup (`PORT_BRINGUP_REGISTER_MAP.md`, `SERDES_WC_INIT.md`). Likely complete. Re-verify only if something breaks.

**Quick re-capture if needed:**

```bash
# Just rerun cumulus_baseline_2013/cumulus_dump.sh — it covers ports, PHY, link, etc.
bash cumulus_dump.sh > /tmp/cumulus_dump_$(date +%s).txt
bash cumulus_deep_dive.sh > /tmp/cumulus_deep_$(date +%s).txt
```

---

# Tier 3 — packet I/O details

**Already verified** (in `PACKET_IO_VERIFIED.md`, `PKTIO_BDE_DMA_INTERFACE.md`, `cumulus-packet-io-architecture.md`): TUN device flow, BDE mmap, packet buffer layout.

**Gap**: how the CPU side actually pulls packets off CMICm. The answer is in `bcm-knet.c` source (linux kernel module) — we need to mine that explicitly.

**To capture:**
- The exact sequence of `ioctl()`/`read()` calls switchd makes during RX (already partially captured in `traces/`, but specifically for the per-packet RX path)
- Whether interrupts are used or polling (`/proc/interrupts` while pinging)

```bash
# Watch interrupt counters during a ping burst
cat /proc/interrupts | grep -iE "cmic|bcm|knet" > /tmp/intr_before.txt
ping -c 100 -i 0.01 <neighbor>
cat /proc/interrupts | grep -iE "cmic|bcm|knet" > /tmp/intr_after.txt
diff /tmp/intr_before.txt /tmp/intr_after.txt
```

---

# Tier 4 — L2/VLAN/MAC programming (already done, low priority)

Already in:
- `L2_PAYLOAD_FROM_DUMPS.md`, `L2_WRITE_PATH_COMPLETE.md`, `L2_INDEX_SOURCE_FROM_DUMPS.md`
- `L2_TABLE_ACCESS_ANALYSIS.md`, `L2_SCHAN_MEMORY_WRITE_DECODE_STEPS.md`
- `VLAN_TABLE_FORMAT.md`

Only verify if our L2 add behavior diverges from observed Cumulus.

---

# Tier 5 — counters / statistics / link state (low priority, after ping works)

```bash
# After ping works, compare per-port stat layouts
$BC "show counters xe0"
$BC "show counters cpu0"
$BC "getreg COUNTER_INDIRECT_ACCESS"
```

Already covered in `STATS_COUNTER_FORMAT.md` — re-verify only if our stat polling produces nonsense.

---

# Tier 6 — things to research WITHOUT a Cumulus reload

These mine existing material; do them FIRST before asking for a reflash:

1. **bcm-knet kernel module source** — pull from a Cumulus rootfs image or the open OpenNSL release. Look for:
   - `bkn_dma_init`, `bkn_rx_dma_init`, `bkn_rx_setup_chan` (or similarly named)
   - How HALT_ADDR is set
   - How many RX channels are armed
   - DCB ring layout (single vs multiple DCBs)
2. **Cumulus rc.datapath and rc.forwarding** — already captured in `traces/cumulus_rc.datapath_0` and `bcm-config-format.md`. Re-read for CMICm-specific config knobs.
3. **OpenNSL release for BCM56846** — `OPENNSL_LIBRARY_EXTRACTION_RESULTS.md` says we extracted symbols. Look for `bcm_rx_*` and `_bcm_dma_rx_*` entries.

---

# Capture procedure for next reflash (one-page)

When reflashing to Cumulus next time:

1. Boot Cumulus, set IPs on swp1+swp2 to `10.101.101.5/29` and `10.101.101.10/29` (matches what EdgeNOS uses)
2. Verify Nexus neighbor `10.101.101.9` pings successfully
3. Run **`cumulus_deep_dive.sh`** → save as `/tmp/cumulus_dive_<date>.txt`
4. Run **the Tier-0 register dump block above** with ping running in another tty → save as `/tmp/cumulus_cmicm_rx_<date>.txt`
5. Run **strace on switchd** during 5 pings → save as `/tmp/cumulus_strace_rx_<date>.log`
6. Run **interrupt counter diff** → save
7. Add a static route, capture **Tier-1 chip table dumps** → save
8. `scp` everything off the switch BEFORE reflashing back to EdgeNOS
9. Push captures to `edgecore-5610-reverse-engineering/cumulus_baseline_<date>/` and commit

**Time estimate** for full Tier 0+1 capture: ~15 minutes once the switch is booted + neighbor pings work.

---

# Linked memory
[[project_rx_dma_cmicm_migration]] — current state of the migration; the immediate blocker.
[[project_schan_hash_insert]] — chip-side L3 forwarding (done).
[[project_switch_ip_reflash]] — one switch, reflash cost.
[[feedback_readonly_cumulus]] — never write registers on live Cumulus.
[[project_cumulus_baseline_2013]] — the previous capture set (incomplete for CMICm RX).

---
name: project_cumulus_route_storage_decoded
description: How Cumulus 2.5.0 stores routes in the BCM56846 ASIC — verified end-to-end 2026-05-13 with live captures (zebra+chip dumps before/after adding test routes)
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# The L3 chain in the BCM56846 chip

```
Packet in -> MY_STATION_TCAM (our router MAC?)
              |
              v
        L3_ENTRY hash (ARP cache, /32 host routes for REMOTE neighbors)
              |
              v
        L3_DEFIP TCAM (LPM: subnets, default, OUR OWN /32s for CPU-trap)
              |
              v
        INTF lookup in EGR_L3_NEXT_HOP (egress object table — keyed by 6-digit "INTF" id)
              |
              +- single nexthop -> dst MAC + L3_INTF_NUM + chip port
              |
              +- ECMP group (INTF id ~200000+) -> chip-hashes one of N member INTFs
                                                   |
                                                   v
              L3_INTF_NUM -> EGR_L3_INTF: src MAC + service VID (3300+N)
              |
              v
        Packet rewritten + egresses on chip port
```

# Worked example from a live Cumulus capture (2026-05-13)

State after `ip addr add 10.101.101.1/29 dev swp1` + `ip addr add 10.101.101.10/29 dev swp2` and OSPF up with Nexus (10.101.1.241) via both ports.

## `l3 intf show` — per-port src-MAC table (one entry per swpN)
```
Intf 1  VLAN=3301  src MAC=80:a2:35:81:ca:af  (swp1's MAC, service VID 3300+1)
Intf 2  VLAN=3302  src MAC=80:a2:35:81:ca:b0  (swp2's MAC, service VID 3300+2)
... [52 entries, one per front-panel port]
```

**This is the service-VID-per-swpN scheme**. Each swpN gets VID 3300+N (untagged front-panel member, tagged CPU). Our EdgeNOS implementation already mirrors this.

## `l3 egress show` — egress objects (next-hops, including ECMP placeholders)
```
Entry   MAC                  VLAN INTF  PORT  ...
100000  00:00:00:00:00:00     0   4095   31      <- drop entry
100002  00:00:00:00:00:00     0   4095    0      <- "TO_CPU" egress (PORT=0=CPU, MAC=0, INTF=4095=wildcard)
100003  6c:b2:ae:cd:13:33  3301    1     1      <- Nexus eth1/33 (paired w/ swp1)  INTF=1=swp1 L3 intf
100004  6c:b2:ae:cd:13:33  3302    2     2      <- Nexus eth1/34 (paired w/ swp2)  INTF=2=swp2 L3 intf
200000+                                          <- ECMP group ids (one per OSPF route with multiple paths)
```
- INTFs starting **`1000xx`** are single-nexthop egress objects.
- INTFs starting **`2000xx`** are ECMP group objects.
- INTF `100002` is reserved as a generic "trap to CPU" target; all our OWN /32 router IPs use it.

## `l3 l3table show` — L3_ENTRY hash table (ARP cache, REMOTE /32 only)
```
Entry  VRF  IP             MAC   INTF
1      0   10.1.1.1        00..   100002    <- mgmt gateway (kernel learned via eth0 ARP)
2      0   10.101.101.2    00..   100003 y  <- Nexus across swp1 (learned via swp1 ARP)
3      0   10.101.101.9    00..   100004 y  <- Nexus across swp2 (learned via swp2 ARP)
4      0   10.1.1.30       00..   100002    <- our workstation
```
**MAC is `00:00:00:00:00:00` in DEFIP/L3_ENTRY** — the actual dst MAC for L3-rewritten frames is in `EGR_L3_NEXT_HOP[INTF]`, not in the routing tables. Only the INTF pointer is here.

## `l3 defip show` — L3_DEFIP LPM TCAM (everything except remote ARP /32s)
Entries grouped by chip-internal slot, banded by prefix length:
- **/32 slots 2560-2566**: OUR OWN router /32s (10.101.101.10/32, 10.101.101.1/32) → INTF=100002 (TO_CPU). HIT=`y` on the two that are our actual local IPs.
- **/29 slots 2817-2821**: Connected /29s (10.101.101.0/29 swp1, 10.101.101.8/29 swp2) → INTF=100002. OSPF-learned remote /29s → INTF=200000 (ECMP).
- **/24 slots 3072-3079**: All OSPF /24 routes → INTF=200000 (ECMP).
- **/22 slot 3586**: 71.181.68.0/22 → INTF=200000.
- **/0 slot 4096**: 0.0.0.0/0 default → INTF=100002.

Test routes added & verified:
```
ip route add 10.99.99.0/24 via 10.101.101.9 dev swp2  -> DEFIP slot 3080, INTF=100004 (single-NH, via swp2)
ip route add 10.99.99.1/32 via 10.101.101.2 dev swp1  -> DEFIP slot 2567, INTF=100003 (single-NH, via swp1)
```
Delta: 41 → 43 routes. Surgical insert; no other entries touched.

# Implications for EdgeNOS

Today we use `L3_ENTRY_IPV4_UNICAST` hash for both ARP and our local /32s — that works but isn't the Cumulus pattern. The cleaner approach is:

1. **L3_ENTRY hash (HASH_INSERT)** for REMOTE neighbors (ARP cache). MAC=00 in the entry; nexthop comes from EGR_L3_NEXT_HOP[INTF].
2. **L3_DEFIP TCAM** for:
   - Our own router /32s (so they trap to CPU via "INTF 100002" pattern)
   - Connected /29s
   - All static + OSPF subnet routes
   - Default route
3. **EGR_L3_NEXT_HOP** holds the actual dst MAC + L3_INTF_NUM + chip port (the rewrite info).
4. **EGR_L3_INTF** holds per-port src MAC + service VID.

We already have steps 3+4 working (per `project_schan_hash_insert`). The next move for EdgeNOS is to also populate L3_DEFIP via the SCHAN HASH_INSERT-equivalent for TCAM (which is a different op — TCAM uses indexed writes, not hash).

# How `INTF 100002` (TO_CPU) actually traps to CPU

`100002` has PORT=0 (CMIC/CPU port), MAC=00 (no rewrite), INTF=4095 (wildcard L3 intf — no src MAC rewrite). Combined: a packet routed to this egress is essentially handed to the CMICm RX path unchanged.

This is **exactly what our `l3_local_host_add` programs in EdgeNOS**, except we put the entry in L3_ENTRY hash. Cumulus uses L3_DEFIP for this. Both should work given the chip checks L3_ENTRY first then L3_DEFIP; we just took the shorter-prefix path.

# ECMP details we still need

`bcmcmd "l3 ecmp show"` printed the usage banner (cli arg parsing failed). Need `bcmcmd "l3 multipath show"` or `bcmcmd "dump L3_ECMP"` to see ECMP group bodies. Will run next session.

# Files captured
- `/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/routes_20131001_121841.tgz`
- Subdirs: `1_kernel/` (Linux FIB), `2_zebra/` (RIB), `3_switchd_fuse/` (FUSE state), `4_asic/` (all bcmcmd dumps), `5_route_trace/` (before/after diff)

Linked: [[project_schan_hash_insert]] (chip-side L3_ENTRY HASH_INSERT — working), [[project_cumulus_bulk_capture_strategy]] (the capture approach), [[project_cumulus_reflash_capture_plan]] (curated checklist).

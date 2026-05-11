# Full Packet Flow Through the AS5610-52X — Layer 1 ↗ Application

Every stage a frame traverses in this switch under Cumulus 2.5.0,
captured live. Each section names the **exact** hardware block, register,
or daemon involved.

```
┌────────────────────────────────────────────────────────────────────────┐
│            Application (ping, BGP, OSPF, NMS, etc.)                    │
└────────────────────────────────────────────────────────────────────────┘
            ↕  socket()
┌────────────────────────────────────────────────────────────────────────┐
│            Linux Network Stack (TCP/UDP/IP/ARP/ND)                     │
└────────────────────────────────────────────────────────────────────────┘
            ↕  swpN (TUN device)
┌────────────────────────────────────────────────────────────────────────┐
│            switchd (userspace) — read/write TUN ↔ BDE                   │
└────────────────────────────────────────────────────────────────────────┘
            ↕  ioctl(/dev/linux-user-bde)
┌────────────────────────────────────────────────────────────────────────┐
│            linux-kernel-bde + linux-user-bde modules (BCM SDK)          │
└────────────────────────────────────────────────────────────────────────┘
            ↕  PCIe MMIO (BAR0 + PAXB sub-windows)
┌────────────────────────────────────────────────────────────────────────┐
│            CMIC (Chip Management Interface Controller)                  │
│            • 8 DMA channels  • 8 CoS RX queues  • SCHAN  • LED uController│
└────────────────────────────────────────────────────────────────────────┘
            ↕
┌────────────────────────────────────────────────────────────────────────┐
│            BCM56846 Trident+ Switching Core                             │
│  ┌──iPipe──┐   ┌─────MMU────┐   ┌──ePipe──┐                              │
│  │ parse   │ → │ 16MB pkt   │ → │ format  │                              │
│  │ L2/L3   │   │ buffer +   │   │ schedule│                              │
│  │ FP/ACL  │   │ 8 queues   │   │ encap   │                              │
│  │ MY_STN  │   │ per port   │   │ vlanmod │                              │
│  └─────────┘   └────────────┘   └─────────┘                              │
└────────────────────────────────────────────────────────────────────────┘
            ↕
┌────────────────────────────────────────────────────────────────────────┐
│            Warpcore SerDes (B0 variant)                                 │
│            • PCS Clause 49 (64B/66B) for 10G                            │
│            • PCS Clause 73 + KR4 FEC for 40G QSFP                       │
└────────────────────────────────────────────────────────────────────────┘
            ↕  10G XFI or 40G KR4
┌────────────────────────────────────────────────────────────────────────┐
│            DS100DF410 Retimer (32 chips, 4-lane each)                   │
│            • CDR  • Adaptive EQ  • Drive/preemphasis                    │
└────────────────────────────────────────────────────────────────────────┘
            ↕  electrical 10G
┌────────────────────────────────────────────────────────────────────────┐
│            SFP+ / QSFP+ cage                                            │
│            • TX laser  • RX photodiode  • DOM (SFF-8472 / SFF-8436)     │
└────────────────────────────────────────────────────────────────────────┘
            ↕  fiber / DAC
┌────────────────────────────────────────────────────────────────────────┐
│                        Peer (Nexus, etc.)                                │
└────────────────────────────────────────────────────────────────────────┘
```

---

## LAYER 1 — PHYSICAL

### 1.1 Optical module (SFP+ / QSFP+)

Live state for swp1 (Finisar FTLX1475D3BTL-E7 10GBASE-LR):

| Param | Value |
|---|---|
| Identifier | 0x03 (SFP) |
| Encoding | 0x06 (64B/66B) |
| BR Nominal | 10300 MBd (10.3 Gbps) |
| Length (SMF) | 10 km |
| Wavelength | 1310 nm |
| TX bias current | 13.136 mA |
| TX output power | 0.6068 mW / **−2.17 dBm** |
| RX signal power | 0.7913 mW / **−1.02 dBm** |
| Module temperature | 25.66°C |
| Module voltage | 3.3311 V |
| All alarm flags | Off (clean signal) |

The SFP+ DOM page (A2, bytes 96–105) contains live measurements polled
by `ethtool -m`. SFF-8472 standard layout.

#### A note on link-up vs. signal quality on swp1

The Nexus side (`show interface ethernet 1/33 transceiver details`)
reports our swp1 TX arriving at the Nexus RX as **−19.58 dBm**, which
trips the SFP+'s LOW-ALARM threshold (−16.57 dBm). Our swp1 TX leaves
the optic at −2.17 dBm, so the fiber/connector path is dropping **~17 dB**
— several times the 6 dB budget for 10GBASE-LR over SMF.

**The link is still UP** and `ping` works. Why:

* swp1 RX (our side) is healthy: −1.02 dBm from the Nexus TX (−1.70 dBm)
  → only 0.68 dB loss in *that* direction. So the chip's CDR locks,
  PCS gets `block_lock=1`, MAC sees valid frames, and Linux sees
  `carrier=1`.
* The 802.3 MAC layer makes no per-direction signal-quality decision
  beyond "did I get a valid frame with good FCS?" — it doesn't surface
  asymmetric power.
* The Nexus's LOW-ALARM is a *warning* on the receiving optic, not a
  link-down signal. The Nexus's PCS is also still locked, just barely.
* So the chip and OS both say "up" even though one direction is one
  dirty-fiber-event away from going dark.

This is a useful baseline observation: **link-up alone is not proof of
healthy optics**. Even when EdgeNOS reports a port linked, a full
diagnosis needs both sides' DOM (TX power local + RX power remote).
The Nexus 1/33 also shows **66 interface resets** vs only 28 on 1/34
— that's the symptom of marginal optical, not bad config.

### 1.2 DS100DF410 Retimer

Each linked SFP+ port goes through TWO retimers (one Rx, one Tx). For
swp1:
* RX retimer: `sfp_rx_eq_0` (retimer4)
* TX retimer: `sfp_tx_eq_0` (retimer16)

Both at I2C addr 0x27, accessed through the kernel `ds100df410` driver:

```
adapt_eq_sm     = 32     ← adaptive EQ state machine
cdr_rst         = 16     ← last value written (sequence is 28→16)
channels        = 165    ← per-chip channel mask
drv_sel_vod     = 128    ← output VOD
pfd_prbs_dfe    = 233    ← PFD/PRBS/DFE config
tap_dem         = 16     ← de-emphasis (QSFP retimers use 23)
veo_clk_cdr_cap = 1
```

### 1.3 Warpcore SerDes

xe0/swp1 lives at PHY MDIO addr `0xd1`, block 16, lane 0.

| Setting | Value |
|---|---|
| Preemphasis | `0xa370` (for 10G XFI) |
| DriverCurrent | `0x2` |
| PreDriverCurrent | `0x3` |
| Rx LOS (s/w enable) | 0 (use hardware LOS from SFP) |

The Warpcore runs a firmware image (PHY ucode) which handles:
* SerDes RX EQ adaptation
* Tx pre-emphasis tap weights
* PCS sync acquisition
* Idle/error block handling

PHY ID = `0x143` / `0xbff0` (Warpcore B0 revision). Loaded by switchd at boot;
config in `/etc/default/phy_ucode_update`.

### 1.4 PCS (Physical Coding Sublayer)

For 10G XFI (swp1-48): **IEEE 802.3 Clause 49 PCS** — 64B/66B encoding, scrambler/descrambler, block_lock detection.

For 40G KR4 (swp49-52): **IEEE 802.3 Clause 73** PCS with KR4 lane bundling. No FEC enabled in our config (no FEC for 40G-SR on this gen).

Block lock + hi_ber are exposed via CL45 reg 0x0020 at devad=3 (PCS):
* bit 0 = `pcs_block_lock` (must be 1 to receive)
* bit 1 = `hi_ber` (must be 0; goes 1 if too many errors)

When linked at 10G XFI: block_lock=1, hi_ber=0. Hardware PCS handles this; CPU only reads to display status.

### 1.5 MAC (line side)

Each port has a MAC sublayer in the BCM chip's MAC unit. Live for xe0:

| Field | Value |
|---|---|
| Speed | 10G |
| Duplex | Full |
| Interface | XFI |
| max_frame | 1518 bytes (Linux MTU=1500 + 14 hdr + 4 FCS) |
| auto-neg | OFF |
| STP state | Forward |
| Learn | F (no L2 learning — pure router config) |

---

## LAYER 2 — DATA LINK (in BCM iPipe)

### 2.1 Ingress port → VLAN assignment

Cumulus's default config gives **each port its own VLAN**:

| swp | xe | VLAN | Members |
|---|---|---|---|
| swp1 | xe0 | 3301 | cpu (tagged) + xe0 (untagged) |
| swp2 | xe1 | 3302 | cpu + xe1 |
| swpN | xe(N-1) | 3300+N | cpu + xeN-1 |

So an untagged frame on xe0 is automatically associated with VLAN 3301.
This makes each physical port behave like a routed L3 interface (router-on-a-stick distributed across ports).

VLAN 1 (default) exists but has no members.

### 2.2 MY_STATION_TCAM lookup

Every port's MAC is programmed in the MY_STATION_TCAM:

```
MY_STATION_TCAM[7]:  MAC=80:a2:35:81:ca:af (swp1), IPV4/IPV6/ARP_TERMINATE=1
MY_STATION_TCAM[8]:  MAC=80:a2:35:81:ca:b0 (swp2), IPV4/IPV6/ARP_TERMINATE=1
...
MY_STATION_TCAM[58]: MAC=80:a2:35:81:ca:eb (swp52), IPV4/IPV6/ARP_TERMINATE=1
```

When an incoming frame's dst_MAC matches an entry, the chip "terminates"
the L2 frame and hands it to the L3 pipeline (or directly to CPU for
ARP).

### 2.3 L2 MAC table (ARL — Address Resolution Logic)

`bcmcmd "l2 show"` — currently empty because no L2-switching traffic;
all the action is L3-routed.

When L2 switching is needed, the ARL table maps `<vlan, dst_mac>` → egress port. Source MAC learning happens automatically on ingress if STG state is Learn/Forward and `lrn` bit is set in port table.

### 2.4 STP (Spanning Tree) state

Cumulus uses MSTP (Multiple Spanning Tree Protocol). One STG (Spanning
Tree Group) covers all 53 VLANs (1, 3301–3352):

```
STG 0: contains 0 VLANs    (unused)
STG 1: contains 53 VLANs (1, 3301-3352)
  Disable: xe2-xe47       (no SFP / no link)
  Forward: xe0-xe1, xe48-xe51   (linked ports)
```

`mstpd` daemon runs in userspace and updates STP state per port. No BPDUs
flow in our setup because the Nexus side is configured as access ports.

### 2.5 Linux iptables/ebtables → BCM internal_priority

L2 dst-MAC classifiers via ebtables:

| MAC | Class (→ BCM internal_priority) |
|---|---|
| `01:80:c2:00:00:00` (BPDU)  | 7 |
| `01:80:c2:00:00:02` (LACP)  | 7 |
| `01:80:c2:00:00:0e` (LLDP)  | 6 |
| `01:00:0c:cc:cc:cc` (CDP)   | 6 |
| `01:00:0c:cc:cc:cd` (Cisco BPDU+) | 7 |
| ARP                          | 2 |
| (default catch-all)          | 0 |

These rules tag the Linux skb's `priority` field, which switchd then
copies into the BCM TX descriptor's internal_priority on egress, so the
ASIC schedules them to the right queue.

---

## LAYER 2.5 — INTERNAL PIPELINE (iPipe → MMU → ePipe)

This is BCM's internal fabric. None of it is visible at the network edge,
but it's where forwarding decisions actually happen.

### 3.1 iPipe (Ingress Pipeline) blocks

In order:

```
1. PARSER             - locate L2/L3/L4 headers, extract tuple
2. VLAN_TAB lookup    - get port's default VLAN + ingress tag mode
3. VLAN_XLATE         - optional VLAN-id translation (unused here)
4. MY_STATION_TCAM    - "is this frame for me?" → L3 path if yes
5. L2_ENTRY (ARL)     - if not for me, L2 dst lookup
6. L3_ENTRY (host)    - L3 dst lookup if MY_STATION hit
7. L3_DEFIP (route)   - LPM route lookup if no host entry
8. ECMP_GROUP         - if multipath, pick one nexthop
9. L3_EGRESS (nexthop)- look up dst MAC + egress VLAN + egress port
10. FP/ACL (TCAM)     - rules apply, may COPY_TO_CPU / drop / police
11. SRC_PORT_LEARNING - learn src_mac on this port (if enabled)
```

Each block can stamp an `internal_priority` on the frame which carries
through to egress queue selection.

### 3.2 Field Processor (FP) — TCAM ACL engine

The Trident+ FP has slices of TCAM that match arbitrary L1/L2/L3/L4
fields and apply actions:
* SETCLASS (set internal_priority)
* POLICE (rate-limit)
* COPY_TO_CPU
* REDIRECT
* DROP
* METER (apply policer)

Cumulus's default rules from `/etc/cumulus/acl/policy.d/00control_plane.rules` get compiled into BCM FP entries by `cl-acltool`. These implement the protocol-class table from §2.5.

### 3.3 MMU (Memory Management Unit) — packet buffering

The Trident+ has a 16 MB unified packet buffer. The MMU divides it into:
* Per-port input buffers (ingress)
* Per-port output queues (8 unicast + 4 multicast per port)
* CPU queues (8 CoS queues, all going to CMIC)

Live config for CPU queues (from `rc.datapath_0`):

| CPU CoS | q_min_cell | q_shared_limit_cell | Used for |
|---|---|---|---|
| 0 | 307 | 2073 | Default / data |
| 1 | 307 | 2073 | Low priority |
| 2 | 307 | **unlimited** | ICMP, ARP, DHCP, IPv6 ND |
| 3 | 307 | 2073 | Medium |
| 4 | 307 | 2073 | Medium |
| 5 | 307 | 2073 | Medium |
| 6 | 307 | 2073 | IGMP, OSPFv3, LLDP, CDP |
| 7 | 1 | unlimited | OSPF, BGP, CLAG, BPDU |

### 3.4 ePipe (Egress Pipeline) blocks

```
1. DESTINATION lookup - which port/queue, from iPipe decision
2. EGR_VLAN_XLATE     - egress VLAN translation
3. EGR_L3_INTF        - L3 egress interface table — rewrites src MAC
4. EGR_VLAN modify    - tag/untag based on port mode
5. EGR_TTL_DEC        - L3 TTL decrement (for routed packets)
6. EGR_MAC_REWRITE    - apply nexthop MAC from L3_EGRESS
7. EGR_FP/ACL         - egress FP rules
8. FCS recompute      - new CRC at end
9. Queue              - one of 8 per port, scheduled by WRR/DWRR
10. MAC transmit      - send to SerDes
```

### 3.5 Egress queue scheduling

Each physical port has 8 unicast queues. Weights (s2_cosweights):

```
queue 0: 16   queue 1: 0    queue 2: 32   queue 3: (default)
queue 4: 16   queue 5: 16   queue 6: 32   queue 7: 16
```

Some queues (1, 11) have weight 0 — they're strict-priority. Others use
DWRR with the given weights.

---

## LAYER 3 — NETWORK (BCM L3 + Linux IP stack)

### 3.6 BCM L3 interface table (L3_IIF)

One entry per port-VLAN-MAC combo:

```
Intf  VRF Group  VLAN    SrcMAC               MTU TTL
1     0     0    3301    80:a2:35:81:ca:af    1500 0
2     0     0    3302    80:a2:35:81:ca:b0    1500 0
...
```

When a frame arrives, the iPipe assigns an L3_IIF (based on the VLAN
from the port lookup), and this determines:
* Which VRF the routing happens in
* The source MAC to use on egress

### 3.7 BCM L3 host table (small/exact match)

Live entries:

```
1   10.1.1.1          → INTF 100002 (eth0/mgmt fallback)
2   10.101.101.2      → INTF 100003 (swp1 Nexus peer) HIT=y
3   10.101.101.9      → INTF 100004 (swp2 Nexus peer) HIT=y
4   10.1.1.30         → INTF 100002
+ fe80::be24:11ff:fe06:80c2 → INTF 100002 (IPv6)
```

The host table is checked first; on a hit, the chip already knows the
exact nexthop and bypasses the LPM table.

### 3.8 BCM L3 route table (DEFIP — LPM)

18 IPv4 routes live. Highlights:

```
prio  VRF  Net                     INTF        HIT
2562  0    10.49.49.1/32           100002       n
2563  0    10.101.101.10/32        100002       y  ← our swp2 IP
2565  0    10.101.101.1/32         100002       y  ← our swp1 IP
2691  0    10.49.49.0/30           100002       n  ← swp49 subnet
2817  0    10.101.101.8/29         100002       n  ← swp2 subnet
2817  0    10.101.101.0/29         100002       n  ← swp1 subnet
3072  0    10.1.1.0/24             100002       n  ← mgmt subnet
4096  0    0.0.0.0/0               100002       n  ← default route
```

LPM lookup picks longest prefix match. INTF 100002 is the "default L3
egress" (just sends to CMIC for CPU lookup).

### 3.9 BCM L3 egress (nexthop) table

```
Entry   MAC                  VLAN  INTF  Port  Drop  Refs
100000  00:00:00:00:00:00     0    4095  31    yes   0
100002  00:00:00:00:00:00     0    4095   0    no   30   (the "send to CPU" nexthop)
100003  6c:b2:ae:cd:13:33    3301   1     1    no    1   (swp1 Nexus peer)
100004  6c:b2:ae:cd:13:33    3302   2     2    no    1   (swp2 Nexus peer)
```

This is where ARP results are programmed. When the kernel learns an ARP
entry, switchd's RIB watcher updates this table. The chip rewrites the
dst MAC at egress using the Mac field from this entry.

### 3.10 cpu_control_1 register — CPU trap flags

```
modreg cpu_control_1 l3_mtu_fail_tocpu  = 1
modreg cpu_control_1 l3_slowpath_tocpu  = 1   (IP options → CPU)
modreg cpu_control_1 v4l3dstmiss_tocpu  = 1   (IPv4 route miss → CPU)
modreg cpu_control_1 v6l3dstmiss_tocpu  = 1   (IPv6 route miss → CPU)
```

### 3.11 Linux IP stack

Linux is fed by switchd via TUN devices. Live routing table:

```
default via 10.1.1.1 dev eth0
10.1.1.0/24 dev eth0  proto kernel  scope link  src 10.1.1.212
10.49.49.0/30 dev swp49  proto kernel  scope link  src 10.49.49.1
10.101.101.0/29 dev swp1  proto kernel  scope link  src 10.101.101.1
10.101.101.8/29 dev swp2  proto kernel  scope link  src 10.101.101.10
fe80::/64 dev {eth0,swp1,swp2,swp49,swp50}
```

ARP/NDP table:

```
10.101.101.2 dev swp1 lladdr 6c:b2:ae:cd:13:33 REACHABLE
10.101.101.9 dev swp2 lladdr 6c:b2:ae:cd:13:33 REACHABLE
10.1.1.1     dev eth0 lladdr 20:7c:14:f4:77:32 REACHABLE
```

---

## LAYER 4 — TRANSPORT (Linux kernel TCP/UDP)

From `netstat -s` live:

```
IP:    77,963 received  •  1 forwarded  •  65,238 delivered
ICMP:  598 in (594 echo-reply)  •  602 out (596 echo-req)
TCP:   872 active opens  •  13,792 segments rx  •  16,088 tx
UDP:   638 rx  •  647 tx
```

The ICMP counters confirm our ping tests: 596 echo-requests sent, 594
echo-replies received (close to matching → near-zero loss).

---

## CPU PATH — switchd ↔ BDE ↔ CMIC

### switchd file descriptors (live)

```
fd 14 → /dev/linux-user-bde   ← the SDK ↔ kernel BDE interface
fd 15 → /dev/mem              ← mmap PCI BAR0
fd 20–71 → /dev/net/tun       ← 52 TUN devices, one per swp*
12 socket fds                 ← netlink kernel events + IPC
2 pipe fds                    ← internal switchd plumbing
```

### switchd loop (from `strace`)

```
99.58%  select()    waiting on TUN/BDE/sockets
 0.42%  ioctl()     polling BDE for RX descriptors
```

### CMIC interrupt → kernel BDE

**IRQ 16: linux-kernel-bde = 7,775,427 interrupts** at the time of
capture. CMIC asserts this when:
* RX DMA descriptor done
* TX DMA descriptor done
* Link state change
* Any of dozens of internal events

The `linux-kernel-bde` driver decodes the interrupt source and either:
* For DMA: bumps a wait-queue that switchd is blocking on
* For SCHAN/MIIM: signals user-bde-waiting threads
* For LINKSCAN: handled internally; switchd polls every 250ms anyway

### Linkscan (port up/down detection)

```
LINKscan: enabled
  Software polling: 250000 usec (250 ms)
  Soft port bitmap: xe0..xe51 (all 52)
  Hardware port bitmap: none  ← Trident+ doesn't have HW linkscan for these ports
```

So link-up/down is detected by SOFTWARE polling every 250ms. switchd's
BCM SDK thread reads PHY status via MIIM/SCHAN, compares to last known
state, and emits a netlink message to userspace + writes
`/sys/class/net/swpN/carrier` if it changed.

---

## Concrete worked example: ping from swp1 to 10.101.101.2

**TX path (CPU → wire):**
```
Step  Where                           Action
1     ping(8) userspace               sendto(socket=ICMP, dst=10.101.101.2)
2     Linux IP stack                  Route lookup → swp1 (10.101.101.0/29)
3     Linux ARP                       Lookup → 6c:b2:ae:cd:13:33 (cached)
4     Linux IP                        Build ICMP echo-req with src MAC swp1
5     swp1 TUN driver                 Queue packet, mark TUN fd 20 readable
6     switchd select() wakes
7     switchd read(20)                Read 98 bytes (ICMP frame)
8     switchd                         Build TX DCB:
                                        dst_port = xe0
                                        vlan = 3301 (untagged egress)
                                        internal_priority = 2 (ICMP)
9     switchd ioctl(BDE,TX)           BDE writes DCB to CMIC DMA channel
10    CMIC DMA                        DMAs frame from host RAM to ingress
11    BCM ePipe (CPU as ingress port) Adds source MAC = swp1 MAC (from L3_IIF)
                                      VLAN tag 3301 stripped on xe0 egress
12    BCM MAC (xe0)                   Computes FCS, sends to Warpcore
13    Warpcore SerDes                 10G XFI, 64B/66B encode
14    DS100DF410 retimer (TX side)    Adapt EQ, drive electrical signal
15    SFP+ optic                      Laser fires at 1310 nm, 10.3 Gbps
16    Single-mode fiber               (1 to 10 km)
17    Nexus SFP+ optic                RX photodiode
                                      ...etc into Nexus ASIC
```

**RX path (wire → CPU):**
```
Step  Where                           Action
A1    Nexus sends ICMP echo-reply     dst MAC = swp1 MAC (80:a2:35:81:ca:af)
A2    SFP+ optic (RX)                 Photodiode receives 1310 nm
A3    DS100DF410 (RX side)            CDR locks, adapts EQ, presents to Warpcore
A4    Warpcore SerDes                 Decodes 64B/66B, sync words, presents to BCM MAC
A5    BCM MAC xe0                     Verifies FCS, strips preamble, hands to iPipe
A6    iPipe PARSER                    Extracts L2/L3 headers
A7    iPipe VLAN_TAB                  xe0 default VLAN = 3301; frame is untagged → use 3301
A8    iPipe MY_STATION_TCAM           dst_mac matches entry 7 → L2-terminate, go L3
A9    iPipe L3_ENTRY (host)           dst_ip 10.101.101.1 → host table hit
                                      INTF = 100002 (CPU egress placeholder)
A10   iPipe FP                        ICMP rule: SETCLASS class=2 → internal_priority=2
A11   iPipe                           COPY_TO_CPU action set
A12   MMU                             Enqueue frame to CPU CoS 2 queue (unlimited)
A13   ePipe (CPU port)                Adds CMIC RX DCB header (srcport=xe0)
A14   CMIC DMA                        DMAs frame from MMU buffer to host RAM RX ring
A15   CMIC                            Asserts IRQ 16 (linux-kernel-bde)
A16   linux-kernel-bde                Signals waiters
A17   switchd select() wakes on BDE fd
A18   switchd ioctl(BDE,RX)           Reads DCB: srcport=xe0, len=98, cos=2
A19   switchd                         Maps xe0 → TUN fd 20 (swp1)
A20   switchd write(20)               Write 98 bytes to TUN
A21   TUN driver                      Delivers as RX skb on swp1
A22   Linux IP stack                  Decodes ICMP echo-reply
A23   ping(8) socket                  Wakes recvfrom() in userspace
A24   ping(8)                         Prints "64 bytes from 10.101.101.2 ..."
```

Total latency from wire to userspace: ~0.7 ms (per the ping RTT we
measured).

---

## What I/O is happening EVERY 250 ms even at idle?

* `switchd` polling all 52 PHYs (linkscan) — that's at least 52 MIIM
  reads + state compares.
* `switchd` BDE polling (the `ioctl()` calls — 263/sec → every ~3.8 ms).
* `pwmd` polling 10 temp sensors every 30 s.
* `smond` polling sensors every 10 s.
* `monit` checking all daemons every cycle (configured per service).
* `i2c-mpc` IRQ at ~5400/sec = lots of retimer + EEPROM polls (mostly
  from switchd's PHY ucode loader and SFP DOM reads).

So even with no user traffic, the CPU is doing constant I/O at low
priority. EdgeNOS should replicate this ambient activity rate or it
will appear "broken" (no link detection, no fan control, no LEDs
updating).

---

## What's still unknown / unverified

1. **Per-stage drop counters** — we have RX/TX byte totals but not the
   drops at each stage (parser, FP, MMU). Need `bcmcmd "show counter
   c"` with the right pattern.
2. **The exact iPipe block disable register** — `IPIPE_BLOCK_DISABLE`
   returned syntax error. Worth finding the right name.
3. **Per-port PFC/PAUSE config** — `PAUSE_CTRL` syntax error. Probably
   in `PORT_CONFIG` somewhere.
4. **Mirror destinations** — none configured but if we add some we
   need to know the format.
5. **40G PCS** (Clause 73) for xe48–xe51 — we know it's KR4 but didn't
   probe the lane-skew / PCS Lane Mark Aligner state.

These can be filled in by extending `full_packet_flow.sh` with more
specific `getreg` / `g` invocations once we have the BCM register
naming convention dialled in.

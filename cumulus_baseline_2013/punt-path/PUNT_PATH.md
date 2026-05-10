# ASIC ↔ CPU Punt Path — How the BCM56846 Knows to Send Packets to the CPU

This is the end-to-end mechanism that makes `ping -I swp1 10.101.101.2`
work. EdgeNOS must reproduce all of this.

## The 3 things that have to be programmed

### 1. CPU MAC programming — `MY_STATION_TCAM`

Every `swp*` interface MAC is loaded into the ASIC's `MY_STATION_TCAM`.
There's one entry per port (52 entries — entries 7 through 58 or so).

Example entry for swp1 (MAC `80:a2:35:81:ca:af`):

```
MY_STATION_TCAM.ipipe0[7]:
   VALID                          = 1
   MAC_ADDR                       = 0x80a23581caaf       ← swp1 MAC
   MAC_ADDR_MASK                  = 0xffffffffffff       ← exact match
   VLAN_ID / VLAN_ID_MASK         = 0 / 0                ← any VLAN
   IPV4_TERMINATION_ALLOWED       = 1
   IPV6_TERMINATION_ALLOWED       = 1
   ARP_RARP_TERMINATION_ALLOWED   = 1
   FCOE_TERMINATION_ALLOWED       = 0
   MPLS_TERMINATION_ALLOWED       = 0
   TRILL_TERMINATION_ALLOWED      = 0
   ING_PORT_NUM / MASK            = 0 / 0                ← any ingress port
   COPY_TO_CPU                    = 0                    ← go via L3, not direct
   DISCARD                        = 0
   DATA                           = 0x38
   EVEN_PARITY                    = 0
```

When the L2 lookup runs on an incoming frame and the destination MAC
matches a `MY_STATION_TCAM` entry, the chip "terminates" the L2 frame —
i.e., it doesn't switch it; it hands it to the L3 pipeline (or directly
to CPU for ARP).

### 2. Global "copy to CPU" rules — `cpu_control_1` register

From `rc.datapath_0`:

```
modreg cpu_control_1 l3_mtu_fail_tocpu=1    # MTU exceeded → CPU (so we can send ICMP frag-needed)
modreg cpu_control_1 l3_slowpath_tocpu=1    # IP options → CPU (slow path)
modreg cpu_control_1 v4l3dstmiss_tocpu=1    # IPv4 route lookup miss → CPU
modreg cpu_control_1 v6l3dstmiss_tocpu=1    # IPv6 route lookup miss → CPU
```

Plus implicit/hardwired:
* ARP_RARP_TERMINATION → CPU (via MY_STATION above)
* TTL=0/1 → CPU (so we can send ICMP TTL-exceeded)
* L3 dst matches a host entry with `COPY_TO_CPU` flag → CPU
* Reserved L2 dest MACs (BPDU/LLDP/LACP/CDP) → CPU via FP/ACL rules

### 3. CoS queues + priority mapping (8 queues to CPU)

The CMIC has 8 RX queues (CoS 0–7). Each has size limits and a Linux
class-to-CoS mapping.

**Queue sizes** from `rc.datapath_0`:

| CoS | Min cells | Shared cells | Purpose |
|---|---|---|---|
| 0 | 307 | 2073 | Default / data |
| 1 | 307 | 2073 | Low priority |
| **2** | 307 | **unlimited** | ICMP, ARP, DHCP, IPv6 ND |
| 3 | 307 | 2073 | Medium |
| 4 | 307 | 2073 | Medium |
| 5 | 307 | 2073 | Medium |
| 6 | 307 | 2073 | IGMP, OSPFv3, LLDP, Cisco STP |
| **7** | n/a | **unlimited** | OSPF, BGP, CLAG, LACP, BPDU |

**Priority → CoS map** (`cpu_cos_map` entries 120–127):

```
modify cpu_cos_map 127 1 int_pri_key=0 int_pri_mask=0xf cos=0 valid=1   # → CoS 0
modify cpu_cos_map 126 1 int_pri_key=1 int_pri_mask=0xf cos=1 valid=1   # → CoS 1
modify cpu_cos_map 125 1 int_pri_key=2 int_pri_mask=0xf cos=2 valid=1   # → CoS 2 (unlim)
modify cpu_cos_map 124 1 int_pri_key=4 int_pri_mask=0xf cos=4 valid=1   # → CoS 4
modify cpu_cos_map 122 1 int_pri_key=5 int_pri_mask=0xf cos=5 valid=1   # → CoS 5
modify cpu_cos_map 121 1 int_pri_key=6 int_pri_mask=0xf cos=6 valid=1   # → CoS 6
modify cpu_cos_map 120 1 int_pri_key=7 int_pri_mask=0xf cos=7 valid=1   # → CoS 7 (unlim)
```

The chip's `internal_priority` is set by hardware based on:
* The trap reason (ARP → 2, ICMP → 2, OSPF → 7, BGP → 7, etc.)
* The ACL/FP rule match
* The Linux `SETCLASS` mark from iptables (for outbound packets we
  classify in software and that priority is honored by the ASIC on TX)

### 4. Linux iptables/ebtables `SETCLASS` for TX classification

Captured live (`acl-default-rules/00control_plane.rules`):

| Match | Linux class | BCM internal priority |
|---|---|---|
| L2: `1:80:c2:0:0:0` (BPDU)                | 7 | 7 |
| L2: `1:80:c2:0:0:2` (LACP)                | 7 | 7 |
| L2: `1:80:c2:0:0:e` (LLDP)                | 6 | 6 |
| L2: `1:0:c:cc:cc:cc` (Cisco STP)          | 6 | 6 |
| L2: `1:0:c:cc:cc:cd` (Cisco BPDU+)        | 7 | 7 |
| L3: ARP                                    | 2 | 2 |
| L3: OSPF (proto 89)                        | 7 | 7 |
| L3: BGP (tcp/179)                          | 7 | 7 |
| L3: CLAG (tcp/5342)                        | 7 | 7 |
| L3: ICMP                                   | 2 | 2 |
| L3: IGMP                                   | 6 | 6 |
| L3: DHCP (udp/tcp 67-68)                   | 2 | 2 |
| Default (catch-all)                        | 0 | 0 |

These are also enforced by `POLICE` rules to rate-limit the CPU (so a
runaway peer can't DoS us via control traffic).

## switchd's actual punt loop

switchd is the userspace daemon that bridges the kernel's swp* TUN
devices ↔ the BCM ASIC. From live introspection:

```
$ ls /proc/$(pgrep switchd)/fd | wc -l
75 total file descriptors

  fd 14 → /dev/linux-user-bde    ← the kernel BDE driver (BCM SDK access)
  fd 20–71 → /dev/net/tun  ×52   ← one per swp{1..52}, used for kernel↔switchd packet I/O
  fd 6,7,8,9,10,11,12,13,16,73,74,75 → sockets   ← netlink for kernel events + IPC
```

**Live strace summary** (idle, 5-second window):

```
% time      calls    syscall
99.58%         46    select          ← waiting on fds for activity
 0.42%       1315    ioctl           ← polling the BDE for any RX DMA descriptors
 0.00%          6    sendmsg         ← netlink updates (link state changes, etc.)
```

So the loop is:
1. `select()` on (52 TUN fds + BDE fd + sockets)
2. On TUN-fd ready: read packet, build BCM TX DCB, ioctl to BDE
3. On BDE-fd ready: ioctl BDE to read RX DCB, find which swp* the srcport
   maps to, write packet to that TUN fd
4. Back to select()

Even idle, the `ioctl` count is ~263/sec because switchd polls the BDE
periodically rather than relying purely on interrupts.

## End-to-end packet trace: `ping -I swp1 10.101.101.2` round-trip

### TX (CPU → wire)

```
Step  Where                  What
1     ping(8) in userspace   socket(AF_INET, SOCK_RAW, ICMP) bound to swp1
2     Linux kernel IP        Routes 10.101.101.2 via swp1 (directly attached /29)
3     Linux kernel ARP       Lookups 10.101.101.2 → finds 6c:b2:ae:cd:13:33
4     Linux kernel IP        Hands packet to swp1 TUN driver
5     TUN driver             Marks the TUN fd readable
6     switchd select() wakes
7     switchd read(fd_swp1)  Gets 98-byte ICMP frame
8     switchd                Builds BCM TX DCB: dst_port=xe0, internal_priority=2 (ICMP)
9     switchd ioctl(BDE,TX)  BDE writes DCB to CMIC DMA descriptor
10    CMIC DMA               DMAs frame from host RAM → ASIC ingress buffer
11    iPipe / ePipe          Frame egresses on xe0 with the swp1 source MAC
12    Warpcore SerDes        Encodes onto 10G XFI to the retimer
13    DS100DF410 retimer     Adapts EQ, drives the SFP+ optics
14    SFP+ module            Lasers fire, send 10GBASE-LR @ 1310nm to peer
```

### RX (wire → CPU)

```
Step  Where                  What
15    Nexus replies          Sends ICMP echo-reply, dst MAC = 80:a2:35:81:ca:af
16    SFP+ → retimer         Receives optical, retimer CDR locks, drives BCM SerDes
17    Warpcore SerDes        Decodes XFI, hands frame to iPipe on xe0
18    L2 lookup              dst_mac (80:a2:35:81:ca:af) → MY_STATION_TCAM[7] hit
                              → terminate L2, send to L3 pipeline
19    L3 lookup              IPv4 dst (10.101.101.1) → host route hit
                              → COPY_TO_CPU action set
20    Trap classification    Reason = "L3 dst matches MY_STATION + ICMP" → int_pri=2
21    cpu_cos_map[125]       int_pri=2 → CoS 2 queue (unlimited)
22    CPU queue              Frame queued on CoS 2 to CMIC
23    CMIC DMA               DMAs frame from queue into host RAM RX ring
24    BDE driver             Sees DMA descriptor done bit, marks BDE fd readable
25    switchd select() wakes
26    switchd ioctl(BDE,RX)  Reads RX DCB header (srcport=xe0, len, cos=2)
27    switchd                Maps xe0 → fd 20 (swp1 TUN)
28    switchd write(fd_swp1) Writes frame bytes to TUN fd
29    TUN driver             Delivers frame to swp1 netdev
30    Linux kernel IP        Receives ICMP echo-reply, hands to socket
31    ping(8) receives reply
```

## Why this works on EdgeNOS too

EdgeNOS already has:
* ✅ The CMICm DMA path (xgsd_dma — `project_dma_debug_progress`)
* ✅ The custom BDE for iProc/PAXB (`project_subwindow_fix`)
* ✅ Per-port TUN-like interface for swp*
* ✅ The L2/L3 init from OpenMDK

EdgeNOS still needs to program (or already does, verify):
* ❓ **MY_STATION_TCAM with the MAC of every swp interface.** This is the
  single most important thing — without these entries, the chip doesn't
  know which frames are "for me" and just switches/drops them.
* ❓ `cpu_control_1` flags (`l3_mtu_fail_tocpu`, `l3_slowpath_tocpu`,
  `v4l3dstmiss_tocpu`, `v6l3dstmiss_tocpu`).
* ❓ `cpu_cos_map` entries 120-127 mapping int_pri → CoS.
* ❓ CPU egress queue (`op_queue_config_cell[].cpu0`) sizing per CoS.

To verify what EdgeNOS has: dump `MY_STATION_TCAM` via the OpenMDK
`getreg`/`g` command after switchd-equivalent has started, and compare
to the captured output here. If the table is empty or missing entries,
the chip will silently drop "destined for me" frames.

## Captured artifacts

* `punt_path.sh` — the trace script
* `300_punt_trace.txt` — full live output (261 lines)
* `cumulus_baseline_2013/switchd-generated-state/rc.datapath_0` — the
  switchd-generated config that programs the CPU control registers
* `cumulus_baseline_2013/acl-default-rules/00control_plane.rules` —
  the SETCLASS rules that classify control traffic to the right CoS

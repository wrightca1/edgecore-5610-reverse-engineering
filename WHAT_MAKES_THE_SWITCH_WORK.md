# What Makes the Switch Push Packets and Route

**Purpose**: Single checklist of everything required for the AS5610-52X (BCM56846) to forward L2/L3 and behave like a working switch/router.  
**Audience**: Custom NOS implementation.

---

## 1. High-Level Picture

| Layer | What it does | Where it runs |
|-------|----------------|----------------|
| **Data plane** | L2/L3 forwarding at line rate | ASIC hardware only |
| **Control plane** | Programs FIB, L2 table, ports from kernel state | switchd + SDK |
| **Kernel** | Routing table, ARP/NDP, interfaces (swp), punt/inject | Linux |
| **Packet I/O** | CPU ↔ port (control traffic, host-bound) | switchd: TUN fd ↔ SDK/BDE |

**Key point**: Once the ASIC is initialized and tables are programmed, **data plane packets never touch the CPU**. Making “everything work” means: (1) ASIC and ports come up, (2) kernel state (routes, neighbors, link) is reflected into the ASIC, and (3) host/control traffic can be sent and received via the same swp interfaces.

---

## 2. What You Need (Checklist)

### 2.1 Boot and Drivers

| Item | Purpose |
|------|--------|
| **ONIE / bootloader** | Load your OS (or keep Cumulus/ONL). |
| **Kernel** | 3.2.x (Cumulus) or your choice; must support BDE. |
| **linux-kernel-bde.ko** | PCI, BAR mapping, DMA, S-Channel. |
| **linux-user-bde.ko** | User-space device `/dev/linux-user-bde` for switchd. |
| **No KNET** | Cumulus does not use `linux-bcm-knet.ko`. swp are TUN devices created by switchd. |

See: [ONIE_BOOT_AND_PARTITION_LAYOUT.md](ONIE_BOOT_AND_PARTITION_LAYOUT.md), [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md).

### 2.2 Platform and Port Config

| Item | Purpose |
|------|--------|
| **ports.conf (or equivalent)** | Per-port mode: 10G/40G for QSFP, 40G vs 4×10G for ports 49–52. |
| **update-ports (or equivalent)** | Generates 11ports.bcm (portmap, pbmp, port_init_speed), rc.ports_0, porttab, sfptab. |
| **Port mapping** | swpN ↔ xeM (BCM port). porttab format: `linux_intf sdk_intf unit is_fabric`. |
| **SerDes / portmap** | One logical BCM port per 10G lane; 40G = one port over 4 lanes. |

Without this, port numbering and link bring-up are wrong. See: [QSFP_BREAKOUT_CONFIGURATION.md](QSFP_BREAKOUT_CONFIGURATION.md), [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md).

### 2.3 ASIC Initialization (switchd or equivalent)

| Step | What happens |
|------|----------------|
| Open BDE | `open("/dev/linux-user-bde")`. |
| Attach/init | `bcm_attach(0, BCM56846)`, `bcm_init(0)` using merged .bcm config. |
| rc.soc | Run SOC script: `init all`, `rcload rc.ports_0`, `rcload rc.led`, setreg for stats, `rcload rc.datapath_0`. |
| rc.ports_0 | Defines allports, 10Gports, 40Gports (e.g. xe0–xe51). |
| rc.datapath_0 | Buffer pools, priority groups, pipeline (generated from datapath.conf + hw_desc). |
| rc.forwarding | ECMP hash (RTAG7), CPU punt (l3_mtu_fail_tocpu, l3_slowpath_tocpu, v4l3dstmiss_tocpu, etc.). |

See: [initialization-sequence.md](initialization-sequence.md), [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md).

### 2.4 Interfaces (swp) and Packet I/O

| Item | Purpose |
|------|--------|
| **Create swp before/with switchd** | One TUN per port: open `/dev/net/tun`, ioctl TUNSETIFF with name swp1..swp52 (and swp49s0–3 if breakout). |
| **porttab** | switchd reads porttab to map swpX → xeN. |
| **TX (CPU → port)** | Kernel sends to swp → writes to TUN → switchd read(TUN fd) → SDK packet TX → BDE → ASIC. |
| **RX (port → CPU)** | ASIC punts (e.g. host route, TTL=1) → BDE → switchd → write(TUN fd) → kernel → app. |

Without TUN creation and porttab, control plane and host traffic cannot use swp. See: [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md), [COMPLETE_INTERFACE_ANALYSIS.md](COMPLETE_INTERFACE_ANALYSIS.md).

### 2.5 Syncing Kernel State to the ASIC

| Kernel event | Netlink | SDK calls (concept) |
|--------------|--------|---------------------|
| `ip link set swpN up/down` | RTM_NEWLINK (IFF_UP) | bcm_port_enable_set(unit, port, 1/0) |
| `ip route add/ del` | RTM_NEWROUTE / RTM_DELROUTE | bcm_l3_egress_create, bcm_l3_route_add / bcm_l3_route_delete |
| ARP/NDP learn | RTM_NEWNEIGH | bcm_l2_addr_add |
| Neighbor expire | RTM_DELNEIGH | bcm_l2_addr_delete |

switchd (or your daemon) must:

- Subscribe to netlink (RTMGRP_LINK, RTMGRP_IPV4_ROUTE, RTMGRP_NEIGH, etc.).
- Map interface index → BCM port via porttab.
- For routes: resolve next-hop MAC (from neighbor table), create L3 egress, then add L3 route/host entry.

See: [netlink-message-flow.md](netlink-message-flow.md), [netlink-handlers.md](netlink-handlers.md), [api-patterns.md](api-patterns.md).

### 2.6 L2 Forwarding

- **VLANs**: bcm_vlan_create, bcm_vlan_port_add so ports belong to the right VLANs.
- **MAC learning**: Typically from RTM_NEWNEIGH / RTM_DELNEIGH (and optionally learning from data plane if your stack supports it).
- **Broadcast/unknown unicast**: Default VLAN and forwarding behavior from rc.forwarding / datapath; L2 lookup miss can go to CPU or flood depending on config.

### 2.7 L3 Routing

- **FIB**: Populated from kernel routes via bcm_l3_route_add / bcm_l3_host_add, with egress from bcm_l3_egress_create (port + next-hop MAC).
- **ECMP**: bcm_l3_ecmp_* and rc.forwarding RTAG7 hash so multipath works in hardware.
- **Punt**: l3_slowpath_tocpu, v4l3dstmiss_tocpu, etc., so misses and exceptions go to CPU; switchd then injects via TUN so kernel can handle (e.g. ARP, routing daemon).

### 2.8 Config Files the SDK Expects

- **Merged .bcm** (e.g. config.bcm): chip + platform params, portmap, pbmp, port_init_speed, port_init_autoneg.
- **rc.soc**: One-time SOC/port/datapath/led script.
- **rc.ports_0**: allports, 10Gports, 40Gports.
- **rc.datapath_0**: Generated from datapath.conf + hw_desc (buffer/pipeline).
- **rc.forwarding**: ECMP hash, CPU punt flags.

See: [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md), [bcm-config-format.md](bcm-config-format.md).

---

## 3. End-to-End: What “Push Packets and Route” Means

1. **Ports up**: Port config and portmap correct → SerDes/PHY init → `bcm_port_enable_set(1)` when link is up (or admin up). Physical link and LEDs reflect state.
2. **L2**: VLANs and L2 table (MAC → port) programmed so that within-VLAN traffic forwards in hardware.
3. **L3**: Kernel has routes and neighbors; switchd pushes them into the ASIC (L3 egress + route/host entries) so that L3 traffic is forwarded in hardware and TTL/checksum are updated.
4. **Control/host traffic**: Packets to/from the switch’s own IPs go to CPU (punt). switchd receives them via BDE and injects to the right TUN (swp) so the kernel and apps (SSH, ospfd, etc.) see them.

So “everything work as intended” = correct init + port config + netlink-driven table programming + TUN-based packet I/O for CPU-bound traffic.

---

## 4. Gaps for a Custom NOS (from current implementation status)

| Gap | Notes |
|-----|--------|
| **Packet I/O without KNET** | Cumulus uses TUN + SDK packet TX/RX over BDE. Need the exact SDK APIs (e.g. bcm_rx_*, bcm_tx_* or equivalent) and how they bind to BCM port and TUN fd. |
| **Interface creation** | Resolved: create TUN devices (swp1–swp52, and breakout swp49s0–3 etc.) before or when switchd starts; generate porttab; switchd maps swp ↔ xe. |
| **OpenNSL vs Cumulus SDK** | Cumulus switchd is built against Broadcom’s closed SDK (e.g. 6.3.8). OpenNSL uses different names (opennsl_*) and may use KNET by default; need a path that uses TUN + BDE and matches the netlink → SDK mapping above. |
| **VLAN / L2 programming** | Full L2 behavior (VLAN membership, broadcast domains) needs bcm_vlan_* and L2 table updates; document and implement to match desired L2 design. |
| **Datapath generation** | rc.datapath_0 is generated from datapath.conf and hw_desc; need equivalent logic or copy from Cumulus for buffer/pipeline. |

See: [implementation/IMPLEMENTATION_STATUS.md](../implementation/IMPLEMENTATION_STATUS.md), [cumulus-packet-io-architecture.md](cumulus-packet-io-architecture.md).

---

## 5. References (in order of use)

| Doc | Use |
|-----|-----|
| [ONIE_BOOT_AND_PARTITION_LAYOUT.md](ONIE_BOOT_AND_PARTITION_LAYOUT.md) | Boot and partitions |
| [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md) | BDE, init, registers, DMA |
| [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md) | Config files and portmap |
| [QSFP_BREAKOUT_CONFIGURATION.md](QSFP_BREAKOUT_CONFIGURATION.md) | 40G vs 4×10G, porttab for breakout |
| [initialization-sequence.md](initialization-sequence.md) | switchd startup order |
| [PACKET_IO_VERIFIED.md](PACKET_IO_VERIFIED.md) | TUN, TX/RX path |
| [netlink-message-flow.md](netlink-message-flow.md) | Netlink → SDK mapping |
| [netlink-handlers.md](netlink-handlers.md) | Per-message handlers |
| [api-patterns.md](api-patterns.md) | bcm_l2/l3/port/vlan patterns |
| [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) | Ghidra analysis: register/table strings, xrefs, constants |
| [GAPS_FOR_CUSTOM_SWITCHD_SDK.md](GAPS_FOR_CUSTOM_SWITCHD_SDK.md) | Detailed gap analysis |
| [REVERSE_ENGINEERING_STATUS_REPORT.md](REVERSE_ENGINEERING_STATUS_REPORT.md) | Comprehensive status report: what we have vs what we need |
| [IMPLEMENTATION_STATUS.md](../implementation/IMPLEMENTATION_STATUS.md) | Current gaps and next steps |

Previous high-level architecture: [BROADCOM_CUMULUS_ARCHITECTURE.md](../../previous_findings/BROADCOM_CUMULUS_ARCHITECTURE.md).

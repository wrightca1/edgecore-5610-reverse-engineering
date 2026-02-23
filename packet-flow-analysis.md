# Packet Flow Analysis: Control vs Data Plane

**Purpose**: Document how packets flow through Cumulus switchd architecture
**Source**: Architecture analysis from BROADCOM_CUMULUS_ARCHITECTURE.md

## Control Plane Packets

**Examples**: OSPF hello, BGP update, LACP, LLDP, ARP request

### Flow Path

```
Application (ospfd/bgpd)
    ↓ socket send
Linux Kernel (routing decision)
    ↓ netdev xmit
swpX interface (created by SDK)
    ↓ SDK packet API (via BDE)
BCM56846 ASIC DMA Engine
    ↓ SerDes TX
Physical Port (SFP/QSFP)
    ↓ Ethernet
Network
```

**Key Points**:
- Packets originate in Linux user-space
- Kernel routes to swpX interface (created by SDK, NOT KNET)
- SDK handles packet I/O directly through BDE
- ASIC transmits on wire
- **switchd NOT involved** in packet forwarding
- **NO KNET driver** - Cumulus uses SDK direct packet I/O

## Data Plane Packets

**Examples**: Routed IP packets, switched Ethernet frames

### Flow Path (Hardware Forwarding)

```
Physical Port (SFP/QSFP)
    ↓ SerDes RX
BCM56846 ASIC Ingress Pipeline
    ↓ Parse header (Ethernet/VLAN/IP)
    ↓ L2 lookup (MAC table)
    ↓ L3 lookup (FIB)
    ↓ Forward decision
BCM56846 ASIC Egress Pipeline
    ↓ MAC rewrite, TTL decrement
    ↓ Queue scheduling
    ↓ SerDes TX
Physical Port (SFP/QSFP)
```

**Key Points**:
- **Pure hardware forwarding** - no CPU involvement
- ASIC uses tables programmed by switchd
- Latency: 1-3 microseconds
- Throughput: Line rate (960 Gbps)

## Exception Packets (Punted to CPU)

**Examples**: TTL=1, IP options, packets to switch itself

### Flow Path

```
BCM56846 ASIC
    ↓ Exception condition detected
    ↓ DMA to CPU (via BDE)
SDK RX Handler (in switchd or kernel)
    ↓ Process via SDK packet APIs
    ↓ Deliver to Linux network stack
Linux Kernel
    ↓ Route to application
Application (ospfd, switchd, etc.)
```

**Note**: Cumulus does NOT use KNET driver. Exception packets handled by SDK through BDE.

## switchd Role

switchd does **NOT** forward packets. It:
1. **Programs ASIC tables** (L2, L3, ACL) via SDK
2. **Syncs kernel state** (routes, neighbors) to hardware
3. **Monitors** (stats, link status)

## Packet Capture Points

### Control Plane
- `tcpdump -i swp1` - Captures packets on interface
- `tcpdump -i any host <switch-ip>` - All control traffic

### Data Plane
- Hardware forwarding - not visible to tcpdump
- Exception packets - visible when punted

## References

- [BROADCOM_CUMULUS_ARCHITECTURE.md](../../BROADCOM_CUMULUS_ARCHITECTURE.md) - Detailed flow diagrams
- [netlink-message-flow.md](netlink-message-flow.md) - Kernel ↔ switchd sync

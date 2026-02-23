# Netlink Message Flow

**Purpose**: Document netlink -> ASIC programming flow
**Source**: Architecture analysis + dynamic monitoring

## Capturing Flow

1. Run `scripts/reverse-engineering/monitor-netlink.sh` in one terminal
2. In another terminal, run:
   - `ip link set swp1 up`
   - `ip route add 192.168.1.0/24 via 10.0.0.1 dev swp1`
   - `ping 192.168.1.1` (triggers ARP -> RTM_NEWNEIGH)

3. switchd receives netlink, programs ASIC

## Message Flow Diagram

```
User/Kernel                switchd                    ASIC
     |                         |                         |
     | ip link set swp1 up     |                         |
     |------------------------>| RTM_NEWLINK             |
     |                         | bcm_port_enable_set(1)  |
     |                         |------------------------>|
     |                         |                         | Port 1 TX/RX on
     |                         |                         |
     | ip route add ...        |                         |
     |------------------------>| RTM_NEWROUTE            |
     |                         | bcm_l3_egress_create    |
     |                         | bcm_l3_route_add        |
     |                         |------------------------>|
     |                         |                         | FIB updated
     |                         |                         |
     | (ARP reply)             | RTM_NEWNEIGH            |
     |------------------------>| bcm_l2_addr_add         |
     |                         |------------------------>|
     |                         |                         | L2 table updated
```

## Key Mappings

| User command | Netlink | switchd SDK call |
|--------------|---------|------------------|
| ip link set swp1 up | RTM_NEWLINK (IFF_UP) | bcm_port_enable_set |
| ip link set swp1 down | RTM_NEWLINK (!IFF_UP) | bcm_port_enable_set(0) |
| ip route add A/B via C dev swpN | RTM_NEWROUTE | bcm_l3_egress_create, bcm_l3_route_add |
| ip route del A/B | RTM_DELROUTE | bcm_l3_route_delete |
| (ARP/NDP learn) | RTM_NEWNEIGH | bcm_l2_addr_add |
| (neighbor expire) | RTM_DELNEIGH | bcm_l2_addr_delete |

## References

- [netlink-handlers.md](netlink-handlers.md)
- [api-patterns.md](api-patterns.md)
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found `rtnl_*` functions (`rtnl_route_set_table`, `rtnl_link_set_ifindex`, `rtnl_neigh_set_ifindex`) used in the netlink message handling flow

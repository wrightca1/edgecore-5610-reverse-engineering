# Netlink Handlers in switchd

**Source**: Architecture analysis of Cumulus switchd + BROADCOM_CUMULUS_ARCHITECTURE.md
**Date**: 2026-02-15

## Overview

switchd listens to Linux kernel netlink (NETLINK_ROUTE) and synchronizes kernel networking state to the Broadcom ASIC. Each netlink message type maps to specific bcm_* SDK calls.

## Netlink Socket

- **Family**: NETLINK_ROUTE (RTNETLINK)
- **Groups**: RTMGRP_LINK | RTMGRP_IPV4_ROUTE | RTMGRP_NEIGH
- **Bind**: After SDK init, before main loop

## Message Type to SDK Mapping

### RTM_NEWLINK / RTM_DELLINK

**Purpose**: Interface bringup/shutdown

| Kernel event | switchd action | SDK call |
|--------------|----------------|----------|
| Interface up | Enable port TX/RX | bcm_port_enable_set(unit, port, 1) |
| Interface down | Disable port | bcm_port_enable_set(unit, port, 0) |
| New interface | Register in portmap | portmap_register(ifindex, name) |
| Interface delete | Unregister | portmap_unregister(ifindex) |

**Port resolution**: swp1 -> BCM port via portmap (rc.ports_0 / portmap_name_to_bcm)

### RTM_NEWROUTE / RTM_DELROUTE

**Purpose**: Route addition/deletion (FIB programming)

| Kernel event | switchd action | SDK call |
|--------------|----------------|----------|
| Add route | Create L3 egress, add route | bcm_l3_egress_create, bcm_l3_route_add |
| Delete route | Remove route | bcm_l3_route_delete |
| Multipath route | ECMP handling | bcm_l3_ecmp_* |

**Flow**:
1. Parse netlink: destination, prefix, gateway, oif (outgoing interface)
2. oif -> BCM port via portmap_ifindex_to_bcm
3. Resolve gateway MAC (from neighbor table or ARP)
4. bcm_l3_egress_create(unit, 0, &egress, &egress_id)
5. bcm_l3_route_add(unit, &route) with l3a_subnet, l3a_ip_mask, l3a_intf=egress_id

### RTM_NEWNEIGH / RTM_DELNEIGH

**Purpose**: Neighbor (ARP/NDP) -> L2 MAC table

| Kernel event | switchd action | SDK call |
|--------------|----------------|----------|
| Add neighbor | Add L2 entry | bcm_l2_addr_add(unit, &l2addr) |
| Delete neighbor | Remove L2 entry | bcm_l2_addr_delete |
| Refresh | Update hit bit | bcm_l2_addr_add (modify) |

**Flow**:
1. Parse netlink: IP, MAC, ifindex, state
2. ifindex -> BCM port
3. l2addr.mac = neighbor MAC
4. l2addr.port = BCM port
5. l2addr.vid = VLAN (from interface)
6. bcm_l2_addr_add(unit, &l2addr)

### RTM_NEWADDR / RTM_DELADDR

**Purpose**: Interface address changes (may trigger L3 interface programming)

| Kernel event | switchd action | SDK call |
|--------------|----------------|----------|
| Add address | Create L3 interface | bcm_l3_intf_create |
| Delete address | Remove L3 interface | bcm_l3_intf_delete |

### Other (if supported)

- **VLAN**: May use bridge netlink or config file
- **ACL**: Typically from acltool/config, not netlink
- **Bridge FDB**: RTM_GETNEIGH / bridge fdb sync

## Handler Structure (Pseudo-code)

```c
void netlink_loop(void) {
    int fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    bind(fd, ... RTMGRP_LINK | RTMGRP_IPV4_ROUTE | RTMGRP_NEIGH ...);
    for (;;) {
        recvmsg(fd, &msg, 0);
        for (nlh in msg) {
            switch (nlh->nlmsg_type) {
                case RTM_NEWLINK:
                case RTM_DELLINK:
                    handle_link(nlh);
                    break;
                case RTM_NEWROUTE:
                case RTM_DELROUTE:
                    handle_route(nlh);
                    break;
                case RTM_NEWNEIGH:
                case RTM_DELNEIGH:
                    handle_neighbor(nlh);
                    break;
                ...
            }
        }
    }
}
```

## Dependencies

- **libnl-3** (libnl-route-3): Netlink parsing
- **portmap**: Linux ifindex/ifname <-> BCM port mapping
- **BDE**: Must be initialized before any bcm_* calls

## References

- [BROADCOM_CUMULUS_ARCHITECTURE.md](../../BROADCOM_CUMULUS_ARCHITECTURE.md) - Packet flow, API examples
- [api-patterns.md](api-patterns.md) - Common call sequences
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found `rtnl_route_set_table`, `rtnl_route_get_table`, `rtnl_link_set_ifindex`, `rtnl_neigh_set_ifindex` functions matching these handler patterns
- Linux netlink: man 7 netlink, man 7 rtnetlink

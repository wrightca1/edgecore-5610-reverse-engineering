# switchd API Usage Patterns

**Source**: Reverse engineering of Cumulus switchd + architecture docs
**Date**: 2026-02-15

## Pattern 1: Add Route

**Trigger**: RTM_NEWROUTE

```
bcm_l3_egress_t egress;
bcm_l3_egress_t_init(&egress);
egress.mac_addr = gateway_mac;
egress.port = bcm_port;
egress.vlan = vid;

bcm_l3_egress_create(unit, 0, &egress, &egress_id);

bcm_l3_route_t route;
bcm_l3_route_t_init(&route);
route.l3a_subnet = destination;
route.l3a_ip_mask = mask;
route.l3a_intf = egress_id;

bcm_l3_route_add(unit, &route);
```

## Pattern 2: Add L2 MAC

**Trigger**: RTM_NEWNEIGH

```
bcm_l2_addr_t l2addr;
bcm_l2_addr_t_init(&l2addr);
l2addr.mac = neighbor_mac;
l2addr.port = bcm_port;
l2addr.vid = vlan_id;

bcm_l2_addr_add(unit, &l2addr);
```

## Pattern 3: Port Enable/Disable

**Trigger**: RTM_NEWLINK (IFF_UP change)

```
bcm_port_enable_set(unit, port, enable);  // 1=up, 0=down
```

## Pattern 4: VLAN Create

**Trigger**: Config or bridge netlink

```
bcm_vlan_create(unit, vid);
bcm_vlan_port_add(unit, vid, port, flags);
```

## Pattern 5: Init Sequence

```
bcm_attach(unit, devid, ...);
bcm_init(unit);
// ... rc.soc ...
// ... netlink loop ...
```

## OpenNSL Equivalents

| Cumulus (bcm_*) | OpenNSL (opennsl_*) |
|-----------------|---------------------|
| bcm_init | opennsl_init |
| bcm_attach | opennsl_driver_attach |
| bcm_l3_route_add | opennsl_l3_route_add |
| bcm_l2_addr_add | opennsl_l2_addr_add |
| bcm_port_enable_set | opennsl_port_enable_set |
| bcm_vlan_create | opennsl_vlan_create |
| bcm_l3_egress_create | opennsl_l3_egress_create |

Structure names may differ (bcm_l3_route_t vs opennsl_l3_route_t). Field layout should be similar.

## Related Analysis

- **[GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md)** - Ghidra found HAL (Hardware Abstraction Layer) functions (`hal_add_port_cb`, `sync_port_settings`, `hal_set_route_table_mode`) that show the abstraction layer between netlink handlers and SDK APIs. These HAL functions likely wrap the `bcm_*` API calls shown in the patterns above.

## References

- [sdk-api-mapping.md](sdk-api-mapping.md)
- [netlink-handlers.md](netlink-handlers.md)

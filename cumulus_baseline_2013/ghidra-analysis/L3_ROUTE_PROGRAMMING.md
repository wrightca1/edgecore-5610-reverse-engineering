# switchd L3 Route Programming — Netlink → BCM API

How switchd takes Linux netlink route updates and programs them into
the BCM Trident+ DEFIP/host tables. Found via libnl symbols + xref
analysis.

## Architecture: two netlink sockets

switchd uses libnl-3 (linked dynamically). Two netlink sockets per
subsystem:

| Socket | Purpose | Allocated by | File |
|---|---|---|---|
| `DAT_11e46fd0` | Async event socket | `FUN_10041b80` | `genl_port.c` |
| `DAT_11e46fcc` | Sync request socket (non-blocking) | `FUN_10041b80` | `genl_port.c` |

Each gets `genl_connect()` to bind to the kernel generic-netlink family.

## RX loop — `FUN_1004102c` (176 bytes)

```c
void netlink_rx(void) {
    int rc = nl_recvmsgs_default(async_socket);
    if (rc < 0) {
        log_crit("Failed run recvmsg_default on port socket, err %d, %s",
                 rc, nl_geterror(rc));
    }
}
```

Source: `genl_port.c:0x20a`. This is called from switchd's main loop
when `select()` shows the netlink fd readable. libnl dispatches each
message to the registered callbacks.

## Init/registration — `FUN_10041b80` (1436 bytes)

Source: `genl_port.c:0x2f1, 0x2f7, 0x2fc, 0x302, 0x307, 0x30c`

```c
int genl_port_init(void) {
    port_hash_table = hash_table_alloc(0x200);  // 512 buckets
    if (!port_hash_table) {
        log_crit("Failed to allocate port hash table");
        return 0;
    }
    
    // Allocate async event socket
    async_socket = nl_socket_alloc();
    if (!async_socket) { log_crit("Failed to allocate port socket"); ... }
    if (genl_connect(async_socket) < 0) { log_crit("Failed to genl connect"); ... }
    
    // Allocate sync request socket (non-blocking)
    sync_socket = nl_socket_alloc();
    if (!sync_socket) { log_crit("Failed to allocate port sync socket"); ... }
    if (genl_connect(sync_socket) < 0) { log_crit(...); ... }
    if (nl_socket_set_nonblocking(sync_socket) < 0) {
        log_crit("Failed to set genl port sync socket to non-blocking");
    }
    
    // Modify callbacks for message processing
    nl_socket_modify_cb(async_socket, NL_CB_VALID, NL_CB_CUSTOM, FUN_xxx, NULL);
    
    // Subscribe to generic-netlink port events
    ...
}
```

## L3 route update handler — `FUN_100142ac` (8004 bytes!)

Calls `rtnl_route_alloc` (from libnl-route-3). This is the BIG netlink
RTM_NEWROUTE / RTM_DELROUTE handler:

```c
void route_update_handler(uint flags) {
    // 1. Initialize 3 callback registries (for route, host, intf walks)
    callback_setup(buf_route, 0x28, FUN_100161f0, ...);   // route handler
    callback_setup(buf_host,  0x28, FUN_10016288, ...);   // host handler
    callback_setup(buf_intf,  0x28, FUN_10016344, ...);   // intf handler
    
    // 2. Walk libnl route cache via rtnl_route_iterate
    // 3. For each route:
    //    - extract dst prefix (rtnl_route_get_dst)
    //    - extract nexthop list
    //    - for each nexthop, lookup egress interface
    //    - call bcm_l3_route_add(unit, prefix, mask, egress_intf, ...)
    
    // ... ~8 KB of dispatch logic ...
}
```

Source: `netlink.c` (per the string xref).

Functions called from this handler:
* `FUN_100161f0` — RTM_NEWROUTE callback for libnl cache
* `FUN_10016288` — RTM_NEWNEIGH callback (for L3 host entries)
* `FUN_10016344` — RTM_NEWLINK callback (for L3 interfaces)

## Neighbor update handlers (ARP/NDP → L3 host table)

Three functions deal with `rtnl_neigh_*`:

| Function | Size | Role |
|---|---|---|
| `FUN_100122d4` | 1900 | Main neigh-update handler — translates kernel ARP entries into `bcm_l3_host_add` calls |
| `FUN_1001acd4` | 916 | Neigh-table iterator / cleanup |
| `FUN_1000d9d0` | 760 | Lookup helper |
| `FUN_1000b7e8` | 172 | Alloc helper |
| `FUN_10012174` | 352 | Cleanup helper |
| `FUN_1001b068` | 460 | Alloc + program |

## Config tunables exposed via /config sysfs

From string analysis (in `FUN_10005ecc`):

| Path | Purpose |
|---|---|
| `/config/route/table` | Which Linux routing table to monitor (default = 254 = main) |
| `/config/route/host_max_percent` | Max % of host table to use for hosts (vs reserved for routes) |
| `/config/route/delete_dead_routes` | Cleanup dead nexthops automatically |
| `/config/route/max_routes` | Max routes to program |

Debug paths:
* `/debug/neigh_update_start`
* `/debug/neigh_update_stop`
* `/debug/neigh_update_iterate`

These are exposed via switchd's internal config tree (similar to
sysctl). Users probably manipulate them via `cl-cfg` or directly.

## Source files confirmed

| Path | What |
|---|---|
| `netlink.c` | Main netlink event handler (route + neigh) |
| `genl_port.c` | Generic netlink for port events (link state, MAC, MTU) |
| `tuntap.c` | TUN device creation |
| `nic.c` | Packet I/O glue |

## The full L3 programming flow

```
Linux IP stack: ip route add 10.0.0.0/24 via 10.101.101.2
    │
    ▼ generates RTM_NEWROUTE on rtnetlink socket
    │
switchd's netlink RX loop (FUN_1004102c)
    │ select() wakes, calls nl_recvmsgs_default()
    ▼
libnl-3 dispatches to NL_CB_VALID callback (registered in genl_port_init)
    │
    ▼
FUN_100142ac (route_update_handler, 8 KB)
    │ - Parses route via rtnl_route_alloc + rtnl_route_get_dst
    │ - Walks nexthop list
    │ - Looks up egress interface (rtnl_link_get)
    │ - Looks up nexthop MAC via L3 host table (rtnl_neigh_get)
    │ - Calls bcm_l3_egress_create (or finds existing egress)
    │ - Calls bcm_l3_route_add(unit, defip_entry)
    ▼
bcm_l3_route_add (in switchd's statically-linked BCM SDK)
    │ - port_validate
    │ - soc_reg32_set / table write via SCHAN
    │ - actual L3_DEFIP table entry write
    ▼
soc_schan_op → soc_reg_write → linux_user_bde_ioctl (LUBDE_WRITE_REG)
    │
    ▼
linux-kernel-bde.ko: ioctl handler → _write to BAR0 + addr
    │
    ▼
CMICm fabric → DEFIP TCAM entry programmed

═══════════════════════════════════════════════════════════
After programming, when a packet matches:
═══════════════════════════════════════════════════════════
Wire → ASIC → iPipe → My_Station_TCAM → L3 pipeline
    → DEFIP TCAM lookup matches 10.0.0.0/24
    → L3_EGRESS index → egress port + dst MAC
    → frame forwarded
```

## EdgeNOS implications

For EdgeNOS to route packets correctly:

1. **Implement a netlink listener** — libnl-3 or rolled-your-own.
   Listen on `NETLINK_ROUTE` for `RTNLGRP_IPV4_ROUTE`, `RTNLGRP_NEIGH`,
   `RTNLGRP_LINK`, `RTNLGRP_IPV4_IFADDR`, etc.

2. **For RTM_NEWROUTE**: parse dst prefix + nexthop. Look up nexthop
   MAC via internal ARP cache (or do an active neigh-get). Call
   `bcm_l3_route_add` (equivalent OpenMDK function).

3. **For RTM_NEWNEIGH**: that's an ARP/ND entry. Call
   `bcm_l3_host_add` (equivalent OpenMDK function) with the IP+MAC.

4. **For RTM_NEWLINK**: handle interface up/down. Update L3_IIF table
   if the interface gets an IP address (RTM_NEWADDR).

5. **The dual-socket pattern** — one async for events, one sync for
   queries — is a libnl convention. EdgeNOS should follow it.

EdgeNOS already does some of this (per memory: "ARP working to Nexus
peer"). The missing piece for ICMP forwarding might be the RTM_NEWROUTE
handler not properly programming DEFIP, OR an L3 interface not
created correctly. With the function map above we can now diff EdgeNOS
behavior against Cumulus's.

## Files

* `switchd_l3_route_callers.txt` — list of L3 / netlink callers
* `switchd_l3_decomp.c` — 12 small functions decompiled
* `switchd_l3_big_decomp.c` — 11 large functions (incl. 8 KB route handler)
* `switchd_netlink_strings.txt` — netlink-related string xrefs
* `scripts/L3RouteProg.java`, `L3DecompBig.java`

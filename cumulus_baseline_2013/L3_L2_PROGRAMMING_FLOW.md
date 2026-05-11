# L3 & L2 Programming — From netlink to hardware tables

How Cumulus turns Linux netlink events (route adds, neighbor entries,
FDB learns) into actual BCM56846 chip-table writes. Recovered from
static decompilation of the netlink listeners, switchd's HAL bridge,
and the BCM SDK's L2/L3 API entry points.

This closes the gap that was listed in `WHATS_MISSING.md` as
"L3 route programming" and "L2 MAC learning + FDB".

---

## 1. The four-table model

The chip's forwarding state lives in **four canonical tables**:

| Table | Purpose | Size | Indexed by | Holds |
|---|---|---|---|---|
| **L2_TABLE** | MAC-VLAN forwarding | 131,072 entries | hash(MAC, VLAN) | dest port / trunk for L2 frames |
| **L3_DEFIP** | IPv4/v6 longest-prefix | 16,284 v4 + 256 v6-long | TCAM (priority match) | nexthop ID for routed frames |
| **L3_HOST** | IPv4/v6 host (/32, /128) | 8,192 entries | hash(IP, VRF) | direct nexthop |
| **L3_EGRESS / EGR_NEXT_HOP** | nexthop info | variable | egress ID | dst MAC, output port, VLAN |

The Linux kernel doesn't talk to these directly — it generates **netlink
events** (`RTM_NEWROUTE`, `RTM_NEWNEIGH`, `RTM_NEWLINK`) that switchd
listens to. switchd's HAL layer then calls the appropriate `bcm_l3_*`
or `bcm_l2_*` API.

---

## 2. The complete netlink → chip-table path

```
┌──────────────────────────────────────────────────────────────────────┐
│ Linux kernel (route table, neighbor table, bridge fdb)               │
└───────────────────────────┬──────────────────────────────────────────┘
                            │ netlink (RTM_NEWROUTE, RTM_NEWNEIGH, ...)
                            ▼
┌──────────────────────────────────────────────────────────────────────┐
│ switchd netlink listener (libnl-3)                                   │
│   FUN_1004102c — netlink_rx_loop (nl_recvmsgs_default)              │
│   FUN_10041b80 — callback registration                              │
│   FUN_100142ac — route handler (8 KB)                               │
└───────────────────────────┬──────────────────────────────────────────┘
                            │ build hal_route_t / hal_neigh_t / hal_l2_t
                            ▼
┌──────────────────────────────────────────────────────────────────────┐
│ switchd HAL bridge                                                    │
│   FUN_1005f1b4 — add_update_route (THE L3 entry point)              │
│   FUN_10060c7c — switchd L2 addr add                                │
│   FUN_1005a5a8 — switchd L3 intf create                             │
│   FUN_1005d898 — switchd L3 egress create                           │
└───────────────────────────┬──────────────────────────────────────────┘
                            │ build bcm_l3_route_t / bcm_l3_host_t /
                            │       bcm_l2_addr_t / bcm_l3_egress_t
                            ▼
┌──────────────────────────────────────────────────────────────────────┐
│ BCM SDK API                                                           │
│   FUN_103f85a0 — bcm_l3_route_add  → L3_DEFIP TCAM                  │
│   FUN_103f3128 — bcm_l3_host_add   → L3_HOST hash table             │
│   FUN_103f5ef8 — bcm_l3_intf_create → L3_IIF table                  │
│   FUN_103f054c — bcm_l3_egress_create → EGR_NEXT_HOP                │
│   FUN_103e6cf0 — bcm_l2_addr_add   → L2_TABLE hash                  │
└───────────────────────────┬──────────────────────────────────────────┘
                            │ build SCHAN write or table-DMA op
                            ▼
┌──────────────────────────────────────────────────────────────────────┐
│ SCHAN transaction (per CMIC_SCHAN_DMA_DEEP_DIVE)                     │
│   Block ID = MMU / L3 / IPIPE depending on table                    │
│   Opcode  = MEM_W (0x0f) or TBL_W (0x13) for memory writes          │
│   Multi-word write (L2 entry = 4 words, L3 host = 5, DEFIP = 6+)    │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 3. L3 Route Add — the switchd entry point

The switchd function that gets called when the kernel adds a route:

### `FUN_1005f1b4` — `add_update_route(unit, hal_route, update_flag)`

```c
int add_update_route(int unit_ctx, hal_route_t *hal_route, char is_update) {
    bcm_l3_route_t route_or_host[8];   // local_e0 array

    /* CRITICAL DECISION: host (/32, /128) vs subnet route */
    if (hal_route->flags & 0x10) {
        /* === HOST PATH (/32, /128) — use L3_HOST table === */

        if (!hal_route_to_hw_host(unit_ctx, hal_route, route_or_host)) {
            log("hal_route_to_hw_host failed");
            return 0;
        }

        if (is_update) {
            route_or_host[0] |= 0x100;     // BCM_L3_REPLACE flag

            /* Find old entry first */
            bcm_l3_host_t old;
            hal_route_to_hw_host(hal_route, &old);
            if (bcm_l3_host_find(unit, &old) < 0) {
                log("bcm_l3_host_find failed");
                return 0;
            }
        }

        /* Add to L3_HOST table — calls FUN_103f3128 = bcm_l3_host_add */
        int rc = bcm_l3_host_add(unit, route_or_host);
        if (rc < 0) {
            log("bcm_l3_host_add failed: %s", err_str(rc));
            return 0;
        }
    } else {
        /* === SUBNET PATH — use L3_DEFIP TCAM === */

        if (!hal_route_to_hw_route(unit_ctx, hal_route, route_or_host)) {
            log("hal_route_to_hw_route failed");
            return 0;
        }

        if (is_update) {
            route_or_host[0] |= 0x100;
            bcm_l3_route_t old;
            hal_route_to_hw_route(hal_route, &old);
            if (bcm_l3_route_get(unit, &old) < 0) {
                log("bcm_l3_route_get failed");
                return 0;
            }
        }

        /* Add to L3_DEFIP TCAM — calls FUN_103f85a0 = bcm_l3_route_add */
        int rc = bcm_l3_route_add(unit, route_or_host);
        if (rc < 0) {
            log("bcm_l3_route_add failed: %s", err_str(rc));
            return 0;
        }
    }

    /* Clean up old egress object on update */
    if (is_update && old_eid != new_eid) {
        bcm_l3_egress_destroy_if_unused(unit, old_eid);
    }

    return 1;   // success
}
```

### The decision: when host vs route?

Cumulus's HAL marks each route's `flags` with bit `0x10` set if the
prefix length is the full address width:
- IPv4 /32 → L3_HOST
- IPv6 /128 → L3_HOST
- Everything shorter → L3_DEFIP (LPM TCAM)

The L3_HOST table is a hash table (faster lookup, but fixed-size), the
DEFIP is a TCAM (slower lookup, but supports prefix matching).

### `bcm_l3_route_t` struct layout (Cumulus 2.5 SDK)

```c
struct bcm_l3_route_t {
    /* +0x00 */ uint32_t flags;          // BCM_L3_IPV6, BCM_L3_REPLACE, ...
    /* +0x04 */ bcm_ip_t ip;             // IPv4 dest (4 B) or pointer to v6
    /* +0x08 */ bcm_ip_t ip_mask;
    /* +0x0c */ uint32_t vrf;
    /* +0x10 */ bcm_if_t egress_if;      // egress nexthop ID
    /* +0x14 */ uint8_t  mod_id;
    /* +0x18 */ uint8_t  pri;
    /* +0x1c */ uint32_t reserved[...];
    /* ... */
};
```

Flag bits:
- `0x0001` BCM_L3_IPV6 — entry is IPv6
- `0x0002` BCM_L3_REPLACE — replace existing entry
- `0x0010` BCM_L3_HIT — for stats query
- `0x0100` BCM_L3_REPLACE_FIND — used for is_update path
- `0x4000` BCM_L3_RPE — Replicated Path Entries (multipath)

### Inside `bcm_l3_route_add` (FUN_103f85a0 → FUN_101d8854)

The actual implementation function is `FUN_101d8854` (12 KB!). High-level flow:

```c
int bcm_l3_route_add(unit, route) {
    /* Validate args */
    /* Look up egress nexthop info */
    /* Format DEFIP entry words (multi-word entry):
       Word 0: V/P/VRF flags, IP[31:0]
       Word 1: IP[63:32] (for v6)
       Word 2: prefix length
       Word 3: nexthop index
       Word 4: priority / class
    */
    /* For IPv6 long-prefix: split across two paired DEFIP entries */
    /* SCHAN write to L3_DEFIP table (block ID = IPIPE 0x01) */
    soc_mem_write(unit, L3_DEFIP, index, entry_words);

    /* For ALPM (Algorithmic LPM): may use L3_DEFIP_ALPM_IPV6_64 or ALPM bucket */
}
```

Trident+ supports two DEFIP modes:
- **Traditional TCAM**: 16,284 entries, linear LPM
- **ALPM**: Algorithmic Longest-Prefix-Match (better scaling for v6)

The strings we found include `L3_DEFIP_ALPM_IPV6_64` and
`td2_l3_defip_pair128` — Cumulus uses one or the other depending on
chip config flags.

---

## 4. L2 FDB Programming

### `FUN_10060c7c` — switchd's L2 addr add (1028 B)

Called when:
- Linux bridge FDB add (`bridge fdb add`)
- Kernel netlink RTM_NEWNEIGH (with L2 type)
- Static MAC config

```c
int switchd_l2_addr_add(int unit_ctx, hal_l2_t *l2_entry) {
    bcm_l2_addr_t bcm_l2[8];   // local_16c
    short vlan = l2_entry->vlan;     // l2_entry+0xc

    /* If VLAN not specified, look it up by interface */
    if (vlan == 0) {
        vlan = lookup_vlan_by_intf(unit_ctx, l2_entry->intf);  // FUN_1005fb90
        if (vlan == 0) return 0;
    }

    /* Build bcm_l2_addr_t */
    build_l2_addr(bcm_l2, l2_entry, vlan);

    bool is_dynamic = check_dynamic_flag(vlan);

    /* Decide port/trunk/gport based on entry type */
    switch (l2_entry->type) {  // l2_entry + 0x10
    case 0:  // Normal port
        if (is_dynamic || l2_entry->port == -1) {
            bcm_l2->port = port_to_modport(l2_entry->port);
        } else {
            vlan_if_t *vif = get_vlan_if(unit_ctx, l2_entry->type);
            if (!vif) return 0;
            bcm_l2->dest_port = vif->dest_port;
        }
        break;

    case 1:  // Trunk
        if (is_dynamic) {
            bcm_l2->flags |= 0x80;       // BCM_L2_TRUNK_MEMBER
            bcm_l2->trunk_id = l2_entry->trunk_id;
        } else {
            vlan_if_t *vif = get_vlan_if(unit_ctx, l2_entry->type);
            bcm_l2->dest_port = vif->dest_port;
        }
        break;

    case 2:  // Chip-global (CPU)
        bcm_l2->dest_port = unit_ctx->cpu_port;
        break;

    case 3:  // Tunnel
        if (l2_entry->tunnel_port == 0) {
            bcm_l2->flags |= 0x04;       // BCM_L2_TUNNEL
            bcm_l2->dest_port = unit_ctx->cpu_port;
        } else {
            bcm_l2->dest_port = l2_entry->tunnel_port;
        }
        break;

    default:
        return 1;
    }

    /* Static MAC? */
    if (l2_entry->is_static)             // l2_entry + 0x78 == 1
        bcm_l2->flags |= 0x20;            // BCM_L2_STATIC

    /* Call SDK */
    int rc = bcm_l2_addr_add(unit, bcm_l2);   // FUN_103e6cf0
    if (rc < 0) {
        log("bcm_l2_addr_add failed: %s", err_str(rc));
        return 0;
    }
    return 1;
}
```

### `bcm_l2_addr_t` struct layout

```c
struct bcm_l2_addr_t {
    /* +0x00 */ uint32_t flags;          // BCM_L2_STATIC, BCM_L2_TRUNK_MEMBER, BCM_L2_TUNNEL, ...
    /* +0x04 */ bcm_mac_t mac;           // 6 bytes
    /* +0x0a */ uint16_t  pad;
    /* +0x0c */ bcm_vlan_t vlan;         // 12-bit VLAN
    /* +0x10 */ uint16_t  modid_port;    // (modid << 8) | port
    /* +0x14 */ bcm_gport_t dest_port;
    /* +0x18 */ uint32_t  encap_id;      // for tunnels
    /* ... */
};
```

Flag bits:
- `0x0004` BCM_L2_TUNNEL — tunnel-encapsulated
- `0x0020` BCM_L2_STATIC — static (not aged)
- `0x0080` BCM_L2_TRUNK_MEMBER — points at trunk (LAG)
- `0x0100` BCM_L2_REPLACE — replace existing

---

## 5. L2 MAC Learning — the MOD FIFO thread

### `FUN_10eaf31c` — `soc_l2mod_fifo_thread` (932 B)

This is the **kernel-level** event-handler thread for the chip's L2 MOD
FIFO. Each time the chip learns or ages an L2 MAC entry, it pushes a
record into an on-chip FIFO. The host-side thread:

```c
void soc_l2mod_fifo_thread(int unit) {
    chip_state_t *cs = &unit_state[unit];

    /* Compute entry size from chip info */
    int entry_size_words = (mod_fifo_info->entry_width + 3) / 4;
    int max_entries = (chip_regs[L2_MOD_FIFO_END_REG] - mod_fifo_info->start) + 1;
    int word_count = max_entries * entry_size_words;

    /* Allocate host buffer for FIFO contents */
    uint32_t *buffer = soc_dma_alloc(unit, word_count * 4, "L2_MOD_FIFOm");
    if (!buffer) {
        cs->fifo_status = -1;
        log_err("L2_MOD_FIFO buffer alloc failed");
        signal_thread_exit(...);
        return;
    }

    /* Main loop */
    while (cs->fifo_run_flag != 0) {           // +0x2f1964 = run flag
        /* Wait on semaphore signaled by IRQ on L2_MOD_FIFO_FULL */
        sem_wait(cs->fifo_wakeup_sem,           // +0x2f18f4
                 cs->fifo_run_flag);

        soc_l2mod_fifo_irq_enable(unit, 1);    // disable while processing
        soc_l2mod_fifo_count_get(unit, &count); // FUN_10eadc58
        if (count == 0) {
            soc_l2mod_fifo_irq_enable(unit, 0);
            continue;
        }

        /* DMA the FIFO contents from on-chip SRAM to host buffer */
        int rc = soc_mem_read(unit, L2_MOD_FIFOm,
                              0xffffffff /*copyno*/,
                              start_idx, end_idx, buffer);
        if (rc < 0) {
            log("AbnormalThreadExit:soc_l2mod_fifo_thread,DMA failed: %s", err_str(rc));
            signal_thread_exit(rc);
            break;
        }

        soc_l2mod_fifo_irq_enable(unit, 0);

        /* Dispatch each entry to registered callbacks */
        for (int i = 0; i < count; i++) {
            uint32_t *entry = buffer + (i * entry_size_words);
            dispatch_l2_event(unit, cs->event_callback, entry);   // FUN_10eaf214
        }

        /* Re-arm IRQ */
        bcm_irq_re_enable(unit, 0x20);   // L2_MOD_FIFO bit
    }

    /* Cleanup */
    soc_dma_free(unit, buffer);
    cs->fifo_status = -1;
    signal_thread_exit(0);
}
```

### L2 MOD FIFO entry format (`L2_MOD_FIFOm`)

Each entry is multiple 32-bit words (chip-specific width — typically
4-5 words for Trident+):

```
Word 0  bits 0..2    OP     (0=LEARN, 1=AGE, 2=DELETE)
        bits 3..6    SOURCE (which engine generated this — learning vs aging vs SDK)
Word 1  bits 0..47   MAC address (6 bytes)
Word 2  bits 0..11   VLAN
        bits 12..18  PORT (or trunk)
        bit  19      IS_TRUNK
Word 3  bits 0..15   class_id / metadata
        bit  16      STATIC
        bit  17      L3
        bit  18      VALID
Word 4  CRC / parity
```

The `dispatch_l2_event` callback (FUN_10eaf214) registered by switchd
filters by OP:
- LEARN: report via netlink (`RTM_NEWNEIGH` with `NDA_DST=MAC`)
- AGE: report deletion (`RTM_DELNEIGH`)
- DELETE: only fires if `l2_mod_fifo_enable_l2_delete=1` (Cumulus has
  this set to 0 — see rc.datapath_0 — to prevent FIFO overflow during
  bulk operations)

### The `aux_arb_control.l2_mod_fifo_enable_l2_delete = 0` trick

Cumulus's rc.datapath_0 explicitly disables recording of DELETE events:

```
modreg aux_arb_control l2_mod_fifo_enable_l2_delete=0
```

The comment in rc.datapath_0 says:
> Disable l2 entry deletes being recorded to l2_mod_fifo. was result in
> l2 entry bcm_l2_addr_delete failures b'cos of the mod fifo overflow.

When the SDK does a `bcm_l2_addr_delete()`, it doesn't need a FIFO event
back — the software already knows about its own deletes. Recording them
just wastes FIFO slots, and under bulk delete (e.g., port-down event
flushing all MACs on a port) the FIFO overflows and learns get lost.

---

## 6. Where the chip-side tables live

Recovered from string references in `bcm_register_names.txt`:

### L3 tables

| Table name | Block | Size | Entry width |
|---|---|---|---|
| `L3_DEFIP` | IPIPE | 16,284 entries | 6 words (24 B) |
| `L3_DEFIP_PAIR_128` | IPIPE | 8,192 paired entries | 12 words (48 B) for v6 /128 |
| `L3_DEFIP_ALPM_IPV6_64` | IPIPE | (ALPM mode) | 8 words |
| `L3_HOST` (also `L3_ENTRY_IPV4_UNICAST`) | IPIPE | 8,192 | 4 words |
| `L3_ENTRY_IPV6_UNICAST` | IPIPE | (subset of L3_HOST) | 6 words |
| `L3_IIF` (Ingress Interface) | IPIPE | 4,096 | 2 words |
| `EGR_NEXT_HOP` / `EGR_L3_NEXT_HOP` | EPIPE | 8,192 | 4 words |
| `ECMP_GROUP` | IPIPE | 1,024 groups × 64 members | — |

### L2 tables

| Table name | Block | Size | Entry width |
|---|---|---|---|
| `L2_TABLE` (also `L2X`) | IPIPE | 131,072 entries | 4 words (16 B) |
| `L2_MOD_FIFOm` | (CMICm) | 16-32 deep | 4 words |
| `MY_STATION_TCAM` | IPIPE | 256 entries | TCAM, my-mac match |
| `EGR_VLAN` | EPIPE | 4,096 | 2 words |

---

## 7. Linkscan — port state monitoring

### `bcm_linkscan_*` functions (small SDK wrappers, 17 found)

The linkscan subsystem polls every port's PHY MII status register every
250 ms (default — set via `bcm_linkscan_interval`). On state change, it
fires a callback registered with `bcm_linkscan_register`.

```c
/* Internal — the polling thread */
void linkscan_thread(int unit) {
    while (1) {
        usleep(250000);

        for (int port = 1; port < num_ports; port++) {
            uint16_t mii_status = mdio_read(unit, port, MII_STATUS_REG);
            bool linked_now = (mii_status & MII_BMSR_LSTATUS) != 0;
            bool linked_was = port_state[port].linked;

            if (linked_now != linked_was) {
                port_state[port].linked = linked_now;
                /* Fire callback (switchd registers one that emits netlink) */
                callback(unit, port, linked_now);
            }
        }
    }
}
```

switchd's linkscan callback emits netlink `RTM_NEWLINK` events with the
`oper` state, which the Linux kernel propagates to the `swp*` netdev.
That's how `ip link` sees ports as up/down.

---

## 8. KNET — present but unused

The BCM SDK's KNET subsystem is **statically linked into switchd** but
the kernel module (`linux-bcm-knet.ko`) is **not loaded**. So the KNET
functions exist as code but never run.

KNET would normally provide kernel-level packet I/O via:
- `bcm_knet_init(unit)` — initialize subsystem
- `bcm_knet_netif_create(unit, &netif)` — register a kernel netdev
- `bcm_knet_filter_create(unit, &filter)` — install a packet-filter rule

Cumulus chose TUN instead of KNET because:
1. **License/distribution**: KNET requires Broadcom-licensed kernel module
2. **Debugging**: TUN traffic is visible via tcpdump on tunX
3. **Userspace policy**: TUN puts decisions in userspace daemon

For EdgeNOS, sticking with TUN is the right choice — but knowing KNET
is *available* means you could switch architectures later if needed
(e.g., for higher pps throughput).

---

## 9. Putting it together: route programming end-to-end

When you run `ip route add 10.5.0.0/24 dev swp1 via 192.168.1.1`:

```
1. Kernel: rtnetlink processes the add, updates kernel FIB
2. Kernel: emits RTM_NEWROUTE on the route group
3. switchd: nl_recvmsgs_default (FUN_1004102c) wakes from epoll
4. switchd: route_handler (FUN_100142ac) parses the message:
     dest: 10.5.0.0/24
     gateway: 192.168.1.1
     device: swp1 (= xe0)
5. switchd: builds hal_route_t struct
6. switchd: looks up the gateway in L3_HOST (192.168.1.1 should already
   be there as a resolved ARP entry):
     - If found: use its egress_if as the new route's nexthop
     - If not found (next-hop unresolved): trigger ARP, queue route
7. switchd: calls add_update_route(unit, hal_route, is_update=0)
     - FUN_1005f1b4
8. add_update_route: takes the SUBNET path (prefix=/24, not /32)
     - hal_route_to_hw_route fills bcm_l3_route_t
     - bcm_l3_route_add(unit, route)
9. bcm_l3_route_add: builds DEFIP TCAM entry
     - Format: [V|VRF|IP|mask|nexthop_id|priority]
     - SCHAN write opcode TBL_W (0x13) to L3_DEFIP table
10. Chip: TCAM hardware stores the entry
11. Next packet to 10.5.0.X arrives:
     - IPIPE parser extracts dest IP
     - DEFIP lookup matches /24 entry → nexthop_id
     - EGR_NEXT_HOP lookup → dst MAC + output port
     - EPIPE replaces dst MAC, sends out swp1
```

For an ARP entry (`ip neigh add 192.168.1.1 lladdr 00:aa:... dev swp1`):

```
1. Kernel emits RTM_NEWNEIGH
2. switchd: neigh_handler (FUN_100122d4 or FUN_1001acd4 or FUN_1000d9d0)
3. switchd: builds bcm_l3_egress_t with the dst MAC + port
4. bcm_l3_egress_create → writes EGR_NEXT_HOP entry, returns egress_id
5. switchd: builds bcm_l3_host_t pointing at egress_id
6. bcm_l3_host_add → writes L3_HOST hash entry
```

For an L2 entry (kernel bridge learns a MAC):

```
1. Kernel emits RTM_NEWNEIGH with L2 type or FDB add
2. switchd: handler builds hal_l2_t struct
3. switchd: switchd_l2_addr_add (FUN_10060c7c)
4. bcm_l2_addr_add → writes L2_TABLE hash entry
```

Conversely, when the chip learns a MAC from incoming traffic:

```
1. Packet arrives, IPIPE parser extracts src MAC + VLAN
2. L2_TABLE hash lookup: miss
3. Chip pushes LEARN event to L2_MOD_FIFO
4. CMICm IRQ on L2_MOD_FIFO_FULL fires
5. soc_l2mod_fifo_thread (FUN_10eaf31c) wakes
6. Reads FIFO contents via soc_mem_read
7. Dispatches each event to registered callbacks
8. switchd: emits RTM_NEWNEIGH to kernel
9. Kernel: updates bridge fdb
```

---

## 10. EdgeNOS checklist — what you need to make L3+L2 work

### For unicast routing
- [ ] Netlink listener (libnl3) registered for RTNL_ROUTE / RTNL_NEIGH groups
- [ ] route_handler: builds bcm_l3_route_t from netlink message
- [ ] L3 host/route decision based on prefix length
- [ ] **L3 intf setup**: for each `swp*` netdev, create a bcm_l3_intf
      (FUN_103f5ef8 — `bcm_l3_intf_create`)
- [ ] **EGR_NEXT_HOP** for each resolved gateway (after ARP completes)
- [ ] **bcm_l3_host_add** / **bcm_l3_route_add** plumbed
- [ ] **MY_STATION_TCAM** entry: chassis MAC (so chip routes packets with
      that dst MAC rather than flooding as L2)

### For L2 learning
- [ ] L2 MOD FIFO thread implemented
- [ ] L2 event callback that emits RTM_NEWNEIGH netlink to kernel
- [ ] `aux_arb_control.l2_mod_fifo_enable_l2_delete = 0` set (per
      rc.datapath_0)
- [ ] FDB add handler that calls `bcm_l2_addr_add`
- [ ] FDB flush on port-down event

### For ARP/ND
- [ ] netlink RTM_NEWNEIGH handler builds bcm_l3_egress_t
- [ ] **bcm_l3_egress_create** plumbed
- [ ] L3 host entry installed pointing at the egress

---

## 11. Files

- `ghidra-analysis/switchd_l3l2_decomp.c` — 22 functions decompiled
- `ghidra-analysis/switchd_l3l2fp_hunt.txt` — function discovery by category
- `L3_ROUTE_PROGRAMMING.md` — earlier doc with the netlink callers
- `PACKET_FLOW_END_TO_END.md` — packet I/O end-to-end
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` — SCHAN transaction protocol

---

*L3+L2 programming flow recovered from static analysis. Closes the
"L3 route/host programming" and "L2 MAC learning + FDB" gaps that were
listed as not-started in WHATS_MISSING.md.*

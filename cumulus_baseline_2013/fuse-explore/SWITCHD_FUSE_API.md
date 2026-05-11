# switchd FUSE Control Filesystem — `/cumulus/switchd/`

switchd is statically linked against `libfuse.so.2` and mounts a virtual
control filesystem at `/cumulus/switchd/`. This is **the entire control
plane API** for switchd, exposed as filesystem entries.

* **139 directories, 296 files** total
* Version: `1.0-cl2.5`

This is brilliant design — every userspace tool (`cl-acltool`, `cl-bcmcmd`,
`cl-netstat`, etc.) interacts with switchd via these virtual files. No
RPC framework, no IPC sockets — just `open()` / `read()` / `write()`.

## Top-level tree

```
/cumulus/switchd/
├── version            (file: "1.0-cl2.5")
├── config/            (250 RW files - persistent config)
├── ctrl/              (6 trigger files - request actions)
├── run/               (36 read-only files - runtime state)
└── clear/             (4 action files - reset counters)
```

## `config/` — Persistent runtime configuration (250 files)

### Top-level toggles
| Path | Default | Meaning |
|---|---|---|
| `config/disable_internal_hw_err_restart` | FALSE | Restart switchd on HW err |
| `config/disable_internal_parity_restart` | **TRUE** | Don't restart on parity err |
| `config/ignore_non_swps` | FALSE | Process all netifs or only swp* |
| `config/logging` | `file:/var/log/switchd.log=INFO` | Log destination + level |
| `config/resv_vlan_range` | `3300-3999` | Reserved VLAN range (Cumulus uses 3301-3352 for per-port VLANs) |

### `config/acl/`
| Path | Default | Meaning |
|---|---|---|
| `acl/non_atomic_update_mode` | FALSE | Atomic vs incremental ACL updates |
| `acl/optimize_hw` | FALSE | HW optimization (slice compression) |

### `config/arp/`
| Path | Default | Meaning |
|---|---|---|
| `arp/next_hops` | TRUE | Auto-program ARP entries as L3 nexthops |

### `config/bridge/`
| Path | Default | Meaning |
|---|---|---|
| `bridge/broadcast_frame_to_cpu` | FALSE | Copy all bcast to CPU (debug) |

### `config/buf_util/` — Buffer utilization monitoring
| Path | Default | Meaning |
|---|---|---|
| `buf_util/measure_interval` | 0 | Sampling period (0 = off) |
| `buf_util/poll_interval` | 0 | Poll period |

### `config/coalesce/` — Interrupt coalescing
| Path | Default | Meaning |
|---|---|---|
| `coalesce/offset` | 0 | IRQ delay offset |
| `coalesce/reducer` | 1 | Reduction factor |
| `coalesce/timeout` | 10 | Coalescing timeout |

### `config/interface/swp{N}/` — Per-port (×52)
Each swp has:
* `interface_mode` — XFI (10G), KR4 (40G), etc.
* `storm_control/broadcast` — bps limit (0 = unlimited)
* `storm_control/multicast` — bps limit
* `storm_control/unknown_unicast` — bps limit

### `config/netlink/`
| Path | Default | Meaning |
|---|---|---|
| `netlink/buf_size` | **94371840** (~90 MB) | Netlink socket buffer |

### `config/route/`
| Path | Default | Meaning |
|---|---|---|
| `route/table` | 254 (= main) | Which Linux routing table to monitor |
| `route/max_routes` | 32768 | Max DEFIP entries |
| `route/host_max_percent` | 50 | % of host table reserved for hosts (vs routes) |
| `route/delete_dead_routes` | TRUE | Auto-cleanup dead nexthops |

### `config/stats/`
| Path | Default | Meaning |
|---|---|---|
| `stats/poll_interval` | 5000 (5 s) | Stats collection period |
| `stats/vdev_hw_poll_interval` | 5 | Per-device HW poll |
| `stats/vlan/aggregate` | BRIEF | VLAN stats detail level |
| `stats/vlan/show_internal_vlans` | FALSE | Show 3300+ per-port VLANs |
| `stats/vxlan/aggregate` | DETAIL | VXLAN aggregation |
| `stats/vxlan/member` | BRIEF | VXLAN member stats |

### `config/traffic/` — DoS protection
| Path | Default | Meaning |
|---|---|---|
| `traffic/cut_through_enable` | **TRUE** | Cut-through forwarding (vs store-forward) |
| `traffic/dos_enable` | FALSE | DoS protection master switch |
| `traffic/dos/sip_eq_dip` | FALSE | Drop src=dst IP |
| `traffic/dos/smac_eq_dmac` | FALSE | Drop src=dst MAC |
| `traffic/dos/icmp_frag` | FALSE | Drop fragmented ICMP |
| `traffic/dos/icmpv4_length`, `icmpv6_length` | FALSE | Drop malformed ICMP length |
| `traffic/dos/ipv6_min_frag` | FALSE | Drop too-small v6 frags |
| `traffic/dos/tcp_*` | FALSE | Various TCP malformed-flag drops |
| `traffic/dos/udp_ports_eq` | FALSE | Drop UDP src==dst port |

### `config/vxlan/`
| Path | Default | Meaning |
|---|---|---|
| `vxlan/default_ttl` | 64 | VXLAN tunnel TTL |

## `ctrl/` — Action triggers (6 files)

| Path | Effect when written |
|---|---|
| `ctrl/acl/resync` | Re-read iptables, program BCM FP (used by `cl-acltool`) |
| `ctrl/acl/stop_stats_sync` | Pause ACL stats sync |
| `ctrl/acl/reset_stats_sync` | Zero ACL counters |
| `ctrl/hal/resync` | Re-sync HAL (full hardware re-program) |
| `ctrl/netlink/resync` | Re-read kernel netlink state |
| `ctrl/netlink/nl_logger` | Toggle netlink debug logging |
| `ctrl/logger` | Switchd logger control |
| `ctrl/sample/ulog_channel` | ULOG channel for sampled packets |
| `ctrl/resync` | **GLOBAL resync** — everything |

Used by userspace tools as **write + read** sequence:
1. Tool writes "1" to trigger action
2. Tool seeks 0 + reads → gets status string ("0" = OK, error otherwise)

## `run/` — Read-only runtime state (36 files)

### `run/acl_info/` — FP/TCAM occupancy (live)

| Path | Live value | Max |
|---|---|---|
| `acl_info/ingress/entries` | **100** | 1024 |
| `acl_info/ingress/counters` | 68 | 1024 |
| `acl_info/ingress/meters` | 18 | 2048 |
| `acl_info/ingress/slices` | 4 | **5** |
| `acl_info/egress/entries` | 36 | 512 |
| `acl_info/egress/counters` | 36 | 1024 |
| `acl_info/egress/meters` | 18 | 512 |
| `acl_info/egress/slices` | 2 | 2 |

**This reveals the Trident+ Field Processor resource pool:**
* Ingress FP: 1024 entries across 5 slices (each slice = 256 wide)
* Egress FP: 512 entries across 2 slices
* 1024 counters + 2048 meters at ingress
* 1024 counters + 512 meters at egress

### `run/route_info/` — DEFIP/host table occupancy (live)

| Path | Live | Max | Notes |
|---|---|---|---|
| `route/count_total` | 26 | 32768 | Total routes programmed |
| `route/count_v4` | 18 | — | IPv4 routes (we set these up) |
| `route/count_v6` | 8 | — | IPv6 routes (linklocal) |
| `route/count_0` | 22 | 16284 | "Bin 0" routes (longer prefixes?) |
| `route/count_1` | 6 | 256 | "Bin 1" routes (shorter prefixes?) |
| `route/mask_limit` | 64 | — | Max prefix length values |
| `host/count` | 4 | 8192 | Total ARP entries programmed |
| `host/count_v4` | 4 | — | IPv4 hosts |
| `host/count_v6` | 0 | — | IPv6 hosts |

**Trident+ has 32K DEFIP routes + 8K L3 hosts.** This matches BCM's published spec.

### `run/stats/`
* `stats/vxlan/all` — VXLAN aggregated stats
* `stats/vlan/all` — VLAN aggregated stats

## `clear/` — Reset actions (4)
* `clear/stats/vlan` — zero VLAN counters
* `clear/stats/vxlan` — zero VXLAN counters

Write "1" → counters zeroed.

## EdgeNOS implications

This FUSE filesystem is the **single best blueprint for EdgeNOS's control surface.**

### Three approaches for EdgeNOS

**Option A: Same FUSE model**
* EdgeNOS daemon links libfuse, mounts `/edgenos/switch/`
* Identical layout to Cumulus's tree
* All Cumulus CLI tools (`cl-acltool`, `cl-bcmcmd`, etc.) work unchanged if we adopt the path names

**Option B: sysfs-like under `/sys/class/edgecore/`**
* Use Linux sysfs class API
* Cleaner but more kernel-side code

**Option C: Keep it simple — config files in `/etc/edgenos/` + signal-based reload**
* Lower-tech but enough for v1

### Recommended structure (mirror Cumulus's design)

```
/edgenos/switch/
├── version
├── config/
│   ├── acl/, arp/, bridge/, buf_util/, coalesce/, route/, stats/,
│   ├── interface/swp{N}/{interface_mode,storm_control/...}
│   ├── netlink/, traffic/, vxlan/
│   ├── logging, resv_vlan_range, ignore_non_swps,
│   └── disable_internal_hw_err_restart
├── ctrl/
│   ├── resync             (global re-sync)
│   ├── acl/resync         (ACL re-program — used by cl-acltool)
│   ├── netlink/resync     (re-read kernel state)
│   ├── hal/resync         (HAL re-sync)
│   ├── logger
│   └── sample/ulog_channel
├── run/
│   ├── acl_info/{ingress,egress}/{counters,entries,meters,slices}{,_total}
│   ├── route_info/route/{count_*,max_*,mask_limit}
│   ├── route_info/host/{count_v4,count_v6,max,count}
│   └── stats/{vlan,vxlan}/all
└── clear/
    └── stats/{vlan,vxlan}
```

### Key things to preserve
1. **`ctrl/*/resync` is write-and-read-back**. Userspace writes "1", then reads back status. Status `"0"` = OK, any other string = error message.
2. **Persistence**: config/ entries persist across switchd restart? They should be reloaded from `/etc/cumulus/switchd.conf` on each start. Need to confirm but the FS-backed view IS volatile (a FUSE).
3. **Reserved VLAN range** (3300-3999) — EdgeNOS must reserve 3301-3352 for its own per-port VLAN scheme (same as Cumulus).
4. **cut_through_enable = TRUE** by default — Cumulus uses cut-through forwarding (lower latency, lower buffer use).

## Files

* `00_fuse_tree.txt`, `01_full_tree.txt` — initial mount inspection
* `02_key_values.txt` — selected interesting values
* `03_all_values.txt` — every config file with its value
* `04_full_state.txt` — non-interface config + ctrl + run + counts

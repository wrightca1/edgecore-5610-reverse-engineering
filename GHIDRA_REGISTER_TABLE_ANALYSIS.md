# Ghidra Register/Table Analysis

**Date**: 2026-02-18  
**Tool**: Ghidra 12.0.3 headless  
**Binary**: switchd (Cumulus Linux 2.5.1)  
**Host**: <USER>@<GHIDRA_HOST_IP> (Fedora, 30GB RAM)  
**Output**: `build-server/switchd/sdk-deep-extract/ghidra-register-table-export.txt`

## Analysis Summary

Ghidra headless analysis extracted register/table-related strings, cross-references, and constant offsets from the switchd binary. This provides insights into:

- Register access patterns (setreg, getreg, soc_reg)
- Table management (L2, L3, ARL, MMU, VLAN)
- Configuration paths and keys
- Hardware abstraction layer (HAL) functions
- Netlink route/neighbor/interface table operations

## Key Statistics

- **Total strings found**: 34,918 register/table-like strings
- **Xrefs analyzed**: 100 (first 100 strings with references)
- **Register constants**: Sample from 500 functions
- **Output file**: 850 lines, 33 KB

## Register/Table Patterns Extracted

### Pattern Categories

The analysis searched for strings matching these patterns:
- Register operations: `setreg`, `soc_reg`, `modreg`, `rcload`, `getreg`
- ASIC components: `CMIC_`, `PORT_`, `L2_`, `L3_`, `ING_`, `EGR_`
- Table types: `FP_`, `VLAN_`, `ARL_`, `MMU_`, `PBMP`, `portmap`
- Debug/access: `rdbgc`, `tdbgc`, `mem_`, `table`, `base_addr`
- SDK prefixes: `bcm_`, `soc_`, `shr_`

### Notable Findings

#### 1. Configuration Paths

```
0x11318f28: /config/arp/drop_during_failed_state
0x11318fb8: /config/route/table
0x11319048: /config/coalesce/offset
0x11319094: /config/resv_vlan_range
```

These match the sysfs-style config paths used by Cumulus switchd.

#### 2. Table Management Strings

**Host Table**:
- `Host table current count`
- `Host table maximum size`
- `Host table current IPv4 count`
- `Host table current IPv6 count`

**Route Table**:
- `Route table current count`
- `Route table maximum size`
- `Route table current IPv4 count`
- `Route table current IPv6 count`
- `Route table short/long IPv6 address split`
- `Route table mode`

**L2 Table**:
- `L2 table current count`
- `L2 table maximum size`

**ECMP Table**:
- `ECMP next-hop table current count`
- `ECMP next-hop table miximum size`
- `ECMP next-hop table maximum next-hops per route`

#### 3. HAL (Hardware Abstraction Layer) Functions

```
0x1131d36c: hal_add_port_cb
0x1131d3a8: sync_port_settings
0x1131d45c: get_route_table_type_idx
0x1131db04: hal_set_route_table_mode
```

#### 4. Hash Table Operations

```
hash_table_add(hal_neighbors, HAL_ROUTE_KEY(entry), HAL_ROUTE_KEYSIZE, entry)
hash_table_delete(hal_routes, HAL_ROUTE_KEY(route), HAL_ROUTE_KEYSIZE, ...)
hash_table_find(hal_routes, HAL_ROUTE_KEY(route), HAL_ROUTE_KEYSIZE, ...)
```

#### 5. Netlink Route Table Operations

```
rtnl_route_set_table
rtnl_route_get_table
rtnl_link_set_ifindex
rtnl_link_get_ifindex
rtnl_neigh_set_ifindex
rtnl_neigh_get_ifindex
```

## Cross-References (Xrefs)

The analysis found 100 cross-references showing where register/table strings are used in code. Examples:

### Config Path Usage

**`/config/arp/drop_during_failed_state`** (0x11318f28):
- Referenced from `FUN_10005ecc` at 0x1000607c
- Used in configuration loading function

**`/config/route/table`** (0x11318fb8):
- Referenced from `FUN_10005ecc` at 0x1000610c
- Route table configuration

**`/config/coalesce/offset`** (0x11319048):
- Referenced from `FUN_10005ecc` at 0x100061c0
- Coalescing configuration

### Table Statistics Usage

**`Host table current count`** (0x1131b1e0):
- Referenced from `FUN_10010a80` at 0x10010ac4
- Function appears to print table statistics

**`Route table current count`** (0x1131b290):
- Referenced from `FUN_10010a80` at 0x10010b44
- Route table statistics reporting

## Register Offset Constants

The script searched for constants in the 0x31xxx-0x35xxx and 0x32xxx-0x33xxx ranges (typical Broadcom register offsets). Results are limited to samples from the first 500 functions to keep analysis time reasonable.

## Function Analysis

### FUN_10005ecc
- Loads multiple configuration paths
- Appears to be a configuration initialization function
- Uses sysfs-style paths (`/config/...`)

### FUN_10010a80
- Prints table statistics
- Accesses host table, route table, L2 table metrics
- Likely used for `switchdctl` or status reporting

### FUN_1000b638
- Handles route table mode warnings
- Error handling for unsupported table modes

## Implications for Custom NOS

### 1. Table Management
- switchd maintains separate tables for hosts, routes, L2, ECMP
- Tables have current/maximum size tracking
- IPv4/IPv6 counts tracked separately

### 2. Configuration System
- Uses sysfs-style paths (`/config/route/table`, etc.)
- Configuration loaded early in initialization
- Paths match what we see in `/sys/class/netlink/` on live switch

### 3. HAL Abstraction
- Hardware abstraction layer functions (`hal_*`)
- Hash table management for routes/neighbors
- Port callback system (`hal_add_port_cb`)

### 4. Netlink Integration
- Extensive use of `rtnl_*` functions for route/neighbor/interface management
- Table IDs tracked and synchronized with kernel

## Files

- **Full output**: `build-server/switchd/sdk-deep-extract/ghidra-register-table-export.txt`
- **Script**: `scripts/reverse-engineering/ExtractRegisterAndTableInfo.java`
- **Analysis host**: `<USER>@<GHIDRA_HOST_IP>:/home/<USER>/analysis/`

## Cross-References to Other Analysis

### SDK API Analysis
- **[sdk-api-list.md](sdk-api-list.md)** - 2,864 `bcm_*` API symbols extracted via strings analysis. The Ghidra analysis found register/table patterns that complement the API list by showing how these APIs are used internally (e.g., `hash_table_add(hal_routes, ...)` suggests internal route table management).

### Netlink Integration
- **[netlink-handlers.md](netlink-handlers.md)** - Documents `rtnl_*` functions used for kernel synchronization. Ghidra found: `rtnl_route_set_table`, `rtnl_route_get_table`, `rtnl_link_set_ifindex`, `rtnl_neigh_set_ifindex` - these match the netlink handler implementation patterns.

### Initialization Sequence
- **[initialization-sequence.md](initialization-sequence.md)** - Documents switchd startup flow. Ghidra found config paths (`/config/route/table`, `/config/arp/drop_during_failed_state`) that are loaded during Phase 2 (Config Load) and used throughout runtime.

### Register Configuration
- **[config-to-register-map.md](config-to-register-map.md)** - Maps config parameters to register writes. Ghidra found register access patterns (`setreg`, `getreg`, `soc_reg`, `rcload`) and debug counter registers (`rdbgc`, `tdbgc`) that match the `setreg` commands in rc.soc.

### ASIC Initialization
- **[asic-init-sequence.md](asic-init-sequence.md)** - Documents rc.soc register writes. Ghidra found `rdbgc*_select` and `tdbgc*_select` strings matching the drop counter register configuration (e.g., `rdbgc0_select`, `rdbgc3_select`, `tdbgc6_select`).

### API Usage Patterns
- **[api-patterns.md](api-patterns.md)** - Documents `bcm_*` API call patterns. Ghidra's HAL function findings (`hal_add_port_cb`, `sync_port_settings`) show the abstraction layer between netlink handlers and SDK APIs.

### Configuration Format
- **[bcm-config-format.md](bcm-config-format.md)** - Documents `.bcm` file format. Ghidra found config paths (`/config/route/table`, `/config/coalesce/offset`) that may correspond to sysfs-style config nodes or internal config keys.

### Table Management
- **[WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md)** - Checklist of required components. Ghidra's table management findings (Host table, Route table, L2 table, ECMP table) directly support Section 2.4 (Table Programming) requirements.

## Related Documents

- [switchd-binary-analysis.md](switchd-binary-analysis.md) - General binary analysis approach
- [WHAT_MAKES_THE_SWITCH_WORK.md](WHAT_MAKES_THE_SWITCH_WORK.md) - Required components checklist
- [sdk-api-list.md](sdk-api-list.md) - SDK API symbols extracted via strings

## Integration with Overall RE Effort

This Ghidra analysis complements other reverse engineering work:

1. **Strings Analysis** (`sdk-api-list.md`): Extracted 2,864 `bcm_*` API symbols. Ghidra adds internal function patterns (HAL, hash tables) showing how APIs are used.

2. **Dynamic Analysis** (`switchd-init-trace.md`): Captured file access and syscall patterns. Ghidra's config path findings (`/config/route/table`, etc.) match the config loading sequence seen in traces.

3. **Netlink Analysis** (`netlink-handlers.md`, `netlink-message-flow.md`): Documented kernel→ASIC synchronization. Ghidra found `rtnl_*` functions confirming the netlink handler implementation.

4. **Config Analysis** (`bcm-config-format.md`, `config-to-register-map.md`): Documented `.bcm` format and register mappings. Ghidra's register access patterns (`setreg`, `rdbgc`, `tdbgc`) match rc.soc commands.

5. **Initialization** (`initialization-sequence.md`, `asic-init-sequence.md`): Documented startup flow. Ghidra's `FUN_10005ecc` config loading function aligns with Phase 2 (Config Load).

6. **API Patterns** (`api-patterns.md`): Documented SDK call sequences. Ghidra's HAL functions show the abstraction layer between netlink handlers and SDK APIs.

Together, these analyses provide a complete picture: from high-level architecture down to register-level implementation details.

## Notes

- Analysis optimized to process first 500 functions (was taking 12+ hours, now completes in minutes)
- Xref analysis limited to first 100 strings with references
- Register constant search samples from functions (not exhaustive)
- Full string list available in output file (34,918 matches)

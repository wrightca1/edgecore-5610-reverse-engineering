# Trace run summary — 10.1.1.233

**Date**: 2026-02-19

## Setup

- **Switch**: 10.1.1.233 (Cumulus), user `cumulus`
- **Config**: **swp1** 10.101.101.1/29, **swp2** 10.101.101.10/29 (different networks, no bridge). ECMP via 10.101.101.2 (swp1) and 10.101.101.9 (swp2).
- **OSPF**: Enabled on swp1 (10.101.101.0/29 area 0) and swp2 (10.101.101.8/29 area 0), point-to-point, router-id 10.101.101.1.

Applied with:
- `./scripts/reverse-engineering/configure-switch-101-ecmp.sh`
- `./scripts/reverse-engineering/run-configure-ospf-101-10.1.1.233.sh`

## Traces run

### 1. Route/ECMP strace (L3 + ECMP API activity)

- **Script**: `run-route-ecmp-strace-10.1.1.233.sh` → runs `trace-route-ecmp-strace-on-switch.sh` on switch
- **Trigger**: ECMP route add/delete: `10.200.1.0/24 nexthop via 10.101.101.2 dev swp1 nexthop via 10.101.101.9 dev swp2`, single-hop routes, then deletes
- **Output**: 
  - `docs/reverse-engineering/traces/route-ecmp-strace-10.1.1.233.log` (7,246 lines in latest run)
  - `docs/reverse-engineering/traces/route-ecmp-strace-summary-10.1.1.233.txt`
- **Content**: switchd `ioctl(14, 0x20004c09)` / `0x20004c0a` (BDE), `mmap` during route/ECMP programming

### 2. OSPF strace

- **Script**: `run-ospf-strace-10.1.1.233.sh` → runs `trace-ospf-strace-on-switch.sh` on switch
- **Trigger**: `vtysh -c "clear ip ospf neighbor"` (re-adjacency and FIB refresh while tracing switchd)
- **Output**:
  - `docs/reverse-engineering/traces/ospf-strace-10.1.1.233.log` (17,044 lines in run)
  - `docs/reverse-engineering/traces/ospf-strace-summary-10.1.1.233.txt`
- **Content**: switchd BDE ioctl (0x20004c09, 0x20004c0a), mmap, write during OSPF-driven FIB updates

### 3. Port-up strace (swp2)

- **Script**: `run-port-up-trace-10.1.1.233.sh swp2`
- **Trigger**: `ip link set swp2 down` then `up`
- **Output**:
  - `docs/reverse-engineering/traces/port-up-trace-10.1.1.233.log` (12,295 lines)
  - `docs/reverse-engineering/traces/port-up-summary-10.1.1.233.txt`

### 4. API-to-table-ID (GDB) trace

- **Script**: `run-api-to-table-id-trace-10.1.1.233.sh`
- **Status**: Script updated (correct switchd PID 19036, base 0x10000000). **GDB is not installed on the switch**, so breakpoint-based trace was not run. Strace-based route/ECMP trace used instead.

## Notes

- **switchd PID**: Resolved via `/proc/$p/exe` → `/usr/sbin/switchd` (avoids matching strace/timeout wrappers).
- **GDB**: Install `gdb` on the switch to run API/dispatcher breakpoint traces and capture table IDs from registers.
- **ECMP trigger**: `trigger-api-calls-on-switch.sh` uses `GW=10.101.101.9` for ECMP and single-hop routes.

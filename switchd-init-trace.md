# switchd Initialization Trace

**Source**: Actual trace from Cumulus Linux 2.5.1 on AS5610-52X (<LIVE_SWITCH_IP>)
**Date**: 2013-11-01 (clock set back for license)
**Trace file**: `/tmp/switchd-init.trace` (51MB, 680k lines)

## System Information

- **Kernel**: 3.2.60-1+deb7u1+cl2.5+1 (Debian 7 Wheezy)
- **IRQ**: 16 (confirmed - matches reverse engineering findings)
- **Interrupts**: 83,333+ on IRQ 16 (hardware interrupts working)
- **PCI Device**: 0000:01:00.0 (BCM56846)

## File Access Sequence (from trace)

### 1. License Check
```
open("/etc/cumulus/.license.txt", O_RDONLY|O_LARGEFILE) = 4
```

### 2. Configuration Files
```
open("/etc/cumulus/switchd.conf", O_RDONLY|O_LARGEFILE) = 3
open("/var/log/switchd.log", O_WRONLY|O_CREAT|O_APPEND|O_LARGEFILE, 0666) = 3
open("/etc/bcm.d/config.bcm", O_RDONLY) = -1 ENOENT (tries, not found)
open("/etc/bcm.d/rc.soc", O_RDONLY) = 17
open("/etc/bcm.d/rc.ports_0", O_RDONLY) = -1 ENOENT (tries, may be in platform dir)
```

### 3. BDE Device
```
open("/dev/linux-user-bde", O_RDWR|O_SYNC|0x100000) = 14
```

### 4. Netlink Sockets
Multiple netlink sockets created:
```
socket(PF_NETLINK, SOCK_RAW|SOCK_CLOEXEC, 0) = 6
bind(6, {sa_family=AF_NETLINK, pid=6568, groups=00000000}, 12) = 0
socket(PF_NETLINK, SOCK_RAW|SOCK_CLOEXEC, 16) = 7
bind(7, {sa_family=AF_NETLINK, pid=4200872, groups=00000000}, 12) = 0
...
```

### 5. Control Socket
```
bind(16, {sa_family=AF_FILE, path="/var/run/switchd.socket"}, 25) = 0
```

## IOCTL Sequence (BDE Operations)

From trace summary - many ioctl calls to fd 14 (/dev/linux-user-bde):
- `0x20004c05`, `0x20004c01`, `0x20004c0c`, `0x20004c02`, `0x20004c1a`, `0x20004c0a`, `0x20004c0b`, `0x20004c09`

These are BDE ioctl commands for device initialization, register access, DMA setup.

## switchd Log Output

From `/var/log/switchd.log`:
- Port mapping: swp1-48 (10G), swp49-52 (40G)
- SFP table entries loaded
- Routes synced: 6 IPv4/IPv6 routes added
- Neighbors synced: 2 added
- **Startup complete** at 12:09:10

## Key Findings

1. **IRQ 16 confirmed** - Hardware interrupts working (83k+ interrupts)
2. **License validation** - File opened early in init
3. **Config loading** - rc.soc loaded, rc.ports_0 may be platform-specific
4. **BDE device** - Opened with O_RDWR|O_SYNC flags
5. **Netlink** - Multiple sockets created (different groups/processes)
6. **Init time** - ~12 seconds from start to "Startup complete"

## Full Trace

To analyze full trace:
```bash
scp <SWITCH_USER>@<LIVE_SWITCH_IP>:/tmp/switchd-init.trace .
# Analyze with: grep, awk, or import into analysis tool
```

## References

- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md)
- [file-access-pattern.md](file-access-pattern.md)
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra found config paths (`/config/route/table`, `/config/arp/drop_during_failed_state`) that match the config file access patterns seen in this trace

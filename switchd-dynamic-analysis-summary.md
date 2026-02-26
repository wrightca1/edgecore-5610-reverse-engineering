# switchd Dynamic Analysis Summary

**Switch**: AS5610-52X at <LIVE_SWITCH_IP>
**Date**: 2013-11-01 (clock set back for license)
**Status**: switchd running successfully

## Setup Completed

1. **License loaded**: `/etc/cumulus/.license.txt` copied and verified
2. **Clock set**: Date set to 2013-11-01 12:00:00 UTC (license expires 2013-11-27)
3. **switchd started**: Running as PID 8351, daemon mode

## Verification Results

### IRQ Assignment
- **IRQ**: 16 (confirmed - matches reverse engineering)
- **Interrupt count**: 83,333+ (hardware interrupts working)
- **PCI device**: 0000:01:00.0 → IRQ 16

### switchd Status
- **Process**: Running (`/usr/sbin/switchd -d`)
- **Log**: `/var/log/switchd.log` - shows successful initialization
- **Ready flag**: `/var/run/switchd.ready` (created after init)
- **Control socket**: `/var/run/switchd.socket` (for bcmsh)

### Port Status
- **Interfaces**: swp1-52 exist (swp1-48 10G, swp49-52 40G)
- **State**: DOWN initially (can be brought up)
- **MAC addresses**: Assigned (e.g., swp1: 80:a2:35:81:ca:af)

### Initialization Log
From `/var/log/switchd.log`:
- Port structures created for all 52 ports
- SFP table entries loaded
- Routes synced: 6 IPv4/IPv6 routes
- Neighbors synced: 2 added
- **Startup complete** message at 12:09:10

## Trace Files Captured

1. **switchd-init.trace** (51MB, 680k lines)
   - Full strace of initialization
   - File opens, sockets, ioctls, mmaps
   - Location: `/tmp/switchd-init.trace` on switch

2. **switchd-summary.txt**
   - Summary of trace (files, sockets, ioctls)
   - Location: `docs/reverse-engineering/switchd-summary.txt`

## Key Observations

### File Access Pattern
- License checked early: `/etc/cumulus/.license.txt`
- Config loaded: `/etc/cumulus/switchd.conf`, `/etc/bcm.d/rc.soc`
- BDE device: `/dev/linux-user-bde` opened with O_RDWR|O_SYNC
- Log file: `/var/log/switchd.log` created/opened

### Netlink Setup
- Multiple netlink sockets created (different groups)
- Socket 6: NETLINK_ROUTE (protocol 0)
- Socket 7-13: Various NETLINK sockets (protocol 16)
- Control socket: `/var/run/switchd.socket` (AF_FILE)

### BDE Operations
- Many ioctl calls to `/dev/linux-user-bde` (fd 14)
- Commands: 0x20004c05, 0x20004c01, 0x20004c0c, etc.
- These are BDE device initialization and register access

## Next Steps

1. **Analyze full trace** - Extract complete file access sequence
2. **Monitor netlink** - Capture route/link/neighbor changes
3. **Compare with docs** - Verify against reverse engineering findings
4. **Test operations** - Bring up ports, add routes, verify ASIC programming

## References

- [switchd-init-trace.md](switchd-init-trace.md) - Detailed trace analysis
- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Static analysis complements dynamic trace: Ghidra found config paths and table management functions that match the initialization sequence seen in traces
- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md)
- [file-access-pattern.md](file-access-pattern.md)

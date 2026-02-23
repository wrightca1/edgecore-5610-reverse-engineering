# switchd File Access Pattern

**Purpose**: Document files accessed during switchd initialization
**Source**: Expected from strace trace (run trace-switchd-init.sh on switch)

## Expected File Access Sequence

### 1. License Check
- `/etc/cumulus/.license.txt` - License validation

### 2. Configuration Files
- `/etc/cumulus/switchd.conf` - switchd daemon config
- `/etc/bcm.d/config.d/01config.bcm` - Platform BCM config
- `/usr/share/cumulus/__chip_config/bcm/Trident/sdk.bcm` - Chip defaults
- `/etc/bcm.d/rc.soc` - SOC initialization script
- `/etc/bcm.d/rc.ports_0` - Port mapping (via rcload)
- `/etc/bcm.d/rc.led` - LED config (via rcload)
- `/var/lib/cumulus/rc.datapath_0` - Datapath config (via rcload)

### 3. Device Files
- `/dev/linux-user-bde` - BDE user-space device (open, ioctl, mmap)
- `/dev/linux-kernel-bde` - BDE kernel device (check exists)

### 4. Runtime Files
- `/var/run/switchd.pid` - PID file
- `/var/run/switchd.ready` - Ready flag
- `/var/run/switchd.socket` - Control socket (for bcmsh)

### 5. Log Files
- `/var/log/switchd.log` - Log output

## File Access Pattern (from architecture)

1. **Startup**: License, configs
2. **Init**: BDE device open, mmap ASIC registers
3. **Config**: Load .bcm, execute rc.soc
4. **Runtime**: PID file, ready flag, socket
5. **Main loop**: No file I/O (netlink only)

## Capturing Pattern

Run on switch:
```bash
/etc/init.d/switchd stop
strace -e trace=open,openat -o switchd-files.trace /usr/sbin/switchd -d
```

Parse trace:
```bash
grep -E 'open|openat' switchd-files.trace | grep -v ENOENT
```

## References

- [switchd-init-trace.md](switchd-init-trace.md)
- [initialization-sequence.md](initialization-sequence.md)

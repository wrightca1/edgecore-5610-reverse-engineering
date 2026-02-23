# Interface Creation Analysis: How Cumulus Creates swp Interfaces

**Date**: 2026-02-17
**Finding**: swp interfaces are **virtual network devices** created before switchd starts

## Key Discovery

swp interfaces are **virtual netdevs** (`/devices/virtual/net/swp1`), not physical driver interfaces.

### Evidence

```bash
# On Cumulus switch:
$ ls -la /sys/class/net/ | grep swp
lrwxrwxrwx swp1 -> ../../devices/virtual/net/swp1
lrwxrwxrwx swp2 -> ../../devices/virtual/net/swp2
...
```

**Virtual netdevs** are created via Linux kernel APIs, not hardware drivers.

## Interface Creation Timeline

### Before switchd Starts

1. **Platform initialization** (likely in `/etc/init.d/switchd` or platform scripts)
2. **Interfaces created** via kernel API (rtnl_link_alloc/register)
3. **porttab file generated** (`/var/lib/cumulus/porttab`)
4. **switchd starts** and reads porttab

### switchd Log Shows

```
hal_bcm_port.c:56 porttab entry, linux:swp1 sdk:xe0
hal_bcm_port.c:56 porttab entry, linux:swp2 sdk:xe1
...
```

This indicates interfaces **already exist** when switchd starts - switchd just maps them to BCM ports.

## porttab File

**Location**: `/var/lib/cumulus/porttab`

**Format** (from porttab.py):
```
linux_intf bcm unit is_fabric
swp1 xe0 0 0
swp2 xe1 0 0
...
```

**Purpose**: Maps Linux interface names (swp1-52) to BCM SDK port names (xe0-xe51).

## How Virtual Interfaces Are Created

### Linux Kernel API

Virtual netdevs are created using:
- `rtnl_link_alloc()` - Allocate netlink link structure
- `rtnl_link_alloc_cache()` - Get existing links
- `rtnl_link_register()` - Register new link with kernel
- Or via `ip link add` command (which uses netlink internally)

### Possible Mechanisms

1. **Platform-specific kernel module** - Creates interfaces during module load
2. **Platform initialization script** - Uses `ip link add` or netlink API
3. **SDK initialization** - SDK creates interfaces via BDE/kernel API
4. **udev rules** - Creates interfaces based on hardware detection

## Investigation Needed

### 1. Check Platform Scripts

```bash
# Check switchd init script
cat /etc/init.d/switchd

# Check platform-specific scripts
ls -la /usr/share/cumulus/accton_as5610_52x/
```

### 2. Check Kernel Modules

```bash
# Look for platform-specific modules
lsmod | grep -E 'accton|as5610|switch|port'

# Check module parameters
modinfo <module_name>
```

### 3. Check udev Rules

```bash
# Look for interface creation rules
grep -r 'swp\|interface' /etc/udev/rules.d/
```

### 4. Check SDK Initialization

The SDK might create interfaces during `bcm_attach()` or `bcm_init()` via:
- BDE kernel module creating netdevs
- SDK calling kernel netlink API
- Platform-specific SDK hooks

## Implications for Open-Source Implementation

### Cannot Use KNET

- `opennsl_knet_netif_create()` won't work (KNET not used)
- Must create virtual interfaces manually

### Options

1. **Create interfaces before switchd starts**
   - switchd creates swp1-52 via TUN (/dev/net/tun + TUNSETIFF)
   - Or via netlink API in C code
   - switchd then maps them to BCM ports

2. **SDK creates interfaces**
   - Investigate if OpenNSL SDK can create virtual interfaces
   - Check SDK initialization hooks

3. **Platform kernel module**
   - Create kernel module that registers swp1-52 netdevs
   - Similar to how some platforms create management interfaces

## Recommended Approach

### Phase 1: Create Interfaces Manually

Create a platform initialization script that creates swp1-52:

```bash
#!/bin/bash
# Create swp interfaces
for i in {1..52}; do
    # TUN: open /dev/net/tun, TUNSETIFF "swp$i"
done
```

### Phase 2: Integrate with switchd

- switchd reads porttab (or generates it from config)
- Maps swpX to BCM ports
- Uses existing port_mapper component

### Phase 3: Investigate SDK Integration

- Check if SDK can create interfaces
- May need custom netdev ops for packet I/O
- Investigate BDE interface creation APIs

## References

- [porttab.py analysis](porttab.py) - Python module for porttab parsing
- [switchd init script](switchd-init-trace.md) - switchd initialization sequence
- [NO_KNET_ARCHITECTURE.md](../NO_KNET_ARCHITECTURE.md) - Architecture differences

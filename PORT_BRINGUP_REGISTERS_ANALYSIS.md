# Port Bringup Registers Analysis (Path B 5.2-5.3)

**Date**: 2026-02-19  
**Status**: PENDING  
**Goal**: Minimal register sequence to bring one port up (enable, speed, duplex) and SerDes lane config

---

## Current Understanding

### Register Access Mechanism

**From BDE_MMAP_ANALYSIS**:
- switchd mmaps `/dev/mem` at:
  - `0x04000000` (64MB) - Main register space
  - `0xa0000000` (256KB) - Secondary register space
- Register access is **direct mmap read/write**, not ioctl
- Port-up trace shows only synchronization ioctls (USLEEP, WAIT_FOR_INTERRUPT, SEM_OP, UDELAY)

### Port-Up Trace Findings

**From PORT_UP_TRACE_ANALYSIS**:
- BDE ioctls observed: LUBDE_USLEEP, LUBDE_WAIT_FOR_INTERRUPT, LUBDE_SEM_OP, LUBDE_UDELAY
- No CPU_READ_REG/CPU_WRITE_REG ioctls (registers via mmap)
- Register reads/writes happen in mmap'd memory (not visible in strace)

---

## Approach

### Option 1: Enhanced Port-Up Trace

**Enhance trace script** to capture mmap memory access:
- Use `perf record` to trace memory accesses in mmap regions
- Or use `strace -e trace=pread64,pwrite64` to catch explicit mmap reads/writes
- Filter for addresses in `0x04000000-0x0403ffff` and `0xa0000000-0xa003ffff` ranges

**Limitation**: Direct mmap access doesn't show as syscalls - would need memory tracing tools.

### Option 2: Ghidra Analysis

**Find port initialization functions**:
1. Search for `opennsl_port_enable_set`, `opennsl_port_speed_set` symbols
2. Trace call chain to register write functions
3. Identify register offsets used for port enable/speed/SerDes

**Functions to search for**:
- `opennsl_port_enable_set` - Port enable/disable
- `opennsl_port_speed_set` - Port speed configuration
- `opennsl_port_info_set` - Port information/configuration
- SerDes initialization functions (search for "serdes", "phy", "lane")

### Option 3: Register Map Analysis

**From SDK_REGISTER_MAP.md**:
- CMIC base: `0x08000000` (BCM_ICS_CMIC_BASE)
- Port registers likely in `0x04000000` range (mmap'd region)
- SerDes registers per port/lane

**Search for**:
- Port control registers (PORT_ENABLEr, PORT_SPEEDr, etc.)
- SerDes lane configuration registers
- PHY control registers

---

## Port Bringup Sequence (Expected)

Based on OpenNSL documentation and Broadcom SDK patterns:

1. **SerDes Configuration**:
   - Configure SerDes lanes for port
   - Set SerDes speed (10G, 25G, 40G, 100G)
   - Enable SerDes PLLs and clocks

2. **PHY Initialization**:
   - Reset PHY
   - Configure PHY mode (SFP, QSFP)
   - Enable auto-negotiation or force mode

3. **MAC Configuration**:
   - Enable MAC TX/RX
   - Set MAC speed/duplex
   - Configure flow control

4. **Port Enable**:
   - Set PORT_ENABLE register bit
   - Wait for link up interrupt
   - Verify link status

---

## Next Steps

1. **Search Ghidra for port functions**:
   - Find `opennsl_port_enable_set` or equivalent
   - Trace to register write functions
   - Identify register offsets

2. **Enhanced trace** (if needed):
   - Use `perf` or memory tracing to capture mmap accesses
   - Correlate with port-up events

3. **Register map lookup**:
   - Search for PORT_* register definitions
   - Map to actual register offsets in `0x04000000` range

4. **Document minimal sequence**:
   - List register addresses and values
   - Order of operations
   - Timing/delays required

---

## References

- **Port-up trace**: [PORT_UP_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/PORT_UP_TRACE_ANALYSIS_<LIVE_SWITCH_IP>.md)
- **BDE mmap**: [BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md)
- **Register map**: [SDK_REGISTER_MAP.md](SDK_REGISTER_MAP.md)
- **OpenNSL port APIs**: [OPENNSL_DOCUMENTATION_SUMMARY.md](../OPENNSL_DOCUMENTATION_SUMMARY.md)

# switchd Binary Analysis

**Target**: Cumulus Linux 2.5.1 switchd
**Binary**: `cumulus/extracted/switchd/switchd`
**Date**: 2026-02-15

## Binary Information

```
File: ELF 32-bit MSB executable, PowerPC or cisco 4500
Version: 1 (SYSV)
Dynamically linked, interpreter /lib/ld.so.1
Target: GNU/Linux 2.6.26
Stripped: Yes (no debug symbols)
```

## Static Analysis Setup

### Tools Required

1. **Ghidra** (recommended - free, PowerPC support)
   - Download: https://ghidra-sre.org/
   - Load switchd binary: File > Import File
   - Auto-analyze when prompted
   - Processor: PowerPC (BE 32-bit)

2. **Command-line tools** (cross-platform analysis)
   - `strings` - Extract printable strings
   - `readelf` - ELF structure (use powerpc-linux-gnu-readelf or objdump)
   - `objdump` - Disassembly (powerpc-linux-gnu-objdump -d)
   - `file` - File type identification

3. **On PowerPC/Linux** (for dynamic analysis)
   - `strace` - System call tracing
   - `ltrace` - Library call tracing
   - `ldd` - Shared library dependencies

### Loading in Ghidra

1. Create new project: File > New Project > Non-Shared Project
2. Import: File > Import File > select `cumulus/extracted/switchd/switchd`
3. Double-click to open in CodeBrowser
4. Analyze when prompted: Analysis > Auto Analyze
5. Search for SDK APIs: Search > For Strings > filter by "bcm_"
6. Search for config paths: "rc.soc", "rc.ports", "/etc/bcm.d"
7. Search for netlink: "NETLINK", "RTM_", "nl_"

### Key Areas to Analyze

| Area | Search Strings | Purpose |
|------|----------------|---------|
| Entry/Main | `_start`, `main` | Startup flow |
| SDK Init | `bcm_attach`, `bcm_init` | ASIC initialization |
| Config Load | `rc.soc`, `01config`, `/etc/bcm.d` | Config parsing |
| Netlink | `RTM_NEWROUTE`, `RTM_NEWLINK`, `RTM_NEWNEIGH` | Kernel sync |
| Port Map | `portmap_`, `swp` | Port configuration |

## Initialization Flow (from dynamic analysis)

From Cumulus system dumps and switchd logs:

1. **License check** - `/etc/cumulus/.license.txt`
2. **BDE device open** - `/dev/linux-user-bde`
3. **SDK attach** - `bcm_attach()` with device 0xb846 (BCM56846)
4. **Config load** - `/etc/bcm.d/*.bcm`, `rc.soc`
5. **SOC init** - Execute rc.soc script (attach, init, rcload)
6. **Port config** - rc.ports_0, rc.datapath_0
7. **Netlink bind** - NETLINK_ROUTE socket
8. **Ready** - Create `/var/run/switchd.ready`

## Function Call Graph (to document)

Use Ghidra's Function Graph or References to trace:

- main() -> init functions
- Netlink recv loop -> message type dispatch
- RTM_NEWROUTE -> bcm_l3_route_add
- RTM_NEWNEIGH -> bcm_l2_addr_add
- RTM_NEWLINK -> bcm_port_enable_set

## Ghidra Headless Analysis

Automated analysis using Ghidra headless on analysis host (`<USER>@10.1.1.30`):

**Results**: [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md)

- Extracted 34,918 register/table-related strings
- Cross-references showing usage locations
- Register offset constants (0x31xxx-0x35xxx ranges)
- Table management patterns (L2, L3, ARL, MMU, VLAN)
- HAL function identification

**Output**: `build-server/switchd/sdk-deep-extract/ghidra-register-table-export.txt`

**Run**: `./scripts/reverse-engineering/run-ghidra-on-build-server.sh`

## References

- [GHIDRA_REGISTER_TABLE_ANALYSIS.md](GHIDRA_REGISTER_TABLE_ANALYSIS.md) - Ghidra headless analysis results
- [sdk-api-mapping.md](sdk-api-mapping.md) - Full bcm_* API list
- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md)
- [BROADCOM_CUMULUS_ARCHITECTURE.md](../../BROADCOM_CUMULUS_ARCHITECTURE.md)

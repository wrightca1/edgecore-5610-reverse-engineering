# Cumulus switchd vs libopennsl — Architecture and API Comparison

**Date**: 2026-02-21
**Status**: CONFIRMED — Cumulus does NOT use libopennsl; uses statically-linked Broadcom SDK (bcm_* API)
**Sources**: [traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md](traces/BDE_MMAP_ANALYSIS_<LIVE_SWITCH_IP>.md), [build-server/switchd/sdk-deep-extract/strings-register-table.txt](../../build-server/switchd/sdk-deep-extract/strings-register-table.txt), [build-server/switchd/sdk-deep-extract/switchd-schan-data-refs.txt](../../build-server/switchd/sdk-deep-extract/switchd-schan-data-refs.txt)

---

## 1. Architecture Overview

### 1.1 Two separate binaries, same underlying Broadcom SDK

| Binary | API prefix | Linking | Users |
|--------|-----------|---------|-------|
| **switchd** (Cumulus) | `bcm_*` | Broadcom SDK **statically linked** | Cumulus Linux NOS |
| **libopennsl.so.1** | `opennsl_*` | OpenNSL wrapper (GPL SDK extract) | OpenNSL users |

Cumulus switchd does **NOT** use libopennsl. The `bcm_*` API is the Broadcom proprietary SDK
API; `opennsl_*` is the identical API re-exported by the OpenNSL project under a different prefix.

### 1.2 API name mapping (one-to-one)

| Broadcom SDK (`bcm_*`) | OpenNSL (`opennsl_*`) | Notes |
|------------------------|----------------------|-------|
| `bcm_l2_addr_add` | `opennsl_l2_addr_add` | Identical functionality |
| `bcm_l3_route_add` | `opennsl_l3_route_add` | Identical |
| `bcm_l3_egress_create` | `opennsl_l3_egress_create` | Identical |
| `bcm_port_enable_set` | `opennsl_port_enable_set` | Identical |
| `bcm_port_speed_set` | `opennsl_port_speed_set` | Identical |
| `bcm_l3_ecmp_create` | `opennsl_l3_egress_multipath_max_create` | Minor naming diff |
| `bcm_vlan_translate_*` | `opennsl_vlan_translate_*` | Identical |

**Consequence for reverse engineering**: Function internals, table IDs, buffer layouts, dispatch
chains, and register access patterns discovered in libopennsl apply directly to switchd. The SDK
code is functionally identical — only the shared-library boundary differs.

---

## 2. Evidence: Cumulus Uses `bcm_*` API Directly

From `build-server/switchd/sdk-deep-extract/strings-register-table.txt` (string literals embedded in switchd binary):

```
bcm_l3_route_add failed
bcm_l3_host_add failed
bcm_l2_addr_add failed
bcm_l3_egress_create failed
bcm_l3_egress_multipath_max_create failed
bcm_port_enable_set failed
bcm_port_speed_set ... (via bcm_port_control_set)
bcm_vlan_translate_delete
bcm_l2_traverse failed
```

These error strings are from **switchd source code** referencing `bcm_*` directly. There is no
mention of `opennsl_*` or `dlopen("libopennsl")` anywhere in the binary.

---

## 3. Evidence: switchd Has S-Channel Code Directly

`switchd-schan-data-refs.txt` shows **49+ instructions** using the S-Channel 0x2800 pattern in
multiple switchd functions (FUN_10325fa0, FUN_103260d4, FUN_103273a4, FUN_1038a488, etc.).

By contrast, `libopennsl-schan-usage.txt` shows **0 direct references** to 0x32800 in libopennsl.

### Interpretation

- **switchd**: Has the full Broadcom SDK SDRV (socket driver) and CMICM register access layer
  statically linked. S-Channel writes go directly to the mmap'd BAR0+0x32800 within the process.
- **libopennsl**: S-Channel command words are built (FUN_00703dc0 uses `oris 0x2800`) but
  submitted via the Linux BDE kernel module, not by direct /dev/mem access from the library itself.

This reflects the different deployment modes:
- switchd mmaps `/dev/mem` at 0x04000000 and accesses hardware directly
- An external application using libopennsl would go through the kernel BDE ioctl interface for
  hardware access (though on this platform switchd itself does the mmap)

---

## 4. switchd Binary Layout

From `readelf -S switchd`:

| Section | VMA | Size | Notes |
|---------|-----|------|-------|
| `.text` | `0x10004dd0` | ~19MB | Code — addresses 0x10xxxxxx to 0x11xxxxxx |
| `.rodata` | `0x113183c8` | ~5MB | String literals, tables |
| `.data` | `0x118196e8` | ~6MB | Writable data |

The Broadcom SDK occupies the majority of the `.text` section (estimated ~15MB of the 19MB).
Functions are at addresses 0x10xxxxxx–0x11xxxxxx, vs libopennsl addresses 0x00xxxxxx–0x01xxxxxx.

---

## 5. Register Constants in switchd

From `build-server/switchd/sdk-deep-extract/ghidra-register-constants.txt`:

| Constant | Address | Likely meaning |
|----------|---------|---------------|
| `0x21000` | DATA@1183c5f0 | CMICM_CMC_BASE (0x31000 shifted? Or SerDes?) |
| `0x21400` | DATA@1183c5fc | Adjacent to 0x21000 block |
| `0x21800` | DATA@1183c5f8 | Third in triplet |
| `0x1000ccc` | DATA@11324cd2 | Table memory address: L2/L3 table? |
| `0x1005e00` | DATA@11328650 | Table memory address (0x01xxxxxx range) |
| `0x180c200` | DATA@11324cc6 | Table memory high-range (0x0180xxxx) |
| `0x2625a`, `0x275e2`, `0x2dc6c` | 3× each | In triplets — likely SerDes/PHY register indices |
| `0x267ac`, `0x26ce4`, `0x29fcc`, `0x2cb6c`, `0x2dc6c`, `0x3061c`, `0x331d4` | — | Possible table addresses or register maps |

**Note on 0x1005e00 / 0x180c200**: These are in the `0x01xxxxxx` range matching the on-chip
SRAM table-memory range for BCM56846. `0x01005e00` could be L2_USER_ENTRY table base,
`0x0180c200` near L3_DEFIP. Needs cross-reference with Ghidra code using these constants.

---

## 6. Cross-Validation Strategy

Because the `bcm_*` and `opennsl_*` APIs are functionally identical:

1. **Reverse-engineer libopennsl** (simpler: 49MB shared library, no OS-layer code)
2. **Verify** by searching switchd for the same patterns:
   - Same table IDs (e.g. `0x1547` for L2_USER_ENTRY)
   - Same format constants (e.g. `0xa9e2`, `0x95d6`, `0x5740`)
   - Same memory addresses (`0x1005e00`, `0x180c200`)
3. **Runtime traces** on switchd (GDB, strace) capture the actual `bcm_*` calls and hardware
   writes — providing ground-truth that validates the libopennsl static analysis

Our open-source implementation mimics what switchd does at the hardware level. The libopennsl
analysis gives us the data structures and register sequences; switchd traces give us the exact
values written during real traffic.

---

## 7. What This Means for Implementation

To replace Cumulus switchd functionality with an open-source implementation:
- We do NOT need to call libopennsl (it is an OpenNSL wrapper, not what Cumulus uses)
- We DO need to replicate what switchd's embedded SDK does at the hardware level
- The table IDs, buffer layouts, and register sequences from the libopennsl analysis are directly
  applicable — the hardware API is the same
- Our implementation can use either:
  - The OpenNSL API (libopennsl) as a call-compatible wrapper for the hardware
  - Or drive the hardware directly using the register/table sequences we've reverse-engineered

---

## References

- [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md)
- [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) — S-Channel command word format
- [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md) — CMICM register map
- [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md)
- [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md)
- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md)

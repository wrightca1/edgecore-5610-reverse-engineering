# Gemini Reverse Engineering Gaps & Roadmap

**Date**: 2026-02-25  
**Author**: Gemini CLI  
**Objective**: Identify missing technical details required for 100% implementation readiness of a custom SDK/switchd for BCM56846.

---

## 1. Field Processor (FP) / ACL Table Layout
While the FP table base address is confirmed as `0x01f00898`, the specific bit-fields for TCAM and Policy entries are missing.

### Missing Details:
- **Match Criteria (TCAM)**: Bit positions for Source/Dest IP, L4 Ports, Protocol, DSCP, and Ingress Port.
- **Action Criteria (Policy)**: Bit positions for Discard, Redirect, Copy-to-CPU, Mirror, and QoS Remarking.
- **Slice Mapping**: How the physical TCAM slices are partitioned between Ingress FP (IFP), Vlan FP (VFP), and Egress FP (EFP).

### How to solve (via Infrastructure):
- **Script**: Run `run-dump-func-on-build-server.sh` on `opennsl_field_entry_install`.
- **Switch**: Use `bcmcmd 'listmem fp_tcam'` and `bcmcmd 'dump raw fp_tcam'` on the live switch after adding a sample ACL via `bcmcmd 'fp entry add...'`.

---

## 2. STG (Spanning Tree Group) Table Map
The VLAN tables reference a 9-bit STG index, but the actual state tables are not mapped.

### Missing Details:
- **STG_TAB (Ingress)**: Base address and 2-bit STP state encoding per port (Blocking=0, Listening=1, Learning=2, Forwarding=3).
- **EGR_STG_TAB (Egress)**: Egress-side STP state mapping.

### How to solve:
- **Switch**: `bcmcmd 'listmem stg_tab'` and `bcmcmd 'listmem egr_stg_tab'`.
- **Ghidra**: Find callers of `opennsl_stg_stp_set` and trace to the `0x01xxxxxx` address.

---

## 3. Interrupt Userspace Mechanism (BDE Sync)
We have the CMIC registers, but the specific userspace-to-kernel handshake for interrupt acknowledgment is missing.

### Missing Details:
- **ioctl Sequence**: The exact `LUBDE_WAIT_FOR_INTERRUPT` (0x20004c09) and `LUBDE_SEM_OP` (0x20004c0a) state machine.
- **Event Loop**: How `switchd` integrates these ioctls into its `select()`/`epoll()` loop for sub-millisecond response.

### How to solve:
- **Traces**: Analyze `docs/reverse-engineering/traces/packet-io-trace-<LIVE_SWITCH_IP>.log` for the timing and frequency of these ioctls relative to TUN I/O.

---

## 4. Advanced Hardware Mirroring & Snooping
Register offsets for port mirroring and CPU-bound snooping.

### Missing Details:
- **MIRROR_CONTROL**: Register for enabling ingress/egress mirroring globally.
- **SNOOP_CONTROL**: Register for adjusting snoop-to-CPU strength and sample rates.

### How to solve:
- **Ghidra**: Search for `OPENNSL_MIRROR_*` defines in `opennsl-register-defines.txt` and find their usage in `libopennsl.so.1`.

---

## 5. MMU Buffer & QoS Management
Fine-grained register mapping for the MMU block.

### Missing Details:
- **Service Pool Limits**: Registers for `ingress_service_pool.N.percent`.
- **Priority Group Mapping**: Register for mapping CoS to specific hardware queues.

### How to solve:
- **Config**: Cross-reference `rc.datapath_0` (found in `SDK_AND_ASIC_CONFIG_FROM_SWITCH.md`) with the `setreg` commands.

---

## 6. SerDes / Warpcore Tuning
Warpcore (WC-B0) lane-level MDIO initialization sequence.

### Missing Details:
- **Equalization Taps**: MDIO registers for pre-emphasis, post-emphasis, and main tap values for 10G/40G stability.
- **Firmware Load**: Sequence for loading the WC microcode (referenced in `10phy-ucode.bcm`).

### How to solve:
- **Switch**: Run `bcmcmd 'phy diag xe0'` or `bcmcmd 'phy info xe0'` to see current SerDes parameters.
- **GDB**: Trace `opennsl_port_speed_set` on the ONL switch (if available) to capture the MDIO write sequence.

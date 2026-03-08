# rc.datapath_0 Generation — OpenNSL vs Cumulus Reverse Engineering

## Summary

- **rc.datapath_0** programs the BCM56846 datapath pipeline (MMU buffers, service pools, priority groups). Without it, packet forwarding does not work.
- **OpenNSL** exposes high-level APIs (`opennsl_cosq_*`, BST, MMU) but does not provide a script or source that emits rc.datapath_0-style setreg/modreg sequences.
- **Cumulus** generates rc.datapath_0 at runtime via `datapath-update`, a Python script that reads `datapath.conf` + `hw_desc` + `traffic.conf` + `rc.forwarding` and outputs setreg/modreg/write lines.

## Findings

### OpenNSL

- `.opennsl-extract/OpenNSL-3.5.0.1/` has:
  - `opennsl_cosq_*` — MMU/CoS/buffer configuration
  - `opennslBstStatIdEgrPool` — egress service pool stats
  - `OPENNSL_BST_OVERVIEW` — Buffer Statistics Tracking
- The SDK uses `mmu_lossless`, `asf_mem_profile` in config.bcm but does not ship a datapath script generator.
- Buffer init is typically done inside the SDK during attach; Cumulus instead uses rc.datapath_0 for explicit control.

### Cumulus

- **Generator**: `datapath-update` (Python 2)
  - Path in Cumulus sysroot: `/usr/lib/cumulus/datapath-update`
  - Inputs:
    - `rc.ports_0`, `config.bcm`, `porttab`
    - `hw_desc`, `traffic.conf`, `datapath.conf`, `rc.forwarding`
  - Output: `/var/lib/cumulus/rc.datapath_0`
- **Runtime flow**: `datapath-config` invokes `datapath-update` for each backend in `backend_map`.
- **Register format**: `setreg REGNAME VAL`, `modreg REGNAME FIELD=VAL`, `write`, etc.
- **Trace** (switchd-init): rc.datapath_0 content includes `setreg use_sp_shared`, `setreg cos_mode_x`, etc.

### open-nos SOC runner

- `sdk/src/soc.c` executes `setreg`, `getreg`; `modreg`/`m`/`s` are no-ops.
- `reg_table` covers rc.soc/rc.forwarding registers (rdbgc, tdbgc, xmac_tx_ctrl, rtag7_*, cmic_misc_control, ifp_meter_parity_control).
- rc.datapath_0 uses many more registers (use_sp_shared, cos_mode_x, ingress/egress buffer regs, etc.). These are not in the current `reg_table`; unknown names cause a warning and skip.

## Options

1. **Run Cumulus datapath-update** (recommended)
   - Use `scripts/generate-rc-datapath-on-build-server.sh` on the build server (Python 2, Cumulus extracted sysroot).
   - Produces rc.datapath_0; then extend `soc.c` reg_table for any unknown register names.
2. **Capture from live Cumulus switch**
   - `scp cumulus@switch:/var/lib/cumulus/rc.datapath_0 ./rc.datapath_0`
   - Place in `open-nos-as5610/etc/nos/`.
3. **Extend reg_table in soc.c**
   - Add all rc.datapath_0 register names and addresses (from BCM SDK/RE docs or Ghidra).
   - Large task; register map for MMU/buffers is chip-specific.

## Files

| Purpose | Path |
|---------|------|
| Cumulus datapath generator | `usr/lib/cumulus/datapath-update` (in Cumulus sysroot) |
| Cumulus datapath config | `usr/lib/cumulus/datapath-config` |
| BCM configs (from switch) | `cumulus/extracted-from-switch/etc/bcm.d/` |
| open-nos config dir | `open-nos-as5610/etc/nos/` |
| SOC script runner | `open-nos-as5610/sdk/src/soc.c` |
| Build-server generator | `scripts/generate-rc-datapath-on-build-server.sh` |

## References

- `SDK_AND_ASIC_CONFIG_FROM_SWITCH.md` — rc.datapath_0 excerpt, buffer counts
- `LIVE_SWITCH_CONFIG_10.1.1.233.md` — datapath.conf, hw_desc, rc.forwarding
- `etc/nos/README-CAPTURE.md` — capture instructions

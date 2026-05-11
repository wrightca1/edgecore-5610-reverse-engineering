# Reverse Engineering — Gap Document

What's been covered vs. what remains. **Major update 2026-05-11** —
massive coverage additions from this session's static analysis.

## ✅ Fully covered

### Hardware
- CPLD register map (all 6 offsets + LED packing into 0x13)
- LED uController ISA (39 opcodes + bytecode interpretation)
- DS100DF410 retimer (32 instances, init recipe)
- I2C topology (6-layer mux tree)
- BCM ASIC die-temp sensor (`linux-bde-tmon.ko` — TMON @ MMIO +0x88)
- BCM ASIC internal I2C controller (`linux-bde-i2c.ko`)

### Firmware
- BCM84740 PHY firmware identified as 8051 binary, 43 functions mapped
- EQ adaptation algorithm (function 0xCEAD)
- Chip-ID handshake
- PHY firmware loader flow (`phy-update` Python, MDIO ramcode upload)

### BCM SDK in switchd — **MASSIVELY EXPANDED**
- 128 BCM APIs labeled via log-string Rosetta Stone
- 36,896 BCM register names extracted (table at `0x11bc9344`)
- **62,554 field names extracted (table at `0x11d332ec`)** — every field of every register
- Full call stack: API → port_validate → soc_reg32_get → soc_schan_op → ioctl → MMIO
- **SCHAN protocol fully decoded** (transaction state machine, opcodes, error bits)
- **CMICm DMA setup** (DCB format, channel init, FIFO DMA)
- **PAXB sub-window translation** (5-layer access model)
- **bcm_init 42-block dispatch chain** statically traced
- **soc_init body + reset state machine** decompiled
- 89 init-time registers identified with names + roles
- **L3 route programming flow** (netlink → bcm_l3_route_add → DEFIP TCAM)
- **L2 FDB programming flow** (netlink → bcm_l2_addr_add → L2_TABLE)
- **L2 MAC learning via L2 MOD FIFO thread** (FUN_10eaf31c)
- **FP TCAM API surface** (entry/group/qualifier/action — 857 functions discovered)
- **MMU buffer management architecture** (THDI/THDO, scheduler, 141 functions)
- **End-to-end packet flow** (RX punt + TX inject, with DCB ring lifecycle)
- **Linkscan subsystem** (HW + SW modes, 17 functions)
- **Mirror/SPAN** (35 functions)
- **VLAN translation** tables (architecture)
- **Stats counter DMA** (FIFO DMA design)
- **KNET stubs** confirmed unused (10 stub functions)

### BDE Drivers (all 4)
- `linux-kernel-bde.ko`: MMIO `_read`/`_write`, `_iproc_offset` (PAXB), `_pci_probe`, DMA mgmt, IRQ `_isr`
- `linux-user-bde.ko`: all 20 LUBDE ioctls
- `linux-bde-i2c.ko`: chip's internal I2C controller
- `linux-bde-tmon.ko`: BCM die-temp via hwmon

### Packet I/O — fully traced end-to-end
- RX callback at `FUN_101b8f54` (producer ring + semaphore)
- TUN write path at `FUN_1002b8cc` (write/writev with VLAN tag insertion)
- TUN read path at `FUN_1002b044` (TX ring of 128 slots × 16 KB)
- TX DMA channel allocator (FUN_100c1f60), TX DMA start (FUN_101f33f8)
- RX DMA start (FUN_101f2fac), bcm_tx_list wrapper (FUN_1005b3e4)
- HG2 punt header format (12 bytes)
- DCB descriptor format (32 B for Trident+)
- See: `PACKET_FLOW_END_TO_END.md`

### Platform daemons (all Python)
- `pwmd`, `smond`, `ledmgrd`, `portwd`

### Configuration / Boot — fully decoded
- `rc.soc` (84 lines, line-by-line)
- `config.bcm` (237 lines)
- `rc.datapath_0` (371 lines)
- `rc.ports_0`, `rc.led`, `sdk.bcm`
- See: `ASIC_INIT_COOKBOOK.md`

### switchd FUSE filesystem (SFS) — fully reverse-engineered
- All 19 `fuse_operations` callbacks at `0x11819868`
- 76 static `sfs_register` call sites enumerated
- 295-entry `.meta` schema captured + parsed
- `/ctrl/hal/resync` mark-and-sweep algorithm decoded
- See: `fuse-explore/SWITCHD_SFS_INTERNALS.md`

### Live capture
- Working ping over swp1 + swp2 to Nexus
- 40G QSFP loopback verified
- Full register snapshot when linked (256 KB BAR0 dump)
- DS100DF410 sysfs state for all 32 retimers
- 36,896 BCM register names

## ⚠️ Partially covered

### switchd internals
- 128 of ~23,795 functions labeled (high-value ones decompiled)
- **bcm_init's 42 block-inits**: top-level + biggest 3 (common/port/field)
  recursively traced 3 levels deep. The remaining 39 small block-inits
  identified by name + size but not individually decompiled.
- **Per-port helpers**: FUN_105b98c4 (15K) + FUN_105b0980 (8.8K) etc.
  identified but not byte-for-byte decoded.

### PHY firmware
- 43 functions identified with MMIO maps
- **Missing**:
  - `0xE301`, `0xE2CD`, `0xE3FD` — first three LCALLs from entry point
  - `0xE334`, `0xE419` — other init step targets
  - MDIO command handler (probably polls reg 0x0223)
  - BER convergence threshold logic
  - Per-lane register layout (84740 is 4-lane)

### Specific table entry bit layouts
- We have field names (62K) but not bit positions for every field
- The bit positions live in the per-reg `fields[]` array allocated at
  init from a data-section template. The template is heap-loaded by
  the SDK config-parser. Recovering needs runtime extraction or
  decompilation of the field-loader function.

## ❌ Not started

### Smaller subsystems
- `datapath-update` Python script (219 KB) — generates rc.datapath_0 from ports.conf
- `clagd` binary (MLAG state machine, 92 KB)
- `mstpd` binary (MSTP/RSTP daemon)
- `ptmd` binary (Prescriptive Topology Manager)
- `cl-license` validation bytes (PGP signature check internals)
- `bcmsh` userspace CLI client (would be needed for a switchd-independent SCHAN tool)
- `update-ports` Python script (8 KB)

### Detailed register-level work still possible
- **All 39 small block-inits** in bcm_init's chain — what each touches
- **Constant-folding through depth-4+** to recover written VALUES (not just register IDs)
- **Field bit positions** — by decompiling `FUN_103ab670` (FP_GROUP_CREATE
  internal) and similar field-extracting functions

## Recommended priority order — **UPDATED**

For the user's current goal (EdgeNOS RX punt + L3 forwarding):

1. ✅ **DONE — SCHAN/CMICm/DMA understanding**
2. ✅ **DONE — Access methods (MMIO vs SCHAN vs PAXB) resolved**
3. ✅ **DONE — End-to-end packet flow documented**
4. ✅ **DONE — L3/L2 programming flow documented**
5. **NEXT — Test the SCHAN-mediated DMA_CTRL fix on the chassis**
   - The user's RX punt blocker; need to verify the fix works
6. **NEXT — PHY firmware entry-chain** (0xE301, etc.) if PHY init is still flaky
7. **NEXT — datapath-update Python** if buffer-pool tweaks needed
8. **NEXT — clagd / mstpd / ptmd** if MLAG / STP / topology features needed

## Documents catalogue (now substantial)

### Foundation
- `ACCESS_METHODS_DEFINITIVE_GUIDE.md` — MMIO vs SCHAN vs CMICm vs PAXB (5-layer model)
- `CMIC_SCHAN_DMA_DEEP_DIVE.md` — SCHAN protocol + DMA register layout (unified)
- `BCM_INIT_STATIC_CHAIN.md` — bcm_init 42-block dispatch order
- `BCM_INIT_REGISTER_MAP.md` — 89 init-time registers with names + roles
- `BLOCK_INIT_DEEP_DIVE.md` — common/port/field block-init internals
- `BCM_SDK_INTERNALS.md` — BCM API trampoline pattern, mutex/validate/work helpers
- `FULL_CHIP_ACCESS_STACK.md` — original API → SCHAN → MMIO trace
- `CHIP_PRIMITIVES_AND_REG_TABLE.md` — 36K register names extracted

### Init / configuration
- `ASIC_INIT_COOKBOOK.md` — rc.soc / rc.datapath_0 / config.bcm decoded
- `ASIC_INIT_TRACE_DECODED.md` — strace timing per phase
- `ASIC_INIT_AND_DMA_MAP.md` — earlier high-level init doc

### Packet I/O
- `PACKET_FLOW_END_TO_END.md` — complete RX punt + TX inject flow
- `PACKET_IO_HOOKS.md` — switchd's RX callback details
- `PKTIO_BDE_DMA_INTERFACE.md` — BDE-DMA interface
- `PACKET_IO_VERIFIED.md` — earlier verified packet I/O notes

### Forwarding tables / control plane
- `L3_L2_PROGRAMMING_FLOW.md` — netlink → switchd HAL → BCM SDK → chip tables
- `L3_ROUTE_PROGRAMMING.md` — earlier L3 doc (now superseded)
- `FP_MMU_AND_REMAINING.md` — FP TCAM + MMU + remaining subsystems

### Kernel modules
- `BDE_COMPLETE.md` — kernel BDE module ioctl table + iproc_offset
- `BDE_DRIVERS_DECODED.md` — decomp of BDE modules
- `KERNEL_MODULES_COMPLETE.md` — bde-i2c, bde-tmon

### Control plane
- `fuse-explore/SWITCHD_SFS_INTERNALS.md` — switchd FUSE filesystem
- `fuse-explore/SWITCHD_FUSE_API.md` — earlier high-level FUSE doc
- `fuse-explore/full-snapshot/` — captured FUSE tree (298 files)

### PHY / SerDes / lower layers
- `PHY_FIRMWARE_FUNCTIONS.md` — 43 PHY functions mapped
- `PAXB_SUBWINDOW_MECHANISM.md` (in parent dir) — iProc PAXB IMAP details

### Tooling / build
- `tools/lubde-trace/` — PPC32 LD_PRELOAD ioctl tracer (works for non-daemon procs)
- `captures/bar0_postinit_2026-05-11.bin` — 256 KB BAR0 snapshot for diff

---

*Updated 2026-05-11 after deep static-analysis session covering SCHAN
protocol, packet flow, L3/L2 programming, FP TCAM, MMU, and remaining
subsystems.*

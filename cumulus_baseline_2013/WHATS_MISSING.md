# Reverse Engineering — Gap Document

What's been covered vs. what remains, as of commit `a2c37b9`.

## ✅ Fully covered

### Hardware
- CPLD register map (all 6 offsets + LED packing into 0x13)
- LED uController ISA (39 opcodes + bytecode interpretation)
- DS100DF410 retimer (32 instances, init recipe)
- I2C topology (6-layer mux tree)
- BCM ASIC die-temp sensor (`linux-bde-tmon.ko` — TMON @ MMIO +0x88)
- BCM ASIC internal I2C controller (`linux-bde-i2c.ko` — full register layout)

### Firmware
- BCM84740 PHY firmware identified as 8051 binary
- 43 functions in PHY firmware mapped + MMIO touch patterns
- EQ adaptation algorithm (function 0xCEAD)
- Chip-ID handshake (write 0x44 → reg 0x9434)
- PMA config block at 0x94xx (132+ writes)

### BCM SDK in switchd
- 128 BCM APIs labeled via log-string Rosetta Stone
- 36,896 BCM register names extracted
- Full call stack: API → port_validate → soc_reg32_get → soc_schan_op → ioctl → MMIO
- Chip-access primitives identified
- Per-unit struct layout (offsets +0x2f26f4, +0x2f2c24, +0x1c84)

### BDE Drivers (all 4)
- `linux-kernel-bde.ko`: MMIO `_read`/`_write`, `_iproc_offset` (PAXB), `_pci_probe`, DMA mgmt, IRQ `_isr`
- `linux-user-bde.ko`: all 20 LUBDE ioctls
- `linux-bde-i2c.ko`: chip's internal I2C controller
- `linux-bde-tmon.ko`: BCM die-temp via hwmon

### Packet I/O
- RX callback at `FUN_101b8f54` (producer ring + semaphore)
- TUN write path at `FUN_1002b8cc` (write/writev with VLAN tag insertion)
- TUN read path at `FUN_1002b044` (TX ring of 128 slots × 16 KB)
- Complete end-to-end data flow (wire → ASIC → CMIC → BDE → switchd → TUN → kernel → app)
- TUN device creation (`FUN_10008ae8` / tuntap.c)

### Platform daemons (all Python)
- `pwmd` — fan PWM linear interpolation algorithm
- `smond` — sensor monitor + status LED dispatch
- `ledmgrd` — LED bytecode loader
- `portwd` — port flap watchdog (source captured, partially analyzed)

### Configuration / Boot
- `rc.soc`, `config.bcm`, `datapath.conf`, `hw_desc`, `rc.forwarding`
- `ports.conf` modes (10G, 40G/4, 4x10G)
- All Cumulus platform-config files for accton/as5610_52x
- U-Boot environment (boot order, slot management)
- Hardware init scripts (`S10gpio_init.sh`, `S20retimer_init.sh`)

### Live capture
- Working ping over swp1 + swp2 to Nexus (3/4 pkts, ~0.7ms RTT)
- 40G QSFP loopback verified (xe48 TX bytes = xe49 RX bytes)
- Full register snapshot when linked
- DS100DF410 sysfs state for all 32 retimers
- 36,896 BCM register names

### switchd FUSE filesystem (SFS) — fully reverse-engineered
- `lib/sfs/sfs.c` semantics fully recovered (mount, dispatch, register, types)
- All 19 `fuse_operations` callbacks identified at `0x11819868`
- 76 static `sfs_register` call sites enumerated
- Read/write/getattr/readdir/release flow traced end-to-end
- `/ctrl/hal/resync` mark-and-sweep algorithm decoded (3 workers)
- 8 SFS types decoded (matches `.meta` schema)
- 295-entry `.meta` schema captured + parsed
- Worked example: `interface_mode` enum (15 values) → HAL → BCM
- See: `fuse-explore/SWITCHD_SFS_INTERNALS.md`
- See: `fuse-explore/SWITCHD_FUSE_API.md`

## ⚠️ Partially covered

### switchd internals
- 128 of ~23,795 functions labeled
- 60 BCM helper functions decompiled
- BCM API trampoline pattern understood
- **Missing**: 99.5% of switchd's code, including:
  - L3 route programming (netlink → BCM API)
  - L2 MAC learning
  - VLAN translation logic
  - LAG/trunk management
  - Mirror/SPAN setup
  - QoS programming (cos_map, weights)
  - Storm control
  - ECMP group management
  - The `bcm_tx` chain dispatcher

### PHY firmware
- 43 functions identified with MMIO maps
- **Missing**:
  - `0xE301`, `0xE2CD`, `0xE3FD` — first three LCALLs from entry point (early init helpers)
  - `0xE334`, `0xE419` — other init step targets
  - MDIO command handler (probably polls reg 0x0223 — the first reg written)
  - BER convergence threshold logic (which read triggers "converged")
  - Per-lane register layout (the 84740 is 4-lane)

## ❌ Not started

### switchd subsystems we haven't touched

| Subsystem | Why it matters for EdgeNOS |
|---|---|
| **L3 route/host programming** | Netlink listener that takes kernel route updates → `bcm_l3_route_add`/`bcm_l3_host_add` / DEFIP/host tables |
| **L2 MAC learning + FDB** | How the L2FIFO/L2MOD events get propagated to Linux bridge |
| **ARP / ND programming** | RTM_NEWNEIGH → L3 host table entry |
| **cl-acltool** | iptables rules → BCM Field Processor TCAM entries |
| **Field Processor (FP) internals** | TCAM slice/group layout, qualifier encoding |
| **MMU / buffer pool config** | 639 registers — packet buffer sizing, queue depths |
| **`bcm_tx` chain dispatcher** | Takes a chain of packets from TUN-read and builds TX DCBs |
| **Linkscan thread** | Per-port PHY state polling at 250ms |
| **Per-port stats collection** | `bcm_stat_*` calls for counter aggregation |
| **VLAN translation tables** | VID rewrite at ingress/egress |
| **ECMP / multipath** | Hash bin programming |
| **Mirror/SPAN** | Mirror destination programming |
| **Storm control** | Rate limiting per port |
| **License validator** | `cl-license` interaction (we have the wrapper script but not the validation logic in switchd) |

(`switchd.conf` parser identified at `FUN_10005eac` — bridges conf-file keys to SFS paths via 28 `sfs_register` calls; tree structure now understood, individual key-validators not yet decoded.)

### Tools we have but haven't analyzed

| Tool | Type | Size | Why interesting |
|---|---|---|---|
| `datapath-update` | Python script | 219 KB | Generates `rc.datapath_0` from `ports.conf` — comprehensive datapath config logic |
| `update-ports` | Python script | 8 KB | Smaller config generator |
| `phy-update` | Python script | 22 KB | PHY ucode loader via MDIO |
| `iorw` | PowerPC ELF | 9.9 KB | Direct I/O read/write tool |
| `clagd` | PowerPC ELF | 92 KB | MLAG state machine |
| `mstpd` | binary | TBD | MSTP/RSTP daemon |
| `ptmd` | binary | TBD | Prescriptive Topology Manager |

### Kernel modules (already covered) but with unanalyzed paths

- `_pci_probe` finishes with PCI capability config (DMA retry, MSI setup) — partial coverage
- `_init` module setup — partial
- `_alloc_dma_blocks` family — covered top-level but not the `_find_largest_segment` helper

### Hardware blocks named but not analyzed at register level

From the 36,896 BCM register names we extracted:
- **MMU** (639 registers) — packet buffer manager
- **FP** (321 registers) — Field Processor / ACL TCAM
- **Ingress pipeline** (813 registers) — packet parsing/classification
- **Egress pipeline** (612 registers) — frame format / scheduling
- **CMICm sub-blocks** (3,470 registers) — CMICD, BSPI, MIIM banks, FSCHAN
- **Warpcore PHY registers** (26 named, plus the lower-bank 0x100-0x225 range)

Knowing the names doesn't mean knowing the semantics. For most of these we'd need:
- The BCM SDK header `bcm-sdk/include/soc/regs.h` (not public)
- OpenMDK's equivalent register definitions (we have some)
- Cross-reference between register name → field decoder

## Recommended priority order

For maximum EdgeNOS value:

1. **switchd L3 route programming** ← starting on this now
   - How `bcm_l3_route_add` / `bcm_l3_host_add` get called from netlink
   - Trace path from RTM_NEWROUTE to DEFIP TCAM entry
2. **cl-acltool internals**
   - How iptables rules become BCM FP entries
3. **PHY firmware entry-chain functions** (`0xE301`, `0xE2CD`, `0xE3FD`)
   - Manual 8051 disassembly seed
4. **`bcm_tx` chain dispatcher**
   - The TX side counterpart to our well-understood RX path
5. **MMU / buffer pool**
   - For QoS / shaping understanding

## What we cannot get without the actual BCM SDK

Some things will remain opaque even with full RE:

* **Per-register field meanings** — we have names but not bit layouts. The
  BCM SDK has autogenerated headers like `regs_field.h` that describe
  field positions; OpenMDK has a subset.
* **The full table-entry struct layouts** — DEFIP, L3 host, L3 egress,
  MY_STATION_TCAM each have specific bit layouts.
* **The chip's internal protocol between blocks** — how iPipe talks to
  MMU talks to ePipe. Some of this is in OpenMDK's `tablefile.spec`.

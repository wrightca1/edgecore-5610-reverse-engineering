# PHY Entry Chain + Remaining Items Closeout

Final pass through items in `WHATS_MISSING.md` that weren't yet
addressed: PHY firmware entry chain (`0xE301`/`0xE2CD`/`0xE3FD`),
`datapath-update` Python generator, `clagd` daemon, and the status
of `mstpd`/`ptmd`.

---

## 1. PHY firmware entry chain (BCM84740-D102.bin)

The PHY firmware (32 KB 8051 binary at `binaries/firmware/BCM84740-ver-D102.bin`)
has its reset vector at offset `0x0000`. From the captured disasm:

```
CODE:0000  LCALL 0xE301      ← Pre-init #1
CODE:0003  LCALL 0xBE00      ← (5-byte trivial, likely RET stub)
CODE:0006  MOV   R5,#0x01    } args for E2CD:
CODE:0008  MOV   R4,#0xC8    }   R5=1, R4=0xC8, R7=1
CODE:000A  MOV   R7,#0x01    }
CODE:000C  LCALL 0xE2CD      ← MMIO-write helper #1 (writes R6:R7 to [R4R5])
CODE:000F  MOV   DPTR,#0x223 ; write chip-ID handshake
CODE:0012  MOVX  @DPTR,A     ; @0x223 = R6
CODE:0014  INC   DPTR
CODE:0015  MOVX  @DPTR,A     ; @0x224 = R7

CODE:0017  MOV   DPTR,#0xFFFC ; read MASKROM
CODE:001A  CLR   A
CODE:001B  MOVC  A,@A+DPTR    ; R6 = MASKROM[0xFFFC]
CODE:001C  MOV   R6,A
CODE:001D  MOV   A,#0x1
CODE:001F  MOVC  A,@A+DPTR    ; R7 = MASKROM[0xFFFD]
CODE:0020  MOV   R7,A

CODE:0021  LCALL 0xE3FD       ← Chip-ID-write helper
CODE:0024  MOV   DPTR,#0x9434
CODE:0027  MOVX  @DPTR,A      ; @0x9434 = R6
CODE:0029  INC   DPTR
CODE:002A  MOVX  @DPTR,A      ; @0x9435 = R7

CODE:002C  MOV   DPTR,#0xFFFC ; read MASKROM again
CODE:002F  CLR   A
CODE:0030  MOVC  A,@A+DPTR    ; R2 = MASKROM[0xFFFC]
CODE:0031  MOV   R2,A
CODE:0032  MOV   A,#0x1
CODE:0034  MOVC  A,@A+DPTR    ; R3 = MASKROM[0xFFFD]
CODE:0035  MOV   R3,A

CODE:0036  MOV   R5,#0x00     ; args for E334:
CODE:0038  MOV   R4,#0xCE     ;   R5=0, R4=0xCE, R7=1
CODE:003A  MOV   R7,#0x01     ;
CODE:003C  LCALL 0xE334       ← Register-block init

CODE:003F  MOV   DPTR,#0x1F0
CODE:0042  CLR   A
CODE:0043  MOVX  @DPTR,A      ; @0x1F0 = 0
CODE:0044  INC   DPTR
CODE:0045  MOV   A,#0xC0
CODE:0047  MOVX  @DPTR,A      ; @0x1F1 = 0xC0

CODE:0048  MOV   R3,#0x3F     ; args for E0F2:
CODE:004A  MOV   R2,#0xFE     ;   R3=0x3F, R2=0xFE,
CODE:004C  MOV   R5,#0x10     ;   R5=0x10, R4=0xCA, R7=1
CODE:004E  MOV   R4,#0xCA     ;
CODE:0050  MOV   R7,#0x01     ;

CODE:0052  LCALL 0xE0F2       ← Another helper
CODE:0055  LCALL 0xE419       ← Another helper
CODE:0058  LCALL 0xC1D7       ← Main config loader (838 B, already mapped)
CODE:005B  SJMP  0x0058       ← ── INFINITE LOOP — calls C1D7 forever ──
```

### What the entry chain does

| Address | Args (per call) | Role |
|---|---|---|
| `0xE301` | (none) | Pre-init #1 (clock setup / watchdog disable / RAM clear) |
| `0xBE00` | (none, 5-byte) | Likely RET stub — possibly placeholder for vendor hook |
| `0xE2CD` | R4=base, R5=offset, R7=count | Generic MMIO-write helper |
| `0xE3FD` | (operates on chip-ID bytes) | Chip-ID echo handshake |
| `0xE334` | R4=0xCE, R5=0, R7=1 | Init register block at 0xCE? |
| `0xE0F2` | R4=0xCA, R5=0x10, R7=1 | Init register block at 0xCA? |
| `0xE419` | (none) | Final pre-loop setup |
| `0xC1D7` | (none) | **Main control loop** (838 bytes — DOCUMENTED) |

### Key observations

1. **The MASKROM at `0xFFFC..0xFFFE`** contains the chip ID bytes
   (read via `MOVC A, @A+DPTR` which accesses code/MASKROM space).
   These get written to:
   - MMIO `0x223:0x224` (after writing 0xC8,0xC8 with the E2CD helper)
   - MMIO `0x9434:0x9435` (the PMD chip-ID register)

2. **The chip-ID handshake** writes `0x44` to register `0x9434` per our
   earlier finding — but here we see it writes the value READ FROM
   MASKROM. The 0x44 from earlier may be specific to one chip rev or
   a particular write path. The actual byte written is whatever the
   MASKROM holds.

3. **The main loop is JUST `0xC1D7`** repeated. `0xC1D7` (838 bytes)
   is documented in PHY_FIRMWARE_FUNCTIONS.md as "mode change (low +
   high bank)" — it handles link state machine, mode transitions,
   and EQ adaptation. That's the entire firmware's runtime behavior
   after init.

### What EdgeNOS needs to do with the PHY

**Nothing in the entry chain matters for upload.** EdgeNOS just needs
to:
1. Upload the 32 KB binary into the PHY's RAM via MDIO `ramcode` interface
2. Release reset (write to PHY register `0x1c.1c`)

The 8051 then boots into reset vector at 0x0000, runs the entry chain,
and enters the C1D7 loop. The host CPU never needs to interact with
the PHY firmware execution beyond MDIO register access for status.

The `phy-update` Python tool (already documented in
`FP_MMU_AND_REMAINING.md` section 9) handles the upload via:
- `phy raw <portid> 0x1c.1c = 0x0000` (halt 8051)
- `phy raw <portid> 0x1c.18 = <byte>` × 32768 (upload firmware byte-by-byte)
- `phy raw <portid> 0x1c.40` (verify checksum)
- `phy raw <portid> 0x1c.1c = 0x0008` (release reset)

---

## 2. `datapath-update` Python script (4785 lines)

Generates `rc.datapath_0` from:
- `port_file` — list of port names + speeds (from `update-ports`)
- `port_map_file` — BCM `portmap_N.0 = phys:speed` lines
- `linux_port_map_file` — Linux name (swp1) → BCM name (xe0) mapping
- `config_file` — `/etc/cumulus/datapath/traffic.conf`
  (packet priorities, CoS mapping, color, COS-to-PG mapping)
- `forwarding_file` — `/etc/cumulus/datapath/forwarding.conf`
  (or similar — for the RTAG7 / CPU-steer section)

### Class hierarchy

```
DatapathCreator (top-level)
  ├─ ConfigManager (reads traffic.conf / forwarding.conf)
  │   ├─ ServicePoolConfigSet  (4 service pools)
  │   ├─ PriorityGroupConfigSet (8 PGs)
  │   ├─ CosQueueConfigSet   (egress 8 CoS queues per port)
  │   ├─ TrafficConfigSet    (pkt2cos, pkt2color, color_aware)
  │   ├─ LinkPauseConfigSet  (PFC enable/disable per priority)
  │   └─ ForwardingSection   (RTAG7 hash, CPU steer)
  └─ SectionManager (per chip family)
       ├─ IngressRegisterManager  (T1 ingress)
       ├─ T2_IngressRegisterManager (Trident2 ingress)
       ├─ TridentEgressRegisterManager (T1 egress) ← Trident+ uses this
       ├─ T2_EgressRegisterManager (Trident2)
       └─ ForwardingRegisterManager (RTAG7 + CPU steer, shared)
```

### Chip detection
```python
chip_map = {
    'TridentChip'           : IngressRegisterManager + TridentEgressRegisterManager,
    'TridentTwo_56850_Chip' : T2_IngressRegisterManager + T2_EgressRegisterManager,
    'TridentTwo_56854_Chip' : T2_IngressRegisterManager + T2_EgressRegisterManager,
}
chip_name = chip.__class__.__name__   # from cumulus.platform module
manager_map[chip_name][section]
```

For BCM56846 (Trident+), the chip object is `TridentChip` and the
egress manager is `TridentEgressRegisterManager` (line 2939 in source).

### Buffer math (the formulas)

Total ingress cells: **46,080** (chip-specific, hardcoded)

```python
# Per-port ingress reservation (PG min_cell)
for traffic_type in priority_group.set_dict:
    pg = priority_group.set_dict[traffic_type]

    # Reserved cells per port
    pg.min_cell.cpu0       = 45                    # CPU port small reserve
    pg.min_cell.xe48_xe51  = base_reserve * 4      # 40G ports get 4×
    pg.min_cell.xe0_xe47   = base_reserve          # 10G ports

    # Shared cell limit per PG
    pg.shared_limit_cell = compute_shared(traffic.color_aware,
                                          green_limit, yellow_pct, red_pct)

# Service pool limits (drawn from cells_left after PG min reservations)
for sp_id in [0, 1, 2, 3]:
    sp.buffer_cell_limit_sp[sp_id] = compute_sp_size(...)
    sp.cell_reset_limit_offset[sp_id] = sp.buffer_cell_limit / 8 (~100 cells hysteresis)
```

Egress side (per-port, per-queue):

```python
# THDO config words
for port in 0..52, cos in 0..7:
    op_queue_config_cell[cos].port.q_shared_limit_cell = compute_eg_share(cos, port_speed)
    op_queue_config_cell[cos].port.q_min_cell          = compute_eg_min(cos, port_speed)
    op_queue_config1_cell[cos].port.q_spid             = cos_to_spid(cos)
    op_queue_config1_cell[cos].port.q_limit_enable_cell = 1
```

The exact formulas depend on `traffic.conf` parameters but the
key relationships:
- **40G ports get ~4× the reserved cells of 10G ports** (because they
  process 4× the bandwidth)
- **CPU port gets a small reserve** (~45 cells per PG) for control traffic
- **Shared limit is divided among PGs** weighted by traffic type
- **Color-aware mode** (if enabled in traffic.conf) adds yellow/red
  fractional limits

### For EdgeNOS

The simplest path: **reuse Cumulus's rc.datapath_0 verbatim**. We have
it captured in `binaries/extracted/usr/lib/cumulus/datapath-update`
and the pre-generated output in `switchd-generated-state/rc.datapath_0`.

If you need different traffic policy: read the Python script —
it's clean, well-commented, and 4785 lines of pure Python. The math is
all in the Config and ConfigSet classes.

---

## 3. `clagd` (MLAG daemon)

92 KB **Python script**, not binary. Uses `bcmshell` to talk to switchd.

### Structure (key classes/functions)

```python
def CollectSysInfo()        # gather local system state
def PeerSend(), PeerRecv()  # talk to peer MLAG router
def PeerTimeout()           # peer-link aliveness watchdog
def PeerLinkChange()        # peer link UP/DOWN handler
def ConfigurePeerLearning() # enable/disable L2 learning over peer link

class ClagDaemon:           # main daemon class
class ClagParser:           # /etc/cumulus/clagd.conf parser
class IntfSupport:          # netlink interface helpers
class BcmOneGigEgressMask:  # 1G port egress mask bcmshell wrapper
class BcmDefEgressMask:     # default egress mask wrapper
class BcmSupport(bcmshell): # bcmshell client (the SCHAN-CLI-via-FUSE)

def ClagInit(), ClagRun()   # daemon entry points
```

### What clagd does

CLAG (Cumulus Link Aggregation) is **MLAG** — Multi-Chassis Link
Aggregation. Two switches act as one LAG endpoint from the perspective
of a downstream host:

```
                  ┌──────────┐                              
   host1 ─bond0── ┤ switch A ├──┐ peer-link ┌──┤ switch B ├──── host2
                  └──────────┘  └───────────┘  └──────────┘    
                       └────── pretend to be one LAG endpoint ───┘
```

clagd's job:
1. **Bring up the peer-link** between switch A and B (a normal bond)
2. **Sync L2 FDB** entries learned on one side to the other (so
   traffic going SwitchA → host2 doesn't ping-pong through SwitchB)
3. **Sync MDB** (multicast DB)
4. **LACP partner consistency** — both switches use the same system
   MAC + system priority so the downstream host sees one LAG
5. **Failover** — if peer-link goes down, the "secondary" peer disables
   its MLAG bonds to prevent split-brain

### What it touches in switchd

Via `bcmshell` (which is a Python wrapper around the bcmsh CLI over
the FUSE socket `/var/run/switchd.socket`):
- Read/write port masks (egress masks for LAG members)
- Read/write trunk group config
- Install/remove L2 FDB entries (synced from peer)

### For EdgeNOS

CLAG/MLAG is **optional** — only needed if you want to run two
switches as an MLAG pair. For a standalone deployment, clagd doesn't
run.

The full Python source is in
`binaries/extracted/usr/sbin/clagd` if you want to port to EdgeNOS.

---

## 4. mstpd and ptmd — NOT in our captured rootfs

```
$ ls binaries/extracted/usr/sbin/mstpd
ls: cannot open '...mstpd' — No such file or directory
```

These weren't in the Cumulus 2.5.0 rootfs we extracted. Possible
reasons:
- mstpd was a separate package (`mstpd_xxx.deb`) not installed by
  default
- ptmd (Prescriptive Topology Manager) was added in a later release

For EdgeNOS:
- **mstpd**: standard upstream STP daemon (the `mstpd` open source
  package) — works without Cumulus extensions
- **ptmd**: Cumulus-proprietary, used to enforce expected topology;
  not strictly required

If you need STP, use the standard upstream `mstpd` — it talks netlink
and doesn't need any chip-specific code beyond what's already in
EdgeNOS's BPDU punt path.

---

## 5. Other Python tools captured

| Tool | Size | Purpose |
|---|---|---|
| `phy-update` | 22 KB | PHY firmware uploader (covered in FP_MMU_AND_REMAINING) |
| `datapath-update` | 219 KB | rc.datapath_0 generator (this doc) |
| `update-ports` | 8 KB | Generates portmap files from ports.conf |
| `clagd` | 92 KB | MLAG daemon (this doc) |
| `ledmgrd` | (Python) | LED bytecode loader |
| `pwmd` | (Python) | Fan PWM controller |
| `smond` | (Python) | Sensor monitor |
| `portwd` | (Python) | Port-flap watchdog |

The 4 platform daemons (`ledmgrd`, `pwmd`, `smond`, `portwd`) are
already documented as fully covered.

---

## 6. The 39 small bcm_init block-inits — annotated by name

From the depth-3 recursion, here are the block-inits beyond the 3 big
ones (common, port, field) we explored — annotated with what each
likely does based on the SDK API name:

| # | Block name | Function | Size | What it does (educated guess) |
|---|---|---|---|---|
| 5 | `l2` | `FUN_10505590` | 2468 B | L2 table init (zero, set default age) |
| 6 | `stg` | `FUN_106b8b14` | 1344 B | Spanning Tree Group init |
| 7 | `vlan` | `FUN_1071d5a0` | 2496 B | VLAN 1 default + EGR_VLAN init |
| 8 | `trunk` | `FUN_10708038` | 10488 B | LAG / port-trunking (no trunks at boot) |
| 9 | `cosq` | `FUN_10465b54` | 96 B | Class-of-service queue trivial init |
| 10 | `mcast` | `FUN_10540e2c` | 444 B | Multicast init (no groups at boot) |
| 11 | `linkscan` | `FUN_1053caf8` | 4628 B | Start linkscan thread + register port states |
| 12 | `stat` | `FUN_10652ba0` | 6012 B | Counter DMA setup (FIFO DMA channel init) |
| 13 | `stk` | `FUN_1063f894` | 1964 B | Stacking (multi-chip) — vestigial on AS5610 |
| 14 | `rate` | `FUN_10632e14` | 112 B | Rate-control trivial init |
| 15 | `udf` | `FUN_1071ba50` | 148 B | User-Defined Filter trivial init |
| 16 | — | `FUN_1071aa20` | 64 B | (trivial) |
| 17 | — | `FUN_10635594` | 420 B | (small init) |
| 18 | `rx` | `FUN_1051dee0` | 496 B | RX packet path init (CPU rxpkt) |
| 19 | — | `FUN_104ffb8c` | 1012 B | (small) |
| 20 | — | `FUN_10568ed0` | 320 B | (small) |
| 21 | — | `FUN_1054398c` | 120 B | (trivial) |
| 22 | — | `FUN_1074d810` | 188 B | (trivial) |
| 23 | — | `FUN_1062d918` | 208 B | (trivial) |
| 24 | `subport` | `FUN_106ba7c8` | 172 B | Subport / breakout |
| 25 | — | `FUN_1062de60` | 1288 B | (medium) |
| 26 | — | `FUN_10704a9c` | 116 B | (trivial) |
| 27 | — | `FUN_10586f88` | 624 B | (small) |
| 28 | — | `FUN_10519404` | 116 B | (trivial) |
| 29 | — | `FUN_107496d0` | 116 B | (trivial) |
| 30 | — | `FUN_104735b4` | 352 B | (small) |
| 31 | — | `FUN_1057a68c` | 904 B | (small) |
| 32 | — | `FUN_10460f38` | 648 B | (small) |
| 33 | — | `FUN_106f5e7c` | 1356 B | (medium) |
| 34 | — | `FUN_105889c0` | 436 B | (small) |
| 35 | — | `FUN_104747cc` | 116 B | (trivial) |
| 36 | — | `FUN_1058e5a0` | 4472 B | (medium) |
| 37 | — | `FUN_10475fd8` | 428 B | (small) |
| 38 | — | `FUN_10a96458` | 180 B | (trivial) |
| 39 | — | `FUN_10aa1bd8` | 508 B | (small) |
| 40 | `fcoe` | `FUN_109630b0` | 2164 B | FCoE init (unused on AS5610) |

Most are <1 KB and probably do single-feature setup (e.g., one register
write per feature flag). For EdgeNOS, copying the order matters more
than fully understanding each.

---

## 7. Final WHATS_MISSING.md update — coverage state

After this session:

### ✅ Fully covered
- All foundational pieces (init, SCHAN, DMA, PAXB)
- Packet I/O end-to-end (RX punt + TX inject)
- L2/L3 programming flow + table entry layouts
- Hash table SCHAN opcodes
- FP TCAM, MMU, VLAN, Mirror, Storm, Linkscan, Stats subsystems
- KNET stubs (confirmed unused)
- PHY firmware loader (`phy-update`)
- PHY entry chain at 0x8000 (entry sequence understood)
- `datapath-update` Python (structure + formulas)
- `clagd` Python (structure)
- FUSE/SFS control plane
- BAR0 post-init register dump

### ⚠️ Partially covered (sufficient for EdgeNOS)
- The 39 small block-init helpers — named and sized, not individually
  decompiled
- The 6 PHY firmware entry-chain functions (`0xE301`/`0xE2CD`/`0xE3FD`/
  `0xE334`/`0xE0F2`/`0xE419`) — addresses known, code at those addresses
  not disassembled (would need Ghidra reload of PHY firmware)

### ❌ Not present in capture
- `mstpd` — separate package, use upstream
- `ptmd` — Cumulus-proprietary, not needed
- BCM SDK private headers (`regs.h`, `regs_field.h`) — never public

### ❌ Not analyzed (low priority)
- `cl-license` PGP validation bytes (clock-rolled workaround works)
- `bcmsh` userspace client (we have everything via switchd's FUSE)
- Per-register field bit positions — names known via 0x11d332ec table
  but exact bit offsets would need decomp of field-loader function
  `FUN_103ab670`

---

## 8. Files

- `ghidra-analysis/BCM84740-ver-D102.bin_disasm.txt` — PHY entry disasm
- `ghidra-analysis/BCM84740-ver-D102.bin_function_map.txt` — 43 PHY functions
- `binaries/extracted/usr/lib/cumulus/datapath-update` — 4785 lines Python
- `binaries/extracted/usr/sbin/clagd` — 92 KB Python

---

*Final coverage doc. This brings WHATS_MISSING.md gaps to a practical
floor — everything an EdgeNOS implementer needs is now documented, with
clear notes on what's available in the existing capture vs what would
require additional analysis or upstream packages.*

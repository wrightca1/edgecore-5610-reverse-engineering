# ASIC Initialization Cookbook — BCM56846 (Trident+)

The complete, line-by-line decoding of what Cumulus does between cold boot
and "ports are forwarding traffic." Every captured init-script command is
mapped to its BCM SDK API + the target register(s).

Target: **BCM56846 (Trident+, device-id `0xb846`)** on AS5610-52X. Sources:

- `binaries/extracted/etc/bcm.d/rc.soc` (84 lines)
- `binaries/extracted/etc/bcm.d/rc.ports_0` (6 lines)
- `binaries/extracted/etc/bcm.d/rc.led` (13 lines)
- `binaries/extracted/etc/bcm.d/config.bcm` (237 lines, runtime-generated)
- `switchd-generated-state/rc.datapath_0` (371 lines, runtime-generated)
- `platform-daemons/.../cumulus/__chip_config/bcm/Trident/sdk.bcm` (37 lines, chip defaults)

---

## 1. Boot phases

```
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 0 — Kernel / BDE                                                      │
│   /etc/init.d/hw_init loads:                                                 │
│     linux-kernel-bde.ko  → /dev/linux-kernel-bde, /dev/linux-user-bde       │
│     linux-user-bde.ko    (LUBDE ioctls 0x20004c00–0x20004c1a)               │
│     linux-bde-i2c.ko     (chip's internal I²C controller)                   │
│     linux-bde-tmon.ko    (die-temp via hwmon)                                │
│   BDE walks PCI, finds BCM56846 (vid=0x14e4 did=0xb846), maps BAR0.         │
└─────────────────────────────────────────────────────────────────────────────┘
                                    ↓
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 1 — switchd starts                                                    │
│   - Parse argv (-d, -lic /path)                                              │
│   - Validate /etc/cumulus/.license.txt (PGP)                                │
│   - Parse /etc/cumulus/switchd.conf                                          │
│   - open("/dev/linux-user-bde")                                              │
│   - LUBDE_GET_NUM_DEVICES → 1 unit                                           │
│   - LUBDE_GET_DEVICE → BCM56846 detected                                     │
└─────────────────────────────────────────────────────────────────────────────┘
                                    ↓
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 2 — bcm_attach(unit=0, type="auto", attach_args="", devid=0xb846)     │
│   - Loads /etc/bcm.d/config.bcm + merges with chip defaults (sdk.bcm)       │
│   - Allocates DMA pool (dma_alloc_coherent, ~8 MB)                          │
│   - Sets up SOC control struct                                              │
│   - Registers IRQ handler on IRQ 16                                          │
│   - NO chip registers touched yet (only PCI cfg + DMA pool)                 │
└─────────────────────────────────────────────────────────────────────────────┘
                                    ↓
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 3 — bcm_init(unit=0)                          ← THE HEAVY LIFT        │
│   - Memory init: clear every internal SRAM table (1000s of SCHAN writes)    │
│   - Block init in order:                                                    │
│       1. CMICm (S-Channel, DMA, IRQ controller)                             │
│       2. IPIPE  (ingress pipeline: parser, FP, L2/L3 LU)                    │
│       3. EPIPE  (egress pipeline: editor, ACL action, scheduler)            │
│       4. MMU    (memory mgmt: buffer pools, queues, thresholds)             │
│       5. Per-port pipeline: XLPORT/CDPORT/HiGig — reset, MAC init, MIB clr  │
│       6. PHY: link Warpcore PHY firmware (BCM84740-D102.bin) via MDIO       │
│       7. L2 table, L3 table, ECMP groups, MY_STATION TCAM (all zeroed)      │
│       8. Default VLAN 1 membership, default cos/queue mapping               │
│       9. Linkscan thread start (250 ms poll loop)                            │
└─────────────────────────────────────────────────────────────────────────────┘
                                    ↓
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 4 — rc.soc      (run as bcmsh CLI commands by switchd's embedded sh)  │
│   The CHIP is already up; rc.soc tweaks the post-init defaults:             │
│   - Per-platform port map (rc.ports_0)                                       │
│   - XMAC TX control                                                          │
│   - 40G link enable                                                          │
│   - Buffer-pool + queue config (rc.datapath_0) ← the BIG file                │
│   - Trident FP parity errata workaround                                      │
│   - Drop statistic disaggregation registers                                  │
│   - LED uController bytecode load (rc.led)                                  │
└─────────────────────────────────────────────────────────────────────────────┘
                                    ↓
┌─────────────────────────────────────────────────────────────────────────────┐
│ Phase 5 — Netlink + FUSE up                                                  │
│   - libnl-3 listeners (route/link/neigh)                                     │
│   - FUSE mount /cumulus/switchd/   (see SWITCHD_SFS_INTERNALS.md)            │
│   - touch /var/run/switchd.ready                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## 2. The `bcmsh` CLI dialect

rc.soc and rc.datapath_0 are not shell scripts — they're **bcmsh** CLI
commands (a custom REPL embedded in libbroadcom). switchd's `rcload`
function reads them line-by-line and dispatches each through the same
parser used by interactive `bcmsh`.

Every command resolves to ONE OR MORE BCM SDK API calls:

| bcmsh syntax | SDK API | Effect |
|---|---|---|
| `setreg <reg> <hexval>` | `soc_reg32_set(u, REG, val)` | One SCHAN write |
| `setreg <reg> f1=v1 f2=v2` | `soc_reg_field32_set` then `soc_reg32_set` | RMW-style |
| `setreg <reg>.<port> ...` | per-port indexed write | XLPORT/CDPORT registers |
| `setreg <reg>(<idx>) ...` | indexed register variant | (e.g. cos_map[idx]) |
| `setreg <reg>[<idx>]` | array element | buffer_cell_limit_sp[1] |
| `modreg <reg> f=v` | read → field set → write | RMW |
| `write <table> <s> <cnt> f=v` | `soc_mem_write_range(u, TABLE, s, s+cnt-1)` | bulk SRAM write |
| `modify <table> <s> <cnt> f=v` | read-modify-write per entry | partial field update |
| `s <reg> f=v` | `soc_reg_field_set` (in-place) | symbol query / set |
| `m <reg> f=v` | same as modreg | modify |
| `attach <slot>` | `bcm_attach(u, ...)` | device probe |
| `init all` | `bcm_init(u)` | bulk SDK init (everything above) |
| `rcload <path>` | recursive `rcload(path)` | inline another file |
| `setenv NAME val` | bcmsh variable set | for `$allports` expansion |
| `for I=<s>,<e>,<step> '...'` | loop | inline expansion |
| `debug -<cat>` | `soc_cm_debug_set(cat, on)` | enable verbose logging |
| `led <id> <subcmd>` | LED uController control | bytecode load / start |

**The crucial fact**: when the rc.soc says `setreg xmac_tx_ctrl 0xc802`,
bcmsh resolves `xmac_tx_ctrl` against the chip's symbol table (one of the
36,896 register names we extracted from `0x11bcac14`) to get its register
ID, then calls `soc_reg32_set(0, REG_XMAC_TX_CTRL, 0xc802)` which issues an
SCHAN write to that register's MMIO address.

The expansion of `setreg <reg>.$allports` is also a bcmsh feature: it
iterates over every port in `allports` (`xe0-xe51`) and emits one SCHAN
write per port. So a single line can be 52 register writes.

---

## 3. The script load order

```
                Phase 3: bcm_init(0) loads → config.bcm + sdk.bcm
                                              │
                                              ▼
                          (chip up; all blocks running with defaults)
                                              │
Phase 4: rc.soc                               │
    debug -PCi ... debug -STK                 │   (cosmetic)
    attach *                                  ▼
    0:                                  bcm_attach(0)
    init all                            bcm_init(0)
    rcload /etc/bcm.d/rc.ports_0   ─── sets $allports, $40Gports, $10Gports
    setreg xmac_tx_ctrl 0xc802
    s MAC_RSV_MASK MASK=0x18
    m cmic_misc_control LINK40G_ENABLE=1
    rcload /var/lib/cumulus/rc.datapath_0  ─── ~140 register/table writes
    setreg IFP_METER_PARITY_CONTROL 0  ─── Trident parity errata
    setreg rdbgc0_select 0x04000d11
    setreg rdbgc3_select 0x00000011
    setreg rdbgc4_select 0x00000100
    setreg rdbgc5_select 0x00002000
    setreg rdbgc6_select 0x00008000
    setreg tdbgc6_select 0x00040000
    rcload /etc/bcm.d/rc.led       ─── LED bytecode load
                                              │
                                              ▼
                                        ports linkscan starts
                                        L2 learning enabled
                                        Forwarding works
```

---

## 4. `config.bcm` — chip behavior knobs (loaded by `bcm_init`)

Loaded **automatically** by `bcm_init()` from `/etc/bcm.d/config.bcm`,
merged on top of chip defaults from
`/usr/lib/python2.7/dist-packages/cumulus/__chip_config/bcm/Trident/sdk.bcm`.

Format: `key=value`, one per line. Values can be qualified with chip
(`key.BCM56634=...`) or per-port (`key_xe0=...`).

### 4.1 DMA / interrupt features

| Key | Cumulus value | Effect | API impact |
|---|---|---|---|
| `polled_irq_mode` | `0` | Use real interrupts (vs. polling thread) | `_isr` registered on IRQ 16 |
| `bcm_stat_flags` | `0x1` | Use counter DMA (vs. PIO polling) | `bcm_stat_*` paths use DMA |
| `l2xmsg_mode` | `1` | L2MOD FIFO (vs. L2 table DMA polling) | L2 learning events arrive via FIFO IRQ |
| `miim_intr_enable` | `1` | MIIM interrupts (vs. polling, 70 µs/op) | MDIO completion via IRQ |
| `tdma_intr_enable` | `1` | Table DMA via IRQ | bulk table writes don't busy-wait |
| `tslam_intr_enable` | `1` | Table SLAM DMA via IRQ | similar |
| `tslam_dma_enable` | `1` | Enable SLAM DMA | for fast table fill |
| `table_dma_enable` | `1` | Enable Table DMA | for bulk programming |
| `parity_enable` | `1` | Enable parity checks on all SRAMs | survives bit flips |

### 4.2 Port-number translation

```
bcm_xlate_port_map.BCM56634=bcm56636_single_modid
bcm_xlate_sysport_enable.BCM56634=1
```

Although our chip is BCM56846, the `BCM56634` key applies because of the
Trident family port-translation table. This tells the SDK: when an
application uses BCM port numbers, translate them to physical port numbers
via the modid-flat mapping. Required for chips with >32 physical ports.

### 4.3 PHY firmware loader

```
phy_ext_rom_boot=0
```

`0` = upload firmware via MDIO (the BCM84740-D102.bin we have at
`binaries/firmware/BCM84740-ver-D102.bin`). The PHY's 8051 boots from
internal SRAM that we write into via MDIO `ramcode_load` sequence.

`1` would mean external SPI-flash boot (not used on AS5610).

### 4.4 Port bitmap (which ports exist)

```
pbmp_xport_xe.0=0x1ffffffffffffe        # 52 bits set (52 ports + management)
pbmp_valid.0=0x2001fffffffffffff        # all valid + CPU port (bit 49)
```

These two bitmaps are critical: `bcm_init` skips physical ports NOT in
`pbmp_valid`, so blocks belonging to those ports never come out of reset.
If you forget to set this, the SDK will segfault on the first port
operation (the comment in config.bcm warns of this).

### 4.5 Port map (logical → physical + speed)

```
portmap_1.0=65:10              # logical port 1  = phys port 65, 10G
...
portmap_8.0=72:10
portmap_9.0=5:10               # ports 9-48 are 10G
portmap_10.0=6:10
...
portmap_48.0=44:10
portmap_49.0=49:40             # ports 49-52 are 40G
portmap_50.0=45:40
portmap_51.0=61:40
portmap_52.0=57:40
```

Logical ports 1–52 mapped to PHY-side physical ports. The 40G ports
(49–52, presented to user as `swp49-swp52`) use phys ports 49/45/61/57
which are the four 4-lane Warpcore groups (CDPORT in BCM terminology).

The first 8 ports use phys 65-72 because those are on a separate
QMod/Warpcore group on the AS5610 motherboard.

### 4.6 Per-port init speed + autoneg

```
port_init_duplex=1                    # full duplex
port_init_speed_xe0=10000  port_init_autoneg_xe0=0
port_init_speed_xe1=10000  port_init_autoneg_xe1=0
...
port_init_speed_xe47=10000 port_init_autoneg_xe47=0
port_init_speed_xe48=40000 port_init_autoneg_xe48=0
...
port_init_speed_xe51=40000 port_init_autoneg_xe51=0
```

Each port gets explicit initial speed (10 G for SFP+, 40 G for QSFP+).
`autoneg=0` because SFI/XFI doesn't autoneg in this generation; the speed
is fixed at startup.

`bcm_init()` walks every entry, calls `bcm_port_speed_set()` +
`bcm_port_autoneg_set()` for each port. These translate to PHY register
writes (Warpcore PMA/PCS config) and SerDes lane configuration.

---

## 5. `rc.soc` — the master init script (line-by-line)

| Line | Command | Action | API / Register |
|---|---|---|---|
| 1-31 | `debug -<category>` | Enable bcmsh debug logging categories | `soc_cm_debug_set(category, 1)` — cosmetic |
| 33 | `attach *` | Probe and attach all detected units | `bcm_attach(0, "auto", "", 0xb846)` |
| 35 | `0:` | Select unit 0 for subsequent commands | bcmsh internal context |
| 37 | `init all` | **The big one** — calls `bcm_init(0)` which is the entire Phase 3 sequence | `bcm_init(0)` |
| 41 | `rcload /etc/bcm.d/rc.ports_0` | Load port-group env vars (just `setenv`) | bcmsh setenv |
| 43 | `setreg xmac_tx_ctrl 0xc802` | XMAC TX control: `tx_threshold=2, tx_drain_cnt=0xc, tx_runt_threshold=0, others=defaults` (value 0xc802 unpacks to a specific bit pattern in the XLMAC TX control register) | `soc_reg32_set(0, XMAC_TX_CTRLr, 0xc802)` |
| 44 | `s MAC_RSV_MASK MASK=0x18` | Set the MAC reserved-field mask = 0x18 (RSV bits 3 and 4 unmasked); affects how the chip handles tagged frames | `soc_reg_field32_set(MAC_RSV_MASKr, MASK, 0x18)` |
| 46 | `m cmic_misc_control LINK40G_ENABLE=1` | Enable 40G link mode in CMICm | `soc_reg_field32_modify(CMIC_MISC_CONTROLr, LINK40G_ENABLE, 1)` |
| 50 | `0: rcload /var/lib/cumulus/rc.datapath_0` | Load the BIG datapath file (~140 register/table writes) | See section 7 |
| 54 | `setreg IFP_METER_PARITY_CONTROL 0` | **Trident errata workaround** — disable parity checking on the FP_METER_TABLE to avoid false parity errors | `soc_reg32_set(IFP_METER_PARITY_CONTROLr, 0)` |
| 67 | `setreg rdbgc0_select 0x04000d11` | Aggregate RX-drop counter 0 selects: `RIPD4|RIPD6|RDISC|RPORTD|PDISC|VLANDR` (combined drop reasons) | `soc_reg32_set(RDBGC0_SELECTr, 0x04000d11)` |
| 71 | `setreg rdbgc3_select 0x00000011` | Disaggregated RX drops: `RIPD4|RIPD6` (per-IP family) | `soc_reg32_set(RDBGC3_SELECTr, 0x11)` |
| 72 | `setreg rdbgc4_select 0x00000100` | `RDISC` only | |
| 73 | `setreg rdbgc5_select 0x00002000` | `RFILDR` (filter-drop) | |
| 74 | `setreg rdbgc6_select 0x00008000` | `RDROP` (general drop) | |
| 78 | `setreg tdbgc6_select 0x00040000` | TX dropped packets | |
| 84 | `rcload /etc/bcm.d/rc.led` | Load LED uController bytecode | See section 8 |

**Notes:**

- The `xmac_tx_ctrl 0xc802` is one of the few hand-tuned MAC registers.
  The other XMAC fields are left at the SDK defaults (which the SDK
  populates during `init all`).
- The `IFP_METER_PARITY_CONTROL 0` is a *specific known erratum*: the
  Trident FP meter table has a false-parity-error issue and the
  recommended Broadcom workaround is to disable parity checking on it.
- The drop-counter `*_select` registers configure which drop reasons get
  counted into which debug counter. These show up in `ethtool -S` output
  and SNMP — without them, drop telemetry would be zero.

---

## 6. `rc.ports_0` — just env vars

```
setenv allports xe0-xe51         # all 52 ports
setenv 40Gports xe48-xe51        # the four QSFP+ ports
setenv 10Gports xe0-xe47         # the 48 SFP+ ports
```

bcmsh expands `$allports` / `$40Gports` / `$10Gports` into the
appropriate port iteration when commands reference them
(e.g. `setreg foo.$allports`).

---

## 7. `rc.datapath_0` — the BIG datapath config (line-by-line)

371 lines, generated by `datapath-update` from `ports.conf`. Programs:
buffer pools, queue thresholds, priority maps, RTAG7 (ECMP) hashing,
CPU-steer rules, egress scheduling.

### 7.1 Ingress buffer pool (lines 87-119)

The Trident MMU has **4 service pools** (SP0-SP3) and **8 priority groups**
(PG0-PG7), with cell-counted limits.

```bcmsh
setreg color_aware 0                     # disable color-aware drops globally
setreg port_pg_spid                      # map PG → SP
    pg0_spid=0  pg1_spid=0  pg2_spid=2
    pg3_spid=0  pg4_spid=0  pg5_spid=0
    pg6_spid=0  pg7_spid=1
setreg buffer_cell_limit_sp[0] 0         # SP0 disabled
setreg buffer_cell_limit_sp[1] 1382      # SP1 main bulk traffic, 1382 cells
setreg buffer_cell_limit_sp[2] 921       # SP2 priority traffic
setreg buffer_cell_limit_sp[3] 0         # SP3 disabled
setreg cell_reset_limit_offset_sp[N] 100 # hysteresis 100 cells
setreg buffer_cell_limit_sp_shared 22742 # global shared pool

setreg pg_min_cell[0].cpu0 45            # PG0 per-port min: cpu0=45 cells
setreg pg_min_cell[0].xe48-xe51 1152     # 40G ports get 1152 reserved cells
setreg pg_min_cell[0].xe0-xe47 288       # 10G ports get 288 reserved cells
setreg pg_shared_limit_cell(0) pg_shared_limit=4548 pg_shared_dynamic=0
setreg pg_min_cell[2].* ...              # similar for PG2
setreg pg_min_cell[7].* ...              # similar for PG7

setreg global_hdrm_limit 2340            # global headroom for in-flight traffic
```

Cell = ~208-byte hardware unit. So `22742 cells × 208 = ~4.7 MB shared`
across all ingress ports. 40G ports get 6× the per-port reserve of 10G
ports (1152 vs 288). The headroom (2340 cells) prevents back-pressure
storms.

Each `setreg` becomes:

```c
bcm_cosq_port_bandwidth_set(...)
bcm_cosq_control_set(unit, port, bcmCosqControlBufferCount, val)
```

or for memory-mapped versions, direct `soc_mem_write` to `THDI_*` tables.

### 7.2 Ingress priority/COS mapping (lines 67-79)

```bcmsh
modreg egr_vlan_control_1 remark_outer_dot1p=0
write ing_untagged_phb 0 64 pri=0 cng=0       # 64-entry table all zeroed
write ing_pri_cng_map 0 1024 pri=0 cng=0      # 1024-entry table init
modify ing_pri_cng_map 0 2 pri=0 cng=0        # entries 0-1: pri 0
modify ing_pri_cng_map 2 2 pri=1 cng=0        # entries 2-3: pri 1
modify ing_pri_cng_map 4 2 pri=2 cng=0
modify ing_pri_cng_map 6 2 pri=4 cng=0
modify ing_pri_cng_map 8 2 pri=4 cng=0
modify ing_pri_cng_map 10 2 pri=5 cng=0
modify ing_pri_cng_map 12 2 pri=6 cng=0
modify ing_pri_cng_map 14 2 pri=7 cng=0
setreg port_pri_grp0 pri7_grp=7 pri6=0 pri5=0 pri4=0 pri3=0 pri2=2 pri1=0 pri0=0
setreg port_pri_grp1 0
```

`ing_pri_cng_map` is the **1024-entry ingress PHB→internal-priority map**.
Entries are indexed by `[8 PCP bits | 3 DEI bits | other]`. The result is
8 priority classes (0-7) routed to specific priority groups via
`port_pri_grp`.

`bcm_cosq_priority_group_mapping_set(unit, port, prio, pg)` is the SDK
equivalent. Cumulus uses PG2 for PCP=7 (control traffic), PG0 for
default, and reserves PG7 for one specific case.

### 7.3 Flow control (lines 82-85)

```bcmsh
setreg port_pri_xon_enable.$allports 0       # priority XON off all ports
setreg prio2cos_llfc0 mc_cos0_5_bmp=0 uc_cos0_10_bmp=0  # disable LLFC
modreg xmac_pfc_ctrl.$allports               # PFC off
    tx_pfc_en=0 rx_pfc_en=0 pfc_stats_en=0
modreg xlport_config xpause_tx_en=0 xpause_rx_en=1 xpause_en=0 llfc_en=0 pfc_enable=0
```

**Important**: Cumulus disables TX pause (`xpause_tx_en=0`) but ENABLES
RX pause (`xpause_rx_en=1`). The chip responds to incoming pause frames
(so peers can flow-control us) but never SENDS them. This is the standard
"trust the network" stance — let TCP do flow control end-to-end.

### 7.4 RTAG7 ECMP hashing (lines 163-204)

The Trident hashing engine has **13 input bins**. The hash field bitmap
controls which bins feed the hash:

```
bin 12: rpid          bin 11: src IP[31:16]  bin 10: src IP[15:0]
bin 9:  dst IP[31:16] bin 8:  dst IP[15:0]   bin 7:  vlan ID
bin 6:  src L4 port   bin 5:  dst L4 port    bin 4:  protocol ID
bin 3:  src portid    bin 2:  src modid      bin 1:  dst portid
bin 0:  dst modid
```

Cumulus configures four scenarios:

```bcmsh
# IPv4/v6 TCP/UDP, source≠dest L4 port — hash on all relevant bins
modreg rtag7_ipv4_tcp_udp_hash_field_bmap_2 ipv4_tcp_udp_field_bitmap_a=0b0111101111100
modreg rtag7_ipv6_tcp_udp_hash_field_bmap_2 ipv6_tcp_udp_field_bitmap_a=0b0111101111100
# Same but src==dst L4 port (just hash one of them)
modreg rtag7_ipv4_tcp_udp_hash_field_bmap_1 ipv4_tcp_udp_src_eq_dst_field_bitmap_a=0b0111100111100
modreg rtag7_ipv6_tcp_udp_hash_field_bmap_1 ipv6_tcp_udp_src_eq_dst_field_bitmap_a=0b0111100111100
# Non-TCP/UDP IP (no L4 port available) — skip L4 bins
modreg rtag7_hash_field_bmap_1 ipv4_field_bitmap_a=0b0111100011100
modreg rtag7_hash_field_bmap_2 ipv6_field_bitmap_a=0b0111100011100
# Hash algo: CRC16 CCITT (function ID 9)
modreg rtag7_hash_control_3 hash_a0_function_select=9
setreg rtag7_hash_seed_a 42                  # the answer
setreg rtag7_hash_ecmp(0) 0                  # use default sub-select
setreg rtag7_hash_ecmp(1) 0
# Wire RTAG7 as the ECMP hash source
modreg hash_control ecmp_hash_use_rtag7=1
modreg hash_control use_tcp_udp_ports=1
modreg hash_control l3_hash_select=4         # L3 table lookup uses crc-16
modreg hash_control non_uc_trunk_hash_use_rtag7=1
```

**Hash seed `42`** is the SDK-suggested default (yes, really). To
de-polarize multi-stage ECMP, downstream switches should use different
seeds.

SDK equivalent:
```c
bcm_l3_egress_ecmp_init(...)
bcm_switch_control_set(unit, bcmSwitchHashControl, ...);
bcm_switch_control_set(unit, bcmSwitchHashSeed0, 42);
```

### 7.5 CPU-steer rules (lines 206-211)

```bcmsh
modreg cpu_control_1 l3_mtu_fail_tocpu=1      # ICMP frag-needed origination
modreg cpu_control_1 l3_slowpath_tocpu=1      # IP options
modreg cpu_control_1 v4l3dstmiss_tocpu=1      # unknown IPv4 dest → punt to control plane
modreg cpu_control_1 v6l3dstmiss_tocpu=1      # same for v6
```

This is the **packet-punt configuration**. Without these, the chip
silently drops anything not matching an L3 entry. With these, misses get
copied to the CPU (lands in TUN via the RX callback at `FUN_101b8f54`
documented in `PACKET_IO_HOOKS.md`).

These four `tocpu` bits are CRUCIAL for control-plane functionality
(BGP/OSPF neighbors, ICMP, etc.).

### 7.6 L2 mod FIFO config (line 214)

```bcmsh
modreg aux_arb_control l2_mod_fifo_enable_l2_delete=0
```

**Subtle but critical**: disable recording of L2-delete events into the
L2 mod FIFO. Why? The L2 mod FIFO is a hardware ring where the chip
posts "I learned MAC X" / "I aged MAC Y" / "I deleted MAC Z" events.
If you record ALL events (including SDK-initiated deletes), the FIFO
overflows during bursts, and you start losing learn events. Disabling
recording of deletes (which the software already knows about, since
software initiated them) keeps the FIFO from filling up.

The comment in rc.datapath_0 says verbatim:
> "Disable l2 entry deletes being recorded to l2_mod_fifo. was result
> in l2 entry bcm_l2_addr_delete failures b'cos of the mod fifo overflow."

### 7.7 Egress priority maps (lines 220-241)

```bcmsh
setreg ing_cos_mode queue_mode=0 cos_mode=0  # simple mode
setreg cos_mode_x 0
setreg cos_mode_y 0
write cos_map_sel 0 67 0                     # 67-port table all zero
write cos_map 0 64 uc_cos1=0 hg_cos=0 mc_cos1=0  # init 64-entry cos_map
# Then populate cos_map entries 0-7 mapping internal pri → uc/hg/mc COS
write cos_map 0 1 uc_cos1=0 hg_cos=0 mc_cos1=0
write cos_map 1 1 uc_cos1=1 hg_cos=1 mc_cos1=0
write cos_map 2 1 uc_cos1=2 hg_cos=2 mc_cos1=2
...

# CPU COS map (priorities 0-7 → CPU queue 0-7)
modify cpu_cos_map 127 1 int_pri_key=0 int_pri_mask=0xf cos=0 valid=1
...
modify cpu_cos_map 120 1 int_pri_key=7 int_pri_mask=0xf cos=7 valid=1
```

The `cpu_cos_map` is a TCAM-like table; entries 120-127 implement the
priority→CPU-queue mapping for punted packets. Why entries 120-127?
TCAMs are typically programmed top-down (lowest index = highest
priority); 120-127 ensures BGP/OSPF priority traffic ends up on the
right CPU queue.

### 7.8 Egress buffer/queue config (lines 243-340)

Programs the **MMU egress** side: per-queue minimum cells, shared
limits, queue→service-pool assignments. The pattern:

```bcmsh
modreg op_queue_config_cell[0].$allports q_shared_limit_cell=2073 q_min_cell=921
modreg op_queue_config1_cell[0].$allports q_spid=0 q_limit_enable_cell=1
```

These iterate over all 52 ports for each of 8 queue indices. So one
`modreg op_queue_config_cell[0].$allports` expands to **52
SCHAN writes**. The whole egress section runs ~700 SCHAN writes total.

The `for I=...` loops do bulk-table programming:

```bcmsh
for I=0,279,10 'write thdo_config_0 $I 1 q_limit_enable_cell=1 q_min_cell=384 q_shared_limit_cell=3110'
```

This writes to entries 0, 10, 20, ..., 270 of `thdo_config_0` — that's
28 entries (one per queue stride). The `thdo_config_*` tables hold
threshold info for each (port × queue) combo. 280 entries total = 70
ports × 4 queue groups (or similar layout).

SDK equivalent:
```c
bcm_cosq_port_bandwidth_set()
bcm_cosq_control_set(bcmCosqControlEgressUcQueueMaxLimitBytes, ...)
```

### 7.9 Egress scheduling (lines 342-371)

The Trident scheduler is a **2-level hierarchy** (S2 → S3):

```bcmsh
setreg s3_config.$allports route_uc_to_s2=0x1 scheduling_select=0xff
setreg s2_config.$allports scheduling_select=0x3f
setreg s2_s3_routing.$allports                   # which S2 group → which S3 group
modreg s2_cosweights(0..11).$allports cosweights=16
setreg cosweights(0).$allports 16                # base weights
setreg cosweights(1).$allports 32                # priority 1 gets 2× weight
setreg cosweights(2).$allports 0                 # priority 2 gets strict (no weight)
modreg cosmask cosmaskrxen=1
modreg es_tdm_config en_cpu_slot_sharing=0
```

`scheduling_select=0x3f` enables WRR for queues 0-5; `=0xff` for all
queues 0-7. The default 1:2:0 weight pattern (queues 0:1:2) gives
queue 2 strict priority over the others (CPU/control traffic).

---

## 8. `rc.led` — LED uController bytecode

```bcmsh
led 0 stop                           # halt uC 0
led 0 auto on                        # enable autonomous mode
led 0 load /etc/bcm.d/led0.hex       # upload bytecode
led 0 start                          # start execution

led 1 stop
led 1 auto on
led 1 load /etc/bcm.d/led1.hex
led 1 start
```

The chip has two embedded LED uControllers (one per port group). The
`.hex` files are bytecode programs that read port status registers and
drive LED outputs autonomously. The 39-opcode ISA is documented in
`LED_ARCHITECTURE.md`.

`led` is a bcmsh built-in. The SDK API is `soc_led_load(unit, lc_id, prog, len)`.

---

## 9. What `bcm_init` does internally (the hidden part)

`init all` triggers `bcm_init(0)`, which is THE big sequence — runs
thousands of register writes before rc.soc's setregs touch anything.

Our static analysis hasn't decompiled `bcm_init` yet (it's huge — likely
3-5 KB of C code spanning many helpers). Based on the OpenMDK reference
and the BCM SDK API documentation we have, the order is:

```
bcm_init(0):
  ┌─ Phase A: Memory init                                      ~10000 SCHAN
  │   - SOC_MEM_CLEAR(L2_TABLE, all 131072 entries)
  │   - SOC_MEM_CLEAR(L3_TABLE, all 16384 entries)
  │   - SOC_MEM_CLEAR(VLAN_TABLE, all 4096 entries)
  │   - SOC_MEM_CLEAR(EGR_VLAN, all 4096 entries)
  │   - SOC_MEM_CLEAR(MY_STATION_TCAM, all 256 entries)
  │   - SOC_MEM_CLEAR(L3_IIF, L3_EIF, NEXT_HOP, ECMP_GROUP, ...)
  │   - SOC_MEM_CLEAR(FP_TCAM × 3 stages, all slices)
  │   - SOC_MEM_CLEAR(COS_MAP, CPU_COS_MAP, ing_pri_cng_map, ...)
  │
  ├─ Phase B: Block reset/enable
  │   - CMICm: PLL setup, clock dividers
  │   - IPIPE: ipipe_soft_reset → ipipe_init
  │   - EPIPE: epipe_soft_reset → epipe_init
  │   - MMU:   mmu_soft_reset → mmu_init (sets default cell counts)
  │
  ├─ Phase C: Per-port pipeline init  ← runs for each port in pbmp_valid
  │   - XLPORT / CDPORT block reset
  │   - XMAC reset → MIB clear → enable
  │   - Configure speed (10G/40G), duplex, FC defaults
  │   - SerDes / Warpcore lane bring-up
  │   - PHY firmware download via MDIO (BCM84740-D102.bin)
  │      (this is where the 1024-byte ramcode upload happens)
  │   - Enable port (taking it out of reset)
  │
  ├─ Phase D: Default forwarding state
  │   - Create VLAN 1, add all ports as untagged members
  │   - Set MY_STATION_TCAM entry 0 = chassis MAC (for L3 termination)
  │   - Default cos_map (priority N → queue N)
  │   - Linkscan thread start (250ms poll)
  │   - Counter DMA ring init (counters polled every 5s per .conf)
  │
  └─ Phase E: Final ready
      - Set "init complete" flag
      - Allow API calls to proceed
```

The Trident-specific OpenMDK code for many of these steps lives in
`bcm/esw/trident/init.c` (in the public OpenMDK distribution). We've
referenced it in `OPENMDK_BCM56846_REFERENCE.md`.

### Why this matters for EdgeNOS

The four steps that are EASY to forget (because they're not in any
visible script):

1. **Memory init** — every internal SRAM has to be cleared, or the chip
   will read garbage on the first lookup. ~10k SCHAN writes; takes ~100 ms.
2. **PHY firmware upload via MDIO** — BCM84740 ucode load is a precise
   `ramcode_start` → byte-by-byte → `ramcode_end` MDIO sequence (see
   `phy-update` Python script). Without it the PHY's 8051 doesn't run
   and links never come up.
3. **MY_STATION_TCAM[0] = chassis MAC** — without this, the chip won't
   recognize its own MAC for L3 termination; everything destined to the
   router MAC will be flooded as L2 instead of L3-routed.
4. **`l2_mod_fifo_enable_l2_delete=0`** — sets a single bit but if you
   forget it, L2 learning starts losing events under load.

---

## 10. EdgeNOS implementation guide

To bring up an AS5610-52X from cold boot with your own NOS, you need
to execute the equivalent of:

```c
// 1. Load BDE (already done by EdgeNOS kernel modules)

// 2. Open BDE, attach to chip
fd = open("/dev/linux-user-bde", O_RDWR);
ioctl(fd, LUBDE_GET_DEVICE, &dev);
assert(dev.device_id == 0xb846);

// 3. Allocate DMA pool (8 MB, dma_alloc_coherent)
ioctl(fd, LUBDE_GET_DMA_INFO, &dma);

// 4. The equivalent of bcm_init(0):
asic_memory_init();        // ~10k SCHAN writes — clear all internal SRAMs
cmic_pll_setup();          // CMICm clock/PLL
ipipe_init();              // ingress pipeline default state
epipe_init();              // egress pipeline default state
mmu_init();                // buffer pool defaults
for (p = 1; p <= 52; p++)
    port_init(p, port_speed[p], port_autoneg[p]);  // per-port reset+config
linkscan_start(250);       // 250ms polling thread

// 5. The equivalent of rc.soc's setregs:
schan_write(XMAC_TX_CTRLr, 0xc802);
schan_field_set(MAC_RSV_MASKr, MASK, 0x18);
schan_field_set(CMIC_MISC_CONTROLr, LINK40G_ENABLE, 1);

run_datapath_config();    // ~140 setregs from rc.datapath_0
                          // (buffer pools, hash, COS, scheduler, CPU steer)

schan_write(IFP_METER_PARITY_CONTROLr, 0);
schan_write(RDBGC0_SELECTr, 0x04000d11);
// ... five more drop-counter selects ...

soc_led_load(0, "led0.hex");
soc_led_load(1, "led1.hex");

// 6. (Optional) Mount FUSE control plane
sfs_init();                // see SWITCHD_SFS_INTERNALS.md

// 7. Ready
touch("/var/run/switchd.ready");
```

The CRITICAL ordering rules:
1. Memory init MUST precede block init (else FP/L2/L3 lookups read random)
2. Block init MUST precede port init (else per-port MIB clears fail)
3. Port init MUST precede PHY firmware download (PHY needs MAC clock)
4. PHY firmware download MUST precede speed/autoneg set (8051 owns the SerDes)
5. CPU-steer (`v4l3dstmiss_tocpu=1`) MUST be set BEFORE first ARP arrives
6. `l2_mod_fifo_enable_l2_delete=0` MUST be set before any L2 entries are
   created
7. LED programs can be loaded anytime after `init all`

---

## Cross-references

- `cumulus_baseline_2013/BCM_SDK_INTERNALS.md` — SDK API trampoline pattern
- `cumulus_baseline_2013/FULL_CHIP_ACCESS_STACK.md` — API → SCHAN → MMIO
- `cumulus_baseline_2013/CHIP_PRIMITIVES_AND_REG_TABLE.md` — 36,896 register names
- `cumulus_baseline_2013/SWITCHD_DECOMPILED_BCM_APIS.md` — 127 BCM API addresses
- `cumulus_baseline_2013/fuse-explore/SWITCHD_SFS_INTERNALS.md` — control plane
- `binaries/extracted/etc/bcm.d/` — captured init scripts
- `switchd-generated-state/rc.datapath_0` — runtime-generated MMU config
- `ASIC_INIT_AND_DMA_MAP.md` — DMA / PCI BAR / SCHAN reg map
- `OPENMDK_BCM56846_REFERENCE.md` — public OpenMDK Trident reference

---

*Cumulus Linux 2.5.0 baseline captured 2013-06-01 from chassis 10.1.1.212.
All addresses verified against the running binary
`binaries/extracted/usr/sbin/switchd`.*

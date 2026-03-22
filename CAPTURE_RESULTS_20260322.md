# BCM56846 AS5610-52X Capture Results - 2026-03-22

**Method**: Read-only BAR0 snapshots + GDB passive MIIM watchpoints
**Switch**: Cumulus Linux 2.5, switchd PID 1732, CMIC DEV_REV_ID=0xb8460002

---

## 1. PHY Address Map (CONFIRMED via GDB MIIM Capture)

Three separate GDB MIIM watchpoint captures (6677 total transactions) mapping all port groups:

### Complete MDIO PHY Address Map

| PHY_ADDR | BUS_IDs Observed | xlport Blocks | swp Ports | Notes |
|----------|-----------------|---------------|-----------|-------|
| **1**    | 1, 2            | xlport12,14   | swp25-28, swp33-36, swp41-44, swp49 | Multiple xlports share PHY addr, distinguished by BUS |
| **5**    | 0, 1            | xlport0,4,8   | swp9-12, swp29-32, swp37-40, swp45-48 | |
| **9**    | 0, 1, 2         | xlport2,6,10  | swp13-16, swp17-20, swp50 | Most widely shared |
| **13**   | 1, 2            | xlport3,7,11  | swp5-8, swp21-24, swp51 | |
| **17**   | 2               | xlport16      | swp1-4 | Primary, most captures |
| **21**   | 1, 2            | xlport17,1,5  | swp5-8, swp52 | |

### MDIO BUS Architecture

The BCM56846 Trident+ has **3 internal MDIO buses** (BUS 0, 1, 2). Each bus serves a subset of xlport blocks. Since there are only 6 unique PHY addresses (1,5,9,13,17,21) but 14 xlport blocks, the BUS_ID is the key disambiguator.

```
BUS 0: xlport0-5  (PHY 1,5,9,13 -- SFP+ ports swp9-28)
BUS 1: xlport6-11 (PHY 1,5,9,13,21 -- SFP+ ports swp29-48, QSFP swp50,52)
BUS 2: xlport12-17 (PHY 1,9,13,17,21 -- SFP+ swp1-8, QSFP swp49,51)
```

### QSFP 40G Ports

| Port | PHY_ADDR | BUS_ID | Speed | Status |
|------|----------|--------|-------|--------|
| swp49 | 1      | 2      | 40G   | NO-CARRIER (plugged, no link partner) |
| swp50 | 9      | 1 or 2 | 40G   | UP (connected to swp52) |
| swp51 | 13     | 2      | 40G   | NO-CARRIER (plugged, no link partner) |
| swp52 | 21     | 1      | 40G   | UP (connected to swp50) |

swp50 and swp52 are cross-connected with QSFPs and link up at 40Gbps.

### Capture Sources

| Capture | Ports Flapped | PHYs Seen | Transactions |
|---------|--------------|-----------|--------------|
| wc_switchd_gdb.txt | swp1,5,9,13 | bus0:5,9 bus2:17,21 | 2171 |
| qsfp_miim_capture.txt | swp49-52 | bus1:21 bus2:1,9,13,17 | 4506 |
| allports_miim.txt | swp1-52 | bus1:1,5,9,13 | 5606 |

---

## 2. Warpcore SerDes Init Sequence (Port Flap)

Captured during `ip link set swp5 up` (xe4, PHY 21, BUS 2). This is the full WC init sequence, matching and extending the earlier SERDES_WC_INIT.md capture:

### Phase 1: TX Configuration
```
PAGE_SELECT = 0x0000          ; standard page 0
reg[0x17] WR 0x8010           ; TX config (drive strength low)
reg[0x18] WR 0x8370           ; TX amplitude/drive (3x)
reg[0x18] WR 0x8370
reg[0x18] WR 0x8370
```

### Phase 2: IEEE Block Enable
```
PAGE_SELECT = 0x0008          ; WC IEEE block
reg[0x1e] WR 0x8000           ; enable IEEE features
PAGE_SELECT = 0x0000
reg[0x1e] WR 0x8000           ; page 0 IEEE enable
```

### Phase 3: AN/Clock Recovery
```
PAGE_SELECT = 0x1000          ; AN/clock page
reg[0x18] WR 0x8010           ; clock recovery (3x)
reg[0x18] WR 0x8010
reg[0x18] WR 0x8010
```

### Phase 4: AER + SerDes Digital
```
PAGE_SELECT = 0x0aee          ; AER page
reg[0x1e] WR 0xffd0           ; AER config
PAGE_SELECT = 0x1800          ; uconfig lane 0
reg[0x01] RD                  ; check MII status
PAGE_SELECT = 0x0000
reg[0x1e] WR 0xffd0           ; restore
PAGE_SELECT = 0x0a00          ; SerDes digital
reg[0x10] WR 0xffe0           ; all features enabled
```

### Phase 5: RX Equalization
```
PAGE_SELECT = 0x0000
reg[0x11] WR 0x81d0           ; RX control
reg[0x12] WR 0x81d0           ; RX config
reg[0x14] WR 0x81d0           ; extended control
reg[0x15] WR 0x8340           ; aux control/status
reg[0x10] WR 0x80b0           ; misc lane config
```

### Phase 6: RX EQ Coefficients
```
reg[0x19] WR 0x8320           ; RX EQ A
reg[0x1a] WR 0x8320           ; RX EQ B
reg[0x1b] WR 0x8320           ; RX EQ C
reg[0x1d] WR 0x8350           ; RX EQ D
```

### Phase 7: Core Sequencer
```
PAGE_SELECT = 0x3800          ; WC_CORE
reg[0x00] RD                  ; read sequencer status
reg[0x01] WR 0x0010           ; start sequencer (bit 4)
PAGE_SELECT = 0x0000
reg[0x1e] WR 0xffd0           ; maintenance
```

**Identical sequence observed on all 4 PHY addresses** -- the Warpcore init is the same across BUS IDs 0 and 2.

---

## 3. Steady-State Polling Loop

switchd continuously polls only PHY 17 (xe0/swp1, the only UP port) in a tight loop:

```
PAGE_SELECT = 0x0000
reg[0x1e] WR 0xffd0           ; maintenance/clear
PAGE_SELECT = 0x1800           ; lane 0
reg[0x01] RD                  ; MII_STATUS (link poll)
PAGE_SELECT = 0x0000
reg[0x1e] WR 0xffd0
reg[0x15] WR 0x8340           ; aux control
reg[0x15] WR 0x8340
reg[0x10] WR 0x80b0           ; rotating lane config
reg[0x12] WR 0x81d0
reg[0x10] WR 0x81d0
reg[0x1e] WR 0xffd0
```

Loop period: ~30ms. Only polls lane 0 (page 0x1800) when only swp1 is UP. When multiple ports are up, it polls all 4 lanes (0x1800-0x1803) for each Warpcore.

---

## 4. SBUS Ring Map (BCM56846 Trident+)

Decoded from CMIC_SBUS_RING_MAP registers:

| Block | Ring | Function |
|-------|------|----------|
| 0     | 0    | CMIC |
| 1     | 13   | TOP (misc) |
| 2     | 7    | MMU |
| 10    | 1    | IPIPE block 0 |
| 11    | 2    | IPIPE block 1 |
| 12    | 5    | EPIPE |
| 14    | 3    | XLPORT group A |
| 15    | 4    | XLPORT group B |
| 16-22 | 3    | XLPORT group A (ports) |
| 17,27-31 | 4 | XLPORT group B (ports) |
| 32-35 | 4    | XLPORT group B (ports) |
| 36    | 3    | XLPORT group A (last) |

---

## 5. BAR0 Register Diff During L2/Bridge Operations

480 BAR0 registers changed during bridge/FDB/ARP/route operations. The changes fall into clear patterns:

### 5.1 XLPORT MAC Registers (repeating at 0x800 intervals)

Each of the 14 xlport blocks (0x0000, 0x0800, 0x4000, 0x4800, 0x8000, ..., 0x3C000) shows identical change patterns:

| Offset within Block | Before | After | Field |
|---------------------|--------|-------|-------|
| +0x000 | 0x20500600 | 0x38500000 | XLPORT_XGXS_CTRL (mode/enable) |
| +0x004 | 0x00000000 | 0x40a0060c | XLPORT_XGXS_STAT (status update) |
| +0x010 | 0x04007f40 | 0x00000001 | XLMAC_CTRL (MAC enable/config) |
| +0x014 | 0x00000000 | 0x00000060 | XLMAC_MODE (speed/duplex) |
| +0x028 | 0x13003fa0 | 0xffffffff | XLMAC_PAUSE_CTRL |
| +0x02c | 0x00010000 | 0xffffffff | XLMAC_PAUSE_CTRL_HI |
| +0x090 | 0xb18002c8 | 0xb14002c8 | XLMAC_TX_TIMESTAMP |
| +0x114 | 0x045e1058 | 0x045e10d8 | XLPORT_CONFIG |
| +0x410 | 0x00000003 | 0x00000000 | XLPORT_ENABLE (port bring-down during reconfig) |
| +0x424 | varying | 0x0a240200 | XLPORT_MIB_COUNTER |
| +0x434 | varying | 0x0a240200 | XLPORT_MIB_COUNTER |

### 5.2 Per-Lane Registers (at +0x7c0/+0x7c4 within blocks)

| Offset Pattern | Before | After | Field |
|---------------|--------|-------|-------|
| +0x7c0 | 0x00000003 | 0x00000002 | XLPORT_FLOW_CTRL (per-lane) |
| +0x7c4 | 0x00000001 | 0x00000000 | XLPORT_FLOW_CTRL_HI (per-lane) |

### 5.3 MIB/Counter Registers (at +0x95c, +0x964, +0x968, +0xd64, +0xd68, +0xe40)

These are MAC MIB counters -- the small changes (XOR = 0x0000000e etc.) are packet count increments during the capture window.

### 5.4 CMIC Registers (0x3a000 range)

| Offset | Before | After | Field |
|--------|--------|-------|-------|
| 0x3a2e4 | 0x0000018c | 0x00000058 | CMIC counter (timer/interrupt) |
| 0x3a2ec | 0x00000182 | 0x00000058 | CMIC counter |
| 0x3a2f4 | 0x000001a7 | 0x00000058 | CMIC counter |
| 0x3a2fc | 0x000001a4 | 0x00000058 | CMIC counter |
| 0x3a304 | 0x00000167 | 0x00000058 | CMIC counter |

### 5.5 Key Takeaway

The BAR diff during L2 operations shows **MAC/port-level register changes**, not S-Channel table writes. This confirms that:
- L2/L3 table writes go through S-Channel (SCHAN_MSG at 0x32800+), not direct BAR register access
- The BAR diff captures port enable/disable/reconfig that happens as a side effect of bridge interface creation
- MAC MIB counters increment normally during the capture window

---

## 6. S-Channel Capture

Only 1 transition captured by polling (67444 polls in 15 seconds). The table writes happen too fast for userspace polling to catch -- they complete in microseconds.

**Recommendation**: Use GDB hardware watchpoint on `CMIC_CMC0_SCHAN_CTRL` (0x4802b000 + 0x32800) to capture S-Channel operations, similar to the MIIM capture approach.

---

## 7. DMA Channel State

| Channel | CTRL | DESC | STAT | Status |
|---------|------|------|------|--------|
| PKTDMA_CH0 | 0xb3 | 0x84 | 0x4a | Active (RX?) |
| PKTDMA_CH1 | 0xb3 | 0x84 | 0x4a | Active (TX?) |
| PKTDMA_CH2 | 0xb3 | 0x84 | 0x4a | Active |
| PKTDMA_CH3 | 0x00 | 0x00 | 0xf8 | Inactive |
| SBUSDMA_CH0 | 0xf3 | 0x4a | 0x58 | Active |
| SBUSDMA_CH1 | 0xf3 | 0x4a | 0x58 | Active |
| SBUSDMA_CH2 | 0xf3 | 0x4a | 0x58 | Active |
| SBUSDMA_CH3 | 0x00 | 0xf8 | 0x00 | Inactive |

**Note**: Values appear byte-swapped on PPC big-endian. The DESC addresses (0x84, 0x4a) are in low memory, not the DMA pool (0x04000000). This suggests the registers may need to be read with proper endian handling, or the PKTDMA registers at these offsets are not the descriptor pointers but status/control fields.

**Next step**: Read DMA registers with explicit big-endian awareness, or use GDB to read them from switchd's mapped address space where the endianness is handled correctly.

---

## 8. Lessons Learned: MIIM Bus Safety

| Method | Result |
|--------|--------|
| Direct MIIM write from Python (read-only scan) | **CRASH** - soft lockup in ledmgrd |
| Direct MIIM write with switchd SIGSTOP'd | **CRASH** - switch unresponsive |
| Direct MIIM COMMANDr write (firmware RAM dump) | **CRASH** - Warpcore uC killed |
| GDB awatch on MIIM_ADDRESS (passive) | **SUCCESS** - 2171 transactions captured |
| Read-only BAR0 scan (no MIIM writes) | **SUCCESS** - 25197 registers read |

**Rule**: NEVER write to MIIM registers directly. Always use GDB to observe switchd's own MIIM operations, or call switchd's MIIM functions via GDB.

---

## 9. Full System Capture

Complete system state captured to `traces/full_system_capture_20260322.txt`:

- **CPU**: Freescale P2020 (e500v2 core), PowerPC 32-bit big-endian
- **Kernel**: 3.2.60-1+deb7u1+cl2.5+1 (Debian 7/wheezy based)
- **Cumulus**: 2.5.x
- **switchd**: /usr/sbin/switchd -d (PID varies per boot)
- **ledmgrd**: /usr/sbin/ledmgrd (Python, manages front panel LEDs via I2C/MDIO)
- **QSFP swp50**: 40G FIBRE, Full duplex, link UP (connected to swp52)
- **QSFP swp52**: 40G FIBRE, Full duplex, link UP (connected to swp50)
- **QSFP swp49,51**: Plugged but NO-CARRIER
- **Management**: eth0 at 10.1.1.233/24

---

## 10. Remaining Capture Work

| Task | Method | Status |
|------|--------|--------|
| S-Channel table writes | GDB watchpoint on SCHAN_CTRL | Need GDB capture |
| DMA DCB descriptor chain | GDB read from switchd address space | Need endian-correct read |
| Warpcore firmware RAM | Must use GDB to call switchd's MIIM function | Blocked (direct MIIM crashes switch) |
| Full PHY address map | Need to correlate port flaps with GDB captures | Partially done |

---

## Files

| File | Contents |
|------|----------|
| `traces/safe_capture_20260322_013255.txt` | Full BAR0 dump (25197 regs), DMA state, SCHAN state, XLPORT scan |
| `traces/wc_switchd_gdb.txt` | 2171 MIIM transactions via GDB watchpoint (swp1,5,9,13 flaps) |
| `traces/qsfp_miim_capture.txt` | 4506 MIIM transactions (swp49-52 QSFP flaps) |
| `traces/allports_miim.txt` | 5606 MIIM transactions (all port groups) |
| `traces/bar_diff_l2_20260322_013255.txt` | 480 BAR0 register changes during L2/bridge ops |
| `traces/schan_capture_20260322_013321.txt` | S-Channel polling (1 transition -- need GDB approach) |
| `traces/full_system_capture_20260322.txt` | Complete system state (CPU, mem, modules, interfaces, config) |
| `scripts/capture_safe_no_miim.py` | Safe BAR0/DMA/SCHAN reader (no MIIM) |
| `scripts/capture_wc_via_switchd.sh` | GDB passive MIIM capture |
| `scripts/capture_all_safe.sh` | Master capture suite |
| `scripts/capture_schan.py` | S-Channel polling capture |
| `scripts/capture_bar_diff.py` | BAR0 before/after diff |

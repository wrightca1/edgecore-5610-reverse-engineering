# Warpcore TX Driver Configuration (Captured from Cumulus 2.5.1)

## Capture Method

GDB breakpoints on `soc_miim_write` (0x1082fabc) and `soc_miim_read` (0x10830b78)
in switchd during port flap of swp1 (10G SFP+) and swp50 (40G QSFP loopback).

- Date: March 27, 2026
- Switch: AS5610-52X at 10.1.1.242
- Cumulus: 2.5.1-powerpc
- Capture: `traces/gdb_miim_capture_20260327.log` (6421 lines, 2648 writes, 946 reads)

## PHY ID Encoding

Cumulus uses internal MIIM bus encoding in the `phy_id` parameter:

| phy_id | Decode               | Warpcore | Ports         |
|--------|----------------------|----------|---------------|
| 0x00b5 | port 21 + bus 2<<5   | WC5      | swp49-52 (QSFP 40G) |
| 0x00c1 | port 1 + bus 3<<5    | WC0      | swp1-4        |
| 0x00c9 | port 9 + bus 3<<5    | WC2      | swp9-12       |
| 0x00cd | port 13 + bus 3<<5   | WC3      | swp13-16      |
| 0x00d1 | port 17 + bus 3<<5   | WC4      | swp17-20      |

Encoding: `phy_id = physical_port + (miim_bus << 5)` where bus 2 = 0xa0, bus 3 = 0xc0.

## Warpcore Block Select (AER)

All multi-register operations use block select via CL22 reg 0x1F:

```
MIIM_WRITE reg=0x1f data=<block_addr>   // Select block
MIIM_WRITE reg=<offset> data=<value>    // Write register within block
```

Lane selection uses AER register at block 0xFFD0, reg 0x1E:

```
MIIM_WRITE reg=0x1f data=0xffd0         // Select AER block
MIIM_WRITE reg=0x1e data=0x18XX         // XX = lane (00-03) or broadcast
```

AER lane encoding:
- 0x1800 = lane 0
- 0x1801 = lane 1
- 0x1802 = lane 2
- 0x1803 = lane 3
- 0x0000 = broadcast (all lanes)

## Block Map (from capture)

| Block  | Name                    | Purpose                    |
|--------|-------------------------|----------------------------|
| 0x0000 | IEEE                    | Standard MII registers     |
| 0x0010 | IEEE extended           | AN/speed registers         |
| 0x8000 | XGXSBLK0               | Top-level status/control   |
| 0x8010 | XGXSBLK1               | Extended status            |
| 0x80B0 | MICROBLK0              | Firmware control           |
| 0x80C0 | MICROBLK1              | Firmware status            |
| 0x8130 | TXLN_MISC              | TX lane miscellaneous      |
| 0x81D0 | RXLN_MISC              | RX lane status             |
| 0x81F0 | RXLN_CTRL              | RX lane control            |
| 0x8300 | DIGITAL                | SerDes digital control     |
| 0x8320 | DIGITAL3               | Speed/mode control         |
| 0x8340 | DIGITAL4               | Extended speed control     |
| 0x8350 | DIGITAL5               | Force speed/mode           |
| 0x8370 | TX_ANATXACONTROL       | **TX analog driver config**|
| 0xFFD0 | AER                    | Address Extension Register |
| 0xFFE0 | COMBO_IEEE0            | Combo IEEE registers       |

## TX Driver Configuration

### 10G SFP+ Port (phy 0xd1, swp17-20 area)

Register writes in block 0x8370 (TX analog control):

```
Block 0x8370, reg 0x18 (TX_ANATXACONTROL6) = 0x0ACC
  Bits [15:12] = 0x0  (reserved)
  Bits [11:8]  = 0xA  (idriver = 10)
  Bits [7:4]   = 0xC  (ipredriver = 12)
  Bits [3:0]   = 0xC  (post2 = 12)

Block 0x8370, reg 0x10 (TX_ANATXACONTROL0) = 0x000E
  TX FIR enable and mode bits

Block 0x8370, reg 0x15 (TX_ANATXACONTROL5) = 0x0002
  TX FIR coefficient
```

### 40G QSFP Port (phy 0xb5, swp49-52)

```
Block 0x8370, reg 0x18 (TX_ANATXACONTROL6) = 0x0AFF
  Bits [11:8]  = 0xA  (idriver = 10)
  Bits [7:4]   = 0xF  (ipredriver = 15)
  Bits [3:0]   = 0xF  (post2 = 15)

Block 0x8370, reg 0x18 also written with 0x0200:
  Bits [11:8]  = 0x2  (idriver = 2) — possibly intermediate/reset value
```

### Comparison with OpenMDK defaults

| Parameter    | OpenMDK default | Cumulus 10G | Cumulus 40G |
|-------------|-----------------|-------------|-------------|
| idriver     | 0 (no drive!)   | 10 (0xA)    | 10 (0xA)    |
| ipredriver  | 0               | 12 (0xC)    | 15 (0xF)    |
| post2       | 0               | 12 (0xC)    | 15 (0xF)    |
| TX FIR      | disabled        | 0x000E      | 0x000E      |
| FIR coeff   | 0               | 0x0002      | —           |

**This confirms OpenMDK leaves TX driver at zero — no optical output.**

## Port Flap Sequence (10G)

Complete register sequence during `ip link set swp1 down && ip link set swp1 up`:

### Per-lane (repeated for lanes 0-3):

```
1. AER select lane N:
   reg 0x1f = 0xffd0, reg 0x1e = 0x180N

2. Check link status:
   reg 0x1f = 0x0000, READ reg 0x01 (MII_STATUS)

3. Clear force speed:
   reg 0x1f = 0x8340, reg 0x15 = 0x0000

4. Read firmware status:
   reg 0x1f = 0x80b0, READ reg 0x10
   reg 0x1f = 0x81d0, READ reg 0x12, READ reg 0x10

5. Configure TX pre-emphasis (per lane):
   reg 0x1f = 0x8370, READ reg 0x18
   reg 0x1f = 0x8370, reg 0x18 = 0x0008  (intermediate)
   reg 0x1f = 0x8370, READ reg 0x18
   reg 0x1f = 0x8370, reg 0x18 = 0x0000  (clear)
   reg 0x1f = 0x8370, reg 0x10 = 0x000e  (TX FIR enable)
   reg 0x1f = 0x8370, READ reg 0x11

6. Set TX amplitude:
   reg 0x1f = 0x8370, reg 0x18 = 0x0ACC  (idriver=10, ipre=12, post2=12)
```

### After all lanes:

```
7. AER broadcast (all lanes):
   reg 0x1f = 0xffd0, reg 0x1e = 0x0000

8. Set speed mode:
   reg 0x1f = 0x8300, reg 0x10 = (speed bits)
   reg 0x1f = 0x8340, reg 0x15 = 0x0002  (force speed enable)
```

## Implementation Notes for EdgeNOS

1. TX driver values must be written AFTER firmware has initialized (FW_VER != 0)
2. Use AER lane select (block 0xFFD0, reg 0x1E) before per-lane writes
3. Write TX_ANATXACONTROL6 (block 0x8370, reg 0x18) with 0x0ACC for 10G, 0x0AFF for 40G
4. Write TX_ANATXACONTROL0 (block 0x8370, reg 0x10) with 0x000E to enable TX FIR
5. These are NOT firmware mailbox commands — they are direct MIIM register writes
6. The "firmware mailbox" concern from WC40-TX-DRIVER-ANALYSIS.md was incorrect;
   Cumulus writes TX driver config via standard CL22 block access, same as other regs

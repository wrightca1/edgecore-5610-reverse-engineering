# Warpcore Speed Encoding Analysis (BCM56846 / AS5610-52X)

## Discovery Timeline (March 28, 2026)

### Problem
Front-panel SFP+ ports have optical TX/RX power but PCS never achieves
block lock (pcs=0x0082). Ports stay at link=0 despite Warpcore PLL locked
and firmware v0x0101 loaded.

### Key Findings

#### 1. MIIM Block Access Works
After clearing PHY_F_CLAUSE45 and using `phy_bus_bcm56840_miim_int`:
- XGXSSTATUS (blk 0x8000) = 0x242F ✓
- MISC1r (blk 0x8300) = 0x7A05 — readable and writable
- Write 0xBEEF reads back 0xBEEF — register writes persist
- Block select (reg 0x1F = 0x8300) works correctly

#### 2. MISC1r FORCE_SPEED Is Intentionally Zero
The OpenMDK Warpcore driver (`bcmi_warpcore_xgxs_drv.c` lines 822-829)
**intentionally clears** MISC1r FORCE_SPEED and MISC3r FORCE_SPEED_B5
during `_warpcore_init_stage_1`:

```c
/* Clear forced speed setting */
ioerr += READ_MISC1r(pc, &misc1);
MISC1r_FORCE_SPEEDf_SET(misc1, 0);      // Clear bits [4:0]
ioerr += WRITE_MISC1r(pc, misc1);

ioerr += READ_MISC3r(pc, &misc3);
MISC3r_FORCE_SPEED_B5f_SET(misc3, 0);   // Clear bit 7
ioerr += WRITE_MISC3r(pc, misc3);
```

MISC1r/MISC3r FORCE_SPEED is only used for:
- 2-lane (DXGXS) ports with PHY_F_CUSTOM_MODE
- NOT for single-lane 10G XFI

#### 3. 10G XFI Uses Firmware Mode
For single-lane 10G ports, the speed encoding goes through:
- **FIRMWARE_MODEr** (block 0x8200, offset 0x0A) — per-lane 4-bit nibbles
- **SerDes digital control registers** (CONTROL1000X1, CONTROL1000X3)
- **ind_40bitif** flag (40-bit interface mode for XFI)

From `bcmi_warpcore_xgxs_speed_set()` line 1385-1394:
```c
if (PHY_CTRL_LINE_INTF(pc) == PHY_IF_SFI) {
    speed_val = FV_fdr_10G_SFI;       // 0x29
    fw_mode |= LSHIFT32(2, 4 * lane); // SFP_DAC mode = 2
} else {
    speed_val = FV_fdr_10G_XFI;       // 0x25
    // fw_mode stays at 0 for this lane
}
ind_40bitif = 1;
```

#### 4. Current Register State on EdgeNOS

| Register | Value | Meaning |
|----------|-------|---------|
| XGXSSTATUS (0x8000.10) | 0x242F | Firmware v0x242F running |
| MISC1r (0x8300.18) | 0x7A05 | FORCE_SPEED[4:0]=5, REFCLK=3, PLL_MODE=0xA |
| MISC3r (0x8350.18) | 0x0000 | FORCE_SPEED_B5=0, LANEDISABLE=0 |
| FIRMWARE_MODEr (0x8200.1A) | 0x0063 | lane0=3, lane1=6, lane2=0, lane3=0 |
| MISC6r (0x8340.15) | 0x0000 | force_speed_sel=0 (force speed NOT active) |
| MII_STATUS (reg 1) | 0x0109 | link=0, autoneg capable |
| PCS_STATUS | 0x0082 | block_lock=0, PCS capable |

#### 5. FIRMWARE_MODEr Decode (0x0063)

Each lane has 4 bits in FIRMWARE_MODEr:
```
0x0063 = 0000 0000 0110 0011
         lane3  lane2  lane1  lane0
         = 0     0      6      3
```

Firmware mode values:
- 0 = default/AN
- 1 = SFP_OPT (optical SFP)
- 2 = SFP_DAC (direct attach copper)
- 3 = XFI/KR (clause 72 training)
- 4 = force speed
- ...

Lane 0 = 3 (XFI/KR mode) — this might be correct for XFI.
Lane 1 = 6 — unknown, may be wrong.

### Comparison Needed with Cumulus

From the GDB capture (`gdb_miim_capture_20260327.log`), Cumulus writes to
FIRMWARE_MODEr during port init. Need to extract the exact values:

```
# Find FIRMWARE_MODEr writes in Cumulus capture:
# Block 0x8200, reg 0x0A → CL22 block select 0x8200, reg 0x1A
grep "data=0x8200" gdb_miim_capture_20260327.log
# Then look at the next write to reg 0x1A
```

### Why PCS Doesn't Lock

With FORCE_SPEED disabled (force_speed_sel=0), the Warpcore uses
firmware-controlled speed mode. The firmware (v0x0101 from OpenMDK)
reads FIRMWARE_MODEr to determine the encoding mode per lane.

If FIRMWARE_MODEr lane values are wrong, the firmware configures the
wrong PCS encoding:
- CX4 (8b/10b, 4-lane) — PCS expects XAUI-style block sync
- XFI (64b/66b, single-lane) — PCS expects 66-bit block sync

The SFP+ optics transmit 64b/66b. If the Warpcore is in 8b/10b mode,
PCS will never achieve block lock.

## Register Map Reference

### MISC1r (block 0x8300, CL22 reg 0x18)
```
Bits [15:13] REFCLK_SEL
Bit  [12]    FORCE_PLL_MODE_AFE_SEL
Bits [11:8]  FORCE_PLL_MODE_AFE
Bit  [7]     FORCE_TICK0_SW2
Bit  [6]     TX_UNDERRUN_1000_DIS
Bit  [5]     FORCE_LN_MODE
Bits [4:0]   FORCE_SPEED (lower 5 bits of speed_val)
```

### MISC3r (block 0x8350, CL22 reg 0x18)
```
Bit  [7]     FORCE_SPEED_B5 (bit 5 of speed_val)
Bit  [3]     LANEDISABLE
```

### MISC6r (block 0x8340, CL22 reg 0x15)
```
Bit  [6]     FORCE_SPEED_SEL (1=use MISC1r/MISC3r force speed)
```

### FIRMWARE_MODEr (block 0x8200, CL22 reg 0x1A)
```
Bits [15:12] Lane 3 firmware mode
Bits [11:8]  Lane 2 firmware mode
Bits [7:4]   Lane 1 firmware mode
Bits [3:0]   Lane 0 firmware mode

Values per lane:
  0 = default (auto-negotiation)
  1 = SFP_OPT (optical SFP)
  2 = SFP_DAC (direct attach copper)
  3 = XFI/KR (with clause 72 training)
  4 = force speed (from MISC1r/MISC3r)
```

### Speed Values (FV_fdr_*)
```
0x05 = 10GBASE-CX4 (4-lane 8b/10b) — WRONG for SFP+
0x14 = 10GBASE-CX4 (alternative)
0x20 = 10G_DXGXS (2-lane)
0x25 = 10G_XFI (single-lane 64b/66b) — CORRECT for SFP+
0x29 = 10G_SFI (SFP+ fiber)
```

## CRITICAL CORRECTION (March 30, 2026)

Our debug reads were using WRONG register addresses!

| Register | CDK Address | Correct CL22 | What we read | What we read was |
|----------|-------------|---------------|-------------|------------------|
| MISC1r | 0x8308 | blk 0x8300 reg 0x18 | blk 0x8300 reg 0x18 | **CORRECT** |
| MISC3r | 0x833C | blk 0x8330 reg 0x1C | blk 0x8350 reg 0x18 | LP_OUI_MSB_FIELDr (WRONG!) |
| MISC6r | 0x8349 | blk 0x8340 reg 0x19 | blk 0x8340 reg 0x15 | Wrong offset |

The `speed_set` code (lines 1488-1497 of xgxs_drv.c) DOES write:
- MISC1r FORCE_SPEED = 0x05 (bits [4:0] of 0x25)
- MISC3r FORCE_SPEED_B5 = 1 (bit 5 of 0x25)
- MISC3r IND_40BITIF = 1 (40-bit interface for XFI)

We couldn't verify MISC3r because we were reading the wrong register.
The speed encoding may actually be correct. The PCS no-lock issue
may be caused by something else entirely (TX driver, retimer, or
link partner configuration).

## Next Steps

1. Fix debug code to read correct MISC3r (blk 0x8330 reg 0x1C)
2. Verify MISC3r actually has FORCE_SPEED_B5=1
3. If speed is correct, investigate other causes of PCS no-lock
4. Install Cumulus to verify SFPs still work (rule out hardware)
5. Extract FIRMWARE_MODEr value from Cumulus GDB capture
2. Compare lane-by-lane firmware mode settings
3. If firmware mode is wrong, either:
   a. Fix the OpenMDK driver's firmware mode assignment
   b. Manually write correct FIRMWARE_MODEr after init
4. After firmware mode is correct, verify PCS block lock
5. If PCS locks, verify link-up and test packet forwarding

## Files

- `traces/gdb_miim_capture_20260327.log` — Full MIIM capture from Cumulus
- `traces/gdb_misc1r_capture_20260328.log` — Block-select capture from Cumulus
- `newnos/asic/switchd/portmap.c` — Debug logging for register readback

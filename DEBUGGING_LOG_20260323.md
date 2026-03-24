# EdgeNOS Debugging Log - March 23, 2026

## Session Summary

### Fixes Applied (all working)
1. **DMA mmap**: vm_pgoff=0 in kernel, offset=0 in userspace
2. **SDK DMA**: BMD_CONFIG_INCLUDE_DMA=1 in mdk-init/Makefile
3. **Port mapping**: All BMD calls use physical_lane (CDK port) not logical_port
4. **ONIE installer**: tar payload format
5. **Platform-init**: Module path fallback to /usr/lib/modules/extra/
6. **DMA pool reset**: bde_dma_pool_reset() after BMD init
7. **BMD_PST_LINK_UP**: Manual force in link poll
8. **10G mode for all ports**: Avoids DCFG_40G disabling sub-ports

### Current State
- 52 ports configured (10G), TUN interfaces created
- ASIC init succeeds (reset + init + switching_init)
- DMA engine initialized (CMIC_CONFIG SG enabled, RX channel active)
- QSFP carrier=1 (physical link detected by kernel)
- TX packets silently dropped (BMD_PST_LINK_UP never set)

### Root Cause: iProc PAXB Register Access Issue
**CRITICAL**: Writes to CMIC_SCHAN_CTRL (0x50) and CMIC_DMA_STAT (0x104)
have NO EFFECT through the BDE kernel module's iowrite32 path.

Evidence:
- `read_reg(0x50)` = 0x00400002 (TIMEOUT + MSG_DONE latched)
- `write_reg(0x50, 0x00)` → readback still 0x00400002
- `write_reg(0x50, 0x80)` → readback still 0x00400002 (MIIM read not triggered)
- Other registers (0x100 DMA_CTRL, 0x10C CONFIG, 0x158 MIIM_PARAM) write OK

PAXB state:
- PAXB_ENDIAN (0x2030) = 0xF2 (not 0x00 or 0x01 - invalid/corrupt)
- IMAP0_0-6 = 0xF8/0x80 alternating (not valid)
- All addresses > 0x8000 return 0x62 (sub-window mapping broken)

### Impact Chain
1. SCHAN_CTRL write fails → MIIM reads can't be triggered
2. MIIM fails → bmd_phy_link_get returns no link
3. No link → BMD_PST_LINK_UP never set
4. No link flag → bmd_tx silently drops all packets (return CDK_E_NONE)
5. No TX DMA → no L2 switching → no ping

### Paradox
bmd_init() succeeds (which uses S-Channel heavily via SCHAN_CTRL).
This means SCHAN_CTRL writes DID work during init. The register
became stuck AFTER init completed, from a timed-out S-Channel
operation that left TIMEOUT + MSG_DONE latched.

### Next Steps
1. Check if Cumulus BDE uses __raw_writel instead of iowrite32 for SCHAN_CTRL
2. Check OpenMDK shbde_iproc.c iproc32_write implementation
3. May need to handle SCHAN timeout recovery in the main loop
4. Or: prevent the S-Channel timeout during bmd_switching_init
5. Consider reading SCHAN_CTRL immediately after each BMD init step
   to identify which operation causes the timeout

## Session 2: March 24, 2026 - MIIM Write Root Cause

### MIIM Bus Architecture Discovery

BCM56846 internal PHY (Warpcore) MIIM addressing:
- `CDK_XGS_MIIM_IBUS(bus) = ((bus << 6) | 0x200)` 
- PHY address = `port_number + CDK_XGS_MIIM_IBUS(bus_number)`
- Port 65 (swp1): `phy = 65 + 0x200 = 0x241`
- MIIM_PARAM bit 25 = INTERNAL_SEL (selects internal MDIO bus)
- BCM56840 has `CDK_XGS_CHIP_FLAG_CLAUSE45`: CL22 reg goes to CMIC_MIIM_ADDRESS (0x4a0), not MIIM_PARAM

### SCHAN_CTRL Bit-Command Protocol

SCHAN_CTRL (0x50) uses bit-set/clear commands:
- Write `(0x80 | N)` to SET bit N
- Write `(0x00 | N)` to CLEAR bit N
- `SC_MSG_START_SET = 0x80` (set bit 0) - S-Channel message start
- `SC_MIIM_RD_START_SET = 0x90` (set bit 16) - MIIM read trigger
- `SC_MIIM_WR_START_SET = 0x91` (set bit 17) - MIIM write trigger
- `SC_MIIM_OP_DONE_TST = 0x00040000` (bit 18) - MIIM completion flag

### ROOT CAUSE: MIIM Write Bit 17 Cannot Be Triggered

Systematic test of all values 0x80-0x9F written to SCHAN_CTRL:
```
0x80 → bits [1] (MSG_DONE from S-Channel op)
0x90 → bits [1, 15, 18] (MIIM_RD_START triggers, DONE set)
0x91 → bits [1, 15, 18] (SAME as 0x90! WR_START NOT set)
```

**MIIM_WR_START (bit 17) NEVER appears in SCHAN_CTRL readback**, regardless of:
- Direct bit write (0x00020000)
- Bit-command write (0x91)
- Any other value tested

MIIM READ (bit 16) works correctly. MIIM WRITE (bit 17) does not.

### Impact

All Warpcore register writes during `bmd_init()` silently failed:
- Firmware download: all MIIM writes to Warpcore RAM were no-ops
- Speed configuration: MISC1, MISC3, FIRMWARE_MODE writes ignored
- AER block select: writes went through but reads returned stale data
- COMMANDr: firmware control never set (FW_VER=0, RUN=0, MDIO_UC_RESET_N=0)
- PLL: never locked (TXPLL_LOCK=0 in XGXSSTATUS1)
- Result: all ports show link=0, bmd_tx silently drops all packets

### Warpcore State After bmd_init

```
PHY_ID0 = 0x0143 (Broadcom WC-B0 responds to CL22 IEEE reads)
PHY_ID1 = 0xBFF0
MII_STATUS = 0x0109 (extended caps, no link)
FW_VER = 0x0000 (firmware not loaded!)
COMMANDr = 0x0000 (8051 not running, MDIO not released)
XGXSSTATUS1 = 0x0000 (PLL not locked, no link on any lane)
Block select: works on fresh ASIC, may break after repeated reads
```

### iProc PAXB Sub-Window Limitation

- IMAP0_7 register at 0x2C1C: only 8 writable bits (0xFF max)
- Cannot remap sub-windows to arbitrary AXI addresses
- iProc MDIO controller at AXI 0x18032000 is unreachable through BAR0
- PAXB CONFIG_IND_ADDR/DATA (0x2120/0x2124) returns 0 for all addresses
- BCM56846 has only BAR0 (256KB), no BAR1/BAR2

### Retimer Programming

DS100DF410 retimers successfully programmed via I2C:
- Buses 11-14, address 0x27
- Registers: 0xFF=channel(12), 0x15=VEO(1), 0x1E=DFE(0), 0x17=EQ(0x40), 0x0A=CDR(0x1C→0x10)
- CL22 MII_STATUS shows 0xFFFF after retimer init (aggregate, not per-lane)
- But per-lane link still 0 because Warpcore PLL not locked

### Next Steps

1. Boot Cumulus on the switch and capture MIIM write register access
2. Compare Cumulus BDE's SCHAN_CTRL writes with ours
3. Look for PCIe extended capabilities or alternate MDIO path
4. Check if Cumulus uses a different PAXB initialization sequence
5. Investigate if there's a S-Channel opcode for indirect MIIM write

## Session 3: March 24, 2026 - Raw Access Breakthrough

### Cumulus BDE Analysis (Definitive)

Disassembly of extracted Cumulus linux-kernel-bde.ko:
```
_iproc_write (0x2EDC): uses stwx (raw PPC store, NO byte-swap)
_iproc_read  (0x2F84): uses lwzx (raw PPC load, NO byte-swap)
```

This is fundamentally different from our iowrite32/ioread32 which do:
- iowrite32 = out_le32 = stwbrx (byte-reversed store)
- ioread32 = in_le32 = lwbrx (byte-reversed load)

### iproc_map_default Data Structure

Found at .data offset 0x120 in Cumulus BDE:
```
AXI range 1: 0x18000000 - 0x18000FFF (CMIC base registers)
AXI range 2: 0x18030000 - 0x18030FFF (CMICm: SCHAN, DMA, MIIM)
AXI range 3: 0x18012000 - 0x18012FFF (XLPORT/MAC registers?)
```

### MIIM Write Confirmed Working

With __raw_writel and manual byte-swap:
```
1. Write MIIM_ADDRESS (0x4A0) with reg 0x1F (byte-swapped)
2. Write MIIM_PARAM (0x158) with phy_addr + data (byte-swapped)
3. Write SCHAN_CTRL (0x50) with 0x91000000 (BE encoding of MIIM_WR_START)
4. MIIM_OP_DONE fires, readback confirms write reached Warpcore
```

Block select 0xFFD0 written and read back correctly = **first successful MIIM write to Warpcore PHY**.

### Remaining Issue: S-Channel

CDK S-Channel operations still fail because:
1. CDK uses CMIC_SCHAN_CTRLr at 0x50 (old CMIC address)
2. BCM56846 CMICm S-Channel is at 0x33000 (CMC2)
3. S-Channel MSG_START written to 0x50 triggers the old CMIC which may not be functional
4. Need to either remap in BDE or patch CDK to use CMC2 addresses

### Key Insight: SYS_BE_PIO + Raw Access

With __raw_writel on PPC:
- CPU stores native big-endian bytes to PCIe MMIO
- ASIC reads these as little-endian (byte-swapped)
- CDK's SYS_BE_PIO=1 pre-swaps values to compensate
- Result: ASIC sees the correct LE value
- PAXB endianness register (0x2030) = 0xF2 and cannot be changed

### BDE Differences: Cumulus vs OpenMDK

| Aspect | Cumulus BDE | Our BDE (before fix) | Our BDE (after fix) |
|--------|------------|---------------------|-------------------|
| MMIO access | __raw_readl/__raw_writel (stwx/lwzx) | ioread32/iowrite32 (stwbrx/lwbrx) | __raw_readl/__raw_writel |
| MIIM write | Works (raw bytes on bus) | FAILS (byte-swap corrupts bit-command) | WORKS |
| S-Channel | Uses CMC2 at 0x33000 | Uses old CMIC at 0x50 | Uses old CMIC at 0x50 (broken) |
| PAXB init | PCI config space writes | iowrite32 to BAR0 | __raw_writel to BAR0 |
| Sub-windows | iproc_map with 3 AXI ranges | Only IMAP7 for high regs | Only IMAP7 (same) |
| Userspace | mmap BAR0 directly | ioctl to kernel BDE | ioctl to kernel BDE |

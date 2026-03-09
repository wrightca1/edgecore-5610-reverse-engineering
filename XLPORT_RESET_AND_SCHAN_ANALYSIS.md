# XLPORT Reset and SCHAN Analysis for BCM56846 (Trident+)

## Summary

XLPORT SCHAN operations (Phase 7 of datapath init) fail with status=-5
(EIO = TIMEOUT/NAK in SCHAN_CTRL). Root cause investigation traced through
OpenMDK CDK/BMD source code for BCM56840 (the reference chip for the
BCM56846/Trident+ family).

## Critical Finding: BCM56840/56846 Does NOT Have TOP_SOFT_RESET_REG

**BCM56850 (Trident2) and later** use `TOP_SOFT_RESET_REGr` at CDK address
`0x02030400`, accessed via SCHAN to the TOP block (physical block 57).
The register uses active-LOW fields (`_RST_L` suffix): bit=1 means OUT of
reset, bit=0 means IN reset.

**BCM56840/56846 (Trident+)** does NOT have `TOP_SOFT_RESET_REGr` in CDK.
Instead, it uses `CMIC_SOFT_RESET_REGr` at **BAR0+0x580** — a direct CMIC
register accessed via PCI BAR0 reads/writes, NOT via SCHAN.

### Evidence

1. `grep -r TOP_SOFT_RESET_REG OpenMDK/cdk/PKG/chip/` returns matches for
   bcm56850, bcm56860, bcm56960, bcm56640, bcm56560, bcm56450, bcm56440,
   bcm56340, bcm56270, bcm56260, bcm56160, bcm56150, bcm53400 — but
   **NOT bcm56840**.

2. `OpenMDK/bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_reset.c` uses
   `CMIC_SOFT_RESET_REGr` (not TOP_SOFT_RESET_REGr) for all block resets.

3. `OpenMDK/cdk/PKG/chip/bcm56840/bcm56840_a0_defs.h` defines:
   ```c
   #define BCM56840_A0_CMIC_SOFT_RESET_REGr 0x00000580
   ```

## CMIC_SOFT_RESET_REG (BAR0+0x580) Bit Layout

All fields are active-LOW (`_RST_L`): 1 = OUT of reset, 0 = IN reset.

| Bit | Field | Description |
|-----|-------|-------------|
| 0 | CMIC_PG0_RST_L | Port group 0: xlport0-4 (phys blocks 10-14) |
| 1 | CMIC_PG1_RST_L | Port group 1: xlport5-8 (phys blocks 15-18) |
| 2 | CMIC_PG2_RST_L | Port group 2: xlport9-13 (phys blocks 19-23) |
| 3 | CMIC_PG3_RST_L | Port group 3: xlport14-17 (phys blocks 24-27) |
| 4 | CMIC_MMU_RST_L | MMU block reset |
| 5 | CMIC_IP_RST_L | Ingress Pipeline reset |
| 6 | CMIC_EP_RST_L | Egress Pipeline reset |
| 7 | CMIC_XG_PLL0_RST_L | LCPLL 0 reset |
| 8 | CMIC_XG_PLL1_RST_L | LCPLL 1 reset |
| 9 | CMIC_XG_PLL2_RST_L | LCPLL 2 reset |
| 10 | CMIC_XG_PLL3_RST_L | LCPLL 3 reset |
| 11 | CMIC_XG_PLL0_POST_RST_L | PLL0 post-divider reset |
| 12 | CMIC_XG_PLL1_POST_RST_L | PLL1 post-divider reset |
| 13 | CMIC_XG_PLL2_POST_RST_L | PLL2 post-divider reset |
| 14 | CMIC_XG_PLL3_POST_RST_L | PLL3 post-divider reset |
| 15 | CMIC_TEMP_MON_PEAK_RST_L | Temperature monitor reset |

## BCM56840 BMD Reset Sequence (from OpenMDK)

Source: `OpenMDK/bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_reset.c`

```
1. CPS reset (CMIC_CONFIG bit RESET_CPS)
2. CMIC_SOFT_RESET = 0 (all blocks in reset)
3. Optional LCPLL reconfiguration (if DCFG_LCPLL_156)
4. PLLs out of reset: bits [7:10] = 1
5. Wait for PLL lock
6. PLL post-dividers: bits [11:14] = 1
7. Port groups out of reset: PG0-PG3 bits [0:3] = 1, temp mon bit [15]
8. CMIC_SOFT_RESET_2 (XQ hotswap arbiter release)
9. Ring maps (0x204-0x210)
10. SBUS timeout (0x200)
11. IP, EP, MMU out of reset: bits [4:6] = 1
12. xport_reset for each XLPORT block (SCHAN access to XLPORT regs)
13. WARPcore PHY init via MIIM
```

After step 11, CMIC_SOFT_RESET = 0x0000FFFF (all bits set = all out of reset).

## Our Kernel BDE Reset Sequence

Source: `bde/nos_kernel_bde.c:bcm56846_chip_reset()`

Matches the BMD sequence:
```
1. CPS reset (CMIC_CONFIG bit 5)
2. CMIC_SOFT_RESET = 0x00000000 (all in reset)
3. SBUS timeout + ring maps (0x200-0x210)
4. 0x00000780 → PLLs out of reset
5. 0x0000F780 → PLL post-dividers
6. 0x0000FF8F → PGs + temp mon
7. CMIC_SOFT_RESET_2 = 0x0000007F (XQ arbiter)
8. 0x0000FFFF → IP + EP + MMU
9. CMIC_MISC_CONTROL |= 1 (LINK40G_ENABLE)
10. SCHAN abort (clear stale state)
```

After step 8, CMIC_SOFT_RESET = 0x0000FFFF. All blocks out of reset.

## The Bug: bcm56846_xlport_deassert_reset() Was Wrong

Our `init.c:bcm56846_xlport_deassert_reset()` tried to find and write to
`TOP_SOFT_RESET_REG` via SCHAN. This was wrong because:

1. **BCM56840/56846 has no TOP_SOFT_RESET_REG** — uses CMIC_SOFT_RESET instead
2. **The probe used `schan_read_memory()` / `schan_write_memory()`** which put
   the raw address in D(0) as the SCHAN header. With no proper opcode, dstblk,
   or address field, these are garbage SCHAN messages that produce undefined results.
3. **The function was unnecessary** — the kernel BDE already deasserts all resets
   via CMIC_SOFT_RESET = 0xFFFF during probe().

The probe at address `0x00000200` "succeeded" (returned val=0x200) because
opcode 0 in the header caused undefined SCHAN behavior. Writing 0 to this
address was a NOP (no valid SCHAN write actually occurred).

## SCHAN Header Format (CMICe XGS)

From `OpenMDK/cdk/PKG/arch/xgs/xgs_schan.h`:

```
Bit  Width  Field     Description
0    1      CPU       CPU flag
1-3  3      COS       Class of Service
4-5  2      ECODE     Error code (response)
6    1      EBIT      Error bit (response)
7-13 7      DATALEN   Data length in bytes
14-19 6     SRCBLK    Source block (6 bits, 0-63)
20-25 6     DSTBLK    Destination block (6 bits, 0-63)
26-31 6     OPCODE    Operation (0x07=READ_MEM, 0x09=WRITE_MEM,
                       0x0B=READ_REG, 0x0D=WRITE_REG)
```

## XLPORT Physical Block Numbers

From `OpenMDK/cdk/PKG/chip/bcm56840/bcm56840_a0_chip.c`:

BCM56840 has 18 XLPORT blocks with physical block numbers 10-27.
BCM56840 uses a custom `blockport_addr` for blocks >= 16:

```c
uint32_t bcm56840_a0_blockport_addr(int block, int port, uint32_t offset)
{
    if (block & 0x10) {
        block &= 0xf;
        block |= 0x400;  /* adds 0x40000000 prefix to address */
    }
    return ((block * 0x100000) | (port * 0x1000) | (offset & ~0xf00000));
}
```

### Block-to-Address Mapping

| Block | Base Address | Ring | Port Group |
|-------|-------------|------|------------|
| 10 | 0x00A00000 | 3 | PG0 |
| 11 | 0x00B00000 | 3 | PG0 |
| 12 | 0x00C00000 | 3 | PG0 |
| 13 | 0x00D00000 | 3 | PG0 |
| 14 | 0x00E00000 | 3 | PG0 |
| 15 | 0x00F00000 | 3 | PG1 |
| 16 | 0x40000000 | 3 | PG1 |
| 17 | 0x40100000 | 3 | PG1 |
| 18 | 0x40200000 | 3 | PG1 |
| 19 | 0x40300000 | 4 | PG2 |
| 20 | 0x40400000 | 4 | PG2 |
| 21 | 0x40500000 | 4 | PG2 |
| 22 | 0x40600000 | 4 | PG2 |
| 23 | 0x40700000 | 4 | PG2 |
| 24 | 0x40800000 | 4 | PG3 |
| 25 | 0x40900000 | 4 | PG3 |
| 26 | 0x40A00000 | 4 | PG3 |
| 27 | 0x40B00000 | 4 | PG3 |

### CDK Port-to-Block Mapping (BCM56840 reference)

In standard BCM56840, CDK maps logical ports 1-4 to block 10, 5-8 to block 11,
etc. However, BCM56846 (AS5610-52X) may have a different mapping — our
reverse-engineered base addresses (from Cumulus) assign xe0-3 to block 26
(0x40A00000), not block 10.

## Ring Map Configuration

Ring maps at BAR0+0x204..0x210 (values from Cumulus RE and CDK):
```
MAP_0 (agents 0-7):  0x43052100
MAP_1 (agents 8-15): 0x33333343
MAP_2 (agents 16-23): 0x44444333
MAP_3 (agents 24-31): 0x00034444
```

Ring assignments:
- Ring 0: CMIC(0), IPIPE(1), block 5
- Ring 1: EPIPE(2)
- Ring 2: MMU(3)
- Ring 3: Port groups / XLPORT (lower blocks)
- Ring 4: Port groups / XLPORT (upper blocks)
- Ring 5: OTPC(4)

## CMICe SCHAN_D Overlap Issue

On BCM56846 CMICe, SCHAN message registers (D(0)-D(21)) are mapped at
BAR0+0x00 through BAR0+0x54, overlapping CMIC config registers:

| Offset | SCHAN_D | CMIC Register |
|--------|---------|---------------|
| 0x00 | D(0) | CMIC_CONFIG |
| 0x1C | D(7) | CMIC_MISC_CONTROL (LINK40G_ENABLE bit 0) |
| 0x50 | D(20) | CMICE_SCHAN_CTRL |

The kernel BDE saves/restores CMIC_MISC_CONTROL around every SCHAN op to
prevent LINK40G_ENABLE from being cleared by SCHAN response data.

## XMAC Register Addresses (CDK)

| Register | CDK Address | Offset in XLPORT |
|----------|-------------|-----------------|
| XMAC_TX_CTRLr | 0x00500604 | 0x604 (64-bit) |
| XMAC_RX_CTRLr | 0x00500606 | 0x606 (64-bit) |
| XLPORT_XGXS_CTRL_REGr | 0x00580237 | 0x80237 (32-bit) |
| XLPORT_MODE_REGr | 0x00580229 | 0x80229 (32-bit) |

For XMAC_TX_CTRLr at block 10: blockport_addr = 0x00A00604
For XMAC_TX_CTRLr at block 26: blockport_addr = 0x40A00604

## Diagnostic Plan

Since ALL XLPORT SCHAN ops fail (status=-5 = EIO = NAK or TIMEOUT), and
the kernel BDE correctly sets CMIC_SOFT_RESET=0xFFFF and LINK40G=1, the
root cause is not reset or link40g. Possible causes:

1. **Wrong xe-to-block mapping**: Our RE-derived base addresses may map
   xe ports to blocks that don't physically exist on BCM56846
2. **Some blocks don't exist**: BCM56846 has 52 ports but BCM56840 has
   72 ports; some XLPORT blocks may be absent
3. **Additional init required**: BCM56840 BMD does xport_reset (power up
   WARPcore PHY) before other XLPORT access — maybe required
4. **SCHAN_MBI flag**: Some XGS chips mask the address to `addr & 0xc0fff`;
   if active, our full addresses would be wrong

### Diagnostic approach in init.c:
1. Read and log CMIC_SOFT_RESET (BAR0+0x580)
2. Read and log CMIC_MISC_CONTROL (BAR0+0x1C)
3. Try SCHAN reads to XLPORT_MODE_REG at each possible block base (10-27)
4. Compare which blocks respond vs. which fail
5. If CDK standard blocks (10-15) work but high blocks (16-27) don't,
   the issue is block numbering. If all fail, it's something else.

## References

- `OpenMDK/bmd/PKG/chip/bcm56840_a0/bcm56840_a0_bmd_reset.c` — BMD reset
- `OpenMDK/cdk/PKG/chip/bcm56840/bcm56840_a0_chip.c` — block table + blockport_addr
- `OpenMDK/cdk/PKG/chip/bcm56840/bcm56840_a0_defs.h` — register definitions
- `OpenMDK/cdk/PKG/arch/xgs/xgs_schan.h` — SCHAN header format
- `OpenMDK/cdk/PKG/arch/xgs/xgs_reg.c` — SCHAN register operations
- `bde/nos_kernel_bde.c` — kernel BDE reset and SCHAN handler

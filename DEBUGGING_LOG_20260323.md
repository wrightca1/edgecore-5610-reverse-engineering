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

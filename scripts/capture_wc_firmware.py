#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Dump Warpcore register state from BCM56846 via MIIM clause-22.
READ-ONLY -- does NOT write to COMMANDr or stop the uC.

Previous version crashed the switch by writing to COMMANDr (0xFFC2) to stop
the microcontroller while switchd was running. This version ONLY reads registers.

Register map (WC block addresses, accessed via clause-22 page select):
  VERSIONr       = 0x81F0 - firmware version
  UC_CTRLr       = 0x820E - uC control/status
  FIRMWARE_MODEr = 0x81F2 - firmware operating mode
  COMMANDr       = 0xFFC2 - transfer control (READ ONLY!)
  RAMWORDr       = 0xFFC0 - word count
  ADDRESSr       = 0xFFC1 - address
  CRCr           = 0xFFC5 - firmware CRC
  DOWNLOAD_STATUSr = 0xFFC8 - download status

MIIM access via BAR0 (read-only path):
  We only write to MIIM_PARAM and MIIM_ADDRESS to perform MDIO reads.
  We never write to any WC register except PAGE_SELECT (reg 0x1f),
  which is required to read registers in different blocks.

IMPORTANT: PAGE_SELECT writes are safe -- switchd does them constantly
during its polling loop. COMMANDr writes are NOT safe.
"""
import struct
import mmap
import os
import sys
import time

BAR0_PHYS = 0xa0000000
BAR0_SIZE = 0x40000

MIIM_PARAM = 0x158
MIIM_ADDR = 0x4a0
MIIM_READ_DATA = 0x160

# xe0 warpcore: PHY_ADDR=17, BUS_ID=2, INTERNAL=1
MIIM_PARAM_READ = 0x02910000   # BUS2, INT=1, PHY17, DATA=0 (read)

def read32(m, off):
    return struct.unpack(">I", m[off:off+4])[0]

def write32(m, off, val):
    m[off:off+4] = struct.pack(">I", val)

def miim_wait_done(m, timeout_us=5000):
    """Wait for MIIM transaction to complete by polling MIIM_STAT."""
    for _ in range(timeout_us // 10):
        time.sleep(0.00001)
    # Simple delay-based, the HW is fast enough

def miim_read(m, phy_addr, reg_addr):
    """Read from a clause-22 register. Only touches MIIM_PARAM and MIIM_ADDRESS."""
    # Build MIIM_PARAM: BUS2, INT=1, PHY=phy_addr, DATA=0 (read)
    param = 0x02000000 | (1 << 25) | ((phy_addr & 0x1f) << 16)
    write32(m, MIIM_PARAM, param)
    time.sleep(0.0002)
    write32(m, MIIM_ADDR, reg_addr & 0x1f)
    time.sleep(0.002)  # generous wait for MDIO
    return read32(m, MIIM_READ_DATA) & 0xffff

def miim_write_page_select(m, phy_addr, page):
    """Write ONLY to PAGE_SELECT (reg 0x1f). This is the only safe write."""
    param = 0x02000000 | (1 << 25) | ((phy_addr & 0x1f) << 16) | (page & 0xffff)
    write32(m, MIIM_PARAM, param)
    time.sleep(0.0002)
    write32(m, MIIM_ADDR, 0x1f)
    time.sleep(0.002)

def wc_read(m, phy_addr, wc_addr):
    """Read a Warpcore register using clause-22 block addressing. READ ONLY."""
    block = wc_addr & 0xfff0
    reg = 0x10 | (wc_addr & 0x000f)
    miim_write_page_select(m, phy_addr, block)
    return miim_read(m, phy_addr, reg)

def scan_phy(m, phy_addr, label):
    """Scan all interesting WC registers for one PHY address."""
    results = {}

    # UC and firmware registers
    uc_regs = [
        (0x81F0, "VERSIONr"),
        (0x81F2, "FIRMWARE_MODEr"),
        (0x820E, "UC_CTRLr"),
        (0x820F, "UC_INFOr"),
        (0xFFC0, "RAMWORDr"),
        (0xFFC1, "ADDRESSr"),
        (0xFFC2, "COMMANDr"),
        (0xFFC5, "CRCr"),
        (0xFFC6, "COMMAND2r"),
        (0xFFC7, "COMMAND3r"),
        (0xFFC8, "DOWNLOAD_STATUSr"),
    ]

    print("\n=== %s (PHY_ADDR=%d) ===" % (label, phy_addr))

    print("  UC/Firmware registers:")
    for addr, name in uc_regs:
        val = wc_read(m, phy_addr, addr)
        results[addr] = (name, val)
        print("    %-20s (0x%04x) = 0x%04x" % (name, addr, val))

    # TX driver and analog
    tx_regs = [
        (0x8061, "ANATXACONTROL0"),
        (0x8062, "ANATXACONTROL1"),
        (0x8063, "ANATXACONTROL2"),
        (0x8064, "ANATXACONTROL3"),
        (0x8065, "ANATXASTATUS0"),
        (0x8067, "TX_DRIVERr"),
        (0x8068, "TX_DRIVER2r"),
        (0x80A7, "TXB_TX_DRIVERr"),
    ]

    print("  TX driver/analog registers:")
    for addr, name in tx_regs:
        val = wc_read(m, phy_addr, addr)
        results[addr] = (name, val)
        print("    %-20s (0x%04x) = 0x%04x" % (name, addr, val))

    # RX registers
    rx_regs = [
        (0x80B0, "ANARXCONTROL0"),
        (0x80B1, "ANARXCONTROL1"),
        (0x80B2, "ANARXSTATUS0"),
        (0x80B3, "ANARXSTATUS1"),
        (0x80B4, "ANARXSTATUS2"),
    ]

    print("  RX analog registers:")
    for addr, name in rx_regs:
        val = wc_read(m, phy_addr, addr)
        results[addr] = (name, val)
        print("    %-20s (0x%04x) = 0x%04x" % (name, addr, val))

    # CL72 link training
    cl72_regs = [
        (0x82E0, "CL72_MISC1_CONTROLr"),
        (0x82E2, "CL72_TX_FIR_TAPr"),
        (0x82E3, "CL72_RX_MISC_CONTROLr"),
    ]

    print("  CL72 link training:")
    for addr, name in cl72_regs:
        val = wc_read(m, phy_addr, addr)
        results[addr] = (name, val)
        print("    %-20s (0x%04x) = 0x%04x" % (name, addr, val))

    # Full block scan of interesting areas
    scan_ranges = [
        (0x8000, 0x8010, "IEEE0"),
        (0x8010, 0x8020, "IEEE1"),
        (0x8050, 0x8070, "ANATX"),
        (0x8080, 0x80A0, "ANARX"),
        (0x80A0, 0x80C0, "ANARX_EXT"),
        (0x80E0, 0x8100, "ANMISC"),
        (0x8100, 0x8120, "DIGITAL"),
        (0x8120, 0x8140, "DIGITAL2"),
        (0x8150, 0x8170, "DIGITAL3"),
        (0x8170, 0x8190, "DIGITAL4"),
        (0x81A0, 0x81C0, "DIGITAL5"),
        (0x81D0, 0x81F0, "DIGITAL6"),
        (0x81F0, 0x8210, "UC"),
        (0x8210, 0x8230, "GP_STATUS"),
        (0x8300, 0x8320, "AN"),
        (0x8320, 0x8340, "AN_EXT"),
        (0x8350, 0x8370, "AN2"),
        (0x8370, 0x8390, "AN3"),
    ]

    print("  Full register scan (non-zero only):")
    for start, end, name in scan_ranges:
        block_vals = []
        for addr in range(start, end):
            if addr not in results:
                val = wc_read(m, phy_addr, addr)
                if val != 0:
                    results[addr] = (name + "_0x%x" % (addr & 0xf), val)
                    block_vals.append((addr, val))
        if block_vals:
            print("    %s:" % name)
            for addr, val in block_vals:
                print("      0x%04x = 0x%04x" % (addr, val))

    return results

def main():
    print("Warpcore Register Scan (READ-ONLY) - BCM56846 AS5610-52X")
    print("=" * 60)
    print("NOTE: This script only READS registers. It does NOT stop the uC.")

    fd = os.open("/dev/mem", os.O_RDWR | os.O_SYNC)
    m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ | mmap.PROT_WRITE,
                  offset=BAR0_PHYS)

    outfile = "/tmp/wc_firmware_dump_%s.txt" % time.strftime("%Y%m%d_%H%M%S")

    # Scan all Warpcore instances
    # AS5610 has 14 xlports (56 lanes). Warpcore PHY addresses:
    # xlport16: PHY 17 (xe0-xe3, BUS2)
    # xlport17: PHY 21 (xe4-xe7, BUS2)
    # xlport0-15: PHY 1-16 (xe8-xe51, various BUS IDs)
    # We'll scan the known working ones first

    all_results = {}

    # Primary: xe0 warpcore (PHY 17, BUS 2) - known working
    all_results['xe0_phy17'] = scan_phy(m, 17, "xe0/swp1 (xlport16)")

    # xe4 warpcore (PHY 21, BUS 2)
    all_results['xe4_phy21'] = scan_phy(m, 21, "xe4/swp5 (xlport17)")

    # Try other PHY addresses on BUS 2 to discover more warpcores
    # PHY 1-16 might be on different BUS IDs, but let's try BUS 2 first
    for phy in [1, 5, 9, 13]:
        try:
            ver = wc_read(m, phy, 0x81F0)
            if ver != 0 and ver != 0xffff:
                label = "PHY%d (BUS2 probe)" % phy
                all_results['phy%d' % phy] = scan_phy(m, phy, label)
            else:
                print("\n  PHY%d on BUS2: VERSIONr=0x%04x (not a warpcore)" % (phy, ver))
        except Exception as e:
            print("\n  PHY%d on BUS2: error: %s" % (phy, e))

    # Restore page select to 0 on PHY 17
    miim_write_page_select(m, 17, 0x0000)

    # Save results
    with open(outfile, "w") as f:
        f.write("# Warpcore Register Scan (READ-ONLY) - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
        f.write("# Switch: AS5610-52X, BCM56846 Trident+\n")
        f.write("# Method: MIIM clause-22 reads only, no COMMANDr writes\n\n")

        for group_name, regs in sorted(all_results.items()):
            f.write("\n## %s\n" % group_name)
            for addr in sorted(regs.keys()):
                name, val = regs[addr]
                f.write("0x%04x %-24s = 0x%04x\n" % (addr, name, val))

    m.close()
    os.close(fd)

    print("\n" + "=" * 60)
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

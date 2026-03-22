#!/usr/bin/env python
"""
Option B: Warpcore register scan with exclusive MDIO access.
Run ONLY when switchd and ledmgrd are SIGSTOP'd.

Reads all WC registers AND attempts firmware RAM readback.
Since we have exclusive bus access, we can safely write to
COMMANDr to set up a read transfer.
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

def read32(m, off):
    return struct.unpack(">I", m[off:off+4])[0]

def write32(m, off, val):
    m[off:off+4] = struct.pack(">I", val)

def miim_op(m, phy_addr, bus_id, reg_addr, data=None):
    """Perform a single MIIM operation. data=None for read, else write."""
    if data is not None:
        param = 0x02000000 | (1 << 25) | ((bus_id & 7) << 22) | ((phy_addr & 0x1f) << 16) | (data & 0xffff)
    else:
        param = 0x02000000 | (1 << 25) | ((bus_id & 7) << 22) | ((phy_addr & 0x1f) << 16)
    write32(m, MIIM_PARAM, param)
    time.sleep(0.0005)
    write32(m, MIIM_ADDR, reg_addr & 0x1f)
    time.sleep(0.002)
    if data is None:
        return read32(m, MIIM_READ_DATA) & 0xffff

def wc_read(m, phy_addr, bus_id, wc_addr):
    block = wc_addr & 0xfff0
    reg = 0x10 | (wc_addr & 0x000f)
    miim_op(m, phy_addr, bus_id, 0x1f, data=block)  # page select
    return miim_op(m, phy_addr, bus_id, reg)  # read

def wc_write(m, phy_addr, bus_id, wc_addr, data):
    block = wc_addr & 0xfff0
    reg = 0x10 | (wc_addr & 0x000f)
    miim_op(m, phy_addr, bus_id, 0x1f, data=block)
    miim_op(m, phy_addr, bus_id, reg, data=data)

def scan_wc_regs(m, phy_addr, bus_id, label):
    """Full register scan of one Warpcore instance."""
    print("\n=== %s (PHY=%d BUS=%d) ===" % (label, phy_addr, bus_id))
    results = {}

    named_regs = [
        # UC/firmware
        (0x81F0, "VERSIONr"),
        (0x81F2, "FIRMWARE_MODEr"),
        (0x820E, "UC_CTRLr"),
        (0x820F, "UC_INFOr"),
        (0xFFC0, "RAMWORDr"),
        (0xFFC1, "ADDRESSr"),
        (0xFFC2, "COMMANDr"),
        (0xFFC3, "WRDATAr"),
        (0xFFC4, "RDDATAr"),
        (0xFFC5, "CRCr"),
        (0xFFC6, "COMMAND2r"),
        (0xFFC7, "COMMAND3r"),
        (0xFFC8, "DOWNLOAD_STATUSr"),
        # TX analog
        (0x8061, "ANATXACONTROL0"),
        (0x8062, "ANATXACONTROL1"),
        (0x8063, "ANATXACONTROL2"),
        (0x8064, "ANATXACONTROL3"),
        (0x8065, "ANATXASTATUS0"),
        (0x8066, "ANATXASTATUS1"),
        (0x8067, "TX_DRIVERr"),
        (0x8068, "TX_DRIVER2r"),
        (0x80A7, "TXB_TX_DRIVERr"),
        # RX analog
        (0x80B0, "ANARXCONTROL0"),
        (0x80B1, "ANARXCONTROL1"),
        (0x80B2, "ANARXSTATUS0"),
        (0x80B3, "ANARXSTATUS1"),
        (0x80B4, "ANARXSTATUS2"),
        (0x80B5, "ANARXSTATUS3"),
        # CL72
        (0x82E0, "CL72_MISC1_CONTROLr"),
        (0x82E2, "CL72_TX_FIR_TAPr"),
        (0x82E3, "CL72_RX_MISC_CONTROLr"),
    ]

    for addr, name in named_regs:
        val = wc_read(m, phy_addr, bus_id, addr)
        results[addr] = (name, val)
        print("  %-20s (0x%04x) = 0x%04x" % (name, addr, val))

    # Full block scan
    scan_ranges = [
        (0x8000, 0x8010, "IEEE0"),
        (0x8010, 0x8020, "IEEE1"),
        (0x8050, 0x8070, "ANATX"),
        (0x8070, 0x8090, "ANATX2"),
        (0x8080, 0x80A0, "ANARX"),
        (0x80A0, 0x80C0, "ANARX_EXT"),
        (0x80C0, 0x80E0, "ANMISC0"),
        (0x80E0, 0x8100, "ANMISC1"),
        (0x8100, 0x8120, "DIGITAL"),
        (0x8120, 0x8140, "DIGITAL2"),
        (0x8150, 0x8170, "DIGITAL3"),
        (0x8170, 0x8190, "DIGITAL4"),
        (0x81A0, 0x81C0, "DIGITAL5"),
        (0x81C0, 0x81E0, "DIGITAL6"),
        (0x81E0, 0x8210, "UC_BLOCK"),
        (0x8210, 0x8230, "GP_STATUS"),
        (0x8300, 0x8320, "AN"),
        (0x8320, 0x8340, "AN_EXT"),
        (0x8350, 0x8370, "AN2"),
        (0x8370, 0x8390, "AN3"),
        (0x8390, 0x83B0, "AN4"),
        (0xFFC0, 0xFFD0, "UC_DOWNLOAD"),
    ]

    for start, end, name in scan_ranges:
        for addr in range(start, end):
            if addr not in results:
                val = wc_read(m, phy_addr, bus_id, addr)
                if val != 0 and val != 0xffff:
                    results[addr] = ("%s_0x%x" % (name, addr & 0xf), val)

    return results

def dump_firmware_ram(m, phy_addr, bus_id, num_words=2048):
    """Read firmware RAM via COMMANDr read transfer."""
    print("\n--- Firmware RAM Readback (PHY=%d) ---" % phy_addr)

    # Check current firmware state
    ver = wc_read(m, phy_addr, bus_id, 0x81F0)
    cmd = wc_read(m, phy_addr, bus_id, 0xFFC2)
    dl_stat = wc_read(m, phy_addr, bus_id, 0xFFC8)
    print("  VERSION=0x%04x CMD=0x%04x DL_STAT=0x%04x" % (ver, cmd, dl_stat))

    # Stop uC: clear MDIO_UC_RESET_N
    print("  Stopping uC...")
    wc_write(m, phy_addr, bus_id, 0xFFC2, 0x0000)
    time.sleep(0.01)

    # Set word count
    wc_write(m, phy_addr, bus_id, 0xFFC0, num_words - 1)
    time.sleep(0.001)

    # Set start address = 0
    wc_write(m, phy_addr, bus_id, 0xFFC1, 0x0000)
    time.sleep(0.001)

    # Start read: RUN=1, WRITE=0
    wc_write(m, phy_addr, bus_id, 0xFFC2, 0x0010)
    time.sleep(0.05)

    # Read data words
    fw_data = []
    for i in range(num_words):
        word = wc_read(m, phy_addr, bus_id, 0xFFC4)
        fw_data.append(word)
        if i < 32 or i % 256 == 0:
            print("  RAM[0x%04x] = 0x%04x" % (i, word))

    # Stop transfer
    wc_write(m, phy_addr, bus_id, 0xFFC2, 0x0002)
    time.sleep(0.001)

    # Re-release uC
    print("  Restarting uC...")
    wc_write(m, phy_addr, bus_id, 0xFFC2, 0x0001)
    time.sleep(0.1)

    # Verify it came back
    ver2 = wc_read(m, phy_addr, bus_id, 0x81F0)
    print("  VERSION after restart: 0x%04x (was 0x%04x)" % (ver2, ver))

    return fw_data

def main():
    print("Warpcore Exclusive Scan - BCM56846 AS5610-52X")
    print("REQUIRES: switchd and ledmgrd SIGSTOP'd")
    print("=" * 60)

    fd = os.open("/dev/mem", os.O_RDWR | os.O_SYNC)
    m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ | mmap.PROT_WRITE,
                  offset=BAR0_PHYS)

    ts = time.strftime("%Y%m%d_%H%M%S")
    outfile = "/tmp/wc_exclusive_%s.txt" % ts

    all_results = {}

    # Known Warpcore instances on AS5610
    # BUS_ID 2: PHY 17 (xe0-3), PHY 21 (xe4-7)
    # Try probing other BUS IDs for the remaining ports
    wc_instances = [
        (17, 2, "xe0-3/swp1-4 (xlport16)"),
        (21, 2, "xe4-7/swp5-8 (xlport17)"),
    ]

    # Probe BUS 0,1,2,3 for other PHY addresses
    print("\n--- Probing for Warpcore instances ---")
    for bus in range(4):
        for phy in range(0, 32):
            if bus == 2 and phy in (17, 21):
                continue  # already known
            try:
                ver = wc_read(m, phy, bus, 0x81F0)
                if ver != 0 and ver != 0xffff:
                    print("  FOUND: BUS=%d PHY=%d VERSION=0x%04x" % (bus, phy, ver))
                    wc_instances.append((phy, bus, "probe BUS%d PHY%d" % (bus, phy)))
            except:
                pass

    # Full scan of each instance
    for phy, bus, label in wc_instances:
        all_results[label] = scan_wc_regs(m, phy, bus, label)

    # Firmware RAM dump from primary WC (PHY 17)
    fw_data = dump_firmware_ram(m, 17, 2, num_words=4096)

    # Restore page 0
    miim_op(m, 17, 2, 0x1f, data=0x0000)

    # Save
    with open(outfile, "w") as f:
        f.write("# Warpcore Exclusive Scan - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
        f.write("# Method: switchd/ledmgrd SIGSTOP, exclusive MDIO\n\n")

        for label, regs in sorted(all_results.items()):
            f.write("\n## %s\n" % label)
            for addr in sorted(regs.keys()):
                name, val = regs[addr]
                f.write("0x%04x %-24s = 0x%04x\n" % (addr, name, val))

        if fw_data:
            f.write("\n## Firmware RAM Dump (%d words = %d bytes)\n" % (len(fw_data), len(fw_data)*2))
            all_same = len(set(fw_data)) == 1
            if all_same:
                f.write("ALL WORDS = 0x%04x (readback may have failed)\n" % fw_data[0])
            else:
                for i in range(0, len(fw_data), 8):
                    chunk = fw_data[i:i+8]
                    f.write("0x%04x: %s\n" % (i, " ".join("0x%04x" % w for w in chunk)))

            binfile = outfile.replace(".txt", ".bin")
            with open(binfile, "wb") as bf:
                for w in fw_data:
                    bf.write(struct.pack(">H", w))
            f.write("\nBinary: %s (%d bytes)\n" % (binfile, len(fw_data)*2))

    m.close()
    os.close(fd)

    print("\n" + "=" * 60)
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

#!/usr/bin/env python
"""
Capture MIIM register activity across all port groups on BCM56846.
Polls CMIC_MIIM_PARAM and CMIC_MIIM_ADDRESS to capture SerDes MDIO
transactions for all PHY addresses / BUS IDs.

CMIC_MIIM_PARAM:   BAR0 + 0x158 (also 0x15c for status)
CMIC_MIIM_ADDRESS: BAR0 + 0x4a0
CMIC_MIIM_READ_DATA: BAR0 + 0x160

Trident+ MIIM_PARAM format (big-endian):
  [25]    INTERNAL_SEL
  [24:22] BUS_ID (0-7)
  [21]    C45_SEL
  [20:16] PHY_ADDR
  [15:0]  DATA (0=read, else write data)
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

# AS5610 port to PHY address mapping (from SERDES_WC_INIT.md + portmap)
PHY_MAP = {
    # xlport16: xe0-xe3, PHY 17-20, BUS_ID 2
    17: "xe0/swp1", 18: "xe1/swp2", 19: "xe2/swp3", 20: "xe3/swp4",
    # xlport17: xe4-xe7, PHY 21-24, BUS_ID 2
    21: "xe4/swp5", 22: "xe5/swp6", 23: "xe6/swp7", 24: "xe7/swp8",
    # xlport0-15 use different BUS_IDs
    1: "xe8/swp9?", 2: "xe9/swp10?", 3: "xe10/swp11?", 4: "xe11/swp12?",
    5: "xe12/swp13?", 6: "xe13/swp14?", 7: "xe14/swp15?", 8: "xe15/swp16?",
    9: "xe16/swp17?", 10: "xe17/swp18?", 11: "xe18/swp19?", 12: "xe19/swp20?",
    13: "xe20/swp21?", 14: "xe21/swp22?", 15: "xe22/swp23?", 16: "xe23/swp24?",
}

WC_PAGES = {
    0x0000: "PAGE0_STD",
    0x0001: "PAGE1_EXT",
    0x0002: "PAGE2_EXT",
    0x0003: "PAGE3_EXT",
    0x0008: "IEEE_BLK",
    0x000e: "PAGE_0E",
    0x000c: "PAGE_0C",
    0x0a00: "SERDES_DIGITAL",
    0x0aee: "AER_PAGE",
    0x1000: "AN_CLK_RECOVERY",
    0x1800: "UCONFIG_LANE0",
    0x1801: "UCONFIG_LANE1",
    0x1802: "UCONFIG_LANE2",
    0x1803: "UCONFIG_LANE3",
    0x3800: "WC_CORE",
    0xe000: "PAGE_E000",
}

def read32(m, off):
    return struct.unpack(">I", m[off:off+4])[0]

def decode_miim_param(param):
    internal = (param >> 25) & 1
    bus_id = (param >> 22) & 7
    c45 = (param >> 21) & 1
    phy_addr = (param >> 16) & 0x1f
    data = param & 0xffff
    return {
        'internal': internal,
        'bus_id': bus_id,
        'c45': c45,
        'phy_addr': phy_addr,
        'data': data,
        'is_write': data != 0,
        'port': PHY_MAP.get(phy_addr, "PHY%d" % phy_addr),
    }

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 30

    fd = os.open("/dev/mem", os.O_RDONLY | os.O_SYNC)
    m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=BAR0_PHYS)

    outfile = "/tmp/miim_all_ports_%s.txt" % time.strftime("%Y%m%d_%H%M%S")
    f = open(outfile, "w")
    f.write("# MIIM All-Port Capture - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
    f.write("# Duration: %d seconds\n\n" % duration)

    print("MIIM capture for %d seconds..." % duration)
    print("Bring ports up/down in another terminal to capture different port groups")
    print("=" * 80)

    start = time.time()
    last_param = 0
    last_addr = 0
    captures = []
    phy_addrs_seen = set()
    bus_ids_seen = set()
    current_page = {}  # per phy_addr page tracking

    try:
        while time.time() - start < duration:
            param = read32(m, MIIM_PARAM)
            addr = read32(m, MIIM_ADDR)

            if param != last_param or addr != last_addr:
                ts = time.time() - start
                d = decode_miim_param(param)
                read_data = read32(m, MIIM_READ_DATA) if not d['is_write'] else None

                phy_addrs_seen.add(d['phy_addr'])
                bus_ids_seen.add(d['bus_id'])

                # Track page selects
                reg_addr = addr & 0x1f
                if reg_addr == 0x1f:  # PAGE_SELECT register
                    current_page[d['phy_addr']] = d['data']

                page = current_page.get(d['phy_addr'], 0)
                page_name = WC_PAGES.get(page, "0x%04x" % page)

                entry = {
                    'time': ts,
                    'param': param,
                    'addr': addr,
                    'decoded': d,
                    'reg_addr': reg_addr,
                    'page': page,
                    'page_name': page_name,
                    'read_data': read_data,
                }
                captures.append(entry)

                op = "WR" if d['is_write'] else "RD"
                data_str = "0x%04x" % d['data'] if d['is_write'] else ("0x%04x" % read_data if read_data is not None else "????")

                line = "[%8.4f] %s BUS%d INT=%d PHY%02d %-14s page=%-18s reg[0x%02x] %s=%s" % (
                    ts, op, d['bus_id'], d['internal'], d['phy_addr'],
                    d['port'], page_name, reg_addr, op, data_str)
                print(line)

                f.write(line + "\n")
                last_param = param
                last_addr = addr

            time.sleep(0.00005)

    except KeyboardInterrupt:
        pass

    m.close()
    os.close(fd)

    # Summary
    f.write("\n# SUMMARY\n")
    f.write("# Captures: %d\n" % len(captures))
    f.write("# PHY addresses seen: %s\n" % sorted(phy_addrs_seen))
    f.write("# BUS IDs seen: %s\n" % sorted(bus_ids_seen))

    # Per-PHY summary
    f.write("\n# PER-PHY SUMMARY:\n")
    phy_counts = {}
    for e in captures:
        pa = e['decoded']['phy_addr']
        phy_counts[pa] = phy_counts.get(pa, 0) + 1
    for pa in sorted(phy_counts.keys()):
        port = PHY_MAP.get(pa, "PHY%d" % pa)
        bus = None
        for e in captures:
            if e['decoded']['phy_addr'] == pa:
                bus = e['decoded']['bus_id']
                break
        f.write("#   PHY%02d (BUS%d) %-14s: %d transactions\n" % (pa, bus or -1, port, phy_counts[pa]))

    f.close()
    print("=" * 80)
    print("Captured %d MIIM transactions" % len(captures))
    print("PHY addresses: %s" % sorted(phy_addrs_seen))
    print("BUS IDs: %s" % sorted(bus_ids_seen))
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

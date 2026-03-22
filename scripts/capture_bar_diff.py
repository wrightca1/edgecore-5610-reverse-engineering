#!/usr/bin/env python
"""
Capture BAR0 register diff during L2/L3 table operations on BCM56846.
Takes a "before" snapshot, waits for user to trigger an operation,
then takes an "after" snapshot and diffs.

BAR0 physical: 0xa0000000, size: 256KB (0x40000)
"""
import struct
import mmap
import os
import sys
import time

BAR0_PHYS = 0xa0000000
BAR0_SIZE = 0x40000

# Known register regions for annotation
REGIONS = [
    (0x00000, 0x00100, "CMIC_CORE"),
    (0x00100, 0x00200, "CMIC_MIIM"),
    (0x00200, 0x00300, "CMIC_SBUS_RING_MAP"),
    (0x00400, 0x00500, "CMIC_MIIM_EXT"),
    (0x02000, 0x03000, "CMIC_IRQ"),
    (0x04000, 0x05000, "XLPORT_REGISTERS"),
    (0x31000, 0x31200, "CMIC_CMC0_PKTDMA"),
    (0x32000, 0x32100, "CMIC_CMC0_COMMON"),
    (0x32100, 0x32200, "CMIC_CMC0_CH0_DMA"),
    (0x32200, 0x32300, "CMIC_CMC0_CH1_DMA"),
    (0x32800, 0x32900, "CMIC_CMC0_SCHAN"),
    (0x33000, 0x34000, "CMIC_CMC1"),
    (0x34000, 0x35000, "CMIC_CMC2"),
    (0x38000, 0x39000, "CMIC_LED"),
]

def region_name(offset):
    for start, end, name in REGIONS:
        if start <= offset < end:
            return name
    return "UNKNOWN"

def snapshot(m):
    """Read all 32-bit registers from BAR0."""
    regs = {}
    for off in range(0, BAR0_SIZE, 4):
        raw = m[off:off+4]
        val = struct.unpack(">I", raw)[0]
        if val != 0:  # Skip zero registers to reduce noise
            regs[off] = val
    return regs

def main():
    label = sys.argv[1] if len(sys.argv) > 1 else "generic"

    fd = os.open("/dev/mem", os.O_RDONLY | os.O_SYNC)
    m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=BAR0_PHYS)

    print("Taking BEFORE snapshot...")
    before = snapshot(m)
    print("  %d non-zero registers captured" % len(before))
    print(">>> Now trigger the %s operation <<<" % label)
    print("Press Enter when done...")
    sys.stdin.readline()

    print("Taking AFTER snapshot...")
    after = snapshot(m)
    print("  %d non-zero registers captured" % len(after))

    m.close()
    os.close(fd)

    # Compute diff
    all_offsets = sorted(set(list(before.keys()) + list(after.keys())))
    changes = []
    new_regs = []
    gone_regs = []

    for off in all_offsets:
        b = before.get(off, 0)
        a = after.get(off, 0)
        if b != a:
            if b == 0:
                new_regs.append((off, a))
            elif a == 0:
                gone_regs.append((off, b))
            else:
                changes.append((off, b, a))

    outfile = "/tmp/bar_diff_%s_%s.txt" % (label, time.strftime("%Y%m%d_%H%M%S"))
    with open(outfile, "w") as f:
        f.write("# BAR0 Register Diff - %s\n" % label)
        f.write("# Time: %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
        f.write("# Before: %d non-zero regs, After: %d non-zero regs\n" % (len(before), len(after)))
        f.write("# Changed: %d, New: %d, Gone: %d\n\n" % (len(changes), len(new_regs), len(gone_regs)))

        if changes:
            f.write("## CHANGED REGISTERS\n")
            f.write("%-10s %-25s %-12s %-12s %s\n" % ("Offset", "Region", "Before", "After", "XOR"))
            f.write("-" * 80 + "\n")
            for off, b, a in changes:
                f.write("0x%05x    %-25s 0x%08x   0x%08x   0x%08x\n" % (
                    off, region_name(off), b, a, b ^ a))

        if new_regs:
            f.write("\n## NEW (was zero)\n")
            for off, a in new_regs:
                f.write("0x%05x    %-25s              0x%08x\n" % (off, region_name(off), a))

        if gone_regs:
            f.write("\n## GONE (now zero)\n")
            for off, b in gone_regs:
                f.write("0x%05x    %-25s 0x%08x\n" % (off, region_name(off), b))

    print("\n=== DIFF SUMMARY ===")
    print("Changed: %d registers" % len(changes))
    print("New: %d registers" % len(new_regs))
    print("Gone: %d registers" % len(gone_regs))
    for off, b, a in changes[:20]:
        print("  0x%05x [%-20s]: 0x%08x -> 0x%08x" % (off, region_name(off), b, a))
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

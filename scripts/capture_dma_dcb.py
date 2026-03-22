#!/usr/bin/env python
"""
Capture DMA descriptor chain buffer (DCB) layout during packet TX/RX on BCM56846.

DCB Type 21 (Trident/Trident+): 16 words (64 bytes) per descriptor.
DMA pool physical: 0x04000000, mapped by switchd.

This script reads the DMA control registers and follows the descriptor chain
to dump DCB contents, capturing before and after packet operations.

CMIC_CMC0_CH0_DMA_CTRL:     BAR0 + 0x32100
CMIC_CMC0_CH0_DMA_STAT:     BAR0 + 0x32104
CMIC_CMC0_CH0_DMA_DESC:     BAR0 + 0x32108
CMIC_CMC0_CH0_DMA_CUR_DESC: BAR0 + 0x3210c
CMIC_CMC0_CH1_DMA_CTRL:     BAR0 + 0x32200  (TX typically)
CMIC_CMC0_CH1_DMA_DESC:     BAR0 + 0x32208
"""
import struct
import mmap
import os
import sys
import time

BAR0_PHYS = 0xa0000000
BAR0_SIZE = 0x40000
DMA_PHYS = 0x04000000
DMA_SIZE = 0x2000000  # 32MB

# DMA register offsets from BAR0
DMA_CHANNELS = {
    'CH0': {'ctrl': 0x32100, 'stat': 0x32104, 'desc': 0x32108, 'cur': 0x3210c},
    'CH1': {'ctrl': 0x32200, 'stat': 0x32204, 'desc': 0x32208, 'cur': 0x3220c},
    'CH2': {'ctrl': 0x32300, 'stat': 0x32304, 'desc': 0x32308, 'cur': 0x3230c},
    'CH3': {'ctrl': 0x32400, 'stat': 0x32404, 'desc': 0x32408, 'cur': 0x3240c},
}

# DCB Type 21 word definitions (Trident+)
DCB21_FIELDS = {
    0: "ADDR (physical buffer address)",
    1: "CTRL (byte count, chain, SG, reload, HG, purge, etc.)",
    2: "STATUS (done, end, start, error, sobmh)",
    3: "MH0 (sobmh word 0: src_mod, dst_port)",
    4: "MH1 (sobmh word 1: cos, vlan)",
    5: "MH2 (sobmh word 2: opcode)",
    6: "MH3 (sobmh word 3: reserved)",
    7: "RX_STATUS0 (rx_bpdu, rx_l3only, rx_ip, etc.)",
    8: "RX_STATUS1 (incoming_port, cos, hgi)",
    9: "RX_STATUS2 (match_rule, reason_hi)",
    10: "RX_REASON (cpu_opcode bitmap low 32)",
    11: "RX_REASON_HI (cpu_opcode bitmap high)",
    12: "RX_MATCH (outer_vid, inner_vid, etc.)",
    13: "RX_TIMESTAMP_LO",
    14: "RX_TIMESTAMP_HI",
    15: "RX_MISC (decap_tunnel_type, etc.)",
}

def read32(m, off):
    return struct.unpack(">I", m[off:off+4])[0]

def dump_dma_regs(bar_m):
    """Dump all DMA channel control registers."""
    result = {}
    for ch_name, regs in sorted(DMA_CHANNELS.items()):
        ch = {}
        for reg_name, off in sorted(regs.items(), key=lambda x: x[1]):
            ch[reg_name] = read32(bar_m, off)
        result[ch_name] = ch
    return result

def dump_dcb_chain(dma_m, desc_phys, max_dcbs=32):
    """Follow a DCB descriptor chain and dump each descriptor."""
    dcbs = []
    addr = desc_phys
    for _ in range(max_dcbs):
        if addr < DMA_PHYS or addr >= DMA_PHYS + DMA_SIZE:
            break
        offset = addr - DMA_PHYS
        if offset + 64 > DMA_SIZE:
            break
        words = []
        for i in range(16):
            words.append(read32(dma_m, offset + i * 4))
        dcbs.append({'phys_addr': addr, 'words': words})

        # Check chain bit (word 1, bit 16 in DCB21)
        chain = (words[1] >> 16) & 1
        reload = (words[1] >> 17) & 1
        if reload:
            # Reload: word 0 is next descriptor list address
            addr = words[0]
        elif chain:
            # Chain: next DCB follows immediately
            addr += 64
        else:
            break
    return dcbs

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 10

    fd = os.open("/dev/mem", os.O_RDONLY | os.O_SYNC)
    bar_m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=BAR0_PHYS)
    dma_m = mmap.mmap(fd, DMA_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=DMA_PHYS)

    outfile = "/tmp/dma_dcb_capture_%s.txt" % time.strftime("%Y%m%d_%H%M%S")
    f = open(outfile, "w")
    f.write("# DMA/DCB Capture - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
    f.write("# Duration: %d seconds\n\n" % duration)

    print("DMA/DCB capture for %d seconds..." % duration)
    print("Generate traffic (ping, etc.) in another terminal")
    print("=" * 80)

    # Initial DMA register dump
    regs = dump_dma_regs(bar_m)
    f.write("## INITIAL DMA REGISTERS\n")
    for ch_name, ch in sorted(regs.items()):
        f.write("%s:\n" % ch_name)
        for reg, val in sorted(ch.items()):
            f.write("  %-8s = 0x%08x\n" % (reg, val))
            print("  %s.%-8s = 0x%08x" % (ch_name, reg, val))
        # Dump DCB chain if desc pointer is in DMA range
        desc = ch.get('desc', 0)
        if DMA_PHYS <= desc < DMA_PHYS + DMA_SIZE:
            dcbs = dump_dcb_chain(dma_m, desc)
            f.write("  DCB chain from 0x%08x (%d descriptors):\n" % (desc, len(dcbs)))
            for j, dcb in enumerate(dcbs):
                f.write("    DCB[%d] @ 0x%08x:\n" % (j, dcb['phys_addr']))
                for wi, w in enumerate(dcb['words']):
                    f.write("      [%2d] 0x%08x  %s\n" % (wi, w, DCB21_FIELDS.get(wi, "")))
    f.write("\n")

    # Poll for DMA activity changes
    start = time.time()
    prev_regs = regs
    snap_count = 0

    try:
        while time.time() - start < duration:
            regs = dump_dma_regs(bar_m)
            changed = False
            for ch_name in sorted(regs.keys()):
                for reg in sorted(regs[ch_name].keys()):
                    if regs[ch_name][reg] != prev_regs[ch_name][reg]:
                        changed = True
                        break
                if changed:
                    break

            if changed:
                snap_count += 1
                ts = time.time() - start
                f.write("## SNAPSHOT %d @ t=%.4f\n" % (snap_count, ts))
                print("[%8.4f] DMA registers changed (snapshot %d)" % (ts, snap_count))
                for ch_name in sorted(regs.keys()):
                    for reg in sorted(regs[ch_name].keys()):
                        old = prev_regs[ch_name][reg]
                        new = regs[ch_name][reg]
                        if old != new:
                            f.write("  %s.%-8s: 0x%08x -> 0x%08x\n" % (ch_name, reg, old, new))
                            print("  %s.%-8s: 0x%08x -> 0x%08x" % (ch_name, reg, old, new))

                # Re-dump DCB chains on change
                for ch_name, ch in sorted(regs.items()):
                    desc = ch.get('desc', 0)
                    cur = ch.get('cur', 0)
                    if DMA_PHYS <= desc < DMA_PHYS + DMA_SIZE:
                        dcbs = dump_dcb_chain(dma_m, desc, max_dcbs=8)
                        f.write("  %s DCB chain (%d descriptors):\n" % (ch_name, len(dcbs)))
                        for j, dcb in enumerate(dcbs):
                            marker = " <-- CUR" if dcb['phys_addr'] == cur else ""
                            f.write("    DCB[%d] @ 0x%08x%s:\n" % (j, dcb['phys_addr'], marker))
                            for wi, w in enumerate(dcb['words']):
                                f.write("      [%2d] 0x%08x  %s\n" % (wi, w, DCB21_FIELDS.get(wi, "")))
                f.write("\n")
                prev_regs = regs

            time.sleep(0.001)

    except KeyboardInterrupt:
        pass

    # Final snapshot
    regs = dump_dma_regs(bar_m)
    f.write("## FINAL DMA REGISTERS\n")
    for ch_name, ch in sorted(regs.items()):
        f.write("%s:\n" % ch_name)
        for reg, val in sorted(ch.items()):
            f.write("  %-8s = 0x%08x\n" % (reg, val))
        desc = ch.get('desc', 0)
        if DMA_PHYS <= desc < DMA_PHYS + DMA_SIZE:
            dcbs = dump_dcb_chain(dma_m, desc)
            f.write("  DCB chain from 0x%08x (%d descriptors):\n" % (desc, len(dcbs)))
            for j, dcb in enumerate(dcbs):
                f.write("    DCB[%d] @ 0x%08x:\n" % (j, dcb['phys_addr']))
                for wi, w in enumerate(dcb['words']):
                    f.write("      [%2d] 0x%08x  %s\n" % (wi, w, DCB21_FIELDS.get(wi, "")))

    bar_m.close()
    dma_m.close()
    os.close(fd)
    f.close()

    print("=" * 80)
    print("%d snapshots captured. Saved to %s" % (snap_count, outfile))

if __name__ == "__main__":
    main()

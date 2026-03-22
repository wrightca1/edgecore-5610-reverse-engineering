#!/usr/bin/env python
"""
Option C: Safe captures that do NOT touch MIIM at all.
Only reads BAR0 registers via /dev/mem. No writes whatsoever.

Captures:
1. S-Channel message buffer snapshot
2. DMA descriptor chain dump
3. Full BAR0 register snapshot (non-zero regs)
4. CMIC interrupt/status registers

All reads go through /dev/mem mmap. No contention with switchd/ledmgrd
because we never write to any control register.
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

SCHAN_OPCODES = {
    0x07: "READ_MEMORY",
    0x09: "READ_REGISTER",
    0x0a: "WRITE_MEMORY",
    0x0b: "WRITE_REGISTER",
    0x24: "TABLE_INSERT",
    0x25: "TABLE_DELETE",
    0x26: "TABLE_LOOKUP",
    0x2a: "FIFO_POP",
}

KNOWN_REGS = {
    0x00000: "CMIC_RATE_ADJUST_EXT_MDIO",
    0x00004: "CMIC_RATE_ADJUST_INT_MDIO",
    0x00010: "CMIC_MIIM_CTRL",
    0x00044: "CMIC_LINK_STATUS_1",
    0x00048: "CMIC_LINK_STATUS_2",
    0x00104: "CMIC_CONFIG",
    0x00140: "CMIC_IRQ_STAT",
    0x00144: "CMIC_IRQ_MASK",
    0x00150: "CMIC_MIIM_CTRL",
    0x00158: "CMIC_MIIM_PARAM",
    0x0015c: "CMIC_MIIM_STAT",
    0x00160: "CMIC_MIIM_READ_DATA",
    0x00178: "CMIC_DEV_REV_ID",
    0x00200: "CMIC_SBUS_RING_MAP_0_7",
    0x00204: "CMIC_SBUS_RING_MAP_8_15",
    0x00208: "CMIC_SBUS_RING_MAP_16_23",
    0x0020c: "CMIC_SBUS_RING_MAP_24_31",
    0x00210: "CMIC_SBUS_RING_MAP_32_39",
    0x00214: "CMIC_SBUS_RING_MAP_40_47",
    0x004a0: "CMIC_MIIM_ADDRESS",
    0x31100: "CMIC_CMC0_PKTDMA_CH0_CTRL",
    0x31104: "CMIC_CMC0_PKTDMA_CH0_DESC_ADDR",
    0x31108: "CMIC_CMC0_PKTDMA_CH0_STAT",
    0x31200: "CMIC_CMC0_PKTDMA_CH1_CTRL",
    0x31204: "CMIC_CMC0_PKTDMA_CH1_DESC_ADDR",
    0x31208: "CMIC_CMC0_PKTDMA_CH1_STAT",
    0x31300: "CMIC_CMC0_PKTDMA_CH2_CTRL",
    0x31400: "CMIC_CMC0_PKTDMA_CH3_CTRL",
    0x32100: "CMIC_CMC0_CH0_DMA_CTRL",
    0x32104: "CMIC_CMC0_CH0_DMA_STAT",
    0x32108: "CMIC_CMC0_CH0_DMA_DESC",
    0x3210c: "CMIC_CMC0_CH0_DMA_CUR_DESC",
    0x32200: "CMIC_CMC0_CH1_DMA_CTRL",
    0x32204: "CMIC_CMC0_CH1_DMA_STAT",
    0x32208: "CMIC_CMC0_CH1_DMA_DESC",
    0x3220c: "CMIC_CMC0_CH1_DMA_CUR_DESC",
    0x32300: "CMIC_CMC0_CH2_DMA_CTRL",
    0x32400: "CMIC_CMC0_CH3_DMA_CTRL",
    0x32800: "CMIC_CMC0_SCHAN_CTRL",
    0x32804: "CMIC_CMC0_SCHAN_MSG0",
    0x32808: "CMIC_CMC0_SCHAN_MSG1",
    0x3280c: "CMIC_CMC0_SCHAN_MSG2",
    0x32810: "CMIC_CMC0_SCHAN_MSG3",
    0x32814: "CMIC_CMC0_SCHAN_MSG4",
    0x32818: "CMIC_CMC0_SCHAN_MSG5",
    0x3281c: "CMIC_CMC0_SCHAN_MSG6",
    0x32820: "CMIC_CMC0_SCHAN_MSG7",
}

DCB21_FIELDS = {
    0: "ADDR (phys buffer addr)",
    1: "CTRL (count[15:0], chain[16], reload[17], SG[18], purge[19], HG[20])",
    2: "STATUS (done[31], eop[30], sop[29], sobmhdr[26])",
    3: "MH0 (sobmh word 0)",
    4: "MH1 (sobmh word 1)",
    5: "MH2 (sobmh word 2)",
    6: "MH3 (sobmh word 3)",
    7: "RX_STATUS0",
    8: "RX_STATUS1 (incoming_port, cos)",
    9: "RX_STATUS2 (match_rule)",
    10: "RX_REASON_LO",
    11: "RX_REASON_HI",
    12: "RX_MATCH",
    13: "RX_TIMESTAMP_LO",
    14: "RX_TIMESTAMP_HI",
    15: "RX_MISC",
}

def read32(m, off):
    return struct.unpack(">I", m[off:off+4])[0]

def main():
    print("Safe Capture (NO MIIM, READ-ONLY) - BCM56846 AS5610-52X")
    print("=" * 70)

    fd = os.open("/dev/mem", os.O_RDONLY | os.O_SYNC)
    bar_m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=BAR0_PHYS)
    dma_m = mmap.mmap(fd, DMA_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=DMA_PHYS)

    ts = time.strftime("%Y%m%d_%H%M%S")
    outfile = "/tmp/safe_capture_%s.txt" % ts

    with open(outfile, "w") as f:
        f.write("# Safe Capture (NO MIIM) - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
        f.write("# BCM56846 Trident+ AS5610-52X\n")
        f.write("# Method: /dev/mem read-only, no writes\n\n")

        # 1. CMIC identity
        print("\n--- 1. CMIC Identity ---")
        dev_rev = read32(bar_m, 0x178)
        f.write("## 1. CMIC Identity\n")
        f.write("CMIC_DEV_REV_ID (0x178) = 0x%08x\n" % dev_rev)
        f.write("  Device ID: 0x%04x\n" % ((dev_rev >> 16) & 0xffff))
        f.write("  Rev ID:    0x%02x\n" % (dev_rev & 0xff))
        print("  DEV_REV_ID = 0x%08x (device=0x%04x rev=0x%02x)" % (
            dev_rev, (dev_rev >> 16) & 0xffff, dev_rev & 0xff))

        # 2. SBUS ring map
        print("\n--- 2. SBUS Ring Map ---")
        f.write("\n## 2. SBUS Ring Map\n")
        for i in range(6):
            off = 0x200 + i * 4
            val = read32(bar_m, off)
            f.write("RING_MAP_%d_%d (0x%03x) = 0x%08x\n" % (i*8, i*8+7, off, val))
            # Decode: 4 bits per block
            blocks = []
            for b in range(8):
                ring = (val >> (b * 4)) & 0xf
                blocks.append("blk%d=ring%d" % (i*8+b, ring))
            f.write("  %s\n" % ", ".join(blocks))
            print("  0x%03x = 0x%08x  [%s]" % (off, val, ", ".join(blocks)))

        # 3. S-Channel current state
        print("\n--- 3. S-Channel State ---")
        f.write("\n## 3. S-Channel State\n")
        schan_ctrl = read32(bar_m, 0x32800)
        f.write("SCHAN_CTRL (0x32800) = 0x%08x\n" % schan_ctrl)
        f.write("  MSG_START=%d MSG_DONE=%d NACK=%d SER_CHECK_FAIL=%d\n" % (
            (schan_ctrl >> 0) & 1, (schan_ctrl >> 1) & 1,
            (schan_ctrl >> 2) & 1, (schan_ctrl >> 3) & 1))
        print("  SCHAN_CTRL = 0x%08x" % schan_ctrl)

        for i in range(8):
            off = 0x32804 + i * 4
            val = read32(bar_m, off)
            f.write("SCHAN_MSG[%d] (0x%05x) = 0x%08x\n" % (i, off, val))

        # Decode header
        msg0 = read32(bar_m, 0x32804)
        opcode = (msg0 >> 26) & 0x3f
        dst_blk = (msg0 >> 19) & 0x7f
        data_len = (msg0 >> 7) & 0x7f
        f.write("  Last op: %s (0x%02x) dst_blk=%d data_len=%d\n" % (
            SCHAN_OPCODES.get(opcode, "UNK"), opcode, dst_blk, data_len))
        print("  Last SCHAN op: %s dst_blk=%d len=%d" % (
            SCHAN_OPCODES.get(opcode, "UNK_0x%02x" % opcode), dst_blk, data_len))

        # 4. DMA/Packet DMA channels
        print("\n--- 4. DMA Channels ---")
        f.write("\n## 4. DMA Channels\n")
        dma_channels = [
            ("PKTDMA_CH0", 0x31100, 0x31104, 0x31108),
            ("PKTDMA_CH1", 0x31200, 0x31204, 0x31208),
            ("PKTDMA_CH2", 0x31300, 0x31304, 0x31308),
            ("PKTDMA_CH3", 0x31400, 0x31404, 0x31408),
            ("SBUSDMA_CH0", 0x32100, 0x32108, 0x32104),
            ("SBUSDMA_CH1", 0x32200, 0x32208, 0x32204),
            ("SBUSDMA_CH2", 0x32300, 0x32308, 0x32304),
            ("SBUSDMA_CH3", 0x32400, 0x32408, 0x32404),
        ]
        for name, ctrl_off, desc_off, stat_off in dma_channels:
            ctrl = read32(bar_m, ctrl_off)
            desc = read32(bar_m, desc_off)
            stat = read32(bar_m, stat_off)
            f.write("%s: CTRL=0x%08x DESC=0x%08x STAT=0x%08x\n" % (name, ctrl, desc, stat))
            print("  %s: CTRL=0x%08x DESC=0x%08x STAT=0x%08x" % (name, ctrl, desc, stat))

            # Follow DCB chain if desc is in DMA region
            if DMA_PHYS <= desc < DMA_PHYS + DMA_SIZE:
                dma_off = desc - DMA_PHYS
                f.write("  DCB chain from phys 0x%08x (DMA pool offset 0x%x):\n" % (desc, dma_off))
                for dcb_idx in range(16):
                    dcb_off = dma_off + dcb_idx * 64
                    if dcb_off + 64 > DMA_SIZE:
                        break
                    words = []
                    for w in range(16):
                        words.append(read32(dma_m, dcb_off + w * 4))
                    # Check if DCB looks valid (not all zeros/all ff)
                    if all(w == 0 for w in words):
                        f.write("    DCB[%d]: all zeros, stopping\n" % dcb_idx)
                        break
                    f.write("    DCB[%d] @ DMA+0x%x:\n" % (dcb_idx, dcb_off))
                    for wi, w in enumerate(words):
                        f.write("      [%2d] 0x%08x  %s\n" % (wi, w, DCB21_FIELDS.get(wi, "")))
                    print("    DCB[%d]: addr=0x%08x ctrl=0x%08x stat=0x%08x" % (
                        dcb_idx, words[0], words[1], words[2]))
                    # Check chain/reload
                    chain = (words[1] >> 16) & 1
                    reload_bit = (words[1] >> 17) & 1
                    if reload_bit:
                        next_desc = words[0]
                        if DMA_PHYS <= next_desc < DMA_PHYS + DMA_SIZE:
                            dma_off = next_desc - DMA_PHYS
                            f.write("    (reload to 0x%08x)\n" % next_desc)
                        else:
                            f.write("    (reload to 0x%08x - outside DMA pool)\n" % next_desc)
                            break
                    elif not chain:
                        f.write("    (end of chain)\n")
                        break

        # 5. MIIM state (read-only snapshot, no bus contention)
        print("\n--- 5. MIIM State (snapshot) ---")
        f.write("\n## 5. MIIM State (read-only snapshot)\n")
        miim_regs = [
            (0x150, "CMIC_MIIM_CTRL"),
            (0x158, "CMIC_MIIM_PARAM"),
            (0x15c, "CMIC_MIIM_STAT"),
            (0x160, "CMIC_MIIM_READ_DATA"),
            (0x4a0, "CMIC_MIIM_ADDRESS"),
        ]
        for off, name in miim_regs:
            val = read32(bar_m, off)
            f.write("%-25s (0x%03x) = 0x%08x\n" % (name, off, val))
            print("  %-25s = 0x%08x" % (name, val))
        # Decode MIIM_PARAM
        param = read32(bar_m, 0x158)
        internal = (param >> 25) & 1
        bus_id = (param >> 22) & 7
        c45 = (param >> 21) & 1
        phy_addr = (param >> 16) & 0x1f
        data = param & 0xffff
        f.write("  Decoded: INT=%d BUS=%d C45=%d PHY=%d DATA=0x%04x (%s)\n" % (
            internal, bus_id, c45, phy_addr, data, "WRITE" if data else "READ"))

        # 6. XLPORT registers (port MAC/PHY config)
        print("\n--- 6. XLPORT Register Scan ---")
        f.write("\n## 6. XLPORT Register Scan (non-zero, 0x4000-0x5000)\n")
        xlport_count = 0
        for off in range(0x4000, 0x5000, 4):
            val = read32(bar_m, off)
            if val != 0:
                f.write("0x%05x = 0x%08x\n" % (off, val))
                xlport_count += 1
        print("  %d non-zero XLPORT registers" % xlport_count)

        # 7. Full BAR0 register dump (non-zero only)
        print("\n--- 7. Full BAR0 Scan ---")
        f.write("\n## 7. Full BAR0 Register Dump (non-zero only)\n")
        total_nonzero = 0
        for off in range(0, BAR0_SIZE, 4):
            val = read32(bar_m, off)
            if val != 0:
                name = KNOWN_REGS.get(off, "")
                f.write("0x%05x = 0x%08x  %s\n" % (off, val, name))
                total_nonzero += 1
        print("  %d non-zero registers in full BAR0" % total_nonzero)

        # 8. S-Channel polling (10 seconds, read-only)
        print("\n--- 8. S-Channel Polling (10s, read-only) ---")
        f.write("\n## 8. S-Channel Activity (10 second poll)\n")
        start = time.time()
        last_ctrl = read32(bar_m, 0x32800)
        transitions = []
        while time.time() - start < 10:
            ctrl = read32(bar_m, 0x32800)
            if ctrl != last_ctrl:
                t = time.time() - start
                msg0 = read32(bar_m, 0x32804)
                msg1 = read32(bar_m, 0x32808)
                opcode = (msg0 >> 26) & 0x3f
                dst_blk = (msg0 >> 19) & 0x7f
                transitions.append((t, ctrl, last_ctrl, msg0, msg1, opcode, dst_blk))
                last_ctrl = ctrl
            time.sleep(0.0001)

        f.write("Transitions: %d\n" % len(transitions))
        for t, ctrl, prev, msg0, msg1, op, blk in transitions:
            f.write("[%8.4f] CTRL 0x%08x->0x%08x MSG0=0x%08x MSG1=0x%08x op=%s blk=%d\n" % (
                t, prev, ctrl, msg0, msg1,
                SCHAN_OPCODES.get(op, "0x%02x" % op), blk))
        print("  %d S-Channel transitions in 10s" % len(transitions))

    bar_m.close()
    dma_m.close()
    os.close(fd)

    print("\n" + "=" * 70)
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

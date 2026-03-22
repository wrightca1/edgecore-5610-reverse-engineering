#!/usr/bin/env python
"""
Capture S-Channel table write operations on BCM56846 (Trident+).
Polls SCHAN_CTRL for activity and captures SCHAN_MSG words when a transaction completes.

BAR0 physical: 0xa0000000, mapped by switchd at VA 0x4802b000
CMIC_CMC0_SCHAN_CTRL: BAR0 + 0x32800
CMIC_CMC0_SCHAN_MESSAGE0..7: BAR0 + 0x32804..0x32820
"""
import struct
import mmap
import os
import sys
import time

BAR0_PHYS = 0xa0000000
BAR0_SIZE = 0x40000
SCHAN_CTRL = 0x32800
SCHAN_MSG_BASE = 0x32804
SCHAN_MSG_COUNT = 8

# S-Channel opcodes (from BCM SDK)
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

def read32(m, off):
    """Read 32-bit big-endian value from mmap."""
    raw = m[off:off+4]
    return struct.unpack(">I", raw)[0]

def decode_schan_header(word0):
    """Decode S-Channel command header word (big-endian PPC format)."""
    opcode = (word0 >> 26) & 0x3f
    dst_blk = (word0 >> 19) & 0x7f
    acc_type = (word0 >> 16) & 0x07
    data_len = (word0 >> 7) & 0x7f
    dma = (word0 >> 4) & 0x01
    bank = word0 & 0x03
    return {
        'opcode': opcode,
        'opcode_name': SCHAN_OPCODES.get(opcode, "UNKNOWN_0x%02x" % opcode),
        'dst_blk': dst_blk,
        'acc_type': acc_type,
        'data_len': data_len,
        'dma': dma,
        'bank': bank,
    }

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 10
    print("S-Channel capture for %d seconds..." % duration)
    print("Trigger L2/L3 operations in another terminal")
    print("=" * 80)

    fd = os.open("/dev/mem", os.O_RDONLY | os.O_SYNC)
    m = mmap.mmap(fd, BAR0_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=BAR0_PHYS)

    start = time.time()
    last_ctrl = 0
    captures = []
    poll_count = 0

    try:
        while time.time() - start < duration:
            ctrl = read32(m, SCHAN_CTRL)
            poll_count += 1

            # Bit 1 = MSG_DONE in big-endian, check for transitions
            if ctrl != last_ctrl:
                ts = time.time() - start
                # Read all 8 message words
                words = []
                for i in range(SCHAN_MSG_COUNT):
                    w = read32(m, SCHAN_MSG_BASE + i * 4)
                    words.append(w)

                hdr = decode_schan_header(words[0])
                entry = {
                    'time': ts,
                    'ctrl': ctrl,
                    'prev_ctrl': last_ctrl,
                    'words': words,
                    'header': hdr,
                }
                captures.append(entry)

                # Print live
                print("[%8.4f] CTRL: 0x%08x -> 0x%08x  OP: %s (0x%02x)  DST_BLK: %d  LEN: %d" % (
                    ts, last_ctrl, ctrl,
                    hdr['opcode_name'], hdr['opcode'],
                    hdr['dst_blk'], hdr['data_len']))
                print("           ADDR: 0x%08x  DATA: %s" % (
                    words[1],
                    " ".join("0x%08x" % w for w in words[2:])))

                last_ctrl = ctrl

            # Small sleep to avoid 100% CPU but still catch most transactions
            time.sleep(0.0001)

    except KeyboardInterrupt:
        pass

    m.close()
    os.close(fd)

    print("=" * 80)
    print("Captured %d transitions in %d polls over %.1f seconds" % (
        len(captures), poll_count, time.time() - start))

    # Write detailed output
    outfile = "/tmp/schan_capture_%s.txt" % time.strftime("%Y%m%d_%H%M%S")
    with open(outfile, "w") as f:
        f.write("# S-Channel Capture - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
        f.write("# Duration: %d seconds, %d polls, %d transitions\n\n" % (
            duration, poll_count, len(captures)))
        for e in captures:
            f.write("[%8.4f] CTRL=0x%08x (was 0x%08x)\n" % (e['time'], e['ctrl'], e['prev_ctrl']))
            f.write("  Header: opcode=%s(0x%02x) dst_blk=%d acc_type=%d data_len=%d dma=%d bank=%d\n" % (
                e['header']['opcode_name'], e['header']['opcode'],
                e['header']['dst_blk'], e['header']['acc_type'],
                e['header']['data_len'], e['header']['dma'], e['header']['bank']))
            for i, w in enumerate(e['words']):
                f.write("  MSG[%d] = 0x%08x\n" % (i, w))
            f.write("\n")
    print("Saved to %s" % outfile)

if __name__ == "__main__":
    main()

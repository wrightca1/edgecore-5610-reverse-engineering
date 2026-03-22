#!/bin/bash
# Option A: GDB burst-read of WC registers by attaching to switchd.
#
# Attaches GDB to switchd, sets a breakpoint on the MIIM write function,
# then injects our own MIIM reads during the breakpoint handler.
# switchd is paused only during the burst (milliseconds).
#
# This works by:
# 1. Attaching to switchd (freezes it)
# 2. Reading WC registers via direct memory writes to MIIM regs
# 3. Detaching (resumes switchd)
#
# Total freeze time: ~2-5 seconds for full scan

SWITCHD_PID=$(pidof switchd)
if [ -z "$SWITCHD_PID" ]; then
    echo "switchd not running!"
    exit 1
fi

echo "=== Option A: GDB Burst Read ==="
echo "switchd PID: $SWITCHD_PID"
echo "Attaching GDB, reading WC registers, then detaching..."

OUTFILE="/tmp/wc_gdb_burst_$(date +%Y%m%d_%H%M%S).txt"

# GDB script that reads WC registers using direct BAR0 access
# BAR0 is already mapped in switchd at 0x4802b000
# MIIM_PARAM = BAR0 + 0x158
# MIIM_ADDR  = BAR0 + 0x4a0
# MIIM_READ_DATA = BAR0 + 0x160

cat > /tmp/gdb_wc_burst.py << 'GDBSCRIPT'
import gdb
import time

BAR0 = 0x4802b000
MIIM_PARAM = BAR0 + 0x158
MIIM_ADDR = BAR0 + 0x4a0
MIIM_READ_DATA = BAR0 + 0x160

def read_mem32(addr):
    """Read a 32-bit value from switchd's address space."""
    val = gdb.parse_and_eval("*(unsigned int*)0x%x" % addr)
    return int(val) & 0xffffffff

def write_mem32(addr, val):
    """Write a 32-bit value to switchd's address space."""
    gdb.execute("set *(unsigned int*)0x%x = 0x%x" % (addr, val), to_string=True)

def wc_read(phy_addr, bus_id, wc_addr):
    """Read a WC register via MIIM."""
    block = wc_addr & 0xfff0
    reg = 0x10 | (wc_addr & 0x000f)
    # Page select
    param_wr = 0x02000000 | (1 << 25) | ((bus_id & 7) << 22) | ((phy_addr & 0x1f) << 16) | (block & 0xffff)
    write_mem32(MIIM_PARAM, param_wr)
    time.sleep(0.001)
    write_mem32(MIIM_ADDR, 0x1f)
    time.sleep(0.003)
    # Read
    param_rd = 0x02000000 | (1 << 25) | ((bus_id & 7) << 22) | ((phy_addr & 0x1f) << 16)
    write_mem32(MIIM_PARAM, param_rd)
    time.sleep(0.001)
    write_mem32(MIIM_ADDR, reg)
    time.sleep(0.003)
    return read_mem32(MIIM_READ_DATA) & 0xffff

# Main scan
outf = open("/tmp/wc_gdb_burst_results.txt", "w")
outf.write("# WC GDB Burst Read - %s\n" % time.strftime("%Y-%m-%d %H:%M:%S"))
outf.write("# Method: GDB attach to switchd, direct MIIM access\n\n")

regs_to_read = [
    (0x81F0, "VERSIONr"),
    (0x81F2, "FIRMWARE_MODEr"),
    (0x820E, "UC_CTRLr"),
    (0x820F, "UC_INFOr"),
    (0x8061, "ANATXACONTROL0"),
    (0x8067, "TX_DRIVERr"),
    (0x8068, "TX_DRIVER2r"),
    (0x80A7, "TXB_TX_DRIVERr"),
    (0x80B0, "ANARXCONTROL0"),
    (0x80B1, "ANARXCONTROL1"),
    (0x80B2, "ANARXSTATUS0"),
    (0x82E2, "CL72_TX_FIR_TAPr"),
    (0xFFC0, "RAMWORDr"),
    (0xFFC1, "ADDRESSr"),
    (0xFFC2, "COMMANDr"),
    (0xFFC5, "CRCr"),
    (0xFFC8, "DOWNLOAD_STATUSr"),
]

# Scan PHY 17 (xe0) and PHY 21 (xe4) on BUS 2
for phy, label in [(17, "xe0-3"), (21, "xe4-7")]:
    outf.write("## %s (PHY=%d BUS=2)\n" % (label, phy))
    gdb.write("Scanning %s (PHY %d)...\n" % (label, phy))
    for addr, name in regs_to_read:
        val = wc_read(phy, 2, addr)
        line = "0x%04x %-20s = 0x%04x" % (addr, name, val)
        outf.write(line + "\n")
        gdb.write("  " + line + "\n")
    outf.write("\n")

    # Full block scan
    outf.write("### Full scan (non-zero):\n")
    for start in range(0x8000, 0x83A0, 0x10):
        for off in range(0x10):
            a = start + off
            if any(a == r[0] for r in regs_to_read):
                continue
            val = wc_read(phy, 2, a)
            if val != 0 and val != 0xffff:
                outf.write("0x%04x = 0x%04x\n" % (a, val))
    outf.write("\n")

# Probe other BUS/PHY combos
outf.write("## PHY Probe\n")
gdb.write("Probing other PHY addresses...\n")
for bus in range(4):
    for phy in [1, 5, 9, 13, 17, 21, 25, 29]:
        if bus == 2 and phy in (17, 21):
            continue
        ver = wc_read(phy, bus, 0x81F0)
        if ver != 0 and ver != 0xffff:
            line = "FOUND: BUS=%d PHY=%d VERSION=0x%04x" % (bus, phy, ver)
            outf.write(line + "\n")
            gdb.write("  " + line + "\n")

# Restore page 0 on PHY 17
param_wr = 0x02000000 | (1 << 25) | (2 << 22) | (17 << 16) | 0x0000
write_mem32(MIIM_PARAM, param_wr)
time.sleep(0.001)
write_mem32(MIIM_ADDR, 0x1f)
time.sleep(0.003)

outf.close()
gdb.write("Done! Results in /tmp/wc_gdb_burst_results.txt\n")
GDBSCRIPT

# Run GDB
gdb -batch -p $SWITCHD_PID \
    -ex "source /tmp/gdb_wc_burst.py" \
    -ex "detach" \
    -ex "quit" 2>&1 | tee "$OUTFILE"

echo "=== GDB burst read complete ==="
echo "Results: /tmp/wc_gdb_burst_results.txt"
echo "GDB log: $OUTFILE"

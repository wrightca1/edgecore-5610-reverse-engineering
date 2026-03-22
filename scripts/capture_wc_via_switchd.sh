#!/bin/bash
# Option D: Read WC registers by calling switchd's own MIIM read function via GDB.
#
# This is the ONLY safe way to read WC registers -- it uses switchd's own
# bus locking and MDIO timing. No direct writes to MIIM registers.
#
# From binary analysis:
#   soc_miim_read @ 0x00877694: stw r11, 0x4a0(r29)
#   This function takes (unit, phy_addr, reg_addr, &data_out)
#   But we need to find the actual function entry point and calling convention.
#
# Alternative: use GDB hardware watchpoint on MIIM_READ_DATA (0x4802b160)
# to capture what switchd reads, and trigger reads by flapping ports.
#
# Safest alternative: Just read MIIM_READ_DATA passively after switchd
# does its own page-select + register read during its polling loop.
# We can steer which registers it reads by setting a watchpoint on
# MIIM_PARAM and modifying the page-select value in-flight.

SWITCHD_PID=$(pidof switchd)
if [ -z "$SWITCHD_PID" ]; then
    echo "switchd not running!"
    exit 1
fi

TS=$(date +%Y%m%d_%H%M%S)
OUTFILE="/tmp/wc_switchd_capture_${TS}.txt"

echo "=== Option D: WC Capture via switchd's MIIM ==="
echo "switchd PID: $SWITCHD_PID"
echo "Output: $OUTFILE"

# GDB script: attach, set watchpoint on MIIM_ADDRESS write,
# capture the PARAM and READ_DATA for each transaction
cat > /tmp/gdb_wc_capture.gdb << 'EOF'
set pagination off
set logging file /tmp/wc_switchd_gdb.txt
set logging overwrite on
set logging on

# MIIM_ADDRESS is at BAR0+0x4a0 = 0x4802b4a0
# Every MIIM transaction writes to this register last (triggers the op)
# We watch it to capture every MDIO read/write

# Hardware watchpoint on MIIM_ADDRESS
awatch *(unsigned int*)0x4802b4a0

# For each hit, print PARAM and READ_DATA
commands 1
  silent
  set $param = *(unsigned int*)0x4802b158
  set $addr = *(unsigned int*)0x4802b4a0
  set $rdata = *(unsigned int*)0x4802b160
  set $phy = ($param >> 16) & 0x1f
  set $bus = ($param >> 22) & 0x7
  set $data = $param & 0xffff
  set $is_wr = ($data != 0)
  printf "MIIM: bus=%d phy=%d reg=0x%02x ", $bus, $phy, $addr
  if $is_wr
    printf "WR=0x%04x\n", $data
  else
    printf "RD=0x%04x\n", $rdata
  end
  continue
end

# Let it run for ~30 seconds of captures
# The user should flap ports during this time
continue
EOF

echo "Attaching GDB to switchd for passive MIIM capture..."
echo "This captures ALL MIIM transactions switchd performs."
echo "Flap ports (ip link set swpN down/up) to trigger WC register access."
echo ""
echo "Will capture for 30 seconds then detach."
echo "Press Ctrl-C in GDB to stop early."

# Run with timeout
timeout 35 gdb -batch -p $SWITCHD_PID -x /tmp/gdb_wc_capture.gdb 2>&1 | tee "$OUTFILE"

echo ""
echo "=== Capture complete ==="
echo "GDB log: /tmp/wc_switchd_gdb.txt"
echo "Full output: $OUTFILE"

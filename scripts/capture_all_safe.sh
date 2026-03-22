#!/bin/bash
# Master capture script - runs all SAFE captures in sequence.
# Does NOT touch MIIM registers directly.
#
# Captures:
# 1. Safe BAR0/DMA/SCHAN snapshot (pure read, no MIIM)
# 2. S-Channel polling during L2/ARP add (read-only poll)
# 3. BAR0 diff during L2 add (two read-only snapshots)
# 4. MIIM passive capture via GDB watchpoint (reads what switchd writes)

set -e
TS=$(date +%Y%m%d_%H%M%S)

echo "=========================================="
echo "  AS5610-52X Full Capture Suite"
echo "  $TS"
echo "=========================================="

# ---- 1. Safe baseline snapshot ----
echo ""
echo "=== 1/4: Safe BAR0/DMA/SCHAN baseline ==="
python /tmp/capture_safe_no_miim.py
BASELINE=$(ls -t /tmp/safe_capture_*.txt | head -1)
echo "Baseline: $BASELINE"

# ---- 2. S-Channel poll during L2 add ----
echo ""
echo "=== 2/4: S-Channel capture during bridge/ARP ops ==="
echo "Adding bridge and static ARP to trigger L2 table writes..."

# Take BAR0 snapshot BEFORE
python -c "
import struct, mmap, os, time
fd = os.open('/dev/mem', os.O_RDONLY | os.O_SYNC)
m = mmap.mmap(fd, 0x40000, mmap.MAP_SHARED, mmap.PROT_READ, offset=0xa0000000)
with open('/tmp/bar_before_${TS}.bin', 'wb') as f:
    f.write(m[:0x40000])
m.close()
os.close(fd)
print('BAR0 before snapshot saved')
"

# Start S-Channel polling in background
python /tmp/capture_schan.py 15 &
SCHAN_PID=$!
sleep 1

# Generate L2 table activity
brctl addbr br0 2>/dev/null || true
brctl addif br0 swp1 2>/dev/null || true
ip link set br0 up 2>/dev/null || true
ip addr add 10.200.200.1/24 dev br0 2>/dev/null || true

# Add static ARP/FDB entries to trigger table writes
bridge fdb add 00:11:22:33:44:55 dev swp1 2>/dev/null || true
bridge fdb add 00:11:22:33:44:66 dev swp1 2>/dev/null || true
bridge fdb add 00:11:22:33:44:77 dev swp1 2>/dev/null || true
arp -s 10.200.200.2 00:11:22:33:44:55 2>/dev/null || true
ip route add 10.200.201.0/24 via 10.200.200.2 2>/dev/null || true

sleep 2

# Delete them to trigger more table ops
bridge fdb del 00:11:22:33:44:55 dev swp1 2>/dev/null || true
bridge fdb del 00:11:22:33:44:66 dev swp1 2>/dev/null || true
bridge fdb del 00:11:22:33:44:77 dev swp1 2>/dev/null || true
ip route del 10.200.201.0/24 via 10.200.200.2 2>/dev/null || true
arp -d 10.200.200.2 2>/dev/null || true

sleep 2

# Wait for S-Channel capture to finish
wait $SCHAN_PID 2>/dev/null || true
SCHAN_OUT=$(ls -t /tmp/schan_capture_*.txt | head -1)
echo "S-Channel capture: $SCHAN_OUT"

# Take BAR0 snapshot AFTER
python -c "
import struct, mmap, os, time
fd = os.open('/dev/mem', os.O_RDONLY | os.O_SYNC)
m = mmap.mmap(fd, 0x40000, mmap.MAP_SHARED, mmap.PROT_READ, offset=0xa0000000)
with open('/tmp/bar_after_${TS}.bin', 'wb') as f:
    f.write(m[:0x40000])
m.close()
os.close(fd)
print('BAR0 after snapshot saved')
"

# ---- 3. Compute BAR diff ----
echo ""
echo "=== 3/4: BAR0 diff (before vs after L2 ops) ==="
python -c "
import struct
def load(path):
    with open(path, 'rb') as f:
        data = f.read()
    regs = {}
    for off in range(0, len(data), 4):
        val = struct.unpack('>I', data[off:off+4])[0]
        if val != 0:
            regs[off] = val
    return regs

before = load('/tmp/bar_before_${TS}.bin')
after = load('/tmp/bar_after_${TS}.bin')

changes = []
for off in sorted(set(list(before.keys()) + list(after.keys()))):
    b = before.get(off, 0)
    a = after.get(off, 0)
    if b != a:
        changes.append((off, b, a))

with open('/tmp/bar_diff_l2_${TS}.txt', 'w') as f:
    f.write('# BAR0 Diff: before/after L2 table ops\n')
    f.write('# Changed: %d registers\n\n' % len(changes))
    f.write('%-10s %-12s %-12s %-12s\n' % ('Offset', 'Before', 'After', 'XOR'))
    f.write('-' * 50 + '\n')
    for off, b, a in changes:
        f.write('0x%05x    0x%08x   0x%08x   0x%08x\n' % (off, b, a, b^a))
        print('  0x%05x: 0x%08x -> 0x%08x' % (off, b, a))
    if not changes:
        f.write('(no changes detected)\n')
        print('  No BAR0 changes detected')

print('BAR diff: /tmp/bar_diff_l2_${TS}.txt (%d changes)' % len(changes))
"

# ---- 4. GDB passive MIIM capture ----
echo ""
echo "=== 4/4: GDB passive MIIM capture (30s) ==="
echo "Flapping swp1 to trigger WC register access..."

# Start GDB capture in background
timeout 40 bash /tmp/capture_wc_via_switchd.sh &
GDB_PID=$!
sleep 3

# Flap port to trigger WC init sequence
ip link set swp1 down
sleep 2
ip link set swp1 up
sleep 5
ip link set swp1 down
sleep 2
ip link set swp1 up
sleep 5

# Also bring up a few other ports to capture different PHYs
for p in swp5 swp9 swp13; do
    ip link set $p up 2>/dev/null || true
    sleep 2
    ip link set $p down 2>/dev/null || true
    sleep 1
done

wait $GDB_PID 2>/dev/null || true

echo ""
echo "=========================================="
echo "  All captures complete!"
echo "  Results in /tmp/*_${TS}*"
echo "=========================================="
ls -la /tmp/*${TS}* /tmp/wc_switchd_*.txt /tmp/schan_capture_*.txt 2>/dev/null

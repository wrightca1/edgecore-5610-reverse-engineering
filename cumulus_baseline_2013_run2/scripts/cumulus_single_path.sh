#!/bin/bash
# Take swp2 down, watch OSPF reconverge to single-path via swp1, capture chip state.
set -x

OUT=/tmp/single_$(date +%Y%m%d_%H%M%S)
mkdir -p $OUT
cd $OUT

BC=/usr/lib/cumulus/bcmcmd

echo "=== BEFORE: ECMP state ==="
$BC "l3 defip show"               > 00_defip_ecmp.txt 2>&1
$BC "l3 egress show"              > 00_egress_ecmp.txt 2>&1
$BC "l3 l3table show"             > 00_l3table_ecmp.txt 2>&1
$BC "dump L3_DEFIP" | head -c 1000000 > 00_L3_DEFIP_raw_ecmp.txt 2>&1
$BC "dump ING_L3_NEXT_HOP" | head -c 500000 > 00_ING_L3_NEXT_HOP_ecmp.txt 2>&1
$BC "dump EGR_L3_NEXT_HOP" | head -c 500000 > 00_EGR_L3_NEXT_HOP_ecmp.txt 2>&1
$BC "dump L3_ECMP" | head -c 1000000  > 00_L3_ECMP_ecmp.txt 2>&1
$BC "dump L3_ECMP_COUNT" | head -c 200000 > 00_L3_ECMP_COUNT_ecmp.txt 2>&1
vtysh -c 'show ip ospf neighbor'  > 00_ospf_neighbor.txt
vtysh -c 'show ip route ospf'     > 00_zebra_route.txt
ip route                          > 00_kernel_route.txt

echo "=== strace switchd while we drop swp2 ==="
SWPID=$(pidof switchd | awk '{print $1}')
strace -p $SWPID -f -tt -e trace=read,write,ioctl,sendto,recvmsg,sendmsg -s 4096 \
       -o 01_strace.log &
SPID=$!
sleep 1

echo "=== drop swp2 ==="
ip link set swp2 down
date

echo "=== wait for OSPF to converge (~10s dead-timer adjustment) ==="
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do
  sleep 2
  neighbors=$(vtysh -c 'show ip ospf neighbor' 2>/dev/null | grep -c '^[0-9]')
  echo "T+$((i*2))s: neighbors=$neighbors"
  [ "$neighbors" -le 1 ] && [ "$i" -ge 5 ] && break
done
echo "=== done waiting ==="

kill $SPID 2>/dev/null
wait $SPID 2>/dev/null

echo "=== AFTER: single-path state ==="
$BC "l3 defip show"               > 02_defip_single.txt 2>&1
$BC "l3 egress show"              > 02_egress_single.txt 2>&1
$BC "l3 l3table show"             > 02_l3table_single.txt 2>&1
$BC "dump L3_DEFIP" | head -c 1000000 > 02_L3_DEFIP_raw_single.txt 2>&1
$BC "dump ING_L3_NEXT_HOP" | head -c 500000 > 02_ING_L3_NEXT_HOP_single.txt 2>&1
$BC "dump EGR_L3_NEXT_HOP" | head -c 500000 > 02_EGR_L3_NEXT_HOP_single.txt 2>&1
$BC "dump L3_ECMP" | head -c 1000000  > 02_L3_ECMP_single.txt 2>&1
$BC "dump L3_ECMP_COUNT" | head -c 200000 > 02_L3_ECMP_COUNT_single.txt 2>&1
vtysh -c 'show ip ospf neighbor'  > 02_ospf_neighbor.txt
vtysh -c 'show ip route ospf'     > 02_zebra_route.txt
ip route                          > 02_kernel_route.txt

echo "=== diffs ==="
diff 00_defip_ecmp.txt   02_defip_single.txt   > 03_defip_diff.txt
diff 00_egress_ecmp.txt  02_egress_single.txt  > 03_egress_diff.txt
diff 00_L3_DEFIP_raw_ecmp.txt 02_L3_DEFIP_raw_single.txt > 03_L3_DEFIP_raw_diff.txt
diff 00_EGR_L3_NEXT_HOP_ecmp.txt 02_EGR_L3_NEXT_HOP_single.txt > 03_EGR_L3_NEXT_HOP_diff.txt
diff 00_L3_ECMP_ecmp.txt 02_L3_ECMP_single.txt > 03_L3_ECMP_diff.txt

echo "=== bring swp2 back up so the switch is left in a normal state ==="
ip link set swp2 up
date

# leave a marker noting we restored
cat > 04_restored.txt <<EOF
swp2 brought back up at $(date).
OSPF should re-establish in ~30s after this script ends.
EOF

cd /tmp
tar czf $(basename $OUT).tgz $(basename $OUT) 2>/dev/null
ls -lh $(basename $OUT).tgz
echo "DONE: /tmp/$(basename $OUT).tgz"

#!/bin/bash
# Re-run steps 11 (live OSPF→ASIC trace) and 12 (hash function probe) with OSPF up.
set -u
WORK=/var/captures/trace_hash_$(date +%Y%m%d_%H%M%S)
mkdir -p $WORK
cd $WORK
BC=/usr/lib/cumulus/bcmcmd

echo "============ $(date) ============" | tee log.txt

# Verify OSPF state first - capture must happen while neighbors are FULL
echo "[*] OSPF neighbor state ===" | tee -a log.txt
vtysh -c 'show ip ospf neighbor' | tee 00_ospf_neighbor.txt
echo "[*] route count in chip:" | tee -a log.txt
$BC "l3 defip show" | head -3 | tee -a log.txt
$BC "l3 defip show" > 00_defip_baseline.txt 2>&1
ROUTECOUNT=$(grep -c "^[0-9]" 00_defip_baseline.txt)
echo "[*] $ROUTECOUNT routes in DEFIP" | tee -a log.txt
[ "$ROUTECOUNT" -lt 10 ] && { echo "[!] OSPF not fully up — aborting capture"; exit 1; }

# ============ STEP 11: live OSPF→ASIC trace =============
echo "[11] live route ADD trace ===" | tee -a log.txt

# Before-snapshots
$BC "l3 defip show" > 11a_defip_before.txt 2>&1
$BC "l3 egress show" > 11a_egress_before.txt 2>&1
$BC "l3 l3table show" > 11a_l3table_before.txt 2>&1
$BC "dump L3_DEFIP" > 11a_L3_DEFIP_raw_before.txt 2>&1
$BC "dump ING_L3_NEXT_HOP" > 11a_ING_L3_NEXT_HOP_before.txt 2>&1
$BC "dump EGR_L3_NEXT_HOP" > 11a_EGR_L3_NEXT_HOP_before.txt 2>&1
$BC "dump L3_ECMP" > 11a_L3_ECMP_before.txt 2>&1
ip route > 11a_route_before.txt

# Start strace on switchd before any changes
SWPID=$(pidof switchd | awk '{print $1}')
ZEBRA_PID=$(pidof zebra | awk '{print $1}')
echo "switchd=$SWPID zebra=$ZEBRA_PID" | tee -a log.txt

timeout 20 strace -p $SWPID -f -tt -s 4096 \
    -e trace=read,write,readv,writev,ioctl,sendto,recvmsg,sendmsg \
    -o 11b_switchd_strace.log 2>/dev/null &
SS_SW=$!
timeout 20 strace -p $ZEBRA_PID -f -tt -s 2048 \
    -e trace=read,write,readv,writev,sendto,recvmsg,sendmsg \
    -o 11b_zebra_strace.log 2>/dev/null &
SS_Z=$!

sleep 1
echo "[*] adding static route via vtysh: 10.88.88.0/24" | tee -a log.txt
date +%s.%N >> log.txt
vtysh -c 'configure terminal' -c 'ip route 10.88.88.0/24 10.101.101.2' 2>&1 > 11c_vtysh_add.log
date +%s.%N >> log.txt
sleep 2

echo "[*] adding kernel route: 10.77.77.0/24 via 10.101.101.9" | tee -a log.txt
date +%s.%N >> log.txt
ip route add 10.77.77.0/24 via 10.101.101.9 dev swp2
date +%s.%N >> log.txt
sleep 2

echo "[*] adding /32 host: 10.66.66.66 via 10.101.101.2" | tee -a log.txt
date +%s.%N >> log.txt
ip route add 10.66.66.66/32 via 10.101.101.2 dev swp1
date +%s.%N >> log.txt
sleep 2

# After-snapshots
$BC "l3 defip show" > 11d_defip_after.txt 2>&1
$BC "l3 egress show" > 11d_egress_after.txt 2>&1
$BC "l3 l3table show" > 11d_l3table_after.txt 2>&1
$BC "dump L3_DEFIP" > 11d_L3_DEFIP_raw_after.txt 2>&1
$BC "dump ING_L3_NEXT_HOP" > 11d_ING_L3_NEXT_HOP_after.txt 2>&1
$BC "dump EGR_L3_NEXT_HOP" > 11d_EGR_L3_NEXT_HOP_after.txt 2>&1
$BC "dump L3_ECMP" > 11d_L3_ECMP_after.txt 2>&1

# Stop straces
kill $SS_SW $SS_Z 2>/dev/null
wait $SS_SW $SS_Z 2>/dev/null

# Compute diffs
diff 11a_defip_before.txt 11d_defip_after.txt > 11e_defip_diff.txt
diff 11a_egress_before.txt 11d_egress_after.txt > 11e_egress_diff.txt
diff 11a_L3_DEFIP_raw_before.txt 11d_L3_DEFIP_raw_after.txt > 11e_L3_DEFIP_raw_diff.txt
diff 11a_EGR_L3_NEXT_HOP_before.txt 11d_EGR_L3_NEXT_HOP_after.txt > 11e_EGR_L3_NEXT_HOP_diff.txt
echo "[*] diffs:" | tee -a log.txt
wc -l 11e_*.txt | tee -a log.txt

# Cleanup test routes
ip route del 10.77.77.0/24 2>/dev/null
ip route del 10.66.66.66/32 2>/dev/null
vtysh -c 'configure terminal' -c 'no ip route 10.88.88.0/24 10.101.101.2' > /dev/null 2>&1

# ============ STEP 12: hash function probe ============
echo "[12] hash function probe ===" | tee -a log.txt
$BC "l3 l3table show" > 12a_l3table_before.txt 2>&1
$BC "dump L3_ENTRY_IPV4_UNICAST" > 12a_L3_ENTRY_raw_before.txt 2>&1

# Add many ARP entries — distinct IPs in our two connected subnets.
# /29 subnets give us 6 usable hosts each (8 - 2 broadcast/network). With Nexus
# taking one (.2 / .9), we have 5 free per subnet.
# Try a wider range using TEMPORARY ARP entries with arbitrary MAC.
echo "[*] inserting 12 ARP entries..." | tee -a log.txt
declare -a IPS_INSERTED=()
for i in 3 4 5 6 11 12 13 14; do
    if [ $i -le 6 ]; then DEV=swp1; else DEV=swp2; fi
    IP=10.101.101.${i}
    MAC=$(printf '02:00:00:00:00:%02x' $i)
    ip neigh add $IP lladdr ${MAC} dev $DEV nud reachable 2>&1 | tee -a log.txt
    IPS_INSERTED+=( "$IP" )
done
sleep 4  # let switchd process all the netlink events

# Capture after-state
$BC "l3 l3table show" > 12b_l3table_after.txt 2>&1
$BC "dump L3_ENTRY_IPV4_UNICAST" > 12b_L3_ENTRY_raw_after.txt 2>&1

# Diff
diff 12a_l3table_before.txt 12b_l3table_after.txt > 12c_l3table_diff.txt
diff 12a_L3_ENTRY_raw_before.txt 12b_L3_ENTRY_raw_after.txt > 12c_L3_ENTRY_raw_diff.txt
echo "[*] hash probe diff: $(wc -l < 12c_l3table_diff.txt) lines" | tee -a log.txt

# Extract just the new entries (lines starting "> ")
grep -E "^> [0-9]+ +[0-9]+" 12c_l3table_diff.txt > 12d_new_entries.txt
echo "[*] new entries:" | tee -a log.txt
cat 12d_new_entries.txt | tee -a log.txt

# Cleanup ARP
for i in 3 4 5 6 11 12 13 14; do
    if [ $i -le 6 ]; then DEV=swp1; else DEV=swp2; fi
    ip neigh del 10.101.101.${i} dev $DEV 2>/dev/null
done

echo "[12 done]" | tee -a log.txt

# ============ STEP 13: probe with VERY distinct IPs (bypass connected-subnet limit) ============
echo "[13] wider hash probe with distinct subnets via static ARPs..." | tee -a log.txt
# Use 32-bit static routes which create chip entries in L3_DEFIP (no ARP needed for these).
# This will only populate DEFIP, not L3_ENTRY hash. Skip — the connected-subnet ARP
# probe above already gives us 8 (IP, slot) pairs.

echo "============ DONE $(date) ============" | tee -a log.txt
du -sh .
ls -lh

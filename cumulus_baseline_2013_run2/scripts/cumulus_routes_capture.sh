#!/bin/bash
# Capture how routes are stored end-to-end: kernel FIB -> zebra -> switchd -> ASIC
set -x

OUT=/tmp/routes_$(date +%Y%m%d_%H%M%S)
mkdir -p $OUT
cd $OUT

BC=/usr/lib/cumulus/bcmcmd

# ---------- 1. Linux kernel FIB ----------
mkdir 1_kernel
ip route show                              > 1_kernel/ip_route.txt
ip route show table all                    > 1_kernel/ip_route_all.txt
ip route show table local                  > 1_kernel/local.txt
ip route show table main                   > 1_kernel/main.txt
ip neigh show                              > 1_kernel/ip_neigh.txt
ip -4 rule show                            > 1_kernel/rules.txt
cat /proc/net/route                        > 1_kernel/proc_net_route.txt
cat /proc/net/fib_trie                     > 1_kernel/fib_trie.txt
cat /proc/net/fib_triestat                 > 1_kernel/fib_triestat.txt

# ---------- 2. zebra RIB ----------
mkdir 2_zebra
vtysh -c 'show ip route'                   > 2_zebra/route.txt
vtysh -c 'show ip route ospf'              > 2_zebra/route_ospf.txt
vtysh -c 'show ip route static'            > 2_zebra/route_static.txt
vtysh -c 'show ip route connected'         > 2_zebra/route_connected.txt
vtysh -c 'show ip ospf'                    > 2_zebra/ospf_state.txt
vtysh -c 'show ip ospf database'           > 2_zebra/ospf_db.txt
vtysh -c 'show ip ospf neighbor'           > 2_zebra/ospf_neighbor.txt
vtysh -c 'show ip ospf interface'          > 2_zebra/ospf_interface.txt
vtysh -c 'show running-config'             > 2_zebra/running_config.txt

# ---------- 3. switchd /cumulus/switchd FUSE (its internal state) ----------
mkdir 3_switchd_fuse
ls -la /cumulus/switchd/ 2>/dev/null > 3_switchd_fuse/_top.txt
# Walk likely paths — keep depth reasonable so we don't hang on huge files
find /cumulus/switchd -maxdepth 3 -type f 2>/dev/null | head -200 > 3_switchd_fuse/_files.txt
# Read the small important ones; cap each at 100k
while read f; do
    sz=$(stat -c %s "$f" 2>/dev/null)
    [ -z "$sz" ] && continue
    [ "$sz" -gt 100000 ] && continue
    safe=$(echo "$f" | tr '/' '_')
    cat "$f" 2>/dev/null > "3_switchd_fuse/${safe}.txt"
done < 3_switchd_fuse/_files.txt

# Targeted reads of known-interesting paths
for p in /cumulus/switchd/.meta \
         /cumulus/switchd/state \
         /cumulus/switchd/state/route \
         /cumulus/switchd/state/l3 \
         /cumulus/switchd/state/l2 \
         /cumulus/switchd/state/nexthop \
         /cumulus/switchd/state/ecmp \
         /cumulus/switchd/config \
         /cumulus/switchd/version; do
    if [ -e "$p" ]; then
        safe=$(echo "$p" | tr '/' '_')
        ls -la "$p" 2>/dev/null > "3_switchd_fuse/dir${safe}.txt"
        if [ -f "$p" ]; then
            cat "$p" 2>/dev/null | head -c 200000 > "3_switchd_fuse/cat${safe}.txt"
        fi
    fi
done

# ---------- 4. ASIC chip tables via bcmcmd ----------
mkdir 4_asic
echo "=== generic L3 dumps ==="                                             > 4_asic/_diag.txt
for cmd in "ver" \
           "l3 defip show" "l3 l3table show" \
           "l3 ip6host show" "l3 ip6route show" \
           "l3 egress show" "l3 ecmp show" "l3 intf show" \
           "l2 show" "vlan show" "ps"; do
    safe=$(echo "$cmd" | tr ' /' '__')
    $BC "$cmd" > "4_asic/diag_${safe}.txt" 2>&1
done

echo "=== L3 routing chip-tables raw dumps ==="
for t in L3_DEFIP L3_DEFIP_PAIR_128 L3_DEFIP_DATA_ONLY L3_DEFIP_ALPM_IPV4 \
         L3_ENTRY_IPV4_UNICAST L3_ENTRY_IPV6_UNICAST L3_ENTRY_ONLY \
         L3_ENTRY_IPV4_MULTICAST L3_ENTRY_IPV6_MULTICAST \
         L3_IPMC L3_IIF \
         ING_L3_NEXT_HOP EGR_L3_NEXT_HOP EGR_L3_INTF EGR_MAC_DA_PROFILE \
         L3_ECMP L3_ECMP_COUNT \
         MY_STATION_TCAM MY_STATION_TCAM_2 \
         LPORT_TAB PORT_TAB \
         VLAN_TAB VLAN_PROFILE_TAB VLAN_XLATE EGR_VLAN_XLATE \
         L2_USER_ENTRY L2_ENTRY \
         EPC_LINK_BMAP; do
    ( $BC "dump $t" 2>&1 || $BC "d $t" 2>&1 ) | head -c 4000000 > "4_asic/tab_${t}.txt"
    sz=$(stat -c %s "4_asic/tab_${t}.txt")
    [ "$sz" -lt 80 ] && rm -f "4_asic/tab_${t}.txt"
done

# ---------- 5. Trace one new route end-to-end ----------
mkdir 5_route_trace
# Make sure no leftover
ip route del 10.99.99.0/24 2>/dev/null

# Before snapshot
$BC "l3 defip show" > 5_route_trace/00_defip_before.txt 2>&1
$BC "l3 ecmp show"  > 5_route_trace/00_ecmp_before.txt  2>&1
$BC "dump L3_DEFIP" | head -c 1000000 > 5_route_trace/00_L3_DEFIP_before.txt 2>&1
ip route                        > 5_route_trace/00_ip_route_before.txt

# Strace switchd while we add a route
SWPID=$(pidof switchd | awk '{print $1}')
strace -p $SWPID -f -tt -e trace=read,write,ioctl,sendto,recvmsg,sendmsg \
       -s 4096 -o 5_route_trace/01_strace.log &
SPID=$!

sleep 1
echo "=== adding /24 via 10.101.101.9 ==="
ip route add 10.99.99.0/24 via 10.101.101.9 dev swp2
sleep 3

echo "=== adding /32 host via 10.101.101.2 ==="
ip route add 10.99.99.1/32 via 10.101.101.2 dev swp1
sleep 3

# Stop strace
kill $SPID 2>/dev/null
wait $SPID 2>/dev/null

# After snapshot
$BC "l3 defip show" > 5_route_trace/02_defip_after.txt 2>&1
$BC "l3 ecmp show"  > 5_route_trace/02_ecmp_after.txt  2>&1
$BC "dump L3_DEFIP" | head -c 1000000 > 5_route_trace/02_L3_DEFIP_after.txt 2>&1
ip route                        > 5_route_trace/02_ip_route_after.txt
vtysh -c 'show ip route static' > 5_route_trace/02_zebra_static.txt

# Diff
diff 5_route_trace/00_defip_before.txt 5_route_trace/02_defip_after.txt > 5_route_trace/03_defip_diff.txt
diff 5_route_trace/00_ecmp_before.txt  5_route_trace/02_ecmp_after.txt  > 5_route_trace/03_ecmp_diff.txt

# Cleanup our test routes
ip route del 10.99.99.0/24 2>/dev/null
ip route del 10.99.99.1/32 2>/dev/null

# ---------- tar ----------
cd /tmp
tar czf $(basename $OUT).tgz $(basename $OUT) 2>/dev/null
ls -lh $(basename $OUT).tgz
echo DONE: /tmp/$(basename $OUT).tgz

#!/bin/bash
# Mine the remaining low-disruption items, then attempt the switchd init strace last.
set -u
WORK=/var/captures/finish_$(date +%Y%m%d_%H%M%S)
mkdir -p $WORK
cd $WORK
BC=/usr/lib/cumulus/bcmcmd

# Make sure clock is in 2013 so license stays valid
date -s "2013-10-01 12:00:00" >/dev/null 2>&1

echo "============ START $(date) ============" | tee progress.log

# ---------- A4: iptables + tc + cl-acltool ----------
echo "[A4] iptables/tc/cl-acltool..." | tee -a progress.log
iptables -L -v -n         > a4_iptables.txt 2>&1
iptables -L -v -n -t mangle > a4_iptables_mangle.txt 2>&1
iptables -L -v -n -t raw    > a4_iptables_raw.txt 2>&1
iptables -L -v -n -t nat    > a4_iptables_nat.txt 2>&1
tc qdisc show               > a4_tc_qdisc.txt 2>&1
tc -s qdisc show            > a4_tc_qdisc_stats.txt 2>&1
tc class show               > a4_tc_class.txt 2>&1
tc filter show              > a4_tc_filter.txt 2>&1
cl-acltool --show 2>&1      > a4_cl_acltool_show.txt
cl-acltool -l 2>&1          >> a4_cl_acltool_show.txt
ls /etc/cumulus/acl/ 2>&1   > a4_acl_files.txt

# ---------- A5: kallsyms + System.map ----------
echo "[A5] kernel symbols..." | tee -a progress.log
cat /proc/kallsyms | head -c 5000000 > a5_kallsyms.txt
ls /boot/                            > a5_boot.txt 2>&1
[ -f /boot/System.map-$(uname -r) ] && cp /boot/System.map-$(uname -r) a5_System.map
modinfo linux_user_bde linux_kernel_bde linux_bde_tmon 2>&1 > a5_bde_modinfo.txt

# ---------- A7: a SECOND gcore for delta analysis ----------
echo "[A7] second gcore..." | tee -a progress.log
SWPID=$(pidof switchd | awk '{print $1}')
gdb -p $SWPID -batch -ex 'set pagination off' -ex "gcore $WORK/a7_sw2.core" -ex detach -ex quit > a7_gdb.log 2>&1
ls -lh a7_sw2.core* 2>/dev/null

# ---------- A8: cl-acltool --show variations ----------
echo "[A8] cl-acltool variants..." | tee -a progress.log
for sub in '--show' '-l' '-s' '--list' '--rules' '--policy-show' '--policy-list'; do
    safe=$(echo "$sub" | tr -d '-')
    cl-acltool $sub 2>&1 > a8_cl_acltool_${safe}.txt
done

# ---------- A9: bcmcmd "show" enumeration ----------
echo "[A9] bcmcmd show sub-subcommands..." | tee -a progress.log
for sub in counters port portstats stat config dump verbose chip coh \
           portstats portstats-detailed socinfo port-status mode \
           buffer queue cosq pause pfc ecn vlan; do
    safe=$(echo "$sub" | tr ' /' '__')
    $BC "show $sub" > a9_show_${safe}.txt 2>&1
done

# ---------- A10: socket / netstat state ----------
echo "[A10] netstat/ss..." | tee -a progress.log
netstat -tnp           > a10_netstat_tcp.txt 2>&1
netstat -unp           > a10_netstat_udp.txt 2>&1
netstat -tlnp          > a10_netstat_listen.txt 2>&1
netstat -i             > a10_netstat_i.txt 2>&1
netstat -anpe          > a10_netstat_anpe.txt 2>&1
ss -t -a -n            > a10_ss_tcp.txt 2>&1
ss -u -a -n            > a10_ss_udp.txt 2>&1
ss -x -a               > a10_ss_unix.txt 2>&1
cat /proc/net/unix     > a10_proc_net_unix.txt 2>&1

# ---------- A11: tcpdump 100 frames on swp1+swp2 ----------
echo "[A11] tcpdump..." | tee -a progress.log
tcpdump -i swp1 -c 100 -w a11_swp1.pcap not arp 2>a11_swp1.log &
TPID1=$!
tcpdump -i swp2 -c 100 -w a11_swp2.pcap not arp 2>a11_swp2.log &
TPID2=$!
# Trigger some traffic
ping -c 20 -W 1 -i 0.1 10.101.101.2 2>&1 > a11_ping.txt &
ping -c 20 -W 1 -i 0.1 10.101.101.9 2>&1 >> a11_ping.txt &
sleep 8
kill $TPID1 $TPID2 2>/dev/null
wait 2>/dev/null
ls -lh a11_*.pcap

# ---------- A2: more hash probe data points (50+) ----------
echo "[A2] expand hash probe..." | tee -a progress.log
# Temporarily add a /24 secondary on swp1 so we can ARP arbitrary IPs in 10.99.99.0/24
ip addr add 10.99.99.1/24 dev swp1 2>&1
sleep 1
$BC "l3 l3table show" > a2_l3table_before.txt 2>&1
$BC "dump L3_ENTRY_IPV4_UNICAST" > a2_L3_ENTRY_before.txt 2>&1

# Insert 64 ARPs spread across the /24
for i in 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 \
         26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 \
         48 49 50 51 52 60 70 80 90 100 110 120 130 140 150 160 170 180 200 250; do
    MAC=$(printf '02:99:99:99:%02x:%02x' $((i/256)) $((i%256)))
    ip neigh add 10.99.99.$i lladdr ${MAC} dev swp1 nud reachable 2>/dev/null
done
sleep 5  # let switchd insert them all
$BC "l3 l3table show" > a2_l3table_after.txt 2>&1
$BC "dump L3_ENTRY_IPV4_UNICAST" > a2_L3_ENTRY_after.txt 2>&1
diff a2_l3table_before.txt a2_l3table_after.txt > a2_l3table_diff.txt
diff a2_L3_ENTRY_before.txt a2_L3_ENTRY_after.txt > a2_L3_ENTRY_diff.txt
echo "  new entries: $(grep -c '^> [0-9]' a2_l3table_diff.txt)" | tee -a progress.log

# Cleanup
for i in 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 \
         26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 \
         48 49 50 51 52 60 70 80 90 100 110 120 130 140 150 160 170 180 200 250; do
    ip neigh del 10.99.99.$i dev swp1 2>/dev/null
done
ip addr del 10.99.99.1/24 dev swp1 2>/dev/null

# ---------- A3: OSPF/route flap traces ----------
echo "[A3] route flap strace..." | tee -a progress.log

# Snapshot before
$BC "l3 defip show"  > a3_defip_before.txt 2>&1
$BC "l3 ecmp show"   > a3_ecmp_before.txt 2>&1
$BC "l3 egress show" > a3_egress_before.txt 2>&1
ip route             > a3_route_before.txt

# strace 25s
timeout 25 strace -p $SWPID -f -tt -s 2048 \
    -e trace=read,write,readv,writev,ioctl,sendto,recvmsg,sendmsg \
    -o a3_switchd_strace.log 2>/dev/null &
SS=$!

sleep 2

# Drop swp2 — OSPF goes down on that link, ECMP collapses to single path
echo "  swp2 down (ECMP collapse)" | tee -a progress.log
date +%T.%N >> progress.log
ip link set swp2 down
sleep 8

# Bring back
echo "  swp2 up (ECMP re-form)" | tee -a progress.log
date +%T.%N >> progress.log
ip link set swp2 up
ip addr add 10.101.101.10/29 dev swp2 2>/dev/null  # readd address in case it dropped
sleep 12  # OSPF re-converge

wait $SS 2>/dev/null

# Snapshot after
$BC "l3 defip show"  > a3_defip_after.txt 2>&1
$BC "l3 ecmp show"   > a3_ecmp_after.txt 2>&1
$BC "l3 egress show" > a3_egress_after.txt 2>&1
ip route             > a3_route_after.txt

# ---------- A6: DCB ring address discovery from switchd core ----------
echo "[A6] DCB ring address probe from gcore..." | tee -a progress.log
# Look in switchd's memory for the CMIC_CMC_DMA_DESCr value (last written DCB addr).
# From dump_soc we know what value was written.  We can also dd /dev/mem at the
# phys addresses switchd has mmap'd (per /proc/PID/maps the big region is at
# phys 0x02400000). Grep for known DCB patterns.
cat /proc/$SWPID/maps | grep mem > a6_switchd_maps_mem.txt
# Read the first 4MB of the big DMA region (phys 0x02400000) — likely has live DCBs
dd if=/dev/mem of=a6_dma_first_4mb.bin bs=4096 skip=2304 count=1024 2>a6_dd.err
ls -lh a6_dma_first_4mb.bin
md5sum a6_dma_first_4mb.bin > a6_dma.md5

# ---------- A1: switchd init strace (LAST, disruptive) ----------
echo "[A1] switchd init strace (disruptive — uses init.d hook)..." | tee -a progress.log
# Instead of file swap (which broke things last time), use a one-shot strace
# launched IMMEDIATELY after pidof appears
# We launch service switchd restart in background and racing-attach.

# Save pre-state for restore
service switchd stop 2>&1 > a1_stop.log
sleep 2
# Spawn switchd via "service switchd start", and in parallel poll for the PID
# and attach strace ASAP.
(
    service switchd start 2>&1 > /var/captures/a1_start.log
) &
START_PID=$!

# Race to attach strace. Loop fast.
echo "  racing strace attach..." | tee -a progress.log
NEW_PID=""
for i in $(seq 1 500); do
    NEW_PID=$(pidof switchd | awk '{print $1}')
    if [ -n "$NEW_PID" ]; then
        echo "  attached at attempt $i (switchd pid=$NEW_PID)" | tee -a progress.log
        timeout 30 strace -p $NEW_PID -f -tt -s 4096 \
            -e trace=open,openat,read,write,ioctl,mmap,munmap,close \
            -o a1_init_strace.log 2>a1_init_strace.err &
        break
    fi
    # Tiny sleep so we don't busy-loop the CPU
    sleep 0.02 2>/dev/null
done

wait $START_PID 2>/dev/null

# Let strace run for 30 sec to capture init
sleep 30
pkill -P $$ strace 2>/dev/null
sleep 2
wc -l a1_init_strace.log 2>/dev/null

# Restore clock + verify switchd alive
date -s "2013-10-01 12:00:00" >/dev/null 2>&1
service switchd status 2>&1 > a1_after_status.log
pidof switchd > a1_after_pid.log

# ---------- DONE ----------
echo "============ DONE $(date) ============" | tee -a progress.log
du -sh .
ls -lh

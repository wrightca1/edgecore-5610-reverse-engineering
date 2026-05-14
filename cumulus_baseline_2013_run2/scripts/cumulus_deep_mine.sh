#!/bin/bash
# Runs ON the switch. Captures everything else we can mine from the live system.
# Disruptive step (switchd restart) is the LAST thing.
set -u
WORK=/var/captures/mine_$(date +%Y%m%d_%H%M%S)
mkdir -p $WORK
cd $WORK
BC=/usr/lib/cumulus/bcmcmd

# Make sure swp2 is up + OSPF is healthy before we start
ip link set swp2 mtu 1500 up 2>/dev/null

echo "============ DEEP MINE $(date) ============" | tee progress.log

# ============ 1. PCI config space + CMIC PCI regs + MCS ============
echo "[1] dump pcic/pcim/mcs..." | tee -a progress.log
$BC "DUMP PCIC" > 01_dump_pcic.txt 2>&1
$BC "DUMP PCIM" > 01_dump_pcim.txt 2>&1
$BC "DUMP MCS 0 0x1000" > 01_dump_mcs.txt 2>&1
$BC "DUMP MCS 0x1000 0x1000" > 01_dump_mcs2.txt 2>&1
$BC "DUMP MCS 0x2000 0x1000" > 01_dump_mcs3.txt 2>&1
$BC "DUMP MCS 0x10000 0x10000" >> 01_dump_mcs.txt 2>&1
wc -l 01_dump_*.txt | tee -a progress.log

# ============ 2. CMC1 / CMC2 register variants ============
echo "[2] CMC1 + CMC2 register dumps..." | tee -a progress.log
{
for cmc in CMC0 CMC1 CMC2; do
    for reg in CONFIG \
               PKTDMA_DMA_CTRL PKTDMA_DMA_DESC PKTDMA_DMA_DESC_HALT \
               PKTDMA_DMA_STAT PKTDMA_DMA_STAT_CLR \
               PKTDMA_INTR_STAT PKTDMA_INTR_ENABLE \
               PKTDMA_DESC_DONE_TIMEOUT PKTDMA_DESC_DONE_INTR_THRES \
               PKTDMA_COS_CTRL_RX_0 PKTDMA_COS_CTRL_RX_1 \
               IRQ_STAT0 IRQ_STAT1 IRQ_MASK0 IRQ_MASK1 \
               SCHAN_CTRL SCHAN_MSG; do
        for idx in "" .0 .1 .2 .3; do
            r="CMIC_${cmc}_${reg}${idx}"
            v=$($BC "getreg $r" 2>&1 | head -1)
            echo "$r = $v"
        done
    done
done
} > 02_cmc_regs.txt
wc -l 02_cmc_regs.txt | tee -a progress.log
echo "  unique values (non-error): $(grep -v "Invalid\|Unknown\|Unrecognized" 02_cmc_regs.txt | grep -c '=')"

# ============ 3. Full 64 MB DMA region from /dev/mem ============
echo "[3] full 64MB DMA region..." | tee -a progress.log
# phys 0x02400000, length 64MB. skip blocks = 2304 (in 4096-block units)
dd if=/dev/mem of=03_dma_region_full.bin bs=4096 skip=2304 count=16384 conv=noerror 2>03_dma.err
ls -lh 03_dma_region_full.bin
md5sum 03_dma_region_full.bin > 03_dma_region_full.md5

# ============ 4. PHY firmware + Warpcore state ============
echo "[4] PHY/Warpcore..." | tee -a progress.log
for p in xe0 xe1 xe48 xe49; do
    $BC "phy fw dump $p" > 04_phy_fw_$p.txt 2>&1
    $BC "phy diag $p tx" > 04_phy_diag_${p}_tx.txt 2>&1
    $BC "phy diag $p rx" > 04_phy_diag_${p}_rx.txt 2>&1
    $BC "phy diag $p prbs" > 04_phy_diag_${p}_prbs.txt 2>&1
    $BC "phy raw $p 0 0" > 04_phy_raw_${p}.txt 2>&1
    # CL45 register space
    for dev in 1 2 3 4 7; do
        for r in 0x0000 0x0001 0x0002 0x0003 0x0004 0x0008 0x0009 0x000a; do
            $BC "phy raw $p $dev $r" 2>&1 | head -1
        done
    done > 04_phy_cl45_${p}.txt
done
wc -l 04_phy_*.txt | tail -5 | tee -a progress.log

# ============ 5. All bcmcmd subcommand help ============
echo "[5] all bcmcmd help..." | tee -a progress.log
for cmd in help l3 l2 vlan port fp stg dma rx tx phy mmu flow buf knet \
           getreg setreg link queue counters stat ge xe ge0 cmicm dump \
           list reg show g find pbmp config exit echo mod soc system ifp efp \
           bist diag scan socinfo ver rev mem oui stat config rcload rc; do
    $BC "help $cmd" > 05_help_${cmd}.txt 2>&1
done
wc -l 05_help_*.txt | tail -5

# ============ 6. All .bcm files + .scripts on filesystem ============
echo "[6] all .bcm files + scripts..." | tee -a progress.log
mkdir 06_bcm_files
find /usr/lib/cumulus /usr/cumulus /etc -type f \( -name '*.bcm' -o -name '*.bcm.scripts' -o -name 'rc.*' \) 2>/dev/null | tee 06_bcm_files/_list.txt | while read f; do
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    cp "$f" "06_bcm_files/$safe" 2>/dev/null
done
ls 06_bcm_files/ | wc -l
ls 06_bcm_files/ | head -20

# ============ 7. chip ID + socinfo + strapping ============
echo "[7] chip ID + socinfo..." | tee -a progress.log
$BC "show socinfo"           > 07_socinfo.txt 2>&1
$BC "ver"                    > 07_ver.txt 2>&1
$BC "rev"                    > 07_rev.txt 2>&1
$BC "config show"            > 07_config_show.txt 2>&1
$BC "config dump"            > 07_config_dump.txt 2>&1
$BC "show port"              > 07_show_port.txt 2>&1
$BC "show coh"               > 07_show_coh.txt 2>&1
$BC "system bist"            > 07_system_bist.txt 2>&1
$BC "soc info"               > 07_soc_info.txt 2>&1
$BC "show chip"              > 07_show_chip.txt 2>&1
# PCI config space raw
cat /sys/bus/pci/devices/0000:01:00.0/config | hexdump -C > 07_pci_config_full.txt

# ============ 8. MMU / QoS / Buffer state ============
echo "[8] MMU/QoS/Buffer..." | tee -a progress.log
for cmd in "mmu show" "mmu config" "mmu queue" "mmu stat" \
           "buffer show" "buffer config" \
           "queue show" "queue config" \
           "show queue" "show buffer" \
           "cosq show" "cosq config" \
           "pause show" \
           "pfc show" \
           "ecn show"; do
    safe=$(echo "$cmd" | tr ' /' '__')
    $BC "$cmd" > "08_${safe}.txt" 2>&1
done
ls 08_*.txt | wc -l

# ============ 9. FP / ACL TCAM full ============
echo "[9] FP/ACL TCAM..." | tee -a progress.log
$BC "fp show all"            > 09_fp_show_all.txt 2>&1
$BC "fp show group"          > 09_fp_show_group.txt 2>&1
$BC "fp show stats"          > 09_fp_show_stats.txt 2>&1
for slice in 0 1 2 3 4 5 6 7 8 9 10 11; do
    $BC "fp show slice $slice" > 09_fp_slice_${slice}.txt 2>&1
done
$BC "dump FP_TCAM"           > 09_FP_TCAM_raw.txt 2>&1
$BC "dump FP_GLOBAL_MASK_TCAM" > 09_FP_GLOBAL_MASK_TCAM_raw.txt 2>&1
$BC "dump FP_POLICY_TABLE"   > 09_FP_POLICY_TABLE_raw.txt 2>&1
$BC "dump FP_COUNTER_TABLE"  > 09_FP_COUNTER_TABLE_raw.txt 2>&1
$BC "dump FP_METER_TABLE"    > 09_FP_METER_TABLE_raw.txt 2>&1
wc -l 09_FP_TCAM_raw.txt

# ============ 10. /sys/kernel/debug + kernel debug ============
echo "[10] /sys/kernel/debug..." | tee -a progress.log
ls -la /sys/kernel/debug/ > 10_debug_top.txt 2>&1
find /sys/kernel/debug -maxdepth 3 -type f 2>/dev/null > 10_debug_files.txt
# Cat the small ones
mkdir -p 10_debug_files_content
while read f; do
    [ -z "$f" ] && continue
    sz=$(stat -c %s "$f" 2>/dev/null || echo 0)
    [ "$sz" -gt 100000 ] && continue
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    cat "$f" 2>/dev/null > "10_debug_files_content/$safe"
done < 10_debug_files.txt
ls 10_debug_files_content/ | wc -l

# ============ 11. OSPF→ASIC live trace ============
echo "[11] OSPF→ASIC live trace..." | tee -a progress.log
# strace zebra + switchd while we add a route
ZEBRA_PID=$(pidof zebra | awk '{print $1}')
SW_PID=$(pidof switchd | awk '{print $1}')
echo "ZEBRA_PID=$ZEBRA_PID SW_PID=$SW_PID"

# Baseline chip state
$BC "l3 defip show" > 11a_defip_before.txt 2>&1
$BC "l3 egress show" > 11a_egress_before.txt 2>&1
ip route > 11a_route_before.txt
vtysh -c 'show ip route' > 11a_vtysh_before.txt 2>&1

# Start strace
timeout 15 strace -p $SW_PID -f -tt -s 4096 \
   -e trace=read,write,readv,writev,ioctl,sendto,recvmsg,sendmsg,connect \
   -o 11b_switchd_strace.log 2>/dev/null &
SS_SW=$!
timeout 15 strace -p $ZEBRA_PID -f -tt -s 2048 \
   -e trace=read,write,sendto,recvmsg,sendmsg,connect \
   -o 11b_zebra_strace.log 2>/dev/null &
SS_Z=$!

sleep 2
# Add a route via vtysh (zebra route), then a kernel route
echo "  vtysh route add..." | tee -a progress.log
vtysh -c 'configure terminal' -c 'ip route 10.88.88.0/24 10.101.101.2' 2>&1 > 11c_vtysh_add.log
sleep 2
echo "  kernel route add..." | tee -a progress.log
ip route add 10.77.77.0/24 via 10.101.101.9 dev swp2 2>&1
sleep 2
echo "  ip neigh add (provokes ARP/L3_ENTRY)..." | tee -a progress.log
ip neigh add 10.101.101.6 lladdr 02:aa:bb:cc:dd:01 dev swp1 nud reachable 2>&1
sleep 2

# Stop strace
kill $SS_SW $SS_Z 2>/dev/null
wait $SS_SW $SS_Z 2>/dev/null

# Capture after-state
$BC "l3 defip show" > 11d_defip_after.txt 2>&1
$BC "l3 egress show" > 11d_egress_after.txt 2>&1
$BC "l3 l3table show" > 11d_l3table_after.txt 2>&1
ip route > 11d_route_after.txt

# Diffs
diff 11a_defip_before.txt 11d_defip_after.txt > 11e_defip_diff.txt
diff 11a_egress_before.txt 11d_egress_after.txt > 11e_egress_diff.txt
wc -l 11b_switchd_strace.log 11b_zebra_strace.log 11e_*.txt

# Cleanup test routes
ip route del 10.77.77.0/24 2>/dev/null
vtysh -c 'configure terminal' -c 'no ip route 10.88.88.0/24 10.101.101.2' 2>&1 >/dev/null
ip neigh del 10.101.101.6 dev swp1 2>/dev/null

# ============ 12. Hash function probe ============
echo "[12] hash function probe — insert known ARPs, see where L3_ENTRY puts them..." | tee -a progress.log
# Insert a series of known IPs in the connected subnets so kernel can ARP them.
# Cumulus's switchd will SCHAN-insert each into L3_ENTRY hash. We then dump
# L3_ENTRY and see the (IP, bucket index) pairs.
$BC "l3 l3table show" > 12a_l3table_before.txt 2>&1

# Add 10 distinct ARP entries in subnets we have (10.101.101.0/29 + 8/29)
# Connected subnet 1: 10.101.101.0/29 (via swp1) - usable .1, .2, .3, .4, .5, .6
# Connected subnet 2: 10.101.101.8/29 (via swp2) - usable .9, .10, .11, .12, .13, .14
for i in 3 4 5 6 11 12 13 14; do
    if [ $i -le 6 ]; then
        DEV=swp1; SUBNET=101
    else
        DEV=swp2; SUBNET=101
    fi
    MAC=$(printf '02:00:00:00:00:%02x' $i)
    ip neigh add 10.101.${SUBNET}.${i} lladdr ${MAC} dev $DEV nud reachable 2>&1
done
sleep 3
$BC "l3 l3table show" > 12b_l3table_after_inserts.txt 2>&1

# Compute the IP → entry-index mapping
diff 12a_l3table_before.txt 12b_l3table_after_inserts.txt > 12c_l3table_diff.txt
# Also dump raw L3_ENTRY_IPV4_UNICAST to see physical slot indices
$BC "dump L3_ENTRY_IPV4_UNICAST" > 12d_L3_ENTRY_IPV4_UNICAST_raw.txt 2>&1
wc -l 12c_l3table_diff.txt 12d_L3_ENTRY_IPV4_UNICAST_raw.txt

# Cleanup
for i in 3 4 5 6 11 12 13 14; do
    SUBNET=101; DEV=swp1
    [ $i -gt 6 ] && DEV=swp2
    ip neigh del 10.101.${SUBNET}.${i} dev $DEV 2>/dev/null
done

# ============ 13. switchd init strace (DISRUPTIVE — restart switchd) ============
echo "[13] switchd init strace (RESTART)..." | tee -a progress.log

# Save current state — be sure ospf+routing comes back after
$BC "l3 defip show" > 13a_defip_pre_restart.txt 2>&1

# Replace switchd with a wrapper that exec's strace before exec'ing real switchd.
# Backup real binary, install wrapper, restart, capture init, restore.
if [ ! -f /usr/sbin/switchd.real ]; then
    cp /usr/sbin/switchd /usr/sbin/switchd.real
fi
cat > /usr/sbin/switchd.wrap <<'WRAP'
#!/bin/sh
exec strace -o /var/captures/switchd_init.log -f -tt -s 4096 \
    -e trace=open,openat,read,write,ioctl,mmap,munmap,close,connect,bind,listen,accept,sendto,recvmsg \
    /usr/sbin/switchd.real "$@"
WRAP
chmod +x /usr/sbin/switchd.wrap

# Atomically swap
mv /usr/sbin/switchd /usr/sbin/switchd.bak
mv /usr/sbin/switchd.wrap /usr/sbin/switchd

# Restart
rm -f /var/captures/switchd_init.log
service switchd restart
echo "  switchd restarted with strace wrapper" | tee -a progress.log
sleep 25  # let init complete

# Stop strace by stopping switchd, then restore real binary
service switchd stop
sleep 2

# Restore
mv /usr/sbin/switchd.bak /usr/sbin/switchd
# Start real switchd
service switchd start
sleep 5

# Capture init strace
[ -f /var/captures/switchd_init.log ] && mv /var/captures/switchd_init.log 13b_switchd_init.log
wc -l 13b_switchd_init.log 2>/dev/null

# After restart — make sure ospf comes back up
sleep 15
vtysh -c 'show ip ospf neighbor' > 13c_ospf_after_restart.txt 2>&1
$BC "l3 defip show" > 13d_defip_post_restart.txt 2>&1

echo "============ DONE $(date) ============" | tee -a progress.log
du -sh .
ls -la | head -50

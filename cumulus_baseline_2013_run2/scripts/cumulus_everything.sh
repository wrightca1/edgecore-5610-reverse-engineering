#!/bin/bash
# Kitchen-sink capture — grab everything we might conceivably want for offline
# analysis. Strictly read-only. ~5-15 minutes runtime, output 200MB-1GB.
set -u

NEIGHBOR="${1:-10.101.101.9}"
OUT=/tmp/all_$(date +%Y%m%d_%H%M%S)
BC=/usr/lib/cumulus/bcmcmd

mkdir -p $OUT/{bar0,tables,strace,gcore,procfs,sysfs,switchd,cumulus,binaries,modules,knet,fuse,sfp,cpld,dt,logs,thermal,phy,vtysh}
cd $OUT || exit 1
exec > >(tee log.txt) 2>&1

echo "============ $0 START $(date) ============"

# ---------- 0. preflight ----------
PCI=$(lspci -nn 2>/dev/null | grep -iE "14e4:b8[46]6|broadcom.*trident" | awk '{print $1}' | head -1)
[ -z "$PCI" ] && PCI=$(lspci -nn | grep -i "14e4:" | head -1 | awk '{print $1}')
BDF=0000:${PCI}
RES0=/sys/bus/pci/devices/${BDF}/resource0
SWPID=$(pidof switchd | awk '{print $1}')
echo "PCI=$PCI  SWPID=$SWPID"
date > _ts_start.txt

# ---------- 1. BAR0 hexdump — idle + under load ----------
echo "=== 1a. BAR0 idle dump ==="
dd if=$RES0 of=bar0/idle.bin bs=4096 conv=noerror status=none 2>bar0/idle.err
ls -lh bar0/idle.bin
md5sum bar0/idle.bin > bar0/idle.md5

# Bring up a sustained ping
ping -i 0.01 -w 30 -q $NEIGHBOR > ping.txt 2>&1 &
PINGPID=$!
sleep 2  # let RX path warm up

echo "=== 1b. BAR0 loaded dump (during sustained 100Hz ping) ==="
dd if=$RES0 of=bar0/loaded.bin bs=4096 conv=noerror status=none 2>bar0/loaded.err
md5sum bar0/loaded.bin > bar0/loaded.md5

# Take 3 more snapshots ~1 sec apart to capture transient state
for i in 1 2 3; do
    sleep 1
    dd if=$RES0 of=bar0/snap_$i.bin bs=4096 conv=noerror status=none 2>/dev/null
done

# Snapshot diff hint
cmp -l bar0/idle.bin bar0/loaded.bin 2>/dev/null | head -1000 > bar0/idle_vs_loaded_first_diffs.txt
cmp -l bar0/snap_1.bin bar0/snap_3.bin 2>/dev/null | head -1000 > bar0/snap1_vs_snap3_diffs.txt
echo "BAR0 diffs captured"

# ---------- 2. switchd gcore (paused only briefly) ----------
echo "=== 2. switchd gcore ==="
if [ -n "$SWPID" ] && command -v gcore >/dev/null 2>&1; then
    timeout 120 gcore -o gcore/switchd $SWPID 2>&1 | tail -5
    ls -lh gcore/*
fi
# Also save switchd binary + its lib deps
cat /proc/$SWPID/cmdline | tr '\0' ' ' > gcore/cmdline.txt; echo >> gcore/cmdline.txt
cp -L /proc/$SWPID/exe binaries/switchd 2>/dev/null
ldd binaries/switchd > binaries/switchd.ldd 2>&1
cat /proc/$SWPID/maps > gcore/maps.txt
cat /proc/$SWPID/status > gcore/status.txt
ls -la /proc/$SWPID/fd/ > gcore/fds.txt

# ---------- 3. long strace under load ----------
echo "=== 3. strace switchd 30 sec ==="
( timeout 30 strace -p $SWPID -f -tt -s 8192 \
     -e trace=read,write,readv,writev,ioctl,mmap,munmap,pread64,pwrite64,sendto,recvmsg,sendmsg \
     -o strace/io.log 2>strace/io.err ) &
STRACE_IO=$!
( timeout 30 strace -p $SWPID -f -tt -s 256 \
     -e trace=poll,epoll_wait,select,clock_gettime \
     -o strace/poll.log 2>strace/poll.err ) &
STRACE_POLL=$!

# Snapshot /proc/$SWPID counters every 3 sec for 30 sec
( for i in $(seq 1 10); do
    date >> procfs/switchd_io_timeline.txt
    cat /proc/$SWPID/io >> procfs/switchd_io_timeline.txt 2>/dev/null
    cat /proc/$SWPID/stat >> procfs/switchd_stat_timeline.txt 2>/dev/null
    cat /proc/interrupts >> procfs/interrupts_timeline.txt 2>/dev/null
    echo "---" >> procfs/interrupts_timeline.txt
    sleep 3
  done ) &
TIMELINE=$!

# Wait
wait $STRACE_IO 2>/dev/null
wait $STRACE_POLL 2>/dev/null
wait $TIMELINE 2>/dev/null
wait $PINGPID 2>/dev/null
echo "strace + timeline + ping done"

# ---------- 4. EVERY chip table via bcmcmd ----------
echo "=== 4. all chip tables ==="
$BC "list mem"   > tables/_index_listmem.txt 2>&1
$BC "list tab"   > tables/_index_listtab.txt 2>&1
$BC "tab list"   > tables/_index_tablist.txt 2>&1

# Build a name list from any of the indexes
grep -oE '^[A-Z][A-Z0-9_]+' tables/_index_*.txt 2>/dev/null | sort -u > tables/_names.txt
if [ ! -s tables/_names.txt ]; then
    # fallback known-names list
    cat > tables/_names.txt <<'EOF'
L2_USER_ENTRY L2_ENTRY L2_ENTRY_LP L2_ENTRY_ONLY L2MC L2MCm
L3_ENTRY_IPV4_UNICAST L3_ENTRY_IPV6_UNICAST L3_ENTRY_ONLY L3_ENTRY_IPV4_MULTICAST L3_ENTRY_IPV6_MULTICAST
L3_DEFIP L3_DEFIP_PAIR_128 L3_DEFIP_DATA_ONLY L3_DEFIP_AUX_TABLE L3_DEFIP_ALPM_IPV4 L3_DEFIP_ALPM_IPV6_64 L3_DEFIP_ALPM_IPV6_128
L3_IPMC L3_IIF L3_IIF_PROFILE
ING_L3_NEXT_HOP EGR_L3_NEXT_HOP EGR_L3_INTF EGR_MAC_DA_PROFILE EGR_VLAN_XLATE EGR_PORT EGR_VLAN
L3_ECMP L3_ECMP_COUNT MULTIPATH MULTIPATH_GROUP
MY_STATION_TCAM MY_STATION_TCAM_2 MY_STATION
LPORT_TAB PORT_TAB SOURCE_TRUNK_MAP_TABLE
VLAN_TAB VLAN_PROFILE_TAB VLAN_XLATE VLAN_MAC VLAN_MEMBER_TABLE
FP_TCAM FP_GLOBAL_MASK_TCAM FP_POLICY_TABLE FP_METER_TABLE FP_COUNTER_TABLE FP_PORT_FIELD_SEL
STG_TAB STG_PER_PORT
TRUNK_GROUP TRUNK_MEMBER TRUNK_BITMAP
SRC_MAC_BLOCK MAC_BLOCK
EPC_LINK_BMAP
PORT_TRUNK_TABLE PORT_OR_TRUNK_MAC SRC_COMPRESSION DST_COMPRESSION
EGR_QUEUE_PROFILE EGR_PFC_OFFSET_TYPE_MAP
ING_DST_PORT_FILTERS
CPU_COS_MAP CPU_COS_MAP_DATA_ONLY
PHB_TO_QUEUE
IFP_REDIRECTION_PROFILE
EOF
    tr ' ' '\n' < tables/_names.txt | sort -u > /tmp/_n && mv /tmp/_n tables/_names.txt
fi

cnt=$(wc -l < tables/_names.txt)
echo "  $cnt tables to dump"
i=0
while read -r t; do
    [ -z "$t" ] && continue
    i=$((i+1))
    ( $BC "dump $t" 2>&1 || $BC "d $t" 2>&1 ) | head -c 10000000 > tables/${t}.txt 2>&1
    sz=$(stat -c %s tables/${t}.txt 2>/dev/null || echo 0)
    [ "$sz" -lt 80 ] && rm -f tables/${t}.txt
done < tables/_names.txt
echo "  $(ls tables/ | grep -v '^_' | wc -l) tables produced data"

# Direct diag commands
for cmd in "ps" "phy info" "show socinfo" "ver" "rev" \
           "l2 show" "vlan show" \
           "l3 defip show" "l3 l3table show" "l3 ip6host show" "l3 ip6route show" \
           "l3 egress show" "l3 ecmp show" "l3 intf show" \
           "fp show group" "fp show stats" "fp show slice 0" \
           "show counters cpu0" "show counters cpu" \
           "show counters xe0" "show counters xe1" \
           "g xe0" "g xe1" \
           "show port" "show portstats xe0" \
           "stg show" "trunk show" "multicast show" "show coh"; do
    safe=$(echo "$cmd" | tr ' /' '__')
    $BC "$cmd" > "tables/_diag_${safe}.txt" 2>&1
done

# CMICm regs by name (the ones we know about) — idle + loaded
echo "=== CMICm regs by-name ==="
for r in \
    CMIC_CONFIG CMIC_CMC0_CONFIG \
    CMIC_CMC0_PKTDMA_DMA_CTRL.0 CMIC_CMC0_PKTDMA_DMA_CTRL.1 CMIC_CMC0_PKTDMA_DMA_CTRL.2 CMIC_CMC0_PKTDMA_DMA_CTRL.3 \
    CMIC_CMC0_PKTDMA_DMA_DESC.0 CMIC_CMC0_PKTDMA_DMA_DESC.1 CMIC_CMC0_PKTDMA_DMA_DESC.2 CMIC_CMC0_PKTDMA_DMA_DESC.3 \
    CMIC_CMC0_PKTDMA_DMA_DESC_HALT.0 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.1 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.2 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.3 \
    CMIC_CMC0_PKTDMA_DMA_STAT CMIC_CMC0_PKTDMA_DMA_STAT_CLR \
    CMIC_CMC0_PKTDMA_INTR_STAT CMIC_CMC0_PKTDMA_INTR_ENABLE \
    CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.0 CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.1 \
    CMIC_CMC0_PKTDMA_DESC_DONE_INTR_THRES.0 CMIC_CMC0_PKTDMA_DESC_DONE_INTR_THRES.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.2 CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.3 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.2 CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.3 \
    CMIC_CMC0_IRQ_STAT0 CMIC_CMC0_IRQ_STAT1 CMIC_CMC0_IRQ_MASK0 CMIC_CMC0_IRQ_MASK1 \
    CMIC_RXBUF_THRESHOLD CMIC_RXBUF_CTRL CMIC_RXBUF_EP_RLS_CRED \
    EPC_LINK_BMAP; do
    echo "--- $r ---" >> tables/_cmicm_regs.txt
    $BC "getreg $r" >> tables/_cmicm_regs.txt 2>&1
done

# ---------- 5. KNET / BDE state ----------
echo "=== 5. BDE / KNET ==="
lsmod                                                                       > modules/lsmod.txt
for mod in linux_user_bde linux_kernel_bde linux_bde_tmon linux_bcm_knet linux_uk_proxy linux_ngbde; do
    if [ -d /sys/module/$mod ]; then
        cp -r /sys/module/$mod knet/${mod}_sys 2>/dev/null
        modinfo $mod                                                        > knet/${mod}.modinfo.txt 2>&1
        modprobe -n -v $mod                                                 > knet/${mod}.probe.txt 2>&1
        # find the .ko file and copy it
        find /lib/modules /usr/lib/modules -name "${mod}.ko*" 2>/dev/null   > knet/${mod}.ko_paths.txt
        cp /lib/modules/$(uname -r)/extra/${mod}.ko* modules/ 2>/dev/null
        cp /lib/modules/$(uname -r)/kernel/drivers/${mod}.ko* modules/ 2>/dev/null
    fi
done
find /lib/modules/$(uname -r) -name '*.ko*' 2>/dev/null > modules/all_modules.txt
# Copy any module that looks BCM-related
find /lib/modules/$(uname -r) \( -name 'linux_*.ko*' -o -name '*bcm*.ko*' -o -name '*bde*.ko*' -o -name '*knet*.ko*' -o -name 'accton*.ko*' -o -name 'ds100df410*.ko*' -o -name '*cpld*.ko*' \) 2>/dev/null -exec cp {} modules/ \;
ls -la /dev/linux-* /dev/bcm-* /dev/uk_proxy /dev/uio* 2>/dev/null          > knet/devnodes.txt
cat /proc/devices                                                           > knet/proc_devices.txt
cat /proc/modules                                                           > knet/proc_modules.txt
# /proc/bcm and /proc/linux-* if they exist
for p in /proc/bcm /proc/linux-kernel-bde /proc/linux-user-bde /proc/sb_ld; do
    if [ -e "$p" ]; then
        cp -r "$p" knet/$(basename $p)_proc 2>/dev/null
    fi
done

# ---------- 6. switchd FUSE state ----------
echo "=== 6. /cumulus/switchd FUSE ==="
ls -la /cumulus/switchd/ 2>/dev/null > fuse/_top.txt
find /cumulus/switchd -maxdepth 4 -type f 2>/dev/null | head -1000 > fuse/_files.txt
while read f; do
    sz=$(stat -c %s "$f" 2>/dev/null)
    [ -z "$sz" ] && continue
    [ "$sz" -gt 500000 ] && continue
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    cat "$f" 2>/dev/null | head -c 500000 > "fuse/${safe}"
done < fuse/_files.txt
# Also try mount-table to see how /cumulus is constructed
mount | grep -E 'cumulus|fuse'                                              > fuse/_mount.txt

# ---------- 7. system / kernel state ----------
echo "=== 7. system state ==="
uname -a                                                                    > procfs/uname.txt
cat /proc/cpuinfo                                                           > procfs/cpuinfo.txt
cat /proc/iomem                                                             > procfs/iomem.txt
cat /proc/mounts                                                            > procfs/mounts.txt
cat /proc/cmdline                                                           > procfs/cmdline.txt
cat /proc/uptime                                                            > procfs/uptime.txt
cat /proc/loadavg                                                           > procfs/loadavg.txt
free -m                                                                     > procfs/free.txt
df -h                                                                       > procfs/df.txt
mount                                                                       > procfs/mount.txt
ps auxw                                                                     > procfs/ps_auxw.txt
ip addr                                                                     > procfs/ip_addr.txt
ip -4 -d link                                                               > procfs/ip_link.txt
ip route show table all                                                     > procfs/ip_route_all.txt
ip neigh show                                                               > procfs/ip_neigh.txt
ip rule show                                                                > procfs/ip_rule.txt
cat /proc/net/route                                                         > procfs/proc_net_route.txt
cat /proc/net/fib_trie                                                      > procfs/proc_net_fib_trie.txt
cat /proc/net/arp                                                           > procfs/proc_net_arp.txt
cat /proc/interrupts                                                        > procfs/interrupts_final.txt
sysctl -a 2>/dev/null                                                       > procfs/sysctl.txt
dmesg                                                                       > logs/dmesg.txt
# pull last 20MB of each log (truncated to avoid runaway)
for log in syslog daemon.log messages kern.log auth.log dpkg.log switchd.log; do
    [ -f /var/log/$log ] && tail -c 20000000 /var/log/$log > logs/$log
done
ls -la /var/log/                                                            > logs/_listing.txt

# ---------- 8. PCI / device-tree ----------
echo "=== 8. PCI + DT ==="
lspci -nn                                                                   > procfs/lspci.txt
lspci -vvv -s ${PCI}                                                        > procfs/lspci_v.txt
hexdump -C /sys/bus/pci/devices/${BDF}/config | head -100                   > procfs/pci_config.txt
ls -la /sys/bus/pci/devices/${BDF}/                                         > procfs/pci_dev_ls.txt
if [ -d /proc/device-tree ]; then
    find /proc/device-tree -type f 2>/dev/null | while read f; do
        echo "=== $f ==="
        od -An -tx1 -v "$f" 2>/dev/null
    done > dt/device_tree.dump
fi

# ---------- 9. Cumulus config + binaries ----------
echo "=== 9. cumulus config + binaries ==="
for d in /etc/cumulus /etc/network /etc/quagga /etc/frr /etc/init.d; do
    [ -d "$d" ] || continue
    rel=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    cp -rL "$d" cumulus/${rel} 2>/dev/null
done
# /usr/lib/cumulus large files — list only
ls -laR /usr/lib/cumulus/ /usr/cumulus/ 2>/dev/null                         > cumulus/_listing.txt
# rc.* + .bcm files
for d in /usr/lib/cumulus /usr/cumulus /etc/cumulus; do
    find "$d" \( -name 'rc.*' -o -name '*.bcm' -o -name '*.conf' \) -type f 2>/dev/null | while read f; do
        rel=$(echo "$f" | tr '/' '_' | sed 's/^_//')
        cp -L "$f" cumulus/cfg_${rel} 2>/dev/null
    done
done
# Pull a few crucial binaries (bcmcmd, cl-license, switchd already grabbed via /proc/exe)
for b in /usr/lib/cumulus/bcmcmd /usr/cumulus/bin/cl-license /usr/cumulus/bin/cl-cfg \
         /usr/cumulus/bin/cl-acltool /usr/cumulus/bin/cl-ecmpcalc /usr/cumulus/bin/cl-img-pkg \
         /usr/sbin/zebra /usr/sbin/ospfd /usr/sbin/quagga; do
    [ -f "$b" ] || continue
    cp -L "$b" binaries/ 2>/dev/null
done
which bcmcmd cl-license switchd zebra ospfd                                 > binaries/_paths.txt

# ---------- 10. PHY / SerDes / per-port ----------
echo "=== 10. PHY ==="
for p in xe0 xe1; do
    $BC "phy info $p"        > phy/${p}_info.txt 2>&1
    $BC "phy control $p"     > phy/${p}_control.txt 2>&1
    $BC "phy diag $p"        > phy/${p}_diag.txt 2>&1
    $BC "phy diag $p dump"   > phy/${p}_diag_dump.txt 2>&1
    $BC "phy diag $p lanes"  > phy/${p}_lanes.txt 2>&1
    $BC "ge $p"              > phy/${p}_ge.txt 2>&1
    for r in 0 1 2 3 4 5 6 7 8 9 a b c d e f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f; do
        $BC "phy $p 0x$r" 2>&1 | head -1 | tr -d '\n' >> phy/${p}_cl22.txt
        echo "" >> phy/${p}_cl22.txt
    done
done

# ---------- 11. SFP / QSFP eeproms ----------
echo "=== 11. SFP eeproms ==="
for d in /sys/bus/i2c/devices/*/eeprom /sys/class/eeprom_dev/eeprom*; do
    [ -f "$d" ] || continue
    safe=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    od -An -tx1 -v "$d" 2>/dev/null | head -32 > sfp/${safe}.hex
done
ls /sys/class/eeprom_dev/ > sfp/_listing.txt 2>&1

# ---------- 12. CPLD ----------
echo "=== 12. CPLD ==="
for d in /sys/bus/i2c/devices/*-005[89]; do
    [ -d "$d" ] || continue
    safe=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    mkdir -p cpld/${safe}
    for f in $d/*; do
        [ -f "$f" ] || continue
        cp "$f" cpld/${safe}/$(basename $f) 2>/dev/null
    done
done

# ---------- 13. Thermal / fan ----------
echo "=== 13. thermal/fan ==="
for d in /sys/class/hwmon/* /sys/class/thermal/*; do
    [ -d "$d" ] || continue
    safe=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    mkdir -p thermal/${safe}
    for f in $d/*; do
        [ -f "$f" ] || continue
        cp "$f" thermal/${safe}/$(basename $f) 2>/dev/null
    done
done
sensors 2>&1                                                                > thermal/_sensors.txt
which fancontrol pwmconfig                                                  > thermal/_tools.txt 2>&1

# ---------- 14. vtysh state ----------
echo "=== 14. vtysh ==="
for c in 'show running-config' \
         'show ip route' 'show ip route ospf' 'show ip route connected' \
         'show ip ospf' 'show ip ospf neighbor' 'show ip ospf interface' \
         'show ip ospf database' 'show ip ospf database router' \
         'show interface' 'show interface description' 'show version'; do
    safe=$(echo "$c" | tr ' /' '__')
    vtysh -c "$c" > vtysh/${safe}.txt 2>&1
done

# ---------- 15. ONIE / U-Boot env ----------
echo "=== 15. uboot env ==="
fw_printenv                                                                 > procfs/fw_env.txt 2>&1
onie-syseeprom 2>/dev/null                                                  > procfs/syseeprom.txt
decode-syseeprom 2>/dev/null                                                > procfs/decode_syseeprom.txt

# ---------- 16. final ----------
date > _ts_end.txt
echo "============ done $(date) ============"

cd /tmp
TGZ=$(basename $OUT).tgz
tar czf $TGZ $(basename $OUT) 2>/dev/null
ls -lh $TGZ
md5sum $TGZ > ${TGZ}.md5
echo "TARBALL: /tmp/$TGZ"

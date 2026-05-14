#!/bin/bash
# v2 — fixes from v1 run: BAR0 via /dev/mem (since /sys/resource0 errors),
# DUMP SOC + DUMP SOCMEM for full register/memory dump (with names!),
# proper "list mem" parser, gcore via gdb if gcore missing.
set -u

NEIGHBOR="${1:-10.101.101.9}"
OUT=/tmp/all2_$(date +%Y%m%d_%H%M%S)
BC=/usr/lib/cumulus/bcmcmd

mkdir -p $OUT/{bar0,soc,tables,strace,gcore,procfs,switchd,cumulus,modules,knet,fuse,sfp,cpld,thermal,phy,vtysh,logs,dt}
cd $OUT || exit 1
exec > >(tee log.txt) 2>&1

echo "============ START $(date) ============"

PCI=$(lspci -nn | grep -iE "14e4:b8" | awk '{print $1}' | head -1)
BDF=0000:${PCI}
SWPID=$(pidof switchd | awk '{print $1}')
echo "PCI=$PCI SWPID=$SWPID"

# ============ 1. Chip register + memory FULL dumps (named) ============
# These are HUGE — chip-side knows the field names so it's structured.
echo "=== DUMP SOC (all SOC registers w/ names) ==="
$BC "DUMP SOC" 2>&1 | head -c 200000000 > soc/dump_soc.txt &
SOC1=$!

echo "=== DUMP SOCMEM (all chip memories w/ names) ==="
$BC "DUMP SOCMEM" 2>&1 | head -c 500000000 > soc/dump_socmem.txt &
SOC2=$!

# Other large structured dumps
$BC "DUMP SOC DIFF" 2>&1 | head -c 50000000 > soc/dump_soc_diff.txt &
SOC3=$!

# Wait
wait $SOC1 $SOC2 $SOC3 2>/dev/null
ls -lh soc/
echo "SOC dumps complete: $(wc -l soc/*.txt | tail -1)"

# ============ 2. BAR0 via /dev/mem ============
echo "=== BAR0 idle via /dev/mem ==="
# From switchd maps: BAR0 at phys 0xa0000000, 256 KB.
# Use dd with skip=phys/bs and count=size/bs.
# /dev/mem read might still fail without strict_devmem off, but try.
dd if=/dev/mem of=bar0/idle.bin bs=4096 skip=655360 count=64 2>bar0/idle.err
ls -lh bar0/idle.bin 2>/dev/null

# Sustained ping for "under load" dumps
ping -i 0.01 -w 30 -q $NEIGHBOR > ping.txt 2>&1 &
PINGPID=$!
sleep 2

echo "=== BAR0 loaded via /dev/mem ==="
dd if=/dev/mem of=bar0/loaded.bin bs=4096 skip=655360 count=64 2>bar0/loaded.err
md5sum bar0/*.bin 2>/dev/null > bar0/md5.txt
[ -s bar0/idle.bin ] && [ -s bar0/loaded.bin ] && cmp -l bar0/idle.bin bar0/loaded.bin 2>/dev/null | head -5000 > bar0/diff.txt

# ============ 3. gcore (or gdb fallback) ============
echo "=== gcore ==="
if [ -n "$SWPID" ]; then
    if command -v gcore >/dev/null 2>&1; then
        timeout 180 gcore -o gcore/switchd $SWPID 2>gcore/err.txt | tail -5
    elif command -v gdb >/dev/null 2>&1; then
        timeout 180 gdb -p $SWPID -batch \
            -ex "set pagination off" \
            -ex "gcore gcore/switchd_$SWPID.core" \
            -ex "detach" -ex "quit" 2>gcore/err.txt | tail -10
    else
        echo "no gcore/gdb"  > gcore/skipped.txt
    fi
    cat /proc/$SWPID/cmdline | tr '\0' ' ' > gcore/cmdline.txt; echo >> gcore/cmdline.txt
    cp -L /proc/$SWPID/exe binaries_switchd 2>/dev/null
    cat /proc/$SWPID/maps   > gcore/maps.txt
    cat /proc/$SWPID/status > gcore/status.txt
    ls -la /proc/$SWPID/fd/ > gcore/fds.txt
fi
ls -lh gcore/*

# ============ 4. strace + timeline (30 sec, under load) ============
echo "=== strace 30 sec ==="
( timeout 30 strace -p $SWPID -f -tt -s 8192 \
     -e trace=read,write,readv,writev,ioctl,mmap,munmap,pread64,pwrite64,sendto,recvmsg,sendmsg \
     -o strace/io.log 2>strace/io.err ) &
S1=$!
( timeout 30 strace -p $SWPID -f -tt -s 256 \
     -e trace=poll,epoll_wait,select,clock_gettime,nanosleep \
     -o strace/poll.log 2>strace/poll.err ) &
S2=$!

# Timeline of /proc/$SWPID + interrupts
( for i in $(seq 1 12); do
    date +%T >> procfs/timeline.txt
    cat /proc/$SWPID/io     >> procfs/timeline.txt
    cat /proc/$SWPID/status >> procfs/timeline.txt
    cat /proc/interrupts    >> procfs/timeline.txt
    echo "----"           >> procfs/timeline.txt
    sleep 3
  done ) &
T1=$!
wait $S1 $S2 $T1 2>/dev/null
wait $PINGPID 2>/dev/null
echo "strace done"

# ============ 5. ALL chip tables ============
echo "=== chip tables ==="
$BC "list mem" > tables/_listmem_raw.txt 2>&1
# proper parser — column 2 of the table listing (after the flags col)
awk 'NR>1 && /^ *[-bCcr]+ +[A-Z]/ {print $2}' tables/_listmem_raw.txt | sort -u > tables/_names.txt
echo "  table count: $(wc -l < tables/_names.txt)"

i=0
while read -r t; do
    [ -z "$t" ] && continue
    i=$((i+1))
    # Cap each dump at 20 MB and 10 sec
    timeout 10 $BC "dump $t" 2>&1 | head -c 20000000 > tables/${t}.txt
    sz=$(stat -c %s tables/${t}.txt 2>/dev/null || echo 0)
    [ "$sz" -lt 80 ] && rm -f tables/${t}.txt
done < tables/_names.txt
echo "  $(ls tables/*.txt 2>/dev/null | grep -v '^_' | wc -l) tables dumped"
ls tables/ | grep -v '^_' | head -20

# Diag commands
for cmd in "ps" "phy info" "show socinfo" "ver" "rev" \
           "l2 show" "vlan show" \
           "l3 defip show" "l3 l3table show" \
           "l3 egress show" "l3 ecmp show" "l3 intf show" "l3 multipath show" \
           "fp show group" "fp show stats" \
           "show counters cpu0" "show counters xe0" "show counters xe1" \
           "stg show" "trunk show" "show port"; do
    safe=$(echo "$cmd" | tr ' /' '__')
    timeout 8 $BC "$cmd" > "tables/_diag_${safe}.txt" 2>&1
done

# Named CMICm regs
echo "=== CMICm regs ==="
{
for r in \
  CMIC_CONFIG CMIC_CMC0_CONFIG \
  CMIC_CMC0_PKTDMA_DMA_CTRL.0 CMIC_CMC0_PKTDMA_DMA_CTRL.1 CMIC_CMC0_PKTDMA_DMA_CTRL.2 CMIC_CMC0_PKTDMA_DMA_CTRL.3 \
  CMIC_CMC0_PKTDMA_DMA_DESC.0 CMIC_CMC0_PKTDMA_DMA_DESC.1 CMIC_CMC0_PKTDMA_DMA_DESC.2 CMIC_CMC0_PKTDMA_DMA_DESC.3 \
  CMIC_CMC0_PKTDMA_DMA_DESC_HALT.0 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.1 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.2 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.3 \
  CMIC_CMC0_PKTDMA_DMA_STAT CMIC_CMC0_PKTDMA_DMA_STAT_CLR \
  CMIC_CMC0_PKTDMA_INTR_STAT CMIC_CMC0_PKTDMA_INTR_ENABLE \
  CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.0 CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.1 \
  CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.1 \
  CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.1 \
  CMIC_CMC0_IRQ_STAT0 CMIC_CMC0_IRQ_STAT1 CMIC_CMC0_IRQ_MASK0 CMIC_CMC0_IRQ_MASK1 \
  CMIC_RXBUF_THRESHOLD CMIC_RXBUF_CTRL CMIC_RXBUF_EP_RLS_CRED \
  EPC_LINK_BMAP; do
    echo "--- $r ---"
    timeout 3 $BC "getreg $r" 2>&1
done
} > tables/_cmicm_regs.txt

# ============ 6. modules / drivers ============
echo "=== modules ==="
lsmod                                                                   > modules/lsmod.txt
cat /proc/modules                                                       > modules/proc_modules.txt
# Copy every .ko related to BCM / accton / cpld
find /lib/modules/$(uname -r) -name '*.ko*' 2>/dev/null > modules/all_modules.txt
for keyword in linux_ bcm bde knet accton cpld ds100df410 onlp; do
    find /lib/modules/$(uname -r) -iname "*${keyword}*.ko*" 2>/dev/null -exec cp -L {} modules/ \;
done

# /proc/bcm /proc/linux-*
for p in /proc/bcm /proc/linux-kernel-bde /proc/linux-user-bde /proc/sb_ld; do
    [ -e "$p" ] && cp -rL "$p" knet/$(basename $p) 2>/dev/null
done
ls -la /dev/linux-* /dev/bcm-* /dev/uio* 2>/dev/null  > knet/devnodes.txt

# ============ 7. FUSE state ============
ls -la /cumulus/switchd/ > fuse/_top.txt 2>&1
find /cumulus/switchd -maxdepth 4 -type f 2>/dev/null > fuse/_files.txt
while read f; do
    sz=$(stat -c %s "$f" 2>/dev/null || echo 0)
    [ "$sz" -gt 500000 ] && continue
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    cat "$f" 2>/dev/null | head -c 500000 > "fuse/${safe}"
done < fuse/_files.txt

# ============ 8. system / kernel ============
uname -a > procfs/uname.txt
cat /proc/cpuinfo > procfs/cpuinfo.txt
cat /proc/iomem > procfs/iomem.txt
cat /proc/cmdline > procfs/cmdline.txt
cat /proc/mounts > procfs/mounts.txt
cat /proc/devices > procfs/devices.txt
cat /proc/interrupts > procfs/interrupts_final.txt
sysctl -a 2>/dev/null > procfs/sysctl.txt
ps auxw > procfs/ps_auxw.txt
ip addr > procfs/ip_addr.txt
ip -d link > procfs/ip_link.txt
ip route show table all > procfs/ip_route_all.txt
ip neigh show > procfs/ip_neigh.txt
ip rule show > procfs/ip_rule.txt
cat /proc/net/route > procfs/proc_net_route.txt
cat /proc/net/fib_trie > procfs/proc_net_fib_trie.txt
cat /proc/net/arp > procfs/proc_net_arp.txt
dmesg > logs/dmesg.txt
for f in syslog daemon.log messages kern.log auth.log switchd.log; do
    [ -f /var/log/$f ] && tail -c 20000000 /var/log/$f > logs/$f
done

# ============ 9. PCI / lspci ============
lspci -nn > procfs/lspci.txt
lspci -vvv -s ${PCI} > procfs/lspci_v.txt
hexdump -C /sys/bus/pci/devices/${BDF}/config > procfs/pci_config.txt 2>&1

# ============ 10. device-tree ============
if [ -d /proc/device-tree ]; then
    find /proc/device-tree -type f 2>/dev/null | while read f; do
        echo "=== $f ==="
        od -An -tx1 -v "$f" 2>/dev/null
    done > dt/device_tree.dump
fi

# ============ 11. cumulus config + binaries ============
for d in /etc/cumulus /etc/network /etc/quagga /etc/init.d /etc/default; do
    [ -d "$d" ] || continue
    rel=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    cp -rL "$d" cumulus/${rel} 2>/dev/null
done
ls -laR /usr/lib/cumulus/ /usr/cumulus/ > cumulus/_listing.txt 2>&1
find /usr/lib/cumulus /usr/cumulus -name 'rc.*' -o -name '*.bcm' -o -name '*.conf' 2>/dev/null | while read f; do
    rel=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    cp -L "$f" cumulus/cfg_${rel} 2>/dev/null
done

mkdir -p binaries
for b in /usr/lib/cumulus/bcmcmd /usr/cumulus/bin/cl-license /usr/cumulus/bin/cl-cfg \
         /usr/cumulus/bin/cl-acltool /usr/sbin/zebra /usr/sbin/ospfd /usr/sbin/quagga \
         /usr/cumulus/bin/cl-img-pkg /usr/cumulus/bin/cl-ecmpcalc; do
    [ -f "$b" ] && cp -L "$b" binaries/ 2>/dev/null
done
[ -f binaries_switchd ] && mv binaries_switchd binaries/switchd 2>/dev/null
ldd binaries/switchd > binaries/switchd.ldd 2>&1

# ============ 12. vtysh ============
for c in 'show running-config' 'show ip route' 'show ip route ospf' \
         'show ip ospf' 'show ip ospf neighbor' 'show ip ospf interface' \
         'show ip ospf database' 'show interface' 'show version'; do
    safe=$(echo "$c" | tr ' /' '__')
    vtysh -c "$c" > vtysh/${safe}.txt 2>&1
done

# ============ 13. SFP + CPLD + thermal ============
for d in /sys/class/eeprom_dev/eeprom*; do
    [ -L "$d" ] || continue
    n=$(basename $d)
    [ -f "$d/device/eeprom" ] && od -An -tx1 -v "$d/device/eeprom" 2>/dev/null | head -32 > sfp/${n}.hex
done
for d in /sys/bus/i2c/devices/*-005[89] /sys/bus/i2c/devices/*-001a; do
    [ -d "$d" ] || continue
    safe=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    cp -rL "$d" cpld/${safe} 2>/dev/null
done
for d in /sys/class/hwmon/* /sys/class/thermal/*; do
    [ -e "$d" ] || continue
    safe=$(echo "$d" | tr '/' '_' | sed 's/^_//')
    mkdir -p thermal/${safe}
    for f in $d/*; do
        [ -f "$f" ] || continue
        cp -L "$f" thermal/${safe}/$(basename $f) 2>/dev/null
    done
done

# ============ 14. PHY ============
for p in xe0 xe1; do
    $BC "phy info $p"          > phy/${p}_info.txt 2>&1
    $BC "phy control $p"       > phy/${p}_control.txt 2>&1
    $BC "phy diag $p"          > phy/${p}_diag.txt 2>&1
    $BC "phy diag $p dump"     > phy/${p}_diag_dump.txt 2>&1
    $BC "ge $p"                > phy/${p}_ge.txt 2>&1
done

# ============ 15. U-Boot env + ONIE ============
fw_printenv > procfs/fw_env.txt 2>&1
onie-syseeprom 2>/dev/null > procfs/syseeprom.txt
decode-syseeprom 2>/dev/null > procfs/decode_syseeprom.txt

# ============ 16. tarball ============
cd /tmp
TGZ=$(basename $OUT).tgz
tar czf $TGZ $(basename $OUT) 2>/dev/null
ls -lh $TGZ
md5sum $TGZ > ${TGZ}.md5
echo "DONE: /tmp/$TGZ"

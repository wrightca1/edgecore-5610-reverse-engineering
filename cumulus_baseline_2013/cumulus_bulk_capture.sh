#!/bin/bash
# cumulus_bulk_capture.sh
#
# Kitchen-sink capture of EVERYTHING needed to reverse-engineer AS5610-52X
# under Cumulus, taken in a single run so the next reflash session is short.
#
# Captures: PCIe BAR0 idle+loaded, all chip tables, switchd core + strace,
# /proc/interrupts before+after, lspci, BDE module params, dmesg, /proc/iomem,
# device tree, Cumulus rc.* config, Linux state.
#
# Strictly READ-ONLY. No bcmcmd writes, no register pokes, no service restarts.
# Idempotent — safe to rerun.
#
# Run as root.  Usage:
#   sudo ./cumulus_bulk_capture.sh [NEIGHBOR_IP]
# Default neighbor is 10.101.101.9 (Nexus eth1/34 on the test bench).

set -u
NEIGHBOR="${1:-10.101.101.9}"
OUT=/tmp/cap_$(date +%Y%m%d_%H%M%S)
BC=/usr/lib/cumulus/bcmcmd
PINGSECS=15        # how long to keep ping running for under-load capture
STRACE_SECS=8

mkdir -p "$OUT"/{tables,bar,strace,proc,switchd,cumulus}
cd "$OUT" || exit 1
exec > >(tee log.txt) 2>&1

echo "== cumulus_bulk_capture.sh =="
echo "OUT=$OUT  NEIGHBOR=$NEIGHBOR  $(date)"
uname -a; uptime
which $BC || BC=$(which bcmcmd 2>/dev/null || echo "MISSING")
echo "BC=$BC"

# ---------------------------------------------------------------- 0. preflight
echo "== preflight =="
# Auto-detect the BCM switch PCI device.  Trident+ is 14e4:b846 on AS5610.
PCI=$(lspci -nn | grep -i -E "14e4:b8[46]6|broadcom.*trident" | awk '{print $1}' | head -1)
if [ -z "$PCI" ]; then
    PCI=$(lspci -nn | grep -i "14e4:" | head -1 | awk '{print $1}')
fi
echo "PCI device: $PCI"
[ -z "$PCI" ] && { echo "ERROR: no BCM PCI device found"; exit 1; }
BDF=0000:${PCI}
RES0=/sys/bus/pci/devices/${BDF}/resource0
ls -l /sys/bus/pci/devices/${BDF}/
echo

SWPID=$(pgrep -x switchd | head -1)
echo "switchd pid: $SWPID"

# Confirm we can read BAR0 before doing the heavy work
[ -r "$RES0" ] || { echo "ERROR: cannot read $RES0 (need root)"; exit 1; }
BAR0_SZ=$(stat -c %s "$RES0")
echo "BAR0 size: $BAR0_SZ bytes"
echo

# ---------------------------------------------------------------- 1. idle dumps
echo "== 1. idle baseline =="
echo "BAR0 idle snapshot..."
dd if=$RES0 of=bar/bar0_idle.bin bs=4096 conv=noerror status=none 2>bar/bar0_idle.err
ls -lh bar/bar0_idle.bin
md5sum bar/bar0_idle.bin > bar/bar0_idle.md5

cat /proc/interrupts > proc/interrupts_before.txt
ip -s -s link show > proc/ip_link_before.txt
ip neigh show > proc/ip_neigh_before.txt
ip route show > proc/ip_route_before.txt
[ -n "$SWPID" ] && cat /proc/$SWPID/status > switchd/status_before.txt
[ -n "$SWPID" ] && cat /proc/$SWPID/io     > switchd/io_before.txt 2>/dev/null
[ -n "$SWPID" ] && cat /proc/$SWPID/stat   > switchd/stat_before.txt

# ---------------------------------------------------------------- 2. start load
echo "== 2. start sustained ping ($PINGSECS s) =="
# Light load at 100Hz to keep RX DMA active without overwhelming.
ping -i 0.01 -w $PINGSECS -q $NEIGHBOR > ping.txt 2>&1 &
PINGPID=$!
sleep 2   # let the RX path warm up

# ---------------------------------------------------------------- 3. loaded dumps
echo "== 3. under-load BAR0 + strace + tables =="
echo "BAR0 loaded snapshot..."
dd if=$RES0 of=bar/bar0_loaded.bin bs=4096 conv=noerror status=none 2>bar/bar0_loaded.err
ls -lh bar/bar0_loaded.bin
md5sum bar/bar0_loaded.bin > bar/bar0_loaded.md5

# Diff hint inside the tarball — XOR the two snapshots so changed bytes pop
echo "BAR0 diff (4-byte words that changed):"
cmp -l bar/bar0_idle.bin bar/bar0_loaded.bin 2>/dev/null | head -200 > bar/bar0_diff_first200.txt
wc -l bar/bar0_diff_first200.txt

# Strace switchd during the load period
if [ -n "$SWPID" ] && command -v strace >/dev/null; then
    echo "strace switchd for ${STRACE_SECS}s..."
    timeout $STRACE_SECS strace -p $SWPID -f -tt -s 4096 \
        -e trace=read,write,readv,writev,ioctl,mmap,munmap,pread64,pwrite64 \
        -o strace/switchd_io.log 2>strace/switchd_io.err
    timeout 2 strace -p $SWPID -f -tt -e trace=poll,epoll_wait,select \
        -o strace/switchd_poll.log 2>strace/switchd_poll.err
fi

# /proc state while loaded
cat /proc/interrupts > proc/interrupts_after.txt
ip -s -s link show > proc/ip_link_after.txt
ip neigh show > proc/ip_neigh_after.txt
[ -n "$SWPID" ] && cat /proc/$SWPID/status > switchd/status_after.txt
[ -n "$SWPID" ] && cat /proc/$SWPID/io     > switchd/io_after.txt 2>/dev/null
[ -n "$SWPID" ] && cat /proc/$SWPID/stat   > switchd/stat_after.txt

# ---------------------------------------------------------------- 4. chip tables
echo "== 4. all chip tables (bcmcmd) =="
if [ "$BC" != "MISSING" ]; then
    # Try to enumerate tables.  Different bcmcmd builds use different commands;
    # we try several to be robust.
    $BC "list mem"   > tables/_mem_index.txt 2>&1 || true
    $BC "mem list"   >> tables/_mem_index.txt 2>&1 || true
    $BC "list table" >> tables/_mem_index.txt 2>&1 || true
    $BC "tab list"   >> tables/_mem_index.txt 2>&1 || true

    # Extract candidate table names (first column of any line that looks like
    # a table name — UPPERCASE_WITH_UNDERSCORES).
    grep -oE '^[A-Z][A-Z0-9_]+' tables/_mem_index.txt | sort -u > tables/_names.txt
    wc -l tables/_names.txt

    # If enumeration failed completely, fall back to a known list.
    if [ ! -s tables/_names.txt ]; then
        cat > tables/_names.txt <<'EOF'
L2_USER_ENTRY
L2_ENTRY
L3_ENTRY_IPV4_UNICAST
L3_ENTRY_IPV6_UNICAST
L3_ENTRY_ONLY
L3_DEFIP
L3_DEFIP_PAIR_128
L3_DEFIP_ALPM_IPV4
L3_DEFIP_ALPM_IPV6_64
L3_DEFIP_ALPM_IPV6_128
ING_L3_NEXT_HOP
EGR_L3_NEXT_HOP
EGR_L3_INTF
MY_STATION_TCAM
MY_STATION_TCAM_2
LPORT_TAB
VLAN_PROFILE_TAB
VLAN_TAB
VLAN_XLATE
EGR_VLAN_XLATE
FP_TCAM
FP_GLOBAL_MASK_TCAM
STG_TAB
PORT_TAB
EGR_PORT
EPC_LINK_BMAP
TRUNK_GROUP
TRUNK_MEMBER
EOF
    fi

    # Dump each.  Cap each output at 5 MB to prevent runaway.
    while read -r t; do
        [ -z "$t" ] && continue
        # bcmcmd accepts "dump <table>" or "d <table>" depending on build
        ( $BC "dump $t" 2>&1 || $BC "d $t" 2>&1 ) \
            | head -c 5000000 > tables/${t}.txt 2>&1
        sz=$(stat -c %s tables/${t}.txt 2>/dev/null || echo 0)
        if [ "$sz" -lt 64 ]; then rm -f tables/${t}.txt; fi
    done < tables/_names.txt
    ls tables/ | head -40
    echo "... ($(ls tables/ | wc -l) files)"
else
    echo "bcmcmd MISSING — skipping table dumps"
fi

# Also dump common L3/L2 introspection commands directly
if [ "$BC" != "MISSING" ]; then
    for cmd in "ps" "phy info" \
               "l2 show" "vlan show" \
               "l3 defip show" "l3 l3table show" "l3 ip6host show" "l3 ip6route show" \
               "l3 egress show" "l3 ecmp show" "l3 intf show" \
               "fp show group" "fp show stats" \
               "show counters cpu0" \
               "show counters xe0" "show counters xe1" \
               "g xe0" "g xe1" \
               "ver" "rev" "show socinfo"; do
        safe=$(echo "$cmd" | tr ' /' '__')
        $BC "$cmd" > "tables/_diag_${safe}.txt" 2>&1
    done
fi

# Specifically dump the CMICm DMA register block by name.
# These are the regs we need MOST for the RX DMA blocker.
if [ "$BC" != "MISSING" ]; then
    {
        echo "===== CMICm DMA / RXBUF / EPC regs ====="
        for r in \
            "CMIC_CONFIG" \
            "CMIC_CMC0_CONFIG" \
            "CMIC_CMC0_PKTDMA_DMA_CTRL.0" "CMIC_CMC0_PKTDMA_DMA_CTRL.1" \
            "CMIC_CMC0_PKTDMA_DMA_CTRL.2" "CMIC_CMC0_PKTDMA_DMA_CTRL.3" \
            "CMIC_CMC0_PKTDMA_DMA_DESC.0" "CMIC_CMC0_PKTDMA_DMA_DESC.1" \
            "CMIC_CMC0_PKTDMA_DMA_DESC.2" "CMIC_CMC0_PKTDMA_DMA_DESC.3" \
            "CMIC_CMC0_PKTDMA_DMA_DESC_HALT.0" "CMIC_CMC0_PKTDMA_DMA_DESC_HALT.1" \
            "CMIC_CMC0_PKTDMA_DMA_DESC_HALT.2" "CMIC_CMC0_PKTDMA_DMA_DESC_HALT.3" \
            "CMIC_CMC0_PKTDMA_DMA_STAT" \
            "CMIC_CMC0_PKTDMA_DMA_STAT_CLR" \
            "CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.0" "CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.1" \
            "CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.2" "CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.3" \
            "CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.0" "CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.1" \
            "CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.2" "CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.3" \
            "CMIC_CMC0_PKTDMA_INTR_ENABLE" "CMIC_CMC0_PKTDMA_INTR_STAT" \
            "CMIC_RXBUF_THRESHOLD" "CMIC_RXBUF_EP_RLS_CRED" \
            "CMIC_RXBUF_CTRL" \
            "EPC_LINK_BMAP" \
            "CMIC_CMC0_IRQ_STAT0" "CMIC_CMC0_IRQ_STAT1" \
            "CMIC_CMC0_IRQ_MASK0" "CMIC_CMC0_IRQ_MASK1"; do
            echo "--- getreg $r ---"
            $BC "getreg $r" 2>&1
        done
    } > tables/_cmicm_regs.txt
fi

# ---------------------------------------------------------------- 5. wait for ping
echo "== 5. wait for ping to end =="
wait $PINGPID 2>/dev/null
tail -3 ping.txt

# ---------------------------------------------------------------- 6. switchd core
echo "== 6. switchd core dump =="
if [ -n "$SWPID" ] && command -v gcore >/dev/null; then
    echo "gcore -o switchd/core $SWPID  (this pauses switchd briefly)"
    gcore -o switchd/core $SWPID 2>&1 | tail -3
    ls -lh switchd/core.*
else
    echo "gcore unavailable, skipping"
fi
# Save switchd cmdline + maps + open fds
if [ -n "$SWPID" ]; then
    tr '\0' ' ' < /proc/$SWPID/cmdline > switchd/cmdline.txt
    echo                                >> switchd/cmdline.txt
    cp /proc/$SWPID/maps                   switchd/maps.txt
    ls -la /proc/$SWPID/fd/             >  switchd/fds.txt 2>&1
fi

# ---------------------------------------------------------------- 7. system state
echo "== 7. system state =="
lspci -vvv -s $PCI            > proc/lspci.txt
lspci -nn                     > proc/lspci_nn.txt
cat /proc/iomem               > proc/iomem.txt
cat /proc/cpuinfo             > proc/cpuinfo.txt
cat /proc/devices             > proc/devices.txt
cat /proc/modules             > proc/modules.txt
dmesg                         > proc/dmesg.txt
lsmod                         > proc/lsmod.txt
uname -a                      > proc/uname.txt
mount                         > proc/mount.txt
df -h                         > proc/df.txt
free -m                       > proc/free.txt

# BDE driver params
for mod in linux_user_bde linux_kernel_bde linux_bcm_bde linux_bcm_knet; do
    d=/sys/module/$mod/parameters
    [ -d "$d" ] || continue
    mkdir -p proc/${mod}_params
    for p in $d/*; do
        n=$(basename $p)
        echo "${n}=$(cat $p 2>/dev/null)" >> proc/${mod}_params.txt
    done
done

# Device tree (PowerPC FDT)
if [ -d /proc/device-tree ]; then
    find /proc/device-tree -type f 2>/dev/null | while read f; do
        echo "=== $f ==="
        od -An -c -v "$f" 2>/dev/null | head -10
    done > proc/device_tree.txt
fi

# ---------------------------------------------------------------- 8. cumulus config
echo "== 8. cumulus config =="
for f in /etc/cumulus/datapath/datapath.conf \
         /etc/cumulus/datapath/traffic.conf \
         /etc/cumulus/ports.conf \
         /etc/cumulus/switchd.conf \
         /etc/network/interfaces \
         /etc/quagga/Quagga.conf \
         /etc/frr/frr.conf \
         /usr/lib/cumulus/*.bcm \
         /etc/rc.local; do
    [ -f "$f" ] || continue
    rel=$(echo "$f" | tr '/' '_')
    cp "$f" "cumulus/${rel}" 2>/dev/null
done
ls -la cumulus/

# Capture all rc.* and bcm files
for d in /usr/lib/cumulus /etc/cumulus; do
    [ -d "$d" ] || continue
    find "$d" -name 'rc.*' -o -name '*.bcm' -o -name '*.conf' 2>/dev/null | while read f; do
        rel=$(echo "$f" | tr '/' '_')
        cp "$f" "cumulus/${rel}" 2>/dev/null
    done
done

# Show routes + neighbors + ARP
ip route show table all      > cumulus/routes_all.txt
ip neigh show                > cumulus/neigh.txt
arp -an                      > cumulus/arp.txt 2>/dev/null
brctl show                   > cumulus/brctl.txt 2>/dev/null

# ---------------------------------------------------------------- 9. tar it
echo "== 9. tar + summary =="
cd /tmp
TAR="$(basename $OUT).tgz"
tar czf "$TAR" "$(basename $OUT)" 2>&1 | tail
ls -lh "$TAR"
echo
echo "DONE: /tmp/$TAR"
echo "Recommended next:  scp /tmp/$TAR <workstation>:/tmp/  && rm -rf $OUT"

#!/bin/bash
# RX + TX DMA full inventory — registers, BDE state, kernel modules, /dev devices,
# strace under sustained ping load to see live DMA ioctls.
set -x

OUT=/tmp/dma_$(date +%Y%m%d_%H%M%S)
mkdir -p $OUT/{regs,bde,strace,procfs,knet}
cd $OUT

BC=/usr/lib/cumulus/bcmcmd

# ============== 1. BDE module + params ==============
echo "=== BDE kernel modules ===" > bde/modules.txt
lsmod | grep -iE "bde|knet|bcm" >> bde/modules.txt
for mod in linux_user_bde linux_kernel_bde linux_bcm_bde linux_bcm_knet \
           linux_uk_proxy linux_ngbde; do
    if [ -d /sys/module/$mod ]; then
        echo "==== /sys/module/$mod ====" >> bde/sys_module.txt
        ls -la /sys/module/$mod/parameters/ 2>/dev/null >> bde/sys_module.txt
        for p in /sys/module/$mod/parameters/*; do
            [ -f "$p" ] || continue
            n=$(basename $p)
            echo "${mod}.${n}=$(cat $p 2>/dev/null)" >> bde/params.txt
        done
        # module info
        modinfo $mod > bde/modinfo_${mod}.txt 2>&1
    fi
done

# /dev/linux-* device nodes
ls -la /dev/linux-* /dev/bcm-* /dev/bcm_* /dev/uk_proxy 2>/dev/null > bde/devnodes.txt
cat /proc/devices | grep -iE "bde|knet|bcm" > bde/proc_devices.txt
cat /proc/modules | grep -iE "bde|knet|bcm" > bde/proc_modules.txt
cat /proc/iomem > bde/iomem.txt
cat /proc/interrupts > procfs/interrupts_baseline.txt
cat /proc/net/dev > procfs/net_dev_baseline.txt

# Switchd open fds (which DMA / BDE devices it has open)
SWPID=$(pidof switchd | awk '{print $1}')
ls -la /proc/$SWPID/fd/ > bde/switchd_fds.txt 2>&1
# Maps - look for BAR0 / BDE mappings
cat /proc/$SWPID/maps > bde/switchd_maps.txt 2>&1

# ============== 2. KNET specifically (CMICm RX) ==============
# bcm-knet exposes /proc/bcm/knet/* and /proc/linux-kernel-bde/* on many systems
for p in /proc/bcm/knet/* /proc/linux-kernel-bde/* /proc/linux-user-bde/* /proc/bcm/*; do
    [ -e "$p" ] || continue
    safe=$(echo "$p" | tr '/' '_')
    if [ -d "$p" ]; then
        ls -la "$p" > "knet/${safe}_LS.txt"
    else
        cat "$p" 2>&1 | head -c 200000 > "knet/${safe}.txt"
    fi
done

# ============== 3. DMA registers idle ==============
$BC "ver"                              > regs/00_ver.txt 2>&1
$BC "soc"                              > regs/00_soc.txt 2>&1
$BC "show socinfo"                     > regs/00_socinfo.txt 2>&1

# All CMIC + CMC0 register reads we can think of
for r in \
    CMIC_CONFIG \
    CMIC_CMC0_CONFIG \
    CMIC_CMC0_PKTDMA_DMA_CTRL.0  CMIC_CMC0_PKTDMA_DMA_CTRL.1 \
    CMIC_CMC0_PKTDMA_DMA_CTRL.2  CMIC_CMC0_PKTDMA_DMA_CTRL.3 \
    CMIC_CMC0_PKTDMA_DMA_DESC.0  CMIC_CMC0_PKTDMA_DMA_DESC.1 \
    CMIC_CMC0_PKTDMA_DMA_DESC.2  CMIC_CMC0_PKTDMA_DMA_DESC.3 \
    CMIC_CMC0_PKTDMA_DMA_DESC_HALT.0 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.1 \
    CMIC_CMC0_PKTDMA_DMA_DESC_HALT.2 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.3 \
    CMIC_CMC0_PKTDMA_DMA_STAT  CMIC_CMC0_PKTDMA_DMA_STAT_CLR \
    CMIC_CMC0_PKTDMA_DMA_DEBUG_CTRL \
    CMIC_CMC0_PKTDMA_INTR_STAT  CMIC_CMC0_PKTDMA_INTR_ENABLE \
    CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.0  CMIC_CMC0_PKTDMA_DESC_DONE_TIMEOUT.1 \
    CMIC_CMC0_PKTDMA_DESC_DONE_INTR_THRES.0 CMIC_CMC0_PKTDMA_DESC_DONE_INTR_THRES.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.2 CMIC_CMC0_PKTDMA_COS_CTRL_RX_0.3 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.0 CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.1 \
    CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.2 CMIC_CMC0_PKTDMA_COS_CTRL_RX_1.3 \
    CMIC_RXBUF_THRESHOLD CMIC_RXBUF_CTRL CMIC_RXBUF_EP_RLS_CRED \
    CMIC_CMC0_IRQ_STAT0 CMIC_CMC0_IRQ_STAT1 \
    CMIC_CMC0_IRQ_MASK0 CMIC_CMC0_IRQ_MASK1 \
    EPC_LINK_BMAP \
    CMIC_DMA_STAT  CMIC_DMA_CTRL  CMIC_DMA_DESC0; do
    echo "--- getreg $r ---"
    $BC "getreg $r" 2>&1
done > regs/01_idle.txt

# ============== 4. Start ping load + strace ==============
ping -i 0.02 -w 12 -q 10.101.101.9 > ping.txt 2>&1 &
PPID_=$!
sleep 1

# strace switchd's DMA/IO activity
timeout 8 strace -p $SWPID -f -tt -s 2048 \
    -e trace=read,write,ioctl,mmap,munmap,pread64,pwrite64 \
    -o strace/dma_io.log 2>strace/dma_io.err &

# Also: read DMA registers UNDER LOAD several times to see them changing
for snap in 1 2 3 4 5; do
    sleep 0.5
    for r in \
        CMIC_CMC0_PKTDMA_DMA_CTRL.0  CMIC_CMC0_PKTDMA_DMA_CTRL.1 \
        CMIC_CMC0_PKTDMA_DMA_DESC.0  CMIC_CMC0_PKTDMA_DMA_DESC.1 \
        CMIC_CMC0_PKTDMA_DMA_DESC_HALT.0 CMIC_CMC0_PKTDMA_DMA_DESC_HALT.1 \
        CMIC_CMC0_PKTDMA_DMA_STAT \
        CMIC_CMC0_PKTDMA_INTR_STAT; do
        echo -n "snap$snap $r = "; $BC "getreg $r" 2>&1 | head -2 | tail -1
    done
done > regs/02_under_load.txt

# Wait for ping + strace
wait $PPID_ 2>/dev/null
cat /proc/interrupts > procfs/interrupts_after_load.txt
cat /proc/net/dev > procfs/net_dev_after_load.txt
diff procfs/interrupts_baseline.txt procfs/interrupts_after_load.txt > procfs/interrupts_diff.txt

# ============== 5. bcmcmd DMA introspection ==============
$BC "dma info"                         > regs/03_dma_info.txt 2>&1
$BC "dma show"                         > regs/03_dma_show.txt 2>&1
$BC "dma stat"                         > regs/03_dma_stat.txt 2>&1
$BC "show dma"                         > regs/03_show_dma.txt 2>&1
$BC "tx info"                          > regs/03_tx_info.txt 2>&1
$BC "rx info"                          > regs/03_rx_info.txt 2>&1
$BC "show counters cpu0"               > regs/03_counters_cpu0.txt 2>&1
$BC "show counters cpu"                > regs/03_counters_cpu.txt 2>&1
$BC "knet show"                        > regs/03_knet_show.txt 2>&1

# ============== 6. switchd FUSE — anything DMA-related ==============
find /cumulus/switchd -maxdepth 5 -name '*dma*' -o -name '*rx*' -o -name '*tx*' -o -name '*intr*' 2>/dev/null > fuse_dma_paths.txt
head -c 200000 /cumulus/switchd/state/* 2>/dev/null > fuse_state.txt
ls -la /cumulus/switchd/ > fuse_top.txt

# ============== 7. tar ==============
cd /tmp
tar czf $(basename $OUT).tgz $(basename $OUT) 2>/dev/null
ls -lh $(basename $OUT).tgz
echo "DONE: /tmp/$(basename $OUT).tgz"

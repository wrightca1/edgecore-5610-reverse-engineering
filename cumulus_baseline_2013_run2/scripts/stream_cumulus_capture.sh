#!/bin/bash
# Stream-capture: orchestrator runs locally, each command's output piped back
# from the switch to a file on this workstation. No disk use on switch.
set -u

NEIGHBOR=${1:-10.101.101.9}
SWITCH=${2:-10.1.1.212}

OUT=/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/streamed_$(date +%Y%m%d_%H%M%S)
mkdir -p "$OUT"/{bar0,soc,tables,strace,gcore,procfs,switchd,cumulus,modules,knet,fuse,sfp,cpld,thermal,phy,vtysh,logs,dt,binaries}
cd "$OUT" || exit 1
echo "OUT=$OUT" | tee log.txt

SSH_OPTS="-o ConnectTimeout=30 -o HostKeyAlgorithms=+ssh-rsa,ssh-dss -o PubkeyAcceptedAlgorithms=+ssh-rsa -o KexAlgorithms=+diffie-hellman-group1-sha1,diffie-hellman-group14-sha1 -o Ciphers=+aes128-cbc,3des-cbc -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"
SSHCMD() { sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S $1" 2>&1 | grep -v "Warning: Permanently\|^\[sudo\]"; }
SSHRAW() { sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S $1" 2>/dev/null; }

date | tee _ts_start.txt
echo "============ STREAMING CAPTURE START ============"

# =========== A. The biggies: stream DUMP SOC + DUMP SOCMEM straight back ===========
echo "[A] DUMP SOC (full register dump w/ names)..."
SSHRAW "/usr/lib/cumulus/bcmcmd 'DUMP SOC'" > soc/dump_soc.txt
wc -l soc/dump_soc.txt | tee -a log.txt

echo "[A] DUMP SOCMEM (full memory dump w/ names)..."
SSHRAW "/usr/lib/cumulus/bcmcmd 'DUMP SOCMEM'" > soc/dump_socmem.txt
wc -l soc/dump_socmem.txt | tee -a log.txt

echo "[A] DUMP SOC DIFF (regs differing from chip reset defaults)..."
SSHRAW "/usr/lib/cumulus/bcmcmd 'DUMP SOC DIFF'" > soc/dump_soc_diff.txt
wc -l soc/dump_soc_diff.txt | tee -a log.txt

echo "[A] DUMP SOCMEM DIFF (memories differing from chip reset)..."
SSHRAW "/usr/lib/cumulus/bcmcmd 'DUMP SOCMEM DIFF'" > soc/dump_socmem_diff.txt
wc -l soc/dump_socmem_diff.txt | tee -a log.txt

# =========== B. gcore — must go to disk on switch, then transfer ===========
echo "[B] gcore switchd (to /var/captures on switch, then scp)..."
SSHRAW "mkdir -p /var/captures && SWPID=\$(pidof switchd | awk '{print \$1}') && \
        (gcore -o /var/captures/sw \$SWPID 2>/dev/null || \
         gdb -p \$SWPID -batch -ex 'gcore /var/captures/sw.core' -ex 'detach' -ex 'quit' 2>/dev/null) && \
        ls -lh /var/captures/sw*" | tee gcore/gcore_status.txt

# scp gcore back
sshpass -p CumulusLinux! scp $SSH_OPTS cumulus@$SWITCH:'/var/captures/sw*' gcore/ 2>&1 | grep -v Warning
ls -lh gcore/

# clean off switch
SSHRAW "rm -f /var/captures/sw*"

# =========== C. switchd binary + libs ===========
echo "[C] switchd binary + ldd..."
SSHRAW "SWPID=\$(pidof switchd | awk '{print \$1}'); cat /proc/\$SWPID/exe" > binaries/switchd
SSHRAW "ldd /usr/sbin/switchd 2>&1" > binaries/switchd.ldd
SSHRAW "cat /proc/\$(pidof switchd | awk '{print \$1}')/maps" > gcore/maps.txt
SSHRAW "cat /proc/\$(pidof switchd | awk '{print \$1}')/cmdline" | tr '\0' ' ' > gcore/cmdline.txt; echo >> gcore/cmdline.txt
SSHRAW "ls -la /proc/\$(pidof switchd | awk '{print \$1}')/fd/" > gcore/fds.txt
SSHRAW "cat /proc/\$(pidof switchd | awk '{print \$1}')/status" > gcore/status.txt
chmod +x binaries/switchd

for b in /usr/lib/cumulus/bcmcmd /usr/cumulus/bin/cl-license /usr/cumulus/bin/cl-cfg \
         /usr/cumulus/bin/cl-acltool /usr/sbin/zebra /usr/sbin/ospfd /usr/sbin/quagga; do
    name=$(basename $b)
    SSHRAW "cat $b 2>/dev/null" > binaries/$name
    [ -s binaries/$name ] && chmod +x binaries/$name || rm -f binaries/$name
done
ls -lh binaries/

# =========== D. strace + long-running ping for live RX path ===========
echo "[D] strace switchd for 30 sec under ping load..."
# Start ping in bg on switch
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S sh -c 'nohup ping -i 0.01 -w 35 -q $NEIGHBOR >/dev/null 2>&1 &'" 2>&1 | grep -v Warning
sleep 2

# 30-sec strace, streamed back
SSHRAW "SWPID=\$(pidof switchd | awk '{print \$1}'); timeout 30 strace -p \$SWPID -f -tt -s 8192 -e trace=read,write,readv,writev,ioctl,mmap,munmap,pread64,pwrite64,sendto,recvmsg,sendmsg 2>&1" > strace/io.log
wc -l strace/io.log | tee -a log.txt
SSHRAW "SWPID=\$(pidof switchd | awk '{print \$1}'); timeout 8 strace -p \$SWPID -f -tt -s 256 -e trace=poll,epoll_wait,select,nanosleep 2>&1" > strace/poll.log

# =========== E. ALL chip tables (parse list mem, dump each) ===========
echo "[E] chip tables — parse list mem..."
SSHRAW "/usr/lib/cumulus/bcmcmd 'list mem'" > tables/_listmem_raw.txt
awk 'NR>1 && /^ *[-bCcr ]+ +[A-Z]/ {print $2}' tables/_listmem_raw.txt | sort -u > tables/_names.txt
N=$(wc -l < tables/_names.txt)
echo "  $N tables to fetch" | tee -a log.txt
i=0
while read -r t; do
    [ -z "$t" ] && continue
    i=$((i+1))
    SSHRAW "timeout 12 /usr/lib/cumulus/bcmcmd 'dump $t' 2>&1" > tables/${t}.txt
    sz=$(stat -c %s tables/${t}.txt 2>/dev/null || echo 0)
    [ "$sz" -lt 80 ] && rm -f tables/${t}.txt
    [ $((i % 25)) -eq 0 ] && echo "  $i/$N tables..." | tee -a log.txt
done < tables/_names.txt
echo "  total tables with data: $(ls tables/ | grep -vc '^_')" | tee -a log.txt

# Diag commands
for cmd in 'ps' 'phy info' 'show socinfo' 'ver' 'rev' \
           'l2 show' 'vlan show' \
           'l3 defip show' 'l3 l3table show' 'l3 egress show' 'l3 ecmp show' 'l3 intf show' 'l3 multipath show' \
           'fp show group' 'fp show stats' 'fp show slice 0' \
           'show counters cpu0' 'show counters xe0' 'show counters xe1' \
           'stg show' 'trunk show' 'multicast show' 'show port'; do
    safe=$(echo "$cmd" | tr ' /' '__')
    SSHRAW "timeout 8 /usr/lib/cumulus/bcmcmd '$cmd' 2>&1" > tables/_diag_${safe}.txt
done

# =========== F. CMICm regs by name + idle/loaded snapshot ===========
echo "[F] CMICm registers..."
( for r in \
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
    SSHRAW "/usr/lib/cumulus/bcmcmd 'getreg $r' 2>&1"
done ) > tables/_cmicm_regs.txt

# =========== G. PHY / per-port ===========
echo "[G] PHY..."
for p in xe0 xe1; do
    SSHRAW "/usr/lib/cumulus/bcmcmd 'phy info $p' 2>&1"     > phy/${p}_info.txt
    SSHRAW "/usr/lib/cumulus/bcmcmd 'phy control $p' 2>&1"  > phy/${p}_control.txt
    SSHRAW "/usr/lib/cumulus/bcmcmd 'phy diag $p dump' 2>&1" > phy/${p}_diag_dump.txt
    SSHRAW "/usr/lib/cumulus/bcmcmd 'ge $p' 2>&1"           > phy/${p}_ge.txt
done

# =========== H. /proc, /sys, modules, BDE, FUSE, configs ===========
echo "[H] system + modules + BDE + FUSE..."

# Modules
SSHRAW "lsmod" > modules/lsmod.txt
SSHRAW "cat /proc/modules" > modules/proc_modules.txt
SSHRAW "find /lib/modules/\$(uname -r) -name '*.ko*' 2>/dev/null" > modules/all_modules.txt
# Pull every interesting .ko by streaming
for ko in linux_user_bde linux_kernel_bde linux_bde_tmon linux_bcm_knet \
          accton_as5610_52x_cpld ds100df410 8021q at24 sff_8436_eeprom \
          adm1021 max6697 gpio_pca953x; do
    KO_PATH=$(SSHRAW "find /lib/modules -iname '${ko}.ko*' 2>/dev/null | head -1")
    [ -z "$KO_PATH" ] && continue
    KO_NAME=$(basename $KO_PATH)
    SSHRAW "cat $KO_PATH 2>/dev/null" > modules/$KO_NAME
    SSHRAW "modinfo $ko 2>&1" > modules/${ko}.modinfo.txt
done

# BDE / KNET state
SSHRAW "ls -la /dev/linux-* /dev/bcm-* /dev/uio* 2>/dev/null" > knet/devnodes.txt
for proc in /proc/bcm /proc/linux-kernel-bde /proc/linux-user-bde /proc/sb_ld; do
    SSHRAW "ls -laR $proc 2>/dev/null && echo --- && find $proc -type f -exec cat {} \\;" \
        > knet/$(basename $proc).txt
done

# /cumulus/switchd FUSE
echo "[H] FUSE walk..."
SSHRAW "ls -la /cumulus/switchd/" > fuse/_top.txt
SSHRAW "find /cumulus/switchd -maxdepth 4 -type f 2>/dev/null" > fuse/_files.txt
while read f; do
    [ -z "$f" ] && continue
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    SSHRAW "head -c 500000 '$f' 2>/dev/null" > fuse/${safe}
done < fuse/_files.txt

# /proc + ip
for f in cpuinfo iomem cmdline mounts devices uptime loadavg interrupts; do
    SSHRAW "cat /proc/$f" > procfs/$f.txt
done
SSHRAW "uname -a" > procfs/uname.txt
SSHRAW "free -m" > procfs/free.txt
SSHRAW "df -h" > procfs/df.txt
SSHRAW "ps auxw" > procfs/ps_auxw.txt
SSHRAW "ip addr" > procfs/ip_addr.txt
SSHRAW "ip -d link" > procfs/ip_link.txt
SSHRAW "ip route show table all" > procfs/ip_route_all.txt
SSHRAW "ip neigh show" > procfs/ip_neigh.txt
SSHRAW "ip rule show" > procfs/ip_rule.txt
SSHRAW "cat /proc/net/fib_trie" > procfs/proc_net_fib_trie.txt
SSHRAW "cat /proc/net/arp" > procfs/proc_net_arp.txt
SSHRAW "sysctl -a 2>/dev/null" > procfs/sysctl.txt
SSHRAW "dmesg" > logs/dmesg.txt
for l in syslog daemon.log messages kern.log auth.log switchd.log; do
    SSHRAW "tail -c 20000000 /var/log/$l 2>/dev/null" > logs/$l
done

# PCI + device-tree
SSHRAW "lspci -nn" > procfs/lspci.txt
SSHRAW "lspci -vvv -s $(SSHRAW \"lspci -nn | grep -iE '14e4:b8' | awk '{print \\\$1}'\")" > procfs/lspci_v.txt
SSHRAW "for f in \$(find /proc/device-tree -type f 2>/dev/null); do echo === \$f ===; od -An -tx1 -v \$f 2>/dev/null; done" > dt/device_tree.dump

# U-Boot env
SSHRAW "/usr/sbin/fw_printenv 2>&1" > procfs/fw_env.txt
SSHRAW "onie-syseeprom 2>/dev/null" > procfs/syseeprom.txt
SSHRAW "decode-syseeprom 2>/dev/null" > procfs/decode_syseeprom.txt

# =========== I. cumulus config / running config ===========
echo "[I] cumulus config + vtysh..."
SSHRAW "tar c -C / etc/cumulus etc/network etc/quagga etc/init.d etc/default 2>/dev/null" | tar x -C cumulus/
SSHRAW "ls -laR /usr/lib/cumulus /usr/cumulus 2>/dev/null" > cumulus/_listing.txt

for c in 'show running-config' 'show ip route' 'show ip route ospf' \
         'show ip ospf' 'show ip ospf neighbor' 'show ip ospf interface' \
         'show ip ospf database' 'show interface' 'show version'; do
    safe=$(echo "$c" | tr ' /' '__')
    SSHRAW "vtysh -c '$c' 2>&1" > vtysh/${safe}.txt
done

# =========== J. SFP / CPLD / thermal ===========
echo "[J] SFP/CPLD/thermal..."
SSHRAW "ls /sys/class/eeprom_dev/" > sfp/_listing.txt
SSHRAW "for d in /sys/class/eeprom_dev/eeprom*; do
  [ -L \$d ] || continue
  n=\$(basename \$d)
  [ -f \$d/device/eeprom ] && echo === \$n === && od -An -tx1 -v \$d/device/eeprom 2>/dev/null | head -64
done" > sfp/all_hex.txt

SSHRAW "for d in /sys/bus/i2c/devices/*-005[89] /sys/bus/i2c/devices/*-001a; do
  [ -d \$d ] || continue
  echo === \$d ===
  ls -la \$d/
  for f in \$d/*; do [ -f \$f ] && echo \"--- \$(basename \$f) ---\" && cat \$f 2>/dev/null | head -c 1024; done
done" > cpld/all_cpld.txt

SSHRAW "for d in /sys/class/hwmon/* /sys/class/thermal/*; do
  [ -e \$d ] || continue
  echo === \$d ===
  ls -la \$d/
  for f in \$d/*; do [ -f \$f ] && echo \"--- \$(basename \$f) ---\" && cat \$f 2>/dev/null | head -c 1024; done
done" > thermal/all_thermal.txt

date | tee _ts_end.txt
echo "============ STREAM CAPTURE DONE ============"
du -sh "$OUT"
ls "$OUT"/

# Pack a tarball for easy archival
tar czf "${OUT}.tgz" -C "$(dirname $OUT)" "$(basename $OUT)" 2>/dev/null
ls -lh "${OUT}.tgz"

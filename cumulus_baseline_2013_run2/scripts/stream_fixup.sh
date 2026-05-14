#!/bin/bash
# Fixup capture — retry the things that failed in v1:
# 1. strace (longer, more verbose, with load)
# 2. gcore via gdb directly (gcore not in PATH on Cumulus 2.5)
# 3. all chip tables (better name parser using listmem we already have)
# 4. BAR0 hexdump via /dev/mem (root can read /dev/mem)
# 5. thermal/CPLD/SFP (avoid heredoc quoting hell)
set -u

NEIGHBOR=${1:-10.101.101.9}
SWITCH=${2:-10.1.1.212}
OUT=/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/fixup_$(date +%Y%m%d_%H%M%S)
mkdir -p "$OUT"/{bar0,strace,gcore,tables,thermal,cpld,sfp,switchd}
cd "$OUT" || exit 1

SSH_OPTS="-o ConnectTimeout=30 -o HostKeyAlgorithms=+ssh-rsa,ssh-dss -o PubkeyAcceptedAlgorithms=+ssh-rsa -o KexAlgorithms=+diffie-hellman-group1-sha1,diffie-hellman-group14-sha1 -o Ciphers=+aes128-cbc,3des-cbc -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"
SSHRAW() { sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S $1" 2>/dev/null; }

echo "OUT=$OUT" | tee log.txt

# --- 1. BAR0 via /dev/mem ---
# phys 0xa0000000 = decimal 2684354560, /4096 = skip 655360 blocks
echo "[1] BAR0 idle via /dev/mem..." | tee -a log.txt
SSHRAW "dd if=/dev/mem bs=4096 skip=655360 count=64 2>/dev/null" > bar0/idle.bin
ls -lh bar0/idle.bin

# Start ping in background on switch for under-load capture
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S sh -c 'nohup ping -i 0.005 -w 60 -q $NEIGHBOR >/dev/null 2>&1 &'" 2>&1 | grep -v Warning
sleep 2

echo "[1] BAR0 loaded via /dev/mem..." | tee -a log.txt
SSHRAW "dd if=/dev/mem bs=4096 skip=655360 count=64 2>/dev/null" > bar0/loaded.bin
ls -lh bar0/loaded.bin

# also the second mmap region (the big one at 0x02400000)
echo "[1] BAR1/DMA region (0x02400000, 64MB)..." | tee -a log.txt
SSHRAW "dd if=/dev/mem bs=4096 skip=2304 count=128 2>/dev/null" > bar0/dma_region.bin
ls -lh bar0/dma_region.bin

# diff
[ -s bar0/idle.bin ] && [ -s bar0/loaded.bin ] && cmp -l bar0/idle.bin bar0/loaded.bin 2>/dev/null | head -5000 > bar0/idle_vs_loaded_diff.txt && echo "  diff bytes: $(wc -l < bar0/idle_vs_loaded_diff.txt)"

# --- 2. strace, 60 sec with explicit ping flood ---
echo "[2] strace switchd for 60 sec under ping flood..." | tee -a log.txt
# This time use ssh -o ServerAliveInterval so the connection doesn't drop
# and redirect strace stderr too — many strace messages go to stderr
sshpass -p CumulusLinux! ssh -o ServerAliveInterval=15 $SSH_OPTS cumulus@$SWITCH \
   "echo CumulusLinux! | sudo -S bash -c 'SWPID=\$(pidof switchd | awk \"{print \\\$1}\"); echo SWPID=\$SWPID; timeout 60 strace -p \$SWPID -f -tt -s 8192 -e trace=read,write,readv,writev,ioctl,mmap,munmap,pread64,pwrite64,sendto,recvmsg,sendmsg 2>&1'" \
   > strace/io_60sec.log 2>strace/io_60sec.err
wc -l strace/io_60sec.log

# Quick syscall summary
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH \
   "echo CumulusLinux! | sudo -S bash -c 'SWPID=\$(pidof switchd | awk \"{print \\\$1}\"); timeout 15 strace -c -p \$SWPID -f 2>&1'" \
   > strace/syscall_summary.txt 2>&1
cat strace/syscall_summary.txt | head -30

# --- 3. gcore via gdb (gcore binary missing in this Cumulus) ---
echo "[3] gcore switchd via gdb..." | tee -a log.txt
SSHRAW "which gcore gdb"   > gcore/tools.txt
cat gcore/tools.txt

SSHRAW "SWPID=\$(pidof switchd | awk '{print \$1}'); mkdir -p /var/captures && rm -f /var/captures/sw.core* && \
        timeout 120 gdb -p \$SWPID -batch \
          -ex 'set pagination off' \
          -ex 'gcore /var/captures/sw.core' \
          -ex 'detach' -ex 'quit' 2>&1" > gcore/gdb_output.log
cat gcore/gdb_output.log | tail -10

SSHRAW "ls -lh /var/captures/" > gcore/var_captures_ls.txt
cat gcore/var_captures_ls.txt

# scp core back
echo "[3] scp gcore back..." | tee -a log.txt
sshpass -p CumulusLinux! scp $SSH_OPTS cumulus@$SWITCH:'/var/captures/sw.core*' gcore/ 2>&1 | grep -v Warning
ls -lh gcore/

# clean from switch
SSHRAW "rm -f /var/captures/sw.core*"

# --- 4. All chip tables — parse known list-mem format properly ---
# The format on this Cumulus is:
# " -----C  DLB_HGT_GROUP_MEMBERSHIP    8      DLB_HGT Group Member ..."
# so col $2 after the flags col is the name.  Some lines wrap; filter by /^ *[-bCcrP]+ +/.
SSHRAW "/usr/lib/cumulus/bcmcmd 'list mem'" > tables/_listmem_raw.txt
# Filter: starts with whitespace + flag chars + 2+ spaces, then UPPER name
awk 'NR>1 && $1 ~ /^[-bcCrPL]+$/ && $2 ~ /^[A-Z][A-Z0-9_]+$/ {print $2}' tables/_listmem_raw.txt | sort -u > tables/_names.txt
N=$(wc -l < tables/_names.txt)
echo "  parsed $N table names" | tee -a log.txt
head -10 tables/_names.txt | tee -a log.txt

# Dump each in parallel batches of 4 for speed
i=0
while read -r t; do
    [ -z "$t" ] && continue
    i=$((i+1))
    {
        SSHRAW "timeout 20 /usr/lib/cumulus/bcmcmd 'dump $t' 2>&1" > "tables/${t}.txt"
        sz=$(stat -c %s "tables/${t}.txt" 2>/dev/null || echo 0)
        [ "$sz" -lt 80 ] && rm -f "tables/${t}.txt"
    } &
    # parallelism cap
    if [ $((i % 4)) -eq 0 ]; then wait; fi
done < tables/_names.txt
wait
echo "  tables with data: $(ls tables/ | grep -v '^_' | wc -l)" | tee -a log.txt

# --- 5. thermal / hwmon / fan — flat string capture ---
echo "[5] thermal/hwmon..." | tee -a log.txt
SSHRAW 'find /sys/class/hwmon /sys/class/thermal -type f 2>/dev/null | xargs -I{} sh -c "echo \"=== {} ===\"; head -c 256 {} 2>/dev/null; echo"' > thermal/all.txt
SSHRAW 'sensors 2>&1'                                       > thermal/sensors.txt
SSHRAW 'cat /var/log/syslog 2>/dev/null | grep -iE "fan|temp|thermal|cpld" | tail -100' > thermal/syslog_grep.txt

# CPLD via i2c sysfs
echo "[5] CPLD..." | tee -a log.txt
SSHRAW 'find /sys/bus/i2c/devices -maxdepth 2 -type d 2>/dev/null | head -100' > cpld/i2c_devs.txt
SSHRAW 'for d in /sys/bus/i2c/devices/*-005[89] /sys/bus/i2c/devices/*-001a /sys/bus/i2c/devices/*-005f /sys/bus/i2c/devices/*-0060 /sys/bus/i2c/devices/*-0062 /sys/bus/i2c/devices/*-0064 /sys/bus/i2c/devices/*-0050; do
  [ -d "$d" ] || continue
  echo === $d ===
  cat "$d/name" 2>/dev/null
  for f in "$d"/*; do
    [ -f "$f" ] || continue
    nm=$(basename $f)
    val=$(head -c 256 "$f" 2>/dev/null)
    echo "$nm = $val"
  done
done' > cpld/cpld_state.txt
wc -l cpld/cpld_state.txt

# SFP eeproms (compact)
echo "[5] SFP eeproms..." | tee -a log.txt
SSHRAW 'for d in /sys/class/eeprom_dev/eeprom*; do
  [ -L "$d" ] || continue
  e="$d/device/eeprom"
  [ -f "$e" ] || continue
  echo === $d ===
  od -An -tx1 -v -N 256 "$e" 2>/dev/null
done' > sfp/all.hex

# --- 6. /cumulus/switchd FUSE (the SFS) — full walk ---
echo "[6] /cumulus/switchd full walk..." | tee -a log.txt
SSHRAW 'ls -laR /cumulus/switchd/ 2>/dev/null' > switchd/listing.txt
SSHRAW 'find /cumulus/switchd -maxdepth 6 -type f 2>/dev/null' > switchd/files.txt
wc -l switchd/files.txt
mkdir -p switchd/contents
while read f; do
    [ -z "$f" ] && continue
    safe=$(echo "$f" | tr '/' '_' | sed 's/^_//')
    SSHRAW "head -c 1000000 '$f' 2>/dev/null" > "switchd/contents/${safe}"
done < switchd/files.txt
echo "  collected $(ls switchd/contents/ | wc -l) FUSE files" | tee -a log.txt

echo "============ FIXUP DONE ============"
du -sh "$OUT"
tar czf "${OUT}.tgz" -C "$(dirname $OUT)" "$(basename $OUT)" 2>/dev/null
ls -lh "${OUT}.tgz"

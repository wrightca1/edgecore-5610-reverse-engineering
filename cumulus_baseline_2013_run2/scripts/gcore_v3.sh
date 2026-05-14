#!/bin/bash
# v3 — fix the previous quoting bugs: scp scripts to switch, run, scp output back.
# Avoids heredoc-over-ssh and var-expansion-in-quote issues.
set -u

SWITCH=10.1.1.212
OUT=/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/gcorev3_$(date +%Y%m%d_%H%M%S)
mkdir -p "$OUT"/{gcore,sfp,cpld,thermal,switchd,bar0}
cd "$OUT" || exit 1

SSH_OPTS="-o ConnectTimeout=30 -o HostKeyAlgorithms=+ssh-rsa,ssh-dss -o PubkeyAcceptedAlgorithms=+ssh-rsa -o KexAlgorithms=+diffie-hellman-group1-sha1,diffie-hellman-group14-sha1 -o Ciphers=+aes128-cbc,3des-cbc -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"

echo "OUT=$OUT" | tee log.txt

# Write the remote-side script locally, scp it, run it on switch, scp output back.
cat > /tmp/_remote_capture.sh <<'REMOTE'
#!/bin/bash
# Runs on the switch as root via sudo.
set -u
WORK=/var/captures/work_$$
mkdir -p $WORK

# 1. gcore — proper variable resolution (this script runs as root, $$ etc work)
SWPID=$(pidof switchd | awk '{print $1}')
echo "SWPID=$SWPID"
rm -f $WORK/sw.core* 2>/dev/null
gdb -p $SWPID -batch \
    -ex 'set pagination off' \
    -ex "gcore $WORK/sw.core" \
    -ex 'detach' -ex 'quit' > $WORK/gdb.log 2>&1
echo "gdb exit=$?"
ls -lh $WORK/

# 2. SFP eeproms
{
    for d in /sys/class/eeprom_dev/eeprom*; do
        [ -L "$d" ] || continue
        n=$(basename "$d")
        e="$d/device/eeprom"
        if [ -f "$e" ]; then
            echo "===== $n ====="
            echo "  symlink -> $(readlink "$d")"
            echo "  size: $(stat -c %s "$e" 2>/dev/null)"
            od -An -tx1 -v -N 256 "$e" 2>/dev/null
        fi
    done
} > $WORK/sfp.txt

# 3. CPLD via i2c
{
    for d in /sys/bus/i2c/devices/*; do
        [ -d "$d" ] || continue
        name=$(cat "$d/name" 2>/dev/null || echo "?")
        case "$name" in
            *cpld*|*CPLD*|*as5610*|*pca953*|*gpio*|*adm1021*|*max669*|*tmp*|*lm75*|*lm90*)
                echo "===== $(basename $d) [$name] ====="
                ls "$d/" 2>/dev/null
                for f in "$d"/*; do
                    [ -f "$f" ] || continue
                    fname=$(basename "$f")
                    sz=$(stat -c %s "$f" 2>/dev/null || echo 0)
                    [ "$sz" -gt 4096 ] && continue
                    val=$(head -c 1024 "$f" 2>/dev/null)
                    echo "  $fname = $val"
                done
                ;;
        esac
    done
    echo
    echo "=== full i2c topology ==="
    ls -la /sys/bus/i2c/devices/
} > $WORK/cpld.txt

# 4. Thermal / hwmon
{
    for d in /sys/class/hwmon/* /sys/class/thermal/*; do
        [ -e "$d" ] || continue
        realpath=$(readlink -f "$d")
        name=$(cat "$d/name" 2>/dev/null || cat "$d/type" 2>/dev/null || echo "?")
        echo "===== $d [$name] ====="
        echo "  -> $realpath"
        ls "$d/" 2>/dev/null
        for f in "$d"/*; do
            [ -f "$f" ] || continue
            fname=$(basename "$f")
            sz=$(stat -c %s "$f" 2>/dev/null || echo 0)
            [ "$sz" -gt 4096 ] && continue
            val=$(head -c 1024 "$f" 2>/dev/null)
            echo "  $fname = $val"
        done
    done
    echo
    echo "=== fan-related processes ==="
    ps auxw | grep -iE "thermal|fan|temp|cpld|pwm" | grep -v grep
    echo
    echo "=== sensors ==="
    which sensors >/dev/null 2>&1 && sensors 2>&1
    echo
    echo "=== ondemand fan logic? ==="
    ls /etc/init.d/ | grep -iE "fan|thermal|sensor"
    [ -f /etc/fancontrol ] && head -30 /etc/fancontrol
    cat /etc/cumulus/datapath/qos_features.conf 2>/dev/null | head -20
} > $WORK/thermal.txt

# 5. switchd ldd + lib paths
{
    ldd /usr/sbin/switchd
    echo
    echo === switchd maps ===
    cat /proc/$SWPID/maps
} > $WORK/switchd_ldd.txt

# 6. List the dso files we should grab for offline gcore analysis
ldd /usr/sbin/switchd 2>/dev/null | awk '{print $3}' | grep -E '^/' > $WORK/switchd_libs_paths.txt

echo "DONE - work=$WORK"
ls -lh $WORK
REMOTE

# scp remote script + run it
sshpass -p CumulusLinux! scp $SSH_OPTS /tmp/_remote_capture.sh cumulus@$SWITCH:/tmp/ 2>&1 | grep -v Warning
echo "[*] executing on switch (this includes a gcore that may take ~60s)..." | tee -a log.txt
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S bash /tmp/_remote_capture.sh" 2>&1 | tee remote_run.log | tail -20

# Find work dir from the log
WORK=$(grep "DONE - work=" remote_run.log | sed 's/.*work=//')
echo "[*] WORK on switch: $WORK" | tee -a log.txt
[ -z "$WORK" ] && { echo "FAILED - no work dir"; exit 1; }

# scp everything back
echo "[*] scp all work files back..." | tee -a log.txt
sshpass -p CumulusLinux! scp $SSH_OPTS cumulus@$SWITCH:"$WORK/*" gcore/ 2>&1 | grep -v Warning
ls -lh gcore/

# move per-purpose
[ -f gcore/sfp.txt ] && mv gcore/sfp.txt sfp/
[ -f gcore/cpld.txt ] && mv gcore/cpld.txt cpld/
[ -f gcore/thermal.txt ] && mv gcore/thermal.txt thermal/
[ -f gcore/switchd_ldd.txt ] && mv gcore/switchd_ldd.txt switchd/
[ -f gcore/switchd_libs_paths.txt ] && mv gcore/switchd_libs_paths.txt switchd/

# Pull each shared lib for offline gdb-on-core symbol resolution
if [ -f switchd/switchd_libs_paths.txt ]; then
    mkdir -p switchd/libs
    while read libpath; do
        [ -z "$libpath" ] && continue
        libname=$(basename "$libpath")
        sshpass -p CumulusLinux! scp $SSH_OPTS cumulus@$SWITCH:"$libpath" switchd/libs/$libname 2>&1 | grep -v Warning
    done < switchd/switchd_libs_paths.txt
    ls -lh switchd/libs/
fi

# Clean work dir on switch
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S rm -rf $WORK" 2>&1 | grep -v Warning

echo "============ v3 DONE ============" | tee -a log.txt
echo
echo "=== local content ==="
du -sh sfp/ cpld/ thermal/ gcore/ switchd/ 2>/dev/null
ls -lh gcore/

tar czf "${OUT}.tgz" -C "$(dirname $OUT)" "$(basename $OUT)" 2>/dev/null
ls -lh "${OUT}.tgz"

#!/bin/bash
# Now that gdb is installed: gcore switchd + retry SFP/CPLD/thermal w/ proper quoting.
set -u

SWITCH=10.1.1.212
OUT=/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/gcore_and_misc_$(date +%Y%m%d_%H%M%S)
mkdir -p "$OUT"/{gcore,sfp,cpld,thermal,switchd}
cd "$OUT" || exit 1

SSH_OPTS="-o ConnectTimeout=30 -o HostKeyAlgorithms=+ssh-rsa,ssh-dss -o PubkeyAcceptedAlgorithms=+ssh-rsa -o KexAlgorithms=+diffie-hellman-group1-sha1,diffie-hellman-group14-sha1 -o Ciphers=+aes128-cbc,3des-cbc -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"
SSHRAW() { sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH "echo CumulusLinux! | sudo -S $1" 2>/dev/null; }

echo "OUT=$OUT" | tee log.txt

# --- 1. gcore via gdb -> /var/captures/sw.core ---
echo "[1] gcore switchd via gdb..." | tee -a log.txt
SSHRAW 'SWPID=$(pidof switchd | awk "{print \$1}"); mkdir -p /var/captures && rm -f /var/captures/sw.core* && \
        gdb -p $SWPID -batch -ex "set pagination off" -ex "gcore /var/captures/sw.core" -ex "detach" -ex "quit" 2>&1' > gcore/gdb.log
tail -8 gcore/gdb.log

echo "[1] ls var/captures..." | tee -a log.txt
SSHRAW 'ls -lh /var/captures/' | tee gcore/var_ls.txt

# scp it back (could be 100s of MB)
echo "[1] scp gcore back..." | tee -a log.txt
sshpass -p CumulusLinux! scp $SSH_OPTS cumulus@$SWITCH:'/var/captures/sw.core*' gcore/ 2>&1 | grep -v Warning
ls -lh gcore/

# Clean up on switch
SSHRAW 'rm -f /var/captures/sw.core*'

# --- 2. SFP eeproms (script-via-stdin avoids heredoc quote hell) ---
echo "[2] SFP eeproms..." | tee -a log.txt
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S bash -s' <<'SCRIPT'
for d in /sys/class/eeprom_dev/eeprom*; do
    [ -L "$d" ] || continue
    n=$(basename "$d")
    e="$d/device/eeprom"
    if [ -f "$e" ]; then
        echo "=== $n ==="
        echo "  symlink -> $(readlink "$d")"
        echo "  size: $(stat -c %s "$e")"
        od -An -tx1 -v -N 256 "$e" 2>/dev/null
    fi
done
SCRIPT
echo "(captured above, saving to file)"
# Re-run to capture cleanly
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S bash -s' > sfp/all.txt <<'SCRIPT'
for d in /sys/class/eeprom_dev/eeprom*; do
    [ -L "$d" ] || continue
    n=$(basename "$d")
    e="$d/device/eeprom"
    if [ -f "$e" ]; then
        echo "=== $n ==="
        echo "  symlink -> $(readlink "$d")"
        echo "  size: $(stat -c %s "$e")"
        od -An -tx1 -v -N 256 "$e" 2>/dev/null
    fi
done
SCRIPT
wc -l sfp/all.txt
echo "  sfp entries captured: $(grep -c '^===' sfp/all.txt)"

# --- 3. CPLD via i2c sysfs ---
echo "[3] CPLD i2c sysfs..." | tee -a log.txt
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S bash -s' > cpld/all.txt <<'SCRIPT'
# enumerate every i2c device
for d in /sys/bus/i2c/devices/*; do
    [ -d "$d" ] || continue
    name=$(cat "$d/name" 2>/dev/null || echo "?")
    # only print CPLD / accton / mux / GPIO / temp / fan devices (skip eeproms - covered in sfp/)
    case "$name" in
        *cpld*|*CPLD*|*as5610*|*pca953*|*gpio*|*adm1021*|*max669*|*tmp*|*lm75*|*lm90*)
            echo "===== $(basename $d) [$name] ====="
            ls "$d/"
            for f in "$d"/*; do
                [ -f "$f" ] || continue
                fname=$(basename "$f")
                # skip giant ones
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
ls -la /sys/bus/i2c/devices/ | head -100
SCRIPT
wc -l cpld/all.txt
echo "  CPLD devices: $(grep -c '^=====' cpld/all.txt)"

# --- 4. Thermal / hwmon ---
echo "[4] thermal/hwmon..." | tee -a log.txt
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S bash -s' > thermal/all.txt <<'SCRIPT'
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
echo "=== running thermal-related processes ==="
ps auxw | grep -iE "thermal|fan|temp|cpld|pwm" | grep -v grep
echo
echo "=== fan-control config (if any) ==="
ls -la /etc/fancontrol 2>/dev/null
[ -f /etc/fancontrol ] && head -30 /etc/fancontrol
echo
echo "=== syslog grep for fan/thermal ==="
grep -iE "fan|temp|thermal" /var/log/syslog 2>/dev/null | tail -30
echo
echo "=== sensors output (if installed) ==="
which sensors && sensors 2>&1 | head -40
SCRIPT
wc -l thermal/all.txt
echo "  hwmon/thermal entries: $(grep -c '^=====' thermal/all.txt)"

# --- 5. switchd shared libs (for offline gcore decoding) ---
echo "[5] switchd shared libraries..." | tee -a log.txt
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S bash -s' > switchd/ldd.txt <<'SCRIPT'
ldd /usr/sbin/switchd
echo
echo === maps for current switchd ===
cat /proc/$(pidof switchd | awk "{print \$1}")/maps | head -50
SCRIPT
cat switchd/ldd.txt | head -10
# Pull the libs gcore would need
sshpass -p CumulusLinux! ssh $SSH_OPTS cumulus@$SWITCH 'echo CumulusLinux! | sudo -S sh -c "ldd /usr/sbin/switchd 2>/dev/null | awk \"{print \\\$3}\" | grep -E /lib/ | head -20"' > switchd/_libs.txt
mkdir -p switchd/libs
while read libpath; do
    [ -z "$libpath" ] && continue
    libname=$(basename "$libpath")
    SSHRAW "cat $libpath" > switchd/libs/$libname 2>/dev/null
    sz=$(stat -c %s switchd/libs/$libname 2>/dev/null || echo 0)
    [ "$sz" -lt 100 ] && rm -f switchd/libs/$libname
done < switchd/_libs.txt
ls -lh switchd/libs/ | head -20

echo "============ DONE ============" | tee -a log.txt
du -sh "$OUT"
tar czf "${OUT}.tgz" -C "$(dirname $OUT)" "$(basename $OUT)" 2>/dev/null
ls -lh "${OUT}.tgz"

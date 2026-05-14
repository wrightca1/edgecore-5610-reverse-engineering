#!/bin/bash
# Extra captures beyond the bulk script: fan/thermal control + OSPF state.
set -x

OUT=/tmp/extra_$(date +%Y%m%d_%H%M%S)
mkdir -p $OUT
cd $OUT

# --- OSPF state ---
mkdir ospf
vtysh -c 'show ip ospf'              > ospf/state.txt 2>&1
vtysh -c 'show ip ospf interface'    > ospf/interface.txt
vtysh -c 'show ip ospf neighbor'     > ospf/neighbor.txt
vtysh -c 'show ip ospf database'     > ospf/database.txt
vtysh -c 'show ip ospf route'        > ospf/route.txt
vtysh -c 'show ip route'             > ospf/iproute.txt
ip route show table all              > ospf/kernel_route.txt
cat /etc/quagga/Quagga.conf          > ospf/Quagga.conf

# --- Fan / thermal sensors ---
mkdir thermal
# Linux hwmon (lm-sensors)
for d in /sys/class/hwmon/*; do
    [ -d "$d" ] || continue
    name=$(cat $d/name 2>/dev/null)
    echo "==== $d ($name) ===="
    ls $d/
    for f in $d/temp*_input $d/fan*_input $d/pwm* $d/temp*_label $d/temp*_max $d/temp*_crit; do
        [ -f "$f" ] || continue
        echo "$(basename $f) = $(cat $f 2>/dev/null)"
    done
    echo
done > thermal/hwmon.txt

# Thermal subsystem
for d in /sys/class/thermal/*; do
    [ -d "$d" ] || continue
    echo "==== $d ===="
    for f in $d/*; do
        [ -f "$f" ] || continue
        echo "$(basename $f) = $(cat $f 2>/dev/null | head -1)"
    done
    echo
done > thermal/sysclass.txt 2>&1

# Cumulus platform daemons
ps auxw                              > thermal/processes.txt
ls /etc/init.d/                      > thermal/initd.txt
cat /var/log/syslog 2>/dev/null | grep -iE "fan|temp|thermal|pwm|cpld" | tail -100 > thermal/syslog_grep.txt
dmesg | grep -iE "fan|temp|thermal|pwm|cpld" > thermal/dmesg_grep.txt
service --status-all 2>&1 | head -40 > thermal/services.txt

# CPLD registers (this platform exposes fan PWM via CPLD)
mkdir thermal/cpld
ls /sys/bus/i2c/devices/*-0058 2>/dev/null | head
for d in /sys/bus/i2c/devices/*; do
    [ -d "$d" ] || continue
    name=$(cat $d/name 2>/dev/null)
    case "$name" in
        *cpld*|*as5610*)
            echo "==== $d ($name) ===="
            ls $d/
            for f in $d/fan* $d/temp* $d/psu* $d/version $d/cpld_version; do
                [ -e "$f" ] || continue
                echo "$(basename $f) = $(cat $f 2>/dev/null)"
            done
            ;;
    esac
done > thermal/cpld/i2c_cpld.txt

# /etc/cumulus/datapath for thermal references
grep -iE "fan|temp|thermal|pwm" /etc/cumulus/datapath/*.conf 2>/dev/null > thermal/cumulus_datapath_grep.txt

# accton_as5610_52x_cpld module's sysfs - this is the kernel driver that exposes fan/PSU/temp via CPLD i2c
ls -la /sys/module/accton_as5610_52x_cpld/ 2>/dev/null > thermal/accton_module.txt
ls /sys/bus/i2c/drivers/accton_as5610_52x_cpld/ 2>/dev/null  >> thermal/accton_module.txt 2>&1

# All onlpdump / decode-syseeprom data if present
which onlpdump decode-syseeprom 2>&1                                        > thermal/tools.txt
onlpdump -t 2>/dev/null                                                     > thermal/onlp_thermal.txt 2>&1
onlpdump -f 2>/dev/null                                                     > thermal/onlp_fan.txt 2>&1
decode-syseeprom 2>/dev/null                                                > thermal/syseeprom.txt 2>&1

# Find the actual fan control daemon and its config
find /etc/ /usr/share/ -name '*.conf' 2>/dev/null | xargs grep -lE 'fan|thermal|pwm' 2>/dev/null | head -20 > thermal/fan_conf_files.txt
ls -la /etc/cumulus/ /usr/lib/cumulus/ 2>&1                                 > thermal/cumulus_dirs.txt

# Cumulus 2.5 fan ctrl: check /var/log for fancontrol
tail -200 /var/log/daemon.log 2>/dev/null | grep -iE "fan|thermal|cpld" > thermal/daemon_log_grep.txt
tail -200 /var/log/syslog 2>/dev/null | grep -iE "fan|thermal|cpld" >> thermal/syslog_grep.txt

# tar
cd /tmp
tar czf $(basename $OUT).tgz $(basename $OUT)
ls -lh $(basename $OUT).tgz

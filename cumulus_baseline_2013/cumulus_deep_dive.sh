#!/bin/bash
# DEEP DIVE - capture everything we haven't already
BC="/usr/lib/cumulus/bcmcmd"
section() { echo ""; echo "############################################################"; echo "## $1"; echo "############################################################"; }
sub() { echo ""; echo "==== $1 ===="; }

section "1. CPLD - direct register dump via /sys"
sub "find CPLD device(s)"
find /sys -name "*cpld*" -type d 2>/dev/null | head -20
sub "CPLD sysfs attributes if any"
for d in /sys/bus/i2c/drivers/accton_as5610*/* /sys/devices/*/cpld*; do
  [ -d "$d" ] || continue
  echo "--- $d ---"
  ls "$d" 2>&1 | head -30
done
sub "CPLD module info"
modinfo accton_as5610_52x_cpld 2>&1 | head -20

section "2. BCM internal registers - systematic dump"
sub "CMIC registers"
for reg in CMIC_CONFIG CMIC_MISC_CONFIG CMIC_REVISION CMIC_BS_OFFSET \
           CMIC_INTERRUPT_LO CMIC_INTERRUPT_HI CMIC_INTERRUPT_ENABLE_LO \
           CMIC_INTERRUPT_ENABLE_HI CMIC_CMC_INTR_STAT CMIC_CMC_INTR_ENABLE \
           CMIC_LINK_STATUS CMIC_LINK_STATUS_CHG CMIC_RATE_ADJUST \
           CMIC_TXBUF_THRESHOLD CMIC_RXBUF_THRESHOLD CMIC_SBUS_TIMEOUT \
           CMIC_SCHAN_CTRL CMIC_SOFT_RESET; do
  printf "%-35s = " "$reg"
  $BC "getreg $reg" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tail -1 || echo "?"
done
sub "port 0 (CMIC) tables"
$BC "ge 0" 2>&1 | head -20

section "3. PCI - full enumeration"
sub "lspci tree"
lspci -t 2>&1
sub "lspci -nn"
lspci -nn 2>&1
sub "PCI BAR sizes"
lspci -vv 2>&1 | grep -E "^[0-9]|Region|Memory at" | head -60

section "4. iProc (BCM internal ARM) - if accessible"
sub "iProc check via mdio / cmicm"
$BC "ver" 2>&1
$BC "rev" 2>&1
$BC "show socinfo" 2>&1 | head -10
$BC "iproc info" 2>&1 | head -10

section "5. Switchd state - deep introspection"
sub "switchd process status"
ps -p $(pgrep -x switchd) -o pid,ppid,cmd,etime,pcpu,pmem,vsz,rss 2>&1
sub "switchd open files (cat list)"
ls /proc/$(pgrep -x switchd)/fd 2>/dev/null | wc -l
ls -la /proc/$(pgrep -x switchd)/fd 2>/dev/null | awk '{print $NF}' | sort -u | head -40
sub "switchd memory maps"
cat /proc/$(pgrep -x switchd)/status 2>/dev/null | head -20
sub "switchd network namespaces"
ls /proc/$(pgrep -x switchd)/ns/ 2>/dev/null

section "6. Per-port deep state for linked ports"
for p in xe0 xe1 xe48 xe49; do
  sub "$p detailed"
  $BC "phy info $p" 2>&1 | grep "$p" | head -1
  $BC "g $p" 2>&1 | head -20
done

section "7. BCM tables - forwarding state"
sub "MAC table"
$BC "l2 show" 2>&1 | head -30
sub "VLAN table"
$BC "vlan show" 2>&1 | head -30
sub "STP state"
$BC "stg show" 2>&1
sub "Multicast"
$BC "multicast show" 2>&1 | head -30
sub "IP route table"
$BC "l3 ip6route show" 2>&1 | head -10
$BC "l3 defip show" 2>&1 | head -20
sub "L3 host table"
$BC "l3 ip6host show" 2>&1 | head -10
$BC "l3 l3table show" 2>&1 | head -20

section "8. TCAM / Field processor"
sub "FP (Field Processor) groups"
$BC "fp show group" 2>&1 | head -30
$BC "fp show stats" 2>&1 | head -20
sub "FP entries (slices)"
$BC "fp show slice 0" 2>&1 | head -30
$BC "fp show slice 1" 2>&1 | head -30

section "9. EEPROMs - read everything"
sub "system EEPROM (decode-syseeprom)"
decode-syseeprom 2>&1
sub "system EEPROM raw"
for d in /sys/bus/i2c/devices/*-0056/eeprom /sys/bus/i2c/devices/*-0057/eeprom \
         /sys/devices/*/eeprom*; do
  [ -f "$d" ] || continue
  echo "--- $d ($(stat -c %s $d 2>/dev/null) bytes) ---"
  od -An -tx1 -N 256 -v "$d" 2>/dev/null | head -16
done

sub "SFP+ EEPROMs (A0 page = ID, A2 page = DOM) for all 48 SFP+ slots"
for d in /sys/bus/i2c/devices/*-0050; do
  [ -d "$d" ] || continue
  bus=$(basename $d | cut -d- -f1)
  name=$(cat $d/name 2>/dev/null)
  size=$(stat -c %s $d/eeprom 2>/dev/null)
  [ -z "$size" ] && continue
  # only show populated ones (vendor bytes non-zero)
  vendor=$(od -An -c -j 20 -N 16 $d/eeprom 2>/dev/null | tr -d ' ')
  echo "i2c-$bus ($name): size=$size vendor=\"$vendor\""
done

section "10. U-Boot environment"
which fw_printenv 2>&1
sub "fw_env.config"
cat /etc/fw_env.config 2>/dev/null
sub "all U-Boot env vars"
fw_printenv 2>&1 | head -60

section "11. /proc/device-tree (PowerPC FDT)"
sub "model + compatible"
strings /proc/device-tree/model 2>/dev/null
strings /proc/device-tree/compatible 2>/dev/null
sub "top-level nodes"
ls /proc/device-tree/ 2>/dev/null | head -40
sub "soc node summary"
ls /proc/device-tree/soc*/ 2>/dev/null | head -60

section "12. Kernel state"
sub "command line"
cat /proc/cmdline 2>/dev/null
sub "modules with parameters"
for m in $(lsmod 2>/dev/null | tail -n +2 | awk '{print $1}'); do
  pdir="/sys/module/$m/parameters"
  [ -d "$pdir" ] || continue
  out=""
  for p in $pdir/*; do
    [ -f "$p" ] && out="$out $(basename $p)=$(cat $p 2>/dev/null | head -c 30 | tr '\n' ',')"
  done
  [ -n "$out" ] && echo "$m: $out"
done | head -30

section "13. dmesg full boot"
dmesg 2>&1 | head -200

section "14. /var/log syslog highlights"
[ -f /var/log/syslog ] && grep -iE "switchd|i2c|gpio|cpld|retimer|sfp|qsfp|phy|warp|port[ _]up|link.*up" /var/log/syslog 2>&1 | tail -100

section "15. Routing / quagga / zebra"
sub "kernel routing"
ip route 2>&1
sub "any zebra/quagga config"
ls /etc/quagga/ 2>/dev/null
cat /etc/quagga/zebra.conf 2>/dev/null | head -20
cat /etc/quagga/ospfd.conf 2>/dev/null | head -20

section "16. Network interfaces"
sub "all interfaces summary"
ip -br link show 2>&1 | head -60

section "17. switchd config and state files"
sub "switchd.conf"
cat /etc/cumulus/switchd.conf 2>/dev/null
sub "any cumulus state files"
ls /var/lib/cumulus/ 2>/dev/null
ls /run/cumulus/ 2>/dev/null
find /var/lib/cumulus /var/cache/cumulus -type f 2>/dev/null | head -20

section "18. Filesystem - boot/ partitions"
df -h 2>&1
echo "---"
cat /proc/partitions 2>&1
echo "---"
ls /boot 2>&1 | head -10

section "19. CPU + clocks"
cat /proc/cpuinfo 2>/dev/null | head -20
echo "---"
ls /sys/devices/system/clocksource/clocksource0/ 2>/dev/null
cat /sys/devices/system/clocksource/clocksource0/current_clocksource 2>/dev/null

section "20. all kernel module files in cumulus dir"
find /lib/modules/$(uname -r)/extra /lib/modules/$(uname -r)/updates /lib/modules/$(uname -r)/kernel/drivers/cumulus 2>/dev/null | head -30

section "21. ALL services - what's running"
service --status-all 2>&1 | head -30
sub "systemd/sysvinit"
ls /etc/init.d/ 2>/dev/null | head -40

section "22. Persisting filesystem layout"
mount 2>&1 | head -20
cat /etc/fstab 2>/dev/null

section "23. PHY firmware version (Warpcore)"
$BC "phy info" 2>&1 | head -3
$BC "phy diag xe0 firmware" 2>&1 | head -5
$BC "phy diag xe1 firmware" 2>&1 | head -5

section "24. Resource/buffer config"
$BC "show buffer" 2>&1 | head -30
$BC "show counter" 2>&1 | head -10
$BC "show l3 intf" 2>&1 | head -10

section "25. Anything unusual we may have missed"
sub "all files in /etc/cumulus"
find /etc/cumulus -type f 2>/dev/null | head -30
sub "files under /var/lib/openbsd-inetd /etc/network"
ls /etc/network/ 2>/dev/null
ls /var/lib/openbsd-inetd 2>/dev/null

echo ""
echo "########### DEEP DIVE COMPLETE ###########"

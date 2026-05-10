#!/bin/bash
# COMPREHENSIVE read-only register/state dump from live Cumulus baseline.
# Captures everything we can think of - even unknowns.

BC="/usr/lib/cumulus/bcmcmd"

section() { echo ""; echo "============================================================"; echo "=== $1"; echo "============================================================"; }
sub() { echo ""; echo "--- $1 ---"; }

section "DATE/UPTIME/UNAME"
date; uptime; uname -a

section "PORT CARRIER STATE (Linux side)"
for p in /sys/class/net/swp*; do
  n=$(basename $p)
  echo "$n carrier=$(cat $p/carrier 2>/dev/null) operstate=$(cat $p/operstate 2>/dev/null) speed=$(cat $p/speed 2>/dev/null) duplex=$(cat $p/duplex 2>/dev/null)"
done

section "ETHTOOL swp1 / swp2"
for p in swp1 swp2; do
  sub "$p"
  ethtool $p 2>&1
  ethtool -S $p 2>&1 | head -50
done

section "BCM DIAG: ps (port summary)"
$BC "ps" 2>&1

section "BCM DIAG: phy info"
$BC "phy info" 2>&1

section "BCM DIAG: phy control xe0"
$BC "phy control xe0" 2>&1
section "BCM DIAG: phy control xe1"
$BC "phy control xe1" 2>&1

section "BCM DIAG: xe0 link rate"
$BC "ge xe0" 2>&1
section "BCM DIAG: xe1 link rate"
$BC "ge xe1" 2>&1

section "PHY CL22 dump xe0 (0x00-0x1f)"
for r in 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f; do
  printf "xe0 reg %s : " "$r"
  $BC "phy xe0 $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
done

section "PHY CL22 dump xe1 (0x00-0x1f)"
for r in 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f; do
  printf "xe1 reg %s : " "$r"
  $BC "phy xe1 $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
done

section "PHY CL45 dump xe0 (devad=1 PMD/PMA + devad=4 XGXS)"
for d in 1 2 3 4 5 7; do
  for r in 0x0000 0x0001 0x0008 0x0009 0x0020 0x0021 0x8000 0x8001 0x8002 0x8003 0x8400 0xb820 0xc801 0xc802 0xc803 0xc810 0xc811; do
    printf "xe0 dev=%d reg=%s : " "$d" "$r"
    $BC "phy xe0 $d $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
  done
done

section "WARPCORE REGISTERS via raw access (xe0 = phy 0xd1 lane 0)"
sub "Read AER and important blocks"
for blkreg in "0x1f" "0xffde" "0xffdf"; do
  printf "raw 0xd1 reg %s : " "$blkreg"
  $BC "phy raw 0xd1 $blkreg" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
done

section "BCM DIAG: dmac (show MAC tables)"
$BC "l2 show" 2>&1 | head -40

section "BCM DIAG: vlan show"
$BC "vlan show" 2>&1 | head -40

section "BCM DIAG: pmap (port mapping)"
$BC "pmap" 2>&1 | head -100

section "BCM DIAG: stg (spanning tree)"
$BC "stg show" 2>&1 | head -20

section "BCM DIAG: counter (xe0,xe1)"
$BC "show counter xe0" 2>&1 | head -30
$BC "show counter xe1" 2>&1 | head -30

section "CMIC REGISTERS (BAR0 reads)"
for reg in "CMIC_CONFIG" "CMIC_REVISION" "CMIC_LINK_STAT" "CMIC_LINK_STATUS_CHG"; do
  printf "%s : " "$reg"
  $BC "getreg $reg" 2>&1 | grep -E "0x|=" | head -1
done

section "BCM DIAG: misc port_status"
$BC "port_status xe0" 2>&1 | head -30
$BC "port_status xe1" 2>&1 | head -30

section "Configs"
sub "ports.conf"; cat /etc/cumulus/ports.conf 2>/dev/null
sub "switchd.conf (non-comment)"; grep -vE "^#" /etc/cumulus/switchd.conf 2>/dev/null | grep -v "^$"
sub "platform"; cat /etc/cumulus/.platform 2>/dev/null; cat /etc/platform 2>/dev/null
sub "/etc/network/interfaces"; cat /etc/network/interfaces 2>/dev/null

section "Switch process (cmdline)"
ps auxww 2>/dev/null | grep -E "switchd|portd|hsfl|sfputil" | head -10
echo "---"
cat /proc/$(pgrep -x switchd 2>/dev/null | head -1)/cmdline 2>/dev/null | tr '\0' ' '; echo ""

section "lsmod (kernel modules)"
lsmod 2>/dev/null | head -30

section "/proc/iomem and /proc/interrupts"
cat /proc/iomem 2>/dev/null
echo "---"
cat /proc/interrupts 2>/dev/null | head -30

section "lspci -vvxxx (PCI config + first 256B header)"
lspci -nn 2>/dev/null
echo "---"
lspci -vvxxx 2>/dev/null | head -200

section "I2C: detect each bus"
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12; do
  if [ -e /dev/i2c-$i ]; then
    sub "i2c-$i"
    i2cdetect -y $i 2>&1 || echo "FAILED i2c-$i"
  fi
done

section "I2C: SFP+ DOM (port 1 = swp1, addr 0x50/0x51)"
# Try most common buses for SFP detection
for bus in 0 1 2 3 4 5 6 7 8 9; do
  for addr in 0x50 0x51; do
    out=$(i2cget -y $bus $addr 0x00 b 2>&1)
    if echo "$out" | grep -qE "0x[0-9a-f]{2}"; then
      echo "i2c-$bus addr=$addr id_byte=$out"
    fi
  done
done

section "Retimer DS100DF410 (per memory: I2C bus topology, channel pages 0x04-0x07)"
# Try common retimer addresses
for bus in 0 1 2 3 4 5 6 7 8 9; do
  for addr in 0x18 0x19 0x1a 0x1b 0x30 0x32 0x60; do
    out=$(i2cget -y $bus $addr 0xfd b 2>&1)
    if echo "$out" | grep -qE "0x[0-9a-f]{2}"; then
      # Read several registers
      page_cur=$(i2cget -y $bus $addr 0xfc b 2>&1)
      printf "i2c-%s addr=%s reg_0xfd=%s page_reg_0xfc=%s\n" "$bus" "$addr" "$out" "$page_cur"
    fi
  done
done

section "CPLD via /sys or i2c (per memory: CPLD wraps at 32 bytes)"
ls /sys/class/cpld* 2>/dev/null
ls /sys/bus/i2c/devices/ 2>/dev/null | head -20

section "dmesg (boot)"
dmesg 2>&1 | head -100

section "switchd log tail"
ls -la /var/log/switchd* 2>/dev/null
[ -f /var/log/switchd.log ] && awk 'END{print NR}' /var/log/switchd.log

section "Running services"
service --status-all 2>&1 | head -30

echo ""
echo "============================================================"
echo "=== DUMP COMPLETE"
echo "============================================================"

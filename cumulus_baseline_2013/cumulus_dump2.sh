#!/bin/bash
# Phase-2 deep capture - bring up unconnected port, capture extra state.
BC="/usr/lib/cumulus/bcmcmd"
section() { echo ""; echo "============================================================"; echo "=== $1"; echo "============================================================"; }

section "BEFORE: enabling swp10 (unconnected) for admin-up-no-link state"
ip -br link show swp10 2>&1
$BC "ps xe9" 2>&1

ip link set swp10 up 2>/dev/null
sleep 5

section "QSFP+ ports 49-52 - check link state (cables plugged in!)"
echo "User reports cables in QSFP ports 49-52"
for p in swp49 swp50 swp51 swp52; do
  echo "--- $p ---"
  ip -br link show $p 2>&1
  carrier=$(cat /sys/class/net/$p/carrier 2>/dev/null)
  ops=$(cat /sys/class/net/$p/operstate 2>/dev/null)
  echo "carrier=$carrier operstate=$ops"
  ethtool $p 2>&1 | head -10
done

echo "Bring up swp49-52 to test"
for p in swp49 swp50 swp51 swp52; do
  ip link set $p up 2>/dev/null
done
sleep 8

section "QSFP after admin up"
for p in swp49 swp50 swp51 swp52; do
  echo "--- $p ---"
  ip -br link show $p 2>&1
  carrier=$(cat /sys/class/net/$p/carrier 2>/dev/null)
  echo "carrier=$carrier"
  ethtool $p 2>&1 | grep -E "Speed|Link"
done

# Map QSFP to xe ports - 49-52 are typically xe48-xe51 (KR4)
section "QSFP BCM ports xe48-xe51"
$BC "ps xe48,xe49,xe50,xe51" 2>&1
for p in xe48 xe49 xe50 xe51; do
  echo "--- $p ---"
  $BC "phy control $p" 2>&1 | head -10
  echo "  PHY info:"
  $BC "phy info $p" 2>&1 | grep -E "$p" | head -1
done

section "QSFP CL22 reg dump xe48 (swp49)"
for r in 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f; do
  printf "xe48 reg %s : " "$r"
  $BC "phy xe48 $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
done

section "AFTER swp10 admin up"
ip -br link show swp10 2>&1
echo "carrier=$(cat /sys/class/net/swp10/carrier 2>/dev/null)"
$BC "ps xe9" 2>&1
$BC "phy control xe9" 2>&1

section "PHY CL22 dump xe9 (admin up, no SFP)"
for r in 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f; do
  printf "xe9 reg %s : " "$r"
  $BC "phy xe9 $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
done

section "Warpcore raw register dump xe0 — go through all blocks"
# Block (block_id at reg 0x1f) iterating common Warpcore blocks
# The blocks we want: 0x800x for PMD, 0xfffe for AER, 0x900x for digital
PHY_ADDR=0xd1
echo "Reading WC registers for phy=$PHY_ADDR (xe0 lane 0)"
# Read AER first
echo -n "AER (reg 0x1e of phy 0xd1) : "
$BC "phy raw c22 $PHY_ADDR 0x1e" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tr '\n' ' '; echo ""
# Block select reg 0x1f
for blk in 0x0001 0x8003 0x8005 0x8007 0x8100 0x9000 0x9001 0x9002 0x9003 0xc801 0xffff; do
  $BC "phy raw c22 $PHY_ADDR 0x1f $blk" >/dev/null 2>&1
  printf "Block %s reads (regs 0x10-0x1f):" "$blk"
  for r in 0x10 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f; do
    val=$($BC "phy raw c22 $PHY_ADDR $r" 2>&1 | grep -oE "0x[0-9a-fA-F]+" | tail -1)
    printf " %s=%s" "$r" "$val"
  done
  echo ""
done

section "BCM regs - CMICm config"
$BC "getreg CMIC_CONFIG" 2>&1
$BC "getreg CMIC_MISC_CONFIG" 2>&1
$BC "getreg CMIC_REVISION" 2>&1
$BC "g CMIC_BS_OFFSET" 2>&1
$BC "g CMIC_INTERRUPT_LO" 2>&1

section "BCM regs - chip ID + version"
$BC "ver" 2>&1

section "BCM tables - L2"
$BC "l2 show" 2>&1 | head -30
$BC "vlan show" 2>&1 | head -30
$BC "stg show" 2>&1 | head -10

section "BCM TCAM and ACL"
$BC "fp show" 2>&1 | head -50
$BC "fp show stats" 2>&1 | head -10

section "BCM portmap"
$BC "pmap" 2>&1
$BC "show pmap" 2>&1

section "BCM debug + counters"
$BC "show counter c xe0,xe1,xe9" 2>&1 | head -100

section "Per-port DSC equalizer for xe0/xe1"
# These vary - try common ones
for cmd in "dsc xe0" "dsc xe1" "phy debug xe0" "phy debug xe1" "wbz xe0" "wbz xe1" \
           "txport xe0" "rxport xe0" "phy diag xe0 dsc" "phy diag xe1 dsc" \
           "phy diag xe0 short" "phy diag xe0 mediumshort" "phy diag xe0 long"; do
  echo "--- $cmd ---"
  $BC "$cmd" 2>&1 | head -60
done

section "/sys/class/net/swp1 contents"
ls -la /sys/class/net/swp1/ 2>&1
for f in /sys/class/net/swp1/*; do
  if [ -f "$f" ] && [ -r "$f" ]; then
    val=$(cat "$f" 2>/dev/null | head -c 200 | tr '\n' ' ')
    echo "$(basename $f) = $val"
  fi
done

section "/proc/cpuinfo /proc/meminfo /proc/cmdline"
cat /proc/cpuinfo 2>/dev/null
echo "---"
head -10 /proc/meminfo 2>/dev/null
echo "---"
cat /proc/cmdline 2>/dev/null

section "DMI / device-tree (PowerPC)"
ls /proc/device-tree/ 2>/dev/null | head -30
cat /proc/device-tree/model 2>/dev/null; echo
cat /proc/device-tree/compatible 2>/dev/null; echo

section "U-Boot env (read-only via /etc/fw_env.config)"
cat /etc/fw_env.config 2>/dev/null
fw_printenv 2>&1 | head -40

section "ifupdown / Cumulus init scripts inspection"
ls /etc/cumulus/init/ 2>/dev/null
ls /usr/share/cumulus/ 2>/dev/null | head -20

section "switchd binary version / build info"
strings /usr/sbin/switchd 2>/dev/null | grep -iE "version|build|cumulus" | head -10

section "kernel modules loaded at boot"
lsmod 2>/dev/null

section "lspci -nnvvxxx (full)"
lspci -nnvvxxx 2>/dev/null

section "Routing / NDP state"
ip route 2>/dev/null
echo ---
ip -6 route 2>/dev/null

section "dmesg full"
dmesg 2>&1

section "All running processes"
ps auxww 2>/dev/null | head -50

section "syslog tail"
[ -f /var/log/syslog ] && wc -l /var/log/syslog && \
  awk -v s=$(($(wc -l < /var/log/syslog) - 100)) 'NR>=s' /var/log/syslog | head -110

section "Try direct retimer I2C - DS100DF410 known address space"
# DS100DF410 base addresses are typically 0x18, 0x19, 0x1a, 0x1b on the SFP I2C bus
# But Cumulus's kernel driver might have it locked. Try reading raw via /sys
find /sys/bus/i2c/drivers -type d 2>/dev/null | head -20
echo ---
ls /sys/bus/i2c/devices 2>/dev/null
echo ---
for d in /sys/bus/i2c/devices/*; do
  [ -d "$d" ] || continue
  echo "$(basename $d): name=$(cat $d/name 2>/dev/null) status=$(cat $d/status 2>/dev/null)"
done | head -30

section "DUMP COMPLETE phase 2"
echo "Bringing swp10 back DOWN to leave system in baseline"
ip link set swp10 down 2>/dev/null
echo done.

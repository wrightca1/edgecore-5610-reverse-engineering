#!/bin/bash
# Read DS100DF410 retimer state via Cumulus kernel driver sysfs.
# Capture EVERYTHING per channel.

echo "===== ALL retimer device tree ====="
ls -la /sys/bus/i2c/drivers/ds100df410/ 2>&1

echo ""
echo "===== retimer instances ====="
ls -d /sys/bus/i2c/devices/*-0027/ 2>&1

echo ""
echo "===== per-retimer sysfs dump ====="
for d in /sys/bus/i2c/devices/*-0027/; do
  echo ""
  echo "============================================================"
  echo "===== $d"
  echo "============================================================"
  for f in $(ls $d 2>/dev/null); do
    fp="$d$f"
    if [ -f "$fp" ] && [ -r "$fp" ]; then
      val=$(cat $fp 2>/dev/null | head -c 1024 | tr '\n' '|')
      echo "$f = $val"
    fi
  done
  # 'channels' attribute likely lists per-channel state
  if [ -d "$d/channels" ]; then
    echo "-- $d/channels --"
    ls $d/channels
    for ch in $d/channels/*/; do
      echo ""
      echo "** channel $(basename $ch) **"
      for f in $(ls $ch 2>/dev/null); do
        fp="$ch$f"
        if [ -f "$fp" ] && [ -r "$fp" ]; then
          val=$(cat $fp 2>/dev/null | head -c 256 | tr '\n' '|')
          echo "  $f = $val"
        fi
      done
    done
  fi
done

echo ""
echo "===== map retimers to ports via switchd or board config ====="
ls /etc/cumulus/init/ 2>/dev/null
find /etc/cumulus -name "*.json" -o -name "*board*" -o -name "*retimer*" -o -name "*sfp*" 2>/dev/null
find /usr/share/cumulus -name "*as5610*" -o -name "*board*" 2>/dev/null | head -20
find /usr/share/platform-config -name "*as5610*" 2>/dev/null
ls /usr/share/platform-config/ 2>/dev/null

echo ""
echo "===== identify which retimer i2c channel maps to which front-panel port ====="
# Look at i2c-mux topology
for mux in /sys/bus/i2c/drivers/pca954x/*-*; do
  echo "-- $mux --"
  ls "$mux" 2>/dev/null | head -5
done

echo ""
echo "===== platform driver info ====="
ls /sys/bus/platform/drivers 2>/dev/null | head -30
echo ===
dmesg | grep -iE "ds100|retimer|sff|sfp" | head -30

echo ""
echo "===== running switchd flags ====="
[ -f /proc/$(pgrep -x switchd | head -1)/cmdline ] && cat /proc/$(pgrep -x switchd | head -1)/cmdline | tr '\0' ' '; echo

echo ""
echo "===== switchd open file descriptors (for /dev/i2c-* enumeration) ====="
ls -la /proc/$(pgrep -x switchd | head -1)/fd 2>/dev/null | grep -E "i2c|retimer" | head -20

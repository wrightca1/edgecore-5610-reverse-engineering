#!/bin/bash
# Trace the full platform monitoring path: fans, LEDs, PSUs, temp sensors, and
# the fan-control loop driven from temp sensors.

section() { echo ""; echo "============================================================"; echo "=== $1"; echo "============================================================"; }

section "hwmon devices summary"
for h in /sys/class/hwmon/hwmon*; do
  [ -d "$h" ] || continue
  name="$(cat $h/name 2>/dev/null)"
  echo "$h -> name=$name"
done

section "PER hwmon - all readable attrs"
for h in /sys/class/hwmon/hwmon*; do
  [ -d "$h" ] || continue
  echo ""
  echo "--- $h (name=$(cat $h/name 2>/dev/null)) ---"
  for f in $(ls $h 2>/dev/null); do
    fp="$h/$f"
    if [ -f "$fp" ] && [ -r "$fp" ]; then
      val="$(cat $fp 2>/dev/null | head -c 256 | tr '\n' ' ')"
      echo "$f = $val"
    fi
  done
done

section "all temperature sensors quick read"
for t in /sys/class/hwmon/hwmon*/temp*_input /sys/class/hwmon/hwmon*/in*_input; do
  [ -f "$t" ] && echo "$t = $(cat $t 2>/dev/null)"
done

section "fans"
for f in /sys/class/hwmon/hwmon*/fan*_input /sys/class/hwmon/hwmon*/pwm*; do
  [ -f "$f" ] && echo "$f = $(cat $f 2>/dev/null)"
done

section "fancontrol or fancontrold config"
ls -la /etc/fancontrol /etc/fancontrold* /etc/cumulus/fan* 2>&1
[ -f /etc/fancontrol ] && cat /etc/fancontrol
[ -d /etc/cumulus/fancontrol.d ] && ls -la /etc/cumulus/fancontrol.d/ && for f in /etc/cumulus/fancontrol.d/*; do echo "--- $f ---"; cat "$f" 2>/dev/null; done

section "fancontrol service / process"
service fancontrol status 2>&1 | head -10
ps auxww | grep -iE "fancontrol|fancontrold|thermal|temp" | grep -v grep

section "thermal_zone (kernel thermal framework)"
for tz in /sys/class/thermal/thermal_zone*; do
  [ -d "$tz" ] || continue
  echo "--- $tz ---"
  for f in type temperature trip_point_0_type trip_point_0_temp trip_point_1_type trip_point_1_temp policy mode; do
    [ -f "$tz/$f" ] && echo "$f = $(cat $tz/$f 2>/dev/null)"
  done
done

section "cooling devices"
for cd in /sys/class/thermal/cooling_device*; do
  [ -d "$cd" ] || continue
  echo "--- $cd ---"
  for f in type cur_state max_state; do
    [ -f "$cd/$f" ] && echo "$f = $(cat $cd/$f 2>/dev/null)"
  done
done

section "LEDs - kernel led class"
ls /sys/class/leds/ 2>/dev/null
for l in /sys/class/leds/*; do
  [ -d "$l" ] || continue
  echo "--- $l ---"
  for f in brightness max_brightness trigger; do
    [ -f "$l/$f" ] && echo "$f = $(cat $l/$f 2>/dev/null | head -c 200)"
  done
done

section "PSU info - via sysfs / decode-syseeprom / i2c"
# PSUs on AS5610 usually at I2C addresses 0x58 / 0x59 / 0x50 / 0x51 with PMBus or sff8472 EEPROM
for d in /sys/bus/i2c/devices/*-005[8-9]/ /sys/bus/i2c/devices/*-005[0-1]/; do
  [ -d "$d" ] || continue
  name=$(cat "$d/name" 2>/dev/null)
  echo "$d name=$name"
done
echo "--- PSU drivers ---"
for drv in /sys/bus/i2c/drivers/pmbus* /sys/bus/i2c/drivers/lm75* /sys/bus/i2c/drivers/ltc* /sys/bus/i2c/drivers/adm* /sys/bus/i2c/drivers/tps* /sys/bus/i2c/drivers/cumulus*; do
  [ -d "$drv" ] || continue
  echo "$drv"
  ls "$drv" 2>&1 | head -5
done

section "cl-psuutil if available"
which cl-psuutil cl-fanutil cl-temputil 2>&1
for tool in cl-psuutil cl-fanutil cl-temputil; do
  if which "$tool" >/dev/null 2>&1; then
    echo "--- $tool output ---"
    "$tool" 2>&1 | head -30
  fi
done

section "monit + cumulus platform daemons"
ls /etc/monit.d/ 2>&1 | head -10
for f in /etc/monit.d/*; do
  [ -f "$f" ] || continue
  echo "--- $f ---"
  cat "$f" 2>/dev/null | head -20
done

section "platform-detect / quagga / portd init scripts"
ls /etc/init.d/ 2>/dev/null | grep -iE "platform|temp|fan|cpld|switchd|portd|powersupply"
ls /etc/cumulus/init/ 2>/dev/null

section "lm-sensors output"
which sensors 2>&1
sensors 2>&1 | head -80

section "platform detect cumulus"
ls /etc/cumulus/.platform 2>/dev/null
cat /etc/cumulus/.platform 2>/dev/null
ls /usr/share/cumulus/platform/ 2>/dev/null | head -10
ls /usr/share/platform-config/accton/ 2>/dev/null
ls /usr/share/platform-config/accton/as5610_52x/ 2>/dev/null
echo === platform-config files ===
find /usr/share/platform-config/accton/as5610_52x/ -type f 2>/dev/null

section "look for fan-rules in platform-config"
find /etc /usr/share/cumulus /usr/share/platform-config -name "*fan*" -o -name "*thermal*" -o -name "*sensors*" -o -name "*psu*" 2>/dev/null | grep -vE "\.pyc$" | head -30

section "running daemons relating to platform monitoring"
ps auxww | grep -iE "monit|hsfl|sensord|psud|fand|tempd|cpldmond" | grep -v grep | head -10

section "CPLD interfaces - read-only sysfs"
ls /sys/devices/platform/ 2>/dev/null
ls -la /sys/bus/platform/devices/ 2>/dev/null | head -20

section "syslog grep for thermal/fan/psu events"
[ -f /var/log/syslog ] && grep -iE "fan|psu|thermal|temp|sensor|hwmon" /var/log/syslog | head -30

#!/bin/bash
# Self-contained recapture; logs progress to /tmp/recapture.log
# Detached via nohup so it survives SSH disconnect.

set +e
LOG=/var/log/lubde-init-2026-05-11.log
PROG=/tmp/recapture.log

exec > "$PROG" 2>&1
echo "=== recapture started at $(date) ==="

rm -f "$LOG" /tmp/shim_pid_*

echo "[1/6] Stop switchd"
service switchd stop
sleep 3
pkill -KILL -f /usr/sbin/switchd 2>/dev/null
rm -f /var/run/switchd.pid /var/run/switchd.ready

echo "[2/6] Start switchd under root-owned shim"
export LD_PRELOAD=/usr/local/lib/lubde_trace.so
export LUBDE_TRACE_LOG=$LOG
nohup /usr/sbin/switchd -d -lic /etc/cumulus/.license.txt > /tmp/sw.out 2>&1 &
SWPID=$!
unset LD_PRELOAD LUBDE_TRACE_LOG
echo "  switchd pid=$SWPID"

sleep 2
echo "  shim markers after 2s:"
ls /tmp/shim_pid_* 2>&1

echo "[3/6] Wait for ready (up to 180s)"
for i in $(seq 1 180); do
    if [ -f /var/run/switchd.ready ]; then
        echo "  READY after ${i}s"
        break
    fi
    if [ $((i % 10)) -eq 0 ]; then
        sz=$(stat -c%s "$LOG" 2>/dev/null || echo 0)
        echo "  ${i}s: log=$sz bytes"
    fi
    sleep 1
done

if [ ! -f /var/run/switchd.ready ]; then
    echo "  TIMED OUT after 180s; switchd may have failed"
fi

echo "[4/6] Pause 5s for tail-end activity, then stop"
sleep 5
echo "  final log size before stop: $(stat -c%s $LOG 2>/dev/null || echo 0) bytes"
pkill -TERM -f /usr/sbin/switchd 2>/dev/null
sleep 3
pkill -KILL -f /usr/sbin/switchd 2>/dev/null
rm -f /var/run/switchd.pid /var/run/switchd.ready

echo "[5/6] Restart normal switchd via init.d"
service switchd start
sleep 15
ps -ef | grep switchd | grep -v grep | head -2
ls -la /var/run/switchd.ready 2>&1

echo "[6/6] FINAL STATS"
echo "  log file:"
ls -la $LOG
echo "  line count:"
wc -l $LOG
echo "  first 5 lines:"
head -n 5 $LOG
echo "  last 5 lines:"
tail -n 5 $LOG
echo ""
echo "  switchd stdout/stderr (/tmp/sw.out):"
head -n 30 /tmp/sw.out 2>&1
echo ""
echo "=== recapture ended at $(date) ==="

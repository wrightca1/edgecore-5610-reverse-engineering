#!/bin/bash
# Option B: Stop switchd and ledmgrd, do exclusive WC register scan, restart.
# Safe because switch is not in production.
#
# This gives us exclusive MDIO bus access -- no contention.

set -e

echo "=== Option B: Exclusive Warpcore Scan ==="
echo "Stopping switchd and ledmgrd for exclusive MDIO access..."

# Save PIDs
SWITCHD_PID=$(pidof switchd 2>/dev/null || true)
LEDMGRD_PID=$(pidof ledmgrd 2>/dev/null || true)

# Stop them
if [ -n "$LEDMGRD_PID" ]; then
    echo "Stopping ledmgrd (PID $LEDMGRD_PID)..."
    kill -STOP $LEDMGRD_PID 2>/dev/null || true
fi
if [ -n "$SWITCHD_PID" ]; then
    echo "Stopping switchd (PID $SWITCHD_PID)..."
    kill -STOP $SWITCHD_PID 2>/dev/null || true
fi

echo "Services frozen. Running WC register scan..."
sleep 0.5

# Run the read-only scan (now safe since nothing else uses MDIO)
python /tmp/capture_wc_exclusive.py

echo "Scan complete. Resuming services..."

# Resume
if [ -n "$SWITCHD_PID" ]; then
    echo "Resuming switchd..."
    kill -CONT $SWITCHD_PID 2>/dev/null || true
fi
if [ -n "$LEDMGRD_PID" ]; then
    echo "Resuming ledmgrd..."
    kill -CONT $LEDMGRD_PID 2>/dev/null || true
fi

echo "=== Done ==="

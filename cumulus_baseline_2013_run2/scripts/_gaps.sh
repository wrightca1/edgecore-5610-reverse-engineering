#!/bin/bash
echo "=== 1. /var/lib/cumulus ==="
ls -la /var/lib/cumulus/ 2>&1 | head -20
echo
echo "=== rc.datapath_0 head ==="
head -30 /var/lib/cumulus/rc.datapath_0 2>/dev/null
echo "size: $(wc -l /var/lib/cumulus/rc.datapath_0 2>/dev/null)"
echo
echo "=== 2. update-ports ==="
file /usr/lib/cumulus/update-ports 2>&1
head -5 /usr/lib/cumulus/update-ports 2>&1
echo
echo "=== 3. /etc/init.d/switchd head ==="
head -50 /etc/init.d/switchd 2>/dev/null
echo
echo "=== 4. l3 multipath / ecmp ==="
/usr/lib/cumulus/bcmcmd 'l3 multipath show' 2>&1 | head -20
echo "---"
/usr/lib/cumulus/bcmcmd 'l3 ecmp show' 2>&1 | head -20
echo
echo "=== 5. dump L3_ECMP ==="
/usr/lib/cumulus/bcmcmd 'dump L3_ECMP' 2>&1 | head -30

#!/bin/bash
# Trace the CPU<->ASIC punt path in detail
BC="/usr/lib/cumulus/bcmcmd"
section() { echo ""; echo "############################################################"; echo "## $1"; echo "############################################################"; }

section "1. CPU MAC programmed into ASIC (My Station / My MAC)"
sub() { echo ""; echo "==== $1 ===="; }
sub "L2 table - find CPU MAC (eth0 MAC = 80:a2:35:81:ca:ae)"
$BC "l2 show" 2>&1 | grep -iE "80:a2:35|cpu|CPU" | head -10
sub "MY_STATION TCAM entries"
$BC "g MY_STATION_TCAM" 2>&1 | head -20
$BC "g MY_STATION" 2>&1 | head -10
$BC "dump my_station_tcam" 2>&1 | head -20

section "2. Trap table - which protocols/conditions punt to CPU"
sub "Egress trap config"
$BC "g RX_TRAP_TYPE" 2>&1 | head -20
sub "Reserved MAC trap (BPDU/LLDP/LACP)"
$BC "g RXLLDP_TRAP_CONTROL" 2>&1 | head -10
$BC "g LLDP_RX_PARSER_CTRL" 2>&1 | head -10
sub "Listing all trap reasons"
$BC "trap show" 2>&1 | head -40
$BC "rx trap" 2>&1 | head -10
$BC "show trap" 2>&1 | head -40

section "3. Class-of-Service (CoS) queues - DMA channel mapping"
sub "CMIC RX COS control"
$BC "g CMIC_CMC_COS_CTRL_RX_0" 2>&1 | head -10
$BC "g CMIC_CMC_COS_CTRL_RX_1" 2>&1 | head -10
sub "CPU CoS queue counters"
$BC "show counter c cpu" 2>&1 | head -30
$BC "show c cpu" 2>&1 | head -30
sub "CPU port = port 0"
$BC "ge 0" 2>&1 | head -20

section "4. CPU port mappings (where CPU connects to fabric)"
sub "CPU port info"
$BC "ge cpu" 2>&1 | head -20
$BC "ge cmic" 2>&1 | head -20
sub "iPipe egress to CPU"
$BC "g CPU_PORT_AS_DST_FOR_HIGIG_PORTS" 2>&1 | head -5
$BC "g ING_CPU_TRAP_CONTROL" 2>&1 | head -5

section "5. DMA Descriptor Buffers (DCBs) - the actual punt mechanism"
sub "CMIC packet DMA channels"
for ch in 0 1 2 3; do
  $BC "g CMIC_CMC_PKT_DMA_DESC_${ch}" 2>&1 | head -3
done
sub "DMA control + status"
$BC "g CMIC_CMC_DMA_CTRL" 2>&1 | head -10
$BC "g CMIC_CMC_DMA_STAT" 2>&1 | head -10
sub "RX buffer thresholds"
$BC "g CMIC_RXBUF_PKT_BUFFER_CONFIG" 2>&1 | head -5

section "6. switchd RX path - file descriptors and netlinks"
echo "switchd opens 52 TUN fds:"
ls /proc/$(pgrep -x switchd)/fd 2>/dev/null | wc -l
echo "TUN fds:"
ls -la /proc/$(pgrep -x switchd)/fd 2>/dev/null | grep "tun\|net/tun" | wc -l
echo "BDE fd:"
ls -la /proc/$(pgrep -x switchd)/fd 2>/dev/null | grep "bde"
echo "uio fds (if any):"
ls -la /proc/$(pgrep -x switchd)/fd 2>/dev/null | grep "uio\|netlink\|sock"

section "7. Active strace on switchd to capture punt loop (5 seconds)"
echo "Attaching strace to switchd to see punt loop..."
timeout 5 strace -p $(pgrep -x switchd) -e read,write,recvfrom,recvmsg,sendmsg,sendto,ioctl,poll,select -c 2>&1 | head -30

section "8. ACL/setclass mapping (Linux iptables CLASS -> BCM COS)"
sub "Linux iptables classifying control traffic"
iptables -L -n -v 2>&1 | grep -i setclass | head -10
sub "ebtables classifying L2 control"
ebtables -L 2>&1 | grep -iE "setclass|class" | head -10

section "9. Look at the configd rc.datapath_0 for trap setup"
echo "Searching rc.datapath_0 for trap and cpu setup..."
grep -iE "trap|cpu|cmic|punt|cos|station" /var/lib/cumulus/rc.datapath_0 | head -30

section "10. Packet to CPU flow trap reasons (BCM trap codes)"
$BC "trap" 2>&1 | head -50

section "11. switchd PID + binary info"
echo "PID: $(pgrep -x switchd)"
ls -la /usr/sbin/switchd
file /usr/sbin/switchd 2>&1
echo "Open netlink sockets:"
cat /proc/$(pgrep -x switchd)/net/netlink 2>/dev/null | head -10

section "12. CMIC_RX_COS_VALID_BMP - which CoS queues are active for RX"
$BC "g CMIC_CMC_COS_CTRL_RX_0" 2>&1
$BC "g CMIC_CMC_COS_CTRL_RX_1" 2>&1

section "13. The L3_HOST_ENTRY / IP host table - for ARP punt"
$BC "l3 l3table show" 2>&1 | head -20
$BC "l3 defip show" 2>&1 | head -20

section "14. cpu_port = port 0 - check what's bound to it"
$BC "linkscan" 2>&1 | head -5

echo "######### PUNT PATH ANALYSIS COMPLETE #########"

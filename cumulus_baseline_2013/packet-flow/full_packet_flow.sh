#!/bin/bash
# Full packet-flow trace - every layer, every stage
BC="/usr/lib/cumulus/bcmcmd"
SECT() { echo ""; echo "############################################################"; echo "## $*"; echo "############################################################"; }
sub() { echo ""; echo "==== $* ===="; }

# Use one of the actively linked ports for per-port queries
P=xe0  # = swp1
P2=xe48  # = swp49 QSFP

##############################################################
SECT "LAYER 1 - PHYSICAL: optical → retimer → SerDes → PCS"
##############################################################

sub "1.1 SFP+ optical module status (swp1)"
ethtool -m swp1 2>&1 | head -40

sub "1.2 SFP+ DOM/diagnostics raw (swp1)"
ethtool -m swp1 raw on offset 0x100 length 32 2>&1 | head -10
echo "--- bytes 96-105 of A2 page = real-time DOM ---"
od -An -tx1 -N 16 -j 256 /sys/class/eeprom_dev/eeprom7/device/eeprom 2>&1

sub "1.3 DS100DF410 retimer state for swp1 (qsfp_rx label, sfp_rx_eq_0)"
# Find which retimer is for swp1 - it should be sfp_rx_eq_0
for r in /sys/class/retimer_dev/retimer*; do
  label=$(cat $r/label 2>/dev/null)
  if [ "$label" = "sfp_rx_eq_0" ] || [ "$label" = "sfp_tx_eq_0" ]; then
    echo "--- $r ($label) ---"
    for f in $r/device/*; do
      [ -f "$f" ] && [ -r "$f" ] && echo "  $(basename $f) = $(cat $f 2>/dev/null | head -c 100)"
    done
  fi
done

sub "1.4 Warpcore SerDes state - PHY 0xd1 (xe0/swp1 in block 16)"
$BC "phy info $P" 2>&1 | grep $P
$BC "phy control $P" 2>&1
# CL45 PMA/PMD status (devad=1, reg 0x0001 = status)
$BC "phy $P 1 0x0001" 2>&1
$BC "phy $P 1 0x0008" 2>&1  # PMA fault
# CL45 PCS status (devad=3)
$BC "phy $P 3 0x0001" 2>&1  # PCS status
$BC "phy $P 3 0x0020" 2>&1  # PCS BASE-R status (block_lock!)
$BC "phy $P 3 0x0021" 2>&1  # PCS BASE-R BER counter
$BC "phy $P 3 0x0022" 2>&1  # PCS error block counter

sub "1.5 PCS 10GBASE-R block_lock + hi_ber check"
# devad=3 reg 0x0020: bit 0 = block_lock, bit 1 = hi_ber
echo "(0x0020 bit 0 = block_lock | bit 1 = hi_ber)"
$BC "phy $P 3 0x0020" 2>&1

sub "1.6 Lane sync / 64B/66B alignment"
$BC "phy $P 4 0x0018" 2>&1  # XGXS lane status
$BC "phy $P 4 0x0019" 2>&1

sub "1.7 MAC/PCS port mode + frame size"
$BC "g IPORT_OVERSUB_REG_ADDR" 2>&1 | head -3
$BC "g GPORT_SPEED_CONFIG" 2>&1 | head -3
$BC "g $P EGR_PORT_FRAME_MAX_64" 2>&1 | head -3 || echo "(try alt reg name)"
$BC "g $P FRM_LENGTH_64" 2>&1 | head -3 || echo "(try alt)"
$BC "ge $P" 2>&1 | head -20

##############################################################
SECT "LAYER 2 - DATA LINK: MAC, VLAN, L2 lookup, MY_STATION"
##############################################################

sub "2.1 Linux MAC and MTU"
ip -s link show swp1
echo "MTU: $(cat /sys/class/net/swp1/mtu)"
echo "MAC: $(cat /sys/class/net/swp1/address)"

sub "2.2 BCM port MAC config (FRAME_MAX = jumbo etc.)"
$BC "ps $P" 2>&1

sub "2.3 ARL / L2 MAC table - up to 16 entries"
$BC "l2 show" 2>&1 | head -20

sub "2.4 MY_STATION_TCAM entries (for L2 termination → L3 punt)"
echo "(Captured separately in punt-path - just count here)"
$BC "g MY_STATION_TCAM.ipipe0" 2>&1 | grep VALID=1 | wc -l

sub "2.5 VLAN table - default + tagged"
$BC "vlan show" 2>&1 | head -20

sub "2.6 STP state (per VLAN, per port)"
$BC "stg show" 2>&1 | head -20

sub "2.7 Port VLAN tag mode (untagged/access vs trunk)"
$BC "g PORT_TAB.ipipe0[$P]" 2>&1 | head -2 || echo "(try alt name)"
$BC "g VLAN_CTRL_$P" 2>&1 | head -3 || echo "(try alt)"
$BC "ps $P" 2>&1 | head -10

##############################################################
SECT "LAYER 2.5 - INTERNAL PIPELINE: iPipe → MMU → ePipe"
##############################################################

sub "3.1 iPipe ingress port table"
$BC "g IPORT_TAB.ipipe0[$P]" 2>&1 | head -2 || $BC "dump IPORT_TAB ipipe0" 2>&1 | head -5

sub "3.2 Field Processor (FP) - ACL TCAM"
$BC "fp show group" 2>&1 | head -20
$BC "fp show stats" 2>&1 | head -10

sub "3.3 FP entries per slice"
for s in 0 1 2 3; do
  echo "--- slice $s ---"
  $BC "fp show entry slice=$s" 2>&1 | head -10
done

sub "3.4 Metering / policers"
$BC "g MA_METER_TAB.ipipe0[0]" 2>&1 | head -2 || echo "(needs index)"
$BC "show meter" 2>&1 | head -10

sub "3.5 MMU (Memory Management Unit) - packet buffers"
$BC "mmu info" 2>&1 | head -20
$BC "show mmu" 2>&1 | head -20

sub "3.6 Buffer pool config"
$BC "g pg_min_cell" 2>&1 | head -3
$BC "show buffer" 2>&1 | head -20

sub "3.7 Egress port queue config (8 queues per port)"
for q in 0 1 2 3 4 5 6 7; do
  echo "queue $q config:"
  $BC "g op_queue_config_cell[$q].$P" 2>&1 | head -2
done

sub "3.8 COS scheduler (WRR/DWRR weights)"
$BC "g s2_cosweights.$P" 2>&1 | head -5
$BC "g cosweights" 2>&1 | head -5

##############################################################
SECT "LAYER 3 - NETWORK: IP routing, ARP, NDP, ECMP"
##############################################################

sub "4.1 Linux kernel routing"
ip route 2>&1
ip -6 route 2>&1 | head -10

sub "4.2 Kernel ARP / NDP"
ip neigh show

sub "4.3 BCM L3 default route TCAM (DEFIP)"
$BC "l3 defip show" 2>&1 | head -30

sub "4.4 BCM L3 host table"
$BC "l3 l3table show" 2>&1 | head -20
$BC "l3 ip6host show" 2>&1 | head -10

sub "4.5 BCM L3 egress next-hop table"
$BC "l3 egress show" 2>&1 | head -20

sub "4.6 BCM L3 interface table (L3_IIF)"
$BC "l3 intf show" 2>&1 | head -20
$BC "show l3 intf" 2>&1 | head -10

sub "4.7 ECMP groups"
$BC "l3 multipath show" 2>&1 | head -10
$BC "l3 ecmp show" 2>&1 | head -10

sub "4.8 cpu_control_1 (CPU trap flags)"
$BC "g cpu_control_1" 2>&1 | head -3

sub "4.9 TTL handling"
$BC "g ING_TTL_EQ_1_BAD" 2>&1 | head -3
$BC "g ING_IP_TTL_THRESHOLD" 2>&1 | head -3 || echo "(naming)"

##############################################################
SECT "LAYER 4 - TRANSPORT: TCP/UDP"
##############################################################

sub "5.1 Kernel network stats"
netstat -s 2>&1 | head -50

sub "5.2 Listening sockets"
ss -tnlp 2>&1 | head -20
ss -unlp 2>&1 | head -20

sub "5.3 Active sockets"
ss -tn 2>&1 | head -10

##############################################################
SECT "CPU PATH: switchd ↔ BDE ↔ CMIC ↔ TUN"
##############################################################

sub "6.1 switchd fds (BDE + 52 TUN + sockets)"
ls -la /proc/$(pgrep -x switchd)/fd 2>/dev/null | awk '{print $NF}' | sort -u | head -20

sub "6.2 BDE driver state"
cat /proc/linux-user-bde 2>/dev/null | head -30 || echo "(no /proc/linux-user-bde)"
ls /sys/class/bde 2>/dev/null

sub "6.3 CMIC DMA channel states"
for ch in 0 1 2 3; do
  echo "channel $ch:"
  $BC "g CMIC_CMC_DMA_CTRL($ch)" 2>&1 | head -2 || \
  $BC "g CMIC_CMC_PKT_DMA_DESC_$ch" 2>&1 | head -2
done

sub "6.4 CMIC RX statistics"
$BC "show counter c cpu" 2>&1 | head -20

sub "6.5 CPU CoS queues with current depth"
for q in 0 1 2 3 4 5 6 7; do
  $BC "g CMIC_CMC_COS_QUEUE_DEPTH($q)" 2>&1 | head -1
done

sub "6.6 Linux network softirq stats"
cat /proc/net/softnet_stat 2>&1 | head -5

##############################################################
SECT "INGRESS COUNTERS PER STAGE (live counters)"
##############################################################

sub "7.1 Per-port detailed counters for swp1 (xe0)"
$BC "show counter c $P" 2>&1 | head -80

sub "7.2 RX/TX byte+packet totals"
ip -s link show swp1
echo
ip -s link show swp2

sub "7.3 BCM ingress port stats"
$BC "g RUC_xe0,RUCA_xe0,RMCA_xe0,RBCA_xe0,RBYT_xe0" 2>&1 | head -5 || echo "(syntax)"

sub "7.4 CMIC TX/RX drop counters"
$BC "show counter | grep -i cpu" 2>&1 | head -10
$BC "show counter | grep -i drop" 2>&1 | head -20

##############################################################
SECT "VLAN TRANSLATION + ENCAP"
##############################################################

sub "8.1 Ingress VLAN translation table"
$BC "g VLAN_XLATE.ipipe0[0]" 2>&1 | head -2

sub "8.2 Egress VLAN translation table"
$BC "g EGR_VLAN_XLATE.epipe0[0]" 2>&1 | head -2

sub "8.3 Default VLAN per port"
$BC "g PORT_TAB" 2>&1 | head -5

##############################################################
SECT "MIRRORING / SPAN / SFLOW"
##############################################################

sub "9.1 Mirror config"
$BC "mirror show" 2>&1 | head -20

sub "9.2 sFlow / sample rate"
$BC "sflow show" 2>&1 | head -10
$BC "g ING_IFP_PROFILE" 2>&1 | head -3

##############################################################
SECT "QoS - DSCP/COS mapping"
##############################################################

sub "10.1 DSCP→CoS map (ingress)"
$BC "g ING_DSCP_TABLE.ipipe0[0]" 2>&1 | head -2

sub "10.2 CoS→DSCP map (egress)"
$BC "g EGR_DSCP_TABLE.epipe0[0]" 2>&1 | head -2

sub "10.3 802.1p (PCP)→CoS map"
$BC "g ING_PRI_CNG_MAP" 2>&1 | head -3

##############################################################
SECT "INTERRUPTS / INDICATIONS"
##############################################################

sub "11.1 CMIC interrupt status"
$BC "g CMIC_INTERRUPT_LO" 2>&1 | head -3
$BC "g CMIC_INTERRUPT_HI" 2>&1 | head -3
$BC "g CMIC_INTERRUPT_ENABLE_LO" 2>&1 | head -3

sub "11.2 Linkscan thread"
$BC "linkscan" 2>&1 | head -10

sub "11.3 Linux interrupts that drive switchd"
grep -E "ehc|bde|cmic|fsl|bcm" /proc/interrupts | head -15
echo --- top interrupts ---
head -20 /proc/interrupts

##############################################################
SECT "TIMING / FLOW CONTROL"
##############################################################

sub "12.1 Flow control (802.3x PAUSE)"
$BC "g RX_PAUSE_CTL_xe0" 2>&1 | head -3 || \
$BC "g PAUSE_CTRL" 2>&1 | head -3 || echo "(syntax)"

sub "12.2 PFC (Priority Flow Control)"
$BC "g PFC" 2>&1 | head -3 || echo "(no PFC syntax)"

##############################################################
SECT "PIPELINE BLOCK STATUS"
##############################################################

sub "13.1 Per-block enable/status"
$BC "g IPIPE_BLOCK_DISABLE" 2>&1 | head -3
$BC "g EPIPE_BLOCK_DISABLE" 2>&1 | head -3

sub "13.2 Pipeline busy?"
$BC "g IPIPE_BUSY" 2>&1 | head -3

##############################################################
echo ""
echo "########### FULL PACKET FLOW TRACE COMPLETE ###########"

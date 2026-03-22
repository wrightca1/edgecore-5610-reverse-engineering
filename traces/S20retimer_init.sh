#!/bin/sh

. /lib/init/vars.sh
. /lib/lsb/init-functions

set_eq1(){
    echo 12 > channels
    echo 1  > veo_clk_cdr_cap
    echo 28 > cdr_rst
    echo 16 > cdr_rst
}

# RX EQ 10, all QSFP TX and all QSFP RX
set_eq2(){
    echo 12 > channels
    echo 1 > veo_clk_cdr_cap
    echo 28 > cdr_rst
    echo 16 > cdr_rst
    echo 23 > tap_dem
}

log_action_msg "  Initializing Retimers.."

rdir="/sys/class/retimer_dev"
no_retimers=32
i=0

# Sanity Checking
[ -d $rdir ] || {
    log_failure_msg "Unable to find retimer class dir: $rdir"
    exit 1
}
[ `ls $rdir | wc -l` -eq $no_retimers ] || {
    log_failure_msg "$no_retimers retimers not found"
    exit 1
}

while [ $i -lt $no_retimers ] 
do
    # Sanity Checking
    [ -d "$rdir/retimer$i" ] || {
	log_failure_msg "Unable to find retimer for retimer$i"
	exit 1
    }
    [ -d "$rdir/retimer$i/device" ] || {
	log_failure_msg "Unable to find device dir for retimer$i"
	exit 1
    }
    [ -f "$rdir/retimer$i/label" ] || {
	log_failure_msg "Unable to find label for retimer$i"
	exit 1
    }
    [ -f "$rdir/retimer$i/device/channels" ] || {
	log_failure_msg "Unable to find channels for retimer$i"
	exit 1
    }
    [ -f "$rdir/retimer$i/device/veo_clk_cdr_cap" ] || {
	log_failure_msg "Unable to find veo_clk_cdr_cap for retimer$i"
	exit 1
    }
    [ -f "$rdir/retimer$i/device/cdr_rst" ] || {
	log_failure_msg "Unable to find cdr_rst for retimer$i"
	exit 1
    }
    [ -f "$rdir/retimer$i/device/tap_dem" ] || {
	log_failure_msg "Unable to find tap_dem for retimer$i"
	exit 1
    }

    label=`cat $rdir/retimer$i/label`
    cd "$rdir/retimer$i/device"

    case $label in
	"qsfp"*)
	    set_eq2 ;;
	"sfp_rx_eq_10") 
	    set_eq2 ;;
	*)
	    set_eq1 ;;
    esac
    i=$(( $i + 1 ))
done

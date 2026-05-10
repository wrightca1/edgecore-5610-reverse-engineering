#!/bin/sh

#
# Copyright 2014 Cumulus Networks, Inc.
# All rights reserved.
#

# Invoked by /etc/init.d/hw_init

# Configure the GPIOs connected to the 4 QFSPs to:
# a) Take the module out of reset
# b) Enable the module

[ "$1" = "start" ] || exit 0

# Load the VERBOSE setting and other rcS variables
. /lib/init/vars.sh

# Define LSB log_* functions.
# Depend on lsb-base (>= 3.2-14) to ensure that this file is present
# and status_of_proc is working.
. /lib/lsb/init-functions

log_action_msg "  Initializing GPIOs.."

sysfs_gpio="/sys/class/gpio"
gpio_chips="160 168"
expected_label="pca9538"
expected_ngpio="8"

# Sanity checking:

for chip in $gpio_chips; do
    [ -d "$sysfs_gpio/gpiochip${chip}" ] || {
        log_failure_msg "Unable to find QSFP GPIO chip: gpiochip${chip}"
        exit 1
    }

    label="$(cat $sysfs_gpio/gpiochip${chip}/label)"
    [ "$label" = "$expected_label" ] || {
        log_failure_msg "Unexpected QSFP GPIO chip label: $label"
        exit 1
    }

    ngpio="$(cat $sysfs_gpio/gpiochip${chip}/ngpio)"
    [ "$ngpio" = "$expected_ngpio" ] || {
        log_failure_msg "Unexpected QSFP GPIO chip ngpio: $ngpio"
        exit 1
    }
done

set_gpio() {
    start=$1
    stop=$2
    value=$3

    for gpio in `seq $start $stop`; do
        echo $gpio > $sysfs_gpio/export

        gpio_path="$sysfs_gpio/gpio${gpio}"
        [ -d "$gpio_path" ] || {
            log_failure_msg "Unable to export GPIO: $gpio"
            exit 1
        }

        echo out > "$gpio_path/direction"
        echo $value > "$gpio_path/value"
    done
}

# 97 - 104: sfp tx disable
set_gpio 97 104 0
# 24 - 64: sfp tx disable
set_gpio 24 64 0
# 168 - 171: lpmode (output) for qsfp1..4
set_gpio 168 171 0
# 164 - 167: modsel_l (output) for qsfp1..4
set_gpio 164 167 0
# 160 - 163: rst_l (output) for qsfp1..4
set_gpio 160 163 1
# 48 - 51 presence (input) for qsfp1..4
for gpio in `seq 48 51`; do
    echo $gpio > $sysfs_gpio/export
done

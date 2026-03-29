#! /bin/sh
### BEGIN INIT INFO
# Provides:          hw_init
# Required-Start:    kmod
# Required-Stop:     kmod
# X-Start-Before:    switchd
# X-Stop-After:      hwclock
# Default-Start:     S
# Default-Stop:      0 6
# Short-Description: HW init
# Description:       Platform specific hardware initialization
### END INIT INFO

# Author: Curt Brune <curt@cumulusnetworks.com>
#
# Please remove the "Author" lines above and replace them
# with your own name if you copy and modify this script.

# PATH should only include /usr/* if it runs after the mountnfs.sh script
PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/cumulus/bin
DESC="Hardware Initialization"
NAME=hw_init
SCRIPTNAME=/etc/init.d/$NAME

#
# Run all the scripts found in
# /usr/share/platform-config/$platform/hw_init
#

CONFIGDIR="/usr/share/platform-config"
PLATFORM="$(platform-detect)"
PLATFORM_DIR="${CONFIGDIR}/${PLATFORM%%,*}/${PLATFORM##*,}"
HW_INIT_DIR="${PLATFORM_DIR}/hw_init.d"

[ -d "$HW_INIT_DIR" ] || exit 0

# Load the VERBOSE setting and other rcS variables
. /lib/init/vars.sh

# Define LSB log_* functions.
# Depend on lsb-base (>= 3.2-14) to ensure that this file is present
# and status_of_proc is working.
. /lib/lsb/init-functions

case "$1" in
  start)
        log_action_msg "$DESC: starting $PLATFORM"
        init_scripts=$(ls $HW_INIT_DIR/S* 2>&1) && {
            for s in $init_scripts ; do
                $s start
            done
        }
	;;
  stop)
        log_action_msg "$DESC: stopping $PLATFORM"
        init_scripts=$(ls $HW_INIT_DIR/K* 2>&1) && {
            for s in $init_scripts ; do
                $s stop
            done
        }
	;;
  *)
	;;
esac

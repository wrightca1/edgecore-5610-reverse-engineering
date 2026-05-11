#!/bin/sh
#
# Copyright 2012,2014,2015 Cumulus Networks, Inc.
#
# Wrapper around start-stop-daemon that picks up the nice level, ionice level and process
# scheduling priority from a configuration file and launches the real start-stop-daemon
# with these values.
#
# This is run assuming dash as the shell. Do not use bashisms in this script. If you
# modify this file run it by checkbashisms to ensure that there are no bashisms used
# which will cause the script to fail when used with dash.

SSDPKG="/sbin/start-stop-daemon.dpkg"
SSMON="/usr/lib/cumulus/start-stop-monitor"

rc=0
name=0
args=""
ignorenice=0
dargs=0
isstop=0
isstart=0
pretend=0
pid=0
pidfile=""
daemon=""
daemon_name=""
nice_file="/etc/cumulus/nice.conf"
namespace_file="/etc/cumulus/ns.conf"
monit_file="/etc/cumulus/ssmonitor.d"
sscmd=""

SS_DEBUG="no"

log_debug() {
    test "${SS_DEBUG}" = "yes" && echo "$(basename $0): DEBUG -- $@"
    return 0
}

for i in "$@"; do
    log_debug "i: $i"
    # if have not hit args for daemon we process special cases
    # where we need info or override args to start-stop-daemon
    if [ $dargs -eq 0 ]; then
        # Find pidfile
        if [ "$i" = "--pidfile" ] || [ "$i" = "-p" ]; then
            pid=1
            continue
        fi

        if [ $pid -eq 1 ]; then
            pidfile=$i
            pid=0
            continue
        fi

        # Extract name of daemon
        if [ $name -eq 1 ]; then
            daemon=$i
            name=0
            continue
        fi

        # Various ways in which daemon name can be specified
        if [ $i = "--exec" ] || [ $i = "-x" ]; then
            name=1
            continue
        fi
        if [ $i = "--startas" ] || [ $i = "-a" ]; then
            name=1
            continue
        fi
        if [ "$i" = "--name" ] || [ $i = "-n" ]; then
            name=1
            continue
        fi

        #if there was a nice option already specified, skip it
        if [ $i = "--nice" ] || [ $i = "-N" ] || \
           [ $i = "--prosched" ] || [ $i = "-P" ] || \
           [ $i = "--iosched" ] || [ $i = "-I" ]; then
            echo "Ignoring nice value. Specify nice in $nice_file"
            ignorenice=1;
            continue
        fi

        if [ $ignorenice -eq 1 ]; then
            ignorenice=0
            continue
        fi

        # We need to know if the user just wants s-s-d to just pretend to run
        # if so we will not run s-s-m.
        if [ "$i" = "--test" ] || [ "$i" = "-t" ]; then
            pretend=1
            # We want this to be applied to the args list so don't use the
            # keyword continue
        fi

        # Which execution command does the user want?
        if [ "$i" = "--start" ] || [ "$i" = "-S" ]; then
            isstart=1
            # We want this to be applied to the args list so don't use the
            # keyword continue
        fi

        # Don't bother with daemon stops
        if [ "$i" = "--stop" ] || [ "$i" = "-K" ]; then
            isstop=1
            continue
        fi

        # Mark the beginning of args passed to daemon as opposed to
        # start-stop-daemon
        if [ $i = "--" ]; then
            dargs=1
        fi
    fi

    #build the list of args to be passed to the real start-stop-daemon
    args="$args $i"
done

log_debug "args: ${args}"
log_debug "daemon: ${daemon}"

[ "${daemon}" != "" ] && \
    monit_file="${monit_file}/$(/usr/bin/basename ${daemon})-monit.rc"

log_debug "monit file: ${monit_file}"

if [ $pretend -ne 1 ] && [ $isstop -eq 1 ] && [ -f "${monit_file}" ]; then
    ${SSMON} "stop" "${monit_file}"
fi

# Build the command to be invoked
if [ $# -ne 0 -a $isstop -ne 1 -a "$daemon" != "" ]; then

    # priority file may contain only basename of daemon
    daemon_name=`/usr/bin/basename $daemon`

    nicelevel=`/bin/grep \^$daemon_name $nice_file | /usr/bin/awk '{print $2}'`
    ionicelevel=`/bin/grep \^$daemon_name $nice_file | /usr/bin/awk '{print $3}'`
    procsched=`/bin/grep \^$daemon_name $nice_file | /usr/bin/awk '{print $4}'`
    namespace=`/bin/grep \^$daemon_name $namespace_file | /usr/bin/awk '{print $2}'`
    NS=`cat /proc/self/mounts | grep sysfs | /usr/bin/cut -f1 -d' '`
    niceargs=""
    pidargs=""

    [ ! -z "$nicelevel" ] && [ "$nicelevel" != "default" ] && niceargs="--nicelevel $nicelevel"
    [ ! -z "$ionicelevel" ] && [ "$ionicelevel" != "default" ] && niceargs="$niceargs --iosched $ionicelevel"
    [ ! -z "$procsched" ] && [ "$procsched" != "default" ] && niceargs="$niceargs --procsched $procsched"
    [ ! -z "$pidfile" ] && pidargs="--pidfile $pidfile"

    if [ "$NS" != "sysfs" -a "$namespace" != "" -a "$NS" != "$namespace" ]; then
        sscmd="ip netns exec $namespace ${SSDPKG} --exec $daemon $niceargs $pidargs $args"
    else
        sscmd="${SSDPKG} --exec $daemon $niceargs $pidargs $args"
    fi
else
    sscmd="${SSDPKG} $@"
fi

#Invoke the command
log_debug "sscmd: ${sscmd}"
$sscmd
rc=$?

if [ $pretend -ne 1 ] && [ $isstart -eq 1 ] && \
   [ "${daemon}" != "" ] && [ -f "${monit_file}" ]; then
    ${SSMON} "start" "${monit_file}"
fi

exit $rc

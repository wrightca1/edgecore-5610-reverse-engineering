#!/bin/sh
# Capture ONIE live state — run from the ONIE shell after booting into
# install/rescue mode.  Read-only.  Compatible with busybox-ash (no bash).
#
# Usage in ONIE:
#   wget http://<server>/capture-from-onie.sh -O /tmp/cap.sh
#   chmod +x /tmp/cap.sh
#   /tmp/cap.sh
#   tar czf /tmp/onie-live.tgz /tmp/onie-live
#   wget --post-file=/tmp/onie-live.tgz http://<server>/upload   (or scp)

set -u
OUT=/tmp/onie-live
mkdir -p "$OUT"

section() { echo; echo "==== $* ===="; }

#----- Identity & build ---------------------------------------------------
section "identity"
{
    echo "=== uname -a ==="
    uname -a
    echo
    echo "=== /etc/machine.conf ==="
    cat /etc/machine.conf
    echo
    echo "=== /etc/issue ==="
    cat /etc/issue
    echo
    echo "=== /etc/os-release ==="
    cat /etc/os-release 2>/dev/null
    echo
    echo "=== /etc/lsb-release ==="
    cat /etc/lsb-release 2>/dev/null
    echo
    echo "=== onie-sysinfo (all flags) ==="
    onie-sysinfo -v 2>&1
    for flag in p a v m r c b s; do
        printf -- "-%s: " "$flag"; onie-sysinfo -"$flag" 2>&1
    done
} > "$OUT/identity.txt" 2>&1

#----- Boot reason and ONIE state ----------------------------------------
section "boot state"
{
    echo "=== /proc/cmdline ==="
    cat /proc/cmdline
    echo
    echo "=== boot reason environment ==="
    env | grep -iE 'onie|boot_reason|exec_url|install_url|cli_static' | sort
    echo
    echo "=== /tmp/.install_url_parms ==="
    cat /tmp/.install_url_parms 2>&1
    echo
    echo "=== /etc/inittab ==="
    cat /etc/inittab 2>&1
} > "$OUT/boot_state.txt" 2>&1

#----- Process tree, fd table --------------------------------------------
section "processes"
ps -ef > "$OUT/ps.txt" 2>&1
ps wwwo pid,ppid,user,stat,cmd > "$OUT/ps_wide.txt" 2>&1
for d in /proc/[0-9]*; do
    pid=${d#/proc/}
    name=$(cat "$d/comm" 2>/dev/null)
    echo "=== pid $pid ($name) ==="
    echo "  cmdline:  $(tr '\0' ' ' < $d/cmdline 2>/dev/null)"
    echo "  cwd:      $(readlink $d/cwd 2>/dev/null)"
    echo "  exe:      $(readlink $d/exe 2>/dev/null)"
    echo "  fds:"
    ls -l "$d/fd" 2>/dev/null | sed 's/^/    /'
    echo "  maps (top 10):"
    head -10 "$d/maps" 2>/dev/null | sed 's/^/    /'
    echo
done > "$OUT/proc_walk.txt" 2>&1

#----- Network state -----------------------------------------------------
section "network"
{
    echo "=== ip link ==="
    ip link show
    echo
    echo "=== ip addr ==="
    ip addr show
    echo
    echo "=== ip route ==="
    ip route show
    echo
    echo "=== resolv.conf ==="
    cat /etc/resolv.conf 2>/dev/null
    echo
    echo "=== /var/run/dhcp* ==="
    ls -la /var/run/ 2>/dev/null
    echo
    echo "=== udhcpc state ==="
    ps -ef | grep -i 'udhcp\|dhcp\|discover' | grep -v grep
} > "$OUT/network.txt" 2>&1

#----- ONIE-specific tools -----------------------------------------------
section "onie-tools"
{
    for cmd in onie-sysinfo onie-syseeprom onie-fwpkg onie-nos-install onie-self-update; do
        echo "=== $cmd ==="
        which "$cmd" 2>&1
        "$cmd" --help 2>&1 | head -25
        echo
    done
    echo "=== onie-syseeprom (full TLV dump) ==="
    onie-syseeprom -a 2>&1
} > "$OUT/onie_tools.txt" 2>&1

#----- Filesystem layout -------------------------------------------------
section "filesystem"
{
    echo "=== mount ==="
    mount
    echo
    echo "=== /proc/mounts ==="
    cat /proc/mounts
    echo
    echo "=== /proc/mtd ==="
    cat /proc/mtd
    echo
    echo "=== /proc/partitions ==="
    cat /proc/partitions
    echo
    echo "=== lsblk ==="
    lsblk 2>&1
    echo
    echo "=== fdisk -l /dev/sda ==="
    fdisk -l /dev/sda 2>&1
    echo
    echo "=== blkid ==="
    blkid 2>&1
} > "$OUT/filesystem.txt" 2>&1

#----- ONIE config / scripts (whole /etc + /var) --------------------------
section "config"
mkdir -p "$OUT/etc"
cp -a /etc/. "$OUT/etc/" 2>/dev/null || true
mkdir -p "$OUT/var"
cp -a /var/log "$OUT/var/" 2>/dev/null || true
mkdir -p "$OUT/scripts-bin"
# Only the small text scripts, not all of /bin (busybox dominates)
for d in /etc/init.d /bin /sbin; do
    for f in "$d"/*; do
        [ -f "$f" ] || continue
        head -1 "$f" 2>/dev/null | grep -q '^#!' && cp "$f" "$OUT/scripts-bin/" 2>/dev/null
    done
done

#----- ONIE install simulator (dry-run, do NOT actually install) ----------
section "install-flow-dry-run"
{
    echo "=== /etc/init.d/discover.sh contents ==="
    cat /etc/init.d/discover.sh
    echo
    echo "=== current discover state, if any ==="
    ls /tmp/installer 2>/dev/null
    cat /tmp/installer/*.log 2>/dev/null | head -200
} > "$OUT/discover.txt" 2>&1

#----- U-Boot env (live, in ONIE) ----------------------------------------
section "uboot-env"
fw_printenv 2>&1 | sort > "$OUT/fw_printenv_in_onie.txt"

#----- ONIE kernel cmdline, dmesg ----------------------------------------
section "dmesg"
dmesg > "$OUT/dmesg.txt" 2>&1

#----- Modules loaded ----------------------------------------------------
section "modules"
{
    echo "=== lsmod ==="
    lsmod
    echo
    echo "=== /lib/modules/$(uname -r) ==="
    find /lib/modules -name '*.ko' 2>/dev/null | head -50
} > "$OUT/modules.txt" 2>&1

#----- USB / PCI topology ------------------------------------------------
section "hw-topology"
{
    echo "=== lsusb ==="
    lsusb 2>&1
    echo
    echo "=== lspci -v ==="
    lspci -v 2>&1 || lspci 2>&1
    echo
    echo "=== /sys/bus/usb/devices/ ==="
    ls -la /sys/bus/usb/devices/ 2>&1
} > "$OUT/hw_topology.txt" 2>&1

echo
echo "==== capture complete: $OUT ===="
ls -lh "$OUT/"
echo
echo "Pack with:  tar czf /tmp/onie-live.tgz -C /tmp onie-live"

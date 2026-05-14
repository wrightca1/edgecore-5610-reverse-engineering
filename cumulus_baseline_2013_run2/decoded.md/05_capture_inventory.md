---
name: project_cumulus_full_capture_2026_05_13
description: "Comprehensive Cumulus 2.5.0 capture from the live AS5610-52X — 616 MB of chip+software state. What we got and what's gaps."
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# Captures (all under /home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/)

| Archive | Size | Coverage |
|---|---|---|
| `streamed_20260513_162341/` + `.tgz` | **500MB / 7MB** | `DUMP SOC` (49,732 regs w/ names) + `DUMP SOCMEM` (1.47M memory cells w/ names) + DIFF variants. **The gold mine** for offline analysis. |
| `fixup_20260513_163730/` + `.tgz` | 14MB / 1.3MB | 60-sec strace under ping flood, BAR1/DMA-region hexdump, partial chip tables, FUSE walk |
| `routes_20131001_121841.tgz` | 311KB | Before/after L3 chip-table diff when route is added |
| `single_20131001_123018.tgz` | 148KB | ECMP-active vs single-path diff (took swp2 down) |
| `dma_20131001_123802.tgz` | 137KB | RX/TX DMA strace + register state under load |
| `cap_20131001_121651.tgz` | 196KB | First bulk capture (BAR0 attempts failed) |
| `extra_20131001_121652.tgz` | 7.5KB | Initial OSPF + thermal snapshot |

# What's IN it (offline-decodable)

## chip register state — `streamed_*/soc/`
- `dump_soc.txt` — 49,732 entries. Every chip register read with its name. Format `0xADDR NAME.block = 0xVAL`. Examples:
  - `0x0a180d08 L3_DEFIP_CAM_ENABLE.ipipe0 = 0x000003ff`
  - `0x03332000 ASF_PORT_SPEED.xe0 = 0x0000000c`
- `dump_soc_diff.txt` — 6,415 entries (only regs differing from chip reset). **This is what's actually configured.**
- `dump_socmem.txt` — 1.47 MILLION lines, every chip memory cell w/ name
- `dump_socmem_diff.txt` — 228,312 entries (only memory differing from reset). All L3_DEFIP / L3_ENTRY / EGR_L3_INTF / VLAN content lives here.

**Mining method**: `grep 'PKTDMA' soc/dump_soc.txt` returns every CMICm DMA register state. `grep '^Memory: L3_DEFIP' soc/dump_socmem_diff.txt` returns every L3_DEFIP cell with content.

## chip diag command outputs — `streamed_*/tables/`
- `_diag_l3_defip_show.txt` — full DEFIP table (43 routes with INTF ptrs)
- `_diag_l3_l3table_show.txt` — L3_ENTRY hash table (ARP cache)
- `_diag_l3_egress_show.txt` — INTF id → MAC/VLAN/port resolution
- `_diag_l3_intf_show.txt` — per-port src MAC + service VID (52 entries)
- `_diag_l2_show.txt`, `_diag_vlan_show.txt`, `_diag_ps.txt` etc.
- `_cmicm_regs.txt` — focused CMICm DMA register state
- 30+ raw tables (DLB_HGT, OVQ_BANK, etc.) plus `fixup_*/tables/` adds more

## live strace under ping load — `fixup_*/strace/io_60sec.log`
- 60 seconds of full syscall trace, switchd under sustained ping
- All `ioctl(14, 0x20004c0X)` BDE calls, all read/write/sendto/recvmsg, mmap
- This proves: switchd uses `LUBDE_WAIT_FOR_INTERRUPT (ioctl 9)` + `LUBDE_SEM_OP (ioctl 10)` — interrupt-driven, not polling. Per `project_cumulus_dma_decoded`.

## switchd FUSE state — `streamed_*/fuse/` + `fixup_*/switchd/contents/`
- /cumulus/switchd is a 295-entry FUSE filesystem (per `project_sfs_internals`).
- All small files dumped — switchd's own runtime introspection interface

## binaries — `streamed_*/binaries/`
- `switchd` (68KB — pulled via `cat /proc/PID/exe`)
- `bcmcmd`, `cl-license`, `cl-cfg`, `cl-acltool`, `zebra`, `ospfd`, `quagga`

## kernel modules — `streamed_*/modules/` (1.7MB)
- `linux_user_bde.ko`, `linux_kernel_bde.ko`, `linux_bde_tmon.ko`
- `accton_as5610_52x_cpld.ko`, `ds100df410.ko`
- Reverse-engineer these for chip access primitives

## DMA-region host RAM — `fixup_*/bar0/dma_region.bin` (512KB)
- Physical 0x02400000-0x02480000, where switchd mmaps its 64MB DMA pool
- Contains DCB rings + packet buffers
- Use binwalk / `xxd` to inspect

## misc state
- `streamed_*/procfs/` — /proc/{cpuinfo,iomem,interrupts,mounts,cmdline,sysctl,...}, ip route, ip neigh, lspci, fw_printenv
- `streamed_*/cumulus/` — entire /etc/cumulus, /etc/network, /etc/quagga (848KB)
- `streamed_*/vtysh/` — show running-config, show ip ospf, show ip route, etc.
- `streamed_*/phy/` — PHY diag dumps for xe0/xe1
- `streamed_*/logs/` — dmesg + last 20MB of each /var/log/*

# gcorev3 capture — added 2026-05-13 ~5:59 PM EDT (~6:59 PM EDT)

After installing **gdb 7.4.1** on Cumulus 2.5.0 (via `apt-get -t wheezy --allow-unauthenticated install gdb` pointed at archive.debian.org), captured:

| Archive | Size | Coverage |
|---|---|---|
| `gcorev3_20260513_171317/gcore/sw.core` | **123 MB** | Full ELF core dump of running switchd — every byte of switchd's memory: DCB ring addrs, software shadow tables, allocator state, in-memory L3/L2 maps. PowerPC 32-bit MSB. |
| `gcorev3_*/switchd/libs/` | 3.1 MB | All 10 shared libs `ldd switchd` requires (libnl, libfuse, libc, libpthread, libm, etc.) — enables `gdb sw.core` offline with full symbol resolution. |
| `gcorev3_*/sfp/sfp.txt` | 9.5 KB | First 256B of every populated SFP eeprom (52 entries) — vendor strings, part numbers, DOM serial. |
| `gcorev3_*/cpld/cpld.txt` | 26 KB | i2c CPLD devices (5: pca9538 GPIO expanders + max6697 thermal chip). max6697 temp1_input = 22000 (22°C board temp). |
| `gcorev3_*/thermal/thermal.txt` | 156 B | hwmon entries on Cumulus 2.5 (sparse — most thermal is i2c/CPLD, not /sys/class/hwmon). |
| `gcorev3_*/switchd/switchd_ldd.txt` + `switchd_libs_paths.txt` | 1 KB | Loader paths for offline gdb. |

**Now you can do offline:**
```
gdb -ex 'set sysroot /home/.../gcorev3_*/switchd/libs' /home/.../streamed_*/binaries/switchd /home/.../gcorev3_*/gcore/sw.core
(gdb) info threads
(gdb) bt
(gdb) info regs
(gdb) x/16xw <DCB ring addr from strace>
```

# Fan / thermal control — what we found

On AS5610-52X under Cumulus, fan control is **NOT via /sys/class/hwmon** (that's nearly empty). It's via:
- **max6697 thermal sensor** at i2c bus 9 addr 0x4d — exposes temp1_input..temp5_input (sensor #1 = 22°C in this snapshot)
- **CPLD GPIO** (pca9538 chips at i2c bus 16 addresses 0x70..0x73) — these are the actual fan PWM/direction control
- **accton_as5610_52x_cpld.ko** kernel module (in `streamed_*/modules/`) drives them

For EdgeNOS to control fans: read max6697 temps, write CPLD PWM bytes. (Already partially done via the `cpld_fan.c` tool — see [[project_led_dance]] adjacent work.)

# What's STILL missing

1. **BAR0 idle/loaded hexdump** — kernel STRICT_DEVMEM blocks /dev/mem reads at phys 0xa0000000. Workaround: read via `bcmcmd "getreg"` (we have that in `dump_soc.txt`). True raw BAR0 would require disabling STRICT_DEVMEM (kernel boot option, not worth a reboot).
2. **/proc/device-tree raw** — script bug, low priority since `/proc/cpuinfo` + `dmesg` cover the same info.

# Reflash-cost note
The switch is currently running Cumulus 2.5.0 with full OSPF up. Reflashing back to EdgeNOS will lose this live state. **Do not** reflash until we've extracted everything decodable.

Linked: [[project_cumulus_route_storage_decoded]], [[project_cumulus_dma_decoded]], [[project_cumulus_bulk_capture_strategy]], [[project_cumulus_reflash_capture_plan]], [[project_switch_ip_reflash]].

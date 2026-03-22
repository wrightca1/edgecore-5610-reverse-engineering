# Custom NOS Gap Analysis vs Cumulus AS5610-52X

**Date**: 2026-03-22
**Source**: Audit of /home/smiley/edgecore/newnos/ vs live switch RE data

---

## Status: ~15-20% Complete (Skeleton Only)

The custom NOS has a framework but **cannot boot, link, or forward packets**.

---

## What Works

| Component | File | Status |
|-----------|------|--------|
| BDE/CDK/BMD init | bde_interface.c | ASIC detected, reset, basic init |
| Port mapping | portmap.c | Lane/bus tables, swpN naming |
| TUN interfaces | packet_io.c | 52 TUN fds created, select loop |
| Netlink listener | netlink.c | Parses link/route/neigh/addr events |
| CPLD read | platform/cpld/ | PSU/fan status readable |
| Retimer driver | platform/retimer/ | I2C register access shell |
| Build system | Makefile | Kernel 5.10, buildroot, cross-compile |

## What's Missing (Critical Path)

### 1. SerDes / Warpcore Init -- 0% done
**Without this, NO ports link up.**

Need to implement the 7-phase init sequence per port:
- TX drive strength + amplitude (page 0x0000, regs 0x17/0x18)
- IEEE block enable (page 0x0008)
- AN/clock recovery (page 0x1000)
- SerDes digital control (page 0x0a00)
- RX equalization coefficients (regs 0x19-0x1d)
- Core sequencer start (page 0x3800)
- 30ms link polling loop

PHY address mapping: 6 addresses (1,5,9,13,17,21) across 3 MDIO buses.
MIIM access via `soc_miim_read/write` (functions at 0x10830b78 / 0x1082fabc).

### 2. XLPORT/MAC Register Config -- 0% done
**Without this, ports don't enable even if SerDes links.**

Per-port registers (repeating at 0x800 intervals in BAR0):
- XLPORT_XGXS_CTRL: mode/enable
- XLMAC_CTRL: MAC enable
- XLMAC_MODE: speed (10G/40G) + duplex
- XLMAC_PAUSE_CTRL: flow control
- XLPORT_ENABLE: final port enable
- `setreg xmac_tx_ctrl 0xc802`
- `m cmic_misc_control LINK40G_ENABLE=1`

### 3. DMA / Packet I/O -- 10% done (TUN only)
**Without this, no packets reach kernel or leave switch.**

TUN devices exist but TODO stubs for:
- `bmd_tx()` -- send packet from TUN to ASIC
- `bmd_rx_poll()` -- receive packet from ASIC to TUN
- BDE DMA ring management (RX ring at phys 0x04045740, 2044-byte buffers)
- BDE interrupt handler thread (WAIT_FOR_INTERRUPT ioctl 0x20004c09)
- S-Channel DMA for table operations

### 4. S-Channel Table Writes -- 0% done
**Without this, no L2/L3 forwarding in hardware.**

The soc_schan_op function (0x108623e4) handles all table writes:
- L2_USER_ENTRY (table 0x1547): 36-byte MAC/VLAN/port entries
- L3_DEFIP (table 0x22d3): 548-byte route entries
- VLAN (direct register)
- Opcodes: WRITE_REGISTER (0x0b), READ_MEMORY (0x07)

### 5. L2/L3 Table Formatting -- 2% done (stubs)
- L2: MAC at offset 0x08, VLAN at 0x14, port at 0x2c in 36-byte payload
- L3: 0x224-byte buffer with op code, entry arrays, format constants
- ECMP: table 0x2c32, group layout
- Hash/index: CRC16-CCITT for ECMP, hardware hash for L2

### 6. Buffer / QoS / Datapath -- 0% done
From rc.datapath_0:
- 46080 buffer cells across 4 service pools
- 8 CoS queues with weighted scheduling
- RTAG7 ECMP hash (CRC16-CCITT, bins for IP/L4/protocol)
- PFC disabled, pause RX enabled
- CPU control: L3 MTU fail, slow path, dst miss -> CPU

## What's Missing (Platform)

### 7. Retimer Init -- 5% done
32 DS100DF410 equalizers need programming:
```
channels=12, veo_clk_cdr_cap=1, cdr_rst=28 then 16
QSFP/SFP_RX: tap_dem=23
```

### 8. CPLD LED / Fan / Watchdog -- 15% done
- LED control: `echo green > led_psu1` etc. (not implemented)
- Fan PWM: `echo 64 > pwm1` (not implemented)
- Watchdog: enable/timeout/keep_alive (not implemented)
- System status logic (not implemented)

### 9. CMIC LED Processor -- 0% done
- Load 256-byte program into LED0/LED1
- `led 0 load led0.hex; led 0 start`
- Port LEDs: green=link, blink=activity

### 10. Sensor Monitoring -- 0% done
- MAX6697 (7-ch) + MAX1617 (2-ch) temperature
- Fan speed monitoring
- PSU status polling
- Over-temp shutdown logic

### 11. Boot Init Scripts -- 5% done
Missing entirely:
- /etc/modules (kernel module load order)
- hw_init (GPIO + retimer)
- switchd service (start/stop/restart)
- ledmgrd, pwmd, smond daemons
- networking integration

### 12. Device Tree -- 30% done
Missing I2C mux tree, CPLD node, retimer nodes, GPIO expanders.

### 13. ONIE Installer -- 0% done
No working installer for NOR flash + USB flash boot.

---

## Priority Order to Get a Working Switch

| Priority | Task | Lines Est. | Result |
|----------|------|-----------|--------|
| **P0** | SerDes/Warpcore init | 500 | Ports link up |
| **P0** | XLPORT/MAC config | 300 | Ports enabled |
| **P0** | Packet I/O (BMD TX/RX) | 400 | Packets forwarded |
| **P1** | S-Channel writes | 200 | L2/L3 in hardware |
| **P1** | L2 table formatting | 200 | MAC learning |
| **P1** | L3 route programming | 200 | IP routing |
| **P2** | Buffer/QoS config | 150 | Proper queuing |
| **P2** | Boot scripts | 200 | Auto-startup |
| **P2** | CPLD/LED/fan | 100 | System management |
| **P3** | Retimer coefficients | 100 | Signal quality |
| **P3** | Sensor monitoring | 100 | Thermal protection |
| **P3** | Device tree | 150 | Auto-discovery |
| **P3** | ONIE installer | 200 | Field deployment |

**Total estimated**: ~2,800 lines of new code + scripts

---

## Key RE Data Available for Implementation

Every item above has corresponding RE documentation:

| Need | RE Document |
|------|-------------|
| SerDes init sequence | SERDES_WC_INIT.md, CAPTURE_RESULTS_20260322.md §2 |
| XLPORT registers | PORT_BRINGUP_REGISTER_MAP.md, BAR diff data |
| Packet I/O | PKTIO_BDE_DMA_INTERFACE.md, CAPTURE_RESULTS §9 |
| S-Channel format | SCHAN_FORMAT_ANALYSIS.md, schan_msg_capture.txt |
| L2 table layout | L2_ENTRY_FORMAT.md, L2_WRITE_PATH_COMPLETE.md |
| L3 table layout | L3_NEXTHOP_FORMAT.md, L3_ECMP_VLAN_WRITE_PATH.md |
| PHY address map | CAPTURE_RESULTS_20260322.md §1 |
| MIIM functions | soc_miim_read @ 0x10830b78, soc_miim_write @ 0x1082fabc |
| soc_schan_op | Function at 0x108623e4, schan_msg_capture.txt |
| Retimer init | S20retimer_init.sh, COMPLETE_CHIP_INVENTORY.md |
| CPLD registers | SYSTEM_BOOT_AND_I2C.md §2 |
| LED programs | LED_ARCHITECTURE.md, led0.hex/led1.hex |
| Boot sequence | SYSTEM_BOOT_AND_I2C.md §1 |
| Buffer/QoS | rc.datapath_0, rc.soc |

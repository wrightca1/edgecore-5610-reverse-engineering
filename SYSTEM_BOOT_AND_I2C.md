# AS5610-52X System Boot Sequence, I2C Topology, and CPLD

**Date**: 2026-03-22
**Source**: Live switch Cumulus 2.5 extraction

---

## 1. Complete Boot Sequence

### Phase 1: Kernel Boot (rcS.d)

| Order | Script | Purpose |
|-------|--------|---------|
| S01 | mountkernfs.sh | Mount /proc, /sys |
| S02 | mountdevsubfs.sh | Mount /dev/pts, /dev/shm |
| S03 | bootlogd | Start boot logging |
| S04 | hostname.sh, hwclock.sh | Set hostname, sync clock |
| S05 | checkroot.sh | Check root filesystem |
| S06 | **kmod** | **Load kernel modules from /etc/modules** |
| S06 | rsyslog | Start syslog |
| S08 | **decode-syseeprom** | Read board EEPROM (MAC, serial, model) |
| S08 | aclinit | ACL init |
| S08 | mountall.sh | Mount all filesystems |
| **S09** | **hw_init** | **Platform hardware init (GPIO + retimer)** |
| **S10** | **switchd** | **Start BCM SDK + switchd daemon** |
| S10 | mstpd | STP daemon |
| S11 | networking | Configure network interfaces (/etc/network/interfaces) |
| S12 | arp_refresh | ARP refresh daemon |
| S14 | **lm-sensors** | Hardware monitoring |
| **S15** | **ledmgrd** | **System LED daemon** |
| S15 | **phy_ucode_update** | **PHY microcode update (BCM847xx external PHYs)** |
| S15 | **pwmd** | **Fan PWM control daemon** |
| S15 | **smond** | **Sensor monitoring daemon** |

### Phase 2: Runtime Services (rc2.d)

| Order | Script | Purpose |
|-------|--------|---------|
| S01 | lldpd | LLDP daemon |
| S01 | quagga | Routing suite (BGP, OSPF) |
| S01 | clagd | MLAG daemon |
| S01 | ntp | Time sync |
| S02 | ssh | SSH server |
| S02 | ptmd | Topology verification |
| S03 | monit | Process monitoring |

### Key Dependency Chain

```
kmod (/etc/modules)
  -> linux-kernel-bde (himem=1) + linux-user-bde + tun
  -> accton_as5610_52x_cpld
  -> at24, sff_8436_eeprom, gpio-pca953x
  -> max6697, adm1021 (temperature sensors)
  -> ds100df410 (retimer/equalizer)
        |
hw_init (S09)
  -> S10gpio_init.sh: QSFP GPIO reset/enable (pca9538 at chips 160,168)
  -> S20retimer_init.sh: 32 DS100DF410 equalizers via sysfs
        |
switchd (S10)
  -> Loads BCM SDK (BCM56846 Trident+)
  -> Runs rc.soc: debug flags, attach, init all
  -> Runs rc.ports_0: set port speed config (48x10G + 4x40G)
  -> Runs rc.datapath_0: buffer management, QoS, scheduling, ECMP hash
  -> Runs rc.led: load LED programs, start LED processors
  -> Creates 52 TUN interfaces (swp1-swp52)
  -> Starts linkscan, packet I/O threads
```

---

## 2. CPLD Register Map

**Module**: `accton_as5610_52x_cpld`
**Sysfs**: `/sys/devices/ff705000.localbus/ea000000.cpld/`
**Device Tree**: `/proc/device-tree/localbus@ff705000/cpld@1,0`
**Board**: Model 0, HW Rev 2, CPLD Version 7 (engineering)

### Status Registers (Read-Only)

| Register | Current Value | Description |
|----------|--------------|-------------|
| board_revision | 0.2:7-eng | Model.HW_rev:CPLD_ver |
| psu_pwr1_present | 1 | PSU1 installed |
| psu_pwr1_dc_ok | 1 | PSU1 DC output OK |
| psu_pwr1_all_ok | 1 | PSU1 fully operational |
| psu_pwr2_present | 1 | PSU2 installed |
| psu_pwr2_dc_ok | 0 | PSU2 DC output FAIL |
| psu_pwr2_all_ok | 0 | PSU2 not operational |
| system_fan_present | 1 | Fan tray present |
| system_fan_ok | 1 | Fan running OK |
| system_fan_air_flow | front-to-back | Airflow direction |
| system_dc_power_ok | 0 | System DC power not fully OK (PSU2) |
| system_all_ok | 0 | System not fully OK |

### LED Control (Read-Write)

| Register | Current | Values |
|----------|---------|--------|
| led_psu1 | green | green, yellow, off |
| led_psu2 | yellow | green, yellow, off |
| led_fan | green | green, yellow, off |
| led_diag | yellow | green, yellow, off |
| led_locator | off | amber_blinking, off |

### Fan/Watchdog Control (Read-Write)

| Register | Current | Description |
|----------|---------|-------------|
| pwm1 | 64 | Fan speed (0-248) |
| pwm1_enable | 1 | PWM enabled |
| watch_dog_enable | 0 | HW watchdog disabled |
| watch_dog_timeout | 8 sec | NMI timeout (8-512 seconds) |
| watch_dog_keep_alive | 0 | Write any value to pet watchdog |

---

## 3. I2C Bus Topology

### Physical I2C Controllers

| Controller | Address | Linux Bus |
|-----------|---------|-----------|
| MPC8536 I2C0 | 0xff703000 | i2c-0 |
| MPC8536 I2C1 | 0xff703100 | i2c-1 |

### I2C Mux Tree

```
I2C-0 (0xff703000)
  └── 0x70: PCA9548 (8-ch mux) -> buses 2-9
        ├── ch0 -> bus 2: RTC (PCF8564 @ 0x51)
        ├── ch1 -> bus 3: EEPROM (24c02 @ 0x3a, 0x3e, 0x78)
        ├── ch2 -> bus 4: EEPROM (24c02 @ 0x0c, 0x39, 0x3d, 0x78)
        ├── ch3 -> bus 5: (empty)
        ├── ch4 -> bus 6: (empty)
        ├── ch5 -> bus 7: (empty)
        ├── ch6 -> bus 8: (empty)
        └── ch7 -> bus 9: Temp sensors (MAX1617 @ 0x18, MAX6697 @ 0x4d)

I2C-1 (0xff703100)
  ├── 0x75: PCA9546 (4-ch mux) -> buses 10-13
  │     ├── ch0 -> bus 10: PCA9548 @ 0x74 -> buses 22-29 (SFP+ ports 1-8)
  │     ├── ch1 -> bus 11: PCA9548 @ 0x74 -> buses 30-37 (SFP+ ports 9-16)
  │     ├── ch2 -> bus 12: PCA9548 @ 0x74 -> buses 38-45 (SFP+ ports 17-24)
  │     └── ch3 -> bus 13: PCA9548 @ 0x74 -> buses 46-53 (SFP+ ports 25-32)
  │
  ├── 0x76: PCA9546 (4-ch mux) -> buses 14-17
  │     ├── ch0 -> bus 14: PCA9548 @ 0x74 -> buses 54-61 (SFP+ ports 33-40)
  │     ├── ch1 -> bus 15: PCA9548 @ 0x74 -> buses 62-69 (SFP+ ports 41-48)
  │     ├── ch2 -> bus 16: GPIO expanders (PCA9506 @ 0x20,0x21; PCA9538 @ 0x70-0x73)
  │     └── ch3 -> bus 17: GPIO expanders (PCA9506 @ 0x20,0x23,0x24)
  │
  └── 0x77: PCA9546 (4-ch mux) -> buses 18-21
        ├── ch0 -> bus 18: QSFP1 (sff8436 @ 0x50, DS100DF410 @ 0x27)
        ├── ch1 -> bus 19: QSFP2 (sff8436 @ 0x50, DS100DF410 @ 0x27)
        ├── ch2 -> bus 20: QSFP3 (sff8436 @ 0x50, DS100DF410 @ 0x27)
        └── ch3 -> bus 21: QSFP4 (sff8436 @ 0x50, DS100DF410 @ 0x27)
```

### Per-SFP+ Port I2C Devices (buses 22-69)

Each SFP+ port bus has:
- **0x50**: SFP EEPROM (24c04, 256 bytes, SFF-8472 A0 page)
- **0x51**: SFP diagnostic page (dummy driver placeholder)
- **0x27**: DS100DF410 retimer/equalizer (on buses with retimers: 22-25, 30-33, 38-41, 46-49, 54-57, 62-69)

32 of the 48 SFP+ buses have retimers (8 buses per retimer group, 4 groups of 8). The remaining 16 buses (26-29, 34-37, 42-45, 50-53) have SFP EEPROMs but no retimer.

### QSFP Port I2C Devices (buses 18-21)

Each QSFP port bus has:
- **0x50**: QSFP EEPROM (sff8436 driver, SFF-8436 pages)
- **0x27**: DS100DF410 retimer/equalizer

### GPIO Expanders

| Bus | Address | Chip | Function |
|-----|---------|------|----------|
| 16 | 0x20 | PCA9506 | SFP TX disable (ports 1-40) |
| 16 | 0x21 | PCA9506 | SFP TX disable (ports 41-48) |
| 16 | 0x70 | PCA9538 | QSFP1 control (reset, lpmode, modsel) |
| 16 | 0x71 | PCA9538 | QSFP2 control |
| 16 | 0x72 | PCA9538 | QSFP3 control |
| 16 | 0x73 | PCA9538 | QSFP4 control |
| 17 | 0x20 | PCA9506 | SFP presence detect |
| 17 | 0x23 | PCA9506 | SFP RX LOS |
| 17 | 0x24 | PCA9506 | SFP TX fault |

### SFP EEPROM Data (Sample: swp1, bus 22)

```
Vendor: FINISAR CORP.
Part:   FTLX1475D3BTL-E7A
Serial: A0BAJGQ
Date:   180912
Type:   10GBASE-LR (10km, 1310nm)
```

### QSFP EEPROM Data (Sample: swp49, bus 18)

```
Vendor: CISCO-AVAGO
Part:   AFBR-79EBPZ-CS2
Serial: AVM2148U1ZZ
Date:   171130
Type:   40GBASE-SR4
```

---

## 4. BCM SDK Initialization

### rc.soc Sequence

1. Disable all debug output (`debug -PCi`, etc.)
2. `attach *` -- attach to PCI device
3. `init all` -- full SDK initialization (ASIC reset, SerDes init, table init)
4. `rcload /etc/bcm.d/rc.ports_0` -- configure port speeds
5. `setreg xmac_tx_ctrl 0xc802` -- MAC TX config
6. `s MAC_RSV_MASK MASK=0x18` -- MAC reserved mask
7. `m cmic_misc_control LINK40G_ENABLE=1` -- enable 40G link detection
8. `rcload /var/lib/cumulus/rc.datapath_0` -- buffer/QoS/scheduling
9. `setreg IFP_METER_PARITY_CONTROL 0` -- disable FP meter parity (errata)
10. `rcload /etc/bcm.d/rc.led` -- load and start LED programs

### rc.ports_0 (Port Speed Config)

```
allports = xe0-xe51
40Gports = xe48-xe51   (swp49-52, QSFP)
10Gports = xe0-xe47    (swp1-48, SFP+)
```

### rc.datapath_0 Key Settings

- **Buffer**: 46080 total cells, 4 service pools
- **ECMP Hash**: RTAG7, CRC16-CCITT, bins for src/dst IP, L4 ports, protocol
- **QoS**: 8 CoS queues, weighted scheduling
- **Flow Control**: PFC disabled, pause RX enabled
- **CPU Control**: L3 MTU fail, slow path, L3 dst miss -> CPU

---

## 5. What We Have vs What's Missing

### Complete Coverage

| Subsystem | Status | Source |
|-----------|--------|--------|
| CPLD registers | **COMPLETE** | sysfs dump, all values captured |
| I2C bus topology | **COMPLETE** | All 70 buses, all devices mapped |
| I2C mux tree | **COMPLETE** | PCA9548/9546/9538/9506 hierarchy |
| SFP/QSFP EEPROMs | **COMPLETE** | at24/sff8436 drivers, sample data |
| DS100DF410 retimers | **COMPLETE** | 32 devices, init script, sysfs interface |
| GPIO expanders | **COMPLETE** | TX disable, QSFP reset/lpmode/modsel |
| Temperature sensors | **COMPLETE** | MAX6697 + MAX1617 (ADM1021) |
| Fan control | **COMPLETE** | CPLD PWM (0-248) |
| Watchdog | **COMPLETE** | CPLD HW watchdog (8-512s NMI timeout) |
| Boot sequence | **COMPLETE** | Full rcS.d + rc2.d order |
| BCM SDK init | **COMPLETE** | rc.soc, rc.ports, rc.datapath, rc.led |
| LED programs | **COMPLETE** | CMIC bytecode + ledmgrd Python |
| Module load order | **COMPLETE** | /etc/modules with all drivers |

### Nothing Missing

The system boot and I2C subsystem are fully documented. Every kernel module, init script, platform config file, and hardware device has been captured and mapped.

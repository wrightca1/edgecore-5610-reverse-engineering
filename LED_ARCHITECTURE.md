# AS5610-52X LED Architecture

**Date**: 2026-03-22
**Source**: Live switch Cumulus 2.5 extraction

---

## Overview

The AS5610 has two independent LED subsystems:

1. **CMIC LED Processor** -- Hardware microcontroller inside the BCM56846 ASIC that controls per-port link/activity LEDs
2. **ledmgrd** -- Python daemon that controls system status LEDs (PSU, Fan, System) via CPLD/I2C

---

## 1. CMIC LED Processor (Port LEDs)

### Architecture

The BCM56846 has **2 LED processors** (LED0 and LED1), each running a 256-byte program at 30Hz. These control the front-panel per-port LEDs via a serial shift chain.

```
switchd                CMIC LED Processor          Front Panel
  |                         |                         |
  |-- linkscan task ------> |-- LINKSCAN_P (0x80) --> |
  |   updates per-port      |   reads port status     |-- serial LED chain
  |   link/activity bits    |   runs 256-byte program  |   (shift register)
  |                         |   pushes 2 bits/port     |
  |                         |   sends 64 bits total    |
```

### LED Program Format

Each processor runs a custom bytecode program (BCM LED processor ISA):

| Instruction | Opcode | Description |
|-------------|--------|-------------|
| `ld a, N` | Load immediate into register A (port number) |
| `ld b, N` | Load immediate into register B |
| `port a` | Select port from register A |
| `pushst BIT` | Push port status bit onto stack |
| `pack` | Shift stack bit into output register |
| `call ADDR` | Call subroutine |
| `send N` | Send N bits to LED serial output |
| `tst b, BIT` | Test bit in register B |
| `tor` | Stack OR |
| `tand` | Stack AND |
| `tinv` | Stack invert |
| `push cy` | Push carry flag |
| `push (ADDR)` | Push memory value |
| `ret` | Return |

### Per-Port LED Logic

Each port outputs **2 bits** to the serial chain:
- **Bit 1 (first pushed)**: Amber LED (always 0 = off on AS5610)
- **Bit 2 (second pushed)**: Green LED (link + activity)

Green LED logic:
```
green = LINKEN AND NOT(activity AND blink_state)
```
Where:
- `LINKEN` = port is administratively enabled (PORTSTATUS bit 8)
- `activity` = TX OR RX packet detected (LINKSCAN bits 4,5)
- `blink_state` = toggles every 3 ticks (10Hz blink rate)

Effect: Green LED is solid ON when link is up, blinks OFF briefly during packet activity.

### LED0 vs LED1

| Processor | Ports | Physical LEDs |
|-----------|-------|---------------|
| **LED0** | 32 SFP+ ports (hardware ports 5-36) | swp1-swp32 front panel LEDs |
| **LED1** | 4 QSFP ports + 20 SFP+ ports (hw ports 1-4, 9, 13, 21, 25, 29-36) | swp33-swp52 + QSFP LEDs |

LED1 has extra padding (`pad_n_one`) to align the QSFP LEDs in the serial chain, and QSFP ports use the same LED logic as SFP+ ports.

### Port Number Mapping (LED0)

The LED program loads hardware port numbers in a specific order that maps to the physical LED positions on the front panel:

```
LED0 serial order: 6,5,8,7, 30,31,32,29, 36,35,34,33, 28,27,26,25,
                   23,24,21,22, 16,15,14,13, 10,9,12,11, 19,20,17,18
```

This non-sequential order matches the physical wiring of the LED shift chain on the PCB.

### Loading the LED Program

From `rc.led`:
```
led 0 stop          # stop LED processor 0
led 0 auto on       # enable auto-update of linkscan data
led 0 load /etc/bcm.d/led0.hex   # load 256-byte program
led 0 start         # start running
```

The hex file contains the raw bytecode (256 bytes = 16 lines of 16 bytes).

### CMIC LED Registers

From BAR0 (in the CMIC_LED register space):
- LED program memory: loaded via `led load` BCM shell command
- LED data RAM: 0xa0-0xff (variables, blink state at 0xf0-0xf1)
- Linkscan data: 0x80-0x9f (32 ports x 2 bytes, updated by CPU)

---

## 2. ledmgrd (System Status LEDs)

### Architecture

`ledmgrd` is a Python daemon that monitors system health and controls 4 status LEDs via the CPLD:

| LED | CPLD Register | Monitored By |
|-----|--------------|--------------|
| PSU1 | `led_psu1` | PSU1 presence/status sensor |
| PSU2 | `led_psu2` | PSU2 presence/status sensor |
| Fan | `led_fan` | Fan speed/presence sensor |
| System | `led_diag` | Overall system health |

### CPLD Access Path

```
ledmgrd (Python)
  -> cumulus.sysledcontrol
    -> CPLD sysfs at /sys/devices/ff705000.localbus/ea000000.cpld/
      -> led_psu1, led_psu2, led_fan, led_diag files
```

The CPLD is the Accton AS5610 platform CPLD (`accton_as5610_52x_cpld` kernel module) which provides sysfs attributes for LED control.

### LED States

Each system LED supports (from CPLD register values):
- Off
- Green (normal)
- Amber (warning/fault)
- Blinking (managed by CPLD or software)

### ledmgrd Loop

ledmgrd runs a continuous loop:
1. Read sensor status (temperature, PSU, fan)
2. Determine LED color based on health
3. Write to CPLD sysfs

---

## 3. Custom NOS Implementation

To replicate LED behavior in a custom NOS:

### Port LEDs (CMIC)
1. Load the LED program hex into the CMIC LED processor memory
2. Enable linkscan auto-update
3. Start the LED processor
4. The hardware handles everything autonomously after that

### System LEDs (CPLD)
1. Load `accton_as5610_52x_cpld` kernel module
2. Write to sysfs: `/sys/devices/ff705000.localbus/ea000000.cpld/led_*`
3. Monitor sensors and update LED state in a polling loop

---

## Files

| File | Purpose |
|------|---------|
| `/etc/bcm.d/led0.asm` | LED0 program source (SFP+ ports, 32 LEDs) |
| `/etc/bcm.d/led1.asm` | LED1 program source (QSFP + SFP+, 24+pad LEDs) |
| `/etc/bcm.d/led0.hex` | LED0 compiled bytecode (256 bytes) |
| `/etc/bcm.d/led1.hex` | LED1 compiled bytecode (256 bytes) |
| `/etc/bcm.d/rc.led` | LED init script (load + start) |
| `/usr/sbin/ledmgrd` | System LED daemon (Python) |
| `/usr/lib/python2.7/dist-packages/cumulus/platforms/accton.py` | Platform LED config |
| `/usr/lib/python2.7/dist-packages/cumulus/ledup.py` | LED program generator |
| `/usr/lib/python2.7/dist-packages/cumulus/sysledcontrol.py` | System LED control |

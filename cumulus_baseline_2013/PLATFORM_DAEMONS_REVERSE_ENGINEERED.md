# Platform Daemons — Reverse-Engineered from Cumulus 2.5.0 Python sources

The daemons that control fans, sensors, LEDs, and PSUs on AS5610-52X under
Cumulus are all Python scripts — no decompilation needed. The full source is
captured in `platform-daemons/` alongside the dependent `cumulus/` library.

## The three platform daemons

| Daemon | PID | Pidfile | Role | Polls |
|---|---|---|---|---|
| `pwmd`    | `/usr/sbin/pwmd`    | `/var/run/pwmd.pid`    | Calculate fan PWM from temp sensors and write to CPLD | every 30s (override `-i`) |
| `smond`   | `/usr/sbin/smond`   | `/var/run/smond.pid`   | Read sensors, cache state to `/var/cache/cumulus/unit_state/`, drive status LEDs | every 10s (override `-i`) |
| `ledmgrd` | `/usr/sbin/ledmgrd` | `/var/run/ledmgrd.pid` | Compile the BCM CMIC LED uController bytecode and download it to the ASIC | event-driven |

All three are started as init.d services and supervised by `monit`. monitrc
files are in `platform-daemons/etc/monit/monitrc.d/`.

## How they auto-detect the platform

```python
p = os.popen('platform-detect -m').read().strip()  # "accton,as5610_52x"
r = os.popen('platform-detect -r').read().strip()  # board revision
platform = cumulus.platformdb.lookup(p, r)         # → AcctonAS5610_52X class
```

The platform DB (`cumulus.platformdb`) returns a class with `.cpld`,
`.switch`, `.sensors`, `.pwms`, `.statusleds` attributes. The AS5610-52X
class is defined at `cumulus/platforms/accton.py:1245`.

## Fan-control algorithm (the answer to "what's PWMing the fans")

**`pwmd` runs this every 30s** (`cumulus/sensors.py:943` `PWM_Unit`):

```python
def calc_speed(self, fan):
    speed = fan.minpwm                              # start at 64
    for each temp sensor t in self.temps:
        T = read t/temp*_input
        if T < t.temp_max_hyst:
            tmp = fan.minpwm                        # below hysteresis → min
        elif T > t.temp_max:
            tmp = fan.maxpwm                        # above max → 255
        else:
            tmp = minpwm + (T - hyst) * (maxpwm - minpwm) // (max - hyst)
        speed = max(speed, tmp)                     # take MAX across sensors
    return speed

def run_state(self):
    self.update_temps()
    for fan in self.fans:
        self.set_speed(fan, self.calc_speed(fan))   # writes pwm1
```

**Defaults** (`cumulus/sensors.py:386` `Fan_Unit`):

```
fan_max = 29000 rpm     fan_min = 2500 rpm    fan_var = 15%
minpwm = 64             maxpwm = 255          rpmmode = 0 (PWM, not RPM)
```

**AS5610-52X temperature thresholds** (`accton.py:1120-1176`):

| Sensor | Linux hwmon path | hyst | max | crit |
|---|---|---|---|---|
| Temp1 — ASIC die           | `/sys/devices/pci0000:00/0000:00:00.0/0000:01:00.0/hwmon/*/temp1_input` | 65 | 100 | 105 |
| Temp2-Temp8 — board (×7)   | `i2c-9 0x4d (max6697) hwmon temp{1..7}` | 55 | 75 | 85 |
| Temp9 — NE1617A CPU local  | `i2c-9 0x18 (max1617) hwmon temp1` | 55 | 75 | 85 |
| Temp10 — MAC board sensor  | `i2c-9 0x18 (max1617) hwmon temp2` | 65 | 80 | 90 |

PWM duty-cycle output is written to:
`/sys/devices/ff705000.localbus/ea000000.cpld/pwm1`
(set `pwm1_enable=1` first; range is 0–255).

**Verification from live system (idle):**

```
Temp1=42°C  → 42 < 65 (hyst), tmp = 64
Temp2..8 = 25-31°C  → all < 55 (hyst), tmp = 64
Temp9=22°C  → 22 < 55, tmp = 64
Temp10=54°C → 54 < 65 (hyst), tmp = 64
→ max = 64 → pwm1 = 64    ✓ matches live value
```

The system runs at minimum PWM because nothing has crossed its hysteresis
threshold. When any one sensor crosses its hyst, the fan ramps linearly to
maxpwm at the max threshold; if any sensor reaches max, fans go full-on
regardless of others.

## CPLD register map (sysfs attrs at `/sys/devices/ff705000.localbus/ea000000.cpld/`)

Read live from a working system:

| Attr | Value | What it is |
|---|---|---|
| `board_revision` | `0.2:7-eng` | model.HW_rev:cpld_version |
| `led_diag` | `yellow` | System diag LED (yellow = degraded, not "good") |
| `led_fan` | `green` | Fan tray status LED |
| `led_locator` | `off` | Identify/locator LED (front-panel) |
| `led_psu1` | `green` | PSU1 status LED |
| `led_psu2` | `yellow` | PSU2 status LED — degraded |
| `psu_pwr1_all_ok` | `1` | PSU1 is healthy overall |
| `psu_pwr1_dc_ok` | `1` | PSU1 DC output good |
| `psu_pwr1_present` | `1` | PSU1 physically present |
| `psu_pwr2_all_ok` | `0` | PSU2 not OK — **slot is empty** (no PSU plugged in) |
| `psu_pwr2_dc_ok` | `0` | No DC output — no PSU in slot 2 |
| `psu_pwr2_present` | `1` | Slot 2 detectable, but the CPLD reports the slot itself, not the PSU. With nothing in the slot, `all_ok`/`dc_ok` go to 0 |
| `pwm1` | `64` | Fan PWM duty cycle (0–255) |
| `pwm1_enable` | `1` | PWM control enabled |
| `system_all_ok` | `0` | **System overall NOT OK** (because PSU2 failed) |
| `system_dc_power_ok` | `0` | Only one PSU rail up |
| `system_fan_ok` | `1` | Fan tray OK |
| `system_fan_present` | `1` | Fan tray present |
| `system_fan_air_flow` | `front-to-back` | Cooling direction |
| `watch_dog_enable` | `0` | Hardware watchdog disabled |
| `watch_dog_keep_alive` | `0` | (kick the dog) |
| `watch_dog_timeout` | `8 seconds to NMI` | Watchdog period |

**Important note on PSU2 status:** the AS5610 has dual hot-swap PSUs. On
this chassis **PSU2 slot is empty** — no PSU plugged in. System runs on
PSU1 only. Not redundant, but expected for lab.

The `psu_pwr2_present=1 / dc_ok=0` pattern is a useful interpretation hint
for EdgeNOS: the CPLD's "present" bit reports the slot (always 1 here),
while `dc_ok=0` is the real "no power" signal. The system-LED daemon sees
this as BAD/ABSENT and drives `led_psu2 = yellow`.

The kernel module exposing these attrs is `accton_as5610_52x_cpld.ko`
(version 1.0, author Puneet Shenoy at Cumulus). The CPLD itself is
memory-mapped on the local bus at physical address `0xea000000` and
attached to the `ff705000.localbus` controller.

## Port table — front-panel port → BCM SerDes → LED bytecode address

From `accton.py:1056-1110`. **This is the master mapping for the AS5610-52X**:

| Cumulus port | BCM serdes | LED bank | LED bytecode addr | Notes |
|---|---|---|---|---|
| swp1  | 64 | 1 | 34 | SFP+ |
| swp2  | 65 | 1 | 32 | SFP+ |
| swp3  | 66 | 1 | 38 | SFP+ |
| swp4  | 67 | 1 | 36 | SFP+ |
| swp5  | 68 | 1 | 62 | SFP+ |
| swp6  | 69 | 1 | 60 | SFP+ |
| swp7  | 70 | 1 | 58 | SFP+ |
| swp8  | 71 | 1 | 56 | SFP+ |
| swp9..40 | 4..35 | 0 | varies | SFP+ |
| swp41..48 | 36..43 | 1 | varies | SFP+ |
| swp49 | (48,49,50,51) | 1 | 26 | QSFP+ — 4 lanes |
| swp50 | (44,45,46,47) | 1 | 24 | QSFP+ — 4 lanes |
| swp51 | (60,61,62,63) | 1 | 30 | QSFP+ — 4 lanes |
| swp52 | (56,57,58,59) | 1 | 28 | QSFP+ — 4 lanes |

Full table in `platform-config-accton-as5610_52x/etc/bcm.d/config.d/01config.bcm`
and `accton.py:1049-1110`.

## LED bytecode (CMIC LED uController assembly)

Each port class in `accton.py` defines a `_set_led` string containing
**LED-uController assembly** that's compiled by `ledmgrd` and downloaded
into the BCM ASIC's CMIC LED unit. This runs autonomously inside the chip
and updates the LEDs without CPU involvement.

For AS5610-52X SFP+ ports (from accton.py around line 980-1042):

```asm
;;; AcctonAS5610_52XSFPp
;;; 1st bit pushed - amber (we always push 0 -> amber off)
;;; 2nd bit pushed - green
set_led:
        port 1
        pushst  PORTSTATUS_ZERO  ; amber off
        pack
        port    a
        ld      b,LINKSCAN_P
        add     b,a
        ld      b,(b)
        tst     b,LINKSCAN_TX
        push    cy
        tst     b,LINKSCAN_RX
        push    cy
        tor                       ; TX OR RX
        push    (BLINK_STATE_P)
        tand
        tinv                      ; flash off with activity
        pushst  PORTSTATUS_LINKEN
        tand
        pack
        ret
```

The QSFP variant + 4×10G break-out variant are different programs.

We already have the equivalent for EdgeNOS in `LED_CPU_INTERFACE.md` and
`newnos/utils/leddance/passthrough.asm`. This Cumulus source confirms our
disassembly is correct.

## LED management at system level — `ledmgrd` + `cumulus/ledup.py`

`ledmgrd` is event-driven (not poll-based). On port-state changes or after
ASIC init, it:

1. Compiles the port-specific `_set_led` bytecode using `cumulus.ledup`.
2. Builds a dispatch table mapping logical port → bytecode entry.
3. Downloads the bytecode + dispatch table into the ASIC's LED uController
   memory via the CMIC LED data path (we already reverse-engineered this in
   `LED_CPU_INTERFACE.md`).
4. Starts the uController, which then handles all link-state→LED updates
   autonomously.

## Status-LED management — `smond` + `cumulus/sysledcontrol.py`

`smond` runs every 10 seconds and:

1. Reads every sensor unit (Temp1-10, PSU1, PSU2, Fan).
2. Computes each one's `state` (UNKNOWN / ABSENT / BAD / OK).
3. Writes the state to `/var/cache/cumulus/unit_state/<name>/state`.
4. Drives the 4 status LEDs (`led_psu1`, `led_psu2`, `led_fan`, `led_diag`)
   by reading the unit-state cache and computing the right color for each
   indicator. Logic in `cumulus.sensors.StatusLED_Unit`.

The mapping (from `accton.py:1184-1202`):

| Cumulus class | LED location attr | Driven by sensors |
|---|---|---|
| `AcctonAS5610_52xPSU1LED` | `led_psu1` | PSU1 unit state |
| `AcctonAS5610_52xPSU2LED` | `led_psu2` | PSU2 unit state |
| `AcctonAS5610_52xFanLED`  | `led_fan`  | Fan unit state |
| `AcctonAS5610_52xSystemLED` | `led_diag` | aggregate of all sensors |

## What EdgeNOS needs to replicate

1. **A CPLD driver** exposing `pwm1`, `pwm1_enable`, `psu_pwr{1,2}_*`,
   `system_fan_*`, `led_*`, `watch_dog_*` via sysfs (or equivalent).
   Stock Cumulus driver is `accton_as5610_52x_cpld.ko` — we have its module
   metadata (Puneet Shenoy / Cumulus 2013) but not its source. Reasonable
   path is to write our own from scratch — the register layout can be
   reverse-engineered from how the Python daemons access it. **The CPLD
   wraps at 32 bytes** per `feedback_cpld_addr_wrap.md`, so this is a small
   driver.
2. **`pwmd`-equivalent fan controller** that runs the linear-interpolation
   algorithm above. Trivial to port — it's 30 lines of arithmetic.
3. **`smond`-equivalent sensor monitor** to drive the status LEDs.
4. **LED uController bytecode loader** — we already have the recipe in
   `LED_CPU_INTERFACE.md`. Cumulus's source confirms the assembly syntax.
5. **A hardware watchdog kicker** if we want to enable
   `watch_dog_enable=1`. Currently disabled in this build.

## Other interesting findings

* The `auditd` daemon is running — this build has Linux audit subsystem
  enabled. Probably for compliance/security logging. EdgeNOS may not need it.
* `clagd` (Cumulus Link Aggregation / MLAG daemon) is running but no peer
  is configured.
* `portwd` (port watchdog, 46KB Python script) is running — watches for
  flapping links and disables them. We grabbed the source; worth a future
  read.
* `ztp-usb` is running — looks for a USB key with a ZTP script on boot.
  No-op for our setup.
* The hardware watchdog has an 8-second timeout-to-NMI; `watch_dog_enable=0`
  means it's currently disabled.

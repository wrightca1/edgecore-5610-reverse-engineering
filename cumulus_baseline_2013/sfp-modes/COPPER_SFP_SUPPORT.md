# 1000BASE-T vs 10GBASE-T SFP Modules — What Actually Works

The user's question: can the AS5610-52X SFP+ cages use **1000BASE-T**
(1G copper RJ45 SFP) or **10GBASE-T** (10G copper RJ45 SFP+) modules?

The answers are different. Both are "copper SFPs," but they use
fundamentally different host-side interfaces, power budgets, and
software configurations.

## Quick answer

| Module | Host-side electrical | Cumulus 2.5.0 | EdgeNOS path | Power class |
|---|---|---|---|---|
| **1000BASE-T SFP** (1G copper RJ45) | SGMII or 1000BASE-X (1.25 GBaud) | ❌ no SGMII mode in port class | add `'1G':1` + SGMII serdes config | Class 1 (~0.5 W) ✅ |
| **10GBASE-T SFP+** (10G copper RJ45) | XFI (10.3 Gbps, same as fiber 10G) | ⚠️ link layer matches, BUT cage power may be insufficient | check cage power class budget | Class 3/4 (2-2.5 W) ⚠️ |

## 1000BASE-T (1G copper RJ45 SFP)

### How the module works internally

```
       Cat5e/Cat6 RJ45
              │
              ▼
       ┌─────────────┐
       │  1000BASE-T │   ← Marvell 88E1111 / Broadcom BCM5461
       │   PHY chip  │      or similar
       └──────┬──────┘
              │ SGMII (1.25 GBaud SerDes)
              ▼ + MDIO over I²C (0x56)
       SFP electrical pins → cage → host
```

The module presents a 1.25 GBaud SerDes signal to the cage. The host
must run its SerDes in **SGMII or 1000BASE-X** mode (8B/10B encoding,
1.25 GBaud), NOT in the default **XFI** mode (10.3 GBaud, 64B/66B).

The 1G PHY inside the SFP is configured by the host via MDIO. SFP
modules tunnel MDIO over the I²C management interface (typically
address 0x56 on the SFP A2 page).

### Hardware capability on AS5610-52X

* **BCM56846 Warpcore SerDes:** ✅ supports SGMII at 1.25 GBaud. Mode
  is selected via `bcm_port_speed_set(unit, port, 1000)` which
  reconfigures the SerDes from XFI to SGMII.
* **DS100DF410 retimer:** datasheet says 1.0–11.3 Gbps coverage. 1.25
  GBaud falls in range. The retimer's adaptive EQ should converge
  acceptably; if not, `tap_dem` and `drv_sel_vod` may need different
  values for 1G (currently tuned for 10G).
* **SFP+ cage:** electrically identical to a standard SFP cage —
  accepts both 1G and 10G modules. Power needed by 1000BASE-T SFP is
  ~0.5 W which is well within the SFP+ Class 1 budget.

### Software state (Cumulus 2.5.0)

❌ **NOT supported.** From `cumulus/platform.py`:

```python
class Trident10GPort(TridentPort):
    modes = ('10G', '40G/4')        # no '1G'
    _speed_map = {'10G': 10, '40G/4': 40}
```

The Trident10GPort class has no 1G mode. ports.conf rejects `1=1G`.
switchd won't reconfigure the SerDes for SGMII.

Even more: Cumulus's SFF-8472 EEPROM parser at `sff8472.py` only
recognizes optical 10G compliance codes (Base-SR/LR/LRM/ER). It
doesn't have a parser entry for `1000BASE-T` at byte 6 bit 3 either,
though that's a display issue, not a function issue.

### EdgeNOS path to 1000BASE-T SFP support

```python
class Trident10GPort(TridentPort):
    modes = ('10G', '40G/4', '1G')
    _speed_map = {'10G': 10, '40G/4': 40, '1G': 1}

    def serdes_if_type(self, speed):
        # current: returns 'XFI' always for SFP+ class
        return {1: 'SGMII', 10: 'XFI', 40: 'XLAUI'}[speed]
```

Plus in the bring-up path, after detecting `compliance_byte_6_bit_3 = 1`:
1. Call `bcm_port_speed_set(unit, xeN, 1000)` to switch SerDes to SGMII
2. Apply different retimer settings for 1G (test `tap_dem=20`, `drv_sel_vod=128`)
3. Open MDIO-over-I²C tunnel (SFP A2 page 0x56) to access internal 1G PHY
4. Configure that PHY for desired AN advertisement (1G full-duplex)
5. Wait for link up

EdgeNOS doesn't need a port-internal PHY driver — the 1000BASE-T SFP's
own PHY handles the IEEE 802.3 PHY layer. The host just needs to set
the SerDes correctly.

## 10GBASE-T (10G copper RJ45 SFP+)

### How the module works internally

```
       Cat6a/Cat7 RJ45
              │
              ▼
       ┌─────────────┐
       │ 10GBASE-T   │   ← Aquantia AQR105 / Marvell 88X3310 /
       │  PHY chip   │      Inphi CS4223 / similar
       │ (2-3W TDP)  │
       └──────┬──────┘
              │ XFI (10.3 Gbps SerDes) — same as fiber
              ▼ + MDIO over I²C
       SFP+ electrical pins → cage → host
```

The module presents a standard XFI signal — exactly the same electrical
interface as a 10G-LR / 10G-SR optical module. The host doesn't need to
do anything special on the SerDes side; it's already in 10G XFI mode.

### Hardware capability on AS5610-52X

* **BCM port:** ✅ already in 10G XFI mode by default. No reconfiguration.
* **DS100DF410 retimer:** ✅ 10G — exactly what it's designed for. Same
  settings as for 10G fiber.
* **BCM SDK:** ✅ explicitly supports "copper sfp" — captured live from
  `bcmcmd ver`:

  ```
  ...
  BCM84318, BCM84328, BCM84793, BCM82328,
  copper sfp            ← yes, in the supported-PHY list
  ```

* **SFP+ cage power:** ⚠️ **this is the limiting factor.** Standard
  SFP+ cages on Trident+ era hardware deliver **1.0 W (Class 1)** or
  **1.5 W (Class 2)** per port. Most 10GBASE-T SFP+ modules are
  **Class 3 (2.0 W)** or **Class 4 (2.5 W)**.

  AS5610-52X cage power class is not directly documented in our
  captures, but typical Accton/Edgecore boards from 2014-2015 deliver
  Class 2 (1.5 W). Recent 10GBASE-T SFP+ modules from Aquantia have
  worked down to Class 2 — some early ones do not.

  Symptoms of insufficient power:
  * Module repeatedly resets (TX/RX flap pattern)
  * Module's internal PHY fails to initialize
  * RX_LOS asserts even though copper cable is good
  * Module overheats and shuts down

### Software state (Cumulus 2.5.0)

⚠️ **Partially supported.** The port is already in 10G XFI mode so
electrically it's transparent. But:

* Cumulus's SFF-8472 parser (`sff8472.py`) doesn't have a "10GBASE-T"
  compliance code entry. So `cl-sfputil` will show "Unknown" for the
  module type. This is cosmetic — the link still works.
* Cumulus has no awareness of power class — switchd doesn't enforce
  or honor the Extended Identifier byte. It just enables the cage
  power and hopes for the best.
* No CPLD GPIO seen for per-port power-class control on AS5610.
* Auto-negotiation on the host SerDes is OFF (per our Cumulus capture);
  the 10GBASE-T module's PHY does its own AN with the copper peer
  independently. As long as the host XFI is solid at 10.3 Gbps,
  everything works.

### What you'd see if you plugged one in

* `ethtool -m swpN` would read the EEPROM and show vendor name +
  serial, but `TransceiverCodes` would be empty or unrecognized.
* The module's TX/RX power would NOT report — there are no lasers.
  Instead, the EEPROM might report copper-cable diagnostics (cable
  length, signal-to-noise) on some 10GBASE-T modules. Cumulus 2.5.0
  doesn't parse that anyway.
* Link comes up at 10G full duplex.
* Latency is ~2-3 µs higher than fiber (10GBASE-T encoding overhead).
* Power draw on the chassis goes up by ~2 W per port.

### Risk areas to test before relying on it

1. **Power budget:** plug one in and monitor `psu_pwr1_dc_ok` /
   `system_all_ok` in the CPLD. If a 10GBASE-T module starts and
   PSU output drops, the cage isn't delivering enough current.
2. **Temperature:** with 2-3 W of additional heat per port, fan speeds
   should ramp. Watch `pwm1` in the CPLD — if it climbs from 64 toward
   248, that's expected. If a temp sensor exceeds `temp_max` while at
   max PWM, you need more airflow.
3. **EMI:** 10GBASE-T over Cat6a will EMI-radiate within the chassis.
   Usually fine but worth verifying nothing else flakes when active.

## Summary

* **1000BASE-T SFP** — hardware-capable, requires Cumulus/EdgeNOS to add
  1G/SGMII mode. Power: not a problem.
* **10GBASE-T SFP+** — electrically transparent (port already 10G XFI).
  Should work with Cumulus 2.5.0 except for cosmetic EEPROM display.
  **Real risk is SFP+ cage power class** — check the module's required
  power class against AS5610 cage spec before deploying.

For EdgeNOS:
* Add 1G mode to Trident10GPort (~30 LoC).
* Add power-class awareness when reading EEPROM byte 7 so we can fail
  cleanly on Class 3/4 modules if the cage can't deliver.
* Add the 10GBASE-T compliance code (offset 36 / byte 0x24 per
  SFF-8472 rev 12+) to the parser for display purposes.

## Captured evidence

* `platform.py` lines 541-614 — `Trident10GPort` definition
* `sff8472.py` `transceiver_codes` — compliance code bit map
* `bcmcmd ver` output — confirms "copper sfp" in BCM SDK supported list
* `accton.py` `_set_led` strings — LED bytecode is the same for any SFP+
  type (link status logic doesn't care about copper vs fiber)

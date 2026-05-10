# Gap Analysis — what EdgeNOS is missing vs. Cumulus 2.5.0

After a full deep-dive of the live Cumulus install, here is the
side-by-side of what EdgeNOS has done vs. what Cumulus does that we still
need.

## ✅ Already done in EdgeNOS

| Area | Cumulus's approach | EdgeNOS status |
|---|---|---|
| BCM SDK init | `init all` macro in `rc.soc` | ✅ Via OpenMDK init path |
| DMA / CMICm | xgsd_dma path | ✅ Migrated from xgs → xgsd (project_dma_debug_progress) |
| PAXB sub-window | sub-window 7 remap | ✅ Custom BDE fix in place (project_subwindow_fix) |
| Retimer CDR reset | `cdr_rst: 28 → 16` | ✅ Breakthrough applied (project_cdr_reset_breakthrough) |
| LED bytecode | CMIC LED uController | ✅ leddance + passthrough.asm working |
| Custom BDE | PCI config-space writes for iProc | ✅ feedback_cumulus_bde_pci_config |

## ❌ Missing in EdgeNOS — found in this baseline

| Item | Cumulus source | Why it matters |
|---|---|---|
| **CPLD driver with sysfs** | `accton_as5610_52x_cpld.ko` | Exposes `pwm1`, `psu_pwr*`, `system_*`, `led_*`, `watch_dog_*`. Without this, fans cannot be PWMed and PSU/fan health is invisible. |
| **`pwmd`-equivalent fan controller** | `/usr/sbin/pwmd` (Python, source captured) | Linear-interp PWM from 10 temp sensors, polls every 30s. Without it, fans run at firmware-default speed (or stuck full-on / off). |
| **`smond`-equivalent sensor daemon** | `/usr/sbin/smond` (Python, source captured) | Polls sensors every 10s, caches state, drives the 4 system status LEDs. |
| **`ledmgrd` LED bytecode loader** | `/usr/sbin/ledmgrd` (Python, source captured) | Compiles per-port `_set_led` bytecode (LED uController assembly in Python source) and downloads to BCM CMIC LED RAM. We have leddance for testing but the production loader is missing. |
| **`portwd` port-flap watchdog** | `/usr/sbin/portwd` (46KB Python, source captured) | Watches for excessive link flaps and shuts the port down. Not strictly required but adds robustness. |
| **Default control-plane ACL rules** | `/etc/cumulus/acl/policy.d/00control_plane.rules` (captured) | Rate-limits OSPF/BGP/CLAG/ICMP/DHCP/IGMP/BFD/IPv6 ND etc. Without these, a misbehaving neighbour can DoS the CPU. |
| **`hw_init` boot sequencer** | `/etc/init.d/hw_init` (captured) | Calls `S10gpio_init.sh` (QSFP LPMode) then `S20retimer_init.sh` (cdr_rst sequence). EdgeNOS does both ad-hoc; needs to be a real init service. |
| **monit supervision** | `/etc/monit/monitrc.d/*-monit.rc` | Restarts pwmd/smond/ledmgrd/switchd if they crash. Without supervision, a crash leaves fans uncontrolled. |
| **`update-ports` auto-generator** | `/usr/lib/cumulus/update-ports` | Reads `ports.conf` and generates `phytab`, `porttab`, `sfptab`, `rc.datapath_0` in `/var/lib/cumulus/`. EdgeNOS hardcodes these. |
| **U-Boot 2-slot OS image scheme** | `slot_state1/2`, `cl.ver1/2` in fw_env | Cumulus boots from one of two slots; if image is bad, fallback. EdgeNOS uses a single image — would benefit from this. |

## 📁 Files now captured in this directory for porting

```
cumulus_baseline_2013/
├── PROVEN_WORKING_CONFIG.md            ← Operational recipe
├── PLATFORM_DAEMONS_REVERSE_ENGINEERED.md  ← Fan/LED/sensor algorithms
├── GAP_ANALYSIS.md                     ← This document
├── README.md                           ← Hardware + reproduction guide
│
├── platform-config-accton-as5610_52x/  ← The Cumulus platform definition
│   ├── etc/modules                     ← Kernel modules to load
│   ├── etc/bcm.d/rc.soc                ← BCM init script
│   ├── etc/bcm.d/config.d/01config.bcm ← Port mapping
│   ├── etc/bcm.d/backend_map           ← Backend selection
│   ├── etc/sensors.d/as5610_52x.conf   ← Temp thresholds
│   ├── etc/cumulus/ports.conf          ← 48×10G + 4×40G
│   ├── etc/default/phy_ucode_update    ← Warpcore firmware update settings
│   ├── hw_init.d/S10gpio_init.sh       ← QSFP LPMode/ModSel/ResetL GPIO recipe
│   ├── hw_init.d/S20retimer_init.sh    ← cdr_rst 28→16 + tap_dem recipe
│   └── bin/{eeprom.py, sfputil.py}     ← Platform helpers
│
├── platform-daemons/                   ← The Python daemons + Cumulus lib
│   ├── pwmd                            ← Fan PWM controller
│   ├── smond                           ← Sensor monitor + status LEDs
│   ├── ledmgrd                         ← LED bytecode loader
│   ├── portwd                          ← Port flap watchdog
│   ├── etc/init.d/{pwmd,smond,ledmgrd,portwd,hw_init}
│   ├── etc/monit/monitrc.d/*-monit.rc  ← Supervision configs
│   └── usr/lib/python2.7/dist-packages/cumulus/  ← The platform abstraction lib
│       ├── cpld.py                     ← CPLD sysfs wrapper class
│       ├── sensors.py                  ← PWM_Unit, Temp_Unit, Fan_Unit, PSU_Unit, StatusLED_Unit
│       ├── ledup.py                    ← LED bytecode compiler
│       ├── platform.py / platformdb.py ← Platform abstraction
│       ├── platforms/accton.py         ← AS5610-52X port/sensor/LED table
│       └── (sfp.py, sff8472.py, etc.)
│
├── switchd-generated-state/            ← Auto-generated by update-ports
│   ├── porttab     ← swp1→xe0, swp2→xe1, ... (52 entries)
│   ├── phytab      ← PHY-by-MII-addr table (empty here — xe PHYs are in-chip)
│   ├── sfptab      ← swp1→/sys/class/eeprom_dev/eeprom7/... (per-port EEPROM path)
│   └── rc.datapath_0  ← 18KB switchd-generated BCM config (port modes, table sizes, etc.)
│
├── acl-default-rules/                  ← Cumulus default control-plane protection
│   ├── all_rules.txt                   ← iptables -L output (live)
│   └── etc-cumulus-acl/
│       ├── 00control_plane.rules       ← OSPF/BGP/CLAG/ICMP/DHCP/IGMP/etc rate limits
│       └── 99control_plane_catch_all.rules
│
├── cumulus_p2020/                      ← P2020 CPU platform-config
│
├── 30_full_dump.txt                    ← First comprehensive dump (1163 lines)
├── 50_phase2_dump.txt                  ← Phase 2 deep dump (1764 lines)
├── 70_retimer_full.txt                 ← All 32 retimer sysfs states
├── 95_l3_ping_test.txt                 ← Proof ping works to Nexus
├── 97_qsfp_loopback_test.txt           ← Proof QSFP loop works (xe48 TX = xe49 RX)
├── 100_port_speed_fec.txt              ← ethtool/speed/FEC/AN for linked ports
├── 110_platform_monitoring.txt         ← lm-sensors, hwmon
├── 120_stable_identifiers.txt          ← Retimer labels + GPIO chip labels
├── 121_i2c_topology.txt                ← Full I2C mux tree
├── 130_fan_hunt.txt                    ← Where the fan controller lives
├── 132_platform_daemons.txt            ← pwmd/smond/ledmgrd process list
├── 133_cpld_full_dump.txt              ← Every CPLD sysfs attr value
├── 200_deep_dive.txt                   ← Everything else (1221 lines)
└── 210_misc_state.txt                  ← Flash/U-Boot/MII/BCM SDK version
```

## 🎯 Concrete next steps for EdgeNOS

In rough priority order:

1. **Port the CPLD driver.** Reverse-engineer the register layout by tracing
   reads/writes that the Cumulus driver does (mmap of `0xea000000`). The
   CPLD wraps at 32 bytes (per `feedback_cpld_addr_wrap.md`) so the register
   space is tiny.
2. **Add the `hw_init` boot sequence.** Wire up GPIO init + retimer init at
   system startup, not on-demand.
3. **Port pwmd.** It's ~30 lines of arithmetic; trivial port. Use the
   exact temp-sensor thresholds from `accton.py`.
4. **Port smond.** Also small. The valuable part is the status-LED state
   machine and the unit-state cache convention.
5. **Apply default ACL rules.** Copy `00control_plane.rules` into EdgeNOS
   and add a `cl-acltool`-equivalent that translates these into iptables
   + BCM TCAM rules.
6. **Add monit supervision.** Use stock monit with the captured monitrc.d/
   files.
7. **Build the 2-slot U-Boot scheme.** Adapt the captured fw_env-based
   `bootorder1..5` strategy for resilience.

## Bonus context: BCM SDK version live

```
SDK release: sdk-6.3.8 built 20150108 (Thu Jan  8 19:42:14 2015)
Build host: build@monster-07.cumulusnetworks.com
Chips supported: BCM56340/56634/56640/56840/56850 + many PHY families
ASIC instance: BCM56840 (Trident+)
```

The OpenMDK that EdgeNOS uses is also derived from a similar generation
of the Broadcom SDK, so the rc.soc and `01config.bcm` files from this
capture should be directly applicable (modulo path differences).

## What I have NOT yet captured / still unknowns

* **Cumulus's portwd algorithm** — got the 46KB source, haven't read it.
  If we have repeated port flaps in EdgeNOS this is worth a read.
* **`/usr/lib/cumulus/update-ports`** — the script that generates the
  switchd-state files from `ports.conf`. Worth capturing if we want to
  support runtime port-mode changes.
* **Bytecode of the *currently-running* LED uController** — we have the
  Python *source* of the bytecode, but not the compiled assembly bytes
  that are currently sitting in CMIC LED RAM. Capturable via `bcmcmd led
  show` once we know the right command.
* **switchd binary internals** — switchd is a 14MB closed binary. The
  Python platform-config tells us *what* it talks to, but not *how* its
  port-state machine is structured. EdgeNOS doesn't need to copy this —
  we have OpenMDK — but for trace comparison it'd help.
* **`accton_as5610_52x_cpld.ko` source** — driver is binary-only.
  Reverse-engineerable, but small. Would unlock writing the EdgeNOS
  equivalent without trial-and-error.

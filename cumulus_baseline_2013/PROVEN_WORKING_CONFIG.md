# AS5610-52X — Proven-Working Cumulus 2.5.0 Configuration

**This config is verified working.** Ping replies received, BCM counters
incremented for the right packet types, and QSFP loopback traffic confirmed
at the BCM chip level. The "other side" is correctly configured — the bring-up
recipe in this document is the complete, replicable answer for what
EdgeNOS must reproduce.

## Tested topology

```
 Cumulus AS5610-52X (10.1.1.212, 80:a2:35:81:ca:ae)
 │
 ├── swp1 ─── 10G XFI ─── Cisco Nexus  (swp1 = 10.101.101.1/29, peer 10.101.101.2)
 ├── swp2 ─── 10G XFI ─── Cisco Nexus  (swp2 = 10.101.101.10/29, peer 10.101.101.9)
 ├── swp49 ── 40G KR4 ─┐
 │                     │  (QSFP-to-QSFP DAC/optical loopback - same chassis)
 └── swp50 ── 40G KR4 ─┘
 ```

Nexus peer chassis-id `6c:b2:ae:cd:13:33` (same MAC on both swp1 and swp2 — same router).
QSFP modules: Cisco-Avago `AFBR-79EBPZ-CS2` (40G SR-BD, 850nm VCSEL, vendor PN 0x17:6a).

## Verified end-to-end traffic

### L3 ping (swp1 → Nexus)

```
$ ping -c 4 -I swp1 10.101.101.2
PING 10.101.101.2 ... from 10.101.101.1 swp1:
64 bytes from 10.101.101.2: icmp_req=2 ttl=255 time=0.733 ms
64 bytes from 10.101.101.2: icmp_req=3 ttl=255 time=0.739 ms
64 bytes from 10.101.101.2: icmp_req=4 ttl=255 time=0.642 ms
3 received, 25% packet loss   (first packet lost to ARP)
```

### L3 ping (swp2 → Nexus)

```
$ ping -c 4 -I swp2 10.101.101.9
64 bytes from 10.101.101.9: icmp_req=2 ttl=255 time=0.823 ms
...
3 received, 25% packet loss
```

### QSFP loopback (xe48 ↔ xe49 — physical cable)

```
xe48: TPKT=5 (TBYT=433), TBCA=3   ← we transmit broadcast ARP
xe49: RPKT=5 (RBYT=433), RBCA=3   ← same byte count received

  xe48 TBYT = xe49 RBYT = 433 bytes → identical → physical loop verified
```

### ARP resolution

```
10.101.101.2 dev swp1 lladdr 6c:b2:ae:cd:13:33 REACHABLE
10.101.101.9 dev swp2 lladdr 6c:b2:ae:cd:13:33 REACHABLE
```

## Step-by-step bring-up (what EdgeNOS must do)

### 1. Kernel modules (load in this order)

From `/etc/modules` of accton_as5610_52x platform-config:

```
loop
linux-kernel-bde himem=1
linux-user-bde
tun
linux-bde-tmon

accton_as5610_52x_cpld         # platform CPLD
at24                           # 24c04 EEPROM (SFP+)
sff_8436_eeprom                # QSFP EEPROM

gpio-pca953x                   # GPIO expander (QSFP LPMode/ModSel/ResetL)

max6697                        # 7-channel temp sensor (board sensors)
adm1021                        # max1617 temp sensor (CPU/ASIC)

ds100df410                     # ← RETIMER DRIVER (32 instances)
```

`tun` is critical: every `swp*` interface is a TUN device, not a netdev type
`switch`. switchd opens `/dev/net/tun` once per port (52 fds).

### 2. GPIO init for QSFP control

From `hw_init.d/S10gpio_init.sh`. Two pca9538 GPIO chips at gpio bases 160
and 168. Configure 4 control lines per QSFP:

```
GPIOs 24-64        = 0  (SFP+ TX disable — 0 = enabled)
GPIOs 97-104       = 0  (SFP+ TX disable — 0 = enabled, second bank)
GPIOs 160-163      = 1  (QSFP1-4 RST_L  — 1 = released from reset)
GPIOs 164-167      = 0  (QSFP1-4 ModSel_L — 0 = module selected)
GPIOs 168-171      = 0  (QSFP1-4 LPMode — 0 = full power)
```

**Without LPMode=0 the QSFP+ laser does NOT power up, and DOM bytes stay zeroed.**
This is exactly what stock Cumulus 2.5.0 fails to do on this platform when
the user only does `ip link set swp49 up` — the GPIO init script must run
first (called from `/etc/init.d/hw_init`).

### 3. Retimer init for all 32 DS100DF410 chips

From `hw_init.d/S20retimer_init.sh`. Iterate over `/sys/class/retimer_dev/retimer{0..31}`.
For each, read its `label` and apply:

```bash
# Standard SFP+ retimer
set_eq1() {
    cd <retimer device>
    echo 12 > channels
    echo  1 > veo_clk_cdr_cap
    echo 28 > cdr_rst       # ← CDR reset value 28
    echo 16 > cdr_rst       # ← then 16    (this is the breakthrough)
}

# QSFP-side AND "sfp_rx_eq_10" labelled retimers
set_eq2() {
    cd <retimer device>
    echo 12 > channels
    echo  1 > veo_clk_cdr_cap
    echo 28 > cdr_rst
    echo 16 > cdr_rst
    echo 23 > tap_dem       # ← extra: tap_dem = 23 (vs default 16)
}

case "$label" in
    qsfp*)        set_eq2 ;;
    sfp_rx_eq_10) set_eq2 ;;
    *)            set_eq1 ;;
esac
```

This matches our captured live values exactly:

| Retimer attribute | Working value |
|---|---|
| `channels` | 12 → reads back as 165 after write (chip layout) |
| `veo_clk_cdr_cap` | 1 |
| `cdr_rst` write | 28 then 16 (writes 16 last so reads back as 16) |
| `tap_dem` | 16 (default) or 23 (qsfp / sfp_rx_eq_10) |
| `adapt_eq_sm` | 32 (read-only, set by firmware after init) |
| `drv_sel_vod` | 128 (read-only) |
| `pfd_prbs_dfe` | 233 (read-only) |

### 4. BCM ASIC init

`/usr/share/platform-config/accton/as5610_52x/etc/bcm.d/rc.soc` runs after
the kernel BDE is loaded. The full script is in this directory; the
essential lines are:

```
debug -PCi -SChan -SOCMEM -SYMTAB -VERinet -L3 -INTr -ARL ...
attach *
0:
init all
```

`init all` is the BCM SDK macro that runs the standard init sequence
(SRAM init, port mode setup, default config tables, etc.). EdgeNOS already
does this via its OpenMDK init path.

### 5. Port configuration

`/etc/cumulus/ports.conf`:

```
1=10G       # all 48 SFP+ in straight 10G mode
...
48=10G
49=40G      # QSFP+ in full 40G mode (NOT split as 4x10G)
50=40G
51=40G
52=40G
```

### 6. Speed / Duplex / Auto-neg / FEC settings

Captured from `ethtool` on the linked ports:

| Port | Speed | Duplex | Auto-neg | Pause | FEC | PHY | Transceiver |
|---|---|---|---|---|---|---|---|
| swp1 | 10000 | Full | **off** | Symmetric (advertised) | none (XFI, not required by 10GBASE-LR) | 0 | external |
| swp2 | 10000 | Full | **off** | Symmetric | none | 0 | external |
| swp49 | 40000 | Full | **off** | Symmetric | none (40G QSFP-SR, optical) | 0 | external |
| swp50 | 40000 | Full | **off** | Symmetric | none | 0 | external |

Key point: **auto-negotiation is OFF on all ports**. Speed is fixed by
`ports.conf` and the Warpcore firmware mode. FEC is not used on 10GBASE-LR
or 40G QSFP-SR at this generation.

BCM-level interface mode (from `bcmcmd ps`):

| BCM port | Cumulus port | Speed | Interface | STP state |
|---|---|---|---|---|
| xe0  | swp1  | 10G | **XFI** | Forward |
| xe1  | swp2  | 10G | **XFI** | Forward |
| xe48 | swp49 | 40G | **KR4** | Forward |
| xe49 | swp50 | 40G | **KR4** | Forward |

`XFI` (10G) and `KR4` (40G) are the BCM-internal MAC↔PHY interface modes
that EdgeNOS must select via `bmd_port_mode_set()` / equivalent.

### 7. IP assignment

```bash
sudo ip addr add 10.101.101.1/29  dev swp1
sudo ip addr add 10.101.101.10/29 dev swp2
sudo ip addr add 10.101.101.241/32 dev lo
sudo ip link set swp1 up
sudo ip link set swp2 up
```

Persistent equivalent in `/etc/network/interfaces`:

```
auto swp1
iface swp1 inet static
    address 10.101.101.1
    netmask 255.255.255.248

auto swp2
iface swp2 inet static
    address 10.101.101.10
    netmask 255.255.255.248

auto lo
iface lo inet loopback
iface lo inet static
    address 10.101.101.241
    netmask 255.255.255.255
```

## Platform monitoring

### Temperature sensors

Sensor config: `/usr/share/platform-config/accton/as5610_52x/etc/sensors.d/as5610_52x.conf`

| Chip | I2C | Channels | Thresholds (max / crit) |
|---|---|---|---|
| `linux_bde_tmon` | PCI (ASIC built-in) | 1 (BCM die temp) | 100°C / 65°C hyst |
| `max6697` | i2c-9 addr 0x4d | 7 board sensors | 75°C / 85°C crit (channels 2,5,6,7) |
| `max1617` (adm1021) | i2c-9 addr 0x18 | 2 (CPU + remote) | 75°C / 80°C |

Live readings captured (chassis idle):

```
linux_bde_tmon temp1   = 42.5°C   (BCM Trident+ ASIC die temp)
max6697 temp1..7       = 25-32°C  (ambient board sensors)
max1617 temp1          = 22°C     (CPU local)
max1617 temp2          = 52°C     (CPU remote junction)
```

### Fans

The kernel `fan*_input` attributes did not enumerate via `/sys/class/hwmon`
on the running 2.5.0 install (no fan tachometer driver loaded), so fan RPM
isn't directly visible from sysfs in this build. The Accton AS5610-52X has
3 hot-swappable fan trays; their speed control would be:

1. driven by `accton_as5610_52x_cpld` writing PWM duty cycle to the CPLD
   fan-control register set, OR
2. driven by an external fan controller IC on I2C reading the max6697 temps.

Neither was active during this baseline capture (no fan daemon running).
For EdgeNOS we'll need to add a userspace fan controller that polls
`max6697` temps and writes the CPLD fan-PWM register accordingly.

### PSUs

PMBus PSU drivers were not loaded in this Cumulus 2.5.0 install. The
AS5610-52X has 2× hot-swap PSUs typically at PMBus addresses 0x58/0x59 on
a dedicated I2C bus. They are not actively monitored here.

### LEDs

The `/sys/class/leds/` directory is empty on this Cumulus install —
front-panel LEDs are driven by the **CMIC LED uController inside the BCM
ASIC** running a tiny bytecode program (the "ledcode" / "ledproc"), not via
Linux LED class. We already reverse-engineered this path in
`LED_CPU_INTERFACE.md` and `newnos/utils/leddance/`.

## What was wrong before this capture

In earlier sessions we kept blaming the Nexus / SFP+ wavelength / cable
side. **The hardware was fine.** The bring-up steps the platform-config
files prescribe — GPIO init for LPMode + retimer cdr_rst sequence + Warpcore
mode select — are the *complete* recipe. EdgeNOS just needs to do all of
this in the right order before bringing the port up.

## Files captured here (for diffing against EdgeNOS later)

* `platform-config-accton-as5610_52x/` — the entire Accton AS5610-52X
  platform configuration from Cumulus, including:
  * `etc/modules` — kernel module load order
  * `hw_init.d/S10gpio_init.sh` — QSFP GPIO bring-up
  * `hw_init.d/S20retimer_init.sh` — retimer cdr_rst recipe
  * `etc/bcm.d/rc.soc` — BCM SDK init script
  * `etc/bcm.d/backend_map`, `config.d/01config.bcm` — port mapping
  * `etc/sensors.d/as5610_52x.conf` — temp sensor labels and limits
  * `etc/cumulus/ports.conf` — default 48×10G + 4×40G layout
  * `bin/eeprom.py`, `bin/sfputil.py` — SFP/EEPROM helpers
* `cumulus_p2020/` — P2020-CPU platform configs (modules + ports.conf + sensors)
* `100_port_speed_fec.txt` — full `ethtool` + `bcmcmd ps` output for linked ports
* `95_l3_ping_test.txt` / `96_all_links_test.txt` — verified ping captures
* `97_qsfp_loopback_test.txt` / `98_qsfp_tcpdump_test.txt` — QSFP loop proof
* `110_platform_monitoring.txt` / `111_fans_psu_thermal.txt` — sensor/fan/PSU state

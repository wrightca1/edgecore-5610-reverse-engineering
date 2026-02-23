# QSFP Breakout Configuration (Ports 49–52: 40G vs 4x10G)

**Date**: February 15, 2026  
**Platform**: Accton AS5610-52X (BCM56846 Trident+)  
**Source**: Cumulus ports.conf, update-ports, portconfig.py, accton.py

---

## Summary

| Mode | Interfaces | Naming | Use Case |
|------|------------|--------|----------|
| **40G** | 1 per QSFP | swp49, swp50, swp51, swp52 | 40G NIC or cable |
| **4x10G** | 4 per QSFP | swp49s0, swp49s1, swp49s2, swp49s3 | Breakout cable to 4×10G |

---

## 1. Configuration

### 1.1 User Config: `/etc/cumulus/ports.conf`

```
# QSFP+ ports 49-52
# <port> = [4x10G|40G]

49=40G      # One 40G interface (swp49)
50=40G
51=40G
52=40G

# For breakout to 4×10G:
49=4x10G    # Four 10G interfaces (swp49s0, swp49s1, swp49s2, swp49s3)
50=4x10G
51=4x10G
52=4x10G
```

### 1.2 Apply

1. Stop switchd: `systemctl stop switchd` (or `/etc/init.d/switchd stop`)
2. Edit `/etc/cumulus/ports.conf`
3. Run: `/usr/lib/cumulus/update-ports`
4. Restart switchd: `systemctl start switchd`

**Constraint**: switchd must be stopped before running update-ports.

---

## 2. What update-ports Regenerates

When mode changes (40G ↔ 4x10G), update-ports rewrites:

| File | Effect |
|------|--------|
| `/etc/bcm.d/config.d/11ports.bcm` | portmap, pbmp, port_init_speed |
| `/etc/bcm.d/rc.ports_0` | allports, 10Gports, 40Gports |
| `/var/lib/cumulus/porttab` | linux_intf ↔ sdk_intf mapping |
| `/var/lib/cumulus/sfptab` | SFP/QSFP EEPROM path per interface |
| `/var/lib/cumulus/phytab` | PHY addr per interface |
| `/etc/bcm.d/config.bcm` | Merged config (via `merge_config`) |
| Datapath | If layout changes, rc.datapath_0, etc. |

---

## 3. Platform Model (AS5610-52X)

From `cumulus/platforms/accton.py`:

### QSFP SerDes Lanes

| Port | SerDes Lanes (0-based) | 40G portmap | 4x10G portmap (concept) |
|------|------------------------|-------------|---------------------------|
| 49 | 48, 49, 50, 51 | portmap_49.0=49:40 | 49:10, 50:10, 51:10, 52:10 |
| 50 | 44, 45, 46, 47 | portmap_50.0=45:40 | 45:10, 46:10, 47:10, 48:10 |
| 51 | 60, 61, 62, 63 | portmap_51.0=61:40 | 61:10, 62:10, 63:10, 64:10 |
| 52 | 56, 57, 58, 59 | portmap_52.0=57:40 | 57:10, 58:10, 59:10, 60:10 |

### Trident40GPort Behavior

- `modes = ('40G', '4x10G')`
- `num_logical_ports('40G')` = 1
- `num_logical_ports('4x10G')` = 4
- `max_logical_ports` = 4

### Interface Naming

- **40G**: `swp{49,50,51,52}` (one interface per QSFP)
- **4x10G**: `swp{49,50,51,52}s{0,1,2,3}` (four interfaces per QSFP)
  - e.g. swp49s0, swp49s1, swp49s2, swp49s3 for port 49

---

## 4. rc.soc and SerDes

```
m cmic_misc_control LINK40G_ENABLE=1
```

`LINK40G_ENABLE` is chip-level and typically left at 1. Per-port behavior is driven by:

- **portmap**: lane:speed (10 vs 40)
- **port_init_speed_xeN**: 10000 vs 40000
- **pbmp_xport_xe**, **pbmp_valid**: which ports exist

Breakout vs native 40G is expressed by how many logical ports and what portmap entries are emitted, not by changing LINK40G_ENABLE.

---

## 5. Porttab Format (4x10G Example)

```
# linux_intf    sdk_intf    unit    is_fabric
swp1            xe0         0       0
...
swp48           xe47        0       0
swp49s0         xe48        0       0
swp49s1         xe49        0       0
swp49s2         xe50        0       0
swp49s3         xe51        0       0
swp50s0         xe52        0       0
...
swp52s3         xe63        0       0
```

With all 4 QSFP in 4x10G: 48 + 4×4 = 64 logical ports (xe0–xe63).

---

## 6. What Your Custom NOS Needs

### 6.1 Config Input

- User config: port mode (40G or 4x10G) per QSFP
- Source: e.g. `/etc/youros/ports.conf` or equivalent

### 6.2 Logic to Implement

1. **Port expansion**
   - 40G: 1 logical port per QSFP (e.g. xe48 for port 49)
   - 4x10G: 4 logical ports per QSFP (e.g. xe48–xe51 for port 49)

2. **Portmap for 11ports.bcm**
   - 40G: `portmap_N.0=serdes_first:40`
   - 4x10G: one `portmap_M.0=serdes_lane:10` per lane (M increments)

3. **Port init**
   - `port_init_speed_xeN`: 10000 or 40000
   - `port_init_autoneg_xeN`: 0 (no autoneg)

4. **Porttab / sfptab**
   - Map Linux names (swp49 or swp49s0–s3) ↔ BCM names (xeN)

5. **Interface creation**
   - 40G: create swp49, swp50, swp51, swp52
   - 4x10G: create swp49s0–s3, swp50s0–s3, swp51s0–s3, swp52s0–s3
   - Same mechanism as Cumulus: TUN per interface

### 6.3 SerDes / Lane Mapping (AS5610-52X)

| QSFP | 40G Lane | 4x10G Lanes |
|------|----------|-------------|
| 49 | 49 | 48, 49, 50, 51 |
| 50 | 45 | 44, 45, 46, 47 |
| 51 | 61 | 60, 61, 62, 63 |
| 52 | 57 | 56, 57, 58, 59 |

Portmap uses physical SerDes lane numbers. Exact format (1-based vs 0-based) depends on SDK; Cumulus uses `portmap_N.0=lane:speed` with lane from platform serdes.

### 6.4 Hardware Requirements

- Breakout cable or QSFP–to–4×SFP+ fan-out
- Transceivers/cables compatible with 4×10G breakout

### 6.5 LED Handling (Optional)

Cumulus uses different LED programs for 40G vs 4x10G (`_set_led` vs `_set_led_4x10`). Your NOS can implement equivalent logic or ignore LEDs initially.

---

## 7. References

- [SDK_AND_ASIC_CONFIG_FROM_SWITCH.md](SDK_AND_ASIC_CONFIG_FROM_SWITCH.md) – Current portmap (49→lane 49:40, etc.) and BCM config layout
- `cumulus/platforms/accton.py` – AcctonAS5610_52XQSFPp, ports tuple, SerDes lane mapping
- `cumulus/platform.py` – Trident40GPort, num_logical_ports
- `cumulus/portconfig.py` – BCMConfig, porttab, portmap generation

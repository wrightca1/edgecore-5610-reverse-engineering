# OpenMDK Supported Broadcom Chips

OpenMDK (Open Mini Driver Kit) v2.10.9 provides driver support for Broadcom network switch silicon across three subsystems: **CDK** (Chip Development Kit — register-level access), **BMD** (Broadcom Mini Driver — higher-level driver API), and **PHY** (physical layer transceivers).

---

## StrataXGS Data Center Switches (BCM569xx)

High-bandwidth, fixed-pipeline switches for data center spine/leaf and ToR deployments. Prioritize raw throughput over deep feature tables.

### Tomahawk — BCM56960

| Chip | Notes |
|------|-------|
| BCM56960 | 3.2 Tb/s, 32x100GbE or 128x25GbE |
| BCM56961, BCM56962, BCM56963 | Lower port-count / cost-reduced variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56960_A0
**Hardware Examples:**
- Edgecore AS7712-32X (32x 100GbE ToR switch)
- Various whitebox/SONiC-compatible 100GbE data center switches

---

## StrataXGS Trident Family (BCM568xx)

Feature-rich multilayer switches with larger forwarding tables and deeper buffers than Tomahawk. Designed for aggregation, campus core, and feature-heavy ToR.

### Trident2+ — BCM56860 Series

| Chip | Notes |
|------|-------|
| BCM56860 | 1.28 Tb/s, up to 104x10GbE or 32x40GbE |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56860_A0

### Trident2 — BCM56850 Series

| Chip | Notes |
|------|-------|
| BCM56850, BCM56851, BCM56852, BCM56853, BCM56854 | 1.28 Tb/s, 128x10GbE or 32x40GbE |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56850_A0
**Hardware Examples:**
- Netberg Aurora 420 (48x10GbE + 6x40GbE)
- Dell S6000-ON, Arista 7050SX
- Many SONiC/ONIE bare-metal switches

### Trident — BCM56840 Series

| Chip | Notes |
|------|-------|
| BCM56840, BCM56841, BCM56842, BCM56843, BCM56844, BCM56845, BCM56846 | 640 Gb/s, 64x10GbE or 16x40GbE |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56840_A0/B0
**Hardware Examples:**
- ADLINK aTCA-N700 blade switch
- Early-generation 10GbE ToR and aggregation switches

---

## StrataXGS Memory/Triumph Family (BCM566xx)

Carrier-grade and enterprise multilayer switches with advanced QoS, OAM, MPLS, and deep packet inspection features.

### Triumph3 — BCM56640 Series

| Chip | Notes |
|------|-------|
| BCM56640, BCM56643, BCM56644, BCM56648, BCM56649 | 240 Gb/s carrier Ethernet aggregation |
| BCM56680, BCM56682, BCM56684, BCM56685, BCM56686, BCM56689 | Related variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56640_A0/B0, BCM56680_A0/B0, BCM56685_A0/B0
**Hardware Examples:**
- Carrier Ethernet aggregation switches (Brocade/Foundry chassis line cards)
- Service provider metro Ethernet equipment

### Triumph2 — BCM56634 Series

| Chip | Notes |
|------|-------|
| BCM56634, BCM56636 | Multilayer switch with integrated GbE/10GbE |
| BCM56613, BCM56624, BCM56626, BCM56628, BCM56629 | Triumph variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56624_A0/B0, BCM56634_A0/B0

---

## StrataXGS Memory Scorpion/Conqueror (BCM567xx)

Chassis switch fabric interface and high-density 10GbE switches.

| Chip | Notes |
|------|-------|
| BCM56700, BCM56720, BCM56721, BCM56725 | Switch fabric / 10GbE backplane |
| BCM56760, BCM56764, BCM56765, BCM56766, BCM56768 | High-density aggregation |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56725_A0
**Hardware Examples:**
- Chassis-based modular switches (fabric cards)
- High-density aggregation line cards

---

## StrataXGS Firebolt Family (BCM565xx)

Earlier-generation enterprise switches providing GbE with 10GbE uplinks. Foundation of many managed enterprise switches.

### Apache/Firebolt5 — BCM56560 Series

| Chip | Notes |
|------|-------|
| BCM56560, BCM56561, BCM56562, BCM56565, BCM56566, BCM56567, BCM56568, BCM56569 | 1GbE/10GbE/40GbE multilayer |
| BCM56570, BCM56571, BCM56572, BCM56573, BCM56575, BCM56576, BCM56577, BCM56578, BCM56579, BCM56580 | Extended variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56560_A0

### Ranger/Firebolt4 — BCM56440–BCM56468 Series

| Chip | Notes |
|------|-------|
| BCM56440–BCM56468 | GbE/10GbE enterprise multilayer switches |
| BCM56450–BCM56456 | Cost-reduced variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56440_A0/B0, BCM56450_A0/B0

### Firebolt3 — BCM56334 Series

| Chip | Notes |
|------|-------|
| BCM56334, BCM56338 | 24xGbE + 4x10GbE multilayer |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56334_A0/B0

### Firebolt2 — BCM56504/BCM56514 Series

| Chip | Notes |
|------|-------|
| BCM56504, BCM56514 | 24xGbE + 4x10GbE/HiGig+ multilayer |
| BCM56500–BCM56548 | Full family variants |

**Architecture:** XGS
**CDK:** Yes | **BMD:** BCM56504_B0, BCM56514_A0, BCM56524_A0/B0
**Hardware Examples:**
- Enterprise managed switches (HP ProCurve, Foundry/Brocade FastIron series)
- Campus core / distribution layer switches

---

## StrataXGS Memory Hurricane/Wolfhound (BCM561xx–BCM562xx)

Cost-optimized GbE/10GbE switches for SMB, industrial, and campus access deployments.

### Hurricane3 — BCM56160 Series

| Chip | Notes |
|------|-------|
| BCM56160, BCM56162, BCM56163, BCM56164, BCM56166 | Low-cost GbE access switches |

**CDK:** Yes | **BMD:** BCM56160_A0

### Hurricane2 — BCM56150 Series

| Chip | Notes |
|------|-------|
| BCM56150, BCM56151, BCM56152 | GbE access layer |

**CDK:** Yes | **BMD:** BCM56150_A0

### Hurricane — BCM56140–BCM56146

| Chip | Notes |
|------|-------|
| BCM56140–BCM56146 | GbE with 10GbE uplinks |

**CDK:** Yes | **BMD:** BCM56142_A0

### Wolfhound/Helix — BCM56214–BCM56272

| Chip | Notes |
|------|-------|
| BCM56214–BCM56272 | GbE enterprise access / SMB |
| BCM56110–BCM56117 | Low-port-count GbE variants |

**CDK:** Yes | **BMD:** BCM56218_A0, BCM56224_A0/B0
**Hardware Examples:**
- SMB managed switches (Netgear ProSafe, TP-Link managed series)
- Campus access layer switches

---

## StrataXGS Memory Memory Memory Memory Saber/Katana (BCM563xx)

Enterprise stacking switches with GbE density and 10GbE uplinks.

| Chip | Notes |
|------|-------|
| BCM56300–BCM56344 | 24–48 port GbE with stacking |

**CDK:** Yes | **BMD:** BCM56304_B0, BCM56314_A0, BCM56340_A0
**Hardware Examples:**
- Stackable enterprise switches (Foundry/Brocade FastIron Edge series)

---

## StrataXGS Memory Memory Memory Memory XGS Fabric — BCM568xx (Memory Scorpion/Memory Humv)

| Chip | Notes |
|------|-------|
| BCM56800 | 20-port 10GbE multilayer switch |
| BCM56820 | 12x10GbE + 8xHiGig + 4xGbE |
| BCM56825 | Switch fabric variant |

**CDK:** Yes | **BMD:** BCM56800_A0, BCM56820_A0
**Hardware Examples:**
- Modular chassis switch fabric modules
- 10GbE aggregation in carrier/enterprise chassis

---

## StrataXGS Greyhound (BCM534xx / BCM562xx)

Unified GbE/10GbE switches bridging the gap between enterprise StrataXGS and embedded RoboSwitch.

| Chip | Notes |
|------|-------|
| BCM53400–BCM53461 | GbE/10GbE with advanced L2/L3 |
| BCM56260, BCM56261, BCM56262, BCM56263, BCM56265, BCM56266, BCM56267, BCM56268 | Saber2 variants |
| BCM56270, BCM56271, BCM56272 | Wolfhound2 variants |
| BCM55440, BCM55441, BCM55450, BCM55455 | Related variants |

**CDK:** Yes | **BMD:** BCM53400_A0, BCM56260_A0, BCM56270_A0
**Hardware Examples:**
- Edgecore managed campus switches
- SMB/enterprise edge switches with PoE+

---

## Memory/Strata XGS Compact (BCM560xx)

Low-port-count GbE switches for embedded/industrial/CPE applications.

| Chip | Notes |
|------|-------|
| BCM56014, BCM56018 | Compact GbE |
| BCM56024, BCM56025 | Compact GbE variants |
| BCM56040–BCM56049 | Ranger2 compact variants |
| BCM56060–BCM56066 | Memory compact access |

**CDK:** Yes

---

## RoboSwitch Family (BCM53xxx)

Low-cost, low-power embedded Ethernet switches for consumer/CPE, SOHO, wireless APs, and industrial applications. Typically managed via SPI, MDIO, or memory-mapped I/O.

### RoboSwitch Memory — BCM531xx (Memory Managed)

| Chip | Notes |
|------|-------|
| BCM53101, BCM53115, BCM53118, BCM53125, BCM53128, BCM53134 | 5–8 port Fast/Gigabit Ethernet managed switches |

**CDK:** Yes | **BMD:** BCM53101_A0, BCM53115_A0, BCM53118_A0, BCM53125_A0, BCM53128_A0, BCM53134_A0
**Hardware Examples:**
- Home routers (Linksys, ASUS, Netgear consumer routers)
- Wireless access points (Ubiquiti, TP-Link)
- DSL/cable modem gateways
- Industrial Ethernet switches

### RoboSwitch — BCM5301x (Memory ARM SoC + Switch)

| Chip | Notes |
|------|-------|
| BCM53010, BCM53011, BCM53012, BCM53017, BCM53018, BCM53019 | ARM Cortex-A9 SoC with integrated 5-port GbE switch |
| BCM53020, BCM53022, BCM53025 | Enhanced variants |

**CDK:** Yes | **BMD:** BCM53010_A0, BCM53020_A0
**Hardware Examples:**
- ASUS RT-AC68U, RT-AC87U routers
- Netgear R7000 Nighthawk
- Linksys WRT1900AC
- Enterprise wireless access points

### RoboSwitch — BCM532xx/533xx (Memory Memory Managed Stackable)

| Chip | Notes |
|------|-------|
| BCM53242, BCM53262 | Managed stackable 10/100 |
| BCM53280, BCM53282–BCM53286 | Memory Memory Memory Memory Memory Memory Memory Memory Managed GbE stackable |
| BCM53312–BCM53324 | Memory Managed enterprise |
| BCM53342–BCM53347, BCM53365, BCM53369 | Polar/Memoria variants |
| BCM53393, BCM53394 | Industrial variants |

**CDK:** Yes | **BMD:** BCM53262_A0, BCM53280_A0/B0, BCM53314_A0, BCM53324_A0
**Hardware Examples:**
- Managed SMB switches (Netgear GS748T, similar)
- Industrial managed switches

### RoboSwitch Memoria/Memoria — BCM535xx/536xx/537xx

| Chip | Notes |
|------|-------|
| BCM53440–BCM53461 | See Greyhound section above |
| BCM53600, BCM53604 | Memoria enterprise switching |
| BCM53714, BCM53716, BCM53718 | Memoria RoboSwitch high-port |
| BCM53724, BCM53726 | Memoria enhanced variants |

**CDK:** Yes | **BMD:** BCM53600_A0

---

## Memoria/Strata SBX Switch Fabric (BCM88xxx)

Crossbar switch fabric devices for building high-capacity modular chassis systems. Connect to StrataXGS line cards via HiGig.

| Chip | Notes |
|------|-------|
| BCM88230, BCM88231 | Switch fabric with integrated traffic management |
| BCM88235, BCM88236 | Enhanced fabric with deep buffering (up to 2.4 GB DDR3) |

**CDK:** Yes
**Hardware Examples:**
- Memoria Carrier Ethernet chassis switch fabric cards
- Service provider aggregation platforms

---

## Memoria Automotive/Industrial (BCM89xxx)

Ethernet switches for automotive and industrial applications.

| Chip | Notes |
|------|-------|
| BCM89200 | Automotive Ethernet switch |
| BCM89500, BCM89501 | Automotive/industrial Ethernet |

**CDK:** Yes | **BMD:** BCM89500_A0
**Hardware Examples:**
- Automotive in-vehicle networking (infotainment, ADAS backbone)
- Industrial automation networks

---

## PHY Transceivers

OpenMDK includes drivers for both integrated SerDes cores and external PHY chips used for port-level connectivity.

### Integrated SerDes Cores

| Core | Notes |
|------|-------|
| bcmi_combo_serdes | Legacy combo GbE/fiber SerDes |
| bcmi_fusioncore_xgxs | 10GbE XAUI SerDes |
| bcmi_hypercore_xgxs | High-speed backplane SerDes |
| bcmi_hyperlite_xgxs | Lite variant for lower port counts |
| bcmi_tsce_xgxs | TSC Eagle — 1/10/20/40GbE SerDes |
| bcmi_tscf_xgxs | TSC Falcon — 10/25/40/50/100GbE SerDes |
| bcmi_unicore_xgxs | Legacy 10GbE SerDes |
| bcmi_warpcore_xgxs | WarpCore 10/40GbE SerDes |
| bcmi_xgxs16g1 | 16G SerDes for stacking |

### External Copper/Fiber PHYs

| Family | Chips | Notes |
|--------|-------|-------|
| Fast Ethernet | BCM5221, BCM5228, BCM5238, BCM5248 | 10/100 Mbps copper PHY |
| Gigabit Copper | BCM5395, BCM5400, BCM5401, BCM5402, BCM5404, BCM5411, BCM5421, BCM5424, BCM5461, BCM5464, BCM5466, BCM5482, BCM5488 | 10/100/1000 Mbps copper PHY |
| Extended GbE | BCM54210, BCM54220, BCM54240, BCM54280, BCM54282, BCM54290, BCM54292, BCM54294, BCM54295, BCM54296 | Enhanced GbE copper with EEE |
| 10GbE Copper | BCM54616, BCM54680, BCM54880, BCM54980 | 10GBASE-T PHY |
| 10GbE Fiber | BCM8073, BCM8074, BCM8727, BCM8747, BCM8750, BCM8752, BCM8754 | 10GbE SFP+/XFP optical PHY |
| 40/100GbE | BCM82328, BCM84328 | QSFP/CFP retimer/gearbox |
| Copper 10GBASE-T | BCM84834, BCM84844, BCM84846, BCM84848, BCM84856, BCM84858, BCM84868 | 10GBASE-T copper PHY |

---

## Summary by Architecture

| Architecture | Description | Chip Ranges | Count |
|---|---|---|---|
| **XGS** | StrataXGS enterprise/data center switches | BCM56xxx (most) | ~230 |
| **XGSd** | StrataXGS data center optimized | BCM56960 and related | ~5 |
| **XGSm** | StrataXGS metro/carrier | BCM56640, BCM56680 | ~15 |
| **Robo** | RoboSwitch embedded/consumer | BCM53xxx | ~70 |
| **SBX** | Switch fabric | BCM88xxx | 4 |
| **PHY** | Transceivers (integrated + external) | Various | 75+ |
| **Total** | | | **~400** |

---

*Generated from OpenMDK v2.10.9 chip definitions in `cdk/PKG/chip/`, `bmd/PKG/chip/`, and `phy/PKG/chip/`.*

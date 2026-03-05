---
layout: default
title: Home
---

# Edgecore AS5610-52X Reverse Engineering

Reverse engineering documentation for the **Broadcom BCM56846 (Trident+)** ASIC in the Edgecore AS5610-52X switch, running Cumulus Linux 2.5.

All findings obtained via legal means on hardware we own. No NDA material.

## Quick Navigation

### Core References
- [Master Status Table](PATH_B_COMPLETION_STATUS.html) -- what's confirmed, with links
- [SCHAN Format Analysis](SCHAN_FORMAT_ANALYSIS.html) -- S-Channel command word format
- [BDE CMIC Registers](BDE_CMIC_REGISTERS.html) -- BAR0 register map
- [ASIC Init and DMA Map](ASIC_INIT_AND_DMA_MAP.html) -- initialization sequence

### L2 Switching
- [L2 Entry Format](L2_ENTRY_FORMAT.html) -- L2_ENTRY hash table bit layout
- [L2 Write Path](L2_WRITE_PATH_COMPLETE.html) -- full API-to-ASIC call chain
- [L2 Table Access](L2_TABLE_ACCESS_ANALYSIS.html) -- table access mechanism

### L3 Routing
- [L3 Nexthop Format](L3_NEXTHOP_FORMAT.html) -- full L3 forwarding chain
- [L3 IPv6 Format](L3_IPV6_FORMAT.html) -- IPv6 routing tables
- [L3/ECMP/VLAN Write Path](L3_ECMP_VLAN_WRITE_PATH.html) -- L3 programming

### VLAN
- [VLAN Table Format](VLAN_TABLE_FORMAT.html) -- ingress/egress VLAN tables

### Port/MAC
- [Port Bringup Register Map](PORT_BRINGUP_REGISTER_MAP.html) -- XLPORT block addresses
- [SerDes WC Init](SERDES_WC_INIT.html) -- Warpcore MDIO init sequence
- [Stats Counter Format](STATS_COUNTER_FORMAT.html) -- XLMAC counter offsets

### Packet I/O
- [Packet I/O BDE DMA Interface](PKTIO_BDE_DMA_INTERFACE.html) -- DCB type 21 format
- [DMA DCB Layout](DMA_DCB_LAYOUT_FROM_KNET.html) -- descriptor ring layout

### Analysis Documents
- [Complete Interface Analysis](COMPLETE_INTERFACE_ANALYSIS.html)
- [Cumulus vs OpenNSL Architecture](CUMULUS_VS_OPENNSL_ARCHITECTURE.html)
- [Write Mechanism Analysis](WRITE_MECHANISM_ANALYSIS.html)
- [Gaps for Custom Switchd/SDK](GAPS_FOR_CUSTOM_SWITCHD_SDK.html)

## Hardware

| | |
|--|--|
| **Switch** | Edgecore AS5610-52X |
| **ASIC** | BCM56846 (Trident+), 56Gbps |
| **Ports** | 52x 10GbE SFP+ + 4x 40GbE QSFP |
| **CPU** | PowerPC e500v2 (Freescale P2020) |
| **SerDes** | Broadcom Warpcore WC-B0 |

## Related

- [open-nos-as5610](https://wrightca1.github.io/open-nos-as5610/) -- the NOS built from these findings
- [GitHub: open-nos-as5610](https://github.com/wrightca1/open-nos-as5610)

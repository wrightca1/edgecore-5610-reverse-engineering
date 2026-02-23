# Edgecore AS5610-52X Reverse Engineering

Reverse engineering notes for the **Edgecore AS5610-52X** 52-port 10GbE switch running **Cumulus Linux 2.5** on a **Broadcom BCM56846 (Trident+)** ASIC.

The goal was to understand the hardware well enough to write a minimal custom SDK/dataplane — without access to Broadcom NDA documentation.

---

## What's in here

All findings are in the `docs/` directory. Key documents:

| Document | Contents |
|----------|----------|
| [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) | **Master status table** — what's been confirmed, with links to artifacts |
| [L2_ENTRY_FORMAT.md](L2_ENTRY_FORMAT.md) | L2_ENTRY and L2_USER_ENTRY ASIC bit layouts (verified via live bcmcmd) |
| [L3_NEXTHOP_FORMAT.md](L3_NEXTHOP_FORMAT.md) | Full L3 forwarding chain: L3_DEFIP → ECMP → ING/EGR nexthop → EGR_L3_INTF |
| [SERDES_WC_INIT.md](SERDES_WC_INIT.md) | Warpcore WC-B0 SerDes MDIO init sequence (captured via GDB watchpoint) |
| [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) | XLPORT block addresses, MAC registers, per-lane formula |
| [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) | S-channel command word format (0x2800XXXX) |
| [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) | Confirmed: S-channel DMA path, not direct BAR writes |
| [L2_WRITE_PATH_COMPLETE.md](L2_WRITE_PATH_COMPLETE.md) | Full L2 add call chain from API to ASIC |
| [L3_ECMP_VLAN_WRITE_PATH.md](L3_ECMP_VLAN_WRITE_PATH.md) | Full L3/ECMP write path |
| [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md) | CMIC DMA regions and ASIC initialization |
| [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md) | CMIC register map (BAR0 offsets) |
| [INFRASTRUCTURE_REFERENCE.md](INFRASTRUCTURE_REFERENCE.md) | Lab setup used for analysis |

---

## Hardware

- **Switch**: Edgecore AS5610-52X (also sold as Accton AS5610-52X)
- **ASIC**: Broadcom BCM56846 (Trident+), 56Gbps, 52× 10GbE + 4× 40GbE uplinks
- **CPU**: PowerPC e500v2 (Freescale P2020)
- **NOS**: Cumulus Linux 2.5.1 (Debian 7 / Wheezy base, PPC32)
- **SerDes**: Broadcom Warpcore WC-B0 (internal MDIO, clause-22)

---

## Methods

- **bcmcmd** (`bcmcmd 'listmem <table>'`, `dump raw`, etc.) — live ASIC table inspection
- **GDB hardware watchpoints** — traced CMIC MIIM register writes to capture SerDes init sequence
- **Ghidra + manual disassembly** — static analysis of `switchd` (PPC32 big-endian binary)
- **GDB on live switchd** — confirmed S-channel DMA write path at runtime

---

## Key Findings

### Register Access
- BAR0 (physical `0xa0000000`) is mmap'd into switchd at VA `0x4802b000`
- All table writes go through **S-channel DMA** (not direct BAR writes)
- MDIO (Warpcore SerDes) writes happen via `CMIC_MIIM_PARAM` (BAR0+0x158) + `CMIC_MIIM_ADDRESS` (BAR0+0x4a0)

### L2 Table (L2_ENTRY)
- Hash table, 131072 entries × 13 bytes, base address `0x07120000`
- Key fields: `VALID@0`, `VLAN_ID@[15:4]`, `MAC_ADDR@[63:16]`, `PORT_NUM@[70:64]`

### L3 Forwarding Chain
```
L3_DEFIP[prefix] → NEXT_HOP_INDEX
  ING_L3_NEXT_HOP[idx] → PORT_NUM[22:16]
  EGR_L3_NEXT_HOP[idx] → DA_MAC[62:15] + INTF_NUM[14:3]
    EGR_L3_INTF[intf]  → SA_MAC[80:33] + VLAN[24:13]
```

### SerDes Init (Warpcore WC-B0, 10GbE)
Key MDIO writes on port bring-up:
- `page=0x0008, reg[0x1e]=0x8000` — IEEE block enable
- `page=0x0a00, reg[0x10]=0xffe0` — SerDes digital: fiber/SFI mode
- `page=0x1000, reg[0x18]=0x8010` — clock recovery
- `page=0x3800, reg[0x01]=0x0010` — WC_CORE sequencer start

---

## Status

All major reverse engineering goals are complete. See [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md) for the full breakdown.

---

*All findings obtained via legal means on hardware we own.*

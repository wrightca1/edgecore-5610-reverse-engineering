# Cumulus Linux — Supported Hardware (decoded from the install images)

What hardware does Cumulus Linux actually support? This document answers that
**from the software itself** — extracted directly from the Cumulus Linux ONIE
installer images we hold (`CumulusLinux-1.5.2` … `CumulusLinux-2.5.1`,
powerpc + amd64), not from marketing material.

It is the authoritative platform list as Cumulus's own code sees it, plus the
silicon / CPU each board carries.

## Where this data comes from (provenance)

Every fact below is sourced from files **inside** the `.bin` images:

| Source file (in the image) | What it gives us |
|---|---|
| `usr/lib/python2.7/dist-packages/cumulus/platformdb.py` | The master tuple of every supported platform class |
| `…/cumulus/platforms/{accton,cel,cumulusp,dni,dell,quanta}.py` | Per-board: ASIC family, front-panel port map, SerDes lanes, LEDs, sensors |
| `…/cumulus/platform.py` | The `BCMChip` family classes (Trident / Trident2 / Triumph / Apollo / Helix4) and port-speed base classes |
| `…/cumulus/__chip_config/bcm/<family>/{sdk.bcm,rc.forwarding,hw_desc,datapath.conf}` | Per-family Broadcom SDK config → confirms die / buffer sizing |
| `control/cumulus/init/<platform>/platform.conf` + `platform.fdisk` | Per-board install/boot recipe → reveals CPU architecture (PowerPC vs x86) |

The `.bin` is a shell archive: header script, then `exit_marker`, then a tar
of `installer/{control.tar.xz, data.tar}`. `control.tar.xz` holds the per-board
init scripts; `data.tar` → `sysroot.squash.xz` → (unsquashfs) holds the full OS
including the Python platform database above.

Reproduce — list every board a given image supports:

```sh
# board init list (cheap — no squashfs needed)
b=CumulusLinux-2.5.1-powerpc.bin
off=$(grep -a -m1 -n '^exit_marker$' "$b" | cut -d: -f1)
sed -e "1,${off}d" "$b" | tar -xO installer/control.tar.xz \
  | xz -dc | tar -tf - | grep -oE 'cumulus/init/[a-z0-9_]+/?$'

# full silicon/port detail (the authoritative DB)
unsquashfs -d /tmp/cl extracted/2.5.1-powerpc/data/sysroot.squash.xz
sed -n '/^platforms = (/,/^)/p' \
  /tmp/cl/usr/lib/python2.7/dist-packages/cumulus/platformdb.py
```

---

## 1. Broadcom silicon family decoder

Cumulus does not hard-code a die per board; it picks a **chip family class**
(`cumulus.platform.*Chip`) and pulls the SDK config from
`__chip_config/bcm/<family>/`. The family → real Broadcom part mapping:

| Cumulus chip class | Broadcom family / die | Capacity | Typical port build | `base_pbmp` / notes |
|---|---|---|---|---|
| `TridentChip` | **Trident / Trident+** — BCM5684x (AS5610-52X = **BCM56846**) | 640 Gbps | 48×10G + 4×40G | `portmap_capable`, `hw_desc` 46080 cells |
| `TridentTwo_56850_Chip` | **Trident2** — **BCM56850** | 1.28 Tbps | 32×40G (100G uplinks; `hsp_bw=100`) | `hw_desc` 59869 cells |
| `TridentTwo_56854_Chip` | **Trident2** — **BCM56854** | 1.28 Tbps | 48×10G + 6×40G (`hsp_bw=40`) | same Trident2 SDK dir |
| `TriumphChip` | **Triumph2** — BCM5663x | ~240 Gbps | 48×1G + 4×10G | `portmap_capable=False` |
| `ApolloChip` | **Apollo2** — **BCM56540** | — | 48×1G + 4×10G | config: `bcm56540_4x10_2x42` |
| `Helix4Chip` | **Helix4** — **BCM56340** | — | 48×1G + 4×10G | config: `bcm56340_4x10`; AXP ports in `base_pbmp` |

> **Ties to our targets:** the AS5610-52X we reverse-engineered is the
> `TridentChip` / **BCM56846** path. The AS4610-54T (newer effort) is
> **Helix4 / BCM56340** — the *same family* Cumulus uses for the Dell S3000
> (`dell,s3000_c2338`), so the S3000 datapath config is a useful cross-reference.

---

## 2. Master support matrix — Cumulus Linux 2.5.1

Every entry in `platformdb.py`, cross-referenced with the front-panel port map
(`label=` count, QSFP vs SFP) and the install recipe (CPU arch).

`root_type=blk`/`ubi` ⇒ PowerPC (u-boot / NAND / USB-flash). `root_type=tar`
⇒ x86 (GRUB / CFast). This is how the image itself distinguishes arch.

| Platform id (`name`) | Vendor / model | ASIC family → die | Front-panel ports | CPU / arch |
|---|---|---|---|---|
| `accton,as5610_52x` | Accton **AS5610-52X** | Trident+ → **BCM56846** | 48×10G + 4×40G | Freescale **P2020** (PPC) |
| `accton,es5652bt1` | Accton ES5652BT1 | Trident → BCM5684x | 48×10G + 4×40G | P2020 (PPC) |
| `accton,as4600_54t` | Accton **AS4600-54T** | Apollo2 → **BCM56540** | 48×1G + 4×10G | P2020 (PPC) |
| `accton,as6700_32x` | Accton AS6700-32X | Trident2 → BCM56850 | 32×40G | P2020 (PPC) |
| `accton,as6701_32x` | Accton AS6701-32X | Trident2 → BCM56850 | 32×40G | **P2041** (PPC) |
| `accton,as5712_54x` | Accton AS5712-54X | Trident2 → **BCM56854** | 48×10G + 6×40G | Intel Atom **Avoton C2538** (x86) |
| `accton,as6712_32x` | Accton AS6712-32X | Trident2 → BCM56854 | 32×40G | Intel Atom Avoton (x86) |
| `cel,kennisis` | Celestica Kennisis | Triumph2 → BCM5663x | 48×1G + 4×10G | PPC (NAND/UBI) |
| `cel,redstone` | Celestica Redstone | Trident → BCM5684x | 48×10G + 4×40G | PPC (NAND/UBI) |
| `cel,redstone_xp` | Celestica Redstone-XP | Trident2 → BCM56854 | 48×10G + 6×40G | Intel Atom (x86) |
| `cel,smallstone` | Celestica Smallstone | Trident2 → BCM56850 | 32×40G | PPC (NAND/UBI) |
| `cel,smallstone_xp` | Celestica Smallstone-XP | Trident2 → BCM56850 | 32×40G | Intel Atom (x86) |
| `dell,s6000_s1220` | **Dell S6000-ON** | Trident2 → BCM56850 | 32×40G | Intel Atom **S1220 Centerton** (x86) |
| `dell,s4000_c2338` | Dell S4000 | Trident2 → BCM56854 | 48×10G + 6×40G | Intel Atom **Avoton C2338** (x86) |
| `dell,s3000_c2338` | **Dell S3000** | **Helix4 → BCM56340** | 48×1G + 4×10G | Intel Atom Avoton C2338 (x86) |
| `dni,et-7448bf` | Delta/DNI ET-7448BF | Trident → BCM5684x | 48×10G + 4×40G | PPC |
| `dni,c7448n` | Delta/DNI C7448N | Trident → BCM5684x | 48 + 4×40G | PPC |
| `dni,et-6448r` | Delta/DNI ET-6448R | Triumph2 → BCM5663x | 48 ports | PPC |
| `mlx,sx1400_i73612` | Mellanox **SX1400** | **SwitchX (non-Broadcom!)** | — | PPC |
| `quanta,lb9` | Quanta LB9 | Triumph2 → BCM5663x | 48×1G + 4×10G | PPC |
| `quanta,lb8` | Quanta LB8 | Trident → BCM5684x | 48×10G | PPC |
| `quanta,ly2` | Quanta LY2 | Trident → BCM5684x | 48×10G + 4×40G | PPC |
| `quanta,ly2r` | Quanta LY2R | Trident → BCM5684x | 48×10G + 4×40G | PPC |
| `quanta,ly6_p2020` | Quanta LY6 (P2020) | Trident2 → BCM56850 | 32×40G | P2020 (PPC) |
| `quanta,ly6_rangeley` | Quanta LY6 (Rangeley) | Trident2 → BCM56850 | 32×40G | Intel Atom **Rangeley** (x86) |
| `quanta,ly8_rangeley` | Quanta LY8 | Trident2 → BCM56854 | 48×10G + 6×40G | Intel Atom Rangeley (x86) |
| `quanta,ly9_rangeley` | Quanta LY9 | Trident2 → BCM56854 | 54 ×(10G/40G) | Intel Atom Rangeley (x86) |
| `quanta,panther` | Quanta Panther | (init-only, no DB class) | — | Intel Atom (x86) |
| `cumulus,cumulus_p2020` | Cumulus P2020 ref design | Trident / Trident2 | reference line-cards | P2020 (PPC) |

Cumulus reference-design `cumulus_p2020` resolves at runtime to four sub-variants
in `platformdb.py`: `…_lc64x10` (64×10G line card, Trident), `…_lc16x40`
(16×40G, Trident), `…_trident2` (Trident2/BCM56850), and a standalone build.
`dni,et-6448r` likewise expands to board-revision variants (`SbS` rev 160/32,
`OU` rev 128, `OU2` rev 192) all on Triumph2, plus a `DNI7048P` Trident variant.

---

## 3. CPU / architecture split

Cumulus 2.5.x ships **two** installer binaries; a board installs from whichever
matches its CPU:

**PowerPC** (`*-powerpc*.bin`) — Freescale QorIQ:
- **P2020** (e500v2): AS5610-52X, ES5652BT1, AS4600-54T, AS6700-32X, Cumulus P2020, Quanta LY6-P2020, most Celestica/DNI/Quanta Trident & Triumph boards
- **P2041** (e500mc): AS6701-32X
- Mellanox SX1400 (PPC host CPU driving a SwitchX ASIC)

**x86-64** (`*-amd64.bin`) — Intel Atom:
- **Avoton C2538**: AS5712-54X, AS6712-32X
- **Avoton C2338**: Dell S4000, Dell S3000
- **S1220 "Centerton"**: Dell S6000-ON
- **Rangeley (C2000)**: Quanta LY6/LY8/LY9-Rangeley, Quanta Panther
- Celestica Redstone-XP / Smallstone-XP

The "XP" Celestica boards and the Dell/Quanta-Rangeley models are the x86
re-spins of earlier PowerPC designs — same ASIC, new CPU complex.

---

## 4. Hardware-support timeline (across our image collection)

Board init-dir presence per PowerPC image (when a platform first becomes
installable). Confirms when our target hardware entered Cumulus support:

| Platform | 1.5.2 | 1.5.3 | 2.0.0 | 2.0.1 | 2.0.2 | 2.1.0 | 2.5.0 | 2.5.1 |
|---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| accton es5652bt1 | ● | ● | ● | ● | ● | ● | ● | ● |
| accton es4654bf / as4600_54t | ● | ● | ●¹ | ●¹ | ●¹ | ●¹ | ● | ● |
| **accton as5610_52x** | | | | **●** | ● | ● | ● | ● |
| accton as6700_32x | | | | | | ● | ● | ● |
| accton as6701_32x | | | ● | ● | ● | ● | ● | ● |
| accton as5712_54x | | | | | | | ● | ● |
| accton as6712_32x | | | | | | | | ● |
| cel kennisis | ● | ● | ● | ● | ● | ● | ● | ● |
| cel redstone | ● | ● | ● | ● | ● | ● | ● | ● |
| cel smallstone | | | ● | ● | ● | ● | ● | ● |
| cel redstone_xp / smallstone_xp | | | | | | | ● | ● |
| cumulus p2020 | ● | ● | ● | ● | ● | ● | ● | ● |
| dell s6000_s1220 | | | | | | ● | ● | ● |
| dell s4000 / s3000 | | | | | | | ●/– | ● |
| dni et-7448bf / c7448n / et-6448r | | | | | | | ● | ● |
| im n29xx_t40n | | | | | | ● | | |
| **mlx sx1400_i73612** | | | | | | ● | ● | ● |
| quanta lb9 | ● | ● | ● | ● | ● | ● | ● | ● |
| quanta ly2 | ● | ● | ● | ● | ● | ● | ● | ● |
| quanta ly2r | | | | ● | ● | ● | ● | ● |
| quanta ly6 (p2020/rangeley) | | | ● | ● | ● | ● | ● | ● |
| quanta ly8 / ly9 rangeley | | | | | | | ● | ● |
| quanta panther | | | | | | | ● | ● |

¹ `accton_es4654bf` in 1.5.x → renamed `accton_as4600_54t` from 2.0.0.
(2.5.x rows from the extracted powerpc+amd64 init trees; earlier rows from each
`.bin`'s `control.tar.xz`.)

### Takeaways
- **Our AS5610-52X first shipped in Cumulus 2.0.1** and remained supported
  through 2.5.1 — so any 2.0.1+ image is a valid RE baseline (we use 2.5.0).
- **Cumulus was not Broadcom-only.** From 2.1.0 it carried a **Mellanox
  SwitchX (SX1400)** board — a completely different ASIC + datapath that lives
  *outside* the Broadcom `platformdb.py` (it has an `init/` dir but no
  `platforms/*.py` class), driven by Mellanox's own switchd path.
- Interface Masters `im_n29xx_t40n` appears only in 2.1.0 (dropped later).
- The 2.0.x → 2.5.x jump is where Cumulus added the **x86/Atom** re-spins
  (AS5712, Dell S-series, Celestica XP, Quanta Rangeley) alongside the original
  PowerPC fleet.

---

## 5. Notes & caveats

- Port counts are the front-panel `label=` entries in each `*Switch` class;
  QSFP (40G) vs SFP+ (10G/1G) is read from the `_qsfp`/`_sfp` helper used. A few
  boards (e.g. AS4600-54T, Helix4/Triumph designs) expose 48×1G copper + a small
  number of 10G SFP+ uplinks rather than all-10G.
- The exact die within a family (e.g. BCM56840 vs 56846) is set per board by the
  SDK `config.bcm` in the running rootfs, not by `platformdb.py`. AS5610-52X =
  **BCM56846** is confirmed from our live chip dumps (see `COMPLETE_CHIP_INVENTORY.md`).
- `platformdb.py` carries more entries than there are `init/` dirs: several are
  **runtime-detected board revisions** of one physical platform (DNI 6448
  SbS/OU/OU2, Cumulus P2020 line-card variants) selected by `lookup(name, revision)`.

---

*Generated from the Cumulus Linux installer images in this tree
(`CumulusLinux-{1.5.2…2.5.1}-{powerpc,amd64}.bin`). See `extracted/` for the
unpacked 2.5.0/2.5.1 trees.*

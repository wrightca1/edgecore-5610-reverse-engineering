# SFP / QSFP Module Support — What This Switch Can Actually Use

Three questions answered: 1G SFPs, DAC cables, QSFP breakout.

## TL;DR

| Module type | AS5610 hardware capable? | Cumulus 2.5.0 software support? | EdgeNOS opportunity |
|---|---|---|---|
| **10G-LR / SR optical SFP+** | ✅ | ✅ default | already working |
| **10G DAC (passive copper)** | ✅ | ✅ auto-detected, no config | already working |
| **10G DAC (active)** | ✅ | ✅ should work | already working |
| **1G optical SFP (SX, LX, etc.)** | ✅ (Warpcore can do 1000BASE-X) | ❌ **NOT exposed** | yes — add `'1G':1` to Trident10GPort modes |
| **1G copper SFP (1000BASE-T)** | ✅ (Warpcore SGMII to ext PHY) | ❌ **NOT exposed** | yes |
| **100M SFP** | maybe (chip-dependent) | ❌ | unlikely useful |
| **40G QSFP+ SR / LR** | ✅ | ✅ default | working on swp49-52 |
| **40G QSFP DAC** | ✅ | ✅ | should work |
| **40G QSFP → 4× SFP+ breakout** | ✅ | ✅ via `49=4x10G` in ports.conf | works |
| **40G QSFP → 4× LC fan-out** | ✅ | ✅ same as above | works |
| **25G** | ❌ chip is 10G/40G only | ❌ | not possible |

## How I know

From `cumulus/platform.py` source (captured at `platform-daemons/usr/lib/python2.7/dist-packages/cumulus/platform.py`):

```python
class Trident10GPort(TridentPort):     # used by SFP+ ports 1-48
    modes = ('10G', '40G/4')
    default_mode = modes[0]
    _speed_map = { '10G'   : 10,
                   '40G/4' : 40 }

class Trident40GPort(TridentPort):     # used by QSFP+ ports 49-52
    modes = ('40G', '4x10G')
    default_mode = modes[0]
    _speed_map = { '4x10G' : 10,
                   '40G'   : 40 }
```

That's it. The Cumulus 2.5.0 platform definition for AS5610-52X SFP+ ports
literally has only two speeds in its map: 10G and 40G/4. Anything you
plug into SFP+ that wants 1G or 100M will fail to come up under Cumulus
2.5.0 on this specific platform.

The chip itself supports 1G SGMII and 1000BASE-X — that's a Warpcore
capability — but the Cumulus port abstraction doesn't surface it.
EdgeNOS can.

A `'1G'` mode IS defined elsewhere in `platform.py` (lines 444, 469) for
1G-only platform classes (the RJ45 management-style ports), proving the
SDK has 1G support. It's just not wired into the Trident10GPort class.

## 1G SFPs — what would it take to support?

### Hardware confirmation

1. **BCM56846 Warpcore SerDes**: capable. Each lane can run 1G
   (SGMII for copper, 1000BASE-X for optical). Speed is set per-port via
   `bcm_port_speed_set(unit, port, 1000)`.

2. **DS100DF410 retimer**: datasheet says 1.0 – 11.3 Gbps. So 1G passes
   through fine. The retimer EQ adapts to whatever rate the SerDes
   negotiates.

3. **SFP cage / I2C / GPIO**: identical electrically to 10G. The
   module's EEPROM (page A0) byte 12 is "BR, Nominal" which tells the
   host what rate; the host then sets its SerDes accordingly.

### Software changes needed

For EdgeNOS to support 1G optical/copper SFPs:

```python
class Trident10GPort(TridentPort):
    modes = ('10G', '40G/4', '1G')              # add '1G'
    _speed_map = { '10G'   : 10,
                   '40G/4' : 40,
                   '1G'    : 1 }                # add 1G

    def serdes_if_type(self, speed):
        return { 1: 'SGMII', 10: 'XFI', 40: 'XLAUI' }[speed]
```

Then `ports.conf` accepts `1=1G`. update-ports writes a different
`port_init_speed_xe0=1000` to `rc.datapath_0`, switchd reads it and
calls `bcm_port_speed_set(0, xe0, 1000)`. The chip reconfigures the
SerDes to 1000BASE-X (or SGMII for copper SFPs).

Cumulus added 1G SFP support in later releases (Cumulus 3.x+) on this
same hardware. The mechanics work — only the platform-class definition
needs updating.

## DAC cables (Direct Attach Copper)

Should work as-is. Cumulus's SFP detection logic looks at EEPROM page A0:

* Byte 0 (Identifier) = `0x03` (SFP)
* Byte 8 (Transceiver) bit 2 = "Passive Cu cable"
* Byte 8 bit 3 = "Active Cu cable"

When that flag is set, switchd applies different SerDes pre-emphasis /
drive settings (DAC needs different EQ than optic). The retimer's
adaptive EQ then converges on the cable's electrical characteristics.

Captured live: our captures show `Cable_Technology` fields readable in
the EEPROM. The Cisco-Avago AFBR-79EBPZ-CS2 we tested is technically a
QSFP optical module, but a real DAC reports the same `Length (Copper)`
field with a non-zero value (typically 1, 3, 5, or 7 m).

No special config needed for DAC — just plug it in. Both ends must be
DAC-rated (i.e., a 10G DAC plugged into a 10G port works; a 25G DAC
won't because the SerDes can't do 25G).

## 40G QSFP+ breakout — 4× 10G per QSFP port

### Cumulus procedure

1. Edit `/etc/cumulus/ports.conf`:

   ```
   49=4x10G        # was: 49=40G
   ```

2. Regenerate switchd state:

   ```bash
   sudo /usr/lib/cumulus/update-ports
   ```

   This rewrites `/var/lib/cumulus/porttab`, `phytab`, `sfptab`, and
   `rc.datapath_0` with the breakout-config equivalents.

3. Restart switchd:

   ```bash
   sudo service switchd restart
   ```

4. The four lanes appear as separate Linux interfaces:

   ```
   swp49s0   ← QSFP lane 0  (BCM xe48 in 4x10G mode)
   swp49s1   ← QSFP lane 1  (BCM xe49)
   swp49s2   ← QSFP lane 2  (BCM xe50)
   swp49s3   ← QSFP lane 3  (BCM xe51)
   ```

   Each is independent — own MAC, own L3 interface, own VLAN
   (3301-style numbering continues).

### Cable requirements

* **QSFP+ → 4× SFP+** copper breakout (MPO/MTP for fiber, or DAC fan-out
  cable). Common Cisco/Arista part numbers exist.
* **QSFP+ → 4× LC fan-out** optical (e.g., 40G-SR4 with MPO-to-4×LC
  breakout cable) for connecting to 4 separate 10G SR ports.
* Single 40G-LR4 / 40G-CWDM cables (single LC pair) do NOT break out —
  those are WDM at 40G and need a 40G-mode peer.

### Caveat for our chassis

We currently have **40G QSFP-SR-BD** modules (Cisco AFBR-79EBPZ-CS2) in
swp49-52. These are bidirectional dual-LC modules that internally do
40G with 4 lanes multiplexed onto 2 fiber wavelengths. They are NOT
breakout-friendly — they expect a peer QSFP-SR-BD on the other end.

To use the breakout feature, you'd need to replace those modules with
either:
* QSFP+ to 4× SFP+ DAC breakout cable (1-7m, copper), OR
* QSFP+ MPO module + 4× SFP+ at the far end with an MPO-to-LC fan-out
  cable

Once installed and `ports.conf` is updated, the BCM ASIC re-bundles the
4 SerDes lanes that were ganged for 40G into 4 independent 10G lanes.
No retimer reconfig needed — the DS100DF410 just retimes each lane
independently.

### Verification once breakout is active

```bash
ip link show | grep swp49     # → swp49s0, swp49s1, swp49s2, swp49s3
sudo /usr/lib/cumulus/bcmcmd "ps xe48,xe49,xe50,xe51"
# Should show:
#   xe48  up   10G  FD  SW  No  Forward  ...  XFI  ...
#   xe49  up   10G  FD  SW  No  Forward  ...  XFI  ...
#   xe50  up   10G  FD  SW  No  Forward  ...  XFI  ...
#   xe51  up   10G  FD  SW  No  Forward  ...  XFI  ...
# All 10G XFI instead of 40G KR4
```

## Mixing modes — gotchas

`Trident10GPort.modes = ('10G', '40G/4')` means a group of 4 adjacent
SFP+ ports can be ganged into 1× 40G. For this to work:

* The 4 ports must be on lanes 0-3 of the same Warpcore block.
* You set the *first* port to `40G/4` and the *next 3* port labels are
  implicitly consumed: `1=40G/4` would consume ports 1,2,3,4.
* The `num_logical_ports` method returns 0 for ports that are
  "consumed" by an adjacent 40G/4 port — they disappear from `ip link`.

This is mostly useful for connecting an SFP+ aggregator block to a 40G
peer over an MPO or 4× DAC breakout cable in reverse direction.

## What's not supported regardless

* **25G** — chip doesn't have 25G SerDes mode.
* **100G** — chip doesn't have 100G PMA.
* **2.5G / 5G (NBASE-T)** — not on Warpcore.
* **WAN-rate (9.95 Gbps OC-192)** — chip is data-rate only.

## Captured evidence

* `500_ports_conf_options.txt` — live captures of update-ports / ports.conf
  documentation
* `platform-daemons/usr/lib/python2.7/dist-packages/cumulus/platform.py`
  lines 541 (Trident10GPort) and 696 (Trident40GPort) — the
  authoritative mode list

## EdgeNOS recommendations

1. **1G SFP support** — straightforward port-class extension. Adds value
   for mixed deployments where 1G management or legacy SFPs need to work.
   ~30 lines of code to add `_speed_map['1G']=1` and the SerDes mode
   switch.

2. **DAC support** — already works at the SerDes level. Just need to
   trust the existing OpenMDK DAC-detection path. Test with an actual
   DAC before declaring done.

3. **4×10G breakout** — useful for cabling density (one QSFP cage =
   4 lanes of independent 10G connectivity). Implementation needs:
   * `ports.conf`-equivalent parser that accepts `49=4x10G`
   * BCM-SDK port-mode call to reconfigure 4 SerDes lanes from 40G
     gang to independent 10G
   * Generate 4 sub-interfaces (`swpNs0..3` naming) at Linux level
   * Update LED dispatch (each sub-port needs its own LED indication)

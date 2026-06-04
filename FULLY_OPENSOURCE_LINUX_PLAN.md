# AS4610-54T — Fully Open-Source Linux + L3 Routing: What We Need

Goal: a plain Linux distro on the 4610-54T with the **48×1G + 10G uplinks
forwarding in hardware** and **L3 routing** (static + FRR/OSPF/BGP), built from
open source — no Cumulus, no proprietary NOS.

The honest headline: **~90% of this is genuinely open and already on disk.** Two
asterisks keep it from being *100% libre*: the kernel isn't mainline-vanilla for
this SoC, and the switch-chip data plane is fundamentally a vendor SDK (no
clean-room libre driver exists for Helix4). Both are *source-available and
redistributable* — same reality every whitebox NOS (ONL, SONiC, Cumulus) lives
with.

---

## The stack, layer by layer

| Layer | What we use | Openness | Status |
|---|---|---|---|
| Routing protocols | **FRR** (or BIRD/Quagga) | GPLv2 — fully libre | Off-the-shelf |
| Userland / distro | Debian armhf or Buildroot | Fully libre | Off-the-shelf |
| Linux kernel | iProc-XGS kernel (ONL ships **4.14**) | GPLv2 — open, **but patched, not mainline** | **Gap A** |
| BDE kernel modules | `linux-kernel-bde`, `linux-user-bde`, dcb modules | GPLv2 | In OpenBCM/OpenMDK |
| Switch data plane (L2+L3) | **OpenBCM** SDK (or OpenMDK + custom L3) | **Broadcom source-available license**, not OSI-libre | **Gap B** |
| SerDes / PHY firmware | Warpcore XGXS ucode + internal SerDes | Broadcom license, **shipped as C source** | On disk (OpenMDK) |
| Platform mgmt (sensors/optics/LED/fan) | ONL ONLP drivers | EPL/open | Already done |

Control-plane → data-plane glue: kernel netlink/FIB → an agent that programs the
chip via the SDK L3 API. We can write a thin agent, or use **SAI + sonic/FRR's
fpmsyncd-style** sync. For a minimal box, a small `bcm_l3_route_add` shim driven
by netlink route events is enough.

---

## Gap A — the kernel is not mainline-vanilla for this SoC

Mainline `CONFIG_ARCH_BCM_IPROC` supports the *router* iProc parts (Cygnus,
Northstar, NSP) — **not** the **XGS switch-CPU iProc** (Hurricane/Helix4/Saber).
So a stock upstream `vmlinux` will not bring up this board's CPU complex, CMICd,
pinctrl, clocks, or the on-die GMAC.

What "fully open-source kernel" actually requires:

- **Path 1 (pragmatic):** use ONL's **GPLv2 iProc 4.14** kernel + the
  `bcm-helix4.dtsi`/`arm-accton-as4610.dts` we already have. It *is* open
  source, just not upstream. **Lowest effort, ships today.**
- **Path 2 (purist):** forward-port the iProc-XGS platform support (mach-bcm
  glue, CMICd, clk/pinctrl, gmac) onto a modern/mainline kernel. Bounded but
  real work; nobody upstream maintains XGS-iProc.

Recommendation: **Path 1 now**, treat Path 2 as an optional cleanup.

## Gap B — there is no libre data-plane driver for Helix4

The BCM56340 is NDA-documented silicon. The *only* way to move packets / program
L3 tables is the Broadcom SDK lineage. We have two open (source-available) forms:

- **OpenBCM 6.5.27** — full `bcm_l3_*` API (route/host/nexthop/ECMP/L3-intf).
  Helix4 chip code is present (`src/soc/esw/helix4.c`, `BCM_56340_A0`), **but
  note: 6.5.27's README lists supported devices as Trident2+/Tomahawk/DNX —
  Helix4 is legacy code carried in-tree, not a listed/tested target.** Expect to
  validate (and possibly back-port from an older SDK that *did* list Helix4).
- **OpenMDK** — natively supports `bcm56340_a0` and **includes the SerDes/PHY
  firmware as source** (`bcmi_warpcore_xgxs_ucode*.c` for the 10G uplinks,
  internal SerDes for the 1G ports, `bcm84xxx_ucode.c` for external PHYs). But
  OpenMDK's BMD is **L2-only** — no L3 API.

So the data-plane choice is:
1. **OpenBCM for L3** (validate Helix4 path), reusing OpenMDK's firmware if
   OpenBCM's Helix4 SerDes init is incomplete; **or**
2. **OpenMDK for ports+SerDes (proven on 56340) + hand-written L3** table
   programming. This is more tractable than it sounds: OpenMDK's **CDK is the
   full silicon source** — every L3 table (`L3_DEFIP`, `L3_ENTRY`,
   `EGR_L3_NEXT_HOP`, `EGR_L3_INTF`, …) defined with **exact field bit layouts**
   (`bcm56340_a0_defs.h`, 2,301 regs / 8,108 symbols), plus the `xgsm` access
   engine to read/write them. Combined with the SCHAN table-insert technique
   already proven in the 5610 project, L3 here is table-fill code, **not** silicon
   RE. See `EXISTING_SOFTWARE_ASSETS.md` § "What OpenMDK contains".

### License reality
Both SDKs and the SerDes firmware are under the **Broadcom/Avago license**:
royalty-free, perpetual, **redistributable including source and derivative
works**. That makes the build *source-available and freely shippable* — but it
is **not** GPL/MIT/Apache, so a strict FSF/OSI "free software" purist cannot call
the data plane libre. **There is no alternative** — no open silicon, no
clean-room driver. This is identical to SONiC/ONL/Cumulus.

---

## Minimum bill of materials to "fully open-source L3 switch"

1. **Distro:** Debian armhf (or ONL/Buildroot) rootfs.
2. **Kernel:** ONL iProc 4.14 + our DTS (Gap A, Path 1). GPLv2.
3. **BDE modules:** build `linux-kernel-bde` + `linux-user-bde` for the 4.14
   kernel.
4. **Data plane:** OpenBCM (Helix4 L3) **or** OpenMDK+custom-L3; + Warpcore
   SerDes firmware (from OpenMDK).
5. **Sync agent:** netlink-FIB → `bcm_l3_route_add` shim (write small, or adopt
   SAI/SONiC sync).
6. **Routing:** FRR for static/OSPF/BGP/VRRP; `zebra` pushes routes to the agent.
7. **Platform:** ONLP drivers (already in tree) for sensors/optics/LED/fan.

## Recommended sequence

1. Bring up Debian armhf + ONL 4.14 kernel on the box (serial + USB boot).
2. Load BDE modules; `bmd_attach` the chip (OpenMDK) — fastest proof of life.
3. **Ports + SerDes:** confirm 1G copper + 10G SFP+ link via OpenMDK (it has the
   firmware). This de-risks the hardest hardware piece early.
4. **L2 switching** working (OpenMDK BMD).
5. **L3:** stand up OpenBCM on the box; program an L3 interface + static route;
   ping *through* the box. (If OpenBCM Helix4 SerDes is incomplete, keep OpenMDK
   for port/SerDes and add L3 table programming.)
6. Wire **FRR → agent → chip**; bring up OSPF/BGP.

> The single biggest unknown to resolve early is **Gap B option 1 vs 2**: does
> OpenBCM 6.5.27 actually init Helix4 ports/SerDes, or do we drive the data plane
> with OpenMDK and bolt on L3? Decide this on the bench in step 3–5.

---

## What is *fully* libre vs source-available (be precise with stakeholders)

- **Fully libre (GPL/EPL/etc.):** distro, kernel, BDE modules, FRR, ONLP. → the
  OS *is* free software.
- **Source-available (Broadcom license, redistributable, not OSI):** the switch
  data-plane SDK + SerDes firmware. → unavoidable for this silicon.

So: a **"fully open-source (source-available), vendor-NOS-free, L3-routing
Linux"** is achievable with what we have. A **100% FSF-libre data plane is not**
— and won't be on any Broadcom switch.

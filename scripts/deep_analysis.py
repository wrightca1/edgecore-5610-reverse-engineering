#!/usr/bin/env python3
"""
Deep analysis of Cumulus's BCM56846 chip state.

Inputs:
  * dump_soc_diff.txt  (6415 line register diff vs chip-reset)
  * regdump_after_round3.out  (our state vs Cumulus, side-by-side)
  * bcm56840_a0_defs.h  (register descriptions)

Outputs:
  * 12_deep_chip_state_analysis.md — markdown writeup
"""
import re, os
from collections import defaultdict, OrderedDict

ROOT = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2"
DIFF = f"{ROOT}/streamed_20260513_162341/soc/dump_soc_diff.txt"
HDR = "/home/smiley/edgecore/newnos/asic/openmdk/cdk/PKG/chip/bcm56840/bcm56840_a0_defs.h"
REGDUMP = "/tmp/regdump.out"  # after-round-3 snapshot
OUT = f"{ROOT}/cumulus_baseline_2013_run2/decoded.md/12_deep_chip_state_analysis.md"
# adjust path — we're already in cumulus_baseline_2013_run2/
OUT = f"{ROOT}/decoded.md/12_deep_chip_state_analysis.md"


def parse_header(path):
    regs = {}
    cur_name = None
    cur = {}
    in_fields = False
    fields = []
    with open(path, encoding="latin-1") as f:
        for line in f:
            ls = line.rstrip("\n")
            if "* REGISTER:" in ls:
                if cur_name and cur:
                    cur["fields"] = "; ".join(fields)
                    regs[cur_name] = cur
                cur_name = ls.split("REGISTER:", 1)[1].strip()
                cur = {"block": "", "desc": "?"}
                fields = []
                in_fields = False
                continue
            if cur_name is None:
                continue
            if "* BLOCKS:" in ls:
                cur["block"] = ls.split("BLOCKS:", 1)[1].strip()
                continue
            if "* DESC:" in ls:
                cur["desc"] = ls.split("DESC:", 1)[1].strip()
                continue
            if "* FIELDS:" in ls:
                in_fields = True
                continue
            if in_fields and ls.startswith(" *"):
                rest = ls.lstrip(" *").rstrip()
                if not rest:
                    in_fields = False
                else:
                    fields.append(rest)
        if cur_name and cur:
            cur["fields"] = "; ".join(fields)
            regs[cur_name] = cur
    return regs


def parse_diff(path):
    """Return per-register info: count of non-default scopes, sample value, set of blocks observed."""
    counts = defaultdict(int)
    samples = {}
    pat = re.compile(r"^(0x[0-9a-fA-F]+)\s+(\w+)(?:\([^)]*\))?\.(\S+)\s*=\s*(0x[0-9a-fA-F]+)")
    with open(path) as f:
        for line in f:
            m = pat.match(line.strip())
            if not m: continue
            addr, name, scope, val = m.groups()
            counts[name] += 1
            if name not in samples:
                # val already has 0x prefix in source diff
                v = val if val.lower().startswith("0x") else "0x" + val
                samples[name] = (v, scope)
    return counts, samples


def parse_regdump(path):
    """Return per-register count of DIFFs."""
    diffs = defaultdict(int)
    cum = {}
    ours = {}
    pat = re.compile(r"^0x[0-9a-f]+ (\S+) cum=0x([0-9a-f]+) ours=0x([0-9a-f]+)( DIFF)?")
    if not os.path.exists(path):
        return diffs, cum, ours
    with open(path) as f:
        for line in f:
            m = pat.match(line.strip())
            if not m: continue
            full, c, o, d = m.groups()
            name = re.sub(r"(\([^)]*\))?\.[a-zA-Z0-9_]+$", "", full)
            if d:
                diffs[name] += 1
            cum.setdefault(name, c)
            ours.setdefault(name, o)
    return diffs, cum, ours


# Pipeline-stage classification heuristic
def classify_stage(name, block):
    nm = name.upper()
    bl = (block or "").upper()
    # MMU
    if bl == "MMU" or nm.startswith(("PG_", "BUFFER_", "OP_", "CFAP", "MMU_", "MCQ", "OVQ",
                                    "S2_", "S3_", "PORT_PG_", "USE_SP_", "ASF_PORT_SPEED",
                                    "MAXBUCKET", "MINBUCKET")):
        return "MMU + scheduler"
    if "PIPE" in bl and "EPIPE" in bl: return "EPIPE (egress)"
    if "IPIPE" in bl:
        # Sub-divide IPIPE
        if any(k in nm for k in ("L3_", "MY_STATION", "ROUTE", "ARP", "ECMP")):
            return "IPIPE — L3 lookup"
        if any(k in nm for k in ("L2_", "MAC_", "VLAN", "STG_TAB", "LPORT_TAB", "EPC_LINK")):
            return "IPIPE — L2 bridging"
        if any(k in nm for k in ("FP_", "IFP", "VFP")):
            return "IPIPE — FP/ACL filter"
        if any(k in nm for k in ("HASH", "RTAG7")):
            return "IPIPE — hash"
        if any(k in nm for k in ("CPU_CONTROL", "PROTOCOL", "TOCPU")):
            return "IPIPE — CPU punt control"
        if "PARITY" in nm: return "parity / ECC init"
        return "IPIPE (other)"
    if bl == "EPIPE": return "EPIPE (egress)"
    if "XLPORT" in bl: return "XLPORT (MAC/SERDES)"
    if any(k in nm for k in ("XMAC_", "XLPORT_", "MAC_", "PFC_", "PAUSE_", "STORM_")):
        return "XLPORT (MAC/SERDES)"
    if "FP_" in nm or "IFP" in nm or "EFP" in nm or "VFP" in nm:
        return "IPIPE — FP/ACL filter"
    if "PARITY" in nm: return "parity / ECC init"
    if any(k in nm for k in ("LOGICAL_TO_PHYSICAL", "MAPPING", "PORT_NUMBER")):
        return "port mapping (read-only)"
    return "(misc)"


def main():
    print("Parsing header for register descriptions...")
    hdr = parse_header(HDR)
    print(f"  {len(hdr)} register descriptions")

    print("Parsing dump_soc_diff for Cumulus's non-default state...")
    counts, samples = parse_diff(DIFF)
    print(f"  {len(counts)} unique register names with non-default values")

    print("Parsing our regdump_after_round3 for current DIFFs...")
    our_diffs, cum_vals, ours_vals = parse_regdump(REGDUMP)
    print(f"  {len(our_diffs)} unique registers still differing")

    # Build per-stage grouping
    stage_regs = defaultdict(list)
    for name, n in counts.items():
        info = hdr.get(name, {})
        stage = classify_stage(name, info.get("block", ""))
        stage_regs[stage].append((name, n, info))

    print(f"\n{len(stage_regs)} pipeline stages identified")

    # Header
    md = []
    md.append("# BCM56846 Deep Chip-State Analysis — Cumulus vs EdgeNOS")
    md.append("")
    md.append("This document analyses every register Cumulus 2.5.0 changes from chip")
    md.append("reset defaults on a working AS5610-52X (data: `dump_soc_diff.txt`,")
    md.append("6,415 register/scope entries) and groups them by chip-pipeline stage,")
    md.append("with cross-reference to what EdgeNOS currently programs.")
    md.append("")
    md.append("**Goal:** identify which subset of Cumulus's chip writes is the gate that")
    md.append("currently keeps frames from being enqueued to the CPU port (CMICm DCB).")
    md.append("")
    md.append(f"**Snapshot date:** 2026-05-14, after 3 rounds of regdump-diff porting.")
    md.append(f"**Total registers Cumulus changes:** {len(counts)}")
    md.append(f"**Total still-DIFF in our chip:** {len(our_diffs)}")
    md.append("")

    # Stage-by-stage breakdown
    md.append("## By pipeline stage")
    md.append("")
    md.append("Rough flow on BCM56846 / Trident+ chip:")
    md.append("")
    md.append("```")
    md.append("        Port MAC → IPIPE (ingress) → MMU → EPIPE (egress) → Port MAC")
    md.append("                  │")
    md.append("                  └─ L2 bridging │ L3 lookup │ FP/ACL │ Hash │ CPU punt")
    md.append("")
    md.append("        MMU = central buffer manager + multi-level scheduler (S2/S3)")
    md.append("              Output queues (per port per CoS) + colour cells + service pools")
    md.append("```")
    md.append("")
    md.append("Below: for each stage, the registers Cumulus changed, with:")
    md.append("- name + brief description")
    md.append("- number of scopes (per-port / per-queue) Cumulus changed it on")
    md.append("- sample Cumulus value vs ours")
    md.append("- whether we still differ")
    md.append("")

    stage_order = [
        "MMU + scheduler",
        "IPIPE — L2 bridging",
        "IPIPE — L3 lookup",
        "IPIPE — FP/ACL filter",
        "IPIPE — hash",
        "IPIPE — CPU punt control",
        "IPIPE (other)",
        "EPIPE (egress)",
        "XLPORT (MAC/SERDES)",
        "port mapping (read-only)",
        "parity / ECC init",
        "(misc)",
    ]
    for stage in stage_order:
        regs = stage_regs.get(stage, [])
        if not regs:
            continue
        total_scopes = sum(n for _, n, _ in regs)
        unique = len(regs)
        diff_count = sum(our_diffs.get(n, 0) for n, _, _ in regs)
        md.append(f"### {stage}")
        md.append("")
        md.append(f"**{unique} unique registers, {total_scopes} scope-writes; "
                  f"~{diff_count} of those still DIFF in our chip.**")
        md.append("")
        md.append("| Register | Scopes | Cumulus | Ours | Description |")
        md.append("|---|--:|---|---|---|")
        regs_sorted = sorted(regs, key=lambda x: -x[1])
        for name, n, info in regs_sorted[:25]:
            samp_val, samp_scope = samples.get(name, ("?", ""))
            our_v = ours_vals.get(name, "?")
            differs = our_diffs.get(name, 0)
            star = "⚠" if differs > 0 else "✓"
            desc = (info.get("desc", "?") or "?")
            desc = desc[:60].replace("|", "\\|").replace("\n", " ")
            # samp_val + our_v already include 0x via 0x...{val} parsing
            samp_disp = samp_val if samp_val.startswith("0x") else "0x" + samp_val
            ours_disp = our_v if our_v.startswith("0x") else "0x" + our_v
            md.append(f"| `{name}` {star} | {n} | `{samp_disp}` | `{ours_disp}` | {desc} |")
        if len(regs) > 25:
            md.append(f"| _...{len(regs) - 25} more registers in this stage..._ | | | | |")
        md.append("")
        md.append("")

    # Critical gates analysis
    md.append("## Critical gates for chip→CPU forwarding")
    md.append("")
    md.append("For a broadcast/unknown-unicast frame to reach the CPU CMICm DCB ring,")
    md.append("every one of these gates must be open at the right time:")
    md.append("")
    md.append("1. **MAC RX accepts frame** — `XMAC_CTRL.RX_EN`, `XLPORT_CONFIG`, MAC SA filtering")
    md.append("2. **IPIPE STP allows ingress** — `STG_TABm.SP_TREE_PORTn` for ingress port")
    md.append("3. **VLAN_TAB has CPU as member** — `VLAN_TABm.PORT_BITMAP`")
    md.append("4. **L2 lookup decides flood-to-VLAN-members** (broadcast)")
    md.append("    OR `MY_STATION_TCAM` hit → `L3_HOST` → next-hop = CPU port")
    md.append("5. **MMU has buffer for CPU queue** — `PG_MIN_CELL`, `OP_QUEUE_CONFIG`, `OP_BUFFER_SHARED_LIMIT`")
    md.append("6. **EPIPE STP allows egress to CPU port** — `EGR_VLAN_STGm.SP_TREE_PORT0`")
    md.append("7. **EPC_LINK_BMAPm has CPU bit set** — chip considers CPU 'link up'")
    md.append("8. **Egress scheduler dequeues CPU port** — `S2_CONFIG`, `S3_CONFIG`, `ESCONFIG`, `COSWEIGHTS`")
    md.append("9. **CMICm DMA armed** — DCB ring set up with `RELOAD=1`, `DESC_HALT_ADDR`")
    md.append("")
    md.append("We've verified 1, 2, 3, 6, 7 directly.  We've ported parts of 5 and 8 but")
    md.append("none are fully matching Cumulus.  9 is done.  4 might fail for L3-routed traffic")
    md.append("if `MY_STATION_TCAM` doesn't match (we program it but the chip-side may have")
    md.append("its own match requirements).")
    md.append("")
    md.append("The most likely current blockers, ranked:")
    md.append("")
    md.append("1. **`*_PARITY_CONTROL` (~103 not ported)** — Cumulus's `parity_enable=1` SDK")
    md.append("   flag triggers init-time writes to enable parity checking on every chip")
    md.append("   memory.  If these aren't init'd, the chip may refuse to enqueue to certain")
    md.append("   memories.  (Speculation; would need to test.)")
    md.append("2. **Per-port `S3_COSWEIGHTS` (928 scopes)** — egress scheduler weights.  Without")
    md.append("   them all set, the scheduler may never select CPU port's queue for dequeue.")
    md.append("3. **`MMU_TO_LOGIC_PORT_MAPPING` (64 scopes)** — MMU's view of port mapping.")
    md.append("   Could differ from OpenMDK's hardcoded mapping → MMU writes go to wrong port.")
    md.append("4. **Memory-table contents** (we haven't touched `dump_socmem_diff.txt`).")
    md.append("   L2 MAC table entries, FP_TCAM rules, VLAN_TAB content.")
    md.append("")

    # Memory-table preview
    md.append("## Memory tables not yet analysed")
    md.append("")
    md.append("Cumulus also writes 1.47 MB worth of chip-memory data (`dump_socmem_diff.txt`)")
    md.append("that our regdump tool doesn't read — it's content of internal SRAMs, not")
    md.append("registers.  These tables back L2 forwarding, FP rules, VLAN membership, etc.")
    md.append("")
    md.append("Important memories to mine:")
    md.append("")
    md.append("- `L2_USER_ENTRY` — static MAC table entries.  Cumulus pre-populates own MAC.")
    md.append("- `VLAN_TABm` — VLAN port bitmaps + STG mapping (we set up VID 1 / 3301+).")
    md.append("- `EGR_VLAN_STGm` — egress STG per VLAN per port (we patched bmd_port_stp_set).")
    md.append("- `STG_TABm` — ingress STG per port.")
    md.append("- `FP_TCAMm` + `FP_POLICY_TABLEm` + `FP_METER_TABLEm` + `FP_GLOBAL_MASK_TCAMm`")
    md.append("  — Cumulus has ~100 FP entries for OSPF/BGP/ICMP/BFD trap rules.")
    md.append("- `EGR_PORTm` + `EGR_VLAN_CONTROLm` — egress port-level config tables.")
    md.append("- `L3_HOSTm` + `L3_DEFIPm` — L3 forwarding tables (we partially program).")
    md.append("- `MY_STATION_TCAM` — chip-side 'my MAC' match table.")
    md.append("")
    md.append("Mining strategy (TODO next-session):")
    md.append("1. Parse `dump_socmem_diff.txt` (1.47 MB; format is similar to register diff).")
    md.append("2. Group by memory name.")
    md.append("3. For each memory, count non-default entries; sample the most-populated.")
    md.append("4. Use OpenMDK's `WRITE_<MEM>m_<FIELD>f_SET` macros to replicate in `edged`.")
    md.append("")

    # Recommendations
    md.append("## Recommended next-day actions, in order")
    md.append("")
    md.append("1. **Port `*_PARITY_CONTROL` writes** (~103 of them, all value 0x1).  Simple")
    md.append("   to add — single bit set per register, no per-port scope.  Cheap test:")
    md.append("   does any chip-level behaviour change?")
    md.append("2. **Compare `bcm56840_a0_p2m` (OpenMDK port map) byte-by-byte with Cumulus's")
    md.append("   `portmap_N.0` from `11ports.bcm`**.  If they differ for swp1/swp2, our")
    md.append("   per-port writes are landing on the wrong chip ports.")
    md.append("3. **Mine `dump_socmem_diff.txt`** for memory-table content; port the L2_USER,")
    md.append("   VLAN_TAB content, and any FP_TCAM trap rules.")
    md.append("4. **Static-RE switchd binary**: find `bcm_init_check` / `bcm_init_selective`")
    md.append("   (visible as strings) and read disassembly.  These are the SDK's top-level")
    md.append("   init entry points called by `bcmcmd init all`.")
    md.append("")

    with open(OUT, "w") as f:
        f.write("\n".join(md))
    print(f"\nWrote {OUT}")
    print(f"  Sections: {len([s for s in stage_order if s in stage_regs])} pipeline stages")
    print(f"  Lines: {len(md)}")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""
Cross-correlate the SOC register dump with:
  * chip-memory dumps  (dump_socmem_diff.txt)
  * raw chip-table dumps (FP_TCAM_raw, L3_*_raw, etc.)
  * our static analysis (edged source code — what we write)

The point: a register doesn't exist in isolation.  Many registers POINT
AT chip memories.  e.g. L3_DEFIP_CONFIG register is a config-knob;
L3_DEFIPm is the memory holding actual route entries.  You can't
understand one without the other.

Builds:
  decoded.md/14_register_memory_code_crosscorrelation.md
"""
import os, re, gzip
from collections import defaultdict, OrderedDict

ROOT = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2"
EDGED = "/home/smiley/edgecore/newnos/asic/edged"
DEFS = "/home/smiley/edgecore/newnos/asic/openmdk/cdk/PKG/chip/bcm56840/bcm56840_a0_defs.h"

SOC_DIFF = f"{ROOT}/streamed_20260513_162341/soc/dump_soc_diff.txt"
SOCMEM_DIFF = f"{ROOT}/streamed_20260513_162341/soc/dump_socmem_diff.txt"
REGDUMP = "/tmp/regdump.out"
OUT = f"{ROOT}/decoded.md/14_register_memory_code_crosscorrelation.md"

def fsize(p):
    try: return os.path.getsize(p)
    except: return 0

# -------- 1. Parse the header for both registers AND memories --------
def parse_header(path):
    items = {}
    cur_name = None
    cur = {}
    in_fields = False
    fields = []
    is_mem = False
    with open(path, encoding="latin-1") as f:
        for line in f:
            ls = line.rstrip("\n")
            if "* REGISTER:" in ls or "* MEMORY:" in ls:
                if cur_name and cur:
                    cur["fields"] = "; ".join(fields)
                    cur["is_mem"] = is_mem
                    items[cur_name] = cur
                if "* REGISTER:" in ls:
                    cur_name = ls.split("REGISTER:", 1)[1].strip()
                    is_mem = False
                else:
                    cur_name = ls.split("MEMORY:", 1)[1].strip()
                    is_mem = True
                cur = {"block": "", "desc": "?"}
                fields = []
                in_fields = False
                continue
            if cur_name is None: continue
            if "* BLOCKS:" in ls:
                cur["block"] = ls.split("BLOCKS:", 1)[1].strip(); continue
            if "* DESC:" in ls:
                cur["desc"] = ls.split("DESC:", 1)[1].strip(); continue
            if "* FIELDS:" in ls:
                in_fields = True; continue
            if in_fields and ls.startswith(" *"):
                rest = ls.lstrip(" *").rstrip()
                if not rest: in_fields = False
                else: fields.append(rest)
        if cur_name and cur:
            cur["fields"] = "; ".join(fields)
            cur["is_mem"] = is_mem
            items[cur_name] = cur
    return items

# -------- 2. Parse the diffs --------
def parse_reg_diff(path):
    """register-diff format: '0xADDR NAME.scope = 0xVAL'"""
    counts = defaultdict(int)
    sample_val = {}
    pat = re.compile(r"^(0x[0-9a-fA-F]+)\s+(\w+)(?:\([^)]*\))?\.(\S+)\s*=\s*(0x[0-9a-fA-F]+)")
    with open(path, encoding="latin-1") as f:
        for line in f:
            m = pat.match(line.strip())
            if not m: continue
            _, name, _, val = m.groups()
            counts[name] += 1
            sample_val.setdefault(name, val)
    return counts, sample_val

def parse_mem_diff(path):
    """memory-diff format: 'MEMNAME.scope[idx]: <FIELDS>'"""
    counts = defaultdict(int)
    sample_val = {}
    pat = re.compile(r"^\s*(\w+)\.\w+\[\d+\]:\s*<([^>]*)>")
    with open(path, encoding="latin-1") as f:
        for line in f:
            m = pat.match(line)
            if not m: continue
            name, fields = m.groups()
            counts[name] += 1
            sample_val.setdefault(name, fields[:80])
    return counts, sample_val

# -------- 3. Scan our edged source for writes/reads of each register/memory --------
def scan_edged():
    refs = defaultdict(set)
    for fn in os.listdir(EDGED):
        if not fn.endswith(".c"): continue
        with open(os.path.join(EDGED, fn), encoding="latin-1") as f:
            text = f.read()
        # WRITE_X / READ_X — registers (r) and memories (m)
        for m in re.finditer(r"\b(?:WRITE|READ)_(\w+?)[rm]\s*\(", text):
            refs[m.group(1)].add(fn)
    return refs

# -------- 4. Inventory raw table-dump files in captures --------
def inventory_raw_tables():
    """Find raw chip-table dumps with their underlying chip-memory name."""
    out = defaultdict(list)  # mem-name -> [paths]
    interesting_dirs = [
        f"{ROOT}/deep_mine_20260513_191506",
        f"{ROOT}/trace_hash_redo",
        f"{ROOT}/finish_20260513_203818",
    ]
    for d in interesting_dirs:
        if not os.path.isdir(d): continue
        for fn in os.listdir(d):
            for mem in ("FP_TCAM", "FP_POLICY_TABLE", "FP_METER_TABLE",
                        "FP_COUNTER_TABLE", "FP_GLOBAL_MASK_TCAM",
                        "L3_DEFIP", "L3_ENTRY", "L3_ENTRY_IPV4_UNICAST",
                        "EGR_L3_NEXT_HOP", "ING_L3_NEXT_HOP", "L3_ECMP",
                        "MY_STATION_TCAM", "VLAN_TAB", "EGR_VLAN",
                        "MCS"):
                if mem in fn.upper():
                    out[mem].append(os.path.relpath(os.path.join(d, fn), ROOT))
                    break
    return out


# -------- 5. Group registers + memories by subsystem --------
def subsystem(name, block):
    nm = name.upper()
    bl = (block or "").upper()
    if nm.startswith(("FP_", "IFP_", "EFP_", "VFP_")):
        return "FP / ACL"
    if "L3_DEFIP" in nm or "L3_ENTRY" in nm or "L3_NEXT_HOP" in nm \
       or "L3_ECMP" in nm or "MY_STATION" in nm or "L3_HOST" in nm \
       or "L3_TUNNEL" in nm or nm.startswith("L3_"):
        return "L3 forwarding"
    if nm.startswith("L2_") or "L2_USER" in nm or "L2_MOD" in nm:
        return "L2 / MAC table"
    if "VLAN_TAB" in nm or "EGR_VLAN" in nm or "LPORT_TAB" in nm \
       or "STG_TAB" in nm or "PORT_TAB" in nm:
        return "VLAN / STP / port-tab"
    if nm.startswith(("EPC_", "EPIPE_")):
        return "EPC / egress port"
    if "MCS" in nm or "MICROCONTROL" in nm: return "MCS / uC"
    if bl == "MMU" or nm.startswith(("PG_", "OP_", "BUFFER_", "MMU_", "CFAP", "MCQ", "OVQ", "PORT_PG_")):
        return "MMU"
    if "XLPORT" in bl or nm.startswith(("XMAC_", "XLPORT_", "MAC_")):
        return "XLPORT MAC"
    if "HASH" in nm or "RTAG7" in nm: return "Hash / RTAG7"
    if "CPU_CONTROL" in nm or "PROTOCOL_PKT" in nm or "TOCPU" in nm:
        return "CPU punt control"
    if "PARITY" in nm: return "Parity init"
    if "MAPPING" in nm or "LOGICAL_TO_PHYSICAL" in nm:
        return "Port mapping"
    return "(misc)"


def main():
    print("Parsing header...")
    hdr = parse_header(DEFS)
    regs = {n: v for n, v in hdr.items() if not v.get("is_mem")}
    mems = {n: v for n, v in hdr.items() if v.get("is_mem")}
    print(f"  {len(regs)} registers + {len(mems)} memories defined in header")

    print("Parsing SOC register diff...")
    reg_counts, reg_samples = parse_reg_diff(SOC_DIFF)
    print(f"  {len(reg_counts)} unique registers Cumulus changed")

    print("Parsing SOC MEMORY diff...")
    mem_counts, mem_samples = parse_mem_diff(SOCMEM_DIFF)
    print(f"  {len(mem_counts)} unique memories Cumulus populated")

    print("Scanning edged source for our static refs...")
    refs = scan_edged()
    print(f"  {len(refs)} unique register/memory names referenced in edged")

    print("Cataloging raw chip-table dump files...")
    raw_files = inventory_raw_tables()
    print(f"  {len(raw_files)} memory names have raw dump files in captures")

    # Build per-subsystem grouping
    grp = defaultdict(lambda: {"regs": [], "mems": []})
    for name, info in regs.items():
        if name in reg_counts:
            sub = subsystem(name, info.get("block", ""))
            grp[sub]["regs"].append(name)
    for name, info in mems.items():
        # Some mems are referenced without trailing m? Try both ways
        nm_clean = name.rstrip("m")  # drop trailing 'm' if present in lookup
        # mem diff names match the symbol with the 'm' suffix sometimes
        # Take EITHER the with-m or without-m count
        c1 = mem_counts.get(name, 0)
        c2 = mem_counts.get(nm_clean, 0)
        c = max(c1, c2)
        if c > 0:
            sub = subsystem(name, info.get("block", ""))
            grp[sub]["mems"].append(name)

    # Also memories that Cumulus has but aren't in our header lookup
    all_mem_names = set(mems.keys())
    for n in mem_counts:
        if n in all_mem_names: continue
        # Add to (misc)
        grp[subsystem(n, "")]["mems"].append(n)

    md = []
    md.append("# Cross-Correlation: SOC Registers × Chip Memories × Raw Dumps × Our Code")
    md.append("")
    md.append("This document ties together, for each chip subsystem:")
    md.append("- the **registers** Cumulus changed (`dump_soc_diff.txt`)")
    md.append("- the **memories** Cumulus populated (`dump_socmem_diff.txt`)")
    md.append("- the **raw chip-table dumps** captured separately (FP_TCAM, L3_DEFIP, etc.)")
    md.append("- **what `asic/edged/*.c` writes** (our static side)")
    md.append("")
    md.append("Registers are config-knobs (typically global or per-port);")
    md.append("memories are tables with multiple entries (e.g. routes, MAC table, FP rules).")
    md.append("A subsystem only works if both are programmed.  Until now we've been")
    md.append("looking at register diffs in isolation — this doc tracks the *pair*.")
    md.append("")
    md.append(f"**Header symbols:** {len(regs)} regs + {len(mems)} mems")
    md.append(f"**Cumulus reg diff:** {len(reg_counts)} regs")
    md.append(f"**Cumulus mem diff:** {len(mem_counts)} mems")
    md.append(f"**Edged-source refs:** {len(refs)}")
    md.append("")
    md.append("## Per-subsystem cross-correlation")
    md.append("")

    sub_order = [
        "L3 forwarding", "L2 / MAC table", "VLAN / STP / port-tab",
        "FP / ACL", "EPC / egress port", "MMU",
        "XLPORT MAC", "Hash / RTAG7", "CPU punt control",
        "MCS / uC", "Port mapping", "Parity init", "(misc)",
    ]
    for sub in sub_order:
        info = grp.get(sub, {"regs": [], "mems": []})
        regs_l = sorted(info["regs"])
        mems_l = sorted(info["mems"])
        if not regs_l and not mems_l: continue

        md.append(f"### {sub}")
        md.append("")

        # Registers in this subsystem
        if regs_l:
            md.append(f"**Registers ({len(regs_l)}):**")
            md.append("")
            md.append("| Register | Cumulus scopes | Sample value | Our code refs |")
            md.append("|---|--:|---|---|")
            for n in sorted(regs_l, key=lambda x: -reg_counts.get(x, 0))[:15]:
                cnt = reg_counts.get(n, 0)
                val = reg_samples.get(n, "?")
                if not val.startswith("0x"): val = "0x" + val
                our = ", ".join(sorted(refs.get(n, set()))) or "—"
                md.append(f"| `{n}` | {cnt} | `{val}` | {our[:30]} |")
            if len(regs_l) > 15:
                md.append(f"| _...{len(regs_l)-15} more_ | | | |")
            md.append("")

        # Memories in this subsystem
        if mems_l:
            md.append(f"**Memories ({len(mems_l)}):**")
            md.append("")
            md.append("| Memory | Cumulus entries | Sample row fields | Raw dump file? | Our code refs |")
            md.append("|---|--:|---|---|---|")
            for n in sorted(mems_l, key=lambda x: -max(mem_counts.get(x, 0), mem_counts.get(x.rstrip("m"), 0)))[:15]:
                c1 = mem_counts.get(n, 0)
                c2 = mem_counts.get(n.rstrip("m"), 0)
                cnt = max(c1, c2)
                sample = mem_samples.get(n, mem_samples.get(n.rstrip("m"), ""))[:60]
                # Find any raw-table dump file
                raw_hits = []
                for k, paths in raw_files.items():
                    if k in n.upper() or n.rstrip("m").upper().startswith(k):
                        raw_hits.extend(paths)
                raw_disp = ", ".join(raw_hits[:1]) if raw_hits else "—"
                our = ", ".join(sorted(refs.get(n, set()) | refs.get(n.rstrip("m"), set()))) or "—"
                md.append(f"| `{n}` | {cnt} | `{sample}` | `{raw_disp[:40]}` | {our[:30]} |")
            if len(mems_l) > 15:
                md.append(f"| _...{len(mems_l)-15} more_ | | | | |")
            md.append("")

        md.append("")

    md.append("## Summary by subsystem")
    md.append("")
    md.append("| Subsystem | Cumulus regs / mems | Our edged regs / mems | Match status |")
    md.append("|---|---|---|---|")
    for sub in sub_order:
        info = grp.get(sub, {"regs": [], "mems": []})
        regs_l = info["regs"]; mems_l = info["mems"]
        if not regs_l and not mems_l: continue
        # Count what edged writes
        our_regs = sum(1 for n in regs_l if n in refs)
        our_mems = sum(1 for n in mems_l if (n in refs or n.rstrip("m") in refs))
        total_regs = len(regs_l)
        total_mems = len(mems_l)
        # Match status
        if total_mems > 0 and our_mems == 0:
            status = "❌ no memory writes"
        elif our_regs == 0 and our_mems == 0:
            status = "❌ untouched"
        elif our_regs == total_regs and our_mems == total_mems:
            status = "✅ all writes covered"
        else:
            status = f"⚠ {our_regs}/{total_regs} regs, {our_mems}/{total_mems} mems"
        md.append(f"| **{sub}** | {total_regs} / {total_mems} | {our_regs} / {our_mems} | {status} |")
    md.append("")

    md.append("## What this surfaces")
    md.append("")
    md.append("Reading the per-subsystem tables above, the categories where Cumulus has")
    md.append("**memory entries** (not just register values) that we haven't touched stand out.")
    md.append("These are tables with *content* — chip rows that contain forwarding rules,")
    md.append("not just configuration flags.  In particular:")
    md.append("")
    md.append("- **L3 forwarding memories**: Cumulus has populated L3_DEFIPm, L3_ENTRY_IPV4_UNICASTm,")
    md.append("  EGR_L3_NEXT_HOPm, ING_L3_NEXT_HOPm, L3_ECMPm, MY_STATION_TCAMm with actual *routes*.")
    md.append("  Our edged programs L3_HOST + MY_STATION_TCAM via OpenMDK BMD APIs.")
    md.append("  Cross-reference with the raw dumps in `deep_mine_*/12d_*` and `trace_hash_redo/11*-12*` —")
    md.append("  those have the ACTUAL chip rows Cumulus had at capture time.")
    md.append("")
    md.append("- **FP / ACL memories**: Cumulus has FP_TCAMm + FP_POLICY_TABLEm + FP_METER_TABLEm with")
    md.append("  the OSPF/BGP/ICMP/BFD CPU-trap rules.  Our edged writes ZERO FP entries.")
    md.append("  Raw dumps: `deep_mine_*/09_FP_*_raw.txt`.")
    md.append("")
    md.append("- **VLAN / STP memories**: VLAN_TABm content per VID (we partially write via BMD),")
    md.append("  EGR_VLANm (we partially write), LPORT_TABm (we write V4/V6_L3_ENABLE + VT_ENABLE=0),")
    md.append("  STG_TABm (we set FORWARDING via the patched bmd_port_stp_set).")
    md.append("")
    md.append("- **MMU memories**: VAST.  OP_QUEUE_CONFIG_CELLm, PG_*_CELLm, BUFFER_*m all live as")
    md.append("  per-port-per-queue entries.  We write some via direct CDK macros in datapath_rc_full.")
    md.append("")
    md.append("- **EPC / egress-port memories**: EGR_PORTm per port — egress-side port config.")
    md.append("  This is where Cumulus stores per-port egress rules.  We don't write to it.")
    md.append("")

    md.append("## How to use this for the chip→CPU drop")
    md.append("")
    md.append("1. Pick the subsystem that's most likely the silent-drop cause (e.g. EPC / FP / L2).")
    md.append("2. Open the per-subsystem table above; identify a specific memory or register that's")
    md.append("   non-zero in Cumulus but zero in our edged.")
    md.append("3. Open the raw dump file referenced (e.g. `deep_mine_*/09_FP_TCAM_raw.txt`).")
    md.append("4. Use OpenMDK's `WRITE_<MEMNAME>m` (or `bmd_*` API) to populate the equivalent")
    md.append("   row in `asic/edged/datapath.c` or a new module.")
    md.append("5. Re-run regdump + ping test.")
    md.append("")
    md.append("This doc is the index; the per-row work is straight implementation.")
    md.append("")

    with open(OUT, "w") as f:
        f.write("\n".join(md))
    print(f"Wrote {OUT}")
    print(f"Lines: {len(md)}")
    print()
    # Quick summary at console
    print("Subsystem summary:")
    for sub in sub_order:
        info = grp.get(sub, {"regs": [], "mems": []})
        if not info["regs"] and not info["mems"]: continue
        our_regs = sum(1 for n in info["regs"] if n in refs)
        our_mems = sum(1 for n in info["mems"] if (n in refs or n.rstrip("m") in refs))
        print(f"  {sub:30s} regs {our_regs:3d}/{len(info['regs']):3d}  "
              f"mems {our_mems:3d}/{len(info['mems']):3d}")


if __name__ == "__main__":
    main()

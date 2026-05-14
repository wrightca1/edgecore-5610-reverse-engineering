#!/usr/bin/env python3
"""
Cross-reference Cumulus's dump_soc_diff.txt with the BCM56840 header
descriptions and our edged datapath.c.  Streaming line-by-line parser
(the regex-based version OOM'd on the 5 MB header).

Output: CSV with one row per unique register from the diff.
"""
import re
import csv
import os
from collections import defaultdict

HDR = "/home/smiley/edgecore/newnos/asic/openmdk/cdk/PKG/chip/bcm56840/bcm56840_a0_defs.h"
DIFF = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/streamed_20260513_162341/soc/dump_soc_diff.txt"
EDGED_DIR = "/home/smiley/edgecore/newnos/asic/edged/"
OUT = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/decoded.md/cumulus_register_analysis.csv"


def parse_header(path):
    """Streaming parser: walk lines, build per-register info."""
    regs = {}
    cur_name = None
    cur = {}
    in_fields = False
    fields = []
    with open(path, encoding="latin-1") as f:
        for line in f:
            ls = line.rstrip("\n")
            if "* REGISTER:" in ls:
                # commit previous if any
                if cur_name and cur:
                    cur["fields"] = "; ".join(fields)
                    regs[cur_name] = cur
                cur_name = ls.split("REGISTER:", 1)[1].strip()
                cur = {"block": "", "desc": "?", "address": ""}
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
                continue
            # detect address #define line
            m = re.match(rf"^#define BCM56840_A0_{re.escape(cur_name)}[rm]? (0x[0-9a-fA-F]+)", ls)
            if m:
                cur["address"] = m.group(1).lower()
                in_fields = False
        # last
        if cur_name and cur:
            cur["fields"] = "; ".join(fields)
            regs[cur_name] = cur
    return regs


def parse_diff(path):
    """Return dict: regname -> (scope_count, sample_value)."""
    counts = defaultdict(int)
    samples = {}
    pat = re.compile(
        r"^(0x[0-9a-fA-F]+)\s+(\w+)(?:\([^)]*\))?\.\S+\s*=\s*(0x[0-9a-fA-F]+)"
    )
    with open(path) as f:
        for line in f:
            m = pat.match(line.strip())
            if not m:
                continue
            _addr, name, val = m.groups()
            counts[name] += 1
            if name not in samples:
                samples[name] = val
    return counts, samples


def find_ported(edged_dir):
    ported = set()
    for fn in os.listdir(edged_dir):
        if not fn.endswith(".c"):
            continue
        with open(os.path.join(edged_dir, fn), encoding="latin-1") as f:
            text = f.read()
        for m in re.finditer(r"WRITE_(\w+?)[rm]\s*\(", text):
            ported.add(m.group(1))
    return ported


def importance_guess(name, block, desc):
    nm = name.upper()
    bl = (block or "").upper()
    high_keywords = [
        "EPC_LINK", "CPU_CONTROL", "USE_SP_SHARED", "OP_BUFFER",
        "PG_MIN", "PG_SHARED", "BUFFER_CELL_LIMIT", "OP_QUEUE_CONFIG",
        "COSMASK", "STG_TAB", "LPORT_TAB", "PORT_PG_SPID", "MY_STATION",
        "L3_HOST", "ROUTE", "CMC_", "AUX_ARB_CONTROL", "ING_COS_MODE",
        "OP_VOQ_PORT_CONFIG", "ES_TDM_CONFIG", "ES_QUEUE_TO_PRIO",
        "ESCONFIG", "S2_CONFIG", "S3_CONFIG", "PORT_MAX_PKT_SIZE",
    ]
    med_keywords = [
        "COSWEIGHTS", "MINSPCONFIG", "S2_S3_ROUTING", "CPU_COS_MAP",
        "ING_PRI_CNG_MAP", "PORT_PRI", "PRIO2COS", "RTAG7", "HASH_CONTROL",
    ]
    if "RDBGC" in nm or "TDBGC" in nm or "MAC_RSV" in nm:
        return "medium (diag/counter)"
    for kw in high_keywords:
        if kw in nm:
            return "HIGH (data path)"
    for kw in med_keywords:
        if kw in nm:
            return "medium (QoS / hash)"
    if "IFP" in nm or "EFP" in nm or "VFP" in nm or "FP_" in nm:
        return "medium (ACL / filter)"
    if bl == "MMU":
        return "medium (MMU)"
    if "MIB" in nm or "STAT" in nm or "DBG" in nm:
        return "low (statistics)"
    if "PARITY" in nm or "ECC" in nm:
        return "low (parity init)"
    return "unknown"


def main():
    print("Parsing BCM56840 header (streaming)...")
    hdr_regs = parse_header(HDR)
    print(f"  {len(hdr_regs)} register descriptions parsed")

    print("Reading Cumulus dump_soc_diff.txt...")
    counts, samples = parse_diff(DIFF)
    print(f"  {len(counts)} unique register names with non-default values")

    print("Finding registers we already WRITE_ in edged sources...")
    ported = find_ported(EDGED_DIR)
    print(f"  {len(ported)} unique register/memory names referenced in edged")

    print(f"Writing {OUT}...")
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow([
            "register", "block", "description", "fields",
            "scope_count", "sample_value", "ported_by_us",
            "importance_guess", "address",
        ])
        for name in sorted(counts.keys()):
            info = hdr_regs.get(name, {})
            w.writerow([
                name,
                info.get("block", ""),
                info.get("desc", "?"),
                info.get("fields", ""),
                counts[name],
                samples[name],
                "yes" if name in ported else "no",
                importance_guess(name, info.get("block", ""), info.get("desc", "")),
                info.get("address", ""),
            ])

    by_imp = defaultdict(int)
    by_imp_ported = defaultdict(int)
    for name in counts:
        info = hdr_regs.get(name, {})
        imp = importance_guess(name, info.get("block", ""), info.get("desc", ""))
        by_imp[imp] += 1
        if name in ported:
            by_imp_ported[imp] += 1

    print()
    print("Summary by importance category:")
    print(f"  {'category':40s} {'total':>6s}  {'ported':>6s}  {'gap':>6s}")
    for imp in sorted(by_imp.keys(), key=lambda k: -by_imp[k]):
        total = by_imp[imp]
        p = by_imp_ported[imp]
        print(f"  {imp:40s} {total:6d}  {p:6d}  {total - p:6d}")
    tot = sum(by_imp.values())
    pt = sum(by_imp_ported.values())
    print(f"  {'TOTAL':40s} {tot:6d}  {pt:6d}  {tot - pt:6d}")


if __name__ == "__main__":
    main()

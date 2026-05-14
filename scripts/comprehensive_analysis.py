#!/usr/bin/env python3
"""
Comprehensive analysis of ALL the captured Cumulus baseline data.

Walks the entire cumulus_baseline_2013_run2/ tree, categorizes every
artefact by purpose, summarizes content (counts, key contents, cross-
references), and writes a structured markdown synthesis.

Sections:
 1. Capture inventory (every file, by category)
 2. Chip registers (already analyzed in doc 12)
 3. Chip memories — the big unexplored corpus
 4. Chip L3 forwarding tables
 5. Chip FP (Field Processor) TCAM rules  ← CPU punt rules!
 6. Chip MCS (MicroController) RAM
 7. DMA region content
 8. Switchd binary + gcore + libs
 9. Kernel state, system config, network config
10. What this all tells us about chip→CPU
"""
import os, re, gzip, sys
from collections import defaultdict

ROOT = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2"
OUT = f"{ROOT}/decoded.md/13_comprehensive_capture_analysis.md"

def fsz(path):
    try: return os.path.getsize(path)
    except OSError: return 0

def hsize(n):
    for u in ["B", "KB", "MB", "GB"]:
        if n < 1024: return f"{n:.0f} {u}"
        n /= 1024
    return f"{n:.0f} TB"

def count_lines(path):
    try:
        with open(path, "rb") as f:
            return sum(1 for _ in f)
    except OSError: return 0

def count_lines_gz(path):
    try:
        with gzip.open(path, "rb") as f:
            return sum(1 for _ in f)
    except OSError: return 0

def first_lines(path, n=20):
    try:
        with open(path, encoding="latin-1") as f:
            return [next(f).rstrip() for _ in range(n)]
    except StopIteration:
        return []
    except OSError: return []

# Inventory
inventory = defaultdict(list)  # category -> [(path, size, lines, hint)]

# Walk capture tree
for root, dirs, files in os.walk(ROOT):
    # Skip our decoded.md and scripts output
    if "/decoded.md" in root: continue
    if root.endswith(".tgz_unpack"): continue
    for fn in files:
        if fn.startswith("."): continue
        path = os.path.join(root, fn)
        sz = fsz(path)
        rel = os.path.relpath(path, ROOT)
        low = fn.lower()

        # Categorize
        if "dump_soc.txt" in fn:
            inventory["chip-registers"].append((rel, sz, "all 49,732 register values"))
        elif "dump_soc_diff" in fn:
            inventory["chip-registers"].append((rel, sz, "6,415 registers != reset default"))
        elif "dump_socmem" in fn:
            inventory["chip-memories"].append((rel, sz, "chip memory-table content"))
        elif "FP_" in fn:
            inventory["FP-TCAM"].append((rel, sz, "Field Processor rules / counters / meters"))
        elif "L3_" in fn or "DEFIP" in fn or "L3_ENTRY" in fn:
            inventory["L3-tables"].append((rel, sz, "L3 forwarding entries"))
        elif "EGR_L3" in fn or "ING_L3" in fn or "L3_ECMP" in fn:
            inventory["L3-tables"].append((rel, sz, "L3 next-hop / ECMP"))
        elif "dump_mcs" in fn:
            inventory["MCS-firmware"].append((rel, sz, "chip MicroController RAM"))
        elif "dma_region" in fn or "dma_first" in fn:
            inventory["DMA-region"].append((rel, sz, "host DMA buffer pool"))
        elif "switchd" in low and (sz > 1_000_000 or "core" in low):
            inventory["switchd-binary"].append((rel, sz, "switchd binary / gcore"))
        elif fn == "switchd" and sz > 0:
            inventory["switchd-binary"].append((rel, sz, "switchd binary"))
        elif "kallsyms" in fn or "System.map" in fn:
            inventory["kernel-symbols"].append((rel, sz, "kernel symbol map"))
        elif "strace" in fn:
            inventory["strace"].append((rel, sz, "syscall trace"))
        elif fn.endswith(".bcm") or "rc.soc" in fn or "rc.led" in fn or \
             "rc.ports" in fn or "rc.forwarding" in fn or "rc.phy" in fn or \
             "rc.datapath" in fn:
            inventory["bcmcmd-rc-files"].append((rel, sz, "bcmcmd init script"))
        elif "config.bcm" in fn:
            inventory["bcmcmd-rc-files"].append((rel, sz, "SDK runtime config"))
        elif fn.startswith("9") and "bdgcN" in fn:
            inventory["bcmcmd-rc-files"].append((rel, sz, "rc.forwarding-style script"))
        elif "porttab" in fn or "phytab" in fn or "sfptab" in fn:
            inventory["port-tabs"].append((rel, sz, "port/phy/sfp lookup tables"))
        elif "/cpld" in root or "cpld" in low:
            inventory["cpld-thermal"].append((rel, sz, "CPLD/thermal/PSU state"))
        elif "/thermal" in root or "thermal" in low:
            inventory["cpld-thermal"].append((rel, sz, "thermal state"))
        elif "/sfp" in root or "sfp_" in low or "/eeprom" in root:
            inventory["sfp-eeprom"].append((rel, sz, "SFP transceiver EEPROM"))
        elif "/procfs" in root:
            inventory["procfs"].append((rel, sz, "/proc snapshot"))
        elif "/sysfs" in root:
            inventory["sysfs"].append((rel, sz, "/sys snapshot"))
        elif "iptables" in fn or "tc_" in fn or "tc -" in fn:
            inventory["iptables-tc"].append((rel, sz, "kernel netfilter / tc state"))
        elif "/vtysh" in root or "show_ip" in fn or "vtysh" in fn:
            inventory["vtysh-routing"].append((rel, sz, "Quagga vtysh state"))
        elif "/quagga" in root or "/etc/quagga" in path:
            inventory["quagga-config"].append((rel, sz, "Quagga daemon config"))
        elif "knet" in low or "/knet" in root:
            inventory["knet"].append((rel, sz, "kernel network driver state"))
        elif "/bar0" in root or "/bar" in root:
            inventory["BAR0-dump"].append((rel, sz, "PCI BAR0 raw memory"))
        elif "/bde" in root:
            inventory["BDE-driver"].append((rel, sz, "BDE driver state"))
        elif "/modules" in root:
            inventory["kernel-modules"].append((rel, sz, "loaded kernel module"))
        elif "/cumulus_cfg" in root or "/cumulus/" in root or "/etc/" in path:
            inventory["cumulus-config"].append((rel, sz, "Cumulus config file"))
        elif "show_" in fn or "/tables" in root or "_diag_" in fn:
            inventory["bcmcmd-table-dumps"].append((rel, sz, "bcmcmd-output snapshot"))
        elif "PRBS" in fn or "phy_diag" in fn or "phy_cl45" in fn or "phy_raw" in fn:
            inventory["phy-diag"].append((rel, sz, "PHY-level diagnostic"))
        elif fn.endswith(".log") and sz > 100:
            inventory["misc-logs"].append((rel, sz, "log file"))
        elif fn.endswith(".bin"):
            inventory["misc-bin"].append((rel, sz, "binary"))
        elif fn.endswith(".tgz"):
            inventory["tarballs-rolled-up"].append((rel, sz, "(already-unpacked tarball)"))
        else:
            inventory["misc"].append((rel, sz, ""))

# Specific analyses
def analyze_socmem():
    """The big unexplored corpus."""
    path = f"{ROOT}/streamed_20260513_162341/soc/dump_socmem_diff.txt"
    if not os.path.exists(path):
        return None
    sz = fsz(path)
    nlines = count_lines(path)
    # Sample: count by memory name
    mem_counts = defaultdict(int)
    with open(path, encoding="latin-1") as f:
        for line in f:
            # 0xADDR MEM_NAME[idx].scope = 0xDATA
            m = re.match(r"^0x[0-9a-f]+\s+(\w+)", line.strip())
            if m: mem_counts[m.group(1)] += 1
    return {
        "size": sz,
        "lines": nlines,
        "unique_mems": len(mem_counts),
        "top_mems": sorted(mem_counts.items(), key=lambda x: -x[1])[:20],
    }

def analyze_fp_tcam():
    """FP_TCAM is where Cumulus's CPU-trap rules live."""
    paths = [
        f"{ROOT}/deep_mine_20260513_191506/09_FP_TCAM_raw.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_FP_POLICY_TABLE_raw.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_FP_METER_TABLE_raw.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_FP_COUNTER_TABLE_raw.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_FP_GLOBAL_MASK_TCAM_raw.txt",
    ]
    info = {}
    for p in paths:
        if not os.path.exists(p): continue
        nm = os.path.basename(p).replace("09_", "").replace("_raw.txt", "")
        nlines = count_lines(p)
        nonempty_entries = 0
        with open(p, encoding="latin-1") as f:
            for line in f:
                # Trident dump shows entries by index with non-zero data
                if "VALID" in line or "valid=1" in line or "data:" in line:
                    nonempty_entries += 1
        info[nm] = {"size": fsz(p), "lines": nlines, "entries": nonempty_entries}
    return info

def analyze_fp_show():
    """fp_show output — human-readable FP rule summary."""
    paths = [
        f"{ROOT}/deep_mine_20260513_191506/09_fp_show_all.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_fp_show_group.txt",
        f"{ROOT}/deep_mine_20260513_191506/09_fp_show_stats.txt",
    ]
    out = {}
    for p in paths:
        if not os.path.exists(p): continue
        nm = os.path.basename(p)
        out[nm] = {"size": fsz(p), "lines": count_lines(p),
                   "first_lines": first_lines(p, 6)}
    return out

def analyze_l3_tables():
    paths = {
        "L3_DEFIP_after": f"{ROOT}/trace_hash_redo/11d_L3_DEFIP_raw_after.txt",
        "L3_ENTRY_after": f"{ROOT}/trace_hash_redo/12b_L3_ENTRY_raw_after.txt",
        "EGR_L3_NEXT_HOP_after": f"{ROOT}/trace_hash_redo/11d_EGR_L3_NEXT_HOP_after.txt",
        "ING_L3_NEXT_HOP_after": f"{ROOT}/trace_hash_redo/11d_ING_L3_NEXT_HOP_after.txt",
        "L3_ECMP_after": f"{ROOT}/trace_hash_redo/11d_L3_ECMP_after.txt",
        "L3_ENTRY_IPV4_UC": f"{ROOT}/deep_mine_20260513_191506/12d_L3_ENTRY_IPV4_UNICAST_raw.txt",
    }
    out = {}
    for name, p in paths.items():
        if not os.path.exists(p): continue
        nlines = count_lines(p)
        valid = 0
        with open(p, encoding="latin-1") as f:
            for line in f:
                if "VALID" in line or "valid=1" in line:
                    valid += 1
        out[name] = {"size": fsz(p), "lines": nlines, "valid_entries": valid}
    return out

def analyze_mcs():
    path = f"{ROOT}/deep_mine_20260513_191506/01_dump_mcs.txt"
    if not os.path.exists(path):
        return None
    return {"size": fsz(path), "lines": count_lines(path),
            "first": first_lines(path, 8)}

def analyze_strace():
    p = f"{ROOT}/finish_20260513_203818/a1_init_strace.log"
    sp = f"{ROOT}/finish_20260513_203818/a3_switchd_strace.log"
    out = {}
    for name, path in [("init", p), ("runtime", sp)]:
        if not os.path.exists(path): continue
        out[name] = {"size": fsz(path), "lines": count_lines(path)}
    return out

# Now write the markdown
md = []
md.append("# Comprehensive Cumulus Capture Analysis — Everything We Have")
md.append("")
md.append("Inventory of every artefact in `cumulus_baseline_2013_run2/` (and its")
md.append("decoded contents), grouped by purpose, with cross-reference to what we've")
md.append("used / not used so far in the EdgeNOS chip→CPU forwarding investigation.")
md.append("")
md.append("**Date:** 2026-05-14, end-of-session.")
md.append("**Prior docs:**")
md.append("- `decoded.md/01_route_storage.md` ... `decoded.md/09_capture_plan.md` — earlier per-topic decodings.")
md.append("- `decoded.md/10_cumulus_register_analysis.md` — register-gap CSV summary.")
md.append("- `decoded.md/11_session_2026_05_14_summary.md` — session writeup.")
md.append("- `decoded.md/12_deep_chip_state_analysis.md` — chip-register diff by pipeline stage.")
md.append("")
md.append("This doc (`13_...`) covers EVERYTHING ELSE — memories, FP rules, L3 tables, MCS, DMA, BAR0,")
md.append("strace, switchd internals, etc. — not just the chip register diff.")
md.append("")

# 1. Top-level inventory table
md.append("## 1. Capture inventory")
md.append("")
md.append("| Category | Files | Bytes | What it contains |")
md.append("|---|--:|--:|---|")
total = 0
total_files = 0
for cat in sorted(inventory.keys()):
    items = inventory[cat]
    nf = len(items)
    sz = sum(s for _, s, _ in items)
    total += sz
    total_files += nf
    hint = items[0][2] if items else ""
    md.append(f"| **{cat}** | {nf} | {hsize(sz)} | {hint} |")
md.append(f"| _total_ | {total_files} | {hsize(total)} | |")
md.append("")

# 2. Chip registers (already done)
md.append("## 2. Chip registers")
md.append("")
md.append("Already analysed in `decoded.md/12_deep_chip_state_analysis.md`.")
md.append(f"Summary: **417 unique registers** Cumulus changes from chip reset (`dump_soc_diff.txt`),")
md.append("grouped across 12 pipeline stages.  Our regdump shows **3640 still-differing scopes** at session end.")
md.append("")

# 3. Chip memories — the big unanalysed corpus
md.append("## 3. Chip memories (NEW analysis — never previously diff'd)")
md.append("")
memstats = analyze_socmem()
if memstats:
    md.append(f"`dump_socmem_diff.txt` is **{hsize(memstats['size'])}** / **{memstats['lines']} lines** / **{memstats['unique_mems']} unique memory names**.")
    md.append("")
    md.append("These are the chip's *internal SRAM table contents* — VLAN_TAB entries, L2 MAC table rows,")
    md.append("FP_TCAM rules, EGR_PORT per-port config, L3_HOST hash entries — what Cumulus *programmed into* the chip.")
    md.append("Crucially: **register state alone does not capture these.**  Our regdump tool reads only registers,")
    md.append("not memories.  This is the gap our chip→CPU debugging missed.")
    md.append("")
    md.append("**Top 20 memories by scope-count diff:**")
    md.append("")
    md.append("| Memory | Entries Cumulus changed |")
    md.append("|---|--:|")
    for nm, n in memstats["top_mems"]:
        md.append(f"| `{nm}` | {n} |")
    md.append("")
    md.append("Many of these (EGR_PORTm, VLAN_TABm, EGR_VLANm, L2_USER_ENTRYm, MY_STATION_TCAMm, FP_TCAMm) directly")
    md.append("control forwarding decisions.  Without their content programmed, the chip cannot do L2/L3 forwarding")
    md.append("the way Cumulus does.")
    md.append("")

# 4. L3 forwarding tables
md.append("## 4. L3 forwarding tables")
md.append("")
l3 = analyze_l3_tables()
if l3:
    md.append("Cumulus's actual L3 routes + next-hops + ECMP groups, dumped at runtime via `bcmcmd dump`:")
    md.append("")
    md.append("| Table | Size | Lines | Valid entries (heuristic) |")
    md.append("|---|--:|--:|--:|")
    for nm, info in l3.items():
        md.append(f"| `{nm}` | {hsize(info['size'])} | {info['lines']} | ~{info['valid_entries']} |")
    md.append("")
    md.append("These are decoded in `decoded.md/01_route_storage.md` + `04_l3_chip_format.md`.")
    md.append("Used to reverse-engineer Cumulus's L3 chain (L3_DEFIP PAIR mode, L3_ENTRY hash key,")
    md.append("INTF id 100xxx/200xxx convention, EGR_L3_NEXT_HOP MAC layout).")
    md.append("")

# 5. FP / TCAM — THE CPU PUNT RULES
md.append("## 5. FP (Field Processor) TCAM — chip-side CPU-punt rules")
md.append("")
md.append("**Critical and never-implemented in EdgeNOS.**")
md.append("")
md.append("The Field Processor is the chip's flexible packet classifier.  Cumulus uses FP rules to:")
md.append("- COPY protocol packets to CPU (OSPF Hello, BGP TCP/179, ICMP, BFD, LACP, STP, LLDP, ...)")
md.append("- Apply per-flow policing (rate-limit certain classes)")
md.append("- Mark packets with priority/queue")
md.append("- Redirect/drop based on L3/L4 headers")
md.append("")
md.append("**Without FP rules**, control-plane packets are not punted to CPU on a Cumulus-style switch.")
md.append("Trident+ does have implicit `V4L3DSTMISS_TOCPU` (and we set it), but the FP table is *the*")
md.append("CPU-punt mechanism Cumulus relies on.")
md.append("")
fp = analyze_fp_tcam()
if fp:
    md.append("**Raw FP table dumps:**")
    md.append("")
    md.append("| Table | Size | Lines | Non-empty entries (heuristic) |")
    md.append("|---|--:|--:|--:|")
    for nm, info in sorted(fp.items()):
        md.append(f"| `{nm}` | {hsize(info['size'])} | {info['lines']} | ~{info['entries']} |")
    md.append("")
fpsh = analyze_fp_show()
if fpsh:
    md.append("**Human-readable FP summary output (`fp show`):**")
    md.append("")
    for nm, info in sorted(fpsh.items()):
        md.append(f"- `{nm}` ({hsize(info['size'])}, {info['lines']} lines)")
        if info["first_lines"]:
            md.append("  First lines:")
            md.append("  ```")
            for ln in info["first_lines"]:
                md.append("  " + ln[:100])
            md.append("  ```")
    md.append("")
md.append("To use this: parse `09_FP_TCAM_raw.txt` → extract entries → write equivalent FP TCAM")
md.append("entries via OpenMDK's `WRITE_FP_TCAMm` macros.  Cumulus's `00control_plane.rules` source file")
md.append("(`final_gaps_*/etc/cumulus/acl/policy.d/00control_plane.rules`) is the canonical *intent* — the FP_TCAM")
md.append("entries are the compiled hardware output of those rules.")
md.append("")

# 6. MCS firmware
md.append("## 6. MCS — chip MicroController RAM")
md.append("")
m = analyze_mcs()
if m:
    md.append(f"`01_dump_mcs.txt` is **{hsize(m['size'])}** / **{m['lines']} lines**.")
    md.append("")
    md.append("First few lines:")
    md.append("")
    md.append("```")
    for ln in m["first"]:
        md.append(ln[:100])
    md.append("```")
    md.append("")
    md.append("The MCS is the chip's embedded MicroController.  In Trident+ it runs SDK-loaded firmware")
    md.append("for tasks like LED scan, link-status polling, MIIM proxy.  OpenMDK's CMICm support uses the")
    md.append("MCS for hardware linkscan.  Cumulus's MCS RAM dump contains the actual firmware bytes loaded.")
    md.append("")
    md.append("**Not critical for chip→CPU forwarding directly**, but the linkscan firmware affects whether")
    md.append("the chip auto-updates EPC_LINK_BMAP when PHY link state changes.")
    md.append("")

# 7. DMA region
md.append("## 7. Host DMA region — what CPU sees from chip")
md.append("")
dma_bin = f"{ROOT}/deep_mine_20260513_191506/03_dma_region_full.bin"
if os.path.exists(dma_bin):
    md.append(f"`03_dma_region_full.bin` is **{hsize(fsz(dma_bin))}**.")
    md.append("")
    md.append("This is the full 64 MB host-side DMA region used by switchd for RX/TX DCB rings,")
    md.append("scratch buffers, and the chip's BDE-mapped tables.  Most of it is poison values (`0xa5a5...`),")
    md.append("but the active region — the DCB ring base + descriptor metadata — is here.")
    md.append("Decoded in `decoded.md/02_dma_model.md`.")
    md.append("")
    md.append("Key takeaways already extracted:")
    md.append(" - 64-DCB ring with `RELOAD=1` per DCB (Cumulus pattern)")
    md.append(" - `DESC_HALT_ADDR` at chip register 0x31120 + 4*chan")
    md.append(" - Interrupt-driven via `LUBDE_WAIT_FOR_INTERRUPT` (ioctl 9)")
    md.append("")

# 8. Switchd binary + gcore + libs
md.append("## 8. switchd binary + gcore + libs")
md.append("")
sw_bin = f"{ROOT}/all/all_20131001_134200/binaries/switchd"
sw_gc = f"{ROOT}/finish_20260513_203818/a7_sw2.core.gz"
sw_gc2 = f"{ROOT}/gcorev3_20260513_171317/gcore/sw.core.gz"
md.append("| Artefact | Size | Notes |")
md.append("|---|--:|---|")
for nm, p, hint in [
    ("switchd binary (stripped)", sw_bin, "31 MB PowerPC ELF, dyn-linked, stripped.  RE target."),
    ("gcore — sw2.core.gz", sw_gc, "Smaller gcore (~3 MB); thread stacks + small heap."),
    ("gcore — sw.core.gz",  sw_gc2, "Larger gcore (~13 MB); fuller memory image."),
]:
    if os.path.exists(p):
        md.append(f"| `{os.path.relpath(p, ROOT)}` | {hsize(fsz(p))} | {hint} |")
md.append("")
md.append("Plus 10 shared libs in `gcorev3_*/switchd/libs/` (libc, libnl, libfuse, libnet, libpthread,")
md.append("librt, libm, libdl, libnl-route, libnl-genl) so gdb can resolve symbols offline.")
md.append("")
md.append("RE potential:")
md.append("- Register names visible in `.rodata` strings (MY_STATION x47, INPUT_PORT_RX_ENABLE x33, EGR_MTU x2).")
md.append("- 373 dynamic symbols still resolvable (mostly libc imports; a few `bcm_*` exports).")
md.append("- `bcm_init_check`, `bcm_init_selective`, `_bcm_esw_*_init` visible as strings (debug-trace fmt).")
md.append("- Use radare2 + cross-reference (`axt @ <addr>`) to walk from register-name string → caller function → that function's other writes.")
md.append("")

# 9. Strace
md.append("## 9. strace — every syscall switchd made")
md.append("")
sl = analyze_strace()
if sl:
    md.append("| File | Size | Lines |")
    md.append("|---|--:|--:|")
    for nm, info in sl.items():
        md.append(f"| `{nm}` | {hsize(info['size'])} | {info['lines']} |")
    md.append("")
    md.append("The `init` strace (245K lines) captured switchd from process-start through chip init.")
    md.append("**What strace SEES**: read() of rc.soc/rc.datapath_0 (bcmcmd input text), ioctl() to BDE driver,")
    md.append("mmap() of BAR0 + DMA pool, open()/close() syscalls.")
    md.append("**What strace MISSES**: every direct `iowrite32(bar0+offset, val)` (mmap'd BAR0 writes are CPU stores, not syscalls).")
    md.append("That's why we can't see the *register-write sequence* of `init all` even though we have the *bcmcmd input*.")
    md.append("")
    md.append("Mined output: `scripts/mine_strace.py` extracts every chip-config command from the strace.")
    md.append("Result: 46 unique commands (mostly `debug -X` flag-sets + the rcload sequence).")
    md.append("")

# 10. The chip→CPU question
md.append("## 10. What this all tells us about the chip→CPU drop")
md.append("")
md.append("Synthesis of EVERY artefact analysed:")
md.append("")
md.append("**Evidence the chip path works in Cumulus:**")
md.append("- L3_DEFIP, L3_ENTRY, EGR_L3_NEXT_HOP all have valid Cumulus entries (section 4)")
md.append("- FP_TCAM has Cumulus's CPU-trap rules (section 5)")
md.append("- VLAN_TAB / EGR_VLAN / EGR_PORT memories have populated content (section 3)")
md.append("- The chip register state (4544 entries) is `init all` + post-tuning (section 2)")
md.append("- MCS firmware loaded for hardware linkscan (section 6)")
md.append("- DMA ring properly armed via BDE (section 7)")
md.append("")
md.append("**Evidence we're missing in EdgeNOS:**")
md.append("- Chip MEMORIES: we never write content to most chip memories (section 3)")
md.append("- FP_TCAM rules: zero ported (section 5)")
md.append("- ~3640 register diffs still (section 2, ranked in doc 12)")
md.append("- Chip MicroController firmware: we don't load anything for MCS (section 6)")
md.append("")
md.append("**Probable root-cause-of-root-cause:**")
md.append("Even if every register diff is closed, the chip's MEMORY tables would still be empty.")
md.append("OpenMDK's `bmd_init` doesn't populate L2_USER_ENTRY, VLAN_TAB entries beyond the bitmap, FP_TCAM,")
md.append("or the egress port-config tables.  Cumulus's `init all` populates all of these.  Without")
md.append("them, even the correctly-programmed chip *registers* point at empty memories and forwarding")
md.append("decisions return 'unknown' / drop.")
md.append("")
md.append("**Strategy this analysis points at:**")
md.append("1. **Diff and port `dump_socmem_diff.txt`** (12 MB, never done).  Particularly EGR_PORTm,")
md.append("   VLAN_TABm content, FP_TCAMm, MY_STATION_TCAMm.")
md.append("2. **Implement FP_TCAM control-plane trap rules** mirroring `00control_plane.rules`.")
md.append("3. **Reverse-engineer `bcm_init_check` / `bcm_init_selective`** in switchd to find the")
md.append("   chip-memory-population sequence.")
md.append("4. **Continue register regdump→port loop** in parallel (still bumping diff count down 200/round).")
md.append("")

# 11. Cross-match: what EdgeNOS code corresponds to each Cumulus artefact
md.append("## 11. EdgeNOS-side correspondence — match-up table")
md.append("")
md.append("For every Cumulus capture category above, where in EdgeNOS we currently have / don't have")
md.append("the equivalent.  This is the 'who-owns-what' map for tomorrow's prioritization.")
md.append("")
md.append("| Cumulus capture | Cumulus content | EdgeNOS equivalent | Status |")
md.append("|---|---|---|---|")
md.append("| `dump_soc_diff.txt` (registers) | 417 regs / 6415 scopes != reset | `asic/edged/datapath.c` + `bmd_init_all` | **~80 of 417 written; 3640 scopes still DIFF** |")
md.append("| `dump_socmem_diff.txt` (memories) | 12 MB chip-memory contents | only L2/VLAN/L3_HOST via BMD APIs; nothing else | **0 explicit memory-table writes** — biggest unaddressed gap |")
md.append("| `FP_TCAM_raw.txt` (CPU-punt rules) | Cumulus has CPU-punt FP entries | `asic/edged/datapath.c` does ONLY `CPU_CONTROL_1` bits | **0 FP_TCAM entries programmed** |")
md.append("| `L3_DEFIP` + `L3_ENTRY` | Cumulus's routes + ARP entries | `asic/edged/l3.c` writes L3_HOST hash (SCHAN HASH_INSERT) + L3_DEFIP (partial) | Partial — single-path only, no PAIR mode, no ECMP wiring from netlink |")
md.append("| `EGR_L3_NEXT_HOP` + `ING_L3_NEXT_HOP` | nexthop MAC + egress port | `asic/edged/l3.c` writes ING_L3_NEXT_HOP for own IPs (COPY_TO_CPU=1) | Partial |")
md.append("| `L3_ECMP` | ECMP group members | `l3_ecmp_group_create()` primitive exists | **Dead code — never called from netlink** |")
md.append("| `MY_STATION_TCAM` | router MAC match entries | `asic/edged/l3.c` writes our chip MAC | Done |")
md.append("| `01_dump_mcs.txt` (MCS firmware) | Cumulus loads linkscan firmware to MCS | OpenMDK CMICm support; we don't load firmware | **No firmware load** — using polling instead |")
md.append("| `03_dma_region_full.bin` | 64 MB host DMA pool | `asic/edged/bde_interface.c` allocates 4 MB pool | Smaller pool — fine for low rate |")
md.append("| `bcmcmd-rc-files/rc.soc` | bcmcmd top-level init script | `datapath_mac_init()` (xmac_tx_ctrl=0xc802, MAC_RSV_MASK=0x18, etc.) | Mostly ported |")
md.append("| `bcmcmd-rc-files/rc.datapath_0` | MMU + scheduler + CPU buffer config | `datapath_buffer_init`, `datapath_cpu_buffer_init`, `datapath_rc_full` | ~50% ported across rounds 1-3 |")
md.append("| `bcmcmd-rc-files/rc.forwarding` | RTAG7 hash + CPU_CONTROL_1 | `datapath_hash_init` + `datapath_cpu_punt_init` | Fully ported |")
md.append("| `bcmcmd-rc-files/rc.led` | LED state machine config | not ported (cosmetic) | N/A for forwarding |")
md.append("| `bcmcmd-rc-files/rc.ports_0` | `setenv allports`, `setenv 40Gports` | aliases only, no chip writes | N/A |")
md.append("| `bcmcmd-rc-files/rc.phy` | empty (Cumulus reserved) | n/a | N/A |")
md.append("| `bcmcmd-rc-files/config.d/02sdk.bcm` | SDK feature flags (parity_enable, polled_irq, miim_intr, dma) | `asic/openmdk/bmd/...` chip-init defaults | Mostly aligned but `parity_enable=1` triggers ~67 PARITY_CONTROL writes we don't make |")
md.append("| `bcmcmd-rc-files/config.d/11ports.bcm` | full XE→phys port map + speeds | `asic/openmdk/bmd/pkgsrc/chip/bcm56840_a0/...p2m` hardcoded | Need byte-by-byte compare; some scopes may be off |")
md.append("| `cumulus-config/etc/cumulus/acl/policy.d/00control_plane.rules` | OSPF/BGP/ICMP/BFD CPU-trap intent | not implemented | **Critical gap — these compile to FP_TCAM** |")
md.append("| `cumulus-config/etc/cumulus/datapath/traffic.conf` | QoS class/priority config | not implemented | Cosmetic for ping |")
md.append("| `cumulus-config/etc/cumulus/switchd.conf` | switchd runtime config | n/a (edged has its own) | N/A |")
md.append("| `switchd-binary` | 31 MB stripped ELF | n/a — we build edged from sources | RE target for soc_init's sequence |")
md.append("| `strace/a1_init_strace.log` | every syscall switchd made at boot | n/a — runtime instrumentation | Mined (see `scripts/mine_strace.py`); the bcmcmd input is the only useful extract |")
md.append("| `kernel-modules/*.ko` | Cumulus's linux-kernel-bde + linux-user-bde + bcm-knet | EdgeNOS has compatible linux-kernel-bde + linux-user-bde (built from OpenMDK) | Same role, equivalent functionality |")
md.append("| `knet/` (bcm-knet driver state) | TPID, port-VLAN, RX-filter rules in bcm-knet | EdgeNOS has no bcm-knet equivalent — RX punt is via CMICm DCB ring + TUN, not bcm-knet | Different model |")
md.append("| `procfs/interrupts` | /proc/interrupts showing 'linux-kernel-bde' IRQ counts | Same module on EdgeNOS; CMICm IRQ count is 0 right now | Same source, different state |")
md.append("| `bcmcmd-table-dumps/` (`show port`, `dump l2`, etc.) | various live chip-state queries | n/a (no equivalent shell in edged) | Used at debug time only |")
md.append("| `cpld-thermal/` | Cumulus's read of MAX6697 + CPLD fan PWM | EdgeNOS has its own `fan-controller.sh` + ds100df410 + accton_as5610_52x_cpld | Equivalent and working |")
md.append("| `sfp-eeprom/` | 52 SFP EEPROM dumps | EdgeNOS reads via i2c bus + ds100df410 driver | Equivalent |")
md.append("| `phy-diag/` | `bcmcmd phy diag` outputs (mostly empty) | not implemented in edged | Cumulus capture failed at the time; we'd produce our own |")
md.append("| `quagga-config/` | OSPF / BGP config | EdgeNOS has no routing daemon yet | Future work |")
md.append("| `vtysh-routing/` | Quagga runtime tables | n/a | Future |")
md.append("| `iptables-tc/` | kernel netfilter + tc-qdisc state | EdgeNOS has stock iptables / tc | Same kernel layer |")
md.append("")
md.append("**Top three never-touched categories** (in order of likely impact on chip→CPU):")
md.append("")
md.append("1. **`dump_socmem_diff.txt`** — every chip-memory table write Cumulus made.  We never write these.")
md.append("2. **FP_TCAM raw + `00control_plane.rules`** — CPU-trap rules for OSPF/BGP/ICMP/BFD.")
md.append("3. **MCS firmware** — Cumulus loads chip MCU code for hardware-linkscan.  We use polling instead.")
md.append("")

# Write
with open(OUT, "w") as f:
    f.write("\n".join(md))
print(f"Wrote {OUT}")
print(f"Lines: {len(md)}")
print()
print(f"Capture inventory: {total_files} files, {hsize(total)} total")
print(f"Categories: {len(inventory)}")

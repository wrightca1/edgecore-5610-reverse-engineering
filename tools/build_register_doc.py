#!/usr/bin/env python3
"""
Build a complete AS5610 (BCM56846 / BCM56840_B0) register + memory reference.

Joins:
  1. OpenMDK CDK defs  -> register/memory list, base addresses, entry geometry, field bit layouts
  2. OpenMDK CDK sym   -> block type (CMIC/IPIPE/EPIPE/MMU/XLPORT/PORT_GROUP*) per symbol
  3. OpenBCM allregs_desc.i -> English description per register/memory
  4. Cumulus dump_soc.txt / dump_socmem_diff.txt -> real values from a working chip

Outputs (in docs/registers/):
  - per-block register files      <BLOCK>.md
  - per-block memory files        MEM_<BLOCK>.md
  - INDEX.md                      one line per register AND memory
  - COMPLETE.md                   everything in a single consolidated document
  - README.md
"""
import re, os, collections

ROOT = "/home/smiley/edgecore"
DEFS = f"{ROOT}/OpenMDK/cdk/include/cdk/chip/bcm56840_b0_defs.h"
SYM  = f"{ROOT}/OpenMDK/cdk/sym/chip/bcm56840_b0_sym.c"
DESC = f"{ROOT}/OpenBCM/sdk-6.5.27/src/soc/mcm/allregs_desc.i"
MDESC= f"{ROOT}/OpenBCM/sdk-6.5.27/src/soc/mcm/allmems_desc.i"
DUMP = f"{ROOT}/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/streamed_20260513_162341/soc/dump_soc.txt"
MDUMP= f"{ROOT}/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/streamed_20260513_162341/soc/dump_socmem_diff.txt"
OUT_DIR = f"{ROOT}/edgecore-5610-reverse-engineering/docs/registers"

# ---------------------------------------------------------------- 1. defs
addr   = {}   # NAME(r|m) -> int address
size   = {}   # NAME -> entry/reg size in bytes
emax   = {}   # NAMEm -> max index (entries = max+1)
fields = collections.defaultdict(list)  # NAME -> [(field, lsb, msb)]

re_addr = re.compile(r"^#define BCM56840_B0_([A-Z0-9_]+[rm]) (0x[0-9a-fA-F]+)$")
re_size = re.compile(r"^#define BCM56840_B0_([A-Z0-9_]+[rm])_SIZE (\d+)$")
re_max  = re.compile(r"^#define BCM56840_B0_([A-Z0-9_]+m)_MAX (\d+)$")
re_fget = re.compile(
    r"^#define BCM56840_B0_([A-Z0-9_]+[rm])_([A-Z0-9_]+)f_GET\(r\) .*?\[(\d+)\]\)(?:\s*>>\s*(\d+))?\)?\s*&\s*(0x[0-9a-fA-F]+)")

with open(DEFS, encoding="latin-1") as f:
    for line in f:
        if (m := re_addr.match(line)):   addr[m.group(1)] = int(m.group(2), 16); continue
        if (m := re_size.match(line)):   size[m.group(1)] = int(m.group(2));      continue
        if (m := re_max.match(line)):    emax[m.group(1)] = int(m.group(2));      continue
        if (m := re_fget.match(line)):
            reg, fld, word, shift, mask = m.groups()
            shift = int(shift) if shift else 0
            lsb = int(word) * 32 + shift
            msb = lsb + int(mask, 16).bit_length() - 1
            fields[reg].append((fld, lsb, msb))

# ---------------------------------------------------------------- 2. sym (block types)
BLK = {}
re_tok = re.compile(r'BCM56840_B0_BLKTYPE_([A-Z0-9_]+)|"([A-Z0-9_]+[rm])"')
pending = []
for m in re_tok.finditer(open(SYM, encoding="latin-1").read()):
    blk, name = m.group(1), m.group(2)
    if blk:
        pending.append(blk)
    elif name:
        if pending and name not in BLK:
            BLK[name] = "/".join(dict.fromkeys(pending))
        pending = []

# ---------------------------------------------------------------- 3. descriptions
desc = {}
re_desc = re.compile(r'^\s*/\* ([A-Z0-9_]+)\s*\*/ "(.*)",?\s*$')
for path in (DESC, MDESC):           # registers then memories (disjoint namespaces)
    for line in open(path, encoding="latin-1"):
        if (m := re_desc.match(line)):
            desc.setdefault(m.group(1), m.group(2))

# ---------------------------------------------------------------- 4. live values
live = collections.defaultdict(list)   # NAME(no suffix) -> [(block, addr, value)]
re_dump = re.compile(r"^(0x[0-9a-fA-F]+) ([A-Z0-9_]+)\.([a-z0-9]+) = (0x[0-9a-fA-F]+)$")
if os.path.exists(DUMP):
    for line in open(DUMP, encoding="latin-1"):
        if (m := re_dump.match(line)):
            a, name, blk, val = m.groups()
            live[name].append((blk, a, val))

mlive_cnt = collections.Counter()      # NAME(no suffix) -> entries captured
mlive_samp = {}                        # NAME(no suffix) -> sample "block[idx]: <...>"
re_md = re.compile(r"^([A-Z0-9_]+)\.([a-z0-9]+)\[(\d+)\]: <(.*)>$")
if os.path.exists(MDUMP):
    for line in open(MDUMP, encoding="latin-1"):
        if (m := re_md.match(line)):
            name, blk, idx, body = m.groups()
            mlive_cnt[name] += 1
            mlive_samp.setdefault(name, f"{blk}[{idx}]: <{body}>")

# ---------------------------------------------------------------- render helpers
def fmt_fields(name):
    fl = fields.get(name, [])
    if not fl:
        return "    _(no field breakdown — treated as a single value)_\n"
    seen, rows = set(), []
    for fld, lsb, msb in fl:
        if (fld, lsb, msb) in seen: continue
        seen.add((fld, lsb, msb))
        rows.append((f"[{msb}]" if msb == lsb else f"[{msb}:{lsb}]", fld))
    out = "    | Bits | Field |\n    |------|-------|\n"
    for bits, fld in rows:
        out += f"    | `{bits}` | {fld} |\n"
    return out

def render_reg(reg):
    o = [f"## {reg}\n"]
    line = f"- **Address:** `0x{addr[reg]:08x}`"
    if reg in size: line += f"  ·  **Size:** {size[reg]} bytes"
    o.append(line)
    if (d := desc.get(reg[:-1])): o.append(f"- **Function:** {d}")
    o.append("\n**Fields:**\n")
    o.append(fmt_fields(reg).rstrip("\n"))
    lv = live.get(reg[:-1], [])
    if lv:
        o.append("\n**Observed live values (Cumulus, working chip):**\n")
        o.append("    | Instance | Address | Value |\n    |----------|---------|-------|")
        for b, a, v in lv[:64]:
            o.append(f"    | {b} | `{a}` | `{v}` |")
        if len(lv) > 64: o.append(f"    _(+{len(lv)-64} more instances)_")
    o.append("\n---\n")
    return "\n".join(o)

def render_mem(mem):
    o = [f"## {mem}\n"]
    line = f"- **Base address:** `0x{addr[mem]:08x}`"
    if mem in emax: line += f"  ·  **Entries:** {emax[mem]+1}"
    if mem in size: line += f"  ·  **Entry width:** {size[mem]} bytes"
    o.append(line)
    if (d := desc.get(mem[:-1])): o.append(f"- **Function:** {d}")
    o.append("\n**Entry fields:**\n")
    o.append(fmt_fields(mem).rstrip("\n"))
    n = mlive_cnt.get(mem[:-1], 0)
    if n:
        o.append(f"\n**Live capture (Cumulus):** {n} entries populated. Sample:\n")
        o.append(f"    {mlive_samp[mem[:-1]]}")
    o.append("\n---\n")
    return "\n".join(o)

# ---------------------------------------------------------------- grouping
regs = sorted([n for n in addr if n.endswith("r")], key=lambda n: addr[n])
mems = sorted([n for n in addr if n.endswith("m")], key=lambda n: addr[n])
reg_by_blk, mem_by_blk = collections.defaultdict(list), collections.defaultdict(list)
for n in regs: reg_by_blk[BLK.get(n, "OTHER")].append(n)
for n in mems: mem_by_blk[BLK.get(n, "OTHER")].append(n)

PREF = ["CMIC","IPIPE","EPIPE","MMU","XLPORT","PORT_GROUP4","PORT_GROUP5","OTHER"]
def blk_rank(b):
    h = b.split("/")[0]
    return (PREF.index(h) if h in PREF else len(PREF), b)
BLOCK_DESC = {
    "CMIC":"CMIC / CMICm — CPU Management Interface (DMA, S-channel, interrupts, MIIM)",
    "IPIPE":"Ingress pipeline — parsing, L2/L3 lookup, VLAN, FP/TCAM, ingress policy",
    "EPIPE":"Egress pipeline — egress VLAN, modification, mirroring, egress policy",
    "MMU":"Memory Management Unit — buffering, queueing, scheduling, flow control",
    "XLPORT":"XLPORT — 10/40G port logic / Warpcore SerDes wrapper",
    "PORT_GROUP4":"Port group 4 — per-port MAC/PCS block",
    "PORT_GROUP5":"Port group 5 — per-port MAC/PCS block",
    "OTHER":"Uncategorized / top-level",
}
def bdesc(b): return BLOCK_DESC.get(b, BLOCK_DESC.get(b.split("/")[0], b))

os.makedirs(OUT_DIR, exist_ok=True)
big = []   # consolidated document buffer

# ---- per-block REGISTER files ----
reg_files = []
for blk in sorted(reg_by_blk, key=blk_rank):
    rs = reg_by_blk[blk]
    fn = f"{blk.replace('/','+')}.md"
    reg_files.append((blk, len(rs), fn))
    body = [f"# BCM56846 Registers — {blk} block\n", f"_{bdesc(blk)}_\n",
            f"{len(rs)} registers.\n", "---\n"] + [render_reg(r) for r in rs]
    open(f"{OUT_DIR}/{fn}", "w", encoding="utf-8").write("\n".join(body))

# ---- per-block MEMORY files ----
mem_files = []
for blk in sorted(mem_by_blk, key=blk_rank):
    ms = mem_by_blk[blk]
    fn = f"MEM_{blk.replace('/','+')}.md"
    mem_files.append((blk, len(ms), fn))
    body = [f"# BCM56846 Memories (tables) — {blk} block\n", f"_{bdesc(blk)}_\n",
            f"{len(ms)} memories.\n", "---\n"] + [render_mem(r) for r in ms]
    open(f"{OUT_DIR}/{fn}", "w", encoding="utf-8").write("\n".join(body))

# ---- INDEX (registers + memories) ----
with open(f"{OUT_DIR}/INDEX.md", "w", encoding="utf-8") as idx:
    idx.write("# AS5610 / BCM56846 — Master Index\n\n")
    idx.write(f"{len(regs)} registers and {len(mems)} memories on the BCM56840_B0 die.\n\n")
    idx.write("## Registers\n\n| Address | Register | Block | Description |\n|---|---|---|---|\n")
    for r in regs:
        d = desc.get(r[:-1], "").replace("|","\\|").split("\\n")[0][:90]
        idx.write(f"| `0x{addr[r]:08x}` | {r} | {BLK.get(r,'-')} | {d} |\n")
    idx.write("\n## Memories (tables)\n\n| Base | Memory | Entries | Block | Description |\n|---|---|---|---|---|\n")
    for r in mems:
        d = desc.get(r[:-1], "").replace("|","\\|").split("\\n")[0][:80]
        idx.write(f"| `0x{addr[r]:08x}` | {r} | {emax.get(r,-1)+1 or '?'} | {BLK.get(r,'-')} | {d} |\n")

# ---- COMPLETE consolidated document ----
total_r, total_m = len(regs), len(mems)
rd = sum(1 for r in regs if desc.get(r[:-1])); rl = sum(1 for r in regs if live.get(r[:-1]))
md = sum(1 for r in mems if desc.get(r[:-1])); ml = sum(1 for r in mems if mlive_cnt.get(r[:-1]))
with open(f"{OUT_DIR}/COMPLETE.md", "w", encoding="utf-8") as c:
    c.write("# AS5610 / BCM56846 — Complete Register & Memory Reference\n\n")
    c.write("Single consolidated document. The same content is also split per block "
            "(see `INDEX.md` / `README.md`).\n\n")
    c.write(f"- **{total_r}** registers ({100*rd//total_r}% described, {100*rl//total_r}% with live values)\n")
    c.write(f"- **{total_m}** memories ({100*md//total_m}% described, {100*ml//total_m}% with live data)\n\n")
    c.write("Chip: Broadcom BCM56846 = BCM56840_B0 (Trident+) SKU. "
            "Sources: OpenMDK CDK defs/sym + OpenBCM descriptions + live Cumulus dumps.\n\n")
    c.write("---\n\n# PART 1 — REGISTERS\n\n")
    for blk in sorted(reg_by_blk, key=blk_rank):
        c.write(f"\n# Registers · {blk} block\n\n_{bdesc(blk)}_\n\n---\n\n")
        for r in reg_by_blk[blk]:
            c.write(render_reg(r) + "\n")
    c.write("\n---\n\n# PART 2 — MEMORIES (TABLES)\n\n")
    for blk in sorted(mem_by_blk, key=blk_rank):
        c.write(f"\n# Memories · {blk} block\n\n_{bdesc(blk)}_\n\n---\n\n")
        for r in mem_by_blk[blk]:
            c.write(render_mem(r) + "\n")

# ---- README ----
with open(f"{OUT_DIR}/README.md", "w", encoding="utf-8") as o:
    o.write("# AS5610 / BCM56846 Complete Register & Memory Reference\n\n")
    o.write("The AS5610's switch silicon is the **Broadcom BCM56846**, a SKU of the "
            "**BCM56840_B0 (Trident+)**; it inherits the full 56840_B0 register database.\n\n")
    o.write("## Coverage\n\n")
    o.write(f"- **{total_r}** registers — {100*rd//total_r}% with a function description, "
            f"{100*rl//total_r}% with a live value from a working Cumulus chip\n")
    o.write(f"- **{total_m}** memories (tables) — {100*md//total_m}% described, "
            f"{100*ml//total_m}% with live captured entries\n\n")
    o.write("## Files\n\n")
    o.write("- [`COMPLETE.md`](COMPLETE.md) — **everything in one document** (registers + memories)\n")
    o.write("- [`INDEX.md`](INDEX.md) — one line per register and memory\n\n")
    o.write("**Registers, split per block:**\n\n")
    for blk, n, fn in reg_files:
        o.write(f"- [`{fn}`]({fn}) — {n} registers — {bdesc(blk)}\n")
    o.write("\n**Memories (tables), split per block:**\n\n")
    for blk, n, fn in mem_files:
        o.write(f"- [`{fn}`]({fn}) — {n} memories — {bdesc(blk)}\n")
    o.write("\n## Sources joined\n\n| Source | Provides |\n|---|---|\n")
    o.write("| OpenMDK CDK `bcm56840_b0_defs.h` | register/memory list, addresses, geometry, field bits |\n")
    o.write("| OpenMDK CDK `bcm56840_b0_sym.c` | block type per symbol |\n")
    o.write("| OpenBCM `allregs_desc.i` | English descriptions |\n")
    o.write("| Cumulus `dump_soc.txt` / `dump_socmem_diff.txt` | live values from a working chip |\n\n")
    o.write("## Caveats\n\n")
    o.write("- **Overlapping field bits are real** — Broadcom alias / multi-view field definitions "
            "taken verbatim from the SDK `*_GET` macros, not a parsing artifact.\n")
    o.write("- Descriptions are register/memory granularity; field bits carry names but usually no prose.\n")
    o.write("- Memory live counts/sample come from a diff dump (entries that differed from reset), "
            "so they are a lower bound on what the table holds.\n\n")
    o.write("_Auto-generated by `tools/build_register_doc.py` — re-run to regenerate._\n")

print(f"registers={total_r} (desc {rd}, live {rl})  memories={total_m} (desc {md}, live {ml})")
print("reg blocks:", {b:n for b,n,_ in reg_files})
print("mem blocks:", {b:n for b,n,_ in mem_files})

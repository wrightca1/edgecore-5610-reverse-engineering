#!/usr/bin/env python3
"""
Build a complete AS5610 (BCM56846 / BCM56840_B0) register reference document.

Joins four sources:
  1. OpenMDK CDK defs  -> chip-specific register list + base addresses + field bit layouts
  2. OpenMDK CDK sym   -> block type (CMIC/IPIPE/EPIPE/MMU/XLPORT/PORT_GROUP*) per register
  3. OpenBCM allregs_desc.i -> English description per register
  4. Cumulus live dump_soc.txt -> real register values observed on a working chip

Output: REGISTER_REFERENCE.md (+ a one-line index).
"""
import re, sys, os, collections

ROOT = "/home/smiley/edgecore"
DEFS = f"{ROOT}/OpenMDK/cdk/include/cdk/chip/bcm56840_b0_defs.h"
SYM  = f"{ROOT}/OpenMDK/cdk/sym/chip/bcm56840_b0_sym.c"
DESC = f"{ROOT}/OpenBCM/sdk-6.5.27/src/soc/mcm/allregs_desc.i"
DUMP = f"{ROOT}/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/streamed_20260513_162341/soc/dump_soc.txt"
OUT_DIR = f"{ROOT}/edgecore-5610-reverse-engineering/docs/registers"

# ---------------------------------------------------------------- 1. defs
reg_addr = {}           # NAMEr -> int address
reg_size = {}           # NAMEr -> size bytes
fields   = collections.defaultdict(list)  # NAMEr -> [(field, lsb, msb)]

re_addr = re.compile(r"^#define BCM56840_B0_([A-Z0-9_]+r) (0x[0-9a-fA-F]+)$")
re_size = re.compile(r"^#define BCM56840_B0_([A-Z0-9_]+r)_SIZE (\d+)$")
# field GET macro:  ..._<FIELD>f_GET(r) ((((r).word[K]) >> N) & 0xMASK)   (>>N optional)
re_fget = re.compile(
    r"^#define BCM56840_B0_([A-Z0-9_]+r)_([A-Z0-9_]+)f_GET\(r\) .*?\[(\d+)\]\)(?:\s*>>\s*(\d+))?\)?\s*&\s*(0x[0-9a-fA-F]+)")

with open(DEFS, encoding="latin-1") as f:
    for line in f:
        m = re_addr.match(line)
        if m:
            reg_addr[m.group(1)] = int(m.group(2), 16)
            continue
        m = re_size.match(line)
        if m:
            reg_size[m.group(1)] = int(m.group(2))
            continue
        m = re_fget.match(line)
        if m:
            reg, fld, word, shift, mask = m.groups()
            shift = int(shift) if shift else 0
            width = int(mask, 16).bit_length()
            lsb = int(word) * 32 + shift
            msb = lsb + width - 1
            fields[reg].append((fld, lsb, msb))

# ---------------------------------------------------------------- 2. sym (block types)
BLK = {}   # NAMEr -> "IPIPE" etc.
# Walk tokens in order: each register record has one-or-more BLKTYPE_x tokens
# (multiple ORed for shared blocks) followed by the quoted "NAMEr". Assign the
# blocktype(s) seen since the previous name to that name.
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
desc = {}   # NAME (no suffix) -> text
re_desc = re.compile(r'^\s*/\* ([A-Z0-9_]+)\s*\*/ "(.*)",?\s*$')
with open(DESC, encoding="latin-1") as f:
    for line in f:
        m = re_desc.match(line)
        if m:
            desc.setdefault(m.group(1), m.group(2))

# ---------------------------------------------------------------- 4. live dump
live = collections.defaultdict(list)   # NAME (no suffix) -> [(block, addr, value)]
re_dump = re.compile(r"^(0x[0-9a-fA-F]+) ([A-Z0-9_]+)\.([a-z0-9]+) = (0x[0-9a-fA-F]+)$")
if os.path.exists(DUMP):
    with open(DUMP, encoding="latin-1") as f:
        for line in f:
            m = re_dump.match(line)
            if m:
                addr, name, blk, val = m.groups()
                live[name].append((blk, addr, val))

# ---------------------------------------------------------------- join + emit
os.makedirs(OUT_DIR, exist_ok=True)

# group registers by block type
by_block = collections.defaultdict(list)
for reg in sorted(reg_addr, key=lambda r: (BLK.get(r, "ZZZ"), reg_addr[r])):
    by_block[BLK.get(reg, "OTHER")].append(reg)

BLOCK_DESC = {
    "CMIC": "CMIC / CMICm — CPU Management Interface (DMA, S-channel, interrupts, MIIM)",
    "IPIPE": "Ingress pipeline — parsing, L2/L3 lookup, VLAN, FP/TCAM, ingress policy",
    "EPIPE": "Egress pipeline — egress VLAN, modification, mirroring, egress policy",
    "MMU": "Memory Management Unit — buffering, queueing, scheduling, flow control",
    "XLPORT": "XLPORT — 10/40G port logic / Warpcore SerDes wrapper",
    "PORT_GROUP4": "Port group 4 — per-port MAC/PCS block",
    "PORT_GROUP5": "Port group 5 — per-port MAC/PCS block",
    "OTHER": "Uncategorized / top-level registers",
}

total = len(reg_addr)
with_desc = sum(1 for r in reg_addr if desc.get(r[:-1]))
with_live = sum(1 for r in reg_addr if live.get(r[:-1]))

def fmt_fields(reg):
    fl = fields.get(reg, [])
    if not fl:
        return "    _(no field breakdown — treated as a single 32-bit value)_\n"
    # de-dup (defs lists alias variants at same bits), keep first occurrence order
    seen = set(); rows = []
    for fld, lsb, msb in fl:
        key = (fld, lsb, msb)
        if key in seen: continue
        seen.add(key)
        bits = f"[{msb}]" if msb == lsb else f"[{msb}:{lsb}]"
        rows.append((bits, fld))
    out = "    | Bits | Field |\n    |------|-------|\n"
    for bits, fld in rows:
        out += f"    | `{bits}` | {fld} |\n"
    return out

# master index (one line per register)
idx = open(f"{OUT_DIR}/INDEX.md", "w", encoding="utf-8")
idx.write("# AS5610 / BCM56846 Register Index\n\n")
idx.write(f"All {total} registers implemented on the BCM56840_B0 die (the BCM56846's base chip).\n")
idx.write("One line each. Full detail in the per-block files under this directory.\n\n")
idx.write("| Address | Register | Block | Description |\n|---------|----------|-------|-------------|\n")
for reg in sorted(reg_addr, key=lambda r: reg_addr[r]):
    d = desc.get(reg[:-1], "")
    d = d.replace("|", "\\|").split("\\n")[0][:90]
    idx.write(f"| `0x{reg_addr[reg]:08x}` | {reg} | {BLK.get(reg,'-')} | {d} |\n")
idx.close()

# per-block detail files
PREF = ["CMIC","IPIPE","EPIPE","MMU","XLPORT","PORT_GROUP4","PORT_GROUP5","OTHER"]
def blk_rank(b):
    head = b.split("/")[0]
    return (PREF.index(head) if head in PREF else len(PREF), b)
block_order = sorted(by_block, key=blk_rank)
written = []
for blk in block_order:
    regs = by_block.get(blk, [])
    if not regs: continue
    fn = f"{OUT_DIR}/{blk.replace('/','+')}.md"
    written.append((blk, len(regs), fn))
    with open(fn, "w", encoding="utf-8") as o:
        o.write(f"# BCM56846 Registers — {blk} block\n\n")
        o.write(f"_{BLOCK_DESC.get(blk, blk)}_\n\n")
        o.write(f"{len(regs)} registers. Source: OpenMDK CDK defs/sym + OpenBCM descriptions + live Cumulus dump.\n\n---\n\n")
        for reg in regs:
            o.write(f"## {reg}\n\n")
            o.write(f"- **Address:** `0x{reg_addr[reg]:08x}`")
            if reg in reg_size: o.write(f"  ·  **Size:** {reg_size[reg]} bytes")
            o.write("\n")
            d = desc.get(reg[:-1])
            if d:
                o.write(f"- **Function:** {d}\n")
            o.write("\n**Fields:**\n\n")
            o.write(fmt_fields(reg))
            lv = live.get(reg[:-1], [])
            if lv:
                o.write("\n**Observed live values (Cumulus, working chip):**\n\n")
                o.write("    | Instance | Address | Value |\n    |----------|---------|-------|\n")
                for b, a, v in lv[:64]:
                    o.write(f"    | {b} | `{a}` | `{v}` |\n")
                if len(lv) > 64:
                    o.write(f"    _(+{len(lv)-64} more instances)_\n")
            o.write("\n---\n\n")

# README
with open(f"{OUT_DIR}/README.md", "w", encoding="utf-8") as o:
    o.write("# AS5610 / BCM56846 Complete Register Reference\n\n")
    o.write("The AS5610's switch silicon is the **Broadcom BCM56846**, a SKU of the "
            "**BCM56840_B0 (Trident+)**. It inherits the full 56840_B0 register database.\n\n")
    o.write("## Coverage\n\n")
    o.write(f"- **{total}** registers documented (every register implemented on the die)\n")
    o.write(f"- **{with_desc}** ({100*with_desc//total}%) carry an English function description\n")
    o.write(f"- **{with_live}** ({100*with_live//total}%) have at least one live value captured from a working Cumulus chip\n\n")
    o.write("## Sources joined\n\n")
    o.write("| Source | Provides |\n|--------|----------|\n")
    o.write("| OpenMDK CDK `bcm56840_b0_defs.h` | register list, addresses, field bit positions |\n")
    o.write("| OpenMDK CDK `bcm56840_b0_sym.c` | block type (CMIC/IPIPE/EPIPE/MMU/XLPORT/...) |\n")
    o.write("| OpenBCM `allregs_desc.i` | English per-register descriptions |\n")
    o.write("| Cumulus `dump_soc.txt` | real values from a working chip |\n\n")
    o.write("## Files\n\n")
    o.write("- [`INDEX.md`](INDEX.md) — one line per register (address, name, block, description)\n")
    for blk, n, fn in written:
        bn = blk.replace('/','+')
        o.write(f"- [`{bn}.md`]({bn}.md) — {n} registers — {BLOCK_DESC.get(blk, blk)}\n")
    o.write("\n_Auto-generated by `tools/build_register_doc.py`. Registers only; "
            "654 chip memories (tables) are not included here._\n")

print(f"Registers: {total}  with-desc: {with_desc}  with-live: {with_live}")
print("Blocks:", {b: n for b, n, _ in written})
print(f"Output dir: {OUT_DIR}")

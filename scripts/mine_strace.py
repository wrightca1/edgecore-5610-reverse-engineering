#!/usr/bin/env python3
"""
Harvest every chip-config command (rc.soc / rc.datapath_0 / interactive)
from Cumulus switchd's init strace.

strace shows read(fd, "...content...", N) = N.  Walk those lines, decode
the escaped content, and collect every distinct setreg/modreg/modify/
write/init/rcload/attach/debug/s/m verb.
"""
import re
import sys
from collections import OrderedDict

STRACE = "/home/smiley/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013_run2/finish_20260513_203818/a1_init_strace.log"

VERBS = ("setreg", "modreg", "modify", "write", "rcload", "init ",
         "attach ", "debug ", "s ", "m ", "config ", "phy ")

def decode_strace_string(s):
    """Decode the C-style escapes inside a strace string."""
    out = bytearray()
    i = 0
    while i < len(s):
        c = s[i]
        if c == "\\" and i + 1 < len(s):
            nxt = s[i+1]
            if nxt == "n":
                out.append(0x0a); i += 2
            elif nxt == "t":
                out.append(0x09); i += 2
            elif nxt == "r":
                out.append(0x0d); i += 2
            elif nxt == "\\":
                out.append(0x5c); i += 2
            elif nxt == '"':
                out.append(0x22); i += 2
            elif nxt == "x" and i + 3 < len(s):
                out.append(int(s[i+2:i+4], 16)); i += 4
            elif nxt.isdigit():
                # \NNN octal up to 3 digits
                j = i + 1
                while j < len(s) and j - i - 1 < 3 and s[j].isdigit():
                    j += 1
                out.append(int(s[i+1:j], 8)); i = j
            else:
                out.append(ord(c)); i += 1
        else:
            out.append(ord(c)); i += 1
    return out.decode("latin-1", "replace")


# A read() line looks like:
#   29933 12:01:16.295384 read(17, "\ndebug ...", 4096) = 1522
# or split across lines via <unfinished ...> / resumed.

read_re = re.compile(r'\bread\(\d+,\s*"((?:[^"\\]|\\.)*)"')

verbs_seen = OrderedDict()
all_lines_text = []

with open(STRACE, encoding="latin-1") as f:
    for line in f:
        m = read_re.search(line)
        if not m:
            continue
        text = decode_strace_string(m.group(1))
        if not any(v in text for v in VERBS):
            continue
        all_lines_text.append(text)

# Join + split on newlines to get individual commands
buf = "".join(all_lines_text)
for ln in buf.split("\n"):
    ll = ln.strip()
    if not ll or ll.startswith("#"):
        continue
    # First word (or word pair for "init all" etc.)
    parts = ll.split(None, 2)
    if not parts:
        continue
    verb = parts[0]
    if verb in ("setreg", "modreg", "modify", "write", "rcload", "init",
                "attach", "debug", "s", "m", "config", "phy", "port",
                "linkscan", "stg", "vlan", "0:", "expert"):
        # Use full normalized line
        verbs_seen.setdefault(ll, 0)
        verbs_seen[ll] += 1

print(f"Distinct chip-config commands harvested: {len(verbs_seen)}")
print()
print("Top 30 by occurrence:")
for cmd, n in sorted(verbs_seen.items(), key=lambda x: -x[1])[:30]:
    print(f"  ({n:3d})  {cmd[:140]}")

# Save unique commands
out = "/tmp/cumulus_chip_cmds.txt"
with open(out, "w") as f:
    for cmd in sorted(verbs_seen.keys()):
        f.write(cmd + "\n")
print()
print(f"All {len(verbs_seen)} unique cmds saved to {out}")

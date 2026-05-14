---
name: project_cumulus_bulk_capture_strategy
description: "Capture EVERYTHING from Cumulus during a reflash instead of curating what we know to need — BAR0 hexdump, all chip tables, switchd gcore, strace, /proc state. Then mine offline."
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

When the AS5610-52X is reflashed back to Cumulus, **don't curate** the capture list — bulk-dump everything chip and process state and mine offline. We can't predict every register we'll later wish we had.

**The three bulk sources that cover the entire chip + software state:**

1. **PCIe BAR0 mmap dump** — `dd if=/sys/bus/pci/devices/<bdf>/resource0` captures every register byte (~2 MB). Take two snapshots: one idle, one under sustained ping. The diff highlights every register the live RX pipeline touches.

2. **Every chip table** — `bcmcmd "list mem"` enumerates them; loop `bcmcmd "dump <name>"`. Catches L3/L2/VLAN AND obscure tables (RX queue maps, scheduler tables, BST monitoring).

3. **switchd gcore** — `gcore -o switchd_core $(pidof switchd)` produces a full process dump containing all SW state (descriptor ring addrs, shadow tables, allocator state).

**Plus the surrounding context:**
- `strace -p switchd -e all -f -tt -s 4096` during a 5-sec ping burst
- `/proc/interrupts` before+after a ping burst (does CMICm RX use IRQs or polling?)
- `lspci -vvv -s <bdf>` (chip config)
- `/sys/module/linux_user_bde/parameters/*` and `linux_kernel_bde` (BDE driver params)
- `dmesg`, `lsmod`, `/proc/iomem`, `/proc/device-tree`

**Why this matters:** the immediate blocker (2026-05-13) is CMICm RX delivery to CPU. BAR0 idle-vs-active diff will pinpoint the missing register write in minutes; the curated approach risks missing something we didn't think to capture.

**One-shot script lives in [[project_cumulus_reflash_capture_plan]]** (Tier 0 section) — that's the curated version. This memory says: run the bulk script FIRST, then run the curated dump as a sanity check.

**Time cost:** ~5 min to run, ~500 MB-1 GB output. Worth it given a Cumulus reflash is hours.

**Storage / handling:** scp the tarball off before reflashing back to EdgeNOS. Commit summaries (not the multi-hundred-MB binaries) to the RE repo. Keep BAR0 dumps and core dumps in a separate large-file location.

Linked: [[project_cumulus_reflash_capture_plan]], [[project_rx_dma_cmicm_migration]], [[project_switch_ip_reflash]], [[feedback_readonly_cumulus]] (all bulk reads are safe — no writes).

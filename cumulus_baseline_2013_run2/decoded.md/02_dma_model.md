---
name: project_cumulus_dma_decoded
description: "How Cumulus 2.5.0 actually does RX/TX DMA on the BCM56846 — interrupt-driven via user-mode BDE, chained DCB ring (DV), strace+register evidence captured 2026-05-13"
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# Architecture summary

```
+-------------------------------------------------------------+
|                          switchd (user-mode)                |
|    +-----------------+    +------------------+              |
|    | RX thread       |    | TX thread        |              |
|    | blocks on       |    | reads from TUN,  |              |
|    | ioctl WAIT_INTR |    | builds DCBs,     |              |
|    | -> dequeues DV  |    | issues SEM_OP    |              |
|    | -> write(TUN)   |    +------------------+              |
|    +-----------------+                                       |
+-----------|--------------------------|---------------------+
            v                          v
  ioctl /dev/linux-user-bde       /dev/mem mmap of BAR0
   (LUBDE_WAIT_FOR_INTERRUPT,      (256K @ 0xa0000000 + 64M @ 0x02400000)
    LUBDE_SEM_OP, LUBDE_IRQ_MASK)   - direct register writes
            v                       - direct DMA descriptor writes
  +------------------------+
  | linux_kernel_bde / .ko |  - PCI probe
  | (sets up uio-like      |  - IRQ handler -> wake_up on a queue
  |  device)               |  - sem_op pass-through
  +------------------------+
            v
  +------------------------+
  |  BCM56846 / Trident+   |
  |  CMICm DMA engine      |
  +------------------------+
```

Cumulus 2.5.0 does NOT use `linux_bcm_knet` (no `/dev/linux-bcm-knet` exists on the live system). KNET would be the in-kernel TX/RX shortcut; here switchd handles everything itself.

# Critical evidence

## switchd's open FDs
```
14 -> /dev/linux-user-bde     <- the BDE control channel
21 -> (TUN device)            <- packets in/out to kernel
```

## switchd memory maps
```
4802b000-4806b000 rw-s a0000000 /dev/mem    256 KB   <- BAR0 chip registers
4806b000-4c06b000 rw-s 02400000 /dev/mem     64 MB   <- DMA-able host RAM region
```
**BAR0 is mapped via `/dev/mem`, not via BDE's mmap.** The kernel BDE module just claims the PCI device and exports the IRQ; userspace pokes registers directly.

## Loaded modules
```
linux_bde_tmon          6674   0
linux_user_bde         14431   0
linux_kernel_bde       34398   2 linux_user_bde, linux_bde_tmon
```
No `linux_bcm_knet`. No KNET.

## The three hot ioctls (from 8-sec strace under ping load — 11,300+ total)
| ioctl number | nr (last byte) | name | role |
|---|---|---|---|
| `0x20004c08` | 0x08 | (LUBDE_IRQ_MASK or similar) | mask/unmask IRQ lines around DMA submit |
| `0x20004c09` | 0x09 | **LUBDE_WAIT_FOR_INTERRUPT** | block until BDE wakes up on chip IRQ (per-CMICm-RX-completion or coalesced) |
| `0x20004c0a` | 0x0a | **LUBDE_SEM_OP** | semaphore wake between IRQ thread and worker threads — most frequent call |

Mapping confirmed by cross-ref with `PATH_B_INFORMATION_CHECKLIST.md` + `GAPS_FOR_CUSTOM_SWITCHD_SDK.md` (older RE work). Linux ioctl encoding (PPC32): bits 31-30 = dir, bits 29-16 = size, bits 15-8 = type ('L' = 0x4c), bits 7-0 = nr.

## The hot loop pattern
```
ioctl(14, 0x20004c0a, ...)            <- SEM_OP (worker waits on sem)
ioctl(14, 0x20004c0a) = 0             <- (sem wake)
read(21, buf, 16384) = 98             <- TUN read (TX side: packet from kernel)
write(21, buf, 98) = 98               <- TUN write (RX side: packet to kernel)
ioctl(14, 0x20004c09, ...) <unfinished> <- WAIT_FOR_INTERRUPT (blocks until next packet)
```

# DMA descriptors — the "DV" (DMA Vector) model

bcmcmd has these DMA subcommands (no `dma info/show/stat`):
```
dma dvalloc [r|t] <dcb_count>     <- allocate a TX or RX DMA Vector with N DCBs
dma dvfree dv_addr                 <- free a DV
dma addrx <dv_laddr> <buf_laddr> <bytes>  <- add an RX DCB to a DV chain
dma dcbdump [r|t] $dcb_laddr       <- dump a DCB (for r or t direction)
dma alloc/free/l2p/p2l/flush/inval/load/fill/edit  <- DMA-able RAM management
```

So Cumulus's DMA model: allocate a **ring of DCBs** (chained), add buffers, submit. The chip walks the ring, fills DCBs, fires interrupts when the chain hits HALT_ADDR or DESC_DONE.

# Implications for EdgeNOS

Our current RX DMA (`bcm56840_a0_bmd_rx_poll`) does:
1. Allocate **one** DCB
2. Arm DMA on chan=1
3. Poll `chain_done` bit in `STATr` (sticky-1 idle state → false positives)
4. Never see DCB.DONE become 1

What Cumulus does:
1. Allocate a **DV with multiple DCBs** (probably 64 per knet code we already RE'd — `MAX_RX_DCBS=64`)
2. Set `CMIC_CMC_DMA_DESC_HALT` to the end of the ring
3. Arm DMA on chan=1
4. **Block on LUBDE_WAIT_FOR_INTERRUPT** until the chip's IRQ handler fires (after a packet lands in a DCB)
5. After IRQ: walk DCBs, deliver to TUN, re-arm by advancing HALT_ADDR

**Three concrete things to change in EdgeNOS:**
1. Build a multi-DCB ring instead of a single DCB. Mirror `DMA_DCB_LAYOUT_FROM_KNET.md`'s 64-DCB ring.
2. Program `CMIC_CMC_DMA_DESC_HALT` to point at end-of-ring (we never write that register today).
3. Switch from polling to interrupt-driven: open the BDE node and issue the equivalent of `LUBDE_WAIT_FOR_INTERRUPT`. Our custom BDE may not export this yet — that's the work.

Alternatively, keep polling but check **`DCB.DONE` in the host-memory DCB**, not `chain_done` in the chip register. The chip writes DONE=1 into the DCB when it fills it, and that bit is per-DCB (not sticky). Combined with a multi-DCB ring, we walk forward through DONE'd DCBs without needing interrupts.

# Captures
- `cumulus_baseline_2013_run2/dma_20131001_123802.tgz` — bde/, knet/, strace/, regs/, procfs/, fuse/
- `cumulus_baseline_2013_run2/routes_20131001_121841.tgz` — L3 chip-table dumps under OSPF
- `cumulus_baseline_2013_run2/single_20131001_123018.tgz` — chip diff when swp2 goes down (ECMP → single)
- `cumulus_baseline_2013_run2/cap_20131001_121651.tgz` — original bulk capture (BAR0 idle/loaded + chip tables)

Linked: [[project_rx_dma_cmicm_migration]] (where we got stuck — this answers it), [[project_cumulus_route_storage_decoded]] (L3 tables), [[project_cumulus_bulk_capture_strategy]] (the bulk-dump strategy that yielded this).

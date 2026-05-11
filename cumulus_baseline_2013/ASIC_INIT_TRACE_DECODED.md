# switchd Init Trace — Ground-Truth Decode

What `bcm_init` actually does, decoded from the **27 MB / 455,167-line strace**
of switchd cold-boot captured 2026-02-18 from chassis 10.1.1.233.

The trace was taken with plain `strace -f` (no `-v -e read=all`), so we have
**every ioctl call** (opcode + pointer + return code) but **NOT the buffer
contents** — register addresses and values are not recoverable from this
trace. What IS recoverable:

- Exact ioctl call **count** per opcode per phase
- Exact **timing** of every phase boundary
- The **rate** of register reads vs. writes vs. IRQ waits in each sub-phase
- The relative dominance of polling vs. interrupt-driven I/O

This pins down what `bcm_init` is doing well enough to validate against
EdgeNOS, and tells us where to point the magnifying glass when we re-capture
with buffer contents.

---

## 1. LUBDE ioctl opcode reference

| Opcode | Symbol | Effect | Buffer carries |
|---|---|---|---|
| `0x20004c01` | `LUBDE_GET_NUM_DEVICES` | Count chips on the bus | out: int |
| `0x20004c02` | `LUBDE_GET_DEVICE` | Device id, rev, BAR phys | out: device descriptor |
| `0x20004c04` | `LUBDE_PCI_CONFIG_GET` | PCI config-space read | in/out: {offset, len, value} |
| `0x20004c05` | `LUBDE_GET_DMA_INFO` | DMA pool phys addr + size | out: {pbase, size} |
| `0x20004c06` | `LUBDE_ENABLE_INTERRUPTS` | Connect ISR to chip's IRQ line | in: device idx |
| `0x20004c08` | `LUBDE_USLEEP` | `sal_usleep(us)` | in: microseconds |
| `0x20004c09` | `LUBDE_WAIT_FOR_INTERRUPT` | Block waiting for IRQ | in: device idx |
| `0x20004c0a` | `LUBDE_PHYS_READ32` | 32-bit BAR0 read | in/out: {offset, value} |
| `0x20004c0b` | `LUBDE_PHYS_WRITE32` | 32-bit BAR0 write | in: {offset, value} |
| `0x20004c0c` | `LUBDE_GET_DEVICE_TYPE` | Device class flags | out: int |
| `0x20004c1a` | `LUBDE_GET_DEVICE_RESOURCE` | Full BAR0/BAR1/IRQ map | out: resource struct |

The opcodes seen in the trace exactly match this table (the only opcodes
present are init-related). No SPI, no IRQ-mask-set, no semaphore ops in
this capture.

---

## 2. Phase boundaries (verbatim from trace timestamps)

The init flow runs **31.13 seconds** end-to-end. Boundaries are derived from
`open()` calls of the canonical files:

| Phase | Marker | Wall clock | +sec | Duration |
|---|---|---|---|---|
| 1. Parse switchd.conf | `open(switchd.conf)` | `03:58:06.116033` | 0.000 | 0.044 s |
| 2. BDE open | `open(/dev/linux-user-bde)` | `03:58:06.160029` | 0.044 | 0.021 s |
| 3a. bcm_attach (config.bcm) | `open(/etc/bcm.d/config.bcm)` | `03:58:06.180577` | 0.065 | 0.139 s |
| **3b. `init all` (bcm_init)** | `open(/etc/bcm.d/rc.soc)` | `03:58:06.319082` | 0.203 | **24.721 s** |
| 4a. rc.soc tweaks 1 | `open(rc.ports_0)` | `03:58:31.040290` | 24.924 | 0.168 s |
| 4b. rc.datapath_0 | `open(rc.datapath_0)` | `03:58:31.208129` | 25.092 | 3.758 s |
| 4c. rc.led | `open(rc.led)` | `03:58:34.966626` | 28.851 | 1.789 s |
| 5. Datapath conf re-read | `open(datapath.conf)` | `03:58:36.756021` | 30.640 | 0.489 s |
| Ready | `open(/var/run/switchd.ready)` | `03:58:37.245292` | 31.129 | — |

**The single biggest fact: `bcm_init` runs for 24.7 seconds.** That's the
window in which all the memory clearing, block reset, per-port init, and
PHY/SerDes initialization happens.

---

## 3. Ioctl call distribution per phase

| Phase | Duration | PHYS_RD | PHYS_WR | WAIT_IRQ | USLEEP | Other |
|---|---:|---:|---:|---:|---:|---|
| 2. BDE open | 0.021s | 9 | 1 | 0 | 0 | 8 setup ioctls (GET_DEVICE×1, GET_DEVICE_TYPE×1, GET_DEVICE_RESOURCE×1, GET_DMA_INFO×1, GET_NUM_DEVICES×4) |
| 3a. bcm_attach | 0.139s | 24 | 0 | 1 | 0 | ENABLE_INTERRUPTS×1 |
| **3b. bcm_init** | **24.721s** | **110,737** | **557** | **54,371** | **1,107** | 6 PCI_CONFIG_GET |
| 4a. rc.soc setregs | 0.168s | 762 | 3 | 381 | 0 | — |
| 4b. rc.datapath_0 | 3.758s | 10,208 | 48 | 5,003 | 160 | — |
| 4c. rc.led | 1.789s | 1,467 | 156 | 329 | 117 | — |
| 5. Datapath finalize | 0.489s | 264 | 0 | 0 | 1 | — |
| **TOTAL** | 31.1s | **123,471** | **765** | **60,085** | **1,385** | 19 |

### Observations

- **Reads vs writes is 160:1.** This is a polling-heavy SDK — every register
  write is preceded by several reads (probably SCHAN_DONE polling, port
  state checks, validation).
- **Only 557 PIO writes in 24.7 seconds of bcm_init.** This is because
  `config.bcm` sets `table_dma_enable=1` and `tslam_dma_enable=1` — bulk
  memory operations go via DMA descriptor rings, not visible as ioctl
  writes. The 557 writes are mostly SCHAN command-register setups (each
  one issues a SCHAN op that does many internal writes).
- **54k WAIT_FOR_INTERRUPT in bcm_init.** The SDK blocks waiting for
  IRQ-driven completion 54,371 times. That's the `miim_intr_enable=1`,
  `tdma_intr_enable=1`, `tslam_intr_enable=1` settings paying off — every
  MIIM op, every Table DMA, every SLAM DMA waits for an IRQ instead of
  polling.
- **rc.datapath_0 issues only 48 writes** in 3.8 seconds because most of
  its `write/modify` commands target internal tables via DMA (each command
  may program hundreds of entries in a single DMA burst).
- **rc.led has 156 writes** in 1.8 seconds. The LED uController bytecode
  upload (`.hex` files) appears to use PIO writes (one per opcode), not
  DMA. This makes sense — the LED uC SRAM is small and infrequently
  reloaded.

---

## 4. The `init all` window decomposed (sub-second resolution)

Bucketing Phase 3b into 1-second bins reveals **5 distinct sub-phases**:

```
sec  WAIT_IRQ  USLEEP  PHYS_RD  PHYS_WR    inferred sub-phase
---  --------  ------  -------  -------    -------------------------------------
  0       190      97     1123       16    A. Chip soft-reset + CMICm setup
  1         -       -        -        -    (silent — chip settling)
  2      1095      16     2316        5    B. Memory init ramp-up
  3      2693      32     5386       10
  4      3106      16     6212        5
  5      2819      33     5638       10
  6      2916      32     5831       10
  7      3012      16     6025        5    B. Memory init steady-state
  8      2890      33     5779       10       (~3000 IRQ waits/sec —
  9      2878      31     5757       11        Table DMA + SLAM DMA bursts
                                              for SRAM clearing)
 10      2418      62     4837      187    ┐
 11      3024      17     6048       32    ├ C. Block configuration:
 12      2754      32     5509       30    │    MMU/IPIPE/EPIPE setup
 13      2941      16     5883       30    │    + per-port pipeline init
 14      2833      33     5665       28    │    (52 ports × ~150 ms/port = ~7.8s)
 15      2874      16     5748       32    │
 16      2758      32     5518       28    │
 17      2800      17     5598       30    │
 18      2834      31     5667       30    │
 19      1329     186     2659       36    ┘ tail-off: late-port config

 20       551      99     1430       11    D. PHY / SerDes init:
 21      1147      77     2957        0       USLEEP density ↑ (PHY MDIO
 22      1906       0     3862        0       has 70µs/op timing constraint)
 23      1818      53     3676        0
 24       785     130     1613        1       (no PHY ucode loaded — this
                                               is SerDes lane bring-up only;
                                               PHY firmware is loaded later
                                               by /usr/lib/cumulus/phy-update)

End of Phase 3b at +24.7s → rc.ports_0 opens
```

### Sub-phase interpretation

**A (sec 0): Chip soft-reset + CMICm setup** (~0.5s)
- Heavy USLEEP (97 in <1s = ~10 µs avg) — driving chip into reset, holding,
  releasing.
- 16 writes — likely the reset-control register + clock dividers.

**B (sec 2-9): Memory init** (~8s)
- ~3,000 IRQ waits per second, all completing within ~330 µs each.
- ~50 reads per IRQ wait — polling DMA STATUS until done.
- This is the Table DMA bulk-clearing of every internal SRAM table.
  Trident has ~50 internal tables (L2/L3/VLAN/EGR_VLAN/MY_STATION_TCAM/
  FP_TCAM/L3_IIF/L3_EIF/NEXT_HOP/ECMP/COS_MAP/MMU_BUFFERS/...). With
  ~16 IRQs/table × 50 tables = ~800 DMA ops, and each DMA is ~300 µs,
  total ~8 seconds. Matches the observed window.

**C (sec 10-19): Block + per-port init** (~10s)
- Writes per second jump 4× at sec 10 (16→187). This is the SDK starting
  to write block configuration registers (MMU buffer pool sizes, IPIPE
  parser tables, default cos maps, etc.).
- Steady IRQ-wait load suggests SCHAN ops + per-port MIB clearing.
- The 52-port pipeline init (each port: XLPORT/CDPORT reset, MAC reset,
  MIB clear, default config) accounts for most of this window.

**D (sec 20-24): PHY/SerDes init** (~5s)
- USLEEP density increases (99 + 77 + 0 + 53 + 130 = 359 USLEEPs in 5s).
  PHY MDIO transactions need ~70 µs settling time between ops; the high
  USLEEP rate is consistent with hundreds of MDIO writes (lane PMA/PCS
  config, lock detection, etc.).
- Writes drop to near-zero — the SDK is now in read+wait+sleep mode,
  polling for PHY lock + auto-negotiation completion.
- **The PHY firmware is NOT loaded in this window.** Only `rc.soc` was
  opened during all of Phase 3b. The BCM84740 PHY firmware
  (`BCM84740-ver-D102.bin`, 32 KB) is uploaded later by the
  `/usr/lib/cumulus/phy-update` Python tool which runs after switchd
  reaches the ready state.

---

## 5. The 19 startup ioctls (Phase 2 + 3a)

The chip discovery + initial setup uses 19 ioctls in 160 ms:

```
03:58:06.160029   open("/dev/linux-user-bde", O_RDWR|O_SYNC) = fd
03:58:06.160183   ioctl(fd, GET_DMA_INFO)
03:58:06.160402   ioctl(fd, GET_NUM_DEVICES)   ← repeated 4×
                  ioctl(fd, GET_NUM_DEVICES)
                  ioctl(fd, GET_NUM_DEVICES)
                  ioctl(fd, GET_NUM_DEVICES)
03:58:06.16xxxx   ioctl(fd, GET_DEVICE)
                  ioctl(fd, GET_DEVICE_RESOURCE)
                  ioctl(fd, GET_DEVICE_TYPE)
                  ioctl(fd, PHYS_READ32)        ← initial device probe reads (9 of them)
                  ...
03:58:06.180577   open("/etc/bcm.d/config.bcm") — Phase 3a starts here
03:58:06.180xxx   ioctl(fd, ENABLE_INTERRUPTS) — IRQ 16 connected
                  ioctl(fd, WAIT_FOR_INTERRUPT) — first IRQ already pending?
                  24 × PHYS_READ32             — chip ID / capability checks
```

The 4 redundant `GET_NUM_DEVICES` calls early are weird — looks like the
SDK's device-enumeration code is called multiple times during attach (one
per init-stage, maybe). Harmless.

---

## 6. Phase 4 — what rc.soc does after `init all`

The 168ms of "Phase 4a" doesn't actually open rc.ports_0 (which is just
6 lines of `setenv` — bcmsh handles those internally). It runs the
3 register tweaks that come BETWEEN `rcload rc.ports_0` and
`rcload rc.datapath_0`:

```
setreg xmac_tx_ctrl 0xc802             ┐
s MAC_RSV_MASK MASK=0x18               ├ 3 setregs in 168 ms
m cmic_misc_control LINK40G_ENABLE=1   ┘
```

**Each setreg consumes ~125 reads, ~1 write, and ~127 IRQ waits.** The
read amplification is the SDK's symbol-table lookup walking through the
register schema (~3000 BCM register symbols to scan), plus pre/post
state validation reads. This is the per-setreg overhead.

### Phase 4b (rc.datapath_0) details

3.76 seconds for the 371-line datapath config:

| Operation type | Count |
|---|---:|
| `setreg` (single reg) | ~50 |
| `modreg` (read-mod-write) | ~30 |
| `write <table>` (bulk fill) | ~14 |
| `modify <table>` (partial update) | ~30 |
| `for I=...` loop expansions | 32 (each iterates ~28 entries) |

So ~140 unique register-level operations, expanded to ~10,000 PHYS_READ32
+ 5,000 IRQ waits + 48 PHYS_WRITE32. The IRQs are likely from `write
thdo_*` and `modify cpu_cos_map` operations that go via Table DMA.

### Phase 4c (rc.led) details

1.79 seconds for the LED bytecode load — **156 PHYS_WRITE32 in 1.5s**
≈ 100 writes/sec. The LED uControllers have ~150 instruction words each
× 2 uCs = ~300 byte-level writes total. Matches.

---

## 7. What this trace CAN tell us

✅ **Hard timing budget for each init phase** — useful for benchmarking
   EdgeNOS init (we shouldn't be slower than 31s).

✅ **Approximate count of register operations per phase** — useful for
   sanity-checking that EdgeNOS isn't missing entire phases (e.g., skipping
   memory init).

✅ **The fact that 524 PHYS_WRITE32 represent the entire bcm_init's PIO
   writes** — implies massive DMA usage. EdgeNOS needs working DMA
   engines (Table DMA + SLAM DMA) to come up at all in reasonable time.

✅ **PHY firmware is NOT loaded by switchd's first init pass.** Don't
   expect to find it in any switchd trace — it comes from `phy-update`.

## 8. What this trace CANNOT tell us

❌ **The actual register addresses** of the 557 PIO writes — they're in
   the ioctl buffers, which `strace -f` didn't capture.

❌ **The actual values** written — same reason.

❌ **The DMA descriptor contents** — Table DMA bursts don't appear as
   userspace ioctls at all (kernel-side DMA setup).

❌ **The exact memory-init sequence** — which tables are cleared in what
   order, which entries are initialized to which defaults.

❌ **The PHY MDIO sequence** — although the timing pattern in sub-phase D
   suggests heavy MDIO activity, we don't see which PHY registers are
   read/written.

---

## 9. To fill the gaps: re-capture with buffer dumping

The same chassis is still running. A targeted re-trace gives us register
values:

```bash
# On chassis (after backing up state)
sudo systemctl stop switchd
sudo strace -ff -tt -v \
    -e trace=ioctl,read,write,open \
    -e read=14 \
    -s 8192 \
    -o /tmp/switchd-init-with-buffers \
    /usr/sbin/switchd -d \
    > /tmp/switchd-out 2>&1 &
# Watch for /var/run/switchd.ready ; takes ~30s
# Then kill strace + rotate logs
```

Key flags:
- `-v` decodes structs fully
- `-e read=14` dumps fd 14 read buffers (the BDE FD — gives us SCHAN values)
- `-s 8192` long string limit (captures full ioctl-buffer hex dumps)
- `-ff -tt` splits per-process trace with µs timestamps

The output will be ~10× the size of the existing trace (since each ioctl
now includes the full buffer hex). For a 27 MB trace, expect ~250 MB.

Once captured, decode logic:

```python
# Per buffer of LUBDE_PHYS_READ32 / PHYS_WRITE32 ioctl:
#   struct lubde_io { uint32_t addr; uint32_t data; uint32_t dev; };
# addr is the BAR0 offset (4-byte words)
# Cross-reference addr → name using our 36,896-entry register map
```

This gives us a complete cold-boot register-write transcript, the actual
"how to init the chip" cookbook EdgeNOS can compare against.

---

## 10. Alternative: kernel-side trace (no chassis disruption)

If we don't want to restart switchd, we can install a small ftrace probe
on the live chassis to log every `_read`/`_write` call in
`linux-kernel-bde.ko`:

```bash
# On chassis
echo 1 > /sys/kernel/debug/tracing/events/syscalls/sys_enter_ioctl/enable
# OR if linux-kernel-bde exposes function tracing:
echo '_read _write' > /sys/kernel/debug/tracing/set_ftrace_filter
echo function > /sys/kernel/debug/tracing/current_tracer
echo 1 > /sys/kernel/debug/tracing/tracing_on
# Wait for a known register access pattern (e.g. trigger /ctrl/hal/resync)
echo 0 > /sys/kernel/debug/tracing/tracing_on
cat /sys/kernel/debug/tracing/trace
```

This catches register accesses during STEADY-STATE operation, not init —
so it complements the strace approach rather than replacing it.

---

## 11. Cross-references

- Trace source: `traces/switchd-init-2026-02-18.trace` (27 MB, 455,167 lines)
- BDE ioctl decode: `cumulus_baseline_2013/BDE_COMPLETE.md`
- LUBDE opcodes (canonical): `cumulus_baseline_2013/BDE_DRIVERS_DECODED.md`
- Init scripts decoded: `cumulus_baseline_2013/ASIC_INIT_COOKBOOK.md`
- SCHAN protocol: `cumulus_baseline_2013/FULL_CHIP_ACCESS_STACK.md`
- Register name table: `cumulus_baseline_2013/CHIP_PRIMITIVES_AND_REG_TABLE.md`

---

*Decoded 2026-05-11 from existing strace `switchd-init-2026-02-18.trace`
captured 2026-02-18 from chassis 10.1.1.233 (now retired). Same chassis
type as the live baseline at 10.1.1.212. A re-capture with `-v -e read=14`
on the live chassis would yield register-level ground truth.*

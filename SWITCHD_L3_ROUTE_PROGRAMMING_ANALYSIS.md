# switchd L3 Route Programming — Runtime Tracing Analysis

**Date**: 2026-02-23
**Status**: COMPLETE — DMA write mechanism confirmed; L3_DEFIP ASIC entry format decoded; bcmcmd verified
**Switch**: AS5610-52X (BCM56846/Trident+), Cumulus Linux 2.5, PPC32 MSB
**switchd binary**: `/usr/sbin/switchd` loaded at VA 0x10000000–0x11808b84

---

## 1. Overview

The goal is to identify how switchd programs the L3_DEFIP (IPv4 LPM routing) table in the BCM56846 ASIC when routes are added/removed via zebra. This is the switchd-side reverse engineering.

**Route distribution path** (confirmed):
```
ospfd → zebra → zserv.api (Unix socket) → switchd → BCM SDK → ASIC
```
switchd does NOT use netlink (PID groups = 00000000). Routes come exclusively from zebra via `/var/run/quagga/zserv.api`.

---

## 2. OSPF Convergence (prerequisite for testing)

OSPF on the AS5610-52X connects to a Nexus switch at 10.101.1.241 via swp1 (10.101.101.1/29).

**Configuration required** (written to `/etc/quagga/Quagga.conf` via vtysh):
```
router ospf
 ospf router-id 10.101.101.241
 passive-interface lo
 network 10.101.101.0/29 area 0.0.0.0
 network 10.101.101.8/29 area 0.0.0.0
 network 10.101.101.241/32 area 0.0.0.0

interface swp1
 ip ospf network broadcast
 ip ospf mtu-ignore

interface swp2
 ip ospf network broadcast
 ip ospf mtu-ignore
```

**Key fix**: `ip ospf network broadcast` (NOT point-to-point) must match neighbor mode.

**Loopback address** (required for correct router-id):
```bash
ip addr add 10.101.101.241/32 dev lo
```

ospfd must be restarted after router-id change:
```bash
sudo kill $(cat /var/run/quagga/ospfd.pid)
sudo /usr/lib/quagga/ospfd -f /etc/quagga/Quagga.conf --daemon -A 127.0.0.1
```
Note: The `-f /etc/quagga/Quagga.conf` is required; starting without it loads the wrong config.

**OSPF database (after convergence)**:
- Neighbor: 10.101.1.241 (Full/DR)
- Intra-area routes: 19 networks (10.x.x.x/29, /24, /32)
- External routes (E2): 12 from ASBR 0.0.1.1 (default, 10.x.x.x/22, /24 ranges)
- All routes installed in kernel via `proto zebra`

---

## 3. soc_mem_write — Confirmed NOT Used for L3_DEFIP

**Function**: `FUN_10847ab4` (switchd PPC32)
```
FUN_10847ab4(unit=r3, table_id=r4, copyno=r5, index=r6, entry_data_ptr=r7)
```

During full OSPF convergence (31 routes) and route add/del cycles, L3_DEFIP (table ID 0x7FE = 2046) was **NEVER seen** at this function. Tables 0x699b, 0x6967, 0x8f35 appear regularly (background port/VLAN tables).

**L3_DEFIP soc_mem_t value**: found at VA 0x11463b2c (name string), pointer at 0x11ab3bfc (in 17300-entry array at 0x11ab1c04). Index = **0x7FE = 2046**.

**Conclusion**: L3_DEFIP uses a chip-specific TCAM DMA path — NOT the generic `soc_mem_write` function.

---

## 4. L3_DEFIP Write Mechanism: S-Channel DMA

### 4.1 Memory Maps in switchd

From `/proc/18653/maps`:
```
4802b000-4806b000  rw-s  a0000000  /dev/mem  ← PCI BAR0 = CMIC registers (256KB)
4806b000-4c06b000  rw-s  04000000  /dev/mem  ← DMA ring buffer (4MB)
bfacb000-bfaec000  rwxp                      ← main thread stack
10000000-11809000  r-xp  /usr/sbin/switchd
```

- **BAR0 region** (VA 0x4802b000, physical 0xa0000000): CMIC MMIO registers. CMIC_CMC0_SCHAN_CTRL = BAR0+0x32800 = VA **0x4805D800**.
- **DMA buffer** (VA 0x4806b000, physical 0x04000000): BDE DMA memory pool (64MB total; first 4MB mapped here).

### 4.2 SCHAN_CTRL Never Written by CPU

Binary scan of the switchd binary (PPC32 MSB) for `stw *,0x32800(*)` and `stw *,0x1800(*)` found **zero** matches. The CPU never directly writes SCHAN_CTRL. Instead, the DMA engine writes it internally when processing DMA descriptor rings.

### 4.3 DMA Register Writes (by CPU)

`stw rX, 0x014C(rY)` = DMA_CTRLr (CMC0+0x014C = channel 3) found at 6 real locations:
- 0x101dec8c, 0x105bec84, 0x10fce1ac, 0x10fce228, 0x10fce2c0, 0x10fd0a10

`stw rX, 0x0164(rY)` = DMA_DESC0r (CMC0+0x0164 = channel 3) found at:
- 0x10484268, 0x105becd8, 0x10e09c84, 0x10e09c98, 0x10e09cac, 0x10e09cc0

The CPU programs the DMA descriptor ring and the DMA engine takes over from there.

### 4.4 Call Chain for L3_DEFIP Writes

Captured via GDB breakpoint at ioctl filtered for main thread (r1 > 0xbfa00000) and d0=4 (LUBDE_SEM_OP_GIVE) during OSPF route convergence:

```
#0  ioctl() @ 0x0fca6b50            ← libc; fd=14 (/dev/linux-user-bde)
#1  FUN_10322DE8 @ 0x10322e2c       ← BDE ioctl wrapper
#2  FUN_10325700 @ 0x10325700       ← SEM_OP dispatcher
#3  FUN_103257B8 @ 0x10325948       ← S-channel DMA queue manager (SEM_GIVE return)
#4  FUN_10324084 @ 0x103240b8       ← S-channel dispatch wrapper
#5  indirect via BDE func ptr       ← via *(*(0x11E47008)+36)
```

**SEM_GIVE ioctl struct** at the route add event:
```
d0 = 4 (LUBDE_SEM_OP_GIVE)
d1 = 0x240008e2 (semaphore handle)
```

### 4.5 FUN_103257B8 — S-Channel DMA Queue Manager

Function at 0x103257b8, frame = 48 bytes (r31 = frame pointer):

```
Frame layout:
  r31+8:  cur_node pointer (ring node linked list traversal)
  r31+12: new_cmd (malloc'd 12-byte command descriptor)
  r31+16: arg2 & 0x7F (alignment offset)
  r31+24: arg1 saved (ring_node_ptr, from global at 0x11EBC220)
  r31+28: arg2 saved (DMA ring write position, modified to next 128-byte boundary)
```

**Flow**:
1. Calls `FUN_10325634` (LUBDE_SEM_OP_TAKE, infinite wait) on semaphore from global 0x11EBC2D0
2. Traverses linked list of ring_node structs (arg1 → linked list)
3. Calls `malloc(12)` at 0x11316d40 → allocates new_cmd struct
4. Fills new_cmd: `[0]` = ring_node->field0 + ring_node->field4 (ring tail), `[4]` = modified_arg2 (next 128-byte boundary), `[8]` = cur_node->next
5. Inserts new_cmd into linked list
6. Calls `FUN_103256C4` (LUBDE_SEM_OP_GIVE) at 0x10325944 to wake DMA thread
7. Returns ring tail VA

**Key**: `new_cmd[4] = arg2 + (128 - arg2 % 128)` = next 128-byte aligned position after the S-channel command. The S-channel command was already written to the DMA ring buffer by FUN_10324084's caller, at a VA in the 0x4806b000 region.

### 4.6 FUN_10324084 — S-Channel Dispatch Wrapper

Located at 0x10324084, called via indirect BDE function pointer:
- Saves arg1 (r3), arg2 (r4), arg3 (r5) to frame at r31+24, r31+28, r31+32
- Loads global ring_node ptr from 0x11EBC220 → passes as arg1 to FUN_103257B8
- Passes original arg2 (r4 = DMA ring write position) as arg2 to FUN_103257B8
- Returns the new DMA ring tail position

### 4.7 DMA Buffer

The DMA buffer at physical 0x04000000 is the BDE memory pool:
```
sudo /dev/mem read: 0x04000000: 0xaabbccdd (sentinel)
                    0x04000004: 0x113b5e40 (switchd data ptr)
                    0x04000008-0x0000361c: control/size fields
                    0x04000010: 0x480bb800 (VA in DMA range)
```

The DMA kernel buffer at physical 0x846060 (seen in `.BCM` ioctl's d1 field) always reads as **0xdeadbeef** — it is cleared by the kernel BDE after each DMA completion. The S-channel commands are NOT readable from user space after the fact.

The 0x4806b000 VA region (physical 0x04000000) is NOT accessible via ptrace or `/proc/PID/mem`. Must use `/dev/mem` directly for reads. GDB `shell` commands can read /dev/mem while the process is stopped.

---

## 5. BDE ioctl Mechanism (fd=14 = /dev/linux-user-bde)

### 5.1 lubde_ioctl_t Struct

```c
struct lubde_ioctl_t {
    uint32_t dev;   // [+0]  Device / magic / operation code
    uint32_t rc;    // [+4]  Return code
    uint32_t d0;    // [+8]  SEM sub-op: 3=TAKE, 4=GIVE; or ".BCM" DMA magic
    uint32_t d1;    // [+12] Semaphore handle or DMA physical addr
    uint32_t d2;    // [+16] Timeout (0xffffffff = infinite, 0xf4240 = 1s)
    uint32_t d3;    // [+20] Pointer or param
    uint32_t p0;    // [+24] Pointer field
    uint32_t dx[];  // [+28] Extended data
};
```

ALL ioctls use `_IO(LUBDE_MAGIC, n)` — there is NO separate register write ioctl. All CMIC register access is via direct mmap.

### 5.2 Pattern A: DMA Polling (".BCM" pattern)

DMA thread LWP 18691 calls at ~1726/sec:
```
cmd=0x20004c0a  (LUBDE_IOCTL)
[+0] = 0x2e42434d ".BCM"
[+12] = 0x00846060 (DMA physical address, kernel-allocated)
[+20] = 0x4c845630 (ptr to p0 field)
[+24] = 0xec315c80 (kernel VA of DMA buffer)
[+28] = 0x1053ac4c (callback function ptr in switchd text)
```

### 5.3 Pattern B: SEM_GIVE from Main Thread (L3_DEFIP trigger)

Main thread at SEM_GIVE during route add:
```
d0 = 4 (LUBDE_SEM_OP_GIVE)
d1 = 0x240008e2 (semaphore handle)
```
Stack pointer r1 > 0xbfa00000 (main thread stack at 0xbfacb000-0xbfaec000).

### 5.4 Other Patterns
| Pattern | cmd | d0 | Description |
|---------|-----|------|-------------|
| C | 0x20004c0a | 0 | Reset/idle |
| E | 0x20004c09 | 0 | LUBDE_WAIT_FOR_INTERRUPT |
| F | 0x20004c08 | 0 | LUBDE_USLEEP |
| G | 0x20004c0a | libc ptr | Interrupt callback registration |

---

## 6. L3_DEFIP Table Format (BCM56846/Trident+)

Discovered via `bcmcmd` on the running switch (tool at `/usr/lib/cumulus/bcmcmd`).

### 6.1 Table Properties

From `bcmcmd listmem l3_defip`:
```
Memory: L3_DEFIP.ipipe0   address 0x0a170000
Flags:  valid cachable
Blocks: ipipe0 (1 copy)
Entries: 8192  (indices 0-8191)
Entry width: 30 bytes (8 words; last word masked to 0x00001fff)
Total bits used: ~237
Description: L3 Default IP Route (LPM) TCAM view with data and hit bits
```

Each physical entry contains **TWO sub-entries** (0 and 1) — the Trident+ "paired TCAM" architecture allows two IPv4 routes per TCAM row.

### 6.2 Field Bit Positions (from `listmem l3_defip`)

```
Bits  237..178: Data fields (SRAM side — next-hop, class, flags)
  HIT1<236>    HIT0<235>       EVEN_PARITY<234>
  GLOBAL_ROUTE1<205>  GLOBAL_ROUTE0<233>
  CLASS_ID1<204:199>  CLASS_ID0<232:227>
  NEXT_HOP_INDEX1<192:179>  NEXT_HOP_INDEX0<220:207>
  ECMP_PTR1<188:179>        ECMP_PTR0<216:207>
  ECMP1<178>                ECMP0<206>
  SRC_DISCARD1<198>  DST_DISCARD1<198>  (same bit — mutual exclusive flags)
  RPE1<197>   DEFAULTROUTE1<197>       (same bit)
  PRI1<196:193>              PRI0<224:221>

Bits 177..0: TCAM key/mask pairs (two 44-bit KM pairs)
  Sub-entry 1 MASK: MASK1<177:134>  (44 bits)
    VRF_ID_MASK1<176:167>           (10 bits, within MASK1)
    IP_ADDR_MASK1<166:135>          (32 bits, /prefix mask)
    MODE_MASK1<134>                 (1 bit)
  Sub-entry 1 KEY: KEY1<89:46>      (44 bits)
    VRF_ID_1<88:79>                 (10 bits)
    IP_ADDR1<78:47>                 (32 bits)
    MODE1<46>                       (1 bit: 0=IPv4)
  Sub-entry 0 MASK: MASK0<133:90>   (44 bits)
    VRF_ID_MASK0<132:123>
    IP_ADDR_MASK0<122:91>
    MODE_MASK0<90>
  Sub-entry 0 KEY: KEY0<45:2>       (44 bits)
    VRF_ID_0<44:35>
    IP_ADDR0<34:3>
    MODE0<2>
  VALID1<1>  VALID0<0>
```

### 6.3 KEY and MASK Encoding

The KEY and MASK fields pack VRF + IP + MODE into a 44-bit TCAM comparison:

```
KEY  = (VRF_ID  << 33) | (IP_ADDR << 1) | MODE
MASK = (VRF_MASK << 33) | (IP_MASK << 1) | MODE_MASK
```

Example verification: 10.101.101.0/29
```
IP_ADDR = 0x0A656500 = 10.101.101.0
IP_MASK = 0xFFFFFFF8 = /29
VRF = 0, MODE = 0 (IPv4)

KEY  = (0 << 33) | (0x0A656500 << 1) | 0 = 0x000014CACA00  ← matches bcmcmd output
MASK = (0x3FF << 33) | (0xFFFFFFF8 << 1) | 1
     = 0x07FE00000000 | 0x0001FFFFFFF0 | 1 = 0x07FFFFFFFFF1  ← matches
```

**Encoding formula for /N prefix**:
- IP_MASK for /N = 0xFFFFFFFF << (32 - N)
- MASK = 0x07FFFFFFFE01 for /24, 0x07FFFFFFFFF1 for /29, 0x07FFFFFFFFFF for /32

### 6.4 Observed Routes in the ASIC

From `bcmcmd l3 defip show` (39 IPv4 routes):

| Index | IP prefix (sub-0)    | IP prefix (sub-1)    | NH_IDX0 | NH_IDX1 |
|-------|---------------------|---------------------|---------|---------|
| 2560  | 10.1.1.0/32         | 10.1.1.233/32       | 2       | 2       |
| 2561  | 10.1.1.255/32       | 10.101.101.241/32   | 2       | 2       |
| 2562  | 10.101.101.0/32     | 10.101.101.1/32     | 2       | 2       |
| 2563  | 10.101.101.7/32     | 10.101.1.217/32     | 2       | 3       |
| 2817  | 10.101.101.0/29     | 10.101.1.0/29       | 2       | 3       |
| 3072  | 10.1.1.0/24         | 10.14.1.0/24        | 2       | 3       |
| ...   | ...                 | ...                 | ...     | ...     |
| 3202  | 71.181.68.0/22      | —                   | 3       | —       |
| 3328  | 192.168.0.0/16      | —                   | 3       | —       |
| 3584  | 172.16.0.0/12       | —                   | 3       | —       |

### 6.5 Raw Dump Example — 10.101.101.0/29 and 10.101.1.0/29 (index 2817)

```
L3_DEFIP.ipipe0[2817]:
  VALID0=1, VALID1=1
  IP_ADDR0=0xa656500 (10.101.101.0), IP_ADDR_MASK0=0xfffffff8 (/29)
  IP_ADDR1=0xa650100 (10.101.1.0),   IP_ADDR_MASK1=0xfffffff8 (/29)
  KEY0=0x000014caca00, MASK0=0x07fffffffff1
  KEY1=0x000014ca0200, MASK1=0x07fffffffff1
  VRF_ID_0=0, VRF_ID_1=0
  NEXT_HOP_INDEX0=2, NEXT_HOP_INDEX1=3
  ECMP0=0, ECMP1=0
  CLASS_ID0=0, CLASS_ID1=0
  HIT0=0, HIT1=0
```

### 6.6 Raw Dump Example — 192.0.2.0/24 (single sub-entry, index 3080)

```
L3_DEFIP.ipipe0[3080]:
  VALID0=1, VALID1=0
  IP_ADDR0=0xc0000200 (192.0.2.0), IP_ADDR_MASK0=0xffffff00 (/24)
  KEY0=0x000180000400  ← verified: 0xC0000200 << 1 = 0x180000400
  MASK0=0x07fffffffe01 (/24 mask)
  NEXT_HOP_INDEX0=3 (swp1 gateway)
```

---

## 7. L3 Egress (Next-Hop) Table

From `bcmcmd l3 egress show`:

| Entry   | MAC               | VLAN | INTF | PORT | Description |
|---------|-------------------|------|------|------|-------------|
| 100000  | 00:00:00:00:00:00 | 0    | 4095 | 31   | CPU/drop    |
| 100002  | 00:00:00:00:00:00 | 0    | 4095 | 0    | Local subnet (no L3 gateway) |
| 100003  | 6c:b2:ae:cd:13:33 | 3301 | 1    | 1    | Gateway 10.101.101.2 via swp1 |

ASIC index 2 corresponds to SDK L3 interface 100002 (directly connected — ECMP_PTR=2).
ASIC index 3 corresponds to SDK L3 interface 100003 (OSPF gateway 10.101.101.2 — ECMP_PTR=3).

---

## 8. switchd Thread Map

| LWP   | Stack VA   | Role |
|-------|-----------|------|
| 18653 | main      | **Main thread** — zebra socket handler; triggers L3_DEFIP writes |
| 18691 | 0x4c846060 | **DMA polling thread** — runs `.BCM` BDE ioctls at ~1726/sec |
| 18657 | 0x4c08e060 | (background) |
| 18663 | 0x4c755000 | (background) |
| 18666 | 0x4d3c3060 | (background) |
| 18675 | 0x4d3e7060 | (background) |
| 18678 | 0x4c79d060 | (background) |
| 18679 | 0x4c7c1060 | (background) |
| 18693 | 0x4c86a060 | (background) |
| 18694 | 0x4dd8a060 | (background) |

---

## 9. bcmcmd Access

The BCM SDK CLI tool is at `/usr/lib/cumulus/bcmcmd`. Run with `sudo`. Requires no switchd downtime (read-only access works concurrently).

Useful commands:
```bash
# Show all L3 routes in the ASIC
sudo /usr/lib/cumulus/bcmcmd 'l3 defip show'

# Dump raw L3_DEFIP entry (index, count)
sudo /usr/lib/cumulus/bcmcmd 'dump l3_defip 2817 1'

# Show field layout
sudo /usr/lib/cumulus/bcmcmd 'listmem l3_defip'

# Show L3 egress next-hop table
sudo /usr/lib/cumulus/bcmcmd 'l3 egress show'

# Show register
sudo /usr/lib/cumulus/bcmcmd 'getreg CMIC_CMC0_SCHAN_CTRL'
```

---

## 10. Summary: L3_DEFIP Write Path

```
zebra → (zserv.api) → switchd main thread (LWP 18653)
  → FUN via BDE function pointer (*(*(0x11E47008)+36))
  → FUN_10324084 @ 0x10324084
      Writes S-channel WRITE_MEMORY command to DMA buffer (0x4806b000 region)
      Calls FUN_103257B8(ring_node_ptr, dma_write_pos)
  → FUN_103257B8 @ 0x103257b8
      Takes submit semaphore (FUN_10325634)
      Allocates 12-byte command descriptor
      Inserts into DMA command linked list
      Signals DMA thread via SEM_GIVE (FUN_103256C4)
  → DMA thread (LWP 18691) wakes up
      Reads command from linked list
      Programs DMA_CTRLr / DMA_DESC0r for channel 3
      Submits via BDE '.BCM' ioctl (fd=14)
      Kernel BDE: writes S-channel WRITE_MEMORY to physical 0x846060
      Hardware DMA → ASIC executes S-channel command → L3_DEFIP entry written
      Buffer cleared (0xdeadbeef)
```

**S-Channel command format** (from SDK analysis, opcode = 0x28 confirmed via `oris r9,r9,0x2800` at 17 locations in switchd binary):
- Word 0: `0x28_xx_xx_xx` = WRITE_MEMORY opcode (0x28) + channel (0) + word_count
- Word 1: Block ID + table address (L3_DEFIP base = 0x0a170000 + index)
- Words 2–5: 120-bit L3_DEFIP entry data (4 × 32-bit words)

---

## 11. References

- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — libopennsl FUN_01876c30 dispatch chain
- [BDE_CMIC_REGISTERS.md](BDE_CMIC_REGISTERS.md) — CMIC/CMICm register offsets
- [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) — S-Channel message format and `oris` instruction analysis
- [SCHAN_AND_RING_BUFFERS.md](SCHAN_AND_RING_BUFFERS.md) — DMA descriptor rings and CMICm register map
- [ASIC_INIT_AND_DMA_MAP.md](ASIC_INIT_AND_DMA_MAP.md) — /dev/mem mappings and DMA init
- Linux user BDE header: `.opennsl-extract/OpenNSL-3.5.0.1/sdk-6.5.12-gpl-modules/systems/bde/linux/user/kernel/linux-user-bde.h`

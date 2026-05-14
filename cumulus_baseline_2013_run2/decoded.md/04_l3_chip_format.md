---
name: project_l3_chip_format_decoded
description: "BCM56846 L3 chip table formats decoded from live capture — L3_DEFIP TCAM PAIR mode, L3_ENTRY hash function probe data, KEY field layout. Captured 2026-05-13."
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

# L3_DEFIP TCAM — PAIR mode confirmed
Each TCAM line can hold **two** /≤32 routes via "PAIR mode". Fields with `0`/`1` suffix are the two halves.

## Per-slot fields (from `dump L3_DEFIP` raw output)
```
KEY1 / KEY0           = IP << 3 (low 3 bits = KEY_TYPE flags)
IP_ADDR1 / IP_ADDR0   = the IP address (e.g. 0xa4d4d00 = 10.77.77.0)
IP_ADDR_MASK1 / IP_ADDR_MASK0  = prefix mask (e.g. 0xffffff00 for /24, 0xffffffff for /32)
NEXT_HOP_INDEX1 / NEXT_HOP_INDEX0   = INTF id (display is +100000; chip = just the index)
VALID1 / VALID0       = 1 if half is in use
MODE1 / MODE0         = entry mode
MODE_MASK1 / MODE_MASK0  = 1 means this half is a real route; 0 = unused half
VRF_ID_1 / VRF_ID_0   = VRF
PRI / ECMP / CLASS_ID / GLOBAL_ROUTE / DEFAULTROUTE / HIT / EVEN_PARITY
```

## Worked example (the live capture)
| Route | DEFIP slot | half | Key | IP | Mask | NHI |
|---|---|---|---|---|---|---|
| 10.66.66.66/32 | 2567 | 0 | `0x000014848484` | `0xa424242` | `0xffffffff` | 4 |
| 10.77.77.0/24  | 3080 | 0 | `0x000014b0b000` | `0xa4d4d00`  | `0xffffff00` | 4 |
| 10.88.88.0/24  | 3080 | 1 | `0x0000149a9a00` | `0xa585800`  | `0xffffff00` | 3 |

Two distinct /24 routes share slot 3080 — different halves. The single /32 sits alone in 2567 half 0.

## Implications for EdgeNOS
- We currently program L3_DEFIP one route per slot. We can DOUBLE effective TCAM capacity by using PAIR mode.
- Slot indexing is **banded by prefix length** (verified previously in [[project_cumulus_route_storage_decoded]]): /32 in 2560-2566, /24 in 3072-3080, /22 in 3586, /0 in 4096.

# L3_ENTRY (hash) — function probe data
The chip's `L3_ENTRY_IPV4_UNICAST` is **hash-indexed with 16K+ slots** (not 8K as bcm56840 OpenMDK header claims — BCM56846 is bigger).

Field layout per entry (from raw dump):
```
VRF_ID, VALID, V6, RPE, PRI, NEXT_HOP_INDEX, KEY_TYPE
KEY = IP << 3 (so low 3 bits free for type flags)
IP_ADDR = the IP (redundant with KEY but accessible as separate field)
DATA = 40-bit data word
HIT, EVEN_PARITY, DUMMY, DST_DISCARD, CLASS_ID
```

## 8 (IP, slot) data points captured 2026-05-13
| IP (decimal) | IP hex | chip slot | KEY |
|---|---|---|---|
| 10.101.101.3  | `0xa656503` | 10032 | `0x0000532b2818` |
| 10.101.101.4  | `0xa656504` | 6080  | `0x0000532b2820` |
| 10.101.101.5  | `0xa656505` | 15088 | `0x0000532b2828` |
| 10.101.101.6  | `0xa656506` | 368   | `0x0000532b2830` |
| 10.101.101.11 | `0xa65650b` | 8864  | `0x0000532b2858` |
| 10.101.101.12 | `0xa65650c` | 4688  | `0x0000532b2860` |
| 10.101.101.13 | `0xa65650d` | 16224 | `0x0000532b2868` |
| 10.101.101.14 | `0xa65650e` | 1248  | `0x0000532b2870` |

These are all from VRF 0 with KEY_TYPE=0 (IPv4 unicast). The hash function is the chip's internal CRC-style hash over (KEY, VRF, KEY_TYPE). Slots span 0-16224 so table has ~16K buckets.

## What this means for EdgeNOS

We currently use `SCHAN HASH_INSERT` (opcode 0x68000000) — the chip computes the hash itself; we don't need to know the function. **That approach is correct and complete.** This hash probe data is mostly useful for *verification* and as a fallback path:

- To **verify** SCHAN HASH_INSERT works: insert our own IP via HASH_INSERT, then `dump L3_ENTRY_IPV4_UNICAST` and confirm it landed in the expected slot.
- For **future direct-write** path (if we ever want to bypass HASH_INSERT and write the slot directly via MEM_WRITE), we'd need to derive the hash from many more data points. 8 isn't enough.

The truly useful insight is the **KEY = IP << 3** encoding: when we build an entry to HASH_INSERT, set bits 3..34 of the 96-bit entry to the IP value, low 3 bits to KEY_TYPE flags. Matches what we already do in `asic/edged/l3.c`.

## Captures
- `cumulus_baseline_2013_run2/trace_hash_redo/` — all the raw before/after dumps + strace
- `12d_new_entries.txt` — the IP→slot mappings in `l3 l3table show` format
- `12c_L3_ENTRY_raw_diff.txt` — the raw chip-side L3_ENTRY entries (with full field decode)
- `11b_switchd_strace.log` (5.7MB) — switchd's syscalls during route add (interrupt pattern + BDE ioctls)
- `11e_L3_DEFIP_raw_diff.txt` — raw chip-side L3_DEFIP entries for the new routes

Linked: [[project_schan_hash_insert]] (our HASH_INSERT impl), [[project_cumulus_route_storage_decoded]] (L3 chain), [[project_cumulus_chip_init_recipes]] (chip-init flags).

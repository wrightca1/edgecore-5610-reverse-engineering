---
name: project_schan_hash_insert
description: Switched L3_ENTRY_IPV4_UNICASTm programming from blind MEM_WRITE-all-8192-slots to SCHAN TABLE_INSERT_CMD_MSG (chip computes hash itself)
metadata: 
  node_type: memory
  type: project
  originSessionId: 5ebe4e81-6755-4df9-a6bd-900d159925f2
---

L3_ENTRY_IPV4_UNICASTm is hash-indexed. Brute-force MEM_WRITE to every index 0..8191 does NOT make the chip's lookup hit because the chip only checks the bucket(s) its internal hash picks.

The fix: dedicated SCHAN opcode TABLE_INSERT_CMD_MSG (0x24, becomes 0x68000000 in cmd word). Implemented as `l3_v4_schan_insert()` in `asic/edged/l3.c`, modeled after `bcm56840_a0_bmd_port_mac_addr_add.c`'s L2X insert. Same pattern: `schan_msg.gencmd.address = L3_ENTRY_IPV4_UNICASTm`, 3 data words, `cdk_xgs_schan_op(unit, &msg, 5, 2)`. Companion `l3_v4_schan_lookup()` issues TABLE_LOOKUP_CMD_MSG for verification.

**Why:** Cumulus RE doc `cumulus_baseline_2013/TABLE_ENTRY_HASH_OPS.md` revealed dedicated chip opcodes. Previous brute-force approach produced rx_drops += 5 per 5-ping burst because chip's lookup never hit our entries (wrong bucket).

**How to apply:** Any hash-indexed Trident+ table (L2_ENTRY, L3_ENTRY, EXACT_MATCH variants) needs HASH_INSERT/LOOKUP/DELETE — NOT MEM_WRITE by index. Indexed tables (LPORT_TAB, ING_L3_NEXT_HOP, EGR_L3_INTF, MY_STATION_TCAM) are fine with WRITE_*m macros.

Binary built 2026-05-13. **VERIFIED WORKING** on chassis 10.1.1.212 (corrected IP — Cumulus baseline at .212 is now overwritten by EdgeNOS):
- swp2/10.101.101.10 → `schan_insert -> 3984` (chip picked hash bucket 3984)
- `lookup OK: idx=3984 nhi=3 valid=1` (chip can find the entry back)
- Encoding (KEY_TYPE=0, V6=0, VRF_ID=0, IP_ADDR=ipv4 host-order, NEXT_HOP_INDEX, VALID=1) matches what the chip's hash key expects.

Trigger path: `ip addr add <ip>/29 dev swpN` → kernel RTM_NEWADDR → edged netlink_poll → l3_local_host_add → SCHAN INSERT + LOOKUP verify.

**Gotcha caught:** systemd-journald rate-limit drops syslog messages under DMA-timeout flood. Logs survive in `/var/log/daemon.log` (rsyslog) but journalctl misses them. When debugging high-volume edged sessions, grep `/var/log/daemon.log` not `journalctl`.

**End-to-end ping test 2026-05-13** — chip TX/RX/L3 lookup all confirmed working at silicon level. 5 pings EdgeNOS→Nexus: `tx_pkts +6` (ARP + 5 echo req egressed), `rx_pkts +3` (replies arrived at chip), `rx_drops 4→4` (L3 lookup HIT, no drops), but kernel received 0 replies. Bottleneck is now CMIC RX DMA chan=1 timing out — chip is delivering frames to CMIC queue but CPU isn't pulling them off. Hash insert + lookup verified at chip-side buckets 3984 (swp2 own IP) and 13328 (Nexus neighbor) — both encodings produce HITs.

See [[project_session_20260512_supersedes_hwblocks]] for HW state at time of fix.

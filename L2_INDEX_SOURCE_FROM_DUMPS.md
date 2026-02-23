# L2 table index source (Path B 3.10)

**Source**: Dumps of FUN_01408a48, FUN_01cc2f2c, FUN_00948700. Traces where **r6** (index to FUN_01876f10) comes from.

---

## Flow

- **FUN_01408a48** receives index as **r5** (5th arg). At 01408b18: `or r6,r31,r31` where r31=r5, then `bl 0x01876f10` with r6=index. So **index = 5th argument** to 01408a48.
- **Callers of 01408a48**:
  1. **FUN_01cc2f2c** @ 01cc3050
  2. **FUN_00948700** @ 00948838

---

## 01cc2f2c — retry loop (indices 0..5)

- Before call: `li r5,0x0` then loop with `lwz r5,0x8(r1)`; `addi r5,r5,0x1`; `cmpwi cr7,r5,0x5`; `stw r5,0x8(r1)`.
- **r5 = 0, 1, 2, 3, 4, 5** — sequential retry. On `bge` (return ≥ 0) it exits; otherwise increments and retries.
- So **01cc2f2c** does **linear probe** over indices 0..5; no hash. The chosen index is whichever succeeds first.

---

## 00948700 — index = -1 (auto)

- Before call: `li r5,-0x1` (r5 = -1).
- **01408a48** when r5=-1: branches at 01408b78 (cmpwi r31,-0x1) to path that uses bounds from descriptor (0x10(r10)); likely lets internal logic pick index or uses a default.

---

## Summary

- **Index source**: (a) **01cc2f2c**: sequential 0..5 (retry until success); (b) **00948700**: -1 (auto).
- **Hash**: No hash function or key→index mapping visible in these paths. Index is either trial (0..5) or -1.
- **Further**: Hash/key→index, if used, would be in another path (e.g. L3, or L2 add that passes a computed index). Search for calls to hash-like functions (mullw, xor, rlwinm on MAC/VLAN) before table write.

---

## References

- [L2_WRITE_PATH_ANALYSIS.md](L2_WRITE_PATH_ANALYSIS.md)
- [L3_NEXT_STEPS.md](L3_NEXT_STEPS.md) §5 (Hash/index)
- Dumps: libopennsl-dump-01408a48.txt, libopennsl-dump-01cc2f2c.txt, libopennsl-dump-0948700.txt

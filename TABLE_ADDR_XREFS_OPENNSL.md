# Table Address Xrefs (libopennsl)

**Date**: 2026-02-18  
**Source output**: `build-server/opennsl/sdk-deep-extract/opennsl-table-addr-xrefs.txt`  
**Ghidra script**: `scripts/reverse-engineering/XrefTableAddressConstants.java`

## What this gives us

We picked a few “anchor” table-memory constants (all in the `0x01xxxxxx` region) and asked Ghidra:

- where those constants live as data
- which code locations reference those data items
- which functions those xrefs occur in

This is the bridge from “20k addresses” → “which parts of the SDK use them”.

## Current anchors and where they lead

### `0x01000000`

- **Data locations**: `DATA@02f517ec`
- **Xrefs**:
  - `XREF@01905c94` in `FUN_01905af8` (WRITE): `stw r0,0x0(r9)`

### `0x0180c200` (also seen in `switchd`)

- **Data locations**:
  - `DATA@01e00678`
  - `DATA@02f51a74`
- **Xrefs**:
  - `XREF@00881f40` in `FUN_00881edc` (READ): `lwz r11,0x0(r9)`
  - `XREF@009487c8` in `FUN_00948700` (READ): `lwz r10,0x0(r9)`
  - `XREF@01cc2fd8` in `FUN_01cc2f2c` (READ): `lwz r8,0x0(r11)`

### `0x01312d00`

- **Data locations**:
  - `DATA@01f25cc8`
  - `DATA@01f25da0`
- **Xrefs**:
  - `XREF@01452f2c` in `FUN_01452b3c` (READ): `lwz r0,0x0(r23)`
  - `XREF@0145327c` in `FUN_01452b3c` (READ): `lwz r0,0x0(r9)`

### `0x01560974`

- **Data locations**:
  - `DATA@012b0a5c`
  - `DATA@012b1340`
- **Xrefs**:
  - `XREF@012b0a7c` in `FUN_012b0a60` (READ): `lwz r0,-0x10(r30)`
  - `XREF@012b1360` in `FUN_012b1344` (READ): `lwz r0,-0x10(r30)`

### `0x01855abc`

- **Data locations**:
  - `DATA@00faf858`
  - `DATA@00fafbcc`
- **Xrefs**:
  - `XREF@00faf874` in `FUN_00faf85c` (READ): `lwz r0,-0x10(r30)`
  - `XREF@00fafbfc` in `FUN_00fafbd0` (READ): `lwz r0,-0x10(r30)`

## Next xref expansions

To turn these into **named tables**, the next iteration is:

- expand the anchor list (10–50 values)
  - include bucket boundaries like `0x01b00000`, `0x01c00000`, `0x01f00000`
  - include known “base-ish” values like `0x01000000`, `0x0180c200`
- for each xref’d function:
  - dump nearby referenced strings (often includes table names / error strings)
  - dump calls made by that function (e.g., mem read/write helpers)



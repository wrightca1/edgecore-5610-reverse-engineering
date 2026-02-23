# Warpcore WC-B0 SerDes MDIO Initialization Sequence

**Date**: 2026-02-23
**Status**: HAVE — live capture via GDB hardware watchpoint on CMIC_MIIM_ADDRESS
**Switch**: AS5610-52X (BCM56846/Trident+), Cumulus Linux 2.5
**Port**: xe0/swp1 (xlport16, lane 0), PHY_ADDR=17=0x11, MDIO addr=0xd1

---

## 1. CMIC MIIM Register Format (Verified)

### 1.1 CMIC_MIIM_PARAM (BAR0 + 0x158 = VA 0x4802b158)

```
Bits [31:26]: reserved / status (0 during writes)
Bit  [25]:    INTERNAL_SEL = 1 for internal MDIO bus (Warpcore is always internal)
Bits [24:22]: BUS_ID = 0b010 = 2 for xlport16/xlport17 (xe0-xe7)
Bit  [21]:    C45_SEL = 0 for clause-22, 1 for clause-45
Bits [20:16]: PHY_ADDR (5 bits, = MDIO_addr & 0x1f)
Bits [15:0]:  DATA field (0x0000 = READ operation; non-zero = WRITE with this data)
```

**Examples:**
| MIIM_PARAM   | PHY_ADDR | DATA   | Operation |
|--------------|----------|--------|-----------|
| 0x02910000   | 17 (xe0) | 0x0000 | READ      |
| 0x02918010   | 17 (xe0) | 0x8010 | WRITE     |
| 0x02950000   | 21 (xe4) | 0x0000 | READ      |
| 0x02958340   | 21 (xe4) | 0x8340 | WRITE     |

### 1.2 CMIC_MIIM_ADDRESS (BAR0 + 0x4a0 = VA 0x4802b4a0)

```
Bits [4:0]: Clause-22 register address (0x00-0x1f)
```

Writing to CMIC_MIIM_ADDRESS **triggers** the MDIO transaction (read or write) configured in MIIM_PARAM.

### 1.3 PHY Address Map (Clause-22)

| Port(s) | MDIO addr (bcm) | PHY_ADDR (bits[4:0]) | BUS_ID | MIIM_PARAM upper |
|---------|-----------------|----------------------|--------|------------------|
| xe0     | 0xd1            | 17 = 0x11            | 2      | 0x02910000       |
| xe1     | 0xd2            | 18 = 0x12            | 2      | 0x02920000       |
| xe2     | 0xd3            | 19 = 0x13            | 2      | 0x02930000       |
| xe3     | 0xd4            | 20 = 0x14            | 2      | 0x02940000       |
| xe4     | 0xd5            | 21 = 0x15            | 2      | 0x02950000       |
| xe8     | 0x85            | 5 = 0x05             | ?      | 0x0205xxxx       |

### 1.4 CMIC MIIM Write Path in switchd

The actual CMIC register writes do NOT use a direct `stw rX, 0x158(BAR0)` pattern (the binary
scan approach missed these). Instead, the code uses an indirect pointer:

```asm
; At 0x1082ffd8 in switchd (the low-level CMIC write function):
mr   r9, r3              ; r3 = register offset (e.g. 0x4a0 for MIIM_ADDRESS)
rlwinm r9, r9, 30, 2,31  ; r9 = r3 >> 2
rlwinm r10, r9, 2, 0,29  ; r10 = r9 << 2 = r3 (word-aligned register offset)
lis  r9, 4626            ; load global table base
addi r8, r9, 23596       ; r8 = table_base
lwz  r9, 56(r31)         ; r9 = unit index from frame
mulli r9, r9, 120        ; r9 = unit * 120
add  r9, r8, r9          ; r9 = table + unit*120
addi r9, r9, 48          ; r9 = per-unit entry + 48
lwz  r9, 0(r9)           ; r9 = BAR0 base pointer (0x4802b000)
add  r9, r10, r9         ; r9 = BAR0 + register_offset
lbz  r10, 62(r31)        ; r10 = byte value from caller
clrlwi r10, r10, 24      ; zero-extend
stw  r10, 0(r9)          ; WRITE to CMIC register  ← 0x1083000c
b    0x10830094          ; continue                ← 0x10830010 (watchpoint fires here)
```

The watchpoint on `*(unsigned int*)0x4802b4a0` fires at PC=0x10830010 (one instruction after
the store at 0x1083000c).

---

## 2. Warpcore Clause-22 Page Map (Decoded from Live Captures)

| Page (reg 0x1f value) | Usage | Write/Read observed |
|----------------------|-------|-------------------|
| 0x0000 | Standard MII / page 0 (Broadcom extended regs) | Frequently written |
| 0x0001 | Broadcom page 1 | Writes to reg 0x11, 0x15 |
| 0x0002 | Broadcom page 2 | Writes to reg 0x10, 0x11, 0x15 |
| 0x0003 | Broadcom page 3 | Writes to reg 0x11, 0x15 |
| 0x0008 | WC IEEE block (port disable/enable?) | Writes to reg 0x1e=0x8000 |
| 0x0a00 | WC SerDes digital control | Writes to reg 0x10=0xffe0 |
| 0x1000 | WC AN/clock recovery | Writes to reg 0x18=0x8010 |
| 0x1800 | WC_UCONFIG lane 0 (xe0) | Reads reg 0x01 (link status) |
| 0x1801 | WC_UCONFIG lane 1 (xe1) | Reads reg 0x01 |
| 0x1802 | WC_UCONFIG lane 2 (xe2) | Reads reg 0x01 |
| 0x1803 | WC_UCONFIG lane 3 (xe3) | Reads reg 0x01 |
| 0x3800 | WC_CORE (top-level sequencer control) | Read reg 0x00; write reg 0x01=0x0010 |

---

## 3. Steady-State Link Maintenance Loop (per-port polling)

When a port has link, switchd runs this maintenance loop approximately every 30ms per port:

```
-- Per-lane loop (N = 0..3, pages 0x1800..0x1803) --
write PAGE_SELECT = 0x1800+N           ; select Warpcore lane N
read  reg[0x01]                        ; poll MII_STATUS for link up/down

-- Standard page maintenance --
write PAGE_SELECT = 0x0000             ; page 0
write reg[0x1e]  = 0xffd0              ; clear/update test/config bits
write reg[0x15]  = 0x8340              ; Aux Control/Status
write reg[0x10]  = 0x80b0/0x80c0/0x80d0/0x80e0  ; rotating through 4 lanes
write reg[0x11]  = 0xffe0              ; misc config
write reg[0x12]  = 0x81d0              ; status register update
```

---

## 4. SerDes Init Sequence (Triggered on Port Link-Down → Link-Up)

Captured via GDB watchpoint on CMIC_MIIM_ADDRESS during `ip link set swp1 down/up` (xe0).
Sequence begins at approximately event 47 in the GDB log (after the port flap is detected).

### 4.1 TX Configuration (Events 47-51)

```
write PAGE_SELECT = 0x0000             ; standard page 0
write reg[0x17]  = 0x8010              ; TX configuration (drive strength low bits)
write PAGE_SELECT = 0x0000
write reg[0x18]  = 0x8370              ; TX amplitude/drive strength (3× written)
write reg[0x18]  = 0x8370
```

### 4.2 IEEE/SerDes Block Enable (Events 52-55)

```
write PAGE_SELECT = 0x0008             ; WC IEEE block
write reg[0x1e]  = 0x8000              ; enable IEEE block features
write PAGE_SELECT = 0x0000             ; back to page 0
write reg[0x1e]  = 0x8000              ; page 0 reg 0x1e = 0x8000 (differs from normal 0xffd0)
```

### 4.3 AN/Clock Recovery Config (Events 56-61)

```
write PAGE_SELECT = 0x1000             ; WC AN/clock recovery page
write reg[0x18]  = 0x8010              ; clock recovery config (written 3×)
write reg[0x18]  = 0x8010
write reg[0x18]  = 0x8010
```

### 4.4 SerDes Digital Control (Events 62-63)

```
write PAGE_SELECT = 0x0a00             ; WC SerDes digital page
write reg[0x10]  = 0xffe0              ; SerDes digital control: fiber mode, all features enabled
                                       ; 0xffe0 = 0b1111111111100000
```

### 4.5 Extended Page 0 Registers (Events 64-67)

```
write PAGE_SELECT = 0x0000             ; page 0
write reg[0x14]  = 0x81d0              ; extended control register
write reg[0x1e]  = 0xffd0              ; restore normal reg 0x1e value
```

### 4.6 Warpcore Core Sequencer Read (Events 68-69)

```
write PAGE_SELECT = 0x3800             ; WC_CORE top-level control
read  reg[0x00]                        ; read core status (check sequencer ready)
write PAGE_SELECT = 0x0000             ; back to page 0
```

### 4.7 RX Equalization Configuration (Events 72-81)

```
write PAGE_SELECT = 0x0000             ; page 0
write reg[0x11]  = 0x81d0              ; RX control (changed from normal 0xffe0)
write reg[0x19]  = 0x8320              ; RX EQ coefficient A
write reg[0x1a]  = 0x8320              ; RX EQ coefficient B
write reg[0x1b]  = 0x8320              ; RX EQ coefficient C
write reg[0x1d]  = 0x8350              ; RX EQ coefficient D
write reg[0x14]  = 0xffe0              ; extended control 2
write reg[0x1e]  = 0xffd0              ; restore normal reg 0x1e
```

### 4.8 Warpcore Core Sequencer Start (Events 86-93)

```
write PAGE_SELECT = 0x3800             ; WC_CORE control
write reg[0x01]  = 0x0010              ; trigger core op (bit 4 = start/enable)
write PAGE_SELECT = 0x0000
write reg[0x1e]  = 0xffd0              ; normal maintenance
write reg[0x1e]  = 0xffd0
write PAGE_SELECT = 0x3800
write reg[0x00]  = 0x0010              ; confirm/clear sequencer (bit 4 = done/ack)
```

*(This PAGE_SELECT + READ/WRITE on page 0x3800 sequence repeats 3-4 times while polling
for sequencer completion.)*

### 4.9 Post-Init Tuning (Events 97-121)

```
write PAGE_SELECT = 0x0000
write reg[0x10]  = 0xffe0              ; update reg 0x10
write reg[0x14]  = 0x81d0              ; update reg 0x14
write PAGE_SELECT = 0x3800             ; poll core completion again
...
write reg[0x11]  = 0x81d0              ; RX control fine-tune
write reg[0x12]  = 0x81d0              ; additional status
write reg[0x10]  = 0x81d0
write reg[0x14]  = 0x8300              ; further config
write reg[0x17]  = 0x8010              ; re-apply TX config
write reg[0x12]  = 0x81d0
write reg[0x10]  = 0x81d0
```

After this, the port returns to the normal steady-state maintenance loop (events 122+).

---

## 5. Register Value Interpretations

| Register           | Value  | Interpretation |
|-------------------|--------|----------------|
| page0, reg[0x17]  | 0x8010 | TX control, bit 15=valid, bits[4]=10G mode |
| page0, reg[0x18]  | 0x8370 | TX drive: 0x8370=0b10000011_01110000, pre-emphasis + amplitude |
| page0, reg[0x18]  | 0x8010 | (on page 0x1000) clock recovery enable |
| page0x0008,0x1e   | 0x8000 | IEEE block enable (bit 15) |
| page0xa00, 0x10   | 0xffe0 | SerDes digital: fiber/SFI mode, disable power-save |
| page0, reg[0x14]  | 0x81d0 | Extended TX control |
| page0, reg[0x19-1b]| 0x8320 | RX equalizer CTLE coefficients (0x8320 ≈ medium boost) |
| page0, reg[0x1d]  | 0x8350 | RX final EQ adjustment |
| page0x3800, 0x01  | 0x0010 | WC_CORE start (bit 4 = trigger) |
| page0x3800, 0x00  | 0x0010 | WC_CORE ack/done |
| page0, reg[0x1e]  | 0xffd0 | Steady-state: clear test bits, set normal config |
| page0, reg[0x15]  | 0x8340 | Aux control: fiber mode, no loopback, speed=10G |

---

## 6. Software Architecture

### 6.1 Call Chain

```
switchd PHY management timer
  → phymod_phy_notify_os_link_change() or similar
    → 0x10774bec / 0x10774dec  (MIIM read/write wrappers, r8=0/1)
      → 0x107747bc              (core MIIM dispatcher)
        → 0x107691d4            (translate port+reg_id to MDIO addr/devad)
        → 0x10777eec            (soc_miim_write equivalent)
          → 0x1082ffd8          (low-level CMIC register write)
            → stw r10, 0(r9)   ← actual CMIC_MIIM_ADDRESS write at 0x1083000c
```

### 6.2 PHY Control API Dispatch (at 0x1048173c)

The large init table at `0x10b08620–0x10b16fc0` calls `0x1048173c(unit, port, ctrl_id, &struct)`
for each PHY control operation. The `ctrl_id` values (r5) are BCM SDK internal control IDs
(e.g., 67=0x43, 74=0x4a), indexing a per-port function pointer table. This is the phymod
control dispatch layer.

---

## 7. GDB Capture Methodology

```bash
# On switch (as root):
cat > /tmp/gdb_miim.gdb << EOF
set pagination off
set confirm off
attach $(pgrep -x switchd)
watch *(unsigned int*)0x4802b4a0    # CMIC_MIIM_ADDRESS
commands 1
  silent
  x/1xw 0x4802b4a0                  # value written
  x/1xw 0x4802b158                  # CMIC_MIIM_PARAM
  cont
end
cont
EOF
sudo gdb -x /tmp/gdb_miim.gdb /usr/sbin/switchd > /tmp/gdb_miim_log.txt &
# ... trigger port flap ...
# Then parse log with awk
awk '/^0x4802b4a0/{addr=$2; getline; if(/^0x4802b158/){print addr, $2}}' /tmp/gdb_miim_log.txt
```

**Notes**:
- The hardware watchpoint fires AFTER the store; PC shown is the NEXT instruction (0x10830010).
- MIIM_ADDRESS writes happen for BOTH read and write MDIO operations (writing MIIM_ADDRESS triggers the transaction).
- BAR0 must be re-verified if switchd restarts (check `/proc/$(pgrep switchd)/maps`).

---

## References

- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) — XLPORT block addresses and per-lane offsets
- [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md)
- BCM56846 CMIC MIIM registers: CMIC_MIIM_PARAM=0x158, CMIC_MIIM_ADDRESS=0x4a0 (BAR0-relative)

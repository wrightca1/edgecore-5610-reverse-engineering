# Stats Counter Register Format — BCM56846 (Trident+)

**Date**: 2026-02-24
**Status**: HAVE — register addresses and field layouts verified via bcmcmd listreg/getreg on live switch
**Switch**: Edgecore AS5610-52X / Cumulus Linux 2.5 / 10.1.1.233

---

## Summary

BCM56846 has two categories of statistics counters:

| Category | Location | Width | Count/port |
|----------|----------|-------|----------|
| **XLMAC counters** | XLMAC block within each XLPORT | 40- or 48-bit (read as 64-bit via S-Channel) | ~30 per port |
| **Pipeline counters** | ipipe0 block (CPU port) | 32-bit | CPU/global only |

All counters are read-clear or read (depending on bcmcmd counter collection config). The SDK reads them periodically via a counter thread (every ~100ms by default) and accumulates 64-bit software values to prevent overflow.

---

## 1. S-Channel Register Address Encoding

Counter registers are addressed by the S-Channel using the format:

```
S_chan_addr = (block_id << 20) | (lane_in_block << 12) | reg_offset
```

where:
- `block_id` — XLPORT block identifier (see §2)
- `lane_in_block` — which of the 4 lanes within the block (0–3)
- `reg_offset` — XLMAC counter register number (see §3)

**Example**: RPKT.xe0 = `(0x40a << 20) | (0 << 12) | 0x0b = 0x40a0000b` ✓
**Example**: RPKT.xe1 = `(0x40a << 20) | (1 << 12) | 0x0b = 0x40a0100b` ✓

---

## 2. Port → Block/Lane Mapping

From verified `getreg RPKT` output (all 52 ports):

| Port range | XLPORT block | block_id | lane order (xe→lane) |
|-----------|-------------|----------|---------------------|
| xe0–xe3 | xlport0 | 0x40a | xe0=0, xe1=1, xe2=2, xe3=3 |
| xe4–xe7 | xlport1 | 0x40b | xe4=0, xe5=1, xe6=2, xe7=3 |
| xe8–xe11 | xlport2 | 0x00b | xe8=0, xe9=1, xe10=2, xe11=3 |
| xe12–xe15 | xlport3 | 0x00c | xe12=0, xe13=1, xe14=2, xe15=3 |
| xe16–xe19 | xlport4 | 0x00d | xe16=0, xe17=1, xe18=2, xe19=3 |
| xe20–xe23 | xlport5 | 0x00e | xe20=**1**, xe21=**0**, xe22=**3**, xe23=**2** (scrambled) |
| xe24–xe27 | xlport6 | 0x00f | xe24=**1**, xe25=**0**, xe26=**3**, xe27=**2** (scrambled) |
| xe28–xe31 | xlport7 | 0x400 | xe28=0, xe29=1, xe30=2, xe31=3 |
| xe32–xe35 | xlport8 | 0x401 | xe32=0, xe33=1, xe34=2, xe35=3 |
| xe36–xe39 | xlport9 | 0x402 | xe36=0, xe37=1, xe38=2, xe39=3 |
| xe40–xe43 | xlport10 | 0x403 | xe40=0, xe41=1, xe42=2, xe43=3 |
| xe44–xe47 | xlport11 | 0x404 | xe44=0, xe45=1, xe46=2, xe47=3 |
| xe48 | xlport15 | 0x406 | xe48=0 (40G port, single lane) |
| xe49 | xlport14 | 0x405 | xe49=0 (40G port, single lane) |
| xe50 | xlport18 | 0x409 | xe50=0 (40G port, single lane) |
| xe51 | xlport17 | 0x408 | xe51=0 (40G port, single lane) |

**S-Channel address formula**:
```c
uint32_t stat_reg_addr(int xcport, int reg_offset) {
    static const struct { uint32_t block_id; int base_xe; int lane[4]; } ports[] = {
        { 0x40a, 0,  {0,1,2,3} },  // xe0-xe3
        { 0x40b, 4,  {0,1,2,3} },  // xe4-xe7
        { 0x00b, 8,  {0,1,2,3} },  // xe8-xe11
        { 0x00c, 12, {0,1,2,3} },  // xe12-xe15
        { 0x00d, 16, {0,1,2,3} },  // xe16-xe19
        { 0x00e, 20, {1,0,3,2} },  // xe20-xe23 (scrambled)
        { 0x00f, 24, {1,0,3,2} },  // xe24-xe27 (scrambled)
        { 0x400, 28, {0,1,2,3} },  // xe28-xe31
        { 0x401, 32, {0,1,2,3} },  // xe32-xe35
        { 0x402, 36, {0,1,2,3} },  // xe36-xe39
        { 0x403, 40, {0,1,2,3} },  // xe40-xe43
        { 0x404, 44, {0,1,2,3} },  // xe44-xe47
        { 0x406, 48, {0,0,0,0} },  // xe48 only
        { 0x405, 49, {0,0,0,0} },  // xe49 only
        { 0x409, 50, {0,0,0,0} },  // xe50 only
        { 0x408, 51, {0,0,0,0} },  // xe51 only
    };
    // Find the block for this port
    for each entry: if xcport in range [entry.base_xe, base_xe+4):
        lane = entry.lane[xcport - entry.base_xe];
        return (entry.block_id << 20) | (lane << 12) | reg_offset;
}
```

---

## 3. XLMAC Counter Register Offsets

All XLMAC counters are 64-bit (read as two 32-bit S-Channel reads). Field widths from `listreg`:

### 3.1 RX Counters (MAC_GRx*)

| Counter name | SDK alias | reg_offset | Width | Description |
|-------------|-----------|-----------|-------|-------------|
| R64 | MAC_GRx64 | 0x000 | COUNT<39:0> | RX 64-byte frames |
| R127 | MAC_GRx127 | 0x001 | COUNT<39:0> | RX 65–127-byte frames |
| R255 | MAC_GRx255 | 0x002 | COUNT<39:0> | RX 128–255-byte frames |
| R511 | MAC_GRx511 | 0x003 | COUNT<39:0> | RX 256–511-byte frames |
| R1023 | MAC_GRx1023 | 0x004 | COUNT<39:0> | RX 512–1023-byte frames |
| RPKT | MAC_GRxPkt | 0x00b | COUNT<39:0> | RX total packets |
| RUCA | MAC_GRxUCA | 0x00c | COUNT<39:0> | RX unicast frames |
| RMCA | MAC_GRxMCA | 0x00d | COUNT<39:0> | RX multicast frames |
| RBCA | MAC_GRxBCA | 0x00e | COUNT<39:0> | RX broadcast frames |
| RPOK | MAC_GRxPOK | 0x022 | COUNT<39:0> | RX good (no error) frames |
| RBYT | MAC_GRxByt | 0x034 | COUNT<47:0> | RX bytes (48-bit) |

### 3.2 TX Counters (MAC_GTx*)

| Counter name | SDK alias | reg_offset | Width | Description |
|-------------|-----------|-----------|-------|-------------|
| T64 | MAC_GTx64 | 0x039 | COUNT<39:0> | TX 64-byte frames |
| T127 | MAC_GTx127 | 0x03a | COUNT<39:0> | TX 65–127-byte frames |
| T255 | MAC_GTx255 | 0x03b | COUNT<39:0> | TX 128–255-byte frames |
| T511 | MAC_GTx511 | 0x03c | COUNT<39:0> | TX 256–511-byte frames |
| T1023 | MAC_GTx1023 | 0x03d | COUNT<39:0> | TX 512–1023-byte frames |
| TPOK | MAC_GTxPOK | 0x044 | COUNT<39:0> | TX good (no error) frames |
| TPKT | MAC_GTxPkt | 0x045 | COUNT<39:0> | TX total packets |
| TUCA | MAC_GTxUCA | 0x046 | COUNT<39:0> | TX unicast frames |
| TMCA | MAC_GTxMCA | 0x047 | COUNT<39:0> | TX multicast frames |
| TBCA | MAC_GTxBCA | 0x048 | COUNT<39:0> | TX broadcast frames |
| TBYT | MAC_GTxBYT | 0x064 | COUNT<47:0> | TX bytes (48-bit) |

---

## 4. Pipeline Counters (ipipe0)

These are 32-bit counters in the ingress pipeline block. They count CPU-punted packets and IP routing statistics.

| Counter name | S-Chan address | Width | Description |
|-------------|---------------|-------|-------------|
| RIPC4 | 0x0f100001 | COUNT<25:0>, EVEN_PARITY<26> | RX IPv4 L3 unicast frames punted to CPU |
| RUC | 0x0f100009 | COUNT<25:0>, EVEN_PARITY<26> | RX L3 unicast frames (all) |
| RDBGC1 | 0x0f10000c | COUNT<25:0>, EVEN_PARITY<26> | RX debug counter 1 (configurable) |

These are single-instance (cpu0, not per-physical-port). They count ingress pipeline events for packets that were L3-routed.

---

## 5. Live Readings (xe0, 2026-02-24)

`bcmcmd 'show counters xe0'` after extended operation:

```
RIPC4.xe0  :          19     ← IPv4 unicast (punted to CPU)
RUC.xe0    :       2,160     ← unicast (SDK counter; same as RUCA on XLMAC)
RDBGC1.xe0 :       8,113     ← debug (L3 forwarded)
R64        :       2,129     ← 64-byte frames RX
R127       :       7,978     ← 65-127B RX
R255       :         126
R511       :       1,114
R1023      :           3
RPKT       :      11,350     ← total RX packets
RUCA       :       2,160     ← unicast RX (XLMAC)
RMCA       :       9,184     ← multicast RX
RBCA       :           6     ← broadcast RX
RPOK       :      11,350     ← good RX (= RPKT when no errors)
RBYT       :   1,146,807     ← RX bytes
T64        :       2,134
T127       :      10,631
T255       :         181
T511       :         160
T1023      :          16
T1518      :         109
TPOK       :      13,231
TPKT       :      13,231     ← total TX packets
TUCA       :       1,737
TMCA       :       9,371
TBCA       :       2,123
TBYT       :   1,368,447     ← TX bytes
UC_PERQ_PKT(3).xe0  :  13,231  ← per-COS TX packet count (COS queue 3)
UC_PERQ_BYTE(3).xe0 :  1,368,447
```

---

## 6. Implementation Guide — bcm56846_stat_get()

### 6.1 Mapping opennsl_stat_val_t to Register

```c
typedef struct {
    uint32_t reg_offset;    // XLMAC register offset (for XLMAC counters)
    bool is_pipeline;       // true = pipeline counter (ipipe0), not XLMAC
    uint32_t pipeline_addr; // S-Channel address for pipeline counters
    bool is_48bit;          // true = COUNT<47:0>, false = COUNT<39:0>
} stat_reg_t;

static const stat_reg_t stat_map[] = {
    [opennslStatRxPackets]       = { .reg_offset = 0x00b },  // RPKT
    [opennslStatRxBytes]         = { .reg_offset = 0x034, .is_48bit = true },  // RBYT
    [opennslStatTxPackets]       = { .reg_offset = 0x045 },  // TPKT
    [opennslStatTxBytes]         = { .reg_offset = 0x064, .is_48bit = true },  // TBYT
    [opennslStatRxUcastPackets]  = { .reg_offset = 0x00c },  // RUCA
    [opennslStatTxUcastPackets]  = { .reg_offset = 0x046 },  // TUCA
    [opennslStatRxMcastPackets]  = { .reg_offset = 0x00d },  // RMCA
    [opennslStatTxMcastPackets]  = { .reg_offset = 0x047 },  // TMCA
    [opennslStatRxBcastPackets]  = { .reg_offset = 0x00e },  // RBCA
    [opennslStatTxBcastPackets]  = { .reg_offset = 0x048 },  // TBCA
    [opennslStatRx64Octets]      = { .reg_offset = 0x000 },  // R64
    [opennslStatRx65to127Octets] = { .reg_offset = 0x001 },  // R127
    // ... etc
};
```

### 6.2 Reading a Counter

```c
int bcm56846_stat_get(int port, opennsl_stat_val_t stat, uint64_t *val) {
    const stat_reg_t *reg = &stat_map[stat];
    uint32_t s_chan_addr = stat_reg_addr(port, reg->reg_offset);

    // Issue S-Channel READ REGISTER command
    uint32_t words[2];
    schan_read64(s_chan_addr, words);   // reads 64-bit counter as 2×32-bit words

    if (reg->is_48bit)
        *val = ((uint64_t)words[1] << 32) | words[0];  // COUNT<47:0>
    else
        *val = (uint64_t)(words[0] & 0xFFFFFFFF) |
               ((uint64_t)(words[1] & 0xFF) << 32);    // COUNT<39:0>
    return 0;
}
```

### 6.3 Counter Thread (Overflow Prevention)

SDK counters are 40-bit hardware (max ~1T packets or ~280PB bytes). For 10G ports at line rate:
- Packet counter saturates in ~16 hours (40-bit rollover)
- Byte counter (48-bit): saturates in ~3 days

Poll interval: 100ms is more than sufficient to prevent rollover.

```c
void counter_poll_thread(void) {
    while (running) {
        usleep(100 * 1000);   // 100ms
        for (int port = 0; port < 52; port++) {
            for each stat:
                hw = bcm56846_stat_get_hw(port, stat);
                // delta = hw - last_hw (handle rollover)
                software_counter[port][stat] += delta;
                last_hw[port][stat] = hw;
        }
    }
}
```

---

## 7. bcmcmd Reference

```bash
# Show formatted counters for a port
bcmcmd 'show counters xe0'
bcmcmd 'show counters xe0 xe1 xe2'

# Read raw register value
bcmcmd 'getreg RPKT xe0'         # → RPKT.xe0[0x40a0000b] = 0x2d5e
bcmcmd 'getreg RBYT xe0'         # → RBYT.xe0[0x40a00034] = ...

# List register fields
bcmcmd 'listreg RPKT'            # → address 0x40a0000b, COUNT<39:0>
bcmcmd 'listreg RBYT'            # → address 0x40a00034, COUNT<47:0>

# Counter collection control
bcmcmd 'counter sync'            # One-time sync before reading
bcmcmd 'counter interval=100000' # Set 100ms poll interval (microseconds)
bcmcmd 'counter off'             # Stop collection

# Clear counters
bcmcmd 'clear counters'          # Zero all software-accumulated counters
```

---

## 8. References

- [PORT_BRINGUP_REGISTER_MAP.md](PORT_BRINGUP_REGISTER_MAP.md) — XLPORT block addresses, port-to-block mapping
- [WRITE_MECHANISM_ANALYSIS.md](WRITE_MECHANISM_ANALYSIS.md) — S-Channel DMA register read/write
- [SCHAN_FORMAT_ANALYSIS.md](SCHAN_FORMAT_ANALYSIS.md) — S-Channel command word format

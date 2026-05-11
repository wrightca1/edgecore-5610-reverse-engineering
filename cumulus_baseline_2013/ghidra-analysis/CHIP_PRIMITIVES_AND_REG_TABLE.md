# Chip-Register Primitives + Full BCM Register Name Table

Deep-trace of switchd revealed the BCM SDK's lowest-level chip-access
primitives AND a **36,896-entry register name database** — Broadcom's
complete Trident+ register namespace.

## The chip-access primitive functions

From DeepBcmTrace.java (BFS depth 5 from labeled BCM APIs), the
functions with the most chip-keyword string references:

| Address | Identified as | Source file (from strings) |
|---|---|---|
| `FUN_103230a4` | **`linux_user_bde_setup`** / chip-attach main | `bcm-sdk/systems/bde/linux/user/linux-user-bde.c` |
| `FUN_108623e4` | **SCHAN operation** (`CMIC_SCHAN_WORDS` checks) | bcm-sdk/.../schan.c |
| `FUN_10803190` | **`soc_mem_*` access** | bcm-sdk/.../mem.c |
| `FUN_10820164` | **`soc_mem_entries`** (memory table walk) | bcm-sdk/.../mem.c |
| `FUN_1080c940` | **`soc_mem_generic_lookup`** | bcm-sdk/.../mem.c |
| `FUN_10844e8c` | **`soc_reg_log`** (register I/O logger) | bcm-sdk/src/soc/common/reg.c |
| `FUN_10847ab4` | **`soc_reg32_get`** (32-bit reg read) | bcm-sdk/src/soc/common/reg.c:0x4a4 |
| `FUN_10848708` | **`soc_reg64_write_iterative`** (PLL writes with retry) | bcm-sdk/.../reg.c |
| `FUN_1083bfbc` | **`soc_phyctrl_redirect_loopback_set`** | bcm-sdk/.../phyctrl.c |
| `FUN_105c0200` | **`soc_phyctrl_linkup_evt` / `linkdn_evt`** handler | bcm-sdk/.../phyctrl.c |
| `FUN_107a213c` | **`_soc_field_value_fit`** (TCAM field encoder) | bcm-sdk/.../field.c |
| `FUN_108158a4` | `soc_mem_*` (sorted/hashed/cam variants) | bcm-sdk/.../mem.c |

## Decoded BDE init (FUN_103230a4)

```c
int bde_init(void) {
    if (g_bde_fd < 0) {
        g_bde_fd = open("/dev/linux-user-bde", O_RDWR);
        if (g_bde_fd < 0) {
            // Kernel modules not loaded — try insmod
            if (kernel_is_2_4()) {
                system("/sbin/insmod linux-kernel-bde.o");
                system("/sbin/insmod linux-user-bde.o");
            } else {
                system("/sbin/insmod linux-kernel-bde.ko");
                system("/sbin/insmod linux-user-bde.ko");
            }
            g_bde_fd = open("/dev/linux-user-bde", O_RDWR);
            if (g_bde_fd < 0) { perror("..."); return -1; }
        }
        g_mem_fd  = open("/dev/mem", O_RDWR);              // for PCI BAR mmap
        g_kbde_fd = open("/dev/linux-kernel-bde", O_RDWR);  // kernel BDE
        
        // Probe device count
        ioctl(g_bde_fd, LUBDE_GET_NUM_DEVICES /*=0x20004c01*/, &devio);
        if (devio.dev_count == 0) puts("linux-user-bde: no devices");
        // ... per-device attach
    }
}
```

**Source path proven from assert string:**
```
/work/monster-03/build.slave/workspace/CumulusLinux-2.5_br_BUILD_powerpc/
  build/powerpc/bcm-sdk/systems/bde/linux/user/linux-user-bde.c
```

EdgeNOS already implements this path (custom BDE). The IOCTL number
`0x20004c01` = `_IOR('L', 0x01, sizeof(int))` is `LUBDE_GET_NUM_DEVICES`.

## Decoded `soc_reg32_get` (FUN_10847ab4)

```c
int soc_reg32_get(int unit, int reg, /*?*/, /*?*/, uint32_t *out) {
    if (reg < 0 || reg > 0x901f ||
        g_unit[unit].reg_info[reg].entry == NULL) {
        return BCM_E_INTERNAL;  // -4
    }
    if ((g_unit[unit].reg_info[reg].flags & 0x100001) != 0) {
        // bit 0x100001 = "register is wider than 32 bits"
        log("reg %s is > 32 bit, but called with soc_reg32_get\n",
            REG_NAME_TABLE[reg]);
        assert("!SOC_REG_IS_ABOVE_32(unit, reg)",
               "bcm-sdk/src/soc/common/reg.c", 0x4a4);
    }
    // ... actual register read via schan_op
}
```

**Constants for EdgeNOS:**
* `reg < 0x901f` (= 36895) is the max BCM register ID
* `flags & 0x100001` = "register wider than 32 bits" bit
* Per-unit struct has `reg_info[]` array at offset `+ 0x18` from
  `g_unit[unit].pointer_at_+0x2f26f4`

## Full BCM register name database

Extracted **36,896 register names** from the pointer table at
`0x11bcac14` in switchd. Pointer table = array of `const char *` strings,
indexed by register ID.

Saved in: `bcm_register_names.txt`

### Distribution by subsystem

| Prefix / region | Count | What it controls |
|---|---|---|
| CMIC | 3,470 | Chip Management Interface Controller (CMICm + CMICD variants) |
| ING_ | 813 | Ingress pipeline blocks |
| MMU | 639 | Memory Management Unit (packet buffers, queues) |
| EGR_ | 612 | Egress pipeline blocks |
| FP_ | 321 | Field Processor (TCAM/ACL) |
| L2_ | 288 | L2 forwarding tables |
| L3_ | 251 | L3 routing / host / DEFIP |
| MIIM | 144 | MDIO bus access (4 CMC banks × ~36 regs each) |
| XLPORT | 82 | XLPORT (40G port) registers |
| WC / WARPCORE | 26 | Warpcore SerDes core regs (PLL etc.) |

### Critical found registers (selected)

**CMIC MIIM (the actual addresses we wrote in our debug scripts!):**
```
0x0c85   CMIC_CMC0_MIIM_ADDRESS
0x0c86   CMIC_CMC0_MIIM_CTRL
0x0c87   CMIC_CMC0_MIIM_PARAM
0x0c88   CMIC_CMC0_MIIM_READ_DATA
0x0c89   CMIC_CMC0_MIIM_STAT
0x0d91   CMIC_CMC1_MIIM_ADDRESS    (CMC1 bank, used for some ports)
...
```

**CMIC SCHAN (the "S-channel" used for all chip table access):**
```
0x0c75   CMIC_CMC0_FSCHAN_ADDRESS   (Fast SCHAN address)
0x0c76   CMIC_CMC0_FSCHAN_DATA32
0x0c77   CMIC_CMC0_FSCHAN_DATA64_HI
0x0c78   CMIC_CMC0_FSCHAN_DATA64_LO
0x0c7a   CMIC_CMC0_FSCHAN_OPCODE
0x0c7b   CMIC_CMC0_FSCHAN_STATUS
0x0ce0   CMIC_CMC0_SCHAN_ACK_DATA_BEAT_COUNT
0x0ce1   CMIC_CMC0_SCHAN_CTRL
0x0ce2   CMIC_CMC0_SCHAN_ERR
```

**Warpcore PLL controls (for SerDes init):**
```
0x1d95   CX_WC_PLL_CHANNEL_0
0x1d96   CX_WC_PLL_CHANNEL_1
0x1d97   CX_WC_PLL_CHANNEL_2
0x1d98   CX_WC_PLL_CHANNEL_3
0x1d99   CX_WC_PLL_CHANNEL_4
0x1d9a   CX_WC_PLL_CHANNEL_5
0x1d9b   CX_WC_PLL_CONTROL
0x1d9c   CX_WC_PLL_GAIN
0x1d9d   CX_WC_PLL_NDIV_FRACTION
0x1d9e   CX_WC_PLL_NDIV_INTEGER
0x1d9f   CX_WC_PLL_PREDIV
0x1da0   CX_WC_PLL_RESET
0x1da1   CX_WC_PLL_SSC_CTRL
0x1da2   CX_WC_PLL_SSC_LIMIT
0x1da3   CX_WC_PLL_STATUS
```

This is the complete set for setting up the Warpcore SerDes clock —
N-divider integer + fractional parts, pre-divider, spread-spectrum
control, reset, status. EdgeNOS needs these for any non-default port
speed.

**MY_STATION CAM (the L2→L3 punt table we identified earlier):**
```
0x63c4   MY_STATION_CAM_BIST_CONFIG
0x63c5   MY_STATION_CAM_BIST_CONTROL
0x63c6   MY_STATION_CAM_BIST_DBG_DATA
0x63c7   MY_STATION_CAM_BIST_STATUS
0x63c8   MY_STATION_CAM_DBGCTRL
...
```

**L3 DEFIP (longest-prefix-match route table):**
```
0x5ac5   L3_DEFIP_128_CAM_BIST_CONFIG   ← 128-bit (IPv6) DEFIP variant
0x5ac6   L3_DEFIP_128_CAM_BIST_CONTROL
...
```

## How EdgeNOS uses this

1. **Lookup by name** — pick any BCM register name from
   `bcm_register_names.txt` and locate it in OpenMDK headers.
2. **Implement `soc_reg32_get`/`set` equivalents** — EdgeNOS already has
   these via OpenMDK's `cdk_xgs_reg_get/set`. The register IDs we have
   here map 1:1 to the OpenMDK register defines (the BCM SDK is the
   source of OpenMDK's autogenerated header tables).
3. **Identify which subsystem a chip event came from** — error log
   messages reference register IDs; with the name table, EdgeNOS logs
   can decode them.

## Files

* `bcm_register_names.txt` (~1.4 MB) — full 36,896-entry register name table
* `switchd_deep_trace.txt` — primitive function candidates ranked
* `switchd_chip_primitives_decomp.c` — top 40 candidate decompilations
* `scripts/DeepBcmTrace.java` — call-graph depth-5 walker
* `scripts/ExtractRegNames.java` — pointer-table walker for name extraction

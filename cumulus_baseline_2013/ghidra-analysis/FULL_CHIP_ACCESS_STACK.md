# Complete Chip Access Stack — switchd → CMIC

By following the BCM SDK call graph all the way down, we now have the
**complete chip-access stack** from BCM API → SCHAN → register write.

```
┌─────────────────────────────────────────────────────────────────────┐
│  BCM API:  bcm_port_speed_get(unit, port, *speed)                   │
│            (~128 such APIs labeled in switchd, all follow same     │
│             trampoline pattern: lock-validate-work-unlock-trace)    │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────────┐
│  port_validate (FUN_105a6a18, ~284 bytes)                           │
│  - Validate logical port 0..0x81                                    │
│  - Decode encoded port (bits 26+ = port type)                       │
│  - Return BCM_E_INIT (-0x11) or BCM_E_PARAM (-0x12)                 │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────────┐
│  soc_reg32_get (FUN_10847ab4, 544 bytes)                            │
│  bcm-sdk/src/soc/common/reg.c : 0x4a4                               │
│  - Validate reg ID < 0x901f                                         │
│  - Check if reg > 32 bit (flag 0x100001), assert if so              │
│  - Dispatch on chip class                                           │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼ (Trident+ class)
┌─────────────────────────────────────────────────────────────────────┐
│  soc_reg_read_schan (FUN_10847350, 1892 bytes)                      │
│  - Build SCHAN command word:                                        │
│      bits 20-23: register block (from reg_id >> 0x14)               │
│      bits 14-19: block-port encoding                                │
│      bits 0-13:  fixed opcode 0x2c000200                            │
│  - Call soc_schan_op(unit, cmd_buf, 2 write_words, 2 read_words, 0) │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────────┐
│  soc_schan_op (FUN_108623e4, 8176 bytes)                            │
│  bcm-sdk/src/soc/common/schan.c : 0x17f                             │
│  - assert(!sal_int_context())  - can't SCHAN from interrupt         │
│  - Max words = 0x14 (20) or 0x16 (22) based on chip flags           │
│  - Big switch on cmd[0] >> 0x1a (top 6 bits = opcode type)          │
│    cases: 0x7, 0x9, 0xb, 0xd, 0xf, 0x11, 0x15, 0x19, 0x1e, ...      │
│  - Each opcode case constructs the final SCHAN word                 │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────────┐
│  Raw register read (FUN_108508ac, 8596 bytes!)                      │
│  bcm-sdk/src/soc/common/reg.c : 0xd3d                               │
│  - Validate reg_id, extract size class from flags bits 17-19        │
│  - This is where the actual CMIC FIFO write/read happens            │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────────────┐
│  linux_user_bde_ioctl (FUN_10322de8, 140 bytes)                     │
│  bcm-sdk/systems/bde/linux/user/linux-user-bde.c : 0x1f7             │
│                                                                      │
│  int linux_user_bde_ioctl(ulong command, devio_t *pdevio) {         │
│      pdevio->status = -1;                                            │
│      int rc = ioctl(g_bde_fd, command, pdevio);                      │
│      if (rc != 0) assert(...);                                       │
│      return pdevio->status;                                          │
│  }                                                                   │
└─────────────────────────┬───────────────────────────────────────────┘
                          │
                          ▼ ioctl() → kernel BDE → CMIC MMIO
                          │
┌─────────────────────────────────────────────────────────────────────┐
│  linux-kernel-bde.ko / linux-user-bde.ko                            │
│  - Handles the actual hardware access                               │
│  - Maps PCI BAR0 via /dev/mem to user space                         │
│  - Provides /dev/linux-user-bde + /dev/linux-kernel-bde chardevs    │
└─────────────────────────────────────────────────────────────────────┘
```

## Key constants extracted

| Name | Value | Meaning |
|---|---|---|
| `LUBDE_GET_NUM_DEVICES` | `0x20004c01` | BDE ioctl to count devices |
| Max reg ID | `0x901f` (36895) | BCM register namespace max |
| Reg size flag bit | `0x100001` | "Register is > 32 bits" |
| Chip class flag bit | `0x2000000` | Trident+ vs non-Trident path |
| SCHAN opcode (read) | `0x2c000200` | Standard register-read opcode |
| Max SCHAN write words | `0x14` or `0x16` | (20-22 words depending on chip flags) |
| Reg size class bits | flags `[17:19]` | 3-bit register-size encoding |
| BCM_E_INIT | `-0x11` (-17) | Standard error |
| BCM_E_PARAM | `-0x12` (-18) | Standard error |
| `BCM_E_NOT_FOUND` | `-7` | Standard error |
| `BCM_E_INTERNAL` | `-4` | Internal error |

## TUN device creation (bonus find)

While looking at ioctl callers, found `FUN_10008ae8` at 0x10008ae8 —
the **TUN device creator** for swp* interfaces:

```c
int create_tun_device(char *name, void *mac) {
    int fd = open64("/dev/net/tun", O_RDWR);
    struct ifreq ifr = { .ifr_flags = IFF_TUN | IFF_NO_PI };  // 0x300e
    strncpy(ifr.ifr_name, name, IFNAMSIZ);
    if (ioctl(fd, TUNSETIFF /* 0x800454ca */, &ifr) < 0) {
        log_crit("TUNSETIFF failed");
        close(fd); return -1;
    }
    if (mac != NULL && memcmp(mac, &zero_mac, 6) != 0) {
        ifr.ifr_hwaddr = *mac;
        ioctl(fd, SIOCSIFHWADDR /* 0x8927 */, &ifr);
    }
    return fd;
}
```

Source path: `tuntap.c:0x22, 0x3e`. Each of the 52 swp* interfaces in
switchd is created via this function. Confirms our earlier RX path
analysis: 52 TUN fds, one per port.

## Source-file locations now confirmed (via leaked assert paths)

```
bcm-sdk/systems/bde/linux/user/linux-user-bde.c   - BDE user interface
bcm-sdk/src/soc/common/reg.c                       - register access (reg32_get, reg_read)
bcm-sdk/src/soc/common/schan.c                     - SCHAN protocol
bcm-sdk/src/soc/common/mem.c                       - memory table access
bcm-sdk/src/soc/common/field.c                     - FP/TCAM
bcm-sdk/src/soc/common/phyctrl.c                   - PHY control
bcm-sdk/src/sal/core/unix/sync.c                   - SAL mutex
tuntap.c                                            - Cumulus glue (TUN device creation)
```

These are all part of the BCM SDK source tree at Cumulus. The BCM SDK
itself is not publicly available, but **OpenMDK contains equivalent
implementations** of all the SAL, SOC common, and BDE primitives.

## What EdgeNOS needs to do

EdgeNOS already implements equivalents of each layer (via OpenMDK):

| switchd primitive | OpenMDK / EdgeNOS equivalent |
|---|---|
| `linux_user_bde_setup` | `bde_init()` (custom BDE) |
| `linux_user_bde_ioctl` | `cdk_xgs_bde_ioctl()` |
| `soc_reg32_get` | `cdk_xgs_reg_get()` |
| `soc_reg_read_schan` | `cdk_xgs_schan_read()` |
| `soc_schan_op` | `cdk_xgs_schan_op()` |
| Raw CMIC MMIO read | `cdk_xgs_mmio_read32()` |

The differences for EdgeNOS to handle:
1. The 0x901f register count = OpenMDK's `XGS_REG_COUNT_MAX`. Must match.
2. The chip-class flag `0x2000000` distinguishes Trident+ from older
   chips. EdgeNOS must set this for BCM56846.
3. SCHAN opcode encoding (`0x2c000200` for reads, plus the bit
   layout in cmd[0]) matches OpenMDK's `XGS_SCHAN_OP_READ`.
4. Per-unit struct layout: `g_unit[unit]` points to a struct at offset
   `+0x2f26f4` for reg_info, `+0x2f2c24` for class flags, `+0x1c84` for
   port table. EdgeNOS's unit struct must mirror.

## Files

* `switchd_deepest_primitives.c` (67 KB) — 10 deepest functions decompiled
* `switchd_register_primitives_deep.c` (36 KB) — 5 more deep primitives
* `switchd_ioctl_wrappers_full.c` (12 KB) — all 7 BDE ioctl wrappers
* `switchd_ioctl_callers.txt` — list of ioctl callers
* `scripts/DeepestPrimitives.java`
* `scripts/FollowRegistersAndIoctl.java`

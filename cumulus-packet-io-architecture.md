# Cumulus Packet I/O Architecture (No KNET)

**Critical Finding**: Cumulus Linux does **NOT** use KNET driver. This is a fundamental architectural difference from OpenNSL.

## Cumulus Architecture (Actual)

### Modules Loaded
```
linux-kernel-bde.ko    - BDE kernel driver (PCI/DMA)
linux-user-bde.ko      - BDE user-space helper
linux-bde-tmon.ko      - Thermal monitoring
```

**NOT loaded**: `linux-bcm-knet.ko` (KNET driver)

### Device Nodes
```
/dev/linux-user-bde    - BDE user-space device
/dev/linux-kernel-bde  - BDE kernel device (proc)
```

**NOT present**: `/dev/linux-bcm-knet` (KNET device)

## How Cumulus Creates swp Interfaces

Cumulus creates swp1-52 interfaces through the **Broadcom SDK directly**, not through KNET.

### Interface Creation Flow

1. **switchd starts** and initializes SDK
2. **SDK creates interfaces** via internal mechanism (not KNET)
3. **Linux kernel** sees interfaces appear (via netlink or direct kernel API)
4. **swp interfaces** become available for IP configuration

### Evidence from switchd Log

```
hal_bcm_port.c:56 porttab entry, linux:swp1 sdk:xe0
hal_bcm_port.c:56 porttab entry, linux:swp2 sdk:xe1
...
```

This shows switchd maps Linux swpX to SDK xeX ports, but the interfaces are created by the SDK itself, not KNET.

## Packet I/O Without KNET

### Control Plane Packets

**How packets flow WITHOUT KNET:**

1. **Application** (ospfd) sends packet via socket
2. **Linux kernel** routes to swp1 interface
3. **swp1 netdev** → **SDK packet API** (via BDE)
4. **BDE DMA** → **ASIC TX**
5. **ASIC** transmits packet

**Key difference**: No KNET driver intercepting. The SDK handles packet I/O directly through BDE.

### Data Plane Packets

**Same as before** - pure hardware forwarding, no CPU involvement.

## SDK Packet APIs (Not KNET)

Cumulus SDK likely uses:
- `bcm_rx_*` APIs for packet receive
- `bcm_tx_*` APIs for packet transmit
- Direct DMA through BDE
- No `/proc/linux-uk-proxy` or KNET device

## Implications for Open-Source Implementation

### Cannot Use OpenNSL KNET

OpenNSL's `opennsl_knet_netif_create()` won't work because:
- It requires `linux-bcm-knet.ko` module
- Cumulus doesn't use this module
- We need to match Cumulus architecture

### Must Use SDK Direct Packet I/O

Our implementation needs to:
1. **Create swp interfaces** via SDK (not KNET)
2. **Handle packet I/O** through BDE/SDK APIs
3. **Map swpX** to BCM ports via portmap
4. **No KNET dependency**

## References

- [CUMULUS_REVERSE_ENGINEERING_FINDINGS.md](../../CUMULUS_REVERSE_ENGINEERING_FINDINGS.md) - "Cumulus does NOT load a KNET module"
- [AS5610_STRATEGY_PLAN.md](../../open-nos-build/AS5610_STRATEGY_PLAN.md) - "They use an in-kernel packet I/O path"

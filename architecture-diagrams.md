# Cumulus switchd Architecture Diagrams

**Date**: 2026-02-15

## 1. Component Interaction

```mermaid
flowchart TB
    subgraph userspace [User Space]
        ip[ip route/link]
        quagga[Quagga/FRR]
    end

    subgraph kernel [Linux Kernel]
        fib[FIB/RIB]
        bridge[Bridge FDB]
        netlink[Netlink]
    end

    subgraph switchd_component [switchd]
        nl_handler[Netlink Handler]
        hal[HAL Layer]
        sdk_glue[SDK Glue]
    end

    subgraph bcm_sdk [Broadcom SDK 6.3.8]
        bcm_api[bcm_* API]
    end

    subgraph bde [BDE Drivers]
        kernel_bde[kernel-bde.ko]
        user_bde[user-bde.ko]
    end

    subgraph asic [BCM56846 ASIC]
        l2[L2 Table]
        l3[L3 FIB]
        ports[Ports]
    end

    ip --> netlink
    quagga --> netlink
    netlink --> nl_handler
    nl_handler --> hal
    hal --> sdk_glue
    sdk_glue --> bcm_api
    bcm_api --> user_bde
    user_bde --> kernel_bde
    kernel_bde --> asic
```

## 2. Data Flow: Route Addition

```mermaid
sequenceDiagram
    participant User
    participant Kernel
    participant switchd
    participant SDK
    participant BDE
    participant ASIC

    User->>Kernel: ip route add 10.1.1.0/24 via 10.0.0.1 dev swp1
    Kernel->>Kernel: Update FIB
    Kernel->>switchd: RTM_NEWROUTE (netlink)
    switchd->>switchd: Parse: dst=10.1.1.0/24, gw=10.0.0.1, oif=swp1
    switchd->>switchd: portmap: swp1 -> BCM port 1
    switchd->>switchd: Get gateway MAC from neighbor table
    switchd->>SDK: bcm_l3_egress_create(port=1, mac=...)
    SDK->>BDE: ioctl/mmap
    BDE->>ASIC: PCI write
    switchd->>SDK: bcm_l3_route_add(subnet, mask, egress_id)
    SDK->>BDE: ioctl/mmap
    BDE->>ASIC: PCI write to L3_DEFIP table
```

## 3. Initialization Sequence

```mermaid
flowchart TD
    A[Start switchd] --> B[License check]
    B --> C[Load config /etc/bcm.d]
    C --> D[Open /dev/linux-user-bde]
    D --> E[bcm_attach]
    E --> F[bcm_init]
    F --> G[Execute rc.soc]
    G --> H[rcload rc.ports_0]
    H --> I[rcload rc.led]
    I --> J[rcload rc.datapath_0]
    J --> K[Create netlink socket]
    K --> L[Bind RTMGRP_LINK, ROUTE, NEIGH]
    L --> M[Create /var/run/switchd.ready]
    M --> N[Main loop: recv netlink]
```

## 4. Netlink Handler Dispatch

```mermaid
flowchart LR
    NL[Netlink recv] --> D{Message type}
    D -->|RTM_NEWLINK| L1[handle_link]
    D -->|RTM_DELLINK| L1
    D -->|RTM_NEWROUTE| R1[handle_route]
    D -->|RTM_DELROUTE| R1
    D -->|RTM_NEWNEIGH| N1[handle_neighbor]
    D -->|RTM_DELNEIGH| N1

    L1 --> B1[bcm_port_enable_set]
    R1 --> B2[bcm_l3_route_add/del]
    N1 --> B3[bcm_l2_addr_add/del]
```

## 5. Config File Flow

```mermaid
flowchart TD
    subgraph chip [Chip Defaults]
        T[sdk.bcm Trident]
    end

    subgraph platform [Platform]
        P[01config.bcm]
        R[rc.soc]
    end

    subgraph runtime [Runtime]
        DP[rc.datapath_0]
    end

    T --> merge[Merge]
    P --> merge
    merge --> loaded[Loaded config]
    R --> exec[rc.soc execution]
    loaded --> exec
    exec --> H[rcload rc.ports_0]
    exec --> I[rcload rc.led]
    exec --> J[rcload rc.datapath_0]
    switchd[switchd] --> DP
```

## References

- [initialization-sequence.md](initialization-sequence.md)
- [netlink-handlers.md](netlink-handlers.md)
- [BROADCOM_CUMULUS_ARCHITECTURE.md](../../BROADCOM_CUMULUS_ARCHITECTURE.md)

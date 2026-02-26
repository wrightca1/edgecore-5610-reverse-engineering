# Versions and Build Information

**Date**: February 15, 2026  
**Purpose**: Document all software versions, libraries, and build toolchains for Cumulus switch, extracted sysroot, and ONL/open-nos builds.

---

## Summary

| Component | Cumulus (live <LIVE_SWITCH_IP>) | ONL / open-nos build |
|-----------|---------------------------|----------------------|
| **OS** | Cumulus Linux 2.5.1, Debian 7.8 (Wheezy) | Debian 8 (Jessie) base, ONL |
| **Kernel** | 3.2.60-1+deb7u1+cl2.5+1 | 3.16.64 (ONL default) |
| **Architecture** | PowerPC 32-bit | PowerPC |
| **SDK** | Broadcom SDK 6.3.8 (proprietary, statically linked) | OpenNSL 3.5.0.1 (GPL, libopennsl.so) |
| **BDE** | linux-kernel-bde, linux-user-bde (6.3.8-cl2.5+1) | OpenNSL sdk-6.5.12-gpl-modules |
| **Build host** | — | Debian 8 (Jessie) @ <BUILD_SERVER_IP> |

---

## 1. Cumulus Switch (Live <LIVE_SWITCH_IP>)

### 1.1 OS and Kernel

| Item | Version |
|------|---------|
| **OS** | Cumulus Linux |
| **VERSION_ID** | 2.5.1 |
| **Full version** | 2.5.1-5227ded-201503051128-build |
| **Debian base** | 7.8 (Wheezy) |
| **Kernel** | 3.2.60-1+deb7u1+cl2.5+1 |
| **Kernel build** | Thu Mar 5 11:36:33 PST 2015 |
| **Architecture** | ppc (PowerPC) |
| **CPE** | cpe:/o:cumulusnetworks:cumulus_linux:2.5.1-5227ded-201503051128-build |

### 1.2 Key Packages

| Package | Version |
|---------|---------|
| **switchd** | 1.0-cl2.5+1 |
| **bcm-modules** | 6.3.8-cl2.5+1 |
| **bcm-utils** | 6.3.8-cl2.5+1 |
| **ethtool** | 1:3.4.2-1+cl2.2 |
| **iproute** | 20120521-3+cl2.5+1 |
| **quagga** | 0.99.23.1-1+cl2.5+3 |
| **python-ifupdown2** | 0.1-cl2.5+1 |
| **linux-image** | 3.2.60-1+deb7u1+cl2.5+1 |
| **linux-image-powerpc** | 3.2.60-1+deb7u1+cl2.5+1 |

### 1.3 Libraries (switchd and runtime)

| Library | Version |
|---------|---------|
| **glibc (libc6)** | 2.13-38+deb7u8 (EGLIBC 2.13) |
| **libnl-3-200** | 3.2.7-4+cl2.5+1 |
| **libnl-genl-3-200** | 3.2.7-4+cl2.5+1 |
| **libnl-route-3-200** | 3.2.7-4+cl2.5+1 |
| **libnet1** | 1.1.4-2.1 |
| **libfuse2** | 2.9.0-2+deb7u1 |
| **libgcc1** | 1:4.7.2-5 |
| **libstdc++6** | 4.7.2-5 |
| **libpthread** | (part of glibc) |
| **libm** | (part of glibc) |
| **librt** | (part of glibc) |
| **libdl** | (part of glibc) |

### 1.4 Python

| Item | Version |
|------|---------|
| **python** | 2.7.3-4+deb7u1 |
| **python2.7** | 2.7.3-6+deb7u2 |
| **python2.6** | 2.6.8-1.1 |
| **libpython2.7** | 2.7.3-6+deb7u2 |

### 1.5 Kernel Modules (BDE)

| Module | Source | Notes |
|--------|--------|-------|
| **linux-kernel-bde.ko** | bcm-modules 6.3.8-cl2.5+1 | Built for kernel 3.2.60-1+deb7u1+cl2.5+1 |
| **linux-user-bde.ko** | bcm-modules 6.3.8-cl2.5+1 | Same kernel version |
| **linux_bde_tmon** | platform-modules | Temperature monitoring |

### 1.6 switchd Dependencies (from control)

```
Depends: libc6 (>= 2.6), libfuse2 (>= 2.8.1), libnet1 (>= 1.1.2.1),
         libnl-3-200 (>= 3.2.7), libnl-genl-3-200 (>= 3.2.7),
         libnl-route-3-200, cl-utilities, bcm-utils
```

### 1.7 Compiler / Toolchain (runtime)

- **gcc** – not installed on switch (typical for embedded)
- **libgcc1** – 1:4.7.2-5 (GCC 4.7.2 support library)
- **gcc-4.6-base** – 4.6.3-14 (optional)
- **gcc-4.7-base** – 4.7.2-5

---

## 2. Cumulus Extracted Sysroot (PowerPC)

**Source**: CumulusLinux-2.5.1-powerpc.bin (extracted SquashFS)

| Item | Version |
|------|---------|
| **Debian** | 7.8 (`/etc/debian_version`) |
| **Quagga** | 0.99.23.1 (from `usr/include/quagga/version.h`) |
| **Packages** | Same as live switch (bcm-modules 6.3.8-cl2.5+1, switchd 1.0-cl2.5+1, etc.) |

---

## 3. ONL / open-nos Build

### 3.1 OpenNSL

| Item | Version |
|------|---------|
| **OpenNSL** | 3.5.0.1 |
| **Archive** | OpenNSL-3.5.0.1.tar.gz |
| **GPL BDE source** | sdk-6.5.12-gpl-modules (inside OpenNSL archive) |

### 3.2 Build Environment

| Item | Value |
|------|-------|
| **Build host** | <USER>@<BUILD_SERVER_IP> |
| **Build host OS** | Debian 8 (Jessie) |
| **Target architecture** | powerpc |
| **Target platform** | powerpc-accton-as5610-52x-r0 |
| **Kernel version** | 3.16.64 (ONL default) |

### 3.3 Built Artifacts

| Artifact | Built for |
|----------|-----------|
| **linux-kernel-bde.ko** | Kernel 3.16.64 PowerPC |
| **linux-user-bde.ko** | Kernel 3.16.64 PowerPC |
| **linux-bcm-knet.ko** | Kernel 3.16.64 PowerPC |
| **libopennsl.so.1** | PowerPC (from OpenNSL binaries) |

### 3.4 Cumulus vs OpenNSL

| Aspect | Cumulus | ONL / open-nos |
|--------|---------|----------------|
| **SDK** | Broadcom SDK 6.3.8 (proprietary) | OpenNSL 3.5.0.1 (GPL) |
| **Linkage** | Statically linked in switchd | Dynamic libopennsl.so |
| **Kernel** | 3.2.60 | 3.16.64 |
| **KNET** | Not used (TUN + BDE) | bcm-knet.ko used |
| **BDE source** | Proprietary | sdk-6.5.12-gpl-modules |

---

## 4. Library Versions Used at Compile Time

### 4.1 Cumulus switchd (inferred from runtime)

switchd is statically linked with Broadcom SDK 6.3.8. It was built against:

- **glibc** – 2.13 or compatible
- **libnl** – 3.2.7+
- **libnet** – 1.1.2.1+
- **libfuse** – 2.8.1+
- **GCC** – 4.6 or 4.7 (from libgcc1 4.7.2)

### 4.2 OpenNSL BDE modules (ONL build)

- **Kernel headers** – 3.16.64 (ONL)
- **GCC** – Debian 8 default (typically gcc 4.9)
- **Source** – sdk-6.5.12-gpl-modules

---

## 5. References

- **VERSION_COMPARISON.md** – Cumulus 2.5.1 amd64 vs powerpc
- **DEPLOYMENT_GUIDE.md** – ONL build and kernel 3.16.64
- **BUILD_SERVERS.md** – Build host configuration
- **integrate-opennsl-3.5-onl.sh** – OpenNSL 3.5.0.1 integration
- **build-config.sh** – OPENNSL_VERSION=3.5.0.1

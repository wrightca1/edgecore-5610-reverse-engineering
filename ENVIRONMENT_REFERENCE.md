# Environment Reference — Path B Reverse Engineering

**Purpose**: Single reference for the three systems used in Path B work. Use this when running scripts or tracing.

---

## 1. Live switch (Cumulus)

| Property | Value |
|----------|-------|
| **Host** | `<SWITCH_USER>@<LIVE_SWITCH_IP>` |
| **Role** | Production Cumulus switch; runs switchd, has TUN devices, BDE, `/dev/mem` |
| **OS** | Cumulus Linux (Debian-based) |
| **Key paths** | `/home/cumulus/` (trace scripts, logs) |
| **Use for** | Strace traces (packet I/O, port up/down), `bcmcmd`, live behavior |

**Scripts that SSH here:**
- `run-port-up-trace-<LIVE_SWITCH_IP>.sh` — strace during `ip link set swp1 down/up`
- `run-bde-mmap-trace-<LIVE_SWITCH_IP>.sh` — mmap/ioctl at startup
- `trace-packet-io-on-switch.sh` (via `run-*-trace-*.sh`) — packet I/O strace

---

## 2. Debian build servers

| Property | Value |
|----------|-------|
| **Host(s)** | Build server(s) — check `build-config.sh` or scripts for `BUILD_HOST` |
| **Role** | Build ONL, run extraction, host binaries for analysis |
| **Use for** | Compilation, SDK extraction, hosting `libopennsl.so.1`, `switchd` for copy to Ghidra server |

**Note**: Some scripts copy from local `build-server/` or `.opennsl-extract/`; the build server may be the same machine or a remote one. Check `GHIDRA_HOST` vs build host in scripts.

---

## 3. Ghidra server (analysis host)

| Property | Value |
|----------|-------|
| **Host** | `<USER>@<GHIDRA_HOST_IP>` |
| **Role** | Runs Ghidra headless; analyzes libopennsl, switchd |
| **REMOTE_PROJECT** | `/home/<USER>/analysis` |
| **Ghidra install** | `/home/<USER>/analysis/ghidra_12.0.3_PUBLIC` |
| **JDK** | `$REMOTE_PROJECT/jdk` (or system) |
| **Key paths** | `$REMOTE_PROJECT/build-server/opennsl/` (libopennsl), `$REMOTE_PROJECT/build-server/switchd/` (switchd) |
| **Output** | `$REMOTE_PROJECT/build-server/<binary>/sdk-deep-extract/*.txt` |

**Scripts that SSH here:**
- `run-dump-func-on-build-server.sh`
- `run-schan-data-refs-on-build-server.sh`
- `run-l2-callers-on-build-server.sh`
- `run-find-packet-tx-path-on-build-server.sh`
- `run-l2-writes-on-build-server.sh`
- `run-schan-on-build-server.sh`

---

## Quick reference

| System | SSH target | Purpose |
|--------|------------|---------|
| **Live switch** | `<SWITCH_USER>@<LIVE_SWITCH_IP>` | Strace, live traces |
| **Ghidra server** | `<USER>@<GHIDRA_HOST_IP>` | Ghidra headless, analysis output |

---

## Environment variables (scripts)

- `GHIDRA_HOST` — default `<USER>@<GHIDRA_HOST_IP>`
- `REMOTE_PROJECT` — default `/home/<USER>/analysis`
- `SWITCH` — default `<SWITCH_USER>@<LIVE_SWITCH_IP>` (in port-up trace script)
- `SUDOPASS` / `SSHPASS` — for sudo on switch when needed

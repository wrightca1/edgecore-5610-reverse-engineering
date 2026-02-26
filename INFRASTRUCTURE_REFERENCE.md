# Infrastructure Reference (Path B)

**Use this doc as the canonical reference for hosts, paths, and workflows.** Scripts and commands assume these defaults.

---

## Hosts

| Host | IP | User | Role | OS |
|------|-----|------|------|-----|
| **Live switch (Cumulus)** | <LIVE_SWITCH_IP> | cumulus | Running Cumulus Linux, switchd, BDE. For strace, packet I/O traces, port-up traces. | Cumulus Linux |
| **Ghidra server** | <GHIDRA_HOST_IP> | <USER> | Ghidra 12, JDK 21, analyzeHeadless. Binaries and Ghidra projects live here. | Fedora (30GB RAM) |
| **Debian build server (modern)** | <BUILD_SERVER_IP> | <USER> | General builds | Debian |
| **Debian build server (Debian 8)** | <BUILD_SERVER_IP> | <USER> | Legacy/ONL builds | Debian 8 |
| **ONL switch** | <ONL_SWITCH_IP> | root | ONL / bare-metal switch (different from Cumulus) | ONL |

---

## Paths

### Ghidra server (<GHIDRA_HOST_IP>)

| Path | Purpose |
|------|---------|
| `/home/<USER>/analysis/` | Base dir (REMOTE_PROJECT) |
| `/home/<USER>/analysis/ghidra_12.0.3_PUBLIC/` | Ghidra install |
| `/home/<USER>/analysis/jdk` | Java (optional) |
| `/home/<USER>/analysis/build-server/` | Binaries + Ghidra projects |
| `/home/<USER>/analysis/build-server/opennsl/libopennsl.so.1` | libopennsl binary |
| `/home/<USER>/analysis/build-server/opennsl/ghidra-projects/` | libopennsl Ghidra project |
| `/home/<USER>/analysis/build-server/switchd/switchd` | switchd binary |
| `/home/<USER>/analysis/build-server/switchd/ghidra-projects/` | switchd Ghidra project |
| `/home/<USER>/analysis/build-server/scripts/reverse-engineering/` | Ghidra scripts (copied from local) |
| `/home/<USER>/analysis/build-server/*/sdk-deep-extract/` | Script outputs (dumps, xrefs, etc.) |

### Live switch (<LIVE_SWITCH_IP>)

**GDB**: Installed (7.4.1, powerpc). Use for API→table-ID breakpoint traces. Installed via manual .deb (Wheezy gdb+gdbserver) because switch has no outbound internet and Cumulus repo unreachable.

**Trace output**: Scripts write to **/run/shm** (981M tmpfs) or **/dev/shm** if writable, else `/home/cumulus`. Run scripts fetch from all three. Avoids filling `/tmp` (100M, often full) and root.

| Path | Purpose |
|------|---------|
| `/dev/shm/*.log`, `/run/shm/*.log`, `/home/cumulus/*.log` | Trace outputs (port-up, route-ecmp, ospf, api-to-table-id, etc.) |
| `/home/cumulus/trace-port-up-on-switch.sh` | Port-up trace script (when copied by run-port-up-trace) |

**Disk**: Root/home often has little space. Use `./run-switch-disk-cleanup-<LIVE_SWITCH_IP>.sh` to report usage; `--clean` to remove old trace files.

**Config scripts (piped via SSH, no SCP):**
- `configure-switch-101-ecmp.sh` + `configure-switch-101-ecmp-on-switch.sh` — swp1 10.101.101.1/29, swp2 10.101.101.10/29 (no bridge), ECMP via .2 (swp1) and .9 (swp2)
- `run-configure-ospf-101-<LIVE_SWITCH_IP>.sh` + `configure-ospf-101-on-switch.sh` — OSPF on swp1 and swp2 (10.101.101.0/29 and 10.101.101.8/29 area 0)

### Local (workspace)

| Path | Purpose |
|------|---------|
| `ONL/scripts/reverse-engineering/` | All run-* and trace scripts |
| `ONL/docs/reverse-engineering/traces/` | Traces pulled from switch |
| `ONL/build-server/opennsl/sdk-deep-extract/` | Copied Ghidra outputs (libopennsl) |
| `ONL/build-server/switchd/sdk-deep-extract/` | Copied Ghidra outputs (switchd) |

---

## Environment variables (override defaults)

| Variable | Default | Use |
|----------|---------|-----|
| `GHIDRA_HOST` | <USER>@<GHIDRA_HOST_IP> | Ghidra server |
| `REMOTE_PROJECT` | /home/<USER>/analysis | Base on Ghidra server |
| `SWITCH` | <SWITCH_USER>@<LIVE_SWITCH_IP> | Live Cumulus switch |
| `SSHPASS` | (unset) | Password for ssh/scp if key auth fails |
| `SUDOPASS` | $SSHPASS | Sudo password on switch for trace scripts |
| `_JAVA_OPTIONS` | -Xmx8G | For Ghidra headless |

---

## Workflow summary

1. **Traces on live switch**: Scripts SSH to `<SWITCH_USER>@<LIVE_SWITCH_IP>`, run strace/trace scripts, SCP results to `docs/reverse-engineering/traces/`.
2. **Ghidra on server**: Scripts SSH to `<USER>@<GHIDRA_HOST_IP>`, run analyzeHeadless with `-scriptPath` and `-postScript`. Outputs go to `build-server/*/sdk-deep-extract/`.
3. **Copy outputs locally**: `scp <USER>@<GHIDRA_HOST_IP>:/home/<USER>/analysis/build-server/.../sdk-deep-extract/FILE build-server/.../sdk-deep-extract/`

---

## Quick copy commands

```bash
# From Ghidra server, libopennsl outputs
scp <USER>@<GHIDRA_HOST_IP>:/home/<USER>/analysis/build-server/opennsl/sdk-deep-extract/*.txt build-server/opennsl/sdk-deep-extract/

# From Ghidra server, switchd outputs
scp <USER>@<GHIDRA_HOST_IP>:/home/<USER>/analysis/build-server/switchd/sdk-deep-extract/*.txt build-server/switchd/sdk-deep-extract/

# From live switch, traces
scp <SWITCH_USER>@<LIVE_SWITCH_IP>:/home/cumulus/port_up_switchd.log docs/reverse-engineering/traces/port-up-trace-<LIVE_SWITCH_IP>.log
```

---

## Script → host mapping

| Script | Runs on | Connects to |
|--------|---------|-------------|
| `run-dump-func-on-build-server.sh` | Local | Ghidra server (<GHIDRA_HOST_IP>) |
| `run-schan-data-refs-on-build-server.sh` | Local | Ghidra server |
| `run-l2-callers-on-build-server.sh` | Local | Ghidra server |
| `run-find-packet-tx-path-on-build-server.sh` | Local | Ghidra server |
| `run-port-up-trace-<LIVE_SWITCH_IP>.sh` | Local | Live switch (<LIVE_SWITCH_IP>) |
| `run-perf-port-up-<LIVE_SWITCH_IP>.sh` | Local | Live switch |
| `run-bar-diff-port-up-<LIVE_SWITCH_IP>.sh` | Local | Live switch (dumps /dev/mem before/after port up) |
| `run-packet-io-trace-<LIVE_SWITCH_IP>.sh` | Local | Live switch |
| `run-bde-mmap-trace-<LIVE_SWITCH_IP>.sh` | Local | Live switch |
| `trace-port-up-on-switch.sh` | **Runs on switch** (copied + executed via SSH) | — |
| `bar-diff-port-up-on-switch.sh` | **Runs on switch** (sudo; dump BAR, port down/up, dump again) | — |
| `ghidra-find-*.sh` | **Runs on Ghidra server** (invoked via SSH from run-* scripts) | — |

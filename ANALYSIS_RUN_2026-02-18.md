# Reverse Engineering Analysis Run — 2026-02-18

**Switch**: <SWITCH_USER>@<LIVE_SWITCH_IP> (AS5610-52X, Cumulus Linux 2.5.1)  
**Build servers**: <BUILD_SERVER_IP> (modern Debian), <BUILD_SERVER_IP> (Debian 8)  
**Ghidra host**: <USER>@<GHIDRA_HOST_IP> (Fedora 36)

## Summary of actions

### On switch (<LIVE_SWITCH_IP>)

1. **switchd trace** — Stopped switchd, ran `strace -f` on `switchd -d` for 30 seconds
   - Output: `docs/reverse-engineering/traces/switchd-init-2026-02-18.trace` (~27MB, 455k lines)
   - Summary: `docs/reverse-engineering/traces/switchd-init-2026-02-18.summary.txt`
   - BDE ioctl codes observed: 0x20004c05, 0x20004c01, 0x20004c0c, 0x20004c02, 0x20004c1a, 0x20004c0a, 0x20004c0b, 0x20004c09, 0x20004c06

2. **Netlink monitor** — Ran `ip monitor link` / `ip monitor route` for 15 seconds
   - Output: `docs/reverse-engineering/traces/netlink-monitor-2026-02-18.log`
   - No link/route changes captured during the interval

3. **Live switchd binary** — Copied `/usr/sbin/switchd` to `cumulus/extracted/switchd/switchd` (replaces extracted image copy)

4. **BCM config** — Archived live `/etc/bcm.d/` to `docs/reverse-engineering/traces/bcm-config-<LIVE_SWITCH_IP>.tar.gz`
   - Includes: config.bcm (6054 bytes), rc.soc, rc.ports_0, rc.led, rc.phy, config.d/*, datapath, led*.asm/hex

### On build server (<BUILD_SERVER_IP>)

1. **Copy SDK** — Copied switchd and scripts to `/home/<USER>/ONL-RE/build-server/`

2. **Deep string extraction** — Ran `deep-extract-strings.sh`
   - Output in `build-server/switchd/sdk-deep-extract/`:
     - strings-with-offsets.txt (12.6MB, 629k lines)
     - strings-register-table.txt, strings-table-mem.txt
     - strings-bcm-soc.txt (4009 lines)
     - hexdump-head.txt, hexdump-rodata-near-rcsoc.txt
     - objdump-entry.txt, objdump-reg-candidates.txt
     - readelf-sections.txt, readelf-segments.txt
     - REPORT.txt

### Ghidra (<GHIDRA_HOST_IP>)

- **Ghidra headless** — Not run due to project lock: `/home/<USER>/analysis/build-server/switchd/ghidra-projects/switchd`
- **To retry**: Close any Ghidra GUI or other headless process using that project, then:
  ```bash
  GHIDRA_HOST=<USER>@<GHIDRA_HOST_IP> REMOTE_PROJECT=/home/<USER>/analysis ./scripts/reverse-engineering/run-ghidra-on-build-server.sh
  ```

## Script changes

- `deep-extract-strings.sh`: Added fallback to `xxd` when `hexdump` is not installed (e.g. on build server <BUILD_SERVER_IP>)

## Artifacts

| Artifact | Location |
|----------|----------|
| switchd trace (raw) | docs/reverse-engineering/traces/switchd-init-2026-02-18.trace |
| trace summary | docs/reverse-engineering/traces/switchd-init-2026-02-18.summary.txt |
| netlink monitor log | docs/reverse-engineering/traces/netlink-monitor-2026-02-18.log |
| BCM config archive | docs/reverse-engineering/traces/bcm-config-<LIVE_SWITCH_IP>.tar.gz |
| live switchd binary | cumulus/extracted/switchd/switchd |
| deep-extract output | build-server/switchd/sdk-deep-extract/ |

## Commands used

```bash
# Copy scripts to switch
sshpass -p '<PASSWORD>' scp scripts/reverse-engineering/trace-switchd-init.sh scripts/reverse-engineering/monitor-netlink.sh <SWITCH_USER>@<LIVE_SWITCH_IP>:/tmp/

# Stop switchd and trace
sshpass -p '<PASSWORD>' ssh <SWITCH_USER>@<LIVE_SWITCH_IP> "echo '<PASSWORD>' | sudo -S /etc/init.d/switchd stop"
sshpass -p '<PASSWORD>' ssh <SWITCH_USER>@<LIVE_SWITCH_IP> 'cd /tmp && echo "<PASSWORD>" | sudo -S bash trace-switchd-init.sh /tmp/switchd-init.trace /tmp/switchd-init.summary'

# Restart switchd
sshpass -p '<PASSWORD>' ssh <SWITCH_USER>@<LIVE_SWITCH_IP> "echo '<PASSWORD>' | sudo -S /etc/init.d/switchd start"

# Copy trace and config from switch
sshpass -p '<PASSWORD>' scp <SWITCH_USER>@<LIVE_SWITCH_IP>:/tmp/switchd-init.trace docs/reverse-engineering/traces/
sshpass -p '<PASSWORD>' scp <SWITCH_USER>@<LIVE_SWITCH_IP>:/usr/sbin/switchd cumulus/extracted/switchd/switchd

# Build server deep extract
BUILD_SERVER=<USER>@<BUILD_SERVER_IP>:/home/<USER>/ONL-RE ./scripts/reverse-engineering/copy-sdk-to-build-server.sh
ssh <USER>@<BUILD_SERVER_IP> 'cd /home/<USER>/ONL-RE/build-server && bash scripts/deep-extract-strings.sh switchd/switchd'

# Sync back
rsync -avz <USER>@<BUILD_SERVER_IP>:/home/<USER>/ONL-RE/build-server/switchd/ build-server/switchd/
```

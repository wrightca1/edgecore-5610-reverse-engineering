# Publishing to GitHub and Redaction

**Purpose**: When you sync reverse-engineering docs to a public repo (e.g. [wrightca1/edgecore-5610-reverse-engineering](https://github.com/wrightca1/edgecore-5610-reverse-engineering)), use this guide to keep content up to date and **keep private information redacted**.

**Last updated**: 2026-02-26

---

## 1. What to update when syncing

Apply the same updates that were made in the main ONL repo so the published docs match:

- **Paths**: Published repo may use different paths; ensure any references to `docs/reverse-engineering/` or `open-nos-as5610/` are correct for the published layout (e.g. no `../edgecore-5610-re/`; use `docs/reverse-engineering/` or relative paths).
- **Status docs**: Sync [PATH_B_COMPLETION_STATUS.md](PATH_B_COMPLETION_STATUS.md), [PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md](PATH_B_WHATS_LEFT_AND_NEXT_STEPS.md), [PATH_B_INFORMATION_CHECKLIST.md](PATH_B_INFORMATION_CHECKLIST.md), [REVERSE_ENGINEERING_STATUS_REPORT.md](REVERSE_ENGINEERING_STATUS_REPORT.md), [RE_COMPLETE.md](RE_COMPLETE.md) so completion and “what’s left” match the current state.
- **Reference map**: If you publish a copy of `open-nos-as5610/PLAN.md`, its “Reference Map to RE Docs” (§14) should point to the published RE doc paths.

---

## 2. Private information to redact

**Do not push** real IPs, usernames, or credentials to a public repo. Use the placeholders below.

### 2.1 Substitution list (apply to published copy only)

| Private value | Replacement | Notes |
|---------------|-------------|--------|
| `<LIVE_SWITCH_IP>` | `<LIVE_SWITCH_IP>` | Cumulus live switch |
| `<ONL_SWITCH_IP>` | `<ONL_SWITCH_IP>` | ONL / bare-metal switch |
| `<GHIDRA_HOST_IP>` | `<GHIDRA_HOST_IP>` | Ghidra analysis server |
| `<BUILD_SERVER_IP>` | `<BUILD_SERVER_IP>` | Debian build server (modern) |
| `<BUILD_SERVER_IP>` | `<BUILD_SERVER_IP>` | Debian build server (legacy) |
| `<SWITCH_USER>@<LIVE_SWITCH_IP>` | `<SWITCH_USER>@<LIVE_SWITCH_IP>` | When documenting SSH targets |
| `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>` | `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>` | Same |
| `Host <LIVE_SWITCH_IP>` | `Host <LIVE_SWITCH_IP>` | In SSH config examples |
| `<USER>` | Keep as-is | Already a placeholder for Ghidra/build user |
| `SSHPASS`, `SUDOPASS` | Keep as “(unset)” / generic | No real passwords in docs |

### 2.2 Filenames that embed the IP

Trace and analysis filenames contain `<LIVE_SWITCH_IP>`. For the **published** copy you can either:

- **Option A**: Rename for public (e.g. `*<LIVE_SWITCH_IP>*` → `*live-switch*`) and update all links in the redacted docs to the new names, or  
- **Option B**: Keep filenames but ensure **file contents** are redacted (IP replaced by `<LIVE_SWITCH_IP>`). Links will still say “<LIVE_SWITCH_IP>” in the filename; that’s a tradeoff (readers see a placeholder in text but the filename may hint “one device”).

Recommendation: **Option B** for simplicity; optionally rename in a later pass.

### 2.3 Docs that need redaction (high sensitivity)

- **INFRASTRUCTURE_REFERENCE.md** — IPs, hosts table, `SWITCH`, `SSHPASS`, `SUDOPASS`, scp/ssh examples.
- **MANUAL_SSH_KEY_TO_SWITCH.md** — `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>`, “with your password”.
- **SSH_KEY_AUTH_SWITCH.md** — `Host <LIVE_SWITCH_IP>`, `ssh <SWITCH_USER>@<LIVE_SWITCH_IP>`.
- **ENVIRONMENT_REFERENCE.md** — `<SWITCH_USER>@<LIVE_SWITCH_IP>`, `<USER>@<GHIDRA_HOST_IP>`.
- **RUNTIME_TRACING_COMPLETE.md**, **RUNTIME_TRACING_GUIDE.md**, **RUNTIME_TRACING_STATUS.md** — script names and SSH targets with IP.
- **ANALYSIS_RUN_2026-02-18.md** — switch and Ghidra host IPs.
- **SESSION_SUMMARY_2026-02-19.md** — host list.
- All **traces/*.md** — any occurrence of the live-switch IP (and other IPs if present).
- Any other doc that mentions the IPs or `cumulus@...` (see grep list in §3).

---

## 3. How to produce a redacted copy

### Script (recommended)

From the repo root:

```bash
./scripts/reverse-engineering/redact-for-publish.sh [OUTPUT_DIR]
```

If `OUTPUT_DIR` is omitted, defaults to `publish/docs/reverse-engineering`. The script:

- Copies `docs/reverse-engineering/` (including `traces/`) into `OUTPUT_DIR`.
- Applies the substitutions in §2.1 to all `.md` (and optionally `.txt`) files.
- Does **not** rename files (no `<LIVE_SWITCH_IP>` → `live-switch` in filenames); you can do that separately if you want Option A.

Then push or copy only the contents of `OUTPUT_DIR` to the public GitHub repo.

### Manual check

After running the script, search for **private host IPs** only (example subnets like `10.1.1.0/24` or `10.1.1.1` as gateway are fine to leave):

```bash
grep -r -E '10\.1\.1\.(233|222|30)\b|10\.22\.1\.(4|5)\b' publish/docs/reverse-engineering/ || true
grep -r "cumulus@10\|ssh cumulus@" publish/docs/reverse-engineering/ || true
```

Fix any remaining hits by replacing with the placeholders from §2.1.

---

## 4. Checklist before pushing to GitHub

- [ ] Ran `redact-for-publish.sh` (or equivalent) and verified no private IPs/usernames in the output.
- [ ] Synced latest status and path updates (PATH_B_*, REVERSE_ENGINEERING_STATUS_REPORT, RE_COMPLETE, PLAN reference map if published).
- [ ] Grep for `10.1.1`, `10.22.1`, and `cumulus@` in the published tree; all redacted or placeholder.
- [ ] No real passwords or tokens in any file (SSHPASS/SUDOPASS only as “(unset)” or generic description).
- [ ] Example IPs in route/config snippets (e.g. `10.1.1.0/24`, `10.1.1.1` as gateway) are optional to redact; the script only redacts the specific host IPs (233, 222, 30, 10.22.1.x).

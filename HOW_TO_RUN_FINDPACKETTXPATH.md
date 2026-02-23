# How to run FindPacketTxPath (packet TX path for Path B)

**Purpose**: Get opennsl_tx / bcm_tx references, `read()` callers (TUN event loop), and (in libopennsl) callees of opennsl_tx. Used to close Path B checklist §4.3–4.4.

**Script**: `scripts/reverse-engineering/FindPacketTxPath.java`  
**Wrapper**: `scripts/reverse-engineering/ghidra-find-packet-tx-path.sh`

---

## Option 1: Ghidra headless (build server)

1. **Prereqs**: Ghidra installed; binary already imported and analyzed (so the project exists).
2. **Set** `GHIDRA_INSTALL` to your Ghidra install dir (e.g. `/opt/ghidra` or `/home/<USER>/analysis/ghidra`).
3. **Run** (one binary per run):

   ```bash
   cd /path/to/ONL
   GHIDRA_INSTALL=/path/to/ghidra ./scripts/reverse-engineering/ghidra-find-packet-tx-path.sh /path/to/libopennsl.so.1
   GHIDRA_INSTALL=/path/to/ghidra ./scripts/reverse-engineering/ghidra-find-packet-tx-path.sh /path/to/switchd
   ```

4. **Output**:
   - libopennsl: `.../sdk-deep-extract/libopennsl-packet-tx-path.txt`
   - switchd: `.../sdk-deep-extract/switchd-packet-tx-path.txt`

**Note**: Headless uses `-process PROGRAM_NAME -noanalysis`, so the Ghidra project must already exist (e.g. from a previous import/analysis). If the project does not exist, import the binary first (e.g. run another script that uses `-import` once).

---

## Option 2: Ghidra GUI

1. Open Ghidra and load the program (**File → Import File**): either `libopennsl.so.1` or `switchd`.
2. Run analysis (Analysis → Auto Analyze) and wait for it to finish.
3. **Scripts → Run Script…** → choose `FindPacketTxPath.java` (add the repo `scripts/reverse-engineering` to Script Directories if needed).
4. **Output**: The script writes to the path in env var **`SDK_RE_OUTPUT`**, or `/tmp/ghidra-packet-tx-path.txt` if unset.
   - To set the path: before running the script, set `SDK_RE_OUTPUT` in the environment that launches Ghidra, or edit the script’s default path and run again.
5. Run the script **twice** (once with libopennsl loaded, once with switchd) and save the two outputs as e.g. `opennsl-packet-tx-path.txt` and `switchd-packet-tx-path.txt`.

---

## What the script produces

- **References to** `opennsl_tx` / `bcm_tx` / `bcm_pkt_tx` (who calls the TX API).
- **Functions that call `read`** (candidates for the TUN read / event loop).
- **Callees of opennsl_tx** (in libopennsl only): first 50 call refs from the function body (BDE/register/DMA usage).

Use the output to map TX path (TUN read → … → opennsl_tx → …) and to find ioctl/read/write usage for checklist §4.

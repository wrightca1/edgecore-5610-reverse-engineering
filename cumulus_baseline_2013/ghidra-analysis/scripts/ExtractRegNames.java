// Extract the BCM SDK register name table from switchd
// The table base is the symbol referenced at the "reg %s > 32 bit" log call
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryAccessException;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;

public class ExtractRegNames extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        Memory mem = currentProgram.getMemory();

        // Look up the symbol PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT_11bcac14
        Address tableBase = null;
        Iterable<Symbol> all = currentProgram.getSymbolTable().getDefinedSymbols();
        for (Symbol s : all) {
            if (s.getName().startsWith("PTR_s_A9JTAG_M0_IDM_IDM_INTERRUPT_STAT") ||
                s.getName().contains("A9JTAG_M0_IDM_IDM_INTERRUPT_STAT")) {
                tableBase = s.getAddress();
                println("Found table base symbol: " + s.getName() + " @ " + tableBase);
                break;
            }
        }

        if (tableBase == null) {
            // Try hardcoded address from decomp
            tableBase = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x11bcac14L);
            println("Using hardcoded address: " + tableBase);
        }

        // Walk the pointer table, dereference each pointer to get the string
        List<String> regNames = new ArrayList<>();
        int maxEntries = 0x9020;  // soc_reg32_get checks reg < 0x901f
        int validEntries = 0;
        int nullEntries = 0;

        for (int i = 0; i < maxEntries && !monitor.isCancelled(); i++) {
            Address entryAddr = tableBase.add(i * 4);
            if (!mem.contains(entryAddr)) {
                regNames.add(null);
                break;
            }
            int p = mem.getInt(entryAddr);
            long pl = ((long) p) & 0xFFFFFFFFL;

            if (pl == 0) {
                regNames.add(null);
                nullEntries++;
                continue;
            }
            if (pl < 0x10000000L || pl > 0x12000000L) {
                regNames.add(null);
                nullEntries++;
                continue;
            }

            // Read string at pointer
            try {
                Address strAddr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(pl);
                if (!mem.contains(strAddr)) {
                    regNames.add(null);
                    continue;
                }
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < 128; j++) {
                    byte b = mem.getByte(strAddr.add(j));
                    if (b == 0) break;
                    if (b < 0x20 || b > 0x7E) { sb = null; break; }
                    sb.append((char) b);
                }
                if (sb != null && sb.length() > 0) {
                    regNames.add(sb.toString());
                    validEntries++;
                } else {
                    regNames.add(null);
                    nullEntries++;
                }
            } catch (MemoryAccessException e) {
                regNames.add(null);
                break;
            }
            if (i % 5000 == 0 && i > 0) println("  scanned " + i);
        }

        // Save full table
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/bcm_register_names.txt"))) {
            pw.println("# BCM SDK Register Name Table extracted from switchd");
            pw.println("# Table base: " + tableBase);
            pw.printf("# %d valid entries, %d null/skipped, scanned %d slots%n",
                      validEntries, nullEntries, regNames.size());
            pw.println();
            pw.println("# reg_id  | name");
            pw.println("# --------+----------------------");
            for (int i = 0; i < regNames.size(); i++) {
                String n = regNames.get(i);
                if (n != null) {
                    pw.printf("0x%04x   %s%n", i, n);
                }
            }
        }
        println("Extracted " + validEntries + " register names");
    }
}

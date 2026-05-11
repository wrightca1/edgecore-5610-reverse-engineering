// Extract cpld_leds, cpld_system_status, cpld_psu_status, watch_dog_bits from CPLD .ko
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryAccessException;
import ghidra.program.model.data.PointerDataType;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;

public class ExtractCpldTables extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        Memory mem = currentProgram.getMemory();
        SymbolTable st = currentProgram.getSymbolTable();

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/cpld_tables_extracted.txt"))) {
            pw.println("# CPLD data table extraction from accton_as5610_52x_cpld.ko");
            pw.println();

            // The relevant tables - look up by name
            String[] tableNames = {"cpld_leds", "cpld_system_status", "cpld_psu_status", "watch_dog_bits", "accton_as5610_52x_pwm1"};
            for (String tn : tableNames) {
                pw.println("============================================================");
                pw.println("Table: " + tn);
                pw.println("============================================================");
                Symbol sym = null;
                for (Symbol s : st.getSymbols(tn)) { sym = s; break; }
                if (sym == null) {
                    pw.println("  [SYMBOL NOT FOUND]");
                    continue;
                }
                Address a = sym.getAddress();
                pw.println("Address: " + a.toString());

                // Dump 512 bytes from this address as hex + try to decode as struct pointers
                pw.println("\nRaw bytes (up to 512):");
                StringBuilder hex = new StringBuilder();
                for (int i = 0; i < 512; i++) {
                    try {
                        byte b = mem.getByte(a.add(i));
                        hex.append(String.format("%02x ", b & 0xff));
                        if ((i + 1) % 16 == 0) hex.append("\n");
                    } catch (MemoryAccessException e) { break; }
                }
                pw.println(hex.toString());

                // Try to interpret as pointer-to-string array (common for tables of structs)
                pw.println("\nAttempted pointer-table interpretation (4-byte pointers, first 32):");
                for (int i = 0; i < 32; i++) {
                    try {
                        Address e = a.add(i * 4);
                        if (!mem.contains(e)) break;
                        int p = mem.getInt(e);
                        long pl = ((long) p) & 0xFFFFFFFFL;
                        // Try to read string at pointer
                        String s = "";
                        if (pl < 0x100000 && pl > 0) {
                            try {
                                Address pa = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(pl);
                                if (mem.contains(pa)) {
                                    StringBuilder sb = new StringBuilder();
                                    for (int j = 0; j < 64; j++) {
                                        byte b = mem.getByte(pa.add(j));
                                        if (b == 0) break;
                                        if (b < 0x20 || b > 0x7E) { sb = null; break; }
                                        sb.append((char) b);
                                    }
                                    if (sb != null) s = sb.toString();
                                }
                            } catch (Exception ex) {}
                        }
                        pw.printf("  [%2d] +0x%-4x: 0x%08x  %s%n", i, i * 4, p, s.isEmpty() ? "" : "→ \"" + s + "\"");
                    } catch (MemoryAccessException e) { break; }
                }
            }

            // Also dump the help / README strings — they document the layout
            pw.println("\n============================================================");
            pw.println("README sysfs attr content");
            pw.println("============================================================");
            for (Symbol s : st.getSymbols("README")) {
                pw.println("found: " + s.getName() + " @ " + s.getAddress());
            }
        }
        println("Done. Output saved to cpld_tables_extracted.txt");
    }
}

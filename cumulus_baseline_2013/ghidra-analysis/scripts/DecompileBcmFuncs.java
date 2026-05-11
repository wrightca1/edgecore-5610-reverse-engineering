// Decompile the BCM SDK functions we labeled in switchd
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.regex.Pattern;
import java.util.TreeMap;
import java.util.Map;

public class DecompileBcmFuncs extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        Pattern bcmPat = Pattern.compile("(bcm_\\w+|hal_bcm_\\w+)");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        // Group decomp by category
        TreeMap<String, StringBuilder> categories = new TreeMap<>();
        TreeMap<String, Function> apiFunctions = new TreeMap<>();

        SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
        int found = 0;
        while (syms.hasNext() && !monitor.isCancelled()) {
            Symbol s = syms.next();
            String name = s.getName();
            if (!bcmPat.matcher(name).find()) continue;
            Function f = currentProgram.getFunctionManager().getFunctionAt(s.getAddress());
            if (f == null) continue;
            // Skip known false-positive helpers
            if (s.getAddress().getOffset() == 0x10047de0L) continue;
            if (s.getAddress().getOffset() == 0x10029bacL) continue;
            apiFunctions.put(name, f);
            found++;
        }

        println("Decompiling " + found + " BCM API functions");
        int decompiled = 0;

        for (Map.Entry<String, Function> e : apiFunctions.entrySet()) {
            if (monitor.isCancelled()) break;
            String name = e.getKey();
            Function f = e.getValue();
            long size = f.getBody().getNumAddresses();
            if (size < 4 || size > 8192) continue;  // skip tiny or huge

            // Determine category
            String cat;
            if (name.contains("port_")) cat = "port";
            else if (name.contains("l3_") || name.contains("l3host") || name.contains("l3route")) cat = "l3";
            else if (name.contains("l2_") || name.contains("vlan_")) cat = "l2_vlan";
            else if (name.contains("field_")) cat = "field_acl";
            else if (name.contains("mirror_")) cat = "mirror";
            else if (name.contains("trunk_")) cat = "trunk";
            else if (name.contains("rate_") || name.contains("policer_")) cat = "rate_policer";
            else if (name.contains("rx_") || name.contains("tx_")) cat = "rxtx";
            else if (name.contains("stat_") || name.contains("counter")) cat = "stats";
            else if (name.contains("wlan_") || name.contains("mim_") || name.contains("mpls_")) cat = "encap";
            else cat = "other";

            StringBuilder sb = categories.computeIfAbsent(cat, k -> new StringBuilder());

            try {
                DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                if (res.decompileCompleted()) {
                    sb.append("/* === " + name + " @ " + f.getEntryPoint() + " (size=" + size + ") === */\n");
                    sb.append(res.getDecompiledFunction().getC());
                    sb.append("\n\n");
                    decompiled++;
                }
            } catch (Exception ex) {
                sb.append("/* DECOMPILE FAILED " + name + ": " + ex.getMessage() + " */\n\n");
            }
        }

        // Write each category to a separate file
        for (Map.Entry<String, StringBuilder> e : categories.entrySet()) {
            try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_bcm_decomp_" + e.getKey() + ".c"))) {
                pw.println("/* BCM SDK functions in category: " + e.getKey() + " */");
                pw.println("/* Decompiled from switchd binary */");
                pw.println();
                pw.print(e.getValue().toString());
            }
        }
        decomp.dispose();
        println("Decompiled " + decompiled + " functions across " + categories.size() + " categories");
    }
}

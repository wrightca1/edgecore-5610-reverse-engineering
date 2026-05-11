// Targeted survey of switchd binary — find BCM SDK API calls + string-ref clues
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Set;
import java.util.Map;

public class SwitchdSurvey extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        // 1) String inventory - focus on BCM SDK names + Cumulus paths + register names
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_interesting_strings.txt"))) {
            pw.println("# Interesting strings from switchd");
            String[] patterns = {
                "bcm_", "_bcm_", "BCM5", "BCM56", "BCM84",
                "warpcore", "Warpcore", "WC",
                "cmic", "CMIC",
                "trident", "Trident",
                "/etc/cumulus", "/var/lib/cumulus", "/var/cache/cumulus", "/run/cumulus",
                "switchd", "Switchd",
                "FORMAT_", "_TCAM", "_TABLE",
                "PORT_", "MY_STATION", "L3_", "L2_", "VLAN_", "ARL_",
                "MDIO", "miim", "MIIM",
                "datapath", "TX", "RX",
                "phy_", "MMU", "FP_",
                "version", "Version"
            };
            DataIterator data = currentProgram.getListing().getDefinedData(true);
            int count = 0;
            while (data.hasNext() && !monitor.isCancelled()) {
                Data d = data.next();
                if (d.hasStringValue()) {
                    String s = d.getDefaultValueRepresentation();
                    if (s.length() > 6 && s.length() < 120) {
                        for (String p : patterns) {
                            if (s.contains(p)) {
                                pw.printf("0x%-10s  %s%n", d.getAddress().toString(), s);
                                count++;
                                break;
                            }
                        }
                    }
                }
                if (count > 5000) break;
            }
            pw.println("# Total: " + count);
            println("Interesting strings: " + count);
        }

        // 2) Function count + size histogram
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_function_summary.txt"))) {
            FunctionIterator funcs = currentProgram.getFunctionManager().getFunctions(true);
            int total = 0;
            int small = 0, medium = 0, large = 0, huge = 0;
            while (funcs.hasNext() && !monitor.isCancelled()) {
                Function f = funcs.next();
                long size = f.getBody().getNumAddresses();
                if (size < 100) small++;
                else if (size < 500) medium++;
                else if (size < 2000) large++;
                else huge++;
                total++;
            }
            pw.printf("Total functions: %d%n", total);
            pw.printf("  Small  (<100 bytes):    %d%n", small);
            pw.printf("  Medium (100-500):       %d%n", medium);
            pw.printf("  Large  (500-2000):      %d%n", large);
            pw.printf("  Huge   (>2000):         %d%n", huge);
            println("Functions: " + total);
        }

        // 3) Search for log call patterns that contain BCM API function names in their format strings
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_bcm_log_messages.txt"))) {
            pw.println("# Log messages mentioning BCM/Warpcore/CMIC/etc");
            String[] keywords = {"bcm_", "Warpcore", "WC", "CMIC", "PHY", "Trident", "MDIO", "MMU"};
            DataIterator data = currentProgram.getListing().getDefinedData(true);
            int count = 0;
            while (data.hasNext() && !monitor.isCancelled()) {
                Data d = data.next();
                if (d.hasStringValue()) {
                    String s = d.getDefaultValueRepresentation();
                    if (s.length() > 10 && s.length() < 200 && (s.contains("%") || s.contains(":"))) {
                        for (String k : keywords) {
                            if (s.contains(k)) {
                                pw.printf("0x%-10s  %s%n", d.getAddress().toString(), s);
                                count++;
                                break;
                            }
                        }
                    }
                }
                if (count > 2000) break;
            }
            pw.println("# Total: " + count);
            println("Log messages: " + count);
        }

        // Skip decompilation - too big for this pass
        println("Survey complete (skipped full decompilation due to size)");
    }
}

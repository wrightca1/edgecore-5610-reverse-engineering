// Deep call-graph trace: from labeled BCM APIs all the way down to the
// chip-register access primitives. Identify candidate MIIM/SCHAN/MMIO
// functions by their string-reference signatures.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Data;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.listing.FunctionManager;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.regex.Pattern;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.Set;
import java.util.Map;
import java.util.Deque;
import java.util.List;

public class DeepBcmTrace extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        FunctionManager fm = currentProgram.getFunctionManager();
        Pattern bcmPat = Pattern.compile("(bcm_\\w+|hal_bcm_\\w+)");

        // Seeds: labeled BCM API functions
        SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
        List<Function> seeds = new ArrayList<>();
        while (syms.hasNext() && !monitor.isCancelled()) {
            Symbol s = syms.next();
            if (!bcmPat.matcher(s.getName()).find()) continue;
            if (s.getAddress().getOffset() == 0x10047de0L) continue;
            if (s.getAddress().getOffset() == 0x10029bacL) continue;
            Function f = fm.getFunctionAt(s.getAddress());
            if (f != null) seeds.add(f);
        }

        // Deeper BFS with depth tracking
        int MAX_DEPTH = 5;
        Map<Address, Integer> depthMap = new HashMap<>();
        Map<Address, Set<String>> callerNames = new HashMap<>();
        Deque<Function> queue = new ArrayDeque<>();
        for (Function f : seeds) {
            depthMap.put(f.getEntryPoint(), 0);
            queue.add(f);
        }

        int total = 0;
        while (!queue.isEmpty() && total < 5000 && !monitor.isCancelled()) {
            Function f = queue.removeFirst();
            int depth = depthMap.get(f.getEntryPoint());
            if (depth >= MAX_DEPTH) continue;
            total++;

            Set<Function> callees;
            try {
                callees = f.getCalledFunctions(monitor);
            } catch (Exception ex) {
                continue;
            }

            for (Function callee : callees) {
                Address ca = callee.getEntryPoint();
                callerNames.computeIfAbsent(ca, k -> new HashSet<>()).add(f.getName());
                Integer cur = depthMap.get(ca);
                if (cur == null || depth + 1 < cur) {
                    depthMap.put(ca, depth + 1);
                    if (!queue.contains(callee)) queue.add(callee);
                }
            }
        }

        println("Total functions reached at depth ≤ " + MAX_DEPTH + ": " + depthMap.size());

        // Categorize functions by referenced strings (look for chip-register clues)
        Map<Address, Set<String>> funcStrings = new HashMap<>();
        ReferenceManager refMgr = currentProgram.getReferenceManager();
        String[] hwKeywords = {
            "schan", "SCHAN", "miim", "MIIM", "mmio", "MMIO",
            "cmic", "CMIC", "ioctl", "ipic", "bde", "BDE",
            "/dev/", "register", "phy_", "fault", "interrupt",
            "linux-user-bde", "linux-kernel-bde",
            "bcm-sdk/src/", "bcm-sdk/sys/",
            "soc_", "_reg", "_read", "_write", "MII_", "PHY_",
            "schan_", "_schan", "MMU", "DMA", "TIMEOUT"
        };

        for (Address a : depthMap.keySet()) {
            Function f = fm.getFunctionAt(a);
            if (f == null) continue;
            Address[] body = new Address[]{f.getEntryPoint(), f.getBody().getMaxAddress()};
            ghidra.program.model.address.AddressIterator it = f.getBody().getAddresses(true);
            int count = 0;
            while (it.hasNext() && count < 1000) {
                Address insAddr = it.next();
                Reference[] refs = currentProgram.getReferenceManager().getReferencesFrom(insAddr);
                for (Reference r : refs) {
                    if (r.getReferenceType().isData() || r.getReferenceType().isRead()) {
                        Data d = getDataAt(r.getToAddress());
                        if (d != null && d.hasStringValue()) {
                            String s = d.getDefaultValueRepresentation();
                            for (String kw : hwKeywords) {
                                if (s.contains(kw)) {
                                    funcStrings.computeIfAbsent(a, k -> new HashSet<>()).add(s);
                                }
                            }
                        }
                    }
                }
                count++;
            }
        }

        // Score functions by:
        // - Number of HW-keyword string references
        // - How deep in call chain they are (deeper = closer to primitives)
        // - Small size (primitives tend to be small)
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_deep_trace.txt"))) {
            pw.println("# Deep BCM SDK call-graph trace (depth ≤ " + MAX_DEPTH + ")");
            pw.println("# Functions ranked by chip-register-keyword string references");
            pw.println();

            List<Map.Entry<Address, Set<String>>> ranked = new ArrayList<>(funcStrings.entrySet());
            ranked.sort((a, b) -> b.getValue().size() - a.getValue().size());

            for (Map.Entry<Address, Set<String>> e : ranked) {
                Address a = e.getKey();
                Function f = fm.getFunctionAt(a);
                int depth = depthMap.getOrDefault(a, -1);
                long size = (f != null) ? f.getBody().getNumAddresses() : 0;
                pw.printf("0x%-10s  %-40s  depth=%d size=%d  hw_refs=%d%n",
                    a.toString(), f.getName(), depth, size, e.getValue().size());
                int shown = 0;
                for (String s : e.getValue()) {
                    if (shown++ > 4) break;
                    String snip = s.length() > 100 ? s.substring(0, 100) + "..." : s;
                    pw.println("    " + snip);
                }
                pw.println();
            }
        }

        // Decompile top candidates (most HW-keyword refs)
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        int decompiled = 0;
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_chip_primitives_decomp.c"))) {
            pw.println("/* Candidate BCM chip-register primitive functions, decompiled */");
            pw.println();

            List<Map.Entry<Address, Set<String>>> ranked = new ArrayList<>(funcStrings.entrySet());
            ranked.sort((a, b) -> b.getValue().size() - a.getValue().size());

            for (Map.Entry<Address, Set<String>> e : ranked) {
                if (decompiled >= 40) break;
                Function f = fm.getFunctionAt(e.getKey());
                if (f == null) continue;
                long size = f.getBody().getNumAddresses();
                if (size < 8 || size > 4096) continue;
                int depth = depthMap.getOrDefault(e.getKey(), -1);
                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.println("/* === " + f.getName() + " @ " + f.getEntryPoint() +
                                   " (size=" + size + " depth=" + depth + " hw_refs=" + e.getValue().size() + ") === */");
                        pw.println("/* String refs:");
                        int n = 0;
                        for (String s : e.getValue()) {
                            if (n++ > 3) { pw.println("   ..."); break; }
                            pw.println("   " + s);
                        }
                        pw.println("*/");
                        pw.println(res.getDecompiledFunction().getC());
                        pw.println();
                        decompiled++;
                    }
                } catch (Exception ex) {
                    pw.println("/* DECOMPILE FAILED: " + f.getName() + " - " + ex.getMessage() + " */");
                }
            }
        }
        decomp.dispose();
        println("Decompiled " + decompiled + " chip-primitive candidates");
    }
}

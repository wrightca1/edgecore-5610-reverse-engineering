// Follow BCM API → worker function call chains. Recursive depth-limited
// BFS from each labeled bcm_* function, collecting callees, decompiling
// each, and looking for chip-register magic + string fingerprints.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolType;
import ghidra.program.model.symbol.SourceType;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.regex.Pattern;
import java.util.HashSet;
import java.util.HashMap;
import java.util.ArrayDeque;
import java.util.Set;
import java.util.Map;
import java.util.Deque;
import java.util.ArrayList;
import java.util.List;

public class FollowBcmCallGraph extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        Pattern bcmPat = Pattern.compile("(bcm_\\w+|hal_bcm_\\w+)");

        // Find all labeled bcm_ functions (seeds)
        SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
        List<Function> seeds = new ArrayList<>();
        while (syms.hasNext() && !monitor.isCancelled()) {
            Symbol s = syms.next();
            if (!bcmPat.matcher(s.getName()).find()) continue;
            // Skip known common helpers
            if (s.getAddress().getOffset() == 0x10047de0L) continue;
            if (s.getAddress().getOffset() == 0x10029bacL) continue;
            Function f = currentProgram.getFunctionManager().getFunctionAt(s.getAddress());
            if (f != null) seeds.add(f);
        }
        println("Seeds: " + seeds.size() + " labeled bcm_ functions");

        // BFS through callees up to depth N
        int MAX_DEPTH = 2;
        int MAX_FUNCS = 1500;
        Set<Address> visited = new HashSet<>();
        Map<Address, Integer> depthMap = new HashMap<>();
        Deque<Function> queue = new ArrayDeque<>();
        for (Function f : seeds) {
            visited.add(f.getEntryPoint());
            depthMap.put(f.getEntryPoint(), 0);
            queue.add(f);
        }

        // Collect callees + their callers
        Map<Address, Set<String>> callerNames = new HashMap<>();   // callee → set of calling-API names

        while (!queue.isEmpty() && visited.size() < MAX_FUNCS && !monitor.isCancelled()) {
            Function f = queue.removeFirst();
            int depth = depthMap.get(f.getEntryPoint());
            if (depth >= MAX_DEPTH) continue;

            String callerName = f.getName();

            // Get called functions
            Set<Function> callees = f.getCalledFunctions(monitor);
            for (Function callee : callees) {
                Address ca = callee.getEntryPoint();
                callerNames.computeIfAbsent(ca, k -> new HashSet<>()).add(callerName);
                if (!visited.contains(ca)) {
                    visited.add(ca);
                    depthMap.put(ca, depth + 1);
                    queue.add(callee);
                }
            }
        }

        println("Reachable: " + visited.size() + " functions (depth ≤ " + MAX_DEPTH + ")");

        // Find the "highly-used" functions - called by many BCM APIs
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_bcm_call_graph.txt"))) {
            pw.println("# BCM SDK call graph (depth ≤ " + MAX_DEPTH + " from labeled API roots)");
            pw.println("# Format: callee_addr  caller_count  caller_API_names");
            pw.println();

            // Sort by caller_count descending
            List<Map.Entry<Address, Set<String>>> entries = new ArrayList<>(callerNames.entrySet());
            entries.sort((a, b) -> b.getValue().size() - a.getValue().size());

            for (Map.Entry<Address, Set<String>> e : entries) {
                if (e.getValue().size() < 2) continue;
                Function f = currentProgram.getFunctionManager().getFunctionAt(e.getKey());
                String fname = (f != null) ? f.getName() : "FUN_" + e.getKey();
                long size = (f != null) ? f.getBody().getNumAddresses() : 0;
                pw.printf("%s @ 0x%s (size=%d)%n", fname, e.getKey(), size);
                pw.printf("  called by %d BCM APIs: %s%n", e.getValue().size(),
                          String.join(", ", e.getValue().stream().sorted().limit(20).toArray(String[]::new)));
                pw.println();
            }
        }

        // Decompile the top-N most-called helpers
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        int decompiled = 0;
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_bcm_workers_decomp.c"))) {
            pw.println("/* Top-N called BCM SDK helper functions, decompiled */");
            pw.println();

            // Sort callees by caller count descending
            List<Map.Entry<Address, Set<String>>> entries = new ArrayList<>(callerNames.entrySet());
            entries.sort((a, b) -> b.getValue().size() - a.getValue().size());

            for (Map.Entry<Address, Set<String>> e : entries) {
                if (decompiled >= 60) break;
                if (e.getValue().size() < 2) continue;
                Function f = currentProgram.getFunctionManager().getFunctionAt(e.getKey());
                if (f == null) continue;
                long size = f.getBody().getNumAddresses();
                if (size < 8 || size > 4096) continue;

                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.println("/* === " + f.getName() + " @ " + f.getEntryPoint() + " (size=" + size + ") === */");
                        pw.println("/* Called by " + e.getValue().size() + " BCM APIs */");
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
        println("Decompiled " + decompiled + " helper functions");
    }
}

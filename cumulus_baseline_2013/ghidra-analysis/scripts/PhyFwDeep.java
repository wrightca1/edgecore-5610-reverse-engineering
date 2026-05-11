// PHY firmware deep dive: create functions at every LCALL/ACALL target,
// then for each function, list its MMIO accesses + recursive structure.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.SourceType;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.cmd.disassemble.DisassembleCommand;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.Map;

public class PhyFwDeep extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");
        FunctionManager fm = currentProgram.getFunctionManager();

        // Phase 1: Walk all instructions, collect LCALL/ACALL targets
        Set<Long> callTargets = new HashSet<>();
        Map<Long, Set<Long>> calleeToCallers = new HashMap<>();  // callee → caller addrs
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        while (it.hasNext() && !monitor.isCancelled()) {
            Instruction ins = it.next();
            String mnem = ins.getMnemonicString();
            if (mnem.equals("LCALL") || mnem.equals("ACALL")) {
                Object[] objs = ins.getOpObjects(0);
                if (objs.length > 0 && objs[0] instanceof Scalar) {
                    long target = ((Scalar) objs[0]).getUnsignedValue();
                    if (target >= 0x8000 && target < 0x10000) {
                        callTargets.add(target);
                        calleeToCallers.computeIfAbsent(target, k -> new HashSet<>())
                                       .add(ins.getAddress().getOffset());
                    }
                }
            }
        }
        println("Phase 1: found " + callTargets.size() + " unique call targets");

        // Phase 2: Disassemble at each target and create a function there
        int created = 0;
        for (long target : callTargets) {
            if (monitor.isCancelled()) break;
            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(target);
            if (!currentProgram.getMemory().contains(a)) continue;

            // Disassemble (may already be disassembled)
            DisassembleCommand dcmd = new DisassembleCommand(a, null, true);
            dcmd.applyTo(currentProgram, monitor);

            // Create function
            if (fm.getFunctionAt(a) == null) {
                CreateFunctionCmd fcmd = new CreateFunctionCmd(a);
                if (fcmd.applyTo(currentProgram, monitor)) created++;
            }
        }
        println("Phase 2: created " + created + " new functions");

        // Phase 3: For each function, compute:
        // - size
        // - MMIO addresses touched (via MOVX @DPTR after MOV DPTR, #imm)
        // - Functions it calls (LCALL/ACALL targets)
        // - Whether it's a "leaf" (no calls) or "branch" (has calls)
        Map<Address, FuncInfo> info = new HashMap<>();
        Iterable<Function> allFuncs = fm.getFunctions(true);
        for (Function f : allFuncs) {
            if (monitor.isCancelled()) break;
            FuncInfo fi = new FuncInfo();
            fi.size = f.getBody().getNumAddresses();

            long lastDPTR = -1;
            InstructionIterator fIt = currentProgram.getListing().getInstructions(f.getBody(), true);
            while (fIt.hasNext()) {
                Instruction ins = fIt.next();
                String mnem = ins.getMnemonicString();

                if (mnem.equals("MOV")) {
                    String ops = ins.toString();
                    if (ops.contains("DPTR") && ops.contains("#")) {
                        Object[] objs = ins.getOpObjects(ins.getNumOperands() - 1);
                        if (objs.length > 0 && objs[0] instanceof Scalar) {
                            lastDPTR = (int) ((Scalar) objs[0]).getUnsignedValue();
                        }
                    }
                } else if (mnem.equals("MOVX")) {
                    if (lastDPTR >= 0) {
                        String ops = ins.toString();
                        if (ops.contains("@DPTR,A")) fi.mmioWrites.add((int) lastDPTR);
                        else if (ops.contains("A,@DPTR")) fi.mmioReads.add((int) lastDPTR);
                    }
                } else if (mnem.equals("INC")) {
                    String ops = ins.toString();
                    if (ops.contains("DPTR") && lastDPTR >= 0)
                        lastDPTR = (lastDPTR + 1) & 0xFFFF;
                } else if (mnem.equals("LCALL") || mnem.equals("ACALL")) {
                    Object[] objs = ins.getOpObjects(0);
                    if (objs.length > 0 && objs[0] instanceof Scalar) {
                        fi.calls.add((int) ((Scalar) objs[0]).getUnsignedValue());
                    }
                    lastDPTR = -1;  // can't track DPTR across calls
                } else if (mnem.startsWith("LJMP") || mnem.startsWith("AJMP") || mnem.startsWith("SJMP")) {
                    lastDPTR = -1;
                }
            }
            info.put(f.getEntryPoint(), fi);
        }

        // Phase 4: Output a function map
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_function_map.txt"))) {
            pw.println("# PHY firmware function map");
            pw.printf("# %d functions discovered (LCALL-following from entry @ 0x8000)%n", info.size());
            pw.println();
            pw.println("# Format: addr size #calls #mmio_r #mmio_w role");
            pw.println("# Role: LEAF (no calls) | BRANCH (has calls)");
            pw.println();

            // Sort by entry-point address
            List<Map.Entry<Address, FuncInfo>> sorted = new ArrayList<>(info.entrySet());
            sorted.sort((a, b) -> Long.compare(a.getKey().getOffset(), b.getKey().getOffset()));

            for (Map.Entry<Address, FuncInfo> e : sorted) {
                FuncInfo fi = e.getValue();
                String role = fi.calls.isEmpty() ? "LEAF  " : "BRANCH";
                pw.printf("0x%-6s  size=%-5d calls=%-3d mmio_r=%-3d mmio_w=%-3d  %s%n",
                    e.getKey().toString(), fi.size, fi.calls.size(),
                    fi.mmioReads.size(), fi.mmioWrites.size(), role);

                // For leaves with MMIO, show the addresses they touch
                if (fi.calls.isEmpty() && (fi.mmioReads.size() + fi.mmioWrites.size() > 0)) {
                    StringBuilder sb = new StringBuilder();
                    if (!fi.mmioWrites.isEmpty()) {
                        sb.append("        write→ ");
                        for (Integer addr : fi.mmioWrites) sb.append(String.format("0x%04x ", addr));
                        sb.append("\n");
                    }
                    if (!fi.mmioReads.isEmpty()) {
                        sb.append("        read←  ");
                        for (Integer addr : fi.mmioReads) sb.append(String.format("0x%04x ", addr));
                        sb.append("\n");
                    }
                    pw.print(sb);
                }
            }
        }

        // Phase 5: Identify the entry point + top-N most-called functions
        // (these are the firmware's "hot" helpers)
        Map<Long, Integer> callCounts = new HashMap<>();
        for (FuncInfo fi : info.values()) {
            for (Integer t : fi.calls) {
                callCounts.merge(t.longValue(), 1, Integer::sum);
            }
        }
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_hot_functions.txt"))) {
            pw.println("# Most-called PHY firmware functions (top 30)");
            pw.println("# (these are the canonical I/O primitives)");
            pw.println();
            List<Map.Entry<Long, Integer>> ranked = new ArrayList<>(callCounts.entrySet());
            ranked.sort((a, b) -> b.getValue() - a.getValue());
            int n = 0;
            for (Map.Entry<Long, Integer> e : ranked) {
                if (n++ >= 30) break;
                Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(e.getKey());
                Function f = fm.getFunctionAt(a);
                long size = f != null ? f.getBody().getNumAddresses() : 0;
                FuncInfo fi = info.get(a);
                int rw = fi != null ? fi.mmioReads.size() : 0;
                int ww = fi != null ? fi.mmioWrites.size() : 0;
                pw.printf("0x%-6s  called %d times  size=%-5d  mmio_r=%d mmio_w=%d%n",
                    a.toString(), e.getValue(), size, rw, ww);
            }
        }

        println("Wrote function_map.txt + hot_functions.txt");
    }

    static class FuncInfo {
        long size = 0;
        Set<Integer> mmioReads = new java.util.TreeSet<>();
        Set<Integer> mmioWrites = new java.util.TreeSet<>();
        Set<Integer> calls = new java.util.TreeSet<>();
    }
}

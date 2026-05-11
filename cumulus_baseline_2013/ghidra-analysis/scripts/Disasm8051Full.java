// Aggressive 8051 disassembly: walk every LCALL/ACALL/AJMP/LJMP target
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.program.model.scalar.Scalar;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.ArrayDeque;
import java.util.Set;
import java.util.Deque;

public class Disasm8051Full extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        Set<Long> seen = new HashSet<>();
        Deque<Long> queue = new ArrayDeque<>();

        // seed with firmware base address (0x8000) since firmware was relocated
        // The first byte of the file is at 0x8000 (downloaded code RAM)
        long[] seeds = {0x8000, 0x8003, 0x800B, 0x8013, 0x801B, 0x8023, 0x802B,
                        0x8033, 0x803B, 0x8043, 0x804B, 0x8053};
        for (long s : seeds) queue.add(s);

        int iter = 0;
        while (!queue.isEmpty() && iter < 5000 && !monitor.isCancelled()) {
            long addr = queue.removeFirst();
            if (seen.contains(addr)) continue;
            seen.add(addr);

            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addr);
            if (!currentProgram.getMemory().contains(a)) continue;

            // Disassemble at this address
            DisassembleCommand cmd = new DisassembleCommand(a, null, true);
            cmd.applyTo(currentProgram, monitor);
            iter++;

            // Walk forward instructions, queueing call/jump targets
            InstructionIterator it = currentProgram.getListing().getInstructions(a, true);
            int walked = 0;
            while (it.hasNext() && walked < 200 && !monitor.isCancelled()) {
                Instruction ins = it.next();
                String mnem = ins.getMnemonicString();
                if (mnem.equals("LCALL") || mnem.equals("ACALL") ||
                    mnem.equals("LJMP") || mnem.equals("AJMP") ||
                    mnem.equals("JZ") || mnem.equals("JNZ") || mnem.equals("JC") || mnem.equals("JNC") ||
                    mnem.equals("JB") || mnem.equals("JNB") || mnem.equals("JBC") ||
                    mnem.equals("DJNZ") || mnem.equals("CJNE") || mnem.equals("SJMP")) {

                    Object[] objs = ins.getOpObjects(ins.getNumOperands() - 1);
                    if (objs.length > 0 && objs[0] instanceof Scalar) {
                        long target = ((Scalar) objs[0]).getUnsignedValue();
                        if (!seen.contains(target) && target >= 0x8000 && target < 0x10000) {
                            queue.add(target);
                            // Also mark functions for LCALL/ACALL/LJMP/AJMP
                            if (mnem.startsWith("LCALL") || mnem.startsWith("ACALL")) {
                                Address ta = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(target);
                                CreateFunctionCmd fc = new CreateFunctionCmd(ta);
                                fc.applyTo(currentProgram, monitor);
                            }
                        }
                    }
                }
                // Stop at unconditional control flow
                if (mnem.equals("LJMP") || mnem.equals("AJMP") || mnem.equals("SJMP") || mnem.equals("RET") || mnem.equals("RETI")) {
                    break;
                }
                walked++;
            }
        }

        // Count
        InstructionIterator allIt = currentProgram.getListing().getInstructions(true);
        int total = 0;
        while (allIt.hasNext() && !monitor.isCancelled()) { allIt.next(); total++; }
        println("Total instructions: " + total + " (walked " + iter + " addresses)");
        println("Total functions: " + currentProgram.getFunctionManager().getFunctionCount());

        // Dump full disassembly
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_disasm_full.txt"))) {
            pw.println("# Full 8051 disassembly of " + currentProgram.getName());
            pw.printf("# %d instructions, %d functions%n", total, currentProgram.getFunctionManager().getFunctionCount());
            pw.println();
            InstructionIterator it = currentProgram.getListing().getInstructions(true);
            while (it.hasNext() && !monitor.isCancelled()) {
                Instruction ins = it.next();
                pw.printf("%-8s  %-12s  %s%n",
                    ins.getAddress().toString(),
                    bytesToHex(ins.getBytes()),
                    ins.toString());
            }
        }
        println("Full disassembly saved");
    }

    String bytesToHex(byte[] b) {
        StringBuilder s = new StringBuilder();
        for (byte x : b) s.append(String.format("%02x ", x));
        return s.toString();
    }
}

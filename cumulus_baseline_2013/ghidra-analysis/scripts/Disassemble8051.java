// Force 8051 disassembly from reset vector + extract structured tables
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.AddressSet;

import java.io.PrintWriter;
import java.io.FileWriter;

public class Disassemble8051 extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        // Set entry point at 0x0000 (8051 reset vector)
        Address entry = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x0000);
        createLabel(entry, "reset_vector", true, SourceType.IMPORTED);
        addEntryPoint(entry);

        // Standard 8051 interrupt vectors (every 8 bytes from 0x0003)
        int[] vectors = { 0x0003, 0x000b, 0x0013, 0x001b, 0x0023, 0x002b, 0x0033, 0x003b, 0x0043, 0x004b, 0x0053 };
        String[] vec_names = { "ext_int0", "timer0", "ext_int1", "timer1", "serial", "timer2", "irq0x33", "irq0x3b", "irq0x43", "irq0x4b", "irq0x53" };
        for (int i = 0; i < vectors.length; i++) {
            Address va = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(vectors[i]);
            createLabel(va, vec_names[i], true, SourceType.IMPORTED);
            addEntryPoint(va);
        }

        println("Disassembling from reset vector @ 0x0000 and 11 interrupt vectors");
        // Disassemble starting at 0x0000
        DisassembleCommand cmd = new DisassembleCommand(entry, null, true);
        cmd.applyTo(currentProgram, monitor);

        // Also disassemble vectors
        for (int v : vectors) {
            Address va = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(v);
            DisassembleCommand cmd2 = new DisassembleCommand(va, null, true);
            cmd2.applyTo(currentProgram, monitor);
        }

        // Count instructions
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        int instCount = 0;
        while (it.hasNext() && !monitor.isCancelled()) {
            it.next();
            instCount++;
        }
        println("Total instructions disassembled: " + instCount);

        // Dump first 2KB of disassembly
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_disasm.txt"))) {
            pw.println("# 8051 disassembly of " + currentProgram.getName());
            pw.println("# Reset vector @ 0x0000");
            pw.println();
            it = currentProgram.getListing().getInstructions(true);
            int n = 0;
            while (it.hasNext() && n < 500 && !monitor.isCancelled()) {
                Instruction ins = it.next();
                pw.printf("%-8s  %-12s  %s%n",
                    ins.getAddress().toString(),
                    bytesToHex(ins.getBytes()),
                    ins.toString());
                n++;
            }
            pw.println("# Showing first " + n + " of " + instCount + " instructions");
        }

        println("Disassembly saved");
    }

    String bytesToHex(byte[] b) {
        StringBuilder s = new StringBuilder();
        for (byte x : b) s.append(String.format("%02x ", x));
        return s.toString();
    }
}

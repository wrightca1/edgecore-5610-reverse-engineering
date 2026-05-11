// Follow FUN_108508ac (raw register read), find callers of the ioctl PLT stub,
// and decompile a few more key primitives.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.Set;

public class FollowRegistersAndIoctl extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        // 1) Find callers of the ioctl PLT stub at 0x11317c50
        Address ioctlStub = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x11317c50L);
        ReferenceManager refMgr = currentProgram.getReferenceManager();

        Set<Function> ioctlCallers = new HashSet<>();
        java.util.Iterator<Reference> rit = refMgr.getReferencesTo(ioctlStub).iterator();
        while (rit.hasNext()) {
            Reference r = rit.next();
            if (r.getReferenceType().isCall()) {
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                if (f != null) ioctlCallers.add(f);
            }
        }
        println("ioctl PLT stub callers: " + ioctlCallers.size());

        // 2) Decompile the ioctl callers + deeper register primitives
        long[] more_targets = {
            0x108508acL,   // raw register read primitive
            0x10847350L,   // standard chip register read
            0x10846528L,   // alternate chip register read
            0x113128a8L,   // sal_int_context check
            0x10322de8L,   // BDE ioctl wrapper (referenced from BDE init)
        };

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_register_primitives_deep.c"))) {
            pw.println("/* Even deeper register/ioctl primitives */");
            pw.println();
            for (long addr : more_targets) {
                if (monitor.isCancelled()) break;
                Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addr);
                Function f = currentProgram.getFunctionManager().getFunctionAt(a);
                if (f == null) {
                    pw.printf("/* NO FUNCTION at 0x%x */%n%n", addr);
                    continue;
                }
                long size = f.getBody().getNumAddresses();
                pw.printf("/* === %s @ 0x%x (size=%d) === */%n", f.getName(), addr, size);
                try {
                    DecompileResults res = decomp.decompileFunction(f, 60, monitor);
                    if (res.decompileCompleted()) {
                        pw.println(res.getDecompiledFunction().getC());
                    }
                } catch (Exception ex) {
                    pw.println("/* DECOMP FAILED */");
                }
                pw.println();
            }
        }

        // Output ioctl caller list + decomp
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_ioctl_wrappers_full.c"))) {
            pw.println("/* All ioctl() callers - the BDE interface layer */");
            pw.printf("/* %d total callers found via PLT stub xrefs */%n%n", ioctlCallers.size());
            int decompiled = 0;
            for (Function f : ioctlCallers) {
                long size = f.getBody().getNumAddresses();
                if (size < 8 || size > 2048) continue;
                if (decompiled >= 30) break;
                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.println("/* === " + f.getName() + " @ " + f.getEntryPoint() + " (size=" + size + ") === */");
                        pw.println(res.getDecompiledFunction().getC());
                        pw.println();
                        decompiled++;
                    }
                } catch (Exception ex) {}
            }
            println("Decompiled " + decompiled + " ioctl wrappers");
        }

        // Find callers of FUN_108508ac (the raw register read primitive)
        Address rawReadAddr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x108508acL);
        Set<Function> rawReadCallers = new HashSet<>();
        rit = refMgr.getReferencesTo(rawReadAddr).iterator();
        while (rit.hasNext()) {
            Reference r = rit.next();
            if (r.getReferenceType().isCall()) {
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                if (f != null) rawReadCallers.add(f);
            }
        }
        println("FUN_108508ac (raw register read) callers: " + rawReadCallers.size());

        decomp.dispose();
    }
}

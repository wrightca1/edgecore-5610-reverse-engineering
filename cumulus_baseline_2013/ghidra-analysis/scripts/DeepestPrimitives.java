// Decompile the deepest chip-access primitives:
// - soc_schan_op (FUN_108623e4)
// - port-table HW lookup (FUN_10619410)
// - ioctl wrappers for /dev/linux-user-bde
// - functions that reference specific named registers we extracted
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.mem.Memory;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.Set;
import java.util.Map;
import java.util.List;

public class DeepestPrimitives extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        // Target functions we want to decompile (large primitives)
        long[] targets = {
            0x108623e4L,  // soc_schan_op (CMIC_SCHAN_WORDS)
            0x10619410L,  // port-table HW lookup
            0x103230a4L,  // BDE init/setup
            0x1080c940L,  // soc_mem_generic_lookup
            0x10803190L,  // soc_mem family
            0x10820164L,  // soc_mem_entries
            0x10847ab4L,  // soc_reg32_get
            0x10848708L,  // soc_reg64_write_iterative
            0x1083bfbcL,  // soc_phyctrl_redirect_loopback_set
            0x107a213cL,  // _soc_field_value_fit
        };

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_deepest_primitives.c"))) {
            pw.println("/* Deepest chip-access primitives in switchd, decompiled */");
            pw.println();
            for (long addr : targets) {
                if (monitor.isCancelled()) break;
                Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addr);
                Function f = currentProgram.getFunctionManager().getFunctionAt(a);
                if (f == null) {
                    pw.printf("/* NO FUNCTION AT 0x%x */%n%n", addr);
                    continue;
                }
                long size = f.getBody().getNumAddresses();
                pw.printf("/* === %s @ 0x%x (size=%d) === */%n", f.getName(), addr, size);
                try {
                    DecompileResults res = decomp.decompileFunction(f, 60, monitor);
                    if (res.decompileCompleted()) {
                        pw.println(res.getDecompiledFunction().getC());
                    } else {
                        pw.println("/* DECOMP FAILED */");
                    }
                } catch (Exception ex) {
                    pw.println("/* DECOMP EXCEPTION: " + ex.getMessage() + " */");
                }
                pw.println();
            }
        }

        // Find functions that reference specific named registers (via the name table)
        // CMIC_CMC0_MIIM_CTRL is the marquee MIIM control reg
        String[] interestingRegNames = {
            "CMIC_CMC0_MIIM_CTRL",
            "CMIC_CMC0_MIIM_PARAM",
            "CMIC_CMC0_SCHAN_CTRL",
            "CMIC_CMC0_FSCHAN_OPCODE",
            "CX_WC_PLL_RESET",
            "CX_WC_PLL_CONTROL",
        };

        // Find each name in string data, then find xrefs to it
        Map<String, Set<Function>> regToFuncs = new HashMap<>();
        Memory mem = currentProgram.getMemory();
        ReferenceManager refMgr = currentProgram.getReferenceManager();

        for (String regName : interestingRegNames) {
            regToFuncs.put(regName, new HashSet<>());
        }

        DataIterator dataIt = currentProgram.getListing().getDefinedData(true);
        while (dataIt.hasNext() && !monitor.isCancelled()) {
            Data d = dataIt.next();
            if (!d.hasStringValue()) continue;
            String s = d.getDefaultValueRepresentation();
            // strip quotes
            String unq = s.replaceAll("^\"", "").replaceAll("\"$", "");
            for (String regName : interestingRegNames) {
                if (unq.equals(regName) || unq.startsWith(regName + "\\0")) {
                    // Get xrefs - reuse iterator pattern from prior script
                    java.util.Iterator<Reference> rit = refMgr.getReferencesTo(d.getAddress()).iterator();
                    while (rit.hasNext()) {
                        Reference r = rit.next();
                        Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                        if (f != null) regToFuncs.get(regName).add(f);
                    }
                }
            }
        }

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_named_reg_xrefs.txt"))) {
            pw.println("# Functions that reference specific BCM register names");
            pw.println();
            for (Map.Entry<String, Set<Function>> e : regToFuncs.entrySet()) {
                pw.println("==== " + e.getKey() + " ====");
                for (Function f : e.getValue()) {
                    pw.printf("  %-40s @ 0x%s (size=%d)%n",
                        f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
                }
                pw.println();
            }
        }

        // Find ioctl wrappers - look for functions calling the ioctl function via PLT
        // ioctl is usually imported via PLT entry
        Symbol ioctlSym = null;
        Iterable<Symbol> allSyms = currentProgram.getSymbolTable().getDefinedSymbols();
        for (Symbol s : allSyms) {
            if (s.getName().equals("ioctl") || s.getName().equals("ioctl@plt")) {
                ioctlSym = s;
                println("ioctl symbol: " + s.getName() + " @ " + s.getAddress());
                break;
            }
        }

        if (ioctlSym != null) {
            // Find xrefs to ioctl
            java.util.Iterator<Reference> rit = refMgr.getReferencesTo(ioctlSym.getAddress()).iterator();
            Set<Function> ioctlCallers = new HashSet<>();
            while (rit.hasNext()) {
                Reference r = rit.next();
                if (r.getReferenceType().isCall()) {
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    if (f != null) ioctlCallers.add(f);
                }
            }
            try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_ioctl_callers.txt"))) {
                pw.println("# Functions calling ioctl() - candidates for BDE ioctl wrappers");
                pw.printf("# %d callers found%n", ioctlCallers.size());
                pw.println();
                for (Function f : ioctlCallers) {
                    pw.printf("%-40s @ 0x%s (size=%d)%n",
                        f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
                }
            }
            println("ioctl callers: " + ioctlCallers.size());

            // Decompile the ioctl wrappers (likely small)
            try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_ioctl_wrappers_decomp.c"))) {
                pw.println("/* ioctl() callers in switchd (BDE wrappers) */");
                int decompiled = 0;
                for (Function f : ioctlCallers) {
                    if (decompiled >= 30) break;
                    long size = f.getBody().getNumAddresses();
                    if (size < 8 || size > 2048) continue;
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
        }

        decomp.dispose();
    }
}

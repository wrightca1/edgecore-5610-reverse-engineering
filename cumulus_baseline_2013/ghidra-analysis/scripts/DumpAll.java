// Dumps function listing, strings, and decompilation to text files.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.data.StringDataInstance;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;

import java.io.PrintWriter;
import java.io.FileWriter;

public class DumpAll extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        java.io.File dir = new java.io.File(outDir);
        if (!dir.exists()) dir.mkdirs();
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        // 1) Function listing
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_functions.txt"))) {
            pw.println("# Functions in " + currentProgram.getName());
            pw.println("# Address\tName\tSize\tParams");
            FunctionIterator funcs = currentProgram.getFunctionManager().getFunctions(true);
            int count = 0;
            while (funcs.hasNext() && !monitor.isCancelled()) {
                Function f = funcs.next();
                pw.printf("0x%-10s\t%s\t%d\t%d%n",
                    f.getEntryPoint().toString(),
                    f.getName(),
                    f.getBody().getNumAddresses(),
                    f.getParameterCount());
                count++;
            }
            pw.println("# Total: " + count + " functions");
            println("Functions: " + count);
        }

        // 2) String dump
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_strings.txt"))) {
            pw.println("# Strings in " + currentProgram.getName());
            DataIterator data = currentProgram.getListing().getDefinedData(true);
            int count = 0;
            while (data.hasNext() && !monitor.isCancelled()) {
                Data d = data.next();
                if (d.hasStringValue()) {
                    String s = d.getDefaultValueRepresentation();
                    if (s.length() > 2 && s.length() < 200) {
                        pw.printf("0x%-10s\t%s%n", d.getAddress().toString(), s);
                        count++;
                    }
                }
            }
            pw.println("# Total: " + count + " strings");
            println("Strings: " + count);
        }

        // 3) Symbol table
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_symbols.txt"))) {
            pw.println("# Symbols in " + currentProgram.getName());
            SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
            int count = 0;
            while (syms.hasNext() && !monitor.isCancelled()) {
                Symbol s = syms.next();
                pw.printf("0x%-10s\t%s\t%s%n",
                    s.getAddress().toString(),
                    s.getName(),
                    s.getSymbolType().toString());
                count++;
                if (count > 5000) break;
            }
            pw.println("# Total: " + count + " symbols");
            println("Symbols: " + count);
        }

        // 4) Decompile all non-trivial functions (limit per binary based on size)
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        int maxFuncs = 200;
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_decompile.c"))) {
            pw.println("/* Decompilation of " + currentProgram.getName() + " */");
            FunctionIterator funcs = currentProgram.getFunctionManager().getFunctions(true);
            int count = 0;
            while (funcs.hasNext() && count < maxFuncs && !monitor.isCancelled()) {
                Function f = funcs.next();
                if (f.isThunk() || f.isExternal()) continue;
                long size = f.getBody().getNumAddresses();
                if (size < 4 || size > 4096) continue; // skip tiny and huge
                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.println("/* === " + f.getName() + " @ " + f.getEntryPoint() + " (size=" + size + ") === */");
                        pw.println(res.getDecompiledFunction().getC());
                        pw.println();
                        count++;
                    }
                } catch (Exception e) {
                    pw.println("/* DECOMPILE FAILED: " + f.getName() + " - " + e.getMessage() + " */");
                }
            }
            pw.println("/* Decompiled " + count + " functions */");
            println("Decompiled: " + count);
        }
        decomp.dispose();
    }
}

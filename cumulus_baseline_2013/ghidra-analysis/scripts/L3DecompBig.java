// Decompile the big L3/netlink handlers
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.PrintWriter;
import java.io.FileWriter;

public class L3DecompBig extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        // Big functions we want
        long[] targets = {
            0x100142acL,   // route_handler (8004 bytes) - calls rtnl_route_alloc
            0x10013328L,   // route iterator (3280 bytes) - calls rtnl_route_get_dst
            0x100122d4L,   // neigh handler 1 (1900 bytes)
            0x1001acd4L,   // neigh handler 2 (916 bytes)
            0x1000d9d0L,   // neigh handler 3 (760 bytes)
            0x1000b7e8L,   // small neigh alloc helper (172 bytes)
            0x10012174L,   // neigh alloc helper (352 bytes)
            0x1001b068L,   // neigh alloc (460 bytes)
            0x1000a150L,   // netlink init (2680 bytes)
            0x10041b80L,   // netlink cb register (1436 bytes)
            0x1004102cL,   // netlink rx loop (176 bytes)
        };

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_l3_big_decomp.c"))) {
            pw.println("/* L3/netlink BIG functions decompiled */");
            pw.println();
            for (long addr : targets) {
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
                    DecompileResults res = decomp.decompileFunction(f, 120, monitor);
                    if (res.decompileCompleted()) {
                        pw.println(res.getDecompiledFunction().getC());
                    } else {
                        pw.println("/* DECOMP FAILED */");
                    }
                } catch (Exception ex) {
                    pw.println("/* EXCEPTION: " + ex.getMessage() + " */");
                }
                pw.println();
            }
        }
        decomp.dispose();
    }
}

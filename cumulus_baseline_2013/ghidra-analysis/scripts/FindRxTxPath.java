// Find the actual RX/TX paths: functions calling write()/read() PLT stubs
// and functions that look like packet processing.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Set;
import java.util.Map;
import java.util.TreeMap;

public class FindRxTxPath extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        ReferenceManager refMgr = currentProgram.getReferenceManager();

        // PLT stub addresses (16-byte trampolines we identified)
        long[] PLT = {
            0x11317b30L, // read
            0x11316d30L, // write
            0x11317000L, // writev
            0x11317c50L, // ioctl
        };
        String[] PLT_NAMES = {"read", "write", "writev", "ioctl"};

        // Find callers of each PLT stub
        Map<String, Set<Function>> callerMap = new HashMap<>();
        for (int i = 0; i < PLT.length; i++) {
            Set<Function> callers = new HashSet<>();
            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(PLT[i]);
            java.util.Iterator<Reference> rit = refMgr.getReferencesTo(a).iterator();
            while (rit.hasNext()) {
                Reference r = rit.next();
                if (r.getReferenceType().isCall()) {
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    if (f != null) callers.add(f);
                }
            }
            callerMap.put(PLT_NAMES[i], callers);
            println(PLT_NAMES[i] + "(): " + callers.size() + " callers");
        }

        // Also: callers of bcm_rx_register / bcm_rx_start / bcm_rx_unregister
        // (we know bcm_rx_unregister at 0x1042d410 from earlier; let's also find adjacent functions)
        Set<Function> rxRegCallers = new HashSet<>();
        Address rxUnreg = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x1042d410L);
        java.util.Iterator<Reference> rit = refMgr.getReferencesTo(rxUnreg).iterator();
        while (rit.hasNext()) {
            Reference r = rit.next();
            if (r.getReferenceType().isCall()) {
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                if (f != null) rxRegCallers.add(f);
            }
        }

        // Print summary + sample functions for each
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_rxtx_callers.txt"))) {
            pw.println("# write() callers (potential TX-out or TUN-write functions)");
            for (Function f : callerMap.get("write")) {
                pw.printf("  %-40s @ 0x%-10s (size=%d)%n",
                    f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            }
            pw.println();
            pw.println("# writev() callers");
            for (Function f : callerMap.get("writev")) {
                pw.printf("  %-40s @ 0x%-10s (size=%d)%n",
                    f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            }
            pw.println();
            pw.println("# read() callers (TX-in or TUN-read functions)");
            for (Function f : callerMap.get("read")) {
                pw.printf("  %-40s @ 0x%-10s (size=%d)%n",
                    f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            }
            pw.println();
            pw.println("# ioctl() callers - LUBDE / TUN setup");
            for (Function f : callerMap.get("ioctl")) {
                pw.printf("  %-40s @ 0x%-10s (size=%d)%n",
                    f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            }
            pw.println();
            pw.println("# bcm_rx_unregister callers (registration sites)");
            for (Function f : rxRegCallers) {
                pw.printf("  %-40s @ 0x%-10s (size=%d)%n",
                    f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
            }
        }

        // Decompile interesting candidates
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_rxtx_decomp.c"))) {
            pw.println("/* Packet RX/TX functions in switchd */");
            pw.println();

            // Decompile all writev callers (most likely the TX-out hotpath uses writev for scatter-gather)
            // Also write callers
            Set<Function> allInteresting = new HashSet<>();
            allInteresting.addAll(callerMap.get("writev"));
            allInteresting.addAll(callerMap.get("write"));
            allInteresting.addAll(callerMap.get("read"));
            allInteresting.addAll(rxRegCallers);

            int decompiled = 0;
            for (Function f : allInteresting) {
                if (decompiled >= 50) break;
                long size = f.getBody().getNumAddresses();
                if (size < 8 || size > 8192) continue;
                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.printf("/* === %s @ 0x%s (size=%d) === */%n",
                            f.getName(), f.getEntryPoint(), size);
                        pw.println(res.getDecompiledFunction().getC());
                        pw.println();
                        decompiled++;
                    }
                } catch (Exception ex) {}
            }
            println("Decompiled " + decompiled + " functions");
        }

        decomp.dispose();
    }
}

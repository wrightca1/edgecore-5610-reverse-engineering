// Decompile the RX callback FUN_101b8f54 and trace what it does
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.PrintWriter;
import java.io.FileWriter;

public class DecompileRxCallback extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        long[] targets = {
            0x101b8f54L,  // THE RX callback - registered via bcm_rx_unregister
            0x1042cce4L,  // bcm_rx_stop equivalent (called in cleanup)
            0x1002b48cL,  // packet-tag preprocessing (called from rx_to_tun)
            0x1002a910L,  // ring index advance (used in tun_to_tx_read)
            0x100461bcL,  // fd reset (on ENOTCONN)
            0x101b8b00L,  // try near FUN_101b8f54 - might be RX init
            0x1042d410L,  // bcm_rx_unregister itself
        };
        // Filter only valid ones
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_rx_callback_decomp.c"))) {
            pw.println("/* RX callback + related packet-handling functions */");
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
                if (size > 8192) {
                    pw.println("/* too large, skipping decomp */");
                    pw.println();
                    continue;
                }
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
        decomp.dispose();
    }
}

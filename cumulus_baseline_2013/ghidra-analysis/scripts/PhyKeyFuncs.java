// Decompile key PHY firmware functions identified by MMIO touch patterns
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.PrintWriter;
import java.io.FileWriter;

public class PhyKeyFuncs extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        // The interesting functions identified by MMIO touch patterns
        long[] targets = {
            0xACCEL,  // BIGGEST - 1453 bytes, touches all SerDes regs 0x100-0x1FB
            0xCEADL,  // 314 bytes - EQ adaptation loop (0x1F4-0x1FD tight)
            0xC4CCL,  // 648 bytes - 55 writes, configuration loader (0x94xx)
            0xC978L,  // 526 bytes - 77 writes - more 0x94xx config
            0xC1D7L,  // 838 bytes - mode change (low + high bank)
            0xBC17L,  // 466 bytes - 0x1F0-0x1F7 + 0x21C-0x21E + 0x9643
            0xD355L,  // 270 bytes - 0x1EB-0x1F7 (EQ loop variant)
            0xD463L,  // 256 bytes - writes 0x9434 (chip-ID echo)
            0xE301L,  // entry-point call target (firmware @0x8000 calls LCALL 0xE301 first)
            0xBE00L,  // entry-point second call (LCALL 0xBE00)
            0xE2CDL,  // entry-point third call (LCALL 0xE2CD)
            0xE3FDL,  // chip-ID setter
        };

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_key_funcs.c"))) {
            pw.println("/* PHY firmware key functions, decompiled */");
            pw.println("/* Note: 8051 decompilation is generally LOW QUALITY - prefer assembly */");
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
                pw.printf("/* === 0x%x (size=%d) === */%n", addr, size);
                if (size > 4096) {
                    pw.println("/* too large, skipping decomp - show asm separately */");
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

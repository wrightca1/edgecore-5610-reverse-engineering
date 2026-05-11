// Find the packet I/O glue in switchd: TUN ↔ BCM RX/TX paths
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Set;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

public class PacketIO extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        ReferenceManager refMgr = currentProgram.getReferenceManager();

        // Targets to look up
        String[] keyFunctions = {
            "bcm_rx_register", "bcm_rx_start", "bcm_rx_unregister",
            "bcm_tx", "bcm_rx_control_set", "bcm_rx_cosq_mapping_set",
            "read", "write", "writev", "readv",
            "ioctl"
        };

        // Find each function's address
        Map<String, Address> funcAddrs = new HashMap<>();
        SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
        while (syms.hasNext() && !monitor.isCancelled()) {
            Symbol s = syms.next();
            for (String fname : keyFunctions) {
                if (s.getName().equals(fname)) {
                    funcAddrs.put(fname, s.getAddress());
                }
            }
        }

        // Find string references to "tuntap" / "tun_fd" / "swp" / "rx_register" patterns
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_packet_io_clues.txt"))) {
            pw.println("# Packet I/O glue function clues");
            pw.println();

            // 1) Functions that reference tuntap.c or tuntap-related strings
            String[] hwKeywords = {
                "tuntap.c", "tun_fd", "TUNSETIFF", "knet", "punt",
                "swp%d", "RX from", "TX to", "linkscan",
                "_tx_send", "_rx_callback", "pkt_io", "packet_io",
                "_rx_register", "_tx_init", "TUN_", "TAP_", "/dev/net/tun"
            };

            Pattern tuntapPat = Pattern.compile("tuntap|tun_fd|TUNSETIFF|knet|punt|_rx_callback|_tx_send|pkt_io|packet_io");
            DataIterator dataIt = currentProgram.getListing().getDefinedData(true);
            int found = 0;
            while (dataIt.hasNext() && found < 200 && !monitor.isCancelled()) {
                Data d = dataIt.next();
                if (!d.hasStringValue()) continue;
                String s = d.getDefaultValueRepresentation();
                if (s.length() < 6 || s.length() > 200) continue;
                if (tuntapPat.matcher(s).find()) {
                    java.util.Iterator<Reference> rit = refMgr.getReferencesTo(d.getAddress()).iterator();
                    while (rit.hasNext()) {
                        Reference r = rit.next();
                        Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                        if (f != null) {
                            pw.printf("string: %-60s\n    @ 0x%-10s used in func %s (0x%s)\n",
                                s.substring(0, Math.min(s.length(), 60)),
                                d.getAddress().toString(),
                                f.getName(),
                                f.getEntryPoint().toString());
                            found++;
                        }
                    }
                }
            }
            pw.println();
            pw.println("# Total: " + found + " packet-io string references");
        }

        // Decompile key functions if they exist
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_packet_io_decomp.c"))) {
            pw.println("/* Packet I/O functions in switchd */");
            pw.println();

            // Decompile target functions
            for (String fname : keyFunctions) {
                Address a = funcAddrs.get(fname);
                if (a == null) continue;
                Function f = currentProgram.getFunctionManager().getFunctionAt(a);
                if (f == null) continue;
                long size = f.getBody().getNumAddresses();
                if (size < 4) continue;
                pw.printf("/* === %s @ 0x%s (size=%d) === */%n", fname, a, size);
                if (size > 4096) {
                    pw.println("/* size too large to decompile in this pass */");
                    pw.println();
                    continue;
                }
                try {
                    DecompileResults res = decomp.decompileFunction(f, 30, monitor);
                    if (res.decompileCompleted()) {
                        pw.println(res.getDecompiledFunction().getC());
                    }
                } catch (Exception ex) {}
                pw.println();
            }

            // Also decompile FUN_10008ae8 (TUN device creator) and its callers
            Address tunCreator = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(0x10008ae8L);
            Function tunF = currentProgram.getFunctionManager().getFunctionAt(tunCreator);
            if (tunF != null) {
                pw.printf("/* === TUN creator (FUN_10008ae8) and callers === */%n");
                DecompileResults res = decomp.decompileFunction(tunF, 30, monitor);
                if (res.decompileCompleted()) pw.println(res.getDecompiledFunction().getC());
                pw.println();
                // Find callers
                java.util.Iterator<Reference> rit = refMgr.getReferencesTo(tunCreator).iterator();
                Set<Function> callers = new HashSet<>();
                while (rit.hasNext()) {
                    Reference r = rit.next();
                    if (r.getReferenceType().isCall()) {
                        Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                        if (f != null) callers.add(f);
                    }
                }
                pw.printf("/* %d callers of TUN creator */%n", callers.size());
                for (Function f : callers) {
                    if (f.getBody().getNumAddresses() > 4096) continue;
                    pw.printf("/* --- caller: %s @ 0x%s (size=%d) --- */%n",
                              f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
                    try {
                        DecompileResults res2 = decomp.decompileFunction(f, 30, monitor);
                        if (res2.decompileCompleted()) pw.println(res2.getDecompiledFunction().getC());
                    } catch (Exception ex) {}
                    pw.println();
                }
            }
        }

        decomp.dispose();
        println("Output: " + prog + "_packet_io_decomp.c, " + prog + "_packet_io_clues.txt");
    }
}

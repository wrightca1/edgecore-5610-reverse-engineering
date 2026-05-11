// Find switchd's netlink → BCM L3 programming path
// 1) Functions calling bcm_l3_route_add / bcm_l3_host_add / bcm_l3_egress_create
// 2) Netlink listeners (callers of nl_recvmsgs / nl_socket_modify_cb)
// 3) Decompile the bridge functions
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
import java.util.regex.Pattern;

public class L3RouteProg extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        ReferenceManager refMgr = currentProgram.getReferenceManager();

        // Find these L3 + netlink functions by name (some are labeled, others PLT stubs)
        String[] targetSyms = {
            "bcm_l3_route_add", "bcm_l3_route_delete", "bcm_l3_route_traverse",
            "bcm_l3_host_add", "bcm_l3_host_delete", "bcm_l3_host_traverse",
            "bcm_l3_intf_create", "bcm_l3_intf_destroy",
            "bcm_l3_egress_create", "bcm_l3_egress_destroy",
            "bcm_l3_egress_multipath_create",
            "nl_recvmsgs", "nl_recvmsgs_default", "nl_recvmsgs_report",
            "nl_socket_modify_cb", "nl_send_auto", "nl_socket_alloc",
            "nl_cache_alloc", "rtnl_route_alloc", "rtnl_route_get_dst",
            "rtnl_neigh_alloc", "rtnl_neigh_get_dst",
            "rtnl_link_get", "rtnl_route_iterate",
        };

        Map<String, Address> symAddrs = new HashMap<>();
        SymbolIterator syms = currentProgram.getSymbolTable().getDefinedSymbols();
        while (syms.hasNext() && !monitor.isCancelled()) {
            Symbol s = syms.next();
            for (String name : targetSyms) {
                if (s.getName().equals(name)) {
                    symAddrs.put(name, s.getAddress());
                    break;
                }
            }
        }
        println("Symbols found: " + symAddrs.size() + " of " + targetSyms.length);
        for (Map.Entry<String, Address> e : symAddrs.entrySet()) {
            println("  " + e.getKey() + " @ " + e.getValue());
        }

        // Find callers of each (and their callers recursively up 2 levels)
        Map<String, Set<Function>> callerMap = new HashMap<>();
        for (Map.Entry<String, Address> e : symAddrs.entrySet()) {
            Set<Function> callers = new HashSet<>();
            java.util.Iterator<Reference> rit = refMgr.getReferencesTo(e.getValue()).iterator();
            while (rit.hasNext()) {
                Reference r = rit.next();
                if (r.getReferenceType().isCall()) {
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    if (f != null) callers.add(f);
                }
            }
            callerMap.put(e.getKey(), callers);
        }

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_l3_route_callers.txt"))) {
            pw.println("# L3 / Netlink function callers");
            pw.println();
            for (Map.Entry<String, Set<Function>> e : callerMap.entrySet()) {
                pw.println("==== " + e.getKey() + " (" + e.getValue().size() + " callers) ====");
                for (Function f : e.getValue()) {
                    pw.printf("  %-40s @ 0x%s (size=%d)%n",
                        f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses());
                }
                pw.println();
            }
        }

        // Decompile the callers
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_l3_decomp.c"))) {
            pw.println("/* L3 route programming + netlink bridge functions */");
            pw.println();
            Set<Function> done = new HashSet<>();
            int decompiled = 0;
            for (Set<Function> set : callerMap.values()) {
                for (Function f : set) {
                    if (done.contains(f)) continue;
                    done.add(f);
                    long size = f.getBody().getNumAddresses();
                    if (size < 8 || size > 4096) continue;
                    if (decompiled >= 40) break;
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
            }
            println("Decompiled " + decompiled + " functions");
        }

        // Also look for strings related to netlink message types
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_netlink_strings.txt"))) {
            pw.println("# Strings related to netlink / route processing");
            pw.println();
            String[] keys = {"RTM_", "rtnl_", "route", "neigh", "nexthop", "nlmsg",
                            "netlink", "link_update", "addr_update",
                            "route.c", "neigh.c", "rib.c", "rtnetlink",
                            "RTM_NEWROUTE", "RTM_DELROUTE", "RTM_NEWNEIGH"};
            DataIterator dataIt = currentProgram.getListing().getDefinedData(true);
            int found = 0;
            while (dataIt.hasNext() && found < 300 && !monitor.isCancelled()) {
                Data d = dataIt.next();
                if (!d.hasStringValue()) continue;
                String s = d.getDefaultValueRepresentation();
                if (s.length() < 5 || s.length() > 200) continue;
                for (String k : keys) {
                    if (s.contains(k)) {
                        java.util.Iterator<Reference> rit = refMgr.getReferencesTo(d.getAddress()).iterator();
                        while (rit.hasNext()) {
                            Reference r = rit.next();
                            Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                            if (f != null) {
                                pw.printf("%-50s @ 0x%-10s used in %s @ 0x%s%n",
                                    s.substring(0, Math.min(s.length(), 50)),
                                    d.getAddress(), f.getName(), f.getEntryPoint());
                                found++;
                            }
                        }
                        break;
                    }
                }
            }
            pw.println();
            pw.println("# Total: " + found);
        }
        decomp.dispose();
    }
}

// For each "...bcm_FUNC failed..." log string, find xrefs and label the
// function called just before the log call. That's the actual BCM SDK API.
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SymbolType;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.listing.FlowOverride;
import ghidra.program.model.symbol.RefType;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class LabelBcmApiFunctions extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";
        String prog = currentProgram.getName().replaceAll("[/\\\\]", "_");

        ReferenceManager refMgr = currentProgram.getReferenceManager();
        SymbolTable symTab = currentProgram.getSymbolTable();

        Pattern bcmName = Pattern.compile("(bcm_\\w+|hal_bcm_\\w+)");

        Map<String, Set<Address>> apiCallSites = new HashMap<>();
        Map<String, Address> apiCallTargets = new HashMap<>();
        Set<Address> labeledFuncs = new HashSet<>();
        int stringsExamined = 0, callsLabeled = 0;

        DataIterator data = currentProgram.getListing().getDefinedData(true);
        while (data.hasNext() && !monitor.isCancelled()) {
            Data d = data.next();
            if (!d.hasStringValue()) continue;
            String s = d.getDefaultValueRepresentation();
            if (s.length() < 10 || s.length() > 200) continue;

            // Extract bcm_xxx function name from the log string
            Matcher m = bcmName.matcher(s);
            if (!m.find()) continue;
            String apiName = m.group(1);
            // Heuristic: only care about strings that say "<name> failed"
            if (!s.contains("failed")) continue;
            stringsExamined++;

            // Find xrefs to this string
            java.util.Iterator<Reference> refIter = refMgr.getReferencesTo(d.getAddress()).iterator();
            while (refIter.hasNext()) {
                Reference r = refIter.next();
                Address callerAddr = r.getFromAddress();
                Function callerFunc = currentProgram.getFunctionManager().getFunctionContaining(callerAddr);
                if (callerFunc == null) continue;

                // Walk BACKWARD from callerAddr looking for the most recent CALL instruction
                Address scan = callerAddr;
                int back = 0;
                while (back < 50 && scan != null && !monitor.isCancelled()) {
                    Instruction ins = currentProgram.getListing().getInstructionAt(scan);
                    if (ins != null) {
                        String mnem = ins.getMnemonicString();
                        // PowerPC: bl = branch and link (call)
                        if (mnem.equals("bl") || mnem.equals("bla")) {
                            // Get target of the branch
                            Reference[] callRefs = ins.getReferencesFrom();
                            for (Reference cr : callRefs) {
                                if (cr.getReferenceType().isCall()) {
                                    Address target = cr.getToAddress();
                                    apiCallSites.computeIfAbsent(apiName, k -> new HashSet<>()).add(target);
                                    apiCallTargets.put(apiName, target);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    try {
                        Instruction prev = currentProgram.getListing().getInstructionBefore(scan);
                        if (prev == null) break;
                        scan = prev.getAddress();
                    } catch (Exception ex) { break; }
                    back++;
                }
            }
        }

        // Label each found function (skip duplicates / disagreements)
        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/" + prog + "_bcm_api_resolved.txt"))) {
            pw.println("# Resolved BCM SDK API → switchd address");
            pw.println("# (each is the function called immediately before a CRIT log mentioning its name)");
            pw.println();
            pw.printf("# %-40s %-12s   %s%n", "API name", "Switchd addr", "Targets seen");
            pw.println();
            for (Map.Entry<String, Set<Address>> e : apiCallSites.entrySet()) {
                Set<Address> targets = e.getValue();
                String apiName = e.getKey();
                if (targets.size() == 1) {
                    Address target = targets.iterator().next();
                    pw.printf("%-40s 0x%-10s   (unique)%n", apiName, target.toString());
                    // Apply label (use createLabel for free-floating, or addLabel for function)
                    try {
                        Function f = currentProgram.getFunctionManager().getFunctionAt(target);
                        if (f != null) {
                            if (!f.getName().equals(apiName)) {
                                f.setName(apiName, SourceType.ANALYSIS);
                                callsLabeled++;
                                labeledFuncs.add(target);
                            }
                        } else {
                            // Try to create function at this address
                            createFunction(target, apiName);
                            callsLabeled++;
                            labeledFuncs.add(target);
                        }
                    } catch (Exception ex) {
                        pw.println("  // label failed: " + ex.getMessage());
                    }
                } else {
                    pw.printf("%-40s %s   (AMBIGUOUS — %d distinct targets)%n",
                              apiName, "----", targets.size());
                    for (Address t : targets) {
                        pw.printf("    candidate: 0x%s%n", t.toString());
                    }
                }
            }
            pw.println();
            pw.printf("# Total: %d strings examined, %d unique API targets labeled%n",
                      stringsExamined, callsLabeled);
        }

        println("Examined: " + stringsExamined + " strings");
        println("Labeled : " + callsLabeled + " BCM SDK functions in switchd");
    }
}

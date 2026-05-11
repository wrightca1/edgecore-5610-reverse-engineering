// Walk all MOVX @DPTR instructions in the PHY firmware to map MMIO accesses
//@category Analysis

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.address.Address;
import ghidra.program.model.scalar.Scalar;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.Map;

public class MapPhyMmio extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getProperty("user.home") + "/edgecore/edgecore-5610-reverse-engineering/cumulus_baseline_2013/ghidra-analysis";

        // Walk all instructions, track DPTR value
        // Pattern: MOV DPTR, #imm16 then MOVX @DPTR, A (write) or MOVX A, @DPTR (read)
        // Also INC DPTR which means we touch DPTR+1 too
        TreeMap<Integer, int[]> mmio = new TreeMap<>();  // addr -> [reads, writes, last_seen_pc]

        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        int lastDPTR = -1;
        int count = 0;
        int totalInst = 0;
        while (it.hasNext() && !monitor.isCancelled()) {
            Instruction ins = it.next();
            totalInst++;
            String mnem = ins.getMnemonicString();

            if (mnem.equals("MOV")) {
                // Check if this is "MOV DPTR, #imm"
                String operands = ins.toString();
                if (operands.contains("DPTR") && operands.contains("#")) {
                    Object[] objs = ins.getOpObjects(ins.getNumOperands() - 1);
                    if (objs.length > 0 && objs[0] instanceof Scalar) {
                        lastDPTR = (int) ((Scalar) objs[0]).getUnsignedValue();
                    }
                }
            } else if (mnem.equals("MOVX")) {
                if (lastDPTR >= 0) {
                    String operands = ins.toString();
                    boolean isWrite = operands.contains("@DPTR,A");
                    boolean isRead = operands.contains("A,@DPTR");
                    int[] entry = mmio.computeIfAbsent(lastDPTR, k -> new int[3]);
                    if (isWrite) entry[1]++;
                    if (isRead) entry[0]++;
                    entry[2] = (int) ins.getAddress().getOffset();
                    count++;
                }
            } else if (mnem.equals("INC")) {
                String operands = ins.toString();
                if (operands.contains("DPTR") && lastDPTR >= 0) {
                    lastDPTR = (lastDPTR + 1) & 0xFFFF;
                }
            } else if (mnem.equals("LCALL") || mnem.equals("ACALL") ||
                       mnem.equals("LJMP") || mnem.equals("AJMP") ||
                       mnem.equals("SJMP")) {
                lastDPTR = -1;  // can't track across calls
            }
        }

        try (PrintWriter pw = new PrintWriter(new FileWriter(outDir + "/phy_mmio_map.txt"))) {
            pw.println("# PHY firmware MMIO access map (from " + currentProgram.getName() + ")");
            pw.printf("# Walked %d instructions, found %d MMIO accesses across %d unique addresses%n",
                      totalInst, count, mmio.size());
            pw.println();
            pw.printf("# %-8s %8s %8s   %-15s%n", "PHY_REG", "READS", "WRITES", "LAST_PC");
            pw.println("# -----------------------------------------------------------");
            for (Map.Entry<Integer, int[]> e : mmio.entrySet()) {
                int addr = e.getKey();
                int[] s = e.getValue();
                pw.printf("0x%-8x %8d %8d   0x%04x%n", addr, s[0], s[1], s[2]);
            }
            pw.println();
            pw.println("# === Read-only registers (likely status/data) ===");
            for (Map.Entry<Integer, int[]> e : mmio.entrySet()) {
                int[] s = e.getValue();
                if (s[0] > 0 && s[1] == 0) {
                    pw.printf("0x%04x  R-O  reads=%d%n", e.getKey(), s[0]);
                }
            }
            pw.println();
            pw.println("# === Write-only registers (likely config/init) ===");
            for (Map.Entry<Integer, int[]> e : mmio.entrySet()) {
                int[] s = e.getValue();
                if (s[1] > 0 && s[0] == 0) {
                    pw.printf("0x%04x  W-O  writes=%d%n", e.getKey(), s[1]);
                }
            }
            pw.println();
            pw.println("# === Read-Write registers (likely control) ===");
            for (Map.Entry<Integer, int[]> e : mmio.entrySet()) {
                int[] s = e.getValue();
                if (s[0] > 0 && s[1] > 0) {
                    pw.printf("0x%04x  R/W  reads=%d writes=%d%n", e.getKey(), s[0], s[1]);
                }
            }
        }

        println("Found " + mmio.size() + " unique MMIO addresses (" + count + " accesses)");
    }
}

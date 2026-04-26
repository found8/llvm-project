//
// Created by marvinli on 2025/12/21.
//

#include "RISCXInstPrinter.h"
#include "RISCXRegisterInfo.h"
// #include "llvm/MC/MCInst.h"
#include "RISCXMCTargetDesc.h"
#include "llvm/MC/MCAsmInfo.h"

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "RISCXGenAsmWriter.inc"

void RISCXInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) {
  OS << getRegisterName(Reg);
}

void RISCXInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                StringRef Annot, const MCSubtargetInfo &STI,
                                raw_ostream &O) {
  if (!printAliasInstr(MI, Address, O))
    printInstruction(MI, Address, O);

  printAnnotation(O, Annot);
}

void RISCXInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                   raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(OpNo);
  if (MO.isReg()) {
    printRegName(O, MO.getReg());
    return;
  }

  if (MO.isImm()) {
    printImmediate(MI, OpNo, O);
    return;
  }

  assert(MO.isExpr() && "Unknown operand kind in printOperand");
  MAI.printExpr(O, *MO.getExpr());
}

void RISCXInstPrinter::printImmediate(const MCInst *MI, unsigned opNum,
                                     raw_ostream &O) {
  const MCOperand &MO = MI->getOperand(opNum);
  if (MO.isImm())
    O << MO.getImm();
  else if (MO.isExpr()) {
    MAI.printExpr(O, *MO.getExpr());
  } else
    llvm_unreachable("Unknown immediate kind");
}

void RISCXInstPrinter::printMemOperand(const MCInst *MI, unsigned int opNum,
                                       raw_ostream &O) {
  printOperand(MI, opNum+1, O);
  O << "(";
  printOperand(MI, opNum, O);
  O << ")";
}

void llvm::RISCXInstPrinter::printPtrOperand(const MCInst *MI, unsigned opNum,
                                             raw_ostream &O) {
  printOperand(MI, opNum, O);
  O << ", ";
  printOperand(MI, opNum+1, O);
}

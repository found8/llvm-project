//
// Created by 蔡鹏 on 2024/12/1.
//

#include "OneAsmPrinter.h"

#include "MCTargetDesc/OneMCExpr.h"
#include "MCTargetDesc/OneMCTargetDesc.h"
#include "TargetInfo/OneTargetInfo.h"

#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define PRINT_ALIAS_INSTR
#include "OneGenMCPseudoLowering.inc"

bool OneAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  AsmPrinter::runOnMachineFunction(MF);
  return true;
}

void OneAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Do any auto-generated pseudo lowerings.
  if (MCInst OutInst; lowerPseudoInstExpansion(MI, OutInst)) {
    EmitToStreamer(*OutStreamer, OutInst);
    return;
  }

  MCInst TmpInst;
  lowerToMCInst(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

void OneAsmPrinter::lowerToMCInst(const MachineInstr *MI, MCInst &Out) {
  Out.setOpcode(MI->getOpcode());

  unsigned int Opcode = MI->getOpcode();
  int isBranch = false;
  if (Opcode == One::BLT || Opcode == One::BEQ || Opcode == One::BNE ||
      Opcode == One::BGE) {
    isBranch = true;
  }

  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp = LowerOperand(MO, isBranch);
    if (MCOp.isValid())
      Out.addOperand(MCOp);
  }
}

MCOperand OneAsmPrinter::lowerSymbolOperand(const MachineOperand &MO,
                                            bool isBranch) const {
  // auto *symbol = getSymbol(MO.getGlobal());
  // const auto &expr = MCSymbolRefExpr::create(symbol,
  // MCSymbolRefExpr::VK_None, OutContext); MCOp = MCOperand::createExpr(expr);
  OneMCExpr::Kind kind = OneMCExpr::NONE;
  const MCSymbol *symbol = nullptr;
  switch (MO.getTargetFlags()) {
  case OneMCExpr::HI:
    kind = OneMCExpr::HI;
    break;
  case OneMCExpr::LO:
    kind = OneMCExpr::LO;
    break;
  default:
    break;
  }
  if (MO.getType() == MachineOperand::MO_MachineBasicBlock) {
    if (!isBranch) {
      kind = OneMCExpr::JAL;
    } else {
      kind = OneMCExpr::Branch;
    }
    symbol = MO.getMBB()->getSymbol();
  } else if (MO.getType() == MachineOperand::MO_ExternalSymbol) {
    symbol = GetExternalSymbolSymbol(MO.getSymbolName());
  } else {
    symbol = getSymbol(MO.getGlobal());
  }
  const MCExpr *Expr = MCSymbolRefExpr::create(symbol, OutContext);
  Expr = new OneMCExpr(kind, Expr);
  return MCOperand::createExpr(Expr);
}

bool OneAsmPrinter::lowerOperand(const MachineOperand &MO,
                                 MCOperand &MCOp) const {
  MCOp = LowerOperand(MO, false);
  return true;
}

MCOperand OneAsmPrinter::LowerOperand(const MachineOperand &MO,
                                      bool isBranch) const {
  switch (MO.getType()) {
  case MachineOperand::MO_Register: {
    return MCOperand::createReg(MO.getReg());
  }
  case MachineOperand::MO_Immediate: {
    return MCOperand::createImm(MO.getImm());
  }
  case MachineOperand::MO_GlobalAddress:
  case MachineOperand::MO_ExternalSymbol:
  case MachineOperand::MO_MachineBasicBlock: {
    return lowerSymbolOperand(MO, isBranch);
  }
  case MachineOperand::MO_RegisterMask: {
    /// Ignore
    break;
  }
  default:
    break;
  }
  return MCOperand();
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOneAsmPrinter() {
  RegisterAsmPrinter<OneAsmPrinter> X(getTheOneTarget());
}

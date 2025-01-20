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

  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;
    switch (MO.getType()) {
    case MachineOperand::MO_Register: {
      // Ignore all implicit register operands.
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    }
    case MachineOperand::MO_Immediate: {
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    }
    case MachineOperand::MO_GlobalAddress:
    case MachineOperand::MO_MachineBasicBlock: {
      MCOp = lowerSymbolOperand(MO);
      break;
    }
    case MachineOperand::MO_RegisterMask: {
      /// Ignore
      break;
    }
    default:
      llvm_unreachable("unknown operand type");
    }

    Out.addOperand(MCOp);
  }
}

MCOperand OneAsmPrinter::lowerSymbolOperand(const MachineOperand &MO) const {
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
    symbol = MO.getMBB()->getSymbol();
  }else {
    symbol = getSymbol(MO.getGlobal());
  }
  const MCExpr *Expr = MCSymbolRefExpr::create(symbol, OutContext);
  Expr = new OneMCExpr(kind, Expr);
  return MCOperand::createExpr(Expr);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOneAsmPrinter() {
  RegisterAsmPrinter<OneAsmPrinter> X(getTheOneTarget());
}

//
// Created by 蔡鹏 on 2024/12/1.
//

#include "OneAsmPrinter.h"
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
    default:
      llvm_unreachable("unknown operand type");
    }

    Out.addOperand(MCOp);
  }
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeOneAsmPrinter() {
  RegisterAsmPrinter<OneAsmPrinter> X(getTheOneTarget());
}

//
// Created by marvinli on 2025/12/21.
//

#include "RISCXAsmPrinter.h"
// #include "llvm/MC/MCInst.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "TargetInfo/RISCXTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#include "RISCXGenMCPseudoLowering.inc"

// RISCXAsmPrinter::RISCXAsmPrinter() : RISCXGenInstrInfo() {
//   ;
// }

bool RISCXAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  // MMFI = MF.getInfo<RISCXMachineFunctionInfo>();
  // MCInstLowering = std::make_unique<M68kMCInstLower>(MF, *this);
  AsmPrinter::runOnMachineFunction(MF);
  return true;
}

void RISCXAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Do any auto-generated pseudo lowerings.
  if (MCInst OutInst; lowerPseudoInstExpansion(MI, OutInst)) {
    EmitToStreamer(*OutStreamer, OutInst);
  }

  MCInst TmpInst;
  lowerToMCInst(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

void RISCXAsmPrinter::lowerToMCInst(const MachineInstr *MI, MCInst &OutMI) {
  OutMI.setOpcode(MI->getOpcode());

  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;
    switch (MO.getType())
    {
    case MachineOperand::MO_Register:
        // Ignore all implicit register operands.
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    case MachineOperand::MO_Immediate:
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    default:
      llvm_unreachable("unknow operand type");
    }
    OutMI.addOperand(MCOp);
  }
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCXAsmPrinter() {
  RegisterAsmPrinter<RISCXAsmPrinter> X(getTheRISCXTarget());
}

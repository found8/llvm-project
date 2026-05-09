//
// Created by marvinli on 2025/12/21.
//

#ifndef LLVM_RISCXASMPRINTER_H
#define LLVM_RISCXASMPRINTER_H

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "RISCXTargetMachine.h"

// #define GET_INSTRINFO_HEADER
// #include "RISCXGenInstrInfo.inc"

namespace llvm {
class RISCXSubtarget;
// class RISCXTargetMachine;

class RISCXAsmPrinter : public AsmPrinter {
public:
  explicit RISCXAsmPrinter(TargetMachine &TM,
                          std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {
    Subtarget = static_cast<RISCXTargetMachine &>(TM).getSubtargetImpl();
  }

  StringRef getPassName() const override { return "RISCX Assembly Printer"; }
  virtual bool runOnMachineFunction(MachineFunction &MF) override;
  void emitInstruction(const MachineInstr *MI) override;
  bool lowerOperand(const MachineOperand &MO, MCOperand &MCOp);

  const RISCXSubtarget *Subtarget;

private:
  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
  void lowerToMCInst(const MachineInstr *MI, MCInst &Out);
  MCOperand lowerSymbolOperand(const MachineOperand &MO);
};
} // namespace llvm

#endif // LLVM_RISCXASMPRINTER_H

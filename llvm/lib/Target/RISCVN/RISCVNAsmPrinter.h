#ifndef LLVM_LIB_TARGET_RISCVN_ARMASMPRINTER_H
#define LLVM_LIB_TARGET_RISCVN_ARMASMPRINTER_H

#include "RISCVNMCInstLower.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
namespace llvm {

class LLVM_LIBRARY_VISIBILITY RISCVNAsmPrinter : public AsmPrinter {
  RISCVNMCInstLower MCInstLowering;

public:
  explicit RISCVNAsmPrinter(TargetMachine &TM,
                            std::unique_ptr<MCStreamer> Streamer);

  StringRef getPassName() const override { return "RISCVN Assembly Printer"; }

  void emitInstruction(const MachineInstr *MI) override;
private:
  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
};
} // end namespace llvm

#endif
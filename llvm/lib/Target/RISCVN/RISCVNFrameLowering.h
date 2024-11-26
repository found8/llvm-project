#ifndef LLVM_LIB_TARGET_RISCVN_RISCVNFRAMELOWERING_H
#define LLVM_LIB_TARGET_RISCVN_RISCVNFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class RISCVNSubtarget;

class RISCVNFrameLowering : public TargetFrameLowering {
  const RISCVNSubtarget &STI;

public:
  explicit RISCVNFrameLowering(const RISCVNSubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0,
                            Align(4)),
        STI(STI) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  bool hasFPImpl(const MachineFunction &MF) const override;
};
} // namespace llvm

#endif 
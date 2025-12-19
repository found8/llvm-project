//
// Created by marvinli on 2025/12/19.
//

#ifndef LLVM_RISCXFRAMELOWERING_H
#define LLVM_RISCXFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class RISCXSubtarget;

class RISCXFrameLowering : public TargetFrameLowering {
  const RISCXSubtarget &STI;

public:
  explicit RISCXFrameLowering(const RISCXSubtarget &STI)
      : TargetFrameLowering(StackGrowsDown, Align(4), 0, Align(4)), STI(STI) {
    ;
  }

  // virtual function
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

protected:
  bool hasFPImpl(const MachineFunction &MF) const override;
};
}

#endif // LLVM_RISCXFRAMELOWERING_H

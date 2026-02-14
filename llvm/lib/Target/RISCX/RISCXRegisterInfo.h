//
// Created by marvinli on 2025/12/18.
//

#ifndef LLVM_RISCXREGISTERINFO_H
#define LLVM_RISCXREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "RISCXGenRegisterInfo.inc"

namespace llvm {
class RISCXSubtarget;

class RISCXRegisterInfo : public RISCXGenRegisterInfo {
  const RISCXSubtarget &STI;
public:
  RISCXRegisterInfo(const RISCXSubtarget &STI);

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID id) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  Register getFrameRegister(const MachineFunction &MF) const override;
};
} // namespace llvm

#endif // LLVM_RISCXREGISTERINFO_H

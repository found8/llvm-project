//
// Created by marvinli on 2025/12/18.
//

#ifndef LLVM_RISCXINSTRINFO_H
#define LLVM_RISCXINSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RISCXGenInstrInfo.inc"

namespace llvm {

class RISCXInstrInfo : public RISCXGenInstrInfo {
public:
  explicit RISCXInstrInfo();

  // handle callee
  void storeRegToStackSlot(
      llvm::MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
      llvm::Register SrcReg, bool isKill, int FrameIndex,
      const llvm::TargetRegisterClass *RC, const llvm::TargetRegisterInfo *TRI,
      llvm::Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;
  void loadRegFromStackSlot(
      llvm::MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
      llvm::Register DestReg, int FrameIndex,
      const llvm::TargetRegisterClass *RC, const llvm::TargetRegisterInfo *TRI,
      llvm::Register VReg,
      MachineInstr::MIFlag Flags = MachineInstr::NoFlags) const override;
  void copyPhysReg(llvm::MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const llvm::DebugLoc &DL, llvm::Register DestReg,
                   llvm::Register SrcReg, bool KillSrc,
                   bool RenamableDest = false,
                   bool RenamableSrc = false) const override;
};
} // namespace llvm

#endif // LLVM_RISCXINSTRINFO_H

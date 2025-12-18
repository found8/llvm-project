//
// Created by marvinli on 2025/12/18.
//

#include "RISCXRegisterInfo.h"
#include "RISCXSubtarget.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "llvm/ADT/BitVector.h"
//#include "llvm/CodeGen/MachineFunction.h"

#define GET_REGINFO_TARGET_DESC
#include "RISCXGenRegisterInfo.inc"

using namespace llvm;

RISCXRegisterInfo::RISCXRegisterInfo() : RISCXGenRegisterInfo(RISCX::X1){
  ;
}

const MCPhysReg *RISCXRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  static const MCPhysReg CalleeSavedRegs[] = {RISCX::X2, 0};
  return CalleeSavedRegs;
}

BitVector RISCXRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(RISCX::X0);
  return Reserved;
}

bool RISCXRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                         unsigned FIOperandNum,
                         RegScavenger *RS) const {
  return false;
}

Register RISCXRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return RISCX::X2;
}

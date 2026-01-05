//
// Created by marvinli on 2025/12/18.
//

#include "RISCXRegisterInfo.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "RISCX.h"
#include "RISCXSubtarget.h"
#include "llvm/ADT/BitVector.h"
// #include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "RISCXGenRegisterInfo.inc"

using namespace llvm;

RISCXRegisterInfo::RISCXRegisterInfo(const RISCXSubtarget &STI)
    : RISCXGenRegisterInfo(RISCX::RA), STI(STI) {
  ;
}

const MCPhysReg *
RISCXRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CC_CSR_SaveList;
}

BitVector RISCXRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(RISCX::ZERO);
  Reserved.set(RISCX::RA);
  Reserved.set(RISCX::SP);
  return Reserved;
}

bool RISCXRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  /*
  llvm::errs() << "1------------------------\n";
  II->dump();
  llvm::errs() << "2------------------------\n";
  //*/

  MachineInstr &MI = *II;
  /*
  for (const auto &OP: MI.operands()) {
    llvm::errs() << OP.getType() << ": " << OP << "\n";
  }
  //*/

  uint I = FIOperandNum;
  /*
  while (!MI.getOperand(I).isFI()) {
    I++;
    assert(I < MI.getNumOperands());
  }
  //*/

  /*
  llvm::errs() << "3------------------------\n";
  MI.getOperand(I).dump();
  llvm::errs() << "4------------------------\n";
  //*/

  const int FI = MI.getOperand(I).getIndex();

  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  int64_t Offset = MFI.getObjectOffset(FI);
  uint64_t STACKSIZE = ROUND_UP(MFI.getStackSize(), STI.getFrameLowering()->getStackAlignment());
  Offset += static_cast<int64_t>(STACKSIZE);

  MI.getOperand(I).ChangeToRegister(RISCX::SP, false);
  MI.getOperand(I + 1).ChangeToImmediate(Offset);

  return false;
}

Register RISCXRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return RISCX::SP;
}

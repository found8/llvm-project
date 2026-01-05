//
// Created by marvinli on 2025/12/19.
//

#include "RISCXFrameLowering.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "RISCX.h"
#include "RISCXSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

void RISCXFrameLowering::emitPrologue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.begin();

  const TargetInstrInfo &TII = *STI.getInstrInfo();
  int STACKSIZE = computeStackSize(MF);
  if (STACKSIZE == 0) {
    return;
  }
  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();
  BuildMI(MBB, MBBI, DL, TII.get(RISCX::ADDI), RISCX::SP)
      .addReg(RISCX::SP)
      .addImm(-STACKSIZE)
      .setMIFlag(MachineInstr::FrameSetup);
}

void RISCXFrameLowering::emitEpilogue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();

  const TargetInstrInfo &TII = *STI.getInstrInfo();
  int STACKSIZE = computeStackSize(MF);
  if (STACKSIZE == 0) {
    return;
  }
  DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();
  BuildMI(MBB, MBBI, DL, TII.get(RISCX::ADDI), RISCX::SP)
      .addReg(RISCX::SP)
      .addImm(STACKSIZE)
      .setMIFlag(MachineInstr::FrameDestroy);
}

bool RISCXFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return false;
}

uint64_t RISCXFrameLowering::computeStackSize(MachineFunction &MF) const {
  uint64_t STACK_SIZE = MF.getFrameInfo().getStackSize();
  if (getStackAlignment() > 0) {
    STACK_SIZE = ROUND_UP(STACK_SIZE, getStackAlignment());
  }
  return STACK_SIZE;
}

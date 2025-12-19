//
// Created by marvinli on 2025/12/19.
//

#include "RISCXFrameLowering.h"

using namespace llvm;

void RISCXFrameLowering::emitPrologue(
    MachineFunction &MF, MachineBasicBlock &MBB) const {}

void RISCXFrameLowering::emitEpilogue(
    MachineFunction &MF, MachineBasicBlock &MBB) const {}

bool RISCXFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return false;
}

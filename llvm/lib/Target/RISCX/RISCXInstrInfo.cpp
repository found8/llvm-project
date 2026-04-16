//
// Created by marvinli on 2025/12/18.
//

#include "RISCXInstrInfo.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RISCXGenInstrInfo.inc"

RISCXInstrInfo::RISCXInstrInfo() : RISCXGenInstrInfo() {
  ;
}

void RISCXInstrInfo::storeRegToStackSlot(
    llvm::MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    llvm::Register SrcReg, bool isKill, int FrameIndex,
    const llvm::TargetRegisterClass *RC, const llvm::TargetRegisterInfo *TRI,
    llvm::Register VReg, MachineInstr::MIFlag Flags) const {
  DebugLoc DL;
  BuildMI(MBB, MI, DL, get(RISCX::STOREWFI))
      .addReg(SrcReg, getKillRegState(isKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RISCXInstrInfo::loadRegFromStackSlot(
    llvm::MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    llvm::Register DestReg, int FrameIndex, const llvm::TargetRegisterClass *RC,
    const llvm::TargetRegisterInfo *TRI, llvm::Register VReg,
    MachineInstr::MIFlag Flags) const {
  DebugLoc DL;
  BuildMI(MBB, MI, DL, get(RISCX::LOADWFI), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RISCXInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator MI,
                                 const DebugLoc &DL, llvm::Register DestReg,
                                 llvm::Register SrcReg, bool KillSrc,
                                 bool RenamableDest, bool RenamableSrc) const {
//  TargetInstrInfo::copyPhysReg(MBB, MI, DL, DestReg, SrcReg, KillSrc,
//                               RenamableDest, RenamableSrc);
  MachineInstrBuilder MIB = BuildMI(MBB, MI, DL, get(RISCX::ADD));
  MIB.addReg(DestReg, RegState::Define);
  MIB.addReg(RISCX::ZERO);
  MIB.addReg(SrcReg, getKillRegState(KillSrc));
}

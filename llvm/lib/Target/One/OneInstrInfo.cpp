//
// Created by 蔡鹏 on 2024/12/1.
//

#include "OneInstrInfo.h"
#include "MCTargetDesc/OneMCTargetDesc.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "OneGenInstrInfo.inc"

OneInstrInfo::OneInstrInfo() : OneGenInstrInfo() {}

void OneInstrInfo::storeRegToStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register SrcReg,
    bool isKill, int FrameIndex, const TargetRegisterClass *RC,
    const TargetRegisterInfo *TRI, Register VReg) const {
  DebugLoc DL;
  BuildMI(MBB, MI, DL, get(One::STORE))
      .addReg(SrcReg, getKillRegState(isKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void OneInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        Register DestReg, int FrameIndex,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI,
                                        Register VReg) const {
  DebugLoc DL;
  BuildMI(MBB, MI, DL, get(One::LOAD), DestReg)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}
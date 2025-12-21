//
// Created by marvinli on 2025/12/18.
//

#include "RISCXSubtarget.h"
#include "RISCXSelectionDAGInfo.h"

using namespace llvm;

#define DEBUG_TYPE "riscx-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RISCXGenSubtargetInfo.inc"

RISCXSubtarget::RISCXSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : RISCXGenSubtargetInfo(TT, CPU, CPU, FS), FrameLowering(*this),
      TLInfo(TM, *this) {
  TSInfo = std::make_unique<RISCXSelectionDAGInfo>();
}

RISCXSubtarget &
RISCXSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef TuneCPU, StringRef FS,
                                                StringRef ABIName) {
  if (CPU.empty() || CPU == "generic") {
    CPU = "riscx";
  }
  ParseSubtargetFeatures(CPU, /*TuneCPU */ CPU, FS);
  return *this;
}

//const TargetFrameLowering *RISCXSubtarget::getFrameLowering() const {
//  return TargetSubtargetInfo::getFrameLowering();
//}

const SelectionDAGTargetInfo *RISCXSubtarget::getSelectionDAGInfo() const {
  return TSInfo.get();
}

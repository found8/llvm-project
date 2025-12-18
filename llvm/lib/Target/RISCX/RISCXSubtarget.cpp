//
// Created by marvinli on 2025/12/18.
//

#include "RISCXSubtarget.h"

using namespace llvm;

#define DEBUG_TYPE "riscx-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RISCXGenSubtargetInfo.inc"

RISCXSubtarget::RISCXSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
    : RISCXGenSubtargetInfo(TT, CPU, CPU, FS) {
  ;
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

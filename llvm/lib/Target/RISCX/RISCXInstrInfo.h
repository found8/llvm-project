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
};
} // namespace llvm

#endif // LLVM_RISCXINSTRINFO_H

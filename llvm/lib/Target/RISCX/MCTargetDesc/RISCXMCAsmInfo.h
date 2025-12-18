//
// Created by marvinli on 2025/12/18.
//

#ifndef LLVM_RISCXMCASMINFO_H
#define LLVM_RISCXMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class RISCXMCAsmInfo : public MCAsmInfoELF {
public:
  explicit RISCXMCAsmInfo(const Triple &TargetTriple);
};
} // namespace llvm

#endif // LLVM_RISCXMCASMINFO_H

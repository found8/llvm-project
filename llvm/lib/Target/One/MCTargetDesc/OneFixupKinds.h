//
// Created by 蔡鹏 on 2025/1/31.
//

#ifndef ONEFIXUPKINDS_H
#define ONEFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace One {
enum Fixups {
  // 20-bit fixup corresponding to %hi(foo) for instructions like lui
  fixup_riscv_hi20 = FirstTargetFixupKind,
  // 12-bit fixup corresponding to %lo(foo) for instructions like addi
  fixup_riscv_lo12_i,
  fixup_riscv_jal,
  fixup_riscv_branch,
  fixup_riscv_invalid,
  NumTargetFixupKinds = fixup_riscv_invalid - FirstTargetFixupKind
};
}
}

#endif //ONEFIXUPKINDS_H

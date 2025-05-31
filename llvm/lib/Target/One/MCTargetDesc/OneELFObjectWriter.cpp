//
// Created by 蔡鹏 on 2025/1/30.
//

#include "OneELFObjectWriter.h"
#include "OneFixupKinds.h"
#include "llvm/MC/MCContext.h"

using namespace llvm;

unsigned OneELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  unsigned Kind = Fixup.getTargetKind();
  switch (Kind) {
  default:
    Ctx.reportError(Fixup.getLoc(), "unsupported relocation type");
    return ELF::R_RISCV_NONE;
  case One::fixup_riscv_hi20:
    return ELF::R_RISCV_HI20;
  case One::fixup_riscv_lo12_i:
    return ELF::R_RISCV_LO12_I;
  case One::fixup_riscv_jal:
    return ELF::R_RISCV_JAL;
  case One::fixup_riscv_branch:
    return ELF::R_RISCV_BRANCH;
  }
}

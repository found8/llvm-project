//
// Created by 蔡鹏 on 2025/1/30.
//

#include "OneAsmBackend.h"
#include "OneELFObjectWriter.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"

using namespace llvm;

const MCFixupKindInfo &OneAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {
  const static MCFixupKindInfo Infos[One::NumTargetFixupKinds] = {
      {"fixup_riscv_hi20", 12, 20, 0},
    {"fixup_riscv_lo12_i", 20, 12, 0},
    {"fixup_riscv_jal", 12, 20, 0},
    {"fixup_riscv_branch", 0, 32, 0}
  };
  if (Kind < FirstTargetFixupKind)
    return MCAsmBackend::getFixupKindInfo(Kind);
  assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
         "Invalid kind!");
  return Infos[Kind - FirstTargetFixupKind];
}

std::unique_ptr<MCObjectTargetWriter>
OneAsmBackend::createObjectTargetWriter() const {
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TheTriple.getOS());
  bool IsN64 = false;
  bool HasRelocationAddend = false;
  return std::make_unique<OneELFObjectWriter>(OSABI, HasRelocationAddend,
                                              IsN64);
}

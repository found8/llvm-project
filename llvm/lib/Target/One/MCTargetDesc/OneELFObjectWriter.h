//
// Created by 蔡鹏 on 2025/1/30.
//

#ifndef ONEELFOBJECTWRITER_H
#define ONEELFOBJECTWRITER_H

#include "llvm/MC/MCELFObjectWriter.h"

namespace llvm {
class OneELFObjectWriter : public MCELFObjectTargetWriter {
public:
  OneELFObjectWriter(uint8_t OSABI, bool HasRelocationAddend, bool Is64)
    : MCELFObjectTargetWriter(false, OSABI, ELF::EM_RISCV, false) {}

   ~OneELFObjectWriter() = default;

  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                               const MCFixup &Fixup, bool IsPCRel) const override;
  bool needsRelocateWithSymbol(const MCValue &Val, const MCSymbol &Sym,
                                       unsigned Type) const override {
                                       return true;
                                       }
};
}



#endif //ONEELFOBJECTWRITER_H

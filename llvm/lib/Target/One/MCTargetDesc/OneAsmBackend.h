//
// Created by 蔡鹏 on 2025/1/30.
//

#ifndef ONEASMBACKEND_H
#define ONEASMBACKEND_H

#include "llvm/MC/MCAsmBackend.h"
#include "llvm/TargetParser/Triple.h"
#include "OneFixupKinds.h"

namespace llvm {

class Target;
class OneAsmBackend : public MCAsmBackend {
  Triple TheTriple;
public:
  OneAsmBackend(const Target &T, const Triple &TT)
    : MCAsmBackend(endianness::little), TheTriple(TT) {}

  std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override;

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override;

  unsigned getNumFixupKinds() const override {
    return One::NumTargetFixupKinds;
  }

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                            const MCValue &Target, MutableArrayRef<char> Data,
                            uint64_t Value, bool IsResolved,
                            const MCSubtargetInfo *STI) const override {}

  bool writeNopData(raw_ostream &OS, uint64_t Count,
                            const MCSubtargetInfo *STI) const override {return true;}

};
}


#endif //ONEASMBACKEND_H

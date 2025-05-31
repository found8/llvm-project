//
// Created by 蔡鹏 on 2025/1/30.
//

#ifndef ONECODEEMITTER_H
#define ONECODEEMITTER_H

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInst.h"
#include "OneMCTargetDesc.h"
#include <stdint.h>
namespace llvm {
class MCInstrInfo;
class MCContext;
class MCInst;

class OneMCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;

public:
  OneMCCodeEmitter(const MCInstrInfo &mcii, MCContext &Ctx) : Ctx(Ctx) {}

  ~OneMCCodeEmitter() override {}

  void encodeInstruction(const MCInst &Inst, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  // NOTE: auto gen in "ToyGenMCCodeEmitter.inc"
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  // NOTE: called by ToyGenMCCodeEmitter
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
};
} // namespace llvm

#endif // ONECODEEMITTER_H

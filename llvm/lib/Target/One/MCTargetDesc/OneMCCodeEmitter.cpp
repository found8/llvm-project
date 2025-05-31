//
// Created by 蔡鹏 on 2025/1/30.
//

#include "OneMCCodeEmitter.h"
#include "OneFixupKinds.h"
#include "OneMCExpr.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/Casting.h"

#define DEBUG_TYPE "one code emitter"

using namespace llvm;

void OneMCCodeEmitter::encodeInstruction(const MCInst &MI,
                                         SmallVectorImpl<char> &CB,
                                         SmallVectorImpl<MCFixup> &Fixups,
                                         const MCSubtargetInfo &STI) const {
  LLVM_DEBUG(errs() << MI);
  uint32_t Binary = getBinaryCodeForInstr(MI, Fixups, STI);

  for (int i = 0; i < 4; ++i) {
    unsigned Shift = i * 8;
    CB.push_back((char)((Binary >> Shift) & 0xff));
  }
}

unsigned OneMCCodeEmitter::getMachineOpValue(const MCInst &MI,
                                             const MCOperand &MO,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  if (MO.isReg()) {
    unsigned Reg = MO.getReg();
    unsigned RegNo = Ctx.getRegisterInfo()->getEncodingValue(Reg);
    return RegNo;
  } else if (MO.isImm()) {
    return static_cast<unsigned>(MO.getImm());
  }

  assert(MO.isExpr());
  const MCExpr *Expr = MO.getExpr();
  const OneMCExpr *OneExpr = dyn_cast<OneMCExpr>(Expr);
  One::Fixups FixupKind = One::Fixups::fixup_riscv_invalid;
  switch (OneExpr->getKind()) {
  case OneMCExpr::HI: {
    FixupKind = One::Fixups::fixup_riscv_hi20;
    break;
  }
  case OneMCExpr::LO: {
    FixupKind = One::Fixups::fixup_riscv_lo12_i;
    break;
  }
  case OneMCExpr::JAL: {
    FixupKind = One::Fixups::fixup_riscv_jal;
    break;
  }
  case OneMCExpr::Branch: {
    FixupKind = One::Fixups::fixup_riscv_branch;
    break;
  }
  default:
    break;
  }
  Fixups.push_back(MCFixup::create(0, Expr, MCFixupKind(FixupKind)));
  return 0;
}

#include "OneGenMCCodeEmitter.inc"
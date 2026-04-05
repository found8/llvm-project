//
// Created by marvinli on 2026/04/05.
//

#ifndef LLVM_RISCXMCEXPR_H
#define LLVM_RISCXMCEXPR_H

#include "llvm/MC/MCExpr.h"

namespace llvm {
// class Triple;

class RISCXMCExpr : public MCTargetExpr {
public:
  enum Kind {
    NONE,
    HI,
    LO
  };
  RISCXMCExpr(Kind kind, const MCExpr *Expr) : kind(kind), Expr(Expr) {};

  void printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const override;
  bool evaluateAsRelocatableImpl(MCValue &Res,
                                 const MCAssembler *Asm) const override;
  void visitUsedExpr(MCStreamer& Streamer) const override;
  MCFragment *findAssociatedFragment() const override;
private:
  const Kind kind;
  const MCExpr *Expr;
};
} // namespace llvm

#endif // LLVM_RISCXMCEXPR_H

//
// Created by 蔡鹏 on 2025/1/20.
//

#ifndef ONEMCEXPR_H
#define ONEMCEXPR_H

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCStreamer.h"

namespace llvm {
class OneMCExpr : public MCTargetExpr {
public:
  enum Kind { NONE, HI, LO, JAL, Branch };
  OneMCExpr(Kind K, const MCExpr *Expr) : Kd(K), Expr(Expr) {}

  void printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const override;

  bool evaluateAsRelocatableImpl(MCValue &Res, const MCAssembler *Asm,
                                 const MCFixup *Fixup) const override {
    return Expr->evaluateAsRelocatable(Res, Asm, Fixup);
  };
  void visitUsedExpr(MCStreamer &Streamer) const override {
    // NOTE: OneMCExpr 的 kind 是 Target, 导致 MCStreamer 不知道如何 visit 它的
    // operand, 需要自己实现. visitUsedExpr 会把 operand 中用到的 symbol ref 加
    // 入到符号表中
    Streamer.visitUsedExpr(*Expr);
  }
  MCFragment *findAssociatedFragment() const override { return nullptr; }

  void fixELFSymbolsInTLSFixups(MCAssembler &) const override {}
  Kind getKind() const { return Kd; }
private:
  const Kind Kd;
  const MCExpr *Expr;
};
} // namespace llvm

#endif // ONEMCEXPR_H

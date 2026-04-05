//
// Created by marvinli on 2026/04/05.
//

#include "RISCXMCExpr.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// RISCXMCExpr::RISCXMCExpr(const Triple &TT) { CommentString = "#"; }
void RISCXMCExpr::printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const {
  switch (kind)
  {
  case HI:
    OS << "%hi(";
    Expr->print(OS, MAI, true);
    OS << ")";
    break;
  case LO:
    OS << "%lo(";
    Expr->print(OS, MAI, true);
    OS << ")";
    break;
  default:
    Expr->print(OS, MAI, true);
    break;
  }
}

bool RISCXMCExpr::evaluateAsRelocatableImpl(MCValue &Res,
                                            const MCAssembler *Asm) const {
  return false;
}

void RISCXMCExpr::visitUsedExpr(MCStreamer& Streamer) const {
}

MCFragment *RISCXMCExpr::findAssociatedFragment() const {
  return nullptr;
}
//
// Created by marvinli on 2025/12/20.
//

#ifndef LLVM_RISCX_H
#define LLVM_RISCX_H

namespace llvm {
#define DIV_ROUND_UP(n, d)  (((n) + (d) - 1) / (d))
#define ROUND_UP(x, align)  (DIV_ROUND_UP(x, align) * (align))

class FunctionPass;
class RISCXTargetMachine;
class PassRegistry;

FunctionPass *createRISCXISelDag(RISCXTargetMachine &TM);
void initializeRISCXDAGToDAGISelLegacyPass(PassRegistry &Registry);

} // namespace llvm

#endif // LLVM_RISCX_H
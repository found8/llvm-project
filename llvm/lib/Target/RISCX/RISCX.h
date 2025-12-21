//
// Created by marvinli on 2025/12/20.
//

#ifndef LLVM_RISCX_H
#define LLVM_RISCX_H

namespace llvm {
class FunctionPass;
class RISCXTargetMachine;
class PassRegistry;

FunctionPass *createRISCXISelDag(RISCXTargetMachine &TM);
void initializeRISCXDAGToDAGISelLegacyPass(PassRegistry &Registry);

} // namespace llvm

#endif // LLVM_RISCX_H
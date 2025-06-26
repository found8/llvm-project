#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/RISCXTargetInfo.h"
using namespace llvm;

Target &llvm::getTheRISCXTarget() {
    static Target TheRISCXTarget;
    return TheRISCXTarget;
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRISCXTargetInfo() {
  RegisterTarget<Triple::riscx, /*HasJIT=*/true> X(
      getTheRISCXTarget(), "riscx", "32-bit RISC-X", "RISCX");
}
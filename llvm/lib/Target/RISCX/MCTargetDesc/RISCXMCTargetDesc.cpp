#include "llvm/Support/Compiler.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/RISCXTargetInfo.h"

using namespace llvm;

MCAsmInfo *createRISCXMCAsmInfo(const MCRegisterInfo &MRI,
                                           const Triple &TT,
                                           const MCTargetOptions &Options) {
                                            ;
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRISCXTargetMC() {
    TargetRegistry::RegisterMCAsmInfo(getTheRISCXTarget(), createRISCXMCAsmInfo);
}
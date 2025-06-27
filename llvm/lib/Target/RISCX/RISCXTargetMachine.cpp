#include "RISCXTargetMachine.h"
#include "TargetInfo/RISCXTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/MC/TargetRegistry.h"
// #include "llvm/ADT/StringRef.h"
// #include "llvm/Support/Compiler.h"
using namespace llvm;

static StringRef computeDataLayout(const Triple &TT,
                                   const TargetOptions &Options) {
  assert(TT.isArch32Bit() && "only 32 bit is currently supported");
  return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

RISCXTargetMachine::RISCXTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT, Options), TT, CPU, FS,
                               Options, getEffectiveRelocModel(TT, RM),
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  // initAsmInfo();
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCXTarget() {
  RegisterTargetMachine<RISCXTargetMachine> X(getTheRISCXTarget());
}

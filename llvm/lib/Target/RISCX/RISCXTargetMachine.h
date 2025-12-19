#ifndef LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
#define LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
// #include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "RISCXSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/Target/TargetMachine.h"
// #include "llvm/IR/DataLayout.h"
// #include <optional>

namespace llvm {
class RISCXTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  RISCXSubtarget Subtarget;

public:
  RISCXTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  const RISCXSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }
  // DO NOT IMPLEMENT: There is no such thing as a valid default subtarget,
  // subtargets are per-function entities based on the target-specific
  // attributes of each function.
  const RISCXSubtarget *getSubtargetImpl() const { return &Subtarget; }

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
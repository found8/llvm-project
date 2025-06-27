#ifndef LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
#define LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
// #include "MCTargetDesc/RISXVMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
// #include "llvm/IR/DataLayout.h"
// #include <optional>

namespace llvm {
class RISCXTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
public:
  RISCXTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
}

#endif // LLVM_LIB_TARGET_RISCX_RISCXTARGETMACHINE_H
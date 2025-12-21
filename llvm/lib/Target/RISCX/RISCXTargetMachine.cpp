#include "RISCXTargetMachine.h"
#include "TargetInfo/RISCXTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/MC/TargetRegistry.h"
// #include "llvm/ADT/StringRef.h"
// #include "llvm/Support/Compiler.h"
#include "llvm/CodeGen/TargetPassConfig.h"

#include "RISCX.h"

using namespace llvm;

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCXTarget() {
  RegisterTargetMachine<RISCXTargetMachine> X(getTheRISCXTarget());
  auto *PR = PassRegistry::getPassRegistry();
  initializeRISCXDAGToDAGISelLegacyPass(*PR);
}

static StringRef computeDataLayout(const Triple &TT,
                                   const TargetOptions &Options) {
  assert(TT.isArch32Bit() && "only RX32 is currently supported");
  return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

RISCXTargetMachine::RISCXTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT, Options), TT, CPU, FS,
                               Options, getEffectiveRelocModel(RM),
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
class RISCXPassConfig : public TargetPassConfig {
public:
  RISCXPassConfig(RISCXTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  RISCXTargetMachine &getRISCXTargetMachine() const {
    return getTM<RISCXTargetMachine>();
  }

  const RISCXSubtarget &getRISCXSubtarget() const {
    return *getRISCXTargetMachine().getSubtargetImpl();
  }
  // void addIRPasses() override;
  // bool addIRTranslator() override;
  // bool addLegalizeMachineIR() override;
  // bool addRegBankSelect() override;
  // bool addGlobalInstructionSelect() override;
  bool addInstSelector() override;
  // void addPreSched2() override;
  // void addPreEmitPass() override;
};
}

TargetPassConfig *RISCXTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new RISCXPassConfig(*this, PM);
}

bool RISCXPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createRISCXISelDag(getRISCXTargetMachine()));
  // addPass(createM68kGlobalBaseRegPass());
  return false;
}

#include "RISCXMCTargetDesc.h"
#include "llvm/Support/Compiler.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/RISCXTargetInfo.h"
#include "RISCXMCAsmInfo.h"
#include "RISCXInstrInfo.h"
#include "RISCXSubtarget.h"
#include "RISCXInstPrinter.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "RISCXGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "RISCXGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RISCXGenSubtargetInfo.inc"

MCRegisterInfo *createRISCXMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRISCXMCRegisterInfo(X, RISCX::X1);
  return X;
}

MCInstrInfo *createRISCXMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitRISCXMCInstrInfo(X);
  return X;
}

MCSubtargetInfo *createRISCXMCSubtargetInfo(const Triple &TT, StringRef CPU,
                                            StringRef FS) {
  if (CPU.empty()) {
    CPU = "riscx";
  }
  return createRISCXMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

MCAsmInfo *createRISCXMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT,
                                const MCTargetOptions &Options) {
  return new RISCXMCAsmInfo(TT);
}

MCInstPrinter *createRISCXMCInstPrinter(const Triple &T,
                                                 unsigned SyntaxVariant,
                                                 const MCAsmInfo &MAI,
                                                 const MCInstrInfo &MII,
                                                 const MCRegisterInfo &MRI) {
  return new RISCXInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRISCXTargetMC() {
  TargetRegistry::RegisterMCRegInfo(getTheRISCXTarget(), createRISCXMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(getTheRISCXTarget(), createRISCXMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(getTheRISCXTarget(), createRISCXMCSubtargetInfo);
  TargetRegistry::RegisterMCAsmInfo(getTheRISCXTarget(), createRISCXMCAsmInfo);
  TargetRegistry::RegisterMCInstPrinter(getTheRISCXTarget(), createRISCXMCInstPrinter);
}
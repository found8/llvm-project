include "llvm/Target/Target.td"

include "RISCXRegisterInfo.td"
include "RISCXInstrInfo.td"
include "RISCXCallingConv.td"

def : ProcessorModel<"generic", NoSchedModel, []>; // ?

def RISCXInstrInfo : InstrInfo;

def RISCX : Target {
  let InstructionSet = RISCXInstrInfo;
//   let PointerSize = 4;
//   let CalleeSaveStackSlotAlignment = 4;
//   let StackAlignment = 16;
//   let GlobalISelDefaultEnable = true;
}
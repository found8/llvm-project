#ifndef LLVM_LIB_TARGET_RISCX_RISCXMCTARGETDESC_H
#define LLVM_LIB_TARGET_RISCX_RISCXMCTARGETDESC_H

namespace llvm {

}

// Defines symbolic names for RISC-X registers.
#define GET_REGINFO_ENUM
#include "RISCXGenRegisterInfo.inc"

//// Defines symbolic names for RISC-X instructions.
//#define GET_INSTRINFO_ENUM
//#define GET_INSTRINFO_MC_HELPER_DECLS
//#include "RISCXGenInstrInfo.inc"
//
//#define GET_SUBTARGETINFO_ENUM
//#include "RISCXGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_RISCX_RISCXMCTARGETDESC_H
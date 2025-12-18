add_llvm_component_group(RISCX)

set(LLVM_TARGET_DEFINITIONS RISCX.td)

tablegen(LLVM RISCXGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM RISCXGenCallingConv.inc -gen-callingconv)
tablegen(LLVM RISCXGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RISCXGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RISCXGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISCXGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(RISCXCommonTableGen)

add_llvm_target(RISCXCodeGen
  RISCXTargetMachine.cpp
  RISCXInstrInfo.cpp
  RISCXRegisterInfo.cpp
  RISCXSubtarget.cpp

  LINK_COMPONENTS
  # AsmPrinter
  CodeGen
  # CodeGenTypes
  # Core
  MC
  # RISCXDesc
  RISCXInfo
  # SelectionDAG
  Support
  Target
  TargetParser
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

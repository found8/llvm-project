add_llvm_component_group(RISCX)

add_llvm_target(RISCXCodeGen
  RISCXTargetMachine.cpp

  LINK_COMPONENTS
  Support
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

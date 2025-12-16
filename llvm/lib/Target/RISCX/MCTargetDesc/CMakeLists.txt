add_llvm_component_library(LLVMRISCXDesc
  RISCXMCTargetDesc.cpp

  LINK_COMPONENTS
  RISCXInfo
  Support
  )
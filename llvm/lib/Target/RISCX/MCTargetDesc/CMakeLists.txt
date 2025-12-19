add_llvm_component_library(LLVMRISCXDesc
  RISCXMCTargetDesc.cpp
  RISCXMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  RISCXInfo
  Support
  )
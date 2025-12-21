add_llvm_component_library(LLVMRISCXDesc
  RISCXMCTargetDesc.cpp
  RISCXMCAsmInfo.cpp
  RISCXInstPrinter.cpp

  LINK_COMPONENTS
  MC
  RISCXInfo
  Support
  )
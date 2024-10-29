add_llvm_component_library(LLVMCpu0AsmPrinter
  Cpu0InstPrinter.cpp

  LINK_COMPONENTS
  MC # for -DBUILD_SHARED_LIBS=ON
  Support

  ADD_TO_COMPONENT
  Cpu0
  )

add_llvm_component_library(LLVMRISCVNInfo
        RISCVNTargetInfo.cpp

        LINK_COMPONENTS
        MC
        Support

        ADD_TO_COMPONENT
        RISCVN
        )
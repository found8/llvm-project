add_llvm_component_library(LLVMOneDesc
        OneMCTargetDesc.cpp
        OneMCAsmInfo.cpp

        LINK_COMPONENTS
        MC
        OneInfo
        Support
        TargetParser

        ADD_TO_COMPONENT
        One
)
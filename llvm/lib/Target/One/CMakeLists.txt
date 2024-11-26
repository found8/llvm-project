add_llvm_component_group(One)

add_llvm_target(OneCodeGen
        OneTargetMachine.cpp

        LINK_COMPONENTS
        AsmPrinter
        CodeGen
        CodeGenTypes
        Core
        MC
        SelectionDAG
        OneDesc
        OneInfo
        Support
        Target
        TargetParser

        ADD_TO_COMPONENT
        One
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
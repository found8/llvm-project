//
// Created by 蔡鹏 on 2024/12/1.
//

#ifndef ONE_H
#define ONE_H
namespace llvm {

class FunctionPass;
class OneTargetMachine;

FunctionPass *createOneISelDag(OneTargetMachine &TM);

void initializeOneDAGToDAGISelLegacyPass(PassRegistry &);

} // namespace llvm
#endif // ONE_H

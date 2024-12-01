//
// Created by 蔡鹏 on 2024/12/1.
//

#include "OneInstrInfo.h"
#include "MCTargetDesc/OneMCTargetDesc.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "OneGenInstrInfo.inc"

OneInstrInfo::OneInstrInfo() : OneGenInstrInfo() {}
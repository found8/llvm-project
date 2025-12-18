//
// Created by marvinli on 2025/12/18.
//

#include "RISCXInstrInfo.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RISCXGenInstrInfo.inc"

RISCXInstrInfo::RISCXInstrInfo() : RISCXGenInstrInfo() {
  ;
}

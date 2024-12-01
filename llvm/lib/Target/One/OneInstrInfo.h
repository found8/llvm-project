//
// Created by 蔡鹏 on 2024/12/1.
//

#ifndef ONEINSTRINFO_H
#define ONEINSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "OneGenInstrInfo.inc"

namespace llvm {
class OneInstrInfo : public OneGenInstrInfo {
public:
  explicit OneInstrInfo();
};
} // namespace llvm

#endif // ONEINSTRINFO_H

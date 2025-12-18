//
// Created by marvinli on 2025/12/18.
//

#include "RISCXMCAsmInfo.h"

using namespace llvm;

RISCXMCAsmInfo::RISCXMCAsmInfo(const Triple &TT) {
  CommentString = "//";
}
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RISCXSelectionDAGInfo.h"

#define GET_SDNODE_DESC
#include "RISCXGenSDNodeInfo.inc"

using namespace llvm;

RISCXSelectionDAGInfo::RISCXSelectionDAGInfo()
    : SelectionDAGGenTargetInfo(RISCXGenSDNodeInfo) {}

RISCXSelectionDAGInfo::~RISCXSelectionDAGInfo() = default;

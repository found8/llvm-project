//
// Created by marvinli on 2025/12/19.
//

#include "RISCXISelLowering.h"
#include "RISCXRegisterInfo.h" // for ISCX::GPRRegClass
#include "RISCXSubtarget.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h" // for RISCXGenCallingConv.inc
#include "llvm/CodeGen/CallingConvLower.h" // for CCValAssign
using namespace llvm;

#include "RISCXGenCallingConv.inc"
#define GET_SDNODE_ENUM
#include "RISCXGenSDNodeInfo.inc"

RISCXTargetLowering::RISCXTargetLowering(const TargetMachine &TM,
                                         const RISCXSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  addRegisterClass(MVT::i32, &RISCX::GPRRegClass);
  computeRegisterProperties(STI.getRegisterInfo());
}

SDValue RISCXTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &dl,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  return Chain;
}

SDValue
RISCXTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                 bool isVarArg,
                                 const SmallVectorImpl<ISD::OutputArg> &Outs,
                                 const SmallVectorImpl<SDValue> &OutVals,
                                 const SDLoc &DL, SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 16> RVLocs;

  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), RVLocs, *DAG.getContext());
  CCInfo.AnalyzeReturn(Outs, RetCC_RISCX);

  SDValue Glue;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }
  RetOps[0] = Chain;

  // Add the glue node if we have it.
  if (Glue.getNode()) {
    RetOps.push_back(Glue);
  }
  return DAG.getNode(RISCXISD::RET_GLUE, DL, MVT::Other, RetOps);
}

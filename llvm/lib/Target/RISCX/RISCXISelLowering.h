//
// Created by marvinli on 2025/12/19.
//

#ifndef LLVM_RISCXISELLOWERING_H
#define LLVM_RISCXISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
class RISCXSubtarget;
// namespace RISCXISD {
// enum NodeType : unsigned { FIRST_NUMBER = ISD::BUILTIN_OP_END, RET_GLUE };
// }

class RISCXTargetLowering : public TargetLowering {
  const RISCXSubtarget &Subtarget;

public:
  explicit RISCXTargetLowering(const TargetMachine &TM,
                               const RISCXSubtarget &STI);

  const RISCXSubtarget &getSubtarget() const { return Subtarget; }

  SDValue LowerCall(CallLoweringInfo &CLI,
                    SmallVectorImpl<SDValue> &InVals) const override;

  /// llvm_unreachable("Not Implemented");
  /// This hook must be implemented to lower the incoming (formal) arguments,
  /// described by the Ins array, into the specified DAG. The implementation
  /// should fill in the InVals array with legal-type argument values, and
  /// return the resulting token chain value.
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  /// This hook must be implemented to lower outgoing return values, described
  /// by the Outs array, into the specified DAG. The implementation should
  /// return the resulting token chain value.
  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                      SelectionDAG &DAG) const override;

  /// This callback is invoked for operations that are unsupported by the
  /// target, which are registered to use 'custom' lowering, and whose defined
  /// values are all legal.  If the target has no operations that require custom
  /// lowering, it need not implement this.  The default implementation of this
  /// aborts.
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

private:
  SDValue lowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
};
} // namespace llvm

#endif // LLVM_RISCXISELLOWERING_H

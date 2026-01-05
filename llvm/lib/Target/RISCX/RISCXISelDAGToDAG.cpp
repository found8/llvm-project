//
// Created by marvinli on 2025/12/20.
//

#include "RISCX.h"
// #include "RISCXISelLowering.h"
#include "RISCXTargetMachine.h"
#include "MCTargetDesc/RISCXMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define GET_SDNODE_ENUM
#include "RISCXGenSDNodeInfo.inc"

#define DEBUG_TYPE "riscx-isel"
#define PASS_NAME "RISCX DAG->DAG Pattern Instruction Selection"

class RISCXDAGToDAGISel : public SelectionDAGISel {
    const RISCXSubtarget *Subtarget;
public:
  RISCXDAGToDAGISel() = delete;

  explicit RISCXDAGToDAGISel(RISCXTargetMachine &TM, CodeGenOptLevel OL)
      : SelectionDAGISel(TM, OL), Subtarget(nullptr) {}

  bool runOnMachineFunction(MachineFunction &MF) override;
  bool SelectAddrFI(SDNode *Parent, SDValue AddrFI, SDValue &Base, SDValue &Offset);

#include "RISCXGenDAGISel.inc"

  /// getTargetMachine - Return a reference to the TargetMachine, casted
  /// to the target-specific type.
  const RISCXTargetMachine &getTargetMachine() {
    return static_cast<const RISCXTargetMachine &>(TM);
  }
  
  void Select(SDNode *N) override;
};

bool RISCXDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &MF.getSubtarget<RISCXSubtarget>();
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void RISCXDAGToDAGISel::Select(SDNode *Node) {
  // unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  LLVM_DEBUG(dbgs() << "Selecting: "; Node->dump(CurDAG); dbgs() << '\n');
  SelectCode(Node);
}

bool RISCXDAGToDAGISel::SelectAddrFI(SDNode *Parent, SDValue AddrFI, SDValue &Base, SDValue &Offset) {
  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(AddrFI)) {
    Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), AddrFI.getValueType());
    Offset = CurDAG->getTargetConstant(0, SDLoc(AddrFI), AddrFI.getValueType());
    return true;
  }
  return false;
}

class RISCXDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;
  explicit RISCXDAGToDAGISelLegacy(RISCXTargetMachine &TM)
      : SelectionDAGISelLegacy(ID, std::make_unique<RISCXDAGToDAGISel>(TM, TM.getOptLevel())) {}
};

char RISCXDAGToDAGISelLegacy::ID;

INITIALIZE_PASS(RISCXDAGToDAGISelLegacy, DEBUG_TYPE, PASS_NAME, false, false)

/// This pass converts a legalized DAG into a RISCX-specific DAG,
/// ready for instruction scheduling.
FunctionPass *llvm::createRISCXISelDag(RISCXTargetMachine &TM) {
  return new RISCXDAGToDAGISelLegacy(TM);
}


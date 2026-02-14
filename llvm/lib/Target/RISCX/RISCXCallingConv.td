def RetCC_RISCX : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[A0, A1]>>,
]>;

def CC_RISCX : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[A0, A1, A2]>>,

  // Otherwise they are assigned to the stack in 4-byte aligned units.
  CCAssignToStack<4, 4>
]>;

def CSR : CalleeSavedRegs<(add RA, S0, S1)>;
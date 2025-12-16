def RetCC_RISCX : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[X10, X11]>>,
]>;
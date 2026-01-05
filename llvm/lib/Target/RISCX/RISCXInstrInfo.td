include "RISCXInstrFormats.td"

def retglue : SDNode<"RISCXISD::RET_GLUE", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def imm12 : Operand<i32>, ImmLeaf<i32, [{ return isInt<12>(Imm); }]>;
//def imm12Pat : ImmLeaf<i32, [{ return isInt<12>(Imm); }]>;
//def imm12Pat : PatLeaf<(imm), [{ return isInt<12>(N->getSExtValue()); }]>;

// load/store for addr
// addr -> memory
def mem : Operand<iPTR> {
  let MIOperandInfo = (ops GPR, imm12);
  // custom print method to print offset(GPR)
  let PrintMethod = "printMemOperand";
}

// SDNPWantParent -> pass frameIndex's ref Node
def memPat : ComplexPattern<iPTR, 2, "SelectAddrFI", [frameindex]> {
  let WantsParent = true;
}

def LOAD : RISCXInst<(outs GPR: $ra), (ins mem: $addr), "lw \t$ra, $addr", []>;
// from SDNode -> load Instruction Pattern Match
def : Pat<(load memPat: $addr), (LOAD memPat: $addr)>;

def STORE : RISCXInst<(outs), (ins GPR: $ra, mem: $addr), "sw \t$ra, $addr", []>;
def : Pat<(store GPR:$ra, memPat:$addr), (STORE GPR:$ra, memPat:$addr)>;

def ADDI : I<(outs GPR:$rd),
            (ins GPR:$rs1, imm12:$imm12),
            "addi $rd, $rs1, $imm12",
            []>;

def : Pat<(i32 (imm12:$imm12)), (ADDI ZERO, imm12:$imm12)>;

// jalr X0, X1, 0
let isCall = 1 in {
  def JALR : I<(outs GPR:$rd),
              (ins GPR:$rs1, imm12:$imm12),
              "jalr $rd, $rs1, $imm12",
              []>;
}

// 换行符是为了解决报错问题
let isBarrier = 1, isReturn = 1, isTerminator = 1 in {
  def PseudoRET : PseudoInst<
              (outs),
              (ins),
              [(retglue)], " ">,
              PseudoInstExpansion<(JALR ZERO, RA, 0)>;
}

def : InstAlias<"ret", (JALR ZERO, RA, 0)>;
def : InstAlias<"li $rd, $imm", (ADDI GPR:$rd, ZERO, i32imm:$imm)>;

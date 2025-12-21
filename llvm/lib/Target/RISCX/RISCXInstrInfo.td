include "RISCXInstrFormats.td"

def retglue : SDNode<"RISCXISD::RET_GLUE", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def ADDI : I<OPC_ADDI,
            (outs GPR:$rd),
            (ins GPR:$rs1, i32imm:$imm12),
            "addi $rd, $rs1, $imm12",
            []>;

def : Pat<(i32 (imm:$imm12)), (ADDI X0, imm:$imm12)>;

// jalr X0, X1, 0
let isCall = 1 in {
  def JALR : I<OPC_JALR,
              (outs GPR:$rd),
              (ins GPR:$rs1, i32imm:$imm12),
              "jalr $rd, $rs1, $imm12",
              []>;
}

// 换行符是为了解决报错问题
let isBarrier = 1, isReturn = 1, isTerminator = 1 in {
  def PseudoRET : PseudoInst<
              (outs),
              (ins),
              [(retglue)], "\n">,
              PseudoInstExpansion<(JALR X0, X1, 0)>;
}

def : InstAlias<"ret", (JALR X0, X1, 0)>;
def : InstAlias<"li $rd, $imm", (ADDI GPR:$rd, X0, i32imm:$imm)>;

include "RISCVNInstrFormats.td"

def imm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]>;

def RV32RET : SDNode<"RISCVNISD::RET", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;


def ADDI : RV32IInst<
            (outs GPR:$rd),
            (ins GPR:$rs1, i32imm:$imm12),
            "addi $rd, $rs1, $imm12",
            []>;

def : Pat<(i32 (imm:$imm12)), (ADDI X0, imm:$imm12)>;          

let isCall = 1 in {
  def JALR : RV32IInst<
              (outs GPR:$rd),
              (ins GPR:$rs1, imm12:$imm12),
              "jalr $rd, $rs1, $imm12",
              []>;
}


def : RV32Pseudo<(outs), (ins), "", [(RV32RET)]>, PseudoInstExpansion<(JALR X0, X1, 0)> {
    let isReturn = 1;
    let isTerminator = 1;
}

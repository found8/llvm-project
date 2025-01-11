include "OneInstrFormats.td"

def retglue : SDNode<"OneISD::RET_GLUE", SDTNone, [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

//class ImmLeaf<ValueType vt, code pred, SDNodeXForm xform = NOOP_SDNodeXForm,
//              SDNode ImmNode = imm>
//  : PatFrag<(ops), (vt ImmNode), [{}], xform>

// class PatLeaf<dag frag, code pred = [{}], SDNodeXForm xform = NOOP_SDNodeXForm>
// : PatFrag<(ops), frag, pred, xform>;

def imm12 : Operand<i32>, ImmLeaf<i32, [{ return isInt<12>(Imm);}]>;
// def imm12Pat : ImmLeaf<i32, [{ return isInt<12>(Imm);}]>;
// def imm12Pat : PatLeaf<(imm), [{ return isInt<12>(N->getSExtValue());}]>


// load store
// 操作的是地址 -> base + offset
// 对地址建模 -> 内存操作

def mem : Operand<iPTR> {
    /// 具体有哪些操作数
    let MIOperandInfo = (ops GPR, imm12);
    /// 指明自定义的打印函数 offset(GPR)这种形式
    let PrintMethod = "printMemOperand";
}

// SDNPWantParent -> 传递引用frameIndex的节点
// frameindex -> 传递 FrameIndexSDNode
def memPat : ComplexPattern<iPTR, 2, "SelectAddrFI", [frameindex], [SDNPWantParent]>;


// load 和 store
def LOADFI : OneInst<(outs GPR: $ra), (ins mem: $addr), "lw \t$ra, $addr", [(set GPR:$ra, (load memPat:$addr))]>;
def LOAD : OneInst<(outs GPR: $ra), (ins GPR: $rb), "lw \t$ra, 0($rb)", [(set GPR:$ra, (load GPR:$rb))]>;
/// 从SDNode -> load Instruction  Pattern Match
/// def : Pat<(load memPat:$addr), (LOADFI memPat: $addr)>;

def STOREFI : OneInst<(outs), (ins GPR: $ra, mem: $addr), "sw \t$ra, $addr", [(store GPR:$ra, memPat:$addr)]>;
def STORE : OneInst<(outs), (ins GPR: $ra, GPR: $rb), "sw \t$ra, 0($rb)", [(store GPR:$ra, GPR:$rb)]>;
/// def : Pat<(store GPR:$ra, memPat:$addr), (STOREFI GPR:$ra, memPat: $addr)>;

class ArithLogicI<string inst, SDNode node> : I<
    (outs GPR:$rd),
    (ins GPR:$rs1, imm12: $imm12),
    !strconcat(inst, "\t$rd, $rs1, $imm12"),
    [(set GPR:$rd, (node GPR:$rs1, imm12: $imm12))]
    >;

def ADDI : ArithLogicI<"addi", add>;
def ANDI : ArithLogicI<"andi", and>;
def ORI  : ArithLogicI<"ori", or>;
def XORI  : ArithLogicI<"xori", xor>;
def SLLI  : ArithLogicI<"slli", shl>;
def SRLI  : ArithLogicI<"srli", srl>;
def SRAI  : ArithLogicI<"srai", sra>;

//def ADDI : I<(outs GPR:$rd),
//                (ins GPR:$rs1, imm12: $imm12),
//                "addi $rd, $rs1, $imm12", [(set GPR:$rd, (add GPR: $rs1, imm12: $imm12))]>;


class ArithLogicR<string inst, SDNode node> : I<
    (outs GPR:$rd),
    (ins GPR:$rs1, GPR:$rs2),
    !strconcat(inst, "\t$rd, $rs1, $rs2"),
    [(set GPR:$rd, (node GPR:$rs1, GPR:$rs2))]
    >;
def ADD : ArithLogicR<"add", add>;
def SUB : ArithLogicR<"sub", sub>;
def MUL : ArithLogicR<"mul", mul>;
def DIV : ArithLogicR<"div", sdiv>;
def REM : ArithLogicR<"rem", srem>;
def AND : ArithLogicR<"and", and>;
def OR : ArithLogicR<"or", or>;
def XOR : ArithLogicR<"xor", xor>;
def SLL : ArithLogicR<"sll", shl>;
def SRL : ArithLogicR<"srl", srl>;
def SRA : ArithLogicR<"sra", sra>;

//def ADD : I<(outs GPR:$rd),
//                (ins GPR:$rs1, GPR: $rs2),
//                "add $rd, $rs1, $rs2", [(set GPR:$rd, (add GPR: $rs1, GPR: $rs2))]>;

def : Pat<(i32 (imm12:$imm12)), (ADDI ZERO, imm12:$imm12)>;


let isCall = 1 in {
  def JALR : I<(outs GPR:$rd),
              (ins GPR:$rs1, imm12:$imm12),
              "jalr $rd, $rs1, $imm12",
              []>;
}

let isBarrier = 1, isReturn = 1, isTerminator = 1 in {
  def PseudoRET : PseudoInst<
              (outs),
              (ins),
              [(retglue)]>,
              PseudoInstExpansion<(JALR ZERO, RA, 0)>;
}

/// 1. Call 的 SDNode定义
/// 2. SDNode pattern Instruction(Call的instruction)

def OneSDT_Call : SDTypeProfile<0, -1, [SDTCisVT<0, iPTR>]>;
def one_call  : SDNode<"OneISD::Call", OneSDT_Call,
                            [SDNPHasChain, SDNPOutGlue,
                             SDNPOptInGlue, SDNPVariadic]>;

// def tglobaladdr : SDNode<"ISD::TargetGlobalAddress",  SDTPtrLeaf, [],
//                            "GlobalAddressSDNode">;

def call_symbol : Operand<iPTR>;
def CALL : I<(outs), (ins call_symbol:$rs1), "call\t $rs1", [(one_call tglobaladdr:$rs1)]> {
    let isCall = 1;
}

def : InstAlias<"ret", (JALR ZERO, RA, 0)>;
def : InstAlias<"li $rd, $imm",  (ADDI GPR:$rd, ZERO, imm12:$imm)>;



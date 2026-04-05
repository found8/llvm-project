include "RISCXInstrFormats.td"

def riscx_retglue : SDNode<"RISCXISD::RET_GLUE", SDTNone,
                           [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

// Add the Lo 12 bits from an address. Selected to ADDI.
def riscx_lo : SDNode<"RISCXISD::LO", SDTIntUnaryOp>;

// Get the Hi 20 bits from an address. Selected to LUI.
def riscx_hi : SDNode<"RISCXISD::HI", SDTIntUnaryOp>;

class PTX_READ_SREG_R32<string regname, Intrinsic intop, list<Predicate> Preds=[]>
  : RISCXInst<(outs GPR:$d), (ins),
              "MVSPR2R $d, %" # regname # ";",
              [(set i32:$d, (intop))]>,
    Requires<Preds>;

multiclass PTX_READ_SREG_R32V4<string regname, list<Predicate> Preds=[]> {
   foreach suffix = ["x", "y", "z", "w"] in {
      defvar reg = regname # "_" # suffix;
      defvar intr = !cast<Intrinsic>("int_riscx_read_sreg_" # regname # "_" # suffix);
      def "_"#suffix :  PTX_READ_SREG_R32<reg, intr, Preds>;
   }
}

// TODO Add read vector-version of special registers

defm INT_PTX_SREG_TID   : PTX_READ_SREG_R32V4<"tid">;
defm INT_PTX_SREG_NTID  : PTX_READ_SREG_R32V4<"ntid">;
// defm INT_PTX_SREG_CTAID : PTX_READ_SREG_R32V4<"ctaid">;
// defm INT_PTX_SREG_NCTAID: PTX_READ_SREG_R32V4<"nctaid">;

def imm12 : Operand<i32>, ImmLeaf<i32, [{ return isInt<12>(Imm); }]>;
def imm20 : Operand<i32>, ImmLeaf<i32, [{ return isInt<20>(Imm); }]>;
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
def addFI : ComplexPattern<iPTR, 2, "SelectAddrFI", [frameindex]> {
  let WantsParent = true;
}

def LOADFI : RISCXInst<(outs GPR: $ra), (ins mem: $addr), "lw \t$ra, $addr", [(set GPR:$ra, (load addFI:$addr))]>;
// from SDNode -> load Instruction Pattern Match
//def : Pat<(load addFI: $addr), (LOADFI addFI: $addr)>;
def LOAD : RISCXInst<(outs GPR: $ra), (ins GPR: $rb), "lw \t$ra, 0($rb)", [(set GPR:$ra, (load GPR:$rb))]>;

def STOREFI : RISCXInst<(outs), (ins GPR: $ra, mem: $addr), "sw \t$ra, $addr", [(store GPR:$ra, addFI:$addr)]>;
//def : Pat<(store GPR:$ra, addFI:$addr), (STOREFI GPR:$ra, addFI:$addr)>;
def STORE : RISCXInst<(outs), (ins GPR: $ra, GPR: $rb), "sw \t$ra, 0($rb)", [(store GPR:$ra, GPR:$rb)]>;

class ArithLogicI<string inst, SDNode node> : I<
  (outs GPR:$rd),
  (ins GPR:$rs1, imm12:$imm12),
  !strconcat(inst, "\t$rd, $rs1, $imm12"),
  [(set GPR:$rd, (node GPR:$rs1, imm12:$imm12))]>;

def ADDI : ArithLogicI<"addi", add>;
def ORI  : ArithLogicI<"ori", or>;

class ArithLogicR<string inst, SDNode node> : I<
  (outs GPR:$rd),
  (ins GPR:$rs1, GPR:$rs2),
  !strconcat(inst, "\t$rd, $rs1, $rs2"),
  [(set GPR:$rd, (node GPR:$rs1, GPR:$rs2))]>;

def ADD : ArithLogicR<"add", add>;
def MUL : ArithLogicR<"mul", mul>;
def REM : ArithLogicR<"rem", srem>;
def DIV : ArithLogicR<"div", sdiv>;
def OR  : ArithLogicR<"or", or>;
def AND : ArithLogicR<"and", and>;
def XOR : ArithLogicR<"xor", xor>;
def SRA : ArithLogicR<"sra", sra>;
def SLL : ArithLogicR<"sll", shl>;

// def ADDI : I<(outs GPR:$rd),
//             (ins GPR:$rs1, imm12:$imm12),
//             "addi \t$rd, $rs1, $imm12",
//             [(set GPR:$rd, (add GPR:$rs1, imm12:$imm12))]>;

// def ADD : I<(outs GPR:$rd),
//             (ins GPR:$rs1, GPR:$rs2),
//             "add \t$rd, $rs1, $rs2",
//             [(set GPR:$rd, (add GPR:$rs1, GPR:$rs2))]>;

def : Pat<(i32 (imm12:$imm12)), (ADDI ZERO, imm12:$imm12)>;

// jalr X0, X1, 0
let isCall = 1 in {
  def JALR : I<(outs GPR:$rd),
              (ins GPR:$rs1, imm12:$imm12),
              "jalr \t$rd, $rs1, $imm12",
              []>;
}

// 换行符是为了解决报错问题
let isBarrier = 1, isReturn = 1, isTerminator = 1 in {
  def PseudoRET : PseudoInst<
              (outs),
              (ins),
              [(riscx_retglue)], " ">,
              PseudoInstExpansion<(JALR ZERO, RA, 0)>;
}

def RISCXSDT_Call : SDTypeProfile<0, -1, [SDTCisVT<0, iPTR>]>;

def riscxcall : SDNode<"RISCXISD::CALL", RISCXSDT_Call,
                            [SDNPHasChain, SDNPOutGlue,
                             SDNPOptInGlue, SDNPVariadic]>;

def call_symbal : Operand<iPTR>;
def CALL : I<(outs), (ins call_symbal:$rs1), "call \t$rs1", [(riscxcall tglobaladdr:$rs1)]> {
  let isCall = 1;
}

// def HI: SDNode<"RISCXISD::HI", SDTIntUnaryOp>;
// def LO: SDNode<"RISCXISD::LO", SDTIntUnaryOp>;

def LUI : U<(outs GPR:$rd), (ins imm20:$imm20), "lui \t$rd, $imm20", []>;

def : Pat<(riscx_hi tglobaladdr: $in), (LUI tglobaladdr: $in)>;
def : Pat<(add GPR: $hi, (riscx_lo tglobaladdr: $lo)), (ADDI GPR: $hi, tglobaladdr: $lo)>;

def : InstAlias<"ret", (JALR ZERO, RA, 0)>;
def : InstAlias<"li $rd, $imm", (ADDI GPR:$rd, ZERO, i32imm:$imm)>;

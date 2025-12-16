class RISCXOpcode<string name, bits<7> val, bits<3> funct3> {
  string Name = name;
  bits<7> Value = val;
  bits<3> Funct3 = funct3;
}

def OPC_ADDI : RISCXOpcode<"ADDI", 0b0010011, 0b000>;
def OPC_JALR : RISCXOpcode<"JALR", 0b1100111, 0b000>;

class RISCXInst<dag outs, dag ins, string asmstr, list<dag> pattern>
  : Instruction {
  field bits<32> Inst;
  field bits<32> SoftFail = 0;

  let Size = 4;
  let Namespace = "RISCX";

  dag OutOperandList = outs;
  dag InOperandList  = ins;
  // 为什么不用这种方式定义？
  // let OutOperandList = outs;
  // let InOperandList  = ins;
  let AsmString      = asmstr;
  let Pattern        = pattern;
}

class PseudoInst<dag outs, dag ins, list<dag> pattern, string asmstr = "">
  : RISCXInst<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

class I<RISCXOpcode opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
  : RISCXInst<outs, ins, asmstr, pattern> {
  bits<7> Opcode = opcode.Value;
  bits<5> rd;
  bits<3> funct3 = opcode.Funct3;
  bits<5> rs1;
  bits<12> imm12;

  let Inst{6-0} = Opcode;
  let Inst{11-7} = rd;
  let Inst{14-12} = funct3;
  let Inst{19-15} = rs1;
  let Inst{31-20} = imm12;
}

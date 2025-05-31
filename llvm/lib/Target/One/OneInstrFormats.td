class OneInst<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction {
    field bits<32> SoftFail = 0;

    let Size = 4;

    let Namespace = "One";

    dag OutOperandList = outs;
    dag InOperandList = ins;
    let AsmString = asmstr;
    let Pattern = pattern;

    field bits<32> Inst;
    bits<7> Opcode = 0;
    let Inst{6-0} = Opcode;
}

class PseudoInst<dag outs, dag ins, list<dag> pattern, string asmstr = "">
    : OneInst<outs, ins, asmstr, pattern> {
    let isPseudo = 1;
    let isCodeGenOnly = 1;
}

class R<bits<7> opcode, bits<7> funct7, bits<3> funct3, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;

    bits<5> rd;
    bits<5> rs1;
    bits<5> rs2;

    let Inst{31-25} = funct7;
    let Inst{24-20} = rs2;
    let Inst{19-15} = rs1;
    let Inst{14-12} = funct3;
    let Inst{11-7} = rd;
}

class I<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;

    bits<5> rd;
    bits<5> rs1;
    bits<12> imm;

    let Inst{31-20} = imm;
    let Inst{19-15} = rs1;
    let Inst{14-12} = funct3;
    let Inst{11-7} = rd;
}

class U<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;

    bits<5> rd;
    bits<20> imm;

    let Inst{31-12} = imm;
    let Inst{11-7} = rd;
}

class J<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;
    bits<20> imm20;
    bits<5> rd;

    let Inst{31} = imm20{19};
    let Inst{30-21} = imm20{9-0};
    let Inst{20} = imm20{10};
    let Inst{19-12} = imm20{18-11};
    let Inst{11-7} = rd;
}

class B<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;
    bits<5> rs2;
    bits<5> rs1;
    bits<12> imm12;

    let Inst{31} = imm12{11};
    let Inst{30-25} = imm12{9-4};
    let Inst{24-20} = rs2;
    let Inst{19-15} = rs1;
    let Inst{14-12} = funct3;
    let Inst{11-8} = imm12{3-0};
    let Inst{7} = imm12{10};
}

class S<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asmstr, list<dag> pattern>
    : OneInst<outs, ins, asmstr, pattern> {
    let Opcode = opcode;

    bits<5> rs1;
    bits<5> rs2;
    bits<12> imm;

    let Inst{31-25} = imm{11-5};
    let Inst{24-20} = rs2;
    let Inst{19-15} = rs1;
    let Inst{14-12} = funct3;
    let Inst{11-7} = imm{4-0};
}

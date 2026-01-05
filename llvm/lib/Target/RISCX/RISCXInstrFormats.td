class RISCXInst<dag outs, dag ins, string asmstr, list<dag> pattern>
  : Instruction {
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

class I<dag outs, dag ins, string asmstr, list<dag> pattern>
  : RISCXInst<outs, ins, asmstr, pattern> {
}

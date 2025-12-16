class RISCXReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let Namespace = "RISCX";
  let AltNames = alt;
}

def ABIRegAltName : RegAltNameIndex;

let RegAltNameIndices = [ABIRegAltName] in {
  let isConstant = true in {
    def X0 : RISCXReg<0, "x0", ["zero"]>;
  }
  // 与以下定义方式等价
  // def X0  : RISCXReg<0, "x0", ["zero"]> {
  //   let isConstant = true;
  // }
  def X1  : RISCXReg<1,  "x1",  ["ra"]>;
  def X2  : RISCXReg<2,  "x2",  ["sp"]>;
  def X10 : RISCXReg<10, "x10", ["a0"]>;
  def X11 : RISCXReg<11, "x11", ["a1"]>;
}

def GPR : RegisterClass<"RISCX", [i32], 32, (add
  X0, X1, X2, X10, X11
)>;

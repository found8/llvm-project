defvar RISCX_MAX_BLOCK_SIZE_X = 1024;
defvar RISCX_MAX_BLOCK_SIZE_Y = 1024;
defvar RISCX_MAX_BLOCK_SIZE_Z = 64;

// class RISCXReadPreloadRegisterIntrinsic<
//     list<IntrinsicProperty> ExtraAttrs = []>
//     : DefaultAttrsIntrinsic<[llvm_i32_ty], [],
//                             !listconcat([NoUndef<RetIndex>, IntrNoMem,
//                                          IntrSpeculatable],
//                                         ExtraAttrs)>;

// class RISCXReadPreloadRegisterIntrinsicNamed<
//     string name, list<IntrinsicProperty> ExtraAttrs = []>
//     : RISCXReadPreloadRegisterIntrinsic<ExtraAttrs>, ClangBuiltin<name>;

class RISCXBuiltin :
  ClangBuiltin<!strconcat("__", !substr(NAME, !size("int_")))> {
    assert !eq(!substr(NAME, 0, !size("int_riscx_")), "int_riscx_"),
           "RISCXBuiltin must be a RISCX intrinsic starting with 'int_riscx_'";
}

let TargetPrefix = "riscx" in {

class RISCXReadSRegIntrinsicNB_r32<list<IntrinsicProperty> properties = []>
  : DefaultAttrsIntrinsic<[llvm_i32_ty], [],
      !listconcat([IntrNoMem, IntrSpeculatable, NoUndef<RetIndex>], properties)>;

class RISCXReadSRegIntrinsic_r32<list<IntrinsicProperty> properties = []>
  : RISCXReadSRegIntrinsicNB_r32<properties>,
    RISCXBuiltin;
    
// multiclass RISCXReadPreloadRegisterIntrinsic_xyz_named<
//     string prefix, list<IntrinsicProperty> ExtraAttrs = []> {
// def _x : RISCXReadPreloadRegisterIntrinsicNamed<!strconcat(prefix, "_x"),
//                                                     ExtraAttrs>;
// def _y : RISCXReadPreloadRegisterIntrinsicNamed<!strconcat(prefix, "_y"),
//                                                     ExtraAttrs>;
// def _z : RISCXReadPreloadRegisterIntrinsicNamed<!strconcat(prefix, "_z"),
//                                                     ExtraAttrs>;
// }

multiclass RISCXReadSRegIntrinsic_v4i32<list<list<IntrinsicProperty>> properties = [[], [], [], []]> {
  assert !eq(!size(properties), 4), "properties must be a list of 4 lists";
// FIXME: Do we need the 128-bit integer type version?
//    def _r64   : Intrinsic<[llvm_i128_ty],   [], [IntrNoMem, IntrSpeculatable]>;

// FIXME: Enable this once v4i32 support is enabled in back-end.
//    def _v4i16 : Intrinsic<[llvm_v4i32_ty], [], [IntrNoMem, IntrSpeculatable]>;
  defvar suffixes = ["_x", "_y", "_z", "_w"];
  foreach i = !range(suffixes) in
    def suffixes[i] : RISCXReadSRegIntrinsic_r32<properties[i]>;
}

// //===----------------------------------------------------------------------===//
// // ABI Special Intrinsics
// //===----------------------------------------------------------------------===//

// defm int_riscx_workitem_id
//     : RISCXReadPreloadRegisterIntrinsic_xyz_named<
//           "__riscx_workitem_id", [Range<RetIndex, 0, 1024>]>;

defm int_riscx_read_sreg_tid
  : RISCXReadSRegIntrinsic_v4i32<[[Range<RetIndex, 0, RISCX_MAX_BLOCK_SIZE_X>],
                                [Range<RetIndex, 0, RISCX_MAX_BLOCK_SIZE_Y>],
                                [Range<RetIndex, 0, RISCX_MAX_BLOCK_SIZE_Z>],
                                [Range<RetIndex, 0, 1>]]>;

defm int_riscx_read_sreg_ntid
  : RISCXReadSRegIntrinsic_v4i32<[[Range<RetIndex, 1, !add(RISCX_MAX_BLOCK_SIZE_X, 1)>],
                                [Range<RetIndex, 1, !add(RISCX_MAX_BLOCK_SIZE_Y, 1)>],
                                [Range<RetIndex, 1, !add(RISCX_MAX_BLOCK_SIZE_Z, 1)>],
                                [Range<RetIndex, 0, 1>]]>;

// Exit
def int_riscx_exit : RISCXBuiltin,
    Intrinsic<[], [], [IntrConvergent, IntrInaccessibleMemOnly, IntrNoReturn]>;

} // TargetPrefix = "riscx"
#!/bin/bash

# if [ -d "build" ]; then
#    rm -rf build
# fi
#
# mkdir build
cd build

if [[ $1 == "rebuild" ]]; then
   cmake -G Ninja ../llvm \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_C_COMPILER=clang \
      -DCMAKE_CXX_COMPILER=clang++ \
      -DLLVM_TARGETS_TO_BUILD="Mips;Cpu0" \
      -DLLVM_ENABLE_PROJECTS="clang" \
      -DLLVM_OPTIMIZED_TABLEGEN=On \
      -DBUILD_SHARED_LIBS=ON \
      -DLLVM_PARALLEL_COMPILE_JOBS=16 \
      -DLLVM_PARALLEL_LINK_JOBS=8
fi
#cmake --build . -- -j20
time ninja

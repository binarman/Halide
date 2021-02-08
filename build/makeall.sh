export LLVM_ROOT=/mnt/linuxStorage/llvm/install
export LLVM_CONFIG=$LLVM_ROOT/bin/llvm-config
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=~/ops/codegen_experiments/halide/Halide/install/ ../
make -j8 install

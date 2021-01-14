Halide_DIR=../../install cmake -DCMAKE_BUILD_TYPE=Release ../
make -j8 halide_blas \
linear_algebra/src/halide_scopy_impl.a \
linear_algebra/src/halide_scopy_impl.runtime.a \
linear_algebra/src/halide_dcopy_impl.a \
linear_algebra/src/halide_dcopy_impl.runtime.a \
linear_algebra/src/halide_sscal_impl.a \
linear_algebra/src/halide_sscal_impl.runtime.a \
linear_algebra/src/halide_dscal_impl.a \
linear_algebra/src/halide_dscal_impl.runtime.a \
linear_algebra/src/halide_saxpy_impl.a \
linear_algebra/src/halide_saxpy_impl.runtime.a \
linear_algebra/src/halide_daxpy_impl.a \
linear_algebra/src/halide_daxpy_impl.runtime.a \
linear_algebra/src/halide_sdot.a \
linear_algebra/src/halide_sdot.runtime.a \
linear_algebra/src/halide_ddot.a \
linear_algebra/src/halide_ddot.runtime.a \
linear_algebra/src/halide_sasum.a \
linear_algebra/src/halide_sasum.runtime.a \
linear_algebra/src/halide_dasum.a \
linear_algebra/src/halide_dasum.runtime.a \
linear_algebra/src/halide_sgemv_notrans.a \
linear_algebra/src/halide_sgemv_notrans.runtime.a \
linear_algebra/src/halide_dgemv_notrans.a \
linear_algebra/src/halide_dgemv_notrans.runtime.a \
linear_algebra/src/halide_sgemv_trans.a \
linear_algebra/src/halide_sgemv_trans.runtime.a \
linear_algebra/src/halide_dgemv_trans.a \
linear_algebra/src/halide_dgemv_trans.runtime.a \
linear_algebra/src/halide_sger_impl.a \
linear_algebra/src/halide_sger_impl.runtime.a \
linear_algebra/src/halide_dger_impl.a \
linear_algebra/src/halide_dger_impl.runtime.a \
linear_algebra/src/halide_sgemm_notrans.a \
linear_algebra/src/halide_sgemm_notrans.runtime.a \
linear_algebra/src/halide_dgemm_notrans.a \
linear_algebra/src/halide_dgemm_notrans.runtime.a \
linear_algebra/src/halide_sgemm_transA.a \
linear_algebra/src/halide_sgemm_transA.runtime.a \
linear_algebra/src/halide_dgemm_transA.a \
linear_algebra/src/halide_dgemm_transA.runtime.a \
linear_algebra/src/halide_sgemm_transB.a \
linear_algebra/src/halide_sgemm_transB.runtime.a \
linear_algebra/src/halide_dgemm_transB.a \
linear_algebra/src/halide_dgemm_transB.runtime.a \
linear_algebra/src/halide_sgemm_transAB.a \
linear_algebra/src/halide_sgemm_transAB.runtime.a \
linear_algebra/src/halide_dgemm_transAB.a \
linear_algebra/src/halide_dgemm_transAB.runtime.a

cd linear_algebra/benchmarks
/usr/custom/android_ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android29-clang++ -O3 -DNDEBUG ../../../linear_algebra/benchmarks/halide_benchmarks.cpp -I ../../../../include/ -I ../../../linear_algebra/src/ -I ../src/ -I ../../../../tools/ -o halide_benchmarks ../src/libhalide_blas.a ../src/halide_scopy_impl.a ../src/halide_scopy_impl.runtime.a ../src/halide_dcopy_impl.a ../src/halide_dcopy_impl.runtime.a ../src/halide_sscal_impl.a ../src/halide_sscal_impl.runtime.a ../src/halide_dscal_impl.a ../src/halide_dscal_impl.runtime.a ../src/halide_saxpy_impl.a ../src/halide_saxpy_impl.runtime.a ../src/halide_daxpy_impl.a ../src/halide_daxpy_impl.runtime.a ../src/halide_sdot.a ../src/halide_sdot.runtime.a ../src/halide_ddot.a ../src/halide_ddot.runtime.a ../src/halide_sasum.a ../src/halide_sasum.runtime.a ../src/halide_dasum.a ../src/halide_dasum.runtime.a ../src/halide_sgemv_notrans.a ../src/halide_sgemv_notrans.runtime.a ../src/halide_dgemv_notrans.a ../src/halide_dgemv_notrans.runtime.a ../src/halide_sgemv_trans.a ../src/halide_sgemv_trans.runtime.a ../src/halide_dgemv_trans.a ../src/halide_dgemv_trans.runtime.a ../src/halide_sger_impl.a ../src/halide_sger_impl.runtime.a ../src/halide_dger_impl.a ../src/halide_dger_impl.runtime.a ../src/halide_sgemm_notrans.a ../src/halide_sgemm_notrans.runtime.a ../src/halide_dgemm_notrans.a ../src/halide_dgemm_notrans.runtime.a ../src/halide_sgemm_transA.a ../src/halide_sgemm_transA.runtime.a ../src/halide_dgemm_transA.a ../src/halide_dgemm_transA.runtime.a ../src/halide_sgemm_transB.a ../src/halide_sgemm_transB.runtime.a ../src/halide_dgemm_transB.a ../src/halide_dgemm_transB.runtime.a ../src/halide_sgemm_transAB.a ../src/halide_sgemm_transAB.runtime.a ../src/halide_dgemm_transAB.a ../src/halide_dgemm_transAB.runtime.a -ldl -llog

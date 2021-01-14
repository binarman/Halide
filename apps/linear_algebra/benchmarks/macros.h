#include "halide_benchmark.h"

#ifdef ENABLE_FTZ_DAZ
#if defined(__i386__) || defined(__x86_64__)
#include <pmmintrin.h>
#include <xmmintrin.h>
#endif  // defined(__i386__) || defined(__x86_64__)
#endif

inline void set_math_flags() {
#ifdef ENABLE_FTZ_DAZ

#if defined(__i386__) || defined(__x86_64__)
    // Flush denormals to zero (the FTZ flag).
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    // Interpret denormal inputs as zero (the DAZ flag).
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
#endif  // defined(__i386__) || defined(__x86_64__)

#if defined(__arm__) || defined(__aarch64__)
    intptr_t fpsr = 0;

    // Get the FP status register
#if defined(__aarch64__)
    asm volatile("mrs %0, fpcr"
                 : "=r"(fpsr));
#else
    asm volatile("vmrs %0, fpscr"
                 : "=r"(fpsr));
#endif

    // Setting this is like setting FTZ+DAZ on x86
    constexpr intptr_t flush_to_zero = (1 << 24 /* FZ */);
    fpsr |= flush_to_zero;

    // Set the FP status register
#if defined(__aarch64__)
    asm volatile("msr fpcr, %0"
                 :
                 : "ri"(fpsr));
#else
    asm volatile("vmsr fpscr, %0"
                 :
                 : "ri"(fpsr));
#endif

#endif  // defined(__arm__) || defined(__aarch64__)

#endif  // ENABLE_FTZ_DAZ
}

#define time_it(code)                                                        \
    set_math_flags();                                                        \
    double elapsed = 0;                                                      \
    for (int iters = 1;; iters *= 2) {                                       \
        /* Best of 5 */                                                      \
        elapsed = 1e6 * Halide::Tools::benchmark(5, iters, [&]() { code; }); \
        /* spend at least 5x20ms benchmarking */                             \
        if (elapsed * iters > 20000) {                                       \
            break;                                                           \
        }                                                                    \
    }

#define L1GFLOPS(N) 2.0 * N * 1e-3 / elapsed
#define L1Benchmark(benchmark, type, code)              \
    virtual void bench_##benchmark(int N) override {    \
        Scalar alpha = random_scalar();                 \
        (void)alpha;                                    \
        Vector x(random_vector(N));                     \
        Vector y(random_vector(N));                     \
                                                        \
        time_it(code)                                   \
                                                        \
                std::cout                               \
            << std::setw(8) << name                     \
            << std::setw(15) << type << #benchmark      \
            << std::setw(8) << std::to_string(N)        \
            << std::setw(20) << std::to_string(elapsed) \
            << std::setw(20) << L1GFLOPS(N)             \
            << "\n";                                    \
    }

#define L2GFLOPS(N) (2.0 + N) * N * 1e-3 / elapsed
#define L2Benchmark(benchmark, type, code)              \
    virtual void bench_##benchmark(int N) override {    \
        Scalar alpha = random_scalar();                 \
        Scalar beta = random_scalar();                  \
        (void)alpha;                                    \
        (void)beta;                                     \
        Vector x(random_vector(N));                     \
        Vector y(random_vector(N));                     \
        Matrix A(random_matrix(N));                     \
                                                        \
        time_it(code)                                   \
                                                        \
                std::cout                               \
            << std::setw(8) << name                     \
            << std::setw(15) << type << #benchmark      \
            << std::setw(8) << std::to_string(N)        \
            << std::setw(20) << std::to_string(elapsed) \
            << std::setw(20) << L2GFLOPS(N)             \
            << "\n";                                    \
    }

#define FCGFLOPS(M, N) M * N * 1e-3 / elapsed
#define CONCAT(x,y) x##y
#define FCBenchmark(benchmark, in_size, out_size, type)              \
    virtual void bench_fc_##out_size##x##in_size() override {    \
        Vector x(random_vector(in_size));               \
        Vector y(random_vector(out_size));              \
        Matrix A(random_matrix(out_size, in_size));     \
                                                        \
        time_it(benchmark##_##out_size##x##in_size(A.raw_buffer(), x.raw_buffer(), y.raw_buffer(), y.raw_buffer()))               \
                                                        \
                std::cout                               \
            << std::setw(8) << "halide_fc"                     \
            << std::setw(15) << type      \
            << std::setw(8) << std::to_string(out_size) << "x" << std::to_string(in_size)     \
            << std::setw(20) << std::to_string(elapsed) \
            << std::setw(20) << FCGFLOPS(in_size, out_size)          \
            << "\n";                                    \
    }

#define L3GFLOPS(N) (3.0 + N) * N *N * 1e-3 / elapsed
#define L3Benchmark(benchmark, type, code)              \
    virtual void bench_##benchmark(int N) override {    \
        Scalar alpha = random_scalar();                 \
        Scalar beta = random_scalar();                  \
        Matrix A(random_matrix(N));                     \
        Matrix B(random_matrix(N));                     \
        Matrix C(random_matrix(N));                     \
                                                        \
        time_it(code)                                   \
                                                        \
                std::cout                               \
            << std::setw(8) << name                     \
            << std::setw(15) << type << #benchmark      \
            << std::setw(8) << std::to_string(N)        \
            << std::setw(20) << std::to_string(elapsed) \
            << std::setw(20) << L3GFLOPS(N)             \
            << "\n";                                    \
    }

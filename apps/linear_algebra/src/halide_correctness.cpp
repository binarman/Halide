#include "HalideBuffer.h"
#include "halide_blas.h"
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using Buffer = Halide::Runtime::Buffer<float>;

std::random_device rand_dev;
std::default_random_engine rand_eng{rand_dev()};

template <typename T>
T random() {
  std::uniform_real_distribution<T> uniform_dist(0.0, 1.0);
  return uniform_dist(rand_eng);
}

Buffer random_vector(int N, float value) {
  Buffer buff(N);
  float *x = buff.data();
  for (int i = 0; i < N; ++i) {
    x[i] = value;//random<float>();
  }
  return buff;
}

Buffer random_matrix(int N, int M) {
  Buffer buff(M, N); // M - inputs, N - outputs
  float *A = buff.data();
  for (int i = 0; i < N * M; ++i) {
//    A[i] = i;//random<float>();
    A[i] = 0.f;
    if (i == 1)
      A[i] = 1.f;
  }
  return buff;
}

void naive_mult(int N, int M, const float *A, const float *x, const float *y, float *r) {
  for (int i = 0; i < N; ++i) {
    r[i] = y[i];
    for (int j = 0; j < M; ++j)
      r[i] += A[i*M + j] * x[j];
  }
}

#define TEST(N, M) \
{\
  Buffer A = random_matrix(N, M);\
  Buffer x = random_vector(M, 1.f);\
  Buffer y = random_vector(N, 0.f);\
  Buffer r(N);\
  for (int i = 0; i < N; ++i)\
    r.data()[i] = 0.f;\
  std::cout << "run halide test " #N "x" #M  << std::endl;\
  halide_sfc_##N##x##M(A.raw_buffer(), x.raw_buffer(), y.raw_buffer(), r.raw_buffer());\
  std::cout << "run reference implementation" << std::endl;\
  float ref_output[N];\
  naive_mult(N, M, A.data(), x.data(), y.data(), ref_output);\
  for (int i = 0; i < N; ++i) {\
    float diff = std::abs(ref_output[i] - r.data()[i]);\
    float min_value = std::min(std::abs(ref_output[i]), std::abs(r.data()[i]));\
    if (diff / min_value > 1e-6) {\
      std::cout << "diff! index " << i << " values: " << ref_output[i] << " vs " << r.data()[i] << "\n";\
    }\
  }\
}

int main()
{
  TEST(48, 16);
  TEST(48, 512);
  TEST(1152, 512);
  TEST(1152, 384);
  TEST(1001, 1024);
  TEST(1001, 1280);
  TEST(1001, 2048);
  TEST(1001, 2048);
  TEST(4, 4000);
  std::cout << "FINISHED\n";
  return 0;
}
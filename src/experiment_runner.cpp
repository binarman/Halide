#include "libfunc.h"
#include "HalideRuntime.h"
#include "Buffer.h"

int main() {
  constexpr int x_s = 10;
  constexpr int y_s = 20;
  Halide::Runtime::Buffer<float> x(x_s);
  Halide::Runtime::Buffer<int32_t> y(y_s);
  void *args [] = {x.raw_buffer(), y.raw_buffer()};
  united_argv(args);
  for (int i = 0; i < x_s; ++i)
    std::cout << "x " << x.data()[i] << "\n";
  for (int i = 0; i < y_s; ++i)
    std::cout << "y " << y.data()[i] << "\n";
  return 0;
}

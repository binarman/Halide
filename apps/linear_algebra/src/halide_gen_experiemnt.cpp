#include "Halide.h"

void gen_add(const Halide::Func &input, Halide::Func &add) {
  Halide::Var i("i");
  Halide::Var j("j");
  Halide::Func bias("constant");
  float bias_data[40] = {1.f, 2.f, 3.f};
  Halide::Buffer<float> constant_bias(bias_data, 40);
//  bias(j) = Halide::select(j == 0, 1.f,
//                           j == 1, 2.f,
//                           3.f);
  add(i) = input(i) + constant_bias(i);
  add.output_buffer().dim(0).set_extent(30);
}

void gen_mul(const Halide::Func &input, Halide::Func &mul) {
  Halide::Var i("i");
  mul(i) = input(i) * 2.f;
}

void gen_generic_add(const Halide::Func &a, const Halide::Func &b) {
//  a.output_buffer().dim(0).min().as()
}

int main(){
  Halide::ImageParam input(Halide::Float(32), 1);
  Halide::Func add("add");
  gen_add(input, add);
  Halide::Func mul("mul");
  gen_mul(add, mul);
  const Halide::Internal::Variable &v = *add.output_buffer().dim(0).extent().as<Halide::Internal::Variable>();
  std::cout << Halide::Internal::is_const(add.output_buffer().dim(0).extent()) << "\n";
  mul.compile_to_lowered_stmt("example.txt", {input}, Halide::StmtOutputFormat::HTML);
  return 0;
}

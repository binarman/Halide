#include "Halide.h"

int main(){
  Halide::Func f;
  Halide::Var i("i");
  f(i) = i;
  f.output_buffer().dim(0).set_extent(10);
  const Halide::Internal::Variable *v = f.output_buffer().dim(0).extent().as<Halide::Internal::Variable>();
  v->param.type()
//  v->param.
  Halide::Internal::is_const(v);
  return 0;
}
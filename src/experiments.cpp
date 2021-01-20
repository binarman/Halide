#include "Halide.h"

int main(){
  Halide::Func f("foo");
  Halide::Func g("bar");
//  Halide::Func u("united");
  Halide::Var i("i");
  Halide::Var j("j");
  f(i) = Halide::cast<float_t>(i)+1.f;
  g(i) = i*2;
  Halide::Pipeline pipeline({f, g});

//  Halide::Tuple t = {f(i), g(i)};
  f.output_buffers()[0].dim(0).set_extent(10);
  g.output_buffers()[0].dim(0).set_extent(20);
  f.compute_root();
  g.compute_root();
//  u.output_buffers()[0].dim(0).set_extent(5);
//  u.compute_root();

//  u(i) = t;
//  u.compile_to_lowered_stmt("dump.html", {}, Halide::StmtOutputFormat::HTML);
//  u.compile_to_object("func.o", {});
//  u.compile_to_header("libfunc.h", {});

  pipeline.compile_to_lowered_stmt("dump.html", {}, Halide::StmtOutputFormat::HTML);
  pipeline.compile_to_object("func.o", {}, "united");
  pipeline.compile_to_header("libfunc.h", {}, "united");

//  const Halide::Internal::Variable *v = f.output_buffer().dim(0).extent().as<Halide::Internal::Variable>();
//  v->param.type()
//  Halide::Internal::is_const(v);
  return 0;
}

// heck what halide generate for multioutput
// find subgraph
//

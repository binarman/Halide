#include "Halide.h"

Halide::Func MatMul(Halide::Func A, Halide::Func B)
{
  Halide::Var i, j;
  Halide::Func mult("matmul");

  Halide::RDom k(0, 2);//A.output_buffer().dim(0).extent());
  mult(i,j) += A(k,j)*B(i, k);
  return mult;
}

Halide::Func NaiveConv2d(Halide::Func W, Halide::Func input, int stride_x, int stride_y, int pad_x[2], int pad_y[2])
{
  // todo
}

Halide::Func im2col()
{
  // todo
}

int main(){
  Halide::Var i("i");
  Halide::Var j("j");
  Halide::Buffer<float> A(2, 2, "A");
  A.data()[0] = 1.0f;
  A.data()[1] = 2.0f;
  A.data()[2] = 3.0f;
  A.data()[3] = 4.0f;

  Halide::Func func_A;

  Halide::ImageParam input_param(Halide::Type(Halide::Type::Float, 32, 1), 2);

  std::vector<Halide::Expr> args = {i, j};
  func_A(args) = A(i,j) + input_param(i, j);

  func_A.compile_to_header("func_A.h", {input_param}, "generated_func");

  return 0;

  Halide::Func test = MatMul(func_A, func_A);

  Halide::Buffer<float> output(2, 2, "O");

  test.compile_to_lowered_stmt("/proc/self/fd/0", {}, Halide::StmtOutputFormat::Text);

  test.realize(output);

  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 2; ++j)
      std::cout << output(j, i) << " ";
    std::cout << std::endl;
  }
  return 0;



  Halide::Func f("foo");
  Halide::Func g("bar");
//  Halide::Func u("united");

  f(i) = Halide::cast<float_t>(i)+1.f;
  g(i) = i*2;
  Halide::Pipeline pipeline({f, g});

  Halide::Func ff;
  ff(i,j) = f(1) + f(i) * g(j);

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

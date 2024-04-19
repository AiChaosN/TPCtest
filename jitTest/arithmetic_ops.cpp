
#include "codegen/arithmetic_ops.hpp"

#include <gtest/gtest.h>
#include <time.h>
#include "codegen/compiler.hpp"
#include "codegen/module.hpp"
#include "codegen/module_builder.hpp"
#include "codegen/statements.hpp"

int main() {
  clock_t start, end;
  start = clock();
  auto comp = codegen::compiler{};
  auto builder = codegen::module_builder(comp, "signed_integer_arithmetic");

  auto add2 = builder.create_function<int32_t(int32_t, int32_t)>(
      "add2", [](codegen::value<int32_t> x, codegen::value<int32_t> y) { codegen::return_(x + y); });

  auto add4 = builder.create_function<int32_t(int32_t, int32_t, int32_t, int32_t)>(
      "add4", [](codegen::value<int32_t> x, codegen::value<int32_t> y, codegen::value<int32_t> z,
                 codegen::value<int32_t> w) { codegen::return_(x + y + z + w); });

  auto sub_add4 = builder.create_function<int32_t(int32_t, int32_t, int32_t, int32_t)>(
      "sub_add4", [](codegen::value<int32_t> x, codegen::value<int32_t> y, codegen::value<int32_t> z,
                     codegen::value<int32_t> w) { codegen::return_(x - y + z - w); });

  auto mul_div_mod2 = builder.create_function<int32_t(int32_t, int32_t)>(
      "mul_div_mod2",
      [](codegen::value<int32_t> x, codegen::value<int32_t> y) { codegen::return_((x / y) * y + x % y); });
    auto uadd2 = builder.create_function<uint32_t(uint32_t, uint32_t)>(
      "uadd2", [](codegen::value<uint32_t> x, codegen::value<uint32_t> y) { codegen::return_(x + y); });

  auto uadd4 = builder.create_function<uint32_t(uint32_t, uint32_t, uint32_t, uint32_t)>(
      "uadd4", [](codegen::value<uint32_t> x, codegen::value<uint32_t> y, codegen::value<uint32_t> z,
                 codegen::value<uint32_t> w) { codegen::return_(x + y + z + w); });

  auto usub_add4 = builder.create_function<uint32_t(uint32_t, uint32_t, uint32_t, uint32_t)>(
      "usub_add4", [](codegen::value<uint32_t> x, codegen::value<uint32_t> y, codegen::value<uint32_t> z,
                     codegen::value<uint32_t> w) { codegen::return_(x - y + z - w); });

  auto umul_div_mod2 = builder.create_function<uint32_t(uint32_t, uint32_t)>(
      "umul_div_mod2",
      [](codegen::value<uint32_t> x, codegen::value<uint32_t> y) { codegen::return_((x / y) * y + x % y); });

    auto fadd2 =
      builder.create_function<float(float, float)>("fadd2", [](codegen::value<float> x, codegen::value<float> y) {
        codegen::return_(x + y + codegen::constant<float>(0.5f));
      });

  auto fadd4 = builder.create_function<float(float, float, float, float)>(
      "fadd4", [](codegen::value<float> x, codegen::value<float> y, codegen::value<float> z, codegen::value<float> w) {
        codegen::return_(x + y + z + w);
      });

  auto fsub_add4 = builder.create_function<float(float, float, float, float)>(
      "fsub_add4", [](codegen::value<float> x, codegen::value<float> y, codegen::value<float> z,
                     codegen::value<float> w) { codegen::return_(x - y + z - w); });

  auto fmul_div_mod2 = builder.create_function<float(float, float)>(
      "fmul_div_mod2", [](codegen::value<float> x, codegen::value<float> y) { codegen::return_((x / y) * y + x % y); });

    auto and2 = builder.create_function<int32_t(int32_t, int32_t)>(
      "and2", [](codegen::value<int32_t> x, codegen::value<int32_t> y) { codegen::return_(x & y); });

  auto and4 = builder.create_function<int32_t(int32_t, int32_t, int32_t, int32_t)>(
      "and4", [](codegen::value<int32_t> x, codegen::value<int32_t> y, codegen::value<int32_t> z,
                 codegen::value<int32_t> w) { codegen::return_(x & y & z & w); });

  auto and_or4 = builder.create_function<int32_t(int32_t, int32_t, int32_t, int32_t)>(
      "and_or4", [](codegen::value<int32_t> x, codegen::value<int32_t> y, codegen::value<int32_t> z,
                    codegen::value<int32_t> w) { codegen::return_((x & y) | (z & w)); });

  auto and_or_xor4 = builder.create_function<int32_t(int32_t, int32_t, int32_t, int32_t)>(
      "and_or_xor4", [](codegen::value<int32_t> x, codegen::value<int32_t> y, codegen::value<int32_t> z,
                        codegen::value<int32_t> w) { codegen::return_((x | y) ^ (z & w)); });

  auto module = std::move(builder).build();
  end = clock();
  printf("compile time:%f\n", (float)(end-start)*1000/CLOCKS_PER_SEC);
  auto add2_ptr = module.get_address(add2);
  EXPECT_EQ(add2_ptr(1, 2), 3);

  auto add4_ptr = module.get_address(add4);
  EXPECT_EQ(add4_ptr(1, 2, 3, 4), 10);

  auto sub_add4_ptr = module.get_address(sub_add4);
  EXPECT_EQ(sub_add4_ptr(1, 2, 3, 4), -2);

  auto mul_div_mod2_ptr = module.get_address(mul_div_mod2);
  EXPECT_EQ(mul_div_mod2_ptr(7, 2), 7);
  EXPECT_EQ(mul_div_mod2_ptr(11, 3), 11);
  EXPECT_EQ(mul_div_mod2_ptr(4, -3), 4);
  EXPECT_EQ(mul_div_mod2_ptr(1, -7), 1);


  auto uadd2_ptr = module.get_address(uadd2);
  EXPECT_EQ(add2_ptr(1, 2), 3);

  auto uadd4_ptr = module.get_address(uadd4);
  EXPECT_EQ(add4_ptr(1, 2, 3, 4), 10);

  auto usub_add4_ptr = module.get_address(usub_add4);
  EXPECT_EQ(sub_add4_ptr(1, 2, 3, 4), uint32_t(-2));

  auto umul_div_mod2_ptr = module.get_address(umul_div_mod2);
  EXPECT_EQ(mul_div_mod2_ptr(7, 2), 7);
  EXPECT_EQ(mul_div_mod2_ptr(11, 3), 11);
  EXPECT_EQ(mul_div_mod2_ptr(4, uint32_t(-3)), 4);
  EXPECT_EQ(mul_div_mod2_ptr(1, uint32_t(-7)), 1);

  auto fadd2_ptr = module.get_address(fadd2);
  EXPECT_EQ(fadd2_ptr(1, 2), 3.5f);

  auto fadd4_ptr = module.get_address(fadd4);
  EXPECT_EQ(fadd4_ptr(1, 2, 3, 4), 10);

  auto fsub_add4_ptr = module.get_address(fsub_add4);
  EXPECT_EQ(fsub_add4_ptr(1, 2, 3, 4), -2);

  auto fmul_div_mod2_ptr = module.get_address(fmul_div_mod2);
  EXPECT_EQ(mul_div_mod2_ptr(7, 2), 8);
  EXPECT_EQ(mul_div_mod2_ptr(11, 3), 13);
  EXPECT_EQ(mul_div_mod2_ptr(4, -3), 5);
  EXPECT_EQ(mul_div_mod2_ptr(1, -7), 2);

  auto and2_ptr = module.get_address(and2);
  EXPECT_EQ(and2_ptr(1, 2), 0);
  EXPECT_EQ(and2_ptr(1, 3), 1);

  auto and4_ptr = module.get_address(and4);
  EXPECT_EQ(and4_ptr(3, 3, 7, 2), 2);

  auto and_or4_ptr = module.get_address(and_or4);
  EXPECT_EQ(and_or4_ptr(0x10, 0x30, 3, 6), 0x12);

  auto and_or_xor4_ptr = module.get_address(and_or_xor4);
  EXPECT_EQ(and_or_xor4_ptr(3, 6, 11, 14), 13);

  end = clock();
  printf("execution time:%f\n", (float)(end-start)*1000/CLOCKS_PER_SEC);

}

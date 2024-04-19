#include "codegen/arithmetic_ops.hpp"
#include <gtest/gtest.h>
#include <time.h>
#include "codegen/compiler.hpp"
#include "codegen/module.hpp"
#include "codegen/module_builder.hpp"
#include "codegen/statements.hpp"
#include <cstdio>

int main() {
  clock_t start, end;
  start = clock();
  auto comp = codegen::compiler{};
  auto builder = codegen::module_builder(comp, "hello_world");

  auto hello = builder.create_function<void(int32_t*)>(
     "hello", [](codegen::value<int32_t*> x) { printf("hello world:%d\n", codegen::load(x)); codegen::return_();});
  auto module = std::move(builder).build();
  end = clock();
  printf("compile time:%f\n", (float)(end-start)*1000/CLOCKS_PER_SEC);
  int32_t p = 0;
  auto hello_ptr = module.get_address(hello);
  hello_ptr(&p);
  end = clock();
  printf("execution time:%f\n", (float)(end-start)*1000/CLOCKS_PER_SEC);
}


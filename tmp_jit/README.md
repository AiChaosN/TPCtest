使用llvm库运行


使用shell命令运行
```shell
clang -S -emit-llvm -o test.ll test.c
lli test.ll
```
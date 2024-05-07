#include "llvm/ADT/STLExtras.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

#include "../src/Table.h"
#include "../src/Structs.h"
#include "../src/q.h"


void main()
{
    // 初始化LLVM
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // 创建JIT
    auto JIT = llvm::orc::LLJITBuilder().create();
    if (!JIT) {
        llvm::errs() << "Failed to create JIT: " << llvm::toString(JIT.takeError());
        return 1;
    }

    // 加载
    llvm::LLVMContext Context;
    llvm::SMDiagnostic Err;
    auto Mod = llvm::parseIRFile("combined.bc", Err, Context);
    if (!Mod) {
        Err.print("JITExample", llvm::errs());
        return 1;
    }

    auto TSM = llvm::orc::ThreadSafeModule(std::move(Mod), std::move(Context));
    if (auto Err = JIT->addIRModule(std::move(TSM))) {
        llvm::errs() << "Failed to add module to JIT: " << llvm::toString(std::move(Err));
        return 1;
    }


    // 查找并执行函数
    auto Sym = JIT->lookup("函数名");
    if (!Sym) {
        llvm::errs() << "Failed to find function: " << llvm::toString(Sym.takeError());
        return 1;
    }

    // 将函数指针转换为正确的类型并调用它
    auto *Func = (int (*)())(intptr_t)Sym->getAddress();
    return Func();






}
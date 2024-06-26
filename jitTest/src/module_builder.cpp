
#include "codegen/module_builder.hpp"

#include <iostream>
#include <fstream>

#include <llvm/Support/raw_os_ostream.h>

#include "codegen/compiler.hpp"
#include "codegen/module.hpp"

namespace codegen {

module_builder::module_builder(compiler& c, std::string const& name)
    : compiler_(&c), context_(std::make_unique<llvm::LLVMContext>()),
      module_(std::make_unique<llvm::Module>(name, *context_)), ir_builder_(*context_),
      source_file_(c.source_directory_ / (name + ".txt")), dbg_builder_(*module_),
      dbg_file_(dbg_builder_.createFile(source_file_.string(), source_file_.parent_path().string())),
      dbg_scope_(dbg_file_) {
  dbg_builder_.createCompileUnit(llvm::dwarf::DW_LANG_C_plus_plus, dbg_file_, "codegen", true, "", 0);
}

module module_builder::build() && {
  {
    std::cout << source_file_ << std::endl;
    auto ofs = std::ofstream(source_file_, std::ios::trunc);
    ofs << source_code_.get();
  }

  dbg_builder_.finalize();

  auto target_triple = compiler_->target_machine_->getTargetTriple();
  module_->setDataLayout(compiler_->data_layout_);
  module_->setTargetTriple(target_triple.str());

  throw_on_error(compiler_->optimize_layer_.add(compiler_->session_.getMainJITDylib(),
                                                llvm::orc::ThreadSafeModule(std::move(module_), std::move(context_))));
  return module{compiler_->session_, compiler_->data_layout_};
}

void module_builder::set_function_attributes(llvm::Function* fn) {
  fn->addFnAttr("target-cpu", llvm::sys::getHostCPUName());
}

unsigned module_builder::source_code_generator::add_line(std::string const& line) {
  source_code_ << std::string(indent_, ' ') << line << "\n";
  return line_no_++;
}

std::string module_builder::source_code_generator::get() const {
  return source_code_.str();
}

void module_builder::declare_external_symbol(std::string const& name, void* address) {
  compiler_->add_symbol(name, address);
}

std::ostream& operator<<(std::ostream& os, module_builder const& mb) {
  auto llvm_os = llvm::raw_os_ostream(os);
  mb.module_->print(llvm_os, nullptr);
  return os;
}

value<bool> true_() {
  return constant(true);
}
value<bool> false_() {
  return constant(false);
}

void return_() {
  auto& mb = *detail::current_builder;
  auto line_no = mb.source_code_.add_line("return;");
  mb.exited_block_ = true;
  mb.ir_builder_.SetCurrentDebugLocation(llvm::DebugLoc::get(line_no, 1, mb.dbg_scope_));
  mb.ir_builder_.CreateRetVoid();
}

} // namespace codegen

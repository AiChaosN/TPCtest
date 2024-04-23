#include "codegen/statements.hpp"

namespace codegen {

void break_() {
  auto& mb = *detail::current_builder;
  assert(mb.current_loop_.break_block_);

  mb.exited_block_ = true;

  auto line_no = mb.source_code_.add_line("break;");
  mb.ir_builder_.SetCurrentDebugLocation(llvm::DebugLoc::get(line_no, 1, mb.dbg_scope_));

  mb.ir_builder_.CreateBr(mb.current_loop_.break_block_);
}

void continue_() {
  auto& mb = *detail::current_builder;
  assert(mb.current_loop_.continue_block_);

  mb.exited_block_ = true;

  auto line_no = mb.source_code_.add_line("continue;");
  mb.ir_builder_.SetCurrentDebugLocation(llvm::DebugLoc::get(line_no, 1, mb.dbg_scope_));

  mb.ir_builder_.CreateBr(mb.current_loop_.continue_block_);
}

} // namespace codegen

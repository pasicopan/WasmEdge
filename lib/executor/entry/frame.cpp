#include "executor/entry/frame.h"

namespace SSVM {
namespace Executor {

/// Constructor of frame entry. See "include/executor/entry/frame.h".
FrameEntry::FrameEntry(
    unsigned int ModuleAddr, unsigned int Arity,
    std::vector<std::unique_ptr<ValueEntry>> &Args,
    const std::vector<std::pair<unsigned int, AST::ValType>> &LocalDefs) {
  /// Set arity.
  this->Arity = Arity;

  /// Set parameters with arguments.
  for (auto Arg = Args.begin(); Arg != Args.end(); Arg++) {
    Locals.push_back(std::make_unique<ValueEntry>(*Arg->get()));
  }

  /// Set local variables with initialization.
  for (auto LocalDef = LocalDefs.begin(); LocalDef != LocalDefs.end();
       LocalDef++) {
    for (unsigned int i = 0; i < LocalDef->first; i++) {
      Locals.push_back(std::make_unique<ValueEntry>(LocalDef->second));
    }
  }
}

/// Getter of local values by index. See "include/executor/entry/frame.h".
ErrCode FrameEntry::getValue(unsigned int Idx, ValueEntry *&Val) {
  /// Check if the index valid.
  if (Locals.size() <= Idx)
    return ErrCode::WrongLocalAddress;

  /// Get value.
  Val = Locals[Idx].get();
  return ErrCode::Success;
}

/// Setter of local values by index. See "include/executor/entry/frame.h".
ErrCode FrameEntry::setValue(unsigned int Idx,
                             std::unique_ptr<ValueEntry> &ValPtr) {
  /// Check if the index valid.
  if (Locals.size() <= Idx)
    return ErrCode::WrongLocalAddress;

  /// Type check is contained in ValueEntry::setValue.
  return Locals[Idx]->setValue(*ValPtr);
}

} // namespace Executor
} // namespace SSVM
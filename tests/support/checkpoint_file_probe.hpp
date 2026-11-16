#pragma once

#include "crown/recovery/session_file.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>

namespace crown::recovery::testing {
// Test-only syscall attempts, not bytes/CPU/allocation counts; event is borrowed.
struct FileEvent {
  FileStage stage;
  bool after;
  std::uint64_t ordinal;
  std::size_t requested;
  std::int64_t result;
  int native_error;
};
struct FileDecision {
  int error_before=0,error_after=0;
  std::size_t maximum_transfer=std::numeric_limits<std::size_t>::max();
  bool zero_entropy=false;
};
// Setter borrows thread-local callback/context; clear before context dies.
using FileHook=FileDecision(*)(const FileEvent&,void*) noexcept;
// Private testing ABI only. Real syscalls still supply all successful results;
// transfers may be shortened and failures inserted before/after actual effects.
void set_file_hook(FileHook,void*) noexcept;
} // namespace crown::recovery::testing

#pragma once
#include "crown/recovery/journal_file.hpp"
#include <limits>
namespace crown::recovery::journal::testing {
// Test syscall seam: real I/O still runs unless denied; this is not a new/malloc seam.
struct FileEvent {
  FileStage stage;bool after;std::uint64_t ordinal;std::size_t requested;
  std::int64_t result;int native_error;
};
struct FileDecision {
  int error_before=0,error_after=0;
  std::size_t maximum_transfer=std::numeric_limits<std::size_t>::max();
  bool zero_entropy=false;
};
// Thread-local callback/context are borrowed; setters do not stack installations.
using FileHook=FileDecision(*)(const FileEvent&,void*) noexcept;
void set_file_hook(FileHook,void*) noexcept;
} // namespace crown::recovery::journal::testing

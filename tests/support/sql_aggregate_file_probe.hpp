#pragma once
#include "crown/recovery/sql_aggregate_files.hpp"
#include <limits>

namespace crown::recovery::sql_aggregate::testing {
// Test-only syscall seam. Real POSIX I/O runs unless denied; this does not count
// or replace allocation. The owner charges every attempted operation, including EINTR.
struct FileEvent {
  FileStage stage; bool after; std::uint64_t ordinal; std::size_t requested;
  std::int64_t result; int native_error;
};
struct FileDecision {
  int error_before=0,error_after=0;
  std::size_t maximum_transfer=std::numeric_limits<std::size_t>::max();
  bool zero_entropy=false;
};
using FileHook=FileDecision(*)(const FileEvent&,void*) noexcept;
// Borrow callback/context on this thread until replaced; installations do not stack.
void set_file_hook(FileHook,void*) noexcept;
} // namespace crown::recovery::sql_aggregate::testing

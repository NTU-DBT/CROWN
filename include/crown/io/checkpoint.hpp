#pragma once

#include "crown/io/batch.hpp"
#include "crown/io/input_options.hpp"
#include "crown/recovery/image.hpp"

namespace crown::io {
struct SourceStateLimits {
  std::uint64_t work=16*1024*1024;
  std::size_t positions=1024,csv_fields=4096;
};
// Native source components for the versioned session envelope. A queue must
// be empty and a reader must have no unacknowledged cached record. Snapshots
// own their positions/fields and retain immutable original-account options.
struct QueueCheckpoint {
  AccountedInputProgress progress;
  QueueMode mode;
  QueueLimits limits;
  InputLimits input_limits;
  bool closed=false;
  std::array<char,64> catalog_sha256{};
  std::uint64_t work=0;
};
struct ReaderCheckpoint {
  AccountedInputOptions options;
  AccountedInputProgress progress;
  recovery::ImageVector<std::size_t> csv_fields;
  std::uint64_t bytes=0,records=0;
  bool header_read=false,ended=false;
  std::array<char,64> catalog_sha256{};
  std::uint64_t work=0;
};
} // namespace crown::io

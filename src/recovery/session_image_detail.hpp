#pragma once

#include "crown/recovery/session_image.hpp"

namespace crown::recovery::detail {
// Only the native codec can adopt these freshly funded options. No ordinary
// InputOptions/WindowOptions graph is materialized inside binary admission.
struct SessionImageAccess {
  static io::AccountedInputOptions input(const resource::MemoryAccount& account,io::AccountedInputOptions::Values&& value) {
    // Nested bytes already use account; adopting their shared control can allocate.
    return io::AccountedInputOptions(account,std::move(value));
  }
  static runtime::AccountedWindowOptions window(runtime::WindowTables tables,std::uint64_t width,
      runtime::WindowFifoPolicy fifo,std::size_t labels,std::size_t bytes,std::uint64_t work) {
    runtime::AccountedWindowOptions result;result.managed_tables=std::move(tables);result.width=width;result.fifo=fifo;
    result.max_labels=labels;result.max_accounted_bytes=bytes;result.command_work_limit=work;return result;
  }
};
struct ValidatedSessionImage {
  // Mutable internal call state, not a capability. Keep validated bytes/limits
  // unchanged: materialization does not repeat the envelope/inner checksums.
  std::string_view bytes;
  InspectedSessionImage inspected;
  runtime::SessionCheckpointLimits state_limits;
  SessionImageLimits limits;
};
struct DecodedSessionImage {
  runtime::SessionCheckpoint state;
  // Borrows immutable input only during restore. Native source/window rows and
  // options own their receiving-account bytes; no extra runtime-image copy.
  std::string_view runtime_bytes;
};
[[nodiscard]] ValidatedSessionImage validate_session_image(std::string_view,
    const runtime::SessionCheckpointLimits&,SessionImageLimits);
[[nodiscard]] DecodedSessionImage materialize_session_image(const resource::MemoryAccount&,const ValidatedSessionImage&);
} // namespace crown::recovery::detail

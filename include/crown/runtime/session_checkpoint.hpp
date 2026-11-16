#pragma once

#include "crown/runtime/session.hpp"
#include "crown/io/checkpoint.hpp"

namespace crown::runtime {
struct SessionCheckpointLimits {
  recovery::ImageLimits image;
  io::SourceStateLimits source;
  WindowStateLimits window;
  patterns::Limits patterns;
  // Native set/directory/field comparisons joining managed base rows to the
  // window's distinct counts. Scalar byte-comparison costs are additional.
  std::uint64_t matching_work=16*1024*1024;
};
struct SessionRestoreOptions {
  BuildOptions build;
  SessionCheckpointLimits limits;
  std::optional<std::uint64_t> memory_limit_bytes;
};
// Complete native quiescent session state, ready for the binary envelope.
// Source options/positions and window rows have funded native ownership;
// runtime_image alone is already a pointer-free binary runtime component.
// This in-memory C++ object is not itself a durable serialized checkpoint.
struct SessionCheckpoint {
  // Moves transfer funded state; mutable fields still need native restore admission.
  SessionCheckpoint()=default;
  SessionCheckpoint(const SessionCheckpoint&)=delete;
  SessionCheckpoint& operator=(const SessionCheckpoint&)=delete;
  SessionCheckpoint(SessionCheckpoint&&) noexcept=default;
  SessionCheckpoint& operator=(SessionCheckpoint&&) noexcept=default;
  static constexpr std::uint32_t legacy_version=1, current_version=2;
  // Undeclared sessions keep their exact v1 wire layout.
  std::uint32_t version=legacy_version;
  SessionState state=SessionState::created;
  SessionInputKind input_kind=SessionInputKind::owned_stream;
  bool input_failed=false,end_of_input=false;
  std::uint64_t committed_sequence=0;
  recovery::EncodedImage runtime_image;
  io::AccountedInputOptions input_options;
  std::optional<io::QueueLimits> queue_limits;
  SnapshotLimits snapshot;
  DeltaOptions delta;
  workload::Options workload;
  // Stopped sessions retain only accepted progress; their source is closed.
  std::variant<io::ReaderCheckpoint,io::QueueCheckpoint,io::AccountedInputProgress> source;
  std::optional<WindowCheckpoint> window;
  std::optional<patterns::Declaration> update_patterns;
  std::uint64_t pattern_origin_sequence=0, pattern_origin_command_sequence=0;
  std::optional<PatternViolation> pattern_violation;
};
} // namespace crown::runtime

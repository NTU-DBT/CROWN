#pragma once

#include "crown/runtime/session_checkpoint.hpp"

namespace crown::recovery {
struct SessionImageLimits {
  ImageLimits envelope{128*1024*1024,512*1024*1024,4096,2'000'000,1024,1024*1024};
  std::uint64_t relation_tokens=4096,managed_capacity=4096;
};
struct SessionImageManifest {
  ImageManifest runtime_manifest;
  std::uint32_t state_version=runtime::SessionCheckpoint::legacy_version;
  runtime::SessionState state=runtime::SessionState::created;
  runtime::SessionInputKind input_kind=runtime::SessionInputKind::owned_stream;
  bool input_failed=false,end_of_input=false;
  std::uint64_t committed_sequence=0,accepted_sequence=0;
};
struct SessionImage {
  // This record owns funded bytes; copying it can allocate and duplicate them.
  // Wire inspection, native restore and durable file publication are separate.
  ImageVector<char> bytes;
  ImageStatistics statistics;
  SessionImageManifest manifest;
};
struct InspectedSessionImage {
  SessionImageManifest manifest;
  runtime::DeltaOptions delta;
  ImageStatistics statistics;
};
// Complete CROWNSI1 session envelope, including its CROWNRI1 runtime component.
// Native state capture supplies the original query account. Inspection validates
// all bytes/checksums/structure before allocation and reserves both parse passes.
// Program/schema/window semantics are additionally checked by session admission.
[[nodiscard]] SessionImage encode_session_image(const resource::MemoryAccount&,
    const runtime::SessionCheckpoint&,const runtime::SessionCheckpointLimits& = {},SessionImageLimits={});
[[nodiscard]] InspectedSessionImage inspect_session_image(std::string_view,
    const runtime::SessionCheckpointLimits& = {},SessionImageLimits={});
inline constexpr std::size_t session_image_header_size=84;
} // namespace crown::recovery

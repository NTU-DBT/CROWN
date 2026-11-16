#pragma once

#include "crown/recovery/generation.hpp"
#include "crown/recovery/local_sink.hpp"

namespace crown::recovery {
struct PlanDescriptorLimits {
  std::uint64_t bytes=64*1024*1024,artifact_bytes=64*1024*1024,
      work=256*1024*1024,fields=1024;
};
struct PlanSelection {
  GenerationRoot predecessor;
  ImageBinding source,target;
  std::uint64_t generation=0,physical_sequence=0,command_sequence=0;
  std::optional<sink::Header> sink_origin;
  // v2 separates the last actual native switch from later metadata selections.
  std::optional<std::uint64_t> last_switch_epoch;
  bool operator==(const PlanSelection&) const=default;
};
struct EncodedPlanDescriptor {
  ImageVector<char> bytes;
  ImageStatistics statistics;
};
struct InspectedPlanDescriptor {
  // Fixed selection metadata owns no artifact bytes; the view borrows input.
  // Keep the descriptor immutable/alive through separate compiler admission.
  PlanSelection selection;
  // Borrows the immutable descriptor. Parsing this compiler input is an
  // explicit compiler boundary; inspection grants no native plan authority.
  std::string_view compiler_artifact;
  ImageStatistics statistics;
};
// Fixed metadata and an opaque compiler artifact, with a whole-frame SHA256.
// The codec checks source/policy continuity and sink-origin framing. Native
// publication separately requires a checked artifact and exact equivalence.
// Work is a conservative four-byte-visit charge per encoded frame byte;
// compiler validation and runtime rebuild have separate grants and counters.
[[nodiscard]] EncodedPlanDescriptor encode_plan_descriptor(const resource::MemoryAccount&,
    const PlanSelection&,std::string_view compiler_artifact,PlanDescriptorLimits={});
[[nodiscard]] InspectedPlanDescriptor inspect_plan_descriptor(std::string_view,PlanDescriptorLimits={});
inline constexpr std::size_t plan_descriptor_header_size=20;
} // namespace crown::recovery

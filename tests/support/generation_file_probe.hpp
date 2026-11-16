#pragma once
#include "crown/recovery/generation.hpp"
#include <limits>
namespace crown::recovery::testing {
// Same ordinal before/after one admitted syscall; requested is the original size.
struct GenerationEvent {
  GenerationStage stage;GenerationTarget target;bool after;
  std::uint64_t ordinal;std::size_t requested;std::int64_t result;int native_error;
};
struct GenerationDecision {
  int error_before=0,error_after=0;
  std::size_t maximum_transfer=std::numeric_limits<std::size_t>::max();
  bool zero_entropy=false;
};
// Only the before decision is applied; context is borrowed until explicitly cleared.
using GenerationHook=GenerationDecision(*)(const GenerationEvent&,void*) noexcept;
void set_generation_hook(GenerationHook,void*) noexcept;
} // namespace crown::recovery::testing

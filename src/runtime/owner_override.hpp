#pragma once
#include <cstdint>

namespace crown::runtime::detail {
// One-shot override of the next SupportRuntime owner id on this thread: a
// keyed DeltaRuntime builds its reference twin under its own stable owner, so
// twin-derived captures and the owner's workload snapshots share one boundary.
inline thread_local std::uint64_t forced_support_owner = 0;
struct ForcedSupportOwner {
  explicit ForcedSupportOwner(std::uint64_t owner) noexcept { forced_support_owner = owner; }
  ~ForcedSupportOwner() { forced_support_owner = 0; }
  ForcedSupportOwner(const ForcedSupportOwner&) = delete;
  ForcedSupportOwner& operator=(const ForcedSupportOwner&) = delete;
};
}  // namespace crown::runtime::detail

#include "arena_owner.hpp"

#include <atomic>
#include <limits>

namespace crown::storage::detail {
std::optional<ArenaOwnerId> try_new_arena_owner() noexcept {
  static std::atomic<std::uint64_t> last{0};
  // Relaxed ordering allocates unique IDs; it does not synchronize arena
  // payload access. Failed owner construction may leave an unpublished gap.
  auto value = last.load(std::memory_order_relaxed);
  for (;;) {
    if (value == std::numeric_limits<std::uint64_t>::max()) return {};
    if (last.compare_exchange_weak(value, value + 1, std::memory_order_relaxed)) return ArenaOwnerId{value + 1};
  }
}
}

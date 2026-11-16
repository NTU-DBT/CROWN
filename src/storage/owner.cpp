#include "owner.hpp"

#include "crown/api/error.hpp"
#include <atomic>
#include <cstdint>
#include <limits>

namespace crown::storage::detail {

std::optional<StorageOwnerId> try_new_storage_owner() noexcept {
  static std::atomic<std::uint64_t> last{0};
  // Only identity uniqueness is synchronized here, not table payloads.
  // CAS retries can contend; no bounded/lock-free progress claim is required.
  auto value = last.load(std::memory_order_relaxed);
  for (;;) {
    if (value == std::numeric_limits<std::uint64_t>::max())
      return {};
    if (last.compare_exchange_weak(value, value + 1, std::memory_order_relaxed))
      return StorageOwnerId{value + 1};
  }
}
StorageOwnerId new_storage_owner() {
  const auto owner = try_new_storage_owner();
  if (!owner) throw Error("storage_overflow", "storage owner IDs exhausted");
  return *owner;
}

}  // namespace crown::storage::detail

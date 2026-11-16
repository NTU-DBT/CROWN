#pragma once

#include "crown/runtime/session.hpp"
#include <compare>
#include <cstddef>
#include <cstdint>
#include <map>

namespace crown::runtime {

// A process-local directory name, not a recovery token or proof capability.
// The directory account identity rejects foreign IDs; ordinals are never reused.
struct QueryId {
  std::uint64_t directory = 0;
  std::uint64_t value = 0;
  auto operator<=>(const QueryId&) const = default;
};

struct QueryDirectoryLimits {
  std::size_t queries = 1024; // Zero admits an empty directory only.
  std::uint64_t memory_bytes = 256U*1024U;
};

// Serial, non-reentrant ownership directory. Each Session keeps its independent
// runtime, queue, account, progress, results and recovery/publication barriers.
// The separate directory budget funds its controller and map nodes; the caller
// owns this fixed-size facade. It is not a combined query-memory allowance.
class IndependentQueries {
 public:
  explicit IndependentQueries(QueryDirectoryLimits = {});
  IndependentQueries(const IndependentQueries&) = delete;
  IndependentQueries& operator=(const IndependentQueries&) = delete;
  IndependentQueries(IndependentQueries&&) = delete;
  IndependentQueries& operator=(IndependentQueries&&) = delete;

  // Reserve directory storage before moving the owner. Failure leaves it with
  // the caller. Session construction/recovery happens at its existing factory.
  [[nodiscard]] QueryId admit(QuerySession::Owner&) &;
  [[nodiscard]] bool contains(QueryId) const noexcept;
  [[nodiscard]] std::size_t size() const noexcept { return entries_.size(); }
  [[nodiscard]] resource::MemoryStatistics directory_memory() const;

  // Borrow survives changes to other entries. It ends at erase/release of this
  // ID or directory destruction. Keep it to avoid directory lookup per update.
  [[nodiscard]] QuerySession& at(QueryId) &;
  [[nodiscard]] const QuerySession& at(QueryId) const &;
  QuerySession& at(QueryId) && = delete;
  const QuerySession& at(QueryId) const && = delete;

  // Transfer preserves the original Session/account; erasure destroys only
  // this owner. Already owning snapshots/results retain their normal lifetimes.
  [[nodiscard]] QuerySession::Owner release(QueryId) &;
  void erase(QueryId) &;

 private:
  using Entry = std::pair<const std::uint64_t,QuerySession::Owner>;
  using Entries = std::map<std::uint64_t,QuerySession::Owner,std::less<std::uint64_t>,
                           resource::MemoryAllocator<Entry>>;
  resource::MemoryAccount account_;
  Entries entries_;
  QueryDirectoryLimits limits_;
  std::uint64_t directory_,next_ = 1;
};
} // namespace crown::runtime

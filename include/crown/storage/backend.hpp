#pragma once

#include "crown/storage/index_work.hpp"
#include <compare>
#include <cstddef>

namespace crown::storage {
enum class StorageBackend { reference_ordered_v1, indexed_chained_v1 };

// Finite per-table component counts, including detached undo-owned records.
struct IndexedLimits {
  std::size_t rows = 0;
  std::size_t indices = 0;
  std::size_t keys = 0;
  std::size_t memberships = 0;
  std::size_t nodes = 0;
  std::size_t directory_slots = 0;
  std::size_t arena_slots = 0;
  std::size_t arena_pins = 0;
  std::size_t journal_entries = 0;
  auto operator<=>(const IndexedLimits&) const = default;
};

// Pre-admission configuration record. The immutable admitted plan binds
// these values. Work is one aggregate allowance per composed operation,
// not a per-table reset or an allocator-byte guarantee.
struct IndexedBackendSpec {
  IndexedLimits per_table;
  IndexWork per_operation;
  auto operator<=>(const IndexedBackendSpec&) const = default;
};
}  // namespace crown::storage

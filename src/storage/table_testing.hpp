#pragma once
#if !defined(CROWN_STORAGE_TESTING) || CROWN_STORAGE_TESTING != 1
#error "StorageTable testing authority requires the coherent testing variant"
#endif
#include "crown/storage/table.hpp"
#include "indexed_testing.hpp"
namespace crown::storage::detail {
// Delegation rejects the reference backend before changing indexed fixture state.
class StorageTableTesting {
 public:
  static void collisions(StorageTable&, CollisionMode);
};
}  // namespace crown::storage::detail

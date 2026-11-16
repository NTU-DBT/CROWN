#pragma once

#if !defined(CROWN_STORAGE_TESTING) || CROWN_STORAGE_TESTING != 1
#error "Indexed testing authority requires a coherent CROWN_STORAGE_TESTING build"
#endif

#include "crown/storage/indexed.hpp"

namespace crown::storage::detail {

enum class CollisionMode { native, same_bucket, same_full_hash };

// Private to the testing storage variant. Not installed, serialized or defined
// in the production binary; never a configurable production hash callback.
// The same-bucket fixture requires a maximum directory capacity <=65536.
class IndexedTesting {
 public:
  static void collisions(IndexedTable&, CollisionMode);
};

}  // namespace crown::storage::detail

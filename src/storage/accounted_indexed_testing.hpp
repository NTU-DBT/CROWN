#pragma once
#if !defined(CROWN_ACCOUNTED_INDEXED_TESTING) || CROWN_ACCOUNTED_INDEXED_TESTING != 1
#error "Accounted indexed testing requires its coherent private variant"
#endif
#include "crown/storage/accounted_indexed.hpp"
namespace crown::storage::detail {
enum class AccountedCollisionMode { native, same_bucket, same_full_hash };
// Collision setup requires fresh/unlocked state; counter seeding requires unlock.
class AccountedIndexedTesting {
 public:
  static void collisions(AccountedIndexedTable&, AccountedCollisionMode);
  enum class Exhausted { tuple_id, index_id, revision };
  static void exhaust(AccountedIndexedTable&, Exhausted);
};
}

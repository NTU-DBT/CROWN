#pragma once
#if !defined(CROWN_ACCOUNTED_INDEXED_TESTING) || CROWN_ACCOUNTED_INDEXED_TESTING != 1
#error "Accounted storage testing requires its coherent private variant"
#endif
#include "crown/storage/accounted_table.hpp"
#include "accounted_indexed_testing.hpp"
namespace crown::storage::detail {
// Delegation rejects the reference backend before changing indexed fixture state.
class AccountedStorageTableTesting {
 public:
  static void collisions(AccountedStorageTable&, AccountedCollisionMode);
};
}

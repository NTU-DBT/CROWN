#pragma once
#include "crown/storage/index_work.hpp"

namespace crown::storage::detail {
// Runtime diagnostic bridge: public and compact storage consume one canonical
// balance with their respective diagnostics. Nonmovable view, no allocation.
// The caller retains a canonical non-alias root for the whole borrow.
struct IndexWorkAlias {
  // Cold source preparation borrows one fixed-diagnostic root until close.
  [[nodiscard]] static IndexWorkAllowance fixed(IndexWorkAllowance& root) noexcept {
    return IndexWorkAllowance(root,true);
  }
  [[nodiscard]] static IndexWorkAllowance legacy(IndexWorkAllowance& root) noexcept {
    return IndexWorkAllowance(root,false);
  }
};
}

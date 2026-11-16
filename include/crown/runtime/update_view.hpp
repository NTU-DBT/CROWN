#pragma once

#include "crown/storage/tuple_values.hpp"

namespace crown::runtime {
// Borrowed input for native adapters. Values must remain alive during admission;
// physical/delta pending state imports its own native ownership before returning.
struct PhysicalUpdateView {
  std::uint64_t sequence;
  TableId table;
  SetOperation operation;
  storage::TupleValuesView values;
  [[nodiscard]] static PhysicalUpdateView borrow(const PhysicalSetUpdate& update) noexcept {
    return {update.sequence,update.table,update.operation,storage::TupleValuesView::borrow(update.values)};
  }
};
} // namespace crown::runtime

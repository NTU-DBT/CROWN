#pragma once

#include "crown/storage/tuple_values.hpp"

namespace crown::storage::detail {
// Concrete shared_ptr control blocks destroy the concrete payload. This base
// stores views only; the native derived owner retains AccountedTuple, while
// explicit standalone compiler/tool tuples retain their legacy input Row.
struct TuplePayload {
  TuplePayload() noexcept=default;
  TuplePayload(const TuplePayload&)=delete;
  TuplePayload& operator=(const TuplePayload&)=delete;
  const Row* legacy=nullptr;
  RowView native;
  resource::MemoryAccount account;
  // Pooled arena rows (TuplePool) refer to their chunk's single account copy
  // instead of holding one each; the chunk outlives every row it holds.
  const resource::MemoryAccount* shared_account=nullptr;
  resource::MemoryUsage usage;
  [[nodiscard]] const resource::MemoryAccount& query_account() const noexcept { return shared_account?*shared_account:account; }
};
} // namespace crown::storage::detail

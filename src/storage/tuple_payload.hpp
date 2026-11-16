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
  resource::MemoryUsage usage;
};
} // namespace crown::storage::detail

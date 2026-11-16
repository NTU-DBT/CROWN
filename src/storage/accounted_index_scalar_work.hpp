#pragma once

#include "crown/storage/index_work.hpp"
#include "crown/storage/accounted_projection.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <variant>

namespace crown::storage::detail {

static_assert(std::numeric_limits<std::size_t>::digits <= 64);

// These scalar work units admit tags/lengths before the later native
// helper. They are conservative payload domains, not total instruction counts,
// object sizeof, allocator bytes or a CPU measurement.
inline void accounted_admit_scalar_copy(const ScalarView& value, IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_fields = 2});
  if (std::holds_alternative<std::int64_t>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (const auto* text = std::get_if<std::string_view>(&value))
    allowance.admit(IndexWork{.scalar_bytes = static_cast<std::uint64_t>(text->size())});
  else if (std::holds_alternative<bool>(value))
    allowance.admit(IndexWork{.scalar_bytes = 1});
  else if (std::holds_alternative<Date>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (std::holds_alternative<InlineDecimal>(value))
    allowance.admit(IndexWork{.scalar_bytes = 38});
  else
    throw IndexFailure(IndexFault::contract);
}

inline void accounted_admit_scalar_hash(const ScalarView& value, IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_fields = 2, .scalar_bytes = 1});
  if (std::holds_alternative<std::int64_t>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (const auto* text = std::get_if<std::string_view>(&value)) {
    allowance.admit(IndexWork{.scalar_bytes = 8});
    allowance.admit(IndexWork{.scalar_bytes = static_cast<std::uint64_t>(text->size())});
  } else if (std::holds_alternative<bool>(value))
    allowance.admit(IndexWork{.scalar_bytes = 1});
  else if (std::holds_alternative<Date>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (std::holds_alternative<InlineDecimal>(value))
    // Inline decimal rendering is at most sign + "0." +38 digits.
    // Reserve its framing and worst-case output before invoking the formatter.
    allowance.admit(IndexWork{.scalar_bytes = 8 + 41});
  else
    throw IndexFailure(IndexFault::contract);
}

[[nodiscard]] inline std::uint64_t accounted_admitted_hash(const AccountedTuple& tuple,
                                                IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_bytes = 8});  // Native row length framing.
  const auto values = tuple.values();
  for (const auto& value : values.cells()) accounted_admit_scalar_hash(value, allowance);
  // Compact decimal hashing uses a bounded stack buffer. Preparation/probe only;
  // mutations cache this result and never call it during publication or undo.
  return tuple.hash();
}

[[nodiscard]] inline bool accounted_admitted_equal(const AccountedTuple& left, const AccountedTuple& right,
                                         IndexWorkAllowance& allowance) {
  if (!left.layout().same_token(right.layout())) return false;
  const auto left_values = left.values(), right_values = right.values();
  if (left_values.size() != right_values.size()) return false;
  // Admit both complete payloads before row/scalar equality. This
  // can exceed a short-circuit comparison's actual work and is labeled as such.
  for (const auto& value : left_values.cells()) accounted_admit_scalar_copy(value, allowance);
  for (const auto& value : right_values.cells()) accounted_admit_scalar_copy(value, allowance);
  return left == right;
}

inline void accounted_admit_tuple_copy(const AccountedTuple& tuple, IndexWorkAllowance& allowance) {
  const auto values = tuple.values();
  for (const auto& value : values.cells()) accounted_admit_scalar_copy(value, allowance);
}

[[nodiscard]] inline AccountedTuple accounted_admitted_projection(const AccountedProjection& projection,
                                               const AccountedTuple& tuple,
                                               IndexWorkAllowance& allowance,
                                               resource::MemoryAttribution tag) {
  if (!projection.source().same_token(tuple.layout()))
    throw IndexFailure(IndexFault::layout_mismatch);
  for (const auto field : projection.fields())
    accounted_admit_scalar_copy(tuple.values()[field.value], allowance);
  // Repeated slots were charged repeatedly; nullary projections copy no cells.
  return projection.apply(tuple, tag);
}

}  // namespace crown::storage::detail

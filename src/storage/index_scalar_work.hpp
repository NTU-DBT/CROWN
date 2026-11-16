#pragma once

#include "crown/storage/index_work.hpp"
#include "crown/storage/layout.hpp"
#include "accounted_index_scalar_work.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <variant>

namespace crown::storage::detail {

static_assert(std::numeric_limits<std::size_t>::digits <= 64);

// Scalar grants below describe explicit payload domains. They are not
// object sizeof, allocator bytes or a complete CPU/scalar-touch measurement
// for later public descriptor adapters.
inline void admit_scalar_copy(const Value& value, IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_fields = 2});
  if (std::holds_alternative<std::int64_t>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (const auto* text = std::get_if<std::string>(&value))
    allowance.admit(IndexWork{.scalar_bytes = static_cast<std::uint64_t>(text->size())});
  else if (std::holds_alternative<bool>(value))
    allowance.admit(IndexWork{.scalar_bytes = 1});
  else if (std::holds_alternative<Date>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (std::holds_alternative<Decimal>(value))
    allowance.admit(IndexWork{.scalar_bytes = 38});
  else
    throw Error("storage_contract", "optimized index received a valueless scalar");
}
inline void admit_scalar_copy(const ScalarView& value,IndexWorkAllowance& allowance) {
  accounted_admit_scalar_copy(value,allowance);
}

inline void admit_scalar_hash(const Value& value, IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_fields = 2, .scalar_bytes = 1});
  if (std::holds_alternative<std::int64_t>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (const auto* text = std::get_if<std::string>(&value)) {
    allowance.admit(IndexWork{.scalar_bytes = 8});
    allowance.admit(IndexWork{.scalar_bytes = static_cast<std::uint64_t>(text->size())});
  } else if (std::holds_alternative<bool>(value))
    allowance.admit(IndexWork{.scalar_bytes = 1});
  else if (std::holds_alternative<Date>(value))
    allowance.admit(IndexWork{.scalar_bytes = 8});
  else if (std::holds_alternative<Decimal>(value))
    // Public canonical Decimal::to_string is at most sign + "0." +38 digits.
    // Reserve its framing and worst-case output before invoking the formatter.
    allowance.admit(IndexWork{.scalar_bytes = 8 + 41});
  else
    throw Error("storage_contract", "optimized index received a valueless scalar");
}
inline void admit_scalar_hash(const ScalarView& value,IndexWorkAllowance& allowance) {
  accounted_admit_scalar_hash(value,allowance);
}

[[nodiscard]] inline std::uint64_t admitted_hash(const Tuple& tuple,
                                                IndexWorkAllowance& allowance) {
  allowance.admit(IndexWork{.scalar_bytes = 8});  // Native row length framing.
  for (const auto& value : tuple.values()) admit_scalar_hash(value, allowance);
  // Decimal formatting may allocate. This helper is preparation/probe only;
  // mutations cache this result and never call it during publication or undo.
  return tuple.hash();
}

[[nodiscard]] inline bool admitted_equal(const Tuple& left, const Tuple& right,
                                         IndexWorkAllowance& allowance) {
  if (!left.layout().same_token(right.layout())) return false;
  if (left.values().size() != right.values().size()) return false;
  // Admit both complete payloads before public exact-value comparison. This
  // can exceed a short-circuit comparison's actual work and is labeled as such.
  for (const auto& value : left.values()) admit_scalar_copy(value, allowance);
  for (const auto& value : right.values()) admit_scalar_copy(value, allowance);
  return left == right;
}

inline void admit_tuple_copy(const Tuple& tuple, IndexWorkAllowance& allowance) {
  for (const auto& value : tuple.values()) admit_scalar_copy(value, allowance);
}

[[nodiscard]] inline Tuple admitted_projection(const Projection& projection,
                                               const Tuple& tuple,
                                               IndexWorkAllowance& allowance) {
  if (!projection.source().same_token(tuple.layout()))
    throw Error("layout_mismatch", "projection input has a different immutable layout token");
  for (const auto field : projection.fields())
    admit_scalar_copy(tuple.values()[field.value], allowance);
  // Repeated slots were charged repeatedly; nullary projections copy no cells.
  // Native-backed public descriptors also validate the full source.
  // Direct compact AccountedTuple projection uses its separate token fast path.
  return projection.apply(tuple);
}

}  // namespace crown::storage::detail

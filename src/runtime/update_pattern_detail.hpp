#pragma once

#include "crown/runtime/update_pattern.hpp"
#include "crown/api/error.hpp"
#include <algorithm>

namespace crown::runtime::pattern_detail {
// Logical rule comparisons share the existing window command grant. The
// declaration is immutable, so no second lookup index or row history is needed.
template<class Charge> const patterns::TableRule* find(
    const patterns::Declaration& declaration, TableId table, Charge& charge) {
  const auto rules = declaration.rules();
  const auto item = std::lower_bound(rules.begin(), rules.end(), table,
      [&](const auto& rule, TableId key) { charge(); return rule.table < key; });
  charge();
  return item != rules.end() && item->table == table ? &*item : nullptr;
}
// Fill only caller-owned scalar scratch. A failed Error allocation is a
// retryable allocation failure; Session latches only a completed semantic Error.
inline void require(bool condition, PatternViolationKind kind, TableId table,
    std::uint64_t command, std::uint64_t label, PatternViolation* violation) {
  if (condition) return;
  if (violation) *violation = {kind, table, command, label};
  throw Error("update_pattern_violation", "declared update pattern forbids this transition");
}
} // namespace crown::runtime::pattern_detail

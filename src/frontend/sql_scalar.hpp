#pragma once

#include "crown/frontend/bind.hpp"
#include "crown/storage/accounted_row.hpp"
#include "crown/storage/index_work.hpp"
#include <span>

namespace crown::frontend::sql_detail {
using Cell = std::optional<storage::ScalarView>;

// Strings borrow the caller/program payload; other scalar alternatives are
// inline. Returning a Cell never freezes borrowed bytes into retained state.
inline std::uint64_t scalar_bytes(const storage::ScalarView& value) {
  if (const auto* text = std::get_if<std::string_view>(&value)) return static_cast<std::uint64_t>(text->size());
  if (const auto* decimal = std::get_if<storage::InlineDecimal>(&value))
    return static_cast<std::uint64_t>(decimal->parts().digits.size());
  return 0;
}
inline void admit_value(storage::IndexWorkAllowance* work, const storage::ScalarView& value) {
  if (work) work->admit(storage::IndexWork{.scalar_fields = 1, .scalar_bytes = scalar_bytes(value)});
}
inline std::optional<bool> truth(const Cell& value) {
  if (!value) return {};
  if (!std::holds_alternative<bool>(*value)) throw storage::IndexFailure(storage::IndexFault::contract);
  return std::get<bool>(*value);
}
inline Cell boolean(std::optional<bool> value) { return value ? Cell{storage::ScalarView{*value}} : Cell{}; }
inline const Cell& cell_at(std::span<const Cell> values, ExpressionId id) {
  if (id.value >= values.size()) throw storage::IndexFailure(storage::IndexFault::contract);
  return values[id.value];
}

// The binder/compiler has admitted operator arity and operand types. Each
// accessed slot remains checked; NULL comparisons return UNKNOWN. Only a TRUE
// predicate admits a row. These are SQL rules, not core NULL equality.
// Work is charged in the same order as the existing native adapter: one step
// per visited Boolean operand and both present scalar operands of a comparison.
inline Cell evaluate(SqlOperator operation, std::span<const ExpressionId> arguments,
    std::span<const Cell> values, storage::IndexWorkAllowance* work = nullptr) {
  const auto arg = [&](std::size_t i) -> const Cell& {
    if (i >= arguments.size()) throw storage::IndexFailure(storage::IndexFault::contract);
    return cell_at(values, arguments[i]);
  };
  switch (operation) {
    case SqlOperator::identity_cast: case SqlOperator::literal_cast:
    case SqlOperator::widen_integer: case SqlOperator::using_value: return arg(0);
    case SqlOperator::is_null: case SqlOperator::is_unknown: return storage::ScalarView{!arg(0)};
    case SqlOperator::is_not_null: case SqlOperator::is_not_unknown: return storage::ScalarView{arg(0).has_value()};
    case SqlOperator::is_true: return storage::ScalarView{truth(arg(0)) == std::optional<bool>{true}};
    case SqlOperator::is_not_true: return storage::ScalarView{truth(arg(0)) != std::optional<bool>{true}};
    case SqlOperator::is_false: return storage::ScalarView{truth(arg(0)) == std::optional<bool>{false}};
    case SqlOperator::is_not_false: return storage::ScalarView{truth(arg(0)) != std::optional<bool>{false}};
    case SqlOperator::negation: {
      const auto value = truth(arg(0));
      return value ? boolean(!*value) : Cell{};
    }
    case SqlOperator::conjunction: case SqlOperator::disjunction: {
      const bool conjunction = operation == SqlOperator::conjunction;
      bool null_seen = false;
      for (const auto id : arguments) {
        if (work) work->admit(storage::IndexWork{.structural_steps = 1});
        const auto value = truth(cell_at(values, id));
        if (!value) null_seen = true;
        else if (*value != conjunction) return storage::ScalarView{!conjunction};
      }
      return null_seen ? Cell{} : Cell{storage::ScalarView{conjunction}};
    }
    case SqlOperator::equal: case SqlOperator::not_equal: case SqlOperator::less:
    case SqlOperator::less_equal: case SqlOperator::greater: case SqlOperator::greater_equal: {
      if (!arg(0) || !arg(1)) return {};
      if (arg(0)->index() != arg(1)->index()) throw storage::IndexFailure(storage::IndexFault::contract);
      admit_value(work, *arg(0)); admit_value(work, *arg(1));
      const auto order = *arg(0) <=> *arg(1);
      switch (operation) {
        case SqlOperator::equal: return storage::ScalarView{order == 0};
        case SqlOperator::not_equal: return storage::ScalarView{order != 0};
        case SqlOperator::less: return storage::ScalarView{order < 0};
        case SqlOperator::less_equal: return storage::ScalarView{order <= 0};
        case SqlOperator::greater: return storage::ScalarView{order > 0};
        case SqlOperator::greater_equal: return storage::ScalarView{order >= 0};
        default: break;
      }
      break;
    }
  }
  throw storage::IndexFailure(storage::IndexFault::contract);
}
}  // namespace crown::frontend::sql_detail

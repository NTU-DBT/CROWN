#pragma once

#include "sql_rows_value.hpp"
#include "sql_scalar.hpp"

namespace crown::frontend::rows_detail {
inline void step(storage::IndexWorkAllowance* work) {
  if (work) work->admit(storage::IndexWork{.structural_steps = 1});
}
inline bool same(const SqlRowCell& left, const SqlRowCell& right, storage::IndexWorkAllowance* work) {
  if (!left || !right) return !left && !right;
  sql_detail::admit_value(work, *left); sql_detail::admit_value(work, *right);
  return *left == *right;
}

// Use an occurrence from this live program, a complete validated input, and
// disjoint scratch initialized once from initial_values(); output must fit the
// projection. On true, strings borrow input/program until the caller freezes
// the native view. On false/throw, output is unspecified and must not be read.
// Written dynamic slots are cleared on every exit. No Row or per-call allocation.
inline bool adapt(const SqlRowsProgram& program, const SqlRowsOccurrence& occurrence,
    std::span<const SqlRowCell> input, std::span<SqlRowCell> values,
    std::span<storage::ScalarView> output, storage::IndexWorkAllowance* work = nullptr) {
  const auto constants = program.initial_values();
  for (const auto column : occurrence.non_null_columns) {
    step(work); if (!input[column.value]) return false;
  }
  for (const auto& equal : occurrence.equal_columns) {
    step(work);
    const auto& left = input[equal.left.value]; const auto& right = input[equal.right.value];
    // These are ordinary SQL equalities: two NULL cells never match.
    if (!left || !right || !same(left, right, work)) return false;
  }
  for (const auto& fixed : occurrence.constant_columns) {
    step(work); if (!same(input[fixed.column.value], constants[fixed.constant.value], work)) return false;
  }
  struct Borrows {
    const SqlRowsOccurrence& occurrence;
    std::span<SqlRowCell> values;
    std::size_t inputs = 0, operations = 0;
    ~Borrows() {
      for (std::size_t i = 0; i < inputs; ++i) values[occurrence.inputs[i].target.value].reset();
      for (std::size_t i = 0; i < operations; ++i) values[occurrence.operations[i].target.value].reset();
    }
  } borrows{occurrence, values};
  for (const auto& read : occurrence.inputs) {
    step(work); values[read.target.value] = input[read.column.value]; ++borrows.inputs;
  }
  for (const auto& operation : occurrence.operations) {
    step(work);
    values[operation.target.value] = sql_detail::evaluate(operation.operation, operation.arguments, values, work);
    ++borrows.operations;
  }
  for (const auto predicate : occurrence.predicates) {
    step(work); if (sql_detail::truth(values[predicate.value]) != std::optional<bool>{true}) return false;
  }
  for (std::size_t i = 0; i < occurrence.projection.size(); ++i) {
    step(work); const auto& field = occurrence.projection[i]; const auto& value = values[field.expression.value];
    if (field.kind == SqlRowsFieldKind::presence) output[i] = value.has_value();
    else if (value) output[i] = *value;
    else if (field.kind == SqlRowsFieldKind::nullable_payload) output[i] = zero(field.type);
    else throw storage::IndexFailure(storage::IndexFault::contract);
  }
  return true;
}
}  // namespace crown::frontend::rows_detail

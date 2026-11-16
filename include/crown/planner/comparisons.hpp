#pragma once

#include "crown/ir/physical.hpp"
#include <cstdint>
#include <memory>
#include <span>
#include <utility>
#include <variant>

namespace crown::planner::comparisons {
enum class Operator { equal, not_equal, less, less_equal, greater, greater_equal };
using Operand = std::variant<VariableId, Value>;
struct Predicate { Operand left; Operator operation; Operand right; };
struct Limits { std::uint64_t work = 1'000'000; };

// Cold opt-in comparison metadata over a genuine direct exact-set CQ plan.
// Predicates are a conjunction, separate from the original equality query.
// This ordinary compiler owner copies caller literals; native execution must
// freeze retained predicates into its receiving query account.
class Plan {
 public:
  Plan(const Plan&) noexcept = default;
  Plan& operator=(const Plan&) noexcept = default;
  Plan(Plan&& other) noexcept : data_(other.data_) {}
  Plan& operator=(Plan&& other) noexcept { data_ = other.data_; return *this; }
  [[nodiscard]] const PhysicalPlan& general() const & noexcept;
  const PhysicalPlan& general() const && = delete;
  [[nodiscard]] std::span<const Predicate> predicates() const & noexcept;
  std::span<const Predicate> predicates() const && = delete;
  [[nodiscard]] std::uint64_t work() const noexcept;
 private:
  struct Data;
  explicit Plan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
  friend Plan admit(const PhysicalPlan&, std::span<const Predicate>, const Limits&);
  std::shared_ptr<const Data> data_;
};

// Every variable operand must occur in an original query atom. Both operands
// must have the same ScalarType; there are no implicit casts, SQL NULLs or
// collation changes. All six operators, constant operands, empty conjunctions
// and genuine constant/contradictory direct-CQ routes are admitted.
// general() retains its equality-only provenance/profile, not a comparison
// guarantee or new height proof. Copies and moves keep both handles valid.
//
// Invalid predicates or SQL-normalized plans throw comparison_admission;
// exhausted selected work throws comparison_work_limit. One shared balance
// charges entry, variable slots, atom/term visits, predicates, operands and
// literal string bytes before copying. Allocation, compiler-owner teardown,
// inherited plan validation and bounded Date/Decimal copy costs are separate.
// Refusal leaves the caller's plan and predicate DTOs unchanged.
[[nodiscard]] Plan admit(const PhysicalPlan&, std::span<const Predicate>, const Limits& = {});
} // namespace crown::planner::comparisons

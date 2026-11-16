#include "crown/planner/comparisons.hpp"
#include "crown/api/error.hpp"
#include <vector>

namespace crown::planner::comparisons {
namespace {
struct Budget {
  std::uint64_t remaining, used = 0;
  void take(std::uint64_t amount = 1) {
    if (amount > remaining)
      throw Error("comparison_work_limit", "comparison admission work grant exceeded");
    remaining -= amount; used += amount;
  }
};
void require(bool condition, const char* message) {
  if (!condition) throw Error("comparison_admission", message);
}
void validate_operator(Operator operation) {
  switch (operation) {
    case Operator::equal: case Operator::not_equal: case Operator::less:
    case Operator::less_equal: case Operator::greater: case Operator::greater_equal: return;
  }
  require(false, "comparison operator is invalid");
}
ScalarType operand_type(const Operand& operand, const Query& query,
    const std::vector<bool>& bound, Budget& budget) {
  budget.take();
  if (const auto* variable = std::get_if<VariableId>(&operand)) {
    require(variable->value < bound.size() && bound[variable->value],
        "comparison variable is not bound by an original query atom");
    return query.variables[variable->value].type;
  }
  const auto* literal = std::get_if<Value>(&operand);
  require(literal && !literal->valueless_by_exception(), "comparison literal is invalid");
  if (const auto* text = std::get_if<std::string>(literal)) budget.take(text->size());
  return type_of(*literal);
}
} // namespace

struct Plan::Data {
  PhysicalPlan general;
  std::vector<Predicate> predicates;
  std::uint64_t work;
};
const PhysicalPlan& Plan::general() const & noexcept { return data_->general; }
std::span<const Predicate> Plan::predicates() const & noexcept { return data_->predicates; }
std::uint64_t Plan::work() const noexcept { return data_->work; }

Plan admit(const PhysicalPlan& general, std::span<const Predicate> predicates, const Limits& limits) {
  Budget budget{limits.work}; budget.take();
  require(!general.normalized(), "comparison admission requires a direct CQ without SQL adapters");
  const auto& query = general.query();
  for (const auto& variable : query.variables) { static_cast<void>(variable); budget.take(); }
  std::vector<bool> bound(query.variables.size(), false);
  for (const auto& atom : query.atoms) {
    budget.take();
    for (const auto& term : atom.terms) {
      budget.take();
      if (const auto* variable = std::get_if<VariableId>(&term)) bound[variable->value] = true;
    }
  }
  for (const auto& predicate : predicates) {
    budget.take(); validate_operator(predicate.operation);
    const auto left = operand_type(predicate.left, query, bound, budget);
    const auto right = operand_type(predicate.right, query, bound, budget);
    require(left == right, "comparison operands must have the same exact scalar type");
  }
  // Copy only after all guards and payload-byte admissions have succeeded.
  // Predicates remain separate; no equality class, head or source is rewritten.
  return Plan(std::make_shared<Plan::Data>(Plan::Data{general,
      std::vector<Predicate>(predicates.begin(), predicates.end()), budget.used}));
}
} // namespace crown::planner::comparisons

#include "crown/planner/star.hpp"
#include "crown/api/error.hpp"
#include <set>
#include <variant>
#include <vector>

namespace crown::planner::star {
namespace {
// The one balance spans shape checks and output mapping. A failed private
// builder publishes no metadata and never consumes the caller's plan handle.
struct Budget {
  std::uint64_t remaining, used = 0;
  void take() {
    if (!remaining) throw Error("star_work_limit", "star admission work grant exceeded");
    --remaining; ++used;
  }
};
void require(bool condition, const char* message) {
  if (!condition) throw Error("star_admission", message);
}
} // namespace

struct Plan::Data {
  PhysicalPlan general, source_only;
  OccurrenceId center;
  TableId center_table;
  std::vector<std::optional<TableId>> satellites;
  std::vector<std::size_t> head;
  std::size_t distinct_head;
  Usage usage;
};

const PhysicalPlan& Plan::general() const & noexcept { return data_->general; }
const PhysicalPlan& Plan::source_only() const & noexcept { return data_->source_only; }
OccurrenceId Plan::center() const noexcept { return data_->center; }
TableId Plan::center_table() const noexcept { return data_->center_table; }
std::size_t Plan::dimension() const noexcept { return data_->satellites.size(); }
std::size_t Plan::distinct_head() const noexcept { return data_->distinct_head; }
std::span<const std::optional<TableId>> Plan::satellite_tables() const & noexcept { return data_->satellites; }
std::span<const std::size_t> Plan::head_coordinates() const & noexcept { return data_->head; }
const Usage& Plan::usage() const & noexcept { return data_->usage; }

Plan admit(const PhysicalPlan& general, OccurrenceId center, const Limits& limits) {
  Budget budget{limits.work}; budget.take();
  require(!general.normalized(), "star admission requires a direct CQ, without a SQL adapter");
  require(general.route() == PhysicalRoute::tree && !general.query().contradiction,
      "star admission requires a nonconstant tree plan");
  const auto& query = general.query();
  require(center.value < query.atoms.size(), "star center occurrence is outside the original query");
  const auto& fact = query.atoms[center.value];
  const auto d = fact.terms.size();
  require(d != 0, "star center arity must be positive");
  require(d == query.variables.size(), "star center must contain every query variable exactly once");

  // Genuine PhysicalPlan admission already established dense in-range variable
  // IDs and physical schemas. The vector maps IDs, not variable names or types.
  for (const auto& variable : query.variables) { static_cast<void>(variable); budget.take(); }
  std::vector<std::optional<std::size_t>> coordinates(query.variables.size());
  for (std::size_t i = 0; i < d; ++i) {
    budget.take();
    const auto* variable = std::get_if<VariableId>(&fact.terms[i]);
    require(variable != nullptr, "every star center field must be a variable");
    require(!coordinates[variable->value], "star center variables must be pairwise distinct");
    coordinates[variable->value] = i;
  }

  // Literal self-join freedom concerns physical TableIds. Occurrence aliases
  // cannot make repeated physical input into the paper's distinct relations.
  std::set<TableId> tables;
  std::vector<std::optional<TableId>> satellites(d);
  for (std::size_t i = 0; i < query.atoms.size(); ++i) {
    budget.take();
    const auto& atom = query.atoms[i];
    require(tables.insert(atom.table).second, "star relations must have distinct physical tables");
    if (i == center.value) continue;
    require(atom.terms.size() == 1, "every noncenter star relation must be unary");
    budget.take();
    const auto* variable = std::get_if<VariableId>(&atom.terms.front());
    require(variable != nullptr, "every star satellite field must be a variable");
    const auto coordinate = coordinates[variable->value];
    require(coordinate.has_value(), "every star satellite variable must occur in the center");
    require(!satellites[*coordinate], "star satellites must use different center coordinates");
    satellites[*coordinate] = atom.table;
  }

  // j is a set cardinality. Output assembly still records every original
  // position, so repeated variables and aliases in general() remain untouched.
  std::vector<std::size_t> head;
  std::vector<bool> free(d, false);
  std::size_t distinct = 0;
  for (const auto& output : query.head) {
    budget.take();
    const auto coordinate = coordinates[output.variable.value];
    require(coordinate.has_value(), "every star head variable must occur in the center");
    head.push_back(*coordinate);
    if (!free[*coordinate]) { free[*coordinate] = true; ++distinct; }
  }
  for (std::size_t i = 0; i < d; ++i) {
    budget.take();
    require(free[i] || satellites[i].has_value(), "every hidden center coordinate requires a unary satellite");
  }

  // Local engineering source coordinator, not an answer rewrite. The complete
  // catalog/options/constraints are copied unchanged; its empty alias routes
  // avoid maintaining the independent general joins inside the star runtime.
  auto source = lower_tree(general.catalog(), Query{}, FreeConnexTree{}, general.options(), limits.lowering);
  const Usage usage{budget.used, source.work()};
  return Plan(std::make_shared<Plan::Data>(Plan::Data{general, std::move(source), center,
      fact.table, std::move(satellites), std::move(head), distinct, usage}));
}
} // namespace crown::planner::star

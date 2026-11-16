#include "crown/planner/fallback.hpp"
#include "crown/api/error.hpp"
#include <limits>
#include <type_traits>
#include <variant>

namespace crown::planner::fallback {
namespace {
struct Budget {
  std::uint64_t remaining, used = 0;
  void take(std::uint64_t amount = 1) {
    if (amount > remaining) throw Error("fallback_work_limit", "fallback admission work grant exceeded");
    remaining -= amount; used += amount;
  }
  void text(std::string_view value) { take(); take(value.size()); }
  void literal(const Value& value) {
    take();
    if (value.valueless_by_exception()) throw Error("fallback_admission", "invalid fallback literal");
    if (const auto* text = std::get_if<std::string>(&value)) take(text->size());
    else if (const auto* decimal = std::get_if<Decimal>(&value)) take(decimal->parts().digits.size());
  }
};
void require(bool condition, const char* message) {
  if (!condition) throw Error("fallback_admission", message);
}

// Admit copied metadata and variable-width payload before publishing copies.
// Validation, GYO and source-only lowering keep their stated separate costs.
void metadata(const Catalog& catalog, const Query& query, Budget& budget) {
  for (const auto& table : catalog.tables) {
    budget.take(); budget.text(table.name);
    for (const auto& column : table.columns) { budget.take(); budget.text(column.name); }
    for (const auto& constraint : table.constraints) {
      budget.take(); require(!constraint.valueless_by_exception(), "invalid fallback constraint");
      std::visit([&](const auto& key) {
        budget.text(key.name);
        for (const auto column : key.columns) { static_cast<void>(column); budget.take(); }
        if constexpr (std::is_same_v<std::decay_t<decltype(key)>, ForeignKeyConstraint>)
          for (const auto column : key.referenced_columns) { static_cast<void>(column); budget.take(); }
      }, constraint);
    }
    budget.take(); // Optional row count and fixed table/schema metadata.
    for (const auto& estimate : table.statistics.distinct_counts) {
      budget.take();
      for (const auto column : estimate.columns) { static_cast<void>(column); budget.take(); }
    }
    for (const auto& hint : table.key_hints) {
      budget.take(); budget.text(hint.reason);
      for (const auto column : hint.columns) { static_cast<void>(column); budget.take(); }
    }
  }
  for (const auto& variable : query.variables) { budget.take(); budget.text(variable.name); }
  for (const auto& atom : query.atoms) {
    budget.take(); budget.text(atom.occurrence);
    for (const auto& term : atom.terms) {
      budget.take(); require(!term.valueless_by_exception(), "invalid fallback term");
      if (const auto* value = std::get_if<Value>(&term)) budget.literal(*value);
    }
  }
  for (const auto& output : query.head) { budget.take(); budget.text(output.alias); }
}
std::optional<std::uint64_t> sum(std::uint64_t a, std::uint64_t b, bool& overflow) {
  if (b > std::numeric_limits<std::uint64_t>::max() - a) { overflow = true; return {}; }
  return a + b;
}
} // namespace

struct Plan::Data {
  Catalog catalog;
  Query query;
  PhysicalPlan source;
  StructuralAnalysis structure;
  Profile profile;
  std::uint64_t work;
};
const Catalog& Plan::originalcatalog() const & noexcept { return data_->catalog; }
const Query& Plan::query() const & noexcept { return data_->query; }
const PhysicalPlan& Plan::source_only() const & noexcept { return data_->source; }
const StructuralAnalysis& Plan::structure() const & noexcept { return data_->structure; }
const Profile& Plan::profile() const & noexcept { return data_->profile; }
std::uint64_t Plan::work() const noexcept { return data_->work; }

Estimates Plan::estimates(std::span<const std::uint64_t> tablecounts) const {
  require(tablecounts.size() == data_->catalog.tables.size(), "fallback estimates require one count per source table");
  Estimates result; result.source_rows = 0;
  for (const auto count : tablecounts)
    if (result.source_rows) result.source_rows = sum(*result.source_rows, count, result.overflow);

  // A zero factor wins over any otherwise overflowing prefix product.
  bool zero = data_->query.contradiction;
  for (const auto& atom : data_->query.atoms) zero = zero || tablecounts[atom.table.value] == 0;
  result.assignments_upper = zero ? 0 : 1;
  if (!zero) for (const auto& atom : data_->query.atoms) {
    const auto count = tablecounts[atom.table.value];
    if (!result.assignments_upper) break;
    if (count > std::numeric_limits<std::uint64_t>::max() / *result.assignments_upper) {
      result.assignments_upper.reset(); result.overflow = true;
    } else *result.assignments_upper *= count;
  }
  if (data_->query.head.empty())
    result.output_rows_upper = result.assignments_upper && *result.assignments_upper == 0 ? 0 : 1;
  else result.output_rows_upper = result.assignments_upper;
  if (result.source_rows && result.output_rows_upper)
    result.state_rows_upper = sum(*result.source_rows, *result.output_rows_upper, result.overflow);
  return result;
}

Plan admit(const Catalog& catalog, const Query& query, const PhysicalOptions& options, const Limits& limits) {
  Budget budget{limits.work}; budget.take(); metadata(catalog, query, budget);
  Catalog originalcatalog = catalog;
  Query originalquery = query;
  try {
    auto recognition = analyze_bounded(originalcatalog, originalquery, limits.recognition);
    if (!recognition.analysis)
      throw Error("fallback_work_limit", "fallback recognition work grant exceeded; no query class established");
    Profile profile; profile.query_class = recognition.analysis->query_class;
    if (originalquery.contradiction) profile.reason = Reason::contradiction;
    else if (profile.query_class == QueryClass::cyclic) profile.reason = Reason::cyclic_body;
    else if (profile.query_class == QueryClass::acyclic_non_free_connex) profile.reason = Reason::non_free_connex_head;
    auto source = lower_tree(originalcatalog, Query{}, FreeConnexTree{}, options, limits.lowering);
    return Plan(std::make_shared<Plan::Data>(Plan::Data{std::move(originalcatalog), std::move(originalquery), std::move(source),
        std::move(*recognition.analysis), profile, budget.used}));
  } catch (const Error& error) {
    if (error.code() == "fallback_work_limit" || error.code() == "fallback_admission") throw;
    if (error.code() == "resource_limit") throw Error("fallback_work_limit", error.what());
    throw Error("fallback_admission", error.what());
  }
}
} // namespace crown::planner::fallback

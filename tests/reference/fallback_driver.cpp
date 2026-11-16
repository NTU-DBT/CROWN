#include "crown/runtime/fallback.hpp"
#include "crown/io/document.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
using io::Json;
namespace pf = planner::fallback;
namespace rf = runtime::fallback;

// This is actual fallback execution only. The Python/SQLite process defines
// complete original-CQ expected sources, projected rows and endpoint changes.
std::string query_class(planner::QueryClass value) {
  switch (value) {
    case planner::QueryClass::free_connex: return "free_connex";
    case planner::QueryClass::acyclic_non_free_connex: return "acyclic_non_free_connex";
    case planner::QueryClass::cyclic: return "cyclic";
  }
  throw std::runtime_error("unknown fallback query class");
}
std::string reason(pf::Reason value) {
  switch (value) {
    case pf::Reason::cyclic_body: return "cyclic_body";
    case pf::Reason::non_free_connex_head: return "non_free_connex_head";
    case pf::Reason::explicit_reference_choice: return "explicit_reference_choice";
    case pf::Reason::contradiction: return "contradiction";
  }
  throw std::runtime_error("unknown fallback admission reason");
}
Json profile(const pf::Profile& value) {
  return {{"backend",std::string(value.backend)},{"semantics",std::string(value.semantics)},
      {"query_class",query_class(value.query_class)},{"reason",reason(value.reason)},
      {"update",std::string(value.update)},{"state",std::string(value.state)},
      {"startup",std::string(value.startup)},{"delay",std::string(value.delay)},
      {"termination",std::string(value.termination)},{"height",std::string(value.height)}};
}
Json number(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
Json tuples(const rf::TupleVector& input) {
  Relation rows;
  for (const auto& tuple : input)
    if (!rows.insert(storage::export_row(tuple.values())).second)
      throw std::runtime_error("duplicate fallback endpoint row");
  return io::write_relation(rows);
}
Json metrics(const rf::Metrics& m) {
  return {{"work",m.work},{"source_work",m.source_work},{"source_rows",m.source_rows},
      {"row_visits",m.row_visits},{"term_tests",m.term_tests},{"equality_tests",m.equality_tests},
      {"assignments",m.assignments},{"projected",m.projected},{"duplicates",m.duplicates},
      {"scalar_fields",m.scalar_fields},{"scalar_bytes",m.scalar_bytes},{"row_comparisons",m.row_comparisons},
      {"outputs",m.outputs},{"added",m.added},{"removed",m.removed},{"recomputed",m.recomputed}};
}
Json snapshot(const rf::Runtime& owner, const pf::Plan& plan) {
  const auto image = owner.snapshot(); const auto sources = owner.source_snapshot();
  const auto explain = owner.explain(); Json physical = Json::array(), cardinalities = Json::array();
  std::vector<std::uint64_t> counts;
  for (const auto& source : sources.tables) {
    physical.push_back(io::write_relation(source)); counts.push_back(source.size());
  }
  for (const auto value : explain.table_rows) cardinalities.push_back(value);
  const auto estimates = plan.estimates(counts);
  return {{"sequence",owner.sequence()},{"ready",owner.ready()},{"rows",tuples(image.rows)},
      {"source",std::move(physical)},{"has_answer",owner.has_answer()},
      {"original_atoms",image.binding.query().atoms.size()},{"original_head",image.binding.query().head.size()},
      {"source_only_atoms",image.binding.sources().query().atoms.size()},
      {"original_account",image.binding.account().statistics().owner==owner.account().statistics().owner},
      {"explain",{{"profile",profile(explain.profile)},{"table_rows",std::move(cardinalities)},
          {"witness_product",number(explain.witness_product)},{"prefix_product_sum",number(explain.prefix_product_sum)},
          {"result_rows",explain.result_rows}}},
      {"estimates",{{"source_rows",number(estimates.source_rows)},
          {"assignments_upper",number(estimates.assignments_upper)},{"output_rows_upper",number(estimates.output_rows_upper)},
          {"state_rows_upper",number(estimates.state_rows_upper)},{"overflow",estimates.overflow},{"advisory",estimates.advisory}}}};
}
Json apply(rf::Runtime& owner, const PhysicalSetUpdate& update) {
  try {
    const auto epoch = owner.apply(update);
    return {{"error",nullptr},{"changed",epoch.input.input.physical_changed},
        {"added",tuples(epoch.added)},{"removed",tuples(epoch.removed)},{"metrics",metrics(epoch.metrics)},
        {"source_aliases",epoch.input.input.metrics.aliases_visited}};
  } catch (const Error& error) { return {{"error",error.code()}}; }
  catch (const resource::MemoryFailure& error) { return {{"error",std::string(error.code())}}; }
}
Json evaluate(const Json& request) {
  const auto document = io::read_document(request.at("document").dump());
  for (const auto& source : document.initial.tables)
    if (!source.empty()) throw std::runtime_error("fallback driver starts empty; use physical events");
  const auto options = request.value("indexed",false) ? s04_runtime::options() : PhysicalOptions{};
  const auto plan = pf::admit(document.catalog,document.query,options); rf::Runtime owner(plan);
  Json initial = snapshot(owner,plan), trace = Json::array();
  for (const auto& input : request.at("events")) {
    Row values; for (const auto& value : input.at("values")) values.push_back(io::read_scalar(value));
    const auto op = input.at("op").get<std::string>();
    if (op != "insert" && op != "delete") throw std::runtime_error("invalid fallback source operation");
    const PhysicalSetUpdate update{input.at("sequence").get<std::uint64_t>(),TableId{input.at("table").get<std::size_t>()},
        op == "insert" ? SetOperation::insert : SetOperation::erase,std::move(values)};
    auto event = apply(owner,update);
    trace.push_back({{"event",std::move(event)},{"snapshot",snapshot(owner,plan)}});
  }
  return {{"id",request.at("id")},{"profile",profile(plan.profile())},
      {"initial",std::move(initial)},{"trace",std::move(trace)}};
}
} // namespace
int main() {
  try {
    for (std::string line; std::getline(std::cin,line);) std::cout << evaluate(Json::parse(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

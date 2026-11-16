#include "crown/runtime/difference.hpp"
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
namespace pd = planner::difference;
namespace rd = runtime::difference;

// Actual public-IR execution/export only. Expected operand bags, physical
// sources, residual counts and endpoint changes live in the Python/SQLite model.
std::string query_class(planner::QueryClass value) {
  switch (value) {
    case planner::QueryClass::free_connex: return "free_connex";
    case planner::QueryClass::acyclic_non_free_connex: return "acyclic_non_free_connex";
    case planner::QueryClass::cyclic: return "cyclic";
  }
  throw std::runtime_error("unknown difference operand query class");
}
std::string reason(planner::fallback::Reason value) {
  switch (value) {
    case planner::fallback::Reason::cyclic_body: return "cyclic_body";
    case planner::fallback::Reason::non_free_connex_head: return "non_free_connex_head";
    case planner::fallback::Reason::explicit_reference_choice: return "explicit_reference_choice";
    case planner::fallback::Reason::contradiction: return "contradiction";
  }
  throw std::runtime_error("unknown difference operand admission reason");
}
Json profile(const pd::Profile& value) {
  return {{"mode",value.mode == pd::Mode::set_except ? "set_except" : "bag_except_all"},
      {"backend",std::string(value.backend)},{"semantics",std::string(value.semantics)},
      {"input",std::string(value.input)},{"arithmetic",std::string(value.arithmetic)},
      {"output",std::string(value.output)},{"delta",std::string(value.delta)},
      {"state",std::string(value.state)},{"startup",std::string(value.startup)},
      {"delay",std::string(value.delay)},{"termination",std::string(value.termination)},
      {"height",std::string(value.height)},{"left_class",query_class(value.left_class)},
      {"right_class",query_class(value.right_class)},{"left_reason",reason(value.left_reason)},
      {"right_reason",reason(value.right_reason)}};
}
Json number(std::optional<std::uint64_t> value) { return value ? Json(*value) : Json(nullptr); }
Json row(const storage::Tuple& tuple) {
  Json values = Json::array();
  for (const auto& value : storage::export_row(tuple.values())) values.push_back(io::write_scalar(value));
  return values;
}
Json entries(const rd::OutputVector<rd::Entry>& input) {
  Json result = Json::array();
  for (const auto& entry : input) result.push_back({{"values",row(entry.tuple)},{"multiplicity",entry.multiplicity.value}});
  return result;
}
Json changes(const rd::OutputVector<rd::Change>& input) {
  Json result = Json::array();
  for (const auto& change : input) {
    const auto delta = change.delta();
    result.push_back({{"values",row(change.tuple)},{"before",change.before.value},{"after",change.after.value},
        {"negative",delta.negative},{"magnitude",delta.magnitude.value}});
  }
  return result;
}
Json operand_estimates(const planner::fallback::Estimates& value) {
  return {{"source_rows",number(value.source_rows)},{"assignments_upper",number(value.assignments_upper)},
      {"output_rows_upper",number(value.output_rows_upper)},{"state_rows_upper",number(value.state_rows_upper)},
      {"overflow",value.overflow},{"advisory",value.advisory}};
}
Json estimates(const pd::Estimates& value) {
  return {{"left",operand_estimates(value.left)},{"right",operand_estimates(value.right)},
      {"source_rows",number(value.source_rows)},{"output_rows_upper",number(value.output_rows_upper)},
      {"output_multiplicity_upper",number(value.output_multiplicity_upper)},
      {"state_rows_upper",number(value.state_rows_upper)},{"overflow",value.overflow},{"advisory",value.advisory}};
}
Json snapshot(const rd::Runtime& owner, const pd::Plan& plan) {
  const auto image = owner.snapshot(); const auto sources = owner.source_snapshot();
  const auto explain = owner.explain(); Json physical = Json::array(), cardinalities = Json::array();
  std::vector<std::uint64_t> counts;
  for (const auto& source : sources.tables) {
    physical.push_back(io::write_relation(source)); counts.push_back(source.size());
  }
  for (const auto count : explain.table_rows) cardinalities.push_back(count);
  return {{"sequence",image.sequence},{"runtime_sequence",owner.sequence()},{"ready",owner.ready()},
      {"rows",entries(image.rows)},{"source",std::move(physical)},{"has_answer",owner.has_answer()},
      {"original_left_atoms",image.binding.left().atoms.size()},
      {"original_right_atoms",image.binding.right().atoms.size()},{"original_head",image.binding.left().head.size()},
      {"source_only_atoms",image.binding.sources().query().atoms.size()},
      {"original_account",image.binding.account().statistics().owner==owner.account().statistics().owner},
      {"binding_profile",profile(image.binding.profile())},{"explain_profile",profile(explain.profile)},
      {"multiplicity_limit",explain.multiplicity_limit},{"binding_limit",image.binding.multiplicity_limit()},
      {"table_rows",std::move(cardinalities)},{"result_rows",explain.result_rows},
      {"result_multiplicity",number(explain.total_multiplicity)},
      {"left_witness_product",number(explain.left_witness_product)},
      {"right_witness_product",number(explain.right_witness_product)},
      {"left_prefix_product_sum",number(explain.left_prefix_product_sum)},
      {"right_prefix_product_sum",number(explain.right_prefix_product_sum)},
      {"estimates",estimates(plan.estimates(counts))}};
}
Json apply(rd::Runtime& owner, const PhysicalSetUpdate& update) {
  try {
    const auto epoch = owner.apply(update);
    return {{"error",nullptr},{"changed",epoch.input.input.physical_changed},{"changes",changes(epoch.changes)},
        {"source_aliases",epoch.input.input.metrics.aliases_visited},
        {"metrics",{{"work",epoch.metrics.work},{"recomputed",epoch.metrics.recomputed},
            {"left_assignments",epoch.metrics.left_assignments},{"right_assignments",epoch.metrics.right_assignments},
            {"left_keys",epoch.metrics.left_keys},{"right_keys",epoch.metrics.right_keys},{"changes",epoch.metrics.changes}}}};
  } catch (const Error& error) { return {{"error",error.code()}}; }
}
Json evaluate(const Json& request) {
  const auto document = io::read_document(request.at("document").dump());
  auto right_json = request.at("document"); right_json["query"] = request.at("right_query");
  const auto right = io::read_document(right_json.dump());
  for (const auto& source : document.initial.tables)
    if (!source.empty()) throw std::runtime_error("difference driver starts empty; use physical events");
  const auto spelling = request.at("mode").get<std::string>();
  if (spelling != "set_except" && spelling != "bag_except_all") throw std::runtime_error("unknown difference mode");
  const auto mode = spelling == "set_except" ? pd::Mode::set_except : pd::Mode::bag_except_all;
  const auto options = request.value("indexed",false) ? s04_runtime::options() : PhysicalOptions{};
  const auto plan = pd::admit(document.catalog,document.query,right.query,mode,options); rd::Runtime owner(plan);
  Json initial = snapshot(owner,plan), trace = Json::array();
  for (const auto& input : request.at("events")) {
    Row values; for (const auto& value : input.at("values")) values.push_back(io::read_scalar(value));
    const auto op = input.at("op").get<std::string>();
    if (op != "insert" && op != "delete") throw std::runtime_error("invalid difference source operation");
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

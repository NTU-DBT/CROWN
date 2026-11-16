#include "crown/runtime/star.hpp"
#include "crown/io/document.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using io::Json;
namespace st = runtime::star;

// Execution only. The separate Python oracle joins the complete original CQ;
// neither this driver nor the star source-only program supplies expected rows.
FreeConnexTree original_tree(const Query& query,std::size_t center) {
  if (center >= query.atoms.size()) throw std::runtime_error("invalid test center");
  FreeConnexTree tree; tree.root = NodeId{center};
  for (std::size_t i = 0; i < query.atoms.size(); ++i) {
    VariableSet scope;
    for (const auto& term : query.atoms[i].terms)
      if (const auto* variable = std::get_if<VariableId>(&term)) scope.insert(*variable);
    tree.nodes.push_back({"n"+std::to_string(i),NodeKind::native,std::move(scope),{},i,{}});
  }
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    if (i != center) tree.nodes[center].children.push_back(NodeId{i});
  return tree;
}
Json snapshot(const st::Runtime& owner) {
  Relation answer; auto cursor = owner.results();
  while (auto tuple = cursor.next())
    if (!answer.insert(storage::export_row(tuple->values())).second)
      throw std::runtime_error("native star emitted a duplicate projected output");
  const auto metrics = cursor.metrics();
  const auto sources = owner.source_snapshot(); Json tables = Json::array();
  for (const auto& table : sources.tables) tables.push_back(io::write_relation(table));
  const auto state = owner.state(); Json dimensions = Json::array();
  for (const auto& dimension : state.dimensions)
    dimensions.push_back({{"h",dimension.h},{"scale",dimension.scale},{"keys",dimension.keys},
        {"heavy_keys",dimension.heavy_keys},{"threshold",dimension.threshold?Json(*dimension.threshold):Json(nullptr)}});
  return {{"sequence",owner.sequence()},{"ready",owner.ready()},{"rows",io::write_relation(answer)},
      {"source",std::move(tables)},{"center_rows",state.center_rows},{"groups",state.groups},
      {"live_groups",state.live_groups},{"dimensions",std::move(dimensions)},
      {"cursor",{{"work",metrics.work},{"candidates",metrics.candidates},{"duplicates",metrics.duplicates},
          {"outputs",metrics.outputs},{"candidate_quantum",metrics.candidate_quantum}}}};
}
Json apply(st::Runtime& owner,const PhysicalSetUpdate& update) {
  try {
    const auto event = owner.apply(update); const auto& m = event.maintenance;
    return {{"error",nullptr},{"changed",event.physical_changed},
        {"metrics",{{"work",m.work},{"center_changes",m.center_changes},{"satellite_changes",m.satellite_changes},
            {"center_visits",m.center_visits},{"group_visits",m.group_visits},{"projection_changes",m.projection_changes},
            {"key_relabels",m.key_relabels},{"migrated_rows",m.migrated_rows},{"scale_resets",m.scale_resets},
            {"generic_aliases",event.source_metrics.aliases_visited},{"generic_crossings",event.source_metrics.native_crossings}}}};
  } catch (const Error& error) { return {{"error",error.code()}}; }
  catch (const resource::MemoryFailure& error) { return {{"error",std::string(error.code())}}; }
}
Json evaluate(const Json& request) {
  const auto document = io::read_document(request.at("document").dump());
  for (const auto& table : document.initial.tables)
    if (!table.empty()) throw std::runtime_error("star driver starts empty; load with original physical events");
  const auto center = request.at("center").get<std::size_t>();
  auto options = request.value("indexed",false)?s04_runtime::options():PhysicalOptions{};
  if (options.indexed_storage)
    options.indexed_storage->per_table.indices = std::max(options.indexed_storage->per_table.indices,
        document.query.atoms.size()+2);
  const auto general = planner::lower_tree(document.catalog,document.query,original_tree(document.query,center),options);
  const auto plan = planner::star::admit(general,OccurrenceId{center});
  st::Runtime owner(plan); Json initial = snapshot(owner), trace = Json::array();
  for (const auto& input : request.at("events")) {
    Row values; for (const auto& value : input.at("values")) values.push_back(io::read_scalar(value));
    const auto operation = input.at("op").get<std::string>();
    if (operation != "insert" && operation != "delete") throw std::runtime_error("invalid test operation");
    const PhysicalSetUpdate update{input.at("sequence").get<std::uint64_t>(),TableId{input.at("table").get<std::size_t>()},
        operation == "insert"?SetOperation::insert:SetOperation::erase,std::move(values)};
    auto result = apply(owner,update); owner.check_invariants();
    trace.push_back({{"event",std::move(result)},{"snapshot",snapshot(owner)}});
  }
  return {{"id",request.at("id")},{"dimension",plan.dimension()},{"distinct_head",plan.distinct_head()},
      {"original_atoms",plan.general().query().atoms.size()},{"source_only_atoms",plan.source_only().query().atoms.size()},
      {"initial",std::move(initial)},{"trace",std::move(trace)}};
}
} // namespace

int main() {
  try {
    for (std::string line; std::getline(std::cin,line);) std::cout << evaluate(Json::parse(line)).dump() << '\n';
    return 0;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

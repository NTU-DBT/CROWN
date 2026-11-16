#pragma once
#include "component_request.hpp"
#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/physical.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/delta.hpp>
#include <iostream>
#include <map>

// Cold native admission and observation helpers. Baseline adapters continue to
// include only component_request.hpp; no engine hook or virtual owner is added.
namespace component {
using namespace crown;
struct SetProgram {
  Catalog catalog;
  PhysicalOptions physical;
  CompiledProgram program;
};
inline PhysicalOptions physical_options(const Json& native) {
  const auto encoded = native.value("physical_options", Json::object());
  return encoded.is_object() && encoded.empty() ? PhysicalOptions{} : io::read_physical_options(encoded.dump());
}
inline SetProgram compile_set(const Json& document) {
  const auto& input = document.at("program");
  auto catalog = io::read_catalog(input.at("catalog").dump());
  auto admitted = frontend::admit_sql(input.at("sql").get<std::string>(), catalog);
  require(admitted.status == frontend::AdmissionStatus::admitted && admitted.program.has_value(),
      "set SQL was not admitted");
  const auto options = physical_options(document.at("native"));
  FreeConnexTree tree;
  if (input.contains("compiled_set") && !input.at("compiled_set").is_null()) {
    // Imported flags are insufficient. Replay the whole artifact and compare its
    // complete original normalization, then lower its tree under this backend.
    const auto selected = io::read_physical(input.at("compiled_set").dump());
    require(io::write_physical_source(selected.catalog(), selected.query(), selected.normalized()) ==
        io::write_physical_source(admitted.program->core_catalog, admitted.program->core, admitted.program),
        "supplied set plan differs from the actual original SQL/catalog binding");
    tree = selected.tree();
  } else if (admitted.route != frontend::AdmissionRoute::constant_empty) {
    const auto selected = planner::minimum_tree(admitted.program->core_catalog, admitted.program->core);
    require(selected.status == planner::OracleStatus::proven_minimum && selected.tree.has_value(),
        "set source has no proved admissible tree");
    tree = *selected.tree;
  }
  auto compiled = CompiledProgram::standalone(planner::lower_normalized(*admitted.program, tree, options));
  return {std::move(catalog), options, std::move(compiled)};
}
inline runtime::DeltaOptions delta_options(const Json& native) {
  runtime::DeltaOptions options;
  options.physical.support.memory_limit_bytes = number(native.at("memory_limit_bytes"));
  const auto work = number(native.value("work_limit", Json(1000000)));
  options.work_limit = work; options.physical.work_limit = work;
  options.physical.support.work_limit = work; options.cursor.work_limit = work;
  options.epoch_view.work_limit = work;
  options.spool_row_limit = number(native.value("spool_rows", Json(65536)), SIZE_MAX);
  options.spool_byte_limit = number(native.value("spool_bytes", Json(64U*1024U*1024U)), SIZE_MAX);
  const auto mode = native.value("mode", std::string("delta"));
  require(mode == "delta" || mode == "maintenance", "unknown native set mode");
  options.mode = mode == "delta" ? runtime::DeltaMode::delta : runtime::DeltaMode::maintenance;
  const auto live = native.value("live_maintenance", std::string("on_output"));
  require(live == "on_output" || live == "incremental" || live == "eager", "unknown live-maintenance policy");
  options.live_maintenance = live == "on_output" ? runtime::LiveMaintenance::on_output :
      live == "incremental" ? runtime::LiveMaintenance::incremental : runtime::LiveMaintenance::eager;
  const auto completion = native.value("completion", std::string("automatic"));
  require(completion == "automatic" || completion == "ordered_replay" || completion == "anchored" || completion == "root_first",
      "unknown delta completion policy");
  options.completion = completion == "automatic" ? runtime::DeltaCompletion::automatic :
      completion == "ordered_replay" ? runtime::DeltaCompletion::ordered_replay :
      completion == "anchored" ? runtime::DeltaCompletion::anchored : runtime::DeltaCompletion::root_first;
  options.view = runtime::ResultView::sql;
  return options;
}
inline std::vector<TableId> target_tables(const Request& request, const Catalog& catalog) {
  std::map<std::string, TableId> names;
  for (std::size_t i=0; i<catalog.tables.size(); ++i) names.emplace(catalog.tables[i].name, TableId{i});
  std::vector<TableId> result; result.reserve(request.events.size());
  for (const auto& event : request.events) {
    const auto found = names.find(event.table);
    require(found != names.end(), "component event names an unknown table");
    result.push_back(found->second);
  }
  return result;
}
inline SetOperation operation(const Event& event) {
  return event.operation == "+" ? SetOperation::insert : SetOperation::erase;
}
inline Json tuple_values(storage::TupleValuesView values) {
  auto result = Json::array();
  for (const auto cell : values) result.push_back(io::write_scalar_view(cell));
  return result;
}
inline Json signed_values(SetOperation sign, storage::TupleValuesView values) {
  return {{"operation", sign == SetOperation::insert ? "+" : "-"}, {"values", tuple_values(values)}};
}
template<class Cells> Json nullable_values(const Cells& values) {
  auto result = Json::array();
  for (const auto& cell : values) result.push_back(cell ? io::write_scalar_view(*cell) : Json{});
  return result;
}
inline Json memory(const resource::MemoryStatistics& value) {
  return {{"limit_bytes", value.limit_bytes}, {"current_requested_bytes", value.current.requested_bytes},
      {"peak_requested_bytes", value.peak_requested_bytes}, {"current_allocations", value.current.allocations}};
}
inline void admit_capture(const Json& actual, U64& captured, const Request& request) {
  if (!request.verify) return;
  const auto bytes = static_cast<U64>(actual.dump().size());
  require(bytes <= request.max_bytes-captured, "component capture-byte limit exceeded");
  captured += bytes;
}
inline int report(Json value) {
  std::cout << value.dump() << '\n'; std::cout.flush();
  return std::cout ? 0 : 1;
}
} // namespace component

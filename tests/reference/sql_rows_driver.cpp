#include "crown/runtime/sql_rows.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include <iostream>

namespace {
using namespace crown;
using io::Json;
Json snapshot(const runtime::SqlRowsRuntime& runtime) {
  Json rows = Json::array(); auto cursor = runtime.results();
  while (auto result = cursor.next()) {
    Json values = Json::array();
    for (const auto& cell : result->tuple.view()) values.push_back(cell ? io::write_scalar_view(*cell) : Json{});
    rows.push_back({{"values", std::move(values)}, {"weight", result->multiplicity}});
  }
  return {{"sequence", runtime.sequence()}, {"rows", std::move(rows)}};
}
Json evaluate(const Json& request) {
  const auto catalog = io::read_catalog_payload(request.at("catalog"));
  frontend::SqlRowsBindOptions options;
  if (request.contains("parameter_columns")) {
    const auto parameters = io::read_catalog_payload({{"version", 1}, {"tables", Json::array({
        {{"name", "parameters"}, {"columns", request.at("parameter_columns")}}})}});
    options.binding.parameters = parameters.tables[0].columns;
    for (const auto& value : request.at("parameters")) {
      if (value.is_null()) options.parameters.emplace_back();
      else options.parameters.emplace_back(std::in_place, io::read_scalar(value));
    }
  }
  auto bound = frontend::bind_sql_rows(request.at("sql").get<std::string>(), catalog, options);
  if (const auto* error = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw Error(error->diagnostic.code, error->diagnostic.message);
  auto program = std::get<frontend::SqlRowsProgram>(std::move(bound));
  FreeConnexTree tree;
  if (!program.contradiction()) {
    const auto core = program.export_core(); const auto choice = planner::minimum_tree(core.catalog, core.query);
    if (choice.status != planner::OracleStatus::proven_minimum || !choice.tree)
      throw Error("oracle_tree", "SQL oracle fixture has no completely checked free-connex tree");
    tree = *choice.tree;
  }
  runtime::SqlRowsRuntime runtime(program, tree, request.value("indexed", false) ? s04_runtime::options() : PhysicalOptions{});
  Json trace = Json::array({snapshot(runtime)}), types = Json::array();
  for (const auto& output : program.outputs()) types.push_back({{"kind", static_cast<int>(output.type.kind)},
      {"nullable", output.type.nullable}, {"decimal", output.type.decimal ? Json::array({output.type.decimal->precision,
          output.type.decimal->scale}) : Json{}}});
  for (const auto& update : request.at("updates")) {
    runtime::aggregate::Row owned;
    for (const auto& value : update.at("values")) {
      if (value.is_null()) owned.emplace_back();
      else owned.emplace_back(std::in_place, io::read_scalar(value));
    }
    std::vector<runtime::sql_rows::Cell> borrowed;
    for (const auto& value : owned) {
      if (value) borrowed.emplace_back(std::in_place, storage::borrow_scalar(*value));
      else borrowed.emplace_back();
    }
    static_cast<void>(runtime.apply({runtime.sequence() + 1, TableId{update.at("table").get<std::size_t>()}, borrowed,
        update.at("before").get<std::uint64_t>(), update.at("after").get<std::uint64_t>()}));
    trace.push_back(snapshot(runtime));
  }
  return {{"id", request.at("id")}, {"types", std::move(types)}, {"trace", std::move(trace)}};
}
}  // namespace

int main() {
  try {
    for (std::string line; std::getline(std::cin, line);) std::cout << evaluate(Json::parse(line)).dump() << '\n';
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

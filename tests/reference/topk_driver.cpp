#include "crown/runtime/topk.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace {
using namespace crown;
using io::Json;
using namespace runtime;

Json tuple(const aggregate::Tuple& value) {
  Json result=Json::array();
  for(const auto& cell:value.view())result.push_back(cell?io::write_scalar_view(*cell):Json{});
  return result;
}
std::vector<topk::Key> order(const Json& request) {
  std::vector<topk::Key> result;
  for(const auto& key:request)result.push_back({key.at("field").get<std::size_t>(),
      key.at("direction")=="asc"?topk::Direction::ascending:topk::Direction::descending,
      key.at("nulls")=="first"?topk::NullOrder::first:topk::NullOrder::last});
  return result;
}
template<class Owner> Json snapshot(const Owner& owner,const Json& ranks) {
  Json output=Json::array();
  for(const auto& request:ranks) {
    const auto keys=order(request.at("order"));
    const auto ranked=snapshot_topk(owner,keys,request.at("k").get<std::uint64_t>());
    Json entries=Json::array();
    for(const auto& row:ranked.entries)entries.push_back({{"identity",tuple(row.identity)},
        {"values",tuple(row.values)},{"weight",row.multiplicity}});
    output.push_back({{"selected_rows",ranked.selected_rows},{"entries",std::move(entries)},
        {"work",ranked.metrics.work},{"candidates",ranked.metrics.candidates},
        {"comparisons",ranked.metrics.comparisons},{"fields",ranked.metrics.fields},
        {"scalar_bytes",ranked.metrics.scalar_bytes}});
  }
  return {{"sequence",owner.sequence()},{"ranked",std::move(output)}};
}
FreeConnexTree tree(const frontend::SqlRowsProgram& program) {
  if(program.contradiction())return {};
  const auto core=program.export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
  if(chosen.status!=planner::OracleStatus::proven_minimum || !chosen.tree)
    throw Error("topk_oracle_tree","top-k source has no completely checked tree");
  return *chosen.tree;
}
template<class Owner> Json trace(Owner& owner,const Json& request) {
  Json result=Json::array({snapshot(owner,request.at("ranks"))});
  for(const auto& update:request.at("updates")) {
    aggregate::Row owned;
    for(const auto& value:update.at("values")) {
      if(value.is_null())owned.emplace_back();else owned.emplace_back(io::read_scalar(value));
    }
    std::vector<sql_rows::Cell> values;
    for(const auto& cell:owned)values.push_back(cell?sql_rows::Cell{storage::borrow_scalar(*cell)}:sql_rows::Cell{});
    const std::array edits{sql_rows::SourceReplacement{TableId{update.value("table",std::size_t{0})},values,
        update.at("before").get<std::uint64_t>(),update.at("after").get<std::uint64_t>()}};
    static_cast<void>(owner.prepare_batch({owner.sequence()+1,edits}).commit());
    result.push_back(snapshot(owner,request.at("ranks")));
  }
  return result;
}
Json evaluate(const Json& request) {
  const auto schema=io::read_catalog_payload(request.at("catalog"));
  const auto physical=request.value("indexed",false)?s04_runtime::options():PhysicalOptions{};
  const auto sql=request.at("sql").get<std::string>();
  if(request.at("family")=="rows") {
    auto bound=frontend::bind_sql_rows(sql,schema);
    if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&bound))throw Error(failure->diagnostic.code,failure->diagnostic.message);
    auto program=std::get<frontend::SqlRowsProgram>(std::move(bound));
    SqlRowsRuntime owner(program,tree(program),physical);
    return {{"id",request.at("id")},{"trace",trace(owner,request)}};
  }
  frontend::SqlAggregateBindOptions options;options.kernel.average_scale=request.value("average_scale",std::uint8_t{2});
  auto bound=frontend::bind_sql_aggregate(sql,schema,options);
  if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&bound))throw Error(failure->diagnostic.code,failure->diagnostic.message);
  auto program=std::get<frontend::SqlAggregateProgram>(std::move(bound));
  SqlAggregateRuntime owner(program,tree(program.source_program()),physical);
  return {{"id",request.at("id")},{"trace",trace(owner,request)}};
}
} // namespace

int main() {
  try {
    for(std::string line;std::getline(std::cin,line);)std::cout<<evaluate(Json::parse(line)).dump()<<'\n';
  }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}

#include "crown/planner/keys.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/io/document.hpp"
#include "crown/io/catalog.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include <iostream>
#include <optional>
#include <stdexcept>

namespace {
using namespace crown;
using io::Json;
namespace keys=planner::keys;

// Only genuine native execution is performed here. Expected relations and
// expected constraint decisions belong to the separate Python full-state model.
Json snapshot(const runtime::PhysicalRuntime& owner) {
  Relation result;auto cursor=owner.results();
  while(auto tuple=cursor.next())result.insert(storage::export_row(tuple->values()));
  const auto source=owner.snapshot();Json tables=Json::array();
  for(const auto& table:source.physical.tables)tables.push_back(io::write_relation(table));
  return {{"sequence",owner.sequence()},{"ready",owner.ready()},
      {"rows",io::write_relation(result)},{"source",std::move(tables)}};
}
Json metrics(const runtime::PhysicalMetrics& value) {
  return {{"source_changes",value.source_changes},{"aliases_visited",value.aliases_visited},
      {"aliases_filtered",value.aliases_filtered},{"native_crossings",value.native_crossings},
      {"constraint_validations",value.constraint_validations},{"constraint_rows",value.constraint_rows}};
}
Json apply(runtime::PhysicalRuntime& owner,const PhysicalSetUpdate& update) {
  try {const auto epoch=owner.apply(update);return {{"error",nullptr},{"metrics",metrics(epoch.input.metrics)}};}
  catch(const Error& error) {return {{"error",error.code()},{"metrics",nullptr}};}
}

Json evaluate(const Json& request) {
  const auto document=io::read_document(request.at("document").dump());
  const auto choice=planner::minimum_tree(document.catalog,document.query);
  if(choice.status!=planner::OracleStatus::proven_minimum || !choice.tree)
    throw std::runtime_error("key oracle original query has no checked tree");
  const auto options=request.value("indexed",false)?s04_runtime::options():PhysicalOptions{};
  const auto general=planner::lower_tree(document.catalog,document.query,*choice.tree,options);
  const auto before=general.physical_sha256();const auto plan=keys::specialize(general);
  auto generic=runtime::PhysicalRuntime::initialize(plan.general(),document.initial);
  auto execution=runtime::PhysicalRuntime::initialize(plan.execution(),document.initial);
  Json removed=Json::array(),occurrences=Json::array(),variables=Json::array(),head=Json::array();
  for(const auto& rule:plan.eliminations())removed.push_back({{"removed",rule.removed.value},
      {"witness",rule.witness.value},{"foreign_key",rule.foreign_key},{"unique_key",rule.unique_key}});
  for(const auto id:plan.occurrences())occurrences.push_back(id.value);
  for(const auto id:plan.variables())variables.push_back(id.value);
  for(const auto& output:plan.execution().query().head)head.push_back(plan.variables()[output.variable.value].value);
  bool reduced_valid=false,original_valid=false;
  if(plan.reduced_certificate()) {
    reduced_valid=planner::verify_height_certificate(document.catalog,plan.execution().query(),*plan.reduced_certificate()).valid;
    original_valid=planner::verify_height_certificate(document.catalog,document.query,*plan.reduced_certificate()).valid;
  }
  const bool catalogs=io::write_catalog_payload(plan.general().source_catalog())==
      io::write_catalog_payload(plan.execution().source_catalog());
  Json initial={{"general",snapshot(generic)},{"execution",snapshot(execution)}};
  Json trace=Json::array();
  for(const auto& input:request.at("events")) {
    Row values;for(const auto& cell:input.at("values"))values.push_back(io::read_scalar(cell));
    const auto operation=input.at("op").get<std::string>();
    if(operation!="insert" && operation!="delete")throw std::runtime_error("invalid oracle operation");
    const PhysicalSetUpdate update{input.at("sequence").get<std::uint64_t>(),
        TableId{input.at("table").get<std::size_t>()},
        operation=="insert"?SetOperation::insert:SetOperation::erase,std::move(values)};
    const auto a=apply(generic,update),b=apply(execution,update);
    generic.check_invariants();execution.check_invariants();
    trace.push_back({{"general_event",a},{"execution_event",b},
        {"general",snapshot(generic)},{"execution",snapshot(execution)}});
  }
  return {{"id",request.at("id")},{"specialized",plan.specialized()},
      {"reason",static_cast<int>(plan.reason())},{"eliminations",std::move(removed)},
      {"occurrences",std::move(occurrences)},{"variables",std::move(variables)},
      {"head_original",std::move(head)},{"source_catalog_preserved",catalogs},
      {"general_unchanged",general.physical_sha256()==before},
      {"general_atoms",document.query.atoms.size()},{"execution_atoms",plan.execution().query().atoms.size()},
      {"reduced_certificate_valid",reduced_valid},{"original_certificate_valid",original_valid},
      {"initial",std::move(initial)},{"trace",std::move(trace)}};
}
} // namespace

int main() {
  try {
    for(std::string line;std::getline(std::cin,line);)std::cout<<evaluate(Json::parse(line)).dump()<<'\n';
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

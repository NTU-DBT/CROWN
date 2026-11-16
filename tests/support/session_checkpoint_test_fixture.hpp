#pragma once
#include "crown/runtime/session_checkpoint.hpp"
#include "crown/frontend/normalize.hpp"
#include "indexed_runtime_fixture.hpp"
#include "evaluator.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <iostream>
#include <sstream>
#include <set>
#include <stdexcept>
#include <thread>
namespace crown::session_checkpoint_test {
using namespace crown;
using namespace crown::runtime;
inline void check(bool value,const char* message){if(!value)throw std::runtime_error(message);}
using Output=std::set<std::pair<SetOperation,Row>>;
inline void grant(const QuerySession& session,bool indexed) {
#ifdef CROWN_RUNTIME_TESTING
  const auto value=RuntimeTestProbe::index_work(session);
  check(indexed?(value && value->fresh_operations==1):!value,"session restore minted another indexed allowance");
#else
  static_cast<void>(session);static_cast<void>(indexed);
#endif
}
// Native snapshot capture is separate from these ordinary deep row exports.
inline Relation rows(const QuerySession& session) {
  const auto snapshot=session.snapshot();Relation result;
  for(const auto& value:snapshot.rows)check(result.insert(storage::export_row(value.values())).second,"duplicate snapshot row");
  return result;
}
inline Output difference(const Relation& before,const Relation& after) {
  Output result;
  for(const auto& row:before){if(!after.contains(row))result.emplace(SetOperation::erase,row);}
  for(const auto& row:after){if(!before.contains(row))result.emplace(SetOperation::insert,row);}
  return result;
}
inline Output finish(QuerySession& session) {
  while(session.step()!=DeltaStep::prepared){}
  session.commit();Output result;std::uint64_t ordinal=0;
  while(auto value=session.next_output()) {
    check(value->ordinal==++ordinal,"noncontiguous session output ordinal");
    check(result.emplace(value->operation,storage::export_row(value->tuple.values())).second,"duplicate signed output");
  }
  return result;
}
inline void enqueue(QuerySession& session,const io::InputItem& item) {
  io::TransportBatch batch({item});check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"source event not admitted");
}
// Supported kinds are 0..5; plan admission is real, update/model data is ordinary.
struct Case {PhysicalPlan plan;std::vector<PhysicalSetUpdate> updates;unsigned kind;};
inline Case fixture(bool indexed,unsigned kind) {
  const auto options=indexed?s04_runtime::options():PhysicalOptions{};
  if(kind==1) {
    Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
    Query query{{{"x",ScalarType::int64},{"z",ScalarType::int64},{"y",ScalarType::int64}},
        {{"a",TableId{0},{VariableId{0},VariableId{1}}},{"b",TableId{0},{VariableId{1},VariableId{2}}}},
        {{VariableId{0},"x"},{VariableId{1},"z"},{VariableId{2},"y"}},false};
    FreeConnexTree tree{NodeId{0},{{"g",NodeKind::generalized,{VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
        {"a",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},{"b",NodeKind::native,{VariableId{1},VariableId{2}},{},1,{}}},{},{}};
    return {planner::lower_tree(catalog,query,tree,options),{{1,TableId{0},SetOperation::insert,{std::int64_t{1},std::int64_t{2}}},
      {2,TableId{0},SetOperation::insert,{std::int64_t{2},std::int64_t{3}}},{3,TableId{0},SetOperation::insert,{std::int64_t{2},std::int64_t{2}}},
      {4,TableId{0},SetOperation::erase,{std::int64_t{1},std::int64_t{2}}}},kind};
  }
  if(kind==2) {
    Catalog catalog{5,{{"r",{{"x",ScalarType::int64}}},{"s",{{"y",ScalarType::int64}}}}};
    Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}},{"s",TableId{1},{VariableId{1}}}},
        {{VariableId{0},"x"},{VariableId{1},"y"}},false};
    FreeConnexTree tree{NodeId{0},{{"g",NodeKind::generalized,{},{NodeId{1},NodeId{2}},{},{}},
        {"r",NodeKind::native,{VariableId{0}},{},0,{}},{"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
    return {planner::lower_tree(catalog,query,tree,options),{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},
      {2,TableId{1},SetOperation::insert,{std::int64_t{7}}},{3,TableId{0},SetOperation::insert,{std::int64_t{2}}},
      {4,TableId{1},SetOperation::erase,{std::int64_t{7}}}},kind};
  }
  if(kind==3) {
    Catalog catalog{5,{{"r",{}}}};Query query{{},{{"r",TableId{0},{}}},{},false};
    FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{},{},0,{}}},{},{}};
    return {planner::lower_tree(catalog,query,tree,options),{{1,TableId{0},SetOperation::insert,{}},{2,TableId{0},SetOperation::insert,{}},
      {3,TableId{0},SetOperation::erase,{}},{4,TableId{0},SetOperation::insert,{}}},kind};
  }
  Catalog catalog{5,{{"r",{{"x",ScalarType::int64}}}}};std::optional<PhysicalPlan> plan;
  if(kind>=4) {
    auto bound=frontend::bind_sql(kind==4?"SELECT DISTINCT x FROM r WHERE x >= 0":"SELECT EXISTS(SELECT NULL FROM r)",catalog);
    check(std::holds_alternative<frontend::BoundSql>(bound),"SQL fixture did not bind");
    auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
    check(std::holds_alternative<frontend::NormalizedSql>(normalized),"SQL fixture did not normalize");
    auto program=std::get<frontend::NormalizedSql>(std::move(normalized));VariableSet scope;
    for(std::size_t i=0;i<program.core.variables.size();++i)scope.insert(VariableId{i});
    FreeConnexTree tree{NodeId{0},{{program.core.atoms.at(0).occurrence,NodeKind::native,std::move(scope),{},0,{}}},{},{}};
    plan=planner::lower_normalized(program,tree,options);
  }else {
    Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
    FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};plan=planner::lower_tree(catalog,query,tree,options);
  }
  return {std::move(*plan),{{1,TableId{0},SetOperation::insert,{std::int64_t{kind==4?-1:1}}},
    {2,TableId{0},SetOperation::insert,{std::int64_t{2}}},{3,TableId{0},SetOperation::erase,{std::int64_t{1}}},
    {4,TableId{0},SetOperation::erase,{std::int64_t{2}}}},kind};
}
inline Relation oracle(const Case& fixture,const Database& database) {
  if(fixture.kind==5)return Relation{{Row{!database.tables[0].empty()}}};
  if(fixture.kind==4){Relation result;for(const auto& row:database.tables[0])if(std::get<std::int64_t>(row[0])>=0)result.insert(row);return result;}
  return reference::evaluate(fixture.plan.source_catalog(),fixture.plan.query(),database);
}
// Native commit precedes model/export assertions; later failure cannot roll it back.
inline Output step(QuerySession& session,const Case& fixture,Database& database,const PhysicalSetUpdate& update,DeltaMode mode) {
  const auto before=oracle(fixture,database);auto after=database;
  if(update.operation==SetOperation::insert)after.tables[update.table.value].insert(update.values);else after.tables[update.table.value].erase(update.values);
  enqueue(session,io::InputEvent{update,io::SourcePosition{"feed",update.sequence*10}});
  check(session.begin_next(),"session had no admitted event");const auto output=finish(session);
  check(output==(mode==DeltaMode::delta?difference(before,oracle(fixture,after)):Output{}),"session delta disagrees with independent definition");
  database=std::move(after);check(rows(session)==oracle(fixture,database),"session snapshot disagrees with independent definition");return output;
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}catch(const Error&){failed=true;}
  check(failed,"invalid session checkpoint accepted");
}
} // namespace crown::session_checkpoint_test

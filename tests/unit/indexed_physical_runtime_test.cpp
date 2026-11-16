#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/planner/lower.hpp"
#include "crown/io/support.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stdexcept>
#include <utility>
#include <type_traits>

namespace {
using namespace crown;
using namespace crown::runtime;
using Assignment=std::map<VariableId,Value>;
using Assignments=std::set<Assignment>;
using Counts=std::map<Row,std::uint64_t>;
using Adapter=std::function<std::optional<Assignment>(OccurrenceId,const Row&)>;
std::size_t verified=0;
void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(message); }
Value n(std::int64_t value) { return value; }
template<class Action> void error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) { check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code()); return; }
  throw std::runtime_error("missing error "+std::string(code));
}
Row project(const Assignment& assignment,const auto& variables) {
  Row result; for (const auto variable : variables) result.push_back(assignment.at(variable)); return result;
}
Assignment assignment(const Row& row,const auto& variables) {
  check(row.size()==variables.size(),"assignment shape"); Assignment result;
  for (std::size_t i=0;i<row.size();++i) result.emplace(variables[i],row[i]);
  return result;
}
Relation project(const Assignments& source,const auto& variables) {
  Relation result; for (const auto& item : source) result.insert(project(item,variables)); return result;
}
Assignments join(const Assignments& left,const Assignments& right) {
  Assignments result;
  for (const auto& a : left) for (const auto& b : right) {
    auto combined=a; bool matches=true;
    for (const auto& [key,value] : b) {
      const auto [found,inserted]=combined.emplace(key,value);
      if (!inserted && found->second!=value) { matches=false; break; }
    }
    if (matches) result.insert(std::move(combined));
  }
  return result;
}
std::optional<Assignment> raw_atom(const auto& atom,const Row& row) {
  Assignment result;
  for (std::size_t i=0;i<atom.terms.size();++i) {
    if (const auto* variable=std::get_if<VariableId>(&atom.terms[i])) {
      const auto [found,inserted]=result.emplace(*variable,row[i]);
      if (!inserted && found->second!=row[i]) return {};
    } else if (const auto* fixed=std::get_if<1>(&atom.terms[i]); fixed && reference::input::scalar(*fixed)!=row[i]) return {};
  }
  return result;
}
std::vector<VariableId> separator(const auto& plan,const auto& node) {
  std::vector<VariableId> result;
  if (node.parent) {
    const auto& parent=plan.nodes()[node.parent->value];
    std::set_intersection(node.scope.begin(),node.scope.end(),parent.scope.begin(),parent.scope.end(),std::back_inserter(result));
  }
  return result;
}
Counts projected_counts(const Relation& rows,const auto& scope,const auto& key) {
  Counts result; for (const auto& row : rows) ++result[project(assignment(row,scope),key)]; return result;
}
Counts keys(const std::vector<ProjectionKeySnapshot>& input) {
  Counts result; for (const auto& item : input) check(result.emplace(crown::storage::export_row(item.key.values()),item.support.value).second,"duplicate snapshot key"); return result;
}

// Full assignment joins from physical rows, independent of routing, support
// propagation, numeric adapters and the runtime's own invariant checker.
void verify(const PhysicalRuntime& runtime,const Database& database,const Adapter& adapter={}) {
  const auto& plan=runtime.plan(); const auto state=runtime.snapshot();
  check(state.sequence==runtime.sequence() && state.support.sequence==state.sequence,"coordinated sequence");
  check(state.physical.tables==database.tables,"physical source state differs");
  if (plan.route()!=PhysicalRoute::tree) {
    check(state.support.has_answer==(plan.route()==PhysicalRoute::constant_true),"constant truth");
    check(state.support.nodes.empty() && state.derivations.empty(),"constant route has logical ports");
    runtime.check_invariants(); ++verified; return;
  }
  std::vector<Assignments> local(plan.inputs().size()), subtree(plan.nodes().size());
  std::vector<Counts> counts(local.size());
  for (const auto& input : plan.inputs()) {
    const auto& node=plan.nodes()[input.node.value];
    for (const auto& row : database.tables[input.base.value]) {
      const auto mapped=adapter?adapter(input.occurrence,row):raw_atom(plan.query().atoms[input.occurrence.value],row);
      if (!mapped) continue;
      local[input.occurrence.value].insert(*mapped); ++counts[input.occurrence.value][project(*mapped,node.scope)];
    }
    Counts actual;
    for (const auto& item : state.derivations[input.occurrence.value]) {
      check(item.count>0,"zero derivation retained"); actual.emplace(crown::storage::export_row(item.tuple.values()),item.count);
      check(runtime.derivation_count(input.occurrence,crown::storage::export_row(item.tuple.values()))==item.count,"count lookup differs");
    }
    check(actual==counts[input.occurrence.value],"derivation counts differ from full physical recomputation");
  }
  std::vector<NodeId> order{*plan.tree().root};
  for (std::size_t i=0;i<order.size();++i) for (const auto child : plan.nodes()[order[i].value].children) order.push_back(child);
  for (auto it=order.rbegin();it!=order.rend();++it) {
    const auto& node=plan.nodes()[it->value]; const auto& snapshot=state.support.nodes[it->value];
    auto result=node.occurrence?local[node.occurrence->value]:Assignments{Assignment{}};
    for (const auto child : node.children) result=join(result,subtree[child.value]);
    subtree[it->value]=std::move(result);
    const auto survivors=project(subtree[it->value],node.scope);
    Relation actual_survivors; for (const auto& tuple : snapshot.survivors) actual_survivors.insert(crown::storage::export_row(tuple.values()));
    check(actual_survivors==survivors,"subtree survivors differ from assignment joins");
    Relation expected_records;
    if (node.occurrence) expected_records=project(local[node.occurrence->value],node.scope);
    else for (const auto child : node.children) {
      const auto child_keys=project(subtree[child.value],node.scope); expected_records.insert(child_keys.begin(),child_keys.end());
    }
    Relation actual_records;
    for (const auto& record : snapshot.records) {
      actual_records.insert(crown::storage::export_row(record.tuple.values())); const auto values=assignment(crown::storage::export_row(record.tuple.values()),node.scope);
      std::vector<bool> flags; std::size_t satisfied=0;
      for (const auto child : node.children) {
        const auto child_separator=separator(plan,plan.nodes()[child.value]);
        const bool present=project(subtree[child.value],child_separator).contains(project(values,child_separator));
        flags.push_back(present); if (present) ++satisfied;
      }
      check(record.child_present==flags && record.satisfied.value==satisfied && record.survives==survivors.contains(crown::storage::export_row(record.tuple.values())),"child flags or satisfaction differ");
    }
    check(actual_records==expected_records,"candidate/native membership differs");
    check(keys(snapshot.parent_keys)==projected_counts(survivors,node.scope,separator(plan,node)),"P count differs");
    if (snapshot.visible_keys) check(keys(*snapshot.visible_keys)==projected_counts(survivors,node.scope,node.visible_scope),"E count differs");
  }
  Assignments body{Assignment{}};
  for (const auto& occurrence : local) body=join(body,occurrence);
  std::vector<VariableId> head; for (const auto& output : plan.query().head) head.push_back(output.variable);
  const auto expected=project(body,head);
  Assignments visible{Assignment{}};
  for (const auto& node : plan.nodes()) if (node.visible_relation) {
    Assignments rows;
    for (const auto& item : *state.support.nodes[node.id.value].visible_keys) rows.insert(assignment(crown::storage::export_row(item.key.values()),node.visible_scope));
    visible=join(visible,rows);
  }
  check(project(visible,head)==expected && state.support.has_answer==!expected.empty(),"full result or truth differs");
  if (!adapter) check(expected==reference::evaluate(reference::input::catalog(plan.catalog()),reference::input::query(plan.query()),database),"A04 oracle differs from physical assignment interpreter");
  runtime.check_invariants(); ++verified;
}
PhysicalPlan loop_plan(bool boolean=false) {
  const Catalog catalog{1,{{"edge",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"payload",ScalarType::string}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"forward",TableId{0},{VariableId{0},VariableId{1},IgnoredColumn{}}},
       {"reverse",TableId{0},{VariableId{1},VariableId{0},IgnoredColumn{}}}}, {},false};
  if (!boolean) query.head={{VariableId{0},"x"},{VariableId{1},"y"},{VariableId{0},"again"}};
  const FreeConnexTree tree{NodeId{0},{{"root",NodeKind::generalized,{VariableId{0},VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
      {"forward",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},
      {"reverse",NodeKind::native,{VariableId{0},VariableId{1}},{},1,{}}},{},{}};
  return s04_runtime::lower_tree(catalog,query,tree);
}
Row edge(std::int64_t x,std::int64_t y,std::string payload="a") { return {n(x),n(y),Value{std::move(payload)}}; }
PhysicalRuntimeOptions options(PropagationOrder order=PropagationOrder::fifo) {
  PhysicalRuntimeOptions result; result.support.capture_transitions=true; result.support.order=order; return result;
}
void generated_aliases() {
  for (const auto order : {PropagationOrder::fifo,PropagationOrder::lifo}) for (const auto seed : {std::uint64_t{7},std::uint64_t{91}}) {
    PhysicalRuntime runtime(loop_plan(),options(order)); Database database; database.tables.resize(1); auto random=seed;
    std::uint64_t sequence=0;
    for (std::size_t i=0;i<100;++i) {
      random=random*6364136223846793005ULL+1442695040888963407ULL;
      const auto x=static_cast<std::int64_t>((random>>8)%3),y=static_cast<std::int64_t>((random>>16)%3);
      const auto row=edge(x,y,((random>>24)%2)==0?"a":"b");
      const auto operation=((random>>32)%2)==0?SetOperation::insert:SetOperation::erase;
      const bool changed=operation==SetOperation::insert?database.tables[0].insert(row).second:database.tables[0].erase(row)!=0;
      const auto epoch=runtime.apply({++sequence,TableId{0},operation,row});
      check(epoch.input.physical_changed==changed && epoch.input.sequence==sequence && epoch.support.sequence==sequence,"physical epoch header");
      if (changed) {
        check(epoch.input.metrics.aliases_visited==2 && epoch.input.derivations.size()==2,"fan-out omitted an alias");
        check(epoch.input.derivations[0].occurrence==OccurrenceId{0} && epoch.input.derivations[1].occurrence==OccurrenceId{1},"nondeterministic alias order");
        check(epoch.input.source && epoch.input.source->tuple().values()==row,"source change value");
      } else check(epoch.input.metrics.work==0 && epoch.support.metrics.work==0 && !epoch.input.source && !epoch.support.journal,"physical no-op charged or retained work");
      verify(runtime,database);
    }
    const auto remaining=database.tables[0];
    for (const auto& row : remaining) {
      static_cast<void>(runtime.apply({++sequence,TableId{0},SetOperation::erase,row})); database.tables[0].erase(row); verify(runtime,database);
    }
    check(runtime.storage_statistics().derivation_keys==0 && !runtime.has_answer(),"alias cleanup retained logical state");
  }
}
struct Image {
  std::uint64_t sequence;
  std::vector<Relation> physical;
  io::Json support;
  std::vector<Counts> counts;
  bool operator==(const Image&) const=default;
};
Image image(const PhysicalRuntime& runtime) {
  auto state=runtime.snapshot(); Image result{state.sequence,std::move(state.physical.tables),io::write_support_snapshot(state.support,runtime.plan()),{}};
  for (const auto& items : state.derivations) { Counts counts; for (const auto& item : items) counts.emplace(crown::storage::export_row(item.tuple.values()),item.count); result.counts.push_back(std::move(counts)); }
  return result;
}
void busy(PhysicalRuntime& runtime,TupleHandle source,SupportHandle support) {
  error([&] { static_cast<void>(runtime.has_answer()); },"runtime_busy");
  error([&] { static_cast<void>(runtime.snapshot()); },"runtime_busy");
  error([&] { static_cast<void>(runtime.derivation_count(OccurrenceId{0},{n(1),n(1)})); },"runtime_busy");
  error([&] { static_cast<void>(runtime.find_source(TableId{0},edge(1,1))); },"runtime_busy");
  error([&] { static_cast<void>(runtime.get_source(TableId{0},source)); },"runtime_busy");
  error([&] { static_cast<void>(runtime.find_support(NodeId{1},SupportRole::records,{n(1),n(1)})); },"runtime_busy");
  error([&] { static_cast<void>(runtime.get_support(support)); },"runtime_busy");
  error([&] { static_cast<void>(runtime.storage_statistics()); },"runtime_busy");
  error([&] { runtime.check_invariants(); },"runtime_busy");
  error([&] { static_cast<void>(runtime.prepare({2,TableId{0},SetOperation::insert,edge(2,2)})); },"runtime_busy");
  error([&] { static_cast<void>(runtime.apply({2,TableId{0},SetOperation::insert,edge(2,2)})); },"runtime_busy");
}
void publication_and_derivations() {
  PhysicalRuntime runtime(loop_plan(),options()); auto first=runtime.apply({1,TableId{0},SetOperation::insert,edge(1,1)});
  const auto source=*runtime.find_source(TableId{0},edge(1,1)); const auto support=*runtime.find_support(NodeId{1},SupportRole::records,{n(1),n(1)});
  const auto before=image(runtime); const auto owner=runtime.owner(); const auto* plan=&runtime.plan(); const auto* layout=&runtime.source_layout(TableId{0});
  {
    auto pending=runtime.prepare({2,TableId{0},SetOperation::insert,edge(1,1,"b")}); busy(runtime,source,support);
    check(!runtime.ready() && runtime.sequence()==1 && runtime.owner()==owner && &runtime.plan()==plan && &runtime.source_layout(TableId{0})==layout,"immutable identity or last sequence changed");
    check(pending.preview().physical_changed && !pending.support().native_changed && !pending.support().journal,"duplicate projection changed native membership");
    check(pending.preview().derivations[0].before==1 && pending.preview().derivations[0].after==2 && !pending.preview().derivations[0].native_changed,"derivation increment missing");
    check(pending.snapshot().physical.tables[0].size()==2 && pending.snapshot().support.nodes[1].records.size()==1,"tentative source/native state differs");
  }
  check(runtime.ready() && image(runtime)==before,"destructor did not cancel prepared source and counts");
  auto pending=runtime.prepare({2,TableId{0},SetOperation::insert,edge(1,1,"b")});
  const auto committed=pending.commit(); check(!pending.active() && committed.input.physical_changed && !committed.support.native_changed,"projection-only commit");
  check(runtime.derivation_count(OccurrenceId{0},{n(1),n(1)})==2 && runtime.find_support(NodeId{1},SupportRole::records,{n(1),n(1)})==support,"positive derivation count changed stable native handle");
  static_cast<void>(runtime.apply({3,TableId{0},SetOperation::erase,edge(1,1)}));
  check(!runtime.get_source(TableId{0},source) && runtime.get_support(support) && runtime.has_answer(),"non-last derivation removal lost native row");
  check(first.input.source->tuple().values()==edge(1,1) && !first.input.source->retained.is_live(),"erased source pin lost payload");
  static_cast<void>(runtime.apply({4,TableId{0},SetOperation::erase,edge(1,1,"b")}));
  check(!runtime.get_support(support) && !runtime.has_answer(),"last derivation removal retained native row");
  const auto empty=image(runtime);
  error([&] { static_cast<void>(runtime.apply({5,TableId{99},SetOperation::insert,{}})); },"invalid_physical_update");
  error([&] { static_cast<void>(runtime.apply({6,TableId{0},SetOperation::insert,edge(3,3)})); },"invalid_sequence");
  error([&] { static_cast<void>(runtime.apply({5,TableId{0},SetOperation::insert,{n(1)}})); },"invalid_update");
  check(image(runtime)==empty,"invalid input changed state"); runtime.check_invariants();
}
void active_facade_moves() {
  PhysicalRuntime original(loop_plan(),options());
  static_cast<void>(original.apply({1,TableId{0},SetOperation::insert,edge(1,1)}));
  const auto source=*original.find_source(TableId{0},edge(1,1)); const auto owner=original.owner();
  auto pending=original.prepare({2,TableId{0},SetOperation::insert,edge(2,2)});
  PhysicalRuntime moved(std::move(original));
  error([&] { static_cast<void>(original.ready()); },"invalid_runtime");
  check(!moved.ready() && moved.owner()==owner && moved.sequence()==1,"active facade move lost its identity or busy state");
  PhysicalRuntime destination(loop_plan(),options()); destination=std::move(moved);
  error([&] { static_cast<void>(moved.sequence()); },"invalid_runtime");
  const auto epoch=pending.commit();
  check(destination.ready() && destination.sequence()==2 && destination.owner()==owner && destination.get_source(TableId{0},source) && epoch.input.physical_changed,"prepared token did not commit to moved facade");
  destination.check_invariants();
}
PhysicalPlan filtered_plan() {
  const Catalog source{3,{{"r",{{"x",ScalarType::int64},{"flag",ScalarType::int64},{"payload",ScalarType::string}}}}};
  const auto binding=frontend::bind_sql("SELECT DISTINCT a.x, a.x AS again FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1",source);
  check(std::holds_alternative<frontend::BoundSql>(binding),"SQL binding failed");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized),"SQL normalization failed");
  const auto program=std::get<frontend::NormalizedSql>(std::move(normalized));
  check(program.core.variables.size()==1 && program.core.atoms.size()==2,"unexpected filtered core geometry");
  const FreeConnexTree tree{NodeId{0},{{"root",NodeKind::generalized,{VariableId{0}},{NodeId{1},NodeId{2}},{},{}},
      {"a",NodeKind::native,{VariableId{0}},{},0,{}},{"b",NodeKind::native,{VariableId{0}},{},1,{}}},{},{}};
  return s04_runtime::lower_normalized(program,tree);
}
void sql_filters_and_later_alias_failure() {
  const auto plan=filtered_plan();
  const Adapter adapter=[](OccurrenceId occurrence,const Row& row)->std::optional<Assignment> {
    if (occurrence==OccurrenceId{0} && row[1]!=n(1)) return {};
    return Assignment{{VariableId{0},row[0]}};
  };
  PhysicalRuntime runtime(plan,options()); Database database; database.tables.resize(1); std::uint64_t sequence=0;
  for (const auto& row : {edge(1,2),edge(1,1),edge(1,1,"b"),edge(2,3),edge(2,1)}) {
    const auto epoch=runtime.apply({++sequence,TableId{0},SetOperation::insert,row}); database.tables[0].insert(row); verify(runtime,database,adapter);
    if (row==edge(1,2)) check(epoch.input.metrics.aliases_filtered==1 && epoch.input.derivations.size()==1,"different filters not preserved per alias");
  }
  auto bounded=options(); bounded.derivation_limit=1; PhysicalRuntime limited(plan,bounded);
  static_cast<void>(limited.apply({1,TableId{0},SetOperation::insert,edge(1,2)})); const auto before=image(limited);
  error([&] { static_cast<void>(limited.apply({2,TableId{0},SetOperation::insert,edge(1,1)})); },"derivation_overflow");
  check(limited.ready() && image(limited)==before && limited.derivation_count(OccurrenceId{0},{n(1)})==0,"later alias overflow left earlier alias or source row");
  static_cast<void>(limited.apply({2,TableId{0},SetOperation::erase,edge(1,2)}));
  static_cast<void>(limited.apply({3,TableId{0},SetOperation::insert,edge(1,1)})); limited.check_invariants();
}
void raw_guards_and_nullary_derivations() {
  const Catalog catalog{1,{{"edge",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"payload",ScalarType::string}}}}};
  const Query guarded{{{"x",ScalarType::int64}},{{"diagonal",TableId{0},{VariableId{0},VariableId{0},Value{std::string("ok")}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"diagonal",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  PhysicalRuntime runtime(s04_runtime::lower_tree(catalog,guarded,tree)); Database database; database.tables.resize(1); std::uint64_t sequence=0;
  for (const auto& row : {edge(1,2,"ok"),edge(1,1,"no"),edge(1,1,"ok")}) {
    const auto epoch=runtime.apply({++sequence,TableId{0},SetOperation::insert,row}); database.tables[0].insert(row); verify(runtime,database);
    check(epoch.input.metrics.aliases_filtered==(row==edge(1,1,"ok")?0U:1U),"constant/repeated-variable filter differs");
  }
  const Query nullary{{},{{"any",TableId{0},{IgnoredColumn{},IgnoredColumn{},IgnoredColumn{}}}},{},false};
  const FreeConnexTree empty_scope{NodeId{0},{{"any",NodeKind::native,{},{},0,{}}},{},{}};
  PhysicalRuntime boolean(s04_runtime::lower_tree(catalog,nullary,empty_scope)); Database physical; physical.tables.resize(1);
  static_cast<void>(boolean.apply({1,TableId{0},SetOperation::insert,edge(1,2)})); physical.tables[0].insert(edge(1,2)); verify(boolean,physical);
  const auto repeated=boolean.apply({2,TableId{0},SetOperation::insert,edge(2,3)}); physical.tables[0].insert(edge(2,3)); verify(boolean,physical);
  check(!repeated.support.native_changed && boolean.derivation_count(OccurrenceId{0},{})==2 && boolean.snapshot().support.nodes[0].visible_keys->front().support.value==1,"nullary physical derivations confused with local P/E support");
  static_cast<void>(boolean.apply({3,TableId{0},SetOperation::erase,edge(1,2)})); physical.tables[0].erase(edge(1,2)); verify(boolean,physical);
  static_cast<void>(boolean.apply({4,TableId{0},SetOperation::erase,edge(2,3)})); physical.tables[0].clear(); verify(boolean,physical);
}
void constraints_and_unrouted_tables() {
  Catalog catalog{4,{{"r",{{"x",ScalarType::int64},{"ref",ScalarType::int64}}},
      {"target",{{"id",ScalarType::int64}}},{"unused",{{"tag",ScalarType::string}}}}};
  catalog.tables[1].constraints={UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced}};
  catalog.tables[0].constraints={ForeignKeyConstraint{"fk",{ColumnId{1}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  PhysicalRuntime runtime(s04_runtime::lower_tree(catalog,query,tree)); const auto empty=image(runtime);
  error([&] { static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{n(7),n(1)}})); },"constraint_violation");
  check(image(runtime)==empty,"FK rejection changed empty state");
  const auto target=runtime.apply({1,TableId{1},SetOperation::insert,{n(1)}});
  check(target.input.physical_changed && target.input.derivations.empty() && !target.support.native_changed,"unused FK target became native input");
  static_cast<void>(runtime.apply({2,TableId{0},SetOperation::insert,{n(7),n(1)}})); const auto before=image(runtime);
  error([&] { static_cast<void>(runtime.apply({3,TableId{1},SetOperation::erase,{n(1)}})); },"constraint_violation");
  check(image(runtime)==before,"referenced target deletion partially committed");
  static_cast<void>(runtime.apply({3,TableId{2},SetOperation::insert,{Value{std::string("unrouted")}}})); runtime.check_invariants();
  Catalog self{5,{{"r",{{"id",ScalarType::int64},{"parent",ScalarType::int64}}}}};
  self.tables[0].constraints={UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"self",{ColumnId{1}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced}};
  PhysicalRuntime recursive(s04_runtime::lower_tree(self,query,tree));
  static_cast<void>(recursive.apply({1,TableId{0},SetOperation::insert,{n(1),n(1)}}));
  static_cast<void>(recursive.apply({2,TableId{0},SetOperation::insert,{n(2),n(1)}})); const auto saved=image(recursive);
  error([&] { static_cast<void>(recursive.apply({3,TableId{0},SetOperation::erase,{n(1),n(1)}})); },"constraint_violation");
  error([&] { static_cast<void>(recursive.apply({3,TableId{0},SetOperation::insert,{n(2),n(2)}})); },"constraint_violation");
  check(image(recursive)==saved,"unique/self-FK failure changed state"); recursive.check_invariants();
  catalog.tables[0].constraints={UniqueConstraint{"hint",{ColumnId{0}},ConstraintStatus::untrusted}};
  PhysicalRuntime untrusted(s04_runtime::lower_tree(catalog,query,tree));
  static_cast<void>(untrusted.apply({1,TableId{0},SetOperation::insert,{n(7),n(1)}}));
  const auto second=untrusted.apply({2,TableId{0},SetOperation::insert,{n(7),n(2)}});
  check(!second.support.native_changed && untrusted.derivation_count(OccurrenceId{0},{n(7)})==2,"untrusted unique hint enforced"); untrusted.check_invariants();
}
void constants_and_resource_caps() {
  const Catalog catalog{1,{{"unused",{{"id",ScalarType::int64}}}}};
  for (const bool contradiction : {false,true}) {
    const Query query{{},{},{},contradiction}; PhysicalRuntime runtime(s04_runtime::lower_tree(catalog,query,FreeConnexTree{}));
    Database database; database.tables.resize(1); verify(runtime,database);
    static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{n(1)}})); database.tables[0].insert({n(1)}); verify(runtime,database);
    check(runtime.source_layout(TableId{0}).origin()->table==TableId{0},"private constant-route source layout origin");
  }
  PhysicalRuntime probe(loop_plan(),options()); const auto work=probe.apply({1,TableId{0},SetOperation::insert,edge(1,1)}).input.metrics.work;
  auto bounded=options(); bounded.work_limit=work-1; PhysicalRuntime limited(loop_plan(),bounded); const auto before=image(limited);
  error([&] { static_cast<void>(limited.apply({1,TableId{0},SetOperation::insert,edge(1,1)})); },"resource_limit");
  check(limited.ready() && image(limited)==before,"aggregate coordinator budget failed to roll back");
  static_cast<void>(limited.apply({1,TableId{0},SetOperation::erase,edge(9,9)})); limited.check_invariants();
  auto support_options=options(); support_options.support.support_limit=1;
  PhysicalRuntime support(loop_plan(true),support_options);
  static_cast<void>(support.apply({1,TableId{0},SetOperation::insert,edge(1,1)})); const auto saved=image(support);
  error([&] { static_cast<void>(support.apply({2,TableId{0},SetOperation::insert,edge(2,2)})); },"support_overflow");
  check(support.ready() && image(support)==saved,"later logical support failure left a physical alias partially committed"); support.check_invariants();
}
}  // namespace
int main() {
  static_assert(std::is_nothrow_move_constructible_v<PhysicalEpoch>);
  static_assert(std::is_nothrow_move_constructible_v<PhysicalRuntime::PendingUpdate>);
  static_assert(std::is_nothrow_move_assignable_v<PhysicalRuntime::PendingUpdate>);
  try {
    generated_aliases(); publication_and_derivations(); active_facade_moves(); sql_filters_and_later_alias_failure(); raw_guards_and_nullary_derivations();
    constraints_and_unrouted_tables(); constants_and_resource_caps();
    std::cout<<verified<<" independently recomputed physical epochs PASS\n";
  } catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n'; return 1; }
}

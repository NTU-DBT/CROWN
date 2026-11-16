#pragma once

#include "weighted_fixture.hpp"

// W03 test reference: enumerate native assignment joins, independently of
// incremental local products, child caches and projection replacement.
namespace crown::weighted_test {

// Both nodes are in C*: hidden u and z must be summed locally, while S's
// weight must not also enter R's factor. Optional hidden T is outside C*.
inline PhysicalPlan counted_path(bool indexed, bool hidden_tail=false, bool repeated_head=false) {
  Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"u",ScalarType::int64}}},
      {"s",{{"y",ScalarType::int64},{"z",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},{"u",ScalarType::int64},{"z",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2}}},
       {"s",TableId{1},{VariableId{1},VariableId{3}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  FreeConnexTree tree{NodeId{0},{
      {"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1},VariableId{3}},{},1,{}}},{},{}};
  if (hidden_tail) {
    catalog.tables.push_back({"t",{{"z",ScalarType::int64}}});
    query.atoms.push_back({"t",TableId{2},{VariableId{3}}});
    tree.nodes[1].children.push_back(NodeId{2});
    tree.nodes.push_back({"t",NodeKind::native,{VariableId{3}},{},2,{}});
  }
  if (repeated_head) query.head={{VariableId{1},"y"},{VariableId{0},"x"},{VariableId{1},"again"}};
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

inline PhysicalPlan typed_bag(bool indexed) {
  const Catalog catalog{1,{{"r",{{"name",ScalarType::string},{"y",ScalarType::int64},{"day",ScalarType::date}}},
      {"s",{{"y",ScalarType::int64},{"flag",ScalarType::boolean}}}}};
  const Query query{{{"name",ScalarType::string},{"y",ScalarType::int64},{"day",ScalarType::date},{"flag",ScalarType::boolean}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2}}},
       {"s",TableId{1},{VariableId{1},VariableId{3}}}},
      {{VariableId{3},"flag"},{VariableId{0},"name"},{VariableId{2},"day"},{VariableId{0},"again"},
       {VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1},VariableId{3}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

inline void typed_inputs(Model& model, std::size_t rows=3) {
  for (std::size_t i=0;i<rows;++i) model.set(0,{Value{std::string(256,'x')+std::to_string(i)},n(7),
      Value{Date::parse("2026-11-11")}},static_cast<std::uint64_t>(i+2));
  model.set(1,{n(7),Value{false}},3);model.set(1,{n(7),Value{true}},5);
}

inline PhysicalPlan disconnected_bag(bool indexed, std::optional<std::uint64_t> structural_limit={}) {
  const Catalog catalog{1,{{"a",{{"x",ScalarType::int64}}},{"b",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"a",TableId{0},{VariableId{0}}},{"b",TableId{1},{VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"unit",NodeKind::generalized,{}, {NodeId{1},NodeId{2}},{},{}},
      {"a",NodeKind::native,{VariableId{0}},{},0,{}},
      {"b",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  auto configured=options(indexed);
  if (structural_limit) configured.indexed_storage->per_operation.structural_steps=*structural_limit;
  return planner::lower_tree(catalog,query,tree,configured);
}

inline PhysicalPlan deep_bag(std::size_t length, bool hidden, bool indexed) {
  Catalog catalog;Query query;FreeConnexTree tree;tree.root=NodeId{0};
  query.variables={{"x",ScalarType::int64}};
  if (hidden) query.variables.push_back({"y",ScalarType::int64});
  query.head={{VariableId{0},"x"}};
  for (std::size_t i=0;i<length;++i) {
    const auto name="d"+std::to_string(i);
    const auto scope=hidden?(i?VariableSet{VariableId{1}}:VariableSet{VariableId{0},VariableId{1}}):
        VariableSet{VariableId{0}};
    Table table;table.name=name;std::vector<Term> terms;
    for (const auto variable:scope) {
      table.columns.push_back({query.variables[variable.value].name,ScalarType::int64});
      terms.emplace_back(std::in_place_type<VariableId>,variable);
    }
    catalog.tables.push_back(std::move(table));query.atoms.push_back({name,TableId{i},std::move(terms)});
    tree.nodes.push_back({name,NodeKind::native,scope,{},i,{}});
    if (i) tree.nodes[i-1].children.push_back(NodeId{i});
  }
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

inline Assignments native_assignments(const CompiledProgram& plan, const Inputs& inputs,
    const std::vector<NodeId>& nodes, Assignment fixed={}) {
  Assignments result{{std::move(fixed),1}};
  for (const auto node:nodes) {
    if (plan.nodes()[node.value].kind!=NodeKind::native) continue;
    Assignments rows;
    for (const auto& [row,weight]:inputs[node.value])
      rows.emplace(assignment(row,plan.nodes()[node.value].scope),weight);
    result=join(result,rows);
  }
  return result;
}
inline std::vector<NodeId> all_nodes(const CompiledProgram& plan) {
  std::vector<NodeId> result;
  for (const auto& node:plan.nodes()) result.push_back(node.id);
  return result;
}
inline Counts bag_oracle(const CompiledProgram& plan, const Inputs& inputs) {
  if (plan.route()==PhysicalRoute::constant_false) return {};
  if (plan.route()==PhysicalRoute::constant_true) return {{Row{},1}};
  Counts result;
  for (const auto& [value,weight]:native_assignments(plan,inputs,all_nodes(plan))) {
    Row row;
    for (const auto& output:plan.query().head) row.push_back(value.at(output.variable));
    result[row]=add(result[row],weight);
  }
  return result;
}

// Delete C* edges, then join each resulting component's actual native atoms.
// Seeding the visible assignment also handles a generalized unit-only component.
inline std::vector<NodeId> component(const CompiledProgram& plan, NodeId root) {
  std::vector<NodeId> result{root};
  for (std::size_t i=0;i<result.size();++i)
    for (const auto child:plan.nodes()[result[i].value].children)
      if (!plan.nodes()[child.value].connex) result.push_back(child);
  return result;
}
inline std::uint64_t component_count(const CompiledProgram& plan, const Inputs& inputs,
    const std::vector<NodeId>& nodes, Assignment fixed) {
  std::uint64_t count=0;
  for (const auto& [value,weight]:native_assignments(plan,inputs,nodes,std::move(fixed))) {
    static_cast<void>(value);count=add(count,weight);
  }
  return count;
}
inline void compare_factors(const w::Snapshot& actual, const Inputs& inputs) {
  const auto& plan=actual.shape;
  const auto full=recompute(plan,inputs);
  for (const auto& node:actual.nodes) {
    const auto& shape=plan.nodes()[node.node.value];
    Counts expected,observed;
    const auto atoms=component(plan,node.node);
    for (const auto& row:node.records) {
      const auto values=storage::export_row(row.tuple.values());
      const auto count=shape.connex && full.nodes[node.node.value].records.at(values).subtree ?
          component_count(plan,inputs,atoms,assignment(values,shape.scope)) : 0;
      check(row.value->factor.value==count,"cached local contribution differs from native component join");
      if (count) expected.emplace(project(assignment(values,shape.scope),shape.visible_scope),0);
    }
    for (auto& [key,count]:expected)
      count=component_count(plan,inputs,atoms,assignment(key,shape.visible_scope));
    for (const auto& row:node.factors)
      check(observed.emplace(storage::export_row(row.key.values()),row.value.value).second,"duplicate factor key");
    check(observed==expected,"visible factor differs from component assignment join");
  }
}
// Account assertions cover actual emitted tuples; ordinary exported maps remain separate.
inline Counts drain(runtime::WeightedRuntime::ResultCursor& cursor) {
  Counts result;
  while (auto record=cursor.next()) {
    check(record->tuple.layout().same_token(cursor.layout()),"weighted cursor output layout changed");
    check(record->tuple.is_accounted() && record->tuple.account_statistics().owner==cursor.owner(),
        "weighted cursor output escaped original account");
    check(record->multiplicity.present(),"weighted cursor emitted zero multiplicity");
    check(result.emplace(storage::export_row(record->tuple.values()),record->multiplicity.value).second,
        "weighted cursor emitted duplicate projected tuple");
  }
  check(cursor.state()==w::CursorState::exhausted && !cursor.active(),"weighted cursor did not exhaust");
  return result;
}
inline void compare_bag(runtime::WeightedRuntime& runtime, const Inputs& inputs) {
  const auto expected=bag_oracle(runtime.structural_program(),inputs);
  const auto snapshot=runtime.snapshot();compare_factors(snapshot,inputs);
  auto cursor=runtime.results();
  check(cursor.binding()==runtime.binding(),"cursor weighted binding differs");
  check(drain(cursor)==expected,"weighted cursor differs from exhaustive full native join");
  check(runtime.ready(),"exhaustion retained weighted reader lease");
  std::uint64_t count=0;
  for (const auto& [row,weight]:expected) {static_cast<void>(row);count=add(count,weight);}
  check(runtime.root_weight().value==count,"projected bag total differs from root witness count");
}
struct BagModel:Model {
  using Model::Model;
  w::Epoch set(std::size_t node, Row row, std::uint64_t weight) {
    auto result=Model::set(node,std::move(row),weight);
    compare_bag(runtime,inputs);return result;
  }
};
} // namespace crown::weighted_test

#pragma once

#include "crown/planner/lower.hpp"
#include "crown/runtime/weighted.hpp"
#include "indexed_runtime_fixture.hpp"
#include <algorithm>
#include <map>
#include <set>
#include <stdexcept>
#include <string>

// Test-only exhaustive join oracle for Refactor.md §10.2. It enumerates full
// descendant assignments, independently of incremental products/queue/storage.
// Ordinary fixtures use small weights; explicit overflow tests bypass this
// bounded uint64 oracle. The separate Python oracle uses unbounded integers.
namespace crown::weighted_test {
namespace w = runtime::weighted;
// Indexed by native NodeId, with ordinary deep-owned keys; not physical table IDs.
using Inputs = std::vector<std::map<Row,std::uint64_t>>;
using Assignment = std::map<VariableId,Value>;
using Assignments = std::map<Assignment,std::uint64_t>;
using Counts = std::map<Row,std::uint64_t>;

inline void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
inline Value n(std::int64_t value) { return value; }
inline PhysicalOptions options(bool indexed) {
  return indexed ? s04_runtime::options() : PhysicalOptions{};
}

// Hidden native variables force sum-over-witnesses before parent propagation.
inline PhysicalPlan path(bool indexed) {
  const Catalog catalog{1,{
      {"p",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},
      {"q",{{"y",ScalarType::int64},{"z",ScalarType::int64}}},
      {"r",{{"z",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}},
      {{"p",TableId{0},{VariableId{0},VariableId{1}}},
       {"q",TableId{1},{VariableId{1},VariableId{2}}},
       {"r",TableId{2},{VariableId{2}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"p",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"q",NodeKind::native,{VariableId{1},VariableId{2}},{NodeId{2}},1,{}},
      {"r",NodeKind::native,{VariableId{2}},{},2,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

// G(x,z) must sum its full-scope products to parent key x. Both child scopes
// strictly contain G's scope, so this also catches separator/full-row confusion.
inline PhysicalPlan generalized(bool indexed) {
  const Catalog catalog{1,{
      {"p",{{"x",ScalarType::int64}}},
      {"r",{{"x",ScalarType::int64},{"z",ScalarType::int64},{"r",ScalarType::int64}}},
      {"s",{{"x",ScalarType::int64},{"z",ScalarType::int64},{"s",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"z",ScalarType::int64},
      {"r",ScalarType::int64},{"s",ScalarType::int64}},
      {{"p",TableId{0},{VariableId{0}}},
       {"r",TableId{1},{VariableId{0},VariableId{1},VariableId{2}}},
       {"s",TableId{2},{VariableId{0},VariableId{1},VariableId{3}}}},
      {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"root",NodeKind::generalized,{VariableId{0}},{NodeId{1},NodeId{2}},{},{}},
      {"p",NodeKind::native,{VariableId{0}},{},0,{}},
      {"g",NodeKind::generalized,{VariableId{0},VariableId{1}},{NodeId{3},NodeId{4}},{},{}},
      {"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2}},{},1,{}},
      {"s",NodeKind::native,{VariableId{0},VariableId{1},VariableId{3}},{},2,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

// One R(y) update changes several Q(x,y,z) rows sharing parent key x. Their
// queued numeric totals must reach a newly created G(x) candidate in order.
inline PhysicalPlan fanout(bool indexed, std::optional<std::uint64_t> structural_limit={}) {
  const Catalog catalog{1,{
      {"q",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}}},
      {"r",{{"y",ScalarType::int64}}},{"b",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}},
      {{"q",TableId{0},{VariableId{0},VariableId{1},VariableId{2}}},
       {"r",TableId{1},{VariableId{1}}},{"b",TableId{2},{VariableId{0}}}},
      {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"g",NodeKind::generalized,{VariableId{0}},{NodeId{1},NodeId{3}},{},{}},
      {"q",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2}},{NodeId{2}},0,{}},
      {"r",NodeKind::native,{VariableId{1}},{},1,{}},
      {"b",NodeKind::native,{VariableId{0}},{},2,{}}},{},{}};
  auto configured=options(indexed);
  if (structural_limit) configured.indexed_storage->per_operation.structural_steps=*structural_limit;
  return planner::lower_tree(catalog,query,tree,configured);
}

inline PhysicalPlan unary(bool indexed, bool nullary=false, bool boolean=false) {
  const Catalog catalog{1,{{"r",nullary ? std::vector<Column>{} :
      std::vector<Column>{{"x",ScalarType::int64}}}}};
  const VariableSet scope=nullary ? VariableSet{} : VariableSet{VariableId{0}};
  Query query;
  if (!nullary) query.variables={{"x",ScalarType::int64}};
  query.atoms={{"r",TableId{0},nullary ? std::vector<Term>{} : std::vector<Term>{VariableId{0}}}};
  if (!nullary && !boolean) query.head={{VariableId{0},"x"}};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,scope,{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,options(indexed));
}

inline std::uint64_t add(std::uint64_t a, std::uint64_t b) {
  check(b<=UINT64_MAX-a,"test oracle sum overflow");return a+b;
}
inline std::uint64_t multiply(std::uint64_t a, std::uint64_t b) {
  check(!a || b<=UINT64_MAX/a,"test oracle product overflow");return a*b;
}
inline Assignment assignment(const Row& row, const auto& scope) {
  check(row.size()==scope.size(),"test oracle row width");
  Assignment result;std::size_t i=0;
  for (const auto variable:scope) result.emplace(variable,row[i++]);
  return result;
}
inline Row project(const Assignment& value, const auto& scope) {
  Row row;for (const auto variable:scope) row.push_back(value.at(variable));return row;
}

// Exhaustive natural join of complete assignments. This does not use runtime
// child caches, incremental messages, native indices or contribution replace.
inline Assignments join(const Assignments& a, const Assignments& b) {
  Assignments result;
  for (const auto& [left,wa]:a) for (const auto& [right,wb]:b) {
    auto combined=left;bool compatible=true;
    for (const auto& [variable,value]:right) {
      const auto [position,inserted]=combined.emplace(variable,value);
      if (!inserted && position->second!=value) {compatible=false;break;}
    }
    if (compatible) result[combined]=add(result[combined],multiply(wa,wb));
  }
  return result;
}
struct ExpectedRow {
  std::uint64_t local=0, subtree=0;
  std::vector<std::uint64_t> children;
  std::size_t supported=0;
  bool operator==(const ExpectedRow&) const=default;
};
struct ExpectedNode { std::map<Row,ExpectedRow> records;Counts messages; };
struct Expected { std::vector<ExpectedNode> nodes;std::uint64_t root=0; };

// Enumerate all subtree witness assignments, then project and sum. Candidate
// union is checked separately so rows with zero product remain observable.
inline Expected recompute(const CompiledProgram& plan, const Inputs& inputs) {
  Expected result;result.nodes.resize(plan.nodes().size());
  if (plan.route()!=PhysicalRoute::tree) {
    result.root=plan.route()==PhysicalRoute::constant_true ? 1 : 0;return result;
  }
  std::vector<NodeId> order{*plan.tree().root};
  for (std::size_t i=0;i<order.size();++i)
    for (const auto child:plan.nodes()[order[i].value].children) order.push_back(child);
  std::vector<Assignments> subtrees(order.size());
  for (auto position=order.rbegin();position!=order.rend();++position) {
    const auto id=position->value;const auto& shape=plan.nodes()[id];auto& expected=result.nodes[id];
    Assignments values;
    if (shape.kind==NodeKind::native) {
      for (const auto& [row,weight]:inputs[id]) values.emplace(assignment(row,shape.scope),weight);
    } else values.emplace(Assignment{},1);
    for (const auto child:shape.children) values=join(values,subtrees[child.value]);
    subtrees[id]=std::move(values);
    Counts full;
    for (const auto& [value,weight]:subtrees[id]) {
      const auto row=project(value,shape.scope);full[row]=add(full[row],weight);
      std::vector<VariableId> separator;
      if (shape.parent) for (const auto variable:shape.scope)
        if (std::ranges::find(plan.nodes()[shape.parent->value].scope,variable)!=
            plan.nodes()[shape.parent->value].scope.end()) separator.push_back(variable);
      const auto key=project(value,separator);
      expected.messages[key]=add(expected.messages[key],weight);
    }
    std::set<Row> candidates;
    if (shape.kind==NodeKind::native) for (const auto& [row,weight]:inputs[id]) {
      static_cast<void>(weight);candidates.insert(row);
    } else for (const auto child:shape.children)
      for (const auto& [key,weight]:result.nodes[child.value].messages) {
        static_cast<void>(weight);candidates.insert(key);
      }
    for (const auto& row:candidates) {
      auto& record=expected.records[row];record.local=shape.kind==NodeKind::native ? inputs[id].at(row) : 1;
      record.subtree=full[row];const auto values_by_id=assignment(row,shape.scope);
      for (const auto child:shape.children) {
        std::vector<VariableId> separator;
        for (const auto variable:plan.nodes()[child.value].scope)
          if (values_by_id.contains(variable)) separator.push_back(variable);
        const auto& child_messages=result.nodes[child.value].messages;
        const auto found=child_messages.find(project(values_by_id,separator));
        const auto weight=found==child_messages.end() ? 0 : found->second;
        record.children.push_back(weight);if (weight) ++record.supported;
      }
    }
  }
  const auto& root=result.nodes[plan.tree().root->value].messages;
  result.root=root.empty() ? 0 : root.at(Row{});return result;
}

inline void compare(const w::Snapshot& actual, const Expected& expected) {
  check(actual.root.value==expected.root,"root differs from exhaustive weighted join");
  check(actual.nodes.size()==expected.nodes.size(),"snapshot node count");
  for (const auto& node:actual.nodes) {
    std::map<Row,ExpectedRow> records;Counts messages;
    for (const auto& record:node.records) {
      ExpectedRow value{record.value->local.value,record.value->subtree.value,{},record.value->supported_children};
      for (const auto child:record.value->children) value.children.push_back(child.value);
      check(records.emplace(storage::export_row(record.tuple.values()),std::move(value)).second,"duplicate row");
    }
    for (const auto& message:node.messages)
      check(messages.emplace(storage::export_row(message.key.values()),message.value.value).second,"duplicate message");
    check(records==expected.nodes[node.node.value].records,"row/cached factors differ from exhaustive weighted join");
    check(messages==expected.nodes[node.node.value].messages,"separator messages differ from exhaustive weighted join");
  }
}

// Keep the model inputs separate from the runtime. Compare every row/message
// after every logical update, including updates that leave membership unchanged.
struct Model {
  runtime::WeightedRuntime runtime;
  Inputs inputs;
  explicit Model(PhysicalPlan plan, w::Options opts={})
      :runtime(std::move(plan),opts),inputs(runtime.structural_program().nodes().size()) {}
  // apply commits first; later ordinary-model/export failure has no joint rollback.
  w::Epoch set(std::size_t node, Row row, std::uint64_t weight) {
    auto& input=inputs.at(node);const auto found=input.find(row);
    const auto before=found==input.end() ? 0 : found->second;
    auto epoch=runtime.apply({runtime.sequence()+1,{NodeId{node},row,{before},{weight}}});
    if (weight) input[row]=weight;else input.erase(row);
    compare(runtime.snapshot(),recompute(runtime.structural_program(),inputs));return epoch;
  }
};
} // namespace crown::weighted_test

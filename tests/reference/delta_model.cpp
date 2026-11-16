#include "delta_model.hpp"

#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include <algorithm>
#include <iterator>
#include <set>
#include <utility>

namespace crown::reference::delta {
namespace {
using Assignment=FixedAssignment;
using Assignments=std::set<Assignment>;
void require(bool condition,std::string_view message) {
  if (!condition) throw Error("invalid_delta_model",std::string(message));
}
void transition_require(bool condition,std::string_view message) {
  if (!condition) throw Error("invalid_delta_transition",std::string(message));
}
std::vector<VariableId> intersection(const VariableSet& left,const VariableSet& right) {
  std::vector<VariableId> result;
  std::set_intersection(left.begin(),left.end(),right.begin(),right.end(),std::back_inserter(result));
  return result;
}
Assignment assignment(const Row& row,const std::vector<VariableId>& scope) {
  require(row.size()==scope.size(),"factor row width differs from its scope"); Assignment result;
  for (std::size_t i=0;i<scope.size();++i) require(result.emplace(scope[i],row[i]).second,"factor scope repeats a variable");
  return result;
}
Row project(const Assignment& row,const std::vector<VariableId>& scope) {
  Row result; result.reserve(scope.size());
  for (const auto variable : scope) { const auto found=row.find(variable); require(found!=row.end(),"projection has an unbound variable"); result.push_back(found->second); }
  return result;
}
Assignments join(const Assignments& left,const Assignments& right) {
  Assignments result;
  for (const auto& a : left) for (const auto& b : right) {
    auto combined=a; bool compatible=true;
    for (const auto& [variable,value] : b) {
      const auto [found,inserted]=combined.emplace(variable,value);
      if (!inserted && found->second!=value) { compatible=false; break; }
    }
    if (compatible) result.insert(std::move(combined));
  }
  return result;
}
bool compatible(const Row& a,const Factor& left,const Row& b,const Factor& right) {
  const auto values=assignment(a,left.scope);
  for (std::size_t i=0;i<right.scope.size();++i) {
    const auto found=values.find(right.scope[i]); if (found!=values.end() && found->second!=b[i]) return false;
  }
  return true;
}
void validate_snapshot(const Snapshot& snapshot) {
  if (snapshot.factors.empty()) { require(!snapshot.constant_answer || snapshot.head.empty(),"true constant has a nonempty head"); return; }
  const VariableSet head(snapshot.head.begin(),snapshot.head.end());
  std::set<NodeId> nodes; std::map<VariableId,std::size_t> occurrences,edges;
  std::map<VariableId,ScalarType> types;
  for (std::size_t i=0;i<snapshot.factors.size();++i) {
    const auto& factor=snapshot.factors[i];
    require(nodes.insert(factor.node).second,"factor node is repeated");
    require(i==0?!factor.parent:(factor.parent && *factor.parent<i),"factors do not form one parent-before-child tree");
    require(std::is_sorted(factor.scope.begin(),factor.scope.end()) &&
        std::adjacent_find(factor.scope.begin(),factor.scope.end())==factor.scope.end(),"factor scope is not a sorted set");
    for (const auto variable : factor.scope) {
      require(head.contains(variable),"visible factor contains a hidden variable"); ++occurrences[variable];
      if (factor.parent) {
        const auto& parent=snapshot.factors[*factor.parent];
        if (std::binary_search(parent.scope.begin(),parent.scope.end(),variable)) ++edges[variable];
      }
    }
    for (const auto& row : factor.rows) {
      require(row.size()==factor.scope.size(),"factor row width differs from its scope");
      for (std::size_t field=0;field<row.size();++field) {
        const auto [found,inserted]=types.emplace(factor.scope[field],type_of(row[field]));
        require(inserted || found->second==type_of(row[field]),"factor variable has inconsistent exact scalar types");
      }
    }
  }
  for (const auto variable : head) {
    require(occurrences.contains(variable),"visible factors do not cover the head");
    require(edges[variable]+1==occurrences[variable],"visible factor scopes violate running intersection");
  }
}
}  // namespace

Snapshot recompute(const Catalog& catalog,const Query& query,const FreeConnexTree& tree,const std::vector<Relation>& native_rows) {
  const auto checked=planner::validate_tree(catalog,query,tree);
  require(checked.valid,"native model requires a verified free-connex tree");
  require(native_rows.size()==tree.nodes.size(),"native inputs differ from the tree size");
  Snapshot result;
  for (const auto& field : query.head) result.head.push_back(field.variable);
  if (query.contradiction) return result;
  if (query.atoms.empty()) { result.constant_answer=true; return result; }
  require(tree.root.has_value(),"nonconstant native model has no root");
  std::vector<NodeId> order{*tree.root}; std::vector<std::optional<NodeId>> parents(tree.nodes.size());
  for (std::size_t i=0;i<order.size();++i) for (const auto child : tree.nodes[order[i].value].children) {
    parents[child.value]=order[i]; order.push_back(child);
  }
  // Deliberately full subtree assignments: no maintained survivor/support
  // counters, journal records or production cursor implementation is reused.
  std::vector<Assignments> subtrees(tree.nodes.size());
  for (auto it=order.rbegin();it!=order.rend();++it) {
    const auto id=*it; const auto& node=tree.nodes[id.value]; Assignments values;
    const std::vector<VariableId> scope(node.scope.begin(),node.scope.end());
    if (node.kind==NodeKind::native) {
      for (const auto& row : native_rows[id.value]) {
        auto tuple=assignment(row,scope);
        for (const auto& [variable,value] : tuple)
          require(type_of(value)==query.variables[variable.value].type,"native row has the wrong exact scalar type");
        values.insert(std::move(tuple));
      }
    } else { require(native_rows[id.value].empty(),"generalized node has external native rows"); values.insert(Assignment{}); }
    for (const auto child : node.children) values=join(values,subtrees[child.value]);
    subtrees[id.value]=std::move(values);
  }
  const VariableSet head(result.head.begin(),result.head.end());
  std::vector<bool> connex(tree.nodes.size()); connex[tree.root->value]=true;
  std::map<NodeId,std::size_t> positions;
  for (const auto id : order) {
    const auto& node=tree.nodes[id.value];
    if (parents[id.value]) {
      const auto separator=intersection(node.scope,tree.nodes[parents[id.value]->value].scope);
      connex[id.value]=connex[parents[id.value]->value] && std::all_of(separator.begin(),separator.end(),[&](VariableId variable) { return head.contains(variable); });
    }
    if (!connex[id.value]) continue;
    Factor factor; factor.node=id; factor.scope=intersection(node.scope,head);
    if (parents[id.value]) factor.parent=positions.at(*parents[id.value]);
    for (const auto& tuple : subtrees[id.value]) factor.rows.insert(project(tuple,factor.scope));
    positions.emplace(id,result.factors.size()); result.factors.push_back(std::move(factor));
  }
  validate_snapshot(result); return result;
}

std::vector<Row> enumerate(const Snapshot& snapshot,const FixedAssignment& fixed) {
  validate_snapshot(snapshot);
  const VariableSet head(snapshot.head.begin(),snapshot.head.end());
  for (const auto& [variable,value] : fixed) { static_cast<void>(value); require(head.contains(variable),"E witness binding is outside the visible head"); }
  if (snapshot.factors.empty()) return snapshot.constant_answer?std::vector<Row>{Row{}}:std::vector<Row>{};
  Assignments values{fixed};
  for (const auto& factor : snapshot.factors) {
    Assignments local;
    for (const auto& row : factor.rows) local.insert(assignment(row,factor.scope));
    values=join(values,local);
  }
  std::vector<Row> result;
  for (const auto& tuple : values) result.push_back(project(tuple,snapshot.head));
  return result;
}

std::vector<Relation> bootstrap_live(const Snapshot& snapshot) {
  validate_snapshot(snapshot); std::vector<Relation> result(snapshot.factors.size());
  for (std::size_t i=0;i<snapshot.factors.size();++i) {
    const auto& child=snapshot.factors[i];
    if (!child.parent) { result[i]=child.rows; continue; }
    const auto& parent=snapshot.factors[*child.parent];
    // This precondition follows from the drained S/P/E invariant. An
    // arbitrary collection of joins lacks it and cannot use this bootstrap.
    for (const auto& row : parent.rows)
      require(std::any_of(child.rows.begin(),child.rows.end(),[&](const Row& value) { return compatible(row,parent,value,child); }),
          "E factor is not downward total on a child separator");
    for (const auto& row : child.rows)
      if (std::any_of(result[*child.parent].begin(),result[*child.parent].end(),[&](const Row& value) { return compatible(value,parent,row,child); })) result[i].insert(row);
  }
  return result;
}

Transition partition(const Snapshot& before,const Snapshot& after,SetOperation operation) {
  transition_require(operation==SetOperation::insert || operation==SetOperation::erase,"unknown delta polarity");
  validate_snapshot(before); validate_snapshot(after);
  transition_require(before.head==after.head && before.factors.size()==after.factors.size() && before.constant_answer==after.constant_answer,
      "delta snapshots have incompatible query/route schemas");
  Transition result{operation,{}, {},{}, {},{}, {}}; result.changed.resize(before.factors.size());
  const bool insertion=operation==SetOperation::insert;
  for (std::size_t i=0;i<before.factors.size();++i) {
    const auto& old=before.factors[i]; const auto& now=after.factors[i];
    transition_require(old.node==now.node && old.parent==now.parent && old.scope==now.scope,"delta factor schemas differ");
    const auto& smaller=insertion?old.rows:now.rows; const auto& larger=insertion?now.rows:old.rows;
    for (const auto& row : smaller) transition_require(larger.contains(row),"delta factor memberships are not monotone in the declared direction");
    for (const auto& row : larger) if (!smaller.contains(row)) result.changed[i].insert(row);
    result.metrics.changed_keys+=static_cast<std::uint64_t>(result.changed[i].size());
  }
  result.before_live=bootstrap_live(before); result.after_live=bootstrap_live(after);
  const auto& context=insertion?after:before; const auto& live=insertion?result.after_live:result.before_live;
  for (std::size_t i=0;i<result.changed.size();++i) for (const auto& witness : result.changed[i]) {
    if (!live[i].contains(witness)) { ++result.metrics.dead_witnesses; continue; }
    ++result.metrics.live_witnesses;
    Fragment fragment; fragment.factor=i; fragment.witness=witness;
    fragment.candidates=enumerate(context,assignment(witness,context.factors[i].scope));
    require(!fragment.candidates.empty(),"live E witness has no whole-query completion");
    for (const auto& row : fragment.candidates) {
      ++result.metrics.candidates; Assignment values;
      for (std::size_t field=0;field<context.head.size();++field) {
        const auto [found,inserted]=values.emplace(context.head[field],row[field]);
        require(inserted || found->second==row[field],"repeated head fields disagree");
      }
      bool earliest=true;
      for (std::size_t earlier=0;earlier<i;++earlier) {
        ++result.metrics.earlier_probes;
        if (result.changed[earlier].contains(project(values,context.factors[earlier].scope))) { earliest=false; break; }
      }
      if (earliest) { fragment.accepted.push_back(row); result.rows.push_back(row); ++result.metrics.accepted; }
      else { fragment.rejected.push_back(row); ++result.metrics.rejected; }
    }
    result.fragments.push_back(std::move(fragment));
  }
  return result;
}
}  // namespace crown::reference::delta

#include "crown/planner/lower.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/tree.hpp"
#include "crown/storage/physical.hpp"
#include "crown/api/error.hpp"
#include "evaluator.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stdexcept>

namespace {
using namespace crown;
using Assignment=std::map<VariableId,Value>;
using Assignments=std::set<Assignment>;
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
std::string read(const std::filesystem::path& path) {
  std::ifstream stream(path); check(bool(stream),"cannot open fixture: "+path.string());
  return {std::istreambuf_iterator<char>{stream},std::istreambuf_iterator<char>{}};
}
std::vector<std::string> names(const Query& query,const std::vector<VariableId>& variables) {
  std::vector<std::string> result;
  for (const auto variable : variables) result.push_back(query.variables[variable.value].name);
  std::sort(result.begin(),result.end()); return result;
}
std::vector<VariableId> fields(const storage::TupleLayout& layout) {
  std::vector<VariableId> result;
  for (const auto& field : layout.fields()) { check(field.variable.has_value(),"logical field lacks a variable"); result.push_back(*field.variable); }
  return result;
}
Relation rows(const storage::ReferenceTable& table) {
  Relation result; for (const auto& tuple : table.snapshot()) result.insert(crown::storage::export_row(tuple.values())); return result;
}
Assignments atom_assignments(const Catalog& catalog,const Atom& atom,const Database& database) {
  Assignments result;
  for (const auto& row : database.tables.at(atom.table.value)) {
    validate_row(catalog,atom.table,row); Assignment assignment; bool matches=true;
    for (std::size_t i=0;i<atom.terms.size();++i) {
      if (const auto* variable=std::get_if<VariableId>(&atom.terms[i])) {
        const auto [entry,inserted]=assignment.emplace(*variable,row[i]);
        if (!inserted && entry->second!=row[i]) matches=false;
      } else if (const auto* value=std::get_if<Value>(&atom.terms[i]); value && *value!=row[i]) matches=false;
    }
    if (matches) result.insert(std::move(assignment));
  }
  return result;
}
Assignments join(const Assignments& left,const Assignments& right) {
  Assignments result;
  for (const auto& a : left) for (const auto& b : right) {
    auto combined=a; bool matches=true;
    for (const auto& [variable,value] : b) {
      const auto [entry,inserted]=combined.emplace(variable,value);
      if (!inserted && entry->second!=value) { matches=false; break; }
    }
    if (matches) result.insert(std::move(combined));
  }
  return result;
}
Relation project(const Assignments& assignments,const std::vector<VariableId>& variables) {
  Relation result;
  for (const auto& assignment : assignments) {
    Row row; for (const auto variable : variables) row.push_back(assignment.at(variable)); result.insert(std::move(row));
  }
  return result;
}
Value sample(ScalarType type,std::size_t number) {
  switch (type) {
    case ScalarType::int64: return static_cast<std::int64_t>(number+1);
    case ScalarType::string: return std::string(number==0 ? "a" : "b");
    case ScalarType::boolean: return number!=0;
    case ScalarType::date: return Date::parse(number==0 ? "2000-02-29" : "2024-02-29");
    case ScalarType::decimal: return Decimal::parse("0"); // Exact in every fixed P/S domain.
  }
  throw std::runtime_error("unknown sample type");
}
Database data_for(const Catalog& catalog,const Query& query,std::size_t variation) {
  Database database; database.tables.resize(catalog.tables.size());
  if (variation==0) return database;
  for (std::size_t t=0;t<catalog.tables.size();++t) for (std::size_t n=0;n<2;++n) {
    if (variation==2 && t==0 && n==0) continue;
    Row row; for (const auto& column : catalog.tables[t].columns) row.push_back(sample(column.type,n));
    database.tables[t].insert(std::move(row));
  }
  // Constants and ignored physical fields use the direct CQ's raw row
  // semantics, independently of compiled input programs.
  for (const auto& atom : query.atoms) {
    Row row; for (const auto& column : catalog.tables[atom.table.value].columns) row.push_back(sample(column.type,0));
    for (std::size_t i=0;i<atom.terms.size();++i) if (const auto* value=std::get_if<Value>(&atom.terms[i])) row[i]=*value;
    if (variation==1) database.tables[atom.table.value].insert(std::move(row));
  }
  return database;
}

// Test-only static interpreter of the emitted numeric program. Expected
// survivors below come from full subtree assignment joins, not this algorithm.
Relation execute(const PhysicalPlan& plan,const Database& database) {
  storage::ReferencePlanStorage state(plan);
  if (plan.route()==PhysicalRoute::constant_false) return {};
  if (plan.route()==PhysicalRoute::constant_true) return {crown::storage::export_row(plan.assemble_result({}).values())};
  const auto& query=plan.query(); const auto& tree=plan.tree();
  for (const auto& relation : plan.relations()) if (relation.role==RelationRole::physical_base)
    for (const auto& row : database.tables[relation.base->value]) static_cast<void>(state.table(relation.id).insert(relation.layout.tuple(row)));
  for (const auto& input : plan.inputs()) {
    for (const auto& row : database.tables[input.base.value]) if (auto tuple=plan.adapt_input(input.occurrence,row))
      static_cast<void>(state.table(plan.nodes()[input.node.value].records).insert(*tuple));
    const auto expected=atom_assignments(plan.catalog(),query.atoms[input.occurrence.value],database);
    check(rows(state.table(plan.nodes()[input.node.value].records))==project(expected,plan.nodes()[input.node.value].scope),"compiled input differs from raw CQ term evaluation");
  }
  std::vector<NodeId> order{*tree.root};
  for (std::size_t i=0;i<order.size();++i) for (const auto child : tree.nodes[order[i].value].children) order.push_back(child);
  std::vector<Assignments> expected(tree.nodes.size());
  for (auto position=order.rbegin();position!=order.rend();++position) {
    const auto id=*position; const auto& node=plan.nodes()[id.value];
    auto assignments=node.occurrence ? atom_assignments(plan.catalog(),query.atoms[node.occurrence->value],database) : Assignments{Assignment{}};
    for (const auto child : node.children) assignments=join(assignments,expected[child.value]);
    expected[id.value]=std::move(assignments);
    if (node.kind==NodeKind::generalized) for (const auto child : node.children)
      for (const auto& key : state.table(plan.nodes()[child.value].parent_support).snapshot()) static_cast<void>(state.table(node.records).insert(key));
    for (const auto& tuple : state.table(node.records).snapshot()) {
      bool survives=true;
      for (const auto child : node.children) {
        const auto edge=std::find_if(plan.edges().begin(),plan.edges().end(),[&](const PhysicalEdge& e) { return e.parent==id && e.child==child; });
        check(edge!=plan.edges().end(),"missing compiled child event route");
        const auto key=edge->parent_key.apply(tuple);
        if (!state.table(plan.nodes()[child.value].parent_support).find(key)) { survives=false; break; }
        if (edge->reverse_index) {
          const auto bucket=state.table(node.records).bucket(state.index(*edge->reverse_index),key);
          check(!bucket.empty(),"reverse separator lookup missed its own native record");
        }
      }
      if (survives) static_cast<void>(state.table(node.survivors).insert(tuple));
    }
    for (const auto& tuple : state.table(node.survivors).snapshot()) {
      static_cast<void>(state.table(node.parent_support).insert(node.parent_key.apply(tuple)));
      if (node.visible_projection) static_cast<void>(state.table(*node.visible_relation).insert(node.visible_projection->apply(tuple)));
    }
    check(rows(state.table(node.survivors))==project(expected[id.value],node.scope),"compiled survivor program differs from independent subtree joins");
    check(rows(state.table(node.parent_support))==project(expected[id.value],fields(node.parent_key.target())),"compiled parent projection differs from subtree projection");
    if (node.visible_relation) check(rows(state.table(*node.visible_relation))==project(expected[id.value],node.visible_scope),"compiled visible projection lost hidden-witness deduplication");
  }
  state.check_invariants();
  Relation result; std::vector<storage::Tuple> selected; std::size_t emitted=0;
  std::function<void(std::size_t)> walk=[&](std::size_t position) {
    if (position==plan.enumeration().steps.size()) {
      ++emitted; result.insert(crown::storage::export_row(plan.assemble_result(selected).values())); return;
    }
    const auto& step=plan.enumeration().steps[position]; const auto& table=state.table(step.relation);
    std::vector<storage::Tuple> choices;
    if (!step.parent_step) choices=table.snapshot();
    else {
      const auto key=step.parent_key->apply(selected[*step.parent_step]);
      auto cursor=table.bucket_cursor(state.index(*step.bucket_index),key);
      while (const auto handle=cursor.next()) choices.push_back(*table.get(*handle));
    }
    for (const auto& choice : choices) { selected.push_back(choice); walk(position+1); selected.pop_back(); }
  };
  walk(0); check(emitted==result.size(),"compiled visible enumeration emitted a projected result twice");
  std::vector<VariableId> head; for (const auto& output : query.head) head.push_back(output.variable);
  check(result==project(expected[tree.root->value],head),"compiled enumeration differs from full subtree joins");
  return result;
}

void fixtures(const std::filesystem::path& root) {
  const auto manifest=io::Json::parse(read(root/"tests/structural/lowering/manifest.json"));
  std::size_t valid=0,invalid=0;
  for (const auto& fixture : manifest.at("cases")) {
    const auto name=fixture.at("id").get<std::string>();
    const auto document=io::read_document(read(root/fixture.at("query").get<std::string>()));
    const auto tree=io::read_tree(read(root/fixture.at("tree").get<std::string>()),document.catalog,document.query);
    const auto& expected=fixture.at("expected");
    if (!expected.at("valid").get<bool>()) {
      bool rejected=false;
      try { static_cast<void>(planner::lower_tree(document.catalog,document.query,tree)); }
      catch (const Error& error) { check(error.code()=="invalid_plan",name+": wrong rejection: "+error.code()); rejected=true; }
      check(rejected,name+": invalid tree reached physical plan construction"); ++invalid; continue;
    }
    const auto plan=planner::lower_tree(document.catalog,document.query,tree); const auto artifact=io::write_physical(plan);
    check(artifact.at("route")==expected.at("route"),name+": route differs from manual expectation");
    check(plan.nodes().size()==expected.at("nodes").size(),name+": compiled node count differs");
    for (const auto& node : plan.nodes()) {
      const auto& label=tree.nodes[node.id.value].id; const auto& wanted=expected.at("nodes").at(label);
      check(names(document.query,node.scope)==wanted.at("scope").get<std::vector<std::string>>(),name+": scope mismatch");
      check(names(document.query,node.visible_scope)==wanted.at("visible").get<std::vector<std::string>>(),name+": visible scope mismatch");
      check(names(document.query,fields(node.parent_key.target()))==wanted.at("separator").get<std::vector<std::string>>(),name+": separator mismatch");
      check(node.connex==wanted.at("connex").get<bool>(),name+": C* mismatch");
      const auto parent=node.parent ? io::Json(tree.nodes[node.parent->value].id) : io::Json(nullptr);
      check(parent==wanted.at("parent"),name+": parent mismatch");
      std::vector<std::string> children; for (const auto child : node.children) children.push_back(tree.nodes[child.value].id);
      check(children==wanted.at("children").get<std::vector<std::string>>(),name+": child order mismatch");
      check(node.connex==node.visible_relation.has_value() && node.connex==node.visible_projection.has_value(),name+": hidden branch allocated an enumeration relation");
    }
    check(plan.enumeration().steps.size()==plan.validation().maximal_connex.size(),name+": enumeration is not exactly C*");
    const auto restored=io::read_physical(artifact.dump());
    check(io::write_physical(restored).dump()==artifact.dump(),name+": physical artifact does not replay exactly");
    for (std::size_t variation=0;variation<3;++variation) {
      const auto database=data_for(document.catalog,document.query,variation);
      reference::Session oracle(document.catalog,document.query,database);
      check(execute(plan,database)==oracle.snapshot(),name+": numeric program differs from independent A04 evaluator");
    }
    ++valid;
  }
  std::cout << valid << " manual lowering families and " << invalid << " invalid-tree boundaries passed\n";
}
void deep_program() {
  Catalog catalog; Query query; query.variables={{"x",ScalarType::int64}}; query.head={{VariableId{0},"x"}};
  FreeConnexTree tree; tree.root=NodeId{0}; constexpr std::size_t count=128;
  for (std::size_t i=0;i<count;++i) {
    const auto name="r"+std::to_string(i); catalog.tables.push_back({name,{{"x",ScalarType::int64}}});
    query.atoms.push_back({name,TableId{i},{VariableId{0}}});
    tree.nodes.push_back({name,NodeKind::native,{VariableId{0}},{},i,{}});
    if (i>0) tree.nodes[i-1].children.push_back(NodeId{i});
  }
  const auto plan=planner::lower_tree(catalog,query,tree);
  check(plan.validation().native_height==count && plan.validation().edge_depth==count-1 && plan.enumeration().depth==count,
        "native height, edge depth and enumeration program depth were conflated");
  storage::ReferencePlanStorage state(plan); state.check_invariants();
}
}  // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: crown_physical_lowering_test REPOSITORY");
    fixtures(argv[1]); deep_program();
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

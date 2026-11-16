#pragma once
#include "crown/ir/model.hpp"
#include <array>
#include <bit>
#include <optional>
#include <utility>
namespace crown::query_explain_fixture {
struct Fixture {
  std::string name;
  Catalog catalog;
  Query query;
  // Test expectation only, never an input to QueryExplanation authority.
  std::optional<bool> expected_admissible;
};
// Trusted small masks use only x0..x2 and head subset-of-union; this builds DTOs,
// while the separate public search/replay and literal oracle establish outcomes.
inline Fixture hypergraph(std::vector<unsigned> scopes,unsigned head_mask,std::string name,
    std::optional<bool> expected={}) {
  Fixture f{std::move(name),{}, {},expected};unsigned used=0;
  for(auto scope:scopes)used|=scope;
  std::array<std::size_t,3> variable{};
  for(unsigned v=0;v<3;++v)if((used&(1U<<v))!=0){variable[v]=f.query.variables.size();f.query.variables.push_back({"x"+std::to_string(v),ScalarType::int64});}
  for(auto scope:scopes){
    Table t;t.name="T"+std::to_string(f.catalog.tables.size());
    Atom a{"a"+std::to_string(f.query.atoms.size()),TableId{f.catalog.tables.size()}, {}};
    for(unsigned v=0;v<3;++v)if((scope&(1U<<v))!=0){t.columns.push_back({"x"+std::to_string(v),ScalarType::int64});a.terms.emplace_back(VariableId{variable[v]});}
    f.catalog.tables.push_back(std::move(t));f.query.atoms.push_back(std::move(a));
  }
  for(unsigned v=0;v<3;++v)if((head_mask&(1U<<v))!=0)f.query.head.push_back({VariableId{variable[v]},"out"+std::to_string(v)});
  return f;
}
inline std::vector<Fixture> anchors(){
  std::vector<Fixture> out;
  out.push_back(hypergraph({},0,"empty_body",true));
  out.push_back(hypergraph({0},0,"nullary_atom",true));
  out.push_back(hypergraph({1},1,"unary",true));
  out.push_back(hypergraph({3},1,"single_atom_projection",true));
  out.push_back(hypergraph({3,6},7,"path_full_head",true));
  out.push_back(hypergraph({3,6},5,"path_endpoint_projection_not_free_connex",false));
  out.push_back(hypergraph({1,2,4},7,"disconnected_product",true));
  out.push_back(hypergraph({3,6,5},7,"triangle",false));
  auto structural_negative=hypergraph({3,6,5},7,"contradiction_marked_triangle_structural_negative",false);structural_negative.query.contradiction=true;out.push_back(std::move(structural_negative));
  auto contradictory=hypergraph({},0,"empty_body_contradiction");contradictory.query.contradiction=true;out.push_back(std::move(contradictory));
  Fixture bytes{"raw_native_string_constant",{}, {},true};Table table;table.name="B";table.columns.push_back({"s",ScalarType::string});bytes.catalog.tables.push_back(std::move(table));
  Atom atom{"b",TableId{0},{}};atom.terms.emplace_back(Value{std::string(1,static_cast<char>(0xff))});bytes.query.atoms.push_back(std::move(atom));out.push_back(std::move(bytes));
  return out;
}
// Finite family: 1..3 distinct nonempty scopes from subsets of {x0,x1,x2},
// and every head subset of their union. No outcome is assumed for this family;
// compare with the separate literal reference::exhaustive_minimum_tree oracle.
inline std::vector<Fixture> finite_three_variable_family(){
  std::vector<Fixture> out;
  for(unsigned selected=1;selected<128;++selected){
    if(std::popcount(selected)>3)continue;
    std::vector<unsigned> scopes;unsigned used=0;
    for(unsigned scope=1;scope<8;++scope)if((selected&(1U<<(scope-1)))!=0){scopes.push_back(scope);used|=scope;}
    for(unsigned head=0;head<8;++head)if((head&~used)==0)
      out.push_back(hypergraph(scopes,head,"family_"+std::to_string(selected)+"_head_"+std::to_string(head)));
  }
  return out;
}
} // namespace crown::query_explain_fixture

#pragma once
#include "crown/runtime/owner_statistics.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/planner/lower.hpp"
#include <algorithm>
#include <map>
#include <stdexcept>
#include <source_location>
namespace owner_fixture {
using namespace crown;using namespace crown::runtime;
namespace stats=crown::runtime::statistics;
inline Value n(std::int64_t x){return x;}
inline void check(bool b,std::source_location at=std::source_location::current()){
  if(!b)throw std::runtime_error(std::string(at.file_name())+":"+std::to_string(at.line())+": owner statistics assertion");
}
inline PhysicalPlan plan(bool generalized=false){
  const Catalog catalog{1,{{"R",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"ignored",ScalarType::int64}}},
      {"S",{{"y",ScalarType::int64}}},{"unused",{{"u",ScalarType::int64}}}}};
  Query q{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"R",TableId{0},{VariableId{0},VariableId{1},IgnoredColumn{}}},{"S",TableId{1},{VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  if(generalized){q.head={{VariableId{1},"y"}};
    return planner::lower_tree(catalog,q,FreeConnexTree{NodeId{0},{{"g",NodeKind::generalized,{VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
      {"r",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},{"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}});}
  return planner::lower_tree(catalog,q,FreeConnexTree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}});
}
inline Database database(){return {{{{n(1),n(7),n(10)},{n(1),n(7),n(11)},{n(2),n(7),n(20)},{n(3),n(8),n(30)}},{{n(7)}},{{n(99)}}}};}
inline stats::OwnerRequest request(const PhysicalPlan& p){
  stats::OwnerRequest r{{
    {stats::SourceScope{TableId{0}},std::vector<FieldId>{FieldId{1}}},
    {stats::SourceScope{TableId{2}},{}},
    {stats::OccurrenceScope{OccurrenceId{0}},{}},
    {stats::NodeScope{NodeId{0},SupportRole::records},{}},
    {stats::NodeScope{NodeId{0},SupportRole::survivors},std::vector<FieldId>{FieldId{1}}},
    {stats::NodeScope{NodeId{0},SupportRole::parent_support},{}},
    {stats::NodeScope{NodeId{0},SupportRole::visible},{}}}};
  for(const auto& edge:p.edges())if(edge.reverse_index){r.selections.push_back({stats::IndexScope{*edge.reverse_index},{}});break;}
  return r;
}
using Counts=std::map<Row,std::uint64_t>;
inline void distribution(const stats::Component& component,const Counts& expected,std::uint64_t visited,std::size_t top_k=16){
  check(component.availability==stats::Availability::available && component.distribution.has_value());
  const auto& actual=*component.distribution;
  check(actual.completion==stats::Completion::exact && actual.ndv==expected.size() && actual.visited==visited);
  std::map<std::uint64_t,std::uint64_t> bins;
  std::vector<std::pair<Row,std::uint64_t>> ranked;
  for(const auto& [key,count]:expected){++bins[count];ranked.emplace_back(key,count);}
  check(actual.histogram==std::vector<std::pair<std::uint64_t,std::uint64_t>>(bins.begin(),bins.end()));
  std::sort(ranked.begin(),ranked.end(),[](const auto& a,const auto& b){return a.second!=b.second?a.second>b.second:a.first<b.first;});
  ranked.resize(std::min(top_k,ranked.size()));
  check(actual.heavy_keys.has_value() && actual.heavy_keys->size()==ranked.size());
  for(std::size_t i=0;i<ranked.size();++i)
    check((*actual.heavy_keys)[i].key==ranked[i].first && (*actual.heavy_keys)[i].count==ranked[i].second);
}
// Independent set/map oracle for this literal R(x,y,ignored), S(y) fixture.
// It does not inspect engine snapshots, support counters or collector output.
inline void fixture_facts(const stats::OwnerCapture& actual,const Database& input){
  check(actual.availability()==stats::Availability::available && actual.components().size()==8);
  Counts source_y,native,reverse,survivor_y,parent,visible;
  for(const auto& row:input.tables[0]){++source_y[Row{row[1]}];++native[Row{row[0],row[1]}];}
  for(const auto& [key,count]:native){
    static_cast<void>(count);++reverse[Row{key[1]}];
    if(input.tables[1].contains(Row{key[1]})){++survivor_y[Row{key[1]}];++parent[Row{}];++visible[key];}
  }
  const auto size=[](const auto& values){return static_cast<std::uint64_t>(values.size());};
  const auto& c=actual.components();const auto k=actual.limits().heavy_keys;
  check(c[0].cardinality==input.tables[0].size() && c[1].cardinality==input.tables[2].size());
  check(c[2].cardinality==native.size() && c[3].cardinality==native.size() && c[4].cardinality==visible.size());
  check(c[5].cardinality==parent.size() && c[6].cardinality==visible.size() && c[7].cardinality==reverse.size());
  distribution(c[0],source_y,size(input.tables[0]),k);distribution(c[2],native,size(native),k);
  distribution(c[4],survivor_y,size(visible),k);distribution(c[5],parent,size(parent),k);
  distribution(c[6],visible,size(visible),k);distribution(c[7],reverse,size(reverse),k);
  check(!c[1].distribution && !c[3].distribution);
  for(auto index:{std::size_t{5},std::size_t{6}}){
    std::uint64_t sum=0;for(const auto& [multiplicity,keys]:c[index].distribution->histogram)sum+=multiplicity*keys;
    check(sum==visible.size());
  }
}
inline void same_facts(const stats::OwnerCapture& a,const stats::OwnerCapture& b){
  check(a.availability()==b.availability() && a.physical_source_scope()==b.physical_source_scope() && a.components().size()==b.components().size());
  for(std::size_t i=0;i<a.components().size();++i){const auto& x=a.components()[i];const auto& y=b.components()[i];
    check(x.availability==y.availability && x.node_kind==y.node_kind && x.cardinality==y.cardinality && x.distribution.has_value()==y.distribution.has_value());
    check(x.layout.has_value()==y.layout.has_value());if(x.layout)check(x.layout->same_descriptor(*y.layout));
    check(x.selection.scope.index()==y.selection.scope.index() && x.selection.fields==y.selection.fields);
    if(x.distribution){check(x.distribution->completion==y.distribution->completion && x.distribution->visited==y.distribution->visited && x.distribution->ndv==y.distribution->ndv && x.distribution->histogram==y.distribution->histogram);
      check(x.distribution->heavy_keys.has_value()==y.distribution->heavy_keys.has_value());
      if(x.distribution->heavy_keys){check(x.distribution->heavy_keys->size()==y.distribution->heavy_keys->size());
        for(std::size_t j=0;j<x.distribution->heavy_keys->size();++j)check((*x.distribution->heavy_keys)[j].key==(*y.distribution->heavy_keys)[j].key && (*x.distribution->heavy_keys)[j].count==(*y.distribution->heavy_keys)[j].count);}}
  }
}
}

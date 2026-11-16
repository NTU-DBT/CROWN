#pragma once
#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include <algorithm>
#include <array>
#include <map>
#include <source_location>
#include <stdexcept>

namespace workload_fixture {
using namespace crown;
using namespace crown::runtime;
namespace ws=crown::runtime::workload;
inline Value n(std::int64_t value) { return value; }
inline void check(bool condition,std::source_location at=std::source_location::current()) {
  if (!condition) throw std::runtime_error(std::string(at.file_name())+":"+std::to_string(at.line())+": workload assertion");
}
template<class Action> void error(Action&& action,std::string_view code) {
  try { action(); } catch (const Error& failure) { check(failure.code()==code); return; }
  check(false);
}
inline ws::Options enabled(std::uint64_t period=1,std::uint64_t offset=0,std::uint64_t budget=65536) {
  ws::Options result; result.mode=ws::Mode::counters; result.period=period; result.offset=offset; result.detail_budget=budget; return result;
}
inline DeltaOptions delta_options(DeltaMode mode=DeltaMode::delta) {
  DeltaOptions result; result.mode=mode; result.physical.support.observation.mode=ObservationMode::off; return result;
}
inline PhysicalPlan plan(bool payload=false,bool generalized=false) {
  Catalog catalog{1,{{"R",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},
      {"S",{{"y",ScalarType::int64}}},{"unused",{{"u",ScalarType::int64}}}}};
  if (payload) catalog.tables[0].columns.push_back({"ignored",ScalarType::int64});
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"R",TableId{0},{VariableId{0},VariableId{1}}},{"S",TableId{1},{VariableId{1}}}},{{VariableId{0},"x"}},false};
  if (payload) query.atoms[0].terms.emplace_back(std::in_place_type<IgnoredColumn>);
  if (generalized) {
    query.head={{VariableId{1},"y"}};
    return planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},
      {{"g",NodeKind::generalized,{VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
       {"r",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},
       {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}});
  }
  return planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
       {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}});
}
inline PhysicalPlan alias_plan(bool predicate=false) {
  const Catalog catalog{2,{{"R",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"tag",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"left",TableId{0},{VariableId{0},VariableId{1},IgnoredColumn{}}},
       {"right",TableId{0},{VariableId{0},VariableId{1},IgnoredColumn{}}}},{{VariableId{0},"x"},{VariableId{1},"y"}},false};
  if (predicate) query.atoms[1].terms[2]=Value{std::int64_t{1}};
  return planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},
      {{"g",NodeKind::generalized,{VariableId{0},VariableId{1}},{NodeId{1},NodeId{2}},{},{}},
       {"left",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}},
       {"right",NodeKind::native,{VariableId{0},VariableId{1}},{},1,{}}},{},{}});
}
inline std::size_t find(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role,
    std::optional<NodeId> node={},std::optional<OccurrenceId> occurrence={},
    std::optional<std::size_t> edge={},std::optional<ws::Operation> sign={}) {
  for (std::size_t i=0;i<snapshot.descriptors().size();++i) {
    const auto& d=snapshot.descriptors()[i];
    if (d.table==table && d.operation==(op==SetOperation::insert?ws::Operation::insert:ws::Operation::erase) &&
        d.role==role && (!node || d.node==node) && (!occurrence || d.occurrence==occurrence) &&
        (!edge || d.edge==edge) && (!sign || d.event_operation==sign)) return i;
  }
  check(false); return 0;
}
inline const ws::Cell& cell(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role,
    std::optional<NodeId> node={},std::optional<OccurrenceId> occurrence={},
    std::optional<std::size_t> edge={},std::optional<ws::Operation> sign={}) {
  return snapshot.cells()[find(snapshot,table,op,role,node,occurrence,edge,sign)];
}
inline void apply(DeltaRuntime& runtime,std::size_t table,SetOperation operation,Row row) {
  auto output=runtime.apply({runtime.sequence()+1,TableId{table},operation,std::move(row)}); output.discard();
}
inline bool same_cells(std::span<const ws::Cell> a,std::span<const ws::Cell> b) {
  return a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin());
}
} // namespace workload_fixture

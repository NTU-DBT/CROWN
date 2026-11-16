#pragma once
#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/io/inspection.hpp"
#include <filesystem>
#include <fstream>
#include <variant>

namespace s05_inspection {
using namespace crown;
using namespace crown::runtime;
inline constexpr std::uint64_t allowance=64*1024*1024;
enum class Kind {support,physical,delta};
// All runtime alternatives delete copy and transfer concrete ownership on move.
using Owner=std::variant<SupportRuntime,PhysicalRuntime,DeltaRuntime>;
inline c02_test::Fixture fixture(unsigned flavor) {
  auto f=c02_test::fixture();
  if(flavor==1) {
    f.catalog.tables[0].columns[0].type=ScalarType::string;f.catalog.tables[1].columns[0].type=ScalarType::string;f.query.variables[0].type=ScalarType::string;
    const auto text=std::string(4096,'w')+std::string("\0tail",5);
    f.database.tables={Relation{Row{text}},Relation{Row{text,std::int64_t{1}},Row{text,std::int64_t{2}}},Relation{Row{std::int64_t{1}},Row{std::int64_t{2}}}};
  }else if(flavor==2) {
    f.catalog.tables={{"R",{{"x",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal}}}};
    f.query.variables={{"x",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal}};
    f.query.atoms={{"R",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3}}}};
    f.database.tables={Relation{Row{std::string(4096,'r')+std::string("\0tail",5),true,Date::parse("2026-11-09"),Decimal::parse("12345678901234567890123456789012345678")}}};
  }
  return f;
}
inline Owner make(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap=allowance) {
  PhysicalRuntimeOptions options;options.support.memory_limit_bytes=cap;options.support.capture_transitions=false;
  if(kind==Kind::support) {
    SupportRuntime owner(plan,options.support);std::uint64_t sequence=0;
    for(std::size_t i=0;i<plan.inputs().size();++i)for(const auto& row:database.tables[plan.inputs()[i].base.value]) {
      const auto tuple=plan.adapt_input(OccurrenceId{i},row);
      if(tuple)static_cast<void>(owner.apply({++sequence,plan.inputs()[i].node,SetOperation::insert,storage::export_row(tuple->values())}));
    }
    return owner;
  }
  if(kind==Kind::physical)return PhysicalRuntime::initialize(plan,database,options);
  DeltaOptions delta;delta.physical=options;delta.mode=DeltaMode::delta;return DeltaRuntime::initialize(plan,database,delta);
}
inline resource::MemoryAccount account(const Owner& owner) {return std::visit([](const auto& value){return value.plan().account();},owner);}
inline InvariantReport inspect(const Owner& owner,InspectionOptions limits={}) {return std::visit([&](const auto& value){return value.inspect_invariants(limits);},owner);}
inline void check_invariants(const Owner& owner) {std::visit([](const auto& value){value.check_invariants();},owner);}
inline SupportRuntime& support(Owner& owner) {
  return std::visit([](auto& value)->SupportRuntime& {
    using T=std::decay_t<decltype(value)>;
    if constexpr(std::is_same_v<T,SupportRuntime>)return value;
    else if constexpr(std::is_same_v<T,PhysicalRuntime>)return RuntimeTestProbe::support(value);
    else return RuntimeTestProbe::support(RuntimeTestProbe::physical(value));
  },owner);
}
// key is an ordinary deep-owned Row; this value has no automatic restore action.
struct Corruption {NodeId node;Row key;std::size_t previous;};
// Canonical/key exports can allocate. The returned key copy follows the intentional
// counter mutation, so this test helper does not promise exception rollback.
inline Corruption corrupt(Owner& owner) {
  auto& runtime=support(owner);const auto state=runtime.canonical_state();
  const CanonicalRecord* chosen=nullptr;NodeId node{};
  for(const auto& candidate:state.nodes)for(const auto& record:candidate.records) {
    if(!chosen && !record.values.empty()){chosen=&record;node=candidate.node;}
    for(const auto& value:record.values)if(std::holds_alternative<std::string>(value)){chosen=&record;node=candidate.node;}
  }
  c02_test::check(chosen!=nullptr,"invariant fixture has no corruptible nonempty key");
  const auto previous=RuntimeTestProbe::set_satisfied(runtime,node,chosen->values,chosen->satisfied+1);
  return {node,chosen->values,previous};
}
inline void restore(Owner& owner,const Corruption& corruption) {
  static_cast<void>(RuntimeTestProbe::set_satisfied(support(owner),corruption.node,corruption.key,corruption.previous));
}
template<class Function> void each(Function function) {
  for(unsigned flavor=0;flavor<3;++flavor) {
    const auto f=fixture(flavor);const auto candidates=c02_test::candidates(f,flavor==2?1:2,flavor==2?1:3);
    for(const bool indexed:{false,true})for(std::size_t shape=0;shape<candidates.candidate_count();++shape) {
      const auto plan=planner::lower_tree(f.catalog,f.query,candidates.candidate(shape)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
      for(const auto kind:{Kind::support,Kind::physical,Kind::delta})function(flavor,indexed,shape,kind,plan,f.database);
    }
  }
}
// Explicit test IO: default ofstream flags are not checked here; corpus validation
// must detect missing/truncated files. Production runtime code does not use this path.
inline void export_reports(const std::filesystem::path& directory) {
  std::filesystem::create_directories(directory);
  each([&](unsigned flavor,bool indexed,std::size_t shape,Kind kind,const PhysicalPlan& plan,const Database& database) {
    auto owner=make(plan,database,kind);
    const auto prefix=std::to_string(flavor)+"-"+std::to_string(indexed)+"-"+std::to_string(shape)+"-"+std::to_string(static_cast<unsigned>(kind))+"-";
    const auto write=[&](const char* phase,InspectionOptions options=InspectionOptions{}) {
      std::ofstream(directory/(prefix+phase+".json"))<<io::write_invariant_report(inspect(owner,options));
    };
    const auto healthy=inspect(owner);write("healthy");const auto corruption=corrupt(owner);write("corrupt");
    InspectionOptions zero;zero.work_limit=0;write("zero-work",zero);zero=InspectionOptions{};zero.issue_limit=0;write("zero-issue",zero);
    InspectionOptions partial;partial.work_limit=healthy.work/2;write("partial",partial);
    restore(owner,corruption);c02_test::check(inspect(owner).valid(),"fixture export failed to restore corruption");
  });
}
} // namespace s05_inspection

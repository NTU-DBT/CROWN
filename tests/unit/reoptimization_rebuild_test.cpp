#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/frontend/admission.hpp"
#include <iostream>
#include <set>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
using SignedRows=std::set<std::pair<SetOperation,Row>>;
Relation results(const DeltaRuntime& owner) {
  Relation out;auto cursor=owner.results();while(auto value=cursor.next())out.insert(storage::export_row(value->values()));return out;
}
SignedRows apply(DeltaRuntime& owner,TableId table,SetOperation operation,Row values) {
  auto epoch=owner.apply({owner.sequence()+1,table,operation,std::move(values)});SignedRows out;
  while(auto row=epoch.next())out.emplace(row->operation,storage::export_row(row->tuple.values()));
  return out;
}
template<class Action> void code(Action&& action,std::string_view expected) {
  try {action();}catch(const Error& failure){check(failure.code()==expected,"rebuild rejected with wrong error");return;}
  throw std::runtime_error("rebuild accepted a forbidden boundary/budget");
}
struct Case {planner::CandidateSnapshot family;PhysicalPlan basis;Database initial;bool sql;};
std::size_t exercise(const Case& fixture,DeltaMode mode,BuildMethod method) {
  std::size_t changed=0;
  for(std::size_t index=0;index<fixture.family.candidate_count();++index) {
    DeltaOptions options;options.mode=mode;options.physical.support.memory_limit_bytes=8U*1024U*1024U;
    options.physical.support.observation.mode=ObservationMode::off;
    auto old=DeltaRuntime::initialize(fixture.basis,fixture.initial,options);
    const auto expected_true=fixture.sql?Relation{Row{true}}:Relation{Row{}};
    const auto expected_false=fixture.sql?Relation{Row{false}}:Relation{};
    check(results(old)==expected_true,"initial literal result differs");
    static_cast<void>(apply(old,TableId{0},SetOperation::insert,Row{std::string("x")}));
    static_cast<void>(apply(old,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}));
    static_cast<void>(apply(old,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")}));
    static_cast<void>(apply(old,TableId{0},SetOperation::insert,Row{std::string("dangling")}));
    check(old.sequence()==4 && results(old)==expected_true,"old preparation changed literal epoch/state");
    const auto old_owner=old.owner();const auto old_sha=std::string(old.plan().physical_sha256());
    const auto physical=old.snapshot().physical.tables;const auto before=old.accounted_memory_statistics();
    {
      BuildOptions build;build.method=method;
      auto target=old.rebuilt_for(*fixture.family.candidate(index),build);
      const auto dual=old.accounted_memory_statistics();
      check(target.sequence()==4 && target.owner()!=old_owner && old.owner()==old_owner && old.sequence()==4,"rebuild changed epoch/original owner or reused identity");
      check(target.mode()==mode && target.options().mode==options.mode && target.plan().options().indexed_storage==old.plan().options().indexed_storage,"rebuild changed mode/backend grant");
      check(target.accounted_memory_statistics().owner==before.owner && dual.current.requested_bytes>before.current.requested_bytes,"dual state escaped the original query account");
      check(target.snapshot().physical.tables==physical && old.snapshot().physical.tables==physical && results(target)==expected_true && results(old)==expected_true,"rebuild changed source snapshot or SQL/CQ results");
      check(target.initialization_metrics().source_rows==4 && target.initialization_metrics().work>0 && target.initialization_context().route==InitializationRoute::rebuilt_snapshot,"snapshot build work/route missing");
      if(target.plan().physical_sha256()!=old_sha)++changed;
      const auto erased_old=apply(old,TableId{2},SetOperation::erase,Row{std::string("y")});
      const auto erased_new=apply(target,TableId{2},SetOperation::erase,Row{std::string("y")});
      check(erased_old==erased_new && results(target)==expected_false && results(old)==expected_false,"post-rebuild deletion/delta differs");
      const auto inserted_old=apply(old,TableId{2},SetOperation::insert,Row{std::string("y")});
      const auto inserted_new=apply(target,TableId{2},SetOperation::insert,Row{std::string("y")});
      check(inserted_old==inserted_new && results(target)==expected_true,"post-rebuild insertion/delta differs");
      check(apply(old,TableId{0},SetOperation::insert,Row{std::string("x")}).empty() && apply(target,TableId{0},SetOperation::insert,Row{std::string("x")}).empty(),"post-rebuild no-op emitted output");
      check(target.sequence()==old.sequence() && target.plan().physical_source_sha256()==old.plan().physical_source_sha256(),"source/epoch lineage diverged");
      target.check_invariants();old.check_invariants();
    }
    old.check_invariants();
    check(old.owner()==old_owner && old.plan().physical_sha256()==old_sha,"target retirement changed original identity/plan");
  }
  return changed;
}
void failures(const Case& fixture) {
  DeltaOptions options;options.mode=DeltaMode::delta;options.physical.support.memory_limit_bytes=8U*1024U*1024U;
  auto old=DeltaRuntime::initialize(fixture.basis,fixture.initial,options);const auto candidate=*fixture.family.candidate(1);
  const auto before=old.accounted_memory_statistics();const auto sequence=old.sequence();const auto rows=results(old);
  auto foreign_catalog=candidate.catalog();++foreign_catalog.version;
  const auto foreign=c05_independent::candidates(foreign_catalog,candidate.query());
  bool foreign_failed=false;
  try{static_cast<void>(old.rebuilt_for(*foreign.candidate(0)));}
  catch(const program::ReplanFailure& failure){foreign_failed=failure.fault()==program::ReplanFault::binding;}
  check(foreign_failed,"foreign candidate/source binding was accepted");
  BuildOptions zero;zero.work_limit=0;code([&]{static_cast<void>(old.rebuilt_for(candidate,zero));},"resource_limit");
  program::ReplanLimits no_lowering;no_lowering.physical.work_limit=0;
  bool lowering_failed=false;try{static_cast<void>(old.rebuilt_for(candidate,{},no_lowering));}catch(const program::ReplanFailure&){lowering_failed=true;}
  check(lowering_failed,"zero lowering grant was ignored");
  {
    auto cursor=old.results();code([&]{static_cast<void>(old.rebuilt_for(candidate));},"runtime_busy");
  }
  {
    auto pending=old.begin({1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}});
    code([&]{static_cast<void>(old.rebuilt_for(candidate));},"runtime_busy");pending.rollback();
  }
  {
    auto blocked=DeltaRuntime::initialize(fixture.basis,fixture.initial,options);
    auto unread=blocked.apply({1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}});
    check(unread.remaining()>0,"unread output fixture has no committed delta");
    code([&]{static_cast<void>(blocked.rebuilt_for(candidate));},"runtime_busy");unread.discard();
    check(blocked.sequence()==1 && blocked.ready(),"rejected bootstrap damaged committed output owner");
  }
  const auto& account=old.plan().account();const auto current=account.statistics().current.requested_bytes;
  const auto overhead=resource::MemoryAccount::allocation_bytes(0,alignof(std::max_align_t));
  {
    const auto remaining=before.limit_bytes-current;check(remaining>overhead+16,"memory failure fixture has no spare budget");
    auto reserve=account.allocate(static_cast<std::size_t>(remaining-overhead-16));bool exhausted=false;
    try{static_cast<void>(old.rebuilt_for(candidate));}catch(const std::bad_alloc&){exhausted=true;}
    check(exhausted,"candidate bootstrap bypassed original query memory grant");
  }
  check(old.sequence()==sequence && results(old)==rows && old.ready(),"failed build changed old committed state");
  auto retry=old.rebuilt_for(candidate);check(retry.sequence()==sequence && results(retry)==rows,"failed candidate bootstrap cannot retry");
  old.check_invariants();retry.check_invariants();
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_rebuild SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t changes=0,cases=0;
    for(const bool indexed:{false,true}) {
      const auto physical_options=indexed?s04_runtime::options():PhysicalOptions{};
      Case cq{fixture.all,c05_independent::lower(fixture.by_label.at("native_s"),physical_options),fixture.initial,false};
      const auto admitted=frontend::admit_sql("SELECT EXISTS(SELECT 1 FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0);",fixture.document.catalog);
      check(admitted.status==frontend::AdmissionStatus::admitted,"SQL EXISTS rebuild fixture rejected");
      const auto family=c05_independent::candidates(admitted.program->core_catalog,admitted.program->core);
      Case sql{family,planner::lower_normalized(*admitted.program,family.candidate(0)->tree(),physical_options),fixture.initial,true};
      for(const auto* input:{&cq,&sql})for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})for(const auto method:{BuildMethod::direct,BuildMethod::insertion_replay}) {
        changes+=exercise(*input,mode,method);cases+=input->family.candidate_count();
      }
      failures(cq);failures(sql);
    }
    check(changes>0,"rebuild checks never changed a physical tree");
    std::cout<<"C06 native candidate bootstrap PASS: "<<cases<<" SQL/CQ/backend/mode/build cases; "<<changes<<" actual alternative plans; epoch/state/delta/shared-budget/retry checks. Session switching remains separate.\n";return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

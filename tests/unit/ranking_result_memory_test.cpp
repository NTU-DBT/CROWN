#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include "ranking_detail.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>
#include <variant>

using namespace crown;
using namespace crown::runtime;
namespace pr=crown::planner::ranking;
namespace rr=crown::runtime::ranking;
namespace rd=crown::planner::ranking::detail;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
enum class Kind {physical,delta,session};
enum class Phase {ready,pending,stopped,dropped};
using Owner=std::variant<PhysicalRuntime,DeltaRuntime,QuerySession::Owner>;
void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(message));}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto value=account.statistics().current;
  check(value.allocations==1 && value.requested_bytes==resource::MemoryAccount::control_bytes(),"ranking result retained closed query storage");
}
resource::MemoryAccount account(const Owner& owner) {
  return std::visit([](const auto& value){
    if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return value.get_deleter().account();
    else return value.plan().account();
  },owner);
}
template<class Plan> Owner make_owner(Plan plan,const Database& database,Kind kind,std::uint64_t cap) {
  PhysicalRuntimeOptions physical;physical.support.memory_limit_bytes=cap;physical.support.capture_transitions=false;
  DeltaOptions delta;delta.physical=physical;delta.mode=DeltaMode::maintenance;
  if(kind==Kind::physical)return PhysicalRuntime::initialize(std::move(plan),database,physical);
  if(kind==Kind::delta)return DeltaRuntime::initialize(std::move(plan),database,delta);
  SessionOptions options;options.delta=delta;return QuerySession::create_typed(std::move(plan),database,{},options);
}
struct Facts {pr::Policy policy;Phase phase;bool enabled;};
struct Fixture {
  Owner owner;
  const planner::CandidateSnapshot& candidates;
  Facts facts;
  Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind,Phase phase,
      bool enabled,pr::Policy policy,std::uint64_t cap)
      :owner(make_owner(planner::lower_tree(f.catalog,f.query,c.candidate(0)->tree(),indexed?s04_runtime::options():PhysicalOptions{}),f.database,kind,cap)),
       candidates(c),facts{policy,phase,enabled} {
    workload::Options options;options.mode=enabled?workload::Mode::counters:workload::Mode::off;
    std::visit([&](auto& value){
      using T=std::decay_t<decltype(value)>;
      if constexpr(std::is_same_v<T,QuerySession::Owner>) {
        value->configure_workload_statistics(options);
        io::TransportBatch input({io::InputEvent{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},{}}});
        check(value->enqueue(input)==io::Admission::accepted,"ranking result input rejected");value->start();check(value->begin_next(),"ranking result session did not begin");value->drain();
        if(phase==Phase::pending) {
          io::TransportBatch next({io::InputEvent{{2,TableId{0},SetOperation::erase,{std::int64_t{1}}},{}}});
          check(value->enqueue(next)==io::Admission::accepted && value->begin_next(),"ranking result session did not stage pending input");
        }else if(phase==Phase::stopped)value->stop();else if(phase==Phase::dropped)value->drop();
      }else {
        value.configure_workload_statistics(options);
        if constexpr(std::is_same_v<T,PhysicalRuntime>)static_cast<void>(value.apply({1,TableId{0},SetOperation::insert,{std::int64_t{1}}}));
        else {auto pending=value.begin({1,TableId{0},SetOperation::insert,{std::int64_t{1}}});pending.drain();auto epoch=pending.commit();epoch.discard();}
      }
    },owner);
  }
  resource::MemoryAccount account() const{return ::account(owner);}
  pr::Attempt rank() const {
    pr::Request request;request.policy=facts.policy;request.fallback=pr::Fallback::height_only;
    return std::visit([&](const auto& value){
      if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return rr::rank_current(candidates,*value,request);
      else return rr::rank_current(candidates,value,request);
    },owner);
  }
  void stable() const {
    std::visit([](const auto& value){
      if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)check(value->status().committed_sequence==1,"ranking accepted private session input");
      else check(value.sequence()==1,"ranking changed committed owner epoch");
    },owner);
  }
};
pr::Result accepted(pr::Attempt attempt) {check(attempt.stop==pr::Stop::complete && attempt.result.has_value(),"native ranking result fixture failed");return *attempt.result;}
void verify(const pr::Result& result,Facts facts,const resource::MemoryAccount& account) {
  check(result.scores().size()==3 && result.scores().get_allocator()==rd::score_allocator<pr::CandidateScore>(account),"ranking result lost scores or original account");
  check(result.account().statistics().current==account.statistics().current,"ranking result replaced original account");
  const bool depth_available=facts.enabled && facts.phase!=Phase::pending && facts.phase!=Phase::dropped;
  const bool memory_available=facts.phase!=Phase::pending && facts.phase!=Phase::dropped;
  const bool fallback=(facts.policy==pr::Policy::committed_input_native_depth && !depth_available) ||
      (facts.policy==pr::Policy::tuple_index_slots && !memory_available);
  check(result.effective_policy()==(fallback?pr::Policy::height_only:facts.policy),"ranking evidence availability/fallback changed");
  check(result.evidence().has_value()==(facts.policy!=pr::Policy::height_only),"height-only ranking captured unnecessary evidence");
  for(const auto& score:result.scores()) {
    const auto text=rd::score_allocator<char>(account);
    check(score.structural_key.get_allocator()==text && score.numerator.get_allocator()==text && score.denominator.get_allocator()==text && score.slots.get_allocator()==text,
        "score text retained an unfunded/default allocator");
    check(score.depths.get_allocator()==rd::score_allocator<pr::OccurrenceDepth>(account) && score.table_depths.get_allocator()==rd::score_allocator<pr::TableDepth>(account) &&
        score.populations.get_allocator()==rd::score_allocator<pr::PopulationBound>(account) && score.slot_terms.get_allocator()==rd::score_allocator<pr::SlotTerm>(account),"score arrays lost original account");
    check(score.height==2 && score.structural_key==score.candidate.structural_key(),"ranking structural proof/key changed");
    for(const auto& item:score.table_depths)check(item.depth_sum.get_allocator()==text && item.contribution.get_allocator()==text,"table score text is unfunded");
    for(const auto& item:score.populations)check(item.records.get_allocator()==text && item.survivors.get_allocator()==text && item.parent_support.get_allocator()==text &&
        (!item.visible || item.visible->get_allocator()==text),"population score text is unfunded");
    for(const auto& item:score.slot_terms)check(item.population.get_allocator()==text && item.contribution.get_allocator()==text,"slot score text is unfunded");
    check(score.modeled_plan.has_value()==(result.effective_policy()==pr::Policy::tuple_index_slots),"ranking lost or invented a modeled plan");
    if(score.modeled_plan)check(score.modeled_plan->account().statistics().current==account.statistics().current && score.modeled_plan->validation().valid,"modeled plan used another allowance");
    if(result.effective_policy()==pr::Policy::committed_input_native_depth)check(score.denominator=="1" && !score.depths.empty() && score.table_depths.size()==3,"exact input-depth result changed");
  }
}
template<class Make> void requests_and_lifetime(Make make) {
  using T=decltype(make(allowance));std::optional<T> fixture(make(allowance));const auto account=fixture->account();const auto facts=fixture->facts;
  const auto before=account.statistics();pr::Attempt attempt;std::size_t calls=0;
  {s04_alloc::Scope count;attempt=fixture->rank();calls=s04_alloc::calls;}
  std::optional<pr::Result> held(accepted(std::move(attempt)));attempt.result.reset();const auto after=account.statistics();
  check(calls>0 && calls==after.successful_allocations-before.successful_allocations,"ranking result/model/scratch allocated outside the original query account");
  verify(*held,facts,account);fixture->stable();std::optional<pr::Result> copy;
  {s04_alloc::Scope none(0);copy=*held;fixture.reset();verify(*held,facts,account);verify(*copy,facts,account);held.reset();copy.reset();}
  controller_only(account);
}
template<class Make> std::size_t persistent(Make make) {
  auto fixture=make(allowance);const auto account=fixture.account();const auto held=accepted(fixture.rank());std::size_t expected=0;
  {s04_alloc::Scope count;const auto value=fixture.rank();expected=s04_alloc::calls;}
  check(expected>0 && expected<4096,"native ranking fault calibration is outside test bound");
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=account.statistics();pr::Attempt attempt;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));attempt=fixture.rank();calls=s04_alloc::calls;}
    if(point<expected) {
      check(attempt.stop==pr::Stop::allocation_failure && !attempt.result && calls==point+1 && account.statistics().current==before.current,
          "failed native ranking leaked, hid an allocation or published a prefix winner");attempt=fixture.rank();
    }else check(attempt.stop==pr::Stop::complete && calls==expected && calls==account.statistics().successful_allocations-before.successful_allocations,"native ranking missed a fault position");
    verify(accepted(std::move(attempt)),fixture.facts,account);verify(held,fixture.facts,account);fixture.stable();account.check_invariants();
  }
  return expected;
}
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make) {
  std::uint64_t peak=0;std::size_t pins=0;
  {
    auto fixture=make(allowance);const auto account=fixture.account();std::vector<pr::Result> held;held.reserve(2048);
    for(std::size_t i=0;i<2048;++i) {
      const auto before=account.statistics().peak_requested_bytes;auto value=accepted(fixture.rank());const auto after=account.statistics().peak_requested_bytes;
      if(i>0 && after>before){peak=after;pins=i;break;}held.push_back(std::move(value));
    }
    check(peak>0 && pins>0,"ranking did not exceed earlier setup peak");
  }
  for(const bool exact:{true,false}) {
    auto fixture=make(exact?peak:peak-1);const auto account=fixture.account();std::vector<pr::Result> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(accepted(fixture.rank()));
    const auto before=account.statistics().current;
    {const auto attempt=fixture.rank();if(exact)verify(accepted(attempt),fixture.facts,account);else check(attempt.stop==pr::Stop::allocation_failure && !attempt.result,"ranking ignored one-under actual query cap");}
    check(account.statistics().current==before,"query-cap ranking leaked partial result storage");fixture.stable();verify(held.front(),fixture.facts,account);
    if(!exact){held.pop_back();verify(accepted(fixture.rank()),fixture.facts,account);check(account.statistics().limit_bytes==peak-1,"ranking retry minted a larger allowance");}
  }
  return {peak,pins};
}
void native_runtime_input(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed,Kind kind) {
  const auto source=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),indexed?s04_runtime::options():PhysicalOptions{}));
  const auto other=source.account();const auto before=other.statistics();std::optional<Owner> owner;std::size_t calls=0;
  {s04_alloc::Scope count;owner=make_owner(source,f.database,kind,allowance);calls=s04_alloc::calls;}
  const auto target=account(*owner);check(calls>0 && calls==target.statistics().successful_allocations && other.statistics().successful_allocations==before.successful_allocations,
      "native runtime input used ordinary compiler storage or the source's allowance");
  std::visit([&](const auto& value){
    if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)check(value->report_metadata().plan().physical_sha256()==source.physical_sha256(),"native session input changed plan");
    else check(value.plan().physical_sha256()==source.physical_sha256(),"native runtime input changed plan");
  },*owner);
  {s04_alloc::Scope none(0);owner.reset();}controller_only(target);
}
void native_runtime_operation_grant(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates) {
  auto options=s04_runtime::options();
  const auto source=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),options));
  const auto original=options.indexed_storage->per_operation;
  storage::IndexWorkAllowance probe(original,true);const auto probe_account=resource::MemoryAccount::create(allowance);
  {const auto copy=CompiledProgram::freeze(probe_account,source,&probe);}
  controller_only(probe_account);
  const auto left=probe.remaining();
  // Starting the one outer runtime operation consumes a structural step before
  // native program admission begins.
  const storage::IndexWork admission{original.structural_steps-left.structural_steps+1,original.scalar_fields-left.scalar_fields,
      original.scalar_bytes-left.scalar_bytes,original.pointer_slots-left.pointer_slots,original.link_actions-left.link_actions};
  options.indexed_storage->per_operation=admission;
  const auto limited=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),options));
  storage::IndexWorkAllowance exact(admission,true);const auto target=resource::MemoryAccount::create(allowance);
  exact.admit(storage::IndexWork{.structural_steps=1});
  {const auto copy=CompiledProgram::freeze(target,limited,&exact);check(exact.remaining()==storage::IndexWork{},"native admission work calibration changed with limit values");}
  controller_only(target);
  const auto before=limited.account().statistics();
  for(const auto kind:{Kind::physical,Kind::delta,Kind::session}) {
    bool rejected=false;
    try {static_cast<void>(make_owner(limited,f.database,kind,allowance));}
    catch(const Error& error) {rejected=error.code()=="storage_work_limit";}
    check(rejected,"native runtime refilled its operation allowance between admission and initialization");
    check(limited.account().statistics().current==before.current && limited.account().statistics().successful_allocations==before.successful_allocations,
        "failed runtime admission allocated in its immutable compiler source account");
  }
  options.indexed_storage->per_operation={1,0,0,0,0};
  const auto early=CompiledProgram::standalone(planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),options));
  for(const auto kind:{Kind::physical,Kind::delta,Kind::session}) {
    bool rejected=false;
    try {static_cast<void>(make_owner(early,f.database,kind,allowance));}
    catch(const Error& error) {rejected=error.code()=="storage_work_limit";}
    check(rejected,"native compiler-input admission lost its public storage-work diagnostic");
  }
}
}
int main() {
  try {
    const auto f=c02_test::fixture();const auto candidates=c02_test::candidates(f);
    native_runtime_operation_grant(f,candidates);
    for(const bool indexed:{false,true}) {
      for(const auto kind:{Kind::physical,Kind::delta,Kind::session}) {
        native_runtime_input(f,candidates,indexed,kind);
        for(const auto policy:{pr::Policy::height_only,pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}) {
          const auto make=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,kind,Phase::ready,true,policy,cap);};
          requests_and_lifetime(make);const auto faults=persistent(make);const auto [peak,pins]=caps(make);
          std::cout<<(indexed?"indexed":"reference")<<" ranking kind="<<static_cast<int>(kind)<<" policy="<<static_cast<int>(policy)<<" faults="<<faults<<" peak="<<peak<<" pins="<<pins<<'\n';
        }
      }
      for(const auto phase:{Phase::pending,Phase::stopped,Phase::dropped})for(const auto policy:{pr::Policy::height_only,pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}) {
        const auto make=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,Kind::session,phase,true,policy,cap);};
        requests_and_lifetime(make);const auto faults=persistent(make);std::cout<<(indexed?"indexed":"reference")<<" session phase="<<static_cast<int>(phase)<<" policy="<<static_cast<int>(policy)<<" faults="<<faults<<'\n';
      }
      for(const auto policy:{pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}) {
        const auto make=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,Kind::delta,Phase::ready,false,policy,cap);};requests_and_lifetime(make);static_cast<void>(persistent(make));
      }
    }
    std::cout<<"native ranking result/control/text/arrays/scratch/modeled plans: original requests, caps, failures, lifetimes, phases and native runtime inputs passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

#include "owner_statistics_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/observability/statistics_explain.hpp"
#include "crown/io/cursor_observation.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>
#include <variant>

using namespace crown;
using namespace crown::runtime;
namespace obs=crown::observability;
namespace st=crown::runtime::statistics;
namespace ws=crown::runtime::workload;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
enum class Kind { mode,trace,gauges,compiled,combined,plan,statistics,context };
enum class Phase { ready,pending,stopped,dropped };
using Value=std::variant<std::monostate,obs::ModeDescriptor,CapturedObservationTrace,CapturedStateGauges,
    st::CombinedCapture,obs::PlanExplanation,obs::StatisticsExplanation,SessionStatisticsContext>;
void check(bool ok,std::string_view message){if(!ok)throw std::runtime_error(std::string(message));}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto value=account.statistics().current;
  check(value.allocations==1 && value.requested_bytes==resource::MemoryAccount::control_bytes(),"retained report graph did not release its original account storage");
}
PhysicalPlan plan(bool indexed) {
  Catalog catalog{1,{{"R",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"ignored",ScalarType::int64}}},
      {"S",{{"y",ScalarType::int64}}},{"unused",{{"u",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},IgnoredColumn{}}},{"s",TableId{1},{VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
DeltaOptions options(std::uint64_t cap) {
  DeltaOptions result;result.mode=DeltaMode::maintenance;result.physical.support.memory_limit_bytes=cap;
  result.physical.support.capture_transitions=false;result.physical.support.observation={ObservationMode::trace,4096,1,0,false};return result;
}
ws::Options enabled(){ws::Options result;result.mode=ws::Mode::counters;return result;}
struct Facts {std::uint64_t owner;Kind kind;Phase phase;};
void verify(const Value& value,Facts facts) {
  std::visit([&](const auto& report){
    using T=std::decay_t<decltype(report)>;
    if constexpr(std::is_same_v<T,obs::ModeDescriptor>)check(report.owner()==facts.owner && report.sequence()==1,"mode capture lost owner/epoch");
    else if constexpr(std::is_same_v<T,CapturedObservationTrace>)check(report.snapshot.support_owner==facts.owner && !report.records.empty(),"native trace lost records/owner");
    else if constexpr(std::is_same_v<T,CapturedStateGauges>)check(report.owner==facts.owner && report.sequence==1 && report.nodes.size()==2 && report.bases.size()==3,"native gauge facts changed");
    else if constexpr(std::is_same_v<T,st::CombinedCapture>)check(report.state().stamp().owner.value==facts.owner && report.state().stamp().sequence==1 && report.workload().stamp().committed_epoch==1,"combined report lost its actual boundary");
    else if constexpr(std::is_same_v<T,obs::PlanExplanation>) {
      if(facts.kind==Kind::compiled)check(report.mode().owner()==0 && report.mode().presence()==obs::RuntimePresence::compile_only,"native compile-only report acquired a runtime owner");
      else {
        check(report.mode().owner()==facts.owner && report.mode().sequence()==1,"plan report lost its owner/epoch");
        check(report.gauges().has_value()==(facts.phase==Phase::ready || facts.phase==Phase::stopped),"plan report exposed private/released gauges");
        if(report.gauges())check(report.gauges()->nodes.size()==2 && report.gauges()->bases.size()==3,"retained gauge arrays changed");
        if(facts.phase==Phase::dropped)check(report.trace_records().empty(),"dropped plan retained fresh trace records");
      }
    }else if constexpr(std::is_same_v<T,obs::StatisticsExplanation>) {
      check(report.mode().owner()==facts.owner && report.mode().sequence()==1 && report.combined().has_value()!=(facts.phase==Phase::dropped),"statistics report boundary changed");
      if(report.combined())check(report.combined()->workload().pending()==(facts.phase==Phase::pending),"statistics report lost pending metadata");
      if(facts.phase==Phase::dropped)check(report.trace().empty(),"dropped statistics report retained fresh trace records");
    }else if constexpr(std::is_same_v<T,SessionStatisticsContext>) {
      check(report.metadata().owner().value==facts.owner && report.status().committed_sequence==1 && report.combined().has_value()!=(facts.phase==Phase::dropped),"native session context boundary changed");
      if(report.combined())check(report.combined()->workload().pending()==(facts.phase==Phase::pending),"session context lost pending metadata");
      if(facts.phase==Phase::dropped)check(report.trace().records.empty(),"dropped context retained fresh trace records");
    }else check(false,"empty report product");
  },value);
}
struct RuntimeFixture {
  DeltaRuntime runtime;
  obs::StatisticsCaptureOptions request;
  Kind kind;
  RuntimeFixture(bool indexed,Kind k,std::uint64_t cap):runtime(DeltaRuntime::initialize(plan(indexed),owner_fixture::database(),options(cap))),kind(k) {
    request.state=owner_fixture::request(runtime.plan());
    if(k==Kind::combined || k==Kind::statistics)runtime.configure_workload_statistics(enabled());
    auto pending=runtime.begin({1,TableId{1},SetOperation::insert,{std::int64_t{8}}});pending.drain();auto epoch=pending.commit();epoch.discard();
  }
  resource::MemoryAccount account() const{return runtime.plan().account();}
  Facts facts() const{return {runtime.owner().value,kind,Phase::ready};}
  Value capture() const {
    switch(kind) {
      case Kind::mode:return obs::ModeDescriptor::capture(runtime);
      case Kind::trace:return runtime.capture_observation_trace();
      case Kind::gauges:return runtime.capture_state_gauges();
      case Kind::compiled:return obs::PlanExplanation::create(runtime.plan());
      case Kind::combined:return runtime.capture_combined_statistics(*request.state,request.state_limits);
      case Kind::plan:return obs::PlanExplanation::capture(runtime);
      case Kind::statistics:return obs::StatisticsExplanation::capture(runtime,request);
      case Kind::context:break;
    }
    throw std::runtime_error("invalid runtime report kind");
  }
  void stable() const {check(runtime.sequence()==1 && runtime.state()==DeltaState::ready,"report read changed accepted runtime state");}
};
struct SessionFixture {
  QuerySession::Owner session;
  obs::StatisticsCaptureOptions request;
  Kind kind;
  Phase phase;
  SessionFixture(bool indexed,Kind k,Phase p,std::uint64_t cap):kind(k),phase(p) {
    SessionOptions config;config.delta=options(cap);session=QuerySession::create_typed(plan(indexed),owner_fixture::database(),{},config);
    request.state=owner_fixture::request(session->report_metadata().plan());
    if(k!=Kind::plan)session->configure_workload_statistics(enabled());
    io::TransportBatch input({io::InputEvent{{1,TableId{1},SetOperation::insert,{std::int64_t{8}}},{}}});
    check(session->enqueue(input)==io::Admission::accepted,"session report fixture input rejected");session->start();check(session->begin_next(),"session fixture failed to begin");session->drain();
    if(p==Phase::pending) {
      io::TransportBatch next({io::InputEvent{{2,TableId{1},SetOperation::erase,{std::int64_t{8}}},{}}});
      check(session->enqueue(next)==io::Admission::accepted && session->begin_next(),"pending report fixture failed to begin");
    }else if(p==Phase::stopped)session->stop();else if(p==Phase::dropped)session->drop();
  }
  resource::MemoryAccount account() const{return session.get_deleter().account();}
  Facts facts() const{return {session->report_metadata().owner().value,kind,phase};}
  Value capture() const {
    if(kind==Kind::context)return session->capture_statistics_context(request.state,request.state_limits);
    if(kind==Kind::statistics)return obs::StatisticsExplanation::capture(*session,request);
    return obs::PlanExplanation::capture(*session);
  }
  void stable() const {check(session->status().committed_sequence==1,"report read accepted private session input");}
};
using Owners=std::array<resource::MemoryUsage,9>;
Owners owners(const resource::MemoryAccount& account) {
  Owners result{};for(std::size_t i=0;i<result.size();++i)result[i]=account.statistics_for({resource::MemoryOwnerKind::capture,i}).current;return result;
}
template<class Make> void requests_and_lifetime(Make make) {
  using Fixture=decltype(make(allowance));std::optional<Fixture> fixture(make(allowance));const auto account=fixture->account();const auto facts=fixture->facts();
  std::optional<Value> held,copy;const auto before=account.statistics();const auto owned_before=owners(account);std::size_t calls=0;
  {s04_alloc::Scope count;held=fixture->capture();calls=s04_alloc::calls;}
  const auto after=account.statistics();const auto owned_after=owners(account);std::uint64_t retained=0;
  for(std::size_t i=0;i<owned_after.size();++i)retained+=owned_after[i].requested_bytes-owned_before[i].requested_bytes;
  check(calls>0 && calls==after.successful_allocations-before.successful_allocations && retained==after.current.requested_bytes-before.current.requested_bytes,
      "report controls, trace/gauge arrays or nested captures allocated outside original query account");
  const auto blocks=[&](std::size_t id){return owned_after[id].allocations-owned_before[id].allocations;};
  if(facts.kind==Kind::mode)check(blocks(6)==1,"mode control is unfunded");
  if(facts.kind==Kind::trace)check(blocks(3)==1,"retained trace array is unfunded");
  if(facts.kind==Kind::gauges)check(blocks(4)==2,"retained node/base gauge arrays are unfunded");
  if(facts.kind==Kind::plan || facts.kind==Kind::compiled)check(blocks(6)==1 && blocks(7)==1,"plan/mode shared controls are unfunded");
  if(facts.kind==Kind::combined)check(blocks(5)==1,"combined shared control is unfunded");
  if(facts.kind==Kind::statistics)check(blocks(6)==1 && blocks(7)==1 && blocks(8)==1 && blocks(5)==(facts.phase==Phase::dropped?0U:1U),"statistics/plan/mode/combined controls are unfunded");
  if(facts.kind==Kind::context)check(blocks(0)==1 && blocks(5)==(facts.phase==Phase::dropped?0U:1U),"session/combined controls are unfunded");
  verify(*held,facts);fixture->stable();const auto copy_before=account.statistics();
  {s04_alloc::Scope count;copy=*held;calls=s04_alloc::calls;}
  const auto expected=facts.kind==Kind::trace?1U:facts.kind==Kind::gauges?2U:0U;
  check(calls==expected && calls==account.statistics().successful_allocations-copy_before.successful_allocations,"report handle/native value copy hid allocations or replaced its source grant");
  {s04_alloc::Scope none(0);fixture.reset();verify(*held,facts);verify(*copy,facts);held.reset();copy.reset();}controller_only(account);
}
template<class Make> std::size_t persistent(Make make) {
  auto fixture=make(allowance);const auto account=fixture.account();const auto facts=fixture.facts();const auto held=fixture.capture();std::size_t expected=0;
  {s04_alloc::Scope count;const auto calibration=fixture.capture();expected=s04_alloc::calls;}
  check(expected>0 && expected<2048,"invalid report fault-sweep request count");
  std::size_t failures=0;
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=account.statistics();std::optional<Value> output;bool failed=false;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{output=fixture.capture();}catch(const std::bad_alloc&){failed=true;}calls=s04_alloc::calls;}
    if(failed) {
      ++failures;check(point<expected && calls==point+1 && !output && account.statistics().current==before.current,"failed report capture leaked a private graph or changed the old value");
      output=fixture.capture();
    }else check(point==expected && calls==expected && calls==account.statistics().successful_allocations-before.successful_allocations,"report fault sweep missed an original-account request");
    verify(*output,facts);verify(held,facts);fixture.stable();{s04_alloc::Scope none(0);output.reset();}account.check_invariants();
  }
  check(failures==expected,"report persistent sweep did not cover every request");return failures;
}
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make) {
  std::uint64_t peak=0;std::size_t pins=0;
  {
    auto fixture=make(allowance);const auto account=fixture.account();std::vector<Value> held;held.reserve(2048);
    for(std::size_t n=0;n<2048;++n) {
      const auto before=account.statistics().peak_requested_bytes;auto candidate=fixture.capture();const auto after=account.statistics().peak_requested_bytes;
      if(n>0 && after>before){peak=after;pins=n;break;}held.push_back(std::move(candidate));
    }
    check(peak>0 && pins>0,"report cap fixture never exceeded its earlier setup peak");
  }
  for(const bool exact:{true,false}) {
    auto fixture=make(exact?peak:peak-1);const auto account=fixture.account();const auto facts=fixture.facts();std::vector<Value> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i){held.push_back(fixture.capture());}
    const auto before=account.statistics().current;bool denied=false;
    try{const auto value=fixture.capture();verify(value,facts);}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong report query-cap error");denied=true;}
    check(denied!=exact && account.statistics().current==before,"report exact/one-under cap changed retained data or leaked a partial graph");
    fixture.stable();verify(held.front(),facts);
    if(!exact){held.pop_back();const auto retry=fixture.capture();verify(retry,facts);check(account.statistics().limit_bytes==peak-1,"report retry minted another allowance");}
  }
  return {peak,pins};
}
void native_cross_account_values(bool indexed) {
  RuntimeFixture a(indexed,Kind::trace,allowance),b(indexed,Kind::trace,allowance);
  const auto source_trace=a.runtime.capture_observation_trace();const auto old_trace=b.runtime.capture_observation_trace();
  const auto source_gauges=a.runtime.capture_state_gauges();const auto old_gauges=b.runtime.capture_state_gauges();const auto account=a.account(),other=b.account();
  check(io::write_committed_state_gauges_json(source_gauges)==io::write_committed_state_gauges_json(a.runtime.committed_state_gauges()),"native gauge export differs from caller DTO");
  for(const bool gauges:{false,true})for(std::ptrdiff_t point=0;point<=(gauges?2:1);++point) {
    auto trace=old_trace;auto counts=old_gauges;const auto before=account.statistics(),before_other=other.statistics();bool failed=false;std::size_t calls=0;
    {s04_alloc::Scope fault(point);try{if(gauges)counts=source_gauges;else trace=source_trace;}catch(const std::bad_alloc&){failed=true;}calls=s04_alloc::calls;}
    if(failed) {
      check(account.statistics().current==before.current && other.statistics().current==before_other.current &&
          trace.snapshot.support_owner==old_trace.snapshot.support_owner && counts.owner==old_gauges.owner,"failed native value assignment paired new metadata with old arrays");
      if(gauges)counts=source_gauges;else trace=source_trace;
    }else check(calls==(gauges?2U:1U) && calls==account.statistics().successful_allocations-before.successful_allocations &&
        other.statistics().successful_allocations==before_other.successful_allocations,"native value assignment did not adopt the source account");
    check(gauges?counts.owner==source_gauges.owner:trace.snapshot.support_owner==source_trace.snapshot.support_owner,"native value retry lost source metadata");
  }
}
}
int main() {
  try {
    for(const bool indexed:{false,true}) {
      for(const auto kind:{Kind::mode,Kind::trace,Kind::gauges,Kind::compiled,Kind::combined,Kind::plan,Kind::statistics}) {
        const auto make=[&](std::uint64_t cap){return RuntimeFixture(indexed,kind,cap);};requests_and_lifetime(make);const auto faults=persistent(make);const auto [peak,pins]=caps(make);
        std::cout<<(indexed?"indexed":"reference")<<" runtime report kind="<<static_cast<int>(kind)<<" peak="<<peak<<" retained pins="<<pins<<" persistent faults="<<faults<<'\n';
      }
      for(const auto phase:{Phase::ready,Phase::pending,Phase::stopped,Phase::dropped})for(const auto kind:{Kind::plan,Kind::context,Kind::statistics}) {
        const auto make=[&](std::uint64_t cap){return SessionFixture(indexed,kind,phase,cap);};requests_and_lifetime(make);const auto faults=persistent(make);
        if(kind==Kind::statistics){const auto [peak,pins]=caps(make);std::cout<<(indexed?"indexed":"reference")<<" session phase="<<static_cast<int>(phase)<<" peak="<<peak<<" retained pins="<<pins<<'\n';}
        std::cout<<(indexed?"indexed":"reference")<<" session report kind="<<static_cast<int>(kind)<<" phase="<<static_cast<int>(phase)<<" persistent faults="<<faults<<'\n';
      }
      native_cross_account_values(indexed);
    }
    std::cout<<"native report graphs: original requests, controls/arrays, exact caps, retained lifetimes, session phases, cross-account values and persistent failures passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

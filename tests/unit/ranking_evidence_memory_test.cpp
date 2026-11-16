#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include "ranking_detail.hpp"
#include "frozen_binding_v2.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>

using namespace crown;
using namespace crown::runtime;
namespace pr=crown::planner::ranking;
namespace rr=crown::runtime::ranking;
namespace rd=crown::planner::ranking::detail;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
enum class Phase {ready,pending,stopped,dropped};
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto current=account.statistics().current;
  check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "ranking evidence left retained storage after final release");
}
PhysicalPlan plan(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) {
  return planner::lower_tree(f.catalog,f.query,candidates.candidate(0)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
}
workload::Options collection(bool enabled) {
  workload::Options result;result.mode=enabled?workload::Mode::counters:workload::Mode::off;return result;
}
PhysicalRuntimeOptions physical_options(std::uint64_t cap) {
  PhysicalRuntimeOptions result;result.support.memory_limit_bytes=cap;result.support.capture_transitions=false;return result;
}
DeltaOptions delta_options(std::uint64_t cap) {
  DeltaOptions result;result.physical=physical_options(cap);result.mode=DeltaMode::maintenance;return result;
}
struct Facts {std::uint64_t owner;Phase phase;bool enabled,wanted,session;};
struct PhysicalFixture {
  PhysicalRuntime runtime;
  const planner::CandidateSnapshot& candidates;
  bool enabled,wanted;
  PhysicalFixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,bool on,bool sources,std::uint64_t cap)
      :runtime(PhysicalRuntime::initialize(plan(f,c,indexed),f.database,physical_options(cap))),candidates(c),enabled(on),wanted(sources) {
    runtime.configure_workload_statistics(collection(on));
    static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{std::int64_t{1}}}));
  }
  resource::MemoryAccount account() const{return runtime.plan().account();}
  Facts facts() const{return {runtime.owner().value,Phase::ready,enabled,wanted,false};}
  rr::CaptureAttempt capture() const {rr::CaptureOptions options;options.source_cardinalities=wanted;return rr::capture(candidates,runtime,options);}
  void stable() const {check(runtime.sequence()==1,"evidence capture changed physical epoch");}
};
struct DeltaFixture {
  DeltaRuntime runtime;
  const planner::CandidateSnapshot& candidates;
  bool enabled,wanted;
  DeltaFixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,bool on,bool sources,std::uint64_t cap)
      :runtime(DeltaRuntime::initialize(plan(f,c,indexed),f.database,delta_options(cap))),candidates(c),enabled(on),wanted(sources) {
    runtime.configure_workload_statistics(collection(on));
    auto pending=runtime.begin({1,TableId{0},SetOperation::insert,{std::int64_t{1}}});pending.drain();auto epoch=pending.commit();epoch.discard();
  }
  resource::MemoryAccount account() const{return runtime.plan().account();}
  Facts facts() const{return {runtime.owner().value,Phase::ready,enabled,wanted,false};}
  rr::CaptureAttempt capture() const {rr::CaptureOptions options;options.source_cardinalities=wanted;return rr::capture(candidates,runtime,options);}
  void stable() const {check(runtime.sequence()==1 && runtime.state()==DeltaState::ready,"evidence capture changed delta epoch/state");}
};
struct SessionFixture {
  QuerySession::Owner session;
  const planner::CandidateSnapshot& candidates;
  Phase phase;
  bool enabled,wanted;
  SessionFixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Phase p,bool on,bool sources,std::uint64_t cap)
      :candidates(c),phase(p),enabled(on),wanted(sources) {
    SessionOptions options;options.delta=delta_options(cap);session=QuerySession::create_typed(plan(f,c,indexed),f.database,{},options);
    session->configure_workload_statistics(collection(on));
    io::TransportBatch input({io::InputEvent{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},{}}});
    check(session->enqueue(input)==io::Admission::accepted,"ranking session input rejected");session->start();check(session->begin_next(),"ranking session did not begin");session->drain();
    if(p==Phase::pending) {
      io::TransportBatch next({io::InputEvent{{2,TableId{0},SetOperation::erase,{std::int64_t{1}}},{}}});
      check(session->enqueue(next)==io::Admission::accepted && session->begin_next(),"ranking session pending input rejected");
    }else if(p==Phase::stopped)session->stop();else if(p==Phase::dropped)session->drop();
  }
  resource::MemoryAccount account() const{return session.get_deleter().account();}
  Facts facts() const{return {session->report_metadata().owner().value,phase,enabled,wanted,true};}
  rr::CaptureAttempt capture() const {rr::CaptureOptions options;options.source_cardinalities=wanted;return rr::capture(candidates,*session,options);}
  void stable() const {check(session->status().committed_sequence==1,"evidence capture accepted a private session epoch");}
};
void verify(const rr::RuntimeEvidence& evidence,Facts facts,const resource::MemoryAccount& account) {
  const auto& inputs=evidence.inputs();const auto& data=rd::Factory::data(inputs);
  check(inputs.identity().owner==facts.owner && inputs.identity().epoch==1,"retained ranking owner/epoch changed");
  check(data.binding.get_allocator()==rd::evidence_allocator<char>(account) &&
      inputs.weights().get_allocator()==rd::evidence_allocator<pr::InputWeight>(account) &&
      inputs.sources().get_allocator()==rd::evidence_allocator<pr::SourceCardinality>(account) &&
      inputs.source_observations().get_allocator()==rd::evidence_allocator<pr::SourceObservation>(account),
      "ranking binding or arrays lost the original account/attribution");
  check(evidence.session_context().has_value()==facts.session && evidence.captured().has_value()!=(facts.phase==Phase::dropped),"ranking native capture boundary changed");
  if(facts.phase==Phase::dropped) {
    check(inputs.depth_reasons()==pr::reason(pr::Reason::released) && inputs.memory_reasons()==pr::reason(pr::Reason::released),"released ranking facts were reused");return;
  }
  if(facts.enabled) {
    check(inputs.weights().size()==3 && inputs.denominator()==1 && inputs.weights()[0].inserts==1 && inputs.weights()[0].noop==1,"exact committed input census changed");
    check((inputs.depth_reasons()&pr::reason(pr::Reason::pending))==(facts.phase==Phase::pending?pr::reason(pr::Reason::pending):0),"ranking pending census reason changed");
  }else check(inputs.weights().empty() && (inputs.depth_reasons()&pr::reason(pr::Reason::disabled)),"disabled collection invented a census");
  if(facts.wanted && facts.phase!=Phase::pending) {
    check(inputs.memory_reasons()==0 && inputs.sources().size()==3 && inputs.source_observations().size()==3,"ranking source cardinalities changed");
    for(const auto& source:inputs.sources())check(source.rows==1,"ranking source cardinality was narrowed/lost");
  }else if(!facts.wanted)check(inputs.memory_reasons()&pr::reason(pr::Reason::not_captured),"unrequested source facts were invented");
}
rr::RuntimeEvidence accepted(rr::CaptureAttempt attempt) {
  check(attempt.stop==pr::Stop::complete && attempt.evidence.has_value(),"ranking memory fixture capture failed");return *attempt.evidence;
}
using Owners=std::array<resource::MemoryUsage,11>;
Owners owners(const resource::MemoryAccount& account) {
  Owners result{};for(std::size_t i=0;i<result.size();++i)result[i]=account.statistics_for({resource::MemoryOwnerKind::capture,i}).current;return result;
}
template<class Make> void requests_and_lifetime(Make make) {
  using Fixture=decltype(make(allowance));std::optional<Fixture> fixture(make(allowance));const auto account=fixture->account();const auto facts=fixture->facts();
  const auto before=account.statistics();const auto owned_before=owners(account);rr::CaptureAttempt attempt;std::size_t calls=0;
  {s04_alloc::Scope count;attempt=fixture->capture();calls=s04_alloc::calls;}
  std::optional<rr::RuntimeEvidence> held(accepted(std::move(attempt)));attempt.evidence.reset();const auto after=account.statistics();const auto owned_after=owners(account);std::uint64_t retained=0;
  for(std::size_t i=0;i<owned_after.size();++i)retained+=owned_after[i].requested_bytes-owned_before[i].requested_bytes;
  check(calls>0 && calls==after.successful_allocations-before.successful_allocations && retained==after.current.requested_bytes-before.current.requested_bytes,
      "ranking capture made an allocation outside the original query account");
  const auto blocks=[&](std::size_t i){return owned_after[i].allocations-owned_before[i].allocations;};
  check(blocks(9)>=2 && blocks(10)==1,"ranking evidence or runtime shared controls are unfunded");
  if(facts.phase==Phase::ready && facts.enabled && facts.wanted)check(blocks(9)==5,"ranking evidence did not retain exactly its control, binding and three arrays");
  verify(*held,facts,account);fixture->stable();std::optional<rr::RuntimeEvidence> copy;std::optional<pr::Evidence> inputs;
  {s04_alloc::Scope none(0);copy=*held;inputs=held->inputs();}
  {s04_alloc::Scope none(0);fixture.reset();verify(*held,facts,account);verify(*copy,facts,account);copy.reset();inputs.reset();held.reset();}
  controller_only(account);
}
template<class Make> std::size_t persistent(Make make) {
  auto fixture=make(allowance);const auto account=fixture.account();const auto facts=fixture.facts();const auto held=accepted(fixture.capture());std::size_t expected=0;
  {s04_alloc::Scope count;const auto calibration=fixture.capture();expected=s04_alloc::calls;}
  check(expected>0 && expected<2048,"invalid ranking fault-sweep request count");std::size_t failures=0;
  for(std::size_t point=0;point<=expected;++point) {
    const auto before=account.statistics();rr::CaptureAttempt attempt;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));attempt=fixture.capture();calls=s04_alloc::calls;}
    if(point<expected) {
      ++failures;check(attempt.stop==pr::Stop::allocation_failure && !attempt.evidence && calls==point+1 && account.statistics().current==before.current,
          "failed ranking capture published evidence, hid an allocation or leaked a private graph");attempt=fixture.capture();
    }else check(attempt.stop==pr::Stop::complete && calls==expected && calls==account.statistics().successful_allocations-before.successful_allocations,"ranking fault sweep missed an original-account request");
    verify(accepted(std::move(attempt)),facts,account);verify(held,facts,account);fixture.stable();account.check_invariants();
  }
  return failures;
}
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make) {
  std::uint64_t peak=0;std::size_t pins=0;
  {
    auto fixture=make(allowance);const auto account=fixture.account();std::vector<rr::RuntimeEvidence> held;held.reserve(2048);
    for(std::size_t n=0;n<2048;++n) {
      const auto before=account.statistics().peak_requested_bytes;auto candidate=accepted(fixture.capture());const auto after=account.statistics().peak_requested_bytes;
      if(n>0 && after>before){peak=after;pins=n;break;}held.push_back(std::move(candidate));
    }
    check(peak>0 && pins>0,"ranking captures never exceeded the earlier setup peak");
  }
  for(const bool exact:{true,false}) {
    auto fixture=make(exact?peak:peak-1);const auto account=fixture.account();const auto facts=fixture.facts();std::vector<rr::RuntimeEvidence> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(accepted(fixture.capture()));
    const auto before=account.statistics().current;
    {
      const auto attempt=fixture.capture();
      if(exact)verify(accepted(attempt),facts,account);
      else check(attempt.stop==pr::Stop::allocation_failure && !attempt.evidence,"ranking capture ignored its one-under query cap");
    }
    check(account.statistics().current==before,"ranking query-cap attempt leaked a partial graph");fixture.stable();verify(held.front(),facts,account);
    if(!exact){held.pop_back();const auto retry=accepted(fixture.capture());verify(retry,facts,account);check(account.statistics().limit_bytes==peak-1,"ranking retry minted another allowance");}
  }
  return {peak,pins};
}
template<class Make> void run(Make make,std::string_view label,bool cap_test=true) {
  requests_and_lifetime(make);const auto faults=persistent(make);
  std::cout<<label<<" persistent faults="<<faults;
  if(cap_test){const auto [peak,pins]=caps(make);std::cout<<" peak="<<peak<<" retained pins="<<pins;}
  std::cout<<'\n';
}
struct BindingFixture {Catalog catalog;Query query;FreeConnexTree tree;};
BindingFixture binding_fixture(bool invalid_utf8=true) {
  const std::string raw=std::string(160,'z')+(invalid_utf8?std::string("a\0\xff",3):std::string("a\0b",3));
  Table values{"values",{{"key",ScalarType::int64},{raw,ScalarType::int64},{"s",ScalarType::string},
      {"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,12}}}};
  values.source_schema_version=13;values.constraints={UniqueConstraint{raw,{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"self",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::untrusted}};
  values.statistics.row_count=997;values.statistics.distinct_counts={{{ColumnId{0}},991}};values.key_hints={{{ColumnId{1}},raw}};
  Catalog catalog{7,{values}};
  Query query{{{"x",ScalarType::int64}},{{"v",TableId{0},{VariableId{0},Value{INT64_MIN},Value{raw},Value{true},
      Value{Date::parse("0001-01-01")},Value{Decimal::parse("-99999999999999999999999999.123456789012")}}}},
      {{VariableId{0},raw},{VariableId{0},"again"}},false};
  FreeConnexTree tree{NodeId{0},{{"v",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return {std::move(catalog),std::move(query),std::move(tree)};
}
template<class C,class Q> std::size_t binding_checks(const C& catalog,const Q& query,std::string_view expected,const resource::MemoryAccount& account) {
  pr::Limits limits;limits.binding_key_bytes=expected.size();limits.payload_bytes=expected.size();rd::Budget budget(limits),legacy_budget(limits);
  const auto legacy=rd::binding(catalog,query,legacy_budget);const auto before=account.statistics();std::optional<pr::EvidenceText> encoded;std::size_t calls=0;
  {s04_alloc::Scope count;encoded=rd::binding(catalog,query,budget,account);calls=s04_alloc::calls;}
  check(std::string_view(*encoded)==expected && legacy==expected && budget.usage.work==legacy_budget.usage.work && budget.usage.binding_key_bytes==legacy_budget.usage.binding_key_bytes &&
      budget.usage.payload_bytes==legacy_budget.usage.payload_bytes,"native binding changed frozen v2 bytes or logical admission");
  check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations && encoded->get_allocator()==rd::evidence_allocator<char>(account),
      "native binding or decimal formatting allocated outside its original account");encoded.reset();
  for(std::size_t point=0;point<=calls;++point) {
    const auto baseline=account.statistics().current;rd::Budget current(limits);bool failed=false;std::optional<pr::EvidenceText> value;std::size_t actual=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{value=rd::binding(catalog,query,current,account);}catch(const std::bad_alloc&){failed=true;}actual=s04_alloc::calls;}
    check(failed==(point<calls) && actual==(failed?point+1:calls),"binding persistent sweep missed an allocation");
    if(failed){check(account.statistics().current==baseline,"failed binding leaked a partially grown string");rd::Budget retry(limits);value=rd::binding(catalog,query,retry,account);}
    check(std::string_view(*value)==expected,"binding retry changed binary/scalar bytes");value.reset();check(account.statistics().current==baseline,"binding release leaked its original account storage");
  }
  pr::Limits zero;zero.payload_bytes=0;rd::Budget rejected(zero);bool stopped=false;std::size_t denied_calls=0;
  {s04_alloc::Scope none(0);try{static_cast<void>(rd::binding(catalog,query,rejected,account));}catch(const rd::Failure& failure){stopped=failure.stop==pr::Stop::byte_limit;}denied_calls=s04_alloc::calls;}
  check(stopped && denied_calls==0 && rejected.usage.binding_key_bytes==0,"native prefix allocated before logical admission");
  return calls;
}
void bindings() {
  const auto f=binding_fixture();const auto expected=planner::frozen_binding_v2::binding_bytes(f.catalog,f.query);const auto account=resource::MemoryAccount::create(allowance);
  const auto calls=binding_checks(f.catalog,f.query,expected,account);const auto peak=account.statistics().peak_requested_bytes;controller_only(account);
  for(const bool exact:{true,false}) {
    const auto bounded=resource::MemoryAccount::create(exact?peak:peak-1);rd::Budget budget(pr::Limits{});bool denied=false;
    try{const auto encoded=rd::binding(f.catalog,f.query,budget,bounded);check(std::string_view(encoded)==expected,"bounded native binding bytes changed");}
    catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong native binding cap failure");denied=true;}
    check(denied!=exact,"native binding exact/one-under query admission changed");controller_only(bounded);
  }
  CompiledProgram native;std::string native_expected;
  {auto source=binding_fixture(false);native_expected=planner::frozen_binding_v2::binding_bytes(source.catalog,source.query);
    native=CompiledProgram::standalone(planner::lower_tree(source.catalog,source.query,source.tree));}
  const auto native_account=native.account();const auto native_calls=binding_checks(native.catalog(),native.query(),native_expected,native_account);
  native={};controller_only(native_account);
  std::cout<<"frozen v2 binding persistent faults="<<calls<<'/'<<native_calls<<" exact/one-under peak="<<peak<<'\n';
}
}
int main() {
  try {
    bindings();const auto f=c02_test::fixture();const auto candidates=c02_test::candidates(f);
    for(const bool indexed:{false,true}) {
      std::cout<<(indexed?"indexed":"reference")<<'\n';
      run([&](std::uint64_t cap){return PhysicalFixture(f,candidates,indexed,true,true,cap);},"physical");
      run([&](std::uint64_t cap){return DeltaFixture(f,candidates,indexed,true,true,cap);},"delta");
      for(const auto phase:{Phase::ready,Phase::pending,Phase::stopped,Phase::dropped}) {
        std::cout<<"session phase="<<static_cast<int>(phase)<<' ';
        run([&](std::uint64_t cap){return SessionFixture(f,candidates,indexed,phase,true,true,cap);},"session");
      }
      for(const auto& [enabled,wanted]:{std::pair{false,true},std::pair{true,false},std::pair{false,false}})
        run([&](std::uint64_t cap){return DeltaFixture(f,candidates,indexed,enabled,wanted,cap);},"delta optional facts",false);
    }
    std::cout<<"native ranking evidence: original requests/controls/arrays/scratch, frozen bytes, retained lifetime, query caps, phases and persistent failures passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

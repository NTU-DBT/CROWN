#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/selection.hpp"
#include "selection_detail.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>
#include <variant>

using namespace crown;
using namespace crown::runtime;
namespace ps=crown::planner::selection;
namespace rs=crown::runtime::selection;
namespace sd=crown::planner::selection::detail;
namespace pr=crown::planner::ranking;
namespace {
constexpr std::uint64_t allowance=64*1024*1024;
enum class Kind {physical,delta,session};
enum class SourceKind {direct,compiler,native};
enum class Case {height,depth,slots,constrained_depth};
enum class Cache {bypass,disabled,miss,hit,evict};
using Owner=std::variant<PhysicalRuntime,DeltaRuntime,QuerySession::Owner>;
void check(bool value,std::string_view message) {if(!value)throw std::runtime_error(std::string(message));}
resource::MemoryAccount account(const Owner& owner) {
  return std::visit([](const auto& value) {
    if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return value.get_deleter().account();
    else return value.plan().account();
  },owner);
}
Owner make_owner(const PhysicalPlan& plan,const Database& database,Kind kind,std::uint64_t cap) {
  PhysicalRuntimeOptions physical;physical.support.memory_limit_bytes=cap;physical.support.capture_transitions=false;
  if(kind==Kind::physical)return PhysicalRuntime::initialize(plan,database,physical);
  DeltaOptions delta;delta.physical=physical;delta.mode=DeltaMode::maintenance;
  if(kind==Kind::delta)return DeltaRuntime::initialize(plan,database,delta);
  SessionOptions options;options.delta=delta;return QuerySession::create_typed(plan,database,{},options);
}
rs::CurrentSelection accepted(rs::Attempt attempt) {
  if(attempt.stop!=ps::Stop::complete || !attempt.selection)
    throw std::runtime_error("native selection fixture failed: stop="+std::to_string(static_cast<unsigned>(attempt.stop))+" stage="+std::to_string(static_cast<unsigned>(attempt.stage)));
  return *attempt.selection;
}
ps::Request request(Case value) {
  ps::Request out;out.policy=value==Case::height?ps::Policy::height_only:
      value==Case::slots?ps::Policy::tuple_index_slots:ps::Policy::committed_input_native_depth;
  if(value==Case::constrained_depth)out.constraint=ps::TupleIndexSlotLimit{"100000000000000000000000000000000000000000000000000000000000000000000000000000000"};
  return out;
}
struct Fixture {
  PhysicalPlan compiler;
  Owner owner;
  const planner::CandidateSnapshot& candidates;
  ps::Source source;
  ps::Request wanted;
  Cache mode;
  ps::PlanCache cache;
  std::optional<rs::CurrentSelection> previous;
  Fixture(const c02_test::Fixture& f,const planner::CandidateSnapshot& c,bool indexed,Kind kind,
      SourceKind source_kind,Case policy,Cache use,std::uint64_t cap)
      :compiler(planner::lower_tree(f.catalog,f.query,c.candidate(0)->tree(),[&] {
        auto options=indexed?s04_runtime::options():PhysicalOptions{};
        options.policy.cost_model=std::string(80,'m')+std::string("\0tail",5);return options;
      }())),owner(make_owner(compiler,f.database,kind,cap)),candidates(c),
       source(source_kind==SourceKind::direct?ps::Source{ps::DirectCQ{compiler.options()}}:
          source_kind==SourceKind::compiler?ps::Source{ps::PhysicalBasis{compiler}}:
          ps::Source{ps::PhysicalBasis{CompiledProgram::standalone(compiler)}}),
       wanted(request(policy)),mode(use),cache(ps::PlanCache::create(use==Cache::disabled?ps::CacheLimits{0,0,0}:ps::CacheLimits{1,8*1024*1024,32*1024*1024})) {
    std::visit([&](auto& value) {
      workload::Options options;options.mode=workload::Mode::counters;
      if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>) {
        value->configure_workload_statistics(options);
        io::TransportBatch input({io::InputEvent{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},{}}});
        check(value->enqueue(input)==io::Admission::accepted,"selection input rejected");value->start();
        check(value->begin_next(),"selection session did not begin");value->drain();
      }else {
        value.configure_workload_statistics(options);
        if constexpr(std::is_same_v<std::decay_t<decltype(value)>,PhysicalRuntime>)static_cast<void>(value.apply({1,TableId{0},SetOperation::insert,{std::int64_t{1}}}));
        else {auto pending=value.begin({1,TableId{0},SetOperation::insert,{std::int64_t{1}}});pending.drain();auto epoch=pending.commit();epoch.discard();}
      }
    },owner);
    if(mode==Cache::hit)previous=accepted(run(wanted,ps::CacheUse::read_write));
    if(mode==Cache::evict)previous=accepted(run(request(Case::height),ps::CacheUse::read_write));
  }
  resource::MemoryAccount account() const {return ::account(owner);}
  rs::Attempt run(const ps::Request& r,ps::CacheUse use) {
    return std::visit([&](const auto& value) {
      if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)return rs::select_current(candidates,source,*value,r,{},&cache,use);
      else return rs::select_current(candidates,source,value,r,{},&cache,use);
    },owner);
  }
  rs::Attempt select() {return run(wanted,mode==Cache::bypass?ps::CacheUse::bypass:mode==Cache::hit?ps::CacheUse::read_only:ps::CacheUse::read_write);}
  void stable() const {
    std::visit([](const auto& value) {
      if constexpr(std::is_same_v<std::decay_t<decltype(value)>,QuerySession::Owner>)check(value->status().committed_sequence==1,"selection changed session epoch");
      else check(value.sequence()==1,"selection changed runtime epoch");
    },owner);
  }
};
void verify(const rs::CurrentSelection& value,const resource::MemoryAccount& account,Case policy) {
  const auto& result=value.selection();const auto& text=sd::selection_allocator<char>(account);
  check(result.account().statistics().owner==account.statistics().owner,"selection replaced the original account");
  check(result.assessments().get_allocator()==sd::selection_allocator<ps::Assessment>(account) &&
      result.decisions().get_allocator()==sd::selection_allocator<ps::CandidateDecision>(account),"selection arrays use another allocator");
  check(result.assessments().size()==(policy==Case::constrained_depth?2U:1U) && result.decisions().size()==3,"selection lost complete assessments or decisions");
  for(const auto& item:result.assessments())check(item.result.account().statistics().owner==account.statistics().owner && item.result.scores().size()==3,"selection assessment minted an allowance");
  if(const auto* direct=std::get_if<ps::CapturedDirectCQ>(&result.source())) {
    const auto& p=direct->options.policy;
    check(p.arithmetic.get_allocator()==text && p.planner.get_allocator()==text && p.optimization.get_allocator()==text && p.cost_model.get_allocator()==text &&
        p.cost_model.size()==85 && p.cost_model[80]=='\0',"selection source strings are unfunded or lost embedded NUL");
  }
  if(const auto* cap=std::get_if<ps::CapturedTupleIndexSlotLimit>(&result.request().constraint))check(cap->maximum.get_allocator()==text,"selection constraint text is unfunded");
  if(result.cache_binding())check(result.cache_binding()->get_allocator()==text && !result.cache_binding()->empty(),"selection cache key is unfunded");
  check(result.plan().validation().valid && result.plan().account().statistics().owner==account.statistics().owner &&
      result.selected().height()==2 && result.plan().tree().nodes.size()>0,"selection plan lost original account or structural authority");
  check(value.capture().inputs().identity().epoch==1,"selection result changed captured boundary");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto now=account.statistics().current;
  check(now.allocations==1 && now.requested_bytes==resource::MemoryAccount::control_bytes(),"selection/cache retained closed query allocations");
}
template<class Make> void requests_and_lifetime(Make make,Case policy) {
  using T=decltype(make(allowance));std::optional<T> fixture(make(allowance));const auto account=fixture->account();const auto before=account.statistics();
  rs::Attempt attempt;std::size_t calls=0;
  {s04_alloc::Scope count;attempt=fixture->select();calls=s04_alloc::calls;}
  std::optional<rs::CurrentSelection> held(accepted(std::move(attempt)));attempt.selection.reset();
  check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations,"selection result/lowering/cache/scratch allocated outside original account");
  verify(*held,account,policy);fixture->stable();std::optional<rs::CurrentSelection> copy;
  {s04_alloc::Scope none(0);copy=*held;fixture.reset();verify(*held,account,policy);verify(*copy,account,policy);held.reset();copy.reset();}
  controller_only(account);
}
template<class Make> std::size_t persistent(Make make,Case policy) {
  std::size_t expected=0;
  {auto fixture=make(allowance);rs::Attempt attempt;{s04_alloc::Scope count;attempt=fixture.select();expected=s04_alloc::calls;}verify(accepted(std::move(attempt)),fixture.account(),policy);}
  check(expected>0 && expected<4096,"selection fault calibration exceeded bound");
  for(std::size_t point=0;point<=expected;++point) {
    auto fixture=make(allowance);const auto account=fixture.account();const auto before=account.statistics();const auto cached=fixture.cache.statistics();rs::Attempt attempt;std::size_t calls=0;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));attempt=fixture.select();calls=s04_alloc::calls;}
    if(point<expected) {
      check(attempt.stop==ps::Stop::allocation_failure && !attempt.selection && calls==point+1 && account.statistics().current==before.current,
          "failed selection leaked, hid an allocation or published a partial winner");
      check(fixture.cache.statistics()==cached,"failed selection changed cache statistics or FIFO ownership");
      attempt=fixture.select();
    }else check(attempt.stop==ps::Stop::complete && calls==expected && calls==account.statistics().successful_allocations-before.successful_allocations,"selection missed an allocation fault position");
    verify(accepted(std::move(attempt)),account,policy);fixture.stable();
    if(fixture.previous)verify(*fixture.previous,account,fixture.mode==Cache::evict?Case::height:policy);
    account.check_invariants();
  }
  return expected;
}
template<class Make> std::pair<std::uint64_t,std::size_t> caps(Make make,Case policy) {
  std::uint64_t peak=0;std::size_t pins=0;
  {auto fixture=make(allowance);const auto account=fixture.account();std::vector<rs::CurrentSelection> held;held.reserve(2048);
    for(std::size_t i=0;i<2048;++i) {
      const auto before=account.statistics().peak_requested_bytes;auto value=accepted(fixture.select());const auto after=account.statistics().peak_requested_bytes;
      if(i>0 && after>before){peak=after;pins=i;break;}held.push_back(std::move(value));
    }
    check(peak>0 && pins>0,"selection result did not exceed setup high water");
  }
  for(const bool exact:{true,false}) {
    auto fixture=make(exact?peak:peak-1);const auto account=fixture.account();std::vector<rs::CurrentSelection> held;held.reserve(pins);
    for(std::size_t i=0;i<pins;++i)held.push_back(accepted(fixture.select()));
    const auto before=account.statistics().current;
    {const auto attempt=fixture.select();if(exact)verify(accepted(attempt),account,policy);else check(attempt.stop==ps::Stop::allocation_failure && !attempt.selection,"selection ignored one-under actual query cap");}
    check(account.statistics().current==before,"query-cap failure leaked partial selection storage");verify(held.front(),account,policy);fixture.stable();
    if(!exact){held.pop_back();verify(accepted(fixture.select()),account,policy);check(account.statistics().limit_bytes==peak-1,"selection retry minted a larger allowance");}
  }
  return {peak,pins};
}
void session_phases(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) {
  for(const unsigned phase:{0U,1U,2U}) {
    std::optional<Fixture> fixture(std::in_place,f,candidates,indexed,Kind::session,SourceKind::direct,Case::constrained_depth,Cache::hit,allowance);
    const auto account=fixture->account();std::optional<rs::CurrentSelection> held(accepted(fixture->select()));
    auto& session=*std::get<QuerySession::Owner>(fixture->owner);
    if(phase==0)session.stop();
    else if(phase==1) {
      io::TransportBatch next({io::InputEvent{{2,TableId{0},SetOperation::erase,{std::int64_t{1}}},{}}});
      check(session.enqueue(next)==io::Admission::accepted && session.begin_next(),"selection phase fixture failed to stage private input");
    }else session.drop();
    const auto before=account.statistics();const auto cached=fixture->cache.statistics();rs::Attempt attempt;std::size_t calls=0;
    {s04_alloc::Scope count;attempt=fixture->select();calls=s04_alloc::calls;}
    check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations,"selection session boundary allocated outside original account");
    if(phase==0)verify(accepted(std::move(attempt)),account,Case::constrained_depth);
    else {
      check(attempt.stop==ps::Stop::boundary_unavailable && !attempt.selection && fixture->cache.statistics()==cached && account.statistics().current==before.current,
          "blocked session selection published a result, changed the cache or retained private capture storage");
      const auto expected=phase==1?pr::Reason::pending:pr::Reason::released;
      check(attempt.reasons&pr::reason(expected),"selection lost its pending/released boundary reason");
    }
    attempt.selection.reset();
    verify(*held,account,Case::constrained_depth);
    {s04_alloc::Scope none(0);fixture.reset();verify(*held,account,Case::constrained_depth);held.reset();}
    controller_only(account);
  }
  for(const auto kind:{Kind::physical,Kind::delta,Kind::session}) {
    Fixture fixture(f,candidates,indexed,kind,SourceKind::direct,Case::height,Cache::bypass,allowance);
    fixture.wanted.limits.aggregate.work=0;const auto before=fixture.account().statistics().current;rs::Attempt attempt;
    {s04_alloc::Scope none(0);attempt=fixture.select();check(s04_alloc::calls==0,"selection admission minted an account before checking limits");}
    check(attempt.stop==ps::Stop::resource_limit && !attempt.selection && fixture.account().statistics().current==before,"selection exhausted admission escaped its original account");
  }
}
void native_input_admission(const c02_test::Fixture& f,const planner::CandidateSnapshot& candidates,bool indexed) {
  const ps::Source invalid=ps::PhysicalBasis{CompiledProgram{}};const auto wanted=request(Case::height);
  ps::Attempt pure;std::size_t calls=0;
  {s04_alloc::Scope none(0);pure=ps::select(candidates,invalid,wanted);calls=s04_alloc::calls;}
  check(calls==0 && pure.stop==ps::Stop::invalid_handle && pure.stage==ps::Stage::admission && !pure.selection,
      "empty native compiler input allocated a component account or escaped invalid-handle admission");
  for(const auto kind:{Kind::physical,Kind::delta,Kind::session}) {
    Fixture fixture(f,candidates,indexed,kind,SourceKind::direct,Case::height,Cache::hit,allowance);
    fixture.source=invalid;const auto account=fixture.account();const auto before=account.statistics().current;const auto cached=fixture.cache.statistics();rs::Attempt attempt;
    {s04_alloc::Scope none(0);attempt=fixture.select();calls=s04_alloc::calls;}
    check(calls==0 && attempt.stop==ps::Stop::invalid_handle && attempt.stage==ps::Stage::admission && !attempt.selection,
        "empty native current input began capture or escaped invalid-handle admission");
    {s04_alloc::Scope none(0);pure=ps::select(candidates,invalid,wanted,fixture.previous->capture().inputs());calls=s04_alloc::calls;}
    check(calls==0 && pure.stop==ps::Stop::invalid_handle && pure.stage==ps::Stage::admission && !pure.selection,
        "empty native as-of input allocated or escaped invalid-handle admission");
    check(account.statistics().current==before && fixture.cache.statistics()==cached,"invalid native input changed original query or cache storage");
    verify(*fixture.previous,account,Case::height);fixture.stable();
  }
}
}
int main(int argc,char** argv) {
  try {
    const bool admission_only=argc==2 && std::string_view(argv[1])=="--admission-only";
    check(argc==1 || admission_only,"unknown selection memory test argument");
    const auto f=c02_test::fixture();const auto candidates=c02_test::candidates(f);
    for(const bool indexed:{false,true}) {
      native_input_admission(f,candidates,indexed);
      if(admission_only)continue;
      session_phases(f,candidates,indexed);
      for(const auto kind:{Kind::physical,Kind::delta,Kind::session})for(const auto source:{SourceKind::direct,SourceKind::compiler,SourceKind::native})
          for(const auto policy:{Case::height,Case::depth,Case::slots,Case::constrained_depth})for(const auto cache:{Cache::bypass,Cache::disabled,Cache::miss,Cache::hit}) {
        const auto make=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,kind,source,policy,cache,cap);};requests_and_lifetime(make,policy);
      }
      for(const auto policy:{Case::height,Case::depth,Case::slots,Case::constrained_depth}) {
        const auto kind=policy==Case::depth?Kind::delta:policy==Case::slots?Kind::session:Kind::physical;
        const auto source=policy==Case::depth?SourceKind::compiler:policy==Case::slots?SourceKind::native:SourceKind::direct;
        const auto cache=policy==Case::height?Cache::bypass:policy==Case::slots?Cache::hit:Cache::evict;
        const auto make=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,kind,source,policy,cache,cap);};const auto faults=persistent(make,policy);
        const auto no_cache=[&](std::uint64_t cap){return Fixture(f,candidates,indexed,kind,source,policy,Cache::bypass,cap);};const auto [peak,pins]=caps(no_cache,policy);
        std::cout<<(indexed?"indexed":"reference")<<" selection policy="<<static_cast<int>(policy)<<" faults="<<faults<<" peak="<<peak<<" pins="<<pins<<'\n';
      }
    }
    if(admission_only){std::cout<<"empty native compiler/current/as-of inputs reject before allocation and preserve query/cache ownership\n";return 0;}
    std::cout<<"native selection/current/source/request/assessments/decisions/cache/program: original requests, caps, persistent failures and retained lifetimes passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

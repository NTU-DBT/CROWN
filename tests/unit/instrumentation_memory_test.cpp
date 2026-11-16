#include "crown/runtime/session.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace ws=crown::runtime::workload;
namespace {
constexpr resource::MemoryAttribution observation_owner{resource::MemoryOwnerKind::observation,0};
constexpr resource::MemoryAttribution workload_owner{resource::MemoryOwnerKind::observation,1};
constexpr resource::MemoryAttribution snapshot_owner{resource::MemoryOwnerKind::capture,1};
void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message));}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto state=account.statistics().current;
  check(state.allocations==1 && state.requested_bytes==resource::MemoryAccount::control_bytes(),"instrumentation/snapshot retained storage after final release");
}
PhysicalPlan plan(bool indexed) {
  Catalog catalog{1,{}};Query query{{{"x",ScalarType::int64}},{},{{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{},{},{}};
  for(std::size_t i=0;i<12;++i) {
    const auto name="a"+std::to_string(i);catalog.tables.push_back({"r"+std::to_string(i),{{"x",ScalarType::int64}}});
    query.atoms.push_back({name,TableId{i},{VariableId{0}}});
    tree.nodes.push_back({name,NodeKind::native,{VariableId{0}},{},i,{}});
    if(i)tree.nodes[0].children.push_back(NodeId{i});
  }
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
DeltaOptions options(std::uint64_t cap=64*1024*1024,ObservationMode mode=ObservationMode::counters) {
  DeltaOptions result;result.physical.support.memory_limit_bytes=cap;result.physical.support.capture_transitions=false;
  result.physical.support.observation={mode,8192,1,0,false};return result;
}
ws::Options enabled(std::uint64_t period=1) {ws::Options value;value.mode=ws::Mode::counters;value.period=period;return value;}
void accept(DeltaRuntime& runtime,std::uint64_t sequence) {
  const PhysicalSetUpdate input{sequence,TableId{0},SetOperation::insert,{static_cast<std::int64_t>(sequence)}};
  auto pending=runtime.begin(input);pending.drain();
  {s04_alloc::Scope none(0);auto epoch=pending.commit();epoch.discard();}
}
bool same(const ws::Snapshot& a,const ws::Snapshot& b) {
  return a.options()==b.options() && a.modes()==b.modes() && a.previous_modes()==b.previous_modes() &&
      a.stamp().owner==b.stamp().owner && a.stamp().committed_epoch==b.stamp().committed_epoch &&
      a.stamp().reset_generation==b.stamp().reset_generation && a.stamp().configuration_generation==b.stamp().configuration_generation &&
      a.stamp().segment==b.stamp().segment && a.pending()==b.pending() && a.has_previous()==b.has_previous() && a.replaced_history()==b.replaced_history() &&
      a.metadata().attempts==b.metadata().attempts && a.metadata().committed==b.metadata().committed && a.metadata().aborted==b.metadata().aborted &&
      a.metadata().detail_actions==b.metadata().detail_actions && a.metadata().cleared_cells==b.metadata().cleared_cells &&
      a.previous_metadata().committed==b.previous_metadata().committed &&
      std::equal(a.descriptors().begin(),a.descriptors().end(),b.descriptors().begin(),b.descriptors().end()) &&
      std::equal(a.cells().begin(),a.cells().end(),b.cells().begin(),b.cells().end()) &&
      std::equal(a.previous_cells().begin(),a.previous_cells().end(),b.previous_cells().begin(),b.previous_cells().end());
}
void observer_requests_limits_and_failures() {
  std::uint64_t trace_peak=0,counter_bytes=0,trace_bytes=0;
  for(const auto mode:{ObservationMode::off,ObservationMode::counters,ObservationMode::timed,ObservationMode::trace}) {
    const auto account=resource::MemoryAccount::create(64*1024*1024);const auto before=account.statistics();std::shared_ptr<crown::runtime::detail::ObservationState> state;std::size_t calls=0;
    {s04_alloc::Scope count;state=crown::runtime::detail::ObservationState::create(account,{mode,8192,1,0,false});calls=s04_alloc::calls;}
    const auto after=account.statistics();const auto owned=account.statistics_for(observation_owner).current;
    check(calls==after.successful_allocations-before.successful_allocations && owned.requested_bytes==after.current.requested_bytes-before.current.requested_bytes,
        "observation object/control/trace capacity allocated outside its account");
    check(owned.allocations==(mode==ObservationMode::off?0U:mode==ObservationMode::trace?2U:1U),"observation mode allocated the wrong actual blocks");
    if(mode==ObservationMode::counters)counter_bytes=owned.requested_bytes;
    if(mode==ObservationMode::trace){trace_bytes=owned.requested_bytes;trace_peak=after.peak_requested_bytes;}
    if(state) {
      s04_alloc::Scope none(0);const auto ticket=state->begin(ObservationLayer::support,1);
      for(std::size_t i=0;i<9000;++i)state->event(TraceKind::source_change,i);
      state->finish(ticket,ObservationOutcome::committed);
      const auto report=state->snapshot();if(mode==ObservationMode::trace)check(report.trace_records==8192 && report.trace_truncated,"trace grew beyond its admitted native capacity");
      state.reset();
    }
    controller_only(account);
  }
  check(trace_bytes-counter_bytes==resource::MemoryAccount::allocation_bytes(8192*sizeof(TraceRecord),alignof(TraceRecord)),"trace capacity charge is not its real framed request");
  for(const bool exact:{true,false}) {
    const auto account=resource::MemoryAccount::create(exact?trace_peak:trace_peak-1);bool denied=false;
    try{auto state=crown::runtime::detail::ObservationState::create(account,{ObservationMode::trace,8192,1,0,false});check(exact,"short trace cap was accepted");}
    catch(const resource::MemoryFailure& error){check(!exact && error.fault()==resource::MemoryFault::limit,"wrong trace cap error");denied=true;}
    check(denied!=exact,"trace exact/one-under boundary changed");controller_only(account);
    auto smaller=crown::runtime::detail::ObservationState::create(account,{ObservationMode::trace,16,1,0,false});
    {s04_alloc::Scope none(0);smaller.reset();}controller_only(account);
  }
  std::size_t failures=0;
  for(std::ptrdiff_t point=0;point<16;++point) {
    const auto account=resource::MemoryAccount::create(64*1024*1024);std::shared_ptr<crown::runtime::detail::ObservationState> state;bool failed=false;
    {s04_alloc::Scope fault(point);try{state=crown::runtime::detail::ObservationState::create(account,{ObservationMode::trace,8192,1,0,false});}catch(const std::bad_alloc&){failed=true;}}
    if(failed){++failures;controller_only(account);}else{state.reset();controller_only(account);break;}
  }
  check(failures==2,"observation constructor fault sweep missed control or trace capacity");
  std::cout<<"observation native requests="<<trace_bytes<<" exact/one-under peak="<<trace_peak<<" persistent faults="<<failures<<'\n';
}
void actual_runtime_requests_and_lifetimes(bool indexed) {
  resource::MemoryAccount account;std::optional<ws::Snapshot> held,pending_copy;
  {
    DeltaRuntime runtime(plan(indexed),options(64*1024*1024,ObservationMode::trace));account=runtime.plan().account();
    check(account.statistics_for(observation_owner).current.allocations==2,"actual query observation owner is unfunded");
    auto before=account.statistics();std::size_t calls=0;
    {s04_alloc::Scope count;runtime.configure_workload_statistics(enabled());calls=s04_alloc::calls;}
    const auto working=account.statistics_for(workload_owner).current;
    check(calls>0 && calls==account.statistics().successful_allocations-before.successful_allocations && working.allocations==5 &&
        account.statistics().current.requested_bytes-before.current.requested_bytes==working.requested_bytes,
        "workload configuration/retained routes/descriptor/cell arrays allocated outside the original grant");
    accept(runtime,1);before=account.statistics();
    {s04_alloc::Scope count;held.emplace(runtime.workload_statistics());calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before.successful_allocations && calls==4 &&
        held->plan().account().statistics().owner==account.statistics().owner &&
        account.statistics_for(workload_owner).current.payload_bytes==held->memory().retained_payload_bytes,
        "workload snapshot control/arrays or component payload totals do not reconcile with native requests");
    before=account.statistics();
    {s04_alloc::Scope count;pending_copy.emplace(runtime.workload_statistics());calls=s04_alloc::calls;}
    check(calls==4 && calls==account.statistics().successful_allocations-before.successful_allocations &&
        !pending_copy->pending() && !held->pending() && account.statistics_for(snapshot_owner).current.allocations==8,
        "pending workload snapshot hid ordinary copies or changed the original snapshot");
    const auto saved=held->stamp().committed_epoch;accept(runtime,2);
    check(held->stamp().committed_epoch==saved && held->metadata().committed==1,"immutable workload snapshot changed with its runtime");
    {s04_alloc::Scope none(0);runtime.reset_workload_statistics();}
    runtime.configure_workload_statistics({});check(account.statistics_for(workload_owner).current.allocations==0,"off workload retained native capacity");
  }
  check(held->metadata().committed==1 && !pending_copy->pending() && held->plan().account().statistics().owner==account.statistics().owner,
      "retained workload snapshot lost native data after runtime destruction");
  {s04_alloc::Scope none(0);held.reset();pending_copy.reset();}controller_only(account);
}
void cap_and_persistent_failures(bool indexed) {
  for(const bool copying:{false,true}) {
    std::uint64_t peak=0;
    {
      DeltaRuntime runtime(plan(indexed),options());runtime.configure_workload_statistics(enabled());accept(runtime,1);
      const auto held=runtime.workload_statistics();const auto before=runtime.plan().account().statistics().peak_requested_bytes;
      if(copying){auto candidate=runtime.workload_statistics();}else runtime.configure_workload_statistics(enabled(3));
      peak=runtime.plan().account().statistics().peak_requested_bytes;check(peak>before,"instrumentation fixture did not exceed prior setup peak");
    }
    for(const bool exact:{true,false}) {
      DeltaRuntime runtime(plan(indexed),options(exact?peak:peak-1));const auto account=runtime.plan().account();runtime.configure_workload_statistics(enabled());accept(runtime,1);
      const auto held=runtime.workload_statistics();const auto baseline=account.statistics().current;bool denied=false;
      try{if(copying){auto candidate=runtime.workload_statistics();}else runtime.configure_workload_statistics(enabled(3));}
      catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong workload query cap error");denied=true;}
      check(denied!=exact && runtime.sequence()==1 && held.metadata().committed==1,"workload query cap changed prior accepted epoch");
      if(!exact) {
        // A second capture has the same byte frontier as with_pending. At the
        // denied copy boundary, inspect the retained value/fixed runtime fields;
        // the ample-budget persistent sweep below also compares a fresh capture.
        check(account.statistics().current==baseline && !held.pending() && runtime.workload_statistics_options()==enabled() &&
            (copying || same(runtime.workload_statistics(),held)),"failed native workload operation changed old data or leaked capacity");
        {s04_alloc::Scope none(0);runtime.reset_workload_statistics();}
        check(runtime.sequence()==1 && account.statistics().limit_bytes==peak-1,"workload failure recovery replaced the query grant");
      }
    }
    std::size_t failures=0;bool complete=false;
    for(std::ptrdiff_t point=0;point<128;++point) {
      DeltaRuntime runtime(plan(indexed),options());runtime.configure_workload_statistics(enabled());accept(runtime,1);const auto account=runtime.plan().account();
      const auto held=runtime.workload_statistics();const auto baseline=account.statistics().current;std::optional<ws::Snapshot> output;bool failed=false;
      {s04_alloc::Scope fault(point);try{if(copying)output.emplace(runtime.workload_statistics());else runtime.configure_workload_statistics(enabled(3));}catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;check(account.statistics().current==baseline && same(runtime.workload_statistics(),held) && runtime.sequence()==1,
            "persistent native workload failure changed configuration/history or leaked tentative storage");
        if(copying)output.emplace(runtime.workload_statistics());else runtime.configure_workload_statistics(enabled(3));
      }else complete=true;
      account.check_invariants();if(complete)break;
    }
    check(complete && failures==(copying?4U:6U),"native workload fault sweep missed candidate or retained allocations");
    std::cout<<(indexed?"indexed":"reference")<<" workload phase="<<(copying?"snapshot-capture":"reconfigure")<<" exact/one-under peak="<<peak<<" persistent faults="<<failures<<'\n';
  }
}
QuerySession::Owner pending_session(bool indexed,std::uint64_t cap=64*1024*1024) {
  SessionOptions config;config.delta=options(cap);auto session=QuerySession::create_typed(plan(indexed),io::QueueLimits{},config);
  session->configure_workload_statistics(enabled());
  io::TransportBatch offered({io::InputEvent{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},{}}});
  check(session->enqueue(offered)==io::Admission::accepted,"pending workload session input was refused");session->start();
  check(session->begin_next(),"pending workload session failed to begin");return session;
}
void pending_session_capture(bool indexed) {
  std::uint64_t peak=0;
  {
    auto session=pending_session(indexed);const auto account=session.get_deleter().account();const auto before=account.statistics();
    std::optional<ws::Snapshot> held;std::size_t calls=0;
    {s04_alloc::Scope count;held=session->workload_statistics();calls=s04_alloc::calls;}
    check(held && held->pending() && calls==8 && calls==account.statistics().successful_allocations-before.successful_allocations &&
        account.statistics_for(snapshot_owner).current.allocations==4,"public pending capture did not fund its temporary and copied snapshot graph");
    peak=account.statistics().peak_requested_bytes;check(peak>before.peak_requested_bytes,"pending capture fixture did not exceed setup peak");
  }
  for(const bool exact:{true,false}) {
    auto session=pending_session(indexed,exact?peak:peak-1);const auto account=session.get_deleter().account();const auto baseline=account.statistics().current;
    std::optional<ws::Snapshot> held;bool denied=false;
    try{held=session->workload_statistics();}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong pending capture query cap error");denied=true;}
    check(denied!=exact && session->status().committed_sequence==0 && session->progress().sequence==0,"pending capture cap accepted private input");
    if(!exact)check(!held && account.statistics().current==baseline,"denied pending capture leaked partial snapshots");
    {s04_alloc::Scope none(0);session->drop();session.reset();}
    if(held)check(held->pending() && held->stamp().committed_epoch==0 && held->plan().account().statistics().owner==account.statistics().owner,
        "pending snapshot lost native data after dropped session");
    {s04_alloc::Scope none(0);held.reset();}controller_only(account);
  }
  std::size_t failures=0;bool complete=false;
  for(std::ptrdiff_t point=0;point<32;++point) {
    auto session=pending_session(indexed);const auto account=session.get_deleter().account();const auto baseline=account.statistics().current;
    std::optional<ws::Snapshot> held;bool failed=false;
    {s04_alloc::Scope fault(point);try{held=session->workload_statistics();}catch(const std::bad_alloc&){failed=true;}}
    if(failed) {
      ++failures;check(!held && account.statistics().current==baseline && session->status().committed_sequence==0 && session->progress().sequence==0,
          "pending snapshot failure changed accepted progress or leaked tentative native copies");held=session->workload_statistics();
    }else complete=true;
    check(held && held->pending(),"pending snapshot retry lost its private-work flag");
    {s04_alloc::Scope none(0);session->drop();session.reset();held.reset();}controller_only(account);if(complete)break;
  }
  check(complete && failures==8,"public pending capture fault sweep missed initial or copied native snapshot");
  std::cout<<(indexed?"indexed":"reference")<<" pending-session snapshot exact/one-under peak="<<peak<<" persistent faults="<<failures<<'\n';
}
} // namespace
int main() {
  try{observer_requests_limits_and_failures();for(const bool indexed:{false,true}){actual_runtime_requests_and_lifetimes(indexed);cap_and_persistent_failures(indexed);pending_session_capture(indexed);}
    std::cout<<"native instrumentation: actual original grants/requests, caps, retained snapshots, nonallocating hooks and persistent failures passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"
#include "crown/runtime/session.hpp"
#include "crown/io/support.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>
#include <type_traits>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool value,std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template<class F> void denied(F&& operation) {
  try { operation(); }
  catch (const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"unexpected memory rejection");return;
  }
  throw std::runtime_error("expected actual account byte-limit denial");
}
PhysicalPlan plan(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},
      {"s",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Row parent(std::size_t i) { return {std::string(100,'x')+std::to_string(i),std::int64_t{42}}; }
Row child() { return {std::int64_t{42}}; }
void populate(SupportRuntime& runtime) {
  static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,parent(1)}));
  static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,parent(2)}));
}
void populate(PhysicalRuntime& runtime) {
  static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,parent(1)}));
  static_cast<void>(runtime.apply({2,TableId{0},SetOperation::insert,parent(2)}));
}
void reconcile(const resource::MemoryAccount& account) {
  account.check_invariants();
  const auto stats=account.statistics();resource::MemoryUsage purposes{},lifetimes{};
  const auto add=[](auto& a,const auto& b) {
    a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;
  };
  for (const auto& usage:stats.by_purpose) add(purposes,usage);
  for (const auto& usage:stats.by_lifetime) add(lifetimes,usage);
  check(purposes==stats.current && lifetimes==stats.current,"routed bytes do not reconcile");
  check(stats.current.requested_bytes<=stats.limit_bytes && stats.peak_requested_bytes<=stats.limit_bytes,
      "actual runtime exceeded its finite account");
}
void exact_epoch(bool indexed) {
  const auto compiled=plan(indexed);std::uint64_t peak=0,setup_peak=0;
  {
    SupportRuntime golden(compiled);populate(golden);setup_peak=golden.accounted_memory_statistics().peak_requested_bytes;
    static_cast<void>(golden.apply({3,NodeId{1},SetOperation::insert,child()}));
    peak=golden.accounted_memory_statistics().peak_requested_bytes;
    check(peak>setup_peak,"crossing must exceed the setup peak");
  }
  SupportOptions options;options.memory_limit_bytes=peak;
  {
    SupportRuntime exact(compiled,options);populate(exact);
    static_cast<void>(exact.apply({3,NodeId{1},SetOperation::insert,child()}));
    check(exact.sequence()==3 && exact.has_answer() && exact.accounted_memory_statistics().peak_requested_bytes==peak,
        "exact real epoch peak was not admitted");
    reconcile(RuntimeTestProbe::memory_account(exact));
  }
  --options.memory_limit_bytes;
  SupportRuntime limited(compiled,options);populate(limited);const auto before=limited.canonical_state();
  const auto before_statistics=limited.accounted_memory_statistics();
  const auto bytes=before_statistics.current;
  denied([&] { static_cast<void>(limited.apply({3,NodeId{1},SetOperation::insert,child()})); });
  check(limited.ready() && limited.canonical_state()==before,"byte denial did not restore the previous epoch");
  // Native tables may keep admitted arena/directory capacity after rollback.
  // Payloads and pins must return to the committed state; retained capacity
  // remains actually charged and is tested for bounded reuse below.
  const auto arena=limited.storage_statistics();
  check(limited.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::tuple_values)]==
      before_statistics.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::tuple_values)],"byte rollback leaked compact payload allocations");
  check(arena.retained_records==0 && arena.pins==0,"byte denial retained native rows or journal pins");
  check(limited.accounted_memory_statistics().current.requested_bytes>=bytes.requested_bytes,
      "rollback unexpectedly lost committed metadata ownership");
  static_cast<void>(limited.apply({3,NodeId{1},SetOperation::erase,child()}));
  check(limited.sequence()==3 && !limited.has_answer(),"valid no-op retry after byte denial failed");
  reconcile(RuntimeTestProbe::memory_account(limited));
  std::cout<<(indexed?"indexed":"reference")<<" real support peak="<<peak<<"; exact/one-under rollback and retry passed\n";
}
void undo_and_churn(bool indexed) {
  SupportRuntime runtime(plan(indexed));const auto empty=runtime.accounted_memory_statistics().current;
  populate(runtime);static_cast<void>(runtime.apply({3,NodeId{1},SetOperation::insert,child()}));
  const auto before=runtime.canonical_state();const auto bytes=runtime.accounted_memory_statistics().current;
  const auto account=RuntimeTestProbe::memory_account(runtime);
  {
  auto pending=runtime.begin_epoch(4,SetOperation::erase);
  check(pending.stage(NodeId{1},child()),"deletion fixture did not change state");
  check(account.statistics().by_lifetime[static_cast<std::size_t>(resource::AllocationLifetime::retained)].requested_bytes>0,
      "undo flags/nodes were not classified as retained");
  {
    s04_alloc::Scope fail_every_allocation(0);pending.rollback();
    check(s04_alloc::calls==0,"rollback allocated while restoring funded nodes or child flags");
  }
  check(runtime.canonical_state()==before,"rollback changed the previous epoch");
  // A closed pending token may retain its original lease until destruction.
  }
  check(account.statistics().current.requested_bytes>=bytes.requested_bytes,"destroying the closed token lost committed metadata");
  reconcile(account);
  static_cast<void>(runtime.apply({4,NodeId{1},SetOperation::erase,child()}));
  static_cast<void>(runtime.apply({5,NodeId{0},SetOperation::erase,parent(1)}));
  static_cast<void>(runtime.apply({6,NodeId{0},SetOperation::erase,parent(2)}));
  const auto warm_empty=account.statistics().current;
  check(warm_empty.requested_bytes>=empty.requested_bytes,"native teardown lost immutable metadata");
  std::uint64_t sequence=6;
  for (std::size_t i=0;i<40;++i) {
    static_cast<void>(runtime.apply({++sequence,NodeId{0},SetOperation::insert,parent(1)}));
    const auto live=account.statistics().current;
    static_cast<void>(runtime.apply({++sequence,NodeId{0},SetOperation::insert,parent(1)}));
    check(account.statistics().current==live,"duplicate insert retained routed allocations");
    static_cast<void>(runtime.apply({++sequence,NodeId{0},SetOperation::erase,parent(1)}));
    check(account.statistics().current==warm_empty,"churn leaked routed metadata beyond reusable native capacity");
  }
}
void retained_owners(bool indexed) {
  resource::MemoryAccount account;std::shared_ptr<const SupportJournal> journal;
  std::optional<SupportRuntime::ResultCursor> cursor;
  {
    SupportRuntime runtime(plan(indexed));account=RuntimeTestProbe::memory_account(runtime);
    populate(runtime);auto epoch=runtime.apply({3,NodeId{1},SetOperation::insert,child()});journal=epoch.journal;
    cursor.emplace(runtime.results());
  }
  check(account.statistics().current.allocations>1,"retained cursor lost query ownership");
  check(cursor->next().has_value(),"retained cursor cannot read after facade destruction");
  cursor.reset();
  check(account.statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::journal_undo)].requested_bytes>0,
      "retained public journal released its actual control too early");
  journal.reset();reconcile(account);
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes() &&
      account.statistics().current.allocations==1,"final owners did not release routed bytes");
}
void cursor_limits(bool indexed) {
  const auto compiled=plan(indexed);std::uint64_t peak=0;
  {
    SupportRuntime golden(compiled);const auto startup=golden.accounted_memory_statistics().peak_requested_bytes;
    std::vector<SupportRuntime::ResultCursor> cursors;cursors.reserve(4);
    for (int i=0;i<4;++i) cursors.push_back(golden.results());
    peak=golden.accounted_memory_statistics().peak_requested_bytes;
    check(peak>startup,"concurrent cursors must exceed the constructor peak");
  }
  SupportOptions options;options.memory_limit_bytes=peak;
  {
    SupportRuntime exact(compiled,options);std::vector<SupportRuntime::ResultCursor> cursors;cursors.reserve(4);
    for (int i=0;i<4;++i) cursors.push_back(exact.results());
    check(exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact cursor peak was not admitted");
    reconcile(RuntimeTestProbe::memory_account(exact));
  }
  --options.memory_limit_bytes;SupportRuntime limited(compiled,options);const auto before=limited.canonical_state();
  {
    std::vector<SupportRuntime::ResultCursor> cursors;cursors.reserve(3);
    for (int i=0;i<3;++i) cursors.push_back(limited.results());
    const auto bytes=limited.accounted_memory_statistics().current;
    denied([&] { static_cast<void>(limited.results()); });
    check(limited.accounted_memory_statistics().current==bytes,"failed cursor startup leaked funded control/frame bytes");
    for (const auto& cursor:cursors) check(cursor.active(),"failed cursor startup invalidated an existing read lease");
  }
  check(limited.ready() && limited.canonical_state()==before,"cursor byte denial changed the runtime or kept a read lease");
  { auto retry=limited.results();check(retry.active(),"smaller cursor retry after denial failed"); }
  check(limited.ready(),"cursor retry failed to release its lease");
  reconcile(RuntimeTestProbe::memory_account(limited));
  std::cout<<(indexed?"indexed":"reference")<<" funded cursor peak="<<peak<<"; exact/one-under, existing leases and smaller retry passed\n";
}
std::string binary_binding() { auto value=std::string(8192,'b');value.append("\0\xff",2);return value; }
void binding_limits(bool indexed) {
  const auto compiled=plan(indexed);const auto binary=binary_binding();
  const FixedAssignment fixed{{VariableId{0},binary}};std::uint64_t peak=0;
  {
    SupportRuntime golden(compiled);const auto before=golden.accounted_memory_statistics();
    auto cursor=golden.completions(fixed);const auto after=golden.accounted_memory_statistics();
    peak=after.peak_requested_bytes;
    check(peak>before.peak_requested_bytes,"binary binding must exceed the empty runtime peak");
    const auto payload=static_cast<std::size_t>(resource::MemoryPurpose::tuple_values);
    check(after.by_purpose[payload].requested_bytes-before.by_purpose[payload].requested_bytes>=binary.size(),
        "binary binding payload was not charged to the query account");
  }
  SupportOptions options;options.memory_limit_bytes=peak;
  {
    SupportRuntime exact(compiled,options);auto cursor=exact.completions(fixed);
    check(exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact binding peak was not admitted");
    reconcile(RuntimeTestProbe::memory_account(exact));
  }
  --options.memory_limit_bytes;SupportRuntime limited(compiled,options);
  const auto before=limited.canonical_state();const auto bytes=limited.accounted_memory_statistics().current;
  denied([&] {static_cast<void>(limited.completions(fixed));});
  check(limited.ready() && limited.accounted_memory_statistics().current==bytes && limited.canonical_state()==before,
      "denied binding startup leaked bytes, changed state or retained its view lease");
  {auto retry=limited.completions({{VariableId{0},std::string("short")}});check(retry.active(),"smaller binding retry failed");}
  check(limited.ready(),"binding retry retained its read lease");reconcile(RuntimeTestProbe::memory_account(limited));
  resource::MemoryAccount retained_account;std::optional<SupportRuntime::ResultCursor> retained;
  {
    SupportRuntime runtime(compiled);retained_account=RuntimeTestProbe::memory_account(runtime);
    static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,{binary,std::int64_t{42}}}));
    static_cast<void>(runtime.apply({2,NodeId{1},SetOperation::insert,child()}));
    retained.emplace(runtime.completions({{VariableId{0},std::string(binary)}}));
  }
  auto result=retained->next();check(result && result->values()==Row{binary},"fixed binary value did not survive input/facade destruction");
  retained.reset();reconcile(retained_account);
  check(retained_account.statistics().current.requested_bytes>resource::MemoryAccount::control_bytes() &&
      result->layout().fields().size()==1 && result->values()==Row{binary},
      "returned binding result did not retain its accounted layout after cursor destruction");
  result.reset();reconcile(retained_account);
  check(retained_account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "last binding cursor did not release its funded values and view");
  std::cout<<(indexed?"indexed":"reference")<<" funded binary binding peak="<<peak<<"; exact/one-under, smaller retry and retained bytes passed\n";
}
PhysicalPlan overlay_plan(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},{"s",{{"x",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{0}}}},{{VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{0}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
void overlay_limits(bool indexed) {
  const auto compiled=overlay_plan(indexed);const auto binary=binary_binding();const Row input{binary,std::int64_t{42}};
  const auto seed=[&](SupportRuntime& runtime) {
    static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,input}));
    static_cast<void>(runtime.apply({2,NodeId{1},SetOperation::insert,{binary}}));
  };
  std::uint64_t peak=0;
  {
    SupportRuntime golden(compiled);seed(golden);auto pending=golden.begin_epoch(3,SetOperation::erase);
    check(pending.stage(NodeId{0},input),"overlay fixture did not erase the root");
    const auto before=golden.accounted_memory_statistics();auto view=pending.view(SnapshotSide::before);
    const auto after=golden.accounted_memory_statistics();peak=after.peak_requested_bytes;
    check(peak>before.peak_requested_bytes && view.metrics().restored_bucket_entries>0,
        "overlay fixture did not cross its setup peak with an indexed restored bucket");
    const auto payload=static_cast<std::size_t>(resource::MemoryPurpose::tuple_values);
    check(after.by_purpose[payload].requested_bytes-before.by_purpose[payload].requested_bytes>=3*binary.size(),
        "full-key and nested index-key binary overlay copies were not charged");
    check(view.has_answer(),"before overlay lost the pre-delete answer");
  }
  SupportOptions options;options.memory_limit_bytes=peak;
  {
    SupportRuntime exact(compiled,options);seed(exact);auto pending=exact.begin_epoch(3,SetOperation::erase);
    check(pending.stage(NodeId{0},input),"exact overlay fixture failed to stage");auto view=pending.view(SnapshotSide::before);
    check(view.has_answer() && exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact overlay peak was not admitted");
    reconcile(RuntimeTestProbe::memory_account(exact));
  }
  --options.memory_limit_bytes;SupportRuntime limited(compiled,options);seed(limited);const auto before=limited.canonical_state();
  auto pending=limited.begin_epoch(3,SetOperation::erase);check(pending.stage(NodeId{0},input),"limited overlay fixture failed to stage");
  const auto bytes=limited.accounted_memory_statistics().current;
  denied([&] {static_cast<void>(pending.view(SnapshotSide::before));});
  check(pending.active() && !pending.preview().has_answer && limited.accounted_memory_statistics().current==bytes,
      "denied overlay construction changed its prepared epoch or leaked keys/map nodes");
  {s04_alloc::Scope fault(0);pending.rollback();check(s04_alloc::calls==0,"overlay denial rollback allocated");}
  check(limited.ready() && limited.canonical_state()==before,"overlay denial rollback changed the previous epoch");
  {auto retry=limited.current_view();check(retry.valid() && retry.has_answer(),"smaller view retry failed after overlay denial");}
  check(limited.ready(),"smaller view retry retained a lease");reconcile(RuntimeTestProbe::memory_account(limited));
  resource::MemoryAccount retained_account;std::optional<SupportRuntime::EpochView> retained_view;
  std::optional<SupportRuntime::ResultCursor> witness,completion;
  {
    SupportRuntime runtime(compiled);retained_account=RuntimeTestProbe::memory_account(runtime);seed(runtime);
    auto update=runtime.begin_epoch(3,SetOperation::erase);check(update.stage(NodeId{0},input),"retained overlay fixture failed to stage");
    retained_view.emplace(update.view(SnapshotSide::before));static_cast<void>(update.commit());
    witness.emplace(retained_view->witnesses({{VariableId{0},std::string(binary)},{VariableId{1},std::int64_t{42}}}));
    completion.emplace(retained_view->completions({{VariableId{0},std::string(binary)}}));
  }
  check(retained_view->valid() && !retained_view->tentative(),"committed overlay did not survive its facade");
  auto full=witness->next(),projected=completion->next();
  check(full && full->values()==input && projected && projected->values()==Row{std::int64_t{42}},
      "retained ghost/direct lookup lost binary overlay keys or fixed values");
  witness.reset();completion.reset();retained_view.reset();reconcile(retained_account);
  check(retained_account.statistics().current.requested_bytes>resource::MemoryAccount::control_bytes() &&
      full->layout().fields().size()==2 && projected->layout().fields().size()==1,
      "returned overlay results did not retain their accounted layouts");
  full.reset();projected.reset();reconcile(retained_account);
  check(retained_account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "final overlay/binding owners did not release their funded bytes");
  std::cout<<(indexed?"indexed":"reference")<<" funded overlay peak="<<peak<<"; exact/one-under, allocation-free rollback and retained binary lookups passed\n";
}
void persistent_faults(bool indexed) {
  const auto compiled=plan(indexed);std::size_t positions=0;
  for (std::ptrdiff_t fail=0;fail<2000;++fail) {
    SupportRuntime runtime(compiled);populate(runtime);const auto before=runtime.canonical_state();
    const auto before_statistics=runtime.accounted_memory_statistics();const auto bytes=before_statistics.current;bool failed=false,triggered=false;
    {
      s04_alloc::Scope fault(fail);
      try { static_cast<void>(runtime.apply({3,NodeId{1},SetOperation::insert,child()})); }
      catch (const std::bad_alloc&) { failed=true; }
      triggered=s04_alloc::triggered;
    }
    if (!triggered) { check(!failed && runtime.sequence()==3,"fault sweep ended without a committed epoch");break; }
    ++positions;
    check(runtime.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::tuple_values)]==before_statistics.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::tuple_values)],"persistent failure leaked compact payload bytes");
    check(failed && runtime.ready() && runtime.canonical_state()==before && runtime.accounted_memory_statistics().current.requested_bytes>=bytes.requested_bytes,
        "persistent allocation failure changed prior state or retained routed metadata");
    static_cast<void>(runtime.apply({3,NodeId{1},SetOperation::insert,child()}));
    check(runtime.sequence()==3 && runtime.has_answer(),"allocation-failure retry failed");
    if (fail==1999) throw std::runtime_error("fault sweep did not terminate");
  }
  check(positions>20,"fault sweep did not cover the real propagation path");
  std::cout<<(indexed?"indexed":"reference")<<" persistent real epoch faults="<<positions<<"\n";
}
void rebuild_and_composition(bool indexed) {
  PhysicalRuntime physical(plan(indexed));populate(physical);
  const auto owner=physical.accounted_memory_statistics().owner;
  check(RuntimeTestProbe::support(physical).accounted_memory_statistics().owner==owner,"physical/support minted separate accounts");
  const auto before=physical.accounted_memory_statistics().current;
  {
    auto rebuilt=physical.rebuilt();
    check(rebuilt.accounted_memory_statistics().owner==owner &&
        physical.accounted_memory_statistics().current.requested_bytes>before.requested_bytes,
        "rebuild excluded old/new runtime overlap from the account");
    check(rebuilt.canonical_state()==physical.canonical_state(),"memory-owner migration changed rebuilt state");
  }
  check(physical.accounted_memory_statistics().current==before,"rebuilt owner leaked routed bytes");
  DeltaOptions options;options.mode=DeltaMode::delta;options.physical.support.memory_limit_bytes=1024*1024;
  DeltaRuntime delta(plan(indexed),options);
  const auto observation=delta.observations();
  check(observation.current_configuration &&
      observation.current_configuration->requested_options().physical.support.memory_limit_bytes==1024*1024,
      "observation configuration lost the requested finite memory limit");
  const auto compiled=plan(indexed);
  const io::Json trace{{"schema_version",1},{"options",io::write_support_options(options.physical.support)},{"updates",io::Json::array()}};
  check(io::read_support_trace(trace.dump(),compiled).options.memory_limit_bytes==1024*1024,
      "logical trace round trip lost the requested finite memory limit");
  auto& inner=RuntimeTestProbe::physical(delta);
  check(delta.accounted_memory_statistics().owner==inner.accounted_memory_statistics().owner,"delta minted a separate query account");
  const auto delta_owner=delta.accounted_memory_statistics().owner;
  auto rebuilt=delta.rebuilt();check(rebuilt.accounted_memory_statistics().owner==delta_owner,"delta rebuild replaced its memory account");
  SessionOptions session_options;session_options.delta.physical.support.memory_limit_bytes=1024*1024;
  auto session=QuerySession::create_typed(plan(indexed),{},session_options);
  const auto stats=session->accounted_memory_statistics();
  check(stats && stats->owner!=0 && stats->limit_bytes==1024*1024,"session did not forward the configured runtime account");
  session->stop();check(session->accounted_memory_statistics()->owner==stats->owner,"stop replaced the runtime memory owner");
  session->drop();check(!session->accounted_memory_statistics(),"drop still exposes a released runtime account");
}
PhysicalPlan payload_plan(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"payload",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
void compact_source_epoch(bool indexed) {
  const auto compiled=payload_plan(indexed);
  auto bytes=std::string(8192,'p');bytes.append("\0\xff",2);
  const Row large{std::int64_t{7},bytes},small{std::int64_t{7},std::string("short")};
  std::uint64_t peak=0;
  {
    PhysicalRuntime golden(compiled);
    auto epoch=golden.apply({1,TableId{0},SetOperation::insert,large});
    peak=golden.accounted_memory_statistics().peak_requested_bytes;
    static_assert(std::is_same_v<decltype(epoch.input.source->tuple()),const storage::AccountedTuple&>);
    check(epoch.input.source->tuple().values()==large,"compact pin lost ignored physical payload bytes");
  }
  PhysicalRuntimeOptions options;options.support.memory_limit_bytes=peak;
  {
    PhysicalRuntime exact(compiled,options);
    auto epoch=exact.apply({1,TableId{0},SetOperation::insert,large});
    check(exact.sequence()==1 && epoch.input.source->tuple().values()==large &&
        exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact compact source peak did not commit");
    const auto account=RuntimeTestProbe::memory_account(RuntimeTestProbe::support(exact));reconcile(account);
  }
  --options.support.memory_limit_bytes;
  {
    PhysicalRuntime limited(compiled,options);
    denied([&]{static_cast<void>(limited.apply({1,TableId{0},SetOperation::insert,large}));});
    const auto gauges=limited.committed_state_gauges();
    check(limited.ready() && limited.sequence()==0 && gauges.bases[0].tuples==0 && gauges.nodes[0].records==0 &&
        limited.derivation_count(OccurrenceId{0},{std::int64_t{7}})==0,"compact source denial changed the previous epoch");
    auto retry=limited.apply({1,TableId{0},SetOperation::insert,small});
    check(limited.sequence()==1 && retry.input.source->tuple().values()==small,"compact source denial prevented smaller retry");
    reconcile(RuntimeTestProbe::memory_account(RuntimeTestProbe::support(limited)));
  }
  resource::MemoryAccount account;std::optional<PhysicalEpoch> held;
  {
    PhysicalRuntime runtime(compiled);account=RuntimeTestProbe::memory_account(RuntimeTestProbe::support(runtime));
    held.emplace(runtime.apply({1,TableId{0},SetOperation::insert,large}));
    auto exported=runtime.get_source(TableId{0},held->input.source->handle);
    static_assert(std::is_same_v<decltype(exported),std::optional<storage::AccountedTuple>>);
    check(exported && exported->values()==large && exported->layout().account_statistics().owner==account.statistics().owner &&
        exported->attribution().kind==resource::MemoryOwnerKind::output,"owning source export escaped the query account");
    PhysicalRuntime other(compiled);bool foreign=false;
    try {static_cast<void>(other.get_source(TableId{0},held->input.source->handle));}
    catch(const Error& failure){check(failure.code()=="foreign_handle","wrong foreign source rejection");foreign=true;}
    check(foreign,"foreign compact source handle did not preserve the public error boundary");
  }
  check(held->input.source->tuple().values()==large && account.statistics().current.requested_bytes>bytes.size(),
      "retained compact pin lost its real payload or account after facade destruction");
  reconcile(account);held.reset();
  check(account.statistics().current.allocations==1 && account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "final source pin/journal release retained query allocations");
  std::cout<<(indexed?"indexed":"reference")<<" compact physical source peak="<<peak<<"; exact/one-under, smaller retry and retained payload passed\n";
}
void scalar_compatibility() {
  const Row values{std::int64_t{-9},std::string("a\0\xff",3),true,Date::parse("2000-02-29"),
      Decimal::parse("-12345678901234567890123456789012345678")};
  auto account=resource::MemoryAccount::create(65536);auto owned=storage::AccountedRow::copy_of(account,values);
  {
    s04_alloc::Scope no_allocation(0);
    check(owned.view()==values && values==owned.view() && (owned.view()<=>values)==0,
        "borrowed compact/legacy scalar comparison changed exact values");
    check(s04_alloc::calls==0,"borrowed row comparison allocated");
  }
  check(storage::export_row(owned.view())==values,"explicit scalar export changed exact or binary values");
}
void physical_persistent_faults(bool indexed) {
  const auto compiled=plan(indexed);
  const PhysicalSetUpdate update{3,TableId{1},SetOperation::insert,child()};
  std::size_t positions=0;
  for(std::ptrdiff_t fail=0;fail<3000;++fail) {
    PhysicalRuntime runtime(compiled);populate(runtime);const auto before=runtime.canonical_state();
    const auto account=RuntimeTestProbe::memory_account(RuntimeTestProbe::support(runtime));
    const auto first=*runtime.find_source(TableId{0},parent(1));
    const auto second=*runtime.find_source(TableId{0},parent(2));
    bool failed=false,triggered=false;
    {
      s04_alloc::Scope fault(fail);
      try{static_cast<void>(runtime.apply(update));}catch(const std::bad_alloc&){failed=true;}
      triggered=s04_alloc::triggered;
    }
    if(!triggered){check(!failed && runtime.sequence()==3,"physical fault sweep ended without commit");break;}
    ++positions;
    check(failed && runtime.ready() && runtime.canonical_state()==before,"physical allocation failure changed the previous epoch");
    const auto a=runtime.get_source(TableId{0},first),b=runtime.get_source(TableId{0},second);
    check(a && b && a->values()==parent(1) && b->values()==parent(2),"physical allocation failure changed a stable compact source handle");
    reconcile(account);
    auto retry=runtime.apply(update);
    check(runtime.sequence()==3 && runtime.has_answer() && retry.input.source && retry.input.source->handle.tuple.value==1,
        "physical allocation-failure retry lost tentative identity or native state");
    if(fail==2999)throw std::runtime_error("physical fault sweep did not terminate");
  }
  check(positions>40,"physical allocation sweep missed the composed route");
  std::cout<<(indexed?"indexed":"reference")<<" persistent compact physical epoch faults="<<positions<<"\n";
}
} // namespace
int main() {
  try {
    scalar_compatibility();
    for (bool indexed:{false,true}) {
      exact_epoch(indexed);undo_and_churn(indexed);retained_owners(indexed);cursor_limits(indexed);persistent_faults(indexed);rebuild_and_composition(indexed);
      binding_limits(indexed);overlay_limits(indexed);
      compact_source_epoch(indexed);
      physical_persistent_faults(indexed);
    }
    std::cout<<"actual compact support/source/overlay/binding memory passed; legacy plan, exported outputs/captures, delta and session coverage remains open\n";
    return 0;
  } catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n';return 1; }
}

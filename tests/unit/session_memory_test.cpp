#include "crown/api/error.hpp"
#include "crown/runtime/session.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
constexpr resource::MemoryAttribution session_owner{resource::MemoryOwnerKind::session,0};
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
resource::MemoryUsage plus(resource::MemoryUsage left,const resource::MemoryUsage& right) {
  left.allocations+=right.allocations;left.requested_bytes+=right.requested_bytes;left.payload_bytes+=right.payload_bytes;
  return left;
}
resource::MemoryUsage difference(const resource::MemoryUsage& left,const resource::MemoryUsage& right) {
  return {left.allocations-right.allocations,left.requested_bytes-right.requested_bytes,left.payload_bytes-right.payload_bytes};
}
void reconcile(const resource::MemoryAccount& account) {
  account.check_invariants();const auto state=account.statistics();resource::MemoryUsage purposes{},lifetimes{};
  for(const auto& usage:state.by_purpose)purposes=plus(purposes,usage);
  for(const auto& usage:state.by_lifetime)lifetimes=plus(lifetimes,usage);
  check(purposes==state.current && lifetimes==state.current,"session account partitions do not reconcile");
  check(state.current.requested_bytes<=state.limit_bytes && state.peak_requested_bytes<=state.limit_bytes,
      "session owners exceeded their original query account");
}
void controller_only(const resource::MemoryAccount& account) {
  reconcile(account);const auto usage=account.statistics().current;
  check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),
      "session/snapshot final release retained allocations");
}
PhysicalPlan plan(bool indexed,bool boolean=false) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"text",ScalarType::string}}}}};
  Query query{{{"x",ScalarType::int64},{"text",ScalarType::string}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}}},{{VariableId{0},"x"},{VariableId{1},"text"}},false};
  if(boolean)query.head.clear();
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Database database(std::size_t count=13) {
  Database db;db.tables.resize(1);
  for(std::size_t i=0;i<count;++i)db.tables[0].insert(Row{static_cast<std::int64_t>(i),
      std::string("snapshot\0bytes",14)+std::string(8192,static_cast<char>('a'+i%20))});
  return db;
}
SessionOptions options(std::uint64_t cap=64*1024*1024) {
  SessionOptions value;value.delta.physical.support.memory_limit_bytes=cap;return value;
}
void same_rows(const SessionSnapshot& snapshot,const Relation& expected) {
  Relation actual;
  for(const auto& tuple:snapshot.rows) {
    check(tuple.layout().same_token(snapshot.layout),"snapshot tuple lost its advertised layout token");
    actual.insert(storage::export_row(tuple.values()));
  }
  check(actual==expected,"snapshot differs from independent owning rows");
}
template<class F>void resource_denied(F&& action) {
  try{action();}catch(const Error& failure){check(failure.code()=="resource_limit","wrong snapshot sublimit failure");return;}
  throw std::runtime_error("expected snapshot sublimit rejection");
}
template<class F>void account_denied(F&& action) {
  try{action();}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong query-byte failure");return;}
  throw std::runtime_error("expected original query-byte rejection");
}
void ownership_and_bytes(bool indexed) {
  const auto input=database();resource::MemoryAccount account;
  std::optional<SessionSnapshot> held;
  std::shared_ptr<const SessionRunContext> context;
  std::optional<SessionStatisticsContext> capture;
  {
    auto session=QuerySession::create_typed(plan(indexed),input,{},options());
    account=session.get_deleter().account();
    check(session->accounted_memory_statistics()->owner==account.statistics().owner,
        "session facade has a different account from its runtime");
    const auto controls=account.statistics_for(session_owner);
    check(controls.current.allocations==3 &&
        controls.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::support_metadata)].allocations==2 &&
        controls.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::immutable_metadata)].allocations==1,
        "actual facade/Impl/run-context control allocations are not funded");
    context=session->run_context();
    const auto before=account.statistics().current;
    held.emplace(session->snapshot());
    const auto after=account.statistics().current;
    resource::MemoryUsage tuples{};
    for(const auto& row:held->rows)tuples=plus(tuples,row.memory_usage());
    const auto collection=held->rows.memory_usage();
    check(collection.allocations==2 && collection.requested_bytes>held->rows.capacity()*sizeof(storage::Tuple),
        "snapshot collection/control/capacity framing is not actually charged");
    check(difference(after,before)==plus(collection,tuples) &&
        held->accounted_bytes==collection.requested_bytes+tuples.requested_bytes,
        "snapshot bytes do not equal actual retained collection and tuple requests");
    same_rows(*held,input.tables[0]);
    {
      s04_alloc::Scope no_allocation(0);
      auto copied=*held;auto rows=held->rows;rows=copied.rows;
      check(rows.data()==held->rows.data() && copied.accounted_bytes==held->accounted_bytes && s04_alloc::calls==0,
          "snapshot copy/view allocated or cloned immutable collection storage");
    }
    // Preserve the measured growth schedule; a smaller row cap legitimately shrinks final capacity.
    SnapshotLimits exact;exact.rows=held->rows.capacity();exact.bytes=held->accounted_bytes;
    {auto retry=session->snapshot(exact);check(retry.accounted_bytes==exact.bytes,"exact snapshot sublimit was not admitted");}
    const auto stable=account.statistics().current;
    --exact.bytes;resource_denied([&]{static_cast<void>(session->snapshot(exact));});
    check(account.statistics().current==stable && session->status().committed_sequence==0,
        "one-byte snapshot denial leaked partial rows or changed its committed epoch");
    capture.emplace(session->capture_statistics_context());
    check(account.statistics_for({resource::MemoryOwnerKind::capture,0}).current.allocations>=1,
        "session capture outer object/control has no original-account allocation");
    {s04_alloc::Scope no_allocation(0);session->drop();session.reset();}
  }
  same_rows(*held,input.tables[0]);
  check(capture->metadata().plan().account().statistics().owner==account.statistics().owner &&
      context->input_kind==SessionInputKind::typed_physical,"retained context/capture lost the original query account");
  {s04_alloc::Scope no_allocation(0);capture.reset();context.reset();held.reset();}
  controller_only(account);
}
void empty_and_boolean(bool indexed) {
  {
    auto session=QuerySession::create_typed(plan(indexed),{},options());
    const auto account=session.get_deleter().account();const auto before=account.statistics().current;
    SnapshotLimits zero;zero.rows=0;zero.bytes=0;auto empty=session->snapshot(zero);
    check(empty.rows.empty() && empty.rows.memory_usage()==resource::MemoryUsage{} &&
        empty.accounted_bytes==0 && account.statistics().current==before,"empty snapshot allocated row collection storage");
  }
  auto session=QuerySession::create_typed(plan(indexed,true),database(1),{},options());
  auto result=session->snapshot();check(result.rows.size()==1 && result.rows.front().values().empty() &&
      result.rows.front().memory_usage().requested_bytes>0 && result.rows.memory_usage().requested_bytes>0,
      "nullary snapshot omitted native tuple or collection/control requests");
}
void retained_cap_and_move(bool indexed) {
  const auto compiled=plan(indexed);const auto initial=database();std::uint64_t peak=0;
  {
    auto session=QuerySession::create_typed(compiled,initial,{},options());
    auto first=session->snapshot();auto second=session->snapshot();
    peak=session->accounted_memory_statistics()->peak_requested_bytes;
  }
  {
    auto session=QuerySession::create_typed(compiled,initial,{},options(peak));
    auto first=session->snapshot();auto second=session->snapshot();
    check(session->accounted_memory_statistics()->peak_requested_bytes==peak,"exact original session/snapshot cap changed");
  }
  auto session=QuerySession::create_typed(compiled,initial,{},options(peak-1));
  const auto account=session.get_deleter().account();auto first=session->snapshot();
  const auto before=account.statistics().current;
  account_denied([&]{static_cast<void>(session->snapshot());});
  check(account.statistics().current==before && session->status().committed_sequence==0,
      "retained snapshot query-cap denial leaked partial output or changed state");
  same_rows(first,initial.tables[0]);
  auto other=QuerySession::create_typed(compiled,database(1),{},options());
  auto foreign=other->snapshot().rows;const auto old_account=foreign.account_statistics().owner;
  {
    s04_alloc::Scope no_allocation(0);foreign=first.rows;
    check(s04_alloc::calls==0 && foreign.data()==first.rows.data(),"cross-account collection assignment allocated or copied buffers");
  }
  check(old_account!=foreign.account_statistics().owner && foreign.account_statistics().owner==account.statistics().owner,
      "collection assignment changed or refilled an original query grant");
  foreign={};first.rows={};
  {auto retry=session->snapshot();same_rows(retry,initial.tables[0]);}
  reconcile(account);
  std::cout<<(indexed?"indexed":"reference")<<" retained snapshot exact/one-under peak="<<peak<<'\n';
}
void snapshot_faults(bool indexed) {
  const auto compiled=plan(indexed);const auto initial=database(5);std::size_t faults=0;bool complete=false;
  for(std::ptrdiff_t point=0;point<512;++point) {
    auto session=QuerySession::create_typed(compiled,initial,{},options());
    const auto account=session.get_deleter().account();const auto before=account.statistics().current;
    bool failed=false;
    {s04_alloc::Scope fault(point);try{auto snapshot=session->snapshot();}catch(const std::bad_alloc&){failed=true;}}
    check(account.statistics().current==before && session->status().committed_sequence==0,
        "persistent snapshot allocation failure leaked native collection/payloads or changed state");
    if(failed){++faults;auto retry=session->snapshot();same_rows(retry,initial.tables[0]);}
    else complete=true;
    reconcile(account);session.reset();controller_only(account);if(complete)break;
  }
  check(complete && faults>=10,"snapshot collection/growth/payload fault sweep was incomplete");
  std::cout<<(indexed?"indexed":"reference")<<" native snapshot persistent faults="<<faults<<'\n';
}
void window_controls(bool indexed) {
  resource::MemoryAccount account;
  {
    WindowOptions window;window.managed_tables={TableId{0}};
    auto session=QuerySession::create_windowed(plan(indexed),window,{},options());account=session.get_deleter().account();
    check(account.statistics_for(session_owner).current.allocations==5,
        "window facade/Impl controls were not funded under the existing session account");
    {s04_alloc::Scope no_allocation(0);session.reset();}
  }
  controller_only(account);
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      ownership_and_bytes(indexed);empty_and_boolean(indexed);retained_cap_and_move(indexed);
      snapshot_faults(indexed);window_controls(indexed);
    }
    std::cout<<"native session/snapshot controls, actual capacity bytes, immutable ownership, caps and failures passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/api/error.hpp"

#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
PhysicalPlan plan(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},
      {"s",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Row parent(std::size_t i) {return {std::string("left\0right",10)+std::string(8192,'q')+std::to_string(i),std::int64_t{42}};}
Row child() {return {std::int64_t{42}};}
DeltaOptions options(LiveMaintenance maintenance,DeltaCompletion completion,DeltaMode mode=DeltaMode::delta,
    std::uint64_t cap=std::numeric_limits<std::uint64_t>::max()) {
  DeltaOptions result;result.mode=mode;result.live_maintenance=maintenance;result.completion=completion;
  result.physical.support.memory_limit_bytes=cap;return result;
}
resource::MemoryAccount memory(DeltaRuntime& runtime) {
  return RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(runtime)));
}
void populate(DeltaRuntime& runtime,bool complete=false) {
  {auto epoch=runtime.apply({1,TableId{0},SetOperation::insert,parent(1)});epoch.discard();}
  {auto epoch=runtime.apply({2,TableId{0},SetOperation::insert,parent(2)});epoch.discard();}
  if(complete){auto epoch=runtime.apply({3,TableId{1},SetOperation::insert,child()});epoch.discard();}
}
void reconcile(const resource::MemoryAccount& account) {
  account.check_invariants();const auto state=account.statistics();resource::MemoryUsage purposes{},lifetimes{};
  const auto add=[](auto& a,const auto& b){a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;};
  for(const auto& value:state.by_purpose)add(purposes,value);
  for(const auto& value:state.by_lifetime)add(lifetimes,value);
  check(purposes==state.current && lifetimes==state.current,"actual Delta memory does not reconcile");
  check(state.current.requested_bytes<=state.limit_bytes && state.peak_requested_bytes<=state.limit_bytes,
      "actual Delta allocations exceeded the query account");
}
resource::MemoryUsage delta_usage(const resource::MemoryAccount& account) {
  resource::MemoryUsage result;
  for(const std::uint64_t id:{std::uint64_t{0},std::uint64_t{1},UINT64_MAX}) {
    const auto usage=account.statistics_for({resource::MemoryOwnerKind::delta_node,id}).current;
    result.allocations+=usage.allocations;result.requested_bytes+=usage.requested_bytes;result.payload_bytes+=usage.payload_bytes;
  }
  return result;
}
std::uint64_t delta_retained(const resource::MemoryAccount& account) {
  std::uint64_t bytes=0;
  for(const std::uint64_t id:{std::uint64_t{0},std::uint64_t{1},UINT64_MAX})bytes+=account.statistics_for({resource::MemoryOwnerKind::delta_node,id})
      .by_lifetime[static_cast<std::size_t>(resource::AllocationLifetime::retained)].requested_bytes;
  return bytes;
}
void controller_only(const resource::MemoryAccount& account) {
  reconcile(account);const auto state=account.statistics();
  check(state.current.allocations==1 && state.current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "final Delta owner retained actual allocated bytes");
}
template<class Operation> void denied(Operation&& operation) {
  try{operation();}catch(const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"unexpected actual Delta memory failure");return;
  }
  throw std::runtime_error("expected an actual query-account byte-limit denial");
}
void bootstrap_caps(bool indexed) {
  const auto compiled=plan(indexed);std::uint64_t peak=0;
  const auto bootstrap=[](DeltaRuntime& runtime) {
    for(std::size_t i=1;i<=32;++i){auto epoch=runtime.apply({i,TableId{0},SetOperation::insert,parent(i)});epoch.discard();}
    auto epoch=runtime.apply({33,TableId{1},SetOperation::insert,child()});epoch.discard();
  };
  {
    DeltaRuntime runtime(compiled,options(LiveMaintenance::incremental,DeltaCompletion::anchored,DeltaMode::maintenance));
    bootstrap(runtime);const auto setup=runtime.accounted_memory_statistics().peak_requested_bytes;
    static_cast<void>(runtime.set_mode(DeltaMode::delta));peak=runtime.accounted_memory_statistics().peak_requested_bytes;
    check(peak>setup,"native live/index bootstrap did not charge actual bytes");
    const auto live=runtime.live_snapshot();
    check(live && live->factors.size()==2 && live->factors[0].size()==32 && live->factors[1].size()==1,
        "memory fixture did not retain both native factors and separator indexes");
  }
  {
    DeltaRuntime exact(compiled,options(LiveMaintenance::incremental,DeltaCompletion::anchored,DeltaMode::maintenance,peak));
    bootstrap(exact);static_cast<void>(exact.set_mode(DeltaMode::delta));
    check(exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact native live bootstrap cap was not admitted");
    reconcile(memory(exact));
  }
  {
    DeltaRuntime limited(compiled,options(LiveMaintenance::incremental,DeltaCompletion::anchored,DeltaMode::maintenance,peak-1));
    bootstrap(limited);const auto before=limited.canonical_state();const auto account=memory(limited);
    const auto bytes=account.statistics().current;
    denied([&]{static_cast<void>(limited.set_mode(DeltaMode::delta));});
    check(limited.ready() && limited.canonical_state()==before && account.statistics().current==bytes,
        "one-byte bootstrap denial changed state or leaked native live/index allocations");
    reconcile(account);
  }
  std::cout<<(indexed?"indexed":"reference")<<" native live/index bootstrap exact/one-under peak="<<peak<<'\n';
}
void epoch_caps(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) {
  const auto compiled=plan(indexed);std::uint64_t peak=0;
  const PhysicalSetUpdate update{3,TableId{1},SetOperation::insert,child()};
  {
    DeltaRuntime runtime(compiled,options(maintenance,completion));populate(runtime);
    const auto setup=runtime.accounted_memory_statistics().peak_requested_bytes;
    auto epoch=runtime.apply(update);check(epoch.remaining()==2,"native memory fixture emitted a different result set");epoch.discard();
    peak=runtime.accounted_memory_statistics().peak_requested_bytes;check(peak>setup,"Delta crossing did not increase actual peak bytes");
  }
  {
    DeltaRuntime exact(compiled,options(maintenance,completion,DeltaMode::delta,peak));populate(exact);
    auto epoch=exact.apply(update);check(epoch.remaining()==2,"exact native crossing lost output rows");epoch.discard();
    check(exact.accounted_memory_statistics().peak_requested_bytes==peak,"exact native Delta crossing cap was not admitted");
    reconcile(memory(exact));
  }
  {
    DeltaRuntime limited(compiled,options(maintenance,completion,DeltaMode::delta,peak-1));populate(limited);
    const auto before=limited.canonical_state();const auto account=memory(limited);const auto delta_before=delta_usage(account);
    denied([&]{auto epoch=limited.apply(update);epoch.discard();});
    check(limited.ready() && limited.canonical_state()==before && delta_usage(account)==delta_before,
        "one-byte Delta denial changed committed state or retained native Delta allocations");
    reconcile(account);
  }
}
void undo_and_transfer(bool indexed,LiveMaintenance maintenance,DeltaCompletion completion) {
  const auto compiled=plan(indexed);resource::MemoryAccount account;
  {
    DeltaRuntime runtime(compiled,options(maintenance,completion));account=memory(runtime);populate(runtime,true);
    const auto before=runtime.canonical_state();const auto usage=delta_usage(account);
    const auto payload=account.statistics_for({resource::MemoryOwnerKind::delta_node,0})
        .by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::tuple_values)].payload_bytes;
    check(payload>=4*1024,"retained native live/parent-index string bytes were not actually attributed");
    {
      auto pending=runtime.begin({4,TableId{1},SetOperation::erase,child()});pending.drain();
      if(maintenance!=LiveMaintenance::eager)check(delta_retained(account)>0,"extracted live/index nodes were not classified retained");
      {s04_alloc::Scope no_allocation(0);pending.rollback();check(s04_alloc::calls==0,"native Delta rollback allocated");}
    }
    check(runtime.ready() && runtime.canonical_state()==before && delta_usage(account)==usage && delta_retained(account)==0,
        "native Delta rollback did not restore actual live/index ownership");
    {
      auto pending=runtime.begin({4,TableId{1},SetOperation::erase,child()});pending.drain();
      std::optional<DeltaRuntime::Epoch> committed;std::size_t records=0;
      {
        s04_alloc::Scope no_allocation(0);committed.emplace(pending.commit());
        while(auto record=committed->next())++records;
        committed.reset();check(s04_alloc::calls==0,"prepared native Delta commit/transfer/cleanup allocated");
      }
      check(records==2 && runtime.sequence()==4,"native prepared commit transferred the wrong records");
    }
    reconcile(account);
  }
  controller_only(account);
}
void persistent_faults(bool indexed) {
  const auto compiled=plan(indexed);const PhysicalSetUpdate update{3,TableId{1},SetOperation::insert,child()};
  std::size_t failures=0;bool finished=false;
  for(std::ptrdiff_t fail=0;fail<2048;++fail) {
    resource::MemoryAccount account;
    {
      DeltaRuntime runtime(compiled,options(LiveMaintenance::on_output,DeltaCompletion::ordered_replay));
      account=memory(runtime);populate(runtime);const auto before=runtime.canonical_state();const auto usage=delta_usage(account);
      bool failed=false;
      {
        s04_alloc::Scope fault(fail);
        try{auto epoch=runtime.apply(update);epoch.discard();}catch(const std::bad_alloc&){failed=true;}
      }
      if(failed) {
        ++failures;check(runtime.ready() && runtime.canonical_state()==before && delta_usage(account)==usage,
            "persistent allocation failure changed committed state or leaked native Delta storage");
        auto retry=runtime.apply(update);check(retry.remaining()==2,"same-sequence native Delta retry lost output rows");retry.discard();
      }else finished=true;
      reconcile(account);
    }
    controller_only(account);if(finished)break;
  }
  check(finished && failures>20,"native Delta failure sweep did not cover the complete update path");
  std::cout<<(indexed?"indexed":"reference")<<" actual Delta persistent failure positions="<<failures<<'\n';
}
void native_cursor_boundaries(bool indexed) {
  const auto compiled=plan(indexed);resource::MemoryAccount account;
  std::optional<storage::AccountedTuple> retained;
  {
    SupportRuntime runtime(compiled);account=RuntimeTestProbe::memory_account(runtime);
    static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,parent(1)}));
    static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,parent(2)}));
    static_cast<void>(runtime.apply({3,NodeId{1},SetOperation::insert,child()}));
    auto view=runtime.current_view();
    {
      auto legacy=view.visible_keys(NodeId{0}),native=view.visible_keys(NodeId{0});
      for(;;) {
        auto old=legacy.next();auto row=native.next_native();
        check(bool(old)==bool(row),"native/public cursor termination differs");
        check(legacy.metrics().last.work==native.metrics().last.work,"native cursor changed mandatory traversal work");
        if(!row)break;
        check(row->values()==old->values() && row->layout().same_token(old->layout()),
            "native cursor changed exact values or the original layout token");
        check(row->layout().account_statistics().owner==account.statistics().owner,
            "native cursor output minted a foreign account");
      }
    }
    {
      const std::array cells{storage::ScalarView{std::int64_t{42}}};
      auto native=view.visible_bucket_native(NodeId{1},storage::RowView::borrow(cells));
      auto legacy=view.visible_bucket(NodeId{1},child());
      auto row=native.next_native();auto old=legacy.next();
      check(row && old && row->values()==old->values() && !native.next_native() && !legacy.next(),
          "native/public separator bucket results differ");
    }
    const auto error=[&](auto&& operation,std::string_view code) {
      try{operation();}catch(const Error& failure){check(failure.code()==code,"native input changed the error category");return;}
      throw std::runtime_error("invalid native cursor input was admitted");
    };
    error([&]{static_cast<void>(view.visible_bucket_native(NodeId{1},{}));},"invalid_tuple");
    error([&]{static_cast<void>(view.visible_bucket_native(NodeId{0},{}));},"invalid_fragment");
    {
      const std::array wrong{VariableBindingView{VariableId{1},storage::ScalarView{std::string_view("wrong")}}};
      error([&]{static_cast<void>(view.completions_native(wrong));},"invalid_binding");
    }
    std::optional<SupportRuntime::ResultCursor> native;
    {
      const auto row=parent(1);auto input=storage::AccountedRow::copy_of(account,row);
      const std::array bindings{VariableBindingView{VariableId{0},input.view()[0]}};
      native.emplace(view.completions_native(bindings));
    }
    retained=native->next_native();
    check(retained && retained->values()==parent(1) && !native->next_native(),
        "native fixed binding did not survive destruction of its borrowed input");
    native.reset();view.close();check(runtime.ready(),"native cursor boundary retained a read lease");
    reconcile(account);
  }
  check(retained && retained->values()==parent(1),"native output did not survive runtime destruction");
  check(account.statistics().current.requested_bytes>resource::MemoryAccount::control_bytes(),
      "native output payload/layout were not charged after runtime destruction");
  {
    s04_alloc::Scope no_allocation(0);auto moved=std::move(retained);retained.reset();moved.reset();
    check(s04_alloc::calls==0,"native output transfer or final release allocated");
  }
  controller_only(account);
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      native_cursor_boundaries(indexed);
      bootstrap_caps(indexed);
      for(const auto& [maintenance,completion]:std::array{
          std::pair{LiveMaintenance::on_output,DeltaCompletion::ordered_replay},
          std::pair{LiveMaintenance::on_output,DeltaCompletion::anchored},
          std::pair{LiveMaintenance::incremental,DeltaCompletion::anchored},
          std::pair{LiveMaintenance::eager,DeltaCompletion::anchored},
          std::pair{LiveMaintenance::incremental,DeltaCompletion::root_first}}) {
        epoch_caps(indexed,maintenance,completion);undo_and_transfer(indexed,maintenance,completion);
      }
      persistent_faults(indexed);
    }
    std::cout<<"actual Delta live/index/undo/queue memory: exact caps, rollback, no-allocation transfer and cleanup passed\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

#include "crown/runtime/session.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
constexpr resource::MemoryAttribution window_owner{resource::MemoryOwnerKind::session,1};
void check(bool condition,std::string_view message) {
  if(!condition)throw std::runtime_error(std::string(message));
}
PhysicalPlan plan(bool indexed) {
  Catalog catalog{1,{}};
  for(const auto* name:{"left","right"})catalog.tables.push_back({name,
      {{"id",ScalarType::int64},{"key",ScalarType::string},{"flag",ScalarType::boolean},
       {"day",ScalarType::date},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}});
  return planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():PhysicalOptions{});
}
DeltaOptions options(std::uint64_t cap=64*1024*1024) {
  DeltaOptions result;result.physical.support.memory_limit_bytes=cap;return result;
}
WindowOptions windows(WindowFifoPolicy fifo=WindowFifoPolicy::global) {
  WindowOptions result;result.managed_tables={TableId{0},TableId{1}};result.width=10;result.fifo=fifo;return result;
}
Row row(std::int64_t id,std::size_t bytes=8192) {
  return {id,std::string("\0native",7)+std::string(bytes,'w'),true,Date::parse("2026-11-09"),
      Decimal::parse("123456789012345678901234567890123456.12")};
}
io::WindowCommand insertion(std::uint64_t sequence,std::uint64_t label,TableId table,const Row& values) {
  return {sequence,io::WindowInsert{label,table,values,0},{}};
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto usage=account.statistics().current;
  check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),
      "window ownership survived its final native owner");
}
struct Fixture {
  DeltaRuntime runtime;
  WindowController window;
  Fixture(bool indexed,std::uint64_t cap=64*1024*1024,WindowFifoPolicy fifo=WindowFifoPolicy::global)
      :runtime(plan(indexed),options(cap)),window(runtime.plan().account(),runtime.plan().source_catalog(),windows(fifo)) {}
  resource::MemoryAccount account() const {return runtime.plan().account();}
  void accept(const io::WindowCommand& command,bool count_requests=false) {
    std::optional<WindowController::Prepared> step;
    std::optional<DeltaRuntime::PendingEpoch> pending;
    const auto before=account().statistics().successful_allocations;std::size_t calls=0;
    const auto prepare=[&] {
      step.emplace(window.prepare(command,runtime.sequence()+1));
      if(step->update()) {pending.emplace(runtime.begin_view(*step->update()));pending->drain();}
    };
    if(count_requests) {s04_alloc::Scope count;prepare();calls=s04_alloc::calls;}
    else prepare();
    if(count_requests)check(calls==account().statistics().successful_allocations-before && calls>0,
        "native window/physical admission allocated an ordinary row, option, node or expansion mirror");
    const auto publish=[&] {
      if(pending){auto epoch=pending->commit();epoch.discard();}
      step->publish();step.reset();pending.reset();
    };
    // A persistent upstream failure scope remains active through publication;
    // the helper rejects nested scopes. Ordinary calls independently forbid
    // every publication/cleanup allocation at the zero-allocation barrier.
    if(s04_alloc::enabled)publish();
    else {s04_alloc::Scope no_allocation(0);publish();}
    account().check_invariants();
  }
};
void controls_and_retained_values(bool indexed) {
  resource::MemoryAccount account;
  std::optional<AccountedWindowOptions> retained;
  std::optional<WindowController::Prepared> published;
  const auto values=row(7);const auto command=insertion(1,1,TableId{0},values);
  {
    DeltaRuntime runtime(plan(indexed),options());account=runtime.plan().account();const auto config=windows();
    const auto before=account.statistics().successful_allocations;std::size_t calls=0;
    std::optional<WindowController> window;
    {s04_alloc::Scope count;window.emplace(account,runtime.plan().source_catalog(),config);calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before,
        "native window constructor retained ordinary options or relation nodes");
    {s04_alloc::Scope no_allocation(0);retained.emplace(window->options());}
    check(retained->managed_tables==config.managed_tables,"retained native options lost managed-table order");
    published.emplace(window->prepare(command,1));
    auto pending=runtime.begin_view(*published->update());pending.drain();
    {s04_alloc::Scope no_allocation(0);auto epoch=pending.commit();published->publish();epoch.discard();}
    check(published->update()->values==values,"published prepared native update lost its owning payload");
    check(account.statistics_for(window_owner).current.allocations>2,"native window owner attribution was not exercised");
  }
  check(retained->managed_tables.size()==2 && retained->managed_tables[1]==TableId{1} &&
      published->update()->values==values,"native options/update did not survive facade destruction");
  {s04_alloc::Scope no_allocation(0);auto copy=*retained;auto moved=std::move(copy);*retained=std::move(moved);published.reset();}
  check(account.statistics().current.allocations>1,"held native options were no longer charged");
  {s04_alloc::Scope no_allocation(0);retained.reset();}
  controller_only(account);
}
void allocation_and_prefixes(bool indexed,WindowFifoPolicy fifo) {
  Fixture f(indexed,64*1024*1024,fifo);const auto values=row(3);
  const auto first=insertion(1,1,TableId{0},values);const auto duplicate=insertion(2,2,TableId{0},values);
  const auto other=insertion(3,3,TableId{1},values);const io::WindowCommand watermark{4,io::AdvanceWatermark{10},{}};
  f.accept(first,true);f.accept(duplicate,true);f.accept(other,true);
  const auto before=f.window.canonical_state();check(before.labels.size()==3 && before.counts.size()==2,"duplicate full rows changed reference counts");
  f.accept(watermark,true);auto prefix=f.window.canonical_state();
  check(prefix.active_command && prefix.active_command->completed_steps==1 && prefix.active_command->total_steps==3 &&
      prefix.completed_command_sequence==3 && prefix.completed_watermark==0,"watermark acknowledged before its final native step");
  f.accept(watermark,true);f.accept(watermark,true);
  check(f.window.progress().completed_command_sequence==4 && f.window.progress().completed_watermark==10 &&
      f.window.metrics().live_labels==0 && f.runtime.sequence()==4,"native watermark expansion changed physical/command progress");
}
template<class Action> void denied(Action&& action) {
  try{action();}catch(const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"unexpected window account failure kind");return;
  }
  throw std::runtime_error("expected original-account native window denial");
}
void insertion_limits(bool indexed) {
  const auto values=row(9,16000);const auto command=insertion(1,1,TableId{0},values);
  const io::WindowCommand smaller{1,io::AdvanceWatermark{0},{}};
  std::uint64_t peak=0;
  {
    Fixture f(indexed);const auto initial=f.account().statistics().peak_requested_bytes;f.accept(command);
    peak=f.account().statistics().peak_requested_bytes;check(peak>initial,"window insertion did not exceed setup peak");
  }
  {Fixture f(indexed,peak);f.accept(command);check(f.account().statistics().peak_requested_bytes==peak,"exact native window insertion cap changed");}
  resource::MemoryAccount account;
  {
    Fixture f(indexed,peak-1);account=f.account();const auto before=f.window.canonical_state();const auto physical=f.runtime.canonical_state();
    denied([&]{f.accept(command);});
    check(f.window.canonical_state()==before && f.runtime.canonical_state()==physical && f.runtime.ready(),
        "native window byte rejection changed committed physical/label state");
    f.accept(smaller);check(f.window.progress().completed_command_sequence==1 && f.runtime.sequence()==0 &&
        account.statistics().limit_bytes==peak-1,"smaller same-command native window retry replaced its allowance");
  }
  controller_only(account);
  std::cout<<(indexed?"indexed":"reference")<<" native window insertion exact/one-under peak="<<peak<<'\n';
}
void expansion_limits_and_stop(bool indexed,WindowFifoPolicy fifo) {
  constexpr std::uint64_t labels=512;
  const auto values=row(1,0);const io::WindowCommand watermark{labels+1,io::AdvanceWatermark{10},{}};
  const io::WindowCommand smaller{labels+1,io::AdvanceWatermark{0},{}};
  const auto seed=[&](Fixture& f) {
    for(std::uint64_t id=1;id<=labels;++id) {const auto command=insertion(id,id,TableId{0},values);f.accept(command);}
  };
  std::uint64_t peak=0;
  {
    Fixture f(indexed,64*1024*1024,fifo);seed(f);const auto before=f.account().statistics().peak_requested_bytes;
    f.accept(watermark,true);peak=f.account().statistics().peak_requested_bytes;
    check(peak>before,"watermark native expansion did not exceed prior peak");
    const auto prefix=f.window.progress();const auto usage=f.account().statistics().current;
    {s04_alloc::Scope no_allocation(0);f.window.stop();}
    const auto after=f.window.canonical_state();
    check(after.active_command && after.active_command->expiration_labels.empty() && f.window.progress()==prefix &&
        f.account().statistics().current.requested_bytes<usage.requested_bytes,
        "stop did not release actual native expansion capacity while preserving prefix scalars");
  }
  {
    Fixture f(indexed,peak,fifo);seed(f);f.accept(watermark);
    check(f.account().statistics().peak_requested_bytes==peak,"exact native expansion budget changed");
  }
  resource::MemoryAccount account;
  {
    Fixture f(indexed,peak-1,fifo);account=f.account();seed(f);const auto before=f.window.canonical_state();
    const auto physical=f.runtime.canonical_state();const auto usage=account.statistics().current;
    denied([&]{f.accept(watermark);});
    check(f.window.canonical_state()==before && f.runtime.canonical_state()==physical && account.statistics().current==usage,
        "watermark byte denial retained tentative native expansion or changed prior state");
    f.accept(smaller);check(account.statistics().limit_bytes==peak-1 && f.window.progress().completed_command_sequence==labels+1,
        "same-sequence smaller native expansion retry failed");
  }
  controller_only(account);
  std::cout<<(indexed?"indexed":"reference")<<(fifo==WindowFifoPolicy::global?" global":" per-relation")
      <<" native watermark exact/one-under peak="<<peak<<'\n';
}
void persistent_failures(bool indexed,WindowFifoPolicy fifo) {
  const auto first=insertion(1,1,TableId{0},row(1));const auto other=insertion(2,2,TableId{1},row(2));
  const auto duplicate=insertion(2,2,TableId{0},row(1));const io::WindowCommand watermark{3,io::AdvanceWatermark{10},{}};
  for(int scenario=0;scenario<4;++scenario) {
    std::size_t failures=0;bool complete=false;
    for(std::ptrdiff_t point=0;point<2048;++point) {
      Fixture f(indexed,64*1024*1024,fifo);
      if(scenario>=1)f.accept(first);
      if(scenario>=2)f.accept(other);
      if(scenario==3)f.accept(watermark);
      const auto& command=scenario==0?first:(scenario==1?duplicate:watermark);
      const auto before=f.window.canonical_state();const auto physical=f.runtime.canonical_state();
      bool failed=false;
      {s04_alloc::Scope fault(point);try{f.accept(command);}catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;check(f.window.canonical_state()==before && f.runtime.canonical_state()==physical && f.runtime.ready(),
            "persistent native window fault changed the prior committed prefix");
        f.accept(command);
      }else complete=true;
      f.account().check_invariants();if(complete)break;
    }
    check(complete && failures>0,"native window persistent fault sweep did not complete");
    std::cout<<(indexed?"indexed":"reference")<<(fifo==WindowFifoPolicy::global?" global":" per-relation")
        <<" native window scenario="<<scenario<<" persistent faults="<<failures<<'\n';
  }
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      controls_and_retained_values(indexed);insertion_limits(indexed);
      for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation}) {
        allocation_and_prefixes(indexed,fifo);expansion_limits_and_stop(indexed,fifo);persistent_failures(indexed,fifo);
      }
    }
    std::cout<<"native window ownership: allocation routing, real caps, retained options/updates, prefix recovery and nonallocating barriers passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

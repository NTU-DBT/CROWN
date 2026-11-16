#include "crown/api/error.hpp"
#include "crown/runtime/physical.hpp"
#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <type_traits>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto current=account.statistics().current;
  check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "final epoch/array owner retained funded allocations");
}
template<class F>void denied(F&& action) {
  try{action();}catch(const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"wrong epoch byte-limit failure");return;
  }
  throw std::runtime_error("expected original epoch account byte denial");
}
template<class T>resource::MemoryUsage buffer_usage(const std::vector<T,resource::OwnerAllocator<T>>& values) {
  return values.get_allocator().allocation_usage(values.data(),values.capacity());
}
void allocator_ownership() {
  using Allocator=resource::OwnerAllocator<int>;
  using Vector=std::vector<int,Allocator>;
  static_assert(!std::allocator_traits<resource::MemoryAllocator<int>>::propagate_on_container_move_assignment::value);
  static_assert(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value);
  static_assert(std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value);
  static_assert(std::allocator_traits<Allocator>::propagate_on_container_swap::value);
  static_assert(std::is_nothrow_move_assignable_v<Vector>);
  auto first=resource::MemoryAccount::create(1024*1024),second=resource::MemoryAccount::create(1024*1024);
  const resource::MemoryAttribution owner{resource::MemoryOwnerKind::output,17};
  {
    Vector source({1,2,3},Allocator(first,resource::MemoryPurpose::output_buffer,owner));
    Vector target({8,9},Allocator(second,resource::MemoryPurpose::scratch,{resource::MemoryOwnerKind::output,19}));
    const auto* pointer=source.data();
    {s04_alloc::Scope fault(0);target=std::move(source);check(s04_alloc::calls==0,"cross-account result move allocated");}
    check(target.data()==pointer && target.get_allocator().account().statistics().owner==first.statistics().owner &&
        target.get_allocator().attribution()==owner,"result move changed the source account, attribution or buffer");
    controller_only(second);
    Vector copied;copied=target;
    check(copied==target && copied.data()!=target.data() && copied.get_allocator()==target.get_allocator(),
        "result copy did not fund its new buffer under the original account");
    Vector other({7},Allocator(second,resource::MemoryPurpose::scratch));
    const auto* other_pointer=other.data();
    {s04_alloc::Scope fault(0);other.swap(target);check(s04_alloc::calls==0,"cross-account result swap allocated");}
    check(target.data()==other_pointer && target.get_allocator().account().statistics().owner==second.statistics().owner &&
        other.data()==pointer && other.get_allocator().attribution()==owner,"result swap did not transfer the exact owners");
    const auto before=first.statistics().current;bool failed=false;
    {s04_alloc::Scope fault(0);try{Vector denied_copy(other);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && first.statistics().current==before && other==copied,"failed result copy leaked or changed the source");
    std::vector<bool,resource::OwnerAllocator<bool>> bits(65,true,
        resource::OwnerAllocator<bool>(first,resource::MemoryPurpose::journal_undo,owner));
    std::vector<bool,resource::OwnerAllocator<bool>> moved;
    {s04_alloc::Scope fault(0);moved=std::move(bits);check(s04_alloc::calls==0,"rebound bit-buffer move allocated");}
    check(moved.size()==65 && std::ranges::all_of(moved,[](bool bit){return bit;}) &&
        moved.get_allocator().account().statistics().owner==first.statistics().owner && moved.get_allocator().attribution()==owner,
        "bit allocator rebind lost original ownership or values");
  }
  controller_only(first);controller_only(second);
}
PhysicalPlan plan(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},{"s",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Row parent(){return {std::string("epoch\0bytes",11)+std::string(8192,'e'),std::int64_t{42}};}
Row child(){return {std::int64_t{42}};}
SupportOptions options(bool trace,std::uint64_t cap=64*1024*1024) {
  SupportOptions value;value.capture_transitions=trace;value.memory_limit_bytes=cap;return value;
}
void journal_owners(bool indexed,bool trace) {
  resource::MemoryAccount account;std::optional<SupportEpoch> held;
  {
    SupportRuntime runtime(plan(indexed),options(trace));account=RuntimeTestProbe::memory_account(runtime);
    {auto first=runtime.apply({1,NodeId{0},SetOperation::insert,parent()});}
    auto pending=runtime.begin_epoch(2,SetOperation::insert);
    check(pending.stage(NodeId{1},child()),"journal fixture did not change its child");
    {s04_alloc::Scope fault(0);held.emplace(pending.commit());check(s04_alloc::calls==0,"funded journal publication allocated");}
    check(held->journal && held->journal->records.size()>0,"actual journal is missing");
    check(held->transitions.get_allocator().account().statistics().owner==account.statistics().owner &&
        held->journal->events.get_allocator().account().statistics().owner==account.statistics().owner,
        "actual event/transition arrays do not use the original query account");
    if(trace) {
      check(buffer_usage(held->transitions).allocations==1 && buffer_usage(held->journal->events).allocations==1,
          "captured event/transition capacity has no real allocator request");
      const auto before=account.statistics().current;
      {
        auto copied=*held;const auto usage=buffer_usage(copied.transitions);const auto after=account.statistics().current;
        check(after.allocations==before.allocations+usage.allocations &&
            after.requested_bytes==before.requested_bytes+usage.requested_bytes && copied.journal==held->journal,
            "epoch copy created unaccounted storage or cloned shared journal/payloads");
      }
      check(account.statistics().current==before,"epoch copy release leaked capacity");
    }else check(held->transitions.empty() && held->journal->events.empty() &&
        buffer_usage(held->transitions)==resource::MemoryUsage{} && buffer_usage(held->journal->events)==resource::MemoryUsage{},
        "disabled trace allocated output arrays");
    bool flags_seen=false;
    for(const auto& record:held->journal->records)for(const auto* state:{&record.before,&record.after}) {
      if(state->child_present.empty())continue;
      flags_seen=true;const auto allocator=state->child_present.get_allocator();
      check(allocator.account().statistics().owner==account.statistics().owner &&
          allocator.purpose()==resource::MemoryPurpose::journal_undo,"retained child flags lost their original allocator");
      const auto before=account.statistics();
      {
        std::optional<decltype(state->child_present)> copy;
        std::size_t calls=0;
        {s04_alloc::Scope count;copy.emplace(state->child_present);calls=s04_alloc::calls;}
        const auto after=account.statistics();
        check(*copy==state->child_present && after.current.allocations==before.current.allocations+1 &&
            calls==after.successful_allocations-before.successful_allocations,
            "child flags copied through an unaccounted bit-buffer mirror");
      }
      check(account.statistics().current==before.current,"retained child flag copy leaked");
    }
    check(flags_seen,"journal fixture did not exercise retained child flags");
  }
  check(held->journal->records.size()>0 && held->has_answer,"held journal lost its values after runtime destruction");
  if(trace) {
    check(!held->transitions.empty() && held->transitions.front().tuple.is_accounted() && !held->journal->events.empty(),
        "retained trace/transition arrays lost storage after facade destruction");
    for(const auto& event:held->journal->events)check(event.key.is_accounted() && event.sequence==2,
        "held causal event lost its native tuple or sequence");
  }
  {s04_alloc::Scope fault(0);held.reset();check(s04_alloc::calls==0,"final journal/flags/array cleanup allocated");}
  controller_only(account);
}
void physical_owners(bool indexed) {
  resource::MemoryAccount account;std::optional<PhysicalEpoch> held;
  {
    PhysicalRuntimeOptions value;value.support=options(true);PhysicalRuntime runtime(plan(indexed),value);
    account=RuntimeTestProbe::memory_account(RuntimeTestProbe::support(runtime));
    {auto first=runtime.apply({1,TableId{0},SetOperation::insert,parent()});}
    auto pending=runtime.prepare({2,TableId{1},SetOperation::insert,child()});
    const auto& rows=pending.preview().derivations;
    check(rows.size()==1 && rows.get_allocator().account().statistics().owner==account.statistics().owner &&
        buffer_usage(rows).allocations==1,"physical preview derivation capacity is not actually funded");
    {s04_alloc::Scope fault(0);held.emplace(pending.commit());check(s04_alloc::calls==0,"funded physical publication allocated");}
  }
  check(held->input.derivations.size()==1 && held->input.derivations[0].occurrence==OccurrenceId{1} &&
      held->input.derivations[0].tuple.values()==child() && held->input.derivations[0].after==1,
      "retained derivation values/order/owner did not survive physical runtime destruction");
  {s04_alloc::Scope fault(0);held.reset();check(s04_alloc::calls==0,"final physical epoch cleanup allocated");}
  controller_only(account);
}
void limits_and_faults(bool indexed) {
  const auto compiled=plan(indexed);std::uint64_t peak=0;
  {
    SupportRuntime runtime(compiled,options(true));{auto first=runtime.apply({1,NodeId{0},SetOperation::insert,parent()});}
    auto held=runtime.apply({2,NodeId{1},SetOperation::insert,child()});
    auto next=runtime.apply({3,NodeId{1},SetOperation::erase,child()});peak=runtime.accounted_memory_statistics().peak_requested_bytes;
  }
  {
    SupportRuntime runtime(compiled,options(true,peak));{auto first=runtime.apply({1,NodeId{0},SetOperation::insert,parent()});}
    auto held=runtime.apply({2,NodeId{1},SetOperation::insert,child()});auto next=runtime.apply({3,NodeId{1},SetOperation::erase,child()});
    check(runtime.accounted_memory_statistics().peak_requested_bytes==peak,"exact retained epoch peak was not admitted");
  }
  {
    SupportRuntime runtime(compiled,options(true,peak-1));{auto first=runtime.apply({1,NodeId{0},SetOperation::insert,parent()});}
    std::optional<SupportEpoch> held;held.emplace(runtime.apply({2,NodeId{1},SetOperation::insert,child()}));
    const auto before=runtime.canonical_state();
    denied([&]{static_cast<void>(runtime.apply({3,NodeId{1},SetOperation::erase,child()}));});
    check(runtime.ready() && runtime.canonical_state()==before && !held->journal->events.empty(),
        "retained epoch cap rejection damaged the previous state or trace");
    {s04_alloc::Scope fault(0);held.reset();}
    auto retry=runtime.apply({3,NodeId{1},SetOperation::erase,child()});check(runtime.sequence()==3 && !retry.has_answer,
        "same-sequence epoch retry did not succeed after history release");
  }
  std::size_t failures=0;bool complete=false;
  for(std::ptrdiff_t point=0;point<1024;++point) {
    SupportRuntime runtime(compiled,options(true));const auto account=RuntimeTestProbe::memory_account(runtime);
    {auto first=runtime.apply({1,NodeId{0},SetOperation::insert,parent()});}
    const auto before=runtime.canonical_state();const auto usage=account.statistics();bool failed=false;
    {s04_alloc::Scope fault(point);try{auto epoch=runtime.apply({2,NodeId{1},SetOperation::insert,child()});}
      catch(const std::bad_alloc&){failed=true;}}
    if(failed) {
      ++failures;check(runtime.ready() && runtime.canonical_state()==before,"epoch allocation failure damaged the previous state");
      const auto after=account.statistics();
      for(const auto purpose:{resource::MemoryPurpose::journal_undo,resource::MemoryPurpose::output_buffer})
        check(after.by_purpose[static_cast<std::size_t>(purpose)]==usage.by_purpose[static_cast<std::size_t>(purpose)],
            "failed epoch retained new journal/flag/output allocations");
      {auto retry=runtime.apply({2,NodeId{1},SetOperation::insert,child()});check(retry.has_answer,"same-input retry failed");}
    }else complete=true;
    account.check_invariants();if(complete)break;
  }
  check(complete && failures>=10,"epoch array/flag persistent allocation sweep was incomplete");
  std::cout<<(indexed?"indexed":"reference")<<" retained epoch exact/one-under peak="<<peak<<"; persistent faults="<<failures<<'\n';
}
} // namespace
int main() {
  try {
    allocator_ownership();
    for(const bool indexed:{false,true}) {
      for(const bool trace:{false,true})journal_owners(indexed,trace);
      physical_owners(indexed);limits_and_faults(indexed);
    }
    std::cout<<"native epoch arrays, retained flags, ownership transfer, exact bytes, limits and faults passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

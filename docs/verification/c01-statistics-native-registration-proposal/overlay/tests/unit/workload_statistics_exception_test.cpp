#include "workload_statistics_fixture.hpp"
#include <cstdlib>
#include <iostream>
#include <new>

namespace {
thread_local std::ptrdiff_t fail_after=-1;
thread_local std::size_t allocations=0;
[[gnu::noinline]] void* allocate(std::size_t bytes) {
  if (fail_after==0) throw std::bad_alloc{};
  if (fail_after>0) --fail_after;
  ++allocations;
  if (auto* p=std::malloc(bytes?bytes:1)) return p;
  throw std::bad_alloc{};
}
struct Fault {
  explicit Fault(std::ptrdiff_t position):previous(fail_after) { fail_after=position; }
  ~Fault() { fail_after=previous; }
  Fault(const Fault&)=delete;
  Fault& operator=(const Fault&)=delete;
  std::ptrdiff_t previous;
};
}
void* operator new(std::size_t bytes) { return allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocate(bytes); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p,std::size_t) noexcept { std::free(p); }
void operator delete[](void* p,std::size_t) noexcept { std::free(p); }

namespace {
using namespace workload_fixture;
std::size_t configure_failures=0, update_failures=0, mode_failures=0;
void strong_configure() {
  DeltaRuntime runtime(plan(),delta_options()); runtime.configure_workload_statistics(enabled());
  apply(runtime,0,SetOperation::insert,{n(1),n(7)});
  const auto previous=runtime.workload_statistics(); const auto owner=runtime.owner();
  auto next=enabled(3,1,20); bool success=false;
  for (std::ptrdiff_t ordinal=0;ordinal<64;++ordinal) {
    bool failed=false;
    { Fault fault(ordinal); try { runtime.configure_workload_statistics(next); } catch (const std::bad_alloc&) { failed=true; } }
    if (!failed) { success=true; break; }
    ++configure_failures;
    const auto current=runtime.workload_statistics();
    check(current.options()==previous.options() && current.stamp().reset_generation==previous.stamp().reset_generation);
    check(current.stamp().configuration_generation==previous.stamp().configuration_generation);
    check(same_cells(current.cells(),previous.cells()) && runtime.owner()==owner && runtime.sequence()==1);
    check(current.memory().retained_payload_bytes==previous.memory().retained_payload_bytes);
  }
  check(success && configure_failures>=6);
  const auto configured=runtime.workload_statistics();
  check(configured.options()==next && configured.metadata().committed==0);
  check(configured.stamp().configuration_generation==previous.stamp().configuration_generation+1);
  check(previous.metadata().committed==1);
  const auto count=allocations;
  { Fault fault(0); runtime.reset_workload_statistics(); }
  check(count==allocations);
  // Disabling releases every slab/route without requesting new allocation.
  { Fault fault(0); runtime.configure_workload_statistics({}); }
  check(runtime.workload_statistics().memory().retained_payload_bytes==0);
}
void same_owner_update_recovery() {
  DeltaRuntime runtime(alias_plan(),delta_options()); runtime.configure_workload_statistics(enabled());
  const auto owner=runtime.owner(); bool success=false, staged_failure=false;
  const Row row{n(1),n(7),n(3)};
  for (std::ptrdiff_t ordinal=0;ordinal<2048;++ordinal) {
    const auto before=runtime.workload_statistics(); const auto sequence=runtime.sequence();
    const PhysicalSetUpdate update{sequence+1,{0},SetOperation::insert,row};
    bool failed=false;
    { Fault fault(ordinal); try { auto output=runtime.apply(update); output.discard(); } catch (const std::bad_alloc&) { failed=true; } }
    check(runtime.owner()==owner && runtime.ready());
    if (failed) {
      ++update_failures;
      const auto after=runtime.workload_statistics();
      check(runtime.sequence()==sequence && same_cells(before.cells(),after.cells()));
      check(runtime.snapshot().physical.tables[0].empty());
      staged_failure=staged_failure || after.metadata().detail_actions>before.metadata().detail_actions;
      runtime.check_invariants();
      // Recovery is an actual subsequent update on the same owner and same
      // failed physical sequence, with a new admitted sampling ordinal.
      auto recovered=runtime.apply(update); recovered.discard();
      const auto recovery=runtime.workload_statistics();
      check(runtime.sequence()==sequence+1 && recovery.metadata().committed==before.metadata().committed+1);
    } else success=true;
    apply(runtime,0,SetOperation::erase,row); runtime.check_invariants();
    check(runtime.snapshot().physical.tables[0].empty());
    if (success) break;
  }
  check(success && staged_failure && update_failures>0);
}
void nonallocating_commit_abort_and_snapshot_failure() {
  DeltaRuntime runtime(alias_plan(),delta_options()); runtime.configure_workload_statistics(enabled());
  auto pending=runtime.begin({1,{0},SetOperation::insert,{n(1),n(7),n(0)}}); pending.drain();
  const auto before=runtime.workload_statistics(); check(before.pending() && before.metadata().committed==0);
  auto count=allocations;
  { Fault fault(0); auto output=pending.commit(); output.discard(); }
  check(count==allocations && runtime.sequence()==1);
  auto committed=runtime.workload_statistics(); check(committed.metadata().committed==1);
  auto aborted=runtime.begin({2,{0},SetOperation::erase,{n(1),n(7),n(0)}}); aborted.drain();
  count=allocations;
  { Fault fault(0); aborted.rollback(); }
  check(count==allocations && runtime.sequence()==1 && runtime.ready());
  check(same_cells(runtime.workload_statistics().cells(),committed.cells()));
  bool failed=false;
  { Fault fault(0); try { static_cast<void>(runtime.workload_statistics()); } catch (const std::bad_alloc&) { failed=true; } }
  check(failed && same_cells(runtime.workload_statistics().cells(),committed.cells()));
  runtime.check_invariants();
}
void failed_mode_oom() {
  DeltaRuntime runtime(plan(),delta_options(DeltaMode::maintenance));
  apply(runtime,0,SetOperation::insert,{n(1),n(7)}); apply(runtime,1,SetOperation::insert,{n(7)});
  runtime.configure_workload_statistics(enabled()); apply(runtime,2,SetOperation::insert,{n(9)});
  const auto before=runtime.workload_statistics(); bool success=false;
  for (std::ptrdiff_t ordinal=0;ordinal<2048;++ordinal) {
    bool failed=false;
    { Fault fault(ordinal); try { static_cast<void>(runtime.set_mode(DeltaMode::delta)); } catch (const std::bad_alloc&) { failed=true; } }
    if (!failed) { success=true; break; }
    ++mode_failures; const auto current=runtime.workload_statistics();
    check(runtime.ready() && runtime.mode()==DeltaMode::maintenance && runtime.owner()==before.stamp().owner);
    check(current.stamp().segment==before.stamp().segment && current.modes()==before.modes());
    check(same_cells(current.cells(),before.cells()) && !current.has_previous());
  }
  check(success && mode_failures>0);
  const auto after=runtime.workload_statistics(); check(after.stamp().segment==before.stamp().segment+1);
  check(after.previous_metadata().committed==1 && after.metadata().committed==0);
}
}
int main() {
  strong_configure(); same_owner_update_recovery(); nonallocating_commit_abort_and_snapshot_failure(); failed_mode_oom();
  std::cout<<"workload statistics exception: configure failures="<<configure_failures
      <<", same-owner update failures="<<update_failures<<", mode failures="<<mode_failures<<"\n";
}

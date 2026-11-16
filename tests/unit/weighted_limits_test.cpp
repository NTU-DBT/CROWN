#include "weighted_bag_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/api/error.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::weighted_test;

template<class Action>
void error(Action action, std::string_view code) {
  try {action();}
  catch (const Error& failure) {check(failure.code()==code,"unexpected error: "+failure.code());return;}
  throw std::runtime_error("expected error "+std::string(code));
}

// The configured maximum applies to stored sums and products. Failed arithmetic
// must restore rows, numeric caches, separator messages and committed sequence.
void overflow(bool indexed) {
  w::Options opts;opts.multiplicity_limit=100;
  Model model(path(indexed),opts);
  model.set(0,{n(1),n(10)},10);model.set(1,{n(10),n(20)},5);
  model.set(2,{n(20)},2);
  const auto expected=recompute(model.runtime.structural_program(),model.inputs);
  error([&]{static_cast<void>(model.runtime.apply({model.runtime.sequence()+1,
      {NodeId{2},{n(20)},{2},{3}}}));},"annotation_overflow");
  compare(model.runtime.snapshot(),expected);
  check(model.runtime.ready() && model.runtime.sequence()==3,"overflow published sequence");
  check(model.runtime.last_attempt()->phase==w::Phase::aborted,"missing failed arithmetic attempt");
  // Unsupported products return zero before multiplication, even when the
  // other local factor would overflow a partially evaluated product.
  Model zero(path(indexed),opts);
  zero.set(0,{n(1),n(10)},100);zero.set(1,{n(10),n(20)},100);
  check(zero.runtime.root_weight().value==0,"known-zero product overflowed");
  Model sums(unary(indexed),opts);sums.set(0,{n(1)},90);
  error([&]{static_cast<void>(sums.runtime.apply({2,{NodeId{0},{n(2)},{0},{11}}}));},"annotation_overflow");
  compare(sums.runtime.snapshot(),recompute(sums.runtime.structural_program(),sums.inputs));
  sums.set(0,{n(1)},100);
  error([&]{static_cast<void>(sums.runtime.apply({3,{NodeId{0},{n(1)},{100},{101}}}));},"annotation_overflow");
  sums.set(0,{n(1)},0);
}

void setup(Model& model) {
  for (std::int64_t z=0;z<4;++z) model.set(1,{n(1),n(7),n(z)},static_cast<std::uint64_t>(z+2));
  model.set(3,{n(1)},5);model.set(2,{n(7)},3);
}

bool stage_input(runtime::WeightedRuntime::PendingEpoch& pending, const w::Replacement& input, bool contribution) {
  if (contribution) return pending.stage_contribution(input.node,
      storage::TupleValuesView::borrow(input.values),input.before,input.after);
  return pending.stage(input);
}

// One work budget funds the whole private logical epoch. The threshold is
// derived from observed operations, then replayed exactly and one below.
void work_limit(bool indexed, bool contribution) {
  Model measured(fanout(indexed));setup(measured);
  auto measurement=measured.runtime.begin_epoch(7);
  static_cast<void>(stage_input(measurement,{NodeId{2},{n(7)},{3},{7}},contribution));
  static_cast<void>(stage_input(measurement,{NodeId{2},{n(7)},{7},{9}},contribution));
  const auto work=measurement.commit().metrics.work;
  check(work>0,"empty measured work");
  w::Options opts;opts.work_limit=work;
  Model exact(fanout(indexed),opts);setup(exact);
  auto success=exact.runtime.begin_epoch(7);
  static_cast<void>(stage_input(success,{NodeId{2},{n(7)},{3},{7}},contribution));
  static_cast<void>(stage_input(success,{NodeId{2},{n(7)},{7},{9}},contribution));
  check(success.commit().metrics.work==work,"exact work threshold differs");
  exact.inputs[2][Row{n(7)}]=9;
  compare(exact.runtime.snapshot(),recompute(exact.runtime.structural_program(),exact.inputs));
  opts.work_limit=work-1;Model below(fanout(indexed),opts);setup(below);
  auto rejected=below.runtime.begin_epoch(7);
  static_cast<void>(stage_input(rejected,{NodeId{2},{n(7)},{3},{7}},contribution));
  error([&]{static_cast<void>(stage_input(rejected,{NodeId{2},{n(7)},{7},{9}},contribution));},"resource_limit");
  compare(below.runtime.snapshot(),recompute(below.runtime.structural_program(),below.inputs));
  check(below.runtime.sequence()==6 && below.runtime.ready(),"work exhaustion did not roll back");
  // Spending one successful stage does not refill the budget for the next.
  auto pending=exact.runtime.begin_epoch(8);
  check(stage_input(pending,{NodeId{2},{n(7)},{9},{10}},contribution),"first budget stage");
  check(stage_input(pending,{NodeId{2},{n(7)},{10},{11}},contribution),"second budget stage");
  error([&]{static_cast<void>(stage_input(pending,{NodeId{2},{n(7)},{11},{12}},contribution));},"resource_limit");
  compare(exact.runtime.snapshot(),recompute(exact.runtime.structural_program(),exact.inputs));
}

// Use a private multi-stage epoch to make its live peak exceed initial runtime
// admission. Native requested bytes include controller/headers/alignment.
std::uint64_t heap_scenario(bool indexed, std::uint64_t cap) {
  w::Options opts;opts.memory_limit_bytes=cap;opts.capture_changes=true;
  runtime::WeightedRuntime runtime(unary(indexed),opts);
  auto pending=runtime.begin_epoch(1);
  for (std::int64_t i=0;i<40;++i)
    static_cast<void>(pending.stage({NodeId{0},{n(i)},{0},{static_cast<std::uint64_t>(i+1)}}));
  static_cast<void>(pending.commit());
  return runtime.accounted_memory_statistics().peak_requested_bytes;
}
void heap_limit(bool indexed) {
  const auto peak=heap_scenario(indexed,256ULL*1024*1024);
  check(heap_scenario(indexed,peak)==peak,"exact requested-byte heap threshold");
  bool rejected=false;
  try {static_cast<void>(heap_scenario(indexed,peak-1));}
  catch (const resource::MemoryFailure& failure) {rejected=failure.fault()==resource::MemoryFault::limit;}
  check(rejected,"one-under heap threshold admitted");
}

std::uint64_t receiving_peak(const CompiledProgram& source, std::uint64_t cap) {
  const auto account=resource::MemoryAccount::create(cap);
  auto sentinel=account.allocate(128);static_cast<void>(sentinel);
  w::Options opts;opts.memory_limit_bytes=UINT64_MAX;
  auto runtime=runtime::WeightedRuntime::create_into(account,source,opts);
  auto pending=runtime.begin_epoch(1);
  for (std::int64_t i=0;i<20;++i) {
    const Row row{n(i)};
    static_cast<void>(pending.stage_contribution(NodeId{0},storage::TupleValuesView::borrow(row),
        {0},{static_cast<std::uint64_t>(i+1)}));
  }
  static_cast<void>(pending.commit());
  return account.statistics().peak_requested_bytes;
}

// The receiver's existing bytes consume the same cap as imported metadata and
// updates. An empty receiver must reject before any replacement-new request.
void receiving_limits(bool indexed) {
  const auto plan=unary(indexed);const auto source=CompiledProgram::standalone(plan);
  const auto source_before=source.account().statistics();
  for (const bool native:{false,true}) {
    bool rejected=false;std::size_t calls=0;
    {
      s04_alloc::Scope fail(0);
      try {
        if (native) static_cast<void>(runtime::WeightedRuntime::create_into({},source));
        else static_cast<void>(runtime::WeightedRuntime::create_into({},plan));
      } catch (const resource::MemoryFailure& failure) {rejected=failure.fault()==resource::MemoryFault::contract;}
      calls=s04_alloc::calls;
    }
    check(rejected && calls==0,"empty receiver minted an account or allocated");
  }
  const auto peak=receiving_peak(source,8ULL*1024*1024);
  check(receiving_peak(source,peak)==peak,"exact receiving cap did not reproduce");
  bool below=false;
  try {static_cast<void>(receiving_peak(source,peak-1));}
  catch (const resource::MemoryFailure& failure) {below=failure.fault()==resource::MemoryFault::limit;}
  check(below,"one-under receiving cap admitted");

  const auto account=resource::MemoryAccount::create(8ULL*1024*1024);
  auto sentinel=account.allocate(128);const auto baseline=account.statistics().current;
  std::size_t allocations=0;
  {
    s04_alloc::Scope count;
    auto runtime=runtime::WeightedRuntime::create_into(account,source);
    allocations=s04_alloc::calls;
  }
  check(allocations>0 && account.statistics().current==baseline,"receiving measurement retained state");
  for (std::size_t cut=0;cut<allocations;++cut) {
    bool rejected=false;
    {
      s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));
      try {static_cast<void>(runtime::WeightedRuntime::create_into(account,source));}
      catch (const std::bad_alloc&) {rejected=true;}
    }
    check(rejected && s04_alloc::triggered,"receiving allocation cut was not observed");
    check(account.statistics().current==baseline,"failed receiving import released sentinel or leaked");
  }
  check(source.account().statistics()==source_before,"receiving limits changed compiler account");
  std::cout<<"receiving cuts backend="<<(indexed ? "indexed" : "ordered")
      <<" count="<<allocations<<" peak="<<peak<<'\n';
}

// Inject at every allocation in a real transaction. Each failure must preserve
// the direct reference state, projected factors and bag outputs, permit retry
// and release all private ownership. Reference joins run outside injection.
void allocation_cuts(bool indexed, bool capture, bool creation, bool contribution) {
  w::Options opts;opts.capture_events=capture;
  auto initial=[&](Model& model) {
    setup(model);
    if (creation) {model.set(2,{n(7)},0);model.set(3,{n(1)},0);}
  };
  Model baseline(fanout(indexed),opts);initial(baseline);
  const auto sequence=baseline.runtime.sequence()+1;
  const w::Replacement a{NodeId{2},{n(7)},{creation ? 0U : 3U},{creation ? 3U : 0U}},
      b{NodeId{3},{n(1)},{creation ? 0U : 5U},{9}};
  std::size_t allocations=0;
  {
    s04_alloc::Scope count;
    auto pending=baseline.runtime.begin_epoch(sequence);
    static_cast<void>(stage_input(pending,a,contribution));static_cast<void>(stage_input(pending,b,contribution));
    allocations=s04_alloc::calls;
    pending.rollback();
  }
  check(allocations>0,"empty allocation-cut scenario");
  for (std::size_t cut=0;cut<allocations;++cut) {
    Model model(fanout(indexed),opts);initial(model);
    const auto expected=recompute(model.runtime.structural_program(),model.inputs);
    bool rejected=false;
    {
      s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));
      try {
        auto pending=model.runtime.begin_epoch(sequence);
        static_cast<void>(stage_input(pending,a,contribution));static_cast<void>(stage_input(pending,b,contribution));
        static_cast<void>(pending.commit());
      } catch (const std::bad_alloc&) {rejected=true;}
    }
    check(rejected && s04_alloc::triggered,"allocation cut was not observed");
    check(model.runtime.ready() && model.runtime.sequence()==sequence-1,"failed allocation published state");
    compare(model.runtime.snapshot(),expected);
    compare_bag(model.runtime,model.inputs);
    model.set(2,{n(7)},a.after.value);model.set(3,{n(1)},9);model.set(2,{n(7)},2);
    compare_bag(model.runtime,model.inputs);
  }
  // Commit and explicit rollback themselves allocate nothing after stage.
  for (const bool commit:{false,true}) {
    Model model(fanout(indexed),opts);initial(model);
    auto pending=model.runtime.begin_epoch(sequence);static_cast<void>(stage_input(pending,a,contribution));
    std::size_t calls=0;
    {s04_alloc::Scope fail(0);if (commit) static_cast<void>(pending.commit());else pending.rollback();calls=s04_alloc::calls;}
    check(calls==0,"publication/rollback allocated");
  }
  std::cout<<"allocation cuts backend="<<(indexed ? "indexed" : "ordered")
      <<" capture="<<capture<<" creation="<<creation<<" contribution="<<contribution<<" count="<<allocations<<'\n';
}

void retention_and_churn(bool indexed) {
  resource::MemoryAccount account;w::Snapshot retained;
  {
    runtime::WeightedRuntime runtime(unary(indexed));account=runtime.structural_program().account();
    static_cast<void>(runtime.apply({1,{NodeId{0},{n(1)},{0},{1}}}));
    const auto baseline=runtime.accounted_memory_statistics().current.requested_bytes;
    for (std::uint64_t i=2;i<130;++i) {
      static_cast<void>(runtime.apply({i,{NodeId{0},{n(1)},{i-1},{i}}}));
      check(runtime.accounted_memory_statistics().current.requested_bytes==baseline,"numeric churn retained metadata");
    }
    retained=runtime.snapshot();
    const auto capture_bytes=runtime.accounted_memory_statistics().by_purpose[
        static_cast<std::size_t>(resource::MemoryPurpose::capture)].requested_bytes;
    check(capture_bytes>0,"snapshot escaped capture accounting");
  }
  check(retained.root.value==129 && account.statistics().current.requested_bytes>resource::MemoryAccount::control_bytes(),
      "owning snapshot failed to retain original account");
  retained={};
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"retention leaked native allocations");
}

// Establish an actual native structural-work threshold over many resumed
// stages and a private capture. One below must fail under that same grant.
std::uint64_t native_grant_scenario(std::optional<std::uint64_t> limit, bool reject, bool contribution) {
  Model model(fanout(true,limit));setup(model);
  const auto expected=recompute(model.runtime.structural_program(),model.inputs);
  auto pending=model.runtime.begin_epoch(7);std::uint64_t previous=0;bool rejected=false;
  try {
    for (std::uint64_t weight=4;weight<68;++weight) {
      static_cast<void>(stage_input(pending,{NodeId{2},{n(7)},{weight-1},{weight}},contribution));
      const auto spent=pending.preview().metrics.native_grant_consumed.structural_steps;
      check(spent>previous,"resumed stage refilled native grant");previous=spent;
    }
    const auto capture=pending.snapshot();static_cast<void>(capture);
    check(pending.preview().metrics.native_grant_consumed.structural_steps>previous,"private capture used a fresh grant");
  } catch (const storage::IndexFailure& failure) {
    check(failure.code()=="storage_work_limit","unexpected native grant rejection");
    rejected=true;pending.rollback();
  }
  check(rejected==reject,"native grant threshold disagreed");
  if (rejected) {
    compare(model.runtime.snapshot(),expected);
    check(model.runtime.sequence()==6 && model.runtime.ready(),"native grant rejection published state");return 0;
  }
  const auto epoch=pending.commit();model.inputs[2][Row{n(7)}]=67;
  compare(model.runtime.snapshot(),recompute(model.runtime.structural_program(),model.inputs));
  return epoch.metrics.native_grant_consumed.structural_steps;
}
void native_grant() {
  const auto work=native_grant_scenario({},false,false);
  for (const bool contribution:{false,true}) {
    check(native_grant_scenario(work,false,contribution)==work,"exact native structural grant threshold");
    static_cast<void>(native_grant_scenario(work-1,true,contribution));
  }
}
} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      overflow(indexed);heap_limit(indexed);receiving_limits(indexed);
      for (const bool contribution:{false,true}) {
        work_limit(indexed,contribution);
        for (const bool capture:{false,true}) for (const bool creation:{false,true})
          allocation_cuts(indexed,capture,creation,contribution);
      }
      retention_and_churn(indexed);
    }
    native_grant();
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}

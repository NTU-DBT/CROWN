#include "weighted_bag_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/api/error.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::weighted_test;

template<class Action> void error(Action action, std::string_view code) {
  try {action();}
  catch (const Error& failure) {check(failure.code()==code,"unexpected weighted error: "+failure.code());return;}
  throw std::runtime_error("expected "+std::string(code));
}

// Allocation injection is outside the reference/checking work. Startup must
// publish no reader on failure; next failure must release every borrowed row.
void allocation_cuts(bool indexed, bool startup, bool later) {
  Model baseline(typed_bag(indexed));typed_inputs(baseline);
  std::size_t allocations=0;
  if (startup) {
    s04_alloc::Scope count;auto cursor=baseline.runtime.results();allocations=s04_alloc::calls;
  } else {
    auto cursor=baseline.runtime.results();
    if (later) {static_cast<void>(cursor.next());static_cast<void>(cursor.next());}
    s04_alloc::Scope count;static_cast<void>(cursor.next());allocations=s04_alloc::calls;
  }
  check(allocations>0,"empty cursor allocation sweep");
  for (std::size_t cut=0;cut<allocations;++cut) {
    Model model(typed_bag(indexed));typed_inputs(model);
    bool rejected=false;
    if (startup) {
      {s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));
        try {auto cursor=model.runtime.results();}catch (const std::bad_alloc&) {rejected=true;}}
    } else {
      auto cursor=model.runtime.results();std::optional<w::Result> retained;
      if (later) {retained=cursor.next();static_cast<void>(cursor.next());}
      {s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(cut));
        try {static_cast<void>(cursor.next());}catch (const std::bad_alloc&) {rejected=true;}}
      check(cursor.state()==w::CursorState::failed && !cursor.active(),"failed next retained reader");
      error([&]{static_cast<void>(cursor.next());},"invalid_cursor");
      if (retained) check(!storage::export_row(retained->tuple.values()).empty(),"prior row lost ownership");
    }
    check(rejected && s04_alloc::triggered,"cursor allocation failure not observed");
    check(model.runtime.ready(),"cursor failure left runtime busy");
    compare_bag(model.runtime,model.inputs);
    model.set(1,{n(7),Value{true}},7);
  }
  std::cout<<"cursor allocation cuts backend="<<(indexed?"indexed":"ordered")
      <<" startup="<<startup<<" later="<<later<<" count="<<allocations<<'\n';
}

void work_limit(bool indexed) {
  Model model(typed_bag(indexed));typed_inputs(model);
  auto measured=model.runtime.results();static_cast<void>(drain(measured));
  const auto budget=measured.metrics().work;
  auto exact=model.runtime.results({budget});static_cast<void>(drain(exact));
  check(exact.metrics().work==budget,"cursor exact cumulative work differs");
  auto below=model.runtime.results({budget-1});
  error([&]{static_cast<void>(drain(below));},"resource_limit");
  check(below.state()==w::CursorState::failed && model.runtime.ready(),"work failure retained reader");
  error([&]{static_cast<void>(model.runtime.results({0}));},"resource_limit");
  check(model.runtime.ready(),"failed startup published reader");
  const auto short_budget=measured.metrics().startup_work+measured.metrics().max_result_work;
  auto cumulative=model.runtime.results({short_budget});
  check(cumulative.next().has_value(),"first cumulative-budget row failed");
  error([&]{static_cast<void>(drain(cumulative));},"resource_limit");
  check(model.runtime.ready(),"next calls refilled cursor budget");
  compare_bag(model.runtime,model.inputs);
}

// Many compressed outputs with small maintained inputs make the complete
// cursor grant larger than plan admission/update growth, so exact/one-under
// tests isolate one retained cursor grant rather than an earlier setup limit.
std::uint64_t native_grant(std::optional<std::uint64_t> limit, bool reject) {
  runtime::WeightedRuntime runtime(disconnected_bag(true,limit));std::uint64_t sequence=0;
  for (std::size_t node=1;node<=2;++node) for (std::int64_t value=0;value<64;++value)
    static_cast<void>(runtime.apply({++sequence,{NodeId{node},{n(value)},{0},{1}}}));
  auto cursor=runtime.results();std::uint64_t rows=0,previous=0;bool rejected=false;
  try {
    while (auto row=cursor.next()) {
      check(row->multiplicity.value==1,"disconnected output multiplicity");++rows;
      const auto spent=cursor.metrics().native_grant_consumed.structural_steps;
      check(spent>previous,"cursor next refilled original native grant");previous=spent;
    }
  } catch (const storage::IndexFailure& failure) {
    check(failure.code()=="storage_work_limit","unexpected cursor native failure");rejected=true;
  }
  check(rejected==reject && runtime.ready(),"native cursor grant threshold/lease");
  if (reject) check(cursor.state()==w::CursorState::failed,"native failure cursor state");
  else check(rows==4096,"disconnected compressed output count");
  check(runtime.root_weight().value==4096,"native cursor failure changed query state");
  return cursor.metrics().native_grant_consumed.structural_steps;
}

std::uint64_t heap_scenario(bool indexed, std::uint64_t limit) {
  w::Options options;options.memory_limit_bytes=limit;
  Model model(typed_bag(indexed),options);typed_inputs(model,24);
  auto cursor=model.runtime.results();std::vector<w::Result> retained;
  while (auto row=cursor.next()) retained.push_back(std::move(*row));
  check(retained.size()==48,"heap fixture compressed output size");
  return model.runtime.accounted_memory_statistics().peak_requested_bytes;
}
void heap_limit(bool indexed) {
  const auto peak=heap_scenario(indexed,256ULL*1024*1024);
  check(heap_scenario(indexed,peak)==peak,"cursor exact requested-byte heap");
  bool rejected=false;
  try {static_cast<void>(heap_scenario(indexed,peak-1));}
  catch (const resource::MemoryFailure& failure) {rejected=failure.fault()==resource::MemoryFault::limit;}
  check(rejected,"cursor one-under heap admitted");
}

void rollback_factors(bool indexed) {
  w::Options options;options.multiplicity_limit=100;
  BagModel model(counted_path(indexed),options);
  model.set(0,{n(1),n(7),n(9)},5);model.set(1,{n(7),n(10)},2);
  auto pending=model.runtime.begin_epoch(3);
  static_cast<void>(pending.stage({NodeId{0},{n(1),n(7),n(9)},{5},{10}}));
  error([&]{static_cast<void>(pending.stage({NodeId{1},{n(7),n(10)},{2},{11}}));},"annotation_overflow");
  check(!pending.active() && model.runtime.sequence()==2,"factor epoch overflow published state");
  compare_bag(model.runtime,model.inputs);
}

void release_and_churn(bool indexed) {
  resource::MemoryAccount account;std::optional<runtime::WeightedRuntime::ResultCursor> cursor;
  std::optional<w::Result> row;
  {
    Model model(typed_bag(indexed));typed_inputs(model);account=model.runtime.structural_program().account();
    const auto baseline=account.statistics().current.requested_bytes;
    for (unsigned iteration=0;iteration<64;++iteration) {
      {auto transient=model.runtime.results();static_cast<void>(transient.next());
        std::size_t calls=0;
        {s04_alloc::Scope fail(0);transient.cancel();calls=s04_alloc::calls;}
        check(calls==0,"cursor cancel allocated");}
      check(account.statistics().current.requested_bytes==baseline,"cursor churn retained history");
    }
    cursor.emplace(model.runtime.results());
  }
  row=cursor->next();check(row.has_value(),"cursor failed after facade destruction");
  cursor->cancel();cursor.reset();
  check(!storage::export_row(row->tuple.values()).empty(),"emitted row failed after cursor release");
  row.reset();
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"cursor/output owner leak");
  Model a(unary(indexed)),b(unary(indexed));a.set(0,{n(1)},2);b.set(0,{n(2)},3);
  auto first=a.runtime.results(),second=b.runtime.results();first=std::move(second);
  check(a.runtime.ready() && !b.runtime.ready() && first.owner()==b.runtime.owner(),"cross-owner cursor move assignment");
  first.cancel();check(b.runtime.ready(),"move-assigned cursor leaked reader");
}
} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      allocation_cuts(indexed,true,false);allocation_cuts(indexed,false,false);allocation_cuts(indexed,false,true);
      work_limit(indexed);heap_limit(indexed);rollback_factors(indexed);release_and_churn(indexed);
    }
    const auto work=native_grant({},false);
    check(native_grant(work,false)==work,"exact native cursor grant differs");
    static_cast<void>(native_grant(work-1,true));
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}

#include "reoptimization_detail.hpp"
#include "selection_independent_fixture.hpp"
#include <array>
#include <iostream>
#include <limits>

namespace crown::runtime::reoptimization::detail {
struct ClockCounterTestAccess {
  static void saturate(State& state) noexcept {
    state.status_.clock_reads=std::numeric_limits<std::uint64_t>::max();
  }
};
}

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
namespace reopt=reoptimization;

Relation answers(DeltaRuntime& source) {
  Relation result;
  auto cursor=source.core_results();
  while(auto tuple=cursor.next_native())result.insert(storage::export_row(tuple->values()));
  return result;
}

void cancelled_clock_does_no_more_work(bool verify) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},
      {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  const auto family=c05_independent::candidates(catalog,query);
  const auto candidate=family.candidate(0);
  check(candidate.has_value(),"counter fixture has no checked candidate");
  const Database initial{{Relation{Row{std::int64_t{7}}}}};
  auto source=DeltaRuntime::initialize(planner::lower_tree(catalog,query,tree),initial);
  const auto owner=source.owner();
  const auto before=answers(source);
  reopt::detail::State state(source,*candidate,{},std::nullopt,
      reopt::detail::State::Clock::now());
  if(verify)state.request_barrier();
  reopt::detail::ClockCounterTestAccess::saturate(state);
  const auto account=source.plan().account();
  const auto allocations=account.statistics().successful_allocations;
  const std::array<storage::ScalarView,1> values{std::int64_t{8}};
  if(verify)state.verify(source);
  else state.stage(source,{1,TableId{0},SetOperation::insert,
      storage::TupleValuesView::borrow(storage::RowView::borrow(values))});
  check(account.statistics().successful_allocations==allocations,
      "cancelled clock continued allocating candidate work");
  const auto status=state.status();
  check(!state.active() && status.phase==reopt::Phase::failed &&
      status.stop==reopt::Stop::counter_overflow && !status.admission_frozen &&
      status.backlog_records==0 && status.staging_work==0 &&
      status.clock_reads==std::numeric_limits<std::uint64_t>::max(),
      "clock cancellation did not preserve its terminal state");
  check(source.owner()==owner && source.sequence()==0 && source.ready() && answers(source)==before,
      "candidate clock cancellation changed the current owner");
  auto epoch=source.apply({1,TableId{0},SetOperation::insert,Row{std::int64_t{8}}});
  epoch.discard();
  check(source.sequence()==1 && answers(source)==Relation{Row{std::int64_t{7}},Row{std::int64_t{8}}},
      "current owner could not continue after candidate clock cancellation");
}
}

int main() {
  try {
    cancelled_clock_does_no_more_work(false);
    cancelled_clock_does_no_more_work(true);
    std::cout<<"clock counter cancellation preserves the old owner and allocates no further candidate state\n";
  }catch(const std::exception& failure) {
    std::cerr<<failure.what()<<'\n';return 1;
  }
}

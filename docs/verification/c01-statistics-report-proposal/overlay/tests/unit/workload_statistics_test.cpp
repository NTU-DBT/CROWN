#include "workload_statistics_fixture.hpp"
#include "statistics_collection.hpp"
#include "workload_statistics_detail.hpp"
#include <iostream>
#include <sstream>
#include <thread>
#include <type_traits>

namespace crown::runtime::statistics_collection {
struct CollectorTestAccess {
  static void saturate(Collector& collector) {
    for (auto& cell:collector.committed_) {
      cell.inputs=UINT64_MAX; cell.complete_detail_inputs=UINT64_MAX; cell.count=UINT64_MAX;
      cell.changes=UINT64_MAX; cell.visited=UINT64_MAX; cell.accepted=UINT64_MAX;
      cell.zero_to_positive=UINT64_MAX; cell.positive_to_zero=UINT64_MAX; cell.saturated=true;
    }
  }
};
}
namespace crown::runtime::workload::detail {
struct StateTestAccess {
  static void saturate(State& state) { statistics_collection::CollectorTestAccess::saturate(state.collector_); }
};
}

namespace {
using namespace workload_fixture;
// The oracle stores raw physical sets and independently recomputes literal
// R(x,y) AND S(y) membership. It never reads an O07 trace or runtime journal.
struct Expected {
  ws::Cell counters;
  void observe(std::uint64_t value) {
    if (counters.count==0) counters.min=counters.max=value;
    else { counters.min=std::min(counters.min,value); counters.max=std::max(counters.max,value); }
    ++counters.count; counters.sum+=value;
    std::size_t bin=0; for (auto remaining=value;remaining!=0;remaining/=2) ++bin;
    ++counters.bins[bin];
  }
  void support(std::uint64_t before,std::uint64_t after) {
    if (before==after) return;
    ++counters.changes; if (!before) ++counters.zero_to_positive; if (!after) ++counters.positive_to_zero;
    observe(after);
  }
};
void literal_hand_trace() {
  const auto compiled=plan(); DeltaRuntime runtime(compiled,delta_options()); runtime.configure_workload_statistics(enabled());
  auto definition=runtime.workload_statistics(); std::vector<Expected> expected(definition.cells().size());
  std::array<Relation,3> sources;
  std::array<std::map<Row,std::uint64_t>,2> parent,visible;
  const auto survivors=[&]() {
    std::array<Relation,2> result; result[1]=sources[1];
    for (const auto& row:sources[0]) if (sources[1].contains(Row{row[1]})) result[0].insert(row);
    return result;
  };
  struct Event { std::size_t table; SetOperation op; Row row; };
  const auto add=SetOperation::insert, remove=SetOperation::erase;
  const std::vector<Event> events={
    {0,add,{n(1),n(7)}},{0,add,{n(2),n(7)}},{0,add,{n(1),n(8)}},
    {1,add,{n(7)}},{1,add,{n(9)}},{1,add,{n(7)}},{1,add,{n(8)}},
    {0,add,{n(4),n(8)}},{1,remove,{n(7)}},{1,remove,{n(9)}},
    {0,remove,{n(4),n(8)}},{1,remove,{n(8)}},{1,remove,{n(8)}},{2,add,{n(99)}}};
  for (const auto& event:events) {
    const auto before=survivors(); const bool insertion=event.op==add;
    const bool changed=insertion?sources[event.table].insert(event.row).second:sources[event.table].erase(event.row)!=0;
    auto& input=expected[find(definition,event.table,event.op,ws::Role::input)].counters;
    ++input.inputs; ++input.complete_detail_inputs; if (changed) ++input.changed; else ++input.noop;
    if (changed && event.table<2) {
      const auto occurrence=OccurrenceId{event.table};
      auto& adapter=expected[find(definition,event.table,event.op,ws::Role::adapter,{},occurrence)].counters;
      ++adapter.visited; ++adapter.accepted;
      expected[find(definition,event.table,event.op,ws::Role::derivation,{},occurrence)].support(insertion?0:1,insertion?1:0);
      if (event.table==1) {
        std::uint64_t degree=0;
        for (const auto& row:sources[0]) if (row[1]==event.row[0]) ++degree;
        expected[find(definition,event.table,event.op,ws::Role::native_touched_degree,{}, {},0,
            insertion?ws::Operation::insert:ws::Operation::erase)].observe(degree);
      }
      const auto after=survivors();
      for (std::size_t node=0;node<2;++node) {
        const auto& changed_rows=insertion?after[node]:before[node];
        const auto& unchanged_rows=insertion?before[node]:after[node];
        for (const auto& row:changed_rows) if (!unchanged_rows.contains(row)) {
          expected[find(definition,event.table,event.op,ws::Role::survivor,NodeId{node})].support(insertion?0:1,insertion?1:0);
          const auto count=[&](auto& counts,Row key,ws::Role role) {
            const auto old=counts[key]; const auto next=insertion?old+1:old-1;
            expected[find(definition,event.table,event.op,role,NodeId{node})].support(old,next);
            if (next) counts[key]=next; else counts.erase(key);
          };
          count(parent[node],node==0?Row{}:Row{row[0]},ws::Role::parent_support);
          if (node==0) count(visible[node],Row{row[0]},ws::Role::visible_support);
        }
      }
    }
    apply(runtime,event.table,event.op,event.row);
    const auto snapshot=runtime.workload_statistics();
    check(snapshot.stamp().owner==runtime.owner() && snapshot.stamp().committed_epoch==runtime.sequence());
    check(snapshot.detail_availability()==ws::Availability::exact && !snapshot.pending());
    for (std::size_t i=0;i<expected.size();++i) check(snapshot.cells()[i]==expected[i].counters);
    const auto actual=runtime.snapshot();
    for (std::size_t i=0;i<3;++i) check(actual.physical.tables[i]==sources[i]);
    runtime.check_invariants();
  }
  const auto report=runtime.workload_statistics();
  const auto root=find(report,0,add,ws::Role::input);
  const auto share=report.input_share(root); check(share.numerator==4 && share.denominator==events.size() && share.availability==ws::Availability::exact);
  const auto degree=find(report,1,add,ws::Role::native_touched_degree,{}, {},0,ws::Operation::insert);
  const auto per_input=report.events_per_physical_input(degree);
  check(per_input.numerator==3 && per_input.denominator==4 && per_input.availability==ws::Availability::exact);
  check(report.cells()[degree].count==3 && report.cells()[degree].sum==3 && report.cells()[degree].bins[0]==1);
  const auto crossings=report.crossing_fraction(find(report,1,add,ws::Role::parent_support,NodeId{0}));
  check(crossings.numerator==1 && crossings.denominator==3);
  const auto selectivity=report.adapter_selectivity(find(report,1,add,ws::Role::adapter,{},OccurrenceId{1}));
  check(selectivity.numerator==3 && selectivity.denominator==3);
  check(report.arrival_per_second()==ws::Availability::unavailable);
  const auto& bytes=report.memory();
  check(bytes.retained_payload_bytes==bytes.descriptors_bytes+bytes.routes_bytes+bytes.committed_bytes+bytes.attempt_bytes+bytes.previous_bytes);
  check(bytes.committed_bytes==bytes.attempt_bytes && bytes.attempt_bytes==bytes.previous_bytes);
}
void projection_aliases_and_generalized() {
  PhysicalRuntimeOptions options; options.support.observation.mode=ObservationMode::off;
  PhysicalRuntime runtime(plan(true),options); runtime.configure_workload_statistics(enabled());
  for (const auto& event:std::vector<PhysicalSetUpdate>{{1,{0},SetOperation::insert,{n(1),n(7),n(10)}},
      {2,{0},SetOperation::insert,{n(1),n(7),n(11)}},{3,{0},SetOperation::insert,{n(1),n(7),n(11)}},
      {4,{0},SetOperation::erase,{n(1),n(7),n(10)}},{5,{0},SetOperation::erase,{n(1),n(7),n(11)}},
      {6,{0},SetOperation::erase,{n(1),n(7),n(11)}}}) static_cast<void>(runtime.apply(event));
  auto report=runtime.workload_statistics();
  const auto& ins=cell(report,0,SetOperation::insert,ws::Role::derivation,{},OccurrenceId{0});
  const auto& del=cell(report,0,SetOperation::erase,ws::Role::derivation,{},OccurrenceId{0});
  check(ins.changes==2 && ins.zero_to_positive==1 && ins.sum==3);
  check(del.changes==2 && del.positive_to_zero==1 && del.sum==1);
  check(cell(report,0,SetOperation::insert,ws::Role::input).noop==1);
  check(cell(report,0,SetOperation::erase,ws::Role::input).noop==1);
  PhysicalRuntime aliases(alias_plan(true),options); aliases.configure_workload_statistics(enabled());
  static_cast<void>(aliases.apply({1,{0},SetOperation::insert,{n(1),n(7),n(0)}}));
  static_cast<void>(aliases.apply({2,{0},SetOperation::insert,{n(1),n(7),n(1)}}));
  report=aliases.workload_statistics();
  const auto& left=cell(report,0,SetOperation::insert,ws::Role::adapter,{},OccurrenceId{0});
  const auto& right=cell(report,0,SetOperation::insert,ws::Role::adapter,{},OccurrenceId{1});
  check(left.visited==2 && left.accepted==2 && right.visited==2 && right.accepted==1 && right.rejected==1);
  std::uint64_t generalized=0, absent=0, present=0;
  for (std::size_t i=0;i<report.descriptors().size();++i) {
    const auto& d=report.descriptors()[i]; check(d.role!=ws::Role::native_touched_degree);
    if (d.role==ws::Role::generalized_probe) { generalized+=report.cells()[i].count; absent+=report.cells()[i].bins[0]; present+=report.cells()[i].bins[1]; }
  }
  check(generalized==2 && absent==1 && present==1);
  aliases.check_invariants();
  // One physical row fans out to two child events: this must stay a multiset.
  PhysicalRuntime same(alias_plan(),options); same.configure_workload_statistics(enabled());
  static_cast<void>(same.apply({1,{0},SetOperation::insert,{n(3),n(4),n(1)}}));
  report=same.workload_statistics(); generalized=0;
  for (std::size_t i=0;i<report.descriptors().size();++i)
    if (report.descriptors()[i].role==ws::Role::generalized_probe) generalized+=report.cells()[i].count;
  check(generalized==2 && report.metadata().committed==1);
}
void lower_scope_and_barriers() {
  SupportOptions options; options.observation.mode=ObservationMode::off;
  SupportRuntime runtime(plan(),options); runtime.configure_workload_statistics(enabled());
  auto pending=runtime.begin_epoch(1,SetOperation::insert);
  check(pending.stage({0},{n(1),n(7)})); check(pending.stage({1},{n(7)}));
  auto before=runtime.workload_statistics(); check(before.pending() && before.metadata().committed==0);
  error([&] { runtime.configure_workload_statistics(enabled()); },"runtime_busy");
  error([&] { runtime.reset_workload_statistics(); },"runtime_busy");
  static_cast<void>(pending.commit());
  auto report=runtime.workload_statistics(); check(report.metadata().committed==1);
  std::uint64_t logical=0;
  for (std::size_t i=0;i<report.descriptors().size();++i) {
    const auto& d=report.descriptors()[i]; check(d.input_scope==ws::InputScope::logical_epoch && !d.initiating_table());
    check(d.kind!=ws::Kind::physical); if (d.kind==ws::Kind::logical) logical+=report.cells()[i].inputs;
    check(report.input_share(i).availability==ws::Availability::unavailable);
    check(report.events_per_physical_input(i).availability==ws::Availability::unavailable);
  }
  check(logical==1);
  auto cursor=runtime.results();
  error([&] { runtime.reset_workload_statistics(); },"runtime_busy");
  error([&] { runtime.configure_workload_statistics(enabled()); },"runtime_busy");
  cursor.cancel(); runtime.reset_workload_statistics();
  check(runtime.workload_statistics().stamp().reset_generation==report.stamp().reset_generation+1);
  check(report.metadata().committed==1 && report.stamp().committed_epoch==1);
  auto moved=std::move(runtime); check(moved.workload_statistics().stamp().owner==report.stamp().owner);
}
void native_touched_event_multiset() {
  const Catalog catalog{1,{{"R",{{"a",ScalarType::int64},{"x",ScalarType::int64}}},
      {"T",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},{"S",{{"y",ScalarType::int64}}}}};
  const Query query{{{"a",ScalarType::int64},{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"R",{0},{VariableId{0},VariableId{1}}},{"T",{1},{VariableId{1},VariableId{2}}},{"S",{2},{VariableId{2}}}},
      {{VariableId{0},"a"}},false};
  const auto compiled=planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
       {"t",NodeKind::native,{VariableId{1},VariableId{2}},{NodeId{2}},1,{}},
       {"s",NodeKind::native,{VariableId{2}},{},2,{}}},{},{}});
  DeltaRuntime runtime(compiled,delta_options());
  const std::vector<Row> parents={{n(1),n(10)},{n(2),n(10)},{n(3),n(11)}};
  std::map<Value,std::uint64_t> degrees;
  for (const auto& row:parents) { ++degrees[row[1]]; apply(runtime,0,SetOperation::insert,row); }
  for (const auto key:{10,11,12}) apply(runtime,1,SetOperation::insert,{n(key),n(7)});
  runtime.configure_workload_statistics(enabled()); apply(runtime,2,SetOperation::insert,{n(7)});
  const auto report=runtime.workload_statistics();
  std::size_t edge=0; for (;edge<compiled.edges().size();++edge)
    if (compiled.edges()[edge].parent==NodeId{0} && compiled.edges()[edge].child==NodeId{1}) break;
  check(edge<compiled.edges().size());
  const auto id=find(report,2,SetOperation::insert,ws::Role::native_touched_degree,{}, {},edge,ws::Operation::insert);
  Expected expected; for (const auto key:{10,11,12}) expected.observe(degrees[n(key)]);
  check(report.cells()[id]==expected.counters);
  const auto rate=report.events_per_physical_input(id);
  check(rate.numerator==3 && rate.denominator==1 && report.cells()[id].bins[0]==1);
  // A skewed event multiset differs from the two nonempty keys' uniform mean.
  DeltaRuntime weighted(plan(),delta_options());
  for (const auto& row:std::vector<Row>{{n(1),n(7)},{n(2),n(8)},{n(3),n(8)},{n(4),n(8)}})
    apply(weighted,0,SetOperation::insert,row);
  weighted.configure_workload_statistics(enabled());
  for (int i=0;i<3;++i) { apply(weighted,1,SetOperation::insert,{n(7)}); apply(weighted,1,SetOperation::erase,{n(7)}); }
  apply(weighted,1,SetOperation::insert,{n(8)});
  const auto observation=weighted.workload_statistics();
  const auto& touched=cell(observation,1,SetOperation::insert,ws::Role::native_touched_degree,{}, {},0,ws::Operation::insert);
  check(touched.count==4 && touched.sum==6 && touched.bins[1]==3 && touched.bins[2]==1);
}
void sampled_rate_denominators_and_overflow() {
  DeltaRuntime runtime(plan(),delta_options());
  for (const auto& row:std::vector<Row>{{n(1),n(7)},{n(2),n(8)},{n(3),n(8)},{n(4),n(8)},
      {n(5),n(10)},{n(6),n(10)},{n(7),n(10)}}) apply(runtime,0,SetOperation::insert,row);
  runtime.configure_workload_statistics(enabled(2,0,8));
  apply(runtime,1,SetOperation::insert,{n(7)});  // selected degree 1; exactly 8 detail actions
  apply(runtime,1,SetOperation::insert,{n(8)});  // unselected degree 3
  apply(runtime,1,SetOperation::insert,{n(7)});  // selected complete no-op
  apply(runtime,1,SetOperation::insert,{n(9)});  // unselected degree 0
  apply(runtime,1,SetOperation::insert,{n(10)}); // selected, truncated degree 3
  for (int i=0;i<2;++i) {
    auto pending=runtime.begin({runtime.sequence()+1,{1},SetOperation::insert,{n(11)}});
    pending.drain(); pending.rollback(); // unselected then selected abort, same sequence
  }
  apply(runtime,1,SetOperation::insert,{n(11)}); // unselected retry
  apply(runtime,1,SetOperation::insert,{n(7)});  // selected complete no-op
  auto report=runtime.workload_statistics();
  const auto root=find(report,1,SetOperation::insert,ws::Role::input);
  check(report.cells()[root].inputs==7 && report.cells()[root].complete_detail_inputs==3 && report.cells()[root].noop==2);
  check(report.metadata().attempts==9 && report.metadata().aborted==2 && report.metadata().aborted_selected==1);
  check(report.metadata().committed_truncated==1 && report.metadata().complete==3);
  const auto degree=find(report,1,SetOperation::insert,ws::Role::native_touched_degree,{}, {},0,ws::Operation::insert);
  const auto mean=report.events_per_physical_input(degree);
  check(mean.numerator==1 && mean.denominator==3 && mean.availability==ws::Availability::incomplete);
  check(mean.denominator_scope==ws::DenominatorScope::complete_detail_sample_physical_stratum);
  const auto share=report.input_share(root);
  check(share.numerator==7 && share.denominator==7 && share.availability==ws::Availability::exact);
  check(share.denominator_scope==ws::DenominatorScope::all_committed_physical_inputs);
  auto moved=std::move(report); check(moved.metadata().committed==7 && report.metadata().committed==7);
  auto other=moved; other=std::move(moved); check(other.metadata().committed==7 && moved.metadata().committed==7);
  ws::detail::State state; const auto compiled=plan(); state.configure(compiled,true,enabled(),0);
  ws::detail::StateTestAccess::saturate(state);
  const auto overflow=state.snapshot(compiled,SupportOwnerId{42},0);
  const auto input=find(overflow,0,SetOperation::insert,ws::Role::input);
  check(overflow.input_share(input).availability==ws::Availability::unavailable);
  check(overflow.events_per_physical_input(input).availability==ws::Availability::unavailable);
  check(overflow.events_per_physical_input(find(overflow,0,SetOperation::insert,ws::Role::derivation,{},OccurrenceId{0})).availability==ws::Availability::unavailable);
  check(overflow.crossing_fraction(find(overflow,0,SetOperation::insert,ws::Role::parent_support,NodeId{0})).availability==ws::Availability::unavailable);
  check(overflow.adapter_selectivity(find(overflow,0,SetOperation::insert,ws::Role::adapter,{},OccurrenceId{0})).availability==ws::Availability::unavailable);
}
void sample_retry_and_truncation() {
  DeltaRuntime runtime(plan(),delta_options()); runtime.configure_workload_statistics(enabled(2,0));
  auto aborted=runtime.begin({1,{0},SetOperation::insert,{n(1),n(7)}}); aborted.drain();
  const auto staged=runtime.workload_statistics(); check(staged.pending() && staged.metadata().detail_actions>0);
  aborted.rollback();
  apply(runtime,0,SetOperation::insert,{n(1),n(7)});
  auto report=runtime.workload_statistics();
  check(report.metadata().attempts==2 && report.metadata().selected==1 && report.metadata().aborted_selected==1);
  check(report.metadata().committed==1 && report.metadata().complete==0);
  check(cell(report,0,SetOperation::insert,ws::Role::input).inputs==1);
  check(cell(report,0,SetOperation::insert,ws::Role::adapter,{},OccurrenceId{0}).visited==0);
  check(report.detail_availability()==ws::Availability::sampled);
  const auto retained=report;
  for (const auto budget:{std::uint64_t{0},std::uint64_t{1}}) {
    runtime.configure_workload_statistics(enabled(1,0,budget));
    apply(runtime,0,SetOperation::insert,{n(2+static_cast<std::int64_t>(budget)),n(7)});
    report=runtime.workload_statistics(); check(report.metadata().committed_truncated==1);
    check(report.detail_availability()==ws::Availability::incomplete);
    for (std::size_t i=0;i<report.descriptors().size();++i)
      if (report.descriptors()[i].kind!=ws::Kind::physical) check(report.cells()[i]==ws::Cell{});
    check(cell(report,0,SetOperation::insert,ws::Role::input).changed==1);
  }
  auto invalid=enabled(); invalid.period=0;
  bool threw=false; try { runtime.configure_workload_statistics(invalid); } catch (const std::invalid_argument&) { threw=true; }
  check(threw && same_cells(runtime.workload_statistics().cells(),report.cells()));
  invalid=enabled(); invalid.max_cells=1; threw=false;
  try { runtime.configure_workload_statistics(invalid); } catch (const std::length_error&) { threw=true; }
  check(threw && runtime.workload_statistics().stamp().reset_generation==report.stamp().reset_generation);
  runtime.configure_workload_statistics({});
  check(runtime.workload_statistics().memory().retained_payload_bytes==0);
  check(retained.metadata().aborted==1 && retained.stamp().committed_epoch==1);
}
std::uint64_t clock_calls=0;
std::uint64_t clock() noexcept { return ++clock_calls; }
void modes_initialization_and_parity() {
  detail::set_observation_clock_for_testing(&clock);
  const auto compiled=plan(); DeltaRuntime off(compiled,delta_options()), counted(compiled,delta_options());
  counted.configure_workload_statistics(enabled());
  check(off.workload_statistics().memory().retained_payload_bytes==0);
  for (std::size_t i=0;i<2;++i) {
    const Row row=i==0?Row{n(1),n(7)}:Row{n(7)};
    auto a=off.apply({i+1,TableId{i},SetOperation::insert,row});
    auto b=counted.apply({i+1,TableId{i},SetOperation::insert,row});
    for (;;) { auto x=a.next(), y=b.next(); check(x.has_value()==y.has_value()); if (!x) break; check(x->operation==y->operation && x->tuple.values()==y->tuple.values()); }
  }
  check(clock_calls==0);
  auto old=counted.workload_statistics(); check(old.modes().requested_mode==DeltaMode::delta && old.modes().resolved_mode==DeltaMode::delta);
  static_cast<void>(counted.set_mode(DeltaMode::delta)); check(counted.workload_statistics().stamp().segment==0);
  static_cast<void>(counted.set_mode(DeltaMode::maintenance));
  auto current=counted.workload_statistics(); check(current.stamp().segment==1 && current.has_previous());
  check(current.metadata().committed==0 && current.previous_metadata().committed==2);
  check(current.modes().requested_mode==DeltaMode::delta && current.modes().resolved_mode==DeltaMode::maintenance);
  check(current.previous_modes().resolved_mode==DeltaMode::delta && current.previous_interval_end_epoch()==2);
  static_cast<void>(counted.set_mode(DeltaMode::delta)); current=counted.workload_statistics();
  check(current.stamp().segment==2 && current.replaced_history() && current.previous_modes().resolved_mode==DeltaMode::maintenance);
  check(old.metadata().committed==2 && old.stamp().segment==0);
  auto bad=delta_options(DeltaMode::maintenance); bad.work_limit=0;
  DeltaRuntime failing(compiled,bad); failing.configure_workload_statistics(enabled());
  const auto before=failing.workload_statistics();
  error([&] { static_cast<void>(failing.set_mode(DeltaMode::delta)); },"resource_limit");
  check(failing.mode()==DeltaMode::maintenance && failing.workload_statistics().stamp().segment==before.stamp().segment);
  const Database database{{{{n(1),n(7)}},{{n(7)}},{}}};
  for (const auto method:{BuildMethod::direct,BuildMethod::insertion_replay}) {
    BuildOptions build; build.method=method;
    auto built=DeltaRuntime::initialize(compiled,database,delta_options(),build);
    check(built.workload_statistics().metadata().attempts==0 && built.workload_statistics().memory().retained_payload_bytes==0);
    built.configure_workload_statistics(enabled()); check(built.workload_statistics().metadata().committed==0);
    apply(built,2,SetOperation::insert,{n(9)});
    auto rebuilt=built.rebuilt(build); check(rebuilt.owner()!=built.owner());
    check(rebuilt.workload_statistics().metadata().attempts==0 && rebuilt.workload_statistics().stamp().segment==0);
    rebuilt.configure_workload_statistics(enabled());
    check(rebuilt.workload_statistics().stamp().interval_start_epoch==rebuilt.sequence());
  }
  check(clock_calls==0); detail::set_observation_clock_for_testing(nullptr);
}
void late_abort_and_output_barrier() {
  auto options=delta_options(); options.spool_row_limit=0;
  DeltaRuntime runtime(plan(),options); runtime.configure_workload_statistics(enabled());
  apply(runtime,0,SetOperation::insert,{n(1),n(7)}); apply(runtime,0,SetOperation::insert,{n(2),n(7)});
  const auto before=runtime.workload_statistics();
  error([&] { auto pending=runtime.begin({3,{1},SetOperation::insert,{n(7)}}); pending.drain(); },"resource_limit");
  auto after=runtime.workload_statistics(); check(runtime.sequence()==2 && runtime.ready());
  check(after.metadata().aborted==1 && after.metadata().detail_actions>before.metadata().detail_actions);
  check(same_cells(before.cells(),after.cells())); runtime.check_invariants();
  DeltaRuntime normal(plan(),delta_options()); normal.configure_workload_statistics(enabled());
  apply(normal,0,SetOperation::insert,{n(1),n(7)});
  auto pending=normal.begin({2,{1},SetOperation::insert,{n(7)}}); pending.drain();
  check(normal.workload_statistics().metadata().committed==1);
  error([&] { normal.reset_workload_statistics(); },"runtime_busy");
  auto output=pending.commit(); check(output.remaining()==1 && normal.workload_statistics().metadata().committed==2);
  error([&] { normal.configure_workload_statistics(enabled()); },"runtime_busy");
  error([&] { normal.reset_workload_statistics(); },"runtime_busy");
  output.discard(); normal.reset_workload_statistics();
}
void sessions_and_owning_lifetime() {
  SessionOptions options; options.delta=delta_options();
  auto session=QuerySession::create_typed(plan(),{},options); session->configure_workload_statistics(enabled());
  io::TransportBatch batch({io::InputEvent{{1,{0},SetOperation::insert,{n(1),n(7)}},{}},
      io::InputEvent{{2,{1},SetOperation::insert,{n(7)}},{}}});
  check(session->enqueue(batch)==io::Admission::accepted); session->finish_input(); session->start();
  check(session->begin_next());
  error([&] { session->reset_workload_statistics(); },"session_pending_epoch");
  check(session->workload_statistics()->pending()); session->drain();
  check(session->begin_next()); while (session->step()!=DeltaStep::prepared) {}
  session->commit(); auto report=*session->workload_statistics();
  check(report.metadata().committed==2 && !report.pending());
  error([&] { session->configure_workload_statistics(enabled()); },"runtime_busy");
  bool thread_rejected=false; std::thread other([&] {
    try { static_cast<void>(session->workload_statistics()); } catch (const Error& e) { thread_rejected=e.code()=="session_wrong_thread"; }
  }); other.join(); check(thread_rejected);
  session->stop(); check(session->workload_statistics()->metadata().committed==2);
  session->reset_workload_statistics(); session->drop(); check(!session->workload_statistics()); session.reset();
  check(report.metadata().committed==2 && report.plan().nodes().size()==2 && report.stamp().committed_epoch==2);
  // A metadata-only window command has private work without a Delta ticket.
  WindowOptions window; window.managed_tables={TableId{0}};
  auto managed=QuerySession::create_windowed(plan(),window,{},options); managed->configure_workload_statistics(enabled());
  io::TransportBatch watermark({io::WindowCommand{1,io::AdvanceWatermark{2},{}}});
  check(managed->enqueue(watermark)==io::Admission::accepted); managed->start(); check(managed->begin_next());
  check(managed->workload_statistics()->pending());
  error([&] { managed->configure_workload_statistics(enabled()); },"session_pending_epoch");
  managed->drain(); check(managed->workload_statistics()->metadata().committed==0); managed->drop();
  class Buffer final:public std::streambuf {
   public:
    QuerySession* session=nullptr;
    bool fired=false,rejected=false;
    std::string bytes;
    std::size_t position=0;
   protected:
    int_type underflow() override {
      if (!fired) {
        fired=true;
        try { static_cast<void>(session->workload_statistics()); }
        catch (const Error& failure) { rejected=failure.code()=="session_busy"; }
      }
      return position==bytes.size()?traits_type::eof():traits_type::to_int_type(bytes[position]);
    }
    int_type uflow() override {
      const auto next=underflow(); if (!traits_type::eq_int_type(next,traits_type::eof())) ++position; return next;
    }
  } buffer;
  const auto compiled=plan();
  buffer.bytes=io::write_input_json({{1,{0},SetOperation::insert,{n(1),n(7)}},{}},compiled.source_catalog())+"\n";
  auto reentrant=QuerySession::create(compiled,std::make_unique<std::istream>(&buffer),options);
  buffer.session=reentrant.get(); reentrant->configure_workload_statistics(enabled()); reentrant->start();
  check(reentrant->begin_next() && buffer.rejected); reentrant->stop();
}
void delayed_root_admission() {
  using namespace statistics_collection;
  const Descriptor definitions[]={{Kind::physical,0,0,Operation::insert},{Kind::support,0,1,Operation::insert}};
  Collector collector; collector.configure(enabled(),definitions);
  auto outer=collector.admit(0); auto physical=collector.nest(outer); auto support=collector.nest(physical);
  collector.physical_fact(true); collector.support(1,0,1);
  check(collector.finish(support,true) && collector.finish(physical,true));
  check(collector.committed()[0].inputs==0 && collector.committed()[1].changes==0);
  check(!collector.finish(outer,false)); check(collector.metadata().aborted==1 && collector.committed()[0].inputs==0);
}
static_assert(!std::is_default_constructible_v<ws::Snapshot>);
static_assert(std::is_same_v<decltype(std::declval<const ws::Snapshot&>().cells()),std::span<const ws::Cell>>);
}
int main() {
  literal_hand_trace(); projection_aliases_and_generalized(); lower_scope_and_barriers(); native_touched_event_multiset();
  sample_retry_and_truncation(); modes_initialization_and_parity(); late_abort_and_output_barrier();
  sampled_rate_denominators_and_overflow();
  sessions_and_owning_lifetime(); delayed_root_admission();
  std::cout<<"workload statistics integration: 10 groups passed\n";
}

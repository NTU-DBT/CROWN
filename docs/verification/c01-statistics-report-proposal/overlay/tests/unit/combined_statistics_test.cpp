#include "combined_statistics_fixture.hpp"
#include <iostream>
#include <sstream>
#include <type_traits>
using namespace combined_fixture;
static_assert(!std::is_default_constructible_v<stats::CombinedCapture>);
static_assert(!std::is_constructible_v<stats::CombinedCapture,stats::OwnerCapture,ws::Snapshot>);
static_assert(std::is_nothrow_copy_constructible_v<stats::CombinedCapture>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::CombinedCapture&>().state())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<stats::CombinedCapture&>().workload())>>);
int main(){
  const auto p=plan();const auto db=database();const auto r=request(p);
  auto physical=PhysicalRuntime::initialize(p,db);
  // 1. Actual bindings agree even while workload collection is off; success and no-op are distinct.
  const auto off=physical.capture_combined_statistics(r);facts(off,db,0);
  check(off.workload().options().mode==ws::Mode::off && off.workload().descriptors().empty());
  physical.configure_workload_statistics(wf::enabled());
  const auto configured=physical.capture_combined_statistics(r);facts(configured,db,0);
  check(configured.workload().metadata().committed==0 && configured.workload().stamp().configuration_generation>off.workload().stamp().configuration_generation);
  static_cast<void>(physical.apply({1,TableId{1},SetOperation::insert,{n(8)}}));
  auto all=db;all.tables[1].insert(Row{n(8)});
  const auto success=physical.capture_combined_statistics(r);facts(success,all,1);
  const auto& changed=wf::cell(success.workload(),1,SetOperation::insert,ws::Role::input);
  check(changed.inputs==1 && changed.changed==1 && changed.noop==0);
  const auto& parent=wf::cell(success.workload(),1,SetOperation::insert,ws::Role::parent_support,NodeId{0});
  check(parent.changes==1 && parent.zero_to_positive==0 && parent.positive_to_zero==0);
  static_cast<void>(physical.apply({2,TableId{1},SetOperation::insert,{n(8)}}));
  const auto noop=physical.capture_combined_statistics(r);facts(noop,all,2);
  const auto& inputs=wf::cell(noop.workload(),1,SetOperation::insert,ws::Role::input);
  check(inputs.inputs==2 && inputs.changed==1 && inputs.noop==1 && inputs.complete_detail_inputs==2);
  const auto share=noop.workload().events_per_physical_input(wf::find(noop.workload(),1,SetOperation::insert,ws::Role::parent_support,NodeId{0}));
  check(share.numerator==1 && share.denominator==2);
  check(physical.statistics_freshness(success.state())==stats::Freshness::stale);
  // 2. Private changes expose no state facts; abort preserves committed facts and cells.
  {auto pending=physical.prepare({3,TableId{1},SetOperation::erase,{n(7)}});
    const auto hidden=physical.capture_combined_statistics(r);binding(hidden,2,true);
    check(hidden.state().components().empty() && hidden.workload().metadata().committed==2);
    pending.rollback();}
  const auto aborted=physical.capture_combined_statistics(r);facts(aborted,all,2);
  check(aborted.workload().metadata().aborted==1 && aborted.workload().metadata().committed==2);
  check(wf::same_cells(aborted.workload().cells(),noop.workload().cells()));
  check(physical.statistics_freshness(noop.state())==stats::Freshness::current);
  // 3. Two real support events differ from the final one-key population; reset changes no data epoch.
  static_cast<void>(physical.apply({3,TableId{1},SetOperation::erase,{n(7)}}));
  all.tables[1].erase(Row{n(7)});const auto erased=physical.capture_combined_statistics(r);facts(erased,all,3);
  const auto& erased_parent=wf::cell(erased.workload(),1,SetOperation::erase,ws::Role::parent_support,NodeId{0});
  check(erased_parent.changes==2 && erased_parent.count==2 && erased_parent.sum==3 && erased_parent.positive_to_zero==0);
  distribution(erased.state().components()[5],Counts{{Row{},1}},1);
  const auto& touched=wf::cell(erased.workload(),1,SetOperation::erase,ws::Role::native_touched_degree,{},{},{},ws::Operation::erase);
  check(touched.count==1 && touched.sum==2);
  physical.reset_workload_statistics();const auto reset=physical.capture_combined_statistics(r);facts(reset,all,3);
  check(reset.workload().stamp().reset_generation==erased.workload().stamp().reset_generation+1 && reset.workload().stamp().interval_start_epoch==3);
  check(reset.workload().metadata().attempts==0 && physical.statistics_freshness(erased.state())==stats::Freshness::current);
  check(erased.workload().metadata().committed==3 && noop.workload().metadata().aborted==0);
  // 4. Delta outer pending/unread state and mode segments share a committed data boundary.
  auto delta=DeltaRuntime::initialize(p,db,wf::delta_options());delta.configure_workload_statistics(wf::enabled());
  auto pending=delta.begin({1,TableId{1},SetOperation::insert,{n(8)}});
  binding(delta.capture_combined_statistics(r),0,true);pending.drain();binding(delta.capture_combined_statistics(r),0,true);
  auto unread=pending.commit();auto delta_db=db;delta_db.tables[1].insert(Row{n(8)});
  const auto committed=delta.capture_combined_statistics(r);facts(committed,delta_db,1);
  check(committed.workload().metadata().committed==1);unread.discard();
  static_cast<void>(delta.set_mode(DeltaMode::delta));same_workload(committed.workload(),delta.capture_combined_statistics(r).workload());
  static_cast<void>(delta.set_mode(DeltaMode::maintenance));const auto segmented=delta.capture_combined_statistics(r);facts(segmented,delta_db,1);
  check(delta.statistics_freshness(committed.state())==stats::Freshness::current);
  check(segmented.workload().stamp().segment==committed.workload().stamp().segment+1 && segmented.workload().has_previous());
  check(segmented.workload().previous_interval_end_epoch()==1 && segmented.workload().previous_metadata().committed==1 && segmented.workload().metadata().committed==0);
  // 5. Failed mode construction and a real late spool abort cannot publish a mixed pair.
  auto bad=wf::delta_options(DeltaMode::maintenance);bad.work_limit=0;DeltaRuntime failed_mode(p,bad);
  failed_mode.configure_workload_statistics(wf::enabled());const auto before_mode=failed_mode.capture_combined_statistics(r);
  wf::error([&]{static_cast<void>(failed_mode.set_mode(DeltaMode::delta));},"resource_limit");
  const auto after_mode=failed_mode.capture_combined_statistics(r);same_facts(before_mode.state(),after_mode.state());same_workload(before_mode.workload(),after_mode.workload());
  auto capped=wf::delta_options();capped.spool_row_limit=0;auto late=DeltaRuntime::initialize(p,db,capped);late.configure_workload_statistics(wf::enabled());
  const auto before_late=late.capture_combined_statistics(r);
  wf::error([&]{auto output=late.apply({1,TableId{1},SetOperation::insert,{n(8)}});output.discard();},"resource_limit");
  const auto after_late=late.capture_combined_statistics(r);facts(after_late,db,0);
  check(after_late.workload().metadata().aborted==1 && after_late.workload().metadata().committed==0);
  check(wf::same_cells(before_late.workload().cells(),after_late.workload().cells()));
  // 6. Lower-only availability, sampling and exhausted state scans remain independent.
  SupportRuntime lower(p);lower.configure_workload_statistics(wf::enabled());
  static_cast<void>(lower.apply({1,NodeId{0},SetOperation::insert,{n(1),n(7)}}));
  static_cast<void>(lower.apply({2,NodeId{1},SetOperation::insert,{n(7)}}));
  const auto logical=lower.capture_combined_statistics(r);binding(logical,2);
  check(logical.state().physical_source_scope()==stats::Availability::unavailable && logical.workload().metadata().committed==2);
  check(logical.workload().input_share(0).availability==ws::Availability::unavailable);
  {auto operation=lower.begin_epoch(3,SetOperation::insert);static_cast<void>(operation.stage(NodeId{0},{n(2),n(7)}));binding(lower.capture_combined_statistics(r),2,true);operation.rollback();}
  auto sampled=PhysicalRuntime::initialize(p,db);sampled.configure_workload_statistics(wf::enabled(2));
  for(std::uint64_t seq=1;seq<=2;++seq)static_cast<void>(sampled.apply({seq,TableId{1},SetOperation::insert,{n(7)}}));
  const auto sample=sampled.capture_combined_statistics(r);facts(sample,db,2);
  check(sample.workload().metadata().selected==1 && sample.workload().metadata().committed==2 && sample.workload().options().period==2);
  stats::Limits limit;limit.rows=4;const auto incomplete=sampled.capture_combined_statistics(r,limit);binding(incomplete,2);
  check(incomplete.state().availability()==stats::Availability::budget_exhausted && incomplete.state().components()[0].distribution->ndv==2 && !incomplete.state().components()[2].distribution->ndv);
  same_workload(sample.workload(),incomplete.workload());
  // 7. Rebuild, move and immutable joint history retain correct independent identities.
  auto rebuilt=physical.rebuilt();const auto rebuilt_report=rebuilt.capture_combined_statistics(r);facts(rebuilt_report,all,3);
  check(rebuilt.statistics_freshness(erased.state())==stats::Freshness::foreign_owner && rebuilt_report.workload().options().mode==ws::Mode::off && rebuilt_report.workload().metadata().attempts==0);
  rebuilt.configure_workload_statistics(wf::enabled());const auto restarted=rebuilt.capture_combined_statistics(r);
  check(restarted.workload().stamp().interval_start_epoch==3 && rebuilt.statistics_freshness(rebuilt_report.state())==stats::Freshness::current);
  auto moved=std::move(rebuilt);facts(moved.capture_combined_statistics(r),all,3);
  auto retained=erased;auto transferred=std::move(retained);facts(retained,all,3);facts(transferred,all,3);
  check(retained.workload().metadata().committed==3 && configured.workload().metadata().committed==0);
  // 8. One session guard composes both reads, including private work and owner release.
  auto session=QuerySession::create(p,db,std::make_unique<std::istringstream>(
      io::write_input_json(io::InputEvent{PhysicalSetUpdate{1,TableId{1},SetOperation::insert,{n(8)}},{}},p.source_catalog())+"\n"));
  session->configure_workload_statistics(wf::enabled());const auto saved=*session->capture_combined_statistics(r);facts(saved,db,0);
  session->start();check(session->begin_next());session->pause();const auto session_pending=*session->capture_combined_statistics(r);binding(session_pending,0,true);check(session_pending.state().components().empty());
  session->stop();facts(*session->capture_combined_statistics(r),db,0);session->drop();check(!session->capture_combined_statistics(r));facts(saved,db,0);
  // 9. All-off and counters-on preserve complete canonical state and signed output at every event.
  auto off_runtime=DeltaRuntime::initialize(p,db,wf::delta_options());auto on_runtime=DeltaRuntime::initialize(p,db,wf::delta_options());
  on_runtime.configure_workload_statistics(wf::enabled());auto expected=db;
  const std::vector<PhysicalSetUpdate> trace{{1,TableId{1},SetOperation::insert,{n(8)}},{2,TableId{1},SetOperation::insert,{n(8)}},
    {3,TableId{1},SetOperation::erase,{n(7)}},{4,TableId{0},SetOperation::erase,{n(1),n(7),n(99)}},
    {5,TableId{0},SetOperation::insert,{n(4),n(8),n(40)}},{6,TableId{2},SetOperation::insert,{n(100)}}};
  for(const auto& update:trace){
    auto a=off_runtime.apply(update);auto b=on_runtime.apply(update);
    for(;;){auto x=a.next();auto y=b.next();check(x.has_value()==y.has_value());if(!x)break;check(x->operation==y->operation && x->tuple.values()==y->tuple.values());}
    if(update.operation==SetOperation::insert)expected.tables[update.table.value].insert(update.values);else expected.tables[update.table.value].erase(update.values);
    check(off_runtime.canonical_state()==on_runtime.canonical_state());
    const auto a_report=off_runtime.capture_combined_statistics(r);const auto b_report=on_runtime.capture_combined_statistics(r);
    facts(a_report,expected,update.sequence);facts(b_report,expected,update.sequence);
    check(a_report.workload().options().mode==ws::Mode::off && a_report.workload().metadata().committed==0);
    check(b_report.workload().metadata().committed==update.sequence);
  }
  std::cout<<"9 combined owner statistics groups passed\n";
}

#include "statistics_report_fixture.hpp"
#include <iostream>
#include <limits>
#include <type_traits>
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
using namespace report_fixture;
static_assert(!std::is_default_constructible_v<Report>);
static_assert(std::is_nothrow_copy_constructible_v<Report>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<Report&>().combined())>>);
namespace {
void boundaries(const Report& report,const std::filesystem::path& dir){
  for(const auto encoder:{io::write_statistics_json,io::write_statistics_text}){
    const auto full=encoder(report,{});check(!full.text.empty() && full.items>0);
    check(encoder(report,{full.text.size(),full.items}).text==full.text);
    wf::error([&]{static_cast<void>(encoder(report,{full.text.size()-1,full.items}));},"resource_limit");
    wf::error([&]{static_cast<void>(encoder(report,{full.text.size(),full.items-1}));},"resource_limit");
    wf::error([&]{static_cast<void>(encoder(report,{0,full.items}));},"resource_limit");
    wf::error([&]{static_cast<void>(encoder(report,{full.text.size(),0}));},"resource_limit");
  }
  const auto result=io::write_statistics_json(report);write(dir/"export-items.txt",std::to_string(result.items)+"\n");
}
void scalars(const std::filesystem::path& dir){
  const Catalog c{9,{{"mixed",{{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal},{"s",ScalarType::string}}}}};
  const Query q{{{"i",ScalarType::int64},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal},{"s",ScalarType::string}},
      {{"m",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}}}},
      {{VariableId{0},"i"},{VariableId{1},"b"},{VariableId{2},"d"},{VariableId{3},"n"},{VariableId{4},"s"}},false};
  auto p=planner::lower_tree(c,q,FreeConnexTree{NodeId{0},{{"m",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},{},0,{}}},{},{}});
  const std::string bytes{"a\0\xff\x80",4};
  const Database db{{Relation{{std::numeric_limits<std::int64_t>::min(),true,Date::parse("0001-01-01"),Decimal::parse("1.00"),bytes},
      {std::numeric_limits<std::int64_t>::max(),false,Date::parse("9999-12-31"),Decimal::parse("-0.000100"),std::string("\xc3\xa9",2)}}}};
  auto runtime=DeltaRuntime::initialize(p,db,wf::delta_options());Capture capture;
  capture.state=stats::OwnerRequest{{{stats::SourceScope{TableId{0}},std::vector<FieldId>{{0},{1},{2},{3},{4}}},
      {stats::SourceScope{TableId{0}},std::vector<FieldId>{{4},{0},{4}}},{stats::SourceScope{TableId{0}},std::vector<FieldId>{}},
      {stats::OccurrenceScope{OccurrenceId{0}},{}}}};
  const auto report=emit(dir,"scalars",Report::capture(runtime,capture));const auto& components=report.combined()->state().components();
  Counts full,repeated;for(const auto& row:db.tables[0]){++full[row];++repeated[Row{row[4],row[0],row[4]}];}
  distribution(components[0],full,2);distribution(components[1],repeated,2);distribution(components[2],Counts{{Row{},2}},2);distribution(components[3],full,2);
}
}
int main(int argc,char** argv){
  check(argc==2);const std::filesystem::path dir=argv[1];std::filesystem::create_directories(dir);
  const auto p=plan();const auto db=database();const auto opts=wf::delta_options();auto runtime=DeltaRuntime::initialize(p,db,opts);
  SessionOptions session_options;session_options.delta=opts;auto session=QuerySession::create_typed(p,db,{},session_options);
  legacy_pair(dir,runtime,*session);const auto scan=requested(p);
  const auto metadata=emit(dir,"off-metadata",Report::capture(runtime));check(!metadata.state_requested() && metadata.combined()->state().components().empty() && metadata.combined()->state().usage().rows==0);
  const auto off=emit(dir,"off-state",Report::capture(runtime,scan));literal(off,db,0);boundaries(off,dir);
  runtime.configure_workload_statistics(wf::enabled());wf::error([&]{static_cast<void>(observability::PlanExplanation::capture(runtime));},"explain_statistics_version");
  check(!io::write_explain_tree_json(observability::PlanExplanation::create(runtime.plan())).empty());
  wf::apply(runtime,1,SetOperation::insert,{n(8)});auto all=db;all.tables[1].insert(Row{n(8)});
  auto success=emit(dir,"success",Report::capture(runtime,scan,&off));literal(success,all,1);
  wf::apply(runtime,1,SetOperation::insert,{n(8)});auto noop=emit(dir,"noop",Report::capture(runtime,scan,&success));literal(noop,all,2);
  check(noop.combined()->workload().metadata().committed==2 && noop.comparison()->data==stats::Freshness::stale);
  wf::apply(runtime,1,SetOperation::erase,{n(7)});all.tables[1].erase(Row{n(7)});const auto erased=emit(dir,"erased",Report::capture(runtime,scan));literal(erased,all,3);
  const auto& events=wf::cell(erased.combined()->workload(),1,SetOperation::erase,ws::Role::parent_support,NodeId{0});check(events.count==2 && events.sum==3);
  distribution(erased.combined()->state().components()[5],Counts{{Row{},1}},1);
  auto sampled=DeltaRuntime::initialize(p,db,opts);sampled.configure_workload_statistics(wf::enabled(2));wf::apply(sampled,1,SetOperation::insert,{n(8)});wf::apply(sampled,1,SetOperation::insert,{n(8)});
  const auto sample=emit(dir,"sampled",Report::capture(sampled,scan));check(sample.combined()->workload().metadata().selected==1);
  auto truncated=DeltaRuntime::initialize(p,db,opts);truncated.configure_workload_statistics(wf::enabled(1,0,0));wf::apply(truncated,1,SetOperation::insert,{n(8)});
  check(emit(dir,"truncated",Report::capture(truncated,scan)).combined()->workload().metadata().committed_truncated==1);
  auto partial=scan;partial.state_limits.rows=4;const auto incomplete=emit(dir,"state-exhausted",Report::capture(runtime,partial));check(incomplete.combined()->state().availability()==stats::Availability::budget_exhausted);
  check(incomplete.combined()->state().components()[0].distribution->ndv==2 && !incomplete.combined()->state().components()[2].distribution->ndv);
  auto zero=scan;zero.state_limits.accounted_bytes=0;check(emit(dir,"state-zero",Report::capture(runtime,zero)).combined()->state().availability()==stats::Availability::budget_exhausted);
  auto observed_options=opts;observed_options.physical.support.observation.mode=ObservationMode::counters;
  auto observed=DeltaRuntime::initialize(p,db,observed_options);observed.configure_workload_statistics(wf::enabled());
  observed.declare_benchmark_context(std::make_shared<const DeclaredBenchmarkContext>(BenchmarkLabels{std::string("run\0\xff",5),"declared-adapter","declared-codec","declared-sink"}));
  wf::apply(observed,1,SetOperation::insert,{n(8)});const auto before_mode=emit(dir,"mode-before",Report::capture(observed,scan));
  const auto historical=io::write_statistics_json(before_mode).text;static_cast<void>(observed.set_mode(DeltaMode::maintenance));
  const auto after_mode=emit(dir,"mode-after",Report::capture(observed,scan,&before_mode));check(after_mode.comparison()->data==stats::Freshness::current && after_mode.comparison()->segment==observability::IntervalComparison::changed);
  check(after_mode.observation().last->configuration->mode()==DeltaMode::delta && after_mode.mode().profile()->mode==DeltaMode::maintenance);
  static_cast<void>(observed.set_mode(DeltaMode::maintenance));
  const auto same_mode=emit(dir,"mode-noop",Report::capture(observed,scan,&after_mode));check(same_mode.comparison()->segment==observability::IntervalComparison::same);
  observed.reset_workload_statistics();const auto reset=emit(dir,"reset",Report::capture(observed,scan,&after_mode));check(reset.comparison()->reset==observability::IntervalComparison::changed && reset.comparison()->data==stats::Freshness::current);
  observed.configure_workload_statistics(wf::enabled(2));const auto reconfigured=emit(dir,"reconfigured",Report::capture(observed,scan,&reset));
  check(reconfigured.comparison()->configuration==observability::IntervalComparison::changed && reconfigured.comparison()->data==stats::Freshness::current);
  static_cast<void>(observed.set_mode(DeltaMode::delta));auto pending=observed.begin({2,TableId{1},SetOperation::erase,{n(8)}});
  const auto private_report=emit(dir,"pending",Report::capture(observed,scan));check(private_report.combined()->state().components().empty() && private_report.combined()->workload().pending());
  pending.drain();emit(dir,"prepared",Report::capture(observed,scan));auto unread=pending.commit();
  const auto published=emit(dir,"unread",Report::capture(observed,scan));literal(published,db,2);check(published.mode().state()==DeltaState::committed_output);unread.discard();
  {auto abort=observed.begin({3,TableId{1},SetOperation::insert,{n(8)}});abort.rollback();}
  literal(emit(dir,"aborted",Report::capture(observed,scan)),db,2);
  check(emit(dir,"stale",Report::capture(observed,scan,&before_mode)).comparison()->data==stats::Freshness::stale);
  check(emit(dir,"within-lag",Report::capture(observed,scan,&before_mode,1)).comparison()->data==stats::Freshness::within_lag);
  auto rebuilt=observed.rebuilt();const auto foreign=emit(dir,"rebuilt",Report::capture(rebuilt,scan,&published));literal(foreign,db,2);check(foreign.comparison()->data==stats::Freshness::foreign_owner);
  auto moved=std::move(observed);literal(emit(dir,"moved",Report::capture(moved,scan,&published)),db,2);check(io::write_statistics_json(before_mode).text==historical);
  auto held=before_mode;auto held_move=std::move(held);check(io::write_statistics_json(held).text==historical && io::write_statistics_json(held_move).text==historical);
  session->configure_workload_statistics(wf::enabled());wf::error([&]{static_cast<void>(observability::PlanExplanation::capture(*session));},"explain_statistics_version");
  const auto session_old=emit(dir,"session-live",Report::capture(*session,scan));enqueue(*session,{1,TableId{1},SetOperation::insert,{n(8)}});session->start();check(session->begin_next());session->pause();
  check(emit(dir,"session-private",Report::capture(*session,scan)).combined()->workload().pending());session->stop();literal(emit(dir,"session-stopped",Report::capture(*session,scan)),db,0);
  session->drop();const auto released=emit(dir,"session-released",Report::capture(*session,scan,&session_old));check(!released.combined() && !released.comparison()->data && released.workload_options().mode==ws::Mode::counters);
  wf::error([&]{static_cast<void>(observability::PlanExplanation::capture(*session));},"explain_statistics_version");session.reset();literal(session_old,db,0);
  auto window_db=db;window_db.tables[1].clear();WindowOptions window_options;window_options.managed_tables={TableId{1}};window_options.width=17;
  auto window=QuerySession::create_windowed(p,window_db,window_options,{},session_options);window->configure_workload_statistics(wf::enabled());
  io::TransportBatch watermark({io::WindowCommand{1,io::AdvanceWatermark{10},{}}});check(window->enqueue(watermark)==io::Admission::accepted);window->start();check(window->begin_next());
  const auto window_pending=emit(dir,"window-private",Report::capture(*window,scan));check(window_pending.mode().state()==DeltaState::ready && window_pending.combined()->workload().pending() && window_pending.combined()->state().components().empty());
  while(window->step()!=DeltaStep::prepared){}window->commit();literal(emit(dir,"window-committed",Report::capture(*window,scan)),window_db,0);
  auto hidden=DeltaRuntime::initialize(hidden_separator_plan(),hidden_separator_database(),opts);Capture hidden_options;
  hidden_options.state=stats::OwnerRequest{{{stats::NodeScope{NodeId{3},SupportRole::visible},{}},{stats::NodeScope{NodeId{0},SupportRole::records},{}},{stats::NodeScope{NodeId{0},SupportRole::survivors},{}}}};
  const auto absent=emit(dir,"hidden-e",Report::capture(hidden,hidden_options));check(absent.combined()->state().components()[0].availability==stats::Availability::not_applicable);
  check(absent.combined()->state().components()[1].cardinality==2 && absent.combined()->state().components()[2].cardinality==1);
  scalars(dir);
  DeltaRuntime generalized(wf::alias_plan(true),opts);generalized.configure_workload_statistics(wf::enabled());
  wf::apply(generalized,0,SetOperation::insert,{n(1),n(7),n(0)});wf::apply(generalized,0,SetOperation::insert,{n(1),n(7),n(1)});
  const auto generalized_report=emit(dir,"generalized-events",Report::capture(generalized));const auto& generalized_work=generalized_report.combined()->workload();
  std::uint64_t probes=0,absent_probes=0,present_probes=0;
  for(std::size_t i=0;i<generalized_work.descriptors().size();++i)if(generalized_work.descriptors()[i].role==ws::Role::generalized_probe){
    probes+=generalized_work.cells()[i].count;absent_probes+=generalized_work.cells()[i].bins[0];present_probes+=generalized_work.cells()[i].bins[1];}
  check(probes==2 && absent_probes==1 && present_probes==1);
#ifdef CROWN_RUNTIME_TESTING
  auto saturated=DeltaRuntime::initialize(p,db,opts);saturated.configure_workload_statistics(wf::enabled());const auto saturation_before=Report::capture(saturated,scan);
  RuntimeTestProbe::seed_c01_report_saturation(saturated);const auto capped=emit(dir,"saturated",Report::capture(saturated,scan,&saturation_before));
  check(capped.combined()->workload().detail_availability()==ws::Availability::lower_bound && capped.comparison()->configuration==observability::IntervalComparison::saturated);
  literal(capped,db,0);
#endif
  std::cout<<"statistics report lifecycle, literal facts, scalar and export-boundary fixtures produced\n";
}

#include "update_pattern_fixture.hpp"
#include "window_checkpoint_test_fixture.hpp"
#include "selection_fixture.hpp"
#include "crown/frontend/admission.hpp"
#include "crown/recovery/session_image.hpp"
#include <array>

namespace {
using namespace crown;
using namespace crown::runtime;
using c02_test::check;
namespace ip=crown::patterns;
namespace pp=planner::patterns;
namespace ps=planner::selection;
namespace rs=runtime::selection;
namespace win=window_checkpoint_test;

struct SqlFixture {
  CompiledProgram program;
  planner::CandidateSnapshot family;
};
// Physical table 0 is unused; core table IDs are occurrences, not physical
// bases. Aliases and dropped payloads deliberately create projection collisions.
SqlFixture sql_fixture(bool indexed,bool taller) {
  const Catalog catalog{7,{{"unused",{{"value",ScalarType::int64}}},
      {"r",{{"x",ScalarType::int64},{"y",ScalarType::int64},{"flag",ScalarType::int64},{"payload",ScalarType::string}}}}};
  const auto sql=taller?
      "SELECT DISTINCT 1 AS yes FROM r a JOIN r b ON a.y=b.x JOIN r c ON b.y=c.x WHERE a.flag=1":
      "SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1";
  auto admitted=frontend::admit_sql(sql,catalog);
  check(admitted.status==frontend::AdmissionStatus::admitted && admitted.program.has_value(),"SQL transfer admission failed");
  const auto& normalized=*admitted.program;
  auto family=c02_test::candidates({normalized.core_catalog,normalized.core,{}},taller?2:1,0);
  auto program=CompiledProgram::standalone(planner::lower_normalized(normalized,family.candidate(0)->tree(),
      indexed?s04_runtime::options():PhysicalOptions{}));
  for(const auto& input:program.inputs())check(input.base==TableId{1},"normalized input lost actual physical base ID");
  return {std::move(program),std::move(family)};
}
SessionOptions monitored(const CompiledProgram& program,std::span<const ip::TableRule> rules) {
  SessionOptions options;options.update_patterns=UpdatePatternOptions{ip::Declaration::capture(program.account(),program,rules),{}};
  options.delta.physical.support.observation.mode=ObservationMode::counters;return options;
}
void physical(QuerySession& owner,std::uint64_t sequence,TableId table,SetOperation operation,Row row) {
  io::TransportBatch batch({io::InputEvent{{sequence,table,operation,std::move(row)},{}}});
  check(owner.enqueue(batch)==io::Admission::accepted && owner.begin_next(),"transfer input missing");
  static_cast<void>(win::finish(owner));
}
std::string_view bytes(const recovery::SessionImage& image){return {image.bytes.data(),image.bytes.size()};}

// A logical insertion condition belongs to physical participating sources.
// Unknown mixed transfer stays unknown above height one, including FIFO rules;
// arbitrary height-one transfer needs only bounded zero/one occurrence events.
void sql_contract(bool indexed,bool taller) {
  const auto fixture=sql_fixture(indexed,taller);const auto& program=fixture.program;
  const std::array right{ip::TableRule{TableId{1},true,0}};
  const std::array wrong{ip::TableRule{TableId{0},true,0}};
  const std::array fifo{ip::TableRule{TableId{1},false,1}};
  const auto declaration=ip::Declaration::capture(program.account(),program,right);
  for(std::size_t i=0;i<fixture.family.candidate_count();++i) {
    const auto candidate=*fixture.family.candidate(i);
    const auto good=pp::analyse(program.account(),program,candidate,declaration);
    check(good.stop==planner::ranking::Stop::complete && good.analysis->sufficient==pp::SufficientCase::insertion_only &&
        good.analysis->transfer==pp::Transfer::checked_monotone_source,"normalized monotone source was not proved");
    for(const auto rules:{std::span<const ip::TableRule>(wrong),std::span<const ip::TableRule>(fifo)}) {
      const auto requested=ip::Declaration::capture(program.account(),program,rules);
      const auto other=pp::analyse(program.account(),program,candidate,requested);
      check(other.analysis && other.analysis->sufficient==(taller?pp::SufficientCase::unknown:pp::SufficientCase::height_one) &&
          other.analysis->transfer==(taller?pp::Transfer::normalized_source:pp::Transfer::checked_event_mapping),
          "core IDs or FIFO metadata invented a source transfer");
    }
  }
  ps::Request request;request.policy=ps::Policy::height_only;request.update_patterns=declaration;
  const ps::Source basis=ps::PhysicalBasis{program};auto cache=ps::PlanCache::create();
  const auto selected=ps::select(fixture.family,basis,request,{},&cache,ps::CacheUse::read_write);
  check(selected.selection && selected.stop==ps::Stop::complete && selected.selection->plan().normalized(),"SQL pattern selection failed");
  check(ps::select(fixture.family,basis,request,{},&cache,ps::CacheUse::read_write).selection->cache_observation().disposition==ps::CacheDisposition::hit,
      "source-event condition did not retain exact cache binding");
  auto session=QuerySession::create_typed(program,{},monitored(program,right));session->start();
  session->configure_workload_statistics(c05_test::counters());
  check(rs::select_current(fixture.family,basis,*session,request).selection.has_value(),"actual SQL monitor did not bind selection");
  // Erasing an unused physical table is legal and creates no occurrence event.
  physical(*session,1,TableId{0},SetOperation::insert,{std::int64_t{42}});
  physical(*session,2,TableId{0},SetOperation::erase,{std::int64_t{42}});
  const std::array<Row,4> rows{{
      {std::int64_t{100},std::int64_t{10},std::int64_t{1},std::string("a")},
      {std::int64_t{10},std::int64_t{20},std::int64_t{0},std::string("b")},
      {std::int64_t{20},std::int64_t{30},std::int64_t{0},std::string("c")},
      {std::int64_t{100},std::int64_t{10},std::int64_t{1},std::string("different-full-row")}}};
  for(std::size_t i=0;i<rows.size();++i)physical(*session,i+3,TableId{1},SetOperation::insert,rows[i]);
  const auto collision=session->observations();
  check(collision.last && collision.last->metric(MetricId::physical_native_crossings).availability==MetricAvailability::available &&
      collision.last->metric(MetricId::physical_source_changes).value==1 &&
      collision.last->metric(MetricId::physical_native_crossings).value==0,"projection collision created a native erase or extra insertion");
  physical(*session,7,TableId{1},SetOperation::insert,rows.back());
  check(session->observations().last->metric(MetricId::physical_source_changes).value==0,"duplicate physical insertion was not a no-op");
  const Relation expected{Row{std::int64_t{taller?1:100}}};
  check(win::rows(*session)==expected && rs::select_current(fixture.family,basis,*session,request).selection.has_value(),
      "literal alias result or committed monitor selection changed");
  const auto image=session->checkpoint_image();auto restored=QuerySession::restore_image(program,bytes(image));restored->start();
  check(restored->update_pattern_status().history==PatternHistory::restored_checkpoint &&
      rs::select_current(fixture.family,basis,*restored,request).selection.has_value(),"restored SQL monitor lost its source mapping");
  io::TransportBatch erase({io::InputEvent{{8,TableId{1},SetOperation::erase,rows.front()},{}}});
  check(restored->enqueue(erase)==io::Admission::accepted,"restored erase fixture was not queued");
  bool rejected=false;try{static_cast<void>(restored->begin_next());}catch(const Error& e){rejected=e.code()=="update_pattern_violation";}
  check(rejected && restored->progress().sequence==7 && win::rows(*restored)==expected,"restored source erase escaped enforcement");
}

// Higher mixed trees retain the lifetime gate. A dropped column and a genuine
// three-alias self-join remain unknown with arbitrary/FIFO source declarations.
void mixed_transfer_refusals() {
  for(const bool aliases:{false,true}) {
    auto fixture=c02_test::fixture();
    if(aliases) {
      fixture.catalog.tables={{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}};
      fixture.query.variables={{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64},{"w",ScalarType::int64}};
      fixture.query.atoms={{"a",TableId{0},{VariableId{0},VariableId{1}}},{"b",TableId{0},{VariableId{1},VariableId{2}}},
          {"c",TableId{0},{VariableId{2},VariableId{3}}}};
    } else {
      fixture.catalog.tables[0].columns.push_back({"ignored",ScalarType::int64});fixture.query.atoms[0].terms.emplace_back(IgnoredColumn{});
    }
    const auto family=c02_test::candidates(fixture,2,0);
    const auto source=CompiledProgram::standalone(planner::lower_tree(fixture.catalog,fixture.query,family.candidate(0)->tree()));
    std::vector<ip::TableRule> rules;for(std::size_t t=0;t<fixture.catalog.tables.size();++t)rules.push_back({TableId{t},false,1});
    const auto declaration=ip::Declaration::capture(source.account(),source,rules);
    const auto result=pp::analyse(source.account(),source,*family.candidate(0),declaration);
    check(result.analysis && result.analysis->sufficient==pp::SufficientCase::unknown &&
        result.analysis->transfer==(aliases?pp::Transfer::self_join:pp::Transfer::ignored_column),"mixed lifetime transfer was weakened");
    for(auto& rule:rules)rule.insertion_only=true;
    const auto insertions=ip::Declaration::capture(source.account(),source,rules);
    check(pp::analyse(source.account(),source,*family.candidate(0),insertions).analysis->sufficient==pp::SufficientCase::insertion_only,
        "all-insertion mapping retained an unnecessary lifetime gate");
  }
}

// The proof's explicit seven-atom tree uses non-topological IDs (root is 7).
// Lowering independently verifies the witness; minimum-height authority in the
// analysis tests still comes from the real exact search/provider.
PhysicalPlan oscillator_plan(bool indexed) {
  const auto fixture=pattern_test::height_three_fixture();
  FreeConnexTree tree{NodeId{7},{
      {"R",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3}},{NodeId{1},NodeId{2},NodeId{6}},0,{}},
      {"S",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{4}},{NodeId{3}},1,{}},
      {"L",NodeKind::native,{VariableId{3}},{},2,{}},{"V",NodeKind::native,{VariableId{4}},{},3,{}},
      {"T",NodeKind::native,{VariableId{1},VariableId{5}},{NodeId{5}},4,{}},{"B",NodeKind::native,{VariableId{5}},{},5,{}},
      {"E",NodeKind::native,{VariableId{0},VariableId{6}},{},6,{}},
      {"g",NodeKind::generalized,{VariableId{1}},{NodeId{0},NodeId{4}},std::nullopt,{}}},{},{}};
  return planner::lower_tree(fixture.catalog,fixture.query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}

// Actual global raw FIFO plus internal insertion-only does not prevent 2mn R
// survivor transitions. All 3n+2m+3 loading/loop updates are counted. Capture is
// test instrumentation; this control establishes no wall-clock benchmark.
void oscillator_contract(bool indexed,std::uint64_t n,std::uint64_t m) {
  const auto program=CompiledProgram::standalone(oscillator_plan(indexed));
  std::vector<ip::TableRule> rules;WindowOptions windows;windows.fifo=WindowFifoPolicy::unrestricted;windows.width=1000;
  for(std::uint64_t t=0;t<7;++t){rules.push_back({TableId{t},t!=0 && t!=3,1});windows.managed_tables.push_back(TableId{t});}
  auto session=QuerySession::create_windowed(program,windows,{},monitored(program,rules));session->start();
  PhysicalRuntimeOptions options;options.support.capture_transitions=true;options.support.observation.mode=ObservationMode::counters;
  PhysicalRuntime native(program,options);std::uint64_t sequence=0,r_transitions=0,total=0;
  const auto apply=[&](TableId table,Row row,bool add,std::uint64_t label=0) {
    ++sequence;const auto epoch=native.apply({sequence,table,add?SetOperation::insert:SetOperation::erase,row});
    total+=epoch.support.metrics.survivor_transitions;
    for(const auto& change:epoch.support.transitions)if(change.handle.node==NodeId{0} && change.handle.role==SupportRole::survivors)++r_transitions;
    const auto command=add?io::WindowCommand{sequence,io::WindowInsert{sequence,table,std::move(row),0},{}}:
        io::WindowCommand{sequence,io::WindowWithdraw{label},{}};
    static_cast<void>(win::command(*session,command));
    check(win::rows(*session)==c05_test::answers(native) && !session->update_pattern_status().violation,"admitted FIFO trace or exact query result diverged");
  };
  for(std::uint64_t i=1;i<=n;++i)apply(TableId{3},{static_cast<std::int64_t>(i)},true);
  for(std::uint64_t j=1;j<=m;++j)apply(TableId{2},{static_cast<std::int64_t>(j)},true);
  apply(TableId{6},{std::int64_t{0},std::int64_t{0}},true);apply(TableId{5},{std::int64_t{0}},true);apply(TableId{4},{std::int64_t{0},std::int64_t{0}},true);
  for(std::uint64_t j=1;j<=m;++j)apply(TableId{0},{std::int64_t{0},std::int64_t{0},std::int64_t{0},static_cast<std::int64_t>(j)},true);
  for(std::uint64_t i=1;i<=n;++i) {
    apply(TableId{1},{std::int64_t{0},std::int64_t{0},std::int64_t{0},static_cast<std::int64_t>(i)},true);
    check(win::rows(*session)==Relation{Row{std::int64_t{0},std::int64_t{0},std::int64_t{0}}},"oscillator failed to produce its literal answer");
    apply(TableId{3},{static_cast<std::int64_t>(i)},false,i);check(win::rows(*session).empty(),"oscillator retained an answer after old support vanished");
  }
  check(sequence==3*n+2*m+3 && r_transitions==2*m*n && total==2*m*n+6*n+m+3 &&
      session->update_pattern_status().completed_command_sequence==sequence,"parameterized support-event formula differs");
  std::cout<<"FIFO oscillator indexed="<<indexed<<" n="<<n<<" m="<<m<<" updates="<<sequence<<" R_transitions="<<r_transitions<<" total="<<total<<'\n';
}

// The new postorder scratch and retained edge report must obey the same public
// work/cell/byte grants and persistent C++ new failure cleanup as older cases.
void analysis_resource_contract() {
  const auto fixture=pattern_test::height_three_fixture();const auto family=pattern_test::height_three_family(fixture);
  const auto candidate=*family.candidate(0);
  const auto program=CompiledProgram::standalone(planner::lower_tree(fixture.catalog,fixture.query,candidate.tree()));
  std::vector<ip::TableRule> rules;for(std::size_t t=0;t<7;++t)rules.push_back({TableId{t},true,0});
  std::vector<NodeId> first{*candidate.tree().root};std::size_t root=0;
  while(candidate.tree().nodes[first[root].value].kind!=NodeKind::native) {
    const auto& node=candidate.tree().nodes[first[root++].value];first.insert(first.end(),node.children.begin(),node.children.end());
  }
  rules[fixture.query.atoms[*candidate.tree().nodes[first[root].value].occurrence].table.value].insertion_only=false;
  const auto declaration=ip::Declaration::capture(program.account(),program,rules);
  const auto measured=pp::analyse(program.account(),program,candidate,declaration);
  check(measured.analysis && measured.analysis->sufficient==pp::SufficientCase::subtree_edges,"resource fixture missed taller path");
  ps::Request request;request.policy=ps::Policy::height_only;request.update_patterns=declaration;
  const ps::Source basis=ps::PhysicalBasis{program};
  const auto selected=ps::select(family,basis,request);
  check(selected.selection && selected.selection->selected().height()==3 &&
      selected.selection->pattern_analyses().front().sufficient==pp::SufficientCase::subtree_edges,
      "taller proof did not affect real selection eligibility");
  auto session=QuerySession::create_typed(program,{},monitored(program,rules));session->start();
  session->configure_workload_statistics(c05_test::counters());
  check(rs::select_current(family,basis,*session,request).selection.has_value(),"actual taller monitor did not bind current selection");
  planner::ranking::Limits exact;exact.work=measured.usage.work;exact.cells=measured.usage.cells;
  exact.payload_bytes=measured.usage.payload_bytes;exact.binding_key_bytes=measured.usage.binding_key_bytes;
  check(pp::analyse(program.account(),program,candidate,declaration,exact).stop==planner::ranking::Stop::complete,"exact taller grant refused");
  for(unsigned dimension=0;dimension<3;++dimension) {
    auto low=exact;if(dimension==0)--low.work;else if(dimension==1)--low.cells;else --low.payload_bytes;
    const auto baseline=program.account().statistics().current;const auto denied=pp::analyse(program.account(),program,candidate,declaration,low);
    check(!denied.analysis && denied.stop==(dimension==0?planner::ranking::Stop::work_limit:
        dimension==1?planner::ranking::Stop::cell_limit:planner::ranking::Stop::byte_limit) && program.account().statistics().current==baseline,
        "taller grant failure escaped cleanup or returned partial analysis");
  }
  std::size_t allocations=0;
  {s04_alloc::Scope count;const auto result=pp::analyse(program.account(),program,candidate,declaration);check(result.analysis.has_value(),"allocation control failed");allocations=s04_alloc::calls;}
  check(allocations>0 && allocations<1000,"unbounded taller allocation control");
  for(std::size_t cut=0;cut<allocations;++cut) {
    const auto baseline=program.account().statistics().current;pp::Attempt result;
    {s04_alloc::Scope denied(static_cast<std::ptrdiff_t>(cut));result=pp::analyse(program.account(),program,candidate,declaration);}
    check(result.stop==planner::ranking::Stop::allocation_failure && !result.analysis && program.account().statistics().current==baseline,
        "taller persistent denial retained storage or a partial report");
  }
  std::cout<<"taller analysis persistent C++ new denials="<<allocations<<'\n';
}
} // namespace
int main() {
  try {
    mixed_transfer_refusals();analysis_resource_contract();
    for(const bool indexed:{false,true}) {
      sql_contract(indexed,false);sql_contract(indexed,true);
      for(const auto size:{1U,4U,8U})oscillator_contract(indexed,size,size);
    }
    std::cout<<"source-event transfer and taller proof controls passed\n";
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

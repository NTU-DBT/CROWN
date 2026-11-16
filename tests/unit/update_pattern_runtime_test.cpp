#include "window_checkpoint_test_fixture.hpp"
#include "selection_fixture.hpp"
#include "session_journal_fixture.hpp"
#include "crown/recovery/session_image.hpp"
#include "crown/runtime/session_generation.hpp"
#include "crown/io/ingest.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/io/explain.hpp"
#include "crown/io/run_context.hpp"
#include <array>
#include <fstream>
#include <map>
#include <random>

namespace {
using namespace crown;
using namespace crown::runtime;
using c02_test::check;
namespace win = crown::window_checkpoint_test;
namespace ip = crown::patterns;

PhysicalPlan source_plan(bool indexed) {
  Catalog catalog{12,{}};
  for (const auto* name : {"r","s","t","u"}) catalog.tables.push_back({name,{{"x",ScalarType::int64}}});
  Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
SessionOptions declared(const CompiledProgram& program,std::span<const ip::TableRule> rules) {
  SessionOptions options;
  options.update_patterns=UpdatePatternOptions{ip::Declaration::capture(program.account(),program,rules),{}};
  return options;
}
WindowOptions window_options(WindowFifoPolicy policy=WindowFifoPolicy::unrestricted) {
  WindowOptions options;options.managed_tables={TableId{0},TableId{1},TableId{2},TableId{3}};
  options.width=10;options.fifo=policy;return options;
}
std::string_view bytes(const recovery::SessionImage& image) { return {image.bytes.data(),image.bytes.size()}; }
void physical(QuerySession& session,PhysicalSetUpdate update) {
  io::TransportBatch batch({io::InputEvent{std::move(update),{}}});
  check(session.enqueue(batch)==io::Admission::accepted,"physical fixture admission failed");
  check(session.begin_next(),"physical fixture event disappeared");static_cast<void>(win::finish(session));
}
void rejects(QuerySession& session,const char* code) {
  bool failed=false;try { static_cast<void>(session.begin_next()); }
  catch (const Error& error) { failed=error.code()==code; }
  check(failed,"event did not take its exact declared rejection path");
}

// No-op erases are deliberately rejected in the cheap nonwindow policy. Both
// typed and owned-stream paths must reject before journal/native preparation.
void insertion_contract(bool indexed,bool stream) {
  const auto program=CompiledProgram::standalone(source_plan(indexed));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  const auto options=declared(program,rules);
  const io::InputEvent insert{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},{}};
  const io::InputEvent absent{{2,TableId{0},SetOperation::erase,{std::int64_t{999}}},{}};
  auto session=stream?QuerySession::create(program,std::make_unique<std::istringstream>(
      io::write_input_json(insert,program.source_catalog())+"\n"+
      io::write_input_json(absent,program.source_catalog())+"\n"),options):QuerySession::create_typed(program,{},options);
  session->start();
  if(stream){check(session->begin_next(),"stream insertion missing");static_cast<void>(win::finish(*session));}
  else physical(*session,insert.update);
  const auto before=session->checkpoint_state();
  if(!stream){io::TransportBatch batch({absent});check(session->enqueue(batch)==io::Admission::accepted,"erase fixture rejected by queue");}
  rejects(*session,"update_pattern_violation");
  const auto profile=session->update_pattern_status();
  check(profile.declaration.matches(program) && profile.monitored_sequence==1 && profile.completed_command_sequence==1 &&
      profile.insertion==PatternInsertionPolicy::reject_erase_commands && profile.violation &&
      profile.violation->kind==PatternViolationKind::erase_command && profile.violation->command_sequence==2,
      "insertion-only committed diagnostic misstates the accepted prefix");
  rejects(*session,"input_failed");
  session->stop();const auto after=session->checkpoint_state();
  check(after.runtime_image.bytes==before.runtime_image.bytes,"rejected erase changed native committed state");
  const auto image=session->checkpoint_image();
  {s04_alloc::Scope denied(0);const auto inspected=recovery::inspect_session_image(bytes(image));
    check(inspected.manifest.state_version==2 && s04_alloc::calls==0,"pattern inspection allocated or lost v2");}
  auto restored=QuerySession::restore_image(program,bytes(image));
  const auto recovered=restored->update_pattern_status();
  check(recovered.history==PatternHistory::restored_checkpoint && recovered.violation==profile.violation &&
      recovered.monitored_sequence==1 && restored->status().input_failed,"recovery dropped declared rejection metadata");
}

// Whole-command validation must detect B's premature final reference even when
// an unrelated arbitrary-table expiration would precede it in deadline order.
void watermark_contract(bool indexed,WindowFifoPolicy policy) {
  const auto program=CompiledProgram::standalone(source_plan(indexed));
  const std::array rules{ip::TableRule{TableId{0},false,UINT64_MAX},ip::TableRule{TableId{1},false,UINT64_MAX}};
  auto session=QuerySession::create_windowed(program,window_options(policy),{},declared(program,rules));session->start();
  win::command(*session,win::insertion(1,1,TableId{0},1,0));
  win::command(*session,win::insertion(2,2,TableId{1},2,1));
  win::command(*session,win::insertion(3,3,TableId{0},1,2));
  win::command(*session,win::insertion(4,4,TableId{3},3,0));
  const auto prefix=*session->window_state();const auto rows=win::rows(*session);const auto state=session->checkpoint_state();
  win::enqueue(*session,{5,io::AdvanceWatermark{11},{}});
  rejects(*session,"update_pattern_violation");
  check(*session->window_state()==prefix && win::rows(*session)==rows && session->progress().sequence==4,
      "rejected whole watermark published a metadata/unrelated-row prefix");
  const auto violation=session->update_pattern_status().violation;
  check(violation && violation->kind==PatternViolationKind::fifo_scope && violation->table==TableId{1} &&
      violation->label==2,"whole watermark did not identify the actual lifetime violation");
  session->stop();check(session->checkpoint_state().runtime_image.bytes==state.runtime_image.bytes,
      "whole-watermark rejection changed the committed engine");

  auto restored=QuerySession::restore_state(program,state);
  win::command(*restored,{5,io::WindowWithdraw{1},{}}); // metadata only; birth 1 survives
  const auto before=*restored->window_state();
  win::enqueue(*restored,{6,io::WindowWithdraw{2},{}});rejects(*restored,"update_pattern_violation");
  check(*restored->window_state()==before && before.counts.front().id==1,
      "explicit scope check used surviving labels instead of original physical birth");
}

void duplicate_contract(bool indexed) {
  const auto program=CompiledProgram::standalone(source_plan(indexed));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  auto session=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));session->start();
  win::command(*session,win::insertion(1,1,TableId{0},1,0));
  win::command(*session,win::insertion(2,2,TableId{0},1,100));
  win::command(*session,{3,io::AdvanceWatermark{10},{}});
  check(session->status().committed_sequence==1 && session->progress().sequence==3 &&
      !session->update_pattern_status().violation,"metadata-only expiration violated insertion-only");
  const auto state=session->checkpoint_image();
  auto restored=QuerySession::restore_image(program,bytes(state));
  win::enqueue(*restored,{4,io::WindowWithdraw{2},{}});rejects(*restored,"update_pattern_violation");
  check(restored->update_pattern_status().violation->kind==PatternViolationKind::physical_erase,
      "final duplicate reference was not a physical erase violation after restore");
}

// Independent lifetime-list model: it neither uses native birth IDs nor the
// implementation's sorted-prefix test. Rejected proposals restore the healthy
// checkpoint so later proposals can exercise the same accepted prefix.
struct Model {
  struct Label {std::uint64_t id;unsigned table;std::int64_t value;std::uint64_t timestamp;};
  struct Life {unsigned table;std::int64_t value;};
  std::vector<Label> labels;std::vector<Life> births;std::uint64_t watermark=0;
  bool remove(std::uint64_t id,bool per_table) {
    const auto at=std::find_if(labels.begin(),labels.end(),[&](const auto& x){return x.id==id;});check(at!=labels.end(),"oracle lost label");
    const auto target=*at;
    const auto references=std::count_if(labels.begin(),labels.end(),[&](const auto& x){return x.table==target.table && x.value==target.value;});
    if(references==1) {
      if(target.table==2)return false;
      const auto scope=[&](unsigned table){return table<2?7U:per_table?100U+table:0U;};
      if(scope(target.table)) {
        const auto oldest=std::find_if(births.begin(),births.end(),[&](const auto& life){return scope(life.table)==scope(target.table);});
        if(oldest->table!=target.table || oldest->value!=target.value)return false;
      }
      births.erase(std::find_if(births.begin(),births.end(),[&](const auto& life){return life.table==target.table && life.value==target.value;}));
    }
    labels.erase(at);return true;
  }
  bool apply(const io::WindowCommand& command,bool per_table) {
    if(const auto* insert=std::get_if<io::WindowInsert>(&command.command)) {
      const auto value=std::get<std::int64_t>(insert->values[0]);
      const auto table=static_cast<unsigned>(insert->table.value);
      if(std::none_of(labels.begin(),labels.end(),[&](const auto& x){return x.table==table && x.value==value;}))births.push_back({table,value});
      labels.push_back({insert->label,table,value,insert->timestamp});return true;
    }
    if(const auto* withdrawal=std::get_if<io::WindowWithdraw>(&command.command))return remove(withdrawal->label,per_table);
    const auto mark=std::get<io::AdvanceWatermark>(command.command).watermark;
    std::vector<std::pair<std::uint64_t,std::uint64_t>> order;
    for(const auto& label:labels)if(label.timestamp+10<=mark)order.emplace_back(label.timestamp+10,label.id);
    std::sort(order.begin(),order.end());
    for(const auto& [deadline,id]:order){static_cast<void>(deadline);if(!remove(id,per_table))return false;}
    watermark=mark;return true;
  }
};
void model_contract(bool indexed,bool per_table) {
  const auto program=CompiledProgram::standalone(source_plan(indexed));
  const std::array rules{ip::TableRule{TableId{0},false,7},ip::TableRule{TableId{1},false,7},ip::TableRule{TableId{2},true,0}};
  auto session=QuerySession::create_windowed(program,window_options(per_table?WindowFifoPolicy::physical_per_relation:WindowFifoPolicy::unrestricted),{},declared(program,rules));session->start();
  Model model;std::mt19937_64 random(9017);std::uint64_t next_label=0,sequence=0;unsigned accepted=0,rejected=0;
  for(unsigned step=0;step<140;++step) {
    io::WindowCommand command;command.sequence=sequence+1;
    const auto choice=random()%5;
    if(choice<3 || model.labels.empty()) command.command=io::WindowInsert{++next_label,TableId{random()%4},
        {std::int64_t(random()%4)},model.watermark+random()%8};
    else if(choice==3)command.command=io::WindowWithdraw{model.labels[static_cast<std::size_t>(random()%model.labels.size())].id};
    else command.command=io::AdvanceWatermark{model.watermark+random()%10};
    auto proposed=model;const bool allowed=proposed.apply(command,per_table);
    const auto checkpoint=session->checkpoint_state();const auto before=*session->window_state();
    if(allowed) {win::command(*session,command);model=std::move(proposed);++sequence;++accepted;}
    else {
      win::enqueue(*session,command);bool failed=false;
      try{static_cast<void>(session->begin_next());}catch(const Error& error){failed=error.code()=="update_pattern_violation" || error.code()=="window_fifo_violation";}
      check(failed && *session->window_state()==before,"lifetime-list oracle rejection differs or leaked a prefix");
      session=QuerySession::restore_state(program,checkpoint);++rejected;
    }
    Relation expected;for(const auto& label:model.labels)if(label.table==0)expected.insert(Row{label.value});
    check(win::rows(*session)==expected && session->progress().sequence==sequence &&
        session->update_pattern_status().completed_command_sequence==sequence,"model/result/committed monitor prefix differs");
  }
  check(accepted>50 && rejected>0,"mixed oracle did not exercise both outcomes");
  std::cout<<"mixed monitor indexed="<<indexed<<" per_table="<<per_table<<" accepted="<<accepted<<" rejected="<<rejected<<'\n';
}

// Separate scope IDs never imply a joint FIFO restriction. Metadata removal
// and an unrelated table's later birth must remain ordinary exact operations.
void separate_scopes() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},false,1},ip::TableRule{TableId{1},false,2}};
  auto session=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));session->start();
  win::command(*session,win::insertion(1,1,TableId{0},1,0));
  win::command(*session,win::insertion(2,2,TableId{1},2,0));
  win::command(*session,{3,io::WindowWithdraw{2},{}});
  check(session->window_state()->counts.size()==1 && !session->update_pattern_status().violation,
      "different explicit FIFO scopes were silently united");
}

void current_selection_contract() {
  namespace ps=planner::selection;
  namespace rs=runtime::selection;
  const auto fixture=c02_test::fixture();const auto candidates=c02_test::candidates(fixture);
  const auto program=CompiledProgram::standalone(planner::lower_tree(fixture.catalog,fixture.query,candidates.candidate(0)->tree()));
  const std::array rules{ip::TableRule{TableId{2},true,0}};
  auto options=declared(program,rules);WindowOptions windows;windows.managed_tables={TableId{0},TableId{1},TableId{2}};
  windows.fifo=WindowFifoPolicy::unrestricted;
  auto session=QuerySession::create_windowed(program,windows,{},options);session->start();
  session->configure_workload_statistics(c05_test::counters());
  ps::Request request;request.policy=ps::Policy::height_only;request.update_patterns=options.update_patterns->declaration;
  const ps::Source source=ps::PhysicalBasis{program};
  const auto selected=rs::select_current(candidates,source,*session,request);
  check(selected.stop==ps::Stop::complete && selected.selection &&
      c02_test::shape(selected.selection->selection().selected().tree())==1,
      "actual Session enforcement did not bind conditional current selection");
  auto bare=PhysicalRuntime::initialize(program,Database{{Relation{},Relation{},Relation{}}});
  check(rs::select_current(candidates,source,bare,request).stop==ps::Stop::unsupported_model,
      "bare runtime manufactured a Session monitor");
  const std::array different{ip::TableRule{TableId{0},true,0}};
  request.update_patterns=ip::Declaration::capture(program.account(),program,different);
  check(rs::select_current(candidates,source,*session,request).stop==ps::Stop::binding_mismatch,
      "current selection ignored the actual enforced rule set");
}

// Denial stays enabled through private cleanup. A retryable resource failure
// must not become a sticky semantic violation or publish a watermark prefix.
void allocation_contract() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  const auto make=[&] {
    auto value=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));value->start();
    win::command(*value,win::insertion(1,1,TableId{0},1,0));
    win::command(*value,win::insertion(2,2,TableId{0},1,100));
    win::enqueue(*value,{3,io::AdvanceWatermark{10},{}});return value;
  };
  std::size_t positions=0;
  {auto value=make();s04_alloc::Scope count;check(value->begin_next(),"healthy preflight missing");positions=s04_alloc::calls;}
  check(positions>0 && positions<1000,"preflight allocation control not finite");
  for(std::size_t cut=0;cut<positions;++cut) {
    auto value=make();const auto before=*value->window_state();const auto account=value.get_deleter().account();
    const auto resident=account.statistics().current;bool failed=false;
    {s04_alloc::Scope denied(static_cast<std::ptrdiff_t>(cut));
      try{static_cast<void>(value->begin_next());}catch(const std::bad_alloc&){failed=true;}}
    check(failed && !value->status().input_failed && !value->update_pattern_status().violation &&
        *value->window_state()==before && account.statistics().current==resident,
        "resource denial changed prefix/latch/storage");
    check(value->begin_next(),"resource retry lost the original command");
    check(value->update_pattern_status().completed_command_sequence==2,"private monitor preparation became committed");
    static_cast<void>(win::finish(*value));
    check(value->progress().sequence==3 && value->status().committed_sequence==1,
        "metadata-only retry did not commit its exact command boundary");
  }
  std::cout<<"declared watermark persistent allocation cuts="<<positions<<'\n';
}

// Error construction is fallible too. Denial remains active through unwinding;
// only a fully constructed semantic error may latch the rejected command.
void rejection_allocation_contract() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},false,9},ip::TableRule{TableId{1},false,9}};
  const auto make=[&] {
    auto value=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));value->start();
    win::command(*value,win::insertion(1,1,TableId{0},1,0));
    win::command(*value,win::insertion(2,2,TableId{1},2,1));
    win::command(*value,win::insertion(3,3,TableId{0},1,2));
    win::enqueue(*value,{4,io::AdvanceWatermark{11},{}});return value;
  };
  std::size_t positions=0;
  {auto value=make();s04_alloc::Scope count;rejects(*value,"update_pattern_violation");positions=s04_alloc::calls;}
  check(positions>0 && positions<1000,"rejection allocation control not finite");
  for(std::size_t cut=0;cut<positions;++cut) {
    auto value=make();const auto before=*value->window_state();const auto account=value.get_deleter().account();
    const auto resident=account.statistics().current;bool failed=false;
    {s04_alloc::Scope denied(static_cast<std::ptrdiff_t>(cut));
      try{static_cast<void>(value->begin_next());}catch(const std::bad_alloc&){failed=true;}}
    check(failed && !value->status().input_failed && !value->update_pattern_status().violation &&
        *value->window_state()==before && account.statistics().current==resident,
        "failed rejection construction latched a violation or changed committed storage");
    rejects(*value,"update_pattern_violation");
    check(value->status().input_failed && value->update_pattern_status().violation &&
        *value->window_state()==before,"retry lost semantic rejection or published a prefix");
  }
  std::cout<<"declared rejection persistent allocation cuts="<<positions<<'\n';
}

// Measure the controller's abstract work, then use fresh identical histories
// at the exact grant and one unit below it. This is not a CPU-time measurement.
void work_contract() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  const auto make=[&](std::uint64_t cap) {
    auto windows=window_options();windows.command_work_limit=cap;
    auto value=QuerySession::create_windowed(program,windows,{},declared(program,rules));value->start();
    for(std::uint64_t i=1;i<=8;++i)win::command(*value,win::insertion(i,i,TableId{0},1,i==8?100:0));
    return value;
  };
  auto measured=make(1000000);win::command(*measured,{9,io::AdvanceWatermark{10},{}});
  const auto work=measured->checkpoint_state().window->last_command_work;check(work>1,"missing preflight work");
  auto exact=make(work);win::command(*exact,{9,io::AdvanceWatermark{10},{}});
  check(exact->checkpoint_state().window->last_command_work==work && exact->progress().sequence==9,"exact preflight grant refused");
  auto short_value=make(work-1);const auto before=*short_value->window_state();
  win::enqueue(*short_value,{9,io::AdvanceWatermark{10},{}});rejects(*short_value,"resource_limit");
  check(!short_value->status().input_failed && !short_value->update_pattern_status().violation &&
      *short_value->window_state()==before,"preflight work refusal changed the committed prefix");
  const auto unordered_work=[&](bool interleaved) {
    auto value=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));value->start();
    for(std::uint64_t i=0;i<15;++i)win::command(*value,win::insertion(i+1,i+1,
        TableId{1+(interleaved?i%3:i/5)},static_cast<std::int64_t>(i),0));
    win::command(*value,{16,io::AdvanceWatermark{10},{}});
    check(value->window_state()->counts.empty(),"unordered work control retained an expired row");
    return value->checkpoint_state().window->last_command_work;
  };
  check(unordered_work(false)==unordered_work(true),"unrestricted preflight charged unnecessary table sorting");
  std::cout<<"declared watermark exact abstract work="<<work<<'\n';
}

// A v2 checkpoint survives actual file/log reconstruction, including a logged
// input with no durable decision. Replayed inputs pass through the same guard.
void journal_contract(bool indexed) {
  namespace journal=crown::session_journal_test;
  journal::Directory directory;const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");
  const auto program=CompiledProgram::standalone(source_plan(indexed));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  auto value=QuerySession::create_windowed(program,window_options(),{},declared(program,rules));value->start();
  win::command(*value,win::insertion(1,1,TableId{0},1,0));
  static_cast<void>(value->checkpoint_file(checkpoint));value->enable_journal(checkpoint,log,journal::options());
  win::command(*value,win::insertion(2,2,TableId{0},1,100));
  win::enqueue(*value,{3,io::AdvanceWatermark{10},{}});check(value->begin_next(),"pending journal mark missing");
  while(value->step()!=DeltaStep::prepared){}value.reset();
  SessionJournalRecoveryOptions recovery;recovery.journal=journal::options();
  value=QuerySession::restore_journal(program,checkpoint,log,recovery);
  check(value->update_pattern_status().history==PatternHistory::restored_checkpoint &&
      value->update_pattern_status().completed_command_sequence==2 && value->recovery_status().pending_input_sequence==3,
      "journal replay lost the declared committed/pending boundary");
  value->discard_recovered_output();value->start();check(value->begin_next(),"journal pending input was not retryable");
  static_cast<void>(win::finish(*value));
  const auto prefix=*value->window_state();const auto log_prefix=journal::contents(log);
  win::enqueue(*value,{4,io::WindowWithdraw{2},{}});rejects(*value,"update_pattern_violation");
  check(*value->window_state()==prefix && journal::contents(log)==log_prefix &&
      value->update_pattern_status().completed_command_sequence==3 && value->status().committed_sequence==1,
      "restored guard journaled or published a forbidden lifetime termination");
}

// Bind a measured pattern-conditioned choice to the real owner, publish its
// different tree through the existing durable barrier, then enforce and restore
// the same declaration against the installed program's actual physical hash.
void replacement_contract() {
  namespace ps=planner::selection;namespace rs=runtime::selection;
  const auto fixture=c02_test::fixture();const auto candidates=c02_test::candidates(fixture);
  const auto program=CompiledProgram::standalone(planner::lower_tree(fixture.catalog,fixture.query,candidates.candidate(0)->tree()));
  const std::array rules{ip::TableRule{TableId{2},true,0}};
  session_journal_test::Directory directory;
  auto options=declared(program,rules);WindowOptions windows;windows.managed_tables={TableId{0},TableId{1},TableId{2}};
  windows.fifo=WindowFifoPolicy::unrestricted;auto value=QuerySession::create_windowed(program,windows,{},options);value->start();
  SessionGenerationOptions generation;generation.journal=session_journal_test::options();
  value->enable_generation(directory.file("selected.root"),generation);
  value->configure_workload_statistics(c05_test::counters());ps::Request request;
  request.policy=ps::Policy::height_only;request.update_patterns=options.update_patterns->declaration;
  const auto selected=rs::select_for_reoptimization(candidates,ps::PhysicalBasis{program},*value,request);
  check(selected.selection.has_value(),"measured declared selection failed");
  reoptimization::Options change;change.forecast=reoptimization::Forecast{1000000000,1,UINT64_MAX};
  rs::begin_reoptimization(*value,*selected.selection,change);value->request_reoptimization_barrier();
  check(value->advance_reoptimization(100000).phase==reoptimization::Phase::verified,"declared target did not verify");
  const auto artifact=io::CompilerPlanArtifact::prepare(resource::MemoryAccount::create(32*1024*1024),selected.selection->selection().plan());
  check(value->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"declared target did not publish");
  const auto target=value->report_metadata().plan();const auto profile=value->update_pattern_status();
  const auto hash=std::string_view(profile.physical_sha256.data(),profile.physical_sha256.size());
  check(profile.declaration.matches(target) && hash==target.physical_sha256() &&
      hash!=program.physical_sha256(),"replacement retained stale physical identity");
  value->start();win::command(*value,win::insertion(1,1,TableId{2},1,0));
  const auto image=value->checkpoint_image();auto restored=QuerySession::restore_image(target,bytes(image));restored->start();
  win::enqueue(*restored,{2,io::WindowWithdraw{1},{}});rejects(*restored,"update_pattern_violation");
  check(restored->update_pattern_status().physical_sha256==profile.physical_sha256,"restored target profile changed its owning tree");
}

// Public checkpoint records are trusted history, but source, version, shape,
// violation context and receiving grants must still pass native admission.
void checkpoint_contract() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  auto value=QuerySession::create_typed(program,{},declared(program,rules));value->start();
  physical(*value,{1,TableId{0},SetOperation::insert,{std::int64_t{1}}});
  const auto image=value->checkpoint_image();
  SessionCheckpointLimits small;small.patterns.cells=0;bool failed=false;
  try{static_cast<void>(recovery::inspect_session_image(bytes(image),small));}
  catch(const recovery::ImageFailure& e){failed=e.fault()==recovery::ImageFault::limit;}
  check(failed,"v2 inspection ignored its rule grant");
  small={};small.patterns.work=0;failed=false;
  try{static_cast<void>(value->checkpoint_state(small));}
  catch(const recovery::ImageFailure& e){failed=e.fault()==recovery::ImageFault::work;}
  check(failed,"native checkpoint ignored declaration capture work");
  const auto denied=[&](auto mutate) {
    auto state=value->checkpoint_state();mutate(state);bool rejected=false;
    try{auto restored=QuerySession::restore_state(program,state);}
    catch(const recovery::ImageFailure&){rejected=true;}
    check(rejected,"native restore accepted malformed pattern metadata");
  };
  denied([](auto& state){state.version=1;});
  denied([](auto& state){state.pattern_origin_sequence=2;});
  denied([](auto& state){state.pattern_origin_command_sequence=1;});
  denied([&](auto& state){auto record=state.update_patterns->export_record();
    record.source_sha256[0]=record.source_sha256[0]=='0'?'1':'0';
    state.update_patterns=ip::Declaration::import(program.account(),record);});
  denied([](auto& state){state.pattern_violation=PatternViolation{PatternViolationKind::erase_command,TableId{0},2,0};});
  const auto state=value->checkpoint_state();small={};small.patterns.cells=0;failed=false;
  SessionRestoreOptions restore;restore.limits=small;
  try{auto restored=QuerySession::restore_state(program,state,restore);}
  catch(const ip::Failure& e){failed=e.fault()==ip::Fault::cell_limit;}
  check(failed,"native restore did not admit a fresh declaration copy");
  auto restored=QuerySession::restore_image(program,bytes(image));
  check(restored->run_context()->update_patterns->rules().data()!=value->run_context()->update_patterns->rules().data(),
      "restore retained the sender's declaration storage");
}

// Export actual owner-bound diagnostics for schema validation. Requested rules
// stay in run_context; live enforcement/rejection and restored provenance stay
// in session status. The unconfigured report omits both optional objects.
void report_contract(const std::filesystem::path& directory) {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array rules{ip::TableRule{TableId{0},true,0}};
  auto value=QuerySession::create_typed(program,{},declared(program,rules));value->start();
  const auto report=[&](QuerySession& owner,const char* name,const char* history,const char* state) {
    const auto text=io::write_explain_json(observability::PlanExplanation::capture(owner));
    const auto json=io::Json::parse(text);const auto& profile=json.at("session").at("update_patterns");
    check(profile.at("history_evidence")==history && profile.at("state")==state &&
        profile.at("maintenance_bound")=="not_asserted" &&
        json.at("run_context").at("session").at("update_patterns").at("rules").size()==1,
        "report conflated requested rules and actual enforcement/provenance");
    if(!directory.empty()){std::ofstream output(directory/name);output<<text;check(output.good(),"report evidence write failed");}
  };
  if(!directory.empty())std::filesystem::create_directories(directory);
  report(*value,"enforced.json","current_session","enforced_prefix");
  physical(*value,{1,TableId{0},SetOperation::insert,{std::int64_t{1}}});
  io::TransportBatch batch({io::InputEvent{{2,TableId{0},SetOperation::erase,{std::int64_t{999}}},{}}});
  check(value->enqueue(batch)==io::Admission::accepted,"report erase fixture missing");rejects(*value,"update_pattern_violation");
  report(*value,"rejected.json","current_session","rejected");value->stop();const auto image=value->checkpoint_image();
  auto restored=QuerySession::restore_image(program,bytes(image));report(*restored,"restored.json","trusted_restored_checkpoint","rejected");
  auto plain=QuerySession::create_typed(program);const auto unconfigured=io::Json::parse(io::write_explain_json(observability::PlanExplanation::capture(*plain)));
  check(!unconfigured.at("session").contains("update_patterns") &&
      !unconfigured.at("run_context").at("session").contains("update_patterns"),"default report acquired pattern-only fields");
}

void admission_contract() {
  const auto program=CompiledProgram::standalone(source_plan(false));
  const std::array fifo{ip::TableRule{TableId{0},false,1}};
  bool failed=false;try{auto value=QuerySession::create_typed(program,{},declared(program,fifo));}
  catch(const Error& e){failed=e.code()=="unsupported_update_pattern";}check(failed,"nonwindow FIFO manufactured history");
  auto options=declared(program,fifo);auto record=options.update_patterns->declaration.export_record();
  record.source_sha256[0]=record.source_sha256[0]=='0'?'1':'0';
  options.update_patterns->declaration=ip::Declaration::import(program.account(),record);
  failed=false;try{auto value=QuerySession::create_windowed(program,window_options(),{},options);}
  catch(const Error& e){failed=e.code()=="invalid_update_pattern";}check(failed,"foreign source declaration admitted");
  options=declared(program,fifo);options.update_patterns->capture_limits.work=0;
  failed=false;try{auto value=QuerySession::create_windowed(program,window_options(),{},options);}
  catch(const ip::Failure& e){failed=e.fault()==ip::Fault::work_limit;}check(failed,"runtime capture ignored its metadata grant");
  auto plain=QuerySession::create_typed(program);const auto image=plain->checkpoint_image();
  check(recovery::inspect_session_image(bytes(image)).manifest.state_version==1,"undeclared session lost v1 format");
}
}
int main(int argc,char** argv) {
  try {
    admission_contract();separate_scopes();current_selection_contract();allocation_contract();
    rejection_allocation_contract();work_contract();checkpoint_contract();replacement_contract();
    report_contract(argc>1?std::filesystem::path{argv[1]}:std::filesystem::path{});
    for(const bool indexed:{false,true}) {
      journal_contract(indexed);
      insertion_contract(indexed,false);insertion_contract(indexed,true);
      watermark_contract(indexed,WindowFifoPolicy::unrestricted);
      watermark_contract(indexed,WindowFifoPolicy::physical_per_relation);
      duplicate_contract(indexed);model_contract(indexed,false);model_contract(indexed,true);
    }
    std::cout<<"runtime declaration/monitor/recovery contracts passed\n";
  } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}

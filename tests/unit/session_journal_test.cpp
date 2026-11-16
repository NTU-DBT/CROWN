#include "session_journal_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::session_journal_test;
namespace {
void typed_case(bool indexed,unsigned kind) {
  Fixture f(indexed,kind);Database database;database.tables.resize(f.test.plan.source_catalog().tables.size());
  const auto account=f.session.get_deleter().account();
  for(std::size_t i=0;i<f.test.updates.size();++i) {
    const auto before=typed::oracle(f.test,database);const auto& update=f.test.updates[i];auto& table=database.tables[update.table.value];
    if(update.operation==SetOperation::insert)table.insert(update.values);else table.erase(update.values);
    const auto expected=kind==2?typed::Output{}:typed::difference(before,typed::oracle(f.test,database));f.offer(i);f.prepare();
    const auto input_log=contents(f.log);const auto pending=jp::scan(input_log);check(pending.pending && pending.pending->input.sequence==i+1 && pending.command_sequence==i,"input was not durable before preparation");
    check(f.session->status().committed_sequence==i && f.session->progress().sequence==i,"private epoch acknowledged input");
    f.session->commit();typed::Output actual;while(auto result=f.session->next_output())check(actual.emplace(result->operation,storage::export_row(result->tuple.values())).second,"duplicate signed output");
    check(actual==expected && typed::rows(*f.session)==typed::oracle(f.test,database),"journal changed native semantics");
    const auto log=contents(f.log);const auto state=jp::scan(log);const auto native=f.session->journal_state();
    check(!state.pending && state.records==1+2*(i+1) && state.physical_sequence==i+1 && state.command_sequence==i+1 &&
        native.enabled && !native.recovery_required && native.records==state.records && native.physical_sequence==i+1 && native.command_sequence==i+1,"durable decision/source/native sequence differs");
  }
  const auto old_checkpoint=contents(f.checkpoint),old_log=contents(f.log);
  for(const auto& target:{f.checkpoint,f.log}) {
    bool blocked=false;try{static_cast<void>(f.session->checkpoint_file(target));}catch(const SessionJournalFailure& e){blocked=e.fault()==SessionJournalFault::state;}
    check(blocked && contents(f.checkpoint)==old_checkpoint && contents(f.log)==old_log,"checkpoint replacement clobbered active recovery pair");
  }
  const auto log=contents(f.log);const auto header=jp::inspect(frames(log).front()).header;const auto stored=contents(f.checkpoint);
  check(header.checkpoint_sha256==sha256_fixed(stored) && header.query_id==options().query_id,"journal not bound to exact durable checkpoint/query identity");
  f.session.reset();auto writer=jp::File::open(account,f.log,header);writer.close();
  std::cout<<"session journal indexed="<<indexed<<" query="<<kind<<" prepared input/decision/state/output/source passed\n";
}
void windows(bool indexed) {
  Directory directory;const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");const auto plan=window::plan(indexed);
  auto source=QuerySession::create_windowed(plan,window::config(WindowFifoPolicy::global));auto reference=QuerySession::create_windowed(plan,window::config(WindowFifoPolicy::global));
  source->start();reference->start();static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());
  const Row one{std::int64_t{1}},two{std::int64_t{2}};
  const std::vector<io::WindowCommand> commands{{1,io::WindowInsert{1,TableId{0},one,1},{}},{2,io::WindowInsert{2,TableId{0},one,2},{}},
    {3,io::WindowInsert{3,TableId{0},two,3},{}},{4,io::WindowWithdraw{1},{}},{5,io::AdvanceWatermark{30},{}}};
  std::uint64_t physical=0,commits=0;
  for(const auto& command:commands) {
    typed::enqueue(*source,command);typed::enqueue(*reference,command);
    for(;;) {
      check(source->begin_next() && reference->begin_next(),"window journal fixture head missing");
      const auto current=contents(log);const auto prefix=jp::scan(current);check(prefix.pending && prefix.pending->input.sequence==command.sequence,"window input missing from log");
      check(typed::finish(*source)==typed::finish(*reference),"window journal output differs");++commits;
      const auto after=contents(log);const auto state=jp::scan(after);const auto progress=source->progress();const auto native=source->status().committed_sequence;
      check(state.physical_sequence==native && state.command_sequence==progress.sequence && state.records==1+command.sequence+commits &&
          source->window_state()==reference->window_state() && typed::rows(*source)==typed::rows(*reference),"window journal command/substep state differs");
      if(progress.sequence==command.sequence)break;
      check(state.pending && state.pending->next_substep>0 && state.physical_sequence>physical,"partial watermark lost durable physical substep");physical=state.physical_sequence;
    }
  }
  const auto saved=contents(log);const auto list=frames(saved);std::size_t inputs=0,metadata=0,partial=0;
  for(const auto frame:list){const auto info=jp::inspect(frame);inputs+=info.kind==jp::Kind::input;if(info.kind==jp::Kind::commit){metadata+=info.commit.kind==jp::CommitKind::metadata;partial+=!info.commit.completes_input;}}
  check(inputs==commands.size() && metadata>=2 && partial>=1,"window path missed metadata or partial-command records");
  std::cout<<"session window journal indexed="<<indexed<<" input deduplication, metadata and multi-physical watermark passed\n";
}
void duplicate_expiration(bool indexed,WindowFifoPolicy fifo) {
  Directory directory;auto source=QuerySession::create_windowed(window::plan(indexed),window::config(fifo));source->start();
  for(std::uint64_t label=1;label<=3;++label)static_cast<void>(window::command(*source,{label,io::WindowInsert{label,TableId{0},Row{std::int64_t{1}},label},{}}));
  const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());
  typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},{}});
  for(std::uint64_t step=0;step<3;++step) {
    check(source->begin_next(),"duplicate expiration head missing");const auto output=typed::finish(*source);const auto data=contents(log);const auto state=jp::scan(data);
    check(state.records==3+step && state.physical_sequence==(step==2?2U:1U) && state.command_sequence==(step==2?4U:3U) &&
        source->progress().sequence==(step==2?4U:3U) && source->status().committed_sequence==(step==2?2U:1U),"duplicate expiration counters differ");
    if(step<2)check(output.empty() && state.pending && state.pending->next_substep==step+1 && typed::rows(*source)==Relation{{Row{std::int64_t{1}}}},"incomplete metadata expiration lost row/input");
    else check(output==typed::Output{{SetOperation::erase,Row{std::int64_t{1}}}} && !state.pending && typed::rows(*source).empty(),"final duplicate expiration failed physical deletion");
  }
  const auto data=contents(log);const auto header=jp::inspect(frames(data).front()).header;const auto account=source.get_deleter().account();const auto fds=descriptors();source->drop();
  check(!source->journal_state().enabled && descriptors()+1==fds,"explicit drop retained journal resources");auto reopened=jp::File::open(account,log,header);reopened.close();
  std::cout<<"session duplicate expiration indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" partial metadata/final physical/drop release passed\n";
}
void stream_and_resources() {
  Directory directory;const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");const auto test=typed::fixture(false,1);
  SessionOptions config;config.input.format=io::InputFormat::csv;config.input.table=TableId{0};config.input.delimiter=';';config.input.source="csv";config.input.byte_offset=123;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>("y;x\n2;1\n3;2\n"),config);source->start();static_cast<void>(source->checkpoint_file(checkpoint));
  const auto account=source.get_deleter().account();const auto before=account.statistics().successful_allocations;std::size_t allocations=0;
  {s04_alloc::Scope count;source->enable_journal(checkpoint,log,options());allocations=s04_alloc::calls;}
  check(account.statistics().successful_allocations-before==allocations,"session journal enable escaped query account");
  for(std::uint64_t sequence=1;sequence<=2;++sequence) {
    check(source->begin_next(),"CSV journal record missing");static_cast<void>(typed::finish(*source));const auto bytes=contents(log);const auto records=frames(bytes);
    const auto input=jp::decode(account,records[static_cast<std::size_t>(2*sequence-1)]);const auto view=input.input_view();
    check(view.reader && view.reader->records==sequence && view.reader->bytes==4+4*sequence && view.reader->header_read &&
        input.csv_fields==recovery::ImageVector<std::uint64_t>({1,0},recovery::image_allocator<std::uint64_t>(account)) &&
        std::get<io::InputEventView>(view.item).source_position->offset==123+4*sequence,"CSV decoder/source origin/permutation not journaled");
  }
  check(source->progress().source_positions.at("csv")==131,"CSV source acknowledgment differs");
  const auto original=contents(checkpoint);source.reset();auto current=QuerySession::restore_file(CompiledProgram::standalone(test.plan),checkpoint,std::make_unique<std::istringstream>("y;x\n2;1\n"));
  current->start();check(current->begin_next(),"stale checkpoint fixture missing");static_cast<void>(typed::finish(*current));bool rejected=false;
  try{current->enable_journal(checkpoint,directory.file("stale.wal"),options());}catch(const SessionJournalFailure& e){rejected=e.fault()==SessionJournalFault::checkpoint;}
  check(rejected && !current->journal_state().enabled && !std::filesystem::exists(directory.file("stale.wal")) && contents(checkpoint)==original,"stale checkpoint journal binding published or replaced files");
  std::cout<<"session CSV pending decoder view/source offsets/permutation, enable account allocations="<<allocations<<" and exact checkpoint binding passed\n";
}
void all_stream_formats() {
  const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  for(const bool indexed:{false,true})for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool seeded:{false,true}) {
    Directory directory;const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");const auto test=typed::fixture(indexed,1);
    SessionOptions config;config.input=profile.options;auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),config);source->start();
    if(seeded){check(source->begin_next(),"seeded stream missing first row");static_cast<void>(typed::finish(*source));}
    static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());const auto account=source.get_deleter().account();
    for(std::uint64_t sequence=seeded?2U:1U;sequence<=2;++sequence) {
      check(source->begin_next(),"profile journal row missing");static_cast<void>(typed::finish(*source));const auto data=contents(log);const auto records=frames(data);
      const auto index=static_cast<std::size_t>(1+2*(sequence-1-(seeded?1U:0U)));const auto decoded=jp::decode(account,records[index]);const auto view=decoded.input_view();
      check(view.reader && view.reader->bytes==profile.bytes[static_cast<std::size_t>(sequence-1)] && view.reader->records==sequence &&
          view.reader->header_read==(profile.options.format==io::InputFormat::csv) && decoded.info.input.source_present &&
          decoded.info.input.source_offset==*profile.source_offsets[static_cast<std::size_t>(sequence-1)] &&
          std::get<io::InputEventView>(view.item).update.values==Row{static_cast<std::int64_t>(sequence),static_cast<std::int64_t>(sequence+1)},"stream log lost native row/decoder/source position");
      if(profile.options.format==io::InputFormat::csv)check(decoded.csv_fields.size()==2 && decoded.csv_fields[0]==1 && decoded.csv_fields[1]==0,"CSV header mapping lost");
      else check(decoded.csv_fields.empty(),"non-CSV stream acquired header fields");
    }
    check(source->progress().sequence==2 && source->status().committed_sequence==2,"stream source/physical completion differs");
    std::cout<<"session stream journal "<<profile.name<<" indexed="<<indexed<<" prior_record="<<seeded<<" full decoder/source origin passed\n";
  }
}
void lifecycle() {
  for(const auto control:{SessionState::created,SessionState::paused,SessionState::stopped}) {
    Directory directory;const auto test=typed::fixture(false,0);auto source=QuerySession::create_typed(test.plan);const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");
    if(control==SessionState::paused){source->start();source->pause();}else if(control==SessionState::stopped)source->stop();
    static_cast<void>(source->checkpoint_file(checkpoint));
    if(control==SessionState::stopped){bool rejected=false;try{source->enable_journal(checkpoint,log,options());}catch(const SessionJournalFailure& e){rejected=e.fault()==SessionJournalFault::state;}check(rejected && !std::filesystem::exists(log),"stopped session enabled journal");}
    else {source->enable_journal(checkpoint,log,options());source->start();typed::enqueue(*source,io::InputEvent{test.updates[0],{}});check(source->begin_next(),"created/paused journal missing input");static_cast<void>(typed::finish(*source));check(source->journal_state().command_sequence==1,"created/paused journal did not commit");}
  }
  Directory directory;auto source=QuerySession::create_windowed(window::plan(false),window::config(WindowFifoPolicy::global));source->start();const auto checkpoint=directory.file("base.crown"),log=directory.file("query.wal");
  static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());typed::enqueue(*source,io::WindowCommand{1,io::WindowWithdraw{99},{}});bool rejected=false;
  try{static_cast<void>(source->begin_next());}catch(const Error& e){rejected=e.code()=="invalid_window_command";}
  const auto data=contents(log);check(rejected && jp::scan(data).records==1 && !source->journal_state().recovery_required,"semantic window rejection was journaled or diagnostics changed");
  std::cout<<"session journal created/paused/stopped lifecycle and pre-WAL window semantic rejection passed\n";
}
void drain_and_retry() {
  Fixture f(false,1);f.offer();check(f.session->begin_next(),"drain fixture missing");f.session->pause();f.session->start_drain();f.session->drain();
  auto data=contents(f.log);check(jp::scan(data).command_sequence==1 && f.session->progress().sequence==1 && !f.session->next_output(),"drain bypassed durable decision");f.session->start();
  f.offer(1);f.prepare();bool failed=false;{s04_alloc::Scope fault(0);try{f.session->commit();}catch(const std::bad_alloc&){failed=true;}}
  check(failed && !f.session->journal_state().recovery_required && f.session->status().committed_sequence==1 && f.session->progress().sequence==1,"predecision allocation failure published or poisoned session");
  const auto pending=contents(f.log);check(jp::scan(pending).records==4 && jp::scan(pending).pending,"predecision failure lost input or appended decision");
  check(f.session->begin_next(),"predecision retry lost cached input");static_cast<void>(typed::finish(*f.session));
  const auto complete=contents(f.log);check(jp::scan(complete).records==5 && jp::scan(complete).command_sequence==2,"retry duplicated input or failed to publish");
  std::cout<<"session paused drain and predecision allocation failure/rollback/retry passed\n";
}
}
int main(){try{for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)typed_case(indexed,kind);windows(indexed);for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})duplicate_expiration(indexed,fifo);}stream_and_resources();all_stream_formats();lifecycle();drain_and_retry();}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

#include "session_journal_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
#include <fstream>
#include <tuple>
using namespace crown;
using namespace crown::runtime;
using namespace crown::session_journal_test;
namespace {
SessionJournalRecoveryOptions recovery_options(){SessionJournalRecoveryOptions result;result.journal=options();return result;}
using Events=std::vector<RecoveredResult>;
void append_events(QuerySession& session,Events& events) {
  const auto epoch=session.status().committed_sequence;
  while(auto value=session.next_output())events.push_back({options().query_id,options().generation,epoch,std::move(*value)});
}
Events finish_events(QuerySession& session){while(session.step()!=DeltaStep::prepared){}session.commit();Events events;append_events(session,events);return events;}
Events recovered(QuerySession& session){Events events;while(auto value=session.next_recovered_output())events.push_back(std::move(*value));return events;}
void same_events(const Events& actual,const Events& expected) {
  check(actual.size()==expected.size(),"replay event count differs");std::vector<bool> seen(expected.size());
  for(const auto& value:actual){bool found=false;for(std::size_t i=0;i<expected.size();++i)if(!seen[i] && value.same_identity(expected[i])){seen[i]=true;found=true;break;}check(found,"replayed semantic event identity differs");}
}
void typed_case(bool indexed,unsigned kind,bool pending_input) {
  Fixture f(indexed,kind);Events events;
  for(std::size_t i=0;i<3;++i){f.offer(i);f.prepare();f.session->commit();append_events(*f.session,events);}
  const auto rows=typed::rows(*f.session);const auto progress=f.session->progress();const auto data=contents(f.log);const auto records=jp::scan(data).records;
  if(pending_input){f.offer(3);f.prepare();}
  f.session.reset();const auto compiler=CompiledProgram::standalone(f.test.plan);auto result=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());typed::grant(*result,indexed);
  check(result->status().state==SessionState::paused && result->status().committed_sequence==3 && result->progress()==progress && typed::rows(*result)==rows,"typed native replay state/source/control differs");
  const auto status=result->recovery_status();check(status.records==records+(pending_input?1U:0U) && status.pending_input_sequence.has_value()==pending_input,"replay pending input report differs");
  same_events(recovered(*result),events);check(result->recovery_status().output_remaining==0 && result->recovery_status().output_bytes==0,"recovery output buffer retained after final transfer");
  result->start();if(!pending_input)typed::enqueue(*result,io::InputEvent{f.test.updates[3],io::SourcePosition{"test",103}});
  check(result->begin_next(),"recovered next input unavailable");static_cast<void>(typed::finish(*result));const auto after=contents(f.log);
  check(jp::scan(after).records==9 && result->status().committed_sequence==4 && result->progress().sequence==4,"resume duplicated input or lost source/physical counter");
  std::cout<<"native replay typed indexed="<<indexed<<" query="<<kind<<" pending="<<pending_input<<" state/source/output identities/next update passed\n";
}
std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) {
  switch(profile.options.format) {
    case io::InputFormat::jsonl:return io::write_input_json(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int64_t{4}}},io::SourcePosition{"jsonl-source",30}},catalog)+"\n";
    case io::InputFormat::binary:return io::write_input_binary(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int64_t{4}}},io::SourcePosition{"binary-source",50}},catalog);
    case io::InputFormat::csv:return profile.options.header?"4;3\n":"3;4\n";
    case io::InputFormat::legacy_signed:return "+,3,4\n";
    case io::InputFormat::legacy_relations:return "+,E,3,4\n";
    case io::InputFormat::legacy_insert_only:return "3,4\n";
    case io::InputFormat::legacy_flags:return "1,3,4\n";
    case io::InputFormat::legacy_timestamp_flags:return "30,1,3,4\n";
  }
  throw std::runtime_error("unknown stream profile");
}
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool baseline_first,bool commit_second,bool seek) {
  Directory dir;const auto test=typed::fixture(indexed,1);const auto checkpoint=dir.file("base.crown"),log=dir.file("query.wal");SessionOptions config;config.input=profile.options;const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  const auto tail_record=third_record(profile,catalog);const auto full_source=profile.data+tail_record;config.input.limits.records=3;config.input.limits.total_bytes=full_source.size();
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(full_source),config);source->start();
  if(baseline_first){check(source->begin_next(),"stream first seed missing");static_cast<void>(typed::finish(*source));}
  static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());Events events;
  if(!baseline_first){check(source->begin_next(),"first stream event missing");auto first=finish_events(*source);events.insert(events.end(),std::make_move_iterator(first.begin()),std::make_move_iterator(first.end()));}
  check(source->begin_next(),"second stream event missing");if(commit_second){auto second=finish_events(*source);events.insert(events.end(),std::make_move_iterator(second.begin()),std::make_move_iterator(second.end()));}
  source.reset();auto restore=recovery_options();restore.seek_source_from_origin=seek;const auto tail=seek?full_source:tail_record;
  auto result=QuerySession::restore_journal(CompiledProgram::standalone(test.plan),checkpoint,log,restore,std::make_unique<std::istringstream>(tail));typed::grant(*result,indexed);
  const auto status=result->recovery_status();check(status.reader_bytes==profile.bytes[1] && status.reader_records==2 && status.pending_input_sequence.has_value()==!commit_second &&
      result->progress().sequence==(commit_second?2U:1U),"stream continuation/cached/accepted counters differ");
  same_events(recovered(*result),events);result->start();if(!commit_second){check(result->begin_next(),"cached stream event missing after replay");static_cast<void>(typed::finish(*result));}
  check(result->begin_next(),"post-replay third input skipped by continuation");static_cast<void>(typed::finish(*result));
  check(!result->begin_next() && result->progress().sequence==3 && result->status().committed_sequence==3 && typed::rows(*result)==Relation{{Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}},{Row{std::int64_t{2},std::int64_t{3},std::int64_t{4}}}},"stream post-replay next input/EOF differs");
  const auto state=result->checkpoint_state();const auto& reader=std::get<io::ReaderCheckpoint>(state.source);
  check(reader.bytes==full_source.size() && reader.records==3 && reader.header_read==(profile.options.format==io::InputFormat::csv && profile.options.header),"reader checkpoint origin differs after replay");
  std::cout<<"native replay stream "<<profile.name<<" indexed="<<indexed<<" baseline_first="<<baseline_first<<" pending="<<!commit_second<<" seek="<<seek<<" decoder/source/EOF passed\n";
}
void csv_variants(bool indexed) {
  const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};auto quoted=session_journal_stream_test::cases(catalog)[2];quoted.name="csv_quoted_crlf";quoted.data="\"y\";\"x\"\r\n2;1\r\n3;2\r\n";quoted.bytes={14,19};quoted.source_offsets={109,114};
  auto headerless=quoted;headerless.name="csv_headerless";headerless.options.header=false;headerless.data="1;2\n2;3\n";headerless.bytes={4,8};headerless.source_offsets={100,104};
  for(const auto* profile:{&quoted,&headerless})for(const bool baseline:{false,true})for(const bool committed:{false,true})stream_case(indexed,*profile,baseline,committed,!baseline);
  Directory dir;const auto test=typed::fixture(indexed,3);SessionOptions config;config.input.format=io::InputFormat::csv;config.input.table=TableId{0};config.input.source="nullary";config.input.byte_offset=100;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>("\"\"\r\n\r\n"),config);source->start();const auto checkpoint=dir.file("base.crown"),log=dir.file("query.wal");static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());check(source->begin_next(),"nullary CSV missing");auto expected=finish_events(*source);source.reset();
  auto restore=recovery_options();restore.seek_source_from_origin=true;auto result=QuerySession::restore_journal(CompiledProgram::standalone(test.plan),checkpoint,log,restore,std::make_unique<std::istringstream>("\"\"\r\n\r\n"));same_events(recovered(*result),expected);check(result->recovery_status().reader_bytes==6 && result->progress().source_positions.at("nullary")==104,"nullary quoted CSV header origin differs");
  std::cout<<"native replay nullary quoted CSV indexed="<<indexed<<" exact header-byte bounds passed\n";
}
void windows(bool indexed,WindowFifoPolicy fifo,unsigned committed_steps) {
  Directory dir;const auto plan=window::plan(indexed);auto source=QuerySession::create_windowed(plan,window::config(fifo));source->start();
  for(std::uint64_t label=1;label<=3;++label)static_cast<void>(window::command(*source,{label,io::WindowInsert{label,TableId{0},Row{std::int64_t{1}},label},{}}));
  const auto checkpoint=dir.file("base.crown"),log=dir.file("query.wal");static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());
  typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},io::SourcePosition{"wm",100}});Events events;
  for(unsigned step=0;step<committed_steps;++step){check(source->begin_next(),"watermark step missing");auto output=finish_events(*source);events.insert(events.end(),std::make_move_iterator(output.begin()),std::make_move_iterator(output.end()));}
  if(committed_steps==0){check(source->begin_next(),"pending watermark missing");source->pause();source->stop();}
  const auto expected=committed_steps==0?std::optional<WindowCanonicalState>{}:source->window_state();source.reset();
  auto result=QuerySession::restore_journal(CompiledProgram::standalone(plan),checkpoint,log,recovery_options());typed::grant(*result,indexed);
  if(expected){check(result->window_state()==expected,"partial metadata window state differs");}
  same_events(recovered(*result),events);result->start();
  for(unsigned step=committed_steps;step<3;++step){check(result->begin_next(),"resumed watermark missing");static_cast<void>(typed::finish(*result));}
  check(result->progress().sequence==4 && result->status().committed_sequence==2 && typed::rows(*result).empty() && !result->window_state()->active_command,"watermark resume duplicated/lost physical deletion");
  const auto data=contents(log);check(jp::scan(data).records==5 && !jp::scan(data).pending,"watermark replay re-journaled committed substeps");
  std::cout<<"native replay window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" committed_steps="<<committed_steps<<" pending metadata/physical state passed\n";
}
void put(const std::string& path,std::string_view data) {std::ofstream out(path,std::ios::binary|std::ios::trunc);out.write(data.data(),static_cast<std::streamsize>(data.size()));check(static_cast<bool>(out),"test file write failed");}
void truncations() {
  Fixture f;f.offer();f.prepare();f.session->commit();while(f.session->next_output()){}f.session.reset();const auto full=contents(f.log);const auto list=frames(full);const auto header_size=list[0].size();const auto compiler=CompiledProgram::standalone(f.test.plan);
  for(std::size_t cut=header_size;cut<=full.size();++cut) {
    put(f.log,std::string_view(full).substr(0,cut));auto result=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());
    const bool complete=cut==full.size(),input=cut>=header_size+list[1].size();
    check(result->progress().sequence==(complete?1U:0U) && result->recovery_status().pending_input_sequence.has_value()==(input && !complete),"native prefix recovery accepted torn input/decision");
    result->discard_recovered_output();result->start();if(!complete){if(!input)typed::enqueue(*result,io::InputEvent{f.test.updates[0],io::SourcePosition{"test",100}});check(result->begin_next(),"repaired prefix input missing");static_cast<void>(typed::finish(*result));}
    check(result->progress().sequence==1 && typed::rows(*result)==Relation{{f.test.updates[0].values}} && contents(f.log)==full,"tail recovery/retry duplicated or lost native input/decision");
  }
  put(f.log,std::string_view(full).substr(0,full.size()-1));auto no_repair=recovery_options();no_repair.repair_torn_tail=false;bool rejected=false;
  try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,no_repair);}catch(const SessionJournalFailure& e){rejected=e.fault()==SessionJournalFault::tail;}
  check(rejected && contents(f.log)==full.substr(0,full.size()-1),"explicit no-repair policy changed torn file");
  auto bad=full;bad.back()^=1;put(f.log,bad);rejected=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());}catch(const jp::Failure&){rejected=true;}
  check(rejected && contents(f.log)==bad,"complete corrupted decision was repaired or accepted");
  std::cout<<"native replay every input/decision byte cut="<<full.size()-header_size+1<<" explicit repair/no-repair/corruption and exact next commit passed\n";
}
void malformed_native() {
  Directory dir;const auto plan=window::plan(false);auto source=QuerySession::create_windowed(plan,window::config(WindowFifoPolicy::global));source->start();
  static_cast<void>(window::command(*source,{1,io::WindowInsert{1,TableId{0},Row{std::int64_t{1}},1},{}}));static_cast<void>(window::command(*source,{2,io::WindowInsert{2,TableId{0},Row{std::int64_t{1}},2},{}}));
  const auto checkpoint=dir.file("base.crown"),log=dir.file("query.wal");static_cast<void>(source->checkpoint_file(checkpoint));source->enable_journal(checkpoint,log,options());typed::enqueue(*source,io::WindowCommand{3,io::AdvanceWatermark{30},{}});check(source->begin_next(),"forged transition source missing");static_cast<void>(typed::finish(*source));source.reset();
  auto data=contents(log);const auto list=frames(data);auto account=resource::MemoryAccount::create(1024*1024);const auto original=jp::inspect(list[2]);auto wrong=original.commit;
  wrong.kind=jp::CommitKind::physical;wrong.physical_sequence=2;auto encoded=jp::encode(account,2,jp::PayloadView{wrong});std::string forged(list[0]);forged.append(list[1]);forged.append(encoded.bytes.data(),encoded.bytes.size());put(log,forged);
  static_cast<void>(jp::scan(forged));bool rejected=false;try{auto value=QuerySession::restore_journal(CompiledProgram::standalone(plan),checkpoint,log,recovery_options());}catch(const SessionJournalFailure& e){rejected=e.fault()==SessionJournalFault::transition;}
  check(rejected && contents(log)==forged,"checksum-valid decision differing from native metadata transition accepted");
  const auto test=typed::fixture(false,1);const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};const auto profiles=session_journal_stream_test::cases(catalog);const auto& profile=profiles[2];
  SessionOptions config;config.input=profile.options;auto stream=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),config);stream->start();check(stream->begin_next(),"CSV baseline missing");static_cast<void>(typed::finish(*stream));const auto csv_checkpoint=dir.file("csv.crown"),csv_log=dir.file("csv.wal");static_cast<void>(stream->checkpoint_file(csv_checkpoint));stream->enable_journal(csv_checkpoint,csv_log,options());check(stream->begin_next(),"CSV pending record missing");stream.reset();
  const auto csv=contents(csv_log);const auto csv_frames=frames(csv);const auto decoded=jp::decode(account,csv_frames[1]);auto input=decoded.input_view();const std::array<std::size_t,2> changed{0,1};input.reader->csv_fields=changed;auto frame=jp::encode(account,1,jp::PayloadView{input});forged=std::string(csv_frames[0]);forged.append(frame.bytes.data(),frame.bytes.size());put(csv_log,forged);static_cast<void>(jp::scan(forged));
  rejected=false;auto restore=recovery_options();restore.seek_source_from_origin=true;
  try{auto value=QuerySession::restore_journal(CompiledProgram::standalone(test.plan),csv_checkpoint,csv_log,restore,std::make_unique<std::istringstream>(profile.data));}catch(const recovery::ImageFailure& e){rejected=e.fault()==recovery::ImageFault::binding;}
  check(rejected && contents(csv_log)==forged,"checkpoint-known CSV permutation changed during native replay");
  for(const auto& text_profile:profiles) {
    if(text_profile.options.format==io::InputFormat::jsonl || text_profile.options.format==io::InputFormat::binary || text_profile.options.format==io::InputFormat::legacy_timestamp_flags)continue;
    Directory files;SessionOptions settings;settings.input=text_profile.options;auto current=QuerySession::create(test.plan,std::make_unique<std::istringstream>(text_profile.data),settings);current->start();check(current->begin_next(),"offset baseline missing");static_cast<void>(typed::finish(*current));
    const auto base=files.file("base.crown"),wal=files.file("query.wal");static_cast<void>(current->checkpoint_file(base));current->enable_journal(base,wal,options());check(current->begin_next(),"offset pending row missing");current.reset();
    const auto original=contents(wal);const auto items=frames(original);const auto row=jp::decode(account,items[1]);auto native=row.input_view();++std::get<io::InputEventView>(native.item).source_position->offset;const auto changed_frame=jp::encode(account,1,jp::PayloadView{native});std::string changed_log(items[0]);changed_log.append(changed_frame.bytes.data(),changed_frame.bytes.size());put(wal,changed_log);static_cast<void>(jp::scan(changed_log));
    bool rejected_offset=false;try{auto value=QuerySession::restore_journal(CompiledProgram::standalone(test.plan),base,wal,restore,std::make_unique<std::istringstream>(text_profile.data));}catch(const recovery::ImageFailure& e){rejected_offset=e.fault()==recovery::ImageFault::binding;}
    check(rejected_offset && contents(wal)==changed_log,"known text record-start offset accepted in-record forgery");
  }
  {Directory first;SessionOptions settings;settings.input=profile.options;settings.input.limits.total_bytes=100;auto current=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),settings);current->start();const auto base=first.file("base.crown"),wal=first.file("query.wal");static_cast<void>(current->checkpoint_file(base));current->enable_journal(base,wal,options());check(current->begin_next(),"first CSV row missing");current.reset();
    const auto original=contents(wal);const auto items=frames(original);const auto row=jp::decode(account,items[1]);auto native=row.input_view();std::get<io::InputEventView>(native.item).source_position->offset=110;native.reader->bytes=15;
    const auto changed=jp::encode(account,1,jp::PayloadView{native});std::string forged_first(items[0]);forged_first.append(changed.bytes.data(),changed.bytes.size());put(wal,forged_first);static_cast<void>(jp::scan(forged_first));
    bool invalid_header=false;try{auto value=QuerySession::restore_journal(CompiledProgram::standalone(test.plan),base,wal,recovery_options(),std::make_unique<std::istringstream>(""));}catch(const recovery::ImageFailure&){invalid_header=true;}
    check(invalid_header && contents(wal)==forged_first,"first CSV source offset outside possible quoted-header lengths accepted");}
  std::cout<<"native replay checksum-valid semantic transition and checkpoint-known CSV permutation forgeries rejected without file mutation\n";
}
void caps_and_identity() {
  Fixture f;f.offer();f.prepare();f.session->commit();Events expected;append_events(*f.session,expected);f.session.reset();const auto compiler=CompiledProgram::standalone(f.test.plan);
  auto result=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());const auto status=result->recovery_status();const auto reported=result->capture_statistics_context(std::nullopt);check(reported.status().output_remaining==status.output_remaining && reported.status().phase==SessionPhase::output,"recovery output status/observation disagrees");auto output=recovered(*result);same_events(output,expected);result.reset();
  check(!output.empty(),"identity fixture empty");auto same=output[0];same.value.ordinal+=99;check(output[0].same_identity(same),"identity depends on output ordinal");same.generation++;check(!output[0].same_identity(same),"identity lost generation");same=output[0];same.physical_sequence++;check(!output[0].same_identity(same),"identity lost physical epoch");
  auto exact=recovery_options();exact.decode_work=status.decode_work;{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,exact);value->discard_recovered_output();}
  auto source_exact=recovery_options();source_exact.source_work=status.source_work;{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,source_exact);value->discard_recovered_output();}
  --source_exact.source_work;bool source_under=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,source_exact);}catch(const recovery::ImageFailure& e){source_under=e.fault()==recovery::ImageFault::work;}check(source_under,"one-under cumulative source work accepted");
  auto bytes_exact=recovery_options();bytes_exact.output_bytes=status.output_bytes;{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,bytes_exact);value->discard_recovered_output();}
  --bytes_exact.output_bytes;bool bytes_under=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,bytes_exact);}catch(const recovery::ImageFailure& e){bytes_under=e.fault()==recovery::ImageFault::limit;}check(bytes_under,"one-under recovery output bytes accepted");
  --exact.decode_work;bool under=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,exact);}catch(const recovery::ImageFailure& e){under=e.fault()==recovery::ImageFault::work;}catch(const jp::Failure& e){under=e.fault()==jp::Fault::work;}check(under,"one-under replay codec work accepted");
  auto bounded=recovery_options();bounded.output_rows=0;bool limited=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,bounded);}catch(const recovery::ImageFailure& e){limited=e.fault()==recovery::ImageFault::limit;}check(limited,"replay output row cap ignored");
  auto wrong=recovery_options();++wrong.journal.generation;bool binding=false;try{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,wrong);}catch(const jp::Failure& e){binding=e.fault()==jp::Fault::binding;}check(binding,"wrong durable generation accepted");
  {Fixture multiple;for(std::size_t i=0;i<2;++i){multiple.offer(i);multiple.prepare();multiple.session->commit();while(multiple.session->next_output()){}}multiple.session.reset();const auto model=CompiledProgram::standalone(multiple.test.plan);
    auto first=QuerySession::restore_journal(model,multiple.checkpoint,multiple.log,recovery_options());const auto used=first->recovery_status().source_work;first.reset();auto cap=recovery_options();cap.source_work=used;
    {auto value=QuerySession::restore_journal(model,multiple.checkpoint,multiple.log,cap);value->discard_recovered_output();}--cap.source_work;bool bounded_source=false;
    try{auto value=QuerySession::restore_journal(model,multiple.checkpoint,multiple.log,cap);}catch(const recovery::ImageFailure& e){bounded_source=e.fault()==recovery::ImageFault::work;}check(bounded_source,"source work grant reset between replayed inputs");}
  const auto before=descriptors();{auto value=QuerySession::restore_journal(compiler,f.checkpoint,f.log,recovery_options());value->drop();}check(descriptors()==before,"recovery/drop retained descriptors");
  std::cout<<"native replay exact/under codec work, bounded output, generation, stable identity and drop cleanup passed\n";
}
}
int main(){try{
  for(const bool indexed:{false,true}) {
    for(unsigned kind=0;kind<6;++kind)for(const bool pending:{false,true})typed_case(indexed,kind,pending);
    const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
    for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool baseline:{false,true})for(const bool committed:{false,true})stream_case(indexed,profile,baseline,committed,!baseline);
    csv_variants(indexed);
    for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned step=0;step<=3;++step)windows(indexed,fifo,step);
  }
  caps_and_identity();truncations();malformed_native();
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

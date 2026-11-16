#include "history_retirement_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::history_retirement_test;
namespace {
void typed_case(bool indexed,unsigned kind) {
  RetirementFixture f(indexed,kind);const auto selected=f.session->generation_state().selected;const auto sink=f.session->local_sink_state();const auto cp=contents(f.path(3,".ckpt")),wal=contents(f.path(3,".wal")),output_bytes=contents(f.sink);
  f.history(true);f.session->retire_generation_history();f.history(false);const auto after=f.session->generation_state();auto expected=selected;expected.first_generation=3;
  check(after.selected==expected && !after.retirement_pending && f.session->local_sink_state().persisted.header==sink.persisted.header && contents(f.path(3,".ckpt"))==cp && contents(f.path(3,".wal"))==wal && contents(f.sink)==output_bytes,"retirement changed selected pair, local origin or native boundary");
  const auto root=contents(f.root);f.session->retire_generation_history();check(contents(f.root)==root,"empty retirement rewrote selected root");
  f.session.reset();{auto bare=QuerySession::restore_generation(f.program,f.root,generation_test::recovery_options());check(bare->status().committed_sequence==3 && typed::rows(*bare)==typed::oracle(f.test,f.database),"retired pair unavailable to native checkpoint/log recovery");}
  f.verify();std::cout<<"retirement typed indexed="<<indexed<<" query="<<kind<<" selected pair/output/oracle/idempotence/next update passed\n";
}
void retention_reuse() {
  RetirementFixture f;bool capped=false;try{f.session->rotate_generation();}catch(const recovery::GenerationFailure& e){capped=e.fault()==recovery::GenerationFault::limit;}check(capped,"retention fixture did not reach finite pair cap");
  f.session->retire_generation_history();f.session->rotate_generation();check(f.session->generation_state().selected.generation==4 && f.session->generation_state().selected.first_generation==3,"retirement did not free retained pair capacity");
  f.session->retire_generation_history();check(!std::filesystem::exists(f.path(3,".ckpt")) && !std::filesystem::exists(f.path(3,".wal")) && f.session->generation_state().selected.first_generation==4,"second retirement did not use new selected checkpoint coverage");
  f.commit(3);static_cast<void>(f.session->deliver_local_epoch());check(f.session->read_local_epoch(4).generation==4,"retention reuse changed new output generation");
  std::cout<<"retirement reuses bounded retention after durable rotation; local output origin preserved passed\n";
}
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
  Directory directory;const auto test=typed::fixture(indexed,1);const auto root=directory.file("stream.root"),sink=directory.file("output.sink");SessionOptions config;config.input=profile.options;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),config);source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(sink,options());
  check(source->begin_next(),"retirement first stream input absent");finish(*source);static_cast<void>(source->deliver_local_epoch());source->rotate_generation();check(source->begin_next(),"retirement second stream input absent");
  if(pending){bool rejected=false;try{source->retire_generation_history();}catch(const Error&){rejected=true;}check(rejected && std::filesystem::exists(generation_test::path(root,1,".wal")),"pending stream input authorized retirement");}
  finish(*source);static_cast<void>(source->deliver_local_epoch());source->retire_generation_history();source.reset();auto recovery=generation_test::recovery_options();recovery.replay.seek_source_from_origin=true;
  auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(test.plan),root,recovery,sink,options(),std::make_unique<std::istringstream>(profile.data));
  check(value->generation_state().selected.first_generation==2 && value->recovery_status().reader_bytes==profile.bytes[1] && value->recovery_status().reader_records==2 && value->local_sink_receipt().sequence()==2 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::insert,Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"retirement lost source/header or accepted stream output");
  value->start();check(!value->begin_next() && value->progress().sequence==2,"retirement duplicated/lost resumed stream source");
  std::cout<<"retirement stream "<<profile.name<<" indexed="<<indexed<<" pending="<<pending<<" decoder/header/accepted epoch/EOF passed\n";
}
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned cut) {
  Directory directory;const auto root=directory.file("window.root"),sink=directory.file("output.sink");const auto plan=window::plan(indexed);auto source=QuerySession::create_windowed(plan,window::config(fifo));source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(sink,options());
  for(std::uint64_t i=1;i<=3;++i){typed::enqueue(*source,io::WindowCommand{i,io::WindowInsert{i,TableId{0},Row{std::int64_t{1}},i},{}});check(source->begin_next(),"retirement window insert absent");finish(*source);static_cast<void>(source->deliver_local_epoch());}source->rotate_generation();
  typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},{}});
  for(unsigned step=0;step<3;++step){check(source->begin_next(),"retirement watermark step absent");if(cut==0 && step==0){bool rejected=false;try{source->retire_generation_history();}catch(const Error&){rejected=true;}check(rejected,"private watermark authorized retirement");}
    finish(*source);static_cast<void>(source->deliver_local_epoch());if(cut==step+1 && cut<3){bool rejected=false;try{source->retire_generation_history();}catch(const Error&){rejected=true;}check(rejected,"partial metadata command authorized retirement");}}
  source->retire_generation_history();source.reset();auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(plan),root,generation_test::recovery_options(),sink,options());
  check(value->generation_state().selected.first_generation==2 && value->status().committed_sequence==2 && value->progress().sequence==4 && value->local_sink_state().persisted.epochs==2 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::erase,Row{std::int64_t{1}}}},"retirement changed physical/metadata window identity");
  value->start();typed::enqueue(*value,io::WindowCommand{5,io::WindowInsert{5,TableId{0},Row{std::int64_t{9}},31},{}});check(value->begin_next(),"post-retirement window insert absent");finish(*value);static_cast<void>(value->deliver_local_epoch());check(typed::rows(*value)==Relation{{Row{std::int64_t{9}}}} && value->local_sink_receipt().sequence()==3,"retirement changed next window update");
  std::cout<<"retirement window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" cut="<<cut<<" metadata guards/physical recovery/next update passed\n";
}
void gates() {
  {generation_test::Fixture plain;plain.session->rotate_generation();const auto root=contents(plain.name);bool rejected=false;
    try{plain.session->retire_generation_history();}catch(const Error&){rejected=true;}check(rejected && contents(plain.name)==root && std::filesystem::exists(generation_test::path(plain.name,1,".wal")),"plain output consumption fabricated retirement authority");}
  {RetirementFixture f;const auto root=contents(f.root),sink=contents(f.sink);f.commit(3);bool rejected=false;try{f.session->retire_generation_history();}catch(const Error&){rejected=true;}
    check(rejected && contents(f.root)==root && contents(f.sink)==sink && !std::filesystem::exists(f.root+".retire"),"undelivered native output authorized history removal");f.history(true);static_cast<void>(f.session->deliver_local_epoch());f.session->retire_generation_history();f.history(false);}
  {RetirementFixture f;auto report=f.session->generation_state();report.selected.first_generation=report.selected.generation;check(f.session->generation_state().selected.first_generation==1,"mutable generation report changed retirement authority");
    typed::enqueue(*f.session,io::InputEvent{f.test.updates[3],io::SourcePosition{"feed",40}});check(f.session->begin_next(),"retirement private barrier input absent");bool rejected=false;try{f.session->retire_generation_history();}catch(const Error&){rejected=true;}check(rejected && !std::filesystem::exists(f.root+".retire"),"private occurrence fanout authorized retirement");f.history(true);}
  {RetirementFixture f;const auto path=f.path(3,".ckpt"),original=contents(path),root=contents(f.root);auto corrupt=original;corrupt.back()^=1;generation_test::put(path,corrupt);bool rejected=false;
    try{f.session->retire_generation_history();}catch(const recovery::ImageFailure&){rejected=true;}check(rejected && contents(f.root)==root && !std::filesystem::exists(f.root+".retire"),"corrupt selected checkpoint authorized deletion");f.history(true);generation_test::put(path,original);f.session->retire_generation_history();f.history(false);}
  std::cout<<"retirement rejects caller reports/no sink/unaccepted delivery/private fanout/corrupt checkpoint without deletion passed\n";
}
void pending_and_hostile() {
  RetirementFixture f;const auto original_intent=wire(intent(f)),old_root=contents(f.root),sink=contents(f.sink),wal=contents(f.path(3,".wal"));f.session.reset();
  const auto reject=[&](const std::string& bytes){generation_test::put(f.root+".retire",bytes);const auto before=descriptors();bool rejected=false;
    try{auto value=f.restore();}catch(const std::exception&){rejected=true;}check(rejected && descriptors()==before && contents(f.root)==old_root && contents(f.root+".retire")==bytes && contents(f.sink)==sink && contents(f.path(3,".wal"))==wal,"invalid retirement intent exposed owner, repaired files or leaked locks");f.history(true);};
  for(std::size_t cut=0;cut<original_intent.size();++cut)reject(original_intent.substr(0,cut));
  for(std::size_t i=0;i<original_intent.size();++i){auto bad=original_intent;bad[i]^=1;reject(bad);}reject(original_intent+"x");
  for(const std::size_t offset:{std::size_t{8},std::size_t{20},std::size_t{52},std::size_t{60},std::size_t{68},std::size_t{132},std::size_t{140},std::size_t{180},std::size_t{212},std::size_t{276},std::size_t{340},std::size_t{348},std::size_t{564},std::size_t{572},std::size_t{580}}) {
    auto bad=original_intent;if(offset==180 || offset==212 || offset==276 || offset==580 || offset==20 || offset==68)bad[offset]=bad[offset]=='0'?'1':'0';else bad[offset]^=1;checksum(bad);reject(bad);
  }
  {auto bad=original_intent;bad[652]=4;checksum(bad);reject(bad);}
  generation_test::put(f.root+".retire",original_intent);bool bare=false;try{auto value=QuerySession::restore_generation(f.program,f.root,generation_test::recovery_options());}catch(const recovery::GenerationFailure& e){bare=e.fault()==recovery::GenerationFault::state;}check(bare,"pending retirement restored without its actual local sink contract");
  auto torn_sink=sink;const auto sink_frames=session_journal_test::frames(sink);torn_sink.append(sink_frames.back().substr(0,85));generation_test::put(f.sink,torn_sink);
  auto torn_wal=wal;const auto wal_frames=session_journal_test::frames(wal);torn_wal.append(wal_frames[1].substr(0,85));generation_test::put(f.path(3,".wal"),torn_wal);
  auto bad=original_intent;bad[180]=bad[180]=='0'?'1':'0';checksum(bad);generation_test::put(f.root+".retire",bad);bool mismatch=false;
  try{auto value=f.restore();}catch(const recovery::GenerationFailure& e){mismatch=e.fault()==recovery::GenerationFault::binding;}check(mismatch && contents(f.sink)==torn_sink && contents(f.path(3,".wal"))==torn_wal && contents(f.root)==old_root,"intent/sink mismatch repaired a tail before authority checks");f.history(true);
  generation_test::put(f.root+".retire",original_intent);auto after=old_root;after[60]=3;checksum(after);generation_test::put(f.root,after);
  std::filesystem::remove(f.path(1,".ckpt"));const auto sentinel=f.path(4,".ckpt");generation_test::put(sentinel,"future unselected checkpoint");
  {auto value=f.restore();check(value->generation_state().selected.first_generation==3 && !value->generation_state().retirement_pending && contents(f.root)==after && contents(f.sink)==sink && contents(f.path(3,".wal"))==wal,"interrupted floor/partial cleanup did not resume exactly");}
  f.history(false);check(contents(sentinel)=="future unselected checkpoint","retirement deleted an unrecorded future candidate");f.verify();
  std::cout<<"retirement724 cuts/724 flips/checksummed bindings; actual sink before both-tail repair; recorded floor/absent-file continuation passed\n";
}
void wire_golden(const char* path) {
  const auto text=contents(path);std::string bytes;int high=-1;for(const char c:text){if(c=='\n' || c=='\r' || c==' ' || c=='\t')continue;const int digit=c>='0'&&c<='9'?c-'0':c>='a'&&c<='f'?c-'a'+10:-1;check(digit>=0,"invalid retirement golden hex");if(high<0)high=digit;else{bytes.push_back(static_cast<char>(16*high+digit));high=-1;}}
  check(high<0 && bytes.size()==724 && sha256(bytes)=="54e9f4216cb183cc3f55dc84d218586dfc25c87a12d6b69591d9afec775d4ace","independent retirement fixture hash differs");
  const auto decoded=recovery::detail::inspect_retirement_intent(bytes);check(decoded.before.generation==7 && decoded.before.first_generation==3 && decoded.acknowledged_sequence==11 && decoded.sink.base_sequence==10 && wire(decoded)==bytes,"native intent differs from independent Python bytes");
  std::cout<<"retirement independent724-byte root/sink/ack intent golden exact roundtrip passed\n";
}
void checkpoint_delivery_binding(const char* golden_path) {
  RetirementFixture f;const auto root=contents(f.root),sink=contents(f.sink),wal=contents(f.path(3,".wal"));const auto selected=f.session->generation_state().selected;
  check(root.size()==324 && selected.delivery.has_value() && selected.delivery->sequence==2 && f.session->local_sink_state().retirement_verified,"selected checkpoint has no actual delivery content anchor");
  const auto frames=session_journal_test::frames(sink);std::array<char,64> digest{};std::copy_n(frames[0].data()+84,64,digest.begin());
  for(std::size_t i=1;i<=2;++i){std::string joined(digest.data(),digest.size());joined.append(frames[i].substr(84,64));digest=sha256_fixed(joined);}
  check(selected.delivery->content_sha256==digest && selected.delivery->bytes==frames[0].size()+frames[1].size()+frames[2].size(),"root delivery anchor differs from independent frame-chain calculation");
  f.session.reset();auto wrong=std::string(frames[2]);wrong.back()^=1;const auto body=sha256_fixed(std::string_view(wrong).substr(148));std::copy(body.begin(),body.end(),wrong.begin()+20);const auto head=sha256_fixed(std::string_view(wrong).substr(0,84));std::copy(head.begin(),head.end(),wrong.begin()+84);
  std::string forged(frames[0]);forged.append(frames[1]);forged+=wrong;forged.append(frames[3]);generation_test::put(f.sink,forged);
  const auto before=descriptors();bool rejected=false;try{auto value=f.restore();}catch(const Error& e){rejected=e.code()=="local_sink_binding";}check(rejected && descriptors()==before && contents(f.root)==root && contents(f.sink)==forged && contents(f.path(3,".wal"))==wal,"old checkpoint sink mismatch authorized native history retirement");f.history(true);
  {auto bare=QuerySession::restore_generation(f.program,f.root,generation_test::recovery_options());bool denied=false;try{bare->open_local_sink(f.sink,options());}catch(const Error& e){denied=e.code()=="local_sink_binding";}check(denied && contents(f.sink)==forged,"two-step attachment bypassed durable checkpoint-prefix binding");}
  generation_test::put(f.sink,sink);
  std::string legacy(root.substr(0,148));legacy[8]=1;for(unsigned i=0;i<8;++i)legacy[12+i]=static_cast<char>((std::uint64_t{128}>>(8*i))&255);const auto hash=sha256_fixed(legacy);legacy.append(hash.data(),hash.size());generation_test::put(f.root,legacy);
  {auto value=f.restore();check(!value->local_sink_state().retirement_verified,"legacy root without content proof silently authenticated old output");bool denied=false;try{value->retire_generation_history();}catch(const Error&){denied=true;}check(denied && contents(f.root)==legacy,"legacy prefix options authorized retirement");denied=false;try{value->rotate_generation();}catch(const Error&){denied=true;}check(denied && contents(f.root)==legacy,"rotation promoted an unauthenticated legacy sink prefix");}
  f.history(true);generation_test::put(f.root,root);
  for(std::size_t cut=0;cut<root.size();++cut){generation_test::put(f.root,std::string_view(root).substr(0,cut));bool bad=false;try{auto value=f.restore();}catch(const recovery::GenerationFailure&){bad=true;}check(bad,"partial delivery-root accepted");}
  for(std::size_t i=0;i<root.size();++i){auto bad=root;bad[i]^=1;generation_test::put(f.root,bad);bool failed=false;try{auto value=f.restore();}catch(const recovery::GenerationFailure&){failed=true;}check(failed,"changed delivery-root accepted");}
  generation_test::put(f.root,root);f.verify();
  const auto text=contents(golden_path);std::string golden;int high=-1;for(const char c:text){if(c=='\n' || c=='\r' || c==' ' || c=='\t')continue;const int digit=c>='0'&&c<='9'?c-'0':c>='a'&&c<='f'?c-'a'+10:-1;check(digit>=0,"invalid delivery-root hex");if(high<0)high=digit;else{golden.push_back(static_cast<char>(16*high+digit));high=-1;}}
  check(high<0 && golden.size()==324 && sha256(golden)=="86e8d4ea2d5df4d1a60935790146d34751a475801e89f14f908866d972d6dee5","independent delivery-root golden differs");const auto decoded=recovery::inspect_generation_root(golden);check(decoded.delivery && decoded.delivery->sequence==11 && decoded.delivery->bytes==1234 && decoded.generation==7 && decoded.first_generation==3,"independent root delivery fields differ");
  std::cout<<"retirement native checkpoint-prefix binding/forged old output/legacy fail-closed/324 root cuts+flips/independent root golden passed\n";
}
}
int main(int argc,char** argv){try{check(argc==3,"expected retirement intent and delivery-root goldens");const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)typed_case(indexed,kind);for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool pending:{false,true})stream_case(indexed,profile,pending);for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned cut=0;cut<4;++cut)window_case(indexed,fifo,cut);}retention_reuse();gates();pending_and_hostile();wire_golden(argv[1]);checkpoint_delivery_binding(argv[2]);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

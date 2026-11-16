#include "sql_aggregate_file_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>

namespace {
using namespace crown;
using namespace crown::sql_aggregate_file_test;
static_assert(!std::is_default_constructible_v<ar::SinkReceipt> && !std::is_aggregate_v<ar::SinkReceipt>);
static_assert(!std::is_constructible_v<ar::SinkReceipt,ar::SinkHeader,ar::SinkPrefix>);
static_assert(std::is_copy_constructible_v<ar::SinkReceipt> && !std::is_copy_assignable_v<ar::SinkReceipt>);
static_assert(std::is_nothrow_move_constructible_v<ar::WalFile> && std::is_nothrow_move_constructible_v<ar::SinkFile>);

// Actual files preserve independent W/I/C and the sink's separate D. File
// primitives expose sink_floor metadata; the later coordinator enforces D=C.
void round_trip(Schema& s,const Packets& p) {
  Directory dir;const auto wp=dir.file("wal"),sp=dir.file("sink");
  const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);
  auto wal=ar::WalFile::create(receiver,wp,s.admitted.descriptor,s.wal);
  auto sink=ar::SinkFile::create(receiver,sp,s.admitted.descriptor,s.sink);
  const auto initial_receipt=sink.receipt();assert(initial_receipt.prefix().physical_sequence==0);
  { s04_alloc::Scope deny(0);wal.append(p.wal[1]);wal.append(p.wal[2]);assert(s04_alloc::calls==0); }
  assert(wal.state().wal.logged_sequence==1 && wal.state().wal.command_sequence==1 && wal.state().wal.physical_sequence==1);
  const auto initial=contents(sp);bool failed=false;
  { s04_alloc::Scope deny(0);try { static_cast<void>(sink.append(p.sink[1])); } catch(const std::bad_alloc&) { failed=true; } }
  assert(failed && !sink.requires_reopen() && contents(sp)==initial && sink.state().prefix.physical_sequence==0);
  assert(sink.append(p.sink[1]));assert(!sink.append(p.sink[1])); // Also funds duplicate scratch.
  { s04_alloc::Scope deny(0);sink.verify(p.sink[1]);assert(s04_alloc::calls==0); }
  wal.append(p.wal[3]);assert(wal.state().wal.pending && wal.state().wal.sink_floor==1);
  wal.append(p.wal[4]);assert(wal.state().wal.command_sequence==2 && wal.state().wal.physical_sequence==1);
  wal.append(p.wal[5]);wal.append(p.wal[6]);assert(wal.state().wal.command_sequence==3 && wal.state().wal.physical_sequence==2);
  assert(sink.append(p.sink[2]));assert(!sink.append(p.sink[2])); // Empty closure remains a real record.
  const auto receipt=sink.receipt();assert(receipt.prefix().input_sequence==3 && receipt.prefix().physical_sequence==2);
  assert(receipt.prefix()==sink.prefix(2) && sink.prefix(1).generation==7);
  refused([&]{auto locked=ar::WalFile::open(receiver,wp,s.admitted.descriptor,s.wal);});
  refused([&]{auto locked=ar::SinkFile::open(receiver,sp,s.admitted.descriptor,s.sink);});
  auto moved=std::move(wal);assert(wal.requires_reopen());refused([&]{static_cast<void>(wal.state());});
  auto moved_sink=std::move(sink);assert(sink.requires_reopen());refused([&]{static_cast<void>(sink.receipt());});
  moved.close();moved_sink.close();
  auto reopened=ar::WalFile::open(receiver,wp,s.admitted.descriptor,s.wal);
  auto reopened_sink=ar::SinkFile::open(receiver,sp,s.admitted.descriptor,s.sink);
  assert(reopened.state().wal.records==7 && reopened.state().wal.command_sequence==3 && !reopened.state().wal.pending);
  const auto reopened_receipt=reopened_sink.receipt();assert(reopened_receipt.prefix()==receipt.prefix() && reopened_sink.state().records==3);
  reopened_sink.verify(p.sink[1]);reopened_sink.verify(p.sink[2]);
  assert(contents(wp)==Packets::prefix(p.wal,7) && contents(sp)==Packets::prefix(p.sink,3));
}
// Every prefix cut after a complete header is either a complete prior prefix or
// one validated incomplete suffix. Repair preserves complete pending Inputs;
// a complete corrupt record, wrong kind or wrong ordinal is never repaired.
void tails_and_corruption(Schema& s,const Packets& p) {
  Directory dir;const auto path=dir.file();const auto wh=Packets::prefix(p.wal,2),sh=Packets::prefix(p.sink,1);
  for(std::size_t cut=0;cut<p.wal[2].bytes().size();++cut) {
    const auto bytes=wh+std::string(p.wal[2].bytes().substr(0,cut));put(path,bytes);
    auto file=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);
    assert(file.state().wal.pending && file.state().wal.command_sequence==0 && file.state().torn_tail==(cut!=0));
    assert(contents(path)==bytes);file.repair_tail();assert(contents(path)==wh);file.append(p.wal[2]);
    assert(file.state().wal.command_sequence==1);
  }
  for(std::size_t cut=0;cut<p.sink[1].bytes().size();++cut) {
    const auto bytes=sh+std::string(p.sink[1].bytes().substr(0,cut));put(path,bytes);
    auto file=ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink);
    assert(file.state().prefix.physical_sequence==0 && file.state().torn_tail==(cut!=0) && contents(path)==bytes);
    if(cut)refused([&]{static_cast<void>(file.receipt());});
    file.repair_tail();assert(contents(path)==sh);assert(file.append(p.sink[1]));
  }
  for(const auto* frame:{&p.wal[2],&p.sink[1]})for(std::size_t at=0;at<frame->bytes().size();++at) {
    std::string bad(frame->bytes());bad[at]^=1;const bool sink=frame==&p.sink[1];const auto bytes=(sink?sh:wh)+bad;put(path,bytes);
    refused([&]{if(sink){auto file=ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink);}
      else {auto file=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);}});
    assert(contents(path)==bytes);
  }
  for(bool sink:{false,true}) {
    const auto& frame=sink?p.sink[1]:p.wal[2];
    for(unsigned mode=0;mode<3;++mode) {
      std::string bad(frame.bytes());if(mode==0)bad[ar::frame_header_size]=static_cast<char>(ar::Kind::sink_header);
      if(mode==1)bad[ar::frame_header_size+1]^=1;
      if(mode==2)std::fill_n(bad.begin()+12,8,'\0'); // Authenticated impossible length.
      reseal(bad);const auto bytes=(sink?sh:wh)+bad.substr(0,ar::frame_header_size+9);put(path,bytes);
      refused([&]{if(sink){auto file=ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink);}
        else {auto file=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);}});
      assert(contents(path)==bytes);
    }
  }
  // Duplicates remain verifiable through an incomplete next suffix; receipt and
  // append wait for the caller's semantic validation and explicit repair.
  put(path,Packets::prefix(p.sink,2)+std::string(p.sink[2].bytes().substr(0,23)));
  auto file=ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink);file.verify(p.sink[1]);
  refused([&]{static_cast<void>(file.append(p.sink[2]));});file.repair_tail();assert(file.append(p.sink[2]));
}
// Rebased sinks use global C ordinals and accept an increasing input-sequence
// gap; falling generation/I, relative ordinals and differing duplicate bytes fail.
void identity_and_extremes(Schema& s,const Packets& p) {
  Directory dir;const auto wp=dir.file("wal"),sp=dir.file("sink");const auto& program=s.admitted.descriptor.program();
  auto wh=s.wal;wh.physical_sequence=10;wh.command_sequence=17;auto sh=s.sink;sh.base_sequence=10;
  const std::array<runtime::sql_rows::SourceReplacement,0> empty{};
  const auto input=ar::encode(s.account,program,1,ar::InputView{18,empty,{},{}});
  const auto epoch=ar::encode(s.account,program,11,ar::GroupEpochView{9,18,11,input.info().body_sha256,false,false,{}});
  const auto commit=ar::encode(s.account,program,2,ar::Commit{1,input.info().body_sha256,18,11,epoch.bytes().size(),sha256_fixed(epoch.bytes())});
  {auto wal=ar::WalFile::create(s.account,wp,s.admitted.descriptor,wh);wal.append(input);wal.append(commit);}
  {auto sink=ar::SinkFile::create(s.account,sp,s.admitted.descriptor,sh);
    const auto baseline=sink.receipt();assert(baseline.prefix().generation==0 && baseline.prefix().physical_sequence==10);
    assert(sink.append(epoch));assert(!sink.append(epoch));}
  {auto wal=ar::WalFile::open(s.account,wp,s.admitted.descriptor,wh);assert(wal.state().wal.command_sequence==18 && wal.state().wal.physical_sequence==11);}
  {auto sink=ar::SinkFile::open(s.account,sp,s.admitted.descriptor,sh);assert(sink.state().prefix.physical_sequence==11);}
  auto bad=wh;bad.binding.descriptor_sha256[0]=bad.binding.descriptor_sha256[0]=='0'?'1':'0';
  refused([&]{auto file=ar::WalFile::create(s.account,dir.file("bad"),s.admitted.descriptor,bad);});assert(!std::filesystem::exists(dir.file("bad")));
  refused([&]{auto file=ar::WalFile::open(s.account,wp,s.admitted.descriptor,s.wal);});
  auto sink=ar::SinkFile::open(s.account,sp,s.admitted.descriptor,sh);
  for(const auto& value:{ar::GroupEpochView{8,19,12,hash('a'),false,false,{}},ar::GroupEpochView{9,18,12,hash('a'),false,false,{}}}) {
    const auto frame=ar::encode(s.account,program,12,value);refused([&]{static_cast<void>(sink.append(frame));});
  }
  const auto relative=ar::encode(s.account,program,2,ar::GroupEpochView{9,19,12,hash('a'),false,false,{}});
  refused([&]{static_cast<void>(sink.append(relative));});
  const auto different=ar::encode(s.account,program,11,ar::GroupEpochView{9,18,11,hash('b'),false,false,{}});
  refused([&]{static_cast<void>(sink.append(different));});assert(!sink.requires_reopen());sink.close();
  // Terminal headers are readable but cannot admit even a prefix of another record.
  sh.base_sequence=UINT64_MAX;const auto terminal=dir.file("terminal");
  {auto file=ar::SinkFile::create(s.account,terminal,s.admitted.descriptor,sh);assert(file.state().prefix.physical_sequence==UINT64_MAX);}
  auto raw=contents(terminal);put(terminal,raw+"C");refused([&]{auto file=ar::SinkFile::open(s.account,terminal,s.admitted.descriptor,sh);});
  wh.physical_sequence=wh.command_sequence=UINT64_MAX;
  {auto file=ar::WalFile::create(s.account,dir.file("terminal-wal"),s.admitted.descriptor,wh);refused([&]{file.append(p.wal[1]);});}
  // I=MAX below terminal C is independently terminal for a sink's next epoch.
  sh.base_sequence=0;const auto end=ar::encode(s.account,program,1,ar::GroupEpochView{9,UINT64_MAX,1,hash('a'),false,false,{}});
  put(terminal,std::string(p.sink[0].bytes())+std::string(end.bytes())+"C");
  refused([&]{auto file=ar::SinkFile::open(s.account,terminal,s.admitted.descriptor,sh);});
}
// An immutable Frame may have a different genuine schema or be moved from.
// The file must inspect actual bytes under its own program, with no mutation
// or poisoning for these pre-I/O refusals; cached Frame metadata is insufficient.
void frame_boundaries(Schema& s,const Packets& p) {
  Directory dir;const auto wp=dir.file("wal"),sp=dir.file("sink");
  auto wal=ar::WalFile::create(s.account,wp,s.admitted.descriptor,s.wal);
  auto sink=ar::SinkFile::create(s.account,sp,s.admitted.descriptor,s.sink);
  const auto wb=contents(wp),sb=contents(sp);const auto wo=wal.state().statistics.operations,so=sink.state().statistics.operations;
  Catalog catalog{1,{{"r",{{"g",ScalarType::int64}}}}};
  auto bound=frontend::bind_sql_aggregate("SELECT COUNT(*) FROM r GROUP BY g",catalog);
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(bound));const auto& alien=std::get<frontend::SqlAggregateProgram>(bound);
  const std::array<Cell,1> row{number(2)};const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,1}};
  const auto input=ar::encode(s.account,alien,1,ar::InputView{1,edits,{},{}});
  const std::array<Cell,1> count{number(1)};
  const auto key=runtime::aggregate::Tuple::copy_of(s.account,row),value=runtime::aggregate::Tuple::copy_of(s.account,count);
  const std::array changes{runtime::aggregate::GroupChange{key,{},value}};
  const auto output=ar::encode(s.account,alien,1,ar::GroupEpochView{7,1,1,hash('a'),true,true,changes});
  refused([&]{wal.append(input);});refused([&]{static_cast<void>(sink.append(output));});
  refused([&]{wal.append(p.sink[1]);});refused([&]{static_cast<void>(sink.append(p.wal[1]));});
  auto source=ar::encode(s.account,s.admitted.descriptor.program(),1,ar::InputView{1,{}, {},{}});auto retained=std::move(source);
  assert(!retained.bytes().empty());refused([&]{wal.append(source);});refused([&]{static_cast<void>(sink.append(source));});
  assert(!wal.requires_reopen() && !sink.requires_reopen() && contents(wp)==wb && contents(sp)==sb);
  assert(wal.state().wal.records==1 && wal.state().statistics.operations==wo && sink.state().statistics.operations==so);
}
// Successful open's measured grants are replayed exactly and one below. Scope
// allocation cuts cover every receiving metadata/index/scratch allocation, with
// file bytes/FD counts and the receiving account restored after each rejection.
template<class Factory> void receiving_limits(Factory factory,const std::string& path) {
  const auto bytes=contents(path);const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);std::uint64_t peak=0;
  std::size_t calls=0;{s04_alloc::Scope count;{auto file=factory(receiver,ar::FileLimits{});}calls=s04_alloc::calls;peak=receiver.statistics().peak_requested_bytes;}
  for(std::size_t cut=0;cut<calls;++cut) {
    const auto fds=descriptors();bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));try {auto file=factory(receiver,ar::FileLimits{});}catch(const std::bad_alloc&){failed=true;}}
    assert(failed && receiver.statistics().current.allocations==1 && descriptors()==fds && contents(path)==bytes);
  }
  const auto exact=resource::MemoryAccount::create(peak);{auto file=factory(exact,ar::FileLimits{});}
  const auto low=resource::MemoryAccount::create(peak-1);refused([&]{auto file=factory(low,ar::FileLimits{});});assert(low.statistics().current.allocations==1);
  ar::FileLimits limits;{auto file=factory(receiver,limits);const auto state=file.state();limits.scan.work=state.statistics.work;limits.operations=state.statistics.operations;
    if constexpr(requires{state.wal;})limits.scan.records=state.wal.records;else limits.scan.records=state.records;}
  limits.scan.bytes=bytes.size();{auto file=factory(receiver,limits);}
  for(unsigned which=0;which<4;++which) {
    auto below=limits;if(which==0)--below.scan.work;if(which==1)--below.operations;if(which==2)--below.scan.bytes;
    if(which==3)--below.scan.records;
    refused([&]{auto file=factory(receiver,below);});assert(contents(path)==bytes);
  }
}
void limits_namespace_and_lifetime(Schema& s,const Packets& p) {
  Directory dir;const auto wp=dir.file("wal"),sp=dir.file("sink");put(wp,Packets::prefix(p.wal,7));put(sp,Packets::prefix(p.sink,3));
  receiving_limits([&](const auto& account,ar::FileLimits limits){return ar::WalFile::open(account,wp,s.admitted.descriptor,s.wal,limits);},wp);
  receiving_limits([&](const auto& account,ar::FileLimits limits){return ar::SinkFile::open(account,sp,s.admitted.descriptor,s.sink,limits);},sp);
  for(bool sink:{false,true}) {
    auto limits=ar::FileLimits{};limits.scan.records=1;const auto bytes=std::string((sink?p.sink[0]:p.wal[0]).bytes());put(wp,bytes+"C");
    refused([&]{if(sink){auto file=ar::SinkFile::open(s.account,wp,s.admitted.descriptor,s.sink,limits);}
      else {auto file=ar::WalFile::open(s.account,wp,s.admitted.descriptor,s.wal,limits);}});
    put(wp,bytes);if(sink){auto file=ar::SinkFile::open(s.account,wp,s.admitted.descriptor,s.sink,limits);}
    else {auto file=ar::WalFile::open(s.account,wp,s.admitted.descriptor,s.wal,limits);}
  }
  put(wp,"preserved");refused([&]{auto file=ar::WalFile::create(s.account,wp,s.admitted.descriptor,s.wal);});assert(contents(wp)=="preserved");
  const auto link=dir.file("link");assert(::symlink(wp.c_str(),link.c_str())==0);
  refused([&]{auto file=ar::SinkFile::create(s.account,link,s.admitted.descriptor,s.sink);});assert(contents(wp)=="preserved");
  refused([&]{auto file=ar::WalFile::open(s.account,link,s.admitted.descriptor,s.wal);});
  for(const auto& path:{std::string{},dir.name+"/",std::string("x\0y",3),dir.name+"/.."})
    refused([&]{auto file=ar::WalFile::create(s.account,path,s.admitted.descriptor,s.wal);});
  const auto receiver=resource::MemoryAccount::create(128ULL*1024*1024);resource::MemoryAccount producer;
  std::optional<ar::WalFile> wal;std::optional<ar::SinkFile> sink;
  {Schema local;producer=local.account;wal.emplace(ar::WalFile::create(receiver,dir.file("live-wal"),local.admitted.descriptor,local.wal));
    sink.emplace(ar::SinkFile::create(receiver,dir.file("live-sink"),local.admitted.descriptor,local.sink));}
  assert(producer.statistics().current.allocations==1);wal->append(p.wal[1]);wal->append(p.wal[2]);assert(sink->append(p.sink[1]));
  wal.reset();sink.reset();assert(receiver.statistics().current.allocations==1 && temporaries(dir)==0);
}
} // namespace
int main() {
  Schema schema;const Packets packets(schema);round_trip(schema,packets);tails_and_corruption(schema,packets);
  identity_and_extremes(schema,packets);frame_boundaries(schema,packets);limits_namespace_and_lifetime(schema,packets);
  std::cout<<"R2 actual WAL/sink ownership, nullable/empty epochs, prefix repair, full-byte retries and receiving limits passed\n";
}

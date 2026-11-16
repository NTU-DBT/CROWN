#include "crown/recovery/sql_aggregate_records.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

namespace {
using namespace crown;
namespace ar = recovery::sql_aggregate;
using Cell = runtime::sql_rows::Cell;
using Group = runtime::aggregate::GroupChange;
template<class T> concept RvalueView = requires(const T&& value) { std::move(value).view(); };
static_assert(!RvalueView<ar::DecodedInput> && !std::is_copy_constructible_v<ar::Frame>);
static_assert(std::is_nothrow_move_assignable_v<ar::DecodedInput>);
static_assert(std::is_nothrow_move_constructible_v<ar::WalCursor>);
Cell number(std::int64_t value) { return storage::ScalarView{value}; }
Cell text(std::string_view value) { return storage::ScalarView{value}; }
ar::Hash hash(char value) { ar::Hash result{};result.fill(value);return result; }
ar::Binding binding() {
  ar::Binding result;result.query_id.fill('0');result.descriptor_sha256=hash('a');return result;
}
frontend::SqlAggregateProgram bind_program(std::string_view sql="SELECT g,COUNT(*) FROM r GROUP BY g") {
  Catalog schema{1,{{"r",{{"g",ScalarType::string,true},{"id",ScalarType::int64},
      {"flag",ScalarType::boolean},{"d",ScalarType::date},
      {"x",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}},{"n",ScalarType::int64,true}}}}};
  auto result=frontend::bind_sql_aggregate(sql,schema);
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));
  return std::get<frontend::SqlAggregateProgram>(std::move(result));
}
runtime::aggregate::Tuple tuple(const resource::MemoryAccount& account,std::initializer_list<Cell> values) {
  return runtime::aggregate::Tuple::copy_of(account,values);
}
// All malformed transport paths must reject without covered C++ allocations.
template<class Action> void rejected(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);
    try { action(); } catch(const recovery::ImageFailure&) { failed=true; }
    assert(s04_alloc::calls==0);
  }assert(failed);
}
template<class Action> void limited(Action action) {
  bool failed=false;try { action(); } catch(const recovery::ImageFailure&) { failed=true; }assert(failed);
}
// Independent Python fixtures compare full bytes, not implementation round trips.
void golden(std::string_view directory,std::string_view name,const ar::Frame& frame) {
  std::ifstream file(std::string(directory)+"/"+std::string(name)+".hex");std::string encoded;file>>encoded;
  assert(encoded.size()==frame.bytes().size()*2);constexpr std::string_view hex="0123456789abcdef";
  for(std::size_t i=0;i<frame.bytes().size();++i) {
    const auto value=static_cast<unsigned char>(frame.bytes()[i]);
    assert(encoded[2*i]==hex[value>>4] && encoded[2*i+1]==hex[value&15]);
  }
}
// Recompute both checksums so negative cases exercise structure/type validation.
void reseal(std::string& bytes) {
  const auto body=sha256_fixed(std::string_view(bytes).substr(ar::frame_header_size));
  std::copy(body.begin(),body.end(),bytes.begin()+20);
  const auto prefix=sha256_fixed(std::string_view(bytes).substr(0,ar::frame_prefix_size));
  std::copy(prefix.begin(),prefix.end(),bytes.begin()+ar::frame_prefix_size);
}
void frame_checks(const frontend::SqlAggregateProgram& schema,const ar::Frame& frame) {
  const auto bytes=frame.bytes();ar::Inspected info{};
  {s04_alloc::Scope deny(0);info=ar::inspect(schema,bytes);assert(s04_alloc::calls==0);}
  for(std::size_t size=0;size<bytes.size();++size)
    rejected([&]{static_cast<void>(ar::inspect(schema,bytes.substr(0,size)));});
  for(std::size_t i=0;i<bytes.size();++i) {
    std::string bad(bytes);bad[i]^=1;rejected([&]{static_cast<void>(ar::inspect(schema,bad));});
  }
  ar::Limits exact;exact.record.bytes=bytes.size();exact.record.work=info.statistics.work;
  static_cast<void>(ar::inspect(schema,bytes,exact));
  auto low=exact;--low.record.bytes;rejected([&]{static_cast<void>(ar::inspect(schema,bytes,low));});
  low=exact;--low.record.work;rejected([&]{static_cast<void>(ar::inspect(schema,bytes,low));});
  std::string extra(bytes);extra+='x';rejected([&]{static_cast<void>(ar::inspect(schema,extra));});
}
// Count real allocation sites, fail each one, and require exact account release.
template<class Factory> void allocation_cuts(const resource::MemoryAccount& account,Factory factory) {
  std::size_t calls=0;const auto before=account.statistics();
  {s04_alloc::Scope count;{auto owned=factory();}calls=s04_alloc::calls;}
  assert(account.statistics().current==before.current);
  assert(account.statistics().successful_allocations-before.successful_allocations==calls);
  for(std::size_t i=0;i<calls;++i) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(i));
      try { auto owned=factory(); } catch(const std::bad_alloc&) { failed=true; }
    }assert(failed && account.statistics().current==before.current);
  }
}
// Independent receiving grants must pass at their measured peak and fail one
// byte below it; failures return to the receiving controller's sole allocation.
template<class Factory> void receiving_caps(Factory factory) {
  auto trial=resource::MemoryAccount::create(64ULL*1024*1024);std::uint64_t peak=0;
  {auto owned=factory(trial);peak=trial.statistics().peak_requested_bytes;}
  auto exact=resource::MemoryAccount::create(peak);{auto owned=factory(exact);assert(exact.statistics().peak_requested_bytes==peak);}
  auto low=resource::MemoryAccount::create(peak-1);bool failed=false;
  try {auto owned=factory(low);}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
  assert(failed && low.statistics().current.allocations==1);low.check_invariants();
}
void cursor_checks(const frontend::SqlAggregateProgram& schema,const resource::MemoryAccount& account,
    const ar::Frame& header,const ar::Frame& input,const ar::Frame& commit,const ar::Frame& reject) {
  ar::WalCursor cursor;
  for(const auto* frame:{&header,&input,&reject}) {
    s04_alloc::Scope deny(0);static_cast<void>(cursor.feed(schema,frame->bytes()));assert(s04_alloc::calls==0);
  }
  assert(cursor.state().physical_sequence==0 && cursor.state().command_sequence==1 && !cursor.state().pending);
  const std::array<runtime::sql_rows::SourceReplacement,0> edits{};
  const auto second=ar::encode(account,schema,3,ar::InputView{2,edits,{},{}});
  static_cast<void>(cursor.feed(schema,second.bytes()));assert(cursor.state().pending && cursor.state().sink_floor==0);
  ar::Commit decision{3,second.info().body_sha256,2,1,std::get<ar::Commit>(commit.info().payload).output_bytes,hash('d')};
  const auto accepted=ar::encode(account,schema,4,decision);static_cast<void>(cursor.feed(schema,accepted.bytes()));
  assert(cursor.state().logged_sequence==2 && cursor.state().command_sequence==2 && cursor.state().physical_sequence==1);
  const auto third=ar::encode(account,schema,5,ar::InputView{3,edits,{},{}});static_cast<void>(cursor.feed(schema,third.bytes()));
  assert(cursor.state().sink_floor==1 && cursor.state().pending->command_sequence==3);
  const auto saved=cursor.state();rejected([&]{static_cast<void>(cursor.feed(schema,third.bytes()));});
  assert(cursor.state().records==saved.records && cursor.state().work==saved.work && cursor.state().pending->body_sha256==saved.pending->body_sha256);
  ar::ScanLimits exact;exact.bytes=saved.bytes;exact.work=saved.work;exact.records=saved.records;
  for(unsigned which=0;which<4;++which) {
    auto limits=exact;if(which==1)--limits.bytes;if(which==2)--limits.work;if(which==3)--limits.records;
    ar::WalCursor checked(limits);bool failed=false;
    {s04_alloc::Scope deny(0);
      try {for(const auto* frame:{&header,&input,&reject,&second,&accepted,&third})static_cast<void>(checked.feed(schema,frame->bytes()));}
      catch(const recovery::ImageFailure&) { failed=true; }assert(s04_alloc::calls==0);
    }assert(failed==(which!=0));
  }
  // C=UINT64_MAX and I=UINT64_MAX are terminal; no overflowing successor.
  auto terminal=std::get<ar::WalHeader>(header.info().payload);terminal.command_sequence=terminal.physical_sequence=UINT64_MAX;
  auto end=ar::encode(account,schema,0,terminal);ar::WalCursor full;static_cast<void>(full.feed(schema,end.bytes()));
  rejected([&]{static_cast<void>(full.feed(schema,input.bytes()));});
}
} // namespace

int main(int argc,char** argv) {
  assert(argc==2);const auto schema=bind_program();const auto account=resource::MemoryAccount::create(64ULL*1024*1024);
  const auto header=ar::encode(account,schema,0,ar::WalHeader{binding(),7,hash('b'),0,0});
  const auto sink=ar::encode(account,schema,0,ar::SinkHeader{binding(),[] {ar::Id id{};id.fill('c');return id;}(),0});
  std::string original="µ";
  const std::array<Cell,6> row{text(original),number(-2),storage::ScalarView{true},
      storage::ScalarView{Date::parse("2024-02-29")},storage::ScalarView{storage::InlineDecimal::parse("-1.25")},{}};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
  const ar::InputView command{1,edits,ar::SourcePosition{"feed",9},ar::ReaderPosition{200,1}};
  const auto input=ar::encode(account,schema,1,command);
  const Group group{tuple(account,{text("µ")}),{},tuple(account,{text("µ"),number(2)})};
  const std::array changes{group};
  const ar::GroupEpochView output{7,1,1,input.info().body_sha256,true,true,changes};
  const auto epoch=ar::encode(account,schema,1,output);
  const auto commit=ar::encode(account,schema,2,ar::Commit{1,input.info().body_sha256,1,1,epoch.bytes().size(),sha256_fixed(epoch.bytes())});
  const auto reject=ar::encode(account,schema,2,ar::Reject{1,input.info().body_sha256,1,0,ar::RejectReason::unique_violation});
  const std::array<Group,0> empty{};
  const auto empty_epoch=ar::encode(account,schema,2,ar::GroupEpochView{7,2,2,hash('d'),false,false,empty});
  const std::array names{"wal-header","input","commit","reject","sink-header","group-epoch","empty-epoch"};
  const std::array frames{&header,&input,&commit,&reject,&sink,&epoch,&empty_epoch};
  for(std::size_t i=0;i<frames.size();++i){golden(argv[1],names[i],*frames[i]);frame_checks(schema,*frames[i]);}

  // One owned buffer survives external byte/text destruction and facade moves.
  auto decoded=ar::decode_input(account,schema,input.bytes());auto moved=std::move(decoded);original.assign(1000,'z');
  assert(moved.view().source->source=="feed" && moved.view().reader==ar::ReaderPosition(200,1));
  assert(std::get<std::string_view>(*moved.view().replacements[0].values[0])=="µ");
  auto own=ar::encode_input(account,schema,1,moved.view());assert(own.frame().bytes()==input.bytes());
  const auto core=schema.source_program().export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
  assert(chosen.tree);auto live=runtime::SqlAggregateRuntime::create_into(account,schema,*chosen.tree);
  const auto applied=live.prepare_batch({1,own.view().replacements}).commit();assert(applied.changed && live.root_weight()==annotations::Multiplicity{2});

  // Canonical full-key order preserves equal visible values and NULL keys.
  const auto hidden_schema=bind_program("SELECT COUNT(*) FROM r GROUP BY g");
  const std::array unordered{Group{tuple(account,{text("z")}),{},tuple(account,{number(1)})},
      Group{tuple(account,{{}}),{},tuple(account,{number(1)})}};
  auto unordered_view=output;unordered_view.groups=unordered;auto sorted=ar::encode(account,hidden_schema,1,unordered_view);
  const std::array reversed{unordered[1],unordered[0]};unordered_view.groups=reversed;
  const auto reordered=ar::encode(account,hidden_schema,1,unordered_view);assert(reordered.bytes()==sorted.bytes());
  const std::array duplicate{unordered[0],unordered[0]};unordered_view.groups=duplicate;
  limited([&]{auto unused=ar::encode(account,hidden_schema,1,unordered_view);});
  const std::array invalid_handle{Group{group.key,runtime::aggregate::Tuple{},group.after}};auto invalid_output=output;invalid_output.groups=invalid_handle;
  limited([&]{auto unused=ar::encode(account,schema,1,invalid_output);});
  const std::array unchanged{Group{group.key,group.after,group.after}};invalid_output.groups=unchanged;
  limited([&]{auto unused=ar::encode(account,schema,1,invalid_output);});
  const std::array removal{Group{group.key,group.after,{}}};invalid_output.groups=removal;
  const auto removed=ar::encode(account,schema,1,invalid_output);static_cast<void>(ar::inspect(schema,removed.bytes()));
  auto invalid=row;invalid[1]={};const std::array bad_edits{runtime::sql_rows::SourceReplacement{TableId{0},invalid,0,2}};
  rejected([&]{auto unused=ar::encode(account,schema,1,ar::InputView{1,bad_edits,{},{}});});
  invalid=row;invalid[0]=text(std::string_view("\xc0\xaf",2));
  rejected([&]{auto unused=ar::encode(account,schema,1,ar::InputView{1,std::array{runtime::sql_rows::SourceReplacement{TableId{0},invalid,0,1}},{},{}});});
  for(const auto position:{148U,189U,190U}) {
    std::string bad(input.bytes());bad[position]=static_cast<char>(0xff);reseal(bad);
    rejected([&]{static_cast<void>(ar::inspect(schema,bad));});
  }
  ar::Limits exact;exact.record.work=input.info().statistics.work;exact.record.bytes=input.bytes().size();
  const auto exact_encoded=ar::encode(account,schema,1,moved.view(),exact);assert(exact_encoded.bytes()==input.bytes());
  --exact.record.work;limited([&]{auto unused=ar::encode(account,schema,1,moved.view(),exact);});
  exact={};exact.source_bytes=3;rejected([&]{auto unused=ar::encode(account,schema,1,moved.view(),exact);});
  allocation_cuts(account,[&]{return ar::encode_input(account,schema,1,moved.view());});
  allocation_cuts(account,[&]{return ar::decode_input(account,schema,input.bytes());});
  allocation_cuts(account,[&]{return ar::encode(account,schema,1,output);});
  receiving_caps([&](const auto& receiving){return ar::encode_input(receiving,schema,1,moved.view());});
  receiving_caps([&](const auto& receiving){return ar::decode_input(receiving,schema,input.bytes());});
  receiving_caps([&](const auto& receiving){return ar::encode(receiving,schema,1,output);});
  cursor_checks(schema,account,header,input,commit,reject);account.check_invariants();
  std::cout<<"R2 seven independent goldens; nullable ownership/native use; canonical full keys; all truncations/flips; allocation cuts; exact caps; W/I/C transport passed\n";
}

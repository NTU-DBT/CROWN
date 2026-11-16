#include "crown/recovery/sql_rows_records.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace {
using namespace crown;
namespace rr = recovery::sql_rows;
using Cell = runtime::sql_rows::Cell;
constexpr std::uint64_t memory = 64ULL*1024*1024;
Catalog schema() { return {1,{{"r",{{"x",ScalarType::int64,true},{"tag",ScalarType::string,true}}}}}; }
Cell n(std::int64_t value) { return storage::ScalarView{value}; }
Cell text(std::string_view value) { return storage::ScalarView{value}; }
frontend::SqlRowsProgram bind(std::string_view sql,bool retain=true) {
  frontend::SqlRowsBindOptions options;options.retain_binding_image=retain;
  auto result=frontend::bind_sql_rows(sql,schema(),options);
  assert(std::holds_alternative<frontend::SqlRowsProgram>(result));
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}
FreeConnexTree tree(const frontend::SqlRowsProgram& program) {
  const auto core=program.export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
  assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;
}
rr::Hash hash(char c) { rr::Hash value{};value.fill(c);return value; }
rr::Id id(char c) { rr::Id value{};value.fill(c);return value; }
void integer(std::string& bytes,std::uint64_t value,unsigned width=8) {
  for(unsigned i=0;i<width;++i)bytes.push_back(static_cast<char>(value>>(8*i)));
}
// Independent wire construction pins all framing bytes, not merely codec info.
std::string envelope(std::string body) {
  std::string result("CROWNRW2\x01\x00\x00\x00",12);integer(result,body.size());
  const auto digest=sha256_fixed(body);result.append(digest.data(),digest.size());
  const auto prefix=sha256_fixed(result);result.append(prefix.data(),prefix.size());return result+body;
}
std::string body(std::uint64_t sequence,bool changed,std::uint64_t rows) {
  std::string result;integer(result,5,1);integer(result,sequence);integer(result,1);integer(result,sequence);
  integer(result,sequence);result.append(64,'a');integer(result,changed,1);integer(result,rows!=0,1);integer(result,rows);return result;
}
void reseal(std::string& bytes) {
  const auto size=bytes.size()-148;for(unsigned i=0;i<8;++i)bytes[12+i]=static_cast<char>(std::uint64_t(size)>>(8*i));
  const auto digest=sha256_fixed(std::string_view(bytes).substr(148));std::copy(digest.begin(),digest.end(),bytes.begin()+20);
  const auto prefix=sha256_fixed(std::string_view(bytes).substr(0,84));std::copy(prefix.begin(),prefix.end(),bytes.begin()+84);
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed);
}
void inspect_checks(const frontend::SqlRowsProgram& program,std::string_view bytes) {
  rr::Inspected checked{};{s04_alloc::Scope deny(0);checked=rr::inspect(program,bytes);assert(s04_alloc::calls==0);}
  rr::Limits exact;exact.record.bytes=bytes.size();exact.record.work=checked.statistics.work;
  static_cast<void>(rr::inspect(program,bytes,exact));auto low=exact;--low.record.work;
  rejected([&]{static_cast<void>(rr::inspect(program,bytes,low));});low=exact;--low.record.bytes;
  rejected([&]{static_cast<void>(rr::inspect(program,bytes,low));});
  for(std::size_t size=0;size<bytes.size();++size)
    rejected([&]{static_cast<void>(rr::inspect(program,bytes.substr(0,size)));});
  for(std::size_t i=0;i<bytes.size();++i) {
    std::string bad(bytes);bad[i]^=1;rejected([&]{static_cast<void>(rr::inspect(program,bad));});
  }
}
void binding_opt_in() {
  const auto ordinary=bind("SELECT x FROM r",false),retained=bind("SELECT x FROM r");
  assert(ordinary.binding_image().empty() && !retained.binding_image().empty());
  assert(ordinary.source_sha256()==retained.source_sha256());
  const auto account=resource::MemoryAccount::create(memory);
  auto live=runtime::SqlRowsRuntime::create_into(account,ordinary,tree(ordinary));
  const std::array<Cell,2> row{n(7),text("ordinary")};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,3}};
  auto pending=live.prepare_output_batch({1,edits});std::array<Cell,1> scratch{};
  assert(pending.output_size()==1);const auto output=pending.output_change(0,scratch);
  assert(output.values[0]==row[0] && output.change.magnitude.value==3);
  const rr::WalHeader header{{id('1'),hash('2')},1,hash('3'),0,0};
  const auto frame=rr::encode(account,retained,0,header);const auto before=account.statistics().current;
  const auto work=pending.output_work();
  for(const bool absent_token:{false,true}) {
    bool denied=false;
    try {auto invalid=rr::encode(account,absent_token?retained:ordinary,1,rr::RowEpochView{1,1,1,hash('a'),true,&pending});}
    catch(const recovery::ImageFailure& error) {denied=error.fault()==recovery::ImageFault::binding;}
    assert(denied);
  }
  bool denied=false;
  try {static_cast<void>(rr::inspect(ordinary,frame.bytes()));}
  catch(const recovery::ImageFailure& error) {denied=error.fault()==recovery::ImageFault::binding;}
  assert(denied && pending.active() && pending.output_work()==work && account.statistics().current==before);
  static_cast<void>(pending.commit());assert(live.sequence()==1);
}
void magnitudes_and_wire(bool indexed) {
  const auto program=bind("SELECT x FROM r");const auto account=resource::MemoryAccount::create(memory);
  auto runtime=runtime::SqlRowsRuntime::create_into(account,program,tree(program),indexed?s04_runtime::options():PhysicalOptions{});
  const std::array<Cell,2> row{Cell{},text("kept")};std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,UINT64_MAX}};
  auto pending=runtime.prepare_output_batch({1,edits});
  auto frame=rr::encode(account,program,1,rr::RowEpochView{1,1,1,hash('a'),true,&pending});
  auto expected=body(1,true,1);integer(expected,1);integer(expected,0,1);integer(expected,0,1);integer(expected,UINT64_MAX);
  assert(frame.bytes()==envelope(expected));assert(std::get<rr::RowInfo>(frame.info().payload).rows==1);
  inspect_checks(program,frame.bytes());
  std::string zero(frame.bytes());std::fill(zero.begin()+265,zero.end(),0);reseal(zero);
  rejected([&]{static_cast<void>(rr::inspect(program,zero));});
  std::string duplicate(frame.bytes());duplicate.append(frame.bytes().substr(255));duplicate[247]=2;reseal(duplicate);
  rejected([&]{static_cast<void>(rr::inspect(program,duplicate));});
  std::string false_change(frame.bytes());false_change[246]=0;reseal(false_change);
  rejected([&]{static_cast<void>(rr::inspect(program,false_change));});
  static_cast<void>(pending.commit());edits[0].before=UINT64_MAX;edits[0].after=0;
  auto erased=runtime.prepare_output_batch({2,edits});
  auto negative=rr::encode(account,program,2,rr::RowEpochView{1,2,2,hash('a'),true,&erased});
  expected=body(2,true,1);integer(expected,1);integer(expected,0,1);integer(expected,1,1);integer(expected,UINT64_MAX);
  assert(negative.bytes()==envelope(expected));static_cast<void>(erased.commit());
  assert(runtime.sequence()==2 && runtime.source_weight(TableId{0},row)==0);
}
void support_and_constants(bool indexed) {
  for(const std::string_view sql:{"SELECT DISTINCT x,7 AS token FROM r", "SELECT EXISTS(SELECT FROM r WHERE x IS NULL)"}) {
    const auto program=bind(sql);const auto account=resource::MemoryAccount::create(memory);
    auto runtime=runtime::SqlRowsRuntime::create_into(account,program,tree(program),indexed?s04_runtime::options():PhysicalOptions{});
    const bool exists=program.wrapper()==frontend::SqlWrapper::exists;
    const std::array<Cell,2> row{Cell{},text("a")};std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
    auto first=runtime.prepare_output_batch({1,edits});
    auto frame=rr::encode(account,program,1,rr::RowEpochView{1,1,1,hash('a'),true,&first});
    const auto info=std::get<rr::RowInfo>(rr::inspect(program,frame.bytes()).payload);
    assert(info.output_changed && info.rows==(exists?2U:1U));
    if(!exists) {
      // The constant7 is typed bigint and must remain7 even in checksum-valid frames.
      std::string false_constant(frame.bytes());false_constant[266]=8;reseal(false_constant);
      rejected([&]{static_cast<void>(rr::inspect(program,false_constant));});
      std::string multiple(frame.bytes());multiple[multiple.size()-8]=2;reseal(multiple);
      rejected([&]{static_cast<void>(rr::inspect(program,multiple));});
    }
    static_cast<void>(first.commit());edits[0].before=2;edits[0].after=3;
    auto numeric=runtime.prepare_output_batch({2,edits});
    auto empty=rr::encode(account,program,2,rr::RowEpochView{1,2,2,hash('a'),true,&numeric});
    assert(empty.bytes().size()==255 && !std::get<rr::RowInfo>(empty.info().payload).output_changed);
    static_cast<void>(numeric.commit());edits[0].before=3;edits[0].after=0;
    auto last=runtime.prepare_output_batch({3,edits});
    auto removed=rr::encode(account,program,3,rr::RowEpochView{1,3,3,hash('a'),true,&last});
    assert(std::get<rr::RowInfo>(removed.info().payload).rows==(exists?2U:1U));static_cast<void>(last.commit());
  }
}
void input_and_wal() {
  const auto program=bind("SELECT x FROM r");const auto account=resource::MemoryAccount::create(memory);
  std::string tag="source-text",source="feed";const std::array<Cell,2> row{n(17),text(tag)};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,UINT64_MAX}};
  auto input=rr::encode_input(account,program,1,{1,edits,rr::SourcePosition{source,9},rr::ReaderPosition{12,1}});
  const std::string original(input.frame().bytes());tag.assign(64,'z');source="different";
  auto decoded=rr::decode_input(account,program,original);const auto view=decoded.view();
  assert(view.source->source=="feed" && view.reader==(rr::ReaderPosition{12,1}) && view.replacements[0].after==UINT64_MAX);
  assert(std::get<std::string_view>(*view.replacements[0].values[1])=="source-text");
  const rr::WalHeader header{{id('1'),hash('2')},1,hash('3'),0,0};
  const auto first=rr::encode(account,program,0,header);
  const auto commit=rr::encode(account,program,2,rr::Commit{1,input.frame().info().body_sha256,1,1,255,hash('4')});
  rr::WalCursor cursor;static_cast<void>(cursor.feed(program,first.bytes()));static_cast<void>(cursor.feed(program,input.frame().bytes()));
  std::string bad(commit.bytes());bad[165]=bad[165]=='a'?'b':'a';reseal(bad);
  rejected([&]{static_cast<void>(cursor.feed(program,bad));});assert(cursor.state().pending && cursor.state().physical_sequence==0);
  static_cast<void>(cursor.feed(program,commit.bytes()));
  auto next=rr::encode_input(account,program,3,{2,{},std::nullopt,std::nullopt});
  const auto reject=rr::encode(account,program,4,rr::Reject{3,next.frame().info().body_sha256,2,1,rr::RejectReason::weight_mismatch});
  static_cast<void>(cursor.feed(program,next.frame().bytes()));static_cast<void>(cursor.feed(program,reject.bytes()));
  assert(cursor.state().logged_sequence==2 && cursor.state().command_sequence==2 && cursor.state().physical_sequence==1 && !cursor.state().pending);
  const std::array<Cell,2> wrong{storage::ScalarView{true},text("bad")};const std::array bad_edit{runtime::sql_rows::SourceReplacement{TableId{0},wrong,0,1}};
  rejected([&]{static_cast<void>(rr::encode_input(account,program,5,{3,bad_edit,{},{}}));});
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {magnitudes_and_wire(indexed);support_and_constants(indexed);}
    binding_opt_in();input_and_wal();std::cout<<"plain SQL row records: exact nullable unsigned deltas and owned transport\n";
  } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}

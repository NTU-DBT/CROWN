#include "crown/io/sql_aggregate_input.hpp"
#include "crown/io/document.hpp"
#include "crown/api/error.hpp"
#include "sql_aggregate_session_fixture.hpp"
#include "index_allocation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace {
using namespace crown;
namespace ar=recovery::sql_aggregate;
using io::Json;
using Reader=io::SqlAggregateJsonlReader;
template<class T> concept RvalueView=requires(const T&& value){std::move(value).view();};
static_assert(!RvalueView<io::SqlAggregateJsonCommand>);
static_assert(!std::is_copy_constructible_v<Reader> && std::is_nothrow_move_constructible_v<Reader>);
frontend::SqlAggregateProgram bind_program() {
  Catalog catalog{1,{{"r",{{"g",ScalarType::string,true},{"id",ScalarType::int64},
      {"flag",ScalarType::boolean},{"d",ScalarType::date},
      {"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}},{"x",ScalarType::int64,true}}}}};
  auto bound=frontend::bind_sql_aggregate("SELECT g,COUNT(*),SUM(id) FROM r GROUP BY g",catalog);
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(bound));return std::get<frontend::SqlAggregateProgram>(std::move(bound));
}
Json record(const frontend::SqlAggregateProgram& program,std::uint64_t sequence=1) {
  const auto& binding=program.identity().binding;
  return {{"schema_version",1},{"binding_sha256",std::string(binding.begin(),binding.end())},{"sequence",sequence},
      {"replacements",Json::array({{{"table","r"},{"source_schema_version",1},
        {"values",Json::array({"long enough TEXT to leave the small string buffer",42,true,Json{{"date","2020-02-29"}},Json{{"decimal","12.50"}},nullptr})},
        {"before",0},{"after",3}}})},{"source_position",{{"source","source-name-owned-through-command-moves"},{"offset",0}}}};
}
template<class Action> void error(Action action,std::string_view expected={}) {
  bool refused=false;try {action();}catch(const Error& failure) {refused=true;if(!expected.empty())assert(failure.code()==expected);}assert(refused);
}
// A returned command survives reader/stream/DOM destruction and later decoding;
// exact LF/CRLF byte counters are independent of command/native frontiers.
void ownership(const frontend::SqlAggregateProgram& schema) {
  const auto account=resource::MemoryAccount::create(32ULL*1024*1024);const auto baseline=account.statistics().current;
  {
    std::optional<io::SqlAggregateJsonCommand> saved;const auto first=record(schema).dump()+"\r\n";
    auto second=record(schema,2);second["replacements"]=Json::array();second.erase("source_position");
    const auto last=second.dump();
    {
      std::istringstream stream(first+last);Reader reader(stream,account,schema);
      saved=reader.next();assert(saved);const auto one=saved->view();assert(one.reader==ar::ReaderPosition(first.size(),1));
      auto two=reader.next();assert(two && two->view().replacements.empty() && !two->view().source);
      assert(reader.position()==ar::ReaderPosition(first.size()+last.size(),2));
      assert(!reader.next() && !reader.next());assert(!reader.requires_reopen());
    }
    auto moved=std::move(*saved);error([&]{(void)saved->view();},"invalid_input_state");
    const auto view=moved.view();assert(view.command_sequence==1 && view.replacements.size()==1);
    const auto& edit=view.replacements[0];assert(edit.before==0 && edit.after==3 && edit.values.size()==6);
    assert(std::get<std::string_view>(*edit.values[0])=="long enough TEXT to leave the small string buffer");
    assert(view.source->source=="source-name-owned-through-command-moves" && !edit.values[5]);
    assert(std::get<Date>(*edit.values[3])==Date::parse("2020-02-29"));
    assert(std::get<storage::InlineDecimal>(*edit.values[4])==storage::InlineDecimal::parse("12.5"));
  }
  assert(account.statistics().current==baseline);
}
void malformed(const frontend::SqlAggregateProgram& schema) {
  const auto account=resource::MemoryAccount::create(32ULL*1024*1024);const auto good=record(schema);
  std::vector<Json> cases;
  auto bad=good;bad["extra"]=0;cases.push_back(bad);
  bad=good;bad.erase("sequence");cases.push_back(bad);
  bad=good;bad["schema_version"]=2;cases.push_back(bad);
  bad=good;bad["sequence"]=2;cases.push_back(bad);
  bad=good;bad["sequence"]=-1;cases.push_back(bad);
  bad=good;bad["binding_sha256"]=std::string(64,'f');cases.push_back(bad);
  bad=good;bad["replacements"]=Json::object();cases.push_back(bad);
  for(const auto& [field,value]:std::vector<std::pair<std::string,Json>>{{"table","R"},{"source_schema_version",2},{"before",-1},{"after",1.5},{"extra",0}}) {
    bad=good;bad["replacements"][0][field]=value;cases.push_back(bad);
  }
  for(const auto& [column,value]:std::vector<std::pair<std::size_t,Json>>{{0,std::string("nul\0byte",8)},{1,nullptr},{1,UINT64_MAX},{2,1},{3,Json{{"date","2021-02-29"}}},{4,Json{{"decimal","10000.00"}}},{5,1.5}}) {
    bad=good;bad["replacements"][0]["values"][column]=value;cases.push_back(bad);
  }
  bad=good;bad["replacements"][0]["values"].erase(0);cases.push_back(bad);
  bad=good;bad["source_position"]["source"]="";cases.push_back(bad);
  bad=good;bad["source_position"]["offset"]=-1;cases.push_back(bad);
  for(const auto& item:cases) {
    std::istringstream stream(item.dump()+"\n");Reader reader(stream,account,schema);
    error([&]{(void)reader.next();});assert(reader.requires_reopen());
    error([&]{(void)reader.next();},"invalid_input_state");error([&]{(void)reader.position();},"invalid_input_state");
  }
  for(const auto& input:std::vector<std::string>{"\n"," ",good.dump()+" x",std::string("{\"schema_version\":1,")+good.dump().substr(1)}) {
    std::istringstream stream(input);Reader reader(stream,account,schema);error([&]{(void)reader.next();});assert(reader.requires_reopen());
  }
  std::istringstream failed;failed.setstate(std::ios::badbit);Reader reader(failed,account,schema);
  error([&]{(void)reader.next();},"io_error");assert(reader.requires_reopen());
}
void limits(const frontend::SqlAggregateProgram& schema) {
  const auto account=resource::MemoryAccount::create(32ULL*1024*1024);auto item=record(schema);item.erase("source_position");
  const auto line=item.dump();io::SqlAggregateJsonlLimits exact;exact.record_bytes=line.size();exact.bytes=line.size()+2;exact.records=1;
  exact.replacements=1;exact.cells=6;exact.field_bytes=49;
  {
    std::istringstream stream(line+"\r\n");Reader reader(stream,account,schema,0,{},exact);
    assert(reader.next() && !reader.next());
  }
  std::vector<io::SqlAggregateJsonlLimits> low;
  auto cap=exact;--cap.record_bytes;low.push_back(cap);cap=exact;--cap.bytes;low.push_back(cap);
  cap=exact;cap.records=0;low.push_back(cap);cap=exact;cap.replacements=0;low.push_back(cap);cap=exact;cap.cells=5;low.push_back(cap);
  cap=exact;cap.field_bytes=0;low.push_back(cap);
  for(const auto value:low) {
    std::istringstream stream(line+"\r\n");Reader reader(stream,account,schema,0,{},value);
    error([&]{(void)reader.next();},"resource_limit");assert(reader.requires_reopen());
  }
  // Remove TEXT to isolate the tagged scalar cap before DATE/DECIMAL parsing.
  item["replacements"][0]["values"][0]=nullptr;cap={};cap.field_bytes=9;
  {
    std::istringstream stream(item.dump());Reader reader(stream,account,schema,0,{},cap);
    error([&]{(void)reader.next();},"resource_limit");
  }
  item["replacements"][0]["values"][3]=Json{{"date","2020-02-29"}};cap.field_bytes=10;
  item["replacements"][0]["values"][4]=Json{{"decimal","0000000012.50"}};
  {
    std::istringstream stream(item.dump());Reader reader(stream,account,schema,0,{},cap);
    error([&]{(void)reader.next();},"resource_limit");
  }
  std::istringstream empty;cap={};cap.records=cap.bytes=0;Reader zero(empty,account,schema,0,{},cap);assert(!zero.next());
  error([&]{Reader invalid(empty,account,schema,1,{0,1});},"invalid_input_progress");
  const auto next=record(schema,8).dump();std::istringstream resumed(next);Reader seven(resumed,account,schema,7,{1000,7});
  assert(seven.next()->view().reader==ar::ReaderPosition(1000+next.size(),8));
}
// Deny every observed C++ allocation in constructor/decode. DOM destruction can
// fall back without propagating allocation failure: require a correct command
// or an exception, and exact receiving-account restoration in either case.
void allocation_cuts(const frontend::SqlAggregateProgram& schema) {
  const auto account=resource::MemoryAccount::create(32ULL*1024*1024);const auto line=record(schema).dump();
  const auto baseline=account.statistics().current;std::size_t calls=0;
  {std::istringstream stream(line);s04_alloc::Scope count;{Reader reader(stream,account,schema);assert(reader.next());}calls=s04_alloc::calls;}
  assert(account.statistics().current==baseline);
  std::size_t propagated=0,fallbacks=0;
  for(std::size_t i=0;i<calls;++i) {
    std::istringstream stream(line);bool failed=false,decoded=false,triggered=false;
    {
      s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(i));
      try {
        Reader reader(stream,account,schema);auto command=reader.next();assert(command);
        const auto view=command->view();assert(view.command_sequence==1 && view.replacements[0].after==3);
        assert(std::get<std::string_view>(*view.replacements[0].values[0])=="long enough TEXT to leave the small string buffer");
        decoded=true;
      }catch(const std::bad_alloc&){failed=true;}
      triggered=s04_alloc::triggered;
    }
    assert(triggered && (failed || decoded) && account.statistics().current==baseline);
    if(failed)++propagated;else ++fallbacks;
  }
  const auto measure=[&](std::uint64_t bytes) {
    const auto receiving=resource::MemoryAccount::create(bytes);const auto origin=receiving.statistics().current;
    {std::istringstream stream(line);Reader reader(stream,receiving,schema);assert(reader.next());}
    assert(receiving.statistics().current==origin);return receiving.statistics().peak_requested_bytes;
  };
  const auto peak=measure(32ULL*1024*1024);assert(measure(peak)==peak);
  bool refused=false;try {(void)measure(peak-1);}catch(const resource::MemoryFailure&){refused=true;}assert(refused);
  std::cout<<"aggregate JSONL covered allocation cuts="<<calls<<" propagated="<<propagated
      <<" cleanup fallbacks="<<fallbacks<<" receiving peak="<<peak<<'\n';
}
// Integration fixture only: persist a real Input or Commit through public APIs,
// then release locks so the actual CLI must resume it without duplicate logging.
void leave(int argc,char** argv) {
  assert(argc==5 || argc==6);const auto account=resource::MemoryAccount::create(256ULL*1024*1024);
  ar::SessionLimits limits;if(argc==6)limits.rebuild.source.indexed_work=storage::IndexWork{100000000,100000000,100000000,100000000,100000000};
  ar::Id query;query.fill('0');auto session=ar::Session::recover_into(account,{argv[2],argv[3]},query,limits);
  const auto origin=session.logged_reader_position().value_or(ar::ReaderPosition{});
  std::ifstream stream(argv[4],std::ios::binary);assert(stream);stream.seekg(static_cast<std::streamoff>(origin.bytes));
  Reader reader(stream,account,session.descriptor().program(),session.state().logged,origin);
  auto command=reader.next();assert(command);session.log(command->view());
  if(std::string_view(argv[1])=="--leave-output")assert(!session.decide().rejected);
}
} // namespace
int main(int argc,char** argv) {
  try {
    if(argc>1){leave(argc,argv);return 0;}
    const auto schema=bind_program();ownership(schema);malformed(schema);limits(schema);allocation_cuts(schema);return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

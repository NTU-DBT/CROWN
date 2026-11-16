#include "crown/runtime/session.hpp"
#include "crown/runtime/replay.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message));}
Catalog schema() {return Catalog{1,{{"input",{{"id",ScalarType::int64},{"text",ScalarType::string},{"flag",ScalarType::boolean},
    {"day",ScalarType::date},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}}}};}
PhysicalPlan plan(bool indexed) {return planner::lower_tree(schema(),Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():PhysicalOptions{});}
DeltaOptions runtime_options(std::uint64_t cap=64*1024*1024) {DeltaOptions value;value.physical.support.memory_limit_bytes=cap;return value;}
constexpr std::array formats{io::InputFormat::jsonl,io::InputFormat::binary,io::InputFormat::csv,io::InputFormat::legacy_signed,
    io::InputFormat::legacy_relations,io::InputFormat::legacy_insert_only,io::InputFormat::legacy_flags,io::InputFormat::legacy_timestamp_flags};
std::string quote(std::string_view input) {
  std::string result="\"";for(const char ch:input){if(ch=='"')result+='"';result+=ch;}return result+'"';
}
struct Fixture {
  io::InputOptions options;
  std::string bytes;
  std::array<io::InputEvent,2> expected;
  explicit Fixture(io::InputFormat format,std::size_t payload=8192) {
    options.format=format;
    const bool wire=format==io::InputFormat::jsonl || format==io::InputFormat::binary;
    const auto source=std::string(120,'s');const auto token=std::string(97,'r');
    if(!wire) {
      options.source=source;options.null_token=std::string(80,'N');
      if(format==io::InputFormat::legacy_relations)options.relation_tokens.emplace(token,TableId{0});else options.table=TableId{0};
      if(format!=io::InputFormat::legacy_timestamp_flags)options.byte_offset=100;
      if(format==io::InputFormat::csv)bytes="amount,day,flag,text,id\r\n";
    }
    for(std::size_t i=0;i<2;++i) {
      const auto id=static_cast<std::int64_t>(i+1);
      const auto text=std::string("stream\0\n\"",9)+"\xe4\xb8\xad"+std::string(payload,'x');
      Row row{id,text,true,Date::parse("2026-11-09"),Decimal::parse("123456789012345678901234567890123456.12")};row.reserve(16);
      const auto offset=wire?static_cast<std::uint64_t>(i+1):format==io::InputFormat::legacy_timestamp_flags?99+i:100+bytes.size();
      expected[i]={{i+1,TableId{0},SetOperation::insert,std::move(row)},io::SourcePosition{source,offset}};
      if(format==io::InputFormat::jsonl){bytes+=io::write_input_json(expected[i],schema())+"\r\n";continue;}
      if(format==io::InputFormat::binary){bytes+=io::write_input_binary(expected[i],schema());continue;}
      const auto amount="123456789012345678901234567890123456.12";
      if(format==io::InputFormat::csv)bytes+=std::string(amount)+",2026-11-09,true,"+quote(text)+","+std::to_string(id)+"\r\n";
      else {
        if(format==io::InputFormat::legacy_signed)bytes+="+,";
        else if(format==io::InputFormat::legacy_relations)bytes+="+,"+token+",";
        else if(format==io::InputFormat::legacy_flags)bytes+="1,";
        else if(format==io::InputFormat::legacy_timestamp_flags)bytes+=std::to_string(99+i)+",1,";
        bytes+=std::to_string(id)+","+quote(text)+",true,2026-11-09,"+amount+"\n";
      }
    }
  }
};
bool same(const io::InputEventView& actual,const io::InputEvent& expected) {
  return actual.update.sequence==expected.update.sequence && actual.update.table==expected.update.table &&
      actual.update.operation==expected.update.operation && actual.update.values==expected.update.values && actual.source_position==expected.source_position;
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto usage=account.statistics().current;
  check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),"stream reader/options/progress retained storage after final release");
}
void accept(io::EventReader& reader,DeltaRuntime& runtime) {
  const auto* event=reader.peek();check(event,"stream reader lost cached event");auto pending=runtime.begin_view(event->update);pending.drain();
  {s04_alloc::Scope none(0);auto epoch=pending.commit();reader.acknowledge();epoch.discard();}
}
void ownership(bool indexed,io::InputFormat format) {
  Fixture fixture(format);resource::MemoryAccount account;io::AccountedInputProgress held,closed;
  {
    DeltaRuntime runtime(plan(indexed),runtime_options());account=runtime.plan().account();std::istringstream stream(fixture.bytes);
    auto config=fixture.options;std::optional<io::EventReader> reader;auto before=account.statistics().successful_allocations;std::size_t calls=0;
    {s04_alloc::Scope count;reader.emplace(stream,runtime.plan(),std::move(config));calls=s04_alloc::calls;}
    check(calls>0 && calls==account.statistics().successful_allocations-before && reader->account().statistics().owner==account.statistics().owner,
        "stream constructor/fingerprint/options/control allocated outside the original grant");
    before=account.statistics().successful_allocations;const io::InputEventView* head=nullptr;
    {s04_alloc::Scope count;head=reader->peek();calls=s04_alloc::calls;}
    check(head && same(*head,fixture.expected[0]) && calls==account.statistics().successful_allocations-before && calls>0,
        "stream framing/lexer/parser/decimal/row/progress staging allocated ordinary storage or changed values");
    {s04_alloc::Scope none(0);check(reader->peek()==head,"stream cached pointer changed");}
    check(reader->progress().sequence==0 && reader->records_read()==1,"stream peek accepted input early");accept(*reader,runtime);
    before=account.statistics().successful_allocations;
    {s04_alloc::Scope count;held=reader->progress();calls=s04_alloc::calls;}
    check(calls>0 && calls==account.statistics().successful_allocations-before,"stream progress snapshot used unaccounted storage");
    check(reader->peek() && same(*reader->peek(),fixture.expected[1]),"second stream row changed");accept(*reader,runtime);
    check(held.sequence==1 && held.source_positions.at(fixture.expected[0].source_position->source)==fixture.expected[0].source_position->offset,
        "stream accepted-progress value snapshot changed with its source");
    check(!reader->peek() && reader->records_read()==2 && reader->bytes_read()==fixture.bytes.size(),"stream EOF/raw byte/decoded count differs");
    {s04_alloc::Scope none(0);closed=reader->close();reader.reset();}
  }
  check(held.sequence==1 && closed.sequence==2 && closed.source_positions.at(fixture.expected[1].source_position->source)==fixture.expected[1].source_position->offset,
      "stream native progress lost source text after reader/program/runtime destruction");
  {s04_alloc::Scope none(0);held={};closed={};}controller_only(account);
}
void limits(bool indexed,io::InputFormat format) {
  Fixture big(format,131072);std::uint64_t peak=0;
  {
    DeltaRuntime runtime(plan(indexed),runtime_options());std::istringstream stream(big.bytes);io::EventReader reader(stream,runtime.plan(),big.options);
    const auto setup=runtime.plan().account().statistics().peak_requested_bytes;check(reader.peek()!=nullptr,"stream cap calibration failed");
    peak=runtime.plan().account().statistics().peak_requested_bytes;check(peak>setup,"stream payload failed to exceed setup peak");
  }
  {DeltaRuntime runtime(plan(indexed),runtime_options(peak));std::istringstream stream(big.bytes);io::EventReader reader(stream,runtime.plan(),big.options);
   check(reader.peek() && runtime.plan().account().statistics().peak_requested_bytes==peak,"exact original stream query cap changed");}
  resource::MemoryAccount account;
  {
    DeltaRuntime runtime(plan(indexed),runtime_options(peak-1));account=runtime.plan().account();const auto committed=runtime.canonical_state();std::istringstream stream(big.bytes);
    io::EventReader reader(stream,runtime.plan(),big.options);bool denied=false;
    try{static_cast<void>(reader.peek());}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong stream cap denial");denied=true;}
    check(denied && reader.failed() && reader.progress().sequence==0 && reader.records_read()==0 && runtime.canonical_state()==committed,
        "one-byte-short stream cap changed accepted progress or prior engine epoch");
    {s04_alloc::Scope none(0);auto discarded=reader.close();}
    Fixture small(format,16);std::istringstream replacement(small.bytes);io::EventReader retry(replacement,runtime.plan(),small.options);
    check(retry.peek() && same(*retry.peek(),small.expected[0]),"smaller same-sequence explicit stream recreation failed");accept(retry,runtime);
    check(runtime.sequence()==1 && retry.progress().sequence==1 && account.statistics().limit_bytes==peak-1,"stream recreation replaced the original grant");
  }
  controller_only(account);std::cout<<(indexed?"indexed":"reference")<<" stream format="<<static_cast<int>(format)<<" exact/one-under peak="<<peak<<'\n';
}
void faults(bool indexed,io::InputFormat format) {
  Fixture fixture(format,256);
  for(const bool construction:{true,false}) {
    std::size_t failures=0;bool complete=false;
    for(std::ptrdiff_t point=0;point<512;++point) {
      DeltaRuntime runtime(plan(indexed),runtime_options());const auto account=runtime.plan().account();const auto baseline=account.statistics().current;
      std::istringstream stream(fixture.bytes);auto config=fixture.options;std::optional<io::EventReader> reader;
      if(!construction)reader.emplace(stream,runtime.plan(),std::move(config));
      bool failed=false;
      {s04_alloc::Scope fault(point);try {
        if(construction)reader.emplace(stream,runtime.plan(),std::move(config));else static_cast<void>(reader->peek());
      }catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;
        if(construction)check(stream.tellg()==0 && !reader && account.statistics().current==baseline,"failed stream construction consumed bytes or leaked native storage");
        else {
          check(reader->failed() && reader->progress().sequence==0 && reader->records_read()==0 && runtime.sequence()==0,"failed stream peek changed its accepted prefix");
          bool sticky=false;try{static_cast<void>(reader->peek());}catch(const Error& error){sticky=error.code()=="input_failed";}check(sticky,"stream allocation failure lost sticky error policy");
          {s04_alloc::Scope none(0);auto progress=reader->close();reader.reset();}
          check(account.statistics().current==baseline,"stream fault/close leaked native decoder/options/source storage");
        }
        std::istringstream replacement(fixture.bytes);io::EventReader retry(replacement,runtime.plan(),fixture.options);
        check(retry.peek() && same(*retry.peek(),fixture.expected[0]),"explicit stream fault recreation changed the event");accept(retry,runtime);
      }else {
        complete=true;check(reader->peek() && same(*reader->peek(),fixture.expected[0]),"successful stream fault endpoint changed native row");accept(*reader,runtime);
      }
      account.check_invariants();if(complete)break;
    }
    check(complete && failures>0,"persistent native stream fault sweep incomplete");
    std::cout<<(indexed?"indexed":"reference")<<" stream format="<<static_cast<int>(format)<<" phase="<<(construction?"constructor":"peek")<<" persistent faults="<<failures<<'\n';
  }
}
std::string replaced(std::string value,std::string_view from,std::string_view to) {
  const auto at=value.find(from);check(at!=std::string::npos,"bad parser parity fixture");value.replace(at,from.size(),to);return value;
}
template<class Action> std::pair<std::string,std::string> diagnostic(Action&& action) {
  try{action();return {};}catch(const Error& error){return {error.code(),error.what()};}
}
void json_parity(bool indexed) {
  Fixture fixture(io::InputFormat::jsonl,16);const auto canonical=io::write_input_json(fixture.expected[0],schema());
  const std::string marker=",\"values\":";const auto at=canonical.find(marker);
  std::vector<std::string> cases{canonical,"\xef\xbb\xbf"+canonical,
      "{\"values\":"+canonical.substr(at+marker.size(),canonical.size()-1-at-marker.size())+","+canonical.substr(1,at-1)+"}",
      replaced(canonical,"stream","\\u0073tream"),replaced(canonical,"\"sequence\":1","\"sequence\":0"),
      replaced(canonical,"\"schema_version\":1","\"schema_version\":2"),replaced(canonical,"\"operation\":\"insert\"","\"operation\":\"update\""),
      replaced(canonical,"\"values\":[1,","\"values\":[null,"),replaced(canonical,"\"values\":[1,","\"values\":[1.5,"),
      replaced(canonical,"\"values\":[1,","\"values\":[18446744073709551615,"),
      replaced(canonical,"\"table\":\"input\"","\"table\":\"missing\""),
      "{\"unknown\":1,"+canonical.substr(1),"{\"sequence\":1,"+canonical.substr(1),
      replaced(canonical,"\"offset\":1","\"offset\":-1"),replaced(canonical,"stream","\\ud800"),
      replaced(canonical,"stream",std::string(1,static_cast<char>(0xff))),canonical.substr(0,canonical.size()-1),
      replaced(canonical,"stream","\\ud83d\\ude80"),replaced(canonical,"\"sequence\":1","\"sequence\":-0")};
  for(const auto& bytes:cases) {
    std::optional<io::InputEvent> expected;const auto reference=diagnostic([&]{expected=io::read_input_json(bytes,schema());});
    DeltaRuntime runtime(plan(indexed),runtime_options());std::istringstream stream(bytes+"\n");io::EventReader reader(stream,runtime.plan());
    const io::InputEventView* actual=nullptr;const auto native=diagnostic([&]{actual=reader.peek();});
    check(native.first==reference.first,"native JSON parser error code differs from unchanged public codec");
    if(expected)check(actual && same(*actual,*expected),"native JSON parser changed arbitrary-order/Unicode/scalar values");
    else check(reader.failed() && reader.progress().sequence==0 && runtime.sequence()==0,"malformed native JSON changed its accepted prefix");
  }
}
void retained_options(bool indexed) {
  Fixture fixture(io::InputFormat::legacy_relations,32);resource::MemoryAccount account;std::shared_ptr<const SessionRunContext> held;
  {
    SessionOptions options;options.input=fixture.options;auto stream=std::make_unique<std::istringstream>(fixture.bytes);
    auto session=QuerySession::create(plan(indexed),std::move(stream),options);account=session.get_deleter().account();held=session->run_context();
    check(held->input.account().statistics().owner==account.statistics().owner && held->input.get().relation_tokens.size()==1,
        "session run-context input options did not retain original-grant nodes/text");
    {s04_alloc::Scope none(0);auto copy=held->input;check(copy.get().source==held->input.get().source,"native input option copy changed source");session->stop();session->drop();session.reset();}
  }
  const auto exported=held->input.export_value();check(exported.source==fixture.options.source && exported.null_token==fixture.options.null_token && exported.relation_tokens==fixture.options.relation_tokens,
      "retained native options lost exact names/null/source after session/runtime destruction");
  {s04_alloc::Scope none(0);held.reset();}controller_only(account);
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      for(const auto format:formats){ownership(indexed,format);limits(indexed,format);faults(indexed,format);}
      json_parity(indexed);retained_options(indexed);
    }
    std::cout<<"native stream input: original grants, all eight profiles, codec parity, actual requests, caps, persistent faults and retained options/progress passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}

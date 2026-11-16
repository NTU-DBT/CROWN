#include "aggregate.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/binding.hpp"
#include "crown/io/normalization.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/sql_aggregate_input.hpp"
#include "crown/recovery/sql_aggregate_session.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/storage/index_failure.hpp"
#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>

namespace crown::cli {
namespace {
namespace ar=recovery::sql_aggregate;
using io::Json;
constexpr std::size_t document_bytes=16U*1024U*1024U;
std::uint64_t number(std::string_view value) {
  std::uint64_t result=0;const auto parsed=std::from_chars(value.data(),value.data()+value.size(),result);
  if(parsed.ec!=std::errc{} || parsed.ptr!=value.data()+value.size())throw Error("usage","expected an unsigned integer");
  return result;
}
std::size_t size(std::uint64_t n) {
  if(n>SIZE_MAX)throw Error("usage","size exceeds this host");
  return static_cast<std::size_t>(n);
}
std::string read(const std::string& path,std::size_t limit=document_bytes) {
  std::ifstream input(path,std::ios::binary);if(!input)throw Error("io_error","cannot open aggregate input document");
  std::string result;char block[8192];
  while(input) {
    input.read(block,sizeof(block));const auto bytes=static_cast<std::size_t>(input.gcount());
    if(bytes>limit-result.size())throw Error("resource_limit","aggregate input document exceeds its byte limit");
    result.append(block,bytes);
  }
  if(input.bad())throw Error("io_error","failed reading aggregate input document");
  return result;
}
struct Arguments {
  std::string command;
  std::vector<std::string> paths;
  std::map<std::string,std::string> options;
  Arguments(int argc,char** argv):command(argv[2]) {
    for(int i=3;i<argc;++i) {
      const std::string key(argv[i]);
      if(!key.starts_with("--")){paths.push_back(key);continue;}
      if(i+1>=argc || std::string_view(argv[i+1]).starts_with("--"))throw Error("usage","aggregate option requires a value: "+key);
      if(!options.emplace(key,argv[++i]).second)throw Error("usage","duplicate aggregate option: "+key);
    }
  }
  std::optional<std::string> take(const char* key) {
    const auto found=options.find(key);if(found==options.end())return {};
    auto result=found->second;options.erase(found);return result;
  }
  std::uint64_t integer(const char* key,std::uint64_t fallback) {const auto value=take(key);return value?number(*value):fallback;}
  void finish(std::size_t count) const {
    if(paths.size()!=count)throw Error("usage","incorrect aggregate paths; use crown aggregate --help");
    if(!options.empty())throw Error("usage","unknown or inapplicable aggregate option: "+options.begin()->first);
  }
};
ar::Id identity(const std::optional<std::string>& value,char default_digit) {
  ar::Id result;result.fill(default_digit);if(!value)return result;
  if(value->size()!=result.size() || !std::all_of(value->begin(),value->end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');}))
    throw Error("usage","aggregate identities require 32 lowercase hexadecimal characters");
  std::copy(value->begin(),value->end(),result.begin());return result;
}
void help() {
  std::cout<<"usage: crown aggregate create QUERY.sql CATALOG.json ROOT SINK [OPTIONS]\n"
      "       crown aggregate run ROOT SINK INPUT.jsonl [--commands N] [OPTIONS]\n"
      "       crown aggregate {status|snapshot|checkpoint} ROOT SINK [OPTIONS]\n"
      "common: --query-id HEX32 (default 32 zeroes), --memory-limit-bytes N, --max-bytes N\n"
      "create: --sink-id HEX32 (default 32 ones), --average-scale N, --physical-options FILE\n"
      "        --parameter-types FILE --parameters FILE --search-work N --count-limit N --multiplicity-limit N\n"
      "recovery: --history-generations N --replay-commands N --replay-codec-work N --repair-tail yes|no\n"
      "          --rebuild-indexed-work N (required for indexed storage, one finite cap per work domain)\n"
      "run: --record-bytes N --field-bytes N --source-bytes N --replacements N --cells N --input-bytes N --records N\n"
      "R2 JSONL binds the reported binding_sha256; each record is one atomic weight-replacement command.\n"
      "Run resumes logged W and its reader position, resolves the pending head and delivers output first.\n"
      "--commands counts decisions in this invocation, including a previously logged pending head.\n"
      "Even --commands 0 delivers an existing committed spool. Checkpoint requires a quiescent session.\n"
      "The binary sink is durable output; stdout is a bounded report, not an acknowledgement.\n";
}
Json position(std::optional<ar::ReaderPosition> value) {
  return value?Json{{"bytes",value->bytes},{"records",value->records}}:Json{};
}
Json status(const ar::Session& session) {
  const auto state=session.state();const auto& descriptor=session.descriptor();
  const auto& binding=descriptor.program().identity().binding;const auto root=session.selected_root();
  return {{"schema_version",1},{"family","sql_aggregate"},{"binding_sha256",std::string(binding.begin(),binding.end())},
      {"query_id",std::string(root.query_id.begin(),root.query_id.end())},
      {"logged",state.logged},{"disposed",state.disposed},{"committed",state.committed},
      {"delivered",state.delivered},{"generation",state.generation},{"pending",state.pending},
      {"output_pending",state.output_pending},{"reader",position(session.reader_position())},
      {"logged_reader",position(session.logged_reader_position())},
      {"storage_backend",descriptor.native_program().options().indexed_storage?"indexed_chained_v1":"reference_ordered_v1"}};
}
// Final report bytes are capped before append; one scalar's JSON escape
// temporary follows the existing CLI's ordinary presentation allocation policy.
class Report {
 public:
  explicit Report(std::size_t limit):limit_(limit) {}
  void raw(std::string_view value) {
    if(value.size()>limit_-value_.size())throw Error("output_limit","aggregate report exceeds --max-bytes");
    value_.append(value);
  }
  void json(const Json& value) {raw(value.dump());}
  void tuple(const runtime::aggregate::Tuple& value) {
    raw("[");bool first=true;
    for(const auto& cell:value.view()) {if(!first)raw(",");first=false;json(cell?io::write_scalar_view(*cell):Json{});}raw("]");
  }
  void emit() const {
    std::cout.write(value_.data(),static_cast<std::streamsize>(value_.size()));std::cout.put('\n');
    if(!std::cout)throw Error("output_error","cannot write aggregate report; durable state remains authoritative");
  }
 private:
  std::size_t limit_;
  std::string value_;
};
void snapshot(const ar::Session& session,std::size_t max_bytes) {
  const auto image=session.snapshot();Report report(max_bytes);auto header=status(session).dump();header.pop_back();
  report.raw(header);report.raw(",\"columns\":[");bool first=true;
  for(const auto& output:image.program.kernel_program().outputs()) {
    if(!first)report.raw(",");
    first=false;
    report.json({{"name",output.name},{"kind",frontend::sql_kind_name(output.type.kind)},
        {"nullable",output.type.nullable},{"decimal",output.type.decimal?
          Json{{"precision",output.type.decimal->precision},{"scale",output.type.decimal->scale}}:Json{}}});
  }
  report.raw("],\"groups\":[");first=true;
  for(const auto& group:image.groups) {
    if(!first)report.raw(",");
    first=false;report.raw("{\"key\":");report.tuple(group.key);
    report.raw(",\"values\":");report.tuple(group.values);report.raw("}");
  }
  report.raw("]}");report.emit();
}
// A regular file is supplied from its original origin on every invocation.
// A saved offset alone is not a file-content hash; the caller preserves the
// consumed prefix. An unterminated final line cannot gain a second glued row.
void seek(std::ifstream& input,ar::ReaderPosition origin) {
  if(origin.bytes>static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max()))
    throw Error("invalid_input_progress","aggregate reader byte offset exceeds this host");
  input.seekg(0,std::ios::end);const auto end=input.tellg();
  if(end<0 || static_cast<std::uint64_t>(end)<origin.bytes)throw Error("invalid_input_progress","aggregate input is shorter than logged reader progress");
  if(origin.bytes>0 && origin.bytes<static_cast<std::uint64_t>(end)) {
    input.seekg(static_cast<std::streamoff>(origin.bytes-1),std::ios::beg);
    if(input.get()!='\n')throw Error("invalid_input_progress","aggregate continuation is not a line boundary");
  }
  input.seekg(static_cast<std::streamoff>(origin.bytes),std::ios::beg);
  if(!input)throw Error("io_error","cannot seek aggregate input continuation");
}
const char* reason(ar::RejectReason value) {
  switch(value) {
    case ar::RejectReason::weight_mismatch:return "weight_mismatch";
    case ar::RejectReason::source_overflow:return "source_overflow";
    case ar::RejectReason::unique_violation:return "unique_violation";
    case ar::RejectReason::foreign_key_violation:return "foreign_key_violation";
    case ar::RejectReason::aggregate_overflow:return "aggregate_overflow";
    case ar::RejectReason::annotation_overflow:return "annotation_overflow";
  }
  throw Error("runtime_contract","unknown durable aggregate Reject reason");
}
Json run(ar::Session& session,std::ifstream& input,const resource::MemoryAccount& account,
    std::uint64_t commands,io::SqlAggregateJsonlLimits limits) {
  std::uint64_t processed=0,commits=0,rejects=0;Json last_reject;
  std::optional<io::SqlAggregateJsonlReader> reader;
  (void)session.deliver();
  while(processed<commands) {
    if(!session.state().pending) {
      if(!reader) {
        const auto origin=session.logged_reader_position().value_or(ar::ReaderPosition{});
        if(origin.records!=session.state().logged)throw Error("invalid_input_progress","CLI JSONL requires one saved reader record per logged command");
        seek(input,origin);reader.emplace(input,account,session.descriptor().program(),session.state().logged,origin,limits);
      }
      // Release the decoded command before native preparation. The reader
      // retains its bounded raw-line capacity; log() owns the durable head.
      auto command=reader->next();if(!command)break;session.log(command->view());
    }
    const auto decision=session.decide();++processed;
    if(decision.rejected) {++rejects;last_reject={{"sequence",decision.command_sequence},{"reason",reason(*decision.rejected)}};}
    else ++commits;
    (void)session.deliver();
  }
  auto result=status(session);result["processed"]=processed;result["committed_here"]=commits;
  result["rejected_here"]=rejects;result["last_reject"]=std::move(last_reject);return result;
}

int execute(int argc,char** argv) {
  if(argc==2 || (argc>=3 && std::string_view(argv[2])=="--help") || (argc==4 && std::string_view(argv[3])=="--help")) {help();return 0;}
  Arguments args(argc,argv);
  if(args.command!="create" && args.command!="run" && args.command!="status" && args.command!="snapshot" && args.command!="checkpoint")
    throw Error("usage","unknown aggregate command");
  const auto max_bytes=size(args.integer("--max-bytes",document_bytes));
  if(max_bytes>64U*1024U*1024U)throw Error("usage","aggregate --max-bytes cannot exceed 64 MiB");
  if(max_bytes<2)throw Error("output_limit","aggregate --max-bytes cannot hold an object");
  const auto memory=args.integer("--memory-limit-bytes",256ULL*1024*1024);
  const auto query_id=identity(args.take("--query-id"),'0');ar::SessionLimits limits;
  limits.history_generations=args.integer("--history-generations",limits.history_generations);
  limits.replay_commands=args.integer("--replay-commands",limits.replay_commands);
  limits.replay_codec_work=args.integer("--replay-codec-work",limits.replay_codec_work);
  if(const auto work=args.take("--rebuild-indexed-work")) {
    const auto n=number(*work);limits.rebuild.source.indexed_work=storage::IndexWork{n,n,n,n,n};
  }
  if(const auto repair=args.take("--repair-tail")) {
    if(*repair!="yes" && *repair!="no")throw Error("usage","--repair-tail expects yes or no");
    limits.repair_torn_tail=*repair=="yes";
  }
  if(args.command=="create") {
    const auto sink_id=identity(args.take("--sink-id"),'1');const auto physical_path=args.take("--physical-options");
    const auto parameter_types=args.take("--parameter-types"),parameters=args.take("--parameters");
    const auto search_work=args.integer("--search-work",10000000);frontend::SqlAggregateBindOptions binding;
    const auto average=args.integer("--average-scale",binding.kernel.average_scale);
    if(average>18)throw Error("usage","aggregate AVG scale must be 0..18");
    binding.kernel.average_scale=static_cast<std::uint8_t>(average);
    runtime::sql_aggregate::Options options;options.capture_changes=true;
    options.count_limit=args.integer("--count-limit",options.count_limit);
    options.source.native.multiplicity_limit=args.integer("--multiplicity-limit",options.source.native.multiplicity_limit);
    args.finish(4);
    if(parameter_types)binding.source.binding=io::read_bind_options(read(*parameter_types));
    if(parameters)binding.source.parameters=io::read_parameter_values(read(*parameters));
    const auto physical=physical_path?io::read_physical_options(read(*physical_path)):PhysicalOptions{};
    const auto catalog=io::read_catalog(read(args.paths[1]));const auto account=resource::MemoryAccount::create(memory);
    auto compiled=frontend::bind_sql_aggregate_into(account,read(args.paths[0],binding.parsing.source_bytes),catalog,binding);
    if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&compiled))throw Error(failure->diagnostic.code,failure->diagnostic.message);
    auto program=std::get<frontend::SqlAggregateProgram>(std::move(compiled));FreeConnexTree tree;
    if(!program.source_program().contradiction()) {
      const auto core=program.source_program().export_core();planner::SearchLimits search;search.work_limit=search_work;
      const auto choice=planner::minimum_tree(core.catalog,core.query,search);
      if(choice.status==planner::OracleStatus::resource_limit)throw Error("resource_limit",choice.reason);
      if(choice.status!=planner::OracleStatus::proven_minimum || !choice.tree || !choice.certificate_verified)throw Error("unsupported_plan",choice.reason);
      tree=*choice.tree;
    }
    auto session=ar::Session::create_into(account,{args.paths[2],args.paths[3]},
        {query_id,sink_id},std::move(program),tree,physical,options,limits);
    Report report(max_bytes);report.json(status(session));report.emit();return 0;
  }
  const auto commands=args.command=="run"?args.integer("--commands",UINT64_MAX):0;
  io::SqlAggregateJsonlLimits input_limits;
  if(args.command=="run") {
    input_limits.record_bytes=size(args.integer("--record-bytes",input_limits.record_bytes));
    input_limits.field_bytes=size(args.integer("--field-bytes",input_limits.field_bytes));
    input_limits.source_bytes=size(args.integer("--source-bytes",input_limits.source_bytes));
    input_limits.replacements=size(args.integer("--replacements",input_limits.replacements));
    input_limits.cells=size(args.integer("--cells",input_limits.cells));
    input_limits.bytes=args.integer("--input-bytes",input_limits.bytes);input_limits.records=args.integer("--records",input_limits.records);
    if(input_limits.record_bytes==SIZE_MAX)throw Error("usage","aggregate record byte limit is too large");
  }
  args.finish(args.command=="run"?3:2);std::ifstream input;
  if(args.command=="run") {input.open(args.paths[2],std::ios::binary);if(!input)throw Error("io_error","cannot open aggregate JSONL input");}
  const auto account=resource::MemoryAccount::create(memory);
  auto session=ar::Session::recover_into(account,{args.paths[0],args.paths[1]},query_id,limits);
  if(args.command=="snapshot") {snapshot(session,max_bytes);return 0;}
  auto result=args.command=="run"?run(session,input,account,commands,input_limits):status(session);
  if(args.command=="checkpoint") {
    const auto state=session.state();if(state.pending || state.output_pending)throw Error("aggregate_state","run the pending decision/delivery before checkpoint");
    (void)session.checkpoint();result=status(session);
  }
  Report report(max_bytes);report.json(result);report.emit();return 0;
}
} // namespace

// Presentation only: fixed durable/resource failures are translated after all
// owned state has unwound. Actual command code uses its existing RAII barriers.
int aggregate_main(int argc,char** argv) {
  try {return execute(argc,argv);}
  catch(const ar::SessionFailure& error) {throw Error("aggregate_session",error.what());}
  catch(const ar::FileFailure& error) {throw Error("aggregate_file",error.what());}
  catch(const recovery::GenerationFailure& error) {throw Error("aggregate_generation",error.what());}
  catch(const recovery::ImageFailure& error) {throw Error("aggregate_image",error.what());}
  catch(const resource::MemoryFailure& error) {throw Error(std::string(error.code()),error.what());}
  catch(const storage::IndexFailure& error) {throw Error(std::string(error.code()),error.what());}
}
} // namespace crown::cli

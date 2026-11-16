#include "workflow.hpp"
#include "workflow_verify.hpp"
#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/frontend/admission.hpp"
#include "crown/io/admission.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/document.hpp"
#include "crown/io/explain.hpp"
#include "crown/io/oracle.hpp"
#include "crown/io/physical.hpp"
#include "crown/runtime/session_generation.hpp"
#include "crown/runtime/session_local_sink.hpp"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace {
using namespace crown;
using io::Json;
constexpr std::size_t document_limit=64U*1024U*1024U;
constexpr std::size_t default_output_limit=16U*1024U*1024U;

std::uint64_t integer(std::string_view text) {
  std::uint64_t value=0;
  const auto parsed=std::from_chars(text.data(),text.data()+text.size(),value);
  if(parsed.ec!=std::errc{} || parsed.ptr!=text.data()+text.size())
    throw Error("usage","expected an unsigned integer");
  return value;
}
std::size_t size(std::uint64_t value) {
  if(value>std::numeric_limits<std::size_t>::max())throw Error("resource_limit","size exceeds this host");
  return static_cast<std::size_t>(value);
}
std::string read(const std::string& path,std::size_t limit=document_limit) {
  std::ifstream file(path,std::ios::binary);
  if(!file)throw Error("io_error","cannot open input document");
  std::string result;char block[8192];
  while(file) {
    file.read(block,sizeof(block));const auto count=static_cast<std::size_t>(file.gcount());
    if(count>limit-result.size())throw Error("resource_limit","input document exceeds its byte limit");
    result.append(block,count);
  }
  if(file.bad())throw Error("io_error","failed reading input document");
  return result;
}

// Final transport text is outside the native account and capped before append.
// Scalar dump temporaries precede that cap; stdout starts after full encoding.
class Writer {
 public:
  explicit Writer(std::size_t limit):limit_(limit) {}
  void raw(std::string_view text) {
    if(text.size()>limit_-text_.size())throw Error("output_limit","output exceeds --max-bytes");
    text_.append(text);
  }
  void text(std::string_view value) {raw(Json(value).dump());}
  void number(std::uint64_t value) {
    char bytes[32];const auto result=std::to_chars(bytes,bytes+sizeof(bytes),value);
    raw({bytes,static_cast<std::size_t>(result.ptr-bytes)});
  }
  void json(const Json& value,unsigned depth=0) {
    if(depth>128)throw Error("resource_limit","JSON nesting exceeds128 levels");
    if(value.is_object()) {
      raw("{");bool first=true;
      for(auto entry=value.begin();entry!=value.end();++entry) {
        if(!first){raw(",");}first=false;text(entry.key());raw(":");json(entry.value(),depth+1);
      }
      raw("}");
    }else if(value.is_array()) {
      raw("[");bool first=true;
      for(const auto& item:value){if(!first){raw(",");}first=false;json(item,depth+1);}
      raw("]");
    }else raw(value.dump());
  }
  void row(storage::TupleValuesView values) {
    raw("[");bool first=true;
    for(const auto& value:values){if(!first){raw(",");}first=false;json(io::write_scalar_view(value));}
    raw("]");
  }
  std::string finish() && {return std::move(text_);}
 private:
  std::size_t limit_;std::string text_;
};
std::string encode(const Json& value,std::size_t limit) {Writer writer(limit);writer.json(value);return std::move(writer).finish();}
// Stdout is a report view; failure here does not revoke durable sink publication.
void emit(std::string_view value) {
  std::cout.write(value.data(),static_cast<std::streamsize>(value.size()));std::cout.put('\n');
  if(!std::cout)throw Error("output_error","cannot write command output; durable results remain in the sink");
}
struct Arguments {
  std::string command;
  std::vector<std::string> positional;
  std::map<std::string,std::string> options;
  explicit Arguments(int argc,char** argv):command(argc>1?argv[1]:"") {
    for(int i=2;i<argc;++i) {
      const std::string key(argv[i]);
      if(!key.starts_with("--")){positional.push_back(key);continue;}
      if(key=="--retire") {
        if(!options.emplace(key,"true").second)throw Error("usage","duplicate option: "+key);
      }else {
        if(i+1>=argc || std::string_view(argv[i+1]).starts_with("--"))throw Error("usage","option requires a value: "+key);
        if(!options.emplace(key,argv[++i]).second)throw Error("usage","duplicate option: "+key);
      }
    }
  }
  std::optional<std::string> take(const std::string& key) {
    const auto found=options.find(key);if(found==options.end())return {};
    auto value=found->second;options.erase(found);return value;
  }
  std::uint64_t number(const std::string& key,std::uint64_t fallback) {const auto value=take(key);return value?integer(*value):fallback;}
  void count(std::size_t minimum,std::size_t maximum) const {
    if(positional.size()<minimum || positional.size()>maximum)throw Error("usage","incorrect arguments; use crown "+command+" --help");
  }
  void finished() const {if(!options.empty())throw Error("usage","unknown or inapplicable option: "+options.begin()->first);}
};
std::size_t output_limit(Arguments& arguments) {
  const auto value=arguments.number("--max-bytes",default_output_limit);
  if(value>document_limit)throw Error("usage","--max-bytes cannot exceed64MiB");
  if(value<2)throw Error("output_limit","--max-bytes cannot hold a JSON object");
  return size(value);
}
void help() {
  std::cout<<
    "usage: crown compile QUERY.sql CATALOG.json [OPTIONS]\n"
    "       crown {explain|validate-plan} compiled ARTIFACT.json [OPTIONS]\n"
    "       crown verify-trace ARTIFACT.json INPUT [--verify-work N --reference-bytes N --verify-events N]\n"
    "       crown {run|restore|snapshot|checkpoint|results|benchmark} ARTIFACT.json INPUT ROOT SINK [OPTIONS]\n"
    "compile: --admission-options FILE --physical-options FILE --search-work N\n"
    "run/restore/benchmark: --events N (optional positional EVENTS is also accepted)\n"
    "run/benchmark: --input-format jsonl|binary --mode delta|maintenance --spool-rows N --spool-bytes N\n"
    "runtime: --memory-limit-bytes N --query-id HEX32 --sink-id HEX32\n"
    "results: --epoch N; checkpoint: --retire\n"
    "new runs: --observe off|counters|timed|trace; benchmark: --run-label TEXT\n"
    "explain compiled: --format text|json|dot|tree-json\n"
    "artifact loading: --proof-work N; reports: --max-bytes N (default16MiB, maximum64MiB)\n"
    "Input is an ordered typed physical stream. New run paths must not exist.\n"
    "Restore validates actual checkpoint/log/sink state and seeks INPUT from its origin.\n"
    "Reports do not acknowledge results: the local sink is the durable output.\n";
}
struct Artifact {
  PhysicalPlan plan;
  Json proof;
  std::optional<planner::VerifiedOptimum> optimum;
};
// Existing set-family admission only; nullable/bag library APIs are separate.
Artifact compile(Arguments& arguments) {
  arguments.count(2,2);
  const auto admission=arguments.take("--admission-options");
  const auto physical=arguments.take("--physical-options");
  planner::SearchLimits search;search.work_limit=arguments.number("--search-work",10'000'000);
  arguments.finished();
  const auto catalog=io::read_catalog(read(arguments.positional[1],16U*1024U*1024U));
  const auto options=admission?io::read_admission_options(read(*admission)):frontend::AdmissionOptions{};
  const auto plan_options=physical?io::read_physical_options(read(*physical)):PhysicalOptions{};
  auto admitted=frontend::admit_sql(read(arguments.positional[0],frontend::ParseLimits{}.source_bytes),catalog,options);
  if(admitted.status!=frontend::AdmissionStatus::admitted) {
    const auto message=admitted.diagnostic?admitted.diagnostic->message:"SQL admission rejected this input";
    throw Error(frontend::admission_status_name(admitted.status),message);
  }
  const auto& normalized=*admitted.program;
  if(admitted.route==frontend::AdmissionRoute::constant_empty)
    return {planner::lower_normalized(normalized,FreeConnexTree{},plan_options),nullptr,{}};
  const auto optimum=planner::minimum_tree(normalized.core_catalog,normalized.core,search);
  if(optimum.status==planner::OracleStatus::resource_limit)throw Error("resource_limit",optimum.reason);
  if(optimum.status!=planner::OracleStatus::proven_minimum || !optimum.tree || !optimum.certificate_verified)
    throw Error("unsupported_plan",optimum.reason);
  return {planner::lower_normalized(normalized,*optimum.tree,plan_options),io::write_oracle(optimum,normalized.core_catalog,normalized.core).at("certificate"),{}};
}
// Reconstruct the plan and independently replay proof; JSON flags are not authority.
Artifact artifact(const std::string& path,std::uint64_t proof_work) {
  const auto data=io::read_json(read(path));
  if(!data.is_object() || data.size()!=3 || !data.contains("schema_version") ||
      !data.at("schema_version").is_number_integer() || data.at("schema_version")!=1 ||
      !data.contains("physical") || !data.contains("height_certificate"))
    throw Error("invalid_artifact","expected a compiled workflow artifact, schema_version1");
  auto plan=io::read_physical(encode(data.at("physical"),document_limit));
  const auto& encoded=data.at("height_certificate");
  if(plan.route()==PhysicalRoute::constant_false) {
    if(!encoded.is_null())throw Error("invalid_height_certificate","constant-empty execution uses its checked empty-operator route");
    return {std::move(plan),nullptr,{}};
  }
  auto claim=io::read_height_certificate(encode(encoded,document_limit),plan.catalog(),plan.query());
  auto replay=planner::CertificateReplay::create(plan.catalog(),plan.query(),std::move(claim));
  static_cast<void>(replay.advance({proof_work,{}}));
  const auto checked=replay.checked();
  if(!checked) {
    if(replay.progress().last_stop==planner::StopReason::invalid_certificate)
      throw Error("invalid_height_certificate","independent height proof replay rejected the artifact");
    throw Error("resource_limit","height proof replay did not complete within --proof-work");
  }
  const auto optimum=checked->optimum();
  if(!optimum || optimum->height()!=plan.validation().native_height ||
      io::write_tree(optimum->upper().tree(),plan.catalog(),plan.query())!=io::write_tree(plan.tree(),plan.catalog(),plan.query()))
    throw Error("invalid_height_certificate","compiled tree differs from the independently checked minimum-height witness");
  return {std::move(plan),encoded,optimum};
}
observability::HeightEvidence evidence(const Artifact& built) {
  if(built.optimum)return *built.optimum;
  return {};
}
std::unique_ptr<std::istream> input(const std::string& path) {
  auto stream=std::make_unique<std::ifstream>(path,std::ios::binary);
  if(!*stream)throw Error("io_error","cannot open update stream");
  return stream;
}
std::array<char,32> identifier(const std::string& text) {
  if(text.size()!=32 || !std::all_of(text.begin(),text.end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');}))
    throw Error("usage","query and sink IDs must be32 lowercase hexadecimal characters");
  std::array<char,32> value{};std::copy(text.begin(),text.end(),value.begin());return value;
}
std::array<char,32> query_id(const CompiledProgram& program) {
  std::array<char,32> value{};std::copy_n(program.physical_source_sha256().begin(),32,value.begin());return value;
}
runtime::SessionLocalSinkOptions sink_options(const CompiledProgram& program) {
  runtime::SessionLocalSinkOptions options;std::copy_n(program.physical_sha256().begin(),32,options.sink_id.begin());return options;
}
// Session commit owns the WAL/native publication barrier, not this stepping loop.
void finish(runtime::QuerySession& session) {while(session.step()!=runtime::DeltaStep::prepared){}session.commit();}
std::uint64_t deliver(runtime::QuerySession& session) {
  std::uint64_t rows=0;
  while(session.local_sink_state().verified_sequence<session.status().committed_sequence) {
    const auto accepted=session.deliver_local_epoch();
    if(accepted.rows>UINT64_MAX-rows)throw Error("counter_overflow","delivered row counter exhausted");
    rows+=accepted.rows;
  }
  return rows;
}
void accumulate(std::uint64_t& total,std::uint64_t amount) {
  if(amount>UINT64_MAX-total)throw Error("counter_overflow","benchmark timing counter exhausted");
  total+=amount;
}
std::uint64_t nanoseconds(std::chrono::steady_clock::time_point begin,std::chrono::steady_clock::time_point end) {
  const auto elapsed=std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
  return elapsed>0?static_cast<std::uint64_t>(elapsed):0;
}
std::string snapshot(runtime::QuerySession& session,std::size_t limit) {
  const auto state=session.snapshot();const auto sink=session.local_sink_state();const auto generation=session.generation_state();
  Writer writer(limit);writer.raw("{\"schema_version\":1,\"committed_sequence\":");writer.number(state.sequence);
  writer.raw(",\"source_positions\":");writer.json(state.progress.source_positions);
  writer.raw(",\"rows\":[");bool first=true;
  for(const auto& row:state.rows){if(!first){writer.raw(",");}first=false;writer.row(row.values());}
  writer.raw("],\"verified_output_sequence\":");writer.number(sink.verified_sequence);
  writer.raw(",\"selected_generation\":");writer.number(generation.selected.generation);
  writer.raw(",\"first_generation\":");writer.number(generation.selected.first_generation);
  writer.raw(",\"delivery_work\":");writer.number(sink.delivery_work);
  writer.raw(",\"sink_bytes\":");writer.number(sink.persisted.bytes);
  writer.raw(",\"memory_requested_bytes\":");writer.number(session.accounted_memory_statistics()->current.requested_bytes);
  writer.raw("}");return std::move(writer).finish();
}
std::string results(runtime::QuerySession& session,std::uint64_t sequence,std::size_t limit) {
  const auto epoch=session.read_local_epoch(sequence);Writer writer(limit);
  writer.raw("{\"schema_version\":1,\"generation\":");writer.number(epoch.generation);
  writer.raw(",\"epoch\":");writer.number(epoch.sequence);
  const auto header=session.local_sink_state().persisted.header;
  writer.raw(",\"query_id\":");writer.text({header.query_id.data(),header.query_id.size()});
  writer.raw(",\"sink_id\":");writer.text({header.sink_id.data(),header.sink_id.size()});
  writer.raw(",\"physical_sha256\":");writer.text({header.binding.physical_sha256.data(),header.binding.physical_sha256.size()});
  writer.raw(",\"rows\":[");bool first=true;
  for(const auto& row:epoch.rows) {
    if(!first){writer.raw(",");}first=false;
    writer.raw("{\"op\":");writer.text(row.operation==SetOperation::insert?"insert":"delete");
    writer.raw(",\"values\":");writer.row(storage::TupleValuesView::borrow(row.values.view()));writer.raw("}");
  }
  writer.raw("]}");return std::move(writer).finish();
}
int workflow(int argc,char** argv) {
  if((argc==3 && std::string_view(argv[2])=="--help") || (argc==4 && std::string_view(argv[1])=="explain" && std::string_view(argv[3])=="--help")){help();return 0;}
  Arguments arguments(argc,argv);const auto limit=output_limit(arguments);
  if(arguments.command=="compile") {
    const auto built=compile(arguments);Writer writer(limit);
    writer.raw("{\"schema_version\":1,\"physical\":");writer.json(io::write_physical(built.plan));
    writer.raw(",\"height_certificate\":");writer.json(built.proof);writer.raw("}");emit(std::move(writer).finish());return 0;
  }
  const auto proof_work=arguments.number("--proof-work",10'000'000);
  if(arguments.command=="verify-trace") {
    arguments.count(2,2);io::InputOptions input_options;
    const auto format=arguments.take("--input-format").value_or("jsonl");
    if(format=="binary")input_options.format=io::InputFormat::binary;
    else if(format!="jsonl")throw Error("usage","verification input format must be jsonl or binary");
    const auto work=arguments.number("--verify-work",10'000'000);
    const auto bytes=arguments.number("--reference-bytes",64U*1024U*1024U);
    const auto events=arguments.number("--verify-events",4096);
    const auto memory=arguments.take("--memory-limit-bytes");
    const auto memory_bytes=memory?std::optional<std::uint64_t>{integer(*memory)}:std::nullopt;
    arguments.finished();const auto built=artifact(arguments.positional[0],proof_work);
    emit(crown::cli::verify_workflow_trace(built.plan,arguments.positional[1],input_options,memory_bytes,work,bytes,events,limit));return 0;
  }
  if(arguments.command=="validate-plan") {
    arguments.count(2,2);if(arguments.positional[0]!="compiled")throw Error("usage","expected validate-plan compiled ARTIFACT.json");
    arguments.finished();const auto built=artifact(arguments.positional[1],proof_work);
    emit(encode({{"schema_version",1},{"physical_valid",true},{"physical_sha256",built.plan.physical_sha256()},
      {"source_sha256",built.plan.physical_source_sha256()},{"selected_native_height",built.plan.validation().native_height},
      {"height_status",built.plan.route()==PhysicalRoute::tree?"proven_minimum":"checked_constant_operator"}},limit));return 0;
  }
  if(arguments.command=="explain") {
    arguments.count(2,2);if(arguments.positional[0]!="compiled")throw Error("usage","expected explain compiled ARTIFACT.json");
    const auto format=arguments.take("--format").value_or("text");
    if(format!="text" && format!="json" && format!="dot" && format!="tree-json")throw Error("usage","unknown EXPLAIN format");
    arguments.finished();const auto built=artifact(arguments.positional[1],proof_work);
    const auto report=observability::PlanExplanation::create(built.plan,evidence(built));const io::ExplainTextLimits bytes{limit};
    if(format=="json")emit(io::write_explain_json(report,bytes));
    else if(format=="dot")emit(io::write_explain_dot(report,bytes));
    else if(format=="tree-json")emit(io::write_explain_tree_json(report,bytes));
    else emit(io::write_explain_text(report,bytes));
    return 0;
  }
  const bool running=arguments.command=="run" || arguments.command=="restore" || arguments.command=="benchmark";
  const bool creating=arguments.command=="run" || arguments.command=="benchmark";
  const bool reading=arguments.command=="results";
  arguments.count(4,(running || reading)?5:4);
  const auto extra=(reading || running)?arguments.take(reading?"--epoch":"--events"):std::nullopt;
  if(extra && arguments.positional.size()==5)throw Error("usage","specify an event count or epoch once");
  const auto numeric=extra?integer(*extra):arguments.positional.size()==5?integer(arguments.positional[4]):std::numeric_limits<std::uint64_t>::max();
  if(reading && (!extra && arguments.positional.size()!=5))throw Error("usage","results requires --epoch N");
  if(reading && numeric==0)throw Error("usage","physical output epochs start at1");
  const auto memory=arguments.take("--memory-limit-bytes");const auto memory_bytes=memory?std::optional<std::uint64_t>{integer(*memory)}:std::nullopt;
  runtime::SessionOptions session_options;
  if(creating) {
    const auto format=arguments.take("--input-format").value_or("jsonl");
    if(format=="binary")session_options.input.format=io::InputFormat::binary;
    else if(format!="jsonl")throw Error("usage","workflow input format must be jsonl or binary");
    const auto mode=arguments.take("--mode").value_or("delta");
    if(mode=="maintenance")session_options.delta.mode=runtime::DeltaMode::maintenance;
    else if(mode!="delta")throw Error("usage","unknown execution mode");
    session_options.delta.spool_row_limit=size(arguments.number("--spool-rows",session_options.delta.spool_row_limit));
    session_options.delta.spool_byte_limit=size(arguments.number("--spool-bytes",session_options.delta.spool_byte_limit));
    const auto observe=arguments.take("--observe").value_or("timed");
    auto& observation=session_options.delta.physical.support.observation.mode;
    if(observe=="off")observation=runtime::ObservationMode::off;
    else if(observe=="counters")observation=runtime::ObservationMode::counters;
    else if(observe=="timed")observation=runtime::ObservationMode::timed;
    else if(observe=="trace")observation=runtime::ObservationMode::trace;
    else throw Error("usage","unknown observation mode");
    if(arguments.command=="benchmark") {
      runtime::BenchmarkLabels labels;
      labels.run=arguments.take("--run-label").value_or("cli-durable-native");
      labels.input_adapter=format;labels.output_codec="CROWNSK1";labels.sink="durable_local_file";
      session_options.declared_benchmark=std::make_shared<const runtime::DeclaredBenchmarkContext>(std::move(labels));
    }
    if(memory_bytes)session_options.delta.physical.support.memory_limit_bytes=*memory_bytes;
  }
  const auto query_override=arguments.take("--query-id"),sink_override=arguments.take("--sink-id");
  const auto requested_query=query_override?identifier(*query_override):std::array<char,32>{};
  const auto requested_sink=sink_override?identifier(*sink_override):std::array<char,32>{};
  const bool retire=arguments.command=="checkpoint" && arguments.take("--retire").has_value();
  arguments.finished();
  const auto admission_begin=std::chrono::steady_clock::now();
  const auto built=artifact(arguments.positional[0],proof_work);auto program=CompiledProgram::standalone(built.plan);auto sink=sink_options(program);
  auto expected_query=query_id(program);if(query_override)expected_query=requested_query;if(sink_override)sink.sink_id=requested_sink;
  // All options/proof/labels are admitted before native file operations. A later
  // failure can leave published or uncertain files; restore checks their authority.
  runtime::QuerySession::Owner session;
  if(creating) {
    session=runtime::QuerySession::create(program,input(arguments.positional[1]),session_options);
    runtime::SessionGenerationOptions options;options.journal.query_id=expected_query;
    session->enable_generation(arguments.positional[2],options);session->create_local_sink(arguments.positional[3],sink);
  }else {
    runtime::SessionGenerationRecoveryOptions options;options.replay.journal.query_id=expected_query;
    options.replay.seek_source_from_origin=true;options.replay.memory_limit_bytes=memory_bytes;
    session=runtime::QuerySession::restore_generation_with_local_sink(program,arguments.positional[2],options,arguments.positional[3],sink,input(arguments.positional[1]));
  }
  const auto ready=std::chrono::steady_clock::now();
  std::uint64_t processed=0,delivered_rows=0,input_ns=0,native_ns=0,delivery_ns=0;
  if(running) {
    const auto first_delivery=std::chrono::steady_clock::now();
    delivered_rows=deliver(*session);delivery_ns=nanoseconds(first_delivery,std::chrono::steady_clock::now());session->start();
    for(std::uint64_t i=0;i<numeric;++i) {
      const auto begin=std::chrono::steady_clock::now();
      const auto next=session->begin_next_result();const auto prepared_at=std::chrono::steady_clock::now();
      accumulate(input_ns,nanoseconds(begin,prepared_at));
      if(next==runtime::SessionBegin::end)break;
      if(next!=runtime::SessionBegin::pending)throw Error("would_block","input admission blocked");
      finish(*session);const auto committed_at=std::chrono::steady_clock::now();accumulate(native_ns,nanoseconds(prepared_at,committed_at));
      const auto rows=deliver(*session);accumulate(delivery_ns,nanoseconds(committed_at,std::chrono::steady_clock::now()));
      if(rows>UINT64_MAX-delivered_rows)throw Error("counter_overflow","delivered row counter exhausted");
      delivered_rows+=rows;++processed;
    }
  }else if(arguments.command=="checkpoint") {
    deliver(*session);
    if(session->recovery_status().pending_input_sequence) {
      session->start();if(!session->begin_next())throw Error("pending_input","logged input missing");
      finish(*session);deliver(*session);session->pause();
    }
    session->rotate_generation();if(retire)session->retire_generation_history();
  }else if(reading){emit(results(*session,numeric,limit));return 0;}
  const auto completed=std::chrono::steady_clock::now();
  if(arguments.command=="benchmark") {
    const auto report=observability::PlanExplanation::capture(*session,evidence(built));
    // Reporting is after completed: capture, JSON parse and nested copies are untimed.
    const auto engine=Json::parse(io::write_explain_json(report,io::ExplainTextLimits{limit}));
    const auto receipt=session->local_sink_receipt();
    Writer writer(limit);writer.raw("{\"schema_version\":1,\"benchmark_scope\":\"single_process_native_durable_file_run\",\"records\":");writer.number(processed);
    writer.raw(",\"delivered_rows\":");writer.number(delivered_rows);
    writer.raw(",\"initialization_ns\":");writer.number(nanoseconds(admission_begin,ready));
    writer.raw(",\"processing_ns\":");writer.number(nanoseconds(ready,completed));
    writer.raw(",\"timing_scope\":\"initialization includes artifact proof/native admission/checkpoint/log/sink creation; processing includes input/native epochs/WAL and sink synchronization; reporting excluded\"");
    writer.raw(",\"final\":");writer.raw(snapshot(*session,limit));
    writer.raw(",\"input_begin_ns\":");writer.number(input_ns);
    writer.raw(",\"native_prepare_commit_ns\":");writer.number(native_ns);
    writer.raw(",\"delivery_ns\":");writer.number(delivery_ns);
    writer.raw(",\"runtime\":");writer.json(engine.at("mode").at("runtime"));
    writer.raw(",\"backend\":");writer.json(engine.at("mode").at("backend"));
    writer.raw(",\"identity\":");writer.json(engine.at("identity"));
    writer.raw(",\"height_evidence\":");writer.json(engine.at("height_evidence"));
    writer.raw(",\"metrics\":");writer.json(engine.at("observations"));
    writer.raw(",\"run_context\":");writer.json(engine.at("run_context"));
    writer.raw(",\"cursor\":");writer.json(engine.at("cursor"));
    writer.raw(",\"committed_gauges\":");writer.json(engine.at("committed_gauges"));
    writer.raw(",\"delivery\":{\"kind\":\"durable_local_file\",\"verified_sequence\":");writer.number(receipt.sequence());
    writer.raw(",\"generation\":");writer.number(receipt.generation());writer.raw(",\"bytes\":");writer.number(receipt.bytes());
    const auto digest=receipt.content_sha256();writer.raw(",\"prefix_sha256\":");writer.text({digest.data(),digest.size()});writer.raw("}}");
    emit(std::move(writer).finish());return 0;
  }
  emit(snapshot(*session,limit));return 0;
}
void diagnostic(std::string_view code,std::string_view message,const Json& details=nullptr) {
  Json result{{"schema_version",1},{"error",code},{"message",message}};
  if(!details.is_null())result["details"]=details;
  std::cerr<<result.dump()<<'\n';
}
// Preserve typed fault/stage/outcome; a diagnostic never authorizes blind retry.
template<class Failure> void file_diagnostic(std::string_view code,const Failure& error) {
  const auto outcome=static_cast<unsigned>(error.outcome());
  const char* names[]={"unchanged","unknown","durable"};
  diagnostic(code,error.what(),{{"fault",static_cast<unsigned>(error.fault())},
    {"stage",static_cast<unsigned>(error.stage())},{"outcome",outcome<3?names[outcome]:"unknown"},
    {"native_error",error.native_error()},{"cleanup_failed",error.temporary_cleanup_failed()}});
}
} // namespace
int crown::cli::workflow_main(int argc,char** argv) {
  try{return workflow(argc,argv);}
  catch(const Error& error){diagnostic(error.code(),error.what());}
  catch(const Json::exception& error){diagnostic(error.id==316?"output_encoding":"invalid_document",error.what());}
  catch(const resource::MemoryFailure& error){diagnostic("resource_limit",error.what());}
  catch(const recovery::ImageFailure& error){diagnostic(error.fault()==recovery::ImageFault::limit || error.fault()==recovery::ImageFault::work?"resource_limit":"checkpoint_invalid",error.what());}
  catch(const recovery::FileFailure& error){
    const char* states[]={"not_published","unknown","published_unsynced","durable"};
    const auto state=static_cast<unsigned>(error.publication());
    diagnostic(error.fault()==recovery::FileFault::limit?"resource_limit":"checkpoint_failed",error.what(),
      {{"fault",static_cast<unsigned>(error.fault())},{"stage",static_cast<unsigned>(error.stage())},
       {"publication",state<4?states[state]:"unknown"},{"native_error",error.native_error()},
       {"cleanup_failed",error.temporary_cleanup_failed()}});
  }
  catch(const recovery::GenerationFailure& error){file_diagnostic(error.fault()==recovery::GenerationFault::limit?"resource_limit":"generation_failed",error);}
  catch(const recovery::journal::FileFailure& error){file_diagnostic(error.fault()==recovery::journal::FileFault::limit?"resource_limit":"journal_failed",error);}
  catch(const recovery::sink::Failure& error){file_diagnostic(error.fault()==recovery::sink::Fault::limit?"resource_limit":"sink_failed",error);}
  catch(const runtime::SessionJournalFailure& error){diagnostic("recovery_failed",error.what());}
  catch(const std::bad_alloc&){diagnostic("resource_limit","allocation failed");}
  catch(const std::exception& error){diagnostic("workflow_failure",error.what());}
  return 1;
}

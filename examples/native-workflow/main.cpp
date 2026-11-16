#include <crown/version.hpp>
#include <crown/api/error.hpp>
#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/document.hpp>
#include <crown/io/explain.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/session_generation.hpp>
#include <crown/runtime/session_local_sink.hpp>
#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>

namespace {
using namespace crown;
std::string read(const char* path,std::size_t limit) {
  std::ifstream file(path,std::ios::binary);if(!file)throw Error("io_error","cannot open input document");
  std::string result;char block[4096];
  while(file){file.read(block,sizeof(block));const auto bytes=static_cast<std::size_t>(file.gcount());if(bytes>limit-result.size())throw Error("resource_limit","example document limit exceeded");result.append(block,bytes);}
  if(file.bad())throw Error("io_error","cannot read input document");
  return result;
}
std::unique_ptr<std::istream> input(const char* path) {
  auto result=std::make_unique<std::ifstream>(path,std::ios::binary);
  if(!*result)throw Error("io_error","cannot open input stream");
  return result;
}
void deliver(runtime::QuerySession& session) {
  while(session.local_sink_state().verified_sequence<session.status().committed_sequence)static_cast<void>(session.deliver_local_epoch());
}
}
int main(int argc,char** argv) {
  using namespace crown;
  try {
    if(argc!=8 || (std::string_view(argv[1])!="run" && std::string_view(argv[1])!="restore"))
      throw Error("usage","run|restore QUERY.sql CATALOG.json INPUT.jsonl ROOT SINK EVENTS");
    const std::string_view count(argv[7]);std::uint64_t events=0;
    const auto parsed=std::from_chars(count.data(),count.data()+count.size(),events);
    if(parsed.ec!=std::errc{} || parsed.ptr!=count.data()+count.size())throw Error("usage","EVENTS must be unsigned");
    const auto catalog=io::read_catalog(read(argv[3],16U*1024U*1024U));
    auto admitted=frontend::admit_sql(read(argv[2],frontend::ParseLimits{}.source_bytes),catalog);
    if(admitted.status!=frontend::AdmissionStatus::admitted)throw Error("sql_rejected","query was not admitted");
    // Nonconstant queries need the actual proved witness; unfinished inputs stop here.
    auto plan=[&] {
      if(admitted.route==frontend::AdmissionRoute::constant_empty)return planner::lower_normalized(*admitted.program,FreeConnexTree{});
      const auto minimum=planner::minimum_tree(admitted.program->core_catalog,admitted.program->core);
      if(minimum.status!=planner::OracleStatus::proven_minimum || !minimum.tree)throw Error("resource_limit","minimum height was not proved");
      return planner::lower_normalized(*admitted.program,*minimum.tree);
    }();
    // These fixed IDs copy digest text prefixes; native recovery still checks full bindings.
    auto program=CompiledProgram::standalone(plan);std::array<char,32> query{};
    std::copy_n(program.physical_source_sha256().begin(),32,query.begin());
    runtime::SessionLocalSinkOptions sink;std::copy_n(program.physical_sha256().begin(),32,sink.sink_id.begin());
    runtime::QuerySession::Owner session;
    if(std::string_view(argv[1])=="run") {
      session=runtime::QuerySession::create(program,input(argv[4]));runtime::SessionGenerationOptions options;options.journal.query_id=query;
      session->enable_generation(argv[5],options);session->create_local_sink(argv[6],sink);
    }else {
      runtime::SessionGenerationRecoveryOptions options;options.replay.journal.query_id=query;options.replay.seek_source_from_origin=true;
      session=runtime::QuerySession::restore_generation_with_local_sink(program,argv[5],options,argv[6],sink,input(argv[4]));
    }
    // Recovered whole epochs must reach the sink before any new input starts.
    deliver(*session);session->start();
    for(std::uint64_t i=0;i<events;++i) {
      if(!session->begin_next())break;
      while(session->step()!=runtime::DeltaStep::prepared){}session->commit();deliver(*session);
    }
    // Rotation selects durable checkpoint/WAL state; later report failures do not undo it.
    session->pause();if(!session->status().end_of_input)session->rotate_generation();
    const auto state=session->snapshot();auto rows=io::Json::array();
    for(const auto& tuple:state.rows) {
      auto row=io::Json::array();for(const auto& value:tuple.values())row.push_back(io::write_scalar_view(value));rows.push_back(std::move(row));
    }
    const auto report=io::Json::parse(io::write_explain_json(observability::PlanExplanation::capture(*session)));
    io::Json result{{"schema_version",1},{"public_api_version",public_api_version},{"sequence",state.sequence},
      {"source_positions",state.progress.source_positions},{"rows",std::move(rows)},
      {"verified_output_sequence",session->local_sink_receipt().sequence()},
      {"runtime",report.at("mode").at("runtime")},{"metrics",report.at("observations")}};
    const auto encoded=result.dump();if(encoded.size()>16U*1024U*1024U)throw Error("resource_limit","example report exceeds16MiB");
    std::cout<<encoded<<'\n';std::cout.flush();return std::cout?0:1;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

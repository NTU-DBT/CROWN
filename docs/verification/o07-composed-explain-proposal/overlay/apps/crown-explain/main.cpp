#include "crown/io/explain.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/document.hpp"
#include "crown/io/oracle.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
namespace {
using namespace crown;
std::string read(const std::string& path){
  std::ifstream input(path,std::ios::binary);if(!input)throw Error("io_error","cannot open artifact");
  constexpr std::size_t limit=16*1024*1024;std::string result;char buffer[4096];
  while(input){input.read(buffer,sizeof(buffer));const auto count=static_cast<std::size_t>(input.gcount());if(count>limit-result.size())throw Error("resource_limit","artifact exceeds 16 MiB");result.append(buffer,count);}
  if(!input.eof())throw Error("io_error","cannot read artifact");
  return result;
}
std::uint64_t integer(std::string_view text){std::uint64_t value=0;const auto p=std::from_chars(text.data(),text.data()+text.size(),value);if(p.ec!=std::errc{} || p.ptr!=text.data()+text.size())throw Error("usage","expected unsigned integer");return value;}
struct Arguments {
  std::string command,path,format="text";
  io::ExplainTextLimits text;
  std::map<std::string,std::string> values;
  Arguments(int argc,char** argv){
    if(argc<3)throw Error("usage","expected command and input path");
    command=argv[1];path=argv[2];
    for(int i=3;i<argc;i+=2){if(i+1>=argc)throw Error("usage","options require values");if(!values.emplace(argv[i],argv[i+1]).second)throw Error("usage","duplicate option");}
    if(auto v=take("--format"))format=*v;
    if(format!="json" && format!="text" && format!="dot" && format!="tree-json")throw Error("usage","unknown format");
    if(auto v=take("--max-bytes"))text.bytes=static_cast<std::size_t>(integer(*v));
  }
  std::optional<std::string> take(const std::string& key){const auto it=values.find(key);if(it==values.end())return {};auto value=it->second;values.erase(it);return value;}
  std::uint64_t number(const std::string& key,std::uint64_t fallback){auto v=take(key);return v?integer(*v):fallback;}
  void finished() const {if(!values.empty())throw Error("usage","unknown or inapplicable option");}
};
template<class Report>std::string encode(const Report& report,const Arguments& a){
 if(a.format=="json")return io::write_explain_json(report,a.text);
 if(a.format=="dot")return io::write_explain_dot(report,a.text);
 if(a.format=="tree-json")return io::write_explain_tree_json(report,a.text);
 return io::write_explain_text(report,a.text);
}
runtime::DeltaOptions delta_options(Arguments& a){
 runtime::DeltaOptions o;
 if(auto v=a.take("--mode")){if(*v=="maintenance")o.mode=runtime::DeltaMode::maintenance;else if(*v!="delta")throw Error("usage","unknown delta mode");}
 if(auto v=a.take("--observe")){auto& m=o.physical.support.observation.mode;if(*v=="off")m=runtime::ObservationMode::off;else if(*v=="counters")m=runtime::ObservationMode::counters;else if(*v=="timed")m=runtime::ObservationMode::timed;else if(*v=="trace")m=runtime::ObservationMode::trace;else throw Error("usage","unknown observation mode");}
 if(auto v=a.take("--live")){if(*v=="on_output")o.live_maintenance=runtime::LiveMaintenance::on_output;else if(*v=="incremental")o.live_maintenance=runtime::LiveMaintenance::incremental;else if(*v=="eager")o.live_maintenance=runtime::LiveMaintenance::eager;else throw Error("usage","unknown live mode");}
 if(auto v=a.take("--completion")){if(*v=="automatic")o.completion=runtime::DeltaCompletion::automatic;else if(*v=="ordered_replay")o.completion=runtime::DeltaCompletion::ordered_replay;else if(*v=="anchored")o.completion=runtime::DeltaCompletion::anchored;else if(*v=="root_first")o.completion=runtime::DeltaCompletion::root_first;else throw Error("usage","unknown completion mode");}
 if(auto v=a.take("--view")){if(*v=="core")o.view=runtime::ResultView::core;else if(*v=="sql")o.view=runtime::ResultView::sql;else throw Error("usage","unknown result view");}
 if(auto v=a.take("--work-limit"))o.work_limit=integer(*v);
 if(auto v=a.take("--spool-rows"))o.spool_row_limit=static_cast<std::size_t>(integer(*v));
 return o;
}
std::shared_ptr<const runtime::DeclaredBenchmarkContext> labels(Arguments& a){
 runtime::BenchmarkLabels v;v.run=a.take("--run-label");v.input_adapter=a.take("--adapter-label");v.output_codec=a.take("--codec-label");v.sink=a.take("--sink-label");
 if(!v.run && !v.input_adapter && !v.output_codec && !v.sink)return {};
 return std::make_shared<const runtime::DeclaredBenchmarkContext>(std::move(v));
}
observability::HeightEvidence evidence(Arguments& a,const PhysicalPlan& plan){
 auto file=a.take("--certificate");const auto budget=a.number("--proof-work",10000000);
 if(!file)return {};
 auto claim=io::read_height_certificate(read(*file),plan.catalog(),plan.query());
 auto replay=planner::CertificateReplay::create(plan.catalog(),plan.query(),std::move(claim));
 // Explicit CLI proof operation, never hidden inside capture/export.
 static_cast<void>(replay.advance({budget,{}}));
 const auto checked=replay.checked();if(!checked || !checked->optimum())throw Error("certificate_replay","checked optimum was not established within the explicit proof quantum");
 return *checked->optimum();
}
std::string run(Arguments& a){
 if(a.command=="query" || a.command=="progress" || a.command=="replay"){
  auto doc=io::read_document(read(a.path));const auto quantum=a.number("--work",0);
  if(a.command=="replay"){
   const auto file=a.take("--certificate");if(!file)throw Error("usage","replay needs a certificate");a.finished();
   auto claim=io::read_height_certificate(read(*file),doc.catalog,doc.query);
   auto owner=planner::CertificateReplay::create(std::move(doc.catalog),std::move(doc.query),std::move(claim));
   if(quantum)static_cast<void>(owner.advance({quantum,{}}));
   return encode(observability::QueryExplanation::capture(owner),a);
  }
  planner::SearchOptions options;if(auto v=a.take("--height-policy")){if(*v=="best-found")options.policy=planner::SearchPolicy::best_found;else if(*v!="strict")throw Error("usage","unknown height policy");}a.finished();
  auto owner=planner::ExactSearch::create(std::move(doc.catalog),std::move(doc.query),options);
  if(quantum)static_cast<void>(owner.advance({quantum,{}}));
  return encode(observability::QueryExplanation::capture(owner),a);
 }
 if(a.command!="physical" && a.command!="runtime" && a.command!="session")throw Error("usage","unknown command");
 auto plan=io::read_physical(read(a.path));auto proof=evidence(a,plan);
 if(a.command=="physical"){a.finished();return encode(observability::PlanExplanation::create(std::move(plan),std::move(proof)),a);}
 auto options=delta_options(a);auto declared=labels(a);
 if(a.command=="runtime"){a.finished();runtime::DeltaRuntime owner(std::move(plan),options);owner.declare_benchmark_context(std::move(declared));return encode(observability::PlanExplanation::capture(owner,std::move(proof)),a);}
 runtime::SessionOptions session_options;session_options.delta=options;session_options.declared_benchmark=std::move(declared);
 if(auto v=a.take("--input-format")){if(*v=="jsonl")session_options.input.format=io::InputFormat::jsonl;else if(*v=="binary")session_options.input.format=io::InputFormat::binary;else throw Error("usage","CLI stream supports jsonl or binary");}
 const auto file=a.take("--input");const auto events=a.number("--events",0);const auto steps_text=a.take("--steps");const auto steps=steps_text?std::optional<std::uint64_t>{integer(*steps_text)}:std::nullopt;
 const auto consume=a.take("--consume").value_or("discard");if(consume!="discard" && consume!="transfer" && consume!="retain")throw Error("usage","unknown output disposition");
 const auto lifecycle=a.take("--lifecycle").value_or("preserve");if(lifecycle!="preserve" && lifecycle!="stop" && lifecycle!="drop")throw Error("usage","unknown session lifecycle");a.finished();
 std::unique_ptr<std::istream> input;
 if(file){auto stream=std::make_unique<std::ifstream>(*file,std::ios::binary);if(!*stream)throw Error("io_error","cannot open input stream");input=std::move(stream);}else input=std::make_unique<std::istringstream>();
 auto owner=runtime::QuerySession::create(std::move(plan),std::move(input),session_options);
 if(events){owner->start();std::uint64_t completed_steps=0;
  for(std::uint64_t event=0;event<events;++event){if(owner->begin_next_result()!=runtime::SessionBegin::pending)break;
   if(consume=="discard")owner->start_drain();
   bool prepared=false;
   while(!steps || completed_steps<*steps){const auto step=owner->step();++completed_steps;if(step==runtime::DeltaStep::prepared){prepared=true;break;}}
   if(!prepared)break;
   owner->commit();
   if(consume=="transfer")while(owner->next_output()){}
   if(consume=="retain" && owner->status().output_remaining)break;
  }
 }
 if(lifecycle=="stop")owner->stop();else if(lifecycle=="drop")owner->drop();
 return encode(observability::PlanExplanation::capture(*owner,std::move(proof)),a);
}
} // namespace
int main(int argc,char** argv){
 try{Arguments args(argc,argv);const auto result=run(args);std::cout.write(result.data(),static_cast<std::streamsize>(result.size()));if(!std::cout)throw crown::Error("io_error","output failed");return 0;}
 catch(const crown::Error& e){std::cerr<<"error: ";for(char ch:e.code())std::cerr.put((ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||ch=='_'?ch:'?');std::cerr.put('\n');return e.code()=="usage"?2:e.code()=="text_encoding"?3:e.code()=="resource_limit"?4:1;}
 catch(const std::bad_alloc&){std::cerr<<"error: resource_limit\n";return 4;}catch(const std::exception&){std::cerr<<"error: invalid_document\n";return 1;}
}

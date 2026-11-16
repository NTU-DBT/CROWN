#include "crown/io/explain.hpp"
#include "crown/io/physical.hpp"
#include "crown/io/oracle.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <fstream>
#include <iostream>
#include <optional>

namespace {
std::string read(const std::string& path) {
  constexpr std::size_t limit=16*1024*1024;
  std::ifstream stream(path,std::ios::binary);
  if (!stream) throw crown::Error("io_error","cannot open input artifact");
  std::string result; char buffer[4096];
  while (stream) {
    stream.read(buffer,sizeof(buffer)); const auto count=static_cast<std::size_t>(stream.gcount());
    if (count>limit-result.size()) throw crown::Error("resource_limit","input artifact exceeds 16 MiB");
    result.append(buffer,count);
  }
  if (!stream.eof()) throw crown::Error("io_error","cannot read complete input artifact");
  return result;
}
std::size_t size(std::string_view value) {
  std::size_t result=0; const auto parsed=std::from_chars(value.data(),value.data()+value.size(),result);
  if (parsed.ec!=std::errc{} || parsed.ptr!=value.data()+value.size()) throw crown::Error("usage","invalid --max-bytes");
  return result;
}
}
int main(int argc,char** argv) {
  try {
    if (argc<2) throw crown::Error("usage","crown-explain-proposal PLAN.json [--format text|json|dot] [--certificate FILE] [--max-bytes N]");
    std::string format="text"; std::optional<std::string> certificate; crown::io::ExplainTextLimits limits;
    for (int i=2;i<argc;i+=2) {
      if (i+1>=argc) throw crown::Error("usage","every option needs one value");
      const std::string_view key=argv[i];
      if (key=="--format") format=argv[i+1];
      else if (key=="--certificate") certificate=argv[i+1];
      else if (key=="--max-bytes") limits.bytes=size(argv[i+1]);
      else throw crown::Error("usage","unknown option");
    }
    if (format!="text" && format!="json" && format!="dot") throw crown::Error("usage","unknown output format");
    auto plan=crown::io::read_physical(read(argv[1]));
    crown::observability::HeightEvidence evidence;
    if (certificate) {
      auto claims=crown::io::read_height_certificate(read(*certificate),plan.catalog(),plan.query());
      auto replay=crown::planner::CertificateReplay::create(plan.catalog(),plan.query(),std::move(claims));
      while (!replay.checked()) {
        const auto step=replay.advance({100000,{}});
        if (step.stopped_for!=crown::planner::StopReason::quantum_work && step.stopped_for!=crown::planner::StopReason::quantum_time &&
            step.stopped_for!=crown::planner::StopReason::complete)
          throw crown::Error("certificate_replay","independent replay did not establish checked authority within its resource limits");
      }
      auto proof=replay.checked()->optimum();
      if (!proof) throw crown::Error("explain_evidence","infeasibility proof cannot certify an executable physical plan");
      evidence=std::move(*proof);
    }
    const auto report=crown::observability::PlanExplanation::create(std::move(plan),std::move(evidence));
    const auto result=format=="json"?crown::io::write_explain_json(report,limits):
        format=="dot"?crown::io::write_explain_dot(report,limits):crown::io::write_explain_text(report,limits);
    std::cout.write(result.data(),static_cast<std::streamsize>(result.size()));
    if (!std::cout) throw crown::Error("io_error","report output failed");
    return 0;
  } catch (const crown::Error& error) {
    // Do not echo untrusted native diagnostics or query bytes into a terminal.
    std::cerr << "error: ";
    for (const char ch:error.code()) {
      const bool safe=(ch>='a' && ch<='z') || (ch>='0' && ch<='9') || ch=='_';
      std::cerr.put(safe?ch:'?');
    }
    std::cerr.put('\n');
    return error.code()=="usage"?2:error.code()=="text_encoding"?3:error.code()=="resource_limit"?4:1;
  } catch (const std::bad_alloc&) {
    std::cerr << "resource_limit: report allocation failed\n"; return 4;
  } catch (const std::exception&) {
    std::cerr << "invalid_document: artifact processing failed\n"; return 1;
  }
}

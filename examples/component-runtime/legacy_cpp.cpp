#include "component_request.hpp"
#include "crown_line5cd.h"
#include "crown_line5gc.h"
#include <iostream>
#include <memory>
#include <sstream>

namespace {
using namespace component;

// Template ownership keeps the published concrete destructor. CrownBase has no
// virtual destructor and must never be the deleting type. Calls still execute
// the unchanged, separately linked published process()/milestone() definitions.
template<class Factory>
Json passes(const Request& request, const std::vector<std::string>& lines, Factory create) {
  auto output_passes = Json::array();
  for (std::size_t pass=0; pass<request.warmups+request.repetitions; ++pass) {
    const auto initializing = Clock::now();
    TextSink sink(request.verify,request.max_bytes);
    std::ostream output(&sink);
    output.exceptions(std::ios::badbit | std::ios::failbit);
    auto owner = create(output);
    const auto initialize_ns = elapsed(initializing,Clock::now());
    auto epochs = Json::array();
    const auto looping = Clock::now();
    for (std::size_t i=0; i<lines.size(); ++i) {
      sink.next_frame(); const auto previous_records = sink.records, previous_bytes = sink.bytes;
      const auto applying = Clock::now();
      owner->process(lines[i]); // Intrinsic stringstream/stoul and delta formatting remain here.
      const auto apply_ns = elapsed(applying,Clock::now());
      const auto observing = Clock::now();
      owner->milestone(); // Full-mode formatting is genuine published observation work.
      const auto output_ns = elapsed(observing,Clock::now());
      require(output.good(),"legacy component output failed");
      require(sink.records <= request.max_records,"component output-record limit exceeded");
      epochs.push_back({{"sequence",i+1}, {"phase",request.events[i].phase},
          {"apply_ns",time_value(request,apply_ns)}, {"output_ns",time_value(request,output_ns)},
          {"release_ns",nullptr}, {"output_records",sink.records-previous_records},
          {"intrinsic_text_bytes",sink.bytes-previous_bytes},
          {"actual",request.verify ? Json{{"raw_output",sink.frame()}} : Json{}}});
    }
    const auto loop_ns = elapsed(looping,Clock::now());
    const auto destroying = Clock::now(); owner.reset();
    const auto teardown_ns = elapsed(destroying,Clock::now());
    output.flush(); require(output.good(),"legacy component output flush failed");
    output_passes.push_back({{"warmup",pass < request.warmups},
        {"initialize_ns",time_value(request,initialize_ns)}, {"loop_wall_ns",time_value(request,loop_ns)},
        {"teardown_ns",time_value(request,teardown_ns)}, {"output_records",sink.records},
        {"intrinsic_text_bytes",sink.bytes}, {"native_memory_before_teardown",nullptr},
        {"epochs",std::move(epochs)}});
  }
  return output_passes;
}

int run(int argc, char** argv) {
  const auto reading = Clock::now();
  const auto request = read_request(argc,argv);
  const auto read_ns = elapsed(reading,Clock::now());
  const auto admitting = Clock::now();
  const auto family = request.document.at("query_family").get<std::string>();
  const auto mode = request.document.at("output").get<std::string>();
  require((family == "l5_distinct_count" && mode == "cardinality") ||
      (family == "l5_group_count" && (mode == "groups_full" || mode == "groups_replacements")),
      "unsupported fixed legacy query/output pair");
  std::vector<std::string> lines; lines.reserve(request.events.size());
  for (const auto& event : request.events) {
    require(event.table == "graph","legacy graph input must name graph");
    require(family != "l5_distinct_count" || event.operation == "+","line5cd deletes are unqualified");
    for (const auto value : event.values)
      require(value > 0 && static_cast<U64>(value) <= UINT32_MAX,"legacy graph IDs must be positive uint32");
    lines.push_back(event.operation + "|" + std::to_string(event.values[0]) + "|" + std::to_string(event.values[1]));
  }
  const auto admission_ns = elapsed(admitting,Clock::now());
  Json output_passes;
  if (family == "l5_distinct_count")
    output_passes = passes(request,lines,[](std::ostream& output) {
      return std::make_unique<CrownLine5cd>(output,true);
    });
  else output_passes = passes(request,lines,[&](std::ostream& output) {
    return std::make_unique<CrownLine5gc>(output,true,mode == "groups_replacements");
  });
  Json report{{"schema_version",1}, {"implementation","legacy_cpp_local_api"},
      {"case_id",request.document.at("case_id")}, {"query_family",family},
      {"command",request.document.at("command")}, {"output",mode},
      {"read_request_ns",time_value(request,read_ns)}, {"input_admission_ns",time_value(request,admission_ns)},
      {"shared_program_ns",nullptr}, {"passes",std::move(output_passes)},
      {"scope","local API adapter over immutable published classes/archives, not original CLI timing; fixed query selected by query_family, SQL is manifest metadata; one process then milestone per physical event; intrinsic parsing/formatting included; main's timing/VmPeak/FD probe omitted; fresh logical owner per pass; allocator/process state may persist; no native account or pure-dispatch claim"}};
  std::cout << report.dump() << '\n'; std::cout.flush();
  return std::cout ? 0 : 1;
}
}  // namespace
int main(int argc, char** argv) {
  try { return run(argc,argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

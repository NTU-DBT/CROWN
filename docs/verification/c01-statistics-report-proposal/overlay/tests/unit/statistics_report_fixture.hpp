#pragma once
#include "combined_statistics_fixture.hpp"
#include "crown/io/statistics_explain.hpp"
#include "crown/io/explain.hpp"
#include <filesystem>
#include <fstream>

namespace report_fixture {
using namespace combined_fixture;
using Report=observability::StatisticsExplanation;
using Capture=observability::StatisticsCaptureOptions;
inline Capture requested(const PhysicalPlan& value){Capture options;options.state=request(value);return options;}
inline void write(const std::filesystem::path& path,const std::string& value){std::ofstream out(path,std::ios::binary);out<<value;check(bool(out));}
inline Report emit(const std::filesystem::path& dir,const char* label,Report report){
  write(dir/(std::string(label)+".json"),io::write_statistics_json(report).text);
  write(dir/(std::string(label)+".txt"),io::write_statistics_text(report).text);return report;
}
inline void literal(const Report& report,const Database& db,std::uint64_t sequence){check(report.combined().has_value());facts(*report.combined(),db,sequence);}
inline void enqueue(QuerySession& session,PhysicalSetUpdate update){
  io::TransportBatch batch({io::InputEvent{std::move(update),{}}});check(session.enqueue(batch)==io::Admission::accepted);
}
inline void legacy_pair(const std::filesystem::path& dir,DeltaRuntime& runtime,const QuerySession& session){
  write(dir/"legacy-runtime.json",io::write_explain_json(observability::PlanExplanation::capture(runtime)));
  write(dir/"legacy-session.json",io::write_explain_json(observability::PlanExplanation::capture(session)));
}
}

#include "crown/api/error.hpp"
#include "crown/io/explain.hpp"
#include "crown/planner/lower.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
using namespace crown;
void write_case(const std::filesystem::path& directory,std::string_view name,std::uint64_t limit) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  Database database;database.tables={Relation{Row{std::int64_t{7}}}};
  runtime::SessionOptions options;
  options.delta.mode=runtime::DeltaMode::maintenance;
  options.delta.physical.support.memory_limit_bytes=limit;
  options.delta.physical.support.observation.mode=runtime::ObservationMode::counters;
  auto session=runtime::QuerySession::create_typed(planner::lower_tree(catalog,query,tree),database,{},options);
  if(session->report_metadata().plan().account().statistics().limit_bytes!=limit)
    throw std::runtime_error("reported input limit differs from the actual query account");
  const auto report=observability::PlanExplanation::capture(*session);
  std::ofstream output(directory/(std::string(name)+".json"),std::ios::binary);
  output.exceptions(std::ios::badbit|std::ios::failbit);
  output<<io::write_explain_json(report)<<'\n';
}
}
int main(int argc,char** argv) {
  try {
    if(argc!=2)throw std::runtime_error("usage: report-memory-schema OUTPUT_DIRECTORY");
    const std::filesystem::path directory=argv[1];std::filesystem::create_directories(directory);
    write_case(directory,"default",crown::runtime::SupportOptions{}.memory_limit_bytes);
    write_case(directory,"limited",1024ULL*1024+123);
    write_case(directory,"maximum",std::numeric_limits<std::uint64_t>::max());
    std::cout<<"Actual query account limits and memory-option report fixtures passed\n";
    return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}

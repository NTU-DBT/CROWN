// Test-boundary exporter: no oracle, query-class dispatch or timing code.
#include <crown/api/error.hpp>
#include <crown/io/document.hpp>
#include <crown/io/physical.hpp>
#include <crown/runtime/session.hpp>
#include "indexed_runtime_fixture.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace {
using namespace crown;
using io::Json;
void require(bool value, const char* message) {
  if (!value) throw Error("workload_replay", message);
}
std::string read(const char* path, std::size_t limit) {
  std::ifstream input(path, std::ios::binary);
  require(bool(input), "cannot open test input");
  std::string text; char block[4096];
  while (input) {
    input.read(block, sizeof(block));
    const auto count = static_cast<std::size_t>(input.gcount());
    require(count <= limit - text.size(), "test input exceeds byte limit");
    text.append(block, count);
  }
  require(!input.bad(), "cannot read test input");
  return text;
}
template<class Values> Json row(const Values& values) {
  auto out = Json::array();
  for (const auto& value : values) out.push_back(io::write_scalar_view(value));
  return out;
}
Json snapshot(runtime::QuerySession& owner) {
  const auto state = owner.snapshot(); auto out = Json::array();
  for (const auto& tuple : state.rows) out.push_back(row(tuple.values()));
  return out;
}
int run(int argc, char** argv) {
  require(argc == 5, "usage: workload_replay PHYSICAL.json INPUT.jsonl delta|maintenance reference_ordered_v1|indexed_chained_v1");
  auto plan = io::read_physical(read(argv[1], 16U * 1024U * 1024U));
  const std::string backend = argv[4];
  require(backend == "reference_ordered_v1" || backend == "indexed_chained_v1", "invalid test backend");
  if (backend == "indexed_chained_v1") {
    require(plan.normalized().has_value(), "expected a normalized SQL plan");
    plan = s04_runtime::lower_normalized(*plan.normalized(), plan.tree());
  }
  const auto text = read(argv[2], 8U * 1024U * 1024U);
  const std::string mode = argv[3];
  require(mode == "delta" || mode == "maintenance", "invalid test mode");
  runtime::SessionOptions options;
  options.delta.mode = mode == "delta" ? runtime::DeltaMode::delta : runtime::DeltaMode::maintenance;
  auto owner = runtime::QuerySession::create(plan, std::make_unique<std::istringstream>(text), options);
  Json report{{"backend", plan.guarantee().storage_backend}, {"mode", mode},
              {"physical_sha256", plan.physical_sha256()}, {"initial_rows", snapshot(*owner)},
              {"epochs", Json::array()}};
  owner->start(); std::uint64_t records = 0, steps = 0;
  for (;;) {
    const auto status = owner->begin_next_result();
    if (status == runtime::SessionBegin::end) break;
    require(status == runtime::SessionBegin::pending && records < 4096, "test input blocked or event cap exceeded");
    for (;;) {
      require(steps++ < 10'000'000, "test native-step cap exceeded");
      if (owner->step() == runtime::DeltaStep::prepared) break;
    }
    owner->commit(); auto signed_rows = Json::array();
    while (auto output = owner->next_output())
      signed_rows.push_back({{"operation", output->operation == SetOperation::insert ? "insert" : "delete"},
                             {"values", row(output->tuple.values())}});
    ++records;
    report["epochs"].push_back({{"sequence", owner->progress().sequence},
                                 {"source_positions", owner->progress().source_positions},
                                 {"current_rows", snapshot(*owner)}, {"signed_delta", std::move(signed_rows)}});
  }
  report["records"] = records;
  // This publication cap follows full DOM/string construction; it is not peak memory.
  const auto encoded = report.dump();
  require(encoded.size() <= 64U * 1024U * 1024U, "test report exceeds byte limit");
  std::cout << encoded << '\n';
  return std::cout ? 0 : 1;
}
} // namespace
int main(int argc, char** argv) {
  try { return run(argc, argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

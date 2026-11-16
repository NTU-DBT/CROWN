#include "crown/io/explain.hpp"
#include "crown/io/physical.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/observation.hpp"
#include <fstream>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using crown::observability::PlanExplanation;

std::string read_file(const char* path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::runtime_error("cannot open physical plan");
  std::string bytes{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
  if (!input.eof() && input.fail()) throw std::runtime_error("cannot read physical plan");
  return bytes;
}

std::string report_json(const crown::runtime::DeltaRuntime& runtime) {
  const auto report = PlanExplanation::capture(runtime);
  return crown::io::write_explain_json(report);
}

struct GenerationSeedReset {
  ~GenerationSeedReset() {
    crown::runtime::detail::set_observation_initial_generation_for_testing(0);
  }
};

void add_report(std::vector<std::pair<std::string, std::string>>& reports,
                const char* name, const crown::runtime::DeltaRuntime& runtime) {
  reports.emplace_back(name, report_json(runtime));
}

void emit(const std::vector<std::pair<std::string, std::string>>& reports) {
  std::cout.put('{');
  bool first = true;
  for (const auto& [name, report] : reports) {
    if (!first) std::cout.put(',');
    first = false;
    std::cout.put('"'); std::cout << name; std::cout << "\":"; std::cout << report;
  }
  std::cout << "}\n";
  if (!std::cout) throw std::runtime_error("report output failed");
}
}

int main(int argc, char** argv) {
  try {
    if (argc != 2) throw std::runtime_error("usage: runtime-report-emitter PLAN.json");
    auto plan = crown::io::read_physical(read_file(argv[1]));
    if (plan.route() != crown::PhysicalRoute::tree || plan.catalog().tables.size() != 1 ||
        plan.catalog().tables.front().columns.size() != 1 ||
        plan.catalog().tables.front().columns.front().type != crown::ScalarType::string ||
        plan.query().atoms.size() != 1)
      throw std::runtime_error("probe requires a one-table, one-string-column, one-atom tree plan");

    crown::runtime::DeltaOptions options;
    options.mode = crown::runtime::DeltaMode::delta;
    options.view = crown::runtime::ResultView::core;
    options.live_maintenance = crown::runtime::LiveMaintenance::on_output;
    options.completion = crown::runtime::DeltaCompletion::automatic;
    options.work_limit = 200000;
    options.physical.work_limit = 210000;
    options.physical.derivation_limit = 220000;
    options.physical.support.work_limit = 230000;
    options.physical.support.support_limit = 240000;
    options.physical.support.order = crown::runtime::PropagationOrder::lifo;
    options.physical.support.capture_transitions = true;
    options.physical.support.observation.mode = crown::runtime::ObservationMode::counters;
    options.physical.support.observation.trace_capacity = 7;
    options.physical.support.observation.sample_period = 3;
    options.physical.support.observation.sample_offset = 1;
    options.physical.support.observation.trace_timings = false;
    options.cursor.work_limit = 250000;
    options.epoch_view.work_limit = 260000;
    options.spool_row_limit = 270000;
    options.spool_byte_limit = 280000;

    const auto maximum = std::numeric_limits<std::uint64_t>::max();
    crown::runtime::detail::set_observation_initial_generation_for_testing(maximum - 1);
    GenerationSeedReset reset_seed;
    static_cast<void>(reset_seed);

    std::vector<std::pair<std::string, std::string>> reports;
    std::optional<PlanExplanation> detached;
    {
      crown::runtime::DeltaRuntime runtime(std::move(plan), options);
      crown::runtime::detail::set_observation_initial_generation_for_testing(0);
      add_report(reports, "initial", runtime);

      const crown::PhysicalSetUpdate update{
          1, crown::TableId{0}, crown::SetOperation::insert,
          crown::Row{crown::Value{std::string("o07-report-probe")}}};
      auto pending = runtime.begin(update);
      add_report(reports, "pending", runtime);
      pending.drain();
      auto committed = pending.commit();
      while (committed.next()) {}
      add_report(reports, "after_attempt", runtime);

      static_cast<void>(runtime.set_mode(crown::runtime::DeltaMode::delta));
      add_report(reports, "after_noop_switch", runtime);

      static_cast<void>(runtime.set_mode(crown::runtime::DeltaMode::maintenance));
      add_report(reports, "after_successful_switch", runtime);

      static_cast<void>(runtime.set_mode(crown::runtime::DeltaMode::delta));
      detached.emplace(PlanExplanation::capture(runtime));
    }
    reports.emplace_back("after_saturation_and_runtime_drop", crown::io::write_explain_json(*detached));
    emit(reports);
    return 0;
  } catch (const std::exception&) {
    std::cerr << "runtime_report_probe_failed\n";
    return 1;
  }
}

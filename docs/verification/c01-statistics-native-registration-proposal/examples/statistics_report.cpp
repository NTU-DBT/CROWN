#include "crown/io/statistics_explain.hpp"

#include <optional>

crown::io::StatisticsText export_statistics(
    const crown::runtime::DeltaRuntime& owner, crown::TableId source_table,
    const crown::observability::StatisticsExplanation* previous = nullptr) {
  namespace statistics = crown::runtime::statistics;
  crown::observability::StatisticsCaptureOptions options;
  options.state.emplace();
  options.state->selections.push_back(
      statistics::Selection{statistics::SourceScope{source_table}, std::nullopt});
  options.state_limits = statistics::Limits{};
  const auto report = crown::observability::StatisticsExplanation::capture(
      owner, options, previous, 0); // Explicit zero committed-event lag.
  return crown::io::write_statistics_json(report, {16 * 1024 * 1024, 1000000});
}

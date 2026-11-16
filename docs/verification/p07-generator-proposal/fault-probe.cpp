// Supplemental proposal probe; not a repository target or P07 acceptance suite.
#define main crown_p05_original_exception_test_main
#include "../../../tests/unit/residual_exception_test.cpp"
#undef main

#include "machine.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <vector>

namespace ap = crown::planner::alternatives_proposal;
namespace cd = crown::planner::continuation_detail;

namespace {
struct GeneratorRun {
  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  ap::GeneratorStatistics statistics;
  std::uint64_t records = 0;
  std::uint64_t cells = 0;
  std::size_t allocations = 0;
};

struct GeneratorState {
  ap::GeneratorStatistics statistics;
  std::uint64_t records = 0;
  std::uint64_t cells = 0;
  std::size_t depth = 0;
  std::shared_ptr<const FreeConnexTree> pending;
  bool cancelled = false;
};

bool same_statistics(const ap::GeneratorStatistics& left,
                     const ap::GeneratorStatistics& right) {
  return left.completed_steps == right.completed_steps &&
      left.topologies_examined == right.topologies_examined &&
      left.topology_survivors == right.topology_survivors &&
      left.drafts_ready == right.drafts_ready &&
      left.drafts_consumed == right.drafts_consumed &&
      left.peak_depth == right.peak_depth;
}

GeneratorState state_of(const ap::NormalFormGenerator& generator,
                        const std::shared_ptr<ap::ContentBudget>& budget) {
  return {generator.statistics(), budget->records(), budget->cells(),
          generator.current_depth(), generator.draft(), generator.cancelled()};
}

bool same_state(const GeneratorState& left, const GeneratorState& right) {
  return same_statistics(left.statistics, right.statistics) &&
      left.records == right.records && left.cells == right.cells &&
      left.depth == right.depth && left.pending == right.pending &&
      left.cancelled == right.cancelled;
}

void append_ready_draft(ap::NormalFormGenerator& generator,
                        const std::shared_ptr<ap::ContentBudget>& budget,
                        std::vector<std::shared_ptr<const FreeConnexTree>>& drafts) {
  const auto retained = generator.draft();
  check(static_cast<bool>(retained), "draft_ready did not expose an immutable draft");
  check(drafts.size() < drafts.capacity(), "probe draft reserve was too small");
  drafts.push_back(retained);
  const auto before = state_of(generator, budget);
  for (int observation = 0; observation != 2; ++observation) {
    const auto repeated = generator.step({});
    check(repeated.event == ap::GeneratorEvent::draft_ready &&
              generator.draft() == retained && same_state(before, state_of(generator, budget)),
          "ready observation changed the pending draft, cursor, statistics or budget");
  }
  generator.consume_draft();
}

bool process_result(ap::NormalFormGenerator& generator,
                    const std::shared_ptr<ap::ContentBudget>& budget,
                    std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
                    ap::Step result) {
  if (result.event == ap::GeneratorEvent::draft_ready) {
    append_ready_draft(generator, budget, drafts);
    return false;
  }
  if (result.event == ap::GeneratorEvent::exhausted) return true;
  check(result.event == ap::GeneratorEvent::advanced,
        "unbounded generator run stopped before exhaustion");
  return false;
}

bool run_until_exhausted(ap::NormalFormGenerator& generator,
                         const std::shared_ptr<ap::ContentBudget>& budget,
                         std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
                         std::size_t& calls) {
  constexpr std::size_t call_limit = 1'000'000;
  while (calls < call_limit) {
    ++calls;
    if (process_result(generator, budget, drafts, generator.step({}))) return true;
  }
  return false;
}

bool same_run(const ap::NormalFormGenerator& generator,
              const std::shared_ptr<ap::ContentBudget>& budget,
              const std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
              const GeneratorRun& expected) {
  return drafts.size() == expected.drafts.size() &&
      [&] {
        for (std::size_t i = 0; i < drafts.size(); ++i) {
          if (!drafts[i] || !expected.drafts[i] ||
              !same_tree(*drafts[i], *expected.drafts[i])) return false;
        }
        return true;
      }() &&
      same_statistics(generator.statistics(), expected.statistics) &&
      budget->records() == expected.records && budget->cells() == expected.cells;
}

GeneratorRun uninterrupted_run(const std::shared_ptr<const cd::BindingData>& binding) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  GeneratorRun result;
  result.drafts.reserve(256);
  allocation_count = 0;
  std::size_t calls = 0;
  check(run_until_exhausted(generator, budget, result.drafts, calls),
        "uninterrupted Boolean generator exceeded its finite probe bound");
  result.allocations = allocation_count;
  result.statistics = generator.statistics();
  result.records = budget->records();
  result.cells = budget->cells();
  check(!result.drafts.empty() && result.allocations > 0,
        "uninterrupted generator did not enumerate allocated drafts");
  check(result.statistics.drafts_ready == result.drafts.size() &&
            result.statistics.drafts_consumed == result.drafts.size(),
        "baseline draft accounting did not match its complete sequence");
  return result;
}

void fault_sweep_one(const std::shared_ptr<const cd::BindingData>& binding,
                     const GeneratorRun& expected, std::size_t point) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  drafts.reserve(256);
  allocation_count = 0;
  std::size_t calls = 0;
  bool failed = false;
  {
    FaultScope fault(static_cast<std::ptrdiff_t>(point));
    constexpr std::size_t call_limit = 1'000'000;
    while (calls < call_limit) {
      ++calls;
      ap::Step result;
      try {
        result = generator.step({});
      } catch (const std::bad_alloc&) {
        failed = true;
        break;
      }
      if (process_result(generator, budget, drafts, result)) break;
    }
    if (failed) {
      check(allocation_count == point + 1,
            "fault did not hit the requested observed allocation position");
      const auto failed_state = state_of(generator, budget);
      check(!failed_state.pending,
            "allocation failed while a draft acknowledgement was pending");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated_failure = false;
        try {
          static_cast<void>(generator.step({}));
        } catch (const std::bad_alloc&) {
          repeated_failure = true;
        }
        check(repeated_failure && same_state(failed_state, state_of(generator, budget)),
              "persistent failure did not retain the same pending operation on retry");
      }
    }
  }
  check(failed, "fault position was not reached in the uninterrupted allocation trace");
  check(run_until_exhausted(generator, budget, drafts, calls),
        "same generator owner failed to finish after allocation recovery");
  check(same_run(generator, budget, drafts, expected),
        "same-owner recovery differed from the complete uninterrupted trace or accounting");
}

void fault_sweep(const std::shared_ptr<const cd::BindingData>& binding,
                 const GeneratorRun& expected) {
  check(expected.allocations <=
            static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "baseline allocation count exceeds the fault helper's range");
  for (std::size_t point = 0; point < expected.allocations; ++point)
    fault_sweep_one(binding, expected, point);
}

void check_depth_resume(const std::shared_ptr<const cd::BindingData>& binding,
                        const GeneratorRun& expected) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  drafts.reserve(256);
  const auto before_zero = state_of(generator, budget);
  const auto zero = generator.step({0});
  check(zero.event == ap::GeneratorEvent::stopped &&
            zero.reason == ap::GeneratorStop::depth_limit && zero.requested_depth == 1 &&
            same_state(before_zero, state_of(generator, budget)),
        "zero depth grant started or charged the generator");

  std::size_t calls = 0;
  bool blocked = false;
  while (calls < 1'000'000) {
    ++calls;
    const auto result = generator.step({1});
    if (result.event == ap::GeneratorEvent::stopped) {
      check(result.reason == ap::GeneratorStop::depth_limit && result.requested_depth > 1,
            "depth-one run stopped for a reason other than its pending DFS push");
      blocked = true;
      break;
    }
    if (process_result(generator, budget, drafts, result)) break;
  }
  check(blocked, "depth-one ceiling did not reach a deeper saved operation");
  const auto before_retry = state_of(generator, budget);
  const auto same_ceiling = generator.step({1});
  check(same_ceiling.event == ap::GeneratorEvent::stopped &&
            same_ceiling.reason == ap::GeneratorStop::depth_limit &&
            same_ceiling.requested_depth > 1 &&
            same_state(before_retry, state_of(generator, budget)),
        "repeated depth stop changed the pending operation");
  check(run_until_exhausted(generator, budget, drafts, calls),
        "generator did not finish after monotonically lifting the depth ceiling");
  check(same_run(generator, budget, drafts, expected),
        "depth-limited resume differed from baseline sequence or accounting");
}

void check_content_resume(const std::shared_ptr<const cd::BindingData>& binding,
                          const GeneratorRun& expected, bool records) {
  const ap::ContentLimits initial = records
      ? ap::ContentLimits{1, {}}
      : ap::ContentLimits{{}, 0};
  auto budget = std::make_shared<ap::ContentBudget>(initial);
  ap::NormalFormGenerator generator(binding, 2, budget);
  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  drafts.reserve(256);
  std::size_t calls = 0;
  bool blocked = false;
  constexpr std::size_t call_limit = 1'000'000;
  while (calls < call_limit) {
    ++calls;
    const auto result = generator.step({});
    if (result.event == ap::GeneratorEvent::stopped) {
      const auto reason = records ? ap::GeneratorStop::record_limit
                                  : ap::GeneratorStop::cell_limit;
      check(result.reason == reason, "content cap stopped for the wrong reason");
      blocked = true;
      break;
    }
    if (process_result(generator, budget, drafts, result)) break;
  }
  check(blocked, "finite content cap did not stop its pending construction");
  const auto blocked_state = state_of(generator, budget);
  const auto repeated = generator.step({});
  const auto reason = records ? ap::GeneratorStop::record_limit
                              : ap::GeneratorStop::cell_limit;
  check(repeated.event == ap::GeneratorEvent::stopped && repeated.reason == reason &&
            same_state(blocked_state, state_of(generator, budget)),
        "repeated content stop changed the pending operation or cumulative usage");
  check(budget->raise_limits({{}, {}}), "monotone content-limit extension was rejected");
  check(budget->records() == blocked_state.records && budget->cells() == blocked_state.cells,
        "raising content limits reset cumulative accounting");
  check(run_until_exhausted(generator, budget, drafts, calls),
        "generator did not finish after monotonically lifting a content cap");
  check(same_run(generator, budget, drafts, expected),
        "content-limited resume differed from baseline sequence or accounting");
}

void check_cancel_retention(const std::shared_ptr<const cd::BindingData>& binding,
                            const GeneratorRun& expected) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  allocation_count = 0;
  std::size_t calls = 0;
  bool ready = false;
  while (calls < 100'000) {
    ++calls;
    const auto result = generator.step({});
    if (result.event == ap::GeneratorEvent::draft_ready) {
      ready = true;
      break;
    }
    check(result.event == ap::GeneratorEvent::advanced,
          "generator stopped before the first retained draft");
  }
  check(ready && !expected.drafts.empty(), "cancel probe did not reach a draft");
  const auto retained = generator.draft();
  check(retained && same_tree(*retained, *expected.drafts.front()),
        "first draft differed before cancellation");
  const auto retained_snapshot = *retained;
  const auto allocations_before_cancel = allocation_count;
  generator.cancel();
  check(allocation_count == allocations_before_cancel,
        "generator cancellation performed a global allocation");
  check(generator.cancelled() && generator.current_depth() == 0 && !generator.draft(),
        "cancel did not clear active generator ownership");
  check(same_tree(*retained, retained_snapshot),
        "caller-retained immutable draft changed after cancellation");
}
}  // namespace

int main() {
  try {
    const auto fixture = scoped_fixture({{0}, {0, 1}, {1}}, {});
    auto binding = std::make_shared<const cd::BindingData>(
        cd::BindingData{fixture.catalog, fixture.query});

    const auto baseline = uninterrupted_run(binding);
    fault_sweep(binding, baseline);
    check_depth_resume(binding, baseline);
    check_content_resume(binding, baseline, true);
    check_content_resume(binding, baseline, false);
    check_cancel_retention(binding, baseline);

    std::cout << "proposal_generator_fault_positions=" << baseline.allocations
              << " drafts=" << baseline.drafts.size()
              << " completed_steps=" << baseline.statistics.completed_steps
              << " topologies=" << baseline.statistics.topologies_examined
              << " survivors=" << baseline.statistics.topology_survivors
              << " records=" << baseline.records
              << " cells=" << baseline.cells
              << " persistent_retries=2 same_owner_recovery=yes"
              << " depth_record_cell_resume=yes ready_inertness=yes"
              << " retained_draft_cancel_allocation_free=yes authority=none\n";
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

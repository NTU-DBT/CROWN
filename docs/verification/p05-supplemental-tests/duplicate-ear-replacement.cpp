// Supplemental check against the frozen P05 implementation. Not a CMake target.
// Reuse the independently authored failure-test machinery, not planner helpers.
#define main crown_p05_original_exception_test_main
#include "../../../tests/unit/residual_exception_test.cpp"
#undef main

int main() {
  try {
    // Three complete equal scopes form a frozen anchor chain; native-first
    // restoration gives height3, while a shared generalized x/y branch gives2.
    const auto fixture = scoped_fixture({{0, 1}, {0, 1}, {0, 1}, {1, 2}, {2}}, {});
    const auto upper = calibrate(fixture, ResidualMode::candidates_with_exact_repair);
    check(upper.candidate.height() == 3 && !upper.optimum,
          "duplicate-ear fixture did not produce its taller checked upper");
    const auto exact = calibrate(fixture, ResidualMode::require_exact_original);
    check(exact.optimum && exact.optimum->height() == 2 && exact.candidate.height() == 2 &&
              exact.candidate.origin() == ResidualOrigin::exact_original &&
              exact.progress.statistics.candidate_publications == 2,
          "original proof did not improve and replace the taller residual candidate");

    auto owner = ResidualSearch::create(fixture.catalog, fixture.query,
                                       options_for(ResidualMode::require_exact_original));
    std::optional<ResidualCandidate> retained{};
    for (std::uint64_t unit = 0; unit < 1'000'000; ++unit) {
      const auto update = owner.advance({1, {}});
      if (!retained) {
        if (auto candidate = owner.candidate(); candidate && candidate->height() == 3)
          retained.emplace(*candidate);
      }
      if (update.stopped_for == ResidualStopReason::complete) break;
      check(update.stopped_for == ResidualStopReason::quantum_work,
            "unit replacement fixture stopped unexpectedly");
    }
    check(retained && retained->height() == 3 && owner.candidate() && owner.candidate()->height() == 2 &&
              validate_tree(fixture.catalog, fixture.query, retained->tree()).valid,
          "replacing a candidate mutated or invalidated an earlier immutable handle");
    Coverage coverage;
    residual_oom_sweep(fixture, ResidualMode::require_exact_original, exact, coverage,
                       "duplicate_ear_original_replacement");
    check(coverage.exact_failure_with_candidate,
          "supplemental sweep missed original proof failure with an existing candidate");
    std::cout << "supplemental duplicate-ear height3-to2 replacement and full fault sweep passed\n";
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

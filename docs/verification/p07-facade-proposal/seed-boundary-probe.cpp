// Excluded seed/width preflight; original test entry point is never run.
#define main crown_p05_original_exception_test_main
#include "../../../tests/unit/residual_exception_test.cpp"
#undef main
#include "../p07-api-proposal-2026-11-07.hpp"

namespace {
void bounded_after_seed(const VerifiedOptimum& proof,
                        std::optional<ResidualCandidate> residual,
                        std::size_t expected_height) {
  auto provider = CandidateProvider::create(proof, {}, {}, std::move(residual));
  const auto first = provider.advance(all_work);
  check(first.stopped_for == CandidateStop::candidate_ready && provider.candidate_count() == 1,
        "provider failed to publish supplied exact seed before enumeration");
  const auto retained = *provider.candidate(0);
  check(retained.height() == expected_height &&
            validate_tree(retained.catalog(), retained.query(), retained.tree()).valid,
        "seed is not an original-binding checked tree at the proved height");
  for (int round = 0; round != 2; ++round) {
    const auto before = provider.progress().work.attempted;
    const auto update = provider.advance({1000, {}});
    check(update.stopped_for == CandidateStop::quantum_work ||
              update.stopped_for == CandidateStop::candidate_ready,
          "bounded enumeration claimed exhaustion/unsupported or stopped unexpectedly");
    check(update.progress.work.attempted >= before &&
              update.progress.work.attempted - before <= 1000 &&
              !update.progress.family_exhausted && update.progress.verified_original_height == expected_height,
          "bounded enumeration lost actual height or exceeded its work grant");
  }
  provider.cancel();
  check(retained.height() == expected_height &&
            validate_tree(retained.catalog(), retained.query(), retained.tree()).valid &&
            retained.original_proof().height() == expected_height,
        "retained seed lost its tree or original proof on cancellation");
}
}  // namespace

int main() {
  try {
    const auto seven = scoped_fixture(
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}}, {0, 1, 6});
    const auto nine = scoped_fixture(
        {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5, 6},
         {1, 5, 7}, {6}, {7}, {0, 8}}, {0, 1, 8});
    for (const auto& fixture : {seven, nine}) {
      const auto baseline = calibrate(fixture, ResidualMode::require_exact_original);
      check(baseline.optimum && baseline.optimum->height() == 3 && baseline.candidate.height() == 3,
            "mandatory residual fixture did not supply original minimum three");
      bounded_after_seed(*baseline.optimum, baseline.candidate, 3);
      std::cout << "mandatory_atoms=" << fixture.query.atoms.size()
                << " original_height=3 residual_seed=checked bounded_resume=yes retained_proof=yes\n";
    }
    std::vector<std::vector<std::size_t>> scopes(70);
    for (auto& scope : scopes) for (std::size_t v = 0; v < 70; ++v) scope.push_back(v);
    const auto wide = scoped_fixture(scopes, {});
    auto exact = ExactSearch::create(wide.catalog, wide.query);
    check(exact.advance(all_work).progress.result == ResultKind::verified_optimum && exact.optimum(),
          "wide original P06 proof did not complete");
    check(exact.optimum()->height() == 1, "wide identical scopes changed their minimum height");
    bounded_after_seed(*exact.optimum(), {}, 1);
    std::cout << "wide_occurrences=70 wide_variables=70 original_height=1 bounded_resume=yes"
              << " fixed_mask_cutoff=none exhaustion_claimed=no\nproposal_only P07=not_started\n";
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

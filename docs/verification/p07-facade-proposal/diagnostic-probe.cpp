// White-box supplemental diagnostic probe; never a public construction route.
// Proofs still come solely from ExactSearch. Only counters are injected.
#include "crown/planner/residual.hpp"
#include "../p07-generator-proposal/machine.hpp"
#include "../p07-key-proposal/key_machine.hpp"
#include <memory>
#include <optional>
#include <string>
#define private public
#include "../p07-api-proposal-2026-11-07.hpp"
#undef private
#include "facade.cpp"
#include <iostream>
#include <stdexcept>

int main() {
  using namespace crown;
  using namespace crown::planner;
  const auto check = [](bool ok, const char* message) { if (!ok) throw std::runtime_error(message); };
  try {
    Catalog catalog;
    catalog.tables.push_back(Table{"R", {{"x", ScalarType::int64}}});
    Query query;
    query.variables.push_back({"x", ScalarType::int64});
    query.atoms.push_back(Atom{"r", TableId{0}, {VariableId{0}}});
    auto exact = ExactSearch::create(catalog, query);
    check(exact.advance({1'000'000, {}}).progress.result == ResultKind::verified_optimum,
          "diagnostic fixture did not produce real P06 proof");
    const auto proof = *exact.optimum();
    constexpr auto maximum_value = std::numeric_limits<std::uint64_t>::max();
    auto saturated = CandidateProvider::create(proof);
    saturated.data_->ledger.counters.active_nanoseconds = maximum_value;
    check(saturated.advance({1'000'000, {}}).stopped_for == CandidateStop::candidate_ready &&
              saturated.progress().work.active_nanoseconds == maximum_value,
          "saturated diagnostic time caused terminal overflow");
    CandidateLimits finite;
    finite.enumeration.active_time = std::chrono::nanoseconds{1'000'000};
    auto timed = CandidateProvider::create(proof, {}, finite);
    timed.data_->ledger.counters.active_nanoseconds = maximum_value;
    check(timed.advance({1, {}}).stopped_for == CandidateStop::total_time &&
              timed.progress().phase != CandidatePhase::failed,
          "finite time cap ignored saturated diagnostic time");
    for (int which = 0; which < 2; ++which) {
      auto overflow = CandidateProvider::create(proof);
      if (which == 0) overflow.data_->ledger.counters.attempted = maximum_value;
      else overflow.data_->ledger.counters.committed_transitions = maximum_value;
      check(overflow.advance({1, {}}).stopped_for == CandidateStop::counter_overflow &&
                overflow.progress().phase == CandidatePhase::failed &&
                overflow.advance({1, {}}).stopped_for == CandidateStop::counter_overflow,
            "logical overflow was not terminal");
    }
    CandidateLimits depth_limits;
    depth_limits.logical_depth = 0;
    auto depth = CandidateProvider::create(proof, {}, depth_limits);
    check(depth.advance({1'000'000, {}}).stopped_for == CandidateStop::depth_limit &&
              depth.progress().work.current_depth == 0 && depth.progress().work.peak_depth == 0,
          "blocked depth request counted as owned frame");
    depth_limits.logical_depth = 1;
    check(depth.raise_limits(depth_limits) == LimitChange::applied, "depth raise failed");
    auto advanced = depth.advance({1, {}});
    check(advanced.progress.work.current_depth == depth.data_->depth() &&
              advanced.progress.work.current_depth <= 1,
          "diagnostic current depth differs from actual saved worker frames");
    std::cout << "diagnostic_time_saturation=nonterminal finite_time_cap=enforced logical_overflow=terminal\n"
              << "blocked_first_depth=0 actual_frame_depth=matched proof_source=P06\n";
  } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}

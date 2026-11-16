#include "crown/api/error.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"
#include "tree_oracle.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace planner = crown::planner;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

struct Fixture {
  Catalog catalog;
  Query query;
};

Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
                       const std::vector<std::size_t>& head) {
  Fixture fixture;
  std::set<std::size_t> names(head.begin(), head.end());
  for (const auto& scope : scopes) names.insert(scope.begin(), scope.end());
  std::vector<VariableId> ids;
  ids.reserve(names.size());
  for (const auto name : names) {
    ids.push_back(VariableId{fixture.query.variables.size()});
    fixture.query.variables.push_back({"v" + std::to_string(name), ScalarType::int64});
  }
  for (std::size_t i = 0; i < scopes.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    for (std::size_t column = 0; column < scopes[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      atom.terms.emplace_back(ids.at(scopes[i][column]));
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (std::size_t i = 0; i < head.size(); ++i) {
    fixture.query.head.push_back({ids.at(head[i]), "out" + std::to_string(i)});
  }
  return fixture;
}

std::vector<std::vector<std::size_t>> residual_seven() {
  return {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}};
}

planner::HeightCertificate certificate_of(const planner::OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}

bool same_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) {
  return a.work == b.work && a.states == b.states && a.partitions == b.partitions &&
         a.candidates == b.candidates && a.cache_hits == b.cache_hits &&
         a.certificate_work == b.certificate_work && a.hierarchy_tests == b.hierarchy_tests &&
         a.hierarchy_hits == b.hierarchy_hits && a.singleton_hits == b.singleton_hits &&
         a.empty_body_hits == b.empty_body_hits && a.component_splits == b.component_splits &&
         a.symmetry_skips == b.symmetry_skips && a.bound_prunes == b.bound_prunes;
}

bool same_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result &&
         a.heights == b.heights && a.producer_complete == b.producer_complete &&
         a.proof_complete == b.proof_complete && a.producer == b.producer &&
         a.replay == b.replay && same_statistics(a.structural, b.structural) &&
         a.limit_revision == b.limit_revision;
}

bool same_progress(const planner::ReplayProgress& a, const planner::ReplayProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.complete == b.complete &&
         a.valid == b.valid && a.checked_claims == b.checked_claims && a.work == b.work &&
         a.limit_revision == b.limit_revision;
}

void check_monotone(const planner::SearchProgress& before,
                    const planner::SearchProgress& after,
                    const std::string& context) {
  check(after.producer.attempted >= before.producer.attempted &&
        after.producer.committed_transitions >= before.producer.committed_transitions &&
        after.producer.allocation_failures >= before.producer.allocation_failures &&
        after.producer.active_nanoseconds >= before.producer.active_nanoseconds &&
        after.producer.peak_depth >= before.producer.peak_depth,
        context + ": producer counters regressed");
  check(after.replay.attempted >= before.replay.attempted &&
        after.replay.committed_transitions >= before.replay.committed_transitions &&
        after.replay.allocation_failures >= before.replay.allocation_failures &&
        after.replay.active_nanoseconds >= before.replay.active_nanoseconds &&
        after.replay.peak_depth >= before.replay.peak_depth,
        context + ": replay counters regressed");
  check(after.limit_revision >= before.limit_revision, context + ": limit revision regressed");
}

void check_monotone(const planner::ReplayProgress& before,
                    const planner::ReplayProgress& after,
                    const std::string& context) {
  check(after.checked_claims >= before.checked_claims &&
        after.work.attempted >= before.work.attempted &&
        after.work.committed_transitions >= before.work.committed_transitions &&
        after.work.allocation_failures >= before.work.allocation_failures &&
        after.work.active_nanoseconds >= before.work.active_nanoseconds &&
        after.work.peak_depth >= before.work.peak_depth &&
        after.limit_revision >= before.limit_revision,
        context + ": replay progress regressed");
}

enum class Slicing { one_shot, unit, varied };

struct SearchRun {
  planner::SearchProgress progress;
  std::optional<planner::VerifiedOptimum> optimum;
  std::set<planner::SearchPhase> phases;
};

planner::ContinuationLimits generous_limits() {
  planner::ContinuationLimits limits;
  limits.producer.work = 50'000'000;
  limits.replay.work = 50'000'000;
  limits.logical_depth = 1024;
  return limits;
}

SearchRun run_search(const Fixture& fixture, Slicing slicing,
                     planner::SearchPolicy policy = planner::SearchPolicy::strict,
                     planner::ContinuationLimits limits = generous_limits()) {
  planner::SearchOptions options;
  options.policy = policy;
  options.limits = std::move(limits);
  auto owner = planner::ExactSearch::create(fixture.catalog, fixture.query, options);
  SearchRun result;
  constexpr std::array<std::uint64_t, 4> varied{3, 1, 5, 2};
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto before = owner.progress();
    planner::WorkQuantum quantum{50'000'000, {}};
    if (slicing == Slicing::unit) quantum.work = 1;
    else if (slicing == Slicing::varied) quantum.work = varied[step % varied.size()];
    const auto advanced = owner.advance(quantum);
    const auto& after = advanced.progress;
    check_monotone(before, after, "exact search");
    result.phases.insert(after.phase);
    if (policy == planner::SearchPolicy::strict) {
      check(!owner.incumbent(), "strict policy exposed an incumbent handle");
    }
    if (after.result == planner::ResultKind::failed) {
      throw std::runtime_error("continuation failed with stop reason " +
                               std::to_string(static_cast<int>(advanced.stopped_for)));
    }
    if (after.result == planner::ResultKind::verified_optimum) {
      result.progress = after;
      result.optimum = owner.optimum();
      check(result.optimum.has_value(), "verified optimum progress has no authority handle");
      check(advanced.stopped_for == planner::StopReason::complete,
            "completed exact search returned a nonterminal stop reason");
      return result;
    }
    check(advanced.stopped_for == planner::StopReason::quantum_work ||
          advanced.stopped_for == planner::StopReason::quantum_time ||
          advanced.stopped_for == planner::StopReason::total_work ||
          advanced.stopped_for == planner::StopReason::total_time,
          "unfinished exact search stopped for an unexpected reason");
  }
  throw std::runtime_error("exact search exceeded the continuation-step guard");
}

void compare_differential_representatives() {
  const std::vector<std::pair<std::string, Fixture>> cases{
      {"single occurrence", scoped_fixture({{0, 1}}, {0})},
      {"height-two nested scopes", scoped_fixture({{0, 1}, {1}}, {0})},
      {"duplicate-scope orbit", scoped_fixture({{0, 1}, {0, 1}, {1}}, {0})},
      {"disconnected components", scoped_fixture({{0, 1}, {1}, {2}}, {0, 2})},
  };
  constexpr std::size_t expected_case_count = 4;
  check(cases.size() == expected_case_count, "small differential case count changed");

  for (const auto& [name, fixture] : cases) {
    const auto v2 = planner::minimum_tree(fixture.catalog, fixture.query);
    const auto v1 = planner::testing::minimum_tree_baseline(fixture.catalog, fixture.query);
    const auto frozen = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
    check(v2.status == planner::OracleStatus::proven_minimum && v1.status == v2.status &&
          frozen.status == v2.status && v1.minimum_height == v2.minimum_height &&
          frozen.minimum_height == v2.minimum_height,
          name + ": v2, private v1, and frozen P03 disagree on feasibility or minimum height");
    check(v2.certificate_verified && v1.certificate_verified && v2.tree && v1.tree,
          name + ": a differential result omitted a complete checked witness");
    check(planner::validate_tree(fixture.catalog, fixture.query, *v2.tree).valid &&
          planner::validate_tree(fixture.catalog, fixture.query, *v1.tree).valid,
          name + ": a differential witness did not pass P02 validation");
    check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(v2)).valid &&
          planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(v1)).valid,
          name + ": a final differential proof failed independent replay");

    const auto one_shot = run_search(fixture, Slicing::one_shot);
    const auto unit = run_search(fixture, Slicing::unit);
    const auto varied = run_search(fixture, Slicing::varied);
    check(one_shot.optimum->height() == *v2.minimum_height &&
          unit.optimum->height() == one_shot.optimum->height() &&
          varied.optimum->height() == one_shot.optimum->height(),
          name + ": sliced continuations changed the exact result");
    check(one_shot.progress.producer.committed_transitions == unit.progress.producer.committed_transitions &&
          one_shot.progress.producer.committed_transitions == varied.progress.producer.committed_transitions &&
          one_shot.progress.replay.committed_transitions == unit.progress.replay.committed_transitions &&
          one_shot.progress.replay.committed_transitions == varied.progress.replay.committed_transitions,
          name + ": no-fault committed work changed with quantum schedule");
    check(planner::verify_height_certificate(fixture.catalog, fixture.query,
          one_shot.optimum->certificate()).valid &&
          planner::verify_height_certificate(fixture.catalog, fixture.query,
          unit.optimum->certificate()).valid &&
          planner::verify_height_certificate(fixture.catalog, fixture.query,
          varied.optimum->certificate()).valid,
          name + ": a sliced final proof failed independent replay");
    check(one_shot.progress.heights.lower && one_shot.progress.heights.upper &&
          *one_shot.progress.heights.lower <= *v2.minimum_height &&
          *v2.minimum_height <= *one_shot.progress.heights.upper &&
          unit.progress.heights.lower && unit.progress.heights.upper &&
          *unit.progress.heights.lower <= *v2.minimum_height &&
          *v2.minimum_height <= *unit.progress.heights.upper,
          name + ": completed height interval does not contain the independently known minimum");
    check(one_shot.progress.heights.lower_evidence == planner::BoundEvidence::independently_checked &&
          unit.progress.heights.lower_evidence == planner::BoundEvidence::independently_checked,
          name + ": final lower bound lacks independent evidence");

    // Exercise each existing certificate version through the independently
    // owned, one-transition-at-a-time replay facade.
    const auto v1_certificate = certificate_of(v1);
    const auto v2_certificate = certificate_of(v2);
    for (const auto* certificate : {&v1_certificate, &v2_certificate}) {
      auto replay = planner::CertificateReplay::create(fixture.catalog, fixture.query, *certificate);
      for (std::size_t step = 0; step < 5'000'000; ++step) {
        const auto before = replay.progress();
        const auto advanced = replay.advance(planner::WorkQuantum{1, {}});
        check_monotone(before, advanced.progress, name + ": standalone certificate replay");
        if (advanced.progress.complete) {
          check(advanced.progress.valid && replay.checked() && replay.checked()->valid(),
                name + ": replay completed without checked certificate authority");
          break;
        }
        check(!replay.checked(), name + ": partial replay exposed checked-certificate authority");
        check(advanced.stopped_for == planner::StopReason::quantum_work,
              name + ": one-step replay stopped for an unexpected reason");
        if (step + 1 == 5'000'000) throw std::runtime_error(name + ": replay exceeded step guard");
      }
    }
  }
}

void phase_suspension_and_interval_semantics() {
  const auto fixture = scoped_fixture({{0, 1}, {1}}, {0});
  auto best_options = planner::SearchOptions{};
  best_options.policy = planner::SearchPolicy::best_found;
  best_options.limits = generous_limits();
  auto best = planner::ExactSearch::create(fixture.catalog, fixture.query, best_options);
  bool saw_best_before_proof = false;
  std::set<planner::SearchPhase> phases;
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto before = best.progress();
    const auto advanced = best.advance(planner::WorkQuantum{1, {}});
    check_monotone(before, advanced.progress, "best-found search");
    phases.insert(advanced.progress.phase);
    if (const auto upper = best.incumbent()) {
      const auto progress = best.progress();
      check(upper->valid() && planner::validate_tree(fixture.catalog, fixture.query, upper->tree()).valid,
            "best-found exposed an upper tree before complete P02 validation");
      check(progress.heights.lower && progress.heights.upper &&
            *progress.heights.lower <= 2 && 2 <= *progress.heights.upper,
            "best-found interval failed to contain the known height-two optimum");
      check(!progress.producer_complete && !progress.proof_complete && !best.optimum(),
            "best-found upper was not published before proof completion");
      saw_best_before_proof = true;
      best.cancel();
      check(best.progress().phase == planner::SearchPhase::cancelled && !best.optimum(),
            "cancel did not end proof production");
      check(upper->valid() && upper->height() == 2 &&
            planner::validate_tree(fixture.catalog, fixture.query, upper->tree()).valid,
            "cancellation invalidated a published incumbent handle");
      break;
    }
    check(advanced.stopped_for == planner::StopReason::quantum_work,
          "unit-quantum best-found search stopped unexpectedly");
  }
  check(saw_best_before_proof, "nontrivial search never published a best-found upper before proof completion");
  check(phases.contains(planner::SearchPhase::preprocess) &&
        phases.contains(planner::SearchPhase::search) &&
        phases.contains(planner::SearchPhase::build_incumbent) &&
        phases.contains(planner::SearchPhase::validate_incumbent),
        "unit slicing did not suspend inside preprocess, search, witness build, and upper validation");

  // The seven-atom height-three residual is a compact deeper case that reaches
  // the ordinary exact search and proof export after preprocessing.
  const auto residual = scoped_fixture(residual_seven(), {0, 1, 6});
  const auto residual_run = run_search(residual, Slicing::unit);
  check(residual_run.optimum->height() == 3 && residual_run.progress.producer_complete &&
        residual_run.progress.proof_complete,
        "residual height-three case did not finish producer and independent proof replay");
  check(residual_run.phases.contains(planner::SearchPhase::preprocess) &&
        residual_run.phases.contains(planner::SearchPhase::search) &&
        residual_run.phases.contains(planner::SearchPhase::build_incumbent) &&
        residual_run.phases.contains(planner::SearchPhase::validate_incumbent) &&
        residual_run.phases.contains(planner::SearchPhase::export_proof) &&
        residual_run.phases.contains(planner::SearchPhase::replay),
        "residual case did not expose all public producer, witness, validation, export, and replay phases");
}

void replay_phase_coverage_and_corruption() {
  const auto fixture = scoped_fixture({{0, 1}, {0, 1}, {1}}, {0});
  const auto v2_result = planner::minimum_tree(fixture.catalog, fixture.query);
  const auto v1_result = planner::testing::minimum_tree_baseline(fixture.catalog, fixture.query);
  const auto good_v2 = certificate_of(v2_result);
  const auto good_v1 = certificate_of(v1_result);
  check(v2_result.minimum_height == 2 && v1_result.minimum_height == 2,
        "duplicate-scope replay fixture changed its known minimum");

  std::set<planner::ReplayPhase> phases;
  auto replay = planner::CertificateReplay::create(fixture.catalog, fixture.query, good_v2);
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto before = replay.progress();
    const auto advanced = replay.advance(planner::WorkQuantum{1, {}});
    check_monotone(before, advanced.progress, "v2 replay phase walk");
    phases.insert(advanced.progress.phase);
    if (advanced.progress.complete) {
      check(advanced.progress.valid && replay.checked(), "v2 phase walk failed final publication");
      break;
    }
    check(!replay.checked(), "v2 replay exposed authority before completion");
    check(advanced.stopped_for == planner::StopReason::quantum_work,
          "v2 replay phase walk stopped unexpectedly");
    if (step + 1 == 5'000'000) throw std::runtime_error("v2 replay phase walk exceeded step guard");
  }
  for (const auto phase : {planner::ReplayPhase::dispatch, planner::ReplayPhase::validate_upper,
                           planner::ReplayPhase::build_scopes, planner::ReplayPhase::classify_scope_orbits,
                           planner::ReplayPhase::index_claims, planner::ReplayPhase::order_claims,
                           planner::ReplayPhase::prove_claim, planner::ReplayPhase::match_root,
                           planner::ReplayPhase::complete}) {
    check(phases.contains(phase), "one-step v2 replay skipped a public replay phase");
  }

  auto require_rejected = [&](planner::HeightCertificate bad, const std::string& context) {
    auto checker = planner::CertificateReplay::create(fixture.catalog, fixture.query, std::move(bad));
    for (std::size_t step = 0; step < 5'000'000; ++step) {
      const auto advanced = checker.advance(planner::WorkQuantum{1, {}});
      if (advanced.progress.phase == planner::ReplayPhase::failed) {
        check(!advanced.progress.valid && !checker.checked(), context + ": rejected claim created authority");
        return;
      }
      check(!checker.checked(), context + ": malformed replay exposed partial authority");
      check(advanced.stopped_for == planner::StopReason::quantum_work,
            context + ": malformed replay stopped for an unexpected reason");
    }
    throw std::runtime_error(context + ": malformed proof was not rejected");
  };

  auto bad = good_v2;
  bad.algorithm = "unknown-partition";
  require_rejected(std::move(bad), "algorithm name");

  bad = good_v2;
  bad.minimum_height = 3;
  require_rejected(std::move(bad), "false minimum bound");

  const auto root = std::find_if(good_v2.lower_bounds.begin(), good_v2.lower_bounds.end(),
      [&](const planner::LowerBoundEntry& entry) {
        return entry.occurrences == std::vector<std::size_t>{0, 1, 2} &&
               entry.generalized_allowed && entry.connex_reachable;
      });
  check(root != good_v2.lower_bounds.end(), "v2 test proof omitted its full-query state");

  bad = good_v2;
  auto root_bad = std::find_if(bad.lower_bounds.begin(), bad.lower_bounds.end(),
      [](const planner::LowerBoundEntry& entry) {
        return entry.occurrences == std::vector<std::size_t>{0, 1, 2} &&
               entry.generalized_allowed && entry.connex_reachable;
      });
  root_bad->bound = 3;
  require_rejected(std::move(bad), "false root lower bound");

  bad = good_v2;
  auto flags_bad = std::find_if(bad.lower_bounds.begin(), bad.lower_bounds.end(),
      [](const planner::LowerBoundEntry& entry) {
        return entry.occurrences == std::vector<std::size_t>{0, 1, 2} &&
               entry.generalized_allowed && entry.connex_reachable;
      });
  flags_bad->connex_reachable = false;
  require_rejected(std::move(bad), "incorrect root flags");

  bad = good_v2;
  const auto orbit_member = std::find_if(bad.lower_bounds.begin(), bad.lower_bounds.end(),
      [](const planner::LowerBoundEntry& entry) {
        return entry.occurrences.size() == 1 &&
               (entry.occurrences.front() == 0 || entry.occurrences.front() == 1);
      });
  check(orbit_member != bad.lower_bounds.end(), "v2 test proof omitted an equal-scope orbit representative");
  auto duplicate_orbit = *orbit_member;
  duplicate_orbit.occurrences.front() = duplicate_orbit.occurrences.front() == 0 ? 1 : 0;
  bad.lower_bounds.push_back(std::move(duplicate_orbit));
  std::stable_sort(bad.lower_bounds.begin(), bad.lower_bounds.end(), [](const auto& a, const auto& b) {
    return a.occurrences.size() < b.occurrences.size();
  });
  require_rejected(std::move(bad), "duplicate v2 scope orbit");

  bad = good_v2;
  bad.lower_bounds.erase(std::remove_if(bad.lower_bounds.begin(), bad.lower_bounds.end(),
      [](const planner::LowerBoundEntry& entry) {
        return entry.occurrences == std::vector<std::size_t>{0, 1, 2} &&
               entry.generalized_allowed && entry.connex_reachable;
      }), bad.lower_bounds.end());
  require_rejected(std::move(bad), "missing full-query root proof");

  bad = good_v2;
  check(!bad.lower_bounds.empty() && !bad.lower_bounds.front().occurrences.empty(),
        "v2 test proof has no state ids to corrupt");
  bad.lower_bounds.front().occurrences.push_back(bad.lower_bounds.front().occurrences.front());
  require_rejected(std::move(bad), "duplicate state occurrence id");

  bad = good_v2;
  bad.lower_bounds.front().occurrences.push_back(fixture.query.atoms.size());
  require_rejected(std::move(bad), "out-of-range state occurrence id");

  bad = good_v2;
  check(bad.tree && bad.tree->claimed_native_height, "v2 witness omitted claimed upper height");
  ++*bad.tree->claimed_native_height;
  require_rejected(std::move(bad), "corrupt upper-tree height");

  // Prove that the v1 fixture is actually dispatched as v1, independently of
  // the v2 orbit test above.
  auto v1_replay = planner::CertificateReplay::create(fixture.catalog, fixture.query, good_v1);
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = v1_replay.advance(planner::WorkQuantum{1, {}});
    if (advanced.progress.complete) {
      check(advanced.progress.valid && v1_replay.checked(), "standalone v1 proof replay failed");
      break;
    }
    check(advanced.stopped_for == planner::StopReason::quantum_work,
          "standalone v1 replay stopped unexpectedly");
    if (step + 1 == 5'000'000) throw std::runtime_error("standalone v1 replay exceeded step guard");
  }
}

void ownership_move_and_zero_quantum() {
  const auto original = scoped_fixture({{0, 1}, {1}}, {0});
  auto changed = original;
  auto search = planner::ExactSearch::create(changed.catalog, changed.query);
  changed.catalog.tables.clear();
  changed.query.atoms.clear();
  changed.query.variables.clear();
  const auto bound = search.binding();
  check(bound.valid() && bound.catalog().tables.size() == 2 && bound.query().atoms.size() == 2 &&
        bound.catalog().tables.front().name == "T0",
        "search binding borrowed caller-owned input instead of retaining its snapshot");
  while (!search.progress().proof_complete) {
    const auto advanced = search.advance(planner::WorkQuantum{97, {}});
    check(advanced.progress.result != planner::ResultKind::failed,
          "mutated caller input affected owned continuation");
  }
  const auto completed_before = search.progress();
  const auto zero_work = search.advance(planner::WorkQuantum{0, {}});
  check(zero_work.stopped_for == planner::StopReason::quantum_work &&
        same_progress(completed_before, zero_work.progress),
        "zero-work quantum changed completed progress");
  const auto zero_time = search.advance(planner::WorkQuantum{1, std::chrono::nanoseconds{0}});
  check(zero_time.stopped_for == planner::StopReason::quantum_time &&
        same_progress(completed_before, zero_time.progress),
        "zero-time quantum changed completed progress");
  check(search.optimum() && search.optimum()->valid(), "completed owner lost its optimum handle");

  auto moved_from = planner::ExactSearch::create(original.catalog, original.query);
  auto moved_to = std::move(moved_from);
  check(moved_from.progress().phase == planner::SearchPhase::moved_from &&
        moved_from.advance(planner::WorkQuantum{1, {}}).stopped_for == planner::StopReason::moved_from,
        "moved-from exact-search facade remained callable");
  bool moved_binding_rejected = false;
  try { static_cast<void>(moved_from.binding()); }
  catch (const Error&) { moved_binding_rejected = true; }
  check(moved_binding_rejected, "moved-from exact-search binding was accepted");
  check(moved_to.binding().valid(), "move construction lost exact-search ownership");

  auto proof = planner::minimum_tree(original.catalog, original.query);
  auto source_certificate = certificate_of(proof);
  auto replay = planner::CertificateReplay::create(original.catalog, original.query, source_certificate);
  source_certificate.algorithm = "mutated-after-create";
  source_certificate.lower_bounds.clear();
  while (!replay.progress().complete) {
    const auto advanced = replay.advance(planner::WorkQuantum{31, {}});
    check(advanced.progress.phase != planner::ReplayPhase::failed,
          "caller mutation of source proof changed replay's owned copy");
  }
  check(replay.progress().valid && replay.checked(), "owned proof snapshot failed after caller mutation");
  const auto replay_done = replay.progress();
  const auto replay_zero = replay.advance(planner::WorkQuantum{0, {}});
  check(replay_zero.stopped_for == planner::StopReason::quantum_work &&
        same_progress(replay_done, replay_zero.progress),
        "zero-work quantum changed completed replay progress");

  auto replay_moved_from = planner::CertificateReplay::create(original.catalog, original.query, certificate_of(proof));
  auto replay_moved_to = std::move(replay_moved_from);
  check(replay_moved_from.progress().phase == planner::ReplayPhase::moved_from &&
        replay_moved_from.advance(planner::WorkQuantum{1, {}}).stopped_for == planner::StopReason::moved_from,
        "moved-from replay facade remained callable");
  check(replay_moved_to.binding().valid(), "move construction lost replay ownership");

  std::optional<planner::VerifiedOptimum> saved_optimum;
  std::optional<planner::ValidatedIncumbent> saved_upper;
  {
    auto ephemeral = planner::ExactSearch::create(original.catalog, original.query);
    while (!ephemeral.progress().proof_complete) {
      const auto advanced = ephemeral.advance(planner::WorkQuantum{127, {}});
      check(advanced.progress.result != planner::ResultKind::failed,
            "ephemeral owner failed before authority publication");
    }
    saved_optimum = ephemeral.optimum();
    check(saved_optimum.has_value(), "ephemeral owner produced no optimum handle");
    saved_upper = saved_optimum->upper();
  }
  check(saved_optimum && saved_optimum->valid() && saved_upper && saved_upper->valid() &&
        saved_optimum->height() == 2 && saved_upper->height() == 2 &&
        saved_optimum->binding().valid() && saved_upper->binding().valid() &&
        planner::verify_height_certificate(original.catalog, original.query,
                                           saved_optimum->certificate()).valid,
        "immutable authority handle did not outlive its facade");
}

void resource_stops_and_monotone_extension() {
  const auto fixture = scoped_fixture({{0, 1}, {1}}, {0});

  auto work_limits = generous_limits();
  work_limits.producer.work = 0;
  auto work_owner = planner::ExactSearch::create(fixture.catalog, fixture.query,
      planner::SearchOptions{planner::SearchPolicy::strict, work_limits});
  auto stopped = work_owner.advance(planner::WorkQuantum{10, {}});
  check(stopped.stopped_for == planner::StopReason::total_work &&
        stopped.progress.result == planner::ResultKind::unfinished && !stopped.progress.producer_complete &&
        !work_owner.incumbent() && !work_owner.optimum(),
        "zero producer-work ceiling published a partial or unsupported result");
  const auto before_raise = stopped.progress;
  work_limits.producer.work = std::nullopt;
  check(work_owner.raise_limits(work_limits) == planner::LimitChange::applied,
        "finite-to-unbounded producer extension was rejected");
  check(work_owner.progress().limit_revision == before_raise.limit_revision + 1 &&
        work_owner.progress().producer.attempted == before_raise.producer.attempted,
        "raising work limits reset work or omitted its revision");
  auto reduced = work_limits;
  reduced.producer.work = 100;
  check(work_owner.raise_limits(reduced) == planner::LimitChange::not_monotone,
        "unbounded-to-finite producer reduction was accepted");
  auto negative = work_limits;
  negative.producer.active_time = std::chrono::nanoseconds{-1};
  check(work_owner.raise_limits(negative) == planner::LimitChange::invalid,
        "negative active-time ceiling was accepted");
  while (!work_owner.progress().proof_complete) {
    const auto advanced = work_owner.advance(planner::WorkQuantum{257, {}});
    check(advanced.progress.result != planner::ResultKind::failed,
          "raised producer work ceiling did not resume");
  }

  auto depth_limits = generous_limits();
  depth_limits.logical_depth = 0;
  auto depth_owner = planner::ExactSearch::create(fixture.catalog, fixture.query,
      planner::SearchOptions{planner::SearchPolicy::strict, depth_limits});
  stopped = depth_owner.advance(planner::WorkQuantum{100, {}});
  check(stopped.stopped_for == planner::StopReason::depth_limit &&
        stopped.progress.result == planner::ResultKind::unfinished && !depth_owner.optimum() &&
        !depth_owner.incumbent(), "zero logical depth did not retain an unfinished search");
  const auto depth_before = stopped.progress;
  depth_limits.logical_depth = 1024;
  check(depth_owner.raise_limits(depth_limits) == planner::LimitChange::applied,
        "raising logical depth was rejected");
  check(depth_owner.progress().producer.attempted == depth_before.producer.attempted &&
        depth_owner.progress().producer.committed_transitions == depth_before.producer.committed_transitions,
        "raising logical depth reset charged transitions");
  auto depth_reduction = depth_limits;
  depth_reduction.logical_depth = 512;
  check(depth_owner.raise_limits(depth_reduction) == planner::LimitChange::not_monotone,
        "lowering logical depth was accepted");
  while (!depth_owner.progress().proof_complete) {
    const auto advanced = depth_owner.advance(planner::WorkQuantum{257, {}});
    check(advanced.progress.result != planner::ResultKind::failed,
          "raised logical depth did not resume the retained continuation");
  }
  check(depth_owner.progress().producer.attempted > depth_before.producer.attempted,
        "depth resume made no additional charged work");

  auto time_limits = generous_limits();
  time_limits.producer.active_time = std::chrono::nanoseconds{0};
  auto time_owner = planner::ExactSearch::create(fixture.catalog, fixture.query,
      planner::SearchOptions{planner::SearchPolicy::strict, time_limits});
  for (int i = 0; i < 4; ++i) {
    stopped = time_owner.advance(planner::WorkQuantum{1, {}});
    check(stopped.stopped_for == planner::StopReason::total_time &&
          stopped.progress.result == planner::ResultKind::unfinished && !time_owner.optimum(),
          "zero active-time ceiling did not preserve unfinished search state");
  }
  const auto charged_time = time_owner.progress().producer.active_nanoseconds;
  check(charged_time > 1, "active-time ceiling did not record active execution time");
  auto below_time = time_limits;
  below_time.producer.active_time = std::chrono::nanoseconds{1};
  check(time_owner.raise_limits(below_time) == planner::LimitChange::below_consumed,
        "limit below already consumed active time was accepted");
  time_limits.producer.active_time.reset();
  check(time_owner.raise_limits(time_limits) == planner::LimitChange::applied,
        "finite-to-unbounded active-time extension was rejected");
  while (!time_owner.progress().proof_complete) {
    const auto advanced = time_owner.advance(planner::WorkQuantum{257, {}});
    check(advanced.progress.result != planner::ResultKind::failed,
          "raised active-time ceiling did not resume");
  }

  auto replay_limits = generous_limits();
  replay_limits.replay.work = 0;
  auto cut = planner::ExactSearch::create(fixture.catalog, fixture.query,
      planner::SearchOptions{planner::SearchPolicy::strict, replay_limits});
  bool saw_producer_done_before_authority = false;
  for (std::size_t i = 0; i < 1'000'000; ++i) {
    stopped = cut.advance(planner::WorkQuantum{100, {}});
    if (stopped.progress.producer_complete) {
      check(stopped.stopped_for == planner::StopReason::total_work &&
            stopped.progress.phase == planner::SearchPhase::replay &&
            !stopped.progress.proof_complete && stopped.progress.result == planner::ResultKind::unfinished &&
            !cut.optimum() && !cut.infeasibility() && !cut.incumbent(),
            "replay cut published strict optimum authority or a certificate");
      saw_producer_done_before_authority = true;
      break;
    }
    check(stopped.progress.result != planner::ResultKind::failed,
          "producer failed before the requested replay cut");
  }
  check(saw_producer_done_before_authority, "could not suspend after producer proof completion");
  replay_limits.replay.work = 50'000'000;
  check(cut.raise_limits(replay_limits) == planner::LimitChange::applied,
        "raising replay work ceiling was rejected");
  while (!cut.progress().proof_complete) {
    stopped = cut.advance(planner::WorkQuantum{257, {}});
    check(stopped.progress.result != planner::ResultKind::failed,
          "raised replay ceiling did not resume final authority checking");
  }
  check(cut.optimum() && cut.optimum()->valid(), "resumed replay did not publish the strict optimum");
}

void wide_dynamic_and_replay_input_ownership() {
  constexpr std::size_t width = 70;
  std::vector<std::vector<std::size_t>> chain(width);
  std::vector<std::size_t> head;
  for (std::size_t variable = 0; variable < width; ++variable) {
    head.push_back(variable);
    for (std::size_t occurrence = variable; occurrence < width; ++occurrence) {
      chain[occurrence].push_back(variable);
    }
  }
  const auto deep = scoped_fixture(chain, head);
  check(deep.query.variables.size() > 64 && deep.query.atoms.size() > 64 && chain.back().size() > 64,
        "wide continuation fixture does not cross legacy fixed-width assumptions");
  const auto deep_run = run_search(deep, Slicing::varied);
  check(deep_run.optimum->height() == 1 && deep_run.progress.proof_complete,
        "wide, deeply nested incidence chain did not finish with a checked optimum");

  const auto fixture = scoped_fixture({{0, 1}, {0, 1}, {1}}, {0});
  const auto result = planner::minimum_tree(fixture.catalog, fixture.query);
  auto proof = certificate_of(result);
  auto input_catalog = fixture.catalog;
  auto input_query = fixture.query;
  auto replay = planner::CertificateReplay::create(input_catalog, input_query, proof);
  input_catalog.tables.clear();
  input_query.atoms.clear();
  input_query.variables.clear();
  proof.algorithm = "mutated-after-admission";
  proof.lower_bounds.clear();
  check(replay.binding().catalog().tables.size() == 3 && replay.binding().query().atoms.size() == 3,
        "replay binding borrowed source catalog or query");
  while (!replay.progress().complete) {
    const auto advanced = replay.advance(planner::WorkQuantum{13, {}});
    check(advanced.progress.phase != planner::ReplayPhase::failed,
          "mutating replay source input/proof changed its admitted snapshot");
  }
  check(replay.progress().valid && replay.checked(),
        "owned replay snapshot failed to validate after caller mutation");
}

static_assert(!std::is_convertible_v<planner::ValidatedIncumbent, planner::VerifiedOptimum>);
static_assert(!std::is_constructible_v<planner::VerifiedOptimum, planner::ValidatedIncumbent>);
static_assert(!std::is_convertible_v<planner::VerifiedOptimum, planner::ValidatedIncumbent>);
static_assert(std::is_same_v<decltype(std::declval<const planner::ValidatedIncumbent&>().tree()),
                             const FreeConnexTree&>);

}  // namespace

int main() {
  try {
    compare_differential_representatives();
    phase_suspension_and_interval_semantics();
    replay_phase_coverage_and_corruption();
    ownership_move_and_zero_quantum();
    resource_stops_and_monotone_extension();
    wide_dynamic_and_replay_input_ownership();
    std::cout << "planner continuation semantics, slicing, ownership, replay, and resource limits passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}

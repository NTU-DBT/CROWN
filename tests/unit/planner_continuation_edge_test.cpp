#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;
using namespace crown::planner;

void check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

struct Fixture {
  Catalog catalog;
  Query query;
};

Fixture fixture_for(const std::vector<std::vector<std::size_t>>& scopes,
                    const std::vector<std::size_t>& head) {
  Fixture fixture;
  std::set<std::size_t> used;
  for (const auto& scope : scopes) used.insert(scope.begin(), scope.end());
  used.insert(head.begin(), head.end());
  std::vector<VariableId> ids;
  ids.reserve(used.size());
  for (const auto value : used) {
    ids.push_back(VariableId{fixture.query.variables.size()});
    fixture.query.variables.push_back({"v" + std::to_string(value), ScalarType::int64});
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
  for (std::size_t i = 0; i < head.size(); ++i)
    fixture.query.head.push_back({ids.at(head[i]), "out" + std::to_string(i)});
  return fixture;
}

HeightCertificate certificate_for(const OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}

bool is_full_root(const LowerBoundEntry& entry, std::size_t occurrence_count) {
  if (entry.occurrences.size() != occurrence_count) return false;
  for (std::size_t i = 0; i < occurrence_count; ++i)
    if (entry.occurrences[i] != i) return false;
  return true;
}

bool zero_depth_counters(const SearchProgress& progress) {
  return progress.producer.current_depth == 0 && progress.producer.peak_depth == 0 &&
      progress.replay.current_depth == 0 && progress.replay.peak_depth == 0;
}

bool zero_depth_counters(const ReplayProgress& progress) {
  return progress.work.current_depth == 0 && progress.work.peak_depth == 0;
}

bool same_work_history(const WorkCounters& before, const WorkCounters& after) {
  return before.attempted == after.attempted &&
      before.committed_transitions == after.committed_transitions &&
      before.allocation_failures == after.allocation_failures &&
      before.active_nanoseconds == after.active_nanoseconds &&
      before.peak_depth == after.peak_depth && after.current_depth == 0;
}

bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) {
  return a.work == b.work && a.states == b.states && a.partitions == b.partitions &&
      a.candidates == b.candidates && a.cache_hits == b.cache_hits &&
      a.certificate_work == b.certificate_work && a.hierarchy_tests == b.hierarchy_tests &&
      a.hierarchy_hits == b.hierarchy_hits && a.singleton_hits == b.singleton_hits &&
      a.empty_body_hits == b.empty_body_hits && a.component_splits == b.component_splits &&
      a.symmetry_skips == b.symmetry_skips && a.bound_prunes == b.bound_prunes;
}

SearchProgress finish_unit_search(ExactSearch& owner) {
  for (;;) {
    const auto advanced = owner.advance(WorkQuantum{1, {}});
    if (advanced.stopped_for == StopReason::complete) return advanced.progress;
    check(advanced.stopped_for == StopReason::quantum_work &&
              advanced.progress.result != ResultKind::failed,
          "unit-quantum exact search stopped before completion");
  }
}

ReplayProgress finish_unit_replay(CertificateReplay& owner) {
  for (;;) {
    const auto advanced = owner.advance(WorkQuantum{1, {}});
    if (advanced.stopped_for == StopReason::complete) return advanced.progress;
    check(advanced.stopped_for == StopReason::quantum_work &&
              advanced.progress.phase != ReplayPhase::failed,
          "unit-quantum certificate replay stopped before completion");
  }
}

// Compatibility diagnostics describe only the evidence that replay published.
void compatibility_report_describes_checked_evidence(const Fixture& finite,
                                                       const HeightCertificate& certificate) {
  const auto upper = verify_height_certificate(finite.catalog, finite.query, certificate);
  check(upper.valid && !upper.resource_limit &&
            upper.message == "upper tree and independent lower bound verified",
        "finite replay diagnostic lost its checked upper/lower meaning");

  const auto cyclic = fixture_for({{0, 1}, {1, 2}, {0, 2}}, {0, 1, 2});
  const auto impossible = minimum_tree(cyclic.catalog, cyclic.query);
  check(impossible.status == OracleStatus::unsupported && impossible.certificate_verified &&
            !impossible.tree && !impossible.minimum_height,
        "cyclic fixture did not supply an independently checked empty family");
  const auto infinite = certificate_for(impossible);
  const auto empty = verify_height_certificate(cyclic.catalog, cyclic.query, infinite);
  check(empty.valid && !empty.resource_limit &&
            empty.message == "empty admissible family independently verified",
        "infeasibility replay diagnostic incorrectly claimed an upper tree");

  auto corrupt = infinite;
  corrupt.algorithm = "unknown";
  const auto invalid = verify_height_certificate(cyclic.catalog, cyclic.query, corrupt);
  check(!invalid.valid && !invalid.resource_limit &&
            invalid.message == "invalid exact-search certificate",
        "unreplayed empty-family claim received a successful diagnostic");

  SearchLimits limits;
  limits.work_limit = 0;
  const auto stopped = verify_height_certificate(cyclic.catalog, cyclic.query, infinite, limits);
  check(!stopped.valid && stopped.resource_limit &&
            stopped.message == "cumulative search work limit reached",
        "resource-stopped replay received a successful diagnostic");
}

void empty_body_depth_zero() {
  Catalog catalog;
  Query query;
  SearchLimits legacy_limits;
  legacy_limits.recursion_limit = 0;
  const auto legacy = minimum_tree(catalog, query, legacy_limits);
  check(legacy.status == OracleStatus::proven_minimum && legacy.minimum_height == 0 &&
            legacy.tree && legacy.certificate_verified,
        "legacy zero-recursion empty-body search did not prove height zero");
  const auto certificate = certificate_for(legacy);

  SearchOptions search_options;
  search_options.limits.logical_depth = 0;
  auto search = ExactSearch::create(catalog, query, search_options);
  const auto searched = finish_unit_search(search);
  check(searched.result == ResultKind::verified_optimum && searched.proof_complete &&
            searched.heights.lower == 0 && searched.heights.upper == 0 &&
            zero_depth_counters(searched),
        "owned zero-depth empty-body search did not finish at height zero without frames");
  const auto optimum = search.optimum();
  check(optimum && optimum->valid() && optimum->height() == 0 &&
            optimum->certificate().minimum_height == 0,
        "owned empty-body search did not publish its zero-height authority");

  ReplayOptions replay_options;
  replay_options.logical_depth = 0;
  auto replay = CertificateReplay::create(catalog, query, certificate, replay_options);
  const auto replayed = finish_unit_replay(replay);
  check(replayed.complete && replayed.valid && replayed.checked_claims == 0 &&
            zero_depth_counters(replayed),
        "owned zero-depth empty-body replay did not complete without frames");
  const auto checked = replay.checked();
  check(checked && checked->valid() && checked->optimum() &&
            checked->optimum()->height() == 0,
        "zero-depth empty-body replay did not publish its checked authority");
}

void zero_depth_nonempty_retains_and_resumes(const Fixture& fixture,
                                             const HeightCertificate& certificate) {
  SearchOptions search_options;
  search_options.limits.logical_depth = 0;
  auto search = ExactSearch::create(fixture.catalog, fixture.query, search_options);
  auto stopped = search.advance(WorkQuantum{1, {}});
  check(stopped.stopped_for == StopReason::quantum_work,
        "nonempty zero-depth search did not create its owner shell");
  stopped = search.advance(WorkQuantum{1, {}});
  check(stopped.stopped_for == StopReason::depth_limit &&
            stopped.progress.result == ResultKind::unfinished &&
            !stopped.progress.proof_complete && !search.optimum(),
        "nonempty zero-depth search did not stop before its first frame");
  const auto before_retry = search.progress();
  const auto repeated = search.advance(WorkQuantum{1, {}});
  const auto after_retry = search.progress();
  check(repeated.stopped_for == StopReason::depth_limit &&
            after_retry.producer.attempted == before_retry.producer.attempted + 1 &&
            after_retry.producer.committed_transitions == before_retry.producer.committed_transitions &&
            after_retry.result == ResultKind::unfinished && !search.optimum(),
        "repeated depth stop did not retain the same exact-search cursor");
  search_options.limits.logical_depth = std::nullopt;
  check(search.raise_limits(search_options.limits) == LimitChange::applied,
        "removing the search depth ceiling was rejected");
  const auto search_done = finish_unit_search(search);
  check(search_done.proof_complete && search.optimum() &&
            search.optimum()->height() == certificate.minimum_height,
        "same exact-search owner failed to resume after raising depth");

  ReplayOptions replay_options;
  replay_options.logical_depth = 0;
  auto replay = CertificateReplay::create(fixture.catalog, fixture.query, certificate, replay_options);
  auto replay_stopped = replay.advance(WorkQuantum{1, {}});
  check(replay_stopped.stopped_for == StopReason::quantum_work,
        "nonempty zero-depth replay did not create its owner shell");
  replay_stopped = replay.advance(WorkQuantum{1, {}});
  check(replay_stopped.stopped_for == StopReason::depth_limit &&
            !replay_stopped.progress.complete && !replay_stopped.progress.valid &&
            !replay.checked(),
        "nonempty zero-depth replay did not stop before its first frame");
  const auto replay_before_retry = replay.progress();
  const auto replay_repeated = replay.advance(WorkQuantum{1, {}});
  const auto replay_after_retry = replay.progress();
  check(replay_repeated.stopped_for == StopReason::depth_limit &&
            replay_after_retry.work.attempted == replay_before_retry.work.attempted + 1 &&
            replay_after_retry.work.committed_transitions ==
                replay_before_retry.work.committed_transitions &&
            replay_after_retry.checked_claims == replay_before_retry.checked_claims &&
            !replay_after_retry.valid && !replay.checked(),
        "repeated replay depth stop did not retain its cursor and claims");
  replay_options.logical_depth = std::nullopt;
  check(replay.raise_limits(replay_options) == LimitChange::applied,
        "removing the replay depth ceiling was rejected");
  const auto replay_done = finish_unit_replay(replay);
  check(replay_done.valid && replay.checked(),
        "same replay owner failed to resume after raising depth");
}

void cancellation_preserves_work_history_and_claims(
    const Fixture& fixture, const HeightCertificate& certificate) {
  auto search = ExactSearch::create(fixture.catalog, fixture.query);
  SearchProgress before_search_cancel;
  for (;;) {
    const auto advanced = search.advance(WorkQuantum{1, {}});
    before_search_cancel = advanced.progress;
    if (before_search_cancel.producer.current_depth > 0) break;
    check(advanced.stopped_for == StopReason::quantum_work &&
              before_search_cancel.result != ResultKind::failed,
          "exact search stopped before reaching a nonzero logical depth");
  }
  search.cancel();
  const auto after_search_cancel = search.progress();
  check(after_search_cancel.phase == SearchPhase::cancelled &&
            after_search_cancel.result == ResultKind::unfinished &&
            after_search_cancel.producer.current_depth == 0 &&
            after_search_cancel.replay.current_depth == 0 &&
            same_work_history(before_search_cancel.producer, after_search_cancel.producer) &&
            same_work_history(before_search_cancel.replay, after_search_cancel.replay) &&
            same_statistics(before_search_cancel.structural, after_search_cancel.structural),
        "search cancellation lost work history or failed to clear current depth");

  auto replay = CertificateReplay::create(fixture.catalog, fixture.query, certificate);
  ReplayProgress before_replay_cancel;
  for (;;) {
    const auto advanced = replay.advance(WorkQuantum{1, {}});
    before_replay_cancel = advanced.progress;
    if (before_replay_cancel.checked_claims > 0 && !before_replay_cancel.complete) break;
    check(advanced.stopped_for == StopReason::quantum_work &&
              !before_replay_cancel.valid,
          "certificate replay stopped before publishing a partial checked-claim count");
  }
  replay.cancel();
  const auto after_replay_cancel = replay.progress();
  check(after_replay_cancel.phase == ReplayPhase::cancelled &&
            !after_replay_cancel.complete && !after_replay_cancel.valid &&
            after_replay_cancel.checked_claims == before_replay_cancel.checked_claims &&
            same_work_history(before_replay_cancel.work, after_replay_cancel.work),
        "replay cancellation lost checked-claim history or failed to clear current depth");
}

void replay_rejects_corrupt_v1(const Fixture& fixture) {
  const auto baseline = testing::minimum_tree_baseline(fixture.catalog, fixture.query);
  check(baseline.status == OracleStatus::proven_minimum && baseline.minimum_height == 2 &&
            baseline.tree,
        "v1 corruption fixture did not produce a strict baseline certificate");
  const auto good = certificate_for(baseline);
  check(good.algorithm == "crown_partition_exact_v1",
        "strict baseline did not emit a v1 certificate");

  auto replay_good = CertificateReplay::create(fixture.catalog, fixture.query, good);
  const auto valid = finish_unit_replay(replay_good);
  check(valid.valid && replay_good.checked() && replay_good.checked()->valid(),
        "unmodified v1 certificate failed standalone unit-step replay");

  const auto reject_after_steps = [&](HeightCertificate corrupted, const char* label) {
    // Creation only admits and owns the typed value. Rejection must come from
    // subsequent replay transitions, not eager format handling.
    auto replay = CertificateReplay::create(fixture.catalog, fixture.query, std::move(corrupted));
    auto advanced = replay.advance(WorkQuantum{1, {}});
    std::size_t steps = 1;
    check(advanced.stopped_for == StopReason::quantum_work &&
              !advanced.progress.complete && !advanced.progress.valid && !replay.checked(),
          "corrupt v1 proof was rejected before its first replay unit");
    while (advanced.stopped_for == StopReason::quantum_work) {
      advanced = replay.advance(WorkQuantum{1, {}});
      ++steps;
    }
    const auto progress = replay.progress();
    if (advanced.stopped_for != StopReason::invalid_certificate ||
        progress.phase != ReplayPhase::failed || !progress.complete || progress.valid ||
        replay.checked() || steps < 2 || progress.work.committed_transitions == 0) {
      std::cerr << "v1 replay corruption " << label << " stop="
                << static_cast<int>(advanced.stopped_for) << " phase="
                << static_cast<int>(progress.phase) << " complete=" << progress.complete
                << " valid=" << progress.valid << " claims=" << progress.checked_claims
                << " steps=" << steps << '\n';
    }
    check(advanced.stopped_for == StopReason::invalid_certificate &&
              progress.phase == ReplayPhase::failed && progress.complete && !progress.valid &&
              !replay.checked() && steps >= 2 && progress.work.committed_transitions > 0,
          "corrupt v1 proof was not rejected after replay work");
  };

  auto bad_algorithm = good;
  bad_algorithm.algorithm = "unsupported_v1_variant";
  reject_after_steps(std::move(bad_algorithm), "algorithm");

  auto bad_root = good;
  auto root = std::find_if(bad_root.lower_bounds.begin(), bad_root.lower_bounds.end(),
      [&](const LowerBoundEntry& entry) { return is_full_root(entry, fixture.query.atoms.size()); });
  check(root != bad_root.lower_bounds.end(), "v1 proof omitted its full-query root claim");
  bad_root.lower_bounds.erase(root);
  reject_after_steps(std::move(bad_root), "root");

  auto bad_members = good;
  check(!bad_members.lower_bounds.empty() && !bad_members.lower_bounds.front().occurrences.empty(),
        "v1 proof has no member claim to corrupt");
  bad_members.lower_bounds.front().occurrences.back() = fixture.query.atoms.size();
  reject_after_steps(std::move(bad_members), "members");

  auto bad_bounds = good;
  root = std::find_if(bad_bounds.lower_bounds.begin(), bad_bounds.lower_bounds.end(),
      [&](const LowerBoundEntry& entry) { return is_full_root(entry, fixture.query.atoms.size()); });
  check(root != bad_bounds.lower_bounds.end() && root->bound && *root->bound == 2,
        "v1 proof root bound did not match the expected height-two fixture");
  root->bound = 1;
  reject_after_steps(std::move(bad_bounds), "bounds");

  auto bad_upper_height = good;
  check(bad_upper_height.tree && bad_upper_height.minimum_height,
        "v1 corruption fixture omitted its upper tree");
  bad_upper_height.tree->claimed_native_height = *bad_upper_height.minimum_height + 1;
  reject_after_steps(std::move(bad_upper_height), "upper-height");
}

std::uint64_t total_active_time(const SearchProgress& progress) {
  return progress.producer.active_nanoseconds + progress.replay.active_nanoseconds;
}

void active_time_excludes_admission_and_idle(const Fixture& fixture,
                                             const HeightCertificate& certificate) {
  using namespace std::chrono_literals;
  SearchOptions search_options;
  search_options.limits.producer.active_time = 2s;
  search_options.limits.replay.active_time = 2s;
  auto search = ExactSearch::create(fixture.catalog, fixture.query, search_options);
  const auto admitted_search = search.progress();
  check(total_active_time(admitted_search) == 0,
        "search admission was charged as active continuation time");
  const auto search_zero_before = search.progress();
  const auto search_zero = search.advance(WorkQuantum{0, {}});
  const auto search_zero_after = search.progress();
  check(search_zero.stopped_for == StopReason::quantum_work &&
            search_zero_before.producer == search_zero_after.producer &&
            search_zero_before.replay == search_zero_after.replay,
        "zero-work search grant sampled active time or charged work");
  const auto search_first = search.advance(WorkQuantum{1, {}});
  const auto search_after_first = search.progress();
  check(search_first.stopped_for == StopReason::quantum_work &&
            search_after_first.producer.attempted > search_zero_after.producer.attempted &&
            search_after_first.producer.active_nanoseconds > 0,
        "nonzero search grant did not record active work");
  const auto search_time_before_idle = total_active_time(search_after_first);
  const auto search_attempts_before_idle = search_after_first.producer.attempted +
      search_after_first.replay.attempted;
  std::this_thread::sleep_for(2500ms);
  const auto search_after_idle = search.progress();
  check(total_active_time(search_after_idle) == search_time_before_idle &&
            search_after_idle.producer.attempted + search_after_idle.replay.attempted ==
                search_attempts_before_idle,
        "caller idle time was charged to the search continuation");
  const auto search_second = search.advance(WorkQuantum{1, {}});
  const auto search_after_second = search.progress();
  check(search_second.stopped_for != StopReason::total_time &&
            search_after_second.producer.attempted == search_after_idle.producer.attempted + 1 &&
            total_active_time(search_after_second) >= search_time_before_idle,
        "search did not resume after caller idle exceeded its active-time ceiling");

  ReplayOptions replay_options;
  replay_options.limits.active_time = 2s;
  auto replay = CertificateReplay::create(fixture.catalog, fixture.query, certificate, replay_options);
  const auto admitted_replay = replay.progress();
  check(admitted_replay.work.active_nanoseconds == 0,
        "replay admission was charged as active continuation time");
  const auto replay_zero_before = replay.progress();
  const auto replay_zero = replay.advance(WorkQuantum{0, {}});
  const auto replay_zero_after = replay.progress();
  check(replay_zero.stopped_for == StopReason::quantum_work &&
            replay_zero_before.work == replay_zero_after.work,
        "zero-work replay grant sampled active time or charged work");
  const auto replay_first = replay.advance(WorkQuantum{1, {}});
  const auto replay_after_first = replay.progress();
  check(replay_first.stopped_for == StopReason::quantum_work &&
            replay_after_first.work.attempted > replay_zero_after.work.attempted &&
            replay_after_first.work.active_nanoseconds > 0,
        "nonzero replay grant did not record active work");
  const auto replay_time_before_idle = replay_after_first.work.active_nanoseconds;
  const auto replay_attempts_before_idle = replay_after_first.work.attempted;
  std::this_thread::sleep_for(2500ms);
  const auto replay_after_idle = replay.progress();
  check(replay_after_idle.work.active_nanoseconds == replay_time_before_idle &&
            replay_after_idle.work.attempted == replay_attempts_before_idle,
        "caller idle time was charged to the replay continuation");
  const auto replay_second = replay.advance(WorkQuantum{1, {}});
  const auto replay_after_second = replay.progress();
  check(replay_second.stopped_for != StopReason::total_time &&
            replay_after_second.work.attempted == replay_after_idle.work.attempted + 1 &&
            replay_after_second.work.active_nanoseconds >= replay_time_before_idle,
        "replay did not resume after caller idle exceeded its active-time ceiling");
}

Fixture nested_chain(std::size_t count) {
  std::vector<std::vector<std::size_t>> scopes;
  scopes.reserve(count);
  for (std::size_t length = count; length > 0; --length) {
    std::vector<std::size_t> scope;
    scope.reserve(length);
    for (std::size_t variable = 0; variable < length; ++variable)
      scope.push_back(variable);
    scopes.push_back(std::move(scope));
  }
  return fixture_for(scopes, {0});
}

SearchProgress finish_varied_search(ExactSearch& owner) {
  constexpr std::array<std::uint64_t, 5> grants{7, 31, 127, 509, 1021};
  std::size_t next = 0;
  for (;;) {
    const auto advanced = owner.advance(WorkQuantum{grants[next % grants.size()], {}});
    ++next;
    if (advanced.stopped_for == StopReason::complete) return advanced.progress;
    check(advanced.stopped_for == StopReason::quantum_work &&
              advanced.progress.result != ResultKind::failed,
          "unbounded-depth nested-chain search stopped before proof completion");
  }
}

void deep_hierarchy_handle_survives_owner_teardown() {
  constexpr std::size_t count = 150;
  const auto fixture = nested_chain(count);
  SearchOptions options;
  options.policy = SearchPolicy::best_found;
  options.limits.producer.work = std::nullopt;
  options.limits.replay.work = std::nullopt;
  options.limits.logical_depth = std::nullopt;

  std::optional<ValidatedIncumbent> retained;
  {
    auto owner = ExactSearch::create(fixture.catalog, fixture.query, options);
    const auto completed = finish_varied_search(owner);
    check(completed.result == ResultKind::verified_optimum && completed.proof_complete &&
              completed.producer_complete && completed.heights.lower == 1 &&
              completed.heights.upper == 1,
          "150-scope nested hierarchy did not finish at height one without a depth ceiling");
    const auto optimum = owner.optimum();
    check(optimum && optimum->valid() && optimum->height() == 1,
          "deep nested hierarchy did not publish a verified optimum");
    retained = owner.incumbent();
    check(retained && retained->valid() && retained->height() == 1,
          "deep nested hierarchy did not retain its validated incumbent handle");
    const auto& tree = retained->tree();
    std::size_t native = 0;
    std::size_t generalized = 0;
    for (const auto& node : tree.nodes) {
      if (node.kind == NodeKind::native) ++native;
      else ++generalized;
    }
    check(native == count && generalized > 0 && tree.nodes.size() > count,
          "deep nested witness did not preserve its native and generalized ChoiceArena payload");
  }

  check(retained && retained->valid() && retained->height() == 1,
        "destroying the deep search owner invalidated the retained incumbent handle");
  const auto checked_tree = validate_tree(fixture.catalog, fixture.query, retained->tree());
  check(checked_tree.valid && checked_tree.native_height == 1,
        "deep incumbent tree became invalid after ChoiceArena owner teardown");
}

void run() {
  const auto connected = fixture_for({{0, 1}, {0, 1}, {1}}, {0});
  const auto exact_baseline = minimum_tree(connected.catalog, connected.query);
  check(exact_baseline.status == OracleStatus::proven_minimum && exact_baseline.minimum_height == 2,
        "small continuation fixture lost its expected height-two minimum");
  const auto certificate = certificate_for(exact_baseline);

  compatibility_report_describes_checked_evidence(connected, certificate);
  empty_body_depth_zero();
  zero_depth_nonempty_retains_and_resumes(connected, certificate);
  cancellation_preserves_work_history_and_claims(connected, certificate);
  replay_rejects_corrupt_v1(connected);
  active_time_excludes_admission_and_idle(connected, certificate);
  deep_hierarchy_handle_survives_owner_teardown();
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "P06 continuation edge cases passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}

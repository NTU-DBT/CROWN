#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// Faults direct ordinary/nothrow scalar/array new via malloc-backed replacements.
// No aligned replacement; indirect delegation is unasserted; direct malloc/realloc,
// system calls, and MemoryAccount denials are outside this seam.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocation_count = 0;

[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  ++allocation_count;
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

struct FaultScope {
  explicit FaultScope(std::ptrdiff_t point) noexcept { fail_after = point; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return malloc_new(bytes); }
  catch (const std::bad_alloc&) { return nullptr; }
}
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return malloc_new(bytes); }
  catch (const std::bad_alloc&) { return nullptr; }
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::planner;

static_assert(std::is_nothrow_destructible_v<ExactSearch>);
static_assert(std::is_nothrow_destructible_v<CertificateReplay>);
static_assert(std::is_nothrow_destructible_v<SearchBinding>);
static_assert(std::is_nothrow_destructible_v<ValidatedIncumbent>);
static_assert(std::is_nothrow_destructible_v<VerifiedOptimum>);
static_assert(std::is_nothrow_destructible_v<VerifiedInfeasible>);
static_assert(std::is_nothrow_destructible_v<CheckedCertificate>);

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

bool same_constraint(const Constraint& left, const Constraint& right) {
  if (left.index() != right.index()) return false;
  if (const auto* a = std::get_if<UniqueConstraint>(&left)) {
    const auto& b = std::get<UniqueConstraint>(right);
    return a->name == b.name && a->columns == b.columns && a->status == b.status;
  }
  const auto& a = std::get<ForeignKeyConstraint>(left);
  const auto& b = std::get<ForeignKeyConstraint>(right);
  return a.name == b.name && a.columns == b.columns &&
         a.referenced_table == b.referenced_table &&
         a.referenced_columns == b.referenced_columns && a.status == b.status;
}

bool same_catalog(const Catalog& left, const Catalog& right) {
  if (left.version != right.version || left.tables.size() != right.tables.size()) return false;
  for (std::size_t i = 0; i < left.tables.size(); ++i) {
    const auto& a = left.tables[i];
    const auto& b = right.tables[i];
    if (a.name != b.name || a.source_schema_version != b.source_schema_version ||
        a.columns.size() != b.columns.size() || a.constraints.size() != b.constraints.size() ||
        a.statistics.row_count != b.statistics.row_count ||
        a.statistics.distinct_counts.size() != b.statistics.distinct_counts.size() ||
        a.key_hints.size() != b.key_hints.size()) return false;
    for (std::size_t j = 0; j < a.columns.size(); ++j) {
      const auto& x = a.columns[j];
      const auto& y = b.columns[j];
      if (x.name != y.name || x.type != y.type || x.nullable != y.nullable ||
          x.collation != y.collation || x.decimal != y.decimal) return false;
    }
    for (std::size_t j = 0; j < a.constraints.size(); ++j)
      if (!same_constraint(a.constraints[j], b.constraints[j])) return false;
    for (std::size_t j = 0; j < a.statistics.distinct_counts.size(); ++j) {
      const auto& x = a.statistics.distinct_counts[j];
      const auto& y = b.statistics.distinct_counts[j];
      if (x.columns != y.columns || x.estimate != y.estimate) return false;
    }
    for (std::size_t j = 0; j < a.key_hints.size(); ++j) {
      const auto& x = a.key_hints[j];
      const auto& y = b.key_hints[j];
      if (x.columns != y.columns || x.reason != y.reason) return false;
    }
  }
  return true;
}

bool same_term(const Term& left, const Term& right) {
  if (left.index() != right.index()) return false;
  if (const auto* variable = std::get_if<VariableId>(&left))
    return *variable == std::get<VariableId>(right);
  if (const auto* value = std::get_if<Value>(&left))
    return *value == std::get<Value>(right);
  return true;
}

bool same_query(const Query& left, const Query& right) {
  if (left.contradiction != right.contradiction ||
      left.variables.size() != right.variables.size() ||
      left.atoms.size() != right.atoms.size() || left.head.size() != right.head.size()) return false;
  for (std::size_t i = 0; i < left.variables.size(); ++i)
    if (left.variables[i].name != right.variables[i].name ||
        left.variables[i].type != right.variables[i].type) return false;
  for (std::size_t i = 0; i < left.atoms.size(); ++i) {
    const auto& a = left.atoms[i];
    const auto& b = right.atoms[i];
    if (a.occurrence != b.occurrence || a.table != b.table || a.terms.size() != b.terms.size()) return false;
    for (std::size_t j = 0; j < a.terms.size(); ++j)
      if (!same_term(a.terms[j], b.terms[j])) return false;
  }
  for (std::size_t i = 0; i < left.head.size(); ++i)
    if (left.head[i].variable != right.head[i].variable || left.head[i].alias != right.head[i].alias) return false;
  return true;
}

bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
  if (left.root != right.root || left.claimed_connex != right.claimed_connex ||
      left.claimed_native_height != right.claimed_native_height ||
      left.nodes.size() != right.nodes.size()) return false;
  for (std::size_t i = 0; i < left.nodes.size(); ++i) {
    const auto& a = left.nodes[i];
    const auto& b = right.nodes[i];
    if (a.id != b.id || a.kind != b.kind || a.scope != b.scope ||
        a.children != b.children || a.occurrence != b.occurrence ||
        a.claimed_separator != b.claimed_separator) return false;
  }
  return true;
}

bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) {
  if (left.algorithm != right.algorithm || left.minimum_height != right.minimum_height ||
      left.tree.has_value() != right.tree.has_value() ||
      left.lower_bounds.size() != right.lower_bounds.size()) return false;
  if (left.tree && !same_tree(*left.tree, *right.tree)) return false;
  for (std::size_t i = 0; i < left.lower_bounds.size(); ++i) {
    const auto& a = left.lower_bounds[i];
    const auto& b = right.lower_bounds[i];
    if (a.occurrences != b.occurrences || a.generalized_allowed != b.generalized_allowed ||
        a.connex_reachable != b.connex_reachable || a.bound != b.bound) return false;
  }
  return true;
}

bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) {
  return a.work == b.work && a.states == b.states && a.partitions == b.partitions &&
      a.candidates == b.candidates && a.cache_hits == b.cache_hits &&
      a.certificate_work == b.certificate_work && a.hierarchy_tests == b.hierarchy_tests &&
      a.hierarchy_hits == b.hierarchy_hits && a.singleton_hits == b.singleton_hits &&
      a.empty_body_hits == b.empty_body_hits && a.component_splits == b.component_splits &&
      a.symmetry_skips == b.symmetry_skips && a.bound_prunes == b.bound_prunes;
}

bool same_statistics_shape(const SearchStatistics& a, const SearchStatistics& b) {
  // P06 fills these compatibility fields from attempted counters, which must
  // increase on every persistent-failure retry.
  return a.states == b.states && a.partitions == b.partitions &&
      a.candidates == b.candidates && a.cache_hits == b.cache_hits &&
      a.hierarchy_tests == b.hierarchy_tests && a.hierarchy_hits == b.hierarchy_hits &&
      a.singleton_hits == b.singleton_hits && a.empty_body_hits == b.empty_body_hits &&
      a.component_splits == b.component_splits && a.symmetry_skips == b.symmetry_skips &&
      a.bound_prunes == b.bound_prunes;
}

bool same_search_shape(const SearchProgress& a, const SearchProgress& b) {
  // Attempted/failed counts, active time and last_stop legitimately change
  // when a retry is made. The saved cursor, bounds and committed work do not.
  return a.phase == b.phase && a.result == b.result && a.heights == b.heights &&
      a.producer_complete == b.producer_complete && a.proof_complete == b.proof_complete &&
      a.producer.committed_transitions == b.producer.committed_transitions &&
      a.producer.current_depth == b.producer.current_depth &&
      a.producer.peak_depth == b.producer.peak_depth &&
      a.replay.committed_transitions == b.replay.committed_transitions &&
      a.replay.current_depth == b.replay.current_depth &&
      a.replay.peak_depth == b.replay.peak_depth &&
      same_statistics_shape(a.structural, b.structural) && a.limit_revision == b.limit_revision;
}

bool same_search_progress(const SearchProgress& a, const SearchProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result &&
      a.heights == b.heights && a.producer_complete == b.producer_complete &&
      a.proof_complete == b.proof_complete && a.producer == b.producer &&
      a.replay == b.replay && same_statistics(a.structural, b.structural) &&
      a.limit_revision == b.limit_revision;
}

bool same_replay_shape(const ReplayProgress& a, const ReplayProgress& b) {
  // Repeated OOM retries advance only attempted/failure diagnostics.
  return a.phase == b.phase && a.complete == b.complete && a.valid == b.valid &&
      a.checked_claims == b.checked_claims &&
      a.work.committed_transitions == b.work.committed_transitions &&
      a.work.current_depth == b.work.current_depth && a.work.peak_depth == b.work.peak_depth &&
      a.limit_revision == b.limit_revision;
}

bool same_replay_progress(const ReplayProgress& a, const ReplayProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.complete == b.complete &&
      a.valid == b.valid && a.checked_claims == b.checked_claims && a.work == b.work &&
      a.limit_revision == b.limit_revision;
}

std::uint64_t attempted_total(const SearchProgress& p) {
  return p.producer.attempted + p.replay.attempted;
}
std::uint64_t committed_total(const SearchProgress& p) {
  return p.producer.committed_transitions + p.replay.committed_transitions;
}
std::uint64_t failures_total(const SearchProgress& p) {
  return p.producer.allocation_failures + p.replay.allocation_failures;
}

HeightCertificate certificate_for(const OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}

SearchOptions best_found_options() {
  SearchOptions options;
  options.policy = SearchPolicy::best_found;
  return options;
}

constexpr WorkQuantum whole_quantum{std::numeric_limits<std::uint64_t>::max(), {}};

struct ReplacementPoint {
  std::size_t allocation = 0;
  std::size_t old_height = 0;
  FreeConnexTree old_tree;
};

struct ExactBaseline {
  SearchProgress progress;
  HeightCertificate certificate;
  std::vector<ReplacementPoint> replacements;
  std::size_t advance_allocations = 0;
  bool infeasible = false;
};

ExactBaseline calibrate_exact(const Fixture& fixture) {
  // Admission precedes calibration, so the count measures advance only.
  auto owner = ExactSearch::create(fixture.catalog, fixture.query, best_found_options());
  ExactBaseline result;
  for (;;) {
    const auto old_incumbent = owner.incumbent();
    allocation_count = 0;
    const auto advanced = owner.advance(WorkQuantum{1, {}});
    const auto step_allocations = allocation_count;
    const auto allocation_base = result.advance_allocations;
    result.advance_allocations += step_allocations;
    const auto new_incumbent = owner.incumbent();
    if (old_incumbent && new_incumbent && new_incumbent->height() < old_incumbent->height()) {
      result.replacements.push_back({allocation_base, old_incumbent->height(), old_incumbent->tree()});
    }
    if (advanced.stopped_for == StopReason::complete) break;
    check(advanced.stopped_for == StopReason::quantum_work,
          "exact continuation calibration stopped before completion");
  }
  result.progress = owner.progress();
  check(result.progress.result == ResultKind::verified_optimum ||
            result.progress.result == ResultKind::verified_infeasible,
        "exact continuation calibration did not publish a typed final authority");
  result.infeasible = result.progress.result == ResultKind::verified_infeasible;
  if (result.infeasible) {
    const auto authority = owner.infeasibility();
    check(authority && authority->valid(), "infeasible calibration lost its typed authority");
    result.certificate = authority->certificate();
  } else {
    const auto authority = owner.optimum();
    check(authority && authority->valid(), "optimum calibration lost its typed authority");
    result.certificate = authority->certificate();
  }
  check(result.advance_allocations > 0, "exact continuation calibration observed no advance allocations");
  check(result.advance_allocations <= static_cast<std::size_t>(
            std::numeric_limits<std::ptrdiff_t>::max()),
        "exact continuation allocation count exceeds fault-index range");
  return result;
}

void check_exact_final(const ExactSearch& owner, const ExactBaseline& baseline) {
  const auto progress = owner.progress();
  check(progress.phase == SearchPhase::complete && progress.proof_complete,
        "resumed exact continuation did not complete its independent proof");
  if (baseline.infeasible) {
    check(progress.result == ResultKind::verified_infeasible && progress.heights.infeasible,
          "resumed search returned the wrong infeasibility type");
    check(!owner.optimum(), "infeasible continuation published an optimum handle");
    const auto authority = owner.infeasibility();
    check(authority && authority->valid() && same_certificate(authority->certificate(), baseline.certificate),
          "resumed infeasibility proof differs from uninterrupted completion");
  } else {
    check(progress.result == ResultKind::verified_optimum && !progress.heights.infeasible &&
              progress.heights.lower == baseline.certificate.minimum_height &&
              progress.heights.upper == baseline.certificate.minimum_height,
          "resumed search returned the wrong optimum interval");
    check(!owner.infeasibility(), "optimal continuation published an infeasibility handle");
    const auto authority = owner.optimum();
    check(authority && authority->valid() && authority->height() == baseline.certificate.minimum_height &&
              same_certificate(authority->certificate(), baseline.certificate),
          "resumed optimum proof differs from uninterrupted completion");
  }
}

bool same_incumbent(const std::optional<ValidatedIncumbent>& a,
                    const std::optional<ValidatedIncumbent>& b) {
  if (a.has_value() != b.has_value()) return false;
  return !a || (a->valid() && b->valid() && a->height() == b->height() &&
                same_tree(a->tree(), b->tree()));
}

void exact_oom_sweep(const Fixture& fixture, const ExactBaseline& baseline,
                     const char* label, bool require_replacement) {
  const auto catalog_before = fixture.catalog;
  const auto query_before = fixture.query;
  check(!require_replacement || !baseline.replacements.empty(),
        "replacement fixture did not improve a previously validated incumbent");

  std::size_t fault_positions = 0;
  bool replacement_failure_seen = false;
  std::size_t maximum_fault_attempt_allocations = 0;
  for (std::size_t point = 0; point <= baseline.advance_allocations; ++point) {
    // Owner creation and all input copies happen before persistent failure.
    auto owner = ExactSearch::create(fixture.catalog, fixture.query, best_found_options());
    allocation_count = 0;
    bool correct_stop = false;
    bool no_partial_authority = false;
    bool stable_retries = false;
    bool zero_quantum_unchanged = false;
    bool noalloc_facade_and_handles = false;
    bool binding_unchanged = false;
    bool old_incumbent_retained = false;
    bool replacement_failure_here = require_replacement &&
        point == baseline.replacements.front().allocation;
    std::size_t attempt_allocations = 0;

    if (point == baseline.advance_allocations) {
      SearchAdvance completed;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        completed = owner.advance(whole_quantum);
        attempt_allocations = allocation_count;
        correct_stop = completed.stopped_for == StopReason::complete;
        no_partial_authority = owner.progress().result == baseline.progress.result;
      }
      const bool point_n_valid = correct_stop && no_partial_authority &&
          attempt_allocations == baseline.advance_allocations;
      if (!point_n_valid) {
        const auto p = owner.progress();
        std::cerr << label << " exact point=" << point << " N-check stop=" << correct_stop
                  << " authority=" << no_partial_authority << " allocs=" << attempt_allocations
                  << '/' << baseline.advance_allocations << " phase=" << static_cast<int>(p.phase)
                  << " result=" << static_cast<int>(p.result) << " producer_attempted="
                  << p.producer.attempted << " replay_attempted=" << p.replay.attempted << '\n';
      }
      check(point_n_valid,
            "allocation position N did not finish while every observed allocation succeeded");
      check_exact_final(owner, baseline);
    } else {
      SearchProgress first_progress;
      SearchProgress second_progress;
      SearchProgress third_progress;
      std::optional<ValidatedIncumbent> first_incumbent;
      std::size_t count_before_noalloc = 0;
      bool typed_getters_empty = false;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        const auto first = owner.advance(whole_quantum);
        first_progress = owner.progress();
        first_incumbent = owner.incumbent();
        correct_stop = first.stopped_for == StopReason::allocation_failure &&
            first_progress.last_stop == StopReason::allocation_failure;
        no_partial_authority = first_progress.result == ResultKind::unfinished &&
            !first_progress.proof_complete;

        // This is the first intercepted new request in the transition whose clean
        // one-quantum calibration publishes the next strictly better incumbent.
        if (replacement_failure_here) {
          const auto& previous = baseline.replacements.front();
          old_incumbent_retained = first_incumbent &&
              first_incumbent->height() == previous.old_height &&
              same_tree(first_incumbent->tree(), previous.old_tree);
        } else {
          old_incumbent_retained = true;
        }

        const auto repeat_one = owner.advance(whole_quantum);
        second_progress = owner.progress();
        const auto repeat_two = owner.advance(whole_quantum);
        third_progress = owner.progress();
        stable_retries = repeat_one.stopped_for == StopReason::allocation_failure &&
            repeat_two.stopped_for == StopReason::allocation_failure &&
            same_search_shape(first_progress, second_progress) &&
            same_search_shape(first_progress, third_progress) &&
            second_progress.producer.attempted == first_progress.producer.attempted +
                (first_progress.phase < SearchPhase::replay ? 1U : 0U) &&
            second_progress.replay.attempted == first_progress.replay.attempted +
                (first_progress.phase >= SearchPhase::replay ? 1U : 0U) &&
            second_progress.producer.allocation_failures == first_progress.producer.allocation_failures +
                (first_progress.phase < SearchPhase::replay ? 1U : 0U) &&
            second_progress.replay.allocation_failures == first_progress.replay.allocation_failures +
                (first_progress.phase >= SearchPhase::replay ? 1U : 0U) &&
            third_progress.producer.attempted == second_progress.producer.attempted +
                (second_progress.phase < SearchPhase::replay ? 1U : 0U) &&
            third_progress.replay.attempted == second_progress.replay.attempted +
                (second_progress.phase >= SearchPhase::replay ? 1U : 0U) &&
            third_progress.producer.allocation_failures == second_progress.producer.allocation_failures +
                (second_progress.phase < SearchPhase::replay ? 1U : 0U) &&
            third_progress.replay.allocation_failures == second_progress.replay.allocation_failures +
                (second_progress.phase >= SearchPhase::replay ? 1U : 0U);

        count_before_noalloc = allocation_count;
        const auto retained_incumbent = owner.incumbent();
        const auto unpublished_optimum = owner.optimum();
        const auto unpublished_infeasibility = owner.infeasibility();
        typed_getters_empty = !unpublished_optimum && !unpublished_infeasibility;
        stable_retries = stable_retries && third_progress.last_stop == StopReason::allocation_failure &&
            same_incumbent(first_incumbent, retained_incumbent);
        const auto before_zero = owner.progress();
        const auto zero = owner.advance(WorkQuantum{0, {}});
        const auto after_zero = owner.progress();
        zero_quantum_unchanged = zero.stopped_for == StopReason::quantum_work &&
            same_search_progress(before_zero, after_zero) &&
            same_search_progress(before_zero, zero.progress);

        // Owned-handle copies, binding views and moves are all heap independent.
        auto binding = owner.binding();
        auto binding_copy = binding;
        const auto best = owner.incumbent();
        std::optional<ValidatedIncumbent> best_copy{};
        if (best) best_copy.emplace(*best);
        binding_unchanged = binding.valid() && binding_copy.valid() &&
            same_catalog(binding.catalog(), fixture.catalog) &&
            same_query(binding.query(), fixture.query) &&
            same_catalog(binding_copy.catalog(), fixture.catalog) &&
            same_query(binding_copy.query(), fixture.query);
        const auto before_move = owner.progress();
        auto moved = std::move(owner);
        const auto moved_progress = moved.progress();
        owner = std::move(moved);
        const auto after_move = owner.progress();
        noalloc_facade_and_handles = best_copy.has_value() == best.has_value() &&
            same_search_progress(before_move, moved_progress) &&
            same_search_progress(before_move, after_move);
        attempt_allocations = allocation_count;
      }
      maximum_fault_attempt_allocations = std::max(maximum_fault_attempt_allocations,
                                                    attempt_allocations);
      noalloc_facade_and_handles = noalloc_facade_and_handles &&
          attempt_allocations == count_before_noalloc;
      const bool fault_point_valid = correct_stop && no_partial_authority && stable_retries &&
                zero_quantum_unchanged && noalloc_facade_and_handles &&
                binding_unchanged && old_incumbent_retained && typed_getters_empty;
      if (!fault_point_valid) {
        std::cerr << label << " exact point=" << point << " flags stop=" << correct_stop
                  << " no_partial=" << no_partial_authority << " retries=" << stable_retries
                  << " zero=" << zero_quantum_unchanged << " noalloc=" << noalloc_facade_and_handles
                  << " binding=" << binding_unchanged << " old_incumbent=" << old_incumbent_retained
                  << " typed_empty=" << typed_getters_empty << " phase="
                  << static_cast<int>(third_progress.phase) << " producer_attempted="
                  << third_progress.producer.attempted << " producer_committed="
                  << third_progress.producer.committed_transitions << " producer_failures="
                  << third_progress.producer.allocation_failures << " replay_attempted="
                  << third_progress.replay.attempted << " replay_committed="
                  << third_progress.replay.committed_transitions << " replay_failures="
                  << third_progress.replay.allocation_failures << " allocations="
                  << attempt_allocations << '\n';
      }
      check(fault_point_valid,
            "persistent search OOM escaped, published partial authority, moved progress, or allocated in facade operations");
      ++fault_positions;
      if (replacement_failure_here) replacement_failure_seen = true;

      // The owner that hit OOM is resumed in place after disarming the fault.
      allocation_count = 0;
      const auto resumed = owner.advance(whole_quantum);
      const auto final_progress = owner.progress();
      check(resumed.stopped_for == StopReason::complete,
            "same exact-search owner did not complete after OOM was disarmed");
      check_exact_final(owner, baseline);
      check(committed_total(final_progress) == committed_total(baseline.progress) &&
                attempted_total(final_progress) == attempted_total(baseline.progress) + 3 &&
                failures_total(final_progress) == failures_total(baseline.progress) + 3,
            "resumed exact search restarted work or lost monotone failure accounting");
    }
    check(same_catalog(fixture.catalog, catalog_before) && same_query(fixture.query, query_before),
          "exact-search admission or recovery changed caller-owned inputs");
  }
  check(fault_positions == baseline.advance_allocations,
        "persistent exact-search sweep missed an observed allocation position");
  check(!require_replacement || replacement_failure_seen,
        "OOM in the better-incumbent transition fault did not retain the previous validated incumbent");
  std::cout << label << " fault_positions=" << fault_positions
            << " successful_advance_allocations=" << baseline.advance_allocations
            << " maximum_faulted_advance_allocations=" << maximum_fault_attempt_allocations
            << " better_incumbent_transition_fault=" << (replacement_failure_seen ? "yes" : "no") << '\n';
}

void check_replay_final(const CertificateReplay& owner, const HeightCertificate& expected) {
  const auto progress = owner.progress();
  check(progress.phase == ReplayPhase::complete && progress.complete && progress.valid &&
            progress.checked_claims == expected.lower_bounds.size(),
        "resumed certificate replay did not finish every proof claim");
  const auto checked = owner.checked();
  check(checked && checked->valid() && same_certificate(checked->certificate(), expected),
        "resumed replay authority differs from uninterrupted proof input");
  if (expected.tree) {
    const auto optimum = checked->optimum();
    check(optimum && optimum->valid() && optimum->height() == expected.minimum_height &&
              same_certificate(optimum->certificate(), expected),
          "replayed optimum authority differs from its independently checked proof");
    check(!checked->infeasibility(), "replayed optimum also published infeasibility");
  } else {
    const auto infeasible = checked->infeasibility();
    check(infeasible && infeasible->valid() && same_certificate(infeasible->certificate(), expected),
          "replayed infeasibility authority differs from its proof");
    check(!checked->optimum(), "replayed infeasibility also published an optimum");
  }
}

struct ReplayBaseline {
  ReplayProgress progress;
  std::size_t advance_allocations = 0;
  bool saw_order_claims = false;
};

ReplayBaseline calibrate_replay(const Fixture& fixture, const HeightCertificate& certificate) {
  // Certificate and owner admission are prepared before measuring advance.
  auto owner = CertificateReplay::create(fixture.catalog, fixture.query, certificate);
  ReplayBaseline result;
  for (;;) {
    allocation_count = 0;
    const auto advanced = owner.advance(WorkQuantum{1, {}});
    result.advance_allocations += allocation_count;
    const auto progress = owner.progress();
    result.saw_order_claims = result.saw_order_claims || progress.phase == ReplayPhase::order_claims;
    if (advanced.stopped_for == StopReason::complete) break;
    check(advanced.stopped_for == StopReason::quantum_work,
          "certificate replay calibration stopped before completion");
  }
  result.progress = owner.progress();
  check(result.progress.complete && result.progress.valid && owner.checked(),
        "certificate replay calibration did not publish checked authority");
  check(result.progress.checked_claims == certificate.lower_bounds.size(),
        "certificate replay calibration omitted lower-bound claims");
  check(result.advance_allocations > 0, "certificate replay calibration observed no advance allocations");
  check(result.advance_allocations <= static_cast<std::size_t>(
            std::numeric_limits<std::ptrdiff_t>::max()),
        "certificate replay allocation count exceeds fault-index range");
  return result;
}

void replay_oom_sweep(const Fixture& fixture, const HeightCertificate& certificate,
                      const ReplayBaseline& baseline, const char* label) {
  const auto catalog_before = fixture.catalog;
  const auto query_before = fixture.query;
  const auto certificate_before = certificate;
  check(certificate.lower_bounds.size() > 1,
        "replay phase coverage needs a multi-claim certificate");
  check(baseline.saw_order_claims, "replay calibration did not enter proof-claim ordering");

  std::size_t fault_positions = 0;
  bool index_publication_failure = false;
  bool dependency_publication_failure = false;
  bool final_authority_failure = false;
  std::size_t maximum_fault_attempt_allocations = 0;
  for (std::size_t point = 0; point <= baseline.advance_allocations; ++point) {
    auto owner = CertificateReplay::create(fixture.catalog, fixture.query, certificate);
    allocation_count = 0;
    bool correct_stop = false;
    bool no_partial_authority = false;
    bool stable_retries = false;
    bool zero_quantum_unchanged = false;
    bool noalloc_facade_and_handles = false;
    bool binding_unchanged = false;
    std::size_t attempt_allocations = 0;
    if (point == baseline.advance_allocations) {
      ReplayAdvance completed;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        completed = owner.advance(whole_quantum);
        attempt_allocations = allocation_count;
        correct_stop = completed.stopped_for == StopReason::complete;
        const auto progress = owner.progress();
        no_partial_authority = progress.complete && progress.valid && owner.checked();
      }
      const bool point_n_valid = correct_stop && no_partial_authority &&
          attempt_allocations == baseline.advance_allocations;
      if (!point_n_valid) {
        const auto p = owner.progress();
        std::cerr << label << " replay point=" << point << " N-check stop=" << correct_stop
                  << " authority=" << no_partial_authority << " allocs=" << attempt_allocations
                  << '/' << baseline.advance_allocations << " phase=" << static_cast<int>(p.phase)
                  << " checked=" << p.checked_claims << " attempted=" << p.work.attempted
                  << " committed=" << p.work.committed_transitions << " failures="
                  << p.work.allocation_failures << '\n';
      }
      check(point_n_valid,
            "replay allocation position N did not finish while all observed allocations succeeded");
      check_replay_final(owner, certificate);
    } else {
      ReplayProgress first_progress;
      ReplayProgress second_progress;
      ReplayProgress third_progress;
      std::size_t count_before_noalloc = 0;
      bool checked_getter_empty = false;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        const auto first = owner.advance(whole_quantum);
        first_progress = owner.progress();
        correct_stop = first.stopped_for == StopReason::allocation_failure &&
            first_progress.last_stop == StopReason::allocation_failure;
        no_partial_authority = !first_progress.complete && !first_progress.valid &&
            first_progress.checked_claims <= certificate.lower_bounds.size();
        if (first_progress.phase == ReplayPhase::index_claims)
          index_publication_failure = true;
        if (first_progress.phase == ReplayPhase::prove_claim && first_progress.checked_claims > 0)
          dependency_publication_failure = true;
        if (first_progress.phase == ReplayPhase::match_root &&
            first_progress.checked_claims == certificate.lower_bounds.size())
          final_authority_failure = true;

        const auto repeat_one = owner.advance(whole_quantum);
        second_progress = owner.progress();
        const auto repeat_two = owner.advance(whole_quantum);
        third_progress = owner.progress();
        stable_retries = repeat_one.stopped_for == StopReason::allocation_failure &&
            repeat_two.stopped_for == StopReason::allocation_failure &&
            same_replay_shape(first_progress, second_progress) &&
            same_replay_shape(first_progress, third_progress) &&
            second_progress.work.attempted == first_progress.work.attempted + 1 &&
            third_progress.work.attempted == second_progress.work.attempted + 1 &&
            second_progress.work.allocation_failures == first_progress.work.allocation_failures + 1 &&
            third_progress.work.allocation_failures == second_progress.work.allocation_failures + 1;

        count_before_noalloc = allocation_count;
        const auto unpublished = owner.checked();
        checked_getter_empty = !unpublished;
        stable_retries = stable_retries && third_progress.last_stop == StopReason::allocation_failure;
        const auto before_zero = owner.progress();
        const auto zero = owner.advance(WorkQuantum{0, {}});
        const auto after_zero = owner.progress();
        zero_quantum_unchanged = zero.stopped_for == StopReason::quantum_work &&
            same_replay_progress(before_zero, after_zero) &&
            same_replay_progress(before_zero, zero.progress);

        auto binding = owner.binding();
        auto binding_copy = binding;
        binding_unchanged = binding.valid() && binding_copy.valid() &&
            same_catalog(binding.catalog(), fixture.catalog) &&
            same_query(binding.query(), fixture.query) &&
            same_catalog(binding_copy.catalog(), fixture.catalog) &&
            same_query(binding_copy.query(), fixture.query) &&
            same_certificate(certificate, certificate_before);
        const auto before_move = owner.progress();
        auto moved = std::move(owner);
        const auto moved_progress = moved.progress();
        owner = std::move(moved);
        const auto after_move = owner.progress();
        noalloc_facade_and_handles = same_replay_progress(before_move, moved_progress) &&
            same_replay_progress(before_move, after_move);
        attempt_allocations = allocation_count;
      }
      maximum_fault_attempt_allocations = std::max(maximum_fault_attempt_allocations,
                                                    attempt_allocations);
      noalloc_facade_and_handles = noalloc_facade_and_handles &&
          attempt_allocations == count_before_noalloc;
      const bool fault_point_valid = correct_stop && no_partial_authority && stable_retries &&
                zero_quantum_unchanged && noalloc_facade_and_handles && binding_unchanged &&
                checked_getter_empty;
      if (!fault_point_valid) {
        std::cerr << label << " replay point=" << point << " flags stop=" << correct_stop
                  << " no_partial=" << no_partial_authority << " retries=" << stable_retries
                  << " zero=" << zero_quantum_unchanged << " noalloc=" << noalloc_facade_and_handles
                  << " binding=" << binding_unchanged << " checked_empty=" << checked_getter_empty
                  << " phase=" << static_cast<int>(third_progress.phase) << " claims="
                  << third_progress.checked_claims << " attempted=" << third_progress.work.attempted
                  << " committed=" << third_progress.work.committed_transitions << " failures="
                  << third_progress.work.allocation_failures << " allocations="
                  << attempt_allocations << '\n';
      }
      check(fault_point_valid,
            "persistent replay OOM escaped, published a partial claim, changed state, or allocated in facade operations");
      ++fault_positions;

      allocation_count = 0;
      const auto resumed = owner.advance(whole_quantum);
      const auto final_progress = owner.progress();
      check(resumed.stopped_for == StopReason::complete,
            "same replay owner did not complete after OOM was disarmed");
      check_replay_final(owner, certificate);
      check(final_progress.work.committed_transitions == baseline.progress.work.committed_transitions &&
                final_progress.work.attempted == baseline.progress.work.attempted + 3 &&
                final_progress.work.allocation_failures == baseline.progress.work.allocation_failures + 3,
            "resumed replay restarted work or lost monotone failure accounting");
    }
    check(same_catalog(fixture.catalog, catalog_before) && same_query(fixture.query, query_before) &&
              same_certificate(certificate, certificate_before),
          "replay admission or recovery changed caller-owned input or certificate");
  }
  check(fault_positions == baseline.advance_allocations,
        "persistent replay sweep missed an observed allocation position");
  check(index_publication_failure,
        "allocation sweep did not fault while indexing/order-list publication was active");
  check(dependency_publication_failure,
        "allocation sweep did not fault while publishing a checked dependency claim");
  check(final_authority_failure,
        "allocation sweep did not fault after all claims at final authority publication");
  std::cout << label << " fault_positions=" << fault_positions
            << " successful_advance_allocations=" << baseline.advance_allocations
            << " maximum_faulted_advance_allocations=" << maximum_fault_attempt_allocations
            << " index_fault=" << (index_publication_failure ? "yes" : "no")
            << " dependency_fault=" << (dependency_publication_failure ? "yes" : "no")
            << " final_authority_fault=" << (final_authority_failure ? "yes" : "no") << '\n';
}

void search_nonallocating_lifecycle(const Fixture& fixture) {
  auto owner = ExactSearch::create(fixture.catalog, fixture.query, best_found_options());
  static_cast<void>(owner.advance(WorkQuantum{1, {}}));
  std::optional<ExactSearch> held;
  held.emplace(std::move(owner));
  allocation_count = 0;
  bool valid = false;
  std::size_t observed = 0;
  {
    FaultScope fault(0);
    const auto before = held->progress();
    const auto zero = held->advance(WorkQuantum{0, {}});
    const auto after = held->progress();
    auto binding = held->binding();
    auto binding_copy = binding;
    auto moved = std::move(*held);
    const auto moved_progress = moved.progress();
    *held = std::move(moved);
    const auto restored = held->progress();
    held->cancel();
    const auto cancelled = held->progress();
    held.reset();
    valid = zero.stopped_for == StopReason::quantum_work &&
        same_search_progress(before, after) && same_search_progress(before, zero.progress) &&
        same_search_progress(before, moved_progress) && same_search_progress(before, restored) &&
        binding.valid() && binding_copy.valid() && cancelled.phase == SearchPhase::cancelled;
    observed = allocation_count;
  }
  check(valid && observed == 0,
        "search progress, zero quantum, move, handle copy, cancel, or destruction allocated");
}

void replay_nonallocating_lifecycle(const Fixture& fixture, const HeightCertificate& certificate) {
  auto owner = CertificateReplay::create(fixture.catalog, fixture.query, certificate);
  static_cast<void>(owner.advance(WorkQuantum{1, {}}));
  std::optional<CertificateReplay> held;
  held.emplace(std::move(owner));
  allocation_count = 0;
  bool valid = false;
  std::size_t observed = 0;
  {
    FaultScope fault(0);
    const auto before = held->progress();
    const auto zero = held->advance(WorkQuantum{0, {}});
    const auto after = held->progress();
    auto binding = held->binding();
    auto binding_copy = binding;
    auto moved = std::move(*held);
    const auto moved_progress = moved.progress();
    *held = std::move(moved);
    const auto restored = held->progress();
    held->cancel();
    const auto cancelled = held->progress();
    held.reset();
    valid = zero.stopped_for == StopReason::quantum_work &&
        same_replay_progress(before, after) && same_replay_progress(before, zero.progress) &&
        same_replay_progress(before, moved_progress) && same_replay_progress(before, restored) &&
        binding.valid() && binding_copy.valid() && cancelled.phase == ReplayPhase::cancelled;
    observed = allocation_count;
  }
  check(valid && observed == 0,
        "replay progress, zero quantum, move, handle copy, cancel, or destruction allocated");
}

void exact_handle_copies_are_nonallocating(const Fixture& fixture, bool infeasible) {
  auto owner = ExactSearch::create(fixture.catalog, fixture.query, best_found_options());
  const auto done = owner.advance(whole_quantum);
  check(done.stopped_for == StopReason::complete, "handle-copy search fixture did not finish");
  auto binding = owner.binding();
  const auto incumbent = owner.incumbent();
  const auto optimum = owner.optimum();
  const auto impossible = owner.infeasibility();
  check(infeasible ? (impossible.has_value() && !optimum && !incumbent) :
                     (optimum.has_value() && incumbent.has_value() && !impossible),
        "handle-copy fixture published the wrong exact artifact type");

  allocation_count = 0;
  bool valid = false;
  std::size_t observed = 0;
  {
    FaultScope fault(0);
    auto binding_copy = binding;
    auto method_binding = owner.binding();
    const auto incumbent_copy = owner.incumbent();
    const auto optimum_copy = owner.optimum();
    const auto infeasible_copy = owner.infeasibility();
    bool artifact_copies_valid = true;
    if (incumbent) {
      auto copy = *incumbent;
      artifact_copies_valid = artifact_copies_valid && copy.valid() &&
          copy.height() == incumbent->height() && same_tree(copy.tree(), incumbent->tree()) &&
          copy.binding().valid();
    }
    if (optimum) {
      auto copy = *optimum;
      auto upper = copy.upper();
      artifact_copies_valid = artifact_copies_valid && copy.valid() && upper.valid() &&
          copy.height() == optimum->height() &&
          same_certificate(copy.certificate(), optimum->certificate()) && copy.binding().valid();
    }
    if (impossible) {
      auto copy = *impossible;
      artifact_copies_valid = artifact_copies_valid && copy.valid() &&
          same_certificate(copy.certificate(), impossible->certificate()) && copy.binding().valid();
    }
    valid = binding_copy.valid() && method_binding.valid() &&
        incumbent_copy.has_value() == incumbent.has_value() &&
        optimum_copy.has_value() == optimum.has_value() &&
        infeasible_copy.has_value() == impossible.has_value() && artifact_copies_valid;
    observed = allocation_count;
  }
  check(valid && observed == 0,
        "search artifact or owning-handle copy allocated under persistent OOM");
}

void replay_handle_copies_are_nonallocating(const Fixture& fixture,
                                            const HeightCertificate& certificate) {
  auto owner = CertificateReplay::create(fixture.catalog, fixture.query, certificate);
  const auto done = owner.advance(whole_quantum);
  check(done.stopped_for == StopReason::complete, "handle-copy replay fixture did not finish");
  const auto checked = owner.checked();
  check(checked && checked->valid(), "handle-copy replay fixture did not publish checked authority");

  allocation_count = 0;
  bool valid = false;
  std::size_t observed = 0;
  {
    FaultScope fault(0);
    auto checked_copy = *checked;
    auto binding = checked_copy.binding();
    auto binding_copy = binding;
    const auto optimum = checked_copy.optimum();
    const auto infeasible = checked_copy.infeasibility();
    bool typed_copy_valid = false;
    if (certificate.tree) {
      if (optimum) {
        auto copy = *optimum;
        typed_copy_valid = copy.valid() && copy.height() == certificate.minimum_height &&
            same_certificate(copy.certificate(), certificate) && copy.binding().valid();
      }
    } else if (infeasible) {
      auto copy = *infeasible;
      typed_copy_valid = copy.valid() && same_certificate(copy.certificate(), certificate) &&
          copy.binding().valid();
    }
    valid = checked_copy.valid() && binding.valid() && binding_copy.valid() &&
        same_certificate(checked_copy.certificate(), certificate) && typed_copy_valid;
    observed = allocation_count;
  }
  check(valid && observed == 0,
        "checked-certificate or owning-handle copy allocated under persistent OOM");
}

void validate_baseline_certificate(const Fixture& fixture, const HeightCertificate& certificate,
                                   const char* expected_algorithm) {
  check(certificate.algorithm == expected_algorithm,
        "baseline certificate has the unexpected algorithm version");
  const auto report = verify_height_certificate(fixture.catalog, fixture.query, certificate);
  check(report.valid && !report.resource_limit,
        "strict baseline certificate failed independent replay before OOM injection");
}

void run() {
  const auto hierarchical = fixture_for({{0, 1}, {0, 1}, {0}}, {0});
  const auto connected = fixture_for({{0, 1}, {0, 1}, {1}}, {0});
  const auto infeasible = fixture_for({{0, 1}, {1, 2}}, {0, 2});

  const auto hierarchy_before = planner::minimum_tree(hierarchical.catalog, hierarchical.query);
  check(hierarchy_before.status == OracleStatus::proven_minimum &&
            hierarchy_before.minimum_height == 1,
        "hierarchical P06 fixture lost its expected exact result");
  const auto hierarchy_baseline = calibrate_exact(hierarchical);
  check(hierarchy_baseline.progress.structural.hierarchy_hits > 0,
        "hierarchical continuation did not exercise hierarchy construction");
  validate_baseline_certificate(hierarchical, hierarchy_baseline.certificate,
                                "crown_partition_exact_v2");
  exact_oom_sweep(hierarchical, hierarchy_baseline, "owned_hierarchical_search", false);

  const auto connected_before = planner::minimum_tree(connected.catalog, connected.query);
  check(connected_before.status == OracleStatus::proven_minimum &&
            connected_before.minimum_height == 2,
        "connected duplicate-scope P06 fixture lost its expected exact result");
  const auto connected_baseline = calibrate_exact(connected);
  check(connected_baseline.progress.structural.states > 0 &&
            connected_baseline.progress.structural.symmetry_skips > 0,
        "connected continuation did not exercise non-hierarchical duplicate-scope search");
  check(!connected_baseline.replacements.empty(),
        "connected fixture did not publish a lower validated incumbent during search");
  validate_baseline_certificate(connected, connected_baseline.certificate,
                                "crown_partition_exact_v2");
  exact_oom_sweep(connected, connected_baseline, "owned_connected_duplicate_search", true);

  const auto infeasible_before = planner::minimum_tree(infeasible.catalog, infeasible.query);
  check(infeasible_before.status == OracleStatus::unsupported &&
            !infeasible_before.tree && !infeasible_before.minimum_height,
        "non-free-connex endpoint fixture did not produce the strict infeasible baseline");
  const auto infeasible_baseline = calibrate_exact(infeasible);
  check(infeasible_baseline.infeasible && !infeasible_baseline.certificate.tree &&
            !infeasible_baseline.certificate.minimum_height,
        "owned exact search did not preserve typed infeasibility");
  validate_baseline_certificate(infeasible, infeasible_baseline.certificate,
                                "crown_partition_exact_v2");
  exact_oom_sweep(infeasible, infeasible_baseline, "owned_infeasible_search", false);

  // Construct standalone proof inputs through the strict baseline APIs before
  // creating any replay owner or arming replacement-new failure.
  const auto v2_certificate = certificate_for(connected_before);
  validate_baseline_certificate(connected, v2_certificate, "crown_partition_exact_v2");
  const auto v2_replay_baseline = calibrate_replay(connected, v2_certificate);
  replay_oom_sweep(connected, v2_certificate, v2_replay_baseline,
                   "standalone_v2_certificate_replay");

#ifdef CROWN_PLANNER_TESTING
  const auto v1_result = testing::minimum_tree_baseline(connected.catalog, connected.query);
  check(v1_result.status == OracleStatus::proven_minimum && v1_result.minimum_height == 2,
        "strict v1 baseline did not produce the expected connected result");
  const auto v1_certificate = certificate_for(v1_result);
  validate_baseline_certificate(connected, v1_certificate, "crown_partition_exact_v1");
  const auto v1_replay_baseline = calibrate_replay(connected, v1_certificate);
  replay_oom_sweep(connected, v1_certificate, v1_replay_baseline,
                   "standalone_v1_certificate_replay");
#endif

  const auto infeasible_certificate = certificate_for(infeasible_before);
  validate_baseline_certificate(infeasible, infeasible_certificate, "crown_partition_exact_v2");
  const auto infeasible_replay_baseline = calibrate_replay(infeasible, infeasible_certificate);
  replay_oom_sweep(infeasible, infeasible_certificate, infeasible_replay_baseline,
                   "standalone_infeasibility_replay");

  search_nonallocating_lifecycle(connected);
  replay_nonallocating_lifecycle(connected, v2_certificate);
  exact_handle_copies_are_nonallocating(connected, false);
  exact_handle_copies_are_nonallocating(infeasible, true);
  replay_handle_copies_are_nonallocating(connected, v2_certificate);
  replay_handle_copies_are_nonallocating(infeasible, infeasible_certificate);
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "P06 owned continuation replacement-new recovery checks passed\n";
    return 0;
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

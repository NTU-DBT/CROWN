#include "crown/planner/residual.hpp"
#include "crown/planner/verify.hpp"

#include <algorithm>
#include <chrono>
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

namespace {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocation_count = 0;

[[gnu::noinline]] void* tracked_malloc_new(std::size_t bytes) {
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

void* operator new(std::size_t bytes) { return tracked_malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return tracked_malloc_new(bytes); }
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return tracked_malloc_new(bytes); }
  catch (const std::bad_alloc&) { return nullptr; }
}
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return tracked_malloc_new(bytes); }
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

static_assert(std::is_nothrow_destructible_v<ResidualSearch>);
static_assert(std::is_nothrow_destructible_v<ResidualTrace>);
static_assert(std::is_nothrow_destructible_v<ResidualCandidate>);

void check(bool condition, const char* message) {
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
  for (std::size_t i = 0; i < head.size(); ++i)
    fixture.query.head.push_back({ids.at(head[i]), "out" + std::to_string(i)});
  return fixture;
}

bool same_term(const Term& left, const Term& right) {
  if (left.index() != right.index()) return false;
  if (const auto* id = std::get_if<VariableId>(&left)) return *id == std::get<VariableId>(right);
  if (const auto* value = std::get_if<Value>(&left)) return *value == std::get<Value>(right);
  return true;
}

bool same_query(const Query& left, const Query& right) {
  if (left.contradiction != right.contradiction || left.variables.size() != right.variables.size() ||
      left.atoms.size() != right.atoms.size() || left.head.size() != right.head.size()) return false;
  for (std::size_t i = 0; i < left.variables.size(); ++i)
    if (left.variables[i].name != right.variables[i].name || left.variables[i].type != right.variables[i].type) return false;
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
  }
  return true;
}

bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
  if (left.root != right.root || left.claimed_connex != right.claimed_connex ||
      left.claimed_native_height != right.claimed_native_height || left.nodes.size() != right.nodes.size()) return false;
  for (std::size_t i = 0; i < left.nodes.size(); ++i) {
    const auto& a = left.nodes[i];
    const auto& b = right.nodes[i];
    if (a.id != b.id || a.kind != b.kind || a.scope != b.scope || a.children != b.children ||
        a.occurrence != b.occurrence || a.claimed_separator != b.claimed_separator) return false;
  }
  return true;
}

bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) {
  if (left.algorithm != right.algorithm || left.minimum_height != right.minimum_height ||
      left.tree.has_value() != right.tree.has_value() || left.lower_bounds.size() != right.lower_bounds.size()) return false;
  if (left.tree && !same_tree(*left.tree, *right.tree)) return false;
  for (std::size_t i = 0; i < left.lower_bounds.size(); ++i) {
    const auto& a = left.lower_bounds[i];
    const auto& b = right.lower_bounds[i];
    if (a.occurrences != b.occurrences || a.generalized_allowed != b.generalized_allowed ||
        a.connex_reachable != b.connex_reachable || a.bound != b.bound) return false;
  }
  return true;
}

bool same_layer(const ResidualLayer& a, const ResidualLayer& b) {
  if (a.members != b.members || a.variables != b.variables || a.head != b.head || a.unique != b.unique ||
      a.ears.size() != b.ears.size() || a.deletions.size() != b.deletions.size() ||
      a.remaining != b.remaining || a.residual_head != b.residual_head) return false;
  for (std::size_t i = 0; i < a.ears.size(); ++i) {
    const auto& x = a.ears[i];
    const auto& y = b.ears[i];
    if (x.occurrence != y.occurrence || x.shared != y.shared || x.unique != y.unique ||
        x.anchors.size() != y.anchors.size()) return false;
    for (std::size_t j = 0; j < x.anchors.size(); ++j)
      if (x.anchors[j].occurrence != y.anchors[j].occurrence ||
          x.anchors[j].condition != y.anchors[j].condition) return false;
  }
  for (std::size_t i = 0; i < a.deletions.size(); ++i)
    if (a.deletions[i].occurrence != b.deletions[i].occurrence ||
        a.deletions[i].anchor != b.deletions[i].anchor) return false;
  return true;
}

bool same_view(const ResidualView& a, const ResidualView& b) {
  return a.original_occurrences == b.original_occurrences && a.original_variables == b.original_variables &&
      a.occurrence_to_local == b.occurrence_to_local && a.variable_to_local == b.variable_to_local &&
      same_query(a.query, b.query);
}

bool same_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) {
  if (a.version != b.version || a.original_scopes != b.original_scopes || a.layers.size() != b.layers.size() ||
      a.terminal_members != b.terminal_members || a.terminal_head != b.terminal_head || a.terminal != b.terminal ||
      !same_view(a.terminal_view, b.terminal_view)) return false;
  for (std::size_t i = 0; i < a.layers.size(); ++i)
    if (!same_layer(a.layers[i], b.layers[i])) return false;
  return true;
}

bool same_statistics(const ResidualStatistics& a, const ResidualStatistics& b) {
  return a.hierarchy_tests == b.hierarchy_tests && a.rounds == b.rounds &&
      a.eligibility_pairs == b.eligibility_pairs && a.deletions == b.deletions &&
      a.restorations == b.restorations && a.drafts == b.drafts &&
      a.rejected_drafts == b.rejected_drafts && a.generalized_grafts == b.generalized_grafts &&
      a.exact_repairs == b.exact_repairs && a.original_exact_runs == b.original_exact_runs &&
      a.candidate_publications == b.candidate_publications && a.admissions == b.admissions;
}

bool same_search_shape(const SearchProgress& a, const SearchProgress& b) {
  return a.phase == b.phase && a.result == b.result && a.heights == b.heights &&
      a.producer_complete == b.producer_complete && a.proof_complete == b.proof_complete &&
      a.producer.committed_transitions == b.producer.committed_transitions &&
      a.producer.current_depth == b.producer.current_depth && a.producer.peak_depth == b.producer.peak_depth &&
      a.replay.committed_transitions == b.replay.committed_transitions &&
      a.replay.current_depth == b.replay.current_depth && a.replay.peak_depth == b.replay.peak_depth &&
      a.structural.states == b.structural.states && a.structural.partitions == b.structural.partitions &&
      a.structural.candidates == b.structural.candidates && a.structural.cache_hits == b.structural.cache_hits &&
      a.structural.hierarchy_tests == b.structural.hierarchy_tests && a.structural.hierarchy_hits == b.structural.hierarchy_hits &&
      a.structural.singleton_hits == b.structural.singleton_hits && a.structural.empty_body_hits == b.structural.empty_body_hits &&
      a.structural.component_splits == b.structural.component_splits && a.structural.symmetry_skips == b.structural.symmetry_skips &&
      a.structural.bound_prunes == b.structural.bound_prunes && a.limit_revision == b.limit_revision;
}

bool same_progress_shape(const ResidualProgress& a, const ResidualProgress& b) {
  return a.phase == b.phase && a.result == b.result && a.proof_status == b.proof_status &&
      a.heights == b.heights && a.trace_complete == b.trace_complete && a.trace_verified == b.trace_verified &&
      a.exact_scope_original == b.exact_scope_original && a.records == b.records && a.cells == b.cells &&
      a.limit_revision == b.limit_revision && same_statistics(a.statistics, b.statistics) &&
      a.work.committed_transitions == b.work.committed_transitions &&
      a.work.current_depth == b.work.current_depth && a.work.peak_depth == b.work.peak_depth &&
      same_search_shape(a.exact_progress, b.exact_progress);
}

bool same_progress(const ResidualProgress& a, const ResidualProgress& b) {
  return same_progress_shape(a, b) && a.last_stop == b.last_stop && a.exact_stop == b.exact_stop &&
      a.work == b.work && a.exact_progress.last_stop == b.exact_progress.last_stop &&
      a.exact_progress.producer == b.exact_progress.producer && a.exact_progress.replay == b.exact_progress.replay &&
      a.exact_progress.structural.work == b.exact_progress.structural.work &&
      a.exact_progress.structural.certificate_work == b.exact_progress.structural.certificate_work;
}

bool counters_monotone(const WorkCounters& before, const WorkCounters& after) {
  return after.attempted >= before.attempted &&
      after.committed_transitions >= before.committed_transitions &&
      after.allocation_failures >= before.allocation_failures &&
      after.active_nanoseconds >= before.active_nanoseconds && after.peak_depth >= before.peak_depth;
}

bool progress_counters_monotone(const ResidualProgress& before, const ResidualProgress& after) {
  return counters_monotone(before.work, after.work) &&
      counters_monotone(before.exact_progress.producer, after.exact_progress.producer) &&
      counters_monotone(before.exact_progress.replay, after.exact_progress.replay);
}

bool same_trace(const ResidualTrace& a, const ResidualTrace& b) {
  return a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) &&
      same_query(a.query(), b.query()) && same_record(a.record(), b.record());
}

bool same_candidate(const ResidualCandidate& a, const ResidualCandidate& b) {
  return a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) &&
      same_query(a.query(), b.query()) && a.height() == b.height() && a.origin() == b.origin() &&
      same_tree(a.tree(), b.tree()) && same_trace(a.trace(), b.trace());
}

constexpr WorkQuantum all_work{std::numeric_limits<std::uint64_t>::max(), {}};

ResidualOptions options_for(ResidualMode mode) {
  ResidualOptions options;
  options.mode = mode;
  return options;
}

struct Baseline {
  ResidualProgress progress;
  ResidualTrace trace;
  ResidualCandidate candidate;
  std::optional<VerifiedOptimum> optimum;
  std::size_t advance_allocations = 0;
};

Baseline calibrate(const Fixture& fixture, ResidualMode mode) {
  auto owner = ResidualSearch::create(fixture.catalog, fixture.query, options_for(mode));
  allocation_count = 0;
  const auto advanced = owner.advance(all_work);
  const auto allocations = allocation_count;
  const auto progress = owner.progress();
  const auto trace = owner.trace();
  const auto candidate = owner.candidate();
  check(advanced.stopped_for == ResidualStopReason::complete,
        "uninterrupted residual fixture did not complete in one unbounded advance");
  check(trace && trace->valid() && progress.trace_complete && progress.trace_verified,
        "residual baseline did not publish its independently replayed trace");
  check(candidate && candidate->valid(), "residual baseline did not publish a checked candidate");
  if (mode == ResidualMode::candidates_with_exact_repair) {
    check(progress.result == ResidualResult::checked_candidate &&
              progress.proof_status == ResidualProofStatus::checked_upper_only &&
              !owner.exact_original() && !owner.infeasibility() && !progress.exact_scope_original &&
              progress.heights.lower_evidence == BoundEvidence::universal,
          "candidate mode promoted an upper bound to original-query exact authority");
  } else {
    const auto optimum = owner.exact_original();
    check(progress.result == ResidualResult::verified_optimum && optimum &&
              optimum->valid() && progress.proof_status == ResidualProofStatus::exact_original_verified &&
              progress.exact_scope_original && !owner.infeasibility(),
          "require-exact mode did not publish original-query exact authority");
    const auto certificate = verify_height_certificate(fixture.catalog, fixture.query,
                                                        optimum->certificate());
    check(certificate.valid && !certificate.resource_limit,
          "residual original-query P06 certificate failed independent verification");
  }
  const auto p02 = validate_tree(fixture.catalog, fixture.query, candidate->tree());
  check(p02.valid && p02.native_height == candidate->height(),
        "residual candidate is not a complete independently checked P02 upper bound");
  std::optional<VerifiedOptimum> optimum{};
  if (mode == ResidualMode::require_exact_original) {
    const auto published = owner.exact_original();
    check(published.has_value(), "exact baseline did not retain its published optimum");
    optimum.emplace(*published);
  }
  check(allocations > 0 && allocations <=
            static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "residual baseline allocation count is unusable for an exhaustive fault sweep");
  return Baseline{progress, *trace, *candidate, std::move(optimum), allocations};
}

bool allocation_stop(const ResidualAdvance& value) {
  return value.stopped_for == ResidualStopReason::allocation_failure ||
      (value.stopped_for == ResidualStopReason::exact_limit &&
       value.exact_reason == StopReason::allocation_failure);
}

bool trace_same_optional(const std::optional<ResidualTrace>& a,
                         const std::optional<ResidualTrace>& b) {
  return a.has_value() == b.has_value() && (!a || same_trace(*a, *b));
}

bool candidate_same_optional(const std::optional<ResidualCandidate>& a,
                             const std::optional<ResidualCandidate>& b) {
  return a.has_value() == b.has_value() && (!a || same_candidate(*a, *b));
}

struct Coverage {
  bool eligibility = false;
  bool layer = false;
  bool restore = false;
  bool validation = false;
  bool repair = false;
  bool exact_original = false;
  bool trace_publication = false;
  bool candidate_publication = false;
  bool exact_failure_with_candidate = false;
  bool repair_allocation_failure = false;
};

void update_coverage(Coverage& coverage, const ResidualProgress& p,
                    const std::optional<ResidualTrace>& trace,
                    const std::optional<ResidualCandidate>& candidate) {
  coverage.eligibility = coverage.eligibility || p.phase == ResidualPhase::eligibility ||
      p.statistics.eligibility_pairs > 0;
  coverage.layer = coverage.layer || p.phase == ResidualPhase::seal_layer || p.statistics.rounds > 0;
  coverage.restore = coverage.restore || p.phase == ResidualPhase::restore || p.statistics.restorations > 0;
  coverage.validation = coverage.validation || p.phase == ResidualPhase::validate_candidate;
  coverage.repair = coverage.repair || p.phase == ResidualPhase::repair || p.statistics.exact_repairs > 0;
  coverage.repair_allocation_failure = coverage.repair_allocation_failure ||
      (p.phase == ResidualPhase::repair && p.last_stop == ResidualStopReason::exact_limit &&
       p.exact_stop == StopReason::allocation_failure);
  coverage.exact_original = coverage.exact_original || p.phase == ResidualPhase::exact_original ||
      p.statistics.original_exact_runs > 0;
  coverage.trace_publication = coverage.trace_publication ||
      (p.trace_complete && !p.trace_verified && !trace);
  coverage.candidate_publication = coverage.candidate_publication ||
      (p.phase == ResidualPhase::validate_candidate && !candidate);
  coverage.exact_failure_with_candidate = coverage.exact_failure_with_candidate ||
      (p.phase == ResidualPhase::exact_original && p.trace_verified && candidate.has_value());
}

void residual_oom_sweep(const Fixture& fixture, ResidualMode mode, const Baseline& baseline,
                        Coverage& coverage, const char* label) {
  const auto catalog_before = fixture.catalog;
  const auto query_before = fixture.query;
  std::size_t fault_positions = 0;
  std::size_t maximum_faulted_allocations = 0;
  for (std::size_t point = 0; point <= baseline.advance_allocations; ++point) {
    auto owner = ResidualSearch::create(fixture.catalog, fixture.query, options_for(mode));
    allocation_count = 0;
    if (point == baseline.advance_allocations) {
      ResidualAdvance completed{};
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        completed = owner.advance(all_work);
        check(completed.stopped_for == ResidualStopReason::complete,
              "residual allocation position N did not finish with all observed allocations allowed");
        check(allocation_count == baseline.advance_allocations,
              "residual allocation calibration did not match the successful full advance");
      }
      const auto final = owner.progress();
      const auto trace = owner.trace();
      const auto candidate = owner.candidate();
      check(same_progress_shape(final, baseline.progress) && trace && same_trace(*trace, baseline.trace) &&
                candidate && same_candidate(*candidate, baseline.candidate),
            "all-success N point differs from uninterrupted residual baseline");
      if (baseline.optimum) {
        const auto exact = owner.exact_original();
        check(exact && exact->valid() && exact->height() == baseline.optimum->height() &&
                  same_certificate(exact->certificate(), baseline.optimum->certificate()),
              "all-success N point published a different original-query optimum");
      }
    } else {
      ResidualProgress first_progress;
      ResidualProgress second_progress;
      ResidualProgress third_progress;
      std::optional<ResidualTrace> first_trace{};
      std::optional<ResidualCandidate> first_candidate{};
      bool stable = false;
      bool zero_unchanged = false;
      bool noalloc_facade = false;
      bool correct_stop = false;
      std::size_t before_noalloc = 0;
      std::size_t faulted_allocations = 0;
      {
        FaultScope fault(static_cast<std::ptrdiff_t>(point));
        const auto first = owner.advance(all_work);
        first_progress = owner.progress();
        first_trace = owner.trace();
        first_candidate = owner.candidate();
        correct_stop = allocation_stop(first) && allocation_stop(
            ResidualAdvance{first_progress.last_stop, first_progress.exact_stop, first_progress});
        update_coverage(coverage, first_progress, first_trace, first_candidate);
        const bool no_partial_authority = first_progress.result == ResidualResult::unfinished &&
            first_progress.proof_status != ResidualProofStatus::exact_original_verified &&
            (first_progress.phase != ResidualPhase::exact_original || first_candidate.has_value());

        const auto repeated_one = owner.advance(all_work);
        second_progress = owner.progress();
        const auto repeated_two = owner.advance(all_work);
        third_progress = owner.progress();
        stable = allocation_stop(repeated_one) && allocation_stop(repeated_two) &&
            same_progress_shape(first_progress, second_progress) &&
            same_progress_shape(first_progress, third_progress) &&
            progress_counters_monotone(first_progress, second_progress) &&
            progress_counters_monotone(second_progress, third_progress) &&
            second_progress.work.attempted == first_progress.work.attempted + 1 &&
            third_progress.work.attempted == second_progress.work.attempted + 1 &&
            second_progress.work.allocation_failures == first_progress.work.allocation_failures + 1 &&
            third_progress.work.allocation_failures == second_progress.work.allocation_failures + 1 &&
            second_progress.work.committed_transitions == first_progress.work.committed_transitions &&
            third_progress.work.committed_transitions == second_progress.work.committed_transitions &&
            second_progress.records == first_progress.records && second_progress.cells == first_progress.cells &&
            third_progress.records == second_progress.records && third_progress.cells == second_progress.cells &&
            trace_same_optional(first_trace, owner.trace()) &&
            candidate_same_optional(first_candidate, owner.candidate());
        stable = stable && no_partial_authority;

        before_noalloc = allocation_count;
        const auto before_zero = owner.progress();
        const auto zero = owner.advance(WorkQuantum{0, {}});
        const auto after_zero = owner.progress();
        const auto unpublished_optimum = owner.exact_original();
        const auto unpublished_infeasibility = owner.infeasibility();
        zero_unchanged = zero.stopped_for == ResidualStopReason::quantum_work &&
            same_progress(before_zero, after_zero) && same_progress(before_zero, zero.progress) &&
            !unpublished_optimum && !unpublished_infeasibility;
        auto options = owner.options();
        const auto& owned_catalog = owner.catalog();
        const auto& owned_query = owner.query();
        auto moved = std::move(owner);
        const auto moved_progress = moved.progress();
        owner = std::move(moved);
        noalloc_facade = same_progress(before_zero, moved_progress) &&
            same_progress(before_zero, owner.progress()) && options.mode == mode &&
            same_catalog(owned_catalog, fixture.catalog) && same_query(owned_query, fixture.query);
        if (first_trace) {
          auto copy = *first_trace;
          noalloc_facade = noalloc_facade && copy.valid() && same_record(copy.record(), baseline.trace.record());
        }
        if (first_candidate) {
          auto copy = *first_candidate;
          const auto candidate_trace = copy.trace();
          noalloc_facade = noalloc_facade && copy.valid() && candidate_trace.valid() &&
              copy.height() == first_candidate->height() && same_tree(copy.tree(), first_candidate->tree());
        }
        faulted_allocations = allocation_count;
        check(correct_stop && stable && zero_unchanged && noalloc_facade,
              "persistent residual OOM escaped, changed committed state, lost handles, or allocated in facade operations");
        check(faulted_allocations == before_noalloc,
              "residual getters, handle copies, move, or zero quantum allocated under persistent OOM");
      }
      maximum_faulted_allocations = std::max(maximum_faulted_allocations, faulted_allocations);
      ++fault_positions;

      allocation_count = 0;
      const auto resumed = owner.advance(all_work);
      const auto final = owner.progress();
      const auto resumed_trace = owner.trace();
      const auto resumed_candidate = owner.candidate();
      check(resumed.stopped_for == ResidualStopReason::complete &&
                same_progress_shape(final, baseline.progress) && resumed_trace &&
                same_trace(*resumed_trace, baseline.trace) && resumed_candidate &&
                same_candidate(*resumed_candidate, baseline.candidate),
            "same residual owner did not recover to uninterrupted trace/candidate after OOM");
      check(final.work.committed_transitions == baseline.progress.work.committed_transitions &&
                final.work.attempted == baseline.progress.work.attempted + 3 &&
                final.work.allocation_failures == baseline.progress.work.allocation_failures + 3,
            "resumed residual owner restarted work or lost monotone retry accounting");
      if (baseline.optimum) {
        const auto exact = owner.exact_original();
        check(exact && exact->valid() && exact->height() == baseline.optimum->height() &&
                  same_certificate(exact->certificate(), baseline.optimum->certificate()),
              "resumed residual owner lost its final original-query exact authority");
      }
      const auto candidate_on_resume = owner.candidate();
      check(candidate_on_resume && validate_tree(fixture.catalog, fixture.query, candidate_on_resume->tree()).valid,
            "resumed residual owner candidate failed independent P02 validation");
      check(same_catalog(fixture.catalog, catalog_before) && same_query(fixture.query, query_before),
            "residual fault sweep mutated caller-owned input");
    }
    check(same_catalog(fixture.catalog, catalog_before) && same_query(fixture.query, query_before),
          "residual fault sweep mutated caller-owned input");
  }
  check(fault_positions == baseline.advance_allocations,
        "residual persistent OOM sweep missed an observed allocation position");
  check(coverage.eligibility && coverage.layer && coverage.restore && coverage.validation &&
            coverage.trace_publication && coverage.candidate_publication,
        "residual OOM sweep missed eligibility/layer/restore/validation/trace/candidate publication coverage");
  if (mode == ResidualMode::require_exact_original)
    check(coverage.exact_original && coverage.exact_failure_with_candidate,
          "require-exact residual sweep missed original proof failure after checked candidate publication");
  std::cout << label << " tracked-new requests=" << baseline.advance_allocations
            << " fault_positions=" << fault_positions
            << " max_faulted_calls=" << maximum_faulted_allocations << '\n' << std::flush;
}

void trace_verifier_is_independent_and_resource_honest(const Fixture& fixture,
                                                       const ResidualTrace& trace) {
  const auto valid = verify_residual_trace(fixture.catalog, fixture.query, trace.record());
  check(valid.valid && !valid.resource_limit && valid.work > 0 && valid.rule == ResidualTraceRule::none,
        "standalone residual trace replay did not independently validate the frozen record");
  SearchLimits zero;
  zero.work_limit = 0;
  const auto stopped = verify_residual_trace(fixture.catalog, fixture.query, trace.record(), zero);
  check(!stopped.valid && stopped.resource_limit && stopped.work == 0 &&
            stopped.rule == ResidualTraceRule::resource_limit,
        "zero-work standalone trace verification claimed validity or charged nonexistent work");
  auto malformed = trace.record();
  malformed.version = 2;
  const auto rejected = verify_residual_trace(fixture.catalog, fixture.query, malformed);
  check(!rejected.valid && !rejected.resource_limit && rejected.rule == ResidualTraceRule::version,
        "standalone replay accepted a malformed residual trace as valid or as mere resource exhaustion");
}

void limit_extensions_and_zero_quanta(const Fixture& fixture) {
  const auto make_limited = [&](int kind) {
    auto options = options_for(ResidualMode::require_exact_original);
    if (kind == 0) options.limits.residual.work = 0;
    if (kind == 1) options.limits.residual.active_time = std::chrono::nanoseconds{0};
    if (kind == 2) options.limits.logical_depth = 0;
    if (kind == 3) options.limits.record_limit = 0;
    if (kind == 4) options.limits.cell_limit = 0;
    if (kind == 5) options.limits.exact.producer.work = 0;
    return std::pair{std::move(options), kind};
  };
  for (int kind = 0; kind != 6; ++kind) {
    auto [options, selected] = make_limited(kind);
    auto owner = ResidualSearch::create(fixture.catalog, fixture.query, options);
    const auto first = owner.advance(all_work);
    const auto progress = owner.progress();
    const ResidualStopReason expected = selected == 0 ? ResidualStopReason::total_work :
        selected == 1 ? ResidualStopReason::total_time :
        selected == 2 ? ResidualStopReason::depth_limit :
        selected == 3 ? ResidualStopReason::record_limit :
        selected == 4 ? ResidualStopReason::cell_limit : ResidualStopReason::exact_limit;
    check(first.stopped_for == expected && progress.result == ResidualResult::unfinished &&
              !owner.exact_original() && !owner.infeasibility(),
          "residual resource ceiling published authority or reported the wrong stop");

    const auto before_zero = owner.progress();
    const auto zero = owner.advance(WorkQuantum{0, {}});
    check(zero.stopped_for == ResidualStopReason::quantum_work &&
              same_progress(before_zero, owner.progress()) && same_progress(before_zero, zero.progress),
          "zero-work residual quantum changed logical progress or accounting");
    const auto time_zero = owner.advance(WorkQuantum{1, std::chrono::nanoseconds{0}});
    check(time_zero.stopped_for == ResidualStopReason::quantum_time &&
              same_progress(before_zero, owner.progress()),
          "zero-time residual quantum changed logical progress or accounting");

    auto raised = options.limits;
    raised.residual.work = 50'000'000;
    if (selected == 1) raised.residual.active_time = std::chrono::seconds{30};
    raised.logical_depth = 256;
    raised.record_limit = 1'000'000;
    raised.cell_limit = 10'000'000;
    raised.exact.producer.work = 10'000'000;
    raised.exact.replay.work = 10'000'000;
    check(owner.raise_limits(raised) == LimitChange::applied,
          "monotone residual limit extension was rejected");
    const auto next_revision = owner.progress().limit_revision;
    auto smaller = raised;
    if (selected == 0) smaller.residual.work = 1;
    else if (selected == 1) smaller.residual.active_time = std::chrono::nanoseconds{1};
    else if (selected == 2) smaller.logical_depth = 1;
    else if (selected == 3) smaller.record_limit = 1;
    else if (selected == 4) smaller.cell_limit = 1;
    else smaller.exact.producer.work = 1;
    const auto before_reject = owner.progress();
    check(owner.raise_limits(smaller) == LimitChange::not_monotone &&
              same_progress(before_reject, owner.progress()) && owner.progress().limit_revision == next_revision,
          "residual limit reduction mutated progress or limit revision");
    auto invalid = raised;
    invalid.residual.active_time = std::chrono::nanoseconds{-1};
    const auto before_invalid = owner.progress();
    check(owner.raise_limits(invalid) == LimitChange::invalid &&
              same_progress(before_invalid, owner.progress()),
          "invalid residual ceiling changed owner state");
    const auto resumed = owner.advance(all_work);
    check(resumed.stopped_for == ResidualStopReason::complete &&
              owner.progress().result == ResidualResult::verified_optimum && owner.exact_original(),
          "residual owner did not resume after resource ceilings were extended");
  }
}

void cancellation_lifecycle_and_outliving_handles(const Fixture& fixture) {
  auto owner = ResidualSearch::create(fixture.catalog, fixture.query,
                                      options_for(ResidualMode::require_exact_original));
  std::optional<ResidualTrace> trace{};
  std::optional<ResidualCandidate> candidate{};
  for (;;) {
    static_cast<void>(owner.advance(WorkQuantum{1, {}}));
    trace = owner.trace();
    candidate = owner.candidate();
    const auto current = owner.progress();
    if (candidate && current.phase == ResidualPhase::exact_original &&
        current.exact_progress.producer.current_depth > 0) break;
    check(current.result != ResidualResult::failed,
          "residual lifecycle fixture failed before entering original proof depth");
    check(current.phase != ResidualPhase::complete,
          "residual lifecycle fixture completed before cancellation at nonzero nested depth");
  }
  check(trace && trace->valid(), "residual lifecycle fixture never published a frozen trace");
  if (!candidate) candidate = owner.candidate();
  check(candidate && candidate->valid(), "residual lifecycle fixture never published a checked candidate");
  const auto trace_copy = *trace;
  const auto candidate_copy = *candidate;
  std::optional<ResidualSearch> held;
  held.emplace(std::move(owner));
  allocation_count = 0;
  bool valid = false;
  std::size_t observed = 0;
  {
    FaultScope fault(0);
    const auto before = held->progress();
    const auto zero = held->advance(WorkQuantum{0, {}});
    const auto after = held->progress();
    auto held_trace = held->trace();
    auto held_candidate = held->candidate();
    const auto held_optimum = held->exact_original();
    const auto held_infeasibility = held->infeasibility();
    auto trace_handle_copy = trace_copy;
    auto candidate_handle_copy = candidate_copy;
    auto moved = std::move(*held);
    const auto moved_progress = moved.progress();
    *held = std::move(moved);
    const auto restored = held->progress();
    held->cancel();
    const auto cancelled = held->progress();
    auto cancelled_trace = held->trace();
    auto cancelled_candidate = held->candidate();
    held.reset();
    valid = zero.stopped_for == ResidualStopReason::quantum_work &&
        same_progress(before, after) && same_progress(before, zero.progress) &&
        same_progress(before, moved_progress) && same_progress(before, restored) &&
        held_trace && held_candidate && held_trace->valid() && held_candidate->valid() &&
        !held_optimum && !held_infeasibility && trace_same_optional(held_trace, cancelled_trace) &&
        candidate_same_optional(held_candidate, cancelled_candidate) &&
        trace_handle_copy.valid() && candidate_handle_copy.valid() &&
        cancelled.phase == ResidualPhase::cancelled && cancelled.work.current_depth == 0 &&
        cancelled.work.attempted == before.work.attempted &&
        cancelled.work.committed_transitions == before.work.committed_transitions &&
        cancelled.work.peak_depth == before.work.peak_depth &&
        cancelled.exact_progress.producer.current_depth == 0 && cancelled.exact_progress.replay.current_depth == 0 &&
        cancelled.exact_progress.producer.attempted == before.exact_progress.producer.attempted &&
        cancelled.exact_progress.producer.committed_transitions == before.exact_progress.producer.committed_transitions &&
        cancelled.exact_progress.producer.peak_depth == before.exact_progress.producer.peak_depth &&
        cancelled.result == ResidualResult::unfinished;
    observed = allocation_count;
  }
  check(valid && observed == 0,
        "residual handle copies, getter, zero quantum, move, cancel, replacement, or destruction allocated under OOM");
  check(trace_copy.valid() && candidate_copy.valid() && same_record(trace_copy.record(), candidate_copy.trace().record()) &&
            validate_tree(candidate_copy.catalog(), candidate_copy.query(), candidate_copy.tree()).valid,
        "published residual handles did not outlive their owner with their bindings and proof intact");
}

void run() {
  // Head-induced nonhierarchy removes the second atom while retaining a valid
  // one-atom dense projection and the original output-bearing native root.
  const auto projected = scoped_fixture({{0, 1}, {0, 2}}, {1});
  const auto candidate_baseline = calibrate(projected, ResidualMode::candidates_with_exact_repair);
  check(candidate_baseline.trace.record().layers.size() == 1 &&
            candidate_baseline.trace.record().terminal_view.query.atoms.size() == 1 &&
            candidate_baseline.trace.record().terminal_view.original_variables ==
                std::vector<VariableId>{VariableId{0}, VariableId{1}} &&
            !candidate_baseline.trace.record().terminal_view.variable_to_local[2] &&
            candidate_baseline.progress.statistics.eligibility_pairs > 0 &&
            candidate_baseline.progress.statistics.restorations > 0,
        "projected residual fixture missed its one-layer dense-view recovery path");
  const auto exact_baseline = calibrate(projected, ResidualMode::require_exact_original);
  check(candidate_baseline.candidate.height() == 2 && exact_baseline.optimum &&
            exact_baseline.optimum->height() == 2,
        "projected residual fixture lost its expected height-two original result");
  Coverage candidate_coverage;
  Coverage exact_coverage;
  residual_oom_sweep(projected, ResidualMode::candidates_with_exact_repair,
                     candidate_baseline, candidate_coverage, "projected_candidate_mode");
  residual_oom_sweep(projected, ResidualMode::require_exact_original,
                     exact_baseline, exact_coverage, "projected_require_exact_mode");
  trace_verifier_is_independent_and_resource_honest(projected, candidate_baseline.trace);

  // A compact non-hierarchical residual with ears around a generalized core.
  // The full sweep verifies whether reconstruction chooses a native attachment,
  // generalized attachment, graft, or exact repair on this concrete shape.
  const auto graft = scoped_fixture({{0, 1, 2}, {0, 1, 3}, {2}, {3}, {0, 4}}, {0, 4});
  const auto graft_baseline = calibrate(graft, ResidualMode::candidates_with_exact_repair);
  check(graft_baseline.trace.record().layers.size() > 0 && graft_baseline.progress.statistics.rounds > 0 &&
            graft_baseline.progress.statistics.generalized_grafts > 0,
        "five-atom reconstruction fixture did not exercise a frozen round and generalized graft");
  Coverage graft_coverage;
  residual_oom_sweep(graft, ResidualMode::candidates_with_exact_repair,
                     graft_baseline, graft_coverage, "five_atom_candidate_mode");
  const auto graft_exact = calibrate(graft, ResidualMode::require_exact_original);
  Coverage graft_exact_coverage;
  residual_oom_sweep(graft, ResidualMode::require_exact_original,
                     graft_exact, graft_exact_coverage, "five_atom_require_exact_mode");
  trace_verifier_is_independent_and_resource_honest(graft, graft_baseline.trace);

  const auto repair = scoped_fixture(
      {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}}, {0, 1, 6});
  const auto repair_baseline = calibrate(repair, ResidualMode::candidates_with_exact_repair);
  check(repair_baseline.progress.statistics.exact_repairs == 1 &&
            repair_baseline.candidate.height() == 3,
        "seven-atom fixture did not enter the owned exact-repair path");
  Coverage repair_coverage;
  residual_oom_sweep(repair, ResidualMode::candidates_with_exact_repair,
                     repair_baseline, repair_coverage, "seven_atom_exact_repair_mode");
  check(repair_coverage.repair && repair_coverage.repair_allocation_failure,
        "seven-atom persistent sweep missed exact-repair progress or nested P06 allocation failure");

  limit_extensions_and_zero_quanta(projected);
  cancellation_lifecycle_and_outliving_handles(projected);

  const auto infeasible = scoped_fixture({{0, 1}, {1, 2}}, {0, 2});
  auto exact_infeasible = ResidualSearch::create(infeasible.catalog, infeasible.query,
      options_for(ResidualMode::require_exact_original));
  const auto infeasible_done = exact_infeasible.advance(all_work);
  const auto infeasibility = exact_infeasible.infeasibility();
  check(infeasible_done.stopped_for == ResidualStopReason::complete &&
            exact_infeasible.progress().result == ResidualResult::verified_infeasible &&
            exact_infeasible.progress().proof_status == ResidualProofStatus::exact_original_verified &&
            exact_infeasible.progress().exact_scope_original && infeasibility && infeasibility->valid() &&
            !infeasibility->certificate().tree && !infeasibility->certificate().minimum_height &&
            !exact_infeasible.exact_original(),
        "residual exact infeasibility was published as unsupported or as an optimum");
  const auto infeasible_report = verify_height_certificate(infeasible.catalog, infeasible.query,
                                                            infeasibility->certificate());
  check(infeasible_report.valid && !infeasible_report.resource_limit,
        "residual original-query infeasibility certificate failed independent P06 replay");
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "P05 residual tracked-new fault-recovery checks passed\n";
    return 0;
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

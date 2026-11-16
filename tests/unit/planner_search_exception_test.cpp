#include "crown/planner/oracle.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"

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
#include <string_view>
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
  explicit FaultScope(std::ptrdiff_t point = -1) noexcept { fail_after = point; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
  void forbid_allocations() noexcept { fail_after = 0; }
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try {
    return malloc_new(bytes);
  } catch (const std::bad_alloc&) {
    // malloc_new leaves fail_after at zero after an injected failure, so an
    // optional-buffer fallback cannot disarm later planner allocations.
    return nullptr;
  }
}
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try {
    return malloc_new(bytes);
  } catch (const std::bad_alloc&) {
    return nullptr;
  }
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

namespace {
using namespace crown;

static_assert(std::is_nothrow_destructible_v<planner::OracleResult>);
static_assert(std::is_nothrow_destructible_v<planner::CertificateReport>);

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

void check_unchanged(const Fixture& fixture, const Catalog& catalog_before,
                     const Query& query_before) {
  check(same_catalog(fixture.catalog, catalog_before), "planner changed the input catalog");
  check(same_query(fixture.query, query_before), "planner changed the input query");
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

bool same_certificate(const planner::HeightCertificate& left,
                     const planner::HeightCertificate& right) {
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

planner::HeightCertificate certificate_for(const planner::OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}

void check_no_partial_result(const planner::OracleResult& result) {
  check(result.status == planner::OracleStatus::resource_limit,
        "interrupted exact search did not report resource_limit");
  check(!result.minimum_height && !result.tree && result.lower_bounds.empty() &&
            !result.certificate_verified,
        "interrupted exact search published a partial optimum, tree, or proof");
}

void check_native_occurrences_once(const Query& query, const FreeConnexTree& tree) {
  std::vector<std::size_t> observed;
  for (const auto& node : tree.nodes) {
    if (node.kind == NodeKind::native) {
      check(node.occurrence.has_value(), "native witness node omitted its occurrence");
      observed.push_back(*node.occurrence);
    }
  }
  std::sort(observed.begin(), observed.end());
  std::vector<std::size_t> expected(query.atoms.size());
  for (std::size_t i = 0; i < expected.size(); ++i) expected[i] = i;
  check(observed == expected, "planner witness merged, dropped, or duplicated native occurrences");
}

void check_successful_oracle(const Fixture& fixture, const planner::OracleResult& result,
                             std::size_t expected_height, std::string_view algorithm) {
  check(result.status == planner::OracleStatus::proven_minimum,
        "clean planner run did not prove a minimum");
  check(result.minimum_height == expected_height && result.tree.has_value(),
        "clean planner run returned the wrong exact height");
  check(result.algorithm == algorithm, "planner emitted the wrong certificate algorithm");
  check(result.certificate_verified && !result.lower_bounds.empty(),
        "completed planner result lacks its independently checked proof");
  const auto tree = planner::validate_tree(fixture.catalog, fixture.query, *result.tree);
  check(tree.valid && tree.native_height == result.minimum_height,
        "completed planner result has an invalid upper witness");
  check_native_occurrences_once(fixture.query, *result.tree);
  const auto replay = planner::verify_height_certificate(
      fixture.catalog, fixture.query, certificate_for(result));
  check(replay.valid && !replay.resource_limit,
        "completed planner result does not independently replay");
}

// Return 1 for success, 0 for an honest resource stop, and -1 for a malformed
// result. The classifier is also used under persistent failure and must not
// allocate.
int classify_oracle(const planner::OracleResult& result) {
  if (result.status == planner::OracleStatus::proven_minimum) return 1;
  if (result.status == planner::OracleStatus::resource_limit &&
      !result.minimum_height && !result.tree && result.lower_bounds.empty() &&
      !result.certificate_verified) return 0;
  return -1;
}

int classify_report(const planner::CertificateReport& report) {
  if (report.valid && !report.resource_limit) return 1;
  if (!report.valid && report.resource_limit) return 0;
  return -1;
}

// The observed successful path determines the complete sweep length. Point N
// lets all N observed allocations succeed, so it is the first un-faulted run;
// there is no arbitrary test-only cap on the failure positions.
template <class Invoke, class Classify, class CheckSuccess, class CheckImmutable>
void sweep_persistent_allocations(std::string_view label, Invoke invoke,
                                  Classify classify, CheckSuccess check_success,
                                  CheckImmutable check_immutable) {
  using Result = std::decay_t<decltype(invoke())>;
  allocation_count = 0;
  Result calibration = invoke();
  const std::size_t successful_allocations = allocation_count;
  check(successful_allocations > 0, "planner sweep calibration observed no allocations");
  check(successful_allocations <= static_cast<std::size_t>(
            std::numeric_limits<std::ptrdiff_t>::max()),
        "planner sweep allocation count exceeds fault-index range");
  check(classify(calibration) == 1, "planner sweep calibration did not complete successfully");
  check_success(calibration);
  check_immutable();

  std::size_t fault_positions = 0;
  std::size_t maximum_attempt_allocations = 0;
  bool reached_success = false;
  for (std::size_t point = 0; point <= successful_allocations; ++point) {
    allocation_count = 0;
    std::optional<Result> attempt;
    bool threw_bad_alloc = false;
    int observation = -1;
    std::size_t attempt_allocations = 0;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      try {
        attempt.emplace(invoke());
        observation = classify(*attempt);
        if (observation != 1) attempt.reset();
      } catch (const std::bad_alloc&) {
        threw_bad_alloc = true;
      }
      // Snapshot before any assertion message can allocate and perturb it.
      attempt_allocations = allocation_count;
    }
    maximum_attempt_allocations = std::max(maximum_attempt_allocations, attempt_allocations);
    check_immutable();

    if (threw_bad_alloc || observation == 0) {
      ++fault_positions;
      continue;
    }
    check(observation == 1 && attempt.has_value(),
          "replacement-new failure produced an unsupported or partially published result");
    check_success(*attempt);
    check(point == successful_allocations,
          "persistent sweep reached success before exhausting the observed allocation path");
    reached_success = true;
    break;
  }

  check(reached_success, "persistent planner sweep did not reach its observed successful path");
  check(fault_positions == successful_allocations,
        "persistent planner sweep did not fail at every observed allocation position");

  allocation_count = 0;
  Result recovery = invoke();
  const std::size_t recovery_allocations = allocation_count;
  check(classify(recovery) == 1,
        "fresh planner invocation did not recover after replacement-new fault sweep");
  check_success(recovery);
  check_immutable();
  std::cout << label << " fault_positions=" << fault_positions
            << " successful_allocation_calls=" << successful_allocations
            << " maximum_attempt_allocation_calls=" << maximum_attempt_allocations
            << " recovery_allocation_calls=" << recovery_allocations << '\n';
}

void check_successful_report(const planner::CertificateReport& report) {
  check(report.valid && !report.resource_limit && report.work > 0,
        "independent certificate replay did not complete successfully");
}

void hierarchy_sweep(const Fixture& fixture) {
  const Catalog catalog_before = fixture.catalog;
  const Query query_before = fixture.query;
  auto invoke = [&] { return planner::minimum_tree(fixture.catalog, fixture.query); };
  auto success = [&](const planner::OracleResult& result) {
    check_successful_oracle(fixture, result, 1, "crown_partition_exact_v2");
    check(result.statistics.hierarchy_hits > 0,
          "hierarchical sweep did not exercise hierarchy construction");
  };
  sweep_persistent_allocations(
      "q_hierarchical_construction", invoke, classify_oracle, success,
      [&] { check_unchanged(fixture, catalog_before, query_before); });
}

void connected_symmetry_sweep(const Fixture& fixture) {
  const Catalog catalog_before = fixture.catalog;
  const Query query_before = fixture.query;
  auto invoke = [&] { return planner::minimum_tree(fixture.catalog, fixture.query); };
  auto success = [&](const planner::OracleResult& result) {
    check_successful_oracle(fixture, result, 2, "crown_partition_exact_v2");
    check(result.statistics.symmetry_skips > 0,
          "connected sweep did not exercise equal-complete-scope symmetry pruning");
    check(result.statistics.states > 0, "connected sweep did not enter exact search");
  };
  sweep_persistent_allocations(
      "connected_duplicate_scope_search", invoke, classify_oracle, success,
      [&] { check_unchanged(fixture, catalog_before, query_before); });
}

void disconnected_components_sweep(const Fixture& fixture) {
  const Catalog catalog_before = fixture.catalog;
  const Query query_before = fixture.query;
  auto invoke = [&] { return planner::minimum_tree(fixture.catalog, fixture.query); };
  auto success = [&](const planner::OracleResult& result) {
    check_successful_oracle(fixture, result, 2, "crown_partition_exact_v2");
    check(result.statistics.component_splits > 0,
          "disconnected sweep did not exercise component decomposition");
    check(result.tree && std::any_of(result.tree->nodes.begin(), result.tree->nodes.end(),
                                     [](const auto& node) {
                                       return node.kind == NodeKind::native && node.scope.empty();
                                     }),
          "disconnected witness lost its nullary native component");
  };
  sweep_persistent_allocations(
      "disconnected_height_two_and_nullary_components", invoke, classify_oracle, success,
      [&] { check_unchanged(fixture, catalog_before, query_before); });
}

void certificate_replay_sweep(const Fixture& fixture,
                              const planner::HeightCertificate& certificate,
                              std::string_view label) {
  const Catalog catalog_before = fixture.catalog;
  const Query query_before = fixture.query;
  const planner::HeightCertificate certificate_before = certificate;
  auto invoke = [&] {
    return planner::verify_height_certificate(fixture.catalog, fixture.query, certificate);
  };
  auto success = [&](const planner::CertificateReport& report) {
    check_successful_report(report);
  };
  sweep_persistent_allocations(label, invoke, classify_report, success, [&] {
    check_unchanged(fixture, catalog_before, query_before);
    check(same_certificate(certificate, certificate_before),
          "certificate replay changed its input certificate");
  });
}

void zero_limits_never_publish_partial_proofs(const Fixture& fixture,
                                              const planner::HeightCertificate& certificate) {
  const Catalog catalog_before = fixture.catalog;
  const Query query_before = fixture.query;
  const planner::HeightCertificate certificate_before = certificate;
  for (int kind = 0; kind < 3; ++kind) {
    planner::SearchLimits limits;
    if (kind == 0) limits.work_limit = 0;
    if (kind == 1) limits.time_limit = std::chrono::milliseconds{0};
    if (kind == 2) limits.recursion_limit = 0;
    const auto stopped = planner::minimum_tree(fixture.catalog, fixture.query, limits);
    check_no_partial_result(stopped);

    const auto replay = planner::verify_height_certificate(
        fixture.catalog, fixture.query, certificate, limits);
    check(replay.resource_limit && !replay.valid,
          "zero-limited certificate replay published a partial proof");
    check_unchanged(fixture, catalog_before, query_before);
    check(same_certificate(certificate, certificate_before),
          "resource-limited certificate replay changed its input certificate");
  }
}

Fixture residual_seven() {
  return fixture_for({{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}},
                     {0, 1, 6});
}

void certificate_replay_resource_limit_is_distinct() {
  const auto fixture = residual_seven();
  const auto complete = planner::minimum_tree(fixture.catalog, fixture.query);
  check(complete.status == planner::OracleStatus::proven_minimum &&
            complete.minimum_height == 3 && complete.certificate_verified &&
            complete.statistics.work > 0 && complete.statistics.certificate_work > 0,
        "residual seven fixture did not produce its exact certified height");

  planner::ContinuationLimits limits;
  limits.producer.work.reset();
  limits.producer.active_time.reset();
  limits.replay.work = 0;
  limits.replay.active_time.reset();
  limits.logical_depth = 512;
  planner::SearchOptions options;
  options.policy = planner::SearchPolicy::strict;
  options.limits = limits;
  auto owner = planner::ExactSearch::create(fixture.catalog, fixture.query, options);

  planner::SearchAdvance stopped;
  bool replay_interrupted = false;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    stopped = owner.advance(planner::WorkQuantum{4096, {}});
    if (stopped.stopped_for == planner::StopReason::total_work) {
      replay_interrupted = true;
      break;
    }
    check(stopped.stopped_for == planner::StopReason::quantum_work ||
          stopped.stopped_for == planner::StopReason::quantum_time,
          "unbounded residual producer stopped before independent replay");
  }
  check(replay_interrupted && stopped.progress.producer_complete &&
            stopped.progress.phase == planner::SearchPhase::replay &&
            !stopped.progress.proof_complete &&
            stopped.progress.result == planner::ResultKind::unfinished &&
            stopped.progress.replay.attempted == 0 && !owner.optimum() &&
            !owner.infeasibility() && !owner.incumbent(),
        "forced replay interruption published strict authority or occurred before production completed");

  limits.replay.work = 10'000'000;
  check(owner.raise_limits(limits) == planner::LimitChange::applied,
        "raising the replay ceiling was rejected");
  planner::SearchAdvance resumed;
  bool resumed_to_completion = false;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    resumed = owner.advance(planner::WorkQuantum{4096, {}});
    if (resumed.progress.proof_complete) {
      resumed_to_completion = true;
      break;
    }
    check(resumed.progress.result != planner::ResultKind::failed,
          "continued proof replay failed before final publication");
    check(resumed.stopped_for == planner::StopReason::quantum_work ||
          resumed.stopped_for == planner::StopReason::quantum_time,
          "continued proof replay stopped for an unexpected reason");
  }
  const auto optimum = owner.optimum();
  check(resumed_to_completion && optimum && optimum->valid() && optimum->height() == 3 &&
            resumed.progress.result == planner::ResultKind::verified_optimum &&
            resumed.progress.producer.attempted > 0 && resumed.progress.replay.attempted > 0 &&
            !owner.incumbent(),
        "resumed strict continuation did not verify height three with producer and replay work");
}

void typed_result_and_report_cleanup_is_allocation_free(const Fixture& fixture) {
  auto result = planner::minimum_tree(fixture.catalog, fixture.query);
  check(result.status == planner::OracleStatus::proven_minimum && result.tree &&
            result.certificate_verified,
        "typed cleanup fixture did not produce a complete planner result");
  auto certificate = certificate_for(result);
  auto report = planner::verify_height_certificate(fixture.catalog, fixture.query, certificate);
  check_successful_report(report);

  std::optional<planner::OracleResult> result_source(std::move(result));
  std::optional<planner::OracleResult> result_destination;
  std::optional<planner::CertificateReport> report_source(std::move(report));
  std::optional<planner::CertificateReport> report_destination;
  allocation_count = 0;
  std::size_t cleanup_allocations = 0;
  {
    FaultScope fault;
    fault.forbid_allocations();
    result_destination = std::move(result_source);
    result_source.reset();
    result_destination.reset();
    report_destination = std::move(report_source);
    report_source.reset();
    report_destination.reset();
    cleanup_allocations = allocation_count;
  }
  check(cleanup_allocations == 0,
        "typed OracleResult/CertificateReport move cleanup allocated");
}

void run() {
  // Nested incidence classes exercise generalized-node construction and its
  // partial-vector cleanup while q-hierarchy is recognized.
  const auto hierarchical = fixture_for({{0, 1}, {0, 1}, {0}}, {0});
  hierarchy_sweep(hierarchical);

  // Duplicate complete scopes stay distinct native occurrences while the
  // connected, non-hierarchical fallback skips only symmetric root choices.
  const auto connected = fixture_for({{0, 1}, {0, 1}, {1}}, {0});
  connected_symmetry_sweep(connected);

  // The height-two connected component is joined with an ordinary singleton
  // and a separate nullary occurrence; the whole minimum remains two.
  const auto disconnected = fixture_for({{0, 1}, {1}, {2}, {}}, {0, 2});
  disconnected_components_sweep(disconnected);

  const auto connected_result = planner::minimum_tree(connected.catalog, connected.query);
  check_successful_oracle(connected, connected_result, 2, "crown_partition_exact_v2");
  const auto v2_certificate = certificate_for(connected_result);
  check(v2_certificate.lower_bounds.size() > 1,
        "v2 replay sweep needs a nontrivial lower-bound certificate");
  certificate_replay_sweep(connected, v2_certificate, "independent_v2_certificate_replay");
  zero_limits_never_publish_partial_proofs(connected, v2_certificate);

#ifdef CROWN_PLANNER_TESTING
  auto invoke_v1 = [&] {
    return planner::testing::minimum_tree_baseline(connected.catalog, connected.query);
  };
  const Catalog catalog_before = connected.catalog;
  const Query query_before = connected.query;
  auto v1_success = [&](const planner::OracleResult& result) {
    check_successful_oracle(connected, result, 2, "crown_partition_exact_v1");
  };
  sweep_persistent_allocations(
      "private_v1_baseline_search", invoke_v1, classify_oracle, v1_success,
      [&] { check_unchanged(connected, catalog_before, query_before); });
  const auto v1_result = invoke_v1();
  check_successful_oracle(connected, v1_result, 2, "crown_partition_exact_v1");
  const auto v1_certificate = certificate_for(v1_result);
  certificate_replay_sweep(connected, v1_certificate, "independent_v1_certificate_replay");
#endif

  certificate_replay_resource_limit_is_distinct();
  typed_result_and_report_cleanup_is_allocation_free(connected);
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "planner replacement-new and proof-resource checks passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}

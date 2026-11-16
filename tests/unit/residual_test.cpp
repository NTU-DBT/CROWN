#include "crown/planner/residual.hpp"
#include "crown/planner/verify.hpp"
#include "residual_oracle.hpp"
#include "tree_oracle.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;
namespace planner = crown::planner;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

struct VariableRef { std::size_t value; };
struct Ignored {};
using Slot = std::variant<VariableRef, std::int64_t, Ignored>;
using Occurrence = std::vector<Slot>;
struct Fixture { Catalog catalog; Query query; };

Slot v(std::size_t value) { return VariableRef{value}; }
Slot c(std::int64_t value) { return value; }
Slot ignored() { return Ignored{}; }

Fixture fixture_for(const std::vector<Occurrence>& occurrences,
                    const std::vector<std::size_t>& head,
                    std::vector<std::size_t> table_groups = {},
                    bool contradiction = false) {
  Fixture fixture;
  if (table_groups.empty()) {
    table_groups.resize(occurrences.size());
    for (std::size_t occurrence = 0; occurrence < occurrences.size(); ++occurrence) {
      table_groups[occurrence] = occurrence;
    }
  }
  check(table_groups.size() == occurrences.size(), "test fixture table-group count differs from atom count");

  std::set<std::size_t> variable_names(head.begin(), head.end());
  std::size_t table_count = 0;
  for (std::size_t occurrence = 0; occurrence < occurrences.size(); ++occurrence) {
    table_count = std::max(table_count, table_groups[occurrence] + 1);
    for (const auto& slot : occurrences[occurrence]) {
      if (const auto* variable = std::get_if<VariableRef>(&slot)) variable_names.insert(variable->value);
    }
  }

  std::map<std::size_t, VariableId> variable_ids;
  for (const auto name : variable_names) {
    const auto id = VariableId{fixture.query.variables.size()};
    variable_ids.emplace(name, id);
    fixture.query.variables.push_back({"v" + std::to_string(name), ScalarType::int64});
  }

  std::vector<std::size_t> table_arities(table_count, 0);
  for (std::size_t occurrence = 0; occurrence < occurrences.size(); ++occurrence) {
    table_arities[table_groups[occurrence]] =
        std::max(table_arities[table_groups[occurrence]], occurrences[occurrence].size());
  }
  for (std::size_t table = 0; table < table_count; ++table) {
    Table source{"SourceTable_" + std::to_string(table), {}};
    source.source_schema_version = 17 + static_cast<std::uint64_t>(table);
    for (std::size_t column = 0; column < table_arities[table]; ++column) {
      source.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
    }
    fixture.catalog.tables.push_back(std::move(source));
  }

  fixture.query.atoms.reserve(occurrences.size());
  for (std::size_t occurrence = 0; occurrence < occurrences.size(); ++occurrence) {
    Atom atom{"source_occurrence_" + std::to_string(occurrence), TableId{table_groups[occurrence]}, {}};
    atom.terms.reserve(occurrences[occurrence].size());
    for (const auto& slot : occurrences[occurrence]) {
      if (const auto* variable = std::get_if<VariableRef>(&slot)) {
        atom.terms.emplace_back(variable_ids.at(variable->value));
      } else if (const auto* value = std::get_if<std::int64_t>(&slot)) {
        atom.terms.emplace_back(std::in_place_type<Value>, std::in_place_type<std::int64_t>, *value);
      } else {
        atom.terms.emplace_back(IgnoredColumn{});
      }
    }
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (std::size_t position = 0; position < head.size(); ++position) {
    fixture.query.head.push_back({variable_ids.at(head[position]), "out" + std::to_string(position)});
  }
  fixture.query.contradiction = contradiction;
  return fixture;
}

Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
                       const std::vector<std::size_t>& head,
                       bool contradiction = false) {
  std::vector<Occurrence> occurrences;
  occurrences.reserve(scopes.size());
  for (const auto& scope : scopes) {
    Occurrence occurrence;
    occurrence.reserve(scope.size());
    for (const auto variable : scope) occurrence.push_back(v(variable));
    occurrences.push_back(std::move(occurrence));
  }
  return fixture_for(occurrences, head, {}, contradiction);
}

std::vector<std::vector<std::size_t>> seven_scopes() {
  // Q(x,y,w): R(x,y,z,r), S(x,y,z,s), L(r), V(s), T(y,b), B(b), E(x,w).
  return {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}};
}

std::vector<std::vector<std::size_t>> nine_scopes() {
  // The nine-atom analytical variant adds U(y,a,c) and C(c).
  return {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5, 6},
          {1, 5, 7}, {6}, {7}, {0, 8}};
}

bool same_term(const Term& left, const Term& right) {
  if (left.index() != right.index()) return false;
  if (const auto* variable = std::get_if<VariableId>(&left)) {
    return *variable == std::get<VariableId>(right);
  }
  if (const auto* value = std::get_if<Value>(&left)) {
    const auto& other = std::get<Value>(right);
    if (value->index() != other.index()) return false;
    if (const auto* integer = std::get_if<std::int64_t>(value)) {
      return *integer == std::get<std::int64_t>(other);
    }
    return false;
  }
  return std::holds_alternative<IgnoredColumn>(right);
}

bool same_query(const Query& left, const Query& right) {
  if (left.contradiction != right.contradiction || left.variables.size() != right.variables.size() ||
      left.atoms.size() != right.atoms.size() || left.head.size() != right.head.size()) return false;
  for (std::size_t i = 0; i < left.variables.size(); ++i) {
    if (left.variables[i].name != right.variables[i].name || left.variables[i].type != right.variables[i].type) return false;
  }
  for (std::size_t i = 0; i < left.atoms.size(); ++i) {
    const auto& a = left.atoms[i];
    const auto& b = right.atoms[i];
    if (a.occurrence != b.occurrence || a.table != b.table || a.terms.size() != b.terms.size()) return false;
    for (std::size_t j = 0; j < a.terms.size(); ++j) if (!same_term(a.terms[j], b.terms[j])) return false;
  }
  for (std::size_t i = 0; i < left.head.size(); ++i) {
    if (left.head[i].variable != right.head[i].variable || left.head[i].alias != right.head[i].alias) return false;
  }
  return true;
}

bool same_catalog_boundary(const Catalog& left, const Catalog& right) {
  if (left.version != right.version || left.tables.size() != right.tables.size()) return false;
  for (std::size_t i = 0; i < left.tables.size(); ++i) {
    const auto& a = left.tables[i];
    const auto& b = right.tables[i];
    if (a.name != b.name || a.source_schema_version != b.source_schema_version ||
        a.columns.size() != b.columns.size()) return false;
    for (std::size_t j = 0; j < a.columns.size(); ++j) {
      if (a.columns[j].name != b.columns[j].name || a.columns[j].type != b.columns[j].type ||
          a.columns[j].nullable != b.columns[j].nullable || a.columns[j].collation != b.columns[j].collation) return false;
    }
  }
  return true;
}

bool same_anchors(const std::vector<planner::EarAnchor>& left,
                  const std::vector<planner::EarAnchor>& right) {
  if (left.size() != right.size()) return false;
  for (std::size_t i = 0; i < left.size(); ++i) {
    if (left[i].occurrence != right[i].occurrence || left[i].condition != right[i].condition) return false;
  }
  return true;
}

bool same_deletions(const std::vector<planner::EarDeletion>& left,
                    const std::vector<planner::EarDeletion>& right) {
  if (left.size() != right.size()) return false;
  for (std::size_t i = 0; i < left.size(); ++i) {
    if (left[i].occurrence != right[i].occurrence || left[i].anchor != right[i].anchor) return false;
  }
  return true;
}

void require_same_trace(const planner::ResidualTraceRecord& actual,
                        const planner::ResidualTraceRecord& expected,
                        const std::string& context) {
  check(actual.version == expected.version, context + ": trace version differs from the literal replay");
  check(actual.original_scopes == expected.original_scopes, context + ": original scopes differ from direct atom-term sets");
  check(actual.layers.size() == expected.layers.size(), context + ": frozen round count differs");
  for (std::size_t i = 0; i < actual.layers.size(); ++i) {
    const auto& a = actual.layers[i];
    const auto& e = expected.layers[i];
    check(a.members == e.members, context + ": live member set differs at a round boundary");
    check(a.variables == e.variables && a.head == e.head && a.unique == e.unique,
          context + ": round V/F/U differs from direct set counting");
    check(a.ears.size() == e.ears.size(), context + ": frozen eligible-ear count differs");
    for (std::size_t j = 0; j < a.ears.size(); ++j) {
      check(a.ears[j].occurrence == e.ears[j].occurrence && a.ears[j].shared == e.ears[j].shared &&
            a.ears[j].unique == e.ears[j].unique && same_anchors(a.ears[j].anchors, e.ears[j].anchors),
            context + ": eligible ear, shared/unique split, anchor set or condition bits differ");
    }
    check(same_deletions(a.deletions, e.deletions), context + ": deterministic deletion schedule differs");
    check(a.remaining == e.remaining && a.residual_head == e.residual_head,
          context + ": post-round members or induced head differ");
  }
  check(actual.terminal_members == expected.terminal_members && actual.terminal_head == expected.terminal_head &&
        actual.terminal == expected.terminal,
        context + ": terminal state differs from independent q-hierarchy replay");

  const auto& a = actual.terminal_view;
  const auto& e = expected.terminal_view;
  check(a.original_occurrences == e.original_occurrences && a.original_variables == e.original_variables &&
        a.occurrence_to_local == e.occurrence_to_local && a.variable_to_local == e.variable_to_local,
        context + ": terminal view forward or inverse ID maps differ");
  check(same_query(a.query, e.query), context + ": terminal dense query lost ordered terms, types, outputs or contradiction metadata");
}

bool same_statistics(const planner::ResidualStatistics& a, const planner::ResidualStatistics& b) {
  return a.hierarchy_tests == b.hierarchy_tests && a.rounds == b.rounds &&
         a.eligibility_pairs == b.eligibility_pairs && a.deletions == b.deletions &&
         a.restorations == b.restorations && a.drafts == b.drafts &&
         a.rejected_drafts == b.rejected_drafts && a.generalized_grafts == b.generalized_grafts &&
         a.exact_repairs == b.exact_repairs && a.original_exact_runs == b.original_exact_runs &&
         a.candidate_publications == b.candidate_publications && a.admissions == b.admissions;
}

bool same_search_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) {
  return a.work == b.work && a.states == b.states && a.partitions == b.partitions &&
         a.candidates == b.candidates && a.cache_hits == b.cache_hits &&
         a.certificate_work == b.certificate_work && a.hierarchy_tests == b.hierarchy_tests &&
         a.hierarchy_hits == b.hierarchy_hits && a.singleton_hits == b.singleton_hits &&
         a.empty_body_hits == b.empty_body_hits && a.component_splits == b.component_splits &&
         a.symmetry_skips == b.symmetry_skips && a.bound_prunes == b.bound_prunes;
}

bool same_search_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result &&
         a.heights == b.heights && a.producer_complete == b.producer_complete &&
         a.proof_complete == b.proof_complete && a.producer == b.producer && a.replay == b.replay &&
         same_search_statistics(a.structural, b.structural) && a.limit_revision == b.limit_revision;
}

bool same_progress(const planner::ResidualProgress& a, const planner::ResidualProgress& b) {
  return a.phase == b.phase && a.result == b.result && a.proof_status == b.proof_status &&
         a.last_stop == b.last_stop && a.exact_stop == b.exact_stop && a.heights == b.heights &&
         a.work == b.work && same_statistics(a.statistics, b.statistics) && a.records == b.records &&
         a.cells == b.cells && a.limit_revision == b.limit_revision && a.trace_complete == b.trace_complete &&
         a.trace_verified == b.trace_verified && a.exact_scope_original == b.exact_scope_original &&
         same_search_progress(a.exact_progress, b.exact_progress);
}

void check_monotone(const planner::ResidualProgress& before,
                    const planner::ResidualProgress& after,
                    const std::string& context) {
  check(after.work.attempted >= before.work.attempted &&
        after.work.committed_transitions >= before.work.committed_transitions &&
        after.work.allocation_failures >= before.work.allocation_failures &&
        after.work.active_nanoseconds >= before.work.active_nanoseconds &&
        after.work.peak_depth >= before.work.peak_depth,
        context + ": residual work counters moved backward");
  check(after.records >= before.records && after.cells >= before.cells &&
        after.limit_revision >= before.limit_revision,
        context + ": retained-content counters or limit revision moved backward");
  check(after.statistics.hierarchy_tests >= before.statistics.hierarchy_tests &&
        after.statistics.rounds >= before.statistics.rounds &&
        after.statistics.eligibility_pairs >= before.statistics.eligibility_pairs &&
        after.statistics.deletions >= before.statistics.deletions &&
        after.statistics.restorations >= before.statistics.restorations &&
        after.statistics.drafts >= before.statistics.drafts &&
        after.statistics.rejected_drafts >= before.statistics.rejected_drafts &&
        after.statistics.generalized_grafts >= before.statistics.generalized_grafts &&
        after.statistics.exact_repairs >= before.statistics.exact_repairs &&
        after.statistics.original_exact_runs >= before.statistics.original_exact_runs &&
        after.statistics.candidate_publications >= before.statistics.candidate_publications &&
        after.statistics.admissions >= before.statistics.admissions,
        context + ": residual diagnostics moved backward");
}

enum class Slicing { unsliced, unit, varied };

planner::ResidualOptions options_for(planner::ResidualMode mode = planner::ResidualMode::candidates_with_exact_repair) {
  planner::ResidualOptions options;
  options.mode = mode;
  options.limits.residual.work = 50'000'000;
  options.limits.logical_depth = 1024;
  options.limits.record_limit = 1'000'000;
  options.limits.cell_limit = 10'000'000;
  options.limits.exact.producer.work = 50'000'000;
  options.limits.exact.replay.work = 50'000'000;
  options.limits.exact.logical_depth = 1024;
  return options;
}

planner::WorkQuantum quantum_for(Slicing slicing, std::size_t step) {
  constexpr std::array<std::uint64_t, 4> grants{3, 1, 5, 2};
  if (slicing == Slicing::unit) return {1, {}};
  if (slicing == Slicing::varied) return {grants[step % grants.size()], {}};
  return {50'000'000, {}};
}

struct CompletedRun {
  planner::ResidualProgress progress;
  std::optional<planner::ResidualTrace> trace;
  std::optional<planner::ResidualCandidate> candidate;
  std::optional<planner::VerifiedOptimum> optimum;
  std::optional<planner::VerifiedInfeasible> infeasibility;
  std::set<planner::ResidualPhase> residual_phases;
  std::set<planner::SearchPhase> exact_phases;
  std::set<planner::ResidualStopReason> residual_stops;
  std::set<planner::StopReason> exact_stops;
};

void check_valid_candidate(const Fixture& fixture, const planner::ResidualCandidate& candidate,
                           const std::string& context);

CompletedRun run_to_completion(const Fixture& fixture, planner::ResidualMode mode, Slicing slicing,
                               planner::ResidualOptions options = {}) {
  if (options.limits.residual.work == planner::ResidualLimits{}.residual.work) {
    options = options_for(mode);
  }
  options.mode = mode;
  auto owner = planner::ResidualSearch::create(fixture.catalog, fixture.query, options);
  CompletedRun result;
  constexpr std::size_t max_steps = 5'000'000;
  for (std::size_t step = 0; step < max_steps; ++step) {
    const auto before = owner.progress();
    const auto advanced = owner.advance(quantum_for(slicing, step));
    check_monotone(before, advanced.progress, "residual continuation");
    result.residual_phases.insert(advanced.progress.phase);
    result.exact_phases.insert(advanced.progress.exact_progress.phase);
    result.residual_stops.insert(advanced.stopped_for);
    result.exact_stops.insert(advanced.exact_reason);
    if (advanced.progress.result == planner::ResidualResult::failed) {
      throw std::runtime_error("residual continuation failed with residual reason " +
                               std::to_string(static_cast<int>(advanced.stopped_for)) +
                               " and exact reason " +
                               std::to_string(static_cast<int>(advanced.exact_reason)));
    }
    if (advanced.progress.result == planner::ResidualResult::unfinished) {
      check(!owner.exact_original() && !owner.infeasibility(),
            "unfinished P05 continuation published original-query proof authority");
    }
    if (advanced.progress.result != planner::ResidualResult::unfinished) {
      check(advanced.stopped_for == planner::ResidualStopReason::complete,
            "terminal residual result lacks a complete stop reason");
      result.progress = advanced.progress;
      result.trace = owner.trace();
      result.candidate = owner.candidate();
      result.optimum = owner.exact_original();
      result.infeasibility = owner.infeasibility();
      if (result.candidate) check_valid_candidate(fixture, *result.candidate, "published P05 candidate");
      if (result.optimum) {
        const auto upper = result.optimum->upper();
        const auto validation = planner::validate_tree(fixture.catalog, fixture.query, upper.tree());
        check(validation.valid && validation.native_height && *validation.native_height == result.optimum->height(),
              "verified original optimum did not retain a P02-checked upper witness");
      }
      return result;
    }
    check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
          advanced.stopped_for == planner::ResidualStopReason::quantum_time,
          "unlimited residual continuation stopped for a total resource ceiling");
  }
  throw std::runtime_error("residual continuation exceeded the step guard");
}

planner::ResidualTrace trace_only(const Fixture& fixture) {
  auto owner = planner::ResidualSearch::create(fixture.catalog, fixture.query, options_for());
  for (std::size_t step = 0; step < 1'000'000; ++step) {
    const auto advanced = owner.advance({50'000'000, {}});
    check(advanced.progress.result != planner::ResidualResult::failed,
          "trace production failed before publishing a replayable trace");
    if (const auto trace = owner.trace(); trace && advanced.progress.trace_verified) return *trace;
    if (advanced.progress.result != planner::ResidualResult::unfinished) break;
  }
  throw std::runtime_error("residual provider completed without publishing its verified trace");
}

void audit_trace(const Fixture& fixture, const std::string& context) {
  const auto trace = trace_only(fixture);
  check(trace.valid(), context + ": published trace handle is invalid");
  const auto expected = reference::frozen_residual_trace(fixture.query);
  require_same_trace(trace.record(), expected, context);
  check(same_query(trace.query(), fixture.query), context + ": trace binding changed the original Query");
  check(same_catalog_boundary(trace.catalog(), fixture.catalog),
        context + ": trace binding crossed the original Catalog/source metadata boundary");
  const auto report = planner::verify_residual_trace(fixture.catalog, fixture.query, trace.record());
  check(report.valid && !report.resource_limit && report.rule == planner::ResidualTraceRule::none,
        context + ": independent native trace replay rejected the producer record");
  if (!fixture.query.atoms.empty()) {
    check(report.work > 0, context + ": nonempty native trace replay reported no work");
  }
}

void audit_trace_handle(const Fixture& fixture, const planner::ResidualTrace& trace,
                        const std::string& context) {
  check(trace.valid(), context + ": published trace handle is invalid");
  const auto expected = reference::frozen_residual_trace(fixture.query);
  require_same_trace(trace.record(), expected, context);
  check(same_query(trace.query(), fixture.query), context + ": trace binding changed the original Query");
  check(same_catalog_boundary(trace.catalog(), fixture.catalog),
        context + ": trace binding crossed the original Catalog/source metadata boundary");
  const auto report = planner::verify_residual_trace(fixture.catalog, fixture.query, trace.record());
  check(report.valid && !report.resource_limit && report.rule == planner::ResidualTraceRule::none,
        context + ": independent native trace replay rejected the producer record");
  if (!fixture.query.atoms.empty()) {
    check(report.work > 0, context + ": nonempty native trace replay reported no work");
  }
}

void check_valid_candidate(const Fixture& fixture, const planner::ResidualCandidate& candidate,
                           const std::string& context) {
  check(candidate.valid(), context + ": invalid candidate handle");
  check(same_query(candidate.query(), fixture.query) && same_catalog_boundary(candidate.catalog(), fixture.catalog),
        context + ": candidate is not bound to the complete original query/catalog");
  const auto validation = planner::validate_tree(fixture.catalog, fixture.query, candidate.tree());
  check(validation.valid && validation.native_height && *validation.native_height == candidate.height(),
        context + ": candidate is not a P02-checked full-original-query tree at its actual height");
  std::vector<std::size_t> native;
  for (const auto& node : candidate.tree().nodes) {
    if (node.kind == NodeKind::native) {
      check(node.occurrence.has_value(), context + ": native candidate node lost its original occurrence");
      native.push_back(*node.occurrence);
    }
  }
  std::sort(native.begin(), native.end());
  std::vector<std::size_t> expected(fixture.query.atoms.size());
  for (std::size_t i = 0; i < expected.size(); ++i) expected[i] = i;
  check(native == expected, context + ": candidate omitted, merged or duplicated source occurrences");
}

void small_p03_and_trace_family() {
  std::size_t comparisons = 0;
  for (unsigned first = 0; first < 4; ++first) {
    for (unsigned second = 0; second < 4; ++second) {
      for (unsigned third = 0; third < 4; ++third) {
       const unsigned used = first | second | third;
       for (unsigned head_mask = 0; head_mask < 4; ++head_mask) {
        if ((head_mask & used) != head_mask) continue;
        std::vector<std::vector<std::size_t>> scopes(3);
        for (std::size_t variable = 0; variable < 2; ++variable) {
          if ((first & (1U << variable)) != 0) scopes[0].push_back(variable);
          if ((second & (1U << variable)) != 0) scopes[1].push_back(variable);
          if ((third & (1U << variable)) != 0) scopes[2].push_back(variable);
        }
        std::vector<std::size_t> head;
        for (std::size_t variable = 0; variable < 2; ++variable) {
          if ((head_mask & (1U << variable)) != 0) head.push_back(variable);
        }
        const auto fixture = scoped_fixture(scopes, head);
        const auto candidate_run = run_to_completion(fixture,
            planner::ResidualMode::candidates_with_exact_repair, Slicing::varied, options_for());
        check(candidate_run.trace && candidate_run.progress.trace_verified,
              "candidate-mode P05 run did not publish its checked frozen trace");
        audit_trace_handle(fixture, *candidate_run.trace, "three-atom finite family");

        const auto frozen_original = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
        check(frozen_original.status != planner::OracleStatus::resource_limit,
              "frozen P03 original oracle exhausted on a three-atom finite family");
        if (candidate_run.candidate) check_valid_candidate(fixture, *candidate_run.candidate,
                                                            "three-atom P05 candidate family");
        if (frozen_original.status == planner::OracleStatus::proven_minimum) {
          check(candidate_run.candidate || candidate_run.optimum,
                "candidate-mode P05 run found no full-query upper bound for a feasible small case");
          if (candidate_run.candidate) {
            check(candidate_run.candidate->height() >= *frozen_original.minimum_height,
                  "P05 candidate is below the frozen P03 minimum");
          }
          if (candidate_run.optimum) {
            check(candidate_run.optimum->height() == *frozen_original.minimum_height,
                  "candidate-mode P05 exact fallback disagrees with frozen P03");
          }
        } else {
          check(candidate_run.progress.result == planner::ResidualResult::verified_infeasible &&
                candidate_run.infeasibility,
                "candidate-mode P05 run did not use full-query proof fallback for an unsupported small case");
        }

        const auto exact_run = run_to_completion(fixture,
            planner::ResidualMode::require_exact_original, Slicing::varied, options_for());
        check(exact_run.trace.has_value(), "default P05 exact mode did not publish its own frozen trace");
        audit_trace_handle(fixture, *exact_run.trace, "three-atom default exact family");
        require_same_trace(exact_run.trace->record(), candidate_run.trace->record(),
                           "candidate and exact modes on the same original binding");
        if (frozen_original.status == planner::OracleStatus::proven_minimum) {
          check(exact_run.progress.result == planner::ResidualResult::verified_optimum && exact_run.optimum &&
                exact_run.optimum->height() == *frozen_original.minimum_height &&
                exact_run.progress.exact_scope_original,
                "default P05 exact mode differs from frozen P03 on the original query");
          check(planner::verify_height_certificate(fixture.catalog, fixture.query,
                                                    exact_run.optimum->certificate()).valid,
                "default P05 exact mode failed independent proof replay on the original query");
        } else {
          check(exact_run.progress.result == planner::ResidualResult::verified_infeasible &&
                exact_run.infeasibility,
                "default P05 exact mode did not prove original-query infeasibility");
        }
        const auto& expected = candidate_run.trace->record();
        const auto exact_residual = planner::minimum_tree(fixture.catalog, expected.terminal_view.query);
        const auto frozen_residual = reference::exhaustive_minimum_tree(fixture.catalog, expected.terminal_view.query);
        check(exact_residual.status != planner::OracleStatus::resource_limit &&
              frozen_residual.status != planner::OracleStatus::resource_limit &&
              exact_residual.status == frozen_residual.status &&
              exact_residual.minimum_height == frozen_residual.minimum_height,
              "P06 induced-residual height differs from frozen P03 on the small family");
        ++comparisons;
       }
      }
    }
  }
  check(comparisons == 225, "finite three-atom P03 differential family changed unexpectedly");
}

void named_semantic_cases() {
  audit_trace(scoped_fixture({}, {}), "empty body");
  audit_trace(scoped_fixture({{0}}, {0}), "singleton atom");
  audit_trace(scoped_fixture({{}}, {}), "nullary atom");
  audit_trace(scoped_fixture({{0}, {1}}, {0, 1}), "disconnected q-hierarchical body");
  audit_trace(scoped_fixture({{0, 1}, {0, 1}, {1}}, {0, 0}), "duplicate scopes with repeated head output");
  audit_trace(scoped_fixture({{0, 1}, {0, 1}, {1}}, {0}, true), "contradictory structural input");

  const auto distinct_tables = fixture_for({{v(0), v(1)}, {v(0), v(1)}, {v(1), ignored()}},
                                           {0}, {0, 1, 2});
  audit_trace(distinct_tables, "equal scopes on distinct original tables");

  const auto self_join = fixture_for({{v(0), v(1)}, {v(0), v(1)}, {v(1), ignored()}},
                                     {0}, {0, 0, 0});
  audit_trace(self_join, "self-join occurrences over one original table");

  const auto terms = fixture_for({{v(0), v(0), c(17), ignored()},
                                  {v(0), v(1), c(17), ignored()},
                                  {v(1), v(1), c(17), ignored()}},
                                 {0, 0, 1}, {0, 1, 2}, true);
  const auto terms_trace = trace_only(terms);
  const auto& dense = terms_trace.record().terminal_view;
  check(same_query(terms_trace.query(), terms.query), "typed-term fixture lost its original query binding");
  check(dense.query.contradiction && dense.query.head.size() == 3 &&
        dense.query.head[0].variable == dense.query.head[1].variable &&
        dense.query.head[0].alias != dense.query.head[1].alias,
        "dense terminal view did not preserve contradiction or ordered repeated head positions");
  audit_trace(terms, "constants, ignored columns, repeated variables and ordered repeated head");

  const std::vector<std::vector<std::size_t>> triangle{{0, 1}, {1, 2}, {0, 2}};
  const auto stalled = scoped_fixture(triangle, {});
  const auto stalled_trace = trace_only(stalled);
  check(stalled_trace.record().terminal == planner::ResidualTerminal::stalled,
        "unreduced crossing incidence did not finish at the stalled terminal");
  audit_trace(stalled, "stalled cyclic incidence");

  // Removing C and A changes U so E becomes an ear only in the next frozen
  // round. The untouched triangle keeps the induced residual nonhierarchical.
  const auto delayed = scoped_fixture({{1}, {0, 1}, {0}, {0, 2},
                                       {3, 4}, {4, 5}, {3, 5}}, {2});
  const auto delayed_reference = reference::frozen_residual_trace(delayed.query);
  check(delayed_reference.layers.size() >= 2 &&
        std::none_of(delayed_reference.layers[0].ears.begin(), delayed_reference.layers[0].ears.end(),
                     [](const planner::EarRecord& ear) { return ear.occurrence == 1; }) &&
        std::any_of(delayed_reference.layers[1].ears.begin(), delayed_reference.layers[1].ears.end(),
                    [](const planner::EarRecord& ear) { return ear.occurrence == 1; }),
        "analytic delayed-ear fixture no longer requires a new frozen round");
  audit_trace(delayed, "new ear waits for the next frozen round");

  std::vector<std::vector<std::size_t>> deep_scopes(70);
  std::vector<std::size_t> deep_head;
  for (std::size_t variable = 0; variable < 70; ++variable) {
    deep_head.push_back(variable);
    for (std::size_t occurrence = variable; occurrence < 70; ++occurrence) {
      deep_scopes[occurrence].push_back(variable);
    }
  }
  const auto deep = scoped_fixture(deep_scopes, deep_head);
  check(deep.query.variables.size() > 64 && deep.query.atoms.size() > 64,
        "dynamic residual fixture must exceed fixed 64-bit widths");
  audit_trace(deep, "70-variable and 70-occurrence nested incidence chain");
}

void verify_counterexamples_and_authority() {
  const auto seven = scoped_fixture(seven_scopes(), {0, 1, 6});
  const auto nine = scoped_fixture(nine_scopes(), {0, 1, 8});
  bool exercised_exact_repair = false;
  for (const auto& [fixture, name, residual_atoms] :
       std::vector<std::tuple<Fixture, std::string, std::size_t>>{
           {seven, "seven-atom residual counterexample", 3},
           {nine, "nine-atom residual counterexample", 4}}) {
    const auto slicing = name == "seven-atom residual counterexample" ? Slicing::unit : Slicing::varied;
    const auto exact_run = run_to_completion(fixture, planner::ResidualMode::require_exact_original,
                                             slicing, options_for(planner::ResidualMode::require_exact_original));
    const auto& final_progress = exact_run.progress;
    check(final_progress.result == planner::ResidualResult::verified_optimum &&
          exact_run.residual_phases.contains(planner::ResidualPhase::exact_original),
          name + ": exact-required mode did not finish original-query proof");
    check(final_progress.proof_status == planner::ResidualProofStatus::exact_original_verified &&
          final_progress.exact_scope_original,
          name + ": verified result is not explicitly bound to the original query");
    const auto optimum = exact_run.optimum;
    check(optimum && optimum->valid() && optimum->height() == 3,
          name + ": original minimum is not independently proved at height three");
    check(exact_run.exact_phases.contains(planner::SearchPhase::replay),
          name + ": original exact proof did not expose its independent replay phase");
    const auto binding = optimum->binding();
    check(same_catalog_boundary(binding.catalog(), fixture.catalog) && same_query(binding.query(), fixture.query),
          name + ": exact authority is bound to the terminal residual instead of the original input");
    check(planner::verify_height_certificate(fixture.catalog, fixture.query, optimum->certificate()).valid,
          name + ": original exact certificate failed independent P06 replay");

    const auto trace = exact_run.trace;
    check(trace && trace->valid(), name + ": exact completion lost its residual trace");
    audit_trace_handle(fixture, *trace, name);
    check(trace->record().layers.size() == 1 && !trace->record().layers[0].deletions.empty() &&
          trace->record().terminal == planner::ResidualTerminal::hierarchical &&
          trace->record().terminal_members.size() == residual_atoms,
          name + ": expected exactly one productive frozen round to a smaller hierarchical residual");
    const auto residual_minimum = reference::exhaustive_minimum_tree(fixture.catalog, trace->record().terminal_view.query);
    check(residual_minimum.status == planner::OracleStatus::proven_minimum && residual_minimum.minimum_height == 1,
          name + ": frozen P03 oracle did not confirm the height-one terminal query");

    if (exact_run.candidate) {
      const auto& candidate = exact_run.candidate;
      check_valid_candidate(fixture, *candidate, name);
      check(candidate->height() >= 3,
            name + ": a residual-round arithmetic claim escaped as a height-two full-query candidate");
    }
    check(final_progress.statistics.rounds == 1,
          name + ": round counter differs from the one-layer published trace");
    if (name == "seven-atom residual counterexample") {
      exercised_exact_repair = final_progress.statistics.exact_repairs > 0 &&
                               exact_run.residual_phases.contains(planner::ResidualPhase::repair);
    }
  }
  check(exercised_exact_repair,
        "incomplete reconstruction family did not enter checked exact repair on the seven-atom case");
}

Fixture wrong_anchor_fixture() {
  // R(x,a), A(x,a,b), B(x,b,c), C(x,c,d), U(x,d), E(x,w); head {x,w}.
  return scoped_fixture({{0, 1}, {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4}, {0, 5}}, {0, 5});
}

Fixture generalized_augmentation_fixture() {
  // P(a,z,x), R(a,z,y), L(x), U(y), S(a,c); head {a,c}.
  return scoped_fixture({{0, 1, 2}, {0, 1, 3}, {2}, {3}, {0, 4}}, {0, 4});
}

void candidate_reconstruction_and_ownership() {
  const auto augmentation = generalized_augmentation_fixture();
  auto candidate_run = run_to_completion(augmentation, planner::ResidualMode::candidates_with_exact_repair,
                                        Slicing::unit, options_for());
  check(candidate_run.progress.result == planner::ResidualResult::checked_candidate &&
        candidate_run.progress.proof_status == planner::ResidualProofStatus::checked_upper_only &&
        !candidate_run.optimum && !candidate_run.infeasibility && candidate_run.candidate,
        "candidate policy did not stop with only a checked original-query upper bound");
  check_valid_candidate(augmentation, *candidate_run.candidate, "generalized augmentation");
  check(candidate_run.candidate->height() == 2,
        "generalized {a,z}->{a} augmentation did not restore a valid height-two candidate");
  check(candidate_run.progress.statistics.generalized_grafts > 0,
        "generalized augmentation never exercised a graft restoration");
  check(candidate_run.progress.heights.upper == candidate_run.candidate->height(),
        "candidate upper interval does not match its actual P02-checked height");
  check(candidate_run.progress.heights.lower_evidence == planner::BoundEvidence::universal,
        "candidate-only mode reported residual rounds as exact lower-bound evidence");
  check(candidate_run.progress.statistics.rounds == 1,
        "augmentation fixture did not retain its one-round diagnostic count");
  check(candidate_run.candidate->origin() != planner::ResidualOrigin::exact_original,
        "candidate-only mode forged exact-original provenance");
  for (const auto phase : {planner::ResidualPhase::scopes, planner::ResidualPhase::recognize,
                           planner::ResidualPhase::eligibility, planner::ResidualPhase::delete_ears,
                           planner::ResidualPhase::seal_layer, planner::ResidualPhase::trace_replay,
                           planner::ResidualPhase::seed, planner::ResidualPhase::restore,
                           planner::ResidualPhase::validate_candidate}) {
    check(candidate_run.residual_phases.contains(phase),
          "unit-quantum candidate run skipped a resumable residual phase");
  }

  const auto wrong_anchor = wrong_anchor_fixture();
  const auto wrong_anchor_run = run_to_completion(wrong_anchor,
      planner::ResidualMode::candidates_with_exact_repair, Slicing::varied, options_for());
  check(wrong_anchor_run.candidate.has_value(),
        "wrong-anchor chain did not produce a checked candidate or use complete exact repair");
  check_valid_candidate(wrong_anchor, *wrong_anchor_run.candidate, "wrong-anchor restoration chain");
  check(wrong_anchor_run.progress.proof_status == planner::ResidualProofStatus::checked_upper_only &&
        !wrong_anchor_run.optimum,
        "wrong-anchor candidate was confused with an original-query minimum proof");
  if (wrong_anchor_run.candidate->origin() == planner::ResidualOrigin::exact_repair) {
    check(wrong_anchor_run.progress.statistics.exact_repairs > 0,
          "exact-repair candidate provenance lacks a recorded P06 repair");
  }

  std::optional<planner::ResidualTrace> kept_trace;
  std::optional<planner::ResidualCandidate> kept_candidate;
  {
    auto owner = planner::ResidualSearch::create(augmentation.catalog, augmentation.query, options_for());
    for (std::size_t step = 0; step < 1'000'000; ++step) {
      const auto advanced = owner.advance({50'000'000, {}});
      if (advanced.progress.result == planner::ResidualResult::failed) {
        throw std::runtime_error("retained-handle search failed before publication");
      }
      if (owner.trace() && owner.candidate()) {
        kept_trace = owner.trace();
        kept_candidate = owner.candidate();
        break;
      }
      if (advanced.progress.result != planner::ResidualResult::unfinished) break;
    }
    check(kept_trace && kept_candidate, "test could not retain immutable residual handles");
    owner.cancel();
  }
  check(kept_trace->valid() && kept_candidate->valid(),
        "immutable trace/candidate handles did not outlive their owner");
  require_same_trace(kept_trace->record(), reference::frozen_residual_trace(augmentation.query),
                     "retained trace handle");
  check_valid_candidate(augmentation, *kept_candidate, "retained candidate handle");

  auto source = augmentation;
  const auto original_copy = augmentation;
  auto owning_search = planner::ResidualSearch::create(source.catalog, source.query, options_for());
  source.catalog.tables.clear();
  source.query.atoms.clear();
  check(same_catalog_boundary(owning_search.catalog(), original_copy.catalog) &&
        same_query(owning_search.query(), original_copy.query),
        "residual owner borrowed caller-mutable input instead of retaining its original binding");
  auto moved = std::move(owning_search);
  check(owning_search.progress().phase == planner::ResidualPhase::moved_from,
        "moving a residual owner left the source facade active");
  check(owning_search.advance({1, {}}).progress.phase == planner::ResidualPhase::moved_from,
        "advancing a moved-from residual owner did not report its terminal state");
  moved.cancel();
  check(moved.progress().phase == planner::ResidualPhase::cancelled,
        "cancel did not leave a stable cancelled history");
}

void residual_ceiling_extensions_resume() {
  const auto augmentation = generalized_augmentation_fixture();
  const auto baseline = run_to_completion(augmentation,
      planner::ResidualMode::candidates_with_exact_repair, Slicing::varied, options_for());
  check(baseline.candidate && baseline.trace, "resource-resume baseline lacks a candidate or trace");

  enum class Ceiling { work, depth, records, cells };
  for (const auto ceiling : {Ceiling::work, Ceiling::depth, Ceiling::records, Ceiling::cells}) {
    auto options = options_for();
    planner::ResidualStopReason expected_stop = planner::ResidualStopReason::none;
    switch (ceiling) {
      case Ceiling::work:
        options.limits.residual.work = 0;
        expected_stop = planner::ResidualStopReason::total_work;
        break;
      case Ceiling::depth:
        options.limits.logical_depth = 0;
        expected_stop = planner::ResidualStopReason::depth_limit;
        break;
      case Ceiling::records:
        options.limits.record_limit = 0;
        expected_stop = planner::ResidualStopReason::record_limit;
        break;
      case Ceiling::cells:
        options.limits.cell_limit = 0;
        expected_stop = planner::ResidualStopReason::cell_limit;
        break;
    }
    auto owner = planner::ResidualSearch::create(augmentation.catalog, augmentation.query, options);
    const auto stopped = owner.advance({50'000, {}});
    check(stopped.stopped_for == expected_stop && stopped.progress.last_stop == expected_stop &&
          stopped.progress.result == planner::ResidualResult::unfinished &&
          !owner.exact_original() && !owner.infeasibility(),
          "residual resource ceiling did not produce its specific honest stop");
    const auto revision = stopped.progress.limit_revision;
    auto raised = owner.options().limits;
    switch (ceiling) {
      case Ceiling::work: raised.residual.work = 50'000'000; break;
      case Ceiling::depth: raised.logical_depth = 1024; break;
      case Ceiling::records: raised.record_limit = 1'000'000; break;
      case Ceiling::cells: raised.cell_limit = 10'000'000; break;
    }
    check(owner.raise_limits(raised) == planner::LimitChange::applied &&
          owner.progress().limit_revision > revision,
          "monotone residual work/depth/record/cell extension was rejected");

    for (std::size_t step = 0; step < 2'000'000; ++step) {
      const auto before = owner.progress();
      const auto advanced = owner.advance(quantum_for(Slicing::varied, step));
      check_monotone(before, advanced.progress, "residual resource resume");
      if (advanced.progress.result == planner::ResidualResult::failed) {
        throw std::runtime_error("raised residual ceiling did not resume the pending construction");
      }
      if (advanced.progress.result != planner::ResidualResult::unfinished) {
        check(advanced.progress.result == planner::ResidualResult::checked_candidate && owner.candidate(),
              "resumed candidate mode did not complete with its checked upper bound");
        check_valid_candidate(augmentation, *owner.candidate(), "resumed residual candidate");
        const auto trace = owner.trace();
        check(trace && baseline.trace, "resumed residual run lost its trace");
        require_same_trace(trace->record(), baseline.trace->record(), "resource-resumed trace");
        check(owner.candidate()->height() == baseline.candidate->height(),
              "raising a residual ceiling changed the completed candidate height");
        break;
      }
      check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
            advanced.stopped_for == planner::ResidualStopReason::quantum_time,
            "resumed construction hit a second unraised resource ceiling");
      if (step + 1 == 2'000'000) throw std::runtime_error("resumed residual ceiling exceeded the step guard");
    }
  }
}

void slicing_zero_quantum_and_limit_resume() {
  const auto augmentation = generalized_augmentation_fixture();
  const auto unsliced = run_to_completion(augmentation, planner::ResidualMode::candidates_with_exact_repair,
                                          Slicing::unsliced, options_for());
  const auto unit = run_to_completion(augmentation, planner::ResidualMode::candidates_with_exact_repair,
                                      Slicing::unit, options_for());
  const auto varied = run_to_completion(augmentation, planner::ResidualMode::candidates_with_exact_repair,
                                        Slicing::varied, options_for());
  check(unsliced.candidate && unit.candidate && varied.candidate,
        "sliced candidate runs did not all publish a checked upper bound");
  check(unsliced.trace && unit.trace && varied.trace,
        "sliced candidate runs did not all publish their frozen trace");
  require_same_trace(unsliced.trace->record(), unit.trace->record(), "unit quantum trace");
  require_same_trace(unsliced.trace->record(), varied.trace->record(), "varied quantum trace");
  check(unsliced.progress.result == unit.progress.result && unit.progress.result == varied.progress.result &&
        unsliced.progress.proof_status == unit.progress.proof_status &&
        unit.progress.proof_status == varied.progress.proof_status &&
        unsliced.candidate->height() == unit.candidate->height() &&
        unit.candidate->height() == varied.candidate->height(),
        "quantum slicing changed the candidate result or actual height");
  check(unsliced.progress.work.committed_transitions == unit.progress.work.committed_transitions &&
        unit.progress.work.committed_transitions == varied.progress.work.committed_transitions,
        "quantum slicing changed committed logical work");
  check(unsliced.progress.records == unit.progress.records && unit.progress.records == varied.progress.records &&
        unsliced.progress.cells == unit.progress.cells && unit.progress.cells == varied.progress.cells,
        "quantum slicing changed retained record/cell accounting");

  auto owner = planner::ResidualSearch::create(augmentation.catalog, augmentation.query, options_for());
  const auto before = owner.progress();
  const auto zero = owner.advance({0, {}});
  check(zero.stopped_for == planner::ResidualStopReason::quantum_work &&
        same_progress(before, zero.progress) && same_progress(before, owner.progress()),
        "zero work quantum was not inert");
  const auto zero_time = owner.advance({1, std::chrono::nanoseconds{0}});
  check(zero_time.stopped_for == planner::ResidualStopReason::quantum_time &&
        same_progress(before, zero_time.progress),
        "zero active-time quantum changed residual state");

  const auto seven = scoped_fixture(seven_scopes(), {0, 1, 6});
  auto exact_options = options_for(planner::ResidualMode::require_exact_original);
  // A shared zero replay grant would stop the induced seed first. Calibrate
  // enough replay work for every actual prefix owner, then interrupt the
  // larger original proof. Counts are observed through the public API.
  auto calibration = planner::ResidualSearch::create(seven.catalog, seven.query, exact_options);
  std::uint64_t prefix_replay_work = 0;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto update = calibration.advance({1, {}});
    if (!update.progress.exact_scope_original)
      prefix_replay_work = std::max(prefix_replay_work, update.progress.exact_progress.replay.attempted);
    if (update.progress.result == planner::ResidualResult::verified_optimum) break;
    check(update.stopped_for == planner::ResidualStopReason::quantum_work,
          "original replay calibration stopped unexpectedly");
  }
  check(calibration.exact_original() && prefix_replay_work > 0 &&
        calibration.progress().exact_progress.replay.attempted > prefix_replay_work,
        "original replay fixture has no grant separating prefix and original proof work");
  exact_options.limits.exact.replay.work = prefix_replay_work;
  auto strict = planner::ResidualSearch::create(seven.catalog, seven.query, exact_options);
  std::set<planner::ResidualPhase> seen_residual;
  std::set<planner::SearchPhase> seen_exact;
  bool stopped_in_original_replay = false;
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto before_step = strict.progress();
    const auto advanced = strict.advance({1, {}});
    check_monotone(before_step, advanced.progress, "unit exact-required residual pause");
    seen_residual.insert(advanced.progress.phase);
    seen_exact.insert(advanced.progress.exact_progress.phase);
    if (advanced.progress.phase == planner::ResidualPhase::failed) {
      throw std::runtime_error("original replay budget incorrectly failed the residual owner");
    }
    if (advanced.progress.last_stop == planner::ResidualStopReason::exact_limit &&
        advanced.progress.exact_stop == planner::StopReason::total_work) {
      stopped_in_original_replay = true;
      check(advanced.progress.exact_scope_original,
            "replay calibration interrupted an induced prefix instead of the original proof");
      check(!strict.exact_original() && !strict.infeasibility() &&
            advanced.progress.result == planner::ResidualResult::unfinished,
            "inner exact replay budget stop leaked partial minimum authority");
      check(advanced.stopped_for == planner::ResidualStopReason::exact_limit,
            "exact resource stop lost its outer residual-specific reason");
      break;
    }
    check(advanced.stopped_for == planner::ResidualStopReason::quantum_work ||
          advanced.stopped_for == planner::ResidualStopReason::quantum_time,
          "strict search stopped before reaching the original replay ceiling");
  }
  check(stopped_in_original_replay && seen_residual.contains(planner::ResidualPhase::eligibility) &&
        seen_residual.contains(planner::ResidualPhase::delete_ears) &&
        seen_residual.contains(planner::ResidualPhase::trace_replay) &&
        seen_residual.contains(planner::ResidualPhase::validate_candidate) &&
        seen_residual.contains(planner::ResidualPhase::exact_original) &&
        seen_exact.contains(planner::SearchPhase::replay),
        "unit quanta did not pause through reduction, validation and original proof replay");

  const auto revision_before_raise = strict.progress().limit_revision;
  auto raised = strict.options().limits;
  raised.exact.replay.work = 50'000'000;
  check(strict.raise_limits(raised) == planner::LimitChange::applied,
        "monotone exact replay ceiling extension was rejected");
  check(strict.progress().limit_revision > revision_before_raise,
        "residual limit revision did not record exact proof extension");
  for (std::size_t step = 0; step < 5'000'000; ++step) {
    const auto advanced = strict.advance(quantum_for(Slicing::varied, step));
    if (advanced.progress.result == planner::ResidualResult::failed) {
      throw std::runtime_error("resumed exact proof failed after raising its replay ceiling");
    }
    if (advanced.progress.result == planner::ResidualResult::verified_optimum) {
      const auto optimum = strict.exact_original();
      check(optimum && optimum->height() == 3 && advanced.progress.exact_scope_original,
            "resumed original proof did not produce a height-three authority handle");
      return;
    }
    check(!strict.exact_original() && !strict.infeasibility(),
          "resumed exact continuation published authority before proof completion");
  }
  throw std::runtime_error("resumed exact proof exceeded the step guard");
}

planner::ResidualTraceRecord get_good_mutation_target(const Fixture& fixture) {
  return trace_only(fixture).record();
}

void rejected_mutations() {
  const auto seven = scoped_fixture(seven_scopes(), {0, 1, 6});
  const auto good = get_good_mutation_target(seven);
  const auto reject = [&](planner::ResidualTraceRecord changed, const std::string& context) {
    const auto report = planner::verify_residual_trace(seven.catalog, seven.query, changed);
    check(!report.valid && !report.resource_limit && report.rule != planner::ResidualTraceRule::none,
          "native trace verifier accepted copied mutation: " + context);
  };

  auto changed = good;
  changed.version += 1;
  reject(std::move(changed), "version");
  changed = good;
  changed.original_scopes.front().clear();
  reject(std::move(changed), "original scopes");
  changed = good;
  changed.layers.front().members.pop_back();
  reject(std::move(changed), "round membership");
  changed = good;
  changed.layers.front().variables.erase(changed.layers.front().variables.begin());
  reject(std::move(changed), "round variable union");
  changed = good;
  changed.layers.front().head.clear();
  reject(std::move(changed), "round free set");
  changed = good;
  changed.layers.front().unique.clear();
  reject(std::move(changed), "unique-variable set");
  changed = good;
  changed.layers.front().ears.front().occurrence = seven.query.atoms.size() + 13;
  reject(std::move(changed), "ear occurrence identity");
  changed = good;
  changed.layers.front().ears.front().anchors.front().occurrence =
      changed.layers.front().ears.front().occurrence;
  reject(std::move(changed), "self-anchor identity");
  changed = good;
  auto& condition = changed.layers.front().ears.front().anchors.front().condition;
  condition = condition == planner::EarCondition::first ? planner::EarCondition::second
                                                         : planner::EarCondition::first;
  reject(std::move(changed), "eligible-anchor condition bits");
  changed = good;
  changed.layers.front().deletions.front().anchor = changed.layers.front().deletions.front().occurrence;
  reject(std::move(changed), "deletion anchor");
  changed = good;
  const auto deleted = changed.layers.front().deletions.front().occurrence;
  changed.layers.front().deletions.erase(changed.layers.front().deletions.begin());
  changed.layers.front().remaining.push_back(deleted);
  std::sort(changed.layers.front().remaining.begin(), changed.layers.front().remaining.end());
  reject(std::move(changed), "deletion maximality and frozen schedule");
  changed = good;
  changed.layers.front().residual_head.clear();
  reject(std::move(changed), "induced residual head");
  changed = good;
  changed.terminal_members.front() = seven.query.atoms.size() + 5;
  reject(std::move(changed), "terminal member identity");
  changed = good;
  changed.terminal_view.occurrence_to_local.front() = std::size_t{999};
  reject(std::move(changed), "occurrence forward map");
  changed = good;
  changed.terminal_view.original_occurrences.front() = seven.query.atoms.size() + 7;
  reject(std::move(changed), "occurrence inverse map");
  changed = good;
  changed.terminal_view.variable_to_local.front() = VariableId{999};
  reject(std::move(changed), "variable forward map");
  changed = good;
  changed.terminal_view.original_variables.front() = VariableId{999};
  reject(std::move(changed), "variable inverse map");
  changed = good;
  changed.terminal_view.query.head.clear();
  reject(std::move(changed), "dense ordered head");

  const auto constants = fixture_for({{v(0), c(17), ignored()}}, {0, 0});
  changed = get_good_mutation_target(constants);
  bool changed_constant = false;
  for (auto& term : changed.terminal_view.query.atoms.front().terms) {
    if (auto* value = std::get_if<Value>(&term)) {
      *value = Value{std::int64_t{18}};
      changed_constant = true;
      break;
    }
  }
  check(changed_constant, "constant-preservation fixture did not retain its typed constant");
  const auto report = planner::verify_residual_trace(constants.catalog, constants.query, changed);
  check(!report.valid && !report.resource_limit && report.rule != planner::ResidualTraceRule::none,
        "native trace verifier accepted a changed terminal-query constant");

  auto no_work = planner::SearchLimits{};
  no_work.work_limit = 0;
  const auto stopped = planner::verify_residual_trace(seven.catalog, seven.query, good, no_work);
  check(!stopped.valid && stopped.resource_limit && stopped.rule == planner::ResidualTraceRule::resource_limit &&
        stopped.work == 0,
        "native trace verifier reported zero-work admission as a free successful replay");
}

void exact_inner_reason_and_fallback_handle() {
  const auto simple = scoped_fixture({{0}}, {0});
  auto options = options_for(planner::ResidualMode::require_exact_original);
  options.limits.exact.producer.work = 0;
  auto owner = planner::ResidualSearch::create(simple.catalog, simple.query, options);
  bool got_inner_stop = false;
  for (std::size_t i = 0; i < 10000; ++i) {
    const auto advanced = owner.advance({50'000, {}});
    if (advanced.progress.last_stop == planner::ResidualStopReason::exact_limit) {
      check(advanced.stopped_for == planner::ResidualStopReason::exact_limit &&
            advanced.exact_reason == planner::StopReason::total_work &&
            advanced.progress.exact_stop == planner::StopReason::total_work &&
            !owner.exact_original() && advanced.progress.result == planner::ResidualResult::unfinished,
            "outer residual-specific and inner exact stop reasons were not both retained");
      got_inner_stop = true;
      break;
    }
    check(advanced.progress.result == planner::ResidualResult::unfinished,
          "zero exact work unexpectedly produced a completed exact result");
  }
  check(got_inner_stop, "zero exact ceiling never surfaced its custom residual stop reason");
  auto raised = owner.options().limits;
  raised.exact.producer.work = 50'000;
  check(owner.raise_limits(raised) == planner::LimitChange::applied,
        "raising exact producer work after a resource stop was rejected");
  for (std::size_t i = 0; i < 10000; ++i) {
    const auto advanced = owner.advance({50'000, {}});
    if (advanced.progress.result == planner::ResidualResult::verified_optimum) {
      const auto optimum = owner.exact_original();
      check(optimum && optimum->height() == 1 && same_query(optimum->binding().query(), simple.query),
            "resumed exact original did not bind to the original singleton query");
      return;
    }
    check(advanced.progress.result == planner::ResidualResult::unfinished,
          "resumed exact producer returned an unexpected terminal status");
  }
  throw std::runtime_error("simple exact fallback did not finish after a monotone budget raise");
}

}  // namespace

int main() {
  try {
    small_p03_and_trace_family();
    named_semantic_cases();
    verify_counterexamples_and_authority();
    candidate_reconstruction_and_ownership();
    slicing_zero_quantum_and_limit_resume();
    residual_ceiling_extensions_resume();
    rejected_mutations();
    exact_inner_reason_and_fallback_handle();
    std::cout << "P05 residual frozen traces, candidates, and exact authority verified\n";
  } catch (const std::exception& error) {
    std::cerr << "P05 residual test failed: " << error.what() << '\n';
    return 1;
  }
}

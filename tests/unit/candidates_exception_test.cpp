#include "crown/planner/candidates.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/verify.hpp"
#include "candidate_key.hpp"
#include "candidate_machine.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// This executable replaces the global allocation family so a failure remains
// armed while the same owner retries and unwinds.
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
namespace ap = crown::planner::candidate_detail;
namespace cd = crown::planner::continuation_detail;

static_assert(std::is_nothrow_destructible_v<MinimumHeightCandidate>);
static_assert(std::is_nothrow_destructible_v<CandidateSnapshot>);

void check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

constexpr WorkQuantum all_work{std::numeric_limits<std::uint64_t>::max(), {}};

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

VerifiedOptimum prove(const Fixture& fixture) {
  auto owner = ExactSearch::create(fixture.catalog, fixture.query);
  const auto result = owner.advance(all_work);
  check(result.progress.result == ResultKind::verified_optimum && owner.optimum().has_value(),
        "P06 did not produce an original-query verified optimum");
  return *owner.optimum();
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
    if (left.head[i].variable != right.head[i].variable || left.head[i].alias != right.head[i].alias)
      return false;
  return true;
}

bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
  if (left.root != right.root || left.claimed_connex != right.claimed_connex ||
      left.claimed_native_height != right.claimed_native_height || left.nodes.size() != right.nodes.size())
    return false;
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

bool same_residual_view(const ResidualView& a, const ResidualView& b) {
  return a.original_occurrences == b.original_occurrences &&
      a.original_variables == b.original_variables &&
      a.occurrence_to_local == b.occurrence_to_local &&
      a.variable_to_local == b.variable_to_local && same_query(a.query, b.query);
}

bool same_residual_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) {
  if (a.version != b.version || a.original_scopes != b.original_scopes ||
      a.layers.size() != b.layers.size() || a.terminal_members != b.terminal_members ||
      a.terminal_head != b.terminal_head || a.terminal != b.terminal ||
      !same_residual_view(a.terminal_view, b.terminal_view)) return false;
  for (std::size_t i = 0; i < a.layers.size(); ++i)
    if (!same_layer(a.layers[i], b.layers[i])) return false;
  return true;
}

bool same_residual_trace(const ResidualTrace& a, const ResidualTrace& b) {
  return a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) &&
      same_query(a.query(), b.query()) && same_residual_record(a.record(), b.record());
}

bool same_context(const CandidateContext& a, const CandidateContext& b) {
  return a.updates == b.updates && a.arithmetic == b.arithmetic && a.planner == b.planner &&
      a.optimization == b.optimization && a.cost_model == b.cost_model &&
      a.canonicalization == b.canonicalization;
}

bool same_provenance(const CandidateProvenance& a, const CandidateProvenance& b) {
  if (a.source != b.source || a.family != b.family || a.sequence != b.sequence ||
      a.residual_last_step != b.residual_last_step ||
      a.residual_trace.has_value() != b.residual_trace.has_value()) return false;
  return !a.residual_trace || same_residual_trace(*a.residual_trace, *b.residual_trace);
}

bool same_candidate(const MinimumHeightCandidate& a, const MinimumHeightCandidate& b) {
  if (!a.valid() || !b.valid() || !same_catalog(a.catalog(), b.catalog()) ||
      !same_query(a.query(), b.query()) || !same_tree(a.tree(), b.tree()) ||
      a.height() != b.height() || a.structural_key() != b.structural_key() ||
      !same_context(a.context(), b.context()) || !same_provenance(a.provenance(), b.provenance()))
    return false;
  const auto a_proof = a.original_proof();
  const auto b_proof = b.original_proof();
  return a_proof.valid() && b_proof.valid() &&
      same_certificate(a_proof.certificate(), b_proof.certificate());
}

struct ProofValue {
  Catalog catalog;
  Query query;
  HeightCertificate certificate;
  FreeConnexTree upper;
  std::size_t height = 0;
};

ProofValue proof_value(const VerifiedOptimum& proof) {
  const auto binding = proof.binding();
  return {binding.catalog(), binding.query(), proof.certificate(), proof.upper().tree(), proof.height()};
}

bool same_proof_value(const VerifiedOptimum& proof, const ProofValue& value) {
  if (!proof.valid() || proof.height() != value.height ||
      !same_certificate(proof.certificate(), value.certificate) ||
      !same_tree(proof.upper().tree(), value.upper)) return false;
  const auto binding = proof.binding();
  return same_catalog(binding.catalog(), value.catalog) && same_query(binding.query(), value.query);
}

struct ResidualValue {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  std::size_t height = 0;
  ResidualOrigin origin = ResidualOrigin::hierarchy_seed;
  ResidualTraceRecord trace;
  Catalog trace_catalog;
  Query trace_query;
};

ResidualValue residual_value(const ResidualCandidate& candidate) {
  const auto trace = candidate.trace();
  return {candidate.catalog(), candidate.query(), candidate.tree(), candidate.height(), candidate.origin(),
          trace.record(), trace.catalog(), trace.query()};
}

bool same_residual_value(const ResidualCandidate& candidate, const ResidualValue& value) {
  if (!candidate.valid() || candidate.height() != value.height || candidate.origin() != value.origin ||
      !same_catalog(candidate.catalog(), value.catalog) || !same_query(candidate.query(), value.query) ||
      !same_tree(candidate.tree(), value.tree)) return false;
  const auto trace = candidate.trace();
  return same_catalog(trace.catalog(), value.trace_catalog) &&
      same_query(trace.query(), value.trace_query) && same_residual_record(trace.record(), value.trace);
}

struct ProvenanceValue {
  CandidateSource source = CandidateSource::exact_witness;
  CandidateFamily family = CandidateFamily::exact_seed_residual_seed_normal_form_v1;
  std::uint64_t sequence = 0;
  std::optional<ResidualOrigin> residual_last_step;
  bool has_trace = false;
  Catalog trace_catalog;
  Query trace_query;
  ResidualTraceRecord trace;
};

ProvenanceValue provenance_value(const CandidateProvenance& provenance) {
  ProvenanceValue value{provenance.source, provenance.family, provenance.sequence,
                        provenance.residual_last_step, provenance.residual_trace.has_value(), {}, {}, {}};
  if (provenance.residual_trace) {
    value.trace_catalog = provenance.residual_trace->catalog();
    value.trace_query = provenance.residual_trace->query();
    value.trace = provenance.residual_trace->record();
  }
  return value;
}

bool same_provenance_value(const CandidateProvenance& provenance, const ProvenanceValue& value) {
  if (provenance.source != value.source || provenance.family != value.family ||
      provenance.sequence != value.sequence || provenance.residual_last_step != value.residual_last_step ||
      provenance.residual_trace.has_value() != value.has_trace) return false;
  if (!provenance.residual_trace) return true;
  return same_catalog(provenance.residual_trace->catalog(), value.trace_catalog) &&
      same_query(provenance.residual_trace->query(), value.trace_query) &&
      same_residual_record(provenance.residual_trace->record(), value.trace);
}

struct CandidateValue {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  std::size_t height = 0;
  std::string key;
  CandidateContext context;
  ProvenanceValue provenance;
  ProofValue proof;
};

CandidateValue candidate_value(const MinimumHeightCandidate& candidate) {
  const auto proof = candidate.original_proof();
  return {candidate.catalog(), candidate.query(), candidate.tree(), candidate.height(),
          candidate.structural_key(), candidate.context(), provenance_value(candidate.provenance()),
          proof_value(proof)};
}

bool same_candidate_value(const MinimumHeightCandidate& candidate, const CandidateValue& value) {
  if (!candidate.valid() || candidate.height() != value.height ||
      candidate.structural_key() != value.key || !same_catalog(candidate.catalog(), value.catalog) ||
      !same_query(candidate.query(), value.query) || !same_tree(candidate.tree(), value.tree) ||
      !same_context(candidate.context(), value.context) ||
      !same_provenance_value(candidate.provenance(), value.provenance)) return false;
  return same_proof_value(candidate.original_proof(), value.proof);
}

struct SnapshotValue {
  bool exhausted = false;
  CandidateFamily family = CandidateFamily::exact_seed_residual_seed_normal_form_v1;
  CandidateContext context;
  ProofValue proof;
  std::vector<CandidateValue> candidates;
};

SnapshotValue snapshot_value(const CandidateSnapshot& snapshot) {
  SnapshotValue value;
  value.exhausted = snapshot.family_exhausted();
  value.family = snapshot.family();
  value.context = snapshot.context();
  value.proof = proof_value(snapshot.original_proof());
  value.candidates.reserve(snapshot.candidate_count());
  for (std::size_t i = 0; i < snapshot.candidate_count(); ++i) {
    const auto candidate = snapshot.candidate(i);
    check(candidate.has_value(), "snapshot value capture lost an indexed candidate");
    value.candidates.push_back(candidate_value(*candidate));
  }
  return value;
}

bool same_snapshot_value(const CandidateSnapshot& snapshot, const SnapshotValue& value) {
  if (!snapshot.valid() || snapshot.candidate_count() != value.candidates.size() ||
      snapshot.family_exhausted() != value.exhausted || snapshot.family() != value.family ||
      !same_context(snapshot.context(), value.context) ||
      !same_proof_value(snapshot.original_proof(), value.proof)) return false;
  for (std::size_t i = 0; i < value.candidates.size(); ++i) {
    const auto candidate = snapshot.candidate(i);
    if (!candidate || !same_candidate_value(*candidate, value.candidates[i])) return false;
  }
  return true;
}

bool same_provider_prefix_value(const CandidateProvider& owner, const SnapshotValue& value) {
  if (owner.candidate_count() > value.candidates.size()) return false;
  for (std::size_t i = 0; i < owner.candidate_count(); ++i) {
    const auto candidate = owner.candidate(i);
    if (!candidate || !same_candidate_value(*candidate, value.candidates[i])) return false;
  }
  return true;
}

bool same_stats(const CandidateStatistics& a, const CandidateStatistics& b) {
  return a.proposed == b.proposed && a.rejected == b.rejected && a.taller == b.taller &&
      a.duplicates == b.duplicates && a.published == b.published &&
      a.topologies == b.topologies && a.scope_tuples == b.scope_tuples &&
      a.cache_seeded == b.cache_seeded;
}

bool same_work_except_faults(const WorkCounters& a, const WorkCounters& b) {
  return a.committed_transitions == b.committed_transitions &&
      a.current_depth == b.current_depth && a.peak_depth == b.peak_depth;
}

bool same_progress_except_faults(const CandidateProgress& a, const CandidateProgress& b) {
  return a.phase == b.phase && a.last_stop == b.last_stop && a.family == b.family &&
      a.verified_original_height == b.verified_original_height &&
      a.family_exhausted == b.family_exhausted && same_work_except_faults(a.work, b.work) &&
      same_stats(a.statistics, b.statistics) && a.records == b.records && a.cells == b.cells &&
      a.limit_revision == b.limit_revision && a.candidate_count == b.candidate_count;
}

bool same_pending_progress(const CandidateProgress& a, const CandidateProgress& b) {
  return a.phase == b.phase && a.family == b.family &&
      a.verified_original_height == b.verified_original_height &&
      a.family_exhausted == b.family_exhausted && same_work_except_faults(a.work, b.work) &&
      same_stats(a.statistics, b.statistics) && a.records == b.records && a.cells == b.cells &&
      a.limit_revision == b.limit_revision && a.candidate_count == b.candidate_count;
}

bool same_published(const CandidateProvider& owner, const CandidateSnapshot& expected) {
  if (owner.candidate_count() != expected.candidate_count()) return false;
  for (std::size_t i = 0; i < owner.candidate_count(); ++i) {
    const auto actual = owner.candidate(i);
    const auto prior = expected.candidate(i);
    if (!actual || !prior || !same_candidate(*actual, *prior)) return false;
  }
  return true;
}

bool same_published_prefix(const CandidateProvider& owner, const CandidateSnapshot& expected) {
  if (owner.candidate_count() > expected.candidate_count()) return false;
  for (std::size_t i = 0; i < owner.candidate_count(); ++i) {
    const auto actual = owner.candidate(i);
    const auto prior = expected.candidate(i);
    if (!actual || !prior || !same_candidate(*actual, *prior)) return false;
  }
  return true;
}

struct GeneratorState {
  ap::GeneratorStatistics stats;
  std::uint64_t records = 0;
  std::uint64_t cells = 0;
  std::size_t depth = 0;
  std::shared_ptr<const FreeConnexTree> pending;
  bool cancelled = false;
};

bool same_generator_stats(const ap::GeneratorStatistics& a, const ap::GeneratorStatistics& b) {
  return a.completed_steps == b.completed_steps && a.topologies_examined == b.topologies_examined &&
      a.topology_survivors == b.topology_survivors && a.drafts_ready == b.drafts_ready &&
      a.drafts_consumed == b.drafts_consumed && a.peak_depth == b.peak_depth;
}

GeneratorState generator_state(const ap::NormalFormGenerator& generator,
                                const std::shared_ptr<ap::ContentBudget>& budget) {
  return {generator.statistics(), budget->records(), budget->cells(), generator.current_depth(),
          generator.draft(), generator.cancelled()};
}

bool same_generator_state(const GeneratorState& a, const GeneratorState& b) {
  return same_generator_stats(a.stats, b.stats) && a.records == b.records && a.cells == b.cells &&
      a.depth == b.depth && a.pending == b.pending && a.cancelled == b.cancelled;
}

struct GeneratorRun {
  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  ap::GeneratorStatistics stats;
  std::uint64_t records = 0;
  std::uint64_t cells = 0;
  std::size_t allocations = 0;
};

void append_ready_draft(ap::NormalFormGenerator& generator,
                        const std::shared_ptr<ap::ContentBudget>& budget,
                        std::vector<std::shared_ptr<const FreeConnexTree>>& drafts) {
  const auto retained = generator.draft();
  check(static_cast<bool>(retained), "generator ready event did not expose a retained draft");
  check(drafts.size() < drafts.capacity(), "generator test output reserve was too small");
  drafts.push_back(retained);
  const auto before = generator_state(generator, budget);
  for (int i = 0; i < 2; ++i) {
    const auto repeated = generator.step({});
    check(repeated.event == ap::GeneratorEvent::draft_ready && generator.draft() == retained &&
              same_generator_state(before, generator_state(generator, budget)),
          "repeated ready observation changed the pending draft or accounting");
  }
  generator.consume_draft();
}

bool generator_result(ap::NormalFormGenerator& generator,
                      const std::shared_ptr<ap::ContentBudget>& budget,
                      std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
                      ap::Step result) {
  if (result.event == ap::GeneratorEvent::draft_ready) {
    append_ready_draft(generator, budget, drafts);
    return false;
  }
  if (result.event == ap::GeneratorEvent::exhausted) return true;
  check(result.event == ap::GeneratorEvent::advanced,
        "unbounded generator stopped before exhaustion");
  return false;
}

bool drain_generator(ap::NormalFormGenerator& generator,
                     const std::shared_ptr<ap::ContentBudget>& budget,
                     std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
                     std::size_t& calls) {
  constexpr std::size_t limit = 1'000'000;
  while (calls < limit) {
    ++calls;
    if (generator_result(generator, budget, drafts, generator.step({}))) return true;
  }
  return false;
}

bool same_generator_run(const ap::NormalFormGenerator& generator,
                        const std::shared_ptr<ap::ContentBudget>& budget,
                        const std::vector<std::shared_ptr<const FreeConnexTree>>& drafts,
                        const GeneratorRun& expected) {
  if (drafts.size() != expected.drafts.size() ||
      !same_generator_stats(generator.statistics(), expected.stats) ||
      budget->records() != expected.records || budget->cells() != expected.cells) return false;
  for (std::size_t i = 0; i < drafts.size(); ++i)
    if (!drafts[i] || !expected.drafts[i] || !same_tree(*drafts[i], *expected.drafts[i])) return false;
  return true;
}

GeneratorRun baseline_generator(const std::shared_ptr<const cd::BindingData>& binding) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  GeneratorRun result;
  result.drafts.reserve(256);
  allocation_count = 0;
  std::size_t calls = 0;
  check(drain_generator(generator, budget, result.drafts, calls),
        "uninterrupted generator exceeded its finite transition bound");
  result.allocations = allocation_count;
  result.stats = generator.statistics();
  result.records = budget->records();
  result.cells = budget->cells();
  check(!result.drafts.empty() && result.allocations != 0,
        "generator baseline did not enumerate allocated drafts");
  check(result.stats.drafts_ready == result.drafts.size() &&
            result.stats.drafts_consumed == result.drafts.size(),
        "generator accounting did not match the complete draft order");
  return result;
}

void generator_faults(const std::shared_ptr<const cd::BindingData>& binding,
                       const GeneratorRun& expected) {
  check(expected.allocations <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "generator allocation sweep exceeds fault-index range");
  for (std::size_t point = 0; point < expected.allocations; ++point) {
    auto budget = std::make_shared<ap::ContentBudget>();
    ap::NormalFormGenerator generator(binding, 2, budget);
    std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
    drafts.reserve(256);
    allocation_count = 0;
    std::size_t calls = 0;
    bool failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      constexpr std::size_t limit = 1'000'000;
      while (calls < limit) {
        ++calls;
        ap::Step result;
        try { result = generator.step({}); }
        catch (const std::bad_alloc&) { failed = true; break; }
        if (generator_result(generator, budget, drafts, result)) break;
      }
      if (failed) {
        check(allocation_count == point + 1,
              "generator allocation fault missed the requested observed position");
        const auto pending = generator_state(generator, budget);
        check(!pending.pending, "generator allocation fault occurred during draft acknowledgement");
        for (int retry = 0; retry != 2; ++retry) {
          bool repeated = false;
          try { static_cast<void>(generator.step({})); }
          catch (const std::bad_alloc&) { repeated = true; }
          check(repeated && same_generator_state(pending, generator_state(generator, budget)),
                "generator persistent retry changed its pending operation");
        }
      }
    }
    check(failed, "generator allocation fault point was not reached");
    check(drain_generator(generator, budget, drafts, calls),
          "same generator owner did not finish after allocation recovery");
    check(same_generator_run(generator, budget, drafts, expected),
          "same-owner generator recovery differed from full ordered drafts or content accounting");
  }
}

void generator_caps_and_cancel(const std::shared_ptr<const cd::BindingData>& binding,
                               const GeneratorRun& expected) {
  for (int cap = 0; cap != 3; ++cap) {
    ap::ContentLimits initial;
    if (cap == 0) initial.records = 0;
    if (cap == 1) initial.cells = 0;
    if (cap == 2) initial.records = 1;
    auto budget = std::make_shared<ap::ContentBudget>(initial);
    ap::NormalFormGenerator generator(binding, 2, budget);
    std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
    drafts.reserve(256);
    bool stopped = false;
    std::size_t calls = 0;
    while (calls++ < 100'000) {
      const auto before = generator_state(generator, budget);
      const auto result = generator.step({});
      if (result.event == ap::GeneratorEvent::stopped) {
        const auto again = generator.step({});
        check(again.event == ap::GeneratorEvent::stopped &&
                  same_generator_state(before, generator_state(generator, budget)),
              "repeated generator content stop changed its pending stage");
        stopped = true;
        break;
      }
      if (generator_result(generator, budget, drafts, result)) break;
    }
    check(stopped, "generator content ceiling did not stop at a pending stage");
    check(budget->raise_limits({}), "generator content ceiling could not be lifted");
    check(drain_generator(generator, budget, drafts, calls),
          "generator failed to resume after a content grant");
    check(same_generator_run(generator, budget, drafts, expected),
          "generator content resume changed ordered drafts or accounting");
  }

  auto budget = std::make_shared<ap::ContentBudget>();
  ap::NormalFormGenerator generator(binding, 2, budget);
  auto result = generator.step({0});
  const auto blocked_state = generator_state(generator, budget);
  check(result.event == ap::GeneratorEvent::stopped &&
            result.reason == ap::GeneratorStop::depth_limit && result.requested_depth == 1 &&
            budget->records() == 0 && budget->cells() == 0 &&
            generator.step({0}).event == ap::GeneratorEvent::stopped &&
            same_generator_state(blocked_state, generator_state(generator, budget)),
        "zero depth grant allocated a generator frame");

  std::vector<std::shared_ptr<const FreeConnexTree>> drafts;
  drafts.reserve(256);
  std::size_t calls = 0;
  bool ready = false;
  while (calls++ < 100'000) {
    result = generator.step({});
    if (result.event == ap::GeneratorEvent::draft_ready) { ready = true; break; }
    check(result.event == ap::GeneratorEvent::advanced,
          "unbounded generator stopped before first retained draft");
  }
  check(ready, "generator did not produce a retained draft for cancellation");
  const auto retained = generator.draft();
  const FreeConnexTree frozen = *retained;
  allocation_count = 0;
  {
    FaultScope fault(0);
    generator.cancel();
  }
  check(allocation_count == 0 && generator.cancelled() && retained && same_tree(*retained, frozen),
        "generator cancellation allocated or changed a caller-retained draft");
}

void finish_key(ap::StructuralKeyMachine& machine) {
  for (std::size_t i = 0; i < 1'000'000; ++i) {
    const auto result = machine.step({256});
    check(result.event != ap::KeyEvent::stopped,
          "unbounded structural-key machine stopped before publication");
    if (result.event == ap::KeyEvent::key_ready) return;
  }
  check(false, "structural-key machine exceeded its finite transition bound");
}

bool same_key_stats(const ap::KeyStatistics& a, const ap::KeyStatistics& b) {
  return a.completed_steps == b.completed_steps && a.completed_nodes == b.completed_nodes &&
      a.compared_characters == b.compared_characters && a.peak_depth == b.peak_depth;
}

struct KeyRun {
  std::shared_ptr<const std::string> key;
  ap::KeyStatistics stats;
  std::uint64_t records = 0;
  std::uint64_t cells = 0;
  std::size_t allocations = 0;
};

KeyRun baseline_key(const std::shared_ptr<const FreeConnexTree>& tree) {
  auto budget = std::make_shared<ap::ContentBudget>();
  ap::StructuralKeyMachine machine(tree, budget);
  allocation_count = 0;
  finish_key(machine);
  KeyRun result{machine.key(), machine.statistics(), budget->records(), budget->cells(), allocation_count};
  check(result.key && result.allocations != 0,
        "structural-key baseline did not allocate its published token");
  return result;
}

void key_faults(const std::shared_ptr<const FreeConnexTree>& tree, const KeyRun& expected) {
  check(expected.allocations <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "key allocation sweep exceeds fault-index range");
  for (std::size_t point = 0; point < expected.allocations; ++point) {
    auto budget = std::make_shared<ap::ContentBudget>();
    ap::StructuralKeyMachine machine(tree, budget);
    allocation_count = 0;
    bool failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      try { finish_key(machine); }
      catch (const std::bad_alloc&) { failed = true; }
      check(failed && allocation_count == point + 1,
            "structural-key fault missed the requested observed position");
      const auto stats = machine.statistics();
      const auto records = budget->records();
      const auto cells = budget->cells();
      const auto depth = machine.current_depth();
      check(!machine.key(), "failed structural-key worker published a partial token");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated = false;
        try { static_cast<void>(machine.step({256})); }
        catch (const std::bad_alloc&) { repeated = true; }
        check(repeated && same_key_stats(stats, machine.statistics()) &&
                  budget->records() == records && budget->cells() == cells &&
                  machine.current_depth() == depth && !machine.key(),
              "structural-key persistent retry changed its pending operation");
      }
    }
    finish_key(machine);
    check(machine.key() && *machine.key() == *expected.key &&
              same_key_stats(machine.statistics(), expected.stats) &&
              budget->records() == expected.records && budget->cells() == expected.cells,
          "same-owner structural-key recovery changed token or content accounting");
  }
}

void key_caps_and_cancel(const std::shared_ptr<const FreeConnexTree>& tree, const KeyRun& expected) {
  auto budget = std::make_shared<ap::ContentBudget>(ap::ContentLimits{{}, 0});
  ap::StructuralKeyMachine machine(tree, budget);
  const auto zero = machine.step({0});
  check(zero.event == ap::KeyEvent::stopped && zero.reason == ap::KeyStop::depth_limit &&
            machine.current_depth() == 0 && budget->records() == 0,
        "zero key depth grant allocated a frame");
  bool cell_stop = false;
  for (int i = 0; i < 1000; ++i) {
    const auto state_stats = machine.statistics();
    const auto records = budget->records(), cells = budget->cells();
    const auto step = machine.step({256});
    if (step.reason == ap::KeyStop::cell_limit) {
      const auto again = machine.step({256});
      check(again.reason == ap::KeyStop::cell_limit &&
                same_key_stats(state_stats, machine.statistics()) &&
                budget->records() == records && budget->cells() == cells,
            "repeated key cell stop changed pending serialization state");
      cell_stop = true;
      break;
    }
    check(step.event == ap::KeyEvent::advanced,
          "zero-cell key budget stopped for an unexpected reason");
  }
  check(cell_stop && !machine.key(), "zero-cell key budget did not block key publication");
  check(budget->raise_limits({{}, 100'000}), "key cell budget could not be lifted");
  finish_key(machine);
  check(machine.key() && *machine.key() == *expected.key &&
            same_key_stats(machine.statistics(), expected.stats),
        "key content resume changed token or traversal statistics");
  const auto retained = machine.key();
  allocation_count = 0;
  {
    FaultScope fault(0);
    machine.cancel();
  }
  check(allocation_count == 0 && retained && *retained == *expected.key,
        "key cancellation allocated or changed a retained token");
}

CandidateStop drain(CandidateProvider& owner, std::uint64_t quantum =
                    std::numeric_limits<std::uint64_t>::max()) {
  constexpr std::size_t limit = 2'000'000;
  for (std::size_t i = 0; i < limit; ++i) {
    const auto result = owner.advance({quantum, {}});
    if (result.stopped_for != CandidateStop::quantum_work &&
        result.stopped_for != CandidateStop::candidate_ready) return result.stopped_for;
  }
  throw std::runtime_error("candidate provider exceeded its finite drain bound");
}

struct CandidateRun {
  CandidateProgress progress;
  std::size_t allocations = 0;
};

CandidateRun baseline_provider(CandidateProvider& owner) {
  allocation_count = 0;
  const auto stop = drain(owner);
  const auto allocations = allocation_count;
  check(stop == CandidateStop::exhausted,
        "uninterrupted candidate provider did not exhaust its finite family");
  check(owner.progress().family_exhausted && owner.progress().candidate_count != 0,
        "uninterrupted provider omitted candidates or completion");
  return {owner.progress(), allocations};
}

void compare_provider(const CandidateProvider& actual, const CandidateRun& expected,
                      const CandidateSnapshot& expected_snapshot) {
  const auto progress = actual.progress();
  check(same_progress_except_faults(progress, expected.progress),
        "candidate owner recovery changed progress, statistics, content or committed transitions");
  check(same_published(actual, expected_snapshot),
        "candidate owner recovery changed ordered candidate tree/key/provenance");
}

void provider_faults(const VerifiedOptimum& proof, const CandidateRun& expected,
                     const CandidateSnapshot& expected_snapshot) {
  const auto expected_value = snapshot_value(expected_snapshot);
  check(expected.allocations <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "provider allocation sweep exceeds fault-index range");
  for (std::size_t point = 0; point < expected.allocations; ++point) {
    auto owner = CandidateProvider::create(proof);
    allocation_count = 0;
    bool failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      failed = drain(owner) == CandidateStop::allocation_failure;
      check(failed && allocation_count == point + 1,
            "provider allocation fault missed the requested observed position");
      const auto pending = owner.progress();
      check(pending.phase != CandidatePhase::failed && !pending.family_exhausted,
            "allocation failure incorrectly became a terminal provider failure");
      check(same_published_prefix(owner, expected_snapshot),
            "provider failure exposed an out-of-order or extra candidate");
      for (int retry = 0; retry != 2; ++retry) {
        const auto result = owner.advance(all_work);
        check(result.stopped_for == CandidateStop::allocation_failure &&
                  same_pending_progress(pending, result.progress) &&
                  result.progress.work.allocation_failures == pending.work.allocation_failures +
                      static_cast<std::uint64_t>(retry + 1),
              "provider persistent retry changed the saved stage or committed state");
      }
      check(same_published_prefix(owner, expected_snapshot),
            "persistent provider failure changed a previously retained candidate");
    }
    check(same_provider_prefix_value(owner, expected_value) &&
              same_snapshot_value(expected_snapshot, expected_value) &&
              same_proof_value(proof, expected_value.proof),
          "provider failure changed a deep-copied retained candidate value");
    check(drain(owner) == CandidateStop::exhausted,
          "same provider owner did not recover after persistent allocation failure");
    compare_provider(owner, expected, expected_snapshot);
    check(same_provider_prefix_value(owner, expected_value) &&
              same_snapshot_value(expected_snapshot, expected_value),
          "same-owner provider recovery changed an immutable value baseline");
  }
}

void factory_admission_faults(const VerifiedOptimum& proof,
                              const CandidateSnapshot& retained_snapshot) {
  const auto retained_proof = proof_value(proof);
  const auto retained_snapshot_copy = snapshot_value(retained_snapshot);
  allocation_count = 0;
  {
    auto sample = CandidateProvider::create(proof);
    check(sample.progress().phase == CandidatePhase::exact_seed &&
              sample.original_proof().valid(), "candidate factory baseline admission was malformed");
  }
  const auto positions = allocation_count;
  check(positions != 0 && positions <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "candidate factory admission had no measurable allocation positions");
  for (std::size_t point = 0; point < positions; ++point) {
    allocation_count = 0;
    bool first_failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      try { auto ignored = CandidateProvider::create(proof); static_cast<void>(ignored); }
      catch (const std::bad_alloc&) { first_failed = true; }
      check(first_failed && allocation_count == point + 1,
            "candidate factory fault missed the requested admission allocation");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated = false;
        try { auto ignored = CandidateProvider::create(proof); static_cast<void>(ignored); }
        catch (const std::bad_alloc&) { repeated = true; }
        check(repeated, "candidate factory admission did not remain faulted on retry");
      }
    }
    check(same_proof_value(proof, retained_proof) &&
              same_snapshot_value(retained_snapshot, retained_snapshot_copy),
          "failed candidate factory admission changed a retained original proof");
    check(retained_snapshot.valid() && retained_snapshot.candidate_count() != 0,
          "failed candidate factory admission changed a retained snapshot");
    auto recovered = CandidateProvider::create(proof);
    check(recovered.progress().phase == CandidatePhase::exact_seed && recovered.original_proof().valid(),
          "candidate factory did not recover after admission allocation failure");
  }
}

void snapshot_admission_faults(CandidateProvider& owner, const CandidateSnapshot& expected) {
  const auto expected_value = snapshot_value(expected);
  allocation_count = 0;
  std::size_t positions = 0;
  {
    auto sample = owner.snapshot();
    positions = allocation_count;
    check(same_snapshot_value(sample, expected_value),
          "snapshot allocation baseline changed its frozen prefix");
  }
  check(positions != 0 && positions <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "snapshot admission had no measurable allocation positions");
  const auto before_progress = owner.progress();
  for (std::size_t point = 0; point < positions; ++point) {
    allocation_count = 0;
    bool first_failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      try { static_cast<void>(owner.snapshot()); }
      catch (const std::bad_alloc&) { first_failed = true; }
      check(first_failed && allocation_count == point + 1,
            "snapshot fault missed the requested admission allocation");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated = false;
        try { static_cast<void>(owner.snapshot()); }
        catch (const std::bad_alloc&) { repeated = true; }
        check(repeated, "snapshot admission did not remain faulted on retry");
      }
    }
    check(same_progress_except_faults(owner.progress(), before_progress) &&
              same_provider_prefix_value(owner, expected_value) &&
              same_snapshot_value(expected, expected_value),
          "failed snapshot admission changed provider counters or published candidates");
    auto recovered = owner.snapshot();
    check(same_snapshot_value(recovered, expected_value),
          "snapshot admission did not recover to the exact frozen prefix");
  }
}

void provider_caps_and_cancel(const VerifiedOptimum& proof, const CandidateRun& baseline,
                              const CandidateSnapshot& expected_snapshot) {
  const auto uncapped = [] {
    CandidateLimits limits;
    limits.enumeration.work.reset();
    limits.enumeration.active_time.reset();
    limits.logical_depth.reset();
    limits.records.reset();
    limits.cells.reset();
    limits.retained_candidates.reset();
    return limits;
  };

  for (int cap = 0; cap != 3; ++cap) {
    CandidateLimits limits;
    if (cap == 0) limits.logical_depth = 0;
    if (cap == 1) limits.records = 0;
    if (cap == 2) limits.cells = 0;
    auto owner = CandidateProvider::create(proof, {}, limits);
    const auto stop = drain(owner);
    const auto expected_stop = cap == 0 ? CandidateStop::depth_limit :
        cap == 1 ? CandidateStop::record_limit : CandidateStop::cell_limit;
    check(stop == expected_stop && !owner.progress().family_exhausted,
          "candidate resource ceiling stopped at the wrong saved stage");
    const auto pending = owner.progress();
    check(drain(owner) == expected_stop && same_pending_progress(pending, owner.progress()),
          "repeated candidate resource stop changed its pending operation");
    check(owner.raise_limits(uncapped()) == LimitChange::applied,
          "candidate resource ceiling could not be raised");
    check(drain(owner) == CandidateStop::exhausted,
          "candidate provider did not resume after a resource raise");
    auto expected_after_raise = baseline;
    ++expected_after_raise.progress.limit_revision;
    compare_provider(owner, expected_after_raise, expected_snapshot);
  }

  CandidateLimits one;
  one.retained_candidates = 1;
  auto capped = CandidateProvider::create(proof, {}, one);
  check(capped.advance(all_work).stopped_for == CandidateStop::candidate_ready &&
            capped.candidate_count() == 1,
        "candidate-cap setup failed to retain its first publication");
  const auto retained = *capped.candidate(0);
  const auto pending = capped.advance(all_work);
  check(pending.stopped_for == CandidateStop::candidate_capacity &&
            pending.progress.phase == CandidatePhase::publish && pending.progress.candidate_count == 1,
        "candidate cap did not stop at a pending publication");
  const auto stopped = pending.progress;
  check(capped.advance(all_work).stopped_for == CandidateStop::candidate_capacity &&
            same_pending_progress(stopped, capped.progress()) && retained.valid(),
        "repeated candidate-cap stop changed its pending publication or retained handle");
  auto raised = uncapped();
  raised.retained_candidates = 8;
  check(capped.raise_limits(raised) == LimitChange::applied && drain(capped) == CandidateStop::exhausted,
        "candidate provider did not resume its pending publication after a cap raise");
  auto expected_after_cap_raise = baseline;
  ++expected_after_cap_raise.progress.limit_revision;
  compare_provider(capped, expected_after_cap_raise, expected_snapshot);

  auto cancelled = CandidateProvider::create(proof);
  check(cancelled.advance(all_work).stopped_for == CandidateStop::candidate_ready,
        "cancellation setup did not publish a candidate");
  const auto retained_candidate = *cancelled.candidate(0);
  const auto retained_snapshot = cancelled.snapshot();
  const auto retained_proof = cancelled.original_proof();
  const auto retained_proof_value = proof_value(retained_proof);
  const auto retained_candidate_value = candidate_value(retained_candidate);
  const auto retained_snapshot_value = snapshot_value(retained_snapshot);
  allocation_count = 0;
  {
    FaultScope fault(0);
    cancelled.cancel();
  }
  check(allocation_count == 0 && cancelled.advance(all_work).stopped_for == CandidateStop::cancelled &&
            cancelled.original_proof().valid() && cancelled.candidate_count() == 1 &&
            same_candidate_value(retained_candidate, retained_candidate_value) &&
            same_snapshot_value(retained_snapshot, retained_snapshot_value) &&
            same_proof_value(retained_proof, retained_proof_value) &&
            same_proof_value(cancelled.original_proof(), retained_proof_value) &&
            same_candidate_value(*cancelled.candidate(0), retained_candidate_value),
        "provider cancellation allocated or invalidated retained proof/candidate/snapshot handles");
}

void optional_seed_path_faults(const VerifiedOptimum& proof, const ResidualCandidate& residual,
                               const CandidateSnapshot& prefix) {
  const auto retained_proof = proof_value(proof);
  const auto retained_residual = residual_value(residual);
  const auto retained_prefix = snapshot_value(prefix);
  CandidateLimits limits;
  auto owner = CandidateProvider::create(proof, {}, limits, residual, prefix);
  allocation_count = 0;
  const auto stop = drain(owner);
  const auto positions = allocation_count;
  check(stop == CandidateStop::exhausted && owner.progress().family_exhausted &&
            owner.progress().candidate_count == 2 &&
            owner.progress().statistics.cache_seeded == prefix.candidate_count(),
        "residual/cache seed path did not exhaust its small exact family");
  auto frozen = owner.snapshot();
  const CandidateRun expected{owner.progress(), positions};
  bool residual_published = false;
  for (std::size_t i = 0; i < frozen.candidate_count(); ++i) {
    const auto candidate = frozen.candidate(i);
    check(candidate && candidate->valid(), "seeded owner published an invalid handle");
    if (candidate->provenance().source == CandidateSource::residual_seed) {
      residual_published = true;
      const auto exact = frozen.candidate(0);
      check(exact && candidate->structural_key() != exact->structural_key(),
            "residual source did not publish a distinct structural candidate");
    }
  }
  check(residual_published && positions != 0,
        "residual/cache path omitted a distinct published residual-source candidate");
  const auto expected_prefix = frozen;
  const auto expected_value = snapshot_value(frozen);
  const auto retained_expected_proof = expected_value.proof;

  check(positions <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "seeded provider allocation sweep exceeds fault-index range");
  for (std::size_t point = 0; point < positions; ++point) {
    auto trial = CandidateProvider::create(proof, {}, limits, residual, prefix);
    allocation_count = 0;
    bool failed = false;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      failed = drain(trial) == CandidateStop::allocation_failure;
      check(failed && allocation_count == point + 1,
            "optional residual/cache path fault missed its observed allocation position");
      const auto pending = trial.progress();
      for (int retry = 0; retry != 2; ++retry) {
        const auto again = trial.advance(all_work);
        check(again.stopped_for == CandidateStop::allocation_failure &&
                  same_pending_progress(pending, again.progress),
              "optional residual/cache retry changed its saved stage or retained candidates");
      }
    }
    check(same_residual_value(residual, retained_residual) &&
              same_snapshot_value(prefix, retained_prefix) &&
              same_proof_value(proof, retained_proof) &&
              same_snapshot_value(expected_prefix, expected_value) &&
              same_proof_value(proof, retained_expected_proof),
          "optional seed fault changed its retained residual or cached-prefix handles");
    check(drain(trial) == CandidateStop::exhausted &&
              same_progress_except_faults(trial.progress(), expected.progress) &&
              same_published(trial, expected_prefix) && same_provider_prefix_value(trial, expected_value),
          "optional residual/cache same-owner recovery changed prefix order or provenance");
  }

  // Full factory-admission sweeps include copies/serialization of both optional
  // holders. Those retries recreate the same request; they are not advance retries.
  allocation_count = 0;
  {
    auto sample = CandidateProvider::create(proof, {}, limits, residual, prefix);
    check(sample.original_proof().valid(), "seeded factory baseline lost its proof");
  }
  const auto factory_positions = allocation_count;
  check(factory_positions != 0 && factory_positions <=
            static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "seeded factory admission had no measurable allocation positions");
  for (std::size_t point = 0; point < factory_positions; ++point) {
    allocation_count = 0;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      bool first_failed = false;
      try { auto ignored = CandidateProvider::create(proof, {}, limits, residual, prefix); }
      catch (const std::bad_alloc&) { first_failed = true; }
      check(first_failed && allocation_count == point + 1,
            "seeded factory fault missed its observed admission position");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated = false;
        try { auto ignored = CandidateProvider::create(proof, {}, limits, residual, prefix); }
        catch (const std::bad_alloc&) { repeated = true; }
        check(repeated, "seeded factory admission fault did not remain armed");
      }
    }
    check(same_proof_value(proof, retained_proof) &&
              same_residual_value(residual, retained_residual) &&
              same_snapshot_value(prefix, retained_prefix),
          "seeded factory admission failure changed retained proof, residual candidate, or prefix");
    auto recovered = CandidateProvider::create(proof, {}, limits, residual, prefix);
    check(drain(recovered) == CandidateStop::exhausted &&
              same_progress_except_faults(recovered.progress(), expected.progress) &&
              same_published(recovered, expected_prefix) && same_provider_prefix_value(recovered, expected_value),
          "seeded factory admission did not recover to the same optional-seed state");
  }
}

CandidateCacheStatistics cache_stats(const CandidateCache& cache) {
  return cache.statistics();
}

bool same_cache_stats(const CandidateCacheStatistics& a, const CandidateCacheStatistics& b) {
  return a.hits == b.hits && a.misses == b.misses && a.insertions == b.insertions &&
      a.replacements == b.replacements && a.evictions == b.evictions && a.entries == b.entries;
}

CandidateSnapshot first_snapshot(const VerifiedOptimum& proof) {
  CandidateLimits one;
  one.retained_candidates = 1;
  auto owner = CandidateProvider::create(proof, {}, one);
  check(owner.advance(all_work).stopped_for == CandidateStop::candidate_ready,
        "cache fixture did not publish its exact seed");
  return owner.snapshot();
}

void cache_install_faults(const VerifiedOptimum& a_proof, const VerifiedOptimum& b_proof,
                          const VerifiedOptimum& c_proof, const CandidateSnapshot& a_full,
                          const CandidateSnapshot& a_partial, const CandidateSnapshot& b,
                          const CandidateSnapshot& c) {
  const auto a_full_value = snapshot_value(a_full);
  const auto a_partial_value = snapshot_value(a_partial);
  const auto b_value = snapshot_value(b);
  const auto c_value = snapshot_value(c);
  // Replacing a matching immutable snapshot cannot allocate; it keeps the old
  // FIFO position. Inject failure at the first allocation and require success.
  auto replacement = CandidateCache::create(2);
  check(replacement.install(a_full) == CandidateCacheInstall::inserted &&
            replacement.install(b) == CandidateCacheInstall::inserted,
        "cache replacement fixture setup failed");
  const auto before_replace = cache_stats(replacement);
  allocation_count = 0;
  CandidateCacheInstall replaced = CandidateCacheInstall::inserted;
  {
    FaultScope fault(0);
    replaced = replacement.install(a_partial);
  }
  check(allocation_count == 0 && replaced == CandidateCacheInstall::replaced &&
            replacement.statistics().entries == 2 &&
            replacement.statistics().replacements == before_replace.replacements + 1,
        "matching cache replacement allocated or lost its FIFO slot");
  auto replaced_hit = replacement.lookup(a_proof);
  check(replaced_hit && same_snapshot_value(*replaced_hit, a_partial_value),
        "allocation-free cache replacement did not publish the replacement snapshot value");
  check(same_snapshot_value(a_full, a_full_value) && same_snapshot_value(a_partial, a_partial_value) &&
            same_snapshot_value(b, b_value) && same_snapshot_value(c, c_value),
        "cache replacement changed caller-retained snapshots");

  // Count every allocation for a new node while the FIFO is full. Failed
  // installation must preserve both earlier entries until a successful retry.
  auto calibrate = [&] {
    auto cache = CandidateCache::create(2);
    static_cast<void>(cache.install(a_partial));
    static_cast<void>(cache.install(b));
    allocation_count = 0;
    const auto status = cache.install(c);
    check(status == CandidateCacheInstall::inserted && cache.statistics().entries == 2,
          "cache new-entry baseline failed before eviction");
    return allocation_count;
  };
  const auto positions = calibrate();
  check(positions != 0 && positions <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()),
        "cache new-entry install had no measurable allocation position");
  for (std::size_t point = 0; point < positions; ++point) {
    auto cache = CandidateCache::create(2);
    check(cache.install(a_partial) == CandidateCacheInstall::inserted &&
              cache.install(b) == CandidateCacheInstall::inserted,
          "cache fault fixture setup failed");
    const auto before = cache_stats(cache);
    allocation_count = 0;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      bool failed = false;
      try { static_cast<void>(cache.install(c)); }
      catch (const std::bad_alloc&) { failed = true; }
      check(failed && allocation_count == point + 1 && same_cache_stats(cache_stats(cache), before),
            "failed cache new-entry preparation evicted or changed prior entries/counters");
      for (int retry = 0; retry != 2; ++retry) {
        bool repeated = false;
        try { static_cast<void>(cache.install(c)); }
        catch (const std::bad_alloc&) { repeated = true; }
        check(repeated && same_cache_stats(cache_stats(cache), before),
              "persistent cache install retry changed entries, FIFO or counters");
      }
    }
    auto a_hit = cache.lookup(a_proof);
    auto b_hit = cache.lookup(b_proof);
    const auto c_miss = cache.lookup(c_proof);
    check(a_hit && b_hit && !c_miss && same_snapshot_value(*a_hit, a_partial_value) &&
              same_snapshot_value(*b_hit, b_value) && same_snapshot_value(a_partial, a_partial_value) &&
              same_snapshot_value(b, b_value) && same_snapshot_value(c, c_value),
          "failed cache admission changed a retained snapshot or prior FIFO entry");
    check(cache.install(c) == CandidateCacheInstall::inserted,
          "cache failed to retry new-entry installation before eviction");
    check(!cache.lookup(a_proof), "cache retry did not evict the first FIFO entry");
    const auto retained_b = cache.lookup(b_proof);
    const auto retained_c = cache.lookup(c_proof);
    check(retained_b && retained_c && same_snapshot_value(*retained_b, b_value) &&
              same_snapshot_value(*retained_c, c_value),
          "successful cache retry changed FIFO eviction order");
  }

  // A replacement keeps its original position; adding a third key after the
  // replacement still evicts that first key.
  auto fifo = CandidateCache::create(2);
  static_cast<void>(fifo.install(a_full));
  static_cast<void>(fifo.install(b));
  check(fifo.install(a_partial) == CandidateCacheInstall::replaced,
        "matching cache replacement was not recognized");
  check(fifo.install(c) == CandidateCacheInstall::inserted && !fifo.lookup(a_proof),
        "replacement changed which FIFO entry is evicted");
  const auto fifo_b = fifo.lookup(b_proof);
  const auto fifo_c = fifo.lookup(c_proof);
  check(fifo_b && fifo_c && same_snapshot_value(*fifo_b, b_value) &&
            same_snapshot_value(*fifo_c, c_value),
        "cache replacement moved its original FIFO position");
}

}  // namespace

int main() {
  try {
    const auto boolean_path = scoped_fixture({{0}, {0, 1}, {1}}, {});
    const auto proof = prove(boolean_path);
    check(proof.height() == 2, "Boolean fault fixture minimum was not two");
    auto binding = std::make_shared<const cd::BindingData>(
        cd::BindingData{boolean_path.catalog, boolean_path.query});

    const auto generator = baseline_generator(binding);
    generator_faults(binding, generator);
    generator_caps_and_cancel(binding, generator);

    auto key_tree = std::make_shared<const FreeConnexTree>(proof.upper().tree());
    const auto key = baseline_key(key_tree);
    key_faults(key_tree, key);
    key_caps_and_cancel(key_tree, key);

    auto facade = CandidateProvider::create(proof);
    const auto facade_run = baseline_provider(facade);
    auto facade_snapshot = facade.snapshot();
    check(facade_snapshot.family_exhausted() && facade_snapshot.candidate_count() ==
              facade_run.progress.candidate_count,
          "facade baseline snapshot did not freeze the complete ordered prefix");
    provider_faults(proof, facade_run, facade_snapshot);
    factory_admission_faults(proof, facade_snapshot);
    snapshot_admission_faults(facade, facade_snapshot);
    provider_caps_and_cancel(proof, facade_run, facade_snapshot);

    auto self_join = scoped_fixture({{0}, {0}, {0}}, {});
    self_join.catalog.tables.resize(1);
    for (auto& atom : self_join.query.atoms) atom.table = TableId{0};
    const auto self_proof = prove(self_join);
    auto metadata_fixture = boolean_path;
    metadata_fixture.catalog.tables[0].statistics.row_count = 17;
    const auto metadata_proof = prove(metadata_fixture);
    check(self_proof.height() == 1 && metadata_proof.height() == proof.height(),
          "cache binding fixtures changed their expected minimum heights");
    const auto self_snapshot = first_snapshot(self_proof);
    const auto metadata_snapshot = first_snapshot(metadata_proof);
    const auto partial = first_snapshot(proof);
    cache_install_faults(proof, self_proof, metadata_proof, facade_snapshot, partial,
                         self_snapshot, metadata_snapshot);

    const auto residual_fixture = scoped_fixture({{}, {0, 1}, {0}}, {1});
    const auto residual_proof = prove(residual_fixture);
    check(residual_proof.height() == 2,
          "distinct residual-source fixture did not retain its expected original minimum");
    ResidualOptions residual_options;
    residual_options.mode = ResidualMode::candidates_with_exact_repair;
    auto residual_search = ResidualSearch::create(
        residual_fixture.catalog, residual_fixture.query, residual_options);
    check(residual_search.advance(all_work).stopped_for == ResidualStopReason::complete &&
              residual_search.candidate().has_value(),
          "distinct residual-source fixture did not produce its checked residual candidate");
    const auto residual = *residual_search.candidate();
    check(residual.valid() && residual.height() == residual_proof.height() &&
              validate_tree(residual.catalog(), residual.query(), residual.tree()).valid &&
              !same_tree(residual.tree(), residual_proof.upper().tree()),
          "residual source is not a distinct P02-checked original-binding upper");
    const auto residual_prefix = first_snapshot(residual_proof);
    optional_seed_path_faults(residual_proof, residual, residual_prefix);

    std::cout << "generator_fault_positions=" << generator.allocations
              << " key_fault_positions=" << key.allocations
              << " provider_fault_positions=" << facade_run.allocations << '\n'
              << "retries=two persistent same-owner recovery=ordered outputs+statistics+content+committed transitions\n"
              << "admission_sweeps=factory+snapshot+cache-node seeded_residual_cache_path=verified\n"
              << "caps=depth+records+cells+pending_candidate cancellation=no-allocation retained_handles=yes\n";
  } catch (const std::exception& error) {
    fail_after = -1;
    std::cerr << error.what() << '\n';
    return 1;
  }
}

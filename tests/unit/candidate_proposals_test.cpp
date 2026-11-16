#include "ranking_fixture.hpp"
#include "crown/api/error.hpp"
#include "crown/io/candidates.hpp"
#include "crown/io/explain.hpp"
#include "crown/planner/selection.hpp"
#include "crown/planner/verify.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Deny only the new proposal-owner allocation, once; all other cases allocate
// normally. Reset before throwing so assertions and cleanup remain available.
namespace allocation_probe {
bool deny_next = false;
void* allocate(std::size_t bytes) {
  if (deny_next) { deny_next = false; throw std::bad_alloc{}; }
  if (void* value = std::malloc(bytes == 0 ? 1 : bytes)) return value;
  throw std::bad_alloc{};
}
}
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
void operator delete(void* value) noexcept { std::free(value); }
void operator delete[](void* value) noexcept { std::free(value); }
void operator delete(void* value, std::size_t) noexcept { std::free(value); }
void operator delete[](void* value, std::size_t) noexcept { std::free(value); }

namespace {
using namespace crown;
using namespace crown::planner;
namespace pr = crown::planner::ranking;
namespace ps = crown::planner::selection;
constexpr auto finite = CandidateFamily::finite_proposals_v1;
void check(bool value, const char* message) { if (!value) throw std::runtime_error(message); }

// Literal Boolean R(x),S(x,y),T(y) witnesses. Their supplied P06 optimum is
// genuinely proved by the existing fixture; these trees supply no lower proof.
FreeConnexTree native_tree() {
  return {NodeId{0}, {{"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}, NodeId{2}}, 1, {}},
                     {"r", NodeKind::native, {VariableId{0}}, {}, 0, {}},
                     {"t", NodeKind::native, {VariableId{1}}, {}, 2, {}}}, {}, {}};
}
FreeConnexTree x_tree() {
  return {NodeId{0}, {{"gx", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{2}}, {}, {}},
                     {"r", NodeKind::native, {VariableId{0}}, {}, 0, {}},
                     {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{3}}, 1, {}},
                     {"t", NodeKind::native, {VariableId{1}}, {}, 2, {}}}, {}, {}};
}
FreeConnexTree y_tree() {
  return {NodeId{0}, {{"gy", NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
                     {"t", NodeKind::native, {VariableId{1}}, {}, 2, {}},
                     {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{3}}, 1, {}},
                     {"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
}
FreeConnexTree taller_tree() {
  return {NodeId{0}, {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
                     {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{2}}, 1, {}},
                     {"t", NodeKind::native, {VariableId{1}}, {}, 2, {}}}, {}, {}};
}
std::vector<FreeConnexTree> minima() { return {x_tree(), native_tree(), y_tree()}; }
std::vector<FreeConnexTree> mixed_batch() {
  auto invalid = native_tree(); invalid.nodes[0].children.push_back(NodeId{99});
  auto duplicate = x_tree();
  for (auto& node : duplicate.nodes) { node.id += "_display"; std::reverse(node.children.begin(), node.children.end()); }
  return {std::move(invalid), taller_tree(), x_tree(), std::move(duplicate), native_tree(), y_tree()};
}

// Fail boundedly on a stalled fixture. A yielded prefix is never accepted as
// exhaustion, and every check below remains active with NDEBUG/Release.
void finish(CandidateProvider& owner, std::uint64_t quantum = 10000) {
  for (std::size_t step = 0; step < 100000; ++step) {
    const auto stopped = owner.advance({quantum, {}}).stopped_for;
    if (stopped == CandidateStop::exhausted) return;
    check(stopped == CandidateStop::candidate_ready || stopped == CandidateStop::quantum_work,
          "finite proposal batch stopped unexpectedly");
  }
  throw std::runtime_error("finite proposal batch did not exhaust");
}
MinimumHeightCandidate at(const CandidateSnapshot& snapshot, std::size_t index) {
  const auto candidate = snapshot.candidate(index);
  check(candidate.has_value(), "snapshot omitted a published proposal");
  return *candidate;
}
std::vector<std::string> keys(const CandidateSnapshot& snapshot) {
  std::vector<std::string> out;
  for (std::size_t i = 0; i < snapshot.candidate_count(); ++i) out.push_back(at(snapshot, i).structural_key());
  return out;
}
CandidateSnapshot admitted(const VerifiedOptimum& proof, std::vector<FreeConnexTree> trees,
                           std::uint64_t quantum = 10000) {
  auto owner = CandidateProvider::from_proposals(proof, std::move(trees));
  finish(owner, quantum); return owner.snapshot();
}
template<class Operation> void rejects_binding(Operation operation) {
  try { operation(); }
  catch (const Error& error) { check(error.code() == "candidate_binding", "wrong cross-family rejection"); return; }
  throw std::runtime_error("cross-family reuse was accepted");
}

void empty_and_admission(const c02_test::Fixture& fixture, const VerifiedOptimum& proof) {
  auto empty = CandidateProvider::from_proposals(proof, {});
  check(empty.progress().family == finite && !empty.progress().family_exhausted && empty.candidate_count() == 0,
        "empty batch injected a seed or asserted exhaustion before processing");
  finish(empty);
  check(empty.snapshot().family() == finite && empty.snapshot().family_exhausted() && empty.candidate_count() == 0,
        "empty finite batch did not exhaust without fallback");
  check(pr::rank(empty.snapshot()).stop == pr::Stop::no_candidates, "empty batch acquired a ranking fallback");

  const auto tall = validate_tree(fixture.catalog, fixture.query, taller_tree());
  check(tall.valid && tall.native_height == 3 && proof.height() == 2, "literal taller control is not a valid height gap");
  auto owner = CandidateProvider::from_proposals(proof, mixed_batch()); finish(owner);
  const auto progress = owner.progress(); const auto snapshot = owner.snapshot();
  check(progress.family == finite && progress.family_exhausted && snapshot.family() == finite &&
      progress.statistics.proposed == 6 && progress.statistics.rejected == 1 && progress.statistics.taller == 1 &&
      progress.statistics.duplicates == 1 && progress.statistics.published == 3,
      "invalid/taller/duplicate proposals did not produce the expected finite family");
  const auto original = io::write_verified_optimum(proof);
  const std::uint64_t positions[] = {2, 4, 5};
  for (std::size_t i = 0; i < 3; ++i) {
    const auto candidate = at(snapshot, i); const auto provenance = candidate.provenance();
    check(candidate.height() == 2 && candidate.validation().valid && provenance.source == CandidateSource::supplied_proposal &&
        provenance.family == finite && provenance.sequence == positions[i], "proposal binding/provenance or input order changed");
    const auto report = io::write_minimum_height_candidate(candidate);
    check(report.at("original_proof").at("certificate") == original &&
        report.at("query_binding") == original.at("query_binding"), "proposal replaced its original proof or binding");
  }
  const auto sliced = admitted(proof, mixed_batch(), 1);
  check(keys(sliced) == keys(snapshot), "single-step grants changed duplicate suppression or ordered results");
  for (std::size_t i = 0; i < 3; ++i)
    check(at(sliced, i).provenance().sequence == positions[i], "slicing changed first-published provenance");
}

// Raising a grant must preserve consumed work and old handles, then resume
// the same pending draft rather than restart, skip it, or relabel a prefix.
void resume(CandidateProvider& owner, CandidateLimits limits, const std::vector<std::string>& expected) {
  const auto before = owner.progress();
  check(!before.family_exhausted && owner.raise_limits(limits) == LimitChange::applied, "proposal grant extension failed");
  const auto after = owner.progress();
  check(after.work.attempted == before.work.attempted && after.records == before.records &&
      after.cells == before.cells && after.candidate_count == before.candidate_count, "grant extension reset consumed progress");
  finish(owner);
  check(owner.snapshot().family_exhausted() && keys(owner.snapshot()) == expected, "resumed batch lost or changed a proposal");
}
void stops_and_retry(const VerifiedOptimum& proof) {
  const auto expected = keys(admitted(proof, minima()));
  auto inert = CandidateProvider::from_proposals(proof, minima());
  check(inert.advance({0, {}}).stopped_for == CandidateStop::quantum_work &&
      inert.advance({1000, std::chrono::nanoseconds{0}}).stopped_for == CandidateStop::quantum_time &&
      inert.progress().work.attempted == 0 && inert.progress().records == 0 && inert.candidate_count() == 0,
      "zero proposal quantum performed work");

  CandidateLimits work_limits; work_limits.enumeration.work = 1;
  auto work = CandidateProvider::from_proposals(proof, minima(), {}, work_limits);
  check(work.advance({10000, {}}).stopped_for == CandidateStop::total_work && work.progress().work.attempted == 1,
        "proposal work ceiling did not stop the pending batch");
  auto limits = work.limits(); limits.enumeration.work = 50'000'000; resume(work, limits, expected);

  CandidateLimits record_limits; record_limits.records = 0;
  auto records = CandidateProvider::from_proposals(proof, minima(), {}, record_limits);
  check(records.advance({10000, {}}).stopped_for == CandidateStop::record_limit && records.progress().records == 0,
        "proposal owner ignored the record ceiling");
  limits = records.limits(); limits.records = 1'000'000; resume(records, limits, expected);

  CandidateLimits cell_limits; cell_limits.cells = 0;
  auto cells = CandidateProvider::from_proposals(proof, minima(), {}, cell_limits);
  check(cells.advance({10000, {}}).stopped_for == CandidateStop::cell_limit && cells.candidate_count() == 0,
        "proposal canonicalization ignored the cell ceiling");
  limits = cells.limits(); limits.cells = 10'000'000; resume(cells, limits, expected);

  CandidateLimits capacity_limits; capacity_limits.retained_candidates = 1;
  auto capacity = CandidateProvider::from_proposals(proof, minima(), {}, capacity_limits);
  check(capacity.advance({10000, {}}).stopped_for == CandidateStop::candidate_ready, "capacity fixture omitted first proposal");
  const auto prefix = capacity.snapshot(); const auto first = at(prefix, 0);
  check(capacity.advance({10000, {}}).stopped_for == CandidateStop::candidate_capacity &&
      prefix.candidate_count() == 1 && !prefix.family_exhausted(), "capacity stop mislabeled its retained prefix");
  ps::Request strict; strict.policy = ps::Policy::height_only; strict.family = ps::FamilyPolicy::require_exhausted_family;
  check(ps::select(prefix, ps::DirectCQ{}, strict).stop == ps::Stop::incomplete_family,
        "C05 treated a partial supplied batch as an exhausted family");
  limits = capacity.limits(); limits.retained_candidates = 3; resume(capacity, limits, expected);
  check(first.structural_key() == expected[0] && prefix.candidate_count() == 1 && !prefix.family_exhausted(),
        "resumption mutated an older handle or snapshot");

  auto allocation = CandidateProvider::from_proposals(proof, minima());
  allocation_probe::deny_next = true;
  const auto denied = allocation.advance({1, {}});
  const bool consumed = !allocation_probe::deny_next; allocation_probe::deny_next = false;
  check(consumed && denied.stopped_for == CandidateStop::allocation_failure && denied.progress.records == 0 &&
      denied.progress.statistics.proposed == 0 && denied.progress.work.allocation_failures == 1,
      "proposal owner allocation denial lost its retryable input");
  finish(allocation);
  check(keys(allocation.snapshot()) == expected, "allocation retry skipped or changed the first proposal");

  auto cancelled = CandidateProvider::from_proposals(proof, minima());
  check(cancelled.advance({10000, {}}).stopped_for == CandidateStop::candidate_ready, "cancel fixture omitted first proposal");
  const auto held = at(cancelled.snapshot(), 0); cancelled.cancel();
  check(cancelled.advance({10000, {}}).stopped_for == CandidateStop::cancelled &&
      !cancelled.snapshot().family_exhausted() && held.structural_key() == expected[0], "cancellation lost a published proposal");
}

void ranking_cache_and_reports(const CandidateSnapshot& exact, io::Json* reports) {
  const auto proof = exact.original_proof();
  // Identical raw trees/order/completion isolate the family dimension of the
  // C05 cache key; a different tree representation cannot explain the miss.
  std::vector<FreeConnexTree> copies;
  for (std::size_t i = 0; i < exact.candidate_count(); ++i) copies.push_back(at(exact, i).tree());
  const auto supplied = admitted(proof, std::move(copies));
  check(keys(supplied) == keys(exact) && supplied.family_exhausted() && exact.family_exhausted(),
        "cache control did not retain exactly the same complete raw tree family");
  auto candidate_cache = CandidateCache::create();
  check(candidate_cache.install(exact) == CandidateCacheInstall::inserted, "old candidate cache admission changed");
  rejects_binding([&] { static_cast<void>(candidate_cache.install(supplied)); });
  rejects_binding([&] { static_cast<void>(CandidateProvider::create(proof, {}, {}, {}, supplied)); });
  const auto cached = candidate_cache.lookup(proof);
  check(candidate_cache.statistics().entries == 1 && candidate_cache.statistics().insertions == 1 &&
      candidate_cache.statistics().replacements == 0 && cached && cached->family() == exact.family(),
      "finite batch polluted the original candidate cache");

  const auto ranked = pr::rank(supplied);
  check(ranked.stop == pr::Stop::complete && ranked.result && ranked.result->snapshot().family() == finite &&
      ranked.result->selected().provenance().family == finite, "C02 lost finite proposal family identity");
  const auto names = keys(supplied);
  check(ranked.result->selected().structural_key() == *std::min_element(names.begin(), names.end()),
        "height-only C02 selection violated its stable full-key tie break");

  ps::Request request; request.policy = ps::Policy::height_only;
  request.fallback = pr::Fallback::require_evidence; request.family = ps::FamilyPolicy::require_exhausted_family;
  const ps::Source source = ps::DirectCQ{}; auto cache = ps::PlanCache::create();
  const auto original = ps::select(exact, source, request, {}, &cache, ps::CacheUse::read_write);
  const auto finite_choice = ps::select(supplied, source, request, {}, &cache, ps::CacheUse::read_write);
  check(original.selection && finite_choice.selection && original.stop == ps::Stop::complete && finite_choice.stop == ps::Stop::complete,
        "C05 failed to select the two checked family controls");
  const auto& chosen = *finite_choice.selection;
  check(chosen.snapshot().family() == finite && chosen.selected().provenance().family == finite &&
      chosen.selected().structural_key() == original.selection->selected().structural_key() &&
      chosen.plan().physical_sha256() == original.selection->plan().physical_sha256(), "C05 changed the identical chosen structure");
  check(chosen.cache_binding() && original.selection->cache_binding() && chosen.cache_binding() != original.selection->cache_binding() &&
      chosen.cache_observation().disposition == ps::CacheDisposition::inserted && cache.statistics().entries == 2,
      "C05 cache merged different proposal families with identical raw trees");
  const auto hit = ps::select(supplied, source, request, {}, &cache, ps::CacheUse::read_only);
  check(hit.selection && hit.selection->cache_observation().disposition == ps::CacheDisposition::hit &&
      hit.selection->snapshot().family() == finite && hit.selection->cache_binding() == chosen.cache_binding(),
      "C05 cache hit lost its finite supplied family");

  auto report_owner = CandidateProvider::from_proposals(proof, minima());
  const auto prefix_report = io::write_candidate_progress(report_owner);
  check(prefix_report.at("family") == "finite-proposals-v1" && !prefix_report.at("family_exhausted").get<bool>() &&
      prefix_report.at("exhaustion_scope") == "supplied_finite_proposals_v1_only", "proposal progress reports invented coverage");
  finish(report_owner);
  const auto snapshot_report = io::write_candidate_snapshot(report_owner.snapshot());
  check(snapshot_report.at("family_exhausted").get<bool>() && snapshot_report.at("candidate_count") == 3 &&
      snapshot_report.at("exhaustion_scope") == "supplied_finite_proposals_v1_only", "proposal snapshot report lost batch scope");
  const auto candidate_report = io::write_minimum_height_candidate(chosen.selected());
  check(candidate_report.at("family") == "finite-proposals-v1" &&
      candidate_report.at("provenance").at("source") == "supplied_proposal" &&
      candidate_report.at("original_proof").at("certificate") == io::write_verified_optimum(proof),
      "proposal candidate report invented source or proof authority");
  const auto explanation = observability::PlanExplanation::create(chosen.plan(), chosen.selected(), supplied);
  const auto explained = io::Json::parse(io::write_explain_json(explanation));
  check(explained.at("candidate_family").at("family") == "finite-proposals-v1" &&
      explained.at("candidate_family").at("exhaustion_scope") == "supplied_finite_proposals_v1_only" &&
      explained.at("candidate_family").at("global_cost_complete") == false &&
      explained.at("selected_candidate").at("source") == "supplied_proposal" &&
      io::write_explain_text(explanation).find("finite-proposals-v1") != std::string::npos, "EXPLAIN mislabeled supplied coverage");
  bool mismatch = false;
  try { static_cast<void>(observability::PlanExplanation::create(chosen.plan(), chosen.selected(), exact)); }
  catch (const Error& error) { mismatch = error.code() == "explain_family"; }
  check(mismatch, "typed EXPLAIN paired a supplied candidate with another family");
  if (reports) {
    auto add = [&](const char* name, const char* schema, io::Json document) {
      reports->push_back({{"name", name}, {"schema", schema}, {"document", std::move(document)}});
    };
    constexpr auto schema = "candidate-report-v1.schema.json";
    add("finite_progress", schema, prefix_report);
    add("finite_snapshot", schema, snapshot_report);
    add("finite_candidate", schema, candidate_report);
    add("finite_explain", "explain-report-v2.schema.json", explained);
    add("normal_explain", "explain-report-v2.schema.json", io::Json::parse(io::write_explain_json(
        observability::PlanExplanation::create(original.selection->plan(), original.selection->selected(), exact))));
  }
}

void retained_lifetime() {
  // All source/proof/provider locals die before the returned snapshot is used.
  const auto held = [] {
    const auto fixture = c02_test::fixture(); const auto exact = c02_test::candidates(fixture);
    return admitted(exact.original_proof(), {x_tree(), native_tree()});
  }();
  check(held.family() == finite && held.candidate_count() == 2 && held.original_proof().valid() &&
      at(held, 0).catalog().tables.at(1).name == "S" && at(held, 0).query().atoms.size() == 3,
      "retained proposal snapshot borrowed destroyed source/proof/batch state");
  check(io::write_candidate_snapshot(held).at("prefix").size() == 2, "retained proposal serialization lost its owners");
}
}

int main(int argc, char** argv) {
  try {
    const bool emit = argc == 2 && std::string_view(argv[1]) == "--emit";
    check(argc == 1 || emit, "usage: candidate_proposals_test [--emit]");
    auto reports = io::Json::array();
    const auto fixture = c02_test::fixture(); const auto exact = c02_test::candidates(fixture);
    empty_and_admission(fixture, exact.original_proof());
    stops_and_retry(exact.original_proof());
    ranking_cache_and_reports(exact, emit ? &reports : nullptr);
    retained_lifetime();
    if (emit) std::cout << reports.dump() << '\n';
    else std::cout << "finite supplied proposals: original proof, rejection/resume, family caches and reports passed\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}

#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/ranking.hpp"
#include "crown/planner/search.hpp"
#include "crown/runtime/ranking_evidence.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
namespace p = crown::planner;
namespace r = crown::runtime;
namespace ranking = crown::planner::ranking;
namespace evidence = crown::runtime::ranking;

static_assert(!std::is_default_constructible_v<ranking::Evidence>);
static_assert(!std::is_default_constructible_v<ranking::Result>);
static_assert(!std::is_default_constructible_v<evidence::RuntimeEvidence>);
static_assert(!std::is_constructible_v<ranking::Evidence, PhysicalPlan, ranking::EvidenceIdentity>);
static_assert(std::is_same_v<decltype(std::declval<const ranking::Evidence&>().identity()), const ranking::EvidenceIdentity&>);
static_assert(std::is_same_v<decltype(std::declval<const ranking::Evidence&>().weights()), const ranking::EvidenceVector<ranking::InputWeight>&>);
static_assert(std::is_same_v<decltype(std::declval<const ranking::Result&>().scores()), const ranking::ScoreVector<ranking::CandidateScore>&>);

void require(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
}

std::string read(const std::filesystem::path& path) {
  std::ifstream input(path);
  require(input.good(), "cannot read fixture " + path.string());
  return {std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
}

p::VerifiedOptimum prove(const Catalog& catalog, const Query& query) {
  p::SearchOptions options;
  options.limits.producer.work = 100'000'000;
  options.limits.replay.work = 100'000'000;
  options.limits.logical_depth = 64;
  auto search = p::ExactSearch::create(catalog, query, options);
  for (unsigned step = 0; step < 2'000; ++step) {
    const auto result = search.advance({100'000, {}});
    if (result.progress.result == p::ResultKind::verified_optimum) {
      auto proof = search.optimum();
      require(proof && proof->valid(), "P06 omitted its checked optimum");
      return *proof;
    }
    require(result.stopped_for == p::StopReason::quantum_work ||
                result.stopped_for == p::StopReason::quantum_time,
            "finite P06 proof stopped without an optimum");
  }
  throw std::runtime_error("finite P06 call guard exhausted");
}

void finish(p::CandidateProvider& provider) {
  for (unsigned step = 0; step < 2'000; ++step) {
    const auto result = provider.advance({100'000, {}});
    if (result.stopped_for == p::CandidateStop::exhausted) return;
    require(result.stopped_for == p::CandidateStop::candidate_ready ||
                result.stopped_for == p::CandidateStop::quantum_work ||
                result.stopped_for == p::CandidateStop::quantum_time,
            "finite P07 provider stopped before family exhaustion");
  }
  throw std::runtime_error("finite P07 call guard exhausted");
}

p::CandidateProvider provider(p::VerifiedOptimum proof) {
  p::CandidateLimits limits;
  limits.enumeration.work = 100'000'000;
  limits.logical_depth = 64;
  limits.records = 1'000'000;
  limits.cells = 10'000'000;
  limits.retained_candidates = 32;
  return p::CandidateProvider::create(std::move(proof), {}, limits);
}

// Independent shape fingerprint, not the production structural-key encoding.
// Labels/node vector positions are ignored; scopes and occurrence identities
// remain literal, and unordered children are compared as full strings.
std::string shape_node(const FreeConnexTree& tree, NodeId id) {
  const auto& node = tree.nodes.at(id.value);
  std::string out = node.kind == NodeKind::native ? "N" : "G";
  if (node.occurrence) out += std::to_string(*node.occurrence);
  out += ':';
  for (const auto variable : node.scope) out += std::to_string(variable.value) + ',';
  std::vector<std::string> children;
  for (const auto child : node.children) children.push_back(shape_node(tree, child));
  std::sort(children.begin(), children.end());
  out += '[';
  for (const auto& child : children) out += '{' + child + '}';
  return out + ']';
}

std::string shape(const FreeConnexTree& tree) {
  return tree.root ? shape_node(tree, *tree.root) : "empty";
}

struct BooleanFixture {
  Document document;
  p::CandidateSnapshot all;
  p::CandidateSnapshot partial;
  p::CandidateSnapshot empty;
  std::map<std::string, std::string> label_by_key;
  std::map<std::string, p::MinimumHeightCandidate> by_label;
  Database initial;
};

BooleanFixture boolean_fixture(const std::filesystem::path& root) {
  auto document = io::read_document(read(root / "tests/candidates/queries/boolean_rst.cq.json"));
  const auto proof = prove(document.catalog, document.query);
  require(proof.height() == 2, "independently checked Boolean optimum is not 2");
  auto owner = provider(proof);
  const auto empty = owner.snapshot();
  for (unsigned i = 0; owner.candidate_count() == 0 && i < 2'000; ++i) {
    static_cast<void>(owner.advance({100'000, {}}));
  }
  require(owner.candidate_count() == 1, "P07 does not publish one candidate at a time");
  const auto partial = owner.snapshot();
  require(!partial.family_exhausted(), "prefix incorrectly claims exhaustion");
  finish(owner);
  const auto all = owner.snapshot();
  require(all.family_exhausted() && all.candidate_count() == 3, "Boolean normal-form family is not the three expected candidates");
  require(partial.candidate_count() == 1 && !partial.family_exhausted(), "retained prefix changed during provider advancement");
  std::map<std::string, std::string> expected;
  for (const auto& label : {std::string("native_s"), std::string("generalized_x"), std::string("generalized_y")}) {
    auto tree = io::read_tree(read(root / ("tests/candidates/trees/boolean_rst_" + label + "_root.tree.json")), document.catalog, document.query);
    const auto validated = p::validate_tree(document.catalog, document.query, tree);
    require(validated.valid && validated.native_height == 2, "literal fixture geometry is not P02-valid at height 2");
    require(expected.emplace(shape(tree), label).second, "literal fixture shapes collide");
  }
  BooleanFixture fixture{std::move(document), all, partial, empty, {}, {}, {}};
  for (std::size_t i = 0; i < all.candidate_count(); ++i) {
    const auto candidate = all.candidate(i);
    require(candidate && candidate->valid() && candidate->height() == 2 && candidate->original_proof().height() == 2,
            "candidate lost typed original height proof");
    const auto found = expected.find(shape(candidate->tree()));
    require(found != expected.end(), "candidate is outside the literal three-tree family");
    require(fixture.label_by_key.emplace(candidate->structural_key(), found->second).second, "duplicate structural key");
    require(fixture.by_label.emplace(found->second, *candidate).second, "duplicate literal geometry");
  }
  require(fixture.label_by_key.size() == 3 && fixture.by_label.size() == 3, "missing structural-key/geometry identity");
  fixture.initial.tables.resize(3);
  fixture.initial.tables[0].insert(Row{std::string("x")});
  fixture.initial.tables[1].insert(Row{std::string("x"), std::string("y")});
  fixture.initial.tables[2].insert(Row{std::string("y")});
  return fixture;
}

PhysicalPlan lower(const p::MinimumHeightCandidate& candidate) {
  return p::lower_tree(candidate.catalog(), candidate.query(), candidate.tree());
}

r::workload::Options counters(std::uint64_t period = 1, std::uint64_t offset = 0) {
  r::workload::Options options;
  options.mode = r::workload::Mode::counters;
  options.period = period;
  options.offset = offset;
  return options;
}

template<class Runtime>
evidence::RuntimeEvidence capture_checked(const p::CandidateSnapshot& candidates, const Runtime& owner,
                                  const evidence::CaptureOptions& options = {}) {
  auto captured = evidence::capture(candidates, owner, options);
  require(captured.stop == ranking::Stop::complete && captured.evidence.has_value(), "runtime capture failed");
  return *captured.evidence;
}

ranking::Result rank(const p::CandidateSnapshot& candidates, ranking::Policy policy,
                     const std::optional<ranking::Evidence>& inputs = {}, ranking::Fallback fallback = ranking::Fallback::require_evidence) {
  ranking::Request request;
  request.policy = policy;
  request.fallback = fallback;
  auto result = ranking::rank(candidates, request, inputs);
  require(result.stop == ranking::Stop::complete && result.result.has_value(), "ranking did not publish a complete result");
  require(result.evaluated == candidates.candidate_count() && result.result->scores().size() == candidates.candidate_count(),
          "ranking omitted retained candidates");
  return *result.result;
}

bool has(ranking::Reasons reasons, ranking::Reason reason) {
  return (reasons & ranking::reason(reason)) != 0;
}

using WeightRow = std::tuple<std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t>;
std::map<std::size_t, WeightRow> weights(const ranking::Evidence& value) {
  std::map<std::size_t, WeightRow> result;
  for (const auto& row : value.weights()) {
    require(result.emplace(row.table.value, WeightRow{row.inserts, row.erases, row.changed, row.noop}).second,
            "duplicate physical table weight");
  }
  return result;
}

std::map<std::size_t, std::uint64_t> sources(const ranking::Evidence& value) {
  std::map<std::size_t, std::uint64_t> result;
  for (const auto& row : value.sources()) require(result.emplace(row.table.value, row.rows).second, "duplicate source table cardinality");
  return result;
}

Relation answers(const r::PhysicalRuntime& owner) {
  auto cursor = owner.results();
  Relation rows;
  while (const auto row = cursor.next()) rows.insert(crown::storage::export_row(row->values()));
  return rows;
}

void noop(r::PhysicalRuntime& owner, std::size_t table, const Row& row, unsigned count) {
  for (unsigned i = 0; i < count; ++i) {
    const auto epoch = owner.apply({owner.sequence() + 1, TableId{table}, SetOperation::insert, row});
    require(!epoch.input.physical_changed, "literal duplicate insert unexpectedly changed source");
  }
}

void verify_depth_scores(const BooleanFixture& fixture, const ranking::Result& result, bool hot_r) {
  const std::map<std::string, std::array<std::uint64_t, 3>> depth{
      {"native_s", {2, 1, 2}}, {"generalized_x", {1, 1, 2}}, {"generalized_y", {2, 1, 1}}};
  const std::map<std::string, std::string> expected = hot_r
      ? std::map<std::string, std::string>{{"native_s", "195"}, {"generalized_x", "105"}, {"generalized_y", "190"}}
      : std::map<std::string, std::string>{{"native_s", "195"}, {"generalized_x", "190"}, {"generalized_y", "105"}};
  require(result.effective_policy() == ranking::Policy::committed_input_native_depth && result.fallback_reasons() == 0,
          "eligible literal census used fallback");
  for (const auto& score : result.scores()) {
    const auto& label = fixture.label_by_key.at(std::string(score.structural_key));
    require(score.height == 2 && score.numerator == expected.at(label) && score.denominator == "100", "literal hot-table rational mismatch");
    require(score.depths.size() == 3, "missing native occurrence depths");
    std::set<std::size_t> seen;
    for (const auto& item : score.depths) {
      require(item.occurrence.value < 3 && item.table.value == item.occurrence.value &&
                  seen.insert(item.occurrence.value).second && item.depth == depth.at(label)[item.occurrence.value],
              "literal occurrence depth differs from the three fixture trees");
    }
    require(score.candidate.structural_key() == score.structural_key && score.candidate.original_proof().height() == 2,
            "ranking relabelled its candidate/proof");
  }
  require(result.selected().structural_key() == fixture.by_label.at(hot_r ? "generalized_x" : "generalized_y").structural_key(),
          "hot-table winner is not the literal minimum");
}

void candidate_semantics_and_height(const BooleanFixture& fixture) {
  auto empty = ranking::rank(fixture.empty);
  require(empty.stop == ranking::Stop::no_candidates && !empty.result, "empty actual snapshot published a selection");
  const auto prefix = rank(fixture.partial, ranking::Policy::height_only);
  require(!prefix.snapshot().family_exhausted() && prefix.snapshot().candidate_count() == 1, "ranker invented family exhaustion");
  const auto height = rank(fixture.all, ranking::Policy::height_only);
  require(height.selected().structural_key() == fixture.label_by_key.begin()->first, "height tie did not use full structural-key order");
  require(height.snapshot().family_exhausted() && height.selected().original_proof().height() == 2, "height rank changed structural authority");
  for (const auto& [label, candidate] : fixture.by_label) {
    auto owner = r::PhysicalRuntime::initialize(lower(candidate), fixture.initial);
    require(owner.has_answer() && owner.snapshot().physical.tables == fixture.initial.tables, "initial Boolean literal join differs for " + label);
    static_cast<void>(owner.apply({1, TableId{1}, SetOperation::erase, {std::string("x"), std::string("y")}}));
    require(!owner.has_answer(), "Boolean result survived deletion of its sole S witness");
    static_cast<void>(owner.apply({2, TableId{1}, SetOperation::insert, {std::string("x"), std::string("y")}}));
    require(owner.has_answer() && owner.snapshot().physical.tables == fixture.initial.tables, "Boolean literal result did not recover");
  }
}

void hot_reversal_and_memory(const BooleanFixture& fixture) {
  auto owner = r::PhysicalRuntime::initialize(lower(fixture.by_label.at("native_s")), fixture.initial);
  owner.configure_workload_statistics(counters());
  noop(owner, 0, *fixture.initial.tables[0].begin(), 90);
  noop(owner, 1, *fixture.initial.tables[1].begin(), 5);
  noop(owner, 2, *fixture.initial.tables[2].begin(), 5);
  const auto before = owner.workload_statistics().metadata();
  const auto hot_r = capture_checked(fixture.all, owner);
  require(hot_r.inputs().identity().owner == owner.owner().value && hot_r.inputs().identity().epoch == 100,
          "capture is not bound to actual committed owner");
  require(hot_r.inputs().denominator() == 100 && hot_r.inputs().depth_reasons() == 0 && hot_r.inputs().memory_reasons() == 0,
          "exact positive census/source evidence unavailable");
  require(weights(hot_r.inputs()) == std::map<std::size_t, WeightRow>{{0, {90, 0, 0, 90}}, {1, {5, 0, 0, 5}}, {2, {5, 0, 0, 5}}},
          "physical no-op census is not literal R90/S5/T5");
  require(sources(hot_r.inputs()) == std::map<std::size_t, std::uint64_t>{{0, 1}, {1, 1}, {2, 1}}, "literal source cardinalities changed");
  const auto first = rank(fixture.all, ranking::Policy::committed_input_native_depth, hot_r.inputs());
  verify_depth_scores(fixture, first, true);
  ranking::Request current_request;
  current_request.policy = ranking::Policy::committed_input_native_depth;
  const auto current = evidence::rank_current(fixture.all, owner, current_request);
  require(current.stop == ranking::Stop::complete && current.result && current.result->evidence() &&
              current.result->evidence()->identity().owner == owner.owner().value &&
              current.result->evidence()->identity().epoch == owner.sequence(), "live wrapper did not retain its actual owner boundary");
  verify_depth_scores(fixture, *current.result, true);
  const auto memory = rank(fixture.all, ranking::Policy::tuple_index_slots, hot_r.inputs());
  for (const auto& score : memory.scores()) {
    const auto& label = fixture.label_by_key.at(std::string(score.structural_key));
    require(score.slots == (label == "native_s" ? "24" : "32"), "literal candidate-local slot proxy mismatch");
    require(score.modeled_plan.has_value(), "memory score omitted its own lowered plan");
    const auto plan = PhysicalPlan::from_compiled(*score.modeled_plan);
    require(shape(plan.tree()) == shape(score.candidate.tree()), "memory model borrowed another candidate's topology");
    require(plan.indexes().size() == (label == "native_s" ? 2U : 1U), "literal reverse-index count mismatch");
    require(std::count_if(plan.nodes().begin(), plan.nodes().end(), [](const auto& node) { return node.visible_relation.has_value(); }) == 1,
            "Boolean candidate has a non-root visible relation");
    require(score.populations.size() == plan.nodes().size() && score.slot_terms.size() == (label == "native_s" ? 12U : 14U),
            "literal candidate population/slot-term count mismatch");
    for (const auto& population : score.populations) {
      const auto& node = plan.nodes().at(population.node.value);
      const bool generalized = node.kind == NodeKind::generalized;
      require(population.records == (generalized ? "2" : "1") && population.survivors == (generalized ? "2" : "1") &&
                  population.parent_support == "1" && population.visible == (node.parent ? std::optional<std::string>{} : std::optional<std::string>{"1"}),
              "literal per-node population bound mismatch");
    }
    std::set<std::pair<std::size_t, std::optional<std::size_t>>> terms;
    for (const auto& term : score.slot_terms) {
      require(terms.emplace(term.relation.value, term.index ? std::optional<std::size_t>{term.index->value} : std::nullopt).second,
              "duplicate modeled relation/index term");
      const auto& relation = plan.relations().at(term.relation.value);
      require(relation.node.has_value(), "physical source storage entered candidate memory proxy");
      const auto& node = plan.nodes().at(relation.node->value);
      if (term.index) {
        require(term.width == 1 && term.population == "1" && term.contribution == "2", "literal reverse-index slot term mismatch");
      } else if (relation.role == RelationRole::parent_support || relation.role == RelationRole::visible) {
        require(term.width == (node.parent ? 1U : 0U) && term.population == "1" &&
                    term.contribution == (node.parent ? "2" : "1"), "literal P/E slot term mismatch");
      } else if (node.kind == NodeKind::generalized) {
        require(term.width == 1 && term.population == "2" && term.contribution == "4", "generalized union bound incorrectly used observed distinct keys");
      } else {
        require(node.occurrence.has_value(), "native memory term lost occurrence");
        const bool binary_s = node.occurrence->value == 1;
        require(term.width == (binary_s ? 2U : 1U) && term.population == "1" && term.contribution == (binary_s ? "3" : "2"),
                "literal native relation slot term mismatch");
      }
    }
  }
  require(memory.selected().structural_key() == fixture.by_label.at("native_s").structural_key(), "memory proxy did not select literal24 over32");
  ranking::Request payload_request;
  payload_request.policy = ranking::Policy::tuple_index_slots;
  payload_request.fallback = ranking::Fallback::height_only;
  payload_request.limits.payload_bytes = memory.usage().payload_bytes;
  require(payload_request.limits.payload_bytes != 0, "candidate memory model charged no payload");
  const auto exact_payload = ranking::rank(fixture.all, payload_request, hot_r.inputs());
  require(exact_payload.stop == ranking::Stop::complete && exact_payload.result &&
              exact_payload.result->selected().structural_key() == memory.selected().structural_key(),
          "exact modeled payload boundary changed or failed candidate ranking");
  --payload_request.limits.payload_bytes;
  const auto short_payload = ranking::rank(fixture.all, payload_request, hot_r.inputs());
  require(short_payload.stop == ranking::Stop::byte_limit && !short_payload.result,
          "one-under modeled payload published a partial selection or used fallback");
  require(memory.scores().size() == 3 && memory.selected().structural_key() == fixture.by_label.at("native_s").structural_key(),
          "later resource failure modified prior owning result");
  require(owner.sequence() == 100 && owner.has_answer() && owner.snapshot().physical.tables == fixture.initial.tables &&
              owner.workload_statistics().metadata().attempts == before.attempts,
          "capture/ranking changed owner data, census or Boolean semantics");
  owner.reset_workload_statistics();
  const auto reset = evidence::revalidate(hot_r, owner);
  require(has(reset.depth, ranking::Reason::interval_changed) && !reset.usable(ranking::Policy::committed_input_native_depth),
          "reset reused old census interval");
  require(reset.boundary == 0 && reset.usable(ranking::Policy::tuple_index_slots),
          "workload reset incorrectly staled unchanged data cardinalities");
  noop(owner, 0, *fixture.initial.tables[0].begin(), 5);
  noop(owner, 1, *fixture.initial.tables[1].begin(), 5);
  noop(owner, 2, *fixture.initial.tables[2].begin(), 90);
  const auto hot_t = capture_checked(fixture.all, owner);
  verify_depth_scores(fixture, rank(fixture.all, ranking::Policy::committed_input_native_depth, hot_t.inputs()), false);
  verify_depth_scores(fixture, first, true);
  verify_depth_scores(fixture, rank(fixture.all, ranking::Policy::committed_input_native_depth, hot_r.inputs()), true);
  require(hot_r.inputs().denominator() == 100 && hot_r.inputs().identity().epoch == 100 && hot_t.inputs().identity().epoch == 200,
          "old owning evidence changed after reset/update");
}

void changed_noop_abort_and_freshness(const BooleanFixture& fixture) {
  auto owner = r::PhysicalRuntime::initialize(lower(fixture.by_label.at("native_s")), fixture.initial);
  owner.configure_workload_statistics(counters());
  const Row added{std::string("new-x")};
  static_cast<void>(owner.apply({1, TableId{0}, SetOperation::insert, added}));
  noop(owner, 0, added, 1);
  static_cast<void>(owner.apply({3, TableId{0}, SetOperation::erase, added}));
  static_cast<void>(owner.apply({4, TableId{0}, SetOperation::erase, added}));
  const auto before = capture_checked(fixture.all, owner);
  require(weights(before.inputs()).at(0) == WeightRow{2, 2, 2, 2} && before.inputs().denominator() == 4,
          "changed/no-op physical insert/erase scope mismatch");
  auto pending = owner.prepare({5, TableId{1}, SetOperation::erase, *fixture.initial.tables[1].begin()});
  const auto private_read = capture_checked(fixture.all, owner);
  require(has(private_read.inputs().depth_reasons(), ranking::Reason::pending) &&
              has(private_read.inputs().memory_reasons(), ranking::Reason::pending), "pending facts were eligible");
  require(!evidence::revalidate(before, owner).all_facts_usable(), "pending owner validated prior facts");
  pending.rollback();
  const auto after = capture_checked(fixture.all, owner);
  require(owner.sequence() == 4 && owner.has_answer() && owner.snapshot().physical.tables == fixture.initial.tables,
          "abort changed committed data/epoch");
  require(weights(after.inputs()) == weights(before.inputs()) && sources(after.inputs()) == sources(before.inputs()),
          "aborted attempt entered source/input facts");
  require(evidence::revalidate(before, owner).all_facts_usable(), "rollback invalidated unchanged committed interval");
  noop(owner, 1, *fixture.initial.tables[1].begin(), 1);
  require(has(evidence::revalidate(before, owner).boundary, ranking::Reason::stale), "successful no-op did not stale committed epoch");
  auto rebuilt = owner.rebuilt();
  require(rebuilt.snapshot().physical.tables == owner.snapshot().physical.tables &&
              has(evidence::revalidate(before, rebuilt).boundary, ranking::Reason::foreign_owner),
          "rebuilt equal data reused owner identity");
  auto moved = std::move(owner);
  const auto current = capture_checked(fixture.all, moved);
  require(evidence::revalidate(current, moved).all_facts_usable(), "capture is not current on moved owner");
  require(before.inputs().identity().epoch == 4 && before.inputs().denominator() == 4, "old owning evidence mutated after move");
}

void unavailable_and_resources(const BooleanFixture& fixture) {
  auto owner = r::PhysicalRuntime::initialize(lower(fixture.by_label.at("native_s")), fixture.initial);
  const auto off = capture_checked(fixture.all, owner);
  require(has(off.inputs().depth_reasons(), ranking::Reason::disabled) && off.inputs().memory_reasons() == 0,
          "off census was confused with exact source memory facts");
  const auto off_current = evidence::revalidate(off, owner);
  require(off_current.boundary == 0 && off_current.usable(ranking::Policy::tuple_index_slots) &&
              !off_current.usable(ranking::Policy::committed_input_native_depth), "currentness was conflated with disabled workload availability");
  ranking::Request request;
  request.policy = ranking::Policy::committed_input_native_depth;
  auto rejected = ranking::rank(fixture.all, request, off.inputs());
  require(rejected.stop == ranking::Stop::evidence_unavailable && !rejected.result, "missing census silently ranked");
  const auto fallback = rank(fixture.all, request.policy, off.inputs(), ranking::Fallback::height_only);
  require(fallback.effective_policy() == ranking::Policy::height_only && has(fallback.fallback_reasons(), ranking::Reason::disabled),
          "explicit fallback did not retain disabled reason");
  require(fallback.request().policy == request.policy && fallback.request().fallback == ranking::Fallback::height_only,
          "fallback rewrote the requested policy");
  require(fallback.selected().structural_key() == fixture.label_by_key.begin()->first, "fallback ignored deterministic tie key");
  owner.configure_workload_statistics(counters(64, 63));
  const auto empty = capture_checked(fixture.all, owner);
  require(has(empty.inputs().depth_reasons(), ranking::Reason::empty_census), "zero interval borrowed old counts");
  noop(owner, 0, *fixture.initial.tables[0].begin(), 1);
  require(owner.workload_statistics().metadata().complete == 0, "unselected first input unexpectedly completed detail sample");
  const auto sampled = capture_checked(fixture.all, owner);
  require(sampled.inputs().depth_reasons() == 0 && sampled.inputs().denominator() == 1,
          "exact root census incorrectly required a complete detail sample");
  const auto baseline = rank(fixture.all, request.policy, sampled.inputs());
  request.fallback = ranking::Fallback::height_only;
  for (const auto& [field, expected] : std::array<std::pair<unsigned, ranking::Stop>, 5>{{
           {0, ranking::Stop::work_limit}, {1, ranking::Stop::cell_limit}, {2, ranking::Stop::byte_limit},
           {3, ranking::Stop::candidate_limit}, {4, ranking::Stop::bit_limit}}}) {
    auto limited = request;
    if (field == 0) limited.limits.work = 0;
    if (field == 1) limited.limits.cells = 0;
    if (field == 2) limited.limits.payload_bytes = 0;
    if (field == 3) limited.limits.candidates = 2;
    if (field == 4) limited.limits.score_bits = 1;
    const auto attempt = ranking::rank(fixture.all, limited, sampled.inputs());
    require(attempt.stop == expected && !attempt.result, "resource stop used fallback or wrong category");
  }
  auto exact = request;
  exact.limits.work = baseline.usage().work;
  const auto exact_result = ranking::rank(fixture.all, exact, sampled.inputs());
  require(exact_result.stop == ranking::Stop::complete && exact_result.result, "exact public work limit failed");
  require(exact.limits.work != 0, "public rank charged zero work");
  --exact.limits.work;
  const auto short_result = ranking::rank(fixture.all, exact, sampled.inputs());
  require(short_result.stop == ranking::Stop::work_limit && !short_result.result, "one-under public work cap published partial minimum");
  auto timed = request;
  timed.limits.active_time = std::chrono::nanoseconds{0};
  const auto no_time = ranking::rank(fixture.all, timed, sampled.inputs());
  require(no_time.stop == ranking::Stop::time_limit && !no_time.result, "zero active-time cap did not stop transactionally");
  timed.limits.active_time = std::chrono::nanoseconds{-1};
  const auto negative_time = ranking::rank(fixture.all, timed, sampled.inputs());
  require(negative_time.stop == ranking::Stop::invalid_limits && !negative_time.result, "negative active-time cap was accepted");
  evidence::CaptureOptions no_processing;
  no_processing.processing.work = 0;
  const auto no_capture = evidence::capture(fixture.all, owner, no_processing);
  require(no_capture.stop == ranking::Stop::work_limit && !no_capture.evidence && owner.sequence() == 1,
          "capture processing exhaustion published evidence or changed owner");
  evidence::CaptureOptions no_sources;
  no_sources.source_cardinalities = false;
  const auto missing_sources = capture_checked(fixture.all, owner, no_sources);
  require(missing_sources.inputs().depth_reasons() == 0 && missing_sources.inputs().memory_reasons() != 0,
          "optional source omission corrupted independent depth availability");
  for (const bool byte_limit : {false, true}) {
    evidence::CaptureOptions limited_sources;
    if (byte_limit) limited_sources.state_limits.accounted_bytes = 0;
    else limited_sources.state_limits.work = 0;
    const auto incomplete = capture_checked(fixture.all, owner, limited_sources);
    const auto& accounting = incomplete.inputs().capture_accounting();
    require(incomplete.inputs().depth_reasons() == 0 && has(incomplete.inputs().memory_reasons(), ranking::Reason::source_budget_exhausted),
            "C01 source work/byte exhaustion was confused with exact census or C02 processing failure");
    require(accounting.state_requested && accounting.state == ranking::CaptureState::budget_exhausted &&
                accounting.requested_components == 3 && accounting.returned_components <= 3 &&
                incomplete.inputs().source_observations().size() == accounting.returned_components,
            "partial source status/counts were not retained honestly");
    require(accounting.state_rows == 0 && accounting.state_keys == 0, "cardinality-only capture scanned source rows");
    ranking::Request memory_request;
    memory_request.policy = ranking::Policy::tuple_index_slots;
    const auto unavailable = ranking::rank(fixture.all, memory_request, incomplete.inputs());
    require(unavailable.stop == ranking::Stop::evidence_unavailable && !unavailable.result,
            "incomplete source cardinalities produced a memory selection");
    const auto explicit_fallback = rank(fixture.all, memory_request.policy, incomplete.inputs(), ranking::Fallback::height_only);
    require(explicit_fallback.effective_policy() == ranking::Policy::height_only &&
                has(explicit_fallback.fallback_reasons(), ranking::Reason::source_budget_exhausted),
            "explicit C01 source-budget fallback lost its reason");
  }
  evidence::CaptureOptions cardinalities_only;
  cardinalities_only.state_limits.rows = 0;
  cardinalities_only.state_limits.distinct_keys = 0;
  const auto exact_counts = capture_checked(fixture.all, owner, cardinalities_only);
  const auto& accounting = exact_counts.inputs().capture_accounting();
  require(exact_counts.inputs().memory_reasons() == 0 && accounting.state == ranking::CaptureState::available &&
              accounting.requested_components == 3 && accounting.returned_components == 3 &&
              accounting.state_rows == 0 && accounting.state_keys == 0,
          "source cardinality-only capture incorrectly consumed rows/keys or became incomplete");
  require(sources(exact_counts.inputs()) == std::map<std::size_t, std::uint64_t>{{0, 1}, {1, 1}, {2, 1}} &&
              exact_counts.inputs().source_observations().size() == 3, "zero row-budget source cardinalities differ from literal stores");
  for (const auto& observation : exact_counts.inputs().source_observations()) {
    require(observation.state == ranking::CaptureState::available && observation.cardinality == 1,
            "per-source exact cardinality status missing");
  }
  const auto memory_counts = rank(fixture.all, ranking::Policy::tuple_index_slots, exact_counts.inputs());
  require(memory_counts.selected().structural_key() == fixture.by_label.at("native_s").structural_key(),
          "zero row/key scan budgets changed exact source-count memory ranking");
  owner.configure_workload_statistics(counters(2));
  const auto configured = evidence::revalidate(sampled, owner);
  require(configured.boundary == 0 && configured.usable(ranking::Policy::tuple_index_slots) &&
              has(configured.depth, ranking::Reason::interval_changed) && has(configured.depth, ranking::Reason::mode_changed),
          "configuration change reused old interval or staled unchanged data");
  const auto new_interval = capture_checked(fixture.all, owner);
  require(new_interval.inputs().denominator() == 0 && has(new_interval.inputs().depth_reasons(), ranking::Reason::empty_census) &&
              sampled.inputs().denominator() == 1, "configuration replaced prior owning evidence or borrowed old census");
}

void normalized_alias_mapping() {
  Catalog catalog{7, {{"unused", {{"value", ScalarType::int64}}},
                     {"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64}, {"payload", ScalarType::string}}}}};
  auto binding = frontend::bind_sql("SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1", catalog);
  require(std::holds_alternative<frontend::BoundSql>(binding), "independent SQL alias binding failed");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  require(std::holds_alternative<frontend::NormalizedSql>(normalized), "independent SQL alias normalization failed");
  const auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  auto candidates = provider(prove(program.core_catalog, program.core));
  finish(candidates);
  const auto snapshot = candidates.snapshot();
  require(snapshot.candidate_count() != 0 && snapshot.original_proof().height() == 1, "alias fixture lost height-one proof");
  const auto plan = p::lower_normalized(program, snapshot.candidate(0)->tree());
  require(plan.inputs().size() == 2 && plan.source_catalog().tables.size() == 2 && plan.base_routes()[0].empty() && plan.base_routes()[1].size() == 2,
          "normalized physical aliases/source routes differ from literal fixture");
  Database initial;
  initial.tables.resize(2);
  initial.tables[0].insert(Row{std::int64_t{99}});
  initial.tables[1].insert(Row{std::int64_t{1}, std::int64_t{1}, std::string("a")});
  initial.tables[1].insert(Row{std::int64_t{2}, std::int64_t{0}, std::string("b")});
  auto owner = r::PhysicalRuntime::initialize(plan, initial);
  const Relation expected_answer{Row{std::int64_t{1}}};
  require(answers(owner) == expected_answer, "normalized alias result differs from literal filtered self-join");
  owner.configure_workload_statistics(counters());
  noop(owner, 1, *initial.tables[1].begin(), 3);
  for (unsigned i = 0; i < 2; ++i) static_cast<void>(owner.apply({owner.sequence() + 1, TableId{1}, SetOperation::erase,
      {std::int64_t{3}, std::int64_t{1}, std::string("absent")}}));
  noop(owner, 0, *initial.tables[0].begin(), 2);
  const auto observed = capture_checked(snapshot, owner);
  require(weights(observed.inputs()) == std::map<std::size_t, WeightRow>{{0, {2, 0, 0, 2}}, {1, {3, 2, 0, 5}}} &&
              observed.inputs().denominator() == 7, "aliases doubled physical denominator or omitted unused source events");
  // The memory contract requests distinct routed bases only. Unused physical
  // table 0 remains in the input denominator but requires no source scan.
  require(sources(observed.inputs()) == std::map<std::size_t, std::uint64_t>{{1, 2}}, "source cardinality used filtered/core relation rows or scanned unused source");
  const auto ranked = rank(snapshot, ranking::Policy::committed_input_native_depth, observed.inputs());
  for (const auto& score : ranked.scores()) {
    require(score.numerator == "10" && score.denominator == "7" && score.height == 1 && score.depths.size() == 2,
            "literal alias native-depth score is not 10/7");
    for (const auto& depth : score.depths) require(depth.table == TableId{1} && depth.depth == 1, "logical table ID was substituted for physical base");
    require(score.table_depths.size() == 2, "unused source omitted from table-depth diagnostics");
    for (const auto& term : score.table_depths) {
      require(term.depth_sum == (term.table == TableId{1} ? "2" : "0") &&
                  term.contribution == (term.table == TableId{1} ? "10" : "0"), "literal alias/unused-source contribution mismatch");
    }
  }
  const auto memory = rank(snapshot, ranking::Policy::tuple_index_slots, observed.inputs());
  for (const auto& score : memory.scores()) {
    require(score.modeled_plan && score.modeled_plan->normalized(), "alternative memory model lost normalized adapter context");
    for (const auto& input : score.modeled_plan->inputs()) require(input.base == TableId{1}, "candidate-local lowering changed physical alias base");
  }
  for (unsigned field = 0; field < 4; ++field) {
    ranking::Request request;
    request.policy = ranking::Policy::tuple_index_slots;
    request.fallback = ranking::Fallback::height_only;
    if (field == 0) request.limits.lowering_work = 0;
    if (field == 1) request.limits.identity_work = 0;
    if (field == 2) request.limits.binding_replay_work = 0;
    if (field == 3) request.limits.normalization_work = 0;
    const auto stopped = ranking::rank(snapshot, request, observed.inputs());
    require(stopped.stop == ranking::Stop::lowering_limit && !stopped.result,
            "normalized lowering/replay exhaustion was confused with data fallback");
  }
  require(owner.snapshot().physical.tables == initial.tables && answers(owner) == expected_answer,
          "alias ranking/no-op workload changed sources or literal result");
  const auto foreign = evidence::capture(snapshot, r::PhysicalRuntime::initialize(
      p::lower_tree(program.core_catalog, program.core, snapshot.candidate(0)->tree()), Database{std::vector<Relation>(program.core_catalog.tables.size())}));
  // A core-only owner is legitimately a distinct physical binding even though
  // its Catalog/Query proof is the same. Its own capture must never masquerade
  // as the normalized owner's source map.
  if (foreign.evidence) require(foreign.evidence->inputs().identity().owner != observed.inputs().identity().owner,
                                "independent core owner reused normalized owner stamp");
}

void statistical_ties_and_binding(const BooleanFixture& fixture) {
  auto owner = r::PhysicalRuntime::initialize(lower(fixture.by_label.at("native_s")), fixture.initial);
  owner.configure_workload_statistics(counters());
  for (std::size_t table = 0; table < 3; ++table) noop(owner, table, *fixture.initial.tables[table].begin(), 1);
  const auto observed = capture_checked(fixture.all, owner);
  const auto tied = rank(fixture.all, ranking::Policy::committed_input_native_depth, observed.inputs());
  const auto& x = fixture.by_label.at("generalized_x").structural_key();
  const auto& y = fixture.by_label.at("generalized_y").structural_key();
  require(tied.selected().structural_key() == std::min(x, y), "equal statistical score ignored full structural-key tie-break");
  for (const auto& score : tied.scores()) {
    const auto label = fixture.label_by_key.at(std::string(score.structural_key));
    require(score.numerator == (label == "native_s" ? "5" : "4") && score.denominator == "3", "literal equal-weight depth table mismatch");
  }
  const auto prefix = rank(fixture.partial, ranking::Policy::committed_input_native_depth, observed.inputs());
  require(prefix.scores().size() == 1 && !prefix.snapshot().family_exhausted() &&
              prefix.selected().structural_key() == fixture.partial.candidate(0)->structural_key(),
          "ranker advanced the provider or imported a missing candidate");
  auto catalog = fixture.document.catalog;
  ++catalog.version;
  auto other_provider = provider(prove(catalog, fixture.document.query));
  finish(other_provider);
  ranking::Request request;
  request.policy = ranking::Policy::committed_input_native_depth;
  request.fallback = ranking::Fallback::height_only;
  const auto mismatch = ranking::rank(other_provider.snapshot(), request, observed.inputs());
  require(mismatch.stop == ranking::Stop::binding_mismatch && !mismatch.result, "different catalog version reused evidence or fell back");
  const auto capture_mismatch = evidence::capture(other_provider.snapshot(), owner);
  require(capture_mismatch.stop == ranking::Stop::binding_mismatch && !capture_mismatch.evidence, "runtime adapter ignored exact original binding");
  auto moved_from = fixture.all;
  const auto retained = std::move(moved_from);
  require(retained.valid() && !moved_from.valid(), "snapshot move contract changed");
  const auto invalid = ranking::rank(moved_from);
  require(invalid.stop == ranking::Stop::invalid_handle && !invalid.result, "moved-from snapshot manufactured ranking authority");
}

void mode_reset_drop(const BooleanFixture& fixture) {
  auto plan = lower(fixture.by_label.at("native_s"));
  r::DeltaOptions options;
  options.mode = r::DeltaMode::maintenance;
  auto owner = r::DeltaRuntime::initialize(plan, fixture.initial, options);
  owner.configure_workload_statistics(counters());
  auto epoch = owner.apply({1, TableId{0}, SetOperation::insert, *fixture.initial.tables[0].begin()});
  epoch.discard();
  const auto before = capture_checked(fixture.all, owner);
  require(before.inputs().identity().modes.delta_owner && evidence::revalidate(before, owner).all_facts_usable(), "Delta mode identity unavailable");
  static_cast<void>(owner.set_mode(r::DeltaMode::delta));
  const auto changed_mode = evidence::revalidate(before, owner);
  require(owner.sequence() == 1 && has(changed_mode.depth, ranking::Reason::mode_changed),
          "mode rotation reused prior workload facts");
  require(changed_mode.boundary == 0 && changed_mode.usable(ranking::Policy::tuple_index_slots),
          "mode rotation staled unchanged source cardinalities");
  const auto rotated = capture_checked(fixture.all, owner);
  require(has(rotated.inputs().depth_reasons(), ranking::Reason::empty_census) && rotated.inputs().memory_reasons() == 0,
          "mode interval reset destroyed current data facts or reused previous census");
  auto session = r::QuerySession::create_typed(plan, fixture.initial);
  session->configure_workload_statistics(counters());
  const auto live = capture_checked(fixture.all, *session);
  require(live.session_context().has_value(), "session evidence lost actual guarded context");
  session->drop();
  const auto released = capture_checked(fixture.all, *session);
  require(has(released.inputs().depth_reasons(), ranking::Reason::released) &&
              has(released.inputs().memory_reasons(), ranking::Reason::released) && !released.captured().has_value(),
          "dropped session fabricated retained live facts");
  require(has(evidence::revalidate(live, *session).boundary, ranking::Reason::released), "drop revalidated live evidence");
  const auto fallback = rank(fixture.all, ranking::Policy::tuple_index_slots, released.inputs(), ranking::Fallback::height_only);
  require(fallback.effective_policy() == ranking::Policy::height_only && has(fallback.fallback_reasons(), ranking::Reason::released),
          "released session fallback lost its reason");
  require(live.session_context()->metadata().sequence() == 0 && !live.session_context()->status().pending_sequence,
          "prior owning session context mutated after drop");
  const auto historical = rank(fixture.all, ranking::Policy::tuple_index_slots, live.inputs());
  require(historical.selected().structural_key() == fixture.by_label.at("native_s").structural_key(),
          "pure as-of ranking lost its owning source facts after session drop");
}

void decimal_and_repeated_output_payload() {
  const auto value = Decimal::parse("12345678901234567890123456789012345678");
  const auto predicate = Decimal::parse("87654321098765432109876543210987654321");
  const Catalog catalog{1, {{"decimal_rows", {{"x", ScalarType::decimal}, {"filter", ScalarType::decimal}}}}};
  const Query query{{{"x", ScalarType::decimal}},
      {{"r", TableId{0}, {VariableId{0}, Value{predicate}}}},
      {{VariableId{0}, "first"}, {VariableId{0}, "again"}}, false};
  auto candidates = provider(prove(catalog, query));
  finish(candidates);
  const auto snapshot = candidates.snapshot();
  require(snapshot.candidate_count() == 1 && snapshot.original_proof().height() == 1, "decimal fixture lost unary optimum");
  const auto plan = lower(*snapshot.candidate(0));
  Database initial;
  initial.tables.resize(1);
  initial.tables[0].insert(Row{value, predicate});
  initial.tables[0].insert(Row{value, Decimal::parse("0")});
  auto owner = r::PhysicalRuntime::initialize(plan, initial);
  const Relation literal{Row{value, value}};
  require(answers(owner) == literal, "decimal constant/repeated head differs from literal row result");
  const auto facts = capture_checked(snapshot, owner);
  require(sources(facts.inputs()) == std::map<std::size_t, std::uint64_t>{{0, 2}}, "decimal source cardinality substituted filtered membership");
  const auto memory = rank(snapshot, ranking::Policy::tuple_index_slots, facts.inputs());
  require(memory.scores().size() == 1 && memory.scores()[0].slots == "13", "literal decimal unary population bound is not 13");
  const auto modeled = PhysicalPlan::from_compiled(*memory.scores()[0].modeled_plan);
  require(modeled.result_layout().fields().size() == 2 && modeled.result_layout().fields()[0].variable == modeled.result_layout().fields()[1].variable,
          "modeled repeated output layout lost its equality");
  bool rejected_unequal_repeat = false;
  try {
    static_cast<void>(modeled.result_layout().tuple(Row{value, predicate}));
  } catch (const Error& error) {
    rejected_unequal_repeat = error.code() == "invalid_tuple";
  }
  require(rejected_unequal_repeat, "retained repeated layout lacks its actual private equality check");
  ranking::Request request;
  request.policy = ranking::Policy::tuple_index_slots;
  request.fallback = ranking::Fallback::height_only;
  request.limits.payload_bytes = memory.usage().payload_bytes;
  const auto exact = ranking::rank(snapshot, request, facts.inputs());
  require(exact.stop == ranking::Stop::complete && exact.result && exact.result->scores()[0].slots == "13",
          "exact decimal/repeated-layout modeled payload cap failed");
  require(request.limits.payload_bytes != 0, "decimal model charged no retained payload");
  --request.limits.payload_bytes;
  const auto short_budget = ranking::rank(snapshot, request, facts.inputs());
  require(short_budget.stop == ranking::Stop::byte_limit && !short_budget.result && answers(owner) == literal,
          "decimal/repeated-layout resource failure selected a partial result or changed semantics");
}
}  // namespace

int main(int argc, char** argv) {
  try {
    require(argc == 2, "usage: ranking_public_independent_test REPOSITORY_ROOT");
    const auto fixture = boolean_fixture(argv[1]);
    candidate_semantics_and_height(fixture);
    hot_reversal_and_memory(fixture);
    changed_noop_abort_and_freshness(fixture);
    unavailable_and_resources(fixture);
    statistical_ties_and_binding(fixture);
    normalized_alias_mapping();
    mode_reset_drop(fixture);
    decimal_and_repeated_output_payload();
    std::cout << "independent public ranking groups=8 boolean_candidates=3 hot_inputs=200 slot_scores=24,32,32 decimal_repeated_slots=13\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "independent public ranking failure: " << error.what() << '\n';
    return 1;
  }
}

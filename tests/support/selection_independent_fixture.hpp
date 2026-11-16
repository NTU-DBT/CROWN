#pragma once

// Literal row/shape lineage: the reviewer's accepted C02 independent public
// fixtures. No C05 production fixture, score helper or private factory is used.
#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"
#include "crown/io/tree.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/search.hpp"
#include "crown/planner/selection.hpp"
#include "crown/runtime/selection.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace c05_independent {
using namespace crown;
namespace p = crown::planner;
namespace r = crown::runtime;
namespace rank = crown::planner::ranking;
namespace capture = crown::runtime::ranking;
namespace s = crown::planner::selection;
namespace current = crown::runtime::selection;

inline void check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
inline std::string read(const std::filesystem::path& path) {
  std::ifstream input(path);
  check(input.good(), "independent fixture file is unreadable");
  return {std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
}
template<class Text> inline std::string caller_text(const Text& text) {
  return std::string{text.data(), text.size()};
}
inline p::VerifiedOptimum prove(const Catalog& catalog, const Query& query) {
  p::SearchOptions options;
  options.limits.producer.work = 100'000'000;
  options.limits.replay.work = 100'000'000;
  options.limits.logical_depth = 64;
  auto search = p::ExactSearch::create(catalog, query, options);
  for (unsigned step = 0; step < 2'000; ++step) {
    const auto next = search.advance({100'000, {}});
    if (next.progress.result == p::ResultKind::verified_optimum) {
      const auto result = search.optimum();
      check(result && result->valid(), "P06 failed to publish its real checked proof");
      return *result;
    }
    check(next.stopped_for == p::StopReason::quantum_work ||
          next.stopped_for == p::StopReason::quantum_time, "finite P06 search failed");
  }
  throw std::runtime_error("finite P06 call guard exhausted");
}
inline p::CandidateProvider provider(p::VerifiedOptimum proof) {
  p::CandidateLimits limits;
  limits.enumeration.work = 100'000'000;
  limits.logical_depth = 64;
  limits.records = 1'000'000;
  limits.cells = 10'000'000;
  limits.retained_candidates = 32;
  return p::CandidateProvider::create(std::move(proof), {}, limits);
}
inline void finish(p::CandidateProvider& value) {
  for (unsigned step = 0; step < 2'000; ++step) {
    const auto next = value.advance({100'000, {}});
    if (next.stopped_for == p::CandidateStop::exhausted) return;
    check(next.stopped_for == p::CandidateStop::candidate_ready ||
          next.stopped_for == p::CandidateStop::quantum_work ||
          next.stopped_for == p::CandidateStop::quantum_time, "finite P07 family failed");
  }
  throw std::runtime_error("finite P07 call guard exhausted");
}
inline p::CandidateSnapshot candidates(const Catalog& catalog, const Query& query) {
  auto value = provider(prove(catalog, query));
  finish(value);
  return value.snapshot();
}
inline std::string shape_node(const FreeConnexTree& tree, NodeId id) {
  const auto& node = tree.nodes.at(id.value);
  std::string out = node.kind == NodeKind::native ? "N" : "G";
  if (node.occurrence) out += std::to_string(*node.occurrence);
  out += ':';
  for (auto variable : node.scope) out += std::to_string(variable.value) + ',';
  std::vector<std::string> children;
  for (auto child : node.children) children.push_back(shape_node(tree, child));
  std::sort(children.begin(), children.end());
  out += '[';
  for (const auto& child : children) out += '{' + child + '}';
  return out + ']';
}
inline std::string shape(const FreeConnexTree& tree) {
  return tree.root ? shape_node(tree, *tree.root) : "empty";
}
// Aggregate copies deep-copy DTO/maps/rows while typed proof-prefix handles share
// their real immutable controls. Copied map keys are ordinary independent strings.
struct BooleanFixture {
  Document document;
  p::CandidateSnapshot all, partial, empty;
  std::map<std::string, std::string> label_by_key;
  std::map<std::string, p::MinimumHeightCandidate> by_label;
  Database initial;
};
inline BooleanFixture boolean_fixture(const std::filesystem::path& root) {
  auto document = io::read_document(read(root / "tests/candidates/queries/boolean_rst.cq.json"));
  const auto proof = prove(document.catalog, document.query);
  check(proof.height() == 2, "literal Boolean optimum differs from two");
  auto value = provider(proof);
  const auto empty = value.snapshot();
  for (unsigned i = 0; value.candidate_count() == 0 && i < 2'000; ++i)
    static_cast<void>(value.advance({100'000, {}}));
  check(value.candidate_count() == 1, "P07 did not stop at its first candidate");
  const auto partial = value.snapshot();
  finish(value);
  const auto all = value.snapshot();
  check(all.family_exhausted() && all.candidate_count() == 3 && !partial.family_exhausted(),
        "literal retained family is not three plus its immutable prefix");
  std::map<std::string, std::string> expected;
  for (const auto* label : {"native_s", "generalized_x", "generalized_y"}) {
    const auto tree = io::read_tree(read(root / (std::string("tests/candidates/trees/boolean_rst_") + label + "_root.tree.json")),
                                    document.catalog, document.query);
    const auto validated = p::validate_tree(document.catalog, document.query, tree);
    check(validated.valid && validated.native_height == 2, "literal tree is not valid height two");
    check(expected.emplace(shape(tree), label).second, "literal shapes collide");
  }
  BooleanFixture result{std::move(document), all, partial, empty, {}, {}, {}};
  for (std::size_t i = 0; i < all.candidate_count(); ++i) {
    const auto member = all.candidate(i);
    check(member && member->valid() && member->height() == 2, "actual family member is invalid");
    const auto found = expected.find(shape(member->tree()));
    check(found != expected.end(), "unexpected candidate outside literal family");
    check(result.label_by_key.emplace(member->structural_key(), found->second).second, "duplicate candidate key");
    check(result.by_label.emplace(found->second, *member).second, "duplicate candidate geometry");
  }
  result.initial.tables = {Relation{Row{std::string("x")}},
      Relation{Row{std::string("x"), std::string("y")}}, Relation{Row{std::string("y")}}};
  return result;
}
inline PhysicalPlan lower(const p::MinimumHeightCandidate& member, const PhysicalOptions& options = {}) {
  return p::lower_tree(member.catalog(), member.query(), member.tree(), options);
}
inline r::workload::Options counters() {
  r::workload::Options result;
  result.mode = r::workload::Mode::counters;
  return result;
}
inline void noop(r::PhysicalRuntime& owner, std::size_t table, const Row& row, unsigned count) {
  for (unsigned i = 0; i < count; ++i)
    check(!owner.apply({owner.sequence() + 1, TableId{table}, SetOperation::insert, row}).input.physical_changed,
          "literal duplicate insert changed its source");
}
inline void hot(r::PhysicalRuntime& owner, const BooleanFixture& fixture, bool hot_r = true) {
  owner.configure_workload_statistics(counters());
  noop(owner, 0, *fixture.initial.tables[0].begin(), hot_r ? 90U : 5U);
  noop(owner, 1, *fixture.initial.tables[1].begin(), 5);
  noop(owner, 2, *fixture.initial.tables[2].begin(), hot_r ? 5U : 90U);
}
inline Relation answers(const r::PhysicalRuntime& owner) {
  auto cursor = owner.results();
  Relation result;
  while (const auto row = cursor.next()) result.insert(crown::storage::export_row(row->values()));
  return result;
}
template<class Runtime>
capture::RuntimeEvidence capture_checked(const p::CandidateSnapshot& snapshot, const Runtime& owner,
                                        const capture::CaptureOptions& options = {}) {
  const auto result = capture::capture(snapshot, owner, options);
  check(result.stop == rank::Stop::complete && result.evidence.has_value(), "real owner capture failed");
  return *result.evidence;
}
// Returned reference borrows the Attempt. Copy the typed handle to retain it.
inline const s::Selection& complete(const s::Attempt& result) {
  check(result.stop == s::Stop::complete && result.selection.has_value(), "C05 did not publish a complete pure result");
  return *result.selection;
}
// Returned reference borrows the Attempt; it does not extend temporary lifetime.
inline const current::CurrentSelection& complete(const current::Attempt& result) {
  check(result.stop == s::Stop::complete && result.selection.has_value(), "C05 did not publish a complete current result");
  return *result.selection;
}
inline bool has(rank::Reasons value, rank::Reason flag) {
  return (value & rank::reason(flag)) != 0;
}
inline s::Request height() {
  s::Request result;
  result.policy = s::Policy::height_only;
  return result;
}
inline s::Request depth() {
  s::Request result;
  result.fallback = rank::Fallback::require_evidence;
  return result;
}
inline s::Request slots() {
  auto result = depth();
  result.policy = s::Policy::tuple_index_slots;
  return result;
}
inline std::string label(const BooleanFixture& fixture, const s::Selection& result) {
  return fixture.label_by_key.at(result.selected().structural_key());
}
inline const rank::Result& assessment(const s::Selection& result, s::AssessmentPurpose purpose) {
  const auto found = std::find_if(result.assessments().begin(), result.assessments().end(),
      [purpose](const auto& value) { return value.purpose == purpose; });
  check(found != result.assessments().end(), "required complete assessment is missing");
  return found->result;
}
inline void literal_depth(const BooleanFixture& fixture, const rank::Result& result, bool hot_r = true) {
  const std::map<std::string, std::string> expected = hot_r
      ? std::map<std::string, std::string>{{"native_s", "195"}, {"generalized_x", "105"}, {"generalized_y", "190"}}
      : std::map<std::string, std::string>{{"native_s", "195"}, {"generalized_x", "190"}, {"generalized_y", "105"}};
  check(result.scores().size() == 3 && result.effective_policy() == rank::Policy::committed_input_native_depth,
        "depth assessment omitted the complete retained family");
  for (const auto& score : result.scores())
    check(score.height == 2 && score.numerator == expected.at(fixture.label_by_key.at(caller_text(score.structural_key))) &&
          score.denominator == "100", "literal depth numerator or denominator changed");
}
inline void literal_slots(const BooleanFixture& fixture, const rank::Result& result) {
  check(result.scores().size() == 3 && result.effective_policy() == rank::Policy::tuple_index_slots,
        "slot assessment omitted the complete retained family");
  for (const auto& score : result.scores())
    check(score.slots == (fixture.label_by_key.at(caller_text(score.structural_key)) == "native_s" ? "24" : "32") &&
          score.modeled_plan.has_value(), "literal candidate-local slot proxy changed");
}
// tie tuples borrow fields only through these immediate comparisons; arrays stay owned
// by snapshots. Component capacity bytes are not whole-query allocator statistics.
inline bool same_workload(const r::workload::Snapshot& a, const r::workload::Snapshot& b) {
  const auto metadata = [](const r::workload::Metadata& x) {
    return std::tie(x.attempts,x.committed,x.aborted,x.selected,x.complete,x.aborted_selected,
        x.truncated,x.committed_truncated,x.guards,x.detail_actions,x.cleared_cells,x.merged_cells,
        x.saturated,x.invalid_descriptor,x.protocol_error,x.ordinal_exhausted);
  };
  const auto stamp = [](const r::workload::Stamp& x) {
    return std::tie(x.owner.value,x.committed_epoch,x.interval_start_epoch,x.reset_generation,
        x.configuration_generation,x.segment,x.format_version,x.reset_saturated,x.configuration_saturated,x.segment_saturated);
  };
  const auto memory = [](const r::workload::Memory& x) {
    return std::tie(x.object_bytes,x.descriptors_bytes,x.committed_bytes,x.attempt_bytes,x.previous_bytes,
        x.retained_payload_bytes,x.routes_bytes);
  };
  return a.plan().physical_sha256() == b.plan().physical_sha256() && stamp(a.stamp()) == stamp(b.stamp()) &&
      a.options() == b.options() && a.modes() == b.modes() && a.previous_modes() == b.previous_modes() &&
      std::ranges::equal(a.descriptors(),b.descriptors()) && std::ranges::equal(a.cells(),b.cells()) &&
      std::ranges::equal(a.previous_cells(),b.previous_cells()) && metadata(a.metadata()) == metadata(b.metadata()) &&
      metadata(a.previous_metadata()) == metadata(b.previous_metadata()) && memory(a.memory()) == memory(b.memory()) &&
      a.pending() == b.pending() && a.has_previous() == b.has_previous() && a.replaced_history() == b.replaced_history() &&
      a.previous_interval_start_epoch() == b.previous_interval_start_epoch() &&
      a.previous_interval_end_epoch() == b.previous_interval_end_epoch() && a.detail_availability() == b.detail_availability();
}
inline p::VerifiedOptimum replay(const Catalog& catalog, const Query& query, p::HeightCertificate certificate) {
  p::ReplayOptions limits;
  limits.limits.work = 100'000'000;
  auto value = p::CertificateReplay::create(catalog, query, std::move(certificate), limits);
  for (unsigned i = 0; i < 2'000; ++i) {
    const auto next = value.advance({100'000, {}});
    if (next.stopped_for == p::StopReason::complete) {
      const auto checked = value.checked();
      check(checked && checked->valid() && checked->optimum(), "real replay did not verify the supplied raw-tree witness");
      return *checked->optimum();
    }
    check(next.stopped_for == p::StopReason::quantum_work || next.stopped_for == p::StopReason::quantum_time,
          "real replay rejected the equivalent raw-tree witness");
  }
  throw std::runtime_error("finite certificate replay guard exhausted");
}
} // namespace c05_independent

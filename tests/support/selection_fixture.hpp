#pragma once

#include "ranking_fixture.hpp"
#include "crown/runtime/selection.hpp"
#include "crown/io/physical.hpp"
#include <algorithm>
#include <array>
#include <sstream>

namespace c05_test {
using namespace crown;
using c02_test::check;
using c02_test::Fixture;
namespace ps = planner::selection;
namespace rs = runtime::selection;
namespace pr = planner::ranking;
namespace rr = runtime::ranking;
inline ps::Selection complete(ps::Attempt value) {
  if (!value.selection || value.stop != ps::Stop::complete) {
    throw std::runtime_error("C05 pure stop=" + std::to_string(static_cast<unsigned>(value.stop)) +
        " stage=" + std::to_string(static_cast<unsigned>(value.stage)) +
        " resource=" + std::to_string(static_cast<unsigned>(value.resource)));
  }
  return *value.selection;
}
inline rs::CurrentSelection complete(rs::Attempt value) {
  if (!value.selection || value.stop != ps::Stop::complete) {
    throw std::runtime_error("C05 current stop=" + std::to_string(static_cast<unsigned>(value.stop)) +
        " stage=" + std::to_string(static_cast<unsigned>(value.stage)) +
        " resource=" + std::to_string(static_cast<unsigned>(value.resource)));
  }
  return *value.selection;
}
// Exact root inputs survive sparse/zero-detail sampling; root slab work remains.
inline runtime::workload::Options counters() {
  runtime::workload::Options options; options.mode = runtime::workload::Mode::counters;
  options.period = 64; options.detail_budget = 0; return options;
}
inline void heat(runtime::PhysicalRuntime& owner, const Fixture& f, bool hot_r = true) {
  owner.configure_workload_statistics(counters());
  for (std::size_t table = 0; table < 3; ++table) {
    const unsigned n = table == (hot_r ? 0U : 2U) ? 90U : 5U;
    for (unsigned i = 0; i < n; ++i)
      static_cast<void>(owner.apply({owner.sequence() + 1, TableId{table}, SetOperation::insert, *f.database.tables[table].begin()}));
  }
}
inline rr::RuntimeEvidence capture(const planner::CandidateSnapshot& snapshot, const runtime::PhysicalRuntime& owner,
                                  rr::CaptureOptions options = {}) {
  auto result = rr::capture(snapshot, owner, options);
  check(result.stop == pr::Stop::complete && result.evidence.has_value(), "C05 fixture actual capture failed");
  return *result.evidence;
}
// Explicit ordinary row export/set construction, separate from native cursor ownership.
inline Relation answers(const runtime::PhysicalRuntime& owner) {
  auto cursor = owner.results(); Relation result;
  while (const auto tuple = cursor.next()) result.insert(crown::storage::export_row(tuple->values()));
  return result;
}
inline ps::Request request(ps::Policy policy) {
  ps::Request out; out.policy = policy; return out;
}
inline const pr::Result& assessment(const ps::Selection& selected, pr::Policy policy) {
  for (const auto& item : selected.assessments()) if (item.result.request().policy == policy) return item.result;
  throw std::runtime_error("C05 missing complete assessment");
}
inline void depth_oracle(const pr::Result& result, bool hot_r = true) {
  const std::array<std::string, 3> expected = hot_r ? std::array<std::string, 3>{"195", "105", "190"} :
      std::array<std::string, 3>{"195", "190", "105"};
  check(result.scores().size() == 3, "C05 depth retained set incomplete");
  for (const auto& score : result.scores()) {
    check(score.height == 2 && score.denominator == "100" &&
        score.numerator == expected[static_cast<std::size_t>(c02_test::shape(score.candidate.tree()))], "C05 literal depth oracle");
    check(score.depths.size() == 3 && score.table_depths.size() == 3, "C05 missing depth reproduction terms");
  }
}
inline void slot_oracle(const pr::Result& result) {
  check(result.scores().size() == 3, "C05 slot retained set incomplete");
  for (const auto& score : result.scores()) {
    const bool native = c02_test::shape(score.candidate.tree()) == 0;
    check(score.slots == (native ? "24" : "32") && score.modeled_plan.has_value(), "C05 literal slot oracle");
    check(score.slot_terms.size() == (native ? 12U : 14U) && score.populations.size() == score.modeled_plan->nodes().size(),
        "C05 missing complete slot reproduction terms");
  }
}
inline void valid_plan(const ps::Selection& selected, const Database& database) {
  const auto owner = runtime::PhysicalRuntime::initialize(selected.plan(), database);
  check(owner.has_answer(), "C05 selected plan changed Boolean answer");
  check(selected.selected().height() == selected.snapshot().original_proof().height() &&
      selected.plan().guarantee().height_status == "valid_upper_bound", "C05 proof authority/profile changed");
}
inline planner::CandidateSnapshot prefix(const planner::VerifiedOptimum& proof) {
  auto provider = planner::CandidateProvider::create(proof);
  for (std::size_t n = 0; n < 100'000 && !provider.candidate_count(); ++n)
    static_cast<void>(provider.advance({1000, {}}));
  check(provider.candidate_count() == 1, "C05 finite prefix admission failed"); return provider.snapshot();
}
} // namespace c05_test

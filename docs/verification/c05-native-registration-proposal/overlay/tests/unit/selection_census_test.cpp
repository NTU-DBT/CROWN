#include "selection_fixture.hpp"
#include "runtime_probe.hpp"
#include <iostream>

int main() { try {
  using namespace c05_test;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  runtime::DeltaOptions options; options.mode = runtime::DeltaMode::maintenance;
  auto owner = runtime::DeltaRuntime::initialize(plan, f.database, options);
  owner.configure_workload_statistics(counters());
  static_cast<void>(owner.apply({1, TableId{0}, SetOperation::insert, *f.database.tables[0].begin()}));
  runtime::RuntimeTestProbe::seed_c01_report_saturation(owner);
  const ps::Source source = ps::PhysicalBasis{plan};
  const auto fallback = complete(rs::select_current(snapshot, source, owner));
  check(fallback.selection().effective_policy() == pr::Policy::height_only &&
      (fallback.selection().fallback_reasons() & pr::reason(pr::Reason::root_saturated)) &&
      (fallback.selection().fallback_reasons() & pr::reason(pr::Reason::interval_saturated)),
      "C05 actual root/interval saturation was used as exact depth");
  auto required = request(ps::Policy::committed_input_native_depth); required.fallback = pr::Fallback::require_evidence;
  const auto rejected = rs::select_current(snapshot, source, owner, required);
  check(!rejected.selection && rejected.stop == ps::Stop::evidence_unavailable, "C05 saturation requirement fell back");
  const auto memory = complete(rs::select_current(snapshot, source, owner, request(ps::Policy::tuple_index_slots)));
  slot_oracle(assessment(memory.selection(), pr::Policy::tuple_index_slots));
  auto constrained = request(ps::Policy::committed_input_native_depth); constrained.constraint = ps::TupleIndexSlotLimit{"24"};
  const auto retained = complete(rs::select_current(snapshot, source, owner, constrained));
  check(retained.selection().effective_policy() == pr::Policy::height_only &&
      retained.selection().assessments().size() == 2 && c02_test::shape(retained.selection().selected().tree()) == 0,
      "C05 saturated depth bypassed a complete source constraint");
  // The existing probe sets several real counters/generations together. This
  // verifies conservative actual-owner handling, not independent flag causes.
  std::cout << "C05 actual-owner simultaneous saturation rejects depth and preserves exact source-only slot constraints\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

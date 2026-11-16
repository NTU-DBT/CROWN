#include "selection_fixture.hpp"
#include <iostream>

int main() { try {
  using namespace c05_test;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  const ps::Source source = ps::PhysicalBasis{plan};
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database);
  auto memory = request(ps::Policy::tuple_index_slots);
  const auto off = complete(rs::select_current(snapshot, source, owner));
  check(off.selection().effective_policy() == pr::Policy::height_only && off.selection().fallback_reasons() & pr::reason(pr::Reason::disabled),
      "C05 off collection did not disclose primary fallback");
  const auto state_only = complete(rs::select_current(snapshot, source, owner, memory));
  slot_oracle(assessment(state_only.selection(), pr::Policy::tuple_index_slots));
  auto required = request(ps::Policy::committed_input_native_depth); required.fallback = pr::Fallback::require_evidence;
  const auto unavailable = rs::select_current(snapshot, source, owner, required);
  check(!unavailable.selection && unavailable.stop == ps::Stop::evidence_unavailable, "C05 require-evidence selected fallback");
  heat(owner, f); const auto old = complete(rs::select_current(snapshot, source, owner));
  depth_oracle(assessment(old.selection(), pr::Policy::committed_input_native_depth));
  auto pending = owner.prepare({owner.sequence() + 1, TableId{0}, SetOperation::insert, Row{std::int64_t{2}}});
  auto height = request(ps::Policy::height_only);
  const auto blocked = rs::select_current(snapshot, source, owner, height);
  check(!blocked.selection && blocked.stop == ps::Stop::boundary_unavailable && blocked.reasons & pr::reason(pr::Reason::pending),
      "C05 current height bypassed private pending boundary");
  pending.rollback();
  const auto same = complete(rs::select_current(snapshot, source, owner));
  check(same.capture().inputs().identity().epoch == old.capture().inputs().identity().epoch &&
      same.capture().captured()->workload().metadata().aborted > old.capture().captured()->workload().metadata().aborted,
      "C05 fresh context omitted abort while committed epoch was unchanged");
  owner.reset_workload_statistics();
  const auto reset = complete(rs::select_current(snapshot, source, owner));
  check(reset.capture().inputs().identity().reset != old.capture().inputs().identity().reset &&
      reset.selection().fallback_reasons() & pr::reason(pr::Reason::empty_census), "C05 reset interval reused");
  const auto preserved = complete(ps::select(snapshot, source, {}, old.capture().inputs()));
  depth_oracle(assessment(preserved, pr::Policy::committed_input_native_depth));
  auto changed_config = counters(); changed_config.offset = 1; changed_config.period = 2; owner.configure_workload_statistics(changed_config);
  const auto config = complete(rs::select_current(snapshot, source, owner, memory));
  check(config.capture().inputs().identity().configuration != reset.capture().inputs().identity().configuration &&
      config.selection().effective_policy() == pr::Policy::tuple_index_slots, "C05 configuration invalidated current source cardinality");
  auto rebuilt = owner.rebuilt(); const auto different = complete(rs::select_current(snapshot, source, rebuilt, memory));
  check(different.capture().inputs().identity().owner != config.capture().inputs().identity().owner, "C05 foreign owner identity reused");
  runtime::statistics::Limits state_limits; state_limits.work = 0;
  const auto optional = complete(rs::select_current(snapshot, source, owner, memory, state_limits));
  check(optional.selection().effective_policy() == pr::Policy::height_only &&
      optional.selection().fallback_reasons() & pr::reason(pr::Reason::source_budget_exhausted), "C05 source budget fallback reason lost");
  auto mandatory = memory; mandatory.constraint = ps::TupleIndexSlotLimit{"32"};
  const auto no_constraint = rs::select_current(snapshot, source, owner, mandatory, state_limits);
  check(!no_constraint.selection && no_constraint.stop == ps::Stop::evidence_unavailable, "C05 mandatory constraint used unavailable sources");
  state_limits = {}; state_limits.rows = 0; state_limits.distinct_keys = 0;
  const auto cardinality = complete(rs::select_current(snapshot, source, owner, mandatory, state_limits));
  slot_oracle(assessment(cardinality.selection(), pr::Policy::tuple_index_slots));
  mandatory.limits.aggregate.work = 0;
  const auto processing = rs::select_current(snapshot, source, owner, mandatory);
  check(!processing.selection && processing.stop == ps::Stop::resource_limit, "C05 processing exhaustion took fallback");
  runtime::DeltaOptions delta_options; delta_options.mode = runtime::DeltaMode::maintenance;
  auto delta = runtime::DeltaRuntime::initialize(plan, f.database, delta_options);
  delta.configure_workload_statistics(counters());
  static_cast<void>(delta.apply({1, TableId{0}, SetOperation::insert, *f.database.tables[0].begin()}));
  const auto delta_selected = complete(rs::select_current(snapshot, source, delta));
  check(delta_selected.capture().inputs().identity().modes.delta_owner &&
      delta_selected.capture().inputs().identity().owner == delta.owner().value, "C05 actual Delta mode/owner missing");
  runtime::SessionOptions session_options; session_options.delta.mode = runtime::DeltaMode::maintenance;
  auto session = runtime::QuerySession::create(plan, f.database, std::make_unique<std::istringstream>(""), session_options);
  const auto session_selected = complete(rs::select_current(snapshot, source, *session, memory));
  check(session_selected.capture().session_context().has_value() &&
      session_selected.capture().session_context()->metadata().owner().value == session_selected.capture().inputs().identity().owner,
      "C05 actual session context not retained");
  session->stop(); const auto stopped = complete(rs::select_current(snapshot, source, *session, memory));
  check(stopped.capture().session_context()->status().state == runtime::SessionState::stopped, "C05 stopped retained runtime rejected");
  session->drop(); const auto dropped = rs::select_current(snapshot, source, *session, height);
  check(!dropped.selection && dropped.stop == ps::Stop::boundary_unavailable && dropped.reasons & pr::reason(pr::Reason::released),
      "C05 dropped current height accepted");
  check(session_selected.selection().plan().physical_sha256() == stopped.selection().plan().physical_sha256(),
      "C05 old session result failed after drop");
  std::cout << "C05 current/as-of, pending/abort/reset/configuration/source budget and actual Physical/Delta/Session boundaries passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

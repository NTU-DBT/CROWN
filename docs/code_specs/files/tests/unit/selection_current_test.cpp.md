# `tests/unit/selection_current_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_current_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1dbee3972947a286d5ae077921dd2b40795fb63405710986c12bd7b15db70133`. 77 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../tests/unit/selection_current_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 4–77](../../../../../tests/unit/selection_current_test.cpp#L4) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, planner::lower_tree, candidate; guard check(off.selection().effective_policy() == pr::Policy::height_only && off.selection().fallback_rea…; returns 1; growth insert, make_unique · [reviewed contract](#b0002) |

## B0001

[Lines 1–3](../../../../../tests/unit/selection_current_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L3:sha256:e6ca5670d869f671aa91e8e477ee91b4a88da625b296bfc104bf14c177fb2b77
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_current_test.cpp: include "selection_fixture.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 4–77](../../../../../tests/unit/selection_current_test.cpp#L4); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pure historical selection against fresh current-owner boundary rules. |
| inputs / outputs | Exercises disabled, pending, rollback, reset, rebuilt-owner, DeltaRuntime, and QuerySession cases across height/depth/slot requests. |
| invariants | Height can fall back when facts are unusable but \`select_current\` still captures/checks the owner; current failures do not make old Evidence stale as a stored value; new interval changes are reflected. |
| ownership | Historical Selection retains as-of Evidence/plan; CurrentSelection retains a separate fresh capture. |
| failure | Pending/released/budget-exhausted boundaries are explicit; mandatory constraints and processing-resource failures do not silently become fallback. |
| cost | Sequential fixture updates and bounded captures across three owner forms; each current call performs fresh admission/capture work. |
| Design | [tests/unit/selection_current_test.cpp](../../../../../tests/unit/selection_current_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

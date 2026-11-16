# `tests/unit/selection_census_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_census_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0403ceef259de7c944c32a1c9d1d3217f81da61c61ada85a082407f1c45db7b3`. 33 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../tests/unit/selection_census_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 5–33](../../../../../tests/unit/selection_census_test.cpp#L5) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, planner::lower_tree, candidate; guard check(fallback.selection().effective_policy() == pr::Policy::height_only &&; returns 1; growth insert; source comment (unverified): // The existing probe sets several real counters/generations together. This · [reviewed contract](#b0002) |

## B0001

[Lines 1–4](../../../../../tests/unit/selection_census_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L4:sha256:b4d754124dee9c2ac26d71409664afbf55bdc2fd89893b9bcdf8b52a9f35584d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_census_test.cpp: include "selection_fixture.hpp", "runtime_probe.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_census_test.cpp](../../../../../tests/unit/selection_census_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 5–33](../../../../../tests/unit/selection_census_test.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare selection behavior under injected census saturation. |
| inputs / outputs | Creates an owner, injects several maximum counter fields through the runtime probe, captures evidence, then compares fallback height, require-evidence, and slot selection. |
| invariants | The test hook sets multiple related counters together, so this is a combined saturation boundary, not an isolated cause; slot facts can remain usable while depth is degraded. |
| ownership | Probe touches only test-enabled owner internals; Evidence and Selection retain immutable copied context. |
| failure | Required evidence rejects degraded depth; default fallback and slot policy must report their distinct results. |
| cost | Seeds and captures one actual owner, then makes four current-selection calls: fallback, require-evidence, slot-only, and constrained depth. The probe sets several saturation fields together; no maximum-length update sequence runs. |
| Design | [tests/unit/selection_census_test.cpp](../../../../../tests/unit/selection_census_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |

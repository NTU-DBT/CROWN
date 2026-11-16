# `tests/unit/weighted_delta_test.cpp` — block usage map

[Source](../../../../../tests/unit/weighted_delta_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `375122f59e00dc3dc59d48e0b67a7c4984a7ca22bdf3b7ed8e6d1cbb514c7382`. 618 lines partitioned into 58 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/weighted_delta_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // negative, magnitude · [reviewed contract](#b0001) |
| [B0002 · 24–30](../../../../../tests/unit/weighted_delta_test.cpp#L24) | Callable definition: template&lt;class Action&gt; void error(Action action, std::string_view code) | calls action, check, code, std::runtime_error; guard check(failure.code()==code,"unexpected weighted error: "+failure.code());return; · [reviewed contract](#b0002) |
| [B0003 · 31–31](../../../../../tests/unit/weighted_delta_test.cpp#L31) | Explanatory comments or spacing. |  |
| [B0004 · 32–44](../../../../../tests/unit/weighted_delta_test.cpp#L32) | Callable definition: DeltaMap difference(const Counts& before, const Counts& after) | calls insert, contains, at, emplace; returns result; growth emplace, insert; 3 loop sites · [reviewed contract](#b0004) |
| [B0005 · 45–45](../../../../../tests/unit/weighted_delta_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0006 · 46–55](../../../../../tests/unit/weighted_delta_test.cpp#L46) | Callable definition: DeltaMap read_deltas(std::span&lt;const w::BagDelta&gt; entries) | calls check, present, storage::export_row, values; guard check(entry.change.magnitude.present(),"zero net delta was retained");; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 56–56](../../../../../tests/unit/weighted_delta_test.cpp#L56) | Explanatory comments or spacing. |  |
| [B0008 · 57–59](../../../../../tests/unit/weighted_delta_test.cpp#L57) | Callable definition: Counts reference_bag(const runtime::WeightedRuntime& runtime, const Inputs& inputs) | calls bag_oracle, structural_program; returns bag_oracle(runtime.structural_program(),inputs) · [reviewed contract](#b0008) |
| [B0009 · 60–60](../../../../../tests/unit/weighted_delta_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0010 · 61–69](../../../../../tests/unit/weighted_delta_test.cpp#L61) | Callable definition: void compare_delta(const w::Epoch& epoch, const Counts& before, const Counts& after, std::uint64_t owner) | calls check, bool, read_deltas, entries; guard check(bool(epoch.bag_deltas),"enabled commit did not publish an owning delta handle");; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 70–70](../../../../../tests/unit/weighted_delta_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0012 · 71–75](../../../../../tests/unit/weighted_delta_test.cpp#L71) | Callable definition: DeltaMap preview_deltas(const runtime::WeightedRuntime::PendingEpoch& pending) | calls bag_delta_preview, check, has_value, read_deltas; guard check(preview.has_value(),"enabled pending epoch returned disabled preview");; returns read_deltas(*preview); source comment (unverified): // Copy while the borrowed view is valid. · [reviewed contract](#b0012) |
| [B0013 · 76–76](../../../../../tests/unit/weighted_delta_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0014 · 77–81](../../../../../tests/unit/weighted_delta_test.cpp#L77) | Callable definition: void replace_input(Inputs& inputs, std::size_t node, const Row& row, std::uint64_t after) | calls at, erase · [reviewed contract](#b0014) |
| [B0015 · 82–82](../../../../../tests/unit/weighted_delta_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0016 · 83–91](../../../../../tests/unit/weighted_delta_test.cpp#L83) | Callable definition: void stage_replace(runtime::WeightedRuntime::PendingEpoch& pending, Inputs& inputs, std::size_t node, const Row& row, std::uint64… | calls at, find, end, check; guard check(current==before,"test input mirror has a stale replacement precondition"); · [reviewed contract](#b0016) |
| [B0017 · 92–92](../../../../../tests/unit/weighted_delta_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0018 · 93–97](../../../../../tests/unit/weighted_delta_test.cpp#L93) | Callable definition: void compare_runtime_bag(runtime::WeightedRuntime& runtime, const Inputs& inputs) | calls results, check, drain, reference_bag; guard check(drain(cursor)==reference_bag(runtime,inputs), · [reviewed contract](#b0018) |
| [B0019 · 98–98](../../../../../tests/unit/weighted_delta_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0020 · 99–102](../../../../../tests/unit/weighted_delta_test.cpp#L99) | Callable definition: std::uint64_t delta_state_bytes(const runtime::WeightedRuntime& runtime) | calls accounted_memory_statistics; returns statistics.by_purpose\[static_cast&lt;std::size_t&gt;(resource::MemoryPurpose::delta_state)\].requested_byt… · [reviewed contract](#b0020) |
| [B0021 · 103–103](../../../../../tests/unit/weighted_delta_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0022 · 104–116](../../../../../tests/unit/weighted_delta_test.cpp#L104) | Callable definition: PhysicalPlan shared_key_path(bool indexed, std::optional&lt;std::uint64_t&gt; structural_limit={}) | calls options, planner::lower_tree; returns planner::lower_tree(catalog,query,tree,configured) · [reviewed contract](#b0022) |
| [B0023 · 117–117](../../../../../tests/unit/weighted_delta_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0024 · 118–135](../../../../../tests/unit/weighted_delta_test.cpp#L118) | Callable definition: void opt_out(bool indexed) | calls model, unary, reference_bag, delta_state_bytes; guard check(!pending.bag_delta_preview().has_value(),"default begin_epoch enabled delta capture");; source comment (unverified): // One-argument form remains disabled. · [reviewed contract](#b0024) |
| [B0025 · 136–136](../../../../../tests/unit/weighted_delta_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0026 · 137–171](../../../../../tests/unit/weighted_delta_test.cpp#L137) | Callable definition: void insert_delete_and_swap_remove(bool indexed) | calls model, unary, reference_bag, begin_epoch; guard check(preview_deltas(pending)==DeltaMap{{Row{n(7)},Signed{false,2}}},; source comment (unverified): // Slot 0. · [reviewed contract](#b0026) |
| [B0027 · 172–172](../../../../../tests/unit/weighted_delta_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0028 · 173–215](../../../../../tests/unit/weighted_delta_test.cpp#L173) | Callable definition: void absent_anchor_and_cross_term(bool indexed) | calls model, counted_path, reference_bag, begin_epoch; guard check(preview_deltas(pending).empty(),"unsupported root row emitted output"); · [reviewed contract](#b0028) |
| [B0029 · 216–216](../../../../../tests/unit/weighted_delta_test.cpp#L216) | Explanatory comments or spacing. |  |
| [B0030 · 217–238](../../../../../tests/unit/weighted_delta_test.cpp#L217) | Callable definition: void dead_prefix_is_pruned(bool indexed) | calls model, shared_key_path, set, n; guard check(model.runtime.root_weight().value==40,"dead-prefix initial root"); · [reviewed contract](#b0030) |
| [B0031 · 239–239](../../../../../tests/unit/weighted_delta_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0032 · 240–279](../../../../../tests/unit/weighted_delta_test.cpp#L240) | Callable definition: void hidden_projection_and_repeated_head(bool indexed) | calls model, path, set, n; guard check(preview_deltas(pending)==expected,"hidden y/z contributions did not consolidate to x"); · [reviewed contract](#b0032) |
| [B0033 · 280–280](../../../../../tests/unit/weighted_delta_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0034 · 281–299](../../../../../tests/unit/weighted_delta_test.cpp#L281) | Callable definition: void generalized_factor(bool indexed) | calls model, generalized, set, n; guard check(preview_deltas(pending)==expected,"generalized hidden-scope factor did not sum exactly once"); · [reviewed contract](#b0034) |
| [B0035 · 300–300](../../../../../tests/unit/weighted_delta_test.cpp#L300) | Explanatory comments or spacing. |  |
| [B0036 · 301–325](../../../../../tests/unit/weighted_delta_test.cpp#L301) | Callable definition: void nullary_unsigned_magnitude(bool indexed) | calls model, unary, reference_bag, begin_epoch; guard check(full==Counts{{Row{},UINT64_MAX}},"nullary UINT64_MAX output bag");; growth insert · [reviewed contract](#b0036) |
| [B0037 · 326–326](../../../../../tests/unit/weighted_delta_test.cpp#L326) | Explanatory comments or spacing. |  |
| [B0038 · 327–364](../../../../../tests/unit/weighted_delta_test.cpp#L327) | Callable definition: void typed_string_ownership(bool indexed) | calls std::string, model, typed_bag, typed_inputs; guard check(expected.size()==2,"typed string fixture did not emit two flag rows");; growth emplace; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 365–365](../../../../../tests/unit/weighted_delta_test.cpp#L365) | Explanatory comments or spacing. |  |
| [B0040 · 366–376](../../../../../tests/unit/weighted_delta_test.cpp#L366) | Callable definition: std::pair&lt;std::uint64_t,std::uint64_t&gt; measured_cross_term_work(bool indexed) | calls model, counted_path, begin_epoch, check; guard check(pending.stage({NodeId{0},{n(1),n(10),n(100)},{0},{2}}),"work probe root insertion");; returns {first,complete} · [reviewed contract](#b0040) |
| [B0041 · 377–377](../../../../../tests/unit/weighted_delta_test.cpp#L377) | Explanatory comments or spacing. |  |
| [B0042 · 378–409](../../../../../tests/unit/weighted_delta_test.cpp#L378) | Callable definition: void resource_failure_rollback_and_retry(bool indexed) | calls measured_cross_term_work, model, counted_path, reference_bag; guard check(pending.stage({NodeId{0},{n(1),n(10),n(100)},{0},{2}}), · [reviewed contract](#b0042) |
| [B0043 · 410–412](../../../../../tests/unit/weighted_delta_test.cpp#L410) | Explanatory comments or spacing. | source comment (unverified): // Intermediate stages use private state. Compare their net after every edit, · [reviewed contract](#b0043) |
| [B0044 · 413–440](../../../../../tests/unit/weighted_delta_test.cpp#L413) | Callable definition: void randomized_batches(bool indexed) | calls model, counted_path, random, reference_bag; guard check(preview_deltas(pending)==difference(before,reference_bag(model.runtime,next_inputs)),; 2 loop sites; source comment (unverified): // Intermediate stages use private state. Compare their net after every edit, · [reviewed contract](#b0044) |
| [B0045 · 441–441](../../../../../tests/unit/weighted_delta_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0046 · 442–457](../../../../../tests/unit/weighted_delta_test.cpp#L442) | Callable definition: void arithmetic_failure_rollback(bool indexed) | calls model, unary, set, n; guard check(!pending.active() && model.runtime.ready() && model.runtime.sequence()==1 && · [reviewed contract](#b0046) |
| [B0047 · 458–460](../../../../../tests/unit/weighted_delta_test.cpp#L458) | Explanatory comments or spacing. | source comment (unverified): // Deny each covered C++ new attempt in the exact native scenario. Oracle/Row · [reviewed contract](#b0047) |
| [B0048 · 461–506](../../../../../tests/unit/weighted_delta_test.cpp#L461) | Callable definition: void allocation_cuts(bool indexed) | calls n, stage, measured, counted_path; guard check(allocations&gt;0,"empty enabled allocation-cut scenario");; 3 loop sites; source comment (unverified): // Deny each covered C++ new attempt in the exact native scenario. Oracle/Row · [reviewed contract](#b0048) |
| [B0049 · 507–507](../../../../../tests/unit/weighted_delta_test.cpp#L507) | Explanatory comments or spacing. |  |
| [B0050 · 508–525](../../../../../tests/unit/weighted_delta_test.cpp#L508) | Callable definition: void publication_uses_prepared_storage(bool indexed) | calls model, unary, begin_epoch, stage; guard check(calls==0 && !s04_alloc::triggered,"prepared delta publication or rollback used C++ new");; growth emplace; 1 loop sites · [reviewed contract](#b0050) |
| [B0051 · 526–528](../../../../../tests/unit/weighted_delta_test.cpp#L526) | Explanatory comments or spacing. | source comment (unverified): // A caller owns the physical shares; this port edits their logical total. · [reviewed contract](#b0051) |
| [B0052 · 529–549](../../../../../tests/unit/weighted_delta_test.cpp#L529) | Callable definition: void contribution_changes(bool indexed) | calls model, unary, n, set; guard check(pending.stage_contribution(NodeId{0},storage::TupleValuesView::borrow(row),{2},{4}),; source comment (unverified): // A caller owns the physical shares; this port edits their logical total. · [reviewed contract](#b0052) |
| [B0053 · 550–552](../../../../../tests/unit/weighted_delta_test.cpp#L550) | Explanatory comments or spacing. | source comment (unverified): // Measure actual indexed work, then replay exact and one-below limits across · [reviewed contract](#b0053) |
| [B0054 · 553–583](../../../../../tests/unit/weighted_delta_test.cpp#L553) | Callable definition: std::uint64_t enabled_native_grant_scenario(std::optional&lt;std::uint64_t&gt; limit, w::DeltaCapture capture, bool reject) | calls model, shared_key_path, set, n; guard check(spent&gt;previous,"enabled resumed stage refilled its native grant");previous=spent;; returns 0; committed.metrics.native_grant_consumed.structural_steps; 1 loop sites; source comment (unverified): // Measure actual indexed work, then replay exact and one-below limits across · [reviewed contract](#b0054) |
| [B0055 · 584–584](../../../../../tests/unit/weighted_delta_test.cpp#L584) | Explanatory comments or spacing. |  |
| [B0056 · 585–593](../../../../../tests/unit/weighted_delta_test.cpp#L585) | Callable definition: void enabled_native_grant() | calls enabled_native_grant_scenario, check; guard check(enabled&gt;disabled,"private capture cursors did not debit native indexed work"); · [reviewed contract](#b0056) |
| [B0057 · 594–596](../../../../../tests/unit/weighted_delta_test.cpp#L594) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0057) |
| [B0058 · 597–618](../../../../../tests/unit/weighted_delta_test.cpp#L597) | Callable definition: int main() | calls opt_out, insert_delete_and_swap_remove, absent_anchor_and_cross_term, dead_prefix_is_pruned; returns 1; 1 loop sites · [reviewed contract](#b0058) |

## B0001

[Lines 1–23](../../../../../tests/unit/weighted_delta_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:4438c685e88d7e6b335a6130041fca17f1f31889b6217847fed6a3182503590b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare weighted_delta_test.cpp: include "weighted_bag_fixture.hpp", "index_allocation.hpp", "crown/api/error.hpp", &lt;array&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;random&gt;, &lt;set&gt;, &lt;span&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–30](../../../../../tests/unit/weighted_delta_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one expected Error code. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Callable must fail with the named code; unexpected type/code or success fails the test. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | One action; failure-only diagnostic strings. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0004

[Lines 32–44](../../../../../tests/unit/weighted_delta_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMap difference(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build independent signed map from full before/after oracle bags. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Unsigned subtraction preserves UINT64_MAX; omit unchanged keys. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Union of ordinary owned keys and ordered lookup/copies; test-only full mirrors. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0006

[Lines 46–55](../../../../../tests/unit/weighted_delta_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMap read_deltas(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export captured entries to an ordinary comparison map. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Reject zero magnitudes and duplicate projected keys. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Actual scalar/string exports and ordered insertion; no production use. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0008

[Lines 57–59](../../../../../tests/unit/weighted_delta_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts reference_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the projected bag from complete native inputs. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Uses the existing exhaustive join oracle, not incremental factor/delta logic. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Bounded fixture joins and owned result map. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0010

[Lines 61–69](../../../../../tests/unit/weighted_delta_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_delta(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare owning committed facts to the independent net. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Enabled owner, exact signed map and original layout account must agree. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Actual full-map comparison and owned tuple exports. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0012

[Lines 71–75](../../../../../tests/unit/weighted_delta_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMap preview_deltas(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a pending borrowed span while it is valid. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Enabled preview must be engaged; copy before another stage invalidates it. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Test-only deep export/map construction. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0014

[Lines 77–81](../../../../../tests/unit/weighted_delta_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replace_input(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update the independent native occurrence mirror. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Zero removes a row; positive sets its full expected native weight. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Ordinary test map lookup/insertion/erase. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0016

[Lines 83–91](../../../../../tests/unit/weighted_delta_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stage_replace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a changed native input and advance the independent mirror. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Verify expected-before in the mirror and require an actual native change. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Synchronous stage plus ordinary test map update. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0018

[Lines 93–97](../../../../../tests/unit/weighted_delta_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_runtime_bag(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed enumeration independently of captured deltas. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Drain owning cursor to terminal and compare with the full-join oracle. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Complete bounded output enumeration and test map copies. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0020

[Lines 99–102](../../../../../tests/unit/weighted_delta_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t delta_state_bytes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current native-account bytes attributed to optional delta state. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Inspect only the delta_state purpose counter; this is not a global-heap observation. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Fixed aggregate statistics copy and purpose lookup. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0022

[Lines 104–116](../../../../../tests/unit/weighted_delta_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_key_path(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the two-node equality path for dead-prefix checks. |
| inputs / outputs | Storage backend and optional indexed structural ceiling produce the checked two-node x-equality plan. |
| invariants | Both nodes join on x; ordered/indexed option comes from existing fixtures. A supplied structural ceiling is used only with the indexed test backend. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Cold catalog/query/tree/lowering allocations. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0024

[Lines 118–135](../../../../../tests/unit/weighted_delta_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void opt_out(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the existing one-argument entry disabled. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | No preview or committed delta owner; delta_state requested bytes stay at baseline and normal output matches oracle. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | One small replacement, purpose-counter observations and bounded output comparison; full allocation counts are measured separately. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0026

[Lines 137–171](../../../../../tests/unit/weighted_delta_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insert_delete_and_swap_remove(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact cancellation and borrowed-key slot repair. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | 0→2→0 emits enabled empty net; canceling first of two entries repairs moved-last lookup. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two small unary scenarios and independent map exports. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0028

[Lines 173–215](../../../../../tests/unit/weighted_delta_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void absent_anchor_and_cross_term(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check first-answer insertion and causal two-stage products. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Unsupported root emits zero, new child yields +6; existing2*3→4*5 net is+14, not final-factor replay. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two bounded two-node scenarios and per-stage preview checks. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0030

[Lines 217–238](../../../../../tests/unit/weighted_delta_test.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void dead_prefix_is_pruned(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reproduce the incompatible-prefix overflow counterexample. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Limit100 admits roots40→90 and only b:+50; never multiply coefficient50 by incompatible a:40. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two-key fixture and exact independent before/after maps. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0032

[Lines 240–279](../../../../../tests/unit/weighted_delta_test.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hidden_projection_and_repeated_head(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hidden witness summation and repeated output positions. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Independent bag nets are+26 and+6 in the declared head order. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two bounded hidden/projection scenarios. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0034

[Lines 281–299](../../../../../tests/unit/weighted_delta_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generalized_factor(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nested generalized/hidden contributions. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Generalized unit/local sums produce341→451 and net+110 exactly once. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Small generalized plan, native oracle and output comparison. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0036

[Lines 301–325](../../../../../tests/unit/weighted_delta_test.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_unsigned_magnitude(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check positive/negative full unsigned magnitudes on empty tuples. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Unary/nullary outputs ±UINT64_MAX without signed narrowing or wider intermediate oracle sums. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two exact replacements and constant-cardinality maps. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0038

[Lines 327–364](../../../../../tests/unit/weighted_delta_test.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_string_ownership(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain typed repeated long-string facts after runtime teardown. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Original account/layout and output bytes survive; dropping last handle leaves account controller only. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Actual long-string payload copies and post-owner exports. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0040

[Lines 366–376](../../../../../tests/unit/weighted_delta_test.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<std::uint64_t,std::uint64_t> measured_cross_term_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure enabled cumulative work across two real stages. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Second-stage threshold strictly exceeds first; explicit rollback leaves no publication. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | One small measurement, using actual work counters. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0042

[Lines 378–409](../../../../../tests/unit/weighted_delta_test.cpp#L378); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resource_failure_rollback_and_retry(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject one below measured work and retry the same sequence. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Failure closes all stages, preserves committed state/spent diagnostics, and smaller retry succeeds. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Measured small scenario replay; no grant refill. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0043

[Lines 410–412](../../../../../tests/unit/weighted_delta_test.cpp#L410); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L410-L412:sha256:4049d2ca8c13183614a706dd25453e0ecb082085a32ce847fd72e4c5f8f81e8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Intermediate stages use private state. Compare their net after every edit, including cancellation, against full native joins in this test-only mirror. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 413–440](../../../../../tests/unit/weighted_delta_test.cpp#L413); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void randomized_batches(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every private stage across repeated hidden/repeated-head batches. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | 64 epochs with six deterministic stage opportunities per backend; no-ops may skip staging, but every preview equals the full independent before/current bag difference. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Bounded test-only full joins, maps and cursor drains after every epoch. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0046

[Lines 442–457](../../../../../tests/unit/weighted_delta_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arithmetic_failure_rollback(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject arithmetic after a successful private stage. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Limit10 restores initial weight9/sequence1, then same-sequence negative retry commits correctly. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | One small overflow and retry; failure-only Error check. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0047

[Lines 458–460](../../../../../tests/unit/weighted_delta_test.cpp#L458); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L458-L460:sha256:22764b83c12a6a18952d7f1959a13eab14eedb96b3b63a061194f0e861307b11
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Deny each covered C++ new attempt in the exact native scenario. Oracle/Row setup is outside the seam; this neither intercepts all malloc nor measures CPU. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0048

[Lines 461–506](../../../../../tests/unit/weighted_delta_test.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_cuts(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny every observed covered C++ new attempt in enabled capture. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Every failed setup/stage restores initial state, permits same-sequence retry and releases all account payloads on owner teardown. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Actual measured159/178 positions in current Debug profile; malloc/global process behavior is not fully intercepted. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0050

[Lines 508–525](../../../../../tests/unit/weighted_delta_test.cpp#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publication_uses_prepared_storage(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny C++ new during prepared commit and rollback. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Zero covered allocation attempts; committed owning facts or unchanged rollback state remain valid. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | Two small prepared cases; deallocation/allocator bookkeeping still occurs. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

## B0051

[Lines 526–528](../../../../../tests/unit/weighted_delta_test.cpp#L526); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L526-L528:sha256:81233b63d9cd681da2df1b9a87e33fcfe2204e3210d16f47af48b191773371af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A caller owns the physical shares; this port edits their logical total. The private aggregate changes 5→7→5, so the captured projected net cancels. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0052

[Lines 529–549](../../../../../tests/unit/weighted_delta_test.cpp#L529); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void contribution_changes(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify genuine capture through the borrowed contribution-replacement port. |
| inputs / outputs | Logical row total 5 with shares 2+3 owned by the caller; edits 2→4 and 3→1 cancel, then 1→3 emits +2. |
| invariants | The port replaces aggregate shares without claiming physical-source provenance; private preview and committed output match independent totals. |
| ownership | Test owns ordinary fixture/oracle rows; pending token retains the original native allowance and committed facts retain their original account. |
| failure | Unexpected error, net, owner or state fails the test; no local exception translation. |
| cost | Two small captured epochs per backend, borrowed row descriptors and ordinary oracle maps. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W06](../../../../../Refactor.md) |

## B0053

[Lines 550–552](../../../../../tests/unit/weighted_delta_test.cpp#L550); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L550-L552:sha256:0e7c1395e57973c9615137d0bc88b0d2874ac9c6ebfb2ccd90d8033ed56c00bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Measure actual indexed work, then replay exact and one-below limits across 64 resumed stages. Capture cursor work must spend this same native allowance. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0054

[Lines 553–583](../../../../../tests/unit/weighted_delta_test.cpp#L553); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t enabled_native_grant_scenario(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and enforce one actual indexed structural allowance across enabled capture. |
| inputs / outputs | Optional native ceiling, capture mode and expected outcome; return actual committed structural consumption. |
| invariants | 64 resumed native stages share one grant; capture cursor work is included. One-below rejection closes the token and restores sequence 4/native bags. |
| ownership | Test owns ordinary fixture/oracle rows; pending token retains the original native allowance and committed facts retain their original account. |
| failure | Unexpected error/code/admission/state fails the test; the scenario catches only the expected native IndexFailure. |
| cost | Actual indexed work in a fixed two-row/two-node case plus independent before/after comparison; no elapsed-time bound. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W06](../../../../../Refactor.md) |

## B0056

[Lines 585–593](../../../../../tests/unit/weighted_delta_test.cpp#L585); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enabled_native_grant()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay exact and one-below native limits with capture. |
| inputs / outputs | Measure disabled/enabled work, then repeat enabled at its exact ceiling and one below. |
| invariants | Enabled work must exceed disabled cursor-free work, exact admission must consume the measured value, and one below must reject atomically. |
| ownership | Test owns ordinary fixture/oracle rows; pending token retains the original native allowance and committed facts retain their original account. |
| failure | Unexpected error/code/admission/state fails the test; the scenario catches only the expected native IndexFailure. |
| cost | Four bounded indexed scenarios; prints observed structural work, not CPU. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W06](../../../../../Refactor.md) |

## B0057

[Lines 594–596](../../../../../tests/unit/weighted_delta_test.cpp#L594); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L594-L596:sha256:ca577cbc6a8d67316fef9a0d7f55d33179b8f6889d41ade799bac8ac78469ed5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in weighted_delta_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/weighted_delta_test.cpp](../../../../../tests/unit/weighted_delta_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0058

[Lines 597–618](../../../../../tests/unit/weighted_delta_test.cpp#L597); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the selected correctness/resource suite on both storage fixtures. |
| inputs / outputs | Ordinary test fixture state and exact expected observations; assertions execute in the registered target. |
| invariants | Report a process failure for any test exception; one process-boundary diagnostic. |
| ownership | Fixtures/oracle maps own ordinary test data; runtime outputs retain original native account; temporary preview borrows are consumed before invalidation. |
| failure | Unexpected native/oracle/resource result fails the test; only the named helper/fault/process boundaries catch expected failures. |
| cost | All listed bounded scenarios; no timing benchmark. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [tests/support/weighted_bag_fixture.hpp](../../../../../tests/support/weighted_bag_fixture.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md §W06](../../../../../Refactor.md) |

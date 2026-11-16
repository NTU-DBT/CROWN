# `tests/unit/reoptimization_rebuild_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_rebuild_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `befbff8424298c92aa89bee2a4602f575b3115d40eb3a93d5d12fd15d48f6395`. 125 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L12) | Callable definition: Relation results(const DeltaRuntime& owner) | calls next, insert, storage::export_row, values; returns out; growth insert; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 15–19](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L15) | Callable definition: SignedRows apply(DeltaRuntime& owner,TableId table,SetOperation operation,Row values) | calls sequence, std::move, next, emplace; returns out; growth emplace; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 20–23](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L20) | Callable definition: template&lt;class Action&gt; void code(Action&& action,std::string_view expected) | calls action, check, std::runtime_error; guard try {action();}catch(const Error& failure){check(failure.code()==expected,"rebuild rejected with wr… · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L24) | Type/record definition: struct Case |  · [reviewed contract](#b0005) |
| [B0006 · 25–65](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L25) | Callable definition: std::size_t exercise(const Case& fixture,DeltaMode mode,BuildMethod method) | calls candidate_count, DeltaRuntime::initialize, check, results; guard check(results(old)==expected_true,"initial literal result differs");; returns changed; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 66–105](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L66) | Callable definition: void failures(const Case& fixture) | calls DeltaRuntime::initialize, candidate, accounted_memory_statistics, sequence; guard check(foreign_failed,"foreign candidate/source binding was accepted");; growth allocate, reserve · [reviewed contract](#b0007) |
| [B0008 · 106–106](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L106) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 107–125](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L107) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_rebuild SOURCE");const auto fixture=c05_independent::boolean_f…; returns 0; 1; 4 loop sites · [reviewed contract](#b0009) |

## B0001

[Lines 1–11](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:2b08855d398e30234a695fc7fed8d9ee5e8d9ab27618f4debea2dd4cbd5c105c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_rebuild_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "crown/frontend/admission.hpp", &lt;iostream&gt;, &lt;set&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–14](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation results(const DeltaRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a DeltaRuntime result cursor into an ordinary Relation for equality checks. |
| inputs / outputs | Input const DeltaRuntime owner; output copied rows from repeated cursor.next(). |
| invariants | Drains the result cursor into a Relation and compares distinct row values. It ignores set insertion success, so duplicate raw results would collapse. |
| ownership | Cursor borrows owner during loop; exported rows are test-owned copies. |
| failure | Cursor/export failures propagate. |
| cost | Visits and copies all result rows and their scalar/string fields. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § Relation results(const DeltaRuntime& owner) (lines 12-14)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [include/crown/runtime/delta.hpp § results API](../../../../../include/crown/runtime/delta.hpp) |

## B0003

[Lines 15–19](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SignedRows apply(DeltaRuntime& owner,TableId table,SetOperation operation,Row values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one next-sequence update and collect its signed output into an ordinary set. |
| inputs / outputs | Inputs mutable owner/table/op/row copy; calls apply at owner.sequence()+1, drains returned epoch and stores operation plus exported row. |
| invariants | Applies owner.sequence()+1 and drains the epoch into a signed set. emplace success is ignored, so duplicate identical (operation,row) records collapse; equality of returned sets does not verify raw multiplicity or order. |
| ownership | Epoch/cursor owns native output while read; returned SignedRows owns deep exported values. |
| failure | Apply/cursor/export errors propagate. |
| cost | One epoch update plus full signed output drain/copy. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § SignedRows apply(DeltaRuntime& owner,TableId table,SetOperation operation,Row values) (lines 15-19)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [include/crown/runtime/delta.hpp § apply and DeltaRuntime::Epoch API](../../../../../include/crown/runtime/delta.hpp) |

## B0004

[Lines 20–23](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void code(Action&& action,std::string_view expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one rebuild action to fail with an exact public Error code. |
| inputs / outputs | Callable and expected code string; invokes action once, catches Error and compares its code. |
| invariants | Only Error is interpreted as the expected rejection; other exceptions propagate. |
| ownership | Borrows the callable through Action&&, invokes action() as a named lvalue and retains no result; expected borrows the caller's code string. |
| failure | Throws runtime_error if action returns; check rejects wrong code. |
| cost | One action invocation. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § template<class Action> void code(Action&& action,std::string_view expected) (lines 20-23)](../../../../../tests/unit/reoptimization_rebuild_test.cpp) |

## B0005

[Lines 24–24](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Case {planner::CandidateSnapshot family;PhysicalPlan basis;Database initial;bool sql;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle one complete candidate family, physical basis plan, initial database, and SQL-vs-CQ expectation flag. |
| inputs / outputs | Fields: CandidateSnapshot, PhysicalPlan, Database, and bool sql. |
| invariants | All members are retained for repeated candidate/mode/build cases; the bool selects EXISTS result semantics in assertions. |
| ownership | Owns copies of snapshot/plan/database values; proof-prefix handles follow their public snapshot ownership semantics. |
| failure | Construction errors propagate from caller. |
| cost | Copy/retain cost follows family and fixture size; no dynamic execution by this record. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § struct Case (lines 24-24)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 25–65](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t exercise(const Case& fixture,DeltaMode mode,BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare rebuilt owners against the old owner over every retained candidate, mode and build method. |
| inputs / outputs | Inputs Case, DeltaMode and BuildMethod. For each candidate, initializes old runtime, applies four prefix updates, rebuilds at sequence 4, compares owners/account/backend/plan/source/results/init metrics, then applies table-2 delete/insert and duplicate no-op on both owners and checks invariants. |
| invariants | At sequence 4, SQL EXISTS expects one row {true} or {false}; nullary CQ expects the singleton empty row {Row{}} or an empty Relation. Rebuilt runtime owner identity differs while account owner identity is shared. Post-build outputs are compared as signed sets; main separately requires at least one changed physical hash across the whole campaign. |
| ownership | Old and target runtimes coexist under the original query account; exported Relation and SignedRows are ordinary test copies. Target destruction must leave old owner and plan intact. |
| failure | Checks reject incorrect sequence, identity, mode/grant, source-table snapshots, literal results, initialization metrics or paired signed-set deltas. After target destruction, old.check_invariants plus old owner/hash checks run; old results are not re-exported in that final check. |
| cost | Per candidate builds an initial owner and a rebuilt owner and applies four prefix plus three paired post-build updates. Runtime work and full-result copies scale with fixture size. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § std::size_t exercise(const Case& fixture,DeltaMode mode,BuildMethod method) (lines 25-65)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [src/runtime/delta.cpp § DeltaRuntime::rebuilt_for (lines 1447-1458)](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp § rebuilt_for and rebuilt_with_program (lines 591-624)](../../../../../src/runtime/physical.cpp), [docs/reoptimization.md § Native foundation (lines 19-40)](../../../../reoptimization.md) |

## B0007

[Lines 66–105](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failures(const Case& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check replan/build admission rejects foreign source, exhausted budgets, busy readers/private epochs, unread output and account exhaustion without corrupting the old owner. |
| inputs / outputs | Input Case; constructs one delta owner and candidate; tests foreign catalog version, zero BuildOptions work, zero physical lowering work, cursor, pending update, unread output, then original-account exhaustion followed by retry. |
| invariants | Foreign catalog requires ReplanFault::binding; zero build requires resource_limit; cursor/private/unread-output cases require runtime_busy. Zero lowering accepts any ReplanFailure, and memory exhaustion accepts bad_alloc. The original account is deliberately filled, then old sequence/rows/readiness and retry are checked. |
| ownership | Old runtime owns original account; deliberate reserve allocation and cursor/pending/output states are scoped. |
| failure | Each invalid boundary must reject; memory failure must be bad_alloc; retry must reproduce prior sequence/results and invariants. |
| cost | Seven denial setups plus one successful rebuild retry. The unread-output case uses a separate runtime and calls discard after rejection; it does not export/drain those rows into a comparison set. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § void failures(const Case& fixture) (lines 66-105)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [src/runtime/delta.cpp § DeltaRuntime::rebuilt_for (lines 1447-1458)](../../../../../src/runtime/delta.cpp), [src/runtime/physical.cpp § rebuilt_for and rebuilt_with_program (lines 591-624)](../../../../../src/runtime/physical.cpp), [docs/reoptimization.md § Native foundation (lines 19-40)](../../../../reoptimization.md) |

## B0008

[Lines 106–106](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_rebuild_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 107–125](../../../../../tests/unit/reoptimization_rebuild_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run native rebuild comparisons for literal CQ and admitted SQL EXISTS across both backends, two delta modes, and two build methods. |
| inputs / outputs | Requires source root; creates Boolean fixture, a CQ plan and separately admitted SQL normalized program/family; runs exercise for each combination, then failure checks. |
| invariants | Reports actual candidate count and changed plans from fixtures; not a universal candidate-family completeness claim. |
| ownership | Main owns snapshots/plans/databases; exercise owns old/target runtimes per candidate. |
| failure | Requires one path; SQL fixture admission and all assertions must pass; std::exception prints and returns 1. |
| cost | 2 backends × 2 query forms × 2 modes × 2 build methods × family candidate_count, plus failure cases; no performance benchmark. |
| Design | [tests/unit/reoptimization_rebuild_test.cpp § int main(int argc,char** argv) (lines 107-125)](../../../../../tests/unit/reoptimization_rebuild_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_rebuild registration (lines 647-652)](../../../../../CMakeLists.txt), [Refactor.md § C06 — Implement barrier-based reoptimization (lines 1295-1297)](../../../../../Refactor.md) |

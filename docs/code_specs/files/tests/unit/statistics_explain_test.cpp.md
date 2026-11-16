# `tests/unit/statistics_explain_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_explain_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `16fe462635437ccb3ffd1ff09c0dba8701a32855f5c212095af10c447e3a7318`. 117 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/statistics_explain_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;Report&gt;); · [reviewed contract](#b0001) |
| [B0002 · 13–23](../../../../../tests/unit/statistics_explain_test.cpp#L13) | Callable definition: void boundaries(const Report& report,const std::filesystem::path& dir) | calls encoder, check, empty, size; guard const auto full=encoder(report,{});check(!full.text.empty() && full.items&gt;0);; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 24–40](../../../../../tests/unit/statistics_explain_test.cpp#L24) | Callable definition: void scalars(const std::filesystem::path& dir) | calls planner::lower_tree, min, Date::parse, Decimal::parse; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 41–41](../../../../../tests/unit/statistics_explain_test.cpp#L41) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 42–117](../../../../../tests/unit/statistics_explain_test.cpp#L42) | Callable definition: int main(int argc,char** argv) | calls check, std::filesystem::create_directories, plan, database; guard check(argc==2);const std::filesystem::path dir=argv\[1\];std::filesystem::create_directories(dir);; growth insert, make_shared; 2 loop sites · [reviewed contract](#b0005) |

## B0001

[Lines 1–12](../../../../../tests/unit/statistics_explain_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:bcfc81abf3f1f9df382da4d924d4444cf2492e1d1802432e3124be5a0c018ea3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_explain_test.cpp: include "statistics_report_fixture.hpp", &lt;iostream&gt;, &lt;limits&gt;, &lt;type_traits&gt;, "runtime_probe.hpp"; bind local aliases/name imports; require 3 compile-time type/ABI conditions; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_explain_test.cpp](../../../../../tests/unit/statistics_explain_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–23](../../../../../tests/unit/statistics_explain_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundaries(const Report& report,const std::filesystem::path& dir){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check full JSON/text export sizes, exact accepted limits, and one-unit-under resource failures. |
| inputs / outputs | Borrowed Report and directory enter; for both encoders computes full text/item totals, retries exact limits, rejects one-less bytes/items and zero limits. |
| invariants | Exact limits reproduce full text; any insufficient text-byte or item cap raises resource_limit; JSON item count is written for later fixture inspection. |
| ownership | Report is borrowed and immutable; returned serialized text is temporary; file helper owns output. |
| failure | Expected under-cap paths are caught as the exact resource_limit Error code; other failures propagate. |
| cost | Runs both complete encoders multiple times and writes one count file; work scales with report size. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 24–40](../../../../../tests/unit/statistics_explain_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalars(const std::filesystem::path& dir){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture mixed native scalars and compare full, repeated-field, nullary, and occurrence distributions. |
| inputs / outputs | Builds one source relation with int64 endpoints, bool, date endpoints, large/signed decimal, and NUL/high-byte strings; requests full/repeated/empty source projections and occurrence capture. |
| invariants | Literal row maps independently define expected keys; repeated field order is preserved; string bytes and decimal equality remain native; report is emitted in both formats. |
| ownership | Report owns copied capture values and keys after DeltaRuntime operations; input Database/plan are local owners. |
| failure | Planner/capture/export/runtime errors propagate; the helper catches no expected failure. |
| cost | Performs one typed runtime capture, map grouping, JSON/text serialization and file writes; this is not a serializer benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 41–41](../../../../../tests/unit/statistics_explain_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L41:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_explain_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/statistics_explain_test.cpp](../../../../../tests/unit/statistics_explain_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 42–117](../../../../../tests/unit/statistics_explain_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise report capture, lifecycle/version boundaries, partial state, session/window barriers, and generalized workload probes. |
| inputs / outputs | Creates DeltaRuntime and QuerySession fixtures, emits named JSON/text reports, then checks off/no-request, current/stale/within-lag/foreign, workload sampling/truncation/reset/configuration/mode segments, pending/unread/rollback, generalized nodes, hidden E, typed scalar reports, and optional test saturation. |
| invariants | Default capture requests no owner traversal; explicit request facts bind to actual owner/sequence; state and workload availability/budgets stay independent; pending captures expose metadata only; reports and encodings survive later update/move/drop; exact resource caps and failure codes are checked. CROWN_RUNTIME_TESTING saturation is separately guarded. Compile-time checks require Report to be non-default, nothrow-copyable, with const CombinedCapture access. |
| ownership | Each returned report owns immutable combined state/workload/metadata; runtime/session/window are separate local owners. Saved reports from the off and pending scenarios remain valid after mutations and drop. |
| failure | Expected error codes are explicit (explain_statistics_version, resource_limit, session/runtime busy paths); other errors fail main. C++ allocator failures are in the separate exception executable. |
| cost | Creates many fixed reports, re-runs JSON/text serialization, scans literal fixtures, and writes each artifact; volume follows named scenarios and is correctness/export evidence, not timing evidence. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-report-root-results-2026-11-07.md](../../../../verification/c01-statistics-report-root-results-2026-11-07.md) |

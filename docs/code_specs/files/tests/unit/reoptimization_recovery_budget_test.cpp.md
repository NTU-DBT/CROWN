# `tests/unit/reoptimization_recovery_budget_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `353a73a1cb76ebba004a5d701bada1bf04442fbdff8b56907ff6fe608f33014c`. 88 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L12) | Callable definition: reoptimization::Options options() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 15–21](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L15) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 22–39](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L22) | Callable definition: Fixture(const PhysicalPlan& plan,const PhysicalPlan& target,const planner::MinimumHeightCandidate& candidate,const Database& init… | calls source, CompiledProgram::standalone, artifact, io::CompilerPlanArtifact::prepare; guard check(session-&gt;enqueue(batch)==io::Admission::accepted && session-&gt;begin_next(),"recovery budget in…; growth emplace, insert; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 40–40](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L40) | Callable definition: void reset() const | calls generation_test::put; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 41–41](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L41) | Callable definition: void intact() const | calls check, session_file_test::contents; guard void intact() const {for(const auto& \[path,bytes\]:saved)check(session_file_test::contents(path)==by…; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 42–45](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L42) | Callable definition: QuerySession::Owner restore(SessionGenerationRecoveryOptions config=generation_test::recovery_options()) | calls generation_test::recovery_options, QuerySession::lock_generation_recovery, QuerySession::restore_selected_generation_with_local_sink, std::move; returns QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,local_sin… · [reviewed contract](#b0007) |
| [B0008 · 46–52](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L46) | Callable definition: void verify(QuerySession& session) const | calls check, status, progress, snapshot; guard check(session.status().committed_sequence==3 && session.progress().sequence==3 && session.snapshot(… · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L53) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 54–76](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L54) | Callable definition: std::size_t sweep(Fixture& fixture) | calls restore, accounted_memory_statistics, check, verify; guard check(measured-&gt;successful_allocations==allocations,"locked/native recovery escaped the original re…; returns allocations; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 77–77](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L77) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 78–88](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L78) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_recovery_budget SOURCE");const auto model=c05_independent::boo…; returns 0; 1; 1 loop sites · [reviewed contract](#b0012) |

## B0001

[Lines 1–11](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:6eeebfed639ddc5f15f8c785957b9db454d689ad1a61a7eb2606276376bc07a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_recovery_budget_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "crown/io/compiler_plan_artifact.hpp", "crown/runtime/session_reoptimization.hpp", &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–14](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the explicit fixture forecast used to allow the selected-generation recovery tests to reach publication. |
| inputs / outputs | Returns reoptimization::Options with Forecast{1,000,000,000 ns, 1 ns, UINT64_MAX inputs}. |
| invariants | Caller-supplied predicted values only; they are not measured costs. |
| ownership | Owns only a value object. |
| failure | No failure path. |
| cost | Constant-time construction. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § reoptimization::Options options() (lines 12-14)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy and Options (lines 11-61)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md) |

## B0003

[Lines 15–21](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L21:sha256:fb8570be0cde5769711e68247ff200568b34105519fbdf79e608d0a890d474b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_recovery_budget_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. This filesystem Directory member owns the fixture namespace; its constructor/cleanup follows the documented filesystem effects of its helper type. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. This span declares a filesystem Directory member; its fixture construction/cleanup can perform filesystem I/O outside the native query account. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 22–39](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(const PhysicalPlan& plan,const PhysicalPlan& target,const planner::MinimumHeightCandidate& candidate,const Database& initial)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build and switch a sink-attached generation, append incomplete WAL/sink tails, and save five named files for rejected-admission comparisons. |
| inputs / outputs | Inputs original and target plans, candidate, and initial database. Prepares compiler artifact from target; enables generation and local sink; commits/delivers sequences 1 and 2; verifies barrier and publishes; commits sequence 3; appends five-byte CROWN tails to WAL and sink; saves root, sink, WAL, checkpoint, and descriptor bytes. |
| invariants | The saved selection is generation 2 at physical/command sequence 2, followed by sequence 3; the tests preserve and repair exactly the appended five-byte tails. The native and compiler accounts are distinct. |
| ownership | Fixture owns temp directory, compiler input/account, source program, saved file strings, and sink origin; session is local to constructor and dropped before recovery. |
| failure | Setup checks fail on missing delivery, verification, or publication; filesystem/codec exceptions propagate. |
| cost | Prepares one checked target artifact by serialization and compilation, without calling CompilerPlanArtifact::replay; performs one native switch, three input commits/deliveries, two five-byte tail appends and full reads of five saved files. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § Fixture(const PhysicalPlan& plan,const PhysicalPlan& target,const planner::MinimumHeightCandidate& candidate,const Database& initial) :source(CompiledProgram::standalone(plan)),ar… (lines 22-39)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [src/io/compiler_plan_artifact.cpp § prepare and replay overloads (lines 23-54)](../../../../../src/io/compiler_plan_artifact.cpp), [src/runtime/session.cpp § publish_reoptimization (lines 1361-1413)](../../../../../src/runtime/session.cpp), [tests/support/generation_fixture.hpp § put (lines 23-25)](../../../../../tests/support/generation_fixture.hpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp) |

## B0005

[Lines 40–40](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reset() const {for(const auto& [path,bytes]:saved)generation_test::put(path,bytes);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore the exact saved durable bytes before a new receiving-admission attempt. |
| inputs / outputs | Input no args; writes every saved path/value pair back to disk. |
| invariants | Restores all five files to their captured bytes; does not assert or perform recovery itself. |
| ownership | Saved strings are Fixture-owned; filesystem writes copy each string. |
| failure | Write failures propagate. |
| cost | Five writes, total bytes equal saved selected-generation files. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § void reset() const (lines 40-40)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [tests/support/generation_fixture.hpp § put (lines 23-25)](../../../../../tests/support/generation_fixture.hpp) |

## B0006

[Lines 41–41](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void intact() const {for(const auto& [path,bytes]:saved)check(session_file_test::contents(path)==bytes,"recovery allocation/cap rejection repaired or changed durable bytes");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare current durable files with their saved damaged-tail versions after a rejected admission. |
| inputs / outputs | No input; checks each path equals saved byte string. |
| invariants | Requires all selected paths to remain byte-identical; used only before a valid retry has repaired tails. |
| ownership | Fixture retains saved strings; each current file read allocates an ordinary string. |
| failure | check rejects any inequality between a saved string and current contents. The underlying contents helper does not explicitly check stream-open/read status; these comparisons are not a separate I/O-error oracle. |
| cost | Reads and compares all five files, proportional to their total length. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § void intact() const (lines 41-41)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [tests/support/session_file_fixture.hpp § contents and descriptors (lines 26-31)](../../../../../tests/support/session_file_fixture.hpp) |

## B0007

[Lines 42–45](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner restore(SessionGenerationRecoveryOptions config=generation_test::recovery_options()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire the selected-generation root lock and consume it through sink-aware restore using the prepared compiler artifact. |
| inputs / outputs | Optional recovery config input; calls lock_generation_recovery(source,root,config), then restore_selected_generation_with_local_sink with artifact and sink path. |
| invariants | The actual root lock remains held across selected-plan handoff and native admission; only this helper path is used. |
| ownership | Move-only locked package is transferred into restore; returned QuerySession owner owns the receiving native state. |
| failure | Lock/descriptor/binding/admission failures propagate; failed restore must release lock through package/session destruction. |
| cost | One lock/open and recovery admission over fixture state. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § QuerySession::Owner restore(SessionGenerationRecoveryOptions config=generation_test::recovery_options()) (lines 42-45)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp) |

## B0008

[Lines 46–52](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(QuerySession& session) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert recovered sequence/sink lineage and five-byte size reductions for the two known incomplete tails. |
| inputs / outputs | Input restored session; checks committed/progress sequence 3, one snapshot row, sink verified sequence 3, immutable origin header, and current WAL/sink sizes equal saved sizes minus five bytes. |
| invariants | Checks sequence/progress 3, snapshot row count 1, sink verified sequence 3, exact origin header, and WAL/sink lengths five bytes below saved lengths. It does not compare successful-repair prefix contents or assert an exhaustive filesystem diff. |
| ownership | Session owns live state; path reads are temporary standard strings. |
| failure | check rejects changed state/origin or wrong repair lengths. |
| cost | Exports one snapshot and reads two files; work follows fixture row/file sizes. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § void verify(QuerySession& session) const (lines 46-52)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp), [tests/support/session_file_fixture.hpp § contents and descriptors (lines 26-31)](../../../../../tests/support/session_file_fixture.hpp) |

## B0009

[Lines 53–53](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_recovery_budget_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 54–76](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep(Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure actual receiving-account allocations/peak and exercise each allocator cut plus exact/one-under heap admission. |
| inputs / outputs | Input Fixture; baseline restores and records calls/peak, then sweeps every measured call with reset, fd-count comparison, intact-byte check and retry; finally tests exact peak and one-byte-under memory caps. |
| invariants | N must be 1..9999 and equals successful-account allocation count on the successful baseline. Every covered-new fault preserves all five saved byte strings and the observed /proc/self/fd count, then permits retry. One-under admission preserves the five strings but has no FD-count assertion; successful repair is checked by state and two size reductions. |
| ownership | Each restore owns a new receiving session and root lock; descriptors count is process-wide \`/proc/self/fd\`; saved bytes remain fixture-owned. |
| failure | Each cut must observe bad_alloc and trigger, preserve descriptor count/files, then allow successful retry. One-under cap must be MemoryFault::limit. |
| cost | For N measured covered-new calls, performs N failed restore/retry pairs, one baseline, exact-cap and one-byte-under admissions, and a final unrestricted retry. Resets rewrite five files; each restore reads/replays fixture state. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § std::size_t sweep(Fixture& fixture) (lines 54-76)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [tests/support/session_file_fixture.hpp § contents and descriptors (lines 26-31)](../../../../../tests/support/session_file_fixture.hpp) |

## B0011

[Lines 77–77](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L77:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_recovery_budget_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 78–88](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run selected recovery admission sweeps for reference and indexed backends from the repository root. |
| inputs / outputs | Requires one root/source path; builds literal Boolean source and two physical candidate plans for each backend, constructs a durable fixture, and calls sweep. |
| invariants | Only these two backends and one selected-generation fixture are covered. |
| ownership | Main owns Boolean fixture/plans and one Fixture per backend; each sweep owns recovery sessions. |
| failure | Requires one path; exceptions print and return 1. |
| cost | Constructs one durable selected fixture and performs its calibrated allocation/cap campaign for each of two backends. The printed points total counts failed allocation ordinals, excluding baseline, retries and cap attempts. |
| Design | [tests/unit/reoptimization_recovery_budget_test.cpp § int main(int argc,char** argv) (lines 78-88)](../../../../../tests/unit/reoptimization_recovery_budget_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_recovery_budget registration (lines 698-703)](../../../../../CMakeLists.txt) |

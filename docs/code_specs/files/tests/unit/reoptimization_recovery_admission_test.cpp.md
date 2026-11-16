# `tests/unit/reoptimization_recovery_admission_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c1e043a20e4ca526e2e07e6382043dbf373c36de0858f4f99996f5dc8aaf6ec7`. 112 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–17](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L15) | Callable definition: reoptimization::Options options() | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 18–22](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L18) | Type/record definition: struct PauseCleanup | returns result · [reviewed contract](#b0003) |
| [B0004 · 23–37](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L23) | Callable definition: void retirement_preflight(bool indexed) | calls fixture, recovery::testing::set_generation_hook, retire_generation_history, check; guard check(interrupted && std::filesystem::exists(fixture.root+".retire"),"retirement preflight fixture … · [reviewed contract](#b0004) |
| [B0005 · 38–45](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L38) | Type/record definition: struct DenyAfterInput | returns {} · [reviewed contract](#b0005) |
| [B0006 · 46–80](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L46) | Callable definition: void cached_reader(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Databas… | calls file, begin, io::write_input_json, source_catalog; guard check(failed && hook.reached && !session-&gt;status().input_failed && !session-&gt;journal_state().recove…; growth insert, make_unique; 3 loop sites; source comment (unverified): // Rebuild after the failed candidate; the barrier must drain the already decoded row. · [reviewed contract](#b0006) |
| [B0007 · 81–100](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L81) | Callable definition: void lock_and_binding(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Data… | calls file, QuerySession::create_typed, start, enable_generation; guard check(session-&gt;advance_reoptimization(100000).phase==reoptimization::Phase::verified,"lock fixture … · [reviewed contract](#b0007) |
| [B0008 · 101–101](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L101) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 102–112](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L102) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, s04_runtime::options, c05_independent::lower; guard check(argc==2,"usage: reoptimization_recovery_admission SOURCE");const auto fixture=c05_independent…; returns 0; 1; 1 loop sites · [reviewed contract](#b0009) |

## B0001

[Lines 1–14](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:a69d2c780a9d5183a80d71aae7ecd7281a67881064ec4330478cb4d2134cd378
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_recovery_admission_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "history_retirement_fixture.hpp", "generation_file_probe.hpp", "journal_file_probe.hpp", "crown/io/compiler_plan_artifact.hpp", "crown/runtime/session_reoptimization.hpp", &lt;cerrno&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–17](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the explicit fixture forecast used by barrier and selected-recovery tests. |
| inputs / outputs | Returns Options with Forecast{1,000,000,000 ns, 1 ns, UINT64_MAX inputs}. |
| invariants | Values are predictions only and serve to avoid payback rejection. |
| ownership | Owns a value object. |
| failure | No failure path. |
| cost | Constant-time construction. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § reoptimization::Options options() (lines 15-17)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy and Options (lines 11-61)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md) |

## B0003

[Lines 18–22](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PauseCleanup {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject EIO before the history unlink stage to leave one retirement intent for recovery-preflight tests. |
| inputs / outputs | Static generation-hook callback; returns error_before=EIO only for \`unlink_history\`. |
| invariants | The hook is scoped to one named generation event and does not emulate power loss. |
| ownership | No ownership; callback context unused. |
| failure | Callback is noexcept; caller must clear the hook. |
| cost | Constant predicate per event. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § struct PauseCleanup (lines 18-22)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [tests/support/generation_file_probe.hpp § GenerationDecision (lines 10-17)](../../../../../tests/support/generation_file_probe.hpp) |

## B0004

[Lines 23–37](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retirement_preflight(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove pending retirement without its required sink is rejected before WAL-tail repair, then resumes through sink-aware recovery. |
| inputs / outputs | Input backend flag; creates RetirementFixture, injects one unlink error, confirms \`.retire\`, drops owner, appends five bytes to generation-3 WAL, locks root and attempts restore without sink, then invokes valid fixture restore. |
| invariants | Checks retirement intent remains and corrupt-tail bytes remain unchanged on missing-sink rejection; valid sink-aware recovery reaches sequence 3 and finishes retirement. Scope is this one generation-history fixture per backend. |
| ownership | Fixture owns root/sink/session/temp dir; lock package is moved into rejected restore; compiler artifact uses separate account. |
| failure | The injected retirement call catches GenerationFailure and then explicitly clears its hook to null; an unexpected exception bypasses that reset. Missing-sink restore must report GenerationFault::state with unchanged WAL bytes and an extant intent, then sink-aware retry must reach sequence 3 and remove the intent. |
| cost | One retirement attempt, one rejected selected recovery and one valid recovery per backend; file reads/copies scale with fixture data. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § void retirement_preflight(bool indexed) (lines 23-37)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [tests/support/history_retirement_fixture.hpp § RetirementFixture (lines 6-35)](../../../../../tests/support/history_retirement_fixture.hpp), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp) |

## B0005

[Lines 38–45](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DenyAfterInput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny instrumented allocation immediately after a successful journal input sync. |
| inputs / outputs | Static callback with borrowed context; marks reached and zeros s04 allocator after an after-event successful \`sync_file\`. |
| invariants | Matches any journal after sync_file event with result==0, independent of record payload type. cached_reader installs it only around the first begin_next, making that observed sync the original Input append; remaining=0 denies covered-new attempts on this thread until Scope exit. |
| ownership | Context is borrowed during callback installation. |
| failure | Callback returns default FileDecision and is noexcept. |
| cost | Constant work per event. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § struct DenyAfterInput (lines 38-45)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [tests/support/journal_file_probe.hpp § FileEvent and FileDecision (lines 5-17)](../../../../../tests/support/journal_file_probe.hpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 46–80](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cached_reader(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test cached stream-row retry across candidate cancellation, a barrier, publication, and selected-generation restore. |
| inputs / outputs | Inputs original/target plans, candidate family and database. Creates two JSONL events; denies native allocation after first input sync during begin_next; verifies reader offset/progress, retries after cancel, pauses/freezes and advances quantum 1 under a 10000-call guard, publishes target, then locked-recovers with tail continuation. |
| invariants | Native begin fails after the first Input is synced, leaving decoder at prefix end and accepted progress 0. The frozen barrier processes that cached row, verifies one replay at progress 1 and stays paused without reading the tail. Publication checks complete plus returned query_memory.current equal a fresh account current snapshot; it does not prove exact attribution. The caller later supplies only sequence 2 as continuation. |
| ownership | Input reader is owned by session; test keeps a borrowed stream pointer only until session replacement. Artifact/compiler account is separate; lock package is consumed by restore. |
| failure | Initial begin_next must throw bad_alloc after the sync hook is reached without input_failed or recovery_required. The hook is cleared after normal return or the caught bad_alloc; other exception types bypass that explicit reset. Barrier verification must occur within the 10000-call guard, and restored continuation must reach committed/progress 2 with one snapshot row. |
| cost | One injected input, up to 10000 advance(1) calls with possible output drains, one publication, one restore and one continuation epoch. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § void cached_reader(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) (lines 46-80)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [src/runtime/session.cpp § admitted_input and begin (lines 554-605)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § begin_reoptimization_with_cost through reoptimization_status (lines 1298-1360)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State construction, stage, advance and verify (lines 51-250)](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md § Required session protocol (lines 59-139)](../../../../reoptimization.md), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/io/compiler_plan_artifact.cpp § prepare and replay overloads (lines 23-54)](../../../../../src/io/compiler_plan_artifact.cpp) |

## B0007

[Lines 81–100](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lock_and_binding(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify the actual root lock remains held through compiler handoff, and reject a wrong artifact before repairing a WAL tail. |
| inputs / outputs | Inputs original/target plans, candidate family and initial DB. Publishes selected generation, appends five-byte WAL tail, obtains lock, attempts second lock, attempts restore with wrong original artifact, then reacquires lock, replays borrowed compiler bytes and performs valid selected restore. |
| invariants | A second lock must fail busy while the package owns the root. Wrong-original artifact restore must report binding and leave the entire damaged WAL string unchanged. Successful retry checks a five-byte WAL size reduction and snapshot row count 1, without comparing the repaired prefix bytes. |
| ownership | Move-only lock package owns real root lock during artifact replay; prepared compiler artifact comes from separate account. |
| failure | Assertions reject lost lock, premature tail repair or wrong binding; filesystem/recovery exceptions propagate. |
| cost | One switch, two lock attempts plus re-lock, compiler replay, and two recovery attempts over fixture files. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § void lock_and_binding(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) (lines 81-100)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [src/runtime/session.cpp § lock_generation_recovery and restore_locked_generation (lines 1093-1150)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp), [src/io/compiler_plan_artifact.cpp § prepare and replay overloads (lines 23-54)](../../../../../src/io/compiler_plan_artifact.cpp) |

## B0008

[Lines 101–101](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L101:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_recovery_admission_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 102–112](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run retirement, cached-reader and lock/binding recovery-admission cases on both physical backends. |
| inputs / outputs | Requires source root; builds Boolean fixture, lowers candidates 0 and 1 per backend, invokes all three cases. |
| invariants | Finite two-backend coverage for these specific recovery sequences; no general syscall-fault matrix. |
| ownership | Main owns source plans/family; each case owns its temp directory and sessions. |
| failure | Requires one path; exceptions print and return 1. |
| cost | Two backends × three cases; cases perform a small number of file and recovery operations. |
| Design | [tests/unit/reoptimization_recovery_admission_test.cpp § int main(int argc,char** argv) (lines 102-112)](../../../../../tests/unit/reoptimization_recovery_admission_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_recovery_admission registration (lines 678-683)](../../../../../CMakeLists.txt) |

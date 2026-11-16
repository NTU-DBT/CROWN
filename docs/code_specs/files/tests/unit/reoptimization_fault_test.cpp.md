# `tests/unit/reoptimization_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `740f5a2d0f3de8abcfc3952113bae09aeb15f5155c00525d1e461efdf0d09ae4`. 154 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/unit/reoptimization_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../tests/unit/reoptimization_fault_test.cpp#L12) | Callable definition: reoptimization::Options options() | calls ; returns result · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../tests/unit/reoptimization_fault_test.cpp#L15) | Type/record definition: enum class Cut |  · [reviewed contract](#b0003) |
| [B0004 · 16–18](../../../../../tests/unit/reoptimization_fault_test.cpp#L16) | declares types or opens a type body. |  · [reviewed contract](#b0004) |
| [B0005 · 19–27](../../../../../tests/unit/reoptimization_fault_test.cpp#L19) | Callable definition: Fixture(const PhysicalPlan& plan,const Database& initial,planner::MinimumHeightCandidate target,Cut cut) :session(QuerySession::c… | calls session, QuerySession::create_typed, candidate, std::move; guard check(session-&gt;enqueue(batch)==io::Admission::accepted,"fault input was not admitted"); · [reviewed contract](#b0005) |
| [B0006 · 28–30](../../../../../tests/unit/reoptimization_fault_test.cpp#L28) | Callable definition: void finish() | calls step, commit, next_output; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 31–35](../../../../../tests/unit/reoptimization_fault_test.cpp#L31) | Callable definition: void attempt(Cut cut) | calls begin_reoptimization, options, begin_next, advance_reoptimization · [reviewed contract](#b0007) |
| [B0008 · 36–41](../../../../../tests/unit/reoptimization_fault_test.cpp#L36) | Callable definition: void verify_retry() | calls cancel_reoptimization, begin_reoptimization, options, request_reoptimization_barrier; guard check(status.phase==reoptimization::Phase::verified && status.source_epoch==session-&gt;status().commi… · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../tests/unit/reoptimization_fault_test.cpp#L42) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 43–45](../../../../../tests/unit/reoptimization_fault_test.cpp#L43) | Callable definition: Relation rows(QuerySession& session) | calls snapshot, insert, storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 46–78](../../../../../tests/unit/reoptimization_fault_test.cpp#L46) | Callable definition: std::size_t sweep(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,Cut cut) | calls source, attempt, finish, check; guard check(allocations&gt;0 && allocations&lt;10000,"allocation sweep has an invalid finite bound");; returns allocations; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 79–86](../../../../../tests/unit/reoptimization_fault_test.cpp#L79) | Type/record definition: struct DenyAfterSync | returns {} · [reviewed contract](#b0012) |
| [B0013 · 87–106](../../../../../tests/unit/reoptimization_fault_test.cpp#L87) | Callable definition: void durable_publication(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate) | calls source, file, checkpoint_file, enable_journal; guard check(source.session-&gt;enqueue(batch)==io::Admission::accepted && source.session-&gt;begin_next(),"jour…; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 107–113](../../../../../tests/unit/reoptimization_fault_test.cpp#L107) | Type/record definition: struct FailAfterSync | returns result · [reviewed contract](#b0014) |
| [B0015 · 114–140](../../../../../tests/unit/reoptimization_fault_test.cpp#L114) | Callable definition: void uncertain_original_journal(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate… | calls source, file, checkpoint_file, enable_journal; guard check(source.session-&gt;enqueue(batch)==io::Admission::accepted,"uncertain journal candidate input mi…; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 141–141](../../../../../tests/unit/reoptimization_fault_test.cpp#L141) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0016) |
| [B0017 · 142–154](../../../../../tests/unit/reoptimization_fault_test.cpp#L142) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, c05_independent::lower, at; guard check(argc==2,"usage: reoptimization_fault SOURCE");const auto fixture=c05_independent::boolean_fix…; returns 0; 1; 3 loop sites · [reviewed contract](#b0017) |

## B0001

[Lines 1–11](../../../../../tests/unit/reoptimization_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:fe39b26ec99f340de8b7d34f09ae206142afc146dfd37299a91f6c93b511c220
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_fault_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "session_journal_fixture.hpp", "journal_file_probe.hpp", &lt;cerrno&gt;, &lt;iostream&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_fault_test.cpp](../../../../../tests/unit/reoptimization_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–14](../../../../../tests/unit/reoptimization_fault_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Options options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the deliberately long caller forecast used to keep policy payback from stopping these mechanics tests. |
| inputs / outputs | Returns one Options value with Forecast{1,000,000,000 ns, 1 ns, UINT64_MAX inputs}. |
| invariants | These are fixture predictions supplied by the test; they are not measured performance or an enabled automatic cost model. |
| ownership | Owns only the returned value object. |
| failure | No failure path. |
| cost | Constant-time value construction. |
| Design | [tests/unit/reoptimization_fault_test.cpp § reoptimization::Options options() (lines 12-14)](../../../../../tests/unit/reoptimization_fault_test.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy and Options (lines 11-61)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md) |

## B0003

[Lines 15–15](../../../../../tests/unit/reoptimization_fault_test.cpp#L15); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Cut {snapshot,old_begin,catch_up,equivalence};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the four allocation-fault entry points swept by this file. |
| inputs / outputs | Cut values select candidate snapshot, old-owner begin, private catch-up, or equivalence preparation. |
| invariants | Only the four enum values appear in the main loop; this does not include durable plan-selection cuts. |
| ownership | Stateless enum. |
| failure | No failure path. |
| cost | Constant-size enum. |
| Design | [tests/unit/reoptimization_fault_test.cpp § enum class Cut (lines 15-15)](../../../../../tests/unit/reoptimization_fault_test.cpp) |

## B0004

[Lines 16–18](../../../../../tests/unit/reoptimization_fault_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L18:sha256:d0c463409bc53bb8ebafa87f8e16cfd6dcf242b02a64f05b273df91dc4697a8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/reoptimization_fault_test.cpp](../../../../../tests/unit/reoptimization_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 19–27](../../../../../tests/unit/reoptimization_fault_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(const PhysicalPlan& plan,const Database& initial,planner::MinimumHeightCandidate target,Cut cut)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the old session and candidate at the source state appropriate to one selected allocation cut. |
| inputs / outputs | Inputs: plan, initial database, copied minimum-height candidate, and Cut. Starts the session; except snapshot, begins candidate preparation; equivalence requests a barrier; other cuts enqueue one erase at sequence 1, and catch_up also commits/drains it. |
| invariants | The old_begin case reaches begin_next with one admitted event; catch_up has committed sequence 1 and drained output; equivalence is frozen at the initial epoch. |
| ownership | Fixture owns QuerySession and candidate; moving the candidate into the fixture prevents dependence on caller lifetime. |
| failure | Preparation/enqueue failures propagate; checks fail if the selected state cannot be reached. |
| cost | Constructs one source session. Snapshot leaves candidate rebuild for attempt(); every other cut performs begin_reoptimization and its snapshot rebuild here. Old-begin and catch-up enqueue one erase; catch-up also steps, commits and drains it during setup. |
| Design | [tests/unit/reoptimization_fault_test.cpp § Fixture(const PhysicalPlan& plan,const Database& initial,planner::MinimumHeightCandidate target,Cut cut) :session(QuerySession::create_typed(plan,initial)),candidate(std::move(tar… (lines 19-27)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/runtime/session.cpp § begin_reoptimization_with_cost through reoptimization_status (lines 1298-1360)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State construction, stage, advance and verify (lines 51-250)](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md § Required session protocol (lines 59-139)](../../../../reoptimization.md) |

## B0006

[Lines 28–30](../../../../../tests/unit/reoptimization_fault_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and fully consume the current old-owner input epoch for retry and fixture preparation. |
| inputs / outputs | No input; steps until prepared, commits once, then repeatedly calls next_output until empty. |
| invariants | The loop has no guard and requires a progress-capable pending epoch; it is not a general bounded-progress helper. |
| ownership | Session retains owner; returned outputs are discarded as each optional result leaves scope. |
| failure | Any session transition exception escapes to caller. |
| cost | Work equals the engine steps plus all output rows in the current fixture epoch; no CPU cap. |
| Design | [tests/unit/reoptimization_fault_test.cpp § void finish() (lines 28-30)](../../../../../tests/unit/reoptimization_fault_test.cpp), [include/crown/runtime/session.hpp § QuerySession lifecycle API](../../../../../include/crown/runtime/session.hpp) |

## B0007

[Lines 31–35](../../../../../tests/unit/reoptimization_fault_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void attempt(Cut cut) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one allocation-sweep attempt to the source operation named by Cut. |
| inputs / outputs | Input Cut: snapshot invokes begin_reoptimization; old_begin invokes begin_next; catch_up/equivalence call advance_reoptimization(100000). |
| invariants | The argument 100000 is a quantum for advance, not a wall-clock bound; the helper does not verify completion itself. |
| ownership | Uses the fixture session and candidate by reference; no new owner. |
| failure | Native errors and bad_alloc propagate to sweep. |
| cost | One public operation. advance(100000) limits counted old/private native begin/step calls; a following equivalence check has its own work/row/cursor grants and is not bounded by that quantum in elapsed time. |
| Design | [tests/unit/reoptimization_fault_test.cpp § void attempt(Cut cut) (lines 31-35)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/runtime/session.cpp § begin_reoptimization_with_cost through reoptimization_status (lines 1298-1360)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State construction, stage, advance and verify (lines 51-250)](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md § Required session protocol (lines 59-139)](../../../../reoptimization.md) |

## B0008

[Lines 36–41](../../../../../tests/unit/reoptimization_fault_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel and retry an allocation-failed candidate, then verify it at the exact current old-owner epoch. |
| inputs / outputs | No input; cancels current preparation, rebuilds the same candidate, requests barrier, advances with quantum 100000, checks verified and source_epoch==target_epoch==current committed sequence, then cancels. |
| invariants | This retry check is against the current source after the caller-specific old_begin retry/finish behavior; the large quantum is not a CPU-time deadline. |
| ownership | Fixture session owns candidate preparation state; no caller payload escapes. |
| failure | Check fails if exact retry is not verified; runtime exceptions propagate. |
| cost | One candidate rebuild, barrier verification and cancellation; their work is fixture-dependent. |
| Design | [tests/unit/reoptimization_fault_test.cpp § void verify_retry() (lines 36-41)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/runtime/session.cpp § begin_reoptimization_with_cost through reoptimization_status (lines 1298-1360)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State construction, stage, advance and verify (lines 51-250)](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md § Required session protocol (lines 59-139)](../../../../reoptimization.md) |

## B0009

[Lines 42–42](../../../../../tests/unit/reoptimization_fault_test.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L42:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_fault_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_fault_test.cpp](../../../../../tests/unit/reoptimization_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 43–45](../../../../../tests/unit/reoptimization_fault_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation rows(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the session snapshot into an ordinary set for old-result preservation assertions. |
| inputs / outputs | Input QuerySession reference; output Relation of copied rows. |
| invariants | Reads committed snapshot rows into a set; insertion success is not checked, so duplicate raw snapshot rows would collapse in the returned Relation. |
| ownership | Copies exported row values into a standard Relation. |
| failure | Session snapshot or export failures propagate. |
| cost | Visits and copies every snapshot result row and field/string payload. |
| Design | [tests/unit/reoptimization_fault_test.cpp § Relation rows(QuerySession& session) (lines 43-45)](../../../../../tests/unit/reoptimization_fault_test.cpp), [include/crown/runtime/session.hpp § snapshot API](../../../../../include/crown/runtime/session.hpp) |

## B0011

[Lines 46–78](../../../../../tests/unit/reoptimization_fault_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,Cut cut) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure the instrumented allocation count and fail each allocation point for one selected preparation boundary. |
| inputs / outputs | Inputs plan/database/candidate/Cut; counts one baseline attempt, then constructs a fresh fixture and injects each allocation ordinal below that measured count. |
| invariants | Count must be positive and below 10000. Old-begin failures may retry the event and then finish it; other failures may throw bad_alloc or transition the candidate to failed. Checks preserve owner/committed rows, admission thawing, account invariants and a successful candidate retry. |
| ownership | Each iteration owns a fresh session and temporary candidate state; \`owner\` is a value ID, while Relation snapshots are copied test data. |
| failure | Every injected point must trigger. The source owner cannot be replaced or journal-poisoned; old_begin must leave sequence/progress/backlog zero before its optional retry. |
| cost | N measured calls produce N fault runs per Cut/backend, plus setup and retry; 10000 is only an assertion ceiling, not a query-wide memory/time bound. |
| Design | [tests/unit/reoptimization_fault_test.cpp § std::size_t sweep(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,Cut cut) (lines 46-78)](../../../../../tests/unit/reoptimization_fault_test.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [src/runtime/session.cpp § begin_reoptimization_with_cost through reoptimization_status (lines 1298-1360)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State construction, stage, advance and verify (lines 51-250)](../../../../../src/runtime/reoptimization.cpp), [docs/reoptimization.md § Required session protocol (lines 59-139)](../../../../reoptimization.md) |

## B0012

[Lines 79–86](../../../../../tests/unit/reoptimization_fault_test.cpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DenyAfterSync {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deny further instrumented allocation immediately after a successful original journal file sync. |
| inputs / outputs | Static file-hook callback and borrowed context; records a successful after-sync event and sets s04_alloc::remaining to zero. |
| invariants | Only journal FileEvents are observed; after sync_file with result==0 sets remaining=0 for the active nonnested s04_alloc Scope on this thread. Covered C++ new attempts are denied persistently until Scope exit; libc allocation and other threads are outside that counter. |
| ownership | Context pointer is borrowed until the hook is cleared by the caller. |
| failure | Callback is noexcept and returns the default decision; cleanup of hook installation is caller responsibility. |
| cost | Constant work per event; no allocation. |
| Design | [tests/unit/reoptimization_fault_test.cpp § struct DenyAfterSync (lines 79-86)](../../../../../tests/unit/reoptimization_fault_test.cpp), [tests/support/journal_file_probe.hpp § FileEvent, FileDecision and hook setter (lines 5-17)](../../../../../tests/support/journal_file_probe.hpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0013

[Lines 87–106](../../../../../tests/unit/reoptimization_fault_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void durable_publication(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that an original journal decision can publish the committed old epoch and candidate ledger without post-sync instrumented allocation. |
| inputs / outputs | Inputs plan/database/candidate; creates checkpoint+WAL, begins reoptimization, prepares sequence-1 erase, installs DenyAfterSync while committing, drains normal output, requests barrier and advances candidate. |
| invariants | Asserts successful file sync, no denied allocator call, committed/progress sequence 1, one backlog record and source epoch 1, then verified catch-up. It covers this journal hook point and fixture, not all I/O boundaries. |
| ownership | Fixture owns session and temp journal directory; journal hook borrows stack context and is cleared before checks. |
| failure | Commit exception clears the hook then rethrows. Checks fail if durable publication allocates or the candidate loses committed input. |
| cost | One journaled input/commit, output drain, and advance quantum 100000; no CPU bound or broad durability proof. |
| Design | [tests/unit/reoptimization_fault_test.cpp § void durable_publication(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate) (lines 87-106)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/runtime/session.cpp § journal_decision and finish (lines 323-345)](../../../../../src/runtime/session.cpp), [src/runtime/reoptimization.cpp § State::committed (lines 170-176)](../../../../../src/runtime/reoptimization.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0014

[Lines 107–113](../../../../../tests/unit/reoptimization_fault_test.cpp#L107); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FailAfterSync {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request an after-syscall EIO for each original-journal sync_file observed while this hook is installed. |
| inputs / outputs | Static journal callback returning FileDecision with error_after=EIO when a before event identifies sync_file. |
| invariants | The before-event decision sets error_after; File::call executes fsync and reports EIO after a successful syscall. The callback matches sync_file only and ignores its context. |
| ownership | No data ownership; callback context is unused. |
| failure | The caller expects FileFailure and always clears the hook, including unexpected exceptions. |
| cost | Constant predicate and decision construction per observed event. |
| Design | [tests/unit/reoptimization_fault_test.cpp § struct FailAfterSync (lines 107-113)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/recovery/journal_file.cpp § File::call (lines 61-113)](../../../../../src/recovery/journal_file.cpp), [tests/support/journal_file_probe.hpp § FileDecision (lines 10-17)](../../../../../tests/support/journal_file_probe.hpp) |

## B0015

[Lines 114–140](../../../../../tests/unit/reoptimization_fault_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void uncertain_original_journal(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,bool decision) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify uncertain original-journal input or decision recovery never selects the private reoptimization candidate. |
| inputs / outputs | Inputs plan/database/candidate and bool decision. Injects after-sync EIO either during begin_next or commit, checks recovery_required and blocked candidate cancellation, drops owner, restores original journal, and finishes the uncommitted input when appropriate. |
| invariants | Two cases distinguish failure while recording input from failure while recording decision. Recovery must use the original CompiledProgram and return inactive reoptimization; exact recovered sequence is 0 then committed once, or 1 if decision persisted. |
| ownership | Temporary journal is owned by Directory; source and recovered sessions own separate runtime state. Hook is explicitly cleared on normal and exceptional paths. |
| failure | Requires FileFailure, recovery latch, blocked cancel, and exactly-once original recovery; unexpected errors rethrow after hook cleanup. |
| cost | At most one injected journal sync fault per decision mode; one restore and, for input-only failure, one subsequent ordinary commit. |
| Design | [tests/unit/reoptimization_fault_test.cpp § void uncertain_original_journal(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,bool decision) (lines 114-140)](../../../../../tests/unit/reoptimization_fault_test.cpp), [src/runtime/session.cpp § journal_input, journal_decision, require_recovery and finish (lines 286-345)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp), [docs/reoptimization.md § Required session protocol (lines 98-111)](../../../../reoptimization.md) |

## B0016

[Lines 141–141](../../../../../tests/unit/reoptimization_fault_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L141:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_fault_test.cpp](../../../../../tests/unit/reoptimization_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 142–154](../../../../../tests/unit/reoptimization_fault_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run preparation allocation sweeps on both physical backends and separate durable journal cases. |
| inputs / outputs | Requires repository/source root; loads literal Boolean fixture; executes four Cut values per backend, one post-sync publication case, and both uncertain-journal modes. |
| invariants | The main does not include managed-root plan-selection crash cuts; its success message explicitly leaves those separate. Every measured sweep is fixture-limited. |
| ownership | Main owns Boolean fixture and local plans; each sweep owns its own sessions. |
| failure | Requires exactly one path argument; any std::exception is printed and returns 1. |
| cost | Two backends each run four measured allocation campaigns, one durable-publication case and two original-journal uncertainty cases. Sweep sizes come from covered-new baseline counts; stepping/draining is fixture-dependent. |
| Design | [tests/unit/reoptimization_fault_test.cpp § int main(int argc,char** argv) (lines 142-154)](../../../../../tests/unit/reoptimization_fault_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § reoptimization_faults registration (lines 719-724)](../../../../../CMakeLists.txt) |

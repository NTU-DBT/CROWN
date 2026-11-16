# `tests/unit/reoptimization_promotion_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c3315ae4b139626c6d175b844829aaf78f3dc165be06727908d590e2aa1830ec`. 139 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 21–28](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L21) | Callable definition: Fixture(const PhysicalPlan& plan,const Database& initial):session(QuerySession::create_typed(plan,initial)) | calls session, QuerySession::create_typed, start, checkpoint_file; growth insert · [reviewed contract](#b0002) |
| [B0003 · 29–33](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L29) | Callable definition: void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) | calls batch, check, enqueue, begin_next; guard check(session-&gt;enqueue(batch)==io::Admission::accepted && session-&gt;begin_next(),"promotion input mi… · [reviewed contract](#b0003) |
| [B0004 · 34–34](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L34) | Callable definition: void promote() | calls promote_journal, generation_test::options · [reviewed contract](#b0004) |
| [B0005 · 35–38](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L35) | Callable definition: void original() const | calls check, session_file_test::contents; guard check(session_file_test::contents(checkpoint)==old_checkpoint && session_file_test::contents(wal)==… · [reviewed contract](#b0005) |
| [B0006 · 39–52](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L39) | Callable definition: void recover(const PhysicalPlan& plan,const Database& initial) | calls reset, CompiledProgram::standalone, std::filesystem::exists, QuerySession::restore_generation_with_local_sink; guard check(session-&gt;status().committed_sequence==3 && session-&gt;progress().sequence==3 && session-&gt;status… · [reviewed contract](#b0006) |
| [B0007 · 53–53](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L53) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 54–74](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L54) | Type/record definition: struct Hook | returns result; self.decision&lt;recovery::testing::GenerationDecision&gt;(event.after) · [reviewed contract](#b0008) |
| [B0009 · 75–78](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L75) | Type/record definition: struct Installed |  · [reviewed contract](#b0009) |
| [B0010 · 79–84](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L79) | Callable definition: std::uint64_t trace(const PhysicalPlan& plan,const Database& initial) | calls fixture, installed, promote, check; guard check(hook.reached && !hook.order_violation && !triggered && fixture.session-&gt;status().state==Sessi…; returns hook.count · [reviewed contract](#b0010) |
| [B0011 · 85–101](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L85) | Callable definition: std::size_t io_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) | calls fixture, installed, promote, check; guard check(failed,"promotion ignored a persistence failure");fixture.original();; returns cuts; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 102–111](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L102) | Callable definition: std::size_t crash_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) | calls fixture, fork, check, installed; guard Fixture fixture(plan,initial);const auto child=::fork();check(child&gt;=0,"promotion fork failed");; returns cuts; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 112–125](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L112) | Callable definition: std::size_t allocations(const PhysicalPlan& plan,const Database& initial) | calls fixture, report_metadata, plan, account; guard check(count==account.statistics().successful_allocations-before,"promotion allocations escaped orig…; returns count; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 126–126](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L126) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 127–139](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L127) | Callable definition: int main(int argc,char** argv) | calls check, c05_independent::boolean_fixture, c05_independent::lower, candidate; guard check(argc==3,"usage: reoptimization_promotion_fault SOURCE io\|crash\|allocation");const auto fixtur…; returns 0; 1; 1 loop sites · [reviewed contract](#b0015) |

## B0001

[Lines 1–20](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:7a18c89c91c9bf513ea6f0e7a99b87179f90a3a4706c59d72aec7026a7817251
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_promotion_fault_test.cpp: include "selection_independent_fixture.hpp", "indexed_runtime_fixture.hpp", "local_sink_fixture.hpp", "generation_file_probe.hpp", "journal_file_probe.hpp", "crown/runtime/session_reoptimization.hpp", &lt;cerrno&gt;, &lt;iostream&gt;, &lt;sys/wait.h&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. This filesystem Directory member owns the fixture namespace; its constructor/cleanup follows the documented filesystem effects of its helper type. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. This span declares a filesystem Directory member; its fixture construction/cleanup can perform filesystem I/O outside the native query account. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–28](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(const PhysicalPlan& plan,const Database& initial):session(QuerySession::create_typed(plan,initial)) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a journaled, sink-attached, paused session with three delivered epochs and preserve original durable bytes for promotion checks. |
| inputs / outputs | Input plan/database; creates checkpoint, original WAL, sink, commits/delivers seq 1..3, pauses, and snapshots old checkpoint/WAL/sink bytes and immutable sink header. |
| invariants | Promotion begins at delivered physical/command frontier 3. Fixture verifies old file bytes after promotion/recovery and later tests sequence 4; it does not test arbitrary prefixes. |
| ownership | Owns directory and session; copied file contents and origin Header are fixture-owned values. |
| failure | Setup checks reject missing input/output delivery; filesystem/native errors propagate. |
| cost | Creates checkpoint/WAL/sink, processes three one-row physical inputs and delivers all three epochs, then reads three original files. Sequence 1 is a duplicate insertion and may have empty output; the input-row count is not an output-row count. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § Fixture(const PhysicalPlan& plan,const Database& initial):session(QuerySession::create_typed(plan,initial)) (lines 21-28)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp) |

## B0003

[Lines 29–33](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit and deliver one specified physical input for the promotion prefix or the post-recovery continuation. |
| inputs / outputs | Sequence/table/op/row in; builds one event at wire offset sequence*10, requires enqueue/begin success, steps and commits via local_sink_test::finish, then delivers the still-pending output to the local sink and checks its sequence. |
| invariants | The helper expects one accepted event and exact matching delivery sequence; duplicate or non-monotone cases are outside the helper. |
| ownership | Batch is local; session and sink retain accepted state; row is borrowed during batch construction. |
| failure | Check fails on admission, begin, or delivery mismatch. |
| cost | One event, one native epoch, and one local sink delivery. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) (lines 29-33)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp) |

## B0004

[Lines 34–34](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void promote() {session->promote_journal(root,generation_test::options());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke journal promotion with the test generation options. |
| inputs / outputs | No input; calls promote_journal(root, generation_test::options()). |
| invariants | The fixture begins from a quiescent paused journal with three delivered epochs. |
| ownership | Uses fixture-owned path and session. |
| failure | Generation/journal errors propagate to the calling fault case. |
| cost | One checkpoint capture/encode plus creation of the next managed checkpoint, WAL and root, with their sync operations. This unchanged-plan journal promotion does not create a .plan descriptor. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § void promote() (lines 34-34)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp), [docs/reoptimization.md § Durable selection and sink lineage (lines 211-214)](../../../../reoptimization.md) |

## B0005

[Lines 35–38](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void original() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert promotion left all pre-existing unmanaged checkpoint, WAL, and sink bytes unchanged. |
| inputs / outputs | Reads the three fixture paths and compares them byte-for-byte with captured strings. |
| invariants | Checks only the exact original durable files captured at fixture construction. |
| ownership | File reads allocate ordinary strings; captured bytes remain owned by Fixture. |
| failure | check throws if any of the three returned byte strings differs. contents() does not explicitly check stream-open/read status, so this helper provides byte equality rather than a separate I/O-success assertion. |
| cost | Reads and compares each original file, proportional to their bytes. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § void original() const (lines 35-38)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/session_file_fixture.hpp § contents and descriptors (lines 26-31)](../../../../../tests/support/session_file_fixture.hpp) |

## B0006

[Lines 39–52](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void recover(const PhysicalPlan& plan,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover whichever complete selection the generation root actually names and verify the next delivered epoch. |
| inputs / outputs | Inputs original plan/database; after dropping the old owner, checks root existence and restores either selected generation+sink or original journal+sink. Confirms sequence/progress 3, paused state, one snapshot row, sink origin, selected generation metadata when present, then starts and commits sequence 4. |
| invariants | Root existence selects the restore path. Before sequence 4, the three original byte strings must match and recovery must report sequence/progress 3, paused state, one snapshot row, sink frontier 3 and exact origin header; a selected root must report generation/floor 2 with delivery. After sequence 4 only output generation, output row count 1 and empty snapshot are asserted. |
| ownership | Replaces fixture-owned session with recovered owner; recovery options and compiler program are local. |
| failure | Checks state, lineage and next native output; recovery/IO failures propagate. |
| cost | One restore plus one next input/delivery and local epoch read; comparisons scale with these small fixture files/rows. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § void recover(const PhysicalPlan& plan,const Database& initial) (lines 39-52)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § restore_journal_selected admission and tail repair (lines 773-847)](../../../../../src/runtime/session.cpp), [tests/support/local_sink_fixture.hpp § finish and output (lines 15-20)](../../../../../tests/support/local_sink_fixture.hpp) |

## B0007

[Lines 53–53](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L53); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L53:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_promotion_fault_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 54–74](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L54); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count generation and journal syscall-hook events, enforce sync ordering, fail selected operations, crash at a selected before/after event, and optionally deny allocation before root selection. |
| inputs / outputs | State: count/fail/crash ordinals, before-or-after selector, checkpoint/WAL sync flags, reached/order flags, deny flag. Static callbacks receive GenerationEvent or FileEvent. |
| invariants | count increments only on before events, combining both seams; after callbacks share that count. The before decision requests error_before/error_after at fail, with open/create after-errors normalized to before and close still executed by the wrappers. crash invokes _exit(77) at the matching before/after callback; deny zeros covered-new allowance just before root link. |
| ownership | Hook context is a stack Hook borrowed only while Installed is alive; counters own no file data. |
| failure | Callbacks are noexcept and return test decisions; hook installation/cleanup is in Installed. |
| cost | Constant work per hook event. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § struct Hook (lines 54-74)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/recovery/generation.cpp § GenerationOwner::call (lines 132-181)](../../../../../src/recovery/generation.cpp), [src/recovery/journal_file.cpp § File::call (lines 61-113)](../../../../../src/recovery/journal_file.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp) |

## B0009

[Lines 75–78](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L75); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install and clear both generation and journal testing hooks for one scoped fault operation. |
| inputs / outputs | Input Hook reference; registers generation and journal callbacks and clears both in destructor. |
| invariants | Setters overwrite thread-local callback/context pairs and do not stack. This scope assumes exclusive use on the current thread; destruction resets both pairs to null rather than restoring a previous installation. |
| ownership | Borrows Hook for its scope; no allocation or dynamic payload. |
| failure | Destructor clears both hooks on normal C++ scope exit or stack unwinding. _exit in a crash child bypasses this destructor and terminates that child. |
| cost | Two setter calls on entry and two on exit. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § struct Installed (lines 75-78)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/recovery/generation.cpp § set_generation_hook (lines 16-20)](../../../../../src/recovery/generation.cpp), [src/recovery/journal_file.cpp § set_file_hook (lines 13-18)](../../../../../src/recovery/journal_file.cpp) |

## B0010

[Lines 79–84](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t trace(const PhysicalPlan& plan,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one promotion syscall trace and prove instrumented allocation is denied at the root-link selection boundary. |
| inputs / outputs | Inputs plan/database; Fixture promotes under Hook with deny=true and s04 allocation count; returns total before-events counted. |
| invariants | Requires both checkpoint and WAL directory-sync observations before root linking; checks pause and old files. Trace length becomes the bound for later finite cut loops. |
| ownership | Fixture/session and hook are scoped; hooks cleared before recovery. |
| failure | Assertions reject wrong sync order, allocation after denial, missing root-link event or changed state. |
| cost | One traced promotion and one recovery; returned count is an observed fixture-specific syscall-event bound. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § std::uint64_t trace(const PhysicalPlan& plan,const Database& initial) (lines 79-84)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [docs/reoptimization.md § Resource and failure verification (lines 283-288)](../../../../reoptimization.md) |

## B0011

[Lines 85–101](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t io_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request before- and after-error decisions at each calibrated promotion syscall ordinal, then recover the surviving original or promoted state. |
| inputs / outputs | Inputs plan/database/boundary count; for each ordinal and before/after position creates a fresh fixture, installs Hook error, promotes, checks GenerationFailure/FileFailure, unchanged originals and either latched uncertain root lock or unchanged old owner, then recovers. |
| invariants | boundaries is the successful same-backend trace count. Error decisions follow wrapper open/create and close rules. If journal recovery_required is set, begin_next must reject and a second root lock must fail busy; otherwise generation remains disabled at committed sequence 3. |
| ownership | Each iteration owns new temp files, session, and hook; recovery replaces the session only after failed promoter teardown. |
| failure | Each selected cut must fail; recovery must produce complete sequence-3 state and next sequence-4 output. |
| cost | 2×observed-boundaries promotions per backend; each performs file comparisons and a recovery. The finite seam is not a kill at every machine instruction. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § std::size_t io_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) (lines 85-101)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [src/recovery/generation.cpp § GenerationOwner::call (lines 132-181)](../../../../../src/recovery/generation.cpp), [src/recovery/journal_file.cpp § File::call (lines 61-113)](../../../../../src/recovery/journal_file.cpp), [src/runtime/session.cpp § SelectionGuard (lines 376-391)](../../../../../src/runtime/session.cpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp) |

## B0012

[Lines 102–111](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t crash_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fork one child per observed before/after promotion event and require the child to exit at the exact injected crash hook. |
| inputs / outputs | Inputs plan/database/boundary count; child installs Hook with crash ordinal and calls promotion; parent waitpid checks exit 77, original bytes and recovery state. |
| invariants | The cut is \`_exit(77)\` at an instrumented syscall event. It does not model kernel cache loss, host power loss, or instruction-by-instruction process death. |
| ownership | Each parent iteration constructs a Fixture, then fork gives the child inherited process state and file descriptors. Only the child installs the crash hook; the parent waits and replaces its own session during recover. |
| failure | Requires fork/wait success, normal exit status 77, and successful recovery; otherwise check fails. |
| cost | Two child processes per measured syscall ordinal per backend; parent-side setup builds each fixture before fork, child performs promotion, and parent checks originals and recovers. CTest supplies an external timeout; the helper itself has no elapsed-time guard. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § std::size_t crash_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) (lines 102-111)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/generation_file_probe.hpp § GenerationEvent (lines 5-9)](../../../../../tests/support/generation_file_probe.hpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp) |

## B0013

[Lines 112–125](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t allocations(const PhysicalPlan& plan,const Database& initial) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure promotion allocator calls and fail each observed instrumented allocation before root selection. |
| inputs / outputs | Inputs plan/database; first measures \`s04_alloc::calls\` and checks equality with original account successful-allocation delta, then sweeps each ordinal in a fresh fixture. |
| invariants | Count must be between 1 and 9999. Every allocation failure must leave generation disabled, journal healthy, original durable bytes intact and recovery successful. This allocator seam does not intercept all C++/C allocations. |
| ownership | The original query account owns native allocations; each fixture and hook scope is destroyed before next ordinal. |
| failure | Each cut must trigger bad_alloc and preserve old authoritative state. |
| cost | N measured calls imply N fresh promotion fault runs and recoveries per backend. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § std::size_t allocations(const PhysicalPlan& plan,const Database& initial) (lines 112-125)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/index_allocation.hpp § replacement new/delete and nonnested thread-local Scope (lines 11-70)](../../../../../tests/support/index_allocation.hpp), [src/runtime/session.cpp § promote_journal (lines 965-989)](../../../../../src/runtime/session.cpp) |

## B0014

[Lines 126–126](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L126); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L126:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_promotion_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 127–139](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select I/O-fault, process-crash, or allocation-promotion campaigns from the exact command argument. |
| inputs / outputs | Requires source path plus mode; loads Boolean fixture and runs both backends using candidate 0, tracing each backend before the chosen campaign. |
| invariants | Only exact string \`io\` selects I/O cuts and exact \`crash\` selects fork cuts; every other mode string takes the allocation branch. The main reports the passed mode text, so the accepted argument vocabulary is not validated. |
| ownership | Main owns fixture/plans; each campaign creates isolated durable directories. |
| failure | Requires argc 3; std::exception prints and returns 1. Unknown mode is not a rejection. |
| cost | Two backends × one trace plus either finite I/O cuts, crash children, or N allocation sweeps. |
| Design | [tests/unit/reoptimization_promotion_fault_test.cpp § int main(int argc,char** argv) (lines 127-139)](../../../../../tests/unit/reoptimization_promotion_fault_test.cpp), [tests/support/selection_independent_fixture.hpp § BooleanFixture and boolean_fixture (lines 111-157)](../../../../../tests/support/selection_independent_fixture.hpp), [CMakeLists.txt § promotion io/crash/allocation registrations (lines 690-697)](../../../../../CMakeLists.txt) |

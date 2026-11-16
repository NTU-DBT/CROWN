# `tests/unit/session_journal_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_journal_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `70d46d365c59d8b3e9672f88b2927d1c9e82e316df6d8e823d7d92ccf7db27a0`. 99 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/session_journal_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–18](../../../../../tests/unit/session_journal_fault_test.cpp#L9) | Type/record definition: struct Hook | returns result · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/unit/session_journal_fault_test.cpp#L19) | Type/record definition: struct Installed |  · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tests/unit/session_journal_fault_test.cpp#L20) | Callable definition: void attempt(Fixture& f,bool commit) | calls commit, check, begin_next; guard void attempt(Fixture& f,bool commit){if(commit)f.session-&gt;commit();else check(f.session-&gt;begin_next… · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/unit/session_journal_fault_test.cpp#L21) | Callable definition: Hook trace(bool commit) | calls offer, prepare, installed, attempt; returns hook · [reviewed contract](#b0005) |
| [B0006 · 22–41](../../../../../tests/unit/session_journal_fault_test.cpp#L22) | Type/record definition: struct WindowFixture | guard check(session-&gt;begin_next(),"window fault head missing");; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 42–42](../../../../../tests/unit/session_journal_fault_test.cpp#L42) | Callable definition: Hook window_trace(unsigned kind) | calls f, installed, attempt; returns hook · [reviewed contract](#b0007) |
| [B0008 · 43–58](../../../../../tests/unit/session_journal_fault_test.cpp#L43) | Callable definition: void window_faults() | calls window_trace, f, status, installed; guard check(failed && f.session-&gt;journal_state().recovery_required && f.session-&gt;status().committed_seque…; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 59–81](../../../../../tests/unit/session_journal_fault_test.cpp#L59) | Callable definition: void faults() | calls trace, offer, prepare, installed; guard check(rejected && f.session-&gt;journal_state().recovery_required && f.session-&gt;status().committed_seq…; 4 loop sites · [reviewed contract](#b0009) |
| [B0010 · 82–97](../../../../../tests/unit/session_journal_fault_test.cpp#L82) | Callable definition: void crashes() | calls trace, offer, prepare, contents; guard const pid_t child=::fork();check(child&gt;=0,"fork failed");if(child==0){Hook hook;hook.crash_at=point…; 3 loop sites; source comment (unverified): // Parent releases its inherited lock after the child exits; its stale · [reviewed contract](#b0010) |
| [B0011 · 98–98](../../../../../tests/unit/session_journal_fault_test.cpp#L98) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 99–99](../../../../../tests/unit/session_journal_fault_test.cpp#L99) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, faults; guard int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv\[1\])=="cr…; returns 1 · [reviewed contract](#b0012) |

## B0001

[Lines 1–8](../../../../../tests/unit/session_journal_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:2cb78baf4380d7c6ed25f14eaf4ec572d0669b3394064f8024703b29f8963c71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_journal_fault_test.cpp: include "session_journal_fixture.hpp", "journal_file_probe.hpp", &lt;sys/wait.h&gt;, &lt;cerrno&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–18](../../../../../tests/unit/session_journal_fault_test.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe session-journal syscalls, retain a bounded event sample, and inject before/after errors or exit. |
| inputs / outputs | FileEvent and borrowed Hook context; counts before events, copies at most 128 observations, may exit child 77, returns FileDecision. |
| invariants | Only a successful after-sync event arms S04 allocation denial; injected error side follows \`after\`; retained event sample is truncated safely at capacity. |
| ownership | Installed borrows Hook; fixed std::array stores event values without heap allocation. |
| failure | Callback is noexcept; real journal/session code surfaces file failure or process termination. |
| cost | Constant callback updates and at most 128 stack-resident events per Hook. |
| Design | tests/unit/session_journal_fault_test.cpp:9-18, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 19–19](../../../../../tests/unit/session_journal_fault_test.cpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {explicit Installed(Hook& hook){jp::testing::set_file_hook(Hook::call,&hook);}~Installed(){jp::testing::set_file_hook(nullptr,nullptr);}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install and clear the per-thread journal syscall callback. |
| inputs / outputs | Hook reference in; setter installs file hook; destructor nulls it. |
| invariants | A previous hook is not stacked; context must outlive the scope. |
| ownership | Installed borrows Hook and is scoped around one trace or operation. |
| failure | No error mapping at this seam. |
| cost | One setter and one reset. |
| Design | tests/unit/session_journal_fault_test.cpp:19-19, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0004

[Lines 20–20](../../../../../tests/unit/session_journal_fault_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void attempt(Fixture& f,bool commit){if(commit)f.session->commit();else check(f.session->begin_next(),"journal input missing");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start one input or cross the prepared commit barrier for the session fault fixture. |
| inputs / outputs | Fixture and boolean in; false path calls begin_next; true path calls commit. |
| invariants | Callers prepare the epoch before commit path; false path deliberately tests durable input before native preparation. |
| ownership | Fixture retains session/checkpoint/journal; this helper borrows it. |
| failure | Missing source input assertion or journal FileFailure propagates. |
| cost | One journal input or decision operation. |
| Design | tests/unit/session_journal_fault_test.cpp:20-20, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0005

[Lines 21–21](../../../../../tests/unit/session_journal_fault_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(bool commit) {Fixture f;f.offer();if(commit)f.prepare();Hook hook;{Installed installed(hook);attempt(f,commit);}return hook;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count syscall boundaries for either input append or commit decision. |
| inputs / outputs | Commit selector in; Fixture offers source and may prepare, then one \`attempt\` runs under Hook. |
| invariants | No injected failure is configured; returned count describes current actual syscall path only. |
| ownership | Fixture/session and hook context are local; Installed clears the callback before return. |
| failure | Setup or journal failure aborts trace. |
| cost | One input or decision attempt. |
| Design | tests/unit/session_journal_fault_test.cpp:21-21, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0006

[Lines 22–41](../../../../../tests/unit/session_journal_fault_test.cpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a window-journal fixture at an insertion, watermark, or partial-watermark barrier. |
| inputs / outputs | Mode 0-3 selects no begin, prepared insertion, first watermark step, or second step after one completed expiration. |
| invariants | Before-window snapshot and committed progress capture the recovery boundary; mode 3 confirms first step accepted command has not yet advanced; attempt starts input for mode 0 and commits prepared work for other modes. |
| ownership | Directory owns checkpoint/WAL paths; QuerySession owns queue/runtime and journal file lock; before_window is a value snapshot. |
| failure | Missing command or wrong prepared/substep state fails before syscall faulting. |
| cost | Two initial window inserts and at most one extra watermark substep; fixed small window state. |
| Design | tests/unit/session_journal_fault_test.cpp:22-41, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0007

[Lines 42–42](../../../../../tests/unit/session_journal_fault_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook window_trace(unsigned kind){WindowFixture f(kind);Hook hook;{Installed installed(hook);f.attempt();}return hook;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count actual syscall boundaries for one window input/decision attempt. |
| inputs / outputs | Window mode in; constructs matching WindowFixture and calls \`attempt\` under Hook. |
| invariants | The same mode defines baseline and faulted operation state. |
| ownership | Fixture dies after Installed; returned Hook contains only scalar counts and event samples. |
| failure | Setup or journal failures abort baseline. |
| cost | One window input or decision attempt. |
| Design | tests/unit/session_journal_fault_test.cpp:42-42, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0008

[Lines 43–58](../../../../../tests/unit/session_journal_fault_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every journal syscall around window input, first/final physical, and metadata substep publication. |
| inputs / outputs | Four fixture modes; every baseline event gets before/after error; checks recovery_required, source/physical/window snapshots and scanned WAL progress. |
| invariants | No failed decision acknowledges a command or publishes private physical/metadata state; committed physical sequence stays 2 and WAL command remains 2-3; after a successful sync, allocation denial does not prevent nonthrowing publication. |
| ownership | Each fault case owns fresh WindowFixture/Hook; event scans borrow copied WAL string only during validation. |
| failure | Only journal FileFailure counts as injected failure; state drift, a false durable publication or nonalloc failure fails assertions. |
| cost | Four modes times two sides for each measured boundary; modes 1–3 also test one post-sync denial under S04, with at most two extra window steps. |
| Design | tests/unit/session_journal_fault_test.cpp:43-58, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0009

[Lines 59–81](../../../../../tests/unit/session_journal_fault_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault actual input or commit-decision appends and check rollback, uncertain blocking, reopenability, and nonallocating publication. |
| inputs / outputs | Input/commit selector and each baseline event/side; then clean prepared attempt with S04 denial at successful sync. |
| invariants | Journal I/O error sets recovery_required, leaves native progress/committed sequence at zero, blocks output, and does not invent more than the valid input record; writer lock is released after owner reset; commit after durable sync publishes without allocation. |
| ownership | Fixture's account is retained before resetting QuerySession; journal File opens independently only after old owner releases its lock. |
| failure | Expected FileFailure during fault; a later direct journal open must succeed; any output or stuck lock is a failure. |
| cost | Two operation classes times two sides per observed boundary, plus one clean denied-new commit each and one drain path; small one-input fixtures. |
| Design | tests/unit/session_journal_fault_test.cpp:59-81, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0010

[Lines 82–97](../../../../../tests/unit/session_journal_fault_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit child at each input/decision syscall boundary and read the valid journal prefix from the parent. |
| inputs / outputs | Input/commit selector, baseline ordinal and side; fork child attempts operation then parent waits and reopens File after resetting session. |
| invariants | Accepted prefix respects command/physical decision boundary; process exit around syscalls is not a power-loss durability test. |
| ownership | Child inherits process/file state; parent keeps QuerySession until explicit reset after waitpid, then uses its account to open the actual WAL. |
| failure | The source comment is accurate: parent releases inherited lock only after child exits and discards stale session before opening; fork/wait/status or prefix mismatch fails. |
| cost | Two operation classes times two sides per measured boundary; parent reopens and scans each small file. |
| Design | tests/unit/session_journal_fault_test.cpp:82-97, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

## B0011

[Lines 98–98](../../../../../tests/unit/session_journal_fault_test.cpp#L98); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L98-L98:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_journal_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_journal_fault_test.cpp](../../../../../tests/unit/session_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 99–99](../../../../../tests/unit/session_journal_fault_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv[1])=="crash")crashes();else {faults();window_faults();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select child crash mode or run the journal, window, and drain syscall-failure suites. |
| inputs / outputs | One mode argument chooses crashes; otherwise faults and window_faults execute. |
| invariants | Inner matrices determine the tested syscall counts and state assertions. |
| ownership | main owns no test resources; suite stack scopes manage all callback and session lifetimes. |
| failure | Wrong argument count or standard exception reports status 1. |
| cost | One bounded mode suite. |
| Design | tests/unit/session_journal_fault_test.cpp:99-99, docs/session-journal.md:25-72, docs/journal-files.md:37-66, src/runtime/session.cpp:286-345, src/runtime/session.cpp:1449-1476, src/recovery/journal_file.cpp:231-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/journal_file_probe.hpp:1-17, tests/support/index_allocation.hpp:11-70 |

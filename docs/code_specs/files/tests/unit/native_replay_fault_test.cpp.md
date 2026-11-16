# `tests/unit/native_replay_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/native_replay_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4d34ce596d3e3463685a212a1f42443c08b97064c7898380a38c6fbce56b36fa`. 83 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../tests/unit/native_replay_fault_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 10–22](../../../../../tests/unit/native_replay_fault_test.cpp#L10) | Type/record definition: struct Saved | guard void write(std::string_view data){std::ofstream out(fixture.log,std::ios::binary\|std::ios::trunc);o…; returns result; QuerySession::restore_journal(compiler,fixture.checkpoint,fixture.log,options()); 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 23–31](../../../../../tests/unit/native_replay_fault_test.cpp#L23) | Type/record definition: struct Hook | returns result · [reviewed contract](#b0003) |
| [B0004 · 32–32](../../../../../tests/unit/native_replay_fault_test.cpp#L32) | Type/record definition: struct Installed |  · [reviewed contract](#b0004) |
| [B0005 · 33–36](../../../../../tests/unit/native_replay_fault_test.cpp#L33) | Callable definition: void verify(QuerySession& session) | calls check, status, progress, recovery_status; guard check(session.status().state==SessionState::paused && session.progress().sequence==2 && session.sta…; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 37–48](../../../../../tests/unit/native_replay_fault_test.cpp#L37) | Callable definition: void allocation_faults() | calls emplace, restore, get_deleter, account; guard const auto account=result-&gt;get_deleter().account();check(allocations==account.statistics().successf…; growth emplace; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../tests/unit/native_replay_fault_test.cpp#L49) | Callable definition: Hook trace(Saved& saved) | calls write, installed, restore; returns h · [reviewed contract](#b0007) |
| [B0008 · 50–68](../../../../../tests/unit/native_replay_fault_test.cpp#L50) | Callable definition: void io_faults() | calls saved, trace, write, descriptors; guard check(failed && descriptors()==fds,"recovery syscall error escaped/leaked descriptor");const auto a…; 3 loop sites · [reviewed contract](#b0008) |
| [B0009 · 69–81](../../../../../tests/unit/native_replay_fault_test.cpp#L69) | Callable definition: void crashes() | calls saved, trace, write, fork; guard saved.write(saved.bytes);const auto child=::fork();check(child&gt;=0,"fork failed");; 3 loop sites · [reviewed contract](#b0009) |
| [B0010 · 82–82](../../../../../tests/unit/native_replay_fault_test.cpp#L82) | Closes surrounding scope/type. |  · [reviewed contract](#b0010) |
| [B0011 · 83–83](../../../../../tests/unit/native_replay_fault_test.cpp#L83) | Callable definition: int main(int argc,char** argv) | calls check, std::string_view, crashes, allocation_faults; guard int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv\[1\])=="cr…; returns 1 · [reviewed contract](#b0011) |

## B0001

[Lines 1–9](../../../../../tests/unit/native_replay_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:7e152f40c89251fcd062bd5b7eaf88b49a3d049240851406619adf68d8c03672
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare native_replay_fault_test.cpp: include "session_journal_fixture.hpp", "journal_file_probe.hpp", &lt;sys/wait.h&gt;, &lt;fstream&gt;, &lt;cerrno&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/native_replay_fault_test.cpp](../../../../../tests/unit/native_replay_fault_test.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 10–22](../../../../../tests/unit/native_replay_fault_test.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Saved {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a reusable committed-plus-pending journal fixture and its restore tools. |
| inputs / outputs | A torn toggle selects a fixture with two committed rows, a prepared third input and optionally the first 20 bytes of its decision; members write exact WAL bytes, return shared options and restore the saved checkpoint/WAL. |
| invariants | Pending input remains complete without a commit; the optional 20-byte decision suffix is incomplete and must not become a commit; every rewrite targets only the fixture WAL. |
| ownership | Fixture owns directory, session and account; compiler and saved byte string are members; synthetic tail encoding uses a separate temporary MemoryAccount; returned recovery owner holds receiving account and journal lock. |
| failure | Fixture write failure becomes the test assertion carrier; restore failures keep native file/image/journal categories. |
| cost | Two committed changes, one prepared input, optional 20-byte suffix, and one file rewrite or full restore per use. |
| Design | tests/unit/native_replay_fault_test.cpp:10-22, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0003

[Lines 23–31](../../../../../tests/unit/native_replay_fault_test.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Hook {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject before/after journal syscalls and support short reads and repeated interruption. |
| inputs / outputs | FileEvent and borrowed Hook context; returns FileDecision or exits selected child with status 77. |
| invariants | Before events alone change count and injected errors; after errors model post-syscall uncertainty; max transfer applies per requested I/O. |
| ownership | Installed borrows Hook; the event is observed synchronously and is not retained by callback. |
| failure | Callback is noexcept; the journal File/Session recovery layer returns its native failure category. |
| cost | Constant per-event decision; no history buffer. |
| Design | tests/unit/native_replay_fault_test.cpp:23-31, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0004

[Lines 32–32](../../../../../tests/unit/native_replay_fault_test.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Installed {explicit Installed(Hook& h){jp::testing::set_file_hook(Hook::call,&h);}~Installed(){jp::testing::set_file_hook(nullptr,nullptr);}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install and clear one thread-local journal file callback with scoped lifetime. |
| inputs / outputs | Hook reference in; sets jp::testing file hook; clears it on scope exit. |
| invariants | Caller must keep Hook alive until Installed destruction; no nested prior hook is restored. |
| ownership | Installed borrows the test-local Hook. |
| failure | Setter/cleanup are test instrumentation only; file errors are thrown by the real API path. |
| cost | One setter and one clear. |
| Design | tests/unit/native_replay_fault_test.cpp:32-32, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0005

[Lines 33–36](../../../../../tests/unit/native_replay_fault_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reconstructed pending state, committed output identity and receiving session control. |
| inputs / outputs | A restored session reference in; asserts paused status, physical/source counters, pending sequence and one exact recovered tuple. |
| invariants | The third input remains pending at sequence 3 while committed sequence is 2; recovered output belongs only to physical epoch 2. |
| ownership | QuerySession owns its output and account; optional recovered result owns/transfers native tuple payload as defined by API. |
| failure | Any status/source/tuple mismatch fails via typed assertion. |
| cost | One status read and one recovered-output drain, expecting exactly one row. |
| Design | tests/unit/native_replay_fault_test.cpp:33-36, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0006

[Lines 37–48](../../../../../tests/unit/native_replay_fault_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault every receiving-account allocation and prove replay heap admission has an exact boundary. |
| inputs / outputs | A successful restore counts S04 calls and captures account peak; each position faults a fresh restore; exact and one-under memory limits are compared. |
| invariants | The S04 count is intercepted C++ new attempts and must equal account successful allocation statistics for the clean restore; count is not bytes; one-under cap rejects as MemoryFailure. |
| ownership | Each restore owns a fresh account/file lock and is destroyed before descriptor/file checks; account statistics are read from its deleter. |
| failure | Every selected new position must throw bad_alloc without changing WAL or leaking descriptors; verify() must pass on a clean owner. |
| cost | One measured restore, one rebuild/replay per intercepted new call, and two memory-cap-edge restores. |
| Design | tests/unit/native_replay_fault_test.cpp:37-48, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0007

[Lines 49–49](../../../../../tests/unit/native_replay_fault_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Hook trace(Saved& saved){saved.write(saved.bytes);Hook h;{Installed installed(h);auto value=saved.restore();}return h;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count actual journal read/replay I/O boundaries for clean or torn saved bytes. |
| inputs / outputs | Saved restores the exact bytes under Hook; returns call count for fault matrix. |
| invariants | No injected fault is configured; actual prefix scan defines ordinals for the same fixture state. |
| ownership | Temporary restore owner and Installed callback end before the count is used. |
| failure | Normal recovery failures prevent a valid baseline and propagate. |
| cost | One read-only recovery pass for the two-record prefix, with or without 20-byte suffix. |
| Design | tests/unit/native_replay_fault_test.cpp:49-49, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0008

[Lines 50–68](../../../../../tests/unit/native_replay_fault_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void io_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject before/after read errors at all recovery boundaries and check repair/quota behavior. |
| inputs / outputs | For clean and torn input, every observed syscall edge is failed on both sides; a fresh restore must verify state/output afterward. |
| invariants | Complete committed prefix remains; a torn final 20-byte suffix may be truncated only by successful recovery; a 3-byte transfer succeeds; repeated EINTR is bounded by copied 30-operation quota. |
| ownership | Each attempt uses a fresh hook and temporary receiving owner; descriptors are compared after failed construction. |
| failure | Expected jp::FileFailure is required at injected edge; test permits only unchanged bytes or the one defined torn-suffix removal. |
| cost | Two tail states times two sides per baseline boundary, plus one short-read and one bounded interrupt case per tail state. |
| Design | tests/unit/native_replay_fault_test.cpp:50-68, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0009

[Lines 69–81](../../../../../tests/unit/native_replay_fault_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void crashes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exit child at each journal recovery syscall and validate restart from the parent. |
| inputs / outputs | Clean/torn Saved, observed ordinal and before/after side; child invokes restore under Hook, parent waits then restores/verifies. |
| invariants | This is a process-exit test at instrumented syscall boundaries, not a power-loss simulation; pending input and recovered output remain expected. |
| ownership | Child owns temporary restore result; parent retains and rewrites its exact fixture bytes before each point. |
| failure | Fork/wait status mismatch or recovery mismatch fails; child's exception status differs from the expected hook code. |
| cost | Two tail states times two sides per observed boundary; one bounded parent reconstruction per process exit. |
| Design | tests/unit/native_replay_fault_test.cpp:69-81, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

## B0010

[Lines 82–82](../../../../../tests/unit/native_replay_fault_test.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in native_replay_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/native_replay_fault_test.cpp](../../../../../tests/unit/native_replay_fault_test.cpp), [docs/native-replay.md](../../../../native-replay.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 83–83](../../../../../tests/unit/native_replay_fault_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv[1])=="crash")crashes();else{allocation_faults();io_faults();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the child crash matrix or allocation and syscall-failure matrix. |
| inputs / outputs | Exactly one mode argument chooses crashes; otherwise runs allocation and I/O fault suites. |
| invariants | All modes are finite and defined by actual trace counts. |
| ownership | main owns only dispatch; each suite owns fixtures/hooks. |
| failure | Wrong argc or standard exception returns 1 with diagnostic. |
| cost | One bounded suite invocation. |
| Design | tests/unit/native_replay_fault_test.cpp:83-83, docs/native-replay.md:16-43, docs/native-replay.md:69-100, docs/journal-files.md:27-66, src/runtime/session.cpp:630-657, src/runtime/session.cpp:765-846, src/recovery/journal_file.cpp:199-254, tests/support/session_journal_fixture.hpp:17-40, tests/support/index_allocation.hpp:11-70 |

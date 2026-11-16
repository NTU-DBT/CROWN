# `tests/unit/journal_file_test.cpp` — block usage map

[Source](../../../../../tests/unit/journal_file_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9d7bcf96c333a3512b2f0103a8e72d4a5fdd2bf940d10cff7dc9a8272565e766`. 107 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/journal_file_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–10](../../../../../tests/unit/journal_file_test.cpp#L8) | Callable definition: template&lt;class Action&gt; void file_rejected(Action action,jp::FileFault expected) | calls action, fault, check; guard bool failed=false;try{action();}catch(const jp::FileFailure& error){failed=error.fault()==expected;… · [reviewed contract](#b0002) |
| [B0003 · 11–39](../../../../../tests/unit/journal_file_test.cpp#L11) | Callable definition: void basic(const Frames& f) | calls file, resource::MemoryAccount::create, statistics, emplace; guard check(account.statistics().successful_allocations-before==allocations,"journal create C++ new/accou…; growth emplace · [reviewed contract](#b0003) |
| [B0004 · 40–70](../../../../../tests/unit/journal_file_test.cpp#L40) | Callable definition: void recovery_cases(const Frames& f) | calls file, resource::MemoryAccount::create, size, put; guard check(state.consumed==complete && state.torn_tail==(cut!=complete),"file prefix cut differs");; 3 loop sites; source comment (unverified): // Open retains complete Input records and reports incomplete trailing bytes. · [reviewed contract](#b0004) |
| [B0005 · 71–105](../../../../../tests/unit/journal_file_test.cpp#L71) | Callable definition: void resources_and_paths(const Frames& f) | calls file, put, resource::MemoryAccount::create, statistics; guard {auto receiving=resource::MemoryAccount::create(4*1024*1024);const auto before=receiving.statistics…; 4 loop sites; source comment (unverified): // Intercepted C++ new failures during create precede file publication. · [reviewed contract](#b0005) |
| [B0006 · 106–106](../../../../../tests/unit/journal_file_test.cpp#L106) | Closes surrounding scope/type. |  · [reviewed contract](#b0006) |
| [B0007 · 107–107](../../../../../tests/unit/journal_file_test.cpp#L107) | Callable definition: int main(int argc,char** argv) | calls check, f, basic, recovery_cases; guard int main(int argc,char** argv) {try{check(argc==2,"expected fixture directory");const Frames f(argv…; returns 1 · [reviewed contract](#b0007) |

## B0001

[Lines 1–7](../../../../../tests/unit/journal_file_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:b06db7bbd7d4933d5e02ab23235c11eb5d25f2929b74c4970312e1698761ef6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare journal_file_test.cpp: include "journal_file_fixture.hpp", "index_allocation.hpp", &lt;sys/wait.h&gt;, &lt;fcntl.h&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–10](../../../../../tests/unit/journal_file_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void file_rejected(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a journal-file action to fail with one exact FileFault. |
| inputs / outputs | Invokes the supplied callable once; compares a caught FileFailure fault with expected and returns void. |
| invariants | Success or another FileFault fails the fixture; codec/native exceptions are not accepted by this helper. |
| ownership | Borrows the callable captures for the call and retains no File or pending-frame view. |
| failure | Only FileFailure is caught; other exceptions propagate to the executable boundary. A failed predicate throws the fixture runtime_error. |
| cost | One invocation plus fixed comparison; action I/O/codec work is additional. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [include/crown/recovery/journal_file.hpp](../../../../../include/crown/recovery/journal_file.hpp), [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp) |

## B0003

[Lines 11–39](../../../../../tests/unit/journal_file_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void basic(const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exclusive journal creation, real writer ownership, append/reopen state and mutation rejection. |
| inputs / outputs | Uses frozen header/input and a production-encoded Commit; creates one private file, forks a competing opener and exercises create/open/append/move/close. |
| invariants | Header mode is 0600; both same-process and child competing writers get busy. Complete input/decision bytes survive reopen; wrong generation, existing destination and externally appended bytes are rejected without replacement. |
| ownership | Directory owns fixture paths; File owns the actual descriptor/flock and account buffers. Pending frame is inspected before another append; the saved borrowed view is never dereferenced after that append. Moved-from/closed File state rejects. |
| failure | Exact FileFault checks distinguish busy/state/changed; wrong binding uses codec Failure. Parent validates child exit and receiving-account return to its initial resident statistics. |
| cost | Several bounded record scans/writes, one fork/wait and explicit whole-file test copies. C++ replacement-new counts are compared with account successful allocations; this is not a libc/RSS proof. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 40–70](../../../../../tests/unit/journal_file_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void recovery_cases(const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise every input/decision truncation boundary and preservation of complete pending/window state. |
| inputs / outputs | Rewrites one fixture file at every cut, reopens it, explicitly repairs only an incomplete suffix and completes the remaining decision; also mutates every byte and constructs one partial watermark continuation. |
| invariants | Open itself never repairs. repair_tail retains every complete Input and committed window substep; incomplete mandatory headers and complete corruption reject. Window physical C may advance before command I completes. |
| ownership | Each trial closes its File before rewriting the path. Encoded window header/input/Commit and assembled prefix remain alive while their views are used. |
| failure | Torn owners reject append until explicit repair. Malformed headers and corrupted complete frames must reject without changing bytes; the final metadata substep clears the retained pending input. |
| cost | For B fixture bytes, O(B) cut/corruption trials each scan/copy up to B bytes: aggregate test work can be quadratic, plus filesystem calls. This is a bounded test corpus, not append complexity. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [include/crown/recovery/journal.hpp](../../../../../include/crown/recovery/journal.hpp) |

## B0005

[Lines 71–105](../../../../../tests/unit/journal_file_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resources_and_paths(const Frames& f)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check receiving-account caps, injected C++ allocation failures, finite scan limits and safe path admission. |
| inputs / outputs | Measures a successful open peak/count, retries exact/one-under memory and byte/work/record caps, sweeps observed create/open allocation positions and tests an append preallocation failure plus malformed/FIFO/symlink paths. |
| invariants | Failed create must publish no destination; failed open returns account/descriptor counts. Commit-buffer failure leaves disk, cursor and operation count unchanged and permits same-owner retry. Symlinks/FIFOs are not adopted as regular journals. |
| ownership | Each trial owns its File and MemoryAccount lexically; temporary path names and original frame bytes remain fixture-owned. Peak is requested account bytes, separate from replacement-new calls. |
| failure | MemoryFault::limit is required for one-under receiving memory. Injected bad_alloc and codec/file scan rejection are checked separately; all other exceptions escape to main. |
| cost | Repeats full scans for each measured allocation cut and each cap/path case. The hook covers the explicit ordinary/aligned/nothrow global-new overloads, not direct libc or exception-ABI allocation. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [docs/journal-files.md](../../../../journal-files.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 106–106](../../../../../tests/unit/journal_file_test.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L106:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in journal_file_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 107–107](../../../../../tests/unit/journal_file_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the three journal-file functional/resource groups using the supplied fixture directory. |
| inputs / outputs | Requires one fixture-directory argument, constructs Frames and invokes basic, recovery_cases and resources_and_paths. |
| invariants | Frozen header/input fixtures and the production-encoded Commit are distinct evidence sources; merely authoring this contract does not execute them. |
| ownership | Frames and all subordinate fixture owners release before process exit; each group owns its own temporary directory. |
| failure | The final std::exception boundary prints what() and returns one; normal completion reaches implicit return zero. |
| cost | Executes all bounded groups sequentially; their scans, fork and fault sweeps dominate the fixed dispatch. |
| Design | [tests/unit/journal_file_test.cpp](../../../../../tests/unit/journal_file_test.cpp), [tests/support/journal_file_fixture.hpp](../../../../../tests/support/journal_file_fixture.hpp) |

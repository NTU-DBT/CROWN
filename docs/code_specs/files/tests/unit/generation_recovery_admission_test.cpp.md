# `tests/unit/generation_recovery_admission_test.cpp` — block usage map

[Source](../../../../../tests/unit/generation_recovery_admission_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `75bb18c618c8656a56ec3697f347e481ea7167f8de4bad2bee83ac93b9e1c5c1`. 96 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/generation_recovery_admission_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0001) |
| [B0002 · 13–25](../../../../../tests/unit/generation_recovery_admission_test.cpp#L13) | Callable definition: explicit Fixture(bool indexed) : source(indexed), program(CompiledProgram::standalone(source.query.test.plan)), wal(generation_te… | calls source, program, CompiledProgram::standalone, wal; guard check(source.query.session-&gt;deliver_local_epoch().sequence == i + 1, "legacy delivery missed an epo…; growth emplace; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/generation_recovery_admission_test.cpp#L26) | Callable definition: void reset() const | calls generation_test::put; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 27–30](../../../../../tests/unit/generation_recovery_admission_test.cpp#L27) | Callable definition: void intact() const | calls check, session_file_test::contents; guard check(session_file_test::contents(path) == bytes, "rejected legacy recovery changed durable files");; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 31–33](../../../../../tests/unit/generation_recovery_admission_test.cpp#L31) | Callable definition: QuerySession::Owner restore(SessionGenerationRecoveryOptions options = generation_test::recovery_options()) | calls generation_test::recovery_options, QuerySession::restore_generation_with_local_sink, local_sink_test::options; returns QuerySession::restore_generation_with_local_sink(program, source.query.name, options, source.path, … · [reviewed contract](#b0005) |
| [B0006 · 34–48](../../../../../tests/unit/generation_recovery_admission_test.cpp#L34) | Callable definition: void verify(QuerySession& session) const | calls check, status, progress, local_sink_state; guard check(session.status().committed_sequence == 2 && session.progress().sequence == 2 &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../tests/unit/generation_recovery_admission_test.cpp#L49) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 50–89](../../../../../tests/unit/generation_recovery_admission_test.cpp#L50) | Callable definition: std::size_t sweep(bool indexed) | calls fixture, restore, accounted_memory_statistics, check; guard check(measured-&gt;successful_allocations == allocations, "legacy recovery C++ new/account counts diff…; returns allocations; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 90–90](../../../../../tests/unit/generation_recovery_admission_test.cpp#L90) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 91–96](../../../../../tests/unit/generation_recovery_admission_test.cpp#L91) | Callable definition: int main() | calls sweep, what; returns 1 · [reviewed contract](#b0010) |

## B0001

[Lines 1–12](../../../../../tests/unit/generation_recovery_admission_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:056768f1bb71b44b4ed88e1e9d4c8a394140dcac8d6f5b1e37cee877d6e75d2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare generation_recovery_admission_test.cpp: include "local_sink_fixture.hpp", &lt;map&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–25](../../../../../tests/unit/generation_recovery_admission_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Fixture(bool indexed) :
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save an actual legacy generation/local-sink image with two complete epochs and incomplete suffixes. |
| inputs / outputs | Constructs the chosen-backend sink fixture and standalone program, commits/delivers two epochs, releases the original session, appends CROWN to WAL and sink and saves root/sink/WAL/checkpoint bytes. |
| invariants | The saved suffixes are intentionally incomplete; complete accepted epochs remain at2. The compiler is genuine and no hand-built native state is imported. |
| ownership | Fixture owns private paths, compiler and ordinary saved-byte map. Original session locks are released before corrupting/restoring the test files. |
| failure | Fixture commit/delivery or file I/O failure escapes; setup does not infer a valid baseline from a failed operation. |
| cost | Two native/delivery epochs, whole selected-file copies and two short suffix writes per backend fixture. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [docs/generations.md](../../../../generations.md) |

## B0003

[Lines 26–26](../../../../../tests/unit/generation_recovery_admission_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reset() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore the exact saved torn-file fixture before a new receiving-admission trial. |
| inputs / outputs | Rewrites every path in saved with its complete saved bytes. |
| invariants | Callers release all prior session/file owners before rewriting; stable sentinel/parent namespace is fixture-owned. |
| ownership | Borrows immutable map strings while checked fixture writes create the on-disk test state. |
| failure | Checked fixture write failures propagate instead of continuing with an invalid baseline. |
| cost | Linear in total saved file bytes plus one write per path. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [tests/support/generation_fixture.hpp](../../../../../tests/support/generation_fixture.hpp) |

## B0004

[Lines 27–30](../../../../../tests/unit/generation_recovery_admission_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void intact() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a rejected receiving admission changed none of the saved durable file bytes. |
| inputs / outputs | Reads every saved root/sink/WAL/checkpoint path and compares with its saved string. |
| invariants | Includes both incomplete suffixes: failed receiving allocation must not repair them before a final owner is funded. |
| ownership | Only test-owned content strings are materialized; no live session or mutation capability is acquired. |
| failure | A byte mismatch throws the fixture check; this method does not repair or retry. |
| cost | Linear full-file reads/comparisons across the small saved image. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/session_file_fixture.hpp](../../../../../tests/support/session_file_fixture.hpp) |

## B0005

[Lines 31–33](../../../../../tests/unit/generation_recovery_admission_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner restore(SessionGenerationRecoveryOptions options
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the real sink-aware legacy generation recovery factory with the supplied receiving limits. |
| inputs / outputs | Passes genuine program, root path, recovery options, actual sink path and sink options; returns QuerySession::Owner. |
| invariants | This adapter imports no success/frontier DTO. Actual root/checkpoint/log/sink validation and tail repair ordering remain production factory obligations. |
| ownership | Returned session owns receiving account, reconstructed state and real writer locks; Fixture paths/compiler outlive the call. |
| failure | Native/file/codec/account errors propagate unchanged; no catch or fallback hides admission failure. |
| cost | Actual whole selected recovery plus sink validation; dispatch itself is fixed. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp) |

## B0006

[Lines 34–48](../../../../../tests/unit/generation_recovery_admission_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(QuerySession& session) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check successful admission has the expected tail-length reduction and preserves the next actual epoch/output. |
| inputs / outputs | Requires C=I=verified sink sequence2, checks WAL/sink lengths equal saved lengths minus5, starts, enqueues/commits/delivers event3 and compares native rows with independent reference recomputation. |
| invariants | The direct tail assertions check length, not every preserved prefix byte. Validation-before-repair remains the real factory obligation; subsequent source/native/sink behavior must reach epoch3, beyond matching metadata. |
| ownership | Borrows the live restored owner; local reference Database owns its copied input rows and expected relation. |
| failure | Wrong frontiers/tail lengths/missing next input/output or oracle state fails; real production errors escape. |
| cost | Two complete file-size reads, one native/delivery epoch and bounded independent reference recomputation. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/generations.md](../../../../generations.md), [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp) |

## B0007

[Lines 49–49](../../../../../tests/unit/generation_recovery_admission_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L49:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_recovery_admission_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 50–89](../../../../../tests/unit/generation_recovery_admission_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exhaust observed receiving new-failure cuts and exact/one-under account caps before any legacy WAL/sink tail repair. |
| inputs / outputs | Measures restore call count/peak, verifies one success, resets before each injected cut, checks failure/descriptor cleanup/intact bytes and retries with full next-epoch verification. Then checks exact/one-under memory and another retry. |
| invariants | Measured count is finite and below10000. Each injected cut must trigger and throw bad_alloc; rejected heap admission leaves original torn bytes intact. The full global-new seam and account requested-byte cap are separate controls. |
| ownership | Every trial scopes and releases its receiving owner before reset. A successful retry proves root locks remain obtainable; descriptor checks do not independently measure all freed heap bytes. |
| failure | Requires bad_alloc for the selected new seam and MemoryFault::limit for one-under cap; other failures propagate. No semantic Reject is manufactured. |
| cost | A measured allocation-count number of failed restores plus a successful full retry after each, with full image reset/read and actual next native/sink epoch. This is test verification cost, not production recovery latency. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/generations.md](../../../../generations.md) |

## B0009

[Lines 90–90](../../../../../tests/unit/generation_recovery_admission_test.cpp#L90); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L90:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in generation_recovery_admission_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 91–96](../../../../../tests/unit/generation_recovery_admission_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run receiving-admission sweeps on both physical backends and report their combined observed cut count. |
| inputs / outputs | Calls sweep(false) then sweep(true); prints summed allocations only after both succeed. |
| invariants | These are legacy sink-aware generation tests, not acceptance of the new R2 WAL/coordinator. |
| ownership | Both fixture lifetimes end within sweep; no restored session escapes the executable. |
| failure | Final std::exception handler prints its diagnostic and returns one; successful completion returns implicit zero. |
| cost | Runs the two bounded exhaustive observed-allocation sweeps; this inspection pass does not execute them. |
| Design | [tests/unit/generation_recovery_admission_test.cpp](../../../../../tests/unit/generation_recovery_admission_test.cpp), [docs/generations.md](../../../../generations.md) |

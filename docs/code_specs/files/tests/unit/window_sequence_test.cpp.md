# `tests/unit/window_sequence_test.cpp` — block usage map

[Source](../../../../../tests/unit/window_sequence_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `67516d4ec2ea187ac82803b5a26835dd05d53c29eb04ffbab72fadf5e48c9538`. 83 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/window_sequence_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 13–13](../../../../../tests/unit/window_sequence_test.cpp#L13) | Callable definition: void check(bool yes,const char* message) | calls std::runtime_error; guard void check(bool yes,const char* message) { if (!yes) throw std::runtime_error(message); } · [reviewed contract](#b0002) |
| [B0003 · 14–19](../../../../../tests/unit/window_sequence_test.cpp#L14) | Callable definition: PhysicalPlan plan() | calls planner::lower_tree; returns planner::lower_tree(c,q,t) · [reviewed contract](#b0003) |
| [B0004 · 20–24](../../../../../tests/unit/window_sequence_test.cpp#L20) | Callable definition: void enqueue(QuerySession& session,io::WindowCommand command) | calls emplace_back, std::move, batch, check; guard check(session.enqueue(batch)==io::Admission::accepted,"sequence fixture admission failed");; growth emplace_back · [reviewed contract](#b0004) |
| [B0005 · 25–30](../../../../../tests/unit/window_sequence_test.cpp#L25) | Callable definition: void commit_next(QuerySession& session) | calls check, begin_next_result, step, commit; guard check(session.begin_next_result()==SessionBegin::pending,"expected a prepared source step");; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 31–78](../../../../../tests/unit/window_sequence_test.cpp#L31) | Callable definition: void run() | calls QuerySession::create_windowed, plan, start, enqueue; guard check(session-&gt;status().committed_sequence==maximum && session-&gt;progress().sequence==2,; source comment (unverified): // Only the testing archive defines this setup: all real support/physical/ · [reviewed contract](#b0006) |
| [B0007 · 79–79](../../../../../tests/unit/window_sequence_test.cpp#L79) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 80–83](../../../../../tests/unit/window_sequence_test.cpp#L80) | Callable definition: int main() | calls run, what; returns 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–12](../../../../../tests/unit/window_sequence_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:8656aeb63e982668442b59381f0d3ff5524d8a257fe9f6de7a424b09b5ecdb2c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_sequence_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "runtime_probe.hpp", &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–13](../../../../../tests/unit/window_sequence_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool yes,const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a sequence-boundary assertion. |
| inputs / outputs | Predicate and borrowed C-string in; no output. |
| invariants | True returns; false throws. |
| ownership | Message borrowed until exception construction. |
| failure | False throws std::runtime_error. |
| cost | One branch. |
| Design | [tests/unit/window_sequence_test.cpp § lines 13-13](../../../../../tests/unit/window_sequence_test.cpp) |

## B0003

[Lines 14–19](../../../../../tests/unit/window_sequence_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the single-table x query/tree used to test physical sequence exhaustion. |
| inputs / outputs | No inputs; lowered PhysicalPlan out. |
| invariants | Catalog R(x:int64), one native node/atom/head variable, normal default plan options. |
| ownership | Returned plan owns lowered descriptors. |
| failure | Lowering failures propagate. |
| cost | One fixed single-table plan lowering. |
| Design | [tests/unit/window_sequence_test.cpp § lines 14-19](../../../../../tests/unit/window_sequence_test.cpp), [include/crown/planner/lower.hpp § lines 1-16](../../../../../include/crown/planner/lower.hpp) |

## B0004

[Lines 20–24](../../../../../tests/unit/window_sequence_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(QuerySession& session,io::WindowCommand command) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Offer exactly one owned window command to a typed QuerySession. |
| inputs / outputs | Session borrowed; command moved in; no result. |
| invariants | Builds one InputItem/TransportBatch and requires Admission::accepted; no coalescing or command substitution. |
| ownership | Batch owns moved command until accepted; session queue then owns imported head. |
| failure | Admission mismatch fails via check; allocation/session errors propagate. |
| cost | One-item vector/batch construction and queue admission. |
| Design | [tests/unit/window_sequence_test.cpp § lines 20-24](../../../../../tests/unit/window_sequence_test.cpp), [include/crown/io/batch.hpp § lines 47-95](../../../../../include/crown/io/batch.hpp), [src/io/batch.cpp § lines 216-248](../../../../../src/io/batch.cpp), [docs/batches_windows.md § Typed ordered input, lines 11-55](../../../../batches_windows.md) |

## B0005

[Lines 25–30](../../../../../tests/unit/window_sequence_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit_next(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one queued window step through commit and drain all signed output. |
| inputs / outputs | Session borrowed; requires one pending command; no output. |
| invariants | Requires begin_next_result()==pending; runs step until prepared, commits, then consumes output until exhausted. Empty output is allowed; function has no artificial iteration cap. |
| ownership | Session retains runtime/queue/window; step/output handles are local. |
| failure | Unexpected begin state fails; session runtime errors propagate. |
| cost | Work is one step/drain state-machine unit plus all output records for that commit; no CPU timing claim. |
| Design | [tests/unit/window_sequence_test.cpp § lines 25-30](../../../../../tests/unit/window_sequence_test.cpp), [include/crown/runtime/session.hpp § lines 240-270](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp § lines 1435-1485](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure, lines 154-175](../../../../batches_windows.md) |

## B0006

[Lines 31–78](../../../../../tests/unit/window_sequence_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise the distinction between command progress and physical sequence at UINT64_MAX. |
| inputs / outputs | No inputs; creates/starts a window QuerySession, commits commands, then returns after boundary checks. |
| invariants | Commits an initial row insert at physical seq1. Testing-only RuntimeTestProbe sets session physical/runtime/window sequence to UINT64_MAX. Inserting a duplicate label and withdrawing one of two labels are count-only: command progress advances to 2 and 3 while committed physical sequence stays max and supported row remains. Watermark 0 is metadata-only and commits at max. Final withdrawal of last label fails resource_limit without poisoning session, mutating window/progress/snapshot or releasing queued head. After test-only reseed to max-1, same command seq5 commits deletion at max. Metadata watermark seq6 to 100 and EOF finish succeed without another physical sequence. Source offsets 10,20,30,40,50,60 are preserved in submitted commands; accepted progress reaches 6. |
| ownership | QuerySession owns one typed queue, runtime and WindowController. Each batch owns one command until admitted; session retains failed head for retry. RuntimeTestProbe is testing-target only and mutates three synchronized physical tags; it is not a production seed interface. |
| failure | Boundary deletion must throw Error(resource_limit); other errors or changed committed prefix fail. The test explicitly verifies input_failed remains false and phase ready. |
| cost | Six commands and their finite outputs/steps, including one failed begin and two sequence-probe writes; no timing or exhaustive uint64 traversal. |
| Design | [tests/unit/window_sequence_test.cpp § lines 31-78](../../../../../tests/unit/window_sequence_test.cpp), [tests/support/runtime_probe.hpp § lines 16-39](../../../../../tests/support/runtime_probe.hpp), [src/runtime/session.cpp § lines 529-553,563-601,665-669](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp § lines 298-413,132-161](../../../../../src/runtime/window.cpp), [src/runtime/delta.cpp § lines 1582-1594](../../../../../src/runtime/delta.cpp), [docs/batches_windows.md § Window policy and full-row identity, lines 117-152](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure, lines 154-193](../../../../batches_windows.md), [docs/delta_runtime.md § One physical input, lines 41-55](../../../../delta_runtime.md) |

## B0007

[Lines 79–79](../../../../../tests/unit/window_sequence_test.cpp#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L79-L79:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_sequence_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_sequence_test.cpp](../../../../../tests/unit/window_sequence_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 80–83](../../../../../tests/unit/window_sequence_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the sequence-boundary scenario and convert any test exception to process failure. |
| inputs / outputs | No arguments; returns 0 after run, else 1. |
| invariants | Only \`run()\` is called; this source packet does not claim execution. |
| ownership | Session and all fixtures live within run and are destroyed before return. |
| failure | Catches std::exception, writes message and returns 1. |
| cost | One deterministic scenario; the helper loops only until each finite session step/output completes. |
| Design | [tests/unit/window_sequence_test.cpp § lines 80-83](../../../../../tests/unit/window_sequence_test.cpp) |

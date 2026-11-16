# `tests/unit/session_checkpoint_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_checkpoint_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8a93cb3fe82ee6f18897a7168a0d16e03795cb5c740c1e08fd05935503320f64`. 193 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/unit/session_checkpoint_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–61](../../../../../tests/unit/session_checkpoint_test.cpp#L6) | Callable definition: void typed(bool indexed,unsigned kind,SessionState control) | calls fixture, CompiledProgram::standalone, QuerySession::create_typed, get_deleter; guard check(captures==original.statistics().successful_allocations-before.successful_allocations && captu…; growth resize; 4 loop sites · [reviewed contract](#b0002) |
| [B0003 · 62–106](../../../../../tests/unit/session_checkpoint_test.cpp#L62) | Callable definition: void stream(io::InputFormat format,bool indexed) | calls fixture, CompiledProgram::standalone, io::write_input_json, source_catalog; guard source-&gt;start();check(source-&gt;begin_next(),"stream first event missing");finish(*source);source-&gt;pa…; growth emplace, insert, make_unique; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 107–127](../../../../../tests/unit/session_checkpoint_test.cpp#L107) | Callable definition: void barriers(bool indexed) | calls fixture, QuerySession::create_typed, status, progress; guard check(after.state==before.state && after.phase==before.phase && after.committed_sequence==before.co…; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 128–157](../../../../../tests/unit/session_checkpoint_test.cpp#L128) | Callable definition: void failed_readers(bool indexed) | calls fixture, CompiledProgram::standalone, io::write_input_json, source_catalog; guard source-&gt;start();check(source-&gt;begin_next(),"cached reader fixture missing");finish(*source);; returns io::write_input_json(io::InputEvent{update,{}},test.plan.source_catalog())+@; growth make_unique · [reviewed contract](#b0005) |
| [B0006 · 158–182](../../../../../tests/unit/session_checkpoint_test.cpp#L158) | Callable definition: void lifetime_and_initialization(bool indexed) | calls fixture, CompiledProgram::standalone, resize, insert; guard check(retained.by_purpose\[static_cast&lt;std::size_t&gt;(purpose)\].requested_bytes==0,"checkpoint retaine…; growth insert, make_unique, resize; 1 loop sites; source comment (unverified): // A stream continuation is caller-owned; a typed checkpoint cannot use one. · [reviewed contract](#b0006) |
| [B0007 · 183–183](../../../../../tests/unit/session_checkpoint_test.cpp#L183) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 184–193](../../../../../tests/unit/session_checkpoint_test.cpp#L184) | Callable definition: int main() | calls typed, stream, barriers, failed_readers; returns 1; 4 loop sites · [reviewed contract](#b0008) |

## B0001

[Lines 1–5](../../../../../tests/unit/session_checkpoint_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:9d17d53b751c51f9fa6cb335333b29aace1a9fe1f9534d2ad3cb00902599a6d5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_checkpoint_test.cpp: include "session_checkpoint_test_fixture.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–61](../../../../../tests/unit/session_checkpoint_test.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed(bool indexed,unsigned kind,SessionState control)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture and restore a typed QuerySession for one fixture query kind, backend, and control state. |
| inputs / outputs | Creates a typed session, optionally applies its first two test updates, configures workload counters, checkpoints in memory, and restores with the matching CompiledProgram. |
| invariants | Logical rows, progress, exact control status, workload/snapshot options, and one indexed grant must match; diagnostics/histories/owner IDs are not asserted as restored state. Replacement-new fault injection runs only for kind 1 in running state. |
| ownership | SessionCheckpoint owns original-account image/source metadata after capture; restored session owns a separate receiving account; row/oracle comparisons are exported DTO copies. |
| failure | Bad image state, any covered replacement-new bad_alloc, one-under query cap, wrong continuation, or an attempt to restart stopped state must reject while the original prefix remains unchanged. |
| cost | Fixture matrix uses six query kinds, four controls and two backends; each native session has at most two initial plus four next updates; native checkpoint graph allocations use query accounts, while state and oracle Row copies use ordinary test memory. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 62–106](../../../../../tests/unit/session_checkpoint_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stream(io::InputFormat format,bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise binary-session restore with one owned stream profile and a caller-supplied continuation at the next unread byte. |
| inputs / outputs | For one of eight formats, reads/acknowledges a first row, pauses, captures ReaderCheckpoint metadata, mutates counter/accepted-position consistency, then restores with the remaining tail. |
| invariants | Restore carries the original reader byte/record origin and EOF state; it does not own or rewind the caller stream. A continuation passed at EOF is not consumed. |
| ownership | Original and restored sessions own their distinct query accounts; each is given a caller-owned istringstream positioned at the next unread byte. |
| failure | Malformed record counters or impossible source positions reject before allocation; different continued output/progress or EOF is failure. |
| cost | Two records per format, bounded to the configured total-byte/record limits; native decoded state uses query accounts; stream buffers, row exports, and serialized fixture records are test-owned copies. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 107–127](../../../../../tests/unit/session_checkpoint_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void barriers(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe the QuerySession checkpoint barrier across queued, private, paused, output, draining, wrong-thread, and dropped states. |
| inputs / outputs | Builds a small EXISTS session and attempts capture at each lifecycle phase; a helper compares status/progress before and after rejection. |
| invariants | Only a fully acknowledged output boundary is capturable; a rejected capture must not alter state, phase, committed sequence, output remainder, or source progress. |
| ownership | One creator-thread session owns its queue/runtime; a spawned thread borrows it only for the guard check and joins before teardown. |
| failure | A checkpoint that succeeds at any busy barrier, mutates state, bypasses creator-thread ownership, or succeeds after drop fails. |
| cost | A finite sequence of lifecycle transitions and one short-lived thread; the query retains its native state; status/snapshot comparison objects use ordinary copies. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 128–157](../../../../../tests/unit/session_checkpoint_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failed_readers(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate a healthy cached reader rejection from a failed reader and prove only stopped prefixes can be captured. |
| inputs / outputs | Uses a derivation-limited stream for a later healthy engine rejection and malformed JSON for an input failure, then stops and round-trips each terminal prefix. |
| invariants | Healthy cached input and failed active reader are both checkpoint barriers until stop; stopped checkpoint preserves accepted sequence, committed rows, and input_failed independently. |
| ownership | Reader/session native state is owned by each query account; malformed record strings and expected relation exports are test values. |
| failure | Impossible restored positions reject; failed-reader capture before stop rejects; stopped failure options over budget reject before allocation. |
| cost | Two small stream records and one malformed record; allocation denial applies to codec/native capture path, while parser strings and expected rows are test-owned. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0006

[Lines 158–182](../../../../../tests/unit/session_checkpoint_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifetime_and_initialization(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify initialized-table and checkpoint lifetime behavior, then reject mismatched stream/typed continuations and policies. |
| inputs / outputs | Creates a typed session over one initial row, captures it, destroys the source, restores the created epoch-zero state, releases the checkpoint under allocation denial, and tests next update and continuation compatibility. |
| invariants | Checkpoint owns funded recovery bytes but no destroyed table/index/cursor graph; a typed session rejects a stream continuation, an active stream requires one, and changed input options reject. |
| ownership | The captured checkpoint outlives the source account's runtime allocations; target session has a new account; caller stream remains caller-owned. |
| failure | Retained native source allocations, allocating checkpoint destruction, lost initialized row, or accepted mismatched continuation/options fails. |
| cost | One initialized row and one next update; account-purpose inspection is constant in owners; exported rows and istringstream are separate test allocations. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0007

[Lines 183–183](../../../../../tests/unit/session_checkpoint_test.cpp#L183); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L183-L183:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_checkpoint_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 184–193](../../../../../tests/unit/session_checkpoint_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the ordinary session checkpoint matrix for typed queries, stream formats, barriers, reader failures, and lifetime rules. |
| inputs / outputs | For each backend, runs six typed query kinds across four session states, eight owned-stream formats, and four specialized scenario groups. |
| invariants | The typed sessions here are unjournaled; these assertions do not prove durable-before-publication, WAL replay, or local-sink acknowledgment. |
| ownership | Each called scenario owns and releases its fixture session/accounts; main retains no native owner between cases. |
| failure | Any scenario error exits the executable as a failure. |
| cost | Finite matrix: 48 typed combinations, 16 stream combinations, and eight calls to each specialized group; native account allocations are per fresh session, independent reference rows/format buffers are ordinary test copies. |
| Design | [tests/unit/session_checkpoint_test.cpp](../../../../../tests/unit/session_checkpoint_test.cpp), [tests/support/session_checkpoint_test_fixture.hpp](../../../../../tests/support/session_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/recovery/session_image.cpp](../../../../../src/recovery/session_image.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

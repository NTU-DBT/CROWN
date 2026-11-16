# `tests/support/sink_replay_fixture.hpp` — block usage map

[Source](../../../../../tests/support/sink_replay_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4741180f5bf735008269db7a4a0a3db8ee33849f7a263a7f1b4ce12e4203627f`. 43 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/support/sink_replay_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body. | source comment (unverified): // Full ordinary sink snapshot and oracle data; source session is closed before restore. · [reviewed contract](#b0001) |
| [B0002 · 12–21](../../../../../tests/support/sink_replay_fixture.hpp#L12) | Callable definition: explicit Saved(bool indexed=false,unsigned kind=1):source(indexed,kind),program(runtime::CompiledProgram::standalone(source.query… | calls source, program, runtime::CompiledProgram::standalone, log; growth resize; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/support/sink_replay_fixture.hpp#L22) | Explanatory comments or spacing. | source comment (unverified): // accepted is 0..3 for this known four-frame sink; this deliberately writes a torn file. · [reviewed contract](#b0003) |
| [B0004 · 23–28](../../../../../tests/support/sink_replay_fixture.hpp#L23) | Callable definition: void prefix(std::size_t accepted,bool torn=false) | calls session_journal_test::frames, append, substr, generation_test::put; 1 loop sites; source comment (unverified): // accepted is 0..3 for this known four-frame sink; this deliberately writes a torn file. · [reviewed contract](#b0004) |
| [B0005 · 29–33](../../../../../tests/support/sink_replay_fixture.hpp#L29) | Callable definition: runtime::QuerySession::Owner restore(const runtime::SessionGenerationRecoveryOptions& recovery=generation_test::recovery_options(… | calls generation_test::recovery_options, options, runtime::QuerySession::restore_journal_with_local_sink, runtime::QuerySession::restore_generation_with_local_sink; returns runtime::QuerySession::restore_journal_with_local_sink(program,checkpoint,log,recovery.replay,sourc… · [reviewed contract](#b0005) |
| [B0006 · 34–41](../../../../../tests/support/sink_replay_fixture.hpp#L34) | Callable definition: void verify() | calls restore, check, status, progress; guard auto value=restore();check(value-&gt;status().committed_sequence==3 && value-&gt;progress().sequence==3 &…; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 42–43](../../../../../tests/support/sink_replay_fixture.hpp#L42) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::sink_replay_test · [reviewed contract](#b0007) |

## B0001

[Lines 1–11](../../../../../tests/support/sink_replay_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Saved
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain complete source output and independent expectations for restart/truncated-sink tests. |
| inputs / outputs | Contains actual local Fixture, separate standalone compiler, sink/log/checkpoint byte/path strings, three expected deltas and ordinary model Database. |
| invariants | Standalone compiler admission account is distinct from source. Editable copied sink bytes are a tamper baseline, not accepted sink receipt/source proof. |
| ownership | Session within source is move-only and explicitly reset after construction. Model/expected/strings deep-own ordinary data; program handle owns separate immutable control. |
| failure | Construction/verification errors propagate; no native/ordinary joint transaction guarantee. |
| cost | Three actual commits/deliveries plus independent before/after queries, full sink read and ordinary deep data copies. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–21](../../../../../tests/support/sink_replay_fixture.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Saved(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build three committed/delivered epochs and capture their exact sink bytes. |
| inputs / outputs | Computes expected independent deltas, commits/delivers first three updates; saves generation1 paths; resets source session then reads sink. |
| invariants | Kind2 expects empty maintenance deltas while current rows remain checked. Closing source releases native locks before restore tests. |
| ownership | Expected arrays/model own copies; sink snapshot string owns data after stream closure; standalone program stays alive for receiving restore. |
| failure | Oracle/allocation/native/file failure can follow earlier successful commits; no construction rollback promise. |
| cost | Three full oracle transitions and actual delivery paths plus whole sink read/copy. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 22–22](../../../../../tests/support/sink_replay_fixture.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:e44b59f2873924a0456d283af0fc7c742b0868b0216472bf51af30a100f8497a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: accepted is 0..3 for this known four-frame sink; this deliberately writes a torn file. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 23–28](../../../../../tests/support/sink_replay_fixture.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prefix(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write a complete accepted prefix plus optional deterministic torn epoch tail. |
| inputs / outputs | Trusted accepted0..3 selects header through that epoch; optional tail copies first85 bytes of next or final epoch. |
| invariants | Relies on known valid four-frame saved sink and sufficient partial-tail size; frames helper is not a hostile-input parser. This deliberately invalidates on-disk fixture state. |
| ownership | Temporary frame views borrow immutable Saved.sink; concatenated string owns bytes written; Saved.sink is retained unchanged. |
| failure | Out-of-range accepted is outside fixture contract; vector/string/I/O/assertion failures propagate after possible file truncation. |
| cost | O(saved frame count) view split then O(prefix bytes) copy/write, no native restore until caller requests it. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 29–33](../../../../../tests/support/sink_replay_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::QuerySession::Owner restore(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke real sink-aware recovery by direct journal or generation route. |
| inputs / outputs | direct true uses compiler+checkpoint+log/replay options; false uses compiler+generation root; both supply actual sink path/delivery options. |
| invariants | Standalone CompiledProgram and actual file validation establish receiving native state. Paths/digests/editable DTOs are not accepted proof substitutes. |
| ownership | Returns a move-only new owning Session; borrows saved program/paths only through admission as defined by real API. |
| failure | Native binding/budget/file/replay failures propagate; may have real recovery/publication effects governed by those APIs. |
| cost | Actual complete inspection/replay/native rebuild and filesystem locking/delivery checks; not a shallow owner clone. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 34–41](../../../../../tests/support/sink_replay_fixture.hpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert recovered state, exactly retained output and a subsequent live update. |
| inputs / outputs | Restores at sequence/progress3, drains delivery until idle, checks receipt/full sink bytes and three oracle epochs; starts and commits/delivers update4 then verifies rows/receipt4. |
| invariants | No independent loop bound; tests rely on real delivery progress/grants. Full output bytes plus oracle signed sets check exercised cases, not every crash/hardware state. |
| ownership | Local recovered Owner closes before Saved/Directory dies; ordinary model copy for fourth update is independent. |
| failure | Recovery/delivery/assertion/allocation failure propagates after any prior persistence/commit; no rollback wrapper. |
| cost | Complete restore/replay, delivery retry loop, sink reread, three epoch reads and fourth native update plus independent oracle scans. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [tests/unit/local_sink_replay_test.cpp](../../../../../tests/unit/local_sink_replay_test.cpp), [tests/unit/local_sink_replay_fault_test.cpp](../../../../../tests/unit/local_sink_replay_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 42–43](../../../../../tests/support/sink_replay_fixture.hpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L43:sha256:8593cfecd589c57ec9f96b9d56988e4f7e79d4041e3e0b137b90ca695c092c31
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sink_replay_fixture.hpp: struct Saved, namespace crown::sink_replay_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/sink_replay_fixture.hpp](../../../../../tests/support/sink_replay_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

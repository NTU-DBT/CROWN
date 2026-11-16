# `tests/unit/session_checkpoint_window_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_checkpoint_window_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a5d7cb2aa83f163d057ce216b36245f9f3d323aafbcaa846edffe13c7bf5a44c`. 142 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/unit/session_checkpoint_window_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–79](../../../../../tests/unit/session_checkpoint_window_test.cpp#L6) | Callable definition: void scenario(bool indexed,WindowFifoPolicy fifo,SessionState state) | calls plan, CompiledProgram::standalone, QuerySession::create_windowed, config; guard check(captures&gt;0 && captures==original.statistics().successful_allocations-before.successful_alloca…; growth clone, copy_of; 5 loop sites; source comment (unverified): // This window is internally valid; only its join to the managed base · [reviewed contract](#b0002) |
| [B0003 · 80–99](../../../../../tests/unit/session_checkpoint_window_test.cpp#L80) | Callable definition: void barriers(bool indexed) | calls plan, QuerySession::create_windowed, config, seed; guard rejected(\[&\]{auto value=source-&gt;checkpoint_state();});check(source-&gt;begin_next(),"watermark pending… · [reviewed contract](#b0003) |
| [B0004 · 100–114](../../../../../tests/unit/session_checkpoint_window_test.cpp#L100) | Callable definition: void unmanaged_initialization(bool indexed) | calls plan, CompiledProgram::standalone, config, resize; guard check(target-&gt;status().state==SessionState::created && target-&gt;status().committed_sequence==0 &&; growth insert, resize · [reviewed contract](#b0004) |
| [B0005 · 115–131](../../../../../tests/unit/session_checkpoint_window_test.cpp#L115) | Callable definition: void lifetime_rejection(bool indexed,WindowFifoPolicy fifo) | calls QuerySession::create_windowed, plan, config, start; guard check(failed && source-&gt;status().input_failed,"physical FIFO session rejection was not sticky");; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 132–132](../../../../../tests/unit/session_checkpoint_window_test.cpp#L132) | Closes surrounding scope/type. |  · [reviewed contract](#b0006) |
| [B0007 · 133–142](../../../../../tests/unit/session_checkpoint_window_test.cpp#L133) | Callable definition: int main() | calls scenario, barriers, unmanaged_initialization, lifetime_rejection; returns 1; 4 loop sites · [reviewed contract](#b0007) |

## B0001

[Lines 1–5](../../../../../tests/unit/session_checkpoint_window_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:09324eaeed9bd500a633c9e1ff54661406cee3a70a145d536c1f9e740692f588
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_checkpoint_window_test.cpp: include "window_checkpoint_test_fixture.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–79](../../../../../tests/unit/session_checkpoint_window_test.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario(bool indexed,WindowFifoPolicy fifo,SessionState state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip a windowed QuerySession at one control state, FIFO policy, and backend, including managed-base matching. |
| inputs / outputs | Seeds up to five commands, checkpoints and restores with a compiled program, then compares full window state, rows, source progress, command/physical sequences, and later watermark/insertion output. |
| invariants | The fixture intentionally reaches physical sequence 2, command sequence 5, and count ID 1 after its original label is withdrawn; restore must join window rows to managed runtime base rows. Standalone-valid mismatched window state alone is insufficient. |
| ownership | Original SessionCheckpoint owns original-account data; restored session owns one receiving account and one indexed grant; \`window_state\`/row exports are caller-owned copies. |
| failure | Bad fields/counters/policy, wrong managed base, zero or insufficient matching work, allocation cut, or one-under receiving cap reject without changing the source query. |
| cost | At most eight command steps and finite mutation/work probes per case; actual native table/window rebuild allocates in the receiving account; full-state comparison DTOs copy rows outside it. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0003

[Lines 80–99](../../../../../tests/unit/session_checkpoint_window_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void barriers(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that queued, private, between-step, stopped-tombstone, wrong-thread, and dropped window sessions remain checkpoint barriers. |
| inputs / outputs | Queues a watermark, attempts capture before begin and after begin, captures a fully completed command, probes creator-thread guard, then separately stops between expiration steps and checks the tombstone under allocation denial. |
| invariants | A partial watermark can already have committed a physical prefix while its external command remains active; stop does not erase that active-command tombstone or make it capturable. |
| ownership | Each session retains its native runtime/window owner; the spawned thread borrows one session only until join. |
| failure | Any successful partial/tombstoned capture, state mutation on rejection, wrong-thread bypass, or capture after drop fails. |
| cost | Finite two-step watermark and one thread; work/error setup is small; native rows remain account-owned and progress snapshots are copies. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0004

[Lines 100–114](../../../../../tests/unit/session_checkpoint_window_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void unmanaged_initialization(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve unmanaged initialized base rows across a window checkpoint and subsequent expiration. |
| inputs / outputs | Initializes one row in table 1 while table 0 is managed, checkpoints the created session, restores, and applies matching insertion/watermark commands to both. |
| invariants | Managed table state is reconstructed from window labels/counts; the unmanaged table remains in the physical base image and is not erased by window restore. |
| ownership | The source and target sessions own separate native table state; initial Database and expected row relation are ordinary test values. |
| failure | Changed epoch-zero runtime bytes, missing unmanaged rows, or different follow-up output/state fails. |
| cost | One initialized row and two commands; native restore allocates under one receiving account; snapshots and rows are exported copies. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |

## B0005

[Lines 115–131](../../../../../tests/unit/session_checkpoint_window_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L131:sha256:c99f5fc5714f5cdfdc4976938cef1194e04bfa669dcd62e75f6ccd3227bc614a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the actual Session sticky rejection path for a physical FIFO violation. |
| inputs / outputs | Storage-backend flag and physical FIFO mode select an empty windowed session. Three duplicate-supported inserts precede a watermark that would remove B while older A remains. |
| invariants | First begin must report window_fifo_violation and latch input_failed; the next begin reports input_failed. Both retain the complete prior window state, visible rows, source progress/positions and physical epoch, including the watermark metadata prefix. |
| ownership | Owns the Session and offered typed command batches. Test-side row/window/progress copies are ordinary explicit exports; the session keeps its original query account. |
| failure | Missing/wrong error, changed state or unexpected success throws a fixture failure. Other exceptions propagate to the test main; no production handler is installed. |
| cost | Three committed inputs, one queued invalid watermark and two rejected begins per combination, with full-state inspection. Two physical modes and two backends provide four cases; no performance bound is inferred. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [docs/update_patterns.md](../../../../update_patterns.md), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0006

[Lines 132–132](../../../../../tests/unit/session_checkpoint_window_test.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_checkpoint_window_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [docs/checkpoints.md](../../../../checkpoints.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 133–142](../../../../../tests/unit/session_checkpoint_window_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both backends through four FIFO policies/four control states, then checkpoint barriers and physical violation-latch checks. |
| inputs / outputs | Loops two backends times four FIFO policies times created/running/paused/stopped; also runs barriers, unmanaged initialization and both physical-policy sticky rejection cases per backend. |
| invariants | This is in-memory QuerySession checkpoint coverage; the separate file suite tests persisted window artifacts. |
| ownership | Each scenario owns its session/checkpoint until completion and releases it before the next matrix case. |
| failure | Any state, output, matching, or barrier failure propagates to a nonzero test result. |
| cost | Thirty-two primary state combinations, four original helper cases and four physical rejection cases, with bounded commands and finite fault sweeps. |
| Design | [tests/unit/session_checkpoint_window_test.cpp](../../../../../tests/unit/session_checkpoint_window_test.cpp), [tests/support/window_checkpoint_test_fixture.hpp](../../../../../tests/support/window_checkpoint_test_fixture.hpp), [docs/checkpoints.md § Native source and window state components](../../../../checkpoints.md), [docs/checkpoints.md § Complete native QuerySession checkpoint state](../../../../checkpoints.md), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

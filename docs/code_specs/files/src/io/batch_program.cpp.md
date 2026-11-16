# `src/io/batch_program.cpp` — block usage map

[Source](../../../../../src/io/batch_program.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `fda95321ec515e5c2c1daa104397ac3c00871ec3ab8cfa07844e53aad0a3ee0e`. 14 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../ingestion.md), [docs/query_identity.md](../../../../query_identity.md), [docs/schema_evolution.md](../../../../schema_evolution.md), [docs/cli.md](../../../../cli.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/io/batch_program.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // This thin authority bridge belongs to crown_plan. Core native queue storage · [reviewed contract](#b0001) |
| [B0002 · 8–9](../../../../../src/io/batch_program.cpp#L8) | Callable definition: TypedQueue::TypedQueue(const CompiledProgram& program,QueueMode mode,QueueLimits limits,InputLimits input_limits) :TypedQueue(pro… | calls TypedQueue, account, source_catalog_owner; source comment (unverified): // This thin authority bridge belongs to crown_plan. Core native queue storage · [reviewed contract](#b0002) |
| [B0003 · 10–11](../../../../../src/io/batch_program.cpp#L10) | Callable definition: TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state) :TypedQueue(program,state,SourceStateLimits{}) | calls TypedQueue · [reviewed contract](#b0003) |
| [B0004 · 12–13](../../../../../src/io/batch_program.cpp#L12) | Callable definition: TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state,const SourceStateLimits& limits) :TypedQueue(p… | calls TypedQueue, account, source_catalog_owner · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../src/io/batch_program.cpp#L14) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0005) |

## B0001

[Lines 1–7](../../../../../src/io/batch_program.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:075e01a5623b4406d6a291b02a425f4236846b00fd2e0e2ba9b09d29baf559f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports batch, compiled-program, and checkpoint declarations and opens crown::io for the thin constructor bridge from CompiledProgram authority to TypedQueue. Embedded source note records intended usage: This thin authority bridge belongs to crown_plan. Core native queue storage has no link back to the planner or executable-program implementation. Treat that prose as guidance, not as independently verified executable behavior. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/io/batch_program.cpp](../../../../../src/io/batch_program.cpp), [docs/code_specs/files/src/io/batch_program.cpp.md](batch_program.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0002

[Lines 8–9](../../../../../src/io/batch_program.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(const CompiledProgram& program,QueueMode mode,QueueLimits limits,InputLimits input_limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a typed queue from the program's existing source owner and account. |
| inputs / outputs | Delegates mode/queue/input limits with program.account(), aliasing source_catalog_owner() and admitted=true to the core queue constructor. |
| invariants | The checked program supplies immutable schema authority; this bridge never constructs an unlimited replacement query account or links core queue storage back to planner code. |
| ownership | Queue owns funded native metadata/progress and retains the program source owner; future batches remain governed by the concrete queue. |
| failure | Invalid program, mode/options or account allocation failure propagates during private construction; no partial queue or accepted input escapes. |
| cost | Fixed bridge/handle forwarding plus core funded Data/progress setup and option checks. No input events are decoded, enqueued or acknowledged here. |
| Design | [src/io/batch_program.cpp](../../../../../src/io/batch_program.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 10–11](../../../../../src/io/batch_program.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a typed queue with the standard bounded continuation policy. |
| inputs / outputs | Delegates program/checkpoint to the explicit SourceStateLimits overload with defaults. |
| invariants | A checkpoint is descriptive continuation state, not proof of prior runtime commits or permission to invent source sequence. |
| ownership | No checkpoint bytes or rows are copied by this wrapper itself; the delegated constructor owns the result. |
| failure | The explicit restore path's shape/binding/work/account failures propagate unchanged. |
| cost | Fixed forwarding; actual progress cloning, fingerprint generation and checkpoint validation remain in core queue restore. |
| Design | [src/io/batch_program.cpp](../../../../../src/io/batch_program.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 12–13](../../../../../src/io/batch_program.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TypedQueue::TypedQueue(const CompiledProgram& program,const QueueCheckpoint& state,const SourceStateLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore validated typed-source continuation under the receiving program's account. |
| inputs / outputs | Delegates program account/source owner, QueueCheckpoint and SourceStateLimits to the core admitted restore constructor. |
| invariants | Core restore checks source positions/sequence limits, queue configuration and full catalog fingerprint, but does not replay external events or accept pending input. |
| ownership | Restored progress/native metadata are funded by the existing program account; source catalog owner is retained. Caller checkpoint is not kept as an unchecked backing graph. |
| failure | Binding/shape/work/cap/account/allocation failures destroy private partial restore and return no queue. |
| cost | Actual source-position text/map clone and catalog serialization/hash plus funded Data/control. Source-state work units are not total parsing/allocator CPU. |
| Design | [src/io/batch_program.cpp](../../../../../src/io/batch_program.cpp), [include/crown/io/batch.hpp](../../../../../include/crown/io/batch.hpp), [include/crown/io/checkpoint.hpp](../../../../../include/crown/io/checkpoint.hpp), [src/io/batch.cpp](../../../../../src/io/batch.cpp), [src/io/checkpoint_detail.hpp](../../../../../src/io/checkpoint_detail.hpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 14–14](../../../../../src/io/batch_program.cpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L14:sha256:39c2bd587239794e92def2b2ebc5cce8f0acd397d817bceec761a8f61bea3e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::io at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/io/batch_program.cpp](../../../../../src/io/batch_program.cpp), [docs/code_specs/files/src/io/batch_program.cpp.md](batch_program.cpp.md), [docs/ingestion.md](../../../../ingestion.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

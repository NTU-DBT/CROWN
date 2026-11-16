# `include/crown/runtime/session_generation.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session_generation.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `0d8c9b88b8172c4473a8006a948a6b3025d8961d912bfb6d14efe18e605613ed`. 31 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/runtime/session_generation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–13](../../../../../../include/crown/runtime/session_generation.hpp#L6) | Type/record definition: struct SessionGenerationOptions | source comment (unverified): // Includes first/current; rotation retains older pairs until explicit verified · [reviewed contract](#b0002) |
| [B0003 · 14–21](../../../../../../include/crown/runtime/session_generation.hpp#L14) | Type/record definition: struct SessionGenerationRecoveryOptions | source comment (unverified): // The root supplies replay.journal.generation; query_id remains an expected · [reviewed contract](#b0003) |
| [B0004 · 22–30](../../../../../../include/crown/runtime/session_generation.hpp#L22) | Type/record definition: struct SessionGenerationState | source comment (unverified): // Last known metadata; when recovery_required, reopen the actual root. · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../../include/crown/runtime/session_generation.hpp#L31) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../../include/crown/runtime/session_generation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose managed generation session policy and state. |
| inputs / outputs | Includes WAL/native checkpoints and fixed GenerationRoot metadata. |
| invariants | Actual root/sink/native ownership handled by QuerySession/GenerationOwner, not options/status fields. |
| ownership | No IO/account owner from inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/runtime/session_generation.hpp](../../../../../../include/crown/runtime/session_generation.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../../src/recovery/generation_retirement.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 6–13](../../../../../../include/crown/runtime/session_generation.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionGenerationOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure managed checkpoint/WAL/plan retention. |
| inputs / outputs | SessionJournalOptions, root limits, retained_generations32 and descriptor limits. |
| invariants | Includes first/current generation; rotation retains older files until explicit verified retirement. Zero retention rejected by actual session. Metadata/frontier consumption is not deletion authority. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_generation.hpp](../../../../../../include/crown/runtime/session_generation.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../../src/recovery/generation_retirement.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 14–21](../../../../../../include/crown/runtime/session_generation.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionGenerationRecoveryOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure managed generation reconstruction. |
| inputs / outputs | Replay policy, root limits, retention32 and descriptor limits. |
| invariants | Actual selected root supplies replay generation, query ID stays expected binding. Output frontier does not authorize history deletion. Descriptor roots require actual locked recovery/checked artifact API. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_generation.hpp](../../../../../../include/crown/runtime/session_generation.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../../src/recovery/generation_retirement.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 22–30](../../../../../../include/crown/runtime/session_generation.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionGenerationState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report last known managed selection and retirement diagnostics. |
| inputs / outputs | Enabled/recovery_required, fixed selected root, operations/validation work and pending-retirement bounds. |
| invariants | When recovery_required do not assume public selected fields equal surviving disk root; release/reopen actual authority. Report cannot mint root lock/receipt or retire files. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_generation.hpp](../../../../../../include/crown/runtime/session_generation.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/generation.cpp](../../../../../../src/recovery/generation.cpp), [src/recovery/generation_retirement.cpp](../../../../../../src/recovery/generation_retirement.cpp), [docs/generations.md](../../../../../generations.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 31–31](../../../../../../include/crown/runtime/session_generation.hpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/session_generation.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

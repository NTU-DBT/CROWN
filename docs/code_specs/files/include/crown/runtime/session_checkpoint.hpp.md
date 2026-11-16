# `include/crown/runtime/session_checkpoint.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session_checkpoint.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `484fb28469be237d833409361a01637e392429bc27d869931214f46c1e943b11`. 52 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/runtime/session_checkpoint.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–15](../../../../../../include/crown/runtime/session_checkpoint.hpp#L7) | Type/record definition: struct SessionCheckpointLimits | source comment (unverified): // Native set/directory/field comparisons joining managed base rows to the · [reviewed contract](#b0002) |
| [B0003 · 16–20](../../../../../../include/crown/runtime/session_checkpoint.hpp#L16) | Type/record definition: struct SessionRestoreOptions |  · [reviewed contract](#b0003) |
| [B0004 · 21–52](../../../../../../include/crown/runtime/session_checkpoint.hpp#L21) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Complete native quiescent session state, ready for the binary envelope. · [reviewed contract](#b0004) |

## B0001

[Lines 1–6](../../../../../../include/crown/runtime/session_checkpoint.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose native quiescent session capture/import values. |
| inputs / outputs | Includes session facade and funded source checkpoint types. |
| invariants | In-memory state is not itself durable serialized file or native admission capability. |
| ownership | No session/account allocated by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 7–15](../../../../../../include/crown/runtime/session_checkpoint.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionCheckpointLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound native session capture/restore domains separately. |
| inputs / outputs | Separate image/source/window/matching-work and declaration work/cell/payload grants. |
| invariants | Logical grants are separate from the original receiving account byte cap; adding a pattern grant does not authenticate historical enforcement. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

## B0003

[Lines 16–20](../../../../../../include/crown/runtime/session_checkpoint.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionRestoreOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure native checkpoint receiving reconstruction. |
| inputs / outputs | BuildOptions, SessionCheckpointLimits and optional memory_limit_bytes override. |
| invariants | Override chooses receiving query cap; does not mint/replenish an existing admitted owner. Actual version/source/program/policy/window matching required. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 21–52](../../../../../../include/crown/runtime/session_checkpoint.hpp#L21); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionCheckpoint {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own complete move-only native quiescent session state. |
| inputs / outputs | Move-only quiescent source/window/runtime checkpoint, optional declaration, origins and first fixed violation; legacy version 1 without declaration, version 2 with declaration. |
| invariants | Public mutable checkpoint state is trusted history only after source/version/shape/sequence/violation admission. Checksums do not authenticate prior enforcement. Undeclared state retains its legacy layout. |
| ownership | Binary/source/window payload owns receiving-account storage. Immutable input/window-table/declaration handles retain their actual owners. No stream, file lock or live runtime is retained. |
| failure | Explicit copies deleted, moves noexcept. Capture/restore allocation/work/binding errors release private graph; default value creates no account/grant. |
| cost | Factory scans/clones full native component/source/window and allocates bytes/rows; move transfers native graphs, assignment releases old owned graph; final teardown visits positions/row owners and buffers. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md), [include/crown/io/checkpoint.hpp](../../../../../../include/crown/io/checkpoint.hpp), [include/crown/io/input_options.hpp](../../../../../../include/crown/io/input_options.hpp), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
SessionCheckpoint()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct unbound native checkpoint carrier. |
| inputs / outputs | Default version/state/kind/scalars, empty runtime bytes/options/source/default source variant and no window. |
| invariants | Default created flags do not represent an admitted session or valid image. No allowance created. |
| ownership | Empty native handles/vectors and fixed settings only. |
| failure | No payload allocation until factory supplies account-backed values; signature not noexcept. |
| cost | Fixed empty construction. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionCheckpoint(const SessionCheckpoint&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject SessionCheckpoint copy construction. |
| inputs / outputs | Deleted operation. |
| invariants | Avoids silent duplication of native source/window row ownership and allowance. Explicit capture/import performs accounted clone. |
| ownership | Unique native mutable state carrier. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionCheckpoint& operator=(const SessionCheckpoint&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject SessionCheckpoint copy assignment. |
| inputs / outputs | Deleted operation. |
| invariants | Avoids silent duplication of native source/window row ownership and allowance. Explicit capture/import performs accounted clone. |
| ownership | Unique native mutable state carrier. |
| failure | Compile-time rejection. |
| cost | No runtime cost. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionCheckpoint(SessionCheckpoint&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move SessionCheckpoint by construction. |
| inputs / outputs | Default noexcept ownership transfer across bytes/options/source/window. |
| invariants | Move does not revalidate mutable fields or create durable file. Source remains ordinary moved-from/destructible. |
| ownership | Destination adopts actual vector/account/source/window owners; assignment releases old graph. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | Fixed graph transfers plus actual old graph teardown, no fresh payload allocation. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
SessionCheckpoint& operator=(SessionCheckpoint&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move SessionCheckpoint by assignment. |
| inputs / outputs | Default noexcept ownership transfer across bytes/options/source/window. |
| invariants | Move does not revalidate mutable fields or create durable file. Source remains ordinary moved-from/destructible. |
| ownership | Destination adopts actual vector/account/source/window owners; assignment releases old graph. |
| failure | noexcept for the stated live object; no hidden validation or ownership extension. |
| cost | Fixed graph transfers plus actual old graph teardown, no fresh payload allocation. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
@source-span:L21-L52:sha256:6aea70d46531284b54bd72a9b96ceba7f87d4e250c4486b2b7ec186a58b278a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Version native in-memory session checkpoint shape. |
| inputs / outputs | legacy_version=1, current_version=2; default carrier version is legacy 1. |
| invariants | A valid admitted checkpoint uses version 2 exactly when a declaration is present. Version constants alone validate neither the carrier nor historical compliance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md), [docs/update_patterns.md](../../../../../update_patterns.md) |

```text
std::variant<io::ReaderCheckpoint,io::QueueCheckpoint,io::AccountedInputProgress> source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain actual native source checkpoint alternative. |
| inputs / outputs | variant&lt;ReaderCheckpoint,QueueCheckpoint,AccountedInputProgress&gt;. |
| invariants | Stopped retains accepted progress only; live reader must have no unacknowledged cached row, queue empty; actual kind/state matching checked on restore. |
| ownership | Source progress owns funded positions/CSV/native options; no underlying stream/queue object/fd retained. |
| failure | Capture/import can allocate; default/move not a new grant. |
| cost | Positions/text/CSV clone cost during factory, fixed variant move, nested native graph cleanup. |
| Design | [include/crown/runtime/session_checkpoint.hpp](../../../../../../include/crown/runtime/session_checkpoint.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/code_review.md](../../../../../code_review.md) |

```text
@source-span:L21-L24:sha256:d1f6df864d7356d9e45b48823a18c9d3d6f1136a353142f1717a109285a0b1a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SessionCheckpoint\`: Complete native quiescent session state, ready for the binary envelope. Source options/positions and window rows have funded native ownership; runtime_image alone is already a pointer-free binary runtime component. This in-memory C++ object is not itself a durable serialized checkpoint. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/runtime/session_checkpoint.hpp:L24; use that declaration for the actual input/output shape. |
| invariants | The source note states: Complete native quiescent session state, ready for the binary envelope. Source options/positions and window rows have funded native ownership; runtime_image alone is already a pointer-free binary runtime component. This in-memory C++ object is not itself a durable serialized checkpoint. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Complete native quiescent session state, ready for the binary envelope. Source options/positions and window rows have funded native ownership; runtime_image alone is already a pointer-free binary runtime component. This in-memory C++ object is not itself a durable serialized checkpoint. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

```text
@source-span:L52-L52:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/session_checkpoint.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

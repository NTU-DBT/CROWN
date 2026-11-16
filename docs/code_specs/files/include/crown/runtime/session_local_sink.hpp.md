# `include/crown/runtime/session_local_sink.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session_local_sink.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `9194f64a52350994d32e065d517502ca55106cf80a0ce0b9b0b53f5119a40172`. 27 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../../include/crown/runtime/session_local_sink.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–10](../../../../../../include/crown/runtime/session_local_sink.hpp#L5) | Type/record definition: struct SessionLocalSinkOptions |  · [reviewed contract](#b0002) |
| [B0003 · 11–20](../../../../../../include/crown/runtime/session_local_sink.hpp#L11) | Type/record definition: struct SessionLocalSinkState | source comment (unverified): // Describes an authenticated checkpoint-prefix basis. Current delivery, · [reviewed contract](#b0003) |
| [B0004 · 21–21](../../../../../../include/crown/runtime/session_local_sink.hpp#L21) | Type/record definition: enum class LocalDeliveryKind :std::uint8_t |  · [reviewed contract](#b0004) |
| [B0005 · 22–26](../../../../../../include/crown/runtime/session_local_sink.hpp#L22) | Type/record definition: struct LocalDelivery |  · [reviewed contract](#b0005) |
| [B0006 · 27–27](../../../../../../include/crown/runtime/session_local_sink.hpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0006) |

## B0001

[Lines 1–4](../../../../../../include/crown/runtime/session_local_sink.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose whole-epoch durable local output policy/status. |
| inputs / outputs | Includes session WAL and native sink File/Receipt types. |
| invariants | Descriptive fields cannot replace actual local sink or retirement checks. |
| ownership | No sink created by inclusion. |
| failure | Compile-time boundary. |
| cost | No runtime action. |
| Design | [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 5–10](../../../../../../include/crown/runtime/session_local_sink.hpp#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionLocalSinkOptions {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure actual durable sink identity/IO/delivery budget. |
| inputs / outputs | Fixed sink ID, sink::Limits, delivery_work512Mi and tail-repair flag. |
| invariants | Actual session/File verifies schema/query/origin/frontiers and controls repair; option alone not durable delivery authority or new allowance. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 11–20](../../../../../../include/crown/runtime/session_local_sink.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionLocalSinkState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report persisted and native-verified sink progress separately. |
| inputs / outputs | Enabled/recovery_required/replaying, verified epoch, delivery work, blocked inputs, persisted State and retirement_verified flag. |
| invariants | retirement_verified only says authenticated checkpoint-prefix basis exists. Current health/full committed delivery/quiescence/actual Receipt still gate retirement; persisted coverage may exceed verified replay frontier. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 21–21](../../../../../../include/crown/runtime/session_local_sink.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LocalDeliveryKind :std::uint8_t {idle,published,duplicate};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify one native whole-epoch delivery result. |
| inputs / outputs | idle/published/duplicate. |
| invariants | published/duplicate describes actual File acceptance from deliver_local_epoch; caller-created tag cannot authenticate delivery or retire history. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Constant-size tag, no allocation/IO/clock. Arbitrary casts are not admitted automatically. |
| Design | [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 22–26](../../../../../../include/crown/runtime/session_local_sink.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LocalDelivery {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one completed local-delivery action. |
| inputs / outputs | Kind/generation/sequence/row count. |
| invariants | Fixed descriptive output; no receipt/File/lock/account ownership. Actual complete epoch acceptance happened in native method, not by constructing this DTO. |
| ownership | Owns inline descriptive values only; no file/lock/runtime/account allowance or caller backing retained. |
| failure | The public record declaration performs no validation or failure translation. Actual codec/file/native factories enforce stated rules. |
| cost | Fixed scalar/enum/optional/array storage and bounded copies; no dynamic payload, IO, clock or heap allocation. |
| Design | [include/crown/runtime/session_local_sink.hpp](../../../../../../include/crown/runtime/session_local_sink.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [src/recovery/local_sink.cpp](../../../../../../src/recovery/local_sink.cpp), [docs/local-sink.md](../../../../../local-sink.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 27–27](../../../../../../include/crown/runtime/session_local_sink.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/session_local_sink.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/checkpoints.md](../../../../../checkpoints.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

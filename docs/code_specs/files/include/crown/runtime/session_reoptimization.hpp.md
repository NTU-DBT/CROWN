# `include/crown/runtime/session_reoptimization.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/session_reoptimization.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `a57f907203a0352c982bd8b785274e31d16e2b54497d6b0bcc90615cd41f80da`. 26 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/runtime/session_reoptimization.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Owns the actual root lock and receiving account while caller/compiler IO · [reviewed contract](#b0001) |
| [B0002 · 9–25](../../../../../../include/crown/runtime/session_reoptimization.hpp#L9) | Type/record definition: class LockedGenerationRecovery | source comment (unverified): // Owns the actual root lock and receiving account while caller/compiler IO · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../../include/crown/runtime/session_reoptimization.hpp#L26) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../../include/crown/runtime/session_reoptimization.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime session_reoptimization public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

## B0002

[Lines 9–25](../../../../../../include/crown/runtime/session_reoptimization.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class LockedGenerationRecovery
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the real selected-root recovery fence across caller compiler I/O. |
| inputs / outputs | Created only by QuerySession::lock_generation_recovery and consumed by selected-generation restore APIs. |
| invariants | Unlike unlocked inspection/status flags, this object retains the actual root lock and receiving account while caller decodes the immutable selected compiler artifact. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Creation/restore handle actual typed file/source/root/account failures; no arbitrary public constructor is available. |
| cost | Creation already performed root/checkpoint/optional descriptor reads and native funding. Getters are metadata/borrow access; destruction releases lock/fd and actual retained graph. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
using Owner=resource::AccountedUnique<LockedGenerationRecovery>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the actual funded locked-input owner. |
| inputs / outputs | Move-only unique facade owner with its native allocator/deleter. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Fixed owner transfer; final release retains actual lock/descriptor/account cleanup. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
~LockedGenerationRecovery();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release unconsumed selected-root recovery input. |
| inputs / outputs | Drops actual lock/root file owner, context, expected plan and optional selected descriptor. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Actual file close/unlock and retained native graph release; no implicit native session admission. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
LockedGenerationRecovery(const LockedGenerationRecovery&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject copying the locked recovery facade. |
| inputs / outputs | No duplicated lock/admission token. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Compile-time restriction. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
LockedGenerationRecovery& operator=(const LockedGenerationRecovery&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject locked facade copy assignment. |
| inputs / outputs | Owner transfer uses its AccountedUnique Owner. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Compile-time restriction. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
bool has_plan() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the selected root has retained plan descriptor data. |
| inputs / outputs | Reads actual ManagedPlan presence, not an editable caller flag. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Fixed pointer test. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
std::string_view compiler_artifact() const & noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact selected immutable compiler artifact bytes. |
| inputs / outputs | Empty view when no selected plan; otherwise borrows locked ManagedPlan encoded storage. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Fixed view, no compilation, parsing, reread or byte clone. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
std::string_view compiler_artifact() const &&=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject borrowing selected artifact from a temporary facade. |
| inputs / outputs | Rvalue-borrow restriction, in addition to actual Owner lifetime. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Compile-time restriction. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
resource::MemoryStatistics accounted_memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual receiving query-account counters. |
| inputs / outputs | Returns fixed current/peak/history statistics from retained receiving context. |
| invariants | Only a live genuine facade has Data; borrowed artifact bytes must not outlive token consumption/release. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Deleted operations fail compilation; declared noexcept getters read existing prepared state. No getter creates admission authority. |
| cost | Fixed account statistics snapshot; no full attribution/row ledger scan. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
friend class QuerySession;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restrict locked recovery construction/consumption to session admission. |
| inputs / outputs | Private locked recovery authority/storage declaration. |
| invariants | No caller-created inspection result or selected hash can substitute for this retained actual owner. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Declaration/prepared owner transfer adds no catch or new I/O. |
| cost | Fixed native descriptor; final release retains real fd/graph cleanup cost. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide actual locked-root/account/selected-plan resources. |
| inputs / outputs | Private locked recovery authority/storage declaration. |
| invariants | No caller-created inspection result or selected hash can substitute for this retained actual owner. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Declaration/prepared owner transfer adds no catch or new I/O. |
| cost | Fixed native descriptor; final release retains real fd/graph cleanup cost. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
explicit LockedGenerationRecovery(resource::AccountedUnique<Data>) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a prepared genuine locked-input facade. |
| inputs / outputs | Private locked recovery authority/storage declaration. |
| invariants | No caller-created inspection result or selected hash can substitute for this retained actual owner. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Declaration/prepared owner transfer adds no catch or new I/O. |
| cost | Fixed native descriptor; final release retains real fd/graph cleanup cost. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

```text
resource::AccountedUnique<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own actual root lock, receiving context and selected bytes. |
| inputs / outputs | Private locked recovery authority/storage declaration. |
| invariants | No caller-created inspection result or selected hash can substitute for this retained actual owner. |
| ownership | Noncopyable/nonmovable facade in AccountedUnique Owner retains actual GenerationOwner root lock, receiving work/account context, expected CompiledProgram and optional selected plan/artifact bytes. Moving Owner transfers the facade; consuming/destroying it releases/transfers those actual resources. |
| failure | Declaration/prepared owner transfer adds no catch or new I/O. |
| cost | Fixed native descriptor; final release retains real fd/graph cleanup cost. |
| Design | [include/crown/runtime/session_reoptimization.hpp](../../../../../../include/crown/runtime/session_reoptimization.hpp), [src/runtime/session.cpp](../../../../../../src/runtime/session.cpp), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/generations.md](../../../../../generations.md) |

## B0003

[Lines 26–26](../../../../../../include/crown/runtime/session_reoptimization.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L26:sha256:024a31d07f0690bcfeef2cd00cf111a56223bd48741eae7b548b6bc9143d9111
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/session_reoptimization.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/selection.md](../../../../../selection.md), [docs/selection_binding.md](../../../../../selection_binding.md), [docs/selection_accounting.md](../../../../../selection_accounting.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

# `include/crown/runtime/replay.hpp` — block usage map

[Source](../../../../../../include/crown/runtime/replay.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `100880b34670668e7bdfba456ba6ddb0f7d3f8669055417c0a9abd2ec1519b42`. 27 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../../session_lifecycle.md), [docs/session-journal.md](../../../../../session-journal.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/reoptimization.md](../../../../../reoptimization.md), [docs/native-replay.md](../../../../../native-replay.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/runtime/replay.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // One ordered source reader binds to one runtime owner on first application. · [reviewed contract](#b0001) |
| [B0002 · 10–26](../../../../../../include/crown/runtime/replay.hpp#L10) | Type/record definition: class OrderedReplay | source comment (unverified): // One ordered source reader binds to one runtime owner on first application. · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../../include/crown/runtime/replay.hpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0003) |

## B0001

[Lines 1–9](../../../../../../include/crown/runtime/replay.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the runtime replay public interface and its required types. |
| inputs / outputs | Header imports its explicit dependencies and declares the APIs/contracts below. |
| invariants | Inclusion does not construct a live query, source, report, proof or file owner. |
| ownership | Declarations retain no instance; object ownership and copies are specified at the individual APIs. |
| failure | Compile-time dependency/declaration boundary; runtime failures belong to instantiated objects/operations. |
| cost | No runtime action from inclusion itself; inline methods retain their stated actual costs. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

## B0002

[Lines 10–26](../../../../../../include/crown/runtime/replay.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OrderedReplay
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind one ordered source to one actual runtime owner. |
| inputs / outputs | Before applying, checks readiness, equal accepted/runtime sequence and complete catalog binding; then applies the cached view and acknowledges after atomic engine commit. |
| invariants | Binds owner before the first nonempty engine application, so a rejected first apply does not permit owner switching. Output retry is separate from input retry. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Reader decoding errors stay sticky; engine rejection leaves complete cached head retryable for the same owner. No throwing source bookkeeping follows commit. |
| cost | Initial binding can canonicalize/hash catalog; each head decodes/prepares then pays actual engine work. Acknowledgment moves/links prepaid source state and returns a nothrow-moved epoch. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
explicit OrderedReplay(io::EventReader reader);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a reader into a funded replay facade. |
| inputs / outputs | Reads its actual account and allocates Data; by-value move may have consumed caller reader before allocation failure. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | One funded Data owner plus reader transfer; no source row/progress clone. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
~OrderedReplay();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release replay/source ownership. |
| inputs / outputs | Destroys reader state without destroying borrowed stream. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Actual decoder/map/options/schema cleanup, not merely a pointer reset. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
OrderedReplay(const OrderedReplay&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject duplicate replay cursor copying. |
| inputs / outputs | Unique mutable acceptance owner. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Compile-time restriction. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
OrderedReplay& operator=(const OrderedReplay&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject replay copy assignment. |
| inputs / outputs | No duplicate source owner. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Compile-time restriction. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
OrderedReplay(OrderedReplay&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the replay owner. |
| inputs / outputs | Moves unique native Data. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Fixed descriptor transfer, no data clone. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
OrderedReplay& operator=(OrderedReplay&&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace/transfer replay ownership. |
| inputs / outputs | Releases old source Data then transfers replacement. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Transfer plus actual old source graph cleanup, no new allocation. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
const io::InputEventView* peek();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow/decode the next source head without applying it. |
| inputs / outputs | Delegates reader.peek; does not bind a runtime or acknowledge input. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Actual reader decode/preparation cost or fixed cached/end access. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
const io::AccountedInputProgress& progress() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow accepted replay progress. |
| inputs / outputs | Pending head is excluded. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Fixed Data/reader reference access; explicit progress copy clones native Data/map nodes and nonempty key character blocks/bytes. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
bool failed() const noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read source decoder sticky failure. |
| inputs / outputs | Absent Data reports false. |
| invariants | No hidden source acceptance or engine reapplication. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Moved/invalid reader, original-account allocation or reader decode errors propagate where applicable. Deleted functions fail compilation; noexcept operations retain their declared contract. |
| cost | Fixed pointer/flag read. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
apply_next(PhysicalRuntime& runtime);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply exactly one ordered head to PhysicalRuntime. |
| inputs / outputs | Returns absent at end, otherwise actual engine epoch after native apply_view and nonthrowing reader acknowledgment. |
| invariants | Checks owner/readiness/sequence/catalog before apply; same cached event may retry after engine rejection. Epoch move is statically required nothrow after commit. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Preparation/engine failures propagate before source acknowledgment; no new rollback wrapper or output retry is performed by replay. |
| cost | Source preparation plus actual engine work; postcommit source link/scalar updates and epoch move add no new allocation. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
apply_next(DeltaRuntime& runtime);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply exactly one ordered head to DeltaRuntime. |
| inputs / outputs | Returns absent at end, otherwise actual engine epoch after native apply_view and nonthrowing reader acknowledgment. |
| invariants | Checks owner/readiness/sequence/catalog before apply; same cached event may retry after engine rejection. Epoch move is statically required nothrow after commit. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Preparation/engine failures propagate before source acknowledgment; no new rollback wrapper or output retry is performed by replay. |
| cost | Source preparation plus actual engine work; postcommit source link/scalar updates and epoch move add no new allocation. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
struct Data;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hide unique source/bound-owner replay state. |
| inputs / outputs | Private replay storage declaration. |
| invariants | No public constructor accepts an arbitrary bound owner flag. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Declaration adds no handler. |
| cost | Fixed descriptor; final release retains actual source graph cost. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

```text
resource::AccountedUnique<Data> data_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the original-account replay facade state. |
| inputs / outputs | Private replay storage declaration. |
| invariants | No public constructor accepts an arbitrary bound owner flag. |
| ownership | Unique funded Data owns the moved EventReader and first-bound owner ID. Reader retains schema/native source state but only borrows its stream. Returned event/progress references borrow this source; no runtime owner pointer is stored. |
| failure | Declaration adds no handler. |
| cost | Fixed descriptor; final release retains actual source graph cost. |
| Design | [include/crown/runtime/replay.hpp](../../../../../../include/crown/runtime/replay.hpp), [src/runtime/replay.cpp](../../../../../../src/runtime/replay.cpp), [docs/native-replay.md](../../../../../native-replay.md) |

## B0003

[Lines 27–27](../../../../../../include/crown/runtime/replay.hpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L27:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in include/crown/runtime/replay.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/delta_runtime.md](../../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../../weighted_deltas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

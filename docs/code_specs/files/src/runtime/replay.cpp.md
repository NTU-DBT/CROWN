# `src/runtime/replay.cpp` — block usage map

[Source](../../../../../src/runtime/replay.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Coordinate input, window control, native epoch preparation, output delivery and durable recovery at one session lifecycle boundary.

Snapshot SHA-256: `8931a12565708892cd7a60fc4ade887b2bcb9ba42ec7765561554dbecc664b85`. 61 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/runtime/replay.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–26](../../../../../src/runtime/replay.cpp#L8) | Type/record definition: struct OrderedReplay::Data | returns event; source comment (unverified): // Bind on the first prepared event, before engine apply; rejection retries · [reviewed contract](#b0002) |
| [B0003 · 27–31](../../../../../src/runtime/replay.cpp#L27) | Callable definition: OrderedReplay::OrderedReplay(io::EventReader reader) | calls account, std::move; growth make_accounted_unique · [reviewed contract](#b0003) |
| [B0004 · 32–34](../../../../../src/runtime/replay.cpp#L32) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 35–38](../../../../../src/runtime/replay.cpp#L35) | Callable definition: const io::InputEventView* OrderedReplay::peek() | calls Error, peek; returns data_-&gt;reader.peek() · [reviewed contract](#b0005) |
| [B0006 · 39–42](../../../../../src/runtime/replay.cpp#L39) | Callable definition: const io::AccountedInputProgress& OrderedReplay::progress() const | calls Error, progress; returns data_-&gt;reader.progress() · [reviewed contract](#b0006) |
| [B0007 · 43–43](../../../../../src/runtime/replay.cpp#L43) | Callable definition: bool OrderedReplay::failed() const noexcept | calls failed; returns data_ && data_-&gt;reader.failed() · [reviewed contract](#b0007) |
| [B0008 · 44–53](../../../../../src/runtime/replay.cpp#L44) | Callable definition: std::optional&lt;PhysicalEpoch&gt; OrderedReplay::apply_next(PhysicalRuntime& runtime) | calls Error, prepare, apply_view, acknowledge; guard static_assert(std::is_nothrow_move_constructible_v&lt;PhysicalEpoch&gt;);; returns {}; std::optional&lt;PhysicalEpoch&gt;{std::move(epoch)}; source comment (unverified): // Sequence/source map changes were prepared by peek before engine work. · [reviewed contract](#b0008) |
| [B0009 · 54–60](../../../../../src/runtime/replay.cpp#L54) | Callable definition: std::optional&lt;DeltaRuntime::Epoch&gt; OrderedReplay::apply_next(DeltaRuntime& runtime) | calls Error, prepare, apply_view, acknowledge; guard static_assert(std::is_nothrow_move_constructible_v&lt;DeltaRuntime::Epoch&gt;);; returns {}; std::optional&lt;DeltaRuntime::Epoch&gt;{std::move(epoch)} · [reviewed contract](#b0009) |
| [B0010 · 61–61](../../../../../src/runtime/replay.cpp#L61) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0010) |

## B0001

[Lines 1–7](../../../../../src/runtime/replay.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:19e32af8ed12c26a8953dfcc9ace5b58d487ddd5f86b3b54bf9b67cbb37f9896
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/replay.cpp: imports \`"crown/runtime/replay.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;type_traits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 8–26](../../../../../src/runtime/replay.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OrderedReplay::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one ordered input reader and its eventual single-runtime binding. |
| inputs / outputs | reader owns native input/control/progress state; optional owner starts disengaged. Constructor moves reader; prepare verifies owner/readiness/sequence/catalog then peeks one event. |
| invariants | Binding is established when prepare sees the first event, before engine apply. An engine-rejected event remains bound to that runtime for retry; EOF without any event remains unbound. |
| ownership | Data owns EventReader but its underlying input stream remains subject to EventReader's caller stream lifetime. Cached event view borrows reader storage until acknowledge/reader change. |
| failure | Binding/readiness/sequence/catalog failures precede engine apply; reader decoding failure poisons reader by its own boundary. Data introduces no broad catch. |
| cost | Fixed binding gates plus first-unbound full catalog fingerprint and actual event decode/cache costs; not a free wrapper around engine apply. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  explicit Data(io::EventReader input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the prepared reader into ordered replay state. |
| inputs / outputs | Moves by-value EventReader, with optional owner initially empty. |
| invariants | No event is read, acknowledged or bound by construction. |
| ownership | Reader owner transfers into Data; caller must still retain its underlying stream per reader API. |
| failure | No explicit exception translation; enclosing funded Data construction can fail. |
| cost | Fixed owner transfer; no input byte scan or progress copy. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
  template<class Runtime> const io::InputEventView* prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate retryable ordered input against the exact actual runtime boundary before apply. |
| inputs / outputs | Rejects a different bound owner, unready runtime or source/runtime sequence mismatch; until first event checks full source catalog compatibility; peeks and binds owner when an event exists. |
| invariants | Owner binding occurs before commit and survives engine rejection. Sequence/progress and complete cached event remain unchanged until later acknowledge; empty EOF does not bind. Catalog equality alone is not source/account ownership authority. |
| ownership | Returned InputEventView borrows reader cache; runtime and stream must remain stable through synchronous apply. No event row is copied merely to return its pointer. |
| failure | Throws invalid_replay_owner, runtime_busy, invalid_sequence or catalog_mismatch precisely. Reader parse/resource faults retain its existing poison semantics; no retry layer here. |
| cost | Fixed owner/readiness/sequence checks plus full catalog fingerprint when unbound and real reader peek/decode/progress staging. Empty unbound retries may repeat fingerprint work. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 27–31](../../../../../src/runtime/replay.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OrderedReplay::OrderedReplay(io::EventReader reader)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund ordered replay metadata under the reader's existing account. |
| inputs / outputs | Retrieves reader.account and make_accounted_unique&lt;Data&gt; under input memory_owner/support_metadata, moving the reader. |
| invariants | No fresh unlimited account, source event, runtime binding or acknowledgement is created. |
| ownership | Replay exclusively owns funded Data and moved reader; stream borrowing remains unchanged. |
| failure | Data/control account/allocation failure discards local partial state with RAII; no catch or partially usable replay escapes. |
| cost | One actual funded unique control/Data request plus owner transfer; no input scan yet. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 32–34](../../../../../src/runtime/replay.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OrderedReplay::~OrderedReplay()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release ordered replay and cached native input through the owning implementation. |
| inputs / outputs | Default destructor destroys Data/reader/progress/cache and their funded owners. |
| invariants | Closing an unapplied cached event does not acknowledge it or roll back a committed runtime; no runtime pointer is owned. |
| ownership | Underlying stream is borrowed and not owned by this wrapper. Cached values/control release original-account memory. |
| failure | Nonthrowing RAII cleanup; no recovery or source read. |
| cost | Actual progress/source-map and cached text/key destruction/deallocation can scale with retained payload; no replacement allocation. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
OrderedReplay::OrderedReplay(OrderedReplay&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move ordered replay ownership without cloning input or source progress. |
| inputs / outputs | Default noexcept operation will construct a replay by transferring the same Data owner. |
| invariants | Single-runtime binding and cached event/poison/progress move with Data; moved-from peek/progress/apply reject and failed() returns false. |
| ownership | Existing borrowed cache/progress references follow the transferred Data while retained; replacement can release old Data and invalidate its views. |
| failure | Noexcept owner movement; no retry, rebind or acknowledgement. |
| cost | Fixed owner transfer plus possible destruction of replaced reader/progress payload for assignment; no new input allocation. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

```text
OrderedReplay& OrderedReplay::operator=(OrderedReplay&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move ordered replay ownership without cloning input or source progress. |
| inputs / outputs | Default noexcept operation will replace this replay owner after releasing its previously retained Data. |
| invariants | Single-runtime binding and cached event/poison/progress move with Data; moved-from peek/progress/apply reject and failed() returns false. |
| ownership | Existing borrowed cache/progress references follow the transferred Data while retained; replacement can release old Data and invalidate its views. |
| failure | Noexcept owner movement; no retry, rebind or acknowledgement. |
| cost | Fixed owner transfer plus possible destruction of replaced reader/progress payload for assignment; no new input allocation. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 35–38](../../../../../src/runtime/replay.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const io::InputEventView* OrderedReplay::peek()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read or reuse one cached native input event without engine publication. |
| inputs / outputs | Rejects moved-from wrapper, otherwise delegates reader.peek and returns pointer or null at EOF. |
| invariants | Peeking alone does not bind runtime owner or advance committed progress; decode errors retain EventReader poison semantics. |
| ownership | Pointer borrows reader cache and remains valid only until its documented acknowledgement/cache lifetime ends. |
| failure | Moved-from throws invalid_input_reader; reader parse/limit/allocation/poison errors propagate unchanged. |
| cost | Cached peek is fixed forwarding; first peek performs real byte parsing, native row/text funding and staged progress work. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 39–42](../../../../../src/runtime/replay.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const io::AccountedInputProgress& OrderedReplay::progress()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow committed source progress without exporting ordinary strings/maps. |
| inputs / outputs | Rejects moved-from wrapper, otherwise returns reader.progress() by const reference. |
| invariants | Cached but unacknowledged event does not advance this committed sequence/source map. |
| ownership | Reference borrows replay reader Data; retain the owner and avoid acknowledgement/mutation while relying on old contents. |
| failure | Moved-from throws invalid_input_reader; no copy/recovery or account fallback. |
| cost | Fixed reference forwarding, no progress-map clone or input scan. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 43–43](../../../../../src/runtime/replay.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool OrderedReplay::failed()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe reader poison state, tolerating a moved-from replay. |
| inputs / outputs | Returns data_ && data_-&gt;reader.failed(). |
| invariants | Engine rejection need not poison the reader; this reports decoder failure only. Moved-from returns false, not a usable reader. |
| ownership | Reads fixed state only; no retained pointer is returned. |
| failure | Declared noexcept, no throw or recovery. |
| cost | Fixed nullable-owner/flag check without allocation. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 44–53](../../../../../src/runtime/replay.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<PhysicalEpoch> OrderedReplay::apply_next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one cached ordered input and acknowledge only after atomic engine success. |
| inputs / outputs | Checks moved-from state, runs prepare, returns nullopt at EOF, calls runtime.apply_view(event.update), then acknowledge and moves PhysicalEpoch into optional. |
| invariants | Input progress/source map is staged before engine work; acknowledge is nonthrowing/nonallocating and epoch move is statically nothrow. Engine rejection leaves the complete cached event/progress retryable on its bound owner; output retry is separate. |
| ownership | Cached native update is borrowed through apply; returned epoch owns its required journal/output state. Acknowledgement can release/replace reader cache, so no input view escapes. |
| failure | All prepare/decode/engine failures propagate before acknowledge; no generic catch or automatic retry. No throwing input bookkeeping follows successful engine publication. |
| cost | Fixed wrapper gates plus real decode/fingerprint and whole engine update costs; acknowledgement uses prepared owners rather than allocating a new progress map after commit. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 54–60](../../../../../src/runtime/replay.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<DeltaRuntime::Epoch> OrderedReplay::apply_next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one cached ordered input and acknowledge only after atomic engine success. |
| inputs / outputs | Checks moved-from state, runs prepare, returns nullopt at EOF, calls runtime.apply_view(event.update), then acknowledge and moves DeltaRuntime::Epoch into optional. |
| invariants | Input progress/source map is staged before engine work; acknowledge is nonthrowing/nonallocating and epoch move is statically nothrow. Engine rejection leaves the complete cached event/progress retryable on its bound owner; output retry is separate. |
| ownership | Cached native update is borrowed through apply; returned epoch owns its required journal/output state. Acknowledgement can release/replace reader cache, so no input view escapes. |
| failure | All prepare/decode/engine failures propagate before acknowledge; no generic catch or automatic retry. No throwing input bookkeeping follows successful engine publication. |
| cost | Fixed wrapper gates plus real decode/fingerprint and whole engine update costs; acknowledgement uses prepared owners rather than allocating a new progress map after commit. |
| Design | [src/runtime/replay.cpp](../../../../../src/runtime/replay.cpp), [include/crown/runtime/replay.hpp](../../../../../include/crown/runtime/replay.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/io/ingest_program.cpp](../../../../../src/io/ingest_program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/ingestion.md](../../../../ingestion.md), [tests/unit/ingest_test.cpp](../../../../../tests/unit/ingest_test.cpp), [tests/unit/ingest_exception_test.cpp](../../../../../tests/unit/ingest_exception_test.cpp), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 61–61](../../../../../src/runtime/replay.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L61:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/replay.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

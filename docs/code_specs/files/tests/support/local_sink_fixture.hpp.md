# `tests/support/local_sink_fixture.hpp` — block usage map

[Source](../../../../../tests/support/local_sink_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `da301c5171dd1a2cc7d08300f91a0e62b9e8bb86633cee77524157375b600e8d`. 30 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/support/local_sink_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–14](../../../../../tests/support/local_sink_fixture.hpp#L12) | Callable definition: inline runtime::SessionLocalSinkOptions options() | calls std::copy, begin, end; returns result · [reviewed contract](#b0002) |
| [B0003 · 15–15](../../../../../tests/support/local_sink_fixture.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Commit retains outbox delivery for the caller; no public next_output drain here. · [reviewed contract](#b0003) |
| [B0004 · 16–16](../../../../../tests/support/local_sink_fixture.hpp#L16) | Callable definition: inline void finish(runtime::QuerySession& session) | calls step, commit; 1 loop sites; source comment (unverified): // Commit retains outbox delivery for the caller; no public next_output drain here. · [reviewed contract](#b0004) |
| [B0005 · 17–17](../../../../../tests/support/local_sink_fixture.hpp#L17) | Explanatory comments or spacing. | source comment (unverified): // Epoch owns native rows during export; returned signed set owns ordinary copies. · [reviewed contract](#b0005) |
| [B0006 · 18–20](../../../../../tests/support/local_sink_fixture.hpp#L18) | Callable definition: inline typed::Output output(const sk::Epoch& epoch) | calls check, emplace, storage::export_row, storage::TupleValuesView::borrow; guard typed::Output result;for(const auto& row:epoch.rows)check(result.emplace(row.operation,storage::exp…; returns result; growth emplace; 1 loop sites; source comment (unverified): // Epoch owns native rows during export; returned signed set owns ordinary copies. · [reviewed contract](#b0006) |
| [B0007 · 21–23](../../../../../tests/support/local_sink_fixture.hpp#L21) | Callable definition: inline void apply(Database& database,const PhysicalSetUpdate& update) | calls insert, erase; growth insert · [reviewed contract](#b0007) |
| [B0008 · 24–29](../../../../../tests/support/local_sink_fixture.hpp#L24) | Type/record definition: struct Fixture | guard void commit(std::size_t index) {typed::enqueue(*query.session,io::InputEvent{query.test.updates\[ind… · [reviewed contract](#b0008) |
| [B0009 · 30–30](../../../../../tests/support/local_sink_fixture.hpp#L30) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::local_sink_test · [reviewed contract](#b0009) |

## B0001

[Lines 1–11](../../../../../tests/support/local_sink_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:f4bce24306df1441d8e8f9dcabcf2657aefc3c4d4a06745ac9b2abf76571c952
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare local_sink_fixture.hpp: include "generation_fixture.hpp", "crown/runtime/session_local_sink.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–14](../../../../../tests/support/local_sink_fixture.hpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline runtime::SessionLocalSinkOptions options(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a deterministic sink ID for fixture delivery. |
| inputs / outputs | Copies 32 literal ASCII hex bytes into sink_id with other defaults. |
| invariants | Fixed test metadata is checked by actual sink APIs; it is not entropy or a receipt capability. |
| ownership | Returns owning fixed fields, with no borrowed literal data retained. |
| failure | No explicit fixed-copy failure; later sink admission can reject mismatch. |
| cost | Fixed 32-byte copy/default options. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–15](../../../../../tests/support/local_sink_fixture.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:efdcbc0ce30f97e239f97561a815ff1e557f06579d154c63902bee3bee76a77b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Commit retains outbox delivery for the caller; no public next_output drain here. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 16–16](../../../../../tests/support/local_sink_fixture.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void finish(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit one active epoch while retaining local-sink outbox delivery for the caller. |
| inputs / outputs | Steps until prepared then commits; does not call next_output or deliver_local_epoch. |
| invariants | The omission of public output draining is intentional for sink tests; delivery is a separate real API action. |
| ownership | Borrows live session; pending output/outbox remains native session-owned. |
| failure | Native step/commit failures propagate; no independent iteration cap or recovery wrapper. |
| cost | All real preparation/commit work; zero ordinary output export in this helper does not mean no engine allocation. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 17–17](../../../../../tests/support/local_sink_fixture.hpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:79fe2579dfd8f7aac180482b0b9879e3181c37bfc1602a6c074d14a76a78d881
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Epoch owns native rows during export; returned signed set owns ordinary copies. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 18–20](../../../../../tests/support/local_sink_fixture.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline typed::Output output(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a persisted local epoch into ordinary signed-set expected data. |
| inputs / outputs | Borrows each epoch row value view, exports Row, inserts operation/row and rejects duplicates. |
| invariants | Epoch retains actual accounted row ownership during export; this helper does not create native proof/source authority or counted bag results. |
| ownership | Returns deep-owning ordinary set; source tuple views borrow only through each synchronous export. |
| failure | Export/set allocation/assertion failures propagate without mutating persisted epoch. |
| cost | O(epoch rows log rows) plus scalar copies/comparisons; ordinary expected-data storage is outside native accounting. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 21–23](../../../../../tests/support/local_sink_fixture.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a trusted physical set update to the independent ordinary model database. |
| inputs / outputs | Inserts update.values or erases the matching row in database.tables\[table.value\]. |
| invariants | No sequence/table/type/source admission; caller supplies valid fixture shape. Set duplicates/noop semantics are deliberate. |
| ownership | Insert deep-copies Row into model; erase destroys its ordinary copy; does not share native storage keys. |
| failure | Allocation/index misuse follows ordinary containers; no native engine mutation or rollback coordination. |
| cost | O(log table rows) lookup plus row/scalar compare and insertion copy/allocation. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 24–29](../../../../../tests/support/local_sink_fixture.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own generation-backed source session and its actual local sink. |
| inputs / outputs | Retains generation_test::Fixture plus owning results.sink path; constructor calls create_local_sink. |
| invariants | Creates a real persisted sink under source Directory. commit prepares query/outbox but delivery must be invoked separately. |
| ownership | Move-only session within query prevents ordinary Fixture copying; path and Case retain their real ordinary payloads. |
| failure | Source or sink creation failures propagate with best-effort directory cleanup; no atomic fixture-wide filesystem rollback. |
| cost | Generation setup plus real sink header creation and native delivery admission, path copies. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

```text
explicit Fixture(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the native local sink attached to a generation session. |
| inputs / outputs | Initializes query/indexed/kind, computes results.sink and invokes create_local_sink(options). |
| invariants | The sink is bound through actual production checks, not merely fixed sink_id assignment. |
| ownership | query owns source before path and sink setup; session cleanup precedes Directory removal. |
| failure | Constructor can leave prior real files until Directory cleanup if sink creation rejects. |
| cost | Real source/generation setup plus sink file/open/lock/write work and ordinary path construction. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

```text
void commit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit a fixture input without automatically delivering its sink epoch. |
| inputs / outputs | Enqueues feed event, requires begin_next and calls local finish. |
| invariants | Trusted trace index; caller chooses delivery timing to exercise outbox retry/restart. |
| ownership | Native session owns input/state/outbox; helper returns no borrowed row. |
| failure | Native failures propagate; successful commit can precede later caller-side delivery failures. |
| cost | Actual queue/update/commit work; no independent oracle scan or sink delivery inside this function. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [tests/unit/local_sink_test.cpp](../../../../../tests/unit/local_sink_test.cpp), [tests/unit/local_sink_fault_test.cpp](../../../../../tests/unit/local_sink_fault_test.cpp), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 30–30](../../../../../tests/support/local_sink_fixture.hpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L30:sha256:ada7eddee2f3c8f90078b9675164f89b536b3699c598a94bc859f23b5e8a829d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in local_sink_fixture.hpp: namespace crown::local_sink_test. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/local_sink_fixture.hpp](../../../../../tests/support/local_sink_fixture.hpp), [docs/local-sink.md](../../../../local-sink.md), [docs/code_review.md](../../../../code_review.md) |

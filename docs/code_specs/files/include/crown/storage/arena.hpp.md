# `include/crown/storage/arena.hpp` — block usage map

[Source](../../../../../../include/crown/storage/arena.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `fc687b4bbd2ee992c765606c9ed3cd78b5edbb7a6d77cda65afda1cd6e1ffe25`. 81 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/storage/arena.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Counts records/slots, not allocator bytes. Free slots retain metadata only; · [reviewed contract](#b0001) |
| [B0002 · 11–19](../../../../../../include/crown/storage/arena.hpp#L11) | Type/record definition: struct ArenaStatistics | source comment (unverified): // Counts records/slots, not allocator bytes. Free slots retain metadata only; · [reviewed contract](#b0002) |
| [B0003 · 20–24](../../../../../../include/crown/storage/arena.hpp#L20) | declares types or opens a type body. | source comment (unverified): // Single-threaded, noncopyable tuple owner. Allocation returns a stable slot · [reviewed contract](#b0003) |
| [B0004 · 25–46](../../../../../../include/crown/storage/arena.hpp#L25) | Type/record definition: public: class Pin | source comment (unverified): // Releases retention without allocating. A reset/moved-from pin is empty; · [reviewed contract](#b0004) |
| [B0005 · 47–81](../../../../../../include/crown/storage/arena.hpp#L47) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Failed allocation leaves every published slot, generation and counter · [reviewed contract](#b0005) |

## B0001

[Lines 1–10](../../../../../../include/crown/storage/arena.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:951e7633fd2a734ee82b34367f1955f23c0ef50357337586670466746b8c0046
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/arena.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/layout.hpp"\`, \`&lt;memory&gt;\` for compilation; opens namespace \`crown::storage\`; forward-declares \`class ReferenceTable\`, \`class IndexedTable\` without defining object layout. Source comment: Counts records/slots, not allocator bytes. Free slots retain metadata only; payloads (including owned strings) are destroyed as soon as no pin needs them. |
| inputs / outputs | Compile-time consumers may name \`class ReferenceTable\`, \`class IndexedTable\` while their definitions remain owned by the declaring headers/source files. |
| invariants | Forward declarations permit references to incomplete types; consumers that need layout or members include the defining header. The source note says: Counts records/slots, not allocator bytes. Free slots retain metadata only; payloads (including owned strings) are destroyed as soon as no pin needs them. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Counts records/slots, not allocator bytes. Free slots retain metadata only; payloads (including owned strings) are destroyed as soon as no pin needs them. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 11–19](../../../../../../include/crown/storage/arena.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArenaStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report live, retained and reusable arena population facts. |
| inputs / outputs | slots/live_records/retained_records/pins/free_slots/exhausted_slots count metadata and payload populations; default comparison compares all six. |
| invariants | Pins count pin objects on both live and retired rows; these are not allocator-byte limits or cursor retention. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/arena.hpp](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp](../../../../../../src/storage/arena.cpp), [tests/unit/arena_storage_test.cpp](../../../../../../tests/unit/arena_storage_test.cpp), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 20–24](../../../../../../include/crown/storage/arena.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TupleArena {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the standalone tuple owner with a hidden State implementation and nested Pin type. |
| inputs / outputs | This block establishes the public owner type; constructor and operation signatures are in the adjacent class body. |
| invariants | State is incomplete in the public declaration, so slot layout is private to the implementation. |
| ownership | The class declaration owns no state; TupleArena instances and Pins own state at runtime. |
| failure | No runtime failure path exists in the type declaration. |
| cost | Type declaration only; instance construction is the operation that creates State. |
| Design | [include/crown/storage/arena.hpp §TupleArena](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp §TupleArena::State](../../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md §Ownership and identity](../../../../../tuple_arenas.md) |

## B0004

[Lines 25–46](../../../../../../include/crown/storage/arena.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Pin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one immutable arena payload beyond logical membership. |
| inputs / outputs | Move-only Pin reads handle/get/is_live, and reset releases its slot pin and retained State reference. |
| invariants | erase/clear/destruction invalidate ordinary handles and membership immediately. A pin never preserves table indexes or cursor validity. |
| ownership | shared State and per-slot pin counts keep the payload and slot metadata alive; a reset/moved-from pin is empty. |
| failure | Empty accessors throw invalid_pin; reset/destruction are noexcept and allocate nothing. New pin acquisition separately checks pin overflow. |
| cost | Normal pin bookkeeping is fixed. Last retired-payload release destroys that payload, and last closed-State release can destroy all high-water slot metadata; no blanket O(1) destructor claim. |
| Design | [include/crown/storage/arena.hpp](../../../../../../include/crown/storage/arena.hpp), [src/storage/arena.cpp](../../../../../../src/storage/arena.cpp), [tests/unit/arena_storage_test.cpp](../../../../../../tests/unit/arena_storage_test.cpp), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 47–81](../../../../../../include/crown/storage/arena.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit TupleArena(TupleLayout layout);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own tuple payload slots and expose generational handle, borrow, pin, erase, and clear operations. |
| inputs / outputs | A TupleLayout and tuples in; ArenaHandles, borrowed tuples, pins, and statistics out. |
| invariants | Foreign handles throw; stale contains/erase return false while stale get/pin throw; erase removes membership immediately. |
| ownership | Pins retain immutable payload/state across erase or owner loss, but do not retain table membership or cursors. |
| failure | Failed insert leaves published slot state unchanged; layout mismatch, stale/foreign handles, and ID exhaustion are defined failures. |
| cost | Insert may allocate/grow storage; clear visits live rows and check_invariants scans all slots. Pin bookkeeping is constant, but the last pin can destroy its payload and, after owner close, all high-water slot metadata. |
| Design | [src/storage/arena.cpp §TupleArena::insert and pin](../../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md §Slot lifecycle and reclamation](../../../../../tuple_arenas.md), [docs/storage.md §Reference table and cursors](../../../../../storage.md) |

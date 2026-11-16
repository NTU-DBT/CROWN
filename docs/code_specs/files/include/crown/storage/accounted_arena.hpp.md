# `include/crown/storage/accounted_arena.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_arena.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `74e137e880125ea491e06c25b3c380a3aba639d47de0c579e69e84d39f8aac62`. 96 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/storage/accounted_arena.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–10](../../../../../../include/crown/storage/accounted_arena.hpp#L10) | Type/record definition: enum class ArenaProblem |  · [reviewed contract](#b0002) |
| [B0003 · 11–19](../../../../../../include/crown/storage/accounted_arena.hpp#L11) | Type/record definition: class ArenaValidationFailure final : public std::exception | returns issue_ · [reviewed contract](#b0003) |
| [B0004 · 20–24](../../../../../../include/crown/storage/accounted_arena.hpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Slot/row figures contain actual request, payload and allocation counts. · [reviewed contract](#b0004) |
| [B0005 · 25–35](../../../../../../include/crown/storage/accounted_arena.hpp#L25) | Type/record definition: struct ArenaMemoryStatistics | source comment (unverified): // Slot/row figures contain actual request, payload and allocation counts. · [reviewed contract](#b0005) |
| [B0006 · 36–44](../../../../../../include/crown/storage/accounted_arena.hpp#L36) | declares types or opens a type body. | source comment (unverified): // Native arena with stable owner/slot/generation handles. Layout metadata, · [reviewed contract](#b0006) |
| [B0007 · 45–63](../../../../../../include/crown/storage/accounted_arena.hpp#L45) | Type/record definition: public: class Pin |  · [reviewed contract](#b0007) |
| [B0008 · 64–96](../../../../../../include/crown/storage/accounted_arena.hpp#L64) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Explicit whole-arena diagnostic; bounded storage and no allocations. · [reviewed contract](#b0008) |

## B0001

[Lines 1–9](../../../../../../include/crown/storage/accounted_arena.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:3e08a8c03aca175941bd515aef87050ce3f5d4c86914a2e99d21a40345758def
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_arena.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/accounted_layout.hpp"\`, \`"crown/storage/arena.hpp"\`, \`&lt;exception&gt;\`, \`&lt;memory&gt;\`, \`&lt;string_view&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 10–10](../../../../../../include/crown/storage/accounted_arena.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class ArenaProblem
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep fixed arena diagnostic categories. |
| inputs / outputs | Invalid facade/pin, foreign/stale handle, layout mismatch or invariant issue. |
| invariants | Categories describe a fault; they do not authorize an inverse or manufacture handle validity. |
| ownership | Inline enum. |
| failure | No failure/allocation in the enum. |
| cost | Fixed tag. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0003

[Lines 11–19](../../../../../../include/crown/storage/accounted_arena.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ArenaValidationFailure final
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present fixed arena failures without formatted strings. |
| inputs / outputs | Constructor stores ArenaProblem; issue/code/what expose that category. |
| invariants | what and code map to static literals, including a fallback for unknown tags. |
| ownership | Exception owns only the enum; returned descriptions have static lifetime. |
| failure | Construction/access are noexcept; throwing still uses normal exception-runtime machinery. |
| cost | Fixed fields/switches, no native account allocation. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0004

[Lines 20–24](../../../../../../include/crown/storage/accounted_arena.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L24:sha256:fa9f228d060f007dc950fd06a6d8572bed2719b3c313e3a03436841f82f59bdd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct ArenaMemoryStatistics\`: Slot/row figures contain actual request, payload and allocation counts. Directory spare payload is a portion of its existing allocation, not a second charge. Shared layout metadata and the query controller are separate owners in the same query account and are not counted again here. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/accounted_arena.hpp:L25; use that declaration for the actual input/output shape. |
| invariants | The source note states: Slot/row figures contain actual request, payload and allocation counts. Directory spare payload is a portion of its existing allocation, not a second charge. Shared layout metadata and the query controller are separate owners in the same query account and are not counted again here. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Slot/row figures contain actual request, payload and allocation counts. Directory spare payload is a portion of its existing allocation, not a second charge. Shared layout metadata and the query controller are separate owners in the same query account and are not counted again here. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Slot/row figures contain actual request, payload and allocation counts. Directory spare payload is a portion of its existing allocation, not a second charge. Shared layout metadata and the query controller are separate owners in the same query account and are not counted again here. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0005

[Lines 25–35](../../../../../../include/crown/storage/accounted_arena.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArenaMemoryStatistics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Partition one arena attribution into actual allocation/request/payload usage. |
| inputs / outputs | Records, state/directory, live/retained/free/exhausted slot and tuple partitions plus spare directory payload. |
| invariants | Directory spare is part of existing capacity, not another charge. Shared layout/controller remain different account owners. |
| ownership | Plain owning counters; carries no slot references or authority. |
| failure | Value construction/copy is nonallocating; obtaining the full report requires the diagnostic scan. |
| cost | Fixed-size result; memory_statistics performs O(A+H) account/high-water scans. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0006

[Lines 36–44](../../../../../../include/crown/storage/accounted_arena.hpp#L36); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedTupleArena {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own stable native tuple handles under one existing finite account. |
| inputs / outputs | Immutable AccountedLayout supplies account; insert/lookup/pin/erase/clear expose controlled membership. |
| invariants | Single mutating thread; exact layout token, owner/slot/generation and live/retained rules are separate checks. |
| ownership | Facade shares State only with its Pins; account funds state/control/directory/slots/deep tuples. |
| failure | Prepare tuple and directory capacity before live publication; normal unwind replaces extra catch/undo scaffolding. |
| cost | Direct handle operations are fixed work; insertion copies fields/bytes and may grow directory; full diagnostics/teardown are explicit. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0007

[Lines 45–63](../../../../../../include/crown/storage/accounted_arena.hpp#L45); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Pin {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one authenticated slot generation through membership removal. |
| inputs / outputs | Move-only pin exposes lvalue tuple borrow, identity, live flag and reset. |
| invariants | Only arena constructs pins after checked counters; no public fabricated or copied pin. |
| ownership | Shared State retains slot/payload until pin reset; rvalue get is deleted. |
| failure | Empty access rejects; reset/destruction are nonthrowing. |
| cost | Fixed normal pin operations; final retention release can destroy tuple and O(H) State storage. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

## B0008

[Lines 64–96](../../../../../../include/crown/storage/accounted_arena.hpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] ArenaMemoryStatistics memory_statistics() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request the full attributed high-water memory diagnostic. |
| inputs / outputs | Returns all native arena memory partitions. |
| invariants | Shared-account total is distinct from this arena owner; no limit is refilled. |
| ownership | Counter result owns no tuple/slot. |
| failure | Invalid facade/account contract rejects; successful scan uses no dynamic scratch. |
| cost | O(all account allocations + arena high-water slots); keep it outside per-row lookup/update paths. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

```text
void revive(const Pin&) noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a retained slot only through owner-held inverse authority. |
| inputs / outputs | Private table journal supplies a matching live Pin for a deleted slot. |
| invariants | Slot must be retained, same state/generation and nonlive; inverse neither allocates nor increments generation. |
| ownership | Existing pin/slot/tuple retain original account/layout/identity. |
| failure | Broken internal inverse preconditions terminate; user input cannot call this private operation. |
| cost | Fixed checks and live-link/classification edits, no payload copy. |
| Design | [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_reports.md](../../../../../memory_reports.md), [include/crown/storage/accounted_arena.hpp](../../../../../../include/crown/storage/accounted_arena.hpp) |

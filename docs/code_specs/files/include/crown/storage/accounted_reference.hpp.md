# `include/crown/storage/accounted_reference.hpp` — block usage map

[Source](../../../../../../include/crown/storage/accounted_reference.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `464f1b208a32b9baf9ae3db6c9339b9cccbaf856b09bcb70457ed6432d5f9261`. 146 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../../include/crown/storage/accounted_reference.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–11](../../../../../../include/crown/storage/accounted_reference.hpp#L10) | Type/record definition: enum class TableProblem |  · [reviewed contract](#b0002) |
| [B0003 · 12–19](../../../../../../include/crown/storage/accounted_reference.hpp#L12) | Type/record definition: class TableValidationFailure final : public std::exception |  · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../../include/crown/storage/accounted_reference.hpp#L20) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 21–28](../../../../../../include/crown/storage/accounted_reference.hpp#L21) | Type/record definition: struct TableMemoryStatistics | source comment (unverified): // Table + arena, shared metadata counted separately. · [reviewed contract](#b0005) |
| [B0006 · 29–37](../../../../../../include/crown/storage/accounted_reference.hpp#L29) | declares types or opens a type body. | source comment (unverified): // Native ordered reference backend. All owned containers, deep keys, state, · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../../include/crown/storage/accounted_reference.hpp#L38) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0007) |
| [B0008 · 39–65](../../../../../../include/crown/storage/accounted_reference.hpp#L39) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // List-backed O(index) access. The pin-backed tuple survives commit while · [reviewed contract](#b0008) |
| [B0009 · 66–83](../../../../../../include/crown/storage/accounted_reference.hpp#L66) | Type/record definition: class Cursor | source comment (unverified): // Low-level cursors borrow weak table ownership and check revisions. Runtime · [reviewed contract](#b0009) |
| [B0010 · 84–99](../../../../../../include/crown/storage/accounted_reference.hpp#L84) | Type/record definition: class IndexKeyCursor |  · [reviewed contract](#b0010) |
| [B0011 · 100–135](../../../../../../include/crown/storage/accounted_reference.hpp#L100) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0011) |
| [B0012 · 136–146](../../../../../../include/crown/storage/accounted_reference.hpp#L136) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0012) |

## B0001

[Lines 1–9](../../../../../../include/crown/storage/accounted_reference.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:a6492e0bad417acfe65c278459376110b4aa0cac5cdbd13d2e7dec82ca2b1225
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/accounted_reference.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/accounted_arena.hpp"\`, \`"crown/storage/accounted_projection.hpp"\`, \`"crown/storage/table_types.hpp"\`, \`"crown/resource/ownership.hpp"\`, \`&lt;vector&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 10–11](../../../../../../include/crown/storage/accounted_reference.hpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class TableProblem {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate native storage validation outcomes without allocating diagnostics. |
| inputs / outputs | Enumerates invalid table/journal/cursor, foreign/stale handle, layout/index, busy and invariant problems. |
| invariants | Absence can be a normal operation result; foreign ownership and broken internal state are different errors. |
| ownership | Inline enum; no resource owner or payload. |
| failure | Presented by TableValidationFailure; this enum alone performs no recovery. |
| cost | Fixed scalar tag; no success-path message construction. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0003

[Lines 12–19](../../../../../../include/crown/storage/accounted_reference.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TableValidationFailure final
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed native ordered-table failure codes through exception unwinding. |
| inputs / outputs | Problem enum yields stable code/what text, with no formatted user message. |
| invariants | A public/runtime boundary can separately translate native failures; caller state restoration remains the operation obligation. |
| ownership | Stores an enum and borrows static code/message bytes. |
| failure | Construction/accessors are noexcept; C++ exception-runtime allocation is a separate scope. |
| cost | Fixed value construction/access; no ordinary-new diagnostic string allocation. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0004

[Lines 20–20](../../../../../../include/crown/storage/accounted_reference.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using AccountedVector = std::vector<T, resource::MemoryAllocator<T>>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a vector whose element storage uses MemoryAllocator. |
| inputs / outputs | AccountedVector&lt;T&gt; has the std::vector interface with a MemoryAllocator&lt;T&gt; allocator. |
| invariants | The allocator funds this vector's storage; nested payload ownership remains the element type's responsibility. |
| ownership | Each vector owns its allocated element buffer under the allocator's MemoryAccount. |
| failure | The alias itself cannot fail; vector growth may throw account or capacity errors. |
| cost | The alias has no runtime cost; operations retain std::vector growth and destruction costs. |
| Design | [include/crown/storage/accounted_reference.hpp §AccountedVector](../../../../../../include/crown/storage/accounted_reference.hpp), [src/storage/accounted_reference.cpp §accounted collection results](../../../../../../src/storage/accounted_reference.cpp), [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 21–28](../../../../../../include/crown/storage/accounted_reference.hpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TableMemoryStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe ordered-table native ownership and logical populations. |
| inputs / outputs | Reports records/indices/keys/memberships, active/retained history, table and arena attributed allocation statistics. |
| invariants | owned adds disjoint table+arena current usage; shared immutable descriptors and caller-tagged output remain separate owners. |
| ownership | Owns counter structures only, not copies of rows or allocation-ledger entries. |
| failure | Collection can reject invalid state; the value type performs no repair. |
| cost | Fixed result storage; collecting it scans the actual ledger/arena/index-key populations. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0006

[Lines 29–37](../../../../../../include/crown/storage/accounted_reference.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedReferenceTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the native ordered comparison backend under an existing layout account. |
| inputs / outputs | Typed native insert/find/get/index/copy/journal/cursor operations maintain one exact-set table. |
| invariants | Primary/ID/arena/index populations agree; ordinary mutation/cursor startup rejects an active journal, including no-op writes. Low-level reads may see tentative contents; runtime owners enforce query-level visibility. |
| ownership | Move-only facade owns shared State. Original account funds deep values/containers/outputs; low-level cursors are weak and payload pins retain their separate arena lifetime. |
| failure | Fixed native failures distinguish foreign ownership/layout/busy/stale conditions. Preparation precedes mutation; journals provide funded reverse undo. |
| cost | Ordered comparator/deep-byte and container costs remain explicit; this is the semantic reference, not a constant-time indexed claim. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0007

[Lines 38–38](../../../../../../include/crown/storage/accounted_reference.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChangeView { bool inserted;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one pinned journal change without cloning its native tuple. |
| inputs / outputs | Direction and logical handle accompany a const tuple reference. |
| invariants | Tentative handles stay internal until commit; this view is not an owning snapshot or durable identity proof. |
| ownership | Tuple borrows the containing journal entry pin; commit preserves it, rollback/history destruction releases it. |
| failure | An already borrowed view cannot validate its own lifetime after its journal closes/clears. |
| cost | Fixed scalars/reference; history ordinal lookup cost is separate. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0008

[Lines 39–65](../../../../../../include/crown/storage/accounted_reference.hpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own exclusive ordered-table mutation, exact inverse nodes and pinned change history. |
| inputs / outputs | Open table journal accepts inserts/handle erases; commit keeps state, rollback/destruction restores reverse changes. |
| invariants | Single active table journal; prefix reads use its Reader. Close is idempotent. Revision is not rolled back, and uncommitted IDs must never escape as committed authority. |
| ownership | Active Data strongly owns State; after commit only affected detached nodes/keys/payload pins and weak reporting authority remain. Moves transfer the token and clean the old destination. |
| failure | Failed operation preparation preserves prior journal stages; abandoned active token reverses them. Native undo/publication allocate nothing. |
| cost | Per-change accounted inverse/list/key work; change(i) is O(i). Commit/undo have real map, ledger-classification and release costs. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0009

[Lines 66–83](../../../../../../include/crown/storage/accounted_reference.hpp#L66); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose ordinary or journal-authorized borrowed ordered row traversal. |
| inputs / outputs | next returns handles; lvalue next_entry returns handle plus const native tuple; end yields nullopt. |
| invariants | Each call validates live facade, journal phase/authority and unchanged revision before iterator access. A weak cursor is not a mutation-blocking reader lease. |
| ownership | Owns small accounted Data and optional shared Reader; State remains weak. Borrowed entries need source lifetime or a separate pin. |
| failure | Moved/expired/revised/aborted cursor rejects before dereference; a conflicting journal reports storage_busy. |
| cost | Primary iterator access is fixed; bucket tuple entries add O(log rows) ID lookup. No owning result/bucket materialization. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

```text
struct Entry { TupleHandle handle; const AccountedTuple& tuple; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one cursor logical handle with its borrowed arena tuple. |
| inputs / outputs | Both values identify the selected live native row. |
| invariants | This is one entry, not an added pin or copied tuple. |
| ownership | Reference follows cursor/table mutation and lifetime rules. |
| failure | No autonomous validation after returning from cursor next_entry. |
| cost | Fixed handle/reference assembly; no deep payload allocation. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0010

[Lines 84–99](../../../../../../include/crown/storage/accounted_reference.hpp#L84); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse distinct live projection keys and their maintained degrees. |
| inputs / outputs | Lvalue next returns borrowed key/degree entries or nullopt. |
| invariants | Ordinary key cursor requires unlocked current table state and matching revision; it is invalidated by real mutation/index drop. |
| ownership | Accounted cursor Data holds weak State and ordered-map iterators, not key copies. |
| failure | Moved/expired/busy/revised cursor rejects before key access. |
| cost | O(log indices) factory lookup plus fixed per-key iterator/degree access; no population-sized startup copy. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

```text
struct Entry { const AccountedTuple& key; std::size_t degree; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one borrowed secondary key and exact live bucket size. |
| inputs / outputs | Reference and scalar degree come directly from the current bucket. |
| invariants | Degree is set cardinality, not an independently validated join multiplicity. |
| ownership | Key borrows native index storage; caller may explicitly clone it under the original account. |
| failure | Mutation/index/table loss ends the unretained borrow. |
| cost | Fixed entry construction and maintained size read, no member scan. |
| Design | [docs/storage_journal.md](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/storage.md](../../../../../storage.md) |

## B0011

[Lines 100–135](../../../../../../include/crown/storage/accounted_reference.hpp#L100); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountedReferenceTable(RelationId, AccountedLayout);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the account-backed ordered reference table API for relation rows and projected indexes. |
| inputs / outputs | RelationId and frozen AccountedLayout in; insert/find/get/pin/erase/index/journal/cursor/snapshot results out. |
| invariants | Tuple handles are checked against owner/relation; get is borrowed, while pin explicitly retains payload but not membership. |
| ownership | Table state and returned AccountedVector buffers use the layout's query account; snapshots and keys own copied values. |
| failure | Invalid layout, foreign/stale handles, unknown indexes, active-journal conflicts, and account failures are reported. |
| cost | Ordered table operations compare keys; keys/snapshot allocate and copy outputs, with work dependent on rows and key widths. |
| Design | [src/storage/accounted_reference.cpp §AccountedReferenceTable methods](../../../../../../src/storage/accounted_reference.cpp), [docs/storage.md §Reference table and cursors](../../../../../storage.md), [docs/storage_journal.md §Accounted native interfaces](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0012

[Lines 136–146](../../../../../../include/crown/storage/accounted_reference.hpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<State> state_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose explicit live-state snapshot_copy and check_invariants operations while retaining the private shared State. |
| inputs / outputs | snapshot_copy returns a distinct table rebuilt from live rows and registered indexes; check_invariants scans arena/table/index state; state_ retains the current implementation State. |
| invariants | snapshot_copy requires the table to be unlocked; the facade is noncopyable and move transfers its State. Empty state() rejects. |
| ownership | The shared state owns the table account/layout/maps; a journal may retain it, while an arena pin retains payload state only. |
| failure | state() reports invalid_table for an empty facade; snapshot_copy can reject an active journal or fail during account-backed copying, and failed invariant predicates raise TableValidationFailure(invariant). |
| cost | snapshot_copy visits/copies live rows and index registrations; check_invariants scans arena slots, rows, keys, and memberships. Final State cleanup can release resident containers and payloads. |
| Design | [src/storage/accounted_reference.cpp §AccountedReferenceTable construction](../../../../../../src/storage/accounted_reference.cpp), [src/storage/accounted_reference.cpp §snapshot_copy](../../../../../../src/storage/accounted_reference.cpp), [docs/storage_journal.md §Accounted native interfaces](../../../../../storage_journal.md), [docs/query_memory.md](../../../../../query_memory.md) |

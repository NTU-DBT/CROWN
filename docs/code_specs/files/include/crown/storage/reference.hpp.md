# `include/crown/storage/reference.hpp` — block usage map

[Source](../../../../../../include/crown/storage/reference.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `93c4bb931ffcf9cc4c65909e0248a2f0a0fba7fcb93bb6020a06ff41a8b9f068`. 131 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../../include/crown/storage/reference.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body. | source comment (unverified): // Standard-container storage for one logical relation. Owning/noncopyable, · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../../include/crown/storage/reference.hpp#L17) | Type/record definition: struct ChangeView |  · [reviewed contract](#b0002) |
| [B0003 · 18–45](../../../../../../include/crown/storage/reference.hpp#L18) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Exclusive, single-writer mutation scope. Tentative handles/reads must stay · [reviewed contract](#b0003) |
| [B0004 · 46–67](../../../../../../include/crown/storage/reference.hpp#L46) | Type/record definition: class Cursor | source comment (unverified): // Visits live handles only. Real mutation/owner destruction invalidates · [reviewed contract](#b0004) |
| [B0005 · 68–83](../../../../../../include/crown/storage/reference.hpp#L68) | Type/record definition: class IndexKeyCursor | source comment (unverified): // Borrow expires on mutation, destruction, or next traversal. No pins. · [reviewed contract](#b0005) |
| [B0006 · 84–91](../../../../../../include/crown/storage/reference.hpp#L84) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |
| [B0007 · 92–127](../../../../../../include/crown/storage/reference.hpp#L92) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): // Borrowed until erase/clear/destruction. · [reviewed contract](#b0007) |
| [B0008 · 128–131](../../../../../../include/crown/storage/reference.hpp#L128) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0008) |

## B0001

[Lines 1–16](../../../../../../include/crown/storage/reference.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReferenceTable {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the ReferenceTable storage representation and its explicit primitive protocol. |
| inputs / outputs | Set-valued insert/find/get/pin/erase, projection index registration/probes, owning snapshots and lazy cursors operate on one relation/layout. |
| invariants | Logical IDs belong to one storage owner; exact layout/projection tokens matter. Journal mutation is exclusive and tentative handles remain internal until commit. |
| ownership | Concrete owners retain rows/indexes/arena. Ordinary std containers/shared controls are a standalone/tool boundary, not native query-account accounting; returned references/cursor entries borrow unless explicitly pinned/copied. |
| failure | Concrete validation, allocation, overflow and journal/cursor failures propagate. Indexed operations additionally require the original finite work grant; facade dispatch creates none. |
| cost | Ordered map/set operations compare actual typed/deep values with logarithmic lookup factors; the mixed facade adds fixed dispatch and retains each concrete backend's costs. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../../include/crown/storage/reference.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ChangeView { bool inserted; TupleHandle handle; const Tuple& tuple; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one retained journal change without copying its payload. |
| inputs / outputs | ChangeView carries insertion/deletion polarity, a TupleHandle and const Tuple& from journal.change(index). |
| invariants | A change view is not current table membership; commit can remove rows while retained change payload remains readable. Rollback clears history. |
| ownership | The reference requires its original journal-owned pin/history lifetime; copying this struct alone retains nothing. |
| failure | Constructing the view is fixed; change(index) separately validates journal/index state and can reject. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 18–45](../../../../../../include/crown/storage/reference.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  class Journal {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one exclusive standalone ReferenceTable mutation journal. |
| inputs / outputs | insert/erase prepare change history and inverse records; live/bucket cursors see internal tentative state; change(index) exposes retained payload; commit/rollback close the mutation scope. |
| invariants | Reference journals retain detached ordered-container nodes for allocation-free inverse operations. Tentative handles/reads stay internal until commit; destruction rolls an active journal back in reverse order. |
| ownership | An active journal retains table State; completed history retains affected payload pins until destruction. A copied ChangeView is only a reference to that lifetime. |
| failure | Invalid/closed journal, capacity/overflow/work or allocation failures propagate during preparation. commit/rollback/destruction use prepared no-throw cleanup; no catch/retry is added to this header. |
| cost | Per mutation, journal storage and per-index projected keys/membership records are prepared; commit/rollback process actual history and releases. Retained capacity can survive successful tentative operations and logical rollback. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0004

[Lines 46–67](../../../../../../include/crown/storage/reference.hpp#L46); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Cursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse ordered reference rows or bucket IDs lazily. |
| inputs / outputs | Move-only Cursor provides next() handles and next_entry() borrowed Tuple references. |
| invariants | Actual mutation/revision change, journal rollback or owner loss invalidates traversal; duplicate insert/absent erase no-ops preserve it. |
| ownership | Ordinary allocated cursor data uses weak table ownership and retains journal reader metadata when applicable. It does not pin rows; returned references need source stability. |
| failure | Invalid/moved/expired/busy/stale cursor state rejects through Error before using invalid iterators. |
| cost | Primary traversal and bucket handle next advance one ordered iterator. Bucket next_entry additionally resolves ById in O(log rows); neither successful step deep-copies or pins payloads. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 68–83](../../../../../../include/crown/storage/reference.hpp#L68); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexKeyCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Traverse distinct ordered projection keys and bucket sizes. |
| inputs / outputs | Move-only IndexKeyCursor::next returns optional {const Tuple& key,degree}. |
| invariants | Key borrow expires on next traversal, mutation or destruction; an independent equal descriptor does not validate an input key token. |
| ownership | Cursor metadata owns no table lifetime or key payload pin; table/read stability must be supplied externally. |
| failure | Invalid/moved/expired/mutated/busy states reject rather than replaying a snapshot or refilling work. |
| cost | Fixed cursor allocation at construction and one ordered-key iterator step per success/end; degree reads the stored bucket population without materializing it. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0006

[Lines 84–91](../../../../../../include/crown/storage/reference.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReferenceTable(RelationId relation, TupleLayout layout);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the movable, noncopyable ReferenceTable lifecycle and its index-key cursor factory. |
| inputs / outputs | Construction takes RelationId and TupleLayout; index_keys(IndexId) returns a move-only cursor over ordered keys; move operations transfer the facade. |
| invariants | Copy construction/assignment are deleted; move transfers shared State. IndexKeyCursor checks owner lifetime and table revision on next(). |
| ownership | The facade holds shared State; IndexKeyCursor holds only a weak State reference and does not keep the table alive. |
| failure | Construction or cursor-record allocation can fail; moved-from calls and unknown indexes reject, and cursor next rejects an expired owner or changed revision. |
| cost | Construction creates State/arena; index_keys allocates cursor data, and next advances the ordered key iterator. The declaration promises no bounded container or teardown cost. |
| Design | [src/storage/reference.cpp §ReferenceTable construction](../../../../../../src/storage/reference.cpp), [src/storage/reference.cpp §ReferenceTable::index_keys and IndexKeyCursor::next](../../../../../../src/storage/reference.cpp), [docs/storage.md §Reference table and cursors](../../../../../storage.md) |

## B0007

[Lines 92–127](../../../../../../include/crown/storage/reference.hpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] InsertResult insert(const Tuple& tuple);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert/probe/remove set rows through ReferenceTable's concrete storage contract. |
| inputs / outputs | insert returns {inserted,handle}; find returns optional handle, get borrows payload, pin retains payload, and erase(tuple/handle) removes membership. |
| invariants | Duplicate inserts and absent erases are no-ops. Foreign owner/layout tokens reject; stale/missing handles follow concrete contracts. Ordinary mutation is locked while an exclusive journal is active. |
| ownership | The standalone owner funds ordinary containers; get is a borrow, not a pin. An explicit pin retains immutable payload after erase/clear/owner loss without preserving membership. |
| failure | Public Error, component-cap/work and allocator failures propagate; preparation precedes links and failed operations preserve logical state. |
| cost | Ordered lookup/mutation pays logarithmic map/set comparisons over actual typed values and per-index projections. Payload copying and final destruction cost actual selected/string bytes; the facade adds only fixed dispatch. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] IndexId add_index(Projection projection);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register and operate explicit projection indexes in ReferenceTable. |
| inputs / outputs | add_index registers a projection, drop_index removes it, projection exposes its immutable handle, key_count counts distinct keys, keys/bucket materialize owning outputs, and erase_key removes a whole key bucket. |
| invariants | Same projection token registration is idempotent; equal field lists with independent tokens may coexist. Lookup key must have the exact target token. Nullary keys and repeated fields are ordinary values, not sentinels. |
| ownership | Returned vectors are ordinary owning collections; legacy Tuple copies can deep-copy strings. Returned bucket handles do not pin rows; projection handles retain immutable metadata. |
| failure | Invalid index/key/layout, busy state, size/cap/work/account or allocation failures propagate. Adding an index finishes throwing preparation before registration; no catch/retry/refill is added. |
| cost | Index creation visits existing rows and projects each key; removal/erase_key visit actual affected keys/memberships. keys/snapshot copy actual outputs, bucket is O(matches) handle materialization. Hash collisions or ordered comparison costs remain concrete-backend work. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] std::vector<Tuple> snapshot() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning row collection from ReferenceTable. |
| inputs / outputs | snapshot returns all live rows in this backend's defined traversal order; keys similarly returns distinct owning projected tuples. |
| invariants | Reference order is lexical; indexed order is insertion/first-live-key order. This is an explicit collection boundary, separate from lazy cursor traversal. |
| ownership | An ordinary vector owns returned tuples; legacy rows deep-copy payload, while already native-backed public tuples may share immutable funded payload. |
| failure | Output allocation, overflow, owner-state and any required indexed work denial propagate; no partially returned collection escapes. |
| cost | Visits/materializes all live rows or keys plus actual deep-byte clone/copy costs; output vector capacity/control is additional. Native index work is finite but is not a total CPU or allocator-byte measurement. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

```text
void check_invariants() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an explicit full diagnostic on ReferenceTable state. |
| inputs / outputs | check_invariants cross-checks rows, arena, directories, indexes, memberships, ownership/counters and active journal relationships. |
| invariants | This diagnostic is separate from the operational grant and is never a cursor/probe implementation or hot-update prerequisite. |
| ownership | Reads the existing owner; its diagnostic scratch/cost is representation-specific, not output ownership or a new budget. |
| failure | Inconsistent state throws the concrete contract diagnostic; standalone diagnostics can allocate scratch/error text. No recovery is attempted. |
| cost | May allocate and scan arena high-water, rows/indices/keys/memberships, including collision-heavy/quadratic checks. It has no constant operational bound. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

```text
  void clear();
  [[nodiscard]] Cursor live() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open a lazy table-row or key-bucket cursor with explicit lifetime fences. |
| inputs / outputs | live walks current rows; bucket_cursor resolves an index/key then walks only that bucket; index_keys walks distinct projected keys/degrees. |
| invariants | Standalone cursors require live weak State, unchanged revision and a nonaborted journal-reader phase; an active journal can retain State beyond its facade. Ordinary factories reject an exclusive active journal. |
| ownership | Factory owns fixed cursor metadata (account-funded on native route) but keeps only weak table ownership. Entries borrow; the enclosing runtime must supply any read lease. |
| failure | Factory can reject owner/index/key/grant/work/account/allocation state; next separately checks its lifetime fences before dereference. |
| cost | Startup allocates fixed cursor data; bucket startup additionally pays index/key lookup and scalar-byte comparison. Successful traversal avoids full result collection and payload copy/pin; reference bucket next_entry still adds ordered-ID lookup. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

```text
[[nodiscard]] ReferenceTable snapshot_copy() const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent live storage with fresh backend/arena owners. |
| inputs / outputs | snapshot_copy preserves live logical tuple/index IDs, high-water counters/revision and concrete traversal order while rebinding internal links/iterators. |
| invariants | It rejects an active journal and copies neither external pins nor retired allocations/source action history. The copied population is a new baseline. |
| ownership | Copy owns separate ordinary table/index/arena storage; public native-backed tuple payloads can retain immutable shared native ownership as their representation allows. |
| failure | Allocation, work/cap/account or invalid-state failure discards the private incomplete copy; source logical state remains unchanged. |
| cost | Visits all live rows/indexes/keys/memberships and copies/rebinds their data; native copy clones deep values. Indexed copy borrows one finite aggregate operation allowance, never one new grant per table. |
| Design | [include/crown/storage/reference.hpp](../../../../../../include/crown/storage/reference.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [docs/storage.md](../../../../../storage.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_review.md](../../../../../code_review.md) |

## B0008

[Lines 128–131](../../../../../../include/crown/storage/reference.hpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<State> state_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the ReferenceTable's mutable backend State behind the public facade. |
| inputs / outputs | state() returns the mutable State owned by state_; facade constructors and move operations install/transfer that handle. |
| invariants | State groups the arena and ordered primary/ID/index containers; calls use the facade’s current State handle. |
| ownership | The shared pointer owns State and its arena/container graph; callers of state() borrow that object. |
| failure | state() rejects an empty moved-from facade with invalid_storage. |
| cost | The member declaration allocates nothing; final State release destroys resident table structures with data-dependent cleanup. |
| Design | [src/storage/reference.cpp §ReferenceTable::State](../../../../../../src/storage/reference.cpp), [docs/storage.md §Reference table and cursors](../../../../../storage.md) |

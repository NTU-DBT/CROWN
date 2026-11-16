# `src/storage/indexed_journal.inc` — block usage map

[Source](../../../../../src/storage/indexed_journal.inc) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Record/reverse standalone indexed mutations using prepaid growth, pinned nodes and saved neighbors.

Snapshot SHA-256: `fd48e9b7197775559f982cc9c1669f3a2fbb24024987a3db690cdad99a59e186`. 201 lines partitioned into 26 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/storage/indexed_journal.inc#L1) | declares types or opens a type body. | source comment (unverified): // Included once inside crown::storage, after IndexedTable::State. No separate · [reviewed contract](#b0001) |
| [B0002 · 5–12](../../../../../src/storage/indexed_journal.inc#L5) | Type/record definition: struct Key |  · [reviewed contract](#b0002) |
| [B0003 · 13–25](../../../../../src/storage/indexed_journal.inc#L13) | Type/record definition: struct Undo |  · [reviewed contract](#b0003) |
| [B0004 · 26–29](../../../../../src/storage/indexed_journal.inc#L26) | Member/declaration region. |  · [reviewed contract](#b0004) |
| [B0005 · 30–31](../../../../../src/storage/indexed_journal.inc#L30) | Callable definition: Data(std::shared_ptr&lt;State&gt; state, std::shared_ptr&lt;IndexedJournalReader&gt; authority) noexcept : owner(std::move(state)), reader(st… | calls owner, std::move, reader · [reviewed contract](#b0005) |
| [B0006 · 32–32](../../../../../src/storage/indexed_journal.inc#L32) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0006) |
| [B0007 · 33–38](../../../../../src/storage/indexed_journal.inc#L33) | Callable definition: State& active() const | calls Error; returns *owner · [reviewed contract](#b0007) |
| [B0008 · 39–55](../../../../../src/storage/indexed_journal.inc#L39) | Callable definition: std::unique_ptr&lt;Undo&gt; prepare(bool inserted) | calls active, room, size, max_size; returns result; growth make_unique · [reviewed contract](#b0008) |
| [B0009 · 56–60](../../../../../src/storage/indexed_journal.inc#L56) | Callable definition: void publish(std::unique_ptr&lt;Undo&gt; undo) noexcept | calls size, capacity, std::terminate, push_back; growth push_back; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 61–74](../../../../../src/storage/indexed_journal.inc#L61) | Callable definition: void release_keys(Undo& undo) noexcept | calls std::terminate, size; 1 loop sites; source comment (unverified): // The last reference proves that no later inverse can dereference this · [reviewed contract](#b0010) |
| [B0011 · 75–87](../../../../../src/storage/indexed_journal.inc#L75) | Callable definition: void undo_insert(Undo& undo) noexcept | calls unlink_prepaid, first, erase_prepaid, size; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 88–102](../../../../../src/storage/indexed_journal.inc#L88) | Callable definition: void undo_erase(Undo& undo) noexcept | calls revive, link_between_prepaid, size, insert_between_prepaid; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 103–106](../../../../../src/storage/indexed_journal.inc#L103) | Callable definition: void close() noexcept | calls reset · [reviewed contract](#b0013) |
| [B0014 · 107–115](../../../../../src/storage/indexed_journal.inc#L107) | Callable definition: void rollback() noexcept | calls rbegin, rend, undo_insert, undo_erase; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 116–132](../../../../../src/storage/indexed_journal.inc#L116) | Callable definition: void commit() noexcept | calls size, release_keys, close; 1 loop sites; source comment (unverified): // Only change-view pins and inert pointer records remain caller-owned. · [reviewed contract](#b0015) |
| [B0016 · 133–134](../../../../../src/storage/indexed_journal.inc#L133) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 135–135](../../../../../src/storage/indexed_journal.inc#L135) | Callable definition: IndexedTable::Journal::Journal(std::unique_ptr&lt;Data&gt; data) noexcept : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0017) |
| [B0018 · 136–138](../../../../../src/storage/indexed_journal.inc#L136) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 139–139](../../../../../src/storage/indexed_journal.inc#L139) | Callable definition: bool IndexedTable::Journal::active() const noexcept | calls ; returns data_ && data_-&gt;owner · [reviewed contract](#b0019) |
| [B0020 · 140–140](../../../../../src/storage/indexed_journal.inc#L140) | Callable definition: std::size_t IndexedTable::Journal::size() const noexcept | calls size; returns data_ ? data_-&gt;entries.size() : 0 · [reviewed contract](#b0020) |
| [B0021 · 141–145](../../../../../src/storage/indexed_journal.inc#L141) | Callable definition: IndexedTable::ChangeView IndexedTable::Journal::change(std::size_t index) const | calls size, Error, get; returns {entry.inserted, entry.handle, entry.pin-&gt;get()} · [reviewed contract](#b0021) |
| [B0022 · 146–146](../../../../../src/storage/indexed_journal.inc#L146) | Callable definition: void IndexedTable::Journal::rollback() noexcept | calls rollback · [reviewed contract](#b0022) |
| [B0023 · 147–147](../../../../../src/storage/indexed_journal.inc#L147) | Callable definition: void IndexedTable::Journal::commit() noexcept | calls commit · [reviewed contract](#b0023) |
| [B0024 · 148–152](../../../../../src/storage/indexed_journal.inc#L148) | Callable definition: InsertResult IndexedTable::Journal::insert(const Tuple& tuple) | calls Error, active, facade, insert_impl; returns facade.insert_impl(tuple, *data_-&gt;reader-&gt;work, data_.get()); growth insert · [reviewed contract](#b0024) |
| [B0025 · 153–190](../../../../../src/storage/indexed_journal.inc#L153) | Callable definition: bool IndexedTable::Journal::erase(TupleHandle handle) | calls Error, active, start, row; returns false; true; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 191–201](../../../../../src/storage/indexed_journal.inc#L191) | Callable definition: IndexedTable::Journal IndexedTable::journal(std::shared_ptr&lt;IndexWorkAllowance&gt; work) | calls Error, state, unlocked, start; returns Journal(std::move(data)); growth make_shared, make_unique · [reviewed contract](#b0026) |

## B0001

[Lines 1–4](../../../../../src/storage/indexed_journal.inc#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedTable::Journal::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the single included inverse-record owner after complete indexed State. |
| inputs / outputs | The inc file is included once within crown::storage; Data provides preparation, publication, inverse, close and finalization helpers. |
| invariants | No second translation unit, storage owner authority or grant is introduced. All inverse work is prepaid before forward mutation. |
| ownership | Data owns State while active, original reader/grant and unique affected Undo records; ordinary table graph is not copied. |
| failure | Declaration has no runtime exception layer; specific preparation/poison boundaries belong to methods. |
| cost | Journal retained state scales with affected changes/memberships plus pinned payloads, not an unrelated-table snapshot. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0002

[Lines 5–12](../../../../../src/storage/indexed_journal.inc#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Key {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remember one exact key/member and saved list neighbors for reverse-order erase undo. |
| inputs / outputs | Stores key/member pointers, previous/next bucket members and previous/next publicly live keys. |
| invariants | Pointers refer to stable nodes, not old hash bucket arrays. Saved neighbors are valid only after all later operations have been undone. |
| ownership | Borrows row-owned member and resident key; published journal_references retain empty keys until no inverse can use them. |
| failure | Record performs no validation/allocation; callers must prepare complete stable locations before mutation. |
| cost | Six fixed pointers per affected index, no key projection/payload clone. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp) |

## B0003

[Lines 13–25](../../../../../src/storage/indexed_journal.inc#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Undo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one successful reversible insertion/erasure and its exact immutable payload. |
| inputs / outputs | Stores direction, logical handle, previous tuple-ID high-water, row and directory neighbors, optional arena Pin and per-index Key vector. |
| invariants | Inserted inverse restores previous_last; erased inverse revives same allocation/generation/address and original live ordering. Complete published Undo always has a pin. |
| ownership | Unique Undo owns its pin and vector; raw row/key/member pointers are acted on only while State is active, and become inert retained history after commit. |
| failure | Construction itself noexcept; vector/pin preparation may fail only before forward mutation. |
| cost | O(I) fixed pointer records and one retained payload pin per change; no full-table copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0004

[Lines 26–29](../../../../../src/storage/indexed_journal.inc#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<State> owner;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep active strong table authority and unique vector-backed change history. |
| inputs / outputs | Data owns State, shared IndexedJournalReader and vector&lt;unique_ptr&lt;Undo&gt;&gt;. |
| invariants | owner nonempty denotes active; after commit owner is released but entries/pins remain for change views, whereas rollback clears entries. |
| ownership | State strong only while active; reader retains original grant. Entries uniquely own affected records/pins, not table State after close. |
| failure | Declarations perform no admission or cleanup themselves. |
| cost | O(changes) pointer capacity plus O(changes*I) inverse records/pins; vector capacity may survive rollback. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0005

[Lines 30–31](../../../../../src/storage/indexed_journal.inc#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<State> state, std::shared_ptr<IndexedJournalReader> authority) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the exact table and reader owners prepared by journal(). |
| inputs / outputs | Moves shared State and reader into Data. |
| invariants | Reader already retains nonnull original allowance; State active flags are published only after this Data allocation succeeds. |
| ownership | Acquires moved strong owners, no second State/grant/payload copy. |
| failure | Noexcept shared_ptr moves. |
| cost | Constant transfer; allocations occur in factory. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0006

[Lines 32–32](../../../../../src/storage/indexed_journal.inc#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Automatically reverse an uncommitted journal before releasing its records. |
| inputs / outputs | Destructor invokes idempotent rollback; committed/rolled-back Data has no owner and skips inverse. |
| invariants | Move replacement destroys destination Data through the same path; caller cannot forget rollback by losing an active scope. |
| ownership | Active inverse releases pins/records, then State; committed destruction instead drops retained history pins after rollback no-op. |
| failure | Noexcept cleanup; impossible inverse invariants terminate. |
| cost | O(affected changes/members) reverse undo when active; committed history release can free payloads or last closed arena high-water metadata. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0007

[Lines 33–38](../../../../../src/storage/indexed_journal.inc#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
State& active() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exact live Data/State/reader authority before journal operations. |
| inputs / outputs | Checks owner, journal_active, State active_journal==this and active reader phase, then returns State. |
| invariants | Prevents using a moved, committed, rolled-back or replaced journal for further mutation/cursor creation. |
| ownership | Borrowed State remains strong in Data throughout active operation. |
| failure | invalid_journal before any mutation/work lookup when authority is closed or inconsistent. |
| cost | Constant pointer/phase checks; no graph scan. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0008

[Lines 39–55](../../../../../src/storage/indexed_journal.inc#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::unique_ptr<Undo> prepare(bool inserted)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare entry capacity, one inverse owner and per-index location capacity before mutation. |
| inputs / outputs | Direction in; checks journal entry count, grows entries geometrically within finite max, admits Undo metadata and reserves key vector for every registered index. |
| invariants | No push may allocate after publication starts. Grants are retained original balance; no-op insert/erase avoids this helper and consumes no history entry. |
| ownership | Returns private unique Undo; entries may retain successfully grown capacity even if later preparation fails. Ordinary vector/node allocations are outside query account. |
| failure | Entry overflow/capacity/work/bad_alloc before mutation; charges/capacity need not roll back. |
| cost | Amortized O(1) entry growth plus O(I) requested pointer slots; a growth moves O(changes) owners and allocates new array. Not actual allocator-byte accounting. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0009

[Lines 56–60](../../../../../src/storage/indexed_journal.inc#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish(std::unique_ptr<Undo> undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach a complete prepaid inverse record after successful forward link publication. |
| inputs / outputs | Requires spare entries capacity and pin, increments each key journal reference and State journal_entries, moves Undo into entries. |
| invariants | Every key reference room was checked during preparation. No inverse is published without exact retained payload pin. |
| ownership | Transfers unique record/pin ownership into active history; key raw pointers now protected by explicit references. |
| failure | Invariant missing-capacity/pin terminates; vector push cannot allocate within reserved capacity for unique_ptr. |
| cost | O(I) key reference increments and one constant-capacity vector insertion; no hash/copy/admission/allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0010

[Lines 61–74](../../../../../src/storage/indexed_journal.inc#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void release_keys(Undo& undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one inverse's key references and reclaim only final unneeded empty keys. |
| inputs / outputs | For each saved key decrements journal_references; if zero and no live members, verifies detached live hook and deletes key. |
| invariants | Only final reference proves no later inverse can dereference the key. Retired row destructors detach actual hooks without reading stale raw key pointers. |
| ownership | Drops retained key ownership via its resident directory hook; inert Undo pointer records need no pointee lifetime after close. |
| failure | Zero reference or empty-key live-hook inconsistency terminates; valid path allocates/admit nothing. |
| cost | O(I) key checks plus actual last-key payload/node destruction, no projection/hash/key lookup. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

## B0011

[Lines 75–87](../../../../../src/storage/indexed_journal.inc#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_insert(Undo& undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse one tentative insertion using original stable nodes and prepaid work. |
| inputs / outputs | Unlinks row primary/ID, removes each bucket/member and last-live-key link, erases arena membership, deletes row, decrements tentative counts and restores previous_last. |
| invariants | Reverse operation order makes later erase of the same inserted row already revived; keys remain resident while any history references them. Revision deliberately stays advanced. |
| ownership | Deletes row-owned members/row; affected payload pin remains until rollback entries clear. release_keys follows separately. |
| failure | Any missing arena membership or hook/state inconsistency terminates; no recoverable partial rollback. |
| cost | O(I) targeted pointer/node work plus later pin/key teardown, no lookup/hash/projection/allocation/new work grant. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0012

[Lines 88–102](../../../../../src/storage/indexed_journal.inc#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void undo_erase(Undo& undo) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revive the exact retained allocation and restore original resident/bucket/key order. |
| inputs / outputs | Uses pin to revive arena, links row at saved primary/ID neighbors with cached hashes, restores empty-key live positions and member bucket positions, decrements retained/pending counts. |
| invariants | Strict reverse undo restores saved neighbors first. No new TupleId/generation/allocation/address is created; row-owned members never left their row list. |
| ownership | Returns retained row/member ownership to live graph; history pin is later released with entries. |
| failure | Private revive/hook mismatch terminates inside noexcept; all capacity/work was prepaid by erase. |
| cost | O(I) saved-pointer inserts and fixed arena update; no search, hash, projection, key copy or allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0013

[Lines 103–106](../../../../../src/storage/indexed_journal.inc#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop exclusive authority and the active journal's strong State owner. |
| inputs / outputs | Resets weak reader, active Data pointer and journal_active, then owner.reset(). |
| invariants | Called only after commit/rollback consumes all active inverse obligations. Reader phase was already set; reader/grant may survive with cursor/history. |
| ownership | If this is final table State owner, complete resident graph teardown runs here; pins can keep arena storage after table loss. |
| failure | Noexcept owner release relies on valid nonthrowing destructor invariants. |
| cost | Fixed authority stores plus potentially O(all live nodes/members+payloads) State teardown and eventual O(arena high-water) metadata release. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0014

[Lines 107–115](../../../../../src/storage/indexed_journal.inc#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort journal-reader authority, reverse successful changes backward, clear views and close scope. |
| inputs / outputs | If owner absent returns; otherwise marks aborted, walks entries in reverse with correct direction inverse, releases key references/counts, clears entries and closes. |
| invariants | Reader abort precedes raw-node changes; last_tuple restores aborted insertion IDs, revision does not rewind, committed counts stay unchanged. No new grants requested. |
| ownership | Returns retained rows to live graph, removes inserted rows, then releases entry/pin owners. Vector capacity may remain; State release can tear down unrelated live graph if final owner. |
| failure | Idempotent closed call; invariant failures terminate. No bad_alloc recovery/allocation is attempted during inverse. |
| cost | O(changes+affected memberships) prepaid inverse plus key/payload/record destruction; add final State/arena teardown when ownership ends. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0015

[Lines 116–132](../../../../../src/storage/indexed_journal.inc#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finalize installed tentative rows without fresh work/allocation and retain change-view pins. |
| inputs / outputs | If owner absent returns; otherwise marks committed, transfers checked pending action totals, deletes erased row/member nodes, releases key references and closes. |
| invariants | Headroom for pending sums was validated by each mutation. Inserted live nodes stay installed; erased rows never revive after commit. Entries' raw pointers become inert. |
| ownership | Keeps entry/pin history until journal destruction while dropping strong State. Final State owner release may destroy unrelated live rows/indices even though change payloads remain pinned. |
| failure | Idempotent closed call; private destructor/reference corruption terminates rather than catching partial finalization. |
| cost | O(changes+erased memberships+released keys) prepaid bookkeeping/destruction plus possible final whole-State/arena teardown; no whole-table snapshot copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0016

[Lines 133–134](../../../../../src/storage/indexed_journal.inc#L133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L133-L134:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct IndexedTable::Journal::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct IndexedTable::Journal::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct IndexedTable::Journal::Data\` at its lexical source position in src/storage/indexed_journal.inc; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct IndexedTable::Journal::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0017

[Lines 135–135](../../../../../src/storage/indexed_journal.inc#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Journal::Journal(std::unique_ptr<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the completely prepared exclusive journal record owner. |
| inputs / outputs | Moves unique Data into Journal. |
| invariants | Factory publishes State authority only after reader/Data allocations succeeded. |
| ownership | Exclusive Data owns active State or committed affected history; no new allowance. |
| failure | Noexcept pointer move. |
| cost | Constant transfer. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0018

[Lines 136–138](../../../../../src/storage/indexed_journal.inc#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Journal::Journal(Journal&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move or destroy journal unique ownership with automatic rollback on replacement/loss. |
| inputs / outputs | Default move constructor/assignment/destructor manage data_. |
| invariants | Moving preserves same Data address stored as active_journal; moved-from operations reject or safe-return as specified. Destination replacement rolls back its prior active scope. |
| ownership | Transfers/relinquishes unique Data and all pin/grant owners, without copying affected history. |
| failure | Noexcept cleanup relies on inverse/State/arena invariants. |
| cost | Move construction fixed; assignment/destruction can run full affected undo/pin and final-State teardown. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0019

[Lines 139–139](../../../../../src/storage/indexed_journal.inc#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool IndexedTable::Journal::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether this facade still owns an active State scope. |
| inputs / outputs | Returns data_ && data_-&gt;owner. |
| invariants | Committed/rolled-back/moved journal returns false; does not independently revalidate all private authority pointers. |
| ownership | No retained new owner. |
| failure | Noexcept query. |
| cost | Constant pointer checks. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0020

[Lines 140–140](../../../../../src/storage/indexed_journal.inc#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t IndexedTable::Journal::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read recorded successful changes without scanning history. |
| inputs / outputs | Returns entries.size() or0 for moved facade. |
| invariants | Commit retains history; rollback clears entries; duplicate/absent operations add no entry. |
| ownership | Scalar copy, no payload pin/copy. |
| failure | Noexcept query. |
| cost | Constant vector size read. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md) |

## B0021

[Lines 141–145](../../../../../src/storage/indexed_journal.inc#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::ChangeView IndexedTable::Journal::change(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one affected immutable Tuple from journal-owned pin history. |
| inputs / outputs | Zero-based index in; vector entry returns direction, original logical handle and entry.pin-&gt;get() reference. |
| invariants | Available while active/committed; rollback clears history. Handle direction/identity can describe erased or inserted-then-erased records, not current membership. |
| ownership | View does not own its pin; caller keeps its history alive (moves transfer it). Commit preserves payload; active rollback or destruction/replacement of that history ends borrow. Closed rollback is a no-op. |
| failure | invalid_journal on moved/out-of-range; valid pin get remains private lifetime authority. |
| cost | O(1) vector access and pin slot validation, no list scan, hash, projection, copy or success allocation. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md) |

## B0022

[Lines 146–146](../../../../../src/storage/indexed_journal.inc#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::Journal::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose idempotent prepaid rollback through optional Data owner. |
| inputs / outputs | Calls Data.rollback when data_ exists; moved/closed facade safely returns. |
| invariants | All real inverse behavior and reader abort occur in Data; no new allowance/refill. |
| ownership | May clear history/pins and drop final State owner. |
| failure | Noexcept private-invariant poison boundary propagates by termination. |
| cost | Affected inverse/cleanup and possible final owner teardown cost; fixed wrapper. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0023

[Lines 147–147](../../../../../src/storage/indexed_journal.inc#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void IndexedTable::Journal::commit() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose idempotent prepaid commit through optional Data owner. |
| inputs / outputs | Calls Data.commit when data_ exists; moved/closed facade safely returns. |
| invariants | No new grant, hash/projection or allocation is introduced by wrapper. |
| ownership | Keeps affected history pins while releasing strong table authority. |
| failure | Noexcept private-invariant poison boundary propagates by termination. |
| cost | Affected finalization and possible final owner teardown cost; fixed wrapper. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp) |

## B0024

[Lines 148–152](../../../../../src/storage/indexed_journal.inc#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InsertResult IndexedTable::Journal::insert(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert through the active journal's exact State and original grant. |
| inputs / outputs | Requires non-moved active Data, creates private shared-State facade and calls insert_impl(tuple,original_work,data). |
| invariants | Bypasses ordinary journal exclusion only with verified active Data authority; same duplicate probe makes no history. |
| ownership | Temporary facade shares State, not table contents; successful mutation publishes one complete Undo/pin into this Data. |
| failure | Moved/closed/layout/work/capacity/allocation failures propagate before publication as defined by insert_impl. |
| cost | Insert probe/O(I) projected preparation/publication plus fixed shared-owner facade; no snapshot/independent grant. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0025

[Lines 153–190](../../../../../src/storage/indexed_journal.inc#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool IndexedTable::Journal::erase(TupleHandle handle)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a retained row/member inverse before unlinking one live journal row. |
| inputs / outputs | Uses active State and exact original grant; absent authorized ID returns false, success records handle/pin/saved positions and returns true. |
| invariants | Checks revision/committed+pending counts, total pins, history/key-reference room and all forward/inverse/finalization work before mutation. Retains rows instead of rebuilding on undo. |
| ownership | Undo owns pin and borrowed key/member/neighbor records; row remains allocated with its row-owned members while detached from live directories/buckets. |
| failure | Validation/work/allocation/preparation failure preserves installed graph/history/revision; post-pin valid-state link publication is nonthrowing and corruption terminates. |
| cost | ID-chain lookup plus O(I) saved locations/admissions and link changes; conservative row/key scalar debits do not actually clone payloads. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

```text
undo->primary_previous = row->primary_link.resident_previous;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture stable erase inverse neighbors and debit both mutation and inverse/finalization before unlink. |
| inputs / outputs | Copies primary/ID resident neighbors and each member's bucket/live-key neighbors into pre-reserved Undo keys; admits all required structural/link/scalar work. |
| invariants | Cached hashes and stable nodes avoid re-projection, rehash or directory-array pointers in undo. Key references prevent later empty-key destruction while any inverse needs it. |
| ownership | Only private Undo vector/pointer records are prepared here; row/key tuple views remain borrowed. |
| failure | Any work/reference-room rejection precedes pin and first live link change. Prior work/capacity remains spent/retained. |
| cost | O(I) exact neighbor records plus conservative full affected row/key scalar admissions; no payload copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/index_scalar_work.hpp](../../../../../src/storage/index_scalar_work.hpp), [src/storage/live_list.hpp](../../../../../src/storage/live_list.hpp), [src/storage/hash_directory.hpp](../../../../../src/storage/hash_directory.hpp) |

```text
undo->pin.emplace(s.arena.pin(row->allocation));
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin original erased payload then publish detachment and one complete inverse record. |
| inputs / outputs | Acquires checked nonallocating pin; removes bucket/live-key links and primary/ID residency, erases arena membership, advances retained/pending/revision counters and publishes Undo. |
| invariants | After the pin no fallible admission/allocation/hash/projection remains. Empty keys stay resident under journal references; absent public membership does not invalidate pinned payload. |
| ownership | Retained row still owns members; Undo pin owns payload lifetime and publish increments key references before control returns. |
| failure | Noexcept pointer/arena invariants terminate if private preparation was inconsistent; do not insert exception handling after partial unlink. |
| cost | O(I) prepaid link writes/reference increments, constant arena retirement and counters; no tuple allocation/copy. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [src/storage/indexed_nodes.hpp](../../../../../src/storage/indexed_nodes.hpp) |

## B0026

[Lines 191–201](../../../../../src/storage/indexed_journal.inc#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedTable::Journal IndexedTable::journal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open one exclusive journal with an owning finite allowance supplied by its caller. |
| inputs / outputs | Nonnull shared work in; checks State/unlocked, debits startup/fixed metadata, allocates reader and Data, then publishes active authority. |
| invariants | Same grant object is retained for all operations/cursors/composed scopes; factory creates no substitute/refill. Flag/pointer publication follows all throwing construction. |
| ownership | Data retains exact State strongly, reader owns original grant, State keeps weak reader/raw Data for fencing only. Ordinary allocations are separate from native query-account routes. |
| failure | Null grant, moved/busy/work/allocation errors leave State journal authority unchanged; prior work remains consumed. |
| cost | Two fixed ownership allocations plus shared-reference setup and constant authority writes; no row/index snapshot. |
| Design | [include/crown/storage/indexed.hpp](../../../../../include/crown/storage/indexed.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [Refactor.md §11.4 S03–S05](../../../../../Refactor.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |
